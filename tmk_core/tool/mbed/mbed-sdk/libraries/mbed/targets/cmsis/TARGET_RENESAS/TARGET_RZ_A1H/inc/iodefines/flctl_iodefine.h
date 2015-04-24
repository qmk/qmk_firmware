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
* File Name : flctl_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef FLCTL_IODEFINE_H
#define FLCTL_IODEFINE_H
/* ->SEC M1.10.1 : Not magic number */

struct st_flctl
{                                                          /* FLCTL            */
    volatile uint32_t  FLCMNCR;                                /*  FLCMNCR         */
    volatile uint32_t  FLCMDCR;                                /*  FLCMDCR         */
    volatile uint32_t  FLCMCDR;                                /*  FLCMCDR         */
    volatile uint32_t  FLADR;                                  /*  FLADR           */
    volatile uint32_t  FLDATAR;                                /*  FLDATAR         */
    volatile uint32_t  FLDTCNTR;                               /*  FLDTCNTR        */
    volatile uint32_t  FLINTDMACR;                             /*  FLINTDMACR      */
    volatile uint32_t  FLBSYTMR;                               /*  FLBSYTMR        */
    volatile uint32_t  FLBSYCNT;                               /*  FLBSYCNT        */
    volatile uint8_t   dummy555[8];                            /*                  */
    volatile uint8_t   FLTRCR;                                 /*  FLTRCR          */
    volatile uint8_t   dummy556[15];                           /*                  */
    volatile uint32_t  FLADR2;                                 /*  FLADR2          */
    volatile uint8_t   dummy557[16];                           /*                  */
    volatile uint32_t  FLDTFIFO;                               /*  FLDTFIFO        */
    volatile uint8_t   dummy558[12];                           /*                  */
    volatile uint32_t  FLECFIFO;                               /*  FLECFIFO        */
};


#define FLCTL   (*(struct st_flctl   *)0xFCFF4000uL) /* FLCTL */


#define FLCTLFLCMNCR FLCTL.FLCMNCR
#define FLCTLFLCMDCR FLCTL.FLCMDCR
#define FLCTLFLCMCDR FLCTL.FLCMCDR
#define FLCTLFLADR FLCTL.FLADR
#define FLCTLFLDATAR FLCTL.FLDATAR
#define FLCTLFLDTCNTR FLCTL.FLDTCNTR
#define FLCTLFLINTDMACR FLCTL.FLINTDMACR
#define FLCTLFLBSYTMR FLCTL.FLBSYTMR
#define FLCTLFLBSYCNT FLCTL.FLBSYCNT
#define FLCTLFLTRCR FLCTL.FLTRCR
#define FLCTLFLADR2 FLCTL.FLADR2
#define FLCTLFLDTFIFO FLCTL.FLDTFIFO
#define FLCTLFLECFIFO FLCTL.FLECFIFO
/* <-SEC M1.10.1 */
#endif
