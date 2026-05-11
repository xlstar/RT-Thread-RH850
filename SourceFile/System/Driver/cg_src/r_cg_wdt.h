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
* Copyright (C) 2015, 2018 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_wdt.h
* Version      : Code Generator for RH850/F1K V1.01.02.02 [08 May 2018]
* Device(s)    : R7F701581(LQFP100pin)
* Tool-Chain   : CCRH
* Description  : This file implements device driver for WDTA module.
* Creation Date: 2022/3/26
***********************************************************************************************************************/
#ifndef WDTA_H
#define WDTA_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    WDT start control and trigger register (WDTAnWDTE)
*/
/* Enables/disables the WDT (WDTAnWDTE[7-0]) */
#define _WDT_START_CODE                           (0xACU) /* WDT enabled */
#define _WDT_RESET_CODE                           (0x11U) /* WDT disabled */

/*
    WDT mode setting register (WDTAnMD)
*/
/* Select the overflow time (WDTAnOVF2,WDTAnOVF1,WDTAnOVF0,) */
#define _WDT_OVERFLOW_WDTACKI_2_9                 (0x00U)		// 2^9/240K*128 = 2^9/4.2 us = 122 us  273ms
#define _WDT_OVERFLOW_WDTACKI_2_10                (0x10U)		// 2^10/240k*128 = 2^10/4.2 us = 244us	546ms
#define _WDT_OVERFLOW_WDTACKI_2_11                (0x20U)		// 2^11/240k*128 = 2^11/4.2 us = 488us	1092ms
#define _WDT_OVERFLOW_WDTACKI_2_12                (0x30U)		// 2^12/240k*128 = 2^12/4.2 us = 975us	2185ms
#define _WDT_OVERFLOW_WDTACKI_2_13                (0x40U)		// 2^13/240k*128 = 2^13/4.2 us = 1.95ms	4369ms
#define _WDT_OVERFLOW_WDTACKI_2_14                (0x50U)		// 2^14/240k*128 = 2^14/4.2 us = 3.9ms	8738ms
#define _WDT_OVERFLOW_WDTACKI_2_15                (0x60U)		// 2^15/240k*128 = 2^15/4.2 us = 7.8ms	17.48s
#define _WDT_OVERFLOW_WDTACKI_2_16                (0x70U)		// 2^16/240k*128 = 2^16/4.2 us = 15.6ms	35s
/* Enables/disables the 75% interrupt request WDTAnTIT (WDTAnWIE) */
#define _WDT_INTERRUPT_DISABLED                   (0x00U) /* WDTAnTIT disabled */
#define _WDT_INTERRUPT_ENABLED                    (0x08U) /* WDTAnTIT enabled */
/* Specifies the error mode (WDTAnERM) */
#define _WDT_NMI_REQUEST_MODE                     (0x00U) /* NMI request mode */
#define _WDT_RESET_MODE                           (0x04U) /* Reset mode */
/* Select the period over which the window is open (WDTAnWS1,WDTAnWS0) */
#define _WDT_PERIOD_25                            (0x00U) /* Window-open period 25%  */
#define _WDT_PERIOD_50                            (0x01U) /* Window-open period 50% */
#define _WDT_PERIOD_75                            (0x02U) /* Window-open period 75% */
#define _WDT_PERIOD_100                           (0x03U) /* Window-open period 100% */

#define Clear_WDT1 R_WDT1_Restart();
#define Clear_WDT0 R_WDT0_Restart();
void R_WDT0_HardReset(void);
#define HardReset_WDT0 R_WDT0_HardReset();
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_WDT0_Create(void);
void R_WDT0_Restart(void);
void R_WDT1_Create(void);
void R_WDT1_Restart(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
