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
* File Name    : r_cg_csih.c
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
extern volatile uint32_t g_cg_sync_read;

/***********************************************************************************************************************
* Function Name: R_CSIH0_Create
* Description  : This function initializes the CSIH0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSIH0_Create(void)
{
    uint32_t tmp_port;

    /* Disable CSIH0 operation */
    CSIH0.CTL0 = _CSIH_OPERATION_CLOCK_STOP;
    /* Disable INTCSIH0IC operation and clear request */
    INTC1.ICCSIH0IC.BIT.MKCSIH0IC = _INT_PROCESSING_DISABLED;
    INTC1.ICCSIH0IC.BIT.RFCSIH0IC = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTCSIH0IR operation and clear request */
    INTC1.ICCSIH0IR.BIT.MKCSIH0IR = _INT_PROCESSING_DISABLED;
    INTC1.ICCSIH0IR.BIT.RFCSIH0IR = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTCSIH0IRE operation and clear request */
    INTC1.ICCSIH0IRE.BIT.MKCSIH0IRE = _INT_PROCESSING_DISABLED;
    INTC1.ICCSIH0IRE.BIT.RFCSIH0IRE = _INT_REQUEST_NOT_OCCUR;
    /* Set CSIH0 interrupt(INTCSIH0IC) setting */
    INTC1.ICCSIH0IC.BIT.TBCSIH0IC = _INT_TABLE_VECTOR;
    INTC1.ICCSIH0IC.UINT16 &= _INT_PRIORITY_LOWEST - 2U;
    /* Set CSIH0 interrupt(INTCSIH0IR) setting */
    INTC1.ICCSIH0IR.BIT.TBCSIH0IR = _INT_TABLE_VECTOR;
    INTC1.ICCSIH0IR.UINT16 &= _INT_PRIORITY_LOWEST - 2U;
    /* Set CSIH0 interrupt(INTCSIH0IRE) setting */
    INTC1.ICCSIH0IRE.BIT.TBCSIH0IRE = _INT_TABLE_VECTOR;
    INTC1.ICCSIH0IRE.UINT16 &= _INT_PRIORITY_LOWEST - 2U;
    /* Set CSIH0 control setting */
    CSIH0.CTL1 = _CSIH_INTERRUPT_TIMING_NORMAL | _CSIH_CHIPSELECT0_ACTIVE_LOW | _CSIH_DATA_CONSISTENCY_CHECK_DISABLE |
                 _CSIH_CHIPSELECT_SIGNAL_HOLD_INACTIVE | _CSIH_NO_DELAY | _CSIH_HANDSHAKE_DISABLE |
                 _CSIH_SLAVE_SELECT_DISABLE;
    CSIH0.CTL2 = _CSIH0_SELECT_BASIC_CLOCK;
    CSIH0.BRS0 = _CSIH0_BAUD_RATE_0;
    CSIH0.BRS1 = _CSIH0_BAUD_RATE_1;
    CSIH0.BRS2 = _CSIH0_BAUD_RATE_2;
    CSIH0.BRS3 = _CSIH0_BAUD_RATE_3;
    /* Set CSIH0 configuration setting */
    CSIH0.CFG0 = _CSIH_USED_BAUDRATE_0 | _CSIH_PARITY_NO | _CSIH_DATA_LENGTH_8 | _CSIH_DATA_DIRECTION_MSB |
                 _CSIHn_MASTER_PHASE_SELECTION_TYPE1 | _CSIH_IDLE_INSERTED_NOT_ALWAYS | _CSIH_IDLE_TIME_0 |
                 _CSIH_HOLD_TIME_0 | _CSIH_INTER_DATA_DELAY_TIME_0 | _CSIH_SETUP_TIME_0;
    /* Synchronization processing */
    g_cg_sync_read = CSIH0.CTL1;
    __syncp();
    /* Set CSIH0SC pin */
    PORT.PIBC0 &= _PORT_CLEAR_BIT2;
    PORT.PBDC0 &= _PORT_CLEAR_BIT2;
    PORT.PM0 |= _PORT_SET_BIT2;
    PORT.PMC0 &= _PORT_CLEAR_BIT2;
    PORT.PIPC0 &= _PORT_CLEAR_BIT2;
    tmp_port = PORT.PDSC0;
    PORT.PPCMD0 = _WRITE_PROTECT_COMMAND;
    PORT.PDSC0 = (tmp_port | _PORT_SET_BIT2);
    PORT.PDSC0 = (uint32_t) ~(tmp_port | _PORT_SET_BIT2);
    PORT.PDSC0 = (tmp_port | _PORT_SET_BIT2);
    PORT.PFC0 |= _PORT_SET_BIT2;
    PORT.PFCE0 |= _PORT_SET_BIT2;
    PORT.PFCAE0 &= _PORT_CLEAR_BIT2;
    PORT.PIPC0 |= _PORT_SET_BIT2;
    PORT.PMC0 |= _PORT_SET_BIT2;
    /* Set CSIH0SO pin */
    PORT.PIBC0 &= _PORT_CLEAR_BIT3;
    PORT.PBDC0 &= _PORT_CLEAR_BIT3;
    PORT.PM0 |= _PORT_SET_BIT3;
    PORT.PMC0 &= _PORT_CLEAR_BIT3;
    PORT.PIPC0 &= _PORT_CLEAR_BIT3;
    tmp_port = PORT.PDSC0;
    PORT.PPCMD0 = _WRITE_PROTECT_COMMAND;
    PORT.PDSC0 = (tmp_port | _PORT_SET_BIT3);
    PORT.PDSC0 = (uint32_t) ~(tmp_port | _PORT_SET_BIT3);
    PORT.PDSC0 = (tmp_port | _PORT_SET_BIT3);
    PORT.PFC0 |= _PORT_SET_BIT3;
    PORT.PFCE0 |= _PORT_SET_BIT3;
    PORT.PFCAE0 &= _PORT_CLEAR_BIT3;
    PORT.PIPC0 |= _PORT_SET_BIT3;
    PORT.PMC0 |= _PORT_SET_BIT3;
    /* Set CSIH0SI pin */
    PORT.PIBC0 &= _PORT_CLEAR_BIT1;
    PORT.PBDC0 &= _PORT_CLEAR_BIT1;
    PORT.PM0 |= _PORT_SET_BIT1;
    PORT.PMC0 &= _PORT_CLEAR_BIT1;
    PORT.PFC0 |= _PORT_SET_BIT1;
    PORT.PFCE0 |= _PORT_SET_BIT1;
    PORT.PFCAE0 &= _PORT_CLEAR_BIT1;
    PORT.PMC0 |= _PORT_SET_BIT1;
    /* Set CSIH0CSS0 pin */
    //   PORT.PIBC8 &= _PORT_CLEAR_BIT0;
    //   PORT.PBDC8 &= _PORT_CLEAR_BIT0;
    //   PORT.PM8 |= _PORT_SET_BIT0;
    //   PORT.PMC8 &= _PORT_CLEAR_BIT0;
    //   PORT.PFC8 &= _PORT_CLEAR_BIT0;
    //   PORT.PFCE8 |= _PORT_SET_BIT0;
    //   PORT.PMC8 |= _PORT_SET_BIT0;
    //   PORT.PM8 &= _PORT_CLEAR_BIT0;

}
/***********************************************************************************************************************
* Function Name: R_CSIH0_Start
* Description  : This function starts the CSIH0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSIH0_Start(void)
{
    /* Enable CSIH0 operation */
    CSIH0.CTL0 = _CSIH_OPERATION_CLOCK_PROVIDE | _CSIH_TRANSMISSION_PERMIT | _CSIH_RECEPTION_PERMIT;
    /* Clear CSIH0 interrupt request and enable operation */
    INTC1.ICCSIH0IC.BIT.RFCSIH0IC = _INT_REQUEST_NOT_OCCUR;
    INTC1.ICCSIH0IR.BIT.RFCSIH0IR = _INT_REQUEST_NOT_OCCUR;
    INTC1.ICCSIH0IRE.BIT.RFCSIH0IRE = _INT_REQUEST_NOT_OCCUR;
    INTC1.ICCSIH0IC.BIT.MKCSIH0IC = _INT_PROCESSING_ENABLED;
    INTC1.ICCSIH0IR.BIT.MKCSIH0IR = _INT_PROCESSING_ENABLED;
    INTC1.ICCSIH0IRE.BIT.MKCSIH0IRE = _INT_PROCESSING_ENABLED;
}
/***********************************************************************************************************************
* Function Name: R_CSIH0_Stop
* Description  : This function stops the CSIH0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSIH0_Stop(void)
{
    /* Disable CSIH0 interrupt operation */
    INTC1.ICCSIH0IC.BIT.MKCSIH0IC = _INT_PROCESSING_DISABLED;
    INTC1.ICCSIH0IR.BIT.MKCSIH0IR = _INT_PROCESSING_DISABLED;
    INTC1.ICCSIH0IRE.BIT.MKCSIH0IRE = _INT_PROCESSING_DISABLED;
    /* Disable CSIH0 operation */
    CSIH0.CTL0 &= (uint8_t) ~_CSIH_RECEPTION_PERMIT;
    CSIH0.CTL0 &= (uint8_t) ~_CSIH_TRANSMISSION_PERMIT;
    CSIH0.CTL0 &= (uint8_t) ~_CSIH_OPERATION_CLOCK_PROVIDE;
    /* Synchronization processing */
    g_cg_sync_read = CSIH0.CTL0;
    __syncp();
    /* Clear CSIH0 interrupt request */
    INTC1.ICCSIH0IC.BIT.RFCSIH0IC = _INT_REQUEST_NOT_OCCUR;
    INTC1.ICCSIH0IR.BIT.RFCSIH0IR = _INT_REQUEST_NOT_OCCUR;
    INTC1.ICCSIH0IRE.BIT.RFCSIH0IRE = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = INTC1.ICCSIH0IC.UINT16;
    __syncp();
}

/***********************************************************************************************************************
* Function Name: R_CSIH1_Create
* Description  : This function initializes the CSIH1 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSIH1_Create(void)
{
    uint32_t tmp_port;

    /* Disable CSIH1 operation */
    CSIH1.CTL0 = _CSIH_OPERATION_CLOCK_STOP;
    /* Disable INTCSIH1IC operation and clear request */
    INTC2.ICCSIH1IC.BIT.MKCSIH1IC = _INT_PROCESSING_DISABLED;
    INTC2.ICCSIH1IC.BIT.RFCSIH1IC = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTCSIH1IR operation and clear request */
    INTC2.ICCSIH1IR.BIT.MKCSIH1IR = _INT_PROCESSING_DISABLED;
    INTC2.ICCSIH1IR.BIT.RFCSIH1IR = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTCSIH1IRE operation and clear request */
    INTC2.ICCSIH1IRE.BIT.MKCSIH1IRE = _INT_PROCESSING_DISABLED;
    INTC2.ICCSIH1IRE.BIT.RFCSIH1IRE = _INT_REQUEST_NOT_OCCUR;
    /* Set CSIH1 interrupt(INTCSIH1IC) setting */
    INTC2.ICCSIH1IC.BIT.TBCSIH1IC = _INT_TABLE_VECTOR;
    INTC2.ICCSIH1IC.UINT16 &= _INT_PRIORITY_LEVEL10;
    /* Set CSIH1 interrupt(INTCSIH1IR) setting */
    INTC2.ICCSIH1IR.BIT.TBCSIH1IR = _INT_TABLE_VECTOR;
    INTC2.ICCSIH1IR.UINT16 &= _INT_PRIORITY_LEVEL10;
    /* Set CSIH1 interrupt(INTCSIH1IRE) setting */
    INTC2.ICCSIH1IRE.BIT.TBCSIH1IRE = _INT_TABLE_VECTOR;
    INTC2.ICCSIH1IRE.UINT16 &= _INT_PRIORITY_LOWEST - 2;
    /* Set CSIH1 control setting */
    CSIH1.CTL1 = _CSIH_INTERRUPT_TIMING_NORMAL | _CSIH_CHIPSELECT0_ACTIVE_LOW  | _CSIH_HALF_CLOCK_DELAY | _CSIH_HANDSHAKE_DISABLE |
                 _CSIH_SLAVE_SELECT_DISABLE | _CSIH_CLOCK_INVERTING_LOW | _CSIH_LOOP_BACK_DEACTIVE;
    CSIH1.CTL2 = _CSIH1_SELECT_BASIC_CLOCK;
    CSIH1.BRS0 = _CSIH1_BAUD_RATE_0;
    CSIH1.BRS1 = _CSIH1_BAUD_RATE_1;
    CSIH1.BRS2 = _CSIH1_BAUD_RATE_2;
    CSIH1.BRS3 = _CSIH1_BAUD_RATE_3;
    /* Set CSIH1 configuration setting */
    CSIH1.CFG1 = _CSIH_USED_BAUDRATE_0 | _CSIH_PARITY_NO | _CSIH_DATA_LENGTH_16 | _CSIH_DATA_DIRECTION_MSB |
                 _CSIHn_MASTER_PHASE_SELECTION_TYPE1 | _CSIH_IDLE_INSERTED_NOT_ALWAYS | _CSIH_IDLE_TIME_0 |
                 _CSIH_HOLD_TIME_0 | _CSIH_INTER_DATA_DELAY_TIME_0 | _CSIH_SETUP_TIME_0;
    CSIH1.MCTL0  = 0x0100U; 		//dual buffer mode
    CSIH1.STCR0 |= 0x0100U;			// clear FIFO pointer
    //	CSIH1.MCTL1 = 0x00000008;    /* Synchronization processing */
    g_cg_sync_read = CSIH1.CTL1;
    __syncp();
    /* Set CSIH1SC pin */
    PORT.PIBC10 &= _PORT_CLEAR_BIT1;
    PORT.PBDC10 &= _PORT_CLEAR_BIT1;
    PORT.PM10 |= _PORT_SET_BIT1;
    PORT.PMC10 &= _PORT_CLEAR_BIT1;
    PORT.PIPC10 &= _PORT_CLEAR_BIT1;
    tmp_port = PORT.PDSC10;
    PORT.PPCMD10 = _WRITE_PROTECT_COMMAND;
    PORT.PDSC10 = (tmp_port | _PORT_SET_BIT1);
    PORT.PDSC10 = (uint32_t) ~(tmp_port | _PORT_SET_BIT1);
    PORT.PDSC10 = (tmp_port | _PORT_SET_BIT1);
    PORT.PFC10 &= _PORT_CLEAR_BIT1;
    PORT.PFCE10 &= _PORT_CLEAR_BIT1;
    PORT.PFCAE10 |= _PORT_SET_BIT1;
    PORT.PIPC10 |= _PORT_SET_BIT1;
    PORT.PMC10 |= _PORT_SET_BIT1;
    /* Set CSIH1SO pin */
    PORT.PIBC10 &= _PORT_CLEAR_BIT2;
    PORT.PBDC10 &= _PORT_CLEAR_BIT2;
    PORT.PM10 |= _PORT_SET_BIT2;
    PORT.PMC10 &= _PORT_CLEAR_BIT2;
    PORT.PIPC10 &= _PORT_CLEAR_BIT2;
    tmp_port = PORT.PDSC10;
    PORT.PPCMD10 = _WRITE_PROTECT_COMMAND;
    PORT.PDSC10 = (tmp_port | _PORT_SET_BIT2);
    PORT.PDSC10 = (uint32_t) ~(tmp_port | _PORT_SET_BIT2);
    PORT.PDSC10 = (tmp_port | _PORT_SET_BIT2);
    PORT.PFC10 &= _PORT_CLEAR_BIT2;
    PORT.PFCE10 &= _PORT_CLEAR_BIT2;
    PORT.PFCAE10 |= _PORT_SET_BIT2;
    PORT.PIPC10 |= _PORT_SET_BIT2;
    PORT.PMC10 |= _PORT_SET_BIT2;
    /* Set CSIH1SI pin */
    PORT.PIBC10 &= _PORT_CLEAR_BIT0;
    PORT.PBDC10 &= _PORT_CLEAR_BIT0;
    PORT.PM10 |= _PORT_SET_BIT0;
    PORT.PMC10 &= _PORT_CLEAR_BIT0;
    PORT.PIPC10 &= _PORT_CLEAR_BIT0;
    PORT.PFC10 &= _PORT_CLEAR_BIT0;
    PORT.PFCE10 &= _PORT_CLEAR_BIT0;
    PORT.PFCAE10 |= _PORT_SET_BIT0;
    PORT.PMC10 |= _PORT_SET_BIT0;
    /* Set CSIH1CSS1 pin */
    //    PORT.PIBC0 &= _PORT_CLEAR_BIT10;
    //    PORT.PBDC0 &= _PORT_CLEAR_BIT10;
    //    PORT.PM0 |= _PORT_SET_BIT10;
    //    PORT.PMC0 &= _PORT_CLEAR_BIT10;
    //    PORT.PFC0 &= _PORT_CLEAR_BIT10;
    //    PORT.PFCE0 &= _PORT_CLEAR_BIT10;
    //    PORT.PFCAE0 &= _PORT_CLEAR_BIT10;
    //    PORT.PMC0 |= _PORT_SET_BIT10;
    //    PORT.PM0 &= _PORT_CLEAR_BIT10;

}
/***********************************************************************************************************************
* Function Name: R_CSIH1_Start
* Description  : This function starts the CSIH1 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSIH1_Start(void)
{
    /* Enable CSIH1 operation */
    CSIH1.CTL0 = _CSIH_OPERATION_CLOCK_PROVIDE | _CSIH_TRANSMISSION_PERMIT | _CSIH_RECEPTION_PERMIT | _CSIH_OPERATION_PROHIBITED;
    /* Clear CSIH1 interrupt request and enable operation */
    INTC2.ICCSIH1IC.BIT.RFCSIH1IC = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICCSIH1IR.BIT.RFCSIH1IR = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICCSIH1IRE.BIT.RFCSIH1IRE = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICCSIH1IC.BIT.MKCSIH1IC = _INT_PROCESSING_ENABLED;
    INTC2.ICCSIH1IR.BIT.MKCSIH1IR = _INT_PROCESSING_ENABLED;
    INTC2.ICCSIH1IRE.BIT.MKCSIH1IRE = _INT_PROCESSING_ENABLED;
}
/***********************************************************************************************************************
* Function Name: R_CSIH1_Stop
* Description  : This function stops the CSIH1 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSIH1_Stop(void)
{
    /* Disable CSIH1 interrupt operation */
    INTC2.ICCSIH1IC.BIT.MKCSIH1IC = _INT_PROCESSING_DISABLED;
    INTC2.ICCSIH1IR.BIT.MKCSIH1IR = _INT_PROCESSING_DISABLED;
    INTC2.ICCSIH1IRE.BIT.MKCSIH1IRE = _INT_PROCESSING_DISABLED;
    /* Disable CSIH1 operation */
    CSIH1.CTL0 &= (uint8_t) ~_CSIH_RECEPTION_PERMIT;
    CSIH1.CTL0 &= (uint8_t) ~_CSIH_TRANSMISSION_PERMIT;
    CSIH1.CTL0 &= (uint8_t) ~_CSIH_OPERATION_CLOCK_PROVIDE;
    /* Synchronization processing */
    g_cg_sync_read = CSIH1.CTL0;
    __syncp();
    /* Clear CSIH1 interrupt request */
    INTC2.ICCSIH1IC.BIT.RFCSIH1IC = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICCSIH1IR.BIT.RFCSIH1IR = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICCSIH1IRE.BIT.RFCSIH1IRE = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = INTC2.ICCSIH1IC.UINT16;
    __syncp();
}

/***********************************************************************************************************************
* Function Name: R_CSIH2_Create
* Description  : This function initializes the CSIH2 module. bandrate = 1.32M
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSIH2_Create(void)
{
    uint32_t tmp_port;

    /* Disable CSIH2 operation */
    CSIH2.CTL0 = _CSIH_OPERATION_CLOCK_STOP;
    /* Disable INTCSIH2IC operation and clear request */
    INTC2.ICCSIH2IC.BIT.MKCSIH2IC = _INT_PROCESSING_DISABLED;
    INTC2.ICCSIH2IC.BIT.RFCSIH2IC = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTCSIH2IR operation and clear request */
    INTC2.ICCSIH2IR.BIT.MKCSIH2IR = _INT_PROCESSING_DISABLED;
    INTC2.ICCSIH2IR.BIT.RFCSIH2IR = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTCSIH2IRE operation and clear request */
    INTC2.ICCSIH2IRE.BIT.MKCSIH2IRE = _INT_PROCESSING_DISABLED;
    INTC2.ICCSIH2IRE.BIT.RFCSIH2IRE = _INT_REQUEST_NOT_OCCUR;
    /* Set CSIH2 interrupt(INTCSIH2IC) setting */
    INTC2.ICCSIH2IC.BIT.TBCSIH2IC = _INT_TABLE_VECTOR;
    INTC2.ICCSIH2IC.UINT16 &= _INT_PRIORITY_LEVEL10;
    /* Set CSIH2 interrupt(INTCSIH2IR) setting */
    INTC2.ICCSIH2IR.BIT.TBCSIH2IR = _INT_TABLE_VECTOR;
    INTC2.ICCSIH2IR.UINT16 &= _INT_PRIORITY_LEVEL10;
    /* Set CSIH2 interrupt(INTCSIH2IRE) setting */
    INTC2.ICCSIH2IRE.BIT.TBCSIH2IRE = _INT_TABLE_VECTOR;
    INTC2.ICCSIH2IRE.UINT16 &= _INT_PRIORITY_LEVEL10;
    /* Set CSIH2 control setting */
    CSIH2.CTL1 = _CSIH_INTERRUPT_TIMING_NORMAL | _CSIH_CHIPSELECT0_ACTIVE_LOW  | _CSIH_HALF_CLOCK_DELAY | _CSIH_HANDSHAKE_DISABLE |
                 _CSIH_SLAVE_SELECT_DISABLE | _CSIH_CLOCK_INVERTING_LOW | _CSIH_LOOP_BACK_DEACTIVE;
    CSIH2.CTL2 = _CSIH2_SELECT_BASIC_CLOCK;
    CSIH2.BRS0 = _CSIH2_BAUD_RATE_0;
    CSIH2.BRS1 = _CSIH2_BAUD_RATE_1;
    CSIH2.BRS2 = _CSIH2_BAUD_RATE_2;
    CSIH2.BRS3 = _CSIH2_BAUD_RATE_3;
    /* Set CSIH2 configuration setting */
    CSIH2.CFG0 = _CSIH_USED_BAUDRATE_0 | _CSIH_PARITY_NO | _CSIH_DATA_LENGTH_16 | _CSIH_DATA_DIRECTION_MSB |
                 _CSIHn_MASTER_PHASE_SELECTION_TYPE1 | _CSIH_IDLE_INSERTED_NOT_ALWAYS | _CSIH_IDLE_TIME_0 |
                 _CSIH_HOLD_TIME_0 | _CSIH_INTER_DATA_DELAY_TIME_0 | _CSIH_SETUP_TIME_0;
    CSIH2.MCTL0  = 0x0100U; 		//dual buffer mode
    CSIH2.STCR0 |= 0x0100U;			// clear FIFO pointer
    //	CSIH2.MCTL1 = 0x00000008;
    /* Synchronization processing */
    g_cg_sync_read = CSIH2.CTL1;
    __syncp();
    /* Set CSIH2SC pin */
    PORT.PIBC11 &= _PORT_CLEAR_BIT3;
    PORT.PBDC11 &= _PORT_CLEAR_BIT3;
    PORT.PM11 |= _PORT_SET_BIT3;
    //   PORT.PM11 &= _PORT_CLEAR_BIT3;
    PORT.PMC11 &= _PORT_CLEAR_BIT3;
    PORT.PIPC11 &= _PORT_CLEAR_BIT3;
    tmp_port = PORT.PDSC11;
    PORT.PPCMD11 = _WRITE_PROTECT_COMMAND;
    PORT.PDSC11 = (tmp_port | _PORT_SET_BIT3);
    PORT.PDSC11 = (uint32_t) ~(tmp_port | _PORT_SET_BIT3);
    PORT.PDSC11 = (tmp_port | _PORT_SET_BIT3);
    PORT.PFC11 &= _PORT_CLEAR_BIT3;
    PORT.PFCE11 &= _PORT_CLEAR_BIT3;
    PORT.PFCAE11 &= _PORT_CLEAR_BIT3;
    PORT.PIPC11 |= _PORT_SET_BIT3;
    PORT.PMC11 |= _PORT_SET_BIT3;

    /* Set CSIH2SO pin */
    PORT.PIBC11 &= _PORT_CLEAR_BIT2;
    PORT.PBDC11 &= _PORT_CLEAR_BIT2;
    PORT.PM11 |= _PORT_SET_BIT2;
    //    PORT.PM11 &= _PORT_CLEAR_BIT2;
    PORT.PMC11 &= _PORT_CLEAR_BIT2;
    PORT.PIPC11 &= _PORT_CLEAR_BIT2;
    tmp_port = PORT.PDSC11;
    PORT.PPCMD11 = _WRITE_PROTECT_COMMAND;
    PORT.PDSC11 = (tmp_port | _PORT_SET_BIT2);
    PORT.PDSC11 = (uint32_t) ~(tmp_port | _PORT_SET_BIT2);
    PORT.PDSC11 = (tmp_port | _PORT_SET_BIT2);
    PORT.PFC11 &= _PORT_CLEAR_BIT2;
    PORT.PFCE11 &= _PORT_CLEAR_BIT2;
    PORT.PFCAE11 &= _PORT_CLEAR_BIT2;
    PORT.PIPC11 |= _PORT_SET_BIT2;
    PORT.PMC11 |= _PORT_SET_BIT2;

    /* Set CSIH2SI pin */
    PORT.PIBC11 &= _PORT_CLEAR_BIT4;
    PORT.PBDC11 &= _PORT_CLEAR_BIT4;
    PORT.PM11 |= _PORT_SET_BIT4;
    PORT.PMC11 &= _PORT_CLEAR_BIT4;
    PORT.PFC11 &= _PORT_CLEAR_BIT4;
    PORT.PFCE11 &= _PORT_CLEAR_BIT4;
    PORT.PMC11 |= _PORT_SET_BIT4;

    /* Set CSIH2CSS0 pin */
    PORT.PIBC9 &= _PORT_CLEAR_BIT0;
    PORT.PBDC9 &= _PORT_CLEAR_BIT0;
    PORT.PM9 |= _PORT_SET_BIT0;
    //    PORT.PM9 &= _PORT_CLEAR_BIT0;
    PORT.PMC9 &= _PORT_CLEAR_BIT0;
    PORT.PFC9 &= _PORT_CLEAR_BIT0;
    PORT.PFCE9 |= _PORT_SET_BIT0;
    PORT.PMC9 |= _PORT_SET_BIT0;
    PORT.PM9 &= _PORT_CLEAR_BIT0;
    //PORT.P11 &= _PORT_Pn1_OUTPUT_LOW;
}
/***********************************************************************************************************************
* Function Name: R_CSIH2_Start
* Description  : This function starts the CSIH2 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSIH2_Start(void)
{
    /* Enable CSIH2 operation */
    //    CSIH2.CTL0 = _CSIH_OPERATION_CLOCK_PROVIDE | _CSIH_TRANSMISSION_PERMIT |
    CSIH2.CTL0 = _CSIH_OPERATION_CLOCK_PROVIDE | _CSIH_TRANSMISSION_PERMIT | _CSIH_RECEPTION_PERMIT | _CSIH_OPERATION_PROHIBITED;
    /* Clear CSIH2 interrupt request and enable operation */
    INTC2.ICCSIH2IC.BIT.RFCSIH2IC = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICCSIH2IR.BIT.RFCSIH2IR = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICCSIH2IRE.BIT.RFCSIH2IRE = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICCSIH2IC.BIT.MKCSIH2IC = _INT_PROCESSING_ENABLED;
    INTC2.ICCSIH2IR.BIT.MKCSIH2IR = _INT_PROCESSING_ENABLED;
    INTC2.ICCSIH2IRE.BIT.MKCSIH2IRE = _INT_PROCESSING_ENABLED;
}
/***********************************************************************************************************************
* Function Name: R_CSIH2_Stop
* Description  : This function stops the CSIH2 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSIH2_Stop(void)
{
    /* Disable CSIH2 interrupt operation */
    INTC2.ICCSIH2IC.BIT.MKCSIH2IC = _INT_PROCESSING_DISABLED;
    INTC2.ICCSIH2IR.BIT.MKCSIH2IR = _INT_PROCESSING_DISABLED;
    INTC2.ICCSIH2IRE.BIT.MKCSIH2IRE = _INT_PROCESSING_DISABLED;
    /* Disable CSIH2 operation */
    CSIH2.CTL0 &= (uint8_t) ~_CSIH_RECEPTION_PERMIT;
    CSIH2.CTL0 &= (uint8_t) ~_CSIH_TRANSMISSION_PERMIT;
    CSIH2.CTL0 &= (uint8_t) ~_CSIH_OPERATION_CLOCK_PROVIDE;
    /* Synchronization processing */
    g_cg_sync_read = CSIH2.CTL0;
    __syncp();
    /* Clear CSIH2 interrupt request */
    INTC2.ICCSIH2IC.BIT.RFCSIH2IC = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICCSIH2IR.BIT.RFCSIH2IR = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICCSIH2IRE.BIT.RFCSIH2IRE = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = INTC2.ICCSIH2IC.UINT16;
    __syncp();
}

/***********************************************************************************************************************
* Function Name: R_CSIH3_Create
* Description  : This function initializes the CSIH3 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSIH3_Create(void)
{
    uint32_t tmp_port;

    /* Disable CSIH3 operation */
    CSIH3.CTL0 = _CSIH_OPERATION_CLOCK_STOP;
    /* Disable INTCSIH3IC operation and clear request */
    INTC2.ICCSIH3IC.BIT.MKCSIH3IC = _INT_PROCESSING_DISABLED;
    INTC2.ICCSIH3IC.BIT.RFCSIH3IC = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTCSIH3IR operation and clear request */
    INTC2.ICCSIH3IR.BIT.MKCSIH3IR = _INT_PROCESSING_DISABLED;
    INTC2.ICCSIH3IR.BIT.RFCSIH3IR = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTCSIH3IRE operation and clear request */
    INTC2.ICCSIH3IRE.BIT.MKCSIH3IRE = _INT_PROCESSING_DISABLED;
    INTC2.ICCSIH3IRE.BIT.RFCSIH3IRE = _INT_REQUEST_NOT_OCCUR;
    /* Set CSIH3 interrupt(INTCSIH3IC) setting */
    INTC2.ICCSIH3IC.BIT.TBCSIH3IC = _INT_TABLE_VECTOR;
    INTC2.ICCSIH3IC.UINT16 &= _INT_PRIORITY_LEVEL12;
    /* Set CSIH3 interrupt(INTCSIH3IR) setting */
    INTC2.ICCSIH3IR.BIT.TBCSIH3IR = _INT_TABLE_VECTOR;
    INTC2.ICCSIH3IR.UINT16 &= _INT_PRIORITY_LEVEL12;
    /* Set CSIH3 interrupt(INTCSIH3IRE) setting */
    INTC2.ICCSIH3IRE.BIT.TBCSIH3IRE = _INT_PRIORITY_LEVEL12;
    INTC2.ICCSIH3IRE.UINT16 &= _INT_PRIORITY_LOWEST;
    /* Set CSIH3 control setting */
    CSIH3.CTL1 = _CSIH_CLOCK_INVERTING_LOW | _CSIH_INTERRUPT_TIMING_NORMAL | _CSIH_CHIPSELECT3_ACTIVE_LOW | _CSIH_DATA_CONSISTENCY_CHECK_DISABLE |
                 _CSIH_CHIPSELECT_SIGNAL_HOLD_ACTIVE | _CSIH_NO_DELAY | _CSIH_HANDSHAKE_DISABLE |
                 _CSIH_SLAVE_SELECT_DISABLE;
    CSIH3.CTL2 = _CSIH3_SELECT_BASIC_CLOCK;
    CSIH3.BRS0 = _CSIH3_BAUD_RATE_0;
    CSIH3.BRS1 = _CSIH3_BAUD_RATE_1;
    CSIH3.BRS2 = _CSIH3_BAUD_RATE_2;
    CSIH3.BRS3 = _CSIH3_BAUD_RATE_3;
    /* Set CSIH3 configuration setting */
    CSIH3.CFG3 = _CSIH_USED_BAUDRATE_0 | _CSIH_PARITY_NO | _CSIH_DATA_LENGTH_16 | _CSIH_DATA_DIRECTION_MSB |
                 _CSIHn_MASTER_PHASE_SELECTION_TYPE2 | _CSIH_IDLE_INSERTED_NOT_ALWAYS | _CSIH_IDLE_TIME_0 |
                 _CSIH_HOLD_TIME_0 | _CSIH_INTER_DATA_DELAY_TIME_0 | _CSIH_SETUP_TIME_0;
    CSIH3.MCTL0  = 0x0100U; 		//dual buffer mode
    CSIH3.STCR0 |= 0x0100U;			// clear FIFO pointer
    /* Synchronization processing */
    g_cg_sync_read = CSIH3.CTL1;
    __syncp();
    /* Set CSIH3SC pin */
    PORT.PIBC11 &= _PORT_CLEAR_BIT7;
    PORT.PBDC11 &= _PORT_CLEAR_BIT7;
    PORT.PM11 |= _PORT_SET_BIT7;
    PORT.PMC11 &= _PORT_CLEAR_BIT7;
    PORT.PIPC11 &= _PORT_CLEAR_BIT7;
    tmp_port = PORT.PDSC11;
    PORT.PPCMD11 = _WRITE_PROTECT_COMMAND;
    PORT.PDSC11 = (tmp_port | _PORT_SET_BIT7);
    PORT.PDSC11 = (uint32_t) ~(tmp_port | _PORT_SET_BIT7);
    PORT.PDSC11 = (tmp_port | _PORT_SET_BIT7);
    PORT.PFC11 &= _PORT_CLEAR_BIT7;
    PORT.PFCE11 |= _PORT_SET_BIT7;
    PORT.PIPC11 |= _PORT_SET_BIT7;
    PORT.PMC11 |= _PORT_SET_BIT7;
    /* Set CSIH3SO pin */
    PORT.PIBC11 &= _PORT_CLEAR_BIT6;
    PORT.PBDC11 &= _PORT_CLEAR_BIT6;
    PORT.PM11 |= _PORT_SET_BIT6;
    PORT.PMC11 &= _PORT_CLEAR_BIT6;
    PORT.PIPC11 &= _PORT_CLEAR_BIT6;
    tmp_port = PORT.PDSC11;
    PORT.PPCMD11 = _WRITE_PROTECT_COMMAND;
    PORT.PDSC11 = (tmp_port | _PORT_SET_BIT6);
    PORT.PDSC11 = (uint32_t) ~(tmp_port | _PORT_SET_BIT6);
    PORT.PDSC11 = (tmp_port | _PORT_SET_BIT6);
    PORT.PFC11 &= _PORT_CLEAR_BIT6;
    PORT.PFCE11 |= _PORT_SET_BIT6;
    PORT.PFCAE11 &= _PORT_CLEAR_BIT6;
    PORT.PIPC11 |= _PORT_SET_BIT6;
    PORT.PMC11 |= _PORT_SET_BIT6;
    /* Set CSIH3SI pin */
    PORT.PIBC11 &= _PORT_CLEAR_BIT5;
    PORT.PBDC11 &= _PORT_CLEAR_BIT5;
    PORT.PM11 |= _PORT_SET_BIT5;
    PORT.PMC11 &= _PORT_CLEAR_BIT5;
    PORT.PFC11 &= _PORT_CLEAR_BIT5;
    PORT.PFCE11 |= _PORT_SET_BIT5;
    PORT.PFCAE11 &= _PORT_CLEAR_BIT5;
    PORT.PMC11 |= _PORT_SET_BIT5;
    /* Set CSIH3CSS3 pin */
    PORT.PIBC8 &= _PORT_CLEAR_BIT10;
    PORT.PBDC8 &= _PORT_CLEAR_BIT10;
    PORT.PM8 |= _PORT_SET_BIT10;
    PORT.PMC8 &= _PORT_CLEAR_BIT10;
    PORT.PFC8 &= _PORT_CLEAR_BIT10;
    PORT.PMC8 |= _PORT_SET_BIT10;
    PORT.PM8 &= _PORT_CLEAR_BIT10;

}
/***********************************************************************************************************************
* Function Name: R_CSIH3_Start
* Description  : This function starts the CSIH3 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSIH3_Start(void)
{
    /* Enable CSIH3 operation */
    CSIH3.CTL0 = _CSIH_OPERATION_CLOCK_PROVIDE | _CSIH_TRANSMISSION_PERMIT | _CSIH_RECEPTION_PERMIT |
                 _CSIH_OPERATION_PROHIBITED;
    g_cg_sync_read = CSIH3.CTL0;
    __syncp();
    /* Clear CSIH3 interrupt request and enable operation */
    INTC2.ICCSIH3IC.BIT.RFCSIH3IC = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICCSIH3IR.BIT.RFCSIH3IR = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICCSIH3IRE.BIT.RFCSIH3IRE = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICCSIH3IC.BIT.MKCSIH3IC = _INT_PROCESSING_ENABLED;
    INTC2.ICCSIH3IR.BIT.MKCSIH3IR = _INT_PROCESSING_ENABLED;
    INTC2.ICCSIH3IRE.BIT.MKCSIH3IRE = _INT_PROCESSING_ENABLED;
    g_cg_sync_read = INTC2.ICCSIH3IC.UINT16;
    __syncp();
}
/***********************************************************************************************************************
* Function Name: R_CSIH3_Stop
* Description  : This function stops the CSIH3 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSIH3_Stop(void)
{
    /* Disable CSIH3 interrupt operation */
    INTC2.ICCSIH3IC.BIT.MKCSIH3IC = _INT_PROCESSING_DISABLED;
    INTC2.ICCSIH3IR.BIT.MKCSIH3IR = _INT_PROCESSING_DISABLED;
    INTC2.ICCSIH3IRE.BIT.MKCSIH3IRE = _INT_PROCESSING_DISABLED;
    /* Disable CSIH3 operation */
    CSIH3.CTL0 &= (uint8_t) ~_CSIH_RECEPTION_PERMIT;
    CSIH3.CTL0 &= (uint8_t) ~_CSIH_TRANSMISSION_PERMIT;
    CSIH3.CTL0 &= (uint8_t) ~_CSIH_OPERATION_CLOCK_PROVIDE;
    /* Synchronization processing */
    g_cg_sync_read = CSIH3.CTL0;
    __syncp();
    /* Clear CSIH3 interrupt request */
    INTC2.ICCSIH3IC.BIT.RFCSIH3IC = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICCSIH3IR.BIT.RFCSIH3IR = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICCSIH3IRE.BIT.RFCSIH3IRE = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = INTC2.ICCSIH3IC.UINT16;
    __syncp();
}

/* Start user code for adding. Do not edit comment generated here */
MD_STATUS CSIH3_Master_Send(unsigned short *transmit_data, unsigned short transmit_length)
{
    unsigned short i;
    CSIH3.CTL0 |= 0x40U;        /* start CSIH2                             */
    CSIH3.STCR0 |= 0x0100U;    /* clear buffer pointer                    */
    CSIH3.MCTL2 = (0x00000000UL | (transmit_length << 16));  /* set transmit size   */
    for (i = 0; i < transmit_length; i++)
    {
        /* setup frame data to TX buffer */
        CSIH3.TX0W = (0x00000000 | transmit_data[i]);
    }
    CSIH3.MCTL2 |= 0x80000000UL; /* transfer start by setting the BTST bit*/
    return 0;
}



/**
 * CSIHnCFG0.CSIHnDLS0[3:0] = 8D
 * (CSIHnTX0W.CSIHnEDL = 0)
 *
 */
//uint8_t rddata[3];

MD_STATUS CSIH3_Master_Send3(uint8_t *data, uint8_t *rddata)
{
    //1611 1665

    //  uint8_t data[3] = {0x09, 0x00, 0x57};
#ifndef    Send3

    uint16_t data1 = (data[0] << 8) | data[1];
    uint8_t data2 = data[2];
    uint32_t rddata1;

    uint16_t timeout = 1000;

    CSIH3.CTL0 |= 0x40U;        /* start CSIH3       Enables transmission. */
    CSIH3.CTL1 |= 0x00000080; //EDL function is enabled ;CSIHnCSLx 0: Chip select is active low.

    CSIH3.MCTL2 = (0x00000000UL | (2 << 16));  /* set transmit size   */

    CSIH3.MCTL2 |= 0x80000000UL; /* transfer start by setting the BTST bit*/

    CSIH3.CFG3 &= 0xF0FFFFFF;
    //    CSIH3.CFG3 |=_CSIH_DATA_LENGTH_16;
    //    CSIH3.TX0W = (0x20000000 | 0x1234);
    CSIH3.CFG3 &= 0xF0FFFFFF;
    CSIH3.CFG3 |= _CSIH_DATA_LENGTH_8;
    CSIH3.TX0W = (0x20F70000 | data1); //CSIHnEDL Enables the extended data length.
    while(timeout)
    {
        timeout--;
    }
    rddata1 = CSIH3.RX0W;
    rddata[0] = (rddata1 >> 8) & 0xFF;
    rddata[1] = (rddata1 >> 0) & 0xFF;
    CSIH3.TX0W = (0x00F70000 | data2);
    timeout = 500;
    while(timeout)
    {
        timeout--;
    }
    rddata1 = CSIH3.RX0W;
    rddata[2] = (rddata1 >> 0) & 0xFF;

    CSIH3.STCR0 |= 0x0100U;    /* clear buffer pointer                    */
    return 0;
#else
    uint16_t data1 = (data[0] << 8) | data[1];
    uint8_t data2 = data[2];
    //uint16_t timeout = 1000;
    CSIH3.CTL0 |= 0x40U;        /* start CSIH3       Enables transmission. */
    CSIH3.CTL1 |= 0x00000080; //EDL function is enabled ;CSIHnCSLx 0: Chip select is active low.
    CSIH3.MCTL2 = (0x00000000UL | (2 << 16));  /* set transmit size   */
    CSIH3.MCTL2 |= 0x80000000UL;   /* transfer start by setting the BTST bit*/
    CSIH3.CFG3 &= 0xF0FFFFFF;
    g_send_end = 0;
    CSIH3.TX0W = (0x20F70000 | data1); //CSIHnEDL Enables the extended data length.
    //	timeout = 1000;
    //	while(timeout)
    //	{
    //	timeout--;
    //	}
    CSIH3.CFG3 &= 0xF0FFFFFF;
    CSIH3.CFG3 |= _CSIH_DATA_LENGTH_8;
    CSIH3.TX0W = (0x00F70000 | data2);
    rddata1 = CSIH3.RX0W;
    rddata[0] = (rddata1 >> 8) & 0xFF;
    rddata[1] = (rddata1 >> 0) & 0xFF;
    timeout = 500;
    while((timeout) && (g_send_end == 0))
        //while(timeout)
    {
        timeout--;
    }
    //rddata2 = CSIH3.RX0W;
    rddata[2] = (rddata2 >> 0) & 0xFF;

    // CSIH3.STCR0 |= 0x0100U;    /* clear buffer pointer                    */

    return 0;
#endif
}

/* End user code. Do not edit comment generated here */
