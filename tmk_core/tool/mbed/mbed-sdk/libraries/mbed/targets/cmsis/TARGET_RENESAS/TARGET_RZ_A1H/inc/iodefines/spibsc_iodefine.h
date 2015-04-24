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
* File Name : spibsc_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef SPIBSC_IODEFINE_H
#define SPIBSC_IODEFINE_H
/* ->SEC M1.10.1 : Not magic number */

struct st_spibsc
{                                                          /* SPIBSC           */
    volatile uint32_t  CMNCR;                                  /*  CMNCR           */
    volatile uint32_t  SSLDR;                                  /*  SSLDR           */
    volatile uint32_t  SPBCR;                                  /*  SPBCR           */
    volatile uint32_t  DRCR;                                   /*  DRCR            */
    volatile uint32_t  DRCMR;                                  /*  DRCMR           */
    volatile uint32_t  DREAR;                                  /*  DREAR           */
    volatile uint32_t  DROPR;                                  /*  DROPR           */
    volatile uint32_t  DRENR;                                  /*  DRENR           */
    volatile uint32_t  SMCR;                                   /*  SMCR            */
    volatile uint32_t  SMCMR;                                  /*  SMCMR           */
    volatile uint32_t  SMADR;                                  /*  SMADR           */
    volatile uint32_t  SMOPR;                                  /*  SMOPR           */
    volatile uint32_t  SMENR;                                  /*  SMENR           */
    volatile uint8_t   dummy1[4];                              /*                  */
    union iodefine_reg32_t  SMRDR0;                        /*  SMRDR0          */
    union iodefine_reg32_t  SMRDR1;                        /*  SMRDR1          */
    union iodefine_reg32_t  SMWDR0;                        /*  SMWDR0          */
    union iodefine_reg32_t  SMWDR1;                        /*  SMWDR1          */
    
    volatile uint32_t  CMNSR;                                  /*  CMNSR           */
    volatile uint8_t   dummy2[12];                             /*                  */
    volatile uint32_t  DRDMCR;                                 /*  DRDMCR          */
    volatile uint32_t  DRDRENR;                                /*  DRDRENR         */
    volatile uint32_t  SMDMCR;                                 /*  SMDMCR          */
    volatile uint32_t  SMDRENR;                                /*  SMDRENR         */
};


#define SPIBSC0 (*(struct st_spibsc  *)0x3FEFA000uL) /* SPIBSC0 */
#define SPIBSC1 (*(struct st_spibsc  *)0x3FEFB000uL) /* SPIBSC1 */


/* Start of channnel array defines of SPIBSC */

/* Channnel array defines of SPIBSC */
/*(Sample) value = SPIBSC[ channel ]->CMNCR; */
#define SPIBSC_COUNT  2
#define SPIBSC_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &SPIBSC0, &SPIBSC1 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */

/* End of channnel array defines of SPIBSC */


#define CMNCR_0 SPIBSC0.CMNCR
#define SSLDR_0 SPIBSC0.SSLDR
#define SPBCR_0 SPIBSC0.SPBCR
#define DRCR_0 SPIBSC0.DRCR
#define DRCMR_0 SPIBSC0.DRCMR
#define DREAR_0 SPIBSC0.DREAR
#define DROPR_0 SPIBSC0.DROPR
#define DRENR_0 SPIBSC0.DRENR
#define SMCR_0 SPIBSC0.SMCR
#define SMCMR_0 SPIBSC0.SMCMR
#define SMADR_0 SPIBSC0.SMADR
#define SMOPR_0 SPIBSC0.SMOPR
#define SMENR_0 SPIBSC0.SMENR
#define SMRDR0_0   SPIBSC0.SMRDR0.UINT32
#define SMRDR0_0L  SPIBSC0.SMRDR0.UINT16[L]
#define SMRDR0_0H  SPIBSC0.SMRDR0.UINT16[H]
#define SMRDR0_0LL SPIBSC0.SMRDR0.UINT8[LL]
#define SMRDR0_0LH SPIBSC0.SMRDR0.UINT8[LH]
#define SMRDR0_0HL SPIBSC0.SMRDR0.UINT8[HL]
#define SMRDR0_0HH SPIBSC0.SMRDR0.UINT8[HH]
#define SMRDR1_0   SPIBSC0.SMRDR1.UINT32
#define SMRDR1_0L  SPIBSC0.SMRDR1.UINT16[L]
#define SMRDR1_0H  SPIBSC0.SMRDR1.UINT16[H]
#define SMRDR1_0LL SPIBSC0.SMRDR1.UINT8[LL]
#define SMRDR1_0LH SPIBSC0.SMRDR1.UINT8[LH]
#define SMRDR1_0HL SPIBSC0.SMRDR1.UINT8[HL]
#define SMRDR1_0HH SPIBSC0.SMRDR1.UINT8[HH]
#define SMWDR0_0   SPIBSC0.SMWDR0.UINT32
#define SMWDR0_0L  SPIBSC0.SMWDR0.UINT16[L]
#define SMWDR0_0H  SPIBSC0.SMWDR0.UINT16[H]
#define SMWDR0_0LL SPIBSC0.SMWDR0.UINT8[LL]
#define SMWDR0_0LH SPIBSC0.SMWDR0.UINT8[LH]
#define SMWDR0_0HL SPIBSC0.SMWDR0.UINT8[HL]
#define SMWDR0_0HH SPIBSC0.SMWDR0.UINT8[HH]
#define SMWDR1_0   SPIBSC0.SMWDR1.UINT32
#define SMWDR1_0L  SPIBSC0.SMWDR1.UINT16[L]
#define SMWDR1_0H  SPIBSC0.SMWDR1.UINT16[H]
#define SMWDR1_0LL SPIBSC0.SMWDR1.UINT8[LL]
#define SMWDR1_0LH SPIBSC0.SMWDR1.UINT8[LH]
#define SMWDR1_0HL SPIBSC0.SMWDR1.UINT8[HL]
#define SMWDR1_0HH SPIBSC0.SMWDR1.UINT8[HH]
#define CMNSR_0 SPIBSC0.CMNSR
#define DRDMCR_0 SPIBSC0.DRDMCR
#define DRDRENR_0 SPIBSC0.DRDRENR
#define SMDMCR_0 SPIBSC0.SMDMCR
#define SMDRENR_0 SPIBSC0.SMDRENR
#define CMNCR_1 SPIBSC1.CMNCR
#define SSLDR_1 SPIBSC1.SSLDR
#define SPBCR_1 SPIBSC1.SPBCR
#define DRCR_1 SPIBSC1.DRCR
#define DRCMR_1 SPIBSC1.DRCMR
#define DREAR_1 SPIBSC1.DREAR
#define DROPR_1 SPIBSC1.DROPR
#define DRENR_1 SPIBSC1.DRENR
#define SMCR_1 SPIBSC1.SMCR
#define SMCMR_1 SPIBSC1.SMCMR
#define SMADR_1 SPIBSC1.SMADR
#define SMOPR_1 SPIBSC1.SMOPR
#define SMENR_1 SPIBSC1.SMENR
#define SMRDR0_1   SPIBSC1.SMRDR0.UINT32
#define SMRDR0_1L  SPIBSC1.SMRDR0.UINT16[L]
#define SMRDR0_1H  SPIBSC1.SMRDR0.UINT16[H]
#define SMRDR0_1LL SPIBSC1.SMRDR0.UINT8[LL]
#define SMRDR0_1LH SPIBSC1.SMRDR0.UINT8[LH]
#define SMRDR0_1HL SPIBSC1.SMRDR0.UINT8[HL]
#define SMRDR0_1HH SPIBSC1.SMRDR0.UINT8[HH]
#define SMRDR1_1   SPIBSC1.SMRDR1.UINT32
#define SMRDR1_1L  SPIBSC1.SMRDR1.UINT16[L]
#define SMRDR1_1H  SPIBSC1.SMRDR1.UINT16[H]
#define SMRDR1_1LL SPIBSC1.SMRDR1.UINT8[LL]
#define SMRDR1_1LH SPIBSC1.SMRDR1.UINT8[LH]
#define SMRDR1_1HL SPIBSC1.SMRDR1.UINT8[HL]
#define SMRDR1_1HH SPIBSC1.SMRDR1.UINT8[HH]
#define SMWDR0_1   SPIBSC1.SMWDR0.UINT32
#define SMWDR0_1L  SPIBSC1.SMWDR0.UINT16[L]
#define SMWDR0_1H  SPIBSC1.SMWDR0.UINT16[H]
#define SMWDR0_1LL SPIBSC1.SMWDR0.UINT8[LL]
#define SMWDR0_1LH SPIBSC1.SMWDR0.UINT8[LH]
#define SMWDR0_1HL SPIBSC1.SMWDR0.UINT8[HL]
#define SMWDR0_1HH SPIBSC1.SMWDR0.UINT8[HH]
#define SMWDR1_1   SPIBSC1.SMWDR1.UINT32
#define SMWDR1_1L  SPIBSC1.SMWDR1.UINT16[L]
#define SMWDR1_1H  SPIBSC1.SMWDR1.UINT16[H]
#define SMWDR1_1LL SPIBSC1.SMWDR1.UINT8[LL]
#define SMWDR1_1LH SPIBSC1.SMWDR1.UINT8[LH]
#define SMWDR1_1HL SPIBSC1.SMWDR1.UINT8[HL]
#define SMWDR1_1HH SPIBSC1.SMWDR1.UINT8[HH]
#define CMNSR_1 SPIBSC1.CMNSR
#define DRDMCR_1 SPIBSC1.DRDMCR
#define DRDRENR_1 SPIBSC1.DRDRENR
#define SMDMCR_1 SPIBSC1.SMDMCR
#define SMDRENR_1 SPIBSC1.SMDRENR
/* <-SEC M1.10.1 */
#endif
