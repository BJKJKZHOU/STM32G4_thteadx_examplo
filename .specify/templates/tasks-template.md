---
description: "Task list template for STM32 motor control feature implementation"
---
description: "STM32电机控制功能实现的任务列表模板"

# Tasks: [FEATURE NAME]    # Tasks: [功能名称]

**Input**: Design documents from `/specs/[###-feature-name]/`
**输入**: 来自 `/specs/[ ###-feature-name]/` 的设计文档
**Prerequisites**: plan.md (required), spec.md (required for user stories), research.md, data-model.md, contracts/
**先决条件**: plan.md（必需），spec.md（用户故事必需），research.md，data-model.md，contracts/

**Tests**: The examples below include test tasks. Tests are OPTIONAL - only include them if explicitly requested in the feature specification.
**测试**: 下面的示例包括测试任务。测试是可选的 - 仅在功能规范中明确要求时才包括它们。

**Organization**: Tasks are grouped by user story to enable independent implementation and testing of each story.
**组织**: 任务按用户故事分组，以便每个故事可以独立实现和测试。
**CRITICAL**: All tasks MUST comply with STM32 PMSM FOC project constitution regarding timing, safety, and hardware constraints.
**关键**: 所有任务必须符合STM32 PMSM FOC项目章程关于时序、安全和硬件约束的规定。

## Format: `[ID] [P?] [Story] Description`    ## Format: `[ID] [P?] [Story] Description`
- **[P]**: Can run in parallel (different files, no dependencies)
- **[P]**: 可以并行运行（不同文件，无依赖关系）
- **[Story]**: Which user story this task belongs to (e.g., US1, US2, US3)
- **[Story]**: 此任务属于哪个用户故事（例如，US1，US2，US3）
- Include exact file paths in descriptions
- 在描述中包含确切的文件路径
- All timing-critical tasks must include performance validation
- 所有时序关键任务必须包括性能验证
- All safety-critical tasks must include safety validation
- 所有安全关键任务必须包括安全验证

## Path Conventions    ## Path Conventions
- **STM32 Project**: `Core/Src/`, `Core/Inc/`, `Drivers/`, `Middlewares/`, `tests/` at repository root
- **STM32项目**: 仓库根目录下的 `Core/Src/`, `Core/Inc/`, `Drivers/`, `Middlewares/`, `tests/`
- All code must comply with STM32 HAL/LL driver best practices
- 所有代码必须符合STM32 HAL/LL驱动程序最佳实践
- Paths shown below follow STM32项目结构基于plan.md
- 下面显示的路径基于plan.md遵循STM32项目结构

<!-- 
  ============================================================================
  IMPORTANT: The tasks below are SAMPLE TASKS for illustration purposes only.
  
  The /speckit.tasks command MUST replace these with actual tasks based on:
  - User stories from spec.md (with their priorities P1, P2, P3...)
  - Feature requirements from plan.md
  - Entities from data-model.md
  - Motor control specifications from contracts/
  
  Tasks MUST be organized by user story so each story can be:
  - Implemented independently
  - Tested independently
  - Delivered as an MVP increment
  
  DO NOT keep these sample tasks in the generated tasks.md file.
  ============================================================================
-->
<!-- 
  ============================================================================
  重要：下面的任务是仅用于说明目的的示例任务。
  
  /speckit.tasks命令必须根据以下内容替换这些任务：
  - 来自spec.md的用户故事（及其优先级P1，P2，P3...）
  - 来自plan.md的功能需求
  - 来自data-model.md的实体
  - 来自contracts/的电机控制规范
  
  任务必须按用户故事组织，以便每个故事可以：
  - 独立实现
  - 独立测试
  - 作为MVP增量交付
  
  不要在生成的任务.md文件中保留这些示例任务。
  ============================================================================
-->

## Phase 1: Setup (Shared Infrastructure)    ## Phase 1: Setup (Shared Infrastructure)

**Purpose**: Project initialization and basic structure
**目的**: 项目初始化和基本结构

- [ ] T001 Create project structure per implementation plan with STM32 HAL/LL dependencies
- [ ] T001 根据实现计划创建项目结构，包含STM32 HAL/LL依赖
- [ ] T002 Initialize STM32G474xx project with CMSIS and HAL drivers
- [ ] T002 使用CMSIS和HAL驱动程序初始化STM32G474xx项目
- [ ] T003 [P] Configure embedded development tools and timing analysis tools
- [ ] T003 [P] 配置嵌入式开发工具和时序分析工具

---

## Phase 2: Foundational (Blocking Prerequisites)    ## Phase 2: Foundational (Blocking Prerequisites)

**Purpose**: Core infrastructure that MUST be complete before ANY user story can be implemented
**目的**: 在任何用户故事可以实施之前必须完成的核心基础设施

**⚠️ CRITICAL**: No user story work can begin until this phase is complete
**⚠️ 关键**: 在此阶段完成之前不能开始任何用户故事工作
**⚠️ CRITICAL**: All timing and safety constraints must be defined during this phase
**⚠️ 关键**: 所有时序和安全约束必须在此阶段定义

Examples of foundational tasks (adjust based on your project):
基础任务示例（根据您的项目调整）：

- [ ] T004 Setup ADC configuration for motor feedback (current, voltage, temperature)
- [ ] T004 设置电机反馈的ADC配置（电流、电压、温度）
- [ ] T005 [P] Implement PWM generation setup for 3-phase inverter control
- [ ] T005 [P] 实现三相逆变器控制的PWM生成设置
- [ ] T006 [P] Setup timer configuration for control loop timing (e.g., 10kHz)
- [ ] T006 [P] 设置控制回路时序的定时器配置（例如，10kHz）
- [ ] T007 Create base motor control parameters structure
- [ ] T007 创建基础电机控制参数结构
- [ ] T008 Configure error handling and fault detection infrastructure
- [ ] T008 配置错误处理和故障检测基础设施
- [ ] T009 Setup safety monitoring (overcurrent, overtemperature, overvoltage)
- [ ] T009 设置安全监控（过流、过温、过压）
- [ ] T010 Implement basic FOC algorithm framework with timing compliance verification
- [ ] T010 实现基本的FOC算法框架，包含时序合规性验证

**Checkpoint**: Foundation ready - user story implementation can now begin in parallel
**检查点**: 基础就绪 - 用户故事实现现在可以并行开始

---

## Phase 3: User Story 1 - [Title] (Priority: P1) 🎯 MVP    ## Phase 3: User Story 1 - [Title] (Priority: P1) 🎯 MVP

**Goal**: [Brief description of what this story delivers with timing and safety focus]
**目标**: [简要描述此故事交付的内容，重点关注时序和安全]

**Independent Test**: [How to verify this story works on its own with timing and safety validation]
**独立测试**: [如何通过时序和安全验证独立验证此故事工作]

### Tests for User Story 1 (OPTIONAL - only if tests requested) ⚠️    ### Tests for User Story 1 (OPTIONAL - only if tests requested) ⚠️

**NOTE: Write these tests FIRST, ensure they FAIL before implementation**
**注意：首先编写这些测试，确保在实现之前它们失败**
**NOTE: All tests must verify timing, safety, and hardware constraints**
**注意：所有测试必须验证时序、安全和硬件约束**

- [ ] T011 [P] [US1] Unit test for [timing-critical function] in tests/unit/test_[name].c (verifies timing constraints)
- [ ] T011 [P] [US1] 在tests/unit/test_[名称].c中对[时序关键功能]进行单元测试（验证时序约束）
- [ ] T012 [P] [US1] Safety validation test for [fault condition] in tests/safety/test_[name].c
- [ ] T012 [P] [US1] 在tests/safety/test_[名称].c中对[故障条件]进行安全验证测试
- [ ] T013 [P] [US1] Hardware constraint validation in tests/resource/test_[name].c (memory usage, performance)
- [ ] T013 [P] [US1] 在tests/resource/test_[名称].c中进行硬件约束验证（内存使用、性能）

### Implementation for User Story 1    ### Implementation for User Story 1

- [ ] T014 [P] [US1] Implement [motor control function] in Core/Src/[motor_control].c (with timing validation)
- [ ] T014 [P] [US1] 在Core/Src/[电机控制].c中实现[电机控制功能]（包含时序验证）
- [ ] T015 [P] [US1] Create [safety mechanism] in Core/Src/[safety].c (with fault detection)
- [ ] T015 [P] [US1] 在Core/Src/[安全].c中创建[安全机制]（包含故障检测）
- [ ] T016 [US1] Implement [parameter validation] in Core/Src/[validation].c (ensures hardware constraints)
- [ ] T016 [US1] 在Core/Src/[验证].c中实现[参数验证]（确保硬件约束）
- [ ] T017 [US1] Add timing compliance verification in Core/Src/[timing].c
- [ ] T017 [US1] 在Core/Src/[时序].c中添加时序合规性验证
- [ ] T018 [US1] Add error handling and logging for user story 1 in Core/Src/[error_handling].c
- [ ] T018 [US1] 在Core/Src/[错误处理].c中为用户故事1添加错误处理和日志记录

**Checkpoint**: At this point, User Story 1 should be fully functional and testable independently with timing and safety compliance verified
**检查点**: 此时，用户故事1应该完全功能化并可独立测试，时序和安全合规性已验证

---

## Phase 4: User Story 2 - [Title] (Priority: P2)    ## Phase 4: User Story 2 - [Title] (Priority: P2)

**Goal**: [Brief description of what this story delivers with timing and safety focus]
**目标**: [简要描述此故事交付的内容，重点关注时序和安全]

**Independent Test**: [How to verify this story works on its own with timing and safety validation]
**独立测试**: [如何通过时序和安全验证独立验证此故事工作]

### Tests for User Story 2 (OPTIONAL - only if tests requested) ⚠️    ### Tests for User Story 2 (OPTIONAL - only if tests requested) ⚠️

- [ ] T019 [P] [US2] Unit test for [timing-critical function] in tests/unit/test_[name].c (verifies timing constraints)
- [ ] T019 [P] [US2] 在tests/unit/test_[名称].c中对[时序关键功能]进行单元测试（验证时序约束）
- [ ] T020 [P] [US2] Safety validation test for [fault condition] in tests/safety/test_[name].c
- [ ] T020 [P] [US2] 在tests/safety/test_[名称].c中对[故障条件]进行安全验证测试

### Implementation for User Story 2    ### Implementation for User Story 2

- [ ] T021 [P] [US2] Implement [motor control function] in Core/Src/[motor_control].c (with timing validation)
- [ ] T021 [P] [US2] 在Core/Src/[电机控制].c中实现[电机控制功能]（包含时序验证）
- [ ] T022 [US2] Implement [safety mechanism] in Core/Src/[safety].c (with fault detection)
- [ ] T022 [US2] 在Core/Src/[安全].c中实现[安全机制]（包含故障检测）
- [ ] T023 [US2] Integrate with User Story 1 components (if needed) ensuring no timing conflicts
- [ ] T023 [US2] 与用户故事1组件集成（如果需要），确保无时序冲突

**Checkpoint**: At this point, User Stories 1 AND 2 should both work independently with timing and safety compliance verified
**检查点**: 此时，用户故事1和2都应该独立工作，时序和安全合规性已验证

---

## Phase 5: User Story 3 - [Title] (Priority: P3)    ## Phase 5: User Story 3 - [Title] (Priority: P3)

**Goal**: [Brief description of what this story delivers with timing and safety focus]
**目标**: [简要描述此故事交付的内容，重点关注时序和安全]

**Independent Test**: [How to verify this story works on its own with timing and safety validation]
**独立测试**: [如何通过时序和安全验证独立验证此故事工作]

### Tests for User Story 3 (OPTIONAL - only if tests requested) ⚠️    ### Tests for User Story 3 (OPTIONAL - only if tests requested) ⚠️

- [ ] T024 [P] [US3] Unit test for [timing-critical function] in tests/unit/test_[name].c (verifies timing constraints)
- [ ] T024 [P] [US3] 在tests/unit/test_[名称].c中对[时序关键功能]进行单元测试（验证时序约束）
- [ ] T025 [P] [US3] Safety validation test for [fault condition] in tests/safety/test_[name].c
- [ ] T025 [P] [US3] 在tests/safety/test_[名称].c中对[故障条件]进行安全验证测试

### Implementation for User Story 3    ### Implementation for User Story 3

- [ ] T026 [P] [US3] Implement [motor control function] in Core/Src/[motor_control].c (with timing validation)
- [ ] T026 [P] [US3] 在Core/Src/[电机控制].c中实现[电机控制功能]（包含时序验证）
- [ ] T027 [US3] Implement [safety mechanism] in Core/Src/[safety].c (with fault detection)
- [ ] T027 [US3] 在Core/Src/[安全].c中实现[安全机制]（包含故障检测）

**Checkpoint**: All user stories should now be independently functional with timing and safety compliance verified
**检查点**: 所有用户故事现在应该独立功能化，时序和安全合规性已验证

---

[Add more user story phases as needed, following the same pattern]
[根据需要添加更多用户故事阶段，遵循相同模式]

---

## Phase N: Polish & Cross-Cutting Concerns    ## Phase N: Polish & Cross-Cutting Concerns

**Purpose**: Improvements that affect multiple user stories
**目的**: 影响多个用户故事的改进

- [ ] TXXX [P] Documentation updates in docs/ with timing and safety requirements
- [ ] TXXX [P] 在docs/中更新文档，包含时序和安全要求
- [ ] TXXX Code cleanup and refactoring ensuring timing compliance is maintained
- [ ] TXXX 代码清理和重构，确保时序合规性得到维护
- [ ] TXXX Performance optimization across all stories with timing validation
- [ ] TXXX 在所有故事中进行性能优化，包含时序验证
- [ ] TXXX [P] Additional unit tests (if requested) in tests/unit/ with timing and safety validation
- [ ] TXXX [P] 在tests/unit/中添加额外的单元测试（如果需要），包含时序和安全验证
- [ ] TXXX Security and safety hardening review
- [ ] TXXX 安全性和安全性强化审查
- [ ] TXXX Run quickstart.md validation ensuring all constraints are met
- [ ] TXXX 运行quickstart.md验证，确保所有约束得到满足
- [ ] TXXX Full system integration testing with timing, safety and hardware constraint verification
- [ ] TXXX 完整的系统集成测试，包含时序、安全和硬件约束验证

---

## Dependencies & Execution Order    ## Dependencies & Execution Order

### Phase Dependencies    ### Phase Dependencies

- **Setup (Phase 1)**: No dependencies - can start immediately
- **Setup (Phase 1)**: 无依赖关系 - 可以立即开始
- **Foundational (Phase 2)**: Depends on Setup completion - BLOCKS all user stories
- **Foundational (Phase 2)**: 依赖于Setup完成 - 阻塞所有用户故事
- **User Stories (Phase 3+)**: All depend on Foundational phase completion
- **User Stories (Phase 3+)**: 所有依赖于Foundational阶段完成
  - User stories can then proceed in parallel (if staffed)
  - 然后用户故事可以并行进行（如果有人员配备）
  - Or sequentially in priority order (P1 → P2 → P3)
  - 或按优先级顺序依次进行（P1 → P2 → P3）
- **Polish (Final Phase)**: Depends on all desired user stories being complete
- **Polish (Final Phase)**: 依赖于所有期望的用户故事完成

### User Story Dependencies    ### User Story Dependencies

- **User Story 1 (P1)**: Can start after Foundational (Phase 2) - No dependencies on other stories
- **User Story 1 (P1)**: 可以在Foundational（Phase 2）之后开始 - 不依赖其他故事
- **User Story 2 (P2)**: Can start after Foundational (Phase 2) - May integrate with US1 but should be independently testable
- **User Story 2 (P2)**: 可以在Foundational（Phase 2）之后开始 - 可能与US1集成但应该独立可测试
- **User Story 3 (P3)**: Can start after Foundational (Phase 2) - May integrate with US1/US2 but should be independently testable
- **User Story 3 (P3)**: 可以在Foundational（Phase 2）之后开始 - 可能与US1/US2集成但应该独立可测试

### Within Each User Story    ### Within Each User Story

- Tests (if included) MUST be written and FAIL before implementation
- 测试（如果包含）必须在实现之前编写并失败
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

### Parallel Opportunities    ### Parallel Opportunities

- All Setup tasks marked [P] can run in parallel
- 所有标记为[P]的Setup任务可以并行运行
- All Foundational tasks marked [P] can run in parallel (within Phase 2)
- 所有标记为[P]的Foundational任务可以并行运行（在Phase 2内）
- Once Foundational phase completes, all user stories can start in parallel (if team capacity allows)
- 一旦Foundational阶段完成，所有用户故事可以并行开始（如果团队容量允许）
- All tests for a user story marked [P] can run in parallel
- 用户故事的所有标记为[P]的测试可以并行运行
- Functions within a story marked [P] can run in parallel
- 故事内标记为[P]的函数可以并行运行
- Different user stories can be worked on in parallel by different team members
- 不同的用户故事可以由不同的团队成员并行处理

---

## Parallel Example: User Story 1    ## Parallel Example: User Story 1

```bash
# Launch all tests for User Story 1 together (if tests requested):
Task: "Unit test for [timing-critical function] in tests/unit/test_[name].c (verifies timing constraints)"
Task: "Safety validation test for [fault condition] in tests/safety/test_[name].c"

# Launch all functions for User Story 1 together:
Task: "Implement [motor control function] in Core/Src/[motor_control].c (with timing validation)"
Task: "Create [safety mechanism] in Core/Src/[safety].c (with fault detection)"
```
```bash
# 一起启动用户故事1的所有测试（如果请求测试）：
Task: "在tests/unit/test_[名称].c中对[时序关键功能]进行单元测试（验证时序约束）"
Task: "在tests/safety/test_[名称].c中对[故障条件]进行安全验证测试"

# 一起启动用户故事1的所有功能：
Task: "在Core/Src/[电机控制].c中实现[电机控制功能]（包含时序验证）"
Task: "在Core/Src/[安全].c中创建[安全机制]（包含故障检测）"
```

---

## Implementation Strategy    ## Implementation Strategy

### MVP First (User Story 1 Only)    ### MVP First (User Story 1 Only)

1. Complete Phase 1: Setup
1. 完成Phase 1: Setup
2. Complete Phase 2: Foundational (CRITICAL - blocks all stories, defines all constraints)
2. 完成Phase 2: Foundational（关键 - 阻塞所有故事，定义所有约束）
3. Complete Phase 3: User Story 1
3. 完成Phase 3: User Story 1
4. **STOP and VALIDATE**: Test User Story 1 independently with timing and safety validation
4. **停止并验证**: 通过时序和安全验证独立测试用户故事1
5. Deploy/demo if ready
5. 如果准备就绪，部署/演示

### Incremental Delivery    ### Incremental Delivery

1. Complete Setup + Foundational → Foundation ready with all constraints defined
1. 完成Setup + Foundational → 基础就绪，所有约束已定义
2. Add User Story 1 → Test independently with timing/safety validation → Deploy/Demo (MVP!)
2. 添加用户故事1 → 通过时序/安全验证独立测试 → 部署/演示（MVP！）
3. Add User Story 2 → Test independently with timing/safety validation → Deploy/Demo
3. 添加用户故事2 → 通过时序/安全验证独立测试 → 部署/演示
4. Add User Story 3 → Test independently with timing/safety validation → Deploy/Demo
4. 添加用户故事3 → 通过时序/安全验证独立测试 → 部署/演示
5. Each story adds value without breaking previous stories or violating constraints
5. 每个故事在不破坏先前故事或违反约束的情况下增加价值

### Parallel Team Strategy    ### Parallel Team Strategy

With multiple developers:
有多个开发人员时：

1. Team completes Setup + Foundational together (especially constraint definitions)
1. 团队一起完成Setup + Foundational（特别是约束定义）
2. Once Foundational is done:
2. 一旦Foundational完成：
   - Developer A: User Story 1
   - 开发人员A: 用户故事1
   - Developer B: User Story 2
   - 开发人员B: 用户故事2
   - Developer C: User Story 3
   - 开发人员C: 用户故事3
3. Stories complete and integrate independently, all with compliance verification
3. 故事完成并独立集成，所有都包含合规性验证

---

## Notes    ## Notes

- [P] tasks = different files, no dependencies
- [P] 任务 = 不同文件，无依赖关系
- [Story] label maps task to specific user story for traceability
- [Story] 标签将任务映射到特定用户故事以便追踪
- Each user story should be independently completable and testable
- 每个用户故事应该独立完成和可测试
- Verify tests fail before implementing
- 在实现之前验证测试失败
- Commit after each task or logical group
- 在每个任务或逻辑组之后提交
- Stop at any checkpoint to validate story independently with timing and safety compliance
- 在任何检查点停止，通过时序和安全合规性独立验证故事
- Avoid: vague tasks, same file conflicts, cross-story dependencies that break independence
- 避免：模糊任务，相同文件冲突，破坏独立性的跨故事依赖关系
- CRITICAL: All timing-critical code must be validated against timing constraints
- 关键：所有时序关键代码必须根据时序约束进行验证
- CRITICAL: All safety-critical code must be validated with safety tests
- 关键：所有安全关键代码必须通过安全测试进行验证
- CRITICAL: All hardware resources must be validated against constraints
- 关键：所有硬件资源必须根据约束进行验证
- CRITICAL: Before completion, each story must be verified to not violate any constitution principles
- 关键：在完成之前，每个故事必须被验证不违反任何章程原则