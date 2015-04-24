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
* File Name   : mtu2_iobitmask.h
* $Rev: 1138 $
* $Date:: 2014-08-08 11:03:56 +0900#$
* Description : MTU2 register define header
*******************************************************************************/
#ifndef MTU2_IOBITMASK_H
#define MTU2_IOBITMASK_H


/* ==== Mask values for IO registers ==== */
#define MTU2_TCR_n_TPSC                         (0x07u)
#define MTU2_TCR_n_CKEG                         (0x18u)
#define MTU2_TCR_n_CCLR                         (0xE0u)

#define MTU2_TMDR_n_MD                          (0x0Fu)

#define MTU2_TIOR_2_IOA                         (0x0Fu)
#define MTU2_TIOR_2_IOB                         (0xF0u)

#define MTU2_TIER_n_TGIEA                       (0x01u)
#define MTU2_TIER_n_TGIEB                       (0x02u)
#define MTU2_TIER_n_TCIEV                       (0x10u)
#define MTU2_TIER_2_TCIEU                       (0x20u)
#define MTU2_TIER_n_TTGE                        (0x80u)

#define MTU2_TSR_n_TGFA                         (0x01u)
#define MTU2_TSR_n_TGFB                         (0x02u)
#define MTU2_TSR_n_TCFV                         (0x10u)
#define MTU2_TSR_2_TCFU                         (0x20u)
#define MTU2_TSR_2_TCFD                         (0x80u)

#define MTU2_TCNT_n_D                           (0xFFFFu)

#define MTU2_TGRA_n_D                           (0xFFFFu)

#define MTU2_TGRB_n_D                           (0xFFFFu)

#define MTU2_TMDR_3_BFA                         (0x10u)
#define MTU2_TMDR_3_BFB                         (0x20u)

#define MTU2_TMDR_4_BFA                         (0x10u)
#define MTU2_TMDR_4_BFB                         (0x20u)

#define MTU2_TIORH_3_IOA                        (0x0Fu)
#define MTU2_TIORH_3_IOB                        (0xF0u)

#define MTU2_TIORL_3_IOC                        (0x0Fu)
#define MTU2_TIORL_3_IOD                        (0xF0u)

#define MTU2_TIORH_4_IOA                        (0x0Fu)
#define MTU2_TIORH_4_IOB                        (0xF0u)

#define MTU2_TIORL_4_IOC                        (0x0Fu)
#define MTU2_TIORL_4_IOD                        (0xF0u)

#define MTU2_TIER_3_TGIEC                       (0x04u)
#define MTU2_TIER_3_TGIED                       (0x08u)

#define MTU2_TIER_4_TGIEC                       (0x04u)
#define MTU2_TIER_4_TGIED                       (0x08u)
#define MTU2_TIER_4_TTGE2                       (0x40u)

#define MTU2_TOER_OE3B                          (0x01u)
#define MTU2_TOER_OE4A                          (0x02u)
#define MTU2_TOER_OE4B                          (0x04u)
#define MTU2_TOER_OE3D                          (0x08u)
#define MTU2_TOER_OE4C                          (0x10u)
#define MTU2_TOER_OE4D                          (0x20u)

#define MTU2_TGCR_UF                            (0x01u)
#define MTU2_TGCR_VF                            (0x02u)
#define MTU2_TGCR_WF                            (0x04u)
#define MTU2_TGCR_FB                            (0x08u)
#define MTU2_TGCR_P                             (0x10u)
#define MTU2_TGCR_N                             (0x20u)
#define MTU2_TGCR_BDC                           (0x40u)

#define MTU2_TOCR1_OLSP                         (0x01u)
#define MTU2_TOCR1_OLSN                         (0x02u)
#define MTU2_TOCR1_TOCS                         (0x04u)
#define MTU2_TOCR1_TOCL                         (0x08u)
#define MTU2_TOCR1_PSYE                         (0x40u)

#define MTU2_TOCR2_OLS1P                        (0x01u)
#define MTU2_TOCR2_OLS1N                        (0x02u)
#define MTU2_TOCR2_OLS2P                        (0x04u)
#define MTU2_TOCR2_OLS2N                        (0x08u)
#define MTU2_TOCR2_OLS3P                        (0x10u)
#define MTU2_TOCR2_OLS3N                        (0x20u)
#define MTU2_TOCR2_BF                           (0xC0u)

#define MTU2_TCDR_D                             (0xFFFFu)

#define MTU2_TDDR_D                             (0xFFFFu)

#define MTU2_TCNTS_D                            (0xFFFFu)

#define MTU2_TCBR_D                             (0xFFFFu)

#define MTU2_TGRC_3_D                           (0xFFFFu)

#define MTU2_TGRD_3_D                           (0xFFFFu)

#define MTU2_TGRC_4_D                           (0xFFFFu)

#define MTU2_TGRD_4_D                           (0xFFFFu)

#define MTU2_TSR_3_TGFC                         (0x04u)
#define MTU2_TSR_3_TGFD                         (0x08u)
#define MTU2_TSR_3_TCFD                         (0x80u)

#define MTU2_TSR_4_TGFC                         (0x04u)
#define MTU2_TSR_4_TGFD                         (0x08u)
#define MTU2_TSR_4_TCFD                         (0x80u)

#define MTU2_TITCR_4VCOR                        (0x07u)
#define MTU2_TITCR_T4VEN                        (0x08u)
#define MTU2_TITCR_3ACOR                        (0x70u)
#define MTU2_TITCR_T3AEN                        (0x80u)

#define MTU2_TITCNT_4VCNT                       (0x07u)
#define MTU2_TITCNT_3ACNT                       (0x70u)

#define MTU2_TBTER_BTE                          (0x03u)

#define MTU2_TDER_TDER                          (0x01u)

#define MTU2_TOLBR_OLS1P                        (0x01u)
#define MTU2_TOLBR_OLS1N                        (0x02u)
#define MTU2_TOLBR_OLS2P                        (0x04u)
#define MTU2_TOLBR_OLS2N                        (0x08u)
#define MTU2_TOLBR_OLS3P                        (0x10u)
#define MTU2_TOLBR_OLS3N                        (0x20u)

#define MTU2_TBTM_3_TTSA                        (0x01u)
#define MTU2_TBTM_3_TTSB                        (0x02u)

#define MTU2_TBTM_4_TTSA                        (0x01u)
#define MTU2_TBTM_4_TTSB                        (0x02u)

#define MTU2_TADCR_ITB4VE                       (0x0001u)
#define MTU2_TADCR_ITB3AE                       (0x0002u)
#define MTU2_TADCR_ITA4VE                       (0x0004u)
#define MTU2_TADCR_ITA3AE                       (0x0008u)
#define MTU2_TADCR_DT4BE                        (0x0010u)
#define MTU2_TADCR_UT4BE                        (0x0020u)
#define MTU2_TADCR_DT4AE                        (0x0040u)
#define MTU2_TADCR_UT4AE                        (0x0080u)
#define MTU2_TADCR_BF                           (0xC000u)

#define MTU2_TADCORA_4_D                        (0xFFFFu)

#define MTU2_TADCORB_4_D                        (0xFFFFu)

#define MTU2_TADCOBRA_4_D                       (0xFFFFu)

#define MTU2_TADCOBRB_4_D                       (0xFFFFu)

#define MTU2_TWCR_WRE                           (0x01u)
#define MTU2_TWCR_CCE                           (0x80u)

#define MTU2_TSTR_CST0                          (0x01u)
#define MTU2_TSTR_CST1                          (0x02u)
#define MTU2_TSTR_CST2                          (0x04u)
#define MTU2_TSTR_CST3                          (0x40u)
#define MTU2_TSTR_CST4                          (0x80u)

#define MTU2_TSYR_SYNC0                         (0x01u)
#define MTU2_TSYR_SYNC1                         (0x02u)
#define MTU2_TSYR_SYNC2                         (0x04u)
#define MTU2_TSYR_SYNC3                         (0x40u)
#define MTU2_TSYR_SYNC4                         (0x80u)

#define MTU2_TRWER_RWE                          (0x01u)

#define MTU2_TMDR_0_BFA                         (0x10u)
#define MTU2_TMDR_0_BFB                         (0x20u)
#define MTU2_TMDR_0_BFE                         (0x40u)

#define MTU2_TIORH_0_IOA                        (0x0Fu)
#define MTU2_TIORH_0_IOB                        (0xF0u)

#define MTU2_TIORL_0_IOC                        (0x0Fu)
#define MTU2_TIORL_0_IOD                        (0xF0u)

#define MTU2_TIER_0_TGIEC                       (0x04u)
#define MTU2_TIER_0_TGIED                       (0x08u)

#define MTU2_TSR_0_TGFC                         (0x04u)
#define MTU2_TSR_0_TGFD                         (0x08u)

#define MTU2_TGRC_0_D                           (0xFFFFu)

#define MTU2_TGRD_0_D                           (0xFFFFu)

#define MTU2_TGRE_0_D                           (0xFFFFu)

#define MTU2_TGRF_0_D                           (0xFFFFu)

#define MTU2_TIER2_0_TGIEE                      (0x01u)
#define MTU2_TIER2_0_TGIEF                      (0x02u)

#define MTU2_TSR2_0_TGFE                        (0x01u)
#define MTU2_TSR2_0_TGFF                        (0x02u)

#define MTU2_TBTM_0_TTSA                        (0x01u)
#define MTU2_TBTM_0_TTSB                        (0x02u)
#define MTU2_TBTM_0_TTSE                        (0x04u)

#define MTU2_TIOR_1_IOA                         (0x0Fu)
#define MTU2_TIOR_1_IOB                         (0xF0u)

#define MTU2_TIER_1_TCIEU                       (0x20u)

#define MTU2_TSR_1_TCFU                         (0x20u)
#define MTU2_TSR_1_TCFD                         (0x80u)

#define MTU2_TICCR_I1AE                         (0x01u)
#define MTU2_TICCR_I1BE                         (0x02u)
#define MTU2_TICCR_I2AE                         (0x04u)
#define MTU2_TICCR_I2BE                         (0x08u)


/* ==== Shift values for IO registers ==== */
#define MTU2_TCR_n_TPSC_SHIFT                   (0u)
#define MTU2_TCR_n_CKEG_SHIFT                   (3u)
#define MTU2_TCR_n_CCLR_SHIFT                   (5u)

#define MTU2_TMDR_n_MD_SHIFT                    (0u)

#define MTU2_TIOR_2_IOA_SHIFT                   (0u)
#define MTU2_TIOR_2_IOB_SHIFT                   (4u)

#define MTU2_TIER_n_TGIEA_SHIFT                 (0u)
#define MTU2_TIER_n_TGIEB_SHIFT                 (1u)
#define MTU2_TIER_n_TCIEV_SHIFT                 (4u)
#define MTU2_TIER_2_TCIEU_SHIFT                 (5u)
#define MTU2_TIER_n_TTGE_SHIFT                  (7u)

#define MTU2_TSR_n_TGFA_SHIFT                   (0u)
#define MTU2_TSR_n_TGFB_SHIFT                   (1u)
#define MTU2_TSR_n_TCFV_SHIFT                   (4u)
#define MTU2_TSR_2_TCFU_SHIFT                   (5u)
#define MTU2_TSR_2_TCFD_SHIFT                   (7u)

#define MTU2_TCNT_n_D_SHIFT                     (0u)

#define MTU2_TGRA_n_D_SHIFT                     (0u)

#define MTU2_TGRB_n_D_SHIFT                     (0u)

#define MTU2_TMDR_3_BFA_SHIFT                   (4u)
#define MTU2_TMDR_3_BFB_SHIFT                   (5u)

#define MTU2_TMDR_4_BFA_SHIFT                   (4u)
#define MTU2_TMDR_4_BFB_SHIFT                   (5u)

#define MTU2_TIORH_3_IOA_SHIFT                  (0u)
#define MTU2_TIORH_3_IOB_SHIFT                  (4u)

#define MTU2_TIORL_3_IOC_SHIFT                  (0u)
#define MTU2_TIORL_3_IOD_SHIFT                  (4u)

#define MTU2_TIORH_4_IOA_SHIFT                  (0u)
#define MTU2_TIORH_4_IOB_SHIFT                  (4u)

#define MTU2_TIORL_4_IOC_SHIFT                  (0u)
#define MTU2_TIORL_4_IOD_SHIFT                  (4u)

#define MTU2_TIER_3_TGIEC_SHIFT                 (2u)
#define MTU2_TIER_3_TGIED_SHIFT                 (3u)

#define MTU2_TIER_4_TGIEC_SHIFT                 (2u)
#define MTU2_TIER_4_TGIED_SHIFT                 (3u)
#define MTU2_TIER_4_TTGE2_SHIFT                 (6u)

#define MTU2_TOER_OE3B_SHIFT                    (0u)
#define MTU2_TOER_OE4A_SHIFT                    (1u)
#define MTU2_TOER_OE4B_SHIFT                    (2u)
#define MTU2_TOER_OE3D_SHIFT                    (3u)
#define MTU2_TOER_OE4C_SHIFT                    (4u)
#define MTU2_TOER_OE4D_SHIFT                    (5u)

#define MTU2_TGCR_UF_SHIFT                      (0u)
#define MTU2_TGCR_VF_SHIFT                      (1u)
#define MTU2_TGCR_WF_SHIFT                      (2u)
#define MTU2_TGCR_FB_SHIFT                      (3u)
#define MTU2_TGCR_P_SHIFT                       (4u)
#define MTU2_TGCR_N_SHIFT                       (5u)
#define MTU2_TGCR_BDC_SHIFT                     (6u)

#define MTU2_TOCR1_OLSP_SHIFT                   (0u)
#define MTU2_TOCR1_OLSN_SHIFT                   (1u)
#define MTU2_TOCR1_TOCS_SHIFT                   (2u)
#define MTU2_TOCR1_TOCL_SHIFT                   (3u)
#define MTU2_TOCR1_PSYE_SHIFT                   (6u)

#define MTU2_TOCR2_OLS1P_SHIFT                  (0u)
#define MTU2_TOCR2_OLS1N_SHIFT                  (1u)
#define MTU2_TOCR2_OLS2P_SHIFT                  (2u)
#define MTU2_TOCR2_OLS2N_SHIFT                  (3u)
#define MTU2_TOCR2_OLS3P_SHIFT                  (4u)
#define MTU2_TOCR2_OLS3N_SHIFT                  (5u)
#define MTU2_TOCR2_BF_SHIFT                     (6u)

#define MTU2_TCDR_D_SHIFT                       (0u)

#define MTU2_TDDR_D_SHIFT                       (0u)

#define MTU2_TCNTS_D_SHIFT                      (0u)

#define MTU2_TCBR_D_SHIFT                       (0u)

#define MTU2_TGRC_3_D_SHIFT                     (0u)

#define MTU2_TGRD_3_D_SHIFT                     (0u)

#define MTU2_TGRC_4_D_SHIFT                     (0u)

#define MTU2_TGRD_4_D_SHIFT                     (0u)

#define MTU2_TSR_3_TGFC_SHIFT                   (2u)
#define MTU2_TSR_3_TGFD_SHIFT                   (3u)
#define MTU2_TSR_3_TCFD_SHIFT                   (7u)

#define MTU2_TSR_4_TGFC_SHIFT                   (2u)
#define MTU2_TSR_4_TGFD_SHIFT                   (3u)
#define MTU2_TSR_4_TCFD_SHIFT                   (7u)

#define MTU2_TITCR_4VCOR_SHIFT                  (0u)
#define MTU2_TITCR_T4VEN_SHIFT                  (3u)
#define MTU2_TITCR_3ACOR_SHIFT                  (4u)
#define MTU2_TITCR_T3AEN_SHIFT                  (7u)

#define MTU2_TITCNT_4VCNT_SHIFT                 (0u)
#define MTU2_TITCNT_3ACNT_SHIFT                 (4u)

#define MTU2_TBTER_BTE_SHIFT                    (0u)

#define MTU2_TDER_TDER_SHIFT                    (0u)

#define MTU2_TOLBR_OLS1P_SHIFT                  (0u)
#define MTU2_TOLBR_OLS1N_SHIFT                  (1u)
#define MTU2_TOLBR_OLS2P_SHIFT                  (2u)
#define MTU2_TOLBR_OLS2N_SHIFT                  (3u)
#define MTU2_TOLBR_OLS3P_SHIFT                  (4u)
#define MTU2_TOLBR_OLS3N_SHIFT                  (5u)

#define MTU2_TBTM_3_TTSA_SHIFT                  (0u)
#define MTU2_TBTM_3_TTSB_SHIFT                  (1u)

#define MTU2_TBTM_4_TTSA_SHIFT                  (0u)
#define MTU2_TBTM_4_TTSB_SHIFT                  (1u)

#define MTU2_TADCR_ITB4VE_SHIFT                 (0u)
#define MTU2_TADCR_ITB3AE_SHIFT                 (1u)
#define MTU2_TADCR_ITA4VE_SHIFT                 (2u)
#define MTU2_TADCR_ITA3AE_SHIFT                 (3u)
#define MTU2_TADCR_DT4BE_SHIFT                  (4u)
#define MTU2_TADCR_UT4BE_SHIFT                  (5u)
#define MTU2_TADCR_DT4AE_SHIFT                  (6u)
#define MTU2_TADCR_UT4AE_SHIFT                  (7u)
#define MTU2_TADCR_BF_SHIFT                     (14u)

#define MTU2_TADCORA_4_D_SHIFT                  (0u)

#define MTU2_TADCORB_4_D_SHIFT                  (0u)

#define MTU2_TADCOBRA_4_D_SHIFT                 (0u)

#define MTU2_TADCOBRB_4_D_SHIFT                 (0u)

#define MTU2_TWCR_WRE_SHIFT                     (0u)
#define MTU2_TWCR_CCE_SHIFT                     (7u)

#define MTU2_TSTR_CST0_SHIFT                    (0u)
#define MTU2_TSTR_CST1_SHIFT                    (1u)
#define MTU2_TSTR_CST2_SHIFT                    (2u)
#define MTU2_TSTR_CST3_SHIFT                    (6u)
#define MTU2_TSTR_CST4_SHIFT                    (7u)

#define MTU2_TSYR_SYNC0_SHIFT                   (0u)
#define MTU2_TSYR_SYNC1_SHIFT                   (1u)
#define MTU2_TSYR_SYNC2_SHIFT                   (2u)
#define MTU2_TSYR_SYNC3_SHIFT                   (6u)
#define MTU2_TSYR_SYNC4_SHIFT                   (7u)

#define MTU2_TRWER_RWE_SHIFT                    (0u)

#define MTU2_TMDR_0_BFA_SHIFT                   (4u)
#define MTU2_TMDR_0_BFB_SHIFT                   (5u)
#define MTU2_TMDR_0_BFE_SHIFT                   (6u)

#define MTU2_TIORH_0_IOA_SHIFT                  (0u)
#define MTU2_TIORH_0_IOB_SHIFT                  (4u)

#define MTU2_TIORL_0_IOC_SHIFT                  (0u)
#define MTU2_TIORL_0_IOD_SHIFT                  (4u)

#define MTU2_TIER_0_TGIEC_SHIFT                 (2u)
#define MTU2_TIER_0_TGIED_SHIFT                 (3u)

#define MTU2_TSR_0_TGFC_SHIFT                   (2u)
#define MTU2_TSR_0_TGFD_SHIFT                   (3u)

#define MTU2_TGRC_0_D_SHIFT                     (0u)

#define MTU2_TGRD_0_D_SHIFT                     (0u)

#define MTU2_TGRE_0_D_SHIFT                     (0u)

#define MTU2_TGRF_0_D_SHIFT                     (0u)

#define MTU2_TIER2_0_TGIEE_SHIFT                (0u)
#define MTU2_TIER2_0_TGIEF_SHIFT                (1u)

#define MTU2_TSR2_0_TGFE_SHIFT                  (0u)
#define MTU2_TSR2_0_TGFF_SHIFT                  (1u)

#define MTU2_TBTM_0_TTSA_SHIFT                  (0u)
#define MTU2_TBTM_0_TTSB_SHIFT                  (1u)
#define MTU2_TBTM_0_TTSE_SHIFT                  (2u)

#define MTU2_TIOR_1_IOA_SHIFT                   (0u)
#define MTU2_TIOR_1_IOB_SHIFT                   (4u)

#define MTU2_TIER_1_TCIEU_SHIFT                 (5u)

#define MTU2_TSR_1_TCFU_SHIFT                   (5u)
#define MTU2_TSR_1_TCFD_SHIFT                   (7u)

#define MTU2_TICCR_I1AE_SHIFT                   (0u)
#define MTU2_TICCR_I1BE_SHIFT                   (1u)
#define MTU2_TICCR_I2AE_SHIFT                   (2u)
#define MTU2_TICCR_I2BE_SHIFT                   (3u)


#endif /* MTU2_IOBITMASK_H */
/* End of File */
