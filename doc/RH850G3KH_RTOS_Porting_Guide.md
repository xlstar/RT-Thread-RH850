# RH850G3KH 移植 RTOS 指导操作手册  
适用对象：RH850G3KH + CS+ / CC-RH + RT-Thread Nano 或类似小型 RTOS 移植工程

---

## 0. 移植目标

本文说明如何根据 RH850G3KH 内核软件手册，将 RTOS 移植到 RH850 平台，并说明它与 ARM Cortex-M 系列 RTOS 移植方式的关键差异。

本移植关注以下内容：

1. 启动流程  
2. 异常 / 中断向量  
3. 第一个线程启动  
4. 普通线程上下文切换  
5. 中断中线程切换  
6. 系统 tick  
7. PSW / EIPC / EIPSW / TRAP0  
8. FPU 与系统寄存器 hazard  
9. 与 ARM Cortex-M 的差异  

---

## 1. RH850G3KH RTOS 移植核心原则

RH850G3KH 移植 RTOS 时，最重要的一点是：

**RH850G3KH 在异常和中断入口不会像 ARM Cortex-M 那样自动把一组通用寄存器压入线程栈。**

RH850G3KH 的 EI level 异常主要由硬件保存：

```text
EIPC   = 异常发生前的 PC
EIPSW  = 异常发生前的 PSW
EIIC   = 异常原因码
EIWR   = EI level 工作寄存器
```

FE level 异常则对应：

```text
FEPC
FEPSW
FEIC
FEWR
```

因此，RTOS port 必须由软件显式保存和恢复通用寄存器。

对于 RT-Thread Nano，最关键的移植函数是：

```c
rt_hw_stack_init()
rt_hw_context_switch_to()
rt_hw_context_switch()
rt_hw_context_switch_interrupt()
rt_hw_interrupt_disable()
rt_hw_interrupt_enable()
```

---

## 2. 启动流程设计

### 2.1 当前裸机 main 调用 rtthread_startup 的流程

如果工程当前是裸机环境启动，然后在 `main()` 中调用 `rtthread_startup()`，流程应为：

```text
复位
  ↓
boot.asm
  ↓
cstart.asm
  ↓
main()
  ↓
rtthread_startup()
  ↓
rt_system_scheduler_start()
  ↓
rt_hw_context_switch_to()
  ↓
进入第一个 RT-Thread 线程
```

这种方式是可行的，但要注意 RT-Thread 的 `RT_USING_USER_MAIN` 配置。

---

### 2.2 避免 main 递归启动

如果 `rtconfig.h` 中打开：

```c
#define RT_USING_USER_MAIN
```

RT-Thread 启动后可能会创建一个 main 线程，并在 main 线程中再次调用 `main()`。

如果裸机 `main()` 里已经调用了 `rtthread_startup()`，就可能形成：

```text
裸机 main()
  ↓
rtthread_startup()
  ↓
RT-Thread main 线程
  ↓
再次调用 main()
  ↓
再次 rtthread_startup()
```

这会导致重复启动或跑飞。

推荐改法：

```c
int main(void)
{
    rtthread_startup();

    while (1)
    {
    }
}
```

然后 RTOS 中真正运行的用户线程入口不要再叫 `main()`，可以改成：

```c
int user_main(void)
{
    while (1)
    {
        rt_thread_mdelay(1000);
    }
}
```

如果使用 RT-Thread 的 `main_thread_entry()`，则把其中调用 `main()` 的位置改成调用 `user_main()`。

---

## 3. 异常和中断基础

RH850G3KH 有两个重要异常层级：

```text
EI level exception
FE level exception
```

RTOS 常用的普通外部中断、TRAP0、系统 tick 一般走 EI level。

EI level 异常返回必须使用：

```asm
eiret
```

`eiret` 会从 `EIPC` 和 `EIPSW` 恢复 PC 和 PSW。

因此，RTOS 恢复线程时，通常不是使用：

```asm
jmp [lp]
```

而是使用：

```asm
ldsr    rX, EIPSW
ldsr    rY, EIPC
eiret
```

---

## 4. 线程栈初始化

### 4.1 `rt_hw_stack_init()` 的作用

`rt_hw_stack_init()` 要人工构造一个线程初始栈，使得后续 `_rt_hw_context_restore` 可以像“从异常返回”一样进入线程入口函数。

栈中至少应包含：

```text
EIPC   = 线程入口函数 entry
EIPSW  = 初始 PSW
r6     = parameter
r31/lp = rt_thread_exit 或兜底函数
其他通用寄存器初始值
```

### 4.2 推荐初始 PSW

建议初始线程 PSW 默认设置为：

```text
UM  = 0    supervisor mode
ID  = 0    允许 EI level maskable interrupt
EP  = 0
NP  = 0
CU0 = 0    默认不打开 FPU
```

默认不建议打开 `PSW.CU0`，除非已经实现 FPU 系统寄存器上下文保存。

---

## 5. 三类上下文切换

RTOS 移植时必须区分三种切换：

```text
1. 第一次启动线程
2. 普通线程态切换
3. 中断态切换
```

这三种切换不能混用。

---

### 5.1 第一次启动线程：`rt_hw_context_switch_to`

第一次启动线程时，没有当前线程可以保存，所以不能触发 TRAP0。

正确逻辑：

```asm
_rt_hw_context_switch_to:
    ld.w    0[r6], sp
    br      _rt_hw_context_restore
```

含义：

```text
加载第一个线程的 sp
  ↓
从第一个线程人工构造的栈中恢复寄存器
  ↓
恢复 EIPC / EIPSW
  ↓
eiret
  ↓
进入第一个线程入口函数
```

结论：

```text
rt_hw_context_switch_to 不需要，也不应该显式触发 TRAP0。
```

---

### 5.2 普通线程态切换：`rt_hw_context_switch`

普通线程态切换需要触发 TRAP0。

典型逻辑：

```asm
_rt_hw_context_switch:
    mov     #_rt_interrupt_from_thread, r10
    st.w    r6, 0[r10]

    mov     #_rt_interrupt_to_thread, r10
    st.w    r7, 0[r10]

    trap    0
    jmp     [lp]
```

说明：

```text
rt_hw_context_switch()
  只记录 from / to
  然后触发 trap 0
```

真正保存和恢复上下文的工作应放在 TRAP0 handler 中。

---

### 5.3 TRAP0 handler

TRAP0 handler 才是真正的普通线程态上下文切换入口。

它应完成：

```text
1. 保存当前线程通用寄存器
2. 保存 EIPC / EIPSW
3. 保存当前 sp 到 from_thread->sp
4. 加载 to_thread->sp
5. 恢复目标线程上下文
6. eiret 返回目标线程
```

注意：

```text
rt_hw_context_switch() 里不要再保存完整上下文。
TRAP0 handler 里也不要再次触发 trap。
```

否则会出现双重压栈，导致栈帧恢复错位。

---

### 5.4 中断态切换：`rt_hw_context_switch_interrupt`

中断态切换不需要触发 TRAP0。

正确思路：

```text
OSTM0 / EIINT 中断进入
  ↓
硬件保存 EIPC / EIPSW
  ↓
中断 wrapper 保存通用寄存器
  ↓
rt_tick_increase()
  ↓
rt_hw_context_switch_interrupt(from, to)
  ↓
只记录 from / to / switch_flag
  ↓
中断退出前检查 switch_flag
  ↓
如需切换，则保存当前 sp，加载目标线程 sp
  ↓
eiret 返回目标线程
```

结论：

```text
rt_hw_context_switch_interrupt 不需要，也不应该触发 TRAP0。
```

原因是：中断已经处在 EI level 异常环境中。如果再触发 TRAP0，会复用 EI level 的 EIPC / EIPSW，容易污染当前中断现场。

---

## 6. 中断向量表和系统 tick

RH850G3KH 支持两种中断向量方式：

```text
direct vector method
table reference method
```

如果使用 table reference method，则中断入口地址来自：

```text
INTBP + channel_number × 4
```

例如 OSTM0 若为 EIINT channel 84，则表项位置为：

```text
INTBP + 84 × 4
```

该表项内容应指向 tick handler：

```asm
.long __rtthread_tick_handler
```

同时需要在具体芯片的 INTC 寄存器中设置该通道使用 table reference 模式。

注意：

```text
RH850G3KH 内核软件手册只说明 CPU 内核异常机制。
具体 OSTM0 通道号、INTC 寄存器地址、ICOSTM0 位定义必须看具体芯片硬件手册。
```

---

## 7. 系统 tick 设计

通常使用 OSTM0 作为 RTOS tick。

tick handler 应完成：

```text
1. 清 OSTM0 中断标志
2. 保存当前线程上下文
3. 调用 rt_tick_increase()
4. 如果调度器请求线程切换，则切换 sp
5. 恢复目标线程上下文
6. eiret
```

tick 中断里不要再执行：

```asm
trap 0
```

---

## 8. 中断开关实现

RTOS 需要实现：

```c
rt_base_t rt_hw_interrupt_disable(void);
void rt_hw_interrupt_enable(rt_base_t level);
```

RH850 上一般通过 `PSW.ID` 控制 EI level maskable interrupt。

推荐原则：

```text
disable:
    保存旧 PSW
    关闭中断
    返回旧 PSW

enable:
    恢复旧 PSW 的中断状态
```

不要简单粗暴地在 enable 中直接 `ei`，否则会破坏 RTOS 临界区嵌套。

---

## 9. FPU 处理

RH850G3KH 的 FPU 与 ARM Cortex-M 的 FPU 不同。

RH850G3KH FPU 使用通用寄存器参与浮点运算，同时还有以下 FPU 系统寄存器：

```text
FPSR
FPEPC
FPST
FPCC
FPCFG
FPEC
```

如果线程中使用硬件浮点，则要考虑：

```text
1. 是否打开 PSW.CU0
2. 是否按线程保存 / 恢复 FPU 系统寄存器
3. 修改 PSW.CU0 或 FPU 系统寄存器后是否执行同步指令
```

建议初版移植时：

```text
默认不打开 PSW.CU0。
默认禁止硬件浮点上下文切换。
```

如果后续必须使用 FPU，再补充 FPU 系统寄存器保存恢复。

---

## 10. 系统寄存器 hazard

RH850G3KH 对系统寄存器访问有 hazard 要求。

常见注意点：

```text
1. 修改 PSW 后，需要考虑同步。
2. 修改 PSW.CU0 后，后续若执行浮点指令，需要执行 syncp / synci / eiret / feret 之一。
3. 修改 FPU 系统寄存器后，建议执行 syncp。
4. 进入线程时通过 eiret 恢复 PSW，比直接 ldsr PSW 后继续执行更安全。
```

示例：

```asm
ldsr    r10, PSW
syncp
```

或者：

```asm
ldsr    r10, EIPSW
ldsr    r11, EIPC
eiret
```

---

## 11. 与 ARM Cortex-M RTOS 移植差异

| 对比项 | RH850G3KH | ARM Cortex-M |
|---|---|---|
| 软件触发上下文切换 | 通常用 TRAP0 | 通常用 PendSV |
| 系统 tick | OSTM / TAUJ 等外设定时器 | SysTick 常用 |
| 异常入口硬件保存 | 保存 EIPC / EIPSW 等，通用寄存器主要靠软件保存 | 自动压栈 R0-R3、R12、LR、PC、xPSR |
| 异常返回 | EIRET / FERET | EXC_RETURN |
| 中断控制器 | RH850 INTC，通道可 direct/table | NVIC |
| 第一个线程启动 | 人工构造 EIPC/EIPSW 栈帧，然后 EIRET | 常用 SVC 或直接构造异常栈帧 |
| 普通线程态切换 | rt_hw_context_switch → trap 0 → TRAP0 handler | 设置 PendSV pending → PendSV_Handler |
| 中断态切换 | ISR 尾部根据 switch_flag 切换 sp，不再 trap | SysTick 中 pend PendSV，退出后 PendSV 切换 |
| FPU 上下文 | FPU 依赖通用寄存器，并有 FPU 系统寄存器 | Cortex-M4/M7/M33 有 S 寄存器，涉及 lazy stacking |
| 特权模式 | supervisor / user mode，PSW.UM 控制 | Thread mode / Handler mode，部分型号支持 MPU/TrustZone |

---

## 12. ARM Cortex-M 的典型 RTOS 切换流程

Cortex-M 常见流程：

```text
SysTick_Handler
  ↓
rt_tick_increase()
  ↓
如果需要调度，设置 PendSV pending
  ↓
退出 SysTick
  ↓
PendSV_Handler 执行上下文切换
```

PendSV 被设计成最低优先级异常，适合延后执行上下文切换。

而 RH850G3KH 上没有 Cortex-M 风格的 PendSV，所以普通线程态切换可以使用 TRAP0，中断态切换则在 ISR wrapper 尾部完成。

---

## 13. RH850 移植验证顺序

建议按以下顺序验证：

```text
1. 裸机 main 可以运行
2. main 中调用 rtthread_startup
3. rtthread_startup 能进入 rt_system_scheduler_start
4. rt_hw_context_switch_to 能进入第一个线程
5. 第一个线程能执行 while 循环
6. OSTM0 tick 能正常进入
7. rt_tick_increase 正常增加 tick
8. rt_thread_mdelay 能阻塞当前线程
9. 中断态切换能在 tick handler 尾部完成
10. 线程态 rt_thread_yield 能触发 TRAP0
11. TRAP0 handler 能保存 from，恢复 to
12. eiret 后进入目标线程
13. 中断开关嵌套正常
14. 如启用 FPU，再单独验证 FPU 上下文
```

---

## 14. 最关键结论

```text
第一次启动线程：
    rt_hw_context_switch_to
    不触发 TRAP0
    直接加载第一个线程 sp，然后 eiret

普通线程态切换：
    rt_hw_context_switch
    需要触发 TRAP0

中断态切换：
    rt_hw_context_switch_interrupt
    不触发 TRAP0
    只设置 from / to / switch_flag
    在 ISR 尾部完成切换

所有线程恢复：
    最终通过 EIRET 返回线程
```

这是 RH850G3KH RTOS 移植时最容易混淆、也最容易出 BUG 的地方。

---

## 15. CS+ / CC-RH 工程检查点

在 CS+ 工程中建议检查：

```text
1. boot.asm 是否定义 RESET 向量
2. TRAP0 向量是否跳转到 __rtthread_trap0_handler
3. OSTM0 EIINT 表项是否跳转到 __rtthread_tick_handler
4. INTBP 是否设置到 EIINT table 地址
5. EBASE 是否设置正确
6. OSTM0 中断通道是否选择 table reference
7. rt_hw_context_switch_to 是否不触发 trap
8. rt_hw_context_switch 是否触发 trap 0
9. rt_hw_context_switch_interrupt 是否不触发 trap
10. _rt_hw_context_restore 是否以 eiret 结束
11. rtconfig.h 中是否避免 main 递归启动
12. 默认是否关闭 PSW.CU0
13. 如果打开 FPU，是否保存 FPU 系统寄存器
14. 链接段 RESET / EIINTTBL / text / data / bss / stack 是否正确
```

---

## 16. 常见错误与排查

### 错误 1：启动第一个线程时看不到 TRAP0

这是正常现象。

第一个线程启动走：

```text
rt_hw_context_switch_to → restore → eiret
```

不走 TRAP0。

---

### 错误 2：线程态 yield 看不到 TRAP0

检查：

```text
1. rt_hw_context_switch 是否执行 trap 0
2. TRAP0 向量是否指向 __rtthread_trap0_handler
3. TRAP 指令写法是否被 CC-RH 接受
4. 是否实际发生了线程态切换
```

推荐写法：

```asm
trap    0
```

---

### 错误 3：中断里触发 TRAP0 后跑飞

中断里不应该再触发 TRAP0。

中断态切换应该在 ISR 尾部完成。

---

### 错误 4：开 FPU 后随机跑飞

可能原因：

```text
1. PSW.CU0 打开后没有 syncp
2. 没有保存 FPSR / FPEPC 等 FPU 系统寄存器
3. 多线程同时使用浮点，但没有 FPU 上下文管理
```

初版建议关闭硬件 FPU。

---

### 错误 5：main 反复进入

检查是否出现：

```text
裸机 main 调 rtthread_startup
RT-Thread main 线程又调用 main
```

如果是，需要把 RTOS 用户入口改名为 `user_main()`。

---

## 17. 推荐最终结构

```text
startup/
    boot.asm
    cstart.asm

libcpu/rh850/ccrh/
    context_ccrh.asm
    cpuport.c

board/
    board.c

applications/
    main.c 或 user_main.c

docs/
    RH850G3KH_RTOS_Porting_Guide.md
```

关键函数归属：

```text
context_ccrh.asm:
    rt_hw_context_switch_to
    rt_hw_context_switch
    rt_hw_context_switch_interrupt
    __rtthread_trap0_handler
    __rtthread_tick_handler
    _rt_hw_context_restore

cpuport.c:
    rt_hw_stack_init
    rt_hw_interrupt_disable
    rt_hw_interrupt_enable

board.c:
    rt_hw_board_init
    OSTM0 初始化
    heap 初始化
```

---

## 18. 一句话总结

RH850G3KH 移植 RTOS 的关键不是简单照搬 ARM Cortex-M 的 PendSV/SysTick 模型，而是围绕：

```text
EIPC / EIPSW / EIRET / TRAP0 / EIINT / PSW
```

重新设计线程恢复和上下文切换流程。

正确分工是：

```text
context_switch_to：第一次进线程，不 TRAP
context_switch：线程态切换，TRAP0
context_switch_interrupt：中断态切换，不 TRAP
restore：统一 EIRET 返回
```
