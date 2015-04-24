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
* File Name : ceu_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef CEU_IODEFINE_H
#define CEU_IODEFINE_H
/* ->SEC M1.10.1 : Not magic number */

struct st_ceu
{                                                          /* CEU              */
/* start of struct st_ceu_n */
    volatile uint32_t  CAPSR;                                  /*  CAPSR           */
    volatile uint32_t  CAPCR;                                  /*  CAPCR           */
    volatile uint32_t  CAMCR;                                  /*  CAMCR           */
    volatile uint32_t  CMCYR;                                  /*  CMCYR           */
    volatile uint32_t  CAMOR_A;                                /*  CAMOR_A         */
    volatile uint32_t  CAPWR_A;                                /*  CAPWR_A         */
    volatile uint32_t  CAIFR;                                  /*  CAIFR           */
    volatile uint8_t   dummy305[12];                           /*                  */
    volatile uint32_t  CRCNTR;                                 /*  CRCNTR          */
    volatile uint32_t  CRCMPR;                                 /*  CRCMPR          */
    volatile uint32_t  CFLCR_A;                                /*  CFLCR_A         */
    volatile uint32_t  CFSZR_A;                                /*  CFSZR_A         */
    volatile uint32_t  CDWDR_A;                                /*  CDWDR_A         */
    volatile uint32_t  CDAYR_A;                                /*  CDAYR_A         */
    volatile uint32_t  CDACR_A;                                /*  CDACR_A         */
    volatile uint32_t  CDBYR_A;                                /*  CDBYR_A         */
    volatile uint32_t  CDBCR_A;                                /*  CDBCR_A         */
    volatile uint32_t  CBDSR_A;                                /*  CBDSR_A         */
    volatile uint8_t   dummy306[12];                           /*                  */
    volatile uint32_t  CFWCR;                                  /*  CFWCR           */
    volatile uint32_t  CLFCR_A;                                /*  CLFCR_A         */
    volatile uint32_t  CDOCR_A;                                /*  CDOCR_A         */
    volatile uint8_t   dummy307[8];                            /*                  */
    volatile uint32_t  CEIER;                                  /*  CEIER           */
    volatile uint32_t  CETCR;                                  /*  CETCR           */
    volatile uint8_t   dummy308[4];                            /*                  */
    volatile uint32_t  CSTSR;                                  /*  CSTSR           */
    volatile uint8_t   dummy309[4];                            /*                  */
    volatile uint32_t  CDSSR;                                  /*  CDSSR           */
    volatile uint8_t   dummy310[8];                            /*                  */
    volatile uint32_t  CDAYR2_A;                               /*  CDAYR2_A        */
    volatile uint32_t  CDACR2_A;                               /*  CDACR2_A        */
    volatile uint32_t  CDBYR2_A;                               /*  CDBYR2_A        */
    volatile uint32_t  CDBCR2_A;                               /*  CDBCR2_A        */
/* end of struct st_ceu_n */
    volatile uint8_t   dummy3110[3936];                        /*                  */
/* start of struct st_ceu_n */
    volatile uint8_t   dummy3111[4];                           /*                  */
    volatile uint8_t   dummy3112[4];                           /*                  */
    volatile uint8_t   dummy3113[4];                           /*                  */
    volatile uint8_t   dummy3114[4];                           /*                  */
    volatile uint32_t  CAMOR_B;                                /*  CAMOR_B         */
    volatile uint32_t  CAPWR_B;                                /*  CAPWR_B         */
    volatile uint8_t   dummy3120[4];                           /*                  */
    volatile uint8_t   dummy3121[12];                          /*                  */
    volatile uint8_t   dummy3122[4];                           /*                  */
    volatile uint8_t   dummy3123[4];                           /*                  */
    volatile uint32_t  CFLCR_B;                                /*  CFLCR_B         */
    volatile uint32_t  CFSZR_B;                                /*  CFSZR_B         */
    volatile uint32_t  CDWDR_B;                                /*  CDWDR_B         */
    volatile uint32_t  CDAYR_B;                                /*  CDAYR_B         */
    volatile uint32_t  CDACR_B;                                /*  CDACR_B         */
    volatile uint32_t  CDBYR_B;                                /*  CDBYR_B         */
    volatile uint32_t  CDBCR_B;                                /*  CDBCR_B         */
    volatile uint32_t  CBDSR_B;                                /*  CBDSR_B         */
    volatile uint8_t   dummy3130[12];                          /*                  */
    volatile uint8_t   dummy3131[4];                           /*                  */
    volatile uint32_t  CLFCR_B;                                /*  CLFCR_B         */
    volatile uint32_t  CDOCR_B;                                /*  CDOCR_B         */
    volatile uint8_t   dummy3140[8];                           /*                  */
    volatile uint8_t   dummy3141[4];                           /*                  */
    volatile uint8_t   dummy3142[4];                           /*                  */
    volatile uint8_t   dummy3143[4];                           /*                  */
    volatile uint8_t   dummy3144[4];                           /*                  */
    volatile uint8_t   dummy3145[4];                           /*                  */
    volatile uint8_t   dummy3146[4];                           /*                  */
    volatile uint8_t   dummy3147[8];                           /*                  */
    volatile uint32_t  CDAYR2_B;                               /*  CDAYR2_B        */
    volatile uint32_t  CDACR2_B;                               /*  CDACR2_B        */
    volatile uint32_t  CDBYR2_B;                               /*  CDBYR2_B        */
    volatile uint32_t  CDBCR2_B;                               /*  CDBCR2_B        */
/* end of struct st_ceu_n */
    volatile uint8_t   dummy3150[3936];                        /*                  */
/* start of struct st_ceu_n */
    volatile uint8_t   dummy3151[4];                           /*                  */
    volatile uint8_t   dummy3152[4];                           /*                  */
    volatile uint8_t   dummy3153[4];                           /*                  */
    volatile uint8_t   dummy3154[4];                           /*                  */
    volatile uint32_t  CAMOR_M;                                /*  CAMOR_M         */
    volatile uint32_t  CAPWR_M;                                /*  CAPWR_M         */
    volatile uint8_t   dummy3160[4];                           /*                  */
    volatile uint8_t   dummy3161[12];                          /*                  */
    volatile uint8_t   dummy3162[4];                           /*                  */
    volatile uint8_t   dummy3163[4];                           /*                  */
    volatile uint32_t  CFLCR_M;                                /*  CFLCR_M         */
    volatile uint32_t  CFSZR_M;                                /*  CFSZR_M         */
    volatile uint32_t  CDWDR_M;                                /*  CDWDR_M         */
    volatile uint32_t  CDAYR_M;                                /*  CDAYR_M         */
    volatile uint32_t  CDACR_M;                                /*  CDACR_M         */
    volatile uint32_t  CDBYR_M;                                /*  CDBYR_M         */
    volatile uint32_t  CDBCR_M;                                /*  CDBCR_M         */
    volatile uint32_t  CBDSR_M;                                /*  CBDSR_M         */
    volatile uint8_t   dummy3170[12];                          /*                  */
    volatile uint8_t   dummy3171[4];                           /*                  */
    volatile uint32_t  CLFCR_M;                                /*  CLFCR_M         */
    volatile uint32_t  CDOCR_M;                                /*  CDOCR_M         */
    volatile uint8_t   dummy3180[8];                           /*                  */
    volatile uint8_t   dummy3181[4];                           /*                  */
    volatile uint8_t   dummy3182[4];                           /*                  */
    volatile uint8_t   dummy3183[4];                           /*                  */
    volatile uint8_t   dummy3184[4];                           /*                  */
    volatile uint8_t   dummy3185[4];                           /*                  */
    volatile uint8_t   dummy3186[4];                           /*                  */
    volatile uint8_t   dummy3187[8];                           /*                  */
    volatile uint32_t  CDAYR2_M;                               /*  CDAYR2_M        */
    volatile uint32_t  CDACR2_M;                               /*  CDACR2_M        */
    volatile uint32_t  CDBYR2_M;                               /*  CDBYR2_M        */
    volatile uint32_t  CDBCR2_M;                               /*  CDBCR2_M        */
/* end of struct st_ceu_n */
};


struct st_ceu_n
{
    volatile uint32_t  not_common1;                            /*                  */
    volatile uint32_t  not_common2;                            /*                  */
    volatile uint32_t  not_common3;                            /*                  */
    volatile uint32_t  not_common4;                            /*                  */
    volatile uint32_t  CAMOR;                                  /*  CAMOR           */
    volatile uint32_t  CAPWR;                                  /*  CAPWR           */
    volatile uint32_t  not_common5;                            /*                  */
    volatile uint8_t   dummy322[12];                           /*                  */
    volatile uint32_t  not_common6;                            /*                  */
    volatile uint32_t  not_common7;                            /*                  */
    volatile uint32_t  CFLCR;                                  /*  CFLCR           */
    volatile uint32_t  CFSZR;                                  /*  CFSZR           */
    volatile uint32_t  CDWDR;                                  /*  CDWDR           */
    volatile uint32_t  CDAYR;                                  /*  CDAYR           */
    volatile uint32_t  CDACR;                                  /*  CDACR           */
    volatile uint32_t  CDBYR;                                  /*  CDBYR           */
    volatile uint32_t  CDBCR;                                  /*  CDBCR           */
    volatile uint32_t  CBDSR;                                  /*  CBDSR           */
    volatile uint8_t   dummy323[12];                           /*                  */
    volatile uint32_t  not_common8;                            /*                  */
    volatile uint32_t  CLFCR;                                  /*  CLFCR           */
    volatile uint32_t  CDOCR;                                  /*  CDOCR           */
    volatile uint8_t   dummy324[8];                            /*                  */
    volatile uint32_t  not_common9;                            /*                  */
    volatile uint32_t  not_common10;                           /*                  */
    volatile uint8_t   dummy325[4];                            /*                  */
    volatile uint32_t  not_common11;                           /*                  */
    volatile uint8_t   dummy326[4];                            /*                  */
    volatile uint32_t  not_common12;                           /*                  */
    volatile uint8_t   dummy327[8];                            /*                  */
    volatile uint32_t  CDAYR2;                                 /*  CDAYR2          */
    volatile uint32_t  CDACR2;                                 /*  CDACR2          */
    volatile uint32_t  CDBYR2;                                 /*  CDBYR2          */
    volatile uint32_t  CDBCR2;                                 /*  CDBCR2          */
};


#define CEU     (*(struct st_ceu     *)0xE8210000uL) /* CEU */


/* Start of channnel array defines of CEU */

/* Channnel array defines of CEUn */
/*(Sample) value = CEUn[ channel ]->CAMOR; */
#define CEUn_COUNT  3
#define CEUn_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    (volatile struct st_ceu_n*)&CEU_A, \
    (volatile struct st_ceu_n*)&CEU_B, \
    (volatile struct st_ceu_n*)&CEU_M \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define CEU_A   (*(struct st_ceu_n *)&CEU.CAPSR)                 /* CEU_A */
#define CEU_B   (*(struct st_ceu_n *)&CEU.dummy3111)             /* CEU_B */
#define CEU_M   (*(struct st_ceu_n *)&CEU.dummy3151)             /* CEU_M */

/* End of channnel array defines of CEU */


#define CEUCAPSR CEU.CAPSR
#define CEUCAPCR CEU.CAPCR
#define CEUCAMCR CEU.CAMCR
#define CEUCMCYR CEU.CMCYR
#define CEUCAMOR_A CEU.CAMOR_A
#define CEUCAPWR_A CEU.CAPWR_A
#define CEUCAIFR CEU.CAIFR
#define CEUCRCNTR CEU.CRCNTR
#define CEUCRCMPR CEU.CRCMPR
#define CEUCFLCR_A CEU.CFLCR_A
#define CEUCFSZR_A CEU.CFSZR_A
#define CEUCDWDR_A CEU.CDWDR_A
#define CEUCDAYR_A CEU.CDAYR_A
#define CEUCDACR_A CEU.CDACR_A
#define CEUCDBYR_A CEU.CDBYR_A
#define CEUCDBCR_A CEU.CDBCR_A
#define CEUCBDSR_A CEU.CBDSR_A
#define CEUCFWCR CEU.CFWCR
#define CEUCLFCR_A CEU.CLFCR_A
#define CEUCDOCR_A CEU.CDOCR_A
#define CEUCEIER CEU.CEIER
#define CEUCETCR CEU.CETCR
#define CEUCSTSR CEU.CSTSR
#define CEUCDSSR CEU.CDSSR
#define CEUCDAYR2_A CEU.CDAYR2_A
#define CEUCDACR2_A CEU.CDACR2_A
#define CEUCDBYR2_A CEU.CDBYR2_A
#define CEUCDBCR2_A CEU.CDBCR2_A
#define CEUCAMOR_B CEU.CAMOR_B
#define CEUCAPWR_B CEU.CAPWR_B
#define CEUCFLCR_B CEU.CFLCR_B
#define CEUCFSZR_B CEU.CFSZR_B
#define CEUCDWDR_B CEU.CDWDR_B
#define CEUCDAYR_B CEU.CDAYR_B
#define CEUCDACR_B CEU.CDACR_B
#define CEUCDBYR_B CEU.CDBYR_B
#define CEUCDBCR_B CEU.CDBCR_B
#define CEUCBDSR_B CEU.CBDSR_B
#define CEUCLFCR_B CEU.CLFCR_B
#define CEUCDOCR_B CEU.CDOCR_B
#define CEUCDAYR2_B CEU.CDAYR2_B
#define CEUCDACR2_B CEU.CDACR2_B
#define CEUCDBYR2_B CEU.CDBYR2_B
#define CEUCDBCR2_B CEU.CDBCR2_B
#define CEUCAMOR_M CEU.CAMOR_M
#define CEUCAPWR_M CEU.CAPWR_M
#define CEUCFLCR_M CEU.CFLCR_M
#define CEUCFSZR_M CEU.CFSZR_M
#define CEUCDWDR_M CEU.CDWDR_M
#define CEUCDAYR_M CEU.CDAYR_M
#define CEUCDACR_M CEU.CDACR_M
#define CEUCDBYR_M CEU.CDBYR_M
#define CEUCDBCR_M CEU.CDBCR_M
#define CEUCBDSR_M CEU.CBDSR_M
#define CEUCLFCR_M CEU.CLFCR_M
#define CEUCDOCR_M CEU.CDOCR_M
#define CEUCDAYR2_M CEU.CDAYR2_M
#define CEUCDACR2_M CEU.CDACR2_M
#define CEUCDBYR2_M CEU.CDBYR2_M
#define CEUCDBCR2_M CEU.CDBCR2_M
/* <-SEC M1.10.1 */
#endif
