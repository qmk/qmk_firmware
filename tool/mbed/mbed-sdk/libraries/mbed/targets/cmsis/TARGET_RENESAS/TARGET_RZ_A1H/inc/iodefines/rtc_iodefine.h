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
* File Name : rtc_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef RTC_IODEFINE_H
#define RTC_IODEFINE_H
/* ->SEC M1.10.1 : Not magic number */

struct st_rtc
{                                                          /* RTC              */
    volatile uint8_t   R64CNT;                                 /*  R64CNT          */
    volatile uint8_t   dummy537[1];                            /*                  */
    volatile uint8_t   RSECCNT;                                /*  RSECCNT         */
    volatile uint8_t   dummy538[1];                            /*                  */
    volatile uint8_t   RMINCNT;                                /*  RMINCNT         */
    volatile uint8_t   dummy539[1];                            /*                  */
    volatile uint8_t   RHRCNT;                                 /*  RHRCNT          */
    volatile uint8_t   dummy540[1];                            /*                  */
    volatile uint8_t   RWKCNT;                                 /*  RWKCNT          */
    volatile uint8_t   dummy541[1];                            /*                  */
    volatile uint8_t   RDAYCNT;                                /*  RDAYCNT         */
    volatile uint8_t   dummy542[1];                            /*                  */
    volatile uint8_t   RMONCNT;                                /*  RMONCNT         */
    volatile uint8_t   dummy543[1];                            /*                  */
    volatile uint16_t RYRCNT;                                 /*  RYRCNT          */
    volatile uint8_t   RSECAR;                                 /*  RSECAR          */
    volatile uint8_t   dummy544[1];                            /*                  */
    volatile uint8_t   RMINAR;                                 /*  RMINAR          */
    volatile uint8_t   dummy545[1];                            /*                  */
    volatile uint8_t   RHRAR;                                  /*  RHRAR           */
    volatile uint8_t   dummy546[1];                            /*                  */
    volatile uint8_t   RWKAR;                                  /*  RWKAR           */
    volatile uint8_t   dummy547[1];                            /*                  */
    volatile uint8_t   RDAYAR;                                 /*  RDAYAR          */
    volatile uint8_t   dummy548[1];                            /*                  */
    volatile uint8_t   RMONAR;                                 /*  RMONAR          */
    volatile uint8_t   dummy549[1];                            /*                  */
    volatile uint8_t   RCR1;                                   /*  RCR1            */
    volatile uint8_t   dummy550[1];                            /*                  */
    volatile uint8_t   RCR2;                                   /*  RCR2            */
    volatile uint8_t   dummy551[1];                            /*                  */
    volatile uint16_t RYRAR;                                  /*  RYRAR           */
    volatile uint8_t   dummy552[2];                            /*                  */
    volatile uint8_t   RCR3;                                   /*  RCR3            */
    volatile uint8_t   dummy553[1];                            /*                  */
    volatile uint8_t   RCR5;                                   /*  RCR5            */
    volatile uint8_t   dummy554[3];                            /*                  */
    volatile uint16_t RFRH;                                   /*  RFRH            */
    volatile uint16_t RFRL;                                   /*  RFRL            */
};


#define RTC     (*(struct st_rtc     *)0xFCFF1000uL) /* RTC */


#define RTCR64CNT RTC.R64CNT
#define RTCRSECCNT RTC.RSECCNT
#define RTCRMINCNT RTC.RMINCNT
#define RTCRHRCNT RTC.RHRCNT
#define RTCRWKCNT RTC.RWKCNT
#define RTCRDAYCNT RTC.RDAYCNT
#define RTCRMONCNT RTC.RMONCNT
#define RTCRYRCNT RTC.RYRCNT
#define RTCRSECAR RTC.RSECAR
#define RTCRMINAR RTC.RMINAR
#define RTCRHRAR RTC.RHRAR
#define RTCRWKAR RTC.RWKAR
#define RTCRDAYAR RTC.RDAYAR
#define RTCRMONAR RTC.RMONAR
#define RTCRCR1 RTC.RCR1
#define RTCRCR2 RTC.RCR2
#define RTCRYRAR RTC.RYRAR
#define RTCRCR3 RTC.RCR3
#define RTCRCR5 RTC.RCR5
#define RTCRFRH RTC.RFRH
#define RTCRFRL RTC.RFRL
/* <-SEC M1.10.1 */
#endif
