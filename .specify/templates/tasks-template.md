---
description: "Task list template for STM32 motor control feature implementation"
---

# Tasks: [FEATURE NAME]

**Input**: Design documents from `/specs/[###-feature-name]/`
**Prerequisites**: plan.md (required), spec.md (required for user stories), research.md, data-model.md, contracts/

**Tests**: The examples below include test tasks. Tests are OPTIONAL - only include them if explicitly requested in the feature specification.

**Organization**: Tasks are grouped by user story to enable independent implementation and testing of each story.
**CRITICAL**: All tasks MUST comply with STM32 PMSM FOC project constitution regarding timing, safety, and hardware constraints.

## Format: `[ID] [P?] [Story] Description`
- **[P]**: Can run in parallel (different files, no dependencies)
- **[Story]**: Which user story this task belongs to (e.g., US1, US2, US3)
- Include exact file paths in descriptions
- All timing-critical tasks must include performance validation
- All safety-critical tasks must include safety validation

## Path Conventions
- **STM32 Project**: `Core/Src/`, `Core/Inc/`, `Drivers/`, `Middlewares/`, `tests/` at repository root
- All code must comply with STM32 HAL/LL driver best practices
- Paths shown below follow STM32 project structure based on plan.md

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

## Phase 1: Setup (Shared Infrastructure)

**Purpose**: Project initialization and basic structure

- [ ] T001 Create project structure per implementation plan with STM32 HAL/LL dependencies
- [ ] T002 Initialize STM32G474xx project with CMSIS and HAL drivers
- [ ] T003 [P] Configure embedded development tools and timing analysis tools

---

## Phase 2: Foundational (Blocking Prerequisites)

**Purpose**: Core infrastructure that MUST be complete before ANY user story can be implemented

**⚠️ CRITICAL**: No user story work can begin until this phase is complete
**⚠️ CRITICAL**: All timing and safety constraints must be defined during this phase

Examples of foundational tasks (adjust based on your project):

- [ ] T004 Setup ADC configuration for motor feedback (current, voltage, temperature)
- [ ] T005 [P] Implement PWM generation setup for 3-phase inverter control
- [ ] T006 [P] Setup timer configuration for control loop timing (e.g., 10kHz)
- [ ] T007 Create base motor control parameters structure
- [ ] T008 Configure error handling and fault detection infrastructure
- [ ] T009 Setup safety monitoring (overcurrent, overtemperature, overvoltage)
- [ ] T010 Implement basic FOC algorithm framework with timing compliance verification

**Checkpoint**: Foundation ready - user story implementation can now begin in parallel

---

## Phase 3: User Story 1 - [Title] (Priority: P1) 🎯 MVP

**Goal**: [Brief description of what this story delivers with timing and safety focus]

**Independent Test**: [How to verify this story works on its own with timing and safety validation]

### Tests for User Story 1 (OPTIONAL - only if tests requested) ⚠️

**NOTE: Write these tests FIRST, ensure they FAIL before implementation**
**NOTE: All tests must verify timing, safety, and hardware constraints**

- [ ] T011 [P] [US1] Unit test for [timing-critical function] in tests/unit/test_[name].c (verifies timing constraints)
- [ ] T012 [P] [US1] Safety validation test for [fault condition] in tests/safety/test_[name].c
- [ ] T013 [P] [US1] Hardware constraint validation in tests/resource/test_[name].c (memory usage, performance)

### Implementation for User Story 1

- [ ] T014 [P] [US1] Implement [motor control function] in Core/Src/[motor_control].c (with timing validation)
- [ ] T015 [P] [US1] Create [safety mechanism] in Core/Src/[safety].c (with fault detection)
- [ ] T016 [US1] Implement [parameter validation] in Core/Src/[validation].c (ensures hardware constraints)
- [ ] T017 [US1] Add timing compliance verification in Core/Src/[timing].c
- [ ] T018 [US1] Add error handling and logging for user story 1 in Core/Src/[error_handling].c

**Checkpoint**: At this point, User Story 1 should be fully functional and testable independently with timing and safety compliance verified

---

## Phase 4: User Story 2 - [Title] (Priority: P2)

**Goal**: [Brief description of what this story delivers with timing and safety focus]

**Independent Test**: [How to verify this story works on its own with timing and safety validation]

### Tests for User Story 2 (OPTIONAL - only if tests requested) ⚠️

- [ ] T019 [P] [US2] Unit test for [timing-critical function] in tests/unit/test_[name].c (verifies timing constraints)
- [ ] T020 [P] [US2] Safety validation test for [fault condition] in tests/safety/test_[name].c

### Implementation for User Story 2

- [ ] T021 [P] [US2] Implement [motor control function] in Core/Src/[motor_control].c (with timing validation)
- [ ] T022 [US2] Implement [safety mechanism] in Core/Src/[safety].c (with fault detection)
- [ ] T023 [US2] Integrate with User Story 1 components (if needed) ensuring no timing conflicts

**Checkpoint**: At this point, User Stories 1 AND 2 should both work independently with timing and safety compliance verified

---

## Phase 5: User Story 3 - [Title] (Priority: P3)

**Goal**: [Brief description of what this story delivers with timing and safety focus]

**Independent Test**: [How to verify this story works on its own with timing and safety validation]

### Tests for User Story 3 (OPTIONAL - only if tests requested) ⚠️

- [ ] T024 [P] [US3] Unit test for [timing-critical function] in tests/unit/test_[name].c (verifies timing constraints)
- [ ] T025 [P] [US3] Safety validation test for [fault condition] in tests/safety/test_[name].c

### Implementation for User Story 3

- [ ] T026 [P] [US3] Implement [motor control function] in Core/Src/[motor_control].c (with timing validation)
- [ ] T027 [US3] Implement [safety mechanism] in Core/Src/[safety].c (with fault detection)

**Checkpoint**: All user stories should now be independently functional with timing and safety compliance verified

---

[Add more user story phases as needed, following the same pattern]

---

## Phase N: Polish & Cross-Cutting Concerns

**Purpose**: Improvements that affect multiple user stories

- [ ] TXXX [P] Documentation updates in docs/ with timing and safety requirements
- [ ] TXXX Code cleanup and refactoring ensuring timing compliance is maintained
- [ ] TXXX Performance optimization across all stories with timing validation
- [ ] TXXX [P] Additional unit tests (if requested) in tests/unit/ with timing and safety validation
- [ ] TXXX Security and safety hardening review
- [ ] TXXX Run quickstart.md validation ensuring all constraints are met
- [ ] TXXX Full system integration testing with timing, safety and hardware constraint verification

---

## Dependencies & Execution Order

### Phase Dependencies

- **Setup (Phase 1)**: No dependencies - can start immediately
- **Foundational (Phase 2)**: Depends on Setup completion - BLOCKS all user stories
- **User Stories (Phase 3+)**: All depend on Foundational phase completion
  - User stories can then proceed in parallel (if staffed)
  - Or sequentially in priority order (P1 → P2 → P3)
- **Polish (Final Phase)**: Depends on all desired user stories being complete

### User Story Dependencies

- **User Story 1 (P1)**: Can start after Foundational (Phase 2) - No dependencies on other stories
- **User Story 2 (P2)**: Can start after Foundational (Phase 2) - May integrate with US1 but should be independently testable
- **User Story 3 (P3)**: Can start after Foundational (Phase 2) - May integrate with US1/US2 but should be independently testable

### Within Each User Story

- Tests (if included) MUST be written and FAIL before implementation
- Safety-critical components before functional components
- Timing-critical functions before integration
- Core implementation before integration
- All safety validations complete before story completion
- All timing validations complete before story completion
- All hardware constraint validations complete before story completion
- Story complete before moving to next priority

### Parallel Opportunities

- All Setup tasks marked [P] can run in parallel
- All Foundational tasks marked [P] can run in parallel (within Phase 2)
- Once Foundational phase completes, all user stories can start in parallel (if team capacity allows)
- All tests for a user story marked [P] can run in parallel
- Functions within a story marked [P] can run in parallel
- Different user stories can be worked on in parallel by different team members

---

## Parallel Example: User Story 1

```bash
# Launch all tests for User Story 1 together (if tests requested):
Task: "Unit test for [timing-critical function] in tests/unit/test_[name].c (verifies timing constraints)"
Task: "Safety validation test for [fault condition] in tests/safety/test_[name].c"

# Launch all functions for User Story 1 together:
Task: "Implement [motor control function] in Core/Src/[motor_control].c (with timing validation)"
Task: "Create [safety mechanism] in Core/Src/[safety].c (with fault detection)"
```

---

## Implementation Strategy

### MVP First (User Story 1 Only)

1. Complete Phase 1: Setup
2. Complete Phase 2: Foundational (CRITICAL - blocks all stories, defines all constraints)
3. Complete Phase 3: User Story 1
4. **STOP and VALIDATE**: Test User Story 1 independently with timing and safety validation
5. Deploy/demo if ready

### Incremental Delivery

1. Complete Setup + Foundational → Foundation ready with all constraints defined
2. Add User Story 1 → Test independently with timing/safety validation → Deploy/Demo (MVP!)
3. Add User Story 2 → Test independently with timing/safety validation → Deploy/Demo
4. Add User Story 3 → Test independently with timing/safety validation → Deploy/Demo
5. Each story adds value without breaking previous stories or violating constraints

### Parallel Team Strategy

With multiple developers:

1. Team completes Setup + Foundational together (especially constraint definitions)
2. Once Foundational is done:
   - Developer A: User Story 1
   - Developer B: User Story 2
   - Developer C: User Story 3
3. Stories complete and integrate independently, all with compliance verification

---

## Notes

- [P] tasks = different files, no dependencies
- [Story] label maps task to specific user story for traceability
- Each user story should be independently completable and testable
- Verify tests fail before implementing
- Commit after each task or logical group
- Stop at any checkpoint to validate story independently with timing and safety compliance
- Avoid: vague tasks, same file conflicts, cross-story dependencies that break independence
- CRITICAL: All timing-critical code must be validated against timing constraints
- CRITICAL: All safety-critical code must be validated with safety tests
- CRITICAL: All hardware resources must be validated against constraints
- CRITICAL: Before completion, each story must be verified to not violate any constitution principles



