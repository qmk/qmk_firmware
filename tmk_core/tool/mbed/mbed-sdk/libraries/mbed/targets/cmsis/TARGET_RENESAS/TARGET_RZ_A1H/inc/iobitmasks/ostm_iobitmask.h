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
* File Name   : ostm_iobitmask.h
* $Rev: 1115 $
* $Date:: 2014-07-09 15:35:02 +0900#$
* Description : OSTM register define header
*******************************************************************************/
#ifndef OSTM_IOBITMASK_H
#define OSTM_IOBITMASK_H


/* ==== Mask values for IO registers ==== */
/* ---- OSTM0 ---- */
#define OSTM0_OSTMnCMP_OSTMnCMP                 (0xFFFFFFFFuL)

#define OSTM0_OSTMnCNT_OSTMnCNT                 (0xFFFFFFFFuL)

#define OSTM0_OSTMnTE_OSTMnTE                   (0x01u)

#define OSTM0_OSTMnTS_OSTMnTS                   (0x01u)

#define OSTM0_OSTMnTT_OSTMnTT                   (0x01u)

#define OSTM0_OSTMnCTL_MD0                      (0x00000001uL)
#define OSTM0_OSTMnCTL_MD1                      (0x00000002uL)

/* ---- OSTM1 ---- */
#define OSTM1_OSTMnCMP_OSTMnCMP                 (0xFFFFFFFFuL)

#define OSTM1_OSTMnCNT_OSTMnCNT                 (0xFFFFFFFFuL)

#define OSTM1_OSTMnTE_OSTMnTE                   (0x01u)

#define OSTM1_OSTMnTS_OSTMnTS                   (0x01u)

#define OSTM1_OSTMnTT_OSTMnTT                   (0x01u)

#define OSTM1_OSTMnCTL_MD0                      (0x00000001uL)
#define OSTM1_OSTMnCTL_MD1                      (0x00000002uL)

/* ---- OSTMn ---- */
#define OSTMn_OSTMnCMP_OSTMnCMP                 (0xFFFFFFFFuL)

#define OSTMn_OSTMnCNT_OSTMnCNT                 (0xFFFFFFFFuL)

#define OSTMn_OSTMnTE_OSTMnTE                   (0x01u)

#define OSTMn_OSTMnTS_OSTMnTS                   (0x01u)

#define OSTMn_OSTMnTT_OSTMnTT                   (0x01u)

#define OSTMn_OSTMnCTL_MD0                      (0x00000001uL)
#define OSTMn_OSTMnCTL_MD1                      (0x00000002uL)


/* ==== Shift values for IO registers ==== */
/* ---- OSTM0 ---- */
#define OSTM0_OSTMnCMP_OSTMnCMP_SHIFT           (0u)

#define OSTM0_OSTMnCNT_OSTMnCNT_SHIFT           (0u)

#define OSTM0_OSTMnTE_OSTMnTE_SHIFT             (0u)

#define OSTM0_OSTMnTS_OSTMnTS_SHIFT             (0u)

#define OSTM0_OSTMnTT_OSTMnTT_SHIFT             (0u)

#define OSTM0_OSTMnCTL_MD0_SHIFT                (0u)
#define OSTM0_OSTMnCTL_MD1_SHIFT                (1u)

/* ---- OSTM1 ---- */
#define OSTM1_OSTMnCMP_OSTMnCMP_SHIFT           (0u)

#define OSTM1_OSTMnCNT_OSTMnCNT_SHIFT           (0u)

#define OSTM1_OSTMnTE_OSTMnTE_SHIFT             (0u)

#define OSTM1_OSTMnTS_OSTMnTS_SHIFT             (0u)

#define OSTM1_OSTMnTT_OSTMnTT_SHIFT             (0u)

#define OSTM1_OSTMnCTL_MD0_SHIFT                (0u)
#define OSTM1_OSTMnCTL_MD1_SHIFT                (1u)

/* ---- OSTMn ---- */
#define OSTMn_OSTMnCMP_OSTMnCMP_SHIFT           (0u)

#define OSTMn_OSTMnCNT_OSTMnCNT_SHIFT           (0u)

#define OSTMn_OSTMnTE_OSTMnTE_SHIFT             (0u)

#define OSTMn_OSTMnTS_OSTMnTS_SHIFT             (0u)

#define OSTMn_OSTMnTT_OSTMnTT_SHIFT             (0u)

#define OSTMn_OSTMnCTL_MD0_SHIFT                (0u)
#define OSTMn_OSTMnCTL_MD1_SHIFT                (1u)


#endif /* OSTM_IOBITMASK_H */

/* End of File */
