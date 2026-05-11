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
* File Name    : r_cg_taub.c
* Version      :
* Device(s)    : R7F701587(LQFP176pin)
* Tool-Chain   : CCRH
* Description  : This file implements device driver for TAUB module.
* Creation Date: 2018/6/12
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_taub.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t g_cg_sync_read;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_TAUB0_Create
* Description  : This function initializes the TAUB0 Bus Interface.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUB0_Init(void)
{
    R_TAUB0_Create();
    R_TAUB0_Channel7_Start();
}

void R_TAUB0_Create(void)
{
    /* Disable channel0 counter operation */
    TAUB0.TT = _TAUB_CHANNEL15_COUNTER_STOP | _TAUB_CHANNEL14_COUNTER_STOP | _TAUB_CHANNEL13_COUNTER_STOP |
               _TAUB_CHANNEL12_COUNTER_STOP | _TAUB_CHANNEL11_COUNTER_STOP | _TAUB_CHANNEL10_COUNTER_STOP |
               _TAUB_CHANNEL9_COUNTER_STOP | _TAUB_CHANNEL8_COUNTER_STOP | _TAUB_CHANNEL7_COUNTER_STOP |
               _TAUB_CHANNEL6_COUNTER_STOP | _TAUB_CHANNEL5_COUNTER_STOP | _TAUB_CHANNEL4_COUNTER_STOP |
               _TAUB_CHANNEL3_COUNTER_STOP | _TAUB_CHANNEL2_COUNTER_STOP | _TAUB_CHANNEL1_COUNTER_STOP |
               _TAUB_CHANNEL0_COUNTER_STOP;
    /* Disable INTTAUB0I7 operation and clear request */
    INTC2.ICTAUB0I7.BIT.MKTAUB0I7 = _INT_PROCESSING_DISABLED;
    INTC2.ICTAUB0I7.BIT.RFTAUB0I7 = _INT_REQUEST_NOT_OCCUR;
    /* Set INTTAUB0I7 setting */
    INTC2.ICTAUB0I7.BIT.TBTAUB0I7 = _INT_TABLE_VECTOR;
    INTC2.ICTAUB0I7.UINT16 &= _INT_PRIORITY_LOWEST - 2U;
    TAUB0.TPS = _TAUB_CK3_PRE_PCLK_15 | _TAUB_CK2_PRE_PCLK_15 | _TAUB_CK1_PRE_PCLK_15 | _TAUB_CK0_PRE_PCLK_0;
    /* Set channel 7 setting */
    TAUB0.CMOR7 = _TAUB_SELECTION_CK0 | _TAUB_OPERATION_CLOCK | _TAUB_INDEPENDENT_CHANNEL | _TAUB_SOFTWARE_TRIGGER |
                  _TAUB_OVERFLOW_AUTO_CLEAR | _TAUB_INTERVAL_TIMER_MODE | _TAUB_START_INT_NOT_GENERATED;
    TAUB0.CMUR7 = _TAUB_INPUT_EDGE_UNUSED;
    TAUB0.CDR7 = _TAUB0_CHANNEL7_COMPARE_VALUE;
    /* Set output mode setting */
    TAUB0.TOE = _TAUB_CHANNEL7_ENABLES_OUTPUT_MODE;
    TAUB0.TOM = _TAUB_CHANNEL7_INDEPENDENT_OUTPUT_MODE;
    TAUB0.TOC = _TAUB_CHANNEL7_OPERATION_MODE1;
    TAUB0.TOL = _TAUB_CHANNEL7_POSITIVE_LOGIC;
    TAUB0.TDE = _TAUB_CHANNEL7_DISABLE_DEAD_TIME_OPERATE;
    TAUB0.TDL = _TAUB_CHANNEL7_POSITIVE_PHASE_PERIOD;
    /* Synchronization processing */
    g_cg_sync_read = TAUB0.TPS;
    __syncp();

    /* Set TAUB0O7 pin */
    //521.42 CLKREF PIN control P10_14
    PORT.PIBC10 &= _PORT_CLEAR_BIT14;
    PORT.PBDC10 &= _PORT_CLEAR_BIT14;
    PORT.PM10 |= _PORT_SET_BIT14;
    PORT.PMC10 &= _PORT_CLEAR_BIT14;
    PORT.PFC10 |= _PORT_SET_BIT14;
    PORT.PFCE10 |= _PORT_SET_BIT14;
    PORT.PMC10 |= _PORT_SET_BIT14;
    PORT.PM10 &= _PORT_CLEAR_BIT14;
}
/***********************************************************************************************************************
* Function Name: R_TAUB0_Channel7_Start
* Description  : This function clears TAUB07 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUB0_Channel7_Start(void)
{
    /* Clear INTTAUB0I7 request and enable operation */
    INTC2.ICTAUB0I7.BIT.RFTAUB0I7 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICTAUB0I7.BIT.MKTAUB0I7 = _INT_PROCESSING_DISABLED;
    /* Enable channel7 counter operation */
    TAUB0.TS |= _TAUB_CHANNEL7_COUNTER_START;
}
/***********************************************************************************************************************
* Function Name: R_TAUB0_Channel7_Stop
* Description  : This function disables TAUB07 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUB0_Channel7_Stop(void)
{
    /* Disable channel7 counter operation */
    TAUB0.TT |= _TAUB_CHANNEL7_COUNTER_STOP;
    /* Disable INTTAUB0I0 operation and clear request */
    INTC2.ICTAUB0I7.BIT.MKTAUB0I7 = _INT_PROCESSING_DISABLED;
    INTC2.ICTAUB0I7.BIT.RFTAUB0I7 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = TAUB0.TT;
    __syncp();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
