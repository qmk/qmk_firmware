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
* File Name   : scif_iobitmask.h
* $Rev: 1115 $
* $Date:: 2014-07-09 15:35:02 +0900#$
* Description : SCIF register define header
*******************************************************************************/
#ifndef SCIF_IOBITMASK_H
#define SCIF_IOBITMASK_H


/* ==== Mask values for IO registers ==== */
/* ---- SCIF0 ---- */
#define SCIF0_SCSMR_CKS                         (0x0003u)
#define SCIF0_SCSMR_STOP                        (0x0008u)
#define SCIF0_SCSMR_OE                          (0x0010u)
#define SCIF0_SCSMR_PE                          (0x0020u)
#define SCIF0_SCSMR_CHR                         (0x0040u)
#define SCIF0_SCSMR_CA                          (0x0080u)

#define SCIF0_SCBRR_D                           (0xFFu)

#define SCIF0_SCSCR_CKE                         (0x0003u)
#define SCIF0_SCSCR_REIE                        (0x0008u)
#define SCIF0_SCSCR_RE                          (0x0010u)
#define SCIF0_SCSCR_TE                          (0x0020u)
#define SCIF0_SCSCR_RIE                         (0x0040u)
#define SCIF0_SCSCR_TIE                         (0x0080u)

#define SCIF0_SCFTDR_D                          (0xFFu)

#define SCIF0_SCFSR_DR                          (0x0001u)
#define SCIF0_SCFSR_RDF                         (0x0002u)
#define SCIF0_SCFSR_PER                         (0x0004u)
#define SCIF0_SCFSR_FER                         (0x0008u)
#define SCIF0_SCFSR_BRK                         (0x0010u)
#define SCIF0_SCFSR_TDFE                        (0x0020u)
#define SCIF0_SCFSR_TEND                        (0x0040u)
#define SCIF0_SCFSR_ER                          (0x0080u)
#define SCIF0_SCFSR_FERN                        (0x0F00u)
#define SCIF0_SCFSR_PERN                        (0xF000u)

#define SCIF0_SCFRDR_D                          (0xFFu)

#define SCIF0_SCFCR_LOOP                        (0x0001u)
#define SCIF0_SCFCR_RFRST                       (0x0002u)
#define SCIF0_SCFCR_TFRST                       (0x0004u)
#define SCIF0_SCFCR_MCE                         (0x0008u)
#define SCIF0_SCFCR_TTRG                        (0x0030u)
#define SCIF0_SCFCR_RTRG                        (0x00C0u)
#define SCIF0_SCFCR_RSTRG                       (0x0700u)

#define SCIF0_SCFDR_R                           (0x001Fu)
#define SCIF0_SCFDR_T                           (0x1F00u)

#define SCIF0_SCSPTR_SPB2DT                     (0x0001u)
#define SCIF0_SCSPTR_SPB2IO                     (0x0002u)
#define SCIF0_SCSPTR_SCKDT                      (0x0004u)
#define SCIF0_SCSPTR_SCKIO                      (0x0008u)
#define SCIF0_SCSPTR_CTSDT                      (0x0010u)
#define SCIF0_SCSPTR_CTSIO                      (0x0020u)
#define SCIF0_SCSPTR_RTSDT                      (0x0040u)
#define SCIF0_SCSPTR_RTSIO                      (0x0080u)

#define SCIF0_SCLSR_ORER                        (0x0001u)

#define SCIF0_SCEMR_ABCS                        (0x0001u)
#define SCIF0_SCEMR_BGDM                        (0x0080u)

/* ---- SCIF1 ---- */
#define SCIF1_SCSMR_CKS                         (0x0003u)
#define SCIF1_SCSMR_STOP                        (0x0008u)
#define SCIF1_SCSMR_OE                          (0x0010u)
#define SCIF1_SCSMR_PE                          (0x0020u)
#define SCIF1_SCSMR_CHR                         (0x0040u)
#define SCIF1_SCSMR_CA                          (0x0080u)

#define SCIF1_SCBRR_D                           (0xFFu)

#define SCIF1_SCSCR_CKE                         (0x0003u)
#define SCIF1_SCSCR_REIE                        (0x0008u)
#define SCIF1_SCSCR_RE                          (0x0010u)
#define SCIF1_SCSCR_TE                          (0x0020u)
#define SCIF1_SCSCR_RIE                         (0x0040u)
#define SCIF1_SCSCR_TIE                         (0x0080u)

#define SCIF1_SCFTDR_D                          (0xFFu)

#define SCIF1_SCFSR_DR                          (0x0001u)
#define SCIF1_SCFSR_RDF                         (0x0002u)
#define SCIF1_SCFSR_PER                         (0x0004u)
#define SCIF1_SCFSR_FER                         (0x0008u)
#define SCIF1_SCFSR_BRK                         (0x0010u)
#define SCIF1_SCFSR_TDFE                        (0x0020u)
#define SCIF1_SCFSR_TEND                        (0x0040u)
#define SCIF1_SCFSR_ER                          (0x0080u)
#define SCIF1_SCFSR_FERN                        (0x0F00u)
#define SCIF1_SCFSR_PERN                        (0xF000u)

#define SCIF1_SCFRDR_D                          (0xFFu)

#define SCIF1_SCFCR_LOOP                        (0x0001u)
#define SCIF1_SCFCR_RFRST                       (0x0002u)
#define SCIF1_SCFCR_TFRST                       (0x0004u)
#define SCIF1_SCFCR_MCE                         (0x0008u)
#define SCIF1_SCFCR_TTRG                        (0x0030u)
#define SCIF1_SCFCR_RTRG                        (0x00C0u)
#define SCIF1_SCFCR_RSTRG                       (0x0700u)

#define SCIF1_SCFDR_R                           (0x001Fu)
#define SCIF1_SCFDR_T                           (0x1F00u)

#define SCIF1_SCSPTR_SPB2DT                     (0x0001u)
#define SCIF1_SCSPTR_SPB2IO                     (0x0002u)
#define SCIF1_SCSPTR_SCKDT                      (0x0004u)
#define SCIF1_SCSPTR_SCKIO                      (0x0008u)
#define SCIF1_SCSPTR_CTSDT                      (0x0010u)
#define SCIF1_SCSPTR_CTSIO                      (0x0020u)
#define SCIF1_SCSPTR_RTSDT                      (0x0040u)
#define SCIF1_SCSPTR_RTSIO                      (0x0080u)

#define SCIF1_SCLSR_ORER                        (0x0001u)

#define SCIF1_SCEMR_ABCS                        (0x0001u)
#define SCIF1_SCEMR_BGDM                        (0x0080u)

/* ---- SCIF2 ---- */
#define SCIF2_SCSMR_CKS                         (0x0003u)
#define SCIF2_SCSMR_STOP                        (0x0008u)
#define SCIF2_SCSMR_OE                          (0x0010u)
#define SCIF2_SCSMR_PE                          (0x0020u)
#define SCIF2_SCSMR_CHR                         (0x0040u)
#define SCIF2_SCSMR_CA                          (0x0080u)

#define SCIF2_SCBRR_D                           (0xFFu)

#define SCIF2_SCSCR_CKE                         (0x0003u)
#define SCIF2_SCSCR_REIE                        (0x0008u)
#define SCIF2_SCSCR_RE                          (0x0010u)
#define SCIF2_SCSCR_TE                          (0x0020u)
#define SCIF2_SCSCR_RIE                         (0x0040u)
#define SCIF2_SCSCR_TIE                         (0x0080u)

#define SCIF2_SCFTDR_D                          (0xFFu)

#define SCIF2_SCFSR_DR                          (0x0001u)
#define SCIF2_SCFSR_RDF                         (0x0002u)
#define SCIF2_SCFSR_PER                         (0x0004u)
#define SCIF2_SCFSR_FER                         (0x0008u)
#define SCIF2_SCFSR_BRK                         (0x0010u)
#define SCIF2_SCFSR_TDFE                        (0x0020u)
#define SCIF2_SCFSR_TEND                        (0x0040u)
#define SCIF2_SCFSR_ER                          (0x0080u)
#define SCIF2_SCFSR_FERN                        (0x0F00u)
#define SCIF2_SCFSR_PERN                        (0xF000u)

#define SCIF2_SCFRDR_D                          (0xFFu)

#define SCIF2_SCFCR_LOOP                        (0x0001u)
#define SCIF2_SCFCR_RFRST                       (0x0002u)
#define SCIF2_SCFCR_TFRST                       (0x0004u)
#define SCIF2_SCFCR_MCE                         (0x0008u)
#define SCIF2_SCFCR_TTRG                        (0x0030u)
#define SCIF2_SCFCR_RTRG                        (0x00C0u)
#define SCIF2_SCFCR_RSTRG                       (0x0700u)

#define SCIF2_SCFDR_R                           (0x001Fu)
#define SCIF2_SCFDR_T                           (0x1F00u)

#define SCIF2_SCSPTR_SPB2DT                     (0x0001u)
#define SCIF2_SCSPTR_SPB2IO                     (0x0002u)
#define SCIF2_SCSPTR_SCKDT                      (0x0004u)
#define SCIF2_SCSPTR_SCKIO                      (0x0008u)
#define SCIF2_SCSPTR_CTSDT                      (0x0010u)
#define SCIF2_SCSPTR_CTSIO                      (0x0020u)
#define SCIF2_SCSPTR_RTSDT                      (0x0040u)
#define SCIF2_SCSPTR_RTSIO                      (0x0080u)

#define SCIF2_SCLSR_ORER                        (0x0001u)

#define SCIF2_SCEMR_ABCS                        (0x0001u)
#define SCIF2_SCEMR_BGDM                        (0x0080u)

/* ---- SCIF3 ---- */
#define SCIF3_SCSMR_CKS                         (0x0003u)
#define SCIF3_SCSMR_STOP                        (0x0008u)
#define SCIF3_SCSMR_OE                          (0x0010u)
#define SCIF3_SCSMR_PE                          (0x0020u)
#define SCIF3_SCSMR_CHR                         (0x0040u)
#define SCIF3_SCSMR_CA                          (0x0080u)

#define SCIF3_SCBRR_D                           (0xFFu)

#define SCIF3_SCSCR_CKE                         (0x0003u)
#define SCIF3_SCSCR_REIE                        (0x0008u)
#define SCIF3_SCSCR_RE                          (0x0010u)
#define SCIF3_SCSCR_TE                          (0x0020u)
#define SCIF3_SCSCR_RIE                         (0x0040u)
#define SCIF3_SCSCR_TIE                         (0x0080u)

#define SCIF3_SCFTDR_D                          (0xFFu)

#define SCIF3_SCFSR_DR                          (0x0001u)
#define SCIF3_SCFSR_RDF                         (0x0002u)
#define SCIF3_SCFSR_PER                         (0x0004u)
#define SCIF3_SCFSR_FER                         (0x0008u)
#define SCIF3_SCFSR_BRK                         (0x0010u)
#define SCIF3_SCFSR_TDFE                        (0x0020u)
#define SCIF3_SCFSR_TEND                        (0x0040u)
#define SCIF3_SCFSR_ER                          (0x0080u)
#define SCIF3_SCFSR_FERN                        (0x0F00u)
#define SCIF3_SCFSR_PERN                        (0xF000u)

#define SCIF3_SCFRDR_D                          (0xFFu)

#define SCIF3_SCFCR_LOOP                        (0x0001u)
#define SCIF3_SCFCR_RFRST                       (0x0002u)
#define SCIF3_SCFCR_TFRST                       (0x0004u)
#define SCIF3_SCFCR_MCE                         (0x0008u)
#define SCIF3_SCFCR_TTRG                        (0x0030u)
#define SCIF3_SCFCR_RTRG                        (0x00C0u)
#define SCIF3_SCFCR_RSTRG                       (0x0700u)

#define SCIF3_SCFDR_R                           (0x001Fu)
#define SCIF3_SCFDR_T                           (0x1F00u)

#define SCIF3_SCSPTR_SPB2DT                     (0x0001u)
#define SCIF3_SCSPTR_SPB2IO                     (0x0002u)
#define SCIF3_SCSPTR_SCKDT                      (0x0004u)
#define SCIF3_SCSPTR_SCKIO                      (0x0008u)
#define SCIF3_SCSPTR_CTSDT                      (0x0010u)
#define SCIF3_SCSPTR_CTSIO                      (0x0020u)
#define SCIF3_SCSPTR_RTSDT                      (0x0040u)
#define SCIF3_SCSPTR_RTSIO                      (0x0080u)

#define SCIF3_SCLSR_ORER                        (0x0001u)

#define SCIF3_SCEMR_ABCS                        (0x0001u)
#define SCIF3_SCEMR_BGDM                        (0x0080u)

/* ---- SCIF4 ---- */
#define SCIF4_SCSMR_CKS                         (0x0003u)
#define SCIF4_SCSMR_STOP                        (0x0008u)
#define SCIF4_SCSMR_OE                          (0x0010u)
#define SCIF4_SCSMR_PE                          (0x0020u)
#define SCIF4_SCSMR_CHR                         (0x0040u)
#define SCIF4_SCSMR_CA                          (0x0080u)

#define SCIF4_SCBRR_D                           (0xFFu)

#define SCIF4_SCSCR_CKE                         (0x0003u)
#define SCIF4_SCSCR_REIE                        (0x0008u)
#define SCIF4_SCSCR_RE                          (0x0010u)
#define SCIF4_SCSCR_TE                          (0x0020u)
#define SCIF4_SCSCR_RIE                         (0x0040u)
#define SCIF4_SCSCR_TIE                         (0x0080u)

#define SCIF4_SCFTDR_D                          (0xFFu)

#define SCIF4_SCFSR_DR                          (0x0001u)
#define SCIF4_SCFSR_RDF                         (0x0002u)
#define SCIF4_SCFSR_PER                         (0x0004u)
#define SCIF4_SCFSR_FER                         (0x0008u)
#define SCIF4_SCFSR_BRK                         (0x0010u)
#define SCIF4_SCFSR_TDFE                        (0x0020u)
#define SCIF4_SCFSR_TEND                        (0x0040u)
#define SCIF4_SCFSR_ER                          (0x0080u)
#define SCIF4_SCFSR_FERN                        (0x0F00u)
#define SCIF4_SCFSR_PERN                        (0xF000u)

#define SCIF4_SCFRDR_D                          (0xFFu)

#define SCIF4_SCFCR_LOOP                        (0x0001u)
#define SCIF4_SCFCR_RFRST                       (0x0002u)
#define SCIF4_SCFCR_TFRST                       (0x0004u)
#define SCIF4_SCFCR_MCE                         (0x0008u)
#define SCIF4_SCFCR_TTRG                        (0x0030u)
#define SCIF4_SCFCR_RTRG                        (0x00C0u)
#define SCIF4_SCFCR_RSTRG                       (0x0700u)

#define SCIF4_SCFDR_R                           (0x001Fu)
#define SCIF4_SCFDR_T                           (0x1F00u)

#define SCIF4_SCSPTR_SPB2DT                     (0x0001u)
#define SCIF4_SCSPTR_SPB2IO                     (0x0002u)
#define SCIF4_SCSPTR_SCKDT                      (0x0004u)
#define SCIF4_SCSPTR_SCKIO                      (0x0008u)
#define SCIF4_SCSPTR_CTSDT                      (0x0010u)
#define SCIF4_SCSPTR_CTSIO                      (0x0020u)
#define SCIF4_SCSPTR_RTSDT                      (0x0040u)
#define SCIF4_SCSPTR_RTSIO                      (0x0080u)

#define SCIF4_SCLSR_ORER                        (0x0001u)

#define SCIF4_SCEMR_ABCS                        (0x0001u)
#define SCIF4_SCEMR_BGDM                        (0x0080u)

/* ---- SCIF5 ---- */
#define SCIF5_SCSMR_CKS                         (0x0003u)
#define SCIF5_SCSMR_STOP                        (0x0008u)
#define SCIF5_SCSMR_OE                          (0x0010u)
#define SCIF5_SCSMR_PE                          (0x0020u)
#define SCIF5_SCSMR_CHR                         (0x0040u)
#define SCIF5_SCSMR_CA                          (0x0080u)

#define SCIF5_SCBRR_D                           (0xFFu)

#define SCIF5_SCSCR_CKE                         (0x0003u)
#define SCIF5_SCSCR_REIE                        (0x0008u)
#define SCIF5_SCSCR_RE                          (0x0010u)
#define SCIF5_SCSCR_TE                          (0x0020u)
#define SCIF5_SCSCR_RIE                         (0x0040u)
#define SCIF5_SCSCR_TIE                         (0x0080u)

#define SCIF5_SCFTDR_D                          (0xFFu)

#define SCIF5_SCFSR_DR                          (0x0001u)
#define SCIF5_SCFSR_RDF                         (0x0002u)
#define SCIF5_SCFSR_PER                         (0x0004u)
#define SCIF5_SCFSR_FER                         (0x0008u)
#define SCIF5_SCFSR_BRK                         (0x0010u)
#define SCIF5_SCFSR_TDFE                        (0x0020u)
#define SCIF5_SCFSR_TEND                        (0x0040u)
#define SCIF5_SCFSR_ER                          (0x0080u)
#define SCIF5_SCFSR_FERN                        (0x0F00u)
#define SCIF5_SCFSR_PERN                        (0xF000u)

#define SCIF5_SCFRDR_D                          (0xFFu)

#define SCIF5_SCFCR_LOOP                        (0x0001u)
#define SCIF5_SCFCR_RFRST                       (0x0002u)
#define SCIF5_SCFCR_TFRST                       (0x0004u)
#define SCIF5_SCFCR_MCE                         (0x0008u)
#define SCIF5_SCFCR_TTRG                        (0x0030u)
#define SCIF5_SCFCR_RTRG                        (0x00C0u)
#define SCIF5_SCFCR_RSTRG                       (0x0700u)

#define SCIF5_SCFDR_R                           (0x001Fu)
#define SCIF5_SCFDR_T                           (0x1F00u)

#define SCIF5_SCSPTR_SPB2DT                     (0x0001u)
#define SCIF5_SCSPTR_SPB2IO                     (0x0002u)
#define SCIF5_SCSPTR_SCKDT                      (0x0004u)
#define SCIF5_SCSPTR_SCKIO                      (0x0008u)
#define SCIF5_SCSPTR_CTSDT                      (0x0010u)
#define SCIF5_SCSPTR_CTSIO                      (0x0020u)
#define SCIF5_SCSPTR_RTSDT                      (0x0040u)
#define SCIF5_SCSPTR_RTSIO                      (0x0080u)

#define SCIF5_SCLSR_ORER                        (0x0001u)

#define SCIF5_SCEMR_ABCS                        (0x0001u)
#define SCIF5_SCEMR_BGDM                        (0x0080u)

/* ---- SCIF6 ---- */
#define SCIF6_SCSMR_CKS                         (0x0003u)
#define SCIF6_SCSMR_STOP                        (0x0008u)
#define SCIF6_SCSMR_OE                          (0x0010u)
#define SCIF6_SCSMR_PE                          (0x0020u)
#define SCIF6_SCSMR_CHR                         (0x0040u)
#define SCIF6_SCSMR_CA                          (0x0080u)

#define SCIF6_SCBRR_D                           (0xFFu)

#define SCIF6_SCSCR_CKE                         (0x0003u)
#define SCIF6_SCSCR_REIE                        (0x0008u)
#define SCIF6_SCSCR_RE                          (0x0010u)
#define SCIF6_SCSCR_TE                          (0x0020u)
#define SCIF6_SCSCR_RIE                         (0x0040u)
#define SCIF6_SCSCR_TIE                         (0x0080u)

#define SCIF6_SCFTDR_D                          (0xFFu)

#define SCIF6_SCFSR_DR                          (0x0001u)
#define SCIF6_SCFSR_RDF                         (0x0002u)
#define SCIF6_SCFSR_PER                         (0x0004u)
#define SCIF6_SCFSR_FER                         (0x0008u)
#define SCIF6_SCFSR_BRK                         (0x0010u)
#define SCIF6_SCFSR_TDFE                        (0x0020u)
#define SCIF6_SCFSR_TEND                        (0x0040u)
#define SCIF6_SCFSR_ER                          (0x0080u)
#define SCIF6_SCFSR_FERN                        (0x0F00u)
#define SCIF6_SCFSR_PERN                        (0xF000u)

#define SCIF6_SCFRDR_D                          (0xFFu)

#define SCIF6_SCFCR_LOOP                        (0x0001u)
#define SCIF6_SCFCR_RFRST                       (0x0002u)
#define SCIF6_SCFCR_TFRST                       (0x0004u)
#define SCIF6_SCFCR_MCE                         (0x0008u)
#define SCIF6_SCFCR_TTRG                        (0x0030u)
#define SCIF6_SCFCR_RTRG                        (0x00C0u)
#define SCIF6_SCFCR_RSTRG                       (0x0700u)

#define SCIF6_SCFDR_R                           (0x001Fu)
#define SCIF6_SCFDR_T                           (0x1F00u)

#define SCIF6_SCSPTR_SPB2DT                     (0x0001u)
#define SCIF6_SCSPTR_SPB2IO                     (0x0002u)
#define SCIF6_SCSPTR_SCKDT                      (0x0004u)
#define SCIF6_SCSPTR_SCKIO                      (0x0008u)
#define SCIF6_SCSPTR_CTSDT                      (0x0010u)
#define SCIF6_SCSPTR_CTSIO                      (0x0020u)
#define SCIF6_SCSPTR_RTSDT                      (0x0040u)
#define SCIF6_SCSPTR_RTSIO                      (0x0080u)

#define SCIF6_SCLSR_ORER                        (0x0001u)

#define SCIF6_SCEMR_ABCS                        (0x0001u)
#define SCIF6_SCEMR_BGDM                        (0x0080u)

/* ---- SCIF7 ---- */
#define SCIF7_SCSMR_CKS                         (0x0003u)
#define SCIF7_SCSMR_STOP                        (0x0008u)
#define SCIF7_SCSMR_OE                          (0x0010u)
#define SCIF7_SCSMR_PE                          (0x0020u)
#define SCIF7_SCSMR_CHR                         (0x0040u)
#define SCIF7_SCSMR_CA                          (0x0080u)

#define SCIF7_SCBRR_D                           (0xFFu)

#define SCIF7_SCSCR_CKE                         (0x0003u)
#define SCIF7_SCSCR_REIE                        (0x0008u)
#define SCIF7_SCSCR_RE                          (0x0010u)
#define SCIF7_SCSCR_TE                          (0x0020u)
#define SCIF7_SCSCR_RIE                         (0x0040u)
#define SCIF7_SCSCR_TIE                         (0x0080u)

#define SCIF7_SCFTDR_D                          (0xFFu)

#define SCIF7_SCFSR_DR                          (0x0001u)
#define SCIF7_SCFSR_RDF                         (0x0002u)
#define SCIF7_SCFSR_PER                         (0x0004u)
#define SCIF7_SCFSR_FER                         (0x0008u)
#define SCIF7_SCFSR_BRK                         (0x0010u)
#define SCIF7_SCFSR_TDFE                        (0x0020u)
#define SCIF7_SCFSR_TEND                        (0x0040u)
#define SCIF7_SCFSR_ER                          (0x0080u)
#define SCIF7_SCFSR_FERN                        (0x0F00u)
#define SCIF7_SCFSR_PERN                        (0xF000u)

#define SCIF7_SCFRDR_D                          (0xFFu)

#define SCIF7_SCFCR_LOOP                        (0x0001u)
#define SCIF7_SCFCR_RFRST                       (0x0002u)
#define SCIF7_SCFCR_TFRST                       (0x0004u)
#define SCIF7_SCFCR_MCE                         (0x0008u)
#define SCIF7_SCFCR_TTRG                        (0x0030u)
#define SCIF7_SCFCR_RTRG                        (0x00C0u)
#define SCIF7_SCFCR_RSTRG                       (0x0700u)

#define SCIF7_SCFDR_R                           (0x001Fu)
#define SCIF7_SCFDR_T                           (0x1F00u)

#define SCIF7_SCSPTR_SPB2DT                     (0x0001u)
#define SCIF7_SCSPTR_SPB2IO                     (0x0002u)
#define SCIF7_SCSPTR_SCKDT                      (0x0004u)
#define SCIF7_SCSPTR_SCKIO                      (0x0008u)
#define SCIF7_SCSPTR_CTSDT                      (0x0010u)
#define SCIF7_SCSPTR_CTSIO                      (0x0020u)
#define SCIF7_SCSPTR_RTSDT                      (0x0040u)
#define SCIF7_SCSPTR_RTSIO                      (0x0080u)

#define SCIF7_SCLSR_ORER                        (0x0001u)

#define SCIF7_SCEMR_ABCS                        (0x0001u)
#define SCIF7_SCEMR_BGDM                        (0x0080u)

/* ---- SCIFn ---- */
#define SCIFn_SCSMR_CKS                         (0x0003u)
#define SCIFn_SCSMR_STOP                        (0x0008u)
#define SCIFn_SCSMR_OE                          (0x0010u)
#define SCIFn_SCSMR_PE                          (0x0020u)
#define SCIFn_SCSMR_CHR                         (0x0040u)
#define SCIFn_SCSMR_CA                          (0x0080u)

#define SCIFn_SCBRR_D                           (0xFFu)

#define SCIFn_SCSCR_CKE                         (0x0003u)
#define SCIFn_SCSCR_REIE                        (0x0008u)
#define SCIFn_SCSCR_RE                          (0x0010u)
#define SCIFn_SCSCR_TE                          (0x0020u)
#define SCIFn_SCSCR_RIE                         (0x0040u)
#define SCIFn_SCSCR_TIE                         (0x0080u)

#define SCIFn_SCFTDR_D                          (0xFFu)

#define SCIFn_SCFSR_DR                          (0x0001u)
#define SCIFn_SCFSR_RDF                         (0x0002u)
#define SCIFn_SCFSR_PER                         (0x0004u)
#define SCIFn_SCFSR_FER                         (0x0008u)
#define SCIFn_SCFSR_BRK                         (0x0010u)
#define SCIFn_SCFSR_TDFE                        (0x0020u)
#define SCIFn_SCFSR_TEND                        (0x0040u)
#define SCIFn_SCFSR_ER                          (0x0080u)
#define SCIFn_SCFSR_FERN                        (0x0F00u)
#define SCIFn_SCFSR_PERN                        (0xF000u)

#define SCIFn_SCFRDR_D                          (0xFFu)

#define SCIFn_SCFCR_LOOP                        (0x0001u)
#define SCIFn_SCFCR_RFRST                       (0x0002u)
#define SCIFn_SCFCR_TFRST                       (0x0004u)
#define SCIFn_SCFCR_MCE                         (0x0008u)
#define SCIFn_SCFCR_TTRG                        (0x0030u)
#define SCIFn_SCFCR_RTRG                        (0x00C0u)
#define SCIFn_SCFCR_RSTRG                       (0x0700u)

#define SCIFn_SCFDR_R                           (0x001Fu)
#define SCIFn_SCFDR_T                           (0x1F00u)

#define SCIFn_SCSPTR_SPB2DT                     (0x0001u)
#define SCIFn_SCSPTR_SPB2IO                     (0x0002u)
#define SCIFn_SCSPTR_SCKDT                      (0x0004u)
#define SCIFn_SCSPTR_SCKIO                      (0x0008u)
#define SCIFn_SCSPTR_CTSDT                      (0x0010u)
#define SCIFn_SCSPTR_CTSIO                      (0x0020u)
#define SCIFn_SCSPTR_RTSDT                      (0x0040u)
#define SCIFn_SCSPTR_RTSIO                      (0x0080u)

#define SCIFn_SCLSR_ORER                        (0x0001u)

#define SCIFn_SCEMR_ABCS                        (0x0001u)
#define SCIFn_SCEMR_BGDM                        (0x0080u)


/* ==== Shift values for IO registers ==== */
/* ---- SCIF0 ---- */
#define SCIF0_SCSMR_CKS_SHIFT                   (0u)
#define SCIF0_SCSMR_STOP_SHIFT                  (3u)
#define SCIF0_SCSMR_OE_SHIFT                    (4u)
#define SCIF0_SCSMR_PE_SHIFT                    (5u)
#define SCIF0_SCSMR_CHR_SHIFT                   (6u)
#define SCIF0_SCSMR_CA_SHIFT                    (7u)

#define SCIF0_SCBRR_D_SHIFT                     (0u)

#define SCIF0_SCSCR_CKE_SHIFT                   (0u)
#define SCIF0_SCSCR_REIE_SHIFT                  (3u)
#define SCIF0_SCSCR_RE_SHIFT                    (4u)
#define SCIF0_SCSCR_TE_SHIFT                    (5u)
#define SCIF0_SCSCR_RIE_SHIFT                   (6u)
#define SCIF0_SCSCR_TIE_SHIFT                   (7u)

#define SCIF0_SCFTDR_D_SHIFT                    (0u)

#define SCIF0_SCFSR_DR_SHIFT                    (0u)
#define SCIF0_SCFSR_RDF_SHIFT                   (1u)
#define SCIF0_SCFSR_PER_SHIFT                   (2u)
#define SCIF0_SCFSR_FER_SHIFT                   (3u)
#define SCIF0_SCFSR_BRK_SHIFT                   (4u)
#define SCIF0_SCFSR_TDFE_SHIFT                  (5u)
#define SCIF0_SCFSR_TEND_SHIFT                  (6u)
#define SCIF0_SCFSR_ER_SHIFT                    (7u)
#define SCIF0_SCFSR_FERN_SHIFT                  (8u)
#define SCIF0_SCFSR_PERN_SHIFT                  (12u)

#define SCIF0_SCFRDR_D_SHIFT                    (0u)

#define SCIF0_SCFCR_LOOP_SHIFT                  (0u)
#define SCIF0_SCFCR_RFRST_SHIFT                 (1u)
#define SCIF0_SCFCR_TFRST_SHIFT                 (2u)
#define SCIF0_SCFCR_MCE_SHIFT                   (3u)
#define SCIF0_SCFCR_TTRG_SHIFT                  (4u)
#define SCIF0_SCFCR_RTRG_SHIFT                  (6u)
#define SCIF0_SCFCR_RSTRG_SHIFT                 (8u)

#define SCIF0_SCFDR_R_SHIFT                     (0u)
#define SCIF0_SCFDR_T_SHIFT                     (8u)

#define SCIF0_SCSPTR_SPB2DT_SHIFT               (0u)
#define SCIF0_SCSPTR_SPB2IO_SHIFT               (1u)
#define SCIF0_SCSPTR_SCKDT_SHIFT                (2u)
#define SCIF0_SCSPTR_SCKIO_SHIFT                (3u)
#define SCIF0_SCSPTR_CTSDT_SHIFT                (4u)
#define SCIF0_SCSPTR_CTSIO_SHIFT                (5u)
#define SCIF0_SCSPTR_RTSDT_SHIFT                (6u)
#define SCIF0_SCSPTR_RTSIO_SHIFT                (7u)

#define SCIF0_SCLSR_ORER_SHIFT                  (0u)

#define SCIF0_SCEMR_ABCS_SHIFT                  (0u)
#define SCIF0_SCEMR_BGDM_SHIFT                  (7u)

/* ---- SCIF1 ---- */
#define SCIF1_SCSMR_CKS_SHIFT                   (0u)
#define SCIF1_SCSMR_STOP_SHIFT                  (3u)
#define SCIF1_SCSMR_OE_SHIFT                    (4u)
#define SCIF1_SCSMR_PE_SHIFT                    (5u)
#define SCIF1_SCSMR_CHR_SHIFT                   (6u)
#define SCIF1_SCSMR_CA_SHIFT                    (7u)

#define SCIF1_SCBRR_D_SHIFT                     (0u)

#define SCIF1_SCSCR_CKE_SHIFT                   (0u)
#define SCIF1_SCSCR_REIE_SHIFT                  (3u)
#define SCIF1_SCSCR_RE_SHIFT                    (4u)
#define SCIF1_SCSCR_TE_SHIFT                    (5u)
#define SCIF1_SCSCR_RIE_SHIFT                   (6u)
#define SCIF1_SCSCR_TIE_SHIFT                   (7u)

#define SCIF1_SCFTDR_D_SHIFT                    (0u)

#define SCIF1_SCFSR_DR_SHIFT                    (0u)
#define SCIF1_SCFSR_RDF_SHIFT                   (1u)
#define SCIF1_SCFSR_PER_SHIFT                   (2u)
#define SCIF1_SCFSR_FER_SHIFT                   (3u)
#define SCIF1_SCFSR_BRK_SHIFT                   (4u)
#define SCIF1_SCFSR_TDFE_SHIFT                  (5u)
#define SCIF1_SCFSR_TEND_SHIFT                  (6u)
#define SCIF1_SCFSR_ER_SHIFT                    (7u)
#define SCIF1_SCFSR_FERN_SHIFT                  (8u)
#define SCIF1_SCFSR_PERN_SHIFT                  (12u)

#define SCIF1_SCFRDR_D_SHIFT                    (0u)

#define SCIF1_SCFCR_LOOP_SHIFT                  (0u)
#define SCIF1_SCFCR_RFRST_SHIFT                 (1u)
#define SCIF1_SCFCR_TFRST_SHIFT                 (2u)
#define SCIF1_SCFCR_MCE_SHIFT                   (3u)
#define SCIF1_SCFCR_TTRG_SHIFT                  (4u)
#define SCIF1_SCFCR_RTRG_SHIFT                  (6u)
#define SCIF1_SCFCR_RSTRG_SHIFT                 (8u)

#define SCIF1_SCFDR_R_SHIFT                     (0u)
#define SCIF1_SCFDR_T_SHIFT                     (8u)

#define SCIF1_SCSPTR_SPB2DT_SHIFT               (0u)
#define SCIF1_SCSPTR_SPB2IO_SHIFT               (1u)
#define SCIF1_SCSPTR_SCKDT_SHIFT                (2u)
#define SCIF1_SCSPTR_SCKIO_SHIFT                (3u)
#define SCIF1_SCSPTR_CTSDT_SHIFT                (4u)
#define SCIF1_SCSPTR_CTSIO_SHIFT                (5u)
#define SCIF1_SCSPTR_RTSDT_SHIFT                (6u)
#define SCIF1_SCSPTR_RTSIO_SHIFT                (7u)

#define SCIF1_SCLSR_ORER_SHIFT                  (0u)

#define SCIF1_SCEMR_ABCS_SHIFT                  (0u)
#define SCIF1_SCEMR_BGDM_SHIFT                  (7u)

/* ---- SCIF2 ---- */
#define SCIF2_SCSMR_CKS_SHIFT                   (0u)
#define SCIF2_SCSMR_STOP_SHIFT                  (3u)
#define SCIF2_SCSMR_OE_SHIFT                    (4u)
#define SCIF2_SCSMR_PE_SHIFT                    (5u)
#define SCIF2_SCSMR_CHR_SHIFT                   (6u)
#define SCIF2_SCSMR_CA_SHIFT                    (7u)

#define SCIF2_SCBRR_D_SHIFT                     (0u)

#define SCIF2_SCSCR_CKE_SHIFT                   (0u)
#define SCIF2_SCSCR_REIE_SHIFT                  (3u)
#define SCIF2_SCSCR_RE_SHIFT                    (4u)
#define SCIF2_SCSCR_TE_SHIFT                    (5u)
#define SCIF2_SCSCR_RIE_SHIFT                   (6u)
#define SCIF2_SCSCR_TIE_SHIFT                   (7u)

#define SCIF2_SCFTDR_D_SHIFT                    (0u)

#define SCIF2_SCFSR_DR_SHIFT                    (0u)
#define SCIF2_SCFSR_RDF_SHIFT                   (1u)
#define SCIF2_SCFSR_PER_SHIFT                   (2u)
#define SCIF2_SCFSR_FER_SHIFT                   (3u)
#define SCIF2_SCFSR_BRK_SHIFT                   (4u)
#define SCIF2_SCFSR_TDFE_SHIFT                  (5u)
#define SCIF2_SCFSR_TEND_SHIFT                  (6u)
#define SCIF2_SCFSR_ER_SHIFT                    (7u)
#define SCIF2_SCFSR_FERN_SHIFT                  (8u)
#define SCIF2_SCFSR_PERN_SHIFT                  (12u)

#define SCIF2_SCFRDR_D_SHIFT                    (0u)

#define SCIF2_SCFCR_LOOP_SHIFT                  (0u)
#define SCIF2_SCFCR_RFRST_SHIFT                 (1u)
#define SCIF2_SCFCR_TFRST_SHIFT                 (2u)
#define SCIF2_SCFCR_MCE_SHIFT                   (3u)
#define SCIF2_SCFCR_TTRG_SHIFT                  (4u)
#define SCIF2_SCFCR_RTRG_SHIFT                  (6u)
#define SCIF2_SCFCR_RSTRG_SHIFT                 (8u)

#define SCIF2_SCFDR_R_SHIFT                     (0u)
#define SCIF2_SCFDR_T_SHIFT                     (8u)

#define SCIF2_SCSPTR_SPB2DT_SHIFT               (0u)
#define SCIF2_SCSPTR_SPB2IO_SHIFT               (1u)
#define SCIF2_SCSPTR_SCKDT_SHIFT                (2u)
#define SCIF2_SCSPTR_SCKIO_SHIFT                (3u)
#define SCIF2_SCSPTR_CTSDT_SHIFT                (4u)
#define SCIF2_SCSPTR_CTSIO_SHIFT                (5u)
#define SCIF2_SCSPTR_RTSDT_SHIFT                (6u)
#define SCIF2_SCSPTR_RTSIO_SHIFT                (7u)

#define SCIF2_SCLSR_ORER_SHIFT                  (0u)

#define SCIF2_SCEMR_ABCS_SHIFT                  (0u)
#define SCIF2_SCEMR_BGDM_SHIFT                  (7u)

/* ---- SCIF3 ---- */
#define SCIF3_SCSMR_CKS_SHIFT                   (0u)
#define SCIF3_SCSMR_STOP_SHIFT                  (3u)
#define SCIF3_SCSMR_OE_SHIFT                    (4u)
#define SCIF3_SCSMR_PE_SHIFT                    (5u)
#define SCIF3_SCSMR_CHR_SHIFT                   (6u)
#define SCIF3_SCSMR_CA_SHIFT                    (7u)

#define SCIF3_SCBRR_D_SHIFT                     (0u)

#define SCIF3_SCSCR_CKE_SHIFT                   (0u)
#define SCIF3_SCSCR_REIE_SHIFT                  (3u)
#define SCIF3_SCSCR_RE_SHIFT                    (4u)
#define SCIF3_SCSCR_TE_SHIFT                    (5u)
#define SCIF3_SCSCR_RIE_SHIFT                   (6u)
#define SCIF3_SCSCR_TIE_SHIFT                   (7u)

#define SCIF3_SCFTDR_D_SHIFT                    (0u)

#define SCIF3_SCFSR_DR_SHIFT                    (0u)
#define SCIF3_SCFSR_RDF_SHIFT                   (1u)
#define SCIF3_SCFSR_PER_SHIFT                   (2u)
#define SCIF3_SCFSR_FER_SHIFT                   (3u)
#define SCIF3_SCFSR_BRK_SHIFT                   (4u)
#define SCIF3_SCFSR_TDFE_SHIFT                  (5u)
#define SCIF3_SCFSR_TEND_SHIFT                  (6u)
#define SCIF3_SCFSR_ER_SHIFT                    (7u)
#define SCIF3_SCFSR_FERN_SHIFT                  (8u)
#define SCIF3_SCFSR_PERN_SHIFT                  (12u)

#define SCIF3_SCFRDR_D_SHIFT                    (0u)

#define SCIF3_SCFCR_LOOP_SHIFT                  (0u)
#define SCIF3_SCFCR_RFRST_SHIFT                 (1u)
#define SCIF3_SCFCR_TFRST_SHIFT                 (2u)
#define SCIF3_SCFCR_MCE_SHIFT                   (3u)
#define SCIF3_SCFCR_TTRG_SHIFT                  (4u)
#define SCIF3_SCFCR_RTRG_SHIFT                  (6u)
#define SCIF3_SCFCR_RSTRG_SHIFT                 (8u)

#define SCIF3_SCFDR_R_SHIFT                     (0u)
#define SCIF3_SCFDR_T_SHIFT                     (8u)

#define SCIF3_SCSPTR_SPB2DT_SHIFT               (0u)
#define SCIF3_SCSPTR_SPB2IO_SHIFT               (1u)
#define SCIF3_SCSPTR_SCKDT_SHIFT                (2u)
#define SCIF3_SCSPTR_SCKIO_SHIFT                (3u)
#define SCIF3_SCSPTR_CTSDT_SHIFT                (4u)
#define SCIF3_SCSPTR_CTSIO_SHIFT                (5u)
#define SCIF3_SCSPTR_RTSDT_SHIFT                (6u)
#define SCIF3_SCSPTR_RTSIO_SHIFT                (7u)

#define SCIF3_SCLSR_ORER_SHIFT                  (0u)

#define SCIF3_SCEMR_ABCS_SHIFT                  (0u)
#define SCIF3_SCEMR_BGDM_SHIFT                  (7u)

/* ---- SCIF4 ---- */
#define SCIF4_SCSMR_CKS_SHIFT                   (0u)
#define SCIF4_SCSMR_STOP_SHIFT                  (3u)
#define SCIF4_SCSMR_OE_SHIFT                    (4u)
#define SCIF4_SCSMR_PE_SHIFT                    (5u)
#define SCIF4_SCSMR_CHR_SHIFT                   (6u)
#define SCIF4_SCSMR_CA_SHIFT                    (7u)

#define SCIF4_SCBRR_D_SHIFT                     (0u)

#define SCIF4_SCSCR_CKE_SHIFT                   (0u)
#define SCIF4_SCSCR_REIE_SHIFT                  (3u)
#define SCIF4_SCSCR_RE_SHIFT                    (4u)
#define SCIF4_SCSCR_TE_SHIFT                    (5u)
#define SCIF4_SCSCR_RIE_SHIFT                   (6u)
#define SCIF4_SCSCR_TIE_SHIFT                   (7u)

#define SCIF4_SCFTDR_D_SHIFT                    (0u)

#define SCIF4_SCFSR_DR_SHIFT                    (0u)
#define SCIF4_SCFSR_RDF_SHIFT                   (1u)
#define SCIF4_SCFSR_PER_SHIFT                   (2u)
#define SCIF4_SCFSR_FER_SHIFT                   (3u)
#define SCIF4_SCFSR_BRK_SHIFT                   (4u)
#define SCIF4_SCFSR_TDFE_SHIFT                  (5u)
#define SCIF4_SCFSR_TEND_SHIFT                  (6u)
#define SCIF4_SCFSR_ER_SHIFT                    (7u)
#define SCIF4_SCFSR_FERN_SHIFT                  (8u)
#define SCIF4_SCFSR_PERN_SHIFT                  (12u)

#define SCIF4_SCFRDR_D_SHIFT                    (0u)

#define SCIF4_SCFCR_LOOP_SHIFT                  (0u)
#define SCIF4_SCFCR_RFRST_SHIFT                 (1u)
#define SCIF4_SCFCR_TFRST_SHIFT                 (2u)
#define SCIF4_SCFCR_MCE_SHIFT                   (3u)
#define SCIF4_SCFCR_TTRG_SHIFT                  (4u)
#define SCIF4_SCFCR_RTRG_SHIFT                  (6u)
#define SCIF4_SCFCR_RSTRG_SHIFT                 (8u)

#define SCIF4_SCFDR_R_SHIFT                     (0u)
#define SCIF4_SCFDR_T_SHIFT                     (8u)

#define SCIF4_SCSPTR_SPB2DT_SHIFT               (0u)
#define SCIF4_SCSPTR_SPB2IO_SHIFT               (1u)
#define SCIF4_SCSPTR_SCKDT_SHIFT                (2u)
#define SCIF4_SCSPTR_SCKIO_SHIFT                (3u)
#define SCIF4_SCSPTR_CTSDT_SHIFT                (4u)
#define SCIF4_SCSPTR_CTSIO_SHIFT                (5u)
#define SCIF4_SCSPTR_RTSDT_SHIFT                (6u)
#define SCIF4_SCSPTR_RTSIO_SHIFT                (7u)

#define SCIF4_SCLSR_ORER_SHIFT                  (0u)

#define SCIF4_SCEMR_ABCS_SHIFT                  (0u)
#define SCIF4_SCEMR_BGDM_SHIFT                  (7u)

/* ---- SCIF5 ---- */
#define SCIF5_SCSMR_CKS_SHIFT                   (0u)
#define SCIF5_SCSMR_STOP_SHIFT                  (3u)
#define SCIF5_SCSMR_OE_SHIFT                    (4u)
#define SCIF5_SCSMR_PE_SHIFT                    (5u)
#define SCIF5_SCSMR_CHR_SHIFT                   (6u)
#define SCIF5_SCSMR_CA_SHIFT                    (7u)

#define SCIF5_SCBRR_D_SHIFT                     (0u)

#define SCIF5_SCSCR_CKE_SHIFT                   (0u)
#define SCIF5_SCSCR_REIE_SHIFT                  (3u)
#define SCIF5_SCSCR_RE_SHIFT                    (4u)
#define SCIF5_SCSCR_TE_SHIFT                    (5u)
#define SCIF5_SCSCR_RIE_SHIFT                   (6u)
#define SCIF5_SCSCR_TIE_SHIFT                   (7u)

#define SCIF5_SCFTDR_D_SHIFT                    (0u)

#define SCIF5_SCFSR_DR_SHIFT                    (0u)
#define SCIF5_SCFSR_RDF_SHIFT                   (1u)
#define SCIF5_SCFSR_PER_SHIFT                   (2u)
#define SCIF5_SCFSR_FER_SHIFT                   (3u)
#define SCIF5_SCFSR_BRK_SHIFT                   (4u)
#define SCIF5_SCFSR_TDFE_SHIFT                  (5u)
#define SCIF5_SCFSR_TEND_SHIFT                  (6u)
#define SCIF5_SCFSR_ER_SHIFT                    (7u)
#define SCIF5_SCFSR_FERN_SHIFT                  (8u)
#define SCIF5_SCFSR_PERN_SHIFT                  (12u)

#define SCIF5_SCFRDR_D_SHIFT                    (0u)

#define SCIF5_SCFCR_LOOP_SHIFT                  (0u)
#define SCIF5_SCFCR_RFRST_SHIFT                 (1u)
#define SCIF5_SCFCR_TFRST_SHIFT                 (2u)
#define SCIF5_SCFCR_MCE_SHIFT                   (3u)
#define SCIF5_SCFCR_TTRG_SHIFT                  (4u)
#define SCIF5_SCFCR_RTRG_SHIFT                  (6u)
#define SCIF5_SCFCR_RSTRG_SHIFT                 (8u)

#define SCIF5_SCFDR_R_SHIFT                     (0u)
#define SCIF5_SCFDR_T_SHIFT                     (8u)

#define SCIF5_SCSPTR_SPB2DT_SHIFT               (0u)
#define SCIF5_SCSPTR_SPB2IO_SHIFT               (1u)
#define SCIF5_SCSPTR_SCKDT_SHIFT                (2u)
#define SCIF5_SCSPTR_SCKIO_SHIFT                (3u)
#define SCIF5_SCSPTR_CTSDT_SHIFT                (4u)
#define SCIF5_SCSPTR_CTSIO_SHIFT                (5u)
#define SCIF5_SCSPTR_RTSDT_SHIFT                (6u)
#define SCIF5_SCSPTR_RTSIO_SHIFT                (7u)

#define SCIF5_SCLSR_ORER_SHIFT                  (0u)

#define SCIF5_SCEMR_ABCS_SHIFT                  (0u)
#define SCIF5_SCEMR_BGDM_SHIFT                  (7u)

/* ---- SCIF6 ---- */
#define SCIF6_SCSMR_CKS_SHIFT                   (0u)
#define SCIF6_SCSMR_STOP_SHIFT                  (3u)
#define SCIF6_SCSMR_OE_SHIFT                    (4u)
#define SCIF6_SCSMR_PE_SHIFT                    (5u)
#define SCIF6_SCSMR_CHR_SHIFT                   (6u)
#define SCIF6_SCSMR_CA_SHIFT                    (7u)

#define SCIF6_SCBRR_D_SHIFT                     (0u)

#define SCIF6_SCSCR_CKE_SHIFT                   (0u)
#define SCIF6_SCSCR_REIE_SHIFT                  (3u)
#define SCIF6_SCSCR_RE_SHIFT                    (4u)
#define SCIF6_SCSCR_TE_SHIFT                    (5u)
#define SCIF6_SCSCR_RIE_SHIFT                   (6u)
#define SCIF6_SCSCR_TIE_SHIFT                   (7u)

#define SCIF6_SCFTDR_D_SHIFT                    (0u)

#define SCIF6_SCFSR_DR_SHIFT                    (0u)
#define SCIF6_SCFSR_RDF_SHIFT                   (1u)
#define SCIF6_SCFSR_PER_SHIFT                   (2u)
#define SCIF6_SCFSR_FER_SHIFT                   (3u)
#define SCIF6_SCFSR_BRK_SHIFT                   (4u)
#define SCIF6_SCFSR_TDFE_SHIFT                  (5u)
#define SCIF6_SCFSR_TEND_SHIFT                  (6u)
#define SCIF6_SCFSR_ER_SHIFT                    (7u)
#define SCIF6_SCFSR_FERN_SHIFT                  (8u)
#define SCIF6_SCFSR_PERN_SHIFT                  (12u)

#define SCIF6_SCFRDR_D_SHIFT                    (0u)

#define SCIF6_SCFCR_LOOP_SHIFT                  (0u)
#define SCIF6_SCFCR_RFRST_SHIFT                 (1u)
#define SCIF6_SCFCR_TFRST_SHIFT                 (2u)
#define SCIF6_SCFCR_MCE_SHIFT                   (3u)
#define SCIF6_SCFCR_TTRG_SHIFT                  (4u)
#define SCIF6_SCFCR_RTRG_SHIFT                  (6u)
#define SCIF6_SCFCR_RSTRG_SHIFT                 (8u)

#define SCIF6_SCFDR_R_SHIFT                     (0u)
#define SCIF6_SCFDR_T_SHIFT                     (8u)

#define SCIF6_SCSPTR_SPB2DT_SHIFT               (0u)
#define SCIF6_SCSPTR_SPB2IO_SHIFT               (1u)
#define SCIF6_SCSPTR_SCKDT_SHIFT                (2u)
#define SCIF6_SCSPTR_SCKIO_SHIFT                (3u)
#define SCIF6_SCSPTR_CTSDT_SHIFT                (4u)
#define SCIF6_SCSPTR_CTSIO_SHIFT                (5u)
#define SCIF6_SCSPTR_RTSDT_SHIFT                (6u)
#define SCIF6_SCSPTR_RTSIO_SHIFT                (7u)

#define SCIF6_SCLSR_ORER_SHIFT                  (0u)

#define SCIF6_SCEMR_ABCS_SHIFT                  (0u)
#define SCIF6_SCEMR_BGDM_SHIFT                  (7u)

/* ---- SCIF7 ---- */
#define SCIF7_SCSMR_CKS_SHIFT                   (0u)
#define SCIF7_SCSMR_STOP_SHIFT                  (3u)
#define SCIF7_SCSMR_OE_SHIFT                    (4u)
#define SCIF7_SCSMR_PE_SHIFT                    (5u)
#define SCIF7_SCSMR_CHR_SHIFT                   (6u)
#define SCIF7_SCSMR_CA_SHIFT                    (7u)

#define SCIF7_SCBRR_D_SHIFT                     (0u)

#define SCIF7_SCSCR_CKE_SHIFT                   (0u)
#define SCIF7_SCSCR_REIE_SHIFT                  (3u)
#define SCIF7_SCSCR_RE_SHIFT                    (4u)
#define SCIF7_SCSCR_TE_SHIFT                    (5u)
#define SCIF7_SCSCR_RIE_SHIFT                   (6u)
#define SCIF7_SCSCR_TIE_SHIFT                   (7u)

#define SCIF7_SCFTDR_D_SHIFT                    (0u)

#define SCIF7_SCFSR_DR_SHIFT                    (0u)
#define SCIF7_SCFSR_RDF_SHIFT                   (1u)
#define SCIF7_SCFSR_PER_SHIFT                   (2u)
#define SCIF7_SCFSR_FER_SHIFT                   (3u)
#define SCIF7_SCFSR_BRK_SHIFT                   (4u)
#define SCIF7_SCFSR_TDFE_SHIFT                  (5u)
#define SCIF7_SCFSR_TEND_SHIFT                  (6u)
#define SCIF7_SCFSR_ER_SHIFT                    (7u)
#define SCIF7_SCFSR_FERN_SHIFT                  (8u)
#define SCIF7_SCFSR_PERN_SHIFT                  (12u)

#define SCIF7_SCFRDR_D_SHIFT                    (0u)

#define SCIF7_SCFCR_LOOP_SHIFT                  (0u)
#define SCIF7_SCFCR_RFRST_SHIFT                 (1u)
#define SCIF7_SCFCR_TFRST_SHIFT                 (2u)
#define SCIF7_SCFCR_MCE_SHIFT                   (3u)
#define SCIF7_SCFCR_TTRG_SHIFT                  (4u)
#define SCIF7_SCFCR_RTRG_SHIFT                  (6u)
#define SCIF7_SCFCR_RSTRG_SHIFT                 (8u)

#define SCIF7_SCFDR_R_SHIFT                     (0u)
#define SCIF7_SCFDR_T_SHIFT                     (8u)

#define SCIF7_SCSPTR_SPB2DT_SHIFT               (0u)
#define SCIF7_SCSPTR_SPB2IO_SHIFT               (1u)
#define SCIF7_SCSPTR_SCKDT_SHIFT                (2u)
#define SCIF7_SCSPTR_SCKIO_SHIFT                (3u)
#define SCIF7_SCSPTR_CTSDT_SHIFT                (4u)
#define SCIF7_SCSPTR_CTSIO_SHIFT                (5u)
#define SCIF7_SCSPTR_RTSDT_SHIFT                (6u)
#define SCIF7_SCSPTR_RTSIO_SHIFT                (7u)

#define SCIF7_SCLSR_ORER_SHIFT                  (0u)

#define SCIF7_SCEMR_ABCS_SHIFT                  (0u)
#define SCIF7_SCEMR_BGDM_SHIFT                  (7u)

/* ---- SCIFn ---- */
#define SCIFn_SCSMR_CKS_SHIFT                   (0u)
#define SCIFn_SCSMR_STOP_SHIFT                  (3u)
#define SCIFn_SCSMR_OE_SHIFT                    (4u)
#define SCIFn_SCSMR_PE_SHIFT                    (5u)
#define SCIFn_SCSMR_CHR_SHIFT                   (6u)
#define SCIFn_SCSMR_CA_SHIFT                    (7u)

#define SCIFn_SCBRR_D_SHIFT                     (0u)

#define SCIFn_SCSCR_CKE_SHIFT                   (0u)
#define SCIFn_SCSCR_REIE_SHIFT                  (3u)
#define SCIFn_SCSCR_RE_SHIFT                    (4u)
#define SCIFn_SCSCR_TE_SHIFT                    (5u)
#define SCIFn_SCSCR_RIE_SHIFT                   (6u)
#define SCIFn_SCSCR_TIE_SHIFT                   (7u)

#define SCIFn_SCFTDR_D_SHIFT                    (0u)

#define SCIFn_SCFSR_DR_SHIFT                    (0u)
#define SCIFn_SCFSR_RDF_SHIFT                   (1u)
#define SCIFn_SCFSR_PER_SHIFT                   (2u)
#define SCIFn_SCFSR_FER_SHIFT                   (3u)
#define SCIFn_SCFSR_BRK_SHIFT                   (4u)
#define SCIFn_SCFSR_TDFE_SHIFT                  (5u)
#define SCIFn_SCFSR_TEND_SHIFT                  (6u)
#define SCIFn_SCFSR_ER_SHIFT                    (7u)
#define SCIFn_SCFSR_FERN_SHIFT                  (8u)
#define SCIFn_SCFSR_PERN_SHIFT                  (12u)

#define SCIFn_SCFRDR_D_SHIFT                    (0u)

#define SCIFn_SCFCR_LOOP_SHIFT                  (0u)
#define SCIFn_SCFCR_RFRST_SHIFT                 (1u)
#define SCIFn_SCFCR_TFRST_SHIFT                 (2u)
#define SCIFn_SCFCR_MCE_SHIFT                   (3u)
#define SCIFn_SCFCR_TTRG_SHIFT                  (4u)
#define SCIFn_SCFCR_RTRG_SHIFT                  (6u)
#define SCIFn_SCFCR_RSTRG_SHIFT                 (8u)

#define SCIFn_SCFDR_R_SHIFT                     (0u)
#define SCIFn_SCFDR_T_SHIFT                     (8u)

#define SCIFn_SCSPTR_SPB2DT_SHIFT               (0u)
#define SCIFn_SCSPTR_SPB2IO_SHIFT               (1u)
#define SCIFn_SCSPTR_SCKDT_SHIFT                (2u)
#define SCIFn_SCSPTR_SCKIO_SHIFT                (3u)
#define SCIFn_SCSPTR_CTSDT_SHIFT                (4u)
#define SCIFn_SCSPTR_CTSIO_SHIFT                (5u)
#define SCIFn_SCSPTR_RTSDT_SHIFT                (6u)
#define SCIFn_SCSPTR_RTSIO_SHIFT                (7u)

#define SCIFn_SCLSR_ORER_SHIFT                  (0u)

#define SCIFn_SCEMR_ABCS_SHIFT                  (0u)
#define SCIFn_SCEMR_BGDM_SHIFT                  (7u)


#endif /* SCIF_IOBITMASK_H */

/* End of File */
