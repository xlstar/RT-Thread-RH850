# RH850 RT-Thread Nano Porting Project

> A reference **RT-Thread Nano** porting project for the **Renesas RH850 G3KH** platform, built with the **Renesas CS+ / CC-RH** toolchain.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Directory Structure](#directory-structure)
- [Development Environment](#development-environment)
- [Quick Start](#quick-start)
- [RT-Thread Porting Notes](#rt-thread-porting-notes)
- [System Tick](#system-tick)
- [Sample Tasks](#sample-tasks)
- [Known Limitations](#known-limitations)
- [Open Source and License Notes](#open-source-and-license-notes)
- [Recommended `.gitignore`](#recommended-gitignore)
- [Disclaimer](#disclaimer)

## Overview

This project is a reference RT-Thread Nano porting project for the **Renesas RH850 G3KH** platform. It is mainly intended for RH850 RTOS porting study, functional verification, and secondary development reference.

The project demonstrates:

- RT-Thread Nano startup flow on RH850 G3KH;
- thread stack initialization and context switching;
- `TRAP0`-based software interrupt for thread context switching;
- `OSTM0` as the RT-Thread system tick timer;
- EIINT table-reference interrupt integration for the tick interrupt;
- 1 ms, 5 ms, 10 ms, and 20 ms periodic task examples.

## Features

| Item | Description |
|---|---|
| CPU architecture | RH850 |
| CPU core | G3KH |
| RTOS | RT-Thread Nano |
| Toolchain | Renesas CS+ / CC-RH |
| System tick | OSTM0 |
| Context switch | `TRAP0` plus assembly context save/restore |
| Interrupt mode | EIINT table-reference mode |
| Sample tasks | 1 ms / 5 ms / 10 ms / 20 ms periodic tasks |

## Directory Structure

```text
RH850_RT_Thread_260511_V1.1_ReleaseGithub/
├── SourceFile/
│   ├── System/
│   │   └── Driver/
│   │       ├── cg_src/              # Renesas Code Generator / Smart Configurator peripheral code
│   │       └── startup/             # RH850 startup files, vector table, iodefine, and type definitions
│   └── rtthread/
│       ├── board.c                  # Board initialization and OSTM0 tick initialization
│       ├── rtconfig.h               # RT-Thread Nano configuration
│       ├── rtthread_main.c          # Sample tasks, software timers, and semaphores
│       ├── core/                    # RT-Thread Nano kernel source code
│       └── libcpu/rh850/ccrh/       # RH850 / CC-RH CPU porting layer
│           ├── cpuport.c            # Stack initialization and CPU/interrupt basic interfaces
│           └── context_ccrh.asm     # Context save/restore, TRAP0, and tick interrupt wrapper
├── Toolchain/
│   └── RH850_F1K_F1Kx_G3KH_RT_Thread.mtpj  # CS+ project file
├── doc/
│   └── RH850G3KH_RTOS_Porting_Guide.md     # RH850 G3KH RTOS porting guide
├── README.md                        # Chinese README
├── README_en.md                     # English README
├── LICENSE                          # License file
├── NOTICE                           # Third-party and vendor notice file
└── .gitignore                       # Git ignore rules
```

## Development Environment

Recommended environment:

| Item | Recommended configuration |
|---|---|
| IDE | Renesas CS+ |
| Compiler | Renesas CC-RH |
| Target platform | RH850 G3KH MCU / evaluation board |
| Device File | Renesas Device File matching the selected MCU |
| Debugger | E2 / E2 Lite / J-Link, depending on the actual hardware |

Key project information:

```text
CPU architecture : RH850
CPU core family  : G3KH
Toolchain        : CC-RH
CS+ project file : Toolchain/RH850_F1K_F1Kx_G3KH_RT_Thread.mtpj
```

> **Note**  
> Re-check the CS+ project settings according to your actual MCU model, peripheral configuration, clock configuration, interrupt vector configuration, linker section layout, and debugger setup.

## Quick Start

1. Install **Renesas CS+** and the **CC-RH** toolchain.
2. Open the following project file with CS+:

   ```text
   Toolchain/RH850_F1K_F1Kx_G3KH_RT_Thread.mtpj
   ```

3. Verify that the following settings match your target board:

   - Device / MCU model;
   - clock / CGC configuration;
   - OSTM0 clock source and divider;
   - EIINT vector table address and interrupt channel;
   - linker script / section layout;
   - debugger and download configuration.

4. Build the project.
5. Download it to the target board.
6. If console output is enabled, check the RT-Thread version banner and sample task counter output.

## RT-Thread Porting Notes

The main RT-Thread porting files are listed below.

### `SourceFile/rtthread/rtconfig.h`

RT-Thread Nano configuration file. It defines:

- thread priority count;
- tick frequency;
- heap size;
- IPC components;
- other kernel configuration options.

### `SourceFile/rtthread/board.c`

Board-level initialization file. It mainly provides:

- `rt_hw_interrupt_init()`;
- `rt_system_heap_init()`;
- OSTM0 tick timer initialization;
- OSTM0 tick interrupt request clearing;
- `rt_tick_increase()` invocation.

### `SourceFile/rtthread/libcpu/rh850/ccrh/cpuport.c`

RH850 CPU interface implementation. It mainly provides:

- `rt_hw_stack_init()`;
- `rt_hw_interrupt_init()`;
- `rt_hw_cpu_reset()`;
- `rt_hw_cpu_shutdown()`;
- `rt_hw_us_delay()`;
- placeholder cache and exception interfaces.

### `SourceFile/rtthread/libcpu/rh850/ccrh/context_ccrh.asm`

RH850 / CC-RH assembly context-switch implementation. It mainly includes:

- `rt_hw_interrupt_disable()`;
- `rt_hw_interrupt_enable()`;
- `rt_hw_context_switch()`;
- `rt_hw_context_switch_to()`;
- `rt_hw_context_switch_interrupt()`;
- `__rtthread_trap0_handler()`;
- `__rtthread_tick_handler()`.

### `SourceFile/System/Driver/startup/boot.asm`

RH850 startup vector table file. In the current reference project, `TRAP0` and `OSTM0 / EIINT_CH84` are connected to RT-Thread-related handlers.

## System Tick

The current project uses **OSTM0** as the RT-Thread system tick timer.

Related file:

```text
SourceFile/rtthread/board.c
```

Default macros:

| Macro | Default value | Description |
|---|---:|---|
| `RT_HW_CPU_CLOCK_HZ` | 240 MHz | CPU clock |
| `RT_HW_OSTM_PCLK_DIV` | 4 | OSTM peripheral clock divider |
| `RT_TICK_PER_SECOND` | 1000 | RT-Thread tick frequency |
| `RT_HW_OSTM0_INT_PRIORITY` | 14 | OSTM0 interrupt priority |

If your actual main clock, peripheral clock divider, or interrupt priority is different, update these macros and the CS+ peripheral configuration accordingly.

## Sample Tasks

`SourceFile/rtthread/rtthread_main.c` creates four sample periodic tasks:

| Task | Period | Description |
|---|---:|---|
| `task_1ms` | 1 ms | 1 ms periodic task |
| `task_5ms` | 5 ms | 5 ms periodic task |
| `task_10ms` | 10 ms | 10 ms periodic task |
| `task_20ms` | 20 ms | 20 ms periodic task |

Implementation method:

1. Periodic software timers release semaphores.
2. Corresponding tasks block on semaphores.
3. After a semaphore is received, the task executes its periodic logic.

These tasks are mainly used to verify RT-Thread scheduling, tick, software timer, and IPC mechanisms. Replace them with your own application tasks in a real project.

## Known Limitations

- This is a reference porting project, not a complete RH850 BSP.
- UART console BSP is not enabled by default. Actual `rt_kprintf` output requires a console driver for the target board.
- Cache, interrupt install / mask / unmask interfaces are currently minimal placeholder implementations and may need to be completed for complex projects.
- `OSTM0`, `EIINT_CH84`, and `TRAP0` usage is bound to the current project settings. Re-check vector numbers and register definitions when porting to another RH850 device.
- The peripheral initialization code is strongly related to the target MCU, pin assignment, and clock configuration. It is not guaranteed to work on all RH850 G3KH devices directly.
- If FPU, MPU, user mode, or privilege switching is enabled, further validation is required according to the RH850 G3KH manual, especially for `PSW`, `FPSR`, `FPEPC`, MPU region permissions, and exception return behavior.

## Open Source and License Notes

This package contains code from multiple origins. Before publishing it to GitHub or redistributing it publicly, verify the license boundary carefully.

### RT-Thread Nano kernel source code

RT-Thread-related source files contain `SPDX-License-Identifier: Apache-2.0`. Keep the original copyright headers and retain the root `LICENSE` file when redistributing or modifying them.

### Project-specific RH850 porting files

Unless otherwise stated in individual files, the project-specific RH850 / CC-RH porting files, sample code, and documentation are released under the Apache License 2.0.

### Renesas-generated or Renesas-supplied files

The following directories may contain Renesas Code Generator / Smart Configurator output, startup files, `iodefine.h`, and standard type definitions:

```text
SourceFile/System/Driver/cg_src/
SourceFile/System/Driver/startup/
```

These files retain their own Renesas Electronics Corporation copyright notices, disclaimers, and license restrictions. This project does not relicense Renesas-owned materials under the Apache License 2.0.

> If public redistribution is uncertain, consider publishing only the RT-Thread RH850 porting layer and asking users to generate Renesas startup and peripheral files by themselves with official Renesas tools.

### Third-party-derived code

Some RT-Thread memory-management files retain lwIP and DragonFly BSD-derived notices. Keep the original file headers and refer to the `NOTICE` file for details.

## Recommended `.gitignore`

A root `.gitignore` can exclude typical CS+ / CC-RH build outputs and temporary files:

```gitignore
# CS+ / CC-RH build outputs
*.abs
*.map
*.obj
*.clnk
*.mtud
*.ud
*.mot
*.hex
*.bin
*.srec
*.lst
*.bak
*.tmp

# Build directories
DefaultBuild/
Debug/
Release/
Build/
build/

# IDE / local settings
.vscode/
.idea/
.settings/
*.user
*.log

# OS files
.DS_Store
Thumbs.db
```

## Disclaimer

This project is provided only as a reference example for porting RT-Thread Nano to Renesas RH850 platforms. Users must fully validate the project according to their actual hardware, MCU model, clock configuration, peripheral setup, interrupt configuration, compiler version, MPU/FPU settings, and safety requirements.

The software is provided on an “AS IS” basis, without warranties or conditions of any kind, either express or implied. The authors and contributors shall not be liable for any direct or indirect issues caused by using this reference project.
