# Data Model: PMSM FOC Control System    Data Model: PMSM FOC Control System

## Entities    实体

### Motor Control Parameters    电机控制参数
**Description**: Configuration parameters specific to the PMSM being controlled
**Fields**:
- `pole_pairs` (uint8_t): Number of pole pairs in the motor     电机中的极对数
- `rated_speed` (float32): Maximum rated speed in RPM           最大额定转速（RPM）
- `rated_current` (float32): Maximum rated current in Amps      最大额定电流（安培）
- `torque_constant` (float32): Motor torque constant (Nm/A)     电机转矩常数（Nm/A）
- `flux_linkage` (float32): Rotor flux linkage (Wb)             转子磁链（韦伯）
- `stator_resistance` (float32): Stator resistance (Ohms)       定子电阻（欧姆）
- `d_axis_inductance` (float32): D-axis inductance (H)          D轴电感（亨利）
- `q_axis_inductance` (float32): Q-axis inductance (H)          Q轴电感（亨利）
- `max_position_limit` (float32): Maximum position limit        (degrees)    最大位置限制（度）
- `min_position_limit` (float32): Minimum position limit        (degrees)    最小位置限制（度）
- `max_speed_limit` (float32): Maximum speed limit (RPM)        最大速度限制（RPM）
- `max_current_limit` (float32): Maximum current limit (Amps)   最大电流限制（安培）

**Validation**:    验证
- `pole_pairs` > 0
- `rated_speed` > 0
- `rated_current` > 0
- `torque_constant` > 0
- `flux_linkage` > 0
- `stator_resistance` > 0
- `d_axis_inductance` > 0
- `q_axis_inductance` > 0

### Motor State    电机状态
**Description**: Current operational state of the motor
**Fields**:
- `position` (float32): Current rotor position (degrees)    当前转子位置（度）
- `speed` (float32): Current rotor speed (RPM)              当前转子速度（RPM）
- `current_d` (float32): D-axis current (Amps)              D轴电流（安培）
- `current_q` (float32): Q-axis current (Amps)              Q轴电流（安培）
- `current_u` (float32): Phase U current (Amps)             U相电流（安培）
- `current_v` (float32): Phase V current (Amps)             V相电流（安培）
- `current_w` (float32): Phase W current (Amps)             W相电流（安培）
- `voltage_bus` (float32): DC bus voltage (Volts)           DC母线电压（伏特）
- `temperature` (float32): Motor temperature (°C)       电机温度（摄氏度）
- `operational_mode` (enum): Current control mode (IDLE, STARTING, RUNNING, STOPPING, FAULT)    当前控制模式（空闲、启动、运行、停止、故障）
- `control_mode` (enum): Control mode (CURRENT, SPEED, POSITION, TORQUE)    控制模式（电流、速度、位置、转矩）
- `timestamp` (uint32_t): Time of measurement (microseconds)    测量时间（微秒）

**Validation**:    验证
- `position` within ±3600° (10 mechanical revolutions)
- `speed` within motor limits
- `current_d`, `current_q` within limits
- `voltage_bus` within safe operating range
- `temperature` within safe operating range

### Safety State    安全状态
**Description**: Current safety status and fault conditions
**Fields**:
- `overcurrent_fault` (bool): Overcurrent condition detected    检测到过流状态
- `overvoltage_fault` (bool): Overvoltage condition detected    检测到过压状态
- `overtemperature_fault` (bool): Overtemperature condition detected    检测到过温状态
- `overspeed_fault` (bool): Overspeed condition detected    检测到超速状态
- `encoder_fault` (bool): Encoder feedback fault    编码器反馈故障
- `communication_timeout` (bool): Communication timeout detected    检测到通信超时
- `emergency_stop` (bool): Emergency stop activated    紧急停止激活
- `fault_occurred` (bool): Any fault condition detected    检测到任何故障状态
- `last_fault_code` (uint16_t): Code of the last fault    最后故障代码
- `fault_timestamp` (uint32_t): Time of last fault (microseconds)    最后故障时间（微秒）
- `reset_allowed` (bool): Whether reset is allowed after fault    故障后是否允许复位

**Validation**:    验证
- At least one fault condition must be false at startup
- `last_fault_code` must be a valid fault code

### Control Configuration    控制配置
**Description**: Control loop parameters for PID controllers and other control settings
**Fields**:
- `current_pid_kp` (float32): Current controller proportional gain    电流控制器比例增益
- `current_pid_ki` (float32): Current controller integral gain    电流控制器积分增益
- `current_pid_kd` (float32): Current controller derivative gain    电流控制器微分增益
- `speed_pid_kp` (float32): Speed controller proportional gain    速度控制器比例增益
- `speed_pid_ki` (float32): Speed controller integral gain    速度控制器积分增益
- `speed_pid_kd` (float32): Speed controller derivative gain    速度控制器微分增益
- `position_pid_kp` (float32): Position controller proportional gain    位置控制器比例增益
- `position_pid_ki` (float32): Position controller integral gain    位置控制器积分增益
- `position_pid_kd` (float32): Position controller derivative gain    位置控制器微分增益
- `current_limit` (float32): Maximum current limit in control    控制中的最大电流限制
- `speed_ramp_up` (float32): Speed ramp up rate (RPM/s)    速度上升速率（RPM/秒）
- `speed_ramp_down` (float32): Speed ramp down rate (RPM/s)    速度下降速率（RPM/秒）
- `position_tolerance` (float32): Position tolerance for position control (degrees)    位置控制的位置容差（度）

**Validation**:    验证
- PID gains must be positive
- Current limit must be within hardware limits
- Ramp rates must be positive

### Communication Data    通信数据
**Description**: Commands from host and status data to host
**Fields**:
- `command_type` (enum): Type of command (START, STOP, SET_SPEED, SET_POSITION, SET_CURRENT, GET_STATUS)    命令类型（启动、停止、设置速度、设置位置、设置电流、获取状态）
- `command_value` (float32): Value associated with command    与命令关联的值
- `command_id` (uint16_t): Unique command identifier    唯一命令标识符
- `status_flags` (uint32_t): Status flags bitmask    状态标志位掩码
- `host_connected` (bool): Whether host is connected    主机是否连接
- `last_command_timestamp` (uint32_t): Time of last command (milliseconds)    最后命令时间（毫秒）
- `command_acknowledged` (bool): Whether last command was acknowledged    最后命令是否被确认

**Validation**:    验证
- Command values must be within valid ranges
- Command IDs must be unique within a reasonable timeframe

## State Transitions    状态转换

### Motor Operational States    电机运行状态
```
IDLE → STARTING → RUNNING → STOPPING → IDLE
IDLE → FAULT
STARTING → FAULT
RUNNING → FAULT
RUNNING → STOPPING
STOPPING → IDLE
STOPPING → FAULT
```

**Transitions**:    转换
- From IDLE: START command begins transition to STARTING    从空闲状态：START命令开始转换到启动状态
- From STARTING: Speed reaches target transitions to RUNNING    从启动状态：速度达到目标转换到运行状态
- From RUNNING: STOP command begins transition to STOPPING    从运行状态：STOP命令开始转换到停止状态
- From RUNNING: Fault condition transitions to FAULT    从运行状态：故障状态转换到故障状态
- From STOPPING: Speed reaches zero transitions to IDLE    从停止状态：速度达到零转换到空闲状态
- From any state: Emergency stop transitions to FAULT immediately    从任何状态：紧急停止立即转换到故障状态

### Safety State Transitions    安全状态转换
**Transitions**:    转换
- From SAFE: Fault condition detected transitions to FAULT_DETECTED    从安全状态：检测到故障状态转换到故障检测状态
- From FAULT_DETECTED: Protection action taken transitions to FAULT_ACTIVE    从故障检测状态：采取保护动作转换到故障激活状态
- From FAULT_ACTIVE: Reset command (if allowed) transitions to RESETTING    从故障激活状态：复位命令（如果允许）转换到复位状态
- From RESETTING: System verifies safe state transitions to SAFE    从复位状态：系统验证安全状态转换到安全状态