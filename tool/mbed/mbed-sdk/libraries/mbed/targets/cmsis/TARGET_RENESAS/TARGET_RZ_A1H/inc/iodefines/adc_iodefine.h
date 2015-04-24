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
* File Name : adc_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef ADC_IODEFINE_H
#define ADC_IODEFINE_H
/* ->SEC M1.10.1 : Not magic number */

struct st_adc
{                                                          /* ADC              */
    volatile uint16_t ADDRA;                                  /*  ADDRA           */
    volatile uint16_t ADDRB;                                  /*  ADDRB           */
    volatile uint16_t ADDRC;                                  /*  ADDRC           */
    volatile uint16_t ADDRD;                                  /*  ADDRD           */
    volatile uint16_t ADDRE;                                  /*  ADDRE           */
    volatile uint16_t ADDRF;                                  /*  ADDRF           */
    volatile uint16_t ADDRG;                                  /*  ADDRG           */
    volatile uint16_t ADDRH;                                  /*  ADDRH           */
    volatile uint8_t   dummy32[16];                            /*                  */
    volatile uint16_t ADCMPHA;                                /*  ADCMPHA         */
    volatile uint16_t ADCMPLA;                                /*  ADCMPLA         */
    volatile uint16_t ADCMPHB;                                /*  ADCMPHB         */
    volatile uint16_t ADCMPLB;                                /*  ADCMPLB         */
    volatile uint16_t ADCMPHC;                                /*  ADCMPHC         */
    volatile uint16_t ADCMPLC;                                /*  ADCMPLC         */
    volatile uint16_t ADCMPHD;                                /*  ADCMPHD         */
    volatile uint16_t ADCMPLD;                                /*  ADCMPLD         */
    volatile uint16_t ADCMPHE;                                /*  ADCMPHE         */
    volatile uint16_t ADCMPLE;                                /*  ADCMPLE         */
    volatile uint16_t ADCMPHF;                                /*  ADCMPHF         */
    volatile uint16_t ADCMPLF;                                /*  ADCMPLF         */
    volatile uint16_t ADCMPHG;                                /*  ADCMPHG         */
    volatile uint16_t ADCMPLG;                                /*  ADCMPLG         */
    volatile uint16_t ADCMPHH;                                /*  ADCMPHH         */
    volatile uint16_t ADCMPLH;                                /*  ADCMPLH         */
    volatile uint8_t   dummy33[32];                            /*                  */
    volatile uint16_t ADCSR;                                  /*  ADCSR           */
    volatile uint16_t ADCMPER;                                /*  ADCMPER         */
    volatile uint16_t ADCMPSR;                                /*  ADCMPSR         */
};


#define ADC     (*(struct st_adc     *)0xE8005800uL) /* ADC */


#define ADCADDRA ADC.ADDRA
#define ADCADDRB ADC.ADDRB
#define ADCADDRC ADC.ADDRC
#define ADCADDRD ADC.ADDRD
#define ADCADDRE ADC.ADDRE
#define ADCADDRF ADC.ADDRF
#define ADCADDRG ADC.ADDRG
#define ADCADDRH ADC.ADDRH
#define ADCADCMPHA ADC.ADCMPHA
#define ADCADCMPLA ADC.ADCMPLA
#define ADCADCMPHB ADC.ADCMPHB
#define ADCADCMPLB ADC.ADCMPLB
#define ADCADCMPHC ADC.ADCMPHC
#define ADCADCMPLC ADC.ADCMPLC
#define ADCADCMPHD ADC.ADCMPHD
#define ADCADCMPLD ADC.ADCMPLD
#define ADCADCMPHE ADC.ADCMPHE
#define ADCADCMPLE ADC.ADCMPLE
#define ADCADCMPHF ADC.ADCMPHF
#define ADCADCMPLF ADC.ADCMPLF
#define ADCADCMPHG ADC.ADCMPHG
#define ADCADCMPLG ADC.ADCMPLG
#define ADCADCMPHH ADC.ADCMPHH
#define ADCADCMPLH ADC.ADCMPLH
#define ADCADCSR ADC.ADCSR
#define ADCADCMPER ADC.ADCMPER
#define ADCADCMPSR ADC.ADCMPSR
/* <-SEC M1.10.1 */
#endif
