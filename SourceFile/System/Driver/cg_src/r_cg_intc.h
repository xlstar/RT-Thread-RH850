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
* File Name    : r_cg_intc.h
* Version      : Code Generator for RH850/F1K V1.01.02.02 [08 May 2018]
* Device(s)    : R7F701581(LQFP100pin)
* Tool-Chain   : CCRH
* Description  : This file implements device driver for INTC module.
* Creation Date: 2022/3/11
***********************************************************************************************************************/
#ifndef INTC_H
#define INTC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Filter Control Register (FCLA0CTLm_<name>)
*/
/* NMI/INTPn interrupt detecting method select (FCLA0INTLm_<name>,FCLA0INTFm_<name>,FCLA0INTRm_<name> */
#define _INTC_EDGE_RISING                          (0x01U) /* Rising edge detection */
#define _INTC_EDGE_FALLING                         (0x02U) /* Falling edge detection */
#define _INTC_EDGE_BOTH                            (0x03U) /* Both edges detection */
#define _INTC_LEVEL_LOW                            (0x04U) /* Low level detection */
#define _INTC_LEVEL_HIGH                           (0x05U) /* High level detection */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
extern void R_INTC_Create(void);
extern void R_INTP0_Start(void);
extern void R_INTP0_Stop(void);
extern void R_INTP1_Start(void);
extern void R_INTP1_Stop(void);
extern void R_INTP2_Start(void);
extern void R_INTP2_Stop(void);
extern void R_INTP3_Start(void);
extern void R_INTP3_Stop(void);
extern void R_INTP4_Start(void);
extern void R_INTP4_Stop(void);
extern void R_INTP5_Start(void);
extern void R_INTP5_Stop(void);
extern void R_INTP6_Start(void);
extern void R_INTP6_Stop(void);
extern void R_INTP10_Start(void);
extern void R_INTP10_Stop(void);
extern void R_INTP11_Start(void);
extern void R_INTP11_Stop(void);


/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
