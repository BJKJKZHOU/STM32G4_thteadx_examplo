# Data Model: PMSM FOC Control System

## Entities

### Motor Control Parameters
**Description**: Configuration parameters specific to the PMSM being controlled

**Fields**:
- `pole_pairs` (uint8_t): Number of pole pairs in the motor
- `rated_speed` (float32): Maximum rated speed in RPM
- `rated_current` (float32): Maximum rated current in Amps
- `torque_constant` (float32): Motor torque constant (Nm/A)
- `flux_linkage` (float32): Rotor flux linkage (Wb)
- `stator_resistance` (float32): Stator resistance (Ohms)
- `d_axis_inductance` (float32): D-axis inductance (H)
- `q_axis_inductance` (float32): Q-axis inductance (H)
- `max_position_limit` (float32): Maximum position limit (degrees)
- `min_position_limit` (float32): Minimum position limit (degrees)
- `max_speed_limit` (float32): Maximum speed limit (RPM)
- `max_current_limit` (float32): Maximum current limit (Amps)

**Validation**:
- `pole_pairs` > 0
- `rated_speed` > 0
- `rated_current` > 0
- `torque_constant` > 0
- `flux_linkage` > 0
- `stator_resistance` > 0
- `d_axis_inductance` > 0
- `q_axis_inductance` > 0

### Motor State
**Description**: Current operational state of the motor

**Fields**:
- `position` (float32): Current rotor position (degrees)
- `speed` (float32): Current rotor speed (RPM)
- `current_d` (float32): D-axis current (Amps)
- `current_q` (float32): Q-axis current (Amps)
- `current_u` (float32): Phase U current (Amps)
- `current_v` (float32): Phase V current (Amps)
- `current_w` (float32): Phase W current (Amps)
- `voltage_bus` (float32): DC bus voltage (Volts)
- `temperature` (float32): Motor temperature (°C)
- `operational_mode` (enum): Current control mode (IDLE, STARTING, RUNNING, STOPPING, FAULT)
- `control_mode` (enum): Control mode (CURRENT, SPEED, POSITION, TORQUE)
- `timestamp` (uint32_t): Time of measurement (microseconds)

**Validation**:
- `position` within ±3600° (10 mechanical revolutions)
- `speed` within motor limits
- `current_d`, `current_q` within limits
- `voltage_bus` within safe operating range
- `temperature` within safe operating range

### Safety State
**Description**: Current safety status and fault conditions

**Fields**:
- `overcurrent_fault` (bool): Overcurrent condition detected
- `overvoltage_fault` (bool): Overvoltage condition detected
- `overtemperature_fault` (bool): Overtemperature condition detected
- `overspeed_fault` (bool): Overspeed condition detected
- `encoder_fault` (bool): Encoder feedback fault
- `communication_timeout` (bool): Communication timeout detected
- `emergency_stop` (bool): Emergency stop activated
- `fault_occurred` (bool): Any fault condition detected
- `last_fault_code` (uint16_t): Code of the last fault
- `fault_timestamp` (uint32_t): Time of last fault (microseconds)
- `reset_allowed` (bool): Whether reset is allowed after fault

**Validation**:
- At least one fault condition must be false at startup
- `last_fault_code` must be a valid fault code

### Control Configuration
**Description**: Control loop parameters for PID controllers and other control settings

**Fields**:
- `current_pid_kp` (float32): Current controller proportional gain
- `current_pid_ki` (float32): Current controller integral gain
- `current_pid_kd` (float32): Current controller derivative gain
- `speed_pid_kp` (float32): Speed controller proportional gain
- `speed_pid_ki` (float32): Speed controller integral gain
- `speed_pid_kd` (float32): Speed controller derivative gain
- `position_pid_kp` (float32): Position controller proportional gain
- `position_pid_ki` (float32): Position controller integral gain
- `position_pid_kd` (float32): Position controller derivative gain
- `current_limit` (float32): Maximum current limit in control
- `speed_ramp_up` (float32): Speed ramp up rate (RPM/s)
- `speed_ramp_down` (float32): Speed ramp down rate (RPM/s)
- `position_tolerance` (float32): Position tolerance for position control (degrees)

**Validation**:
- PID gains must be positive
- Current limit must be within hardware limits
- Ramp rates must be positive

### Communication Data
**Description**: Commands from host and status data to host

**Fields**:
- `command_type` (enum): Type of command (START, STOP, SET_SPEED, SET_POSITION, SET_CURRENT, GET_STATUS)
- `command_value` (float32): Value associated with command
- `command_id` (uint16_t): Unique command identifier
- `status_flags` (uint32_t): Status flags bitmask
- `host_connected` (bool): Whether host is connected
- `last_command_timestamp` (uint32_t): Time of last command (milliseconds)
- `command_acknowledged` (bool): Whether last command was acknowledged

**Validation**:
- Command values must be within valid ranges
- Command IDs must be unique within a reasonable timeframe

## State Transitions

### Motor Operational States
```
IDLE → STARTING → RUNNING → STOPPING → IDLE
IDLE → FAULT
STARTING → FAULT
RUNNING → FAULT
RUNNING → STOPPING
STOPPING → IDLE
STOPPING → FAULT
```

**Transitions**:
- From IDLE: START command begins transition to STARTING
- From STARTING: Speed reaches target transitions to RUNNING
- From RUNNING: STOP command begins transition to STOPPING
- From RUNNING: Fault condition transitions to FAULT
- From STOPPING: Speed reaches zero transitions to IDLE
- From any state: Emergency stop transitions to FAULT immediately

### Safety State Transitions
```
SAFE → FAULT_DETECTED → FAULT_ACTIVE → RESETTING → SAFE
```

**Transitions**:
- From SAFE: Fault condition detected transitions to FAULT_DETECTED
- From FAULT_DETECTED: Protection action taken transitions to FAULT_ACTIVE
- From FAULT_ACTIVE: Reset command (if allowed) transitions to RESETTING
- From RESETTING: System verifies safe state transitions to SAFE