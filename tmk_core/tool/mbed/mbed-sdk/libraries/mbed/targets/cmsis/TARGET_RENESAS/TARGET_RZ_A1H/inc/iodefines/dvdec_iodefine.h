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
* File Name : dvdec_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef DVDEC_IODEFINE_H
#define DVDEC_IODEFINE_H
/* ->SEC M1.10.1 : Not magic number */

struct st_dvdec
{                                                          /* DVDEC            */
    volatile uint16_t ADCCR1;                                 /*  ADCCR1          */
    volatile uint8_t   dummy1[4];                              /*                  */
#define DVDEC_TGCRn_COUNT 3
    volatile uint16_t TGCR1;                                  /*  TGCR1           */
    volatile uint16_t TGCR2;                                  /*  TGCR2           */
    volatile uint16_t TGCR3;                                  /*  TGCR3           */
    volatile uint8_t   dummy2[6];                              /*                  */
#define DVDEC_SYNSCRn_COUNT 5
    volatile uint16_t SYNSCR1;                                /*  SYNSCR1         */
    volatile uint16_t SYNSCR2;                                /*  SYNSCR2         */
    volatile uint16_t SYNSCR3;                                /*  SYNSCR3         */
    volatile uint16_t SYNSCR4;                                /*  SYNSCR4         */
    volatile uint16_t SYNSCR5;                                /*  SYNSCR5         */
#define DVDEC_HAFCCRn_COUNT 3
    volatile uint16_t HAFCCR1;                                /*  HAFCCR1         */
    volatile uint16_t HAFCCR2;                                /*  HAFCCR2         */
    volatile uint16_t HAFCCR3;                                /*  HAFCCR3         */
    volatile uint16_t VCDWCR1;                                /*  VCDWCR1         */
    volatile uint8_t   dummy3[4];                              /*                  */
#define DVDEC_DCPCRn_COUNT 8
    volatile uint16_t DCPCR1;                                 /*  DCPCR1          */
    volatile uint16_t DCPCR2;                                 /*  DCPCR2          */
    volatile uint16_t DCPCR3;                                 /*  DCPCR3          */
    volatile uint16_t DCPCR4;                                 /*  DCPCR4          */
    volatile uint16_t DCPCR5;                                 /*  DCPCR5          */
    volatile uint16_t DCPCR6;                                 /*  DCPCR6          */
    volatile uint16_t DCPCR7;                                 /*  DCPCR7          */
    volatile uint16_t DCPCR8;                                 /*  DCPCR8          */
    volatile uint16_t NSDCR;                                  /*  NSDCR           */
    volatile uint16_t BTLCR;                                  /*  BTLCR           */
    volatile uint16_t BTGPCR;                                 /*  BTGPCR          */
#define DVDEC_ACCCRn_COUNT 3
    volatile uint16_t ACCCR1;                                 /*  ACCCR1          */
    volatile uint16_t ACCCR2;                                 /*  ACCCR2          */
    volatile uint16_t ACCCR3;                                 /*  ACCCR3          */
    volatile uint16_t TINTCR;                                 /*  TINTCR          */
    volatile uint16_t YCDCR;                                  /*  YCDCR           */
#define DVDEC_AGCCRn_COUNT 2
    volatile uint16_t AGCCR1;                                 /*  AGCCR1          */
    volatile uint16_t AGCCR2;                                 /*  AGCCR2          */
    volatile uint16_t PKLIMITCR;                              /*  PKLIMITCR       */
#define DVDEC_RGORCRn_COUNT 7
    volatile uint16_t RGORCR1;                                /*  RGORCR1         */
    volatile uint16_t RGORCR2;                                /*  RGORCR2         */
    volatile uint16_t RGORCR3;                                /*  RGORCR3         */
    volatile uint16_t RGORCR4;                                /*  RGORCR4         */
    volatile uint16_t RGORCR5;                                /*  RGORCR5         */
    volatile uint16_t RGORCR6;                                /*  RGORCR6         */
    volatile uint16_t RGORCR7;                                /*  RGORCR7         */
    volatile uint8_t   dummy4[24];                             /*                  */
    volatile uint16_t AFCPFCR;                                /*  AFCPFCR         */
    volatile uint16_t RUPDCR;                                 /*  RUPDCR          */
    volatile uint16_t VSYNCSR;                                /*  VSYNCSR         */
    volatile uint16_t HSYNCSR;                                /*  HSYNCSR         */
#define DVDEC_DCPSRn_COUNT 2
    volatile uint16_t DCPSR1;                                 /*  DCPSR1          */
    volatile uint16_t DCPSR2;                                 /*  DCPSR2          */
    volatile uint8_t   dummy5[4];                              /*                  */
    volatile uint16_t NSDSR;                                  /*  NSDSR           */
#define DVDEC_CROMASRn_COUNT 2
    volatile uint16_t CROMASR1;                               /*  CROMASR1        */
    volatile uint16_t CROMASR2;                               /*  CROMASR2        */
    volatile uint16_t SYNCSSR;                                /*  SYNCSSR         */
#define DVDEC_AGCCSRn_COUNT 2
    volatile uint16_t AGCCSR1;                                /*  AGCCSR1         */
    volatile uint16_t AGCCSR2;                                /*  AGCCSR2         */
    volatile uint8_t   dummy6[108];                            /*                  */
#define DVDEC_YCSCRn_COUNT 7
    volatile uint16_t YCSCR3;                                 /*  YCSCR3          */
    volatile uint16_t YCSCR4;                                 /*  YCSCR4          */
    volatile uint16_t YCSCR5;                                 /*  YCSCR5          */
    volatile uint16_t YCSCR6;                                 /*  YCSCR6          */
    volatile uint16_t YCSCR7;                                 /*  YCSCR7          */
    volatile uint16_t YCSCR8;                                 /*  YCSCR8          */
    volatile uint16_t YCSCR9;                                 /*  YCSCR9          */
    volatile uint8_t   dummy7[2];                              /*                  */
    volatile uint16_t YCSCR11;                                /*  YCSCR11         */
    volatile uint16_t YCSCR12;                                /*  YCSCR12         */
    volatile uint8_t   dummy8[104];                            /*                  */
    volatile uint16_t DCPCR9;                                 /*  DCPCR9          */
    volatile uint8_t   dummy9[16];                             /*                  */
#define DVDEC_YCTWA_Fn_COUNT 9
    volatile uint16_t YCTWA_F0;                               /*  YCTWA_F0        */
    volatile uint16_t YCTWA_F1;                               /*  YCTWA_F1        */
    volatile uint16_t YCTWA_F2;                               /*  YCTWA_F2        */
    volatile uint16_t YCTWA_F3;                               /*  YCTWA_F3        */
    volatile uint16_t YCTWA_F4;                               /*  YCTWA_F4        */
    volatile uint16_t YCTWA_F5;                               /*  YCTWA_F5        */
    volatile uint16_t YCTWA_F6;                               /*  YCTWA_F6        */
    volatile uint16_t YCTWA_F7;                               /*  YCTWA_F7        */
    volatile uint16_t YCTWA_F8;                               /*  YCTWA_F8        */
#define DVDEC_YCTWB_Fn_COUNT 9
    volatile uint16_t YCTWB_F0;                               /*  YCTWB_F0        */
    volatile uint16_t YCTWB_F1;                               /*  YCTWB_F1        */
    volatile uint16_t YCTWB_F2;                               /*  YCTWB_F2        */
    volatile uint16_t YCTWB_F3;                               /*  YCTWB_F3        */
    volatile uint16_t YCTWB_F4;                               /*  YCTWB_F4        */
    volatile uint16_t YCTWB_F5;                               /*  YCTWB_F5        */
    volatile uint16_t YCTWB_F6;                               /*  YCTWB_F6        */
    volatile uint16_t YCTWB_F7;                               /*  YCTWB_F7        */
    volatile uint16_t YCTWB_F8;                               /*  YCTWB_F8        */
#define DVDEC_YCTNA_Fn_COUNT 9
    volatile uint16_t YCTNA_F0;                               /*  YCTNA_F0        */
    volatile uint16_t YCTNA_F1;                               /*  YCTNA_F1        */
    volatile uint16_t YCTNA_F2;                               /*  YCTNA_F2        */
    volatile uint16_t YCTNA_F3;                               /*  YCTNA_F3        */
    volatile uint16_t YCTNA_F4;                               /*  YCTNA_F4        */
    volatile uint16_t YCTNA_F5;                               /*  YCTNA_F5        */
    volatile uint16_t YCTNA_F6;                               /*  YCTNA_F6        */
    volatile uint16_t YCTNA_F7;                               /*  YCTNA_F7        */
    volatile uint16_t YCTNA_F8;                               /*  YCTNA_F8        */
#define DVDEC_YCTNB_Fn_COUNT 9
    volatile uint16_t YCTNB_F0;                               /*  YCTNB_F0        */
    volatile uint16_t YCTNB_F1;                               /*  YCTNB_F1        */
    volatile uint16_t YCTNB_F2;                               /*  YCTNB_F2        */
    volatile uint16_t YCTNB_F3;                               /*  YCTNB_F3        */
    volatile uint16_t YCTNB_F4;                               /*  YCTNB_F4        */
    volatile uint16_t YCTNB_F5;                               /*  YCTNB_F5        */
    volatile uint16_t YCTNB_F6;                               /*  YCTNB_F6        */
    volatile uint16_t YCTNB_F7;                               /*  YCTNB_F7        */
    volatile uint16_t YCTNB_F8;                               /*  YCTNB_F8        */
    volatile uint8_t   dummy10[38];                            /*                  */
    volatile uint16_t YGAINCR;                                /*  YGAINCR         */
    volatile uint16_t CBGAINCR;                               /*  CBGAINCR        */
    volatile uint16_t CRGAINCR;                               /*  CRGAINCR        */
    volatile uint8_t   dummy11[122];                           /*                  */
    volatile uint16_t PGA_UPDATE;                             /*  PGA_UPDATE      */
    volatile uint16_t PGACR;                                  /*  PGACR           */
    volatile uint16_t ADCCR2;                                 /*  ADCCR2          */
};


#define DVDEC1  (*(struct st_dvdec   *)0xFCFFA008uL) /* DVDEC1 */
#define DVDEC0  (*(struct st_dvdec   *)0xFCFFB808uL) /* DVDEC0 */


/* Start of channnel array defines of DVDEC */

/* Channnel array defines of DVDEC */
/*(Sample) value = DVDEC[ channel ]->ADCCR1; */
#define DVDEC_COUNT  2
#define DVDEC_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &DVDEC0, &DVDEC1 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */

/* End of channnel array defines of DVDEC */


#define ADCCR1_1 DVDEC1.ADCCR1
#define TGCR1_1 DVDEC1.TGCR1
#define TGCR2_1 DVDEC1.TGCR2
#define TGCR3_1 DVDEC1.TGCR3
#define SYNSCR1_1 DVDEC1.SYNSCR1
#define SYNSCR2_1 DVDEC1.SYNSCR2
#define SYNSCR3_1 DVDEC1.SYNSCR3
#define SYNSCR4_1 DVDEC1.SYNSCR4
#define SYNSCR5_1 DVDEC1.SYNSCR5
#define HAFCCR1_1 DVDEC1.HAFCCR1
#define HAFCCR2_1 DVDEC1.HAFCCR2
#define HAFCCR3_1 DVDEC1.HAFCCR3
#define VCDWCR1_1 DVDEC1.VCDWCR1
#define DCPCR1_1 DVDEC1.DCPCR1
#define DCPCR2_1 DVDEC1.DCPCR2
#define DCPCR3_1 DVDEC1.DCPCR3
#define DCPCR4_1 DVDEC1.DCPCR4
#define DCPCR5_1 DVDEC1.DCPCR5
#define DCPCR6_1 DVDEC1.DCPCR6
#define DCPCR7_1 DVDEC1.DCPCR7
#define DCPCR8_1 DVDEC1.DCPCR8
#define NSDCR_1 DVDEC1.NSDCR
#define BTLCR_1 DVDEC1.BTLCR
#define BTGPCR_1 DVDEC1.BTGPCR
#define ACCCR1_1 DVDEC1.ACCCR1
#define ACCCR2_1 DVDEC1.ACCCR2
#define ACCCR3_1 DVDEC1.ACCCR3
#define TINTCR_1 DVDEC1.TINTCR
#define YCDCR_1 DVDEC1.YCDCR
#define AGCCR1_1 DVDEC1.AGCCR1
#define AGCCR2_1 DVDEC1.AGCCR2
#define PKLIMITCR_1 DVDEC1.PKLIMITCR
#define RGORCR1_1 DVDEC1.RGORCR1
#define RGORCR2_1 DVDEC1.RGORCR2
#define RGORCR3_1 DVDEC1.RGORCR3
#define RGORCR4_1 DVDEC1.RGORCR4
#define RGORCR5_1 DVDEC1.RGORCR5
#define RGORCR6_1 DVDEC1.RGORCR6
#define RGORCR7_1 DVDEC1.RGORCR7
#define AFCPFCR_1 DVDEC1.AFCPFCR
#define RUPDCR_1 DVDEC1.RUPDCR
#define VSYNCSR_1 DVDEC1.VSYNCSR
#define HSYNCSR_1 DVDEC1.HSYNCSR
#define DCPSR1_1 DVDEC1.DCPSR1
#define DCPSR2_1 DVDEC1.DCPSR2
#define NSDSR_1 DVDEC1.NSDSR
#define CROMASR1_1 DVDEC1.CROMASR1
#define CROMASR2_1 DVDEC1.CROMASR2
#define SYNCSSR_1 DVDEC1.SYNCSSR
#define AGCCSR1_1 DVDEC1.AGCCSR1
#define AGCCSR2_1 DVDEC1.AGCCSR2
#define YCSCR3_1 DVDEC1.YCSCR3
#define YCSCR4_1 DVDEC1.YCSCR4
#define YCSCR5_1 DVDEC1.YCSCR5
#define YCSCR6_1 DVDEC1.YCSCR6
#define YCSCR7_1 DVDEC1.YCSCR7
#define YCSCR8_1 DVDEC1.YCSCR8
#define YCSCR9_1 DVDEC1.YCSCR9
#define YCSCR11_1 DVDEC1.YCSCR11
#define YCSCR12_1 DVDEC1.YCSCR12
#define DCPCR9_1 DVDEC1.DCPCR9
#define YCTWA_F0_1 DVDEC1.YCTWA_F0
#define YCTWA_F1_1 DVDEC1.YCTWA_F1
#define YCTWA_F2_1 DVDEC1.YCTWA_F2
#define YCTWA_F3_1 DVDEC1.YCTWA_F3
#define YCTWA_F4_1 DVDEC1.YCTWA_F4
#define YCTWA_F5_1 DVDEC1.YCTWA_F5
#define YCTWA_F6_1 DVDEC1.YCTWA_F6
#define YCTWA_F7_1 DVDEC1.YCTWA_F7
#define YCTWA_F8_1 DVDEC1.YCTWA_F8
#define YCTWB_F0_1 DVDEC1.YCTWB_F0
#define YCTWB_F1_1 DVDEC1.YCTWB_F1
#define YCTWB_F2_1 DVDEC1.YCTWB_F2
#define YCTWB_F3_1 DVDEC1.YCTWB_F3
#define YCTWB_F4_1 DVDEC1.YCTWB_F4
#define YCTWB_F5_1 DVDEC1.YCTWB_F5
#define YCTWB_F6_1 DVDEC1.YCTWB_F6
#define YCTWB_F7_1 DVDEC1.YCTWB_F7
#define YCTWB_F8_1 DVDEC1.YCTWB_F8
#define YCTNA_F0_1 DVDEC1.YCTNA_F0
#define YCTNA_F1_1 DVDEC1.YCTNA_F1
#define YCTNA_F2_1 DVDEC1.YCTNA_F2
#define YCTNA_F3_1 DVDEC1.YCTNA_F3
#define YCTNA_F4_1 DVDEC1.YCTNA_F4
#define YCTNA_F5_1 DVDEC1.YCTNA_F5
#define YCTNA_F6_1 DVDEC1.YCTNA_F6
#define YCTNA_F7_1 DVDEC1.YCTNA_F7
#define YCTNA_F8_1 DVDEC1.YCTNA_F8
#define YCTNB_F0_1 DVDEC1.YCTNB_F0
#define YCTNB_F1_1 DVDEC1.YCTNB_F1
#define YCTNB_F2_1 DVDEC1.YCTNB_F2
#define YCTNB_F3_1 DVDEC1.YCTNB_F3
#define YCTNB_F4_1 DVDEC1.YCTNB_F4
#define YCTNB_F5_1 DVDEC1.YCTNB_F5
#define YCTNB_F6_1 DVDEC1.YCTNB_F6
#define YCTNB_F7_1 DVDEC1.YCTNB_F7
#define YCTNB_F8_1 DVDEC1.YCTNB_F8
#define YGAINCR_1 DVDEC1.YGAINCR
#define CBGAINCR_1 DVDEC1.CBGAINCR
#define CRGAINCR_1 DVDEC1.CRGAINCR
#define PGA_UPDATE_1 DVDEC1.PGA_UPDATE
#define PGACR_1 DVDEC1.PGACR
#define ADCCR2_1 DVDEC1.ADCCR2
#define ADCCR1_0 DVDEC0.ADCCR1
#define TGCR1_0 DVDEC0.TGCR1
#define TGCR2_0 DVDEC0.TGCR2
#define TGCR3_0 DVDEC0.TGCR3
#define SYNSCR1_0 DVDEC0.SYNSCR1
#define SYNSCR2_0 DVDEC0.SYNSCR2
#define SYNSCR3_0 DVDEC0.SYNSCR3
#define SYNSCR4_0 DVDEC0.SYNSCR4
#define SYNSCR5_0 DVDEC0.SYNSCR5
#define HAFCCR1_0 DVDEC0.HAFCCR1
#define HAFCCR2_0 DVDEC0.HAFCCR2
#define HAFCCR3_0 DVDEC0.HAFCCR3
#define VCDWCR1_0 DVDEC0.VCDWCR1
#define DCPCR1_0 DVDEC0.DCPCR1
#define DCPCR2_0 DVDEC0.DCPCR2
#define DCPCR3_0 DVDEC0.DCPCR3
#define DCPCR4_0 DVDEC0.DCPCR4
#define DCPCR5_0 DVDEC0.DCPCR5
#define DCPCR6_0 DVDEC0.DCPCR6
#define DCPCR7_0 DVDEC0.DCPCR7
#define DCPCR8_0 DVDEC0.DCPCR8
#define NSDCR_0 DVDEC0.NSDCR
#define BTLCR_0 DVDEC0.BTLCR
#define BTGPCR_0 DVDEC0.BTGPCR
#define ACCCR1_0 DVDEC0.ACCCR1
#define ACCCR2_0 DVDEC0.ACCCR2
#define ACCCR3_0 DVDEC0.ACCCR3
#define TINTCR_0 DVDEC0.TINTCR
#define YCDCR_0 DVDEC0.YCDCR
#define AGCCR1_0 DVDEC0.AGCCR1
#define AGCCR2_0 DVDEC0.AGCCR2
#define PKLIMITCR_0 DVDEC0.PKLIMITCR
#define RGORCR1_0 DVDEC0.RGORCR1
#define RGORCR2_0 DVDEC0.RGORCR2
#define RGORCR3_0 DVDEC0.RGORCR3
#define RGORCR4_0 DVDEC0.RGORCR4
#define RGORCR5_0 DVDEC0.RGORCR5
#define RGORCR6_0 DVDEC0.RGORCR6
#define RGORCR7_0 DVDEC0.RGORCR7
#define AFCPFCR_0 DVDEC0.AFCPFCR
#define RUPDCR_0 DVDEC0.RUPDCR
#define VSYNCSR_0 DVDEC0.VSYNCSR
#define HSYNCSR_0 DVDEC0.HSYNCSR
#define DCPSR1_0 DVDEC0.DCPSR1
#define DCPSR2_0 DVDEC0.DCPSR2
#define NSDSR_0 DVDEC0.NSDSR
#define CROMASR1_0 DVDEC0.CROMASR1
#define CROMASR2_0 DVDEC0.CROMASR2
#define SYNCSSR_0 DVDEC0.SYNCSSR
#define AGCCSR1_0 DVDEC0.AGCCSR1
#define AGCCSR2_0 DVDEC0.AGCCSR2
#define YCSCR3_0 DVDEC0.YCSCR3
#define YCSCR4_0 DVDEC0.YCSCR4
#define YCSCR5_0 DVDEC0.YCSCR5
#define YCSCR6_0 DVDEC0.YCSCR6
#define YCSCR7_0 DVDEC0.YCSCR7
#define YCSCR8_0 DVDEC0.YCSCR8
#define YCSCR9_0 DVDEC0.YCSCR9
#define YCSCR11_0 DVDEC0.YCSCR11
#define YCSCR12_0 DVDEC0.YCSCR12
#define DCPCR9_0 DVDEC0.DCPCR9
#define YCTWA_F0_0 DVDEC0.YCTWA_F0
#define YCTWA_F1_0 DVDEC0.YCTWA_F1
#define YCTWA_F2_0 DVDEC0.YCTWA_F2
#define YCTWA_F3_0 DVDEC0.YCTWA_F3
#define YCTWA_F4_0 DVDEC0.YCTWA_F4
#define YCTWA_F5_0 DVDEC0.YCTWA_F5
#define YCTWA_F6_0 DVDEC0.YCTWA_F6
#define YCTWA_F7_0 DVDEC0.YCTWA_F7
#define YCTWA_F8_0 DVDEC0.YCTWA_F8
#define YCTWB_F0_0 DVDEC0.YCTWB_F0
#define YCTWB_F1_0 DVDEC0.YCTWB_F1
#define YCTWB_F2_0 DVDEC0.YCTWB_F2
#define YCTWB_F3_0 DVDEC0.YCTWB_F3
#define YCTWB_F4_0 DVDEC0.YCTWB_F4
#define YCTWB_F5_0 DVDEC0.YCTWB_F5
#define YCTWB_F6_0 DVDEC0.YCTWB_F6
#define YCTWB_F7_0 DVDEC0.YCTWB_F7
#define YCTWB_F8_0 DVDEC0.YCTWB_F8
#define YCTNA_F0_0 DVDEC0.YCTNA_F0
#define YCTNA_F1_0 DVDEC0.YCTNA_F1
#define YCTNA_F2_0 DVDEC0.YCTNA_F2
#define YCTNA_F3_0 DVDEC0.YCTNA_F3
#define YCTNA_F4_0 DVDEC0.YCTNA_F4
#define YCTNA_F5_0 DVDEC0.YCTNA_F5
#define YCTNA_F6_0 DVDEC0.YCTNA_F6
#define YCTNA_F7_0 DVDEC0.YCTNA_F7
#define YCTNA_F8_0 DVDEC0.YCTNA_F8
#define YCTNB_F0_0 DVDEC0.YCTNB_F0
#define YCTNB_F1_0 DVDEC0.YCTNB_F1
#define YCTNB_F2_0 DVDEC0.YCTNB_F2
#define YCTNB_F3_0 DVDEC0.YCTNB_F3
#define YCTNB_F4_0 DVDEC0.YCTNB_F4
#define YCTNB_F5_0 DVDEC0.YCTNB_F5
#define YCTNB_F6_0 DVDEC0.YCTNB_F6
#define YCTNB_F7_0 DVDEC0.YCTNB_F7
#define YCTNB_F8_0 DVDEC0.YCTNB_F8
#define YGAINCR_0 DVDEC0.YGAINCR
#define CBGAINCR_0 DVDEC0.CBGAINCR
#define CRGAINCR_0 DVDEC0.CRGAINCR
#define PGA_UPDATE_0 DVDEC0.PGA_UPDATE
#define PGACR_0 DVDEC0.PGACR
#define ADCCR2_0 DVDEC0.ADCCR2
/* <-SEC M1.10.1 */
#endif
