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
* File Name : dmac_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef DMAC_IODEFINE_H
#define DMAC_IODEFINE_H
/* ->QAC 0639 : Over 127 members (C90) */
/* ->SEC M1.10.1 : Not magic number */

struct st_dmac
{                                                          /* DMAC             */
/* start of struct st_dmac_n */
    volatile uint32_t  N0SA_0;                                 /*  N0SA_0          */
    volatile uint32_t  N0DA_0;                                 /*  N0DA_0          */
    volatile uint32_t  N0TB_0;                                 /*  N0TB_0          */
    volatile uint32_t  N1SA_0;                                 /*  N1SA_0          */
    volatile uint32_t  N1DA_0;                                 /*  N1DA_0          */
    volatile uint32_t  N1TB_0;                                 /*  N1TB_0          */
    volatile uint32_t  CRSA_0;                                 /*  CRSA_0          */
    volatile uint32_t  CRDA_0;                                 /*  CRDA_0          */
    volatile uint32_t  CRTB_0;                                 /*  CRTB_0          */
    volatile uint32_t  CHSTAT_0;                               /*  CHSTAT_0        */
    volatile uint32_t  CHCTRL_0;                               /*  CHCTRL_0        */
    volatile uint32_t  CHCFG_0;                                /*  CHCFG_0         */
    volatile uint32_t  CHITVL_0;                               /*  CHITVL_0        */
    volatile uint32_t  CHEXT_0;                                /*  CHEXT_0         */
    volatile uint32_t  NXLA_0;                                 /*  NXLA_0          */
    volatile uint32_t  CRLA_0;                                 /*  CRLA_0          */
/* end of struct st_dmac_n */
/* start of struct st_dmac_n */
    volatile uint32_t  N0SA_1;                                 /*  N0SA_1          */
    volatile uint32_t  N0DA_1;                                 /*  N0DA_1          */
    volatile uint32_t  N0TB_1;                                 /*  N0TB_1          */
    volatile uint32_t  N1SA_1;                                 /*  N1SA_1          */
    volatile uint32_t  N1DA_1;                                 /*  N1DA_1          */
    volatile uint32_t  N1TB_1;                                 /*  N1TB_1          */
    volatile uint32_t  CRSA_1;                                 /*  CRSA_1          */
    volatile uint32_t  CRDA_1;                                 /*  CRDA_1          */
    volatile uint32_t  CRTB_1;                                 /*  CRTB_1          */
    volatile uint32_t  CHSTAT_1;                               /*  CHSTAT_1        */
    volatile uint32_t  CHCTRL_1;                               /*  CHCTRL_1        */
    volatile uint32_t  CHCFG_1;                                /*  CHCFG_1         */
    volatile uint32_t  CHITVL_1;                               /*  CHITVL_1        */
    volatile uint32_t  CHEXT_1;                                /*  CHEXT_1         */
    volatile uint32_t  NXLA_1;                                 /*  NXLA_1          */
    volatile uint32_t  CRLA_1;                                 /*  CRLA_1          */
/* end of struct st_dmac_n */
/* start of struct st_dmac_n */
    volatile uint32_t  N0SA_2;                                 /*  N0SA_2          */
    volatile uint32_t  N0DA_2;                                 /*  N0DA_2          */
    volatile uint32_t  N0TB_2;                                 /*  N0TB_2          */
    volatile uint32_t  N1SA_2;                                 /*  N1SA_2          */
    volatile uint32_t  N1DA_2;                                 /*  N1DA_2          */
    volatile uint32_t  N1TB_2;                                 /*  N1TB_2          */
    volatile uint32_t  CRSA_2;                                 /*  CRSA_2          */
    volatile uint32_t  CRDA_2;                                 /*  CRDA_2          */
    volatile uint32_t  CRTB_2;                                 /*  CRTB_2          */
    volatile uint32_t  CHSTAT_2;                               /*  CHSTAT_2        */
    volatile uint32_t  CHCTRL_2;                               /*  CHCTRL_2        */
    volatile uint32_t  CHCFG_2;                                /*  CHCFG_2         */
    volatile uint32_t  CHITVL_2;                               /*  CHITVL_2        */
    volatile uint32_t  CHEXT_2;                                /*  CHEXT_2         */
    volatile uint32_t  NXLA_2;                                 /*  NXLA_2          */
    volatile uint32_t  CRLA_2;                                 /*  CRLA_2          */
/* end of struct st_dmac_n */
/* start of struct st_dmac_n */
    volatile uint32_t  N0SA_3;                                 /*  N0SA_3          */
    volatile uint32_t  N0DA_3;                                 /*  N0DA_3          */
    volatile uint32_t  N0TB_3;                                 /*  N0TB_3          */
    volatile uint32_t  N1SA_3;                                 /*  N1SA_3          */
    volatile uint32_t  N1DA_3;                                 /*  N1DA_3          */
    volatile uint32_t  N1TB_3;                                 /*  N1TB_3          */
    volatile uint32_t  CRSA_3;                                 /*  CRSA_3          */
    volatile uint32_t  CRDA_3;                                 /*  CRDA_3          */
    volatile uint32_t  CRTB_3;                                 /*  CRTB_3          */
    volatile uint32_t  CHSTAT_3;                               /*  CHSTAT_3        */
    volatile uint32_t  CHCTRL_3;                               /*  CHCTRL_3        */
    volatile uint32_t  CHCFG_3;                                /*  CHCFG_3         */
    volatile uint32_t  CHITVL_3;                               /*  CHITVL_3        */
    volatile uint32_t  CHEXT_3;                                /*  CHEXT_3         */
    volatile uint32_t  NXLA_3;                                 /*  NXLA_3          */
    volatile uint32_t  CRLA_3;                                 /*  CRLA_3          */
/* end of struct st_dmac_n */
/* start of struct st_dmac_n */
    volatile uint32_t  N0SA_4;                                 /*  N0SA_4          */
    volatile uint32_t  N0DA_4;                                 /*  N0DA_4          */
    volatile uint32_t  N0TB_4;                                 /*  N0TB_4          */
    volatile uint32_t  N1SA_4;                                 /*  N1SA_4          */
    volatile uint32_t  N1DA_4;                                 /*  N1DA_4          */
    volatile uint32_t  N1TB_4;                                 /*  N1TB_4          */
    volatile uint32_t  CRSA_4;                                 /*  CRSA_4          */
    volatile uint32_t  CRDA_4;                                 /*  CRDA_4          */
    volatile uint32_t  CRTB_4;                                 /*  CRTB_4          */
    volatile uint32_t  CHSTAT_4;                               /*  CHSTAT_4        */
    volatile uint32_t  CHCTRL_4;                               /*  CHCTRL_4        */
    volatile uint32_t  CHCFG_4;                                /*  CHCFG_4         */
    volatile uint32_t  CHITVL_4;                               /*  CHITVL_4        */
    volatile uint32_t  CHEXT_4;                                /*  CHEXT_4         */
    volatile uint32_t  NXLA_4;                                 /*  NXLA_4          */
    volatile uint32_t  CRLA_4;                                 /*  CRLA_4          */
/* end of struct st_dmac_n */
/* start of struct st_dmac_n */
    volatile uint32_t  N0SA_5;                                 /*  N0SA_5          */
    volatile uint32_t  N0DA_5;                                 /*  N0DA_5          */
    volatile uint32_t  N0TB_5;                                 /*  N0TB_5          */
    volatile uint32_t  N1SA_5;                                 /*  N1SA_5          */
    volatile uint32_t  N1DA_5;                                 /*  N1DA_5          */
    volatile uint32_t  N1TB_5;                                 /*  N1TB_5          */
    volatile uint32_t  CRSA_5;                                 /*  CRSA_5          */
    volatile uint32_t  CRDA_5;                                 /*  CRDA_5          */
    volatile uint32_t  CRTB_5;                                 /*  CRTB_5          */
    volatile uint32_t  CHSTAT_5;                               /*  CHSTAT_5        */
    volatile uint32_t  CHCTRL_5;                               /*  CHCTRL_5        */
    volatile uint32_t  CHCFG_5;                                /*  CHCFG_5         */
    volatile uint32_t  CHITVL_5;                               /*  CHITVL_5        */
    volatile uint32_t  CHEXT_5;                                /*  CHEXT_5         */
    volatile uint32_t  NXLA_5;                                 /*  NXLA_5          */
    volatile uint32_t  CRLA_5;                                 /*  CRLA_5          */
/* end of struct st_dmac_n */
/* start of struct st_dmac_n */
    volatile uint32_t  N0SA_6;                                 /*  N0SA_6          */
    volatile uint32_t  N0DA_6;                                 /*  N0DA_6          */
    volatile uint32_t  N0TB_6;                                 /*  N0TB_6          */
    volatile uint32_t  N1SA_6;                                 /*  N1SA_6          */
    volatile uint32_t  N1DA_6;                                 /*  N1DA_6          */
    volatile uint32_t  N1TB_6;                                 /*  N1TB_6          */
    volatile uint32_t  CRSA_6;                                 /*  CRSA_6          */
    volatile uint32_t  CRDA_6;                                 /*  CRDA_6          */
    volatile uint32_t  CRTB_6;                                 /*  CRTB_6          */
    volatile uint32_t  CHSTAT_6;                               /*  CHSTAT_6        */
    volatile uint32_t  CHCTRL_6;                               /*  CHCTRL_6        */
    volatile uint32_t  CHCFG_6;                                /*  CHCFG_6         */
    volatile uint32_t  CHITVL_6;                               /*  CHITVL_6        */
    volatile uint32_t  CHEXT_6;                                /*  CHEXT_6         */
    volatile uint32_t  NXLA_6;                                 /*  NXLA_6          */
    volatile uint32_t  CRLA_6;                                 /*  CRLA_6          */
/* end of struct st_dmac_n */
/* start of struct st_dmac_n */
    volatile uint32_t  N0SA_7;                                 /*  N0SA_7          */
    volatile uint32_t  N0DA_7;                                 /*  N0DA_7          */
    volatile uint32_t  N0TB_7;                                 /*  N0TB_7          */
    volatile uint32_t  N1SA_7;                                 /*  N1SA_7          */
    volatile uint32_t  N1DA_7;                                 /*  N1DA_7          */
    volatile uint32_t  N1TB_7;                                 /*  N1TB_7          */
    volatile uint32_t  CRSA_7;                                 /*  CRSA_7          */
    volatile uint32_t  CRDA_7;                                 /*  CRDA_7          */
    volatile uint32_t  CRTB_7;                                 /*  CRTB_7          */
    volatile uint32_t  CHSTAT_7;                               /*  CHSTAT_7        */
    volatile uint32_t  CHCTRL_7;                               /*  CHCTRL_7        */
    volatile uint32_t  CHCFG_7;                                /*  CHCFG_7         */
    volatile uint32_t  CHITVL_7;                               /*  CHITVL_7        */
    volatile uint32_t  CHEXT_7;                                /*  CHEXT_7         */
    volatile uint32_t  NXLA_7;                                 /*  NXLA_7          */
    volatile uint32_t  CRLA_7;                                 /*  CRLA_7          */
/* end of struct st_dmac_n */
    volatile uint8_t   dummy187[256];                          /*                  */
/* start of struct st_dmaccommon_n */
    volatile uint32_t  DCTRL_0_7;                              /*  DCTRL_0_7       */
    volatile uint8_t   dummy188[12];                           /*                  */
    volatile uint32_t  DSTAT_EN_0_7;                           /*  DSTAT_EN_0_7    */
    volatile uint32_t  DSTAT_ER_0_7;                           /*  DSTAT_ER_0_7    */
    volatile uint32_t  DSTAT_END_0_7;                          /*  DSTAT_END_0_7   */
    volatile uint32_t  DSTAT_TC_0_7;                           /*  DSTAT_TC_0_7    */
    volatile uint32_t  DSTAT_SUS_0_7;                          /*  DSTAT_SUS_0_7   */
/* end of struct st_dmaccommon_n */
    volatile uint8_t   dummy189[220];                          /*                  */
/* start of struct st_dmac_n */
    volatile uint32_t  N0SA_8;                                 /*  N0SA_8          */
    volatile uint32_t  N0DA_8;                                 /*  N0DA_8          */
    volatile uint32_t  N0TB_8;                                 /*  N0TB_8          */
    volatile uint32_t  N1SA_8;                                 /*  N1SA_8          */
    volatile uint32_t  N1DA_8;                                 /*  N1DA_8          */
    volatile uint32_t  N1TB_8;                                 /*  N1TB_8          */
    volatile uint32_t  CRSA_8;                                 /*  CRSA_8          */
    volatile uint32_t  CRDA_8;                                 /*  CRDA_8          */
    volatile uint32_t  CRTB_8;                                 /*  CRTB_8          */
    volatile uint32_t  CHSTAT_8;                               /*  CHSTAT_8        */
    volatile uint32_t  CHCTRL_8;                               /*  CHCTRL_8        */
    volatile uint32_t  CHCFG_8;                                /*  CHCFG_8         */
    volatile uint32_t  CHITVL_8;                               /*  CHITVL_8        */
    volatile uint32_t  CHEXT_8;                                /*  CHEXT_8         */
    volatile uint32_t  NXLA_8;                                 /*  NXLA_8          */
    volatile uint32_t  CRLA_8;                                 /*  CRLA_8          */
/* end of struct st_dmac_n */
/* start of struct st_dmac_n */
    volatile uint32_t  N0SA_9;                                 /*  N0SA_9          */
    volatile uint32_t  N0DA_9;                                 /*  N0DA_9          */
    volatile uint32_t  N0TB_9;                                 /*  N0TB_9          */
    volatile uint32_t  N1SA_9;                                 /*  N1SA_9          */
    volatile uint32_t  N1DA_9;                                 /*  N1DA_9          */
    volatile uint32_t  N1TB_9;                                 /*  N1TB_9          */
    volatile uint32_t  CRSA_9;                                 /*  CRSA_9          */
    volatile uint32_t  CRDA_9;                                 /*  CRDA_9          */
    volatile uint32_t  CRTB_9;                                 /*  CRTB_9          */
    volatile uint32_t  CHSTAT_9;                               /*  CHSTAT_9        */
    volatile uint32_t  CHCTRL_9;                               /*  CHCTRL_9        */
    volatile uint32_t  CHCFG_9;                                /*  CHCFG_9         */
    volatile uint32_t  CHITVL_9;                               /*  CHITVL_9        */
    volatile uint32_t  CHEXT_9;                                /*  CHEXT_9         */
    volatile uint32_t  NXLA_9;                                 /*  NXLA_9          */
    volatile uint32_t  CRLA_9;                                 /*  CRLA_9          */
/* end of struct st_dmac_n */
/* start of struct st_dmac_n */
    volatile uint32_t  N0SA_10;                                /*  N0SA_10         */
    volatile uint32_t  N0DA_10;                                /*  N0DA_10         */
    volatile uint32_t  N0TB_10;                                /*  N0TB_10         */
    volatile uint32_t  N1SA_10;                                /*  N1SA_10         */
    volatile uint32_t  N1DA_10;                                /*  N1DA_10         */
    volatile uint32_t  N1TB_10;                                /*  N1TB_10         */
    volatile uint32_t  CRSA_10;                                /*  CRSA_10         */
    volatile uint32_t  CRDA_10;                                /*  CRDA_10         */
    volatile uint32_t  CRTB_10;                                /*  CRTB_10         */
    volatile uint32_t  CHSTAT_10;                              /*  CHSTAT_10       */
    volatile uint32_t  CHCTRL_10;                              /*  CHCTRL_10       */
    volatile uint32_t  CHCFG_10;                               /*  CHCFG_10        */
    volatile uint32_t  CHITVL_10;                              /*  CHITVL_10       */
    volatile uint32_t  CHEXT_10;                               /*  CHEXT_10        */
    volatile uint32_t  NXLA_10;                                /*  NXLA_10         */
    volatile uint32_t  CRLA_10;                                /*  CRLA_10         */
/* end of struct st_dmac_n */
/* start of struct st_dmac_n */
    volatile uint32_t  N0SA_11;                                /*  N0SA_11         */
    volatile uint32_t  N0DA_11;                                /*  N0DA_11         */
    volatile uint32_t  N0TB_11;                                /*  N0TB_11         */
    volatile uint32_t  N1SA_11;                                /*  N1SA_11         */
    volatile uint32_t  N1DA_11;                                /*  N1DA_11         */
    volatile uint32_t  N1TB_11;                                /*  N1TB_11         */
    volatile uint32_t  CRSA_11;                                /*  CRSA_11         */
    volatile uint32_t  CRDA_11;                                /*  CRDA_11         */
    volatile uint32_t  CRTB_11;                                /*  CRTB_11         */
    volatile uint32_t  CHSTAT_11;                              /*  CHSTAT_11       */
    volatile uint32_t  CHCTRL_11;                              /*  CHCTRL_11       */
    volatile uint32_t  CHCFG_11;                               /*  CHCFG_11        */
    volatile uint32_t  CHITVL_11;                              /*  CHITVL_11       */
    volatile uint32_t  CHEXT_11;                               /*  CHEXT_11        */
    volatile uint32_t  NXLA_11;                                /*  NXLA_11         */
    volatile uint32_t  CRLA_11;                                /*  CRLA_11         */
/* end of struct st_dmac_n */
/* start of struct st_dmac_n */
    volatile uint32_t  N0SA_12;                                /*  N0SA_12         */
    volatile uint32_t  N0DA_12;                                /*  N0DA_12         */
    volatile uint32_t  N0TB_12;                                /*  N0TB_12         */
    volatile uint32_t  N1SA_12;                                /*  N1SA_12         */
    volatile uint32_t  N1DA_12;                                /*  N1DA_12         */
    volatile uint32_t  N1TB_12;                                /*  N1TB_12         */
    volatile uint32_t  CRSA_12;                                /*  CRSA_12         */
    volatile uint32_t  CRDA_12;                                /*  CRDA_12         */
    volatile uint32_t  CRTB_12;                                /*  CRTB_12         */
    volatile uint32_t  CHSTAT_12;                              /*  CHSTAT_12       */
    volatile uint32_t  CHCTRL_12;                              /*  CHCTRL_12       */
    volatile uint32_t  CHCFG_12;                               /*  CHCFG_12        */
    volatile uint32_t  CHITVL_12;                              /*  CHITVL_12       */
    volatile uint32_t  CHEXT_12;                               /*  CHEXT_12        */
    volatile uint32_t  NXLA_12;                                /*  NXLA_12         */
    volatile uint32_t  CRLA_12;                                /*  CRLA_12         */
/* end of struct st_dmac_n */
/* start of struct st_dmac_n */
    volatile uint32_t  N0SA_13;                                /*  N0SA_13         */
    volatile uint32_t  N0DA_13;                                /*  N0DA_13         */
    volatile uint32_t  N0TB_13;                                /*  N0TB_13         */
    volatile uint32_t  N1SA_13;                                /*  N1SA_13         */
    volatile uint32_t  N1DA_13;                                /*  N1DA_13         */
    volatile uint32_t  N1TB_13;                                /*  N1TB_13         */
    volatile uint32_t  CRSA_13;                                /*  CRSA_13         */
    volatile uint32_t  CRDA_13;                                /*  CRDA_13         */
    volatile uint32_t  CRTB_13;                                /*  CRTB_13         */
    volatile uint32_t  CHSTAT_13;                              /*  CHSTAT_13       */
    volatile uint32_t  CHCTRL_13;                              /*  CHCTRL_13       */
    volatile uint32_t  CHCFG_13;                               /*  CHCFG_13        */
    volatile uint32_t  CHITVL_13;                              /*  CHITVL_13       */
    volatile uint32_t  CHEXT_13;                               /*  CHEXT_13        */
    volatile uint32_t  NXLA_13;                                /*  NXLA_13         */
    volatile uint32_t  CRLA_13;                                /*  CRLA_13         */
/* end of struct st_dmac_n */
/* start of struct st_dmac_n */
    volatile uint32_t  N0SA_14;                                /*  N0SA_14         */
    volatile uint32_t  N0DA_14;                                /*  N0DA_14         */
    volatile uint32_t  N0TB_14;                                /*  N0TB_14         */
    volatile uint32_t  N1SA_14;                                /*  N1SA_14         */
    volatile uint32_t  N1DA_14;                                /*  N1DA_14         */
    volatile uint32_t  N1TB_14;                                /*  N1TB_14         */
    volatile uint32_t  CRSA_14;                                /*  CRSA_14         */
    volatile uint32_t  CRDA_14;                                /*  CRDA_14         */
    volatile uint32_t  CRTB_14;                                /*  CRTB_14         */
    volatile uint32_t  CHSTAT_14;                              /*  CHSTAT_14       */
    volatile uint32_t  CHCTRL_14;                              /*  CHCTRL_14       */
    volatile uint32_t  CHCFG_14;                               /*  CHCFG_14        */
    volatile uint32_t  CHITVL_14;                              /*  CHITVL_14       */
    volatile uint32_t  CHEXT_14;                               /*  CHEXT_14        */
    volatile uint32_t  NXLA_14;                                /*  NXLA_14         */
    volatile uint32_t  CRLA_14;                                /*  CRLA_14         */
/* end of struct st_dmac_n */
/* start of struct st_dmac_n */
    volatile uint32_t  N0SA_15;                                /*  N0SA_15         */
    volatile uint32_t  N0DA_15;                                /*  N0DA_15         */
    volatile uint32_t  N0TB_15;                                /*  N0TB_15         */
    volatile uint32_t  N1SA_15;                                /*  N1SA_15         */
    volatile uint32_t  N1DA_15;                                /*  N1DA_15         */
    volatile uint32_t  N1TB_15;                                /*  N1TB_15         */
    volatile uint32_t  CRSA_15;                                /*  CRSA_15         */
    volatile uint32_t  CRDA_15;                                /*  CRDA_15         */
    volatile uint32_t  CRTB_15;                                /*  CRTB_15         */
    volatile uint32_t  CHSTAT_15;                              /*  CHSTAT_15       */
    volatile uint32_t  CHCTRL_15;                              /*  CHCTRL_15       */
    volatile uint32_t  CHCFG_15;                               /*  CHCFG_15        */
    volatile uint32_t  CHITVL_15;                              /*  CHITVL_15       */
    volatile uint32_t  CHEXT_15;                               /*  CHEXT_15        */
    volatile uint32_t  NXLA_15;                                /*  NXLA_15         */
    volatile uint32_t  CRLA_15;                                /*  CRLA_15         */
/* end of struct st_dmac_n */
    volatile uint8_t   dummy190[256];                          /*                  */
/* start of struct st_dmaccommon_n */
    volatile uint32_t  DCTRL_8_15;                             /*  DCTRL_8_15      */
    volatile uint8_t   dummy191[12];                           /*                  */
    volatile uint32_t  DSTAT_EN_8_15;                          /*  DSTAT_EN_8_15   */
    volatile uint32_t  DSTAT_ER_8_15;                          /*  DSTAT_ER_8_15   */
    volatile uint32_t  DSTAT_END_8_15;                         /*  DSTAT_END_8_15  */
    volatile uint32_t  DSTAT_TC_8_15;                          /*  DSTAT_TC_8_15   */
    volatile uint32_t  DSTAT_SUS_8_15;                         /*  DSTAT_SUS_8_15  */
/* end of struct st_dmaccommon_n */
    volatile uint8_t   dummy192[350095580];                    /*                  */
    volatile uint32_t  DMARS0;                                 /*  DMARS0          */
    volatile uint32_t  DMARS1;                                 /*  DMARS1          */
    volatile uint32_t  DMARS2;                                 /*  DMARS2          */
    volatile uint32_t  DMARS3;                                 /*  DMARS3          */
    volatile uint32_t  DMARS4;                                 /*  DMARS4          */
    volatile uint32_t  DMARS5;                                 /*  DMARS5          */
    volatile uint32_t  DMARS6;                                 /*  DMARS6          */
    volatile uint32_t  DMARS7;                                 /*  DMARS7          */
};


struct st_dmaccommon_n
{
    volatile uint32_t  DCTRL_0_7;                              /*  DCTRL_0_7       */
    volatile uint8_t   dummy1[12];                             /*                  */
    volatile uint32_t  DSTAT_EN_0_7;                           /*  DSTAT_EN_0_7    */
    volatile uint32_t  DSTAT_ER_0_7;                           /*  DSTAT_ER_0_7    */
    volatile uint32_t  DSTAT_END_0_7;                          /*  DSTAT_END_0_7   */
    volatile uint32_t  DSTAT_TC_0_7;                           /*  DSTAT_TC_0_7    */
    volatile uint32_t  DSTAT_SUS_0_7;                          /*  DSTAT_SUS_0_7   */
};


struct st_dmac_n
{
    volatile uint32_t  N0SA_n;                                 /*  N0SA_n          */
    volatile uint32_t  N0DA_n;                                 /*  N0DA_n          */
    volatile uint32_t  N0TB_n;                                 /*  N0TB_n          */
    volatile uint32_t  N1SA_n;                                 /*  N1SA_n          */
    volatile uint32_t  N1DA_n;                                 /*  N1DA_n          */
    volatile uint32_t  N1TB_n;                                 /*  N1TB_n          */
    volatile uint32_t  CRSA_n;                                 /*  CRSA_n          */
    volatile uint32_t  CRDA_n;                                 /*  CRDA_n          */
    volatile uint32_t  CRTB_n;                                 /*  CRTB_n          */
    volatile uint32_t  CHSTAT_n;                               /*  CHSTAT_n        */
    volatile uint32_t  CHCTRL_n;                               /*  CHCTRL_n        */
    volatile uint32_t  CHCFG_n;                                /*  CHCFG_n         */
    volatile uint32_t  CHITVL_n;                               /*  CHITVL_n        */
    volatile uint32_t  CHEXT_n;                                /*  CHEXT_n         */
    volatile uint32_t  NXLA_n;                                 /*  NXLA_n          */
    volatile uint32_t  CRLA_n;                                 /*  CRLA_n          */
};


#define DMAC    (*(struct st_dmac    *)0xE8200000uL) /* DMAC */


/* Start of channnel array defines of DMAC */

/* Channnel array defines of DMACn */
/*(Sample) value = DMACn[ channel ]->N0SA_n; */
#define DMACn_COUNT  16
#define DMACn_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &DMAC0, &DMAC1, &DMAC2, &DMAC3, &DMAC4, &DMAC5, &DMAC6, &DMAC7, \
    &DMAC8, &DMAC9, &DMAC10, &DMAC11, &DMAC12, &DMAC13, &DMAC14, &DMAC15 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define DMAC0   (*(struct st_dmac_n *)&DMAC.N0SA_0)              /* DMAC0 */
#define DMAC1   (*(struct st_dmac_n *)&DMAC.N0SA_1)              /* DMAC1 */
#define DMAC2   (*(struct st_dmac_n *)&DMAC.N0SA_2)              /* DMAC2 */
#define DMAC3   (*(struct st_dmac_n *)&DMAC.N0SA_3)              /* DMAC3 */
#define DMAC4   (*(struct st_dmac_n *)&DMAC.N0SA_4)              /* DMAC4 */
#define DMAC5   (*(struct st_dmac_n *)&DMAC.N0SA_5)              /* DMAC5 */
#define DMAC6   (*(struct st_dmac_n *)&DMAC.N0SA_6)              /* DMAC6 */
#define DMAC7   (*(struct st_dmac_n *)&DMAC.N0SA_7)              /* DMAC7 */
#define DMAC8   (*(struct st_dmac_n *)&DMAC.N0SA_8)              /* DMAC8 */
#define DMAC9   (*(struct st_dmac_n *)&DMAC.N0SA_9)              /* DMAC9 */
#define DMAC10  (*(struct st_dmac_n *)&DMAC.N0SA_10)             /* DMAC10 */
#define DMAC11  (*(struct st_dmac_n *)&DMAC.N0SA_11)             /* DMAC11 */
#define DMAC12  (*(struct st_dmac_n *)&DMAC.N0SA_12)             /* DMAC12 */
#define DMAC13  (*(struct st_dmac_n *)&DMAC.N0SA_13)             /* DMAC13 */
#define DMAC14  (*(struct st_dmac_n *)&DMAC.N0SA_14)             /* DMAC14 */
#define DMAC15  (*(struct st_dmac_n *)&DMAC.N0SA_15)             /* DMAC15 */


/* Channnel array defines of DMACnn */
/*(Sample) value = DMACnn[ channel / 8 ]->DCTRL_0_7; */
#define DMACnn_COUNT  2
#define DMACnn_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &DMAC07, &DMAC815 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define DMAC07  (*(struct st_dmaccommon_n *)&DMAC.DCTRL_0_7)     /* DMAC07 */
#define DMAC815 (*(struct st_dmaccommon_n *)&DMAC.DCTRL_8_15)    /* DMAC815 */


/* Channnel array defines of DMACmm */
/*(Sample) value = DMACmm[ channel / 2 ]->DMARS; */
struct st_dmars_mm
{
    uint32_t       DMARS;                                        /*  DMARS     */
};
#define DMACmm_COUNT  8
#define DMACmm_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &DMAC01, &DMAC23, &DMAC45, &DMAC67, &DMAC89, &DMAC1011, &DMAC1213, &DMAC1415 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define DMAC01    (*(struct st_dmars_mm *)&DMAC.DMARS0)  /* DMAC0-1   */
#define DMAC23    (*(struct st_dmars_mm *)&DMAC.DMARS1)  /* DMAC2-3   */
#define DMAC45    (*(struct st_dmars_mm *)&DMAC.DMARS2)  /* DMAC4-5   */
#define DMAC67    (*(struct st_dmars_mm *)&DMAC.DMARS3)  /* DMAC6-7   */
#define DMAC89    (*(struct st_dmars_mm *)&DMAC.DMARS4)  /* DMAC8-9   */
#define DMAC1011  (*(struct st_dmars_mm *)&DMAC.DMARS5)  /* DMAC10-11 */
#define DMAC1213  (*(struct st_dmars_mm *)&DMAC.DMARS6)  /* DMAC12-13 */
#define DMAC1415  (*(struct st_dmars_mm *)&DMAC.DMARS7)  /* DMAC14-15 */

/* End of channnel array defines of DMAC */


#define DMACN0SA_0 DMAC.N0SA_0
#define DMACN0DA_0 DMAC.N0DA_0
#define DMACN0TB_0 DMAC.N0TB_0
#define DMACN1SA_0 DMAC.N1SA_0
#define DMACN1DA_0 DMAC.N1DA_0
#define DMACN1TB_0 DMAC.N1TB_0
#define DMACCRSA_0 DMAC.CRSA_0
#define DMACCRDA_0 DMAC.CRDA_0
#define DMACCRTB_0 DMAC.CRTB_0
#define DMACCHSTAT_0 DMAC.CHSTAT_0
#define DMACCHCTRL_0 DMAC.CHCTRL_0
#define DMACCHCFG_0 DMAC.CHCFG_0
#define DMACCHITVL_0 DMAC.CHITVL_0
#define DMACCHEXT_0 DMAC.CHEXT_0
#define DMACNXLA_0 DMAC.NXLA_0
#define DMACCRLA_0 DMAC.CRLA_0
#define DMACN0SA_1 DMAC.N0SA_1
#define DMACN0DA_1 DMAC.N0DA_1
#define DMACN0TB_1 DMAC.N0TB_1
#define DMACN1SA_1 DMAC.N1SA_1
#define DMACN1DA_1 DMAC.N1DA_1
#define DMACN1TB_1 DMAC.N1TB_1
#define DMACCRSA_1 DMAC.CRSA_1
#define DMACCRDA_1 DMAC.CRDA_1
#define DMACCRTB_1 DMAC.CRTB_1
#define DMACCHSTAT_1 DMAC.CHSTAT_1
#define DMACCHCTRL_1 DMAC.CHCTRL_1
#define DMACCHCFG_1 DMAC.CHCFG_1
#define DMACCHITVL_1 DMAC.CHITVL_1
#define DMACCHEXT_1 DMAC.CHEXT_1
#define DMACNXLA_1 DMAC.NXLA_1
#define DMACCRLA_1 DMAC.CRLA_1
#define DMACN0SA_2 DMAC.N0SA_2
#define DMACN0DA_2 DMAC.N0DA_2
#define DMACN0TB_2 DMAC.N0TB_2
#define DMACN1SA_2 DMAC.N1SA_2
#define DMACN1DA_2 DMAC.N1DA_2
#define DMACN1TB_2 DMAC.N1TB_2
#define DMACCRSA_2 DMAC.CRSA_2
#define DMACCRDA_2 DMAC.CRDA_2
#define DMACCRTB_2 DMAC.CRTB_2
#define DMACCHSTAT_2 DMAC.CHSTAT_2
#define DMACCHCTRL_2 DMAC.CHCTRL_2
#define DMACCHCFG_2 DMAC.CHCFG_2
#define DMACCHITVL_2 DMAC.CHITVL_2
#define DMACCHEXT_2 DMAC.CHEXT_2
#define DMACNXLA_2 DMAC.NXLA_2
#define DMACCRLA_2 DMAC.CRLA_2
#define DMACN0SA_3 DMAC.N0SA_3
#define DMACN0DA_3 DMAC.N0DA_3
#define DMACN0TB_3 DMAC.N0TB_3
#define DMACN1SA_3 DMAC.N1SA_3
#define DMACN1DA_3 DMAC.N1DA_3
#define DMACN1TB_3 DMAC.N1TB_3
#define DMACCRSA_3 DMAC.CRSA_3
#define DMACCRDA_3 DMAC.CRDA_3
#define DMACCRTB_3 DMAC.CRTB_3
#define DMACCHSTAT_3 DMAC.CHSTAT_3
#define DMACCHCTRL_3 DMAC.CHCTRL_3
#define DMACCHCFG_3 DMAC.CHCFG_3
#define DMACCHITVL_3 DMAC.CHITVL_3
#define DMACCHEXT_3 DMAC.CHEXT_3
#define DMACNXLA_3 DMAC.NXLA_3
#define DMACCRLA_3 DMAC.CRLA_3
#define DMACN0SA_4 DMAC.N0SA_4
#define DMACN0DA_4 DMAC.N0DA_4
#define DMACN0TB_4 DMAC.N0TB_4
#define DMACN1SA_4 DMAC.N1SA_4
#define DMACN1DA_4 DMAC.N1DA_4
#define DMACN1TB_4 DMAC.N1TB_4
#define DMACCRSA_4 DMAC.CRSA_4
#define DMACCRDA_4 DMAC.CRDA_4
#define DMACCRTB_4 DMAC.CRTB_4
#define DMACCHSTAT_4 DMAC.CHSTAT_4
#define DMACCHCTRL_4 DMAC.CHCTRL_4
#define DMACCHCFG_4 DMAC.CHCFG_4
#define DMACCHITVL_4 DMAC.CHITVL_4
#define DMACCHEXT_4 DMAC.CHEXT_4
#define DMACNXLA_4 DMAC.NXLA_4
#define DMACCRLA_4 DMAC.CRLA_4
#define DMACN0SA_5 DMAC.N0SA_5
#define DMACN0DA_5 DMAC.N0DA_5
#define DMACN0TB_5 DMAC.N0TB_5
#define DMACN1SA_5 DMAC.N1SA_5
#define DMACN1DA_5 DMAC.N1DA_5
#define DMACN1TB_5 DMAC.N1TB_5
#define DMACCRSA_5 DMAC.CRSA_5
#define DMACCRDA_5 DMAC.CRDA_5
#define DMACCRTB_5 DMAC.CRTB_5
#define DMACCHSTAT_5 DMAC.CHSTAT_5
#define DMACCHCTRL_5 DMAC.CHCTRL_5
#define DMACCHCFG_5 DMAC.CHCFG_5
#define DMACCHITVL_5 DMAC.CHITVL_5
#define DMACCHEXT_5 DMAC.CHEXT_5
#define DMACNXLA_5 DMAC.NXLA_5
#define DMACCRLA_5 DMAC.CRLA_5
#define DMACN0SA_6 DMAC.N0SA_6
#define DMACN0DA_6 DMAC.N0DA_6
#define DMACN0TB_6 DMAC.N0TB_6
#define DMACN1SA_6 DMAC.N1SA_6
#define DMACN1DA_6 DMAC.N1DA_6
#define DMACN1TB_6 DMAC.N1TB_6
#define DMACCRSA_6 DMAC.CRSA_6
#define DMACCRDA_6 DMAC.CRDA_6
#define DMACCRTB_6 DMAC.CRTB_6
#define DMACCHSTAT_6 DMAC.CHSTAT_6
#define DMACCHCTRL_6 DMAC.CHCTRL_6
#define DMACCHCFG_6 DMAC.CHCFG_6
#define DMACCHITVL_6 DMAC.CHITVL_6
#define DMACCHEXT_6 DMAC.CHEXT_6
#define DMACNXLA_6 DMAC.NXLA_6
#define DMACCRLA_6 DMAC.CRLA_6
#define DMACN0SA_7 DMAC.N0SA_7
#define DMACN0DA_7 DMAC.N0DA_7
#define DMACN0TB_7 DMAC.N0TB_7
#define DMACN1SA_7 DMAC.N1SA_7
#define DMACN1DA_7 DMAC.N1DA_7
#define DMACN1TB_7 DMAC.N1TB_7
#define DMACCRSA_7 DMAC.CRSA_7
#define DMACCRDA_7 DMAC.CRDA_7
#define DMACCRTB_7 DMAC.CRTB_7
#define DMACCHSTAT_7 DMAC.CHSTAT_7
#define DMACCHCTRL_7 DMAC.CHCTRL_7
#define DMACCHCFG_7 DMAC.CHCFG_7
#define DMACCHITVL_7 DMAC.CHITVL_7
#define DMACCHEXT_7 DMAC.CHEXT_7
#define DMACNXLA_7 DMAC.NXLA_7
#define DMACCRLA_7 DMAC.CRLA_7
#define DMACDCTRL_0_7 DMAC.DCTRL_0_7
#define DMACDSTAT_EN_0_7 DMAC.DSTAT_EN_0_7
#define DMACDSTAT_ER_0_7 DMAC.DSTAT_ER_0_7
#define DMACDSTAT_END_0_7 DMAC.DSTAT_END_0_7
#define DMACDSTAT_TC_0_7 DMAC.DSTAT_TC_0_7
#define DMACDSTAT_SUS_0_7 DMAC.DSTAT_SUS_0_7
#define DMACN0SA_8 DMAC.N0SA_8
#define DMACN0DA_8 DMAC.N0DA_8
#define DMACN0TB_8 DMAC.N0TB_8
#define DMACN1SA_8 DMAC.N1SA_8
#define DMACN1DA_8 DMAC.N1DA_8
#define DMACN1TB_8 DMAC.N1TB_8
#define DMACCRSA_8 DMAC.CRSA_8
#define DMACCRDA_8 DMAC.CRDA_8
#define DMACCRTB_8 DMAC.CRTB_8
#define DMACCHSTAT_8 DMAC.CHSTAT_8
#define DMACCHCTRL_8 DMAC.CHCTRL_8
#define DMACCHCFG_8 DMAC.CHCFG_8
#define DMACCHITVL_8 DMAC.CHITVL_8
#define DMACCHEXT_8 DMAC.CHEXT_8
#define DMACNXLA_8 DMAC.NXLA_8
#define DMACCRLA_8 DMAC.CRLA_8
#define DMACN0SA_9 DMAC.N0SA_9
#define DMACN0DA_9 DMAC.N0DA_9
#define DMACN0TB_9 DMAC.N0TB_9
#define DMACN1SA_9 DMAC.N1SA_9
#define DMACN1DA_9 DMAC.N1DA_9
#define DMACN1TB_9 DMAC.N1TB_9
#define DMACCRSA_9 DMAC.CRSA_9
#define DMACCRDA_9 DMAC.CRDA_9
#define DMACCRTB_9 DMAC.CRTB_9
#define DMACCHSTAT_9 DMAC.CHSTAT_9
#define DMACCHCTRL_9 DMAC.CHCTRL_9
#define DMACCHCFG_9 DMAC.CHCFG_9
#define DMACCHITVL_9 DMAC.CHITVL_9
#define DMACCHEXT_9 DMAC.CHEXT_9
#define DMACNXLA_9 DMAC.NXLA_9
#define DMACCRLA_9 DMAC.CRLA_9
#define DMACN0SA_10 DMAC.N0SA_10
#define DMACN0DA_10 DMAC.N0DA_10
#define DMACN0TB_10 DMAC.N0TB_10
#define DMACN1SA_10 DMAC.N1SA_10
#define DMACN1DA_10 DMAC.N1DA_10
#define DMACN1TB_10 DMAC.N1TB_10
#define DMACCRSA_10 DMAC.CRSA_10
#define DMACCRDA_10 DMAC.CRDA_10
#define DMACCRTB_10 DMAC.CRTB_10
#define DMACCHSTAT_10 DMAC.CHSTAT_10
#define DMACCHCTRL_10 DMAC.CHCTRL_10
#define DMACCHCFG_10 DMAC.CHCFG_10
#define DMACCHITVL_10 DMAC.CHITVL_10
#define DMACCHEXT_10 DMAC.CHEXT_10
#define DMACNXLA_10 DMAC.NXLA_10
#define DMACCRLA_10 DMAC.CRLA_10
#define DMACN0SA_11 DMAC.N0SA_11
#define DMACN0DA_11 DMAC.N0DA_11
#define DMACN0TB_11 DMAC.N0TB_11
#define DMACN1SA_11 DMAC.N1SA_11
#define DMACN1DA_11 DMAC.N1DA_11
#define DMACN1TB_11 DMAC.N1TB_11
#define DMACCRSA_11 DMAC.CRSA_11
#define DMACCRDA_11 DMAC.CRDA_11
#define DMACCRTB_11 DMAC.CRTB_11
#define DMACCHSTAT_11 DMAC.CHSTAT_11
#define DMACCHCTRL_11 DMAC.CHCTRL_11
#define DMACCHCFG_11 DMAC.CHCFG_11
#define DMACCHITVL_11 DMAC.CHITVL_11
#define DMACCHEXT_11 DMAC.CHEXT_11
#define DMACNXLA_11 DMAC.NXLA_11
#define DMACCRLA_11 DMAC.CRLA_11
#define DMACN0SA_12 DMAC.N0SA_12
#define DMACN0DA_12 DMAC.N0DA_12
#define DMACN0TB_12 DMAC.N0TB_12
#define DMACN1SA_12 DMAC.N1SA_12
#define DMACN1DA_12 DMAC.N1DA_12
#define DMACN1TB_12 DMAC.N1TB_12
#define DMACCRSA_12 DMAC.CRSA_12
#define DMACCRDA_12 DMAC.CRDA_12
#define DMACCRTB_12 DMAC.CRTB_12
#define DMACCHSTAT_12 DMAC.CHSTAT_12
#define DMACCHCTRL_12 DMAC.CHCTRL_12
#define DMACCHCFG_12 DMAC.CHCFG_12
#define DMACCHITVL_12 DMAC.CHITVL_12
#define DMACCHEXT_12 DMAC.CHEXT_12
#define DMACNXLA_12 DMAC.NXLA_12
#define DMACCRLA_12 DMAC.CRLA_12
#define DMACN0SA_13 DMAC.N0SA_13
#define DMACN0DA_13 DMAC.N0DA_13
#define DMACN0TB_13 DMAC.N0TB_13
#define DMACN1SA_13 DMAC.N1SA_13
#define DMACN1DA_13 DMAC.N1DA_13
#define DMACN1TB_13 DMAC.N1TB_13
#define DMACCRSA_13 DMAC.CRSA_13
#define DMACCRDA_13 DMAC.CRDA_13
#define DMACCRTB_13 DMAC.CRTB_13
#define DMACCHSTAT_13 DMAC.CHSTAT_13
#define DMACCHCTRL_13 DMAC.CHCTRL_13
#define DMACCHCFG_13 DMAC.CHCFG_13
#define DMACCHITVL_13 DMAC.CHITVL_13
#define DMACCHEXT_13 DMAC.CHEXT_13
#define DMACNXLA_13 DMAC.NXLA_13
#define DMACCRLA_13 DMAC.CRLA_13
#define DMACN0SA_14 DMAC.N0SA_14
#define DMACN0DA_14 DMAC.N0DA_14
#define DMACN0TB_14 DMAC.N0TB_14
#define DMACN1SA_14 DMAC.N1SA_14
#define DMACN1DA_14 DMAC.N1DA_14
#define DMACN1TB_14 DMAC.N1TB_14
#define DMACCRSA_14 DMAC.CRSA_14
#define DMACCRDA_14 DMAC.CRDA_14
#define DMACCRTB_14 DMAC.CRTB_14
#define DMACCHSTAT_14 DMAC.CHSTAT_14
#define DMACCHCTRL_14 DMAC.CHCTRL_14
#define DMACCHCFG_14 DMAC.CHCFG_14
#define DMACCHITVL_14 DMAC.CHITVL_14
#define DMACCHEXT_14 DMAC.CHEXT_14
#define DMACNXLA_14 DMAC.NXLA_14
#define DMACCRLA_14 DMAC.CRLA_14
#define DMACN0SA_15 DMAC.N0SA_15
#define DMACN0DA_15 DMAC.N0DA_15
#define DMACN0TB_15 DMAC.N0TB_15
#define DMACN1SA_15 DMAC.N1SA_15
#define DMACN1DA_15 DMAC.N1DA_15
#define DMACN1TB_15 DMAC.N1TB_15
#define DMACCRSA_15 DMAC.CRSA_15
#define DMACCRDA_15 DMAC.CRDA_15
#define DMACCRTB_15 DMAC.CRTB_15
#define DMACCHSTAT_15 DMAC.CHSTAT_15
#define DMACCHCTRL_15 DMAC.CHCTRL_15
#define DMACCHCFG_15 DMAC.CHCFG_15
#define DMACCHITVL_15 DMAC.CHITVL_15
#define DMACCHEXT_15 DMAC.CHEXT_15
#define DMACNXLA_15 DMAC.NXLA_15
#define DMACCRLA_15 DMAC.CRLA_15
#define DMACDCTRL_8_15 DMAC.DCTRL_8_15
#define DMACDSTAT_EN_8_15 DMAC.DSTAT_EN_8_15
#define DMACDSTAT_ER_8_15 DMAC.DSTAT_ER_8_15
#define DMACDSTAT_END_8_15 DMAC.DSTAT_END_8_15
#define DMACDSTAT_TC_8_15 DMAC.DSTAT_TC_8_15
#define DMACDSTAT_SUS_8_15 DMAC.DSTAT_SUS_8_15
#define DMACDMARS0 DMAC.DMARS0
#define DMACDMARS1 DMAC.DMARS1
#define DMACDMARS2 DMAC.DMARS2
#define DMACDMARS3 DMAC.DMARS3
#define DMACDMARS4 DMAC.DMARS4
#define DMACDMARS5 DMAC.DMARS5
#define DMACDMARS6 DMAC.DMARS6
#define DMACDMARS7 DMAC.DMARS7
/* <-SEC M1.10.1 */
/* <-QAC 0639 */
#endif
