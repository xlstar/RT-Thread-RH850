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
* File Name    : r_cg_systeminit.c
* Version      :
* Device(s)    : R7F701587(LQFP176pin)
* Tool-Chain   : CCRH
* Description  : This file implements system initializing function.
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
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_intc.h"
#include "r_cg_dmac.h"
#include "r_cg_taub.h"
#include "r_cg_taud.h"
#include "r_cg_tauj.h"
#include "r_cg_wdt.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Systeminit
* Description  : This function initializes every macro.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Systeminit(void)
{
    R_PORT_Create();
    R_CGC_Create();
    R_TAUB0_Init();
    R_TAUJ0_Init();
    R_TAUJ1_Init();
    //R_SPI_Initial();
    R_INTC_Create();
    R_WDT0_Create();
    //AD1_Init();
}

/* Wake-up factors */
#define R_WUF_RESET           (uint32_t)0x00
#define R_WUF_LPS_AI          (uint32_t)(1<<14)
#define R_WUF_LPS_DI          (uint32_t)(1<<19)
#define R_WUF_INTP12          (uint32_t)(1<<23)
#define R_WUF_INTP15          (uint32_t)(1<<27)
#define R_WUF_DCUTDI          (uint32_t)(1<<31)
#define R_WUF_ERROR           (uint32_t)0xff


#define R_RESF_DeepSTOP       (uint32_t)(1<<10)
#define R_RESF_PowerUp        (uint32_t)(1<< 9)
#define R_RESF_External       (uint32_t)(1<< 8)
#define R_RESF_CVM            (uint32_t)(1<< 7)
#define R_RESF_LVI            (uint32_t)(1<< 6)
#define R_RESF_CLMA2          (uint32_t)(1<< 5)
#define R_RESF_CLMA1          (uint32_t)(1<< 4)
#define R_RESF_CLMA0          (uint32_t)(1<< 3)
#define R_RESF_WDTA1          (uint32_t)(1<< 2)
#define R_RESF_WDTA0          (uint32_t)(1<< 1)
#define R_RESF_Software       (uint32_t)(1<< 0)

#define RET_RAM_BEG 0xFEF00000
#define RET_RAM_END 0xFEF0FFFF

typedef struct
{
    /*
    0: No reset occurred
    1: Reset has occurred
    */
    unsigned long SoftwareResetFlag : 1;	/*RESF0*/
    unsigned long WDTA0ResetFlag: 1;		/*RESF1*/
    unsigned long WDTA1ResetFlag: 1;		/*RESF2*/
    unsigned long CLMA0ResetFlag: 1;		/*RESF3*/

    unsigned long CLMA1ResetFlag: 1;		/*RESF4*/
    unsigned long CLMA2ResetFlag: 1;		/*RESF5*/
    unsigned long LVIResetFlag: 1;		/*RESF6*/
    unsigned long CVMResetFlag: 1;		/*RESF7*/

    unsigned long ExternalResetFlag: 1;	/*RESF8*/
    unsigned long PowerUpResetFlag: 1;	/*RESF9*/
    unsigned long ResetFlagByDeepSTOPmode: 1;	/*RESF10*/
    unsigned long Reserved: 21;
} stRESFRegContents;

typedef union
{
    unsigned long  RESF;
    stRESFRegContents Bits;
} unRESFRegContents;

unRESFRegContents McuResetReason;

void _GetMcuResetReason(void)
{
    McuResetReason.RESF = RESCTL.RESF;
}

void _lowinit(void)
{

    uint32_t *loc_ptr;

    if(RESCTL.RESF & R_RESF_PowerUp)
    {
        loc_ptr = (uint32_t *)RET_RAM_BEG;
        while(((uint32_t *)RET_RAM_END ) > loc_ptr)
        {
            *loc_ptr = 0x00000000;
            loc_ptr++;
        }
    }
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
