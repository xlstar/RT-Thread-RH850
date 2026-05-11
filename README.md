# RH850 RT-Thread Nano 移植工程

> 面向 **Renesas RH850 G3KH** 平台的 **RT-Thread Nano** 移植参考工程，使用 **Renesas CS+ / CC-RH** 工具链构建。

## 目录

- [项目简介](#项目简介)
- [主要特性](#主要特性)
- [目录结构](#目录结构)
- [开发环境](#开发环境)
- [快速开始](#快速开始)
- [RT-Thread 移植说明](#rt-thread-移植说明)
- [系统 Tick 说明](#系统-tick-说明)
- [示例任务说明](#示例任务说明)
- [已知限制](#已知限制)
- [开源与版权注意事项](#开源与版权注意事项)
- [推荐 `.gitignore`](#推荐-gitignore)
- [免责声明](#免责声明)

## 项目简介

本项目是一个面向 **Renesas RH850 G3KH 内核平台** 的 RT-Thread Nano 移植参考工程，主要用于 RH850 平台 RTOS 移植学习、功能验证和二次开发参考。

工程重点演示以下内容：

- RH850 G3KH 平台上的 RT-Thread Nano 启动流程；
- 线程栈初始化与上下文切换；
- 基于 `TRAP0` 的软件中断线程切换；
- 使用 `OSTM0` 作为 RT-Thread 系统 tick；
- EIINT 表引用方式下的 tick 中断接入；
- 1 ms、5 ms、10 ms、20 ms 周期任务示例。

## 主要特性

| 模块 | 说明 |
|---|---|
| CPU 架构 | RH850 |
| CPU 内核 | G3KH |
| RTOS | RT-Thread Nano |
| 工具链 | Renesas CS+ / CC-RH |
| 系统 Tick | OSTM0 |
| 上下文切换 | `TRAP0` + 汇编保存/恢复上下文 |
| 中断方式 | EIINT 表引用方式 |
| 示例任务 | 1 ms / 5 ms / 10 ms / 20 ms 周期任务 |

## 目录结构

```text
RH850_RT_Thread_260511_V1.1_ReleaseGithub/
├── SourceFile/
│   ├── System/
│   │   └── Driver/
│   │       ├── cg_src/              # Renesas Code Generator / Smart Configurator 生成的外设初始化代码
│   │       └── startup/             # RH850 启动文件、向量表、iodefine、类型定义等
│   └── rtthread/
│       ├── board.c                  # 板级初始化、OSTM0 tick 初始化
│       ├── rtconfig.h               # RT-Thread Nano 配置文件
│       ├── rtthread_main.c          # 示例任务、软件定时器和信号量初始化
│       ├── core/                    # RT-Thread Nano 内核源码
│       └── libcpu/rh850/ccrh/       # RH850 / CC-RH CPU 移植层
│           ├── cpuport.c            # 栈初始化、CPU/中断基础接口
│           └── context_ccrh.asm     # 上下文保存/恢复、TRAP0、tick 中断封装
├── Toolchain/
│   └── RH850_F1K_F1Kx_G3KH_RT_Thread.mtpj  # CS+ 工程文件
├── doc/
│   └── RH850G3KH_RTOS_Porting_Guide.md     # RH850 G3KH RTOS 移植说明文档
├── README.md                        # 中文说明文档
├── README_en.md                     # English README
├── LICENSE                          # 开源许可证
├── NOTICE                           # 第三方代码与厂商文件声明
└── .gitignore                       # Git 忽略规则
```

## 开发环境

推荐环境如下：

| 项目 | 推荐配置 |
|---|---|
| IDE | Renesas CS+ |
| 编译器 | Renesas CC-RH |
| 目标平台 | RH850 G3KH 系列 MCU / 开发板 |
| Device File | 与实际芯片型号匹配的 Renesas Device File |
| 调试器 | E2 / E2 Lite / J-Link 等，按实际硬件选择 |

当前工程文件中可见的关键信息：

```text
CPU architecture : RH850
CPU core family  : G3KH
Toolchain        : CC-RH
CS+ project file : Toolchain/RH850_F1K_F1Kx_G3KH_RT_Thread.mtpj
```

> **注意**  
> 请根据实际芯片型号、外设配置、时钟配置、中断向量配置、链接 section 分配和调试器配置重新检查 CS+ 工程设置。

## 快速开始

1. 安装 **Renesas CS+** 和 **CC-RH** 工具链。
2. 使用 CS+ 打开工程文件：

   ```text
   Toolchain/RH850_F1K_F1Kx_G3KH_RT_Thread.mtpj
   ```

3. 检查以下工程设置是否与实际硬件一致：

   - Device / MCU 型号；
   - Clock / CGC 配置；
   - OSTM0 时钟源和分频；
   - EIINT 向量表地址和中断通道；
   - 链接脚本 / section 分配；
   - 调试器和下载配置。

4. 编译工程。
5. 下载到目标板运行。
6. 如果启用控制台输出，可观察 RT-Thread 版本信息以及示例任务计数输出。

## RT-Thread 移植说明

本移植层主要涉及以下文件：

### `SourceFile/rtthread/rtconfig.h`

RT-Thread Nano 配置文件，主要定义：

- 线程优先级数量；
- tick 频率；
- 堆大小；
- IPC 组件；
- 其他内核配置项。

### `SourceFile/rtthread/board.c`

板级初始化文件，主要完成：

- `rt_hw_interrupt_init()`；
- `rt_system_heap_init()`；
- OSTM0 tick 定时器初始化；
- OSTM0 tick 中断请求清除；
- `rt_tick_increase()` 调用。

### `SourceFile/rtthread/libcpu/rh850/ccrh/cpuport.c`

RH850 CPU 相关接口，主要完成：

- `rt_hw_stack_init()`；
- `rt_hw_interrupt_init()`；
- `rt_hw_cpu_reset()`；
- `rt_hw_cpu_shutdown()`；
- `rt_hw_us_delay()`；
- cache / exception 基础接口占位实现。

### `SourceFile/rtthread/libcpu/rh850/ccrh/context_ccrh.asm`

RH850 / CC-RH 汇编上下文切换实现，主要包括：

- `rt_hw_interrupt_disable()`；
- `rt_hw_interrupt_enable()`；
- `rt_hw_context_switch()`；
- `rt_hw_context_switch_to()`；
- `rt_hw_context_switch_interrupt()`；
- `__rtthread_trap0_handler()`；
- `__rtthread_tick_handler()`。

### `SourceFile/System/Driver/startup/boot.asm`

RH850 启动向量表文件。当前参考工程中，`TRAP0` 和 `OSTM0 / EIINT_CH84` 已接入 RT-Thread 相关处理函数。

## 系统 Tick 说明

当前工程默认使用 **OSTM0** 作为 RT-Thread 系统 tick 定时器。

相关配置文件：

```text
SourceFile/rtthread/board.c
```

默认宏定义：

| 宏 | 默认值 | 说明 |
|---|---:|---|
| `RT_HW_CPU_CLOCK_HZ` | 240 MHz | CPU 主频 |
| `RT_HW_OSTM_PCLK_DIV` | 4 | OSTM 外设时钟分频 |
| `RT_TICK_PER_SECOND` | 1000 | RT-Thread tick 频率 |
| `RT_HW_OSTM0_INT_PRIORITY` | 14 | OSTM0 中断优先级 |

如果实际工程的主频、外设时钟分频或中断优先级不同，请同步修改这些宏定义和 CS+ 外设配置。

## 示例任务说明

`SourceFile/rtthread/rtthread_main.c` 中创建了 4 个示例周期任务：

| 任务名 | 周期 | 说明 |
|---|---:|---|
| `task_1ms` | 1 ms | 1 ms 周期任务 |
| `task_5ms` | 5 ms | 5 ms 周期任务 |
| `task_10ms` | 10 ms | 10 ms 周期任务 |
| `task_20ms` | 20 ms | 20 ms 周期任务 |

实现方式：

1. 周期软件定时器定时释放信号量；
2. 对应任务阻塞等待信号量；
3. 收到信号量后执行周期任务逻辑。

这些任务主要用于验证 RT-Thread 调度、tick、软件定时器和 IPC 机制是否正常工作。实际项目中可以替换为自己的应用任务。

## 已知限制

- 当前工程是参考移植工程，并不是完整 RH850 BSP。
- 默认未启用 UART 控制台 BSP，`rt_kprintf` 的实际输出需要根据目标板补充 console 驱动。
- cache、interrupt install / mask / unmask 等接口目前为最小占位实现，复杂项目需要进一步完善。
- `OSTM0`、`EIINT_CH84`、`TRAP0` 的使用与当前工程配置绑定，移植到其他 RH850 型号时需要重新核对向量号和寄存器定义。
- 当前工程中的外设初始化代码与目标芯片型号、引脚、时钟配置强相关，不能直接保证适用于所有 RH850 G3KH 芯片。
- 若启用 FPU、MPU、用户态 / 特权态切换，需要结合 RH850 G3KH 手册进一步验证 `PSW`、`FPSR`、`FPEPC`、MPU 区域权限和异常返回流程。

## 开源与版权注意事项

本工程包含多类来源代码。公开发布到 GitHub 或再次分发前，请务必确认授权边界。

### RT-Thread Nano 内核源码

RT-Thread 相关文件头部包含 `SPDX-License-Identifier: Apache-2.0`。发布时应保留原始版权声明，并在仓库根目录保留 `LICENSE` 文件。

### 项目自有 RH850 移植代码

除非单个文件另有说明，本项目中自有的 RH850 / CC-RH 移植代码、示例代码和文档按 Apache License 2.0 发布。

### Renesas 生成或提供的文件

以下目录可能包含 Renesas Code Generator / Smart Configurator 生成代码、启动文件、`iodefine.h` 和类型定义文件：

```text
SourceFile/System/Driver/cg_src/
SourceFile/System/Driver/startup/
```

这些文件应继续遵循 Renesas Electronics Corporation 自身的版权声明、免责声明和许可限制。本项目不会将 Renesas 所有的材料重新授权为 Apache License 2.0。

> 如果不确定这些文件是否允许公开再分发，建议只公开 RT-Thread RH850 移植层，并在文档中说明用户需要通过 Renesas 官方工具自行生成启动和外设初始化代码。

### 第三方派生代码

RT-Thread 内核中的部分内存管理实现保留了 lwIP、DragonFly BSD 等来源的版权声明。请保留对应文件头部声明，并参考 `NOTICE` 文件中的说明。

## 推荐 `.gitignore`

建议仓库根目录添加 `.gitignore`，用于排除 CS+ / CC-RH 构建产物和临时文件：

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

## 免责声明

本工程仅作为 RH850 平台 RT-Thread Nano 移植参考示例提供。使用者需要根据实际硬件、芯片型号、时钟、外设、中断、编译器版本、MPU/FPU 配置和安全需求进行充分验证。

本软件按“现状”提供，不提供任何明示或暗示担保。项目作者和贡献者不对因使用本工程产生的任何直接或间接问题负责。
