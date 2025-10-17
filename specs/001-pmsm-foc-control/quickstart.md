# Quickstart: PMSM FOC Control System

## Prerequisites

Before starting development with the PMSM FOC Control System, ensure you have the following tools and hardware:

### Development Environment
- STM32CubeMX 6.12.0 or later
- STM32CubeCLT (CLion/VScode/STM32CubeIDE command-line tools)
- GCC ARM Embedded Toolchain 
- CMake 3.21 or later
- Eclipse ThreadX RTOS package
- Git for version control

### Hardware Requirements
- STM32G474RET6  or custom board with STM32G474xx microcontroller
- PMSM motor with encoder feedback
- 3-phase motor driver (e.g., IXXAT USB-to-CAN or compatible)
- Power supply appropriate for your motor (typically 12-48V)
- Debug probe (ST-LINK/V2 or equivalent)

## Initial Setup

### 1. Clone the Repository
```bash
git clone <repository_url>
cd motor-project
```

### 2. Install Dependencies
The project uses STM32CubeMX to generate initialization code and HAL drivers. Ensure you have the required STM32G4 series packages installed in STM32CubeMX.

For ThreadX RTOS:
```bash
# ThreadX should be available in Middlewares/Third_Party/Azure-RTOS/
# If not present, download from Microsoft GitHub
```

### 3. Configure STM32CubeMX Project
1. Open `stm32g4-motor-project-ex.ioc` in STM32CubeMX
2. Verify the configuration matches your hardware setup:
   - Enable required peripherals (ADC1/2 for current sensing, TIM1/8 for PWM, USART1 for communication, CAN1 for CAN communication)
   - Configure clock tree appropriately (170MHz max for G474)
   - Set up GPIO pins for motor control and feedback
3. Generate code to the `Core/` directory
4. Ensure the generated code follows MISRA C guidelines

### 4. Build the Project
```bash
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/stm32g474xx.cmake

# Build the project
make -j$(nproc)
```

## Basic Usage

### 1. Flash the Firmware
```bash
# Connect your ST-LINK debugger
# Flash the firmware using STM32CubeProgrammer
STM32_Programmer_CLI -c port=SWD -w build/motor-project.bin -v -s
```

### 2. Motor Configuration
Before operating the motor, configure the parameters for your specific PMSM:

1. Connect to the board via serial or CAN interface
2. Send configuration commands with your motor parameters:
   - Pole pairs
   - Rated current
   - Rated speed
   - Torque constant
   - Stator resistance
   - D/Q axis inductance

### 3. Basic Motor Control
The system supports three control modes:

#### Current Control Mode
```c
// Set current control mode
set_control_mode(CURRENT_CONTROL);

// Set d-axis and q-axis current targets
set_current_target(0.0f, 5.0f);  // Id=0A, Iq=5A
```

#### Speed Control Mode
```c
// Set speed control mode
set_control_mode(SPEED_CONTROL);

// Set target speed (RPM)
set_speed_target(1000.0f);  // 1000 RPM
```

#### Position Control Mode
```c
// Set position control mode
set_control_mode(POSITION_CONTROL);

// Set target position (degrees)
set_position_target(90.0f);  // 90 degrees
```

## Communication Interface

### Serial Interface (UART)
The system supports serial communication at 115200 baud by default. Commands follow this format:
- Start motor: `START`
- Stop motor: `STOP`
- Set speed: `SPEED <value>` (RPM)
- Set position: `POS <value>` (degrees)
- Get status: `STATUS`
- Get parameters: `PARAMS`

### CAN Interface
Default CAN configuration uses 1Mbps baud rate with 11-bit identifiers:
- Command frame ID: 0x100
- Status frame ID: 0x200
- Parameter frame ID: 0x300

## Safety Features

The system includes multiple safety layers:

1. **Hardware Protection**: Immediate response to overcurrent via hardware comparators
2. **Software Monitoring**: Continuous monitoring of voltage, temperature, and speed
3. **Safe State**: Automatic transition to safe state on fault detection
4. **Emergency Stop**: Immediate motor stop on emergency input

To check safety status:
```c
safety_state_t state = get_safety_status();
if (state.fault_occurred) {
    // Handle fault - check state.last_fault_code
    clear_faults();
}
```

## Troubleshooting

### Motor Not Responding
- Verify power supply connections
- Check encoder feedback connections
- Verify motor parameters are correctly configured
- Check current limits are not too low

### Communication Issues
- Verify baud rate settings (serial)
- Check CAN bus termination (should be 120Ω at each end)
- Verify message format and frame IDs

### FOC Not Working Properly
- Verify pole pairs are set correctly
- Check current sensing calibration
- Verify encoder alignment (rotor position at electrical angle 0°)

## Next Steps

1. **Configuration**: Adjust motor parameters for your specific motor
2. **Tuning**: Fine-tune PID controllers for your mechanical system
3. **Safety Testing**: Verify all safety functions operate as expected
4. **Performance Validation**: Test timing constraints and response characteristics