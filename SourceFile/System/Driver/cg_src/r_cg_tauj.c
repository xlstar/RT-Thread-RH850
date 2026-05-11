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
* File Name    : r_cg_tauj.c
* Version      :
* Device(s)    : R7F701587(LQFP176pin)
* Tool-Chain   : CCRH
* Description  : This file implements device driver for TAUJ module.
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
#include "r_cg_tauj.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t g_cg_sync_read;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
void R_TAUJ0_Init(void)
{
    // generate 330us timer for detect DCR1B/DCR2B/INTB
    R_TAUJ0_Create();
#ifdef SUPPORT_CPU_LOADING
    R_TAUJ0_Channel0_Start();
#endif
    //	R_TAUJ0_Channel3_Start();
}

void R_TAUJ1_Init(void)
{
    // generate 1ms timer
    R_TAUJ1_Create();
    //#ifndef SUPPORT_FREERTOS
    R_TAUJ1_Channel0_Start();		// 1ms timer
    //#endif
    //	R_TAUJ1_Channel1_Start();
    //	R_TAUJ1_Channel2_Start();
}
/***********************************************************************************************************************
* Function Name: R_TAUJ0_Create
* Description  : This function initializes the TAUJ0 Bus Interface.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUJ0_Create(void)
{
    /* Disable channel0 counter operation */
    TAUJ0.TT = _TAUJ_CHANNEL3_COUNTER_STOP | _TAUJ_CHANNEL2_COUNTER_STOP | _TAUJ_CHANNEL1_COUNTER_STOP |
               _TAUJ_CHANNEL0_COUNTER_STOP;
    /* Disable INTTAUJ0I0 operation and clear request */
    INTC2.ICTAUJ0I0.BIT.MKTAUJ0I0 = _INT_PROCESSING_DISABLED;
    INTC2.ICTAUJ0I0.BIT.RFTAUJ0I0 = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTTAUJ0I1 operation and clear request */
    //INTC2.ICTAUJ0I1.BIT.MKTAUJ0I1 = _INT_PROCESSING_DISABLED;
    //INTC2.ICTAUJ0I1.BIT.RFTAUJ0I1 = _INT_REQUEST_NOT_OCCUR;
    /* Set INTTAUJ0I0 setting */
    //INTC2.ICTAUJ0I0.BIT.TBTAUJ0I0 = _INT_TABLE_VECTOR;
    //INTC2.ICTAUJ0I0.UINT16 &= _INT_PRIORITY_LOWEST - 2U;
    /* Set INTTAUJ0I1 setting */
    INTC2.ICTAUJ0I1.BIT.TBTAUJ0I1 = _INT_TABLE_VECTOR;
    INTC2.ICTAUJ0I1.UINT16 &= _INT_PRIORITY_LEVEL10;		//because the time between two AUTOBRC is strict liao_wq

    TAUJ0.TPS &= _TAUJ_CK0_PRS_CLEAR;
    TAUJ0.TPS |= _TAUJ_CK0_PRE_PCLK_3;
    /* Set channel 0 setting */
    TAUJ0.CMOR0 = _TAUJ_SELECTION_CK0 | _TAUJ_COUNT_CLOCK_PCLK | _TAUJ_INDEPENDENT_CHANNEL |
                  _TAUJ_START_TRIGGER_VALID_EDGE | _TAUJ_OVERFLOW_AUTO_CLEAR | _TAUJ_INTERVAL_TIMER_MODE |
                  _TAUJ_START_INT_NOT_GENERATED;
    /* Set compare match register */
    TAUJ0.CMUR0 = _TAUJ_INPUT_EDGE_FALLING;
    TAUJ0.CDR0 = _TAUJ0_CHANNEL0_COMPARE_VALUE;

    /* Set channel 1 setting */
    TAUJ0.CMOR1 = _TAUJ_SELECTION_CK0 | _TAUJ_COUNT_CLOCK_PCLK | _TAUJ_INDEPENDENT_CHANNEL |
                  _TAUJ_START_TRIGGER_SOFTWARE | _TAUJ_OVERFLOW_AUTO_CLEAR | _TAUJ_INTERVAL_TIMER_MODE |
                  _TAUJ_START_INT_NOT_GENERATED;
    TAUJ0.CMUR1 = _TAUJ_INPUT_EDGE_UNUSED;
    TAUJ0.CDR1 = _TAUJ0_CHANNEL1_COMPARE_VALUE;
    /* Set output mode setting */
    TAUJ0.TOE = _TAUJ_CHANNEL1_ENABLES_OUTPUT_FUNCTION | _TAUJ_CHANNEL0_ENABLES_OUTPUT_FUNCTION;
    TAUJ0.TOM = _TAUJ_CHANNEL1_INDEPENDENT_OPERATION | _TAUJ_CHANNEL0_INDEPENDENT_OPERATION;
    TAUJ0.TOC = _TAUJ_CHANNEL1_OPERATION_MODE1 | _TAUJ_CHANNEL0_OPERATION_MODE1;
    TAUJ0.TOL = _TAUJ_CHANNEL1_POSITIVE_LOGIC | _TAUJ_CHANNEL0_POSITIVE_LOGIC;
    /* Synchronization processing */
    g_cg_sync_read = TAUJ0.TPS;
    __syncp();
    SL_TAUJ0.SELB_TAUJ0I = _TAUJ_CHANNEL3_TAUJ0I3 | _TAUJ_CHANNEL2_TAUJ0I2;

}
/***********************************************************************************************************************
* Function Name: R_TAUJ0_Channel0_Start
* Description  : This function clears TAUJ00 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUJ0_Channel0_Start(void)
{
    /* Clear INTTAUJ0I3 request and enable operation */
    INTC2.ICTAUJ0I0.BIT.RFTAUJ0I0 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICTAUJ0I0.BIT.MKTAUJ0I0 = _INT_PROCESSING_DISABLED;
    /* Enable channel0 counter operation */
    TAUJ0.TS |= _TAUJ_CHANNEL0_COUNTER_START;
}
/***********************************************************************************************************************
* Function Name: R_TAUJ0_Channel0_Stop
* Description  : This function disables TAUJ00 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUJ0_Channel0_Stop(void)
{
    /* Disable channel0 counter operation */
    //    TAUJ0.TT |= _TAUJ_CHANNEL0_COUNTER_STOP | _TAUJ_CHANNEL3_COUNTER_STOP;
    TAUJ0.TT |= _TAUJ_CHANNEL0_COUNTER_STOP;
    /* Disable INTTAUJ0I3 operation and clear request */
    INTC2.ICTAUJ0I0.BIT.MKTAUJ0I0 = _INT_PROCESSING_DISABLED;
    INTC2.ICTAUJ0I0.BIT.RFTAUJ0I0 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = TAUJ0.TT;
    __syncp();
}

/***********************************************************************************************************************
* Function Name: R_TAUJ0_Channel0_Start
* Description  : This function clears TAUJ00 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUJ0_Channel1_Start(void)
{
    /* Clear INTTAUJ0I3 request and enable operation */
    INTC2.ICTAUJ0I1.BIT.RFTAUJ0I1 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICTAUJ0I1.BIT.MKTAUJ0I1 = _INT_PROCESSING_ENABLED;
    /* Enable channel0 counter operation */
    TAUJ0.TS |= _TAUJ_CHANNEL1_COUNTER_START;
}
/***********************************************************************************************************************
* Function Name: R_TAUJ0_Channel3_Stop
* Description  : This function disables TAUJ00 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUJ0_Channel1_Stop(void)
{
    /* Disable channel0 counter operation */
    TAUJ0.TT |= _TAUJ_CHANNEL1_COUNTER_STOP;
    /* Disable INTTAUJ0I3 operation and clear request */
    INTC2.ICTAUJ0I1.BIT.MKTAUJ0I1 = _INT_PROCESSING_DISABLED;
    INTC2.ICTAUJ0I1.BIT.RFTAUJ0I1 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = TAUJ0.TT;
    __syncp();
}
/***********************************************************************************************************************
* Function Name: R_TAUJ1_Create
* Description  : This function initializes the TAUJ1 Bus Interface.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUJ1_Create(void)
{
    /* Disable channel 0 counter operation */
    TAUJ1.TT |= _TAUJ_CHANNEL0_COUNTER_STOP;
    /* Disable INTTAUJ1I0 operation and clear request */
    INTC2.ICTAUJ1I0.BIT.MKTAUJ1I0 = _INT_PROCESSING_DISABLED;
    INTC2.ICTAUJ1I0.BIT.RFTAUJ1I0 = _INT_REQUEST_NOT_OCCUR;
    /* Set INTTAUJ1I0 setting */
    INTC2.ICTAUJ1I0.BIT.TBTAUJ1I0 = _INT_TABLE_VECTOR;
    INTC2.ICTAUJ1I0.UINT16 &= _INT_PRIORITY_LEVEL6;
    TAUJ1.TPS &= _TAUJ_CK0_PRS_CLEAR;
    TAUJ1.TPS |= _TAUJ_CK0_PRE_PCLK_0;
    /* Set channel 0 setting */
    TAUJ1.CMOR0 = _TAUJ_SELECTION_CK0 | _TAUJ_COUNT_CLOCK_PCLK | _TAUJ_INDEPENDENT_CHANNEL |
                  _TAUJ_START_TRIGGER_SOFTWARE | _TAUJ_OVERFLOW_AUTO_CLEAR | _TAUJ_INTERVAL_TIMER_MODE |
                  _TAUJ_START_INT_NOT_GENERATED;
    /* Set compare match register */
    TAUJ1.CMUR0 = _TAUJ_INPUT_EDGE_UNUSED;
    TAUJ1.CDR0 = _TAUJ10_COMPARE_VALUE;
    /* Set output mode setting */
    TAUJ1.TOE |= _TAUJ_CHANNEL0_ENABLES_OUTPUT_MODE;
    TAUJ1.TOM &= _TAUJ_CHANNEL0_INDEPENDENT_OPERATION;
    TAUJ1.TOC &= _TAUJ_CHANNEL0_OPERATION_MODE1;
    TAUJ1.TOL &= _TAUJ_CHANNEL0_POSITIVE_LOGIC;
    /* Synchronization processing */
    g_cg_sync_read = TAUJ1.TPS;
    __syncp();

    /* Set TAUJ1O0 pin */
    PORT.PIBC0 &= _PORT_CLEAR_BIT3;
    PORT.PBDC0 &= _PORT_CLEAR_BIT3;
    PORT.PM0 |= _PORT_SET_BIT3;
    PORT.PMC0 &= _PORT_CLEAR_BIT3;
    PORT.PIPC0 &= _PORT_CLEAR_BIT3;
    PORT.PFC0 |= _PORT_SET_BIT3;
    PORT.PFCE0 &= _PORT_CLEAR_BIT3;
    PORT.PFCAE0 |= _PORT_SET_BIT3;
    PORT.PMC0 |= _PORT_SET_BIT3;
    PORT.PM0 &= _PORT_CLEAR_BIT3;

    //R_Config_TAUJ1_0_Create_UserInit();
}
/***********************************************************************************************************************
* Function Name: R_TAUJ1_Channel0_Start
* Description  : This function clears TAUJ10 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUJ1_Channel0_Start(void)
{
    /* Clear INTTAUJ1I0 request and enable operation */
    INTC2.ICTAUJ1I0.BIT.RFTAUJ1I0 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICTAUJ1I0.BIT.MKTAUJ1I0 = _INT_PROCESSING_ENABLED;
    /* Enable channel0 counter operation */
    TAUJ1.TS |= _TAUJ_CHANNEL0_COUNTER_START;
}
/***********************************************************************************************************************
* Function Name: R_TAUJ1_Channel0_Stop
* Description  : This function disables TAUJ10 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUJ1_Channel0_Stop(void)
{
    /* Disable channel0 counter operation */
    TAUJ1.TT |= _TAUJ_CHANNEL0_COUNTER_STOP;
    /* Disable INTTAUJ1I0 operation and clear request */
    INTC2.ICTAUJ1I0.BIT.MKTAUJ1I0 = _INT_PROCESSING_DISABLED;
    INTC2.ICTAUJ1I0.BIT.RFTAUJ1I0 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = TAUJ1.TT;
    __syncp();
}
/***********************************************************************************************************************
* Function Name: R_TAUJ1_Channel1_Start
* Description  : This function clears TAUJ11 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUJ1_Channel1_Start(void)
{
    /* Clear INTTAUJ1I1 request and enable operation */
    INTC2.ICTAUJ1I1.BIT.RFTAUJ1I1 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICTAUJ1I1.BIT.MKTAUJ1I1 = _INT_PROCESSING_ENABLED;
    /* Enable channel1 counter operation */
    TAUJ1.TS |= _TAUJ_CHANNEL1_COUNTER_START;
}
/***********************************************************************************************************************
* Function Name: R_TAUJ1_Channel1_Stop
* Description  : This function disables TAUJ11 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUJ1_Channel1_Stop(void)
{
    /* Disable channel1 counter operation */
    TAUJ1.TT |= _TAUJ_CHANNEL1_COUNTER_STOP;
    /* Disable INTTAUJ1I1 operation and clear request */
    INTC2.ICTAUJ1I1.BIT.MKTAUJ1I1 = _INT_PROCESSING_DISABLED;
    INTC2.ICTAUJ1I1.BIT.RFTAUJ1I1 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = TAUJ1.TT;
    __syncp();
}
/***********************************************************************************************************************
* Function Name: R_TAUJ1_Channel2_Start
* Description  : This function clears TAUJ12 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUJ1_Channel2_Start(void)
{
    /* Clear INTTAUJ1I2 request and enable operation */
    INTC2.ICTAUJ1I2.BIT.RFTAUJ1I2 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICTAUJ1I2.BIT.MKTAUJ1I2 = _INT_PROCESSING_ENABLED;
    /* Enable channel2 counter operation */
    TAUJ1.TS |= _TAUJ_CHANNEL2_COUNTER_START;
}
/***********************************************************************************************************************
* Function Name: R_TAUJ1_Channel2_Stop
* Description  : This function disables TAUJ12 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUJ1_Channel2_Stop(void)
{
    /* Disable channel2 counter operation */
    TAUJ1.TT |= _TAUJ_CHANNEL2_COUNTER_STOP;
    /* Disable INTTAUJ1I2 operation and clear request */
    INTC2.ICTAUJ1I2.BIT.MKTAUJ1I2 = _INT_PROCESSING_DISABLED;
    INTC2.ICTAUJ1I2.BIT.RFTAUJ1I2 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = TAUJ1.TT;
    __syncp();
}
/***********************************************************************************************************************
* Function Name: R_TAUJ1_Channel3_Start
* Description  : This function clears TAUJ13 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUJ1_Channel3_Start(void)
{
    /* Clear INTTAUJ1I3 request and enable operation */
    INTC2.ICTAUJ1I3.BIT.RFTAUJ1I3 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICTAUJ1I3.BIT.MKTAUJ1I3 = _INT_PROCESSING_ENABLED;
    /* Enable channel3 counter operation */
    TAUJ1.TS |= _TAUJ_CHANNEL3_COUNTER_START;
}
/***********************************************************************************************************************
* Function Name: R_TAUJ1_Channel3_Stop
* Description  : This function disables TAUJ13 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUJ1_Channel3_Stop(void)
{
    /* Disable channel3 counter operation */
    TAUJ1.TT |= _TAUJ_CHANNEL3_COUNTER_STOP;
    /* Disable INTTAUJ1I3 operation and clear request */
    INTC2.ICTAUJ1I3.BIT.MKTAUJ1I3 = _INT_PROCESSING_DISABLED;
    INTC2.ICTAUJ1I3.BIT.RFTAUJ1I3 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = TAUJ1.TT;
    __syncp();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
