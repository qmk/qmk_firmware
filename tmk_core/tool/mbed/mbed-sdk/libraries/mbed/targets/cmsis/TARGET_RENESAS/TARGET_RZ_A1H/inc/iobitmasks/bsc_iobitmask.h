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
* File Name   : bsc_iobitmask.h
* $Rev: 1115 $
* $Date:: 2014-07-09 15:35:02 +0900#$
* Description : BSC register define header
*******************************************************************************/
#ifndef BSC_IOBITMASK_H
#define BSC_IOBITMASK_H


/* ==== Mask values for IO registers ==== */
#define BSC_CMNCR_HIZCNT                (0x00000001uL)
#define BSC_CMNCR_HIZMEM                (0x00000002uL)
#define BSC_CMNCR_DPRTY                 (0x00000600uL)
#define BSC_CMNCR_AL0                   (0x01000000uL)
#define BSC_CMNCR_TL0                   (0x10000000uL)

#define BSC_CS0BCR_BSZ                  (0x00000600uL)
#define BSC_CS0BCR_TYPE                 (0x00007000uL)
#define BSC_CS0BCR_IWRRS                (0x00070000uL)
#define BSC_CS0BCR_IWRRD                (0x00380000uL)
#define BSC_CS0BCR_IWRWS                (0x01C00000uL)
#define BSC_CS0BCR_IWRWD                (0x0E000000uL)
#define BSC_CS0BCR_IWW                  (0x70000000uL)

#define BSC_CS1BCR_BSZ                  (0x00000600uL)
#define BSC_CS1BCR_TYPE                 (0x00007000uL)
#define BSC_CS1BCR_IWRRS                (0x00070000uL)
#define BSC_CS1BCR_IWRRD                (0x00380000uL)
#define BSC_CS1BCR_IWRWS                (0x01C00000uL)
#define BSC_CS1BCR_IWRWD                (0x0E000000uL)
#define BSC_CS1BCR_IWW                  (0x70000000uL)

#define BSC_CS2BCR_BSZ                  (0x00000600uL)
#define BSC_CS2BCR_TYPE                 (0x00007000uL)
#define BSC_CS2BCR_IWRRS                (0x00070000uL)
#define BSC_CS2BCR_IWRRD                (0x00380000uL)
#define BSC_CS2BCR_IWRWS                (0x01C00000uL)
#define BSC_CS2BCR_IWRWD                (0x0E000000uL)
#define BSC_CS2BCR_IWW                  (0x70000000uL)

#define BSC_CS3BCR_BSZ                  (0x00000600uL)
#define BSC_CS3BCR_TYPE                 (0x00007000uL)
#define BSC_CS3BCR_IWRRS                (0x00070000uL)
#define BSC_CS3BCR_IWRRD                (0x00380000uL)
#define BSC_CS3BCR_IWRWS                (0x01C00000uL)
#define BSC_CS3BCR_IWRWD                (0x0E000000uL)
#define BSC_CS3BCR_IWW                  (0x70000000uL)

#define BSC_CS4BCR_BSZ                  (0x00000600uL)
#define BSC_CS4BCR_TYPE                 (0x00007000uL)
#define BSC_CS4BCR_IWRRS                (0x00070000uL)
#define BSC_CS4BCR_IWRRD                (0x00380000uL)
#define BSC_CS4BCR_IWRWS                (0x01C00000uL)
#define BSC_CS4BCR_IWRWD                (0x0E000000uL)
#define BSC_CS4BCR_IWW                  (0x70000000uL)

#define BSC_CS5BCR_BSZ                  (0x00000600uL)
#define BSC_CS5BCR_TYPE                 (0x00007000uL)
#define BSC_CS5BCR_IWRRS                (0x00070000uL)
#define BSC_CS5BCR_IWRRD                (0x00380000uL)
#define BSC_CS5BCR_IWRWS                (0x01C00000uL)
#define BSC_CS5BCR_IWRWD                (0x0E000000uL)
#define BSC_CS5BCR_IWW                  (0x70000000uL)

#define BSC_CS0WCR_NORMAL_HW            (0x00000003uL)
#define BSC_CS0WCR_NORMAL_WM            (0x00000040uL)
#define BSC_CS0WCR_NORMAL_WR            (0x00000780uL)
#define BSC_CS0WCR_NORMAL_SW            (0x00001800uL)
#define BSC_CS0WCR_NORMAL_BAS           (0x00100000uL)

#define BSC_CS1WCR_NORMAL_HW            (0x00000003uL)
#define BSC_CS1WCR_NORMAL_WM            (0x00000040uL)
#define BSC_CS1WCR_NORMAL_WR            (0x00000780uL)
#define BSC_CS1WCR_NORMAL_SW            (0x00001800uL)
#define BSC_CS1WCR_NORMAL_WW            (0x00070000uL)
#define BSC_CS1WCR_NORMAL_BAS           (0x00100000uL)

#define BSC_CS2WCR_NORMAL_WM            (0x00000040uL)
#define BSC_CS2WCR_NORMAL_WR            (0x00000780uL)
#define BSC_CS2WCR_NORMAL_BAS           (0x00100000uL)

#define BSC_CS3WCR_NORMAL_WM            (0x00000040uL)
#define BSC_CS3WCR_NORMAL_WR            (0x00000780uL)
#define BSC_CS3WCR_NORMAL_BAS           (0x00100000uL)

#define BSC_CS4WCR_NORMAL_HW            (0x00000003uL)
#define BSC_CS4WCR_NORMAL_WM            (0x00000040uL)
#define BSC_CS4WCR_NORMAL_WR            (0x00000780uL)
#define BSC_CS4WCR_NORMAL_SW            (0x00001800uL)
#define BSC_CS4WCR_NORMAL_WW            (0x00070000uL)
#define BSC_CS4WCR_NORMAL_BAS           (0x00100000uL)

#define BSC_CS5WCR_NORMAL_HW            (0x00000003uL)
#define BSC_CS5WCR_NORMAL_WM            (0x00000040uL)
#define BSC_CS5WCR_NORMAL_WR            (0x00000780uL)
#define BSC_CS5WCR_NORMAL_SW            (0x00001800uL)
#define BSC_CS5WCR_NORMAL_WW            (0x00070000uL)
#define BSC_CS5WCR_NORMAL_MPXWBAS       (0x00100000uL)
#define BSC_CS5WCR_NORMAL_SZSEL         (0x00200000uL)

#define BSC_CS0WCR_BROM_ASY_WM          (0x00000040uL)
#define BSC_CS0WCR_BROM_ASY_W           (0x00000780uL)
#define BSC_CS0WCR_BROM_ASY_BW          (0x00030000uL)
#define BSC_CS0WCR_BROM_ASY_BST         (0x00300000uL)

#define BSC_CS4WCR_BROM_ASY_HW          (0x00000003uL)
#define BSC_CS4WCR_BROM_ASY_WM          (0x00000040uL)
#define BSC_CS4WCR_BROM_ASY_W           (0x00000780uL)
#define BSC_CS4WCR_BROM_ASY_SW          (0x00001800uL)
#define BSC_CS4WCR_BROM_ASY_BW          (0x00030000uL)
#define BSC_CS4WCR_BROM_ASY_BST         (0x00300000uL)

#define BSC_CS2WCR_SDRAM_A2CL           (0x00000180uL)

#define BSC_CS3WCR_SDRAM_WTRC           (0x00000003uL)
#define BSC_CS3WCR_SDRAM_TRWL           (0x00000018uL)
#define BSC_CS3WCR_SDRAM_A3CL           (0x00000180uL)
#define BSC_CS3WCR_SDRAM_WTRCD          (0x00000C00uL)
#define BSC_CS3WCR_SDRAM_WTRP           (0x00006000uL)

#define BSC_CS0WCR_BROM_SY_WM           (0x00000040uL)
#define BSC_CS0WCR_BROM_SY_W            (0x00000780uL)
#define BSC_CS0WCR_BROM_SY_BW           (0x00030000uL)

#define BSC_SDCR_A3COL                  (0x00000003uL)
#define BSC_SDCR_A3ROW                  (0x00000018uL)
#define BSC_SDCR_BACTV                  (0x00000100uL)
#define BSC_SDCR_PDOWN                  (0x00000200uL)
#define BSC_SDCR_RMODE                  (0x00000400uL)
#define BSC_SDCR_RFSH                   (0x00000800uL)
#define BSC_SDCR_DEEP                   (0x00002000uL)
#define BSC_SDCR_A2COL                  (0x00030000uL)
#define BSC_SDCR_A2ROW                  (0x00180000uL)

#define BSC_RTCSR_RRC                   (0x00000007uL)
#define BSC_RTCSR_CKS                   (0x00000038uL)
#define BSC_RTCSR_CMIE                  (0x00000040uL)
#define BSC_RTCSR_CMF                   (0x00000080uL)

#define BSC_RTCNT_D                     (0xFFFFFFFFuL)

#define BSC_RTCOR_D                     (0xFFFFFFFFuL)

#define BSC_TOSCOR0_D                   (0x0000FFFFuL)

#define BSC_TOSCOR1_D                   (0x0000FFFFuL)

#define BSC_TOSCOR2_D                   (0x0000FFFFuL)

#define BSC_TOSCOR3_D                   (0x0000FFFFuL)

#define BSC_TOSCOR4_D                   (0x0000FFFFuL)

#define BSC_TOSCOR5_D                   (0x0000FFFFuL)

#define BSC_TOSTR_CS0TOSTF              (0x00000001uL)
#define BSC_TOSTR_CS1TOSTF              (0x00000002uL)
#define BSC_TOSTR_CS2TOSTF              (0x00000004uL)
#define BSC_TOSTR_CS3TOSTF              (0x00000008uL)
#define BSC_TOSTR_CS4TOSTF              (0x00000010uL)
#define BSC_TOSTR_CS5TOSTF              (0x00000020uL)

#define BSC_TOENR_CS0TOEN               (0x00000001uL)
#define BSC_TOENR_CS1TOEN               (0x00000002uL)
#define BSC_TOENR_CS2TOEN               (0x00000004uL)
#define BSC_TOENR_CS3TOEN               (0x00000008uL)
#define BSC_TOENR_CS4TOEN               (0x00000010uL)
#define BSC_TOENR_CS5TOEN               (0x00000020uL)


/* ==== Shift values for IO registers ==== */
#define BSC_CMNCR_HIZCNT_SHIFT          (0u)
#define BSC_CMNCR_HIZMEM_SHIFT          (1u)
#define BSC_CMNCR_DPRTY_SHIFT           (9u)
#define BSC_CMNCR_AL0_SHIFT             (24u)
#define BSC_CMNCR_TL0_SHIFT             (28u)

#define BSC_CS0BCR_BSZ_SHIFT            (9u)
#define BSC_CS0BCR_TYPE_SHIFT           (12u)
#define BSC_CS0BCR_IWRRS_SHIFT          (16u)
#define BSC_CS0BCR_IWRRD_SHIFT          (19u)
#define BSC_CS0BCR_IWRWS_SHIFT          (22u)
#define BSC_CS0BCR_IWRWD_SHIFT          (25u)
#define BSC_CS0BCR_IWW_SHIFT            (28u)

#define BSC_CS1BCR_BSZ_SHIFT            (9u)
#define BSC_CS1BCR_TYPE_SHIFT           (12u)
#define BSC_CS1BCR_IWRRS_SHIFT          (16u)
#define BSC_CS1BCR_IWRRD_SHIFT          (19u)
#define BSC_CS1BCR_IWRWS_SHIFT          (22u)
#define BSC_CS1BCR_IWRWD_SHIFT          (25u)
#define BSC_CS1BCR_IWW_SHIFT            (28u)

#define BSC_CS2BCR_BSZ_SHIFT            (9u)
#define BSC_CS2BCR_TYPE_SHIFT           (12u)
#define BSC_CS2BCR_IWRRS_SHIFT          (16u)
#define BSC_CS2BCR_IWRRD_SHIFT          (19u)
#define BSC_CS2BCR_IWRWS_SHIFT          (22u)
#define BSC_CS2BCR_IWRWD_SHIFT          (25u)
#define BSC_CS2BCR_IWW_SHIFT            (28u)

#define BSC_CS3BCR_BSZ_SHIFT            (9u)
#define BSC_CS3BCR_TYPE_SHIFT           (12u)
#define BSC_CS3BCR_IWRRS_SHIFT          (16u)
#define BSC_CS3BCR_IWRRD_SHIFT          (19u)
#define BSC_CS3BCR_IWRWS_SHIFT          (22u)
#define BSC_CS3BCR_IWRWD_SHIFT          (25u)
#define BSC_CS3BCR_IWW_SHIFT            (28u)

#define BSC_CS4BCR_BSZ_SHIFT            (9u)
#define BSC_CS4BCR_TYPE_SHIFT           (12u)
#define BSC_CS4BCR_IWRRS_SHIFT          (16u)
#define BSC_CS4BCR_IWRRD_SHIFT          (19u)
#define BSC_CS4BCR_IWRWS_SHIFT          (22u)
#define BSC_CS4BCR_IWRWD_SHIFT          (25u)
#define BSC_CS4BCR_IWW_SHIFT            (28u)

#define BSC_CS5BCR_BSZ_SHIFT            (9u)
#define BSC_CS5BCR_TYPE_SHIFT           (12u)
#define BSC_CS5BCR_IWRRS_SHIFT          (16u)
#define BSC_CS5BCR_IWRRD_SHIFT          (19u)
#define BSC_CS5BCR_IWRWS_SHIFT          (22u)
#define BSC_CS5BCR_IWRWD_SHIFT          (25u)
#define BSC_CS5BCR_IWW_SHIFT            (28u)

#define BSC_CS0WCR_NORMAL_HW_SHIFT      (0u)
#define BSC_CS0WCR_NORMAL_WM_SHIFT      (6u)
#define BSC_CS0WCR_NORMAL_WR_SHIFT      (7u)
#define BSC_CS0WCR_NORMAL_SW_SHIFT      (11u)
#define BSC_CS0WCR_NORMAL_BAS_SHIFT     (20u)

#define BSC_CS1WCR_NORMAL_HW_SHIFT      (0u)
#define BSC_CS1WCR_NORMAL_WM_SHIFT      (6u)
#define BSC_CS1WCR_NORMAL_WR_SHIFT      (7u)
#define BSC_CS1WCR_NORMAL_SW_SHIFT      (11u)
#define BSC_CS1WCR_NORMAL_WW_SHIFT      (16u)
#define BSC_CS1WCR_NORMAL_BAS_SHIFT     (20u)

#define BSC_CS2WCR_NORMAL_WM_SHIFT      (6u)
#define BSC_CS2WCR_NORMAL_WR_SHIFT      (7u)
#define BSC_CS2WCR_NORMAL_BAS_SHIFT     (20u)

#define BSC_CS3WCR_NORMAL_WM_SHIFT      (6u)
#define BSC_CS3WCR_NORMAL_WR_SHIFT      (7u)
#define BSC_CS3WCR_NORMAL_BAS_SHIFT     (20u)

#define BSC_CS4WCR_NORMAL_HW_SHIFT      (0u)
#define BSC_CS4WCR_NORMAL_WM_SHIFT      (6u)
#define BSC_CS4WCR_NORMAL_WR_SHIFT      (7u)
#define BSC_CS4WCR_NORMAL_SW_SHIFT      (11u)
#define BSC_CS4WCR_NORMAL_WW_SHIFT      (16u)
#define BSC_CS4WCR_NORMAL_BAS_SHIFT     (20u)

#define BSC_CS5WCR_NORMAL_HW_SHIFT      (0u)
#define BSC_CS5WCR_NORMAL_WM_SHIFT      (6u)
#define BSC_CS5WCR_NORMAL_WR_SHIFT      (7u)
#define BSC_CS5WCR_NORMAL_SW_SHIFT      (11u)
#define BSC_CS5WCR_NORMAL_WW_SHIFT      (16u)
#define BSC_CS5WCR_NORMAL_MPXWBAS_SHIFT (20u)
#define BSC_CS5WCR_NORMAL_SZSEL_SHIFT   (21u)

#define BSC_CS0WCR_BROM_ASY_WM_SHIFT    (6u)
#define BSC_CS0WCR_BROM_ASY_W_SHIFT     (7u)
#define BSC_CS0WCR_BROM_ASY_BW_SHIFT    (16u)
#define BSC_CS0WCR_BROM_ASY_BST_SHIFT   (20u)

#define BSC_CS4WCR_BROM_ASY_HW_SHIFT    (0u)
#define BSC_CS4WCR_BROM_ASY_WM_SHIFT    (6u)
#define BSC_CS4WCR_BROM_ASY_W_SHIFT     (7u)
#define BSC_CS4WCR_BROM_ASY_SW_SHIFT    (11u)
#define BSC_CS4WCR_BROM_ASY_BW_SHIFT    (16u)
#define BSC_CS4WCR_BROM_ASY_BST_SHIFT   (20u)

#define BSC_CS2WCR_SDRAM_A2CL_SHIFT     (7u)

#define BSC_CS3WCR_SDRAM_WTRC_SHIFT     (0u)
#define BSC_CS3WCR_SDRAM_TRWL_SHIFT     (3u)
#define BSC_CS3WCR_SDRAM_A3CL_SHIFT     (7u)
#define BSC_CS3WCR_SDRAM_WTRCD_SHIFT    (10u)
#define BSC_CS3WCR_SDRAM_WTRP_SHIFT     (13u)

#define BSC_CS0WCR_BROM_SY_WM_SHIFT     (6u)
#define BSC_CS0WCR_BROM_SY_W_SHIFT      (7u)
#define BSC_CS0WCR_BROM_SY_BW_SHIFT     (16u)

#define BSC_SDCR_A3COL_SHIFT            (0u)
#define BSC_SDCR_A3ROW_SHIFT            (3u)
#define BSC_SDCR_BACTV_SHIFT            (8u)
#define BSC_SDCR_PDOWN_SHIFT            (9u)
#define BSC_SDCR_RMODE_SHIFT            (10u)
#define BSC_SDCR_RFSH_SHIFT             (11u)
#define BSC_SDCR_DEEP_SHIFT             (13u)
#define BSC_SDCR_A2COL_SHIFT            (16u)
#define BSC_SDCR_A2ROW_SHIFT            (19u)

#define BSC_RTCSR_RRC_SHIFT             (0u)
#define BSC_RTCSR_CKS_SHIFT             (3u)
#define BSC_RTCSR_CMIE_SHIFT            (6u)
#define BSC_RTCSR_CMF_SHIFT             (7u)

#define BSC_RTCNT_D_SHIFT               (0u)

#define BSC_RTCOR_D_SHIFT               (0u)

#define BSC_TOSCOR0_D_SHIFT             (0u)

#define BSC_TOSCOR1_D_SHIFT             (0u)

#define BSC_TOSCOR2_D_SHIFT             (0u)

#define BSC_TOSCOR3_D_SHIFT             (0u)

#define BSC_TOSCOR4_D_SHIFT             (0u)

#define BSC_TOSCOR5_D_SHIFT             (0u)

#define BSC_TOSTR_CS0TOSTF_SHIFT        (0u)
#define BSC_TOSTR_CS1TOSTF_SHIFT        (1u)
#define BSC_TOSTR_CS2TOSTF_SHIFT        (2u)
#define BSC_TOSTR_CS3TOSTF_SHIFT        (3u)
#define BSC_TOSTR_CS4TOSTF_SHIFT        (4u)
#define BSC_TOSTR_CS5TOSTF_SHIFT        (5u)

#define BSC_TOENR_CS0TOEN_SHIFT         (0u)
#define BSC_TOENR_CS1TOEN_SHIFT         (1u)
#define BSC_TOENR_CS2TOEN_SHIFT         (2u)
#define BSC_TOENR_CS3TOEN_SHIFT         (3u)
#define BSC_TOENR_CS4TOEN_SHIFT         (4u)
#define BSC_TOENR_CS5TOEN_SHIFT         (5u)


#endif /* BSC_IOBITMASK_H */

/* End of File */
