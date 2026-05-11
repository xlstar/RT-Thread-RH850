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
* File Name    : r_cg_intc_user.c
* Version      : Code Generator for RH850/F1K V1.01.02.02 [08 May 2018]
* Device(s)    : R7F701581(LQFP100pin)
* Tool-Chain   : CCRH
* Description  : This file implements device driver for INTC module.
* Creation Date: 2022/3/11
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
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
void INT_EnableDCR1BAndDCR2B_Interrupt(void)
{
    /* Clear INTP0 request and enable operation */
    INTC2.ICP0.BIT.RFP0 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICP0.BIT.MKP0 = _INT_PROCESSING_ENABLED;
    //	R_INTP0_Start();
    /* Clear INTP10 request and enable operation */
    INTC2.ICP10.BIT.RFP10 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICP10.BIT.MKP10 = _INT_PROCESSING_ENABLED;
    //	R_INTP10_Start();
    /* Clear INTP3 request and enable operation */
    INTC2.ICP3.BIT.RFP3 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICP3.BIT.MKP3 = _INT_PROCESSING_ENABLED;
    /* Clear INTP5 request and enable operation */
    INTC2.ICP5.BIT.RFP5 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICP5.BIT.MKP5 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: r_intp0_interrupt
* Description  : DCR1B interrupt
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_intp0_interrupt(enable=false, channel=37, fpu=true, callt=false)
void r_intp0_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_intp1_interrupt
* Description  : INTB interrupt
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_intp1_interrupt(enable=true, channel=38, fpu=true, callt=false)
void r_intp1_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_intp2_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_intp2_interrupt(enable=false, channel=39, fpu=true, callt=false)
void r_intp2_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_intp3_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_intp3_interrupt(enable=false, channel=43, fpu=true, callt=false)
void r_intp3_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_intp4_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_intp4_interrupt(enable=false, channel=44, fpu=true, callt=false)
void r_intp4_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_intp5_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_intp5_interrupt(enable=false, channel=45, fpu=true, callt=false)
void r_intp5_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_intp6_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_intp6_interrupt(enable=false, channel=128, fpu=true, callt=false)
void r_intp6_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_intp10_interrupt
* Description  : DCR2B interrupt
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_intp10_interrupt(enable=true, channel=46, fpu=true, callt=false)
void r_intp10_interrupt(void)
{
    //	SPI_Send_PDCM_CMD_Handle();
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_intp11_interrupt
* Description  : RFC interrupt
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_intp11_interrupt(enable=true, channel=47, fpu=true, callt=false)
void r_intp11_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
