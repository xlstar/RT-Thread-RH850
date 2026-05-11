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
* File Name    : r_cg_port.c
* Version      :
* Device(s)    : R7F701587(LQFP176pin)
* Tool-Chain   : CCRH
* Description  : This file implements device driver for Port module.
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
#include "r_cg_port.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t g_cg_sync_read      /* Synchronization processing */;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_PORT_Create
* Description  : This function initializes the Port I/O.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PORT_Create(void)
{
    NOP();
    /* PORT initialization */
    PORT.APIBC0 = _PORT_APIBC_INIT;
    PORT.PIBC0 = _PORT_PIBC_INIT;
    PORT.PIBC8 = _PORT_PIBC_INIT;
    PORT.PBDC0 = _PORT_PBDC_INIT;
    PORT.PBDC8 = _PORT_PBDC_INIT;
    PORT.APIBC0 = _PORT_APIBC_INIT;
    PORT.APBDC0 = _PORT_APBDC_INIT;
    PORT.APM0 = _PORT_APM_INIT;
    PORT.PM0 = _PORT_PM_INIT;
    PORT.PM8 = _PORT_PM_INIT;
    PORT.PMC0 = _PORT_PMC_INIT;
    PORT.PMC8 = _PORT_PMC_INIT;
    PORT.PIPC0 = _PORT_PIPC_INIT;
    /* Analog Port0 setting  AP0_1:FLS_FLC POWER AP0_2:RLS_RLC AP0_6:FLM_FRM AP0_7:FRC_FRS AP0_8:RLM_RRM AP0_9:RRC_RRS*/
    /* Analog Port0 setting  AP0_3:TPS2H000 DIAG_EN AP0_14:TPS4H000 DIAG_EN*/
    PORT.APBDC0 = _PORT_APBDCn2_APBDC_MODE_DISABLED | _PORT_APBDCn13_APBDC_MODE_DISABLED;
    PORT.AP0 =	_PORT_APn6_OUTPUT_LOW |
                //    PORT.AP0 =	_PORT_APn1_OUTPUT_LOW | _PORT_APn2_OUTPUT_LOW | _PORT_APn3_OUTPUT_LOW | _PORT_APn6_OUTPUT_LOW |
                _PORT_APn7_OUTPUT_LOW | _PORT_APn8_OUTPUT_LOW | _PORT_APn9_OUTPUT_LOW | _PORT_APn13_OUTPUT_LOW | _PORT_APn14_OUTPUT_LOW ;
    PORT.APM0 = _PORT_APMn15_MODE_UNUSED | _PORT_APMn14_MODE_OUTPUT | _PORT_APMn13_MODE_OUTPUT |
                _PORT_APMn12_MODE_INPUT | _PORT_APMn11_MODE_INPUT | _PORT_APMn10_MODE_INPUT |
                _PORT_APMn9_MODE_OUTPUT | _PORT_APMn8_MODE_OUTPUT | _PORT_APMn7_MODE_OUTPUT |
                _PORT_APMn6_MODE_OUTPUT | _PORT_APMn5_MODE_INPUT | _PORT_APMn4_MODE_INPUT |
                //                _PORT_APMn3_MODE_OUTPUT | _PORT_APMn2_MODE_OUTPUT | _PORT_APMn1_MODE_OUTPUT | _PORT_APMn0_MODE_UNUSED;
                _PORT_APMn3_MODE_UNUSED | _PORT_APMn2_MODE_UNUSED | _PORT_APMn1_MODE_UNUSED | _PORT_APMn0_MODE_UNUSED;
    PORT.APIBC0 = _PORT_PIBCn10_INPUT_BUFFER_ENABLE | _PORT_PIBCn11_INPUT_BUFFER_ENABLE | _PORT_PIBCn12_INPUT_BUFFER_ENABLE;
#if 1
    /* Port0 setting */
    /* P0_1  input to detect DCR1B */
    /* P0_2  input to detect INTB */
    /* P0_3  input to detect DCR2B */
    /* P0_4  input to detect RFC */
    /* P0_5  output to control RESB */
    PORT.PPCMD0 = _WRITE_PROTECT_COMMAND;
    PORT.PDSC0 = _PORT_PDSCn5_SLOW_MODE_SELECT;
    PORT.PDSC0 = (uint32_t) ~_PORT_PDSCn5_SLOW_MODE_SELECT;
    PORT.PDSC0 = _PORT_PDSCn5_SLOW_MODE_SELECT;
    PORT.PPCMD0 = _WRITE_PROTECT_COMMAND;
    PORT.PODC0 = _PORT_PODCn5_PUSH_PULL;
    PORT.PODC0 = (uint32_t) ~_PORT_PODCn5_PUSH_PULL;
    PORT.PODC0 = _PORT_PODCn5_PUSH_PULL;
    PORT.PBDC0 = _PORT_PBDCn5_PBDC_MODE_DISABLED;

    PORT.P0 = _PORT_Pn5_OUTPUT_HIGH | _PORT_Pn12_OUTPUT_HIGH | _PORT_Pn11_OUTPUT_LOW;
    PORT.PM0 = _PORT_PM0_DEFAULT_VALUE | _PORT_PMn14_MODE_UNUSED | _PORT_PMn13_MODE_UNUSED | _PORT_PMn12_MODE_OUTPUT |
               _PORT_PMn11_MODE_OUTPUT | _PORT_PMn10_MODE_UNUSED | _PORT_PMn9_MODE_UNUSED | _PORT_PMn8_MODE_UNUSED |
               _PORT_PMn7_MODE_UNUSED | _PORT_PMn6_MODE_UNUSED | _PORT_PMn5_MODE_OUTPUT | _PORT_PMn4_MODE_UNUSED |
               _PORT_PMn3_MODE_UNUSED | _PORT_PMn2_MODE_UNUSED | _PORT_PMn1_MODE_UNUSED | _PORT_PMn0_MODE_UNUSED;
#endif
    /* Port8 setting */
    /* P8_0  output to control TJA1041A_EN */
    /* P8_1  input to detect TJA1041A_Err */
    /* P8_3  output to control TJA1041A_STB */
    /* P8_4  output to control TJA1044_STB */
    /* P8_7 input for detect test start button */
    /* P8_9 : FLS2_RLS2 */
    /* P8_10 output control NG LED,P8_11 output control OK LED */
    PORT.PPCMD8 = _WRITE_PROTECT_COMMAND;
    PORT.PODC8 = _PORT_PODCn10_PUSH_PULL;
    PORT.PODC8 = (uint32_t) ~_PORT_PODCn10_PUSH_PULL;
    PORT.PODC8 = _PORT_PODCn10_PUSH_PULL;
    PORT.PBDC8 = _PORT_PBDCn10_PBDC_MODE_DISABLED;
    PORT.PU8 = _PORT_PUn12_PULLUP_OFF | _PORT_PUn9_PULLUP_OFF | _PORT_PUn8_PULLUP_OFF |
               _PORT_PUn7_PULLUP_OFF | _PORT_PUn5_PULLUP_OFF | _PORT_PUn4_PULLUP_OFF |
               _PORT_PUn3_PULLUP_OFF | _PORT_PUn2_PULLUP_OFF | _PORT_PUn1_PULLUP_OFF | _PORT_PUn0_PULLUP_OFF;
    PORT.PD8 = _PORT_PDn12_PULLDOWN_OFF | _PORT_PDn9_PULLDOWN_OFF |
               _PORT_PDn8_PULLDOWN_OFF | _PORT_PDn7_PULLDOWN_OFF | _PORT_PDn5_PULLDOWN_OFF |
               _PORT_PDn4_PULLDOWN_OFF | _PORT_PDn3_PULLDOWN_OFF | _PORT_PDn2_PULLDOWN_OFF | _PORT_PDn1_PULLDOWN_OFF |
               _PORT_PDn0_PULLDOWN_OFF;
    PORT.PIS8 = _PORT_PIS8_DEFAULT_VALUE | _PORT_PISn12_TYPE_SHMT4 |
                _PORT_PISn9_TYPE_SHMT4 | _PORT_PISn8_TYPE_SHMT4 | _PORT_PISn7_TYPE_SHMT1 |
                _PORT_PISn5_TYPE_SHMT4 | _PORT_PISn4_TYPE_SHMT4 | _PORT_PISn3_TYPE_SHMT4 | _PORT_PISn2_TYPE_SHMT4 |
                _PORT_PISn1_TYPE_SHMT4 | _PORT_PISn0_TYPE_SHMT4;
    PORT.P8 = _PORT_Pn11_OUTPUT_LOW | _PORT_Pn6_OUTPUT_HIGH | _PORT_Pn4_OUTPUT_LOW | _PORT_Pn3_OUTPUT_LOW;
    PORT.PM8 = _PORT_PM8_DEFAULT_VALUE | _PORT_PMn12_MODE_UNUSED | _PORT_PMn11_MODE_OUTPUT | _PORT_PMn10_MODE_UNUSED |
               _PORT_PMn9_MODE_INPUT | _PORT_PMn8_MODE_UNUSED | _PORT_PMn7_MODE_INPUT | _PORT_PMn6_MODE_OUTPUT |
               _PORT_PMn5_MODE_UNUSED | _PORT_PMn4_MODE_OUTPUT | _PORT_PMn3_MODE_OUTPUT | _PORT_PMn2_MODE_UNUSED |
               _PORT_PMn1_MODE_OUTPUT | _PORT_PMn0_MODE_UNUSED;
    PORT.PIBC8 = _PORT_PIBCn7_INPUT_BUFFER_ENABLE;
    /* Port9 setting */
    // P9_5:FR_RR P9_6:FLM_RLM
    PORT.PPCMD9 = _WRITE_PROTECT_COMMAND;
    PORT.PODC9 = _PORT_PODCn6_PUSH_PULL | _PORT_PODCn5_PUSH_PULL;
    PORT.PODC9 = (uint32_t) ~(_PORT_PODCn6_PUSH_PULL | _PORT_PODCn5_PUSH_PULL);
    PORT.PODC9 = _PORT_PODCn6_PUSH_PULL | _PORT_PODCn5_PUSH_PULL;
    PORT.PBDC9 = _PORT_PBDCn6_PBDC_MODE_DISABLED | _PORT_PBDCn5_PBDC_MODE_DISABLED;
    PORT.P9 = _PORT_Pn6_OUTPUT_LOW | _PORT_Pn5_OUTPUT_LOW;
    PORT.PM9 = _PORT_PM9_DEFAULT_VALUE | _PORT_PMn6_MODE_INPUT | _PORT_PMn5_MODE_INPUT | _PORT_PMn4_MODE_UNUSED |
               _PORT_PMn3_MODE_UNUSED | _PORT_PMn2_MODE_UNUSED | _PORT_PMn1_MODE_UNUSED | _PORT_PMn0_MODE_UNUSED;
    /* Port10 setting */
    /* Input PIN: P10_3:DCR1B; P10_4:DCR2B; P10_5:INTB; P10_15:RFC */
#if 0
    PORT.PPCMD10 = _WRITE_PROTECT_COMMAND;
    PORT.PDSC10 = _PORT_PDSCn14_SLOW_MODE_SELECT;
    PORT.PDSC10 = (uint32_t) ~_PORT_PDSCn14_SLOW_MODE_SELECT;
    PORT.PDSC10 = _PORT_PDSCn14_SLOW_MODE_SELECT;
    PORT.PPCMD10 = _WRITE_PROTECT_COMMAND;
    PORT.PODC10 = _PORT_PODCn14_PUSH_PULL;
    PORT.PODC10 = (uint32_t) ~_PORT_PODCn14_PUSH_PULL;
    PORT.PODC10 = _PORT_PODCn14_PUSH_PULL;
    PORT.PBDC10 = _PORT_PBDCn14_PBDC_MODE_DISABLED;
#endif
    PORT.PU10 = _PORT_PUn15_PULLUP_OFF | _PORT_PUn14_PULLUP_OFF | _PORT_PUn13_PULLUP_OFF | _PORT_PUn12_PULLUP_OFF | _PORT_PUn11_PULLUP_OFF |
                _PORT_PUn10_PULLUP_OFF | _PORT_PUn9_PULLUP_OFF | _PORT_PUn8_PULLUP_OFF | _PORT_PUn6_PULLUP_OFF |
                _PORT_PUn5_PULLUP_OFF | _PORT_PUn4_PULLUP_OFF | _PORT_PUn3_PULLUP_OFF | _PORT_PUn2_PULLUP_OFF |
                _PORT_PUn1_PULLUP_OFF | _PORT_PUn0_PULLUP_OFF;
    PORT.PD10 = _PORT_PDn15_PULLDOWN_OFF | _PORT_PDn14_PULLDOWN_OFF | _PORT_PDn13_PULLDOWN_OFF | _PORT_PDn12_PULLDOWN_OFF |
                _PORT_PDn11_PULLDOWN_OFF | _PORT_PDn10_PULLDOWN_OFF | _PORT_PDn9_PULLDOWN_OFF |
                _PORT_PDn8_PULLDOWN_OFF | _PORT_PDn7_PULLDOWN_ON | _PORT_PDn6_PULLDOWN_OFF | _PORT_PDn5_PULLDOWN_OFF |
                _PORT_PDn4_PULLDOWN_OFF | _PORT_PDn3_PULLDOWN_OFF | _PORT_PDn2_PULLDOWN_OFF |
                _PORT_PDn1_PULLDOWN_OFF | _PORT_PDn0_PULLDOWN_OFF;
    PORT.PIS10 = _PORT_PISn15_TYPE_SHMT4 | _PORT_PISn14_TYPE_SHMT4 | _PORT_PISn13_TYPE_SHMT4 | _PORT_PISn12_TYPE_SHMT4 |
                 _PORT_PISn11_TYPE_SHMT4 | _PORT_PISn10_TYPE_SHMT4 | _PORT_PISn9_TYPE_SHMT1 | _PORT_PISn8_TYPE_SHMT4 |
                 _PORT_PISn7_TYPE_SHMT4 | _PORT_PISn6_TYPE_SHMT4 | _PORT_PISn5_TYPE_SHMT4 | _PORT_PISn4_TYPE_SHMT4 |
                 _PORT_PISn3_TYPE_SHMT4 | _PORT_PISn2_TYPE_SHMT4 | _PORT_PISn1_TYPE_SHMT4 | _PORT_PISn0_TYPE_SHMT4;
    PORT.P10 = _PORT_Pn14_OUTPUT_HIGH;
    PORT.PM10 = _PORT_PMn15_MODE_INPUT | _PORT_PMn14_MODE_UNUSED | _PORT_PMn13_MODE_UNUSED | _PORT_PMn12_MODE_UNUSED |
                _PORT_PMn11_MODE_UNUSED | _PORT_PMn10_MODE_UNUSED | _PORT_PMn9_MODE_UNUSED | _PORT_PMn8_MODE_UNUSED |
                _PORT_PMn7_MODE_UNUSED | _PORT_PMn6_MODE_UNUSED | _PORT_PMn5_MODE_INPUT | _PORT_PMn4_MODE_INPUT |
                _PORT_PMn3_MODE_OUTPUT | _PORT_PMn2_MODE_UNUSED | _PORT_PMn1_MODE_UNUSED | _PORT_PMn0_MODE_UNUSED;
    PORT.PIBC10 = _PORT_PIBCn15_INPUT_BUFFER_ENABLE | _PORT_PIBCn5_INPUT_BUFFER_ENABLE |
                  _PORT_PIBCn4_INPUT_BUFFER_ENABLE | _PORT_PIBCn3_INPUT_BUFFER_ENABLE;
    /* Port11 setting */
    /* P11_1:control SPI CS; P11_0: control RESB */
    PORT.PPCMD11 = _WRITE_PROTECT_COMMAND;
    PORT.PDSC11 = _PORT_PDSCn1_SLOW_MODE_SELECT | _PORT_PDSCn0_SLOW_MODE_SELECT;
    PORT.PDSC11 = (uint32_t) ~(_PORT_PDSCn1_SLOW_MODE_SELECT | _PORT_PDSCn0_SLOW_MODE_SELECT);
    PORT.PDSC11 = _PORT_PDSCn1_SLOW_MODE_SELECT | _PORT_PDSCn0_SLOW_MODE_SELECT;
    PORT.PPCMD11 = _WRITE_PROTECT_COMMAND;
    PORT.PODC11 = _PORT_PODCn1_PUSH_PULL | _PORT_PODCn0_PUSH_PULL;
    PORT.PODC11 = (uint32_t) ~(_PORT_PODCn1_PUSH_PULL | _PORT_PODCn0_PUSH_PULL);
    PORT.PODC11 = _PORT_PODCn1_PUSH_PULL | _PORT_PODCn0_PUSH_PULL;
    PORT.PBDC11 = _PORT_PBDCn1_PBDC_MODE_DISABLED | _PORT_PBDCn0_PBDC_MODE_DISABLED;
    PORT.P11 = _PORT_Pn1_OUTPUT_HIGH ;
    //	PORT.P11 &= ~_PORT_Pn1_OUTPUT_HIGH;
    PORT.PM11 = _PORT_PMn11_MODE_UNUSED | _PORT_PMn7_MODE_UNUSED | _PORT_PMn6_MODE_UNUSED | _PORT_PMn5_MODE_UNUSED |
                _PORT_PMn4_MODE_UNUSED | _PORT_PMn3_MODE_UNUSED | _PORT_PMn2_MODE_UNUSED | _PORT_PMn1_MODE_OUTPUT |
                _PORT_PMn0_MODE_INPUT;
    /* Synchronization processing */
    g_cg_sync_read = PORT.APM0;
    g_cg_sync_read = PORT.PM0;
    __syncp();
}

void R_PORT_LED1_TOG(void)
{
    PORT.P8 ^= _PORT_Pn11_OUTPUT_HIGH;
}
void R_PORT_TestPIN_TOG(void)
{
    PORT.P10 ^= _PORT_Pn2_OUTPUT_HIGH;
}
void R_PORT_SetOkLed_On(void)
{
    PORT.P8 |= _PORT_Pn11_OUTPUT_HIGH;
}
void R_PORT_SetOkLed_Off(void)
{
    PORT.P8 &= ~_PORT_Pn11_OUTPUT_HIGH;
}

void R_PORT_SetNgLed_On(void)
{
    PORT.P8 |= _PORT_Pn10_OUTPUT_HIGH;
    //	PORT.P8 |= _PORT_Pn6_OUTPUT_HIGH;
}

void R_PORT_SetNgLed_Off(void)
{
    PORT.P8 &= ~_PORT_Pn10_OUTPUT_HIGH;
    //	PORT.P8 &= _PORT_Pn6_OUTPUT_LOW;
}
void R_PORT_SetCAN0_STB_Low(void)
{
    //TJA1044 STB pin
    PORT.P8 &= ~_PORT_Pn4_OUTPUT_HIGH;
}

void R_PORT_SetCAN0_STB_High(void)
{
    //TJA1044 STB pin
    PORT.P8 |= _PORT_Pn4_OUTPUT_HIGH;
}

void R_PORT_SetCAN1_STB_Low(void)
{
    //TJA1041A STB pin
    PORT.P8 &= ~_PORT_Pn3_OUTPUT_HIGH;
}

void R_PORT_SetCAN1_STB_High(void)
{
    //TJA1041A STB pin
    PORT.P8 |= _PORT_Pn3_OUTPUT_HIGH;
}

void R_PORT_SetCAN1_EN_Low(void)
{
    //TJA1041A EN pin
    PORT.P8 &= ~_PORT_Pn0_OUTPUT_HIGH;
}

void R_PORT_SetCAN1_EN_High(void)
{
    //TJA1041A EN pin
    PORT.P8 |= _PORT_Pn0_OUTPUT_HIGH;
}

void R_PORT_Set42CS_High(void)
{
    PORT.P11 |= _PORT_Pn1_OUTPUT_HIGH;
}

void R_PORT_Set42CS_Low(void)
{
    PORT.P11 &= ~_PORT_Pn1_OUTPUT_HIGH;
}

void R_PORT_Set2nd42CS_High(void)
{
    PORT.P10 |= _PORT_Pn3_OUTPUT_HIGH;
}

void R_PORT_Set2nd42CS_Low(void)
{
    PORT.P10 &= ~_PORT_Pn3_OUTPUT_HIGH;
}

void R_PORT_SetPort8_9_High(void)
{
    PORT.P8 |= _PORT_Pn9_OUTPUT_HIGH;
}

void R_PORT_SetPort8_9_Low(void)
{
    PORT.P8 &= ~_PORT_Pn9_OUTPUT_HIGH;
}
void R_PORT_Set42RESB_High(void)
{
    PORT.P0 |= _PORT_Pn5_OUTPUT_HIGH;
}

void R_PORT_Set42RESB_Low(void)
{
    PORT.P0 &= ~_PORT_Pn5_OUTPUT_HIGH;
}
void R_PORT_Set2nd42RESB_High(void)
{
    PORT.P0 |= _PORT_Pn12_OUTPUT_HIGH;
}

void R_PORT_Set2nd42RESB_Low(void)
{
    PORT.P0 &= ~_PORT_Pn12_OUTPUT_HIGH;
}
void R_PORT_SetCLKREF_High(void)
{
    PORT.P10 |= _PORT_Pn14_OUTPUT_HIGH;
}

void R_PORT_SetCLKREF_Low(void)
{
    PORT.P10 &= ~_PORT_Pn14_OUTPUT_HIGH;
}
//FRC_FRM_FLM_FLC SENSOR
void R_PORT_FRC_FRM_FLM_FLC_PowerOn(void)
{
    PORT.AP0 |= _PORT_APn9_OUTPUT_HIGH;
}

void R_PORT_FRC_FRM_FLM_FLC_PowerOff(void)
{
    PORT.AP0 &= ~_PORT_APn9_OUTPUT_HIGH;
}

//TPS4H000
//
void CORN_SEN_PowerOn(void)
{
    PORT.AP0 |= _PORT_APn6_OUTPUT_HIGH;
}
void CORN_SEN_PowerOff(void)
{
    PORT.AP0 &= ~ _PORT_APn6_OUTPUT_HIGH;
}

void MIDD_SEN_PowerOn(void)
{
    PORT.AP0 |= _PORT_APn7_OUTPUT_HIGH;
}
void MIDD_SEN_PowerOff(void)
{
    PORT.AP0 &= ~ _PORT_APn7_OUTPUT_HIGH;
}

void SIDE_SEN_PowerOn(void)
{
    PORT.AP0 |= _PORT_Pn8_OUTPUT_HIGH;
}
void SIDE_SEN_PowerOff(void)
{
    PORT.AP0 &= ~ _PORT_Pn8_OUTPUT_HIGH;
}


//
void R_PORT_TPS4H000_DIAG_ENABLE(void)
{
    PORT.P8 |= _PORT_Pn1_OUTPUT_HIGH;
}

void R_PORT_TPS4H000_DIAG_DISABLE(void)
{
    PORT.P8 &= ~_PORT_Pn1_OUTPUT_HIGH;
}
//RLS_RRS SENSOR
void R_PORT_RLS_RRS_PowerOn(void)
{
    PORT.AP0 |= _PORT_APn7_OUTPUT_HIGH;
}

void R_PORT_RLS_RRS_PowerOff(void)
{
    PORT.AP0 &= ~_PORT_APn7_OUTPUT_HIGH;
}
//FLS_FRS SENSOR
void R_PORT_FLS_FRS_PowerOn(void)
{
    PORT.AP0 |= _PORT_APn6_OUTPUT_HIGH;
}

void R_PORT_FLS_FRS_PowerOff(void)
{
    PORT.AP0 &= ~_PORT_APn6_OUTPUT_HIGH;
}
//RLC_RLM_RRM_RRC SENSOR
void R_PORT_RLC_RLM_RRM_RRC_PowerOn(void)
{
    PORT.AP0 |= _PORT_Pn8_OUTPUT_HIGH;
}
void R_PORT_RLC_RLM_RRM_RRC_PowerOff(void)
{
    PORT.AP0 &= ~_PORT_Pn8_OUTPUT_HIGH;
}
uint16_t R_PORT_TPS4Hand2H_DiagResult(void)
{
    uint16_t pin_status;
    //	uint8_t ret = 0x00;
    pin_status = PORT.APPR0;

    return(pin_status);
}

uint8_t R_PORT_CHKINTB_High(void)
{
#if 0
    uint8_t pin_status;
    uint8_t ret = 0x00;
    pin_status = PORT.PPR10;

    if((pin_status & _PORT_Pn4_OUTPUT_HIGH) != 0x00)
    {
        ret = 0x01;
    }
    else
    {
        ret = 0x00;
    }
    return(ret);
#else
    uint8_t pin_status;
    uint8_t ret = 0x00;
    pin_status = PORT.PPR0;

    if((pin_status & _PORT_Pn2_OUTPUT_HIGH) != 0x00)
    {
        ret = 0x01;
    }
    else
    {
        ret = 0x00;
    }
    return(ret);

#endif
}

uint8_t R_PORT_CHKDCR1B_High(void)
{
#if 0
    //port10.3 for detect DCR2B
    uint8_t pin_status;
    uint8_t ret = 0x00;
    pin_status = PORT.PPR10;

    if((pin_status & _PORT_Pn3_OUTPUT_HIGH) != 0x00)
    {
        ret = 0x01;
    }
    else
    {
        ret = 0x00;
    }
    return(ret);
#else
    //port0.1 for detect DCR2B
    uint8_t pin_status;
    uint8_t ret = 0x00;
    pin_status = PORT.PPR0;

    if((pin_status & _PORT_Pn1_OUTPUT_HIGH) != 0x00)
    {
        ret = 0x01;
    }
    else
    {
        ret = 0x00;
    }
    return(ret);

#endif
}

uint8_t R_PORT_CHKDCR2B_High(void)
{
#if 0
    //port10.5 for detect DCR2B
    uint8_t pin_status;
    uint8_t ret = 0x00;
    pin_status = PORT.PPR10;

    if((pin_status & _PORT_Pn5_OUTPUT_HIGH) != 0x00)
    {
        ret = 0x01;
    }
    else
    {
        ret = 0x00;
    }
    return(ret);
#else
    //port0.3 for detect DCR2B
    uint8_t pin_status;
    uint8_t ret = 0x00;
    pin_status = PORT.PPR0;

    if((pin_status & _PORT_Pn3_OUTPUT_HIGH) != 0x00)
    {
        ret = 0x01;
    }
    else
    {
        ret = 0x00;
    }
    return(ret);

#endif
}


uint8_t R_PORT_CHKRFC_High(void)
{
#if 0
    //port10.15 for detect RFC
    uint8_t pin_status;
    uint8_t ret = 0x00;
    pin_status = PORT.PPR10;

    if((pin_status & _PORT_Pn15_OUTPUT_HIGH) != 0x00)
    {
        ret = 0x01;
    }
    else
    {
        ret = 0x00;
    }
    return(ret);
#else
    //port0.4 for detect RFC
    uint8_t pin_status;
    uint8_t ret = 0x00;
    pin_status = PORT.PPR0;

    if((pin_status & _PORT_Pn4_OUTPUT_HIGH) != 0x00)
    {
        ret = 0x01;
    }
    else
    {
        ret = 0x00;
    }
    return(ret);
#endif
}

uint8_t R_PORT_CHKTJA1041A_ERR_High(void)
{
    uint8_t pin_status;
    uint8_t ret = 0x00;
    pin_status = PORT.PPR8;

    if((pin_status & _PORT_Pn1_OUTPUT_HIGH) != 0x00)
    {
        ret = 0x01;
    }
    else
    {
        ret = 0x00;
    }
    return(ret);

}
uint8_t R_PORT_CHKSW_TestStart_High(void)
{
    uint8_t pin_status;
    uint8_t ret = 0x00;
    pin_status = PORT.PPR8;

    if((pin_status & _PORT_Pn7_OUTPUT_HIGH) != 0x00)
    {
        ret = 0x01;
    }
    else
    {
        ret = 0x00;
    }
    return(ret);
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
