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
* File Name : bsc_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef BSC_IODEFINE_H
#define BSC_IODEFINE_H
/* ->SEC M1.10.1 : Not magic number */

struct st_bsc
{                                                          /* BSC              */
    volatile uint32_t  CMNCR;                                  /*  CMNCR           */
#define BSC_CSnBCR_COUNT 6
    volatile uint32_t  CS0BCR;                                 /*  CS0BCR          */
    volatile uint32_t  CS1BCR;                                 /*  CS1BCR          */
    volatile uint32_t  CS2BCR;                                 /*  CS2BCR          */
    volatile uint32_t  CS3BCR;                                 /*  CS3BCR          */
    volatile uint32_t  CS4BCR;                                 /*  CS4BCR          */
    volatile uint32_t  CS5BCR;                                 /*  CS5BCR          */
    volatile uint8_t   dummy4[12];                             /*                  */
#define BSC_CSnWCR_COUNT 6
    volatile uint32_t  CS0WCR;                                 /*  CS0WCR          */
    volatile uint32_t  CS1WCR;                                 /*  CS1WCR          */
    volatile uint32_t  CS2WCR;                                 /*  CS2WCR          */
    volatile uint32_t  CS3WCR;                                 /*  CS3WCR          */
    volatile uint32_t  CS4WCR;                                 /*  CS4WCR          */
    volatile uint32_t  CS5WCR;                                 /*  CS5WCR          */
    volatile uint8_t   dummy5[12];                             /*                  */
    volatile uint32_t  SDCR;                                   /*  SDCR            */
    volatile uint32_t  RTCSR;                                  /*  RTCSR           */
    volatile uint32_t  RTCNT;                                  /*  RTCNT           */
    volatile uint32_t  RTCOR;                                  /*  RTCOR           */
    volatile uint8_t   dummy6[4];                              /*                  */
#define BSC_TOSCORn_COUNT 6
    volatile uint32_t  TOSCOR0;                                /*  TOSCOR0         */
    volatile uint32_t  TOSCOR1;                                /*  TOSCOR1         */
    volatile uint32_t  TOSCOR2;                                /*  TOSCOR2         */
    volatile uint32_t  TOSCOR3;                                /*  TOSCOR3         */
    volatile uint32_t  TOSCOR4;                                /*  TOSCOR4         */
    volatile uint32_t  TOSCOR5;                                /*  TOSCOR5         */
    volatile uint8_t   dummy7[8];                              /*                  */
    volatile uint32_t  TOSTR;                                  /*  TOSTR           */
    volatile uint32_t  TOENR;                                  /*  TOENR           */
};


#define BSC     (*(struct st_bsc     *)0x3FFFC000uL) /* BSC */


#define BSCCMNCR BSC.CMNCR
#define BSCCS0BCR BSC.CS0BCR
#define BSCCS1BCR BSC.CS1BCR
#define BSCCS2BCR BSC.CS2BCR
#define BSCCS3BCR BSC.CS3BCR
#define BSCCS4BCR BSC.CS4BCR
#define BSCCS5BCR BSC.CS5BCR
#define BSCCS0WCR BSC.CS0WCR
#define BSCCS1WCR BSC.CS1WCR
#define BSCCS2WCR BSC.CS2WCR
#define BSCCS3WCR BSC.CS3WCR
#define BSCCS4WCR BSC.CS4WCR
#define BSCCS5WCR BSC.CS5WCR
#define BSCSDCR BSC.SDCR
#define BSCRTCSR BSC.RTCSR
#define BSCRTCNT BSC.RTCNT
#define BSCRTCOR BSC.RTCOR
#define BSCTOSCOR0 BSC.TOSCOR0
#define BSCTOSCOR1 BSC.TOSCOR1
#define BSCTOSCOR2 BSC.TOSCOR2
#define BSCTOSCOR3 BSC.TOSCOR3
#define BSCTOSCOR4 BSC.TOSCOR4
#define BSCTOSCOR5 BSC.TOSCOR5
#define BSCTOSTR BSC.TOSTR
#define BSCTOENR BSC.TOENR
/* <-SEC M1.10.1 */
#endif
