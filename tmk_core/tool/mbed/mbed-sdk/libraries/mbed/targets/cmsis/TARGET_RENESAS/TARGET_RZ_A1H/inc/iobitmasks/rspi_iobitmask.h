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
* File Name   : rspi_iobitmask.h
* $Rev: 1114 $
* $Date:: 2014-07-09 14:56:39 +0900#$
* Description : Renesas Serial Peripheral Interface register define header
*******************************************************************************/
#ifndef RSPI_IOBITMASK_H
#define RSPI_IOBITMASK_H


/* ==== Mask values for IO registers ==== */
#define RSPIn_SPCR_MODFEN                   (0x04u)
#define RSPIn_SPCR_MSTR                     (0x08u)
#define RSPIn_SPCR_SPEIE                    (0x10u)
#define RSPIn_SPCR_SPTIE                    (0x20u)
#define RSPIn_SPCR_SPE                      (0x40u)
#define RSPIn_SPCR_SPRIE                    (0x80u)

#define RSPIn_SSLP_SSL0P                    (0x01u)

#define RSPIn_SPPCR_SPLP                    (0x01u)
#define RSPIn_SPPCR_MOIFV                   (0x10u)
#define RSPIn_SPPCR_MOIFE                   (0x20u)

#define RSPIn_SPSR_OVRF                     (0x01u)
#define RSPIn_SPSR_MODF                     (0x04u)
#define RSPIn_SPSR_SPTEF                    (0x20u)
#define RSPIn_SPSR_TEND                     (0x40u)
#define RSPIn_SPSR_SPRF                     (0x80u)

#define RSPIn_SPDR_UINT32                   (0xFFFFFFFFuL)

#define RSPIn_SPDR_UINT16                   (0xFFFFu)

#define RSPIn_SPDR_UINT8                    (0xFFu)

#define RSPIn_SPSCR_SPSLN                   (0x03u)

#define RSPIn_SPSSR_SPCP                    (0x03u)

#define RSPIn_SPBR_SPR                      (0xFFu)

#define RSPIn_SPDCR_SPLW                    (0x60u)
#define RSPIn_SPDCR_TXDMY                   (0x80u)

#define RSPIn_SPCKD_SCKDL                   (0x07u)

#define RSPIn_SSLND_SLNDL                   (0x07u)

#define RSPIn_SPND_SPNDL                    (0x07u)

#define RSPIn_SPCMD0_CPHA                   (0x0001u)
#define RSPIn_SPCMD0_CPOL                   (0x0002u)
#define RSPIn_SPCMD0_BRDV                   (0x000Cu)
#define RSPIn_SPCMD0_SSLKP                  (0x0080u)
#define RSPIn_SPCMD0_SPB                    (0x0F00u)
#define RSPIn_SPCMD0_LSBF                   (0x1000u)
#define RSPIn_SPCMD0_SPNDEN                 (0x2000u)
#define RSPIn_SPCMD0_SLNDEN                 (0x4000u)
#define RSPIn_SPCMD0_SCKDEN                 (0x8000u)

#define RSPIn_SPCMD1_CPHA                   (0x0001u)
#define RSPIn_SPCMD1_CPOL                   (0x0002u)
#define RSPIn_SPCMD1_BRDV                   (0x000Cu)
#define RSPIn_SPCMD1_SSLKP                  (0x0080u)
#define RSPIn_SPCMD1_SPB                    (0x0F00u)
#define RSPIn_SPCMD1_LSBF                   (0x1000u)
#define RSPIn_SPCMD1_SPNDEN                 (0x2000u)
#define RSPIn_SPCMD1_SLNDEN                 (0x4000u)
#define RSPIn_SPCMD1_SCKDEN                 (0x8000u)

#define RSPIn_SPCMD2_CPHA                   (0x0001u)
#define RSPIn_SPCMD2_CPOL                   (0x0002u)
#define RSPIn_SPCMD2_BRDV                   (0x000Cu)
#define RSPIn_SPCMD2_SSLKP                  (0x0080u)
#define RSPIn_SPCMD2_SPB                    (0x0F00u)
#define RSPIn_SPCMD2_LSBF                   (0x1000u)
#define RSPIn_SPCMD2_SPNDEN                 (0x2000u)
#define RSPIn_SPCMD2_SLNDEN                 (0x4000u)
#define RSPIn_SPCMD2_SCKDEN                 (0x8000u)

#define RSPIn_SPCMD3_CPHA                   (0x0001u)
#define RSPIn_SPCMD3_CPOL                   (0x0002u)
#define RSPIn_SPCMD3_BRDV                   (0x000Cu)
#define RSPIn_SPCMD3_SSLKP                  (0x0080u)
#define RSPIn_SPCMD3_SPB                    (0x0F00u)
#define RSPIn_SPCMD3_LSBF                   (0x1000u)
#define RSPIn_SPCMD3_SPNDEN                 (0x2000u)
#define RSPIn_SPCMD3_SLNDEN                 (0x4000u)
#define RSPIn_SPCMD3_SCKDEN                 (0x8000u)

#define RSPIn_SPBFCR_RXTRG                  (0x07u)
#define RSPIn_SPBFCR_TXTRG                  (0x30u)
#define RSPIn_SPBFCR_RXRST                  (0x40u)
#define RSPIn_SPBFCR_TXRST                  (0x80u)

#define RSPIn_SPBFDR_R                      (0x003Fu)
#define RSPIn_SPBFDR_T                      (0x0F00u)


/* ==== Shift values for IO registers ==== */
#define RSPIn_SPCR_MODFEN_SHIFT             (2u)
#define RSPIn_SPCR_MSTR_SHIFT               (3u)
#define RSPIn_SPCR_SPEIE_SHIFT              (4u)
#define RSPIn_SPCR_SPTIE_SHIFT              (5u)
#define RSPIn_SPCR_SPE_SHIFT                (6u)
#define RSPIn_SPCR_SPRIE_SHIFT              (7u)

#define RSPIn_SSLP_SSL0P_SHIFT              (0u)

#define RSPIn_SPPCR_SPLP_SHIFT              (0u)
#define RSPIn_SPPCR_MOIFV_SHIFT             (4u)
#define RSPIn_SPPCR_MOIFE_SHIFT             (5u)

#define RSPIn_SPSR_OVRF_SHIFT               (0u)
#define RSPIn_SPSR_MODF_SHIFT               (2u)
#define RSPIn_SPSR_SPTEF_SHIFT              (5u)
#define RSPIn_SPSR_TEND_SHIFT               (6u)
#define RSPIn_SPSR_SPRF_SHIFT               (7u)

#define RSPIn_SPDR_UINT32_SHIFT             (0u)

#define RSPIn_SPDR_UINT16_SHIFT             (0u)

#define RSPIn_SPDR_UINT8_SHIFT              (0u)

#define RSPIn_SPSCR_SPSLN_SHIFT             (0u)

#define RSPIn_SPSSR_SPCP_SHIFT              (0u)

#define RSPIn_SPBR_SPR_SHIFT                (0u)

#define RSPIn_SPDCR_SPLW_SHIFT              (5u)
#define RSPIn_SPDCR_TXDMY_SHIFT             (7u)

#define RSPIn_SPCKD_SCKDL_SHIFT             (0u)

#define RSPIn_SSLND_SLNDL_SHIFT             (0u)

#define RSPIn_SPND_SPNDL_SHIFT              (0u)

#define RSPIn_SPCMD0_CPHA_SHIFT             (0u)
#define RSPIn_SPCMD0_CPOL_SHIFT             (1u)
#define RSPIn_SPCMD0_BRDV_SHIFT             (2u)
#define RSPIn_SPCMD0_SSLKP_SHIFT            (7u)
#define RSPIn_SPCMD0_SPB_SHIFT              (8u)
#define RSPIn_SPCMD0_LSBF_SHIFT             (12u)
#define RSPIn_SPCMD0_SPNDEN_SHIFT           (13u)
#define RSPIn_SPCMD0_SLNDEN_SHIFT           (14u)
#define RSPIn_SPCMD0_SCKDEN_SHIFT           (15u)

#define RSPIn_SPCMD1_CPHA_SHIFT             (0u)
#define RSPIn_SPCMD1_CPOL_SHIFT             (1u)
#define RSPIn_SPCMD1_BRDV_SHIFT             (2u)
#define RSPIn_SPCMD1_SSLKP_SHIFT            (7u)
#define RSPIn_SPCMD1_SPB_SHIFT              (8u)
#define RSPIn_SPCMD1_LSBF_SHIFT             (12u)
#define RSPIn_SPCMD1_SPNDEN_SHIFT           (13u)
#define RSPIn_SPCMD1_SLNDEN_SHIFT           (14u)
#define RSPIn_SPCMD1_SCKDEN_SHIFT           (15u)

#define RSPIn_SPCMD2_CPHA_SHIFT             (0u)
#define RSPIn_SPCMD2_CPOL_SHIFT             (1u)
#define RSPIn_SPCMD2_BRDV_SHIFT             (2u)
#define RSPIn_SPCMD2_SSLKP_SHIFT            (7u)
#define RSPIn_SPCMD2_SPB_SHIFT              (8u)
#define RSPIn_SPCMD2_LSBF_SHIFT             (12u)
#define RSPIn_SPCMD2_SPNDEN_SHIFT           (13u)
#define RSPIn_SPCMD2_SLNDEN_SHIFT           (14u)
#define RSPIn_SPCMD2_SCKDEN_SHIFT           (15u)

#define RSPIn_SPCMD3_CPHA_SHIFT             (0u)
#define RSPIn_SPCMD3_CPOL_SHIFT             (1u)
#define RSPIn_SPCMD3_BRDV_SHIFT             (2u)
#define RSPIn_SPCMD3_SSLKP_SHIFT            (7u)
#define RSPIn_SPCMD3_SPB_SHIFT              (8u)
#define RSPIn_SPCMD3_LSBF_SHIFT             (12u)
#define RSPIn_SPCMD3_SPNDEN_SHIFT           (13u)
#define RSPIn_SPCMD3_SLNDEN_SHIFT           (14u)
#define RSPIn_SPCMD3_SCKDEN_SHIFT           (15u)

#define RSPIn_SPBFCR_RXTRG_SHIFT            (0u)
#define RSPIn_SPBFCR_TXTRG_SHIFT            (4u)
#define RSPIn_SPBFCR_RXRST_SHIFT            (6u)
#define RSPIn_SPBFCR_TXRST_SHIFT            (7u)

#define RSPIn_SPBFDR_R_SHIFT                (0u)
#define RSPIn_SPBFDR_T_SHIFT                (8u)


#endif /* RSPI_IOBITMASK_H */

/* End of File */
