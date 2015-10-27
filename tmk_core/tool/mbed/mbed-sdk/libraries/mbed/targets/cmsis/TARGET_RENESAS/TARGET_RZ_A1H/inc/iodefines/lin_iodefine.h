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
* File Name : lin_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef LIN_IODEFINE_H
#define LIN_IODEFINE_H
/* ->MISRA 18.4 : Pack unpack union */ /* ->SEC M1.6.2 */
/* ->SEC M1.10.1 : Not magic number */

struct st_lin
{                                                          /* LIN              */
    volatile uint8_t   dummy1[1];                              /*                  */
    volatile uint8_t   RLN3nLWBR;                              /*  RLN3nLWBR       */
    union iodefine_reg16_8_t  RLN3nLBRP01;                     /*  RLN3nLBRP01 */
    
    volatile uint8_t   RLN3nLSTC;                              /*  RLN3nLSTC       */
    volatile uint8_t   dummy2[3];                              /*                  */
    volatile uint8_t   RLN3nLMD;                               /*  RLN3nLMD        */
    volatile uint8_t   RLN3nLBFC;                              /*  RLN3nLBFC       */
    volatile uint8_t   RLN3nLSC;                               /*  RLN3nLSC        */
    volatile uint8_t   RLN3nLWUP;                              /*  RLN3nLWUP       */
    volatile uint8_t   RLN3nLIE;                               /*  RLN3nLIE        */
    volatile uint8_t   RLN3nLEDE;                              /*  RLN3nLEDE       */
    volatile uint8_t   RLN3nLCUC;                              /*  RLN3nLCUC       */
    volatile uint8_t   dummy3[1];                              /*                  */
    volatile uint8_t   RLN3nLTRC;                              /*  RLN3nLTRC       */
    volatile uint8_t   RLN3nLMST;                              /*  RLN3nLMST       */
    volatile uint8_t   RLN3nLST;                               /*  RLN3nLST        */
    volatile uint8_t   RLN3nLEST;                              /*  RLN3nLEST       */
    volatile uint8_t   RLN3nLDFC;                              /*  RLN3nLDFC       */
    volatile uint8_t   RLN3nLIDB;                              /*  RLN3nLIDB       */
    volatile uint8_t   RLN3nLCBR;                              /*  RLN3nLCBR       */
    volatile uint8_t   RLN3nLUDB0;                             /*  RLN3nLUDB0      */
#define LIN_LDBn_COUNT 8
    volatile uint8_t   RLN3nLDBR1;                             /*  RLN3nLDBR1      */
    volatile uint8_t   RLN3nLDBR2;                             /*  RLN3nLDBR2      */
    volatile uint8_t   RLN3nLDBR3;                             /*  RLN3nLDBR3      */
    volatile uint8_t   RLN3nLDBR4;                             /*  RLN3nLDBR4      */
    volatile uint8_t   RLN3nLDBR5;                             /*  RLN3nLDBR5      */
    volatile uint8_t   RLN3nLDBR6;                             /*  RLN3nLDBR6      */
    volatile uint8_t   RLN3nLDBR7;                             /*  RLN3nLDBR7      */
    volatile uint8_t   RLN3nLDBR8;                             /*  RLN3nLDBR8      */
    volatile uint8_t   RLN3nLUOER;                             /*  RLN3nLUOER      */
    volatile uint8_t   RLN3nLUOR1;                             /*  RLN3nLUOR1      */
    volatile uint8_t   dummy4[2];                              /*                  */
    union iodefine_reg16_8_t  RLN3nLUTDR;                      /*  RLN3nLUTDR  */
    union iodefine_reg16_8_t  RLN3nLURDR;                      /*  RLN3nLURDR  */
    union iodefine_reg16_8_t  RLN3nLUWTDR;                     /*  RLN3nLUWTDR */
    
};


#define LIN0    (*(struct st_lin     *)0xFCFE9000uL) /* LIN0 */
#define LIN1    (*(struct st_lin     *)0xFCFE9800uL) /* LIN1 */


/* Start of channnel array defines of LIN */

/* Channnel array defines of LIN */
/*(Sample) value = LIN[ channel ]->RLN3nLWBR; */
#define LIN_COUNT  2
#define LIN_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &LIN0, &LIN1 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */

/* End of channnel array defines of LIN */


#define LIN0RLN30LWBR LIN0.RLN3nLWBR
#define LIN0RLN30LBRP01 LIN0.RLN3nLBRP01.UINT16
#define LIN0RLN30LBRP0 LIN0.RLN3nLBRP01.UINT8[L]
#define LIN0RLN30LBRP1 LIN0.RLN3nLBRP01.UINT8[H]
#define LIN0RLN30LSTC LIN0.RLN3nLSTC
#define LIN0RLN30LMD LIN0.RLN3nLMD
#define LIN0RLN30LBFC LIN0.RLN3nLBFC
#define LIN0RLN30LSC LIN0.RLN3nLSC
#define LIN0RLN30LWUP LIN0.RLN3nLWUP
#define LIN0RLN30LIE LIN0.RLN3nLIE
#define LIN0RLN30LEDE LIN0.RLN3nLEDE
#define LIN0RLN30LCUC LIN0.RLN3nLCUC
#define LIN0RLN30LTRC LIN0.RLN3nLTRC
#define LIN0RLN30LMST LIN0.RLN3nLMST
#define LIN0RLN30LST LIN0.RLN3nLST
#define LIN0RLN30LEST LIN0.RLN3nLEST
#define LIN0RLN30LDFC LIN0.RLN3nLDFC
#define LIN0RLN30LIDB LIN0.RLN3nLIDB
#define LIN0RLN30LCBR LIN0.RLN3nLCBR
#define LIN0RLN30LUDB0 LIN0.RLN3nLUDB0
#define LIN0RLN30LDBR1 LIN0.RLN3nLDBR1
#define LIN0RLN30LDBR2 LIN0.RLN3nLDBR2
#define LIN0RLN30LDBR3 LIN0.RLN3nLDBR3
#define LIN0RLN30LDBR4 LIN0.RLN3nLDBR4
#define LIN0RLN30LDBR5 LIN0.RLN3nLDBR5
#define LIN0RLN30LDBR6 LIN0.RLN3nLDBR6
#define LIN0RLN30LDBR7 LIN0.RLN3nLDBR7
#define LIN0RLN30LDBR8 LIN0.RLN3nLDBR8
#define LIN0RLN30LUOER LIN0.RLN3nLUOER
#define LIN0RLN30LUOR1 LIN0.RLN3nLUOR1
#define LIN0RLN30LUTDR LIN0.RLN3nLUTDR.UINT16
#define LIN0RLN30LUTDRL LIN0.RLN3nLUTDR.UINT8[L]
#define LIN0RLN30LUTDRH LIN0.RLN3nLUTDR.UINT8[H]
#define LIN0RLN30LURDR LIN0.RLN3nLURDR.UINT16
#define LIN0RLN30LURDRL LIN0.RLN3nLURDR.UINT8[L]
#define LIN0RLN30LURDRH LIN0.RLN3nLURDR.UINT8[H]
#define LIN0RLN30LUWTDR LIN0.RLN3nLUWTDR.UINT16
#define LIN0RLN30LUWTDRL LIN0.RLN3nLUWTDR.UINT8[L]
#define LIN0RLN30LUWTDRH LIN0.RLN3nLUWTDR.UINT8[H]
#define LIN1RLN31LWBR LIN1.RLN3nLWBR
#define LIN1RLN31LBRP01 LIN1.RLN3nLBRP01.UINT16
#define LIN1RLN31LBRP0 LIN1.RLN3nLBRP01.UINT8[L]
#define LIN1RLN31LBRP1 LIN1.RLN3nLBRP01.UINT8[H]
#define LIN1RLN31LSTC LIN1.RLN3nLSTC
#define LIN1RLN31LMD LIN1.RLN3nLMD
#define LIN1RLN31LBFC LIN1.RLN3nLBFC
#define LIN1RLN31LSC LIN1.RLN3nLSC
#define LIN1RLN31LWUP LIN1.RLN3nLWUP
#define LIN1RLN31LIE LIN1.RLN3nLIE
#define LIN1RLN31LEDE LIN1.RLN3nLEDE
#define LIN1RLN31LCUC LIN1.RLN3nLCUC
#define LIN1RLN31LTRC LIN1.RLN3nLTRC
#define LIN1RLN31LMST LIN1.RLN3nLMST
#define LIN1RLN31LST LIN1.RLN3nLST
#define LIN1RLN31LEST LIN1.RLN3nLEST
#define LIN1RLN31LDFC LIN1.RLN3nLDFC
#define LIN1RLN31LIDB LIN1.RLN3nLIDB
#define LIN1RLN31LCBR LIN1.RLN3nLCBR
#define LIN1RLN31LUDB0 LIN1.RLN3nLUDB0
#define LIN1RLN31LDBR1 LIN1.RLN3nLDBR1
#define LIN1RLN31LDBR2 LIN1.RLN3nLDBR2
#define LIN1RLN31LDBR3 LIN1.RLN3nLDBR3
#define LIN1RLN31LDBR4 LIN1.RLN3nLDBR4
#define LIN1RLN31LDBR5 LIN1.RLN3nLDBR5
#define LIN1RLN31LDBR6 LIN1.RLN3nLDBR6
#define LIN1RLN31LDBR7 LIN1.RLN3nLDBR7
#define LIN1RLN31LDBR8 LIN1.RLN3nLDBR8
#define LIN1RLN31LUOER LIN1.RLN3nLUOER
#define LIN1RLN31LUOR1 LIN1.RLN3nLUOR1
#define LIN1RLN31LUTDR LIN1.RLN3nLUTDR.UINT16
#define LIN1RLN31LUTDRL LIN1.RLN3nLUTDR.UINT8[L]
#define LIN1RLN31LUTDRH LIN1.RLN3nLUTDR.UINT8[H]
#define LIN1RLN31LURDR LIN1.RLN3nLURDR.UINT16
#define LIN1RLN31LURDRL LIN1.RLN3nLURDR.UINT8[L]
#define LIN1RLN31LURDRH LIN1.RLN3nLURDR.UINT8[H]
#define LIN1RLN31LUWTDR LIN1.RLN3nLUWTDR.UINT16
#define LIN1RLN31LUWTDRL LIN1.RLN3nLUWTDR.UINT8[L]
#define LIN1RLN31LUWTDRH LIN1.RLN3nLUWTDR.UINT8[H]
/* <-SEC M1.10.1 */
/* <-MISRA 18.4 */ /* <-SEC M1.6.2 */
#endif
