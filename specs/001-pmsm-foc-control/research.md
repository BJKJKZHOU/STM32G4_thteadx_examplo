# Research: PMSM FOC Control System

## Decision: Use STM32G474xx with HAL/LL libraries
**Rationale**: The STM32G474xx is specifically designed for real-time motor control applications with integrated peripherals like FPU, advanced timers, and ADCs optimized for motor control. HAL/LL libraries provide the right balance between hardware abstraction and performance for meeting timing requirements.

**Alternatives considered**:
- STM32F3xx: Lower cost but less processing power and memory
- STM32H7xx: More powerful but overkill for this application and higher cost
- Other manufacturers: STMicroelectronics ecosystem provides better support for motor control

## Decision: Field-Oriented Control (FOC) Algorithm Implementation
**Rationale**: FOC is the industry standard for PMSM control, providing maximum efficiency and smooth torque delivery. It requires Clarke/Park transforms, PID controllers for d/q axis currents, and space vector modulation.

**Alternatives considered**:
- Scalar control: Simpler but less efficient and less precise
- Direct Torque Control: Alternative but more complex and less mature for this application

## Decision: Eclipse ThreadX RTOS with Task Priorities
**Rationale**: ThreadX is a proven RTOS with excellent real-time performance characteristics suitable for motor control. It provides the necessary interrupt handling and task scheduling for meeting timing constraints while maintaining safety functions.

**Task Priorities**:
- Safety monitoring: Highest priority (interrupt level)
- Current control loop: High priority (10kHz)
- Speed/position control loops: Medium priority
- Communication: Low priority
- Status reporting: Lowest priority

**Alternatives considered**:
- FreeRTOS: Good alternative but ThreadX has better real-time guarantees
- Bare-metal: Used in many motor control applications but harder to manage multiple concurrent tasks
- RT-Thread: Less common in industrial motor control

## Decision: ADC Configuration for Current Sensing
**Rationale**: For 10kHz control loop with PMSM FOC, we need precise current measurements. Using dual-sampling ADCs with simultaneous sampling capability built into STM32G474xx allows for accurate phase current measurements without aliasing effects.

**Configuration**:
- ADC sampling rate: 100kHz minimum (10x control loop)
- Resolution: 12-bit or higher
- Simultaneous sampling for two phases
- Hardware triggers from timer

**Alternatives considered**:
- External ADC: Higher cost and complexity
- Software sampling: Cannot meet timing requirements

## Decision: PWM Configuration for Motor Drive
**Rationale**: The STM32G474xx has advanced timers with complementary outputs, dead-time insertion, and emergency stop capabilities specifically designed for motor control. Using these features ensures safe and efficient motor driving.

**Configuration**:
- PWM frequency: 20kHz carrier frequency (2x minimum)
- Complementary outputs with dead-time
- Emergency stop (BKIN) functionality
- Center-aligned modulation for better harmonic performance

**Alternatives considered**:
- Fixed frequency external PWM: Less flexible and higher cost
- Software PWM: Cannot meet timing requirements

## Decision: Encoder Interface for Feedback
**Rationale**: For position and speed control, we need precise feedback. The STM32G474xx has hardware support for quadrature encoder interfaces (QEI) which can provide direct position measurement and hardware-based speed calculation.

**Configuration**:
- Hardware QEI interface
- Filter for noise reduction
- Position counter with overflow handling
- Speed calculation using hardware timers

**Alternatives considered**:
- Software encoder counting: Less accurate and uses more CPU
- Hall sensors: Less precise than encoders
- Sensorless control: More complex and less accurate at low speeds

## Decision: Communication Interface (CAN/Serial)
**Rationale**: CAN provides robust communication suitable for industrial environments with built-in error detection. Serial (UART) provides easier integration with PC-based tools. Implementation will support both with protocol selection at compile time.

**Configuration**:
- CAN 2.0B support
- Baud rate: 1 Mbps for high-speed applications
- Serial: 115200 baud or higher as needed
- Protocol: CANopen or custom protocol with 11-bit IDs

**Alternatives considered**:
- Only CAN or only serial: Reduces flexibility
- Ethernet: Overkill for this application
- USB: Good for debugging but less suitable for industrial applications

## Decision: Safety and Protection Implementation
**Rationale**: Motor control systems must operate safely under all conditions. Multiple protection layers are needed to respond to faults within microseconds to prevent hardware damage.

**Protection mechanisms**:
- Overcurrent: Hardware comparator with immediate response
- Overvoltage: Software monitoring with configurable thresholds
- Overtemperature: Software monitoring with configurable thresholds
- Overspeed: Software monitoring
- Communication timeout: Software watchdog
- Emergency stop: Hardware interrupt

**Alternatives considered**:
- Software-only protection: May not respond fast enough
- Hardware-only protection: Less flexible and harder to configure

## Decision: MISRA C Compliance Approach
**Rationale**: MISRA C is an essential standard for safety-critical embedded systems. Using static analysis tools ensures compliance without extensive manual checking.

**Tools**:
- PC-lint Plus or similar static analysis tool
- Integration into build system
- Regular compliance checks

**Alternatives considered**:
- Manual compliance checking: Time-consuming and error-prone
- No compliance checking: Does not meet safety requirements

## Decision: Matlab/Simulink Integration for Algorithm Validation
**Rationale**: Developing motor control algorithms requires extensive simulation before hardware implementation. Matlab/Simulink provides proven models for PMSM simulation and algorithm validation.

**Process**:
- Develop control algorithms in Simulink
- Simulate with PMSM model
- Generate C code from Simulink model
- Integrate generated code with hand-written code
- Validate performance against simulation

**Alternatives considered**:
- Pure hardware development: Higher risk and longer development time
- Other simulation tools: Less proven for motor control applications