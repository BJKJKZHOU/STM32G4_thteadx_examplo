<!-- 
Sync Impact Report:
- Version change: 1.0.0 → 1.1.0
- Modified principles: Added STM32-specific timing, safety, and hardware principles
- Added sections: Timing Constraints, Error Handling, Hardware Constraints
- Templates requiring updates: plan-template.md, spec-template.md, tasks-template.md (all updated to reflect STM32 motor control requirements)
- Follow-up: Ensure all development follows the new timing and safety requirements
-->

# STM32 PMSM FOC Motor Control Project Constitution
STM32 PMSM FOC 电机控制项目章程

## Core Principles
核心原则

### Timing Constraint Compliance
时序约束符合性

All code must satisfy specified timing constraints; Performance-critical functions must be optimized and measured; Latency requirements must be consistently met under all operating conditions.
所有代码必须满足指定的时序约束；性能关键函数必须经过优化和测量；在所有操作条件下必须一致满足延迟要求。

### Comprehensive Error Handling and Safety
全面的错误处理和安全保障

Implement comprehensive error handling and fault detection; Systems must fail safely; All safety-critical code must undergo appropriate testing and validation.
实施全面的错误处理和故障检测；系统必须安全失效；所有安全关键代码必须经过适当的测试和验证。

### Hardware Constraint Compliance
硬件约束符合性

All implementations must respect hardware limitations (memory, processing power, peripheral constraints); Code must not cause hardware failures; Ensure personnel and equipment safety during operation, testing, and unexpected failures.
所有实现必须尊重硬件限制（内存、处理能力、外设约束）；代码不能导致硬件故障；保障运行、测试、突发故障时的人员和设备安全。

### Performance Optimization
性能优化

All performance-critical functions must be profiled and optimized; Measurement and verification of timing requirements must be conducted under all operating conditions.
所有性能关键函数必须经过分析和优化；在所有操作条件下必须测量和验证时序要求。

### Safety-Critical Development
安全关键开发

All safety-critical code must undergo rigorous validation and verification processes; Design and implementation must follow safety standards appropriate for motor control applications.
所有安全关键代码必须经过严格的验证和确认过程；设计和实现必须遵循适用于电机控制应用的安全标准。

## Additional Constraints
附加约束

STM32G474xx microcontroller specific development:
- Utilize hardware peripherals effectively (e.g., ADC, timers, PWM, FPU)
- Optimize for real-time performance requirements
- Follow STM32 HAL/LL driver best practices
- Implement proper ADC sampling and conversion for motor feedback
- Use hardware-based PWM generation for motor control signals
- Implement motor control protection mechanisms (overcurrent, overtemperature, overvoltage)

STM32G474xx微控制器特定开发：
- 有效利用硬件外设（如ADC、定时器、PWM、FPU）
- 针对实时性能要求进行优化
- 遵循STM32 HAL/LL驱动最佳实践
- 为电机反馈实施适当的ADC采样和转换
- 使用硬件PWM生成电机控制信号
- 实施电机控制保护机制（过流、过温、过压）

## Development Workflow
开发工作流程

### Code Review Requirements
代码审查要求

- All timing-critical code must be reviewed with focus on performance impact
- Safety-critical code must undergo pair programming or dual review
- Hardware constraint compliance must be verified during review process

- 所有定时关键代码必须审查，重点关注性能影响
- 安全关键代码必须进行结对编程或双重审查
- 在审查过程中必须验证硬件约束符合性

### Testing Gates
测试关口

- Unit tests must validate timing behavior under normal and edge conditions
- Integration tests must verify hardware interaction safety
- System tests must confirm safety mechanisms function correctly

- 单元测试必须在正常和边界条件下验证时序行为
- 集成测试必须验证硬件交互安全性
- 系统测试必须确认安全机制正常工作

## Governance
治理

All PRs/reviews must verify compliance with timing, safety, and hardware constraints; Complexity must be justified with performance and safety trade-off analysis; Use this constitution for STM32 motor control development guidance.

所有PR/审查必须验证时序、安全和硬件约束的符合性；必须用性能和安全权衡分析来证明复杂性是合理的；使用本章程作为STM32电机控制开发指南。

**Version**: 1.1.0 | **Ratified**: 2025-01-01 | **Last Amended**: 2025-10-17
**版本**: 1.1.0 | **通过日期**: 2025-01-01 | **最后修订**: 2025-10-17
