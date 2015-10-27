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
* File Name   : riic_iobitmask.h
* $Rev: 1114 $
* $Date:: 2014-07-09 14:56:39 +0900#$
* Description : RIIC register define header
*******************************************************************************/
#ifndef RIIC_IOBITMASK_H
#define RIIC_IOBITMASK_H


/* ==== Mask values for IO registers ==== */
#define RIICn_RIICnCR1_SDAI                     (0x01u)
#define RIICn_RIICnCR1_SCLI                     (0x02u)
#define RIICn_RIICnCR1_SDAO                     (0x04u)
#define RIICn_RIICnCR1_SCLO                     (0x08u)
#define RIICn_RIICnCR1_SOWP                     (0x10u)
#define RIICn_RIICnCR1_CLO                      (0x20u)
#define RIICn_RIICnCR1_IICRST                   (0x40u)
#define RIICn_RIICnCR1_ICE                      (0x80u)

#define RIICn_RIICnCR2_ST                       (0x02u)
#define RIICn_RIICnCR2_RS                       (0x04u)
#define RIICn_RIICnCR2_SP                       (0x08u)
#define RIICn_RIICnCR2_TRS                      (0x20u)
#define RIICn_RIICnCR2_MST                      (0x40u)
#define RIICn_RIICnCR2_BBSY                     (0x80u)

#define RIICn_RIICnMR1_BC                       (0x07u)
#define RIICn_RIICnMR1_BCWP                     (0x08u)
#define RIICn_RIICnMR1_CKS                      (0x70u)
#define RIICn_RIICnMR1_MTWP                     (0x80u)

#define RIICn_RIICnMR2_TMOS                     (0x01u)
#define RIICn_RIICnMR2_TMOL                     (0x02u)
#define RIICn_RIICnMR2_TMOH                     (0x04u)
#define RIICn_RIICnMR2_SDDL                     (0x70u)
#define RIICn_RIICnMR2_DLCS                     (0x80u)

#define RIICn_RIICnMR3_NF                       (0x03u)
#define RIICn_RIICnMR3_ACKBR                    (0x04u)
#define RIICn_RIICnMR3_ACKBT                    (0x08u)
#define RIICn_RIICnMR3_ACKWP                    (0x10u)
#define RIICn_RIICnMR3_RDRFS                    (0x20u)
#define RIICn_RIICnMR3_WAIT                     (0x40u)
#define RIICn_RIICnMR3_SMBS                     (0x80u)

#define RIICn_RIICnFER_TMOE                     (0x01u)
#define RIICn_RIICnFER_MALE                     (0x02u)
#define RIICn_RIICnFER_NALE                     (0x04u)
#define RIICn_RIICnFER_SALE                     (0x08u)
#define RIICn_RIICnFER_NACKE                    (0x10u)
#define RIICn_RIICnFER_NFE                      (0x20u)
#define RIICn_RIICnFER_SCLE                     (0x40u)
#define RIICn_RIICnFER_FMPE                     (0x80u)

#define RIICn_RIICnSER_SAR0E                    (0x01u)
#define RIICn_RIICnSER_SAR1E                    (0x02u)
#define RIICn_RIICnSER_SAR2E                    (0x04u)
#define RIICn_RIICnSER_GCAE                     (0x08u)
#define RIICn_RIICnSER_DIDE                     (0x20u)
#define RIICn_RIICnSER_HOAE                     (0x80u)

#define RIICn_RIICnIER_TMOIE                    (0x01u)
#define RIICn_RIICnIER_ALIE                     (0x02u)
#define RIICn_RIICnIER_STIE                     (0x04u)
#define RIICn_RIICnIER_SPIE                     (0x08u)
#define RIICn_RIICnIER_NAKIE                    (0x10u)
#define RIICn_RIICnIER_RIE                      (0x20u)
#define RIICn_RIICnIER_TEIE                     (0x40u)
#define RIICn_RIICnIER_TIE                      (0x80u)

#define RIICn_RIICnSR1_AAS0                     (0x01u)
#define RIICn_RIICnSR1_AAS1                     (0x02u)
#define RIICn_RIICnSR1_AAS2                     (0x04u)
#define RIICn_RIICnSR1_GCA                      (0x08u)
#define RIICn_RIICnSR1_DID                      (0x20u)
#define RIICn_RIICnSR1_HOA                      (0x80u)

#define RIICn_RIICnSR2_TMOF                     (0x01u)
#define RIICn_RIICnSR2_AL                       (0x02u)
#define RIICn_RIICnSR2_START                    (0x04u)
#define RIICn_RIICnSR2_STOP                     (0x08u)
#define RIICn_RIICnSR2_NACKF                    (0x10u)
#define RIICn_RIICnSR2_RDRF                     (0x20u)
#define RIICn_RIICnSR2_TEND                     (0x40u)
#define RIICn_RIICnSR2_TDRE                     (0x80u)

#define RIICn_RIICnSAR0_SVA0                    (0x0001u)
#define RIICn_RIICnSAR0_SVA                     (0x03FEu)
#define RIICn_RIICnSAR0_FSy                     (0x8000u)

#define RIICn_RIICnSAR1_SVA0                    (0x0001u)
#define RIICn_RIICnSAR1_SVA                     (0x03FEu)
#define RIICn_RIICnSAR1_FSy                     (0x8000u)

#define RIICn_RIICnSAR2_SVA0                    (0x0001u)
#define RIICn_RIICnSAR2_SVA                     (0x03FEu)
#define RIICn_RIICnSAR2_FSy                     (0x8000u)

#define RIICn_RIICnBRL_BRL                      (0x1Fu)

#define RIICn_RIICnBRH_BRH                      (0x1Fu)

#define RIICn_RIICnDRT_DRT                      (0xFFu)

#define RIICn_RIICnDRR_DRR                      (0xFFu)


/* ==== Shift values for IO registers ==== */
#define RIICn_RIICnCR1_SDAI_SHIFT               (0u)
#define RIICn_RIICnCR1_SCLI_SHIFT               (1u)
#define RIICn_RIICnCR1_SDAO_SHIFT               (2u)
#define RIICn_RIICnCR1_SCLO_SHIFT               (3u)
#define RIICn_RIICnCR1_SOWP_SHIFT               (4u)
#define RIICn_RIICnCR1_CLO_SHIFT                (5u)
#define RIICn_RIICnCR1_IICRST_SHIFT             (6u)
#define RIICn_RIICnCR1_ICE_SHIFT                (7u)

#define RIICn_RIICnCR2_ST_SHIFT                 (1u)
#define RIICn_RIICnCR2_RS_SHIFT                 (2u)
#define RIICn_RIICnCR2_SP_SHIFT                 (3u)
#define RIICn_RIICnCR2_TRS_SHIFT                (5u)
#define RIICn_RIICnCR2_MST_SHIFT                (6u)
#define RIICn_RIICnCR2_BBSY_SHIFT               (7u)

#define RIICn_RIICnMR1_BC_SHIFT                 (0u)
#define RIICn_RIICnMR1_BCWP_SHIFT               (3u)
#define RIICn_RIICnMR1_CKS_SHIFT                (4u)
#define RIICn_RIICnMR1_MTWP_SHIFT               (7u)

#define RIICn_RIICnMR2_TMOS_SHIFT               (0u)
#define RIICn_RIICnMR2_TMOL_SHIFT               (1u)
#define RIICn_RIICnMR2_TMOH_SHIFT               (2u)
#define RIICn_RIICnMR2_SDDL_SHIFT               (4u)
#define RIICn_RIICnMR2_DLCS_SHIFT               (7u)

#define RIICn_RIICnMR3_NF_SHIFT                 (0u)
#define RIICn_RIICnMR3_ACKBR_SHIFT              (2u)
#define RIICn_RIICnMR3_ACKBT_SHIFT              (3u)
#define RIICn_RIICnMR3_ACKWP_SHIFT              (4u)
#define RIICn_RIICnMR3_RDRFS_SHIFT              (5u)
#define RIICn_RIICnMR3_WAIT_SHIFT               (6u)
#define RIICn_RIICnMR3_SMBS_SHIFT               (7u)

#define RIICn_RIICnFER_TMOE_SHIFT               (0u)
#define RIICn_RIICnFER_MALE_SHIFT               (1u)
#define RIICn_RIICnFER_NALE_SHIFT               (2u)
#define RIICn_RIICnFER_SALE_SHIFT               (3u)
#define RIICn_RIICnFER_NACKE_SHIFT              (4u)
#define RIICn_RIICnFER_NFE_SHIFT                (5u)
#define RIICn_RIICnFER_SCLE_SHIFT               (6u)
#define RIICn_RIICnFER_FMPE_SHIFT               (7u)

#define RIICn_RIICnSER_SAR0E_SHIFT              (0u)
#define RIICn_RIICnSER_SAR1E_SHIFT              (1u)
#define RIICn_RIICnSER_SAR2E_SHIFT              (2u)
#define RIICn_RIICnSER_GCAE_SHIFT               (3u)
#define RIICn_RIICnSER_DIDE_SHIFT               (5u)
#define RIICn_RIICnSER_HOAE_SHIFT               (7u)

#define RIICn_RIICnIER_TMOIE_SHIFT              (0u)
#define RIICn_RIICnIER_ALIE_SHIFT               (1u)
#define RIICn_RIICnIER_STIE_SHIFT               (2u)
#define RIICn_RIICnIER_SPIE_SHIFT               (3u)
#define RIICn_RIICnIER_NAKIE_SHIFT              (4u)
#define RIICn_RIICnIER_RIE_SHIFT                (5u)
#define RIICn_RIICnIER_TEIE_SHIFT               (6u)
#define RIICn_RIICnIER_TIE_SHIFT                (7u)

#define RIICn_RIICnSR1_AAS0_SHIFT               (0u)
#define RIICn_RIICnSR1_AAS1_SHIFT               (1u)
#define RIICn_RIICnSR1_AAS2_SHIFT               (2u)
#define RIICn_RIICnSR1_GCA_SHIFT                (3u)
#define RIICn_RIICnSR1_DID_SHIFT                (5u)
#define RIICn_RIICnSR1_HOA_SHIFT                (7u)

#define RIICn_RIICnSR2_TMOF_SHIFT               (0u)
#define RIICn_RIICnSR2_AL_SHIFT                 (1u)
#define RIICn_RIICnSR2_START_SHIFT              (2u)
#define RIICn_RIICnSR2_STOP_SHIFT               (3u)
#define RIICn_RIICnSR2_NACKF_SHIFT              (4u)
#define RIICn_RIICnSR2_RDRF_SHIFT               (5u)
#define RIICn_RIICnSR2_TEND_SHIFT               (6u)
#define RIICn_RIICnSR2_TDRE_SHIFT               (7u)

#define RIICn_RIICnSAR0_SVA0_SHIFT              (0u)
#define RIICn_RIICnSAR0_SVA_SHIFT               (1u)
#define RIICn_RIICnSAR0_FSy_SHIFT               (15u)

#define RIICn_RIICnSAR1_SVA0_SHIFT              (0u)
#define RIICn_RIICnSAR1_SVA_SHIFT               (1u)
#define RIICn_RIICnSAR1_FSy_SHIFT               (15u)

#define RIICn_RIICnSAR2_SVA0_SHIFT              (0u)
#define RIICn_RIICnSAR2_SVA_SHIFT               (1u)
#define RIICn_RIICnSAR2_FSy_SHIFT               (15u)

#define RIICn_RIICnBRL_BRL_SHIFT                (0u)

#define RIICn_RIICnBRH_BRH_SHIFT                (0u)

#define RIICn_RIICnDRT_DRT_SHIFT                (0u)

#define RIICn_RIICnDRR_DRR_SHIFT                (0u)


#endif /* RIIC_IOBITMASK_H */

/* End of File */
