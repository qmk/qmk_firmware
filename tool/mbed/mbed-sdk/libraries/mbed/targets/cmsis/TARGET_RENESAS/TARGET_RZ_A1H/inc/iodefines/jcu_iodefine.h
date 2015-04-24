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
* File Name : jcu_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef JCU_IODEFINE_H
#define JCU_IODEFINE_H
/* ->SEC M1.10.1 : Not magic number */

struct st_jcu
{                                                          /* JCU              */
    volatile uint8_t   JCMOD;                                  /*  JCMOD           */
    volatile uint8_t   JCCMD;                                  /*  JCCMD           */
    volatile uint8_t   dummy145[1];                            /*                  */
    volatile uint8_t   JCQTN;                                  /*  JCQTN           */
    volatile uint8_t   JCHTN;                                  /*  JCHTN           */
    volatile uint8_t   JCDRIU;                                 /*  JCDRIU          */
    volatile uint8_t   JCDRID;                                 /*  JCDRID          */
    volatile uint8_t   JCVSZU;                                 /*  JCVSZU          */
    volatile uint8_t   JCVSZD;                                 /*  JCVSZD          */
    volatile uint8_t   JCHSZU;                                 /*  JCHSZU          */
    volatile uint8_t   JCHSZD;                                 /*  JCHSZD          */
    volatile uint8_t   JCDTCU;                                 /*  JCDTCU          */
    volatile uint8_t   JCDTCM;                                 /*  JCDTCM          */
    volatile uint8_t   JCDTCD;                                 /*  JCDTCD          */
    volatile uint8_t   JINTE0;                                 /*  JINTE0          */
    volatile uint8_t   JINTS0;                                 /*  JINTS0          */
    volatile uint8_t   JCDERR;                                 /*  JCDERR          */
    volatile uint8_t   JCRST;                                  /*  JCRST           */
    volatile uint8_t   dummy146[46];                           /*                  */
    volatile uint32_t  JIFECNT;                                /*  JIFECNT         */
    volatile uint32_t  JIFESA;                                 /*  JIFESA          */
    volatile uint32_t  JIFESOFST;                              /*  JIFESOFST       */
    volatile uint32_t  JIFEDA;                                 /*  JIFEDA          */
    volatile uint32_t  JIFESLC;                                /*  JIFESLC         */
    volatile uint32_t  JIFEDDC;                                /*  JIFEDDC         */
    volatile uint32_t  JIFDCNT;                                /*  JIFDCNT         */
    volatile uint32_t  JIFDSA;                                 /*  JIFDSA          */
    volatile uint32_t  JIFDDOFST;                              /*  JIFDDOFST       */
    volatile uint32_t  JIFDDA;                                 /*  JIFDDA          */
    volatile uint32_t  JIFDSDC;                                /*  JIFDSDC         */
    volatile uint32_t  JIFDDLC;                                /*  JIFDDLC         */
    volatile uint32_t  JIFDADT;                                /*  JIFDADT         */
    volatile uint8_t   dummy147[24];                           /*                  */
    volatile uint32_t  JINTE1;                                 /*  JINTE1          */
    volatile uint32_t  JINTS1;                                 /*  JINTS1          */
    volatile uint32_t  JIFESVSZ;                               /*  JIFESVSZ        */
    volatile uint32_t  JIFESHSZ;                               /*  JIFESHSZ        */
    volatile uint8_t   dummy148[100];                          /*                  */
/* start of struct st_jcu_from_jcqtbl0 */
    volatile uint8_t   JCQTBL0;                                /*  JCQTBL0         */
    volatile uint8_t   dummy149[63];                           /*                  */
/* end of struct st_jcu_from_jcqtbl0 */
/* start of struct st_jcu_from_jcqtbl0 */
    volatile uint8_t   JCQTBL1;                                /*  JCQTBL1         */
    volatile uint8_t   dummy150[63];                           /*                  */
/* end of struct st_jcu_from_jcqtbl0 */
/* start of struct st_jcu_from_jcqtbl0 */
    volatile uint8_t   JCQTBL2;                                /*  JCQTBL2         */
    volatile uint8_t   dummy151[63];                           /*                  */
/* end of struct st_jcu_from_jcqtbl0 */
/* start of struct st_jcu_from_jcqtbl0 */
    volatile uint8_t   JCQTBL3;                                /*  JCQTBL3         */
    volatile uint8_t   dummy152[63];                           /*                  */
/* end of struct st_jcu_from_jcqtbl0 */
    volatile uint8_t   JCHTBD0;                                /*  JCHTBD0         */
    volatile uint8_t   dummy153[31];                           /*                  */
    volatile uint8_t   JCHTBA0;                                /*  JCHTBA0         */
    volatile uint8_t   dummy154[223];                          /*                  */
    volatile uint8_t   JCHTBD1;                                /*  JCHTBD1         */
    volatile uint8_t   dummy155[31];                           /*                  */
    volatile uint8_t   JCHTBA1;                                /*  JCHTBA1         */
};


struct st_jcu_from_jcqtbl0
{
    volatile uint8_t   JCQTBL0;                                /*  JCQTBL0         */
    volatile uint8_t   dummy1[63];                             /*                  */
};


#define JCU     (*(struct st_jcu     *)0xE8017000uL) /* JCU */


/* Start of channnel array defines of JCU */

/* Channnel array defines of JCU_JCQTBL0 */
/*(Sample) value = JCU_JCQTBL0[ channel ]->JCQTBL0; */
#define JCU_JCQTBL0_COUNT  4
#define JCU_JCQTBL0_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &JCU_FROM_JCQTBL0, &JCU_FROM_JCQTBL1, &JCU_FROM_JCQTBL2, &JCU_FROM_JCQTBL3 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define JCU_FROM_JCQTBL0 (*(struct st_jcu_from_jcqtbl0 *)&JCU.JCQTBL0) /* JCU_FROM_JCQTBL0 */
#define JCU_FROM_JCQTBL1 (*(struct st_jcu_from_jcqtbl0 *)&JCU.JCQTBL1) /* JCU_FROM_JCQTBL1 */
#define JCU_FROM_JCQTBL2 (*(struct st_jcu_from_jcqtbl0 *)&JCU.JCQTBL2) /* JCU_FROM_JCQTBL2 */
#define JCU_FROM_JCQTBL3 (*(struct st_jcu_from_jcqtbl0 *)&JCU.JCQTBL3) /* JCU_FROM_JCQTBL3 */

/* End of channnel array defines of JCU */


#define JCUJCMOD JCU.JCMOD
#define JCUJCCMD JCU.JCCMD
#define JCUJCQTN JCU.JCQTN
#define JCUJCHTN JCU.JCHTN
#define JCUJCDRIU JCU.JCDRIU
#define JCUJCDRID JCU.JCDRID
#define JCUJCVSZU JCU.JCVSZU
#define JCUJCVSZD JCU.JCVSZD
#define JCUJCHSZU JCU.JCHSZU
#define JCUJCHSZD JCU.JCHSZD
#define JCUJCDTCU JCU.JCDTCU
#define JCUJCDTCM JCU.JCDTCM
#define JCUJCDTCD JCU.JCDTCD
#define JCUJINTE0 JCU.JINTE0
#define JCUJINTS0 JCU.JINTS0
#define JCUJCDERR JCU.JCDERR
#define JCUJCRST JCU.JCRST
#define JCUJIFECNT JCU.JIFECNT
#define JCUJIFESA JCU.JIFESA
#define JCUJIFESOFST JCU.JIFESOFST
#define JCUJIFEDA JCU.JIFEDA
#define JCUJIFESLC JCU.JIFESLC
#define JCUJIFEDDC JCU.JIFEDDC
#define JCUJIFDCNT JCU.JIFDCNT
#define JCUJIFDSA JCU.JIFDSA
#define JCUJIFDDOFST JCU.JIFDDOFST
#define JCUJIFDDA JCU.JIFDDA
#define JCUJIFDSDC JCU.JIFDSDC
#define JCUJIFDDLC JCU.JIFDDLC
#define JCUJIFDADT JCU.JIFDADT
#define JCUJINTE1 JCU.JINTE1
#define JCUJINTS1 JCU.JINTS1
#define JCUJIFESVSZ JCU.JIFESVSZ
#define JCUJIFESHSZ JCU.JIFESHSZ
#define JCUJCQTBL0 JCU.JCQTBL0
#define JCUJCQTBL1 JCU.JCQTBL1
#define JCUJCQTBL2 JCU.JCQTBL2
#define JCUJCQTBL3 JCU.JCQTBL3
#define JCUJCHTBD0 JCU.JCHTBD0
#define JCUJCHTBA0 JCU.JCHTBA0
#define JCUJCHTBD1 JCU.JCHTBD1
#define JCUJCHTBA1 JCU.JCHTBA1
/* <-SEC M1.10.1 */
#endif
