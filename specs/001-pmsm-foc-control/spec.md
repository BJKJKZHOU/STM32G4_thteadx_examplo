# Feature Specification: PMSM FOC Control System    功能规格说明：永磁同步电机FOC控制系统

**Feature Branch**: `001-pmsm-foc-control`  
**Created**: 2025-10-17  
**Status**: Draft  
**Input**: User description: "开发一个基于STM32G474的永磁同步电机（PMSM）磁场定向控制（FOC）系统。该系统应具备以下功能： 电机启动和停止控制 速度闭环控制 电流闭环控制（FOC） 位置闭环控制 过流、过压、过热保护 支持编码器反馈 支持CAN或串口通信接收速度指令 实时监控电机状态（电流、速度、位置，通过通信模块连接上位机） 使用STM32CubeMX生成初始化代码，使用HAL库 代码符合MISRA C规范 还有其他建议可以补充"
**功能分支**：`001-pmsm-foc-control`  
**创建日期**：2025-10-17  
**状态**：草稿  
**输入**：用户描述："开发一个基于STM32G474的永磁同步电机（PMSM）磁场定向控制（FOC）系统。该系统应具备以下功能： 电机启动和停止控制 速度闭环控制 电流闭环控制（FOC） 位置闭环控制 过流、过压、过热保护 支持编码器反馈 支持CAN或串口通信接收速度指令 实时监控电机状态（电流、速度、位置，通过通信模块连接上位机） 使用STM32CubeMX生成初始化代码，使用HAL库 代码符合MISRA C规范 还有其他建议可以补充"

## User Scenarios & Testing *(mandatory)*    用户场景与测试*(必填)*

### User Story 1 - PMSM FOC Basic Control (Priority: P1)    用户故事1 - 永磁同步电机FOC基本控制（优先级：P1）

An engineer controls a PMSM motor using the FOC system, starting and stopping the motor, setting speed parameters, and monitoring basic status in real-time. The system provides basic protection against overcurrent, overvoltage, and overtemperature.
工程师使用FOC系统控制永磁同步电机，启动和停止电机，设置速度参数，并实时监控基本状态。系统提供基本的过流、过压和过温保护。

**Why this priority**: This is the most critical functionality as it establishes the core motor control capability that all other features depend on. Without basic start/stop and speed control, the system has no value.
**为什么这个优先级**：这是最关键的功能，因为它建立了所有其他功能依赖的核心电机控制能力。没有基本的启动/停止和速度控制，系统就没有价值。

**Independent Test**: Can be fully tested by connecting a PMSM motor, issuing start/stop commands and speed setpoints, and verifying the motor responds appropriately with safety protection mechanisms working within timing constraints.
**独立测试**：可以通过连接永磁同步电机，发出启动/停止命令和速度设定点，并验证电机在安全保护机制在时序约束内工作的情况下适当响应。

**Acceptance Scenarios**:
**验收场景**：

1. **Given** motor is stopped and system is ready, **When** user sends start command with speed setpoint, **Then** motor starts and reaches requested speed within timing constraints
2. **Given** motor is in normal operation, **When** overcurrent condition is detected, **Then** system fails safely by stopping motor and protecting hardware
3. **Given** motor is running at requested speed, **When** user sends stop command, **Then** motor stops safely within expected time
4. **Given** motor is running, **When** user changes speed setpoint, **Then** motor reaches new speed smoothly within 500ms
1. **给定**电机已停止且系统准备就绪，**当**用户发送带速度设定点的启动命令，**那么**电机启动并在时序约束内达到请求的速度
2. **给定**电机处于正常运行状态，**当**检测到过流情况，**那么**系统通过停止电机和保护硬件安全地失效
3. **给定**电机以请求的速度运行，**当**用户发送停止命令，**那么**电机在预期时间内安全停止
4. **给定**电机正在运行，**当**用户更改速度设定点，**那么**电机在500ms内平稳达到新速度

---

### User Story 2 - Advanced Position and Current Control (Priority: P2)    用户故事2 - 高级位置和电流控制（优先级：P2）

An engineer configures and uses position and current control in addition to speed control for more precise motor operation. The system implements full FOC algorithm for optimal current control.
工程师配置和使用位置和电流控制，除了速度控制外，用于更精确的电机操作。系统实现完整的FOC算法以实现最佳电流控制。

**Why this priority**: This adds precision control capabilities that are essential for many motor control applications, building on the core functionality in User Story 1.
**为什么这个优先级**：这增加了许多电机控制应用所需的精密控制能力，建立在用户故事1的核心功能之上。

**Independent Test**: Can be tested by configuring position control mode, setting position targets, and verifying the motor accurately reaches those positions while maintaining proper current control and safety protection.
**独立测试**：可以通过配置位置控制模式，设置位置目标，并验证电机在保持适当电流控制和安全保护的情况下准确到达这些位置。

**Acceptance Scenarios**:
**验收场景**：

1. **Given** motor is stopped, **When** user sets position control mode and target position, **Then** motor moves to target position with precision within 1 degree
2. **Given** motor is in current control mode, **When** FOC algorithm is active, **Then** d/q axis currents are controlled within ±2% of target values
3. **Given** motor is operating under position control, **When** position error exceeds safety threshold, **Then** system transitions to safe state
1. **给定**电机已停止，**当**用户设置位置控制模式和目标位置，**那么**电机以1度以内的精度移动到目标位置
2. **给定**电机处于电流控制模式，**当**FOC算法激活，**那么**d/q轴电流控制在目标值的±2%以内
3. **给定**电机在位置控制下运行，**当**位置误差超过安全阈值，**那么**系统转换到安全状态

---

### User Story 3 - Communication and Monitoring (Priority: P3)    用户故事3 - 通信与监控（优先级：P3）

A system operator monitors motor status remotely via CAN or serial communication and sends speed commands from a host computer. The system continuously reports motor state (current, speed, position) to the host.
系统操作员通过CAN或串行通信远程监控电机状态，并从主机发送速度命令。系统持续向主机报告电机状态（电流、速度、位置）。

**Why this priority**: This provides the interface for real-world applications where remote monitoring and control is needed, but is less critical than core motor control functionality.
**为什么这个优先级**：这为需要远程监控和控制的实际应用提供了接口，但比核心电机控制功能不那么关键。

**Independent Test**: Can be tested by connecting host computer via CAN or serial, sending commands, and verifying bidirectional communication with real-time status updates while maintaining core motor control and safety functions.
**独立测试**：可以通过CAN或串行连接主机计算机，发送命令，并验证在保持核心电机控制和安全功能的同时进行双向通信和实时状态更新。

**Acceptance Scenarios**:
**验收场景**：

1. **Given** host computer is connected via CAN, **When** host sends speed command, **Then** motor responds to command and reports status back to host
2. **Given** host is receiving status updates, **When** motor state changes, **Then** updated current, speed, and position data is sent to host within 100ms
3. **Given** communication link is active, **When** communication failure occurs, **Then** system maintains safe operation independent of host
1. **给定**主机计算机通过CAN连接，**当**主机发送速度命令，**那么**电机响应命令并向主机报告状态
2. **给定**主机正在接收状态更新，**当**电机状态改变，**那么**更新的电流、速度和位置数据在100ms内发送到主机
3. **给定**通信链路处于活动状态，**当**发生通信故障，**那么**系统保持独立于主机的安全操作

---

### Edge Cases    边界情况

- What happens when encoder feedback fails or is disconnected?
- How does system handle sudden load changes or motor stall conditions?
- What is the response during power supply fluctuations?
- How does the system behave during temperature extremes?
- What happens when communication timeout occurs during command execution?
- 当编码器反馈失败或断开连接时会发生什么？
- 系统如何处理突然的负载变化或电机失速情况？
- 在电源波动期间响应是什么？
- 系统在极端温度下如何表现？
- 当命令执行期间发生通信超时时会发生什么？

## Requirements *(mandatory)*    需求*(必填)*

### Functional Requirements    功能需求

- **FR-001**: System MUST implement PMSM FOC algorithm with current, speed, and position control capabilities
- **FR-002**: System MUST provide motor start and stop control with smooth acceleration/deceleration profiles
- **FR-003**: System MUST process encoder feedback for position and speed information with update rate of at least 10kHz
- **FR-004**: System MUST support CAN or serial communication for receiving speed commands from host
- **FR-005**: System MUST continuously monitor motor status (current, speed, position) and report to host
- **FR-006**: System MUST detect and protect against overcurrent, overvoltage, and overtemperature conditions
- **FR-007**: System MUST execute FOC control algorithm within specified timing constraints (control loop at 10kHz or faster)
- **FR-008**: System MUST fail safely by stopping motor and protecting hardware when faults are detected
- **FR-009**: System MUST operate within STM32G474xx hardware constraints (memory, processing power)
- **FR-010**: System MUST store and allow configuration of motor parameters (pole pairs, inductance, resistance)
- **FR-001**：系统必须实现具有电流、速度和位置控制能力的永磁同步电机FOC算法
- **FR-002**：系统必须提供具有平滑加减速曲线的电机启动和停止控制
- **FR-003**：系统必须以至少10kHz的更新率处理编码器反馈以获取位置和速度信息
- **FR-004**：系统必须支持CAN或串行通信以接收来自主机的速度命令
- **FR-005**：系统必须持续监控电机状态（电流、速度、位置）并向主机报告
- **FR-006**：系统必须检测并保护过流、过压和过温情况
- **FR-007**：系统必须在指定的时序约束内执行FOC控制算法（控制环为10kHz或更快）
- **FR-008**：系统必须在检测到故障时通过停止电机和保护硬件安全地失效
- **FR-009**：系统必须在STM32G474xx硬件约束（内存、处理能力）内运行
- **FR-010**：系统必须存储并允许配置电机参数（极对数、电感、电阻）

*Example of marking unclear requirements:*
*标记不明确需求的示例：*

- **FR-011**: Communication protocol specifics - Use standard CANopen or custom protocol with 11-bit message IDs for motor commands and status reporting
- **FR-012**: Position accuracy requirements - Target position accuracy of ±0.5 degrees for position control mode
- **FR-011**：通信协议细节 - 使用标准CANopen或具有11位消息ID的自定义协议进行电机命令和状态报告
- **FR-012**：位置精度要求 - 位置控制模式的目标位置精度为±0.5度

### Key Entities    关键实体

- **Motor Control Parameters**: Motor-specific parameters like pole pairs, inductance, resistance, current limits, speed limits, position limits
- **Safety State**: Current safety status including fault conditions, protective actions taken, and safe state status
- **Motor State**: Current motor status including position, speed, current (d/q axis), temperature, and operational mode
- **Communication Data**: Commands received from host and status data transmitted to host via CAN or serial
- **Control Configuration**: Settings for current, speed, and position control loops including PID parameters
- **电机控制参数**：电机特定参数，如极对数、电感、电阻、电流限制、速度限制、位置限制
- **安全状态**：当前安全状态，包括故障情况、采取的保护措施和安全状态状态
- **电机状态**：当前电机状态，包括位置、速度、电流（d/q轴）、温度和操作模式
- **通信数据**：从主机接收的命令和通过CAN或串行传输到主机的状态数据
- **控制配置**：电流、速度和位置控制环的设置，包括PID参数

## Success Criteria *(mandatory)*    成功标准*(必填)*

### Measurable Outcomes    可衡量的结果

- **SC-001**: Motor starts and stops on command with 99% success rate within 1 second
- **SC-002**: Speed control achieves target speed within 5% accuracy for speeds between 10% and 100% of rated speed
- **SC-003**: Position control achieves target position within 1 degree accuracy when in position control mode
- **SC-004**: System responds to overcurrent, overvoltage, and overtemperature conditions within 100 microseconds to prevent damage
- **SC-005**: Control loops execute at minimum 10kHz frequency with timing jitter less than 5 microseconds
- **SC-006**: System utilizes less than 80% of available STM32G474xx RAM and Flash memory
- **SC-007**: Communication (CAN or serial) maintains 95% message integrity during normal operation
- **SC-008**: All safety mechanisms pass validation testing with 100% success rate
- **SC-009**: Position and speed can be controlled independently with cross-coupling effects less than 2%
- **SC-010**: System passes MISRA C compliance checks with zero violations
- **SC-001**：电机在1秒内按命令启动和停止，成功率为99%
- **SC-002**：速度控制在额定速度的10%到100%之间达到目标速度的5%精度以内
- **SC-003**：位置控制在位置控制模式下达到1度以内的目标位置精度
- **SC-004**：系统在100微秒内响应过流、过压和过温情况以防止损坏
- **SC-005**：控制环以最低10kHz频率执行，时序抖动小于5微秒
- **SC-006**：系统使用少于80%的可用STM32G474xx RAM和Flash内存
- **SC-007**：通信（CAN或串行）在正常操作期间保持95%的消息完整性
- **SC-008**：所有安全机制通过验证测试，成功率为100%
- **SC-009**：位置和速度可以独立控制，交叉耦合效应小于2%
- **SC-010**：系统通过MISRA C合规性检查，零违规