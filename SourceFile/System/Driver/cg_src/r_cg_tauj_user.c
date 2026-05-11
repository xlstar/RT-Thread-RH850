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
* File Name    : r_cg_tauj_user.c
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

uint32_t d_1ms_timer_cnt;

uint32_t R_GetTimeStamp_1ms_Cnt(void);
/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: r_tauj0_channel3_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

#pragma interrupt r_tauj0_channel0_interrupt(enable=false, channel=80, fpu=true, callt=false)
void r_tauj0_channel0_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_tauj0_channel1_interrupt
* Description  : 1us timer base
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_tauj0_channel1_interrupt(enable=false, channel=81, fpu=true, callt=false)
void r_tauj0_channel1_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_tauj0_channel3_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_tauj0_channel3_interrupt(enable=false, channel=83, fpu=true, callt=false)
void r_tauj0_channel3_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_tauj1_channel0_interrupt
* Description  : 1ms timer
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_tauj1_channel0_interrupt(enable=true, channel=168, fpu=true, callt=false)
void r_tauj1_channel0_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    d_1ms_timer_cnt ++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_tauj1_channel1_interrupt
* Description  : 1us timer
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
//static uint8_t d_tauj1_ch1_cnt;
#pragma interrupt r_tauj1_channel1_interrupt(enable=false, channel=169, fpu=true, callt=false)
void r_tauj1_channel1_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_tauj1_channel2_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_tauj1_channel2_interrupt(enable=false, channel=170, fpu=true, callt=false)
void r_tauj1_channel2_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_tauj1_channel3_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_tauj1_channel3_interrupt(enable=false, channel=171, fpu=true, callt=false)
void r_tauj1_channel3_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
void TIM_SetDelayTime(uint32_t value)
{
    R_TAUJ0_Channel1_Stop();
    //	d_Wait_timer_Flag = 1;
    TAUJ0.CDR1 = value;
    R_TAUJ0_Channel1_Start();
    //	ObjDtdTimerTimeoutCnt = 0;
    //	while(d_Wait_timer_Flag != 0)
    //	{
    //	}
}

uint32_t R_GetTimeStamp_1ms_Cnt(void)
{
    return d_1ms_timer_cnt;
}

void R_SetTimeStamp_1ms_Cnt(void)
{
    d_1ms_timer_cnt ++;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
