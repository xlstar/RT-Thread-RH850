/*
 * RT-Thread Nano RH850 / Renesas CC-RH CPU port.
 * This file supplies the CPU-specific stack layout and minimal CPU/interrupt
 * service hooks required by RT-Thread Nano.
 */

#include <rtthread.h>
#include <rthw.h>

/*
 * Initial PSW for a new RT-Thread thread.
 * 0x00018000: EBV=1, CU0=1, ID=0.
 * CU0 must be 1 because this FPU-enabled port saves/restores FPSR/FPEPC and
 * allows application threads to execute single-precision FPU instructions.
 */
#ifndef RH850_INITIAL_PSW
#define RH850_INITIAL_PSW       (0x00018000UL)
#endif

#ifndef RH850_INITIAL_FPSR
#define RH850_INITIAL_FPSR      (0x00020000UL)  /* FS=1, flush subnormal numbers */
#endif

#ifndef RH850_INITIAL_FPEPC
#define RH850_INITIAL_FPEPC     (0x00000000UL)
#endif

/* These three variables are used by context_ccrh.asm. */
rt_uint32_t rt_interrupt_from_thread = 0;
rt_uint32_t rt_interrupt_to_thread = 0;
rt_uint32_t rt_thread_switch_interrupt_flag = 0;

static void rt_thread_exit_trap(void)
{
    /* A thread entry function must not return. */
    rt_kprintf("thread returned unexpectedly\n");
    while (1)
    {
        ;
    }
}

rt_uint8_t *rt_hw_stack_init(void       *tentry,
                             void       *parameter,
                             rt_uint8_t *stack_addr,
                             void       *texit)
{
    rt_uint32_t *stk;

    if (texit == RT_NULL)
    {
        texit = rt_thread_exit_trap;
    }

    stack_addr += sizeof(rt_uint32_t);
    stack_addr  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_ubase_t)stack_addr, 4);
    stk = (rt_uint32_t *)stack_addr;

    /* The restore code pops in this order:
     *   popsp r20-r30
     *   popsp r8-r9      -> r8=FPSR, r9=FPEPC
     *   popsp r6-r7      -> r6=EIPSW, r7=EIPC
     *   popsp r1-r2
     *   popsp r5-r19
     *   dispose 0, lp   -> saved lp
     * Therefore the artificial stack is pushed in the reverse order below.
     */
    *(--stk) = (rt_uint32_t)texit;          /* saved lp, used by dispose */

    *(--stk) = 0x05050505UL;                /* r5  */
    *(--stk) = (rt_uint32_t)parameter;      /* r6  : first argument */
    *(--stk) = 0x07070707UL;                /* r7  */
    *(--stk) = 0x08080808UL;                /* r8  */
    *(--stk) = 0x09090909UL;                /* r9  */
    *(--stk) = 0x10101010UL;                /* r10 */
    *(--stk) = 0x11111111UL;                /* r11 */
    *(--stk) = 0x12121212UL;                /* r12 */
    *(--stk) = 0x13131313UL;                /* r13 */
    *(--stk) = 0x14141414UL;                /* r14 */
    *(--stk) = 0x15151515UL;                /* r15 */
    *(--stk) = 0x16161616UL;                /* r16 */
    *(--stk) = 0x17171717UL;                /* r17 */
    *(--stk) = 0x18181818UL;                /* r18 */
    *(--stk) = 0x19191919UL;                /* r19 */

    *(--stk) = 0x01010101UL;                /* r1  */
    *(--stk) = 0x02020202UL;                /* r2  */

    *(--stk) = RH850_INITIAL_PSW;           /* EIPSW */
    *(--stk) = (rt_uint32_t)tentry;         /* EIPC  */

    *(--stk) = RH850_INITIAL_FPSR;          /* FPSR  */
    *(--stk) = RH850_INITIAL_FPEPC;         /* FPEPC */

    *(--stk) = 0x20202020UL;                /* r20 */
    *(--stk) = 0x21212121UL;                /* r21 */
    *(--stk) = 0x22222222UL;                /* r22 */
    *(--stk) = 0x23232323UL;                /* r23 */
    *(--stk) = 0x24242424UL;                /* r24 */
    *(--stk) = 0x25252525UL;                /* r25 */
    *(--stk) = 0x26262626UL;                /* r26 */
    *(--stk) = 0x27272727UL;                /* r27 */
    *(--stk) = 0x28282828UL;                /* r28 */
    *(--stk) = 0x29292929UL;                /* r29 */
    *(--stk) = 0x30303030UL;                /* r30 */

    return (rt_uint8_t *)stk;
}

void rt_hw_cpu_icache_enable(void) {}
void rt_hw_cpu_icache_disable(void) {}
rt_base_t rt_hw_cpu_icache_status(void) { return 0; }
void rt_hw_cpu_icache_ops(int ops, void *addr, int size) { (void)ops; (void)addr; (void)size; }

void rt_hw_cpu_dcache_enable(void) {}
void rt_hw_cpu_dcache_disable(void) {}
rt_base_t rt_hw_cpu_dcache_status(void) { return 0; }
void rt_hw_cpu_dcache_ops(int ops, void *addr, int size) { (void)ops; (void)addr; (void)size; }

void rt_hw_cpu_reset(void)
{
    rt_hw_interrupt_disable();
    while (1)
    {
        ;
    }
}

void rt_hw_cpu_shutdown(void)
{
    rt_hw_interrupt_disable();
    while (1)
    {
        ;
    }
}

void rt_hw_interrupt_init(void)
{
    rt_thread_switch_interrupt_flag = 0;
    rt_interrupt_from_thread = 0;
    rt_interrupt_to_thread = 0;
}

void rt_hw_interrupt_mask(int vector)
{
    (void)vector;
}

void rt_hw_interrupt_umask(int vector)
{
    (void)vector;
}

rt_isr_handler_t rt_hw_interrupt_install(int vector,
                                         rt_isr_handler_t handler,
                                         void *param,
                                         const char *name)
{
    (void)vector;
    (void)param;
    (void)name;
    return handler;
}

void rt_hw_us_delay(rt_uint32_t us)
{
    volatile rt_uint32_t i;

    while (us--)
    {
        /* Rough delay placeholder; tune for your RH850 clock if precise delay is required. */
        for (i = 0; i < 40; i++)
        {
            ;
        }
    }
}

void rt_hw_exception_install(rt_err_t (*exception_handle)(void *context))
{
    (void)exception_handle;
}
