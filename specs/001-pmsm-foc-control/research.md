# Research: PMSM FOC Control System    研究：永磁同步电机FOC控制系统

## Decision: Use STM32G474xx with HAL/LL libraries    决策：使用STM32G474xx与HAL/LL库
**Rationale**: The STM32G474xx is specifically designed for real-time motor control applications with integrated peripherals like FPU, advanced timers, and ADCs optimized for motor control. HAL/LL libraries provide the right balance between hardware abstraction and performance for meeting timing requirements.  
**基本原理**：STM32G474xx系列专为实时电机控制应用设计，集成了FPU、高级定时器和针对电机控制优化的ADC等外设。HAL/LL库在硬件抽象和性能之间提供了恰当的平衡，能够满足时序要求。
**Alternatives considered**:
- STM32F3xx: Lower cost but less processing power and memory
- STM32H7xx: More powerful but overkill for this application and higher cost
- Other manufacturers: STMicroelectronics ecosystem provides better support for motor control
**考虑的替代方案**：
- STM32F3xx：成本较低但处理能力和内存较少
- STM32H7xx：性能更强但对此应用过于强大且成本更高
- 其他制造商：STMicroelectronics生态系统为电机控制提供更好的支持

## Decision: Field-Oriented Control (FOC) Algorithm Implementation    决策：磁场定向控制（FOC）算法实现
**Rationale**: FOC is the industry standard for PMSM control, providing maximum efficiency and smooth torque delivery. It requires Clarke/Park transforms, PID controllers for d/q axis currents, and space vector modulation.  
**基本原理**：FOC是永磁同步电机控制的行业标准，提供最高效率和平滑的扭矩输出。它需要克拉克/帕克变换、d/q轴电流的PID控制器以及空间矢量调制。
 
**Alternatives considered**:
- Scalar control: Simpler but less efficient and less precise
- Direct Torque Control: Alternative but more complex and less mature for this application
**考虑的替代方案**：
- 标量控制：更简单但效率较低且精度较差
- 直接扭矩控制：替代方案但对此应用更复杂且不够成熟

## Decision: Eclipse ThreadX RTOS with Task Priorities    决策：使用Eclipse ThreadX RTOS与任务优先级
**Rationale**: ThreadX is a proven RTOS with excellent real-time performance characteristics suitable for motor control. It provides the necessary interrupt handling and task scheduling for meeting timing constraints while maintaining safety functions.  
**基本原理**：ThreadX是一个成熟的实时操作系统，具有出色的实时性能特性，适用于电机控制。它提供必要的中断处理和任务调度功能，能够满足时序约束同时维持安全功能。

**Task Priorities**:
- Safety monitoring: Highest priority (interrupt level)  
- Current control loop: High priority (20kHz)
- Speed/position control loops: Medium priority
- Communication: Low priority
- Status reporting: Lowest priority  
**任务优先级**：
- 安全监控：最高优先级（中断级别）
- 电流控制环：高优先级（20kHz）
- 速度/位置控制环：中等优先级
- 通信：低优先级
- 状态报告：最低优先级

**Alternatives considered**:
- FreeRTOS: Good alternative but ThreadX has better real-time guarantees
- Bare-metal: Used in many motor control applications but harder to manage multiple concurrent tasks
- RT-Thread: Less common in industrial motor control
**考虑的替代方案**：
- FreeRTOS：良好的替代方案但ThreadX具有更好的实时保证
- 裸机：在许多电机控制应用中使用但更难管理多个并发任务
- RT-Thread：在工业电机控制中较少见

## Decision: ADC Configuration for Current Sensing    决策：电流检测的ADC配置
**Rationale**: For 10kHz control loop with PMSM FOC, we need precise current measurements. Using dual-sampling ADCs with simultaneous sampling capability built into STM32G474xx allows for accurate phase current measurements without aliasing effects.
**基本原理**：对于10kHz的永磁同步电机FOC控制环，我们需要精确的电流测量。STM32G474xx内置的双采样ADC具有同步采样能力，可以实现准确的相电流测量而无混叠效应。
**Configuration**:
- ADC sampling rate: 200kHz minimum (10x control loop)
- Resolution: 12-bit or higher
- Simultaneous sampling for two phases
- Hardware triggers from timer
**配置**：
- ADC采样率：最低200kHz（控制环的10倍）
- 分辨率：12位或更高
- 两相同时采样
- 来自定时器的硬件触发

**Alternatives considered**:
- External ADC: Higher cost and complexity
- Software sampling: Cannot meet timing requirements
**考虑的替代方案**：
- 外部ADC：成本更高且更复杂
- 软件采样：无法满足时序要求

## Decision: PWM Configuration for Motor Drive    决策：电机驱动的PWM配置
**Rationale**: The STM32G474xx has advanced timers with complementary outputs, dead-time insertion, and emergency stop capabilities specifically designed for motor control. Using these features ensures safe and efficient motor driving.
**基本原理**：STM32G474xx具有高级定时器，带有互补输出、死区插入和紧急停止功能，专为电机控制设计。使用这些功能确保安全高效的电机驱动。
**Configuration**:
- PWM frequency: 20kHz carrier frequency (2x minimum)
- Complementary outputs with dead-time
- Emergency stop (BKIN) functionality
- Center-aligned modulation for better harmonic performance
**配置**：
- PWM频率：20kHz载波频率（最低2倍）
- 带死区的互补输出
- 紧急停止（BKIN）功能
- 中心对齐调制以获得更好的谐波性能

**Alternatives considered**:
- Fixed frequency external PWM: Less flexible and higher cost
- Software PWM: Cannot meet timing requirements
**考虑的替代方案**：
- 固定频率外部PWM：灵活性较差且成本更高
- 软件PWM：无法满足时序要求

## Decision: Encoder Interface for Feedback    决策：用于反馈的编码器接口
**Rationale**: For position and speed control, we need precise feedback. The STM32G474xx has hardware support for quadrature encoder interfaces (QEI) which can provide direct position measurement and hardware-based speed calculation.
**基本原理**：对于位置和速度控制，我们需要精确的反馈。STM32G474xx具有正交编码器接口（QEI）的硬件支持，可以提供直接的位置测量和基于硬件的速度计算。
**Configuration**:
- Hardware QEI interface
- Filter for noise reduction
- Position counter with overflow handling
- Speed calculation using hardware timers
**配置**：
- 硬件QEI接口
- 用于降噪的滤波器
- 带溢出处理的位置计数器
- 使用硬件定时器的速度计算

**Alternatives considered**:
- Software encoder counting: Less accurate and uses more CPU
- Hall sensors: Less precise than encoders
- Sensorless control: More complex and less accurate at low speeds
**考虑的替代方案**：
- 软件编码器计数：精度较低且使用更多CPU
- 霍尔传感器：比编码器精度低
- 无传感器控制：更复杂且在低速时精度较低

## Decision: Communication Interface (CAN/Serial)    决策：通信接口（CAN/串行）
**Rationale**: CAN provides robust communication suitable for industrial environments with built-in error detection. Serial (UART) provides easier integration with PC-based tools. Implementation will support both with protocol selection at compile time.
**基本原理**：CAN提供适用于工业环境的鲁棒通信，具有内置错误检测功能。串行（UART）提供与基于PC的工具更轻松的集成。实现将支持两者，并在编译时选择协议。
**Configuration**:
- CAN 2.0B support
- Baud rate: 1 Mbps for high-speed applications
- Serial: 115200 baud or higher as needed
- Protocol: CANopen or custom protocol with 11-bit IDs
**配置**：
- CAN 2.0B支持
- 波特率：高速应用为1 Mbps
- 串行：根据需要115200波特或更高
- 协议：CANopen或具有11位ID的自定义协议

**Alternatives considered**:
- Only CAN or only serial: Reduces flexibility
- Ethernet: Overkill for this application
- USB: Good for debugging but less suitable for industrial applications
**考虑的替代方案**：
- 仅CAN或仅串行：降低灵活性
- 以太网：对此应用过于强大
- USB：适合调试但不太适合工业应用

## Decision: Safety and Protection Implementation    决策：安全与保护实现
**Rationale**: Motor control systems must operate safely under all conditions. Multiple protection layers are needed to respond to faults within microseconds to prevent hardware damage.
**基本原理**：电机控制系统必须在所有条件下安全运行。需要多层保护来在微秒内响应故障以防止硬件损坏。
**Protection mechanisms**:
- Overcurrent: Hardware comparator with immediate response
- Overvoltage: Software monitoring with configurable thresholds
- Overtemperature: Software monitoring with configurable thresholds
- Overspeed: Software monitoring
- Communication timeout: Software watchdog
- Emergency stop: Hardware interrupt
**保护机制**：
- 过流：具有立即响应的硬件比较器
- 过压：具有可配置阈值的软件监控
- 过温：具有可配置阈值的软件监控
- 超速：软件监控
- 通信超时：软件看门狗
- 紧急停止：硬件中断

**Alternatives considered**:
- Software-only protection: May not respond fast enough
- Hardware-only protection: Less flexible and harder to configure
**考虑的替代方案**：
- 仅软件保护：可能响应不够快
- 仅硬件保护：灵活性较差且更难配置

## Decision: MISRA C Compliance Approach    决策：MISRA C合规性方法
**Rationale**: MISRA C is an essential standard for safety-critical embedded systems. Using static analysis tools ensures compliance without extensive manual checking.
**基本原理**：MISRA C是安全关键嵌入式系统的重要标准。使用静态分析工具确保合规性而无需大量手动检查。
**Tools**:
- PC-lint Plus or similar static analysis tool
- Integration into build system
- Regular compliance checks
**工具**：
- PC-lint Plus或类似的静态分析工具
- 集成到构建系统中
- 定期合规性检查

**Alternatives considered**:
- Manual compliance checking: Time-consuming and error-prone
- No compliance checking: Does not meet safety requirements
**考虑的替代方案**：
- 手动合规性检查：耗时且容易出错
- 无合规性检查：不符合安全要求

## Decision: Matlab/Simulink Integration for Algorithm Validation    决策：Matlab/Simulink集成用于算法验证
**Rationale**: Developing motor control algorithms requires extensive simulation before hardware implementation. Matlab/Simulink provides proven models for PMSM simulation and algorithm validation.
**基本原理**：开发电机控制算法需要在硬件实现之前进行广泛的仿真。Matlab/Simulink提供经过验证的永磁同步电机仿真和算法验证模型。
**Process**:
- Develop control algorithms in Simulink
- Simulate with PMSM model
- Generate C code from Simulink model
- Integrate generated code with hand-written code
- Validate performance against simulation
**流程**：
- 在Simulink中开发控制算法
- 使用永磁同步电机模型进行仿真
- 从Simulink模型生成C代码
- 将生成的代码与手写代码集成
- 根据仿真验证性能

**Alternatives considered**:
- Pure hardware development: Higher risk and longer development time
- Other simulation tools: Less proven for motor control applications
**考虑的替代方案**：
- 纯硬件开发：风险更高且开发时间更长
- 其他仿真工具：对电机控制应用验证较少