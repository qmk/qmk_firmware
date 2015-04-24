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
* File Name : usb20_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef USB20_IODEFINE_H
#define USB20_IODEFINE_H
/* ->SEC M1.10.1 : Not magic number */

struct st_usb20
{                                                          /* USB20            */
    volatile uint16_t SYSCFG0;                                /*  SYSCFG0         */
    volatile uint16_t BUSWAIT;                                /*  BUSWAIT         */
    volatile uint16_t SYSSTS0;                                /*  SYSSTS0         */
    volatile uint8_t   dummy1[2];                              /*                  */
    volatile uint16_t DVSTCTR0;                               /*  DVSTCTR0        */
    volatile uint8_t   dummy2[2];                              /*                  */
    volatile uint16_t TESTMODE;                               /*  TESTMODE        */
    volatile uint8_t   dummy3[2];                              /*                  */
#define USB20_D0FBCFG_COUNT 2
    volatile uint16_t D0FBCFG;                                /*  D0FBCFG         */
    volatile uint16_t D1FBCFG;                                /*  D1FBCFG         */
    union iodefine_reg32_t  CFIFO;                         /*  CFIFO           */
#define USB20_D0FIFO_COUNT 2
    union iodefine_reg32_t  D0FIFO;                        /*  D0FIFO          */
    union iodefine_reg32_t  D1FIFO;                        /*  D1FIFO          */
    
    volatile uint16_t CFIFOSEL;                               /*  CFIFOSEL        */
    volatile uint16_t CFIFOCTR;                               /*  CFIFOCTR        */
    volatile uint8_t   dummy4[4];                              /*                  */
/* start of struct st_usb20_from_d0fifosel */
    volatile uint16_t D0FIFOSEL;                              /*  D0FIFOSEL       */
    volatile uint16_t D0FIFOCTR;                              /*  D0FIFOCTR       */
/* end of struct st_usb20_from_d0fifosel */
/* start of struct st_usb20_from_d0fifosel */
    volatile uint16_t D1FIFOSEL;                              /*  D1FIFOSEL       */
    volatile uint16_t D1FIFOCTR;                              /*  D1FIFOCTR       */
/* end of struct st_usb20_from_d0fifosel */
#define USB20_INTENB0_COUNT 2
    volatile uint16_t INTENB0;                                /*  INTENB0         */
    volatile uint16_t INTENB1;                                /*  INTENB1         */
    volatile uint8_t   dummy5[2];                              /*                  */
    volatile uint16_t BRDYENB;                                /*  BRDYENB         */
    volatile uint16_t NRDYENB;                                /*  NRDYENB         */
    volatile uint16_t BEMPENB;                                /*  BEMPENB         */
    volatile uint16_t SOFCFG;                                 /*  SOFCFG          */
    volatile uint8_t   dummy6[2];                              /*                  */
#define USB20_INTSTS0_COUNT 2
    volatile uint16_t INTSTS0;                                /*  INTSTS0         */
    volatile uint16_t INTSTS1;                                /*  INTSTS1         */
    volatile uint8_t   dummy7[2];                              /*                  */
    volatile uint16_t BRDYSTS;                                /*  BRDYSTS         */
    volatile uint16_t NRDYSTS;                                /*  NRDYSTS         */
    volatile uint16_t BEMPSTS;                                /*  BEMPSTS         */
    volatile uint16_t FRMNUM;                                 /*  FRMNUM          */
    volatile uint16_t UFRMNUM;                                /*  UFRMNUM         */
    volatile uint16_t USBADDR;                                /*  USBADDR         */
    volatile uint8_t   dummy8[2];                              /*                  */
    volatile uint16_t USBREQ;                                 /*  USBREQ          */
    volatile uint16_t USBVAL;                                 /*  USBVAL          */
    volatile uint16_t USBINDX;                                /*  USBINDX         */
    volatile uint16_t USBLENG;                                /*  USBLENG         */
    volatile uint16_t DCPCFG;                                 /*  DCPCFG          */
    volatile uint16_t DCPMAXP;                                /*  DCPMAXP         */
    volatile uint16_t DCPCTR;                                 /*  DCPCTR          */
    volatile uint8_t   dummy9[2];                              /*                  */
    volatile uint16_t PIPESEL;                                /*  PIPESEL         */
    volatile uint8_t   dummy10[2];                             /*                  */
    volatile uint16_t PIPECFG;                                /*  PIPECFG         */
    volatile uint16_t PIPEBUF;                                /*  PIPEBUF         */
    volatile uint16_t PIPEMAXP;                               /*  PIPEMAXP        */
    volatile uint16_t PIPEPERI;                               /*  PIPEPERI        */
#define USB20_PIPE1CTR_COUNT 0xF
    volatile uint16_t PIPE1CTR;                               /*  PIPE1CTR        */
    volatile uint16_t PIPE2CTR;                               /*  PIPE2CTR        */
    volatile uint16_t PIPE3CTR;                               /*  PIPE3CTR        */
    volatile uint16_t PIPE4CTR;                               /*  PIPE4CTR        */
    volatile uint16_t PIPE5CTR;                               /*  PIPE5CTR        */
    volatile uint16_t PIPE6CTR;                               /*  PIPE6CTR        */
    volatile uint16_t PIPE7CTR;                               /*  PIPE7CTR        */
    volatile uint16_t PIPE8CTR;                               /*  PIPE8CTR        */
    volatile uint16_t PIPE9CTR;                               /*  PIPE9CTR        */
    volatile uint16_t PIPEACTR;                               /*  PIPEACTR        */
    volatile uint16_t PIPEBCTR;                               /*  PIPEBCTR        */
    volatile uint16_t PIPECCTR;                               /*  PIPECCTR        */
    volatile uint16_t PIPEDCTR;                               /*  PIPEDCTR        */
    volatile uint16_t PIPEECTR;                               /*  PIPEECTR        */
    volatile uint16_t PIPEFCTR;                               /*  PIPEFCTR        */
    volatile uint8_t   dummy11[2];                             /*                  */
/* start of struct st_usb20_from_pipe1tre */
    volatile uint16_t PIPE1TRE;                               /*  PIPE1TRE        */
    volatile uint16_t PIPE1TRN;                               /*  PIPE1TRN        */
/* end of struct st_usb20_from_pipe1tre */
/* start of struct st_usb20_from_pipe1tre */
    volatile uint16_t PIPE2TRE;                               /*  PIPE2TRE        */
    volatile uint16_t PIPE2TRN;                               /*  PIPE2TRN        */
/* end of struct st_usb20_from_pipe1tre */
/* start of struct st_usb20_from_pipe1tre */
    volatile uint16_t PIPE3TRE;                               /*  PIPE3TRE        */
    volatile uint16_t PIPE3TRN;                               /*  PIPE3TRN        */
/* end of struct st_usb20_from_pipe1tre */
/* start of struct st_usb20_from_pipe1tre */
    volatile uint16_t PIPE4TRE;                               /*  PIPE4TRE        */
    volatile uint16_t PIPE4TRN;                               /*  PIPE4TRN        */
/* end of struct st_usb20_from_pipe1tre */
/* start of struct st_usb20_from_pipe1tre */
    volatile uint16_t PIPE5TRE;                               /*  PIPE5TRE        */
    volatile uint16_t PIPE5TRN;                               /*  PIPE5TRN        */
/* end of struct st_usb20_from_pipe1tre */
    volatile uint16_t PIPEBTRE;                               /*  PIPEBTRE        */
    volatile uint16_t PIPEBTRN;                               /*  PIPEBTRN        */
    volatile uint16_t PIPECTRE;                               /*  PIPECTRE        */
    volatile uint16_t PIPECTRN;                               /*  PIPECTRN        */
    volatile uint16_t PIPEDTRE;                               /*  PIPEDTRE        */
    volatile uint16_t PIPEDTRN;                               /*  PIPEDTRN        */
    volatile uint16_t PIPEETRE;                               /*  PIPEETRE        */
    volatile uint16_t PIPEETRN;                               /*  PIPEETRN        */
    volatile uint16_t PIPEFTRE;                               /*  PIPEFTRE        */
    volatile uint16_t PIPEFTRN;                               /*  PIPEFTRN        */
    volatile uint16_t PIPE9TRE;                               /*  PIPE9TRE        */
    volatile uint16_t PIPE9TRN;                               /*  PIPE9TRN        */
    volatile uint16_t PIPEATRE;                               /*  PIPEATRE        */
    volatile uint16_t PIPEATRN;                               /*  PIPEATRN        */
    volatile uint8_t   dummy12[16];                            /*                  */
#define USB20_DEVADD0_COUNT 0xB
    volatile uint16_t DEVADD0;                                /*  DEVADD0         */
    volatile uint16_t DEVADD1;                                /*  DEVADD1         */
    volatile uint16_t DEVADD2;                                /*  DEVADD2         */
    volatile uint16_t DEVADD3;                                /*  DEVADD3         */
    volatile uint16_t DEVADD4;                                /*  DEVADD4         */
    volatile uint16_t DEVADD5;                                /*  DEVADD5         */
    volatile uint16_t DEVADD6;                                /*  DEVADD6         */
    volatile uint16_t DEVADD7;                                /*  DEVADD7         */
    volatile uint16_t DEVADD8;                                /*  DEVADD8         */
    volatile uint16_t DEVADD9;                                /*  DEVADD9         */
    volatile uint16_t DEVADDA;                                /*  DEVADDA         */
    volatile uint8_t   dummy13[28];                            /*                  */
    volatile uint16_t SUSPMODE;                               /*  SUSPMODE        */
    volatile uint8_t   dummy14[92];                            /*                  */
/* start of struct st_usb20_from_dmfifob0 */
    volatile uint32_t  D0FIFOB0;                               /*  D0FIFOB0        */
    volatile uint32_t  D0FIFOB1;                               /*  D0FIFOB1        */
    volatile uint32_t  D0FIFOB2;                               /*  D0FIFOB2        */
    volatile uint32_t  D0FIFOB3;                               /*  D0FIFOB3        */
    volatile uint32_t  D0FIFOB4;                               /*  D0FIFOB4        */
    volatile uint32_t  D0FIFOB5;                               /*  D0FIFOB5        */
    volatile uint32_t  D0FIFOB6;                               /*  D0FIFOB6        */
    volatile uint32_t  D0FIFOB7;                               /*  D0FIFOB7        */
/* end of struct st_usb20_from_dmfifob0 */
/* start of struct st_usb20_from_dmfifob0 */
    volatile uint32_t  D1FIFOB0;                               /*  D1FIFOB0        */
    volatile uint32_t  D1FIFOB1;                               /*  D1FIFOB1        */
    volatile uint32_t  D1FIFOB2;                               /*  D1FIFOB2        */
    volatile uint32_t  D1FIFOB3;                               /*  D1FIFOB3        */
    volatile uint32_t  D1FIFOB4;                               /*  D1FIFOB4        */
    volatile uint32_t  D1FIFOB5;                               /*  D1FIFOB5        */
    volatile uint32_t  D1FIFOB6;                               /*  D1FIFOB6        */
    volatile uint32_t  D1FIFOB7;                               /*  D1FIFOB7        */
/* end of struct st_usb20_from_dmfifob0 */
};


struct st_usb20_from_d0fifosel
{
    volatile uint16_t D0FIFOSEL;                              /*  D0FIFOSEL       */
    volatile uint16_t D0FIFOCTR;                              /*  D0FIFOCTR       */
};


struct st_usb20_from_pipe1tre
{
    volatile uint16_t PIPE1TRE;                               /*  PIPE1TRE        */
    volatile uint16_t PIPE1TRN;                               /*  PIPE1TRN        */
};


struct st_usb20_from_dmfifob0
{
#define USB20_D0FIFOB0_COUNT 0x8
    volatile uint32_t  D0FIFOB0;                               /*  D0FIFOB0        */
    volatile uint32_t  D0FIFOB1;                               /*  D0FIFOB1        */
    volatile uint32_t  D0FIFOB2;                               /*  D0FIFOB2        */
    volatile uint32_t  D0FIFOB3;                               /*  D0FIFOB3        */
    volatile uint32_t  D0FIFOB4;                               /*  D0FIFOB4        */
    volatile uint32_t  D0FIFOB5;                               /*  D0FIFOB5        */
    volatile uint32_t  D0FIFOB6;                               /*  D0FIFOB6        */
    volatile uint32_t  D0FIFOB7;                               /*  D0FIFOB7        */
};


#define USB200  (*(struct st_usb20   *)0xE8010000uL) /* USB200 */
#define USB201  (*(struct st_usb20   *)0xE8207000uL) /* USB201 */


/* Start of channnel array defines of USB20 */

/* Channnel array defines of USB20 */
/*(Sample) value = USB20[ channel ]->SYSCFG0; */
#define USB20_COUNT  2
#define USB20_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &USB200, &USB201 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */



/* Channnel array defines of USB20_FROM_D0FIFOB0 */
/*(Sample) value = USB20_FROM_D0FIFOB0[ channel ][ index ]->D0FIFOB0; */
#define USB20_FROM_D0FIFOB0_COUNT  2
#define USB20_FROM_D0FIFOB0_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
{ \
    &USB200_FROM_D0FIFOB0, &USB200_FROM_D1FIFOB0 },{ \
    &USB201_FROM_D0FIFOB0, &USB201_FROM_D1FIFOB0 \
} \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define USB200_FROM_D0FIFOB0 (*(struct st_usb20_from_dmfifob0 *)&USB200.D0FIFOB0) /* USB200_FROM_D0FIFOB0 */
#define USB200_FROM_D1FIFOB0 (*(struct st_usb20_from_dmfifob0 *)&USB200.D1FIFOB0) /* USB200_FROM_D1FIFOB0 */
#define USB201_FROM_D0FIFOB0 (*(struct st_usb20_from_dmfifob0 *)&USB201.D0FIFOB0) /* USB201_FROM_D0FIFOB0 */
#define USB201_FROM_D1FIFOB0 (*(struct st_usb20_from_dmfifob0 *)&USB201.D1FIFOB0) /* USB201_FROM_D1FIFOB0 */




/* Channnel array defines of USB20_FROM_PIPE1ATRE */
/*(Sample) value = USB20_FROM_PIPE1ATRE[ channel ][ index ]->PIPE1TRE; */
#define USB20_FROM_PIPE1ATRE_COUNT  5
#define USB20_FROM_PIPE1ATRE_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
{ \
    &USB200_FROM_PIPE1TRE, &USB200_FROM_PIPE2TRE, &USB200_FROM_PIPE3TRE, &USB200_FROM_PIPE4TRE, &USB200_FROM_PIPE5TRE },{ \
    &USB201_FROM_PIPE1TRE, &USB201_FROM_PIPE2TRE, &USB201_FROM_PIPE3TRE, &USB201_FROM_PIPE4TRE, &USB201_FROM_PIPE5TRE \
} \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define USB200_FROM_PIPE1TRE (*(struct st_usb20_from_pipe1tre *)&USB200.PIPE1TRE) /* USB200_FROM_PIPE1TRE */
#define USB200_FROM_PIPE2TRE (*(struct st_usb20_from_pipe1tre *)&USB200.PIPE2TRE) /* USB200_FROM_PIPE2TRE */
#define USB200_FROM_PIPE3TRE (*(struct st_usb20_from_pipe1tre *)&USB200.PIPE3TRE) /* USB200_FROM_PIPE3TRE */
#define USB200_FROM_PIPE4TRE (*(struct st_usb20_from_pipe1tre *)&USB200.PIPE4TRE) /* USB200_FROM_PIPE4TRE */
#define USB200_FROM_PIPE5TRE (*(struct st_usb20_from_pipe1tre *)&USB200.PIPE5TRE) /* USB200_FROM_PIPE5TRE */
#define USB201_FROM_PIPE1TRE (*(struct st_usb20_from_pipe1tre *)&USB201.PIPE1TRE) /* USB201_FROM_PIPE1TRE */
#define USB201_FROM_PIPE2TRE (*(struct st_usb20_from_pipe1tre *)&USB201.PIPE2TRE) /* USB201_FROM_PIPE2TRE */
#define USB201_FROM_PIPE3TRE (*(struct st_usb20_from_pipe1tre *)&USB201.PIPE3TRE) /* USB201_FROM_PIPE3TRE */
#define USB201_FROM_PIPE4TRE (*(struct st_usb20_from_pipe1tre *)&USB201.PIPE4TRE) /* USB201_FROM_PIPE4TRE */
#define USB201_FROM_PIPE5TRE (*(struct st_usb20_from_pipe1tre *)&USB201.PIPE5TRE) /* USB201_FROM_PIPE5TRE */




/* Channnel array defines of USB20_FROM_D0FIFOSEL */
/*(Sample) value = USB20_FROM_D0FIFOSEL[ channel ][ index ]->D0FIFOSEL; */
#define USB20_FROM_D0FIFOSEL_COUNT  2
#define USB20_FROM_D0FIFOSEL_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
{ \
    &USB200_FROM_D0FIFOSEL, &USB200_FROM_D1FIFOSEL },{ \
    &USB201_FROM_D0FIFOSEL, &USB201_FROM_D1FIFOSEL \
} \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define USB200_FROM_D0FIFOSEL (*(struct st_usb20_from_d0fifosel *)&USB200.D0FIFOSEL) /* USB200_FROM_D0FIFOSEL */
#define USB200_FROM_D1FIFOSEL (*(struct st_usb20_from_d0fifosel *)&USB200.D1FIFOSEL) /* USB200_FROM_D1FIFOSEL */
#define USB201_FROM_D0FIFOSEL (*(struct st_usb20_from_d0fifosel *)&USB201.D0FIFOSEL) /* USB201_FROM_D0FIFOSEL */
#define USB201_FROM_D1FIFOSEL (*(struct st_usb20_from_d0fifosel *)&USB201.D1FIFOSEL) /* USB201_FROM_D1FIFOSEL */


/* End of channnel array defines of USB20 */


#define SYSCFG0_0 USB200.SYSCFG0
#define BUSWAIT_0 USB200.BUSWAIT
#define SYSSTS0_0 USB200.SYSSTS0
#define DVSTCTR0_0 USB200.DVSTCTR0
#define TESTMODE_0 USB200.TESTMODE
#define D0FBCFG_0 USB200.D0FBCFG
#define D1FBCFG_0 USB200.D1FBCFG
#define CFIFO_0   USB200.CFIFO.UINT32
#define CFIFO_0L  USB200.CFIFO.UINT16[L]
#define CFIFO_0H  USB200.CFIFO.UINT16[H]
#define CFIFO_0LL USB200.CFIFO.UINT8[LL]
#define CFIFO_0LH USB200.CFIFO.UINT8[LH]
#define CFIFO_0HL USB200.CFIFO.UINT8[HL]
#define CFIFO_0HH USB200.CFIFO.UINT8[HH]
#define D0FIFO_0   USB200.D0FIFO.UINT32
#define D0FIFO_0L  USB200.D0FIFO.UINT16[L]
#define D0FIFO_0H  USB200.D0FIFO.UINT16[H]
#define D0FIFO_0LL USB200.D0FIFO.UINT8[LL]
#define D0FIFO_0LH USB200.D0FIFO.UINT8[LH]
#define D0FIFO_0HL USB200.D0FIFO.UINT8[HL]
#define D0FIFO_0HH USB200.D0FIFO.UINT8[HH]
#define D1FIFO_0   USB200.D1FIFO.UINT32
#define D1FIFO_0L  USB200.D1FIFO.UINT16[L]
#define D1FIFO_0H  USB200.D1FIFO.UINT16[H]
#define D1FIFO_0LL USB200.D1FIFO.UINT8[LL]
#define D1FIFO_0LH USB200.D1FIFO.UINT8[LH]
#define D1FIFO_0HL USB200.D1FIFO.UINT8[HL]
#define D1FIFO_0HH USB200.D1FIFO.UINT8[HH]
#define CFIFOSEL_0 USB200.CFIFOSEL
#define CFIFOCTR_0 USB200.CFIFOCTR
#define D0FIFOSEL_0 USB200.D0FIFOSEL
#define D0FIFOCTR_0 USB200.D0FIFOCTR
#define D1FIFOSEL_0 USB200.D1FIFOSEL
#define D1FIFOCTR_0 USB200.D1FIFOCTR
#define INTENB0_0 USB200.INTENB0
#define INTENB1_0 USB200.INTENB1
#define BRDYENB_0 USB200.BRDYENB
#define NRDYENB_0 USB200.NRDYENB
#define BEMPENB_0 USB200.BEMPENB
#define SOFCFG_0 USB200.SOFCFG
#define INTSTS0_0 USB200.INTSTS0
#define INTSTS1_0 USB200.INTSTS1
#define BRDYSTS_0 USB200.BRDYSTS
#define NRDYSTS_0 USB200.NRDYSTS
#define BEMPSTS_0 USB200.BEMPSTS
#define FRMNUM_0 USB200.FRMNUM
#define UFRMNUM_0 USB200.UFRMNUM
#define USBADDR_0 USB200.USBADDR
#define USBREQ_0 USB200.USBREQ
#define USBVAL_0 USB200.USBVAL
#define USBINDX_0 USB200.USBINDX
#define USBLENG_0 USB200.USBLENG
#define DCPCFG_0 USB200.DCPCFG
#define DCPMAXP_0 USB200.DCPMAXP
#define DCPCTR_0 USB200.DCPCTR
#define PIPESEL_0 USB200.PIPESEL
#define PIPECFG_0 USB200.PIPECFG
#define PIPEBUF_0 USB200.PIPEBUF
#define PIPEMAXP_0 USB200.PIPEMAXP
#define PIPEPERI_0 USB200.PIPEPERI
#define PIPE1CTR_0 USB200.PIPE1CTR
#define PIPE2CTR_0 USB200.PIPE2CTR
#define PIPE3CTR_0 USB200.PIPE3CTR
#define PIPE4CTR_0 USB200.PIPE4CTR
#define PIPE5CTR_0 USB200.PIPE5CTR
#define PIPE6CTR_0 USB200.PIPE6CTR
#define PIPE7CTR_0 USB200.PIPE7CTR
#define PIPE8CTR_0 USB200.PIPE8CTR
#define PIPE9CTR_0 USB200.PIPE9CTR
#define PIPEACTR_0 USB200.PIPEACTR
#define PIPEBCTR_0 USB200.PIPEBCTR
#define PIPECCTR_0 USB200.PIPECCTR
#define PIPEDCTR_0 USB200.PIPEDCTR
#define PIPEECTR_0 USB200.PIPEECTR
#define PIPEFCTR_0 USB200.PIPEFCTR
#define PIPE1TRE_0 USB200.PIPE1TRE
#define PIPE1TRN_0 USB200.PIPE1TRN
#define PIPE2TRE_0 USB200.PIPE2TRE
#define PIPE2TRN_0 USB200.PIPE2TRN
#define PIPE3TRE_0 USB200.PIPE3TRE
#define PIPE3TRN_0 USB200.PIPE3TRN
#define PIPE4TRE_0 USB200.PIPE4TRE
#define PIPE4TRN_0 USB200.PIPE4TRN
#define PIPE5TRE_0 USB200.PIPE5TRE
#define PIPE5TRN_0 USB200.PIPE5TRN
#define PIPEBTRE_0 USB200.PIPEBTRE
#define PIPEBTRN_0 USB200.PIPEBTRN
#define PIPECTRE_0 USB200.PIPECTRE
#define PIPECTRN_0 USB200.PIPECTRN
#define PIPEDTRE_0 USB200.PIPEDTRE
#define PIPEDTRN_0 USB200.PIPEDTRN
#define PIPEETRE_0 USB200.PIPEETRE
#define PIPEETRN_0 USB200.PIPEETRN
#define PIPEFTRE_0 USB200.PIPEFTRE
#define PIPEFTRN_0 USB200.PIPEFTRN
#define PIPE9TRE_0 USB200.PIPE9TRE
#define PIPE9TRN_0 USB200.PIPE9TRN
#define PIPEATRE_0 USB200.PIPEATRE
#define PIPEATRN_0 USB200.PIPEATRN
#define DEVADD0_0 USB200.DEVADD0
#define DEVADD1_0 USB200.DEVADD1
#define DEVADD2_0 USB200.DEVADD2
#define DEVADD3_0 USB200.DEVADD3
#define DEVADD4_0 USB200.DEVADD4
#define DEVADD5_0 USB200.DEVADD5
#define DEVADD6_0 USB200.DEVADD6
#define DEVADD7_0 USB200.DEVADD7
#define DEVADD8_0 USB200.DEVADD8
#define DEVADD9_0 USB200.DEVADD9
#define DEVADDA_0 USB200.DEVADDA
#define SUSPMODE_0 USB200.SUSPMODE
#define D0FIFOB0_0 USB200.D0FIFOB0
#define D0FIFOB1_0 USB200.D0FIFOB1
#define D0FIFOB2_0 USB200.D0FIFOB2
#define D0FIFOB3_0 USB200.D0FIFOB3
#define D0FIFOB4_0 USB200.D0FIFOB4
#define D0FIFOB5_0 USB200.D0FIFOB5
#define D0FIFOB6_0 USB200.D0FIFOB6
#define D0FIFOB7_0 USB200.D0FIFOB7
#define D1FIFOB0_0 USB200.D1FIFOB0
#define D1FIFOB1_0 USB200.D1FIFOB1
#define D1FIFOB2_0 USB200.D1FIFOB2
#define D1FIFOB3_0 USB200.D1FIFOB3
#define D1FIFOB4_0 USB200.D1FIFOB4
#define D1FIFOB5_0 USB200.D1FIFOB5
#define D1FIFOB6_0 USB200.D1FIFOB6
#define D1FIFOB7_0 USB200.D1FIFOB7
#define SYSCFG0_1 USB201.SYSCFG0
#define BUSWAIT_1 USB201.BUSWAIT
#define SYSSTS0_1 USB201.SYSSTS0
#define DVSTCTR0_1 USB201.DVSTCTR0
#define TESTMODE_1 USB201.TESTMODE
#define D0FBCFG_1 USB201.D0FBCFG
#define D1FBCFG_1 USB201.D1FBCFG
#define CFIFO_1   USB201.CFIFO.UINT32
#define CFIFO_1L  USB201.CFIFO.UINT16[L]
#define CFIFO_1H  USB201.CFIFO.UINT16[H]
#define CFIFO_1LL USB201.CFIFO.UINT8[LL]
#define CFIFO_1LH USB201.CFIFO.UINT8[LH]
#define CFIFO_1HL USB201.CFIFO.UINT8[HL]
#define CFIFO_1HH USB201.CFIFO.UINT8[HH]
#define D0FIFO_1   USB201.D0FIFO.UINT32
#define D0FIFO_1L  USB201.D0FIFO.UINT16[L]
#define D0FIFO_1H  USB201.D0FIFO.UINT16[H]
#define D0FIFO_1LL USB201.D0FIFO.UINT8[LL]
#define D0FIFO_1LH USB201.D0FIFO.UINT8[LH]
#define D0FIFO_1HL USB201.D0FIFO.UINT8[HL]
#define D0FIFO_1HH USB201.D0FIFO.UINT8[HH]
#define D1FIFO_1   USB201.D1FIFO.UINT32
#define D1FIFO_1L  USB201.D1FIFO.UINT16[L]
#define D1FIFO_1H  USB201.D1FIFO.UINT16[H]
#define D1FIFO_1LL USB201.D1FIFO.UINT8[LL]
#define D1FIFO_1LH USB201.D1FIFO.UINT8[LH]
#define D1FIFO_1HL USB201.D1FIFO.UINT8[HL]
#define D1FIFO_1HH USB201.D1FIFO.UINT8[HH]
#define CFIFOSEL_1 USB201.CFIFOSEL
#define CFIFOCTR_1 USB201.CFIFOCTR
#define D0FIFOSEL_1 USB201.D0FIFOSEL
#define D0FIFOCTR_1 USB201.D0FIFOCTR
#define D1FIFOSEL_1 USB201.D1FIFOSEL
#define D1FIFOCTR_1 USB201.D1FIFOCTR
#define INTENB0_1 USB201.INTENB0
#define INTENB1_1 USB201.INTENB1
#define BRDYENB_1 USB201.BRDYENB
#define NRDYENB_1 USB201.NRDYENB
#define BEMPENB_1 USB201.BEMPENB
#define SOFCFG_1 USB201.SOFCFG
#define INTSTS0_1 USB201.INTSTS0
#define INTSTS1_1 USB201.INTSTS1
#define BRDYSTS_1 USB201.BRDYSTS
#define NRDYSTS_1 USB201.NRDYSTS
#define BEMPSTS_1 USB201.BEMPSTS
#define FRMNUM_1 USB201.FRMNUM
#define UFRMNUM_1 USB201.UFRMNUM
#define USBADDR_1 USB201.USBADDR
#define USBREQ_1 USB201.USBREQ
#define USBVAL_1 USB201.USBVAL
#define USBINDX_1 USB201.USBINDX
#define USBLENG_1 USB201.USBLENG
#define DCPCFG_1 USB201.DCPCFG
#define DCPMAXP_1 USB201.DCPMAXP
#define DCPCTR_1 USB201.DCPCTR
#define PIPESEL_1 USB201.PIPESEL
#define PIPECFG_1 USB201.PIPECFG
#define PIPEBUF_1 USB201.PIPEBUF
#define PIPEMAXP_1 USB201.PIPEMAXP
#define PIPEPERI_1 USB201.PIPEPERI
#define PIPE1CTR_1 USB201.PIPE1CTR
#define PIPE2CTR_1 USB201.PIPE2CTR
#define PIPE3CTR_1 USB201.PIPE3CTR
#define PIPE4CTR_1 USB201.PIPE4CTR
#define PIPE5CTR_1 USB201.PIPE5CTR
#define PIPE6CTR_1 USB201.PIPE6CTR
#define PIPE7CTR_1 USB201.PIPE7CTR
#define PIPE8CTR_1 USB201.PIPE8CTR
#define PIPE9CTR_1 USB201.PIPE9CTR
#define PIPEACTR_1 USB201.PIPEACTR
#define PIPEBCTR_1 USB201.PIPEBCTR
#define PIPECCTR_1 USB201.PIPECCTR
#define PIPEDCTR_1 USB201.PIPEDCTR
#define PIPEECTR_1 USB201.PIPEECTR
#define PIPEFCTR_1 USB201.PIPEFCTR
#define PIPE1TRE_1 USB201.PIPE1TRE
#define PIPE1TRN_1 USB201.PIPE1TRN
#define PIPE2TRE_1 USB201.PIPE2TRE
#define PIPE2TRN_1 USB201.PIPE2TRN
#define PIPE3TRE_1 USB201.PIPE3TRE
#define PIPE3TRN_1 USB201.PIPE3TRN
#define PIPE4TRE_1 USB201.PIPE4TRE
#define PIPE4TRN_1 USB201.PIPE4TRN
#define PIPE5TRE_1 USB201.PIPE5TRE
#define PIPE5TRN_1 USB201.PIPE5TRN
#define PIPEBTRE_1 USB201.PIPEBTRE
#define PIPEBTRN_1 USB201.PIPEBTRN
#define PIPECTRE_1 USB201.PIPECTRE
#define PIPECTRN_1 USB201.PIPECTRN
#define PIPEDTRE_1 USB201.PIPEDTRE
#define PIPEDTRN_1 USB201.PIPEDTRN
#define PIPEETRE_1 USB201.PIPEETRE
#define PIPEETRN_1 USB201.PIPEETRN
#define PIPEFTRE_1 USB201.PIPEFTRE
#define PIPEFTRN_1 USB201.PIPEFTRN
#define PIPE9TRE_1 USB201.PIPE9TRE
#define PIPE9TRN_1 USB201.PIPE9TRN
#define PIPEATRE_1 USB201.PIPEATRE
#define PIPEATRN_1 USB201.PIPEATRN
#define DEVADD0_1 USB201.DEVADD0
#define DEVADD1_1 USB201.DEVADD1
#define DEVADD2_1 USB201.DEVADD2
#define DEVADD3_1 USB201.DEVADD3
#define DEVADD4_1 USB201.DEVADD4
#define DEVADD5_1 USB201.DEVADD5
#define DEVADD6_1 USB201.DEVADD6
#define DEVADD7_1 USB201.DEVADD7
#define DEVADD8_1 USB201.DEVADD8
#define DEVADD9_1 USB201.DEVADD9
#define DEVADDA_1 USB201.DEVADDA
#define SUSPMODE_1 USB201.SUSPMODE
#define D0FIFOB0_1 USB201.D0FIFOB0
#define D0FIFOB1_1 USB201.D0FIFOB1
#define D0FIFOB2_1 USB201.D0FIFOB2
#define D0FIFOB3_1 USB201.D0FIFOB3
#define D0FIFOB4_1 USB201.D0FIFOB4
#define D0FIFOB5_1 USB201.D0FIFOB5
#define D0FIFOB6_1 USB201.D0FIFOB6
#define D0FIFOB7_1 USB201.D0FIFOB7
#define D1FIFOB0_1 USB201.D1FIFOB0
#define D1FIFOB1_1 USB201.D1FIFOB1
#define D1FIFOB2_1 USB201.D1FIFOB2
#define D1FIFOB3_1 USB201.D1FIFOB3
#define D1FIFOB4_1 USB201.D1FIFOB4
#define D1FIFOB5_1 USB201.D1FIFOB5
#define D1FIFOB6_1 USB201.D1FIFOB6
#define D1FIFOB7_1 USB201.D1FIFOB7
/* <-SEC M1.10.1 */
#endif
