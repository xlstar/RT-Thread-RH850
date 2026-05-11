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
* File Name    : r_cg_csih.h
* Version      :
* Device(s)    : R7F701587(LQFP176pin)
* Tool-Chain   : CCRH
* Description  : This file implements device driver for CSIH module.
* Creation Date: 2018/5/10
***********************************************************************************************************************/
#ifndef CSIH_H
#define CSIH_H
#include <r_cg_macrodriver.h>

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    CSIH Control Register 0 (CSIHnCTL0)
*/
/* Controls the operation clock (CSIHnPWR) */
#define _CSIH_OPERATION_CLOCK_STOP                (0x00U) /* Stops operation clock */
#define _CSIH_OPERATION_CLOCK_PROVIDE             (0x80U) /* Provides operation clock */
/* Permits or prohibits transmission (CSIHnTXE) */
#define _CSIH_TRANSMISSION_PROHIBIT               (0x00U) /* Prohibits transmission */
#define _CSIH_TRANSMISSION_PERMIT                 (0x40U) /* Permits transmission */
/* Permits or prohibits reception (CSIHnRXE) */
#define _CSIH_RECEPTION_PROHIBIT                  (0x00U) /* Prohibits reception */
#define _CSIH_RECEPTION_PERMIT                    (0x20U) /* Permits reception */
/* Enables direct access mode (CSIHnMBS) */
#define _CSIH_OPERATION_PROHIBITED                (0x00U) /* CSIH transmit/receive operation is prohibited */
#define _CSIH_DIRECTACCESS                        (0x01U) /* Direct access mode */

/*
    CSIH Control Register 1 (CSIHnCTL1)
*/
/* Sets the internal synchronization timing for receive data input (CSIHnSLRS) */
#define _CSIH_SYNCHRONIZATION_RISING_EDGE         (0x00000000U) /* Rising edge of PCLK */
#define _CSIH_SYNCHRONIZATION_FALLING_EDGE        (0x01000000U) /* Falling edge of PCLK */
/* CSIHnTSCK Clock Inverting Function (CSIHnCKR) */
#define _CSIH_CLOCK_INVERTING_HIGH                (0x00000000U) /* Default of CSIHnTSCK is high level */
#define _CSIH_CLOCK_INVERTING_LOW                 (0x00020000U) /* Default of CSIHnTSCK is low level */
/* Selects the timing of interrupt INT_CSIHTIC (CSIHnSLIT) */
#define _CSIH_INTERRUPT_TIMING_NORMAL             (0x00000000U) /* Normal interrupt timing */
#define _CSIH_INTERRUPT_TIMING_TRANSFERRED        (0x00010000U) /* an interrupt is generated when transfer */
/* Selects the active output level of chip select signal 7 (CSIHnCSL7) */
#define _CSIH_CHIPSELECT7_ACTIVE_LOW              (0x00000000U) /* Chip select is active low */
#define _CSIH_CHIPSELECT7_ACTIVE_HIGH             (0x00008000U) /* Chip select is active high */
/* Selects the active output level of chip select signal 6 (CSIHnCSL6) */
#define _CSIH_CHIPSELECT6_ACTIVE_LOW              (0x00000000U) /* Chip select is active low */
#define _CSIH_CHIPSELECT6_ACTIVE_HIGH             (0x00004000U) /* Chip select is active high */
/* Selects the active output level of chip select signal 5 (CSIHnCSL5) */
#define _CSIH_CHIPSELECT5_ACTIVE_LOW              (0x00000000U) /* Chip select is active low */
#define _CSIH_CHIPSELECT5_ACTIVE_HIGH             (0x00002000U) /* Chip select is active high */
/* Selects the active output level of chip select signal 4 (CSIHnCSL4) */
#define _CSIH_CHIPSELECT4_ACTIVE_LOW              (0x00000000U) /* Chip select is active low */
#define _CSIH_CHIPSELECT4_ACTIVE_HIGH             (0x00001000U) /* Chip select is active high */
/* Selects the active output level of chip select signal 3 (CSIHnCSL3) */
#define _CSIH_CHIPSELECT3_ACTIVE_LOW              (0x00000000U) /* Chip select is active low */
#define _CSIH_CHIPSELECT3_ACTIVE_HIGH             (0x00000800U) /* Chip select is active high */
/* Selects the active output level of chip select signal 2 (CSIHnCSL2) */
#define _CSIH_CHIPSELECT2_ACTIVE_LOW              (0x00000000U) /* Chip select is active low */
#define _CSIH_CHIPSELECT2_ACTIVE_HIGH             (0x00000400U) /* Chip select is active high */
/* Selects the active output level of chip select signal 1 (CSIHnCSL1) */
#define _CSIH_CHIPSELECT1_ACTIVE_LOW              (0x00000000U) /* Chip select is active low */
#define _CSIH_CHIPSELECT1_ACTIVE_HIGH             (0x00000200U) /* Chip select is active high */
/* Selects the active output level of chip select signal 0 (CSIHnCSL0) */
#define _CSIH_CHIPSELECT0_ACTIVE_LOW              (0x00000000U) /* Chip select is active low */
#define _CSIH_CHIPSELECT0_ACTIVE_HIGH             (0x00000100U) /* Chip select is active high */
/* Enables/disables data consistency check (CSIHnDCS) */
#define _CSIH_DATA_CONSISTENCY_CHECK_DISABLE      (0x00000000U) /* Disables data consistency check */
#define _CSIH_DATA_CONSISTENCY_CHECK_ENABLE       (0x00000020U) /* Enables data consistency check */
/* Defines chip select signal behavior after last data transfer (CSIHnCSRI) */
#define _CSIH_CHIPSELECT_SIGNAL_HOLD_ACTIVE       (0x00000000U) /* Chip select signal holds the active level */
#define _CSIH_CHIPSELECT_SIGNAL_HOLD_INACTIVE     (0x00000010U) /* Chip select signal returns to the inactive level */
/* Controls loop-back mode (CSIHnLBM) */
#define _CSIH_LOOP_BACK_DEACTIVE                  (0x00000000U) /* Deactivates loop-back mode */
#define _CSIH_LOOP_BACK_ACTIVE                    (0x00000008U) /* Activates loop-back mode */
/* Selects interrupt delay mode (CSIHnSIT) */
#define _CSIH_NO_DELAY                            (0x00000000U) /* No delay is generated */
#define _CSIH_HALF_CLOCK_DELAY                    (0x00000004U) /* Half clock delay is generated for all interrupts */
/* Enables/disables handshake mode (CSIHnHSE) */
#define _CSIH_HANDSHAKE_DISABLE                   (0x00000000U) /* Disables the handshake function */
#define _CSIH_HANDSHAKE_ENABLE                    (0x00000002U) /* Enables the handshake function */
/* Enables/disables the slave select function (CSIHnSSE) */
#define _CSIH_SLAVE_SELECT_DISABLE                (0x00000000U) /* Input signal CSIHnTSSI is ignored */
#define _CSIH_SLAVE_SELECT_ENABLE                 (0x00000001U) /* Input signal CSIHnTSSI is recognized */

/*
    CSIH Status Register 0 (CSIHnSTR0)
*/
/* Transfer status flag (CSIHnTSF) */
#define _CSIH_TRANSFER_IDLE_STATE                 (0x00000000U) /* Idle state */
#define _CSIH_TRANSFER_WORKING_STATE              (0x00000080U) /* Transmission is in progress or being prepared */
/* Data consistency check error flag (CSIHnDCE) */
#define _CSIH_CONSISTENCY_ERROR_UNDETECTED        (0x00000000U) /* No data consistency error is detected */
#define _CSIH_CONSISTENCY_ERROR_DETECTED          (0x00000008U) /* Data consistency error is detected */
/* Parity error flag (CSIHnPE) */
#define _CSIH_PARITY_ERROR_UNDETECTED             (0x00000000U) /* No parity error is detected */
#define _CSIH_PARITY_ERROR_DETECTED               (0x00000002U) /* Parity error is detected */
/* Overrun error flag (CSIHnOVE) */
#define _CSIH_OVERRUN_ERROR_UNDETECTED            (0x00000000U) /* No overrun error is detected */
#define _CSIH_OVERRUN_ERROR_DETECTED              (0x00000001U) /* Overrun error is detected */

/*
    CSIH Status Clear Register 0 (CSIHnSTCR0)
*/
/* Controls the data consistency error flag clear command (CSIHnDCEC) */
#define _CSIH_CONSISTENCY_ERROR_CLEAR             (0x0008U) /* Clears the data consistency error flag */
/* Controls the parity error flag clear command (CSIHnPEC) */
#define _CSIH_PARITY_ERROR_CLEAR                  (0x0002U) /* Clears the parity error flag */
/* Controls the overrun error flag clear command (CSIHnOVEC) */
#define _CSIH_OVERRUN_ERROR_CLEAR                 (0x0001U) /* Clears the overrun error flag */

/*
    CSIH Configuration Register m (CSIHnCFGm)
*/
/* A register used to set the baud rate (CSIHnBRSSm1,CSIHnBRSSm0) */
#define _CSIH_USED_BAUDRATE_0                     (0x00000000U) /* baudrate is same with the CSIHnBRS0 setting */
#define _CSIH_USED_BAUDRATE_1                     (0x40000000U) /* baudrate is same with the CSIHnBRS1 setting */
#define _CSIH_USED_BAUDRATE_2                     (0x80000000U) /* baudrate is same with the CSIHnBRS2 setting */
#define _CSIH_USED_BAUDRATE_3                     (0xC0000000U) /* baudrate is same with the CSIHnBRS3 setting */
/* Selects the parity for sending or receiving chip select signal m (CSIHnPSm1,CSIHnPSm0) */
#define _CSIH_PARITY_NO                           (0x00000000U) /* No parity is expected */
#define _CSIH_PARITY_ZERO                         (0x10000000U) /* Set parity is zero */
#define _CSIH_PARITY_ODD                          (0x20000000U) /* Set parity is odd */
#define _CSIH_PARITY_EVEN                         (0x30000000U) /* Set parity is even */
/* Selects the data length for chip select sinal m (CSIHnDLSm3,CSIHnDLSm2,CSIHnDLSm1,CSIHnDLSm0) */
#define _CSIH_DATA_LENGTH_16                      (0x00000000U) /* Selects the data length for chip select sinal */
#define _CSIH_DATA_LENGTH_1                       (0x01000000U) /* Selects the data length for chip select sinal */
#define _CSIH_DATA_LENGTH_2                       (0x02000000U) /* Selects the data length for chip select sinal */
#define _CSIH_DATA_LENGTH_3                       (0x03000000U) /* Selects the data length for chip select sinal */
#define _CSIH_DATA_LENGTH_4                       (0x04000000U) /* Selects the data length for chip select sinal */
#define _CSIH_DATA_LENGTH_5                       (0x05000000U) /* Selects the data length for chip select sinal */
#define _CSIH_DATA_LENGTH_6                       (0x06000000U) /* Selects the data length for chip select sinal */
#define _CSIH_DATA_LENGTH_7                       (0x07000000U) /* Selects the data length for chip select sinal */
#define _CSIH_DATA_LENGTH_8                       (0x08000000U) /* Selects the data length for chip select sinal */
#define _CSIH_DATA_LENGTH_9                       (0x09000000U) /* Selects the data length for chip select sinal */
#define _CSIH_DATA_LENGTH_10                      (0x0A000000U) /* Selects the data length for chip select sinal */
#define _CSIH_DATA_LENGTH_11                      (0x0B000000U) /* Selects the data length for chip select sinal */
#define _CSIH_DATA_LENGTH_12                      (0x0C000000U) /* Selects the data length for chip select sinal */
#define _CSIH_DATA_LENGTH_13                      (0x0D000000U) /* Selects the data length for chip select sinal */
#define _CSIH_DATA_LENGTH_14                      (0x0E000000U) /* Selects the data length for chip select sinal */
#define _CSIH_DATA_LENGTH_15                      (0x0F000000U) /* Selects the data length for chip select sinal */
/* Selects the serial data direction (CSIHnDIRm) */
#define _CSIH_DATA_DIRECTION_MSB                  (0x00000000U) /* Data is sent/received with MSB first */
#define _CSIH_DATA_DIRECTION_LSB                  (0x00040000U) /* Data is sent/received with LSB first */
/* Clock and Data Phase Selection (CSIHnCKPm,CSIHnDAPm) */
#define _CSIHn_MASTER_PHASE_SELECTION_TYPE1       (0x00000000U) /* type1 */
#define _CSIHn_MASTER_PHASE_SELECTION_TYPE3       (0x00010000U) /* type3 */
#define _CSIHn_MASTER_PHASE_SELECTION_TYPE2       (0x00020000U) /* type2 */
#define _CSIHn_MASTER_PHASE_SELECTION_TYPE4       (0x00030000U) /* type4 */
#define _CSIHn_SLAVE_PHASE_SELECTION_TYPE2        (0x00000000U) /* type2 */
#define _CSIHn_SLAVE_PHASE_SELECTION_TYPE4        (0x00010000U) /* type4 */
#define _CSIHn_SLAVE_PHASE_SELECTION_TYPE1        (0x00000000U) /* type1 */
#define _CSIHn_SLAVE_PHASE_SELECTION_TYPE3        (0x00010000U) /* type3 */
/* Selects the idle enforcement configuration for chip select m (CSIHnIDLm) */
#define _CSIH_IDLE_INSERTED_NOT_ALWAYS            (0x00000000U) /* an idle state is not always inserted */
#define _CSIH_IDLE_INSERTED_ALWAYS                (0x00008000U) /* an idle state is always inserted */
/* Selects the idle time for chip select signal m (CSIHnIDm) */
#define _CSIH_IDLE_TIME_0                         (0x00000000U) /* 0.5 or 1.0 transmission clock cycle */
#define _CSIH_IDLE_TIME_1                         (0x00001000U) /* 1.0 or 1.5 transmission clock cycle */
#define _CSIH_IDLE_TIME_2                         (0x00002000U) /* 1.5 or 2.0 transmission clock cycle */
#define _CSIH_IDLE_TIME_3                         (0x00003000U) /* 2.5 or 3.0 transmission clock cycle */
#define _CSIH_IDLE_TIME_4                         (0x00004000U) /* 3.5 or 4.0 transmission clock cycle */
#define _CSIH_IDLE_TIME_5                         (0x00005000U) /* 4.5 or 5.0 transmission clock cycle */
#define _CSIH_IDLE_TIME_6                         (0x00006000U) /* 6.5 or 7.0 transmission clock cycle */
#define _CSIH_IDLE_TIME_7                         (0x00007000U) /* 8.5 or 9.0 transmission clock cycle */
/* Specifies the hold time for chip select signal m in transmission clock cycles (CSIHnHDm) */
#define _CSIH_HOLD_TIME_0                         (0x00000000U) /* 0.5 or 1.0 transmission clock cycle */
#define _CSIH_HOLD_TIME_1                         (0x00000100U) /* 1.0 or 1.5 transmission clock cycle */
#define _CSIH_HOLD_TIME_2                         (0x00000200U) /* 1.5 or 2.0 transmission clock cycle */
#define _CSIH_HOLD_TIME_3                         (0x00000300U) /* 2.5 or 3.0 transmission clock cycle */
#define _CSIH_HOLD_TIME_4                         (0x00000400U) /* 3.5 or 4.0 transmission clock cycle */
#define _CSIH_HOLD_TIME_5                         (0x00000500U) /* 4.5 or 5.0 transmission clock cycle */
#define _CSIH_HOLD_TIME_6                         (0x00000600U) /* 6.5 or 7.0 transmission clock cycle */
#define _CSIH_HOLD_TIME_7                         (0x00000700U) /* 8.5 or 9.0 transmission clock cycle */
#define _CSIH_HOLD_TIME_8                         (0x00000800U) /* 9.5 or 10.0 transmission clock cycle */
#define _CSIH_HOLD_TIME_9                         (0x00000900U) /* 10.5 or 11.0 transmission clock cycle */
#define _CSIH_HOLD_TIME_10                        (0x00000A00U) /* 11.5 or 12.0 transmission clock cycle */
#define _CSIH_HOLD_TIME_11                        (0x00000B00U) /* 12.5 or 13.0 transmission clock cycle */
#define _CSIH_HOLD_TIME_12                        (0x00000C00U) /* 14.5 or 15.0 transmission clock cycle */
#define _CSIH_HOLD_TIME_13                        (0x00000D00U) /* 16.5 or 17.0 transmission clock cycle */
#define _CSIH_HOLD_TIME_14                        (0x00000E00U) /* 18.5 or 19.0 transmission clock cycle */
#define _CSIH_HOLD_TIME_15                        (0x00000F00U) /* 20.5 or 21.0 transmission clock cycle */
/* Specifies the inter-data delay time for chip select signal m in transmission clock cycles (CSIHnINm) */
#define _CSIH_INTER_DATA_DELAY_TIME_0             (0x00000000U) /* 0.0 or 0.5 transmission clock cycle */
#define _CSIH_INTER_DATA_DELAY_TIME_1             (0x00000010U) /* 0.5 or 1.0 transmission clock cycle */
#define _CSIH_INTER_DATA_DELAY_TIME_2             (0x00000020U) /* 1.0 or 1.5 transmission clock cycle */
#define _CSIH_INTER_DATA_DELAY_TIME_3             (0x00000030U) /* 2.0 or 2.5 transmission clock cycle */
#define _CSIH_INTER_DATA_DELAY_TIME_4             (0x00000040U) /* 3.0 or 3.5 transmission clock cycle */
#define _CSIH_INTER_DATA_DELAY_TIME_5             (0x00000050U) /* 4.0 or 4.5 transmission clock cycle */
#define _CSIH_INTER_DATA_DELAY_TIME_6             (0x00000060U) /* 6.0 or 6.5 transmission clock cycle */
#define _CSIH_INTER_DATA_DELAY_TIME_7             (0x00000070U) /* 8.0 or 8.5 transmission clock cycle */
#define _CSIH_INTER_DATA_DELAY_TIME_8             (0x00000080U) /* 9.0 or 9.5 transmission clock cycle */
#define _CSIH_INTER_DATA_DELAY_TIME_9             (0x00000090U) /* 10.0 or 10.5 transmission clock cycle */
#define _CSIH_INTER_DATA_DELAY_TIME_10            (0x000000A0U) /* 11.0 or 11.5 transmission clock cycle */
#define _CSIH_INTER_DATA_DELAY_TIME_11            (0x000000B0U) /* 12.0 or 12.5 transmission clock cycle */
#define _CSIH_INTER_DATA_DELAY_TIME_12            (0x000000C0U) /* 14.0 or 14.5 transmission clock cycle */
#define _CSIH_INTER_DATA_DELAY_TIME_13            (0x000000D0U) /* 16.0 or 16.5 transmission clock cycle */
#define _CSIH_INTER_DATA_DELAY_TIME_14            (0x000000E0U) /* 18.0 or 18.5 transmission clock cycle */
#define _CSIH_INTER_DATA_DELAY_TIME_15            (0x000000F0U) /* 20.0 or 20.5 transmission clock cycle */
/* Specifies the setup time for chip select signal m in transmission clock cycles (CSIHnSPm) */
#define _CSIH_SETUP_TIME_0                        (0x00000000U) /* 0.5 transmission clock cycle */
#define _CSIH_SETUP_TIME_1                        (0x00000001U) /* 1.0 transmission clock cycle */
#define _CSIH_SETUP_TIME_2                        (0x00000002U) /* 1.5 transmission clock cycle */
#define _CSIH_SETUP_TIME_3                        (0x00000003U) /* 2.5 transmission clock cycle */
#define _CSIH_SETUP_TIME_4                        (0x00000004U) /* 3.5 transmission clock cycle */
#define _CSIH_SETUP_TIME_5                        (0x00000005U) /* 4.5 transmission clock cycle */
#define _CSIH_SETUP_TIME_6                        (0x00000006U) /* 6.5 transmission clock cycle */
#define _CSIH_SETUP_TIME_7                        (0x00000007U) /* 8.5 transmission clock cycle */
#define _CSIH_SETUP_TIME_8                        (0x00000008U) /* 9.5 transmission clock cycle */
#define _CSIH_SETUP_TIME_9                        (0x00000009U) /* 10.5 transmission clock cycle */
#define _CSIH_SETUP_TIME_10                       (0x0000000AU) /* 11.5 transmission clock cycle */
#define _CSIH_SETUP_TIME_11                       (0x0000000BU) /* 12.5 transmission clock cycle */
#define _CSIH_SETUP_TIME_12                       (0x0000000CU) /* 14.5 transmission clock cycle */
#define _CSIH_SETUP_TIME_13                       (0x0000000DU) /* 16.5 transmission clock cycle */
#define _CSIH_SETUP_TIME_14                       (0x0000000EU) /* 18.5 transmission clock cycle */
#define _CSIH_SETUP_TIME_15                       (0x0000000FU) /* 20.5 transmission clock cycle */

/*
    CSIH Transmit Data Register 0 for Word Access (CSIHnTX0W)
*/
/* Activates one or several chip select signals (CSIHnCS7) */
#define _CSIH_SELECT_CHIP_7                       (0x09U) /* CSIH SELECT CHIP 7 */
//#define _CSIH_SELECT_CHIP_7                       (0x00800000U) /* CSIH SELECT CHIP 7 */
/* Activates one or several chip select signals (CSIHnCS6) */
#define _CSIH_SELECT_CHIP_6                       (0x08U) /* CSIH SELECT CHIP 6 */
//#define _CSIH_SELECT_CHIP_6                       (0x00400000U) /* CSIH SELECT CHIP 6 */
/* Activates one or several chip select signals (CSIHnCS5) */
#define _CSIH_SELECT_CHIP_5                       (0x07U) /* CSIH SELECT CHIP 5 */
//#define _CSIH_SELECT_CHIP_5                       (0x00200000U) /* CSIH SELECT CHIP 5 */
/* Activates one or several chip select signals (CSIHnCS4) */
#define _CSIH_SELECT_CHIP_4                       (0x06U) /* CSIH SELECT CHIP 4 */
//#define _CSIH_SELECT_CHIP_4                       (0x00100000U) /* CSIH SELECT CHIP 4 */
/* Activates one or several chip select signals (CSIHnCS3) */
#define _CSIH_SELECT_CHIP_3                       (0x04U) /* CSIH SELECT CHIP 3 */
//#define _CSIH_SELECT_CHIP_3                       (0x00080000U) /* CSIH SELECT CHIP 3 */
/* Activates one or several chip select signals (CSIHnCS2) */
#define _CSIH_SELECT_CHIP_2                       (0x03U) /* CSIH SELECT CHIP 2 */
//#define _CSIH_SELECT_CHIP_2                       (0x00040000U) /* CSIH SELECT CHIP 2 */
/* Activates one or several chip select signals (CSIHnCS1) */
#define _CSIH_SELECT_CHIP_1                       (0x02U) /* CSIH SELECT CHIP 1 */
//#define _CSIH_SELECT_CHIP_1                       (0x00020000U) /* CSIH SELECT CHIP 1 */
/* Activates one or several chip select signals (CSIHnCS0) */
#define _CSIH_SELECT_CHIP_0                       (0x01U) /* CSIH SELECT CHIP 0 */
//#define _CSIH_SELECT_CHIP_0                       (0x00010000U) /* CSIH SELECT CHIP 0 */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _CSIH0_SELECT_BASIC_CLOCK                 (0x2000U) /* Selects the basic clock */
#define _CSIH_SELECT_CHIP_SUM_0                   (0x00FF0000U) /* CSIH SELECT CHIP SUM */
#define _CSIH_SELECT_CHIP_SUM_1                   (0x003F0000U) /* CSIH SELECT CHIP SUM */
#define _CSIH_SELECT_CHIP_SUM_2                   (0x000F0000U) /* CSIH SELECT CHIP SUM */
#define _CSIH_RECEIVE_SETTING_INIT                (0x00FF0000U) /* Receive setting init value */
#define _CSIH_TRANSMIT_SETTING_INIT               (0x00FF0000U) /* Transmit setting init value */
#define _CSIH_TRANSMIT_EXTEND_DATA_SIZE           (0x000FU) /* Transmit extend data size */
#define _CSIH_SLAVE_TRANSMIT_SETTING_INIT         (0x00FE0000U) /* Transmit setting init value */
#define _CSIH0_BAUD_RATE_0                        (0x0823U) /* baudrate set */
#define _CSIH0_BAUD_RATE_1                        (0x0823U) /* baudrate set */
#define _CSIH0_BAUD_RATE_2                        (0x0823U) /* baudrate set */
#define _CSIH0_BAUD_RATE_3                        (0x0823U) /* baudrate set */

#define _CSIH1_SELECT_BASIC_CLOCK                 (0x2000U) /* Selects the basic clock */
#define _CSIH1_BAUD_RATE_0                        (0x000FU) /* baudrate set */
#define _CSIH1_BAUD_RATE_1                        (0x0823U) /* baudrate set */
#define _CSIH1_BAUD_RATE_2                        (0x0412U) /* baudrate set */
#define _CSIH1_BAUD_RATE_3                        (0x0823U) /* baudrate set */

#define _CSIH2_SELECT_BASIC_CLOCK                 (0x2000U) /* Selects the basic clock */
#define _CSIH2_BAUD_RATE_0                        (0x000FU) /* baudrate set */
#define _CSIH2_BAUD_RATE_1                        (0x0823U) /* baudrate set */
#define _CSIH2_BAUD_RATE_2                        (0x0412U) /* baudrate set */
#define _CSIH2_BAUD_RATE_3                        (0x0823U) /* baudrate set */

#define _CSIH3_SELECT_BASIC_CLOCK                 (0x2000U) /* Selects the basic clock */
#define _CSIH3_BAUD_RATE_0                        (0x0014U) /* baudrate set */
#define _CSIH3_BAUD_RATE_1                        (0x0823U) /* baudrate set */
#define _CSIH3_BAUD_RATE_2                        (0x0823U) /* baudrate set */
#define _CSIH3_BAUD_RATE_3                        (0x0823U) /* baudrate set */
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/



/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_CSIH0_Create(void);
void R_CSIH0_Start(void);
void R_CSIH0_Stop(void);
MD_STATUS R_CSIH0_Master_Send(const uint16_t *tx_buf, uint16_t tx_num, uint32_t chip_id);
MD_STATUS R_CSIH0_Master_Receive(uint16_t *rx_buf, uint16_t rx_num, uint32_t chipid);
static void r_csih0_callback_receiveend(void);

void R_CSIH1_Create(void);
void R_CSIH1_Start(void);
void R_CSIH1_Stop(void);
MD_STATUS R_CSIH1_Master_Send(const uint16_t *tx_buf, uint16_t tx_num, uint32_t chip_id);
MD_STATUS R_CSIH1_Master_Receive(uint16_t *rx_buf, uint16_t rx_num, uint32_t chipid);
static void r_csih1_callback_receiveend(void);


void R_CSIH2_Create(void);
void R_CSIH2_Start(void);
void R_CSIH2_Stop(void);
MD_STATUS R_CSIH2_Master_Send(const uint16_t *tx_buf, uint16_t tx_num, uint32_t chip_id);
MD_STATUS R_CSIH2_Master_Receive(uint16_t *rx_buf, uint16_t rx_num, uint32_t chipid);
static void r_csih2_callback_receiveend(void);
static void r_csih2_callback_sendend(void);
static void r_csih2_callback_error(uint32_t err_type);


void R_CSIH3_Create(void);
void R_CSIH3_Start(void);
void R_CSIH3_Stop(void);
MD_STATUS R_CSIH3_Master_Send(const uint16_t *tx_buf, uint16_t tx_num, uint32_t chip_id);
MD_STATUS R_CSIH3_Master_Receive(uint16_t *rx_buf, uint16_t rx_num, uint32_t chipid);
//MD_STATUS CSIH3_Master_Send(unsigned char *transmit_data, unsigned char transmit_length);
MD_STATUS R_CSIH3_Master_Send2();
MD_STATUS R_CSIH3_Master_Send3(uint8_t *data, uint8_t *rddata);
MD_STATUS CSIH3_Master_Send4(uint8_t *data, uint8_t *rddata);
void r_CSIH3_Transfer(void);

MD_STATUS CSIH3_Master_Send1(uint8_t *transmit_data, uint16_t transmit_length);
static void r_csih3_callback_receiveend(void);

/* Start user code for function. Do not edit comment generated here */

/* End user code. Do not edit comment generated here */
#endif
