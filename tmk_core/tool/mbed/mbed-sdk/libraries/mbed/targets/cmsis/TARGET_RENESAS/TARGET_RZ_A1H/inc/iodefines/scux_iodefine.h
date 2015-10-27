/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer*
* Copyright (C) 2013-2014 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name : scux_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef SCUX_IODEFINE_H
#define SCUX_IODEFINE_H
/* ->QAC 0639 : Over 127 members (C90) */
/* ->SEC M1.10.1 : Not magic number */

struct st_scux
{                                                          /* SCUX             */
/* start of struct st_scux_from_ipcir_ipc0_n */
    volatile uint32_t  IPCIR_IPC0_0;                           /*  IPCIR_IPC0_0    */
    volatile uint32_t  IPSLR_IPC0_0;                           /*  IPSLR_IPC0_0    */
    volatile uint8_t   dummy259[248];                          /*                  */
/* end of struct st_scux_from_ipcir_ipc0_n */
/* start of struct st_scux_from_ipcir_ipc0_n */
    volatile uint32_t  IPCIR_IPC0_1;                           /*  IPCIR_IPC0_1    */
    volatile uint32_t  IPSLR_IPC0_1;                           /*  IPSLR_IPC0_1    */
    volatile uint8_t   dummy260[248];                          /*                  */
/* end of struct st_scux_from_ipcir_ipc0_n */
/* start of struct st_scux_from_ipcir_ipc0_n */
    volatile uint32_t  IPCIR_IPC0_2;                           /*  IPCIR_IPC0_2    */
    volatile uint32_t  IPSLR_IPC0_2;                           /*  IPSLR_IPC0_2    */
    volatile uint8_t   dummy261[248];                          /*                  */
/* end of struct st_scux_from_ipcir_ipc0_n */
/* start of struct st_scux_from_ipcir_ipc0_n */
    volatile uint32_t  IPCIR_IPC0_3;                           /*  IPCIR_IPC0_3    */
    volatile uint32_t  IPSLR_IPC0_3;                           /*  IPSLR_IPC0_3    */
    volatile uint8_t   dummy262[248];                          /*                  */
/* end of struct st_scux_from_ipcir_ipc0_n */
/* start of struct st_scux_from_opcir_opc0_n */
    volatile uint32_t  OPCIR_OPC0_0;                           /*  OPCIR_OPC0_0    */
    volatile uint32_t  OPSLR_OPC0_0;                           /*  OPSLR_OPC0_0    */
    volatile uint8_t   dummy263[248];                          /*                  */
/* end of struct st_scux_from_opcir_opc0_n */
/* start of struct st_scux_from_opcir_opc0_n */
    volatile uint32_t  OPCIR_OPC0_1;                           /*  OPCIR_OPC0_1    */
    volatile uint32_t  OPSLR_OPC0_1;                           /*  OPSLR_OPC0_1    */
    volatile uint8_t   dummy264[248];                          /*                  */
/* end of struct st_scux_from_opcir_opc0_n */
/* start of struct st_scux_from_opcir_opc0_n */
    volatile uint32_t  OPCIR_OPC0_2;                           /*  OPCIR_OPC0_2    */
    volatile uint32_t  OPSLR_OPC0_2;                           /*  OPSLR_OPC0_2    */
    volatile uint8_t   dummy265[248];                          /*                  */
/* end of struct st_scux_from_opcir_opc0_n */
/* start of struct st_scux_from_opcir_opc0_n */
    volatile uint32_t  OPCIR_OPC0_3;                           /*  OPCIR_OPC0_3    */
    volatile uint32_t  OPSLR_OPC0_3;                           /*  OPSLR_OPC0_3    */
    volatile uint8_t   dummy266[248];                          /*                  */
/* end of struct st_scux_from_opcir_opc0_n */
/* start of struct st_scux_from_ffdir_ffd0_n */
    volatile uint32_t  FFDIR_FFD0_0;                           /*  FFDIR_FFD0_0    */
    volatile uint32_t  FDAIR_FFD0_0;                           /*  FDAIR_FFD0_0    */
    volatile uint32_t  DRQSR_FFD0_0;                           /*  DRQSR_FFD0_0    */
    volatile uint32_t  FFDPR_FFD0_0;                           /*  FFDPR_FFD0_0    */
    volatile uint32_t  FFDBR_FFD0_0;                           /*  FFDBR_FFD0_0    */
    volatile uint32_t  DEVMR_FFD0_0;                           /*  DEVMR_FFD0_0    */
    volatile uint8_t   dummy267[4];                            /*                  */
    volatile uint32_t  DEVCR_FFD0_0;                           /*  DEVCR_FFD0_0    */
/* end of struct st_scux_from_ffdir_ffd0_n */
    volatile uint8_t   dummy268[224];                          /*                  */
/* start of struct st_scux_from_ffdir_ffd0_n */
    volatile uint32_t  FFDIR_FFD0_1;                           /*  FFDIR_FFD0_1    */
    volatile uint32_t  FDAIR_FFD0_1;                           /*  FDAIR_FFD0_1    */
    volatile uint32_t  DRQSR_FFD0_1;                           /*  DRQSR_FFD0_1    */
    volatile uint32_t  FFDPR_FFD0_1;                           /*  FFDPR_FFD0_1    */
    volatile uint32_t  FFDBR_FFD0_1;                           /*  FFDBR_FFD0_1    */
    volatile uint32_t  DEVMR_FFD0_1;                           /*  DEVMR_FFD0_1    */
    volatile uint8_t   dummy269[4];                            /*                  */
    volatile uint32_t  DEVCR_FFD0_1;                           /*  DEVCR_FFD0_1    */
/* end of struct st_scux_from_ffdir_ffd0_n */
    volatile uint8_t   dummy270[224];                          /*                  */
/* start of struct st_scux_from_ffdir_ffd0_n */
    volatile uint32_t  FFDIR_FFD0_2;                           /*  FFDIR_FFD0_2    */
    volatile uint32_t  FDAIR_FFD0_2;                           /*  FDAIR_FFD0_2    */
    volatile uint32_t  DRQSR_FFD0_2;                           /*  DRQSR_FFD0_2    */
    volatile uint32_t  FFDPR_FFD0_2;                           /*  FFDPR_FFD0_2    */
    volatile uint32_t  FFDBR_FFD0_2;                           /*  FFDBR_FFD0_2    */
    volatile uint32_t  DEVMR_FFD0_2;                           /*  DEVMR_FFD0_2    */
    volatile uint8_t   dummy271[4];                            /*                  */
    volatile uint32_t  DEVCR_FFD0_2;                           /*  DEVCR_FFD0_2    */
/* end of struct st_scux_from_ffdir_ffd0_n */
    volatile uint8_t   dummy272[224];                          /*                  */
/* start of struct st_scux_from_ffdir_ffd0_n */
    volatile uint32_t  FFDIR_FFD0_3;                           /*  FFDIR_FFD0_3    */
    volatile uint32_t  FDAIR_FFD0_3;                           /*  FDAIR_FFD0_3    */
    volatile uint32_t  DRQSR_FFD0_3;                           /*  DRQSR_FFD0_3    */
    volatile uint32_t  FFDPR_FFD0_3;                           /*  FFDPR_FFD0_3    */
    volatile uint32_t  FFDBR_FFD0_3;                           /*  FFDBR_FFD0_3    */
    volatile uint32_t  DEVMR_FFD0_3;                           /*  DEVMR_FFD0_3    */
    volatile uint8_t   dummy273[4];                            /*                  */
    volatile uint32_t  DEVCR_FFD0_3;                           /*  DEVCR_FFD0_3    */
/* end of struct st_scux_from_ffdir_ffd0_n */
    volatile uint8_t   dummy274[224];                          /*                  */
/* start of struct st_scux_from_ffuir_ffu0_n */
    volatile uint32_t  FFUIR_FFU0_0;                           /*  FFUIR_FFU0_0    */
    volatile uint32_t  FUAIR_FFU0_0;                           /*  FUAIR_FFU0_0    */
    volatile uint32_t  URQSR_FFU0_0;                           /*  URQSR_FFU0_0    */
    volatile uint32_t  FFUPR_FFU0_0;                           /*  FFUPR_FFU0_0    */
    volatile uint32_t  UEVMR_FFU0_0;                           /*  UEVMR_FFU0_0    */
    volatile uint8_t   dummy275[4];                            /*                  */
    volatile uint32_t  UEVCR_FFU0_0;                           /*  UEVCR_FFU0_0    */
/* end of struct st_scux_from_ffuir_ffu0_n */
    volatile uint8_t   dummy276[228];                          /*                  */
/* start of struct st_scux_from_ffuir_ffu0_n */
    volatile uint32_t  FFUIR_FFU0_1;                           /*  FFUIR_FFU0_1    */
    volatile uint32_t  FUAIR_FFU0_1;                           /*  FUAIR_FFU0_1    */
    volatile uint32_t  URQSR_FFU0_1;                           /*  URQSR_FFU0_1    */
    volatile uint32_t  FFUPR_FFU0_1;                           /*  FFUPR_FFU0_1    */
    volatile uint32_t  UEVMR_FFU0_1;                           /*  UEVMR_FFU0_1    */
    volatile uint8_t   dummy277[4];                            /*                  */
    volatile uint32_t  UEVCR_FFU0_1;                           /*  UEVCR_FFU0_1    */
/* end of struct st_scux_from_ffuir_ffu0_n */
    volatile uint8_t   dummy278[228];                          /*                  */
/* start of struct st_scux_from_ffuir_ffu0_n */
    volatile uint32_t  FFUIR_FFU0_2;                           /*  FFUIR_FFU0_2    */
    volatile uint32_t  FUAIR_FFU0_2;                           /*  FUAIR_FFU0_2    */
    volatile uint32_t  URQSR_FFU0_2;                           /*  URQSR_FFU0_2    */
    volatile uint32_t  FFUPR_FFU0_2;                           /*  FFUPR_FFU0_2    */
    volatile uint32_t  UEVMR_FFU0_2;                           /*  UEVMR_FFU0_2    */
    volatile uint8_t   dummy279[4];                            /*                  */
    volatile uint32_t  UEVCR_FFU0_2;                           /*  UEVCR_FFU0_2    */
/* end of struct st_scux_from_ffuir_ffu0_n */
    volatile uint8_t   dummy280[228];                          /*                  */
/* start of struct st_scux_from_ffuir_ffu0_n */
    volatile uint32_t  FFUIR_FFU0_3;                           /*  FFUIR_FFU0_3    */
    volatile uint32_t  FUAIR_FFU0_3;                           /*  FUAIR_FFU0_3    */
    volatile uint32_t  URQSR_FFU0_3;                           /*  URQSR_FFU0_3    */
    volatile uint32_t  FFUPR_FFU0_3;                           /*  FFUPR_FFU0_3    */
    volatile uint32_t  UEVMR_FFU0_3;                           /*  UEVMR_FFU0_3    */
    volatile uint8_t   dummy281[4];                            /*                  */
    volatile uint32_t  UEVCR_FFU0_3;                           /*  UEVCR_FFU0_3    */
/* end of struct st_scux_from_ffuir_ffu0_n */
    volatile uint8_t   dummy282[228];                          /*                  */
/* start of struct st_scux_from_srcir0_2src0_n */
    volatile uint32_t  SRCIR0_2SRC0_0;                         /*  SRCIR0_2SRC0_0  */
    volatile uint32_t  SADIR0_2SRC0_0;                         /*  SADIR0_2SRC0_0  */
    volatile uint32_t  SRCBR0_2SRC0_0;                         /*  SRCBR0_2SRC0_0  */
    volatile uint32_t  IFSCR0_2SRC0_0;                         /*  IFSCR0_2SRC0_0  */
    volatile uint32_t  IFSVR0_2SRC0_0;                         /*  IFSVR0_2SRC0_0  */
    volatile uint32_t  SRCCR0_2SRC0_0;                         /*  SRCCR0_2SRC0_0  */
    volatile uint32_t  MNFSR0_2SRC0_0;                         /*  MNFSR0_2SRC0_0  */
    volatile uint32_t  BFSSR0_2SRC0_0;                         /*  BFSSR0_2SRC0_0  */
    volatile uint32_t  SC2SR0_2SRC0_0;                         /*  SC2SR0_2SRC0_0  */
    volatile uint32_t  WATSR0_2SRC0_0;                         /*  WATSR0_2SRC0_0  */
    volatile uint32_t  SEVMR0_2SRC0_0;                         /*  SEVMR0_2SRC0_0  */
    volatile uint8_t   dummy283[4];                            /*                  */
    volatile uint32_t  SEVCR0_2SRC0_0;                         /*  SEVCR0_2SRC0_0  */
    volatile uint32_t  SRCIR1_2SRC0_0;                         /*  SRCIR1_2SRC0_0  */
    volatile uint32_t  SADIR1_2SRC0_0;                         /*  SADIR1_2SRC0_0  */
    volatile uint32_t  SRCBR1_2SRC0_0;                         /*  SRCBR1_2SRC0_0  */
    volatile uint32_t  IFSCR1_2SRC0_0;                         /*  IFSCR1_2SRC0_0  */
    volatile uint32_t  IFSVR1_2SRC0_0;                         /*  IFSVR1_2SRC0_0  */
    volatile uint32_t  SRCCR1_2SRC0_0;                         /*  SRCCR1_2SRC0_0  */
    volatile uint32_t  MNFSR1_2SRC0_0;                         /*  MNFSR1_2SRC0_0  */
    volatile uint32_t  BFSSR1_2SRC0_0;                         /*  BFSSR1_2SRC0_0  */
    volatile uint32_t  SC2SR1_2SRC0_0;                         /*  SC2SR1_2SRC0_0  */
    volatile uint32_t  WATSR1_2SRC0_0;                         /*  WATSR1_2SRC0_0  */
    volatile uint32_t  SEVMR1_2SRC0_0;                         /*  SEVMR1_2SRC0_0  */
    volatile uint8_t   dummy284[4];                            /*                  */
    volatile uint32_t  SEVCR1_2SRC0_0;                         /*  SEVCR1_2SRC0_0  */
    volatile uint32_t  SRCIRR_2SRC0_0;                         /*  SRCIRR_2SRC0_0  */
/* end of struct st_scux_from_srcir0_2src0_n */
    volatile uint8_t   dummy285[148];                          /*                  */
/* start of struct st_scux_from_srcir0_2src0_n */
    volatile uint32_t  SRCIR0_2SRC0_1;                         /*  SRCIR0_2SRC0_1  */
    volatile uint32_t  SADIR0_2SRC0_1;                         /*  SADIR0_2SRC0_1  */
    volatile uint32_t  SRCBR0_2SRC0_1;                         /*  SRCBR0_2SRC0_1  */
    volatile uint32_t  IFSCR0_2SRC0_1;                         /*  IFSCR0_2SRC0_1  */
    volatile uint32_t  IFSVR0_2SRC0_1;                         /*  IFSVR0_2SRC0_1  */
    volatile uint32_t  SRCCR0_2SRC0_1;                         /*  SRCCR0_2SRC0_1  */
    volatile uint32_t  MNFSR0_2SRC0_1;                         /*  MNFSR0_2SRC0_1  */
    volatile uint32_t  BFSSR0_2SRC0_1;                         /*  BFSSR0_2SRC0_1  */
    volatile uint32_t  SC2SR0_2SRC0_1;                         /*  SC2SR0_2SRC0_1  */
    volatile uint32_t  WATSR0_2SRC0_1;                         /*  WATSR0_2SRC0_1  */
    volatile uint32_t  SEVMR0_2SRC0_1;                         /*  SEVMR0_2SRC0_1  */
    volatile uint8_t   dummy286[4];                            /*                  */
    volatile uint32_t  SEVCR0_2SRC0_1;                         /*  SEVCR0_2SRC0_1  */
    volatile uint32_t  SRCIR1_2SRC0_1;                         /*  SRCIR1_2SRC0_1  */
    volatile uint32_t  SADIR1_2SRC0_1;                         /*  SADIR1_2SRC0_1  */
    volatile uint32_t  SRCBR1_2SRC0_1;                         /*  SRCBR1_2SRC0_1  */
    volatile uint32_t  IFSCR1_2SRC0_1;                         /*  IFSCR1_2SRC0_1  */
    volatile uint32_t  IFSVR1_2SRC0_1;                         /*  IFSVR1_2SRC0_1  */
    volatile uint32_t  SRCCR1_2SRC0_1;                         /*  SRCCR1_2SRC0_1  */
    volatile uint32_t  MNFSR1_2SRC0_1;                         /*  MNFSR1_2SRC0_1  */
    volatile uint32_t  BFSSR1_2SRC0_1;                         /*  BFSSR1_2SRC0_1  */
    volatile uint32_t  SC2SR1_2SRC0_1;                         /*  SC2SR1_2SRC0_1  */
    volatile uint32_t  WATSR1_2SRC0_1;                         /*  WATSR1_2SRC0_1  */
    volatile uint32_t  SEVMR1_2SRC0_1;                         /*  SEVMR1_2SRC0_1  */
    volatile uint8_t   dummy287[4];                            /*                  */
    volatile uint32_t  SEVCR1_2SRC0_1;                         /*  SEVCR1_2SRC0_1  */
    volatile uint32_t  SRCIRR_2SRC0_1;                         /*  SRCIRR_2SRC0_1  */
/* end of struct st_scux_from_srcir0_2src0_n */
    volatile uint8_t   dummy288[148];                          /*                  */
/* start of struct st_scux_from_dvuir_dvu0_n */
    volatile uint32_t  DVUIR_DVU0_0;                           /*  DVUIR_DVU0_0    */
    volatile uint32_t  VADIR_DVU0_0;                           /*  VADIR_DVU0_0    */
    volatile uint32_t  DVUBR_DVU0_0;                           /*  DVUBR_DVU0_0    */
    volatile uint32_t  DVUCR_DVU0_0;                           /*  DVUCR_DVU0_0    */
    volatile uint32_t  ZCMCR_DVU0_0;                           /*  ZCMCR_DVU0_0    */
    volatile uint32_t  VRCTR_DVU0_0;                           /*  VRCTR_DVU0_0    */
    volatile uint32_t  VRPDR_DVU0_0;                           /*  VRPDR_DVU0_0    */
    volatile uint32_t  VRDBR_DVU0_0;                           /*  VRDBR_DVU0_0    */
    volatile uint32_t  VRWTR_DVU0_0;                           /*  VRWTR_DVU0_0    */
    volatile uint32_t  VOL0R_DVU0_0;                           /*  VOL0R_DVU0_0    */
    volatile uint32_t  VOL1R_DVU0_0;                           /*  VOL1R_DVU0_0    */
    volatile uint32_t  VOL2R_DVU0_0;                           /*  VOL2R_DVU0_0    */
    volatile uint32_t  VOL3R_DVU0_0;                           /*  VOL3R_DVU0_0    */
    volatile uint32_t  VOL4R_DVU0_0;                           /*  VOL4R_DVU0_0    */
    volatile uint32_t  VOL5R_DVU0_0;                           /*  VOL5R_DVU0_0    */
    volatile uint32_t  VOL6R_DVU0_0;                           /*  VOL6R_DVU0_0    */
    volatile uint32_t  VOL7R_DVU0_0;                           /*  VOL7R_DVU0_0    */
    volatile uint32_t  DVUER_DVU0_0;                           /*  DVUER_DVU0_0    */
    volatile uint32_t  DVUSR_DVU0_0;                           /*  DVUSR_DVU0_0    */
    volatile uint32_t  VEVMR_DVU0_0;                           /*  VEVMR_DVU0_0    */
    volatile uint8_t   dummy289[4];                            /*                  */
    volatile uint32_t  VEVCR_DVU0_0;                           /*  VEVCR_DVU0_0    */
/* end of struct st_scux_from_dvuir_dvu0_n */
    volatile uint8_t   dummy290[168];                          /*                  */
/* start of struct st_scux_from_dvuir_dvu0_n */
    volatile uint32_t  DVUIR_DVU0_1;                           /*  DVUIR_DVU0_1    */
    volatile uint32_t  VADIR_DVU0_1;                           /*  VADIR_DVU0_1    */
    volatile uint32_t  DVUBR_DVU0_1;                           /*  DVUBR_DVU0_1    */
    volatile uint32_t  DVUCR_DVU0_1;                           /*  DVUCR_DVU0_1    */
    volatile uint32_t  ZCMCR_DVU0_1;                           /*  ZCMCR_DVU0_1    */
    volatile uint32_t  VRCTR_DVU0_1;                           /*  VRCTR_DVU0_1    */
    volatile uint32_t  VRPDR_DVU0_1;                           /*  VRPDR_DVU0_1    */
    volatile uint32_t  VRDBR_DVU0_1;                           /*  VRDBR_DVU0_1    */
    volatile uint32_t  VRWTR_DVU0_1;                           /*  VRWTR_DVU0_1    */
    volatile uint32_t  VOL0R_DVU0_1;                           /*  VOL0R_DVU0_1    */
    volatile uint32_t  VOL1R_DVU0_1;                           /*  VOL1R_DVU0_1    */
    volatile uint32_t  VOL2R_DVU0_1;                           /*  VOL2R_DVU0_1    */
    volatile uint32_t  VOL3R_DVU0_1;                           /*  VOL3R_DVU0_1    */
    volatile uint32_t  VOL4R_DVU0_1;                           /*  VOL4R_DVU0_1    */
    volatile uint32_t  VOL5R_DVU0_1;                           /*  VOL5R_DVU0_1    */
    volatile uint32_t  VOL6R_DVU0_1;                           /*  VOL6R_DVU0_1    */
    volatile uint32_t  VOL7R_DVU0_1;                           /*  VOL7R_DVU0_1    */
    volatile uint32_t  DVUER_DVU0_1;                           /*  DVUER_DVU0_1    */
    volatile uint32_t  DVUSR_DVU0_1;                           /*  DVUSR_DVU0_1    */
    volatile uint32_t  VEVMR_DVU0_1;                           /*  VEVMR_DVU0_1    */
    volatile uint8_t   dummy291[4];                            /*                  */
    volatile uint32_t  VEVCR_DVU0_1;                           /*  VEVCR_DVU0_1    */
/* end of struct st_scux_from_dvuir_dvu0_n */
    volatile uint8_t   dummy292[168];                          /*                  */
/* start of struct st_scux_from_dvuir_dvu0_n */
    volatile uint32_t  DVUIR_DVU0_2;                           /*  DVUIR_DVU0_2    */
    volatile uint32_t  VADIR_DVU0_2;                           /*  VADIR_DVU0_2    */
    volatile uint32_t  DVUBR_DVU0_2;                           /*  DVUBR_DVU0_2    */
    volatile uint32_t  DVUCR_DVU0_2;                           /*  DVUCR_DVU0_2    */
    volatile uint32_t  ZCMCR_DVU0_2;                           /*  ZCMCR_DVU0_2    */
    volatile uint32_t  VRCTR_DVU0_2;                           /*  VRCTR_DVU0_2    */
    volatile uint32_t  VRPDR_DVU0_2;                           /*  VRPDR_DVU0_2    */
    volatile uint32_t  VRDBR_DVU0_2;                           /*  VRDBR_DVU0_2    */
    volatile uint32_t  VRWTR_DVU0_2;                           /*  VRWTR_DVU0_2    */
    volatile uint32_t  VOL0R_DVU0_2;                           /*  VOL0R_DVU0_2    */
    volatile uint32_t  VOL1R_DVU0_2;                           /*  VOL1R_DVU0_2    */
    volatile uint32_t  VOL2R_DVU0_2;                           /*  VOL2R_DVU0_2    */
    volatile uint32_t  VOL3R_DVU0_2;                           /*  VOL3R_DVU0_2    */
    volatile uint32_t  VOL4R_DVU0_2;                           /*  VOL4R_DVU0_2    */
    volatile uint32_t  VOL5R_DVU0_2;                           /*  VOL5R_DVU0_2    */
    volatile uint32_t  VOL6R_DVU0_2;                           /*  VOL6R_DVU0_2    */
    volatile uint32_t  VOL7R_DVU0_2;                           /*  VOL7R_DVU0_2    */
    volatile uint32_t  DVUER_DVU0_2;                           /*  DVUER_DVU0_2    */
    volatile uint32_t  DVUSR_DVU0_2;                           /*  DVUSR_DVU0_2    */
    volatile uint32_t  VEVMR_DVU0_2;                           /*  VEVMR_DVU0_2    */
    volatile uint8_t   dummy293[4];                            /*                  */
    volatile uint32_t  VEVCR_DVU0_2;                           /*  VEVCR_DVU0_2    */
/* end of struct st_scux_from_dvuir_dvu0_n */
    volatile uint8_t   dummy294[168];                          /*                  */
/* start of struct st_scux_from_dvuir_dvu0_n */
    volatile uint32_t  DVUIR_DVU0_3;                           /*  DVUIR_DVU0_3    */
    volatile uint32_t  VADIR_DVU0_3;                           /*  VADIR_DVU0_3    */
    volatile uint32_t  DVUBR_DVU0_3;                           /*  DVUBR_DVU0_3    */
    volatile uint32_t  DVUCR_DVU0_3;                           /*  DVUCR_DVU0_3    */
    volatile uint32_t  ZCMCR_DVU0_3;                           /*  ZCMCR_DVU0_3    */
    volatile uint32_t  VRCTR_DVU0_3;                           /*  VRCTR_DVU0_3    */
    volatile uint32_t  VRPDR_DVU0_3;                           /*  VRPDR_DVU0_3    */
    volatile uint32_t  VRDBR_DVU0_3;                           /*  VRDBR_DVU0_3    */
    volatile uint32_t  VRWTR_DVU0_3;                           /*  VRWTR_DVU0_3    */
    volatile uint32_t  VOL0R_DVU0_3;                           /*  VOL0R_DVU0_3    */
    volatile uint32_t  VOL1R_DVU0_3;                           /*  VOL1R_DVU0_3    */
    volatile uint32_t  VOL2R_DVU0_3;                           /*  VOL2R_DVU0_3    */
    volatile uint32_t  VOL3R_DVU0_3;                           /*  VOL3R_DVU0_3    */
    volatile uint32_t  VOL4R_DVU0_3;                           /*  VOL4R_DVU0_3    */
    volatile uint32_t  VOL5R_DVU0_3;                           /*  VOL5R_DVU0_3    */
    volatile uint32_t  VOL6R_DVU0_3;                           /*  VOL6R_DVU0_3    */
    volatile uint32_t  VOL7R_DVU0_3;                           /*  VOL7R_DVU0_3    */
    volatile uint32_t  DVUER_DVU0_3;                           /*  DVUER_DVU0_3    */
    volatile uint32_t  DVUSR_DVU0_3;                           /*  DVUSR_DVU0_3    */
    volatile uint32_t  VEVMR_DVU0_3;                           /*  VEVMR_DVU0_3    */
    volatile uint8_t   dummy295[4];                            /*                  */
    volatile uint32_t  VEVCR_DVU0_3;                           /*  VEVCR_DVU0_3    */
/* end of struct st_scux_from_dvuir_dvu0_n */
    volatile uint8_t   dummy296[168];                          /*                  */
    volatile uint32_t  MIXIR_MIX0_0;                           /*  MIXIR_MIX0_0    */
    volatile uint32_t  MADIR_MIX0_0;                           /*  MADIR_MIX0_0    */
    volatile uint32_t  MIXBR_MIX0_0;                           /*  MIXBR_MIX0_0    */
    volatile uint32_t  MIXMR_MIX0_0;                           /*  MIXMR_MIX0_0    */
    volatile uint32_t  MVPDR_MIX0_0;                           /*  MVPDR_MIX0_0    */
    volatile uint32_t  MDBAR_MIX0_0;                           /*  MDBAR_MIX0_0    */
    volatile uint32_t  MDBBR_MIX0_0;                           /*  MDBBR_MIX0_0    */
    volatile uint32_t  MDBCR_MIX0_0;                           /*  MDBCR_MIX0_0    */
    volatile uint32_t  MDBDR_MIX0_0;                           /*  MDBDR_MIX0_0    */
    volatile uint32_t  MDBER_MIX0_0;                           /*  MDBER_MIX0_0    */
    volatile uint32_t  MIXSR_MIX0_0;                           /*  MIXSR_MIX0_0    */
    volatile uint8_t   dummy297[212];                          /*                  */
    volatile uint32_t  SWRSR_CIM;                              /*  SWRSR_CIM       */
    volatile uint32_t  DMACR_CIM;                              /*  DMACR_CIM       */
#define SCUX_DMATDn_CIM_COUNT 4
    union iodefine_reg32_16_t  DMATD0_CIM;                 /*  DMATD0_CIM      */
    union iodefine_reg32_16_t  DMATD1_CIM;                 /*  DMATD1_CIM      */
    union iodefine_reg32_16_t  DMATD2_CIM;                 /*  DMATD2_CIM      */
    union iodefine_reg32_16_t  DMATD3_CIM;                 /*  DMATD3_CIM      */
#define SCUX_DMATUn_CIM_COUNT 4
    union iodefine_reg32_16_t  DMATU0_CIM;                 /*  DMATU0_CIM      */
    union iodefine_reg32_16_t  DMATU1_CIM;                 /*  DMATU1_CIM      */
    union iodefine_reg32_16_t  DMATU2_CIM;                 /*  DMATU2_CIM      */
    union iodefine_reg32_16_t  DMATU3_CIM;                 /*  DMATU3_CIM      */
    
    volatile uint8_t   dummy298[16];                           /*                  */
    volatile uint32_t  SSIRSEL_CIM;                            /*  SSIRSEL_CIM     */
#define SCUX_FDTSELn_CIM_COUNT 4
    volatile uint32_t  FDTSEL0_CIM;                            /*  FDTSEL0_CIM     */
    volatile uint32_t  FDTSEL1_CIM;                            /*  FDTSEL1_CIM     */
    volatile uint32_t  FDTSEL2_CIM;                            /*  FDTSEL2_CIM     */
    volatile uint32_t  FDTSEL3_CIM;                            /*  FDTSEL3_CIM     */
#define SCUX_FUTSELn_CIM_COUNT 4
    volatile uint32_t  FUTSEL0_CIM;                            /*  FUTSEL0_CIM     */
    volatile uint32_t  FUTSEL1_CIM;                            /*  FUTSEL1_CIM     */
    volatile uint32_t  FUTSEL2_CIM;                            /*  FUTSEL2_CIM     */
    volatile uint32_t  FUTSEL3_CIM;                            /*  FUTSEL3_CIM     */
    volatile uint32_t  SSIPMD_CIM;                             /*  SSIPMD_CIM      */
    volatile uint32_t  SSICTRL_CIM;                            /*  SSICTRL_CIM     */
#define SCUX_SRCRSELn_CIM_COUNT 4
    volatile uint32_t  SRCRSEL0_CIM;                           /*  SRCRSEL0_CIM    */
    volatile uint32_t  SRCRSEL1_CIM;                           /*  SRCRSEL1_CIM    */
    volatile uint32_t  SRCRSEL2_CIM;                           /*  SRCRSEL2_CIM    */
    volatile uint32_t  SRCRSEL3_CIM;                           /*  SRCRSEL3_CIM    */
    volatile uint32_t  MIXRSEL_CIM;                            /*  MIXRSEL_CIM     */
};


struct st_scux_from_ipcir_ipc0_n
{
    volatile uint32_t  IPCIR_IPC0_0;                           /*  IPCIR_IPC0_0    */
    volatile uint32_t  IPSLR_IPC0_0;                           /*  IPSLR_IPC0_0    */
    volatile uint8_t   dummy1[248];                            /*                  */
};


struct st_scux_from_opcir_opc0_n
{
    volatile uint32_t  OPCIR_OPC0_0;                           /*  OPCIR_OPC0_0    */
    volatile uint32_t  OPSLR_OPC0_0;                           /*  OPSLR_OPC0_0    */
    volatile uint8_t   dummy1[248];                            /*                  */
};


struct st_scux_from_ffdir_ffd0_n
{
    volatile uint32_t  FFDIR_FFD0_0;                           /*  FFDIR_FFD0_0    */
    volatile uint32_t  FDAIR_FFD0_0;                           /*  FDAIR_FFD0_0    */
    volatile uint32_t  DRQSR_FFD0_0;                           /*  DRQSR_FFD0_0    */
    volatile uint32_t  FFDPR_FFD0_0;                           /*  FFDPR_FFD0_0    */
    volatile uint32_t  FFDBR_FFD0_0;                           /*  FFDBR_FFD0_0    */
    volatile uint32_t  DEVMR_FFD0_0;                           /*  DEVMR_FFD0_0    */
    volatile uint8_t   dummy1[4];                              /*                  */
    volatile uint32_t  DEVCR_FFD0_0;                           /*  DEVCR_FFD0_0    */
};


struct st_scux_from_ffuir_ffu0_n
{
    volatile uint32_t  FFUIR_FFU0_0;                           /*  FFUIR_FFU0_0    */
    volatile uint32_t  FUAIR_FFU0_0;                           /*  FUAIR_FFU0_0    */
    volatile uint32_t  URQSR_FFU0_0;                           /*  URQSR_FFU0_0    */
    volatile uint32_t  FFUPR_FFU0_0;                           /*  FFUPR_FFU0_0    */
    volatile uint32_t  UEVMR_FFU0_0;                           /*  UEVMR_FFU0_0    */
    volatile uint8_t   dummy1[4];                              /*                  */
    volatile uint32_t  UEVCR_FFU0_0;                           /*  UEVCR_FFU0_0    */
};


struct st_scux_from_srcir0_2src0_n
{
    volatile uint32_t  SRCIR0_2SRC0_0;                         /*  SRCIR0_2SRC0_0  */
    volatile uint32_t  SADIR0_2SRC0_0;                         /*  SADIR0_2SRC0_0  */
    volatile uint32_t  SRCBR0_2SRC0_0;                         /*  SRCBR0_2SRC0_0  */
    volatile uint32_t  IFSCR0_2SRC0_0;                         /*  IFSCR0_2SRC0_0  */
    volatile uint32_t  IFSVR0_2SRC0_0;                         /*  IFSVR0_2SRC0_0  */
    volatile uint32_t  SRCCR0_2SRC0_0;                         /*  SRCCR0_2SRC0_0  */
    volatile uint32_t  MNFSR0_2SRC0_0;                         /*  MNFSR0_2SRC0_0  */
    volatile uint32_t  BFSSR0_2SRC0_0;                         /*  BFSSR0_2SRC0_0  */
    volatile uint32_t  SC2SR0_2SRC0_0;                         /*  SC2SR0_2SRC0_0  */
    volatile uint32_t  WATSR0_2SRC0_0;                         /*  WATSR0_2SRC0_0  */
    volatile uint32_t  SEVMR0_2SRC0_0;                         /*  SEVMR0_2SRC0_0  */
    volatile uint8_t   dummy1[4];                              /*                  */
    volatile uint32_t  SEVCR0_2SRC0_0;                         /*  SEVCR0_2SRC0_0  */
    volatile uint32_t  SRCIR1_2SRC0_0;                         /*  SRCIR1_2SRC0_0  */
    volatile uint32_t  SADIR1_2SRC0_0;                         /*  SADIR1_2SRC0_0  */
    volatile uint32_t  SRCBR1_2SRC0_0;                         /*  SRCBR1_2SRC0_0  */
    volatile uint32_t  IFSCR1_2SRC0_0;                         /*  IFSCR1_2SRC0_0  */
    volatile uint32_t  IFSVR1_2SRC0_0;                         /*  IFSVR1_2SRC0_0  */
    volatile uint32_t  SRCCR1_2SRC0_0;                         /*  SRCCR1_2SRC0_0  */
    volatile uint32_t  MNFSR1_2SRC0_0;                         /*  MNFSR1_2SRC0_0  */
    volatile uint32_t  BFSSR1_2SRC0_0;                         /*  BFSSR1_2SRC0_0  */
    volatile uint32_t  SC2SR1_2SRC0_0;                         /*  SC2SR1_2SRC0_0  */
    volatile uint32_t  WATSR1_2SRC0_0;                         /*  WATSR1_2SRC0_0  */
    volatile uint32_t  SEVMR1_2SRC0_0;                         /*  SEVMR1_2SRC0_0  */
    volatile uint8_t   dummy2[4];                              /*                  */
    volatile uint32_t  SEVCR1_2SRC0_0;                         /*  SEVCR1_2SRC0_0  */
    volatile uint32_t  SRCIRR_2SRC0_0;                         /*  SRCIRR_2SRC0_0  */
};


struct st_scux_from_dvuir_dvu0_n
{
    volatile uint32_t  DVUIR_DVU0_0;                           /*  DVUIR_DVU0_0    */
    volatile uint32_t  VADIR_DVU0_0;                           /*  VADIR_DVU0_0    */
    volatile uint32_t  DVUBR_DVU0_0;                           /*  DVUBR_DVU0_0    */
    volatile uint32_t  DVUCR_DVU0_0;                           /*  DVUCR_DVU0_0    */
    volatile uint32_t  ZCMCR_DVU0_0;                           /*  ZCMCR_DVU0_0    */
    volatile uint32_t  VRCTR_DVU0_0;                           /*  VRCTR_DVU0_0    */
    volatile uint32_t  VRPDR_DVU0_0;                           /*  VRPDR_DVU0_0    */
    volatile uint32_t  VRDBR_DVU0_0;                           /*  VRDBR_DVU0_0    */
    volatile uint32_t  VRWTR_DVU0_0;                           /*  VRWTR_DVU0_0    */
    volatile uint32_t  VOL0R_DVU0_0;                           /*  VOL0R_DVU0_0    */
    volatile uint32_t  VOL1R_DVU0_0;                           /*  VOL1R_DVU0_0    */
    volatile uint32_t  VOL2R_DVU0_0;                           /*  VOL2R_DVU0_0    */
    volatile uint32_t  VOL3R_DVU0_0;                           /*  VOL3R_DVU0_0    */
    volatile uint32_t  VOL4R_DVU0_0;                           /*  VOL4R_DVU0_0    */
    volatile uint32_t  VOL5R_DVU0_0;                           /*  VOL5R_DVU0_0    */
    volatile uint32_t  VOL6R_DVU0_0;                           /*  VOL6R_DVU0_0    */
    volatile uint32_t  VOL7R_DVU0_0;                           /*  VOL7R_DVU0_0    */
    volatile uint32_t  DVUER_DVU0_0;                           /*  DVUER_DVU0_0    */
    volatile uint32_t  DVUSR_DVU0_0;                           /*  DVUSR_DVU0_0    */
    volatile uint32_t  VEVMR_DVU0_0;                           /*  VEVMR_DVU0_0    */
    volatile uint8_t   dummy1[4];                              /*                  */
    volatile uint32_t  VEVCR_DVU0_0;                           /*  VEVCR_DVU0_0    */
};


#define SCUX    (*(struct st_scux    *)0xE8208000uL) /* SCUX */


/* Start of channnel array defines of SCUX */

/* Channnel array defines of SCUX_FROM_DVUIR_DVU0_0_ARRAY */
/*(Sample) value = SCUX_FROM_DVUIR_DVU0_0_ARRAY[ channel ]->DVUIR_DVU0_0; */
#define SCUX_FROM_DVUIR_DVU0_0_ARRAY_COUNT  4
#define SCUX_FROM_DVUIR_DVU0_0_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &SCUX_FROM_DVUIR_DVU0_0, &SCUX_FROM_DVUIR_DVU0_1, &SCUX_FROM_DVUIR_DVU0_2, &SCUX_FROM_DVUIR_DVU0_3 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define SCUX_FROM_DVUIR_DVU0_0 (*(struct st_scux_from_dvuir_dvu0_n *)&SCUX.DVUIR_DVU0_0) /* SCUX_FROM_DVUIR_DVU0_0 */
#define SCUX_FROM_DVUIR_DVU0_1 (*(struct st_scux_from_dvuir_dvu0_n *)&SCUX.DVUIR_DVU0_1) /* SCUX_FROM_DVUIR_DVU0_1 */
#define SCUX_FROM_DVUIR_DVU0_2 (*(struct st_scux_from_dvuir_dvu0_n *)&SCUX.DVUIR_DVU0_2) /* SCUX_FROM_DVUIR_DVU0_2 */
#define SCUX_FROM_DVUIR_DVU0_3 (*(struct st_scux_from_dvuir_dvu0_n *)&SCUX.DVUIR_DVU0_3) /* SCUX_FROM_DVUIR_DVU0_3 */


/* Channnel array defines of SCUX_FROM_SRCIR0_2SRC0_0_ARRAY */
/*(Sample) value = SCUX_FROM_SRCIR0_2SRC0_0_ARRAY[ channel ]->SRCIR0_2SRC0_0; */
#define SCUX_FROM_SRCIR0_2SRC0_0_ARRAY_COUNT  2
#define SCUX_FROM_SRCIR0_2SRC0_0_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &SCUX_FROM_SRCIR0_2SRC0_0, &SCUX_FROM_SRCIR0_2SRC0_1 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define SCUX_FROM_SRCIR0_2SRC0_0 (*(struct st_scux_from_srcir0_2src0_n *)&SCUX.SRCIR0_2SRC0_0) /* SCUX_FROM_SRCIR0_2SRC0_0 */
#define SCUX_FROM_SRCIR0_2SRC0_1 (*(struct st_scux_from_srcir0_2src0_n *)&SCUX.SRCIR0_2SRC0_1) /* SCUX_FROM_SRCIR0_2SRC0_1 */


/* Channnel array defines of SCUX_FROM_FFUIR_FFU0_0_ARRAY */
/*(Sample) value = SCUX_FROM_FFUIR_FFU0_0_ARRAY[ channel ]->FFUIR_FFU0_0; */
#define SCUX_FROM_FFUIR_FFU0_0_ARRAY_COUNT  4
#define SCUX_FROM_FFUIR_FFU0_0_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &SCUX_FROM_FFUIR_FFU0_0, &SCUX_FROM_FFUIR_FFU0_1, &SCUX_FROM_FFUIR_FFU0_2, &SCUX_FROM_FFUIR_FFU0_3 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define SCUX_FROM_FFUIR_FFU0_0 (*(struct st_scux_from_ffuir_ffu0_n *)&SCUX.FFUIR_FFU0_0) /* SCUX_FROM_FFUIR_FFU0_0 */
#define SCUX_FROM_FFUIR_FFU0_1 (*(struct st_scux_from_ffuir_ffu0_n *)&SCUX.FFUIR_FFU0_1) /* SCUX_FROM_FFUIR_FFU0_1 */
#define SCUX_FROM_FFUIR_FFU0_2 (*(struct st_scux_from_ffuir_ffu0_n *)&SCUX.FFUIR_FFU0_2) /* SCUX_FROM_FFUIR_FFU0_2 */
#define SCUX_FROM_FFUIR_FFU0_3 (*(struct st_scux_from_ffuir_ffu0_n *)&SCUX.FFUIR_FFU0_3) /* SCUX_FROM_FFUIR_FFU0_3 */


/* Channnel array defines of SCUX_FROM_FFDIR_FFD0_0_ARRAY */
/*(Sample) value = SCUX_FROM_FFDIR_FFD0_0_ARRAY[ channel ]->FFDIR_FFD0_0; */
#define SCUX_FROM_FFDIR_FFD0_0_ARRAY_COUNT  4
#define SCUX_FROM_FFDIR_FFD0_0_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &SCUX_FROM_FFDIR_FFD0_0, &SCUX_FROM_FFDIR_FFD0_1, &SCUX_FROM_FFDIR_FFD0_2, &SCUX_FROM_FFDIR_FFD0_3 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define SCUX_FROM_FFDIR_FFD0_0 (*(struct st_scux_from_ffdir_ffd0_n *)&SCUX.FFDIR_FFD0_0) /* SCUX_FROM_FFDIR_FFD0_0 */
#define SCUX_FROM_FFDIR_FFD0_1 (*(struct st_scux_from_ffdir_ffd0_n *)&SCUX.FFDIR_FFD0_1) /* SCUX_FROM_FFDIR_FFD0_1 */
#define SCUX_FROM_FFDIR_FFD0_2 (*(struct st_scux_from_ffdir_ffd0_n *)&SCUX.FFDIR_FFD0_2) /* SCUX_FROM_FFDIR_FFD0_2 */
#define SCUX_FROM_FFDIR_FFD0_3 (*(struct st_scux_from_ffdir_ffd0_n *)&SCUX.FFDIR_FFD0_3) /* SCUX_FROM_FFDIR_FFD0_3 */


/* Channnel array defines of SCUX_FROM_OPCIR_OPC0_0_ARRAY */
/*(Sample) value = SCUX_FROM_OPCIR_OPC0_0_ARRAY[ channel ]->OPCIR_OPC0_0; */
#define SCUX_FROM_OPCIR_OPC0_0_ARRAY_COUNT  4
#define SCUX_FROM_OPCIR_OPC0_0_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &SCUX_FROM_OPCIR_OPC0_0, &SCUX_FROM_OPCIR_OPC0_1, &SCUX_FROM_OPCIR_OPC0_2, &SCUX_FROM_OPCIR_OPC0_3 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define SCUX_FROM_OPCIR_OPC0_0 (*(struct st_scux_from_opcir_opc0_n *)&SCUX.OPCIR_OPC0_0) /* SCUX_FROM_OPCIR_OPC0_0 */
#define SCUX_FROM_OPCIR_OPC0_1 (*(struct st_scux_from_opcir_opc0_n *)&SCUX.OPCIR_OPC0_1) /* SCUX_FROM_OPCIR_OPC0_1 */
#define SCUX_FROM_OPCIR_OPC0_2 (*(struct st_scux_from_opcir_opc0_n *)&SCUX.OPCIR_OPC0_2) /* SCUX_FROM_OPCIR_OPC0_2 */
#define SCUX_FROM_OPCIR_OPC0_3 (*(struct st_scux_from_opcir_opc0_n *)&SCUX.OPCIR_OPC0_3) /* SCUX_FROM_OPCIR_OPC0_3 */


/* Channnel array defines of SCUX_FROM_IPCIR_IPC0_0_ARRAY */
/*(Sample) value = SCUX_FROM_IPCIR_IPC0_0_ARRAY[ channel ]->IPCIR_IPC0_0; */
#define SCUX_FROM_IPCIR_IPC0_0_ARRAY_COUNT  4
#define SCUX_FROM_IPCIR_IPC0_0_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &SCUX_FROM_IPCIR_IPC0_0, &SCUX_FROM_IPCIR_IPC0_1, &SCUX_FROM_IPCIR_IPC0_2, &SCUX_FROM_IPCIR_IPC0_3 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define SCUX_FROM_IPCIR_IPC0_0 (*(struct st_scux_from_ipcir_ipc0_n *)&SCUX.IPCIR_IPC0_0) /* SCUX_FROM_IPCIR_IPC0_0 */
#define SCUX_FROM_IPCIR_IPC0_1 (*(struct st_scux_from_ipcir_ipc0_n *)&SCUX.IPCIR_IPC0_1) /* SCUX_FROM_IPCIR_IPC0_1 */
#define SCUX_FROM_IPCIR_IPC0_2 (*(struct st_scux_from_ipcir_ipc0_n *)&SCUX.IPCIR_IPC0_2) /* SCUX_FROM_IPCIR_IPC0_2 */
#define SCUX_FROM_IPCIR_IPC0_3 (*(struct st_scux_from_ipcir_ipc0_n *)&SCUX.IPCIR_IPC0_3) /* SCUX_FROM_IPCIR_IPC0_3 */

/* End of channnel array defines of SCUX */


#define SCUXIPCIR_IPC0_0 SCUX.IPCIR_IPC0_0
#define SCUXIPSLR_IPC0_0 SCUX.IPSLR_IPC0_0
#define SCUXIPCIR_IPC0_1 SCUX.IPCIR_IPC0_1
#define SCUXIPSLR_IPC0_1 SCUX.IPSLR_IPC0_1
#define SCUXIPCIR_IPC0_2 SCUX.IPCIR_IPC0_2
#define SCUXIPSLR_IPC0_2 SCUX.IPSLR_IPC0_2
#define SCUXIPCIR_IPC0_3 SCUX.IPCIR_IPC0_3
#define SCUXIPSLR_IPC0_3 SCUX.IPSLR_IPC0_3
#define SCUXOPCIR_OPC0_0 SCUX.OPCIR_OPC0_0
#define SCUXOPSLR_OPC0_0 SCUX.OPSLR_OPC0_0
#define SCUXOPCIR_OPC0_1 SCUX.OPCIR_OPC0_1
#define SCUXOPSLR_OPC0_1 SCUX.OPSLR_OPC0_1
#define SCUXOPCIR_OPC0_2 SCUX.OPCIR_OPC0_2
#define SCUXOPSLR_OPC0_2 SCUX.OPSLR_OPC0_2
#define SCUXOPCIR_OPC0_3 SCUX.OPCIR_OPC0_3
#define SCUXOPSLR_OPC0_3 SCUX.OPSLR_OPC0_3
#define SCUXFFDIR_FFD0_0 SCUX.FFDIR_FFD0_0
#define SCUXFDAIR_FFD0_0 SCUX.FDAIR_FFD0_0
#define SCUXDRQSR_FFD0_0 SCUX.DRQSR_FFD0_0
#define SCUXFFDPR_FFD0_0 SCUX.FFDPR_FFD0_0
#define SCUXFFDBR_FFD0_0 SCUX.FFDBR_FFD0_0
#define SCUXDEVMR_FFD0_0 SCUX.DEVMR_FFD0_0
#define SCUXDEVCR_FFD0_0 SCUX.DEVCR_FFD0_0
#define SCUXFFDIR_FFD0_1 SCUX.FFDIR_FFD0_1
#define SCUXFDAIR_FFD0_1 SCUX.FDAIR_FFD0_1
#define SCUXDRQSR_FFD0_1 SCUX.DRQSR_FFD0_1
#define SCUXFFDPR_FFD0_1 SCUX.FFDPR_FFD0_1
#define SCUXFFDBR_FFD0_1 SCUX.FFDBR_FFD0_1
#define SCUXDEVMR_FFD0_1 SCUX.DEVMR_FFD0_1
#define SCUXDEVCR_FFD0_1 SCUX.DEVCR_FFD0_1
#define SCUXFFDIR_FFD0_2 SCUX.FFDIR_FFD0_2
#define SCUXFDAIR_FFD0_2 SCUX.FDAIR_FFD0_2
#define SCUXDRQSR_FFD0_2 SCUX.DRQSR_FFD0_2
#define SCUXFFDPR_FFD0_2 SCUX.FFDPR_FFD0_2
#define SCUXFFDBR_FFD0_2 SCUX.FFDBR_FFD0_2
#define SCUXDEVMR_FFD0_2 SCUX.DEVMR_FFD0_2
#define SCUXDEVCR_FFD0_2 SCUX.DEVCR_FFD0_2
#define SCUXFFDIR_FFD0_3 SCUX.FFDIR_FFD0_3
#define SCUXFDAIR_FFD0_3 SCUX.FDAIR_FFD0_3
#define SCUXDRQSR_FFD0_3 SCUX.DRQSR_FFD0_3
#define SCUXFFDPR_FFD0_3 SCUX.FFDPR_FFD0_3
#define SCUXFFDBR_FFD0_3 SCUX.FFDBR_FFD0_3
#define SCUXDEVMR_FFD0_3 SCUX.DEVMR_FFD0_3
#define SCUXDEVCR_FFD0_3 SCUX.DEVCR_FFD0_3
#define SCUXFFUIR_FFU0_0 SCUX.FFUIR_FFU0_0
#define SCUXFUAIR_FFU0_0 SCUX.FUAIR_FFU0_0
#define SCUXURQSR_FFU0_0 SCUX.URQSR_FFU0_0
#define SCUXFFUPR_FFU0_0 SCUX.FFUPR_FFU0_0
#define SCUXUEVMR_FFU0_0 SCUX.UEVMR_FFU0_0
#define SCUXUEVCR_FFU0_0 SCUX.UEVCR_FFU0_0
#define SCUXFFUIR_FFU0_1 SCUX.FFUIR_FFU0_1
#define SCUXFUAIR_FFU0_1 SCUX.FUAIR_FFU0_1
#define SCUXURQSR_FFU0_1 SCUX.URQSR_FFU0_1
#define SCUXFFUPR_FFU0_1 SCUX.FFUPR_FFU0_1
#define SCUXUEVMR_FFU0_1 SCUX.UEVMR_FFU0_1
#define SCUXUEVCR_FFU0_1 SCUX.UEVCR_FFU0_1
#define SCUXFFUIR_FFU0_2 SCUX.FFUIR_FFU0_2
#define SCUXFUAIR_FFU0_2 SCUX.FUAIR_FFU0_2
#define SCUXURQSR_FFU0_2 SCUX.URQSR_FFU0_2
#define SCUXFFUPR_FFU0_2 SCUX.FFUPR_FFU0_2
#define SCUXUEVMR_FFU0_2 SCUX.UEVMR_FFU0_2
#define SCUXUEVCR_FFU0_2 SCUX.UEVCR_FFU0_2
#define SCUXFFUIR_FFU0_3 SCUX.FFUIR_FFU0_3
#define SCUXFUAIR_FFU0_3 SCUX.FUAIR_FFU0_3
#define SCUXURQSR_FFU0_3 SCUX.URQSR_FFU0_3
#define SCUXFFUPR_FFU0_3 SCUX.FFUPR_FFU0_3
#define SCUXUEVMR_FFU0_3 SCUX.UEVMR_FFU0_3
#define SCUXUEVCR_FFU0_3 SCUX.UEVCR_FFU0_3
#define SCUXSRCIR0_2SRC0_0 SCUX.SRCIR0_2SRC0_0
#define SCUXSADIR0_2SRC0_0 SCUX.SADIR0_2SRC0_0
#define SCUXSRCBR0_2SRC0_0 SCUX.SRCBR0_2SRC0_0
#define SCUXIFSCR0_2SRC0_0 SCUX.IFSCR0_2SRC0_0
#define SCUXIFSVR0_2SRC0_0 SCUX.IFSVR0_2SRC0_0
#define SCUXSRCCR0_2SRC0_0 SCUX.SRCCR0_2SRC0_0
#define SCUXMNFSR0_2SRC0_0 SCUX.MNFSR0_2SRC0_0
#define SCUXBFSSR0_2SRC0_0 SCUX.BFSSR0_2SRC0_0
#define SCUXSC2SR0_2SRC0_0 SCUX.SC2SR0_2SRC0_0
#define SCUXWATSR0_2SRC0_0 SCUX.WATSR0_2SRC0_0
#define SCUXSEVMR0_2SRC0_0 SCUX.SEVMR0_2SRC0_0
#define SCUXSEVCR0_2SRC0_0 SCUX.SEVCR0_2SRC0_0
#define SCUXSRCIR1_2SRC0_0 SCUX.SRCIR1_2SRC0_0
#define SCUXSADIR1_2SRC0_0 SCUX.SADIR1_2SRC0_0
#define SCUXSRCBR1_2SRC0_0 SCUX.SRCBR1_2SRC0_0
#define SCUXIFSCR1_2SRC0_0 SCUX.IFSCR1_2SRC0_0
#define SCUXIFSVR1_2SRC0_0 SCUX.IFSVR1_2SRC0_0
#define SCUXSRCCR1_2SRC0_0 SCUX.SRCCR1_2SRC0_0
#define SCUXMNFSR1_2SRC0_0 SCUX.MNFSR1_2SRC0_0
#define SCUXBFSSR1_2SRC0_0 SCUX.BFSSR1_2SRC0_0
#define SCUXSC2SR1_2SRC0_0 SCUX.SC2SR1_2SRC0_0
#define SCUXWATSR1_2SRC0_0 SCUX.WATSR1_2SRC0_0
#define SCUXSEVMR1_2SRC0_0 SCUX.SEVMR1_2SRC0_0
#define SCUXSEVCR1_2SRC0_0 SCUX.SEVCR1_2SRC0_0
#define SCUXSRCIRR_2SRC0_0 SCUX.SRCIRR_2SRC0_0
#define SCUXSRCIR0_2SRC0_1 SCUX.SRCIR0_2SRC0_1
#define SCUXSADIR0_2SRC0_1 SCUX.SADIR0_2SRC0_1
#define SCUXSRCBR0_2SRC0_1 SCUX.SRCBR0_2SRC0_1
#define SCUXIFSCR0_2SRC0_1 SCUX.IFSCR0_2SRC0_1
#define SCUXIFSVR0_2SRC0_1 SCUX.IFSVR0_2SRC0_1
#define SCUXSRCCR0_2SRC0_1 SCUX.SRCCR0_2SRC0_1
#define SCUXMNFSR0_2SRC0_1 SCUX.MNFSR0_2SRC0_1
#define SCUXBFSSR0_2SRC0_1 SCUX.BFSSR0_2SRC0_1
#define SCUXSC2SR0_2SRC0_1 SCUX.SC2SR0_2SRC0_1
#define SCUXWATSR0_2SRC0_1 SCUX.WATSR0_2SRC0_1
#define SCUXSEVMR0_2SRC0_1 SCUX.SEVMR0_2SRC0_1
#define SCUXSEVCR0_2SRC0_1 SCUX.SEVCR0_2SRC0_1
#define SCUXSRCIR1_2SRC0_1 SCUX.SRCIR1_2SRC0_1
#define SCUXSADIR1_2SRC0_1 SCUX.SADIR1_2SRC0_1
#define SCUXSRCBR1_2SRC0_1 SCUX.SRCBR1_2SRC0_1
#define SCUXIFSCR1_2SRC0_1 SCUX.IFSCR1_2SRC0_1
#define SCUXIFSVR1_2SRC0_1 SCUX.IFSVR1_2SRC0_1
#define SCUXSRCCR1_2SRC0_1 SCUX.SRCCR1_2SRC0_1
#define SCUXMNFSR1_2SRC0_1 SCUX.MNFSR1_2SRC0_1
#define SCUXBFSSR1_2SRC0_1 SCUX.BFSSR1_2SRC0_1
#define SCUXSC2SR1_2SRC0_1 SCUX.SC2SR1_2SRC0_1
#define SCUXWATSR1_2SRC0_1 SCUX.WATSR1_2SRC0_1
#define SCUXSEVMR1_2SRC0_1 SCUX.SEVMR1_2SRC0_1
#define SCUXSEVCR1_2SRC0_1 SCUX.SEVCR1_2SRC0_1
#define SCUXSRCIRR_2SRC0_1 SCUX.SRCIRR_2SRC0_1
#define SCUXDVUIR_DVU0_0 SCUX.DVUIR_DVU0_0
#define SCUXVADIR_DVU0_0 SCUX.VADIR_DVU0_0
#define SCUXDVUBR_DVU0_0 SCUX.DVUBR_DVU0_0
#define SCUXDVUCR_DVU0_0 SCUX.DVUCR_DVU0_0
#define SCUXZCMCR_DVU0_0 SCUX.ZCMCR_DVU0_0
#define SCUXVRCTR_DVU0_0 SCUX.VRCTR_DVU0_0
#define SCUXVRPDR_DVU0_0 SCUX.VRPDR_DVU0_0
#define SCUXVRDBR_DVU0_0 SCUX.VRDBR_DVU0_0
#define SCUXVRWTR_DVU0_0 SCUX.VRWTR_DVU0_0
#define SCUXVOL0R_DVU0_0 SCUX.VOL0R_DVU0_0
#define SCUXVOL1R_DVU0_0 SCUX.VOL1R_DVU0_0
#define SCUXVOL2R_DVU0_0 SCUX.VOL2R_DVU0_0
#define SCUXVOL3R_DVU0_0 SCUX.VOL3R_DVU0_0
#define SCUXVOL4R_DVU0_0 SCUX.VOL4R_DVU0_0
#define SCUXVOL5R_DVU0_0 SCUX.VOL5R_DVU0_0
#define SCUXVOL6R_DVU0_0 SCUX.VOL6R_DVU0_0
#define SCUXVOL7R_DVU0_0 SCUX.VOL7R_DVU0_0
#define SCUXDVUER_DVU0_0 SCUX.DVUER_DVU0_0
#define SCUXDVUSR_DVU0_0 SCUX.DVUSR_DVU0_0
#define SCUXVEVMR_DVU0_0 SCUX.VEVMR_DVU0_0
#define SCUXVEVCR_DVU0_0 SCUX.VEVCR_DVU0_0
#define SCUXDVUIR_DVU0_1 SCUX.DVUIR_DVU0_1
#define SCUXVADIR_DVU0_1 SCUX.VADIR_DVU0_1
#define SCUXDVUBR_DVU0_1 SCUX.DVUBR_DVU0_1
#define SCUXDVUCR_DVU0_1 SCUX.DVUCR_DVU0_1
#define SCUXZCMCR_DVU0_1 SCUX.ZCMCR_DVU0_1
#define SCUXVRCTR_DVU0_1 SCUX.VRCTR_DVU0_1
#define SCUXVRPDR_DVU0_1 SCUX.VRPDR_DVU0_1
#define SCUXVRDBR_DVU0_1 SCUX.VRDBR_DVU0_1
#define SCUXVRWTR_DVU0_1 SCUX.VRWTR_DVU0_1
#define SCUXVOL0R_DVU0_1 SCUX.VOL0R_DVU0_1
#define SCUXVOL1R_DVU0_1 SCUX.VOL1R_DVU0_1
#define SCUXVOL2R_DVU0_1 SCUX.VOL2R_DVU0_1
#define SCUXVOL3R_DVU0_1 SCUX.VOL3R_DVU0_1
#define SCUXVOL4R_DVU0_1 SCUX.VOL4R_DVU0_1
#define SCUXVOL5R_DVU0_1 SCUX.VOL5R_DVU0_1
#define SCUXVOL6R_DVU0_1 SCUX.VOL6R_DVU0_1
#define SCUXVOL7R_DVU0_1 SCUX.VOL7R_DVU0_1
#define SCUXDVUER_DVU0_1 SCUX.DVUER_DVU0_1
#define SCUXDVUSR_DVU0_1 SCUX.DVUSR_DVU0_1
#define SCUXVEVMR_DVU0_1 SCUX.VEVMR_DVU0_1
#define SCUXVEVCR_DVU0_1 SCUX.VEVCR_DVU0_1
#define SCUXDVUIR_DVU0_2 SCUX.DVUIR_DVU0_2
#define SCUXVADIR_DVU0_2 SCUX.VADIR_DVU0_2
#define SCUXDVUBR_DVU0_2 SCUX.DVUBR_DVU0_2
#define SCUXDVUCR_DVU0_2 SCUX.DVUCR_DVU0_2
#define SCUXZCMCR_DVU0_2 SCUX.ZCMCR_DVU0_2
#define SCUXVRCTR_DVU0_2 SCUX.VRCTR_DVU0_2
#define SCUXVRPDR_DVU0_2 SCUX.VRPDR_DVU0_2
#define SCUXVRDBR_DVU0_2 SCUX.VRDBR_DVU0_2
#define SCUXVRWTR_DVU0_2 SCUX.VRWTR_DVU0_2
#define SCUXVOL0R_DVU0_2 SCUX.VOL0R_DVU0_2
#define SCUXVOL1R_DVU0_2 SCUX.VOL1R_DVU0_2
#define SCUXVOL2R_DVU0_2 SCUX.VOL2R_DVU0_2
#define SCUXVOL3R_DVU0_2 SCUX.VOL3R_DVU0_2
#define SCUXVOL4R_DVU0_2 SCUX.VOL4R_DVU0_2
#define SCUXVOL5R_DVU0_2 SCUX.VOL5R_DVU0_2
#define SCUXVOL6R_DVU0_2 SCUX.VOL6R_DVU0_2
#define SCUXVOL7R_DVU0_2 SCUX.VOL7R_DVU0_2
#define SCUXDVUER_DVU0_2 SCUX.DVUER_DVU0_2
#define SCUXDVUSR_DVU0_2 SCUX.DVUSR_DVU0_2
#define SCUXVEVMR_DVU0_2 SCUX.VEVMR_DVU0_2
#define SCUXVEVCR_DVU0_2 SCUX.VEVCR_DVU0_2
#define SCUXDVUIR_DVU0_3 SCUX.DVUIR_DVU0_3
#define SCUXVADIR_DVU0_3 SCUX.VADIR_DVU0_3
#define SCUXDVUBR_DVU0_3 SCUX.DVUBR_DVU0_3
#define SCUXDVUCR_DVU0_3 SCUX.DVUCR_DVU0_3
#define SCUXZCMCR_DVU0_3 SCUX.ZCMCR_DVU0_3
#define SCUXVRCTR_DVU0_3 SCUX.VRCTR_DVU0_3
#define SCUXVRPDR_DVU0_3 SCUX.VRPDR_DVU0_3
#define SCUXVRDBR_DVU0_3 SCUX.VRDBR_DVU0_3
#define SCUXVRWTR_DVU0_3 SCUX.VRWTR_DVU0_3
#define SCUXVOL0R_DVU0_3 SCUX.VOL0R_DVU0_3
#define SCUXVOL1R_DVU0_3 SCUX.VOL1R_DVU0_3
#define SCUXVOL2R_DVU0_3 SCUX.VOL2R_DVU0_3
#define SCUXVOL3R_DVU0_3 SCUX.VOL3R_DVU0_3
#define SCUXVOL4R_DVU0_3 SCUX.VOL4R_DVU0_3
#define SCUXVOL5R_DVU0_3 SCUX.VOL5R_DVU0_3
#define SCUXVOL6R_DVU0_3 SCUX.VOL6R_DVU0_3
#define SCUXVOL7R_DVU0_3 SCUX.VOL7R_DVU0_3
#define SCUXDVUER_DVU0_3 SCUX.DVUER_DVU0_3
#define SCUXDVUSR_DVU0_3 SCUX.DVUSR_DVU0_3
#define SCUXVEVMR_DVU0_3 SCUX.VEVMR_DVU0_3
#define SCUXVEVCR_DVU0_3 SCUX.VEVCR_DVU0_3
#define SCUXMIXIR_MIX0_0 SCUX.MIXIR_MIX0_0
#define SCUXMADIR_MIX0_0 SCUX.MADIR_MIX0_0
#define SCUXMIXBR_MIX0_0 SCUX.MIXBR_MIX0_0
#define SCUXMIXMR_MIX0_0 SCUX.MIXMR_MIX0_0
#define SCUXMVPDR_MIX0_0 SCUX.MVPDR_MIX0_0
#define SCUXMDBAR_MIX0_0 SCUX.MDBAR_MIX0_0
#define SCUXMDBBR_MIX0_0 SCUX.MDBBR_MIX0_0
#define SCUXMDBCR_MIX0_0 SCUX.MDBCR_MIX0_0
#define SCUXMDBDR_MIX0_0 SCUX.MDBDR_MIX0_0
#define SCUXMDBER_MIX0_0 SCUX.MDBER_MIX0_0
#define SCUXMIXSR_MIX0_0 SCUX.MIXSR_MIX0_0
#define SCUXSWRSR_CIM SCUX.SWRSR_CIM
#define SCUXDMACR_CIM SCUX.DMACR_CIM
#define SCUXDMATD0_CIM SCUX.DMATD0_CIM.UINT32
#define SCUXDMATD0_CIML SCUX.DMATD0_CIM.UINT16[L]
#define SCUXDMATD0_CIMH SCUX.DMATD0_CIM.UINT16[H]
#define SCUXDMATD1_CIM SCUX.DMATD1_CIM.UINT32
#define SCUXDMATD1_CIML SCUX.DMATD1_CIM.UINT16[L]
#define SCUXDMATD1_CIMH SCUX.DMATD1_CIM.UINT16[H]
#define SCUXDMATD2_CIM SCUX.DMATD2_CIM.UINT32
#define SCUXDMATD2_CIML SCUX.DMATD2_CIM.UINT16[L]
#define SCUXDMATD2_CIMH SCUX.DMATD2_CIM.UINT16[H]
#define SCUXDMATD3_CIM SCUX.DMATD3_CIM.UINT32
#define SCUXDMATD3_CIML SCUX.DMATD3_CIM.UINT16[L]
#define SCUXDMATD3_CIMH SCUX.DMATD3_CIM.UINT16[H]
#define SCUXDMATU0_CIM SCUX.DMATU0_CIM.UINT32
#define SCUXDMATU0_CIML SCUX.DMATU0_CIM.UINT16[L]
#define SCUXDMATU0_CIMH SCUX.DMATU0_CIM.UINT16[H]
#define SCUXDMATU1_CIM SCUX.DMATU1_CIM.UINT32
#define SCUXDMATU1_CIML SCUX.DMATU1_CIM.UINT16[L]
#define SCUXDMATU1_CIMH SCUX.DMATU1_CIM.UINT16[H]
#define SCUXDMATU2_CIM SCUX.DMATU2_CIM.UINT32
#define SCUXDMATU2_CIML SCUX.DMATU2_CIM.UINT16[L]
#define SCUXDMATU2_CIMH SCUX.DMATU2_CIM.UINT16[H]
#define SCUXDMATU3_CIM SCUX.DMATU3_CIM.UINT32
#define SCUXDMATU3_CIML SCUX.DMATU3_CIM.UINT16[L]
#define SCUXDMATU3_CIMH SCUX.DMATU3_CIM.UINT16[H]
#define SCUXSSIRSEL_CIM SCUX.SSIRSEL_CIM
#define SCUXFDTSEL0_CIM SCUX.FDTSEL0_CIM
#define SCUXFDTSEL1_CIM SCUX.FDTSEL1_CIM
#define SCUXFDTSEL2_CIM SCUX.FDTSEL2_CIM
#define SCUXFDTSEL3_CIM SCUX.FDTSEL3_CIM
#define SCUXFUTSEL0_CIM SCUX.FUTSEL0_CIM
#define SCUXFUTSEL1_CIM SCUX.FUTSEL1_CIM
#define SCUXFUTSEL2_CIM SCUX.FUTSEL2_CIM
#define SCUXFUTSEL3_CIM SCUX.FUTSEL3_CIM
#define SCUXSSIPMD_CIM SCUX.SSIPMD_CIM
#define SCUXSSICTRL_CIM SCUX.SSICTRL_CIM
#define SCUXSRCRSEL0_CIM SCUX.SRCRSEL0_CIM
#define SCUXSRCRSEL1_CIM SCUX.SRCRSEL1_CIM
#define SCUXSRCRSEL2_CIM SCUX.SRCRSEL2_CIM
#define SCUXSRCRSEL3_CIM SCUX.SRCRSEL3_CIM
#define SCUXMIXRSEL_CIM SCUX.MIXRSEL_CIM
/* <-SEC M1.10.1 */
/* <-QAC 0639 */
#endif
