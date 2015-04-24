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
* File Name   : cpg_iobitmask.h
* $Rev: 1115 $
* $Date:: 2014-07-09 15:35:02 +0900#$
* Description : CPG register define header
*******************************************************************************/
#ifndef CPG_IOBITMASK_H
#define CPG_IOBITMASK_H


/* ==== Mask values for IO registers ==== */
#define CPG_FRQCR_IFC                   (0x0300u)
#define CPG_FRQCR_CKOEN                 (0x3000u)
#define CPG_FRQCR_CKOEN2                (0x4000u)

#define CPG_FRQCR2_GFC                  (0x0003u)

#define CPG_CPUSTS_ISBUSY               (0x10u)

#define CPG_STBCR1_DEEP                 (0x40u)
#define CPG_STBCR1_STBY                 (0x80u)

#define CPG_STBCR2_MSTP20               (0x01u)
#define CPG_STBCR2_HIZ                  (0x80u)

#define CPG_STBREQ1_STBRQ10             (0x01u)
#define CPG_STBREQ1_STBRQ12             (0x04u)
#define CPG_STBREQ1_STBRQ13             (0x08u)
#define CPG_STBREQ1_STBRQ15             (0x20u)

#define CPG_STBREQ2_STBRQ20             (0x01u)
#define CPG_STBREQ2_STBRQ21             (0x02u)
#define CPG_STBREQ2_STBRQ22             (0x04u)
#define CPG_STBREQ2_STBRQ23             (0x08u)
#define CPG_STBREQ2_STBRQ24             (0x10u)
#define CPG_STBREQ2_STBRQ25             (0x20u)
#define CPG_STBREQ2_STBRQ26             (0x40u)
#define CPG_STBREQ2_STBRQ27             (0x80u)

#define CPG_STBACK1_STBAK10             (0x01u)
#define CPG_STBACK1_STBAK12             (0x04u)
#define CPG_STBACK1_STBAK13             (0x08u)
#define CPG_STBACK1_STBAK15             (0x20u)

#define CPG_STBACK2_STBAK20             (0x01u)
#define CPG_STBACK2_STBAK21             (0x02u)
#define CPG_STBACK2_STBAK22             (0x04u)
#define CPG_STBACK2_STBAK23             (0x08u)
#define CPG_STBACK2_STBAK24             (0x10u)
#define CPG_STBACK2_STBAK25             (0x20u)
#define CPG_STBACK2_STBAK26             (0x40u)
#define CPG_STBACK2_STBAK27             (0x80u)

#define CPG_SYSCR1_VRAME0               (0x01u)
#define CPG_SYSCR1_VRAME1               (0x02u)
#define CPG_SYSCR1_VRAME2               (0x04u)
#define CPG_SYSCR1_VRAME3               (0x08u)
#define CPG_SYSCR1_VRAME4               (0x10u)

#define CPG_SYSCR2_VRAMWE0              (0x01u)
#define CPG_SYSCR2_VRAMWE1              (0x02u)
#define CPG_SYSCR2_VRAMWE2              (0x04u)
#define CPG_SYSCR2_VRAMWE3              (0x08u)
#define CPG_SYSCR2_VRAMWE4              (0x10u)

#define CPG_SYSCR3_RRAMWE0              (0x01u)
#define CPG_SYSCR3_RRAMWE1              (0x02u)
#define CPG_SYSCR3_RRAMWE2              (0x04u)
#define CPG_SYSCR3_RRAMWE3              (0x08u)

#define CPG_STBCR3_MSTP30               (0x01u)
#define CPG_STBCR3_MSTP31               (0x02u)
#define CPG_STBCR3_MSTP32               (0x04u)
#define CPG_STBCR3_MSTP33               (0x08u)
#define CPG_STBCR3_MSTP34               (0x10u)
#define CPG_STBCR3_MSTP35               (0x20u)
#define CPG_STBCR3_MSTP36               (0x40u)
#define CPG_STBCR3_MSTP37               (0x80u)

#define CPG_STBCR4_MSTP40               (0x01u)
#define CPG_STBCR4_MSTP41               (0x02u)
#define CPG_STBCR4_MSTP42               (0x04u)
#define CPG_STBCR4_MSTP43               (0x08u)
#define CPG_STBCR4_MSTP44               (0x10u)
#define CPG_STBCR4_MSTP45               (0x20u)
#define CPG_STBCR4_MSTP46               (0x40u)
#define CPG_STBCR4_MSTP47               (0x80u)

#define CPG_STBCR5_MSTP50               (0x01u)
#define CPG_STBCR5_MSTP51               (0x02u)
#define CPG_STBCR5_MSTP52               (0x04u)
#define CPG_STBCR5_MSTP53               (0x08u)
#define CPG_STBCR5_MSTP54               (0x10u)
#define CPG_STBCR5_MSTP55               (0x20u)
#define CPG_STBCR5_MSTP56               (0x40u)
#define CPG_STBCR5_MSTP57               (0x80u)

#define CPG_STBCR6_MSTP60               (0x01u)
#define CPG_STBCR6_MSTP61               (0x02u)
#define CPG_STBCR6_MSTP62               (0x04u)
#define CPG_STBCR6_MSTP63               (0x08u)
#define CPG_STBCR6_MSTP64               (0x10u)
#define CPG_STBCR6_MSTP65               (0x20u)
#define CPG_STBCR6_MSTP66               (0x40u)
#define CPG_STBCR6_MSTP67               (0x80u)

#define CPG_STBCR7_MSTP70               (0x01u)
#define CPG_STBCR7_MSTP71               (0x02u)
#define CPG_STBCR7_MSTP73               (0x08u)
#define CPG_STBCR7_MSTP74               (0x10u)
#define CPG_STBCR7_MSTP76               (0x40u)
#define CPG_STBCR7_MSTP77               (0x80u)

#define CPG_STBCR8_MSTP81               (0x02u)
#define CPG_STBCR8_MSTP82               (0x04u)
#define CPG_STBCR8_MSTP83               (0x08u)
#define CPG_STBCR8_MSTP84               (0x10u)
#define CPG_STBCR8_MSTP85               (0x20u)
#define CPG_STBCR8_MSTP86               (0x40u)
#define CPG_STBCR8_MSTP87               (0x80u)

#define CPG_STBCR9_MSTP90               (0x01u)
#define CPG_STBCR9_MSTP91               (0x02u)
#define CPG_STBCR9_MSTP92               (0x04u)
#define CPG_STBCR9_MSTP93               (0x08u)
#define CPG_STBCR9_MSTP94               (0x10u)
#define CPG_STBCR9_MSTP95               (0x20u)
#define CPG_STBCR9_MSTP96               (0x40u)
#define CPG_STBCR9_MSTP97               (0x80u)

#define CPG_STBCR10_MSTP100             (0x01u)
#define CPG_STBCR10_MSTP101             (0x02u)
#define CPG_STBCR10_MSTP102             (0x04u)
#define CPG_STBCR10_MSTP103             (0x08u)
#define CPG_STBCR10_MSTP104             (0x10u)
#define CPG_STBCR10_MSTP105             (0x20u)
#define CPG_STBCR10_MSTP106             (0x40u)
#define CPG_STBCR10_MSTP107             (0x80u)

#define CPG_STBCR11_MSTP110             (0x01u)
#define CPG_STBCR11_MSTP111             (0x02u)
#define CPG_STBCR11_MSTP112             (0x04u)
#define CPG_STBCR11_MSTP113             (0x08u)
#define CPG_STBCR11_MSTP114             (0x10u)
#define CPG_STBCR11_MSTP115             (0x20u)

#define CPG_STBCR12_MSTP120             (0x01u)
#define CPG_STBCR12_MSTP121             (0x02u)
#define CPG_STBCR12_MSTP122             (0x04u)
#define CPG_STBCR12_MSTP123             (0x08u)

#define CPG_STBCR13_MSTP131             (0x02u)
#define CPG_STBCR13_MSTP132             (0x04u)

#define CPG_SWRSTCR1_SRST11             (0x02u)
#define CPG_SWRSTCR1_SRST12             (0x04u)
#define CPG_SWRSTCR1_SRST13             (0x08u)
#define CPG_SWRSTCR1_SRST14             (0x10u)
#define CPG_SWRSTCR1_SRST15             (0x20u)
#define CPG_SWRSTCR1_SRST16             (0x40u)
#define CPG_SWRSTCR1_AXTALE             (0x80u)

#define CPG_SWRSTCR2_SRST21             (0x02u)

#define CPG_SWRSTCR3_SRST32             (0x04u)

#define CPG_RRAMKP_RRAMKP0              (0x01u)
#define CPG_RRAMKP_RRAMKP1              (0x02u)
#define CPG_RRAMKP_RRAMKP2              (0x04u)
#define CPG_RRAMKP_RRAMKP3              (0x08u)

#define CPG_DSCTR_RAMBOOT               (0x40u)
#define CPG_DSCTR_EBUSKEEPE             (0x80u)

#define CPG_DSSSR_P8_2                  (0x0001u)
#define CPG_DSSSR_P9_1                  (0x0002u)
#define CPG_DSSSR_P2_15                 (0x0004u)
#define CPG_DSSSR_P7_8                  (0x0008u)
#define CPG_DSSSR_P5_9                  (0x0010u)
#define CPG_DSSSR_P6_4                  (0x0020u)
#define CPG_DSSSR_RTCAR                 (0x0040u)
#define CPG_DSSSR_NMI                   (0x0100u)
#define CPG_DSSSR_P3_3                  (0x0200u)
#define CPG_DSSSR_P8_7                  (0x0400u)
#define CPG_DSSSR_P2_12                 (0x0800u)
#define CPG_DSSSR_P3_1                  (0x1000u)
#define CPG_DSSSR_P3_9                  (0x2000u)
#define CPG_DSSSR_P6_2                  (0x4000u)

#define CPG_DSESR_P8_2E                 (0x0001u)
#define CPG_DSESR_P9_1E                 (0x0002u)
#define CPG_DSESR_P2_15E                (0x0004u)
#define CPG_DSESR_P7_8E                 (0x0008u)
#define CPG_DSESR_P5_9E                 (0x0010u)
#define CPG_DSESR_P6_4E                 (0x0020u)
#define CPG_DSESR_NMIE                  (0x0100u)
#define CPG_DSESR_P3_3E                 (0x0200u)
#define CPG_DSESR_P8_7E                 (0x0400u)
#define CPG_DSESR_P2_12E                (0x0800u)
#define CPG_DSESR_P3_1E                 (0x1000u)
#define CPG_DSESR_P3_9E                 (0x2000u)
#define CPG_DSESR_P6_2E                 (0x4000u)

#define CPG_DSFR_P8_2F                  (0x0001u)
#define CPG_DSFR_P9_1F                  (0x0002u)
#define CPG_DSFR_P2_15F                 (0x0004u)
#define CPG_DSFR_P7_8F                  (0x0008u)
#define CPG_DSFR_P5_9F                  (0x0010u)
#define CPG_DSFR_P6_4F                  (0x0020u)
#define CPG_DSFR_RTCARF                 (0x0040u)
#define CPG_DSFR_NMIF                   (0x0100u)
#define CPG_DSFR_P3_3F                  (0x0200u)
#define CPG_DSFR_P8_7F                  (0x0400u)
#define CPG_DSFR_P2_12F                 (0x0800u)
#define CPG_DSFR_P3_1F                  (0x1000u)
#define CPG_DSFR_P3_9F                  (0x2000u)
#define CPG_DSFR_P6_2F                  (0x4000u)
#define CPG_DSFR_IOKEEP                 (0x8000u)

#define CPG_XTALCTR_GAIN0               (0x01u)
#define CPG_XTALCTR_GAIN1               (0x02u)


/* ==== Shift values for IO registers ==== */
#define CPG_FRQCR_IFC_SHIFT             (8u)
#define CPG_FRQCR_CKOEN_SHIFT           (12u)
#define CPG_FRQCR_CKOEN2_SHIFT          (14u)

#define CPG_FRQCR2_GFC_SHIFT            (0u)

#define CPG_CPUSTS_ISBUSY_SHIFT         (4u)

#define CPG_STBCR1_DEEP_SHIFT           (6u)
#define CPG_STBCR1_STBY_SHIFT           (7u)

#define CPG_STBCR2_MSTP20_SHIFT         (0u)
#define CPG_STBCR2_HIZ_SHIFT            (7u)

#define CPG_STBREQ1_STBRQ10_SHIFT       (0u)
#define CPG_STBREQ1_STBRQ12_SHIFT       (2u)
#define CPG_STBREQ1_STBRQ13_SHIFT       (3u)
#define CPG_STBREQ1_STBRQ15_SHIFT       (5u)

#define CPG_STBREQ2_STBRQ20_SHIFT       (0u)
#define CPG_STBREQ2_STBRQ21_SHIFT       (1u)
#define CPG_STBREQ2_STBRQ22_SHIFT       (2u)
#define CPG_STBREQ2_STBRQ23_SHIFT       (3u)
#define CPG_STBREQ2_STBRQ24_SHIFT       (4u)
#define CPG_STBREQ2_STBRQ25_SHIFT       (5u)
#define CPG_STBREQ2_STBRQ26_SHIFT       (6u)
#define CPG_STBREQ2_STBRQ27_SHIFT       (7u)

#define CPG_STBACK1_STBAK10_SHIFT       (0u)
#define CPG_STBACK1_STBAK12_SHIFT       (2u)
#define CPG_STBACK1_STBAK13_SHIFT       (3u)
#define CPG_STBACK1_STBAK15_SHIFT       (5u)

#define CPG_STBACK2_STBAK20_SHIFT       (0u)
#define CPG_STBACK2_STBAK21_SHIFT       (1u)
#define CPG_STBACK2_STBAK22_SHIFT       (2u)
#define CPG_STBACK2_STBAK23_SHIFT       (3u)
#define CPG_STBACK2_STBAK24_SHIFT       (4u)
#define CPG_STBACK2_STBAK25_SHIFT       (5u)
#define CPG_STBACK2_STBAK26_SHIFT       (6u)
#define CPG_STBACK2_STBAK27_SHIFT       (7u)

#define CPG_SYSCR1_VRAME0_SHIFT         (0u)
#define CPG_SYSCR1_VRAME1_SHIFT         (1u)
#define CPG_SYSCR1_VRAME2_SHIFT         (2u)
#define CPG_SYSCR1_VRAME3_SHIFT         (3u)
#define CPG_SYSCR1_VRAME4_SHIFT         (4u)

#define CPG_SYSCR2_VRAMWE0_SHIFT        (0u)
#define CPG_SYSCR2_VRAMWE1_SHIFT        (1u)
#define CPG_SYSCR2_VRAMWE2_SHIFT        (2u)
#define CPG_SYSCR2_VRAMWE3_SHIFT        (3u)
#define CPG_SYSCR2_VRAMWE4_SHIFT        (4u)

#define CPG_SYSCR3_RRAMWE0_SHIFT        (0u)
#define CPG_SYSCR3_RRAMWE1_SHIFT        (1u)
#define CPG_SYSCR3_RRAMWE2_SHIFT        (2u)
#define CPG_SYSCR3_RRAMWE3_SHIFT        (3u)

#define CPG_STBCR3_MSTP30_SHIFT         (0u)
#define CPG_STBCR3_MSTP31_SHIFT         (1u)
#define CPG_STBCR3_MSTP32_SHIFT         (2u)
#define CPG_STBCR3_MSTP33_SHIFT         (3u)
#define CPG_STBCR3_MSTP34_SHIFT         (4u)
#define CPG_STBCR3_MSTP35_SHIFT         (5u)
#define CPG_STBCR3_MSTP36_SHIFT         (6u)
#define CPG_STBCR3_MSTP37_SHIFT         (7u)

#define CPG_STBCR4_MSTP40_SHIFT         (0u)
#define CPG_STBCR4_MSTP41_SHIFT         (1u)
#define CPG_STBCR4_MSTP42_SHIFT         (2u)
#define CPG_STBCR4_MSTP43_SHIFT         (3u)
#define CPG_STBCR4_MSTP44_SHIFT         (4u)
#define CPG_STBCR4_MSTP45_SHIFT         (5u)
#define CPG_STBCR4_MSTP46_SHIFT         (6u)
#define CPG_STBCR4_MSTP47_SHIFT         (7u)

#define CPG_STBCR5_MSTP50_SHIFT         (0u)
#define CPG_STBCR5_MSTP51_SHIFT         (1u)
#define CPG_STBCR5_MSTP52_SHIFT         (2u)
#define CPG_STBCR5_MSTP53_SHIFT         (3u)
#define CPG_STBCR5_MSTP54_SHIFT         (4u)
#define CPG_STBCR5_MSTP55_SHIFT         (5u)
#define CPG_STBCR5_MSTP56_SHIFT         (6u)
#define CPG_STBCR5_MSTP57_SHIFT         (7u)

#define CPG_STBCR6_MSTP60_SHIFT         (0u)
#define CPG_STBCR6_MSTP61_SHIFT         (1u)
#define CPG_STBCR6_MSTP62_SHIFT         (2u)
#define CPG_STBCR6_MSTP63_SHIFT         (3u)
#define CPG_STBCR6_MSTP64_SHIFT         (4u)
#define CPG_STBCR6_MSTP65_SHIFT         (5u)
#define CPG_STBCR6_MSTP66_SHIFT         (6u)
#define CPG_STBCR6_MSTP67_SHIFT         (7u)

#define CPG_STBCR7_MSTP70_SHIFT         (0u)
#define CPG_STBCR7_MSTP71_SHIFT         (1u)
#define CPG_STBCR7_MSTP73_SHIFT         (3u)
#define CPG_STBCR7_MSTP74_SHIFT         (4u)
#define CPG_STBCR7_MSTP76_SHIFT         (6u)
#define CPG_STBCR7_MSTP77_SHIFT         (7u)

#define CPG_STBCR8_MSTP81_SHIFT         (1u)
#define CPG_STBCR8_MSTP82_SHIFT         (2u)
#define CPG_STBCR8_MSTP83_SHIFT         (3u)
#define CPG_STBCR8_MSTP84_SHIFT         (4u)
#define CPG_STBCR8_MSTP85_SHIFT         (5u)
#define CPG_STBCR8_MSTP86_SHIFT         (6u)
#define CPG_STBCR8_MSTP87_SHIFT         (7u)

#define CPG_STBCR9_MSTP90_SHIFT         (0u)
#define CPG_STBCR9_MSTP91_SHIFT         (1u)
#define CPG_STBCR9_MSTP92_SHIFT         (2u)
#define CPG_STBCR9_MSTP93_SHIFT         (3u)
#define CPG_STBCR9_MSTP94_SHIFT         (4u)
#define CPG_STBCR9_MSTP95_SHIFT         (5u)
#define CPG_STBCR9_MSTP96_SHIFT         (6u)
#define CPG_STBCR9_MSTP97_SHIFT         (7u)

#define CPG_STBCR10_MSTP100_SHIFT       (0u)
#define CPG_STBCR10_MSTP101_SHIFT       (1u)
#define CPG_STBCR10_MSTP102_SHIFT       (2u)
#define CPG_STBCR10_MSTP103_SHIFT       (3u)
#define CPG_STBCR10_MSTP104_SHIFT       (4u)
#define CPG_STBCR10_MSTP105_SHIFT       (5u)
#define CPG_STBCR10_MSTP106_SHIFT       (6u)
#define CPG_STBCR10_MSTP107_SHIFT       (7u)

#define CPG_STBCR11_MSTP110_SHIFT       (0u)
#define CPG_STBCR11_MSTP111_SHIFT       (1u)
#define CPG_STBCR11_MSTP112_SHIFT       (2u)
#define CPG_STBCR11_MSTP113_SHIFT       (3u)
#define CPG_STBCR11_MSTP114_SHIFT       (4u)
#define CPG_STBCR11_MSTP115_SHIFT       (5u)

#define CPG_STBCR12_MSTP120_SHIFT       (0u)
#define CPG_STBCR12_MSTP121_SHIFT       (1u)
#define CPG_STBCR12_MSTP122_SHIFT       (2u)
#define CPG_STBCR12_MSTP123_SHIFT       (3u)

#define CPG_STBCR13_MSTP131_SHIFT       (1u)
#define CPG_STBCR13_MSTP132_SHIFT       (2u)

#define CPG_SWRSTCR1_SRST11_SHIFT       (1u)
#define CPG_SWRSTCR1_SRST12_SHIFT       (2u)
#define CPG_SWRSTCR1_SRST13_SHIFT       (3u)
#define CPG_SWRSTCR1_SRST14_SHIFT       (4u)
#define CPG_SWRSTCR1_SRST15_SHIFT       (5u)
#define CPG_SWRSTCR1_SRST16_SHIFT       (6u)
#define CPG_SWRSTCR1_AXTALE_SHIFT       (7u)

#define CPG_SWRSTCR2_SRST21_SHIFT       (1u)

#define CPG_SWRSTCR3_SRST32_SHIFT       (2u)

#define CPG_RRAMKP_RRAMKP0_SHIFT        (0u)
#define CPG_RRAMKP_RRAMKP1_SHIFT        (1u)
#define CPG_RRAMKP_RRAMKP2_SHIFT        (2u)
#define CPG_RRAMKP_RRAMKP3_SHIFT        (3u)

#define CPG_DSCTR_RAMBOOT_SHIFT         (6u)
#define CPG_DSCTR_EBUSKEEPE_SHIFT       (7u)

#define CPG_DSSSR_P8_2_SHIFT            (0u)
#define CPG_DSSSR_P9_1_SHIFT            (1u)
#define CPG_DSSSR_P2_15_SHIFT           (2u)
#define CPG_DSSSR_P7_8_SHIFT            (3u)
#define CPG_DSSSR_P5_9_SHIFT            (4u)
#define CPG_DSSSR_P6_4_SHIFT            (5u)
#define CPG_DSSSR_RTCAR_SHIFT           (6u)
#define CPG_DSSSR_NMI_SHIFT             (8u)
#define CPG_DSSSR_P3_3_SHIFT            (9u)
#define CPG_DSSSR_P8_7_SHIFT            (10u)
#define CPG_DSSSR_P2_12_SHIFT           (11u)
#define CPG_DSSSR_P3_1_SHIFT            (12u)
#define CPG_DSSSR_P3_9_SHIFT            (13u)
#define CPG_DSSSR_P6_2_SHIFT            (14u)

#define CPG_DSESR_P8_2E_SHIFT           (0u)
#define CPG_DSESR_P9_1E_SHIFT           (1u)
#define CPG_DSESR_P2_15E_SHIFT          (2u)
#define CPG_DSESR_P7_8E_SHIFT           (3u)
#define CPG_DSESR_P5_9E_SHIFT           (4u)
#define CPG_DSESR_P6_4E_SHIFT           (5u)
#define CPG_DSESR_NMIE_SHIFT            (8u)
#define CPG_DSESR_P3_3E_SHIFT           (9u)
#define CPG_DSESR_P8_7E_SHIFT           (10u)
#define CPG_DSESR_P2_12E_SHIFT          (11u)
#define CPG_DSESR_P3_1E_SHIFT           (12u)
#define CPG_DSESR_P3_9E_SHIFT           (13u)
#define CPG_DSESR_P6_2E_SHIFT           (14u)

#define CPG_DSFR_P8_2F_SHIFT            (0u)
#define CPG_DSFR_P9_1F_SHIFT            (1u)
#define CPG_DSFR_P2_15F_SHIFT           (2u)
#define CPG_DSFR_P7_8F_SHIFT            (3u)
#define CPG_DSFR_P5_9F_SHIFT            (4u)
#define CPG_DSFR_P6_4F_SHIFT            (5u)
#define CPG_DSFR_RTCARF_SHIFT           (6u)
#define CPG_DSFR_NMIF_SHIFT             (8u)
#define CPG_DSFR_P3_3F_SHIFT            (9u)
#define CPG_DSFR_P8_7F_SHIFT            (10u)
#define CPG_DSFR_P2_12F_SHIFT           (11u)
#define CPG_DSFR_P3_1F_SHIFT            (12u)
#define CPG_DSFR_P3_9F_SHIFT            (13u)
#define CPG_DSFR_P6_2F_SHIFT            (14u)
#define CPG_DSFR_IOKEEP_SHIFT           (15u)

#define CPG_XTALCTR_GAIN0_SHIFT         (0u)
#define CPG_XTALCTR_GAIN1_SHIFT         (1u)


#endif /* CPG_IOBITMASK_H */

/* End of File */
