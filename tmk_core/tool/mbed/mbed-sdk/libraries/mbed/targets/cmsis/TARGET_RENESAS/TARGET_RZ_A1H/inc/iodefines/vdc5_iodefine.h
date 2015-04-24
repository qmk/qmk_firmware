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
* File Name : vdc5_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef VDC5_IODEFINE_H
#define VDC5_IODEFINE_H
/* ->QAC 0639 : Over 127 members (C90) */
/* ->SEC M1.10.1 : Not magic number */

struct st_vdc5
{                                                          /* VDC5             */
    volatile uint32_t  INP_UPDATE;                             /*  INP_UPDATE      */
    volatile uint32_t  INP_SEL_CNT;                            /*  INP_SEL_CNT     */
    volatile uint32_t  INP_EXT_SYNC_CNT;                       /*  INP_EXT_SYNC_CNT */
    volatile uint32_t  INP_VSYNC_PH_ADJ;                       /*  INP_VSYNC_PH_ADJ */
    volatile uint32_t  INP_DLY_ADJ;                            /*  INP_DLY_ADJ     */
    volatile uint8_t   dummy1[108];                            /*                  */
    volatile uint32_t  IMGCNT_UPDATE;                          /*  IMGCNT_UPDATE   */
#define VDC5_IMGCNT_NR_CNT0_COUNT 2
    volatile uint32_t  IMGCNT_NR_CNT0;                         /*  IMGCNT_NR_CNT0  */
    volatile uint32_t  IMGCNT_NR_CNT1;                         /*  IMGCNT_NR_CNT1  */
    volatile uint8_t   dummy2[20];                             /*                  */
    volatile uint32_t  IMGCNT_MTX_MODE;                        /*  IMGCNT_MTX_MODE */
    volatile uint32_t  IMGCNT_MTX_YG_ADJ0;                     /*  IMGCNT_MTX_YG_ADJ0 */
    volatile uint32_t  IMGCNT_MTX_YG_ADJ1;                     /*  IMGCNT_MTX_YG_ADJ1 */
    volatile uint32_t  IMGCNT_MTX_CBB_ADJ0;                    /*  IMGCNT_MTX_CBB_ADJ0 */
    volatile uint32_t  IMGCNT_MTX_CBB_ADJ1;                    /*  IMGCNT_MTX_CBB_ADJ1 */
    volatile uint32_t  IMGCNT_MTX_CRR_ADJ0;                    /*  IMGCNT_MTX_CRR_ADJ0 */
    volatile uint32_t  IMGCNT_MTX_CRR_ADJ1;                    /*  IMGCNT_MTX_CRR_ADJ1 */
    volatile uint8_t   dummy3[4];                              /*                  */
    volatile uint32_t  IMGCNT_DRC_REG;                         /*  IMGCNT_DRC_REG  */
    volatile uint8_t   dummy4[60];                             /*                  */
/* start of struct st_vdc5_from_sc0_scl0_update */
    volatile uint32_t  SC0_SCL0_UPDATE;                        /*  SC0_SCL0_UPDATE */
#define VDC5_SC0_SCL0_FRC1_COUNT 7
    volatile uint32_t  SC0_SCL0_FRC1;                          /*  SC0_SCL0_FRC1   */
    volatile uint32_t  SC0_SCL0_FRC2;                          /*  SC0_SCL0_FRC2   */
    volatile uint32_t  SC0_SCL0_FRC3;                          /*  SC0_SCL0_FRC3   */
    volatile uint32_t  SC0_SCL0_FRC4;                          /*  SC0_SCL0_FRC4   */
    volatile uint32_t  SC0_SCL0_FRC5;                          /*  SC0_SCL0_FRC5   */
    volatile uint32_t  SC0_SCL0_FRC6;                          /*  SC0_SCL0_FRC6   */
    volatile uint32_t  SC0_SCL0_FRC7;                          /*  SC0_SCL0_FRC7   */
    volatile uint8_t   dummy5[4];                              /*                  */
    volatile uint32_t  SC0_SCL0_FRC9;                          /*  SC0_SCL0_FRC9   */
    volatile uint16_t SC0_SCL0_MON0;                          /*  SC0_SCL0_MON0   */
    volatile uint16_t SC0_SCL0_INT;                           /*  SC0_SCL0_INT    */
#define VDC5_SC0_SCL0_DS1_COUNT 7
    volatile uint32_t  SC0_SCL0_DS1;                           /*  SC0_SCL0_DS1    */
    volatile uint32_t  SC0_SCL0_DS2;                           /*  SC0_SCL0_DS2    */
    volatile uint32_t  SC0_SCL0_DS3;                           /*  SC0_SCL0_DS3    */
    volatile uint32_t  SC0_SCL0_DS4;                           /*  SC0_SCL0_DS4    */
    volatile uint32_t  SC0_SCL0_DS5;                           /*  SC0_SCL0_DS5    */
    volatile uint32_t  SC0_SCL0_DS6;                           /*  SC0_SCL0_DS6    */
    volatile uint32_t  SC0_SCL0_DS7;                           /*  SC0_SCL0_DS7    */
#define VDC5_SC0_SCL0_US1_COUNT 8
    volatile uint32_t  SC0_SCL0_US1;                           /*  SC0_SCL0_US1    */
    volatile uint32_t  SC0_SCL0_US2;                           /*  SC0_SCL0_US2    */
    volatile uint32_t  SC0_SCL0_US3;                           /*  SC0_SCL0_US3    */
    volatile uint32_t  SC0_SCL0_US4;                           /*  SC0_SCL0_US4    */
    volatile uint32_t  SC0_SCL0_US5;                           /*  SC0_SCL0_US5    */
    volatile uint32_t  SC0_SCL0_US6;                           /*  SC0_SCL0_US6    */
    volatile uint32_t  SC0_SCL0_US7;                           /*  SC0_SCL0_US7    */
    volatile uint32_t  SC0_SCL0_US8;                           /*  SC0_SCL0_US8    */
    volatile uint8_t   dummy6[4];                              /*                  */
    volatile uint32_t  SC0_SCL0_OVR1;                          /*  SC0_SCL0_OVR1   */
    volatile uint8_t   dummy7[16];                             /*                  */
    volatile uint32_t  SC0_SCL1_UPDATE;                        /*  SC0_SCL1_UPDATE */
    volatile uint8_t   dummy8[4];                              /*                  */
#define VDC5_SC0_SCL1_WR1_COUNT 4
    volatile uint32_t  SC0_SCL1_WR1;                           /*  SC0_SCL1_WR1    */
    volatile uint32_t  SC0_SCL1_WR2;                           /*  SC0_SCL1_WR2    */
    volatile uint32_t  SC0_SCL1_WR3;                           /*  SC0_SCL1_WR3    */
    volatile uint32_t  SC0_SCL1_WR4;                           /*  SC0_SCL1_WR4    */
    volatile uint8_t   dummy9[4];                              /*                  */
    volatile uint32_t  SC0_SCL1_WR5;                           /*  SC0_SCL1_WR5    */
    volatile uint32_t  SC0_SCL1_WR6;                           /*  SC0_SCL1_WR6    */
    volatile uint32_t  SC0_SCL1_WR7;                           /*  SC0_SCL1_WR7    */
    volatile uint32_t  SC0_SCL1_WR8;                           /*  SC0_SCL1_WR8    */
    volatile uint32_t  SC0_SCL1_WR9;                           /*  SC0_SCL1_WR9    */
    volatile uint32_t  SC0_SCL1_WR10;                          /*  SC0_SCL1_WR10   */
/* end of struct st_vdc5_from_sc0_scl0_update */
    volatile uint32_t  SC0_SCL1_WR11;                          /*  SC0_SCL1_WR11   */
    volatile uint32_t  SC0_SCL1_MON1;                          /*  SC0_SCL1_MON1   */
/* start of struct st_vdc5_from_sc0_scl1_pbuf0 */
#define VDC5_SC0_SCL1_PBUF0_COUNT 4
    volatile uint32_t  SC0_SCL1_PBUF0;                         /*  SC0_SCL1_PBUF0  */
    volatile uint32_t  SC0_SCL1_PBUF1;                         /*  SC0_SCL1_PBUF1  */
    volatile uint32_t  SC0_SCL1_PBUF2;                         /*  SC0_SCL1_PBUF2  */
    volatile uint32_t  SC0_SCL1_PBUF3;                         /*  SC0_SCL1_PBUF3  */
    volatile uint32_t  SC0_SCL1_PBUF_FLD;                      /*  SC0_SCL1_PBUF_FLD */
    volatile uint32_t  SC0_SCL1_PBUF_CNT;                      /*  SC0_SCL1_PBUF_CNT */
/* end of struct st_vdc5_from_sc0_scl1_pbuf0 */
    volatile uint8_t   dummy10[44];                            /*                  */
/* start of struct st_vdc5_from_gr0_update */
    volatile uint32_t  GR0_UPDATE;                             /*  GR0_UPDATE      */
    volatile uint32_t  GR0_FLM_RD;                             /*  GR0_FLM_RD      */
#define VDC5_GR0_FLM1_COUNT 6
    volatile uint32_t  GR0_FLM1;                               /*  GR0_FLM1        */
    volatile uint32_t  GR0_FLM2;                               /*  GR0_FLM2        */
    volatile uint32_t  GR0_FLM3;                               /*  GR0_FLM3        */
    volatile uint32_t  GR0_FLM4;                               /*  GR0_FLM4        */
    volatile uint32_t  GR0_FLM5;                               /*  GR0_FLM5        */
    volatile uint32_t  GR0_FLM6;                               /*  GR0_FLM6        */
#define VDC5_GR0_AB1_COUNT 3
    volatile uint32_t  GR0_AB1;                                /*  GR0_AB1         */
    volatile uint32_t  GR0_AB2;                                /*  GR0_AB2         */
    volatile uint32_t  GR0_AB3;                                /*  GR0_AB3         */
/* end of struct st_vdc5_from_gr0_update */
    volatile uint8_t   dummy11[12];                            /*                  */
/* start of struct st_vdc5_from_gr0_ab7 */
    volatile uint32_t  GR0_AB7;                                /*  GR0_AB7         */
    volatile uint32_t  GR0_AB8;                                /*  GR0_AB8         */
    volatile uint32_t  GR0_AB9;                                /*  GR0_AB9         */
    volatile uint32_t  GR0_AB10;                               /*  GR0_AB10        */
    volatile uint32_t  GR0_AB11;                               /*  GR0_AB11        */
    volatile uint32_t  GR0_BASE;                               /*  GR0_BASE        */
/* end of struct st_vdc5_from_gr0_ab7 */
    volatile uint32_t  GR0_CLUT;                               /*  GR0_CLUT        */
    volatile uint8_t   dummy12[44];                            /*                  */
/* start of struct st_vdc5_from_adj0_update */
    volatile uint32_t  ADJ0_UPDATE;                            /*  ADJ0_UPDATE     */
    volatile uint32_t  ADJ0_BKSTR_SET;                         /*  ADJ0_BKSTR_SET  */
#define VDC5_ADJ0_ENH_TIM1_COUNT 3
    volatile uint32_t  ADJ0_ENH_TIM1;                          /*  ADJ0_ENH_TIM1   */
    volatile uint32_t  ADJ0_ENH_TIM2;                          /*  ADJ0_ENH_TIM2   */
    volatile uint32_t  ADJ0_ENH_TIM3;                          /*  ADJ0_ENH_TIM3   */
#define VDC5_ADJ0_ENH_SHP1_COUNT 6
    volatile uint32_t  ADJ0_ENH_SHP1;                          /*  ADJ0_ENH_SHP1   */
    volatile uint32_t  ADJ0_ENH_SHP2;                          /*  ADJ0_ENH_SHP2   */
    volatile uint32_t  ADJ0_ENH_SHP3;                          /*  ADJ0_ENH_SHP3   */
    volatile uint32_t  ADJ0_ENH_SHP4;                          /*  ADJ0_ENH_SHP4   */
    volatile uint32_t  ADJ0_ENH_SHP5;                          /*  ADJ0_ENH_SHP5   */
    volatile uint32_t  ADJ0_ENH_SHP6;                          /*  ADJ0_ENH_SHP6   */
#define VDC5_ADJ0_ENH_LTI1_COUNT 2
    volatile uint32_t  ADJ0_ENH_LTI1;                          /*  ADJ0_ENH_LTI1   */
    volatile uint32_t  ADJ0_ENH_LTI2;                          /*  ADJ0_ENH_LTI2   */
    volatile uint32_t  ADJ0_MTX_MODE;                          /*  ADJ0_MTX_MODE   */
    volatile uint32_t  ADJ0_MTX_YG_ADJ0;                       /*  ADJ0_MTX_YG_ADJ0 */
    volatile uint32_t  ADJ0_MTX_YG_ADJ1;                       /*  ADJ0_MTX_YG_ADJ1 */
    volatile uint32_t  ADJ0_MTX_CBB_ADJ0;                      /*  ADJ0_MTX_CBB_ADJ0 */
    volatile uint32_t  ADJ0_MTX_CBB_ADJ1;                      /*  ADJ0_MTX_CBB_ADJ1 */
    volatile uint32_t  ADJ0_MTX_CRR_ADJ0;                      /*  ADJ0_MTX_CRR_ADJ0 */
    volatile uint32_t  ADJ0_MTX_CRR_ADJ1;                      /*  ADJ0_MTX_CRR_ADJ1 */
/* end of struct st_vdc5_from_adj0_update */
    volatile uint8_t   dummy13[48];                            /*                  */
/* start of struct st_vdc5_from_gr0_update */
    volatile uint32_t  GR2_UPDATE;                             /*  GR2_UPDATE      */
    volatile uint32_t  GR2_FLM_RD;                             /*  GR2_FLM_RD      */
#define VDC5_GR2_FLM1_COUNT 6
    volatile uint32_t  GR2_FLM1;                               /*  GR2_FLM1        */
    volatile uint32_t  GR2_FLM2;                               /*  GR2_FLM2        */
    volatile uint32_t  GR2_FLM3;                               /*  GR2_FLM3        */
    volatile uint32_t  GR2_FLM4;                               /*  GR2_FLM4        */
    volatile uint32_t  GR2_FLM5;                               /*  GR2_FLM5        */
    volatile uint32_t  GR2_FLM6;                               /*  GR2_FLM6        */
#define VDC5_GR2_AB1_COUNT 3
    volatile uint32_t  GR2_AB1;                                /*  GR2_AB1         */
    volatile uint32_t  GR2_AB2;                                /*  GR2_AB2         */
    volatile uint32_t  GR2_AB3;                                /*  GR2_AB3         */
/* end of struct st_vdc5_from_gr0_update */
    volatile uint32_t  GR2_AB4;                                /*  GR2_AB4         */
    volatile uint32_t  GR2_AB5;                                /*  GR2_AB5         */
    volatile uint32_t  GR2_AB6;                                /*  GR2_AB6         */
/* start of struct st_vdc5_from_gr0_ab7 */
    volatile uint32_t  GR2_AB7;                                /*  GR2_AB7         */
    volatile uint32_t  GR2_AB8;                                /*  GR2_AB8         */
    volatile uint32_t  GR2_AB9;                                /*  GR2_AB9         */
    volatile uint32_t  GR2_AB10;                               /*  GR2_AB10        */
    volatile uint32_t  GR2_AB11;                               /*  GR2_AB11        */
    volatile uint32_t  GR2_BASE;                               /*  GR2_BASE        */
/* end of struct st_vdc5_from_gr0_ab7 */
    volatile uint32_t  GR2_CLUT;                               /*  GR2_CLUT        */
    volatile uint32_t  GR2_MON;                                /*  GR2_MON         */
    volatile uint8_t   dummy14[40];                            /*                  */
/* start of struct st_vdc5_from_gr0_update */
    volatile uint32_t  GR3_UPDATE;                             /*  GR3_UPDATE      */
    volatile uint32_t  GR3_FLM_RD;                             /*  GR3_FLM_RD      */
#define VDC5_GR3_FLM1_COUNT 6
    volatile uint32_t  GR3_FLM1;                               /*  GR3_FLM1        */
    volatile uint32_t  GR3_FLM2;                               /*  GR3_FLM2        */
    volatile uint32_t  GR3_FLM3;                               /*  GR3_FLM3        */
    volatile uint32_t  GR3_FLM4;                               /*  GR3_FLM4        */
    volatile uint32_t  GR3_FLM5;                               /*  GR3_FLM5        */
    volatile uint32_t  GR3_FLM6;                               /*  GR3_FLM6        */
#define VDC5_GR3_AB1_COUNT 3
    volatile uint32_t  GR3_AB1;                                /*  GR3_AB1         */
    volatile uint32_t  GR3_AB2;                                /*  GR3_AB2         */
    volatile uint32_t  GR3_AB3;                                /*  GR3_AB3         */
/* end of struct st_vdc5_from_gr0_update */
    volatile uint32_t  GR3_AB4;                                /*  GR3_AB4         */
    volatile uint32_t  GR3_AB5;                                /*  GR3_AB5         */
    volatile uint32_t  GR3_AB6;                                /*  GR3_AB6         */
/* start of struct st_vdc5_from_gr0_ab7 */
    volatile uint32_t  GR3_AB7;                                /*  GR3_AB7         */
    volatile uint32_t  GR3_AB8;                                /*  GR3_AB8         */
    volatile uint32_t  GR3_AB9;                                /*  GR3_AB9         */
    volatile uint32_t  GR3_AB10;                               /*  GR3_AB10        */
    volatile uint32_t  GR3_AB11;                               /*  GR3_AB11        */
    volatile uint32_t  GR3_BASE;                               /*  GR3_BASE        */
/* end of struct st_vdc5_from_gr0_ab7 */
    volatile uint32_t  GR3_CLUT_INT;                           /*  GR3_CLUT_INT    */
    volatile uint32_t  GR3_MON;                                /*  GR3_MON         */
    volatile uint8_t   dummy15[40];                            /*                  */
    volatile uint32_t  GAM_G_UPDATE;                           /*  GAM_G_UPDATE    */
    volatile uint32_t  GAM_SW;                                 /*  GAM_SW          */
#define VDC5_GAM_G_LUT1_COUNT 16
    volatile uint32_t  GAM_G_LUT1;                             /*  GAM_G_LUT1      */
    volatile uint32_t  GAM_G_LUT2;                             /*  GAM_G_LUT2      */
    volatile uint32_t  GAM_G_LUT3;                             /*  GAM_G_LUT3      */
    volatile uint32_t  GAM_G_LUT4;                             /*  GAM_G_LUT4      */
    volatile uint32_t  GAM_G_LUT5;                             /*  GAM_G_LUT5      */
    volatile uint32_t  GAM_G_LUT6;                             /*  GAM_G_LUT6      */
    volatile uint32_t  GAM_G_LUT7;                             /*  GAM_G_LUT7      */
    volatile uint32_t  GAM_G_LUT8;                             /*  GAM_G_LUT8      */
    volatile uint32_t  GAM_G_LUT9;                             /*  GAM_G_LUT9      */
    volatile uint32_t  GAM_G_LUT10;                            /*  GAM_G_LUT10     */
    volatile uint32_t  GAM_G_LUT11;                            /*  GAM_G_LUT11     */
    volatile uint32_t  GAM_G_LUT12;                            /*  GAM_G_LUT12     */
    volatile uint32_t  GAM_G_LUT13;                            /*  GAM_G_LUT13     */
    volatile uint32_t  GAM_G_LUT14;                            /*  GAM_G_LUT14     */
    volatile uint32_t  GAM_G_LUT15;                            /*  GAM_G_LUT15     */
    volatile uint32_t  GAM_G_LUT16;                            /*  GAM_G_LUT16     */
#define VDC5_GAM_G_AREA1_COUNT 8
    volatile uint32_t  GAM_G_AREA1;                            /*  GAM_G_AREA1     */
    volatile uint32_t  GAM_G_AREA2;                            /*  GAM_G_AREA2     */
    volatile uint32_t  GAM_G_AREA3;                            /*  GAM_G_AREA3     */
    volatile uint32_t  GAM_G_AREA4;                            /*  GAM_G_AREA4     */
    volatile uint32_t  GAM_G_AREA5;                            /*  GAM_G_AREA5     */
    volatile uint32_t  GAM_G_AREA6;                            /*  GAM_G_AREA6     */
    volatile uint32_t  GAM_G_AREA7;                            /*  GAM_G_AREA7     */
    volatile uint32_t  GAM_G_AREA8;                            /*  GAM_G_AREA8     */
    volatile uint8_t   dummy16[24];                            /*                  */
    volatile uint32_t  GAM_B_UPDATE;                           /*  GAM_B_UPDATE    */
    volatile uint8_t   dummy17[4];                             /*                  */
#define VDC5_GAM_B_LUT1_COUNT 16
    volatile uint32_t  GAM_B_LUT1;                             /*  GAM_B_LUT1      */
    volatile uint32_t  GAM_B_LUT2;                             /*  GAM_B_LUT2      */
    volatile uint32_t  GAM_B_LUT3;                             /*  GAM_B_LUT3      */
    volatile uint32_t  GAM_B_LUT4;                             /*  GAM_B_LUT4      */
    volatile uint32_t  GAM_B_LUT5;                             /*  GAM_B_LUT5      */
    volatile uint32_t  GAM_B_LUT6;                             /*  GAM_B_LUT6      */
    volatile uint32_t  GAM_B_LUT7;                             /*  GAM_B_LUT7      */
    volatile uint32_t  GAM_B_LUT8;                             /*  GAM_B_LUT8      */
    volatile uint32_t  GAM_B_LUT9;                             /*  GAM_B_LUT9      */
    volatile uint32_t  GAM_B_LUT10;                            /*  GAM_B_LUT10     */
    volatile uint32_t  GAM_B_LUT11;                            /*  GAM_B_LUT11     */
    volatile uint32_t  GAM_B_LUT12;                            /*  GAM_B_LUT12     */
    volatile uint32_t  GAM_B_LUT13;                            /*  GAM_B_LUT13     */
    volatile uint32_t  GAM_B_LUT14;                            /*  GAM_B_LUT14     */
    volatile uint32_t  GAM_B_LUT15;                            /*  GAM_B_LUT15     */
    volatile uint32_t  GAM_B_LUT16;                            /*  GAM_B_LUT16     */
#define VDC5_GAM_B_AREA1_COUNT 8
    volatile uint32_t  GAM_B_AREA1;                            /*  GAM_B_AREA1     */
    volatile uint32_t  GAM_B_AREA2;                            /*  GAM_B_AREA2     */
    volatile uint32_t  GAM_B_AREA3;                            /*  GAM_B_AREA3     */
    volatile uint32_t  GAM_B_AREA4;                            /*  GAM_B_AREA4     */
    volatile uint32_t  GAM_B_AREA5;                            /*  GAM_B_AREA5     */
    volatile uint32_t  GAM_B_AREA6;                            /*  GAM_B_AREA6     */
    volatile uint32_t  GAM_B_AREA7;                            /*  GAM_B_AREA7     */
    volatile uint32_t  GAM_B_AREA8;                            /*  GAM_B_AREA8     */
    volatile uint8_t   dummy18[24];                            /*                  */
    volatile uint32_t  GAM_R_UPDATE;                           /*  GAM_R_UPDATE    */
    volatile uint8_t   dummy19[4];                             /*                  */
#define VDC5_GAM_R_LUT1_COUNT 16
    volatile uint32_t  GAM_R_LUT1;                             /*  GAM_R_LUT1      */
    volatile uint32_t  GAM_R_LUT2;                             /*  GAM_R_LUT2      */
    volatile uint32_t  GAM_R_LUT3;                             /*  GAM_R_LUT3      */
    volatile uint32_t  GAM_R_LUT4;                             /*  GAM_R_LUT4      */
    volatile uint32_t  GAM_R_LUT5;                             /*  GAM_R_LUT5      */
    volatile uint32_t  GAM_R_LUT6;                             /*  GAM_R_LUT6      */
    volatile uint32_t  GAM_R_LUT7;                             /*  GAM_R_LUT7      */
    volatile uint32_t  GAM_R_LUT8;                             /*  GAM_R_LUT8      */
    volatile uint32_t  GAM_R_LUT9;                             /*  GAM_R_LUT9      */
    volatile uint32_t  GAM_R_LUT10;                            /*  GAM_R_LUT10     */
    volatile uint32_t  GAM_R_LUT11;                            /*  GAM_R_LUT11     */
    volatile uint32_t  GAM_R_LUT12;                            /*  GAM_R_LUT12     */
    volatile uint32_t  GAM_R_LUT13;                            /*  GAM_R_LUT13     */
    volatile uint32_t  GAM_R_LUT14;                            /*  GAM_R_LUT14     */
    volatile uint32_t  GAM_R_LUT15;                            /*  GAM_R_LUT15     */
    volatile uint32_t  GAM_R_LUT16;                            /*  GAM_R_LUT16     */
#define VDC5_GAM_R_AREA1_COUNT 8
    volatile uint32_t  GAM_R_AREA1;                            /*  GAM_R_AREA1     */
    volatile uint32_t  GAM_R_AREA2;                            /*  GAM_R_AREA2     */
    volatile uint32_t  GAM_R_AREA3;                            /*  GAM_R_AREA3     */
    volatile uint32_t  GAM_R_AREA4;                            /*  GAM_R_AREA4     */
    volatile uint32_t  GAM_R_AREA5;                            /*  GAM_R_AREA5     */
    volatile uint32_t  GAM_R_AREA6;                            /*  GAM_R_AREA6     */
    volatile uint32_t  GAM_R_AREA7;                            /*  GAM_R_AREA7     */
    volatile uint32_t  GAM_R_AREA8;                            /*  GAM_R_AREA8     */
    volatile uint8_t   dummy20[24];                            /*                  */
    volatile uint32_t  TCON_UPDATE;                            /*  TCON_UPDATE     */
    volatile uint32_t  TCON_TIM;                               /*  TCON_TIM        */
#define VDC5_TCON_TIM_STVA1_COUNT 2
    volatile uint32_t  TCON_TIM_STVA1;                         /*  TCON_TIM_STVA1  */
    volatile uint32_t  TCON_TIM_STVA2;                         /*  TCON_TIM_STVA2  */
#define VDC5_TCON_TIM_STVB1_COUNT 2
    volatile uint32_t  TCON_TIM_STVB1;                         /*  TCON_TIM_STVB1  */
    volatile uint32_t  TCON_TIM_STVB2;                         /*  TCON_TIM_STVB2  */
#define VDC5_TCON_TIM_STH1_COUNT 2
    volatile uint32_t  TCON_TIM_STH1;                          /*  TCON_TIM_STH1   */
    volatile uint32_t  TCON_TIM_STH2;                          /*  TCON_TIM_STH2   */
#define VDC5_TCON_TIM_STB1_COUNT 2
    volatile uint32_t  TCON_TIM_STB1;                          /*  TCON_TIM_STB1   */
    volatile uint32_t  TCON_TIM_STB2;                          /*  TCON_TIM_STB2   */
#define VDC5_TCON_TIM_CPV1_COUNT 2
    volatile uint32_t  TCON_TIM_CPV1;                          /*  TCON_TIM_CPV1   */
    volatile uint32_t  TCON_TIM_CPV2;                          /*  TCON_TIM_CPV2   */
#define VDC5_TCON_TIM_POLA1_COUNT 2
    volatile uint32_t  TCON_TIM_POLA1;                         /*  TCON_TIM_POLA1  */
    volatile uint32_t  TCON_TIM_POLA2;                         /*  TCON_TIM_POLA2  */
#define VDC5_TCON_TIM_POLB1_COUNT 2
    volatile uint32_t  TCON_TIM_POLB1;                         /*  TCON_TIM_POLB1  */
    volatile uint32_t  TCON_TIM_POLB2;                         /*  TCON_TIM_POLB2  */
    volatile uint32_t  TCON_TIM_DE;                            /*  TCON_TIM_DE     */
    volatile uint8_t   dummy21[60];                            /*                  */
    volatile uint32_t  OUT_UPDATE;                             /*  OUT_UPDATE      */
    volatile uint32_t  OUT_SET;                                /*  OUT_SET         */
#define VDC5_OUT_BRIGHT1_COUNT 2
    volatile uint32_t  OUT_BRIGHT1;                            /*  OUT_BRIGHT1     */
    volatile uint32_t  OUT_BRIGHT2;                            /*  OUT_BRIGHT2     */
    volatile uint32_t  OUT_CONTRAST;                           /*  OUT_CONTRAST    */
    volatile uint32_t  OUT_PDTHA;                              /*  OUT_PDTHA       */
    volatile uint8_t   dummy22[12];                            /*                  */
    volatile uint32_t  OUT_CLK_PHASE;                          /*  OUT_CLK_PHASE   */
    volatile uint8_t   dummy23[88];                            /*                  */
#define VDC5_SYSCNT_INT1_COUNT 6
    volatile uint32_t  SYSCNT_INT1;                            /*  SYSCNT_INT1     */
    volatile uint32_t  SYSCNT_INT2;                            /*  SYSCNT_INT2     */
    volatile uint32_t  SYSCNT_INT3;                            /*  SYSCNT_INT3     */
    volatile uint32_t  SYSCNT_INT4;                            /*  SYSCNT_INT4     */
    volatile uint32_t  SYSCNT_INT5;                            /*  SYSCNT_INT5     */
    volatile uint32_t  SYSCNT_INT6;                            /*  SYSCNT_INT6     */
    volatile uint16_t SYSCNT_PANEL_CLK;                       /*  SYSCNT_PANEL_CLK */
    volatile uint16_t SYSCNT_CLUT;                            /*  SYSCNT_CLUT     */
    volatile uint8_t   dummy24[356];                           /*                  */
/* start of struct st_vdc5_from_sc0_scl0_update */
    volatile uint32_t  SC1_SCL0_UPDATE;                        /*  SC1_SCL0_UPDATE */
#define VDC5_SC1_SCL0_FRC1_COUNT 7
    volatile uint32_t  SC1_SCL0_FRC1;                          /*  SC1_SCL0_FRC1   */
    volatile uint32_t  SC1_SCL0_FRC2;                          /*  SC1_SCL0_FRC2   */
    volatile uint32_t  SC1_SCL0_FRC3;                          /*  SC1_SCL0_FRC3   */
    volatile uint32_t  SC1_SCL0_FRC4;                          /*  SC1_SCL0_FRC4   */
    volatile uint32_t  SC1_SCL0_FRC5;                          /*  SC1_SCL0_FRC5   */
    volatile uint32_t  SC1_SCL0_FRC6;                          /*  SC1_SCL0_FRC6   */
    volatile uint32_t  SC1_SCL0_FRC7;                          /*  SC1_SCL0_FRC7   */
    volatile uint8_t   dummy25[4];                             /*                  */
    volatile uint32_t  SC1_SCL0_FRC9;                          /*  SC1_SCL0_FRC9   */
    volatile uint16_t SC1_SCL0_MON0;                          /*  SC1_SCL0_MON0   */
    volatile uint16_t SC1_SCL0_INT;                           /*  SC1_SCL0_INT    */
#define VDC5_SC1_SC1_SCL0_DS1_COUNT 7
    volatile uint32_t  SC1_SCL0_DS1;                           /*  SC1_SCL0_DS1    */
    volatile uint32_t  SC1_SCL0_DS2;                           /*  SC1_SCL0_DS2    */
    volatile uint32_t  SC1_SCL0_DS3;                           /*  SC1_SCL0_DS3    */
    volatile uint32_t  SC1_SCL0_DS4;                           /*  SC1_SCL0_DS4    */
    volatile uint32_t  SC1_SCL0_DS5;                           /*  SC1_SCL0_DS5    */
    volatile uint32_t  SC1_SCL0_DS6;                           /*  SC1_SCL0_DS6    */
    volatile uint32_t  SC1_SCL0_DS7;                           /*  SC1_SCL0_DS7    */
#define VDC5_SC1_SC1_SCL0_US1_COUNT 8
    volatile uint32_t  SC1_SCL0_US1;                           /*  SC1_SCL0_US1    */
    volatile uint32_t  SC1_SCL0_US2;                           /*  SC1_SCL0_US2    */
    volatile uint32_t  SC1_SCL0_US3;                           /*  SC1_SCL0_US3    */
    volatile uint32_t  SC1_SCL0_US4;                           /*  SC1_SCL0_US4    */
    volatile uint32_t  SC1_SCL0_US5;                           /*  SC1_SCL0_US5    */
    volatile uint32_t  SC1_SCL0_US6;                           /*  SC1_SCL0_US6    */
    volatile uint32_t  SC1_SCL0_US7;                           /*  SC1_SCL0_US7    */
    volatile uint32_t  SC1_SCL0_US8;                           /*  SC1_SCL0_US8    */
    volatile uint8_t   dummy26[4];                             /*                  */
    volatile uint32_t  SC1_SCL0_OVR1;                          /*  SC1_SCL0_OVR1   */
    volatile uint8_t   dummy27[16];                            /*                  */
    volatile uint32_t  SC1_SCL1_UPDATE;                        /*  SC1_SCL1_UPDATE */
    volatile uint8_t   dummy28[4];                             /*                  */
#define VDC5_SC1_SCL1_WR1_COUNT 4
    volatile uint32_t  SC1_SCL1_WR1;                           /*  SC1_SCL1_WR1    */
    volatile uint32_t  SC1_SCL1_WR2;                           /*  SC1_SCL1_WR2    */
    volatile uint32_t  SC1_SCL1_WR3;                           /*  SC1_SCL1_WR3    */
    volatile uint32_t  SC1_SCL1_WR4;                           /*  SC1_SCL1_WR4    */
    volatile uint8_t   dummy29[4];                             /*                  */
    volatile uint32_t  SC1_SCL1_WR5;                           /*  SC1_SCL1_WR5    */
    volatile uint32_t  SC1_SCL1_WR6;                           /*  SC1_SCL1_WR6    */
    volatile uint32_t  SC1_SCL1_WR7;                           /*  SC1_SCL1_WR7    */
    volatile uint32_t  SC1_SCL1_WR8;                           /*  SC1_SCL1_WR8    */
    volatile uint32_t  SC1_SCL1_WR9;                           /*  SC1_SCL1_WR9    */
    volatile uint32_t  SC1_SCL1_WR10;                          /*  SC1_SCL1_WR10   */
/* end of struct st_vdc5_from_sc0_scl0_update */
    volatile uint32_t  SC1_SCL1_WR11;                          /*  SC1_SCL1_WR11   */
    volatile uint32_t  SC1_SCL1_MON1;                          /*  SC1_SCL1_MON1   */
/* start of struct st_vdc5_from_sc0_scl1_pbuf0 */
#define VDC5_SC1_SCL1_PBUF0_COUNT 4
    volatile uint32_t  SC1_SCL1_PBUF0;                         /*  SC1_SCL1_PBUF0  */
    volatile uint32_t  SC1_SCL1_PBUF1;                         /*  SC1_SCL1_PBUF1  */
    volatile uint32_t  SC1_SCL1_PBUF2;                         /*  SC1_SCL1_PBUF2  */
    volatile uint32_t  SC1_SCL1_PBUF3;                         /*  SC1_SCL1_PBUF3  */
    volatile uint32_t  SC1_SCL1_PBUF_FLD;                      /*  SC1_SCL1_PBUF_FLD */
    volatile uint32_t  SC1_SCL1_PBUF_CNT;                      /*  SC1_SCL1_PBUF_CNT */
/* end of struct st_vdc5_from_sc0_scl1_pbuf0 */
    volatile uint8_t   dummy30[44];                            /*                  */
/* start of struct st_vdc5_from_gr0_update */
    volatile uint32_t  GR1_UPDATE;                             /*  GR1_UPDATE      */
    volatile uint32_t  GR1_FLM_RD;                             /*  GR1_FLM_RD      */
#define VDC5_GR1_FLM1_COUNT 6
    volatile uint32_t  GR1_FLM1;                               /*  GR1_FLM1        */
    volatile uint32_t  GR1_FLM2;                               /*  GR1_FLM2        */
    volatile uint32_t  GR1_FLM3;                               /*  GR1_FLM3        */
    volatile uint32_t  GR1_FLM4;                               /*  GR1_FLM4        */
    volatile uint32_t  GR1_FLM5;                               /*  GR1_FLM5        */
    volatile uint32_t  GR1_FLM6;                               /*  GR1_FLM6        */
#define VDC5_GR1_AB1_COUNT 3
    volatile uint32_t  GR1_AB1;                                /*  GR1_AB1         */
    volatile uint32_t  GR1_AB2;                                /*  GR1_AB2         */
    volatile uint32_t  GR1_AB3;                                /*  GR1_AB3         */
/* end of struct st_vdc5_from_gr0_update */
    volatile uint32_t  GR1_AB4;                                /*  GR1_AB4         */
    volatile uint32_t  GR1_AB5;                                /*  GR1_AB5         */
    volatile uint32_t  GR1_AB6;                                /*  GR1_AB6         */
/* start of struct st_vdc5_from_gr0_ab7 */
    volatile uint32_t  GR1_AB7;                                /*  GR1_AB7         */
    volatile uint32_t  GR1_AB8;                                /*  GR1_AB8         */
    volatile uint32_t  GR1_AB9;                                /*  GR1_AB9         */
    volatile uint32_t  GR1_AB10;                               /*  GR1_AB10        */
    volatile uint32_t  GR1_AB11;                               /*  GR1_AB11        */
    volatile uint32_t  GR1_BASE;                               /*  GR1_BASE        */
/* end of struct st_vdc5_from_gr0_ab7 */
    volatile uint32_t  GR1_CLUT;                               /*  GR1_CLUT        */
    volatile uint32_t  GR1_MON;                                /*  GR1_MON         */
    volatile uint8_t   dummy31[40];                            /*                  */
/* start of struct st_vdc5_from_adj0_update */
    volatile uint32_t  ADJ1_UPDATE;                            /*  ADJ1_UPDATE     */
    volatile uint32_t  ADJ1_BKSTR_SET;                         /*  ADJ1_BKSTR_SET  */
#define VDC5_ADJ1_ENH_TIM1_COUNT 3
    volatile uint32_t  ADJ1_ENH_TIM1;                          /*  ADJ1_ENH_TIM1   */
    volatile uint32_t  ADJ1_ENH_TIM2;                          /*  ADJ1_ENH_TIM2   */
    volatile uint32_t  ADJ1_ENH_TIM3;                          /*  ADJ1_ENH_TIM3   */
#define VDC5_ADJ1_ENH_SHP1_COUNT 6
    volatile uint32_t  ADJ1_ENH_SHP1;                          /*  ADJ1_ENH_SHP1   */
    volatile uint32_t  ADJ1_ENH_SHP2;                          /*  ADJ1_ENH_SHP2   */
    volatile uint32_t  ADJ1_ENH_SHP3;                          /*  ADJ1_ENH_SHP3   */
    volatile uint32_t  ADJ1_ENH_SHP4;                          /*  ADJ1_ENH_SHP4   */
    volatile uint32_t  ADJ1_ENH_SHP5;                          /*  ADJ1_ENH_SHP5   */
    volatile uint32_t  ADJ1_ENH_SHP6;                          /*  ADJ1_ENH_SHP6   */
#define VDC5_ADJ1_ENH_LTI1_COUNT 2
    volatile uint32_t  ADJ1_ENH_LTI1;                          /*  ADJ1_ENH_LTI1   */
    volatile uint32_t  ADJ1_ENH_LTI2;                          /*  ADJ1_ENH_LTI2   */
    volatile uint32_t  ADJ1_MTX_MODE;                          /*  ADJ1_MTX_MODE   */
    volatile uint32_t  ADJ1_MTX_YG_ADJ0;                       /*  ADJ1_MTX_YG_ADJ0 */
    volatile uint32_t  ADJ1_MTX_YG_ADJ1;                       /*  ADJ1_MTX_YG_ADJ1 */
    volatile uint32_t  ADJ1_MTX_CBB_ADJ0;                      /*  ADJ1_MTX_CBB_ADJ0 */
    volatile uint32_t  ADJ1_MTX_CBB_ADJ1;                      /*  ADJ1_MTX_CBB_ADJ1 */
    volatile uint32_t  ADJ1_MTX_CRR_ADJ0;                      /*  ADJ1_MTX_CRR_ADJ0 */
    volatile uint32_t  ADJ1_MTX_CRR_ADJ1;                      /*  ADJ1_MTX_CRR_ADJ1 */
/* end of struct st_vdc5_from_adj0_update */
    volatile uint8_t   dummy32[48];                            /*                  */
    volatile uint32_t  GR_VIN_UPDATE;                          /*  GR_VIN_UPDATE   */
    volatile uint8_t   dummy33[28];                            /*                  */
#define VDC5_GR_VIN_AB1_COUNT 7
    volatile uint32_t  GR_VIN_AB1;                             /*  GR_VIN_AB1      */
    volatile uint32_t  GR_VIN_AB2;                             /*  GR_VIN_AB2      */
    volatile uint32_t  GR_VIN_AB3;                             /*  GR_VIN_AB3      */
    volatile uint32_t  GR_VIN_AB4;                             /*  GR_VIN_AB4      */
    volatile uint32_t  GR_VIN_AB5;                             /*  GR_VIN_AB5      */
    volatile uint32_t  GR_VIN_AB6;                             /*  GR_VIN_AB6      */
    volatile uint32_t  GR_VIN_AB7;                             /*  GR_VIN_AB7      */
    volatile uint8_t   dummy34[16];                            /*                  */
    volatile uint32_t  GR_VIN_BASE;                            /*  GR_VIN_BASE     */
    volatile uint8_t   dummy35[4];                             /*                  */
    volatile uint32_t  GR_VIN_MON;                             /*  GR_VIN_MON      */
    volatile uint8_t   dummy36[40];                            /*                  */
    volatile uint32_t  OIR_SCL0_UPDATE;                        /*  OIR_SCL0_UPDATE */
#define VDC5_OIR_SCL0_FRC1_COUNT 7
    volatile uint32_t  OIR_SCL0_FRC1;                          /*  OIR_SCL0_FRC1   */
    volatile uint32_t  OIR_SCL0_FRC2;                          /*  OIR_SCL0_FRC2   */
    volatile uint32_t  OIR_SCL0_FRC3;                          /*  OIR_SCL0_FRC3   */
    volatile uint32_t  OIR_SCL0_FRC4;                          /*  OIR_SCL0_FRC4   */
    volatile uint32_t  OIR_SCL0_FRC5;                          /*  OIR_SCL0_FRC5   */
    volatile uint32_t  OIR_SCL0_FRC6;                          /*  OIR_SCL0_FRC6   */
    volatile uint32_t  OIR_SCL0_FRC7;                          /*  OIR_SCL0_FRC7   */
    volatile uint8_t   dummy37[12];                            /*                  */
#define VDC5_OIR_SCL0_DS1_COUNT 3
    volatile uint32_t  OIR_SCL0_DS1;                           /*  OIR_SCL0_DS1    */
    volatile uint32_t  OIR_SCL0_DS2;                           /*  OIR_SCL0_DS2    */
    volatile uint32_t  OIR_SCL0_DS3;                           /*  OIR_SCL0_DS3    */
    volatile uint8_t   dummy38[12];                            /*                  */
    volatile uint32_t  OIR_SCL0_DS7;                           /*  OIR_SCL0_DS7    */
    volatile uint32_t  OIR_SCL0_US1;                           /*  OIR_SCL0_US1    */
    volatile uint32_t  OIR_SCL0_US2;                           /*  OIR_SCL0_US2    */
    volatile uint32_t  OIR_SCL0_US3;                           /*  OIR_SCL0_US3    */
    volatile uint8_t   dummy39[16];                            /*                  */
    volatile uint32_t  OIR_SCL0_US8;                           /*  OIR_SCL0_US8    */
    volatile uint8_t   dummy40[4];                             /*                  */
    volatile uint32_t  OIR_SCL0_OVR1;                          /*  OIR_SCL0_OVR1   */
    volatile uint8_t   dummy41[16];                            /*                  */
    volatile uint32_t  OIR_SCL1_UPDATE;                        /*  OIR_SCL1_UPDATE */
    volatile uint8_t   dummy42[4];                             /*                  */
#define VDC5_OIR_SCL1_WR1_COUNT 4
    volatile uint32_t  OIR_SCL1_WR1;                           /*  OIR_SCL1_WR1    */
    volatile uint32_t  OIR_SCL1_WR2;                           /*  OIR_SCL1_WR2    */
    volatile uint32_t  OIR_SCL1_WR3;                           /*  OIR_SCL1_WR3    */
    volatile uint32_t  OIR_SCL1_WR4;                           /*  OIR_SCL1_WR4    */
    volatile uint8_t   dummy43[4];                             /*                  */
    volatile uint32_t  OIR_SCL1_WR5;                           /*  OIR_SCL1_WR5    */
    volatile uint32_t  OIR_SCL1_WR6;                           /*  OIR_SCL1_WR6    */
    volatile uint32_t  OIR_SCL1_WR7;                           /*  OIR_SCL1_WR7    */
    volatile uint8_t   dummy44[88];                            /*                  */
    volatile uint32_t  GR_OIR_UPDATE;                          /*  GR_OIR_UPDATE   */
    volatile uint32_t  GR_OIR_FLM_RD;                          /*  GR_OIR_FLM_RD   */
#define VDC5_GR_OIR_FLM1_COUNT 6
    volatile uint32_t  GR_OIR_FLM1;                            /*  GR_OIR_FLM1     */
    volatile uint32_t  GR_OIR_FLM2;                            /*  GR_OIR_FLM2     */
    volatile uint32_t  GR_OIR_FLM3;                            /*  GR_OIR_FLM3     */
    volatile uint32_t  GR_OIR_FLM4;                            /*  GR_OIR_FLM4     */
    volatile uint32_t  GR_OIR_FLM5;                            /*  GR_OIR_FLM5     */
    volatile uint32_t  GR_OIR_FLM6;                            /*  GR_OIR_FLM6     */
#define VDC5_GR_OIR_AB1_COUNT 3
    volatile uint32_t  GR_OIR_AB1;                             /*  GR_OIR_AB1      */
    volatile uint32_t  GR_OIR_AB2;                             /*  GR_OIR_AB2      */
    volatile uint32_t  GR_OIR_AB3;                             /*  GR_OIR_AB3      */
    volatile uint8_t   dummy45[12];                            /*                  */
    volatile uint32_t  GR_OIR_AB7;                             /*  GR_OIR_AB7      */
    volatile uint32_t  GR_OIR_AB8;                             /*  GR_OIR_AB8      */
    volatile uint32_t  GR_OIR_AB9;                             /*  GR_OIR_AB9      */
    volatile uint32_t  GR_OIR_AB10;                            /*  GR_OIR_AB10     */
    volatile uint32_t  GR_OIR_AB11;                            /*  GR_OIR_AB11     */
    volatile uint32_t  GR_OIR_BASE;                            /*  GR_OIR_BASE     */
    volatile uint32_t  GR_OIR_CLUT;                            /*  GR_OIR_CLUT     */
    volatile uint32_t  GR_OIR_MON;                             /*  GR_OIR_MON      */
};


struct st_vdc5_from_gr0_update
{
    volatile uint32_t  GR0_UPDATE;                             /*  GR0_UPDATE      */
    volatile uint32_t  GR0_FLM_RD;                             /*  GR0_FLM_RD      */
    volatile uint32_t  GR0_FLM1;                               /*  GR0_FLM1        */
    volatile uint32_t  GR0_FLM2;                               /*  GR0_FLM2        */
    volatile uint32_t  GR0_FLM3;                               /*  GR0_FLM3        */
    volatile uint32_t  GR0_FLM4;                               /*  GR0_FLM4        */
    volatile uint32_t  GR0_FLM5;                               /*  GR0_FLM5        */
    volatile uint32_t  GR0_FLM6;                               /*  GR0_FLM6        */
    volatile uint32_t  GR0_AB1;                                /*  GR0_AB1         */
    volatile uint32_t  GR0_AB2;                                /*  GR0_AB2         */
    volatile uint32_t  GR0_AB3;                                /*  GR0_AB3         */
};


struct st_vdc5_from_gr0_ab7
{
    volatile uint32_t  GR0_AB7;                                /*  GR0_AB7         */
    volatile uint32_t  GR0_AB8;                                /*  GR0_AB8         */
    volatile uint32_t  GR0_AB9;                                /*  GR0_AB9         */
    volatile uint32_t  GR0_AB10;                               /*  GR0_AB10        */
    volatile uint32_t  GR0_AB11;                               /*  GR0_AB11        */
    volatile uint32_t  GR0_BASE;                               /*  GR0_BASE        */
};


struct st_vdc5_from_adj0_update
{
    volatile uint32_t  ADJ0_UPDATE;                            /*  ADJ0_UPDATE     */
    volatile uint32_t  ADJ0_BKSTR_SET;                         /*  ADJ0_BKSTR_SET  */
    volatile uint32_t  ADJ0_ENH_TIM1;                          /*  ADJ0_ENH_TIM1   */
    volatile uint32_t  ADJ0_ENH_TIM2;                          /*  ADJ0_ENH_TIM2   */
    volatile uint32_t  ADJ0_ENH_TIM3;                          /*  ADJ0_ENH_TIM3   */
    volatile uint32_t  ADJ0_ENH_SHP1;                          /*  ADJ0_ENH_SHP1   */
    volatile uint32_t  ADJ0_ENH_SHP2;                          /*  ADJ0_ENH_SHP2   */
    volatile uint32_t  ADJ0_ENH_SHP3;                          /*  ADJ0_ENH_SHP3   */
    volatile uint32_t  ADJ0_ENH_SHP4;                          /*  ADJ0_ENH_SHP4   */
    volatile uint32_t  ADJ0_ENH_SHP5;                          /*  ADJ0_ENH_SHP5   */
    volatile uint32_t  ADJ0_ENH_SHP6;                          /*  ADJ0_ENH_SHP6   */
    volatile uint32_t  ADJ0_ENH_LTI1;                          /*  ADJ0_ENH_LTI1   */
    volatile uint32_t  ADJ0_ENH_LTI2;                          /*  ADJ0_ENH_LTI2   */
    volatile uint32_t  ADJ0_MTX_MODE;                          /*  ADJ0_MTX_MODE   */
    volatile uint32_t  ADJ0_MTX_YG_ADJ0;                       /*  ADJ0_MTX_YG_ADJ0 */
    volatile uint32_t  ADJ0_MTX_YG_ADJ1;                       /*  ADJ0_MTX_YG_ADJ1 */
    volatile uint32_t  ADJ0_MTX_CBB_ADJ0;                      /*  ADJ0_MTX_CBB_ADJ0 */
    volatile uint32_t  ADJ0_MTX_CBB_ADJ1;                      /*  ADJ0_MTX_CBB_ADJ1 */
    volatile uint32_t  ADJ0_MTX_CRR_ADJ0;                      /*  ADJ0_MTX_CRR_ADJ0 */
    volatile uint32_t  ADJ0_MTX_CRR_ADJ1;                      /*  ADJ0_MTX_CRR_ADJ1 */
};


struct st_vdc5_from_sc0_scl0_update
{
    volatile uint32_t  SC0_SCL0_UPDATE;                        /*  SC0_SCL0_UPDATE */
    volatile uint32_t  SC0_SCL0_FRC1;                          /*  SC0_SCL0_FRC1   */
    volatile uint32_t  SC0_SCL0_FRC2;                          /*  SC0_SCL0_FRC2   */
    volatile uint32_t  SC0_SCL0_FRC3;                          /*  SC0_SCL0_FRC3   */
    volatile uint32_t  SC0_SCL0_FRC4;                          /*  SC0_SCL0_FRC4   */
    volatile uint32_t  SC0_SCL0_FRC5;                          /*  SC0_SCL0_FRC5   */
    volatile uint32_t  SC0_SCL0_FRC6;                          /*  SC0_SCL0_FRC6   */
    volatile uint32_t  SC0_SCL0_FRC7;                          /*  SC0_SCL0_FRC7   */
    volatile uint8_t   dummy5[4];                              /*                  */
    volatile uint32_t  SC0_SCL0_FRC9;                          /*  SC0_SCL0_FRC9   */
    volatile uint16_t SC0_SCL0_MON0;                          /*  SC0_SCL0_MON0   */
    volatile uint16_t SC0_SCL0_INT;                           /*  SC0_SCL0_INT    */
    volatile uint32_t  SC0_SCL0_DS1;                           /*  SC0_SCL0_DS1    */
    volatile uint32_t  SC0_SCL0_DS2;                           /*  SC0_SCL0_DS2    */
    volatile uint32_t  SC0_SCL0_DS3;                           /*  SC0_SCL0_DS3    */
    volatile uint32_t  SC0_SCL0_DS4;                           /*  SC0_SCL0_DS4    */
    volatile uint32_t  SC0_SCL0_DS5;                           /*  SC0_SCL0_DS5    */
    volatile uint32_t  SC0_SCL0_DS6;                           /*  SC0_SCL0_DS6    */
    volatile uint32_t  SC0_SCL0_DS7;                           /*  SC0_SCL0_DS7    */
    volatile uint32_t  SC0_SCL0_US1;                           /*  SC0_SCL0_US1    */
    volatile uint32_t  SC0_SCL0_US2;                           /*  SC0_SCL0_US2    */
    volatile uint32_t  SC0_SCL0_US3;                           /*  SC0_SCL0_US3    */
    volatile uint32_t  SC0_SCL0_US4;                           /*  SC0_SCL0_US4    */
    volatile uint32_t  SC0_SCL0_US5;                           /*  SC0_SCL0_US5    */
    volatile uint32_t  SC0_SCL0_US6;                           /*  SC0_SCL0_US6    */
    volatile uint32_t  SC0_SCL0_US7;                           /*  SC0_SCL0_US7    */
    volatile uint32_t  SC0_SCL0_US8;                           /*  SC0_SCL0_US8    */
    volatile uint8_t   dummy6[4];                              /*                  */
    volatile uint32_t  SC0_SCL0_OVR1;                          /*  SC0_SCL0_OVR1   */
    volatile uint8_t   dummy7[16];                             /*                  */
    volatile uint32_t  SC0_SCL1_UPDATE;                        /*  SC0_SCL1_UPDATE */
    volatile uint8_t   dummy8[4];                              /*                  */
    volatile uint32_t  SC0_SCL1_WR1;                           /*  SC0_SCL1_WR1    */
    volatile uint32_t  SC0_SCL1_WR2;                           /*  SC0_SCL1_WR2    */
    volatile uint32_t  SC0_SCL1_WR3;                           /*  SC0_SCL1_WR3    */
    volatile uint32_t  SC0_SCL1_WR4;                           /*  SC0_SCL1_WR4    */
    volatile uint8_t   dummy9[4];                              /*                  */
    volatile uint32_t  SC0_SCL1_WR5;                           /*  SC0_SCL1_WR5    */
    volatile uint32_t  SC0_SCL1_WR6;                           /*  SC0_SCL1_WR6    */
    volatile uint32_t  SC0_SCL1_WR7;                           /*  SC0_SCL1_WR7    */
    volatile uint32_t  SC0_SCL1_WR8;                           /*  SC0_SCL1_WR8    */
    volatile uint32_t  SC0_SCL1_WR9;                           /*  SC0_SCL1_WR9    */
    volatile uint32_t  SC0_SCL1_WR10;                          /*  SC0_SCL1_WR10   */
};


struct st_vdc5_from_sc0_scl1_pbuf0
{
    volatile uint32_t  SC0_SCL1_PBUF0;                         /*  SC0_SCL1_PBUF0  */
    volatile uint32_t  SC0_SCL1_PBUF1;                         /*  SC0_SCL1_PBUF1  */
    volatile uint32_t  SC0_SCL1_PBUF2;                         /*  SC0_SCL1_PBUF2  */
    volatile uint32_t  SC0_SCL1_PBUF3;                         /*  SC0_SCL1_PBUF3  */
    volatile uint32_t  SC0_SCL1_PBUF_FLD;                      /*  SC0_SCL1_PBUF_FLD */
    volatile uint32_t  SC0_SCL1_PBUF_CNT;                      /*  SC0_SCL1_PBUF_CNT */
};


#define VDC50   (*(struct st_vdc5    *)0xFCFF7400uL) /* VDC50 */
#define VDC51   (*(struct st_vdc5    *)0xFCFF9400uL) /* VDC51 */


/* Start of channnel array defines of VDC5 */

/* Channnel array defines of VDC5 */
/*(Sample) value = VDC5[ channel ]->INP_UPDATE; */
#define VDC5_COUNT  2
#define VDC5_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &VDC50, &VDC51 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */



/* Channnel array defines of VDC5n_FROM_GR2_AB7_ARRAY */
/*(Sample) value = VDC5n_FROM_GR2_AB7_ARRAY[ channel ][ index ]->GR0_AB7; */
#define VDC5n_FROM_GR2_AB7_ARRAY_COUNT  2
#define VDC5n_FROM_GR2_AB7_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
{ \
    &VDC50_FROM_GR2_AB7, &VDC50_FROM_GR3_AB7 },{ \
    &VDC51_FROM_GR2_AB7, &VDC51_FROM_GR3_AB7 \
} \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define VDC50_FROM_GR2_AB7 (*(struct st_vdc5_from_gr0_ab7 *)&VDC50.GR2_AB7) /* VDC50_FROM_GR2_AB7 */
#define VDC50_FROM_GR3_AB7 (*(struct st_vdc5_from_gr0_ab7 *)&VDC50.GR3_AB7) /* VDC50_FROM_GR3_AB7 */
#define VDC51_FROM_GR2_AB7 (*(struct st_vdc5_from_gr0_ab7 *)&VDC51.GR2_AB7) /* VDC51_FROM_GR2_AB7 */
#define VDC51_FROM_GR3_AB7 (*(struct st_vdc5_from_gr0_ab7 *)&VDC51.GR3_AB7) /* VDC51_FROM_GR3_AB7 */




/* Channnel array defines of VDC5n_FROM_GR2_UPDATE_ARRAY */
/*(Sample) value = VDC5n_FROM_GR2_UPDATE_ARRAY[ channel ][ index ]->GR0_UPDATE; */
#define VDC5n_FROM_GR2_UPDATE_ARRAY_COUNT  2
#define VDC5n_FROM_GR2_UPDATE_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
{ \
    &VDC50_FROM_GR2_UPDATE, &VDC50_FROM_GR3_UPDATE },{ \
    &VDC51_FROM_GR2_UPDATE, &VDC51_FROM_GR3_UPDATE \
} \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define VDC50_FROM_GR2_UPDATE (*(struct st_vdc5_from_gr0_update *)&VDC50.GR2_UPDATE) /* VDC50_FROM_GR2_UPDATE */
#define VDC50_FROM_GR3_UPDATE (*(struct st_vdc5_from_gr0_update *)&VDC50.GR3_UPDATE) /* VDC50_FROM_GR3_UPDATE */
#define VDC51_FROM_GR2_UPDATE (*(struct st_vdc5_from_gr0_update *)&VDC51.GR2_UPDATE) /* VDC51_FROM_GR2_UPDATE */
#define VDC51_FROM_GR3_UPDATE (*(struct st_vdc5_from_gr0_update *)&VDC51.GR3_UPDATE) /* VDC51_FROM_GR3_UPDATE */




/* Channnel array defines of VDC5n_FROM_SC0_SCL1_PBUF0_ARRAY */
/*(Sample) value = VDC5n_FROM_SC0_SCL1_PBUF0_ARRAY[ channel ][ index ]->SC0_SCL1_PBUF0; */
#define VDC5n_FROM_SC0_SCL1_PBUF0_ARRAY_COUNT  2
#define VDC5n_FROM_SC0_SCL1_PBUF0_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
{ \
    &VDC50_FROM_SC0_SCL1_PBUF0, &VDC50_FROM_SC1_SCL1_PBUF0 },{ \
    &VDC51_FROM_SC0_SCL1_PBUF0, &VDC51_FROM_SC1_SCL1_PBUF0 \
} \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define VDC50_FROM_SC0_SCL1_PBUF0 (*(struct st_vdc5_from_sc0_scl1_pbuf0 *)&VDC50.SC0_SCL1_PBUF0) /* VDC50_FROM_SC0_SCL1_PBUF0 */
#define VDC50_FROM_SC1_SCL1_PBUF0 (*(struct st_vdc5_from_sc0_scl1_pbuf0 *)&VDC50.SC1_SCL1_PBUF0) /* VDC50_FROM_SC1_SCL1_PBUF0 */
#define VDC51_FROM_SC0_SCL1_PBUF0 (*(struct st_vdc5_from_sc0_scl1_pbuf0 *)&VDC51.SC0_SCL1_PBUF0) /* VDC51_FROM_SC0_SCL1_PBUF0 */
#define VDC51_FROM_SC1_SCL1_PBUF0 (*(struct st_vdc5_from_sc0_scl1_pbuf0 *)&VDC51.SC1_SCL1_PBUF0) /* VDC51_FROM_SC1_SCL1_PBUF0 */




/* Channnel array defines of VDC5n_FROM_SC0_SCL0_UPDATE_ARRAY */
/*(Sample) value = VDC5n_FROM_SC0_SCL0_UPDATE_ARRAY[ channel ][ index ]->SC0_SCL0_UPDATE; */
#define VDC5n_FROM_SC0_SCL0_UPDATE_ARRAY_COUNT  2
#define VDC5n_FROM_SC0_SCL0_UPDATE_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
{ \
    &VDC50_FROM_SC0_SCL0_UPDATE, &VDC50_FROM_SC1_SCL0_UPDATE },{ \
    &VDC51_FROM_SC0_SCL0_UPDATE, &VDC51_FROM_SC1_SCL0_UPDATE \
} \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define VDC50_FROM_SC0_SCL0_UPDATE (*(struct st_vdc5_from_sc0_scl0_update *)&VDC50.SC0_SCL0_UPDATE) /* VDC50_FROM_SC0_SCL0_UPDATE */
#define VDC50_FROM_SC1_SCL0_UPDATE (*(struct st_vdc5_from_sc0_scl0_update *)&VDC50.SC1_SCL0_UPDATE) /* VDC50_FROM_SC1_SCL0_UPDATE */
#define VDC51_FROM_SC0_SCL0_UPDATE (*(struct st_vdc5_from_sc0_scl0_update *)&VDC51.SC0_SCL0_UPDATE) /* VDC51_FROM_SC0_SCL0_UPDATE */
#define VDC51_FROM_SC1_SCL0_UPDATE (*(struct st_vdc5_from_sc0_scl0_update *)&VDC51.SC1_SCL0_UPDATE) /* VDC51_FROM_SC1_SCL0_UPDATE */




/* Channnel array defines of VDC5n_FROM_ADJ0_UPDATE_ARRAY */
/*(Sample) value = VDC5n_FROM_ADJ0_UPDATE_ARRAY[ channel ][ index ]->ADJ0_UPDATE; */
#define VDC5n_FROM_ADJ0_UPDATE_ARRAY_COUNT  2
#define VDC5n_FROM_ADJ0_UPDATE_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
{ \
    &VDC50_FROM_ADJ0_UPDATE, &VDC50_FROM_ADJ1_UPDATE },{ \
    &VDC51_FROM_ADJ0_UPDATE, &VDC51_FROM_ADJ1_UPDATE \
} \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define VDC50_FROM_ADJ0_UPDATE (*(struct st_vdc5_from_adj0_update *)&VDC50.ADJ0_UPDATE) /* VDC50_FROM_ADJ0_UPDATE */
#define VDC50_FROM_ADJ1_UPDATE (*(struct st_vdc5_from_adj0_update *)&VDC50.ADJ1_UPDATE) /* VDC50_FROM_ADJ1_UPDATE */
#define VDC51_FROM_ADJ0_UPDATE (*(struct st_vdc5_from_adj0_update *)&VDC51.ADJ0_UPDATE) /* VDC51_FROM_ADJ0_UPDATE */
#define VDC51_FROM_ADJ1_UPDATE (*(struct st_vdc5_from_adj0_update *)&VDC51.ADJ1_UPDATE) /* VDC51_FROM_ADJ1_UPDATE */




/* Channnel array defines of VDC5n_FROM_GR0_AB7_ARRAY */
/*(Sample) value = VDC5n_FROM_GR0_AB7_ARRAY[ channel ][ index ]->GR0_AB7; */
#define VDC5n_FROM_GR0_AB7_ARRAY_COUNT  2
#define VDC5n_FROM_GR0_AB7_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
{ \
    &VDC50_FROM_GR0_AB7, &VDC50_FROM_GR1_AB7 },{ \
    &VDC51_FROM_GR0_AB7, &VDC51_FROM_GR1_AB7 \
} \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define VDC50_FROM_GR0_AB7 (*(struct st_vdc5_from_gr0_ab7 *)&VDC50.GR0_AB7) /* VDC50_FROM_GR0_AB7 */
#define VDC50_FROM_GR1_AB7 (*(struct st_vdc5_from_gr0_ab7 *)&VDC50.GR1_AB7) /* VDC50_FROM_GR1_AB7 */
#define VDC51_FROM_GR0_AB7 (*(struct st_vdc5_from_gr0_ab7 *)&VDC51.GR0_AB7) /* VDC51_FROM_GR0_AB7 */
#define VDC51_FROM_GR1_AB7 (*(struct st_vdc5_from_gr0_ab7 *)&VDC51.GR1_AB7) /* VDC51_FROM_GR1_AB7 */




/* Channnel array defines of VDC5n_FROM_GR0_UPDATE_ARRAY */
/*(Sample) value = VDC5n_FROM_GR0_UPDATE_ARRAY[ channel ][ index ]->GR0_UPDATE; */
#define VDC5n_FROM_GR0_UPDATE_ARRAY_COUNT  2
#define VDC5n_FROM_GR0_UPDATE_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
{ \
    &VDC50_FROM_GR0_UPDATE, &VDC50_FROM_GR1_UPDATE },{ \
    &VDC51_FROM_GR0_UPDATE, &VDC51_FROM_GR1_UPDATE \
} \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define VDC50_FROM_GR0_UPDATE (*(struct st_vdc5_from_gr0_update *)&VDC50.GR0_UPDATE) /* VDC50_FROM_GR0_UPDATE */
#define VDC50_FROM_GR1_UPDATE (*(struct st_vdc5_from_gr0_update *)&VDC50.GR1_UPDATE) /* VDC50_FROM_GR1_UPDATE */
#define VDC51_FROM_GR0_UPDATE (*(struct st_vdc5_from_gr0_update *)&VDC51.GR0_UPDATE) /* VDC51_FROM_GR0_UPDATE */
#define VDC51_FROM_GR1_UPDATE (*(struct st_vdc5_from_gr0_update *)&VDC51.GR1_UPDATE) /* VDC51_FROM_GR1_UPDATE */


/* End of channnel array defines of VDC5 */


#define VDC50INP_UPDATE VDC50.INP_UPDATE
#define VDC50INP_SEL_CNT VDC50.INP_SEL_CNT
#define VDC50INP_EXT_SYNC_CNT VDC50.INP_EXT_SYNC_CNT
#define VDC50INP_VSYNC_PH_ADJ VDC50.INP_VSYNC_PH_ADJ
#define VDC50INP_DLY_ADJ VDC50.INP_DLY_ADJ
#define VDC50IMGCNT_UPDATE VDC50.IMGCNT_UPDATE
#define VDC50IMGCNT_NR_CNT0 VDC50.IMGCNT_NR_CNT0
#define VDC50IMGCNT_NR_CNT1 VDC50.IMGCNT_NR_CNT1
#define VDC50IMGCNT_MTX_MODE VDC50.IMGCNT_MTX_MODE
#define VDC50IMGCNT_MTX_YG_ADJ0 VDC50.IMGCNT_MTX_YG_ADJ0
#define VDC50IMGCNT_MTX_YG_ADJ1 VDC50.IMGCNT_MTX_YG_ADJ1
#define VDC50IMGCNT_MTX_CBB_ADJ0 VDC50.IMGCNT_MTX_CBB_ADJ0
#define VDC50IMGCNT_MTX_CBB_ADJ1 VDC50.IMGCNT_MTX_CBB_ADJ1
#define VDC50IMGCNT_MTX_CRR_ADJ0 VDC50.IMGCNT_MTX_CRR_ADJ0
#define VDC50IMGCNT_MTX_CRR_ADJ1 VDC50.IMGCNT_MTX_CRR_ADJ1
#define VDC50IMGCNT_DRC_REG VDC50.IMGCNT_DRC_REG
#define VDC50SC0_SCL0_UPDATE VDC50.SC0_SCL0_UPDATE
#define VDC50SC0_SCL0_FRC1 VDC50.SC0_SCL0_FRC1
#define VDC50SC0_SCL0_FRC2 VDC50.SC0_SCL0_FRC2
#define VDC50SC0_SCL0_FRC3 VDC50.SC0_SCL0_FRC3
#define VDC50SC0_SCL0_FRC4 VDC50.SC0_SCL0_FRC4
#define VDC50SC0_SCL0_FRC5 VDC50.SC0_SCL0_FRC5
#define VDC50SC0_SCL0_FRC6 VDC50.SC0_SCL0_FRC6
#define VDC50SC0_SCL0_FRC7 VDC50.SC0_SCL0_FRC7
#define VDC50SC0_SCL0_FRC9 VDC50.SC0_SCL0_FRC9
#define VDC50SC0_SCL0_MON0 VDC50.SC0_SCL0_MON0
#define VDC50SC0_SCL0_INT VDC50.SC0_SCL0_INT
#define VDC50SC0_SCL0_DS1 VDC50.SC0_SCL0_DS1
#define VDC50SC0_SCL0_DS2 VDC50.SC0_SCL0_DS2
#define VDC50SC0_SCL0_DS3 VDC50.SC0_SCL0_DS3
#define VDC50SC0_SCL0_DS4 VDC50.SC0_SCL0_DS4
#define VDC50SC0_SCL0_DS5 VDC50.SC0_SCL0_DS5
#define VDC50SC0_SCL0_DS6 VDC50.SC0_SCL0_DS6
#define VDC50SC0_SCL0_DS7 VDC50.SC0_SCL0_DS7
#define VDC50SC0_SCL0_US1 VDC50.SC0_SCL0_US1
#define VDC50SC0_SCL0_US2 VDC50.SC0_SCL0_US2
#define VDC50SC0_SCL0_US3 VDC50.SC0_SCL0_US3
#define VDC50SC0_SCL0_US4 VDC50.SC0_SCL0_US4
#define VDC50SC0_SCL0_US5 VDC50.SC0_SCL0_US5
#define VDC50SC0_SCL0_US6 VDC50.SC0_SCL0_US6
#define VDC50SC0_SCL0_US7 VDC50.SC0_SCL0_US7
#define VDC50SC0_SCL0_US8 VDC50.SC0_SCL0_US8
#define VDC50SC0_SCL0_OVR1 VDC50.SC0_SCL0_OVR1
#define VDC50SC0_SCL1_UPDATE VDC50.SC0_SCL1_UPDATE
#define VDC50SC0_SCL1_WR1 VDC50.SC0_SCL1_WR1
#define VDC50SC0_SCL1_WR2 VDC50.SC0_SCL1_WR2
#define VDC50SC0_SCL1_WR3 VDC50.SC0_SCL1_WR3
#define VDC50SC0_SCL1_WR4 VDC50.SC0_SCL1_WR4
#define VDC50SC0_SCL1_WR5 VDC50.SC0_SCL1_WR5
#define VDC50SC0_SCL1_WR6 VDC50.SC0_SCL1_WR6
#define VDC50SC0_SCL1_WR7 VDC50.SC0_SCL1_WR7
#define VDC50SC0_SCL1_WR8 VDC50.SC0_SCL1_WR8
#define VDC50SC0_SCL1_WR9 VDC50.SC0_SCL1_WR9
#define VDC50SC0_SCL1_WR10 VDC50.SC0_SCL1_WR10
#define VDC50SC0_SCL1_WR11 VDC50.SC0_SCL1_WR11
#define VDC50SC0_SCL1_MON1 VDC50.SC0_SCL1_MON1
#define VDC50SC0_SCL1_PBUF0 VDC50.SC0_SCL1_PBUF0
#define VDC50SC0_SCL1_PBUF1 VDC50.SC0_SCL1_PBUF1
#define VDC50SC0_SCL1_PBUF2 VDC50.SC0_SCL1_PBUF2
#define VDC50SC0_SCL1_PBUF3 VDC50.SC0_SCL1_PBUF3
#define VDC50SC0_SCL1_PBUF_FLD VDC50.SC0_SCL1_PBUF_FLD
#define VDC50SC0_SCL1_PBUF_CNT VDC50.SC0_SCL1_PBUF_CNT
#define VDC50GR0_UPDATE VDC50.GR0_UPDATE
#define VDC50GR0_FLM_RD VDC50.GR0_FLM_RD
#define VDC50GR0_FLM1 VDC50.GR0_FLM1
#define VDC50GR0_FLM2 VDC50.GR0_FLM2
#define VDC50GR0_FLM3 VDC50.GR0_FLM3
#define VDC50GR0_FLM4 VDC50.GR0_FLM4
#define VDC50GR0_FLM5 VDC50.GR0_FLM5
#define VDC50GR0_FLM6 VDC50.GR0_FLM6
#define VDC50GR0_AB1 VDC50.GR0_AB1
#define VDC50GR0_AB2 VDC50.GR0_AB2
#define VDC50GR0_AB3 VDC50.GR0_AB3
#define VDC50GR0_AB7 VDC50.GR0_AB7
#define VDC50GR0_AB8 VDC50.GR0_AB8
#define VDC50GR0_AB9 VDC50.GR0_AB9
#define VDC50GR0_AB10 VDC50.GR0_AB10
#define VDC50GR0_AB11 VDC50.GR0_AB11
#define VDC50GR0_BASE VDC50.GR0_BASE
#define VDC50GR0_CLUT VDC50.GR0_CLUT
#define VDC50ADJ0_UPDATE VDC50.ADJ0_UPDATE
#define VDC50ADJ0_BKSTR_SET VDC50.ADJ0_BKSTR_SET
#define VDC50ADJ0_ENH_TIM1 VDC50.ADJ0_ENH_TIM1
#define VDC50ADJ0_ENH_TIM2 VDC50.ADJ0_ENH_TIM2
#define VDC50ADJ0_ENH_TIM3 VDC50.ADJ0_ENH_TIM3
#define VDC50ADJ0_ENH_SHP1 VDC50.ADJ0_ENH_SHP1
#define VDC50ADJ0_ENH_SHP2 VDC50.ADJ0_ENH_SHP2
#define VDC50ADJ0_ENH_SHP3 VDC50.ADJ0_ENH_SHP3
#define VDC50ADJ0_ENH_SHP4 VDC50.ADJ0_ENH_SHP4
#define VDC50ADJ0_ENH_SHP5 VDC50.ADJ0_ENH_SHP5
#define VDC50ADJ0_ENH_SHP6 VDC50.ADJ0_ENH_SHP6
#define VDC50ADJ0_ENH_LTI1 VDC50.ADJ0_ENH_LTI1
#define VDC50ADJ0_ENH_LTI2 VDC50.ADJ0_ENH_LTI2
#define VDC50ADJ0_MTX_MODE VDC50.ADJ0_MTX_MODE
#define VDC50ADJ0_MTX_YG_ADJ0 VDC50.ADJ0_MTX_YG_ADJ0
#define VDC50ADJ0_MTX_YG_ADJ1 VDC50.ADJ0_MTX_YG_ADJ1
#define VDC50ADJ0_MTX_CBB_ADJ0 VDC50.ADJ0_MTX_CBB_ADJ0
#define VDC50ADJ0_MTX_CBB_ADJ1 VDC50.ADJ0_MTX_CBB_ADJ1
#define VDC50ADJ0_MTX_CRR_ADJ0 VDC50.ADJ0_MTX_CRR_ADJ0
#define VDC50ADJ0_MTX_CRR_ADJ1 VDC50.ADJ0_MTX_CRR_ADJ1
#define VDC50GR2_UPDATE VDC50.GR2_UPDATE
#define VDC50GR2_FLM_RD VDC50.GR2_FLM_RD
#define VDC50GR2_FLM1 VDC50.GR2_FLM1
#define VDC50GR2_FLM2 VDC50.GR2_FLM2
#define VDC50GR2_FLM3 VDC50.GR2_FLM3
#define VDC50GR2_FLM4 VDC50.GR2_FLM4
#define VDC50GR2_FLM5 VDC50.GR2_FLM5
#define VDC50GR2_FLM6 VDC50.GR2_FLM6
#define VDC50GR2_AB1 VDC50.GR2_AB1
#define VDC50GR2_AB2 VDC50.GR2_AB2
#define VDC50GR2_AB3 VDC50.GR2_AB3
#define VDC50GR2_AB4 VDC50.GR2_AB4
#define VDC50GR2_AB5 VDC50.GR2_AB5
#define VDC50GR2_AB6 VDC50.GR2_AB6
#define VDC50GR2_AB7 VDC50.GR2_AB7
#define VDC50GR2_AB8 VDC50.GR2_AB8
#define VDC50GR2_AB9 VDC50.GR2_AB9
#define VDC50GR2_AB10 VDC50.GR2_AB10
#define VDC50GR2_AB11 VDC50.GR2_AB11
#define VDC50GR2_BASE VDC50.GR2_BASE
#define VDC50GR2_CLUT VDC50.GR2_CLUT
#define VDC50GR2_MON VDC50.GR2_MON
#define VDC50GR3_UPDATE VDC50.GR3_UPDATE
#define VDC50GR3_FLM_RD VDC50.GR3_FLM_RD
#define VDC50GR3_FLM1 VDC50.GR3_FLM1
#define VDC50GR3_FLM2 VDC50.GR3_FLM2
#define VDC50GR3_FLM3 VDC50.GR3_FLM3
#define VDC50GR3_FLM4 VDC50.GR3_FLM4
#define VDC50GR3_FLM5 VDC50.GR3_FLM5
#define VDC50GR3_FLM6 VDC50.GR3_FLM6
#define VDC50GR3_AB1 VDC50.GR3_AB1
#define VDC50GR3_AB2 VDC50.GR3_AB2
#define VDC50GR3_AB3 VDC50.GR3_AB3
#define VDC50GR3_AB4 VDC50.GR3_AB4
#define VDC50GR3_AB5 VDC50.GR3_AB5
#define VDC50GR3_AB6 VDC50.GR3_AB6
#define VDC50GR3_AB7 VDC50.GR3_AB7
#define VDC50GR3_AB8 VDC50.GR3_AB8
#define VDC50GR3_AB9 VDC50.GR3_AB9
#define VDC50GR3_AB10 VDC50.GR3_AB10
#define VDC50GR3_AB11 VDC50.GR3_AB11
#define VDC50GR3_BASE VDC50.GR3_BASE
#define VDC50GR3_CLUT_INT VDC50.GR3_CLUT_INT
#define VDC50GR3_MON VDC50.GR3_MON
#define VDC50GAM_G_UPDATE VDC50.GAM_G_UPDATE
#define VDC50GAM_SW VDC50.GAM_SW
#define VDC50GAM_G_LUT1 VDC50.GAM_G_LUT1
#define VDC50GAM_G_LUT2 VDC50.GAM_G_LUT2
#define VDC50GAM_G_LUT3 VDC50.GAM_G_LUT3
#define VDC50GAM_G_LUT4 VDC50.GAM_G_LUT4
#define VDC50GAM_G_LUT5 VDC50.GAM_G_LUT5
#define VDC50GAM_G_LUT6 VDC50.GAM_G_LUT6
#define VDC50GAM_G_LUT7 VDC50.GAM_G_LUT7
#define VDC50GAM_G_LUT8 VDC50.GAM_G_LUT8
#define VDC50GAM_G_LUT9 VDC50.GAM_G_LUT9
#define VDC50GAM_G_LUT10 VDC50.GAM_G_LUT10
#define VDC50GAM_G_LUT11 VDC50.GAM_G_LUT11
#define VDC50GAM_G_LUT12 VDC50.GAM_G_LUT12
#define VDC50GAM_G_LUT13 VDC50.GAM_G_LUT13
#define VDC50GAM_G_LUT14 VDC50.GAM_G_LUT14
#define VDC50GAM_G_LUT15 VDC50.GAM_G_LUT15
#define VDC50GAM_G_LUT16 VDC50.GAM_G_LUT16
#define VDC50GAM_G_AREA1 VDC50.GAM_G_AREA1
#define VDC50GAM_G_AREA2 VDC50.GAM_G_AREA2
#define VDC50GAM_G_AREA3 VDC50.GAM_G_AREA3
#define VDC50GAM_G_AREA4 VDC50.GAM_G_AREA4
#define VDC50GAM_G_AREA5 VDC50.GAM_G_AREA5
#define VDC50GAM_G_AREA6 VDC50.GAM_G_AREA6
#define VDC50GAM_G_AREA7 VDC50.GAM_G_AREA7
#define VDC50GAM_G_AREA8 VDC50.GAM_G_AREA8
#define VDC50GAM_B_UPDATE VDC50.GAM_B_UPDATE
#define VDC50GAM_B_LUT1 VDC50.GAM_B_LUT1
#define VDC50GAM_B_LUT2 VDC50.GAM_B_LUT2
#define VDC50GAM_B_LUT3 VDC50.GAM_B_LUT3
#define VDC50GAM_B_LUT4 VDC50.GAM_B_LUT4
#define VDC50GAM_B_LUT5 VDC50.GAM_B_LUT5
#define VDC50GAM_B_LUT6 VDC50.GAM_B_LUT6
#define VDC50GAM_B_LUT7 VDC50.GAM_B_LUT7
#define VDC50GAM_B_LUT8 VDC50.GAM_B_LUT8
#define VDC50GAM_B_LUT9 VDC50.GAM_B_LUT9
#define VDC50GAM_B_LUT10 VDC50.GAM_B_LUT10
#define VDC50GAM_B_LUT11 VDC50.GAM_B_LUT11
#define VDC50GAM_B_LUT12 VDC50.GAM_B_LUT12
#define VDC50GAM_B_LUT13 VDC50.GAM_B_LUT13
#define VDC50GAM_B_LUT14 VDC50.GAM_B_LUT14
#define VDC50GAM_B_LUT15 VDC50.GAM_B_LUT15
#define VDC50GAM_B_LUT16 VDC50.GAM_B_LUT16
#define VDC50GAM_B_AREA1 VDC50.GAM_B_AREA1
#define VDC50GAM_B_AREA2 VDC50.GAM_B_AREA2
#define VDC50GAM_B_AREA3 VDC50.GAM_B_AREA3
#define VDC50GAM_B_AREA4 VDC50.GAM_B_AREA4
#define VDC50GAM_B_AREA5 VDC50.GAM_B_AREA5
#define VDC50GAM_B_AREA6 VDC50.GAM_B_AREA6
#define VDC50GAM_B_AREA7 VDC50.GAM_B_AREA7
#define VDC50GAM_B_AREA8 VDC50.GAM_B_AREA8
#define VDC50GAM_R_UPDATE VDC50.GAM_R_UPDATE
#define VDC50GAM_R_LUT1 VDC50.GAM_R_LUT1
#define VDC50GAM_R_LUT2 VDC50.GAM_R_LUT2
#define VDC50GAM_R_LUT3 VDC50.GAM_R_LUT3
#define VDC50GAM_R_LUT4 VDC50.GAM_R_LUT4
#define VDC50GAM_R_LUT5 VDC50.GAM_R_LUT5
#define VDC50GAM_R_LUT6 VDC50.GAM_R_LUT6
#define VDC50GAM_R_LUT7 VDC50.GAM_R_LUT7
#define VDC50GAM_R_LUT8 VDC50.GAM_R_LUT8
#define VDC50GAM_R_LUT9 VDC50.GAM_R_LUT9
#define VDC50GAM_R_LUT10 VDC50.GAM_R_LUT10
#define VDC50GAM_R_LUT11 VDC50.GAM_R_LUT11
#define VDC50GAM_R_LUT12 VDC50.GAM_R_LUT12
#define VDC50GAM_R_LUT13 VDC50.GAM_R_LUT13
#define VDC50GAM_R_LUT14 VDC50.GAM_R_LUT14
#define VDC50GAM_R_LUT15 VDC50.GAM_R_LUT15
#define VDC50GAM_R_LUT16 VDC50.GAM_R_LUT16
#define VDC50GAM_R_AREA1 VDC50.GAM_R_AREA1
#define VDC50GAM_R_AREA2 VDC50.GAM_R_AREA2
#define VDC50GAM_R_AREA3 VDC50.GAM_R_AREA3
#define VDC50GAM_R_AREA4 VDC50.GAM_R_AREA4
#define VDC50GAM_R_AREA5 VDC50.GAM_R_AREA5
#define VDC50GAM_R_AREA6 VDC50.GAM_R_AREA6
#define VDC50GAM_R_AREA7 VDC50.GAM_R_AREA7
#define VDC50GAM_R_AREA8 VDC50.GAM_R_AREA8
#define VDC50TCON_UPDATE VDC50.TCON_UPDATE
#define VDC50TCON_TIM VDC50.TCON_TIM
#define VDC50TCON_TIM_STVA1 VDC50.TCON_TIM_STVA1
#define VDC50TCON_TIM_STVA2 VDC50.TCON_TIM_STVA2
#define VDC50TCON_TIM_STVB1 VDC50.TCON_TIM_STVB1
#define VDC50TCON_TIM_STVB2 VDC50.TCON_TIM_STVB2
#define VDC50TCON_TIM_STH1 VDC50.TCON_TIM_STH1
#define VDC50TCON_TIM_STH2 VDC50.TCON_TIM_STH2
#define VDC50TCON_TIM_STB1 VDC50.TCON_TIM_STB1
#define VDC50TCON_TIM_STB2 VDC50.TCON_TIM_STB2
#define VDC50TCON_TIM_CPV1 VDC50.TCON_TIM_CPV1
#define VDC50TCON_TIM_CPV2 VDC50.TCON_TIM_CPV2
#define VDC50TCON_TIM_POLA1 VDC50.TCON_TIM_POLA1
#define VDC50TCON_TIM_POLA2 VDC50.TCON_TIM_POLA2
#define VDC50TCON_TIM_POLB1 VDC50.TCON_TIM_POLB1
#define VDC50TCON_TIM_POLB2 VDC50.TCON_TIM_POLB2
#define VDC50TCON_TIM_DE VDC50.TCON_TIM_DE
#define VDC50OUT_UPDATE VDC50.OUT_UPDATE
#define VDC50OUT_SET VDC50.OUT_SET
#define VDC50OUT_BRIGHT1 VDC50.OUT_BRIGHT1
#define VDC50OUT_BRIGHT2 VDC50.OUT_BRIGHT2
#define VDC50OUT_CONTRAST VDC50.OUT_CONTRAST
#define VDC50OUT_PDTHA VDC50.OUT_PDTHA
#define VDC50OUT_CLK_PHASE VDC50.OUT_CLK_PHASE
#define VDC50SYSCNT_INT1 VDC50.SYSCNT_INT1
#define VDC50SYSCNT_INT2 VDC50.SYSCNT_INT2
#define VDC50SYSCNT_INT3 VDC50.SYSCNT_INT3
#define VDC50SYSCNT_INT4 VDC50.SYSCNT_INT4
#define VDC50SYSCNT_INT5 VDC50.SYSCNT_INT5
#define VDC50SYSCNT_INT6 VDC50.SYSCNT_INT6
#define VDC50SYSCNT_PANEL_CLK VDC50.SYSCNT_PANEL_CLK
#define VDC50SYSCNT_CLUT VDC50.SYSCNT_CLUT
#define VDC50SC1_SCL0_UPDATE VDC50.SC1_SCL0_UPDATE
#define VDC50SC1_SCL0_FRC1 VDC50.SC1_SCL0_FRC1
#define VDC50SC1_SCL0_FRC2 VDC50.SC1_SCL0_FRC2
#define VDC50SC1_SCL0_FRC3 VDC50.SC1_SCL0_FRC3
#define VDC50SC1_SCL0_FRC4 VDC50.SC1_SCL0_FRC4
#define VDC50SC1_SCL0_FRC5 VDC50.SC1_SCL0_FRC5
#define VDC50SC1_SCL0_FRC6 VDC50.SC1_SCL0_FRC6
#define VDC50SC1_SCL0_FRC7 VDC50.SC1_SCL0_FRC7
#define VDC50SC1_SCL0_FRC9 VDC50.SC1_SCL0_FRC9
#define VDC50SC1_SCL0_MON0 VDC50.SC1_SCL0_MON0
#define VDC50SC1_SCL0_INT VDC50.SC1_SCL0_INT
#define VDC50SC1_SCL0_DS1 VDC50.SC1_SCL0_DS1
#define VDC50SC1_SCL0_DS2 VDC50.SC1_SCL0_DS2
#define VDC50SC1_SCL0_DS3 VDC50.SC1_SCL0_DS3
#define VDC50SC1_SCL0_DS4 VDC50.SC1_SCL0_DS4
#define VDC50SC1_SCL0_DS5 VDC50.SC1_SCL0_DS5
#define VDC50SC1_SCL0_DS6 VDC50.SC1_SCL0_DS6
#define VDC50SC1_SCL0_DS7 VDC50.SC1_SCL0_DS7
#define VDC50SC1_SCL0_US1 VDC50.SC1_SCL0_US1
#define VDC50SC1_SCL0_US2 VDC50.SC1_SCL0_US2
#define VDC50SC1_SCL0_US3 VDC50.SC1_SCL0_US3
#define VDC50SC1_SCL0_US4 VDC50.SC1_SCL0_US4
#define VDC50SC1_SCL0_US5 VDC50.SC1_SCL0_US5
#define VDC50SC1_SCL0_US6 VDC50.SC1_SCL0_US6
#define VDC50SC1_SCL0_US7 VDC50.SC1_SCL0_US7
#define VDC50SC1_SCL0_US8 VDC50.SC1_SCL0_US8
#define VDC50SC1_SCL0_OVR1 VDC50.SC1_SCL0_OVR1
#define VDC50SC1_SCL1_UPDATE VDC50.SC1_SCL1_UPDATE
#define VDC50SC1_SCL1_WR1 VDC50.SC1_SCL1_WR1
#define VDC50SC1_SCL1_WR2 VDC50.SC1_SCL1_WR2
#define VDC50SC1_SCL1_WR3 VDC50.SC1_SCL1_WR3
#define VDC50SC1_SCL1_WR4 VDC50.SC1_SCL1_WR4
#define VDC50SC1_SCL1_WR5 VDC50.SC1_SCL1_WR5
#define VDC50SC1_SCL1_WR6 VDC50.SC1_SCL1_WR6
#define VDC50SC1_SCL1_WR7 VDC50.SC1_SCL1_WR7
#define VDC50SC1_SCL1_WR8 VDC50.SC1_SCL1_WR8
#define VDC50SC1_SCL1_WR9 VDC50.SC1_SCL1_WR9
#define VDC50SC1_SCL1_WR10 VDC50.SC1_SCL1_WR10
#define VDC50SC1_SCL1_WR11 VDC50.SC1_SCL1_WR11
#define VDC50SC1_SCL1_MON1 VDC50.SC1_SCL1_MON1
#define VDC50SC1_SCL1_PBUF0 VDC50.SC1_SCL1_PBUF0
#define VDC50SC1_SCL1_PBUF1 VDC50.SC1_SCL1_PBUF1
#define VDC50SC1_SCL1_PBUF2 VDC50.SC1_SCL1_PBUF2
#define VDC50SC1_SCL1_PBUF3 VDC50.SC1_SCL1_PBUF3
#define VDC50SC1_SCL1_PBUF_FLD VDC50.SC1_SCL1_PBUF_FLD
#define VDC50SC1_SCL1_PBUF_CNT VDC50.SC1_SCL1_PBUF_CNT
#define VDC50GR1_UPDATE VDC50.GR1_UPDATE
#define VDC50GR1_FLM_RD VDC50.GR1_FLM_RD
#define VDC50GR1_FLM1 VDC50.GR1_FLM1
#define VDC50GR1_FLM2 VDC50.GR1_FLM2
#define VDC50GR1_FLM3 VDC50.GR1_FLM3
#define VDC50GR1_FLM4 VDC50.GR1_FLM4
#define VDC50GR1_FLM5 VDC50.GR1_FLM5
#define VDC50GR1_FLM6 VDC50.GR1_FLM6
#define VDC50GR1_AB1 VDC50.GR1_AB1
#define VDC50GR1_AB2 VDC50.GR1_AB2
#define VDC50GR1_AB3 VDC50.GR1_AB3
#define VDC50GR1_AB4 VDC50.GR1_AB4
#define VDC50GR1_AB5 VDC50.GR1_AB5
#define VDC50GR1_AB6 VDC50.GR1_AB6
#define VDC50GR1_AB7 VDC50.GR1_AB7
#define VDC50GR1_AB8 VDC50.GR1_AB8
#define VDC50GR1_AB9 VDC50.GR1_AB9
#define VDC50GR1_AB10 VDC50.GR1_AB10
#define VDC50GR1_AB11 VDC50.GR1_AB11
#define VDC50GR1_BASE VDC50.GR1_BASE
#define VDC50GR1_CLUT VDC50.GR1_CLUT
#define VDC50GR1_MON VDC50.GR1_MON
#define VDC50ADJ1_UPDATE VDC50.ADJ1_UPDATE
#define VDC50ADJ1_BKSTR_SET VDC50.ADJ1_BKSTR_SET
#define VDC50ADJ1_ENH_TIM1 VDC50.ADJ1_ENH_TIM1
#define VDC50ADJ1_ENH_TIM2 VDC50.ADJ1_ENH_TIM2
#define VDC50ADJ1_ENH_TIM3 VDC50.ADJ1_ENH_TIM3
#define VDC50ADJ1_ENH_SHP1 VDC50.ADJ1_ENH_SHP1
#define VDC50ADJ1_ENH_SHP2 VDC50.ADJ1_ENH_SHP2
#define VDC50ADJ1_ENH_SHP3 VDC50.ADJ1_ENH_SHP3
#define VDC50ADJ1_ENH_SHP4 VDC50.ADJ1_ENH_SHP4
#define VDC50ADJ1_ENH_SHP5 VDC50.ADJ1_ENH_SHP5
#define VDC50ADJ1_ENH_SHP6 VDC50.ADJ1_ENH_SHP6
#define VDC50ADJ1_ENH_LTI1 VDC50.ADJ1_ENH_LTI1
#define VDC50ADJ1_ENH_LTI2 VDC50.ADJ1_ENH_LTI2
#define VDC50ADJ1_MTX_MODE VDC50.ADJ1_MTX_MODE
#define VDC50ADJ1_MTX_YG_ADJ0 VDC50.ADJ1_MTX_YG_ADJ0
#define VDC50ADJ1_MTX_YG_ADJ1 VDC50.ADJ1_MTX_YG_ADJ1
#define VDC50ADJ1_MTX_CBB_ADJ0 VDC50.ADJ1_MTX_CBB_ADJ0
#define VDC50ADJ1_MTX_CBB_ADJ1 VDC50.ADJ1_MTX_CBB_ADJ1
#define VDC50ADJ1_MTX_CRR_ADJ0 VDC50.ADJ1_MTX_CRR_ADJ0
#define VDC50ADJ1_MTX_CRR_ADJ1 VDC50.ADJ1_MTX_CRR_ADJ1
#define VDC50GR_VIN_UPDATE VDC50.GR_VIN_UPDATE
#define VDC50GR_VIN_AB1 VDC50.GR_VIN_AB1
#define VDC50GR_VIN_AB2 VDC50.GR_VIN_AB2
#define VDC50GR_VIN_AB3 VDC50.GR_VIN_AB3
#define VDC50GR_VIN_AB4 VDC50.GR_VIN_AB4
#define VDC50GR_VIN_AB5 VDC50.GR_VIN_AB5
#define VDC50GR_VIN_AB6 VDC50.GR_VIN_AB6
#define VDC50GR_VIN_AB7 VDC50.GR_VIN_AB7
#define VDC50GR_VIN_BASE VDC50.GR_VIN_BASE
#define VDC50GR_VIN_MON VDC50.GR_VIN_MON
#define VDC50OIR_SCL0_UPDATE VDC50.OIR_SCL0_UPDATE
#define VDC50OIR_SCL0_FRC1 VDC50.OIR_SCL0_FRC1
#define VDC50OIR_SCL0_FRC2 VDC50.OIR_SCL0_FRC2
#define VDC50OIR_SCL0_FRC3 VDC50.OIR_SCL0_FRC3
#define VDC50OIR_SCL0_FRC4 VDC50.OIR_SCL0_FRC4
#define VDC50OIR_SCL0_FRC5 VDC50.OIR_SCL0_FRC5
#define VDC50OIR_SCL0_FRC6 VDC50.OIR_SCL0_FRC6
#define VDC50OIR_SCL0_FRC7 VDC50.OIR_SCL0_FRC7
#define VDC50OIR_SCL0_DS1 VDC50.OIR_SCL0_DS1
#define VDC50OIR_SCL0_DS2 VDC50.OIR_SCL0_DS2
#define VDC50OIR_SCL0_DS3 VDC50.OIR_SCL0_DS3
#define VDC50OIR_SCL0_DS7 VDC50.OIR_SCL0_DS7
#define VDC50OIR_SCL0_US1 VDC50.OIR_SCL0_US1
#define VDC50OIR_SCL0_US2 VDC50.OIR_SCL0_US2
#define VDC50OIR_SCL0_US3 VDC50.OIR_SCL0_US3
#define VDC50OIR_SCL0_US8 VDC50.OIR_SCL0_US8
#define VDC50OIR_SCL0_OVR1 VDC50.OIR_SCL0_OVR1
#define VDC50OIR_SCL1_UPDATE VDC50.OIR_SCL1_UPDATE
#define VDC50OIR_SCL1_WR1 VDC50.OIR_SCL1_WR1
#define VDC50OIR_SCL1_WR2 VDC50.OIR_SCL1_WR2
#define VDC50OIR_SCL1_WR3 VDC50.OIR_SCL1_WR3
#define VDC50OIR_SCL1_WR4 VDC50.OIR_SCL1_WR4
#define VDC50OIR_SCL1_WR5 VDC50.OIR_SCL1_WR5
#define VDC50OIR_SCL1_WR6 VDC50.OIR_SCL1_WR6
#define VDC50OIR_SCL1_WR7 VDC50.OIR_SCL1_WR7
#define VDC50GR_OIR_UPDATE VDC50.GR_OIR_UPDATE
#define VDC50GR_OIR_FLM_RD VDC50.GR_OIR_FLM_RD
#define VDC50GR_OIR_FLM1 VDC50.GR_OIR_FLM1
#define VDC50GR_OIR_FLM2 VDC50.GR_OIR_FLM2
#define VDC50GR_OIR_FLM3 VDC50.GR_OIR_FLM3
#define VDC50GR_OIR_FLM4 VDC50.GR_OIR_FLM4
#define VDC50GR_OIR_FLM5 VDC50.GR_OIR_FLM5
#define VDC50GR_OIR_FLM6 VDC50.GR_OIR_FLM6
#define VDC50GR_OIR_AB1 VDC50.GR_OIR_AB1
#define VDC50GR_OIR_AB2 VDC50.GR_OIR_AB2
#define VDC50GR_OIR_AB3 VDC50.GR_OIR_AB3
#define VDC50GR_OIR_AB7 VDC50.GR_OIR_AB7
#define VDC50GR_OIR_AB8 VDC50.GR_OIR_AB8
#define VDC50GR_OIR_AB9 VDC50.GR_OIR_AB9
#define VDC50GR_OIR_AB10 VDC50.GR_OIR_AB10
#define VDC50GR_OIR_AB11 VDC50.GR_OIR_AB11
#define VDC50GR_OIR_BASE VDC50.GR_OIR_BASE
#define VDC50GR_OIR_CLUT VDC50.GR_OIR_CLUT
#define VDC50GR_OIR_MON VDC50.GR_OIR_MON
#define VDC51INP_UPDATE VDC51.INP_UPDATE
#define VDC51INP_SEL_CNT VDC51.INP_SEL_CNT
#define VDC51INP_EXT_SYNC_CNT VDC51.INP_EXT_SYNC_CNT
#define VDC51INP_VSYNC_PH_ADJ VDC51.INP_VSYNC_PH_ADJ
#define VDC51INP_DLY_ADJ VDC51.INP_DLY_ADJ
#define VDC51IMGCNT_UPDATE VDC51.IMGCNT_UPDATE
#define VDC51IMGCNT_NR_CNT0 VDC51.IMGCNT_NR_CNT0
#define VDC51IMGCNT_NR_CNT1 VDC51.IMGCNT_NR_CNT1
#define VDC51IMGCNT_MTX_MODE VDC51.IMGCNT_MTX_MODE
#define VDC51IMGCNT_MTX_YG_ADJ0 VDC51.IMGCNT_MTX_YG_ADJ0
#define VDC51IMGCNT_MTX_YG_ADJ1 VDC51.IMGCNT_MTX_YG_ADJ1
#define VDC51IMGCNT_MTX_CBB_ADJ0 VDC51.IMGCNT_MTX_CBB_ADJ0
#define VDC51IMGCNT_MTX_CBB_ADJ1 VDC51.IMGCNT_MTX_CBB_ADJ1
#define VDC51IMGCNT_MTX_CRR_ADJ0 VDC51.IMGCNT_MTX_CRR_ADJ0
#define VDC51IMGCNT_MTX_CRR_ADJ1 VDC51.IMGCNT_MTX_CRR_ADJ1
#define VDC51IMGCNT_DRC_REG VDC51.IMGCNT_DRC_REG
#define VDC51SC0_SCL0_UPDATE VDC51.SC0_SCL0_UPDATE
#define VDC51SC0_SCL0_FRC1 VDC51.SC0_SCL0_FRC1
#define VDC51SC0_SCL0_FRC2 VDC51.SC0_SCL0_FRC2
#define VDC51SC0_SCL0_FRC3 VDC51.SC0_SCL0_FRC3
#define VDC51SC0_SCL0_FRC4 VDC51.SC0_SCL0_FRC4
#define VDC51SC0_SCL0_FRC5 VDC51.SC0_SCL0_FRC5
#define VDC51SC0_SCL0_FRC6 VDC51.SC0_SCL0_FRC6
#define VDC51SC0_SCL0_FRC7 VDC51.SC0_SCL0_FRC7
#define VDC51SC0_SCL0_FRC9 VDC51.SC0_SCL0_FRC9
#define VDC51SC0_SCL0_MON0 VDC51.SC0_SCL0_MON0
#define VDC51SC0_SCL0_INT VDC51.SC0_SCL0_INT
#define VDC51SC0_SCL0_DS1 VDC51.SC0_SCL0_DS1
#define VDC51SC0_SCL0_DS2 VDC51.SC0_SCL0_DS2
#define VDC51SC0_SCL0_DS3 VDC51.SC0_SCL0_DS3
#define VDC51SC0_SCL0_DS4 VDC51.SC0_SCL0_DS4
#define VDC51SC0_SCL0_DS5 VDC51.SC0_SCL0_DS5
#define VDC51SC0_SCL0_DS6 VDC51.SC0_SCL0_DS6
#define VDC51SC0_SCL0_DS7 VDC51.SC0_SCL0_DS7
#define VDC51SC0_SCL0_US1 VDC51.SC0_SCL0_US1
#define VDC51SC0_SCL0_US2 VDC51.SC0_SCL0_US2
#define VDC51SC0_SCL0_US3 VDC51.SC0_SCL0_US3
#define VDC51SC0_SCL0_US4 VDC51.SC0_SCL0_US4
#define VDC51SC0_SCL0_US5 VDC51.SC0_SCL0_US5
#define VDC51SC0_SCL0_US6 VDC51.SC0_SCL0_US6
#define VDC51SC0_SCL0_US7 VDC51.SC0_SCL0_US7
#define VDC51SC0_SCL0_US8 VDC51.SC0_SCL0_US8
#define VDC51SC0_SCL0_OVR1 VDC51.SC0_SCL0_OVR1
#define VDC51SC0_SCL1_UPDATE VDC51.SC0_SCL1_UPDATE
#define VDC51SC0_SCL1_WR1 VDC51.SC0_SCL1_WR1
#define VDC51SC0_SCL1_WR2 VDC51.SC0_SCL1_WR2
#define VDC51SC0_SCL1_WR3 VDC51.SC0_SCL1_WR3
#define VDC51SC0_SCL1_WR4 VDC51.SC0_SCL1_WR4
#define VDC51SC0_SCL1_WR5 VDC51.SC0_SCL1_WR5
#define VDC51SC0_SCL1_WR6 VDC51.SC0_SCL1_WR6
#define VDC51SC0_SCL1_WR7 VDC51.SC0_SCL1_WR7
#define VDC51SC0_SCL1_WR8 VDC51.SC0_SCL1_WR8
#define VDC51SC0_SCL1_WR9 VDC51.SC0_SCL1_WR9
#define VDC51SC0_SCL1_WR10 VDC51.SC0_SCL1_WR10
#define VDC51SC0_SCL1_WR11 VDC51.SC0_SCL1_WR11
#define VDC51SC0_SCL1_MON1 VDC51.SC0_SCL1_MON1
#define VDC51SC0_SCL1_PBUF0 VDC51.SC0_SCL1_PBUF0
#define VDC51SC0_SCL1_PBUF1 VDC51.SC0_SCL1_PBUF1
#define VDC51SC0_SCL1_PBUF2 VDC51.SC0_SCL1_PBUF2
#define VDC51SC0_SCL1_PBUF3 VDC51.SC0_SCL1_PBUF3
#define VDC51SC0_SCL1_PBUF_FLD VDC51.SC0_SCL1_PBUF_FLD
#define VDC51SC0_SCL1_PBUF_CNT VDC51.SC0_SCL1_PBUF_CNT
#define VDC51GR0_UPDATE VDC51.GR0_UPDATE
#define VDC51GR0_FLM_RD VDC51.GR0_FLM_RD
#define VDC51GR0_FLM1 VDC51.GR0_FLM1
#define VDC51GR0_FLM2 VDC51.GR0_FLM2
#define VDC51GR0_FLM3 VDC51.GR0_FLM3
#define VDC51GR0_FLM4 VDC51.GR0_FLM4
#define VDC51GR0_FLM5 VDC51.GR0_FLM5
#define VDC51GR0_FLM6 VDC51.GR0_FLM6
#define VDC51GR0_AB1 VDC51.GR0_AB1
#define VDC51GR0_AB2 VDC51.GR0_AB2
#define VDC51GR0_AB3 VDC51.GR0_AB3
#define VDC51GR0_AB7 VDC51.GR0_AB7
#define VDC51GR0_AB8 VDC51.GR0_AB8
#define VDC51GR0_AB9 VDC51.GR0_AB9
#define VDC51GR0_AB10 VDC51.GR0_AB10
#define VDC51GR0_AB11 VDC51.GR0_AB11
#define VDC51GR0_BASE VDC51.GR0_BASE
#define VDC51GR0_CLUT VDC51.GR0_CLUT
#define VDC51ADJ0_UPDATE VDC51.ADJ0_UPDATE
#define VDC51ADJ0_BKSTR_SET VDC51.ADJ0_BKSTR_SET
#define VDC51ADJ0_ENH_TIM1 VDC51.ADJ0_ENH_TIM1
#define VDC51ADJ0_ENH_TIM2 VDC51.ADJ0_ENH_TIM2
#define VDC51ADJ0_ENH_TIM3 VDC51.ADJ0_ENH_TIM3
#define VDC51ADJ0_ENH_SHP1 VDC51.ADJ0_ENH_SHP1
#define VDC51ADJ0_ENH_SHP2 VDC51.ADJ0_ENH_SHP2
#define VDC51ADJ0_ENH_SHP3 VDC51.ADJ0_ENH_SHP3
#define VDC51ADJ0_ENH_SHP4 VDC51.ADJ0_ENH_SHP4
#define VDC51ADJ0_ENH_SHP5 VDC51.ADJ0_ENH_SHP5
#define VDC51ADJ0_ENH_SHP6 VDC51.ADJ0_ENH_SHP6
#define VDC51ADJ0_ENH_LTI1 VDC51.ADJ0_ENH_LTI1
#define VDC51ADJ0_ENH_LTI2 VDC51.ADJ0_ENH_LTI2
#define VDC51ADJ0_MTX_MODE VDC51.ADJ0_MTX_MODE
#define VDC51ADJ0_MTX_YG_ADJ0 VDC51.ADJ0_MTX_YG_ADJ0
#define VDC51ADJ0_MTX_YG_ADJ1 VDC51.ADJ0_MTX_YG_ADJ1
#define VDC51ADJ0_MTX_CBB_ADJ0 VDC51.ADJ0_MTX_CBB_ADJ0
#define VDC51ADJ0_MTX_CBB_ADJ1 VDC51.ADJ0_MTX_CBB_ADJ1
#define VDC51ADJ0_MTX_CRR_ADJ0 VDC51.ADJ0_MTX_CRR_ADJ0
#define VDC51ADJ0_MTX_CRR_ADJ1 VDC51.ADJ0_MTX_CRR_ADJ1
#define VDC51GR2_UPDATE VDC51.GR2_UPDATE
#define VDC51GR2_FLM_RD VDC51.GR2_FLM_RD
#define VDC51GR2_FLM1 VDC51.GR2_FLM1
#define VDC51GR2_FLM2 VDC51.GR2_FLM2
#define VDC51GR2_FLM3 VDC51.GR2_FLM3
#define VDC51GR2_FLM4 VDC51.GR2_FLM4
#define VDC51GR2_FLM5 VDC51.GR2_FLM5
#define VDC51GR2_FLM6 VDC51.GR2_FLM6
#define VDC51GR2_AB1 VDC51.GR2_AB1
#define VDC51GR2_AB2 VDC51.GR2_AB2
#define VDC51GR2_AB3 VDC51.GR2_AB3
#define VDC51GR2_AB4 VDC51.GR2_AB4
#define VDC51GR2_AB5 VDC51.GR2_AB5
#define VDC51GR2_AB6 VDC51.GR2_AB6
#define VDC51GR2_AB7 VDC51.GR2_AB7
#define VDC51GR2_AB8 VDC51.GR2_AB8
#define VDC51GR2_AB9 VDC51.GR2_AB9
#define VDC51GR2_AB10 VDC51.GR2_AB10
#define VDC51GR2_AB11 VDC51.GR2_AB11
#define VDC51GR2_BASE VDC51.GR2_BASE
#define VDC51GR2_CLUT VDC51.GR2_CLUT
#define VDC51GR2_MON VDC51.GR2_MON
#define VDC51GR3_UPDATE VDC51.GR3_UPDATE
#define VDC51GR3_FLM_RD VDC51.GR3_FLM_RD
#define VDC51GR3_FLM1 VDC51.GR3_FLM1
#define VDC51GR3_FLM2 VDC51.GR3_FLM2
#define VDC51GR3_FLM3 VDC51.GR3_FLM3
#define VDC51GR3_FLM4 VDC51.GR3_FLM4
#define VDC51GR3_FLM5 VDC51.GR3_FLM5
#define VDC51GR3_FLM6 VDC51.GR3_FLM6
#define VDC51GR3_AB1 VDC51.GR3_AB1
#define VDC51GR3_AB2 VDC51.GR3_AB2
#define VDC51GR3_AB3 VDC51.GR3_AB3
#define VDC51GR3_AB4 VDC51.GR3_AB4
#define VDC51GR3_AB5 VDC51.GR3_AB5
#define VDC51GR3_AB6 VDC51.GR3_AB6
#define VDC51GR3_AB7 VDC51.GR3_AB7
#define VDC51GR3_AB8 VDC51.GR3_AB8
#define VDC51GR3_AB9 VDC51.GR3_AB9
#define VDC51GR3_AB10 VDC51.GR3_AB10
#define VDC51GR3_AB11 VDC51.GR3_AB11
#define VDC51GR3_BASE VDC51.GR3_BASE
#define VDC51GR3_CLUT_INT VDC51.GR3_CLUT_INT
#define VDC51GR3_MON VDC51.GR3_MON
#define VDC51GAM_G_UPDATE VDC51.GAM_G_UPDATE
#define VDC51GAM_SW VDC51.GAM_SW
#define VDC51GAM_G_LUT1 VDC51.GAM_G_LUT1
#define VDC51GAM_G_LUT2 VDC51.GAM_G_LUT2
#define VDC51GAM_G_LUT3 VDC51.GAM_G_LUT3
#define VDC51GAM_G_LUT4 VDC51.GAM_G_LUT4
#define VDC51GAM_G_LUT5 VDC51.GAM_G_LUT5
#define VDC51GAM_G_LUT6 VDC51.GAM_G_LUT6
#define VDC51GAM_G_LUT7 VDC51.GAM_G_LUT7
#define VDC51GAM_G_LUT8 VDC51.GAM_G_LUT8
#define VDC51GAM_G_LUT9 VDC51.GAM_G_LUT9
#define VDC51GAM_G_LUT10 VDC51.GAM_G_LUT10
#define VDC51GAM_G_LUT11 VDC51.GAM_G_LUT11
#define VDC51GAM_G_LUT12 VDC51.GAM_G_LUT12
#define VDC51GAM_G_LUT13 VDC51.GAM_G_LUT13
#define VDC51GAM_G_LUT14 VDC51.GAM_G_LUT14
#define VDC51GAM_G_LUT15 VDC51.GAM_G_LUT15
#define VDC51GAM_G_LUT16 VDC51.GAM_G_LUT16
#define VDC51GAM_G_AREA1 VDC51.GAM_G_AREA1
#define VDC51GAM_G_AREA2 VDC51.GAM_G_AREA2
#define VDC51GAM_G_AREA3 VDC51.GAM_G_AREA3
#define VDC51GAM_G_AREA4 VDC51.GAM_G_AREA4
#define VDC51GAM_G_AREA5 VDC51.GAM_G_AREA5
#define VDC51GAM_G_AREA6 VDC51.GAM_G_AREA6
#define VDC51GAM_G_AREA7 VDC51.GAM_G_AREA7
#define VDC51GAM_G_AREA8 VDC51.GAM_G_AREA8
#define VDC51GAM_B_UPDATE VDC51.GAM_B_UPDATE
#define VDC51GAM_B_LUT1 VDC51.GAM_B_LUT1
#define VDC51GAM_B_LUT2 VDC51.GAM_B_LUT2
#define VDC51GAM_B_LUT3 VDC51.GAM_B_LUT3
#define VDC51GAM_B_LUT4 VDC51.GAM_B_LUT4
#define VDC51GAM_B_LUT5 VDC51.GAM_B_LUT5
#define VDC51GAM_B_LUT6 VDC51.GAM_B_LUT6
#define VDC51GAM_B_LUT7 VDC51.GAM_B_LUT7
#define VDC51GAM_B_LUT8 VDC51.GAM_B_LUT8
#define VDC51GAM_B_LUT9 VDC51.GAM_B_LUT9
#define VDC51GAM_B_LUT10 VDC51.GAM_B_LUT10
#define VDC51GAM_B_LUT11 VDC51.GAM_B_LUT11
#define VDC51GAM_B_LUT12 VDC51.GAM_B_LUT12
#define VDC51GAM_B_LUT13 VDC51.GAM_B_LUT13
#define VDC51GAM_B_LUT14 VDC51.GAM_B_LUT14
#define VDC51GAM_B_LUT15 VDC51.GAM_B_LUT15
#define VDC51GAM_B_LUT16 VDC51.GAM_B_LUT16
#define VDC51GAM_B_AREA1 VDC51.GAM_B_AREA1
#define VDC51GAM_B_AREA2 VDC51.GAM_B_AREA2
#define VDC51GAM_B_AREA3 VDC51.GAM_B_AREA3
#define VDC51GAM_B_AREA4 VDC51.GAM_B_AREA4
#define VDC51GAM_B_AREA5 VDC51.GAM_B_AREA5
#define VDC51GAM_B_AREA6 VDC51.GAM_B_AREA6
#define VDC51GAM_B_AREA7 VDC51.GAM_B_AREA7
#define VDC51GAM_B_AREA8 VDC51.GAM_B_AREA8
#define VDC51GAM_R_UPDATE VDC51.GAM_R_UPDATE
#define VDC51GAM_R_LUT1 VDC51.GAM_R_LUT1
#define VDC51GAM_R_LUT2 VDC51.GAM_R_LUT2
#define VDC51GAM_R_LUT3 VDC51.GAM_R_LUT3
#define VDC51GAM_R_LUT4 VDC51.GAM_R_LUT4
#define VDC51GAM_R_LUT5 VDC51.GAM_R_LUT5
#define VDC51GAM_R_LUT6 VDC51.GAM_R_LUT6
#define VDC51GAM_R_LUT7 VDC51.GAM_R_LUT7
#define VDC51GAM_R_LUT8 VDC51.GAM_R_LUT8
#define VDC51GAM_R_LUT9 VDC51.GAM_R_LUT9
#define VDC51GAM_R_LUT10 VDC51.GAM_R_LUT10
#define VDC51GAM_R_LUT11 VDC51.GAM_R_LUT11
#define VDC51GAM_R_LUT12 VDC51.GAM_R_LUT12
#define VDC51GAM_R_LUT13 VDC51.GAM_R_LUT13
#define VDC51GAM_R_LUT14 VDC51.GAM_R_LUT14
#define VDC51GAM_R_LUT15 VDC51.GAM_R_LUT15
#define VDC51GAM_R_LUT16 VDC51.GAM_R_LUT16
#define VDC51GAM_R_AREA1 VDC51.GAM_R_AREA1
#define VDC51GAM_R_AREA2 VDC51.GAM_R_AREA2
#define VDC51GAM_R_AREA3 VDC51.GAM_R_AREA3
#define VDC51GAM_R_AREA4 VDC51.GAM_R_AREA4
#define VDC51GAM_R_AREA5 VDC51.GAM_R_AREA5
#define VDC51GAM_R_AREA6 VDC51.GAM_R_AREA6
#define VDC51GAM_R_AREA7 VDC51.GAM_R_AREA7
#define VDC51GAM_R_AREA8 VDC51.GAM_R_AREA8
#define VDC51TCON_UPDATE VDC51.TCON_UPDATE
#define VDC51TCON_TIM VDC51.TCON_TIM
#define VDC51TCON_TIM_STVA1 VDC51.TCON_TIM_STVA1
#define VDC51TCON_TIM_STVA2 VDC51.TCON_TIM_STVA2
#define VDC51TCON_TIM_STVB1 VDC51.TCON_TIM_STVB1
#define VDC51TCON_TIM_STVB2 VDC51.TCON_TIM_STVB2
#define VDC51TCON_TIM_STH1 VDC51.TCON_TIM_STH1
#define VDC51TCON_TIM_STH2 VDC51.TCON_TIM_STH2
#define VDC51TCON_TIM_STB1 VDC51.TCON_TIM_STB1
#define VDC51TCON_TIM_STB2 VDC51.TCON_TIM_STB2
#define VDC51TCON_TIM_CPV1 VDC51.TCON_TIM_CPV1
#define VDC51TCON_TIM_CPV2 VDC51.TCON_TIM_CPV2
#define VDC51TCON_TIM_POLA1 VDC51.TCON_TIM_POLA1
#define VDC51TCON_TIM_POLA2 VDC51.TCON_TIM_POLA2
#define VDC51TCON_TIM_POLB1 VDC51.TCON_TIM_POLB1
#define VDC51TCON_TIM_POLB2 VDC51.TCON_TIM_POLB2
#define VDC51TCON_TIM_DE VDC51.TCON_TIM_DE
#define VDC51OUT_UPDATE VDC51.OUT_UPDATE
#define VDC51OUT_SET VDC51.OUT_SET
#define VDC51OUT_BRIGHT1 VDC51.OUT_BRIGHT1
#define VDC51OUT_BRIGHT2 VDC51.OUT_BRIGHT2
#define VDC51OUT_CONTRAST VDC51.OUT_CONTRAST
#define VDC51OUT_PDTHA VDC51.OUT_PDTHA
#define VDC51OUT_CLK_PHASE VDC51.OUT_CLK_PHASE
#define VDC51SYSCNT_INT1 VDC51.SYSCNT_INT1
#define VDC51SYSCNT_INT2 VDC51.SYSCNT_INT2
#define VDC51SYSCNT_INT3 VDC51.SYSCNT_INT3
#define VDC51SYSCNT_INT4 VDC51.SYSCNT_INT4
#define VDC51SYSCNT_INT5 VDC51.SYSCNT_INT5
#define VDC51SYSCNT_INT6 VDC51.SYSCNT_INT6
#define VDC51SYSCNT_PANEL_CLK VDC51.SYSCNT_PANEL_CLK
#define VDC51SYSCNT_CLUT VDC51.SYSCNT_CLUT
#define VDC51SC1_SCL0_UPDATE VDC51.SC1_SCL0_UPDATE
#define VDC51SC1_SCL0_FRC1 VDC51.SC1_SCL0_FRC1
#define VDC51SC1_SCL0_FRC2 VDC51.SC1_SCL0_FRC2
#define VDC51SC1_SCL0_FRC3 VDC51.SC1_SCL0_FRC3
#define VDC51SC1_SCL0_FRC4 VDC51.SC1_SCL0_FRC4
#define VDC51SC1_SCL0_FRC5 VDC51.SC1_SCL0_FRC5
#define VDC51SC1_SCL0_FRC6 VDC51.SC1_SCL0_FRC6
#define VDC51SC1_SCL0_FRC7 VDC51.SC1_SCL0_FRC7
#define VDC51SC1_SCL0_FRC9 VDC51.SC1_SCL0_FRC9
#define VDC51SC1_SCL0_MON0 VDC51.SC1_SCL0_MON0
#define VDC51SC1_SCL0_INT VDC51.SC1_SCL0_INT
#define VDC51SC1_SCL0_DS1 VDC51.SC1_SCL0_DS1
#define VDC51SC1_SCL0_DS2 VDC51.SC1_SCL0_DS2
#define VDC51SC1_SCL0_DS3 VDC51.SC1_SCL0_DS3
#define VDC51SC1_SCL0_DS4 VDC51.SC1_SCL0_DS4
#define VDC51SC1_SCL0_DS5 VDC51.SC1_SCL0_DS5
#define VDC51SC1_SCL0_DS6 VDC51.SC1_SCL0_DS6
#define VDC51SC1_SCL0_DS7 VDC51.SC1_SCL0_DS7
#define VDC51SC1_SCL0_US1 VDC51.SC1_SCL0_US1
#define VDC51SC1_SCL0_US2 VDC51.SC1_SCL0_US2
#define VDC51SC1_SCL0_US3 VDC51.SC1_SCL0_US3
#define VDC51SC1_SCL0_US4 VDC51.SC1_SCL0_US4
#define VDC51SC1_SCL0_US5 VDC51.SC1_SCL0_US5
#define VDC51SC1_SCL0_US6 VDC51.SC1_SCL0_US6
#define VDC51SC1_SCL0_US7 VDC51.SC1_SCL0_US7
#define VDC51SC1_SCL0_US8 VDC51.SC1_SCL0_US8
#define VDC51SC1_SCL0_OVR1 VDC51.SC1_SCL0_OVR1
#define VDC51SC1_SCL1_UPDATE VDC51.SC1_SCL1_UPDATE
#define VDC51SC1_SCL1_WR1 VDC51.SC1_SCL1_WR1
#define VDC51SC1_SCL1_WR2 VDC51.SC1_SCL1_WR2
#define VDC51SC1_SCL1_WR3 VDC51.SC1_SCL1_WR3
#define VDC51SC1_SCL1_WR4 VDC51.SC1_SCL1_WR4
#define VDC51SC1_SCL1_WR5 VDC51.SC1_SCL1_WR5
#define VDC51SC1_SCL1_WR6 VDC51.SC1_SCL1_WR6
#define VDC51SC1_SCL1_WR7 VDC51.SC1_SCL1_WR7
#define VDC51SC1_SCL1_WR8 VDC51.SC1_SCL1_WR8
#define VDC51SC1_SCL1_WR9 VDC51.SC1_SCL1_WR9
#define VDC51SC1_SCL1_WR10 VDC51.SC1_SCL1_WR10
#define VDC51SC1_SCL1_WR11 VDC51.SC1_SCL1_WR11
#define VDC51SC1_SCL1_MON1 VDC51.SC1_SCL1_MON1
#define VDC51SC1_SCL1_PBUF0 VDC51.SC1_SCL1_PBUF0
#define VDC51SC1_SCL1_PBUF1 VDC51.SC1_SCL1_PBUF1
#define VDC51SC1_SCL1_PBUF2 VDC51.SC1_SCL1_PBUF2
#define VDC51SC1_SCL1_PBUF3 VDC51.SC1_SCL1_PBUF3
#define VDC51SC1_SCL1_PBUF_FLD VDC51.SC1_SCL1_PBUF_FLD
#define VDC51SC1_SCL1_PBUF_CNT VDC51.SC1_SCL1_PBUF_CNT
#define VDC51GR1_UPDATE VDC51.GR1_UPDATE
#define VDC51GR1_FLM_RD VDC51.GR1_FLM_RD
#define VDC51GR1_FLM1 VDC51.GR1_FLM1
#define VDC51GR1_FLM2 VDC51.GR1_FLM2
#define VDC51GR1_FLM3 VDC51.GR1_FLM3
#define VDC51GR1_FLM4 VDC51.GR1_FLM4
#define VDC51GR1_FLM5 VDC51.GR1_FLM5
#define VDC51GR1_FLM6 VDC51.GR1_FLM6
#define VDC51GR1_AB1 VDC51.GR1_AB1
#define VDC51GR1_AB2 VDC51.GR1_AB2
#define VDC51GR1_AB3 VDC51.GR1_AB3
#define VDC51GR1_AB4 VDC51.GR1_AB4
#define VDC51GR1_AB5 VDC51.GR1_AB5
#define VDC51GR1_AB6 VDC51.GR1_AB6
#define VDC51GR1_AB7 VDC51.GR1_AB7
#define VDC51GR1_AB8 VDC51.GR1_AB8
#define VDC51GR1_AB9 VDC51.GR1_AB9
#define VDC51GR1_AB10 VDC51.GR1_AB10
#define VDC51GR1_AB11 VDC51.GR1_AB11
#define VDC51GR1_BASE VDC51.GR1_BASE
#define VDC51GR1_CLUT VDC51.GR1_CLUT
#define VDC51GR1_MON VDC51.GR1_MON
#define VDC51ADJ1_UPDATE VDC51.ADJ1_UPDATE
#define VDC51ADJ1_BKSTR_SET VDC51.ADJ1_BKSTR_SET
#define VDC51ADJ1_ENH_TIM1 VDC51.ADJ1_ENH_TIM1
#define VDC51ADJ1_ENH_TIM2 VDC51.ADJ1_ENH_TIM2
#define VDC51ADJ1_ENH_TIM3 VDC51.ADJ1_ENH_TIM3
#define VDC51ADJ1_ENH_SHP1 VDC51.ADJ1_ENH_SHP1
#define VDC51ADJ1_ENH_SHP2 VDC51.ADJ1_ENH_SHP2
#define VDC51ADJ1_ENH_SHP3 VDC51.ADJ1_ENH_SHP3
#define VDC51ADJ1_ENH_SHP4 VDC51.ADJ1_ENH_SHP4
#define VDC51ADJ1_ENH_SHP5 VDC51.ADJ1_ENH_SHP5
#define VDC51ADJ1_ENH_SHP6 VDC51.ADJ1_ENH_SHP6
#define VDC51ADJ1_ENH_LTI1 VDC51.ADJ1_ENH_LTI1
#define VDC51ADJ1_ENH_LTI2 VDC51.ADJ1_ENH_LTI2
#define VDC51ADJ1_MTX_MODE VDC51.ADJ1_MTX_MODE
#define VDC51ADJ1_MTX_YG_ADJ0 VDC51.ADJ1_MTX_YG_ADJ0
#define VDC51ADJ1_MTX_YG_ADJ1 VDC51.ADJ1_MTX_YG_ADJ1
#define VDC51ADJ1_MTX_CBB_ADJ0 VDC51.ADJ1_MTX_CBB_ADJ0
#define VDC51ADJ1_MTX_CBB_ADJ1 VDC51.ADJ1_MTX_CBB_ADJ1
#define VDC51ADJ1_MTX_CRR_ADJ0 VDC51.ADJ1_MTX_CRR_ADJ0
#define VDC51ADJ1_MTX_CRR_ADJ1 VDC51.ADJ1_MTX_CRR_ADJ1
#define VDC51GR_VIN_UPDATE VDC51.GR_VIN_UPDATE
#define VDC51GR_VIN_AB1 VDC51.GR_VIN_AB1
#define VDC51GR_VIN_AB2 VDC51.GR_VIN_AB2
#define VDC51GR_VIN_AB3 VDC51.GR_VIN_AB3
#define VDC51GR_VIN_AB4 VDC51.GR_VIN_AB4
#define VDC51GR_VIN_AB5 VDC51.GR_VIN_AB5
#define VDC51GR_VIN_AB6 VDC51.GR_VIN_AB6
#define VDC51GR_VIN_AB7 VDC51.GR_VIN_AB7
#define VDC51GR_VIN_BASE VDC51.GR_VIN_BASE
#define VDC51GR_VIN_MON VDC51.GR_VIN_MON
#define VDC51OIR_SCL0_UPDATE VDC51.OIR_SCL0_UPDATE
#define VDC51OIR_SCL0_FRC1 VDC51.OIR_SCL0_FRC1
#define VDC51OIR_SCL0_FRC2 VDC51.OIR_SCL0_FRC2
#define VDC51OIR_SCL0_FRC3 VDC51.OIR_SCL0_FRC3
#define VDC51OIR_SCL0_FRC4 VDC51.OIR_SCL0_FRC4
#define VDC51OIR_SCL0_FRC5 VDC51.OIR_SCL0_FRC5
#define VDC51OIR_SCL0_FRC6 VDC51.OIR_SCL0_FRC6
#define VDC51OIR_SCL0_FRC7 VDC51.OIR_SCL0_FRC7
#define VDC51OIR_SCL0_DS1 VDC51.OIR_SCL0_DS1
#define VDC51OIR_SCL0_DS2 VDC51.OIR_SCL0_DS2
#define VDC51OIR_SCL0_DS3 VDC51.OIR_SCL0_DS3
#define VDC51OIR_SCL0_DS7 VDC51.OIR_SCL0_DS7
#define VDC51OIR_SCL0_US1 VDC51.OIR_SCL0_US1
#define VDC51OIR_SCL0_US2 VDC51.OIR_SCL0_US2
#define VDC51OIR_SCL0_US3 VDC51.OIR_SCL0_US3
#define VDC51OIR_SCL0_US8 VDC51.OIR_SCL0_US8
#define VDC51OIR_SCL0_OVR1 VDC51.OIR_SCL0_OVR1
#define VDC51OIR_SCL1_UPDATE VDC51.OIR_SCL1_UPDATE
#define VDC51OIR_SCL1_WR1 VDC51.OIR_SCL1_WR1
#define VDC51OIR_SCL1_WR2 VDC51.OIR_SCL1_WR2
#define VDC51OIR_SCL1_WR3 VDC51.OIR_SCL1_WR3
#define VDC51OIR_SCL1_WR4 VDC51.OIR_SCL1_WR4
#define VDC51OIR_SCL1_WR5 VDC51.OIR_SCL1_WR5
#define VDC51OIR_SCL1_WR6 VDC51.OIR_SCL1_WR6
#define VDC51OIR_SCL1_WR7 VDC51.OIR_SCL1_WR7
#define VDC51GR_OIR_UPDATE VDC51.GR_OIR_UPDATE
#define VDC51GR_OIR_FLM_RD VDC51.GR_OIR_FLM_RD
#define VDC51GR_OIR_FLM1 VDC51.GR_OIR_FLM1
#define VDC51GR_OIR_FLM2 VDC51.GR_OIR_FLM2
#define VDC51GR_OIR_FLM3 VDC51.GR_OIR_FLM3
#define VDC51GR_OIR_FLM4 VDC51.GR_OIR_FLM4
#define VDC51GR_OIR_FLM5 VDC51.GR_OIR_FLM5
#define VDC51GR_OIR_FLM6 VDC51.GR_OIR_FLM6
#define VDC51GR_OIR_AB1 VDC51.GR_OIR_AB1
#define VDC51GR_OIR_AB2 VDC51.GR_OIR_AB2
#define VDC51GR_OIR_AB3 VDC51.GR_OIR_AB3
#define VDC51GR_OIR_AB7 VDC51.GR_OIR_AB7
#define VDC51GR_OIR_AB8 VDC51.GR_OIR_AB8
#define VDC51GR_OIR_AB9 VDC51.GR_OIR_AB9
#define VDC51GR_OIR_AB10 VDC51.GR_OIR_AB10
#define VDC51GR_OIR_AB11 VDC51.GR_OIR_AB11
#define VDC51GR_OIR_BASE VDC51.GR_OIR_BASE
#define VDC51GR_OIR_CLUT VDC51.GR_OIR_CLUT
#define VDC51GR_OIR_MON VDC51.GR_OIR_MON
/* <-SEC M1.10.1 */
/* <-QAC 0639 */
#endif
