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
* File Name    : r_cg_csih_user.c
* Version      :
* Device(s)    : R7F701587(LQFP176pin)
* Tool-Chain   : CCRH
* Description  : This file implements device driver for CSIH module.
* Creation Date: 2018/5/10
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
#include "r_cg_csih.h"
#include "r_cg_port.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_csih0_interrupt_receive
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_csih0_interrupt_receive(enable=true, channel=30, fpu=true, callt=false)
void r_csih0_interrupt_receive(void)
{
    
}
/***********************************************************************************************************************
* Function Name: r_csih0_interrupt_error
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_csih0_interrupt_error(enable=true, channel=31, fpu=true, callt=false)
void r_csih0_interrupt_error(void)
{

}
/***********************************************************************************************************************
* Function Name: r_csih0_interrupt_send
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_csih0_interrupt_send(enable=true, channel=29, fpu=true, callt=false)
void r_csih0_interrupt_send(void)
{

}

/***********************************************************************************************************************
* Function Name: r_csih1_interrupt_receive
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_csih1_interrupt_receive(enable=false, channel=117, fpu=true, callt=false)
void r_csih1_interrupt_receive(void)
{

}
/***********************************************************************************************************************
* Function Name: r_csih1_interrupt_error
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_csih1_interrupt_error(enable=false, channel=118, fpu=true, callt=false)
void r_csih1_interrupt_error(void)
{

}
/***********************************************************************************************************************
* Function Name: r_csih1_interrupt_send
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_csih1_interrupt_send(enable=false, channel=116, fpu=true, callt=false)
void r_csih1_interrupt_send(void)
{

}

/***********************************************************************************************************************
* Function Name: r_csih2_interrupt_receive
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_csih2_interrupt_receive(enable=false, channel=133, fpu=true, callt=false)
void r_csih2_interrupt_receive(void)
{

}
/***********************************************************************************************************************
* Function Name: r_csih2_interrupt_error
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_csih2_interrupt_error(enable=false, channel=134, fpu=true, callt=false)
void r_csih2_interrupt_error(void)
{

}
/***********************************************************************************************************************
* Function Name: r_csih2_interrupt_send
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_csih2_interrupt_send(enable=false, channel=132, fpu=true, callt=false)
void r_csih2_interrupt_send(void)
{

}

/***********************************************************************************************************************
* Function Name: r_csih3_interrupt_receive
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_csih3_interrupt_receive(enable=false, channel=159, fpu=true, callt=false)
void r_csih3_interrupt_receive(void)
{
    
}
/***********************************************************************************************************************
* Function Name: r_csih3_interrupt_error
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_csih3_interrupt_error(enable=false, channel=160, fpu=true, callt=false)
void r_csih3_interrupt_error(void)
{

}

/***********************************************************************************************************************
* Function Name: r_csih3_interrupt_send
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_csih3_interrupt_send(enable=false, channel=158, fpu=true, callt=false)
void r_csih3_interrupt_send(void)
{
    
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
