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
* File Name : disc_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef DISC_IODEFINE_H
#define DISC_IODEFINE_H
/* ->SEC M1.10.1 : Not magic number */

struct st_disc
{                                                          /* DISC             */
    volatile uint32_t  DOCMCR;                                 /*  DOCMCR          */
    volatile uint32_t  DOCMSTR;                                /*  DOCMSTR         */
    volatile uint32_t  DOCMCLSTR;                              /*  DOCMCLSTR       */
    volatile uint32_t  DOCMIENR;                               /*  DOCMIENR        */
    volatile uint8_t   dummy1[4];                              /*                  */
    volatile uint32_t  DOCMPMR;                                /*  DOCMPMR         */
    volatile uint32_t  DOCMECRCR;                              /*  DOCMECRCR       */
    volatile uint32_t  DOCMCCRCR;                              /*  DOCMCCRCR       */
    volatile uint32_t  DOCMSPXR;                               /*  DOCMSPXR        */
    volatile uint32_t  DOCMSPYR;                               /*  DOCMSPYR        */
    volatile uint32_t  DOCMSZXR;                               /*  DOCMSZXR        */
    volatile uint32_t  DOCMSZYR;                               /*  DOCMSZYR        */
    volatile uint32_t  DOCMCRCIR;                              /*  DOCMCRCIR       */
};


#define DISC0   (*(struct st_disc    *)0xFCFFA800uL) /* DISC0 */
#define DISC1   (*(struct st_disc    *)0xFCFFB000uL) /* DISC1 */


/* Start of channnel array defines of DISC */

/* Channnel array defines of DISC */
/*(Sample) value = DISC[ channel ]->DOCMCR; */
#define DISC_COUNT  2
#define DISC_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &DISC0, &DISC1 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */

/* End of channnel array defines of DISC */


#define DISC0DOCMCR DISC0.DOCMCR
#define DISC0DOCMSTR DISC0.DOCMSTR
#define DISC0DOCMCLSTR DISC0.DOCMCLSTR
#define DISC0DOCMIENR DISC0.DOCMIENR
#define DISC0DOCMPMR DISC0.DOCMPMR
#define DISC0DOCMECRCR DISC0.DOCMECRCR
#define DISC0DOCMCCRCR DISC0.DOCMCCRCR
#define DISC0DOCMSPXR DISC0.DOCMSPXR
#define DISC0DOCMSPYR DISC0.DOCMSPYR
#define DISC0DOCMSZXR DISC0.DOCMSZXR
#define DISC0DOCMSZYR DISC0.DOCMSZYR
#define DISC0DOCMCRCIR DISC0.DOCMCRCIR
#define DISC1DOCMCR DISC1.DOCMCR
#define DISC1DOCMSTR DISC1.DOCMSTR
#define DISC1DOCMCLSTR DISC1.DOCMCLSTR
#define DISC1DOCMIENR DISC1.DOCMIENR
#define DISC1DOCMPMR DISC1.DOCMPMR
#define DISC1DOCMECRCR DISC1.DOCMECRCR
#define DISC1DOCMCCRCR DISC1.DOCMCCRCR
#define DISC1DOCMSPXR DISC1.DOCMSPXR
#define DISC1DOCMSPYR DISC1.DOCMSPYR
#define DISC1DOCMSZXR DISC1.DOCMSZXR
#define DISC1DOCMSZYR DISC1.DOCMSZYR
#define DISC1DOCMCRCIR DISC1.DOCMCRCIR
/* <-SEC M1.10.1 */
#endif
