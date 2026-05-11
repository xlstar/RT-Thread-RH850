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
* File Name    : r_cg_intc.c
* Version      :
* Device(s)    : R7F701587(LQFP176pin)
* Tool-Chain   : CCRH
* Description  : This file implements device driver for INTC module.
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
#include "r_cg_intc.h"
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
* Function Name: R_INTC_Create
* Description  : This function initializes INTP module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC_Create(void)
{
    /* Disable INTP0 operation and clear request */
    INTC2.ICP0.BIT.MKP0 = _INT_PROCESSING_DISABLED;
    INTC2.ICP0.BIT.RFP0 = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTP1 operation and clear request */
    INTC2.ICP1.BIT.MKP1 = _INT_PROCESSING_DISABLED;
    INTC2.ICP1.BIT.RFP1 = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTP2 operation and clear request */
    INTC2.ICP2.BIT.MKP2 = _INT_PROCESSING_DISABLED;
    INTC2.ICP2.BIT.RFP2 = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTP3 operation and clear request */
    INTC2.ICP3.BIT.MKP3 = _INT_PROCESSING_DISABLED;
    INTC2.ICP3.BIT.RFP3 = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTP5 operation and clear request */
    INTC2.ICP5.BIT.MKP5 = _INT_PROCESSING_DISABLED;
    INTC2.ICP5.BIT.RFP5 = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTP6 operation and clear request */
    INTC2.ICP6.BIT.MKP6 = _INT_PROCESSING_DISABLED;
    INTC2.ICP6.BIT.RFP6 = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTP10 operation and clear request */
    INTC2.ICP10.BIT.MKP10 = _INT_PROCESSING_DISABLED;
    INTC2.ICP10.BIT.RFP10 = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTP11 operation and clear request */
    INTC2.ICP11.BIT.MKP11 = _INT_PROCESSING_DISABLED;
    INTC2.ICP11.BIT.RFP11 = _INT_REQUEST_NOT_OCCUR;
    /* Set INTP0 setting DCR1B */
    INTC2.ICP0.BIT.TBP0 = _INT_TABLE_VECTOR;
    INTC2.ICP0.UINT16 &= _INT_PRIORITY_HIGHEST;
    FCLA0.CTL0_INTPL = _INTC_EDGE_FALLING;
    /* Set INTP1 setting INTB */
    INTC2.ICP1.BIT.TBP1 = _INT_TABLE_VECTOR;
    INTC2.ICP1.UINT16 &= _INT_PRIORITY_LOWEST;
    FCLA0.CTL1_INTPL = _INTC_EDGE_FALLING;
    /* Set INTP2 setting RFC_2 */
    INTC2.ICP2.BIT.TBP2 = _INT_TABLE_VECTOR;
    INTC2.ICP2.UINT16 &= _INT_PRIORITY_LOWEST;
    FCLA0.CTL2_INTPL = _INTC_EDGE_FALLING;
    /* Set INTP3 setting DCR1B_2 */
    INTC2.ICP3.BIT.TBP3 = _INT_TABLE_VECTOR;
    INTC2.ICP3.UINT16 &= _INT_PRIORITY_HIGHEST;
    FCLA0.CTL3_INTPL = _INTC_EDGE_FALLING;
    /* Set INTP5 setting DCR2B_2 */
    INTC2.ICP5.BIT.TBP5 = _INT_TABLE_VECTOR;
    INTC2.ICP5.UINT16 &= _INT_PRIORITY_HIGHEST;
    FCLA0.CTL5_INTPL = _INTC_EDGE_FALLING;
    /* Set INTP6 setting INTB_2 */
    INTC2.ICP6.BIT.TBP6 = _INT_TABLE_VECTOR;
    INTC2.ICP6.UINT16 &= _INT_PRIORITY_LEVEL11;
    FCLA0.CTL6_INTPL = _INTC_EDGE_FALLING;
    /* Set INTP10 setting DCR2B */
    INTC2.ICP10.BIT.TBP10 = _INT_TABLE_VECTOR;
    INTC2.ICP10.UINT16 &= _INT_PRIORITY_HIGHEST;
    FCLA0.CTL2_INTPH = _INTC_EDGE_FALLING;
    /* Set INTP11 setting RFC */
    INTC2.ICP11.BIT.TBP11 = _INT_TABLE_VECTOR;
    INTC2.ICP11.UINT16 &= _INT_PRIORITY_LEVEL14;
    FCLA0.CTL3_INTPH = _INTC_EDGE_FALLING;
    /* Synchronization processing */
    g_cg_sync_read = FCLA0.CTL0_INTPL;
    __syncp();
    /* Set INTP0 pin DCR1B */
    PORT.PIBC0 &= _PORT_CLEAR_BIT1;
    PORT.PBDC0 &= _PORT_CLEAR_BIT1;
    PORT.PM0 |= _PORT_SET_BIT1;
    PORT.PMC0 &= _PORT_CLEAR_BIT1;
    PORT.PFC0 &= _PORT_CLEAR_BIT1;
    PORT.PFCE0 |= _PORT_SET_BIT1;
    PORT.PFCAE0 &= _PORT_CLEAR_BIT1;
    PORT.PMC0 |= _PORT_SET_BIT1;
    /* Set INTP1 pin INTB */
    PORT.PIBC0 &= _PORT_CLEAR_BIT2;
    PORT.PBDC0 &= _PORT_CLEAR_BIT2;
    PORT.PM0 |= _PORT_SET_BIT2;
    PORT.PMC0 &= _PORT_CLEAR_BIT2;
    PORT.PIPC0 &= _PORT_CLEAR_BIT2;
    PORT.PFC0 &= _PORT_CLEAR_BIT2;
    PORT.PFCE0 &= _PORT_CLEAR_BIT2;
    PORT.PFCAE0 |= _PORT_SET_BIT2;
    PORT.PMC0 |= _PORT_SET_BIT2;
    /* Set INTP2 pin RFC_2 */
    PORT.PIBC0 &= _PORT_CLEAR_BIT6;
    PORT.PBDC0 &= _PORT_CLEAR_BIT6;
    PORT.PM0 |= _PORT_SET_BIT6;
    PORT.PMC0 &= _PORT_CLEAR_BIT6;
    PORT.PIPC0 &= _PORT_CLEAR_BIT6;
    PORT.PFC0 &= _PORT_CLEAR_BIT6;
    PORT.PFCE0 &= _PORT_CLEAR_BIT6;
    PORT.PFCAE0 &= _PORT_CLEAR_BIT6;
    PORT.PMC0 |= _PORT_SET_BIT6;
    /* Set INTP3 pin DCR1B_2 */
    JTAG.JPIBC0 &= _JPORT_CLEAR_BIT3;
    JTAG.JPBDC0 &= _JPORT_CLEAR_BIT3;
    JTAG.JPM0 |= _JPORT_SET_BIT3;
    JTAG.JPMC0 &= _JPORT_CLEAR_BIT3;
    JTAG.JPFC0 &= _JPORT_CLEAR_BIT3;
    JTAG.JPMC0 |= _JPORT_SET_BIT3;
    /* Set INTP5 pin DCR2B_2 */
    PORT.PIBC0 &= _PORT_CLEAR_BIT13;
    PORT.PBDC0 &= _PORT_CLEAR_BIT13;
    PORT.PM0 |= _PORT_SET_BIT13;
    PORT.PMC0 &= _PORT_CLEAR_BIT13;
    PORT.PIPC0 &= _PORT_CLEAR_BIT13;
    PORT.PFC0 &= _PORT_CLEAR_BIT13;
    PORT.PFCE0 &= _PORT_CLEAR_BIT13;
    PORT.PFCAE0 |= _PORT_SET_BIT13;
    PORT.PMC0 |= _PORT_SET_BIT13;
    /* Set INTP6 pin INTB_2 */
    PORT.PIBC8 &= _PORT_CLEAR_BIT2;
    PORT.PBDC8 &= _PORT_CLEAR_BIT2;
    PORT.PM8 |= _PORT_SET_BIT2;
    PORT.PMC8 &= _PORT_CLEAR_BIT2;
    PORT.PFC8 &= _PORT_CLEAR_BIT2;
    PORT.PFCE8 |= _PORT_SET_BIT2;
    PORT.PMC8 |= _PORT_SET_BIT2;
    /* Set INTP10 pin DCR2B */
    PORT.PIBC0 &= _PORT_CLEAR_BIT3;
    PORT.PBDC0 &= _PORT_CLEAR_BIT3;
    PORT.PM0 |= _PORT_SET_BIT3;
    PORT.PMC0 &= _PORT_CLEAR_BIT3;
    PORT.PIPC0 &= _PORT_CLEAR_BIT3;
    PORT.PFC0 &= _PORT_CLEAR_BIT3;
    PORT.PFCE0 &= _PORT_CLEAR_BIT3;
    PORT.PFCAE0 |= _PORT_SET_BIT3;
    PORT.PMC0 |= _PORT_SET_BIT3;
    /* Set INTP11 pin RFC */
    PORT.PIBC0 &= _PORT_CLEAR_BIT4;
    PORT.PBDC0 &= _PORT_CLEAR_BIT4;
    PORT.PM0 |= _PORT_SET_BIT4;
    PORT.PMC0 &= _PORT_CLEAR_BIT4;
    PORT.PFC0 |= _PORT_SET_BIT4;
    PORT.PFCE0 &= _PORT_CLEAR_BIT4;
    PORT.PFCAE0 &= _PORT_CLEAR_BIT4;
    PORT.PMC0 |= _PORT_SET_BIT4;
}
/***********************************************************************************************************************
* Function Name: R_INTP0_Start
* Description  : This function clears INTP0 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTP0_Start(void)
{
    /* Clear INTP0 request and enable operation */
    INTC2.ICP0.BIT.RFP0 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICP0.BIT.MKP0 = _INT_PROCESSING_ENABLED;
}
/***********************************************************************************************************************
* Function Name: R_INTP0_Stop
* Description  : This function disables INTP0 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTP0_Stop(void)
{
    /* Disable INTP0 operation and clear request */
    INTC2.ICP0.BIT.MKP0 = _INT_PROCESSING_DISABLED;
    INTC2.ICP0.BIT.RFP0 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = INTC2.ICP0.UINT16;
    __syncp();
}
/***********************************************************************************************************************
* Function Name: R_INTP1_Start
* Description  : This function clears INTP1 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTP1_Start(void)
{
    /* Clear INTP1 request and enable operation */
    INTC2.ICP1.BIT.RFP1 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICP1.BIT.MKP1 = _INT_PROCESSING_ENABLED;
}
/***********************************************************************************************************************
* Function Name: R_INTP1_Stop
* Description  : This function disables INTP1 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTP1_Stop(void)
{
    /* Disable INTP1 operation and clear request */
    INTC2.ICP1.BIT.MKP1 = _INT_PROCESSING_DISABLED;
    INTC2.ICP1.BIT.RFP1 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = INTC2.ICP1.UINT16;
    __syncp();
}
/***********************************************************************************************************************
* Function Name: R_INTP2_Start
* Description  : This function clears INTP2 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTP2_Start(void)
{
    /* Clear INTP2 request and enable operation */
    INTC2.ICP2.BIT.RFP2 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICP2.BIT.MKP2 = _INT_PROCESSING_ENABLED;
}
/***********************************************************************************************************************
* Function Name: R_INTP2_Stop
* Description  : This function disables INTP2 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTP2_Stop(void)
{
    /* Disable INTP2 operation and clear request */
    INTC2.ICP2.BIT.MKP2 = _INT_PROCESSING_DISABLED;
    INTC2.ICP2.BIT.RFP2 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = INTC2.ICP2.UINT16;
    __syncp();
}
/***********************************************************************************************************************
* Function Name: R_INTP3_Start
* Description  : This function clears INTP3 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTP3_Start(void)
{
    /* Clear INTP3 request and enable operation */
    INTC2.ICP3.BIT.RFP3 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICP3.BIT.MKP3 = _INT_PROCESSING_ENABLED;
}
/***********************************************************************************************************************
* Function Name: R_INTP3_Stop
* Description  : This function disables INTP3 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTP3_Stop(void)
{
    /* Disable INTP3 operation and clear request */
    INTC2.ICP3.BIT.MKP3 = _INT_PROCESSING_DISABLED;
    INTC2.ICP3.BIT.RFP3 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = INTC2.ICP3.UINT16;
    __syncp();
}
/***********************************************************************************************************************
* Function Name: R_INTP4_Start
* Description  : This function clears INTP4 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTP4_Start(void)
{
}
/***********************************************************************************************************************
* Function Name: R_INTP4_Stop
* Description  : This function disables INTP4 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTP4_Stop(void)
{
}
/***********************************************************************************************************************
* Function Name: R_INTP5_Start
* Description  : This function clears INTP5 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTP5_Start(void)
{
    /* Clear INTP5 request and enable operation */
    INTC2.ICP5.BIT.RFP5 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICP5.BIT.MKP5 = _INT_PROCESSING_ENABLED;
}
/***********************************************************************************************************************
* Function Name: R_INTP5_Stop
* Description  : This function disables INTP5 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTP5_Stop(void)
{
    /* Disable INTP5 operation and clear request */
    INTC2.ICP5.BIT.MKP5 = _INT_PROCESSING_DISABLED;
    INTC2.ICP5.BIT.RFP5 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = INTC2.ICP5.UINT16;
    __syncp();
}
/***********************************************************************************************************************
* Function Name: R_INTP6_Start
* Description  : This function clears INTP6 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTP6_Start(void)
{
    /* Clear INTP6 request and enable operation */
    INTC2.ICP6.BIT.RFP6 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICP6.BIT.MKP6 = _INT_PROCESSING_ENABLED;
}
/***********************************************************************************************************************
* Function Name: R_INTP6_Stop
* Description  : This function disables INTP6 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTP6_Stop(void)
{
    /* Disable INTP6 operation and clear request */
    INTC2.ICP6.BIT.MKP6 = _INT_PROCESSING_DISABLED;
    INTC2.ICP6.BIT.RFP6 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = INTC2.ICP6.UINT16;
    __syncp();
}

/***********************************************************************************************************************
* Function Name: R_INTP10_Start
* Description  : This function clears INTP10 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTP10_Start(void)
{
    /* Clear INTP10 request and enable operation */
    INTC2.ICP10.BIT.RFP10 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICP10.BIT.MKP10 = _INT_PROCESSING_ENABLED;
}
/***********************************************************************************************************************
* Function Name: R_INTP10_Stop
* Description  : This function disables INTP10 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTP10_Stop(void)
{
    /* Disable INTP10 operation and clear request */
    INTC2.ICP10.BIT.MKP10 = _INT_PROCESSING_DISABLED;
    INTC2.ICP10.BIT.RFP10 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = INTC2.ICP10.UINT16;
    __syncp();
}
/***********************************************************************************************************************
* Function Name: R_INTP11_Start
* Description  : This function clears INTP11 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTP11_Start(void)
{
    /* Clear INTP11 request and enable operation */
    INTC2.ICP11.BIT.RFP11 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICP11.BIT.MKP11 = _INT_PROCESSING_ENABLED;
}
/***********************************************************************************************************************
* Function Name: R_INTP11_Stop
* Description  : This function disables INTP11 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTP11_Stop(void)
{
    /* Disable INTP11 operation and clear request */
    INTC2.ICP11.BIT.MKP11 = _INT_PROCESSING_DISABLED;
    INTC2.ICP11.BIT.RFP11 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = INTC2.ICP11.UINT16;
    __syncp();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
