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
* File Name : ieb_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef IEB_IODEFINE_H
#define IEB_IODEFINE_H
/* ->SEC M1.10.1 : Not magic number */

struct st_ieb
{                                                          /* IEB              */
    volatile uint8_t   B0BCR;                                  /*  B0BCR           */
    volatile uint8_t   dummy495[3];                            /*                  */
    volatile uint8_t   B0PSR;                                  /*  B0PSR           */
    volatile uint8_t   dummy496[3];                            /*                  */
    volatile uint16_t B0UAR;                                  /*  B0UAR           */
    volatile uint8_t   dummy497[2];                            /*                  */
    volatile uint16_t B0SAR;                                  /*  B0SAR           */
    volatile uint8_t   dummy498[2];                            /*                  */
    volatile uint16_t B0PAR;                                  /*  B0PAR           */
    volatile uint8_t   dummy499[2];                            /*                  */
    volatile uint16_t B0RSA;                                  /*  B0RSA           */
    volatile uint8_t   dummy500[2];                            /*                  */
    volatile uint8_t   B0CDR;                                  /*  B0CDR           */
    volatile uint8_t   dummy501[3];                            /*                  */
    volatile uint8_t   B0TCD;                                  /*  B0TCD           */
    volatile uint8_t   dummy502[3];                            /*                  */
    volatile uint8_t   B0RCD;                                  /*  B0RCD           */
    volatile uint8_t   dummy503[3];                            /*                  */
    volatile uint8_t   B0DLR;                                  /*  B0DLR           */
    volatile uint8_t   dummy504[3];                            /*                  */
    volatile uint8_t   B0TDL;                                  /*  B0TDL           */
    volatile uint8_t   dummy505[3];                            /*                  */
    volatile uint8_t   B0RDL;                                  /*  B0RDL           */
    volatile uint8_t   dummy506[3];                            /*                  */
    volatile uint8_t   B0CKS;                                  /*  B0CKS           */
    volatile uint8_t   dummy507[3];                            /*                  */
    volatile uint8_t   B0TMS;                                  /*  B0TMS           */
    volatile uint8_t   dummy508[3];                            /*                  */
    volatile uint8_t   B0PCR;                                  /*  B0PCR           */
    volatile uint8_t   dummy509[3];                            /*                  */
    volatile uint16_t B0BSR;                                  /*  B0BSR           */
    volatile uint8_t   dummy510[2];                            /*                  */
    volatile uint8_t   B0SSR;                                  /*  B0SSR           */
    volatile uint8_t   dummy511[3];                            /*                  */
    volatile uint8_t   B0USR;                                  /*  B0USR           */
    volatile uint8_t   dummy512[3];                            /*                  */
    volatile uint8_t   B0ISR;                                  /*  B0ISR           */
    volatile uint8_t   dummy513[3];                            /*                  */
    volatile uint8_t   B0ESR;                                  /*  B0ESR           */
    volatile uint8_t   dummy514[3];                            /*                  */
    volatile uint8_t   B0FSR;                                  /*  B0FSR           */
    volatile uint8_t   dummy515[3];                            /*                  */
    volatile uint8_t   B0SCR;                                  /*  B0SCR           */
    volatile uint8_t   dummy516[3];                            /*                  */
    volatile uint8_t   B0CCR;                                  /*  B0CCR           */
    volatile uint8_t   dummy517[3];                            /*                  */
    volatile uint8_t   B0STC0;                                 /*  B0STC0          */
    volatile uint8_t   dummy518[3];                            /*                  */
    volatile uint8_t   B0STC1;                                 /*  B0STC1          */
    volatile uint8_t   dummy519[3];                            /*                  */
    volatile uint8_t   B0DR;                                   /*  B0DR            */
};


#define IEB     (*(struct st_ieb     *)0xFCFEF000uL) /* IEB */


#define IEBB0BCR IEB.B0BCR
#define IEBB0PSR IEB.B0PSR
#define IEBB0UAR IEB.B0UAR
#define IEBB0SAR IEB.B0SAR
#define IEBB0PAR IEB.B0PAR
#define IEBB0RSA IEB.B0RSA
#define IEBB0CDR IEB.B0CDR
#define IEBB0TCD IEB.B0TCD
#define IEBB0RCD IEB.B0RCD
#define IEBB0DLR IEB.B0DLR
#define IEBB0TDL IEB.B0TDL
#define IEBB0RDL IEB.B0RDL
#define IEBB0CKS IEB.B0CKS
#define IEBB0TMS IEB.B0TMS
#define IEBB0PCR IEB.B0PCR
#define IEBB0BSR IEB.B0BSR
#define IEBB0SSR IEB.B0SSR
#define IEBB0USR IEB.B0USR
#define IEBB0ISR IEB.B0ISR
#define IEBB0ESR IEB.B0ESR
#define IEBB0FSR IEB.B0FSR
#define IEBB0SCR IEB.B0SCR
#define IEBB0CCR IEB.B0CCR
#define IEBB0STC0 IEB.B0STC0
#define IEBB0STC1 IEB.B0STC1
#define IEBB0DR IEB.B0DR
/* <-SEC M1.10.1 */
#endif
