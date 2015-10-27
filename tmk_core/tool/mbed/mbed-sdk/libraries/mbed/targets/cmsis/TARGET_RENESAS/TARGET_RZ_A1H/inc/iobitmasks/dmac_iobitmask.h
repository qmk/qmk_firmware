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
* http://www.renesas.com/disclaimer
* Copyright (C) 2012 - 2014 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name   : dmac_iobitmask.h
* $Rev: 1114 $
* $Date:: 2014-07-09 14:56:39 +0900#$
* Description : DMAC register define header
*******************************************************************************/
#ifndef DMAC_IOBITMASK_H
#define DMAC_IOBITMASK_H


/* ==== Mask values for IO registers ==== */
/* ---- DMAC0 ---- */
#define DMAC0_N0SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC0_N0DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC0_N0TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC0_N1SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC0_N1DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC0_N1TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC0_CRSA_n_CRSA                   (0xFFFFFFFFuL)

#define DMAC0_CRDA_n_CRDA                   (0xFFFFFFFFuL)

#define DMAC0_CRTB_n_CRTB                   (0xFFFFFFFFuL)

#define DMAC0_CHSTAT_n_EN                   (0x00000001uL)
#define DMAC0_CHSTAT_n_RQST                 (0x00000002uL)
#define DMAC0_CHSTAT_n_TACT                 (0x00000004uL)
#define DMAC0_CHSTAT_n_SUS                  (0x00000008uL)
#define DMAC0_CHSTAT_n_ER                   (0x00000010uL)
#define DMAC0_CHSTAT_n_END                  (0x00000020uL)
#define DMAC0_CHSTAT_n_TC                   (0x00000040uL)
#define DMAC0_CHSTAT_n_SR                   (0x00000080uL)
#define DMAC0_CHSTAT_n_DL                   (0x00000100uL)
#define DMAC0_CHSTAT_n_DW                   (0x00000200uL)
#define DMAC0_CHSTAT_n_DER                  (0x00000400uL)
#define DMAC0_CHSTAT_n_MODE                 (0x00000800uL)
#define DMAC0_CHSTAT_n_INTMSK               (0x00010000uL)

#define DMAC0_CHCTRL_n_SETEN                (0x00000001uL)
#define DMAC0_CHCTRL_n_CLREN                (0x00000002uL)
#define DMAC0_CHCTRL_n_STG                  (0x00000004uL)
#define DMAC0_CHCTRL_n_SWRST                (0x00000008uL)
#define DMAC0_CHCTRL_n_CLRRQ                (0x00000010uL)
#define DMAC0_CHCTRL_n_CLREND               (0x00000020uL)
#define DMAC0_CHCTRL_n_CLRTC                (0x00000040uL)
#define DMAC0_CHCTRL_n_SETSUS               (0x00000100uL)
#define DMAC0_CHCTRL_n_CLRSUS               (0x00000200uL)
#define DMAC0_CHCTRL_n_SETINTMSK            (0x00010000uL)
#define DMAC0_CHCTRL_n_CLRINTMSK            (0x00020000uL)

#define DMAC0_CHCFG_n_SEL                   (0x00000007uL)
#define DMAC0_CHCFG_n_REQD                  (0x00000008uL)
#define DMAC0_CHCFG_n_LOEN                  (0x00000010uL)
#define DMAC0_CHCFG_n_HIEN                  (0x00000020uL)
#define DMAC0_CHCFG_n_LVL                   (0x00000040uL)
#define DMAC0_CHCFG_n_AM                    (0x00000700uL)
#define DMAC0_CHCFG_n_SDS                   (0x0000F000uL)
#define DMAC0_CHCFG_n_DDS                   (0x000F0000uL)
#define DMAC0_CHCFG_n_SAD                   (0x00100000uL)
#define DMAC0_CHCFG_n_DAD                   (0x00200000uL)
#define DMAC0_CHCFG_n_TM                    (0x00400000uL)
#define DMAC0_CHCFG_n_DEM                   (0x01000000uL)
#define DMAC0_CHCFG_n_TCM                   (0x02000000uL)
#define DMAC0_CHCFG_n_SBE                   (0x08000000uL)
#define DMAC0_CHCFG_n_RSEL                  (0x10000000uL)
#define DMAC0_CHCFG_n_RSW                   (0x20000000uL)
#define DMAC0_CHCFG_n_REN                   (0x40000000uL)
#define DMAC0_CHCFG_n_DMS                   (0x80000000uL)

#define DMAC0_CHITVL_n_ITVL                 (0x0000FFFFuL)

#define DMAC0_CHEXT_n_SCA                   (0x000000F0uL)
#define DMAC0_CHEXT_n_DCA                   (0x0000F000uL)

#define DMAC0_NXLA_n_NXLA                   (0xFFFFFFFFuL)

#define DMAC0_CRLA_n_CRLA                   (0xFFFFFFFFuL)

/* ---- DMAC1 ---- */
#define DMAC1_N0SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC1_N0DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC1_N0TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC1_N1SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC1_N1DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC1_N1TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC1_CRSA_n_CRSA                   (0xFFFFFFFFuL)

#define DMAC1_CRDA_n_CRDA                   (0xFFFFFFFFuL)

#define DMAC1_CRTB_n_CRTB                   (0xFFFFFFFFuL)

#define DMAC1_CHSTAT_n_EN                   (0x00000001uL)
#define DMAC1_CHSTAT_n_RQST                 (0x00000002uL)
#define DMAC1_CHSTAT_n_TACT                 (0x00000004uL)
#define DMAC1_CHSTAT_n_SUS                  (0x00000008uL)
#define DMAC1_CHSTAT_n_ER                   (0x00000010uL)
#define DMAC1_CHSTAT_n_END                  (0x00000020uL)
#define DMAC1_CHSTAT_n_TC                   (0x00000040uL)
#define DMAC1_CHSTAT_n_SR                   (0x00000080uL)
#define DMAC1_CHSTAT_n_DL                   (0x00000100uL)
#define DMAC1_CHSTAT_n_DW                   (0x00000200uL)
#define DMAC1_CHSTAT_n_DER                  (0x00000400uL)
#define DMAC1_CHSTAT_n_MODE                 (0x00000800uL)
#define DMAC1_CHSTAT_n_INTMSK               (0x00010000uL)

#define DMAC1_CHCTRL_n_SETEN                (0x00000001uL)
#define DMAC1_CHCTRL_n_CLREN                (0x00000002uL)
#define DMAC1_CHCTRL_n_STG                  (0x00000004uL)
#define DMAC1_CHCTRL_n_SWRST                (0x00000008uL)
#define DMAC1_CHCTRL_n_CLRRQ                (0x00000010uL)
#define DMAC1_CHCTRL_n_CLREND               (0x00000020uL)
#define DMAC1_CHCTRL_n_CLRTC                (0x00000040uL)
#define DMAC1_CHCTRL_n_SETSUS               (0x00000100uL)
#define DMAC1_CHCTRL_n_CLRSUS               (0x00000200uL)
#define DMAC1_CHCTRL_n_SETINTMSK            (0x00010000uL)
#define DMAC1_CHCTRL_n_CLRINTMSK            (0x00020000uL)

#define DMAC1_CHCFG_n_SEL                   (0x00000007uL)
#define DMAC1_CHCFG_n_REQD                  (0x00000008uL)
#define DMAC1_CHCFG_n_LOEN                  (0x00000010uL)
#define DMAC1_CHCFG_n_HIEN                  (0x00000020uL)
#define DMAC1_CHCFG_n_LVL                   (0x00000040uL)
#define DMAC1_CHCFG_n_AM                    (0x00000700uL)
#define DMAC1_CHCFG_n_SDS                   (0x0000F000uL)
#define DMAC1_CHCFG_n_DDS                   (0x000F0000uL)
#define DMAC1_CHCFG_n_SAD                   (0x00100000uL)
#define DMAC1_CHCFG_n_DAD                   (0x00200000uL)
#define DMAC1_CHCFG_n_TM                    (0x00400000uL)
#define DMAC1_CHCFG_n_DEM                   (0x01000000uL)
#define DMAC1_CHCFG_n_TCM                   (0x02000000uL)
#define DMAC1_CHCFG_n_SBE                   (0x08000000uL)
#define DMAC1_CHCFG_n_RSEL                  (0x10000000uL)
#define DMAC1_CHCFG_n_RSW                   (0x20000000uL)
#define DMAC1_CHCFG_n_REN                   (0x40000000uL)
#define DMAC1_CHCFG_n_DMS                   (0x80000000uL)

#define DMAC1_CHITVL_n_ITVL                 (0x0000FFFFuL)

#define DMAC1_CHEXT_n_SCA                   (0x000000F0uL)
#define DMAC1_CHEXT_n_DCA                   (0x0000F000uL)

#define DMAC1_NXLA_n_NXLA                   (0xFFFFFFFFuL)

#define DMAC1_CRLA_n_CRLA                   (0xFFFFFFFFuL)

/* ---- DMAC2 ---- */
#define DMAC2_N0SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC2_N0DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC2_N0TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC2_N1SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC2_N1DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC2_N1TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC2_CRSA_n_CRSA                   (0xFFFFFFFFuL)

#define DMAC2_CRDA_n_CRDA                   (0xFFFFFFFFuL)

#define DMAC2_CRTB_n_CRTB                   (0xFFFFFFFFuL)

#define DMAC2_CHSTAT_n_EN                   (0x00000001uL)
#define DMAC2_CHSTAT_n_RQST                 (0x00000002uL)
#define DMAC2_CHSTAT_n_TACT                 (0x00000004uL)
#define DMAC2_CHSTAT_n_SUS                  (0x00000008uL)
#define DMAC2_CHSTAT_n_ER                   (0x00000010uL)
#define DMAC2_CHSTAT_n_END                  (0x00000020uL)
#define DMAC2_CHSTAT_n_TC                   (0x00000040uL)
#define DMAC2_CHSTAT_n_SR                   (0x00000080uL)
#define DMAC2_CHSTAT_n_DL                   (0x00000100uL)
#define DMAC2_CHSTAT_n_DW                   (0x00000200uL)
#define DMAC2_CHSTAT_n_DER                  (0x00000400uL)
#define DMAC2_CHSTAT_n_MODE                 (0x00000800uL)
#define DMAC2_CHSTAT_n_INTMSK               (0x00010000uL)

#define DMAC2_CHCTRL_n_SETEN                (0x00000001uL)
#define DMAC2_CHCTRL_n_CLREN                (0x00000002uL)
#define DMAC2_CHCTRL_n_STG                  (0x00000004uL)
#define DMAC2_CHCTRL_n_SWRST                (0x00000008uL)
#define DMAC2_CHCTRL_n_CLRRQ                (0x00000010uL)
#define DMAC2_CHCTRL_n_CLREND               (0x00000020uL)
#define DMAC2_CHCTRL_n_CLRTC                (0x00000040uL)
#define DMAC2_CHCTRL_n_SETSUS               (0x00000100uL)
#define DMAC2_CHCTRL_n_CLRSUS               (0x00000200uL)
#define DMAC2_CHCTRL_n_SETINTMSK            (0x00010000uL)
#define DMAC2_CHCTRL_n_CLRINTMSK            (0x00020000uL)

#define DMAC2_CHCFG_n_SEL                   (0x00000007uL)
#define DMAC2_CHCFG_n_REQD                  (0x00000008uL)
#define DMAC2_CHCFG_n_LOEN                  (0x00000010uL)
#define DMAC2_CHCFG_n_HIEN                  (0x00000020uL)
#define DMAC2_CHCFG_n_LVL                   (0x00000040uL)
#define DMAC2_CHCFG_n_AM                    (0x00000700uL)
#define DMAC2_CHCFG_n_SDS                   (0x0000F000uL)
#define DMAC2_CHCFG_n_DDS                   (0x000F0000uL)
#define DMAC2_CHCFG_n_SAD                   (0x00100000uL)
#define DMAC2_CHCFG_n_DAD                   (0x00200000uL)
#define DMAC2_CHCFG_n_TM                    (0x00400000uL)
#define DMAC2_CHCFG_n_DEM                   (0x01000000uL)
#define DMAC2_CHCFG_n_TCM                   (0x02000000uL)
#define DMAC2_CHCFG_n_SBE                   (0x08000000uL)
#define DMAC2_CHCFG_n_RSEL                  (0x10000000uL)
#define DMAC2_CHCFG_n_RSW                   (0x20000000uL)
#define DMAC2_CHCFG_n_REN                   (0x40000000uL)
#define DMAC2_CHCFG_n_DMS                   (0x80000000uL)

#define DMAC2_CHITVL_n_ITVL                 (0x0000FFFFuL)

#define DMAC2_CHEXT_n_SCA                   (0x000000F0uL)
#define DMAC2_CHEXT_n_DCA                   (0x0000F000uL)

#define DMAC2_NXLA_n_NXLA                   (0xFFFFFFFFuL)

#define DMAC2_CRLA_n_CRLA                   (0xFFFFFFFFuL)

/* ---- DMAC3 ---- */
#define DMAC3_N0SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC3_N0DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC3_N0TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC3_N1SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC3_N1DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC3_N1TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC3_CRSA_n_CRSA                   (0xFFFFFFFFuL)

#define DMAC3_CRDA_n_CRDA                   (0xFFFFFFFFuL)

#define DMAC3_CRTB_n_CRTB                   (0xFFFFFFFFuL)

#define DMAC3_CHSTAT_n_EN                   (0x00000001uL)
#define DMAC3_CHSTAT_n_RQST                 (0x00000002uL)
#define DMAC3_CHSTAT_n_TACT                 (0x00000004uL)
#define DMAC3_CHSTAT_n_SUS                  (0x00000008uL)
#define DMAC3_CHSTAT_n_ER                   (0x00000010uL)
#define DMAC3_CHSTAT_n_END                  (0x00000020uL)
#define DMAC3_CHSTAT_n_TC                   (0x00000040uL)
#define DMAC3_CHSTAT_n_SR                   (0x00000080uL)
#define DMAC3_CHSTAT_n_DL                   (0x00000100uL)
#define DMAC3_CHSTAT_n_DW                   (0x00000200uL)
#define DMAC3_CHSTAT_n_DER                  (0x00000400uL)
#define DMAC3_CHSTAT_n_MODE                 (0x00000800uL)
#define DMAC3_CHSTAT_n_INTMSK               (0x00010000uL)

#define DMAC3_CHCTRL_n_SETEN                (0x00000001uL)
#define DMAC3_CHCTRL_n_CLREN                (0x00000002uL)
#define DMAC3_CHCTRL_n_STG                  (0x00000004uL)
#define DMAC3_CHCTRL_n_SWRST                (0x00000008uL)
#define DMAC3_CHCTRL_n_CLRRQ                (0x00000010uL)
#define DMAC3_CHCTRL_n_CLREND               (0x00000020uL)
#define DMAC3_CHCTRL_n_CLRTC                (0x00000040uL)
#define DMAC3_CHCTRL_n_SETSUS               (0x00000100uL)
#define DMAC3_CHCTRL_n_CLRSUS               (0x00000200uL)
#define DMAC3_CHCTRL_n_SETINTMSK            (0x00010000uL)
#define DMAC3_CHCTRL_n_CLRINTMSK            (0x00020000uL)

#define DMAC3_CHCFG_n_SEL                   (0x00000007uL)
#define DMAC3_CHCFG_n_REQD                  (0x00000008uL)
#define DMAC3_CHCFG_n_LOEN                  (0x00000010uL)
#define DMAC3_CHCFG_n_HIEN                  (0x00000020uL)
#define DMAC3_CHCFG_n_LVL                   (0x00000040uL)
#define DMAC3_CHCFG_n_AM                    (0x00000700uL)
#define DMAC3_CHCFG_n_SDS                   (0x0000F000uL)
#define DMAC3_CHCFG_n_DDS                   (0x000F0000uL)
#define DMAC3_CHCFG_n_SAD                   (0x00100000uL)
#define DMAC3_CHCFG_n_DAD                   (0x00200000uL)
#define DMAC3_CHCFG_n_TM                    (0x00400000uL)
#define DMAC3_CHCFG_n_DEM                   (0x01000000uL)
#define DMAC3_CHCFG_n_TCM                   (0x02000000uL)
#define DMAC3_CHCFG_n_SBE                   (0x08000000uL)
#define DMAC3_CHCFG_n_RSEL                  (0x10000000uL)
#define DMAC3_CHCFG_n_RSW                   (0x20000000uL)
#define DMAC3_CHCFG_n_REN                   (0x40000000uL)
#define DMAC3_CHCFG_n_DMS                   (0x80000000uL)

#define DMAC3_CHITVL_n_ITVL                 (0x0000FFFFuL)

#define DMAC3_CHEXT_n_SCA                   (0x000000F0uL)
#define DMAC3_CHEXT_n_DCA                   (0x0000F000uL)

#define DMAC3_NXLA_n_NXLA                   (0xFFFFFFFFuL)

#define DMAC3_CRLA_n_CRLA                   (0xFFFFFFFFuL)

/* ---- DMAC4 ---- */
#define DMAC4_N0SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC4_N0DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC4_N0TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC4_N1SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC4_N1DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC4_N1TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC4_CRSA_n_CRSA                   (0xFFFFFFFFuL)

#define DMAC4_CRDA_n_CRDA                   (0xFFFFFFFFuL)

#define DMAC4_CRTB_n_CRTB                   (0xFFFFFFFFuL)

#define DMAC4_CHSTAT_n_EN                   (0x00000001uL)
#define DMAC4_CHSTAT_n_RQST                 (0x00000002uL)
#define DMAC4_CHSTAT_n_TACT                 (0x00000004uL)
#define DMAC4_CHSTAT_n_SUS                  (0x00000008uL)
#define DMAC4_CHSTAT_n_ER                   (0x00000010uL)
#define DMAC4_CHSTAT_n_END                  (0x00000020uL)
#define DMAC4_CHSTAT_n_TC                   (0x00000040uL)
#define DMAC4_CHSTAT_n_SR                   (0x00000080uL)
#define DMAC4_CHSTAT_n_DL                   (0x00000100uL)
#define DMAC4_CHSTAT_n_DW                   (0x00000200uL)
#define DMAC4_CHSTAT_n_DER                  (0x00000400uL)
#define DMAC4_CHSTAT_n_MODE                 (0x00000800uL)
#define DMAC4_CHSTAT_n_INTMSK               (0x00010000uL)

#define DMAC4_CHCTRL_n_SETEN                (0x00000001uL)
#define DMAC4_CHCTRL_n_CLREN                (0x00000002uL)
#define DMAC4_CHCTRL_n_STG                  (0x00000004uL)
#define DMAC4_CHCTRL_n_SWRST                (0x00000008uL)
#define DMAC4_CHCTRL_n_CLRRQ                (0x00000010uL)
#define DMAC4_CHCTRL_n_CLREND               (0x00000020uL)
#define DMAC4_CHCTRL_n_CLRTC                (0x00000040uL)
#define DMAC4_CHCTRL_n_SETSUS               (0x00000100uL)
#define DMAC4_CHCTRL_n_CLRSUS               (0x00000200uL)
#define DMAC4_CHCTRL_n_SETINTMSK            (0x00010000uL)
#define DMAC4_CHCTRL_n_CLRINTMSK            (0x00020000uL)

#define DMAC4_CHCFG_n_SEL                   (0x00000007uL)
#define DMAC4_CHCFG_n_REQD                  (0x00000008uL)
#define DMAC4_CHCFG_n_LOEN                  (0x00000010uL)
#define DMAC4_CHCFG_n_HIEN                  (0x00000020uL)
#define DMAC4_CHCFG_n_LVL                   (0x00000040uL)
#define DMAC4_CHCFG_n_AM                    (0x00000700uL)
#define DMAC4_CHCFG_n_SDS                   (0x0000F000uL)
#define DMAC4_CHCFG_n_DDS                   (0x000F0000uL)
#define DMAC4_CHCFG_n_SAD                   (0x00100000uL)
#define DMAC4_CHCFG_n_DAD                   (0x00200000uL)
#define DMAC4_CHCFG_n_TM                    (0x00400000uL)
#define DMAC4_CHCFG_n_DEM                   (0x01000000uL)
#define DMAC4_CHCFG_n_TCM                   (0x02000000uL)
#define DMAC4_CHCFG_n_SBE                   (0x08000000uL)
#define DMAC4_CHCFG_n_RSEL                  (0x10000000uL)
#define DMAC4_CHCFG_n_RSW                   (0x20000000uL)
#define DMAC4_CHCFG_n_REN                   (0x40000000uL)
#define DMAC4_CHCFG_n_DMS                   (0x80000000uL)

#define DMAC4_CHITVL_n_ITVL                 (0x0000FFFFuL)

#define DMAC4_CHEXT_n_SCA                   (0x000000F0uL)
#define DMAC4_CHEXT_n_DCA                   (0x0000F000uL)

#define DMAC4_NXLA_n_NXLA                   (0xFFFFFFFFuL)

#define DMAC4_CRLA_n_CRLA                   (0xFFFFFFFFuL)

/* ---- DMAC5 ---- */
#define DMAC5_N0SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC5_N0DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC5_N0TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC5_N1SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC5_N1DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC5_N1TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC5_CRSA_n_CRSA                   (0xFFFFFFFFuL)

#define DMAC5_CRDA_n_CRDA                   (0xFFFFFFFFuL)

#define DMAC5_CRTB_n_CRTB                   (0xFFFFFFFFuL)

#define DMAC5_CHSTAT_n_EN                   (0x00000001uL)
#define DMAC5_CHSTAT_n_RQST                 (0x00000002uL)
#define DMAC5_CHSTAT_n_TACT                 (0x00000004uL)
#define DMAC5_CHSTAT_n_SUS                  (0x00000008uL)
#define DMAC5_CHSTAT_n_ER                   (0x00000010uL)
#define DMAC5_CHSTAT_n_END                  (0x00000020uL)
#define DMAC5_CHSTAT_n_TC                   (0x00000040uL)
#define DMAC5_CHSTAT_n_SR                   (0x00000080uL)
#define DMAC5_CHSTAT_n_DL                   (0x00000100uL)
#define DMAC5_CHSTAT_n_DW                   (0x00000200uL)
#define DMAC5_CHSTAT_n_DER                  (0x00000400uL)
#define DMAC5_CHSTAT_n_MODE                 (0x00000800uL)
#define DMAC5_CHSTAT_n_INTMSK               (0x00010000uL)

#define DMAC5_CHCTRL_n_SETEN                (0x00000001uL)
#define DMAC5_CHCTRL_n_CLREN                (0x00000002uL)
#define DMAC5_CHCTRL_n_STG                  (0x00000004uL)
#define DMAC5_CHCTRL_n_SWRST                (0x00000008uL)
#define DMAC5_CHCTRL_n_CLRRQ                (0x00000010uL)
#define DMAC5_CHCTRL_n_CLREND               (0x00000020uL)
#define DMAC5_CHCTRL_n_CLRTC                (0x00000040uL)
#define DMAC5_CHCTRL_n_SETSUS               (0x00000100uL)
#define DMAC5_CHCTRL_n_CLRSUS               (0x00000200uL)
#define DMAC5_CHCTRL_n_SETINTMSK            (0x00010000uL)
#define DMAC5_CHCTRL_n_CLRINTMSK            (0x00020000uL)

#define DMAC5_CHCFG_n_SEL                   (0x00000007uL)
#define DMAC5_CHCFG_n_REQD                  (0x00000008uL)
#define DMAC5_CHCFG_n_LOEN                  (0x00000010uL)
#define DMAC5_CHCFG_n_HIEN                  (0x00000020uL)
#define DMAC5_CHCFG_n_LVL                   (0x00000040uL)
#define DMAC5_CHCFG_n_AM                    (0x00000700uL)
#define DMAC5_CHCFG_n_SDS                   (0x0000F000uL)
#define DMAC5_CHCFG_n_DDS                   (0x000F0000uL)
#define DMAC5_CHCFG_n_SAD                   (0x00100000uL)
#define DMAC5_CHCFG_n_DAD                   (0x00200000uL)
#define DMAC5_CHCFG_n_TM                    (0x00400000uL)
#define DMAC5_CHCFG_n_DEM                   (0x01000000uL)
#define DMAC5_CHCFG_n_TCM                   (0x02000000uL)
#define DMAC5_CHCFG_n_SBE                   (0x08000000uL)
#define DMAC5_CHCFG_n_RSEL                  (0x10000000uL)
#define DMAC5_CHCFG_n_RSW                   (0x20000000uL)
#define DMAC5_CHCFG_n_REN                   (0x40000000uL)
#define DMAC5_CHCFG_n_DMS                   (0x80000000uL)

#define DMAC5_CHITVL_n_ITVL                 (0x0000FFFFuL)

#define DMAC5_CHEXT_n_SCA                   (0x000000F0uL)
#define DMAC5_CHEXT_n_DCA                   (0x0000F000uL)

#define DMAC5_NXLA_n_NXLA                   (0xFFFFFFFFuL)

#define DMAC5_CRLA_n_CRLA                   (0xFFFFFFFFuL)

/* ---- DMAC6 ---- */
#define DMAC6_N0SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC6_N0DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC6_N0TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC6_N1SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC6_N1DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC6_N1TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC6_CRSA_n_CRSA                   (0xFFFFFFFFuL)

#define DMAC6_CRDA_n_CRDA                   (0xFFFFFFFFuL)

#define DMAC6_CRTB_n_CRTB                   (0xFFFFFFFFuL)

#define DMAC6_CHSTAT_n_EN                   (0x00000001uL)
#define DMAC6_CHSTAT_n_RQST                 (0x00000002uL)
#define DMAC6_CHSTAT_n_TACT                 (0x00000004uL)
#define DMAC6_CHSTAT_n_SUS                  (0x00000008uL)
#define DMAC6_CHSTAT_n_ER                   (0x00000010uL)
#define DMAC6_CHSTAT_n_END                  (0x00000020uL)
#define DMAC6_CHSTAT_n_TC                   (0x00000040uL)
#define DMAC6_CHSTAT_n_SR                   (0x00000080uL)
#define DMAC6_CHSTAT_n_DL                   (0x00000100uL)
#define DMAC6_CHSTAT_n_DW                   (0x00000200uL)
#define DMAC6_CHSTAT_n_DER                  (0x00000400uL)
#define DMAC6_CHSTAT_n_MODE                 (0x00000800uL)
#define DMAC6_CHSTAT_n_INTMSK               (0x00010000uL)

#define DMAC6_CHCTRL_n_SETEN                (0x00000001uL)
#define DMAC6_CHCTRL_n_CLREN                (0x00000002uL)
#define DMAC6_CHCTRL_n_STG                  (0x00000004uL)
#define DMAC6_CHCTRL_n_SWRST                (0x00000008uL)
#define DMAC6_CHCTRL_n_CLRRQ                (0x00000010uL)
#define DMAC6_CHCTRL_n_CLREND               (0x00000020uL)
#define DMAC6_CHCTRL_n_CLRTC                (0x00000040uL)
#define DMAC6_CHCTRL_n_SETSUS               (0x00000100uL)
#define DMAC6_CHCTRL_n_CLRSUS               (0x00000200uL)
#define DMAC6_CHCTRL_n_SETINTMSK            (0x00010000uL)
#define DMAC6_CHCTRL_n_CLRINTMSK            (0x00020000uL)

#define DMAC6_CHCFG_n_SEL                   (0x00000007uL)
#define DMAC6_CHCFG_n_REQD                  (0x00000008uL)
#define DMAC6_CHCFG_n_LOEN                  (0x00000010uL)
#define DMAC6_CHCFG_n_HIEN                  (0x00000020uL)
#define DMAC6_CHCFG_n_LVL                   (0x00000040uL)
#define DMAC6_CHCFG_n_AM                    (0x00000700uL)
#define DMAC6_CHCFG_n_SDS                   (0x0000F000uL)
#define DMAC6_CHCFG_n_DDS                   (0x000F0000uL)
#define DMAC6_CHCFG_n_SAD                   (0x00100000uL)
#define DMAC6_CHCFG_n_DAD                   (0x00200000uL)
#define DMAC6_CHCFG_n_TM                    (0x00400000uL)
#define DMAC6_CHCFG_n_DEM                   (0x01000000uL)
#define DMAC6_CHCFG_n_TCM                   (0x02000000uL)
#define DMAC6_CHCFG_n_SBE                   (0x08000000uL)
#define DMAC6_CHCFG_n_RSEL                  (0x10000000uL)
#define DMAC6_CHCFG_n_RSW                   (0x20000000uL)
#define DMAC6_CHCFG_n_REN                   (0x40000000uL)
#define DMAC6_CHCFG_n_DMS                   (0x80000000uL)

#define DMAC6_CHITVL_n_ITVL                 (0x0000FFFFuL)

#define DMAC6_CHEXT_n_SCA                   (0x000000F0uL)
#define DMAC6_CHEXT_n_DCA                   (0x0000F000uL)

#define DMAC6_NXLA_n_NXLA                   (0xFFFFFFFFuL)

#define DMAC6_CRLA_n_CRLA                   (0xFFFFFFFFuL)

/* ---- DMAC7 ---- */
#define DMAC7_N0SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC7_N0DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC7_N0TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC7_N1SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC7_N1DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC7_N1TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC7_CRSA_n_CRSA                   (0xFFFFFFFFuL)

#define DMAC7_CRDA_n_CRDA                   (0xFFFFFFFFuL)

#define DMAC7_CRTB_n_CRTB                   (0xFFFFFFFFuL)

#define DMAC7_CHSTAT_n_EN                   (0x00000001uL)
#define DMAC7_CHSTAT_n_RQST                 (0x00000002uL)
#define DMAC7_CHSTAT_n_TACT                 (0x00000004uL)
#define DMAC7_CHSTAT_n_SUS                  (0x00000008uL)
#define DMAC7_CHSTAT_n_ER                   (0x00000010uL)
#define DMAC7_CHSTAT_n_END                  (0x00000020uL)
#define DMAC7_CHSTAT_n_TC                   (0x00000040uL)
#define DMAC7_CHSTAT_n_SR                   (0x00000080uL)
#define DMAC7_CHSTAT_n_DL                   (0x00000100uL)
#define DMAC7_CHSTAT_n_DW                   (0x00000200uL)
#define DMAC7_CHSTAT_n_DER                  (0x00000400uL)
#define DMAC7_CHSTAT_n_MODE                 (0x00000800uL)
#define DMAC7_CHSTAT_n_INTMSK               (0x00010000uL)

#define DMAC7_CHCTRL_n_SETEN                (0x00000001uL)
#define DMAC7_CHCTRL_n_CLREN                (0x00000002uL)
#define DMAC7_CHCTRL_n_STG                  (0x00000004uL)
#define DMAC7_CHCTRL_n_SWRST                (0x00000008uL)
#define DMAC7_CHCTRL_n_CLRRQ                (0x00000010uL)
#define DMAC7_CHCTRL_n_CLREND               (0x00000020uL)
#define DMAC7_CHCTRL_n_CLRTC                (0x00000040uL)
#define DMAC7_CHCTRL_n_SETSUS               (0x00000100uL)
#define DMAC7_CHCTRL_n_CLRSUS               (0x00000200uL)
#define DMAC7_CHCTRL_n_SETINTMSK            (0x00010000uL)
#define DMAC7_CHCTRL_n_CLRINTMSK            (0x00020000uL)

#define DMAC7_CHCFG_n_SEL                   (0x00000007uL)
#define DMAC7_CHCFG_n_REQD                  (0x00000008uL)
#define DMAC7_CHCFG_n_LOEN                  (0x00000010uL)
#define DMAC7_CHCFG_n_HIEN                  (0x00000020uL)
#define DMAC7_CHCFG_n_LVL                   (0x00000040uL)
#define DMAC7_CHCFG_n_AM                    (0x00000700uL)
#define DMAC7_CHCFG_n_SDS                   (0x0000F000uL)
#define DMAC7_CHCFG_n_DDS                   (0x000F0000uL)
#define DMAC7_CHCFG_n_SAD                   (0x00100000uL)
#define DMAC7_CHCFG_n_DAD                   (0x00200000uL)
#define DMAC7_CHCFG_n_TM                    (0x00400000uL)
#define DMAC7_CHCFG_n_DEM                   (0x01000000uL)
#define DMAC7_CHCFG_n_TCM                   (0x02000000uL)
#define DMAC7_CHCFG_n_SBE                   (0x08000000uL)
#define DMAC7_CHCFG_n_RSEL                  (0x10000000uL)
#define DMAC7_CHCFG_n_RSW                   (0x20000000uL)
#define DMAC7_CHCFG_n_REN                   (0x40000000uL)
#define DMAC7_CHCFG_n_DMS                   (0x80000000uL)

#define DMAC7_CHITVL_n_ITVL                 (0x0000FFFFuL)

#define DMAC7_CHEXT_n_SCA                   (0x000000F0uL)
#define DMAC7_CHEXT_n_DCA                   (0x0000F000uL)

#define DMAC7_NXLA_n_NXLA                   (0xFFFFFFFFuL)

#define DMAC7_CRLA_n_CRLA                   (0xFFFFFFFFuL)

/* ---- DMAC0-7 ---- */
#define DMAC07_DCTRL_0_7_PR                 (0x00000001uL)
#define DMAC07_DCTRL_0_7_LVINT              (0x00000002uL)
#define DMAC07_DCTRL_0_7_LDCA               (0x0000003CuL)
#define DMAC07_DCTRL_0_7_LWCA               (0x000003C0uL)

#define DMAC07_DSTAT_EN_0_7_EN0             (0x00000001uL)
#define DMAC07_DSTAT_EN_0_7_EN1             (0x00000002uL)
#define DMAC07_DSTAT_EN_0_7_EN2             (0x00000004uL)
#define DMAC07_DSTAT_EN_0_7_EN3             (0x00000008uL)
#define DMAC07_DSTAT_EN_0_7_EN4             (0x00000010uL)
#define DMAC07_DSTAT_EN_0_7_EN5             (0x00000020uL)
#define DMAC07_DSTAT_EN_0_7_EN6             (0x00000040uL)
#define DMAC07_DSTAT_EN_0_7_EN7             (0x00000080uL)

#define DMAC07_DSTAT_ER_0_7_ER0             (0x00000001uL)
#define DMAC07_DSTAT_ER_0_7_ER1             (0x00000002uL)
#define DMAC07_DSTAT_ER_0_7_ER2             (0x00000004uL)
#define DMAC07_DSTAT_ER_0_7_ER3             (0x00000008uL)
#define DMAC07_DSTAT_ER_0_7_ER4             (0x00000010uL)
#define DMAC07_DSTAT_ER_0_7_ER5             (0x00000020uL)
#define DMAC07_DSTAT_ER_0_7_ER6             (0x00000040uL)
#define DMAC07_DSTAT_ER_0_7_ER7             (0x00000080uL)

#define DMAC07_DSTAT_END_0_7_END0           (0x00000001uL)
#define DMAC07_DSTAT_END_0_7_END1           (0x00000002uL)
#define DMAC07_DSTAT_END_0_7_END2           (0x00000004uL)
#define DMAC07_DSTAT_END_0_7_END3           (0x00000008uL)
#define DMAC07_DSTAT_END_0_7_END4           (0x00000010uL)
#define DMAC07_DSTAT_END_0_7_END5           (0x00000020uL)
#define DMAC07_DSTAT_END_0_7_END6           (0x00000040uL)
#define DMAC07_DSTAT_END_0_7_END7           (0x00000080uL)

#define DMAC07_DSTAT_TC_0_7_TC0             (0x00000001uL)
#define DMAC07_DSTAT_TC_0_7_TC1             (0x00000002uL)
#define DMAC07_DSTAT_TC_0_7_TC2             (0x00000004uL)
#define DMAC07_DSTAT_TC_0_7_TC3             (0x00000008uL)
#define DMAC07_DSTAT_TC_0_7_TC4             (0x00000010uL)
#define DMAC07_DSTAT_TC_0_7_TC5             (0x00000020uL)
#define DMAC07_DSTAT_TC_0_7_TC6             (0x00000040uL)
#define DMAC07_DSTAT_TC_0_7_TC7             (0x00000080uL)

#define DMAC07_DSTAT_SUS_0_7_SUS0           (0x00000001uL)
#define DMAC07_DSTAT_SUS_0_7_SUS1           (0x00000002uL)
#define DMAC07_DSTAT_SUS_0_7_SUS2           (0x00000004uL)
#define DMAC07_DSTAT_SUS_0_7_SUS3           (0x00000008uL)
#define DMAC07_DSTAT_SUS_0_7_SUS4           (0x00000010uL)
#define DMAC07_DSTAT_SUS_0_7_SUS5           (0x00000020uL)
#define DMAC07_DSTAT_SUS_0_7_SUS6           (0x00000040uL)
#define DMAC07_DSTAT_SUS_0_7_SUS7           (0x00000080uL)

/* ---- DMAC8 ---- */
#define DMAC8_N0SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC8_N0DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC8_N0TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC8_N1SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC8_N1DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC8_N1TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC8_CRSA_n_CRSA                   (0xFFFFFFFFuL)

#define DMAC8_CRDA_n_CRDA                   (0xFFFFFFFFuL)

#define DMAC8_CRTB_n_CRTB                   (0xFFFFFFFFuL)

#define DMAC8_CHSTAT_n_EN                   (0x00000001uL)
#define DMAC8_CHSTAT_n_RQST                 (0x00000002uL)
#define DMAC8_CHSTAT_n_TACT                 (0x00000004uL)
#define DMAC8_CHSTAT_n_SUS                  (0x00000008uL)
#define DMAC8_CHSTAT_n_ER                   (0x00000010uL)
#define DMAC8_CHSTAT_n_END                  (0x00000020uL)
#define DMAC8_CHSTAT_n_TC                   (0x00000040uL)
#define DMAC8_CHSTAT_n_SR                   (0x00000080uL)
#define DMAC8_CHSTAT_n_DL                   (0x00000100uL)
#define DMAC8_CHSTAT_n_DW                   (0x00000200uL)
#define DMAC8_CHSTAT_n_DER                  (0x00000400uL)
#define DMAC8_CHSTAT_n_MODE                 (0x00000800uL)
#define DMAC8_CHSTAT_n_INTMSK               (0x00010000uL)

#define DMAC8_CHCTRL_n_SETEN                (0x00000001uL)
#define DMAC8_CHCTRL_n_CLREN                (0x00000002uL)
#define DMAC8_CHCTRL_n_STG                  (0x00000004uL)
#define DMAC8_CHCTRL_n_SWRST                (0x00000008uL)
#define DMAC8_CHCTRL_n_CLRRQ                (0x00000010uL)
#define DMAC8_CHCTRL_n_CLREND               (0x00000020uL)
#define DMAC8_CHCTRL_n_CLRTC                (0x00000040uL)
#define DMAC8_CHCTRL_n_SETSUS               (0x00000100uL)
#define DMAC8_CHCTRL_n_CLRSUS               (0x00000200uL)
#define DMAC8_CHCTRL_n_SETINTMSK            (0x00010000uL)
#define DMAC8_CHCTRL_n_CLRINTMSK            (0x00020000uL)

#define DMAC8_CHCFG_n_SEL                   (0x00000007uL)
#define DMAC8_CHCFG_n_REQD                  (0x00000008uL)
#define DMAC8_CHCFG_n_LOEN                  (0x00000010uL)
#define DMAC8_CHCFG_n_HIEN                  (0x00000020uL)
#define DMAC8_CHCFG_n_LVL                   (0x00000040uL)
#define DMAC8_CHCFG_n_AM                    (0x00000700uL)
#define DMAC8_CHCFG_n_SDS                   (0x0000F000uL)
#define DMAC8_CHCFG_n_DDS                   (0x000F0000uL)
#define DMAC8_CHCFG_n_SAD                   (0x00100000uL)
#define DMAC8_CHCFG_n_DAD                   (0x00200000uL)
#define DMAC8_CHCFG_n_TM                    (0x00400000uL)
#define DMAC8_CHCFG_n_DEM                   (0x01000000uL)
#define DMAC8_CHCFG_n_TCM                   (0x02000000uL)
#define DMAC8_CHCFG_n_SBE                   (0x08000000uL)
#define DMAC8_CHCFG_n_RSEL                  (0x10000000uL)
#define DMAC8_CHCFG_n_RSW                   (0x20000000uL)
#define DMAC8_CHCFG_n_REN                   (0x40000000uL)
#define DMAC8_CHCFG_n_DMS                   (0x80000000uL)

#define DMAC8_CHITVL_n_ITVL                 (0x0000FFFFuL)

#define DMAC8_CHEXT_n_SCA                   (0x000000F0uL)
#define DMAC8_CHEXT_n_DCA                   (0x0000F000uL)

#define DMAC8_NXLA_n_NXLA                   (0xFFFFFFFFuL)

#define DMAC8_CRLA_n_CRLA                   (0xFFFFFFFFuL)

/* ---- DMAC9 ---- */
#define DMAC9_N0SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC9_N0DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC9_N0TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC9_N1SA_n_SA                     (0xFFFFFFFFuL)

#define DMAC9_N1DA_n_DA                     (0xFFFFFFFFuL)

#define DMAC9_N1TB_n_TB                     (0xFFFFFFFFuL)

#define DMAC9_CRSA_n_CRSA                   (0xFFFFFFFFuL)

#define DMAC9_CRDA_n_CRDA                   (0xFFFFFFFFuL)

#define DMAC9_CRTB_n_CRTB                   (0xFFFFFFFFuL)

#define DMAC9_CHSTAT_n_EN                   (0x00000001uL)
#define DMAC9_CHSTAT_n_RQST                 (0x00000002uL)
#define DMAC9_CHSTAT_n_TACT                 (0x00000004uL)
#define DMAC9_CHSTAT_n_SUS                  (0x00000008uL)
#define DMAC9_CHSTAT_n_ER                   (0x00000010uL)
#define DMAC9_CHSTAT_n_END                  (0x00000020uL)
#define DMAC9_CHSTAT_n_TC                   (0x00000040uL)
#define DMAC9_CHSTAT_n_SR                   (0x00000080uL)
#define DMAC9_CHSTAT_n_DL                   (0x00000100uL)
#define DMAC9_CHSTAT_n_DW                   (0x00000200uL)
#define DMAC9_CHSTAT_n_DER                  (0x00000400uL)
#define DMAC9_CHSTAT_n_MODE                 (0x00000800uL)
#define DMAC9_CHSTAT_n_INTMSK               (0x00010000uL)

#define DMAC9_CHCTRL_n_SETEN                (0x00000001uL)
#define DMAC9_CHCTRL_n_CLREN                (0x00000002uL)
#define DMAC9_CHCTRL_n_STG                  (0x00000004uL)
#define DMAC9_CHCTRL_n_SWRST                (0x00000008uL)
#define DMAC9_CHCTRL_n_CLRRQ                (0x00000010uL)
#define DMAC9_CHCTRL_n_CLREND               (0x00000020uL)
#define DMAC9_CHCTRL_n_CLRTC                (0x00000040uL)
#define DMAC9_CHCTRL_n_SETSUS               (0x00000100uL)
#define DMAC9_CHCTRL_n_CLRSUS               (0x00000200uL)
#define DMAC9_CHCTRL_n_SETINTMSK            (0x00010000uL)
#define DMAC9_CHCTRL_n_CLRINTMSK            (0x00020000uL)

#define DMAC9_CHCFG_n_SEL                   (0x00000007uL)
#define DMAC9_CHCFG_n_REQD                  (0x00000008uL)
#define DMAC9_CHCFG_n_LOEN                  (0x00000010uL)
#define DMAC9_CHCFG_n_HIEN                  (0x00000020uL)
#define DMAC9_CHCFG_n_LVL                   (0x00000040uL)
#define DMAC9_CHCFG_n_AM                    (0x00000700uL)
#define DMAC9_CHCFG_n_SDS                   (0x0000F000uL)
#define DMAC9_CHCFG_n_DDS                   (0x000F0000uL)
#define DMAC9_CHCFG_n_SAD                   (0x00100000uL)
#define DMAC9_CHCFG_n_DAD                   (0x00200000uL)
#define DMAC9_CHCFG_n_TM                    (0x00400000uL)
#define DMAC9_CHCFG_n_DEM                   (0x01000000uL)
#define DMAC9_CHCFG_n_TCM                   (0x02000000uL)
#define DMAC9_CHCFG_n_SBE                   (0x08000000uL)
#define DMAC9_CHCFG_n_RSEL                  (0x10000000uL)
#define DMAC9_CHCFG_n_RSW                   (0x20000000uL)
#define DMAC9_CHCFG_n_REN                   (0x40000000uL)
#define DMAC9_CHCFG_n_DMS                   (0x80000000uL)

#define DMAC9_CHITVL_n_ITVL                 (0x0000FFFFuL)

#define DMAC9_CHEXT_n_SCA                   (0x000000F0uL)
#define DMAC9_CHEXT_n_DCA                   (0x0000F000uL)

#define DMAC9_NXLA_n_NXLA                   (0xFFFFFFFFuL)

#define DMAC9_CRLA_n_CRLA                   (0xFFFFFFFFuL)

/* ---- DMAC10 ---- */
#define DMAC10_N0SA_n_SA                    (0xFFFFFFFFuL)

#define DMAC10_N0DA_n_DA                    (0xFFFFFFFFuL)

#define DMAC10_N0TB_n_TB                    (0xFFFFFFFFuL)

#define DMAC10_N1SA_n_SA                    (0xFFFFFFFFuL)

#define DMAC10_N1DA_n_DA                    (0xFFFFFFFFuL)

#define DMAC10_N1TB_n_TB                    (0xFFFFFFFFuL)

#define DMAC10_CRSA_n_CRSA                  (0xFFFFFFFFuL)

#define DMAC10_CRDA_n_CRDA                  (0xFFFFFFFFuL)

#define DMAC10_CRTB_n_CRTB                  (0xFFFFFFFFuL)

#define DMAC10_CHSTAT_n_EN                  (0x00000001uL)
#define DMAC10_CHSTAT_n_RQST                (0x00000002uL)
#define DMAC10_CHSTAT_n_TACT                (0x00000004uL)
#define DMAC10_CHSTAT_n_SUS                 (0x00000008uL)
#define DMAC10_CHSTAT_n_ER                  (0x00000010uL)
#define DMAC10_CHSTAT_n_END                 (0x00000020uL)
#define DMAC10_CHSTAT_n_TC                  (0x00000040uL)
#define DMAC10_CHSTAT_n_SR                  (0x00000080uL)
#define DMAC10_CHSTAT_n_DL                  (0x00000100uL)
#define DMAC10_CHSTAT_n_DW                  (0x00000200uL)
#define DMAC10_CHSTAT_n_DER                 (0x00000400uL)
#define DMAC10_CHSTAT_n_MODE                (0x00000800uL)
#define DMAC10_CHSTAT_n_INTMSK              (0x00010000uL)

#define DMAC10_CHCTRL_n_SETEN               (0x00000001uL)
#define DMAC10_CHCTRL_n_CLREN               (0x00000002uL)
#define DMAC10_CHCTRL_n_STG                 (0x00000004uL)
#define DMAC10_CHCTRL_n_SWRST               (0x00000008uL)
#define DMAC10_CHCTRL_n_CLRRQ               (0x00000010uL)
#define DMAC10_CHCTRL_n_CLREND              (0x00000020uL)
#define DMAC10_CHCTRL_n_CLRTC               (0x00000040uL)
#define DMAC10_CHCTRL_n_SETSUS              (0x00000100uL)
#define DMAC10_CHCTRL_n_CLRSUS              (0x00000200uL)
#define DMAC10_CHCTRL_n_SETINTMSK           (0x00010000uL)
#define DMAC10_CHCTRL_n_CLRINTMSK           (0x00020000uL)

#define DMAC10_CHCFG_n_SEL                  (0x00000007uL)
#define DMAC10_CHCFG_n_REQD                 (0x00000008uL)
#define DMAC10_CHCFG_n_LOEN                 (0x00000010uL)
#define DMAC10_CHCFG_n_HIEN                 (0x00000020uL)
#define DMAC10_CHCFG_n_LVL                  (0x00000040uL)
#define DMAC10_CHCFG_n_AM                   (0x00000700uL)
#define DMAC10_CHCFG_n_SDS                  (0x0000F000uL)
#define DMAC10_CHCFG_n_DDS                  (0x000F0000uL)
#define DMAC10_CHCFG_n_SAD                  (0x00100000uL)
#define DMAC10_CHCFG_n_DAD                  (0x00200000uL)
#define DMAC10_CHCFG_n_TM                   (0x00400000uL)
#define DMAC10_CHCFG_n_DEM                  (0x01000000uL)
#define DMAC10_CHCFG_n_TCM                  (0x02000000uL)
#define DMAC10_CHCFG_n_SBE                  (0x08000000uL)
#define DMAC10_CHCFG_n_RSEL                 (0x10000000uL)
#define DMAC10_CHCFG_n_RSW                  (0x20000000uL)
#define DMAC10_CHCFG_n_REN                  (0x40000000uL)
#define DMAC10_CHCFG_n_DMS                  (0x80000000uL)

#define DMAC10_CHITVL_n_ITVL                (0x0000FFFFuL)

#define DMAC10_CHEXT_n_SCA                  (0x000000F0uL)
#define DMAC10_CHEXT_n_DCA                  (0x0000F000uL)

#define DMAC10_NXLA_n_NXLA                  (0xFFFFFFFFuL)

#define DMAC10_CRLA_n_CRLA                  (0xFFFFFFFFuL)

/* ---- DMAC11 ---- */
#define DMAC11_N0SA_n_SA                    (0xFFFFFFFFuL)

#define DMAC11_N0DA_n_DA                    (0xFFFFFFFFuL)

#define DMAC11_N0TB_n_TB                    (0xFFFFFFFFuL)

#define DMAC11_N1SA_n_SA                    (0xFFFFFFFFuL)

#define DMAC11_N1DA_n_DA                    (0xFFFFFFFFuL)

#define DMAC11_N1TB_n_TB                    (0xFFFFFFFFuL)

#define DMAC11_CRSA_n_CRSA                  (0xFFFFFFFFuL)

#define DMAC11_CRDA_n_CRDA                  (0xFFFFFFFFuL)

#define DMAC11_CRTB_n_CRTB                  (0xFFFFFFFFuL)

#define DMAC11_CHSTAT_n_EN                  (0x00000001uL)
#define DMAC11_CHSTAT_n_RQST                (0x00000002uL)
#define DMAC11_CHSTAT_n_TACT                (0x00000004uL)
#define DMAC11_CHSTAT_n_SUS                 (0x00000008uL)
#define DMAC11_CHSTAT_n_ER                  (0x00000010uL)
#define DMAC11_CHSTAT_n_END                 (0x00000020uL)
#define DMAC11_CHSTAT_n_TC                  (0x00000040uL)
#define DMAC11_CHSTAT_n_SR                  (0x00000080uL)
#define DMAC11_CHSTAT_n_DL                  (0x00000100uL)
#define DMAC11_CHSTAT_n_DW                  (0x00000200uL)
#define DMAC11_CHSTAT_n_DER                 (0x00000400uL)
#define DMAC11_CHSTAT_n_MODE                (0x00000800uL)
#define DMAC11_CHSTAT_n_INTMSK              (0x00010000uL)

#define DMAC11_CHCTRL_n_SETEN               (0x00000001uL)
#define DMAC11_CHCTRL_n_CLREN               (0x00000002uL)
#define DMAC11_CHCTRL_n_STG                 (0x00000004uL)
#define DMAC11_CHCTRL_n_SWRST               (0x00000008uL)
#define DMAC11_CHCTRL_n_CLRRQ               (0x00000010uL)
#define DMAC11_CHCTRL_n_CLREND              (0x00000020uL)
#define DMAC11_CHCTRL_n_CLRTC               (0x00000040uL)
#define DMAC11_CHCTRL_n_SETSUS              (0x00000100uL)
#define DMAC11_CHCTRL_n_CLRSUS              (0x00000200uL)
#define DMAC11_CHCTRL_n_SETINTMSK           (0x00010000uL)
#define DMAC11_CHCTRL_n_CLRINTMSK           (0x00020000uL)

#define DMAC11_CHCFG_n_SEL                  (0x00000007uL)
#define DMAC11_CHCFG_n_REQD                 (0x00000008uL)
#define DMAC11_CHCFG_n_LOEN                 (0x00000010uL)
#define DMAC11_CHCFG_n_HIEN                 (0x00000020uL)
#define DMAC11_CHCFG_n_LVL                  (0x00000040uL)
#define DMAC11_CHCFG_n_AM                   (0x00000700uL)
#define DMAC11_CHCFG_n_SDS                  (0x0000F000uL)
#define DMAC11_CHCFG_n_DDS                  (0x000F0000uL)
#define DMAC11_CHCFG_n_SAD                  (0x00100000uL)
#define DMAC11_CHCFG_n_DAD                  (0x00200000uL)
#define DMAC11_CHCFG_n_TM                   (0x00400000uL)
#define DMAC11_CHCFG_n_DEM                  (0x01000000uL)
#define DMAC11_CHCFG_n_TCM                  (0x02000000uL)
#define DMAC11_CHCFG_n_SBE                  (0x08000000uL)
#define DMAC11_CHCFG_n_RSEL                 (0x10000000uL)
#define DMAC11_CHCFG_n_RSW                  (0x20000000uL)
#define DMAC11_CHCFG_n_REN                  (0x40000000uL)
#define DMAC11_CHCFG_n_DMS                  (0x80000000uL)

#define DMAC11_CHITVL_n_ITVL                (0x0000FFFFuL)

#define DMAC11_CHEXT_n_SCA                  (0x000000F0uL)
#define DMAC11_CHEXT_n_DCA                  (0x0000F000uL)

#define DMAC11_NXLA_n_NXLA                  (0xFFFFFFFFuL)

#define DMAC11_CRLA_n_CRLA                  (0xFFFFFFFFuL)

/* ---- DMAC12 ---- */
#define DMAC12_N0SA_n_SA                    (0xFFFFFFFFuL)

#define DMAC12_N0DA_n_DA                    (0xFFFFFFFFuL)

#define DMAC12_N0TB_n_TB                    (0xFFFFFFFFuL)

#define DMAC12_N1SA_n_SA                    (0xFFFFFFFFuL)

#define DMAC12_N1DA_n_DA                    (0xFFFFFFFFuL)

#define DMAC12_N1TB_n_TB                    (0xFFFFFFFFuL)

#define DMAC12_CRSA_n_CRSA                  (0xFFFFFFFFuL)

#define DMAC12_CRDA_n_CRDA                  (0xFFFFFFFFuL)

#define DMAC12_CRTB_n_CRTB                  (0xFFFFFFFFuL)

#define DMAC12_CHSTAT_n_EN                  (0x00000001uL)
#define DMAC12_CHSTAT_n_RQST                (0x00000002uL)
#define DMAC12_CHSTAT_n_TACT                (0x00000004uL)
#define DMAC12_CHSTAT_n_SUS                 (0x00000008uL)
#define DMAC12_CHSTAT_n_ER                  (0x00000010uL)
#define DMAC12_CHSTAT_n_END                 (0x00000020uL)
#define DMAC12_CHSTAT_n_TC                  (0x00000040uL)
#define DMAC12_CHSTAT_n_SR                  (0x00000080uL)
#define DMAC12_CHSTAT_n_DL                  (0x00000100uL)
#define DMAC12_CHSTAT_n_DW                  (0x00000200uL)
#define DMAC12_CHSTAT_n_DER                 (0x00000400uL)
#define DMAC12_CHSTAT_n_MODE                (0x00000800uL)
#define DMAC12_CHSTAT_n_INTMSK              (0x00010000uL)

#define DMAC12_CHCTRL_n_SETEN               (0x00000001uL)
#define DMAC12_CHCTRL_n_CLREN               (0x00000002uL)
#define DMAC12_CHCTRL_n_STG                 (0x00000004uL)
#define DMAC12_CHCTRL_n_SWRST               (0x00000008uL)
#define DMAC12_CHCTRL_n_CLRRQ               (0x00000010uL)
#define DMAC12_CHCTRL_n_CLREND              (0x00000020uL)
#define DMAC12_CHCTRL_n_CLRTC               (0x00000040uL)
#define DMAC12_CHCTRL_n_SETSUS              (0x00000100uL)
#define DMAC12_CHCTRL_n_CLRSUS              (0x00000200uL)
#define DMAC12_CHCTRL_n_SETINTMSK           (0x00010000uL)
#define DMAC12_CHCTRL_n_CLRINTMSK           (0x00020000uL)

#define DMAC12_CHCFG_n_SEL                  (0x00000007uL)
#define DMAC12_CHCFG_n_REQD                 (0x00000008uL)
#define DMAC12_CHCFG_n_LOEN                 (0x00000010uL)
#define DMAC12_CHCFG_n_HIEN                 (0x00000020uL)
#define DMAC12_CHCFG_n_LVL                  (0x00000040uL)
#define DMAC12_CHCFG_n_AM                   (0x00000700uL)
#define DMAC12_CHCFG_n_SDS                  (0x0000F000uL)
#define DMAC12_CHCFG_n_DDS                  (0x000F0000uL)
#define DMAC12_CHCFG_n_SAD                  (0x00100000uL)
#define DMAC12_CHCFG_n_DAD                  (0x00200000uL)
#define DMAC12_CHCFG_n_TM                   (0x00400000uL)
#define DMAC12_CHCFG_n_DEM                  (0x01000000uL)
#define DMAC12_CHCFG_n_TCM                  (0x02000000uL)
#define DMAC12_CHCFG_n_SBE                  (0x08000000uL)
#define DMAC12_CHCFG_n_RSEL                 (0x10000000uL)
#define DMAC12_CHCFG_n_RSW                  (0x20000000uL)
#define DMAC12_CHCFG_n_REN                  (0x40000000uL)
#define DMAC12_CHCFG_n_DMS                  (0x80000000uL)

#define DMAC12_CHITVL_n_ITVL                (0x0000FFFFuL)

#define DMAC12_CHEXT_n_SCA                  (0x000000F0uL)
#define DMAC12_CHEXT_n_DCA                  (0x0000F000uL)

#define DMAC12_NXLA_n_NXLA                  (0xFFFFFFFFuL)

#define DMAC12_CRLA_n_CRLA                  (0xFFFFFFFFuL)

/* ---- DMAC13 ---- */
#define DMAC13_N0SA_n_SA                    (0xFFFFFFFFuL)

#define DMAC13_N0DA_n_DA                    (0xFFFFFFFFuL)

#define DMAC13_N0TB_n_TB                    (0xFFFFFFFFuL)

#define DMAC13_N1SA_n_SA                    (0xFFFFFFFFuL)

#define DMAC13_N1DA_n_DA                    (0xFFFFFFFFuL)

#define DMAC13_N1TB_n_TB                    (0xFFFFFFFFuL)

#define DMAC13_CRSA_n_CRSA                  (0xFFFFFFFFuL)

#define DMAC13_CRDA_n_CRDA                  (0xFFFFFFFFuL)

#define DMAC13_CRTB_n_CRTB                  (0xFFFFFFFFuL)

#define DMAC13_CHSTAT_n_EN                  (0x00000001uL)
#define DMAC13_CHSTAT_n_RQST                (0x00000002uL)
#define DMAC13_CHSTAT_n_TACT                (0x00000004uL)
#define DMAC13_CHSTAT_n_SUS                 (0x00000008uL)
#define DMAC13_CHSTAT_n_ER                  (0x00000010uL)
#define DMAC13_CHSTAT_n_END                 (0x00000020uL)
#define DMAC13_CHSTAT_n_TC                  (0x00000040uL)
#define DMAC13_CHSTAT_n_SR                  (0x00000080uL)
#define DMAC13_CHSTAT_n_DL                  (0x00000100uL)
#define DMAC13_CHSTAT_n_DW                  (0x00000200uL)
#define DMAC13_CHSTAT_n_DER                 (0x00000400uL)
#define DMAC13_CHSTAT_n_MODE                (0x00000800uL)
#define DMAC13_CHSTAT_n_INTMSK              (0x00010000uL)

#define DMAC13_CHCTRL_n_SETEN               (0x00000001uL)
#define DMAC13_CHCTRL_n_CLREN               (0x00000002uL)
#define DMAC13_CHCTRL_n_STG                 (0x00000004uL)
#define DMAC13_CHCTRL_n_SWRST               (0x00000008uL)
#define DMAC13_CHCTRL_n_CLRRQ               (0x00000010uL)
#define DMAC13_CHCTRL_n_CLREND              (0x00000020uL)
#define DMAC13_CHCTRL_n_CLRTC               (0x00000040uL)
#define DMAC13_CHCTRL_n_SETSUS              (0x00000100uL)
#define DMAC13_CHCTRL_n_CLRSUS              (0x00000200uL)
#define DMAC13_CHCTRL_n_SETINTMSK           (0x00010000uL)
#define DMAC13_CHCTRL_n_CLRINTMSK           (0x00020000uL)

#define DMAC13_CHCFG_n_SEL                  (0x00000007uL)
#define DMAC13_CHCFG_n_REQD                 (0x00000008uL)
#define DMAC13_CHCFG_n_LOEN                 (0x00000010uL)
#define DMAC13_CHCFG_n_HIEN                 (0x00000020uL)
#define DMAC13_CHCFG_n_LVL                  (0x00000040uL)
#define DMAC13_CHCFG_n_AM                   (0x00000700uL)
#define DMAC13_CHCFG_n_SDS                  (0x0000F000uL)
#define DMAC13_CHCFG_n_DDS                  (0x000F0000uL)
#define DMAC13_CHCFG_n_SAD                  (0x00100000uL)
#define DMAC13_CHCFG_n_DAD                  (0x00200000uL)
#define DMAC13_CHCFG_n_TM                   (0x00400000uL)
#define DMAC13_CHCFG_n_DEM                  (0x01000000uL)
#define DMAC13_CHCFG_n_TCM                  (0x02000000uL)
#define DMAC13_CHCFG_n_SBE                  (0x08000000uL)
#define DMAC13_CHCFG_n_RSEL                 (0x10000000uL)
#define DMAC13_CHCFG_n_RSW                  (0x20000000uL)
#define DMAC13_CHCFG_n_REN                  (0x40000000uL)
#define DMAC13_CHCFG_n_DMS                  (0x80000000uL)

#define DMAC13_CHITVL_n_ITVL                (0x0000FFFFuL)

#define DMAC13_CHEXT_n_SCA                  (0x000000F0uL)
#define DMAC13_CHEXT_n_DCA                  (0x0000F000uL)

#define DMAC13_NXLA_n_NXLA                  (0xFFFFFFFFuL)

#define DMAC13_CRLA_n_CRLA                  (0xFFFFFFFFuL)

/* ---- DMAC14 ---- */
#define DMAC14_N0SA_n_SA                    (0xFFFFFFFFuL)

#define DMAC14_N0DA_n_DA                    (0xFFFFFFFFuL)

#define DMAC14_N0TB_n_TB                    (0xFFFFFFFFuL)

#define DMAC14_N1SA_n_SA                    (0xFFFFFFFFuL)

#define DMAC14_N1DA_n_DA                    (0xFFFFFFFFuL)

#define DMAC14_N1TB_n_TB                    (0xFFFFFFFFuL)

#define DMAC14_CRSA_n_CRSA                  (0xFFFFFFFFuL)

#define DMAC14_CRDA_n_CRDA                  (0xFFFFFFFFuL)

#define DMAC14_CRTB_n_CRTB                  (0xFFFFFFFFuL)

#define DMAC14_CHSTAT_n_EN                  (0x00000001uL)
#define DMAC14_CHSTAT_n_RQST                (0x00000002uL)
#define DMAC14_CHSTAT_n_TACT                (0x00000004uL)
#define DMAC14_CHSTAT_n_SUS                 (0x00000008uL)
#define DMAC14_CHSTAT_n_ER                  (0x00000010uL)
#define DMAC14_CHSTAT_n_END                 (0x00000020uL)
#define DMAC14_CHSTAT_n_TC                  (0x00000040uL)
#define DMAC14_CHSTAT_n_SR                  (0x00000080uL)
#define DMAC14_CHSTAT_n_DL                  (0x00000100uL)
#define DMAC14_CHSTAT_n_DW                  (0x00000200uL)
#define DMAC14_CHSTAT_n_DER                 (0x00000400uL)
#define DMAC14_CHSTAT_n_MODE                (0x00000800uL)
#define DMAC14_CHSTAT_n_INTMSK              (0x00010000uL)

#define DMAC14_CHCTRL_n_SETEN               (0x00000001uL)
#define DMAC14_CHCTRL_n_CLREN               (0x00000002uL)
#define DMAC14_CHCTRL_n_STG                 (0x00000004uL)
#define DMAC14_CHCTRL_n_SWRST               (0x00000008uL)
#define DMAC14_CHCTRL_n_CLRRQ               (0x00000010uL)
#define DMAC14_CHCTRL_n_CLREND              (0x00000020uL)
#define DMAC14_CHCTRL_n_CLRTC               (0x00000040uL)
#define DMAC14_CHCTRL_n_SETSUS              (0x00000100uL)
#define DMAC14_CHCTRL_n_CLRSUS              (0x00000200uL)
#define DMAC14_CHCTRL_n_SETINTMSK           (0x00010000uL)
#define DMAC14_CHCTRL_n_CLRINTMSK           (0x00020000uL)

#define DMAC14_CHCFG_n_SEL                  (0x00000007uL)
#define DMAC14_CHCFG_n_REQD                 (0x00000008uL)
#define DMAC14_CHCFG_n_LOEN                 (0x00000010uL)
#define DMAC14_CHCFG_n_HIEN                 (0x00000020uL)
#define DMAC14_CHCFG_n_LVL                  (0x00000040uL)
#define DMAC14_CHCFG_n_AM                   (0x00000700uL)
#define DMAC14_CHCFG_n_SDS                  (0x0000F000uL)
#define DMAC14_CHCFG_n_DDS                  (0x000F0000uL)
#define DMAC14_CHCFG_n_SAD                  (0x00100000uL)
#define DMAC14_CHCFG_n_DAD                  (0x00200000uL)
#define DMAC14_CHCFG_n_TM                   (0x00400000uL)
#define DMAC14_CHCFG_n_DEM                  (0x01000000uL)
#define DMAC14_CHCFG_n_TCM                  (0x02000000uL)
#define DMAC14_CHCFG_n_SBE                  (0x08000000uL)
#define DMAC14_CHCFG_n_RSEL                 (0x10000000uL)
#define DMAC14_CHCFG_n_RSW                  (0x20000000uL)
#define DMAC14_CHCFG_n_REN                  (0x40000000uL)
#define DMAC14_CHCFG_n_DMS                  (0x80000000uL)

#define DMAC14_CHITVL_n_ITVL                (0x0000FFFFuL)

#define DMAC14_CHEXT_n_SCA                  (0x000000F0uL)
#define DMAC14_CHEXT_n_DCA                  (0x0000F000uL)

#define DMAC14_NXLA_n_NXLA                  (0xFFFFFFFFuL)

#define DMAC14_CRLA_n_CRLA                  (0xFFFFFFFFuL)

/* ---- DMAC15 ---- */
#define DMAC15_N0SA_n_SA                    (0xFFFFFFFFuL)

#define DMAC15_N0DA_n_DA                    (0xFFFFFFFFuL)

#define DMAC15_N0TB_n_TB                    (0xFFFFFFFFuL)

#define DMAC15_N1SA_n_SA                    (0xFFFFFFFFuL)

#define DMAC15_N1DA_n_DA                    (0xFFFFFFFFuL)

#define DMAC15_N1TB_n_TB                    (0xFFFFFFFFuL)

#define DMAC15_CRSA_n_CRSA                  (0xFFFFFFFFuL)

#define DMAC15_CRDA_n_CRDA                  (0xFFFFFFFFuL)

#define DMAC15_CRTB_n_CRTB                  (0xFFFFFFFFuL)

#define DMAC15_CHSTAT_n_EN                  (0x00000001uL)
#define DMAC15_CHSTAT_n_RQST                (0x00000002uL)
#define DMAC15_CHSTAT_n_TACT                (0x00000004uL)
#define DMAC15_CHSTAT_n_SUS                 (0x00000008uL)
#define DMAC15_CHSTAT_n_ER                  (0x00000010uL)
#define DMAC15_CHSTAT_n_END                 (0x00000020uL)
#define DMAC15_CHSTAT_n_TC                  (0x00000040uL)
#define DMAC15_CHSTAT_n_SR                  (0x00000080uL)
#define DMAC15_CHSTAT_n_DL                  (0x00000100uL)
#define DMAC15_CHSTAT_n_DW                  (0x00000200uL)
#define DMAC15_CHSTAT_n_DER                 (0x00000400uL)
#define DMAC15_CHSTAT_n_MODE                (0x00000800uL)
#define DMAC15_CHSTAT_n_INTMSK              (0x00010000uL)

#define DMAC15_CHCTRL_n_SETEN               (0x00000001uL)
#define DMAC15_CHCTRL_n_CLREN               (0x00000002uL)
#define DMAC15_CHCTRL_n_STG                 (0x00000004uL)
#define DMAC15_CHCTRL_n_SWRST               (0x00000008uL)
#define DMAC15_CHCTRL_n_CLRRQ               (0x00000010uL)
#define DMAC15_CHCTRL_n_CLREND              (0x00000020uL)
#define DMAC15_CHCTRL_n_CLRTC               (0x00000040uL)
#define DMAC15_CHCTRL_n_SETSUS              (0x00000100uL)
#define DMAC15_CHCTRL_n_CLRSUS              (0x00000200uL)
#define DMAC15_CHCTRL_n_SETINTMSK           (0x00010000uL)
#define DMAC15_CHCTRL_n_CLRINTMSK           (0x00020000uL)

#define DMAC15_CHCFG_n_SEL                  (0x00000007uL)
#define DMAC15_CHCFG_n_REQD                 (0x00000008uL)
#define DMAC15_CHCFG_n_LOEN                 (0x00000010uL)
#define DMAC15_CHCFG_n_HIEN                 (0x00000020uL)
#define DMAC15_CHCFG_n_LVL                  (0x00000040uL)
#define DMAC15_CHCFG_n_AM                   (0x00000700uL)
#define DMAC15_CHCFG_n_SDS                  (0x0000F000uL)
#define DMAC15_CHCFG_n_DDS                  (0x000F0000uL)
#define DMAC15_CHCFG_n_SAD                  (0x00100000uL)
#define DMAC15_CHCFG_n_DAD                  (0x00200000uL)
#define DMAC15_CHCFG_n_TM                   (0x00400000uL)
#define DMAC15_CHCFG_n_DEM                  (0x01000000uL)
#define DMAC15_CHCFG_n_TCM                  (0x02000000uL)
#define DMAC15_CHCFG_n_SBE                  (0x08000000uL)
#define DMAC15_CHCFG_n_RSEL                 (0x10000000uL)
#define DMAC15_CHCFG_n_RSW                  (0x20000000uL)
#define DMAC15_CHCFG_n_REN                  (0x40000000uL)
#define DMAC15_CHCFG_n_DMS                  (0x80000000uL)

#define DMAC15_CHITVL_n_ITVL                (0x0000FFFFuL)

#define DMAC15_CHEXT_n_SCA                  (0x000000F0uL)
#define DMAC15_CHEXT_n_DCA                  (0x0000F000uL)

#define DMAC15_NXLA_n_NXLA                  (0xFFFFFFFFuL)

#define DMAC15_CRLA_n_CRLA                  (0xFFFFFFFFuL)

/* ---- DMAC8-15 ---- */
#define DMAC815_DCTRL_8_15_PR               (0x00000001uL)
#define DMAC815_DCTRL_8_15_LVINT            (0x00000002uL)
#define DMAC815_DCTRL_8_15_LDCA             (0x0000003CuL)
#define DMAC815_DCTRL_8_15_LWCA             (0x00003C00uL)

#define DMAC815_DSTAT_EN_8_15_EN8           (0x00000001uL)
#define DMAC815_DSTAT_EN_8_15_EN9           (0x00000002uL)
#define DMAC815_DSTAT_EN_8_15_EN10          (0x00000004uL)
#define DMAC815_DSTAT_EN_8_15_EN11          (0x00000008uL)
#define DMAC815_DSTAT_EN_8_15_EN12          (0x00000010uL)
#define DMAC815_DSTAT_EN_8_15_EN13          (0x00000020uL)
#define DMAC815_DSTAT_EN_8_15_EN14          (0x00000040uL)
#define DMAC815_DSTAT_EN_8_15_EN15          (0x00000080uL)

#define DMAC815_DSTAT_ER_8_15_ER8           (0x00000001uL)
#define DMAC815_DSTAT_ER_8_15_ER9           (0x00000002uL)
#define DMAC815_DSTAT_ER_8_15_ER10          (0x00000004uL)
#define DMAC815_DSTAT_ER_8_15_ER11          (0x00000008uL)
#define DMAC815_DSTAT_ER_8_15_ER12          (0x00000010uL)
#define DMAC815_DSTAT_ER_8_15_ER13          (0x00000020uL)
#define DMAC815_DSTAT_ER_8_15_ER14          (0x00000040uL)
#define DMAC815_DSTAT_ER_8_15_ER15          (0x00000080uL)

#define DMAC815_DSTAT_END_8_15_END8         (0x00000001uL)
#define DMAC815_DSTAT_END_8_15_END9         (0x00000002uL)
#define DMAC815_DSTAT_END_8_15_END10        (0x00000004uL)
#define DMAC815_DSTAT_END_8_15_END11        (0x00000008uL)
#define DMAC815_DSTAT_END_8_15_END12        (0x00000010uL)
#define DMAC815_DSTAT_END_8_15_END13        (0x00000020uL)
#define DMAC815_DSTAT_END_8_15_END14        (0x00000040uL)
#define DMAC815_DSTAT_END_8_15_END15        (0x00000080uL)

#define DMAC815_DSTAT_TC_8_15_TC8           (0x00000001uL)
#define DMAC815_DSTAT_TC_8_15_TC9           (0x00000002uL)
#define DMAC815_DSTAT_TC_8_15_TC10          (0x00000004uL)
#define DMAC815_DSTAT_TC_8_15_TC11          (0x00000008uL)
#define DMAC815_DSTAT_TC_8_15_TC12          (0x00000010uL)
#define DMAC815_DSTAT_TC_8_15_TC13          (0x00000020uL)
#define DMAC815_DSTAT_TC_8_15_TC14          (0x00000040uL)
#define DMAC815_DSTAT_TC_8_15_TC15          (0x00000080uL)

#define DMAC815_DSTAT_SUS_8_15_SUS8         (0x00000001uL)
#define DMAC815_DSTAT_SUS_8_15_SUS9         (0x00000002uL)
#define DMAC815_DSTAT_SUS_8_15_SUS10        (0x00000004uL)
#define DMAC815_DSTAT_SUS_8_15_SUS11        (0x00000008uL)
#define DMAC815_DSTAT_SUS_8_15_SUS12        (0x00000010uL)
#define DMAC815_DSTAT_SUS_8_15_SUS13        (0x00000020uL)
#define DMAC815_DSTAT_SUS_8_15_SUS14        (0x00000040uL)
#define DMAC815_DSTAT_SUS_8_15_SUS15        (0x00000080uL)

/* ---- DMAC0-1 ---- */
#define DMAC01_DMARS_CH0_RID                (0x00000003uL)
#define DMAC01_DMARS_CH0_MID                (0x000001FCuL)
#define DMAC01_DMARS_CH1_RID                (0x00030000uL)
#define DMAC01_DMARS_CH1_MID                (0x01FC0000uL)

/* ---- DMAC2-3 ---- */
#define DMAC23_DMARS_CH2_RID                (0x00000003uL)
#define DMAC23_DMARS_CH2_MID                (0x000001FCuL)
#define DMAC23_DMARS_CH3_RID                (0x00030000uL)
#define DMAC23_DMARS_CH3_MID                (0x01FC0000uL)

/* ---- DMAC4-5 ---- */
#define DMAC45_DMARS_CH4_RID                (0x00000003uL)
#define DMAC45_DMARS_CH4_MID                (0x000001FCuL)
#define DMAC45_DMARS_CH5_RID                (0x00030000uL)
#define DMAC45_DMARS_CH5_MID                (0x01FC0000uL)

/* ---- DMAC6-7 ---- */
#define DMAC67_DMARS_CH6_RID                (0x00000003uL)
#define DMAC67_DMARS_CH6_MID                (0x000001FCuL)
#define DMAC67_DMARS_CH7_RID                (0x00030000uL)
#define DMAC67_DMARS_CH7_MID                (0x01FC0000uL)

/* ---- DMAC8-9 ---- */
#define DMAC89_DMARS_CH8_RID                (0x00000003uL)
#define DMAC89_DMARS_CH8_MID                (0x000001FCuL)
#define DMAC89_DMARS_CH9_RID                (0x00030000uL)
#define DMAC89_DMARS_CH9_MID                (0x01FC0000uL)

/* ---- DMAC10-11 ---- */
#define DMAC1011_DMARS_CH10_RID             (0x00000003uL)
#define DMAC1011_DMARS_CH10_MID             (0x000001FCuL)
#define DMAC1011_DMARS_CH11_RID             (0x00030000uL)
#define DMAC1011_DMARS_CH11_MID             (0x01FC0000uL)

/* ---- DMAC12-13 ---- */
#define DMAC1213_DMARS_CH12_RID             (0x00000003uL)
#define DMAC1213_DMARS_CH12_MID             (0x000001FCuL)
#define DMAC1213_DMARS_CH13_RID             (0x00030000uL)
#define DMAC1213_DMARS_CH13_MID             (0x01FC0000uL)

/* ---- DMAC14-15 ---- */
#define DMAC1415_DMARS_CH14_RID             (0x00000003uL)
#define DMAC1415_DMARS_CH14_MID             (0x000001FCuL)
#define DMAC1415_DMARS_CH15_RID             (0x00030000uL)
#define DMAC1415_DMARS_CH15_MID             (0x01FC0000uL)


/* ==== Shift values for IO registers ==== */
/* ---- DMAC0 ---- */
#define DMAC0_N0SA_n_SA_SHIFT               (0u)

#define DMAC0_N0DA_n_DA_SHIFT               (0u)

#define DMAC0_N0TB_n_TB_SHIFT               (0u)

#define DMAC0_N1SA_n_SA_SHIFT               (0u)

#define DMAC0_N1DA_n_DA_SHIFT               (0u)

#define DMAC0_N1TB_n_TB_SHIFT               (0u)

#define DMAC0_CRSA_n_CRSA_SHIFT             (0u)

#define DMAC0_CRDA_n_CRDA_SHIFT             (0u)

#define DMAC0_CRTB_n_CRTB_SHIFT             (0u)

#define DMAC0_CHSTAT_n_EN_SHIFT             (0u)
#define DMAC0_CHSTAT_n_RQST_SHIFT           (1u)
#define DMAC0_CHSTAT_n_TACT_SHIFT           (2u)
#define DMAC0_CHSTAT_n_SUS_SHIFT            (3u)
#define DMAC0_CHSTAT_n_ER_SHIFT             (4u)
#define DMAC0_CHSTAT_n_END_SHIFT            (5u)
#define DMAC0_CHSTAT_n_TC_SHIFT             (6u)
#define DMAC0_CHSTAT_n_SR_SHIFT             (7u)
#define DMAC0_CHSTAT_n_DL_SHIFT             (8u)
#define DMAC0_CHSTAT_n_DW_SHIFT             (9u)
#define DMAC0_CHSTAT_n_DER_SHIFT            (10u)
#define DMAC0_CHSTAT_n_MODE_SHIFT           (11u)
#define DMAC0_CHSTAT_n_INTMSK_SHIFT         (16u)

#define DMAC0_CHCTRL_n_SETEN_SHIFT          (0u)
#define DMAC0_CHCTRL_n_CLREN_SHIFT          (1u)
#define DMAC0_CHCTRL_n_STG_SHIFT            (2u)
#define DMAC0_CHCTRL_n_SWRST_SHIFT          (3u)
#define DMAC0_CHCTRL_n_CLRRQ_SHIFT          (4u)
#define DMAC0_CHCTRL_n_CLREND_SHIFT         (5u)
#define DMAC0_CHCTRL_n_CLRTC_SHIFT          (6u)
#define DMAC0_CHCTRL_n_SETSUS_SHIFT         (8u)
#define DMAC0_CHCTRL_n_CLRSUS_SHIFT         (9u)
#define DMAC0_CHCTRL_n_SETINTMSK_SHIFT      (16u)
#define DMAC0_CHCTRL_n_CLRINTMSK_SHIFT      (17u)

#define DMAC0_CHCFG_n_SEL_SHIFT             (0u)
#define DMAC0_CHCFG_n_REQD_SHIFT            (3u)
#define DMAC0_CHCFG_n_LOEN_SHIFT            (4u)
#define DMAC0_CHCFG_n_HIEN_SHIFT            (5u)
#define DMAC0_CHCFG_n_LVL_SHIFT             (6u)
#define DMAC0_CHCFG_n_AM_SHIFT              (8u)
#define DMAC0_CHCFG_n_SDS_SHIFT             (12u)
#define DMAC0_CHCFG_n_DDS_SHIFT             (16u)
#define DMAC0_CHCFG_n_SAD_SHIFT             (20u)
#define DMAC0_CHCFG_n_DAD_SHIFT             (21u)
#define DMAC0_CHCFG_n_TM_SHIFT              (22u)
#define DMAC0_CHCFG_n_DEM_SHIFT             (24u)
#define DMAC0_CHCFG_n_TCM_SHIFT             (25u)
#define DMAC0_CHCFG_n_SBE_SHIFT             (27u)
#define DMAC0_CHCFG_n_RSEL_SHIFT            (28u)
#define DMAC0_CHCFG_n_RSW_SHIFT             (29u)
#define DMAC0_CHCFG_n_REN_SHIFT             (30u)
#define DMAC0_CHCFG_n_DMS_SHIFT             (31u)

#define DMAC0_CHITVL_n_ITVL_SHIFT           (0u)

#define DMAC0_CHEXT_n_SCA_SHIFT             (4u)
#define DMAC0_CHEXT_n_DCA_SHIFT             (12u)

#define DMAC0_NXLA_n_NXLA_SHIFT             (0u)

#define DMAC0_CRLA_n_CRLA_SHIFT             (0u)

/* ---- DMAC1 ---- */
#define DMAC1_N0SA_n_SA_SHIFT               (0u)

#define DMAC1_N0DA_n_DA_SHIFT               (0u)

#define DMAC1_N0TB_n_TB_SHIFT               (0u)

#define DMAC1_N1SA_n_SA_SHIFT               (0u)

#define DMAC1_N1DA_n_DA_SHIFT               (0u)

#define DMAC1_N1TB_n_TB_SHIFT               (0u)

#define DMAC1_CRSA_n_CRSA_SHIFT             (0u)

#define DMAC1_CRDA_n_CRDA_SHIFT             (0u)

#define DMAC1_CRTB_n_CRTB_SHIFT             (0u)

#define DMAC1_CHSTAT_n_EN_SHIFT             (0u)
#define DMAC1_CHSTAT_n_RQST_SHIFT           (1u)
#define DMAC1_CHSTAT_n_TACT_SHIFT           (2u)
#define DMAC1_CHSTAT_n_SUS_SHIFT            (3u)
#define DMAC1_CHSTAT_n_ER_SHIFT             (4u)
#define DMAC1_CHSTAT_n_END_SHIFT            (5u)
#define DMAC1_CHSTAT_n_TC_SHIFT             (6u)
#define DMAC1_CHSTAT_n_SR_SHIFT             (7u)
#define DMAC1_CHSTAT_n_DL_SHIFT             (8u)
#define DMAC1_CHSTAT_n_DW_SHIFT             (9u)
#define DMAC1_CHSTAT_n_DER_SHIFT            (10u)
#define DMAC1_CHSTAT_n_MODE_SHIFT           (11u)
#define DMAC1_CHSTAT_n_INTMSK_SHIFT         (16u)

#define DMAC1_CHCTRL_n_SETEN_SHIFT          (0u)
#define DMAC1_CHCTRL_n_CLREN_SHIFT          (1u)
#define DMAC1_CHCTRL_n_STG_SHIFT            (2u)
#define DMAC1_CHCTRL_n_SWRST_SHIFT          (3u)
#define DMAC1_CHCTRL_n_CLRRQ_SHIFT          (4u)
#define DMAC1_CHCTRL_n_CLREND_SHIFT         (5u)
#define DMAC1_CHCTRL_n_CLRTC_SHIFT          (6u)
#define DMAC1_CHCTRL_n_SETSUS_SHIFT         (8u)
#define DMAC1_CHCTRL_n_CLRSUS_SHIFT         (9u)
#define DMAC1_CHCTRL_n_SETINTMSK_SHIFT      (16u)
#define DMAC1_CHCTRL_n_CLRINTMSK_SHIFT      (17u)

#define DMAC1_CHCFG_n_SEL_SHIFT             (0u)
#define DMAC1_CHCFG_n_REQD_SHIFT            (3u)
#define DMAC1_CHCFG_n_LOEN_SHIFT            (4u)
#define DMAC1_CHCFG_n_HIEN_SHIFT            (5u)
#define DMAC1_CHCFG_n_LVL_SHIFT             (6u)
#define DMAC1_CHCFG_n_AM_SHIFT              (8u)
#define DMAC1_CHCFG_n_SDS_SHIFT             (12u)
#define DMAC1_CHCFG_n_DDS_SHIFT             (16u)
#define DMAC1_CHCFG_n_SAD_SHIFT             (20u)
#define DMAC1_CHCFG_n_DAD_SHIFT             (21u)
#define DMAC1_CHCFG_n_TM_SHIFT              (22u)
#define DMAC1_CHCFG_n_DEM_SHIFT             (24u)
#define DMAC1_CHCFG_n_TCM_SHIFT             (25u)
#define DMAC1_CHCFG_n_SBE_SHIFT             (27u)
#define DMAC1_CHCFG_n_RSEL_SHIFT            (28u)
#define DMAC1_CHCFG_n_RSW_SHIFT             (29u)
#define DMAC1_CHCFG_n_REN_SHIFT             (30u)
#define DMAC1_CHCFG_n_DMS_SHIFT             (31u)

#define DMAC1_CHITVL_n_ITVL_SHIFT           (0u)

#define DMAC1_CHEXT_n_SCA_SHIFT             (4u)
#define DMAC1_CHEXT_n_DCA_SHIFT             (12u)

#define DMAC1_NXLA_n_NXLA_SHIFT             (0u)

#define DMAC1_CRLA_n_CRLA_SHIFT             (0u)

/* ---- DMAC2 ---- */
#define DMAC2_N0SA_n_SA_SHIFT               (0u)

#define DMAC2_N0DA_n_DA_SHIFT               (0u)

#define DMAC2_N0TB_n_TB_SHIFT               (0u)

#define DMAC2_N1SA_n_SA_SHIFT               (0u)

#define DMAC2_N1DA_n_DA_SHIFT               (0u)

#define DMAC2_N1TB_n_TB_SHIFT               (0u)

#define DMAC2_CRSA_n_CRSA_SHIFT             (0u)

#define DMAC2_CRDA_n_CRDA_SHIFT             (0u)

#define DMAC2_CRTB_n_CRTB_SHIFT             (0u)

#define DMAC2_CHSTAT_n_EN_SHIFT             (0u)
#define DMAC2_CHSTAT_n_RQST_SHIFT           (1u)
#define DMAC2_CHSTAT_n_TACT_SHIFT           (2u)
#define DMAC2_CHSTAT_n_SUS_SHIFT            (3u)
#define DMAC2_CHSTAT_n_ER_SHIFT             (4u)
#define DMAC2_CHSTAT_n_END_SHIFT            (5u)
#define DMAC2_CHSTAT_n_TC_SHIFT             (6u)
#define DMAC2_CHSTAT_n_SR_SHIFT             (7u)
#define DMAC2_CHSTAT_n_DL_SHIFT             (8u)
#define DMAC2_CHSTAT_n_DW_SHIFT             (9u)
#define DMAC2_CHSTAT_n_DER_SHIFT            (10u)
#define DMAC2_CHSTAT_n_MODE_SHIFT           (11u)
#define DMAC2_CHSTAT_n_INTMSK_SHIFT         (16u)

#define DMAC2_CHCTRL_n_SETEN_SHIFT          (0u)
#define DMAC2_CHCTRL_n_CLREN_SHIFT          (1u)
#define DMAC2_CHCTRL_n_STG_SHIFT            (2u)
#define DMAC2_CHCTRL_n_SWRST_SHIFT          (3u)
#define DMAC2_CHCTRL_n_CLRRQ_SHIFT          (4u)
#define DMAC2_CHCTRL_n_CLREND_SHIFT         (5u)
#define DMAC2_CHCTRL_n_CLRTC_SHIFT          (6u)
#define DMAC2_CHCTRL_n_SETSUS_SHIFT         (8u)
#define DMAC2_CHCTRL_n_CLRSUS_SHIFT         (9u)
#define DMAC2_CHCTRL_n_SETINTMSK_SHIFT      (16u)
#define DMAC2_CHCTRL_n_CLRINTMSK_SHIFT      (17u)

#define DMAC2_CHCFG_n_SEL_SHIFT             (0u)
#define DMAC2_CHCFG_n_REQD_SHIFT            (3u)
#define DMAC2_CHCFG_n_LOEN_SHIFT            (4u)
#define DMAC2_CHCFG_n_HIEN_SHIFT            (5u)
#define DMAC2_CHCFG_n_LVL_SHIFT             (6u)
#define DMAC2_CHCFG_n_AM_SHIFT              (8u)
#define DMAC2_CHCFG_n_SDS_SHIFT             (12u)
#define DMAC2_CHCFG_n_DDS_SHIFT             (16u)
#define DMAC2_CHCFG_n_SAD_SHIFT             (20u)
#define DMAC2_CHCFG_n_DAD_SHIFT             (21u)
#define DMAC2_CHCFG_n_TM_SHIFT              (22u)
#define DMAC2_CHCFG_n_DEM_SHIFT             (24u)
#define DMAC2_CHCFG_n_TCM_SHIFT             (25u)
#define DMAC2_CHCFG_n_SBE_SHIFT             (27u)
#define DMAC2_CHCFG_n_RSEL_SHIFT            (28u)
#define DMAC2_CHCFG_n_RSW_SHIFT             (29u)
#define DMAC2_CHCFG_n_REN_SHIFT             (30u)
#define DMAC2_CHCFG_n_DMS_SHIFT             (31u)

#define DMAC2_CHITVL_n_ITVL_SHIFT           (0u)

#define DMAC2_CHEXT_n_SCA_SHIFT             (4u)
#define DMAC2_CHEXT_n_DCA_SHIFT             (12u)

#define DMAC2_NXLA_n_NXLA_SHIFT             (0u)

#define DMAC2_CRLA_n_CRLA_SHIFT             (0u)

/* ---- DMAC3 ---- */
#define DMAC3_N0SA_n_SA_SHIFT               (0u)

#define DMAC3_N0DA_n_DA_SHIFT               (0u)

#define DMAC3_N0TB_n_TB_SHIFT               (0u)

#define DMAC3_N1SA_n_SA_SHIFT               (0u)

#define DMAC3_N1DA_n_DA_SHIFT               (0u)

#define DMAC3_N1TB_n_TB_SHIFT               (0u)

#define DMAC3_CRSA_n_CRSA_SHIFT             (0u)

#define DMAC3_CRDA_n_CRDA_SHIFT             (0u)

#define DMAC3_CRTB_n_CRTB_SHIFT             (0u)

#define DMAC3_CHSTAT_n_EN_SHIFT             (0u)
#define DMAC3_CHSTAT_n_RQST_SHIFT           (1u)
#define DMAC3_CHSTAT_n_TACT_SHIFT           (2u)
#define DMAC3_CHSTAT_n_SUS_SHIFT            (3u)
#define DMAC3_CHSTAT_n_ER_SHIFT             (4u)
#define DMAC3_CHSTAT_n_END_SHIFT            (5u)
#define DMAC3_CHSTAT_n_TC_SHIFT             (6u)
#define DMAC3_CHSTAT_n_SR_SHIFT             (7u)
#define DMAC3_CHSTAT_n_DL_SHIFT             (8u)
#define DMAC3_CHSTAT_n_DW_SHIFT             (9u)
#define DMAC3_CHSTAT_n_DER_SHIFT            (10u)
#define DMAC3_CHSTAT_n_MODE_SHIFT           (11u)
#define DMAC3_CHSTAT_n_INTMSK_SHIFT         (16u)

#define DMAC3_CHCTRL_n_SETEN_SHIFT          (0u)
#define DMAC3_CHCTRL_n_CLREN_SHIFT          (1u)
#define DMAC3_CHCTRL_n_STG_SHIFT            (2u)
#define DMAC3_CHCTRL_n_SWRST_SHIFT          (3u)
#define DMAC3_CHCTRL_n_CLRRQ_SHIFT          (4u)
#define DMAC3_CHCTRL_n_CLREND_SHIFT         (5u)
#define DMAC3_CHCTRL_n_CLRTC_SHIFT          (6u)
#define DMAC3_CHCTRL_n_SETSUS_SHIFT         (8u)
#define DMAC3_CHCTRL_n_CLRSUS_SHIFT         (9u)
#define DMAC3_CHCTRL_n_SETINTMSK_SHIFT      (16u)
#define DMAC3_CHCTRL_n_CLRINTMSK_SHIFT      (17u)

#define DMAC3_CHCFG_n_SEL_SHIFT             (0u)
#define DMAC3_CHCFG_n_REQD_SHIFT            (3u)
#define DMAC3_CHCFG_n_LOEN_SHIFT            (4u)
#define DMAC3_CHCFG_n_HIEN_SHIFT            (5u)
#define DMAC3_CHCFG_n_LVL_SHIFT             (6u)
#define DMAC3_CHCFG_n_AM_SHIFT              (8u)
#define DMAC3_CHCFG_n_SDS_SHIFT             (12u)
#define DMAC3_CHCFG_n_DDS_SHIFT             (16u)
#define DMAC3_CHCFG_n_SAD_SHIFT             (20u)
#define DMAC3_CHCFG_n_DAD_SHIFT             (21u)
#define DMAC3_CHCFG_n_TM_SHIFT              (22u)
#define DMAC3_CHCFG_n_DEM_SHIFT             (24u)
#define DMAC3_CHCFG_n_TCM_SHIFT             (25u)
#define DMAC3_CHCFG_n_SBE_SHIFT             (27u)
#define DMAC3_CHCFG_n_RSEL_SHIFT            (28u)
#define DMAC3_CHCFG_n_RSW_SHIFT             (29u)
#define DMAC3_CHCFG_n_REN_SHIFT             (30u)
#define DMAC3_CHCFG_n_DMS_SHIFT             (31u)

#define DMAC3_CHITVL_n_ITVL_SHIFT           (0u)

#define DMAC3_CHEXT_n_SCA_SHIFT             (4u)
#define DMAC3_CHEXT_n_DCA_SHIFT             (12u)

#define DMAC3_NXLA_n_NXLA_SHIFT             (0u)

#define DMAC3_CRLA_n_CRLA_SHIFT             (0u)

/* ---- DMAC4 ---- */
#define DMAC4_N0SA_n_SA_SHIFT               (0u)

#define DMAC4_N0DA_n_DA_SHIFT               (0u)

#define DMAC4_N0TB_n_TB_SHIFT               (0u)

#define DMAC4_N1SA_n_SA_SHIFT               (0u)

#define DMAC4_N1DA_n_DA_SHIFT               (0u)

#define DMAC4_N1TB_n_TB_SHIFT               (0u)

#define DMAC4_CRSA_n_CRSA_SHIFT             (0u)

#define DMAC4_CRDA_n_CRDA_SHIFT             (0u)

#define DMAC4_CRTB_n_CRTB_SHIFT             (0u)

#define DMAC4_CHSTAT_n_EN_SHIFT             (0u)
#define DMAC4_CHSTAT_n_RQST_SHIFT           (1u)
#define DMAC4_CHSTAT_n_TACT_SHIFT           (2u)
#define DMAC4_CHSTAT_n_SUS_SHIFT            (3u)
#define DMAC4_CHSTAT_n_ER_SHIFT             (4u)
#define DMAC4_CHSTAT_n_END_SHIFT            (5u)
#define DMAC4_CHSTAT_n_TC_SHIFT             (6u)
#define DMAC4_CHSTAT_n_SR_SHIFT             (7u)
#define DMAC4_CHSTAT_n_DL_SHIFT             (8u)
#define DMAC4_CHSTAT_n_DW_SHIFT             (9u)
#define DMAC4_CHSTAT_n_DER_SHIFT            (10u)
#define DMAC4_CHSTAT_n_MODE_SHIFT           (11u)
#define DMAC4_CHSTAT_n_INTMSK_SHIFT         (16u)

#define DMAC4_CHCTRL_n_SETEN_SHIFT          (0u)
#define DMAC4_CHCTRL_n_CLREN_SHIFT          (1u)
#define DMAC4_CHCTRL_n_STG_SHIFT            (2u)
#define DMAC4_CHCTRL_n_SWRST_SHIFT          (3u)
#define DMAC4_CHCTRL_n_CLRRQ_SHIFT          (4u)
#define DMAC4_CHCTRL_n_CLREND_SHIFT         (5u)
#define DMAC4_CHCTRL_n_CLRTC_SHIFT          (6u)
#define DMAC4_CHCTRL_n_SETSUS_SHIFT         (8u)
#define DMAC4_CHCTRL_n_CLRSUS_SHIFT         (9u)
#define DMAC4_CHCTRL_n_SETINTMSK_SHIFT      (16u)
#define DMAC4_CHCTRL_n_CLRINTMSK_SHIFT      (17u)

#define DMAC4_CHCFG_n_SEL_SHIFT             (0u)
#define DMAC4_CHCFG_n_REQD_SHIFT            (3u)
#define DMAC4_CHCFG_n_LOEN_SHIFT            (4u)
#define DMAC4_CHCFG_n_HIEN_SHIFT            (5u)
#define DMAC4_CHCFG_n_LVL_SHIFT             (6u)
#define DMAC4_CHCFG_n_AM_SHIFT              (8u)
#define DMAC4_CHCFG_n_SDS_SHIFT             (12u)
#define DMAC4_CHCFG_n_DDS_SHIFT             (16u)
#define DMAC4_CHCFG_n_SAD_SHIFT             (20u)
#define DMAC4_CHCFG_n_DAD_SHIFT             (21u)
#define DMAC4_CHCFG_n_TM_SHIFT              (22u)
#define DMAC4_CHCFG_n_DEM_SHIFT             (24u)
#define DMAC4_CHCFG_n_TCM_SHIFT             (25u)
#define DMAC4_CHCFG_n_SBE_SHIFT             (27u)
#define DMAC4_CHCFG_n_RSEL_SHIFT            (28u)
#define DMAC4_CHCFG_n_RSW_SHIFT             (29u)
#define DMAC4_CHCFG_n_REN_SHIFT             (30u)
#define DMAC4_CHCFG_n_DMS_SHIFT             (31u)

#define DMAC4_CHITVL_n_ITVL_SHIFT           (0u)

#define DMAC4_CHEXT_n_SCA_SHIFT             (4u)
#define DMAC4_CHEXT_n_DCA_SHIFT             (12u)

#define DMAC4_NXLA_n_NXLA_SHIFT             (0u)

#define DMAC4_CRLA_n_CRLA_SHIFT             (0u)

/* ---- DMAC5 ---- */
#define DMAC5_N0SA_n_SA_SHIFT               (0u)

#define DMAC5_N0DA_n_DA_SHIFT               (0u)

#define DMAC5_N0TB_n_TB_SHIFT               (0u)

#define DMAC5_N1SA_n_SA_SHIFT               (0u)

#define DMAC5_N1DA_n_DA_SHIFT               (0u)

#define DMAC5_N1TB_n_TB_SHIFT               (0u)

#define DMAC5_CRSA_n_CRSA_SHIFT             (0u)

#define DMAC5_CRDA_n_CRDA_SHIFT             (0u)

#define DMAC5_CRTB_n_CRTB_SHIFT             (0u)

#define DMAC5_CHSTAT_n_EN_SHIFT             (0u)
#define DMAC5_CHSTAT_n_RQST_SHIFT           (1u)
#define DMAC5_CHSTAT_n_TACT_SHIFT           (2u)
#define DMAC5_CHSTAT_n_SUS_SHIFT            (3u)
#define DMAC5_CHSTAT_n_ER_SHIFT             (4u)
#define DMAC5_CHSTAT_n_END_SHIFT            (5u)
#define DMAC5_CHSTAT_n_TC_SHIFT             (6u)
#define DMAC5_CHSTAT_n_SR_SHIFT             (7u)
#define DMAC5_CHSTAT_n_DL_SHIFT             (8u)
#define DMAC5_CHSTAT_n_DW_SHIFT             (9u)
#define DMAC5_CHSTAT_n_DER_SHIFT            (10u)
#define DMAC5_CHSTAT_n_MODE_SHIFT           (11u)
#define DMAC5_CHSTAT_n_INTMSK_SHIFT         (16u)

#define DMAC5_CHCTRL_n_SETEN_SHIFT          (0u)
#define DMAC5_CHCTRL_n_CLREN_SHIFT          (1u)
#define DMAC5_CHCTRL_n_STG_SHIFT            (2u)
#define DMAC5_CHCTRL_n_SWRST_SHIFT          (3u)
#define DMAC5_CHCTRL_n_CLRRQ_SHIFT          (4u)
#define DMAC5_CHCTRL_n_CLREND_SHIFT         (5u)
#define DMAC5_CHCTRL_n_CLRTC_SHIFT          (6u)
#define DMAC5_CHCTRL_n_SETSUS_SHIFT         (8u)
#define DMAC5_CHCTRL_n_CLRSUS_SHIFT         (9u)
#define DMAC5_CHCTRL_n_SETINTMSK_SHIFT      (16u)
#define DMAC5_CHCTRL_n_CLRINTMSK_SHIFT      (17u)

#define DMAC5_CHCFG_n_SEL_SHIFT             (0u)
#define DMAC5_CHCFG_n_REQD_SHIFT            (3u)
#define DMAC5_CHCFG_n_LOEN_SHIFT            (4u)
#define DMAC5_CHCFG_n_HIEN_SHIFT            (5u)
#define DMAC5_CHCFG_n_LVL_SHIFT             (6u)
#define DMAC5_CHCFG_n_AM_SHIFT              (8u)
#define DMAC5_CHCFG_n_SDS_SHIFT             (12u)
#define DMAC5_CHCFG_n_DDS_SHIFT             (16u)
#define DMAC5_CHCFG_n_SAD_SHIFT             (20u)
#define DMAC5_CHCFG_n_DAD_SHIFT             (21u)
#define DMAC5_CHCFG_n_TM_SHIFT              (22u)
#define DMAC5_CHCFG_n_DEM_SHIFT             (24u)
#define DMAC5_CHCFG_n_TCM_SHIFT             (25u)
#define DMAC5_CHCFG_n_SBE_SHIFT             (27u)
#define DMAC5_CHCFG_n_RSEL_SHIFT            (28u)
#define DMAC5_CHCFG_n_RSW_SHIFT             (29u)
#define DMAC5_CHCFG_n_REN_SHIFT             (30u)
#define DMAC5_CHCFG_n_DMS_SHIFT             (31u)

#define DMAC5_CHITVL_n_ITVL_SHIFT           (0u)

#define DMAC5_CHEXT_n_SCA_SHIFT             (4u)
#define DMAC5_CHEXT_n_DCA_SHIFT             (12u)

#define DMAC5_NXLA_n_NXLA_SHIFT             (0u)

#define DMAC5_CRLA_n_CRLA_SHIFT             (0u)

/* ---- DMAC6 ---- */
#define DMAC6_N0SA_n_SA_SHIFT               (0u)

#define DMAC6_N0DA_n_DA_SHIFT               (0u)

#define DMAC6_N0TB_n_TB_SHIFT               (0u)

#define DMAC6_N1SA_n_SA_SHIFT               (0u)

#define DMAC6_N1DA_n_DA_SHIFT               (0u)

#define DMAC6_N1TB_n_TB_SHIFT               (0u)

#define DMAC6_CRSA_n_CRSA_SHIFT             (0u)

#define DMAC6_CRDA_n_CRDA_SHIFT             (0u)

#define DMAC6_CRTB_n_CRTB_SHIFT             (0u)

#define DMAC6_CHSTAT_n_EN_SHIFT             (0u)
#define DMAC6_CHSTAT_n_RQST_SHIFT           (1u)
#define DMAC6_CHSTAT_n_TACT_SHIFT           (2u)
#define DMAC6_CHSTAT_n_SUS_SHIFT            (3u)
#define DMAC6_CHSTAT_n_ER_SHIFT             (4u)
#define DMAC6_CHSTAT_n_END_SHIFT            (5u)
#define DMAC6_CHSTAT_n_TC_SHIFT             (6u)
#define DMAC6_CHSTAT_n_SR_SHIFT             (7u)
#define DMAC6_CHSTAT_n_DL_SHIFT             (8u)
#define DMAC6_CHSTAT_n_DW_SHIFT             (9u)
#define DMAC6_CHSTAT_n_DER_SHIFT            (10u)
#define DMAC6_CHSTAT_n_MODE_SHIFT           (11u)
#define DMAC6_CHSTAT_n_INTMSK_SHIFT         (16u)

#define DMAC6_CHCTRL_n_SETEN_SHIFT          (0u)
#define DMAC6_CHCTRL_n_CLREN_SHIFT          (1u)
#define DMAC6_CHCTRL_n_STG_SHIFT            (2u)
#define DMAC6_CHCTRL_n_SWRST_SHIFT          (3u)
#define DMAC6_CHCTRL_n_CLRRQ_SHIFT          (4u)
#define DMAC6_CHCTRL_n_CLREND_SHIFT         (5u)
#define DMAC6_CHCTRL_n_CLRTC_SHIFT          (6u)
#define DMAC6_CHCTRL_n_SETSUS_SHIFT         (8u)
#define DMAC6_CHCTRL_n_CLRSUS_SHIFT         (9u)
#define DMAC6_CHCTRL_n_SETINTMSK_SHIFT      (16u)
#define DMAC6_CHCTRL_n_CLRINTMSK_SHIFT      (17u)

#define DMAC6_CHCFG_n_SEL_SHIFT             (0u)
#define DMAC6_CHCFG_n_REQD_SHIFT            (3u)
#define DMAC6_CHCFG_n_LOEN_SHIFT            (4u)
#define DMAC6_CHCFG_n_HIEN_SHIFT            (5u)
#define DMAC6_CHCFG_n_LVL_SHIFT             (6u)
#define DMAC6_CHCFG_n_AM_SHIFT              (8u)
#define DMAC6_CHCFG_n_SDS_SHIFT             (12u)
#define DMAC6_CHCFG_n_DDS_SHIFT             (16u)
#define DMAC6_CHCFG_n_SAD_SHIFT             (20u)
#define DMAC6_CHCFG_n_DAD_SHIFT             (21u)
#define DMAC6_CHCFG_n_TM_SHIFT              (22u)
#define DMAC6_CHCFG_n_DEM_SHIFT             (24u)
#define DMAC6_CHCFG_n_TCM_SHIFT             (25u)
#define DMAC6_CHCFG_n_SBE_SHIFT             (27u)
#define DMAC6_CHCFG_n_RSEL_SHIFT            (28u)
#define DMAC6_CHCFG_n_RSW_SHIFT             (29u)
#define DMAC6_CHCFG_n_REN_SHIFT             (30u)
#define DMAC6_CHCFG_n_DMS_SHIFT             (31u)

#define DMAC6_CHITVL_n_ITVL_SHIFT           (0u)

#define DMAC6_CHEXT_n_SCA_SHIFT             (4u)
#define DMAC6_CHEXT_n_DCA_SHIFT             (12u)

#define DMAC6_NXLA_n_NXLA_SHIFT             (0u)

#define DMAC6_CRLA_n_CRLA_SHIFT             (0u)

/* ---- DMAC7 ---- */
#define DMAC7_N0SA_n_SA_SHIFT               (0u)

#define DMAC7_N0DA_n_DA_SHIFT               (0u)

#define DMAC7_N0TB_n_TB_SHIFT               (0u)

#define DMAC7_N1SA_n_SA_SHIFT               (0u)

#define DMAC7_N1DA_n_DA_SHIFT               (0u)

#define DMAC7_N1TB_n_TB_SHIFT               (0u)

#define DMAC7_CRSA_n_CRSA_SHIFT             (0u)

#define DMAC7_CRDA_n_CRDA_SHIFT             (0u)

#define DMAC7_CRTB_n_CRTB_SHIFT             (0u)

#define DMAC7_CHSTAT_n_EN_SHIFT             (0u)
#define DMAC7_CHSTAT_n_RQST_SHIFT           (1u)
#define DMAC7_CHSTAT_n_TACT_SHIFT           (2u)
#define DMAC7_CHSTAT_n_SUS_SHIFT            (3u)
#define DMAC7_CHSTAT_n_ER_SHIFT             (4u)
#define DMAC7_CHSTAT_n_END_SHIFT            (5u)
#define DMAC7_CHSTAT_n_TC_SHIFT             (6u)
#define DMAC7_CHSTAT_n_SR_SHIFT             (7u)
#define DMAC7_CHSTAT_n_DL_SHIFT             (8u)
#define DMAC7_CHSTAT_n_DW_SHIFT             (9u)
#define DMAC7_CHSTAT_n_DER_SHIFT            (10u)
#define DMAC7_CHSTAT_n_MODE_SHIFT           (11u)
#define DMAC7_CHSTAT_n_INTMSK_SHIFT         (16u)

#define DMAC7_CHCTRL_n_SETEN_SHIFT          (0u)
#define DMAC7_CHCTRL_n_CLREN_SHIFT          (1u)
#define DMAC7_CHCTRL_n_STG_SHIFT            (2u)
#define DMAC7_CHCTRL_n_SWRST_SHIFT          (3u)
#define DMAC7_CHCTRL_n_CLRRQ_SHIFT          (4u)
#define DMAC7_CHCTRL_n_CLREND_SHIFT         (5u)
#define DMAC7_CHCTRL_n_CLRTC_SHIFT          (6u)
#define DMAC7_CHCTRL_n_SETSUS_SHIFT         (8u)
#define DMAC7_CHCTRL_n_CLRSUS_SHIFT         (9u)
#define DMAC7_CHCTRL_n_SETINTMSK_SHIFT      (16u)
#define DMAC7_CHCTRL_n_CLRINTMSK_SHIFT      (17u)

#define DMAC7_CHCFG_n_SEL_SHIFT             (0u)
#define DMAC7_CHCFG_n_REQD_SHIFT            (3u)
#define DMAC7_CHCFG_n_LOEN_SHIFT            (4u)
#define DMAC7_CHCFG_n_HIEN_SHIFT            (5u)
#define DMAC7_CHCFG_n_LVL_SHIFT             (6u)
#define DMAC7_CHCFG_n_AM_SHIFT              (8u)
#define DMAC7_CHCFG_n_SDS_SHIFT             (12u)
#define DMAC7_CHCFG_n_DDS_SHIFT             (16u)
#define DMAC7_CHCFG_n_SAD_SHIFT             (20u)
#define DMAC7_CHCFG_n_DAD_SHIFT             (21u)
#define DMAC7_CHCFG_n_TM_SHIFT              (22u)
#define DMAC7_CHCFG_n_DEM_SHIFT             (24u)
#define DMAC7_CHCFG_n_TCM_SHIFT             (25u)
#define DMAC7_CHCFG_n_SBE_SHIFT             (27u)
#define DMAC7_CHCFG_n_RSEL_SHIFT            (28u)
#define DMAC7_CHCFG_n_RSW_SHIFT             (29u)
#define DMAC7_CHCFG_n_REN_SHIFT             (30u)
#define DMAC7_CHCFG_n_DMS_SHIFT             (31u)

#define DMAC7_CHITVL_n_ITVL_SHIFT           (0u)

#define DMAC7_CHEXT_n_SCA_SHIFT             (4u)
#define DMAC7_CHEXT_n_DCA_SHIFT             (12u)

#define DMAC7_NXLA_n_NXLA_SHIFT             (0u)

#define DMAC7_CRLA_n_CRLA_SHIFT             (0u)

/* ---- DMAC0-7 ---- */
#define DMAC07_DCTRL_0_7_PR_SHIFT           (0u)
#define DMAC07_DCTRL_0_7_LVINT_SHIFT        (1u)
#define DMAC07_DCTRL_0_7_LDCA_SHIFT         (2u)
#define DMAC07_DCTRL_0_7_LWCA_SHIFT         (6u)

#define DMAC07_DSTAT_EN_0_7_EN0_SHIFT       (0u)
#define DMAC07_DSTAT_EN_0_7_EN1_SHIFT       (1u)
#define DMAC07_DSTAT_EN_0_7_EN2_SHIFT       (2u)
#define DMAC07_DSTAT_EN_0_7_EN3_SHIFT       (3u)
#define DMAC07_DSTAT_EN_0_7_EN4_SHIFT       (4u)
#define DMAC07_DSTAT_EN_0_7_EN5_SHIFT       (5u)
#define DMAC07_DSTAT_EN_0_7_EN6_SHIFT       (6u)
#define DMAC07_DSTAT_EN_0_7_EN7_SHIFT       (7u)

#define DMAC07_DSTAT_ER_0_7_ER0_SHIFT       (0u)
#define DMAC07_DSTAT_ER_0_7_ER1_SHIFT       (1u)
#define DMAC07_DSTAT_ER_0_7_ER2_SHIFT       (2u)
#define DMAC07_DSTAT_ER_0_7_ER3_SHIFT       (3u)
#define DMAC07_DSTAT_ER_0_7_ER4_SHIFT       (4u)
#define DMAC07_DSTAT_ER_0_7_ER5_SHIFT       (5u)
#define DMAC07_DSTAT_ER_0_7_ER6_SHIFT       (6u)
#define DMAC07_DSTAT_ER_0_7_ER7_SHIFT       (7u)

#define DMAC07_DSTAT_END_0_7_END0_SHIFT     (0u)
#define DMAC07_DSTAT_END_0_7_END1_SHIFT     (1u)
#define DMAC07_DSTAT_END_0_7_END2_SHIFT     (2u)
#define DMAC07_DSTAT_END_0_7_END3_SHIFT     (3u)
#define DMAC07_DSTAT_END_0_7_END4_SHIFT     (4u)
#define DMAC07_DSTAT_END_0_7_END5_SHIFT     (5u)
#define DMAC07_DSTAT_END_0_7_END6_SHIFT     (6u)
#define DMAC07_DSTAT_END_0_7_END7_SHIFT     (7u)

#define DMAC07_DSTAT_TC_0_7_TC0_SHIFT       (0u)
#define DMAC07_DSTAT_TC_0_7_TC1_SHIFT       (1u)
#define DMAC07_DSTAT_TC_0_7_TC2_SHIFT       (2u)
#define DMAC07_DSTAT_TC_0_7_TC3_SHIFT       (3u)
#define DMAC07_DSTAT_TC_0_7_TC4_SHIFT       (4u)
#define DMAC07_DSTAT_TC_0_7_TC5_SHIFT       (5u)
#define DMAC07_DSTAT_TC_0_7_TC6_SHIFT       (6u)
#define DMAC07_DSTAT_TC_0_7_TC7_SHIFT       (7u)

#define DMAC07_DSTAT_SUS_0_7_SUS0_SHIFT     (0u)
#define DMAC07_DSTAT_SUS_0_7_SUS1_SHIFT     (1u)
#define DMAC07_DSTAT_SUS_0_7_SUS2_SHIFT     (2u)
#define DMAC07_DSTAT_SUS_0_7_SUS3_SHIFT     (3u)
#define DMAC07_DSTAT_SUS_0_7_SUS4_SHIFT     (4u)
#define DMAC07_DSTAT_SUS_0_7_SUS5_SHIFT     (5u)
#define DMAC07_DSTAT_SUS_0_7_SUS6_SHIFT     (6u)
#define DMAC07_DSTAT_SUS_0_7_SUS7_SHIFT     (7u)

/* ---- DMAC8 ---- */
#define DMAC8_N0SA_n_SA_SHIFT               (0u)

#define DMAC8_N0DA_n_DA_SHIFT               (0u)

#define DMAC8_N0TB_n_TB_SHIFT               (0u)

#define DMAC8_N1SA_n_SA_SHIFT               (0u)

#define DMAC8_N1DA_n_DA_SHIFT               (0u)

#define DMAC8_N1TB_n_TB_SHIFT               (0u)

#define DMAC8_CRSA_n_CRSA_SHIFT             (0u)

#define DMAC8_CRDA_n_CRDA_SHIFT             (0u)

#define DMAC8_CRTB_n_CRTB_SHIFT             (0u)

#define DMAC8_CHSTAT_n_EN_SHIFT             (0u)
#define DMAC8_CHSTAT_n_RQST_SHIFT           (1u)
#define DMAC8_CHSTAT_n_TACT_SHIFT           (2u)
#define DMAC8_CHSTAT_n_SUS_SHIFT            (3u)
#define DMAC8_CHSTAT_n_ER_SHIFT             (4u)
#define DMAC8_CHSTAT_n_END_SHIFT            (5u)
#define DMAC8_CHSTAT_n_TC_SHIFT             (6u)
#define DMAC8_CHSTAT_n_SR_SHIFT             (7u)
#define DMAC8_CHSTAT_n_DL_SHIFT             (8u)
#define DMAC8_CHSTAT_n_DW_SHIFT             (9u)
#define DMAC8_CHSTAT_n_DER_SHIFT            (10u)
#define DMAC8_CHSTAT_n_MODE_SHIFT           (11u)
#define DMAC8_CHSTAT_n_INTMSK_SHIFT         (16u)

#define DMAC8_CHCTRL_n_SETEN_SHIFT          (0u)
#define DMAC8_CHCTRL_n_CLREN_SHIFT          (1u)
#define DMAC8_CHCTRL_n_STG_SHIFT            (2u)
#define DMAC8_CHCTRL_n_SWRST_SHIFT          (3u)
#define DMAC8_CHCTRL_n_CLRRQ_SHIFT          (4u)
#define DMAC8_CHCTRL_n_CLREND_SHIFT         (5u)
#define DMAC8_CHCTRL_n_CLRTC_SHIFT          (6u)
#define DMAC8_CHCTRL_n_SETSUS_SHIFT         (8u)
#define DMAC8_CHCTRL_n_CLRSUS_SHIFT         (9u)
#define DMAC8_CHCTRL_n_SETINTMSK_SHIFT      (16u)
#define DMAC8_CHCTRL_n_CLRINTMSK_SHIFT      (17u)

#define DMAC8_CHCFG_n_SEL_SHIFT             (0u)
#define DMAC8_CHCFG_n_REQD_SHIFT            (3u)
#define DMAC8_CHCFG_n_LOEN_SHIFT            (4u)
#define DMAC8_CHCFG_n_HIEN_SHIFT            (5u)
#define DMAC8_CHCFG_n_LVL_SHIFT             (6u)
#define DMAC8_CHCFG_n_AM_SHIFT              (8u)
#define DMAC8_CHCFG_n_SDS_SHIFT             (12u)
#define DMAC8_CHCFG_n_DDS_SHIFT             (16u)
#define DMAC8_CHCFG_n_SAD_SHIFT             (20u)
#define DMAC8_CHCFG_n_DAD_SHIFT             (21u)
#define DMAC8_CHCFG_n_TM_SHIFT              (22u)
#define DMAC8_CHCFG_n_DEM_SHIFT             (24u)
#define DMAC8_CHCFG_n_TCM_SHIFT             (25u)
#define DMAC8_CHCFG_n_SBE_SHIFT             (27u)
#define DMAC8_CHCFG_n_RSEL_SHIFT            (28u)
#define DMAC8_CHCFG_n_RSW_SHIFT             (29u)
#define DMAC8_CHCFG_n_REN_SHIFT             (30u)
#define DMAC8_CHCFG_n_DMS_SHIFT             (31u)

#define DMAC8_CHITVL_n_ITVL_SHIFT           (0u)

#define DMAC8_CHEXT_n_SCA_SHIFT             (4u)
#define DMAC8_CHEXT_n_DCA_SHIFT             (12u)

#define DMAC8_NXLA_n_NXLA_SHIFT             (0u)

#define DMAC8_CRLA_n_CRLA_SHIFT             (0u)

/* ---- DMAC9 ---- */
#define DMAC9_N0SA_n_SA_SHIFT               (0u)

#define DMAC9_N0DA_n_DA_SHIFT               (0u)

#define DMAC9_N0TB_n_TB_SHIFT               (0u)

#define DMAC9_N1SA_n_SA_SHIFT               (0u)

#define DMAC9_N1DA_n_DA_SHIFT               (0u)

#define DMAC9_N1TB_n_TB_SHIFT               (0u)

#define DMAC9_CRSA_n_CRSA_SHIFT             (0u)

#define DMAC9_CRDA_n_CRDA_SHIFT             (0u)

#define DMAC9_CRTB_n_CRTB_SHIFT             (0u)

#define DMAC9_CHSTAT_n_EN_SHIFT             (0u)
#define DMAC9_CHSTAT_n_RQST_SHIFT           (1u)
#define DMAC9_CHSTAT_n_TACT_SHIFT           (2u)
#define DMAC9_CHSTAT_n_SUS_SHIFT            (3u)
#define DMAC9_CHSTAT_n_ER_SHIFT             (4u)
#define DMAC9_CHSTAT_n_END_SHIFT            (5u)
#define DMAC9_CHSTAT_n_TC_SHIFT             (6u)
#define DMAC9_CHSTAT_n_SR_SHIFT             (7u)
#define DMAC9_CHSTAT_n_DL_SHIFT             (8u)
#define DMAC9_CHSTAT_n_DW_SHIFT             (9u)
#define DMAC9_CHSTAT_n_DER_SHIFT            (10u)
#define DMAC9_CHSTAT_n_MODE_SHIFT           (11u)
#define DMAC9_CHSTAT_n_INTMSK_SHIFT         (16u)

#define DMAC9_CHCTRL_n_SETEN_SHIFT          (0u)
#define DMAC9_CHCTRL_n_CLREN_SHIFT          (1u)
#define DMAC9_CHCTRL_n_STG_SHIFT            (2u)
#define DMAC9_CHCTRL_n_SWRST_SHIFT          (3u)
#define DMAC9_CHCTRL_n_CLRRQ_SHIFT          (4u)
#define DMAC9_CHCTRL_n_CLREND_SHIFT         (5u)
#define DMAC9_CHCTRL_n_CLRTC_SHIFT          (6u)
#define DMAC9_CHCTRL_n_SETSUS_SHIFT         (8u)
#define DMAC9_CHCTRL_n_CLRSUS_SHIFT         (9u)
#define DMAC9_CHCTRL_n_SETINTMSK_SHIFT      (16u)
#define DMAC9_CHCTRL_n_CLRINTMSK_SHIFT      (17u)

#define DMAC9_CHCFG_n_SEL_SHIFT             (0u)
#define DMAC9_CHCFG_n_REQD_SHIFT            (3u)
#define DMAC9_CHCFG_n_LOEN_SHIFT            (4u)
#define DMAC9_CHCFG_n_HIEN_SHIFT            (5u)
#define DMAC9_CHCFG_n_LVL_SHIFT             (6u)
#define DMAC9_CHCFG_n_AM_SHIFT              (8u)
#define DMAC9_CHCFG_n_SDS_SHIFT             (12u)
#define DMAC9_CHCFG_n_DDS_SHIFT             (16u)
#define DMAC9_CHCFG_n_SAD_SHIFT             (20u)
#define DMAC9_CHCFG_n_DAD_SHIFT             (21u)
#define DMAC9_CHCFG_n_TM_SHIFT              (22u)
#define DMAC9_CHCFG_n_DEM_SHIFT             (24u)
#define DMAC9_CHCFG_n_TCM_SHIFT             (25u)
#define DMAC9_CHCFG_n_SBE_SHIFT             (27u)
#define DMAC9_CHCFG_n_RSEL_SHIFT            (28u)
#define DMAC9_CHCFG_n_RSW_SHIFT             (29u)
#define DMAC9_CHCFG_n_REN_SHIFT             (30u)
#define DMAC9_CHCFG_n_DMS_SHIFT             (31u)

#define DMAC9_CHITVL_n_ITVL_SHIFT           (0u)

#define DMAC9_CHEXT_n_SCA_SHIFT             (4u)
#define DMAC9_CHEXT_n_DCA_SHIFT             (12u)

#define DMAC9_NXLA_n_NXLA_SHIFT             (0u)

#define DMAC9_CRLA_n_CRLA_SHIFT             (0u)

/* ---- DMAC10 ---- */
#define DMAC10_N0SA_n_SA_SHIFT              (0u)

#define DMAC10_N0DA_n_DA_SHIFT              (0u)

#define DMAC10_N0TB_n_TB_SHIFT              (0u)

#define DMAC10_N1SA_n_SA_SHIFT              (0u)

#define DMAC10_N1DA_n_DA_SHIFT              (0u)

#define DMAC10_N1TB_n_TB_SHIFT              (0u)

#define DMAC10_CRSA_n_CRSA_SHIFT            (0u)

#define DMAC10_CRDA_n_CRDA_SHIFT            (0u)

#define DMAC10_CRTB_n_CRTB_SHIFT            (0u)

#define DMAC10_CHSTAT_n_EN_SHIFT            (0u)
#define DMAC10_CHSTAT_n_RQST_SHIFT          (1u)
#define DMAC10_CHSTAT_n_TACT_SHIFT          (2u)
#define DMAC10_CHSTAT_n_SUS_SHIFT           (3u)
#define DMAC10_CHSTAT_n_ER_SHIFT            (4u)
#define DMAC10_CHSTAT_n_END_SHIFT           (5u)
#define DMAC10_CHSTAT_n_TC_SHIFT            (6u)
#define DMAC10_CHSTAT_n_SR_SHIFT            (7u)
#define DMAC10_CHSTAT_n_DL_SHIFT            (8u)
#define DMAC10_CHSTAT_n_DW_SHIFT            (9u)
#define DMAC10_CHSTAT_n_DER_SHIFT           (10u)
#define DMAC10_CHSTAT_n_MODE_SHIFT          (11u)
#define DMAC10_CHSTAT_n_INTMSK_SHIFT        (16u)

#define DMAC10_CHCTRL_n_SETEN_SHIFT         (0u)
#define DMAC10_CHCTRL_n_CLREN_SHIFT         (1u)
#define DMAC10_CHCTRL_n_STG_SHIFT           (2u)
#define DMAC10_CHCTRL_n_SWRST_SHIFT         (3u)
#define DMAC10_CHCTRL_n_CLRRQ_SHIFT         (4u)
#define DMAC10_CHCTRL_n_CLREND_SHIFT        (5u)
#define DMAC10_CHCTRL_n_CLRTC_SHIFT         (6u)
#define DMAC10_CHCTRL_n_SETSUS_SHIFT        (8u)
#define DMAC10_CHCTRL_n_CLRSUS_SHIFT        (9u)
#define DMAC10_CHCTRL_n_SETINTMSK_SHIFT     (16u)
#define DMAC10_CHCTRL_n_CLRINTMSK_SHIFT     (17u)

#define DMAC10_CHCFG_n_SEL_SHIFT            (0u)
#define DMAC10_CHCFG_n_REQD_SHIFT           (3u)
#define DMAC10_CHCFG_n_LOEN_SHIFT           (4u)
#define DMAC10_CHCFG_n_HIEN_SHIFT           (5u)
#define DMAC10_CHCFG_n_LVL_SHIFT            (6u)
#define DMAC10_CHCFG_n_AM_SHIFT             (8u)
#define DMAC10_CHCFG_n_SDS_SHIFT            (12u)
#define DMAC10_CHCFG_n_DDS_SHIFT            (16u)
#define DMAC10_CHCFG_n_SAD_SHIFT            (20u)
#define DMAC10_CHCFG_n_DAD_SHIFT            (21u)
#define DMAC10_CHCFG_n_TM_SHIFT             (22u)
#define DMAC10_CHCFG_n_DEM_SHIFT            (24u)
#define DMAC10_CHCFG_n_TCM_SHIFT            (25u)
#define DMAC10_CHCFG_n_SBE_SHIFT            (27u)
#define DMAC10_CHCFG_n_RSEL_SHIFT           (28u)
#define DMAC10_CHCFG_n_RSW_SHIFT            (29u)
#define DMAC10_CHCFG_n_REN_SHIFT            (30u)
#define DMAC10_CHCFG_n_DMS_SHIFT            (31u)

#define DMAC10_CHITVL_n_ITVL_SHIFT          (0u)

#define DMAC10_CHEXT_n_SCA_SHIFT            (4u)
#define DMAC10_CHEXT_n_DCA_SHIFT            (12u)

#define DMAC10_NXLA_n_NXLA_SHIFT            (0u)

#define DMAC10_CRLA_n_CRLA_SHIFT            (0u)

/* ---- DMAC11 ---- */
#define DMAC11_N0SA_n_SA_SHIFT              (0u)

#define DMAC11_N0DA_n_DA_SHIFT              (0u)

#define DMAC11_N0TB_n_TB_SHIFT              (0u)

#define DMAC11_N1SA_n_SA_SHIFT              (0u)

#define DMAC11_N1DA_n_DA_SHIFT              (0u)

#define DMAC11_N1TB_n_TB_SHIFT              (0u)

#define DMAC11_CRSA_n_CRSA_SHIFT            (0u)

#define DMAC11_CRDA_n_CRDA_SHIFT            (0u)

#define DMAC11_CRTB_n_CRTB_SHIFT            (0u)

#define DMAC11_CHSTAT_n_EN_SHIFT            (0u)
#define DMAC11_CHSTAT_n_RQST_SHIFT          (1u)
#define DMAC11_CHSTAT_n_TACT_SHIFT          (2u)
#define DMAC11_CHSTAT_n_SUS_SHIFT           (3u)
#define DMAC11_CHSTAT_n_ER_SHIFT            (4u)
#define DMAC11_CHSTAT_n_END_SHIFT           (5u)
#define DMAC11_CHSTAT_n_TC_SHIFT            (6u)
#define DMAC11_CHSTAT_n_SR_SHIFT            (7u)
#define DMAC11_CHSTAT_n_DL_SHIFT            (8u)
#define DMAC11_CHSTAT_n_DW_SHIFT            (9u)
#define DMAC11_CHSTAT_n_DER_SHIFT           (10u)
#define DMAC11_CHSTAT_n_MODE_SHIFT          (11u)
#define DMAC11_CHSTAT_n_INTMSK_SHIFT        (16u)

#define DMAC11_CHCTRL_n_SETEN_SHIFT         (0u)
#define DMAC11_CHCTRL_n_CLREN_SHIFT         (1u)
#define DMAC11_CHCTRL_n_STG_SHIFT           (2u)
#define DMAC11_CHCTRL_n_SWRST_SHIFT         (3u)
#define DMAC11_CHCTRL_n_CLRRQ_SHIFT         (4u)
#define DMAC11_CHCTRL_n_CLREND_SHIFT        (5u)
#define DMAC11_CHCTRL_n_CLRTC_SHIFT         (6u)
#define DMAC11_CHCTRL_n_SETSUS_SHIFT        (8u)
#define DMAC11_CHCTRL_n_CLRSUS_SHIFT        (9u)
#define DMAC11_CHCTRL_n_SETINTMSK_SHIFT     (16u)
#define DMAC11_CHCTRL_n_CLRINTMSK_SHIFT     (17u)

#define DMAC11_CHCFG_n_SEL_SHIFT            (0u)
#define DMAC11_CHCFG_n_REQD_SHIFT           (3u)
#define DMAC11_CHCFG_n_LOEN_SHIFT           (4u)
#define DMAC11_CHCFG_n_HIEN_SHIFT           (5u)
#define DMAC11_CHCFG_n_LVL_SHIFT            (6u)
#define DMAC11_CHCFG_n_AM_SHIFT             (8u)
#define DMAC11_CHCFG_n_SDS_SHIFT            (12u)
#define DMAC11_CHCFG_n_DDS_SHIFT            (16u)
#define DMAC11_CHCFG_n_SAD_SHIFT            (20u)
#define DMAC11_CHCFG_n_DAD_SHIFT            (21u)
#define DMAC11_CHCFG_n_TM_SHIFT             (22u)
#define DMAC11_CHCFG_n_DEM_SHIFT            (24u)
#define DMAC11_CHCFG_n_TCM_SHIFT            (25u)
#define DMAC11_CHCFG_n_SBE_SHIFT            (27u)
#define DMAC11_CHCFG_n_RSEL_SHIFT           (28u)
#define DMAC11_CHCFG_n_RSW_SHIFT            (29u)
#define DMAC11_CHCFG_n_REN_SHIFT            (30u)
#define DMAC11_CHCFG_n_DMS_SHIFT            (31u)

#define DMAC11_CHITVL_n_ITVL_SHIFT          (0u)

#define DMAC11_CHEXT_n_SCA_SHIFT            (4u)
#define DMAC11_CHEXT_n_DCA_SHIFT            (12u)

#define DMAC11_NXLA_n_NXLA_SHIFT            (0u)

#define DMAC11_CRLA_n_CRLA_SHIFT            (0u)

/* ---- DMAC12 ---- */
#define DMAC12_N0SA_n_SA_SHIFT              (0u)

#define DMAC12_N0DA_n_DA_SHIFT              (0u)

#define DMAC12_N0TB_n_TB_SHIFT              (0u)

#define DMAC12_N1SA_n_SA_SHIFT              (0u)

#define DMAC12_N1DA_n_DA_SHIFT              (0u)

#define DMAC12_N1TB_n_TB_SHIFT              (0u)

#define DMAC12_CRSA_n_CRSA_SHIFT            (0u)

#define DMAC12_CRDA_n_CRDA_SHIFT            (0u)

#define DMAC12_CRTB_n_CRTB_SHIFT            (0u)

#define DMAC12_CHSTAT_n_EN_SHIFT            (0u)
#define DMAC12_CHSTAT_n_RQST_SHIFT          (1u)
#define DMAC12_CHSTAT_n_TACT_SHIFT          (2u)
#define DMAC12_CHSTAT_n_SUS_SHIFT           (3u)
#define DMAC12_CHSTAT_n_ER_SHIFT            (4u)
#define DMAC12_CHSTAT_n_END_SHIFT           (5u)
#define DMAC12_CHSTAT_n_TC_SHIFT            (6u)
#define DMAC12_CHSTAT_n_SR_SHIFT            (7u)
#define DMAC12_CHSTAT_n_DL_SHIFT            (8u)
#define DMAC12_CHSTAT_n_DW_SHIFT            (9u)
#define DMAC12_CHSTAT_n_DER_SHIFT           (10u)
#define DMAC12_CHSTAT_n_MODE_SHIFT          (11u)
#define DMAC12_CHSTAT_n_INTMSK_SHIFT        (16u)

#define DMAC12_CHCTRL_n_SETEN_SHIFT         (0u)
#define DMAC12_CHCTRL_n_CLREN_SHIFT         (1u)
#define DMAC12_CHCTRL_n_STG_SHIFT           (2u)
#define DMAC12_CHCTRL_n_SWRST_SHIFT         (3u)
#define DMAC12_CHCTRL_n_CLRRQ_SHIFT         (4u)
#define DMAC12_CHCTRL_n_CLREND_SHIFT        (5u)
#define DMAC12_CHCTRL_n_CLRTC_SHIFT         (6u)
#define DMAC12_CHCTRL_n_SETSUS_SHIFT        (8u)
#define DMAC12_CHCTRL_n_CLRSUS_SHIFT        (9u)
#define DMAC12_CHCTRL_n_SETINTMSK_SHIFT     (16u)
#define DMAC12_CHCTRL_n_CLRINTMSK_SHIFT     (17u)

#define DMAC12_CHCFG_n_SEL_SHIFT            (0u)
#define DMAC12_CHCFG_n_REQD_SHIFT           (3u)
#define DMAC12_CHCFG_n_LOEN_SHIFT           (4u)
#define DMAC12_CHCFG_n_HIEN_SHIFT           (5u)
#define DMAC12_CHCFG_n_LVL_SHIFT            (6u)
#define DMAC12_CHCFG_n_AM_SHIFT             (8u)
#define DMAC12_CHCFG_n_SDS_SHIFT            (12u)
#define DMAC12_CHCFG_n_DDS_SHIFT            (16u)
#define DMAC12_CHCFG_n_SAD_SHIFT            (20u)
#define DMAC12_CHCFG_n_DAD_SHIFT            (21u)
#define DMAC12_CHCFG_n_TM_SHIFT             (22u)
#define DMAC12_CHCFG_n_DEM_SHIFT            (24u)
#define DMAC12_CHCFG_n_TCM_SHIFT            (25u)
#define DMAC12_CHCFG_n_SBE_SHIFT            (27u)
#define DMAC12_CHCFG_n_RSEL_SHIFT           (28u)
#define DMAC12_CHCFG_n_RSW_SHIFT            (29u)
#define DMAC12_CHCFG_n_REN_SHIFT            (30u)
#define DMAC12_CHCFG_n_DMS_SHIFT            (31u)

#define DMAC12_CHITVL_n_ITVL_SHIFT          (0u)

#define DMAC12_CHEXT_n_SCA_SHIFT            (4u)
#define DMAC12_CHEXT_n_DCA_SHIFT            (12u)

#define DMAC12_NXLA_n_NXLA_SHIFT            (0u)

#define DMAC12_CRLA_n_CRLA_SHIFT            (0u)

/* ---- DMAC13 ---- */
#define DMAC13_N0SA_n_SA_SHIFT              (0u)

#define DMAC13_N0DA_n_DA_SHIFT              (0u)

#define DMAC13_N0TB_n_TB_SHIFT              (0u)

#define DMAC13_N1SA_n_SA_SHIFT              (0u)

#define DMAC13_N1DA_n_DA_SHIFT              (0u)

#define DMAC13_N1TB_n_TB_SHIFT              (0u)

#define DMAC13_CRSA_n_CRSA_SHIFT            (0u)

#define DMAC13_CRDA_n_CRDA_SHIFT            (0u)

#define DMAC13_CRTB_n_CRTB_SHIFT            (0u)

#define DMAC13_CHSTAT_n_EN_SHIFT            (0u)
#define DMAC13_CHSTAT_n_RQST_SHIFT          (1u)
#define DMAC13_CHSTAT_n_TACT_SHIFT          (2u)
#define DMAC13_CHSTAT_n_SUS_SHIFT           (3u)
#define DMAC13_CHSTAT_n_ER_SHIFT            (4u)
#define DMAC13_CHSTAT_n_END_SHIFT           (5u)
#define DMAC13_CHSTAT_n_TC_SHIFT            (6u)
#define DMAC13_CHSTAT_n_SR_SHIFT            (7u)
#define DMAC13_CHSTAT_n_DL_SHIFT            (8u)
#define DMAC13_CHSTAT_n_DW_SHIFT            (9u)
#define DMAC13_CHSTAT_n_DER_SHIFT           (10u)
#define DMAC13_CHSTAT_n_MODE_SHIFT          (11u)
#define DMAC13_CHSTAT_n_INTMSK_SHIFT        (16u)

#define DMAC13_CHCTRL_n_SETEN_SHIFT         (0u)
#define DMAC13_CHCTRL_n_CLREN_SHIFT         (1u)
#define DMAC13_CHCTRL_n_STG_SHIFT           (2u)
#define DMAC13_CHCTRL_n_SWRST_SHIFT         (3u)
#define DMAC13_CHCTRL_n_CLRRQ_SHIFT         (4u)
#define DMAC13_CHCTRL_n_CLREND_SHIFT        (5u)
#define DMAC13_CHCTRL_n_CLRTC_SHIFT         (6u)
#define DMAC13_CHCTRL_n_SETSUS_SHIFT        (8u)
#define DMAC13_CHCTRL_n_CLRSUS_SHIFT        (9u)
#define DMAC13_CHCTRL_n_SETINTMSK_SHIFT     (16u)
#define DMAC13_CHCTRL_n_CLRINTMSK_SHIFT     (17u)

#define DMAC13_CHCFG_n_SEL_SHIFT            (0u)
#define DMAC13_CHCFG_n_REQD_SHIFT           (3u)
#define DMAC13_CHCFG_n_LOEN_SHIFT           (4u)
#define DMAC13_CHCFG_n_HIEN_SHIFT           (5u)
#define DMAC13_CHCFG_n_LVL_SHIFT            (6u)
#define DMAC13_CHCFG_n_AM_SHIFT             (8u)
#define DMAC13_CHCFG_n_SDS_SHIFT            (12u)
#define DMAC13_CHCFG_n_DDS_SHIFT            (16u)
#define DMAC13_CHCFG_n_SAD_SHIFT            (20u)
#define DMAC13_CHCFG_n_DAD_SHIFT            (21u)
#define DMAC13_CHCFG_n_TM_SHIFT             (22u)
#define DMAC13_CHCFG_n_DEM_SHIFT            (24u)
#define DMAC13_CHCFG_n_TCM_SHIFT            (25u)
#define DMAC13_CHCFG_n_SBE_SHIFT            (27u)
#define DMAC13_CHCFG_n_RSEL_SHIFT           (28u)
#define DMAC13_CHCFG_n_RSW_SHIFT            (29u)
#define DMAC13_CHCFG_n_REN_SHIFT            (30u)
#define DMAC13_CHCFG_n_DMS_SHIFT            (31u)

#define DMAC13_CHITVL_n_ITVL_SHIFT          (0u)

#define DMAC13_CHEXT_n_SCA_SHIFT            (4u)
#define DMAC13_CHEXT_n_DCA_SHIFT            (12u)

#define DMAC13_NXLA_n_NXLA_SHIFT            (0u)

#define DMAC13_CRLA_n_CRLA_SHIFT            (0u)

/* ---- DMAC14 ---- */
#define DMAC14_N0SA_n_SA_SHIFT              (0u)

#define DMAC14_N0DA_n_DA_SHIFT              (0u)

#define DMAC14_N0TB_n_TB_SHIFT              (0u)

#define DMAC14_N1SA_n_SA_SHIFT              (0u)

#define DMAC14_N1DA_n_DA_SHIFT              (0u)

#define DMAC14_N1TB_n_TB_SHIFT              (0u)

#define DMAC14_CRSA_n_CRSA_SHIFT            (0u)

#define DMAC14_CRDA_n_CRDA_SHIFT            (0u)

#define DMAC14_CRTB_n_CRTB_SHIFT            (0u)

#define DMAC14_CHSTAT_n_EN_SHIFT            (0u)
#define DMAC14_CHSTAT_n_RQST_SHIFT          (1u)
#define DMAC14_CHSTAT_n_TACT_SHIFT          (2u)
#define DMAC14_CHSTAT_n_SUS_SHIFT           (3u)
#define DMAC14_CHSTAT_n_ER_SHIFT            (4u)
#define DMAC14_CHSTAT_n_END_SHIFT           (5u)
#define DMAC14_CHSTAT_n_TC_SHIFT            (6u)
#define DMAC14_CHSTAT_n_SR_SHIFT            (7u)
#define DMAC14_CHSTAT_n_DL_SHIFT            (8u)
#define DMAC14_CHSTAT_n_DW_SHIFT            (9u)
#define DMAC14_CHSTAT_n_DER_SHIFT           (10u)
#define DMAC14_CHSTAT_n_MODE_SHIFT          (11u)
#define DMAC14_CHSTAT_n_INTMSK_SHIFT        (16u)

#define DMAC14_CHCTRL_n_SETEN_SHIFT         (0u)
#define DMAC14_CHCTRL_n_CLREN_SHIFT         (1u)
#define DMAC14_CHCTRL_n_STG_SHIFT           (2u)
#define DMAC14_CHCTRL_n_SWRST_SHIFT         (3u)
#define DMAC14_CHCTRL_n_CLRRQ_SHIFT         (4u)
#define DMAC14_CHCTRL_n_CLREND_SHIFT        (5u)
#define DMAC14_CHCTRL_n_CLRTC_SHIFT         (6u)
#define DMAC14_CHCTRL_n_SETSUS_SHIFT        (8u)
#define DMAC14_CHCTRL_n_CLRSUS_SHIFT        (9u)
#define DMAC14_CHCTRL_n_SETINTMSK_SHIFT     (16u)
#define DMAC14_CHCTRL_n_CLRINTMSK_SHIFT     (17u)

#define DMAC14_CHCFG_n_SEL_SHIFT            (0u)
#define DMAC14_CHCFG_n_REQD_SHIFT           (3u)
#define DMAC14_CHCFG_n_LOEN_SHIFT           (4u)
#define DMAC14_CHCFG_n_HIEN_SHIFT           (5u)
#define DMAC14_CHCFG_n_LVL_SHIFT            (6u)
#define DMAC14_CHCFG_n_AM_SHIFT             (8u)
#define DMAC14_CHCFG_n_SDS_SHIFT            (12u)
#define DMAC14_CHCFG_n_DDS_SHIFT            (16u)
#define DMAC14_CHCFG_n_SAD_SHIFT            (20u)
#define DMAC14_CHCFG_n_DAD_SHIFT            (21u)
#define DMAC14_CHCFG_n_TM_SHIFT             (22u)
#define DMAC14_CHCFG_n_DEM_SHIFT            (24u)
#define DMAC14_CHCFG_n_TCM_SHIFT            (25u)
#define DMAC14_CHCFG_n_SBE_SHIFT            (27u)
#define DMAC14_CHCFG_n_RSEL_SHIFT           (28u)
#define DMAC14_CHCFG_n_RSW_SHIFT            (29u)
#define DMAC14_CHCFG_n_REN_SHIFT            (30u)
#define DMAC14_CHCFG_n_DMS_SHIFT            (31u)

#define DMAC14_CHITVL_n_ITVL_SHIFT          (0u)

#define DMAC14_CHEXT_n_SCA_SHIFT            (4u)
#define DMAC14_CHEXT_n_DCA_SHIFT            (12u)

#define DMAC14_NXLA_n_NXLA_SHIFT            (0u)

#define DMAC14_CRLA_n_CRLA_SHIFT            (0u)

/* ---- DMAC15 ---- */
#define DMAC15_N0SA_n_SA_SHIFT              (0u)

#define DMAC15_N0DA_n_DA_SHIFT              (0u)

#define DMAC15_N0TB_n_TB_SHIFT              (0u)

#define DMAC15_N1SA_n_SA_SHIFT              (0u)

#define DMAC15_N1DA_n_DA_SHIFT              (0u)

#define DMAC15_N1TB_n_TB_SHIFT              (0u)

#define DMAC15_CRSA_n_CRSA_SHIFT            (0u)

#define DMAC15_CRDA_n_CRDA_SHIFT            (0u)

#define DMAC15_CRTB_n_CRTB_SHIFT            (0u)

#define DMAC15_CHSTAT_n_EN_SHIFT            (0u)
#define DMAC15_CHSTAT_n_RQST_SHIFT          (1u)
#define DMAC15_CHSTAT_n_TACT_SHIFT          (2u)
#define DMAC15_CHSTAT_n_SUS_SHIFT           (3u)
#define DMAC15_CHSTAT_n_ER_SHIFT            (4u)
#define DMAC15_CHSTAT_n_END_SHIFT           (5u)
#define DMAC15_CHSTAT_n_TC_SHIFT            (6u)
#define DMAC15_CHSTAT_n_SR_SHIFT            (7u)
#define DMAC15_CHSTAT_n_DL_SHIFT            (8u)
#define DMAC15_CHSTAT_n_DW_SHIFT            (9u)
#define DMAC15_CHSTAT_n_DER_SHIFT           (10u)
#define DMAC15_CHSTAT_n_MODE_SHIFT          (11u)
#define DMAC15_CHSTAT_n_INTMSK_SHIFT        (16u)

#define DMAC15_CHCTRL_n_SETEN_SHIFT         (0u)
#define DMAC15_CHCTRL_n_CLREN_SHIFT         (1u)
#define DMAC15_CHCTRL_n_STG_SHIFT           (2u)
#define DMAC15_CHCTRL_n_SWRST_SHIFT         (3u)
#define DMAC15_CHCTRL_n_CLRRQ_SHIFT         (4u)
#define DMAC15_CHCTRL_n_CLREND_SHIFT        (5u)
#define DMAC15_CHCTRL_n_CLRTC_SHIFT         (6u)
#define DMAC15_CHCTRL_n_SETSUS_SHIFT        (8u)
#define DMAC15_CHCTRL_n_CLRSUS_SHIFT        (9u)
#define DMAC15_CHCTRL_n_SETINTMSK_SHIFT     (16u)
#define DMAC15_CHCTRL_n_CLRINTMSK_SHIFT     (17u)

#define DMAC15_CHCFG_n_SEL_SHIFT            (0u)
#define DMAC15_CHCFG_n_REQD_SHIFT           (3u)
#define DMAC15_CHCFG_n_LOEN_SHIFT           (4u)
#define DMAC15_CHCFG_n_HIEN_SHIFT           (5u)
#define DMAC15_CHCFG_n_LVL_SHIFT            (6u)
#define DMAC15_CHCFG_n_AM_SHIFT             (8u)
#define DMAC15_CHCFG_n_SDS_SHIFT            (12u)
#define DMAC15_CHCFG_n_DDS_SHIFT            (16u)
#define DMAC15_CHCFG_n_SAD_SHIFT            (20u)
#define DMAC15_CHCFG_n_DAD_SHIFT            (21u)
#define DMAC15_CHCFG_n_TM_SHIFT             (22u)
#define DMAC15_CHCFG_n_DEM_SHIFT            (24u)
#define DMAC15_CHCFG_n_TCM_SHIFT            (25u)
#define DMAC15_CHCFG_n_SBE_SHIFT            (27u)
#define DMAC15_CHCFG_n_RSEL_SHIFT           (28u)
#define DMAC15_CHCFG_n_RSW_SHIFT            (29u)
#define DMAC15_CHCFG_n_REN_SHIFT            (30u)
#define DMAC15_CHCFG_n_DMS_SHIFT            (31u)

#define DMAC15_CHITVL_n_ITVL_SHIFT          (0u)

#define DMAC15_CHEXT_n_SCA_SHIFT            (4u)
#define DMAC15_CHEXT_n_DCA_SHIFT            (12u)

#define DMAC15_NXLA_n_NXLA_SHIFT            (0u)

#define DMAC15_CRLA_n_CRLA_SHIFT            (0u)

/* ---- DMAC8-15 ---- */
#define DMAC815_DCTRL_8_15_PR_SHIFT         (0u)
#define DMAC815_DCTRL_8_15_LVINT_SHIFT      (1u)
#define DMAC815_DCTRL_8_15_LDCA_SHIFT       (2u)
#define DMAC815_DCTRL_8_15_LWCA_SHIFT       (10u)

#define DMAC815_DSTAT_EN_8_15_EN8_SHIFT     (0u)
#define DMAC815_DSTAT_EN_8_15_EN9_SHIFT     (1u)
#define DMAC815_DSTAT_EN_8_15_EN10_SHIFT    (2u)
#define DMAC815_DSTAT_EN_8_15_EN11_SHIFT    (3u)
#define DMAC815_DSTAT_EN_8_15_EN12_SHIFT    (4u)
#define DMAC815_DSTAT_EN_8_15_EN13_SHIFT    (5u)
#define DMAC815_DSTAT_EN_8_15_EN14_SHIFT    (6u)
#define DMAC815_DSTAT_EN_8_15_EN15_SHIFT    (7u)

#define DMAC815_DSTAT_ER_8_15_ER8_SHIFT     (0u)
#define DMAC815_DSTAT_ER_8_15_ER9_SHIFT     (1u)
#define DMAC815_DSTAT_ER_8_15_ER10_SHIFT    (2u)
#define DMAC815_DSTAT_ER_8_15_ER11_SHIFT    (3u)
#define DMAC815_DSTAT_ER_8_15_ER12_SHIFT    (4u)
#define DMAC815_DSTAT_ER_8_15_ER13_SHIFT    (5u)
#define DMAC815_DSTAT_ER_8_15_ER14_SHIFT    (6u)
#define DMAC815_DSTAT_ER_8_15_ER15_SHIFT    (7u)

#define DMAC815_DSTAT_END_8_15_END8_SHIFT   (0u)
#define DMAC815_DSTAT_END_8_15_END9_SHIFT   (1u)
#define DMAC815_DSTAT_END_8_15_END10_SHIFT  (2u)
#define DMAC815_DSTAT_END_8_15_END11_SHIFT  (3u)
#define DMAC815_DSTAT_END_8_15_END12_SHIFT  (4u)
#define DMAC815_DSTAT_END_8_15_END13_SHIFT  (5u)
#define DMAC815_DSTAT_END_8_15_END14_SHIFT  (6u)
#define DMAC815_DSTAT_END_8_15_END15_SHIFT  (7u)

#define DMAC815_DSTAT_TC_8_15_TC8_SHIFT     (0u)
#define DMAC815_DSTAT_TC_8_15_TC9_SHIFT     (1u)
#define DMAC815_DSTAT_TC_8_15_TC10_SHIFT    (2u)
#define DMAC815_DSTAT_TC_8_15_TC11_SHIFT    (3u)
#define DMAC815_DSTAT_TC_8_15_TC12_SHIFT    (4u)
#define DMAC815_DSTAT_TC_8_15_TC13_SHIFT    (5u)
#define DMAC815_DSTAT_TC_8_15_TC14_SHIFT    (6u)
#define DMAC815_DSTAT_TC_8_15_TC15_SHIFT    (7u)

#define DMAC815_DSTAT_SUS_8_15_SUS8_SHIFT   (0u)
#define DMAC815_DSTAT_SUS_8_15_SUS9_SHIFT   (1u)
#define DMAC815_DSTAT_SUS_8_15_SUS10_SHIFT  (2u)
#define DMAC815_DSTAT_SUS_8_15_SUS11_SHIFT  (3u)
#define DMAC815_DSTAT_SUS_8_15_SUS12_SHIFT  (4u)
#define DMAC815_DSTAT_SUS_8_15_SUS13_SHIFT  (5u)
#define DMAC815_DSTAT_SUS_8_15_SUS14_SHIFT  (6u)
#define DMAC815_DSTAT_SUS_8_15_SUS15_SHIFT  (7u)

/* ---- DMAC0-1 ---- */
#define DMAC01_DMARS_CH0_RID_SHIFT          (0u)
#define DMAC01_DMARS_CH0_MID_SHIFT          (2u)
#define DMAC01_DMARS_CH1_RID_SHIFT          (16u)
#define DMAC01_DMARS_CH1_MID_SHIFT          (18u)

/* ---- DMAC2-3 ---- */
#define DMAC23_DMARS_CH2_RID_SHIFT          (0u)
#define DMAC23_DMARS_CH2_MID_SHIFT          (2u)
#define DMAC23_DMARS_CH3_RID_SHIFT          (16u)
#define DMAC23_DMARS_CH3_MID_SHIFT          (18u)

/* ---- DMAC4-5 ---- */
#define DMAC45_DMARS_CH4_RID_SHIFT          (0u)
#define DMAC45_DMARS_CH4_MID_SHIFT          (2u)
#define DMAC45_DMARS_CH5_RID_SHIFT          (16u)
#define DMAC45_DMARS_CH5_MID_SHIFT          (18u)

/* ---- DMAC6-7 ---- */
#define DMAC67_DMARS_CH6_RID_SHIFT          (0u)
#define DMAC67_DMARS_CH6_MID_SHIFT          (2u)
#define DMAC67_DMARS_CH7_RID_SHIFT          (16u)
#define DMAC67_DMARS_CH7_MID_SHIFT          (18u)

/* ---- DMAC8-9 ---- */
#define DMAC89_DMARS_CH8_RID_SHIFT          (0u)
#define DMAC89_DMARS_CH8_MID_SHIFT          (2u)
#define DMAC89_DMARS_CH9_RID_SHIFT          (16u)
#define DMAC89_DMARS_CH9_MID_SHIFT          (18u)

/* ---- DMAC10-11 ---- */
#define DMAC1011_DMARS_CH10_RID_SHIFT       (0u)
#define DMAC1011_DMARS_CH10_MID_SHIFT       (2u)
#define DMAC1011_DMARS_CH11_RID_SHIFT       (16u)
#define DMAC1011_DMARS_CH11_MID_SHIFT       (18u)

/* ---- DMAC12-13 ---- */
#define DMAC1213_DMARS_CH12_RID_SHIFT       (0u)
#define DMAC1213_DMARS_CH12_MID_SHIFT       (2u)
#define DMAC1213_DMARS_CH13_RID_SHIFT       (16u)
#define DMAC1213_DMARS_CH13_MID_SHIFT       (18u)

/* ---- DMAC14-15 ---- */
#define DMAC1415_DMARS_CH14_RID_SHIFT       (0u)
#define DMAC1415_DMARS_CH14_MID_SHIFT       (2u)
#define DMAC1415_DMARS_CH15_RID_SHIFT       (16u)
#define DMAC1415_DMARS_CH15_MID_SHIFT       (18u)


#endif /* DMAC_IOBITMASK_H */

/* End of File */
