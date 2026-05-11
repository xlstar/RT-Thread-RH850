; RT-Thread Nano RH850/CC-RH context switch port
; Register frame is compatible with the uploaded FreeRTOS RH850 portasm.asm style.

    .section ".text", text

    .extern _rt_os_tick_callback
    .extern _rt_interrupt_from_thread
    .extern _rt_interrupt_to_thread
    .extern _rt_thread_switch_interrupt_flag

    .public _rt_hw_interrupt_disable
    .public _rt_hw_interrupt_enable
    .public _rt_hw_context_switch
    .public _rt_hw_context_switch_to
    .public _rt_hw_context_switch_interrupt
    .public __rtthread_tick_handler
    .public __rtthread_trap0_handler

    EIPC  .set 0
    EIPSW .set 1
    PSW   .set 5
    FPSR  .set 6
    FPEPC .set 7


; rt_base_t rt_hw_interrupt_disable(void)
; return previous PSW in r10, then disable EI-level interrupts.
_rt_hw_interrupt_disable:
    stsr    PSW, r10, 0
    di
    jmp     [lp]

; void rt_hw_interrupt_enable(rt_base_t level)
; r6 = previous PSW returned by rt_hw_interrupt_disable().
_rt_hw_interrupt_enable:
    ldsr    r6, PSW, 0
    jmp     [lp]

; Common restore path.
; Current SP points to a saved RT-Thread RH850 stack frame:
; r20-r30, FPSR/FPEPC, EIPSW/EIPC, r1-r2, r5-r19, saved lp.
; FPU data operands use general-purpose registers on RH850G3KH, so the
; normal GPR save below already preserves floating-point data values.
; FPSR/FPEPC are saved separately to preserve FPU status/config/exception PC.
_rt_hw_context_restore:
    popsp   r20, r30

    popsp   r8, r9
    ldsr    r8, FPSR
    ldsr    r9, FPEPC
    syncp

    popsp   r6, r7
    ldsr    r7, EIPC
    ldsr    r6, EIPSW
    $nowarning
    popsp   r1, r2
    popsp   r5, r19

    dispose 0, lp
    eiret

; void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to)
; r6 = &from_thread->sp, r7 = &to_thread->sp
; Thread-context switch is requested by TRAP0, following the uploaded
; FreeRTOS RH850/CC-RH port style.  The TRAP0 handler saves the current
; thread frame using hardware EIPC/EIPSW, switches SP, and returns by EIRET.
_rt_hw_context_switch:
    mov     #_rt_interrupt_from_thread, r10
    st.w    r6, 0[r10]

    mov     #_rt_interrupt_to_thread, r10
    st.w    r7, 0[r10]

    ; CC-RH FreeRTOS RH850 sample uses this literal form to trigger TRAP0.
    ; If your assembler rejects it, replace with: trap 0
    trap    0x00
    jmp     [lp]

; TRAP0 software-yield handler.
; Entered after rt_hw_context_switch() executes TRAP0.  Hardware has saved
; return PC/PSW into EIPC/EIPSW.  Save a full RT-Thread frame on the current
; thread stack, then restore the next thread frame and return with EIRET.
__rtthread_trap0_handler:
    prepare lp, 0

    pushsp  r5, r19
    pushsp  r1, r2

    stsr    EIPSW, r6
    stsr    EIPC, r7
    pushsp  r6, r7

    stsr    FPSR, r8
    stsr    FPEPC, r9
    pushsp  r8, r9

    pushsp  r20, r30

    mov     #_rt_interrupt_from_thread, r6
    ld.w    0[r6], r6              ; r6 = &from_thread->sp
    st.w    sp, 0[r6]              ; save current thread stack

    mov     #_rt_interrupt_to_thread, r6
    ld.w    0[r6], r6              ; r6 = &to_thread->sp
    ld.w    0[r6], sp              ; load next thread stack

    br      _rt_hw_context_restore

; void rt_hw_context_switch_to(rt_ubase_t to)
; r6 = &to_thread->sp
_rt_hw_context_switch_to:
    ld.w    0[r6], sp
    br      _rt_hw_context_restore

; void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to)
; Called while rt_interrupt_nest != 0. The real switch is completed by
; __rtthread_tick_handler after rt_os_tick_callback() returns.
; r6 = &from_thread->sp, r7 = &to_thread->sp
_rt_hw_context_switch_interrupt:
    mov     #_rt_thread_switch_interrupt_flag, r10
    ld.w    0[r10], r11
    cmp     0x1, r11
    be      .L_reswitch

    mov     0x1, r11
    st.w    r11, 0[r10]

    mov     #_rt_interrupt_from_thread, r10
    st.w    r6, 0[r10]

.L_reswitch:
    mov     #_rt_interrupt_to_thread, r10
    st.w    r7, 0[r10]
    jmp     [lp]

; OSTM0 / EIINT_CH84 tick interrupt wrapper.
; This wrapper saves the interrupted thread context before calling C tick code.
; If RT-Thread requests a switch in interrupt context, the saved SP is committed
; to from_thread->sp and SP is loaded from to_thread->sp before returning.
__rtthread_tick_handler:
    prepare lp, 0

    pushsp  r5, r19
    pushsp  r1, r2

    stsr    EIPSW, r6
    stsr    EIPC, r7
    pushsp  r6, r7

    stsr    FPSR, r8
    stsr    FPEPC, r9
    pushsp  r8, r9

    pushsp  r20, r30

    jarl    _rt_os_tick_callback, lp

    mov     #_rt_thread_switch_interrupt_flag, r6
    ld.w    0[r6], r7
    cmp     0x0, r7
    be      .L_tick_restore_current

    st.w    r0, 0[r6]              ; rt_thread_switch_interrupt_flag = 0

    mov     #_rt_interrupt_from_thread, r6
    ld.w    0[r6], r6              ; r6 = &from_thread->sp
    st.w    sp, 0[r6]              ; save interrupted thread stack

    mov     #_rt_interrupt_to_thread, r6
    ld.w    0[r6], r6              ; r6 = &to_thread->sp
    ld.w    0[r6], sp              ; load next thread stack

.L_tick_restore_current:
    br      _rt_hw_context_restore

; compatible symbol for older RT-Thread ports
    .public _rt_hw_interrupt_thread_switch
_rt_hw_interrupt_thread_switch:
    jmp     [lp]
