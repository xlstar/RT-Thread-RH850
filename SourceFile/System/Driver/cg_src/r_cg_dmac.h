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
* File Name    : r_cg_dmac.h
* Version      :
* Device(s)    : R7F701587(LQFP176pin)
* Tool-Chain   : CCRH
* Description  : This file implements device driver for DMA module.
* Creation Date: 2018/6/12
***********************************************************************************************************************/
#ifndef DMA_H
#define DMA_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/*
    DMAC channel operation enable setting register n (DCENn)
*/
/* Channel operation enable (DTE) */
#define _DMAC_CHANNEL_OPERATION_DISABLED                    (0x00000000U) /* Channel is disabled/suspended */
#define _DMAC_CHANNEL_OPERATION_ENABLED                     (0x00000001U) /* Channel is enabled/suspension cleared */

/*
    DMAC Transfer Control Register n (DTCTn)
*/
/* Transfer error case DMA transfer disable setting (ESE) */
#define _DMAC_CYCLES_EXECUTED                               (0x00000000U) /* DMA cycles are executed */
#define _DMAC_CYCLES_NOT_EXECUTED                           (0x08000000U) /* DMA cycles are not executed */
/* DMA transfer request selection assignment (DRS) */
#define _DMAC_TRANSFER_SOFTWARE                             (0x00000000U) /* Software DMA transfer request */
#define _DMAC_TRANSFER_HARDWARE                             (0x04000000U) /* Hardware DMA transfer request */
/* Next channel in the chain (CHNSEL[2-0]) */
#define _DMAC_SELECT_CHAIN_0                                (0x00000000U) /* chain 0 */
#define _DMAC_SELECT_CHAIN_1                                (0x00040000U) /* chain 1 */
#define _DMAC_SELECT_CHAIN_2                                (0x00080000U) /* chain 2 */
#define _DMAC_SELECT_CHAIN_3                                (0x000C0000U) /* chain 3 */
#define _DMAC_SELECT_CHAIN_4                                (0x00100000U) /* chain 4 */
#define _DMAC_SELECT_CHAIN_5                                (0x00140000U) /* chain 5 */
#define _DMAC_SELECT_CHAIN_6                                (0x00180000U) /* chain 6 */
#define _DMAC_SELECT_CHAIN_7                                (0x001C0000U) /* chain 7 */
/* Chain enable (CHNEL[1-0]) */
#define _DMAC_CHAIN_DISABLE                                 (0x00000000U) /* chain function disabled */
#define _DMAC_CHAIN_LAST_TRANFER                            (0x00010000U) /* Chain at the last transfer */
#define _DMAC_ALWAYS_CHAIN                                  (0x00030000U) /* Always chain */
/* Transfer count match interrupt enable (CCE) */
#define _DMAC_TRANSFER_COUNT_INTERRUPT_DISABLE              (0x00000000U) /* Transfer count match interrupt disable */
#define _DMAC_TRANSFER_COUNT_INTERRUPT_ENABLE               (0x00008000U) /* Transfer count match interrupt enable */
/* Transfer completion interrupt enable (TCE) */
#define _DMAC_TRANSFER_COMPLETION_INTERRUPT_DISABLE         (0x00000000U) /* Transfer completion interrupt disable */
#define _DMAC_TRANSFER_COMPLETION_INTERRUPT_ENABLE          (0x00004000U) /* Transfer completion interrupt enable */
/* Continuous transfer enable (MLE) */
#define _DMAC_CONTINUOUS_TRANSFER_ENABLE                    (0x00002000U) /* DTE bit is cleared */
#define _DMAC_CONTINUOUS_TRANSFER_DISABLE                   (0x00000000U) /* DTE bit is not cleared */
/* Reload function 2 setting (RLD2M[1-0]) */
#define _DMAC_RELOAD2_DISABLE                               (0x00000000U) /* Reload function 2 is disabled */
#define _DMAC_RELOAD2_SOURCE_CONTROL                        (0x00000800U) /* Reload function 2 is enabled source */
#define _DMAC_RELOAD2_DESTINATION_CONTROL                   (0x00001000U) /* Reload function 2 is enabled destination */
#define _DMAC_RELOAD2_ALL_CONTROL                           (0x00001800U) /* Reload function 2 is enabled all */
/* Reload function 1 setting (RLD1M[1-0]) */
#define _DMAC_RELOAD1_DISABLE                               (0x00000000U) /* Reload function 1 is disabled */
#define _DMAC_RELOAD1_SOURCE_CONTROL                        (0x00000200U) /* Reload function 1 is enabled source */
#define _DMAC_RELOAD1_DESTINATION_CONTROL                   (0x00000400U) /* Reload function 1 is enabled destination */
#define _DMAC_RELOAD1_ALL_CONTROL                           (0x00000600U) /* Reload function 1 is enabled all */
/* Destination address count direction (DACM[1-0]) */
#define _DMAC_DESTINATION_INCREMENT                         (0x00000000U) /* Increment mode */
#define _DMAC_DESTINATION_DECREMENT                         (0x00000080U) /* Decrement mode */
#define _DMAC_DESTINATION_FIXED                             (0x00000100U) /* fixed */
/* Source address count direction (SACM[1-0]) */
#define _DMAC_SOURCE_INCREMENT                              (0x00000000U) /* Increment mode */
#define _DMAC_SOURCE_DECREMENT                              (0x00000020U) /* Decrement mode */
#define _DMAC_SOURCE_FIXED                                  (0x00000040U) /* fixed */
/* Transfer data size (DS[2-0]) */
#define _DMAC_TRANSFER_DATA_8BITS                           (0x00000000U) /* transfer data size 8 bits */
#define _DMAC_TRANSFER_DATA_16BITS                          (0x00000004U) /* transfer data size 16 bits */
#define _DMAC_TRANSFER_DATA_32BITS                          (0x00000008U) /* transfer data size 32 bits */
#define _DMAC_TRANSFER_DATA_64BITS                          (0x0000000CU) /* transfer data size 64 bits */
#define _DMAC_TRANSFER_DATA_128BITS                         (0x00000010U) /* transfer data size 128 bits */
/* Transfer mode (TRM[1-0]) */
#define _DMAC_SINGLE_TRANSFER                               (0x00000000U) /* Single transfer */
#define _DMAC_BOLCK_TRANSFER_1                              (0x00000001U) /* Block transfer 1 */
#define _DMAC_BOLCK_TRANSFER_2                              (0x00000002U) /* Block transfer 2 */

/*
    DMAC transfer status set register n (DCSTSn)
*/
/* Software DMA transfer request flag (SRS) */
#define _DMAC_READ_THIS_BIT                                 (0x00000000U) /* always read from this bit */
#define _DMAC_SET_REQUEST_FLAG                              (0x00000001U) /* Set DMACnm software trigger */

/*
    DTFR setting register n (DTFRn)
*/
/* Hardware DMA transfer source selection enable (REQEN) */
#define _DMAC_HARDWARE_TRIGGER_DISABLE                      (0x00000000U) /* Hardware transfer source is disabled */
#define _DMAC_HARDWARE_TRIGGER_ENABLE                       (0x00000001U) /* Hardware transfer source is enabled */
/* Hardware setting (REQSEL[6-0]) */
#define _DMAC_TRIGGER_SOURCE_0                              (0x00000000U) /* INTTAUD0I0 */
#define _DMAC_TRIGGER_SOURCE_1                              (0x00000002U) /* INTTAUD0I4 */
#define _DMAC_TRIGGER_SOURCE_2                              (0x00000004U) /* INTTAUD0I8 */
#define _DMAC_TRIGGER_SOURCE_3                              (0x00000006U) /* INTTAUD0I12 */
#define _DMAC_TRIGGER_SOURCE_4                              (0x00000008U) /* INTTAUD0I12 */
#define _DMAC_TRIGGER_SOURCE_5                              (0x0000000AU) /* INTADCA0I1 */
#define _DMAC_TRIGGER_SOURCE_6                              (0x0000000CU) /* INTADCA0I2 */
#define _DMAC_TRIGGER_SOURCE_7                              (0x0000000EU) /* ADC_CONV_END0 */
#define _DMAC_TRIGGER_SOURCE_8                              (0x00000010U) /* INTCSIG0IC */
#define _DMAC_TRIGGER_SOURCE_9                              (0x00000012U) /* INTCSIG0IR */
#define _DMAC_TRIGGER_SOURCE_10                             (0x00000014U) /* INTRLIN30UR0 */
#define _DMAC_TRIGGER_SOURCE_11                             (0x00000016U) /* INTRLIN30UR1 */
#define _DMAC_TRIGGER_SOURCE_12                             (0x00000018U) /* INTP0 */
#define _DMAC_TRIGGER_SOURCE_13                             (0x0000001AU) /* INTP2 */
#define _DMAC_TRIGGER_SOURCE_14                             (0x0000001CU) /* INTP4 */
#define _DMAC_TRIGGER_SOURCE_15                             (0x0000001EU) /* INTTAUD0I1 */
#define _DMAC_TRIGGER_SOURCE_16                             (0x00000020U) /* INTTAUD0I5 */
#define _DMAC_TRIGGER_SOURCE_17                             (0x00000022U) /* INTTAUD0I9 */
#define _DMAC_TRIGGER_SOURCE_18                             (0x00000024U) /* INTTAUD0I13 */
#define _DMAC_TRIGGER_SOURCE_19                             (0x00000026U) /* INTRIIC0TI */
#define _DMAC_TRIGGER_SOURCE_20                             (0x00000028U) /* INTRIIC0RI */
#define _DMAC_TRIGGER_SOURCE_21                             (0x0000002AU) /* INTTAUJ0I0 */
#define _DMAC_TRIGGER_SOURCE_22                             (0x0000002CU) /* INTTAUJ0I3 */
#define _DMAC_TRIGGER_SOURCE_23                             (0x0000002EU) /* RSCANFDCF0*1 */
#define _DMAC_TRIGGER_SOURCE_24                             (0x00000030U) /* RSCANFDCF1*1 */
#define _DMAC_TRIGGER_SOURCE_26                             (0x00000034U) /* RSCANFDCF2*1 */
#define _DMAC_TRIGGER_SOURCE_27                             (0x00000036U) /* RSCANFDCF3*1 */
#define _DMAC_TRIGGER_SOURCE_28                             (0x00000038U) /* INTCSIH1IC */
#define _DMAC_TRIGGER_SOURCE_29                             (0x0000003AU) /* INTCSIH1IR */
#define _DMAC_TRIGGER_SOURCE_30                             (0x0000003CU) /* INTCSIH1IJC */
#define _DMAC_TRIGGER_SOURCE_31                             (0x0000003EU) /* INTP6 */
#define _DMAC_TRIGGER_SOURCE_32                             (0x00000040U) /* INTP8 */
#define _DMAC_TRIGGER_SOURCE_33                             (0x00000042U) /* INTTAUB0I0 */
#define _DMAC_TRIGGER_SOURCE_34                             (0x00000044U) /* INTTAUB0I2 */
#define _DMAC_TRIGGER_SOURCE_35                             (0x00000046U) /* INTTAUB0I4 */
#define _DMAC_TRIGGER_SOURCE_36                             (0x00000048U) /* INTTAUB0I6 */
#define _DMAC_TRIGGER_SOURCE_37                             (0x0000004AU) /* INTTAUB0I9 */
#define _DMAC_TRIGGER_SOURCE_38                             (0x0000004CU) /* INTTAUB0I11 */
#define _DMAC_TRIGGER_SOURCE_39                             (0x0000004EU) /* INTTAUB0I13 */
#define _DMAC_TRIGGER_SOURCE_40                             (0x00000050U) /* INTTAUB0I15 */
#define _DMAC_TRIGGER_SOURCE_41                             (0x00000052U) /* INTCSIH3IC */
#define _DMAC_TRIGGER_SOURCE_42                             (0x00000054U) /* INTCSIH3IR */
#define _DMAC_TRIGGER_SOURCE_43                             (0x00000056U) /* INTCSIH3IJC */
#define _DMAC_TRIGGER_SOURCE_44                             (0x00000058U) /* INTRLIN32UR0 */
#define _DMAC_TRIGGER_SOURCE_45                             (0x0000005AU) /* INTRLIN32UR1 */
#define _DMAC_TRIGGER_SOURCE_46                             (0x0000005CU) /* INTTAUJ1I0 */
#define _DMAC_TRIGGER_SOURCE_47                             (0x0000005EU) /* INTTAUJ1I2 */
#define _DMAC_TRIGGER_SOURCE_48                             (0x00000060U) /* RSCANFDCF4*1 */
#define _DMAC_TRIGGER_SOURCE_49                             (0x00000062U) /* RSCANFDCF5*1 */
#define _DMAC_TRIGGER_SOURCE_50                             (0x00000064U) /* INTRLIN34UR0 */
#define _DMAC_TRIGGER_SOURCE_51                             (0x00000066U) /* INTRLIN34UR1 */
#define _DMAC_TRIGGER_SOURCE_52                             (0x00000068U) /* INTTAUB1I0 */
#define _DMAC_TRIGGER_SOURCE_53                             (0x0000006AU) /* INTTAUB1I2 */
#define _DMAC_TRIGGER_SOURCE_54                             (0x0000006CU) /* INTTAUB1I4 */
#define _DMAC_TRIGGER_SOURCE_55                             (0x0000006EU) /* INTTAUB1I6 */
#define _DMAC_TRIGGER_SOURCE_56                             (0x00000070U) /* INTTAUB1I9 */
#define _DMAC_TRIGGER_SOURCE_57                             (0x00000072U) /* INTTAUB1I11 */
#define _DMAC_TRIGGER_SOURCE_58                             (0x00000074U) /* INTTAUB1I13 */
#define _DMAC_TRIGGER_SOURCE_59                             (0x00000076U) /* INTTAUB1I15 */
#define _DMAC_TRIGGER_SOURCE_60                             (0x00000078U) /* RSCANFDRF0*1 */
#define _DMAC_TRIGGER_SOURCE_61                             (0x0000007AU) /* RSCANFDRF1*1 */
#define _DMAC_TRIGGER_SOURCE_62                             (0x0000007CU) /* RSCANFDRF2*1 */
#define _DMAC_TRIGGER_SOURCE_63                             (0x0000007EU) /* RSCANFDRF3*1 */
#define _DMAC_TRIGGER_SOURCE_64                             (0x00000080U) /* INTTAUD0I2 */
#define _DMAC_TRIGGER_SOURCE_65                             (0x00000082U) /* INTTAUD0I6 */
#define _DMAC_TRIGGER_SOURCE_66                             (0x00000084U) /* INTTAUD0I10 */
#define _DMAC_TRIGGER_SOURCE_67                             (0x00000086U) /* INTTAUD0I14 */
#define _DMAC_TRIGGER_SOURCE_68                             (0x00000088U) /* RSCANFDRF4*1 */
#define _DMAC_TRIGGER_SOURCE_69                             (0x0000008AU) /* RSCANFDRF5*1 */
#define _DMAC_TRIGGER_SOURCE_70                             (0x0000008CU) /* INTCSIH0IC */
#define _DMAC_TRIGGER_SOURCE_71                             (0x0000008EU) /* INTCSIH0IR */
#define _DMAC_TRIGGER_SOURCE_72                             (0x00000090U) /* INTCSIH0IJC */
#define _DMAC_TRIGGER_SOURCE_73                             (0x00000092U) /* INTP1 */
#define _DMAC_TRIGGER_SOURCE_74                             (0x00000094U) /* INTP3 */
#define _DMAC_TRIGGER_SOURCE_75                             (0x00000096U) /* INTP5 */
#define _DMAC_TRIGGER_SOURCE_76                             (0x00000098U) /* INTTAUD0I3 */
#define _DMAC_TRIGGER_SOURCE_77                             (0x0000009AU) /* INTTAUD0I7 */
#define _DMAC_TRIGGER_SOURCE_78                             (0x0000009CU) /* INTTAUD0I11 */
#define _DMAC_TRIGGER_SOURCE_79                             (0x0000009EU) /* INTTAUD0I15 */
#define _DMAC_TRIGGER_SOURCE_80                             (0x000000A0U) /* INTTAUJ0I1 */
#define _DMAC_TRIGGER_SOURCE_81                             (0x000000A2U) /* INTTAUJ0I2 */
#define _DMAC_TRIGGER_SOURCE_82                             (0x000000A4U) /* RSCANFDRF6*1 */
#define _DMAC_TRIGGER_SOURCE_83                             (0x000000A6U) /* RSCANFDRF7*1 */
#define _DMAC_TRIGGER_SOURCE_85                             (0x000000AAU) /* INTDMAFL */
#define _DMAC_TRIGGER_SOURCE_86                             (0x000000ACU) /* INTRLIN31UR0 */
#define _DMAC_TRIGGER_SOURCE_87                             (0x000000AEU) /* INTRLIN31UR1 */
#define _DMAC_TRIGGER_SOURCE_88                             (0x000000B0U) /* INTP7 */
#define _DMAC_TRIGGER_SOURCE_89                             (0x000000B2U) /* INTCSIH2IC */
#define _DMAC_TRIGGER_SOURCE_90                             (0x000000B4U) /* INTCSIH2IR */
#define _DMAC_TRIGGER_SOURCE_91                             (0x000000B6U) /* INTCSIH2IJC */
#define _DMAC_TRIGGER_SOURCE_92                             (0x000000B8U) /* INTTAUB0I1 */
#define _DMAC_TRIGGER_SOURCE_93                             (0x000000BAU) /* INTTAUB0I3 */
#define _DMAC_TRIGGER_SOURCE_94                             (0x000000BCU) /* INTTAUB0I5 */
#define _DMAC_TRIGGER_SOURCE_95                             (0x000000BEU) /* INTTAUB0I7 */
#define _DMAC_TRIGGER_SOURCE_96                             (0x000000C0U) /* INTTAUB0I8 */
#define _DMAC_TRIGGER_SOURCE_97                             (0x000000C2U) /* INTTAUB0I10 */
#define _DMAC_TRIGGER_SOURCE_98                             (0x000000C4U) /* INTTAUB0I12 */
#define _DMAC_TRIGGER_SOURCE_99                             (0x000000C6U) /* INTTAUB0I14 */
#define _DMAC_TRIGGER_SOURCE_100                            (0x000000C8U) /* INTTAUJ1I1 */
#define _DMAC_TRIGGER_SOURCE_101                            (0x000000CAU) /* INTTAUJ1I3 */
#define _DMAC_TRIGGER_SOURCE_102                            (0x000000CCU) /* INTP9 */
#define _DMAC_TRIGGER_SOURCE_103                            (0x000000CEU) /* INTADCA1I0 */
#define _DMAC_TRIGGER_SOURCE_104                            (0x000000D0U) /* INTADCA1I1 */
#define _DMAC_TRIGGER_SOURCE_105                            (0x000000D2U) /* INTADCA1I2 */
#define _DMAC_TRIGGER_SOURCE_106                            (0x000000D4U) /* ADC_CONV_END1 */
#define _DMAC_TRIGGER_SOURCE_109                            (0x000000DAU) /* INTCSIG1IC */
#define _DMAC_TRIGGER_SOURCE_110                            (0x000000DCU) /* INTCSIG1IR */
#define _DMAC_TRIGGER_SOURCE_111                            (0x000000DEU) /* INTRLIN33UR0 */
#define _DMAC_TRIGGER_SOURCE_112                            (0x000000E0U) /* INTRLIN33UR1 */
#define _DMAC_TRIGGER_SOURCE_113                            (0x000000E2U) /* INTRLIN35UR0 */
#define _DMAC_TRIGGER_SOURCE_114                            (0x000000E4U) /* INTRLIN35UR1 */
#define _DMAC_TRIGGER_SOURCE_115                            (0x000000E6U) /* INTTAUB1I1 */
#define _DMAC_TRIGGER_SOURCE_116                            (0x000000E8U) /* INTTAUB1I3 */
#define _DMAC_TRIGGER_SOURCE_117                            (0x000000EAU) /* INTTAUB1I5 */
#define _DMAC_TRIGGER_SOURCE_118                            (0x000000ECU) /* INTTAUB1I7 */
#define _DMAC_TRIGGER_SOURCE_119                            (0x000000EEU) /* INTTAUB1I8 */
#define _DMAC_TRIGGER_SOURCE_120                            (0x000000F0U) /* INTTAUB1I10 */
#define _DMAC_TRIGGER_SOURCE_121                            (0x000000F2U) /* INTTAUB1I12 */
#define _DMAC_TRIGGER_SOURCE_122                            (0x000000F4U) /* INTTAUB1I14 */

/*
    DMAC Channel Master Setting Register n  (DMnmCM)
*/
/* Channel master UM setting (UM) (UM) */
#define _DMAC_SUPERVISON_MODE                               (0x00000000U) /* Supervison mode */
#define _DMAC_USER_MODE                                     (0x00000002U) /* User mode */
/* Channel master PEID setting  (PEID[2-0]) */
#define _DMAC_PE1_SETTING                                   (0x00000010U) /* PE1 */
#define _DMAC_PE2_SETTING                                   (0x00000030U) /* PE2 */
/* Channel master PEID setting  (SPID1,SPID0) */
#define _DMAC_SPID0_SETTING                                 (0x00000000U) /* SPID0 */
#define _DMAC_SPID1_SETTING                                 (0x00000004U) /* SPID1 */
#define _DMAC_SPID2_SETTING                                 (0x00000008U) /* SPID2 */
#define _DMAC_SPID3_SETTING                                 (0x0000000CU) /* SPID3 */

/*
    DMA Control Register (DMACTL)
*/
/* DMA suspension (DMASPD) */
#define _DMAC_SUSPEND_CLEARED                               (0x00000000U) /* DMA suspension cleared */
#define _DMAC_SUSPEND_REQUEST                               (0x00000001U) /* DMA suspension request/ongoing */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _DMAC8_DESTINATION_ADDRESS                          (0x00000000U)
#define _DMAC8_SOURCE_ADDRESS                               (0x00000000U)
#define _DMAC8_TRANSFER_COUNT                               (0x00000000U)
#define _DMAC8_ADDRESS_RELOAD_COUNT                         (0x00000000U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_DMAC1_Create(void);
void R_DMAC10_Create(void);
void R_DMAC10_Start(void);
void R_DMAC10_Stop(void);
void R_DMAC10_Set_SoftwareTrigger(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif