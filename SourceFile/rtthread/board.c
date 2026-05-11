/*
 * Board support for RT-Thread Nano on RH850 with Renesas CS+/CC-RH.
 * The OSTM0 tick setup is derived from the uploaded FreeRTOS RH850 CS+ sample.
 */

#include <stdint.h>
#include <rtthread.h>
#include <rthw.h>
#include "iodefine.h"

#ifndef RT_HW_CPU_CLOCK_HZ
#define RT_HW_CPU_CLOCK_HZ          (240000000UL)
#endif

#ifndef RT_HW_OSTM_PCLK_DIV
#define RT_HW_OSTM_PCLK_DIV         (4UL)
#endif

#define OSTM_COUNTER_START          (0x01U)
#define OSTM_COUNTER_STOP           (0x01U)
#define OSTM_MODE_INTERVAL_TIMER    (0x00U)
#define OSTM_START_INT_ENABLE       (0x01U)
#define OSTM_COMPARE_VALUE          (((RT_HW_CPU_CLOCK_HZ / RT_HW_OSTM_PCLK_DIV) / RT_TICK_PER_SECOND) - 1UL)

#define INT_PROCESSING_DISABLED     (1U)
#define INT_PROCESSING_ENABLED      (0U)
#define INT_REQUEST_NOT_OCCUR       (0U)
#define INT_TABLE_VECTOR            (1U)
#define INT_PRIORITY_MASK            (0x000FU)
#ifndef RT_HW_OSTM0_INT_PRIORITY
#define RT_HW_OSTM0_INT_PRIORITY     (14U)
#endif

#ifdef RT_USING_HEAP
static rt_uint8_t rt_heap[RT_HEAP_SIZE];
#endif

extern volatile uint32_t g_cg_sync_read;

static void rt_hw_tick_init(void)
{
    /* Disable OSTM0 operation. */
    OSTM0.TT = OSTM_COUNTER_STOP;

    /* Mask and clear OSTM0 interrupt request. */
    INTC2.ICOSTM0.BIT.MKOSTM0 = INT_PROCESSING_DISABLED;
    INTC2.ICOSTM0.BIT.RFOSTM0 = INT_REQUEST_NOT_OCCUR;

    /*
     * Set priority bits without clearing TB/MK/RF bits.
     * The old code used "UINT16 &= 0x0F" after setting TBOSTM0, which cleared
     * the table-vector bit and could send OSTM0 to the direct priority vector
     * instead of EIINT_CH_84.
     */
    INTC2.ICOSTM0.UINT16 = (uint16_t)((INTC2.ICOSTM0.UINT16 & (uint16_t)~INT_PRIORITY_MASK) |
                                      (RT_HW_OSTM0_INT_PRIORITY & INT_PRIORITY_MASK));

    /* Use EIINT table reference vector. OSTM0 is EIINT channel 84 in this sample. */
    INTC2.ICOSTM0.BIT.TBOSTM0 = INT_TABLE_VECTOR;

    /* OSTM0 interval mode, interrupt enabled on compare match. */
    OSTM0.CTL = OSTM_MODE_INTERVAL_TIMER | OSTM_START_INT_ENABLE;
    OSTM0.CMP = OSTM_COMPARE_VALUE;
    g_cg_sync_read = OSTM0.CTL;
    __syncp();

    INTC2.ICOSTM0.BIT.RFOSTM0 = INT_REQUEST_NOT_OCCUR;
    INTC2.ICOSTM0.BIT.MKOSTM0 = INT_PROCESSING_ENABLED;
    OSTM0.TS = OSTM_COUNTER_START;
}

void rt_os_tick_callback(void)
{
    /* Clear request flag early; keep this in C so board-specific register names stay outside asm. */
    INTC2.ICOSTM0.BIT.RFOSTM0 = INT_REQUEST_NOT_OCCUR;

    rt_interrupt_enter();
    rt_tick_increase();
    rt_interrupt_leave();
}

void rt_hw_board_init(void)
{
    rt_hw_interrupt_init();

#ifdef RT_USING_HEAP
    rt_system_heap_init(rt_heap, rt_heap + sizeof(rt_heap));
#endif

    rt_hw_tick_init();
}

unsigned long rt_hw_tick_get_compare_count(void)
{
    return OSTM0.CMP + 1UL;
}

unsigned long rt_hw_tick_get_current_count(void)
{
    return OSTM0.CNT + 1UL;
}
