/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software.  By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) . All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_taud.h
* Version      :
* Device(s)    : R7F701587(LQFP176pin)
* Tool-Chain   : CCRH
* Description  : This file implements device driver for TAUD module.
* Creation Date: 2018/6/12
***********************************************************************************************************************/
#ifndef TAUD_H
#define TAUD_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    TAUDTTINm Input Signal Selection Register (SELB_TAUD0I)
*/
/* Selection of TAUDTTIN14 and TAUDTTIN15 input signal (SELB_TAUD0I14[1-0]) */
#define _TAUD_CHANGE_INPUT_SIGNAL_CH14_CH15                 (0xC000U) /* Selection of TAUDTTIN14 and TAUDTTIN15 input signal */
/* Selection of TAUDTTIN12 and TAUDTTIN13 input signal (SELB_TAUD0I12[1-0]) */
#define _TAUD_CHANGE_INPUT_SIGNAL_CH12_CH13                 (0x3000U) /* Selection of TAUDTTIN12 and TAUDTTIN13 input signal */
/* Selection of TAUDTTIN10 and TAUDTTIN11 input signal (SELB_TAUD0I10[1-0]) */
#define _TAUD_CHANGE_INPUT_SIGNAL_CH10_CH11                 (0x0C00U) /* Selection of TAUDTTIN10 and TAUDTTIN11 input signal */
/* Selection of TAUDTTIN8 and TAUDTTIN9 input signal (SELB_TAUD0I8[1-0]) */
#define _TAUD_CHANGE_INPUT_SIGNAL_CH8_CH9                   (0x0300U) /* Selection of TAUDTTIN8 and TAUDTTIN9 input signal */
/* Selection of TAUDTTIN6 and TAUDTTIN7 input signal (SELB_TAUD0I6[1-0]) */
#define _TAUD_CHANGE_INPUT_SIGNAL_CH6_CH7                   (0x00C0U) /* Selection of TAUDTTIN6 and TAUDTTIN7 input signal */
/* Selection of TAUDTTIN4 and TAUDTTIN5 input signal (SELB_TAUD0I4[1-0]) */
#define _TAUD_CHANGE_INPUT_SIGNAL_CH4_CH5                   (0x0030U) /* Selection of TAUDTTIN4 and TAUDTTIN5 input signal */
/* Selection of TAUDTTIN2 and TAUDTTIN0 input signal (SELB_TAUD0I2[1-0]) */
#define _TAUD_CHANGE_INPUT_SIGNAL_CH2_CH3                   (0x000CU) /* Selection of TAUDTTIN2 and TAUDTTIN3 input signal */
/* Selection of TAUDTTIN0 and TAUDTTIN1 input signal (SELB_TAUD0I0[1-0]) */
#define _TAUD_CHANGE_INPUT_SIGNAL_CH0_CH1                   (0x0003U) /* Selection of TAUDTTIN0 and TAUDTTIN1 input signal */

/*
    TAUDTTINm Input Signal Selection Register (SELB_TAUD0I_NO)
*/
/* Selection of TAUD0 input signal (SELB_TAUD0I_NO) */
#define _TAUD_NO_CHANGE_INPUT_SIGNAL                        (0x0000U) /* TAUD0 no change input */

/*
    TAUD0 Prescaler Clock Select Register (TAUD0TPS)
*/
/* Operating mode selection (AUD0PRS3[3-0]) */
#define _TAUD_CK3_PRE_PCLK_0                                (0x0000U) /* CK3_PRE - PCLK/2^0 */
#define _TAUD_CK3_PRE_PCLK_1                                (0x1000U) /* CK3_PRE - PCLK/2^1 */
#define _TAUD_CK3_PRE_PCLK_2                                (0x2000U) /* CK3_PRE - PCLK/2^2 */
#define _TAUD_CK3_PRE_PCLK_3                                (0x3000U) /* CK3_PRE - PCLK/2^3 */
#define _TAUD_CK3_PRE_PCLK_4                                (0x4000U) /* CK3_PRE - PCLK/2^4 */
#define _TAUD_CK3_PRE_PCLK_5                                (0x5000U) /* CK3_PRE - PCLK/2^5 */
#define _TAUD_CK3_PRE_PCLK_6                                (0x6000U) /* CK3_PRE - PCLK/2^6 */
#define _TAUD_CK3_PRE_PCLK_7                                (0x7000U) /* CK3_PRE - PCLK/2^7 */
#define _TAUD_CK3_PRE_PCLK_8                                (0x8000U) /* CK3_PRE - PCLK/2^8 */
#define _TAUD_CK3_PRE_PCLK_9                                (0x9000U) /* CK3_PRE - PCLK/2^9 */
#define _TAUD_CK3_PRE_PCLK_10                               (0xA000U) /* CK3_PRE - PCLK/2^10 */
#define _TAUD_CK3_PRE_PCLK_11                               (0xB000U) /* CK3_PRE - PCLK/2^11 */
#define _TAUD_CK3_PRE_PCLK_12                               (0xC000U) /* CK3_PRE - PCLK/2^12 */
#define _TAUD_CK3_PRE_PCLK_13                               (0xD000U) /* CK3_PRE - PCLK/2^13 */
#define _TAUD_CK3_PRE_PCLK_14                               (0xE000U) /* CK3_PRE - PCLK/2^14 */
#define _TAUD_CK3_PRE_PCLK_15                               (0xF000U) /* CK3_PRE - PCLK/2^15 */
/* Operating mode selection (AUD0PRS2[3-0]) */
#define _TAUD_CK2_PRE_PCLK_0                                (0x0000U) /* CK2_PRE - PCLK/2^0 */
#define _TAUD_CK2_PRE_PCLK_1                                (0x0100U) /* CK2_PRE - PCLK/2^1 */
#define _TAUD_CK2_PRE_PCLK_2                                (0x0200U) /* CK2_PRE - PCLK/2^2 */
#define _TAUD_CK2_PRE_PCLK_3                                (0x0300U) /* CK2_PRE - PCLK/2^3 */
#define _TAUD_CK2_PRE_PCLK_4                                (0x0400U) /* CK2_PRE - PCLK/2^4 */
#define _TAUD_CK2_PRE_PCLK_5                                (0x0500U) /* CK2_PRE - PCLK/2^5 */
#define _TAUD_CK2_PRE_PCLK_6                                (0x0600U) /* CK2_PRE - PCLK/2^6 */
#define _TAUD_CK2_PRE_PCLK_7                                (0x0700U) /* CK2_PRE - PCLK/2^7 */
#define _TAUD_CK2_PRE_PCLK_8                                (0x0800U) /* CK2_PRE - PCLK/2^8 */
#define _TAUD_CK2_PRE_PCLK_9                                (0x0900U) /* CK2_PRE - PCLK/2^9 */
#define _TAUD_CK2_PRE_PCLK_10                               (0x0A00U) /* CK2_PRE - PCLK/2^10 */
#define _TAUD_CK2_PRE_PCLK_11                               (0x0B00U) /* CK2_PRE - PCLK/2^11 */
#define _TAUD_CK2_PRE_PCLK_12                               (0x0C00U) /* CK2_PRE - PCLK/2^12 */
#define _TAUD_CK2_PRE_PCLK_13                               (0x0D00U) /* CK2_PRE - PCLK/2^13 */
#define _TAUD_CK2_PRE_PCLK_14                               (0x0E00U) /* CK2_PRE - PCLK/2^14 */
#define _TAUD_CK2_PRE_PCLK_15                               (0x0F00U) /* CK2_PRE - PCLK/2^15 */
/* Operating mode selection (AUD0PRS1[3-0]) */
#define _TAUD_CK1_PRE_PCLK_0                                (0x0000U) /* CK1_PRE - PCLK/2^0 */
#define _TAUD_CK1_PRE_PCLK_1                                (0x0010U) /* CK1_PRE - PCLK/2^1 */
#define _TAUD_CK1_PRE_PCLK_2                                (0x0020U) /* CK1_PRE - PCLK/2^2 */
#define _TAUD_CK1_PRE_PCLK_3                                (0x0030U) /* CK1_PRE - PCLK/2^3 */
#define _TAUD_CK1_PRE_PCLK_4                                (0x0040U) /* CK1_PRE - PCLK/2^4 */
#define _TAUD_CK1_PRE_PCLK_5                                (0x0050U) /* CK1_PRE - PCLK/2^5 */
#define _TAUD_CK1_PRE_PCLK_6                                (0x0060U) /* CK1_PRE - PCLK/2^6 */
#define _TAUD_CK1_PRE_PCLK_7                                (0x0070U) /* CK1_PRE - PCLK/2^7 */
#define _TAUD_CK1_PRE_PCLK_8                                (0x0080U) /* CK1_PRE - PCLK/2^8 */
#define _TAUD_CK1_PRE_PCLK_9                                (0x0090U) /* CK1_PRE - PCLK/2^9 */
#define _TAUD_CK1_PRE_PCLK_10                               (0x00A0U) /* CK1_PRE - PCLK/2^10 */
#define _TAUD_CK1_PRE_PCLK_11                               (0x00B0U) /* CK1_PRE - PCLK/2^11 */
#define _TAUD_CK1_PRE_PCLK_12                               (0x00C0U) /* CK1_PRE - PCLK/2^12 */
#define _TAUD_CK1_PRE_PCLK_13                               (0x00D0U) /* CK1_PRE - PCLK/2^13 */
#define _TAUD_CK1_PRE_PCLK_14                               (0x00E0U) /* CK1_PRE - PCLK/2^14 */
#define _TAUD_CK1_PRE_PCLK_15                               (0x00F0U) /* CK1_PRE - PCLK/2^15 */
/* Operating mode selection (AUD0PRS0[3-0]) */
#define _TAUD_CK0_PRE_PCLK_0                                (0x0000U) /* CK0_PRE - PCLK/2^0 */
#define _TAUD_CK0_PRE_PCLK_1                                (0x0001U) /* CK0_PRE - PCLK/2^1 */
#define _TAUD_CK0_PRE_PCLK_2                                (0x0002U) /* CK0_PRE - PCLK/2^2 */
#define _TAUD_CK0_PRE_PCLK_3                                (0x0003U) /* CK0_PRE - PCLK/2^3 */
#define _TAUD_CK0_PRE_PCLK_4                                (0x0004U) /* CK0_PRE - PCLK/2^4 */
#define _TAUD_CK0_PRE_PCLK_5                                (0x0005U) /* CK0_PRE - PCLK/2^5 */
#define _TAUD_CK0_PRE_PCLK_6                                (0x0006U) /* CK0_PRE - PCLK/2^6 */
#define _TAUD_CK0_PRE_PCLK_7                                (0x0007U) /* CK0_PRE - PCLK/2^7 */
#define _TAUD_CK0_PRE_PCLK_8                                (0x0008U) /* CK0_PRE - PCLK/2^8 */
#define _TAUD_CK0_PRE_PCLK_9                                (0x0009U) /* CK0_PRE - PCLK/2^9 */
#define _TAUD_CK0_PRE_PCLK_10                               (0x000AU) /* CK0_PRE - PCLK/2^10 */
#define _TAUD_CK0_PRE_PCLK_11                               (0x000BU) /* CK0_PRE - PCLK/2^11 */
#define _TAUD_CK0_PRE_PCLK_12                               (0x000CU) /* CK0_PRE - PCLK/2^12 */
#define _TAUD_CK0_PRE_PCLK_13                               (0x000DU) /* CK0_PRE - PCLK/2^13 */
#define _TAUD_CK0_PRE_PCLK_14                               (0x000EU) /* CK0_PRE - PCLK/2^14 */
#define _TAUD_CK0_PRE_PCLK_15                               (0x000FU) /* CK0_PRE - PCLK/2^15 */

/*
    TAUD0 Channel Mode OS Register (TAUD0CMORm)
*/
/* Selection of operation clock (TAUD0CKS[1-0]) */
#define _TAUD_SELECTION_CK0                                 (0x0000U) /* CK0 */
#define _TAUD_SELECTION_CK1                                 (0x4000U) /* CK1 */
#define _TAUD_SELECTION_CK2                                 (0x8000U) /* CK2 */
#define _TAUD_SELECTION_CK3                                 (0xC000U) /* CK3 */
/* Selects a count clock or TAUD0CNTm counter (TAUD0CCS[1-0]) */
#define _TAUD_COUNT_CLOCK_PCLK                              (0x0000U) /* Operation clock specified by TAUD0CMORm.TAUD0CKS[1:0] */
#define _TAUD_COUNT_CLOCK_INPUT_EDGE                        (0x1000U) /* Valid edge of TAUDTTINm input signal */
#define _TAUD_COUNT_CLOCK_INPUT_INT                         (0x3000U) /* INTTAUD0Im signal of master channel */
/* A mster channel or slave channel during synchronous channel operation (TAUD0MAS) */
#define _TAUD_INDEPENDENT_CHANNEL                           (0x0000U) /* Slave */
#define _TAUD_SLAVE_CHANNEL                                 (0x0000U) /* Slave */
#define _TAUD_MASTER_CHANNEL                                (0x0800U) /* Master */
/* Selects a count clock or TAUD0CNTm counter (TAUD0STS[2-0]) */
#define _TAUD_START_TRIGGER_SOFTWARE                        (0x0000U) /* Software trigger */
#define _TAUD_START_TRIGGER_VALID_EDGE                      (0x0100U) /* Valid edge of TAUDTTINm input signal */
#define _TAUD_START_STOP_TRIGGER_VALID_EDGE                 (0x0200U) /* Valid edge of TAUDTTINm input signal is used as a start trigger  */
#define _TAUD_START_TRIGGER_SIMULTANEOUS_REWRITE            (0x0300U) /* Triggers Simultaneous rewrite */
#define _TAUD_START_TRIGGER_MASTER_INT                      (0x0400U) /* INTTAUDnIm is the start trigger of master channel */
#define _TAUD_START_TRIGGER_UPPER_INT                       (0x0500U) /* INTTAUDnIm of upper channel is the start trigger regardless of master setting */
#define _TAUD_START_TRIGGER_DEAD_TIME_OUTPUT                (0x0600U) /* Dead time output signal of TAUDTTOUTm generating unit */
#define _TAUD_START_TRIGGER_UP_DOWN_OUTPUT                  (0x0700U) /* Up/down output trigger signal of master channel */
/* Specifies the timing for updating capture register (TAUD0COS[1-0]) */
#define _TAUD_OVERFLOW_AUTO_CLEAR                           (0x0000U) /* TAUDnCDRm update upon detection of edge of TAUDTTINm and TAUDnOVF update */
#define _TAUD_OVERFLOW_MANUAL_CLEAR                         (0x0040U) /* TAUDnCDRm update upon detection of edge of TAUDTTINm and TAUDnOVF is set */
#define _TAUD_OVERFLOW_COUNT_STOP                           (0x0080U) /* TAUDnCDRm update upon detection of edge of TAUDTTINm and at counter overflow, TAUDnOVF is not set */
#define _TAUD_OVERFLOW_COUNT_STOP_MANUAL_CLEAR              (0x00C0U) /* TAUDnCDRm update upon detection of edge of TAUDTTINm and at counter overflow, TAUDnOVF is set */
/* Specifies an operating mode (TAUD0MD[4-0]) */
#define _TAUD_INTERVAL_TIMER_MODE                           (0x0000U) /* Interval timer mode */
#define _TAUD_JUDGE_MODE                                    (0x0002U) /* Judge mode */
#define _TAUD_CAPTURE_MODE                                  (0x0004U) /* Capture mode */
#define _TAUD_EVEVT_COUNT_MODE                              (0x0006U) /* Event count mode */
#define _TAUD_ONE_COUNT_MODE                                (0x0008U) /* One-count mode */
#define _TAUD_CAPTURE_ONE_COUNT_MODE                        (0x000CU) /* Capture and one-count mode */
#define _TAUD_JUDGE_ONE_COUNT_MODE                          (0x000EU) /* Judge and one-count mode */
#define _TAUD_COUNT_UP_DOWN_MODE                            (0x0012U) /* Count-up/-down mode  */
#define _TAUD_PULSE_ONECOUNT_MODE                           (0x0014U) /* Pulse one-count mode */
#define _TAUD_COUNT_CAPTURE_MODE                            (0x0016U) /* Count capture mode  */
#define _TAUD_GATE_COUNT_MODE                               (0x0018U) /* Gate count mode */
#define _TAUD_CAPTURE_AND_GATE_COUNT_MODE                   (0x001AU) /* Capture and gate count mode  */
/* Role of TAUD0MD0 Bit (TAUD0MD0) */
#define _TAUD_START_INT_NOT_GENERATED                       (0x0000U) /* INTTAUD0Im is not generated */
#define _TAUD_START_TRIGGER_DISABLE                         (0x0000U) /* Disables detection. */
#define _TAUD_OUTPUT_IN_SIGNAL_WIDTH                        (0x0000U) /* TAUD output in signal width */
#define _TAUD_START_INT_GENERATED                           (0x0001U) /* INTTAUD0Im is generated */
#define _TAUD_START_TRIGGER_ENABLE                          (0x0001U) /* Enables detection. */
#define _TAUD_OUTPUT_OVER_SIGNAL_WIDTH                      (0x0001U) /* TAUD output over signal width */

/*
    TAUD0 Channel Mode User Register (TAUD0CMURm)
*/
/* Specifies a valid edge of TAUDTTINm input signal (TAUD0TIS[1-0]) */
#define _TAUD_INPUT_EDGE_UNUSED                             (0x00U) /* Unused Falling edge */
#define _TAUD_INPUT_EDGE_FALLING                            (0x00U) /* Falling edge */
#define _TAUD_INPUT_EDGE_RISING                             (0x01U) /* Rising edge */
#define _TAUD_INPUT_EDGE_BOTH_MEASURE_LOW                   (0x02U) /* Detection of rising and falling edges (selects low width measurement) */
#define _TAUD_INPUT_EDGE_BOTH_MEASURE_HIGH                  (0x03U) /* Detection of rising and falling edges (selects high width measurement) */

/*
    TAUD0 Channel Start Trigger Register (TAUD0TS)
*/
/* Enables the counter operation of channel 15 (TAUD0TS15) */
#define _TAUD_CHANNEL15_COUNTER_START                       (0x8000U) /* Enables the counter operation */
/* Enables the counter operation of channel 14 (TAUD0TS14) */
#define _TAUD_CHANNEL14_COUNTER_START                       (0x4000U) /* Enables the counter operation */
/* Enables the counter operation of channel 13 (TAUD0TS13) */
#define _TAUD_CHANNEL13_COUNTER_START                       (0x2000U) /* Enables the counter operation */
/* Enables the counter operation of channel 12 (TAUD0TS12) */
#define _TAUD_CHANNEL12_COUNTER_START                       (0x1000U) /* Enables the counter operation */
/* Enables the counter operation of channel 11 (TAUD0TS11) */
#define _TAUD_CHANNEL11_COUNTER_START                       (0x0800U) /* Enables the counter operation */
/* Enables the counter operation of channel 10 (TAUD0TS10) */
#define _TAUD_CHANNEL10_COUNTER_START                       (0x0400U) /* Enables the counter operation */
/* Enables the counter operation of channel 9 (TAUD0TS9) */
#define _TAUD_CHANNEL9_COUNTER_START                        (0x0200U) /* Enables the counter operation */
/* Enables the counter operation of channel 8 (TAUD0TS8) */
#define _TAUD_CHANNEL8_COUNTER_START                        (0x0100U) /* Enables the counter operation */
/* Enables the counter operation of channel 7 (TAUD0TS7) */
#define _TAUD_CHANNEL7_COUNTER_START                        (0x0080U) /* Enables the counter operation */
/* Enables the counter operation of channel 6 (TAUD0TS06) */
#define _TAUD_CHANNEL6_COUNTER_START                        (0x0040U) /* Enables the counter operation */
/* Enables the counter operation of channel 5 (TAUD0TS5) */
#define _TAUD_CHANNEL5_COUNTER_START                        (0x0020U) /* Enables the counter operation */
/* Enables the counter operation of channel 4 (TAUD0TS4) */
#define _TAUD_CHANNEL4_COUNTER_START                        (0x0010U) /* Enables the counter operation */
/* Enables the counter operation of channel 3 (TAUD0TS3) */
#define _TAUD_CHANNEL3_COUNTER_START                        (0x0008U) /* Enables the counter operation */
/* Enables the counter operation of channel 2 (TAUD0TS2) */
#define _TAUD_CHANNEL2_COUNTER_START                        (0x0004U) /* Enables the counter operation */
/* Enables the counter operation of channel 1 (TAUD0TS1) */
#define _TAUD_CHANNEL1_COUNTER_START                        (0x0002U) /* Enables the counter operation */
/* Enables the counter operation of channel 0 (TAUD0TS0) */
#define _TAUD_CHANNEL0_COUNTER_START                        (0x0001U) /* Enables the counter operation */

/*
    TAUD0 Channel Stop Trigger Register (TAUD0TT)
*/
/* Stops the counter operation of channel 15 (TAUD0TT15) */
#define _TAUD_CHANNEL15_COUNTER_STOP                        (0x8000U) /* Stops the counter operation */
/* Stops the counter operation of channel 14 (TAUD0TT14) */
#define _TAUD_CHANNEL14_COUNTER_STOP                        (0x4000U) /* Stops the counter operation */
/* Stops the counter operation of channel 13 (TAUD0TT13) */
#define _TAUD_CHANNEL13_COUNTER_STOP                        (0x2000U) /* Stops the counter operation */
/* Stops the counter operation of channel 12 (TAUD0TT12) */
#define _TAUD_CHANNEL12_COUNTER_STOP                        (0x1000U) /* Stops the counter operation */
/* Stops the counter operation of channel 11 (TAUD0TT11) */
#define _TAUD_CHANNEL11_COUNTER_STOP                        (0x0800U) /* Stops the counter operation */
/* Stops the counter operation of channel 10 (TAUD0TT10) */
#define _TAUD_CHANNEL10_COUNTER_STOP                        (0x0400U) /* Stops the counter operation  */
/* Stops the counter operation of channel 9 (TAUD0TT9) */
#define _TAUD_CHANNEL9_COUNTER_STOP                         (0x0200U) /* Stops the counter operation */
/* Stops the counter operation of channel 8 (TAUD0TT8) */
#define _TAUD_CHANNEL8_COUNTER_STOP                         (0x0100U) /* Stops the counter operation */
/* Stops the counter operation of channel 7 (TAUD0TT7) */
#define _TAUD_CHANNEL7_COUNTER_STOP                         (0x0080U) /* Stops the counter operation */
/* Stops the counter operation of channel 6 (TAUD0TT6) */
#define _TAUD_CHANNEL6_COUNTER_STOP                         (0x0040U) /* Stops the counter operation */
/* Stops the counter operation of channel 5 (TAUD0TT5) */
#define _TAUD_CHANNEL5_COUNTER_STOP                         (0x0020U) /* Stops the counter operation */
/* Stops the counter operation of channel 4 (TAUD0TT4) */
#define _TAUD_CHANNEL4_COUNTER_STOP                         (0x0010U) /* Stops the counter operation */
/* Stops the counter operation of channel 3 (TAUD0TT3) */
#define _TAUD_CHANNEL3_COUNTER_STOP                         (0x0008U) /* Stops the counter operation */
/* Stops the counter operation of channel 2 (TAUD0TT2) */
#define _TAUD_CHANNEL2_COUNTER_STOP                         (0x0004U) /* Stops the counter operation */
/* Stops the counter operation of channel 1 (TAUD0TT1) */
#define _TAUD_CHANNEL1_COUNTER_STOP                         (0x0002U) /* Stops the counter operation */
/* Stops the counter operation of channel 0 (TAUD0TT0) */
#define _TAUD_CHANNEL0_COUNTER_STOP                         (0x0001U) /* Stops the counter operation */

/*
    TAUD0 Channel Output Enable Register (TAUD0TOE)
*/
/* Enables/disables the independent channel output function (TAUD0TOE15) */
#define _TAUD_CHANNEL15_DISABLES_OUTPUT_FUNCTION            (0x0000U) /* Disables the independent timer output function (controlled by software) */
#define _TAUD_CHANNEL15_ENABLES_OUTPUT_FUNCTION             (0x8000U) /* Enables the independent timer output function */
/* Enables/disables the independent channel output function (TAUD0TOE14) */
#define _TAUD_CHANNEL14_DISABLES_OUTPUT_FUNCTION            (0x0000U) /* Disables the independent timer output function (controlled by software) */
#define _TAUD_CHANNEL14_ENABLES_OUTPUT_FUNCTION             (0x4000U) /* Enables the independent timer output function */
/* Enables/disables the independent channel output function (TAUD0TOE13) */
#define _TAUD_CHANNEL13_DISABLES_OUTPUT_FUNCTION            (0x0000U) /* Disables the independent timer output function (controlled by software) */
#define _TAUD_CHANNEL13_ENABLES_OUTPUT_FUNCTION             (0x2000U) /* Enables the independent timer output function */
/* Enables/disables the independent channel output function (TAUD0TOE12) */
#define _TAUD_CHANNEL12_DISABLES_OUTPUT_FUNCTION            (0x0000U) /* Disables the independent timer output function (controlled by software) */
#define _TAUD_CHANNEL12_ENABLES_OUTPUT_FUNCTION             (0x1000U) /* Enables the independent timer output function */
/* Enables/disables the independent channel output function (TAUD0TOE11) */
#define _TAUD_CHANNEL11_DISABLES_OUTPUT_FUNCTION            (0x0000U) /* Disables the independent timer output function (controlled by software) */
#define _TAUD_CHANNEL11_ENABLES_OUTPUT_FUNCTION             (0x0800U) /* Enables the independent timer output function */
/* Enables/disables the independent channel output function (TAUD0TOE10) */
#define _TAUD_CHANNEL10_DISABLES_OUTPUT_FUNCTION            (0x0000U) /* Disables the independent timer output function (controlled by software) */
#define _TAUD_CHANNEL10_ENABLES_OUTPUT_FUNCTION             (0x0400U) /* Enables the independent timer output function */
/* Enables/disables the independent channel output function (TAUD0TOE9) */
#define _TAUD_CHANNEL9_DISABLES_OUTPUT_FUNCTION             (0x0000U) /* Disables the independent timer output function (controlled by software) */
#define _TAUD_CHANNEL9_ENABLES_OUTPUT_FUNCTION              (0x0200U) /* Enables the independent timer output function */
/* Enables/disables the independent channel output function (TAUD0TOE8) */
#define _TAUD_CHANNEL8_DISABLES_OUTPUT_FUNCTION             (0x0000U) /* Disables the independent timer output function (controlled by software) */
#define _TAUD_CHANNEL8_ENABLES_OUTPUT_FUNCTION              (0x0100U) /* Enables the independent timer output function */
/* Enables/disables the independent channel output function (TAUD0TOE7) */
#define _TAUD_CHANNEL7_DISABLES_OUTPUT_FUNCTION             (0x0000U) /* Disables the independent timer output function (controlled by software) */
#define _TAUD_CHANNEL07_ENABLES_OUTPUT_FUNCTION             (0x0080U) /* Enables the independent timer output function */
/* Enables/disables the independent channel output function (TAUD0TOE6) */
#define _TAUD_CHANNEL6_DISABLES_OUTPUT_FUNCTION             (0x0000U) /* Disables the independent timer output function (controlled by software) */
#define _TAUD_CHANNEL6_ENABLES_OUTPUT_FUNCTION              (0x0040U) /* Enables the independent timer output function */
/* Enables/disables the independent channel output function (TAUD0TOE5) */
#define _TAUD_CHANNEL5_DISABLES_OUTPUT_FUNCTION             (0x0000U) /* Disables the independent timer output function (controlled by software) */
#define _TAUD_CHANNEL5_ENABLES_OUTPUT_FUNCTION              (0x0020U) /* Enables the independent timer output function */
/* Enables/disables the independent channel output function (TAUD0TOE4) */
#define _TAUD_CHANNEL4_DISABLES_OUTPUT_FUNCTION             (0x0000U) /* Disables the independent timer output function (controlled by software) */
#define _TAUD_CHANNEL4_ENABLES_OUTPUT_FUNCTION              (0x0010U) /* Enables the independent timer output function */
/* Enables/disables the independent channel output function (TAUD0TOE3) */
#define _TAUD_CHANNEL3_DISABLES_OUTPUT_FUNCTION             (0x0000U) /* Disables the independent timer output function (controlled by software) */
#define _TAUD_CHANNEL3_ENABLES_OUTPUT_FUNCTION              (0x0008U) /* Enables the independent timer output function */
/* Enables/disables the independent channel output function (TAUD0TOE2) */
#define _TAUD_CHANNEL2_DISABLES_OUTPUT_FUNCTION             (0x0000U) /* Disables the independent timer output function (controlled by software) */
#define _TAUD_CHANNEL2_ENABLES_OUTPUT_FUNCTION              (0x0004U) /* Enables the independent timer output function */
/* Enables/disables the independent channel output function (TAUD0TOE1) */
#define _TAUD_CHANNEL1_DISABLES_OUTPUT_FUNCTION             (0x0000U) /* Disables the independent timer output function (controlled by software) */
#define _TAUD_CHANNEL1_ENABLES_OUTPUT_FUNCTION              (0x0002U) /* Enables the independent timer output function */
/* Enables/disables the independent channel output function (TAUD0TOE0) */
#define _TAUD_CHANNEL0_DISABLES_OUTPUT_FUNCTION             (0x0000U) /* Disables the independent timer output function (controlled by software) */
#define _TAUD_CHANNEL0_ENABLES_OUTPUT_FUNCTION              (0x0001U) /* Enables the independent timer output function */

/*
    TAUD0 Channel Output Mode Register (TAUD0TOM)
*/
/* Specifies an output mode (TAUD0TOM15) */
#define _TAUD_CHANNEL15_INDEPENDENT_OPERATION               (0x0000U) /* Independent channel operation */
#define _TAUD_CHANNEL15_SYNCHRONOUS_OPERATION               (0x8000U) /* Synchronous channel operation */
/* Specifies an output mode (TAUD0TOM14) */
#define _TAUD_CHANNEL14_INDEPENDENT_OPERATION               (0x0000U) /* Independent channel operation */
#define _TAUD_CHANNEL14_SYNCHRONOUS_OPERATION               (0x4000U) /* Synchronous channel operation */
/* Specifies an output mode (TAUD0TOM13) */
#define _TAUD_CHANNEL13_INDEPENDENT_OPERATION               (0x0000U) /* Independent channel operation */
#define _TAUD_CHANNEL13_SYNCHRONOUS_OPERATION               (0x2000U) /* Synchronous channel operation */
/* Specifies an output mode (TAUD0TOM12) */
#define _TAUD_CHANNEL12_INDEPENDENT_OPERATION               (0x0000U) /* Independent channel operation */
#define _TAUD_CHANNEL12_SYNCHRONOUS_OPERATION               (0x1000U) /* Synchronous channel operation */
/* Specifies an output mode (TAUD0TOM11) */
#define _TAUD_CHANNEL11_INDEPENDENT_OPERATION               (0x0000U) /* Independent channel operation */
#define _TAUD_CHANNEL11_SYNCHRONOUS_OPERATION               (0x0800U) /* Synchronous channel operation */
/* Specifies an output mode (TAUD0TOM10) */
#define _TAUD_CHANNEL10_INDEPENDENT_OPERATION               (0x0000U) /* Independent channel operation */
#define _TAUD_CHANNEL10_SYNCHRONOUS_OPERATION               (0x0400U) /* Synchronous channel operation */
/* Specifies an output mode (TAUD0TOM9) */
#define _TAUD_CHANNEL9_INDEPENDENT_OPERATION                (0x0000U) /* Independent channel operation */
#define _TAUD_CHANNEL9_SYNCHRONOUS_OPERATION                (0x0200U) /* Synchronous channel operation */
/* Specifies an output mode (TAUD0TOM8) */
#define _TAUD_CHANNEL8_INDEPENDENT_OPERATION                (0x0000U) /* Independent channel operation */
#define _TAUD_CHANNEL8_SYNCHRONOUS_OPERATION                (0x0100U) /* Synchronous channel operation */
/* Specifies an output mode (TAUD0TOM7) */
#define _TAUD_CHANNEL7_INDEPENDENT_OPERATION                (0x0000U) /* Independent channel operation */
#define _TAUD_CHANNEL7_SYNCHRONOUS_OPERATION                (0x0080U) /* Synchronous channel operation */
/* Specifies an output mode (TAUD0TOM6) */
#define _TAUD_CHANNEL6_INDEPENDENT_OPERATION                (0x0000U) /* Independent channel operation */
#define _TAUD_CHANNEL6_SYNCHRONOUS_OPERATION                (0x0040U) /* Synchronous channel operation */
/* Specifies an output mode (TAUD0TOM5) */
#define _TAUD_CHANNEL5_INDEPENDENT_OPERATION                (0x0000U) /* Independent channel operation */
#define _TAUD_CHANNEL5_SYNCHRONOUS_OPERATION                (0x0020U) /* Synchronous channel operation */
/* Specifies an output mode (TAUD0TOM4) */
#define _TAUD_CHANNEL4_INDEPENDENT_OPERATION                (0x0000U) /* Independent channel operation */
#define _TAUD_CHANNEL4_SYNCHRONOUS_OPERATION                (0x0010U) /* Synchronous channel operation */
/* Specifies an output mode (TAUD0TOM3) */
#define _TAUD_CHANNEL3_INDEPENDENT_OPERATION                (0x0000U) /* Independent channel operation */
#define _TAUD_CHANNEL3_SYNCHRONOUS_OPERATION                (0x0008U) /* Synchronous channel operation */
/* Specifies an output mode (TAUD0TOM2) */
#define _TAUD_CHANNEL2_INDEPENDENT_OPERATION                (0x0000U) /* Independent channel operation */
#define _TAUD_CHANNEL2_SYNCHRONOUS_OPERATION                (0x0004U) /* Synchronous channel operation */
/* Specifies an output mode (TAUD0TOM1) */
#define _TAUD_CHANNEL1_INDEPENDENT_OPERATION                (0x0000U) /* Independent channel operation */
#define _TAUD_CHANNEL1_SYNCHRONOUS_OPERATION                (0x0002U) /* Synchronous channel operation */
/* Specifies an output mode (TAUD0TOM0) */
#define _TAUD_CHANNEL0_INDEPENDENT_OPERATION                (0x0000U) /* Independent channel operation */
#define _TAUD_CHANNEL0_SYNCHRONOUS_OPERATION                (0x0001U) /* Synchronous channel operation */

/*
    TAUD0 Channel Output Configuration Register (TAUD0TOC)
*/
/* Specifies the output mode (TAUD0TOC15) */
#define _TAUD_CHANNEL15_OPERATION_MODE1                     (0x0000U) /* Operation mode 1 */
#define _TAUD_CHANNEL15_OPERATION_MODE2                     (0x8000U) /* Operation mode 2 */
/* Specifies the output mode (TAUD0TOC14) */
#define _TAUD_CHANNEL14_OPERATION_MODE1                     (0x0000U) /* Operation mode 1 */
#define _TAUD_CHANNEL14_OPERATION_MODE2                     (0x4000U) /* Operation mode 2 */
/* Specifies the output mode (TAUD0TOC13) */
#define _TAUD_CHANNEL13_OPERATION_MODE1                     (0x0000U) /* Operation mode 1 */
#define _TAUD_CHANNEL13_OPERATION_MODE2                     (0x2000U) /* Operation mode 2 */
/* Specifies the output mode (TAUD0TOC12) */
#define _TAUD_CHANNEL12_OPERATION_MODE1                     (0x0000U) /* Operation mode 1 */
#define _TAUD_CHANNEL12_OPERATION_MODE2                     (0x1000U) /* Operation mode 2 */
/* Specifies the output mode (TAUD0TOC11) */
#define _TAUD_CHANNEL11_OPERATION_MODE1                     (0x0000U) /* Operation mode 1 */
#define _TAUD_CHANNEL11_OPERATION_MODE2                     (0x0800U) /* Operation mode 2 */
/* Specifies the output mode (TAUD0TOC10) */
#define _TAUD_CHANNEL10_OPERATION_MODE1                     (0x0000U) /* Operation mode 1 */
#define _TAUD_CHANNEL10_OPERATION_MODE2                     (0x0400U) /* Operation mode 2 */
/* Specifies the output mode (TAUD0TOC9) */
#define _TAUD_CHANNEL9_OPERATION_MODE1                      (0x0000U) /* Operation mode 1 */
#define _TAUD_CHANNEL9_OPERATION_MODE2                      (0x0200U) /* Operation mode 2 */
/* Specifies the output mode (TAUD0TOC8) */
#define _TAUD_CHANNEL8_OPERATION_MODE1                      (0x0000U) /* Operation mode 1 */
#define _TAUD_CHANNEL8_OPERATION_MODE2                      (0x0100U) /* Operation mode 2 */
/* Specifies the output mode (TAUD0TOC7) */
#define _TAUD_CHANNEL7_OPERATION_MODE1                      (0x0000U) /* Operation mode 1 */
#define _TAUD_CHANNEL7_OPERATION_MODE2                      (0x0080U) /* Operation mode 2 */
/* Specifies the output mode (TAUD0TOC6) */
#define _TAUD_CHANNEL6_OPERATION_MODE1                      (0x0000U) /* Operation mode 1 */
#define _TAUD_CHANNEL6_OPERATION_MODE2                      (0x0040U) /* Operation mode 2 */
/* Specifies the output mode (TAUD0TOC5) */
#define _TAUD_CHANNEL5_OPERATION_MODE1                      (0x0000U) /* Operation mode 1 */
#define _TAUD_CHANNEL5_OPERATION_MODE2                      (0x0020U) /* Operation mode 2 */
/* Specifies the output mode (TAUD0TOC4) */
#define _TAUD_CHANNEL4_OPERATION_MODE1                      (0x0000U) /* Operation mode 1 */
#define _TAUD_CHANNEL4_OPERATION_MODE2                      (0x0010U) /* Operation mode 2 */
/* Specifies the output mode (TAUD0TOC3) */
#define _TAUD_CHANNEL3_OPERATION_MODE1                      (0x0000U) /* Operation mode 1 */
#define _TAUD_CHANNEL3_OPERATION_MODE2                      (0x0008U) /* Operation mode 2 */
/* Specifies the output mode (TAUD0TOC2) */
#define _TAUD_CHANNEL2_OPERATION_MODE1                      (0x0000U) /* Operation mode 1 */
#define _TAUD_CHANNEL2_OPERATION_MODE2                      (0x0004U) /* Operation mode 2 */
/* Specifies the output mode (TAUD0TOC1) */
#define _TAUD_CHANNEL1_OPERATION_MODE1                      (0x0000U) /* Operation mode 1 */
#define _TAUD_CHANNEL1_OPERATION_MODE2                      (0x0002U) /* Operation mode 2 */
/* Specifies the output mode (TAUD0TOC0) */
#define _TAUD_CHANNEL0_OPERATION_MODE1                      (0x0000U) /* Operation mode 1 */
#define _TAUD_CHANNEL0_OPERATION_MODE2                      (0x0001U) /* Operation mode 2 */

/*
    TAUD0 Channel Output Level Register (TAUD0TOL)
*/
/* Specifies the output logic of channel 15 output bit (TAUD0TOL15) */
#define _TAUD_CHANNEL15_POSITIVE_LOGIC                      (0x0000U) /* Positive logic */
#define _TAUD_CHANNEL15_NEGATIVE_LOGIC                      (0x8000U) /* Negative logic */
/* Specifies the output logic of channel 14 output bit (TAUD0TOL14) */
#define _TAUD_CHANNEL14_POSITIVE_LOGIC                      (0x0000U) /* Positive logic */
#define _TAUD_CHANNEL14_NEGATIVE_LOGIC                      (0x4000U) /* Negative logic */
/* Specifies the output logic of channel 13 output bit (TAUD0TOL13) */
#define _TAUD_CHANNEL13_POSITIVE_LOGIC                      (0x0000U) /* Positive logic */
#define _TAUD_CHANNEL13_NEGATIVE_LOGIC                      (0x2000U) /* Negative logic */
/* Specifies the output logic of channel 12 output bit (TAUD0TOL12) */
#define _TAUD_CHANNEL12_POSITIVE_LOGIC                      (0x0000U) /* Positive logic */
#define _TAUD_CHANNEL12_NEGATIVE_LOGIC                      (0x1000U) /* Negative logic */
/* Specifies the output logic of channel 11 output bit (TAUD0TOL11) */
#define _TAUD_CHANNEL11_POSITIVE_LOGIC                      (0x0000U) /* Positive logic */
#define _TAUD_CHANNEL11_NEGATIVE_LOGIC                      (0x0800U) /* Negative logic */
/* Specifies the output logic of channel 10 output bit (TAUD0TOL10) */
#define _TAUD_CHANNEL10_POSITIVE_LOGIC                      (0x0000U) /* Positive logic */
#define _TAUD_CHANNEL10_NEGATIVE_LOGIC                      (0x0400U) /* Negative logic */
/* Specifies the output logic of channel 9 output bit (TAUD0TOL9) */
#define _TAUD_CHANNEL9_POSITIVE_LOGIC                       (0x0000U) /* Positive logic */
#define _TAUD_CHANNEL9_NEGATIVE_LOGIC                       (0x0200U) /* Negative logic */
/* Specifies the output logic of channel 8 output bit (TAUD0TOL8) */
#define _TAUD_CHANNEL8_POSITIVE_LOGIC                       (0x0000U) /* Positive logic */
#define _TAUD_CHANNEL8_NEGATIVE_LOGIC                       (0x0100U) /* Negative logic */
/* Specifies the output logic of channel 7 output bit (TAUD0TOL7) */
#define _TAUD_CHANNEL7_POSITIVE_LOGIC                       (0x0000U) /* Positive logic */
#define _TAUD_CHANNEL7_NEGATIVE_LOGIC                       (0x0080U) /* Negative logic */
/* Specifies the output logic of channel 6 output bit (TAUD0TOL6) */
#define _TAUD_CHANNEL6_POSITIVE_LOGIC                       (0x0000U) /* Positive logic */
#define _TAUD_CHANNEL6_NEGATIVE_LOGIC                       (0x0040U) /* Negative logic */
/* Specifies the output logic of channel 5 output bit (TAUD0TOL5) */
#define _TAUD_CHANNEL5_POSITIVE_LOGIC                       (0x0000U) /* Positive logic */
#define _TAUD_CHANNEL5_NEGATIVE_LOGIC                       (0x0020U) /* Negative logic */
/* Specifies the output logic of channel 4 output bit (TAUD0TOL4) */
#define _TAUD_CHANNEL4_POSITIVE_LOGIC                       (0x0000U) /* Positive logic */
#define _TAUD_CHANNEL4_NEGATIVE_LOGIC                       (0x0010U) /* Negative logic */
/* Specifies the output logic of channel 3 output bit (TAUD0TOL3) */
#define _TAUD_CHANNEL3_POSITIVE_LOGIC                       (0x0000U) /* Positive logic */
#define _TAUD_CHANNEL3_NEGATIVE_LOGIC                       (0x0008U) /* Negative logic */
/* Specifies the output logic of channel 2 output bit (TAUD0TOL2) */
#define _TAUD_CHANNEL2_POSITIVE_LOGIC                       (0x0000U) /* Positive logic */
#define _TAUD_CHANNEL2_NEGATIVE_LOGIC                       (0x0004U) /* Negative logic */
/* Specifies the output logic of channel 1 output bit (TAUD0TOL1) */
#define _TAUD_CHANNEL1_POSITIVE_LOGIC                       (0x0000U) /* Positive logic */
#define _TAUD_CHANNEL1_NEGATIVE_LOGIC                       (0x0002U) /* Negative logic */
/* Specifies the output logic of channel 0 output bit (TAUD0TOL0) */
#define _TAUD_CHANNEL0_POSITIVE_LOGIC                       (0x0000U) /* Positive logic */
#define _TAUD_CHANNEL0_NEGATIVE_LOGIC                       (0x0001U) /* Negative logic */

/*
    TAUD0 Channel Dead Time Output Enable Register (TAUD0TDE)
*/
/* Enables/disables the dead time control operation of channel 15 (TAUD0TDE15) */
#define _TAUD_CHANNEL15_DISABLES_DEAD_TIME_OPERATION        (0x0000U) /* Disables dead time operation */
#define _TAUD_CHANNEL15_ENABLES_DEAD_TIME_OPERATION         (0x8000U) /* Enables dead time operation */
/* Enables/disables the dead time control operation of channel 14 (TAUD0TDE14) */
#define _TAUD_CHANNEL14_DISABLES_DEAD_TIME_OPERATION        (0x0000U) /* Disables dead time operation */
#define _TAUD_CHANNEL14_ENABLES_DEAD_TIME_OPERATION         (0x4000U) /* Enables dead time operation */
/* Enables/disables the dead time control operation of channel 13 (TAUD0TDE13) */
#define _TAUD_CHANNEL13_DISABLES_DEAD_TIME_OPERATION        (0x0000U) /* Disables dead time operation */
#define _TAUD_CHANNEL13_ENABLES_DEAD_TIME_OPERATION         (0x2000U) /* Enables dead time operation */
/* Enables/disables the dead time control operation of channel 12 (TAUD0TDE12) */
#define _TAUD_CHANNEL12_DISABLES_DEAD_TIME_OPERATION        (0x0000U) /* Disables dead time operation */
#define _TAUD_CHANNEL12_ENABLES_DEAD_TIME_OPERATION         (0x1000U) /* Enables dead time operation */
/* Enables/disables the dead time control operation of channel 11 (TAUD0TDE11) */
#define _TAUD_CHANNEL11_DISABLES_DEAD_TIME_OPERATION        (0x0000U) /* Disables dead time operation */
#define _TAUD_CHANNEL11_ENABLES_DEAD_TIME_OPERATION         (0x0800U) /* Enables dead time operation */
/* Enables/disables the dead time control operation of channel 10 (TAUD0TDE10) */
#define _TAUD_CHANNEL10_DISABLES_DEAD_TIME_OPERATION        (0x0000U) /* Disables dead time operation */
#define _TAUD_CHANNEL10_ENABLES_DEAD_TIME_OPERATION         (0x0400U) /* Enables dead time operation */
/* Enables/disables the dead time control operation of channel 9 (TAUD0TDE9) */
#define _TAUD_CHANNEL9_DISABLES_DEAD_TIME_OPERATION         (0x0000U) /* Disables dead time operation */
#define _TAUD_CHANNEL9_ENABLES_DEAD_TIME_OPERATION          (0x0200U) /* Enables dead time operation */
/* Enables/disables the dead time control operation of channel 8 (TAUD0TDE8) */
#define _TAUD_CHANNEL8_DISABLES_DEAD_TIME_OPERATION         (0x0000U) /* Disables dead time operation */
#define _TAUD_CHANNEL8_ENABLES_DEAD_TIME_OPERATION          (0x0100U) /* Enables dead time operation */
/* Enables/disables the dead time control operation of channel 7 (TAUD0TDE7) */
#define _TAUD_CHANNEL7_DISABLES_DEAD_TIME_OPERATION         (0x0000U) /* Disables dead time operation */
#define _TAUD_CHANNEL7_ENABLES_DEAD_TIME_OPERATION          (0x0080U) /* Enables dead time operation */
/* Enables/disables the dead time control operation of channel 6 (TAUD0TDE6) */
#define _TAUD_CHANNEL6_DISABLES_DEAD_TIME_OPERATION         (0x0000U) /* Disables dead time operation */
#define _TAUD_CHANNEL6_ENABLES_DEAD_TIME_OPERATION          (0x0040U) /* Enables dead time operation */
/* Enables/disables the dead time control operation of channel 5 (TAUD0TDE5) */
#define _TAUD_CHANNEL5_DISABLES_DEAD_TIME_OPERATION         (0x0000U) /* Disables dead time operation */
#define _TAUD_CHANNEL5_ENABLES_DEAD_TIME_OPERATION          (0x0020U) /* Enables dead time operation */
/* Enables/disables the dead time control operation of channel 4 (TAUD0TDE4) */
#define _TAUD_CHANNEL4_DISABLES_DEAD_TIME_OPERATION         (0x0000U) /* Disables dead time operation */
#define _TAUD_CHANNEL4_ENABLES_DEAD_TIME_OPERATION          (0x0010U) /* Enables dead time operation */
/* Enables/disables the dead time control operation of channel 3 (TAUD0TDE3) */
#define _TAUD_CHANNEL3_DISABLES_DEAD_TIME_OPERATION         (0x0000U) /* Disables dead time operation */
#define _TAUD_CHANNEL3_ENABLES_DEAD_TIME_OPERATION          (0x0008U) /* Enables dead time operation */
/* Enables/disables the dead time control operation of channel 2 (TAUD0TDE2) */
#define _TAUD_CHANNEL2_DISABLES_DEAD_TIME_OPERATION         (0x0000U) /* Disables dead time operation */
#define _TAUD_CHANNEL2_ENABLES_DEAD_TIME_OPERATION          (0x0004U) /* Enables dead time operation */
/* Enables/disables the dead time control operation of channel 1 (TAUD0TDE1) */
#define _TAUD_CHANNEL1_DISABLES_DEAD_TIME_OPERATION         (0x0000U) /* Disables dead time operation */
#define _TAUD_CHANNEL1_ENABLES_DEAD_TIME_OPERATION          (0x0002U) /* Enables dead time operation */
/* Enables/disables the dead time control operation of channel 0 (TAUD0TDE0) */
#define _TAUD_CHANNEL0_DISABLES_DEAD_TIME_OPERATION         (0x0000U) /* Disables dead time operation */
#define _TAUD_CHANNEL0_ENABLES_DEAD_TIME_OPERATION          (0x0001U) /* Enables dead time operation */

/*
    TAUDn Channel Dead Time Output Mode Register (TAUD0TDM)
*/
/* Specifies the timing to add dead time during dead time output (TAUD0TDM15) */
#define _TAUD_CHANNEL15_DETECTING_DUTY_CYCLE                (0x0000U) /* When detecting the duty cycle of an upper even channel */
#define _TAUD_CHANNEL15_DETECTING_INPUT_EDGE                (0x8000U) /* When detecting the TIN input edge of a lower odd channel */
/* Specifies the timing to add dead time during dead time output (TAUD0TDM14) */
#define _TAUD_CHANNEL14_DETECTING_DUTY_CYCLE                (0x0000U) /* When detecting the duty cycle of an upper even channel */
#define _TAUD_CHANNEL14_DETECTING_INPUT_EDGE                (0x4000U) /* When detecting the TIN input edge of a lower odd channel */
/* Specifies the timing to add dead time during dead time output (TAUD0TDM13) */
#define _TAUD_CHANNEL13_DETECTING_DUTY_CYCLE                (0x0000U) /* When detecting the duty cycle of an upper even channel */
#define _TAUD_CHANNEL13_DETECTING_INPUT_EDGE                (0x2000U) /* When detecting the TIN input edge of a lower odd channel */
/* Specifies the timing to add dead time during dead time output (TAUD0TDM12) */
#define _TAUD_CHANNEL12_DETECTING_DUTY_CYCLE                (0x0000U) /* When detecting the duty cycle of an upper even channel */
#define _TAUD_CHANNEL12_DETECTING_INPUT_EDGE                (0x1000U) /* When detecting the TIN input edge of a lower odd channel */
/* Specifies the timing to add dead time during dead time output (TAUD0TDM11) */
#define _TAUD_CHANNEL11_DETECTING_DUTY_CYCLE                (0x0000U) /* When detecting the duty cycle of an upper even channel */
#define _TAUD_CHANNEL11_DETECTING_INPUT_EDGE                (0x0800U) /* When detecting the TIN input edge of a lower odd channel */
/* Specifies the timing to add dead time during dead time output (TAUD0TDM10) */
#define _TAUD_CHANNEL10_DETECTING_DUTY_CYCLE                (0x0000U) /* When detecting the duty cycle of an upper even channel */
#define _TAUD_CHANNEL10_DETECTING_INPUT_EDGE                (0x0400U) /* When detecting the TIN input edge of a lower odd channel */
/* Specifies the timing to add dead time during dead time output (TAUD0TDM9) */
#define _TAUD_CHANNEL9_DETECTING_DUTY_CYCLE                 (0x0000U) /* When detecting the duty cycle of an upper even channel */
#define _TAUD_CHANNEL9_DETECTING_INPUT_EDGE                 (0x0200U) /* When detecting the TIN input edge of a lower odd channel */
/* Specifies the timing to add dead time during dead time output (TAUD0TDM8) */
#define _TAUD_CHANNEL8_DETECTING_DUTY_CYCLE                 (0x0000U) /* When detecting the duty cycle of an upper even channel */
#define _TAUD_CHANNEL8_DETECTING_INPUT_EDGE                 (0x0100U) /* When detecting the TIN input edge of a lower odd channel */
/* Specifies the timing to add dead time during dead time output (TAUD0TDM7) */
#define _TAUD_CHANNEL7_DETECTING_DUTY_CYCLE                 (0x0000U) /* When detecting the duty cycle of an upper even channel */
#define _TAUD_CHANNEL7_DETECTING_INPUT_EDGE                 (0x0080U) /* When detecting the TIN input edge of a lower odd channel */
/* Specifies the timing to add dead time during dead time output (TAUD0TDM6) */
#define _TAUD_CHANNEL6_DETECTING_DUTY_CYCLE                 (0x0000U) /* When detecting the duty cycle of an upper even channel */
#define _TAUD_CHANNEL6_DETECTING_INPUT_EDGE                 (0x0040U) /* When detecting the TIN input edge of a lower odd channel */
/* Specifies the timing to add dead time during dead time output (TAUD0TDM5) */
#define _TAUD_CHANNEL5_DETECTING_DUTY_CYCLE                 (0x0000U) /* When detecting the duty cycle of an upper even channel */
#define _TAUD_CHANNEL5_DETECTING_INPUT_EDGE                 (0x0020U) /* When detecting the TIN input edge of a lower odd channel */
/* Specifies the timing to add dead time during dead time output (TAUD0TDM4) */
#define _TAUD_CHANNEL4_DETECTING_DUTY_CYCLE                 (0x0000U) /* When detecting the duty cycle of an upper even channel */
#define _TAUD_CHANNEL4_DETECTING_INPUT_EDGE                 (0x0010U) /* When detecting the TIN input edge of a lower odd channel */
/* Specifies the timing to add dead time during dead time output (TAUD0TDM3) */
#define _TAUD_CHANNEL3_DETECTING_DUTY_CYCLE                 (0x0000U) /* When detecting the duty cycle of an upper even channel */
#define _TAUD_CHANNEL3_DETECTING_INPUT_EDGE                 (0x0008U) /* When detecting the TIN input edge of a lower odd channel */
/* Specifies the timing to add dead time during dead time output (TAUD0TDM2) */
#define _TAUD_CHANNEL2_DETECTING_DUTY_CYCLE                 (0x0000U) /* When detecting the duty cycle of an upper even channel */
#define _TAUD_CHANNEL2_EDETECTING_INPUT_EDGE                (0x0004U) /* When detecting the TIN input edge of a lower odd channel */
/* Specifies the timing to add dead time during dead time output (TAUD0TDM1) */
#define _TAUD_CHANNEL1_DETECTING_DUTY_CYCLE                 (0x0000U) /* When detecting the duty cycle of an upper even channel */
#define _TAUD_CHANNEL1_DETECTING_INPUT_EDGE                 (0x0002U) /* When detecting the TIN input edge of a lower odd channel */
/* Specifies the timing to add dead time during dead time output (TAUD0TDM0) */
#define _TAUD_CHANNEL0_DETECTING_DUTY_CYCLE                 (0x0000U) /* When detecting the duty cycle of an upper even channel */
#define _TAUD_CHANNEL0_DETECTING_INPUT_EDGE                 (0x0001U) /* When detecting the TIN input edge of a lower odd channel */

/*
    TAUD0 Channel Dead Time Output Level Register (TAUD0TDL)
*/
/* Selects a phase in which dead time is added (TAUD0TDL15) */
#define _TAUD_CHANNEL15_NORMAL_PHASE                        (0x0000U) /* Normal phase */
#define _TAUD_CHANNEL15_REVERSE_PHASE                       (0x8000U) /* Reverse phase */
/* Selects a phase in which dead time is added (TAUD0TDL14) */
#define _TAUD_CHANNEL14_NORMAL_PHASE                        (0x0000U) /* Normal phase */
#define _TAUD_CHANNEL14_REVERSE_PHASE                       (0x4000U) /* Reverse phase */
/* Selects a phase in which dead time is added (TAUD0TDL13) */
#define _TAUD_CHANNEL13_NORMAL_PHASE                        (0x0000U) /* Normal phase */
#define _TAUD_CHANNEL13_REVERSE_PHASE                       (0x2000U) /* Reverse phase */
/* Selects a phase in which dead time is added (TAUD0TDL12) */
#define _TAUD_CHANNEL12_NORMAL_PHASE                        (0x0000U) /* Normal phase */
#define _TAUD_CHANNEL12_REVERSE_PHASE                       (0x1000U) /* Reverse phase */
/* Selects a phase in which dead time is added (TAUD0TDL11) */
#define _TAUD_CHANNEL11_NORMAL_PHASE                        (0x0000U) /* Normal phase */
#define _TAUD_CHANNEL11_REVERSE_PHASE                       (0x0800U) /* Reverse phase */
/* Selects a phase in which dead time is added (TAUD0TDL10) */
#define _TAUD_CHANNEL10_NORMAL_PHASE                        (0x0000U) /* Normal phase */
#define _TAUD_CHANNEL10_REVERSE_PHASE                       (0x0400U) /* Reverse phase */
/* Selects a phase in which dead time is added (TAUD0TDL9) */
#define _TAUD_CHANNEL9_NORMAL_PHASE                         (0x0000U) /* Normal phase */
#define _TAUD_CHANNEL9_REVERSE_PHASE                        (0x0200U) /* Reverse phase */
/* Selects a phase in which dead time is added (TAUD0TDL8) */
#define _TAUD_CHANNEL8_NORMAL_PHASE                         (0x0000U) /* Normal phase */
#define _TAUD_CHANNEL8_REVERSE_PHASE                        (0x0100U) /* Reverse phase */
/* Selects a phase in which dead time is added (TAUD0TDL7) */
#define _TAUD_CHANNEL7_NORMAL_PHASE                         (0x0000U) /* Normal phase */
#define _TAUD_CHANNEL7_REVERSE_PHASE                        (0x0080U) /* Reverse phase */
/* Selects a phase in which dead time is added (TAUD0TDL6) */
#define _TAUD_CHANNEL6_NORMAL_PHASE                         (0x0000U) /* Normal phase */
#define _TAUD_CHANNEL6_REVERSE_PHASE                        (0x0040U) /* Reverse phase */
/* Selects a phase in which dead time is added (TAUD0TDL5) */
#define _TAUD_CHANNEL5_NORMAL_PHASE                         (0x0000U) /* Normal phase */
#define _TAUD_CHANNEL5_REVERSE_PHASE                        (0x0020U) /* Reverse phase */
/* Selects a phase in which dead time is added (TAUD0TDL4) */
#define _TAUD_CHANNEL4_NORMAL_PHASE                         (0x0000U) /* Normal phase */
#define _TAUD_CHANNEL4_REVERSE_PHASE                        (0x0010U) /* Reverse phase */
/* Selects a phase in which dead time is added (TAUD0TDL3) */
#define _TAUD_CHANNEL3_NORMAL_PHASE                         (0x0000U) /* Normal phase */
#define _TAUD_CHANNEL3_REVERSE_PHASE                        (0x0008U) /* Reverse phase */
/* Selects a phase in which dead time is added (TAUD0TDL2) */
#define _TAUD_CHANNEL2_NORMAL_PHASE                         (0x0000U) /* Normal phase */
#define _TAUD_CHANNEL2_REVERSE_PHASE                        (0x0004U) /* Reverse phase */
/* Selects a phase in which dead time is added (TAUD0TDL1) */
#define _TAUD_CHANNEL1_NORMAL_PHASE                         (0x0000U) /* Normal phase */
#define _TAUD_CHANNEL1_REVERSE_PHASE                        (0x0002U) /* Reverse phase */
/* Selects a phase in which dead time is added (TAUD0TDL0) */
#define _TAUD_CHANNEL0_NORMAL_PHASE                         (0x0000U) /* Normal phase */
#define _TAUD_CHANNEL0_REVERSE_PHASE                        (0x0001U) /* Reverse phase */

/*
    TAUD0 Channel Real-time Output Enable Register (TAUD0TRE)
*/
/* Enables or disables real-time output of channel 15 (TAUD0TRE15) */
#define _TAUD_CHANNEL15_REAL_TIME_OUTPUT_DISABLES           (0x0000U) /* Disables real-time output */
#define _TAUD_CHANNEL15_REAL_TIME_OUTPUT_ENABLES            (0x8000U) /* Enables real-time output */
/* Enables or disables real-time output of channel 14 (TAUD0TRE14) */
#define _TAUD_CHANNEL14_REAL_TIME_OUTPUT_DISABLES           (0x0000U) /* Disables real-time output */
#define _TAUD_CHANNEL14_REAL_TIME_OUTPUT_ENABLES            (0x4000U) /* Enables real-time output */
/* Enables or disables real-time output of channel 13 (TAUD0TRE13) */
#define _TAUD_CHANNEL13_REAL_TIME_OUTPUT_DISABLES           (0x0000U) /* Disables real-time output */
#define _TAUD_CHANNEL13_REAL_TIME_OUTPUT_ENABLES            (0x2000U) /* Enables real-time output */
/* Enables or disables real-time output of channel 12 (TAUD0TRE12) */
#define _TAUD_CHANNEL12_REAL_TIME_OUTPUT_DISABLES           (0x0000U) /* Disables real-time output */
#define _TAUD_CHANNEL12_REAL_TIME_OUTPUT_ENABLES            (0x1000U) /* Enables real-time output */
/* Enables or disables real-time output of channel 11 (TAUD0TRE11) */
#define _TAUD_CHANNEL11_REAL_TIME_OUTPUT_DISABLES           (0x0000U) /* Disables real-time output */
#define _TAUD_CHANNEL11_REAL_TIME_OUTPUT_ENABLES            (0x0800U) /* Enables real-time output */
/* Enables or disables real-time output of channel 10 (TAUD0TRE10) */
#define _TAUD_CHANNEL10_REAL_TIME_OUTPUT_DISABLES           (0x0000U) /* Disables real-time output */
#define _TAUD_CHANNEL10_REAL_TIME_OUTPUT_ENABLES            (0x0400U) /* Enables real-time output */
/* Enables or disables real-time output of channel 9 (TAUD0TRE9) */
#define _TAUD_CHANNEL9_REAL_TIME_OUTPUT_DISABLES            (0x0000U) /* Disables real-time output */
#define _TAUD_CHANNEL9_REAL_TIME_OUTPUT_ENABLES             (0x0200U) /* Enables real-time output */
/* Enables or disables real-time output of channel 8 (TAUD0TRE8) */
#define _TAUD_CHANNEL8_REAL_TIME_OUTPUT_DISABLES            (0x0000U) /* Disables real-time output */
#define _TAUD_CHANNEL8_REAL_TIME_OUTPUT_ENABLES             (0x0100U) /* Enables real-time output */
/* Enables or disables real-time output of channel 7 (TAUD0TRE7) */
#define _TAUD_CHANNEL7_REAL_TIME_OUTPUT_DISABLES            (0x0000U) /* Disables real-time output */
#define _TAUD_CHANNEL7_REAL_TIME_OUTPUT_ENABLES             (0x0080U) /* Enables real-time output */
/* Enables or disables real-time output of channel 6 (TAUD0TRE6) */
#define _TAUD_CHANNEL6_REAL_TIME_OUTPUT_DISABLES            (0x0000U) /* Disables real-time output */
#define _TAUD_CHANNEL6_REAL_TIME_OUTPUT_ENABLES             (0x0040U) /* Enables real-time output */
/* Enables or disables real-time output of channel 5 (TAUD0TRE5) */
#define _TAUD_CHANNEL5_REAL_TIME_OUTPUT_DISABLES            (0x0000U) /* Disables real-time output */
#define _TAUD_CHANNEL5_REAL_TIME_OUTPUT_ENABLES             (0x0020U) /* Enables real-time output */
/* Enables or disables real-time output of channel 4 (TAUD0TRE4) */
#define _TAUD_CHANNEL4_REAL_TIME_OUTPUT_DISABLES            (0x0000U) /* Disables real-time output */
#define _TAUD_CHANNEL4_REAL_TIME_OUTPUT_ENABLES             (0x0010U) /* Enables real-time output */
/* Enables or disables real-time output of channel 3 (TAUD0TRE3) */
#define _TAUD_CHANNEL3_REAL_TIME_OUTPUT_DISABLES            (0x0000U) /* Disables real-time output */
#define _TAUD_CHANNEL3_REAL_TIME_OUTPUT_ENABLES             (0x0008U) /* Enables real-time output */
/* Enables or disables real-time output of channel 2 (TAUD0TRE2) */
#define _TAUD_CHANNEL2_REAL_TIME_OUTPUT_DISABLES            (0x0000U) /* Disables real-time output */
#define _TAUD_CHANNEL2_REAL_TIME_OUTPUT_ENABLES             (0x0004U) /* Enables real-time output */
/* Enables or disables real-time output of channel 1 (TAUD0TRE1) */
#define _TAUD_CHANNEL1_REAL_TIME_OUTPUT_DISABLES            (0x0000U) /* Disables real-time output */
#define _TAUD_CHANNEL1_REAL_TIME_OUTPUT_ENABLES             (0x0002U) /* Enables real-time output */
/* Enables or disables real-time output of channel 0 (TAUD0TRE0) */
#define _TAUD_CHANNEL0_REAL_TIME_OUTPUT_DISABLES            (0x0000U) /* Disables real-time output */
#define _TAUD_CHANNEL0_REAL_TIME_OUTPUT_ENABLES             (0x0001U) /* Enables real-time output */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _TAUD0_CK3_PRE_CLOCK_DIVISION                       (0x00U) /* Division factor of prescaler clock CK3 */
#define _TAUD0_CHANNEL6_COMPARE_VALUE                       (0x4C4AU) /* Data register for capture/compare values */
#define _TAUD0_CHANNEL7_COMPARE_VALUE                       (0x2625U) /* Data register for capture/compare values */
#define _TAUD0_CHANNEL0_COMPARE_VALUE                       (0x03E7U) /* Data register for capture/compare values */
/* Overflow macro */
#define _TAUD_OVERFLOW_OCCURS                               (0x01U) /* Overflow occurs */
#define _TAUD_OVERFLOW_VALUE                                (0x10000U) /* Overflow value */
#define _TAUD_FILTER_ENABLED                                (0x01U) /* Digital Noise Elimination Enable Control */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_TAUD0_Create(void);
void R_TAUD0_Channel6_Start(void);
void R_TAUD0_Channel6_Stop(void);
void R_TAUD0_Channel0_Start(void);
void R_TAUD0_Channel0_Stop(void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif