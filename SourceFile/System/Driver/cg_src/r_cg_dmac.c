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
* File Name    : r_cg_dmac.c
* Version      :
* Device(s)    : R7F701587(LQFP176pin)
* Tool-Chain   : CCRH
* Description  : This file implements device driver for DMA module.
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
#include "r_cg_dmac.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t g_cg_sync_read;
extern volatile uint32_t g_cg_sync_read;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_DMAC1_Create
* Description  : This function initializes the DMAC1 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC1_Create(void)
{
    R_DMAC10_Create();
}
/***********************************************************************************************************************
* Function Name: R_DMAC_Suspend
* Description  : This function Suspends the DMAC module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC_Suspend(void)
{
    //  DMAC.TL = _DMAC_SUSPEND_REQUEST;
}
/***********************************************************************************************************************
* Function Name: R_DMAC_Resume
* Description  : This function Resumes the DMAC module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC_Resume(void)
{
    // DMAC.TL = _DMAC_SUSPEND_CLEARED;
}
/***********************************************************************************************************************
* Function Name: R_DMAC10_Create
* Description  : This function initializes DMAC10 channel.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC10_Create(void)
{
    //    /* Disable DMAC10 operation */
    //    DMAC.DCEN8 = _DMAC_CHANNEL_OPERATION_DISABLED;
    //    /* Disable DMAC10 operation and clear request */
    //    INTC2.ICDMA8.BIT.MKDMA8 = _INT_PROCESSING_DISABLED;
    //    INTC2.ICDMA8.BIT.RFDMA8 = _INT_REQUEST_NOT_OCCUR;
    //    /* Set DMAC10 interrupt setting */
    //    INTC2.ICDMA8.BIT.TBDMA8 = _INT_TABLE_VECTOR;
    //    INTC2.ICDMA8.UINT16 &= _INT_PRIORITY_LOWEST - 2U;
    //    /* Set DMAC10 global setting */
    //    DMAC.DM10CM = _DMAC_PE1_SETTING | _DMAC_SPID1_SETTING | _DMAC_SUPERVISON_MODE;
    //    /* Set DMAC10 transfer setting */
    //    DMAC.DSA8 = _DMAC8_SOURCE_ADDRESS;
    //    DMAC.DDA8 = _DMAC8_DESTINATION_ADDRESS;
    //    DMAC.DTC8 = _DMAC8_ADDRESS_RELOAD_COUNT | _DMAC8_TRANSFER_COUNT;
    //    DMAC.DTCT8 = _DMAC_CYCLES_EXECUTED | _DMAC_TRANSFER_SOFTWARE | _DMAC_CHAIN_DISABLE |
    //                 _DMAC_TRANSFER_COMPLETION_INTERRUPT_ENABLE | _DMAC_CONTINUOUS_TRANSFER_ENABLE |
    //                 _DMAC_RELOAD2_DISABLE | _DMAC_RELOAD1_DISABLE | _DMAC_DESTINATION_INCREMENT |
    //                 _DMAC_SOURCE_INCREMENT | _DMAC_TRANSFER_DATA_8BITS | _DMAC_SINGLE_TRANSFER;
    //    DMAC.DTFR8 = _DMAC_HARDWARE_TRIGGER_DISABLE;
    //    /* Synchronization processing */
    //    g_cg_sync_read = DMAC.DTCT8;
    //    __syncp();
}
/***********************************************************************************************************************
* Function Name: R_DMAC10_Start
* Description  : This function enable DMAC10 activation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC10_Start(void)
{
    /* Clear DMAC10 request and enable operation */
    INTC2.ICDMA8.BIT.RFDMA8 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICDMA8.BIT.MKDMA8 = _INT_PROCESSING_ENABLED;
    /* Enable DMAC10 operation */
    //   DMAC.DCEN8 = _DMAC_CHANNEL_OPERATION_ENABLED;
}
/***********************************************************************************************************************
* Function Name: R_DMAC10_Stop
* Description  : This function disable DMAC10 activation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC10_Stop(void)
{
    //    /* Disable DMAC10 operation */
    //    DMAC.DCEN8 = _DMAC_CHANNEL_OPERATION_DISABLED;
    //    /* Disable DMAC10 operation and clear request */
    //    INTC2.ICDMA8.BIT.MKDMA8 = _INT_PROCESSING_DISABLED;
    //    INTC2.ICDMA8.BIT.RFDMA8 = _INT_REQUEST_NOT_OCCUR;
    //    /* Synchronization processing */
    //    g_cg_sync_read = DMAC.DCEN8;
    //    __syncp();
}
/***********************************************************************************************************************
* Function Name: R_DMAC10_Set_SoftwareTrigger
* Description  : This function set DMAC10 software trigger.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC10_Set_SoftwareTrigger(void)
{
    /* Set DMAC10 software trigger */
    // DMAC.DCSTS8 = _DMAC_SET_REQUEST_FLAG;
}
/***********************************************************************************************************************
* Function Name: R_DMAC10_Suspend
* Description  : This function Suspends DMAC10 channel operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC10_Suspend(void)
{
    /* Enable DMAC10 operation */
    //  DMAC.DCEN8 = _DMAC_CHANNEL_OPERATION_DISABLED;
}
/***********************************************************************************************************************
* Function Name: R_DMAC10_Resume
* Description  : This function Resumes DMAC10 channel operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC10_Resume(void)
{
    /* Disable DMAC10 operation */
    //   DMAC.DCEN8 = _DMAC_CHANNEL_OPERATION_ENABLED;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
