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
* File Name : mlb_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef MLB_IODEFINE_H
#define MLB_IODEFINE_H
/* ->QAC 0639 : Over 127 members (C90) */
/* ->QAC 0857 : Over 1024 #define (C90) */
/* ->SEC M1.10.1 : Not magic number */

struct st_mlb
{                                                          /* MLB              */
    volatile uint32_t  DCCR;                                   /*  DCCR            */
    volatile uint32_t  SSCR;                                   /*  SSCR            */
    volatile uint32_t  SDCR;                                   /*  SDCR            */
    volatile uint32_t  SMCR;                                   /*  SMCR            */
    volatile uint8_t   dummy156[12];                           /*                  */
    volatile uint32_t  VCCR;                                   /*  VCCR            */
    volatile uint32_t  SBCR;                                   /*  SBCR            */
    volatile uint32_t  ABCR;                                   /*  ABCR            */
    volatile uint32_t  CBCR;                                   /*  CBCR            */
    volatile uint32_t  IBCR;                                   /*  IBCR            */
    volatile uint32_t  CICR;                                   /*  CICR            */
    volatile uint8_t   dummy157[12];                           /*                  */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR0;                                  /*  CECR0           */
    volatile uint32_t  CSCR0;                                  /*  CSCR0           */
    volatile uint32_t  CCBCR0;                                 /*  CCBCR0          */
    volatile uint32_t  CNBCR0;                                 /*  CNBCR0          */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR1;                                  /*  CECR1           */
    volatile uint32_t  CSCR1;                                  /*  CSCR1           */
    volatile uint32_t  CCBCR1;                                 /*  CCBCR1          */
    volatile uint32_t  CNBCR1;                                 /*  CNBCR1          */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR2;                                  /*  CECR2           */
    volatile uint32_t  CSCR2;                                  /*  CSCR2           */
    volatile uint32_t  CCBCR2;                                 /*  CCBCR2          */
    volatile uint32_t  CNBCR2;                                 /*  CNBCR2          */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR3;                                  /*  CECR3           */
    volatile uint32_t  CSCR3;                                  /*  CSCR3           */
    volatile uint32_t  CCBCR3;                                 /*  CCBCR3          */
    volatile uint32_t  CNBCR3;                                 /*  CNBCR3          */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR4;                                  /*  CECR4           */
    volatile uint32_t  CSCR4;                                  /*  CSCR4           */
    volatile uint32_t  CCBCR4;                                 /*  CCBCR4          */
    volatile uint32_t  CNBCR4;                                 /*  CNBCR4          */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR5;                                  /*  CECR5           */
    volatile uint32_t  CSCR5;                                  /*  CSCR5           */
    volatile uint32_t  CCBCR5;                                 /*  CCBCR5          */
    volatile uint32_t  CNBCR5;                                 /*  CNBCR5          */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR6;                                  /*  CECR6           */
    volatile uint32_t  CSCR6;                                  /*  CSCR6           */
    volatile uint32_t  CCBCR6;                                 /*  CCBCR6          */
    volatile uint32_t  CNBCR6;                                 /*  CNBCR6          */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR7;                                  /*  CECR7           */
    volatile uint32_t  CSCR7;                                  /*  CSCR7           */
    volatile uint32_t  CCBCR7;                                 /*  CCBCR7          */
    volatile uint32_t  CNBCR7;                                 /*  CNBCR7          */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR8;                                  /*  CECR8           */
    volatile uint32_t  CSCR8;                                  /*  CSCR8           */
    volatile uint32_t  CCBCR8;                                 /*  CCBCR8          */
    volatile uint32_t  CNBCR8;                                 /*  CNBCR8          */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR9;                                  /*  CECR9           */
    volatile uint32_t  CSCR9;                                  /*  CSCR9           */
    volatile uint32_t  CCBCR9;                                 /*  CCBCR9          */
    volatile uint32_t  CNBCR9;                                 /*  CNBCR9          */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR10;                                 /*  CECR10          */
    volatile uint32_t  CSCR10;                                 /*  CSCR10          */
    volatile uint32_t  CCBCR10;                                /*  CCBCR10         */
    volatile uint32_t  CNBCR10;                                /*  CNBCR10         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR11;                                 /*  CECR11          */
    volatile uint32_t  CSCR11;                                 /*  CSCR11          */
    volatile uint32_t  CCBCR11;                                /*  CCBCR11         */
    volatile uint32_t  CNBCR11;                                /*  CNBCR11         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR12;                                 /*  CECR12          */
    volatile uint32_t  CSCR12;                                 /*  CSCR12          */
    volatile uint32_t  CCBCR12;                                /*  CCBCR12         */
    volatile uint32_t  CNBCR12;                                /*  CNBCR12         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR13;                                 /*  CECR13          */
    volatile uint32_t  CSCR13;                                 /*  CSCR13          */
    volatile uint32_t  CCBCR13;                                /*  CCBCR13         */
    volatile uint32_t  CNBCR13;                                /*  CNBCR13         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR14;                                 /*  CECR14          */
    volatile uint32_t  CSCR14;                                 /*  CSCR14          */
    volatile uint32_t  CCBCR14;                                /*  CCBCR14         */
    volatile uint32_t  CNBCR14;                                /*  CNBCR14         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR15;                                 /*  CECR15          */
    volatile uint32_t  CSCR15;                                 /*  CSCR15          */
    volatile uint32_t  CCBCR15;                                /*  CCBCR15         */
    volatile uint32_t  CNBCR15;                                /*  CNBCR15         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR16;                                 /*  CECR16          */
    volatile uint32_t  CSCR16;                                 /*  CSCR16          */
    volatile uint32_t  CCBCR16;                                /*  CCBCR16         */
    volatile uint32_t  CNBCR16;                                /*  CNBCR16         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR17;                                 /*  CECR17          */
    volatile uint32_t  CSCR17;                                 /*  CSCR17          */
    volatile uint32_t  CCBCR17;                                /*  CCBCR17         */
    volatile uint32_t  CNBCR17;                                /*  CNBCR17         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR18;                                 /*  CECR18          */
    volatile uint32_t  CSCR18;                                 /*  CSCR18          */
    volatile uint32_t  CCBCR18;                                /*  CCBCR18         */
    volatile uint32_t  CNBCR18;                                /*  CNBCR18         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR19;                                 /*  CECR19          */
    volatile uint32_t  CSCR19;                                 /*  CSCR19          */
    volatile uint32_t  CCBCR19;                                /*  CCBCR19         */
    volatile uint32_t  CNBCR19;                                /*  CNBCR19         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR20;                                 /*  CECR20          */
    volatile uint32_t  CSCR20;                                 /*  CSCR20          */
    volatile uint32_t  CCBCR20;                                /*  CCBCR20         */
    volatile uint32_t  CNBCR20;                                /*  CNBCR20         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR21;                                 /*  CECR21          */
    volatile uint32_t  CSCR21;                                 /*  CSCR21          */
    volatile uint32_t  CCBCR21;                                /*  CCBCR21         */
    volatile uint32_t  CNBCR21;                                /*  CNBCR21         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR22;                                 /*  CECR22          */
    volatile uint32_t  CSCR22;                                 /*  CSCR22          */
    volatile uint32_t  CCBCR22;                                /*  CCBCR22         */
    volatile uint32_t  CNBCR22;                                /*  CNBCR22         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR23;                                 /*  CECR23          */
    volatile uint32_t  CSCR23;                                 /*  CSCR23          */
    volatile uint32_t  CCBCR23;                                /*  CCBCR23         */
    volatile uint32_t  CNBCR23;                                /*  CNBCR23         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR24;                                 /*  CECR24          */
    volatile uint32_t  CSCR24;                                 /*  CSCR24          */
    volatile uint32_t  CCBCR24;                                /*  CCBCR24         */
    volatile uint32_t  CNBCR24;                                /*  CNBCR24         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR25;                                 /*  CECR25          */
    volatile uint32_t  CSCR25;                                 /*  CSCR25          */
    volatile uint32_t  CCBCR25;                                /*  CCBCR25         */
    volatile uint32_t  CNBCR25;                                /*  CNBCR25         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR26;                                 /*  CECR26          */
    volatile uint32_t  CSCR26;                                 /*  CSCR26          */
    volatile uint32_t  CCBCR26;                                /*  CCBCR26         */
    volatile uint32_t  CNBCR26;                                /*  CNBCR26         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR27;                                 /*  CECR27          */
    volatile uint32_t  CSCR27;                                 /*  CSCR27          */
    volatile uint32_t  CCBCR27;                                /*  CCBCR27         */
    volatile uint32_t  CNBCR27;                                /*  CNBCR27         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR28;                                 /*  CECR28          */
    volatile uint32_t  CSCR28;                                 /*  CSCR28          */
    volatile uint32_t  CCBCR28;                                /*  CCBCR28         */
    volatile uint32_t  CNBCR28;                                /*  CNBCR28         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR29;                                 /*  CECR29          */
    volatile uint32_t  CSCR29;                                 /*  CSCR29          */
    volatile uint32_t  CCBCR29;                                /*  CCBCR29         */
    volatile uint32_t  CNBCR29;                                /*  CNBCR29         */
/* end of struct st_mlb_from_cecr0 */
/* start of struct st_mlb_from_cecr0 */
    volatile uint32_t  CECR30;                                 /*  CECR30          */
    volatile uint32_t  CSCR30;                                 /*  CSCR30          */
    volatile uint32_t  CCBCR30;                                /*  CCBCR30         */
    volatile uint32_t  CNBCR30;                                /*  CNBCR30         */
/* end of struct st_mlb_from_cecr0 */
    volatile uint8_t   dummy158[80];                           /*                  */
#define MLB_LCBCR0_COUNT 31
    volatile uint32_t  LCBCR0;                                 /*  LCBCR0          */
    volatile uint32_t  LCBCR1;                                 /*  LCBCR1          */
    volatile uint32_t  LCBCR2;                                 /*  LCBCR2          */
    volatile uint32_t  LCBCR3;                                 /*  LCBCR3          */
    volatile uint32_t  LCBCR4;                                 /*  LCBCR4          */
    volatile uint32_t  LCBCR5;                                 /*  LCBCR5          */
    volatile uint32_t  LCBCR6;                                 /*  LCBCR6          */
    volatile uint32_t  LCBCR7;                                 /*  LCBCR7          */
    volatile uint32_t  LCBCR8;                                 /*  LCBCR8          */
    volatile uint32_t  LCBCR9;                                 /*  LCBCR9          */
    volatile uint32_t  LCBCR10;                                /*  LCBCR10         */
    volatile uint32_t  LCBCR11;                                /*  LCBCR11         */
    volatile uint32_t  LCBCR12;                                /*  LCBCR12         */
    volatile uint32_t  LCBCR13;                                /*  LCBCR13         */
    volatile uint32_t  LCBCR14;                                /*  LCBCR14         */
    volatile uint32_t  LCBCR15;                                /*  LCBCR15         */
    volatile uint32_t  LCBCR16;                                /*  LCBCR16         */
    volatile uint32_t  LCBCR17;                                /*  LCBCR17         */
    volatile uint32_t  LCBCR18;                                /*  LCBCR18         */
    volatile uint32_t  LCBCR19;                                /*  LCBCR19         */
    volatile uint32_t  LCBCR20;                                /*  LCBCR20         */
    volatile uint32_t  LCBCR21;                                /*  LCBCR21         */
    volatile uint32_t  LCBCR22;                                /*  LCBCR22         */
    volatile uint32_t  LCBCR23;                                /*  LCBCR23         */
    volatile uint32_t  LCBCR24;                                /*  LCBCR24         */
    volatile uint32_t  LCBCR25;                                /*  LCBCR25         */
    volatile uint32_t  LCBCR26;                                /*  LCBCR26         */
    volatile uint32_t  LCBCR27;                                /*  LCBCR27         */
    volatile uint32_t  LCBCR28;                                /*  LCBCR28         */
    volatile uint32_t  LCBCR29;                                /*  LCBCR29         */
    volatile uint32_t  LCBCR30;                                /*  LCBCR30         */
};


struct st_mlb_from_cecr0
{
    volatile uint32_t  CECR0;                                  /*  CECR0           */
    volatile uint32_t  CSCR0;                                  /*  CSCR0           */
    volatile uint32_t  CCBCR0;                                 /*  CCBCR0          */
    volatile uint32_t  CNBCR0;                                 /*  CNBCR0          */
};


#define MLB     (*(struct st_mlb     *)0xE8034000uL) /* MLB */


/* Start of channnel array defines of MLB */

/* Channnel array defines of MLB_FROM_CECR0_ARRAY */
/*(Sample) value = MLB_FROM_CECR0_ARRAY[ channel ]->CECR0; */
#define MLB_FROM_CECR0_ARRAY_COUNT  31
#define MLB_FROM_CECR0_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &MLB_FROM_CECR0, &MLB_FROM_CECR1, &MLB_FROM_CECR2, &MLB_FROM_CECR3, &MLB_FROM_CECR4, &MLB_FROM_CECR5, &MLB_FROM_CECR6, &MLB_FROM_CECR7, \
    &MLB_FROM_CECR8, &MLB_FROM_CECR9, &MLB_FROM_CECR10, &MLB_FROM_CECR11, &MLB_FROM_CECR12, &MLB_FROM_CECR13, &MLB_FROM_CECR14, &MLB_FROM_CECR15, \
    &MLB_FROM_CECR16, &MLB_FROM_CECR17, &MLB_FROM_CECR18, &MLB_FROM_CECR19, &MLB_FROM_CECR20, &MLB_FROM_CECR21, &MLB_FROM_CECR22, &MLB_FROM_CECR23, \
    &MLB_FROM_CECR24, &MLB_FROM_CECR25, &MLB_FROM_CECR26, &MLB_FROM_CECR27, &MLB_FROM_CECR28, &MLB_FROM_CECR29, &MLB_FROM_CECR30 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define MLB_FROM_CECR0 (*(struct st_mlb_from_cecr0 *)&MLB.CECR0) /* MLB_FROM_CECR0 */
#define MLB_FROM_CECR1 (*(struct st_mlb_from_cecr0 *)&MLB.CECR1) /* MLB_FROM_CECR1 */
#define MLB_FROM_CECR2 (*(struct st_mlb_from_cecr0 *)&MLB.CECR2) /* MLB_FROM_CECR2 */
#define MLB_FROM_CECR3 (*(struct st_mlb_from_cecr0 *)&MLB.CECR3) /* MLB_FROM_CECR3 */
#define MLB_FROM_CECR4 (*(struct st_mlb_from_cecr0 *)&MLB.CECR4) /* MLB_FROM_CECR4 */
#define MLB_FROM_CECR5 (*(struct st_mlb_from_cecr0 *)&MLB.CECR5) /* MLB_FROM_CECR5 */
#define MLB_FROM_CECR6 (*(struct st_mlb_from_cecr0 *)&MLB.CECR6) /* MLB_FROM_CECR6 */
#define MLB_FROM_CECR7 (*(struct st_mlb_from_cecr0 *)&MLB.CECR7) /* MLB_FROM_CECR7 */
#define MLB_FROM_CECR8 (*(struct st_mlb_from_cecr0 *)&MLB.CECR8) /* MLB_FROM_CECR8 */
#define MLB_FROM_CECR9 (*(struct st_mlb_from_cecr0 *)&MLB.CECR9) /* MLB_FROM_CECR9 */
#define MLB_FROM_CECR10 (*(struct st_mlb_from_cecr0 *)&MLB.CECR10) /* MLB_FROM_CECR10 */
#define MLB_FROM_CECR11 (*(struct st_mlb_from_cecr0 *)&MLB.CECR11) /* MLB_FROM_CECR11 */
#define MLB_FROM_CECR12 (*(struct st_mlb_from_cecr0 *)&MLB.CECR12) /* MLB_FROM_CECR12 */
#define MLB_FROM_CECR13 (*(struct st_mlb_from_cecr0 *)&MLB.CECR13) /* MLB_FROM_CECR13 */
#define MLB_FROM_CECR14 (*(struct st_mlb_from_cecr0 *)&MLB.CECR14) /* MLB_FROM_CECR14 */
#define MLB_FROM_CECR15 (*(struct st_mlb_from_cecr0 *)&MLB.CECR15) /* MLB_FROM_CECR15 */
#define MLB_FROM_CECR16 (*(struct st_mlb_from_cecr0 *)&MLB.CECR16) /* MLB_FROM_CECR16 */
#define MLB_FROM_CECR17 (*(struct st_mlb_from_cecr0 *)&MLB.CECR17) /* MLB_FROM_CECR17 */
#define MLB_FROM_CECR18 (*(struct st_mlb_from_cecr0 *)&MLB.CECR18) /* MLB_FROM_CECR18 */
#define MLB_FROM_CECR19 (*(struct st_mlb_from_cecr0 *)&MLB.CECR19) /* MLB_FROM_CECR19 */
#define MLB_FROM_CECR20 (*(struct st_mlb_from_cecr0 *)&MLB.CECR20) /* MLB_FROM_CECR20 */
#define MLB_FROM_CECR21 (*(struct st_mlb_from_cecr0 *)&MLB.CECR21) /* MLB_FROM_CECR21 */
#define MLB_FROM_CECR22 (*(struct st_mlb_from_cecr0 *)&MLB.CECR22) /* MLB_FROM_CECR22 */
#define MLB_FROM_CECR23 (*(struct st_mlb_from_cecr0 *)&MLB.CECR23) /* MLB_FROM_CECR23 */
#define MLB_FROM_CECR24 (*(struct st_mlb_from_cecr0 *)&MLB.CECR24) /* MLB_FROM_CECR24 */
#define MLB_FROM_CECR25 (*(struct st_mlb_from_cecr0 *)&MLB.CECR25) /* MLB_FROM_CECR25 */
#define MLB_FROM_CECR26 (*(struct st_mlb_from_cecr0 *)&MLB.CECR26) /* MLB_FROM_CECR26 */
#define MLB_FROM_CECR27 (*(struct st_mlb_from_cecr0 *)&MLB.CECR27) /* MLB_FROM_CECR27 */
#define MLB_FROM_CECR28 (*(struct st_mlb_from_cecr0 *)&MLB.CECR28) /* MLB_FROM_CECR28 */
#define MLB_FROM_CECR29 (*(struct st_mlb_from_cecr0 *)&MLB.CECR29) /* MLB_FROM_CECR29 */
#define MLB_FROM_CECR30 (*(struct st_mlb_from_cecr0 *)&MLB.CECR30) /* MLB_FROM_CECR30 */

/* End of channnel array defines of MLB */


#define MLBDCCR MLB.DCCR
#define MLBSSCR MLB.SSCR
#define MLBSDCR MLB.SDCR
#define MLBSMCR MLB.SMCR
#define MLBVCCR MLB.VCCR
#define MLBSBCR MLB.SBCR
#define MLBABCR MLB.ABCR
#define MLBCBCR MLB.CBCR
#define MLBIBCR MLB.IBCR
#define MLBCICR MLB.CICR
#define MLBCECR0 MLB.CECR0
#define MLBCSCR0 MLB.CSCR0
#define MLBCCBCR0 MLB.CCBCR0
#define MLBCNBCR0 MLB.CNBCR0
#define MLBCECR1 MLB.CECR1
#define MLBCSCR1 MLB.CSCR1
#define MLBCCBCR1 MLB.CCBCR1
#define MLBCNBCR1 MLB.CNBCR1
#define MLBCECR2 MLB.CECR2
#define MLBCSCR2 MLB.CSCR2
#define MLBCCBCR2 MLB.CCBCR2
#define MLBCNBCR2 MLB.CNBCR2
#define MLBCECR3 MLB.CECR3
#define MLBCSCR3 MLB.CSCR3
#define MLBCCBCR3 MLB.CCBCR3
#define MLBCNBCR3 MLB.CNBCR3
#define MLBCECR4 MLB.CECR4
#define MLBCSCR4 MLB.CSCR4
#define MLBCCBCR4 MLB.CCBCR4
#define MLBCNBCR4 MLB.CNBCR4
#define MLBCECR5 MLB.CECR5
#define MLBCSCR5 MLB.CSCR5
#define MLBCCBCR5 MLB.CCBCR5
#define MLBCNBCR5 MLB.CNBCR5
#define MLBCECR6 MLB.CECR6
#define MLBCSCR6 MLB.CSCR6
#define MLBCCBCR6 MLB.CCBCR6
#define MLBCNBCR6 MLB.CNBCR6
#define MLBCECR7 MLB.CECR7
#define MLBCSCR7 MLB.CSCR7
#define MLBCCBCR7 MLB.CCBCR7
#define MLBCNBCR7 MLB.CNBCR7
#define MLBCECR8 MLB.CECR8
#define MLBCSCR8 MLB.CSCR8
#define MLBCCBCR8 MLB.CCBCR8
#define MLBCNBCR8 MLB.CNBCR8
#define MLBCECR9 MLB.CECR9
#define MLBCSCR9 MLB.CSCR9
#define MLBCCBCR9 MLB.CCBCR9
#define MLBCNBCR9 MLB.CNBCR9
#define MLBCECR10 MLB.CECR10
#define MLBCSCR10 MLB.CSCR10
#define MLBCCBCR10 MLB.CCBCR10
#define MLBCNBCR10 MLB.CNBCR10
#define MLBCECR11 MLB.CECR11
#define MLBCSCR11 MLB.CSCR11
#define MLBCCBCR11 MLB.CCBCR11
#define MLBCNBCR11 MLB.CNBCR11
#define MLBCECR12 MLB.CECR12
#define MLBCSCR12 MLB.CSCR12
#define MLBCCBCR12 MLB.CCBCR12
#define MLBCNBCR12 MLB.CNBCR12
#define MLBCECR13 MLB.CECR13
#define MLBCSCR13 MLB.CSCR13
#define MLBCCBCR13 MLB.CCBCR13
#define MLBCNBCR13 MLB.CNBCR13
#define MLBCECR14 MLB.CECR14
#define MLBCSCR14 MLB.CSCR14
#define MLBCCBCR14 MLB.CCBCR14
#define MLBCNBCR14 MLB.CNBCR14
#define MLBCECR15 MLB.CECR15
#define MLBCSCR15 MLB.CSCR15
#define MLBCCBCR15 MLB.CCBCR15
#define MLBCNBCR15 MLB.CNBCR15
#define MLBCECR16 MLB.CECR16
#define MLBCSCR16 MLB.CSCR16
#define MLBCCBCR16 MLB.CCBCR16
#define MLBCNBCR16 MLB.CNBCR16
#define MLBCECR17 MLB.CECR17
#define MLBCSCR17 MLB.CSCR17
#define MLBCCBCR17 MLB.CCBCR17
#define MLBCNBCR17 MLB.CNBCR17
#define MLBCECR18 MLB.CECR18
#define MLBCSCR18 MLB.CSCR18
#define MLBCCBCR18 MLB.CCBCR18
#define MLBCNBCR18 MLB.CNBCR18
#define MLBCECR19 MLB.CECR19
#define MLBCSCR19 MLB.CSCR19
#define MLBCCBCR19 MLB.CCBCR19
#define MLBCNBCR19 MLB.CNBCR19
#define MLBCECR20 MLB.CECR20
#define MLBCSCR20 MLB.CSCR20
#define MLBCCBCR20 MLB.CCBCR20
#define MLBCNBCR20 MLB.CNBCR20
#define MLBCECR21 MLB.CECR21
#define MLBCSCR21 MLB.CSCR21
#define MLBCCBCR21 MLB.CCBCR21
#define MLBCNBCR21 MLB.CNBCR21
#define MLBCECR22 MLB.CECR22
#define MLBCSCR22 MLB.CSCR22
#define MLBCCBCR22 MLB.CCBCR22
#define MLBCNBCR22 MLB.CNBCR22
#define MLBCECR23 MLB.CECR23
#define MLBCSCR23 MLB.CSCR23
#define MLBCCBCR23 MLB.CCBCR23
#define MLBCNBCR23 MLB.CNBCR23
#define MLBCECR24 MLB.CECR24
#define MLBCSCR24 MLB.CSCR24
#define MLBCCBCR24 MLB.CCBCR24
#define MLBCNBCR24 MLB.CNBCR24
#define MLBCECR25 MLB.CECR25
#define MLBCSCR25 MLB.CSCR25
#define MLBCCBCR25 MLB.CCBCR25
#define MLBCNBCR25 MLB.CNBCR25
#define MLBCECR26 MLB.CECR26
#define MLBCSCR26 MLB.CSCR26
#define MLBCCBCR26 MLB.CCBCR26
#define MLBCNBCR26 MLB.CNBCR26
#define MLBCECR27 MLB.CECR27
#define MLBCSCR27 MLB.CSCR27
#define MLBCCBCR27 MLB.CCBCR27
#define MLBCNBCR27 MLB.CNBCR27
#define MLBCECR28 MLB.CECR28
#define MLBCSCR28 MLB.CSCR28
#define MLBCCBCR28 MLB.CCBCR28
#define MLBCNBCR28 MLB.CNBCR28
#define MLBCECR29 MLB.CECR29
#define MLBCSCR29 MLB.CSCR29
#define MLBCCBCR29 MLB.CCBCR29
#define MLBCNBCR29 MLB.CNBCR29
#define MLBCECR30 MLB.CECR30
#define MLBCSCR30 MLB.CSCR30
#define MLBCCBCR30 MLB.CCBCR30
#define MLBCNBCR30 MLB.CNBCR30
#define MLBLCBCR0 MLB.LCBCR0
#define MLBLCBCR1 MLB.LCBCR1
#define MLBLCBCR2 MLB.LCBCR2
#define MLBLCBCR3 MLB.LCBCR3
#define MLBLCBCR4 MLB.LCBCR4
#define MLBLCBCR5 MLB.LCBCR5
#define MLBLCBCR6 MLB.LCBCR6
#define MLBLCBCR7 MLB.LCBCR7
#define MLBLCBCR8 MLB.LCBCR8
#define MLBLCBCR9 MLB.LCBCR9
#define MLBLCBCR10 MLB.LCBCR10
#define MLBLCBCR11 MLB.LCBCR11
#define MLBLCBCR12 MLB.LCBCR12
#define MLBLCBCR13 MLB.LCBCR13
#define MLBLCBCR14 MLB.LCBCR14
#define MLBLCBCR15 MLB.LCBCR15
#define MLBLCBCR16 MLB.LCBCR16
#define MLBLCBCR17 MLB.LCBCR17
#define MLBLCBCR18 MLB.LCBCR18
#define MLBLCBCR19 MLB.LCBCR19
#define MLBLCBCR20 MLB.LCBCR20
#define MLBLCBCR21 MLB.LCBCR21
#define MLBLCBCR22 MLB.LCBCR22
#define MLBLCBCR23 MLB.LCBCR23
#define MLBLCBCR24 MLB.LCBCR24
#define MLBLCBCR25 MLB.LCBCR25
#define MLBLCBCR26 MLB.LCBCR26
#define MLBLCBCR27 MLB.LCBCR27
#define MLBLCBCR28 MLB.LCBCR28
#define MLBLCBCR29 MLB.LCBCR29
#define MLBLCBCR30 MLB.LCBCR30
/* <-SEC M1.10.1 */
/* <-QAC 0857 */
/* <-QAC 0639 */
#endif
