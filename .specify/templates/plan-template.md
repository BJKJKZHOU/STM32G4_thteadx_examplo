# Implementation Plan: [FEATURE]

**Branch**: `[###-feature-name]` | **Date**: [DATE] | **Spec**: [link]
**Input**: Feature specification from `/specs/[###-feature-name]/spec.md`

**Note**: This template is filled in by the `/speckit.plan` command. See `.specify/templates/commands/plan.md` for the execution workflow.

## Summary

[Extract from feature spec: primary requirement + technical approach from research]

## Technical Context

<!--
  ACTION REQUIRED: Replace the content in this section with the technical details
  for the project. The structure here is presented in advisory capacity to guide
  the iteration process.
-->

**Language/Version**: C for STM32 embedded development, GCC toolchain  
**Primary Dependencies**: STM32 HAL/LL drivers, CMSIS, FreeRTOS (if applicable)  
**Storage**: [if applicable, e.g., external flash, EEPROM or N/A]  
**Testing**: Unit tests with embedded test framework, hardware-in-the-loop testing  
**Target Platform**: STM32G474xx microcontroller  
**Project Type**: Embedded real-time motor control system  
**Performance Goals**: [domain-specific, e.g., FOC control loop <100μs, ADC sampling rate 10kHz, motor response time <10ms or NEEDS CLARIFICATION]  
**Constraints**: Memory usage <80% of available RAM/Flash, Real-time timing compliance, Safety-critical operation  
**Scale/Scope**: [domain-specific, e.g., PMSM motor control, 3-phase inverter control, encoder/sensor interfaces or NEEDS CLARIFICATION]

## Constitution Check

*GATE: Must pass before Phase 0 research. Re-check after Phase 1 design.*

* Verify all timing-critical functions meet specified timing constraints
* Confirm error handling and fault detection mechanisms are planned
* Validate hardware constraint compliance (memory, processing power, peripheral usage)
* Ensure safety-critical code will undergo appropriate testing and validation
* Verify motor control protection mechanisms (overcurrent, overtemperature, overvoltage) are included

## Project Structure

### Documentation (this feature)

```
specs/[###-feature]/
├── plan.md              # This file (/speckit.plan command output)
├── research.md          # Phase 0 output (/speckit.plan command)
├── data-model.md        # Phase 1 output (/speckit.plan command)
├── quickstart.md        # Phase 1 output (/speckit.plan command)
├── contracts/           # Phase 1 output (/speckit.plan command)
└── tasks.md             # Phase 2 output (/speckit.tasks command - NOT created by /speckit.plan)
```

### Source Code (repository root)
<!--
  ACTION REQUIRED: Replace the placeholder tree below with the concrete layout
  for this feature. Delete unused options and expand the chosen structure with
  real paths (e.g., apps/admin, packages/something). The delivered plan must
  not include Option labels.
-->

```
# STM32 PMSM FOC Motor Control Structure
Core/
├── Inc/                 # Header files
│   ├── main.h
│   ├── stm32g4xx_hal_conf.h
│   └── [feature-specific headers]
├── Src/                 # Source files
│   ├── main.c
│   ├── stm32g4xx_it.c
│   └── [feature-specific source files]
├── Startup/             # Startup files
│   └── startup_stm32g474xx.s
└── Utils/               # Utility functions
    └── [motor control utilities]

Drivers/
├── STM32G4xx_HAL_Driver/
└── CMSIS/

Middlewares/
├── Third_Party/         # Third-party components (if any)
└── ST/                  # ST-specific components

configs/
└── [configuration files for motor parameters, timing settings, etc.]

tests/
├── unit/                # Unit tests for algorithms
├── integration/         # Integration tests with hardware
└── system/              # System-level tests for safety and performance
```

**Structure Decision**: [Document the selected structure and reference the real
directories captured above]

## Complexity Tracking

*Fill ONLY if Constitution Check has violations that must be justified*

| Violation | Why Needed | Simpler Alternative Rejected Because |
|-----------|------------|-------------------------------------|
| [e.g., complex FOC algorithm] | [real-time control requirements] | [simpler control methods insufficient for PMSM] |
| [e.g., hardware-specific optimizations] | [performance requirements] | [generic code doesn't meet timing constraints] |

