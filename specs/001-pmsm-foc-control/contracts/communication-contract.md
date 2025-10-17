# Communication Contract: PMSM FOC Control System

## Overview

This document defines the communication interfaces for the PMSM FOC Control System, including both serial and CAN communication protocols.

## Serial Communication Protocol

### Physical Layer
- Interface: USART/UART
- Baud Rate: 115200 (default, configurable up to 921600)
- Data Bits: 8
- Stop Bits: 1
- Parity: None
- Flow Control: None (default)

### Message Format
- Command format: `[COMMAND] [PARAMETER]\n`
- Response format: `[STATUS] [DATA]\n`
- Example: `SPEED 1000\n` sets speed to 1000 RPM

### Commands

#### Motor Control Commands
- `START` - Start motor operation
  - Request: `START\n`
  - Response: `OK\n` on success, `ERROR [CODE]\n` on failure

- `STOP` - Stop motor operation
  - Request: `STOP\n`
  - Response: `OK\n` on success, `ERROR [CODE]\n` on failure

- `SPEED [value]` - Set speed target (RPM)
  - Request: `SPEED [0-9]+\n`
  - Response: `OK\n` on success, `ERROR [CODE]\n` on failure

- `POS [value]` - Set position target (degrees)
  - Request: `POS [-+]?[0-9]*\.?[0-9]+\n`
  - Response: `OK\n` on success, `ERROR [CODE]\n` on failure

- `CURRENT [d_value] [q_value]` - Set d/q axis current targets (Amps)
  - Request: `CURRENT [-+]?[0-9]*\.?[0-9]+ [-+]?[0-9]*\.?[0-9]+\n`
  - Response: `OK\n` on success, `ERROR [CODE]\n` on failure

#### Status and Query Commands
- `STATUS` - Get current motor status
  - Request: `STATUS\n`
  - Response: `POS [degrees] SPD [rpm] CUR_D [amps] CUR_Q [amps] TEMP [celsius] STATE [state] VOLT [volts]\n`

- `PARAMS` - Get motor parameters
  - Request: `PARAMS\n`
  - Response: `PP [pole_pairs] RS [resistance] LD [d_inductance] LQ [q_inductance] TC [torque_constant]\n`

- `FAULTS` - Get fault status
  - Request: `FAULTS\n`
  - Response: `OC [bool] OV [bool] OT [bool] OS [bool] EC [bool] CT [bool] ES [bool]\n`

#### Configuration Commands
- `SET_PP [value]` - Set pole pairs
  - Request: `SET_PP [1-255]\n`
  - Response: `OK\n` on success, `ERROR [CODE]\n` on failure

- `SET_SPD_LIM [value]` - Set speed limit (RPM)
  - Request: `SET_SPD_LIM [0-9]+\n`
  - Response: `OK\n` on success, `ERROR [CODE]\n` on failure

## CAN Communication Protocol

### Physical Layer
- Interface: CAN 2.0B
- Baud Rate: 1 Mbps (default, configurable)
- Frame Type: Standard (11-bit) and Extended (29-bit) frames

### Frame Format
```
ID: 11-bit or 29-bit identifier
DLC: 0-8 bytes of data
Data: Little-endian format
```

### Message IDs (11-bit standard)
- `0x100` - Command frame (from host to motor controller)
- `0x200` - Status frame (from motor controller to host)
- `0x300` - Parameter frame (bidirectional)
- `0x400` - Fault status frame (from motor controller to host)
- `0x500` - Configuration frame (bidirectional)

### Command Frame (ID: 0x100)
**Purpose**: Send commands to motor controller

**Data Format**:
```
Byte 0: Command Type (enum)
Byte 1-2: Command Value (Little Endian, int16_t or uint16_t)
Byte 3-4: Additional Parameter (Little Endian)
Byte 5-7: Reserved (set to 0x00)
```

**Command Types**:
- `0x00`: No operation
- `0x01`: Start motor
- `0x02`: Stop motor
- `0x03`: Set speed (value in RPM)
- `0x04`: Set position (value in 0.01 degree increments)
- `0x05`: Set current (byte 1-2: d-axis, byte 3-4: q-axis in 0.01A increments)
- `0x06`: Get status (value ignored)
- `0x07`: Clear faults

### Status Frame (ID: 0x200)
**Purpose**: Report current motor status to host

**Data Format**:
```
Byte 0-1: Position (0.01 degree increments, Little Endian)
Byte 2-3: Speed (RPM, Little Endian, signed)
Byte 4-5: D-axis current (0.01A increments, Little Endian, signed)
Byte 6-7: Q-axis current (0.01A increments, Little Endian, signed)
```

### Extended Status Frame (ID: 0x201)
**Purpose**: Report extended motor status to host

**Data Format**:
```
Byte 0-1: DC Bus Voltage (0.01V increments, Little Endian)
Byte 2-3: Motor Temperature (0.01°C increments, Little Endian, signed)
Byte 4: Operational State (enum)
Byte 5: Control Mode (enum)
Byte 6-7: Reserved
```

**Operational States**:
- `0x00`: IDLE
- `0x01`: STARTING
- `0x02`: RUNNING
- `0x03`: STOPPING
- `0x04`: FAULT

**Control Modes**:
- `0x00`: CURRENT_CONTROL
- `0x01`: SPEED_CONTROL
- `0x02`: POSITION_CONTROL

### Fault Status Frame (ID: 0x400)
**Purpose**: Report fault conditions to host

**Data Format**:
```
Byte 0: Fault Flags (bitmask)
  Bit 0: Overcurrent fault
  Bit 1: Overvoltage fault
  Bit 2: Overtemperature fault
  Bit 3: Overspeed fault
  Bit 4: Encoder fault
  Bit 5: Communication timeout
  Bit 6: Emergency stop
  Bit 7: Reserved
Byte 1-2: Fault Code (Little Endian)
Byte 3-7: Reserved
```

### Configuration Frame (ID: 0x500)
**Purpose**: Configure motor parameters

**Data Format**:
```
Byte 0: Parameter Type (enum)
Byte 1-2: Parameter Value (Little Endian)
Byte 3-7: Additional data based on parameter type
```

**Parameter Types**:
- `0x00`: Pole pairs (value: 1-255)
- `0x01`: Rated current (value: 0.01A increments)
- `0x02`: Rated speed (value: RPM)
- `0x03`: Current limit (value: 0.01A increments)
- `0x04`: Speed limit (value: RPM)
- `0x05`: Torque constant (value: 0.0001 Nm/A increments)
- `0x06`: Stator resistance (value: 0.001 ohm increments)
- `0x07`: D-axis inductance (value: 0.000001 H increments)
- `0x08`: Q-axis inductance (value: 0.000001 H increments)

## Timing Requirements

### Control Loop Timing
- Main control loop: 10kHz (every 100 microseconds)
- ADC sampling: 100kHz (every 10 microseconds)
- Status reporting: Up to 1kHz when requested via communication

### Communication Timing
- Serial interface should respond to commands within 5ms
- CAN interface should send status frames at 100Hz minimum (10ms interval)
- Fault conditions must be reported within 1ms of detection

## Error Handling

### Error Codes
- `0x0001`: Invalid command
- `0x0002`: Parameter out of range
- `0x0003`: Motor not in correct state for command
- `0x0004`: Hardware fault detected
- `0x0005`: Communication timeout
- `0x0006`: Safety interlock active

### Safety Responses
- Any fault condition triggers immediate transition to safe state
- Motor stops via controlled deceleration unless emergency stop
- Communication interfaces remain active to report fault status
- Fault must be cleared before normal operation can resume