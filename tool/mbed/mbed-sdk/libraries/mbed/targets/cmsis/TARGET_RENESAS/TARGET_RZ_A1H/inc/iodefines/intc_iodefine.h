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
* File Name : intc_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef INTC_IODEFINE_H
#define INTC_IODEFINE_H
/* ->QAC 0639 : Over 127 members (C90) */
/* ->SEC M1.10.1 : Not magic number */

struct st_intc
{                                                          /* INTC             */
    volatile uint32_t  ICDDCR;                                 /*  ICDDCR          */
    volatile uint32_t  ICDICTR;                                /*  ICDICTR         */
    volatile uint32_t  ICDIIDR;                                /*  ICDIIDR         */
    volatile uint8_t   dummy193[116];                          /*                  */
#define INTC_ICDISR0_COUNT 19
    volatile uint32_t  ICDISR0;                                /*  ICDISR0         */
    volatile uint32_t  ICDISR1;                                /*  ICDISR1         */
    volatile uint32_t  ICDISR2;                                /*  ICDISR2         */
    volatile uint32_t  ICDISR3;                                /*  ICDISR3         */
    volatile uint32_t  ICDISR4;                                /*  ICDISR4         */
    volatile uint32_t  ICDISR5;                                /*  ICDISR5         */
    volatile uint32_t  ICDISR6;                                /*  ICDISR6         */
    volatile uint32_t  ICDISR7;                                /*  ICDISR7         */
    volatile uint32_t  ICDISR8;                                /*  ICDISR8         */
    volatile uint32_t  ICDISR9;                                /*  ICDISR9         */
    volatile uint32_t  ICDISR10;                               /*  ICDISR10        */
    volatile uint32_t  ICDISR11;                               /*  ICDISR11        */
    volatile uint32_t  ICDISR12;                               /*  ICDISR12        */
    volatile uint32_t  ICDISR13;                               /*  ICDISR13        */
    volatile uint32_t  ICDISR14;                               /*  ICDISR14        */
    volatile uint32_t  ICDISR15;                               /*  ICDISR15        */
    volatile uint32_t  ICDISR16;                               /*  ICDISR16        */
    volatile uint32_t  ICDISR17;                               /*  ICDISR17        */
    volatile uint32_t  ICDISR18;                               /*  ICDISR18        */
    volatile uint8_t   dummy194[52];                           /*                  */
#define INTC_ICDISER0_COUNT 19
    volatile uint32_t  ICDISER0;                               /*  ICDISER0        */
    volatile uint32_t  ICDISER1;                               /*  ICDISER1        */
    volatile uint32_t  ICDISER2;                               /*  ICDISER2        */
    volatile uint32_t  ICDISER3;                               /*  ICDISER3        */
    volatile uint32_t  ICDISER4;                               /*  ICDISER4        */
    volatile uint32_t  ICDISER5;                               /*  ICDISER5        */
    volatile uint32_t  ICDISER6;                               /*  ICDISER6        */
    volatile uint32_t  ICDISER7;                               /*  ICDISER7        */
    volatile uint32_t  ICDISER8;                               /*  ICDISER8        */
    volatile uint32_t  ICDISER9;                               /*  ICDISER9        */
    volatile uint32_t  ICDISER10;                              /*  ICDISER10       */
    volatile uint32_t  ICDISER11;                              /*  ICDISER11       */
    volatile uint32_t  ICDISER12;                              /*  ICDISER12       */
    volatile uint32_t  ICDISER13;                              /*  ICDISER13       */
    volatile uint32_t  ICDISER14;                              /*  ICDISER14       */
    volatile uint32_t  ICDISER15;                              /*  ICDISER15       */
    volatile uint32_t  ICDISER16;                              /*  ICDISER16       */
    volatile uint32_t  ICDISER17;                              /*  ICDISER17       */
    volatile uint32_t  ICDISER18;                              /*  ICDISER18       */
    volatile uint8_t   dummy195[52];                           /*                  */
#define INTC_ICDICER0_COUNT 19
    volatile uint32_t  ICDICER0;                               /*  ICDICER0        */
    volatile uint32_t  ICDICER1;                               /*  ICDICER1        */
    volatile uint32_t  ICDICER2;                               /*  ICDICER2        */
    volatile uint32_t  ICDICER3;                               /*  ICDICER3        */
    volatile uint32_t  ICDICER4;                               /*  ICDICER4        */
    volatile uint32_t  ICDICER5;                               /*  ICDICER5        */
    volatile uint32_t  ICDICER6;                               /*  ICDICER6        */
    volatile uint32_t  ICDICER7;                               /*  ICDICER7        */
    volatile uint32_t  ICDICER8;                               /*  ICDICER8        */
    volatile uint32_t  ICDICER9;                               /*  ICDICER9        */
    volatile uint32_t  ICDICER10;                              /*  ICDICER10       */
    volatile uint32_t  ICDICER11;                              /*  ICDICER11       */
    volatile uint32_t  ICDICER12;                              /*  ICDICER12       */
    volatile uint32_t  ICDICER13;                              /*  ICDICER13       */
    volatile uint32_t  ICDICER14;                              /*  ICDICER14       */
    volatile uint32_t  ICDICER15;                              /*  ICDICER15       */
    volatile uint32_t  ICDICER16;                              /*  ICDICER16       */
    volatile uint32_t  ICDICER17;                              /*  ICDICER17       */
    volatile uint32_t  ICDICER18;                              /*  ICDICER18       */
    volatile uint8_t   dummy196[52];                           /*                  */
#define INTC_ICDISPR0_COUNT 19
    volatile uint32_t  ICDISPR0;                               /*  ICDISPR0        */
    volatile uint32_t  ICDISPR1;                               /*  ICDISPR1        */
    volatile uint32_t  ICDISPR2;                               /*  ICDISPR2        */
    volatile uint32_t  ICDISPR3;                               /*  ICDISPR3        */
    volatile uint32_t  ICDISPR4;                               /*  ICDISPR4        */
    volatile uint32_t  ICDISPR5;                               /*  ICDISPR5        */
    volatile uint32_t  ICDISPR6;                               /*  ICDISPR6        */
    volatile uint32_t  ICDISPR7;                               /*  ICDISPR7        */
    volatile uint32_t  ICDISPR8;                               /*  ICDISPR8        */
    volatile uint32_t  ICDISPR9;                               /*  ICDISPR9        */
    volatile uint32_t  ICDISPR10;                              /*  ICDISPR10       */
    volatile uint32_t  ICDISPR11;                              /*  ICDISPR11       */
    volatile uint32_t  ICDISPR12;                              /*  ICDISPR12       */
    volatile uint32_t  ICDISPR13;                              /*  ICDISPR13       */
    volatile uint32_t  ICDISPR14;                              /*  ICDISPR14       */
    volatile uint32_t  ICDISPR15;                              /*  ICDISPR15       */
    volatile uint32_t  ICDISPR16;                              /*  ICDISPR16       */
    volatile uint32_t  ICDISPR17;                              /*  ICDISPR17       */
    volatile uint32_t  ICDISPR18;                              /*  ICDISPR18       */
    volatile uint8_t   dummy197[52];                           /*                  */
#define INTC_ICDICPR0_COUNT 19
    volatile uint32_t  ICDICPR0;                               /*  ICDICPR0        */
    volatile uint32_t  ICDICPR1;                               /*  ICDICPR1        */
    volatile uint32_t  ICDICPR2;                               /*  ICDICPR2        */
    volatile uint32_t  ICDICPR3;                               /*  ICDICPR3        */
    volatile uint32_t  ICDICPR4;                               /*  ICDICPR4        */
    volatile uint32_t  ICDICPR5;                               /*  ICDICPR5        */
    volatile uint32_t  ICDICPR6;                               /*  ICDICPR6        */
    volatile uint32_t  ICDICPR7;                               /*  ICDICPR7        */
    volatile uint32_t  ICDICPR8;                               /*  ICDICPR8        */
    volatile uint32_t  ICDICPR9;                               /*  ICDICPR9        */
    volatile uint32_t  ICDICPR10;                              /*  ICDICPR10       */
    volatile uint32_t  ICDICPR11;                              /*  ICDICPR11       */
    volatile uint32_t  ICDICPR12;                              /*  ICDICPR12       */
    volatile uint32_t  ICDICPR13;                              /*  ICDICPR13       */
    volatile uint32_t  ICDICPR14;                              /*  ICDICPR14       */
    volatile uint32_t  ICDICPR15;                              /*  ICDICPR15       */
    volatile uint32_t  ICDICPR16;                              /*  ICDICPR16       */
    volatile uint32_t  ICDICPR17;                              /*  ICDICPR17       */
    volatile uint32_t  ICDICPR18;                              /*  ICDICPR18       */
    volatile uint8_t   dummy198[52];                           /*                  */
#define INTC_ICDABR0_COUNT 19
    volatile uint32_t  ICDABR0;                                /*  ICDABR0         */
    volatile uint32_t  ICDABR1;                                /*  ICDABR1         */
    volatile uint32_t  ICDABR2;                                /*  ICDABR2         */
    volatile uint32_t  ICDABR3;                                /*  ICDABR3         */
    volatile uint32_t  ICDABR4;                                /*  ICDABR4         */
    volatile uint32_t  ICDABR5;                                /*  ICDABR5         */
    volatile uint32_t  ICDABR6;                                /*  ICDABR6         */
    volatile uint32_t  ICDABR7;                                /*  ICDABR7         */
    volatile uint32_t  ICDABR8;                                /*  ICDABR8         */
    volatile uint32_t  ICDABR9;                                /*  ICDABR9         */
    volatile uint32_t  ICDABR10;                               /*  ICDABR10        */
    volatile uint32_t  ICDABR11;                               /*  ICDABR11        */
    volatile uint32_t  ICDABR12;                               /*  ICDABR12        */
    volatile uint32_t  ICDABR13;                               /*  ICDABR13        */
    volatile uint32_t  ICDABR14;                               /*  ICDABR14        */
    volatile uint32_t  ICDABR15;                               /*  ICDABR15        */
    volatile uint32_t  ICDABR16;                               /*  ICDABR16        */
    volatile uint32_t  ICDABR17;                               /*  ICDABR17        */
    volatile uint32_t  ICDABR18;                               /*  ICDABR18        */
    volatile uint8_t   dummy199[180];                          /*                  */
#define INTC_ICDIPR0_COUNT 147
    volatile uint32_t  ICDIPR0;                                /*  ICDIPR0         */
    volatile uint32_t  ICDIPR1;                                /*  ICDIPR1         */
    volatile uint32_t  ICDIPR2;                                /*  ICDIPR2         */
    volatile uint32_t  ICDIPR3;                                /*  ICDIPR3         */
    volatile uint32_t  ICDIPR4;                                /*  ICDIPR4         */
    volatile uint32_t  ICDIPR5;                                /*  ICDIPR5         */
    volatile uint32_t  ICDIPR6;                                /*  ICDIPR6         */
    volatile uint32_t  ICDIPR7;                                /*  ICDIPR7         */
    volatile uint32_t  ICDIPR8;                                /*  ICDIPR8         */
    volatile uint32_t  ICDIPR9;                                /*  ICDIPR9         */
    volatile uint32_t  ICDIPR10;                               /*  ICDIPR10        */
    volatile uint32_t  ICDIPR11;                               /*  ICDIPR11        */
    volatile uint32_t  ICDIPR12;                               /*  ICDIPR12        */
    volatile uint32_t  ICDIPR13;                               /*  ICDIPR13        */
    volatile uint32_t  ICDIPR14;                               /*  ICDIPR14        */
    volatile uint32_t  ICDIPR15;                               /*  ICDIPR15        */
    volatile uint32_t  ICDIPR16;                               /*  ICDIPR16        */
    volatile uint32_t  ICDIPR17;                               /*  ICDIPR17        */
    volatile uint32_t  ICDIPR18;                               /*  ICDIPR18        */
    volatile uint32_t  ICDIPR19;                               /*  ICDIPR19        */
    volatile uint32_t  ICDIPR20;                               /*  ICDIPR20        */
    volatile uint32_t  ICDIPR21;                               /*  ICDIPR21        */
    volatile uint32_t  ICDIPR22;                               /*  ICDIPR22        */
    volatile uint32_t  ICDIPR23;                               /*  ICDIPR23        */
    volatile uint32_t  ICDIPR24;                               /*  ICDIPR24        */
    volatile uint32_t  ICDIPR25;                               /*  ICDIPR25        */
    volatile uint32_t  ICDIPR26;                               /*  ICDIPR26        */
    volatile uint32_t  ICDIPR27;                               /*  ICDIPR27        */
    volatile uint32_t  ICDIPR28;                               /*  ICDIPR28        */
    volatile uint32_t  ICDIPR29;                               /*  ICDIPR29        */
    volatile uint32_t  ICDIPR30;                               /*  ICDIPR30        */
    volatile uint32_t  ICDIPR31;                               /*  ICDIPR31        */
    volatile uint32_t  ICDIPR32;                               /*  ICDIPR32        */
    volatile uint32_t  ICDIPR33;                               /*  ICDIPR33        */
    volatile uint32_t  ICDIPR34;                               /*  ICDIPR34        */
    volatile uint32_t  ICDIPR35;                               /*  ICDIPR35        */
    volatile uint32_t  ICDIPR36;                               /*  ICDIPR36        */
    volatile uint32_t  ICDIPR37;                               /*  ICDIPR37        */
    volatile uint32_t  ICDIPR38;                               /*  ICDIPR38        */
    volatile uint32_t  ICDIPR39;                               /*  ICDIPR39        */
    volatile uint32_t  ICDIPR40;                               /*  ICDIPR40        */
    volatile uint32_t  ICDIPR41;                               /*  ICDIPR41        */
    volatile uint32_t  ICDIPR42;                               /*  ICDIPR42        */
    volatile uint32_t  ICDIPR43;                               /*  ICDIPR43        */
    volatile uint32_t  ICDIPR44;                               /*  ICDIPR44        */
    volatile uint32_t  ICDIPR45;                               /*  ICDIPR45        */
    volatile uint32_t  ICDIPR46;                               /*  ICDIPR46        */
    volatile uint32_t  ICDIPR47;                               /*  ICDIPR47        */
    volatile uint32_t  ICDIPR48;                               /*  ICDIPR48        */
    volatile uint32_t  ICDIPR49;                               /*  ICDIPR49        */
    volatile uint32_t  ICDIPR50;                               /*  ICDIPR50        */
    volatile uint32_t  ICDIPR51;                               /*  ICDIPR51        */
    volatile uint32_t  ICDIPR52;                               /*  ICDIPR52        */
    volatile uint32_t  ICDIPR53;                               /*  ICDIPR53        */
    volatile uint32_t  ICDIPR54;                               /*  ICDIPR54        */
    volatile uint32_t  ICDIPR55;                               /*  ICDIPR55        */
    volatile uint32_t  ICDIPR56;                               /*  ICDIPR56        */
    volatile uint32_t  ICDIPR57;                               /*  ICDIPR57        */
    volatile uint32_t  ICDIPR58;                               /*  ICDIPR58        */
    volatile uint32_t  ICDIPR59;                               /*  ICDIPR59        */
    volatile uint32_t  ICDIPR60;                               /*  ICDIPR60        */
    volatile uint32_t  ICDIPR61;                               /*  ICDIPR61        */
    volatile uint32_t  ICDIPR62;                               /*  ICDIPR62        */
    volatile uint32_t  ICDIPR63;                               /*  ICDIPR63        */
    volatile uint32_t  ICDIPR64;                               /*  ICDIPR64        */
    volatile uint32_t  ICDIPR65;                               /*  ICDIPR65        */
    volatile uint32_t  ICDIPR66;                               /*  ICDIPR66        */
    volatile uint32_t  ICDIPR67;                               /*  ICDIPR67        */
    volatile uint32_t  ICDIPR68;                               /*  ICDIPR68        */
    volatile uint32_t  ICDIPR69;                               /*  ICDIPR69        */
    volatile uint32_t  ICDIPR70;                               /*  ICDIPR70        */
    volatile uint32_t  ICDIPR71;                               /*  ICDIPR71        */
    volatile uint32_t  ICDIPR72;                               /*  ICDIPR72        */
    volatile uint32_t  ICDIPR73;                               /*  ICDIPR73        */
    volatile uint32_t  ICDIPR74;                               /*  ICDIPR74        */
    volatile uint32_t  ICDIPR75;                               /*  ICDIPR75        */
    volatile uint32_t  ICDIPR76;                               /*  ICDIPR76        */
    volatile uint32_t  ICDIPR77;                               /*  ICDIPR77        */
    volatile uint32_t  ICDIPR78;                               /*  ICDIPR78        */
    volatile uint32_t  ICDIPR79;                               /*  ICDIPR79        */
    volatile uint32_t  ICDIPR80;                               /*  ICDIPR80        */
    volatile uint32_t  ICDIPR81;                               /*  ICDIPR81        */
    volatile uint32_t  ICDIPR82;                               /*  ICDIPR82        */
    volatile uint32_t  ICDIPR83;                               /*  ICDIPR83        */
    volatile uint32_t  ICDIPR84;                               /*  ICDIPR84        */
    volatile uint32_t  ICDIPR85;                               /*  ICDIPR85        */
    volatile uint32_t  ICDIPR86;                               /*  ICDIPR86        */
    volatile uint32_t  ICDIPR87;                               /*  ICDIPR87        */
    volatile uint32_t  ICDIPR88;                               /*  ICDIPR88        */
    volatile uint32_t  ICDIPR89;                               /*  ICDIPR89        */
    volatile uint32_t  ICDIPR90;                               /*  ICDIPR90        */
    volatile uint32_t  ICDIPR91;                               /*  ICDIPR91        */
    volatile uint32_t  ICDIPR92;                               /*  ICDIPR92        */
    volatile uint32_t  ICDIPR93;                               /*  ICDIPR93        */
    volatile uint32_t  ICDIPR94;                               /*  ICDIPR94        */
    volatile uint32_t  ICDIPR95;                               /*  ICDIPR95        */
    volatile uint32_t  ICDIPR96;                               /*  ICDIPR96        */
    volatile uint32_t  ICDIPR97;                               /*  ICDIPR97        */
    volatile uint32_t  ICDIPR98;                               /*  ICDIPR98        */
    volatile uint32_t  ICDIPR99;                               /*  ICDIPR99        */
    volatile uint32_t  ICDIPR100;                              /*  ICDIPR100       */
    volatile uint32_t  ICDIPR101;                              /*  ICDIPR101       */
    volatile uint32_t  ICDIPR102;                              /*  ICDIPR102       */
    volatile uint32_t  ICDIPR103;                              /*  ICDIPR103       */
    volatile uint32_t  ICDIPR104;                              /*  ICDIPR104       */
    volatile uint32_t  ICDIPR105;                              /*  ICDIPR105       */
    volatile uint32_t  ICDIPR106;                              /*  ICDIPR106       */
    volatile uint32_t  ICDIPR107;                              /*  ICDIPR107       */
    volatile uint32_t  ICDIPR108;                              /*  ICDIPR108       */
    volatile uint32_t  ICDIPR109;                              /*  ICDIPR109       */
    volatile uint32_t  ICDIPR110;                              /*  ICDIPR110       */
    volatile uint32_t  ICDIPR111;                              /*  ICDIPR111       */
    volatile uint32_t  ICDIPR112;                              /*  ICDIPR112       */
    volatile uint32_t  ICDIPR113;                              /*  ICDIPR113       */
    volatile uint32_t  ICDIPR114;                              /*  ICDIPR114       */
    volatile uint32_t  ICDIPR115;                              /*  ICDIPR115       */
    volatile uint32_t  ICDIPR116;                              /*  ICDIPR116       */
    volatile uint32_t  ICDIPR117;                              /*  ICDIPR117       */
    volatile uint32_t  ICDIPR118;                              /*  ICDIPR118       */
    volatile uint32_t  ICDIPR119;                              /*  ICDIPR119       */
    volatile uint32_t  ICDIPR120;                              /*  ICDIPR120       */
    volatile uint32_t  ICDIPR121;                              /*  ICDIPR121       */
    volatile uint32_t  ICDIPR122;                              /*  ICDIPR122       */
    volatile uint32_t  ICDIPR123;                              /*  ICDIPR123       */
    volatile uint32_t  ICDIPR124;                              /*  ICDIPR124       */
    volatile uint32_t  ICDIPR125;                              /*  ICDIPR125       */
    volatile uint32_t  ICDIPR126;                              /*  ICDIPR126       */
    volatile uint32_t  ICDIPR127;                              /*  ICDIPR127       */
    volatile uint32_t  ICDIPR128;                              /*  ICDIPR128       */
    volatile uint32_t  ICDIPR129;                              /*  ICDIPR129       */
    volatile uint32_t  ICDIPR130;                              /*  ICDIPR130       */
    volatile uint32_t  ICDIPR131;                              /*  ICDIPR131       */
    volatile uint32_t  ICDIPR132;                              /*  ICDIPR132       */
    volatile uint32_t  ICDIPR133;                              /*  ICDIPR133       */
    volatile uint32_t  ICDIPR134;                              /*  ICDIPR134       */
    volatile uint32_t  ICDIPR135;                              /*  ICDIPR135       */
    volatile uint32_t  ICDIPR136;                              /*  ICDIPR136       */
    volatile uint32_t  ICDIPR137;                              /*  ICDIPR137       */
    volatile uint32_t  ICDIPR138;                              /*  ICDIPR138       */
    volatile uint32_t  ICDIPR139;                              /*  ICDIPR139       */
    volatile uint32_t  ICDIPR140;                              /*  ICDIPR140       */
    volatile uint32_t  ICDIPR141;                              /*  ICDIPR141       */
    volatile uint32_t  ICDIPR142;                              /*  ICDIPR142       */
    volatile uint32_t  ICDIPR143;                              /*  ICDIPR143       */
    volatile uint32_t  ICDIPR144;                              /*  ICDIPR144       */
    volatile uint32_t  ICDIPR145;                              /*  ICDIPR145       */
    volatile uint32_t  ICDIPR146;                              /*  ICDIPR146       */
    volatile uint8_t   dummy200[436];                          /*                  */
#define INTC_ICDIPTR0_COUNT 147
    volatile uint32_t  ICDIPTR0;                               /*  ICDIPTR0        */
    volatile uint32_t  ICDIPTR1;                               /*  ICDIPTR1        */
    volatile uint32_t  ICDIPTR2;                               /*  ICDIPTR2        */
    volatile uint32_t  ICDIPTR3;                               /*  ICDIPTR3        */
    volatile uint32_t  ICDIPTR4;                               /*  ICDIPTR4        */
    volatile uint32_t  ICDIPTR5;                               /*  ICDIPTR5        */
    volatile uint32_t  ICDIPTR6;                               /*  ICDIPTR6        */
    volatile uint32_t  ICDIPTR7;                               /*  ICDIPTR7        */
    volatile uint32_t  ICDIPTR8;                               /*  ICDIPTR8        */
    volatile uint32_t  ICDIPTR9;                               /*  ICDIPTR9        */
    volatile uint32_t  ICDIPTR10;                              /*  ICDIPTR10       */
    volatile uint32_t  ICDIPTR11;                              /*  ICDIPTR11       */
    volatile uint32_t  ICDIPTR12;                              /*  ICDIPTR12       */
    volatile uint32_t  ICDIPTR13;                              /*  ICDIPTR13       */
    volatile uint32_t  ICDIPTR14;                              /*  ICDIPTR14       */
    volatile uint32_t  ICDIPTR15;                              /*  ICDIPTR15       */
    volatile uint32_t  ICDIPTR16;                              /*  ICDIPTR16       */
    volatile uint32_t  ICDIPTR17;                              /*  ICDIPTR17       */
    volatile uint32_t  ICDIPTR18;                              /*  ICDIPTR18       */
    volatile uint32_t  ICDIPTR19;                              /*  ICDIPTR19       */
    volatile uint32_t  ICDIPTR20;                              /*  ICDIPTR20       */
    volatile uint32_t  ICDIPTR21;                              /*  ICDIPTR21       */
    volatile uint32_t  ICDIPTR22;                              /*  ICDIPTR22       */
    volatile uint32_t  ICDIPTR23;                              /*  ICDIPTR23       */
    volatile uint32_t  ICDIPTR24;                              /*  ICDIPTR24       */
    volatile uint32_t  ICDIPTR25;                              /*  ICDIPTR25       */
    volatile uint32_t  ICDIPTR26;                              /*  ICDIPTR26       */
    volatile uint32_t  ICDIPTR27;                              /*  ICDIPTR27       */
    volatile uint32_t  ICDIPTR28;                              /*  ICDIPTR28       */
    volatile uint32_t  ICDIPTR29;                              /*  ICDIPTR29       */
    volatile uint32_t  ICDIPTR30;                              /*  ICDIPTR30       */
    volatile uint32_t  ICDIPTR31;                              /*  ICDIPTR31       */
    volatile uint32_t  ICDIPTR32;                              /*  ICDIPTR32       */
    volatile uint32_t  ICDIPTR33;                              /*  ICDIPTR33       */
    volatile uint32_t  ICDIPTR34;                              /*  ICDIPTR34       */
    volatile uint32_t  ICDIPTR35;                              /*  ICDIPTR35       */
    volatile uint32_t  ICDIPTR36;                              /*  ICDIPTR36       */
    volatile uint32_t  ICDIPTR37;                              /*  ICDIPTR37       */
    volatile uint32_t  ICDIPTR38;                              /*  ICDIPTR38       */
    volatile uint32_t  ICDIPTR39;                              /*  ICDIPTR39       */
    volatile uint32_t  ICDIPTR40;                              /*  ICDIPTR40       */
    volatile uint32_t  ICDIPTR41;                              /*  ICDIPTR41       */
    volatile uint32_t  ICDIPTR42;                              /*  ICDIPTR42       */
    volatile uint32_t  ICDIPTR43;                              /*  ICDIPTR43       */
    volatile uint32_t  ICDIPTR44;                              /*  ICDIPTR44       */
    volatile uint32_t  ICDIPTR45;                              /*  ICDIPTR45       */
    volatile uint32_t  ICDIPTR46;                              /*  ICDIPTR46       */
    volatile uint32_t  ICDIPTR47;                              /*  ICDIPTR47       */
    volatile uint32_t  ICDIPTR48;                              /*  ICDIPTR48       */
    volatile uint32_t  ICDIPTR49;                              /*  ICDIPTR49       */
    volatile uint32_t  ICDIPTR50;                              /*  ICDIPTR50       */
    volatile uint32_t  ICDIPTR51;                              /*  ICDIPTR51       */
    volatile uint32_t  ICDIPTR52;                              /*  ICDIPTR52       */
    volatile uint32_t  ICDIPTR53;                              /*  ICDIPTR53       */
    volatile uint32_t  ICDIPTR54;                              /*  ICDIPTR54       */
    volatile uint32_t  ICDIPTR55;                              /*  ICDIPTR55       */
    volatile uint32_t  ICDIPTR56;                              /*  ICDIPTR56       */
    volatile uint32_t  ICDIPTR57;                              /*  ICDIPTR57       */
    volatile uint32_t  ICDIPTR58;                              /*  ICDIPTR58       */
    volatile uint32_t  ICDIPTR59;                              /*  ICDIPTR59       */
    volatile uint32_t  ICDIPTR60;                              /*  ICDIPTR60       */
    volatile uint32_t  ICDIPTR61;                              /*  ICDIPTR61       */
    volatile uint32_t  ICDIPTR62;                              /*  ICDIPTR62       */
    volatile uint32_t  ICDIPTR63;                              /*  ICDIPTR63       */
    volatile uint32_t  ICDIPTR64;                              /*  ICDIPTR64       */
    volatile uint32_t  ICDIPTR65;                              /*  ICDIPTR65       */
    volatile uint32_t  ICDIPTR66;                              /*  ICDIPTR66       */
    volatile uint32_t  ICDIPTR67;                              /*  ICDIPTR67       */
    volatile uint32_t  ICDIPTR68;                              /*  ICDIPTR68       */
    volatile uint32_t  ICDIPTR69;                              /*  ICDIPTR69       */
    volatile uint32_t  ICDIPTR70;                              /*  ICDIPTR70       */
    volatile uint32_t  ICDIPTR71;                              /*  ICDIPTR71       */
    volatile uint32_t  ICDIPTR72;                              /*  ICDIPTR72       */
    volatile uint32_t  ICDIPTR73;                              /*  ICDIPTR73       */
    volatile uint32_t  ICDIPTR74;                              /*  ICDIPTR74       */
    volatile uint32_t  ICDIPTR75;                              /*  ICDIPTR75       */
    volatile uint32_t  ICDIPTR76;                              /*  ICDIPTR76       */
    volatile uint32_t  ICDIPTR77;                              /*  ICDIPTR77       */
    volatile uint32_t  ICDIPTR78;                              /*  ICDIPTR78       */
    volatile uint32_t  ICDIPTR79;                              /*  ICDIPTR79       */
    volatile uint32_t  ICDIPTR80;                              /*  ICDIPTR80       */
    volatile uint32_t  ICDIPTR81;                              /*  ICDIPTR81       */
    volatile uint32_t  ICDIPTR82;                              /*  ICDIPTR82       */
    volatile uint32_t  ICDIPTR83;                              /*  ICDIPTR83       */
    volatile uint32_t  ICDIPTR84;                              /*  ICDIPTR84       */
    volatile uint32_t  ICDIPTR85;                              /*  ICDIPTR85       */
    volatile uint32_t  ICDIPTR86;                              /*  ICDIPTR86       */
    volatile uint32_t  ICDIPTR87;                              /*  ICDIPTR87       */
    volatile uint32_t  ICDIPTR88;                              /*  ICDIPTR88       */
    volatile uint32_t  ICDIPTR89;                              /*  ICDIPTR89       */
    volatile uint32_t  ICDIPTR90;                              /*  ICDIPTR90       */
    volatile uint32_t  ICDIPTR91;                              /*  ICDIPTR91       */
    volatile uint32_t  ICDIPTR92;                              /*  ICDIPTR92       */
    volatile uint32_t  ICDIPTR93;                              /*  ICDIPTR93       */
    volatile uint32_t  ICDIPTR94;                              /*  ICDIPTR94       */
    volatile uint32_t  ICDIPTR95;                              /*  ICDIPTR95       */
    volatile uint32_t  ICDIPTR96;                              /*  ICDIPTR96       */
    volatile uint32_t  ICDIPTR97;                              /*  ICDIPTR97       */
    volatile uint32_t  ICDIPTR98;                              /*  ICDIPTR98       */
    volatile uint32_t  ICDIPTR99;                              /*  ICDIPTR99       */
    volatile uint32_t  ICDIPTR100;                             /*  ICDIPTR100      */
    volatile uint32_t  ICDIPTR101;                             /*  ICDIPTR101      */
    volatile uint32_t  ICDIPTR102;                             /*  ICDIPTR102      */
    volatile uint32_t  ICDIPTR103;                             /*  ICDIPTR103      */
    volatile uint32_t  ICDIPTR104;                             /*  ICDIPTR104      */
    volatile uint32_t  ICDIPTR105;                             /*  ICDIPTR105      */
    volatile uint32_t  ICDIPTR106;                             /*  ICDIPTR106      */
    volatile uint32_t  ICDIPTR107;                             /*  ICDIPTR107      */
    volatile uint32_t  ICDIPTR108;                             /*  ICDIPTR108      */
    volatile uint32_t  ICDIPTR109;                             /*  ICDIPTR109      */
    volatile uint32_t  ICDIPTR110;                             /*  ICDIPTR110      */
    volatile uint32_t  ICDIPTR111;                             /*  ICDIPTR111      */
    volatile uint32_t  ICDIPTR112;                             /*  ICDIPTR112      */
    volatile uint32_t  ICDIPTR113;                             /*  ICDIPTR113      */
    volatile uint32_t  ICDIPTR114;                             /*  ICDIPTR114      */
    volatile uint32_t  ICDIPTR115;                             /*  ICDIPTR115      */
    volatile uint32_t  ICDIPTR116;                             /*  ICDIPTR116      */
    volatile uint32_t  ICDIPTR117;                             /*  ICDIPTR117      */
    volatile uint32_t  ICDIPTR118;                             /*  ICDIPTR118      */
    volatile uint32_t  ICDIPTR119;                             /*  ICDIPTR119      */
    volatile uint32_t  ICDIPTR120;                             /*  ICDIPTR120      */
    volatile uint32_t  ICDIPTR121;                             /*  ICDIPTR121      */
    volatile uint32_t  ICDIPTR122;                             /*  ICDIPTR122      */
    volatile uint32_t  ICDIPTR123;                             /*  ICDIPTR123      */
    volatile uint32_t  ICDIPTR124;                             /*  ICDIPTR124      */
    volatile uint32_t  ICDIPTR125;                             /*  ICDIPTR125      */
    volatile uint32_t  ICDIPTR126;                             /*  ICDIPTR126      */
    volatile uint32_t  ICDIPTR127;                             /*  ICDIPTR127      */
    volatile uint32_t  ICDIPTR128;                             /*  ICDIPTR128      */
    volatile uint32_t  ICDIPTR129;                             /*  ICDIPTR129      */
    volatile uint32_t  ICDIPTR130;                             /*  ICDIPTR130      */
    volatile uint32_t  ICDIPTR131;                             /*  ICDIPTR131      */
    volatile uint32_t  ICDIPTR132;                             /*  ICDIPTR132      */
    volatile uint32_t  ICDIPTR133;                             /*  ICDIPTR133      */
    volatile uint32_t  ICDIPTR134;                             /*  ICDIPTR134      */
    volatile uint32_t  ICDIPTR135;                             /*  ICDIPTR135      */
    volatile uint32_t  ICDIPTR136;                             /*  ICDIPTR136      */
    volatile uint32_t  ICDIPTR137;                             /*  ICDIPTR137      */
    volatile uint32_t  ICDIPTR138;                             /*  ICDIPTR138      */
    volatile uint32_t  ICDIPTR139;                             /*  ICDIPTR139      */
    volatile uint32_t  ICDIPTR140;                             /*  ICDIPTR140      */
    volatile uint32_t  ICDIPTR141;                             /*  ICDIPTR141      */
    volatile uint32_t  ICDIPTR142;                             /*  ICDIPTR142      */
    volatile uint32_t  ICDIPTR143;                             /*  ICDIPTR143      */
    volatile uint32_t  ICDIPTR144;                             /*  ICDIPTR144      */
    volatile uint32_t  ICDIPTR145;                             /*  ICDIPTR145      */
    volatile uint32_t  ICDIPTR146;                             /*  ICDIPTR146      */
    volatile uint8_t   dummy201[436];                          /*                  */
#define INTC_ICDICFR0_COUNT 37
    volatile uint32_t  ICDICFR0;                               /*  ICDICFR0        */
    volatile uint32_t  ICDICFR1;                               /*  ICDICFR1        */
    volatile uint32_t  ICDICFR2;                               /*  ICDICFR2        */
    volatile uint32_t  ICDICFR3;                               /*  ICDICFR3        */
    volatile uint32_t  ICDICFR4;                               /*  ICDICFR4        */
    volatile uint32_t  ICDICFR5;                               /*  ICDICFR5        */
    volatile uint32_t  ICDICFR6;                               /*  ICDICFR6        */
    volatile uint32_t  ICDICFR7;                               /*  ICDICFR7        */
    volatile uint32_t  ICDICFR8;                               /*  ICDICFR8        */
    volatile uint32_t  ICDICFR9;                               /*  ICDICFR9        */
    volatile uint32_t  ICDICFR10;                              /*  ICDICFR10       */
    volatile uint32_t  ICDICFR11;                              /*  ICDICFR11       */
    volatile uint32_t  ICDICFR12;                              /*  ICDICFR12       */
    volatile uint32_t  ICDICFR13;                              /*  ICDICFR13       */
    volatile uint32_t  ICDICFR14;                              /*  ICDICFR14       */
    volatile uint32_t  ICDICFR15;                              /*  ICDICFR15       */
    volatile uint32_t  ICDICFR16;                              /*  ICDICFR16       */
    volatile uint32_t  ICDICFR17;                              /*  ICDICFR17       */
    volatile uint32_t  ICDICFR18;                              /*  ICDICFR18       */
    volatile uint32_t  ICDICFR19;                              /*  ICDICFR19       */
    volatile uint32_t  ICDICFR20;                              /*  ICDICFR20       */
    volatile uint32_t  ICDICFR21;                              /*  ICDICFR21       */
    volatile uint32_t  ICDICFR22;                              /*  ICDICFR22       */
    volatile uint32_t  ICDICFR23;                              /*  ICDICFR23       */
    volatile uint32_t  ICDICFR24;                              /*  ICDICFR24       */
    volatile uint32_t  ICDICFR25;                              /*  ICDICFR25       */
    volatile uint32_t  ICDICFR26;                              /*  ICDICFR26       */
    volatile uint32_t  ICDICFR27;                              /*  ICDICFR27       */
    volatile uint32_t  ICDICFR28;                              /*  ICDICFR28       */
    volatile uint32_t  ICDICFR29;                              /*  ICDICFR29       */
    volatile uint32_t  ICDICFR30;                              /*  ICDICFR30       */
    volatile uint32_t  ICDICFR31;                              /*  ICDICFR31       */
    volatile uint32_t  ICDICFR32;                              /*  ICDICFR32       */
    volatile uint32_t  ICDICFR33;                              /*  ICDICFR33       */
    volatile uint32_t  ICDICFR34;                              /*  ICDICFR34       */
    volatile uint32_t  ICDICFR35;                              /*  ICDICFR35       */
    volatile uint32_t  ICDICFR36;                              /*  ICDICFR36       */
    volatile uint8_t   dummy202[108];                          /*                  */
    volatile uint32_t  PPI_STATUS;                             /*  PPI_STATUS      */
#define INTC_SPI_STATUS0_COUNT 17
    volatile uint32_t  SPI_STATUS0;                            /*  SPI_STATUS0     */
    volatile uint32_t  SPI_STATUS1;                            /*  SPI_STATUS1     */
    volatile uint32_t  SPI_STATUS2;                            /*  SPI_STATUS2     */
    volatile uint32_t  SPI_STATUS3;                            /*  SPI_STATUS3     */
    volatile uint32_t  SPI_STATUS4;                            /*  SPI_STATUS4     */
    volatile uint32_t  SPI_STATUS5;                            /*  SPI_STATUS5     */
    volatile uint32_t  SPI_STATUS6;                            /*  SPI_STATUS6     */
    volatile uint32_t  SPI_STATUS7;                            /*  SPI_STATUS7     */
    volatile uint32_t  SPI_STATUS8;                            /*  SPI_STATUS8     */
    volatile uint32_t  SPI_STATUS9;                            /*  SPI_STATUS9     */
    volatile uint32_t  SPI_STATUS10;                           /*  SPI_STATUS10    */
    volatile uint32_t  SPI_STATUS11;                           /*  SPI_STATUS11    */
    volatile uint32_t  SPI_STATUS12;                           /*  SPI_STATUS12    */
    volatile uint32_t  SPI_STATUS13;                           /*  SPI_STATUS13    */
    volatile uint32_t  SPI_STATUS14;                           /*  SPI_STATUS14    */
    volatile uint32_t  SPI_STATUS15;                           /*  SPI_STATUS15    */
    volatile uint32_t  SPI_STATUS16;                           /*  SPI_STATUS16    */
    volatile uint8_t   dummy203[440];                          /*                  */
    volatile uint32_t  ICDSGIR;                                /*  ICDSGIR         */
    volatile uint8_t   dummy204[252];                          /*                  */
    volatile uint32_t  ICCICR;                                 /*  ICCICR          */
    volatile uint32_t  ICCPMR;                                 /*  ICCPMR          */
    volatile uint32_t  ICCBPR;                                 /*  ICCBPR          */
    volatile uint32_t  ICCIAR;                                 /*  ICCIAR          */
    volatile uint32_t  ICCEOIR;                                /*  ICCEOIR         */
    volatile uint32_t  ICCRPR;                                 /*  ICCRPR          */
    volatile uint32_t  ICCHPIR;                                /*  ICCHPIR         */
    volatile uint32_t  ICCABPR;                                /*  ICCABPR         */
    volatile uint8_t   dummy205[220];                          /*                  */
    volatile uint32_t  ICCIIDR;                                /*  ICCIIDR         */
    volatile uint8_t   dummy206[350148352];                    /*                  */
    volatile uint16_t ICR0;                                   /*  ICR0            */
    volatile uint16_t ICR1;                                   /*  ICR1            */
    volatile uint16_t IRQRR;                                  /*  IRQRR           */
};


#define INTC    (*(struct st_intc    *)0xE8201000uL) /* INTC */


#define INTCICDDCR INTC.ICDDCR
#define INTCICDICTR INTC.ICDICTR
#define INTCICDIIDR INTC.ICDIIDR
#define INTCICDISR0 INTC.ICDISR0
#define INTCICDISR1 INTC.ICDISR1
#define INTCICDISR2 INTC.ICDISR2
#define INTCICDISR3 INTC.ICDISR3
#define INTCICDISR4 INTC.ICDISR4
#define INTCICDISR5 INTC.ICDISR5
#define INTCICDISR6 INTC.ICDISR6
#define INTCICDISR7 INTC.ICDISR7
#define INTCICDISR8 INTC.ICDISR8
#define INTCICDISR9 INTC.ICDISR9
#define INTCICDISR10 INTC.ICDISR10
#define INTCICDISR11 INTC.ICDISR11
#define INTCICDISR12 INTC.ICDISR12
#define INTCICDISR13 INTC.ICDISR13
#define INTCICDISR14 INTC.ICDISR14
#define INTCICDISR15 INTC.ICDISR15
#define INTCICDISR16 INTC.ICDISR16
#define INTCICDISR17 INTC.ICDISR17
#define INTCICDISR18 INTC.ICDISR18
#define INTCICDISER0 INTC.ICDISER0
#define INTCICDISER1 INTC.ICDISER1
#define INTCICDISER2 INTC.ICDISER2
#define INTCICDISER3 INTC.ICDISER3
#define INTCICDISER4 INTC.ICDISER4
#define INTCICDISER5 INTC.ICDISER5
#define INTCICDISER6 INTC.ICDISER6
#define INTCICDISER7 INTC.ICDISER7
#define INTCICDISER8 INTC.ICDISER8
#define INTCICDISER9 INTC.ICDISER9
#define INTCICDISER10 INTC.ICDISER10
#define INTCICDISER11 INTC.ICDISER11
#define INTCICDISER12 INTC.ICDISER12
#define INTCICDISER13 INTC.ICDISER13
#define INTCICDISER14 INTC.ICDISER14
#define INTCICDISER15 INTC.ICDISER15
#define INTCICDISER16 INTC.ICDISER16
#define INTCICDISER17 INTC.ICDISER17
#define INTCICDISER18 INTC.ICDISER18
#define INTCICDICER0 INTC.ICDICER0
#define INTCICDICER1 INTC.ICDICER1
#define INTCICDICER2 INTC.ICDICER2
#define INTCICDICER3 INTC.ICDICER3
#define INTCICDICER4 INTC.ICDICER4
#define INTCICDICER5 INTC.ICDICER5
#define INTCICDICER6 INTC.ICDICER6
#define INTCICDICER7 INTC.ICDICER7
#define INTCICDICER8 INTC.ICDICER8
#define INTCICDICER9 INTC.ICDICER9
#define INTCICDICER10 INTC.ICDICER10
#define INTCICDICER11 INTC.ICDICER11
#define INTCICDICER12 INTC.ICDICER12
#define INTCICDICER13 INTC.ICDICER13
#define INTCICDICER14 INTC.ICDICER14
#define INTCICDICER15 INTC.ICDICER15
#define INTCICDICER16 INTC.ICDICER16
#define INTCICDICER17 INTC.ICDICER17
#define INTCICDICER18 INTC.ICDICER18
#define INTCICDISPR0 INTC.ICDISPR0
#define INTCICDISPR1 INTC.ICDISPR1
#define INTCICDISPR2 INTC.ICDISPR2
#define INTCICDISPR3 INTC.ICDISPR3
#define INTCICDISPR4 INTC.ICDISPR4
#define INTCICDISPR5 INTC.ICDISPR5
#define INTCICDISPR6 INTC.ICDISPR6
#define INTCICDISPR7 INTC.ICDISPR7
#define INTCICDISPR8 INTC.ICDISPR8
#define INTCICDISPR9 INTC.ICDISPR9
#define INTCICDISPR10 INTC.ICDISPR10
#define INTCICDISPR11 INTC.ICDISPR11
#define INTCICDISPR12 INTC.ICDISPR12
#define INTCICDISPR13 INTC.ICDISPR13
#define INTCICDISPR14 INTC.ICDISPR14
#define INTCICDISPR15 INTC.ICDISPR15
#define INTCICDISPR16 INTC.ICDISPR16
#define INTCICDISPR17 INTC.ICDISPR17
#define INTCICDISPR18 INTC.ICDISPR18
#define INTCICDICPR0 INTC.ICDICPR0
#define INTCICDICPR1 INTC.ICDICPR1
#define INTCICDICPR2 INTC.ICDICPR2
#define INTCICDICPR3 INTC.ICDICPR3
#define INTCICDICPR4 INTC.ICDICPR4
#define INTCICDICPR5 INTC.ICDICPR5
#define INTCICDICPR6 INTC.ICDICPR6
#define INTCICDICPR7 INTC.ICDICPR7
#define INTCICDICPR8 INTC.ICDICPR8
#define INTCICDICPR9 INTC.ICDICPR9
#define INTCICDICPR10 INTC.ICDICPR10
#define INTCICDICPR11 INTC.ICDICPR11
#define INTCICDICPR12 INTC.ICDICPR12
#define INTCICDICPR13 INTC.ICDICPR13
#define INTCICDICPR14 INTC.ICDICPR14
#define INTCICDICPR15 INTC.ICDICPR15
#define INTCICDICPR16 INTC.ICDICPR16
#define INTCICDICPR17 INTC.ICDICPR17
#define INTCICDICPR18 INTC.ICDICPR18
#define INTCICDABR0 INTC.ICDABR0
#define INTCICDABR1 INTC.ICDABR1
#define INTCICDABR2 INTC.ICDABR2
#define INTCICDABR3 INTC.ICDABR3
#define INTCICDABR4 INTC.ICDABR4
#define INTCICDABR5 INTC.ICDABR5
#define INTCICDABR6 INTC.ICDABR6
#define INTCICDABR7 INTC.ICDABR7
#define INTCICDABR8 INTC.ICDABR8
#define INTCICDABR9 INTC.ICDABR9
#define INTCICDABR10 INTC.ICDABR10
#define INTCICDABR11 INTC.ICDABR11
#define INTCICDABR12 INTC.ICDABR12
#define INTCICDABR13 INTC.ICDABR13
#define INTCICDABR14 INTC.ICDABR14
#define INTCICDABR15 INTC.ICDABR15
#define INTCICDABR16 INTC.ICDABR16
#define INTCICDABR17 INTC.ICDABR17
#define INTCICDABR18 INTC.ICDABR18
#define INTCICDIPR0 INTC.ICDIPR0
#define INTCICDIPR1 INTC.ICDIPR1
#define INTCICDIPR2 INTC.ICDIPR2
#define INTCICDIPR3 INTC.ICDIPR3
#define INTCICDIPR4 INTC.ICDIPR4
#define INTCICDIPR5 INTC.ICDIPR5
#define INTCICDIPR6 INTC.ICDIPR6
#define INTCICDIPR7 INTC.ICDIPR7
#define INTCICDIPR8 INTC.ICDIPR8
#define INTCICDIPR9 INTC.ICDIPR9
#define INTCICDIPR10 INTC.ICDIPR10
#define INTCICDIPR11 INTC.ICDIPR11
#define INTCICDIPR12 INTC.ICDIPR12
#define INTCICDIPR13 INTC.ICDIPR13
#define INTCICDIPR14 INTC.ICDIPR14
#define INTCICDIPR15 INTC.ICDIPR15
#define INTCICDIPR16 INTC.ICDIPR16
#define INTCICDIPR17 INTC.ICDIPR17
#define INTCICDIPR18 INTC.ICDIPR18
#define INTCICDIPR19 INTC.ICDIPR19
#define INTCICDIPR20 INTC.ICDIPR20
#define INTCICDIPR21 INTC.ICDIPR21
#define INTCICDIPR22 INTC.ICDIPR22
#define INTCICDIPR23 INTC.ICDIPR23
#define INTCICDIPR24 INTC.ICDIPR24
#define INTCICDIPR25 INTC.ICDIPR25
#define INTCICDIPR26 INTC.ICDIPR26
#define INTCICDIPR27 INTC.ICDIPR27
#define INTCICDIPR28 INTC.ICDIPR28
#define INTCICDIPR29 INTC.ICDIPR29
#define INTCICDIPR30 INTC.ICDIPR30
#define INTCICDIPR31 INTC.ICDIPR31
#define INTCICDIPR32 INTC.ICDIPR32
#define INTCICDIPR33 INTC.ICDIPR33
#define INTCICDIPR34 INTC.ICDIPR34
#define INTCICDIPR35 INTC.ICDIPR35
#define INTCICDIPR36 INTC.ICDIPR36
#define INTCICDIPR37 INTC.ICDIPR37
#define INTCICDIPR38 INTC.ICDIPR38
#define INTCICDIPR39 INTC.ICDIPR39
#define INTCICDIPR40 INTC.ICDIPR40
#define INTCICDIPR41 INTC.ICDIPR41
#define INTCICDIPR42 INTC.ICDIPR42
#define INTCICDIPR43 INTC.ICDIPR43
#define INTCICDIPR44 INTC.ICDIPR44
#define INTCICDIPR45 INTC.ICDIPR45
#define INTCICDIPR46 INTC.ICDIPR46
#define INTCICDIPR47 INTC.ICDIPR47
#define INTCICDIPR48 INTC.ICDIPR48
#define INTCICDIPR49 INTC.ICDIPR49
#define INTCICDIPR50 INTC.ICDIPR50
#define INTCICDIPR51 INTC.ICDIPR51
#define INTCICDIPR52 INTC.ICDIPR52
#define INTCICDIPR53 INTC.ICDIPR53
#define INTCICDIPR54 INTC.ICDIPR54
#define INTCICDIPR55 INTC.ICDIPR55
#define INTCICDIPR56 INTC.ICDIPR56
#define INTCICDIPR57 INTC.ICDIPR57
#define INTCICDIPR58 INTC.ICDIPR58
#define INTCICDIPR59 INTC.ICDIPR59
#define INTCICDIPR60 INTC.ICDIPR60
#define INTCICDIPR61 INTC.ICDIPR61
#define INTCICDIPR62 INTC.ICDIPR62
#define INTCICDIPR63 INTC.ICDIPR63
#define INTCICDIPR64 INTC.ICDIPR64
#define INTCICDIPR65 INTC.ICDIPR65
#define INTCICDIPR66 INTC.ICDIPR66
#define INTCICDIPR67 INTC.ICDIPR67
#define INTCICDIPR68 INTC.ICDIPR68
#define INTCICDIPR69 INTC.ICDIPR69
#define INTCICDIPR70 INTC.ICDIPR70
#define INTCICDIPR71 INTC.ICDIPR71
#define INTCICDIPR72 INTC.ICDIPR72
#define INTCICDIPR73 INTC.ICDIPR73
#define INTCICDIPR74 INTC.ICDIPR74
#define INTCICDIPR75 INTC.ICDIPR75
#define INTCICDIPR76 INTC.ICDIPR76
#define INTCICDIPR77 INTC.ICDIPR77
#define INTCICDIPR78 INTC.ICDIPR78
#define INTCICDIPR79 INTC.ICDIPR79
#define INTCICDIPR80 INTC.ICDIPR80
#define INTCICDIPR81 INTC.ICDIPR81
#define INTCICDIPR82 INTC.ICDIPR82
#define INTCICDIPR83 INTC.ICDIPR83
#define INTCICDIPR84 INTC.ICDIPR84
#define INTCICDIPR85 INTC.ICDIPR85
#define INTCICDIPR86 INTC.ICDIPR86
#define INTCICDIPR87 INTC.ICDIPR87
#define INTCICDIPR88 INTC.ICDIPR88
#define INTCICDIPR89 INTC.ICDIPR89
#define INTCICDIPR90 INTC.ICDIPR90
#define INTCICDIPR91 INTC.ICDIPR91
#define INTCICDIPR92 INTC.ICDIPR92
#define INTCICDIPR93 INTC.ICDIPR93
#define INTCICDIPR94 INTC.ICDIPR94
#define INTCICDIPR95 INTC.ICDIPR95
#define INTCICDIPR96 INTC.ICDIPR96
#define INTCICDIPR97 INTC.ICDIPR97
#define INTCICDIPR98 INTC.ICDIPR98
#define INTCICDIPR99 INTC.ICDIPR99
#define INTCICDIPR100 INTC.ICDIPR100
#define INTCICDIPR101 INTC.ICDIPR101
#define INTCICDIPR102 INTC.ICDIPR102
#define INTCICDIPR103 INTC.ICDIPR103
#define INTCICDIPR104 INTC.ICDIPR104
#define INTCICDIPR105 INTC.ICDIPR105
#define INTCICDIPR106 INTC.ICDIPR106
#define INTCICDIPR107 INTC.ICDIPR107
#define INTCICDIPR108 INTC.ICDIPR108
#define INTCICDIPR109 INTC.ICDIPR109
#define INTCICDIPR110 INTC.ICDIPR110
#define INTCICDIPR111 INTC.ICDIPR111
#define INTCICDIPR112 INTC.ICDIPR112
#define INTCICDIPR113 INTC.ICDIPR113
#define INTCICDIPR114 INTC.ICDIPR114
#define INTCICDIPR115 INTC.ICDIPR115
#define INTCICDIPR116 INTC.ICDIPR116
#define INTCICDIPR117 INTC.ICDIPR117
#define INTCICDIPR118 INTC.ICDIPR118
#define INTCICDIPR119 INTC.ICDIPR119
#define INTCICDIPR120 INTC.ICDIPR120
#define INTCICDIPR121 INTC.ICDIPR121
#define INTCICDIPR122 INTC.ICDIPR122
#define INTCICDIPR123 INTC.ICDIPR123
#define INTCICDIPR124 INTC.ICDIPR124
#define INTCICDIPR125 INTC.ICDIPR125
#define INTCICDIPR126 INTC.ICDIPR126
#define INTCICDIPR127 INTC.ICDIPR127
#define INTCICDIPR128 INTC.ICDIPR128
#define INTCICDIPR129 INTC.ICDIPR129
#define INTCICDIPR130 INTC.ICDIPR130
#define INTCICDIPR131 INTC.ICDIPR131
#define INTCICDIPR132 INTC.ICDIPR132
#define INTCICDIPR133 INTC.ICDIPR133
#define INTCICDIPR134 INTC.ICDIPR134
#define INTCICDIPR135 INTC.ICDIPR135
#define INTCICDIPR136 INTC.ICDIPR136
#define INTCICDIPR137 INTC.ICDIPR137
#define INTCICDIPR138 INTC.ICDIPR138
#define INTCICDIPR139 INTC.ICDIPR139
#define INTCICDIPR140 INTC.ICDIPR140
#define INTCICDIPR141 INTC.ICDIPR141
#define INTCICDIPR142 INTC.ICDIPR142
#define INTCICDIPR143 INTC.ICDIPR143
#define INTCICDIPR144 INTC.ICDIPR144
#define INTCICDIPR145 INTC.ICDIPR145
#define INTCICDIPR146 INTC.ICDIPR146
#define INTCICDIPTR0 INTC.ICDIPTR0
#define INTCICDIPTR1 INTC.ICDIPTR1
#define INTCICDIPTR2 INTC.ICDIPTR2
#define INTCICDIPTR3 INTC.ICDIPTR3
#define INTCICDIPTR4 INTC.ICDIPTR4
#define INTCICDIPTR5 INTC.ICDIPTR5
#define INTCICDIPTR6 INTC.ICDIPTR6
#define INTCICDIPTR7 INTC.ICDIPTR7
#define INTCICDIPTR8 INTC.ICDIPTR8
#define INTCICDIPTR9 INTC.ICDIPTR9
#define INTCICDIPTR10 INTC.ICDIPTR10
#define INTCICDIPTR11 INTC.ICDIPTR11
#define INTCICDIPTR12 INTC.ICDIPTR12
#define INTCICDIPTR13 INTC.ICDIPTR13
#define INTCICDIPTR14 INTC.ICDIPTR14
#define INTCICDIPTR15 INTC.ICDIPTR15
#define INTCICDIPTR16 INTC.ICDIPTR16
#define INTCICDIPTR17 INTC.ICDIPTR17
#define INTCICDIPTR18 INTC.ICDIPTR18
#define INTCICDIPTR19 INTC.ICDIPTR19
#define INTCICDIPTR20 INTC.ICDIPTR20
#define INTCICDIPTR21 INTC.ICDIPTR21
#define INTCICDIPTR22 INTC.ICDIPTR22
#define INTCICDIPTR23 INTC.ICDIPTR23
#define INTCICDIPTR24 INTC.ICDIPTR24
#define INTCICDIPTR25 INTC.ICDIPTR25
#define INTCICDIPTR26 INTC.ICDIPTR26
#define INTCICDIPTR27 INTC.ICDIPTR27
#define INTCICDIPTR28 INTC.ICDIPTR28
#define INTCICDIPTR29 INTC.ICDIPTR29
#define INTCICDIPTR30 INTC.ICDIPTR30
#define INTCICDIPTR31 INTC.ICDIPTR31
#define INTCICDIPTR32 INTC.ICDIPTR32
#define INTCICDIPTR33 INTC.ICDIPTR33
#define INTCICDIPTR34 INTC.ICDIPTR34
#define INTCICDIPTR35 INTC.ICDIPTR35
#define INTCICDIPTR36 INTC.ICDIPTR36
#define INTCICDIPTR37 INTC.ICDIPTR37
#define INTCICDIPTR38 INTC.ICDIPTR38
#define INTCICDIPTR39 INTC.ICDIPTR39
#define INTCICDIPTR40 INTC.ICDIPTR40
#define INTCICDIPTR41 INTC.ICDIPTR41
#define INTCICDIPTR42 INTC.ICDIPTR42
#define INTCICDIPTR43 INTC.ICDIPTR43
#define INTCICDIPTR44 INTC.ICDIPTR44
#define INTCICDIPTR45 INTC.ICDIPTR45
#define INTCICDIPTR46 INTC.ICDIPTR46
#define INTCICDIPTR47 INTC.ICDIPTR47
#define INTCICDIPTR48 INTC.ICDIPTR48
#define INTCICDIPTR49 INTC.ICDIPTR49
#define INTCICDIPTR50 INTC.ICDIPTR50
#define INTCICDIPTR51 INTC.ICDIPTR51
#define INTCICDIPTR52 INTC.ICDIPTR52
#define INTCICDIPTR53 INTC.ICDIPTR53
#define INTCICDIPTR54 INTC.ICDIPTR54
#define INTCICDIPTR55 INTC.ICDIPTR55
#define INTCICDIPTR56 INTC.ICDIPTR56
#define INTCICDIPTR57 INTC.ICDIPTR57
#define INTCICDIPTR58 INTC.ICDIPTR58
#define INTCICDIPTR59 INTC.ICDIPTR59
#define INTCICDIPTR60 INTC.ICDIPTR60
#define INTCICDIPTR61 INTC.ICDIPTR61
#define INTCICDIPTR62 INTC.ICDIPTR62
#define INTCICDIPTR63 INTC.ICDIPTR63
#define INTCICDIPTR64 INTC.ICDIPTR64
#define INTCICDIPTR65 INTC.ICDIPTR65
#define INTCICDIPTR66 INTC.ICDIPTR66
#define INTCICDIPTR67 INTC.ICDIPTR67
#define INTCICDIPTR68 INTC.ICDIPTR68
#define INTCICDIPTR69 INTC.ICDIPTR69
#define INTCICDIPTR70 INTC.ICDIPTR70
#define INTCICDIPTR71 INTC.ICDIPTR71
#define INTCICDIPTR72 INTC.ICDIPTR72
#define INTCICDIPTR73 INTC.ICDIPTR73
#define INTCICDIPTR74 INTC.ICDIPTR74
#define INTCICDIPTR75 INTC.ICDIPTR75
#define INTCICDIPTR76 INTC.ICDIPTR76
#define INTCICDIPTR77 INTC.ICDIPTR77
#define INTCICDIPTR78 INTC.ICDIPTR78
#define INTCICDIPTR79 INTC.ICDIPTR79
#define INTCICDIPTR80 INTC.ICDIPTR80
#define INTCICDIPTR81 INTC.ICDIPTR81
#define INTCICDIPTR82 INTC.ICDIPTR82
#define INTCICDIPTR83 INTC.ICDIPTR83
#define INTCICDIPTR84 INTC.ICDIPTR84
#define INTCICDIPTR85 INTC.ICDIPTR85
#define INTCICDIPTR86 INTC.ICDIPTR86
#define INTCICDIPTR87 INTC.ICDIPTR87
#define INTCICDIPTR88 INTC.ICDIPTR88
#define INTCICDIPTR89 INTC.ICDIPTR89
#define INTCICDIPTR90 INTC.ICDIPTR90
#define INTCICDIPTR91 INTC.ICDIPTR91
#define INTCICDIPTR92 INTC.ICDIPTR92
#define INTCICDIPTR93 INTC.ICDIPTR93
#define INTCICDIPTR94 INTC.ICDIPTR94
#define INTCICDIPTR95 INTC.ICDIPTR95
#define INTCICDIPTR96 INTC.ICDIPTR96
#define INTCICDIPTR97 INTC.ICDIPTR97
#define INTCICDIPTR98 INTC.ICDIPTR98
#define INTCICDIPTR99 INTC.ICDIPTR99
#define INTCICDIPTR100 INTC.ICDIPTR100
#define INTCICDIPTR101 INTC.ICDIPTR101
#define INTCICDIPTR102 INTC.ICDIPTR102
#define INTCICDIPTR103 INTC.ICDIPTR103
#define INTCICDIPTR104 INTC.ICDIPTR104
#define INTCICDIPTR105 INTC.ICDIPTR105
#define INTCICDIPTR106 INTC.ICDIPTR106
#define INTCICDIPTR107 INTC.ICDIPTR107
#define INTCICDIPTR108 INTC.ICDIPTR108
#define INTCICDIPTR109 INTC.ICDIPTR109
#define INTCICDIPTR110 INTC.ICDIPTR110
#define INTCICDIPTR111 INTC.ICDIPTR111
#define INTCICDIPTR112 INTC.ICDIPTR112
#define INTCICDIPTR113 INTC.ICDIPTR113
#define INTCICDIPTR114 INTC.ICDIPTR114
#define INTCICDIPTR115 INTC.ICDIPTR115
#define INTCICDIPTR116 INTC.ICDIPTR116
#define INTCICDIPTR117 INTC.ICDIPTR117
#define INTCICDIPTR118 INTC.ICDIPTR118
#define INTCICDIPTR119 INTC.ICDIPTR119
#define INTCICDIPTR120 INTC.ICDIPTR120
#define INTCICDIPTR121 INTC.ICDIPTR121
#define INTCICDIPTR122 INTC.ICDIPTR122
#define INTCICDIPTR123 INTC.ICDIPTR123
#define INTCICDIPTR124 INTC.ICDIPTR124
#define INTCICDIPTR125 INTC.ICDIPTR125
#define INTCICDIPTR126 INTC.ICDIPTR126
#define INTCICDIPTR127 INTC.ICDIPTR127
#define INTCICDIPTR128 INTC.ICDIPTR128
#define INTCICDIPTR129 INTC.ICDIPTR129
#define INTCICDIPTR130 INTC.ICDIPTR130
#define INTCICDIPTR131 INTC.ICDIPTR131
#define INTCICDIPTR132 INTC.ICDIPTR132
#define INTCICDIPTR133 INTC.ICDIPTR133
#define INTCICDIPTR134 INTC.ICDIPTR134
#define INTCICDIPTR135 INTC.ICDIPTR135
#define INTCICDIPTR136 INTC.ICDIPTR136
#define INTCICDIPTR137 INTC.ICDIPTR137
#define INTCICDIPTR138 INTC.ICDIPTR138
#define INTCICDIPTR139 INTC.ICDIPTR139
#define INTCICDIPTR140 INTC.ICDIPTR140
#define INTCICDIPTR141 INTC.ICDIPTR141
#define INTCICDIPTR142 INTC.ICDIPTR142
#define INTCICDIPTR143 INTC.ICDIPTR143
#define INTCICDIPTR144 INTC.ICDIPTR144
#define INTCICDIPTR145 INTC.ICDIPTR145
#define INTCICDIPTR146 INTC.ICDIPTR146
#define INTCICDICFR0 INTC.ICDICFR0
#define INTCICDICFR1 INTC.ICDICFR1
#define INTCICDICFR2 INTC.ICDICFR2
#define INTCICDICFR3 INTC.ICDICFR3
#define INTCICDICFR4 INTC.ICDICFR4
#define INTCICDICFR5 INTC.ICDICFR5
#define INTCICDICFR6 INTC.ICDICFR6
#define INTCICDICFR7 INTC.ICDICFR7
#define INTCICDICFR8 INTC.ICDICFR8
#define INTCICDICFR9 INTC.ICDICFR9
#define INTCICDICFR10 INTC.ICDICFR10
#define INTCICDICFR11 INTC.ICDICFR11
#define INTCICDICFR12 INTC.ICDICFR12
#define INTCICDICFR13 INTC.ICDICFR13
#define INTCICDICFR14 INTC.ICDICFR14
#define INTCICDICFR15 INTC.ICDICFR15
#define INTCICDICFR16 INTC.ICDICFR16
#define INTCICDICFR17 INTC.ICDICFR17
#define INTCICDICFR18 INTC.ICDICFR18
#define INTCICDICFR19 INTC.ICDICFR19
#define INTCICDICFR20 INTC.ICDICFR20
#define INTCICDICFR21 INTC.ICDICFR21
#define INTCICDICFR22 INTC.ICDICFR22
#define INTCICDICFR23 INTC.ICDICFR23
#define INTCICDICFR24 INTC.ICDICFR24
#define INTCICDICFR25 INTC.ICDICFR25
#define INTCICDICFR26 INTC.ICDICFR26
#define INTCICDICFR27 INTC.ICDICFR27
#define INTCICDICFR28 INTC.ICDICFR28
#define INTCICDICFR29 INTC.ICDICFR29
#define INTCICDICFR30 INTC.ICDICFR30
#define INTCICDICFR31 INTC.ICDICFR31
#define INTCICDICFR32 INTC.ICDICFR32
#define INTCICDICFR33 INTC.ICDICFR33
#define INTCICDICFR34 INTC.ICDICFR34
#define INTCICDICFR35 INTC.ICDICFR35
#define INTCICDICFR36 INTC.ICDICFR36
#define INTCPPI_STATUS INTC.PPI_STATUS
#define INTCSPI_STATUS0 INTC.SPI_STATUS0
#define INTCSPI_STATUS1 INTC.SPI_STATUS1
#define INTCSPI_STATUS2 INTC.SPI_STATUS2
#define INTCSPI_STATUS3 INTC.SPI_STATUS3
#define INTCSPI_STATUS4 INTC.SPI_STATUS4
#define INTCSPI_STATUS5 INTC.SPI_STATUS5
#define INTCSPI_STATUS6 INTC.SPI_STATUS6
#define INTCSPI_STATUS7 INTC.SPI_STATUS7
#define INTCSPI_STATUS8 INTC.SPI_STATUS8
#define INTCSPI_STATUS9 INTC.SPI_STATUS9
#define INTCSPI_STATUS10 INTC.SPI_STATUS10
#define INTCSPI_STATUS11 INTC.SPI_STATUS11
#define INTCSPI_STATUS12 INTC.SPI_STATUS12
#define INTCSPI_STATUS13 INTC.SPI_STATUS13
#define INTCSPI_STATUS14 INTC.SPI_STATUS14
#define INTCSPI_STATUS15 INTC.SPI_STATUS15
#define INTCSPI_STATUS16 INTC.SPI_STATUS16
#define INTCICDSGIR INTC.ICDSGIR
#define INTCICCICR INTC.ICCICR
#define INTCICCPMR INTC.ICCPMR
#define INTCICCBPR INTC.ICCBPR
#define INTCICCIAR INTC.ICCIAR
#define INTCICCEOIR INTC.ICCEOIR
#define INTCICCRPR INTC.ICCRPR
#define INTCICCHPIR INTC.ICCHPIR
#define INTCICCABPR INTC.ICCABPR
#define INTCICCIIDR INTC.ICCIIDR
#define INTCICR0 INTC.ICR0
#define INTCICR1 INTC.ICR1
#define INTCIRQRR INTC.IRQRR
/* <-SEC M1.10.1 */
/* <-QAC 0639 */
#endif
