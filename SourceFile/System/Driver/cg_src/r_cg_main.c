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
* File Name    : r_cg_main.c
* Version      :
* Device(s)    : R7F701587(LQFP176pin)
* Tool-Chain   : CCRH
* Description  : This file implements main function.
* Creation Date: 2018/6/12
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
#define EEELIB_INTDEF

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_intc.h"
#include "r_cg_dmac.h"
#include "r_cg_wdt.h"
#include "r_cg_adc.h"
#include "r_cg_csih.h"
#include "r_cg_taub.h"
#include "r_cg_taud.h"
#include "r_cg_tauj.h"

/* Start user code for include. Do not edit comment generated here */

/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */


/* End user code. Do not edit comment generated here */

#pragma section r0_disp32 "GLOBAL_RAM_A_END"
volatile unsigned short wGLOBAL_RAM_A_END;
#pragma section default
#pragma section r0_disp32 "GLOBAL_RAM_B_END"
volatile unsigned short wGLOBAL_RAM_B_END;
#pragma section default
#pragma section r0_disp32 "RETENTION_RAM_END"
volatile unsigned short wRETENTION_RAM_END;
#pragma section default
#pragma section r0_disp32 "LOCAL_RAM_END"
volatile unsigned short wLOCAL_RAM_END;
#pragma section default

void R_MAIN_UserInit(void);

extern void MPU_Init_R7F7016443_Debug(void);
extern void MPU_R7F7016443_EnableSVP(void);

extern void rtthread_taskinit(void);
extern int rtthread_startup(void);
/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void main(void)
{   
    R_MAIN_UserInit();

    /* Start user code. Do not edit comment generated here */
    __EI();    

    rtthread_startup();

    while (1U)
    {       
        if(R_GetTimeStamp_1ms_Cnt() % 50 == 0)
        {
            R_WDT1_Restart();        //WatchDog
            R_WDT0_Restart();        //WatchDog
        }        
    };
    /* End user code. Do not edit comment generated here */
}

uint32_t d_1ms_timer_cnt_Pre = 0;
void user_main(void)
{    
    rtthread_taskinit();    
    MPU_Init_R7F7016443_Debug();
    MPU_R7F7016443_EnableSVP();
    while (1U)
    {        
        if(R_GetTimeStamp_1ms_Cnt() % 50 == 0)
        {
            R_WDT1_Restart();        //WatchDog
            R_WDT0_Restart();        //WatchDog
            d_1ms_timer_cnt_Pre = R_GetTimeStamp_1ms_Cnt();
        }        
    };
}

void Hw_FeedWatchdog(void)
{
    R_WDT1_Restart();
    R_WDT0_Restart();
}

void INTRCAN3TRX_InterruptHandler(void) { }
void INTRCANGRECC_InterruptHandler(void) { }
void INTRCANGERR_InterruptHandler(void) { }
void INTRCAN4TRX_InterruptHandler(void) { }
void INTRCAN4GERR_InterruptHandler(void) { }

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    DI();
    R_Systeminit();
    R_TAUJ1_Channel0_Start();
    R_CSIH3_Start();
    R_ADC0_ScanGroup1_OperationOn();
    EI();
    //	R_TAUJ0_Channel0_Start();
    /* End user code. Do not edit comment generated here */
}


/* R7F7016443 / F1KM-S4 */
#define MPU_CODE_FLASH_START     0x00000000u
#define MPU_CODE_FLASH_END       0x00300000u   /* 3 MB */

#define MPU_LOCAL_RAM_START      0xFEBD0000u
#define MPU_LOCAL_RAM_END        0xFEBFFFFFu   /* 192 KB */

#define MPU_GLOBAL_RAM_A_START   0xFEEF0000
#define MPU_GLOBAL_RAM_A_END     0xFEEFFFFF   /* 64 KB */

#define MPU_GLOBAL_RAM_B_START   0xFEFF0000
#define MPU_GLOBAL_RAM_B_END     0xFEFFFFFF   /* 64 KB */

#define MPU_RET_RAM_START        0xFEF00000u
#define MPU_RET_RAM_END          0xFEF0FFFFu   /* 64 KB */

#define MPU_DATA_FLASH_START     0xFF200000u
#define MPU_DATA_FLASH_END       0xFF21FFFFu   /* 128 KB */

#define MPU_PERIPH1_START       0xFFA00000u
#define MPU_PERIPH1_END         0xFFFDFFFFu
        
#define MPU_PERIPH2_START       0xFFFEE000u
#define MPU_PERIPH2_END         0xFFFEFFFFu
        
#define MPU_PERIPH3_START       0xFFFF5000u
#define MPU_PERIPH3_END         0xFFFFFFFFu

/* MPAT bits */
#define MPAT_UR                  (1u << 0)
#define MPAT_UW                  (1u << 1)
#define MPAT_UX                  (1u << 2)
#define MPAT_SR                  (1u << 3)
#define MPAT_SW                  (1u << 4)
#define MPAT_SX                  (1u << 5)
#define MPAT_G                   (1u << 6)
#define MPAT_E                   (1u << 7)

/* MPM bits */
#define MPM_MPE                  (1u << 0)
#define MPM_SVP                  (1u << 1)

#define MPU_NO_ACCESS            (MPAT_E | MPAT_G)
#define MPU_S_RX                 (MPAT_E | MPAT_G | MPAT_SR | MPAT_SX)
#define MPU_S_RO                 (MPAT_E | MPAT_G | MPAT_SR)
#define MPU_S_RW                 (MPAT_E | MPAT_G | MPAT_SR | MPAT_SW)

void rh850_mpu_write_mpm(uint32_t value);

void rh850_mpu_write_region0(uint32_t lower, uint32_t upper, uint32_t attr);
void rh850_mpu_write_region1(uint32_t lower, uint32_t upper, uint32_t attr);
void rh850_mpu_write_region2(uint32_t lower, uint32_t upper, uint32_t attr);
void rh850_mpu_write_region3(uint32_t lower, uint32_t upper, uint32_t attr);
void rh850_mpu_write_region4(uint32_t lower, uint32_t upper, uint32_t attr);
void rh850_mpu_write_region5(uint32_t lower, uint32_t upper, uint32_t attr);
void rh850_mpu_write_region6(uint32_t lower, uint32_t upper, uint32_t attr);
void rh850_mpu_write_region7(uint32_t lower, uint32_t upper, uint32_t attr);

void MPU_Init_R7F7016443_Debug(void);

/* MPM = SR0, selID 5 */
#pragma inline_asm rh850_mpu_write_mpm
void rh850_mpu_write_mpm(uint32_t value)
{
    ldsr r6, 0, 5
    syncp
    //synci
}

/* Region 0: MPLA0=SR0, MPUA0=SR1, MPAT0=SR2, selID=6 */
#pragma inline_asm rh850_mpu_write_region0
void rh850_mpu_write_region0(uint32_t lower, uint32_t upper, uint32_t attr)
{
    ldsr r6, 0, 6
    ldsr r7, 1, 6
    ldsr r8, 2, 6
    syncp
}

/* Region 1: SR4/SR5/SR6, selID=6 */
#pragma inline_asm rh850_mpu_write_region1
void rh850_mpu_write_region1(uint32_t lower, uint32_t upper, uint32_t attr)
{
    ldsr r6, 4, 6
    ldsr r7, 5, 6
    ldsr r8, 6, 6
    syncp
}

/* Region 2: SR8/SR9/SR10, selID=6 */
#pragma inline_asm rh850_mpu_write_region2
void rh850_mpu_write_region2(uint32_t lower, uint32_t upper, uint32_t attr)
{
    ldsr r6, 8, 6
    ldsr r7, 9, 6
    ldsr r8, 10, 6
    syncp
}

/* Region 3: SR12/SR13/SR14, selID=6 */
#pragma inline_asm rh850_mpu_write_region3
void rh850_mpu_write_region3(uint32_t lower, uint32_t upper, uint32_t attr)
{
    ldsr r6, 12, 6
    ldsr r7, 13, 6
    ldsr r8, 14, 6
    syncp
}

/* Region 4: SR16/SR17/SR18, selID=6 */
#pragma inline_asm rh850_mpu_write_region4
void rh850_mpu_write_region4(uint32_t lower, uint32_t upper, uint32_t attr)
{
    ldsr r6, 16, 6
    ldsr r7, 17, 6
    ldsr r8, 18, 6
    syncp
}

/* Region 5: SR20/SR21/SR22, selID=6 */
#pragma inline_asm rh850_mpu_write_region5
void rh850_mpu_write_region5(uint32_t lower, uint32_t upper, uint32_t attr)
{
    ldsr r6, 20, 6
    ldsr r7, 21, 6
    ldsr r8, 22, 6
    syncp
}

/* Region 6: SR24/SR25/SR26, selID=6 */
#pragma inline_asm rh850_mpu_write_region6
void rh850_mpu_write_region6(uint32_t lower, uint32_t upper, uint32_t attr)
{
    ldsr r6, 24, 6
    ldsr r7, 25, 6
    ldsr r8, 26, 6
    syncp
}

/* Region 7: SR28/SR29/SR30, selID=6 */
#pragma inline_asm rh850_mpu_write_region7
void rh850_mpu_write_region7(uint32_t lower, uint32_t upper, uint32_t attr)
{
    ldsr r6, 28, 6
    ldsr r7, 29, 6
    ldsr r8, 30, 6
    syncp
}

/* Region 8: SR0/SR1/SR2, selID=7 */
#pragma inline_asm rh850_mpu_write_region8
void rh850_mpu_write_region8(uint32_t lower, uint32_t upper, uint32_t attr)
{
    ldsr r6, 0, 7
    ldsr r7, 1, 7
    ldsr r8, 2, 7
    syncp
}

static void MPU_SetRegion(uint32_t region,
                          uint32_t lower,
                          uint32_t upper,
                          uint32_t attr)
{
    switch (region) {
    case 0: rh850_mpu_write_region0(lower, upper, attr); break;
    case 1: rh850_mpu_write_region1(lower, upper, attr); break;
    case 2: rh850_mpu_write_region2(lower, upper, attr); break;
    case 3: rh850_mpu_write_region3(lower, upper, attr); break;
    case 4: rh850_mpu_write_region4(lower, upper, attr); break;
    case 5: rh850_mpu_write_region5(lower, upper, attr); break;
    case 6: rh850_mpu_write_region6(lower, upper, attr); break;
    case 7: rh850_mpu_write_region7(lower, upper, attr); break;
    case 8: rh850_mpu_write_region8(lower, upper, attr); break;
    default:
        break;
    }
}

void MPU_Init_R7F7016443_Debug(void)
{
    rh850_mpu_write_mpm(0u);

    MPU_SetRegion(0,
                  MPU_CODE_FLASH_START,
                  MPU_CODE_FLASH_END,
                  MPU_S_RX);

    MPU_SetRegion(1,
                  MPU_LOCAL_RAM_START,
                  MPU_LOCAL_RAM_END,
                  MPU_S_RW);

    MPU_SetRegion(2,
                   MPU_GLOBAL_RAM_A_START,
                   MPU_GLOBAL_RAM_A_END,
                   MPU_S_RW);

    MPU_SetRegion(3,
                   MPU_GLOBAL_RAM_B_START,
                   MPU_GLOBAL_RAM_B_END,
                   MPU_S_RW);

    MPU_SetRegion(4,
                  MPU_RET_RAM_START,
                  MPU_RET_RAM_END,
                  MPU_S_RW);

    MPU_SetRegion(5,
                  MPU_DATA_FLASH_START,
                  MPU_DATA_FLASH_END,
                  MPU_S_RO); 

    MPU_SetRegion(6,
                  MPU_PERIPH1_START,
                  MPU_PERIPH1_END,
                  MPU_S_RW);    

    MPU_SetRegion(7,
                  MPU_PERIPH2_START,
                  MPU_PERIPH2_END,
                  MPU_S_RW);    

    MPU_SetRegion(8,
                  MPU_PERIPH3_START,
                  MPU_PERIPH3_END,
                  MPU_S_RW);    

    rh850_mpu_write_mpm(MPM_MPE /*| MPM_SVP*/);
}

void MPU_R7F7016443_EnableSVP(void)
{
    rh850_mpu_write_mpm(MPM_MPE | MPM_SVP);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
