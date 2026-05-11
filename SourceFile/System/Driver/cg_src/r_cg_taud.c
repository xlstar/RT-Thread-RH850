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
* File Name    : r_cg_taud.c
* Version      :
* Device(s)    : R7F701587(LQFP176pin)
* Tool-Chain   : CCRH
* Description  : This file implements device driver for TAUD module.
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
#include "r_cg_taud.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t  g_cg_sync_read;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_TAUD0_Create
* Description  : This function initializes the TAUD0 Bus Interface.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUD0_Create(void)
{
    /* Disable channel0 counter operation */
    TAUD0.TT = _TAUD_CHANNEL15_COUNTER_STOP | _TAUD_CHANNEL14_COUNTER_STOP | _TAUD_CHANNEL13_COUNTER_STOP |
               _TAUD_CHANNEL12_COUNTER_STOP | _TAUD_CHANNEL11_COUNTER_STOP | _TAUD_CHANNEL10_COUNTER_STOP |
               _TAUD_CHANNEL9_COUNTER_STOP | _TAUD_CHANNEL8_COUNTER_STOP | _TAUD_CHANNEL7_COUNTER_STOP |
               _TAUD_CHANNEL6_COUNTER_STOP | _TAUD_CHANNEL5_COUNTER_STOP | _TAUD_CHANNEL4_COUNTER_STOP |
               _TAUD_CHANNEL3_COUNTER_STOP | _TAUD_CHANNEL2_COUNTER_STOP | _TAUD_CHANNEL1_COUNTER_STOP |
               _TAUD_CHANNEL0_COUNTER_STOP;
    /* Disable INTTAUD0I6 operation and clear request */
    INTC1.ICTAUD0I6.BIT.MKTAUD0I6 = _INT_PROCESSING_DISABLED;
    INTC1.ICTAUD0I6.BIT.RFTAUD0I6 = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTTAUD0I7 operation and clear request */
    INTC2.ICTAUD0I7.BIT.MKTAUD0I7 = _INT_PROCESSING_DISABLED;
    INTC2.ICTAUD0I7.BIT.RFTAUD0I7 = _INT_REQUEST_NOT_OCCUR;
    /* Set INTTAUD0I7 setting */
    INTC2.ICTAUD0I7.BIT.TBTAUD0I7 = _INT_TABLE_VECTOR;
    INTC2.ICTAUD0I7.UINT16 &= _INT_PRIORITY_LOWEST - 2U;
    TAUD0.TPS = _TAUD_CK3_PRE_PCLK_5 | _TAUD_CK2_PRE_PCLK_6 | _TAUD_CK1_PRE_PCLK_5 | _TAUD_CK0_PRE_PCLK_12;
    TAUD0.BRS = _TAUD0_CK3_PRE_CLOCK_DIVISION;
    /* Set channel 6 setting */
    TAUD0.CMOR6 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_MASTER_CHANNEL | _TAUD_START_TRIGGER_SOFTWARE |
                  _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_INTERVAL_TIMER_MODE | _TAUD_START_INT_GENERATED;
    TAUD0.CMUR6 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD0.CDR6 = _TAUD0_CHANNEL6_COMPARE_VALUE;
    /* Set channel 7 setting */
    TAUD0.CMOR7 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_SLAVE_CHANNEL |
                  _TAUD_START_TRIGGER_MASTER_INT | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_ONE_COUNT_MODE |
                  _TAUD_START_TRIGGER_ENABLE;
    TAUD0.CMUR7 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD0.CDR7 = _TAUD0_CHANNEL7_COMPARE_VALUE;
    /* Set output mode setting */
    TAUD0.TOE = _TAUD_CHANNEL07_ENABLES_OUTPUT_FUNCTION | _TAUD_CHANNEL6_DISABLES_OUTPUT_FUNCTION;
    TAUD0.TOM = _TAUD_CHANNEL7_SYNCHRONOUS_OPERATION;
    TAUD0.TOC = _TAUD_CHANNEL7_OPERATION_MODE1;
    TAUD0.TOL = _TAUD_CHANNEL7_POSITIVE_LOGIC;
    TAUD0.TDE = _TAUD_CHANNEL7_DISABLES_DEAD_TIME_OPERATION;
    TAUD0.TDM = _TAUD_CHANNEL7_DETECTING_DUTY_CYCLE;
    TAUD0.TDL = _TAUD_CHANNEL7_NORMAL_PHASE;
    TAUD0.TRE = _TAUD_CHANNEL7_REAL_TIME_OUTPUT_DISABLES;
    /* Synchronization processing */
    g_cg_sync_read = TAUD0.TPS;
    __syncp();

    SL_TAUD0.SELB_TAUD0I = _TAUD_NO_CHANGE_INPUT_SIGNAL;
    /* Set TAUD0O7 pin */
    PORT.PIBC10 &= _PORT_CLEAR_BIT3;
    PORT.PBDC10 &= _PORT_CLEAR_BIT3;
    PORT.PM10 |= _PORT_SET_BIT3;
    PORT.PMC10 &= _PORT_CLEAR_BIT3;
    PORT.PIPC10 &= _PORT_CLEAR_BIT3;
    PORT.PFC10 &= _PORT_CLEAR_BIT3;
    PORT.PFCE10 &= _PORT_CLEAR_BIT3;
    PORT.PFCAE10 &= _PORT_CLEAR_BIT3;
    PORT.PMC10 |= _PORT_SET_BIT3;
    PORT.PM10 &= _PORT_CLEAR_BIT3;

    /* Disable INTTAUD0I0 operation and clear request */
    INTC1.ICTAUD0I0.BIT.MKTAUD0I0 = _INT_PROCESSING_DISABLED;
    INTC1.ICTAUD0I0.BIT.RFTAUD0I0 = _INT_REQUEST_NOT_OCCUR;
    /* Set INTTAUD0I0 setting */
    INTC1.ICTAUD0I0.BIT.TBTAUD0I0 = _INT_TABLE_VECTOR;
    INTC1.ICTAUD0I0.UINT16 &= _INT_PRIORITY_LOWEST - 2U;
    TAUD0.TPS = _TAUD_CK3_PRE_PCLK_15 | _TAUD_CK2_PRE_PCLK_15 | _TAUD_CK1_PRE_PCLK_15 | _TAUD_CK0_PRE_PCLK_3;
    TAUD0.BRS = _TAUD0_CK3_PRE_CLOCK_DIVISION;
    /* Set channel 0 setting */
    TAUD0.CMOR0 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_INDEPENDENT_CHANNEL |
                  _TAUD_START_TRIGGER_SOFTWARE | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_INTERVAL_TIMER_MODE |
                  _TAUD_START_INT_GENERATED;
    TAUD0.CMUR0 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD0.CDR0 = _TAUD0_CHANNEL0_COMPARE_VALUE;
    /* Set output mode setting */
    TAUD0.TOE = _TAUD_CHANNEL0_ENABLES_OUTPUT_FUNCTION;
    TAUD0.TOM = _TAUD_CHANNEL0_INDEPENDENT_OPERATION;
    TAUD0.TOC = _TAUD_CHANNEL0_OPERATION_MODE1;
    TAUD0.TOL = _TAUD_CHANNEL0_POSITIVE_LOGIC;
    TAUD0.TDE = _TAUD_CHANNEL0_DISABLES_DEAD_TIME_OPERATION;
    TAUD0.TDM = _TAUD_CHANNEL0_DETECTING_DUTY_CYCLE;
    TAUD0.TDL = _TAUD_CHANNEL0_NORMAL_PHASE;
    TAUD0.TRE = _TAUD_CHANNEL0_REAL_TIME_OUTPUT_DISABLES;
    /* Synchronization processing */
    g_cg_sync_read = TAUD0.TPS;
    __syncp();

    SL_TAUD0.SELB_TAUD0I = _TAUD_NO_CHANGE_INPUT_SIGNAL;
#if 0
    /* Set TAUD0O0 pin */
    PORT.PIBC9 &= _PORT_CLEAR_BIT0;
    PORT.PBDC9 &= _PORT_CLEAR_BIT0;
    PORT.PM9 |= _PORT_SET_BIT0;
    PORT.PMC9 &= _PORT_CLEAR_BIT0;
    PORT.PFC9 |= _PORT_SET_BIT0;
    PORT.PFCE9 &= _PORT_CLEAR_BIT0;
    PORT.PMC9 |= _PORT_SET_BIT0;
    PORT.PM9 &= _PORT_CLEAR_BIT0;
#endif
}
/***********************************************************************************************************************
* Function Name: R_TAUD0_Channel6_Start
* Description  : This function clears TAUD06 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUD0_Channel6_Start(void)
{
    /* Clear INTTAUD0I7 request and enable operation */
    INTC2.ICTAUD0I7.BIT.RFTAUD0I7 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICTAUD0I7.BIT.MKTAUD0I7 = _INT_PROCESSING_ENABLED;
    /* Enable channel6 counter operation */
    TAUD0.TS |= _TAUD_CHANNEL6_COUNTER_START | _TAUD_CHANNEL7_COUNTER_START;
}
/***********************************************************************************************************************
* Function Name: R_TAUD0_Channel6_Stop
* Description  : This function disables TAUD06 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUD0_Channel6_Stop(void)
{
    /* Disable channel6 counter operation */
    TAUD0.TT |= _TAUD_CHANNEL6_COUNTER_STOP | _TAUD_CHANNEL7_COUNTER_STOP;
    /* Disable INTTAUD0I7 operation and clear request */
    INTC2.ICTAUD0I7.BIT.MKTAUD0I7 = _INT_PROCESSING_DISABLED;
    INTC2.ICTAUD0I7.BIT.RFTAUD0I7 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = TAUD0.TT;
    __syncp();
}


/***********************************************************************************************************************
* Function Name: R_TAUD0_Channel0_Start
* Description  : This function clears TAUD00 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUD0_Channel0_Start(void)
{
    /* Clear INTTAUD0I0 request and enable operation */
    INTC1.ICTAUD0I0.BIT.RFTAUD0I0 = _INT_REQUEST_NOT_OCCUR;
    INTC1.ICTAUD0I0.BIT.MKTAUD0I0 = _INT_PROCESSING_ENABLED;
    /* Enable channel0 counter operation */
    TAUD0.TS |= _TAUD_CHANNEL0_COUNTER_START;
}
/***********************************************************************************************************************
* Function Name: R_TAUD0_Channel0_Stop
* Description  : This function disables TAUD00 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUD0_Channel0_Stop(void)
{
    /* Disable channel0 counter operation */
    TAUD0.TT |= _TAUD_CHANNEL0_COUNTER_STOP;
    /* Disable INTTAUD0I0 operation and clear request */
    INTC1.ICTAUD0I0.BIT.MKTAUD0I0 = _INT_PROCESSING_DISABLED;
    INTC1.ICTAUD0I0.BIT.RFTAUD0I0 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = TAUD0.TT;
    __syncp();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
