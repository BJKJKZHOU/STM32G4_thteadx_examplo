---
description: "Task list for PMSM FOC Control System implementation"
description: "PMSM FOC控制系统实现的任务列表"
---

# Tasks: PMSM FOC Control System    PMSM FOC控制系统任务

**Input**: Design documents from `/specs/001-pmsm-foc-control/`
**Input**: 来自 `/specs/001-pmsm-foc-control/` 的设计文档
**Prerequisites**: plan.md (required), spec.md (required for user stories), research.md, data-model.md, contracts/
**Prerequisites**: plan.md (必需), spec.md (用户故事必需), research.md, data-model.md, contracts/

**Tests**: The examples below include test tasks. Tests are OPTIONAL - only include them if explicitly requested in the feature specification.
**Tests**: 以下示例包含测试任务。测试是可选的 - 仅在功能规范中明确要求时包含。

**Organization**: Tasks are grouped by user story to enable independent implementation and testing of each story.
**Organization**: 任务按用户故事分组，以便每个故事可以独立实现和测试。

## Format: `[ID] [P?] [Story] Description`
## 格式: `[ID] [P?] [Story] 描述`
- **[P]**: Can run in parallel (different files, no dependencies)
- **[P]**: 可以并行运行（不同文件，无依赖关系）
- **[Story]**: Which user story this task belongs to (e.g., US1, US2, US3)
- **[Story]**: 此任务属于哪个用户故事（例如 US1, US2, US3）
- Include exact file paths in descriptions
- 在描述中包含确切文件路径

## Path Conventions
## 路径约定
- **STM32 Project**: `Core/Src/`, `Core/Inc/`, `Drivers/`, `Middlewares/`, `tests/` at repository root
- **STM32 项目**: 仓库根目录下的 `Core/Src/`, `Core/Inc/`, `Drivers/`, `Middlewares/`, `tests/`
- All code must comply with STM32 HAL/LL driver best practices
- 所有代码必须符合 STM32 HAL/LL 驱动程序最佳实践
- Paths shown below follow STM32 project structure based on plan.md
- 以下路径遵循基于 plan.md 的 STM32 项目结构

## Phase 1: Setup (Shared Infrastructure)
## 阶段 1: 设置（共享基础设施）

**Purpose**: Project initialization and basic structure
**目的**: 项目初始化和基本结构

- [ ] T001 Create project structure per implementation plan with STM32 HAL/LL dependencies
- [ ] T001 根据实现计划创建项目结构，包含 STM32 HAL/LL 依赖项
- [ ] T002 Initialize STM32G474xx project with CMSIS and HAL drivers
- [ ] T002 使用 CMSIS 和 HAL 驱动程序初始化 STM32G474xx 项目
- [ ] T003 [P] Configure embedded development tools and timing analysis tools
- [ ] T003 [P] 配置嵌入式开发工具和时序分析工具
- [ ] T004 [P] Set up MISRA C compliance checking with static analysis tool
- [ ] T004 [P] 使用静态分析工具设置 MISRA C 合规性检查
- [ ] T005 [P] Configure CMake build system for STM32G474xx target
- [ ] T005 [P] 为 STM32G474xx 目标配置 CMake 构建系统
- [ ] T006 Set up ThreadX RTOS integration in project
- [ ] T006 在项目中设置 ThreadX RTOS 集成

---

## Phase 2: Foundational (Blocking Prerequisites)
## 阶段 2: 基础（阻塞性先决条件）

**Purpose**: Core infrastructure that MUST be complete before ANY user story can be implemented
**目的**: 在任何用户故事实现之前必须完成的核心基础设施

**⚠️ CRITICAL**: No user story work can begin until this phase is complete
**⚠️ 关键**: 在此阶段完成之前不能开始任何用户故事工作

- [ ] T007 Setup ADC configuration for motor feedback (current, voltage, temperature)
- [ ] T007 设置用于电机反馈的 ADC 配置（电流、电压、温度）
- [ ] T008 [P] Implement PWM generation setup for 3-phase inverter control
- [ ] T008 [P] 实现用于三相逆变器控制的 PWM 生成设置
- [ ] T009 [P] Setup timer configuration for control loop timing (e.g., 10kHz)
- [ ] T009 [P] 设置用于控制循环时序的定时器配置（例如 10kHz）
- [ ] T010 Create base motor control parameters structure in Core/Inc/motor_parameters.h
- [ ] T010 在 Core/Inc/motor_parameters.h 中创建基础电机控制参数结构
- [ ] T011 Configure error handling and fault detection infrastructure in Core/Inc/safety.h
- [ ] T011 在 Core/Inc/safety.h 中配置错误处理和故障检测基础设施
- [ ] T012 Setup safety monitoring (overcurrent, overtemperature, overvoltage)
- [ ] T012 设置安全监控（过流、过温、过压）
- [ ] T013 Implement basic FOC algorithm framework with timing compliance verification
- [ ] T013 实现基础 FOC 算法框架，包含时序合规性验证
- [ ] T014 [P] Set up encoder interface for position feedback in Core/Inc/encoder.h
- [ ] T014 [P] 在 Core/Inc/encoder.h 中设置用于位置反馈的编码器接口
- [ ] T015 [P] Initialize PID controller utilities in Core/Utils/pid_controller.h and Core/Utils/pid_controller.c
- [ ] T015 [P] 在 Core/Utils/pid_controller.h 和 Core/Utils/pid_controller.c 中初始化 PID 控制器工具
- [ ] T016 [P] Implement coordinate transform utilities (Clarke/Park) in Core/Utils/clarke_park_transforms.h and Core/Utils/clarke_park_transforms.c
- [ ] T016 [P] 在 Core/Utils/clarke_park_transforms.h 和 Core/Utils/clarke_park_transforms.c 中实现坐标变换工具（Clarke/Park）
- [ ] T017 Configure ThreadX RTOS tasks and priorities for motor control
- [ ] T017 为电机控制配置 ThreadX RTOS 任务和优先级
- [ ] T018 Set up communication interface drivers (CAN/UART) in Core/Inc/communication.h
- [ ] T018 在 Core/Inc/communication.h 中设置通信接口驱动程序（CAN/UART）
- [ ] T019 [P] Configure Matlab/Simulink integration for algorithm validation
- [ ] T019 [P] 为算法验证配置 Matlab/Simulink 集成

**Checkpoint**: Foundation ready - user story implementation can now begin in parallel
**检查点**: 基础就绪 - 现在可以并行开始用户故事实现

---

## Phase 3: User Story 1 - PMSM FOC Basic Control (Priority: P1) 🎯 MVP
## 阶段 3: 用户故事 1 - PMSM FOC 基础控制（优先级: P1）🎯 MVP

**Goal**: Basic motor control with start/stop and speed control functionality
**目标**: 具有启动/停止和速度控制功能的基础电机控制

**Independent Test**: Can be fully tested by connecting a PMSM motor, issuing start/stop commands and speed setpoints, and verifying the motor responds appropriately with safety protection mechanisms working within timing constraints.
**独立测试**: 可以通过连接 PMSM 电机、发出启动/停止命令和速度设定点来完全测试，并验证电机响应适当，安全保护机制在时序约束内工作。

### Tests for User Story 1 (OPTIONAL - only if tests requested) ⚠️
### 用户故事 1 的测试（可选 - 仅在要求测试时）⚠️

**NOTE: Write these tests FIRST, ensure they FAIL before implementation**
**注意: 首先编写这些测试，确保在实现之前测试失败**
**NOTE: All tests must verify timing, safety, and hardware constraints**
**注意: 所有测试必须验证时序、安全和硬件约束**

- [ ] T020 [P] [US1] Unit test for basic motor control functions in tests/unit/test_motor_control.c (verifies timing constraints)
- [ ] T020 [P] [US1] 在 tests/unit/test_motor_control.c 中对基础电机控制功能进行单元测试（验证时序约束）
- [ ] T021 [P] [US1] Safety validation test for overcurrent protection in tests/safety/test_fault_protection.c
- [ ] T021 [P] [US1] 在 tests/safety/test_fault_protection.c 中对过流保护进行安全验证测试
- [ ] T022 [P] [US1] Timing compliance test for 10kHz control loop in tests/unit/test_timing_compliance.c
- [ ] T022 [P] [US1] 在 tests/unit/test_timing_compliance.c 中对 10kHz 控制循环进行时序合规性测试

### Implementation for User Story 1
### 用户故事 1 的实现

- [ ] T023 [P] [US1] Implement basic motor control interface in Core/Src/motor_control.c (with timing validation)
- [ ] T023 [P] [US1] 在 Core/Src/motor_control.c 中实现基础电机控制接口（包含时序验证）
- [ ] T024 [P] [US1] Create safety mechanism for basic protection in Core/Src/safety.c (with fault detection)
- [ ] T024 [P] [US1] 在 Core/Src/safety.c 中创建基础保护的安全机制（包含故障检测）
- [ ] T025 [US1] Implement motor parameter validation in Core/Src/motor_parameters.c (ensures hardware constraints)
- [ ] T025 [US1] 在 Core/Src/motor_parameters.c 中实现电机参数验证（确保硬件约束）
- [ ] T026 [US1] Add timing compliance verification for control loop in Core/Src/timer_handler.c
- [ ] T026 [US1] 在 Core/Src/timer_handler.c 中为控制循环添加时序合规性验证
- [ ] T027 [US1] Add error handling and logging for user story 1 in Core/Src/motor_control.c
- [ ] T027 [US1] 在 Core/Src/motor_control.c 中为用户故事 1 添加错误处理与日志记录
- [ ] T028 [US1] Implement motor start/stop control functions in Core/Src/motor_control.c
- [ ] T028 [US1] 在 Core/Src/motor_control.c 中实现电机启动/停止控制功能
- [ ] T029 [US1] Implement speed control loop with PID in Core/Src/speed_control.c
- [ ] T029 [US1] 在 Core/Src/speed_control.c 中使用 PID 实现速度控制循环
- [ ] T030 [US1] Integrate ThreadX task for basic motor control in Core/Src/main.c
- [ ] T030 [US1] 在 Core/Src/main.c 中集成用于基础电机控制的 ThreadX 任务
- [ ] T031 [US1] Implement basic current sensing and ADC handling in Core/Src/adc_handler.c
- [ ] T031 [US1] 在 Core/Src/adc_handler.c 中实现基础电流检测和 ADC 处理
- [ ] T032 [US1] Add basic communication commands (START/STOP/SPEED) in Core/Src/communication.c
- [ ] T032 [US1] 在 Core/Src/communication.c 中添加基础通信命令（START/STOP/SPEED）

**Checkpoint**: At this point, User Story 1 should be fully functional and testable independently with timing and safety compliance verified
**检查点**: 此时，用户故事 1 应该完全功能化并可独立测试，时序和安全合规性已验证

---

## Phase 4: User Story 2 - Advanced Position and Current Control (Priority: P2)
## 阶段 4: 用户故事 2 - 高级位置和电流控制（优先级: P2）

**Goal**: Advanced position and current control with full FOC algorithm implementation
**目标**: 具有完整 FOC 算法实现的高级位置和电流控制

**Independent Test**: Can be tested by configuring position control mode, setting position targets, and verifying the motor accurately reaches those positions while maintaining proper current control and safety protection.
**独立测试**: 可以通过配置位置控制模式、设置位置目标来测试，并验证电机准确到达这些位置，同时保持适当的电流控制和安全保护。

### Tests for User Story 2 (OPTIONAL - only if tests requested) ⚠️
### 用户故事 2 的测试（可选 - 仅在要求测试时）⚠️

- [ ] T033 [P] [US2] Unit test for FOC algorithm in tests/unit/test_foc_control.c (verifies timing constraints)
- [ ] T033 [P] [US2] 在 tests/unit/test_foc_control.c 中对 FOC 算法进行单元测试（验证时序约束）
- [ ] T034 [P] [US2] Safety validation test for position control in tests/safety/test_position_control.c
- [ ] T034 [P] [US2] 在 tests/safety/test_position_control.c 中对位置控制进行安全验证测试

### Implementation for User Story 2
### 用户故事 2 的实现

- [ ] T035 [P] [US2] Implement full FOC algorithm in Core/Src/foc_control.c (with timing validation)
- [ ] T035 [P] [US2] 在 Core/Src/foc_control.c 中实现完整 FOC 算法（包含时序验证）
- [ ] T036 [P] [US2] Create advanced safety mechanism in Core/Src/safety.c (with fault detection)
- [ ] T036 [P] [US2] 在 Core/Src/safety.c 中创建高级安全机制（包含故障检测）
- [ ] T037 [US2] Implement position control loop in Core/Src/position_control.c
- [ ] T037 [US2] 在 Core/Src/position_control.c 中实现位置控制循环
- [ ] T038 [US2] Implement current control loop for d/q axis in Core/Src/current_control.c
- [ ] T038 [US2] 在 Core/Src/current_control.c 中实现 d/q 轴电流控制循环
- [ ] T039 [US2] Integrate FOC algorithm with position and current control in Core/Src/foc_control.c
- [ ] T039 [US2] 在 Core/Src/foc_control.c 中将 FOC 算法与位置和电流控制集成
- [ ] T040 [US2] Implement position sensing and processing in Core/Src/encoder.c
- [ ] T040 [US2] 在 Core/Src/encoder.c 中实现位置检测与处理
- [ ] T041 [US2] Update ThreadX tasks for advanced control in Core/Src/main.c
- [ ] T041 [US2] 在 Core/Src/main.c 中更新用于高级控制的 ThreadX 任务
- [ ] T042 [US2] Add position and current control commands to communication interface in Core/Src/communication.c
- [ ] T042 [US2] 在 Core/Src/communication.c 中向通信接口添加位置和电流控制命令

**Checkpoint**: At this point, User Stories 1 AND 2 should both work independently with timing and safety compliance verified
**检查点**: 此时，用户故事 1 和 2 都应该独立工作，时序和安全合规性已验证

---

## Phase 5: User Story 3 - Communication and Monitoring (Priority: P3)
## 阶段 5: 用户故事 3 - 通信与监控（优先级: P3）

**Goal**: Remote monitoring and communication interface implementation
**目标**: 远程监控和通信接口实现

**Independent Test**: Can be tested by connecting host computer via CAN or serial, sending commands, and verifying bidirectional communication with real-time status updates while maintaining core motor control and safety functions.
**独立测试**: 可以通过 CAN 或串口连接主机计算机、发送命令来测试，并验证双向通信与实时状态更新，同时保持核心电机控制和安全功能。

### Tests for User Story 3 (OPTIONAL - only if tests requested) ⚠️
### 用户故事 3 的测试（可选 - 仅在要求测试时）⚠️

- [ ] T043 [P] [US3] Unit test for communication protocol in tests/unit/test_communication.c (verifies timing constraints)
- [ ] T043 [P] [US3] 在 tests/unit/test_communication.c 中对通信协议进行单元测试（验证时序约束）
- [ ] T044 [P] [US3] Safety validation test for communication timeout in tests/safety/test_communication_timeout.c
- [ ] T044 [P] [US3] 在 tests/safety/test_communication_timeout.c 中对通信超时进行安全验证测试

### Implementation for User Story 3
### 用户故事 3 的实现

- [ ] T045 [P] [US3] Implement CAN communication protocol in Core/Src/communication.c (with timing validation)
- [ ] T045 [P] [US3] 在 Core/Src/communication.c 中实现 CAN 通信协议（包含时序验证）
- [ ] T046 [P] [US3] Implement serial communication protocol in Core/Src/communication.c (with timing validation)
- [ ] T046 [P] [US3] 在 Core/Src/communication.c 中实现串行通信协议（包含时序验证）
- [ ] T047 [US3] Implement status reporting functionality in Core/Src/communication.c
- [ ] T047 [US3] 在 Core/Src/communication.c 中实现状态报告功能
- [ ] T048 [US3] Create communication command handlers in Core/Src/communication.c
- [ ] T048 [US3] 在 Core/Src/communication.c 中创建通信命令处理器
- [ ] T049 [US3] Implement status frame generation for CAN in Core/Src/communication.c
- [ ] T049 [US3] 在 Core/Src/communication.c 中为 CAN 实现状态帧生成
- [ ] T050 [US3] Integrate communication tasks with ThreadX in Core/Src/main.c
- [ ] T050 [US3] 在 Core/Src/main.c 中将通信任务与 ThreadX 集成
- [ ] T051 [US3] Add configuration commands to communication interface in Core/Src/communication.c
- [ ] T051 [US3] 在 Core/Src/communication.c 中向通信接口添加配置命令
- [ ] T052 [US3] Implement parameter storage and retrieval in Core/Src/motor_parameters.c
- [ ] T052 [US3] 在 Core/Src/motor_parameters.c 中实现参数存储与检索

**Checkpoint**: All user stories should now be independently functional with timing and safety compliance verified
**检查点**: 所有用户故事现在都应该独立功能化，时序和安全合规性已验证

---

## Phase N: Polish & Cross-Cutting Concerns
## 阶段 N: 完善与横切关注点

**Purpose**: Improvements that affect multiple user stories
**目的**: 影响多个用户故事的改进

- [ ] T053 [P] Documentation updates in docs/ with timing and safety requirements
- [ ] T053 [P] 在 docs/ 中更新文档，包含时序和安全要求
- [ ] T054 Code cleanup and refactoring ensuring timing compliance is maintained
- [ ] T054 代码清理和重构，确保时序合规性得到保持
- [ ] T055 Performance optimization across all stories with timing validation
- [ ] T055 在所有故事中进行性能优化，包含时序验证
- [ ] T056 [P] Additional unit tests (if requested) in tests/unit/ with timing and safety validation
- [ ] T056 [P] 在 tests/unit/ 中添加额外单元测试（如要求），包含时序和安全验证
- [ ] T057 Security and safety hardening review
- [ ] T057 安全性和安全性加固审查
- [ ] T058 Run quickstart.md validation ensuring all constraints are met
- [ ] T058 运行 quickstart.md 验证，确保所有约束得到满足
- [ ] T059 Full system integration testing with timing, safety and hardware constraint verification
- [ ] T059 完整系统集成测试，包含时序、安全和硬件约束验证
- [ ] T060 MISRA C compliance verification with static analysis
- [ ] T060 使用静态分析进行 MISRA C 合规性验证
- [ ] T061 Final timing validation and performance profiling
- [ ] T061 最终时序验证和性能分析
- [ ] T062 Update configuration files for motor parameters in configs/motor_configs/
- [ ] T062 在 configs/motor_configs/ 中更新电机参数配置文件

---

## Dependencies & Execution Order
## 依赖关系与执行顺序

### Phase Dependencies
### 阶段依赖关系

- **Setup (Phase 1)**: No dependencies - can start immediately
- **设置（阶段 1）**: 无依赖关系 - 可以立即开始
- **Foundational (Phase 2)**: Depends on Setup completion - BLOCKS all user stories
- **基础（阶段 2）**: 依赖于设置完成 - 阻塞所有用户故事
- **User Stories (Phase 3+)**: All depend on Foundational phase completion
- **用户故事（阶段 3+）**: 都依赖于基础阶段完成
  - User stories can then proceed in parallel (if staffed)
  - 用户故事然后可以并行进行（如果有人员配备）
  - Or sequentially in priority order (P1 → P2 → P3)
  - 或按优先级顺序依次进行（P1 → P2 → P3）
- **Polish (Final Phase)**: Depends on all desired user stories being complete
- **完善（最终阶段）**: 依赖于所有期望的用户故事完成

### User Story Dependencies
### 用户故事依赖关系

- **User Story 1 (P1)**: Can start after Foundational (Phase 2) - No dependencies on other stories
- **用户故事 1 (P1)**: 可以在基础（阶段 2）之后开始 - 不依赖其他故事
- **User Story 2 (P2)**: Can start after Foundational (Phase 2) - May integrate with US1 but should be independently testable
- **用户故事 2 (P2)**: 可以在基础（阶段 2）之后开始 - 可能与 US1 集成但应该可独立测试
- **User Story 3 (P3)**: Can start after Foundational (Phase 2) - May integrate with US1/US2 but should be independently testable
- **用户故事 3 (P3)**: 可以在基础（阶段 2）之后开始 - 可能与 US1/US2 集成但应该可独立测试

### Within Each User Story
### 在每个用户故事内

- Tests (if included) MUST be written and FAIL before implementation
- 测试（如包含）必须在实现之前编写并失败
- Safety-critical components before functional components
- 安全关键组件在功能组件之前
- Timing-critical functions before integration
- 时序关键功能在集成之前
- Core implementation before integration
- 核心实现在集成之前
- All safety validations complete before story completion
- 所有安全验证在故事完成之前完成
- All timing validations complete before story completion
- 所有时序验证在故事完成之前完成
- All hardware constraint validations complete before story completion
- 所有硬件约束验证在故事完成之前完成
- Story complete before moving to next priority
- 故事完成后再移动到下一个优先级

### Parallel Opportunities
### 并行机会

- All Setup tasks marked [P] can run in parallel
- 所有标记为 [P] 的设置任务可以并行运行
- All Foundational tasks marked [P] can run in parallel (within Phase 2)
- 所有标记为 [P] 的基础任务可以并行运行（在阶段 2 内）
- Once Foundational phase completes, all user stories can start in parallel (if team capacity allows)
- 一旦基础阶段完成，所有用户故事可以并行开始（如果团队容量允许）
- All tests for a user story marked [P] can run in parallel
- 用户故事的所有标记为 [P] 的测试可以并行运行
- Functions within a story marked [P] can run in parallel
- 故事内标记为 [P] 的功能可以并行运行
- Different user stories can be worked on in parallel by different team members
- 不同的用户故事可以由不同的团队成员并行工作

---

## Parallel Example: User Story 1
## 并行示例: 用户故事 1

```bash
# Launch all tests for User Story 1 together (if tests requested):
# 一起启动用户故事 1 的所有测试（如要求测试）:
Task: "Unit test for basic motor control functions in tests/unit/test_motor_control.c (verifies timing constraints)"
Task: "在 tests/unit/test_motor_control.c 中对基础电机控制功能进行单元测试（验证时序约束）"
Task: "Safety validation test for overcurrent protection in tests/safety/test_fault_protection.c"
Task: "在 tests/safety/test_fault_protection.c 中对过流保护进行安全验证测试"

# Launch all functions for User Story 1 together:
# 一起启动用户故事 1 的所有功能:
Task: "Implement basic motor control interface in Core/Src/motor_control.c (with timing validation)"
Task: "在 Core/Src/motor_control.c 中实现基础电机控制接口（包含时序验证）"
Task: "Create safety mechanism for basic protection in Core/Src/safety.c (with fault detection)"
Task: "在 Core/Src/safety.c 中创建基础保护的安全机制（包含故障检测）"
```

---

## Implementation Strategy
## 实现策略

### MVP First (User Story 1 Only)
### MVP 优先（仅用户故事 1）

1. Complete Phase 1: Setup
1. 完成阶段 1: 设置
2. Complete Phase 2: Foundational (CRITICAL - blocks all stories, defines all constraints)
2. 完成阶段 2: 基础（关键 - 阻塞所有故事，定义所有约束）
3. Complete Phase 3: User Story 1
3. 完成阶段 3: 用户故事 1
4. **STOP and VALIDATE**: Test User Story 1 independently with timing and safety validation
4. **停止并验证**: 独立测试用户故事 1，包含时序和安全验证
5. Deploy/demo if ready
5. 如果准备就绪，部署/演示

### Incremental Delivery
### 增量交付

1. Complete Setup + Foundational → Foundation ready with all constraints defined
1. 完成设置 + 基础 → 基础就绪，所有约束已定义
2. Add User Story 1 → Test independently with timing/safety validation → Deploy/Demo (MVP!)
2. 添加用户故事 1 → 独立测试，包含时序/安全验证 → 部署/演示（MVP!）
3. Add User Story 2 → Test independently with timing/safety validation → Deploy/Demo
3. 添加用户故事 2 → 独立测试，包含时序/安全验证 → 部署/演示
4. Add User Story 3 → Test independently with timing/safety validation → Deploy/Demo
4. 添加用户故事 3 → 独立测试，包含时序/安全验证 → 部署/演示
5. Each story adds value without breaking previous stories or violating constraints
5. 每个故事增加价值，不破坏先前故事或违反约束

### Parallel Team Strategy
### 并行团队策略

With multiple developers:
有多个开发人员时:

1. Team completes Setup + Foundational together (especially constraint definitions)
1. 团队一起完成设置 + 基础（特别是约束定义）
2. Once Foundational is done:
2. 一旦基础完成:
   - Developer A: User Story 1
   - 开发人员 A: 用户故事 1
   - Developer B: User Story 2
   - 开发人员 B: 用户故事 2
   - Developer C: User Story 3
   - 开发人员 C: 用户故事 3
3. Stories complete and integrate independently, all with compliance verification
3. 故事独立完成和集成，都包含合规性验证

---

## Notes
## 注意事项

- [P] tasks = different files, no dependencies
- [P] 任务 = 不同文件，无依赖关系
- [Story] label maps task to specific user story for traceability
- [Story] 标签将任务映射到特定用户故事以便追溯
- Each user story should be independently completable and testable
- 每个用户故事应该可独立完成和测试
- Verify tests fail before implementing
- 在实现之前验证测试失败
- Commit after each task or logical group
- 在每个任务或逻辑组之后提交
- Stop at any checkpoint to validate story independently with timing and safety compliance
- 在任何检查点停止，独立验证故事的时序和安全合规性
- Avoid: vague tasks, same file conflicts, cross-story dependencies that break independence
- 避免: 模糊任务、相同文件冲突、破坏独立性的跨故事依赖关系
- CRITICAL: All timing-critical code must be validated against timing constraints
- 关键: 所有时序关键代码必须根据时序约束进行验证
- CRITICAL: All safety-critical code must be validated with safety tests
- 关键: 所有安全关键代码必须通过安全测试进行验证
- CRITICAL: All hardware resources must be validated against constraints
- 关键: 所有硬件资源必须根据约束进行验证
- CRITICAL: Before completion, each story must be verified to not violate any constitution principles
- 关键: 在完成之前，每个故事必须验证不违反任何基本原则