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
* File Name : inb_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef INB_IODEFINE_H
#define INB_IODEFINE_H

struct st_inb
{                                                          /* INB              */
    volatile uint32_t  RMPR;                                   /*  RMPR            */
#define INB_AXIBUSCTLn_COUNT 11
    volatile uint32_t  AXIBUSCTL0;                             /*  AXIBUSCTL0      */
    volatile uint32_t  AXIBUSCTL1;                             /*  AXIBUSCTL1      */
    volatile uint32_t  AXIBUSCTL2;                             /*  AXIBUSCTL2      */
    volatile uint32_t  AXIBUSCTL3;                             /*  AXIBUSCTL3      */
    volatile uint32_t  AXIBUSCTL4;                             /*  AXIBUSCTL4      */
    volatile uint32_t  AXIBUSCTL5;                             /*  AXIBUSCTL5      */
    volatile uint32_t  AXIBUSCTL6;                             /*  AXIBUSCTL6      */
    volatile uint32_t  AXIBUSCTL7;                             /*  AXIBUSCTL7      */
    volatile uint32_t  AXIBUSCTL8;                             /*  AXIBUSCTL8      */
    volatile uint32_t  AXIBUSCTL9;                             /*  AXIBUSCTL9      */
    volatile uint32_t  AXIBUSCTL10;                            /*  AXIBUSCTL10     */
#define INB_AXIRERRCTLn_COUNT 4
    volatile uint32_t  AXIRERRCTL0;                            /*  AXIRERRCTL0     */
    volatile uint32_t  AXIRERRCTL1;                            /*  AXIRERRCTL1     */
    volatile uint32_t  AXIRERRCTL2;                            /*  AXIRERRCTL2     */
    volatile uint32_t  AXIRERRCTL3;                            /*  AXIRERRCTL3     */
#define INB_AXIRERRSTn_COUNT 4
    volatile uint32_t  AXIRERRST0;                             /*  AXIRERRST0      */
    volatile uint32_t  AXIRERRST1;                             /*  AXIRERRST1      */
    volatile uint32_t  AXIRERRST2;                             /*  AXIRERRST2      */
    volatile uint32_t  AXIRERRST3;                             /*  AXIRERRST3      */
#define INB_AXIRERRCLRn_COUNT 4
    volatile uint32_t  AXIRERRCLR0;                            /*  AXIRERRCLR0     */
    volatile uint32_t  AXIRERRCLR1;                            /*  AXIRERRCLR1     */
    volatile uint32_t  AXIRERRCLR2;                            /*  AXIRERRCLR2     */
    volatile uint32_t  AXIRERRCLR3;                            /*  AXIRERRCLR3     */
};


#define INB     (*(struct st_inb     *)0xFCFE1A00uL) /* INB */


#define INBRMPR INB.RMPR
#define INBAXIBUSCTL0 INB.AXIBUSCTL0
#define INBAXIBUSCTL1 INB.AXIBUSCTL1
#define INBAXIBUSCTL2 INB.AXIBUSCTL2
#define INBAXIBUSCTL3 INB.AXIBUSCTL3
#define INBAXIBUSCTL4 INB.AXIBUSCTL4
#define INBAXIBUSCTL5 INB.AXIBUSCTL5
#define INBAXIBUSCTL6 INB.AXIBUSCTL6
#define INBAXIBUSCTL7 INB.AXIBUSCTL7
#define INBAXIBUSCTL8 INB.AXIBUSCTL8
#define INBAXIBUSCTL9 INB.AXIBUSCTL9
#define INBAXIBUSCTL10 INB.AXIBUSCTL10
#define INBAXIRERRCTL0 INB.AXIRERRCTL0
#define INBAXIRERRCTL1 INB.AXIRERRCTL1
#define INBAXIRERRCTL2 INB.AXIRERRCTL2
#define INBAXIRERRCTL3 INB.AXIRERRCTL3
#define INBAXIRERRST0 INB.AXIRERRST0
#define INBAXIRERRST1 INB.AXIRERRST1
#define INBAXIRERRST2 INB.AXIRERRST2
#define INBAXIRERRST3 INB.AXIRERRST3
#define INBAXIRERRCLR0 INB.AXIRERRCLR0
#define INBAXIRERRCLR1 INB.AXIRERRCLR1
#define INBAXIRERRCLR2 INB.AXIRERRCLR2
#define INBAXIRERRCLR3 INB.AXIRERRCLR3
#endif
