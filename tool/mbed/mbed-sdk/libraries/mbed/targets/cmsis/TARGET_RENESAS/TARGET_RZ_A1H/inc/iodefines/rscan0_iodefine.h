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
* File Name : rscan0_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef RSCAN0_IODEFINE_H
#define RSCAN0_IODEFINE_H
/* ->QAC 0639 : Over 127 members (C90) */
/* ->QAC 0857 : Over 1024 #define (C90) */
/* ->SEC M1.10.1 : Not magic number */

struct st_rscan0
{                                                          /* RSCAN0           */
/* start of struct st_rscan_from_rscan0cncfg */
    union iodefine_reg32_t  C0CFG;                         /*  C0CFG           */
    union iodefine_reg32_t  C0CTR;                         /*  C0CTR           */
    union iodefine_reg32_t  C0STS;                         /*  C0STS           */
    union iodefine_reg32_t  C0ERFL;                        /*  C0ERFL          */
/* end of struct st_rscan_from_rscan0cncfg */
    
/* start of struct st_rscan_from_rscan0cncfg */
    union iodefine_reg32_t  C1CFG;                         /*  C1CFG           */
    union iodefine_reg32_t  C1CTR;                         /*  C1CTR           */
    union iodefine_reg32_t  C1STS;                         /*  C1STS           */
    union iodefine_reg32_t  C1ERFL;                        /*  C1ERFL          */
/* end of struct st_rscan_from_rscan0cncfg */
    
/* start of struct st_rscan_from_rscan0cncfg */
    union iodefine_reg32_t  C2CFG;                         /*  C2CFG           */
    union iodefine_reg32_t  C2CTR;                         /*  C2CTR           */
    union iodefine_reg32_t  C2STS;                         /*  C2STS           */
    union iodefine_reg32_t  C2ERFL;                        /*  C2ERFL          */
/* end of struct st_rscan_from_rscan0cncfg */
    
/* start of struct st_rscan_from_rscan0cncfg */
    union iodefine_reg32_t  C3CFG;                         /*  C3CFG           */
    union iodefine_reg32_t  C3CTR;                         /*  C3CTR           */
    union iodefine_reg32_t  C3STS;                         /*  C3STS           */
    union iodefine_reg32_t  C3ERFL;                        /*  C3ERFL          */
/* end of struct st_rscan_from_rscan0cncfg */
    
/* start of struct st_rscan_from_rscan0cncfg */
    union iodefine_reg32_t  C4CFG;                         /*  C4CFG           */
    union iodefine_reg32_t  C4CTR;                         /*  C4CTR           */
    union iodefine_reg32_t  C4STS;                         /*  C4STS           */
    union iodefine_reg32_t  C4ERFL;                        /*  C4ERFL          */
/* end of struct st_rscan_from_rscan0cncfg */
    
    volatile uint8_t   dummy159[52];                           /*                  */
    union iodefine_reg32_t  GCFG;                          /*  GCFG            */
    union iodefine_reg32_t  GCTR;                          /*  GCTR            */
    union iodefine_reg32_t  GSTS;                          /*  GSTS            */
    union iodefine_reg32_t  GERFL;                         /*  GERFL           */
    union iodefine_reg32_16_t  GTSC;                       /*  GTSC            */
    union iodefine_reg32_t  GAFLECTR;                      /*  GAFLECTR        */
#define RSCAN0_GAFLCFG0_COUNT 2
    union iodefine_reg32_t  GAFLCFG0;                      /*  GAFLCFG0        */
    union iodefine_reg32_t  GAFLCFG1;                      /*  GAFLCFG1        */
    union iodefine_reg32_t  RMNB;                          /*  RMNB            */
#define RSCAN0_RMND0_COUNT 3
    union iodefine_reg32_t  RMND0;                         /*  RMND0           */
    union iodefine_reg32_t  RMND1;                         /*  RMND1           */
    union iodefine_reg32_t  RMND2;                         /*  RMND2           */
    
    volatile uint8_t   dummy160[4];                            /*                  */
#define RSCAN0_RFCC0_COUNT 8
    union iodefine_reg32_t  RFCC0;                         /*  RFCC0           */
    union iodefine_reg32_t  RFCC1;                         /*  RFCC1           */
    union iodefine_reg32_t  RFCC2;                         /*  RFCC2           */
    union iodefine_reg32_t  RFCC3;                         /*  RFCC3           */
    union iodefine_reg32_t  RFCC4;                         /*  RFCC4           */
    union iodefine_reg32_t  RFCC5;                         /*  RFCC5           */
    union iodefine_reg32_t  RFCC6;                         /*  RFCC6           */
    union iodefine_reg32_t  RFCC7;                         /*  RFCC7           */
#define RSCAN0_RFSTS0_COUNT 8
    union iodefine_reg32_t  RFSTS0;                        /*  RFSTS0          */
    union iodefine_reg32_t  RFSTS1;                        /*  RFSTS1          */
    union iodefine_reg32_t  RFSTS2;                        /*  RFSTS2          */
    union iodefine_reg32_t  RFSTS3;                        /*  RFSTS3          */
    union iodefine_reg32_t  RFSTS4;                        /*  RFSTS4          */
    union iodefine_reg32_t  RFSTS5;                        /*  RFSTS5          */
    union iodefine_reg32_t  RFSTS6;                        /*  RFSTS6          */
    union iodefine_reg32_t  RFSTS7;                        /*  RFSTS7          */
#define RSCAN0_RFPCTR0_COUNT 8
    union iodefine_reg32_t  RFPCTR0;                       /*  RFPCTR0         */
    union iodefine_reg32_t  RFPCTR1;                       /*  RFPCTR1         */
    union iodefine_reg32_t  RFPCTR2;                       /*  RFPCTR2         */
    union iodefine_reg32_t  RFPCTR3;                       /*  RFPCTR3         */
    union iodefine_reg32_t  RFPCTR4;                       /*  RFPCTR4         */
    union iodefine_reg32_t  RFPCTR5;                       /*  RFPCTR5         */
    union iodefine_reg32_t  RFPCTR6;                       /*  RFPCTR6         */
    union iodefine_reg32_t  RFPCTR7;                       /*  RFPCTR7         */
#define RSCAN0_CFCC0_COUNT 15
    union iodefine_reg32_t  CFCC0;                         /*  CFCC0           */
    union iodefine_reg32_t  CFCC1;                         /*  CFCC1           */
    union iodefine_reg32_t  CFCC2;                         /*  CFCC2           */
    union iodefine_reg32_t  CFCC3;                         /*  CFCC3           */
    union iodefine_reg32_t  CFCC4;                         /*  CFCC4           */
    union iodefine_reg32_t  CFCC5;                         /*  CFCC5           */
    union iodefine_reg32_t  CFCC6;                         /*  CFCC6           */
    union iodefine_reg32_t  CFCC7;                         /*  CFCC7           */
    union iodefine_reg32_t  CFCC8;                         /*  CFCC8           */
    union iodefine_reg32_t  CFCC9;                         /*  CFCC9           */
    union iodefine_reg32_t  CFCC10;                        /*  CFCC10          */
    union iodefine_reg32_t  CFCC11;                        /*  CFCC11          */
    union iodefine_reg32_t  CFCC12;                        /*  CFCC12          */
    union iodefine_reg32_t  CFCC13;                        /*  CFCC13          */
    union iodefine_reg32_t  CFCC14;                        /*  CFCC14          */
    
    volatile uint8_t   dummy161[36];                           /*                  */
#define RSCAN0_CFSTS0_COUNT 15
    union iodefine_reg32_t  CFSTS0;                        /*  CFSTS0          */
    union iodefine_reg32_t  CFSTS1;                        /*  CFSTS1          */
    union iodefine_reg32_t  CFSTS2;                        /*  CFSTS2          */
    union iodefine_reg32_t  CFSTS3;                        /*  CFSTS3          */
    union iodefine_reg32_t  CFSTS4;                        /*  CFSTS4          */
    union iodefine_reg32_t  CFSTS5;                        /*  CFSTS5          */
    union iodefine_reg32_t  CFSTS6;                        /*  CFSTS6          */
    union iodefine_reg32_t  CFSTS7;                        /*  CFSTS7          */
    union iodefine_reg32_t  CFSTS8;                        /*  CFSTS8          */
    union iodefine_reg32_t  CFSTS9;                        /*  CFSTS9          */
    union iodefine_reg32_t  CFSTS10;                       /*  CFSTS10         */
    union iodefine_reg32_t  CFSTS11;                       /*  CFSTS11         */
    union iodefine_reg32_t  CFSTS12;                       /*  CFSTS12         */
    union iodefine_reg32_t  CFSTS13;                       /*  CFSTS13         */
    union iodefine_reg32_t  CFSTS14;                       /*  CFSTS14         */
    
    volatile uint8_t   dummy162[36];                           /*                  */
#define RSCAN0_CFPCTR0_COUNT 15
    union iodefine_reg32_t  CFPCTR0;                       /*  CFPCTR0         */
    union iodefine_reg32_t  CFPCTR1;                       /*  CFPCTR1         */
    union iodefine_reg32_t  CFPCTR2;                       /*  CFPCTR2         */
    union iodefine_reg32_t  CFPCTR3;                       /*  CFPCTR3         */
    union iodefine_reg32_t  CFPCTR4;                       /*  CFPCTR4         */
    union iodefine_reg32_t  CFPCTR5;                       /*  CFPCTR5         */
    union iodefine_reg32_t  CFPCTR6;                       /*  CFPCTR6         */
    union iodefine_reg32_t  CFPCTR7;                       /*  CFPCTR7         */
    union iodefine_reg32_t  CFPCTR8;                       /*  CFPCTR8         */
    union iodefine_reg32_t  CFPCTR9;                       /*  CFPCTR9         */
    union iodefine_reg32_t  CFPCTR10;                      /*  CFPCTR10        */
    union iodefine_reg32_t  CFPCTR11;                      /*  CFPCTR11        */
    union iodefine_reg32_t  CFPCTR12;                      /*  CFPCTR12        */
    union iodefine_reg32_t  CFPCTR13;                      /*  CFPCTR13        */
    union iodefine_reg32_t  CFPCTR14;                      /*  CFPCTR14        */
    
    volatile uint8_t   dummy163[36];                           /*                  */
    union iodefine_reg32_t  FESTS;                         /*  FESTS           */
    union iodefine_reg32_t  FFSTS;                         /*  FFSTS           */
    union iodefine_reg32_t  FMSTS;                         /*  FMSTS           */
    union iodefine_reg32_t  RFISTS;                        /*  RFISTS          */
    union iodefine_reg32_t  CFRISTS;                       /*  CFRISTS         */
    union iodefine_reg32_t  CFTISTS;                       /*  CFTISTS         */
    
#define RSCAN0_TMC0_COUNT 80
    volatile uint8_t   TMC0;                                   /*  TMC0            */
    volatile uint8_t   TMC1;                                   /*  TMC1            */
    volatile uint8_t   TMC2;                                   /*  TMC2            */
    volatile uint8_t   TMC3;                                   /*  TMC3            */
    volatile uint8_t   TMC4;                                   /*  TMC4            */
    volatile uint8_t   TMC5;                                   /*  TMC5            */
    volatile uint8_t   TMC6;                                   /*  TMC6            */
    volatile uint8_t   TMC7;                                   /*  TMC7            */
    volatile uint8_t   TMC8;                                   /*  TMC8            */
    volatile uint8_t   TMC9;                                   /*  TMC9            */
    volatile uint8_t   TMC10;                                  /*  TMC10           */
    volatile uint8_t   TMC11;                                  /*  TMC11           */
    volatile uint8_t   TMC12;                                  /*  TMC12           */
    volatile uint8_t   TMC13;                                  /*  TMC13           */
    volatile uint8_t   TMC14;                                  /*  TMC14           */
    volatile uint8_t   TMC15;                                  /*  TMC15           */
    volatile uint8_t   TMC16;                                  /*  TMC16           */
    volatile uint8_t   TMC17;                                  /*  TMC17           */
    volatile uint8_t   TMC18;                                  /*  TMC18           */
    volatile uint8_t   TMC19;                                  /*  TMC19           */
    volatile uint8_t   TMC20;                                  /*  TMC20           */
    volatile uint8_t   TMC21;                                  /*  TMC21           */
    volatile uint8_t   TMC22;                                  /*  TMC22           */
    volatile uint8_t   TMC23;                                  /*  TMC23           */
    volatile uint8_t   TMC24;                                  /*  TMC24           */
    volatile uint8_t   TMC25;                                  /*  TMC25           */
    volatile uint8_t   TMC26;                                  /*  TMC26           */
    volatile uint8_t   TMC27;                                  /*  TMC27           */
    volatile uint8_t   TMC28;                                  /*  TMC28           */
    volatile uint8_t   TMC29;                                  /*  TMC29           */
    volatile uint8_t   TMC30;                                  /*  TMC30           */
    volatile uint8_t   TMC31;                                  /*  TMC31           */
    volatile uint8_t   TMC32;                                  /*  TMC32           */
    volatile uint8_t   TMC33;                                  /*  TMC33           */
    volatile uint8_t   TMC34;                                  /*  TMC34           */
    volatile uint8_t   TMC35;                                  /*  TMC35           */
    volatile uint8_t   TMC36;                                  /*  TMC36           */
    volatile uint8_t   TMC37;                                  /*  TMC37           */
    volatile uint8_t   TMC38;                                  /*  TMC38           */
    volatile uint8_t   TMC39;                                  /*  TMC39           */
    volatile uint8_t   TMC40;                                  /*  TMC40           */
    volatile uint8_t   TMC41;                                  /*  TMC41           */
    volatile uint8_t   TMC42;                                  /*  TMC42           */
    volatile uint8_t   TMC43;                                  /*  TMC43           */
    volatile uint8_t   TMC44;                                  /*  TMC44           */
    volatile uint8_t   TMC45;                                  /*  TMC45           */
    volatile uint8_t   TMC46;                                  /*  TMC46           */
    volatile uint8_t   TMC47;                                  /*  TMC47           */
    volatile uint8_t   TMC48;                                  /*  TMC48           */
    volatile uint8_t   TMC49;                                  /*  TMC49           */
    volatile uint8_t   TMC50;                                  /*  TMC50           */
    volatile uint8_t   TMC51;                                  /*  TMC51           */
    volatile uint8_t   TMC52;                                  /*  TMC52           */
    volatile uint8_t   TMC53;                                  /*  TMC53           */
    volatile uint8_t   TMC54;                                  /*  TMC54           */
    volatile uint8_t   TMC55;                                  /*  TMC55           */
    volatile uint8_t   TMC56;                                  /*  TMC56           */
    volatile uint8_t   TMC57;                                  /*  TMC57           */
    volatile uint8_t   TMC58;                                  /*  TMC58           */
    volatile uint8_t   TMC59;                                  /*  TMC59           */
    volatile uint8_t   TMC60;                                  /*  TMC60           */
    volatile uint8_t   TMC61;                                  /*  TMC61           */
    volatile uint8_t   TMC62;                                  /*  TMC62           */
    volatile uint8_t   TMC63;                                  /*  TMC63           */
    volatile uint8_t   TMC64;                                  /*  TMC64           */
    volatile uint8_t   TMC65;                                  /*  TMC65           */
    volatile uint8_t   TMC66;                                  /*  TMC66           */
    volatile uint8_t   TMC67;                                  /*  TMC67           */
    volatile uint8_t   TMC68;                                  /*  TMC68           */
    volatile uint8_t   TMC69;                                  /*  TMC69           */
    volatile uint8_t   TMC70;                                  /*  TMC70           */
    volatile uint8_t   TMC71;                                  /*  TMC71           */
    volatile uint8_t   TMC72;                                  /*  TMC72           */
    volatile uint8_t   TMC73;                                  /*  TMC73           */
    volatile uint8_t   TMC74;                                  /*  TMC74           */
    volatile uint8_t   TMC75;                                  /*  TMC75           */
    volatile uint8_t   TMC76;                                  /*  TMC76           */
    volatile uint8_t   TMC77;                                  /*  TMC77           */
    volatile uint8_t   TMC78;                                  /*  TMC78           */
    volatile uint8_t   TMC79;                                  /*  TMC79           */
    volatile uint8_t   dummy164[48];                           /*                  */
#define RSCAN0_TMSTS0_COUNT 80
    volatile uint8_t   TMSTS0;                                 /*  TMSTS0          */
    volatile uint8_t   TMSTS1;                                 /*  TMSTS1          */
    volatile uint8_t   TMSTS2;                                 /*  TMSTS2          */
    volatile uint8_t   TMSTS3;                                 /*  TMSTS3          */
    volatile uint8_t   TMSTS4;                                 /*  TMSTS4          */
    volatile uint8_t   TMSTS5;                                 /*  TMSTS5          */
    volatile uint8_t   TMSTS6;                                 /*  TMSTS6          */
    volatile uint8_t   TMSTS7;                                 /*  TMSTS7          */
    volatile uint8_t   TMSTS8;                                 /*  TMSTS8          */
    volatile uint8_t   TMSTS9;                                 /*  TMSTS9          */
    volatile uint8_t   TMSTS10;                                /*  TMSTS10         */
    volatile uint8_t   TMSTS11;                                /*  TMSTS11         */
    volatile uint8_t   TMSTS12;                                /*  TMSTS12         */
    volatile uint8_t   TMSTS13;                                /*  TMSTS13         */
    volatile uint8_t   TMSTS14;                                /*  TMSTS14         */
    volatile uint8_t   TMSTS15;                                /*  TMSTS15         */
    volatile uint8_t   TMSTS16;                                /*  TMSTS16         */
    volatile uint8_t   TMSTS17;                                /*  TMSTS17         */
    volatile uint8_t   TMSTS18;                                /*  TMSTS18         */
    volatile uint8_t   TMSTS19;                                /*  TMSTS19         */
    volatile uint8_t   TMSTS20;                                /*  TMSTS20         */
    volatile uint8_t   TMSTS21;                                /*  TMSTS21         */
    volatile uint8_t   TMSTS22;                                /*  TMSTS22         */
    volatile uint8_t   TMSTS23;                                /*  TMSTS23         */
    volatile uint8_t   TMSTS24;                                /*  TMSTS24         */
    volatile uint8_t   TMSTS25;                                /*  TMSTS25         */
    volatile uint8_t   TMSTS26;                                /*  TMSTS26         */
    volatile uint8_t   TMSTS27;                                /*  TMSTS27         */
    volatile uint8_t   TMSTS28;                                /*  TMSTS28         */
    volatile uint8_t   TMSTS29;                                /*  TMSTS29         */
    volatile uint8_t   TMSTS30;                                /*  TMSTS30         */
    volatile uint8_t   TMSTS31;                                /*  TMSTS31         */
    volatile uint8_t   TMSTS32;                                /*  TMSTS32         */
    volatile uint8_t   TMSTS33;                                /*  TMSTS33         */
    volatile uint8_t   TMSTS34;                                /*  TMSTS34         */
    volatile uint8_t   TMSTS35;                                /*  TMSTS35         */
    volatile uint8_t   TMSTS36;                                /*  TMSTS36         */
    volatile uint8_t   TMSTS37;                                /*  TMSTS37         */
    volatile uint8_t   TMSTS38;                                /*  TMSTS38         */
    volatile uint8_t   TMSTS39;                                /*  TMSTS39         */
    volatile uint8_t   TMSTS40;                                /*  TMSTS40         */
    volatile uint8_t   TMSTS41;                                /*  TMSTS41         */
    volatile uint8_t   TMSTS42;                                /*  TMSTS42         */
    volatile uint8_t   TMSTS43;                                /*  TMSTS43         */
    volatile uint8_t   TMSTS44;                                /*  TMSTS44         */
    volatile uint8_t   TMSTS45;                                /*  TMSTS45         */
    volatile uint8_t   TMSTS46;                                /*  TMSTS46         */
    volatile uint8_t   TMSTS47;                                /*  TMSTS47         */
    volatile uint8_t   TMSTS48;                                /*  TMSTS48         */
    volatile uint8_t   TMSTS49;                                /*  TMSTS49         */
    volatile uint8_t   TMSTS50;                                /*  TMSTS50         */
    volatile uint8_t   TMSTS51;                                /*  TMSTS51         */
    volatile uint8_t   TMSTS52;                                /*  TMSTS52         */
    volatile uint8_t   TMSTS53;                                /*  TMSTS53         */
    volatile uint8_t   TMSTS54;                                /*  TMSTS54         */
    volatile uint8_t   TMSTS55;                                /*  TMSTS55         */
    volatile uint8_t   TMSTS56;                                /*  TMSTS56         */
    volatile uint8_t   TMSTS57;                                /*  TMSTS57         */
    volatile uint8_t   TMSTS58;                                /*  TMSTS58         */
    volatile uint8_t   TMSTS59;                                /*  TMSTS59         */
    volatile uint8_t   TMSTS60;                                /*  TMSTS60         */
    volatile uint8_t   TMSTS61;                                /*  TMSTS61         */
    volatile uint8_t   TMSTS62;                                /*  TMSTS62         */
    volatile uint8_t   TMSTS63;                                /*  TMSTS63         */
    volatile uint8_t   TMSTS64;                                /*  TMSTS64         */
    volatile uint8_t   TMSTS65;                                /*  TMSTS65         */
    volatile uint8_t   TMSTS66;                                /*  TMSTS66         */
    volatile uint8_t   TMSTS67;                                /*  TMSTS67         */
    volatile uint8_t   TMSTS68;                                /*  TMSTS68         */
    volatile uint8_t   TMSTS69;                                /*  TMSTS69         */
    volatile uint8_t   TMSTS70;                                /*  TMSTS70         */
    volatile uint8_t   TMSTS71;                                /*  TMSTS71         */
    volatile uint8_t   TMSTS72;                                /*  TMSTS72         */
    volatile uint8_t   TMSTS73;                                /*  TMSTS73         */
    volatile uint8_t   TMSTS74;                                /*  TMSTS74         */
    volatile uint8_t   TMSTS75;                                /*  TMSTS75         */
    volatile uint8_t   TMSTS76;                                /*  TMSTS76         */
    volatile uint8_t   TMSTS77;                                /*  TMSTS77         */
    volatile uint8_t   TMSTS78;                                /*  TMSTS78         */
    volatile uint8_t   TMSTS79;                                /*  TMSTS79         */
    volatile uint8_t   dummy165[48];                           /*                  */
#define RSCAN0_TMTRSTS0_COUNT 3
    union iodefine_reg32_t  TMTRSTS0;                      /*  TMTRSTS0        */
    union iodefine_reg32_t  TMTRSTS1;                      /*  TMTRSTS1        */
    union iodefine_reg32_t  TMTRSTS2;                      /*  TMTRSTS2        */
    
    volatile uint8_t   dummy166[4];                            /*                  */
#define RSCAN0_TMTARSTS0_COUNT 3
    union iodefine_reg32_t  TMTARSTS0;                     /*  TMTARSTS0       */
    union iodefine_reg32_t  TMTARSTS1;                     /*  TMTARSTS1       */
    union iodefine_reg32_t  TMTARSTS2;                     /*  TMTARSTS2       */
    
    volatile uint8_t   dummy167[4];                            /*                  */
#define RSCAN0_TMTCSTS0_COUNT 3
    union iodefine_reg32_t  TMTCSTS0;                      /*  TMTCSTS0        */
    union iodefine_reg32_t  TMTCSTS1;                      /*  TMTCSTS1        */
    union iodefine_reg32_t  TMTCSTS2;                      /*  TMTCSTS2        */
    
    volatile uint8_t   dummy168[4];                            /*                  */
#define RSCAN0_TMTASTS0_COUNT 3
    union iodefine_reg32_t  TMTASTS0;                      /*  TMTASTS0        */
    union iodefine_reg32_t  TMTASTS1;                      /*  TMTASTS1        */
    union iodefine_reg32_t  TMTASTS2;                      /*  TMTASTS2        */
    
    volatile uint8_t   dummy169[4];                            /*                  */
#define RSCAN0_TMIEC0_COUNT 3
    union iodefine_reg32_t  TMIEC0;                        /*  TMIEC0          */
    union iodefine_reg32_t  TMIEC1;                        /*  TMIEC1          */
    union iodefine_reg32_t  TMIEC2;                        /*  TMIEC2          */
    
    volatile uint8_t   dummy170[4];                            /*                  */
#define RSCAN0_TXQCC0_COUNT 5
    union iodefine_reg32_t  TXQCC0;                        /*  TXQCC0          */
    union iodefine_reg32_t  TXQCC1;                        /*  TXQCC1          */
    union iodefine_reg32_t  TXQCC2;                        /*  TXQCC2          */
    union iodefine_reg32_t  TXQCC3;                        /*  TXQCC3          */
    union iodefine_reg32_t  TXQCC4;                        /*  TXQCC4          */
    
    volatile uint8_t   dummy171[12];                           /*                  */
#define RSCAN0_TXQSTS0_COUNT 5
    union iodefine_reg32_t  TXQSTS0;                       /*  TXQSTS0         */
    union iodefine_reg32_t  TXQSTS1;                       /*  TXQSTS1         */
    union iodefine_reg32_t  TXQSTS2;                       /*  TXQSTS2         */
    union iodefine_reg32_t  TXQSTS3;                       /*  TXQSTS3         */
    union iodefine_reg32_t  TXQSTS4;                       /*  TXQSTS4         */
    
    volatile uint8_t   dummy172[12];                           /*                  */
#define RSCAN0_TXQPCTR0_COUNT 5
    union iodefine_reg32_t  TXQPCTR0;                      /*  TXQPCTR0        */
    union iodefine_reg32_t  TXQPCTR1;                      /*  TXQPCTR1        */
    union iodefine_reg32_t  TXQPCTR2;                      /*  TXQPCTR2        */
    union iodefine_reg32_t  TXQPCTR3;                      /*  TXQPCTR3        */
    union iodefine_reg32_t  TXQPCTR4;                      /*  TXQPCTR4        */
    
    volatile uint8_t   dummy173[12];                           /*                  */
#define RSCAN0_THLCC0_COUNT 5
    union iodefine_reg32_t  THLCC0;                        /*  THLCC0          */
    union iodefine_reg32_t  THLCC1;                        /*  THLCC1          */
    union iodefine_reg32_t  THLCC2;                        /*  THLCC2          */
    union iodefine_reg32_t  THLCC3;                        /*  THLCC3          */
    union iodefine_reg32_t  THLCC4;                        /*  THLCC4          */
    
    volatile uint8_t   dummy174[12];                           /*                  */
#define RSCAN0_THLSTS0_COUNT 5
    union iodefine_reg32_t  THLSTS0;                       /*  THLSTS0         */
    union iodefine_reg32_t  THLSTS1;                       /*  THLSTS1         */
    union iodefine_reg32_t  THLSTS2;                       /*  THLSTS2         */
    union iodefine_reg32_t  THLSTS3;                       /*  THLSTS3         */
    union iodefine_reg32_t  THLSTS4;                       /*  THLSTS4         */
    
    volatile uint8_t   dummy175[12];                           /*                  */
#define RSCAN0_THLPCTR0_COUNT 5
    union iodefine_reg32_t  THLPCTR0;                      /*  THLPCTR0        */
    union iodefine_reg32_t  THLPCTR1;                      /*  THLPCTR1        */
    union iodefine_reg32_t  THLPCTR2;                      /*  THLPCTR2        */
    union iodefine_reg32_t  THLPCTR3;                      /*  THLPCTR3        */
    union iodefine_reg32_t  THLPCTR4;                      /*  THLPCTR4        */
    
    volatile uint8_t   dummy176[12];                           /*                  */
#define RSCAN0_GTINTSTS0_COUNT 2
    union iodefine_reg32_t  GTINTSTS0;                     /*  GTINTSTS0       */
    union iodefine_reg32_t  GTINTSTS1;                     /*  GTINTSTS1       */
    union iodefine_reg32_t  GTSTCFG;                       /*  GTSTCFG         */
    union iodefine_reg32_t  GTSTCTR;                       /*  GTSTCTR         */
    
    volatile uint8_t   dummy177[12];                           /*                  */
    union iodefine_reg32_16_t  GLOCKK;                     /*  GLOCKK          */
    
    volatile uint8_t   dummy178[128];                          /*                  */
    
/* start of struct st_rscan_from_rscan0gaflidj */
    union iodefine_reg32_t  GAFLID0;                       /*  GAFLID0         */
    union iodefine_reg32_t  GAFLM0;                        /*  GAFLM0          */
    union iodefine_reg32_t  GAFLP00;                       /*  GAFLP00         */
    union iodefine_reg32_t  GAFLP10;                       /*  GAFLP10         */
/* end of struct st_rscan_from_rscan0gaflidj */
    
/* start of struct st_rscan_from_rscan0gaflidj */
    union iodefine_reg32_t  GAFLID1;                       /*  GAFLID1         */
    union iodefine_reg32_t  GAFLM1;                        /*  GAFLM1          */
    union iodefine_reg32_t  GAFLP01;                       /*  GAFLP01         */
    union iodefine_reg32_t  GAFLP11;                       /*  GAFLP11         */
/* end of struct st_rscan_from_rscan0gaflidj */
    
/* start of struct st_rscan_from_rscan0gaflidj */
    union iodefine_reg32_t  GAFLID2;                       /*  GAFLID2         */
    union iodefine_reg32_t  GAFLM2;                        /*  GAFLM2          */
    union iodefine_reg32_t  GAFLP02;                       /*  GAFLP02         */
    union iodefine_reg32_t  GAFLP12;                       /*  GAFLP12         */
/* end of struct st_rscan_from_rscan0gaflidj */
    
/* start of struct st_rscan_from_rscan0gaflidj */
    union iodefine_reg32_t  GAFLID3;                       /*  GAFLID3         */
    union iodefine_reg32_t  GAFLM3;                        /*  GAFLM3          */
    union iodefine_reg32_t  GAFLP03;                       /*  GAFLP03         */
    union iodefine_reg32_t  GAFLP13;                       /*  GAFLP13         */
/* end of struct st_rscan_from_rscan0gaflidj */
    
/* start of struct st_rscan_from_rscan0gaflidj */
    union iodefine_reg32_t  GAFLID4;                       /*  GAFLID4         */
    union iodefine_reg32_t  GAFLM4;                        /*  GAFLM4          */
    union iodefine_reg32_t  GAFLP04;                       /*  GAFLP04         */
    union iodefine_reg32_t  GAFLP14;                       /*  GAFLP14         */
/* end of struct st_rscan_from_rscan0gaflidj */
    
/* start of struct st_rscan_from_rscan0gaflidj */
    union iodefine_reg32_t  GAFLID5;                       /*  GAFLID5         */
    union iodefine_reg32_t  GAFLM5;                        /*  GAFLM5          */
    union iodefine_reg32_t  GAFLP05;                       /*  GAFLP05         */
    union iodefine_reg32_t  GAFLP15;                       /*  GAFLP15         */
/* end of struct st_rscan_from_rscan0gaflidj */
    
/* start of struct st_rscan_from_rscan0gaflidj */
    union iodefine_reg32_t  GAFLID6;                       /*  GAFLID6         */
    union iodefine_reg32_t  GAFLM6;                        /*  GAFLM6          */
    union iodefine_reg32_t  GAFLP06;                       /*  GAFLP06         */
    union iodefine_reg32_t  GAFLP16;                       /*  GAFLP16         */
/* end of struct st_rscan_from_rscan0gaflidj */
    
/* start of struct st_rscan_from_rscan0gaflidj */
    union iodefine_reg32_t  GAFLID7;                       /*  GAFLID7         */
    union iodefine_reg32_t  GAFLM7;                        /*  GAFLM7          */
    union iodefine_reg32_t  GAFLP07;                       /*  GAFLP07         */
    union iodefine_reg32_t  GAFLP17;                       /*  GAFLP17         */
/* end of struct st_rscan_from_rscan0gaflidj */
    
/* start of struct st_rscan_from_rscan0gaflidj */
    union iodefine_reg32_t  GAFLID8;                       /*  GAFLID8         */
    union iodefine_reg32_t  GAFLM8;                        /*  GAFLM8          */
    union iodefine_reg32_t  GAFLP08;                       /*  GAFLP08         */
    union iodefine_reg32_t  GAFLP18;                       /*  GAFLP18         */
/* end of struct st_rscan_from_rscan0gaflidj */
    
/* start of struct st_rscan_from_rscan0gaflidj */
    union iodefine_reg32_t  GAFLID9;                       /*  GAFLID9         */
    union iodefine_reg32_t  GAFLM9;                        /*  GAFLM9          */
    union iodefine_reg32_t  GAFLP09;                       /*  GAFLP09         */
    union iodefine_reg32_t  GAFLP19;                       /*  GAFLP19         */
/* end of struct st_rscan_from_rscan0gaflidj */
    
/* start of struct st_rscan_from_rscan0gaflidj */
    union iodefine_reg32_t  GAFLID10;                      /*  GAFLID10        */
    union iodefine_reg32_t  GAFLM10;                       /*  GAFLM10         */
    union iodefine_reg32_t  GAFLP010;                      /*  GAFLP010        */
    union iodefine_reg32_t  GAFLP110;                      /*  GAFLP110        */
/* end of struct st_rscan_from_rscan0gaflidj */
    
/* start of struct st_rscan_from_rscan0gaflidj */
    union iodefine_reg32_t  GAFLID11;                      /*  GAFLID11        */
    union iodefine_reg32_t  GAFLM11;                       /*  GAFLM11         */
    union iodefine_reg32_t  GAFLP011;                      /*  GAFLP011        */
    union iodefine_reg32_t  GAFLP111;                      /*  GAFLP111        */
/* end of struct st_rscan_from_rscan0gaflidj */
    
/* start of struct st_rscan_from_rscan0gaflidj */
    union iodefine_reg32_t  GAFLID12;                      /*  GAFLID12        */
    union iodefine_reg32_t  GAFLM12;                       /*  GAFLM12         */
    union iodefine_reg32_t  GAFLP012;                      /*  GAFLP012        */
    union iodefine_reg32_t  GAFLP112;                      /*  GAFLP112        */
/* end of struct st_rscan_from_rscan0gaflidj */
    
/* start of struct st_rscan_from_rscan0gaflidj */
    union iodefine_reg32_t  GAFLID13;                      /*  GAFLID13        */
    union iodefine_reg32_t  GAFLM13;                       /*  GAFLM13         */
    union iodefine_reg32_t  GAFLP013;                      /*  GAFLP013        */
    union iodefine_reg32_t  GAFLP113;                      /*  GAFLP113        */
/* end of struct st_rscan_from_rscan0gaflidj */
    
/* start of struct st_rscan_from_rscan0gaflidj */
    union iodefine_reg32_t  GAFLID14;                      /*  GAFLID14        */
    union iodefine_reg32_t  GAFLM14;                       /*  GAFLM14         */
    union iodefine_reg32_t  GAFLP014;                      /*  GAFLP014        */
    union iodefine_reg32_t  GAFLP114;                      /*  GAFLP114        */
/* end of struct st_rscan_from_rscan0gaflidj */
    
/* start of struct st_rscan_from_rscan0gaflidj */
    union iodefine_reg32_t  GAFLID15;                      /*  GAFLID15        */
    union iodefine_reg32_t  GAFLM15;                       /*  GAFLM15         */
    union iodefine_reg32_t  GAFLP015;                      /*  GAFLP015        */
    union iodefine_reg32_t  GAFLP115;                      /*  GAFLP115        */
/* end of struct st_rscan_from_rscan0gaflidj */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID0;                         /*  RMID0           */
    union iodefine_reg32_t  RMPTR0;                        /*  RMPTR0          */
    union iodefine_reg32_t  RMDF00;                        /*  RMDF00          */
    union iodefine_reg32_t  RMDF10;                        /*  RMDF10          */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID1;                         /*  RMID1           */
    union iodefine_reg32_t  RMPTR1;                        /*  RMPTR1          */
    union iodefine_reg32_t  RMDF01;                        /*  RMDF01          */
    union iodefine_reg32_t  RMDF11;                        /*  RMDF11          */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID2;                         /*  RMID2           */
    union iodefine_reg32_t  RMPTR2;                        /*  RMPTR2          */
    union iodefine_reg32_t  RMDF02;                        /*  RMDF02          */
    union iodefine_reg32_t  RMDF12;                        /*  RMDF12          */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID3;                         /*  RMID3           */
    union iodefine_reg32_t  RMPTR3;                        /*  RMPTR3          */
    union iodefine_reg32_t  RMDF03;                        /*  RMDF03          */
    union iodefine_reg32_t  RMDF13;                        /*  RMDF13          */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID4;                         /*  RMID4           */
    union iodefine_reg32_t  RMPTR4;                        /*  RMPTR4          */
    union iodefine_reg32_t  RMDF04;                        /*  RMDF04          */
    union iodefine_reg32_t  RMDF14;                        /*  RMDF14          */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID5;                         /*  RMID5           */
    union iodefine_reg32_t  RMPTR5;                        /*  RMPTR5          */
    union iodefine_reg32_t  RMDF05;                        /*  RMDF05          */
    union iodefine_reg32_t  RMDF15;                        /*  RMDF15          */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID6;                         /*  RMID6           */
    union iodefine_reg32_t  RMPTR6;                        /*  RMPTR6          */
    union iodefine_reg32_t  RMDF06;                        /*  RMDF06          */
    union iodefine_reg32_t  RMDF16;                        /*  RMDF16          */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID7;                         /*  RMID7           */
    union iodefine_reg32_t  RMPTR7;                        /*  RMPTR7          */
    union iodefine_reg32_t  RMDF07;                        /*  RMDF07          */
    union iodefine_reg32_t  RMDF17;                        /*  RMDF17          */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID8;                         /*  RMID8           */
    union iodefine_reg32_t  RMPTR8;                        /*  RMPTR8          */
    union iodefine_reg32_t  RMDF08;                        /*  RMDF08          */
    union iodefine_reg32_t  RMDF18;                        /*  RMDF18          */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID9;                         /*  RMID9           */
    union iodefine_reg32_t  RMPTR9;                        /*  RMPTR9          */
    union iodefine_reg32_t  RMDF09;                        /*  RMDF09          */
    union iodefine_reg32_t  RMDF19;                        /*  RMDF19          */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID10;                        /*  RMID10          */
    union iodefine_reg32_t  RMPTR10;                       /*  RMPTR10         */
    union iodefine_reg32_t  RMDF010;                       /*  RMDF010         */
    union iodefine_reg32_t  RMDF110;                       /*  RMDF110         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID11;                        /*  RMID11          */
    union iodefine_reg32_t  RMPTR11;                       /*  RMPTR11         */
    union iodefine_reg32_t  RMDF011;                       /*  RMDF011         */
    union iodefine_reg32_t  RMDF111;                       /*  RMDF111         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID12;                        /*  RMID12          */
    union iodefine_reg32_t  RMPTR12;                       /*  RMPTR12         */
    union iodefine_reg32_t  RMDF012;                       /*  RMDF012         */
    union iodefine_reg32_t  RMDF112;                       /*  RMDF112         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID13;                        /*  RMID13          */
    union iodefine_reg32_t  RMPTR13;                       /*  RMPTR13         */
    union iodefine_reg32_t  RMDF013;                       /*  RMDF013         */
    union iodefine_reg32_t  RMDF113;                       /*  RMDF113         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID14;                        /*  RMID14          */
    union iodefine_reg32_t  RMPTR14;                       /*  RMPTR14         */
    union iodefine_reg32_t  RMDF014;                       /*  RMDF014         */
    union iodefine_reg32_t  RMDF114;                       /*  RMDF114         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID15;                        /*  RMID15          */
    union iodefine_reg32_t  RMPTR15;                       /*  RMPTR15         */
    union iodefine_reg32_t  RMDF015;                       /*  RMDF015         */
    union iodefine_reg32_t  RMDF115;                       /*  RMDF115         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID16;                        /*  RMID16          */
    union iodefine_reg32_t  RMPTR16;                       /*  RMPTR16         */
    union iodefine_reg32_t  RMDF016;                       /*  RMDF016         */
    union iodefine_reg32_t  RMDF116;                       /*  RMDF116         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID17;                        /*  RMID17          */
    union iodefine_reg32_t  RMPTR17;                       /*  RMPTR17         */
    union iodefine_reg32_t  RMDF017;                       /*  RMDF017         */
    union iodefine_reg32_t  RMDF117;                       /*  RMDF117         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID18;                        /*  RMID18          */
    union iodefine_reg32_t  RMPTR18;                       /*  RMPTR18         */
    union iodefine_reg32_t  RMDF018;                       /*  RMDF018         */
    union iodefine_reg32_t  RMDF118;                       /*  RMDF118         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID19;                        /*  RMID19          */
    union iodefine_reg32_t  RMPTR19;                       /*  RMPTR19         */
    union iodefine_reg32_t  RMDF019;                       /*  RMDF019         */
    union iodefine_reg32_t  RMDF119;                       /*  RMDF119         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID20;                        /*  RMID20          */
    union iodefine_reg32_t  RMPTR20;                       /*  RMPTR20         */
    union iodefine_reg32_t  RMDF020;                       /*  RMDF020         */
    union iodefine_reg32_t  RMDF120;                       /*  RMDF120         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID21;                        /*  RMID21          */
    union iodefine_reg32_t  RMPTR21;                       /*  RMPTR21         */
    union iodefine_reg32_t  RMDF021;                       /*  RMDF021         */
    union iodefine_reg32_t  RMDF121;                       /*  RMDF121         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID22;                        /*  RMID22          */
    union iodefine_reg32_t  RMPTR22;                       /*  RMPTR22         */
    union iodefine_reg32_t  RMDF022;                       /*  RMDF022         */
    union iodefine_reg32_t  RMDF122;                       /*  RMDF122         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID23;                        /*  RMID23          */
    union iodefine_reg32_t  RMPTR23;                       /*  RMPTR23         */
    union iodefine_reg32_t  RMDF023;                       /*  RMDF023         */
    union iodefine_reg32_t  RMDF123;                       /*  RMDF123         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID24;                        /*  RMID24          */
    union iodefine_reg32_t  RMPTR24;                       /*  RMPTR24         */
    union iodefine_reg32_t  RMDF024;                       /*  RMDF024         */
    union iodefine_reg32_t  RMDF124;                       /*  RMDF124         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID25;                        /*  RMID25          */
    union iodefine_reg32_t  RMPTR25;                       /*  RMPTR25         */
    union iodefine_reg32_t  RMDF025;                       /*  RMDF025         */
    union iodefine_reg32_t  RMDF125;                       /*  RMDF125         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID26;                        /*  RMID26          */
    union iodefine_reg32_t  RMPTR26;                       /*  RMPTR26         */
    union iodefine_reg32_t  RMDF026;                       /*  RMDF026         */
    union iodefine_reg32_t  RMDF126;                       /*  RMDF126         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID27;                        /*  RMID27          */
    union iodefine_reg32_t  RMPTR27;                       /*  RMPTR27         */
    union iodefine_reg32_t  RMDF027;                       /*  RMDF027         */
    union iodefine_reg32_t  RMDF127;                       /*  RMDF127         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID28;                        /*  RMID28          */
    union iodefine_reg32_t  RMPTR28;                       /*  RMPTR28         */
    union iodefine_reg32_t  RMDF028;                       /*  RMDF028         */
    union iodefine_reg32_t  RMDF128;                       /*  RMDF128         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID29;                        /*  RMID29          */
    union iodefine_reg32_t  RMPTR29;                       /*  RMPTR29         */
    union iodefine_reg32_t  RMDF029;                       /*  RMDF029         */
    union iodefine_reg32_t  RMDF129;                       /*  RMDF129         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID30;                        /*  RMID30          */
    union iodefine_reg32_t  RMPTR30;                       /*  RMPTR30         */
    union iodefine_reg32_t  RMDF030;                       /*  RMDF030         */
    union iodefine_reg32_t  RMDF130;                       /*  RMDF130         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID31;                        /*  RMID31          */
    union iodefine_reg32_t  RMPTR31;                       /*  RMPTR31         */
    union iodefine_reg32_t  RMDF031;                       /*  RMDF031         */
    union iodefine_reg32_t  RMDF131;                       /*  RMDF131         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID32;                        /*  RMID32          */
    union iodefine_reg32_t  RMPTR32;                       /*  RMPTR32         */
    union iodefine_reg32_t  RMDF032;                       /*  RMDF032         */
    union iodefine_reg32_t  RMDF132;                       /*  RMDF132         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID33;                        /*  RMID33          */
    union iodefine_reg32_t  RMPTR33;                       /*  RMPTR33         */
    union iodefine_reg32_t  RMDF033;                       /*  RMDF033         */
    union iodefine_reg32_t  RMDF133;                       /*  RMDF133         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID34;                        /*  RMID34          */
    union iodefine_reg32_t  RMPTR34;                       /*  RMPTR34         */
    union iodefine_reg32_t  RMDF034;                       /*  RMDF034         */
    union iodefine_reg32_t  RMDF134;                       /*  RMDF134         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID35;                        /*  RMID35          */
    union iodefine_reg32_t  RMPTR35;                       /*  RMPTR35         */
    union iodefine_reg32_t  RMDF035;                       /*  RMDF035         */
    union iodefine_reg32_t  RMDF135;                       /*  RMDF135         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID36;                        /*  RMID36          */
    union iodefine_reg32_t  RMPTR36;                       /*  RMPTR36         */
    union iodefine_reg32_t  RMDF036;                       /*  RMDF036         */
    union iodefine_reg32_t  RMDF136;                       /*  RMDF136         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID37;                        /*  RMID37          */
    union iodefine_reg32_t  RMPTR37;                       /*  RMPTR37         */
    union iodefine_reg32_t  RMDF037;                       /*  RMDF037         */
    union iodefine_reg32_t  RMDF137;                       /*  RMDF137         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID38;                        /*  RMID38          */
    union iodefine_reg32_t  RMPTR38;                       /*  RMPTR38         */
    union iodefine_reg32_t  RMDF038;                       /*  RMDF038         */
    union iodefine_reg32_t  RMDF138;                       /*  RMDF138         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID39;                        /*  RMID39          */
    union iodefine_reg32_t  RMPTR39;                       /*  RMPTR39         */
    union iodefine_reg32_t  RMDF039;                       /*  RMDF039         */
    union iodefine_reg32_t  RMDF139;                       /*  RMDF139         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID40;                        /*  RMID40          */
    union iodefine_reg32_t  RMPTR40;                       /*  RMPTR40         */
    union iodefine_reg32_t  RMDF040;                       /*  RMDF040         */
    union iodefine_reg32_t  RMDF140;                       /*  RMDF140         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID41;                        /*  RMID41          */
    union iodefine_reg32_t  RMPTR41;                       /*  RMPTR41         */
    union iodefine_reg32_t  RMDF041;                       /*  RMDF041         */
    union iodefine_reg32_t  RMDF141;                       /*  RMDF141         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID42;                        /*  RMID42          */
    union iodefine_reg32_t  RMPTR42;                       /*  RMPTR42         */
    union iodefine_reg32_t  RMDF042;                       /*  RMDF042         */
    union iodefine_reg32_t  RMDF142;                       /*  RMDF142         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID43;                        /*  RMID43          */
    union iodefine_reg32_t  RMPTR43;                       /*  RMPTR43         */
    union iodefine_reg32_t  RMDF043;                       /*  RMDF043         */
    union iodefine_reg32_t  RMDF143;                       /*  RMDF143         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID44;                        /*  RMID44          */
    union iodefine_reg32_t  RMPTR44;                       /*  RMPTR44         */
    union iodefine_reg32_t  RMDF044;                       /*  RMDF044         */
    union iodefine_reg32_t  RMDF144;                       /*  RMDF144         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID45;                        /*  RMID45          */
    union iodefine_reg32_t  RMPTR45;                       /*  RMPTR45         */
    union iodefine_reg32_t  RMDF045;                       /*  RMDF045         */
    union iodefine_reg32_t  RMDF145;                       /*  RMDF145         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID46;                        /*  RMID46          */
    union iodefine_reg32_t  RMPTR46;                       /*  RMPTR46         */
    union iodefine_reg32_t  RMDF046;                       /*  RMDF046         */
    union iodefine_reg32_t  RMDF146;                       /*  RMDF146         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID47;                        /*  RMID47          */
    union iodefine_reg32_t  RMPTR47;                       /*  RMPTR47         */
    union iodefine_reg32_t  RMDF047;                       /*  RMDF047         */
    union iodefine_reg32_t  RMDF147;                       /*  RMDF147         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID48;                        /*  RMID48          */
    union iodefine_reg32_t  RMPTR48;                       /*  RMPTR48         */
    union iodefine_reg32_t  RMDF048;                       /*  RMDF048         */
    union iodefine_reg32_t  RMDF148;                       /*  RMDF148         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID49;                        /*  RMID49          */
    union iodefine_reg32_t  RMPTR49;                       /*  RMPTR49         */
    union iodefine_reg32_t  RMDF049;                       /*  RMDF049         */
    union iodefine_reg32_t  RMDF149;                       /*  RMDF149         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID50;                        /*  RMID50          */
    union iodefine_reg32_t  RMPTR50;                       /*  RMPTR50         */
    union iodefine_reg32_t  RMDF050;                       /*  RMDF050         */
    union iodefine_reg32_t  RMDF150;                       /*  RMDF150         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID51;                        /*  RMID51          */
    union iodefine_reg32_t  RMPTR51;                       /*  RMPTR51         */
    union iodefine_reg32_t  RMDF051;                       /*  RMDF051         */
    union iodefine_reg32_t  RMDF151;                       /*  RMDF151         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID52;                        /*  RMID52          */
    union iodefine_reg32_t  RMPTR52;                       /*  RMPTR52         */
    union iodefine_reg32_t  RMDF052;                       /*  RMDF052         */
    union iodefine_reg32_t  RMDF152;                       /*  RMDF152         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID53;                        /*  RMID53          */
    union iodefine_reg32_t  RMPTR53;                       /*  RMPTR53         */
    union iodefine_reg32_t  RMDF053;                       /*  RMDF053         */
    union iodefine_reg32_t  RMDF153;                       /*  RMDF153         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID54;                        /*  RMID54          */
    union iodefine_reg32_t  RMPTR54;                       /*  RMPTR54         */
    union iodefine_reg32_t  RMDF054;                       /*  RMDF054         */
    union iodefine_reg32_t  RMDF154;                       /*  RMDF154         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID55;                        /*  RMID55          */
    union iodefine_reg32_t  RMPTR55;                       /*  RMPTR55         */
    union iodefine_reg32_t  RMDF055;                       /*  RMDF055         */
    union iodefine_reg32_t  RMDF155;                       /*  RMDF155         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID56;                        /*  RMID56          */
    union iodefine_reg32_t  RMPTR56;                       /*  RMPTR56         */
    union iodefine_reg32_t  RMDF056;                       /*  RMDF056         */
    union iodefine_reg32_t  RMDF156;                       /*  RMDF156         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID57;                        /*  RMID57          */
    union iodefine_reg32_t  RMPTR57;                       /*  RMPTR57         */
    union iodefine_reg32_t  RMDF057;                       /*  RMDF057         */
    union iodefine_reg32_t  RMDF157;                       /*  RMDF157         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID58;                        /*  RMID58          */
    union iodefine_reg32_t  RMPTR58;                       /*  RMPTR58         */
    union iodefine_reg32_t  RMDF058;                       /*  RMDF058         */
    union iodefine_reg32_t  RMDF158;                       /*  RMDF158         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID59;                        /*  RMID59          */
    union iodefine_reg32_t  RMPTR59;                       /*  RMPTR59         */
    union iodefine_reg32_t  RMDF059;                       /*  RMDF059         */
    union iodefine_reg32_t  RMDF159;                       /*  RMDF159         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID60;                        /*  RMID60          */
    union iodefine_reg32_t  RMPTR60;                       /*  RMPTR60         */
    union iodefine_reg32_t  RMDF060;                       /*  RMDF060         */
    union iodefine_reg32_t  RMDF160;                       /*  RMDF160         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID61;                        /*  RMID61          */
    union iodefine_reg32_t  RMPTR61;                       /*  RMPTR61         */
    union iodefine_reg32_t  RMDF061;                       /*  RMDF061         */
    union iodefine_reg32_t  RMDF161;                       /*  RMDF161         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID62;                        /*  RMID62          */
    union iodefine_reg32_t  RMPTR62;                       /*  RMPTR62         */
    union iodefine_reg32_t  RMDF062;                       /*  RMDF062         */
    union iodefine_reg32_t  RMDF162;                       /*  RMDF162         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID63;                        /*  RMID63          */
    union iodefine_reg32_t  RMPTR63;                       /*  RMPTR63         */
    union iodefine_reg32_t  RMDF063;                       /*  RMDF063         */
    union iodefine_reg32_t  RMDF163;                       /*  RMDF163         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID64;                        /*  RMID64          */
    union iodefine_reg32_t  RMPTR64;                       /*  RMPTR64         */
    union iodefine_reg32_t  RMDF064;                       /*  RMDF064         */
    union iodefine_reg32_t  RMDF164;                       /*  RMDF164         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID65;                        /*  RMID65          */
    union iodefine_reg32_t  RMPTR65;                       /*  RMPTR65         */
    union iodefine_reg32_t  RMDF065;                       /*  RMDF065         */
    union iodefine_reg32_t  RMDF165;                       /*  RMDF165         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID66;                        /*  RMID66          */
    union iodefine_reg32_t  RMPTR66;                       /*  RMPTR66         */
    union iodefine_reg32_t  RMDF066;                       /*  RMDF066         */
    union iodefine_reg32_t  RMDF166;                       /*  RMDF166         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID67;                        /*  RMID67          */
    union iodefine_reg32_t  RMPTR67;                       /*  RMPTR67         */
    union iodefine_reg32_t  RMDF067;                       /*  RMDF067         */
    union iodefine_reg32_t  RMDF167;                       /*  RMDF167         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID68;                        /*  RMID68          */
    union iodefine_reg32_t  RMPTR68;                       /*  RMPTR68         */
    union iodefine_reg32_t  RMDF068;                       /*  RMDF068         */
    union iodefine_reg32_t  RMDF168;                       /*  RMDF168         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID69;                        /*  RMID69          */
    union iodefine_reg32_t  RMPTR69;                       /*  RMPTR69         */
    union iodefine_reg32_t  RMDF069;                       /*  RMDF069         */
    union iodefine_reg32_t  RMDF169;                       /*  RMDF169         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID70;                        /*  RMID70          */
    union iodefine_reg32_t  RMPTR70;                       /*  RMPTR70         */
    union iodefine_reg32_t  RMDF070;                       /*  RMDF070         */
    union iodefine_reg32_t  RMDF170;                       /*  RMDF170         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID71;                        /*  RMID71          */
    union iodefine_reg32_t  RMPTR71;                       /*  RMPTR71         */
    union iodefine_reg32_t  RMDF071;                       /*  RMDF071         */
    union iodefine_reg32_t  RMDF171;                       /*  RMDF171         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID72;                        /*  RMID72          */
    union iodefine_reg32_t  RMPTR72;                       /*  RMPTR72         */
    union iodefine_reg32_t  RMDF072;                       /*  RMDF072         */
    union iodefine_reg32_t  RMDF172;                       /*  RMDF172         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID73;                        /*  RMID73          */
    union iodefine_reg32_t  RMPTR73;                       /*  RMPTR73         */
    union iodefine_reg32_t  RMDF073;                       /*  RMDF073         */
    union iodefine_reg32_t  RMDF173;                       /*  RMDF173         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID74;                        /*  RMID74          */
    union iodefine_reg32_t  RMPTR74;                       /*  RMPTR74         */
    union iodefine_reg32_t  RMDF074;                       /*  RMDF074         */
    union iodefine_reg32_t  RMDF174;                       /*  RMDF174         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID75;                        /*  RMID75          */
    union iodefine_reg32_t  RMPTR75;                       /*  RMPTR75         */
    union iodefine_reg32_t  RMDF075;                       /*  RMDF075         */
    union iodefine_reg32_t  RMDF175;                       /*  RMDF175         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID76;                        /*  RMID76          */
    union iodefine_reg32_t  RMPTR76;                       /*  RMPTR76         */
    union iodefine_reg32_t  RMDF076;                       /*  RMDF076         */
    union iodefine_reg32_t  RMDF176;                       /*  RMDF176         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID77;                        /*  RMID77          */
    union iodefine_reg32_t  RMPTR77;                       /*  RMPTR77         */
    union iodefine_reg32_t  RMDF077;                       /*  RMDF077         */
    union iodefine_reg32_t  RMDF177;                       /*  RMDF177         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID78;                        /*  RMID78          */
    union iodefine_reg32_t  RMPTR78;                       /*  RMPTR78         */
    union iodefine_reg32_t  RMDF078;                       /*  RMDF078         */
    union iodefine_reg32_t  RMDF178;                       /*  RMDF178         */
/* end of struct st_rscan_from_rscan0rmidp */
    
/* start of struct st_rscan_from_rscan0rmidp */
    union iodefine_reg32_t  RMID79;                        /*  RMID79          */
    union iodefine_reg32_t  RMPTR79;                       /*  RMPTR79         */
    union iodefine_reg32_t  RMDF079;                       /*  RMDF079         */
    union iodefine_reg32_t  RMDF179;                       /*  RMDF179         */
/* end of struct st_rscan_from_rscan0rmidp */
    
    volatile uint8_t   dummy179[768];                          /*                  */
    
/* start of struct st_rscan_from_rscan0rfidm */
    union iodefine_reg32_t  RFID0;                         /*  RFID0           */
    union iodefine_reg32_t  RFPTR0;                        /*  RFPTR0          */
    union iodefine_reg32_t  RFDF00;                        /*  RFDF00          */
    union iodefine_reg32_t  RFDF10;                        /*  RFDF10          */
/* end of struct st_rscan_from_rscan0rfidm */
    
/* start of struct st_rscan_from_rscan0rfidm */
    union iodefine_reg32_t  RFID1;                         /*  RFID1           */
    union iodefine_reg32_t  RFPTR1;                        /*  RFPTR1          */
    union iodefine_reg32_t  RFDF01;                        /*  RFDF01          */
    union iodefine_reg32_t  RFDF11;                        /*  RFDF11          */
/* end of struct st_rscan_from_rscan0rfidm */
    
/* start of struct st_rscan_from_rscan0rfidm */
    union iodefine_reg32_t  RFID2;                         /*  RFID2           */
    union iodefine_reg32_t  RFPTR2;                        /*  RFPTR2          */
    union iodefine_reg32_t  RFDF02;                        /*  RFDF02          */
    union iodefine_reg32_t  RFDF12;                        /*  RFDF12          */
/* end of struct st_rscan_from_rscan0rfidm */
    
/* start of struct st_rscan_from_rscan0rfidm */
    union iodefine_reg32_t  RFID3;                         /*  RFID3           */
    union iodefine_reg32_t  RFPTR3;                        /*  RFPTR3          */
    union iodefine_reg32_t  RFDF03;                        /*  RFDF03          */
    union iodefine_reg32_t  RFDF13;                        /*  RFDF13          */
/* end of struct st_rscan_from_rscan0rfidm */
    
/* start of struct st_rscan_from_rscan0rfidm */
    union iodefine_reg32_t  RFID4;                         /*  RFID4           */
    union iodefine_reg32_t  RFPTR4;                        /*  RFPTR4          */
    union iodefine_reg32_t  RFDF04;                        /*  RFDF04          */
    union iodefine_reg32_t  RFDF14;                        /*  RFDF14          */
/* end of struct st_rscan_from_rscan0rfidm */
    
/* start of struct st_rscan_from_rscan0rfidm */
    union iodefine_reg32_t  RFID5;                         /*  RFID5           */
    union iodefine_reg32_t  RFPTR5;                        /*  RFPTR5          */
    union iodefine_reg32_t  RFDF05;                        /*  RFDF05          */
    union iodefine_reg32_t  RFDF15;                        /*  RFDF15          */
/* end of struct st_rscan_from_rscan0rfidm */
    
/* start of struct st_rscan_from_rscan0rfidm */
    union iodefine_reg32_t  RFID6;                         /*  RFID6           */
    union iodefine_reg32_t  RFPTR6;                        /*  RFPTR6          */
    union iodefine_reg32_t  RFDF06;                        /*  RFDF06          */
    union iodefine_reg32_t  RFDF16;                        /*  RFDF16          */
/* end of struct st_rscan_from_rscan0rfidm */
    
/* start of struct st_rscan_from_rscan0rfidm */
    union iodefine_reg32_t  RFID7;                         /*  RFID7           */
    union iodefine_reg32_t  RFPTR7;                        /*  RFPTR7          */
    union iodefine_reg32_t  RFDF07;                        /*  RFDF07          */
    union iodefine_reg32_t  RFDF17;                        /*  RFDF17          */
/* end of struct st_rscan_from_rscan0rfidm */
    
/* start of struct st_rscan_from_rscan0cfidm */
    union iodefine_reg32_t  CFID0;                         /*  CFID0           */
    union iodefine_reg32_t  CFPTR0;                        /*  CFPTR0          */
    union iodefine_reg32_t  CFDF00;                        /*  CFDF00          */
    union iodefine_reg32_t  CFDF10;                        /*  CFDF10          */
/* end of struct st_rscan_from_rscan0cfidm */
    
/* start of struct st_rscan_from_rscan0cfidm */
    union iodefine_reg32_t  CFID1;                         /*  CFID1           */
    union iodefine_reg32_t  CFPTR1;                        /*  CFPTR1          */
    union iodefine_reg32_t  CFDF01;                        /*  CFDF01          */
    union iodefine_reg32_t  CFDF11;                        /*  CFDF11          */
/* end of struct st_rscan_from_rscan0cfidm */
    
/* start of struct st_rscan_from_rscan0cfidm */
    union iodefine_reg32_t  CFID2;                         /*  CFID2           */
    union iodefine_reg32_t  CFPTR2;                        /*  CFPTR2          */
    union iodefine_reg32_t  CFDF02;                        /*  CFDF02          */
    union iodefine_reg32_t  CFDF12;                        /*  CFDF12          */
/* end of struct st_rscan_from_rscan0cfidm */
    
/* start of struct st_rscan_from_rscan0cfidm */
    union iodefine_reg32_t  CFID3;                         /*  CFID3           */
    union iodefine_reg32_t  CFPTR3;                        /*  CFPTR3          */
    union iodefine_reg32_t  CFDF03;                        /*  CFDF03          */
    union iodefine_reg32_t  CFDF13;                        /*  CFDF13          */
/* end of struct st_rscan_from_rscan0cfidm */
    
/* start of struct st_rscan_from_rscan0cfidm */
    union iodefine_reg32_t  CFID4;                         /*  CFID4           */
    union iodefine_reg32_t  CFPTR4;                        /*  CFPTR4          */
    union iodefine_reg32_t  CFDF04;                        /*  CFDF04          */
    union iodefine_reg32_t  CFDF14;                        /*  CFDF14          */
/* end of struct st_rscan_from_rscan0cfidm */
    
/* start of struct st_rscan_from_rscan0cfidm */
    union iodefine_reg32_t  CFID5;                         /*  CFID5           */
    union iodefine_reg32_t  CFPTR5;                        /*  CFPTR5          */
    union iodefine_reg32_t  CFDF05;                        /*  CFDF05          */
    union iodefine_reg32_t  CFDF15;                        /*  CFDF15          */
/* end of struct st_rscan_from_rscan0cfidm */
    
/* start of struct st_rscan_from_rscan0cfidm */
    union iodefine_reg32_t  CFID6;                         /*  CFID6           */
    union iodefine_reg32_t  CFPTR6;                        /*  CFPTR6          */
    union iodefine_reg32_t  CFDF06;                        /*  CFDF06          */
    union iodefine_reg32_t  CFDF16;                        /*  CFDF16          */
/* end of struct st_rscan_from_rscan0cfidm */
    
/* start of struct st_rscan_from_rscan0cfidm */
    union iodefine_reg32_t  CFID7;                         /*  CFID7           */
    union iodefine_reg32_t  CFPTR7;                        /*  CFPTR7          */
    union iodefine_reg32_t  CFDF07;                        /*  CFDF07          */
    union iodefine_reg32_t  CFDF17;                        /*  CFDF17          */
/* end of struct st_rscan_from_rscan0cfidm */
    
/* start of struct st_rscan_from_rscan0cfidm */
    union iodefine_reg32_t  CFID8;                         /*  CFID8           */
    union iodefine_reg32_t  CFPTR8;                        /*  CFPTR8          */
    union iodefine_reg32_t  CFDF08;                        /*  CFDF08          */
    union iodefine_reg32_t  CFDF18;                        /*  CFDF18          */
/* end of struct st_rscan_from_rscan0cfidm */
    
/* start of struct st_rscan_from_rscan0cfidm */
    union iodefine_reg32_t  CFID9;                         /*  CFID9           */
    union iodefine_reg32_t  CFPTR9;                        /*  CFPTR9          */
    union iodefine_reg32_t  CFDF09;                        /*  CFDF09          */
    union iodefine_reg32_t  CFDF19;                        /*  CFDF19          */
/* end of struct st_rscan_from_rscan0cfidm */
    
/* start of struct st_rscan_from_rscan0cfidm */
    union iodefine_reg32_t  CFID10;                        /*  CFID10          */
    union iodefine_reg32_t  CFPTR10;                       /*  CFPTR10         */
    union iodefine_reg32_t  CFDF010;                       /*  CFDF010         */
    union iodefine_reg32_t  CFDF110;                       /*  CFDF110         */
/* end of struct st_rscan_from_rscan0cfidm */
    
/* start of struct st_rscan_from_rscan0cfidm */
    union iodefine_reg32_t  CFID11;                        /*  CFID11          */
    union iodefine_reg32_t  CFPTR11;                       /*  CFPTR11         */
    union iodefine_reg32_t  CFDF011;                       /*  CFDF011         */
    union iodefine_reg32_t  CFDF111;                       /*  CFDF111         */
/* end of struct st_rscan_from_rscan0cfidm */
    
/* start of struct st_rscan_from_rscan0cfidm */
    union iodefine_reg32_t  CFID12;                        /*  CFID12          */
    union iodefine_reg32_t  CFPTR12;                       /*  CFPTR12         */
    union iodefine_reg32_t  CFDF012;                       /*  CFDF012         */
    union iodefine_reg32_t  CFDF112;                       /*  CFDF112         */
/* end of struct st_rscan_from_rscan0cfidm */
    
/* start of struct st_rscan_from_rscan0cfidm */
    union iodefine_reg32_t  CFID13;                        /*  CFID13          */
    union iodefine_reg32_t  CFPTR13;                       /*  CFPTR13         */
    union iodefine_reg32_t  CFDF013;                       /*  CFDF013         */
    union iodefine_reg32_t  CFDF113;                       /*  CFDF113         */
/* end of struct st_rscan_from_rscan0cfidm */
    
/* start of struct st_rscan_from_rscan0cfidm */
    union iodefine_reg32_t  CFID14;                        /*  CFID14          */
    union iodefine_reg32_t  CFPTR14;                       /*  CFPTR14         */
    union iodefine_reg32_t  CFDF014;                       /*  CFDF014         */
    union iodefine_reg32_t  CFDF114;                       /*  CFDF114         */
/* end of struct st_rscan_from_rscan0cfidm */
    
    volatile uint8_t   dummy180[144];                          /*                  */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID0;                         /*  TMID0           */
    union iodefine_reg32_t  TMPTR0;                        /*  TMPTR0          */
    union iodefine_reg32_t  TMDF00;                        /*  TMDF00          */
    union iodefine_reg32_t  TMDF10;                        /*  TMDF10          */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID1;                         /*  TMID1           */
    union iodefine_reg32_t  TMPTR1;                        /*  TMPTR1          */
    union iodefine_reg32_t  TMDF01;                        /*  TMDF01          */
    union iodefine_reg32_t  TMDF11;                        /*  TMDF11          */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID2;                         /*  TMID2           */
    union iodefine_reg32_t  TMPTR2;                        /*  TMPTR2          */
    union iodefine_reg32_t  TMDF02;                        /*  TMDF02          */
    union iodefine_reg32_t  TMDF12;                        /*  TMDF12          */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID3;                         /*  TMID3           */
    union iodefine_reg32_t  TMPTR3;                        /*  TMPTR3          */
    union iodefine_reg32_t  TMDF03;                        /*  TMDF03          */
    union iodefine_reg32_t  TMDF13;                        /*  TMDF13          */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID4;                         /*  TMID4           */
    union iodefine_reg32_t  TMPTR4;                        /*  TMPTR4          */
    union iodefine_reg32_t  TMDF04;                        /*  TMDF04          */
    union iodefine_reg32_t  TMDF14;                        /*  TMDF14          */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID5;                         /*  TMID5           */
    union iodefine_reg32_t  TMPTR5;                        /*  TMPTR5          */
    union iodefine_reg32_t  TMDF05;                        /*  TMDF05          */
    union iodefine_reg32_t  TMDF15;                        /*  TMDF15          */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID6;                         /*  TMID6           */
    union iodefine_reg32_t  TMPTR6;                        /*  TMPTR6          */
    union iodefine_reg32_t  TMDF06;                        /*  TMDF06          */
    union iodefine_reg32_t  TMDF16;                        /*  TMDF16          */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID7;                         /*  TMID7           */
    union iodefine_reg32_t  TMPTR7;                        /*  TMPTR7          */
    union iodefine_reg32_t  TMDF07;                        /*  TMDF07          */
    union iodefine_reg32_t  TMDF17;                        /*  TMDF17          */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID8;                         /*  TMID8           */
    union iodefine_reg32_t  TMPTR8;                        /*  TMPTR8          */
    union iodefine_reg32_t  TMDF08;                        /*  TMDF08          */
    union iodefine_reg32_t  TMDF18;                        /*  TMDF18          */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID9;                         /*  TMID9           */
    union iodefine_reg32_t  TMPTR9;                        /*  TMPTR9          */
    union iodefine_reg32_t  TMDF09;                        /*  TMDF09          */
    union iodefine_reg32_t  TMDF19;                        /*  TMDF19          */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID10;                        /*  TMID10          */
    union iodefine_reg32_t  TMPTR10;                       /*  TMPTR10         */
    union iodefine_reg32_t  TMDF010;                       /*  TMDF010         */
    union iodefine_reg32_t  TMDF110;                       /*  TMDF110         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID11;                        /*  TMID11          */
    union iodefine_reg32_t  TMPTR11;                       /*  TMPTR11         */
    union iodefine_reg32_t  TMDF011;                       /*  TMDF011         */
    union iodefine_reg32_t  TMDF111;                       /*  TMDF111         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID12;                        /*  TMID12          */
    union iodefine_reg32_t  TMPTR12;                       /*  TMPTR12         */
    union iodefine_reg32_t  TMDF012;                       /*  TMDF012         */
    union iodefine_reg32_t  TMDF112;                       /*  TMDF112         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID13;                        /*  TMID13          */
    union iodefine_reg32_t  TMPTR13;                       /*  TMPTR13         */
    union iodefine_reg32_t  TMDF013;                       /*  TMDF013         */
    union iodefine_reg32_t  TMDF113;                       /*  TMDF113         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID14;                        /*  TMID14          */
    union iodefine_reg32_t  TMPTR14;                       /*  TMPTR14         */
    union iodefine_reg32_t  TMDF014;                       /*  TMDF014         */
    union iodefine_reg32_t  TMDF114;                       /*  TMDF114         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID15;                        /*  TMID15          */
    union iodefine_reg32_t  TMPTR15;                       /*  TMPTR15         */
    union iodefine_reg32_t  TMDF015;                       /*  TMDF015         */
    union iodefine_reg32_t  TMDF115;                       /*  TMDF115         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID16;                        /*  TMID16          */
    union iodefine_reg32_t  TMPTR16;                       /*  TMPTR16         */
    union iodefine_reg32_t  TMDF016;                       /*  TMDF016         */
    union iodefine_reg32_t  TMDF116;                       /*  TMDF116         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID17;                        /*  TMID17          */
    union iodefine_reg32_t  TMPTR17;                       /*  TMPTR17         */
    union iodefine_reg32_t  TMDF017;                       /*  TMDF017         */
    union iodefine_reg32_t  TMDF117;                       /*  TMDF117         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID18;                        /*  TMID18          */
    union iodefine_reg32_t  TMPTR18;                       /*  TMPTR18         */
    union iodefine_reg32_t  TMDF018;                       /*  TMDF018         */
    union iodefine_reg32_t  TMDF118;                       /*  TMDF118         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID19;                        /*  TMID19          */
    union iodefine_reg32_t  TMPTR19;                       /*  TMPTR19         */
    union iodefine_reg32_t  TMDF019;                       /*  TMDF019         */
    union iodefine_reg32_t  TMDF119;                       /*  TMDF119         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID20;                        /*  TMID20          */
    union iodefine_reg32_t  TMPTR20;                       /*  TMPTR20         */
    union iodefine_reg32_t  TMDF020;                       /*  TMDF020         */
    union iodefine_reg32_t  TMDF120;                       /*  TMDF120         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID21;                        /*  TMID21          */
    union iodefine_reg32_t  TMPTR21;                       /*  TMPTR21         */
    union iodefine_reg32_t  TMDF021;                       /*  TMDF021         */
    union iodefine_reg32_t  TMDF121;                       /*  TMDF121         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID22;                        /*  TMID22          */
    union iodefine_reg32_t  TMPTR22;                       /*  TMPTR22         */
    union iodefine_reg32_t  TMDF022;                       /*  TMDF022         */
    union iodefine_reg32_t  TMDF122;                       /*  TMDF122         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID23;                        /*  TMID23          */
    union iodefine_reg32_t  TMPTR23;                       /*  TMPTR23         */
    union iodefine_reg32_t  TMDF023;                       /*  TMDF023         */
    union iodefine_reg32_t  TMDF123;                       /*  TMDF123         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID24;                        /*  TMID24          */
    union iodefine_reg32_t  TMPTR24;                       /*  TMPTR24         */
    union iodefine_reg32_t  TMDF024;                       /*  TMDF024         */
    union iodefine_reg32_t  TMDF124;                       /*  TMDF124         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID25;                        /*  TMID25          */
    union iodefine_reg32_t  TMPTR25;                       /*  TMPTR25         */
    union iodefine_reg32_t  TMDF025;                       /*  TMDF025         */
    union iodefine_reg32_t  TMDF125;                       /*  TMDF125         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID26;                        /*  TMID26          */
    union iodefine_reg32_t  TMPTR26;                       /*  TMPTR26         */
    union iodefine_reg32_t  TMDF026;                       /*  TMDF026         */
    union iodefine_reg32_t  TMDF126;                       /*  TMDF126         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID27;                        /*  TMID27          */
    union iodefine_reg32_t  TMPTR27;                       /*  TMPTR27         */
    union iodefine_reg32_t  TMDF027;                       /*  TMDF027         */
    union iodefine_reg32_t  TMDF127;                       /*  TMDF127         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID28;                        /*  TMID28          */
    union iodefine_reg32_t  TMPTR28;                       /*  TMPTR28         */
    union iodefine_reg32_t  TMDF028;                       /*  TMDF028         */
    union iodefine_reg32_t  TMDF128;                       /*  TMDF128         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID29;                        /*  TMID29          */
    union iodefine_reg32_t  TMPTR29;                       /*  TMPTR29         */
    union iodefine_reg32_t  TMDF029;                       /*  TMDF029         */
    union iodefine_reg32_t  TMDF129;                       /*  TMDF129         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID30;                        /*  TMID30          */
    union iodefine_reg32_t  TMPTR30;                       /*  TMPTR30         */
    union iodefine_reg32_t  TMDF030;                       /*  TMDF030         */
    union iodefine_reg32_t  TMDF130;                       /*  TMDF130         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID31;                        /*  TMID31          */
    union iodefine_reg32_t  TMPTR31;                       /*  TMPTR31         */
    union iodefine_reg32_t  TMDF031;                       /*  TMDF031         */
    union iodefine_reg32_t  TMDF131;                       /*  TMDF131         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID32;                        /*  TMID32          */
    union iodefine_reg32_t  TMPTR32;                       /*  TMPTR32         */
    union iodefine_reg32_t  TMDF032;                       /*  TMDF032         */
    union iodefine_reg32_t  TMDF132;                       /*  TMDF132         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID33;                        /*  TMID33          */
    union iodefine_reg32_t  TMPTR33;                       /*  TMPTR33         */
    union iodefine_reg32_t  TMDF033;                       /*  TMDF033         */
    union iodefine_reg32_t  TMDF133;                       /*  TMDF133         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID34;                        /*  TMID34          */
    union iodefine_reg32_t  TMPTR34;                       /*  TMPTR34         */
    union iodefine_reg32_t  TMDF034;                       /*  TMDF034         */
    union iodefine_reg32_t  TMDF134;                       /*  TMDF134         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID35;                        /*  TMID35          */
    union iodefine_reg32_t  TMPTR35;                       /*  TMPTR35         */
    union iodefine_reg32_t  TMDF035;                       /*  TMDF035         */
    union iodefine_reg32_t  TMDF135;                       /*  TMDF135         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID36;                        /*  TMID36          */
    union iodefine_reg32_t  TMPTR36;                       /*  TMPTR36         */
    union iodefine_reg32_t  TMDF036;                       /*  TMDF036         */
    union iodefine_reg32_t  TMDF136;                       /*  TMDF136         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID37;                        /*  TMID37          */
    union iodefine_reg32_t  TMPTR37;                       /*  TMPTR37         */
    union iodefine_reg32_t  TMDF037;                       /*  TMDF037         */
    union iodefine_reg32_t  TMDF137;                       /*  TMDF137         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID38;                        /*  TMID38          */
    union iodefine_reg32_t  TMPTR38;                       /*  TMPTR38         */
    union iodefine_reg32_t  TMDF038;                       /*  TMDF038         */
    union iodefine_reg32_t  TMDF138;                       /*  TMDF138         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID39;                        /*  TMID39          */
    union iodefine_reg32_t  TMPTR39;                       /*  TMPTR39         */
    union iodefine_reg32_t  TMDF039;                       /*  TMDF039         */
    union iodefine_reg32_t  TMDF139;                       /*  TMDF139         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID40;                        /*  TMID40          */
    union iodefine_reg32_t  TMPTR40;                       /*  TMPTR40         */
    union iodefine_reg32_t  TMDF040;                       /*  TMDF040         */
    union iodefine_reg32_t  TMDF140;                       /*  TMDF140         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID41;                        /*  TMID41          */
    union iodefine_reg32_t  TMPTR41;                       /*  TMPTR41         */
    union iodefine_reg32_t  TMDF041;                       /*  TMDF041         */
    union iodefine_reg32_t  TMDF141;                       /*  TMDF141         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID42;                        /*  TMID42          */
    union iodefine_reg32_t  TMPTR42;                       /*  TMPTR42         */
    union iodefine_reg32_t  TMDF042;                       /*  TMDF042         */
    union iodefine_reg32_t  TMDF142;                       /*  TMDF142         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID43;                        /*  TMID43          */
    union iodefine_reg32_t  TMPTR43;                       /*  TMPTR43         */
    union iodefine_reg32_t  TMDF043;                       /*  TMDF043         */
    union iodefine_reg32_t  TMDF143;                       /*  TMDF143         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID44;                        /*  TMID44          */
    union iodefine_reg32_t  TMPTR44;                       /*  TMPTR44         */
    union iodefine_reg32_t  TMDF044;                       /*  TMDF044         */
    union iodefine_reg32_t  TMDF144;                       /*  TMDF144         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID45;                        /*  TMID45          */
    union iodefine_reg32_t  TMPTR45;                       /*  TMPTR45         */
    union iodefine_reg32_t  TMDF045;                       /*  TMDF045         */
    union iodefine_reg32_t  TMDF145;                       /*  TMDF145         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID46;                        /*  TMID46          */
    union iodefine_reg32_t  TMPTR46;                       /*  TMPTR46         */
    union iodefine_reg32_t  TMDF046;                       /*  TMDF046         */
    union iodefine_reg32_t  TMDF146;                       /*  TMDF146         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID47;                        /*  TMID47          */
    union iodefine_reg32_t  TMPTR47;                       /*  TMPTR47         */
    union iodefine_reg32_t  TMDF047;                       /*  TMDF047         */
    union iodefine_reg32_t  TMDF147;                       /*  TMDF147         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID48;                        /*  TMID48          */
    union iodefine_reg32_t  TMPTR48;                       /*  TMPTR48         */
    union iodefine_reg32_t  TMDF048;                       /*  TMDF048         */
    union iodefine_reg32_t  TMDF148;                       /*  TMDF148         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID49;                        /*  TMID49          */
    union iodefine_reg32_t  TMPTR49;                       /*  TMPTR49         */
    union iodefine_reg32_t  TMDF049;                       /*  TMDF049         */
    union iodefine_reg32_t  TMDF149;                       /*  TMDF149         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID50;                        /*  TMID50          */
    union iodefine_reg32_t  TMPTR50;                       /*  TMPTR50         */
    union iodefine_reg32_t  TMDF050;                       /*  TMDF050         */
    union iodefine_reg32_t  TMDF150;                       /*  TMDF150         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID51;                        /*  TMID51          */
    union iodefine_reg32_t  TMPTR51;                       /*  TMPTR51         */
    union iodefine_reg32_t  TMDF051;                       /*  TMDF051         */
    union iodefine_reg32_t  TMDF151;                       /*  TMDF151         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID52;                        /*  TMID52          */
    union iodefine_reg32_t  TMPTR52;                       /*  TMPTR52         */
    union iodefine_reg32_t  TMDF052;                       /*  TMDF052         */
    union iodefine_reg32_t  TMDF152;                       /*  TMDF152         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID53;                        /*  TMID53          */
    union iodefine_reg32_t  TMPTR53;                       /*  TMPTR53         */
    union iodefine_reg32_t  TMDF053;                       /*  TMDF053         */
    union iodefine_reg32_t  TMDF153;                       /*  TMDF153         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID54;                        /*  TMID54          */
    union iodefine_reg32_t  TMPTR54;                       /*  TMPTR54         */
    union iodefine_reg32_t  TMDF054;                       /*  TMDF054         */
    union iodefine_reg32_t  TMDF154;                       /*  TMDF154         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID55;                        /*  TMID55          */
    union iodefine_reg32_t  TMPTR55;                       /*  TMPTR55         */
    union iodefine_reg32_t  TMDF055;                       /*  TMDF055         */
    union iodefine_reg32_t  TMDF155;                       /*  TMDF155         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID56;                        /*  TMID56          */
    union iodefine_reg32_t  TMPTR56;                       /*  TMPTR56         */
    union iodefine_reg32_t  TMDF056;                       /*  TMDF056         */
    union iodefine_reg32_t  TMDF156;                       /*  TMDF156         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID57;                        /*  TMID57          */
    union iodefine_reg32_t  TMPTR57;                       /*  TMPTR57         */
    union iodefine_reg32_t  TMDF057;                       /*  TMDF057         */
    union iodefine_reg32_t  TMDF157;                       /*  TMDF157         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID58;                        /*  TMID58          */
    union iodefine_reg32_t  TMPTR58;                       /*  TMPTR58         */
    union iodefine_reg32_t  TMDF058;                       /*  TMDF058         */
    union iodefine_reg32_t  TMDF158;                       /*  TMDF158         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID59;                        /*  TMID59          */
    union iodefine_reg32_t  TMPTR59;                       /*  TMPTR59         */
    union iodefine_reg32_t  TMDF059;                       /*  TMDF059         */
    union iodefine_reg32_t  TMDF159;                       /*  TMDF159         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID60;                        /*  TMID60          */
    union iodefine_reg32_t  TMPTR60;                       /*  TMPTR60         */
    union iodefine_reg32_t  TMDF060;                       /*  TMDF060         */
    union iodefine_reg32_t  TMDF160;                       /*  TMDF160         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID61;                        /*  TMID61          */
    union iodefine_reg32_t  TMPTR61;                       /*  TMPTR61         */
    union iodefine_reg32_t  TMDF061;                       /*  TMDF061         */
    union iodefine_reg32_t  TMDF161;                       /*  TMDF161         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID62;                        /*  TMID62          */
    union iodefine_reg32_t  TMPTR62;                       /*  TMPTR62         */
    union iodefine_reg32_t  TMDF062;                       /*  TMDF062         */
    union iodefine_reg32_t  TMDF162;                       /*  TMDF162         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID63;                        /*  TMID63          */
    union iodefine_reg32_t  TMPTR63;                       /*  TMPTR63         */
    union iodefine_reg32_t  TMDF063;                       /*  TMDF063         */
    union iodefine_reg32_t  TMDF163;                       /*  TMDF163         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID64;                        /*  TMID64          */
    union iodefine_reg32_t  TMPTR64;                       /*  TMPTR64         */
    union iodefine_reg32_t  TMDF064;                       /*  TMDF064         */
    union iodefine_reg32_t  TMDF164;                       /*  TMDF164         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID65;                        /*  TMID65          */
    union iodefine_reg32_t  TMPTR65;                       /*  TMPTR65         */
    union iodefine_reg32_t  TMDF065;                       /*  TMDF065         */
    union iodefine_reg32_t  TMDF165;                       /*  TMDF165         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID66;                        /*  TMID66          */
    union iodefine_reg32_t  TMPTR66;                       /*  TMPTR66         */
    union iodefine_reg32_t  TMDF066;                       /*  TMDF066         */
    union iodefine_reg32_t  TMDF166;                       /*  TMDF166         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID67;                        /*  TMID67          */
    union iodefine_reg32_t  TMPTR67;                       /*  TMPTR67         */
    union iodefine_reg32_t  TMDF067;                       /*  TMDF067         */
    union iodefine_reg32_t  TMDF167;                       /*  TMDF167         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID68;                        /*  TMID68          */
    union iodefine_reg32_t  TMPTR68;                       /*  TMPTR68         */
    union iodefine_reg32_t  TMDF068;                       /*  TMDF068         */
    union iodefine_reg32_t  TMDF168;                       /*  TMDF168         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID69;                        /*  TMID69          */
    union iodefine_reg32_t  TMPTR69;                       /*  TMPTR69         */
    union iodefine_reg32_t  TMDF069;                       /*  TMDF069         */
    union iodefine_reg32_t  TMDF169;                       /*  TMDF169         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID70;                        /*  TMID70          */
    union iodefine_reg32_t  TMPTR70;                       /*  TMPTR70         */
    union iodefine_reg32_t  TMDF070;                       /*  TMDF070         */
    union iodefine_reg32_t  TMDF170;                       /*  TMDF170         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID71;                        /*  TMID71          */
    union iodefine_reg32_t  TMPTR71;                       /*  TMPTR71         */
    union iodefine_reg32_t  TMDF071;                       /*  TMDF071         */
    union iodefine_reg32_t  TMDF171;                       /*  TMDF171         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID72;                        /*  TMID72          */
    union iodefine_reg32_t  TMPTR72;                       /*  TMPTR72         */
    union iodefine_reg32_t  TMDF072;                       /*  TMDF072         */
    union iodefine_reg32_t  TMDF172;                       /*  TMDF172         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID73;                        /*  TMID73          */
    union iodefine_reg32_t  TMPTR73;                       /*  TMPTR73         */
    union iodefine_reg32_t  TMDF073;                       /*  TMDF073         */
    union iodefine_reg32_t  TMDF173;                       /*  TMDF173         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID74;                        /*  TMID74          */
    union iodefine_reg32_t  TMPTR74;                       /*  TMPTR74         */
    union iodefine_reg32_t  TMDF074;                       /*  TMDF074         */
    union iodefine_reg32_t  TMDF174;                       /*  TMDF174         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID75;                        /*  TMID75          */
    union iodefine_reg32_t  TMPTR75;                       /*  TMPTR75         */
    union iodefine_reg32_t  TMDF075;                       /*  TMDF075         */
    union iodefine_reg32_t  TMDF175;                       /*  TMDF175         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID76;                        /*  TMID76          */
    union iodefine_reg32_t  TMPTR76;                       /*  TMPTR76         */
    union iodefine_reg32_t  TMDF076;                       /*  TMDF076         */
    union iodefine_reg32_t  TMDF176;                       /*  TMDF176         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID77;                        /*  TMID77          */
    union iodefine_reg32_t  TMPTR77;                       /*  TMPTR77         */
    union iodefine_reg32_t  TMDF077;                       /*  TMDF077         */
    union iodefine_reg32_t  TMDF177;                       /*  TMDF177         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID78;                        /*  TMID78          */
    union iodefine_reg32_t  TMPTR78;                       /*  TMPTR78         */
    union iodefine_reg32_t  TMDF078;                       /*  TMDF078         */
    union iodefine_reg32_t  TMDF178;                       /*  TMDF178         */
/* end of struct st_rscan_from_rscan0tmidp */
    
/* start of struct st_rscan_from_rscan0tmidp */
    union iodefine_reg32_t  TMID79;                        /*  TMID79          */
    union iodefine_reg32_t  TMPTR79;                       /*  TMPTR79         */
    union iodefine_reg32_t  TMDF079;                       /*  TMDF079         */
    union iodefine_reg32_t  TMDF179;                       /*  TMDF179         */
/* end of struct st_rscan_from_rscan0tmidp */
    
    volatile uint8_t   dummy181[768];                          /*                  */
#define RSCAN0_THLACC0_COUNT 5
    union iodefine_reg32_t  THLACC0;                       /*  THLACC0         */
    union iodefine_reg32_t  THLACC1;                       /*  THLACC1         */
    union iodefine_reg32_t  THLACC2;                       /*  THLACC2         */
    union iodefine_reg32_t  THLACC3;                       /*  THLACC3         */
    union iodefine_reg32_t  THLACC4;                       /*  THLACC4         */
    
};


struct st_rscan_from_rscan0cncfg
{
    union iodefine_reg32_t  CnCFG;                         /*  CnCFG           */
    union iodefine_reg32_t  CnCTR;                         /*  CnCTR           */
    union iodefine_reg32_t  CnSTS;                         /*  CnSTS           */
    union iodefine_reg32_t  CnERFL;                        /*  CnERFL          */
};


struct st_rscan_from_rscan0gaflidj
{
    union iodefine_reg32_t  GAFLIDj;                       /*  GAFLIDj         */
    union iodefine_reg32_t  GAFLMj;                        /*  GAFLMj          */
    union iodefine_reg32_t  GAFLP0j;                       /*  GAFLP0j         */
    union iodefine_reg32_t  GAFLP1j;                       /*  GAFLP1j         */
};


struct st_rscan_from_rscan0rmidp
{
    union iodefine_reg32_t  RMIDp;                         /*  RMIDp           */
    union iodefine_reg32_t  RMPTRp;                        /*  RMPTRp          */
    union iodefine_reg32_t  RMDF0p;                        /*  RMDF0p          */
    union iodefine_reg32_t  RMDF1p;                        /*  RMDF1p          */
};


struct st_rscan_from_rscan0rfidm
{
    union iodefine_reg32_t  RFIDm;                         /*  RFIDm           */
    union iodefine_reg32_t  RFPTRm;                        /*  RFPTRm          */
    union iodefine_reg32_t  RFDF0m;                        /*  RFDF0m          */
    union iodefine_reg32_t  RFDF1m;                        /*  RFDF1m          */
};


struct st_rscan_from_rscan0tmidp
{
    union iodefine_reg32_t  TMIDp;                         /*  TMIDp           */
    union iodefine_reg32_t  TMPTRp;                        /*  TMPTRp          */
    union iodefine_reg32_t  TMDF0p;                        /*  TMDF0p          */
    union iodefine_reg32_t  TMDF1p;                        /*  TMDF1p          */
};


struct st_rscan_from_rscan0cfidm
{
    union iodefine_reg32_t  CFIDm;                         /*  CFIDm           */
    union iodefine_reg32_t  CFPTRm;                        /*  CFPTRm          */
    union iodefine_reg32_t  CFDF0m;                        /*  CFDF0m          */
    union iodefine_reg32_t  CFDF1m;                        /*  CFDF1m          */
};


#define RSCAN0  (*(struct st_rscan0  *)0xE803A000uL) /* RSCAN0 */


/* Start of channnel array defines of RSCAN0 */

/* Channnel array defines of RSCAN_FROM_RSCAN0CFIDm */
/*(Sample) value = RSCAN_FROM_RSCAN0CFIDm[ channel ]->CFIDm.UINT32; */
#define RSCAN_FROM_RSCAN0CFIDm_COUNT  15
#define RSCAN_FROM_RSCAN0CFIDm_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &RSCAN_FROM_RSCAN0CFID0, &RSCAN_FROM_RSCAN0CFID1, &RSCAN_FROM_RSCAN0CFID2, &RSCAN_FROM_RSCAN0CFID3, &RSCAN_FROM_RSCAN0CFID4, &RSCAN_FROM_RSCAN0CFID5, &RSCAN_FROM_RSCAN0CFID6, &RSCAN_FROM_RSCAN0CFID7, \
    &RSCAN_FROM_RSCAN0CFID8, &RSCAN_FROM_RSCAN0CFID9, &RSCAN_FROM_RSCAN0CFID10, &RSCAN_FROM_RSCAN0CFID11, &RSCAN_FROM_RSCAN0CFID12, &RSCAN_FROM_RSCAN0CFID13, &RSCAN_FROM_RSCAN0CFID14 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define RSCAN_FROM_RSCAN0CFID0 (*(struct st_rscan_from_rscan0cfidm *)&RSCAN0.CFID0) /* RSCAN_FROM_RSCAN0CFID0 */
#define RSCAN_FROM_RSCAN0CFID1 (*(struct st_rscan_from_rscan0cfidm *)&RSCAN0.CFID1) /* RSCAN_FROM_RSCAN0CFID1 */
#define RSCAN_FROM_RSCAN0CFID2 (*(struct st_rscan_from_rscan0cfidm *)&RSCAN0.CFID2) /* RSCAN_FROM_RSCAN0CFID2 */
#define RSCAN_FROM_RSCAN0CFID3 (*(struct st_rscan_from_rscan0cfidm *)&RSCAN0.CFID3) /* RSCAN_FROM_RSCAN0CFID3 */
#define RSCAN_FROM_RSCAN0CFID4 (*(struct st_rscan_from_rscan0cfidm *)&RSCAN0.CFID4) /* RSCAN_FROM_RSCAN0CFID4 */
#define RSCAN_FROM_RSCAN0CFID5 (*(struct st_rscan_from_rscan0cfidm *)&RSCAN0.CFID5) /* RSCAN_FROM_RSCAN0CFID5 */
#define RSCAN_FROM_RSCAN0CFID6 (*(struct st_rscan_from_rscan0cfidm *)&RSCAN0.CFID6) /* RSCAN_FROM_RSCAN0CFID6 */
#define RSCAN_FROM_RSCAN0CFID7 (*(struct st_rscan_from_rscan0cfidm *)&RSCAN0.CFID7) /* RSCAN_FROM_RSCAN0CFID7 */
#define RSCAN_FROM_RSCAN0CFID8 (*(struct st_rscan_from_rscan0cfidm *)&RSCAN0.CFID8) /* RSCAN_FROM_RSCAN0CFID8 */
#define RSCAN_FROM_RSCAN0CFID9 (*(struct st_rscan_from_rscan0cfidm *)&RSCAN0.CFID9) /* RSCAN_FROM_RSCAN0CFID9 */
#define RSCAN_FROM_RSCAN0CFID10 (*(struct st_rscan_from_rscan0cfidm *)&RSCAN0.CFID10) /* RSCAN_FROM_RSCAN0CFID10 */
#define RSCAN_FROM_RSCAN0CFID11 (*(struct st_rscan_from_rscan0cfidm *)&RSCAN0.CFID11) /* RSCAN_FROM_RSCAN0CFID11 */
#define RSCAN_FROM_RSCAN0CFID12 (*(struct st_rscan_from_rscan0cfidm *)&RSCAN0.CFID12) /* RSCAN_FROM_RSCAN0CFID12 */
#define RSCAN_FROM_RSCAN0CFID13 (*(struct st_rscan_from_rscan0cfidm *)&RSCAN0.CFID13) /* RSCAN_FROM_RSCAN0CFID13 */
#define RSCAN_FROM_RSCAN0CFID14 (*(struct st_rscan_from_rscan0cfidm *)&RSCAN0.CFID14) /* RSCAN_FROM_RSCAN0CFID14 */


/* Channnel array defines of RSCAN_FROM_RSCAN0TMIDp */
/*(Sample) value = RSCAN_FROM_RSCAN0TMIDp[ channel ]->TMIDp.UINT32; */
#define RSCAN_FROM_RSCAN0TMIDp_COUNT  80
#define RSCAN_FROM_RSCAN0TMIDp_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &RSCAN_FROM_RSCAN0TMID0, &RSCAN_FROM_RSCAN0TMID1, &RSCAN_FROM_RSCAN0TMID2, &RSCAN_FROM_RSCAN0TMID3, &RSCAN_FROM_RSCAN0TMID4, &RSCAN_FROM_RSCAN0TMID5, &RSCAN_FROM_RSCAN0TMID6, &RSCAN_FROM_RSCAN0TMID7, \
    &RSCAN_FROM_RSCAN0TMID8, &RSCAN_FROM_RSCAN0TMID9, &RSCAN_FROM_RSCAN0TMID10, &RSCAN_FROM_RSCAN0TMID11, &RSCAN_FROM_RSCAN0TMID12, &RSCAN_FROM_RSCAN0TMID13, &RSCAN_FROM_RSCAN0TMID14, &RSCAN_FROM_RSCAN0TMID15, \
    &RSCAN_FROM_RSCAN0TMID16, &RSCAN_FROM_RSCAN0TMID17, &RSCAN_FROM_RSCAN0TMID18, &RSCAN_FROM_RSCAN0TMID19, &RSCAN_FROM_RSCAN0TMID20, &RSCAN_FROM_RSCAN0TMID21, &RSCAN_FROM_RSCAN0TMID22, &RSCAN_FROM_RSCAN0TMID23, \
    &RSCAN_FROM_RSCAN0TMID24, &RSCAN_FROM_RSCAN0TMID25, &RSCAN_FROM_RSCAN0TMID26, &RSCAN_FROM_RSCAN0TMID27, &RSCAN_FROM_RSCAN0TMID28, &RSCAN_FROM_RSCAN0TMID29, &RSCAN_FROM_RSCAN0TMID30, &RSCAN_FROM_RSCAN0TMID31, \
    &RSCAN_FROM_RSCAN0TMID32, &RSCAN_FROM_RSCAN0TMID33, &RSCAN_FROM_RSCAN0TMID34, &RSCAN_FROM_RSCAN0TMID35, &RSCAN_FROM_RSCAN0TMID36, &RSCAN_FROM_RSCAN0TMID37, &RSCAN_FROM_RSCAN0TMID38, &RSCAN_FROM_RSCAN0TMID39, \
    &RSCAN_FROM_RSCAN0TMID40, &RSCAN_FROM_RSCAN0TMID41, &RSCAN_FROM_RSCAN0TMID42, &RSCAN_FROM_RSCAN0TMID43, &RSCAN_FROM_RSCAN0TMID44, &RSCAN_FROM_RSCAN0TMID45, &RSCAN_FROM_RSCAN0TMID46, &RSCAN_FROM_RSCAN0TMID47, \
    &RSCAN_FROM_RSCAN0TMID48, &RSCAN_FROM_RSCAN0TMID49, &RSCAN_FROM_RSCAN0TMID50, &RSCAN_FROM_RSCAN0TMID51, &RSCAN_FROM_RSCAN0TMID52, &RSCAN_FROM_RSCAN0TMID53, &RSCAN_FROM_RSCAN0TMID54, &RSCAN_FROM_RSCAN0TMID55, \
    &RSCAN_FROM_RSCAN0TMID56, &RSCAN_FROM_RSCAN0TMID57, &RSCAN_FROM_RSCAN0TMID58, &RSCAN_FROM_RSCAN0TMID59, &RSCAN_FROM_RSCAN0TMID60, &RSCAN_FROM_RSCAN0TMID61, &RSCAN_FROM_RSCAN0TMID62, &RSCAN_FROM_RSCAN0TMID63, \
    &RSCAN_FROM_RSCAN0TMID64, &RSCAN_FROM_RSCAN0TMID65, &RSCAN_FROM_RSCAN0TMID66, &RSCAN_FROM_RSCAN0TMID67, &RSCAN_FROM_RSCAN0TMID68, &RSCAN_FROM_RSCAN0TMID69, &RSCAN_FROM_RSCAN0TMID70, &RSCAN_FROM_RSCAN0TMID71, \
    &RSCAN_FROM_RSCAN0TMID72, &RSCAN_FROM_RSCAN0TMID73, &RSCAN_FROM_RSCAN0TMID74, &RSCAN_FROM_RSCAN0TMID75, &RSCAN_FROM_RSCAN0TMID76, &RSCAN_FROM_RSCAN0TMID77, &RSCAN_FROM_RSCAN0TMID78, &RSCAN_FROM_RSCAN0TMID79 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define RSCAN_FROM_RSCAN0TMID0 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID0) /* RSCAN_FROM_RSCAN0TMID0 */
#define RSCAN_FROM_RSCAN0TMID1 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID1) /* RSCAN_FROM_RSCAN0TMID1 */
#define RSCAN_FROM_RSCAN0TMID2 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID2) /* RSCAN_FROM_RSCAN0TMID2 */
#define RSCAN_FROM_RSCAN0TMID3 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID3) /* RSCAN_FROM_RSCAN0TMID3 */
#define RSCAN_FROM_RSCAN0TMID4 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID4) /* RSCAN_FROM_RSCAN0TMID4 */
#define RSCAN_FROM_RSCAN0TMID5 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID5) /* RSCAN_FROM_RSCAN0TMID5 */
#define RSCAN_FROM_RSCAN0TMID6 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID6) /* RSCAN_FROM_RSCAN0TMID6 */
#define RSCAN_FROM_RSCAN0TMID7 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID7) /* RSCAN_FROM_RSCAN0TMID7 */
#define RSCAN_FROM_RSCAN0TMID8 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID8) /* RSCAN_FROM_RSCAN0TMID8 */
#define RSCAN_FROM_RSCAN0TMID9 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID9) /* RSCAN_FROM_RSCAN0TMID9 */
#define RSCAN_FROM_RSCAN0TMID10 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID10) /* RSCAN_FROM_RSCAN0TMID10 */
#define RSCAN_FROM_RSCAN0TMID11 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID11) /* RSCAN_FROM_RSCAN0TMID11 */
#define RSCAN_FROM_RSCAN0TMID12 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID12) /* RSCAN_FROM_RSCAN0TMID12 */
#define RSCAN_FROM_RSCAN0TMID13 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID13) /* RSCAN_FROM_RSCAN0TMID13 */
#define RSCAN_FROM_RSCAN0TMID14 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID14) /* RSCAN_FROM_RSCAN0TMID14 */
#define RSCAN_FROM_RSCAN0TMID15 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID15) /* RSCAN_FROM_RSCAN0TMID15 */
#define RSCAN_FROM_RSCAN0TMID16 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID16) /* RSCAN_FROM_RSCAN0TMID16 */
#define RSCAN_FROM_RSCAN0TMID17 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID17) /* RSCAN_FROM_RSCAN0TMID17 */
#define RSCAN_FROM_RSCAN0TMID18 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID18) /* RSCAN_FROM_RSCAN0TMID18 */
#define RSCAN_FROM_RSCAN0TMID19 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID19) /* RSCAN_FROM_RSCAN0TMID19 */
#define RSCAN_FROM_RSCAN0TMID20 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID20) /* RSCAN_FROM_RSCAN0TMID20 */
#define RSCAN_FROM_RSCAN0TMID21 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID21) /* RSCAN_FROM_RSCAN0TMID21 */
#define RSCAN_FROM_RSCAN0TMID22 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID22) /* RSCAN_FROM_RSCAN0TMID22 */
#define RSCAN_FROM_RSCAN0TMID23 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID23) /* RSCAN_FROM_RSCAN0TMID23 */
#define RSCAN_FROM_RSCAN0TMID24 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID24) /* RSCAN_FROM_RSCAN0TMID24 */
#define RSCAN_FROM_RSCAN0TMID25 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID25) /* RSCAN_FROM_RSCAN0TMID25 */
#define RSCAN_FROM_RSCAN0TMID26 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID26) /* RSCAN_FROM_RSCAN0TMID26 */
#define RSCAN_FROM_RSCAN0TMID27 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID27) /* RSCAN_FROM_RSCAN0TMID27 */
#define RSCAN_FROM_RSCAN0TMID28 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID28) /* RSCAN_FROM_RSCAN0TMID28 */
#define RSCAN_FROM_RSCAN0TMID29 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID29) /* RSCAN_FROM_RSCAN0TMID29 */
#define RSCAN_FROM_RSCAN0TMID30 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID30) /* RSCAN_FROM_RSCAN0TMID30 */
#define RSCAN_FROM_RSCAN0TMID31 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID31) /* RSCAN_FROM_RSCAN0TMID31 */
#define RSCAN_FROM_RSCAN0TMID32 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID32) /* RSCAN_FROM_RSCAN0TMID32 */
#define RSCAN_FROM_RSCAN0TMID33 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID33) /* RSCAN_FROM_RSCAN0TMID33 */
#define RSCAN_FROM_RSCAN0TMID34 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID34) /* RSCAN_FROM_RSCAN0TMID34 */
#define RSCAN_FROM_RSCAN0TMID35 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID35) /* RSCAN_FROM_RSCAN0TMID35 */
#define RSCAN_FROM_RSCAN0TMID36 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID36) /* RSCAN_FROM_RSCAN0TMID36 */
#define RSCAN_FROM_RSCAN0TMID37 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID37) /* RSCAN_FROM_RSCAN0TMID37 */
#define RSCAN_FROM_RSCAN0TMID38 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID38) /* RSCAN_FROM_RSCAN0TMID38 */
#define RSCAN_FROM_RSCAN0TMID39 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID39) /* RSCAN_FROM_RSCAN0TMID39 */
#define RSCAN_FROM_RSCAN0TMID40 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID40) /* RSCAN_FROM_RSCAN0TMID40 */
#define RSCAN_FROM_RSCAN0TMID41 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID41) /* RSCAN_FROM_RSCAN0TMID41 */
#define RSCAN_FROM_RSCAN0TMID42 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID42) /* RSCAN_FROM_RSCAN0TMID42 */
#define RSCAN_FROM_RSCAN0TMID43 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID43) /* RSCAN_FROM_RSCAN0TMID43 */
#define RSCAN_FROM_RSCAN0TMID44 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID44) /* RSCAN_FROM_RSCAN0TMID44 */
#define RSCAN_FROM_RSCAN0TMID45 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID45) /* RSCAN_FROM_RSCAN0TMID45 */
#define RSCAN_FROM_RSCAN0TMID46 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID46) /* RSCAN_FROM_RSCAN0TMID46 */
#define RSCAN_FROM_RSCAN0TMID47 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID47) /* RSCAN_FROM_RSCAN0TMID47 */
#define RSCAN_FROM_RSCAN0TMID48 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID48) /* RSCAN_FROM_RSCAN0TMID48 */
#define RSCAN_FROM_RSCAN0TMID49 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID49) /* RSCAN_FROM_RSCAN0TMID49 */
#define RSCAN_FROM_RSCAN0TMID50 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID50) /* RSCAN_FROM_RSCAN0TMID50 */
#define RSCAN_FROM_RSCAN0TMID51 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID51) /* RSCAN_FROM_RSCAN0TMID51 */
#define RSCAN_FROM_RSCAN0TMID52 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID52) /* RSCAN_FROM_RSCAN0TMID52 */
#define RSCAN_FROM_RSCAN0TMID53 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID53) /* RSCAN_FROM_RSCAN0TMID53 */
#define RSCAN_FROM_RSCAN0TMID54 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID54) /* RSCAN_FROM_RSCAN0TMID54 */
#define RSCAN_FROM_RSCAN0TMID55 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID55) /* RSCAN_FROM_RSCAN0TMID55 */
#define RSCAN_FROM_RSCAN0TMID56 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID56) /* RSCAN_FROM_RSCAN0TMID56 */
#define RSCAN_FROM_RSCAN0TMID57 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID57) /* RSCAN_FROM_RSCAN0TMID57 */
#define RSCAN_FROM_RSCAN0TMID58 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID58) /* RSCAN_FROM_RSCAN0TMID58 */
#define RSCAN_FROM_RSCAN0TMID59 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID59) /* RSCAN_FROM_RSCAN0TMID59 */
#define RSCAN_FROM_RSCAN0TMID60 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID60) /* RSCAN_FROM_RSCAN0TMID60 */
#define RSCAN_FROM_RSCAN0TMID61 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID61) /* RSCAN_FROM_RSCAN0TMID61 */
#define RSCAN_FROM_RSCAN0TMID62 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID62) /* RSCAN_FROM_RSCAN0TMID62 */
#define RSCAN_FROM_RSCAN0TMID63 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID63) /* RSCAN_FROM_RSCAN0TMID63 */
#define RSCAN_FROM_RSCAN0TMID64 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID64) /* RSCAN_FROM_RSCAN0TMID64 */
#define RSCAN_FROM_RSCAN0TMID65 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID65) /* RSCAN_FROM_RSCAN0TMID65 */
#define RSCAN_FROM_RSCAN0TMID66 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID66) /* RSCAN_FROM_RSCAN0TMID66 */
#define RSCAN_FROM_RSCAN0TMID67 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID67) /* RSCAN_FROM_RSCAN0TMID67 */
#define RSCAN_FROM_RSCAN0TMID68 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID68) /* RSCAN_FROM_RSCAN0TMID68 */
#define RSCAN_FROM_RSCAN0TMID69 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID69) /* RSCAN_FROM_RSCAN0TMID69 */
#define RSCAN_FROM_RSCAN0TMID70 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID70) /* RSCAN_FROM_RSCAN0TMID70 */
#define RSCAN_FROM_RSCAN0TMID71 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID71) /* RSCAN_FROM_RSCAN0TMID71 */
#define RSCAN_FROM_RSCAN0TMID72 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID72) /* RSCAN_FROM_RSCAN0TMID72 */
#define RSCAN_FROM_RSCAN0TMID73 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID73) /* RSCAN_FROM_RSCAN0TMID73 */
#define RSCAN_FROM_RSCAN0TMID74 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID74) /* RSCAN_FROM_RSCAN0TMID74 */
#define RSCAN_FROM_RSCAN0TMID75 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID75) /* RSCAN_FROM_RSCAN0TMID75 */
#define RSCAN_FROM_RSCAN0TMID76 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID76) /* RSCAN_FROM_RSCAN0TMID76 */
#define RSCAN_FROM_RSCAN0TMID77 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID77) /* RSCAN_FROM_RSCAN0TMID77 */
#define RSCAN_FROM_RSCAN0TMID78 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID78) /* RSCAN_FROM_RSCAN0TMID78 */
#define RSCAN_FROM_RSCAN0TMID79 (*(struct st_rscan_from_rscan0tmidp *)&RSCAN0.TMID79) /* RSCAN_FROM_RSCAN0TMID79 */


/* Channnel array defines of RSCAN_FROM_RSCAN0RFIDm */
/*(Sample) value = RSCAN_FROM_RSCAN0RFIDm[ channel ]->RFIDm.UINT32; */
#define RSCAN_FROM_RSCAN0RFIDm_COUNT  8
#define RSCAN_FROM_RSCAN0RFIDm_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &RSCAN_FROM_RSCAN0RFID0, &RSCAN_FROM_RSCAN0RFID1, &RSCAN_FROM_RSCAN0RFID2, &RSCAN_FROM_RSCAN0RFID3, &RSCAN_FROM_RSCAN0RFID4, &RSCAN_FROM_RSCAN0RFID5, &RSCAN_FROM_RSCAN0RFID6, &RSCAN_FROM_RSCAN0RFID7 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define RSCAN_FROM_RSCAN0RFID0 (*(struct st_rscan_from_rscan0rfidm *)&RSCAN0.RFID0) /* RSCAN_FROM_RSCAN0RFID0 */
#define RSCAN_FROM_RSCAN0RFID1 (*(struct st_rscan_from_rscan0rfidm *)&RSCAN0.RFID1) /* RSCAN_FROM_RSCAN0RFID1 */
#define RSCAN_FROM_RSCAN0RFID2 (*(struct st_rscan_from_rscan0rfidm *)&RSCAN0.RFID2) /* RSCAN_FROM_RSCAN0RFID2 */
#define RSCAN_FROM_RSCAN0RFID3 (*(struct st_rscan_from_rscan0rfidm *)&RSCAN0.RFID3) /* RSCAN_FROM_RSCAN0RFID3 */
#define RSCAN_FROM_RSCAN0RFID4 (*(struct st_rscan_from_rscan0rfidm *)&RSCAN0.RFID4) /* RSCAN_FROM_RSCAN0RFID4 */
#define RSCAN_FROM_RSCAN0RFID5 (*(struct st_rscan_from_rscan0rfidm *)&RSCAN0.RFID5) /* RSCAN_FROM_RSCAN0RFID5 */
#define RSCAN_FROM_RSCAN0RFID6 (*(struct st_rscan_from_rscan0rfidm *)&RSCAN0.RFID6) /* RSCAN_FROM_RSCAN0RFID6 */
#define RSCAN_FROM_RSCAN0RFID7 (*(struct st_rscan_from_rscan0rfidm *)&RSCAN0.RFID7) /* RSCAN_FROM_RSCAN0RFID7 */


/* Channnel array defines of RSCAN_FROM_RSCAN0RMIDp */
/*(Sample) value = RSCAN_FROM_RSCAN0RMIDp[ channel ]->RMIDp.UINT32; */
#define RSCAN_FROM_RSCAN0RMIDp_COUNT  80
#define RSCAN_FROM_RSCAN0RMIDp_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &RSCAN_FROM_RSCAN0RMID0, &RSCAN_FROM_RSCAN0RMID1, &RSCAN_FROM_RSCAN0RMID2, &RSCAN_FROM_RSCAN0RMID3, &RSCAN_FROM_RSCAN0RMID4, &RSCAN_FROM_RSCAN0RMID5, &RSCAN_FROM_RSCAN0RMID6, &RSCAN_FROM_RSCAN0RMID7, \
    &RSCAN_FROM_RSCAN0RMID8, &RSCAN_FROM_RSCAN0RMID9, &RSCAN_FROM_RSCAN0RMID10, &RSCAN_FROM_RSCAN0RMID11, &RSCAN_FROM_RSCAN0RMID12, &RSCAN_FROM_RSCAN0RMID13, &RSCAN_FROM_RSCAN0RMID14, &RSCAN_FROM_RSCAN0RMID15, \
    &RSCAN_FROM_RSCAN0RMID16, &RSCAN_FROM_RSCAN0RMID17, &RSCAN_FROM_RSCAN0RMID18, &RSCAN_FROM_RSCAN0RMID19, &RSCAN_FROM_RSCAN0RMID20, &RSCAN_FROM_RSCAN0RMID21, &RSCAN_FROM_RSCAN0RMID22, &RSCAN_FROM_RSCAN0RMID23, \
    &RSCAN_FROM_RSCAN0RMID24, &RSCAN_FROM_RSCAN0RMID25, &RSCAN_FROM_RSCAN0RMID26, &RSCAN_FROM_RSCAN0RMID27, &RSCAN_FROM_RSCAN0RMID28, &RSCAN_FROM_RSCAN0RMID29, &RSCAN_FROM_RSCAN0RMID30, &RSCAN_FROM_RSCAN0RMID31, \
    &RSCAN_FROM_RSCAN0RMID32, &RSCAN_FROM_RSCAN0RMID33, &RSCAN_FROM_RSCAN0RMID34, &RSCAN_FROM_RSCAN0RMID35, &RSCAN_FROM_RSCAN0RMID36, &RSCAN_FROM_RSCAN0RMID37, &RSCAN_FROM_RSCAN0RMID38, &RSCAN_FROM_RSCAN0RMID39, \
    &RSCAN_FROM_RSCAN0RMID40, &RSCAN_FROM_RSCAN0RMID41, &RSCAN_FROM_RSCAN0RMID42, &RSCAN_FROM_RSCAN0RMID43, &RSCAN_FROM_RSCAN0RMID44, &RSCAN_FROM_RSCAN0RMID45, &RSCAN_FROM_RSCAN0RMID46, &RSCAN_FROM_RSCAN0RMID47, \
    &RSCAN_FROM_RSCAN0RMID48, &RSCAN_FROM_RSCAN0RMID49, &RSCAN_FROM_RSCAN0RMID50, &RSCAN_FROM_RSCAN0RMID51, &RSCAN_FROM_RSCAN0RMID52, &RSCAN_FROM_RSCAN0RMID53, &RSCAN_FROM_RSCAN0RMID54, &RSCAN_FROM_RSCAN0RMID55, \
    &RSCAN_FROM_RSCAN0RMID56, &RSCAN_FROM_RSCAN0RMID57, &RSCAN_FROM_RSCAN0RMID58, &RSCAN_FROM_RSCAN0RMID59, &RSCAN_FROM_RSCAN0RMID60, &RSCAN_FROM_RSCAN0RMID61, &RSCAN_FROM_RSCAN0RMID62, &RSCAN_FROM_RSCAN0RMID63, \
    &RSCAN_FROM_RSCAN0RMID64, &RSCAN_FROM_RSCAN0RMID65, &RSCAN_FROM_RSCAN0RMID66, &RSCAN_FROM_RSCAN0RMID67, &RSCAN_FROM_RSCAN0RMID68, &RSCAN_FROM_RSCAN0RMID69, &RSCAN_FROM_RSCAN0RMID70, &RSCAN_FROM_RSCAN0RMID71, \
    &RSCAN_FROM_RSCAN0RMID72, &RSCAN_FROM_RSCAN0RMID73, &RSCAN_FROM_RSCAN0RMID74, &RSCAN_FROM_RSCAN0RMID75, &RSCAN_FROM_RSCAN0RMID76, &RSCAN_FROM_RSCAN0RMID77, &RSCAN_FROM_RSCAN0RMID78, &RSCAN_FROM_RSCAN0RMID79 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define RSCAN_FROM_RSCAN0RMID0 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID0) /* RSCAN_FROM_RSCAN0RMID0 */
#define RSCAN_FROM_RSCAN0RMID1 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID1) /* RSCAN_FROM_RSCAN0RMID1 */
#define RSCAN_FROM_RSCAN0RMID2 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID2) /* RSCAN_FROM_RSCAN0RMID2 */
#define RSCAN_FROM_RSCAN0RMID3 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID3) /* RSCAN_FROM_RSCAN0RMID3 */
#define RSCAN_FROM_RSCAN0RMID4 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID4) /* RSCAN_FROM_RSCAN0RMID4 */
#define RSCAN_FROM_RSCAN0RMID5 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID5) /* RSCAN_FROM_RSCAN0RMID5 */
#define RSCAN_FROM_RSCAN0RMID6 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID6) /* RSCAN_FROM_RSCAN0RMID6 */
#define RSCAN_FROM_RSCAN0RMID7 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID7) /* RSCAN_FROM_RSCAN0RMID7 */
#define RSCAN_FROM_RSCAN0RMID8 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID8) /* RSCAN_FROM_RSCAN0RMID8 */
#define RSCAN_FROM_RSCAN0RMID9 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID9) /* RSCAN_FROM_RSCAN0RMID9 */
#define RSCAN_FROM_RSCAN0RMID10 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID10) /* RSCAN_FROM_RSCAN0RMID10 */
#define RSCAN_FROM_RSCAN0RMID11 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID11) /* RSCAN_FROM_RSCAN0RMID11 */
#define RSCAN_FROM_RSCAN0RMID12 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID12) /* RSCAN_FROM_RSCAN0RMID12 */
#define RSCAN_FROM_RSCAN0RMID13 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID13) /* RSCAN_FROM_RSCAN0RMID13 */
#define RSCAN_FROM_RSCAN0RMID14 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID14) /* RSCAN_FROM_RSCAN0RMID14 */
#define RSCAN_FROM_RSCAN0RMID15 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID15) /* RSCAN_FROM_RSCAN0RMID15 */
#define RSCAN_FROM_RSCAN0RMID16 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID16) /* RSCAN_FROM_RSCAN0RMID16 */
#define RSCAN_FROM_RSCAN0RMID17 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID17) /* RSCAN_FROM_RSCAN0RMID17 */
#define RSCAN_FROM_RSCAN0RMID18 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID18) /* RSCAN_FROM_RSCAN0RMID18 */
#define RSCAN_FROM_RSCAN0RMID19 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID19) /* RSCAN_FROM_RSCAN0RMID19 */
#define RSCAN_FROM_RSCAN0RMID20 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID20) /* RSCAN_FROM_RSCAN0RMID20 */
#define RSCAN_FROM_RSCAN0RMID21 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID21) /* RSCAN_FROM_RSCAN0RMID21 */
#define RSCAN_FROM_RSCAN0RMID22 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID22) /* RSCAN_FROM_RSCAN0RMID22 */
#define RSCAN_FROM_RSCAN0RMID23 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID23) /* RSCAN_FROM_RSCAN0RMID23 */
#define RSCAN_FROM_RSCAN0RMID24 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID24) /* RSCAN_FROM_RSCAN0RMID24 */
#define RSCAN_FROM_RSCAN0RMID25 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID25) /* RSCAN_FROM_RSCAN0RMID25 */
#define RSCAN_FROM_RSCAN0RMID26 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID26) /* RSCAN_FROM_RSCAN0RMID26 */
#define RSCAN_FROM_RSCAN0RMID27 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID27) /* RSCAN_FROM_RSCAN0RMID27 */
#define RSCAN_FROM_RSCAN0RMID28 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID28) /* RSCAN_FROM_RSCAN0RMID28 */
#define RSCAN_FROM_RSCAN0RMID29 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID29) /* RSCAN_FROM_RSCAN0RMID29 */
#define RSCAN_FROM_RSCAN0RMID30 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID30) /* RSCAN_FROM_RSCAN0RMID30 */
#define RSCAN_FROM_RSCAN0RMID31 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID31) /* RSCAN_FROM_RSCAN0RMID31 */
#define RSCAN_FROM_RSCAN0RMID32 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID32) /* RSCAN_FROM_RSCAN0RMID32 */
#define RSCAN_FROM_RSCAN0RMID33 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID33) /* RSCAN_FROM_RSCAN0RMID33 */
#define RSCAN_FROM_RSCAN0RMID34 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID34) /* RSCAN_FROM_RSCAN0RMID34 */
#define RSCAN_FROM_RSCAN0RMID35 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID35) /* RSCAN_FROM_RSCAN0RMID35 */
#define RSCAN_FROM_RSCAN0RMID36 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID36) /* RSCAN_FROM_RSCAN0RMID36 */
#define RSCAN_FROM_RSCAN0RMID37 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID37) /* RSCAN_FROM_RSCAN0RMID37 */
#define RSCAN_FROM_RSCAN0RMID38 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID38) /* RSCAN_FROM_RSCAN0RMID38 */
#define RSCAN_FROM_RSCAN0RMID39 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID39) /* RSCAN_FROM_RSCAN0RMID39 */
#define RSCAN_FROM_RSCAN0RMID40 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID40) /* RSCAN_FROM_RSCAN0RMID40 */
#define RSCAN_FROM_RSCAN0RMID41 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID41) /* RSCAN_FROM_RSCAN0RMID41 */
#define RSCAN_FROM_RSCAN0RMID42 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID42) /* RSCAN_FROM_RSCAN0RMID42 */
#define RSCAN_FROM_RSCAN0RMID43 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID43) /* RSCAN_FROM_RSCAN0RMID43 */
#define RSCAN_FROM_RSCAN0RMID44 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID44) /* RSCAN_FROM_RSCAN0RMID44 */
#define RSCAN_FROM_RSCAN0RMID45 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID45) /* RSCAN_FROM_RSCAN0RMID45 */
#define RSCAN_FROM_RSCAN0RMID46 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID46) /* RSCAN_FROM_RSCAN0RMID46 */
#define RSCAN_FROM_RSCAN0RMID47 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID47) /* RSCAN_FROM_RSCAN0RMID47 */
#define RSCAN_FROM_RSCAN0RMID48 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID48) /* RSCAN_FROM_RSCAN0RMID48 */
#define RSCAN_FROM_RSCAN0RMID49 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID49) /* RSCAN_FROM_RSCAN0RMID49 */
#define RSCAN_FROM_RSCAN0RMID50 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID50) /* RSCAN_FROM_RSCAN0RMID50 */
#define RSCAN_FROM_RSCAN0RMID51 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID51) /* RSCAN_FROM_RSCAN0RMID51 */
#define RSCAN_FROM_RSCAN0RMID52 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID52) /* RSCAN_FROM_RSCAN0RMID52 */
#define RSCAN_FROM_RSCAN0RMID53 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID53) /* RSCAN_FROM_RSCAN0RMID53 */
#define RSCAN_FROM_RSCAN0RMID54 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID54) /* RSCAN_FROM_RSCAN0RMID54 */
#define RSCAN_FROM_RSCAN0RMID55 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID55) /* RSCAN_FROM_RSCAN0RMID55 */
#define RSCAN_FROM_RSCAN0RMID56 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID56) /* RSCAN_FROM_RSCAN0RMID56 */
#define RSCAN_FROM_RSCAN0RMID57 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID57) /* RSCAN_FROM_RSCAN0RMID57 */
#define RSCAN_FROM_RSCAN0RMID58 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID58) /* RSCAN_FROM_RSCAN0RMID58 */
#define RSCAN_FROM_RSCAN0RMID59 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID59) /* RSCAN_FROM_RSCAN0RMID59 */
#define RSCAN_FROM_RSCAN0RMID60 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID60) /* RSCAN_FROM_RSCAN0RMID60 */
#define RSCAN_FROM_RSCAN0RMID61 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID61) /* RSCAN_FROM_RSCAN0RMID61 */
#define RSCAN_FROM_RSCAN0RMID62 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID62) /* RSCAN_FROM_RSCAN0RMID62 */
#define RSCAN_FROM_RSCAN0RMID63 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID63) /* RSCAN_FROM_RSCAN0RMID63 */
#define RSCAN_FROM_RSCAN0RMID64 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID64) /* RSCAN_FROM_RSCAN0RMID64 */
#define RSCAN_FROM_RSCAN0RMID65 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID65) /* RSCAN_FROM_RSCAN0RMID65 */
#define RSCAN_FROM_RSCAN0RMID66 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID66) /* RSCAN_FROM_RSCAN0RMID66 */
#define RSCAN_FROM_RSCAN0RMID67 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID67) /* RSCAN_FROM_RSCAN0RMID67 */
#define RSCAN_FROM_RSCAN0RMID68 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID68) /* RSCAN_FROM_RSCAN0RMID68 */
#define RSCAN_FROM_RSCAN0RMID69 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID69) /* RSCAN_FROM_RSCAN0RMID69 */
#define RSCAN_FROM_RSCAN0RMID70 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID70) /* RSCAN_FROM_RSCAN0RMID70 */
#define RSCAN_FROM_RSCAN0RMID71 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID71) /* RSCAN_FROM_RSCAN0RMID71 */
#define RSCAN_FROM_RSCAN0RMID72 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID72) /* RSCAN_FROM_RSCAN0RMID72 */
#define RSCAN_FROM_RSCAN0RMID73 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID73) /* RSCAN_FROM_RSCAN0RMID73 */
#define RSCAN_FROM_RSCAN0RMID74 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID74) /* RSCAN_FROM_RSCAN0RMID74 */
#define RSCAN_FROM_RSCAN0RMID75 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID75) /* RSCAN_FROM_RSCAN0RMID75 */
#define RSCAN_FROM_RSCAN0RMID76 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID76) /* RSCAN_FROM_RSCAN0RMID76 */
#define RSCAN_FROM_RSCAN0RMID77 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID77) /* RSCAN_FROM_RSCAN0RMID77 */
#define RSCAN_FROM_RSCAN0RMID78 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID78) /* RSCAN_FROM_RSCAN0RMID78 */
#define RSCAN_FROM_RSCAN0RMID79 (*(struct st_rscan_from_rscan0rmidp *)&RSCAN0.RMID79) /* RSCAN_FROM_RSCAN0RMID79 */


/* Channnel array defines of RSCAN_FROM_RSCAN0GAFLIDj */
/*(Sample) value = RSCAN_FROM_RSCAN0GAFLIDj[ channel ]->GAFLIDj.UINT32; */
#define RSCAN_FROM_RSCAN0GAFLIDj_COUNT  16
#define RSCAN_FROM_RSCAN0GAFLIDj_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &RSCAN_FROM_RSCAN0GAFLID0, &RSCAN_FROM_RSCAN0GAFLID1, &RSCAN_FROM_RSCAN0GAFLID2, &RSCAN_FROM_RSCAN0GAFLID3, &RSCAN_FROM_RSCAN0GAFLID4, &RSCAN_FROM_RSCAN0GAFLID5, &RSCAN_FROM_RSCAN0GAFLID6, &RSCAN_FROM_RSCAN0GAFLID7, \
    &RSCAN_FROM_RSCAN0GAFLID8, &RSCAN_FROM_RSCAN0GAFLID9, &RSCAN_FROM_RSCAN0GAFLID10, &RSCAN_FROM_RSCAN0GAFLID11, &RSCAN_FROM_RSCAN0GAFLID12, &RSCAN_FROM_RSCAN0GAFLID13, &RSCAN_FROM_RSCAN0GAFLID14, &RSCAN_FROM_RSCAN0GAFLID15 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define RSCAN_FROM_RSCAN0GAFLID0 (*(struct st_rscan_from_rscan0gaflidj *)&RSCAN0.GAFLID0) /* RSCAN_FROM_RSCAN0GAFLID0 */
#define RSCAN_FROM_RSCAN0GAFLID1 (*(struct st_rscan_from_rscan0gaflidj *)&RSCAN0.GAFLID1) /* RSCAN_FROM_RSCAN0GAFLID1 */
#define RSCAN_FROM_RSCAN0GAFLID2 (*(struct st_rscan_from_rscan0gaflidj *)&RSCAN0.GAFLID2) /* RSCAN_FROM_RSCAN0GAFLID2 */
#define RSCAN_FROM_RSCAN0GAFLID3 (*(struct st_rscan_from_rscan0gaflidj *)&RSCAN0.GAFLID3) /* RSCAN_FROM_RSCAN0GAFLID3 */
#define RSCAN_FROM_RSCAN0GAFLID4 (*(struct st_rscan_from_rscan0gaflidj *)&RSCAN0.GAFLID4) /* RSCAN_FROM_RSCAN0GAFLID4 */
#define RSCAN_FROM_RSCAN0GAFLID5 (*(struct st_rscan_from_rscan0gaflidj *)&RSCAN0.GAFLID5) /* RSCAN_FROM_RSCAN0GAFLID5 */
#define RSCAN_FROM_RSCAN0GAFLID6 (*(struct st_rscan_from_rscan0gaflidj *)&RSCAN0.GAFLID6) /* RSCAN_FROM_RSCAN0GAFLID6 */
#define RSCAN_FROM_RSCAN0GAFLID7 (*(struct st_rscan_from_rscan0gaflidj *)&RSCAN0.GAFLID7) /* RSCAN_FROM_RSCAN0GAFLID7 */
#define RSCAN_FROM_RSCAN0GAFLID8 (*(struct st_rscan_from_rscan0gaflidj *)&RSCAN0.GAFLID8) /* RSCAN_FROM_RSCAN0GAFLID8 */
#define RSCAN_FROM_RSCAN0GAFLID9 (*(struct st_rscan_from_rscan0gaflidj *)&RSCAN0.GAFLID9) /* RSCAN_FROM_RSCAN0GAFLID9 */
#define RSCAN_FROM_RSCAN0GAFLID10 (*(struct st_rscan_from_rscan0gaflidj *)&RSCAN0.GAFLID10) /* RSCAN_FROM_RSCAN0GAFLID10 */
#define RSCAN_FROM_RSCAN0GAFLID11 (*(struct st_rscan_from_rscan0gaflidj *)&RSCAN0.GAFLID11) /* RSCAN_FROM_RSCAN0GAFLID11 */
#define RSCAN_FROM_RSCAN0GAFLID12 (*(struct st_rscan_from_rscan0gaflidj *)&RSCAN0.GAFLID12) /* RSCAN_FROM_RSCAN0GAFLID12 */
#define RSCAN_FROM_RSCAN0GAFLID13 (*(struct st_rscan_from_rscan0gaflidj *)&RSCAN0.GAFLID13) /* RSCAN_FROM_RSCAN0GAFLID13 */
#define RSCAN_FROM_RSCAN0GAFLID14 (*(struct st_rscan_from_rscan0gaflidj *)&RSCAN0.GAFLID14) /* RSCAN_FROM_RSCAN0GAFLID14 */
#define RSCAN_FROM_RSCAN0GAFLID15 (*(struct st_rscan_from_rscan0gaflidj *)&RSCAN0.GAFLID15) /* RSCAN_FROM_RSCAN0GAFLID15 */


/* Channnel array defines of RSCAN_FROM_RSCAN0CnCFG */
/*(Sample) value = RSCAN_FROM_RSCAN0CnCFG[ channel ]->CnCFG.UINT32; */
#define RSCAN_FROM_RSCAN0CnCFG_COUNT  5
#define RSCAN_FROM_RSCAN0CnCFG_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &RSCAN_FROM_RSCAN0C0CFG, &RSCAN_FROM_RSCAN0C1CFG, &RSCAN_FROM_RSCAN0C2CFG, &RSCAN_FROM_RSCAN0C3CFG, &RSCAN_FROM_RSCAN0C4CFG \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define RSCAN_FROM_RSCAN0C0CFG (*(struct st_rscan_from_rscan0cncfg *)&RSCAN0.C0CFG) /* RSCAN_FROM_RSCAN0C0CFG */
#define RSCAN_FROM_RSCAN0C1CFG (*(struct st_rscan_from_rscan0cncfg *)&RSCAN0.C1CFG) /* RSCAN_FROM_RSCAN0C1CFG */
#define RSCAN_FROM_RSCAN0C2CFG (*(struct st_rscan_from_rscan0cncfg *)&RSCAN0.C2CFG) /* RSCAN_FROM_RSCAN0C2CFG */
#define RSCAN_FROM_RSCAN0C3CFG (*(struct st_rscan_from_rscan0cncfg *)&RSCAN0.C3CFG) /* RSCAN_FROM_RSCAN0C3CFG */
#define RSCAN_FROM_RSCAN0C4CFG (*(struct st_rscan_from_rscan0cncfg *)&RSCAN0.C4CFG) /* RSCAN_FROM_RSCAN0C4CFG */

/* End of channnel array defines of RSCAN0 */


#define RSCAN0C0CFG RSCAN0.C0CFG.UINT32
#define RSCAN0C0CFGL RSCAN0.C0CFG.UINT16[L]
#define RSCAN0C0CFGLL RSCAN0.C0CFG.UINT8[LL]
#define RSCAN0C0CFGLH RSCAN0.C0CFG.UINT8[LH]
#define RSCAN0C0CFGH RSCAN0.C0CFG.UINT16[H]
#define RSCAN0C0CFGHL RSCAN0.C0CFG.UINT8[HL]
#define RSCAN0C0CFGHH RSCAN0.C0CFG.UINT8[HH]
#define RSCAN0C0CTR RSCAN0.C0CTR.UINT32
#define RSCAN0C0CTRL RSCAN0.C0CTR.UINT16[L]
#define RSCAN0C0CTRLL RSCAN0.C0CTR.UINT8[LL]
#define RSCAN0C0CTRLH RSCAN0.C0CTR.UINT8[LH]
#define RSCAN0C0CTRH RSCAN0.C0CTR.UINT16[H]
#define RSCAN0C0CTRHL RSCAN0.C0CTR.UINT8[HL]
#define RSCAN0C0CTRHH RSCAN0.C0CTR.UINT8[HH]
#define RSCAN0C0STS RSCAN0.C0STS.UINT32
#define RSCAN0C0STSL RSCAN0.C0STS.UINT16[L]
#define RSCAN0C0STSLL RSCAN0.C0STS.UINT8[LL]
#define RSCAN0C0STSLH RSCAN0.C0STS.UINT8[LH]
#define RSCAN0C0STSH RSCAN0.C0STS.UINT16[H]
#define RSCAN0C0STSHL RSCAN0.C0STS.UINT8[HL]
#define RSCAN0C0STSHH RSCAN0.C0STS.UINT8[HH]
#define RSCAN0C0ERFL RSCAN0.C0ERFL.UINT32
#define RSCAN0C0ERFLL RSCAN0.C0ERFL.UINT16[L]
#define RSCAN0C0ERFLLL RSCAN0.C0ERFL.UINT8[LL]
#define RSCAN0C0ERFLLH RSCAN0.C0ERFL.UINT8[LH]
#define RSCAN0C0ERFLH RSCAN0.C0ERFL.UINT16[H]
#define RSCAN0C0ERFLHL RSCAN0.C0ERFL.UINT8[HL]
#define RSCAN0C0ERFLHH RSCAN0.C0ERFL.UINT8[HH]
#define RSCAN0C1CFG RSCAN0.C1CFG.UINT32
#define RSCAN0C1CFGL RSCAN0.C1CFG.UINT16[L]
#define RSCAN0C1CFGLL RSCAN0.C1CFG.UINT8[LL]
#define RSCAN0C1CFGLH RSCAN0.C1CFG.UINT8[LH]
#define RSCAN0C1CFGH RSCAN0.C1CFG.UINT16[H]
#define RSCAN0C1CFGHL RSCAN0.C1CFG.UINT8[HL]
#define RSCAN0C1CFGHH RSCAN0.C1CFG.UINT8[HH]
#define RSCAN0C1CTR RSCAN0.C1CTR.UINT32
#define RSCAN0C1CTRL RSCAN0.C1CTR.UINT16[L]
#define RSCAN0C1CTRLL RSCAN0.C1CTR.UINT8[LL]
#define RSCAN0C1CTRLH RSCAN0.C1CTR.UINT8[LH]
#define RSCAN0C1CTRH RSCAN0.C1CTR.UINT16[H]
#define RSCAN0C1CTRHL RSCAN0.C1CTR.UINT8[HL]
#define RSCAN0C1CTRHH RSCAN0.C1CTR.UINT8[HH]
#define RSCAN0C1STS RSCAN0.C1STS.UINT32
#define RSCAN0C1STSL RSCAN0.C1STS.UINT16[L]
#define RSCAN0C1STSLL RSCAN0.C1STS.UINT8[LL]
#define RSCAN0C1STSLH RSCAN0.C1STS.UINT8[LH]
#define RSCAN0C1STSH RSCAN0.C1STS.UINT16[H]
#define RSCAN0C1STSHL RSCAN0.C1STS.UINT8[HL]
#define RSCAN0C1STSHH RSCAN0.C1STS.UINT8[HH]
#define RSCAN0C1ERFL RSCAN0.C1ERFL.UINT32
#define RSCAN0C1ERFLL RSCAN0.C1ERFL.UINT16[L]
#define RSCAN0C1ERFLLL RSCAN0.C1ERFL.UINT8[LL]
#define RSCAN0C1ERFLLH RSCAN0.C1ERFL.UINT8[LH]
#define RSCAN0C1ERFLH RSCAN0.C1ERFL.UINT16[H]
#define RSCAN0C1ERFLHL RSCAN0.C1ERFL.UINT8[HL]
#define RSCAN0C1ERFLHH RSCAN0.C1ERFL.UINT8[HH]
#define RSCAN0C2CFG RSCAN0.C2CFG.UINT32
#define RSCAN0C2CFGL RSCAN0.C2CFG.UINT16[L]
#define RSCAN0C2CFGLL RSCAN0.C2CFG.UINT8[LL]
#define RSCAN0C2CFGLH RSCAN0.C2CFG.UINT8[LH]
#define RSCAN0C2CFGH RSCAN0.C2CFG.UINT16[H]
#define RSCAN0C2CFGHL RSCAN0.C2CFG.UINT8[HL]
#define RSCAN0C2CFGHH RSCAN0.C2CFG.UINT8[HH]
#define RSCAN0C2CTR RSCAN0.C2CTR.UINT32
#define RSCAN0C2CTRL RSCAN0.C2CTR.UINT16[L]
#define RSCAN0C2CTRLL RSCAN0.C2CTR.UINT8[LL]
#define RSCAN0C2CTRLH RSCAN0.C2CTR.UINT8[LH]
#define RSCAN0C2CTRH RSCAN0.C2CTR.UINT16[H]
#define RSCAN0C2CTRHL RSCAN0.C2CTR.UINT8[HL]
#define RSCAN0C2CTRHH RSCAN0.C2CTR.UINT8[HH]
#define RSCAN0C2STS RSCAN0.C2STS.UINT32
#define RSCAN0C2STSL RSCAN0.C2STS.UINT16[L]
#define RSCAN0C2STSLL RSCAN0.C2STS.UINT8[LL]
#define RSCAN0C2STSLH RSCAN0.C2STS.UINT8[LH]
#define RSCAN0C2STSH RSCAN0.C2STS.UINT16[H]
#define RSCAN0C2STSHL RSCAN0.C2STS.UINT8[HL]
#define RSCAN0C2STSHH RSCAN0.C2STS.UINT8[HH]
#define RSCAN0C2ERFL RSCAN0.C2ERFL.UINT32
#define RSCAN0C2ERFLL RSCAN0.C2ERFL.UINT16[L]
#define RSCAN0C2ERFLLL RSCAN0.C2ERFL.UINT8[LL]
#define RSCAN0C2ERFLLH RSCAN0.C2ERFL.UINT8[LH]
#define RSCAN0C2ERFLH RSCAN0.C2ERFL.UINT16[H]
#define RSCAN0C2ERFLHL RSCAN0.C2ERFL.UINT8[HL]
#define RSCAN0C2ERFLHH RSCAN0.C2ERFL.UINT8[HH]
#define RSCAN0C3CFG RSCAN0.C3CFG.UINT32
#define RSCAN0C3CFGL RSCAN0.C3CFG.UINT16[L]
#define RSCAN0C3CFGLL RSCAN0.C3CFG.UINT8[LL]
#define RSCAN0C3CFGLH RSCAN0.C3CFG.UINT8[LH]
#define RSCAN0C3CFGH RSCAN0.C3CFG.UINT16[H]
#define RSCAN0C3CFGHL RSCAN0.C3CFG.UINT8[HL]
#define RSCAN0C3CFGHH RSCAN0.C3CFG.UINT8[HH]
#define RSCAN0C3CTR RSCAN0.C3CTR.UINT32
#define RSCAN0C3CTRL RSCAN0.C3CTR.UINT16[L]
#define RSCAN0C3CTRLL RSCAN0.C3CTR.UINT8[LL]
#define RSCAN0C3CTRLH RSCAN0.C3CTR.UINT8[LH]
#define RSCAN0C3CTRH RSCAN0.C3CTR.UINT16[H]
#define RSCAN0C3CTRHL RSCAN0.C3CTR.UINT8[HL]
#define RSCAN0C3CTRHH RSCAN0.C3CTR.UINT8[HH]
#define RSCAN0C3STS RSCAN0.C3STS.UINT32
#define RSCAN0C3STSL RSCAN0.C3STS.UINT16[L]
#define RSCAN0C3STSLL RSCAN0.C3STS.UINT8[LL]
#define RSCAN0C3STSLH RSCAN0.C3STS.UINT8[LH]
#define RSCAN0C3STSH RSCAN0.C3STS.UINT16[H]
#define RSCAN0C3STSHL RSCAN0.C3STS.UINT8[HL]
#define RSCAN0C3STSHH RSCAN0.C3STS.UINT8[HH]
#define RSCAN0C3ERFL RSCAN0.C3ERFL.UINT32
#define RSCAN0C3ERFLL RSCAN0.C3ERFL.UINT16[L]
#define RSCAN0C3ERFLLL RSCAN0.C3ERFL.UINT8[LL]
#define RSCAN0C3ERFLLH RSCAN0.C3ERFL.UINT8[LH]
#define RSCAN0C3ERFLH RSCAN0.C3ERFL.UINT16[H]
#define RSCAN0C3ERFLHL RSCAN0.C3ERFL.UINT8[HL]
#define RSCAN0C3ERFLHH RSCAN0.C3ERFL.UINT8[HH]
#define RSCAN0C4CFG RSCAN0.C4CFG.UINT32
#define RSCAN0C4CFGL RSCAN0.C4CFG.UINT16[L]
#define RSCAN0C4CFGLL RSCAN0.C4CFG.UINT8[LL]
#define RSCAN0C4CFGLH RSCAN0.C4CFG.UINT8[LH]
#define RSCAN0C4CFGH RSCAN0.C4CFG.UINT16[H]
#define RSCAN0C4CFGHL RSCAN0.C4CFG.UINT8[HL]
#define RSCAN0C4CFGHH RSCAN0.C4CFG.UINT8[HH]
#define RSCAN0C4CTR RSCAN0.C4CTR.UINT32
#define RSCAN0C4CTRL RSCAN0.C4CTR.UINT16[L]
#define RSCAN0C4CTRLL RSCAN0.C4CTR.UINT8[LL]
#define RSCAN0C4CTRLH RSCAN0.C4CTR.UINT8[LH]
#define RSCAN0C4CTRH RSCAN0.C4CTR.UINT16[H]
#define RSCAN0C4CTRHL RSCAN0.C4CTR.UINT8[HL]
#define RSCAN0C4CTRHH RSCAN0.C4CTR.UINT8[HH]
#define RSCAN0C4STS RSCAN0.C4STS.UINT32
#define RSCAN0C4STSL RSCAN0.C4STS.UINT16[L]
#define RSCAN0C4STSLL RSCAN0.C4STS.UINT8[LL]
#define RSCAN0C4STSLH RSCAN0.C4STS.UINT8[LH]
#define RSCAN0C4STSH RSCAN0.C4STS.UINT16[H]
#define RSCAN0C4STSHL RSCAN0.C4STS.UINT8[HL]
#define RSCAN0C4STSHH RSCAN0.C4STS.UINT8[HH]
#define RSCAN0C4ERFL RSCAN0.C4ERFL.UINT32
#define RSCAN0C4ERFLL RSCAN0.C4ERFL.UINT16[L]
#define RSCAN0C4ERFLLL RSCAN0.C4ERFL.UINT8[LL]
#define RSCAN0C4ERFLLH RSCAN0.C4ERFL.UINT8[LH]
#define RSCAN0C4ERFLH RSCAN0.C4ERFL.UINT16[H]
#define RSCAN0C4ERFLHL RSCAN0.C4ERFL.UINT8[HL]
#define RSCAN0C4ERFLHH RSCAN0.C4ERFL.UINT8[HH]
#define RSCAN0GCFG RSCAN0.GCFG.UINT32
#define RSCAN0GCFGL RSCAN0.GCFG.UINT16[L]
#define RSCAN0GCFGLL RSCAN0.GCFG.UINT8[LL]
#define RSCAN0GCFGLH RSCAN0.GCFG.UINT8[LH]
#define RSCAN0GCFGH RSCAN0.GCFG.UINT16[H]
#define RSCAN0GCFGHL RSCAN0.GCFG.UINT8[HL]
#define RSCAN0GCFGHH RSCAN0.GCFG.UINT8[HH]
#define RSCAN0GCTR RSCAN0.GCTR.UINT32
#define RSCAN0GCTRL RSCAN0.GCTR.UINT16[L]
#define RSCAN0GCTRLL RSCAN0.GCTR.UINT8[LL]
#define RSCAN0GCTRLH RSCAN0.GCTR.UINT8[LH]
#define RSCAN0GCTRH RSCAN0.GCTR.UINT16[H]
#define RSCAN0GCTRHL RSCAN0.GCTR.UINT8[HL]
#define RSCAN0GCTRHH RSCAN0.GCTR.UINT8[HH]
#define RSCAN0GSTS RSCAN0.GSTS.UINT32
#define RSCAN0GSTSL RSCAN0.GSTS.UINT16[L]
#define RSCAN0GSTSLL RSCAN0.GSTS.UINT8[LL]
#define RSCAN0GSTSLH RSCAN0.GSTS.UINT8[LH]
#define RSCAN0GSTSH RSCAN0.GSTS.UINT16[H]
#define RSCAN0GSTSHL RSCAN0.GSTS.UINT8[HL]
#define RSCAN0GSTSHH RSCAN0.GSTS.UINT8[HH]
#define RSCAN0GERFL RSCAN0.GERFL.UINT32
#define RSCAN0GERFLL RSCAN0.GERFL.UINT16[L]
#define RSCAN0GERFLLL RSCAN0.GERFL.UINT8[LL]
#define RSCAN0GERFLLH RSCAN0.GERFL.UINT8[LH]
#define RSCAN0GERFLH RSCAN0.GERFL.UINT16[H]
#define RSCAN0GERFLHL RSCAN0.GERFL.UINT8[HL]
#define RSCAN0GERFLHH RSCAN0.GERFL.UINT8[HH]
#define RSCAN0GTSC RSCAN0.GTSC.UINT32
#define RSCAN0GTSCL RSCAN0.GTSC.UINT16[L]
#define RSCAN0GTSCH RSCAN0.GTSC.UINT16[H]
#define RSCAN0GAFLECTR RSCAN0.GAFLECTR.UINT32
#define RSCAN0GAFLECTRL RSCAN0.GAFLECTR.UINT16[L]
#define RSCAN0GAFLECTRLL RSCAN0.GAFLECTR.UINT8[LL]
#define RSCAN0GAFLECTRLH RSCAN0.GAFLECTR.UINT8[LH]
#define RSCAN0GAFLECTRH RSCAN0.GAFLECTR.UINT16[H]
#define RSCAN0GAFLECTRHL RSCAN0.GAFLECTR.UINT8[HL]
#define RSCAN0GAFLECTRHH RSCAN0.GAFLECTR.UINT8[HH]
#define RSCAN0GAFLCFG0 RSCAN0.GAFLCFG0.UINT32
#define RSCAN0GAFLCFG0L RSCAN0.GAFLCFG0.UINT16[L]
#define RSCAN0GAFLCFG0LL RSCAN0.GAFLCFG0.UINT8[LL]
#define RSCAN0GAFLCFG0LH RSCAN0.GAFLCFG0.UINT8[LH]
#define RSCAN0GAFLCFG0H RSCAN0.GAFLCFG0.UINT16[H]
#define RSCAN0GAFLCFG0HL RSCAN0.GAFLCFG0.UINT8[HL]
#define RSCAN0GAFLCFG0HH RSCAN0.GAFLCFG0.UINT8[HH]
#define RSCAN0GAFLCFG1 RSCAN0.GAFLCFG1.UINT32
#define RSCAN0GAFLCFG1L RSCAN0.GAFLCFG1.UINT16[L]
#define RSCAN0GAFLCFG1LL RSCAN0.GAFLCFG1.UINT8[LL]
#define RSCAN0GAFLCFG1LH RSCAN0.GAFLCFG1.UINT8[LH]
#define RSCAN0GAFLCFG1H RSCAN0.GAFLCFG1.UINT16[H]
#define RSCAN0GAFLCFG1HL RSCAN0.GAFLCFG1.UINT8[HL]
#define RSCAN0GAFLCFG1HH RSCAN0.GAFLCFG1.UINT8[HH]
#define RSCAN0RMNB RSCAN0.RMNB.UINT32
#define RSCAN0RMNBL RSCAN0.RMNB.UINT16[L]
#define RSCAN0RMNBLL RSCAN0.RMNB.UINT8[LL]
#define RSCAN0RMNBLH RSCAN0.RMNB.UINT8[LH]
#define RSCAN0RMNBH RSCAN0.RMNB.UINT16[H]
#define RSCAN0RMNBHL RSCAN0.RMNB.UINT8[HL]
#define RSCAN0RMNBHH RSCAN0.RMNB.UINT8[HH]
#define RSCAN0RMND0 RSCAN0.RMND0.UINT32
#define RSCAN0RMND0L RSCAN0.RMND0.UINT16[L]
#define RSCAN0RMND0LL RSCAN0.RMND0.UINT8[LL]
#define RSCAN0RMND0LH RSCAN0.RMND0.UINT8[LH]
#define RSCAN0RMND0H RSCAN0.RMND0.UINT16[H]
#define RSCAN0RMND0HL RSCAN0.RMND0.UINT8[HL]
#define RSCAN0RMND0HH RSCAN0.RMND0.UINT8[HH]
#define RSCAN0RMND1 RSCAN0.RMND1.UINT32
#define RSCAN0RMND1L RSCAN0.RMND1.UINT16[L]
#define RSCAN0RMND1LL RSCAN0.RMND1.UINT8[LL]
#define RSCAN0RMND1LH RSCAN0.RMND1.UINT8[LH]
#define RSCAN0RMND1H RSCAN0.RMND1.UINT16[H]
#define RSCAN0RMND1HL RSCAN0.RMND1.UINT8[HL]
#define RSCAN0RMND1HH RSCAN0.RMND1.UINT8[HH]
#define RSCAN0RMND2 RSCAN0.RMND2.UINT32
#define RSCAN0RMND2L RSCAN0.RMND2.UINT16[L]
#define RSCAN0RMND2LL RSCAN0.RMND2.UINT8[LL]
#define RSCAN0RMND2LH RSCAN0.RMND2.UINT8[LH]
#define RSCAN0RMND2H RSCAN0.RMND2.UINT16[H]
#define RSCAN0RMND2HL RSCAN0.RMND2.UINT8[HL]
#define RSCAN0RMND2HH RSCAN0.RMND2.UINT8[HH]
#define RSCAN0RFCC0 RSCAN0.RFCC0.UINT32
#define RSCAN0RFCC0L RSCAN0.RFCC0.UINT16[L]
#define RSCAN0RFCC0LL RSCAN0.RFCC0.UINT8[LL]
#define RSCAN0RFCC0LH RSCAN0.RFCC0.UINT8[LH]
#define RSCAN0RFCC0H RSCAN0.RFCC0.UINT16[H]
#define RSCAN0RFCC0HL RSCAN0.RFCC0.UINT8[HL]
#define RSCAN0RFCC0HH RSCAN0.RFCC0.UINT8[HH]
#define RSCAN0RFCC1 RSCAN0.RFCC1.UINT32
#define RSCAN0RFCC1L RSCAN0.RFCC1.UINT16[L]
#define RSCAN0RFCC1LL RSCAN0.RFCC1.UINT8[LL]
#define RSCAN0RFCC1LH RSCAN0.RFCC1.UINT8[LH]
#define RSCAN0RFCC1H RSCAN0.RFCC1.UINT16[H]
#define RSCAN0RFCC1HL RSCAN0.RFCC1.UINT8[HL]
#define RSCAN0RFCC1HH RSCAN0.RFCC1.UINT8[HH]
#define RSCAN0RFCC2 RSCAN0.RFCC2.UINT32
#define RSCAN0RFCC2L RSCAN0.RFCC2.UINT16[L]
#define RSCAN0RFCC2LL RSCAN0.RFCC2.UINT8[LL]
#define RSCAN0RFCC2LH RSCAN0.RFCC2.UINT8[LH]
#define RSCAN0RFCC2H RSCAN0.RFCC2.UINT16[H]
#define RSCAN0RFCC2HL RSCAN0.RFCC2.UINT8[HL]
#define RSCAN0RFCC2HH RSCAN0.RFCC2.UINT8[HH]
#define RSCAN0RFCC3 RSCAN0.RFCC3.UINT32
#define RSCAN0RFCC3L RSCAN0.RFCC3.UINT16[L]
#define RSCAN0RFCC3LL RSCAN0.RFCC3.UINT8[LL]
#define RSCAN0RFCC3LH RSCAN0.RFCC3.UINT8[LH]
#define RSCAN0RFCC3H RSCAN0.RFCC3.UINT16[H]
#define RSCAN0RFCC3HL RSCAN0.RFCC3.UINT8[HL]
#define RSCAN0RFCC3HH RSCAN0.RFCC3.UINT8[HH]
#define RSCAN0RFCC4 RSCAN0.RFCC4.UINT32
#define RSCAN0RFCC4L RSCAN0.RFCC4.UINT16[L]
#define RSCAN0RFCC4LL RSCAN0.RFCC4.UINT8[LL]
#define RSCAN0RFCC4LH RSCAN0.RFCC4.UINT8[LH]
#define RSCAN0RFCC4H RSCAN0.RFCC4.UINT16[H]
#define RSCAN0RFCC4HL RSCAN0.RFCC4.UINT8[HL]
#define RSCAN0RFCC4HH RSCAN0.RFCC4.UINT8[HH]
#define RSCAN0RFCC5 RSCAN0.RFCC5.UINT32
#define RSCAN0RFCC5L RSCAN0.RFCC5.UINT16[L]
#define RSCAN0RFCC5LL RSCAN0.RFCC5.UINT8[LL]
#define RSCAN0RFCC5LH RSCAN0.RFCC5.UINT8[LH]
#define RSCAN0RFCC5H RSCAN0.RFCC5.UINT16[H]
#define RSCAN0RFCC5HL RSCAN0.RFCC5.UINT8[HL]
#define RSCAN0RFCC5HH RSCAN0.RFCC5.UINT8[HH]
#define RSCAN0RFCC6 RSCAN0.RFCC6.UINT32
#define RSCAN0RFCC6L RSCAN0.RFCC6.UINT16[L]
#define RSCAN0RFCC6LL RSCAN0.RFCC6.UINT8[LL]
#define RSCAN0RFCC6LH RSCAN0.RFCC6.UINT8[LH]
#define RSCAN0RFCC6H RSCAN0.RFCC6.UINT16[H]
#define RSCAN0RFCC6HL RSCAN0.RFCC6.UINT8[HL]
#define RSCAN0RFCC6HH RSCAN0.RFCC6.UINT8[HH]
#define RSCAN0RFCC7 RSCAN0.RFCC7.UINT32
#define RSCAN0RFCC7L RSCAN0.RFCC7.UINT16[L]
#define RSCAN0RFCC7LL RSCAN0.RFCC7.UINT8[LL]
#define RSCAN0RFCC7LH RSCAN0.RFCC7.UINT8[LH]
#define RSCAN0RFCC7H RSCAN0.RFCC7.UINT16[H]
#define RSCAN0RFCC7HL RSCAN0.RFCC7.UINT8[HL]
#define RSCAN0RFCC7HH RSCAN0.RFCC7.UINT8[HH]
#define RSCAN0RFSTS0 RSCAN0.RFSTS0.UINT32
#define RSCAN0RFSTS0L RSCAN0.RFSTS0.UINT16[L]
#define RSCAN0RFSTS0LL RSCAN0.RFSTS0.UINT8[LL]
#define RSCAN0RFSTS0LH RSCAN0.RFSTS0.UINT8[LH]
#define RSCAN0RFSTS0H RSCAN0.RFSTS0.UINT16[H]
#define RSCAN0RFSTS0HL RSCAN0.RFSTS0.UINT8[HL]
#define RSCAN0RFSTS0HH RSCAN0.RFSTS0.UINT8[HH]
#define RSCAN0RFSTS1 RSCAN0.RFSTS1.UINT32
#define RSCAN0RFSTS1L RSCAN0.RFSTS1.UINT16[L]
#define RSCAN0RFSTS1LL RSCAN0.RFSTS1.UINT8[LL]
#define RSCAN0RFSTS1LH RSCAN0.RFSTS1.UINT8[LH]
#define RSCAN0RFSTS1H RSCAN0.RFSTS1.UINT16[H]
#define RSCAN0RFSTS1HL RSCAN0.RFSTS1.UINT8[HL]
#define RSCAN0RFSTS1HH RSCAN0.RFSTS1.UINT8[HH]
#define RSCAN0RFSTS2 RSCAN0.RFSTS2.UINT32
#define RSCAN0RFSTS2L RSCAN0.RFSTS2.UINT16[L]
#define RSCAN0RFSTS2LL RSCAN0.RFSTS2.UINT8[LL]
#define RSCAN0RFSTS2LH RSCAN0.RFSTS2.UINT8[LH]
#define RSCAN0RFSTS2H RSCAN0.RFSTS2.UINT16[H]
#define RSCAN0RFSTS2HL RSCAN0.RFSTS2.UINT8[HL]
#define RSCAN0RFSTS2HH RSCAN0.RFSTS2.UINT8[HH]
#define RSCAN0RFSTS3 RSCAN0.RFSTS3.UINT32
#define RSCAN0RFSTS3L RSCAN0.RFSTS3.UINT16[L]
#define RSCAN0RFSTS3LL RSCAN0.RFSTS3.UINT8[LL]
#define RSCAN0RFSTS3LH RSCAN0.RFSTS3.UINT8[LH]
#define RSCAN0RFSTS3H RSCAN0.RFSTS3.UINT16[H]
#define RSCAN0RFSTS3HL RSCAN0.RFSTS3.UINT8[HL]
#define RSCAN0RFSTS3HH RSCAN0.RFSTS3.UINT8[HH]
#define RSCAN0RFSTS4 RSCAN0.RFSTS4.UINT32
#define RSCAN0RFSTS4L RSCAN0.RFSTS4.UINT16[L]
#define RSCAN0RFSTS4LL RSCAN0.RFSTS4.UINT8[LL]
#define RSCAN0RFSTS4LH RSCAN0.RFSTS4.UINT8[LH]
#define RSCAN0RFSTS4H RSCAN0.RFSTS4.UINT16[H]
#define RSCAN0RFSTS4HL RSCAN0.RFSTS4.UINT8[HL]
#define RSCAN0RFSTS4HH RSCAN0.RFSTS4.UINT8[HH]
#define RSCAN0RFSTS5 RSCAN0.RFSTS5.UINT32
#define RSCAN0RFSTS5L RSCAN0.RFSTS5.UINT16[L]
#define RSCAN0RFSTS5LL RSCAN0.RFSTS5.UINT8[LL]
#define RSCAN0RFSTS5LH RSCAN0.RFSTS5.UINT8[LH]
#define RSCAN0RFSTS5H RSCAN0.RFSTS5.UINT16[H]
#define RSCAN0RFSTS5HL RSCAN0.RFSTS5.UINT8[HL]
#define RSCAN0RFSTS5HH RSCAN0.RFSTS5.UINT8[HH]
#define RSCAN0RFSTS6 RSCAN0.RFSTS6.UINT32
#define RSCAN0RFSTS6L RSCAN0.RFSTS6.UINT16[L]
#define RSCAN0RFSTS6LL RSCAN0.RFSTS6.UINT8[LL]
#define RSCAN0RFSTS6LH RSCAN0.RFSTS6.UINT8[LH]
#define RSCAN0RFSTS6H RSCAN0.RFSTS6.UINT16[H]
#define RSCAN0RFSTS6HL RSCAN0.RFSTS6.UINT8[HL]
#define RSCAN0RFSTS6HH RSCAN0.RFSTS6.UINT8[HH]
#define RSCAN0RFSTS7 RSCAN0.RFSTS7.UINT32
#define RSCAN0RFSTS7L RSCAN0.RFSTS7.UINT16[L]
#define RSCAN0RFSTS7LL RSCAN0.RFSTS7.UINT8[LL]
#define RSCAN0RFSTS7LH RSCAN0.RFSTS7.UINT8[LH]
#define RSCAN0RFSTS7H RSCAN0.RFSTS7.UINT16[H]
#define RSCAN0RFSTS7HL RSCAN0.RFSTS7.UINT8[HL]
#define RSCAN0RFSTS7HH RSCAN0.RFSTS7.UINT8[HH]
#define RSCAN0RFPCTR0 RSCAN0.RFPCTR0.UINT32
#define RSCAN0RFPCTR0L RSCAN0.RFPCTR0.UINT16[L]
#define RSCAN0RFPCTR0LL RSCAN0.RFPCTR0.UINT8[LL]
#define RSCAN0RFPCTR0LH RSCAN0.RFPCTR0.UINT8[LH]
#define RSCAN0RFPCTR0H RSCAN0.RFPCTR0.UINT16[H]
#define RSCAN0RFPCTR0HL RSCAN0.RFPCTR0.UINT8[HL]
#define RSCAN0RFPCTR0HH RSCAN0.RFPCTR0.UINT8[HH]
#define RSCAN0RFPCTR1 RSCAN0.RFPCTR1.UINT32
#define RSCAN0RFPCTR1L RSCAN0.RFPCTR1.UINT16[L]
#define RSCAN0RFPCTR1LL RSCAN0.RFPCTR1.UINT8[LL]
#define RSCAN0RFPCTR1LH RSCAN0.RFPCTR1.UINT8[LH]
#define RSCAN0RFPCTR1H RSCAN0.RFPCTR1.UINT16[H]
#define RSCAN0RFPCTR1HL RSCAN0.RFPCTR1.UINT8[HL]
#define RSCAN0RFPCTR1HH RSCAN0.RFPCTR1.UINT8[HH]
#define RSCAN0RFPCTR2 RSCAN0.RFPCTR2.UINT32
#define RSCAN0RFPCTR2L RSCAN0.RFPCTR2.UINT16[L]
#define RSCAN0RFPCTR2LL RSCAN0.RFPCTR2.UINT8[LL]
#define RSCAN0RFPCTR2LH RSCAN0.RFPCTR2.UINT8[LH]
#define RSCAN0RFPCTR2H RSCAN0.RFPCTR2.UINT16[H]
#define RSCAN0RFPCTR2HL RSCAN0.RFPCTR2.UINT8[HL]
#define RSCAN0RFPCTR2HH RSCAN0.RFPCTR2.UINT8[HH]
#define RSCAN0RFPCTR3 RSCAN0.RFPCTR3.UINT32
#define RSCAN0RFPCTR3L RSCAN0.RFPCTR3.UINT16[L]
#define RSCAN0RFPCTR3LL RSCAN0.RFPCTR3.UINT8[LL]
#define RSCAN0RFPCTR3LH RSCAN0.RFPCTR3.UINT8[LH]
#define RSCAN0RFPCTR3H RSCAN0.RFPCTR3.UINT16[H]
#define RSCAN0RFPCTR3HL RSCAN0.RFPCTR3.UINT8[HL]
#define RSCAN0RFPCTR3HH RSCAN0.RFPCTR3.UINT8[HH]
#define RSCAN0RFPCTR4 RSCAN0.RFPCTR4.UINT32
#define RSCAN0RFPCTR4L RSCAN0.RFPCTR4.UINT16[L]
#define RSCAN0RFPCTR4LL RSCAN0.RFPCTR4.UINT8[LL]
#define RSCAN0RFPCTR4LH RSCAN0.RFPCTR4.UINT8[LH]
#define RSCAN0RFPCTR4H RSCAN0.RFPCTR4.UINT16[H]
#define RSCAN0RFPCTR4HL RSCAN0.RFPCTR4.UINT8[HL]
#define RSCAN0RFPCTR4HH RSCAN0.RFPCTR4.UINT8[HH]
#define RSCAN0RFPCTR5 RSCAN0.RFPCTR5.UINT32
#define RSCAN0RFPCTR5L RSCAN0.RFPCTR5.UINT16[L]
#define RSCAN0RFPCTR5LL RSCAN0.RFPCTR5.UINT8[LL]
#define RSCAN0RFPCTR5LH RSCAN0.RFPCTR5.UINT8[LH]
#define RSCAN0RFPCTR5H RSCAN0.RFPCTR5.UINT16[H]
#define RSCAN0RFPCTR5HL RSCAN0.RFPCTR5.UINT8[HL]
#define RSCAN0RFPCTR5HH RSCAN0.RFPCTR5.UINT8[HH]
#define RSCAN0RFPCTR6 RSCAN0.RFPCTR6.UINT32
#define RSCAN0RFPCTR6L RSCAN0.RFPCTR6.UINT16[L]
#define RSCAN0RFPCTR6LL RSCAN0.RFPCTR6.UINT8[LL]
#define RSCAN0RFPCTR6LH RSCAN0.RFPCTR6.UINT8[LH]
#define RSCAN0RFPCTR6H RSCAN0.RFPCTR6.UINT16[H]
#define RSCAN0RFPCTR6HL RSCAN0.RFPCTR6.UINT8[HL]
#define RSCAN0RFPCTR6HH RSCAN0.RFPCTR6.UINT8[HH]
#define RSCAN0RFPCTR7 RSCAN0.RFPCTR7.UINT32
#define RSCAN0RFPCTR7L RSCAN0.RFPCTR7.UINT16[L]
#define RSCAN0RFPCTR7LL RSCAN0.RFPCTR7.UINT8[LL]
#define RSCAN0RFPCTR7LH RSCAN0.RFPCTR7.UINT8[LH]
#define RSCAN0RFPCTR7H RSCAN0.RFPCTR7.UINT16[H]
#define RSCAN0RFPCTR7HL RSCAN0.RFPCTR7.UINT8[HL]
#define RSCAN0RFPCTR7HH RSCAN0.RFPCTR7.UINT8[HH]
#define RSCAN0CFCC0 RSCAN0.CFCC0.UINT32
#define RSCAN0CFCC0L RSCAN0.CFCC0.UINT16[L]
#define RSCAN0CFCC0LL RSCAN0.CFCC0.UINT8[LL]
#define RSCAN0CFCC0LH RSCAN0.CFCC0.UINT8[LH]
#define RSCAN0CFCC0H RSCAN0.CFCC0.UINT16[H]
#define RSCAN0CFCC0HL RSCAN0.CFCC0.UINT8[HL]
#define RSCAN0CFCC0HH RSCAN0.CFCC0.UINT8[HH]
#define RSCAN0CFCC1 RSCAN0.CFCC1.UINT32
#define RSCAN0CFCC1L RSCAN0.CFCC1.UINT16[L]
#define RSCAN0CFCC1LL RSCAN0.CFCC1.UINT8[LL]
#define RSCAN0CFCC1LH RSCAN0.CFCC1.UINT8[LH]
#define RSCAN0CFCC1H RSCAN0.CFCC1.UINT16[H]
#define RSCAN0CFCC1HL RSCAN0.CFCC1.UINT8[HL]
#define RSCAN0CFCC1HH RSCAN0.CFCC1.UINT8[HH]
#define RSCAN0CFCC2 RSCAN0.CFCC2.UINT32
#define RSCAN0CFCC2L RSCAN0.CFCC2.UINT16[L]
#define RSCAN0CFCC2LL RSCAN0.CFCC2.UINT8[LL]
#define RSCAN0CFCC2LH RSCAN0.CFCC2.UINT8[LH]
#define RSCAN0CFCC2H RSCAN0.CFCC2.UINT16[H]
#define RSCAN0CFCC2HL RSCAN0.CFCC2.UINT8[HL]
#define RSCAN0CFCC2HH RSCAN0.CFCC2.UINT8[HH]
#define RSCAN0CFCC3 RSCAN0.CFCC3.UINT32
#define RSCAN0CFCC3L RSCAN0.CFCC3.UINT16[L]
#define RSCAN0CFCC3LL RSCAN0.CFCC3.UINT8[LL]
#define RSCAN0CFCC3LH RSCAN0.CFCC3.UINT8[LH]
#define RSCAN0CFCC3H RSCAN0.CFCC3.UINT16[H]
#define RSCAN0CFCC3HL RSCAN0.CFCC3.UINT8[HL]
#define RSCAN0CFCC3HH RSCAN0.CFCC3.UINT8[HH]
#define RSCAN0CFCC4 RSCAN0.CFCC4.UINT32
#define RSCAN0CFCC4L RSCAN0.CFCC4.UINT16[L]
#define RSCAN0CFCC4LL RSCAN0.CFCC4.UINT8[LL]
#define RSCAN0CFCC4LH RSCAN0.CFCC4.UINT8[LH]
#define RSCAN0CFCC4H RSCAN0.CFCC4.UINT16[H]
#define RSCAN0CFCC4HL RSCAN0.CFCC4.UINT8[HL]
#define RSCAN0CFCC4HH RSCAN0.CFCC4.UINT8[HH]
#define RSCAN0CFCC5 RSCAN0.CFCC5.UINT32
#define RSCAN0CFCC5L RSCAN0.CFCC5.UINT16[L]
#define RSCAN0CFCC5LL RSCAN0.CFCC5.UINT8[LL]
#define RSCAN0CFCC5LH RSCAN0.CFCC5.UINT8[LH]
#define RSCAN0CFCC5H RSCAN0.CFCC5.UINT16[H]
#define RSCAN0CFCC5HL RSCAN0.CFCC5.UINT8[HL]
#define RSCAN0CFCC5HH RSCAN0.CFCC5.UINT8[HH]
#define RSCAN0CFCC6 RSCAN0.CFCC6.UINT32
#define RSCAN0CFCC6L RSCAN0.CFCC6.UINT16[L]
#define RSCAN0CFCC6LL RSCAN0.CFCC6.UINT8[LL]
#define RSCAN0CFCC6LH RSCAN0.CFCC6.UINT8[LH]
#define RSCAN0CFCC6H RSCAN0.CFCC6.UINT16[H]
#define RSCAN0CFCC6HL RSCAN0.CFCC6.UINT8[HL]
#define RSCAN0CFCC6HH RSCAN0.CFCC6.UINT8[HH]
#define RSCAN0CFCC7 RSCAN0.CFCC7.UINT32
#define RSCAN0CFCC7L RSCAN0.CFCC7.UINT16[L]
#define RSCAN0CFCC7LL RSCAN0.CFCC7.UINT8[LL]
#define RSCAN0CFCC7LH RSCAN0.CFCC7.UINT8[LH]
#define RSCAN0CFCC7H RSCAN0.CFCC7.UINT16[H]
#define RSCAN0CFCC7HL RSCAN0.CFCC7.UINT8[HL]
#define RSCAN0CFCC7HH RSCAN0.CFCC7.UINT8[HH]
#define RSCAN0CFCC8 RSCAN0.CFCC8.UINT32
#define RSCAN0CFCC8L RSCAN0.CFCC8.UINT16[L]
#define RSCAN0CFCC8LL RSCAN0.CFCC8.UINT8[LL]
#define RSCAN0CFCC8LH RSCAN0.CFCC8.UINT8[LH]
#define RSCAN0CFCC8H RSCAN0.CFCC8.UINT16[H]
#define RSCAN0CFCC8HL RSCAN0.CFCC8.UINT8[HL]
#define RSCAN0CFCC8HH RSCAN0.CFCC8.UINT8[HH]
#define RSCAN0CFCC9 RSCAN0.CFCC9.UINT32
#define RSCAN0CFCC9L RSCAN0.CFCC9.UINT16[L]
#define RSCAN0CFCC9LL RSCAN0.CFCC9.UINT8[LL]
#define RSCAN0CFCC9LH RSCAN0.CFCC9.UINT8[LH]
#define RSCAN0CFCC9H RSCAN0.CFCC9.UINT16[H]
#define RSCAN0CFCC9HL RSCAN0.CFCC9.UINT8[HL]
#define RSCAN0CFCC9HH RSCAN0.CFCC9.UINT8[HH]
#define RSCAN0CFCC10 RSCAN0.CFCC10.UINT32
#define RSCAN0CFCC10L RSCAN0.CFCC10.UINT16[L]
#define RSCAN0CFCC10LL RSCAN0.CFCC10.UINT8[LL]
#define RSCAN0CFCC10LH RSCAN0.CFCC10.UINT8[LH]
#define RSCAN0CFCC10H RSCAN0.CFCC10.UINT16[H]
#define RSCAN0CFCC10HL RSCAN0.CFCC10.UINT8[HL]
#define RSCAN0CFCC10HH RSCAN0.CFCC10.UINT8[HH]
#define RSCAN0CFCC11 RSCAN0.CFCC11.UINT32
#define RSCAN0CFCC11L RSCAN0.CFCC11.UINT16[L]
#define RSCAN0CFCC11LL RSCAN0.CFCC11.UINT8[LL]
#define RSCAN0CFCC11LH RSCAN0.CFCC11.UINT8[LH]
#define RSCAN0CFCC11H RSCAN0.CFCC11.UINT16[H]
#define RSCAN0CFCC11HL RSCAN0.CFCC11.UINT8[HL]
#define RSCAN0CFCC11HH RSCAN0.CFCC11.UINT8[HH]
#define RSCAN0CFCC12 RSCAN0.CFCC12.UINT32
#define RSCAN0CFCC12L RSCAN0.CFCC12.UINT16[L]
#define RSCAN0CFCC12LL RSCAN0.CFCC12.UINT8[LL]
#define RSCAN0CFCC12LH RSCAN0.CFCC12.UINT8[LH]
#define RSCAN0CFCC12H RSCAN0.CFCC12.UINT16[H]
#define RSCAN0CFCC12HL RSCAN0.CFCC12.UINT8[HL]
#define RSCAN0CFCC12HH RSCAN0.CFCC12.UINT8[HH]
#define RSCAN0CFCC13 RSCAN0.CFCC13.UINT32
#define RSCAN0CFCC13L RSCAN0.CFCC13.UINT16[L]
#define RSCAN0CFCC13LL RSCAN0.CFCC13.UINT8[LL]
#define RSCAN0CFCC13LH RSCAN0.CFCC13.UINT8[LH]
#define RSCAN0CFCC13H RSCAN0.CFCC13.UINT16[H]
#define RSCAN0CFCC13HL RSCAN0.CFCC13.UINT8[HL]
#define RSCAN0CFCC13HH RSCAN0.CFCC13.UINT8[HH]
#define RSCAN0CFCC14 RSCAN0.CFCC14.UINT32
#define RSCAN0CFCC14L RSCAN0.CFCC14.UINT16[L]
#define RSCAN0CFCC14LL RSCAN0.CFCC14.UINT8[LL]
#define RSCAN0CFCC14LH RSCAN0.CFCC14.UINT8[LH]
#define RSCAN0CFCC14H RSCAN0.CFCC14.UINT16[H]
#define RSCAN0CFCC14HL RSCAN0.CFCC14.UINT8[HL]
#define RSCAN0CFCC14HH RSCAN0.CFCC14.UINT8[HH]
#define RSCAN0CFSTS0 RSCAN0.CFSTS0.UINT32
#define RSCAN0CFSTS0L RSCAN0.CFSTS0.UINT16[L]
#define RSCAN0CFSTS0LL RSCAN0.CFSTS0.UINT8[LL]
#define RSCAN0CFSTS0LH RSCAN0.CFSTS0.UINT8[LH]
#define RSCAN0CFSTS0H RSCAN0.CFSTS0.UINT16[H]
#define RSCAN0CFSTS0HL RSCAN0.CFSTS0.UINT8[HL]
#define RSCAN0CFSTS0HH RSCAN0.CFSTS0.UINT8[HH]
#define RSCAN0CFSTS1 RSCAN0.CFSTS1.UINT32
#define RSCAN0CFSTS1L RSCAN0.CFSTS1.UINT16[L]
#define RSCAN0CFSTS1LL RSCAN0.CFSTS1.UINT8[LL]
#define RSCAN0CFSTS1LH RSCAN0.CFSTS1.UINT8[LH]
#define RSCAN0CFSTS1H RSCAN0.CFSTS1.UINT16[H]
#define RSCAN0CFSTS1HL RSCAN0.CFSTS1.UINT8[HL]
#define RSCAN0CFSTS1HH RSCAN0.CFSTS1.UINT8[HH]
#define RSCAN0CFSTS2 RSCAN0.CFSTS2.UINT32
#define RSCAN0CFSTS2L RSCAN0.CFSTS2.UINT16[L]
#define RSCAN0CFSTS2LL RSCAN0.CFSTS2.UINT8[LL]
#define RSCAN0CFSTS2LH RSCAN0.CFSTS2.UINT8[LH]
#define RSCAN0CFSTS2H RSCAN0.CFSTS2.UINT16[H]
#define RSCAN0CFSTS2HL RSCAN0.CFSTS2.UINT8[HL]
#define RSCAN0CFSTS2HH RSCAN0.CFSTS2.UINT8[HH]
#define RSCAN0CFSTS3 RSCAN0.CFSTS3.UINT32
#define RSCAN0CFSTS3L RSCAN0.CFSTS3.UINT16[L]
#define RSCAN0CFSTS3LL RSCAN0.CFSTS3.UINT8[LL]
#define RSCAN0CFSTS3LH RSCAN0.CFSTS3.UINT8[LH]
#define RSCAN0CFSTS3H RSCAN0.CFSTS3.UINT16[H]
#define RSCAN0CFSTS3HL RSCAN0.CFSTS3.UINT8[HL]
#define RSCAN0CFSTS3HH RSCAN0.CFSTS3.UINT8[HH]
#define RSCAN0CFSTS4 RSCAN0.CFSTS4.UINT32
#define RSCAN0CFSTS4L RSCAN0.CFSTS4.UINT16[L]
#define RSCAN0CFSTS4LL RSCAN0.CFSTS4.UINT8[LL]
#define RSCAN0CFSTS4LH RSCAN0.CFSTS4.UINT8[LH]
#define RSCAN0CFSTS4H RSCAN0.CFSTS4.UINT16[H]
#define RSCAN0CFSTS4HL RSCAN0.CFSTS4.UINT8[HL]
#define RSCAN0CFSTS4HH RSCAN0.CFSTS4.UINT8[HH]
#define RSCAN0CFSTS5 RSCAN0.CFSTS5.UINT32
#define RSCAN0CFSTS5L RSCAN0.CFSTS5.UINT16[L]
#define RSCAN0CFSTS5LL RSCAN0.CFSTS5.UINT8[LL]
#define RSCAN0CFSTS5LH RSCAN0.CFSTS5.UINT8[LH]
#define RSCAN0CFSTS5H RSCAN0.CFSTS5.UINT16[H]
#define RSCAN0CFSTS5HL RSCAN0.CFSTS5.UINT8[HL]
#define RSCAN0CFSTS5HH RSCAN0.CFSTS5.UINT8[HH]
#define RSCAN0CFSTS6 RSCAN0.CFSTS6.UINT32
#define RSCAN0CFSTS6L RSCAN0.CFSTS6.UINT16[L]
#define RSCAN0CFSTS6LL RSCAN0.CFSTS6.UINT8[LL]
#define RSCAN0CFSTS6LH RSCAN0.CFSTS6.UINT8[LH]
#define RSCAN0CFSTS6H RSCAN0.CFSTS6.UINT16[H]
#define RSCAN0CFSTS6HL RSCAN0.CFSTS6.UINT8[HL]
#define RSCAN0CFSTS6HH RSCAN0.CFSTS6.UINT8[HH]
#define RSCAN0CFSTS7 RSCAN0.CFSTS7.UINT32
#define RSCAN0CFSTS7L RSCAN0.CFSTS7.UINT16[L]
#define RSCAN0CFSTS7LL RSCAN0.CFSTS7.UINT8[LL]
#define RSCAN0CFSTS7LH RSCAN0.CFSTS7.UINT8[LH]
#define RSCAN0CFSTS7H RSCAN0.CFSTS7.UINT16[H]
#define RSCAN0CFSTS7HL RSCAN0.CFSTS7.UINT8[HL]
#define RSCAN0CFSTS7HH RSCAN0.CFSTS7.UINT8[HH]
#define RSCAN0CFSTS8 RSCAN0.CFSTS8.UINT32
#define RSCAN0CFSTS8L RSCAN0.CFSTS8.UINT16[L]
#define RSCAN0CFSTS8LL RSCAN0.CFSTS8.UINT8[LL]
#define RSCAN0CFSTS8LH RSCAN0.CFSTS8.UINT8[LH]
#define RSCAN0CFSTS8H RSCAN0.CFSTS8.UINT16[H]
#define RSCAN0CFSTS8HL RSCAN0.CFSTS8.UINT8[HL]
#define RSCAN0CFSTS8HH RSCAN0.CFSTS8.UINT8[HH]
#define RSCAN0CFSTS9 RSCAN0.CFSTS9.UINT32
#define RSCAN0CFSTS9L RSCAN0.CFSTS9.UINT16[L]
#define RSCAN0CFSTS9LL RSCAN0.CFSTS9.UINT8[LL]
#define RSCAN0CFSTS9LH RSCAN0.CFSTS9.UINT8[LH]
#define RSCAN0CFSTS9H RSCAN0.CFSTS9.UINT16[H]
#define RSCAN0CFSTS9HL RSCAN0.CFSTS9.UINT8[HL]
#define RSCAN0CFSTS9HH RSCAN0.CFSTS9.UINT8[HH]
#define RSCAN0CFSTS10 RSCAN0.CFSTS10.UINT32
#define RSCAN0CFSTS10L RSCAN0.CFSTS10.UINT16[L]
#define RSCAN0CFSTS10LL RSCAN0.CFSTS10.UINT8[LL]
#define RSCAN0CFSTS10LH RSCAN0.CFSTS10.UINT8[LH]
#define RSCAN0CFSTS10H RSCAN0.CFSTS10.UINT16[H]
#define RSCAN0CFSTS10HL RSCAN0.CFSTS10.UINT8[HL]
#define RSCAN0CFSTS10HH RSCAN0.CFSTS10.UINT8[HH]
#define RSCAN0CFSTS11 RSCAN0.CFSTS11.UINT32
#define RSCAN0CFSTS11L RSCAN0.CFSTS11.UINT16[L]
#define RSCAN0CFSTS11LL RSCAN0.CFSTS11.UINT8[LL]
#define RSCAN0CFSTS11LH RSCAN0.CFSTS11.UINT8[LH]
#define RSCAN0CFSTS11H RSCAN0.CFSTS11.UINT16[H]
#define RSCAN0CFSTS11HL RSCAN0.CFSTS11.UINT8[HL]
#define RSCAN0CFSTS11HH RSCAN0.CFSTS11.UINT8[HH]
#define RSCAN0CFSTS12 RSCAN0.CFSTS12.UINT32
#define RSCAN0CFSTS12L RSCAN0.CFSTS12.UINT16[L]
#define RSCAN0CFSTS12LL RSCAN0.CFSTS12.UINT8[LL]
#define RSCAN0CFSTS12LH RSCAN0.CFSTS12.UINT8[LH]
#define RSCAN0CFSTS12H RSCAN0.CFSTS12.UINT16[H]
#define RSCAN0CFSTS12HL RSCAN0.CFSTS12.UINT8[HL]
#define RSCAN0CFSTS12HH RSCAN0.CFSTS12.UINT8[HH]
#define RSCAN0CFSTS13 RSCAN0.CFSTS13.UINT32
#define RSCAN0CFSTS13L RSCAN0.CFSTS13.UINT16[L]
#define RSCAN0CFSTS13LL RSCAN0.CFSTS13.UINT8[LL]
#define RSCAN0CFSTS13LH RSCAN0.CFSTS13.UINT8[LH]
#define RSCAN0CFSTS13H RSCAN0.CFSTS13.UINT16[H]
#define RSCAN0CFSTS13HL RSCAN0.CFSTS13.UINT8[HL]
#define RSCAN0CFSTS13HH RSCAN0.CFSTS13.UINT8[HH]
#define RSCAN0CFSTS14 RSCAN0.CFSTS14.UINT32
#define RSCAN0CFSTS14L RSCAN0.CFSTS14.UINT16[L]
#define RSCAN0CFSTS14LL RSCAN0.CFSTS14.UINT8[LL]
#define RSCAN0CFSTS14LH RSCAN0.CFSTS14.UINT8[LH]
#define RSCAN0CFSTS14H RSCAN0.CFSTS14.UINT16[H]
#define RSCAN0CFSTS14HL RSCAN0.CFSTS14.UINT8[HL]
#define RSCAN0CFSTS14HH RSCAN0.CFSTS14.UINT8[HH]
#define RSCAN0CFPCTR0 RSCAN0.CFPCTR0.UINT32
#define RSCAN0CFPCTR0L RSCAN0.CFPCTR0.UINT16[L]
#define RSCAN0CFPCTR0LL RSCAN0.CFPCTR0.UINT8[LL]
#define RSCAN0CFPCTR0LH RSCAN0.CFPCTR0.UINT8[LH]
#define RSCAN0CFPCTR0H RSCAN0.CFPCTR0.UINT16[H]
#define RSCAN0CFPCTR0HL RSCAN0.CFPCTR0.UINT8[HL]
#define RSCAN0CFPCTR0HH RSCAN0.CFPCTR0.UINT8[HH]
#define RSCAN0CFPCTR1 RSCAN0.CFPCTR1.UINT32
#define RSCAN0CFPCTR1L RSCAN0.CFPCTR1.UINT16[L]
#define RSCAN0CFPCTR1LL RSCAN0.CFPCTR1.UINT8[LL]
#define RSCAN0CFPCTR1LH RSCAN0.CFPCTR1.UINT8[LH]
#define RSCAN0CFPCTR1H RSCAN0.CFPCTR1.UINT16[H]
#define RSCAN0CFPCTR1HL RSCAN0.CFPCTR1.UINT8[HL]
#define RSCAN0CFPCTR1HH RSCAN0.CFPCTR1.UINT8[HH]
#define RSCAN0CFPCTR2 RSCAN0.CFPCTR2.UINT32
#define RSCAN0CFPCTR2L RSCAN0.CFPCTR2.UINT16[L]
#define RSCAN0CFPCTR2LL RSCAN0.CFPCTR2.UINT8[LL]
#define RSCAN0CFPCTR2LH RSCAN0.CFPCTR2.UINT8[LH]
#define RSCAN0CFPCTR2H RSCAN0.CFPCTR2.UINT16[H]
#define RSCAN0CFPCTR2HL RSCAN0.CFPCTR2.UINT8[HL]
#define RSCAN0CFPCTR2HH RSCAN0.CFPCTR2.UINT8[HH]
#define RSCAN0CFPCTR3 RSCAN0.CFPCTR3.UINT32
#define RSCAN0CFPCTR3L RSCAN0.CFPCTR3.UINT16[L]
#define RSCAN0CFPCTR3LL RSCAN0.CFPCTR3.UINT8[LL]
#define RSCAN0CFPCTR3LH RSCAN0.CFPCTR3.UINT8[LH]
#define RSCAN0CFPCTR3H RSCAN0.CFPCTR3.UINT16[H]
#define RSCAN0CFPCTR3HL RSCAN0.CFPCTR3.UINT8[HL]
#define RSCAN0CFPCTR3HH RSCAN0.CFPCTR3.UINT8[HH]
#define RSCAN0CFPCTR4 RSCAN0.CFPCTR4.UINT32
#define RSCAN0CFPCTR4L RSCAN0.CFPCTR4.UINT16[L]
#define RSCAN0CFPCTR4LL RSCAN0.CFPCTR4.UINT8[LL]
#define RSCAN0CFPCTR4LH RSCAN0.CFPCTR4.UINT8[LH]
#define RSCAN0CFPCTR4H RSCAN0.CFPCTR4.UINT16[H]
#define RSCAN0CFPCTR4HL RSCAN0.CFPCTR4.UINT8[HL]
#define RSCAN0CFPCTR4HH RSCAN0.CFPCTR4.UINT8[HH]
#define RSCAN0CFPCTR5 RSCAN0.CFPCTR5.UINT32
#define RSCAN0CFPCTR5L RSCAN0.CFPCTR5.UINT16[L]
#define RSCAN0CFPCTR5LL RSCAN0.CFPCTR5.UINT8[LL]
#define RSCAN0CFPCTR5LH RSCAN0.CFPCTR5.UINT8[LH]
#define RSCAN0CFPCTR5H RSCAN0.CFPCTR5.UINT16[H]
#define RSCAN0CFPCTR5HL RSCAN0.CFPCTR5.UINT8[HL]
#define RSCAN0CFPCTR5HH RSCAN0.CFPCTR5.UINT8[HH]
#define RSCAN0CFPCTR6 RSCAN0.CFPCTR6.UINT32
#define RSCAN0CFPCTR6L RSCAN0.CFPCTR6.UINT16[L]
#define RSCAN0CFPCTR6LL RSCAN0.CFPCTR6.UINT8[LL]
#define RSCAN0CFPCTR6LH RSCAN0.CFPCTR6.UINT8[LH]
#define RSCAN0CFPCTR6H RSCAN0.CFPCTR6.UINT16[H]
#define RSCAN0CFPCTR6HL RSCAN0.CFPCTR6.UINT8[HL]
#define RSCAN0CFPCTR6HH RSCAN0.CFPCTR6.UINT8[HH]
#define RSCAN0CFPCTR7 RSCAN0.CFPCTR7.UINT32
#define RSCAN0CFPCTR7L RSCAN0.CFPCTR7.UINT16[L]
#define RSCAN0CFPCTR7LL RSCAN0.CFPCTR7.UINT8[LL]
#define RSCAN0CFPCTR7LH RSCAN0.CFPCTR7.UINT8[LH]
#define RSCAN0CFPCTR7H RSCAN0.CFPCTR7.UINT16[H]
#define RSCAN0CFPCTR7HL RSCAN0.CFPCTR7.UINT8[HL]
#define RSCAN0CFPCTR7HH RSCAN0.CFPCTR7.UINT8[HH]
#define RSCAN0CFPCTR8 RSCAN0.CFPCTR8.UINT32
#define RSCAN0CFPCTR8L RSCAN0.CFPCTR8.UINT16[L]
#define RSCAN0CFPCTR8LL RSCAN0.CFPCTR8.UINT8[LL]
#define RSCAN0CFPCTR8LH RSCAN0.CFPCTR8.UINT8[LH]
#define RSCAN0CFPCTR8H RSCAN0.CFPCTR8.UINT16[H]
#define RSCAN0CFPCTR8HL RSCAN0.CFPCTR8.UINT8[HL]
#define RSCAN0CFPCTR8HH RSCAN0.CFPCTR8.UINT8[HH]
#define RSCAN0CFPCTR9 RSCAN0.CFPCTR9.UINT32
#define RSCAN0CFPCTR9L RSCAN0.CFPCTR9.UINT16[L]
#define RSCAN0CFPCTR9LL RSCAN0.CFPCTR9.UINT8[LL]
#define RSCAN0CFPCTR9LH RSCAN0.CFPCTR9.UINT8[LH]
#define RSCAN0CFPCTR9H RSCAN0.CFPCTR9.UINT16[H]
#define RSCAN0CFPCTR9HL RSCAN0.CFPCTR9.UINT8[HL]
#define RSCAN0CFPCTR9HH RSCAN0.CFPCTR9.UINT8[HH]
#define RSCAN0CFPCTR10 RSCAN0.CFPCTR10.UINT32
#define RSCAN0CFPCTR10L RSCAN0.CFPCTR10.UINT16[L]
#define RSCAN0CFPCTR10LL RSCAN0.CFPCTR10.UINT8[LL]
#define RSCAN0CFPCTR10LH RSCAN0.CFPCTR10.UINT8[LH]
#define RSCAN0CFPCTR10H RSCAN0.CFPCTR10.UINT16[H]
#define RSCAN0CFPCTR10HL RSCAN0.CFPCTR10.UINT8[HL]
#define RSCAN0CFPCTR10HH RSCAN0.CFPCTR10.UINT8[HH]
#define RSCAN0CFPCTR11 RSCAN0.CFPCTR11.UINT32
#define RSCAN0CFPCTR11L RSCAN0.CFPCTR11.UINT16[L]
#define RSCAN0CFPCTR11LL RSCAN0.CFPCTR11.UINT8[LL]
#define RSCAN0CFPCTR11LH RSCAN0.CFPCTR11.UINT8[LH]
#define RSCAN0CFPCTR11H RSCAN0.CFPCTR11.UINT16[H]
#define RSCAN0CFPCTR11HL RSCAN0.CFPCTR11.UINT8[HL]
#define RSCAN0CFPCTR11HH RSCAN0.CFPCTR11.UINT8[HH]
#define RSCAN0CFPCTR12 RSCAN0.CFPCTR12.UINT32
#define RSCAN0CFPCTR12L RSCAN0.CFPCTR12.UINT16[L]
#define RSCAN0CFPCTR12LL RSCAN0.CFPCTR12.UINT8[LL]
#define RSCAN0CFPCTR12LH RSCAN0.CFPCTR12.UINT8[LH]
#define RSCAN0CFPCTR12H RSCAN0.CFPCTR12.UINT16[H]
#define RSCAN0CFPCTR12HL RSCAN0.CFPCTR12.UINT8[HL]
#define RSCAN0CFPCTR12HH RSCAN0.CFPCTR12.UINT8[HH]
#define RSCAN0CFPCTR13 RSCAN0.CFPCTR13.UINT32
#define RSCAN0CFPCTR13L RSCAN0.CFPCTR13.UINT16[L]
#define RSCAN0CFPCTR13LL RSCAN0.CFPCTR13.UINT8[LL]
#define RSCAN0CFPCTR13LH RSCAN0.CFPCTR13.UINT8[LH]
#define RSCAN0CFPCTR13H RSCAN0.CFPCTR13.UINT16[H]
#define RSCAN0CFPCTR13HL RSCAN0.CFPCTR13.UINT8[HL]
#define RSCAN0CFPCTR13HH RSCAN0.CFPCTR13.UINT8[HH]
#define RSCAN0CFPCTR14 RSCAN0.CFPCTR14.UINT32
#define RSCAN0CFPCTR14L RSCAN0.CFPCTR14.UINT16[L]
#define RSCAN0CFPCTR14LL RSCAN0.CFPCTR14.UINT8[LL]
#define RSCAN0CFPCTR14LH RSCAN0.CFPCTR14.UINT8[LH]
#define RSCAN0CFPCTR14H RSCAN0.CFPCTR14.UINT16[H]
#define RSCAN0CFPCTR14HL RSCAN0.CFPCTR14.UINT8[HL]
#define RSCAN0CFPCTR14HH RSCAN0.CFPCTR14.UINT8[HH]
#define RSCAN0FESTS RSCAN0.FESTS.UINT32
#define RSCAN0FESTSL RSCAN0.FESTS.UINT16[L]
#define RSCAN0FESTSLL RSCAN0.FESTS.UINT8[LL]
#define RSCAN0FESTSLH RSCAN0.FESTS.UINT8[LH]
#define RSCAN0FESTSH RSCAN0.FESTS.UINT16[H]
#define RSCAN0FESTSHL RSCAN0.FESTS.UINT8[HL]
#define RSCAN0FESTSHH RSCAN0.FESTS.UINT8[HH]
#define RSCAN0FFSTS RSCAN0.FFSTS.UINT32
#define RSCAN0FFSTSL RSCAN0.FFSTS.UINT16[L]
#define RSCAN0FFSTSLL RSCAN0.FFSTS.UINT8[LL]
#define RSCAN0FFSTSLH RSCAN0.FFSTS.UINT8[LH]
#define RSCAN0FFSTSH RSCAN0.FFSTS.UINT16[H]
#define RSCAN0FFSTSHL RSCAN0.FFSTS.UINT8[HL]
#define RSCAN0FFSTSHH RSCAN0.FFSTS.UINT8[HH]
#define RSCAN0FMSTS RSCAN0.FMSTS.UINT32
#define RSCAN0FMSTSL RSCAN0.FMSTS.UINT16[L]
#define RSCAN0FMSTSLL RSCAN0.FMSTS.UINT8[LL]
#define RSCAN0FMSTSLH RSCAN0.FMSTS.UINT8[LH]
#define RSCAN0FMSTSH RSCAN0.FMSTS.UINT16[H]
#define RSCAN0FMSTSHL RSCAN0.FMSTS.UINT8[HL]
#define RSCAN0FMSTSHH RSCAN0.FMSTS.UINT8[HH]
#define RSCAN0RFISTS RSCAN0.RFISTS.UINT32
#define RSCAN0RFISTSL RSCAN0.RFISTS.UINT16[L]
#define RSCAN0RFISTSLL RSCAN0.RFISTS.UINT8[LL]
#define RSCAN0RFISTSLH RSCAN0.RFISTS.UINT8[LH]
#define RSCAN0RFISTSH RSCAN0.RFISTS.UINT16[H]
#define RSCAN0RFISTSHL RSCAN0.RFISTS.UINT8[HL]
#define RSCAN0RFISTSHH RSCAN0.RFISTS.UINT8[HH]
#define RSCAN0CFRISTS RSCAN0.CFRISTS.UINT32
#define RSCAN0CFRISTSL RSCAN0.CFRISTS.UINT16[L]
#define RSCAN0CFRISTSLL RSCAN0.CFRISTS.UINT8[LL]
#define RSCAN0CFRISTSLH RSCAN0.CFRISTS.UINT8[LH]
#define RSCAN0CFRISTSH RSCAN0.CFRISTS.UINT16[H]
#define RSCAN0CFRISTSHL RSCAN0.CFRISTS.UINT8[HL]
#define RSCAN0CFRISTSHH RSCAN0.CFRISTS.UINT8[HH]
#define RSCAN0CFTISTS RSCAN0.CFTISTS.UINT32
#define RSCAN0CFTISTSL RSCAN0.CFTISTS.UINT16[L]
#define RSCAN0CFTISTSLL RSCAN0.CFTISTS.UINT8[LL]
#define RSCAN0CFTISTSLH RSCAN0.CFTISTS.UINT8[LH]
#define RSCAN0CFTISTSH RSCAN0.CFTISTS.UINT16[H]
#define RSCAN0CFTISTSHL RSCAN0.CFTISTS.UINT8[HL]
#define RSCAN0CFTISTSHH RSCAN0.CFTISTS.UINT8[HH]
#define RSCAN0TMC0 RSCAN0.TMC0
#define RSCAN0TMC1 RSCAN0.TMC1
#define RSCAN0TMC2 RSCAN0.TMC2
#define RSCAN0TMC3 RSCAN0.TMC3
#define RSCAN0TMC4 RSCAN0.TMC4
#define RSCAN0TMC5 RSCAN0.TMC5
#define RSCAN0TMC6 RSCAN0.TMC6
#define RSCAN0TMC7 RSCAN0.TMC7
#define RSCAN0TMC8 RSCAN0.TMC8
#define RSCAN0TMC9 RSCAN0.TMC9
#define RSCAN0TMC10 RSCAN0.TMC10
#define RSCAN0TMC11 RSCAN0.TMC11
#define RSCAN0TMC12 RSCAN0.TMC12
#define RSCAN0TMC13 RSCAN0.TMC13
#define RSCAN0TMC14 RSCAN0.TMC14
#define RSCAN0TMC15 RSCAN0.TMC15
#define RSCAN0TMC16 RSCAN0.TMC16
#define RSCAN0TMC17 RSCAN0.TMC17
#define RSCAN0TMC18 RSCAN0.TMC18
#define RSCAN0TMC19 RSCAN0.TMC19
#define RSCAN0TMC20 RSCAN0.TMC20
#define RSCAN0TMC21 RSCAN0.TMC21
#define RSCAN0TMC22 RSCAN0.TMC22
#define RSCAN0TMC23 RSCAN0.TMC23
#define RSCAN0TMC24 RSCAN0.TMC24
#define RSCAN0TMC25 RSCAN0.TMC25
#define RSCAN0TMC26 RSCAN0.TMC26
#define RSCAN0TMC27 RSCAN0.TMC27
#define RSCAN0TMC28 RSCAN0.TMC28
#define RSCAN0TMC29 RSCAN0.TMC29
#define RSCAN0TMC30 RSCAN0.TMC30
#define RSCAN0TMC31 RSCAN0.TMC31
#define RSCAN0TMC32 RSCAN0.TMC32
#define RSCAN0TMC33 RSCAN0.TMC33
#define RSCAN0TMC34 RSCAN0.TMC34
#define RSCAN0TMC35 RSCAN0.TMC35
#define RSCAN0TMC36 RSCAN0.TMC36
#define RSCAN0TMC37 RSCAN0.TMC37
#define RSCAN0TMC38 RSCAN0.TMC38
#define RSCAN0TMC39 RSCAN0.TMC39
#define RSCAN0TMC40 RSCAN0.TMC40
#define RSCAN0TMC41 RSCAN0.TMC41
#define RSCAN0TMC42 RSCAN0.TMC42
#define RSCAN0TMC43 RSCAN0.TMC43
#define RSCAN0TMC44 RSCAN0.TMC44
#define RSCAN0TMC45 RSCAN0.TMC45
#define RSCAN0TMC46 RSCAN0.TMC46
#define RSCAN0TMC47 RSCAN0.TMC47
#define RSCAN0TMC48 RSCAN0.TMC48
#define RSCAN0TMC49 RSCAN0.TMC49
#define RSCAN0TMC50 RSCAN0.TMC50
#define RSCAN0TMC51 RSCAN0.TMC51
#define RSCAN0TMC52 RSCAN0.TMC52
#define RSCAN0TMC53 RSCAN0.TMC53
#define RSCAN0TMC54 RSCAN0.TMC54
#define RSCAN0TMC55 RSCAN0.TMC55
#define RSCAN0TMC56 RSCAN0.TMC56
#define RSCAN0TMC57 RSCAN0.TMC57
#define RSCAN0TMC58 RSCAN0.TMC58
#define RSCAN0TMC59 RSCAN0.TMC59
#define RSCAN0TMC60 RSCAN0.TMC60
#define RSCAN0TMC61 RSCAN0.TMC61
#define RSCAN0TMC62 RSCAN0.TMC62
#define RSCAN0TMC63 RSCAN0.TMC63
#define RSCAN0TMC64 RSCAN0.TMC64
#define RSCAN0TMC65 RSCAN0.TMC65
#define RSCAN0TMC66 RSCAN0.TMC66
#define RSCAN0TMC67 RSCAN0.TMC67
#define RSCAN0TMC68 RSCAN0.TMC68
#define RSCAN0TMC69 RSCAN0.TMC69
#define RSCAN0TMC70 RSCAN0.TMC70
#define RSCAN0TMC71 RSCAN0.TMC71
#define RSCAN0TMC72 RSCAN0.TMC72
#define RSCAN0TMC73 RSCAN0.TMC73
#define RSCAN0TMC74 RSCAN0.TMC74
#define RSCAN0TMC75 RSCAN0.TMC75
#define RSCAN0TMC76 RSCAN0.TMC76
#define RSCAN0TMC77 RSCAN0.TMC77
#define RSCAN0TMC78 RSCAN0.TMC78
#define RSCAN0TMC79 RSCAN0.TMC79
#define RSCAN0TMSTS0 RSCAN0.TMSTS0
#define RSCAN0TMSTS1 RSCAN0.TMSTS1
#define RSCAN0TMSTS2 RSCAN0.TMSTS2
#define RSCAN0TMSTS3 RSCAN0.TMSTS3
#define RSCAN0TMSTS4 RSCAN0.TMSTS4
#define RSCAN0TMSTS5 RSCAN0.TMSTS5
#define RSCAN0TMSTS6 RSCAN0.TMSTS6
#define RSCAN0TMSTS7 RSCAN0.TMSTS7
#define RSCAN0TMSTS8 RSCAN0.TMSTS8
#define RSCAN0TMSTS9 RSCAN0.TMSTS9
#define RSCAN0TMSTS10 RSCAN0.TMSTS10
#define RSCAN0TMSTS11 RSCAN0.TMSTS11
#define RSCAN0TMSTS12 RSCAN0.TMSTS12
#define RSCAN0TMSTS13 RSCAN0.TMSTS13
#define RSCAN0TMSTS14 RSCAN0.TMSTS14
#define RSCAN0TMSTS15 RSCAN0.TMSTS15
#define RSCAN0TMSTS16 RSCAN0.TMSTS16
#define RSCAN0TMSTS17 RSCAN0.TMSTS17
#define RSCAN0TMSTS18 RSCAN0.TMSTS18
#define RSCAN0TMSTS19 RSCAN0.TMSTS19
#define RSCAN0TMSTS20 RSCAN0.TMSTS20
#define RSCAN0TMSTS21 RSCAN0.TMSTS21
#define RSCAN0TMSTS22 RSCAN0.TMSTS22
#define RSCAN0TMSTS23 RSCAN0.TMSTS23
#define RSCAN0TMSTS24 RSCAN0.TMSTS24
#define RSCAN0TMSTS25 RSCAN0.TMSTS25
#define RSCAN0TMSTS26 RSCAN0.TMSTS26
#define RSCAN0TMSTS27 RSCAN0.TMSTS27
#define RSCAN0TMSTS28 RSCAN0.TMSTS28
#define RSCAN0TMSTS29 RSCAN0.TMSTS29
#define RSCAN0TMSTS30 RSCAN0.TMSTS30
#define RSCAN0TMSTS31 RSCAN0.TMSTS31
#define RSCAN0TMSTS32 RSCAN0.TMSTS32
#define RSCAN0TMSTS33 RSCAN0.TMSTS33
#define RSCAN0TMSTS34 RSCAN0.TMSTS34
#define RSCAN0TMSTS35 RSCAN0.TMSTS35
#define RSCAN0TMSTS36 RSCAN0.TMSTS36
#define RSCAN0TMSTS37 RSCAN0.TMSTS37
#define RSCAN0TMSTS38 RSCAN0.TMSTS38
#define RSCAN0TMSTS39 RSCAN0.TMSTS39
#define RSCAN0TMSTS40 RSCAN0.TMSTS40
#define RSCAN0TMSTS41 RSCAN0.TMSTS41
#define RSCAN0TMSTS42 RSCAN0.TMSTS42
#define RSCAN0TMSTS43 RSCAN0.TMSTS43
#define RSCAN0TMSTS44 RSCAN0.TMSTS44
#define RSCAN0TMSTS45 RSCAN0.TMSTS45
#define RSCAN0TMSTS46 RSCAN0.TMSTS46
#define RSCAN0TMSTS47 RSCAN0.TMSTS47
#define RSCAN0TMSTS48 RSCAN0.TMSTS48
#define RSCAN0TMSTS49 RSCAN0.TMSTS49
#define RSCAN0TMSTS50 RSCAN0.TMSTS50
#define RSCAN0TMSTS51 RSCAN0.TMSTS51
#define RSCAN0TMSTS52 RSCAN0.TMSTS52
#define RSCAN0TMSTS53 RSCAN0.TMSTS53
#define RSCAN0TMSTS54 RSCAN0.TMSTS54
#define RSCAN0TMSTS55 RSCAN0.TMSTS55
#define RSCAN0TMSTS56 RSCAN0.TMSTS56
#define RSCAN0TMSTS57 RSCAN0.TMSTS57
#define RSCAN0TMSTS58 RSCAN0.TMSTS58
#define RSCAN0TMSTS59 RSCAN0.TMSTS59
#define RSCAN0TMSTS60 RSCAN0.TMSTS60
#define RSCAN0TMSTS61 RSCAN0.TMSTS61
#define RSCAN0TMSTS62 RSCAN0.TMSTS62
#define RSCAN0TMSTS63 RSCAN0.TMSTS63
#define RSCAN0TMSTS64 RSCAN0.TMSTS64
#define RSCAN0TMSTS65 RSCAN0.TMSTS65
#define RSCAN0TMSTS66 RSCAN0.TMSTS66
#define RSCAN0TMSTS67 RSCAN0.TMSTS67
#define RSCAN0TMSTS68 RSCAN0.TMSTS68
#define RSCAN0TMSTS69 RSCAN0.TMSTS69
#define RSCAN0TMSTS70 RSCAN0.TMSTS70
#define RSCAN0TMSTS71 RSCAN0.TMSTS71
#define RSCAN0TMSTS72 RSCAN0.TMSTS72
#define RSCAN0TMSTS73 RSCAN0.TMSTS73
#define RSCAN0TMSTS74 RSCAN0.TMSTS74
#define RSCAN0TMSTS75 RSCAN0.TMSTS75
#define RSCAN0TMSTS76 RSCAN0.TMSTS76
#define RSCAN0TMSTS77 RSCAN0.TMSTS77
#define RSCAN0TMSTS78 RSCAN0.TMSTS78
#define RSCAN0TMSTS79 RSCAN0.TMSTS79
#define RSCAN0TMTRSTS0 RSCAN0.TMTRSTS0.UINT32
#define RSCAN0TMTRSTS0L RSCAN0.TMTRSTS0.UINT16[L]
#define RSCAN0TMTRSTS0LL RSCAN0.TMTRSTS0.UINT8[LL]
#define RSCAN0TMTRSTS0LH RSCAN0.TMTRSTS0.UINT8[LH]
#define RSCAN0TMTRSTS0H RSCAN0.TMTRSTS0.UINT16[H]
#define RSCAN0TMTRSTS0HL RSCAN0.TMTRSTS0.UINT8[HL]
#define RSCAN0TMTRSTS0HH RSCAN0.TMTRSTS0.UINT8[HH]
#define RSCAN0TMTRSTS1 RSCAN0.TMTRSTS1.UINT32
#define RSCAN0TMTRSTS1L RSCAN0.TMTRSTS1.UINT16[L]
#define RSCAN0TMTRSTS1LL RSCAN0.TMTRSTS1.UINT8[LL]
#define RSCAN0TMTRSTS1LH RSCAN0.TMTRSTS1.UINT8[LH]
#define RSCAN0TMTRSTS1H RSCAN0.TMTRSTS1.UINT16[H]
#define RSCAN0TMTRSTS1HL RSCAN0.TMTRSTS1.UINT8[HL]
#define RSCAN0TMTRSTS1HH RSCAN0.TMTRSTS1.UINT8[HH]
#define RSCAN0TMTRSTS2 RSCAN0.TMTRSTS2.UINT32
#define RSCAN0TMTRSTS2L RSCAN0.TMTRSTS2.UINT16[L]
#define RSCAN0TMTRSTS2LL RSCAN0.TMTRSTS2.UINT8[LL]
#define RSCAN0TMTRSTS2LH RSCAN0.TMTRSTS2.UINT8[LH]
#define RSCAN0TMTRSTS2H RSCAN0.TMTRSTS2.UINT16[H]
#define RSCAN0TMTRSTS2HL RSCAN0.TMTRSTS2.UINT8[HL]
#define RSCAN0TMTRSTS2HH RSCAN0.TMTRSTS2.UINT8[HH]
#define RSCAN0TMTARSTS0 RSCAN0.TMTARSTS0.UINT32
#define RSCAN0TMTARSTS0L RSCAN0.TMTARSTS0.UINT16[L]
#define RSCAN0TMTARSTS0LL RSCAN0.TMTARSTS0.UINT8[LL]
#define RSCAN0TMTARSTS0LH RSCAN0.TMTARSTS0.UINT8[LH]
#define RSCAN0TMTARSTS0H RSCAN0.TMTARSTS0.UINT16[H]
#define RSCAN0TMTARSTS0HL RSCAN0.TMTARSTS0.UINT8[HL]
#define RSCAN0TMTARSTS0HH RSCAN0.TMTARSTS0.UINT8[HH]
#define RSCAN0TMTARSTS1 RSCAN0.TMTARSTS1.UINT32
#define RSCAN0TMTARSTS1L RSCAN0.TMTARSTS1.UINT16[L]
#define RSCAN0TMTARSTS1LL RSCAN0.TMTARSTS1.UINT8[LL]
#define RSCAN0TMTARSTS1LH RSCAN0.TMTARSTS1.UINT8[LH]
#define RSCAN0TMTARSTS1H RSCAN0.TMTARSTS1.UINT16[H]
#define RSCAN0TMTARSTS1HL RSCAN0.TMTARSTS1.UINT8[HL]
#define RSCAN0TMTARSTS1HH RSCAN0.TMTARSTS1.UINT8[HH]
#define RSCAN0TMTARSTS2 RSCAN0.TMTARSTS2.UINT32
#define RSCAN0TMTARSTS2L RSCAN0.TMTARSTS2.UINT16[L]
#define RSCAN0TMTARSTS2LL RSCAN0.TMTARSTS2.UINT8[LL]
#define RSCAN0TMTARSTS2LH RSCAN0.TMTARSTS2.UINT8[LH]
#define RSCAN0TMTARSTS2H RSCAN0.TMTARSTS2.UINT16[H]
#define RSCAN0TMTARSTS2HL RSCAN0.TMTARSTS2.UINT8[HL]
#define RSCAN0TMTARSTS2HH RSCAN0.TMTARSTS2.UINT8[HH]
#define RSCAN0TMTCSTS0 RSCAN0.TMTCSTS0.UINT32
#define RSCAN0TMTCSTS0L RSCAN0.TMTCSTS0.UINT16[L]
#define RSCAN0TMTCSTS0LL RSCAN0.TMTCSTS0.UINT8[LL]
#define RSCAN0TMTCSTS0LH RSCAN0.TMTCSTS0.UINT8[LH]
#define RSCAN0TMTCSTS0H RSCAN0.TMTCSTS0.UINT16[H]
#define RSCAN0TMTCSTS0HL RSCAN0.TMTCSTS0.UINT8[HL]
#define RSCAN0TMTCSTS0HH RSCAN0.TMTCSTS0.UINT8[HH]
#define RSCAN0TMTCSTS1 RSCAN0.TMTCSTS1.UINT32
#define RSCAN0TMTCSTS1L RSCAN0.TMTCSTS1.UINT16[L]
#define RSCAN0TMTCSTS1LL RSCAN0.TMTCSTS1.UINT8[LL]
#define RSCAN0TMTCSTS1LH RSCAN0.TMTCSTS1.UINT8[LH]
#define RSCAN0TMTCSTS1H RSCAN0.TMTCSTS1.UINT16[H]
#define RSCAN0TMTCSTS1HL RSCAN0.TMTCSTS1.UINT8[HL]
#define RSCAN0TMTCSTS1HH RSCAN0.TMTCSTS1.UINT8[HH]
#define RSCAN0TMTCSTS2 RSCAN0.TMTCSTS2.UINT32
#define RSCAN0TMTCSTS2L RSCAN0.TMTCSTS2.UINT16[L]
#define RSCAN0TMTCSTS2LL RSCAN0.TMTCSTS2.UINT8[LL]
#define RSCAN0TMTCSTS2LH RSCAN0.TMTCSTS2.UINT8[LH]
#define RSCAN0TMTCSTS2H RSCAN0.TMTCSTS2.UINT16[H]
#define RSCAN0TMTCSTS2HL RSCAN0.TMTCSTS2.UINT8[HL]
#define RSCAN0TMTCSTS2HH RSCAN0.TMTCSTS2.UINT8[HH]
#define RSCAN0TMTASTS0 RSCAN0.TMTASTS0.UINT32
#define RSCAN0TMTASTS0L RSCAN0.TMTASTS0.UINT16[L]
#define RSCAN0TMTASTS0LL RSCAN0.TMTASTS0.UINT8[LL]
#define RSCAN0TMTASTS0LH RSCAN0.TMTASTS0.UINT8[LH]
#define RSCAN0TMTASTS0H RSCAN0.TMTASTS0.UINT16[H]
#define RSCAN0TMTASTS0HL RSCAN0.TMTASTS0.UINT8[HL]
#define RSCAN0TMTASTS0HH RSCAN0.TMTASTS0.UINT8[HH]
#define RSCAN0TMTASTS1 RSCAN0.TMTASTS1.UINT32
#define RSCAN0TMTASTS1L RSCAN0.TMTASTS1.UINT16[L]
#define RSCAN0TMTASTS1LL RSCAN0.TMTASTS1.UINT8[LL]
#define RSCAN0TMTASTS1LH RSCAN0.TMTASTS1.UINT8[LH]
#define RSCAN0TMTASTS1H RSCAN0.TMTASTS1.UINT16[H]
#define RSCAN0TMTASTS1HL RSCAN0.TMTASTS1.UINT8[HL]
#define RSCAN0TMTASTS1HH RSCAN0.TMTASTS1.UINT8[HH]
#define RSCAN0TMTASTS2 RSCAN0.TMTASTS2.UINT32
#define RSCAN0TMTASTS2L RSCAN0.TMTASTS2.UINT16[L]
#define RSCAN0TMTASTS2LL RSCAN0.TMTASTS2.UINT8[LL]
#define RSCAN0TMTASTS2LH RSCAN0.TMTASTS2.UINT8[LH]
#define RSCAN0TMTASTS2H RSCAN0.TMTASTS2.UINT16[H]
#define RSCAN0TMTASTS2HL RSCAN0.TMTASTS2.UINT8[HL]
#define RSCAN0TMTASTS2HH RSCAN0.TMTASTS2.UINT8[HH]
#define RSCAN0TMIEC0 RSCAN0.TMIEC0.UINT32
#define RSCAN0TMIEC0L RSCAN0.TMIEC0.UINT16[L]
#define RSCAN0TMIEC0LL RSCAN0.TMIEC0.UINT8[LL]
#define RSCAN0TMIEC0LH RSCAN0.TMIEC0.UINT8[LH]
#define RSCAN0TMIEC0H RSCAN0.TMIEC0.UINT16[H]
#define RSCAN0TMIEC0HL RSCAN0.TMIEC0.UINT8[HL]
#define RSCAN0TMIEC0HH RSCAN0.TMIEC0.UINT8[HH]
#define RSCAN0TMIEC1 RSCAN0.TMIEC1.UINT32
#define RSCAN0TMIEC1L RSCAN0.TMIEC1.UINT16[L]
#define RSCAN0TMIEC1LL RSCAN0.TMIEC1.UINT8[LL]
#define RSCAN0TMIEC1LH RSCAN0.TMIEC1.UINT8[LH]
#define RSCAN0TMIEC1H RSCAN0.TMIEC1.UINT16[H]
#define RSCAN0TMIEC1HL RSCAN0.TMIEC1.UINT8[HL]
#define RSCAN0TMIEC1HH RSCAN0.TMIEC1.UINT8[HH]
#define RSCAN0TMIEC2 RSCAN0.TMIEC2.UINT32
#define RSCAN0TMIEC2L RSCAN0.TMIEC2.UINT16[L]
#define RSCAN0TMIEC2LL RSCAN0.TMIEC2.UINT8[LL]
#define RSCAN0TMIEC2LH RSCAN0.TMIEC2.UINT8[LH]
#define RSCAN0TMIEC2H RSCAN0.TMIEC2.UINT16[H]
#define RSCAN0TMIEC2HL RSCAN0.TMIEC2.UINT8[HL]
#define RSCAN0TMIEC2HH RSCAN0.TMIEC2.UINT8[HH]
#define RSCAN0TXQCC0 RSCAN0.TXQCC0.UINT32
#define RSCAN0TXQCC0L RSCAN0.TXQCC0.UINT16[L]
#define RSCAN0TXQCC0LL RSCAN0.TXQCC0.UINT8[LL]
#define RSCAN0TXQCC0LH RSCAN0.TXQCC0.UINT8[LH]
#define RSCAN0TXQCC0H RSCAN0.TXQCC0.UINT16[H]
#define RSCAN0TXQCC0HL RSCAN0.TXQCC0.UINT8[HL]
#define RSCAN0TXQCC0HH RSCAN0.TXQCC0.UINT8[HH]
#define RSCAN0TXQCC1 RSCAN0.TXQCC1.UINT32
#define RSCAN0TXQCC1L RSCAN0.TXQCC1.UINT16[L]
#define RSCAN0TXQCC1LL RSCAN0.TXQCC1.UINT8[LL]
#define RSCAN0TXQCC1LH RSCAN0.TXQCC1.UINT8[LH]
#define RSCAN0TXQCC1H RSCAN0.TXQCC1.UINT16[H]
#define RSCAN0TXQCC1HL RSCAN0.TXQCC1.UINT8[HL]
#define RSCAN0TXQCC1HH RSCAN0.TXQCC1.UINT8[HH]
#define RSCAN0TXQCC2 RSCAN0.TXQCC2.UINT32
#define RSCAN0TXQCC2L RSCAN0.TXQCC2.UINT16[L]
#define RSCAN0TXQCC2LL RSCAN0.TXQCC2.UINT8[LL]
#define RSCAN0TXQCC2LH RSCAN0.TXQCC2.UINT8[LH]
#define RSCAN0TXQCC2H RSCAN0.TXQCC2.UINT16[H]
#define RSCAN0TXQCC2HL RSCAN0.TXQCC2.UINT8[HL]
#define RSCAN0TXQCC2HH RSCAN0.TXQCC2.UINT8[HH]
#define RSCAN0TXQCC3 RSCAN0.TXQCC3.UINT32
#define RSCAN0TXQCC3L RSCAN0.TXQCC3.UINT16[L]
#define RSCAN0TXQCC3LL RSCAN0.TXQCC3.UINT8[LL]
#define RSCAN0TXQCC3LH RSCAN0.TXQCC3.UINT8[LH]
#define RSCAN0TXQCC3H RSCAN0.TXQCC3.UINT16[H]
#define RSCAN0TXQCC3HL RSCAN0.TXQCC3.UINT8[HL]
#define RSCAN0TXQCC3HH RSCAN0.TXQCC3.UINT8[HH]
#define RSCAN0TXQCC4 RSCAN0.TXQCC4.UINT32
#define RSCAN0TXQCC4L RSCAN0.TXQCC4.UINT16[L]
#define RSCAN0TXQCC4LL RSCAN0.TXQCC4.UINT8[LL]
#define RSCAN0TXQCC4LH RSCAN0.TXQCC4.UINT8[LH]
#define RSCAN0TXQCC4H RSCAN0.TXQCC4.UINT16[H]
#define RSCAN0TXQCC4HL RSCAN0.TXQCC4.UINT8[HL]
#define RSCAN0TXQCC4HH RSCAN0.TXQCC4.UINT8[HH]
#define RSCAN0TXQSTS0 RSCAN0.TXQSTS0.UINT32
#define RSCAN0TXQSTS0L RSCAN0.TXQSTS0.UINT16[L]
#define RSCAN0TXQSTS0LL RSCAN0.TXQSTS0.UINT8[LL]
#define RSCAN0TXQSTS0LH RSCAN0.TXQSTS0.UINT8[LH]
#define RSCAN0TXQSTS0H RSCAN0.TXQSTS0.UINT16[H]
#define RSCAN0TXQSTS0HL RSCAN0.TXQSTS0.UINT8[HL]
#define RSCAN0TXQSTS0HH RSCAN0.TXQSTS0.UINT8[HH]
#define RSCAN0TXQSTS1 RSCAN0.TXQSTS1.UINT32
#define RSCAN0TXQSTS1L RSCAN0.TXQSTS1.UINT16[L]
#define RSCAN0TXQSTS1LL RSCAN0.TXQSTS1.UINT8[LL]
#define RSCAN0TXQSTS1LH RSCAN0.TXQSTS1.UINT8[LH]
#define RSCAN0TXQSTS1H RSCAN0.TXQSTS1.UINT16[H]
#define RSCAN0TXQSTS1HL RSCAN0.TXQSTS1.UINT8[HL]
#define RSCAN0TXQSTS1HH RSCAN0.TXQSTS1.UINT8[HH]
#define RSCAN0TXQSTS2 RSCAN0.TXQSTS2.UINT32
#define RSCAN0TXQSTS2L RSCAN0.TXQSTS2.UINT16[L]
#define RSCAN0TXQSTS2LL RSCAN0.TXQSTS2.UINT8[LL]
#define RSCAN0TXQSTS2LH RSCAN0.TXQSTS2.UINT8[LH]
#define RSCAN0TXQSTS2H RSCAN0.TXQSTS2.UINT16[H]
#define RSCAN0TXQSTS2HL RSCAN0.TXQSTS2.UINT8[HL]
#define RSCAN0TXQSTS2HH RSCAN0.TXQSTS2.UINT8[HH]
#define RSCAN0TXQSTS3 RSCAN0.TXQSTS3.UINT32
#define RSCAN0TXQSTS3L RSCAN0.TXQSTS3.UINT16[L]
#define RSCAN0TXQSTS3LL RSCAN0.TXQSTS3.UINT8[LL]
#define RSCAN0TXQSTS3LH RSCAN0.TXQSTS3.UINT8[LH]
#define RSCAN0TXQSTS3H RSCAN0.TXQSTS3.UINT16[H]
#define RSCAN0TXQSTS3HL RSCAN0.TXQSTS3.UINT8[HL]
#define RSCAN0TXQSTS3HH RSCAN0.TXQSTS3.UINT8[HH]
#define RSCAN0TXQSTS4 RSCAN0.TXQSTS4.UINT32
#define RSCAN0TXQSTS4L RSCAN0.TXQSTS4.UINT16[L]
#define RSCAN0TXQSTS4LL RSCAN0.TXQSTS4.UINT8[LL]
#define RSCAN0TXQSTS4LH RSCAN0.TXQSTS4.UINT8[LH]
#define RSCAN0TXQSTS4H RSCAN0.TXQSTS4.UINT16[H]
#define RSCAN0TXQSTS4HL RSCAN0.TXQSTS4.UINT8[HL]
#define RSCAN0TXQSTS4HH RSCAN0.TXQSTS4.UINT8[HH]
#define RSCAN0TXQPCTR0 RSCAN0.TXQPCTR0.UINT32
#define RSCAN0TXQPCTR0L RSCAN0.TXQPCTR0.UINT16[L]
#define RSCAN0TXQPCTR0LL RSCAN0.TXQPCTR0.UINT8[LL]
#define RSCAN0TXQPCTR0LH RSCAN0.TXQPCTR0.UINT8[LH]
#define RSCAN0TXQPCTR0H RSCAN0.TXQPCTR0.UINT16[H]
#define RSCAN0TXQPCTR0HL RSCAN0.TXQPCTR0.UINT8[HL]
#define RSCAN0TXQPCTR0HH RSCAN0.TXQPCTR0.UINT8[HH]
#define RSCAN0TXQPCTR1 RSCAN0.TXQPCTR1.UINT32
#define RSCAN0TXQPCTR1L RSCAN0.TXQPCTR1.UINT16[L]
#define RSCAN0TXQPCTR1LL RSCAN0.TXQPCTR1.UINT8[LL]
#define RSCAN0TXQPCTR1LH RSCAN0.TXQPCTR1.UINT8[LH]
#define RSCAN0TXQPCTR1H RSCAN0.TXQPCTR1.UINT16[H]
#define RSCAN0TXQPCTR1HL RSCAN0.TXQPCTR1.UINT8[HL]
#define RSCAN0TXQPCTR1HH RSCAN0.TXQPCTR1.UINT8[HH]
#define RSCAN0TXQPCTR2 RSCAN0.TXQPCTR2.UINT32
#define RSCAN0TXQPCTR2L RSCAN0.TXQPCTR2.UINT16[L]
#define RSCAN0TXQPCTR2LL RSCAN0.TXQPCTR2.UINT8[LL]
#define RSCAN0TXQPCTR2LH RSCAN0.TXQPCTR2.UINT8[LH]
#define RSCAN0TXQPCTR2H RSCAN0.TXQPCTR2.UINT16[H]
#define RSCAN0TXQPCTR2HL RSCAN0.TXQPCTR2.UINT8[HL]
#define RSCAN0TXQPCTR2HH RSCAN0.TXQPCTR2.UINT8[HH]
#define RSCAN0TXQPCTR3 RSCAN0.TXQPCTR3.UINT32
#define RSCAN0TXQPCTR3L RSCAN0.TXQPCTR3.UINT16[L]
#define RSCAN0TXQPCTR3LL RSCAN0.TXQPCTR3.UINT8[LL]
#define RSCAN0TXQPCTR3LH RSCAN0.TXQPCTR3.UINT8[LH]
#define RSCAN0TXQPCTR3H RSCAN0.TXQPCTR3.UINT16[H]
#define RSCAN0TXQPCTR3HL RSCAN0.TXQPCTR3.UINT8[HL]
#define RSCAN0TXQPCTR3HH RSCAN0.TXQPCTR3.UINT8[HH]
#define RSCAN0TXQPCTR4 RSCAN0.TXQPCTR4.UINT32
#define RSCAN0TXQPCTR4L RSCAN0.TXQPCTR4.UINT16[L]
#define RSCAN0TXQPCTR4LL RSCAN0.TXQPCTR4.UINT8[LL]
#define RSCAN0TXQPCTR4LH RSCAN0.TXQPCTR4.UINT8[LH]
#define RSCAN0TXQPCTR4H RSCAN0.TXQPCTR4.UINT16[H]
#define RSCAN0TXQPCTR4HL RSCAN0.TXQPCTR4.UINT8[HL]
#define RSCAN0TXQPCTR4HH RSCAN0.TXQPCTR4.UINT8[HH]
#define RSCAN0THLCC0 RSCAN0.THLCC0.UINT32
#define RSCAN0THLCC0L RSCAN0.THLCC0.UINT16[L]
#define RSCAN0THLCC0LL RSCAN0.THLCC0.UINT8[LL]
#define RSCAN0THLCC0LH RSCAN0.THLCC0.UINT8[LH]
#define RSCAN0THLCC0H RSCAN0.THLCC0.UINT16[H]
#define RSCAN0THLCC0HL RSCAN0.THLCC0.UINT8[HL]
#define RSCAN0THLCC0HH RSCAN0.THLCC0.UINT8[HH]
#define RSCAN0THLCC1 RSCAN0.THLCC1.UINT32
#define RSCAN0THLCC1L RSCAN0.THLCC1.UINT16[L]
#define RSCAN0THLCC1LL RSCAN0.THLCC1.UINT8[LL]
#define RSCAN0THLCC1LH RSCAN0.THLCC1.UINT8[LH]
#define RSCAN0THLCC1H RSCAN0.THLCC1.UINT16[H]
#define RSCAN0THLCC1HL RSCAN0.THLCC1.UINT8[HL]
#define RSCAN0THLCC1HH RSCAN0.THLCC1.UINT8[HH]
#define RSCAN0THLCC2 RSCAN0.THLCC2.UINT32
#define RSCAN0THLCC2L RSCAN0.THLCC2.UINT16[L]
#define RSCAN0THLCC2LL RSCAN0.THLCC2.UINT8[LL]
#define RSCAN0THLCC2LH RSCAN0.THLCC2.UINT8[LH]
#define RSCAN0THLCC2H RSCAN0.THLCC2.UINT16[H]
#define RSCAN0THLCC2HL RSCAN0.THLCC2.UINT8[HL]
#define RSCAN0THLCC2HH RSCAN0.THLCC2.UINT8[HH]
#define RSCAN0THLCC3 RSCAN0.THLCC3.UINT32
#define RSCAN0THLCC3L RSCAN0.THLCC3.UINT16[L]
#define RSCAN0THLCC3LL RSCAN0.THLCC3.UINT8[LL]
#define RSCAN0THLCC3LH RSCAN0.THLCC3.UINT8[LH]
#define RSCAN0THLCC3H RSCAN0.THLCC3.UINT16[H]
#define RSCAN0THLCC3HL RSCAN0.THLCC3.UINT8[HL]
#define RSCAN0THLCC3HH RSCAN0.THLCC3.UINT8[HH]
#define RSCAN0THLCC4 RSCAN0.THLCC4.UINT32
#define RSCAN0THLCC4L RSCAN0.THLCC4.UINT16[L]
#define RSCAN0THLCC4LL RSCAN0.THLCC4.UINT8[LL]
#define RSCAN0THLCC4LH RSCAN0.THLCC4.UINT8[LH]
#define RSCAN0THLCC4H RSCAN0.THLCC4.UINT16[H]
#define RSCAN0THLCC4HL RSCAN0.THLCC4.UINT8[HL]
#define RSCAN0THLCC4HH RSCAN0.THLCC4.UINT8[HH]
#define RSCAN0THLSTS0 RSCAN0.THLSTS0.UINT32
#define RSCAN0THLSTS0L RSCAN0.THLSTS0.UINT16[L]
#define RSCAN0THLSTS0LL RSCAN0.THLSTS0.UINT8[LL]
#define RSCAN0THLSTS0LH RSCAN0.THLSTS0.UINT8[LH]
#define RSCAN0THLSTS0H RSCAN0.THLSTS0.UINT16[H]
#define RSCAN0THLSTS0HL RSCAN0.THLSTS0.UINT8[HL]
#define RSCAN0THLSTS0HH RSCAN0.THLSTS0.UINT8[HH]
#define RSCAN0THLSTS1 RSCAN0.THLSTS1.UINT32
#define RSCAN0THLSTS1L RSCAN0.THLSTS1.UINT16[L]
#define RSCAN0THLSTS1LL RSCAN0.THLSTS1.UINT8[LL]
#define RSCAN0THLSTS1LH RSCAN0.THLSTS1.UINT8[LH]
#define RSCAN0THLSTS1H RSCAN0.THLSTS1.UINT16[H]
#define RSCAN0THLSTS1HL RSCAN0.THLSTS1.UINT8[HL]
#define RSCAN0THLSTS1HH RSCAN0.THLSTS1.UINT8[HH]
#define RSCAN0THLSTS2 RSCAN0.THLSTS2.UINT32
#define RSCAN0THLSTS2L RSCAN0.THLSTS2.UINT16[L]
#define RSCAN0THLSTS2LL RSCAN0.THLSTS2.UINT8[LL]
#define RSCAN0THLSTS2LH RSCAN0.THLSTS2.UINT8[LH]
#define RSCAN0THLSTS2H RSCAN0.THLSTS2.UINT16[H]
#define RSCAN0THLSTS2HL RSCAN0.THLSTS2.UINT8[HL]
#define RSCAN0THLSTS2HH RSCAN0.THLSTS2.UINT8[HH]
#define RSCAN0THLSTS3 RSCAN0.THLSTS3.UINT32
#define RSCAN0THLSTS3L RSCAN0.THLSTS3.UINT16[L]
#define RSCAN0THLSTS3LL RSCAN0.THLSTS3.UINT8[LL]
#define RSCAN0THLSTS3LH RSCAN0.THLSTS3.UINT8[LH]
#define RSCAN0THLSTS3H RSCAN0.THLSTS3.UINT16[H]
#define RSCAN0THLSTS3HL RSCAN0.THLSTS3.UINT8[HL]
#define RSCAN0THLSTS3HH RSCAN0.THLSTS3.UINT8[HH]
#define RSCAN0THLSTS4 RSCAN0.THLSTS4.UINT32
#define RSCAN0THLSTS4L RSCAN0.THLSTS4.UINT16[L]
#define RSCAN0THLSTS4LL RSCAN0.THLSTS4.UINT8[LL]
#define RSCAN0THLSTS4LH RSCAN0.THLSTS4.UINT8[LH]
#define RSCAN0THLSTS4H RSCAN0.THLSTS4.UINT16[H]
#define RSCAN0THLSTS4HL RSCAN0.THLSTS4.UINT8[HL]
#define RSCAN0THLSTS4HH RSCAN0.THLSTS4.UINT8[HH]
#define RSCAN0THLPCTR0 RSCAN0.THLPCTR0.UINT32
#define RSCAN0THLPCTR0L RSCAN0.THLPCTR0.UINT16[L]
#define RSCAN0THLPCTR0LL RSCAN0.THLPCTR0.UINT8[LL]
#define RSCAN0THLPCTR0LH RSCAN0.THLPCTR0.UINT8[LH]
#define RSCAN0THLPCTR0H RSCAN0.THLPCTR0.UINT16[H]
#define RSCAN0THLPCTR0HL RSCAN0.THLPCTR0.UINT8[HL]
#define RSCAN0THLPCTR0HH RSCAN0.THLPCTR0.UINT8[HH]
#define RSCAN0THLPCTR1 RSCAN0.THLPCTR1.UINT32
#define RSCAN0THLPCTR1L RSCAN0.THLPCTR1.UINT16[L]
#define RSCAN0THLPCTR1LL RSCAN0.THLPCTR1.UINT8[LL]
#define RSCAN0THLPCTR1LH RSCAN0.THLPCTR1.UINT8[LH]
#define RSCAN0THLPCTR1H RSCAN0.THLPCTR1.UINT16[H]
#define RSCAN0THLPCTR1HL RSCAN0.THLPCTR1.UINT8[HL]
#define RSCAN0THLPCTR1HH RSCAN0.THLPCTR1.UINT8[HH]
#define RSCAN0THLPCTR2 RSCAN0.THLPCTR2.UINT32
#define RSCAN0THLPCTR2L RSCAN0.THLPCTR2.UINT16[L]
#define RSCAN0THLPCTR2LL RSCAN0.THLPCTR2.UINT8[LL]
#define RSCAN0THLPCTR2LH RSCAN0.THLPCTR2.UINT8[LH]
#define RSCAN0THLPCTR2H RSCAN0.THLPCTR2.UINT16[H]
#define RSCAN0THLPCTR2HL RSCAN0.THLPCTR2.UINT8[HL]
#define RSCAN0THLPCTR2HH RSCAN0.THLPCTR2.UINT8[HH]
#define RSCAN0THLPCTR3 RSCAN0.THLPCTR3.UINT32
#define RSCAN0THLPCTR3L RSCAN0.THLPCTR3.UINT16[L]
#define RSCAN0THLPCTR3LL RSCAN0.THLPCTR3.UINT8[LL]
#define RSCAN0THLPCTR3LH RSCAN0.THLPCTR3.UINT8[LH]
#define RSCAN0THLPCTR3H RSCAN0.THLPCTR3.UINT16[H]
#define RSCAN0THLPCTR3HL RSCAN0.THLPCTR3.UINT8[HL]
#define RSCAN0THLPCTR3HH RSCAN0.THLPCTR3.UINT8[HH]
#define RSCAN0THLPCTR4 RSCAN0.THLPCTR4.UINT32
#define RSCAN0THLPCTR4L RSCAN0.THLPCTR4.UINT16[L]
#define RSCAN0THLPCTR4LL RSCAN0.THLPCTR4.UINT8[LL]
#define RSCAN0THLPCTR4LH RSCAN0.THLPCTR4.UINT8[LH]
#define RSCAN0THLPCTR4H RSCAN0.THLPCTR4.UINT16[H]
#define RSCAN0THLPCTR4HL RSCAN0.THLPCTR4.UINT8[HL]
#define RSCAN0THLPCTR4HH RSCAN0.THLPCTR4.UINT8[HH]
#define RSCAN0GTINTSTS0 RSCAN0.GTINTSTS0.UINT32
#define RSCAN0GTINTSTS0L RSCAN0.GTINTSTS0.UINT16[L]
#define RSCAN0GTINTSTS0LL RSCAN0.GTINTSTS0.UINT8[LL]
#define RSCAN0GTINTSTS0LH RSCAN0.GTINTSTS0.UINT8[LH]
#define RSCAN0GTINTSTS0H RSCAN0.GTINTSTS0.UINT16[H]
#define RSCAN0GTINTSTS0HL RSCAN0.GTINTSTS0.UINT8[HL]
#define RSCAN0GTINTSTS0HH RSCAN0.GTINTSTS0.UINT8[HH]
#define RSCAN0GTINTSTS1 RSCAN0.GTINTSTS1.UINT32
#define RSCAN0GTINTSTS1L RSCAN0.GTINTSTS1.UINT16[L]
#define RSCAN0GTINTSTS1LL RSCAN0.GTINTSTS1.UINT8[LL]
#define RSCAN0GTINTSTS1LH RSCAN0.GTINTSTS1.UINT8[LH]
#define RSCAN0GTINTSTS1H RSCAN0.GTINTSTS1.UINT16[H]
#define RSCAN0GTINTSTS1HL RSCAN0.GTINTSTS1.UINT8[HL]
#define RSCAN0GTINTSTS1HH RSCAN0.GTINTSTS1.UINT8[HH]
#define RSCAN0GTSTCFG RSCAN0.GTSTCFG.UINT32
#define RSCAN0GTSTCFGL RSCAN0.GTSTCFG.UINT16[L]
#define RSCAN0GTSTCFGLL RSCAN0.GTSTCFG.UINT8[LL]
#define RSCAN0GTSTCFGLH RSCAN0.GTSTCFG.UINT8[LH]
#define RSCAN0GTSTCFGH RSCAN0.GTSTCFG.UINT16[H]
#define RSCAN0GTSTCFGHL RSCAN0.GTSTCFG.UINT8[HL]
#define RSCAN0GTSTCFGHH RSCAN0.GTSTCFG.UINT8[HH]
#define RSCAN0GTSTCTR RSCAN0.GTSTCTR.UINT32
#define RSCAN0GTSTCTRL RSCAN0.GTSTCTR.UINT16[L]
#define RSCAN0GTSTCTRLL RSCAN0.GTSTCTR.UINT8[LL]
#define RSCAN0GTSTCTRLH RSCAN0.GTSTCTR.UINT8[LH]
#define RSCAN0GTSTCTRH RSCAN0.GTSTCTR.UINT16[H]
#define RSCAN0GTSTCTRHL RSCAN0.GTSTCTR.UINT8[HL]
#define RSCAN0GTSTCTRHH RSCAN0.GTSTCTR.UINT8[HH]
#define RSCAN0GLOCKK RSCAN0.GLOCKK.UINT32
#define RSCAN0GLOCKKL RSCAN0.GLOCKK.UINT16[L]
#define RSCAN0GLOCKKH RSCAN0.GLOCKK.UINT16[H]
#define RSCAN0GAFLID0 RSCAN0.GAFLID0.UINT32
#define RSCAN0GAFLID0L RSCAN0.GAFLID0.UINT16[L]
#define RSCAN0GAFLID0LL RSCAN0.GAFLID0.UINT8[LL]
#define RSCAN0GAFLID0LH RSCAN0.GAFLID0.UINT8[LH]
#define RSCAN0GAFLID0H RSCAN0.GAFLID0.UINT16[H]
#define RSCAN0GAFLID0HL RSCAN0.GAFLID0.UINT8[HL]
#define RSCAN0GAFLID0HH RSCAN0.GAFLID0.UINT8[HH]
#define RSCAN0GAFLM0 RSCAN0.GAFLM0.UINT32
#define RSCAN0GAFLM0L RSCAN0.GAFLM0.UINT16[L]
#define RSCAN0GAFLM0LL RSCAN0.GAFLM0.UINT8[LL]
#define RSCAN0GAFLM0LH RSCAN0.GAFLM0.UINT8[LH]
#define RSCAN0GAFLM0H RSCAN0.GAFLM0.UINT16[H]
#define RSCAN0GAFLM0HL RSCAN0.GAFLM0.UINT8[HL]
#define RSCAN0GAFLM0HH RSCAN0.GAFLM0.UINT8[HH]
#define RSCAN0GAFLP00 RSCAN0.GAFLP00.UINT32
#define RSCAN0GAFLP00L RSCAN0.GAFLP00.UINT16[L]
#define RSCAN0GAFLP00LL RSCAN0.GAFLP00.UINT8[LL]
#define RSCAN0GAFLP00LH RSCAN0.GAFLP00.UINT8[LH]
#define RSCAN0GAFLP00H RSCAN0.GAFLP00.UINT16[H]
#define RSCAN0GAFLP00HL RSCAN0.GAFLP00.UINT8[HL]
#define RSCAN0GAFLP00HH RSCAN0.GAFLP00.UINT8[HH]
#define RSCAN0GAFLP10 RSCAN0.GAFLP10.UINT32
#define RSCAN0GAFLP10L RSCAN0.GAFLP10.UINT16[L]
#define RSCAN0GAFLP10LL RSCAN0.GAFLP10.UINT8[LL]
#define RSCAN0GAFLP10LH RSCAN0.GAFLP10.UINT8[LH]
#define RSCAN0GAFLP10H RSCAN0.GAFLP10.UINT16[H]
#define RSCAN0GAFLP10HL RSCAN0.GAFLP10.UINT8[HL]
#define RSCAN0GAFLP10HH RSCAN0.GAFLP10.UINT8[HH]
#define RSCAN0GAFLID1 RSCAN0.GAFLID1.UINT32
#define RSCAN0GAFLID1L RSCAN0.GAFLID1.UINT16[L]
#define RSCAN0GAFLID1LL RSCAN0.GAFLID1.UINT8[LL]
#define RSCAN0GAFLID1LH RSCAN0.GAFLID1.UINT8[LH]
#define RSCAN0GAFLID1H RSCAN0.GAFLID1.UINT16[H]
#define RSCAN0GAFLID1HL RSCAN0.GAFLID1.UINT8[HL]
#define RSCAN0GAFLID1HH RSCAN0.GAFLID1.UINT8[HH]
#define RSCAN0GAFLM1 RSCAN0.GAFLM1.UINT32
#define RSCAN0GAFLM1L RSCAN0.GAFLM1.UINT16[L]
#define RSCAN0GAFLM1LL RSCAN0.GAFLM1.UINT8[LL]
#define RSCAN0GAFLM1LH RSCAN0.GAFLM1.UINT8[LH]
#define RSCAN0GAFLM1H RSCAN0.GAFLM1.UINT16[H]
#define RSCAN0GAFLM1HL RSCAN0.GAFLM1.UINT8[HL]
#define RSCAN0GAFLM1HH RSCAN0.GAFLM1.UINT8[HH]
#define RSCAN0GAFLP01 RSCAN0.GAFLP01.UINT32
#define RSCAN0GAFLP01L RSCAN0.GAFLP01.UINT16[L]
#define RSCAN0GAFLP01LL RSCAN0.GAFLP01.UINT8[LL]
#define RSCAN0GAFLP01LH RSCAN0.GAFLP01.UINT8[LH]
#define RSCAN0GAFLP01H RSCAN0.GAFLP01.UINT16[H]
#define RSCAN0GAFLP01HL RSCAN0.GAFLP01.UINT8[HL]
#define RSCAN0GAFLP01HH RSCAN0.GAFLP01.UINT8[HH]
#define RSCAN0GAFLP11 RSCAN0.GAFLP11.UINT32
#define RSCAN0GAFLP11L RSCAN0.GAFLP11.UINT16[L]
#define RSCAN0GAFLP11LL RSCAN0.GAFLP11.UINT8[LL]
#define RSCAN0GAFLP11LH RSCAN0.GAFLP11.UINT8[LH]
#define RSCAN0GAFLP11H RSCAN0.GAFLP11.UINT16[H]
#define RSCAN0GAFLP11HL RSCAN0.GAFLP11.UINT8[HL]
#define RSCAN0GAFLP11HH RSCAN0.GAFLP11.UINT8[HH]
#define RSCAN0GAFLID2 RSCAN0.GAFLID2.UINT32
#define RSCAN0GAFLID2L RSCAN0.GAFLID2.UINT16[L]
#define RSCAN0GAFLID2LL RSCAN0.GAFLID2.UINT8[LL]
#define RSCAN0GAFLID2LH RSCAN0.GAFLID2.UINT8[LH]
#define RSCAN0GAFLID2H RSCAN0.GAFLID2.UINT16[H]
#define RSCAN0GAFLID2HL RSCAN0.GAFLID2.UINT8[HL]
#define RSCAN0GAFLID2HH RSCAN0.GAFLID2.UINT8[HH]
#define RSCAN0GAFLM2 RSCAN0.GAFLM2.UINT32
#define RSCAN0GAFLM2L RSCAN0.GAFLM2.UINT16[L]
#define RSCAN0GAFLM2LL RSCAN0.GAFLM2.UINT8[LL]
#define RSCAN0GAFLM2LH RSCAN0.GAFLM2.UINT8[LH]
#define RSCAN0GAFLM2H RSCAN0.GAFLM2.UINT16[H]
#define RSCAN0GAFLM2HL RSCAN0.GAFLM2.UINT8[HL]
#define RSCAN0GAFLM2HH RSCAN0.GAFLM2.UINT8[HH]
#define RSCAN0GAFLP02 RSCAN0.GAFLP02.UINT32
#define RSCAN0GAFLP02L RSCAN0.GAFLP02.UINT16[L]
#define RSCAN0GAFLP02LL RSCAN0.GAFLP02.UINT8[LL]
#define RSCAN0GAFLP02LH RSCAN0.GAFLP02.UINT8[LH]
#define RSCAN0GAFLP02H RSCAN0.GAFLP02.UINT16[H]
#define RSCAN0GAFLP02HL RSCAN0.GAFLP02.UINT8[HL]
#define RSCAN0GAFLP02HH RSCAN0.GAFLP02.UINT8[HH]
#define RSCAN0GAFLP12 RSCAN0.GAFLP12.UINT32
#define RSCAN0GAFLP12L RSCAN0.GAFLP12.UINT16[L]
#define RSCAN0GAFLP12LL RSCAN0.GAFLP12.UINT8[LL]
#define RSCAN0GAFLP12LH RSCAN0.GAFLP12.UINT8[LH]
#define RSCAN0GAFLP12H RSCAN0.GAFLP12.UINT16[H]
#define RSCAN0GAFLP12HL RSCAN0.GAFLP12.UINT8[HL]
#define RSCAN0GAFLP12HH RSCAN0.GAFLP12.UINT8[HH]
#define RSCAN0GAFLID3 RSCAN0.GAFLID3.UINT32
#define RSCAN0GAFLID3L RSCAN0.GAFLID3.UINT16[L]
#define RSCAN0GAFLID3LL RSCAN0.GAFLID3.UINT8[LL]
#define RSCAN0GAFLID3LH RSCAN0.GAFLID3.UINT8[LH]
#define RSCAN0GAFLID3H RSCAN0.GAFLID3.UINT16[H]
#define RSCAN0GAFLID3HL RSCAN0.GAFLID3.UINT8[HL]
#define RSCAN0GAFLID3HH RSCAN0.GAFLID3.UINT8[HH]
#define RSCAN0GAFLM3 RSCAN0.GAFLM3.UINT32
#define RSCAN0GAFLM3L RSCAN0.GAFLM3.UINT16[L]
#define RSCAN0GAFLM3LL RSCAN0.GAFLM3.UINT8[LL]
#define RSCAN0GAFLM3LH RSCAN0.GAFLM3.UINT8[LH]
#define RSCAN0GAFLM3H RSCAN0.GAFLM3.UINT16[H]
#define RSCAN0GAFLM3HL RSCAN0.GAFLM3.UINT8[HL]
#define RSCAN0GAFLM3HH RSCAN0.GAFLM3.UINT8[HH]
#define RSCAN0GAFLP03 RSCAN0.GAFLP03.UINT32
#define RSCAN0GAFLP03L RSCAN0.GAFLP03.UINT16[L]
#define RSCAN0GAFLP03LL RSCAN0.GAFLP03.UINT8[LL]
#define RSCAN0GAFLP03LH RSCAN0.GAFLP03.UINT8[LH]
#define RSCAN0GAFLP03H RSCAN0.GAFLP03.UINT16[H]
#define RSCAN0GAFLP03HL RSCAN0.GAFLP03.UINT8[HL]
#define RSCAN0GAFLP03HH RSCAN0.GAFLP03.UINT8[HH]
#define RSCAN0GAFLP13 RSCAN0.GAFLP13.UINT32
#define RSCAN0GAFLP13L RSCAN0.GAFLP13.UINT16[L]
#define RSCAN0GAFLP13LL RSCAN0.GAFLP13.UINT8[LL]
#define RSCAN0GAFLP13LH RSCAN0.GAFLP13.UINT8[LH]
#define RSCAN0GAFLP13H RSCAN0.GAFLP13.UINT16[H]
#define RSCAN0GAFLP13HL RSCAN0.GAFLP13.UINT8[HL]
#define RSCAN0GAFLP13HH RSCAN0.GAFLP13.UINT8[HH]
#define RSCAN0GAFLID4 RSCAN0.GAFLID4.UINT32
#define RSCAN0GAFLID4L RSCAN0.GAFLID4.UINT16[L]
#define RSCAN0GAFLID4LL RSCAN0.GAFLID4.UINT8[LL]
#define RSCAN0GAFLID4LH RSCAN0.GAFLID4.UINT8[LH]
#define RSCAN0GAFLID4H RSCAN0.GAFLID4.UINT16[H]
#define RSCAN0GAFLID4HL RSCAN0.GAFLID4.UINT8[HL]
#define RSCAN0GAFLID4HH RSCAN0.GAFLID4.UINT8[HH]
#define RSCAN0GAFLM4 RSCAN0.GAFLM4.UINT32
#define RSCAN0GAFLM4L RSCAN0.GAFLM4.UINT16[L]
#define RSCAN0GAFLM4LL RSCAN0.GAFLM4.UINT8[LL]
#define RSCAN0GAFLM4LH RSCAN0.GAFLM4.UINT8[LH]
#define RSCAN0GAFLM4H RSCAN0.GAFLM4.UINT16[H]
#define RSCAN0GAFLM4HL RSCAN0.GAFLM4.UINT8[HL]
#define RSCAN0GAFLM4HH RSCAN0.GAFLM4.UINT8[HH]
#define RSCAN0GAFLP04 RSCAN0.GAFLP04.UINT32
#define RSCAN0GAFLP04L RSCAN0.GAFLP04.UINT16[L]
#define RSCAN0GAFLP04LL RSCAN0.GAFLP04.UINT8[LL]
#define RSCAN0GAFLP04LH RSCAN0.GAFLP04.UINT8[LH]
#define RSCAN0GAFLP04H RSCAN0.GAFLP04.UINT16[H]
#define RSCAN0GAFLP04HL RSCAN0.GAFLP04.UINT8[HL]
#define RSCAN0GAFLP04HH RSCAN0.GAFLP04.UINT8[HH]
#define RSCAN0GAFLP14 RSCAN0.GAFLP14.UINT32
#define RSCAN0GAFLP14L RSCAN0.GAFLP14.UINT16[L]
#define RSCAN0GAFLP14LL RSCAN0.GAFLP14.UINT8[LL]
#define RSCAN0GAFLP14LH RSCAN0.GAFLP14.UINT8[LH]
#define RSCAN0GAFLP14H RSCAN0.GAFLP14.UINT16[H]
#define RSCAN0GAFLP14HL RSCAN0.GAFLP14.UINT8[HL]
#define RSCAN0GAFLP14HH RSCAN0.GAFLP14.UINT8[HH]
#define RSCAN0GAFLID5 RSCAN0.GAFLID5.UINT32
#define RSCAN0GAFLID5L RSCAN0.GAFLID5.UINT16[L]
#define RSCAN0GAFLID5LL RSCAN0.GAFLID5.UINT8[LL]
#define RSCAN0GAFLID5LH RSCAN0.GAFLID5.UINT8[LH]
#define RSCAN0GAFLID5H RSCAN0.GAFLID5.UINT16[H]
#define RSCAN0GAFLID5HL RSCAN0.GAFLID5.UINT8[HL]
#define RSCAN0GAFLID5HH RSCAN0.GAFLID5.UINT8[HH]
#define RSCAN0GAFLM5 RSCAN0.GAFLM5.UINT32
#define RSCAN0GAFLM5L RSCAN0.GAFLM5.UINT16[L]
#define RSCAN0GAFLM5LL RSCAN0.GAFLM5.UINT8[LL]
#define RSCAN0GAFLM5LH RSCAN0.GAFLM5.UINT8[LH]
#define RSCAN0GAFLM5H RSCAN0.GAFLM5.UINT16[H]
#define RSCAN0GAFLM5HL RSCAN0.GAFLM5.UINT8[HL]
#define RSCAN0GAFLM5HH RSCAN0.GAFLM5.UINT8[HH]
#define RSCAN0GAFLP05 RSCAN0.GAFLP05.UINT32
#define RSCAN0GAFLP05L RSCAN0.GAFLP05.UINT16[L]
#define RSCAN0GAFLP05LL RSCAN0.GAFLP05.UINT8[LL]
#define RSCAN0GAFLP05LH RSCAN0.GAFLP05.UINT8[LH]
#define RSCAN0GAFLP05H RSCAN0.GAFLP05.UINT16[H]
#define RSCAN0GAFLP05HL RSCAN0.GAFLP05.UINT8[HL]
#define RSCAN0GAFLP05HH RSCAN0.GAFLP05.UINT8[HH]
#define RSCAN0GAFLP15 RSCAN0.GAFLP15.UINT32
#define RSCAN0GAFLP15L RSCAN0.GAFLP15.UINT16[L]
#define RSCAN0GAFLP15LL RSCAN0.GAFLP15.UINT8[LL]
#define RSCAN0GAFLP15LH RSCAN0.GAFLP15.UINT8[LH]
#define RSCAN0GAFLP15H RSCAN0.GAFLP15.UINT16[H]
#define RSCAN0GAFLP15HL RSCAN0.GAFLP15.UINT8[HL]
#define RSCAN0GAFLP15HH RSCAN0.GAFLP15.UINT8[HH]
#define RSCAN0GAFLID6 RSCAN0.GAFLID6.UINT32
#define RSCAN0GAFLID6L RSCAN0.GAFLID6.UINT16[L]
#define RSCAN0GAFLID6LL RSCAN0.GAFLID6.UINT8[LL]
#define RSCAN0GAFLID6LH RSCAN0.GAFLID6.UINT8[LH]
#define RSCAN0GAFLID6H RSCAN0.GAFLID6.UINT16[H]
#define RSCAN0GAFLID6HL RSCAN0.GAFLID6.UINT8[HL]
#define RSCAN0GAFLID6HH RSCAN0.GAFLID6.UINT8[HH]
#define RSCAN0GAFLM6 RSCAN0.GAFLM6.UINT32
#define RSCAN0GAFLM6L RSCAN0.GAFLM6.UINT16[L]
#define RSCAN0GAFLM6LL RSCAN0.GAFLM6.UINT8[LL]
#define RSCAN0GAFLM6LH RSCAN0.GAFLM6.UINT8[LH]
#define RSCAN0GAFLM6H RSCAN0.GAFLM6.UINT16[H]
#define RSCAN0GAFLM6HL RSCAN0.GAFLM6.UINT8[HL]
#define RSCAN0GAFLM6HH RSCAN0.GAFLM6.UINT8[HH]
#define RSCAN0GAFLP06 RSCAN0.GAFLP06.UINT32
#define RSCAN0GAFLP06L RSCAN0.GAFLP06.UINT16[L]
#define RSCAN0GAFLP06LL RSCAN0.GAFLP06.UINT8[LL]
#define RSCAN0GAFLP06LH RSCAN0.GAFLP06.UINT8[LH]
#define RSCAN0GAFLP06H RSCAN0.GAFLP06.UINT16[H]
#define RSCAN0GAFLP06HL RSCAN0.GAFLP06.UINT8[HL]
#define RSCAN0GAFLP06HH RSCAN0.GAFLP06.UINT8[HH]
#define RSCAN0GAFLP16 RSCAN0.GAFLP16.UINT32
#define RSCAN0GAFLP16L RSCAN0.GAFLP16.UINT16[L]
#define RSCAN0GAFLP16LL RSCAN0.GAFLP16.UINT8[LL]
#define RSCAN0GAFLP16LH RSCAN0.GAFLP16.UINT8[LH]
#define RSCAN0GAFLP16H RSCAN0.GAFLP16.UINT16[H]
#define RSCAN0GAFLP16HL RSCAN0.GAFLP16.UINT8[HL]
#define RSCAN0GAFLP16HH RSCAN0.GAFLP16.UINT8[HH]
#define RSCAN0GAFLID7 RSCAN0.GAFLID7.UINT32
#define RSCAN0GAFLID7L RSCAN0.GAFLID7.UINT16[L]
#define RSCAN0GAFLID7LL RSCAN0.GAFLID7.UINT8[LL]
#define RSCAN0GAFLID7LH RSCAN0.GAFLID7.UINT8[LH]
#define RSCAN0GAFLID7H RSCAN0.GAFLID7.UINT16[H]
#define RSCAN0GAFLID7HL RSCAN0.GAFLID7.UINT8[HL]
#define RSCAN0GAFLID7HH RSCAN0.GAFLID7.UINT8[HH]
#define RSCAN0GAFLM7 RSCAN0.GAFLM7.UINT32
#define RSCAN0GAFLM7L RSCAN0.GAFLM7.UINT16[L]
#define RSCAN0GAFLM7LL RSCAN0.GAFLM7.UINT8[LL]
#define RSCAN0GAFLM7LH RSCAN0.GAFLM7.UINT8[LH]
#define RSCAN0GAFLM7H RSCAN0.GAFLM7.UINT16[H]
#define RSCAN0GAFLM7HL RSCAN0.GAFLM7.UINT8[HL]
#define RSCAN0GAFLM7HH RSCAN0.GAFLM7.UINT8[HH]
#define RSCAN0GAFLP07 RSCAN0.GAFLP07.UINT32
#define RSCAN0GAFLP07L RSCAN0.GAFLP07.UINT16[L]
#define RSCAN0GAFLP07LL RSCAN0.GAFLP07.UINT8[LL]
#define RSCAN0GAFLP07LH RSCAN0.GAFLP07.UINT8[LH]
#define RSCAN0GAFLP07H RSCAN0.GAFLP07.UINT16[H]
#define RSCAN0GAFLP07HL RSCAN0.GAFLP07.UINT8[HL]
#define RSCAN0GAFLP07HH RSCAN0.GAFLP07.UINT8[HH]
#define RSCAN0GAFLP17 RSCAN0.GAFLP17.UINT32
#define RSCAN0GAFLP17L RSCAN0.GAFLP17.UINT16[L]
#define RSCAN0GAFLP17LL RSCAN0.GAFLP17.UINT8[LL]
#define RSCAN0GAFLP17LH RSCAN0.GAFLP17.UINT8[LH]
#define RSCAN0GAFLP17H RSCAN0.GAFLP17.UINT16[H]
#define RSCAN0GAFLP17HL RSCAN0.GAFLP17.UINT8[HL]
#define RSCAN0GAFLP17HH RSCAN0.GAFLP17.UINT8[HH]
#define RSCAN0GAFLID8 RSCAN0.GAFLID8.UINT32
#define RSCAN0GAFLID8L RSCAN0.GAFLID8.UINT16[L]
#define RSCAN0GAFLID8LL RSCAN0.GAFLID8.UINT8[LL]
#define RSCAN0GAFLID8LH RSCAN0.GAFLID8.UINT8[LH]
#define RSCAN0GAFLID8H RSCAN0.GAFLID8.UINT16[H]
#define RSCAN0GAFLID8HL RSCAN0.GAFLID8.UINT8[HL]
#define RSCAN0GAFLID8HH RSCAN0.GAFLID8.UINT8[HH]
#define RSCAN0GAFLM8 RSCAN0.GAFLM8.UINT32
#define RSCAN0GAFLM8L RSCAN0.GAFLM8.UINT16[L]
#define RSCAN0GAFLM8LL RSCAN0.GAFLM8.UINT8[LL]
#define RSCAN0GAFLM8LH RSCAN0.GAFLM8.UINT8[LH]
#define RSCAN0GAFLM8H RSCAN0.GAFLM8.UINT16[H]
#define RSCAN0GAFLM8HL RSCAN0.GAFLM8.UINT8[HL]
#define RSCAN0GAFLM8HH RSCAN0.GAFLM8.UINT8[HH]
#define RSCAN0GAFLP08 RSCAN0.GAFLP08.UINT32
#define RSCAN0GAFLP08L RSCAN0.GAFLP08.UINT16[L]
#define RSCAN0GAFLP08LL RSCAN0.GAFLP08.UINT8[LL]
#define RSCAN0GAFLP08LH RSCAN0.GAFLP08.UINT8[LH]
#define RSCAN0GAFLP08H RSCAN0.GAFLP08.UINT16[H]
#define RSCAN0GAFLP08HL RSCAN0.GAFLP08.UINT8[HL]
#define RSCAN0GAFLP08HH RSCAN0.GAFLP08.UINT8[HH]
#define RSCAN0GAFLP18 RSCAN0.GAFLP18.UINT32
#define RSCAN0GAFLP18L RSCAN0.GAFLP18.UINT16[L]
#define RSCAN0GAFLP18LL RSCAN0.GAFLP18.UINT8[LL]
#define RSCAN0GAFLP18LH RSCAN0.GAFLP18.UINT8[LH]
#define RSCAN0GAFLP18H RSCAN0.GAFLP18.UINT16[H]
#define RSCAN0GAFLP18HL RSCAN0.GAFLP18.UINT8[HL]
#define RSCAN0GAFLP18HH RSCAN0.GAFLP18.UINT8[HH]
#define RSCAN0GAFLID9 RSCAN0.GAFLID9.UINT32
#define RSCAN0GAFLID9L RSCAN0.GAFLID9.UINT16[L]
#define RSCAN0GAFLID9LL RSCAN0.GAFLID9.UINT8[LL]
#define RSCAN0GAFLID9LH RSCAN0.GAFLID9.UINT8[LH]
#define RSCAN0GAFLID9H RSCAN0.GAFLID9.UINT16[H]
#define RSCAN0GAFLID9HL RSCAN0.GAFLID9.UINT8[HL]
#define RSCAN0GAFLID9HH RSCAN0.GAFLID9.UINT8[HH]
#define RSCAN0GAFLM9 RSCAN0.GAFLM9.UINT32
#define RSCAN0GAFLM9L RSCAN0.GAFLM9.UINT16[L]
#define RSCAN0GAFLM9LL RSCAN0.GAFLM9.UINT8[LL]
#define RSCAN0GAFLM9LH RSCAN0.GAFLM9.UINT8[LH]
#define RSCAN0GAFLM9H RSCAN0.GAFLM9.UINT16[H]
#define RSCAN0GAFLM9HL RSCAN0.GAFLM9.UINT8[HL]
#define RSCAN0GAFLM9HH RSCAN0.GAFLM9.UINT8[HH]
#define RSCAN0GAFLP09 RSCAN0.GAFLP09.UINT32
#define RSCAN0GAFLP09L RSCAN0.GAFLP09.UINT16[L]
#define RSCAN0GAFLP09LL RSCAN0.GAFLP09.UINT8[LL]
#define RSCAN0GAFLP09LH RSCAN0.GAFLP09.UINT8[LH]
#define RSCAN0GAFLP09H RSCAN0.GAFLP09.UINT16[H]
#define RSCAN0GAFLP09HL RSCAN0.GAFLP09.UINT8[HL]
#define RSCAN0GAFLP09HH RSCAN0.GAFLP09.UINT8[HH]
#define RSCAN0GAFLP19 RSCAN0.GAFLP19.UINT32
#define RSCAN0GAFLP19L RSCAN0.GAFLP19.UINT16[L]
#define RSCAN0GAFLP19LL RSCAN0.GAFLP19.UINT8[LL]
#define RSCAN0GAFLP19LH RSCAN0.GAFLP19.UINT8[LH]
#define RSCAN0GAFLP19H RSCAN0.GAFLP19.UINT16[H]
#define RSCAN0GAFLP19HL RSCAN0.GAFLP19.UINT8[HL]
#define RSCAN0GAFLP19HH RSCAN0.GAFLP19.UINT8[HH]
#define RSCAN0GAFLID10 RSCAN0.GAFLID10.UINT32
#define RSCAN0GAFLID10L RSCAN0.GAFLID10.UINT16[L]
#define RSCAN0GAFLID10LL RSCAN0.GAFLID10.UINT8[LL]
#define RSCAN0GAFLID10LH RSCAN0.GAFLID10.UINT8[LH]
#define RSCAN0GAFLID10H RSCAN0.GAFLID10.UINT16[H]
#define RSCAN0GAFLID10HL RSCAN0.GAFLID10.UINT8[HL]
#define RSCAN0GAFLID10HH RSCAN0.GAFLID10.UINT8[HH]
#define RSCAN0GAFLM10 RSCAN0.GAFLM10.UINT32
#define RSCAN0GAFLM10L RSCAN0.GAFLM10.UINT16[L]
#define RSCAN0GAFLM10LL RSCAN0.GAFLM10.UINT8[LL]
#define RSCAN0GAFLM10LH RSCAN0.GAFLM10.UINT8[LH]
#define RSCAN0GAFLM10H RSCAN0.GAFLM10.UINT16[H]
#define RSCAN0GAFLM10HL RSCAN0.GAFLM10.UINT8[HL]
#define RSCAN0GAFLM10HH RSCAN0.GAFLM10.UINT8[HH]
#define RSCAN0GAFLP010 RSCAN0.GAFLP010.UINT32
#define RSCAN0GAFLP010L RSCAN0.GAFLP010.UINT16[L]
#define RSCAN0GAFLP010LL RSCAN0.GAFLP010.UINT8[LL]
#define RSCAN0GAFLP010LH RSCAN0.GAFLP010.UINT8[LH]
#define RSCAN0GAFLP010H RSCAN0.GAFLP010.UINT16[H]
#define RSCAN0GAFLP010HL RSCAN0.GAFLP010.UINT8[HL]
#define RSCAN0GAFLP010HH RSCAN0.GAFLP010.UINT8[HH]
#define RSCAN0GAFLP110 RSCAN0.GAFLP110.UINT32
#define RSCAN0GAFLP110L RSCAN0.GAFLP110.UINT16[L]
#define RSCAN0GAFLP110LL RSCAN0.GAFLP110.UINT8[LL]
#define RSCAN0GAFLP110LH RSCAN0.GAFLP110.UINT8[LH]
#define RSCAN0GAFLP110H RSCAN0.GAFLP110.UINT16[H]
#define RSCAN0GAFLP110HL RSCAN0.GAFLP110.UINT8[HL]
#define RSCAN0GAFLP110HH RSCAN0.GAFLP110.UINT8[HH]
#define RSCAN0GAFLID11 RSCAN0.GAFLID11.UINT32
#define RSCAN0GAFLID11L RSCAN0.GAFLID11.UINT16[L]
#define RSCAN0GAFLID11LL RSCAN0.GAFLID11.UINT8[LL]
#define RSCAN0GAFLID11LH RSCAN0.GAFLID11.UINT8[LH]
#define RSCAN0GAFLID11H RSCAN0.GAFLID11.UINT16[H]
#define RSCAN0GAFLID11HL RSCAN0.GAFLID11.UINT8[HL]
#define RSCAN0GAFLID11HH RSCAN0.GAFLID11.UINT8[HH]
#define RSCAN0GAFLM11 RSCAN0.GAFLM11.UINT32
#define RSCAN0GAFLM11L RSCAN0.GAFLM11.UINT16[L]
#define RSCAN0GAFLM11LL RSCAN0.GAFLM11.UINT8[LL]
#define RSCAN0GAFLM11LH RSCAN0.GAFLM11.UINT8[LH]
#define RSCAN0GAFLM11H RSCAN0.GAFLM11.UINT16[H]
#define RSCAN0GAFLM11HL RSCAN0.GAFLM11.UINT8[HL]
#define RSCAN0GAFLM11HH RSCAN0.GAFLM11.UINT8[HH]
#define RSCAN0GAFLP011 RSCAN0.GAFLP011.UINT32
#define RSCAN0GAFLP011L RSCAN0.GAFLP011.UINT16[L]
#define RSCAN0GAFLP011LL RSCAN0.GAFLP011.UINT8[LL]
#define RSCAN0GAFLP011LH RSCAN0.GAFLP011.UINT8[LH]
#define RSCAN0GAFLP011H RSCAN0.GAFLP011.UINT16[H]
#define RSCAN0GAFLP011HL RSCAN0.GAFLP011.UINT8[HL]
#define RSCAN0GAFLP011HH RSCAN0.GAFLP011.UINT8[HH]
#define RSCAN0GAFLP111 RSCAN0.GAFLP111.UINT32
#define RSCAN0GAFLP111L RSCAN0.GAFLP111.UINT16[L]
#define RSCAN0GAFLP111LL RSCAN0.GAFLP111.UINT8[LL]
#define RSCAN0GAFLP111LH RSCAN0.GAFLP111.UINT8[LH]
#define RSCAN0GAFLP111H RSCAN0.GAFLP111.UINT16[H]
#define RSCAN0GAFLP111HL RSCAN0.GAFLP111.UINT8[HL]
#define RSCAN0GAFLP111HH RSCAN0.GAFLP111.UINT8[HH]
#define RSCAN0GAFLID12 RSCAN0.GAFLID12.UINT32
#define RSCAN0GAFLID12L RSCAN0.GAFLID12.UINT16[L]
#define RSCAN0GAFLID12LL RSCAN0.GAFLID12.UINT8[LL]
#define RSCAN0GAFLID12LH RSCAN0.GAFLID12.UINT8[LH]
#define RSCAN0GAFLID12H RSCAN0.GAFLID12.UINT16[H]
#define RSCAN0GAFLID12HL RSCAN0.GAFLID12.UINT8[HL]
#define RSCAN0GAFLID12HH RSCAN0.GAFLID12.UINT8[HH]
#define RSCAN0GAFLM12 RSCAN0.GAFLM12.UINT32
#define RSCAN0GAFLM12L RSCAN0.GAFLM12.UINT16[L]
#define RSCAN0GAFLM12LL RSCAN0.GAFLM12.UINT8[LL]
#define RSCAN0GAFLM12LH RSCAN0.GAFLM12.UINT8[LH]
#define RSCAN0GAFLM12H RSCAN0.GAFLM12.UINT16[H]
#define RSCAN0GAFLM12HL RSCAN0.GAFLM12.UINT8[HL]
#define RSCAN0GAFLM12HH RSCAN0.GAFLM12.UINT8[HH]
#define RSCAN0GAFLP012 RSCAN0.GAFLP012.UINT32
#define RSCAN0GAFLP012L RSCAN0.GAFLP012.UINT16[L]
#define RSCAN0GAFLP012LL RSCAN0.GAFLP012.UINT8[LL]
#define RSCAN0GAFLP012LH RSCAN0.GAFLP012.UINT8[LH]
#define RSCAN0GAFLP012H RSCAN0.GAFLP012.UINT16[H]
#define RSCAN0GAFLP012HL RSCAN0.GAFLP012.UINT8[HL]
#define RSCAN0GAFLP012HH RSCAN0.GAFLP012.UINT8[HH]
#define RSCAN0GAFLP112 RSCAN0.GAFLP112.UINT32
#define RSCAN0GAFLP112L RSCAN0.GAFLP112.UINT16[L]
#define RSCAN0GAFLP112LL RSCAN0.GAFLP112.UINT8[LL]
#define RSCAN0GAFLP112LH RSCAN0.GAFLP112.UINT8[LH]
#define RSCAN0GAFLP112H RSCAN0.GAFLP112.UINT16[H]
#define RSCAN0GAFLP112HL RSCAN0.GAFLP112.UINT8[HL]
#define RSCAN0GAFLP112HH RSCAN0.GAFLP112.UINT8[HH]
#define RSCAN0GAFLID13 RSCAN0.GAFLID13.UINT32
#define RSCAN0GAFLID13L RSCAN0.GAFLID13.UINT16[L]
#define RSCAN0GAFLID13LL RSCAN0.GAFLID13.UINT8[LL]
#define RSCAN0GAFLID13LH RSCAN0.GAFLID13.UINT8[LH]
#define RSCAN0GAFLID13H RSCAN0.GAFLID13.UINT16[H]
#define RSCAN0GAFLID13HL RSCAN0.GAFLID13.UINT8[HL]
#define RSCAN0GAFLID13HH RSCAN0.GAFLID13.UINT8[HH]
#define RSCAN0GAFLM13 RSCAN0.GAFLM13.UINT32
#define RSCAN0GAFLM13L RSCAN0.GAFLM13.UINT16[L]
#define RSCAN0GAFLM13LL RSCAN0.GAFLM13.UINT8[LL]
#define RSCAN0GAFLM13LH RSCAN0.GAFLM13.UINT8[LH]
#define RSCAN0GAFLM13H RSCAN0.GAFLM13.UINT16[H]
#define RSCAN0GAFLM13HL RSCAN0.GAFLM13.UINT8[HL]
#define RSCAN0GAFLM13HH RSCAN0.GAFLM13.UINT8[HH]
#define RSCAN0GAFLP013 RSCAN0.GAFLP013.UINT32
#define RSCAN0GAFLP013L RSCAN0.GAFLP013.UINT16[L]
#define RSCAN0GAFLP013LL RSCAN0.GAFLP013.UINT8[LL]
#define RSCAN0GAFLP013LH RSCAN0.GAFLP013.UINT8[LH]
#define RSCAN0GAFLP013H RSCAN0.GAFLP013.UINT16[H]
#define RSCAN0GAFLP013HL RSCAN0.GAFLP013.UINT8[HL]
#define RSCAN0GAFLP013HH RSCAN0.GAFLP013.UINT8[HH]
#define RSCAN0GAFLP113 RSCAN0.GAFLP113.UINT32
#define RSCAN0GAFLP113L RSCAN0.GAFLP113.UINT16[L]
#define RSCAN0GAFLP113LL RSCAN0.GAFLP113.UINT8[LL]
#define RSCAN0GAFLP113LH RSCAN0.GAFLP113.UINT8[LH]
#define RSCAN0GAFLP113H RSCAN0.GAFLP113.UINT16[H]
#define RSCAN0GAFLP113HL RSCAN0.GAFLP113.UINT8[HL]
#define RSCAN0GAFLP113HH RSCAN0.GAFLP113.UINT8[HH]
#define RSCAN0GAFLID14 RSCAN0.GAFLID14.UINT32
#define RSCAN0GAFLID14L RSCAN0.GAFLID14.UINT16[L]
#define RSCAN0GAFLID14LL RSCAN0.GAFLID14.UINT8[LL]
#define RSCAN0GAFLID14LH RSCAN0.GAFLID14.UINT8[LH]
#define RSCAN0GAFLID14H RSCAN0.GAFLID14.UINT16[H]
#define RSCAN0GAFLID14HL RSCAN0.GAFLID14.UINT8[HL]
#define RSCAN0GAFLID14HH RSCAN0.GAFLID14.UINT8[HH]
#define RSCAN0GAFLM14 RSCAN0.GAFLM14.UINT32
#define RSCAN0GAFLM14L RSCAN0.GAFLM14.UINT16[L]
#define RSCAN0GAFLM14LL RSCAN0.GAFLM14.UINT8[LL]
#define RSCAN0GAFLM14LH RSCAN0.GAFLM14.UINT8[LH]
#define RSCAN0GAFLM14H RSCAN0.GAFLM14.UINT16[H]
#define RSCAN0GAFLM14HL RSCAN0.GAFLM14.UINT8[HL]
#define RSCAN0GAFLM14HH RSCAN0.GAFLM14.UINT8[HH]
#define RSCAN0GAFLP014 RSCAN0.GAFLP014.UINT32
#define RSCAN0GAFLP014L RSCAN0.GAFLP014.UINT16[L]
#define RSCAN0GAFLP014LL RSCAN0.GAFLP014.UINT8[LL]
#define RSCAN0GAFLP014LH RSCAN0.GAFLP014.UINT8[LH]
#define RSCAN0GAFLP014H RSCAN0.GAFLP014.UINT16[H]
#define RSCAN0GAFLP014HL RSCAN0.GAFLP014.UINT8[HL]
#define RSCAN0GAFLP014HH RSCAN0.GAFLP014.UINT8[HH]
#define RSCAN0GAFLP114 RSCAN0.GAFLP114.UINT32
#define RSCAN0GAFLP114L RSCAN0.GAFLP114.UINT16[L]
#define RSCAN0GAFLP114LL RSCAN0.GAFLP114.UINT8[LL]
#define RSCAN0GAFLP114LH RSCAN0.GAFLP114.UINT8[LH]
#define RSCAN0GAFLP114H RSCAN0.GAFLP114.UINT16[H]
#define RSCAN0GAFLP114HL RSCAN0.GAFLP114.UINT8[HL]
#define RSCAN0GAFLP114HH RSCAN0.GAFLP114.UINT8[HH]
#define RSCAN0GAFLID15 RSCAN0.GAFLID15.UINT32
#define RSCAN0GAFLID15L RSCAN0.GAFLID15.UINT16[L]
#define RSCAN0GAFLID15LL RSCAN0.GAFLID15.UINT8[LL]
#define RSCAN0GAFLID15LH RSCAN0.GAFLID15.UINT8[LH]
#define RSCAN0GAFLID15H RSCAN0.GAFLID15.UINT16[H]
#define RSCAN0GAFLID15HL RSCAN0.GAFLID15.UINT8[HL]
#define RSCAN0GAFLID15HH RSCAN0.GAFLID15.UINT8[HH]
#define RSCAN0GAFLM15 RSCAN0.GAFLM15.UINT32
#define RSCAN0GAFLM15L RSCAN0.GAFLM15.UINT16[L]
#define RSCAN0GAFLM15LL RSCAN0.GAFLM15.UINT8[LL]
#define RSCAN0GAFLM15LH RSCAN0.GAFLM15.UINT8[LH]
#define RSCAN0GAFLM15H RSCAN0.GAFLM15.UINT16[H]
#define RSCAN0GAFLM15HL RSCAN0.GAFLM15.UINT8[HL]
#define RSCAN0GAFLM15HH RSCAN0.GAFLM15.UINT8[HH]
#define RSCAN0GAFLP015 RSCAN0.GAFLP015.UINT32
#define RSCAN0GAFLP015L RSCAN0.GAFLP015.UINT16[L]
#define RSCAN0GAFLP015LL RSCAN0.GAFLP015.UINT8[LL]
#define RSCAN0GAFLP015LH RSCAN0.GAFLP015.UINT8[LH]
#define RSCAN0GAFLP015H RSCAN0.GAFLP015.UINT16[H]
#define RSCAN0GAFLP015HL RSCAN0.GAFLP015.UINT8[HL]
#define RSCAN0GAFLP015HH RSCAN0.GAFLP015.UINT8[HH]
#define RSCAN0GAFLP115 RSCAN0.GAFLP115.UINT32
#define RSCAN0GAFLP115L RSCAN0.GAFLP115.UINT16[L]
#define RSCAN0GAFLP115LL RSCAN0.GAFLP115.UINT8[LL]
#define RSCAN0GAFLP115LH RSCAN0.GAFLP115.UINT8[LH]
#define RSCAN0GAFLP115H RSCAN0.GAFLP115.UINT16[H]
#define RSCAN0GAFLP115HL RSCAN0.GAFLP115.UINT8[HL]
#define RSCAN0GAFLP115HH RSCAN0.GAFLP115.UINT8[HH]
#define RSCAN0RMID0 RSCAN0.RMID0.UINT32
#define RSCAN0RMID0L RSCAN0.RMID0.UINT16[L]
#define RSCAN0RMID0LL RSCAN0.RMID0.UINT8[LL]
#define RSCAN0RMID0LH RSCAN0.RMID0.UINT8[LH]
#define RSCAN0RMID0H RSCAN0.RMID0.UINT16[H]
#define RSCAN0RMID0HL RSCAN0.RMID0.UINT8[HL]
#define RSCAN0RMID0HH RSCAN0.RMID0.UINT8[HH]
#define RSCAN0RMPTR0 RSCAN0.RMPTR0.UINT32
#define RSCAN0RMPTR0L RSCAN0.RMPTR0.UINT16[L]
#define RSCAN0RMPTR0LL RSCAN0.RMPTR0.UINT8[LL]
#define RSCAN0RMPTR0LH RSCAN0.RMPTR0.UINT8[LH]
#define RSCAN0RMPTR0H RSCAN0.RMPTR0.UINT16[H]
#define RSCAN0RMPTR0HL RSCAN0.RMPTR0.UINT8[HL]
#define RSCAN0RMPTR0HH RSCAN0.RMPTR0.UINT8[HH]
#define RSCAN0RMDF00 RSCAN0.RMDF00.UINT32
#define RSCAN0RMDF00L RSCAN0.RMDF00.UINT16[L]
#define RSCAN0RMDF00LL RSCAN0.RMDF00.UINT8[LL]
#define RSCAN0RMDF00LH RSCAN0.RMDF00.UINT8[LH]
#define RSCAN0RMDF00H RSCAN0.RMDF00.UINT16[H]
#define RSCAN0RMDF00HL RSCAN0.RMDF00.UINT8[HL]
#define RSCAN0RMDF00HH RSCAN0.RMDF00.UINT8[HH]
#define RSCAN0RMDF10 RSCAN0.RMDF10.UINT32
#define RSCAN0RMDF10L RSCAN0.RMDF10.UINT16[L]
#define RSCAN0RMDF10LL RSCAN0.RMDF10.UINT8[LL]
#define RSCAN0RMDF10LH RSCAN0.RMDF10.UINT8[LH]
#define RSCAN0RMDF10H RSCAN0.RMDF10.UINT16[H]
#define RSCAN0RMDF10HL RSCAN0.RMDF10.UINT8[HL]
#define RSCAN0RMDF10HH RSCAN0.RMDF10.UINT8[HH]
#define RSCAN0RMID1 RSCAN0.RMID1.UINT32
#define RSCAN0RMID1L RSCAN0.RMID1.UINT16[L]
#define RSCAN0RMID1LL RSCAN0.RMID1.UINT8[LL]
#define RSCAN0RMID1LH RSCAN0.RMID1.UINT8[LH]
#define RSCAN0RMID1H RSCAN0.RMID1.UINT16[H]
#define RSCAN0RMID1HL RSCAN0.RMID1.UINT8[HL]
#define RSCAN0RMID1HH RSCAN0.RMID1.UINT8[HH]
#define RSCAN0RMPTR1 RSCAN0.RMPTR1.UINT32
#define RSCAN0RMPTR1L RSCAN0.RMPTR1.UINT16[L]
#define RSCAN0RMPTR1LL RSCAN0.RMPTR1.UINT8[LL]
#define RSCAN0RMPTR1LH RSCAN0.RMPTR1.UINT8[LH]
#define RSCAN0RMPTR1H RSCAN0.RMPTR1.UINT16[H]
#define RSCAN0RMPTR1HL RSCAN0.RMPTR1.UINT8[HL]
#define RSCAN0RMPTR1HH RSCAN0.RMPTR1.UINT8[HH]
#define RSCAN0RMDF01 RSCAN0.RMDF01.UINT32
#define RSCAN0RMDF01L RSCAN0.RMDF01.UINT16[L]
#define RSCAN0RMDF01LL RSCAN0.RMDF01.UINT8[LL]
#define RSCAN0RMDF01LH RSCAN0.RMDF01.UINT8[LH]
#define RSCAN0RMDF01H RSCAN0.RMDF01.UINT16[H]
#define RSCAN0RMDF01HL RSCAN0.RMDF01.UINT8[HL]
#define RSCAN0RMDF01HH RSCAN0.RMDF01.UINT8[HH]
#define RSCAN0RMDF11 RSCAN0.RMDF11.UINT32
#define RSCAN0RMDF11L RSCAN0.RMDF11.UINT16[L]
#define RSCAN0RMDF11LL RSCAN0.RMDF11.UINT8[LL]
#define RSCAN0RMDF11LH RSCAN0.RMDF11.UINT8[LH]
#define RSCAN0RMDF11H RSCAN0.RMDF11.UINT16[H]
#define RSCAN0RMDF11HL RSCAN0.RMDF11.UINT8[HL]
#define RSCAN0RMDF11HH RSCAN0.RMDF11.UINT8[HH]
#define RSCAN0RMID2 RSCAN0.RMID2.UINT32
#define RSCAN0RMID2L RSCAN0.RMID2.UINT16[L]
#define RSCAN0RMID2LL RSCAN0.RMID2.UINT8[LL]
#define RSCAN0RMID2LH RSCAN0.RMID2.UINT8[LH]
#define RSCAN0RMID2H RSCAN0.RMID2.UINT16[H]
#define RSCAN0RMID2HL RSCAN0.RMID2.UINT8[HL]
#define RSCAN0RMID2HH RSCAN0.RMID2.UINT8[HH]
#define RSCAN0RMPTR2 RSCAN0.RMPTR2.UINT32
#define RSCAN0RMPTR2L RSCAN0.RMPTR2.UINT16[L]
#define RSCAN0RMPTR2LL RSCAN0.RMPTR2.UINT8[LL]
#define RSCAN0RMPTR2LH RSCAN0.RMPTR2.UINT8[LH]
#define RSCAN0RMPTR2H RSCAN0.RMPTR2.UINT16[H]
#define RSCAN0RMPTR2HL RSCAN0.RMPTR2.UINT8[HL]
#define RSCAN0RMPTR2HH RSCAN0.RMPTR2.UINT8[HH]
#define RSCAN0RMDF02 RSCAN0.RMDF02.UINT32
#define RSCAN0RMDF02L RSCAN0.RMDF02.UINT16[L]
#define RSCAN0RMDF02LL RSCAN0.RMDF02.UINT8[LL]
#define RSCAN0RMDF02LH RSCAN0.RMDF02.UINT8[LH]
#define RSCAN0RMDF02H RSCAN0.RMDF02.UINT16[H]
#define RSCAN0RMDF02HL RSCAN0.RMDF02.UINT8[HL]
#define RSCAN0RMDF02HH RSCAN0.RMDF02.UINT8[HH]
#define RSCAN0RMDF12 RSCAN0.RMDF12.UINT32
#define RSCAN0RMDF12L RSCAN0.RMDF12.UINT16[L]
#define RSCAN0RMDF12LL RSCAN0.RMDF12.UINT8[LL]
#define RSCAN0RMDF12LH RSCAN0.RMDF12.UINT8[LH]
#define RSCAN0RMDF12H RSCAN0.RMDF12.UINT16[H]
#define RSCAN0RMDF12HL RSCAN0.RMDF12.UINT8[HL]
#define RSCAN0RMDF12HH RSCAN0.RMDF12.UINT8[HH]
#define RSCAN0RMID3 RSCAN0.RMID3.UINT32
#define RSCAN0RMID3L RSCAN0.RMID3.UINT16[L]
#define RSCAN0RMID3LL RSCAN0.RMID3.UINT8[LL]
#define RSCAN0RMID3LH RSCAN0.RMID3.UINT8[LH]
#define RSCAN0RMID3H RSCAN0.RMID3.UINT16[H]
#define RSCAN0RMID3HL RSCAN0.RMID3.UINT8[HL]
#define RSCAN0RMID3HH RSCAN0.RMID3.UINT8[HH]
#define RSCAN0RMPTR3 RSCAN0.RMPTR3.UINT32
#define RSCAN0RMPTR3L RSCAN0.RMPTR3.UINT16[L]
#define RSCAN0RMPTR3LL RSCAN0.RMPTR3.UINT8[LL]
#define RSCAN0RMPTR3LH RSCAN0.RMPTR3.UINT8[LH]
#define RSCAN0RMPTR3H RSCAN0.RMPTR3.UINT16[H]
#define RSCAN0RMPTR3HL RSCAN0.RMPTR3.UINT8[HL]
#define RSCAN0RMPTR3HH RSCAN0.RMPTR3.UINT8[HH]
#define RSCAN0RMDF03 RSCAN0.RMDF03.UINT32
#define RSCAN0RMDF03L RSCAN0.RMDF03.UINT16[L]
#define RSCAN0RMDF03LL RSCAN0.RMDF03.UINT8[LL]
#define RSCAN0RMDF03LH RSCAN0.RMDF03.UINT8[LH]
#define RSCAN0RMDF03H RSCAN0.RMDF03.UINT16[H]
#define RSCAN0RMDF03HL RSCAN0.RMDF03.UINT8[HL]
#define RSCAN0RMDF03HH RSCAN0.RMDF03.UINT8[HH]
#define RSCAN0RMDF13 RSCAN0.RMDF13.UINT32
#define RSCAN0RMDF13L RSCAN0.RMDF13.UINT16[L]
#define RSCAN0RMDF13LL RSCAN0.RMDF13.UINT8[LL]
#define RSCAN0RMDF13LH RSCAN0.RMDF13.UINT8[LH]
#define RSCAN0RMDF13H RSCAN0.RMDF13.UINT16[H]
#define RSCAN0RMDF13HL RSCAN0.RMDF13.UINT8[HL]
#define RSCAN0RMDF13HH RSCAN0.RMDF13.UINT8[HH]
#define RSCAN0RMID4 RSCAN0.RMID4.UINT32
#define RSCAN0RMID4L RSCAN0.RMID4.UINT16[L]
#define RSCAN0RMID4LL RSCAN0.RMID4.UINT8[LL]
#define RSCAN0RMID4LH RSCAN0.RMID4.UINT8[LH]
#define RSCAN0RMID4H RSCAN0.RMID4.UINT16[H]
#define RSCAN0RMID4HL RSCAN0.RMID4.UINT8[HL]
#define RSCAN0RMID4HH RSCAN0.RMID4.UINT8[HH]
#define RSCAN0RMPTR4 RSCAN0.RMPTR4.UINT32
#define RSCAN0RMPTR4L RSCAN0.RMPTR4.UINT16[L]
#define RSCAN0RMPTR4LL RSCAN0.RMPTR4.UINT8[LL]
#define RSCAN0RMPTR4LH RSCAN0.RMPTR4.UINT8[LH]
#define RSCAN0RMPTR4H RSCAN0.RMPTR4.UINT16[H]
#define RSCAN0RMPTR4HL RSCAN0.RMPTR4.UINT8[HL]
#define RSCAN0RMPTR4HH RSCAN0.RMPTR4.UINT8[HH]
#define RSCAN0RMDF04 RSCAN0.RMDF04.UINT32
#define RSCAN0RMDF04L RSCAN0.RMDF04.UINT16[L]
#define RSCAN0RMDF04LL RSCAN0.RMDF04.UINT8[LL]
#define RSCAN0RMDF04LH RSCAN0.RMDF04.UINT8[LH]
#define RSCAN0RMDF04H RSCAN0.RMDF04.UINT16[H]
#define RSCAN0RMDF04HL RSCAN0.RMDF04.UINT8[HL]
#define RSCAN0RMDF04HH RSCAN0.RMDF04.UINT8[HH]
#define RSCAN0RMDF14 RSCAN0.RMDF14.UINT32
#define RSCAN0RMDF14L RSCAN0.RMDF14.UINT16[L]
#define RSCAN0RMDF14LL RSCAN0.RMDF14.UINT8[LL]
#define RSCAN0RMDF14LH RSCAN0.RMDF14.UINT8[LH]
#define RSCAN0RMDF14H RSCAN0.RMDF14.UINT16[H]
#define RSCAN0RMDF14HL RSCAN0.RMDF14.UINT8[HL]
#define RSCAN0RMDF14HH RSCAN0.RMDF14.UINT8[HH]
#define RSCAN0RMID5 RSCAN0.RMID5.UINT32
#define RSCAN0RMID5L RSCAN0.RMID5.UINT16[L]
#define RSCAN0RMID5LL RSCAN0.RMID5.UINT8[LL]
#define RSCAN0RMID5LH RSCAN0.RMID5.UINT8[LH]
#define RSCAN0RMID5H RSCAN0.RMID5.UINT16[H]
#define RSCAN0RMID5HL RSCAN0.RMID5.UINT8[HL]
#define RSCAN0RMID5HH RSCAN0.RMID5.UINT8[HH]
#define RSCAN0RMPTR5 RSCAN0.RMPTR5.UINT32
#define RSCAN0RMPTR5L RSCAN0.RMPTR5.UINT16[L]
#define RSCAN0RMPTR5LL RSCAN0.RMPTR5.UINT8[LL]
#define RSCAN0RMPTR5LH RSCAN0.RMPTR5.UINT8[LH]
#define RSCAN0RMPTR5H RSCAN0.RMPTR5.UINT16[H]
#define RSCAN0RMPTR5HL RSCAN0.RMPTR5.UINT8[HL]
#define RSCAN0RMPTR5HH RSCAN0.RMPTR5.UINT8[HH]
#define RSCAN0RMDF05 RSCAN0.RMDF05.UINT32
#define RSCAN0RMDF05L RSCAN0.RMDF05.UINT16[L]
#define RSCAN0RMDF05LL RSCAN0.RMDF05.UINT8[LL]
#define RSCAN0RMDF05LH RSCAN0.RMDF05.UINT8[LH]
#define RSCAN0RMDF05H RSCAN0.RMDF05.UINT16[H]
#define RSCAN0RMDF05HL RSCAN0.RMDF05.UINT8[HL]
#define RSCAN0RMDF05HH RSCAN0.RMDF05.UINT8[HH]
#define RSCAN0RMDF15 RSCAN0.RMDF15.UINT32
#define RSCAN0RMDF15L RSCAN0.RMDF15.UINT16[L]
#define RSCAN0RMDF15LL RSCAN0.RMDF15.UINT8[LL]
#define RSCAN0RMDF15LH RSCAN0.RMDF15.UINT8[LH]
#define RSCAN0RMDF15H RSCAN0.RMDF15.UINT16[H]
#define RSCAN0RMDF15HL RSCAN0.RMDF15.UINT8[HL]
#define RSCAN0RMDF15HH RSCAN0.RMDF15.UINT8[HH]
#define RSCAN0RMID6 RSCAN0.RMID6.UINT32
#define RSCAN0RMID6L RSCAN0.RMID6.UINT16[L]
#define RSCAN0RMID6LL RSCAN0.RMID6.UINT8[LL]
#define RSCAN0RMID6LH RSCAN0.RMID6.UINT8[LH]
#define RSCAN0RMID6H RSCAN0.RMID6.UINT16[H]
#define RSCAN0RMID6HL RSCAN0.RMID6.UINT8[HL]
#define RSCAN0RMID6HH RSCAN0.RMID6.UINT8[HH]
#define RSCAN0RMPTR6 RSCAN0.RMPTR6.UINT32
#define RSCAN0RMPTR6L RSCAN0.RMPTR6.UINT16[L]
#define RSCAN0RMPTR6LL RSCAN0.RMPTR6.UINT8[LL]
#define RSCAN0RMPTR6LH RSCAN0.RMPTR6.UINT8[LH]
#define RSCAN0RMPTR6H RSCAN0.RMPTR6.UINT16[H]
#define RSCAN0RMPTR6HL RSCAN0.RMPTR6.UINT8[HL]
#define RSCAN0RMPTR6HH RSCAN0.RMPTR6.UINT8[HH]
#define RSCAN0RMDF06 RSCAN0.RMDF06.UINT32
#define RSCAN0RMDF06L RSCAN0.RMDF06.UINT16[L]
#define RSCAN0RMDF06LL RSCAN0.RMDF06.UINT8[LL]
#define RSCAN0RMDF06LH RSCAN0.RMDF06.UINT8[LH]
#define RSCAN0RMDF06H RSCAN0.RMDF06.UINT16[H]
#define RSCAN0RMDF06HL RSCAN0.RMDF06.UINT8[HL]
#define RSCAN0RMDF06HH RSCAN0.RMDF06.UINT8[HH]
#define RSCAN0RMDF16 RSCAN0.RMDF16.UINT32
#define RSCAN0RMDF16L RSCAN0.RMDF16.UINT16[L]
#define RSCAN0RMDF16LL RSCAN0.RMDF16.UINT8[LL]
#define RSCAN0RMDF16LH RSCAN0.RMDF16.UINT8[LH]
#define RSCAN0RMDF16H RSCAN0.RMDF16.UINT16[H]
#define RSCAN0RMDF16HL RSCAN0.RMDF16.UINT8[HL]
#define RSCAN0RMDF16HH RSCAN0.RMDF16.UINT8[HH]
#define RSCAN0RMID7 RSCAN0.RMID7.UINT32
#define RSCAN0RMID7L RSCAN0.RMID7.UINT16[L]
#define RSCAN0RMID7LL RSCAN0.RMID7.UINT8[LL]
#define RSCAN0RMID7LH RSCAN0.RMID7.UINT8[LH]
#define RSCAN0RMID7H RSCAN0.RMID7.UINT16[H]
#define RSCAN0RMID7HL RSCAN0.RMID7.UINT8[HL]
#define RSCAN0RMID7HH RSCAN0.RMID7.UINT8[HH]
#define RSCAN0RMPTR7 RSCAN0.RMPTR7.UINT32
#define RSCAN0RMPTR7L RSCAN0.RMPTR7.UINT16[L]
#define RSCAN0RMPTR7LL RSCAN0.RMPTR7.UINT8[LL]
#define RSCAN0RMPTR7LH RSCAN0.RMPTR7.UINT8[LH]
#define RSCAN0RMPTR7H RSCAN0.RMPTR7.UINT16[H]
#define RSCAN0RMPTR7HL RSCAN0.RMPTR7.UINT8[HL]
#define RSCAN0RMPTR7HH RSCAN0.RMPTR7.UINT8[HH]
#define RSCAN0RMDF07 RSCAN0.RMDF07.UINT32
#define RSCAN0RMDF07L RSCAN0.RMDF07.UINT16[L]
#define RSCAN0RMDF07LL RSCAN0.RMDF07.UINT8[LL]
#define RSCAN0RMDF07LH RSCAN0.RMDF07.UINT8[LH]
#define RSCAN0RMDF07H RSCAN0.RMDF07.UINT16[H]
#define RSCAN0RMDF07HL RSCAN0.RMDF07.UINT8[HL]
#define RSCAN0RMDF07HH RSCAN0.RMDF07.UINT8[HH]
#define RSCAN0RMDF17 RSCAN0.RMDF17.UINT32
#define RSCAN0RMDF17L RSCAN0.RMDF17.UINT16[L]
#define RSCAN0RMDF17LL RSCAN0.RMDF17.UINT8[LL]
#define RSCAN0RMDF17LH RSCAN0.RMDF17.UINT8[LH]
#define RSCAN0RMDF17H RSCAN0.RMDF17.UINT16[H]
#define RSCAN0RMDF17HL RSCAN0.RMDF17.UINT8[HL]
#define RSCAN0RMDF17HH RSCAN0.RMDF17.UINT8[HH]
#define RSCAN0RMID8 RSCAN0.RMID8.UINT32
#define RSCAN0RMID8L RSCAN0.RMID8.UINT16[L]
#define RSCAN0RMID8LL RSCAN0.RMID8.UINT8[LL]
#define RSCAN0RMID8LH RSCAN0.RMID8.UINT8[LH]
#define RSCAN0RMID8H RSCAN0.RMID8.UINT16[H]
#define RSCAN0RMID8HL RSCAN0.RMID8.UINT8[HL]
#define RSCAN0RMID8HH RSCAN0.RMID8.UINT8[HH]
#define RSCAN0RMPTR8 RSCAN0.RMPTR8.UINT32
#define RSCAN0RMPTR8L RSCAN0.RMPTR8.UINT16[L]
#define RSCAN0RMPTR8LL RSCAN0.RMPTR8.UINT8[LL]
#define RSCAN0RMPTR8LH RSCAN0.RMPTR8.UINT8[LH]
#define RSCAN0RMPTR8H RSCAN0.RMPTR8.UINT16[H]
#define RSCAN0RMPTR8HL RSCAN0.RMPTR8.UINT8[HL]
#define RSCAN0RMPTR8HH RSCAN0.RMPTR8.UINT8[HH]
#define RSCAN0RMDF08 RSCAN0.RMDF08.UINT32
#define RSCAN0RMDF08L RSCAN0.RMDF08.UINT16[L]
#define RSCAN0RMDF08LL RSCAN0.RMDF08.UINT8[LL]
#define RSCAN0RMDF08LH RSCAN0.RMDF08.UINT8[LH]
#define RSCAN0RMDF08H RSCAN0.RMDF08.UINT16[H]
#define RSCAN0RMDF08HL RSCAN0.RMDF08.UINT8[HL]
#define RSCAN0RMDF08HH RSCAN0.RMDF08.UINT8[HH]
#define RSCAN0RMDF18 RSCAN0.RMDF18.UINT32
#define RSCAN0RMDF18L RSCAN0.RMDF18.UINT16[L]
#define RSCAN0RMDF18LL RSCAN0.RMDF18.UINT8[LL]
#define RSCAN0RMDF18LH RSCAN0.RMDF18.UINT8[LH]
#define RSCAN0RMDF18H RSCAN0.RMDF18.UINT16[H]
#define RSCAN0RMDF18HL RSCAN0.RMDF18.UINT8[HL]
#define RSCAN0RMDF18HH RSCAN0.RMDF18.UINT8[HH]
#define RSCAN0RMID9 RSCAN0.RMID9.UINT32
#define RSCAN0RMID9L RSCAN0.RMID9.UINT16[L]
#define RSCAN0RMID9LL RSCAN0.RMID9.UINT8[LL]
#define RSCAN0RMID9LH RSCAN0.RMID9.UINT8[LH]
#define RSCAN0RMID9H RSCAN0.RMID9.UINT16[H]
#define RSCAN0RMID9HL RSCAN0.RMID9.UINT8[HL]
#define RSCAN0RMID9HH RSCAN0.RMID9.UINT8[HH]
#define RSCAN0RMPTR9 RSCAN0.RMPTR9.UINT32
#define RSCAN0RMPTR9L RSCAN0.RMPTR9.UINT16[L]
#define RSCAN0RMPTR9LL RSCAN0.RMPTR9.UINT8[LL]
#define RSCAN0RMPTR9LH RSCAN0.RMPTR9.UINT8[LH]
#define RSCAN0RMPTR9H RSCAN0.RMPTR9.UINT16[H]
#define RSCAN0RMPTR9HL RSCAN0.RMPTR9.UINT8[HL]
#define RSCAN0RMPTR9HH RSCAN0.RMPTR9.UINT8[HH]
#define RSCAN0RMDF09 RSCAN0.RMDF09.UINT32
#define RSCAN0RMDF09L RSCAN0.RMDF09.UINT16[L]
#define RSCAN0RMDF09LL RSCAN0.RMDF09.UINT8[LL]
#define RSCAN0RMDF09LH RSCAN0.RMDF09.UINT8[LH]
#define RSCAN0RMDF09H RSCAN0.RMDF09.UINT16[H]
#define RSCAN0RMDF09HL RSCAN0.RMDF09.UINT8[HL]
#define RSCAN0RMDF09HH RSCAN0.RMDF09.UINT8[HH]
#define RSCAN0RMDF19 RSCAN0.RMDF19.UINT32
#define RSCAN0RMDF19L RSCAN0.RMDF19.UINT16[L]
#define RSCAN0RMDF19LL RSCAN0.RMDF19.UINT8[LL]
#define RSCAN0RMDF19LH RSCAN0.RMDF19.UINT8[LH]
#define RSCAN0RMDF19H RSCAN0.RMDF19.UINT16[H]
#define RSCAN0RMDF19HL RSCAN0.RMDF19.UINT8[HL]
#define RSCAN0RMDF19HH RSCAN0.RMDF19.UINT8[HH]
#define RSCAN0RMID10 RSCAN0.RMID10.UINT32
#define RSCAN0RMID10L RSCAN0.RMID10.UINT16[L]
#define RSCAN0RMID10LL RSCAN0.RMID10.UINT8[LL]
#define RSCAN0RMID10LH RSCAN0.RMID10.UINT8[LH]
#define RSCAN0RMID10H RSCAN0.RMID10.UINT16[H]
#define RSCAN0RMID10HL RSCAN0.RMID10.UINT8[HL]
#define RSCAN0RMID10HH RSCAN0.RMID10.UINT8[HH]
#define RSCAN0RMPTR10 RSCAN0.RMPTR10.UINT32
#define RSCAN0RMPTR10L RSCAN0.RMPTR10.UINT16[L]
#define RSCAN0RMPTR10LL RSCAN0.RMPTR10.UINT8[LL]
#define RSCAN0RMPTR10LH RSCAN0.RMPTR10.UINT8[LH]
#define RSCAN0RMPTR10H RSCAN0.RMPTR10.UINT16[H]
#define RSCAN0RMPTR10HL RSCAN0.RMPTR10.UINT8[HL]
#define RSCAN0RMPTR10HH RSCAN0.RMPTR10.UINT8[HH]
#define RSCAN0RMDF010 RSCAN0.RMDF010.UINT32
#define RSCAN0RMDF010L RSCAN0.RMDF010.UINT16[L]
#define RSCAN0RMDF010LL RSCAN0.RMDF010.UINT8[LL]
#define RSCAN0RMDF010LH RSCAN0.RMDF010.UINT8[LH]
#define RSCAN0RMDF010H RSCAN0.RMDF010.UINT16[H]
#define RSCAN0RMDF010HL RSCAN0.RMDF010.UINT8[HL]
#define RSCAN0RMDF010HH RSCAN0.RMDF010.UINT8[HH]
#define RSCAN0RMDF110 RSCAN0.RMDF110.UINT32
#define RSCAN0RMDF110L RSCAN0.RMDF110.UINT16[L]
#define RSCAN0RMDF110LL RSCAN0.RMDF110.UINT8[LL]
#define RSCAN0RMDF110LH RSCAN0.RMDF110.UINT8[LH]
#define RSCAN0RMDF110H RSCAN0.RMDF110.UINT16[H]
#define RSCAN0RMDF110HL RSCAN0.RMDF110.UINT8[HL]
#define RSCAN0RMDF110HH RSCAN0.RMDF110.UINT8[HH]
#define RSCAN0RMID11 RSCAN0.RMID11.UINT32
#define RSCAN0RMID11L RSCAN0.RMID11.UINT16[L]
#define RSCAN0RMID11LL RSCAN0.RMID11.UINT8[LL]
#define RSCAN0RMID11LH RSCAN0.RMID11.UINT8[LH]
#define RSCAN0RMID11H RSCAN0.RMID11.UINT16[H]
#define RSCAN0RMID11HL RSCAN0.RMID11.UINT8[HL]
#define RSCAN0RMID11HH RSCAN0.RMID11.UINT8[HH]
#define RSCAN0RMPTR11 RSCAN0.RMPTR11.UINT32
#define RSCAN0RMPTR11L RSCAN0.RMPTR11.UINT16[L]
#define RSCAN0RMPTR11LL RSCAN0.RMPTR11.UINT8[LL]
#define RSCAN0RMPTR11LH RSCAN0.RMPTR11.UINT8[LH]
#define RSCAN0RMPTR11H RSCAN0.RMPTR11.UINT16[H]
#define RSCAN0RMPTR11HL RSCAN0.RMPTR11.UINT8[HL]
#define RSCAN0RMPTR11HH RSCAN0.RMPTR11.UINT8[HH]
#define RSCAN0RMDF011 RSCAN0.RMDF011.UINT32
#define RSCAN0RMDF011L RSCAN0.RMDF011.UINT16[L]
#define RSCAN0RMDF011LL RSCAN0.RMDF011.UINT8[LL]
#define RSCAN0RMDF011LH RSCAN0.RMDF011.UINT8[LH]
#define RSCAN0RMDF011H RSCAN0.RMDF011.UINT16[H]
#define RSCAN0RMDF011HL RSCAN0.RMDF011.UINT8[HL]
#define RSCAN0RMDF011HH RSCAN0.RMDF011.UINT8[HH]
#define RSCAN0RMDF111 RSCAN0.RMDF111.UINT32
#define RSCAN0RMDF111L RSCAN0.RMDF111.UINT16[L]
#define RSCAN0RMDF111LL RSCAN0.RMDF111.UINT8[LL]
#define RSCAN0RMDF111LH RSCAN0.RMDF111.UINT8[LH]
#define RSCAN0RMDF111H RSCAN0.RMDF111.UINT16[H]
#define RSCAN0RMDF111HL RSCAN0.RMDF111.UINT8[HL]
#define RSCAN0RMDF111HH RSCAN0.RMDF111.UINT8[HH]
#define RSCAN0RMID12 RSCAN0.RMID12.UINT32
#define RSCAN0RMID12L RSCAN0.RMID12.UINT16[L]
#define RSCAN0RMID12LL RSCAN0.RMID12.UINT8[LL]
#define RSCAN0RMID12LH RSCAN0.RMID12.UINT8[LH]
#define RSCAN0RMID12H RSCAN0.RMID12.UINT16[H]
#define RSCAN0RMID12HL RSCAN0.RMID12.UINT8[HL]
#define RSCAN0RMID12HH RSCAN0.RMID12.UINT8[HH]
#define RSCAN0RMPTR12 RSCAN0.RMPTR12.UINT32
#define RSCAN0RMPTR12L RSCAN0.RMPTR12.UINT16[L]
#define RSCAN0RMPTR12LL RSCAN0.RMPTR12.UINT8[LL]
#define RSCAN0RMPTR12LH RSCAN0.RMPTR12.UINT8[LH]
#define RSCAN0RMPTR12H RSCAN0.RMPTR12.UINT16[H]
#define RSCAN0RMPTR12HL RSCAN0.RMPTR12.UINT8[HL]
#define RSCAN0RMPTR12HH RSCAN0.RMPTR12.UINT8[HH]
#define RSCAN0RMDF012 RSCAN0.RMDF012.UINT32
#define RSCAN0RMDF012L RSCAN0.RMDF012.UINT16[L]
#define RSCAN0RMDF012LL RSCAN0.RMDF012.UINT8[LL]
#define RSCAN0RMDF012LH RSCAN0.RMDF012.UINT8[LH]
#define RSCAN0RMDF012H RSCAN0.RMDF012.UINT16[H]
#define RSCAN0RMDF012HL RSCAN0.RMDF012.UINT8[HL]
#define RSCAN0RMDF012HH RSCAN0.RMDF012.UINT8[HH]
#define RSCAN0RMDF112 RSCAN0.RMDF112.UINT32
#define RSCAN0RMDF112L RSCAN0.RMDF112.UINT16[L]
#define RSCAN0RMDF112LL RSCAN0.RMDF112.UINT8[LL]
#define RSCAN0RMDF112LH RSCAN0.RMDF112.UINT8[LH]
#define RSCAN0RMDF112H RSCAN0.RMDF112.UINT16[H]
#define RSCAN0RMDF112HL RSCAN0.RMDF112.UINT8[HL]
#define RSCAN0RMDF112HH RSCAN0.RMDF112.UINT8[HH]
#define RSCAN0RMID13 RSCAN0.RMID13.UINT32
#define RSCAN0RMID13L RSCAN0.RMID13.UINT16[L]
#define RSCAN0RMID13LL RSCAN0.RMID13.UINT8[LL]
#define RSCAN0RMID13LH RSCAN0.RMID13.UINT8[LH]
#define RSCAN0RMID13H RSCAN0.RMID13.UINT16[H]
#define RSCAN0RMID13HL RSCAN0.RMID13.UINT8[HL]
#define RSCAN0RMID13HH RSCAN0.RMID13.UINT8[HH]
#define RSCAN0RMPTR13 RSCAN0.RMPTR13.UINT32
#define RSCAN0RMPTR13L RSCAN0.RMPTR13.UINT16[L]
#define RSCAN0RMPTR13LL RSCAN0.RMPTR13.UINT8[LL]
#define RSCAN0RMPTR13LH RSCAN0.RMPTR13.UINT8[LH]
#define RSCAN0RMPTR13H RSCAN0.RMPTR13.UINT16[H]
#define RSCAN0RMPTR13HL RSCAN0.RMPTR13.UINT8[HL]
#define RSCAN0RMPTR13HH RSCAN0.RMPTR13.UINT8[HH]
#define RSCAN0RMDF013 RSCAN0.RMDF013.UINT32
#define RSCAN0RMDF013L RSCAN0.RMDF013.UINT16[L]
#define RSCAN0RMDF013LL RSCAN0.RMDF013.UINT8[LL]
#define RSCAN0RMDF013LH RSCAN0.RMDF013.UINT8[LH]
#define RSCAN0RMDF013H RSCAN0.RMDF013.UINT16[H]
#define RSCAN0RMDF013HL RSCAN0.RMDF013.UINT8[HL]
#define RSCAN0RMDF013HH RSCAN0.RMDF013.UINT8[HH]
#define RSCAN0RMDF113 RSCAN0.RMDF113.UINT32
#define RSCAN0RMDF113L RSCAN0.RMDF113.UINT16[L]
#define RSCAN0RMDF113LL RSCAN0.RMDF113.UINT8[LL]
#define RSCAN0RMDF113LH RSCAN0.RMDF113.UINT8[LH]
#define RSCAN0RMDF113H RSCAN0.RMDF113.UINT16[H]
#define RSCAN0RMDF113HL RSCAN0.RMDF113.UINT8[HL]
#define RSCAN0RMDF113HH RSCAN0.RMDF113.UINT8[HH]
#define RSCAN0RMID14 RSCAN0.RMID14.UINT32
#define RSCAN0RMID14L RSCAN0.RMID14.UINT16[L]
#define RSCAN0RMID14LL RSCAN0.RMID14.UINT8[LL]
#define RSCAN0RMID14LH RSCAN0.RMID14.UINT8[LH]
#define RSCAN0RMID14H RSCAN0.RMID14.UINT16[H]
#define RSCAN0RMID14HL RSCAN0.RMID14.UINT8[HL]
#define RSCAN0RMID14HH RSCAN0.RMID14.UINT8[HH]
#define RSCAN0RMPTR14 RSCAN0.RMPTR14.UINT32
#define RSCAN0RMPTR14L RSCAN0.RMPTR14.UINT16[L]
#define RSCAN0RMPTR14LL RSCAN0.RMPTR14.UINT8[LL]
#define RSCAN0RMPTR14LH RSCAN0.RMPTR14.UINT8[LH]
#define RSCAN0RMPTR14H RSCAN0.RMPTR14.UINT16[H]
#define RSCAN0RMPTR14HL RSCAN0.RMPTR14.UINT8[HL]
#define RSCAN0RMPTR14HH RSCAN0.RMPTR14.UINT8[HH]
#define RSCAN0RMDF014 RSCAN0.RMDF014.UINT32
#define RSCAN0RMDF014L RSCAN0.RMDF014.UINT16[L]
#define RSCAN0RMDF014LL RSCAN0.RMDF014.UINT8[LL]
#define RSCAN0RMDF014LH RSCAN0.RMDF014.UINT8[LH]
#define RSCAN0RMDF014H RSCAN0.RMDF014.UINT16[H]
#define RSCAN0RMDF014HL RSCAN0.RMDF014.UINT8[HL]
#define RSCAN0RMDF014HH RSCAN0.RMDF014.UINT8[HH]
#define RSCAN0RMDF114 RSCAN0.RMDF114.UINT32
#define RSCAN0RMDF114L RSCAN0.RMDF114.UINT16[L]
#define RSCAN0RMDF114LL RSCAN0.RMDF114.UINT8[LL]
#define RSCAN0RMDF114LH RSCAN0.RMDF114.UINT8[LH]
#define RSCAN0RMDF114H RSCAN0.RMDF114.UINT16[H]
#define RSCAN0RMDF114HL RSCAN0.RMDF114.UINT8[HL]
#define RSCAN0RMDF114HH RSCAN0.RMDF114.UINT8[HH]
#define RSCAN0RMID15 RSCAN0.RMID15.UINT32
#define RSCAN0RMID15L RSCAN0.RMID15.UINT16[L]
#define RSCAN0RMID15LL RSCAN0.RMID15.UINT8[LL]
#define RSCAN0RMID15LH RSCAN0.RMID15.UINT8[LH]
#define RSCAN0RMID15H RSCAN0.RMID15.UINT16[H]
#define RSCAN0RMID15HL RSCAN0.RMID15.UINT8[HL]
#define RSCAN0RMID15HH RSCAN0.RMID15.UINT8[HH]
#define RSCAN0RMPTR15 RSCAN0.RMPTR15.UINT32
#define RSCAN0RMPTR15L RSCAN0.RMPTR15.UINT16[L]
#define RSCAN0RMPTR15LL RSCAN0.RMPTR15.UINT8[LL]
#define RSCAN0RMPTR15LH RSCAN0.RMPTR15.UINT8[LH]
#define RSCAN0RMPTR15H RSCAN0.RMPTR15.UINT16[H]
#define RSCAN0RMPTR15HL RSCAN0.RMPTR15.UINT8[HL]
#define RSCAN0RMPTR15HH RSCAN0.RMPTR15.UINT8[HH]
#define RSCAN0RMDF015 RSCAN0.RMDF015.UINT32
#define RSCAN0RMDF015L RSCAN0.RMDF015.UINT16[L]
#define RSCAN0RMDF015LL RSCAN0.RMDF015.UINT8[LL]
#define RSCAN0RMDF015LH RSCAN0.RMDF015.UINT8[LH]
#define RSCAN0RMDF015H RSCAN0.RMDF015.UINT16[H]
#define RSCAN0RMDF015HL RSCAN0.RMDF015.UINT8[HL]
#define RSCAN0RMDF015HH RSCAN0.RMDF015.UINT8[HH]
#define RSCAN0RMDF115 RSCAN0.RMDF115.UINT32
#define RSCAN0RMDF115L RSCAN0.RMDF115.UINT16[L]
#define RSCAN0RMDF115LL RSCAN0.RMDF115.UINT8[LL]
#define RSCAN0RMDF115LH RSCAN0.RMDF115.UINT8[LH]
#define RSCAN0RMDF115H RSCAN0.RMDF115.UINT16[H]
#define RSCAN0RMDF115HL RSCAN0.RMDF115.UINT8[HL]
#define RSCAN0RMDF115HH RSCAN0.RMDF115.UINT8[HH]
#define RSCAN0RMID16 RSCAN0.RMID16.UINT32
#define RSCAN0RMID16L RSCAN0.RMID16.UINT16[L]
#define RSCAN0RMID16LL RSCAN0.RMID16.UINT8[LL]
#define RSCAN0RMID16LH RSCAN0.RMID16.UINT8[LH]
#define RSCAN0RMID16H RSCAN0.RMID16.UINT16[H]
#define RSCAN0RMID16HL RSCAN0.RMID16.UINT8[HL]
#define RSCAN0RMID16HH RSCAN0.RMID16.UINT8[HH]
#define RSCAN0RMPTR16 RSCAN0.RMPTR16.UINT32
#define RSCAN0RMPTR16L RSCAN0.RMPTR16.UINT16[L]
#define RSCAN0RMPTR16LL RSCAN0.RMPTR16.UINT8[LL]
#define RSCAN0RMPTR16LH RSCAN0.RMPTR16.UINT8[LH]
#define RSCAN0RMPTR16H RSCAN0.RMPTR16.UINT16[H]
#define RSCAN0RMPTR16HL RSCAN0.RMPTR16.UINT8[HL]
#define RSCAN0RMPTR16HH RSCAN0.RMPTR16.UINT8[HH]
#define RSCAN0RMDF016 RSCAN0.RMDF016.UINT32
#define RSCAN0RMDF016L RSCAN0.RMDF016.UINT16[L]
#define RSCAN0RMDF016LL RSCAN0.RMDF016.UINT8[LL]
#define RSCAN0RMDF016LH RSCAN0.RMDF016.UINT8[LH]
#define RSCAN0RMDF016H RSCAN0.RMDF016.UINT16[H]
#define RSCAN0RMDF016HL RSCAN0.RMDF016.UINT8[HL]
#define RSCAN0RMDF016HH RSCAN0.RMDF016.UINT8[HH]
#define RSCAN0RMDF116 RSCAN0.RMDF116.UINT32
#define RSCAN0RMDF116L RSCAN0.RMDF116.UINT16[L]
#define RSCAN0RMDF116LL RSCAN0.RMDF116.UINT8[LL]
#define RSCAN0RMDF116LH RSCAN0.RMDF116.UINT8[LH]
#define RSCAN0RMDF116H RSCAN0.RMDF116.UINT16[H]
#define RSCAN0RMDF116HL RSCAN0.RMDF116.UINT8[HL]
#define RSCAN0RMDF116HH RSCAN0.RMDF116.UINT8[HH]
#define RSCAN0RMID17 RSCAN0.RMID17.UINT32
#define RSCAN0RMID17L RSCAN0.RMID17.UINT16[L]
#define RSCAN0RMID17LL RSCAN0.RMID17.UINT8[LL]
#define RSCAN0RMID17LH RSCAN0.RMID17.UINT8[LH]
#define RSCAN0RMID17H RSCAN0.RMID17.UINT16[H]
#define RSCAN0RMID17HL RSCAN0.RMID17.UINT8[HL]
#define RSCAN0RMID17HH RSCAN0.RMID17.UINT8[HH]
#define RSCAN0RMPTR17 RSCAN0.RMPTR17.UINT32
#define RSCAN0RMPTR17L RSCAN0.RMPTR17.UINT16[L]
#define RSCAN0RMPTR17LL RSCAN0.RMPTR17.UINT8[LL]
#define RSCAN0RMPTR17LH RSCAN0.RMPTR17.UINT8[LH]
#define RSCAN0RMPTR17H RSCAN0.RMPTR17.UINT16[H]
#define RSCAN0RMPTR17HL RSCAN0.RMPTR17.UINT8[HL]
#define RSCAN0RMPTR17HH RSCAN0.RMPTR17.UINT8[HH]
#define RSCAN0RMDF017 RSCAN0.RMDF017.UINT32
#define RSCAN0RMDF017L RSCAN0.RMDF017.UINT16[L]
#define RSCAN0RMDF017LL RSCAN0.RMDF017.UINT8[LL]
#define RSCAN0RMDF017LH RSCAN0.RMDF017.UINT8[LH]
#define RSCAN0RMDF017H RSCAN0.RMDF017.UINT16[H]
#define RSCAN0RMDF017HL RSCAN0.RMDF017.UINT8[HL]
#define RSCAN0RMDF017HH RSCAN0.RMDF017.UINT8[HH]
#define RSCAN0RMDF117 RSCAN0.RMDF117.UINT32
#define RSCAN0RMDF117L RSCAN0.RMDF117.UINT16[L]
#define RSCAN0RMDF117LL RSCAN0.RMDF117.UINT8[LL]
#define RSCAN0RMDF117LH RSCAN0.RMDF117.UINT8[LH]
#define RSCAN0RMDF117H RSCAN0.RMDF117.UINT16[H]
#define RSCAN0RMDF117HL RSCAN0.RMDF117.UINT8[HL]
#define RSCAN0RMDF117HH RSCAN0.RMDF117.UINT8[HH]
#define RSCAN0RMID18 RSCAN0.RMID18.UINT32
#define RSCAN0RMID18L RSCAN0.RMID18.UINT16[L]
#define RSCAN0RMID18LL RSCAN0.RMID18.UINT8[LL]
#define RSCAN0RMID18LH RSCAN0.RMID18.UINT8[LH]
#define RSCAN0RMID18H RSCAN0.RMID18.UINT16[H]
#define RSCAN0RMID18HL RSCAN0.RMID18.UINT8[HL]
#define RSCAN0RMID18HH RSCAN0.RMID18.UINT8[HH]
#define RSCAN0RMPTR18 RSCAN0.RMPTR18.UINT32
#define RSCAN0RMPTR18L RSCAN0.RMPTR18.UINT16[L]
#define RSCAN0RMPTR18LL RSCAN0.RMPTR18.UINT8[LL]
#define RSCAN0RMPTR18LH RSCAN0.RMPTR18.UINT8[LH]
#define RSCAN0RMPTR18H RSCAN0.RMPTR18.UINT16[H]
#define RSCAN0RMPTR18HL RSCAN0.RMPTR18.UINT8[HL]
#define RSCAN0RMPTR18HH RSCAN0.RMPTR18.UINT8[HH]
#define RSCAN0RMDF018 RSCAN0.RMDF018.UINT32
#define RSCAN0RMDF018L RSCAN0.RMDF018.UINT16[L]
#define RSCAN0RMDF018LL RSCAN0.RMDF018.UINT8[LL]
#define RSCAN0RMDF018LH RSCAN0.RMDF018.UINT8[LH]
#define RSCAN0RMDF018H RSCAN0.RMDF018.UINT16[H]
#define RSCAN0RMDF018HL RSCAN0.RMDF018.UINT8[HL]
#define RSCAN0RMDF018HH RSCAN0.RMDF018.UINT8[HH]
#define RSCAN0RMDF118 RSCAN0.RMDF118.UINT32
#define RSCAN0RMDF118L RSCAN0.RMDF118.UINT16[L]
#define RSCAN0RMDF118LL RSCAN0.RMDF118.UINT8[LL]
#define RSCAN0RMDF118LH RSCAN0.RMDF118.UINT8[LH]
#define RSCAN0RMDF118H RSCAN0.RMDF118.UINT16[H]
#define RSCAN0RMDF118HL RSCAN0.RMDF118.UINT8[HL]
#define RSCAN0RMDF118HH RSCAN0.RMDF118.UINT8[HH]
#define RSCAN0RMID19 RSCAN0.RMID19.UINT32
#define RSCAN0RMID19L RSCAN0.RMID19.UINT16[L]
#define RSCAN0RMID19LL RSCAN0.RMID19.UINT8[LL]
#define RSCAN0RMID19LH RSCAN0.RMID19.UINT8[LH]
#define RSCAN0RMID19H RSCAN0.RMID19.UINT16[H]
#define RSCAN0RMID19HL RSCAN0.RMID19.UINT8[HL]
#define RSCAN0RMID19HH RSCAN0.RMID19.UINT8[HH]
#define RSCAN0RMPTR19 RSCAN0.RMPTR19.UINT32
#define RSCAN0RMPTR19L RSCAN0.RMPTR19.UINT16[L]
#define RSCAN0RMPTR19LL RSCAN0.RMPTR19.UINT8[LL]
#define RSCAN0RMPTR19LH RSCAN0.RMPTR19.UINT8[LH]
#define RSCAN0RMPTR19H RSCAN0.RMPTR19.UINT16[H]
#define RSCAN0RMPTR19HL RSCAN0.RMPTR19.UINT8[HL]
#define RSCAN0RMPTR19HH RSCAN0.RMPTR19.UINT8[HH]
#define RSCAN0RMDF019 RSCAN0.RMDF019.UINT32
#define RSCAN0RMDF019L RSCAN0.RMDF019.UINT16[L]
#define RSCAN0RMDF019LL RSCAN0.RMDF019.UINT8[LL]
#define RSCAN0RMDF019LH RSCAN0.RMDF019.UINT8[LH]
#define RSCAN0RMDF019H RSCAN0.RMDF019.UINT16[H]
#define RSCAN0RMDF019HL RSCAN0.RMDF019.UINT8[HL]
#define RSCAN0RMDF019HH RSCAN0.RMDF019.UINT8[HH]
#define RSCAN0RMDF119 RSCAN0.RMDF119.UINT32
#define RSCAN0RMDF119L RSCAN0.RMDF119.UINT16[L]
#define RSCAN0RMDF119LL RSCAN0.RMDF119.UINT8[LL]
#define RSCAN0RMDF119LH RSCAN0.RMDF119.UINT8[LH]
#define RSCAN0RMDF119H RSCAN0.RMDF119.UINT16[H]
#define RSCAN0RMDF119HL RSCAN0.RMDF119.UINT8[HL]
#define RSCAN0RMDF119HH RSCAN0.RMDF119.UINT8[HH]
#define RSCAN0RMID20 RSCAN0.RMID20.UINT32
#define RSCAN0RMID20L RSCAN0.RMID20.UINT16[L]
#define RSCAN0RMID20LL RSCAN0.RMID20.UINT8[LL]
#define RSCAN0RMID20LH RSCAN0.RMID20.UINT8[LH]
#define RSCAN0RMID20H RSCAN0.RMID20.UINT16[H]
#define RSCAN0RMID20HL RSCAN0.RMID20.UINT8[HL]
#define RSCAN0RMID20HH RSCAN0.RMID20.UINT8[HH]
#define RSCAN0RMPTR20 RSCAN0.RMPTR20.UINT32
#define RSCAN0RMPTR20L RSCAN0.RMPTR20.UINT16[L]
#define RSCAN0RMPTR20LL RSCAN0.RMPTR20.UINT8[LL]
#define RSCAN0RMPTR20LH RSCAN0.RMPTR20.UINT8[LH]
#define RSCAN0RMPTR20H RSCAN0.RMPTR20.UINT16[H]
#define RSCAN0RMPTR20HL RSCAN0.RMPTR20.UINT8[HL]
#define RSCAN0RMPTR20HH RSCAN0.RMPTR20.UINT8[HH]
#define RSCAN0RMDF020 RSCAN0.RMDF020.UINT32
#define RSCAN0RMDF020L RSCAN0.RMDF020.UINT16[L]
#define RSCAN0RMDF020LL RSCAN0.RMDF020.UINT8[LL]
#define RSCAN0RMDF020LH RSCAN0.RMDF020.UINT8[LH]
#define RSCAN0RMDF020H RSCAN0.RMDF020.UINT16[H]
#define RSCAN0RMDF020HL RSCAN0.RMDF020.UINT8[HL]
#define RSCAN0RMDF020HH RSCAN0.RMDF020.UINT8[HH]
#define RSCAN0RMDF120 RSCAN0.RMDF120.UINT32
#define RSCAN0RMDF120L RSCAN0.RMDF120.UINT16[L]
#define RSCAN0RMDF120LL RSCAN0.RMDF120.UINT8[LL]
#define RSCAN0RMDF120LH RSCAN0.RMDF120.UINT8[LH]
#define RSCAN0RMDF120H RSCAN0.RMDF120.UINT16[H]
#define RSCAN0RMDF120HL RSCAN0.RMDF120.UINT8[HL]
#define RSCAN0RMDF120HH RSCAN0.RMDF120.UINT8[HH]
#define RSCAN0RMID21 RSCAN0.RMID21.UINT32
#define RSCAN0RMID21L RSCAN0.RMID21.UINT16[L]
#define RSCAN0RMID21LL RSCAN0.RMID21.UINT8[LL]
#define RSCAN0RMID21LH RSCAN0.RMID21.UINT8[LH]
#define RSCAN0RMID21H RSCAN0.RMID21.UINT16[H]
#define RSCAN0RMID21HL RSCAN0.RMID21.UINT8[HL]
#define RSCAN0RMID21HH RSCAN0.RMID21.UINT8[HH]
#define RSCAN0RMPTR21 RSCAN0.RMPTR21.UINT32
#define RSCAN0RMPTR21L RSCAN0.RMPTR21.UINT16[L]
#define RSCAN0RMPTR21LL RSCAN0.RMPTR21.UINT8[LL]
#define RSCAN0RMPTR21LH RSCAN0.RMPTR21.UINT8[LH]
#define RSCAN0RMPTR21H RSCAN0.RMPTR21.UINT16[H]
#define RSCAN0RMPTR21HL RSCAN0.RMPTR21.UINT8[HL]
#define RSCAN0RMPTR21HH RSCAN0.RMPTR21.UINT8[HH]
#define RSCAN0RMDF021 RSCAN0.RMDF021.UINT32
#define RSCAN0RMDF021L RSCAN0.RMDF021.UINT16[L]
#define RSCAN0RMDF021LL RSCAN0.RMDF021.UINT8[LL]
#define RSCAN0RMDF021LH RSCAN0.RMDF021.UINT8[LH]
#define RSCAN0RMDF021H RSCAN0.RMDF021.UINT16[H]
#define RSCAN0RMDF021HL RSCAN0.RMDF021.UINT8[HL]
#define RSCAN0RMDF021HH RSCAN0.RMDF021.UINT8[HH]
#define RSCAN0RMDF121 RSCAN0.RMDF121.UINT32
#define RSCAN0RMDF121L RSCAN0.RMDF121.UINT16[L]
#define RSCAN0RMDF121LL RSCAN0.RMDF121.UINT8[LL]
#define RSCAN0RMDF121LH RSCAN0.RMDF121.UINT8[LH]
#define RSCAN0RMDF121H RSCAN0.RMDF121.UINT16[H]
#define RSCAN0RMDF121HL RSCAN0.RMDF121.UINT8[HL]
#define RSCAN0RMDF121HH RSCAN0.RMDF121.UINT8[HH]
#define RSCAN0RMID22 RSCAN0.RMID22.UINT32
#define RSCAN0RMID22L RSCAN0.RMID22.UINT16[L]
#define RSCAN0RMID22LL RSCAN0.RMID22.UINT8[LL]
#define RSCAN0RMID22LH RSCAN0.RMID22.UINT8[LH]
#define RSCAN0RMID22H RSCAN0.RMID22.UINT16[H]
#define RSCAN0RMID22HL RSCAN0.RMID22.UINT8[HL]
#define RSCAN0RMID22HH RSCAN0.RMID22.UINT8[HH]
#define RSCAN0RMPTR22 RSCAN0.RMPTR22.UINT32
#define RSCAN0RMPTR22L RSCAN0.RMPTR22.UINT16[L]
#define RSCAN0RMPTR22LL RSCAN0.RMPTR22.UINT8[LL]
#define RSCAN0RMPTR22LH RSCAN0.RMPTR22.UINT8[LH]
#define RSCAN0RMPTR22H RSCAN0.RMPTR22.UINT16[H]
#define RSCAN0RMPTR22HL RSCAN0.RMPTR22.UINT8[HL]
#define RSCAN0RMPTR22HH RSCAN0.RMPTR22.UINT8[HH]
#define RSCAN0RMDF022 RSCAN0.RMDF022.UINT32
#define RSCAN0RMDF022L RSCAN0.RMDF022.UINT16[L]
#define RSCAN0RMDF022LL RSCAN0.RMDF022.UINT8[LL]
#define RSCAN0RMDF022LH RSCAN0.RMDF022.UINT8[LH]
#define RSCAN0RMDF022H RSCAN0.RMDF022.UINT16[H]
#define RSCAN0RMDF022HL RSCAN0.RMDF022.UINT8[HL]
#define RSCAN0RMDF022HH RSCAN0.RMDF022.UINT8[HH]
#define RSCAN0RMDF122 RSCAN0.RMDF122.UINT32
#define RSCAN0RMDF122L RSCAN0.RMDF122.UINT16[L]
#define RSCAN0RMDF122LL RSCAN0.RMDF122.UINT8[LL]
#define RSCAN0RMDF122LH RSCAN0.RMDF122.UINT8[LH]
#define RSCAN0RMDF122H RSCAN0.RMDF122.UINT16[H]
#define RSCAN0RMDF122HL RSCAN0.RMDF122.UINT8[HL]
#define RSCAN0RMDF122HH RSCAN0.RMDF122.UINT8[HH]
#define RSCAN0RMID23 RSCAN0.RMID23.UINT32
#define RSCAN0RMID23L RSCAN0.RMID23.UINT16[L]
#define RSCAN0RMID23LL RSCAN0.RMID23.UINT8[LL]
#define RSCAN0RMID23LH RSCAN0.RMID23.UINT8[LH]
#define RSCAN0RMID23H RSCAN0.RMID23.UINT16[H]
#define RSCAN0RMID23HL RSCAN0.RMID23.UINT8[HL]
#define RSCAN0RMID23HH RSCAN0.RMID23.UINT8[HH]
#define RSCAN0RMPTR23 RSCAN0.RMPTR23.UINT32
#define RSCAN0RMPTR23L RSCAN0.RMPTR23.UINT16[L]
#define RSCAN0RMPTR23LL RSCAN0.RMPTR23.UINT8[LL]
#define RSCAN0RMPTR23LH RSCAN0.RMPTR23.UINT8[LH]
#define RSCAN0RMPTR23H RSCAN0.RMPTR23.UINT16[H]
#define RSCAN0RMPTR23HL RSCAN0.RMPTR23.UINT8[HL]
#define RSCAN0RMPTR23HH RSCAN0.RMPTR23.UINT8[HH]
#define RSCAN0RMDF023 RSCAN0.RMDF023.UINT32
#define RSCAN0RMDF023L RSCAN0.RMDF023.UINT16[L]
#define RSCAN0RMDF023LL RSCAN0.RMDF023.UINT8[LL]
#define RSCAN0RMDF023LH RSCAN0.RMDF023.UINT8[LH]
#define RSCAN0RMDF023H RSCAN0.RMDF023.UINT16[H]
#define RSCAN0RMDF023HL RSCAN0.RMDF023.UINT8[HL]
#define RSCAN0RMDF023HH RSCAN0.RMDF023.UINT8[HH]
#define RSCAN0RMDF123 RSCAN0.RMDF123.UINT32
#define RSCAN0RMDF123L RSCAN0.RMDF123.UINT16[L]
#define RSCAN0RMDF123LL RSCAN0.RMDF123.UINT8[LL]
#define RSCAN0RMDF123LH RSCAN0.RMDF123.UINT8[LH]
#define RSCAN0RMDF123H RSCAN0.RMDF123.UINT16[H]
#define RSCAN0RMDF123HL RSCAN0.RMDF123.UINT8[HL]
#define RSCAN0RMDF123HH RSCAN0.RMDF123.UINT8[HH]
#define RSCAN0RMID24 RSCAN0.RMID24.UINT32
#define RSCAN0RMID24L RSCAN0.RMID24.UINT16[L]
#define RSCAN0RMID24LL RSCAN0.RMID24.UINT8[LL]
#define RSCAN0RMID24LH RSCAN0.RMID24.UINT8[LH]
#define RSCAN0RMID24H RSCAN0.RMID24.UINT16[H]
#define RSCAN0RMID24HL RSCAN0.RMID24.UINT8[HL]
#define RSCAN0RMID24HH RSCAN0.RMID24.UINT8[HH]
#define RSCAN0RMPTR24 RSCAN0.RMPTR24.UINT32
#define RSCAN0RMPTR24L RSCAN0.RMPTR24.UINT16[L]
#define RSCAN0RMPTR24LL RSCAN0.RMPTR24.UINT8[LL]
#define RSCAN0RMPTR24LH RSCAN0.RMPTR24.UINT8[LH]
#define RSCAN0RMPTR24H RSCAN0.RMPTR24.UINT16[H]
#define RSCAN0RMPTR24HL RSCAN0.RMPTR24.UINT8[HL]
#define RSCAN0RMPTR24HH RSCAN0.RMPTR24.UINT8[HH]
#define RSCAN0RMDF024 RSCAN0.RMDF024.UINT32
#define RSCAN0RMDF024L RSCAN0.RMDF024.UINT16[L]
#define RSCAN0RMDF024LL RSCAN0.RMDF024.UINT8[LL]
#define RSCAN0RMDF024LH RSCAN0.RMDF024.UINT8[LH]
#define RSCAN0RMDF024H RSCAN0.RMDF024.UINT16[H]
#define RSCAN0RMDF024HL RSCAN0.RMDF024.UINT8[HL]
#define RSCAN0RMDF024HH RSCAN0.RMDF024.UINT8[HH]
#define RSCAN0RMDF124 RSCAN0.RMDF124.UINT32
#define RSCAN0RMDF124L RSCAN0.RMDF124.UINT16[L]
#define RSCAN0RMDF124LL RSCAN0.RMDF124.UINT8[LL]
#define RSCAN0RMDF124LH RSCAN0.RMDF124.UINT8[LH]
#define RSCAN0RMDF124H RSCAN0.RMDF124.UINT16[H]
#define RSCAN0RMDF124HL RSCAN0.RMDF124.UINT8[HL]
#define RSCAN0RMDF124HH RSCAN0.RMDF124.UINT8[HH]
#define RSCAN0RMID25 RSCAN0.RMID25.UINT32
#define RSCAN0RMID25L RSCAN0.RMID25.UINT16[L]
#define RSCAN0RMID25LL RSCAN0.RMID25.UINT8[LL]
#define RSCAN0RMID25LH RSCAN0.RMID25.UINT8[LH]
#define RSCAN0RMID25H RSCAN0.RMID25.UINT16[H]
#define RSCAN0RMID25HL RSCAN0.RMID25.UINT8[HL]
#define RSCAN0RMID25HH RSCAN0.RMID25.UINT8[HH]
#define RSCAN0RMPTR25 RSCAN0.RMPTR25.UINT32
#define RSCAN0RMPTR25L RSCAN0.RMPTR25.UINT16[L]
#define RSCAN0RMPTR25LL RSCAN0.RMPTR25.UINT8[LL]
#define RSCAN0RMPTR25LH RSCAN0.RMPTR25.UINT8[LH]
#define RSCAN0RMPTR25H RSCAN0.RMPTR25.UINT16[H]
#define RSCAN0RMPTR25HL RSCAN0.RMPTR25.UINT8[HL]
#define RSCAN0RMPTR25HH RSCAN0.RMPTR25.UINT8[HH]
#define RSCAN0RMDF025 RSCAN0.RMDF025.UINT32
#define RSCAN0RMDF025L RSCAN0.RMDF025.UINT16[L]
#define RSCAN0RMDF025LL RSCAN0.RMDF025.UINT8[LL]
#define RSCAN0RMDF025LH RSCAN0.RMDF025.UINT8[LH]
#define RSCAN0RMDF025H RSCAN0.RMDF025.UINT16[H]
#define RSCAN0RMDF025HL RSCAN0.RMDF025.UINT8[HL]
#define RSCAN0RMDF025HH RSCAN0.RMDF025.UINT8[HH]
#define RSCAN0RMDF125 RSCAN0.RMDF125.UINT32
#define RSCAN0RMDF125L RSCAN0.RMDF125.UINT16[L]
#define RSCAN0RMDF125LL RSCAN0.RMDF125.UINT8[LL]
#define RSCAN0RMDF125LH RSCAN0.RMDF125.UINT8[LH]
#define RSCAN0RMDF125H RSCAN0.RMDF125.UINT16[H]
#define RSCAN0RMDF125HL RSCAN0.RMDF125.UINT8[HL]
#define RSCAN0RMDF125HH RSCAN0.RMDF125.UINT8[HH]
#define RSCAN0RMID26 RSCAN0.RMID26.UINT32
#define RSCAN0RMID26L RSCAN0.RMID26.UINT16[L]
#define RSCAN0RMID26LL RSCAN0.RMID26.UINT8[LL]
#define RSCAN0RMID26LH RSCAN0.RMID26.UINT8[LH]
#define RSCAN0RMID26H RSCAN0.RMID26.UINT16[H]
#define RSCAN0RMID26HL RSCAN0.RMID26.UINT8[HL]
#define RSCAN0RMID26HH RSCAN0.RMID26.UINT8[HH]
#define RSCAN0RMPTR26 RSCAN0.RMPTR26.UINT32
#define RSCAN0RMPTR26L RSCAN0.RMPTR26.UINT16[L]
#define RSCAN0RMPTR26LL RSCAN0.RMPTR26.UINT8[LL]
#define RSCAN0RMPTR26LH RSCAN0.RMPTR26.UINT8[LH]
#define RSCAN0RMPTR26H RSCAN0.RMPTR26.UINT16[H]
#define RSCAN0RMPTR26HL RSCAN0.RMPTR26.UINT8[HL]
#define RSCAN0RMPTR26HH RSCAN0.RMPTR26.UINT8[HH]
#define RSCAN0RMDF026 RSCAN0.RMDF026.UINT32
#define RSCAN0RMDF026L RSCAN0.RMDF026.UINT16[L]
#define RSCAN0RMDF026LL RSCAN0.RMDF026.UINT8[LL]
#define RSCAN0RMDF026LH RSCAN0.RMDF026.UINT8[LH]
#define RSCAN0RMDF026H RSCAN0.RMDF026.UINT16[H]
#define RSCAN0RMDF026HL RSCAN0.RMDF026.UINT8[HL]
#define RSCAN0RMDF026HH RSCAN0.RMDF026.UINT8[HH]
#define RSCAN0RMDF126 RSCAN0.RMDF126.UINT32
#define RSCAN0RMDF126L RSCAN0.RMDF126.UINT16[L]
#define RSCAN0RMDF126LL RSCAN0.RMDF126.UINT8[LL]
#define RSCAN0RMDF126LH RSCAN0.RMDF126.UINT8[LH]
#define RSCAN0RMDF126H RSCAN0.RMDF126.UINT16[H]
#define RSCAN0RMDF126HL RSCAN0.RMDF126.UINT8[HL]
#define RSCAN0RMDF126HH RSCAN0.RMDF126.UINT8[HH]
#define RSCAN0RMID27 RSCAN0.RMID27.UINT32
#define RSCAN0RMID27L RSCAN0.RMID27.UINT16[L]
#define RSCAN0RMID27LL RSCAN0.RMID27.UINT8[LL]
#define RSCAN0RMID27LH RSCAN0.RMID27.UINT8[LH]
#define RSCAN0RMID27H RSCAN0.RMID27.UINT16[H]
#define RSCAN0RMID27HL RSCAN0.RMID27.UINT8[HL]
#define RSCAN0RMID27HH RSCAN0.RMID27.UINT8[HH]
#define RSCAN0RMPTR27 RSCAN0.RMPTR27.UINT32
#define RSCAN0RMPTR27L RSCAN0.RMPTR27.UINT16[L]
#define RSCAN0RMPTR27LL RSCAN0.RMPTR27.UINT8[LL]
#define RSCAN0RMPTR27LH RSCAN0.RMPTR27.UINT8[LH]
#define RSCAN0RMPTR27H RSCAN0.RMPTR27.UINT16[H]
#define RSCAN0RMPTR27HL RSCAN0.RMPTR27.UINT8[HL]
#define RSCAN0RMPTR27HH RSCAN0.RMPTR27.UINT8[HH]
#define RSCAN0RMDF027 RSCAN0.RMDF027.UINT32
#define RSCAN0RMDF027L RSCAN0.RMDF027.UINT16[L]
#define RSCAN0RMDF027LL RSCAN0.RMDF027.UINT8[LL]
#define RSCAN0RMDF027LH RSCAN0.RMDF027.UINT8[LH]
#define RSCAN0RMDF027H RSCAN0.RMDF027.UINT16[H]
#define RSCAN0RMDF027HL RSCAN0.RMDF027.UINT8[HL]
#define RSCAN0RMDF027HH RSCAN0.RMDF027.UINT8[HH]
#define RSCAN0RMDF127 RSCAN0.RMDF127.UINT32
#define RSCAN0RMDF127L RSCAN0.RMDF127.UINT16[L]
#define RSCAN0RMDF127LL RSCAN0.RMDF127.UINT8[LL]
#define RSCAN0RMDF127LH RSCAN0.RMDF127.UINT8[LH]
#define RSCAN0RMDF127H RSCAN0.RMDF127.UINT16[H]
#define RSCAN0RMDF127HL RSCAN0.RMDF127.UINT8[HL]
#define RSCAN0RMDF127HH RSCAN0.RMDF127.UINT8[HH]
#define RSCAN0RMID28 RSCAN0.RMID28.UINT32
#define RSCAN0RMID28L RSCAN0.RMID28.UINT16[L]
#define RSCAN0RMID28LL RSCAN0.RMID28.UINT8[LL]
#define RSCAN0RMID28LH RSCAN0.RMID28.UINT8[LH]
#define RSCAN0RMID28H RSCAN0.RMID28.UINT16[H]
#define RSCAN0RMID28HL RSCAN0.RMID28.UINT8[HL]
#define RSCAN0RMID28HH RSCAN0.RMID28.UINT8[HH]
#define RSCAN0RMPTR28 RSCAN0.RMPTR28.UINT32
#define RSCAN0RMPTR28L RSCAN0.RMPTR28.UINT16[L]
#define RSCAN0RMPTR28LL RSCAN0.RMPTR28.UINT8[LL]
#define RSCAN0RMPTR28LH RSCAN0.RMPTR28.UINT8[LH]
#define RSCAN0RMPTR28H RSCAN0.RMPTR28.UINT16[H]
#define RSCAN0RMPTR28HL RSCAN0.RMPTR28.UINT8[HL]
#define RSCAN0RMPTR28HH RSCAN0.RMPTR28.UINT8[HH]
#define RSCAN0RMDF028 RSCAN0.RMDF028.UINT32
#define RSCAN0RMDF028L RSCAN0.RMDF028.UINT16[L]
#define RSCAN0RMDF028LL RSCAN0.RMDF028.UINT8[LL]
#define RSCAN0RMDF028LH RSCAN0.RMDF028.UINT8[LH]
#define RSCAN0RMDF028H RSCAN0.RMDF028.UINT16[H]
#define RSCAN0RMDF028HL RSCAN0.RMDF028.UINT8[HL]
#define RSCAN0RMDF028HH RSCAN0.RMDF028.UINT8[HH]
#define RSCAN0RMDF128 RSCAN0.RMDF128.UINT32
#define RSCAN0RMDF128L RSCAN0.RMDF128.UINT16[L]
#define RSCAN0RMDF128LL RSCAN0.RMDF128.UINT8[LL]
#define RSCAN0RMDF128LH RSCAN0.RMDF128.UINT8[LH]
#define RSCAN0RMDF128H RSCAN0.RMDF128.UINT16[H]
#define RSCAN0RMDF128HL RSCAN0.RMDF128.UINT8[HL]
#define RSCAN0RMDF128HH RSCAN0.RMDF128.UINT8[HH]
#define RSCAN0RMID29 RSCAN0.RMID29.UINT32
#define RSCAN0RMID29L RSCAN0.RMID29.UINT16[L]
#define RSCAN0RMID29LL RSCAN0.RMID29.UINT8[LL]
#define RSCAN0RMID29LH RSCAN0.RMID29.UINT8[LH]
#define RSCAN0RMID29H RSCAN0.RMID29.UINT16[H]
#define RSCAN0RMID29HL RSCAN0.RMID29.UINT8[HL]
#define RSCAN0RMID29HH RSCAN0.RMID29.UINT8[HH]
#define RSCAN0RMPTR29 RSCAN0.RMPTR29.UINT32
#define RSCAN0RMPTR29L RSCAN0.RMPTR29.UINT16[L]
#define RSCAN0RMPTR29LL RSCAN0.RMPTR29.UINT8[LL]
#define RSCAN0RMPTR29LH RSCAN0.RMPTR29.UINT8[LH]
#define RSCAN0RMPTR29H RSCAN0.RMPTR29.UINT16[H]
#define RSCAN0RMPTR29HL RSCAN0.RMPTR29.UINT8[HL]
#define RSCAN0RMPTR29HH RSCAN0.RMPTR29.UINT8[HH]
#define RSCAN0RMDF029 RSCAN0.RMDF029.UINT32
#define RSCAN0RMDF029L RSCAN0.RMDF029.UINT16[L]
#define RSCAN0RMDF029LL RSCAN0.RMDF029.UINT8[LL]
#define RSCAN0RMDF029LH RSCAN0.RMDF029.UINT8[LH]
#define RSCAN0RMDF029H RSCAN0.RMDF029.UINT16[H]
#define RSCAN0RMDF029HL RSCAN0.RMDF029.UINT8[HL]
#define RSCAN0RMDF029HH RSCAN0.RMDF029.UINT8[HH]
#define RSCAN0RMDF129 RSCAN0.RMDF129.UINT32
#define RSCAN0RMDF129L RSCAN0.RMDF129.UINT16[L]
#define RSCAN0RMDF129LL RSCAN0.RMDF129.UINT8[LL]
#define RSCAN0RMDF129LH RSCAN0.RMDF129.UINT8[LH]
#define RSCAN0RMDF129H RSCAN0.RMDF129.UINT16[H]
#define RSCAN0RMDF129HL RSCAN0.RMDF129.UINT8[HL]
#define RSCAN0RMDF129HH RSCAN0.RMDF129.UINT8[HH]
#define RSCAN0RMID30 RSCAN0.RMID30.UINT32
#define RSCAN0RMID30L RSCAN0.RMID30.UINT16[L]
#define RSCAN0RMID30LL RSCAN0.RMID30.UINT8[LL]
#define RSCAN0RMID30LH RSCAN0.RMID30.UINT8[LH]
#define RSCAN0RMID30H RSCAN0.RMID30.UINT16[H]
#define RSCAN0RMID30HL RSCAN0.RMID30.UINT8[HL]
#define RSCAN0RMID30HH RSCAN0.RMID30.UINT8[HH]
#define RSCAN0RMPTR30 RSCAN0.RMPTR30.UINT32
#define RSCAN0RMPTR30L RSCAN0.RMPTR30.UINT16[L]
#define RSCAN0RMPTR30LL RSCAN0.RMPTR30.UINT8[LL]
#define RSCAN0RMPTR30LH RSCAN0.RMPTR30.UINT8[LH]
#define RSCAN0RMPTR30H RSCAN0.RMPTR30.UINT16[H]
#define RSCAN0RMPTR30HL RSCAN0.RMPTR30.UINT8[HL]
#define RSCAN0RMPTR30HH RSCAN0.RMPTR30.UINT8[HH]
#define RSCAN0RMDF030 RSCAN0.RMDF030.UINT32
#define RSCAN0RMDF030L RSCAN0.RMDF030.UINT16[L]
#define RSCAN0RMDF030LL RSCAN0.RMDF030.UINT8[LL]
#define RSCAN0RMDF030LH RSCAN0.RMDF030.UINT8[LH]
#define RSCAN0RMDF030H RSCAN0.RMDF030.UINT16[H]
#define RSCAN0RMDF030HL RSCAN0.RMDF030.UINT8[HL]
#define RSCAN0RMDF030HH RSCAN0.RMDF030.UINT8[HH]
#define RSCAN0RMDF130 RSCAN0.RMDF130.UINT32
#define RSCAN0RMDF130L RSCAN0.RMDF130.UINT16[L]
#define RSCAN0RMDF130LL RSCAN0.RMDF130.UINT8[LL]
#define RSCAN0RMDF130LH RSCAN0.RMDF130.UINT8[LH]
#define RSCAN0RMDF130H RSCAN0.RMDF130.UINT16[H]
#define RSCAN0RMDF130HL RSCAN0.RMDF130.UINT8[HL]
#define RSCAN0RMDF130HH RSCAN0.RMDF130.UINT8[HH]
#define RSCAN0RMID31 RSCAN0.RMID31.UINT32
#define RSCAN0RMID31L RSCAN0.RMID31.UINT16[L]
#define RSCAN0RMID31LL RSCAN0.RMID31.UINT8[LL]
#define RSCAN0RMID31LH RSCAN0.RMID31.UINT8[LH]
#define RSCAN0RMID31H RSCAN0.RMID31.UINT16[H]
#define RSCAN0RMID31HL RSCAN0.RMID31.UINT8[HL]
#define RSCAN0RMID31HH RSCAN0.RMID31.UINT8[HH]
#define RSCAN0RMPTR31 RSCAN0.RMPTR31.UINT32
#define RSCAN0RMPTR31L RSCAN0.RMPTR31.UINT16[L]
#define RSCAN0RMPTR31LL RSCAN0.RMPTR31.UINT8[LL]
#define RSCAN0RMPTR31LH RSCAN0.RMPTR31.UINT8[LH]
#define RSCAN0RMPTR31H RSCAN0.RMPTR31.UINT16[H]
#define RSCAN0RMPTR31HL RSCAN0.RMPTR31.UINT8[HL]
#define RSCAN0RMPTR31HH RSCAN0.RMPTR31.UINT8[HH]
#define RSCAN0RMDF031 RSCAN0.RMDF031.UINT32
#define RSCAN0RMDF031L RSCAN0.RMDF031.UINT16[L]
#define RSCAN0RMDF031LL RSCAN0.RMDF031.UINT8[LL]
#define RSCAN0RMDF031LH RSCAN0.RMDF031.UINT8[LH]
#define RSCAN0RMDF031H RSCAN0.RMDF031.UINT16[H]
#define RSCAN0RMDF031HL RSCAN0.RMDF031.UINT8[HL]
#define RSCAN0RMDF031HH RSCAN0.RMDF031.UINT8[HH]
#define RSCAN0RMDF131 RSCAN0.RMDF131.UINT32
#define RSCAN0RMDF131L RSCAN0.RMDF131.UINT16[L]
#define RSCAN0RMDF131LL RSCAN0.RMDF131.UINT8[LL]
#define RSCAN0RMDF131LH RSCAN0.RMDF131.UINT8[LH]
#define RSCAN0RMDF131H RSCAN0.RMDF131.UINT16[H]
#define RSCAN0RMDF131HL RSCAN0.RMDF131.UINT8[HL]
#define RSCAN0RMDF131HH RSCAN0.RMDF131.UINT8[HH]
#define RSCAN0RMID32 RSCAN0.RMID32.UINT32
#define RSCAN0RMID32L RSCAN0.RMID32.UINT16[L]
#define RSCAN0RMID32LL RSCAN0.RMID32.UINT8[LL]
#define RSCAN0RMID32LH RSCAN0.RMID32.UINT8[LH]
#define RSCAN0RMID32H RSCAN0.RMID32.UINT16[H]
#define RSCAN0RMID32HL RSCAN0.RMID32.UINT8[HL]
#define RSCAN0RMID32HH RSCAN0.RMID32.UINT8[HH]
#define RSCAN0RMPTR32 RSCAN0.RMPTR32.UINT32
#define RSCAN0RMPTR32L RSCAN0.RMPTR32.UINT16[L]
#define RSCAN0RMPTR32LL RSCAN0.RMPTR32.UINT8[LL]
#define RSCAN0RMPTR32LH RSCAN0.RMPTR32.UINT8[LH]
#define RSCAN0RMPTR32H RSCAN0.RMPTR32.UINT16[H]
#define RSCAN0RMPTR32HL RSCAN0.RMPTR32.UINT8[HL]
#define RSCAN0RMPTR32HH RSCAN0.RMPTR32.UINT8[HH]
#define RSCAN0RMDF032 RSCAN0.RMDF032.UINT32
#define RSCAN0RMDF032L RSCAN0.RMDF032.UINT16[L]
#define RSCAN0RMDF032LL RSCAN0.RMDF032.UINT8[LL]
#define RSCAN0RMDF032LH RSCAN0.RMDF032.UINT8[LH]
#define RSCAN0RMDF032H RSCAN0.RMDF032.UINT16[H]
#define RSCAN0RMDF032HL RSCAN0.RMDF032.UINT8[HL]
#define RSCAN0RMDF032HH RSCAN0.RMDF032.UINT8[HH]
#define RSCAN0RMDF132 RSCAN0.RMDF132.UINT32
#define RSCAN0RMDF132L RSCAN0.RMDF132.UINT16[L]
#define RSCAN0RMDF132LL RSCAN0.RMDF132.UINT8[LL]
#define RSCAN0RMDF132LH RSCAN0.RMDF132.UINT8[LH]
#define RSCAN0RMDF132H RSCAN0.RMDF132.UINT16[H]
#define RSCAN0RMDF132HL RSCAN0.RMDF132.UINT8[HL]
#define RSCAN0RMDF132HH RSCAN0.RMDF132.UINT8[HH]
#define RSCAN0RMID33 RSCAN0.RMID33.UINT32
#define RSCAN0RMID33L RSCAN0.RMID33.UINT16[L]
#define RSCAN0RMID33LL RSCAN0.RMID33.UINT8[LL]
#define RSCAN0RMID33LH RSCAN0.RMID33.UINT8[LH]
#define RSCAN0RMID33H RSCAN0.RMID33.UINT16[H]
#define RSCAN0RMID33HL RSCAN0.RMID33.UINT8[HL]
#define RSCAN0RMID33HH RSCAN0.RMID33.UINT8[HH]
#define RSCAN0RMPTR33 RSCAN0.RMPTR33.UINT32
#define RSCAN0RMPTR33L RSCAN0.RMPTR33.UINT16[L]
#define RSCAN0RMPTR33LL RSCAN0.RMPTR33.UINT8[LL]
#define RSCAN0RMPTR33LH RSCAN0.RMPTR33.UINT8[LH]
#define RSCAN0RMPTR33H RSCAN0.RMPTR33.UINT16[H]
#define RSCAN0RMPTR33HL RSCAN0.RMPTR33.UINT8[HL]
#define RSCAN0RMPTR33HH RSCAN0.RMPTR33.UINT8[HH]
#define RSCAN0RMDF033 RSCAN0.RMDF033.UINT32
#define RSCAN0RMDF033L RSCAN0.RMDF033.UINT16[L]
#define RSCAN0RMDF033LL RSCAN0.RMDF033.UINT8[LL]
#define RSCAN0RMDF033LH RSCAN0.RMDF033.UINT8[LH]
#define RSCAN0RMDF033H RSCAN0.RMDF033.UINT16[H]
#define RSCAN0RMDF033HL RSCAN0.RMDF033.UINT8[HL]
#define RSCAN0RMDF033HH RSCAN0.RMDF033.UINT8[HH]
#define RSCAN0RMDF133 RSCAN0.RMDF133.UINT32
#define RSCAN0RMDF133L RSCAN0.RMDF133.UINT16[L]
#define RSCAN0RMDF133LL RSCAN0.RMDF133.UINT8[LL]
#define RSCAN0RMDF133LH RSCAN0.RMDF133.UINT8[LH]
#define RSCAN0RMDF133H RSCAN0.RMDF133.UINT16[H]
#define RSCAN0RMDF133HL RSCAN0.RMDF133.UINT8[HL]
#define RSCAN0RMDF133HH RSCAN0.RMDF133.UINT8[HH]
#define RSCAN0RMID34 RSCAN0.RMID34.UINT32
#define RSCAN0RMID34L RSCAN0.RMID34.UINT16[L]
#define RSCAN0RMID34LL RSCAN0.RMID34.UINT8[LL]
#define RSCAN0RMID34LH RSCAN0.RMID34.UINT8[LH]
#define RSCAN0RMID34H RSCAN0.RMID34.UINT16[H]
#define RSCAN0RMID34HL RSCAN0.RMID34.UINT8[HL]
#define RSCAN0RMID34HH RSCAN0.RMID34.UINT8[HH]
#define RSCAN0RMPTR34 RSCAN0.RMPTR34.UINT32
#define RSCAN0RMPTR34L RSCAN0.RMPTR34.UINT16[L]
#define RSCAN0RMPTR34LL RSCAN0.RMPTR34.UINT8[LL]
#define RSCAN0RMPTR34LH RSCAN0.RMPTR34.UINT8[LH]
#define RSCAN0RMPTR34H RSCAN0.RMPTR34.UINT16[H]
#define RSCAN0RMPTR34HL RSCAN0.RMPTR34.UINT8[HL]
#define RSCAN0RMPTR34HH RSCAN0.RMPTR34.UINT8[HH]
#define RSCAN0RMDF034 RSCAN0.RMDF034.UINT32
#define RSCAN0RMDF034L RSCAN0.RMDF034.UINT16[L]
#define RSCAN0RMDF034LL RSCAN0.RMDF034.UINT8[LL]
#define RSCAN0RMDF034LH RSCAN0.RMDF034.UINT8[LH]
#define RSCAN0RMDF034H RSCAN0.RMDF034.UINT16[H]
#define RSCAN0RMDF034HL RSCAN0.RMDF034.UINT8[HL]
#define RSCAN0RMDF034HH RSCAN0.RMDF034.UINT8[HH]
#define RSCAN0RMDF134 RSCAN0.RMDF134.UINT32
#define RSCAN0RMDF134L RSCAN0.RMDF134.UINT16[L]
#define RSCAN0RMDF134LL RSCAN0.RMDF134.UINT8[LL]
#define RSCAN0RMDF134LH RSCAN0.RMDF134.UINT8[LH]
#define RSCAN0RMDF134H RSCAN0.RMDF134.UINT16[H]
#define RSCAN0RMDF134HL RSCAN0.RMDF134.UINT8[HL]
#define RSCAN0RMDF134HH RSCAN0.RMDF134.UINT8[HH]
#define RSCAN0RMID35 RSCAN0.RMID35.UINT32
#define RSCAN0RMID35L RSCAN0.RMID35.UINT16[L]
#define RSCAN0RMID35LL RSCAN0.RMID35.UINT8[LL]
#define RSCAN0RMID35LH RSCAN0.RMID35.UINT8[LH]
#define RSCAN0RMID35H RSCAN0.RMID35.UINT16[H]
#define RSCAN0RMID35HL RSCAN0.RMID35.UINT8[HL]
#define RSCAN0RMID35HH RSCAN0.RMID35.UINT8[HH]
#define RSCAN0RMPTR35 RSCAN0.RMPTR35.UINT32
#define RSCAN0RMPTR35L RSCAN0.RMPTR35.UINT16[L]
#define RSCAN0RMPTR35LL RSCAN0.RMPTR35.UINT8[LL]
#define RSCAN0RMPTR35LH RSCAN0.RMPTR35.UINT8[LH]
#define RSCAN0RMPTR35H RSCAN0.RMPTR35.UINT16[H]
#define RSCAN0RMPTR35HL RSCAN0.RMPTR35.UINT8[HL]
#define RSCAN0RMPTR35HH RSCAN0.RMPTR35.UINT8[HH]
#define RSCAN0RMDF035 RSCAN0.RMDF035.UINT32
#define RSCAN0RMDF035L RSCAN0.RMDF035.UINT16[L]
#define RSCAN0RMDF035LL RSCAN0.RMDF035.UINT8[LL]
#define RSCAN0RMDF035LH RSCAN0.RMDF035.UINT8[LH]
#define RSCAN0RMDF035H RSCAN0.RMDF035.UINT16[H]
#define RSCAN0RMDF035HL RSCAN0.RMDF035.UINT8[HL]
#define RSCAN0RMDF035HH RSCAN0.RMDF035.UINT8[HH]
#define RSCAN0RMDF135 RSCAN0.RMDF135.UINT32
#define RSCAN0RMDF135L RSCAN0.RMDF135.UINT16[L]
#define RSCAN0RMDF135LL RSCAN0.RMDF135.UINT8[LL]
#define RSCAN0RMDF135LH RSCAN0.RMDF135.UINT8[LH]
#define RSCAN0RMDF135H RSCAN0.RMDF135.UINT16[H]
#define RSCAN0RMDF135HL RSCAN0.RMDF135.UINT8[HL]
#define RSCAN0RMDF135HH RSCAN0.RMDF135.UINT8[HH]
#define RSCAN0RMID36 RSCAN0.RMID36.UINT32
#define RSCAN0RMID36L RSCAN0.RMID36.UINT16[L]
#define RSCAN0RMID36LL RSCAN0.RMID36.UINT8[LL]
#define RSCAN0RMID36LH RSCAN0.RMID36.UINT8[LH]
#define RSCAN0RMID36H RSCAN0.RMID36.UINT16[H]
#define RSCAN0RMID36HL RSCAN0.RMID36.UINT8[HL]
#define RSCAN0RMID36HH RSCAN0.RMID36.UINT8[HH]
#define RSCAN0RMPTR36 RSCAN0.RMPTR36.UINT32
#define RSCAN0RMPTR36L RSCAN0.RMPTR36.UINT16[L]
#define RSCAN0RMPTR36LL RSCAN0.RMPTR36.UINT8[LL]
#define RSCAN0RMPTR36LH RSCAN0.RMPTR36.UINT8[LH]
#define RSCAN0RMPTR36H RSCAN0.RMPTR36.UINT16[H]
#define RSCAN0RMPTR36HL RSCAN0.RMPTR36.UINT8[HL]
#define RSCAN0RMPTR36HH RSCAN0.RMPTR36.UINT8[HH]
#define RSCAN0RMDF036 RSCAN0.RMDF036.UINT32
#define RSCAN0RMDF036L RSCAN0.RMDF036.UINT16[L]
#define RSCAN0RMDF036LL RSCAN0.RMDF036.UINT8[LL]
#define RSCAN0RMDF036LH RSCAN0.RMDF036.UINT8[LH]
#define RSCAN0RMDF036H RSCAN0.RMDF036.UINT16[H]
#define RSCAN0RMDF036HL RSCAN0.RMDF036.UINT8[HL]
#define RSCAN0RMDF036HH RSCAN0.RMDF036.UINT8[HH]
#define RSCAN0RMDF136 RSCAN0.RMDF136.UINT32
#define RSCAN0RMDF136L RSCAN0.RMDF136.UINT16[L]
#define RSCAN0RMDF136LL RSCAN0.RMDF136.UINT8[LL]
#define RSCAN0RMDF136LH RSCAN0.RMDF136.UINT8[LH]
#define RSCAN0RMDF136H RSCAN0.RMDF136.UINT16[H]
#define RSCAN0RMDF136HL RSCAN0.RMDF136.UINT8[HL]
#define RSCAN0RMDF136HH RSCAN0.RMDF136.UINT8[HH]
#define RSCAN0RMID37 RSCAN0.RMID37.UINT32
#define RSCAN0RMID37L RSCAN0.RMID37.UINT16[L]
#define RSCAN0RMID37LL RSCAN0.RMID37.UINT8[LL]
#define RSCAN0RMID37LH RSCAN0.RMID37.UINT8[LH]
#define RSCAN0RMID37H RSCAN0.RMID37.UINT16[H]
#define RSCAN0RMID37HL RSCAN0.RMID37.UINT8[HL]
#define RSCAN0RMID37HH RSCAN0.RMID37.UINT8[HH]
#define RSCAN0RMPTR37 RSCAN0.RMPTR37.UINT32
#define RSCAN0RMPTR37L RSCAN0.RMPTR37.UINT16[L]
#define RSCAN0RMPTR37LL RSCAN0.RMPTR37.UINT8[LL]
#define RSCAN0RMPTR37LH RSCAN0.RMPTR37.UINT8[LH]
#define RSCAN0RMPTR37H RSCAN0.RMPTR37.UINT16[H]
#define RSCAN0RMPTR37HL RSCAN0.RMPTR37.UINT8[HL]
#define RSCAN0RMPTR37HH RSCAN0.RMPTR37.UINT8[HH]
#define RSCAN0RMDF037 RSCAN0.RMDF037.UINT32
#define RSCAN0RMDF037L RSCAN0.RMDF037.UINT16[L]
#define RSCAN0RMDF037LL RSCAN0.RMDF037.UINT8[LL]
#define RSCAN0RMDF037LH RSCAN0.RMDF037.UINT8[LH]
#define RSCAN0RMDF037H RSCAN0.RMDF037.UINT16[H]
#define RSCAN0RMDF037HL RSCAN0.RMDF037.UINT8[HL]
#define RSCAN0RMDF037HH RSCAN0.RMDF037.UINT8[HH]
#define RSCAN0RMDF137 RSCAN0.RMDF137.UINT32
#define RSCAN0RMDF137L RSCAN0.RMDF137.UINT16[L]
#define RSCAN0RMDF137LL RSCAN0.RMDF137.UINT8[LL]
#define RSCAN0RMDF137LH RSCAN0.RMDF137.UINT8[LH]
#define RSCAN0RMDF137H RSCAN0.RMDF137.UINT16[H]
#define RSCAN0RMDF137HL RSCAN0.RMDF137.UINT8[HL]
#define RSCAN0RMDF137HH RSCAN0.RMDF137.UINT8[HH]
#define RSCAN0RMID38 RSCAN0.RMID38.UINT32
#define RSCAN0RMID38L RSCAN0.RMID38.UINT16[L]
#define RSCAN0RMID38LL RSCAN0.RMID38.UINT8[LL]
#define RSCAN0RMID38LH RSCAN0.RMID38.UINT8[LH]
#define RSCAN0RMID38H RSCAN0.RMID38.UINT16[H]
#define RSCAN0RMID38HL RSCAN0.RMID38.UINT8[HL]
#define RSCAN0RMID38HH RSCAN0.RMID38.UINT8[HH]
#define RSCAN0RMPTR38 RSCAN0.RMPTR38.UINT32
#define RSCAN0RMPTR38L RSCAN0.RMPTR38.UINT16[L]
#define RSCAN0RMPTR38LL RSCAN0.RMPTR38.UINT8[LL]
#define RSCAN0RMPTR38LH RSCAN0.RMPTR38.UINT8[LH]
#define RSCAN0RMPTR38H RSCAN0.RMPTR38.UINT16[H]
#define RSCAN0RMPTR38HL RSCAN0.RMPTR38.UINT8[HL]
#define RSCAN0RMPTR38HH RSCAN0.RMPTR38.UINT8[HH]
#define RSCAN0RMDF038 RSCAN0.RMDF038.UINT32
#define RSCAN0RMDF038L RSCAN0.RMDF038.UINT16[L]
#define RSCAN0RMDF038LL RSCAN0.RMDF038.UINT8[LL]
#define RSCAN0RMDF038LH RSCAN0.RMDF038.UINT8[LH]
#define RSCAN0RMDF038H RSCAN0.RMDF038.UINT16[H]
#define RSCAN0RMDF038HL RSCAN0.RMDF038.UINT8[HL]
#define RSCAN0RMDF038HH RSCAN0.RMDF038.UINT8[HH]
#define RSCAN0RMDF138 RSCAN0.RMDF138.UINT32
#define RSCAN0RMDF138L RSCAN0.RMDF138.UINT16[L]
#define RSCAN0RMDF138LL RSCAN0.RMDF138.UINT8[LL]
#define RSCAN0RMDF138LH RSCAN0.RMDF138.UINT8[LH]
#define RSCAN0RMDF138H RSCAN0.RMDF138.UINT16[H]
#define RSCAN0RMDF138HL RSCAN0.RMDF138.UINT8[HL]
#define RSCAN0RMDF138HH RSCAN0.RMDF138.UINT8[HH]
#define RSCAN0RMID39 RSCAN0.RMID39.UINT32
#define RSCAN0RMID39L RSCAN0.RMID39.UINT16[L]
#define RSCAN0RMID39LL RSCAN0.RMID39.UINT8[LL]
#define RSCAN0RMID39LH RSCAN0.RMID39.UINT8[LH]
#define RSCAN0RMID39H RSCAN0.RMID39.UINT16[H]
#define RSCAN0RMID39HL RSCAN0.RMID39.UINT8[HL]
#define RSCAN0RMID39HH RSCAN0.RMID39.UINT8[HH]
#define RSCAN0RMPTR39 RSCAN0.RMPTR39.UINT32
#define RSCAN0RMPTR39L RSCAN0.RMPTR39.UINT16[L]
#define RSCAN0RMPTR39LL RSCAN0.RMPTR39.UINT8[LL]
#define RSCAN0RMPTR39LH RSCAN0.RMPTR39.UINT8[LH]
#define RSCAN0RMPTR39H RSCAN0.RMPTR39.UINT16[H]
#define RSCAN0RMPTR39HL RSCAN0.RMPTR39.UINT8[HL]
#define RSCAN0RMPTR39HH RSCAN0.RMPTR39.UINT8[HH]
#define RSCAN0RMDF039 RSCAN0.RMDF039.UINT32
#define RSCAN0RMDF039L RSCAN0.RMDF039.UINT16[L]
#define RSCAN0RMDF039LL RSCAN0.RMDF039.UINT8[LL]
#define RSCAN0RMDF039LH RSCAN0.RMDF039.UINT8[LH]
#define RSCAN0RMDF039H RSCAN0.RMDF039.UINT16[H]
#define RSCAN0RMDF039HL RSCAN0.RMDF039.UINT8[HL]
#define RSCAN0RMDF039HH RSCAN0.RMDF039.UINT8[HH]
#define RSCAN0RMDF139 RSCAN0.RMDF139.UINT32
#define RSCAN0RMDF139L RSCAN0.RMDF139.UINT16[L]
#define RSCAN0RMDF139LL RSCAN0.RMDF139.UINT8[LL]
#define RSCAN0RMDF139LH RSCAN0.RMDF139.UINT8[LH]
#define RSCAN0RMDF139H RSCAN0.RMDF139.UINT16[H]
#define RSCAN0RMDF139HL RSCAN0.RMDF139.UINT8[HL]
#define RSCAN0RMDF139HH RSCAN0.RMDF139.UINT8[HH]
#define RSCAN0RMID40 RSCAN0.RMID40.UINT32
#define RSCAN0RMID40L RSCAN0.RMID40.UINT16[L]
#define RSCAN0RMID40LL RSCAN0.RMID40.UINT8[LL]
#define RSCAN0RMID40LH RSCAN0.RMID40.UINT8[LH]
#define RSCAN0RMID40H RSCAN0.RMID40.UINT16[H]
#define RSCAN0RMID40HL RSCAN0.RMID40.UINT8[HL]
#define RSCAN0RMID40HH RSCAN0.RMID40.UINT8[HH]
#define RSCAN0RMPTR40 RSCAN0.RMPTR40.UINT32
#define RSCAN0RMPTR40L RSCAN0.RMPTR40.UINT16[L]
#define RSCAN0RMPTR40LL RSCAN0.RMPTR40.UINT8[LL]
#define RSCAN0RMPTR40LH RSCAN0.RMPTR40.UINT8[LH]
#define RSCAN0RMPTR40H RSCAN0.RMPTR40.UINT16[H]
#define RSCAN0RMPTR40HL RSCAN0.RMPTR40.UINT8[HL]
#define RSCAN0RMPTR40HH RSCAN0.RMPTR40.UINT8[HH]
#define RSCAN0RMDF040 RSCAN0.RMDF040.UINT32
#define RSCAN0RMDF040L RSCAN0.RMDF040.UINT16[L]
#define RSCAN0RMDF040LL RSCAN0.RMDF040.UINT8[LL]
#define RSCAN0RMDF040LH RSCAN0.RMDF040.UINT8[LH]
#define RSCAN0RMDF040H RSCAN0.RMDF040.UINT16[H]
#define RSCAN0RMDF040HL RSCAN0.RMDF040.UINT8[HL]
#define RSCAN0RMDF040HH RSCAN0.RMDF040.UINT8[HH]
#define RSCAN0RMDF140 RSCAN0.RMDF140.UINT32
#define RSCAN0RMDF140L RSCAN0.RMDF140.UINT16[L]
#define RSCAN0RMDF140LL RSCAN0.RMDF140.UINT8[LL]
#define RSCAN0RMDF140LH RSCAN0.RMDF140.UINT8[LH]
#define RSCAN0RMDF140H RSCAN0.RMDF140.UINT16[H]
#define RSCAN0RMDF140HL RSCAN0.RMDF140.UINT8[HL]
#define RSCAN0RMDF140HH RSCAN0.RMDF140.UINT8[HH]
#define RSCAN0RMID41 RSCAN0.RMID41.UINT32
#define RSCAN0RMID41L RSCAN0.RMID41.UINT16[L]
#define RSCAN0RMID41LL RSCAN0.RMID41.UINT8[LL]
#define RSCAN0RMID41LH RSCAN0.RMID41.UINT8[LH]
#define RSCAN0RMID41H RSCAN0.RMID41.UINT16[H]
#define RSCAN0RMID41HL RSCAN0.RMID41.UINT8[HL]
#define RSCAN0RMID41HH RSCAN0.RMID41.UINT8[HH]
#define RSCAN0RMPTR41 RSCAN0.RMPTR41.UINT32
#define RSCAN0RMPTR41L RSCAN0.RMPTR41.UINT16[L]
#define RSCAN0RMPTR41LL RSCAN0.RMPTR41.UINT8[LL]
#define RSCAN0RMPTR41LH RSCAN0.RMPTR41.UINT8[LH]
#define RSCAN0RMPTR41H RSCAN0.RMPTR41.UINT16[H]
#define RSCAN0RMPTR41HL RSCAN0.RMPTR41.UINT8[HL]
#define RSCAN0RMPTR41HH RSCAN0.RMPTR41.UINT8[HH]
#define RSCAN0RMDF041 RSCAN0.RMDF041.UINT32
#define RSCAN0RMDF041L RSCAN0.RMDF041.UINT16[L]
#define RSCAN0RMDF041LL RSCAN0.RMDF041.UINT8[LL]
#define RSCAN0RMDF041LH RSCAN0.RMDF041.UINT8[LH]
#define RSCAN0RMDF041H RSCAN0.RMDF041.UINT16[H]
#define RSCAN0RMDF041HL RSCAN0.RMDF041.UINT8[HL]
#define RSCAN0RMDF041HH RSCAN0.RMDF041.UINT8[HH]
#define RSCAN0RMDF141 RSCAN0.RMDF141.UINT32
#define RSCAN0RMDF141L RSCAN0.RMDF141.UINT16[L]
#define RSCAN0RMDF141LL RSCAN0.RMDF141.UINT8[LL]
#define RSCAN0RMDF141LH RSCAN0.RMDF141.UINT8[LH]
#define RSCAN0RMDF141H RSCAN0.RMDF141.UINT16[H]
#define RSCAN0RMDF141HL RSCAN0.RMDF141.UINT8[HL]
#define RSCAN0RMDF141HH RSCAN0.RMDF141.UINT8[HH]
#define RSCAN0RMID42 RSCAN0.RMID42.UINT32
#define RSCAN0RMID42L RSCAN0.RMID42.UINT16[L]
#define RSCAN0RMID42LL RSCAN0.RMID42.UINT8[LL]
#define RSCAN0RMID42LH RSCAN0.RMID42.UINT8[LH]
#define RSCAN0RMID42H RSCAN0.RMID42.UINT16[H]
#define RSCAN0RMID42HL RSCAN0.RMID42.UINT8[HL]
#define RSCAN0RMID42HH RSCAN0.RMID42.UINT8[HH]
#define RSCAN0RMPTR42 RSCAN0.RMPTR42.UINT32
#define RSCAN0RMPTR42L RSCAN0.RMPTR42.UINT16[L]
#define RSCAN0RMPTR42LL RSCAN0.RMPTR42.UINT8[LL]
#define RSCAN0RMPTR42LH RSCAN0.RMPTR42.UINT8[LH]
#define RSCAN0RMPTR42H RSCAN0.RMPTR42.UINT16[H]
#define RSCAN0RMPTR42HL RSCAN0.RMPTR42.UINT8[HL]
#define RSCAN0RMPTR42HH RSCAN0.RMPTR42.UINT8[HH]
#define RSCAN0RMDF042 RSCAN0.RMDF042.UINT32
#define RSCAN0RMDF042L RSCAN0.RMDF042.UINT16[L]
#define RSCAN0RMDF042LL RSCAN0.RMDF042.UINT8[LL]
#define RSCAN0RMDF042LH RSCAN0.RMDF042.UINT8[LH]
#define RSCAN0RMDF042H RSCAN0.RMDF042.UINT16[H]
#define RSCAN0RMDF042HL RSCAN0.RMDF042.UINT8[HL]
#define RSCAN0RMDF042HH RSCAN0.RMDF042.UINT8[HH]
#define RSCAN0RMDF142 RSCAN0.RMDF142.UINT32
#define RSCAN0RMDF142L RSCAN0.RMDF142.UINT16[L]
#define RSCAN0RMDF142LL RSCAN0.RMDF142.UINT8[LL]
#define RSCAN0RMDF142LH RSCAN0.RMDF142.UINT8[LH]
#define RSCAN0RMDF142H RSCAN0.RMDF142.UINT16[H]
#define RSCAN0RMDF142HL RSCAN0.RMDF142.UINT8[HL]
#define RSCAN0RMDF142HH RSCAN0.RMDF142.UINT8[HH]
#define RSCAN0RMID43 RSCAN0.RMID43.UINT32
#define RSCAN0RMID43L RSCAN0.RMID43.UINT16[L]
#define RSCAN0RMID43LL RSCAN0.RMID43.UINT8[LL]
#define RSCAN0RMID43LH RSCAN0.RMID43.UINT8[LH]
#define RSCAN0RMID43H RSCAN0.RMID43.UINT16[H]
#define RSCAN0RMID43HL RSCAN0.RMID43.UINT8[HL]
#define RSCAN0RMID43HH RSCAN0.RMID43.UINT8[HH]
#define RSCAN0RMPTR43 RSCAN0.RMPTR43.UINT32
#define RSCAN0RMPTR43L RSCAN0.RMPTR43.UINT16[L]
#define RSCAN0RMPTR43LL RSCAN0.RMPTR43.UINT8[LL]
#define RSCAN0RMPTR43LH RSCAN0.RMPTR43.UINT8[LH]
#define RSCAN0RMPTR43H RSCAN0.RMPTR43.UINT16[H]
#define RSCAN0RMPTR43HL RSCAN0.RMPTR43.UINT8[HL]
#define RSCAN0RMPTR43HH RSCAN0.RMPTR43.UINT8[HH]
#define RSCAN0RMDF043 RSCAN0.RMDF043.UINT32
#define RSCAN0RMDF043L RSCAN0.RMDF043.UINT16[L]
#define RSCAN0RMDF043LL RSCAN0.RMDF043.UINT8[LL]
#define RSCAN0RMDF043LH RSCAN0.RMDF043.UINT8[LH]
#define RSCAN0RMDF043H RSCAN0.RMDF043.UINT16[H]
#define RSCAN0RMDF043HL RSCAN0.RMDF043.UINT8[HL]
#define RSCAN0RMDF043HH RSCAN0.RMDF043.UINT8[HH]
#define RSCAN0RMDF143 RSCAN0.RMDF143.UINT32
#define RSCAN0RMDF143L RSCAN0.RMDF143.UINT16[L]
#define RSCAN0RMDF143LL RSCAN0.RMDF143.UINT8[LL]
#define RSCAN0RMDF143LH RSCAN0.RMDF143.UINT8[LH]
#define RSCAN0RMDF143H RSCAN0.RMDF143.UINT16[H]
#define RSCAN0RMDF143HL RSCAN0.RMDF143.UINT8[HL]
#define RSCAN0RMDF143HH RSCAN0.RMDF143.UINT8[HH]
#define RSCAN0RMID44 RSCAN0.RMID44.UINT32
#define RSCAN0RMID44L RSCAN0.RMID44.UINT16[L]
#define RSCAN0RMID44LL RSCAN0.RMID44.UINT8[LL]
#define RSCAN0RMID44LH RSCAN0.RMID44.UINT8[LH]
#define RSCAN0RMID44H RSCAN0.RMID44.UINT16[H]
#define RSCAN0RMID44HL RSCAN0.RMID44.UINT8[HL]
#define RSCAN0RMID44HH RSCAN0.RMID44.UINT8[HH]
#define RSCAN0RMPTR44 RSCAN0.RMPTR44.UINT32
#define RSCAN0RMPTR44L RSCAN0.RMPTR44.UINT16[L]
#define RSCAN0RMPTR44LL RSCAN0.RMPTR44.UINT8[LL]
#define RSCAN0RMPTR44LH RSCAN0.RMPTR44.UINT8[LH]
#define RSCAN0RMPTR44H RSCAN0.RMPTR44.UINT16[H]
#define RSCAN0RMPTR44HL RSCAN0.RMPTR44.UINT8[HL]
#define RSCAN0RMPTR44HH RSCAN0.RMPTR44.UINT8[HH]
#define RSCAN0RMDF044 RSCAN0.RMDF044.UINT32
#define RSCAN0RMDF044L RSCAN0.RMDF044.UINT16[L]
#define RSCAN0RMDF044LL RSCAN0.RMDF044.UINT8[LL]
#define RSCAN0RMDF044LH RSCAN0.RMDF044.UINT8[LH]
#define RSCAN0RMDF044H RSCAN0.RMDF044.UINT16[H]
#define RSCAN0RMDF044HL RSCAN0.RMDF044.UINT8[HL]
#define RSCAN0RMDF044HH RSCAN0.RMDF044.UINT8[HH]
#define RSCAN0RMDF144 RSCAN0.RMDF144.UINT32
#define RSCAN0RMDF144L RSCAN0.RMDF144.UINT16[L]
#define RSCAN0RMDF144LL RSCAN0.RMDF144.UINT8[LL]
#define RSCAN0RMDF144LH RSCAN0.RMDF144.UINT8[LH]
#define RSCAN0RMDF144H RSCAN0.RMDF144.UINT16[H]
#define RSCAN0RMDF144HL RSCAN0.RMDF144.UINT8[HL]
#define RSCAN0RMDF144HH RSCAN0.RMDF144.UINT8[HH]
#define RSCAN0RMID45 RSCAN0.RMID45.UINT32
#define RSCAN0RMID45L RSCAN0.RMID45.UINT16[L]
#define RSCAN0RMID45LL RSCAN0.RMID45.UINT8[LL]
#define RSCAN0RMID45LH RSCAN0.RMID45.UINT8[LH]
#define RSCAN0RMID45H RSCAN0.RMID45.UINT16[H]
#define RSCAN0RMID45HL RSCAN0.RMID45.UINT8[HL]
#define RSCAN0RMID45HH RSCAN0.RMID45.UINT8[HH]
#define RSCAN0RMPTR45 RSCAN0.RMPTR45.UINT32
#define RSCAN0RMPTR45L RSCAN0.RMPTR45.UINT16[L]
#define RSCAN0RMPTR45LL RSCAN0.RMPTR45.UINT8[LL]
#define RSCAN0RMPTR45LH RSCAN0.RMPTR45.UINT8[LH]
#define RSCAN0RMPTR45H RSCAN0.RMPTR45.UINT16[H]
#define RSCAN0RMPTR45HL RSCAN0.RMPTR45.UINT8[HL]
#define RSCAN0RMPTR45HH RSCAN0.RMPTR45.UINT8[HH]
#define RSCAN0RMDF045 RSCAN0.RMDF045.UINT32
#define RSCAN0RMDF045L RSCAN0.RMDF045.UINT16[L]
#define RSCAN0RMDF045LL RSCAN0.RMDF045.UINT8[LL]
#define RSCAN0RMDF045LH RSCAN0.RMDF045.UINT8[LH]
#define RSCAN0RMDF045H RSCAN0.RMDF045.UINT16[H]
#define RSCAN0RMDF045HL RSCAN0.RMDF045.UINT8[HL]
#define RSCAN0RMDF045HH RSCAN0.RMDF045.UINT8[HH]
#define RSCAN0RMDF145 RSCAN0.RMDF145.UINT32
#define RSCAN0RMDF145L RSCAN0.RMDF145.UINT16[L]
#define RSCAN0RMDF145LL RSCAN0.RMDF145.UINT8[LL]
#define RSCAN0RMDF145LH RSCAN0.RMDF145.UINT8[LH]
#define RSCAN0RMDF145H RSCAN0.RMDF145.UINT16[H]
#define RSCAN0RMDF145HL RSCAN0.RMDF145.UINT8[HL]
#define RSCAN0RMDF145HH RSCAN0.RMDF145.UINT8[HH]
#define RSCAN0RMID46 RSCAN0.RMID46.UINT32
#define RSCAN0RMID46L RSCAN0.RMID46.UINT16[L]
#define RSCAN0RMID46LL RSCAN0.RMID46.UINT8[LL]
#define RSCAN0RMID46LH RSCAN0.RMID46.UINT8[LH]
#define RSCAN0RMID46H RSCAN0.RMID46.UINT16[H]
#define RSCAN0RMID46HL RSCAN0.RMID46.UINT8[HL]
#define RSCAN0RMID46HH RSCAN0.RMID46.UINT8[HH]
#define RSCAN0RMPTR46 RSCAN0.RMPTR46.UINT32
#define RSCAN0RMPTR46L RSCAN0.RMPTR46.UINT16[L]
#define RSCAN0RMPTR46LL RSCAN0.RMPTR46.UINT8[LL]
#define RSCAN0RMPTR46LH RSCAN0.RMPTR46.UINT8[LH]
#define RSCAN0RMPTR46H RSCAN0.RMPTR46.UINT16[H]
#define RSCAN0RMPTR46HL RSCAN0.RMPTR46.UINT8[HL]
#define RSCAN0RMPTR46HH RSCAN0.RMPTR46.UINT8[HH]
#define RSCAN0RMDF046 RSCAN0.RMDF046.UINT32
#define RSCAN0RMDF046L RSCAN0.RMDF046.UINT16[L]
#define RSCAN0RMDF046LL RSCAN0.RMDF046.UINT8[LL]
#define RSCAN0RMDF046LH RSCAN0.RMDF046.UINT8[LH]
#define RSCAN0RMDF046H RSCAN0.RMDF046.UINT16[H]
#define RSCAN0RMDF046HL RSCAN0.RMDF046.UINT8[HL]
#define RSCAN0RMDF046HH RSCAN0.RMDF046.UINT8[HH]
#define RSCAN0RMDF146 RSCAN0.RMDF146.UINT32
#define RSCAN0RMDF146L RSCAN0.RMDF146.UINT16[L]
#define RSCAN0RMDF146LL RSCAN0.RMDF146.UINT8[LL]
#define RSCAN0RMDF146LH RSCAN0.RMDF146.UINT8[LH]
#define RSCAN0RMDF146H RSCAN0.RMDF146.UINT16[H]
#define RSCAN0RMDF146HL RSCAN0.RMDF146.UINT8[HL]
#define RSCAN0RMDF146HH RSCAN0.RMDF146.UINT8[HH]
#define RSCAN0RMID47 RSCAN0.RMID47.UINT32
#define RSCAN0RMID47L RSCAN0.RMID47.UINT16[L]
#define RSCAN0RMID47LL RSCAN0.RMID47.UINT8[LL]
#define RSCAN0RMID47LH RSCAN0.RMID47.UINT8[LH]
#define RSCAN0RMID47H RSCAN0.RMID47.UINT16[H]
#define RSCAN0RMID47HL RSCAN0.RMID47.UINT8[HL]
#define RSCAN0RMID47HH RSCAN0.RMID47.UINT8[HH]
#define RSCAN0RMPTR47 RSCAN0.RMPTR47.UINT32
#define RSCAN0RMPTR47L RSCAN0.RMPTR47.UINT16[L]
#define RSCAN0RMPTR47LL RSCAN0.RMPTR47.UINT8[LL]
#define RSCAN0RMPTR47LH RSCAN0.RMPTR47.UINT8[LH]
#define RSCAN0RMPTR47H RSCAN0.RMPTR47.UINT16[H]
#define RSCAN0RMPTR47HL RSCAN0.RMPTR47.UINT8[HL]
#define RSCAN0RMPTR47HH RSCAN0.RMPTR47.UINT8[HH]
#define RSCAN0RMDF047 RSCAN0.RMDF047.UINT32
#define RSCAN0RMDF047L RSCAN0.RMDF047.UINT16[L]
#define RSCAN0RMDF047LL RSCAN0.RMDF047.UINT8[LL]
#define RSCAN0RMDF047LH RSCAN0.RMDF047.UINT8[LH]
#define RSCAN0RMDF047H RSCAN0.RMDF047.UINT16[H]
#define RSCAN0RMDF047HL RSCAN0.RMDF047.UINT8[HL]
#define RSCAN0RMDF047HH RSCAN0.RMDF047.UINT8[HH]
#define RSCAN0RMDF147 RSCAN0.RMDF147.UINT32
#define RSCAN0RMDF147L RSCAN0.RMDF147.UINT16[L]
#define RSCAN0RMDF147LL RSCAN0.RMDF147.UINT8[LL]
#define RSCAN0RMDF147LH RSCAN0.RMDF147.UINT8[LH]
#define RSCAN0RMDF147H RSCAN0.RMDF147.UINT16[H]
#define RSCAN0RMDF147HL RSCAN0.RMDF147.UINT8[HL]
#define RSCAN0RMDF147HH RSCAN0.RMDF147.UINT8[HH]
#define RSCAN0RMID48 RSCAN0.RMID48.UINT32
#define RSCAN0RMID48L RSCAN0.RMID48.UINT16[L]
#define RSCAN0RMID48LL RSCAN0.RMID48.UINT8[LL]
#define RSCAN0RMID48LH RSCAN0.RMID48.UINT8[LH]
#define RSCAN0RMID48H RSCAN0.RMID48.UINT16[H]
#define RSCAN0RMID48HL RSCAN0.RMID48.UINT8[HL]
#define RSCAN0RMID48HH RSCAN0.RMID48.UINT8[HH]
#define RSCAN0RMPTR48 RSCAN0.RMPTR48.UINT32
#define RSCAN0RMPTR48L RSCAN0.RMPTR48.UINT16[L]
#define RSCAN0RMPTR48LL RSCAN0.RMPTR48.UINT8[LL]
#define RSCAN0RMPTR48LH RSCAN0.RMPTR48.UINT8[LH]
#define RSCAN0RMPTR48H RSCAN0.RMPTR48.UINT16[H]
#define RSCAN0RMPTR48HL RSCAN0.RMPTR48.UINT8[HL]
#define RSCAN0RMPTR48HH RSCAN0.RMPTR48.UINT8[HH]
#define RSCAN0RMDF048 RSCAN0.RMDF048.UINT32
#define RSCAN0RMDF048L RSCAN0.RMDF048.UINT16[L]
#define RSCAN0RMDF048LL RSCAN0.RMDF048.UINT8[LL]
#define RSCAN0RMDF048LH RSCAN0.RMDF048.UINT8[LH]
#define RSCAN0RMDF048H RSCAN0.RMDF048.UINT16[H]
#define RSCAN0RMDF048HL RSCAN0.RMDF048.UINT8[HL]
#define RSCAN0RMDF048HH RSCAN0.RMDF048.UINT8[HH]
#define RSCAN0RMDF148 RSCAN0.RMDF148.UINT32
#define RSCAN0RMDF148L RSCAN0.RMDF148.UINT16[L]
#define RSCAN0RMDF148LL RSCAN0.RMDF148.UINT8[LL]
#define RSCAN0RMDF148LH RSCAN0.RMDF148.UINT8[LH]
#define RSCAN0RMDF148H RSCAN0.RMDF148.UINT16[H]
#define RSCAN0RMDF148HL RSCAN0.RMDF148.UINT8[HL]
#define RSCAN0RMDF148HH RSCAN0.RMDF148.UINT8[HH]
#define RSCAN0RMID49 RSCAN0.RMID49.UINT32
#define RSCAN0RMID49L RSCAN0.RMID49.UINT16[L]
#define RSCAN0RMID49LL RSCAN0.RMID49.UINT8[LL]
#define RSCAN0RMID49LH RSCAN0.RMID49.UINT8[LH]
#define RSCAN0RMID49H RSCAN0.RMID49.UINT16[H]
#define RSCAN0RMID49HL RSCAN0.RMID49.UINT8[HL]
#define RSCAN0RMID49HH RSCAN0.RMID49.UINT8[HH]
#define RSCAN0RMPTR49 RSCAN0.RMPTR49.UINT32
#define RSCAN0RMPTR49L RSCAN0.RMPTR49.UINT16[L]
#define RSCAN0RMPTR49LL RSCAN0.RMPTR49.UINT8[LL]
#define RSCAN0RMPTR49LH RSCAN0.RMPTR49.UINT8[LH]
#define RSCAN0RMPTR49H RSCAN0.RMPTR49.UINT16[H]
#define RSCAN0RMPTR49HL RSCAN0.RMPTR49.UINT8[HL]
#define RSCAN0RMPTR49HH RSCAN0.RMPTR49.UINT8[HH]
#define RSCAN0RMDF049 RSCAN0.RMDF049.UINT32
#define RSCAN0RMDF049L RSCAN0.RMDF049.UINT16[L]
#define RSCAN0RMDF049LL RSCAN0.RMDF049.UINT8[LL]
#define RSCAN0RMDF049LH RSCAN0.RMDF049.UINT8[LH]
#define RSCAN0RMDF049H RSCAN0.RMDF049.UINT16[H]
#define RSCAN0RMDF049HL RSCAN0.RMDF049.UINT8[HL]
#define RSCAN0RMDF049HH RSCAN0.RMDF049.UINT8[HH]
#define RSCAN0RMDF149 RSCAN0.RMDF149.UINT32
#define RSCAN0RMDF149L RSCAN0.RMDF149.UINT16[L]
#define RSCAN0RMDF149LL RSCAN0.RMDF149.UINT8[LL]
#define RSCAN0RMDF149LH RSCAN0.RMDF149.UINT8[LH]
#define RSCAN0RMDF149H RSCAN0.RMDF149.UINT16[H]
#define RSCAN0RMDF149HL RSCAN0.RMDF149.UINT8[HL]
#define RSCAN0RMDF149HH RSCAN0.RMDF149.UINT8[HH]
#define RSCAN0RMID50 RSCAN0.RMID50.UINT32
#define RSCAN0RMID50L RSCAN0.RMID50.UINT16[L]
#define RSCAN0RMID50LL RSCAN0.RMID50.UINT8[LL]
#define RSCAN0RMID50LH RSCAN0.RMID50.UINT8[LH]
#define RSCAN0RMID50H RSCAN0.RMID50.UINT16[H]
#define RSCAN0RMID50HL RSCAN0.RMID50.UINT8[HL]
#define RSCAN0RMID50HH RSCAN0.RMID50.UINT8[HH]
#define RSCAN0RMPTR50 RSCAN0.RMPTR50.UINT32
#define RSCAN0RMPTR50L RSCAN0.RMPTR50.UINT16[L]
#define RSCAN0RMPTR50LL RSCAN0.RMPTR50.UINT8[LL]
#define RSCAN0RMPTR50LH RSCAN0.RMPTR50.UINT8[LH]
#define RSCAN0RMPTR50H RSCAN0.RMPTR50.UINT16[H]
#define RSCAN0RMPTR50HL RSCAN0.RMPTR50.UINT8[HL]
#define RSCAN0RMPTR50HH RSCAN0.RMPTR50.UINT8[HH]
#define RSCAN0RMDF050 RSCAN0.RMDF050.UINT32
#define RSCAN0RMDF050L RSCAN0.RMDF050.UINT16[L]
#define RSCAN0RMDF050LL RSCAN0.RMDF050.UINT8[LL]
#define RSCAN0RMDF050LH RSCAN0.RMDF050.UINT8[LH]
#define RSCAN0RMDF050H RSCAN0.RMDF050.UINT16[H]
#define RSCAN0RMDF050HL RSCAN0.RMDF050.UINT8[HL]
#define RSCAN0RMDF050HH RSCAN0.RMDF050.UINT8[HH]
#define RSCAN0RMDF150 RSCAN0.RMDF150.UINT32
#define RSCAN0RMDF150L RSCAN0.RMDF150.UINT16[L]
#define RSCAN0RMDF150LL RSCAN0.RMDF150.UINT8[LL]
#define RSCAN0RMDF150LH RSCAN0.RMDF150.UINT8[LH]
#define RSCAN0RMDF150H RSCAN0.RMDF150.UINT16[H]
#define RSCAN0RMDF150HL RSCAN0.RMDF150.UINT8[HL]
#define RSCAN0RMDF150HH RSCAN0.RMDF150.UINT8[HH]
#define RSCAN0RMID51 RSCAN0.RMID51.UINT32
#define RSCAN0RMID51L RSCAN0.RMID51.UINT16[L]
#define RSCAN0RMID51LL RSCAN0.RMID51.UINT8[LL]
#define RSCAN0RMID51LH RSCAN0.RMID51.UINT8[LH]
#define RSCAN0RMID51H RSCAN0.RMID51.UINT16[H]
#define RSCAN0RMID51HL RSCAN0.RMID51.UINT8[HL]
#define RSCAN0RMID51HH RSCAN0.RMID51.UINT8[HH]
#define RSCAN0RMPTR51 RSCAN0.RMPTR51.UINT32
#define RSCAN0RMPTR51L RSCAN0.RMPTR51.UINT16[L]
#define RSCAN0RMPTR51LL RSCAN0.RMPTR51.UINT8[LL]
#define RSCAN0RMPTR51LH RSCAN0.RMPTR51.UINT8[LH]
#define RSCAN0RMPTR51H RSCAN0.RMPTR51.UINT16[H]
#define RSCAN0RMPTR51HL RSCAN0.RMPTR51.UINT8[HL]
#define RSCAN0RMPTR51HH RSCAN0.RMPTR51.UINT8[HH]
#define RSCAN0RMDF051 RSCAN0.RMDF051.UINT32
#define RSCAN0RMDF051L RSCAN0.RMDF051.UINT16[L]
#define RSCAN0RMDF051LL RSCAN0.RMDF051.UINT8[LL]
#define RSCAN0RMDF051LH RSCAN0.RMDF051.UINT8[LH]
#define RSCAN0RMDF051H RSCAN0.RMDF051.UINT16[H]
#define RSCAN0RMDF051HL RSCAN0.RMDF051.UINT8[HL]
#define RSCAN0RMDF051HH RSCAN0.RMDF051.UINT8[HH]
#define RSCAN0RMDF151 RSCAN0.RMDF151.UINT32
#define RSCAN0RMDF151L RSCAN0.RMDF151.UINT16[L]
#define RSCAN0RMDF151LL RSCAN0.RMDF151.UINT8[LL]
#define RSCAN0RMDF151LH RSCAN0.RMDF151.UINT8[LH]
#define RSCAN0RMDF151H RSCAN0.RMDF151.UINT16[H]
#define RSCAN0RMDF151HL RSCAN0.RMDF151.UINT8[HL]
#define RSCAN0RMDF151HH RSCAN0.RMDF151.UINT8[HH]
#define RSCAN0RMID52 RSCAN0.RMID52.UINT32
#define RSCAN0RMID52L RSCAN0.RMID52.UINT16[L]
#define RSCAN0RMID52LL RSCAN0.RMID52.UINT8[LL]
#define RSCAN0RMID52LH RSCAN0.RMID52.UINT8[LH]
#define RSCAN0RMID52H RSCAN0.RMID52.UINT16[H]
#define RSCAN0RMID52HL RSCAN0.RMID52.UINT8[HL]
#define RSCAN0RMID52HH RSCAN0.RMID52.UINT8[HH]
#define RSCAN0RMPTR52 RSCAN0.RMPTR52.UINT32
#define RSCAN0RMPTR52L RSCAN0.RMPTR52.UINT16[L]
#define RSCAN0RMPTR52LL RSCAN0.RMPTR52.UINT8[LL]
#define RSCAN0RMPTR52LH RSCAN0.RMPTR52.UINT8[LH]
#define RSCAN0RMPTR52H RSCAN0.RMPTR52.UINT16[H]
#define RSCAN0RMPTR52HL RSCAN0.RMPTR52.UINT8[HL]
#define RSCAN0RMPTR52HH RSCAN0.RMPTR52.UINT8[HH]
#define RSCAN0RMDF052 RSCAN0.RMDF052.UINT32
#define RSCAN0RMDF052L RSCAN0.RMDF052.UINT16[L]
#define RSCAN0RMDF052LL RSCAN0.RMDF052.UINT8[LL]
#define RSCAN0RMDF052LH RSCAN0.RMDF052.UINT8[LH]
#define RSCAN0RMDF052H RSCAN0.RMDF052.UINT16[H]
#define RSCAN0RMDF052HL RSCAN0.RMDF052.UINT8[HL]
#define RSCAN0RMDF052HH RSCAN0.RMDF052.UINT8[HH]
#define RSCAN0RMDF152 RSCAN0.RMDF152.UINT32
#define RSCAN0RMDF152L RSCAN0.RMDF152.UINT16[L]
#define RSCAN0RMDF152LL RSCAN0.RMDF152.UINT8[LL]
#define RSCAN0RMDF152LH RSCAN0.RMDF152.UINT8[LH]
#define RSCAN0RMDF152H RSCAN0.RMDF152.UINT16[H]
#define RSCAN0RMDF152HL RSCAN0.RMDF152.UINT8[HL]
#define RSCAN0RMDF152HH RSCAN0.RMDF152.UINT8[HH]
#define RSCAN0RMID53 RSCAN0.RMID53.UINT32
#define RSCAN0RMID53L RSCAN0.RMID53.UINT16[L]
#define RSCAN0RMID53LL RSCAN0.RMID53.UINT8[LL]
#define RSCAN0RMID53LH RSCAN0.RMID53.UINT8[LH]
#define RSCAN0RMID53H RSCAN0.RMID53.UINT16[H]
#define RSCAN0RMID53HL RSCAN0.RMID53.UINT8[HL]
#define RSCAN0RMID53HH RSCAN0.RMID53.UINT8[HH]
#define RSCAN0RMPTR53 RSCAN0.RMPTR53.UINT32
#define RSCAN0RMPTR53L RSCAN0.RMPTR53.UINT16[L]
#define RSCAN0RMPTR53LL RSCAN0.RMPTR53.UINT8[LL]
#define RSCAN0RMPTR53LH RSCAN0.RMPTR53.UINT8[LH]
#define RSCAN0RMPTR53H RSCAN0.RMPTR53.UINT16[H]
#define RSCAN0RMPTR53HL RSCAN0.RMPTR53.UINT8[HL]
#define RSCAN0RMPTR53HH RSCAN0.RMPTR53.UINT8[HH]
#define RSCAN0RMDF053 RSCAN0.RMDF053.UINT32
#define RSCAN0RMDF053L RSCAN0.RMDF053.UINT16[L]
#define RSCAN0RMDF053LL RSCAN0.RMDF053.UINT8[LL]
#define RSCAN0RMDF053LH RSCAN0.RMDF053.UINT8[LH]
#define RSCAN0RMDF053H RSCAN0.RMDF053.UINT16[H]
#define RSCAN0RMDF053HL RSCAN0.RMDF053.UINT8[HL]
#define RSCAN0RMDF053HH RSCAN0.RMDF053.UINT8[HH]
#define RSCAN0RMDF153 RSCAN0.RMDF153.UINT32
#define RSCAN0RMDF153L RSCAN0.RMDF153.UINT16[L]
#define RSCAN0RMDF153LL RSCAN0.RMDF153.UINT8[LL]
#define RSCAN0RMDF153LH RSCAN0.RMDF153.UINT8[LH]
#define RSCAN0RMDF153H RSCAN0.RMDF153.UINT16[H]
#define RSCAN0RMDF153HL RSCAN0.RMDF153.UINT8[HL]
#define RSCAN0RMDF153HH RSCAN0.RMDF153.UINT8[HH]
#define RSCAN0RMID54 RSCAN0.RMID54.UINT32
#define RSCAN0RMID54L RSCAN0.RMID54.UINT16[L]
#define RSCAN0RMID54LL RSCAN0.RMID54.UINT8[LL]
#define RSCAN0RMID54LH RSCAN0.RMID54.UINT8[LH]
#define RSCAN0RMID54H RSCAN0.RMID54.UINT16[H]
#define RSCAN0RMID54HL RSCAN0.RMID54.UINT8[HL]
#define RSCAN0RMID54HH RSCAN0.RMID54.UINT8[HH]
#define RSCAN0RMPTR54 RSCAN0.RMPTR54.UINT32
#define RSCAN0RMPTR54L RSCAN0.RMPTR54.UINT16[L]
#define RSCAN0RMPTR54LL RSCAN0.RMPTR54.UINT8[LL]
#define RSCAN0RMPTR54LH RSCAN0.RMPTR54.UINT8[LH]
#define RSCAN0RMPTR54H RSCAN0.RMPTR54.UINT16[H]
#define RSCAN0RMPTR54HL RSCAN0.RMPTR54.UINT8[HL]
#define RSCAN0RMPTR54HH RSCAN0.RMPTR54.UINT8[HH]
#define RSCAN0RMDF054 RSCAN0.RMDF054.UINT32
#define RSCAN0RMDF054L RSCAN0.RMDF054.UINT16[L]
#define RSCAN0RMDF054LL RSCAN0.RMDF054.UINT8[LL]
#define RSCAN0RMDF054LH RSCAN0.RMDF054.UINT8[LH]
#define RSCAN0RMDF054H RSCAN0.RMDF054.UINT16[H]
#define RSCAN0RMDF054HL RSCAN0.RMDF054.UINT8[HL]
#define RSCAN0RMDF054HH RSCAN0.RMDF054.UINT8[HH]
#define RSCAN0RMDF154 RSCAN0.RMDF154.UINT32
#define RSCAN0RMDF154L RSCAN0.RMDF154.UINT16[L]
#define RSCAN0RMDF154LL RSCAN0.RMDF154.UINT8[LL]
#define RSCAN0RMDF154LH RSCAN0.RMDF154.UINT8[LH]
#define RSCAN0RMDF154H RSCAN0.RMDF154.UINT16[H]
#define RSCAN0RMDF154HL RSCAN0.RMDF154.UINT8[HL]
#define RSCAN0RMDF154HH RSCAN0.RMDF154.UINT8[HH]
#define RSCAN0RMID55 RSCAN0.RMID55.UINT32
#define RSCAN0RMID55L RSCAN0.RMID55.UINT16[L]
#define RSCAN0RMID55LL RSCAN0.RMID55.UINT8[LL]
#define RSCAN0RMID55LH RSCAN0.RMID55.UINT8[LH]
#define RSCAN0RMID55H RSCAN0.RMID55.UINT16[H]
#define RSCAN0RMID55HL RSCAN0.RMID55.UINT8[HL]
#define RSCAN0RMID55HH RSCAN0.RMID55.UINT8[HH]
#define RSCAN0RMPTR55 RSCAN0.RMPTR55.UINT32
#define RSCAN0RMPTR55L RSCAN0.RMPTR55.UINT16[L]
#define RSCAN0RMPTR55LL RSCAN0.RMPTR55.UINT8[LL]
#define RSCAN0RMPTR55LH RSCAN0.RMPTR55.UINT8[LH]
#define RSCAN0RMPTR55H RSCAN0.RMPTR55.UINT16[H]
#define RSCAN0RMPTR55HL RSCAN0.RMPTR55.UINT8[HL]
#define RSCAN0RMPTR55HH RSCAN0.RMPTR55.UINT8[HH]
#define RSCAN0RMDF055 RSCAN0.RMDF055.UINT32
#define RSCAN0RMDF055L RSCAN0.RMDF055.UINT16[L]
#define RSCAN0RMDF055LL RSCAN0.RMDF055.UINT8[LL]
#define RSCAN0RMDF055LH RSCAN0.RMDF055.UINT8[LH]
#define RSCAN0RMDF055H RSCAN0.RMDF055.UINT16[H]
#define RSCAN0RMDF055HL RSCAN0.RMDF055.UINT8[HL]
#define RSCAN0RMDF055HH RSCAN0.RMDF055.UINT8[HH]
#define RSCAN0RMDF155 RSCAN0.RMDF155.UINT32
#define RSCAN0RMDF155L RSCAN0.RMDF155.UINT16[L]
#define RSCAN0RMDF155LL RSCAN0.RMDF155.UINT8[LL]
#define RSCAN0RMDF155LH RSCAN0.RMDF155.UINT8[LH]
#define RSCAN0RMDF155H RSCAN0.RMDF155.UINT16[H]
#define RSCAN0RMDF155HL RSCAN0.RMDF155.UINT8[HL]
#define RSCAN0RMDF155HH RSCAN0.RMDF155.UINT8[HH]
#define RSCAN0RMID56 RSCAN0.RMID56.UINT32
#define RSCAN0RMID56L RSCAN0.RMID56.UINT16[L]
#define RSCAN0RMID56LL RSCAN0.RMID56.UINT8[LL]
#define RSCAN0RMID56LH RSCAN0.RMID56.UINT8[LH]
#define RSCAN0RMID56H RSCAN0.RMID56.UINT16[H]
#define RSCAN0RMID56HL RSCAN0.RMID56.UINT8[HL]
#define RSCAN0RMID56HH RSCAN0.RMID56.UINT8[HH]
#define RSCAN0RMPTR56 RSCAN0.RMPTR56.UINT32
#define RSCAN0RMPTR56L RSCAN0.RMPTR56.UINT16[L]
#define RSCAN0RMPTR56LL RSCAN0.RMPTR56.UINT8[LL]
#define RSCAN0RMPTR56LH RSCAN0.RMPTR56.UINT8[LH]
#define RSCAN0RMPTR56H RSCAN0.RMPTR56.UINT16[H]
#define RSCAN0RMPTR56HL RSCAN0.RMPTR56.UINT8[HL]
#define RSCAN0RMPTR56HH RSCAN0.RMPTR56.UINT8[HH]
#define RSCAN0RMDF056 RSCAN0.RMDF056.UINT32
#define RSCAN0RMDF056L RSCAN0.RMDF056.UINT16[L]
#define RSCAN0RMDF056LL RSCAN0.RMDF056.UINT8[LL]
#define RSCAN0RMDF056LH RSCAN0.RMDF056.UINT8[LH]
#define RSCAN0RMDF056H RSCAN0.RMDF056.UINT16[H]
#define RSCAN0RMDF056HL RSCAN0.RMDF056.UINT8[HL]
#define RSCAN0RMDF056HH RSCAN0.RMDF056.UINT8[HH]
#define RSCAN0RMDF156 RSCAN0.RMDF156.UINT32
#define RSCAN0RMDF156L RSCAN0.RMDF156.UINT16[L]
#define RSCAN0RMDF156LL RSCAN0.RMDF156.UINT8[LL]
#define RSCAN0RMDF156LH RSCAN0.RMDF156.UINT8[LH]
#define RSCAN0RMDF156H RSCAN0.RMDF156.UINT16[H]
#define RSCAN0RMDF156HL RSCAN0.RMDF156.UINT8[HL]
#define RSCAN0RMDF156HH RSCAN0.RMDF156.UINT8[HH]
#define RSCAN0RMID57 RSCAN0.RMID57.UINT32
#define RSCAN0RMID57L RSCAN0.RMID57.UINT16[L]
#define RSCAN0RMID57LL RSCAN0.RMID57.UINT8[LL]
#define RSCAN0RMID57LH RSCAN0.RMID57.UINT8[LH]
#define RSCAN0RMID57H RSCAN0.RMID57.UINT16[H]
#define RSCAN0RMID57HL RSCAN0.RMID57.UINT8[HL]
#define RSCAN0RMID57HH RSCAN0.RMID57.UINT8[HH]
#define RSCAN0RMPTR57 RSCAN0.RMPTR57.UINT32
#define RSCAN0RMPTR57L RSCAN0.RMPTR57.UINT16[L]
#define RSCAN0RMPTR57LL RSCAN0.RMPTR57.UINT8[LL]
#define RSCAN0RMPTR57LH RSCAN0.RMPTR57.UINT8[LH]
#define RSCAN0RMPTR57H RSCAN0.RMPTR57.UINT16[H]
#define RSCAN0RMPTR57HL RSCAN0.RMPTR57.UINT8[HL]
#define RSCAN0RMPTR57HH RSCAN0.RMPTR57.UINT8[HH]
#define RSCAN0RMDF057 RSCAN0.RMDF057.UINT32
#define RSCAN0RMDF057L RSCAN0.RMDF057.UINT16[L]
#define RSCAN0RMDF057LL RSCAN0.RMDF057.UINT8[LL]
#define RSCAN0RMDF057LH RSCAN0.RMDF057.UINT8[LH]
#define RSCAN0RMDF057H RSCAN0.RMDF057.UINT16[H]
#define RSCAN0RMDF057HL RSCAN0.RMDF057.UINT8[HL]
#define RSCAN0RMDF057HH RSCAN0.RMDF057.UINT8[HH]
#define RSCAN0RMDF157 RSCAN0.RMDF157.UINT32
#define RSCAN0RMDF157L RSCAN0.RMDF157.UINT16[L]
#define RSCAN0RMDF157LL RSCAN0.RMDF157.UINT8[LL]
#define RSCAN0RMDF157LH RSCAN0.RMDF157.UINT8[LH]
#define RSCAN0RMDF157H RSCAN0.RMDF157.UINT16[H]
#define RSCAN0RMDF157HL RSCAN0.RMDF157.UINT8[HL]
#define RSCAN0RMDF157HH RSCAN0.RMDF157.UINT8[HH]
#define RSCAN0RMID58 RSCAN0.RMID58.UINT32
#define RSCAN0RMID58L RSCAN0.RMID58.UINT16[L]
#define RSCAN0RMID58LL RSCAN0.RMID58.UINT8[LL]
#define RSCAN0RMID58LH RSCAN0.RMID58.UINT8[LH]
#define RSCAN0RMID58H RSCAN0.RMID58.UINT16[H]
#define RSCAN0RMID58HL RSCAN0.RMID58.UINT8[HL]
#define RSCAN0RMID58HH RSCAN0.RMID58.UINT8[HH]
#define RSCAN0RMPTR58 RSCAN0.RMPTR58.UINT32
#define RSCAN0RMPTR58L RSCAN0.RMPTR58.UINT16[L]
#define RSCAN0RMPTR58LL RSCAN0.RMPTR58.UINT8[LL]
#define RSCAN0RMPTR58LH RSCAN0.RMPTR58.UINT8[LH]
#define RSCAN0RMPTR58H RSCAN0.RMPTR58.UINT16[H]
#define RSCAN0RMPTR58HL RSCAN0.RMPTR58.UINT8[HL]
#define RSCAN0RMPTR58HH RSCAN0.RMPTR58.UINT8[HH]
#define RSCAN0RMDF058 RSCAN0.RMDF058.UINT32
#define RSCAN0RMDF058L RSCAN0.RMDF058.UINT16[L]
#define RSCAN0RMDF058LL RSCAN0.RMDF058.UINT8[LL]
#define RSCAN0RMDF058LH RSCAN0.RMDF058.UINT8[LH]
#define RSCAN0RMDF058H RSCAN0.RMDF058.UINT16[H]
#define RSCAN0RMDF058HL RSCAN0.RMDF058.UINT8[HL]
#define RSCAN0RMDF058HH RSCAN0.RMDF058.UINT8[HH]
#define RSCAN0RMDF158 RSCAN0.RMDF158.UINT32
#define RSCAN0RMDF158L RSCAN0.RMDF158.UINT16[L]
#define RSCAN0RMDF158LL RSCAN0.RMDF158.UINT8[LL]
#define RSCAN0RMDF158LH RSCAN0.RMDF158.UINT8[LH]
#define RSCAN0RMDF158H RSCAN0.RMDF158.UINT16[H]
#define RSCAN0RMDF158HL RSCAN0.RMDF158.UINT8[HL]
#define RSCAN0RMDF158HH RSCAN0.RMDF158.UINT8[HH]
#define RSCAN0RMID59 RSCAN0.RMID59.UINT32
#define RSCAN0RMID59L RSCAN0.RMID59.UINT16[L]
#define RSCAN0RMID59LL RSCAN0.RMID59.UINT8[LL]
#define RSCAN0RMID59LH RSCAN0.RMID59.UINT8[LH]
#define RSCAN0RMID59H RSCAN0.RMID59.UINT16[H]
#define RSCAN0RMID59HL RSCAN0.RMID59.UINT8[HL]
#define RSCAN0RMID59HH RSCAN0.RMID59.UINT8[HH]
#define RSCAN0RMPTR59 RSCAN0.RMPTR59.UINT32
#define RSCAN0RMPTR59L RSCAN0.RMPTR59.UINT16[L]
#define RSCAN0RMPTR59LL RSCAN0.RMPTR59.UINT8[LL]
#define RSCAN0RMPTR59LH RSCAN0.RMPTR59.UINT8[LH]
#define RSCAN0RMPTR59H RSCAN0.RMPTR59.UINT16[H]
#define RSCAN0RMPTR59HL RSCAN0.RMPTR59.UINT8[HL]
#define RSCAN0RMPTR59HH RSCAN0.RMPTR59.UINT8[HH]
#define RSCAN0RMDF059 RSCAN0.RMDF059.UINT32
#define RSCAN0RMDF059L RSCAN0.RMDF059.UINT16[L]
#define RSCAN0RMDF059LL RSCAN0.RMDF059.UINT8[LL]
#define RSCAN0RMDF059LH RSCAN0.RMDF059.UINT8[LH]
#define RSCAN0RMDF059H RSCAN0.RMDF059.UINT16[H]
#define RSCAN0RMDF059HL RSCAN0.RMDF059.UINT8[HL]
#define RSCAN0RMDF059HH RSCAN0.RMDF059.UINT8[HH]
#define RSCAN0RMDF159 RSCAN0.RMDF159.UINT32
#define RSCAN0RMDF159L RSCAN0.RMDF159.UINT16[L]
#define RSCAN0RMDF159LL RSCAN0.RMDF159.UINT8[LL]
#define RSCAN0RMDF159LH RSCAN0.RMDF159.UINT8[LH]
#define RSCAN0RMDF159H RSCAN0.RMDF159.UINT16[H]
#define RSCAN0RMDF159HL RSCAN0.RMDF159.UINT8[HL]
#define RSCAN0RMDF159HH RSCAN0.RMDF159.UINT8[HH]
#define RSCAN0RMID60 RSCAN0.RMID60.UINT32
#define RSCAN0RMID60L RSCAN0.RMID60.UINT16[L]
#define RSCAN0RMID60LL RSCAN0.RMID60.UINT8[LL]
#define RSCAN0RMID60LH RSCAN0.RMID60.UINT8[LH]
#define RSCAN0RMID60H RSCAN0.RMID60.UINT16[H]
#define RSCAN0RMID60HL RSCAN0.RMID60.UINT8[HL]
#define RSCAN0RMID60HH RSCAN0.RMID60.UINT8[HH]
#define RSCAN0RMPTR60 RSCAN0.RMPTR60.UINT32
#define RSCAN0RMPTR60L RSCAN0.RMPTR60.UINT16[L]
#define RSCAN0RMPTR60LL RSCAN0.RMPTR60.UINT8[LL]
#define RSCAN0RMPTR60LH RSCAN0.RMPTR60.UINT8[LH]
#define RSCAN0RMPTR60H RSCAN0.RMPTR60.UINT16[H]
#define RSCAN0RMPTR60HL RSCAN0.RMPTR60.UINT8[HL]
#define RSCAN0RMPTR60HH RSCAN0.RMPTR60.UINT8[HH]
#define RSCAN0RMDF060 RSCAN0.RMDF060.UINT32
#define RSCAN0RMDF060L RSCAN0.RMDF060.UINT16[L]
#define RSCAN0RMDF060LL RSCAN0.RMDF060.UINT8[LL]
#define RSCAN0RMDF060LH RSCAN0.RMDF060.UINT8[LH]
#define RSCAN0RMDF060H RSCAN0.RMDF060.UINT16[H]
#define RSCAN0RMDF060HL RSCAN0.RMDF060.UINT8[HL]
#define RSCAN0RMDF060HH RSCAN0.RMDF060.UINT8[HH]
#define RSCAN0RMDF160 RSCAN0.RMDF160.UINT32
#define RSCAN0RMDF160L RSCAN0.RMDF160.UINT16[L]
#define RSCAN0RMDF160LL RSCAN0.RMDF160.UINT8[LL]
#define RSCAN0RMDF160LH RSCAN0.RMDF160.UINT8[LH]
#define RSCAN0RMDF160H RSCAN0.RMDF160.UINT16[H]
#define RSCAN0RMDF160HL RSCAN0.RMDF160.UINT8[HL]
#define RSCAN0RMDF160HH RSCAN0.RMDF160.UINT8[HH]
#define RSCAN0RMID61 RSCAN0.RMID61.UINT32
#define RSCAN0RMID61L RSCAN0.RMID61.UINT16[L]
#define RSCAN0RMID61LL RSCAN0.RMID61.UINT8[LL]
#define RSCAN0RMID61LH RSCAN0.RMID61.UINT8[LH]
#define RSCAN0RMID61H RSCAN0.RMID61.UINT16[H]
#define RSCAN0RMID61HL RSCAN0.RMID61.UINT8[HL]
#define RSCAN0RMID61HH RSCAN0.RMID61.UINT8[HH]
#define RSCAN0RMPTR61 RSCAN0.RMPTR61.UINT32
#define RSCAN0RMPTR61L RSCAN0.RMPTR61.UINT16[L]
#define RSCAN0RMPTR61LL RSCAN0.RMPTR61.UINT8[LL]
#define RSCAN0RMPTR61LH RSCAN0.RMPTR61.UINT8[LH]
#define RSCAN0RMPTR61H RSCAN0.RMPTR61.UINT16[H]
#define RSCAN0RMPTR61HL RSCAN0.RMPTR61.UINT8[HL]
#define RSCAN0RMPTR61HH RSCAN0.RMPTR61.UINT8[HH]
#define RSCAN0RMDF061 RSCAN0.RMDF061.UINT32
#define RSCAN0RMDF061L RSCAN0.RMDF061.UINT16[L]
#define RSCAN0RMDF061LL RSCAN0.RMDF061.UINT8[LL]
#define RSCAN0RMDF061LH RSCAN0.RMDF061.UINT8[LH]
#define RSCAN0RMDF061H RSCAN0.RMDF061.UINT16[H]
#define RSCAN0RMDF061HL RSCAN0.RMDF061.UINT8[HL]
#define RSCAN0RMDF061HH RSCAN0.RMDF061.UINT8[HH]
#define RSCAN0RMDF161 RSCAN0.RMDF161.UINT32
#define RSCAN0RMDF161L RSCAN0.RMDF161.UINT16[L]
#define RSCAN0RMDF161LL RSCAN0.RMDF161.UINT8[LL]
#define RSCAN0RMDF161LH RSCAN0.RMDF161.UINT8[LH]
#define RSCAN0RMDF161H RSCAN0.RMDF161.UINT16[H]
#define RSCAN0RMDF161HL RSCAN0.RMDF161.UINT8[HL]
#define RSCAN0RMDF161HH RSCAN0.RMDF161.UINT8[HH]
#define RSCAN0RMID62 RSCAN0.RMID62.UINT32
#define RSCAN0RMID62L RSCAN0.RMID62.UINT16[L]
#define RSCAN0RMID62LL RSCAN0.RMID62.UINT8[LL]
#define RSCAN0RMID62LH RSCAN0.RMID62.UINT8[LH]
#define RSCAN0RMID62H RSCAN0.RMID62.UINT16[H]
#define RSCAN0RMID62HL RSCAN0.RMID62.UINT8[HL]
#define RSCAN0RMID62HH RSCAN0.RMID62.UINT8[HH]
#define RSCAN0RMPTR62 RSCAN0.RMPTR62.UINT32
#define RSCAN0RMPTR62L RSCAN0.RMPTR62.UINT16[L]
#define RSCAN0RMPTR62LL RSCAN0.RMPTR62.UINT8[LL]
#define RSCAN0RMPTR62LH RSCAN0.RMPTR62.UINT8[LH]
#define RSCAN0RMPTR62H RSCAN0.RMPTR62.UINT16[H]
#define RSCAN0RMPTR62HL RSCAN0.RMPTR62.UINT8[HL]
#define RSCAN0RMPTR62HH RSCAN0.RMPTR62.UINT8[HH]
#define RSCAN0RMDF062 RSCAN0.RMDF062.UINT32
#define RSCAN0RMDF062L RSCAN0.RMDF062.UINT16[L]
#define RSCAN0RMDF062LL RSCAN0.RMDF062.UINT8[LL]
#define RSCAN0RMDF062LH RSCAN0.RMDF062.UINT8[LH]
#define RSCAN0RMDF062H RSCAN0.RMDF062.UINT16[H]
#define RSCAN0RMDF062HL RSCAN0.RMDF062.UINT8[HL]
#define RSCAN0RMDF062HH RSCAN0.RMDF062.UINT8[HH]
#define RSCAN0RMDF162 RSCAN0.RMDF162.UINT32
#define RSCAN0RMDF162L RSCAN0.RMDF162.UINT16[L]
#define RSCAN0RMDF162LL RSCAN0.RMDF162.UINT8[LL]
#define RSCAN0RMDF162LH RSCAN0.RMDF162.UINT8[LH]
#define RSCAN0RMDF162H RSCAN0.RMDF162.UINT16[H]
#define RSCAN0RMDF162HL RSCAN0.RMDF162.UINT8[HL]
#define RSCAN0RMDF162HH RSCAN0.RMDF162.UINT8[HH]
#define RSCAN0RMID63 RSCAN0.RMID63.UINT32
#define RSCAN0RMID63L RSCAN0.RMID63.UINT16[L]
#define RSCAN0RMID63LL RSCAN0.RMID63.UINT8[LL]
#define RSCAN0RMID63LH RSCAN0.RMID63.UINT8[LH]
#define RSCAN0RMID63H RSCAN0.RMID63.UINT16[H]
#define RSCAN0RMID63HL RSCAN0.RMID63.UINT8[HL]
#define RSCAN0RMID63HH RSCAN0.RMID63.UINT8[HH]
#define RSCAN0RMPTR63 RSCAN0.RMPTR63.UINT32
#define RSCAN0RMPTR63L RSCAN0.RMPTR63.UINT16[L]
#define RSCAN0RMPTR63LL RSCAN0.RMPTR63.UINT8[LL]
#define RSCAN0RMPTR63LH RSCAN0.RMPTR63.UINT8[LH]
#define RSCAN0RMPTR63H RSCAN0.RMPTR63.UINT16[H]
#define RSCAN0RMPTR63HL RSCAN0.RMPTR63.UINT8[HL]
#define RSCAN0RMPTR63HH RSCAN0.RMPTR63.UINT8[HH]
#define RSCAN0RMDF063 RSCAN0.RMDF063.UINT32
#define RSCAN0RMDF063L RSCAN0.RMDF063.UINT16[L]
#define RSCAN0RMDF063LL RSCAN0.RMDF063.UINT8[LL]
#define RSCAN0RMDF063LH RSCAN0.RMDF063.UINT8[LH]
#define RSCAN0RMDF063H RSCAN0.RMDF063.UINT16[H]
#define RSCAN0RMDF063HL RSCAN0.RMDF063.UINT8[HL]
#define RSCAN0RMDF063HH RSCAN0.RMDF063.UINT8[HH]
#define RSCAN0RMDF163 RSCAN0.RMDF163.UINT32
#define RSCAN0RMDF163L RSCAN0.RMDF163.UINT16[L]
#define RSCAN0RMDF163LL RSCAN0.RMDF163.UINT8[LL]
#define RSCAN0RMDF163LH RSCAN0.RMDF163.UINT8[LH]
#define RSCAN0RMDF163H RSCAN0.RMDF163.UINT16[H]
#define RSCAN0RMDF163HL RSCAN0.RMDF163.UINT8[HL]
#define RSCAN0RMDF163HH RSCAN0.RMDF163.UINT8[HH]
#define RSCAN0RMID64 RSCAN0.RMID64.UINT32
#define RSCAN0RMID64L RSCAN0.RMID64.UINT16[L]
#define RSCAN0RMID64LL RSCAN0.RMID64.UINT8[LL]
#define RSCAN0RMID64LH RSCAN0.RMID64.UINT8[LH]
#define RSCAN0RMID64H RSCAN0.RMID64.UINT16[H]
#define RSCAN0RMID64HL RSCAN0.RMID64.UINT8[HL]
#define RSCAN0RMID64HH RSCAN0.RMID64.UINT8[HH]
#define RSCAN0RMPTR64 RSCAN0.RMPTR64.UINT32
#define RSCAN0RMPTR64L RSCAN0.RMPTR64.UINT16[L]
#define RSCAN0RMPTR64LL RSCAN0.RMPTR64.UINT8[LL]
#define RSCAN0RMPTR64LH RSCAN0.RMPTR64.UINT8[LH]
#define RSCAN0RMPTR64H RSCAN0.RMPTR64.UINT16[H]
#define RSCAN0RMPTR64HL RSCAN0.RMPTR64.UINT8[HL]
#define RSCAN0RMPTR64HH RSCAN0.RMPTR64.UINT8[HH]
#define RSCAN0RMDF064 RSCAN0.RMDF064.UINT32
#define RSCAN0RMDF064L RSCAN0.RMDF064.UINT16[L]
#define RSCAN0RMDF064LL RSCAN0.RMDF064.UINT8[LL]
#define RSCAN0RMDF064LH RSCAN0.RMDF064.UINT8[LH]
#define RSCAN0RMDF064H RSCAN0.RMDF064.UINT16[H]
#define RSCAN0RMDF064HL RSCAN0.RMDF064.UINT8[HL]
#define RSCAN0RMDF064HH RSCAN0.RMDF064.UINT8[HH]
#define RSCAN0RMDF164 RSCAN0.RMDF164.UINT32
#define RSCAN0RMDF164L RSCAN0.RMDF164.UINT16[L]
#define RSCAN0RMDF164LL RSCAN0.RMDF164.UINT8[LL]
#define RSCAN0RMDF164LH RSCAN0.RMDF164.UINT8[LH]
#define RSCAN0RMDF164H RSCAN0.RMDF164.UINT16[H]
#define RSCAN0RMDF164HL RSCAN0.RMDF164.UINT8[HL]
#define RSCAN0RMDF164HH RSCAN0.RMDF164.UINT8[HH]
#define RSCAN0RMID65 RSCAN0.RMID65.UINT32
#define RSCAN0RMID65L RSCAN0.RMID65.UINT16[L]
#define RSCAN0RMID65LL RSCAN0.RMID65.UINT8[LL]
#define RSCAN0RMID65LH RSCAN0.RMID65.UINT8[LH]
#define RSCAN0RMID65H RSCAN0.RMID65.UINT16[H]
#define RSCAN0RMID65HL RSCAN0.RMID65.UINT8[HL]
#define RSCAN0RMID65HH RSCAN0.RMID65.UINT8[HH]
#define RSCAN0RMPTR65 RSCAN0.RMPTR65.UINT32
#define RSCAN0RMPTR65L RSCAN0.RMPTR65.UINT16[L]
#define RSCAN0RMPTR65LL RSCAN0.RMPTR65.UINT8[LL]
#define RSCAN0RMPTR65LH RSCAN0.RMPTR65.UINT8[LH]
#define RSCAN0RMPTR65H RSCAN0.RMPTR65.UINT16[H]
#define RSCAN0RMPTR65HL RSCAN0.RMPTR65.UINT8[HL]
#define RSCAN0RMPTR65HH RSCAN0.RMPTR65.UINT8[HH]
#define RSCAN0RMDF065 RSCAN0.RMDF065.UINT32
#define RSCAN0RMDF065L RSCAN0.RMDF065.UINT16[L]
#define RSCAN0RMDF065LL RSCAN0.RMDF065.UINT8[LL]
#define RSCAN0RMDF065LH RSCAN0.RMDF065.UINT8[LH]
#define RSCAN0RMDF065H RSCAN0.RMDF065.UINT16[H]
#define RSCAN0RMDF065HL RSCAN0.RMDF065.UINT8[HL]
#define RSCAN0RMDF065HH RSCAN0.RMDF065.UINT8[HH]
#define RSCAN0RMDF165 RSCAN0.RMDF165.UINT32
#define RSCAN0RMDF165L RSCAN0.RMDF165.UINT16[L]
#define RSCAN0RMDF165LL RSCAN0.RMDF165.UINT8[LL]
#define RSCAN0RMDF165LH RSCAN0.RMDF165.UINT8[LH]
#define RSCAN0RMDF165H RSCAN0.RMDF165.UINT16[H]
#define RSCAN0RMDF165HL RSCAN0.RMDF165.UINT8[HL]
#define RSCAN0RMDF165HH RSCAN0.RMDF165.UINT8[HH]
#define RSCAN0RMID66 RSCAN0.RMID66.UINT32
#define RSCAN0RMID66L RSCAN0.RMID66.UINT16[L]
#define RSCAN0RMID66LL RSCAN0.RMID66.UINT8[LL]
#define RSCAN0RMID66LH RSCAN0.RMID66.UINT8[LH]
#define RSCAN0RMID66H RSCAN0.RMID66.UINT16[H]
#define RSCAN0RMID66HL RSCAN0.RMID66.UINT8[HL]
#define RSCAN0RMID66HH RSCAN0.RMID66.UINT8[HH]
#define RSCAN0RMPTR66 RSCAN0.RMPTR66.UINT32
#define RSCAN0RMPTR66L RSCAN0.RMPTR66.UINT16[L]
#define RSCAN0RMPTR66LL RSCAN0.RMPTR66.UINT8[LL]
#define RSCAN0RMPTR66LH RSCAN0.RMPTR66.UINT8[LH]
#define RSCAN0RMPTR66H RSCAN0.RMPTR66.UINT16[H]
#define RSCAN0RMPTR66HL RSCAN0.RMPTR66.UINT8[HL]
#define RSCAN0RMPTR66HH RSCAN0.RMPTR66.UINT8[HH]
#define RSCAN0RMDF066 RSCAN0.RMDF066.UINT32
#define RSCAN0RMDF066L RSCAN0.RMDF066.UINT16[L]
#define RSCAN0RMDF066LL RSCAN0.RMDF066.UINT8[LL]
#define RSCAN0RMDF066LH RSCAN0.RMDF066.UINT8[LH]
#define RSCAN0RMDF066H RSCAN0.RMDF066.UINT16[H]
#define RSCAN0RMDF066HL RSCAN0.RMDF066.UINT8[HL]
#define RSCAN0RMDF066HH RSCAN0.RMDF066.UINT8[HH]
#define RSCAN0RMDF166 RSCAN0.RMDF166.UINT32
#define RSCAN0RMDF166L RSCAN0.RMDF166.UINT16[L]
#define RSCAN0RMDF166LL RSCAN0.RMDF166.UINT8[LL]
#define RSCAN0RMDF166LH RSCAN0.RMDF166.UINT8[LH]
#define RSCAN0RMDF166H RSCAN0.RMDF166.UINT16[H]
#define RSCAN0RMDF166HL RSCAN0.RMDF166.UINT8[HL]
#define RSCAN0RMDF166HH RSCAN0.RMDF166.UINT8[HH]
#define RSCAN0RMID67 RSCAN0.RMID67.UINT32
#define RSCAN0RMID67L RSCAN0.RMID67.UINT16[L]
#define RSCAN0RMID67LL RSCAN0.RMID67.UINT8[LL]
#define RSCAN0RMID67LH RSCAN0.RMID67.UINT8[LH]
#define RSCAN0RMID67H RSCAN0.RMID67.UINT16[H]
#define RSCAN0RMID67HL RSCAN0.RMID67.UINT8[HL]
#define RSCAN0RMID67HH RSCAN0.RMID67.UINT8[HH]
#define RSCAN0RMPTR67 RSCAN0.RMPTR67.UINT32
#define RSCAN0RMPTR67L RSCAN0.RMPTR67.UINT16[L]
#define RSCAN0RMPTR67LL RSCAN0.RMPTR67.UINT8[LL]
#define RSCAN0RMPTR67LH RSCAN0.RMPTR67.UINT8[LH]
#define RSCAN0RMPTR67H RSCAN0.RMPTR67.UINT16[H]
#define RSCAN0RMPTR67HL RSCAN0.RMPTR67.UINT8[HL]
#define RSCAN0RMPTR67HH RSCAN0.RMPTR67.UINT8[HH]
#define RSCAN0RMDF067 RSCAN0.RMDF067.UINT32
#define RSCAN0RMDF067L RSCAN0.RMDF067.UINT16[L]
#define RSCAN0RMDF067LL RSCAN0.RMDF067.UINT8[LL]
#define RSCAN0RMDF067LH RSCAN0.RMDF067.UINT8[LH]
#define RSCAN0RMDF067H RSCAN0.RMDF067.UINT16[H]
#define RSCAN0RMDF067HL RSCAN0.RMDF067.UINT8[HL]
#define RSCAN0RMDF067HH RSCAN0.RMDF067.UINT8[HH]
#define RSCAN0RMDF167 RSCAN0.RMDF167.UINT32
#define RSCAN0RMDF167L RSCAN0.RMDF167.UINT16[L]
#define RSCAN0RMDF167LL RSCAN0.RMDF167.UINT8[LL]
#define RSCAN0RMDF167LH RSCAN0.RMDF167.UINT8[LH]
#define RSCAN0RMDF167H RSCAN0.RMDF167.UINT16[H]
#define RSCAN0RMDF167HL RSCAN0.RMDF167.UINT8[HL]
#define RSCAN0RMDF167HH RSCAN0.RMDF167.UINT8[HH]
#define RSCAN0RMID68 RSCAN0.RMID68.UINT32
#define RSCAN0RMID68L RSCAN0.RMID68.UINT16[L]
#define RSCAN0RMID68LL RSCAN0.RMID68.UINT8[LL]
#define RSCAN0RMID68LH RSCAN0.RMID68.UINT8[LH]
#define RSCAN0RMID68H RSCAN0.RMID68.UINT16[H]
#define RSCAN0RMID68HL RSCAN0.RMID68.UINT8[HL]
#define RSCAN0RMID68HH RSCAN0.RMID68.UINT8[HH]
#define RSCAN0RMPTR68 RSCAN0.RMPTR68.UINT32
#define RSCAN0RMPTR68L RSCAN0.RMPTR68.UINT16[L]
#define RSCAN0RMPTR68LL RSCAN0.RMPTR68.UINT8[LL]
#define RSCAN0RMPTR68LH RSCAN0.RMPTR68.UINT8[LH]
#define RSCAN0RMPTR68H RSCAN0.RMPTR68.UINT16[H]
#define RSCAN0RMPTR68HL RSCAN0.RMPTR68.UINT8[HL]
#define RSCAN0RMPTR68HH RSCAN0.RMPTR68.UINT8[HH]
#define RSCAN0RMDF068 RSCAN0.RMDF068.UINT32
#define RSCAN0RMDF068L RSCAN0.RMDF068.UINT16[L]
#define RSCAN0RMDF068LL RSCAN0.RMDF068.UINT8[LL]
#define RSCAN0RMDF068LH RSCAN0.RMDF068.UINT8[LH]
#define RSCAN0RMDF068H RSCAN0.RMDF068.UINT16[H]
#define RSCAN0RMDF068HL RSCAN0.RMDF068.UINT8[HL]
#define RSCAN0RMDF068HH RSCAN0.RMDF068.UINT8[HH]
#define RSCAN0RMDF168 RSCAN0.RMDF168.UINT32
#define RSCAN0RMDF168L RSCAN0.RMDF168.UINT16[L]
#define RSCAN0RMDF168LL RSCAN0.RMDF168.UINT8[LL]
#define RSCAN0RMDF168LH RSCAN0.RMDF168.UINT8[LH]
#define RSCAN0RMDF168H RSCAN0.RMDF168.UINT16[H]
#define RSCAN0RMDF168HL RSCAN0.RMDF168.UINT8[HL]
#define RSCAN0RMDF168HH RSCAN0.RMDF168.UINT8[HH]
#define RSCAN0RMID69 RSCAN0.RMID69.UINT32
#define RSCAN0RMID69L RSCAN0.RMID69.UINT16[L]
#define RSCAN0RMID69LL RSCAN0.RMID69.UINT8[LL]
#define RSCAN0RMID69LH RSCAN0.RMID69.UINT8[LH]
#define RSCAN0RMID69H RSCAN0.RMID69.UINT16[H]
#define RSCAN0RMID69HL RSCAN0.RMID69.UINT8[HL]
#define RSCAN0RMID69HH RSCAN0.RMID69.UINT8[HH]
#define RSCAN0RMPTR69 RSCAN0.RMPTR69.UINT32
#define RSCAN0RMPTR69L RSCAN0.RMPTR69.UINT16[L]
#define RSCAN0RMPTR69LL RSCAN0.RMPTR69.UINT8[LL]
#define RSCAN0RMPTR69LH RSCAN0.RMPTR69.UINT8[LH]
#define RSCAN0RMPTR69H RSCAN0.RMPTR69.UINT16[H]
#define RSCAN0RMPTR69HL RSCAN0.RMPTR69.UINT8[HL]
#define RSCAN0RMPTR69HH RSCAN0.RMPTR69.UINT8[HH]
#define RSCAN0RMDF069 RSCAN0.RMDF069.UINT32
#define RSCAN0RMDF069L RSCAN0.RMDF069.UINT16[L]
#define RSCAN0RMDF069LL RSCAN0.RMDF069.UINT8[LL]
#define RSCAN0RMDF069LH RSCAN0.RMDF069.UINT8[LH]
#define RSCAN0RMDF069H RSCAN0.RMDF069.UINT16[H]
#define RSCAN0RMDF069HL RSCAN0.RMDF069.UINT8[HL]
#define RSCAN0RMDF069HH RSCAN0.RMDF069.UINT8[HH]
#define RSCAN0RMDF169 RSCAN0.RMDF169.UINT32
#define RSCAN0RMDF169L RSCAN0.RMDF169.UINT16[L]
#define RSCAN0RMDF169LL RSCAN0.RMDF169.UINT8[LL]
#define RSCAN0RMDF169LH RSCAN0.RMDF169.UINT8[LH]
#define RSCAN0RMDF169H RSCAN0.RMDF169.UINT16[H]
#define RSCAN0RMDF169HL RSCAN0.RMDF169.UINT8[HL]
#define RSCAN0RMDF169HH RSCAN0.RMDF169.UINT8[HH]
#define RSCAN0RMID70 RSCAN0.RMID70.UINT32
#define RSCAN0RMID70L RSCAN0.RMID70.UINT16[L]
#define RSCAN0RMID70LL RSCAN0.RMID70.UINT8[LL]
#define RSCAN0RMID70LH RSCAN0.RMID70.UINT8[LH]
#define RSCAN0RMID70H RSCAN0.RMID70.UINT16[H]
#define RSCAN0RMID70HL RSCAN0.RMID70.UINT8[HL]
#define RSCAN0RMID70HH RSCAN0.RMID70.UINT8[HH]
#define RSCAN0RMPTR70 RSCAN0.RMPTR70.UINT32
#define RSCAN0RMPTR70L RSCAN0.RMPTR70.UINT16[L]
#define RSCAN0RMPTR70LL RSCAN0.RMPTR70.UINT8[LL]
#define RSCAN0RMPTR70LH RSCAN0.RMPTR70.UINT8[LH]
#define RSCAN0RMPTR70H RSCAN0.RMPTR70.UINT16[H]
#define RSCAN0RMPTR70HL RSCAN0.RMPTR70.UINT8[HL]
#define RSCAN0RMPTR70HH RSCAN0.RMPTR70.UINT8[HH]
#define RSCAN0RMDF070 RSCAN0.RMDF070.UINT32
#define RSCAN0RMDF070L RSCAN0.RMDF070.UINT16[L]
#define RSCAN0RMDF070LL RSCAN0.RMDF070.UINT8[LL]
#define RSCAN0RMDF070LH RSCAN0.RMDF070.UINT8[LH]
#define RSCAN0RMDF070H RSCAN0.RMDF070.UINT16[H]
#define RSCAN0RMDF070HL RSCAN0.RMDF070.UINT8[HL]
#define RSCAN0RMDF070HH RSCAN0.RMDF070.UINT8[HH]
#define RSCAN0RMDF170 RSCAN0.RMDF170.UINT32
#define RSCAN0RMDF170L RSCAN0.RMDF170.UINT16[L]
#define RSCAN0RMDF170LL RSCAN0.RMDF170.UINT8[LL]
#define RSCAN0RMDF170LH RSCAN0.RMDF170.UINT8[LH]
#define RSCAN0RMDF170H RSCAN0.RMDF170.UINT16[H]
#define RSCAN0RMDF170HL RSCAN0.RMDF170.UINT8[HL]
#define RSCAN0RMDF170HH RSCAN0.RMDF170.UINT8[HH]
#define RSCAN0RMID71 RSCAN0.RMID71.UINT32
#define RSCAN0RMID71L RSCAN0.RMID71.UINT16[L]
#define RSCAN0RMID71LL RSCAN0.RMID71.UINT8[LL]
#define RSCAN0RMID71LH RSCAN0.RMID71.UINT8[LH]
#define RSCAN0RMID71H RSCAN0.RMID71.UINT16[H]
#define RSCAN0RMID71HL RSCAN0.RMID71.UINT8[HL]
#define RSCAN0RMID71HH RSCAN0.RMID71.UINT8[HH]
#define RSCAN0RMPTR71 RSCAN0.RMPTR71.UINT32
#define RSCAN0RMPTR71L RSCAN0.RMPTR71.UINT16[L]
#define RSCAN0RMPTR71LL RSCAN0.RMPTR71.UINT8[LL]
#define RSCAN0RMPTR71LH RSCAN0.RMPTR71.UINT8[LH]
#define RSCAN0RMPTR71H RSCAN0.RMPTR71.UINT16[H]
#define RSCAN0RMPTR71HL RSCAN0.RMPTR71.UINT8[HL]
#define RSCAN0RMPTR71HH RSCAN0.RMPTR71.UINT8[HH]
#define RSCAN0RMDF071 RSCAN0.RMDF071.UINT32
#define RSCAN0RMDF071L RSCAN0.RMDF071.UINT16[L]
#define RSCAN0RMDF071LL RSCAN0.RMDF071.UINT8[LL]
#define RSCAN0RMDF071LH RSCAN0.RMDF071.UINT8[LH]
#define RSCAN0RMDF071H RSCAN0.RMDF071.UINT16[H]
#define RSCAN0RMDF071HL RSCAN0.RMDF071.UINT8[HL]
#define RSCAN0RMDF071HH RSCAN0.RMDF071.UINT8[HH]
#define RSCAN0RMDF171 RSCAN0.RMDF171.UINT32
#define RSCAN0RMDF171L RSCAN0.RMDF171.UINT16[L]
#define RSCAN0RMDF171LL RSCAN0.RMDF171.UINT8[LL]
#define RSCAN0RMDF171LH RSCAN0.RMDF171.UINT8[LH]
#define RSCAN0RMDF171H RSCAN0.RMDF171.UINT16[H]
#define RSCAN0RMDF171HL RSCAN0.RMDF171.UINT8[HL]
#define RSCAN0RMDF171HH RSCAN0.RMDF171.UINT8[HH]
#define RSCAN0RMID72 RSCAN0.RMID72.UINT32
#define RSCAN0RMID72L RSCAN0.RMID72.UINT16[L]
#define RSCAN0RMID72LL RSCAN0.RMID72.UINT8[LL]
#define RSCAN0RMID72LH RSCAN0.RMID72.UINT8[LH]
#define RSCAN0RMID72H RSCAN0.RMID72.UINT16[H]
#define RSCAN0RMID72HL RSCAN0.RMID72.UINT8[HL]
#define RSCAN0RMID72HH RSCAN0.RMID72.UINT8[HH]
#define RSCAN0RMPTR72 RSCAN0.RMPTR72.UINT32
#define RSCAN0RMPTR72L RSCAN0.RMPTR72.UINT16[L]
#define RSCAN0RMPTR72LL RSCAN0.RMPTR72.UINT8[LL]
#define RSCAN0RMPTR72LH RSCAN0.RMPTR72.UINT8[LH]
#define RSCAN0RMPTR72H RSCAN0.RMPTR72.UINT16[H]
#define RSCAN0RMPTR72HL RSCAN0.RMPTR72.UINT8[HL]
#define RSCAN0RMPTR72HH RSCAN0.RMPTR72.UINT8[HH]
#define RSCAN0RMDF072 RSCAN0.RMDF072.UINT32
#define RSCAN0RMDF072L RSCAN0.RMDF072.UINT16[L]
#define RSCAN0RMDF072LL RSCAN0.RMDF072.UINT8[LL]
#define RSCAN0RMDF072LH RSCAN0.RMDF072.UINT8[LH]
#define RSCAN0RMDF072H RSCAN0.RMDF072.UINT16[H]
#define RSCAN0RMDF072HL RSCAN0.RMDF072.UINT8[HL]
#define RSCAN0RMDF072HH RSCAN0.RMDF072.UINT8[HH]
#define RSCAN0RMDF172 RSCAN0.RMDF172.UINT32
#define RSCAN0RMDF172L RSCAN0.RMDF172.UINT16[L]
#define RSCAN0RMDF172LL RSCAN0.RMDF172.UINT8[LL]
#define RSCAN0RMDF172LH RSCAN0.RMDF172.UINT8[LH]
#define RSCAN0RMDF172H RSCAN0.RMDF172.UINT16[H]
#define RSCAN0RMDF172HL RSCAN0.RMDF172.UINT8[HL]
#define RSCAN0RMDF172HH RSCAN0.RMDF172.UINT8[HH]
#define RSCAN0RMID73 RSCAN0.RMID73.UINT32
#define RSCAN0RMID73L RSCAN0.RMID73.UINT16[L]
#define RSCAN0RMID73LL RSCAN0.RMID73.UINT8[LL]
#define RSCAN0RMID73LH RSCAN0.RMID73.UINT8[LH]
#define RSCAN0RMID73H RSCAN0.RMID73.UINT16[H]
#define RSCAN0RMID73HL RSCAN0.RMID73.UINT8[HL]
#define RSCAN0RMID73HH RSCAN0.RMID73.UINT8[HH]
#define RSCAN0RMPTR73 RSCAN0.RMPTR73.UINT32
#define RSCAN0RMPTR73L RSCAN0.RMPTR73.UINT16[L]
#define RSCAN0RMPTR73LL RSCAN0.RMPTR73.UINT8[LL]
#define RSCAN0RMPTR73LH RSCAN0.RMPTR73.UINT8[LH]
#define RSCAN0RMPTR73H RSCAN0.RMPTR73.UINT16[H]
#define RSCAN0RMPTR73HL RSCAN0.RMPTR73.UINT8[HL]
#define RSCAN0RMPTR73HH RSCAN0.RMPTR73.UINT8[HH]
#define RSCAN0RMDF073 RSCAN0.RMDF073.UINT32
#define RSCAN0RMDF073L RSCAN0.RMDF073.UINT16[L]
#define RSCAN0RMDF073LL RSCAN0.RMDF073.UINT8[LL]
#define RSCAN0RMDF073LH RSCAN0.RMDF073.UINT8[LH]
#define RSCAN0RMDF073H RSCAN0.RMDF073.UINT16[H]
#define RSCAN0RMDF073HL RSCAN0.RMDF073.UINT8[HL]
#define RSCAN0RMDF073HH RSCAN0.RMDF073.UINT8[HH]
#define RSCAN0RMDF173 RSCAN0.RMDF173.UINT32
#define RSCAN0RMDF173L RSCAN0.RMDF173.UINT16[L]
#define RSCAN0RMDF173LL RSCAN0.RMDF173.UINT8[LL]
#define RSCAN0RMDF173LH RSCAN0.RMDF173.UINT8[LH]
#define RSCAN0RMDF173H RSCAN0.RMDF173.UINT16[H]
#define RSCAN0RMDF173HL RSCAN0.RMDF173.UINT8[HL]
#define RSCAN0RMDF173HH RSCAN0.RMDF173.UINT8[HH]
#define RSCAN0RMID74 RSCAN0.RMID74.UINT32
#define RSCAN0RMID74L RSCAN0.RMID74.UINT16[L]
#define RSCAN0RMID74LL RSCAN0.RMID74.UINT8[LL]
#define RSCAN0RMID74LH RSCAN0.RMID74.UINT8[LH]
#define RSCAN0RMID74H RSCAN0.RMID74.UINT16[H]
#define RSCAN0RMID74HL RSCAN0.RMID74.UINT8[HL]
#define RSCAN0RMID74HH RSCAN0.RMID74.UINT8[HH]
#define RSCAN0RMPTR74 RSCAN0.RMPTR74.UINT32
#define RSCAN0RMPTR74L RSCAN0.RMPTR74.UINT16[L]
#define RSCAN0RMPTR74LL RSCAN0.RMPTR74.UINT8[LL]
#define RSCAN0RMPTR74LH RSCAN0.RMPTR74.UINT8[LH]
#define RSCAN0RMPTR74H RSCAN0.RMPTR74.UINT16[H]
#define RSCAN0RMPTR74HL RSCAN0.RMPTR74.UINT8[HL]
#define RSCAN0RMPTR74HH RSCAN0.RMPTR74.UINT8[HH]
#define RSCAN0RMDF074 RSCAN0.RMDF074.UINT32
#define RSCAN0RMDF074L RSCAN0.RMDF074.UINT16[L]
#define RSCAN0RMDF074LL RSCAN0.RMDF074.UINT8[LL]
#define RSCAN0RMDF074LH RSCAN0.RMDF074.UINT8[LH]
#define RSCAN0RMDF074H RSCAN0.RMDF074.UINT16[H]
#define RSCAN0RMDF074HL RSCAN0.RMDF074.UINT8[HL]
#define RSCAN0RMDF074HH RSCAN0.RMDF074.UINT8[HH]
#define RSCAN0RMDF174 RSCAN0.RMDF174.UINT32
#define RSCAN0RMDF174L RSCAN0.RMDF174.UINT16[L]
#define RSCAN0RMDF174LL RSCAN0.RMDF174.UINT8[LL]
#define RSCAN0RMDF174LH RSCAN0.RMDF174.UINT8[LH]
#define RSCAN0RMDF174H RSCAN0.RMDF174.UINT16[H]
#define RSCAN0RMDF174HL RSCAN0.RMDF174.UINT8[HL]
#define RSCAN0RMDF174HH RSCAN0.RMDF174.UINT8[HH]
#define RSCAN0RMID75 RSCAN0.RMID75.UINT32
#define RSCAN0RMID75L RSCAN0.RMID75.UINT16[L]
#define RSCAN0RMID75LL RSCAN0.RMID75.UINT8[LL]
#define RSCAN0RMID75LH RSCAN0.RMID75.UINT8[LH]
#define RSCAN0RMID75H RSCAN0.RMID75.UINT16[H]
#define RSCAN0RMID75HL RSCAN0.RMID75.UINT8[HL]
#define RSCAN0RMID75HH RSCAN0.RMID75.UINT8[HH]
#define RSCAN0RMPTR75 RSCAN0.RMPTR75.UINT32
#define RSCAN0RMPTR75L RSCAN0.RMPTR75.UINT16[L]
#define RSCAN0RMPTR75LL RSCAN0.RMPTR75.UINT8[LL]
#define RSCAN0RMPTR75LH RSCAN0.RMPTR75.UINT8[LH]
#define RSCAN0RMPTR75H RSCAN0.RMPTR75.UINT16[H]
#define RSCAN0RMPTR75HL RSCAN0.RMPTR75.UINT8[HL]
#define RSCAN0RMPTR75HH RSCAN0.RMPTR75.UINT8[HH]
#define RSCAN0RMDF075 RSCAN0.RMDF075.UINT32
#define RSCAN0RMDF075L RSCAN0.RMDF075.UINT16[L]
#define RSCAN0RMDF075LL RSCAN0.RMDF075.UINT8[LL]
#define RSCAN0RMDF075LH RSCAN0.RMDF075.UINT8[LH]
#define RSCAN0RMDF075H RSCAN0.RMDF075.UINT16[H]
#define RSCAN0RMDF075HL RSCAN0.RMDF075.UINT8[HL]
#define RSCAN0RMDF075HH RSCAN0.RMDF075.UINT8[HH]
#define RSCAN0RMDF175 RSCAN0.RMDF175.UINT32
#define RSCAN0RMDF175L RSCAN0.RMDF175.UINT16[L]
#define RSCAN0RMDF175LL RSCAN0.RMDF175.UINT8[LL]
#define RSCAN0RMDF175LH RSCAN0.RMDF175.UINT8[LH]
#define RSCAN0RMDF175H RSCAN0.RMDF175.UINT16[H]
#define RSCAN0RMDF175HL RSCAN0.RMDF175.UINT8[HL]
#define RSCAN0RMDF175HH RSCAN0.RMDF175.UINT8[HH]
#define RSCAN0RMID76 RSCAN0.RMID76.UINT32
#define RSCAN0RMID76L RSCAN0.RMID76.UINT16[L]
#define RSCAN0RMID76LL RSCAN0.RMID76.UINT8[LL]
#define RSCAN0RMID76LH RSCAN0.RMID76.UINT8[LH]
#define RSCAN0RMID76H RSCAN0.RMID76.UINT16[H]
#define RSCAN0RMID76HL RSCAN0.RMID76.UINT8[HL]
#define RSCAN0RMID76HH RSCAN0.RMID76.UINT8[HH]
#define RSCAN0RMPTR76 RSCAN0.RMPTR76.UINT32
#define RSCAN0RMPTR76L RSCAN0.RMPTR76.UINT16[L]
#define RSCAN0RMPTR76LL RSCAN0.RMPTR76.UINT8[LL]
#define RSCAN0RMPTR76LH RSCAN0.RMPTR76.UINT8[LH]
#define RSCAN0RMPTR76H RSCAN0.RMPTR76.UINT16[H]
#define RSCAN0RMPTR76HL RSCAN0.RMPTR76.UINT8[HL]
#define RSCAN0RMPTR76HH RSCAN0.RMPTR76.UINT8[HH]
#define RSCAN0RMDF076 RSCAN0.RMDF076.UINT32
#define RSCAN0RMDF076L RSCAN0.RMDF076.UINT16[L]
#define RSCAN0RMDF076LL RSCAN0.RMDF076.UINT8[LL]
#define RSCAN0RMDF076LH RSCAN0.RMDF076.UINT8[LH]
#define RSCAN0RMDF076H RSCAN0.RMDF076.UINT16[H]
#define RSCAN0RMDF076HL RSCAN0.RMDF076.UINT8[HL]
#define RSCAN0RMDF076HH RSCAN0.RMDF076.UINT8[HH]
#define RSCAN0RMDF176 RSCAN0.RMDF176.UINT32
#define RSCAN0RMDF176L RSCAN0.RMDF176.UINT16[L]
#define RSCAN0RMDF176LL RSCAN0.RMDF176.UINT8[LL]
#define RSCAN0RMDF176LH RSCAN0.RMDF176.UINT8[LH]
#define RSCAN0RMDF176H RSCAN0.RMDF176.UINT16[H]
#define RSCAN0RMDF176HL RSCAN0.RMDF176.UINT8[HL]
#define RSCAN0RMDF176HH RSCAN0.RMDF176.UINT8[HH]
#define RSCAN0RMID77 RSCAN0.RMID77.UINT32
#define RSCAN0RMID77L RSCAN0.RMID77.UINT16[L]
#define RSCAN0RMID77LL RSCAN0.RMID77.UINT8[LL]
#define RSCAN0RMID77LH RSCAN0.RMID77.UINT8[LH]
#define RSCAN0RMID77H RSCAN0.RMID77.UINT16[H]
#define RSCAN0RMID77HL RSCAN0.RMID77.UINT8[HL]
#define RSCAN0RMID77HH RSCAN0.RMID77.UINT8[HH]
#define RSCAN0RMPTR77 RSCAN0.RMPTR77.UINT32
#define RSCAN0RMPTR77L RSCAN0.RMPTR77.UINT16[L]
#define RSCAN0RMPTR77LL RSCAN0.RMPTR77.UINT8[LL]
#define RSCAN0RMPTR77LH RSCAN0.RMPTR77.UINT8[LH]
#define RSCAN0RMPTR77H RSCAN0.RMPTR77.UINT16[H]
#define RSCAN0RMPTR77HL RSCAN0.RMPTR77.UINT8[HL]
#define RSCAN0RMPTR77HH RSCAN0.RMPTR77.UINT8[HH]
#define RSCAN0RMDF077 RSCAN0.RMDF077.UINT32
#define RSCAN0RMDF077L RSCAN0.RMDF077.UINT16[L]
#define RSCAN0RMDF077LL RSCAN0.RMDF077.UINT8[LL]
#define RSCAN0RMDF077LH RSCAN0.RMDF077.UINT8[LH]
#define RSCAN0RMDF077H RSCAN0.RMDF077.UINT16[H]
#define RSCAN0RMDF077HL RSCAN0.RMDF077.UINT8[HL]
#define RSCAN0RMDF077HH RSCAN0.RMDF077.UINT8[HH]
#define RSCAN0RMDF177 RSCAN0.RMDF177.UINT32
#define RSCAN0RMDF177L RSCAN0.RMDF177.UINT16[L]
#define RSCAN0RMDF177LL RSCAN0.RMDF177.UINT8[LL]
#define RSCAN0RMDF177LH RSCAN0.RMDF177.UINT8[LH]
#define RSCAN0RMDF177H RSCAN0.RMDF177.UINT16[H]
#define RSCAN0RMDF177HL RSCAN0.RMDF177.UINT8[HL]
#define RSCAN0RMDF177HH RSCAN0.RMDF177.UINT8[HH]
#define RSCAN0RMID78 RSCAN0.RMID78.UINT32
#define RSCAN0RMID78L RSCAN0.RMID78.UINT16[L]
#define RSCAN0RMID78LL RSCAN0.RMID78.UINT8[LL]
#define RSCAN0RMID78LH RSCAN0.RMID78.UINT8[LH]
#define RSCAN0RMID78H RSCAN0.RMID78.UINT16[H]
#define RSCAN0RMID78HL RSCAN0.RMID78.UINT8[HL]
#define RSCAN0RMID78HH RSCAN0.RMID78.UINT8[HH]
#define RSCAN0RMPTR78 RSCAN0.RMPTR78.UINT32
#define RSCAN0RMPTR78L RSCAN0.RMPTR78.UINT16[L]
#define RSCAN0RMPTR78LL RSCAN0.RMPTR78.UINT8[LL]
#define RSCAN0RMPTR78LH RSCAN0.RMPTR78.UINT8[LH]
#define RSCAN0RMPTR78H RSCAN0.RMPTR78.UINT16[H]
#define RSCAN0RMPTR78HL RSCAN0.RMPTR78.UINT8[HL]
#define RSCAN0RMPTR78HH RSCAN0.RMPTR78.UINT8[HH]
#define RSCAN0RMDF078 RSCAN0.RMDF078.UINT32
#define RSCAN0RMDF078L RSCAN0.RMDF078.UINT16[L]
#define RSCAN0RMDF078LL RSCAN0.RMDF078.UINT8[LL]
#define RSCAN0RMDF078LH RSCAN0.RMDF078.UINT8[LH]
#define RSCAN0RMDF078H RSCAN0.RMDF078.UINT16[H]
#define RSCAN0RMDF078HL RSCAN0.RMDF078.UINT8[HL]
#define RSCAN0RMDF078HH RSCAN0.RMDF078.UINT8[HH]
#define RSCAN0RMDF178 RSCAN0.RMDF178.UINT32
#define RSCAN0RMDF178L RSCAN0.RMDF178.UINT16[L]
#define RSCAN0RMDF178LL RSCAN0.RMDF178.UINT8[LL]
#define RSCAN0RMDF178LH RSCAN0.RMDF178.UINT8[LH]
#define RSCAN0RMDF178H RSCAN0.RMDF178.UINT16[H]
#define RSCAN0RMDF178HL RSCAN0.RMDF178.UINT8[HL]
#define RSCAN0RMDF178HH RSCAN0.RMDF178.UINT8[HH]
#define RSCAN0RMID79 RSCAN0.RMID79.UINT32
#define RSCAN0RMID79L RSCAN0.RMID79.UINT16[L]
#define RSCAN0RMID79LL RSCAN0.RMID79.UINT8[LL]
#define RSCAN0RMID79LH RSCAN0.RMID79.UINT8[LH]
#define RSCAN0RMID79H RSCAN0.RMID79.UINT16[H]
#define RSCAN0RMID79HL RSCAN0.RMID79.UINT8[HL]
#define RSCAN0RMID79HH RSCAN0.RMID79.UINT8[HH]
#define RSCAN0RMPTR79 RSCAN0.RMPTR79.UINT32
#define RSCAN0RMPTR79L RSCAN0.RMPTR79.UINT16[L]
#define RSCAN0RMPTR79LL RSCAN0.RMPTR79.UINT8[LL]
#define RSCAN0RMPTR79LH RSCAN0.RMPTR79.UINT8[LH]
#define RSCAN0RMPTR79H RSCAN0.RMPTR79.UINT16[H]
#define RSCAN0RMPTR79HL RSCAN0.RMPTR79.UINT8[HL]
#define RSCAN0RMPTR79HH RSCAN0.RMPTR79.UINT8[HH]
#define RSCAN0RMDF079 RSCAN0.RMDF079.UINT32
#define RSCAN0RMDF079L RSCAN0.RMDF079.UINT16[L]
#define RSCAN0RMDF079LL RSCAN0.RMDF079.UINT8[LL]
#define RSCAN0RMDF079LH RSCAN0.RMDF079.UINT8[LH]
#define RSCAN0RMDF079H RSCAN0.RMDF079.UINT16[H]
#define RSCAN0RMDF079HL RSCAN0.RMDF079.UINT8[HL]
#define RSCAN0RMDF079HH RSCAN0.RMDF079.UINT8[HH]
#define RSCAN0RMDF179 RSCAN0.RMDF179.UINT32
#define RSCAN0RMDF179L RSCAN0.RMDF179.UINT16[L]
#define RSCAN0RMDF179LL RSCAN0.RMDF179.UINT8[LL]
#define RSCAN0RMDF179LH RSCAN0.RMDF179.UINT8[LH]
#define RSCAN0RMDF179H RSCAN0.RMDF179.UINT16[H]
#define RSCAN0RMDF179HL RSCAN0.RMDF179.UINT8[HL]
#define RSCAN0RMDF179HH RSCAN0.RMDF179.UINT8[HH]
#define RSCAN0RFID0 RSCAN0.RFID0.UINT32
#define RSCAN0RFID0L RSCAN0.RFID0.UINT16[L]
#define RSCAN0RFID0LL RSCAN0.RFID0.UINT8[LL]
#define RSCAN0RFID0LH RSCAN0.RFID0.UINT8[LH]
#define RSCAN0RFID0H RSCAN0.RFID0.UINT16[H]
#define RSCAN0RFID0HL RSCAN0.RFID0.UINT8[HL]
#define RSCAN0RFID0HH RSCAN0.RFID0.UINT8[HH]
#define RSCAN0RFPTR0 RSCAN0.RFPTR0.UINT32
#define RSCAN0RFPTR0L RSCAN0.RFPTR0.UINT16[L]
#define RSCAN0RFPTR0LL RSCAN0.RFPTR0.UINT8[LL]
#define RSCAN0RFPTR0LH RSCAN0.RFPTR0.UINT8[LH]
#define RSCAN0RFPTR0H RSCAN0.RFPTR0.UINT16[H]
#define RSCAN0RFPTR0HL RSCAN0.RFPTR0.UINT8[HL]
#define RSCAN0RFPTR0HH RSCAN0.RFPTR0.UINT8[HH]
#define RSCAN0RFDF00 RSCAN0.RFDF00.UINT32
#define RSCAN0RFDF00L RSCAN0.RFDF00.UINT16[L]
#define RSCAN0RFDF00LL RSCAN0.RFDF00.UINT8[LL]
#define RSCAN0RFDF00LH RSCAN0.RFDF00.UINT8[LH]
#define RSCAN0RFDF00H RSCAN0.RFDF00.UINT16[H]
#define RSCAN0RFDF00HL RSCAN0.RFDF00.UINT8[HL]
#define RSCAN0RFDF00HH RSCAN0.RFDF00.UINT8[HH]
#define RSCAN0RFDF10 RSCAN0.RFDF10.UINT32
#define RSCAN0RFDF10L RSCAN0.RFDF10.UINT16[L]
#define RSCAN0RFDF10LL RSCAN0.RFDF10.UINT8[LL]
#define RSCAN0RFDF10LH RSCAN0.RFDF10.UINT8[LH]
#define RSCAN0RFDF10H RSCAN0.RFDF10.UINT16[H]
#define RSCAN0RFDF10HL RSCAN0.RFDF10.UINT8[HL]
#define RSCAN0RFDF10HH RSCAN0.RFDF10.UINT8[HH]
#define RSCAN0RFID1 RSCAN0.RFID1.UINT32
#define RSCAN0RFID1L RSCAN0.RFID1.UINT16[L]
#define RSCAN0RFID1LL RSCAN0.RFID1.UINT8[LL]
#define RSCAN0RFID1LH RSCAN0.RFID1.UINT8[LH]
#define RSCAN0RFID1H RSCAN0.RFID1.UINT16[H]
#define RSCAN0RFID1HL RSCAN0.RFID1.UINT8[HL]
#define RSCAN0RFID1HH RSCAN0.RFID1.UINT8[HH]
#define RSCAN0RFPTR1 RSCAN0.RFPTR1.UINT32
#define RSCAN0RFPTR1L RSCAN0.RFPTR1.UINT16[L]
#define RSCAN0RFPTR1LL RSCAN0.RFPTR1.UINT8[LL]
#define RSCAN0RFPTR1LH RSCAN0.RFPTR1.UINT8[LH]
#define RSCAN0RFPTR1H RSCAN0.RFPTR1.UINT16[H]
#define RSCAN0RFPTR1HL RSCAN0.RFPTR1.UINT8[HL]
#define RSCAN0RFPTR1HH RSCAN0.RFPTR1.UINT8[HH]
#define RSCAN0RFDF01 RSCAN0.RFDF01.UINT32
#define RSCAN0RFDF01L RSCAN0.RFDF01.UINT16[L]
#define RSCAN0RFDF01LL RSCAN0.RFDF01.UINT8[LL]
#define RSCAN0RFDF01LH RSCAN0.RFDF01.UINT8[LH]
#define RSCAN0RFDF01H RSCAN0.RFDF01.UINT16[H]
#define RSCAN0RFDF01HL RSCAN0.RFDF01.UINT8[HL]
#define RSCAN0RFDF01HH RSCAN0.RFDF01.UINT8[HH]
#define RSCAN0RFDF11 RSCAN0.RFDF11.UINT32
#define RSCAN0RFDF11L RSCAN0.RFDF11.UINT16[L]
#define RSCAN0RFDF11LL RSCAN0.RFDF11.UINT8[LL]
#define RSCAN0RFDF11LH RSCAN0.RFDF11.UINT8[LH]
#define RSCAN0RFDF11H RSCAN0.RFDF11.UINT16[H]
#define RSCAN0RFDF11HL RSCAN0.RFDF11.UINT8[HL]
#define RSCAN0RFDF11HH RSCAN0.RFDF11.UINT8[HH]
#define RSCAN0RFID2 RSCAN0.RFID2.UINT32
#define RSCAN0RFID2L RSCAN0.RFID2.UINT16[L]
#define RSCAN0RFID2LL RSCAN0.RFID2.UINT8[LL]
#define RSCAN0RFID2LH RSCAN0.RFID2.UINT8[LH]
#define RSCAN0RFID2H RSCAN0.RFID2.UINT16[H]
#define RSCAN0RFID2HL RSCAN0.RFID2.UINT8[HL]
#define RSCAN0RFID2HH RSCAN0.RFID2.UINT8[HH]
#define RSCAN0RFPTR2 RSCAN0.RFPTR2.UINT32
#define RSCAN0RFPTR2L RSCAN0.RFPTR2.UINT16[L]
#define RSCAN0RFPTR2LL RSCAN0.RFPTR2.UINT8[LL]
#define RSCAN0RFPTR2LH RSCAN0.RFPTR2.UINT8[LH]
#define RSCAN0RFPTR2H RSCAN0.RFPTR2.UINT16[H]
#define RSCAN0RFPTR2HL RSCAN0.RFPTR2.UINT8[HL]
#define RSCAN0RFPTR2HH RSCAN0.RFPTR2.UINT8[HH]
#define RSCAN0RFDF02 RSCAN0.RFDF02.UINT32
#define RSCAN0RFDF02L RSCAN0.RFDF02.UINT16[L]
#define RSCAN0RFDF02LL RSCAN0.RFDF02.UINT8[LL]
#define RSCAN0RFDF02LH RSCAN0.RFDF02.UINT8[LH]
#define RSCAN0RFDF02H RSCAN0.RFDF02.UINT16[H]
#define RSCAN0RFDF02HL RSCAN0.RFDF02.UINT8[HL]
#define RSCAN0RFDF02HH RSCAN0.RFDF02.UINT8[HH]
#define RSCAN0RFDF12 RSCAN0.RFDF12.UINT32
#define RSCAN0RFDF12L RSCAN0.RFDF12.UINT16[L]
#define RSCAN0RFDF12LL RSCAN0.RFDF12.UINT8[LL]
#define RSCAN0RFDF12LH RSCAN0.RFDF12.UINT8[LH]
#define RSCAN0RFDF12H RSCAN0.RFDF12.UINT16[H]
#define RSCAN0RFDF12HL RSCAN0.RFDF12.UINT8[HL]
#define RSCAN0RFDF12HH RSCAN0.RFDF12.UINT8[HH]
#define RSCAN0RFID3 RSCAN0.RFID3.UINT32
#define RSCAN0RFID3L RSCAN0.RFID3.UINT16[L]
#define RSCAN0RFID3LL RSCAN0.RFID3.UINT8[LL]
#define RSCAN0RFID3LH RSCAN0.RFID3.UINT8[LH]
#define RSCAN0RFID3H RSCAN0.RFID3.UINT16[H]
#define RSCAN0RFID3HL RSCAN0.RFID3.UINT8[HL]
#define RSCAN0RFID3HH RSCAN0.RFID3.UINT8[HH]
#define RSCAN0RFPTR3 RSCAN0.RFPTR3.UINT32
#define RSCAN0RFPTR3L RSCAN0.RFPTR3.UINT16[L]
#define RSCAN0RFPTR3LL RSCAN0.RFPTR3.UINT8[LL]
#define RSCAN0RFPTR3LH RSCAN0.RFPTR3.UINT8[LH]
#define RSCAN0RFPTR3H RSCAN0.RFPTR3.UINT16[H]
#define RSCAN0RFPTR3HL RSCAN0.RFPTR3.UINT8[HL]
#define RSCAN0RFPTR3HH RSCAN0.RFPTR3.UINT8[HH]
#define RSCAN0RFDF03 RSCAN0.RFDF03.UINT32
#define RSCAN0RFDF03L RSCAN0.RFDF03.UINT16[L]
#define RSCAN0RFDF03LL RSCAN0.RFDF03.UINT8[LL]
#define RSCAN0RFDF03LH RSCAN0.RFDF03.UINT8[LH]
#define RSCAN0RFDF03H RSCAN0.RFDF03.UINT16[H]
#define RSCAN0RFDF03HL RSCAN0.RFDF03.UINT8[HL]
#define RSCAN0RFDF03HH RSCAN0.RFDF03.UINT8[HH]
#define RSCAN0RFDF13 RSCAN0.RFDF13.UINT32
#define RSCAN0RFDF13L RSCAN0.RFDF13.UINT16[L]
#define RSCAN0RFDF13LL RSCAN0.RFDF13.UINT8[LL]
#define RSCAN0RFDF13LH RSCAN0.RFDF13.UINT8[LH]
#define RSCAN0RFDF13H RSCAN0.RFDF13.UINT16[H]
#define RSCAN0RFDF13HL RSCAN0.RFDF13.UINT8[HL]
#define RSCAN0RFDF13HH RSCAN0.RFDF13.UINT8[HH]
#define RSCAN0RFID4 RSCAN0.RFID4.UINT32
#define RSCAN0RFID4L RSCAN0.RFID4.UINT16[L]
#define RSCAN0RFID4LL RSCAN0.RFID4.UINT8[LL]
#define RSCAN0RFID4LH RSCAN0.RFID4.UINT8[LH]
#define RSCAN0RFID4H RSCAN0.RFID4.UINT16[H]
#define RSCAN0RFID4HL RSCAN0.RFID4.UINT8[HL]
#define RSCAN0RFID4HH RSCAN0.RFID4.UINT8[HH]
#define RSCAN0RFPTR4 RSCAN0.RFPTR4.UINT32
#define RSCAN0RFPTR4L RSCAN0.RFPTR4.UINT16[L]
#define RSCAN0RFPTR4LL RSCAN0.RFPTR4.UINT8[LL]
#define RSCAN0RFPTR4LH RSCAN0.RFPTR4.UINT8[LH]
#define RSCAN0RFPTR4H RSCAN0.RFPTR4.UINT16[H]
#define RSCAN0RFPTR4HL RSCAN0.RFPTR4.UINT8[HL]
#define RSCAN0RFPTR4HH RSCAN0.RFPTR4.UINT8[HH]
#define RSCAN0RFDF04 RSCAN0.RFDF04.UINT32
#define RSCAN0RFDF04L RSCAN0.RFDF04.UINT16[L]
#define RSCAN0RFDF04LL RSCAN0.RFDF04.UINT8[LL]
#define RSCAN0RFDF04LH RSCAN0.RFDF04.UINT8[LH]
#define RSCAN0RFDF04H RSCAN0.RFDF04.UINT16[H]
#define RSCAN0RFDF04HL RSCAN0.RFDF04.UINT8[HL]
#define RSCAN0RFDF04HH RSCAN0.RFDF04.UINT8[HH]
#define RSCAN0RFDF14 RSCAN0.RFDF14.UINT32
#define RSCAN0RFDF14L RSCAN0.RFDF14.UINT16[L]
#define RSCAN0RFDF14LL RSCAN0.RFDF14.UINT8[LL]
#define RSCAN0RFDF14LH RSCAN0.RFDF14.UINT8[LH]
#define RSCAN0RFDF14H RSCAN0.RFDF14.UINT16[H]
#define RSCAN0RFDF14HL RSCAN0.RFDF14.UINT8[HL]
#define RSCAN0RFDF14HH RSCAN0.RFDF14.UINT8[HH]
#define RSCAN0RFID5 RSCAN0.RFID5.UINT32
#define RSCAN0RFID5L RSCAN0.RFID5.UINT16[L]
#define RSCAN0RFID5LL RSCAN0.RFID5.UINT8[LL]
#define RSCAN0RFID5LH RSCAN0.RFID5.UINT8[LH]
#define RSCAN0RFID5H RSCAN0.RFID5.UINT16[H]
#define RSCAN0RFID5HL RSCAN0.RFID5.UINT8[HL]
#define RSCAN0RFID5HH RSCAN0.RFID5.UINT8[HH]
#define RSCAN0RFPTR5 RSCAN0.RFPTR5.UINT32
#define RSCAN0RFPTR5L RSCAN0.RFPTR5.UINT16[L]
#define RSCAN0RFPTR5LL RSCAN0.RFPTR5.UINT8[LL]
#define RSCAN0RFPTR5LH RSCAN0.RFPTR5.UINT8[LH]
#define RSCAN0RFPTR5H RSCAN0.RFPTR5.UINT16[H]
#define RSCAN0RFPTR5HL RSCAN0.RFPTR5.UINT8[HL]
#define RSCAN0RFPTR5HH RSCAN0.RFPTR5.UINT8[HH]
#define RSCAN0RFDF05 RSCAN0.RFDF05.UINT32
#define RSCAN0RFDF05L RSCAN0.RFDF05.UINT16[L]
#define RSCAN0RFDF05LL RSCAN0.RFDF05.UINT8[LL]
#define RSCAN0RFDF05LH RSCAN0.RFDF05.UINT8[LH]
#define RSCAN0RFDF05H RSCAN0.RFDF05.UINT16[H]
#define RSCAN0RFDF05HL RSCAN0.RFDF05.UINT8[HL]
#define RSCAN0RFDF05HH RSCAN0.RFDF05.UINT8[HH]
#define RSCAN0RFDF15 RSCAN0.RFDF15.UINT32
#define RSCAN0RFDF15L RSCAN0.RFDF15.UINT16[L]
#define RSCAN0RFDF15LL RSCAN0.RFDF15.UINT8[LL]
#define RSCAN0RFDF15LH RSCAN0.RFDF15.UINT8[LH]
#define RSCAN0RFDF15H RSCAN0.RFDF15.UINT16[H]
#define RSCAN0RFDF15HL RSCAN0.RFDF15.UINT8[HL]
#define RSCAN0RFDF15HH RSCAN0.RFDF15.UINT8[HH]
#define RSCAN0RFID6 RSCAN0.RFID6.UINT32
#define RSCAN0RFID6L RSCAN0.RFID6.UINT16[L]
#define RSCAN0RFID6LL RSCAN0.RFID6.UINT8[LL]
#define RSCAN0RFID6LH RSCAN0.RFID6.UINT8[LH]
#define RSCAN0RFID6H RSCAN0.RFID6.UINT16[H]
#define RSCAN0RFID6HL RSCAN0.RFID6.UINT8[HL]
#define RSCAN0RFID6HH RSCAN0.RFID6.UINT8[HH]
#define RSCAN0RFPTR6 RSCAN0.RFPTR6.UINT32
#define RSCAN0RFPTR6L RSCAN0.RFPTR6.UINT16[L]
#define RSCAN0RFPTR6LL RSCAN0.RFPTR6.UINT8[LL]
#define RSCAN0RFPTR6LH RSCAN0.RFPTR6.UINT8[LH]
#define RSCAN0RFPTR6H RSCAN0.RFPTR6.UINT16[H]
#define RSCAN0RFPTR6HL RSCAN0.RFPTR6.UINT8[HL]
#define RSCAN0RFPTR6HH RSCAN0.RFPTR6.UINT8[HH]
#define RSCAN0RFDF06 RSCAN0.RFDF06.UINT32
#define RSCAN0RFDF06L RSCAN0.RFDF06.UINT16[L]
#define RSCAN0RFDF06LL RSCAN0.RFDF06.UINT8[LL]
#define RSCAN0RFDF06LH RSCAN0.RFDF06.UINT8[LH]
#define RSCAN0RFDF06H RSCAN0.RFDF06.UINT16[H]
#define RSCAN0RFDF06HL RSCAN0.RFDF06.UINT8[HL]
#define RSCAN0RFDF06HH RSCAN0.RFDF06.UINT8[HH]
#define RSCAN0RFDF16 RSCAN0.RFDF16.UINT32
#define RSCAN0RFDF16L RSCAN0.RFDF16.UINT16[L]
#define RSCAN0RFDF16LL RSCAN0.RFDF16.UINT8[LL]
#define RSCAN0RFDF16LH RSCAN0.RFDF16.UINT8[LH]
#define RSCAN0RFDF16H RSCAN0.RFDF16.UINT16[H]
#define RSCAN0RFDF16HL RSCAN0.RFDF16.UINT8[HL]
#define RSCAN0RFDF16HH RSCAN0.RFDF16.UINT8[HH]
#define RSCAN0RFID7 RSCAN0.RFID7.UINT32
#define RSCAN0RFID7L RSCAN0.RFID7.UINT16[L]
#define RSCAN0RFID7LL RSCAN0.RFID7.UINT8[LL]
#define RSCAN0RFID7LH RSCAN0.RFID7.UINT8[LH]
#define RSCAN0RFID7H RSCAN0.RFID7.UINT16[H]
#define RSCAN0RFID7HL RSCAN0.RFID7.UINT8[HL]
#define RSCAN0RFID7HH RSCAN0.RFID7.UINT8[HH]
#define RSCAN0RFPTR7 RSCAN0.RFPTR7.UINT32
#define RSCAN0RFPTR7L RSCAN0.RFPTR7.UINT16[L]
#define RSCAN0RFPTR7LL RSCAN0.RFPTR7.UINT8[LL]
#define RSCAN0RFPTR7LH RSCAN0.RFPTR7.UINT8[LH]
#define RSCAN0RFPTR7H RSCAN0.RFPTR7.UINT16[H]
#define RSCAN0RFPTR7HL RSCAN0.RFPTR7.UINT8[HL]
#define RSCAN0RFPTR7HH RSCAN0.RFPTR7.UINT8[HH]
#define RSCAN0RFDF07 RSCAN0.RFDF07.UINT32
#define RSCAN0RFDF07L RSCAN0.RFDF07.UINT16[L]
#define RSCAN0RFDF07LL RSCAN0.RFDF07.UINT8[LL]
#define RSCAN0RFDF07LH RSCAN0.RFDF07.UINT8[LH]
#define RSCAN0RFDF07H RSCAN0.RFDF07.UINT16[H]
#define RSCAN0RFDF07HL RSCAN0.RFDF07.UINT8[HL]
#define RSCAN0RFDF07HH RSCAN0.RFDF07.UINT8[HH]
#define RSCAN0RFDF17 RSCAN0.RFDF17.UINT32
#define RSCAN0RFDF17L RSCAN0.RFDF17.UINT16[L]
#define RSCAN0RFDF17LL RSCAN0.RFDF17.UINT8[LL]
#define RSCAN0RFDF17LH RSCAN0.RFDF17.UINT8[LH]
#define RSCAN0RFDF17H RSCAN0.RFDF17.UINT16[H]
#define RSCAN0RFDF17HL RSCAN0.RFDF17.UINT8[HL]
#define RSCAN0RFDF17HH RSCAN0.RFDF17.UINT8[HH]
#define RSCAN0CFID0 RSCAN0.CFID0.UINT32
#define RSCAN0CFID0L RSCAN0.CFID0.UINT16[L]
#define RSCAN0CFID0LL RSCAN0.CFID0.UINT8[LL]
#define RSCAN0CFID0LH RSCAN0.CFID0.UINT8[LH]
#define RSCAN0CFID0H RSCAN0.CFID0.UINT16[H]
#define RSCAN0CFID0HL RSCAN0.CFID0.UINT8[HL]
#define RSCAN0CFID0HH RSCAN0.CFID0.UINT8[HH]
#define RSCAN0CFPTR0 RSCAN0.CFPTR0.UINT32
#define RSCAN0CFPTR0L RSCAN0.CFPTR0.UINT16[L]
#define RSCAN0CFPTR0LL RSCAN0.CFPTR0.UINT8[LL]
#define RSCAN0CFPTR0LH RSCAN0.CFPTR0.UINT8[LH]
#define RSCAN0CFPTR0H RSCAN0.CFPTR0.UINT16[H]
#define RSCAN0CFPTR0HL RSCAN0.CFPTR0.UINT8[HL]
#define RSCAN0CFPTR0HH RSCAN0.CFPTR0.UINT8[HH]
#define RSCAN0CFDF00 RSCAN0.CFDF00.UINT32
#define RSCAN0CFDF00L RSCAN0.CFDF00.UINT16[L]
#define RSCAN0CFDF00LL RSCAN0.CFDF00.UINT8[LL]
#define RSCAN0CFDF00LH RSCAN0.CFDF00.UINT8[LH]
#define RSCAN0CFDF00H RSCAN0.CFDF00.UINT16[H]
#define RSCAN0CFDF00HL RSCAN0.CFDF00.UINT8[HL]
#define RSCAN0CFDF00HH RSCAN0.CFDF00.UINT8[HH]
#define RSCAN0CFDF10 RSCAN0.CFDF10.UINT32
#define RSCAN0CFDF10L RSCAN0.CFDF10.UINT16[L]
#define RSCAN0CFDF10LL RSCAN0.CFDF10.UINT8[LL]
#define RSCAN0CFDF10LH RSCAN0.CFDF10.UINT8[LH]
#define RSCAN0CFDF10H RSCAN0.CFDF10.UINT16[H]
#define RSCAN0CFDF10HL RSCAN0.CFDF10.UINT8[HL]
#define RSCAN0CFDF10HH RSCAN0.CFDF10.UINT8[HH]
#define RSCAN0CFID1 RSCAN0.CFID1.UINT32
#define RSCAN0CFID1L RSCAN0.CFID1.UINT16[L]
#define RSCAN0CFID1LL RSCAN0.CFID1.UINT8[LL]
#define RSCAN0CFID1LH RSCAN0.CFID1.UINT8[LH]
#define RSCAN0CFID1H RSCAN0.CFID1.UINT16[H]
#define RSCAN0CFID1HL RSCAN0.CFID1.UINT8[HL]
#define RSCAN0CFID1HH RSCAN0.CFID1.UINT8[HH]
#define RSCAN0CFPTR1 RSCAN0.CFPTR1.UINT32
#define RSCAN0CFPTR1L RSCAN0.CFPTR1.UINT16[L]
#define RSCAN0CFPTR1LL RSCAN0.CFPTR1.UINT8[LL]
#define RSCAN0CFPTR1LH RSCAN0.CFPTR1.UINT8[LH]
#define RSCAN0CFPTR1H RSCAN0.CFPTR1.UINT16[H]
#define RSCAN0CFPTR1HL RSCAN0.CFPTR1.UINT8[HL]
#define RSCAN0CFPTR1HH RSCAN0.CFPTR1.UINT8[HH]
#define RSCAN0CFDF01 RSCAN0.CFDF01.UINT32
#define RSCAN0CFDF01L RSCAN0.CFDF01.UINT16[L]
#define RSCAN0CFDF01LL RSCAN0.CFDF01.UINT8[LL]
#define RSCAN0CFDF01LH RSCAN0.CFDF01.UINT8[LH]
#define RSCAN0CFDF01H RSCAN0.CFDF01.UINT16[H]
#define RSCAN0CFDF01HL RSCAN0.CFDF01.UINT8[HL]
#define RSCAN0CFDF01HH RSCAN0.CFDF01.UINT8[HH]
#define RSCAN0CFDF11 RSCAN0.CFDF11.UINT32
#define RSCAN0CFDF11L RSCAN0.CFDF11.UINT16[L]
#define RSCAN0CFDF11LL RSCAN0.CFDF11.UINT8[LL]
#define RSCAN0CFDF11LH RSCAN0.CFDF11.UINT8[LH]
#define RSCAN0CFDF11H RSCAN0.CFDF11.UINT16[H]
#define RSCAN0CFDF11HL RSCAN0.CFDF11.UINT8[HL]
#define RSCAN0CFDF11HH RSCAN0.CFDF11.UINT8[HH]
#define RSCAN0CFID2 RSCAN0.CFID2.UINT32
#define RSCAN0CFID2L RSCAN0.CFID2.UINT16[L]
#define RSCAN0CFID2LL RSCAN0.CFID2.UINT8[LL]
#define RSCAN0CFID2LH RSCAN0.CFID2.UINT8[LH]
#define RSCAN0CFID2H RSCAN0.CFID2.UINT16[H]
#define RSCAN0CFID2HL RSCAN0.CFID2.UINT8[HL]
#define RSCAN0CFID2HH RSCAN0.CFID2.UINT8[HH]
#define RSCAN0CFPTR2 RSCAN0.CFPTR2.UINT32
#define RSCAN0CFPTR2L RSCAN0.CFPTR2.UINT16[L]
#define RSCAN0CFPTR2LL RSCAN0.CFPTR2.UINT8[LL]
#define RSCAN0CFPTR2LH RSCAN0.CFPTR2.UINT8[LH]
#define RSCAN0CFPTR2H RSCAN0.CFPTR2.UINT16[H]
#define RSCAN0CFPTR2HL RSCAN0.CFPTR2.UINT8[HL]
#define RSCAN0CFPTR2HH RSCAN0.CFPTR2.UINT8[HH]
#define RSCAN0CFDF02 RSCAN0.CFDF02.UINT32
#define RSCAN0CFDF02L RSCAN0.CFDF02.UINT16[L]
#define RSCAN0CFDF02LL RSCAN0.CFDF02.UINT8[LL]
#define RSCAN0CFDF02LH RSCAN0.CFDF02.UINT8[LH]
#define RSCAN0CFDF02H RSCAN0.CFDF02.UINT16[H]
#define RSCAN0CFDF02HL RSCAN0.CFDF02.UINT8[HL]
#define RSCAN0CFDF02HH RSCAN0.CFDF02.UINT8[HH]
#define RSCAN0CFDF12 RSCAN0.CFDF12.UINT32
#define RSCAN0CFDF12L RSCAN0.CFDF12.UINT16[L]
#define RSCAN0CFDF12LL RSCAN0.CFDF12.UINT8[LL]
#define RSCAN0CFDF12LH RSCAN0.CFDF12.UINT8[LH]
#define RSCAN0CFDF12H RSCAN0.CFDF12.UINT16[H]
#define RSCAN0CFDF12HL RSCAN0.CFDF12.UINT8[HL]
#define RSCAN0CFDF12HH RSCAN0.CFDF12.UINT8[HH]
#define RSCAN0CFID3 RSCAN0.CFID3.UINT32
#define RSCAN0CFID3L RSCAN0.CFID3.UINT16[L]
#define RSCAN0CFID3LL RSCAN0.CFID3.UINT8[LL]
#define RSCAN0CFID3LH RSCAN0.CFID3.UINT8[LH]
#define RSCAN0CFID3H RSCAN0.CFID3.UINT16[H]
#define RSCAN0CFID3HL RSCAN0.CFID3.UINT8[HL]
#define RSCAN0CFID3HH RSCAN0.CFID3.UINT8[HH]
#define RSCAN0CFPTR3 RSCAN0.CFPTR3.UINT32
#define RSCAN0CFPTR3L RSCAN0.CFPTR3.UINT16[L]
#define RSCAN0CFPTR3LL RSCAN0.CFPTR3.UINT8[LL]
#define RSCAN0CFPTR3LH RSCAN0.CFPTR3.UINT8[LH]
#define RSCAN0CFPTR3H RSCAN0.CFPTR3.UINT16[H]
#define RSCAN0CFPTR3HL RSCAN0.CFPTR3.UINT8[HL]
#define RSCAN0CFPTR3HH RSCAN0.CFPTR3.UINT8[HH]
#define RSCAN0CFDF03 RSCAN0.CFDF03.UINT32
#define RSCAN0CFDF03L RSCAN0.CFDF03.UINT16[L]
#define RSCAN0CFDF03LL RSCAN0.CFDF03.UINT8[LL]
#define RSCAN0CFDF03LH RSCAN0.CFDF03.UINT8[LH]
#define RSCAN0CFDF03H RSCAN0.CFDF03.UINT16[H]
#define RSCAN0CFDF03HL RSCAN0.CFDF03.UINT8[HL]
#define RSCAN0CFDF03HH RSCAN0.CFDF03.UINT8[HH]
#define RSCAN0CFDF13 RSCAN0.CFDF13.UINT32
#define RSCAN0CFDF13L RSCAN0.CFDF13.UINT16[L]
#define RSCAN0CFDF13LL RSCAN0.CFDF13.UINT8[LL]
#define RSCAN0CFDF13LH RSCAN0.CFDF13.UINT8[LH]
#define RSCAN0CFDF13H RSCAN0.CFDF13.UINT16[H]
#define RSCAN0CFDF13HL RSCAN0.CFDF13.UINT8[HL]
#define RSCAN0CFDF13HH RSCAN0.CFDF13.UINT8[HH]
#define RSCAN0CFID4 RSCAN0.CFID4.UINT32
#define RSCAN0CFID4L RSCAN0.CFID4.UINT16[L]
#define RSCAN0CFID4LL RSCAN0.CFID4.UINT8[LL]
#define RSCAN0CFID4LH RSCAN0.CFID4.UINT8[LH]
#define RSCAN0CFID4H RSCAN0.CFID4.UINT16[H]
#define RSCAN0CFID4HL RSCAN0.CFID4.UINT8[HL]
#define RSCAN0CFID4HH RSCAN0.CFID4.UINT8[HH]
#define RSCAN0CFPTR4 RSCAN0.CFPTR4.UINT32
#define RSCAN0CFPTR4L RSCAN0.CFPTR4.UINT16[L]
#define RSCAN0CFPTR4LL RSCAN0.CFPTR4.UINT8[LL]
#define RSCAN0CFPTR4LH RSCAN0.CFPTR4.UINT8[LH]
#define RSCAN0CFPTR4H RSCAN0.CFPTR4.UINT16[H]
#define RSCAN0CFPTR4HL RSCAN0.CFPTR4.UINT8[HL]
#define RSCAN0CFPTR4HH RSCAN0.CFPTR4.UINT8[HH]
#define RSCAN0CFDF04 RSCAN0.CFDF04.UINT32
#define RSCAN0CFDF04L RSCAN0.CFDF04.UINT16[L]
#define RSCAN0CFDF04LL RSCAN0.CFDF04.UINT8[LL]
#define RSCAN0CFDF04LH RSCAN0.CFDF04.UINT8[LH]
#define RSCAN0CFDF04H RSCAN0.CFDF04.UINT16[H]
#define RSCAN0CFDF04HL RSCAN0.CFDF04.UINT8[HL]
#define RSCAN0CFDF04HH RSCAN0.CFDF04.UINT8[HH]
#define RSCAN0CFDF14 RSCAN0.CFDF14.UINT32
#define RSCAN0CFDF14L RSCAN0.CFDF14.UINT16[L]
#define RSCAN0CFDF14LL RSCAN0.CFDF14.UINT8[LL]
#define RSCAN0CFDF14LH RSCAN0.CFDF14.UINT8[LH]
#define RSCAN0CFDF14H RSCAN0.CFDF14.UINT16[H]
#define RSCAN0CFDF14HL RSCAN0.CFDF14.UINT8[HL]
#define RSCAN0CFDF14HH RSCAN0.CFDF14.UINT8[HH]
#define RSCAN0CFID5 RSCAN0.CFID5.UINT32
#define RSCAN0CFID5L RSCAN0.CFID5.UINT16[L]
#define RSCAN0CFID5LL RSCAN0.CFID5.UINT8[LL]
#define RSCAN0CFID5LH RSCAN0.CFID5.UINT8[LH]
#define RSCAN0CFID5H RSCAN0.CFID5.UINT16[H]
#define RSCAN0CFID5HL RSCAN0.CFID5.UINT8[HL]
#define RSCAN0CFID5HH RSCAN0.CFID5.UINT8[HH]
#define RSCAN0CFPTR5 RSCAN0.CFPTR5.UINT32
#define RSCAN0CFPTR5L RSCAN0.CFPTR5.UINT16[L]
#define RSCAN0CFPTR5LL RSCAN0.CFPTR5.UINT8[LL]
#define RSCAN0CFPTR5LH RSCAN0.CFPTR5.UINT8[LH]
#define RSCAN0CFPTR5H RSCAN0.CFPTR5.UINT16[H]
#define RSCAN0CFPTR5HL RSCAN0.CFPTR5.UINT8[HL]
#define RSCAN0CFPTR5HH RSCAN0.CFPTR5.UINT8[HH]
#define RSCAN0CFDF05 RSCAN0.CFDF05.UINT32
#define RSCAN0CFDF05L RSCAN0.CFDF05.UINT16[L]
#define RSCAN0CFDF05LL RSCAN0.CFDF05.UINT8[LL]
#define RSCAN0CFDF05LH RSCAN0.CFDF05.UINT8[LH]
#define RSCAN0CFDF05H RSCAN0.CFDF05.UINT16[H]
#define RSCAN0CFDF05HL RSCAN0.CFDF05.UINT8[HL]
#define RSCAN0CFDF05HH RSCAN0.CFDF05.UINT8[HH]
#define RSCAN0CFDF15 RSCAN0.CFDF15.UINT32
#define RSCAN0CFDF15L RSCAN0.CFDF15.UINT16[L]
#define RSCAN0CFDF15LL RSCAN0.CFDF15.UINT8[LL]
#define RSCAN0CFDF15LH RSCAN0.CFDF15.UINT8[LH]
#define RSCAN0CFDF15H RSCAN0.CFDF15.UINT16[H]
#define RSCAN0CFDF15HL RSCAN0.CFDF15.UINT8[HL]
#define RSCAN0CFDF15HH RSCAN0.CFDF15.UINT8[HH]
#define RSCAN0CFID6 RSCAN0.CFID6.UINT32
#define RSCAN0CFID6L RSCAN0.CFID6.UINT16[L]
#define RSCAN0CFID6LL RSCAN0.CFID6.UINT8[LL]
#define RSCAN0CFID6LH RSCAN0.CFID6.UINT8[LH]
#define RSCAN0CFID6H RSCAN0.CFID6.UINT16[H]
#define RSCAN0CFID6HL RSCAN0.CFID6.UINT8[HL]
#define RSCAN0CFID6HH RSCAN0.CFID6.UINT8[HH]
#define RSCAN0CFPTR6 RSCAN0.CFPTR6.UINT32
#define RSCAN0CFPTR6L RSCAN0.CFPTR6.UINT16[L]
#define RSCAN0CFPTR6LL RSCAN0.CFPTR6.UINT8[LL]
#define RSCAN0CFPTR6LH RSCAN0.CFPTR6.UINT8[LH]
#define RSCAN0CFPTR6H RSCAN0.CFPTR6.UINT16[H]
#define RSCAN0CFPTR6HL RSCAN0.CFPTR6.UINT8[HL]
#define RSCAN0CFPTR6HH RSCAN0.CFPTR6.UINT8[HH]
#define RSCAN0CFDF06 RSCAN0.CFDF06.UINT32
#define RSCAN0CFDF06L RSCAN0.CFDF06.UINT16[L]
#define RSCAN0CFDF06LL RSCAN0.CFDF06.UINT8[LL]
#define RSCAN0CFDF06LH RSCAN0.CFDF06.UINT8[LH]
#define RSCAN0CFDF06H RSCAN0.CFDF06.UINT16[H]
#define RSCAN0CFDF06HL RSCAN0.CFDF06.UINT8[HL]
#define RSCAN0CFDF06HH RSCAN0.CFDF06.UINT8[HH]
#define RSCAN0CFDF16 RSCAN0.CFDF16.UINT32
#define RSCAN0CFDF16L RSCAN0.CFDF16.UINT16[L]
#define RSCAN0CFDF16LL RSCAN0.CFDF16.UINT8[LL]
#define RSCAN0CFDF16LH RSCAN0.CFDF16.UINT8[LH]
#define RSCAN0CFDF16H RSCAN0.CFDF16.UINT16[H]
#define RSCAN0CFDF16HL RSCAN0.CFDF16.UINT8[HL]
#define RSCAN0CFDF16HH RSCAN0.CFDF16.UINT8[HH]
#define RSCAN0CFID7 RSCAN0.CFID7.UINT32
#define RSCAN0CFID7L RSCAN0.CFID7.UINT16[L]
#define RSCAN0CFID7LL RSCAN0.CFID7.UINT8[LL]
#define RSCAN0CFID7LH RSCAN0.CFID7.UINT8[LH]
#define RSCAN0CFID7H RSCAN0.CFID7.UINT16[H]
#define RSCAN0CFID7HL RSCAN0.CFID7.UINT8[HL]
#define RSCAN0CFID7HH RSCAN0.CFID7.UINT8[HH]
#define RSCAN0CFPTR7 RSCAN0.CFPTR7.UINT32
#define RSCAN0CFPTR7L RSCAN0.CFPTR7.UINT16[L]
#define RSCAN0CFPTR7LL RSCAN0.CFPTR7.UINT8[LL]
#define RSCAN0CFPTR7LH RSCAN0.CFPTR7.UINT8[LH]
#define RSCAN0CFPTR7H RSCAN0.CFPTR7.UINT16[H]
#define RSCAN0CFPTR7HL RSCAN0.CFPTR7.UINT8[HL]
#define RSCAN0CFPTR7HH RSCAN0.CFPTR7.UINT8[HH]
#define RSCAN0CFDF07 RSCAN0.CFDF07.UINT32
#define RSCAN0CFDF07L RSCAN0.CFDF07.UINT16[L]
#define RSCAN0CFDF07LL RSCAN0.CFDF07.UINT8[LL]
#define RSCAN0CFDF07LH RSCAN0.CFDF07.UINT8[LH]
#define RSCAN0CFDF07H RSCAN0.CFDF07.UINT16[H]
#define RSCAN0CFDF07HL RSCAN0.CFDF07.UINT8[HL]
#define RSCAN0CFDF07HH RSCAN0.CFDF07.UINT8[HH]
#define RSCAN0CFDF17 RSCAN0.CFDF17.UINT32
#define RSCAN0CFDF17L RSCAN0.CFDF17.UINT16[L]
#define RSCAN0CFDF17LL RSCAN0.CFDF17.UINT8[LL]
#define RSCAN0CFDF17LH RSCAN0.CFDF17.UINT8[LH]
#define RSCAN0CFDF17H RSCAN0.CFDF17.UINT16[H]
#define RSCAN0CFDF17HL RSCAN0.CFDF17.UINT8[HL]
#define RSCAN0CFDF17HH RSCAN0.CFDF17.UINT8[HH]
#define RSCAN0CFID8 RSCAN0.CFID8.UINT32
#define RSCAN0CFID8L RSCAN0.CFID8.UINT16[L]
#define RSCAN0CFID8LL RSCAN0.CFID8.UINT8[LL]
#define RSCAN0CFID8LH RSCAN0.CFID8.UINT8[LH]
#define RSCAN0CFID8H RSCAN0.CFID8.UINT16[H]
#define RSCAN0CFID8HL RSCAN0.CFID8.UINT8[HL]
#define RSCAN0CFID8HH RSCAN0.CFID8.UINT8[HH]
#define RSCAN0CFPTR8 RSCAN0.CFPTR8.UINT32
#define RSCAN0CFPTR8L RSCAN0.CFPTR8.UINT16[L]
#define RSCAN0CFPTR8LL RSCAN0.CFPTR8.UINT8[LL]
#define RSCAN0CFPTR8LH RSCAN0.CFPTR8.UINT8[LH]
#define RSCAN0CFPTR8H RSCAN0.CFPTR8.UINT16[H]
#define RSCAN0CFPTR8HL RSCAN0.CFPTR8.UINT8[HL]
#define RSCAN0CFPTR8HH RSCAN0.CFPTR8.UINT8[HH]
#define RSCAN0CFDF08 RSCAN0.CFDF08.UINT32
#define RSCAN0CFDF08L RSCAN0.CFDF08.UINT16[L]
#define RSCAN0CFDF08LL RSCAN0.CFDF08.UINT8[LL]
#define RSCAN0CFDF08LH RSCAN0.CFDF08.UINT8[LH]
#define RSCAN0CFDF08H RSCAN0.CFDF08.UINT16[H]
#define RSCAN0CFDF08HL RSCAN0.CFDF08.UINT8[HL]
#define RSCAN0CFDF08HH RSCAN0.CFDF08.UINT8[HH]
#define RSCAN0CFDF18 RSCAN0.CFDF18.UINT32
#define RSCAN0CFDF18L RSCAN0.CFDF18.UINT16[L]
#define RSCAN0CFDF18LL RSCAN0.CFDF18.UINT8[LL]
#define RSCAN0CFDF18LH RSCAN0.CFDF18.UINT8[LH]
#define RSCAN0CFDF18H RSCAN0.CFDF18.UINT16[H]
#define RSCAN0CFDF18HL RSCAN0.CFDF18.UINT8[HL]
#define RSCAN0CFDF18HH RSCAN0.CFDF18.UINT8[HH]
#define RSCAN0CFID9 RSCAN0.CFID9.UINT32
#define RSCAN0CFID9L RSCAN0.CFID9.UINT16[L]
#define RSCAN0CFID9LL RSCAN0.CFID9.UINT8[LL]
#define RSCAN0CFID9LH RSCAN0.CFID9.UINT8[LH]
#define RSCAN0CFID9H RSCAN0.CFID9.UINT16[H]
#define RSCAN0CFID9HL RSCAN0.CFID9.UINT8[HL]
#define RSCAN0CFID9HH RSCAN0.CFID9.UINT8[HH]
#define RSCAN0CFPTR9 RSCAN0.CFPTR9.UINT32
#define RSCAN0CFPTR9L RSCAN0.CFPTR9.UINT16[L]
#define RSCAN0CFPTR9LL RSCAN0.CFPTR9.UINT8[LL]
#define RSCAN0CFPTR9LH RSCAN0.CFPTR9.UINT8[LH]
#define RSCAN0CFPTR9H RSCAN0.CFPTR9.UINT16[H]
#define RSCAN0CFPTR9HL RSCAN0.CFPTR9.UINT8[HL]
#define RSCAN0CFPTR9HH RSCAN0.CFPTR9.UINT8[HH]
#define RSCAN0CFDF09 RSCAN0.CFDF09.UINT32
#define RSCAN0CFDF09L RSCAN0.CFDF09.UINT16[L]
#define RSCAN0CFDF09LL RSCAN0.CFDF09.UINT8[LL]
#define RSCAN0CFDF09LH RSCAN0.CFDF09.UINT8[LH]
#define RSCAN0CFDF09H RSCAN0.CFDF09.UINT16[H]
#define RSCAN0CFDF09HL RSCAN0.CFDF09.UINT8[HL]
#define RSCAN0CFDF09HH RSCAN0.CFDF09.UINT8[HH]
#define RSCAN0CFDF19 RSCAN0.CFDF19.UINT32
#define RSCAN0CFDF19L RSCAN0.CFDF19.UINT16[L]
#define RSCAN0CFDF19LL RSCAN0.CFDF19.UINT8[LL]
#define RSCAN0CFDF19LH RSCAN0.CFDF19.UINT8[LH]
#define RSCAN0CFDF19H RSCAN0.CFDF19.UINT16[H]
#define RSCAN0CFDF19HL RSCAN0.CFDF19.UINT8[HL]
#define RSCAN0CFDF19HH RSCAN0.CFDF19.UINT8[HH]
#define RSCAN0CFID10 RSCAN0.CFID10.UINT32
#define RSCAN0CFID10L RSCAN0.CFID10.UINT16[L]
#define RSCAN0CFID10LL RSCAN0.CFID10.UINT8[LL]
#define RSCAN0CFID10LH RSCAN0.CFID10.UINT8[LH]
#define RSCAN0CFID10H RSCAN0.CFID10.UINT16[H]
#define RSCAN0CFID10HL RSCAN0.CFID10.UINT8[HL]
#define RSCAN0CFID10HH RSCAN0.CFID10.UINT8[HH]
#define RSCAN0CFPTR10 RSCAN0.CFPTR10.UINT32
#define RSCAN0CFPTR10L RSCAN0.CFPTR10.UINT16[L]
#define RSCAN0CFPTR10LL RSCAN0.CFPTR10.UINT8[LL]
#define RSCAN0CFPTR10LH RSCAN0.CFPTR10.UINT8[LH]
#define RSCAN0CFPTR10H RSCAN0.CFPTR10.UINT16[H]
#define RSCAN0CFPTR10HL RSCAN0.CFPTR10.UINT8[HL]
#define RSCAN0CFPTR10HH RSCAN0.CFPTR10.UINT8[HH]
#define RSCAN0CFDF010 RSCAN0.CFDF010.UINT32
#define RSCAN0CFDF010L RSCAN0.CFDF010.UINT16[L]
#define RSCAN0CFDF010LL RSCAN0.CFDF010.UINT8[LL]
#define RSCAN0CFDF010LH RSCAN0.CFDF010.UINT8[LH]
#define RSCAN0CFDF010H RSCAN0.CFDF010.UINT16[H]
#define RSCAN0CFDF010HL RSCAN0.CFDF010.UINT8[HL]
#define RSCAN0CFDF010HH RSCAN0.CFDF010.UINT8[HH]
#define RSCAN0CFDF110 RSCAN0.CFDF110.UINT32
#define RSCAN0CFDF110L RSCAN0.CFDF110.UINT16[L]
#define RSCAN0CFDF110LL RSCAN0.CFDF110.UINT8[LL]
#define RSCAN0CFDF110LH RSCAN0.CFDF110.UINT8[LH]
#define RSCAN0CFDF110H RSCAN0.CFDF110.UINT16[H]
#define RSCAN0CFDF110HL RSCAN0.CFDF110.UINT8[HL]
#define RSCAN0CFDF110HH RSCAN0.CFDF110.UINT8[HH]
#define RSCAN0CFID11 RSCAN0.CFID11.UINT32
#define RSCAN0CFID11L RSCAN0.CFID11.UINT16[L]
#define RSCAN0CFID11LL RSCAN0.CFID11.UINT8[LL]
#define RSCAN0CFID11LH RSCAN0.CFID11.UINT8[LH]
#define RSCAN0CFID11H RSCAN0.CFID11.UINT16[H]
#define RSCAN0CFID11HL RSCAN0.CFID11.UINT8[HL]
#define RSCAN0CFID11HH RSCAN0.CFID11.UINT8[HH]
#define RSCAN0CFPTR11 RSCAN0.CFPTR11.UINT32
#define RSCAN0CFPTR11L RSCAN0.CFPTR11.UINT16[L]
#define RSCAN0CFPTR11LL RSCAN0.CFPTR11.UINT8[LL]
#define RSCAN0CFPTR11LH RSCAN0.CFPTR11.UINT8[LH]
#define RSCAN0CFPTR11H RSCAN0.CFPTR11.UINT16[H]
#define RSCAN0CFPTR11HL RSCAN0.CFPTR11.UINT8[HL]
#define RSCAN0CFPTR11HH RSCAN0.CFPTR11.UINT8[HH]
#define RSCAN0CFDF011 RSCAN0.CFDF011.UINT32
#define RSCAN0CFDF011L RSCAN0.CFDF011.UINT16[L]
#define RSCAN0CFDF011LL RSCAN0.CFDF011.UINT8[LL]
#define RSCAN0CFDF011LH RSCAN0.CFDF011.UINT8[LH]
#define RSCAN0CFDF011H RSCAN0.CFDF011.UINT16[H]
#define RSCAN0CFDF011HL RSCAN0.CFDF011.UINT8[HL]
#define RSCAN0CFDF011HH RSCAN0.CFDF011.UINT8[HH]
#define RSCAN0CFDF111 RSCAN0.CFDF111.UINT32
#define RSCAN0CFDF111L RSCAN0.CFDF111.UINT16[L]
#define RSCAN0CFDF111LL RSCAN0.CFDF111.UINT8[LL]
#define RSCAN0CFDF111LH RSCAN0.CFDF111.UINT8[LH]
#define RSCAN0CFDF111H RSCAN0.CFDF111.UINT16[H]
#define RSCAN0CFDF111HL RSCAN0.CFDF111.UINT8[HL]
#define RSCAN0CFDF111HH RSCAN0.CFDF111.UINT8[HH]
#define RSCAN0CFID12 RSCAN0.CFID12.UINT32
#define RSCAN0CFID12L RSCAN0.CFID12.UINT16[L]
#define RSCAN0CFID12LL RSCAN0.CFID12.UINT8[LL]
#define RSCAN0CFID12LH RSCAN0.CFID12.UINT8[LH]
#define RSCAN0CFID12H RSCAN0.CFID12.UINT16[H]
#define RSCAN0CFID12HL RSCAN0.CFID12.UINT8[HL]
#define RSCAN0CFID12HH RSCAN0.CFID12.UINT8[HH]
#define RSCAN0CFPTR12 RSCAN0.CFPTR12.UINT32
#define RSCAN0CFPTR12L RSCAN0.CFPTR12.UINT16[L]
#define RSCAN0CFPTR12LL RSCAN0.CFPTR12.UINT8[LL]
#define RSCAN0CFPTR12LH RSCAN0.CFPTR12.UINT8[LH]
#define RSCAN0CFPTR12H RSCAN0.CFPTR12.UINT16[H]
#define RSCAN0CFPTR12HL RSCAN0.CFPTR12.UINT8[HL]
#define RSCAN0CFPTR12HH RSCAN0.CFPTR12.UINT8[HH]
#define RSCAN0CFDF012 RSCAN0.CFDF012.UINT32
#define RSCAN0CFDF012L RSCAN0.CFDF012.UINT16[L]
#define RSCAN0CFDF012LL RSCAN0.CFDF012.UINT8[LL]
#define RSCAN0CFDF012LH RSCAN0.CFDF012.UINT8[LH]
#define RSCAN0CFDF012H RSCAN0.CFDF012.UINT16[H]
#define RSCAN0CFDF012HL RSCAN0.CFDF012.UINT8[HL]
#define RSCAN0CFDF012HH RSCAN0.CFDF012.UINT8[HH]
#define RSCAN0CFDF112 RSCAN0.CFDF112.UINT32
#define RSCAN0CFDF112L RSCAN0.CFDF112.UINT16[L]
#define RSCAN0CFDF112LL RSCAN0.CFDF112.UINT8[LL]
#define RSCAN0CFDF112LH RSCAN0.CFDF112.UINT8[LH]
#define RSCAN0CFDF112H RSCAN0.CFDF112.UINT16[H]
#define RSCAN0CFDF112HL RSCAN0.CFDF112.UINT8[HL]
#define RSCAN0CFDF112HH RSCAN0.CFDF112.UINT8[HH]
#define RSCAN0CFID13 RSCAN0.CFID13.UINT32
#define RSCAN0CFID13L RSCAN0.CFID13.UINT16[L]
#define RSCAN0CFID13LL RSCAN0.CFID13.UINT8[LL]
#define RSCAN0CFID13LH RSCAN0.CFID13.UINT8[LH]
#define RSCAN0CFID13H RSCAN0.CFID13.UINT16[H]
#define RSCAN0CFID13HL RSCAN0.CFID13.UINT8[HL]
#define RSCAN0CFID13HH RSCAN0.CFID13.UINT8[HH]
#define RSCAN0CFPTR13 RSCAN0.CFPTR13.UINT32
#define RSCAN0CFPTR13L RSCAN0.CFPTR13.UINT16[L]
#define RSCAN0CFPTR13LL RSCAN0.CFPTR13.UINT8[LL]
#define RSCAN0CFPTR13LH RSCAN0.CFPTR13.UINT8[LH]
#define RSCAN0CFPTR13H RSCAN0.CFPTR13.UINT16[H]
#define RSCAN0CFPTR13HL RSCAN0.CFPTR13.UINT8[HL]
#define RSCAN0CFPTR13HH RSCAN0.CFPTR13.UINT8[HH]
#define RSCAN0CFDF013 RSCAN0.CFDF013.UINT32
#define RSCAN0CFDF013L RSCAN0.CFDF013.UINT16[L]
#define RSCAN0CFDF013LL RSCAN0.CFDF013.UINT8[LL]
#define RSCAN0CFDF013LH RSCAN0.CFDF013.UINT8[LH]
#define RSCAN0CFDF013H RSCAN0.CFDF013.UINT16[H]
#define RSCAN0CFDF013HL RSCAN0.CFDF013.UINT8[HL]
#define RSCAN0CFDF013HH RSCAN0.CFDF013.UINT8[HH]
#define RSCAN0CFDF113 RSCAN0.CFDF113.UINT32
#define RSCAN0CFDF113L RSCAN0.CFDF113.UINT16[L]
#define RSCAN0CFDF113LL RSCAN0.CFDF113.UINT8[LL]
#define RSCAN0CFDF113LH RSCAN0.CFDF113.UINT8[LH]
#define RSCAN0CFDF113H RSCAN0.CFDF113.UINT16[H]
#define RSCAN0CFDF113HL RSCAN0.CFDF113.UINT8[HL]
#define RSCAN0CFDF113HH RSCAN0.CFDF113.UINT8[HH]
#define RSCAN0CFID14 RSCAN0.CFID14.UINT32
#define RSCAN0CFID14L RSCAN0.CFID14.UINT16[L]
#define RSCAN0CFID14LL RSCAN0.CFID14.UINT8[LL]
#define RSCAN0CFID14LH RSCAN0.CFID14.UINT8[LH]
#define RSCAN0CFID14H RSCAN0.CFID14.UINT16[H]
#define RSCAN0CFID14HL RSCAN0.CFID14.UINT8[HL]
#define RSCAN0CFID14HH RSCAN0.CFID14.UINT8[HH]
#define RSCAN0CFPTR14 RSCAN0.CFPTR14.UINT32
#define RSCAN0CFPTR14L RSCAN0.CFPTR14.UINT16[L]
#define RSCAN0CFPTR14LL RSCAN0.CFPTR14.UINT8[LL]
#define RSCAN0CFPTR14LH RSCAN0.CFPTR14.UINT8[LH]
#define RSCAN0CFPTR14H RSCAN0.CFPTR14.UINT16[H]
#define RSCAN0CFPTR14HL RSCAN0.CFPTR14.UINT8[HL]
#define RSCAN0CFPTR14HH RSCAN0.CFPTR14.UINT8[HH]
#define RSCAN0CFDF014 RSCAN0.CFDF014.UINT32
#define RSCAN0CFDF014L RSCAN0.CFDF014.UINT16[L]
#define RSCAN0CFDF014LL RSCAN0.CFDF014.UINT8[LL]
#define RSCAN0CFDF014LH RSCAN0.CFDF014.UINT8[LH]
#define RSCAN0CFDF014H RSCAN0.CFDF014.UINT16[H]
#define RSCAN0CFDF014HL RSCAN0.CFDF014.UINT8[HL]
#define RSCAN0CFDF014HH RSCAN0.CFDF014.UINT8[HH]
#define RSCAN0CFDF114 RSCAN0.CFDF114.UINT32
#define RSCAN0CFDF114L RSCAN0.CFDF114.UINT16[L]
#define RSCAN0CFDF114LL RSCAN0.CFDF114.UINT8[LL]
#define RSCAN0CFDF114LH RSCAN0.CFDF114.UINT8[LH]
#define RSCAN0CFDF114H RSCAN0.CFDF114.UINT16[H]
#define RSCAN0CFDF114HL RSCAN0.CFDF114.UINT8[HL]
#define RSCAN0CFDF114HH RSCAN0.CFDF114.UINT8[HH]
#define RSCAN0TMID0 RSCAN0.TMID0.UINT32
#define RSCAN0TMID0L RSCAN0.TMID0.UINT16[L]
#define RSCAN0TMID0LL RSCAN0.TMID0.UINT8[LL]
#define RSCAN0TMID0LH RSCAN0.TMID0.UINT8[LH]
#define RSCAN0TMID0H RSCAN0.TMID0.UINT16[H]
#define RSCAN0TMID0HL RSCAN0.TMID0.UINT8[HL]
#define RSCAN0TMID0HH RSCAN0.TMID0.UINT8[HH]
#define RSCAN0TMPTR0 RSCAN0.TMPTR0.UINT32
#define RSCAN0TMPTR0L RSCAN0.TMPTR0.UINT16[L]
#define RSCAN0TMPTR0LL RSCAN0.TMPTR0.UINT8[LL]
#define RSCAN0TMPTR0LH RSCAN0.TMPTR0.UINT8[LH]
#define RSCAN0TMPTR0H RSCAN0.TMPTR0.UINT16[H]
#define RSCAN0TMPTR0HL RSCAN0.TMPTR0.UINT8[HL]
#define RSCAN0TMPTR0HH RSCAN0.TMPTR0.UINT8[HH]
#define RSCAN0TMDF00 RSCAN0.TMDF00.UINT32
#define RSCAN0TMDF00L RSCAN0.TMDF00.UINT16[L]
#define RSCAN0TMDF00LL RSCAN0.TMDF00.UINT8[LL]
#define RSCAN0TMDF00LH RSCAN0.TMDF00.UINT8[LH]
#define RSCAN0TMDF00H RSCAN0.TMDF00.UINT16[H]
#define RSCAN0TMDF00HL RSCAN0.TMDF00.UINT8[HL]
#define RSCAN0TMDF00HH RSCAN0.TMDF00.UINT8[HH]
#define RSCAN0TMDF10 RSCAN0.TMDF10.UINT32
#define RSCAN0TMDF10L RSCAN0.TMDF10.UINT16[L]
#define RSCAN0TMDF10LL RSCAN0.TMDF10.UINT8[LL]
#define RSCAN0TMDF10LH RSCAN0.TMDF10.UINT8[LH]
#define RSCAN0TMDF10H RSCAN0.TMDF10.UINT16[H]
#define RSCAN0TMDF10HL RSCAN0.TMDF10.UINT8[HL]
#define RSCAN0TMDF10HH RSCAN0.TMDF10.UINT8[HH]
#define RSCAN0TMID1 RSCAN0.TMID1.UINT32
#define RSCAN0TMID1L RSCAN0.TMID1.UINT16[L]
#define RSCAN0TMID1LL RSCAN0.TMID1.UINT8[LL]
#define RSCAN0TMID1LH RSCAN0.TMID1.UINT8[LH]
#define RSCAN0TMID1H RSCAN0.TMID1.UINT16[H]
#define RSCAN0TMID1HL RSCAN0.TMID1.UINT8[HL]
#define RSCAN0TMID1HH RSCAN0.TMID1.UINT8[HH]
#define RSCAN0TMPTR1 RSCAN0.TMPTR1.UINT32
#define RSCAN0TMPTR1L RSCAN0.TMPTR1.UINT16[L]
#define RSCAN0TMPTR1LL RSCAN0.TMPTR1.UINT8[LL]
#define RSCAN0TMPTR1LH RSCAN0.TMPTR1.UINT8[LH]
#define RSCAN0TMPTR1H RSCAN0.TMPTR1.UINT16[H]
#define RSCAN0TMPTR1HL RSCAN0.TMPTR1.UINT8[HL]
#define RSCAN0TMPTR1HH RSCAN0.TMPTR1.UINT8[HH]
#define RSCAN0TMDF01 RSCAN0.TMDF01.UINT32
#define RSCAN0TMDF01L RSCAN0.TMDF01.UINT16[L]
#define RSCAN0TMDF01LL RSCAN0.TMDF01.UINT8[LL]
#define RSCAN0TMDF01LH RSCAN0.TMDF01.UINT8[LH]
#define RSCAN0TMDF01H RSCAN0.TMDF01.UINT16[H]
#define RSCAN0TMDF01HL RSCAN0.TMDF01.UINT8[HL]
#define RSCAN0TMDF01HH RSCAN0.TMDF01.UINT8[HH]
#define RSCAN0TMDF11 RSCAN0.TMDF11.UINT32
#define RSCAN0TMDF11L RSCAN0.TMDF11.UINT16[L]
#define RSCAN0TMDF11LL RSCAN0.TMDF11.UINT8[LL]
#define RSCAN0TMDF11LH RSCAN0.TMDF11.UINT8[LH]
#define RSCAN0TMDF11H RSCAN0.TMDF11.UINT16[H]
#define RSCAN0TMDF11HL RSCAN0.TMDF11.UINT8[HL]
#define RSCAN0TMDF11HH RSCAN0.TMDF11.UINT8[HH]
#define RSCAN0TMID2 RSCAN0.TMID2.UINT32
#define RSCAN0TMID2L RSCAN0.TMID2.UINT16[L]
#define RSCAN0TMID2LL RSCAN0.TMID2.UINT8[LL]
#define RSCAN0TMID2LH RSCAN0.TMID2.UINT8[LH]
#define RSCAN0TMID2H RSCAN0.TMID2.UINT16[H]
#define RSCAN0TMID2HL RSCAN0.TMID2.UINT8[HL]
#define RSCAN0TMID2HH RSCAN0.TMID2.UINT8[HH]
#define RSCAN0TMPTR2 RSCAN0.TMPTR2.UINT32
#define RSCAN0TMPTR2L RSCAN0.TMPTR2.UINT16[L]
#define RSCAN0TMPTR2LL RSCAN0.TMPTR2.UINT8[LL]
#define RSCAN0TMPTR2LH RSCAN0.TMPTR2.UINT8[LH]
#define RSCAN0TMPTR2H RSCAN0.TMPTR2.UINT16[H]
#define RSCAN0TMPTR2HL RSCAN0.TMPTR2.UINT8[HL]
#define RSCAN0TMPTR2HH RSCAN0.TMPTR2.UINT8[HH]
#define RSCAN0TMDF02 RSCAN0.TMDF02.UINT32
#define RSCAN0TMDF02L RSCAN0.TMDF02.UINT16[L]
#define RSCAN0TMDF02LL RSCAN0.TMDF02.UINT8[LL]
#define RSCAN0TMDF02LH RSCAN0.TMDF02.UINT8[LH]
#define RSCAN0TMDF02H RSCAN0.TMDF02.UINT16[H]
#define RSCAN0TMDF02HL RSCAN0.TMDF02.UINT8[HL]
#define RSCAN0TMDF02HH RSCAN0.TMDF02.UINT8[HH]
#define RSCAN0TMDF12 RSCAN0.TMDF12.UINT32
#define RSCAN0TMDF12L RSCAN0.TMDF12.UINT16[L]
#define RSCAN0TMDF12LL RSCAN0.TMDF12.UINT8[LL]
#define RSCAN0TMDF12LH RSCAN0.TMDF12.UINT8[LH]
#define RSCAN0TMDF12H RSCAN0.TMDF12.UINT16[H]
#define RSCAN0TMDF12HL RSCAN0.TMDF12.UINT8[HL]
#define RSCAN0TMDF12HH RSCAN0.TMDF12.UINT8[HH]
#define RSCAN0TMID3 RSCAN0.TMID3.UINT32
#define RSCAN0TMID3L RSCAN0.TMID3.UINT16[L]
#define RSCAN0TMID3LL RSCAN0.TMID3.UINT8[LL]
#define RSCAN0TMID3LH RSCAN0.TMID3.UINT8[LH]
#define RSCAN0TMID3H RSCAN0.TMID3.UINT16[H]
#define RSCAN0TMID3HL RSCAN0.TMID3.UINT8[HL]
#define RSCAN0TMID3HH RSCAN0.TMID3.UINT8[HH]
#define RSCAN0TMPTR3 RSCAN0.TMPTR3.UINT32
#define RSCAN0TMPTR3L RSCAN0.TMPTR3.UINT16[L]
#define RSCAN0TMPTR3LL RSCAN0.TMPTR3.UINT8[LL]
#define RSCAN0TMPTR3LH RSCAN0.TMPTR3.UINT8[LH]
#define RSCAN0TMPTR3H RSCAN0.TMPTR3.UINT16[H]
#define RSCAN0TMPTR3HL RSCAN0.TMPTR3.UINT8[HL]
#define RSCAN0TMPTR3HH RSCAN0.TMPTR3.UINT8[HH]
#define RSCAN0TMDF03 RSCAN0.TMDF03.UINT32
#define RSCAN0TMDF03L RSCAN0.TMDF03.UINT16[L]
#define RSCAN0TMDF03LL RSCAN0.TMDF03.UINT8[LL]
#define RSCAN0TMDF03LH RSCAN0.TMDF03.UINT8[LH]
#define RSCAN0TMDF03H RSCAN0.TMDF03.UINT16[H]
#define RSCAN0TMDF03HL RSCAN0.TMDF03.UINT8[HL]
#define RSCAN0TMDF03HH RSCAN0.TMDF03.UINT8[HH]
#define RSCAN0TMDF13 RSCAN0.TMDF13.UINT32
#define RSCAN0TMDF13L RSCAN0.TMDF13.UINT16[L]
#define RSCAN0TMDF13LL RSCAN0.TMDF13.UINT8[LL]
#define RSCAN0TMDF13LH RSCAN0.TMDF13.UINT8[LH]
#define RSCAN0TMDF13H RSCAN0.TMDF13.UINT16[H]
#define RSCAN0TMDF13HL RSCAN0.TMDF13.UINT8[HL]
#define RSCAN0TMDF13HH RSCAN0.TMDF13.UINT8[HH]
#define RSCAN0TMID4 RSCAN0.TMID4.UINT32
#define RSCAN0TMID4L RSCAN0.TMID4.UINT16[L]
#define RSCAN0TMID4LL RSCAN0.TMID4.UINT8[LL]
#define RSCAN0TMID4LH RSCAN0.TMID4.UINT8[LH]
#define RSCAN0TMID4H RSCAN0.TMID4.UINT16[H]
#define RSCAN0TMID4HL RSCAN0.TMID4.UINT8[HL]
#define RSCAN0TMID4HH RSCAN0.TMID4.UINT8[HH]
#define RSCAN0TMPTR4 RSCAN0.TMPTR4.UINT32
#define RSCAN0TMPTR4L RSCAN0.TMPTR4.UINT16[L]
#define RSCAN0TMPTR4LL RSCAN0.TMPTR4.UINT8[LL]
#define RSCAN0TMPTR4LH RSCAN0.TMPTR4.UINT8[LH]
#define RSCAN0TMPTR4H RSCAN0.TMPTR4.UINT16[H]
#define RSCAN0TMPTR4HL RSCAN0.TMPTR4.UINT8[HL]
#define RSCAN0TMPTR4HH RSCAN0.TMPTR4.UINT8[HH]
#define RSCAN0TMDF04 RSCAN0.TMDF04.UINT32
#define RSCAN0TMDF04L RSCAN0.TMDF04.UINT16[L]
#define RSCAN0TMDF04LL RSCAN0.TMDF04.UINT8[LL]
#define RSCAN0TMDF04LH RSCAN0.TMDF04.UINT8[LH]
#define RSCAN0TMDF04H RSCAN0.TMDF04.UINT16[H]
#define RSCAN0TMDF04HL RSCAN0.TMDF04.UINT8[HL]
#define RSCAN0TMDF04HH RSCAN0.TMDF04.UINT8[HH]
#define RSCAN0TMDF14 RSCAN0.TMDF14.UINT32
#define RSCAN0TMDF14L RSCAN0.TMDF14.UINT16[L]
#define RSCAN0TMDF14LL RSCAN0.TMDF14.UINT8[LL]
#define RSCAN0TMDF14LH RSCAN0.TMDF14.UINT8[LH]
#define RSCAN0TMDF14H RSCAN0.TMDF14.UINT16[H]
#define RSCAN0TMDF14HL RSCAN0.TMDF14.UINT8[HL]
#define RSCAN0TMDF14HH RSCAN0.TMDF14.UINT8[HH]
#define RSCAN0TMID5 RSCAN0.TMID5.UINT32
#define RSCAN0TMID5L RSCAN0.TMID5.UINT16[L]
#define RSCAN0TMID5LL RSCAN0.TMID5.UINT8[LL]
#define RSCAN0TMID5LH RSCAN0.TMID5.UINT8[LH]
#define RSCAN0TMID5H RSCAN0.TMID5.UINT16[H]
#define RSCAN0TMID5HL RSCAN0.TMID5.UINT8[HL]
#define RSCAN0TMID5HH RSCAN0.TMID5.UINT8[HH]
#define RSCAN0TMPTR5 RSCAN0.TMPTR5.UINT32
#define RSCAN0TMPTR5L RSCAN0.TMPTR5.UINT16[L]
#define RSCAN0TMPTR5LL RSCAN0.TMPTR5.UINT8[LL]
#define RSCAN0TMPTR5LH RSCAN0.TMPTR5.UINT8[LH]
#define RSCAN0TMPTR5H RSCAN0.TMPTR5.UINT16[H]
#define RSCAN0TMPTR5HL RSCAN0.TMPTR5.UINT8[HL]
#define RSCAN0TMPTR5HH RSCAN0.TMPTR5.UINT8[HH]
#define RSCAN0TMDF05 RSCAN0.TMDF05.UINT32
#define RSCAN0TMDF05L RSCAN0.TMDF05.UINT16[L]
#define RSCAN0TMDF05LL RSCAN0.TMDF05.UINT8[LL]
#define RSCAN0TMDF05LH RSCAN0.TMDF05.UINT8[LH]
#define RSCAN0TMDF05H RSCAN0.TMDF05.UINT16[H]
#define RSCAN0TMDF05HL RSCAN0.TMDF05.UINT8[HL]
#define RSCAN0TMDF05HH RSCAN0.TMDF05.UINT8[HH]
#define RSCAN0TMDF15 RSCAN0.TMDF15.UINT32
#define RSCAN0TMDF15L RSCAN0.TMDF15.UINT16[L]
#define RSCAN0TMDF15LL RSCAN0.TMDF15.UINT8[LL]
#define RSCAN0TMDF15LH RSCAN0.TMDF15.UINT8[LH]
#define RSCAN0TMDF15H RSCAN0.TMDF15.UINT16[H]
#define RSCAN0TMDF15HL RSCAN0.TMDF15.UINT8[HL]
#define RSCAN0TMDF15HH RSCAN0.TMDF15.UINT8[HH]
#define RSCAN0TMID6 RSCAN0.TMID6.UINT32
#define RSCAN0TMID6L RSCAN0.TMID6.UINT16[L]
#define RSCAN0TMID6LL RSCAN0.TMID6.UINT8[LL]
#define RSCAN0TMID6LH RSCAN0.TMID6.UINT8[LH]
#define RSCAN0TMID6H RSCAN0.TMID6.UINT16[H]
#define RSCAN0TMID6HL RSCAN0.TMID6.UINT8[HL]
#define RSCAN0TMID6HH RSCAN0.TMID6.UINT8[HH]
#define RSCAN0TMPTR6 RSCAN0.TMPTR6.UINT32
#define RSCAN0TMPTR6L RSCAN0.TMPTR6.UINT16[L]
#define RSCAN0TMPTR6LL RSCAN0.TMPTR6.UINT8[LL]
#define RSCAN0TMPTR6LH RSCAN0.TMPTR6.UINT8[LH]
#define RSCAN0TMPTR6H RSCAN0.TMPTR6.UINT16[H]
#define RSCAN0TMPTR6HL RSCAN0.TMPTR6.UINT8[HL]
#define RSCAN0TMPTR6HH RSCAN0.TMPTR6.UINT8[HH]
#define RSCAN0TMDF06 RSCAN0.TMDF06.UINT32
#define RSCAN0TMDF06L RSCAN0.TMDF06.UINT16[L]
#define RSCAN0TMDF06LL RSCAN0.TMDF06.UINT8[LL]
#define RSCAN0TMDF06LH RSCAN0.TMDF06.UINT8[LH]
#define RSCAN0TMDF06H RSCAN0.TMDF06.UINT16[H]
#define RSCAN0TMDF06HL RSCAN0.TMDF06.UINT8[HL]
#define RSCAN0TMDF06HH RSCAN0.TMDF06.UINT8[HH]
#define RSCAN0TMDF16 RSCAN0.TMDF16.UINT32
#define RSCAN0TMDF16L RSCAN0.TMDF16.UINT16[L]
#define RSCAN0TMDF16LL RSCAN0.TMDF16.UINT8[LL]
#define RSCAN0TMDF16LH RSCAN0.TMDF16.UINT8[LH]
#define RSCAN0TMDF16H RSCAN0.TMDF16.UINT16[H]
#define RSCAN0TMDF16HL RSCAN0.TMDF16.UINT8[HL]
#define RSCAN0TMDF16HH RSCAN0.TMDF16.UINT8[HH]
#define RSCAN0TMID7 RSCAN0.TMID7.UINT32
#define RSCAN0TMID7L RSCAN0.TMID7.UINT16[L]
#define RSCAN0TMID7LL RSCAN0.TMID7.UINT8[LL]
#define RSCAN0TMID7LH RSCAN0.TMID7.UINT8[LH]
#define RSCAN0TMID7H RSCAN0.TMID7.UINT16[H]
#define RSCAN0TMID7HL RSCAN0.TMID7.UINT8[HL]
#define RSCAN0TMID7HH RSCAN0.TMID7.UINT8[HH]
#define RSCAN0TMPTR7 RSCAN0.TMPTR7.UINT32
#define RSCAN0TMPTR7L RSCAN0.TMPTR7.UINT16[L]
#define RSCAN0TMPTR7LL RSCAN0.TMPTR7.UINT8[LL]
#define RSCAN0TMPTR7LH RSCAN0.TMPTR7.UINT8[LH]
#define RSCAN0TMPTR7H RSCAN0.TMPTR7.UINT16[H]
#define RSCAN0TMPTR7HL RSCAN0.TMPTR7.UINT8[HL]
#define RSCAN0TMPTR7HH RSCAN0.TMPTR7.UINT8[HH]
#define RSCAN0TMDF07 RSCAN0.TMDF07.UINT32
#define RSCAN0TMDF07L RSCAN0.TMDF07.UINT16[L]
#define RSCAN0TMDF07LL RSCAN0.TMDF07.UINT8[LL]
#define RSCAN0TMDF07LH RSCAN0.TMDF07.UINT8[LH]
#define RSCAN0TMDF07H RSCAN0.TMDF07.UINT16[H]
#define RSCAN0TMDF07HL RSCAN0.TMDF07.UINT8[HL]
#define RSCAN0TMDF07HH RSCAN0.TMDF07.UINT8[HH]
#define RSCAN0TMDF17 RSCAN0.TMDF17.UINT32
#define RSCAN0TMDF17L RSCAN0.TMDF17.UINT16[L]
#define RSCAN0TMDF17LL RSCAN0.TMDF17.UINT8[LL]
#define RSCAN0TMDF17LH RSCAN0.TMDF17.UINT8[LH]
#define RSCAN0TMDF17H RSCAN0.TMDF17.UINT16[H]
#define RSCAN0TMDF17HL RSCAN0.TMDF17.UINT8[HL]
#define RSCAN0TMDF17HH RSCAN0.TMDF17.UINT8[HH]
#define RSCAN0TMID8 RSCAN0.TMID8.UINT32
#define RSCAN0TMID8L RSCAN0.TMID8.UINT16[L]
#define RSCAN0TMID8LL RSCAN0.TMID8.UINT8[LL]
#define RSCAN0TMID8LH RSCAN0.TMID8.UINT8[LH]
#define RSCAN0TMID8H RSCAN0.TMID8.UINT16[H]
#define RSCAN0TMID8HL RSCAN0.TMID8.UINT8[HL]
#define RSCAN0TMID8HH RSCAN0.TMID8.UINT8[HH]
#define RSCAN0TMPTR8 RSCAN0.TMPTR8.UINT32
#define RSCAN0TMPTR8L RSCAN0.TMPTR8.UINT16[L]
#define RSCAN0TMPTR8LL RSCAN0.TMPTR8.UINT8[LL]
#define RSCAN0TMPTR8LH RSCAN0.TMPTR8.UINT8[LH]
#define RSCAN0TMPTR8H RSCAN0.TMPTR8.UINT16[H]
#define RSCAN0TMPTR8HL RSCAN0.TMPTR8.UINT8[HL]
#define RSCAN0TMPTR8HH RSCAN0.TMPTR8.UINT8[HH]
#define RSCAN0TMDF08 RSCAN0.TMDF08.UINT32
#define RSCAN0TMDF08L RSCAN0.TMDF08.UINT16[L]
#define RSCAN0TMDF08LL RSCAN0.TMDF08.UINT8[LL]
#define RSCAN0TMDF08LH RSCAN0.TMDF08.UINT8[LH]
#define RSCAN0TMDF08H RSCAN0.TMDF08.UINT16[H]
#define RSCAN0TMDF08HL RSCAN0.TMDF08.UINT8[HL]
#define RSCAN0TMDF08HH RSCAN0.TMDF08.UINT8[HH]
#define RSCAN0TMDF18 RSCAN0.TMDF18.UINT32
#define RSCAN0TMDF18L RSCAN0.TMDF18.UINT16[L]
#define RSCAN0TMDF18LL RSCAN0.TMDF18.UINT8[LL]
#define RSCAN0TMDF18LH RSCAN0.TMDF18.UINT8[LH]
#define RSCAN0TMDF18H RSCAN0.TMDF18.UINT16[H]
#define RSCAN0TMDF18HL RSCAN0.TMDF18.UINT8[HL]
#define RSCAN0TMDF18HH RSCAN0.TMDF18.UINT8[HH]
#define RSCAN0TMID9 RSCAN0.TMID9.UINT32
#define RSCAN0TMID9L RSCAN0.TMID9.UINT16[L]
#define RSCAN0TMID9LL RSCAN0.TMID9.UINT8[LL]
#define RSCAN0TMID9LH RSCAN0.TMID9.UINT8[LH]
#define RSCAN0TMID9H RSCAN0.TMID9.UINT16[H]
#define RSCAN0TMID9HL RSCAN0.TMID9.UINT8[HL]
#define RSCAN0TMID9HH RSCAN0.TMID9.UINT8[HH]
#define RSCAN0TMPTR9 RSCAN0.TMPTR9.UINT32
#define RSCAN0TMPTR9L RSCAN0.TMPTR9.UINT16[L]
#define RSCAN0TMPTR9LL RSCAN0.TMPTR9.UINT8[LL]
#define RSCAN0TMPTR9LH RSCAN0.TMPTR9.UINT8[LH]
#define RSCAN0TMPTR9H RSCAN0.TMPTR9.UINT16[H]
#define RSCAN0TMPTR9HL RSCAN0.TMPTR9.UINT8[HL]
#define RSCAN0TMPTR9HH RSCAN0.TMPTR9.UINT8[HH]
#define RSCAN0TMDF09 RSCAN0.TMDF09.UINT32
#define RSCAN0TMDF09L RSCAN0.TMDF09.UINT16[L]
#define RSCAN0TMDF09LL RSCAN0.TMDF09.UINT8[LL]
#define RSCAN0TMDF09LH RSCAN0.TMDF09.UINT8[LH]
#define RSCAN0TMDF09H RSCAN0.TMDF09.UINT16[H]
#define RSCAN0TMDF09HL RSCAN0.TMDF09.UINT8[HL]
#define RSCAN0TMDF09HH RSCAN0.TMDF09.UINT8[HH]
#define RSCAN0TMDF19 RSCAN0.TMDF19.UINT32
#define RSCAN0TMDF19L RSCAN0.TMDF19.UINT16[L]
#define RSCAN0TMDF19LL RSCAN0.TMDF19.UINT8[LL]
#define RSCAN0TMDF19LH RSCAN0.TMDF19.UINT8[LH]
#define RSCAN0TMDF19H RSCAN0.TMDF19.UINT16[H]
#define RSCAN0TMDF19HL RSCAN0.TMDF19.UINT8[HL]
#define RSCAN0TMDF19HH RSCAN0.TMDF19.UINT8[HH]
#define RSCAN0TMID10 RSCAN0.TMID10.UINT32
#define RSCAN0TMID10L RSCAN0.TMID10.UINT16[L]
#define RSCAN0TMID10LL RSCAN0.TMID10.UINT8[LL]
#define RSCAN0TMID10LH RSCAN0.TMID10.UINT8[LH]
#define RSCAN0TMID10H RSCAN0.TMID10.UINT16[H]
#define RSCAN0TMID10HL RSCAN0.TMID10.UINT8[HL]
#define RSCAN0TMID10HH RSCAN0.TMID10.UINT8[HH]
#define RSCAN0TMPTR10 RSCAN0.TMPTR10.UINT32
#define RSCAN0TMPTR10L RSCAN0.TMPTR10.UINT16[L]
#define RSCAN0TMPTR10LL RSCAN0.TMPTR10.UINT8[LL]
#define RSCAN0TMPTR10LH RSCAN0.TMPTR10.UINT8[LH]
#define RSCAN0TMPTR10H RSCAN0.TMPTR10.UINT16[H]
#define RSCAN0TMPTR10HL RSCAN0.TMPTR10.UINT8[HL]
#define RSCAN0TMPTR10HH RSCAN0.TMPTR10.UINT8[HH]
#define RSCAN0TMDF010 RSCAN0.TMDF010.UINT32
#define RSCAN0TMDF010L RSCAN0.TMDF010.UINT16[L]
#define RSCAN0TMDF010LL RSCAN0.TMDF010.UINT8[LL]
#define RSCAN0TMDF010LH RSCAN0.TMDF010.UINT8[LH]
#define RSCAN0TMDF010H RSCAN0.TMDF010.UINT16[H]
#define RSCAN0TMDF010HL RSCAN0.TMDF010.UINT8[HL]
#define RSCAN0TMDF010HH RSCAN0.TMDF010.UINT8[HH]
#define RSCAN0TMDF110 RSCAN0.TMDF110.UINT32
#define RSCAN0TMDF110L RSCAN0.TMDF110.UINT16[L]
#define RSCAN0TMDF110LL RSCAN0.TMDF110.UINT8[LL]
#define RSCAN0TMDF110LH RSCAN0.TMDF110.UINT8[LH]
#define RSCAN0TMDF110H RSCAN0.TMDF110.UINT16[H]
#define RSCAN0TMDF110HL RSCAN0.TMDF110.UINT8[HL]
#define RSCAN0TMDF110HH RSCAN0.TMDF110.UINT8[HH]
#define RSCAN0TMID11 RSCAN0.TMID11.UINT32
#define RSCAN0TMID11L RSCAN0.TMID11.UINT16[L]
#define RSCAN0TMID11LL RSCAN0.TMID11.UINT8[LL]
#define RSCAN0TMID11LH RSCAN0.TMID11.UINT8[LH]
#define RSCAN0TMID11H RSCAN0.TMID11.UINT16[H]
#define RSCAN0TMID11HL RSCAN0.TMID11.UINT8[HL]
#define RSCAN0TMID11HH RSCAN0.TMID11.UINT8[HH]
#define RSCAN0TMPTR11 RSCAN0.TMPTR11.UINT32
#define RSCAN0TMPTR11L RSCAN0.TMPTR11.UINT16[L]
#define RSCAN0TMPTR11LL RSCAN0.TMPTR11.UINT8[LL]
#define RSCAN0TMPTR11LH RSCAN0.TMPTR11.UINT8[LH]
#define RSCAN0TMPTR11H RSCAN0.TMPTR11.UINT16[H]
#define RSCAN0TMPTR11HL RSCAN0.TMPTR11.UINT8[HL]
#define RSCAN0TMPTR11HH RSCAN0.TMPTR11.UINT8[HH]
#define RSCAN0TMDF011 RSCAN0.TMDF011.UINT32
#define RSCAN0TMDF011L RSCAN0.TMDF011.UINT16[L]
#define RSCAN0TMDF011LL RSCAN0.TMDF011.UINT8[LL]
#define RSCAN0TMDF011LH RSCAN0.TMDF011.UINT8[LH]
#define RSCAN0TMDF011H RSCAN0.TMDF011.UINT16[H]
#define RSCAN0TMDF011HL RSCAN0.TMDF011.UINT8[HL]
#define RSCAN0TMDF011HH RSCAN0.TMDF011.UINT8[HH]
#define RSCAN0TMDF111 RSCAN0.TMDF111.UINT32
#define RSCAN0TMDF111L RSCAN0.TMDF111.UINT16[L]
#define RSCAN0TMDF111LL RSCAN0.TMDF111.UINT8[LL]
#define RSCAN0TMDF111LH RSCAN0.TMDF111.UINT8[LH]
#define RSCAN0TMDF111H RSCAN0.TMDF111.UINT16[H]
#define RSCAN0TMDF111HL RSCAN0.TMDF111.UINT8[HL]
#define RSCAN0TMDF111HH RSCAN0.TMDF111.UINT8[HH]
#define RSCAN0TMID12 RSCAN0.TMID12.UINT32
#define RSCAN0TMID12L RSCAN0.TMID12.UINT16[L]
#define RSCAN0TMID12LL RSCAN0.TMID12.UINT8[LL]
#define RSCAN0TMID12LH RSCAN0.TMID12.UINT8[LH]
#define RSCAN0TMID12H RSCAN0.TMID12.UINT16[H]
#define RSCAN0TMID12HL RSCAN0.TMID12.UINT8[HL]
#define RSCAN0TMID12HH RSCAN0.TMID12.UINT8[HH]
#define RSCAN0TMPTR12 RSCAN0.TMPTR12.UINT32
#define RSCAN0TMPTR12L RSCAN0.TMPTR12.UINT16[L]
#define RSCAN0TMPTR12LL RSCAN0.TMPTR12.UINT8[LL]
#define RSCAN0TMPTR12LH RSCAN0.TMPTR12.UINT8[LH]
#define RSCAN0TMPTR12H RSCAN0.TMPTR12.UINT16[H]
#define RSCAN0TMPTR12HL RSCAN0.TMPTR12.UINT8[HL]
#define RSCAN0TMPTR12HH RSCAN0.TMPTR12.UINT8[HH]
#define RSCAN0TMDF012 RSCAN0.TMDF012.UINT32
#define RSCAN0TMDF012L RSCAN0.TMDF012.UINT16[L]
#define RSCAN0TMDF012LL RSCAN0.TMDF012.UINT8[LL]
#define RSCAN0TMDF012LH RSCAN0.TMDF012.UINT8[LH]
#define RSCAN0TMDF012H RSCAN0.TMDF012.UINT16[H]
#define RSCAN0TMDF012HL RSCAN0.TMDF012.UINT8[HL]
#define RSCAN0TMDF012HH RSCAN0.TMDF012.UINT8[HH]
#define RSCAN0TMDF112 RSCAN0.TMDF112.UINT32
#define RSCAN0TMDF112L RSCAN0.TMDF112.UINT16[L]
#define RSCAN0TMDF112LL RSCAN0.TMDF112.UINT8[LL]
#define RSCAN0TMDF112LH RSCAN0.TMDF112.UINT8[LH]
#define RSCAN0TMDF112H RSCAN0.TMDF112.UINT16[H]
#define RSCAN0TMDF112HL RSCAN0.TMDF112.UINT8[HL]
#define RSCAN0TMDF112HH RSCAN0.TMDF112.UINT8[HH]
#define RSCAN0TMID13 RSCAN0.TMID13.UINT32
#define RSCAN0TMID13L RSCAN0.TMID13.UINT16[L]
#define RSCAN0TMID13LL RSCAN0.TMID13.UINT8[LL]
#define RSCAN0TMID13LH RSCAN0.TMID13.UINT8[LH]
#define RSCAN0TMID13H RSCAN0.TMID13.UINT16[H]
#define RSCAN0TMID13HL RSCAN0.TMID13.UINT8[HL]
#define RSCAN0TMID13HH RSCAN0.TMID13.UINT8[HH]
#define RSCAN0TMPTR13 RSCAN0.TMPTR13.UINT32
#define RSCAN0TMPTR13L RSCAN0.TMPTR13.UINT16[L]
#define RSCAN0TMPTR13LL RSCAN0.TMPTR13.UINT8[LL]
#define RSCAN0TMPTR13LH RSCAN0.TMPTR13.UINT8[LH]
#define RSCAN0TMPTR13H RSCAN0.TMPTR13.UINT16[H]
#define RSCAN0TMPTR13HL RSCAN0.TMPTR13.UINT8[HL]
#define RSCAN0TMPTR13HH RSCAN0.TMPTR13.UINT8[HH]
#define RSCAN0TMDF013 RSCAN0.TMDF013.UINT32
#define RSCAN0TMDF013L RSCAN0.TMDF013.UINT16[L]
#define RSCAN0TMDF013LL RSCAN0.TMDF013.UINT8[LL]
#define RSCAN0TMDF013LH RSCAN0.TMDF013.UINT8[LH]
#define RSCAN0TMDF013H RSCAN0.TMDF013.UINT16[H]
#define RSCAN0TMDF013HL RSCAN0.TMDF013.UINT8[HL]
#define RSCAN0TMDF013HH RSCAN0.TMDF013.UINT8[HH]
#define RSCAN0TMDF113 RSCAN0.TMDF113.UINT32
#define RSCAN0TMDF113L RSCAN0.TMDF113.UINT16[L]
#define RSCAN0TMDF113LL RSCAN0.TMDF113.UINT8[LL]
#define RSCAN0TMDF113LH RSCAN0.TMDF113.UINT8[LH]
#define RSCAN0TMDF113H RSCAN0.TMDF113.UINT16[H]
#define RSCAN0TMDF113HL RSCAN0.TMDF113.UINT8[HL]
#define RSCAN0TMDF113HH RSCAN0.TMDF113.UINT8[HH]
#define RSCAN0TMID14 RSCAN0.TMID14.UINT32
#define RSCAN0TMID14L RSCAN0.TMID14.UINT16[L]
#define RSCAN0TMID14LL RSCAN0.TMID14.UINT8[LL]
#define RSCAN0TMID14LH RSCAN0.TMID14.UINT8[LH]
#define RSCAN0TMID14H RSCAN0.TMID14.UINT16[H]
#define RSCAN0TMID14HL RSCAN0.TMID14.UINT8[HL]
#define RSCAN0TMID14HH RSCAN0.TMID14.UINT8[HH]
#define RSCAN0TMPTR14 RSCAN0.TMPTR14.UINT32
#define RSCAN0TMPTR14L RSCAN0.TMPTR14.UINT16[L]
#define RSCAN0TMPTR14LL RSCAN0.TMPTR14.UINT8[LL]
#define RSCAN0TMPTR14LH RSCAN0.TMPTR14.UINT8[LH]
#define RSCAN0TMPTR14H RSCAN0.TMPTR14.UINT16[H]
#define RSCAN0TMPTR14HL RSCAN0.TMPTR14.UINT8[HL]
#define RSCAN0TMPTR14HH RSCAN0.TMPTR14.UINT8[HH]
#define RSCAN0TMDF014 RSCAN0.TMDF014.UINT32
#define RSCAN0TMDF014L RSCAN0.TMDF014.UINT16[L]
#define RSCAN0TMDF014LL RSCAN0.TMDF014.UINT8[LL]
#define RSCAN0TMDF014LH RSCAN0.TMDF014.UINT8[LH]
#define RSCAN0TMDF014H RSCAN0.TMDF014.UINT16[H]
#define RSCAN0TMDF014HL RSCAN0.TMDF014.UINT8[HL]
#define RSCAN0TMDF014HH RSCAN0.TMDF014.UINT8[HH]
#define RSCAN0TMDF114 RSCAN0.TMDF114.UINT32
#define RSCAN0TMDF114L RSCAN0.TMDF114.UINT16[L]
#define RSCAN0TMDF114LL RSCAN0.TMDF114.UINT8[LL]
#define RSCAN0TMDF114LH RSCAN0.TMDF114.UINT8[LH]
#define RSCAN0TMDF114H RSCAN0.TMDF114.UINT16[H]
#define RSCAN0TMDF114HL RSCAN0.TMDF114.UINT8[HL]
#define RSCAN0TMDF114HH RSCAN0.TMDF114.UINT8[HH]
#define RSCAN0TMID15 RSCAN0.TMID15.UINT32
#define RSCAN0TMID15L RSCAN0.TMID15.UINT16[L]
#define RSCAN0TMID15LL RSCAN0.TMID15.UINT8[LL]
#define RSCAN0TMID15LH RSCAN0.TMID15.UINT8[LH]
#define RSCAN0TMID15H RSCAN0.TMID15.UINT16[H]
#define RSCAN0TMID15HL RSCAN0.TMID15.UINT8[HL]
#define RSCAN0TMID15HH RSCAN0.TMID15.UINT8[HH]
#define RSCAN0TMPTR15 RSCAN0.TMPTR15.UINT32
#define RSCAN0TMPTR15L RSCAN0.TMPTR15.UINT16[L]
#define RSCAN0TMPTR15LL RSCAN0.TMPTR15.UINT8[LL]
#define RSCAN0TMPTR15LH RSCAN0.TMPTR15.UINT8[LH]
#define RSCAN0TMPTR15H RSCAN0.TMPTR15.UINT16[H]
#define RSCAN0TMPTR15HL RSCAN0.TMPTR15.UINT8[HL]
#define RSCAN0TMPTR15HH RSCAN0.TMPTR15.UINT8[HH]
#define RSCAN0TMDF015 RSCAN0.TMDF015.UINT32
#define RSCAN0TMDF015L RSCAN0.TMDF015.UINT16[L]
#define RSCAN0TMDF015LL RSCAN0.TMDF015.UINT8[LL]
#define RSCAN0TMDF015LH RSCAN0.TMDF015.UINT8[LH]
#define RSCAN0TMDF015H RSCAN0.TMDF015.UINT16[H]
#define RSCAN0TMDF015HL RSCAN0.TMDF015.UINT8[HL]
#define RSCAN0TMDF015HH RSCAN0.TMDF015.UINT8[HH]
#define RSCAN0TMDF115 RSCAN0.TMDF115.UINT32
#define RSCAN0TMDF115L RSCAN0.TMDF115.UINT16[L]
#define RSCAN0TMDF115LL RSCAN0.TMDF115.UINT8[LL]
#define RSCAN0TMDF115LH RSCAN0.TMDF115.UINT8[LH]
#define RSCAN0TMDF115H RSCAN0.TMDF115.UINT16[H]
#define RSCAN0TMDF115HL RSCAN0.TMDF115.UINT8[HL]
#define RSCAN0TMDF115HH RSCAN0.TMDF115.UINT8[HH]
#define RSCAN0TMID16 RSCAN0.TMID16.UINT32
#define RSCAN0TMID16L RSCAN0.TMID16.UINT16[L]
#define RSCAN0TMID16LL RSCAN0.TMID16.UINT8[LL]
#define RSCAN0TMID16LH RSCAN0.TMID16.UINT8[LH]
#define RSCAN0TMID16H RSCAN0.TMID16.UINT16[H]
#define RSCAN0TMID16HL RSCAN0.TMID16.UINT8[HL]
#define RSCAN0TMID16HH RSCAN0.TMID16.UINT8[HH]
#define RSCAN0TMPTR16 RSCAN0.TMPTR16.UINT32
#define RSCAN0TMPTR16L RSCAN0.TMPTR16.UINT16[L]
#define RSCAN0TMPTR16LL RSCAN0.TMPTR16.UINT8[LL]
#define RSCAN0TMPTR16LH RSCAN0.TMPTR16.UINT8[LH]
#define RSCAN0TMPTR16H RSCAN0.TMPTR16.UINT16[H]
#define RSCAN0TMPTR16HL RSCAN0.TMPTR16.UINT8[HL]
#define RSCAN0TMPTR16HH RSCAN0.TMPTR16.UINT8[HH]
#define RSCAN0TMDF016 RSCAN0.TMDF016.UINT32
#define RSCAN0TMDF016L RSCAN0.TMDF016.UINT16[L]
#define RSCAN0TMDF016LL RSCAN0.TMDF016.UINT8[LL]
#define RSCAN0TMDF016LH RSCAN0.TMDF016.UINT8[LH]
#define RSCAN0TMDF016H RSCAN0.TMDF016.UINT16[H]
#define RSCAN0TMDF016HL RSCAN0.TMDF016.UINT8[HL]
#define RSCAN0TMDF016HH RSCAN0.TMDF016.UINT8[HH]
#define RSCAN0TMDF116 RSCAN0.TMDF116.UINT32
#define RSCAN0TMDF116L RSCAN0.TMDF116.UINT16[L]
#define RSCAN0TMDF116LL RSCAN0.TMDF116.UINT8[LL]
#define RSCAN0TMDF116LH RSCAN0.TMDF116.UINT8[LH]
#define RSCAN0TMDF116H RSCAN0.TMDF116.UINT16[H]
#define RSCAN0TMDF116HL RSCAN0.TMDF116.UINT8[HL]
#define RSCAN0TMDF116HH RSCAN0.TMDF116.UINT8[HH]
#define RSCAN0TMID17 RSCAN0.TMID17.UINT32
#define RSCAN0TMID17L RSCAN0.TMID17.UINT16[L]
#define RSCAN0TMID17LL RSCAN0.TMID17.UINT8[LL]
#define RSCAN0TMID17LH RSCAN0.TMID17.UINT8[LH]
#define RSCAN0TMID17H RSCAN0.TMID17.UINT16[H]
#define RSCAN0TMID17HL RSCAN0.TMID17.UINT8[HL]
#define RSCAN0TMID17HH RSCAN0.TMID17.UINT8[HH]
#define RSCAN0TMPTR17 RSCAN0.TMPTR17.UINT32
#define RSCAN0TMPTR17L RSCAN0.TMPTR17.UINT16[L]
#define RSCAN0TMPTR17LL RSCAN0.TMPTR17.UINT8[LL]
#define RSCAN0TMPTR17LH RSCAN0.TMPTR17.UINT8[LH]
#define RSCAN0TMPTR17H RSCAN0.TMPTR17.UINT16[H]
#define RSCAN0TMPTR17HL RSCAN0.TMPTR17.UINT8[HL]
#define RSCAN0TMPTR17HH RSCAN0.TMPTR17.UINT8[HH]
#define RSCAN0TMDF017 RSCAN0.TMDF017.UINT32
#define RSCAN0TMDF017L RSCAN0.TMDF017.UINT16[L]
#define RSCAN0TMDF017LL RSCAN0.TMDF017.UINT8[LL]
#define RSCAN0TMDF017LH RSCAN0.TMDF017.UINT8[LH]
#define RSCAN0TMDF017H RSCAN0.TMDF017.UINT16[H]
#define RSCAN0TMDF017HL RSCAN0.TMDF017.UINT8[HL]
#define RSCAN0TMDF017HH RSCAN0.TMDF017.UINT8[HH]
#define RSCAN0TMDF117 RSCAN0.TMDF117.UINT32
#define RSCAN0TMDF117L RSCAN0.TMDF117.UINT16[L]
#define RSCAN0TMDF117LL RSCAN0.TMDF117.UINT8[LL]
#define RSCAN0TMDF117LH RSCAN0.TMDF117.UINT8[LH]
#define RSCAN0TMDF117H RSCAN0.TMDF117.UINT16[H]
#define RSCAN0TMDF117HL RSCAN0.TMDF117.UINT8[HL]
#define RSCAN0TMDF117HH RSCAN0.TMDF117.UINT8[HH]
#define RSCAN0TMID18 RSCAN0.TMID18.UINT32
#define RSCAN0TMID18L RSCAN0.TMID18.UINT16[L]
#define RSCAN0TMID18LL RSCAN0.TMID18.UINT8[LL]
#define RSCAN0TMID18LH RSCAN0.TMID18.UINT8[LH]
#define RSCAN0TMID18H RSCAN0.TMID18.UINT16[H]
#define RSCAN0TMID18HL RSCAN0.TMID18.UINT8[HL]
#define RSCAN0TMID18HH RSCAN0.TMID18.UINT8[HH]
#define RSCAN0TMPTR18 RSCAN0.TMPTR18.UINT32
#define RSCAN0TMPTR18L RSCAN0.TMPTR18.UINT16[L]
#define RSCAN0TMPTR18LL RSCAN0.TMPTR18.UINT8[LL]
#define RSCAN0TMPTR18LH RSCAN0.TMPTR18.UINT8[LH]
#define RSCAN0TMPTR18H RSCAN0.TMPTR18.UINT16[H]
#define RSCAN0TMPTR18HL RSCAN0.TMPTR18.UINT8[HL]
#define RSCAN0TMPTR18HH RSCAN0.TMPTR18.UINT8[HH]
#define RSCAN0TMDF018 RSCAN0.TMDF018.UINT32
#define RSCAN0TMDF018L RSCAN0.TMDF018.UINT16[L]
#define RSCAN0TMDF018LL RSCAN0.TMDF018.UINT8[LL]
#define RSCAN0TMDF018LH RSCAN0.TMDF018.UINT8[LH]
#define RSCAN0TMDF018H RSCAN0.TMDF018.UINT16[H]
#define RSCAN0TMDF018HL RSCAN0.TMDF018.UINT8[HL]
#define RSCAN0TMDF018HH RSCAN0.TMDF018.UINT8[HH]
#define RSCAN0TMDF118 RSCAN0.TMDF118.UINT32
#define RSCAN0TMDF118L RSCAN0.TMDF118.UINT16[L]
#define RSCAN0TMDF118LL RSCAN0.TMDF118.UINT8[LL]
#define RSCAN0TMDF118LH RSCAN0.TMDF118.UINT8[LH]
#define RSCAN0TMDF118H RSCAN0.TMDF118.UINT16[H]
#define RSCAN0TMDF118HL RSCAN0.TMDF118.UINT8[HL]
#define RSCAN0TMDF118HH RSCAN0.TMDF118.UINT8[HH]
#define RSCAN0TMID19 RSCAN0.TMID19.UINT32
#define RSCAN0TMID19L RSCAN0.TMID19.UINT16[L]
#define RSCAN0TMID19LL RSCAN0.TMID19.UINT8[LL]
#define RSCAN0TMID19LH RSCAN0.TMID19.UINT8[LH]
#define RSCAN0TMID19H RSCAN0.TMID19.UINT16[H]
#define RSCAN0TMID19HL RSCAN0.TMID19.UINT8[HL]
#define RSCAN0TMID19HH RSCAN0.TMID19.UINT8[HH]
#define RSCAN0TMPTR19 RSCAN0.TMPTR19.UINT32
#define RSCAN0TMPTR19L RSCAN0.TMPTR19.UINT16[L]
#define RSCAN0TMPTR19LL RSCAN0.TMPTR19.UINT8[LL]
#define RSCAN0TMPTR19LH RSCAN0.TMPTR19.UINT8[LH]
#define RSCAN0TMPTR19H RSCAN0.TMPTR19.UINT16[H]
#define RSCAN0TMPTR19HL RSCAN0.TMPTR19.UINT8[HL]
#define RSCAN0TMPTR19HH RSCAN0.TMPTR19.UINT8[HH]
#define RSCAN0TMDF019 RSCAN0.TMDF019.UINT32
#define RSCAN0TMDF019L RSCAN0.TMDF019.UINT16[L]
#define RSCAN0TMDF019LL RSCAN0.TMDF019.UINT8[LL]
#define RSCAN0TMDF019LH RSCAN0.TMDF019.UINT8[LH]
#define RSCAN0TMDF019H RSCAN0.TMDF019.UINT16[H]
#define RSCAN0TMDF019HL RSCAN0.TMDF019.UINT8[HL]
#define RSCAN0TMDF019HH RSCAN0.TMDF019.UINT8[HH]
#define RSCAN0TMDF119 RSCAN0.TMDF119.UINT32
#define RSCAN0TMDF119L RSCAN0.TMDF119.UINT16[L]
#define RSCAN0TMDF119LL RSCAN0.TMDF119.UINT8[LL]
#define RSCAN0TMDF119LH RSCAN0.TMDF119.UINT8[LH]
#define RSCAN0TMDF119H RSCAN0.TMDF119.UINT16[H]
#define RSCAN0TMDF119HL RSCAN0.TMDF119.UINT8[HL]
#define RSCAN0TMDF119HH RSCAN0.TMDF119.UINT8[HH]
#define RSCAN0TMID20 RSCAN0.TMID20.UINT32
#define RSCAN0TMID20L RSCAN0.TMID20.UINT16[L]
#define RSCAN0TMID20LL RSCAN0.TMID20.UINT8[LL]
#define RSCAN0TMID20LH RSCAN0.TMID20.UINT8[LH]
#define RSCAN0TMID20H RSCAN0.TMID20.UINT16[H]
#define RSCAN0TMID20HL RSCAN0.TMID20.UINT8[HL]
#define RSCAN0TMID20HH RSCAN0.TMID20.UINT8[HH]
#define RSCAN0TMPTR20 RSCAN0.TMPTR20.UINT32
#define RSCAN0TMPTR20L RSCAN0.TMPTR20.UINT16[L]
#define RSCAN0TMPTR20LL RSCAN0.TMPTR20.UINT8[LL]
#define RSCAN0TMPTR20LH RSCAN0.TMPTR20.UINT8[LH]
#define RSCAN0TMPTR20H RSCAN0.TMPTR20.UINT16[H]
#define RSCAN0TMPTR20HL RSCAN0.TMPTR20.UINT8[HL]
#define RSCAN0TMPTR20HH RSCAN0.TMPTR20.UINT8[HH]
#define RSCAN0TMDF020 RSCAN0.TMDF020.UINT32
#define RSCAN0TMDF020L RSCAN0.TMDF020.UINT16[L]
#define RSCAN0TMDF020LL RSCAN0.TMDF020.UINT8[LL]
#define RSCAN0TMDF020LH RSCAN0.TMDF020.UINT8[LH]
#define RSCAN0TMDF020H RSCAN0.TMDF020.UINT16[H]
#define RSCAN0TMDF020HL RSCAN0.TMDF020.UINT8[HL]
#define RSCAN0TMDF020HH RSCAN0.TMDF020.UINT8[HH]
#define RSCAN0TMDF120 RSCAN0.TMDF120.UINT32
#define RSCAN0TMDF120L RSCAN0.TMDF120.UINT16[L]
#define RSCAN0TMDF120LL RSCAN0.TMDF120.UINT8[LL]
#define RSCAN0TMDF120LH RSCAN0.TMDF120.UINT8[LH]
#define RSCAN0TMDF120H RSCAN0.TMDF120.UINT16[H]
#define RSCAN0TMDF120HL RSCAN0.TMDF120.UINT8[HL]
#define RSCAN0TMDF120HH RSCAN0.TMDF120.UINT8[HH]
#define RSCAN0TMID21 RSCAN0.TMID21.UINT32
#define RSCAN0TMID21L RSCAN0.TMID21.UINT16[L]
#define RSCAN0TMID21LL RSCAN0.TMID21.UINT8[LL]
#define RSCAN0TMID21LH RSCAN0.TMID21.UINT8[LH]
#define RSCAN0TMID21H RSCAN0.TMID21.UINT16[H]
#define RSCAN0TMID21HL RSCAN0.TMID21.UINT8[HL]
#define RSCAN0TMID21HH RSCAN0.TMID21.UINT8[HH]
#define RSCAN0TMPTR21 RSCAN0.TMPTR21.UINT32
#define RSCAN0TMPTR21L RSCAN0.TMPTR21.UINT16[L]
#define RSCAN0TMPTR21LL RSCAN0.TMPTR21.UINT8[LL]
#define RSCAN0TMPTR21LH RSCAN0.TMPTR21.UINT8[LH]
#define RSCAN0TMPTR21H RSCAN0.TMPTR21.UINT16[H]
#define RSCAN0TMPTR21HL RSCAN0.TMPTR21.UINT8[HL]
#define RSCAN0TMPTR21HH RSCAN0.TMPTR21.UINT8[HH]
#define RSCAN0TMDF021 RSCAN0.TMDF021.UINT32
#define RSCAN0TMDF021L RSCAN0.TMDF021.UINT16[L]
#define RSCAN0TMDF021LL RSCAN0.TMDF021.UINT8[LL]
#define RSCAN0TMDF021LH RSCAN0.TMDF021.UINT8[LH]
#define RSCAN0TMDF021H RSCAN0.TMDF021.UINT16[H]
#define RSCAN0TMDF021HL RSCAN0.TMDF021.UINT8[HL]
#define RSCAN0TMDF021HH RSCAN0.TMDF021.UINT8[HH]
#define RSCAN0TMDF121 RSCAN0.TMDF121.UINT32
#define RSCAN0TMDF121L RSCAN0.TMDF121.UINT16[L]
#define RSCAN0TMDF121LL RSCAN0.TMDF121.UINT8[LL]
#define RSCAN0TMDF121LH RSCAN0.TMDF121.UINT8[LH]
#define RSCAN0TMDF121H RSCAN0.TMDF121.UINT16[H]
#define RSCAN0TMDF121HL RSCAN0.TMDF121.UINT8[HL]
#define RSCAN0TMDF121HH RSCAN0.TMDF121.UINT8[HH]
#define RSCAN0TMID22 RSCAN0.TMID22.UINT32
#define RSCAN0TMID22L RSCAN0.TMID22.UINT16[L]
#define RSCAN0TMID22LL RSCAN0.TMID22.UINT8[LL]
#define RSCAN0TMID22LH RSCAN0.TMID22.UINT8[LH]
#define RSCAN0TMID22H RSCAN0.TMID22.UINT16[H]
#define RSCAN0TMID22HL RSCAN0.TMID22.UINT8[HL]
#define RSCAN0TMID22HH RSCAN0.TMID22.UINT8[HH]
#define RSCAN0TMPTR22 RSCAN0.TMPTR22.UINT32
#define RSCAN0TMPTR22L RSCAN0.TMPTR22.UINT16[L]
#define RSCAN0TMPTR22LL RSCAN0.TMPTR22.UINT8[LL]
#define RSCAN0TMPTR22LH RSCAN0.TMPTR22.UINT8[LH]
#define RSCAN0TMPTR22H RSCAN0.TMPTR22.UINT16[H]
#define RSCAN0TMPTR22HL RSCAN0.TMPTR22.UINT8[HL]
#define RSCAN0TMPTR22HH RSCAN0.TMPTR22.UINT8[HH]
#define RSCAN0TMDF022 RSCAN0.TMDF022.UINT32
#define RSCAN0TMDF022L RSCAN0.TMDF022.UINT16[L]
#define RSCAN0TMDF022LL RSCAN0.TMDF022.UINT8[LL]
#define RSCAN0TMDF022LH RSCAN0.TMDF022.UINT8[LH]
#define RSCAN0TMDF022H RSCAN0.TMDF022.UINT16[H]
#define RSCAN0TMDF022HL RSCAN0.TMDF022.UINT8[HL]
#define RSCAN0TMDF022HH RSCAN0.TMDF022.UINT8[HH]
#define RSCAN0TMDF122 RSCAN0.TMDF122.UINT32
#define RSCAN0TMDF122L RSCAN0.TMDF122.UINT16[L]
#define RSCAN0TMDF122LL RSCAN0.TMDF122.UINT8[LL]
#define RSCAN0TMDF122LH RSCAN0.TMDF122.UINT8[LH]
#define RSCAN0TMDF122H RSCAN0.TMDF122.UINT16[H]
#define RSCAN0TMDF122HL RSCAN0.TMDF122.UINT8[HL]
#define RSCAN0TMDF122HH RSCAN0.TMDF122.UINT8[HH]
#define RSCAN0TMID23 RSCAN0.TMID23.UINT32
#define RSCAN0TMID23L RSCAN0.TMID23.UINT16[L]
#define RSCAN0TMID23LL RSCAN0.TMID23.UINT8[LL]
#define RSCAN0TMID23LH RSCAN0.TMID23.UINT8[LH]
#define RSCAN0TMID23H RSCAN0.TMID23.UINT16[H]
#define RSCAN0TMID23HL RSCAN0.TMID23.UINT8[HL]
#define RSCAN0TMID23HH RSCAN0.TMID23.UINT8[HH]
#define RSCAN0TMPTR23 RSCAN0.TMPTR23.UINT32
#define RSCAN0TMPTR23L RSCAN0.TMPTR23.UINT16[L]
#define RSCAN0TMPTR23LL RSCAN0.TMPTR23.UINT8[LL]
#define RSCAN0TMPTR23LH RSCAN0.TMPTR23.UINT8[LH]
#define RSCAN0TMPTR23H RSCAN0.TMPTR23.UINT16[H]
#define RSCAN0TMPTR23HL RSCAN0.TMPTR23.UINT8[HL]
#define RSCAN0TMPTR23HH RSCAN0.TMPTR23.UINT8[HH]
#define RSCAN0TMDF023 RSCAN0.TMDF023.UINT32
#define RSCAN0TMDF023L RSCAN0.TMDF023.UINT16[L]
#define RSCAN0TMDF023LL RSCAN0.TMDF023.UINT8[LL]
#define RSCAN0TMDF023LH RSCAN0.TMDF023.UINT8[LH]
#define RSCAN0TMDF023H RSCAN0.TMDF023.UINT16[H]
#define RSCAN0TMDF023HL RSCAN0.TMDF023.UINT8[HL]
#define RSCAN0TMDF023HH RSCAN0.TMDF023.UINT8[HH]
#define RSCAN0TMDF123 RSCAN0.TMDF123.UINT32
#define RSCAN0TMDF123L RSCAN0.TMDF123.UINT16[L]
#define RSCAN0TMDF123LL RSCAN0.TMDF123.UINT8[LL]
#define RSCAN0TMDF123LH RSCAN0.TMDF123.UINT8[LH]
#define RSCAN0TMDF123H RSCAN0.TMDF123.UINT16[H]
#define RSCAN0TMDF123HL RSCAN0.TMDF123.UINT8[HL]
#define RSCAN0TMDF123HH RSCAN0.TMDF123.UINT8[HH]
#define RSCAN0TMID24 RSCAN0.TMID24.UINT32
#define RSCAN0TMID24L RSCAN0.TMID24.UINT16[L]
#define RSCAN0TMID24LL RSCAN0.TMID24.UINT8[LL]
#define RSCAN0TMID24LH RSCAN0.TMID24.UINT8[LH]
#define RSCAN0TMID24H RSCAN0.TMID24.UINT16[H]
#define RSCAN0TMID24HL RSCAN0.TMID24.UINT8[HL]
#define RSCAN0TMID24HH RSCAN0.TMID24.UINT8[HH]
#define RSCAN0TMPTR24 RSCAN0.TMPTR24.UINT32
#define RSCAN0TMPTR24L RSCAN0.TMPTR24.UINT16[L]
#define RSCAN0TMPTR24LL RSCAN0.TMPTR24.UINT8[LL]
#define RSCAN0TMPTR24LH RSCAN0.TMPTR24.UINT8[LH]
#define RSCAN0TMPTR24H RSCAN0.TMPTR24.UINT16[H]
#define RSCAN0TMPTR24HL RSCAN0.TMPTR24.UINT8[HL]
#define RSCAN0TMPTR24HH RSCAN0.TMPTR24.UINT8[HH]
#define RSCAN0TMDF024 RSCAN0.TMDF024.UINT32
#define RSCAN0TMDF024L RSCAN0.TMDF024.UINT16[L]
#define RSCAN0TMDF024LL RSCAN0.TMDF024.UINT8[LL]
#define RSCAN0TMDF024LH RSCAN0.TMDF024.UINT8[LH]
#define RSCAN0TMDF024H RSCAN0.TMDF024.UINT16[H]
#define RSCAN0TMDF024HL RSCAN0.TMDF024.UINT8[HL]
#define RSCAN0TMDF024HH RSCAN0.TMDF024.UINT8[HH]
#define RSCAN0TMDF124 RSCAN0.TMDF124.UINT32
#define RSCAN0TMDF124L RSCAN0.TMDF124.UINT16[L]
#define RSCAN0TMDF124LL RSCAN0.TMDF124.UINT8[LL]
#define RSCAN0TMDF124LH RSCAN0.TMDF124.UINT8[LH]
#define RSCAN0TMDF124H RSCAN0.TMDF124.UINT16[H]
#define RSCAN0TMDF124HL RSCAN0.TMDF124.UINT8[HL]
#define RSCAN0TMDF124HH RSCAN0.TMDF124.UINT8[HH]
#define RSCAN0TMID25 RSCAN0.TMID25.UINT32
#define RSCAN0TMID25L RSCAN0.TMID25.UINT16[L]
#define RSCAN0TMID25LL RSCAN0.TMID25.UINT8[LL]
#define RSCAN0TMID25LH RSCAN0.TMID25.UINT8[LH]
#define RSCAN0TMID25H RSCAN0.TMID25.UINT16[H]
#define RSCAN0TMID25HL RSCAN0.TMID25.UINT8[HL]
#define RSCAN0TMID25HH RSCAN0.TMID25.UINT8[HH]
#define RSCAN0TMPTR25 RSCAN0.TMPTR25.UINT32
#define RSCAN0TMPTR25L RSCAN0.TMPTR25.UINT16[L]
#define RSCAN0TMPTR25LL RSCAN0.TMPTR25.UINT8[LL]
#define RSCAN0TMPTR25LH RSCAN0.TMPTR25.UINT8[LH]
#define RSCAN0TMPTR25H RSCAN0.TMPTR25.UINT16[H]
#define RSCAN0TMPTR25HL RSCAN0.TMPTR25.UINT8[HL]
#define RSCAN0TMPTR25HH RSCAN0.TMPTR25.UINT8[HH]
#define RSCAN0TMDF025 RSCAN0.TMDF025.UINT32
#define RSCAN0TMDF025L RSCAN0.TMDF025.UINT16[L]
#define RSCAN0TMDF025LL RSCAN0.TMDF025.UINT8[LL]
#define RSCAN0TMDF025LH RSCAN0.TMDF025.UINT8[LH]
#define RSCAN0TMDF025H RSCAN0.TMDF025.UINT16[H]
#define RSCAN0TMDF025HL RSCAN0.TMDF025.UINT8[HL]
#define RSCAN0TMDF025HH RSCAN0.TMDF025.UINT8[HH]
#define RSCAN0TMDF125 RSCAN0.TMDF125.UINT32
#define RSCAN0TMDF125L RSCAN0.TMDF125.UINT16[L]
#define RSCAN0TMDF125LL RSCAN0.TMDF125.UINT8[LL]
#define RSCAN0TMDF125LH RSCAN0.TMDF125.UINT8[LH]
#define RSCAN0TMDF125H RSCAN0.TMDF125.UINT16[H]
#define RSCAN0TMDF125HL RSCAN0.TMDF125.UINT8[HL]
#define RSCAN0TMDF125HH RSCAN0.TMDF125.UINT8[HH]
#define RSCAN0TMID26 RSCAN0.TMID26.UINT32
#define RSCAN0TMID26L RSCAN0.TMID26.UINT16[L]
#define RSCAN0TMID26LL RSCAN0.TMID26.UINT8[LL]
#define RSCAN0TMID26LH RSCAN0.TMID26.UINT8[LH]
#define RSCAN0TMID26H RSCAN0.TMID26.UINT16[H]
#define RSCAN0TMID26HL RSCAN0.TMID26.UINT8[HL]
#define RSCAN0TMID26HH RSCAN0.TMID26.UINT8[HH]
#define RSCAN0TMPTR26 RSCAN0.TMPTR26.UINT32
#define RSCAN0TMPTR26L RSCAN0.TMPTR26.UINT16[L]
#define RSCAN0TMPTR26LL RSCAN0.TMPTR26.UINT8[LL]
#define RSCAN0TMPTR26LH RSCAN0.TMPTR26.UINT8[LH]
#define RSCAN0TMPTR26H RSCAN0.TMPTR26.UINT16[H]
#define RSCAN0TMPTR26HL RSCAN0.TMPTR26.UINT8[HL]
#define RSCAN0TMPTR26HH RSCAN0.TMPTR26.UINT8[HH]
#define RSCAN0TMDF026 RSCAN0.TMDF026.UINT32
#define RSCAN0TMDF026L RSCAN0.TMDF026.UINT16[L]
#define RSCAN0TMDF026LL RSCAN0.TMDF026.UINT8[LL]
#define RSCAN0TMDF026LH RSCAN0.TMDF026.UINT8[LH]
#define RSCAN0TMDF026H RSCAN0.TMDF026.UINT16[H]
#define RSCAN0TMDF026HL RSCAN0.TMDF026.UINT8[HL]
#define RSCAN0TMDF026HH RSCAN0.TMDF026.UINT8[HH]
#define RSCAN0TMDF126 RSCAN0.TMDF126.UINT32
#define RSCAN0TMDF126L RSCAN0.TMDF126.UINT16[L]
#define RSCAN0TMDF126LL RSCAN0.TMDF126.UINT8[LL]
#define RSCAN0TMDF126LH RSCAN0.TMDF126.UINT8[LH]
#define RSCAN0TMDF126H RSCAN0.TMDF126.UINT16[H]
#define RSCAN0TMDF126HL RSCAN0.TMDF126.UINT8[HL]
#define RSCAN0TMDF126HH RSCAN0.TMDF126.UINT8[HH]
#define RSCAN0TMID27 RSCAN0.TMID27.UINT32
#define RSCAN0TMID27L RSCAN0.TMID27.UINT16[L]
#define RSCAN0TMID27LL RSCAN0.TMID27.UINT8[LL]
#define RSCAN0TMID27LH RSCAN0.TMID27.UINT8[LH]
#define RSCAN0TMID27H RSCAN0.TMID27.UINT16[H]
#define RSCAN0TMID27HL RSCAN0.TMID27.UINT8[HL]
#define RSCAN0TMID27HH RSCAN0.TMID27.UINT8[HH]
#define RSCAN0TMPTR27 RSCAN0.TMPTR27.UINT32
#define RSCAN0TMPTR27L RSCAN0.TMPTR27.UINT16[L]
#define RSCAN0TMPTR27LL RSCAN0.TMPTR27.UINT8[LL]
#define RSCAN0TMPTR27LH RSCAN0.TMPTR27.UINT8[LH]
#define RSCAN0TMPTR27H RSCAN0.TMPTR27.UINT16[H]
#define RSCAN0TMPTR27HL RSCAN0.TMPTR27.UINT8[HL]
#define RSCAN0TMPTR27HH RSCAN0.TMPTR27.UINT8[HH]
#define RSCAN0TMDF027 RSCAN0.TMDF027.UINT32
#define RSCAN0TMDF027L RSCAN0.TMDF027.UINT16[L]
#define RSCAN0TMDF027LL RSCAN0.TMDF027.UINT8[LL]
#define RSCAN0TMDF027LH RSCAN0.TMDF027.UINT8[LH]
#define RSCAN0TMDF027H RSCAN0.TMDF027.UINT16[H]
#define RSCAN0TMDF027HL RSCAN0.TMDF027.UINT8[HL]
#define RSCAN0TMDF027HH RSCAN0.TMDF027.UINT8[HH]
#define RSCAN0TMDF127 RSCAN0.TMDF127.UINT32
#define RSCAN0TMDF127L RSCAN0.TMDF127.UINT16[L]
#define RSCAN0TMDF127LL RSCAN0.TMDF127.UINT8[LL]
#define RSCAN0TMDF127LH RSCAN0.TMDF127.UINT8[LH]
#define RSCAN0TMDF127H RSCAN0.TMDF127.UINT16[H]
#define RSCAN0TMDF127HL RSCAN0.TMDF127.UINT8[HL]
#define RSCAN0TMDF127HH RSCAN0.TMDF127.UINT8[HH]
#define RSCAN0TMID28 RSCAN0.TMID28.UINT32
#define RSCAN0TMID28L RSCAN0.TMID28.UINT16[L]
#define RSCAN0TMID28LL RSCAN0.TMID28.UINT8[LL]
#define RSCAN0TMID28LH RSCAN0.TMID28.UINT8[LH]
#define RSCAN0TMID28H RSCAN0.TMID28.UINT16[H]
#define RSCAN0TMID28HL RSCAN0.TMID28.UINT8[HL]
#define RSCAN0TMID28HH RSCAN0.TMID28.UINT8[HH]
#define RSCAN0TMPTR28 RSCAN0.TMPTR28.UINT32
#define RSCAN0TMPTR28L RSCAN0.TMPTR28.UINT16[L]
#define RSCAN0TMPTR28LL RSCAN0.TMPTR28.UINT8[LL]
#define RSCAN0TMPTR28LH RSCAN0.TMPTR28.UINT8[LH]
#define RSCAN0TMPTR28H RSCAN0.TMPTR28.UINT16[H]
#define RSCAN0TMPTR28HL RSCAN0.TMPTR28.UINT8[HL]
#define RSCAN0TMPTR28HH RSCAN0.TMPTR28.UINT8[HH]
#define RSCAN0TMDF028 RSCAN0.TMDF028.UINT32
#define RSCAN0TMDF028L RSCAN0.TMDF028.UINT16[L]
#define RSCAN0TMDF028LL RSCAN0.TMDF028.UINT8[LL]
#define RSCAN0TMDF028LH RSCAN0.TMDF028.UINT8[LH]
#define RSCAN0TMDF028H RSCAN0.TMDF028.UINT16[H]
#define RSCAN0TMDF028HL RSCAN0.TMDF028.UINT8[HL]
#define RSCAN0TMDF028HH RSCAN0.TMDF028.UINT8[HH]
#define RSCAN0TMDF128 RSCAN0.TMDF128.UINT32
#define RSCAN0TMDF128L RSCAN0.TMDF128.UINT16[L]
#define RSCAN0TMDF128LL RSCAN0.TMDF128.UINT8[LL]
#define RSCAN0TMDF128LH RSCAN0.TMDF128.UINT8[LH]
#define RSCAN0TMDF128H RSCAN0.TMDF128.UINT16[H]
#define RSCAN0TMDF128HL RSCAN0.TMDF128.UINT8[HL]
#define RSCAN0TMDF128HH RSCAN0.TMDF128.UINT8[HH]
#define RSCAN0TMID29 RSCAN0.TMID29.UINT32
#define RSCAN0TMID29L RSCAN0.TMID29.UINT16[L]
#define RSCAN0TMID29LL RSCAN0.TMID29.UINT8[LL]
#define RSCAN0TMID29LH RSCAN0.TMID29.UINT8[LH]
#define RSCAN0TMID29H RSCAN0.TMID29.UINT16[H]
#define RSCAN0TMID29HL RSCAN0.TMID29.UINT8[HL]
#define RSCAN0TMID29HH RSCAN0.TMID29.UINT8[HH]
#define RSCAN0TMPTR29 RSCAN0.TMPTR29.UINT32
#define RSCAN0TMPTR29L RSCAN0.TMPTR29.UINT16[L]
#define RSCAN0TMPTR29LL RSCAN0.TMPTR29.UINT8[LL]
#define RSCAN0TMPTR29LH RSCAN0.TMPTR29.UINT8[LH]
#define RSCAN0TMPTR29H RSCAN0.TMPTR29.UINT16[H]
#define RSCAN0TMPTR29HL RSCAN0.TMPTR29.UINT8[HL]
#define RSCAN0TMPTR29HH RSCAN0.TMPTR29.UINT8[HH]
#define RSCAN0TMDF029 RSCAN0.TMDF029.UINT32
#define RSCAN0TMDF029L RSCAN0.TMDF029.UINT16[L]
#define RSCAN0TMDF029LL RSCAN0.TMDF029.UINT8[LL]
#define RSCAN0TMDF029LH RSCAN0.TMDF029.UINT8[LH]
#define RSCAN0TMDF029H RSCAN0.TMDF029.UINT16[H]
#define RSCAN0TMDF029HL RSCAN0.TMDF029.UINT8[HL]
#define RSCAN0TMDF029HH RSCAN0.TMDF029.UINT8[HH]
#define RSCAN0TMDF129 RSCAN0.TMDF129.UINT32
#define RSCAN0TMDF129L RSCAN0.TMDF129.UINT16[L]
#define RSCAN0TMDF129LL RSCAN0.TMDF129.UINT8[LL]
#define RSCAN0TMDF129LH RSCAN0.TMDF129.UINT8[LH]
#define RSCAN0TMDF129H RSCAN0.TMDF129.UINT16[H]
#define RSCAN0TMDF129HL RSCAN0.TMDF129.UINT8[HL]
#define RSCAN0TMDF129HH RSCAN0.TMDF129.UINT8[HH]
#define RSCAN0TMID30 RSCAN0.TMID30.UINT32
#define RSCAN0TMID30L RSCAN0.TMID30.UINT16[L]
#define RSCAN0TMID30LL RSCAN0.TMID30.UINT8[LL]
#define RSCAN0TMID30LH RSCAN0.TMID30.UINT8[LH]
#define RSCAN0TMID30H RSCAN0.TMID30.UINT16[H]
#define RSCAN0TMID30HL RSCAN0.TMID30.UINT8[HL]
#define RSCAN0TMID30HH RSCAN0.TMID30.UINT8[HH]
#define RSCAN0TMPTR30 RSCAN0.TMPTR30.UINT32
#define RSCAN0TMPTR30L RSCAN0.TMPTR30.UINT16[L]
#define RSCAN0TMPTR30LL RSCAN0.TMPTR30.UINT8[LL]
#define RSCAN0TMPTR30LH RSCAN0.TMPTR30.UINT8[LH]
#define RSCAN0TMPTR30H RSCAN0.TMPTR30.UINT16[H]
#define RSCAN0TMPTR30HL RSCAN0.TMPTR30.UINT8[HL]
#define RSCAN0TMPTR30HH RSCAN0.TMPTR30.UINT8[HH]
#define RSCAN0TMDF030 RSCAN0.TMDF030.UINT32
#define RSCAN0TMDF030L RSCAN0.TMDF030.UINT16[L]
#define RSCAN0TMDF030LL RSCAN0.TMDF030.UINT8[LL]
#define RSCAN0TMDF030LH RSCAN0.TMDF030.UINT8[LH]
#define RSCAN0TMDF030H RSCAN0.TMDF030.UINT16[H]
#define RSCAN0TMDF030HL RSCAN0.TMDF030.UINT8[HL]
#define RSCAN0TMDF030HH RSCAN0.TMDF030.UINT8[HH]
#define RSCAN0TMDF130 RSCAN0.TMDF130.UINT32
#define RSCAN0TMDF130L RSCAN0.TMDF130.UINT16[L]
#define RSCAN0TMDF130LL RSCAN0.TMDF130.UINT8[LL]
#define RSCAN0TMDF130LH RSCAN0.TMDF130.UINT8[LH]
#define RSCAN0TMDF130H RSCAN0.TMDF130.UINT16[H]
#define RSCAN0TMDF130HL RSCAN0.TMDF130.UINT8[HL]
#define RSCAN0TMDF130HH RSCAN0.TMDF130.UINT8[HH]
#define RSCAN0TMID31 RSCAN0.TMID31.UINT32
#define RSCAN0TMID31L RSCAN0.TMID31.UINT16[L]
#define RSCAN0TMID31LL RSCAN0.TMID31.UINT8[LL]
#define RSCAN0TMID31LH RSCAN0.TMID31.UINT8[LH]
#define RSCAN0TMID31H RSCAN0.TMID31.UINT16[H]
#define RSCAN0TMID31HL RSCAN0.TMID31.UINT8[HL]
#define RSCAN0TMID31HH RSCAN0.TMID31.UINT8[HH]
#define RSCAN0TMPTR31 RSCAN0.TMPTR31.UINT32
#define RSCAN0TMPTR31L RSCAN0.TMPTR31.UINT16[L]
#define RSCAN0TMPTR31LL RSCAN0.TMPTR31.UINT8[LL]
#define RSCAN0TMPTR31LH RSCAN0.TMPTR31.UINT8[LH]
#define RSCAN0TMPTR31H RSCAN0.TMPTR31.UINT16[H]
#define RSCAN0TMPTR31HL RSCAN0.TMPTR31.UINT8[HL]
#define RSCAN0TMPTR31HH RSCAN0.TMPTR31.UINT8[HH]
#define RSCAN0TMDF031 RSCAN0.TMDF031.UINT32
#define RSCAN0TMDF031L RSCAN0.TMDF031.UINT16[L]
#define RSCAN0TMDF031LL RSCAN0.TMDF031.UINT8[LL]
#define RSCAN0TMDF031LH RSCAN0.TMDF031.UINT8[LH]
#define RSCAN0TMDF031H RSCAN0.TMDF031.UINT16[H]
#define RSCAN0TMDF031HL RSCAN0.TMDF031.UINT8[HL]
#define RSCAN0TMDF031HH RSCAN0.TMDF031.UINT8[HH]
#define RSCAN0TMDF131 RSCAN0.TMDF131.UINT32
#define RSCAN0TMDF131L RSCAN0.TMDF131.UINT16[L]
#define RSCAN0TMDF131LL RSCAN0.TMDF131.UINT8[LL]
#define RSCAN0TMDF131LH RSCAN0.TMDF131.UINT8[LH]
#define RSCAN0TMDF131H RSCAN0.TMDF131.UINT16[H]
#define RSCAN0TMDF131HL RSCAN0.TMDF131.UINT8[HL]
#define RSCAN0TMDF131HH RSCAN0.TMDF131.UINT8[HH]
#define RSCAN0TMID32 RSCAN0.TMID32.UINT32
#define RSCAN0TMID32L RSCAN0.TMID32.UINT16[L]
#define RSCAN0TMID32LL RSCAN0.TMID32.UINT8[LL]
#define RSCAN0TMID32LH RSCAN0.TMID32.UINT8[LH]
#define RSCAN0TMID32H RSCAN0.TMID32.UINT16[H]
#define RSCAN0TMID32HL RSCAN0.TMID32.UINT8[HL]
#define RSCAN0TMID32HH RSCAN0.TMID32.UINT8[HH]
#define RSCAN0TMPTR32 RSCAN0.TMPTR32.UINT32
#define RSCAN0TMPTR32L RSCAN0.TMPTR32.UINT16[L]
#define RSCAN0TMPTR32LL RSCAN0.TMPTR32.UINT8[LL]
#define RSCAN0TMPTR32LH RSCAN0.TMPTR32.UINT8[LH]
#define RSCAN0TMPTR32H RSCAN0.TMPTR32.UINT16[H]
#define RSCAN0TMPTR32HL RSCAN0.TMPTR32.UINT8[HL]
#define RSCAN0TMPTR32HH RSCAN0.TMPTR32.UINT8[HH]
#define RSCAN0TMDF032 RSCAN0.TMDF032.UINT32
#define RSCAN0TMDF032L RSCAN0.TMDF032.UINT16[L]
#define RSCAN0TMDF032LL RSCAN0.TMDF032.UINT8[LL]
#define RSCAN0TMDF032LH RSCAN0.TMDF032.UINT8[LH]
#define RSCAN0TMDF032H RSCAN0.TMDF032.UINT16[H]
#define RSCAN0TMDF032HL RSCAN0.TMDF032.UINT8[HL]
#define RSCAN0TMDF032HH RSCAN0.TMDF032.UINT8[HH]
#define RSCAN0TMDF132 RSCAN0.TMDF132.UINT32
#define RSCAN0TMDF132L RSCAN0.TMDF132.UINT16[L]
#define RSCAN0TMDF132LL RSCAN0.TMDF132.UINT8[LL]
#define RSCAN0TMDF132LH RSCAN0.TMDF132.UINT8[LH]
#define RSCAN0TMDF132H RSCAN0.TMDF132.UINT16[H]
#define RSCAN0TMDF132HL RSCAN0.TMDF132.UINT8[HL]
#define RSCAN0TMDF132HH RSCAN0.TMDF132.UINT8[HH]
#define RSCAN0TMID33 RSCAN0.TMID33.UINT32
#define RSCAN0TMID33L RSCAN0.TMID33.UINT16[L]
#define RSCAN0TMID33LL RSCAN0.TMID33.UINT8[LL]
#define RSCAN0TMID33LH RSCAN0.TMID33.UINT8[LH]
#define RSCAN0TMID33H RSCAN0.TMID33.UINT16[H]
#define RSCAN0TMID33HL RSCAN0.TMID33.UINT8[HL]
#define RSCAN0TMID33HH RSCAN0.TMID33.UINT8[HH]
#define RSCAN0TMPTR33 RSCAN0.TMPTR33.UINT32
#define RSCAN0TMPTR33L RSCAN0.TMPTR33.UINT16[L]
#define RSCAN0TMPTR33LL RSCAN0.TMPTR33.UINT8[LL]
#define RSCAN0TMPTR33LH RSCAN0.TMPTR33.UINT8[LH]
#define RSCAN0TMPTR33H RSCAN0.TMPTR33.UINT16[H]
#define RSCAN0TMPTR33HL RSCAN0.TMPTR33.UINT8[HL]
#define RSCAN0TMPTR33HH RSCAN0.TMPTR33.UINT8[HH]
#define RSCAN0TMDF033 RSCAN0.TMDF033.UINT32
#define RSCAN0TMDF033L RSCAN0.TMDF033.UINT16[L]
#define RSCAN0TMDF033LL RSCAN0.TMDF033.UINT8[LL]
#define RSCAN0TMDF033LH RSCAN0.TMDF033.UINT8[LH]
#define RSCAN0TMDF033H RSCAN0.TMDF033.UINT16[H]
#define RSCAN0TMDF033HL RSCAN0.TMDF033.UINT8[HL]
#define RSCAN0TMDF033HH RSCAN0.TMDF033.UINT8[HH]
#define RSCAN0TMDF133 RSCAN0.TMDF133.UINT32
#define RSCAN0TMDF133L RSCAN0.TMDF133.UINT16[L]
#define RSCAN0TMDF133LL RSCAN0.TMDF133.UINT8[LL]
#define RSCAN0TMDF133LH RSCAN0.TMDF133.UINT8[LH]
#define RSCAN0TMDF133H RSCAN0.TMDF133.UINT16[H]
#define RSCAN0TMDF133HL RSCAN0.TMDF133.UINT8[HL]
#define RSCAN0TMDF133HH RSCAN0.TMDF133.UINT8[HH]
#define RSCAN0TMID34 RSCAN0.TMID34.UINT32
#define RSCAN0TMID34L RSCAN0.TMID34.UINT16[L]
#define RSCAN0TMID34LL RSCAN0.TMID34.UINT8[LL]
#define RSCAN0TMID34LH RSCAN0.TMID34.UINT8[LH]
#define RSCAN0TMID34H RSCAN0.TMID34.UINT16[H]
#define RSCAN0TMID34HL RSCAN0.TMID34.UINT8[HL]
#define RSCAN0TMID34HH RSCAN0.TMID34.UINT8[HH]
#define RSCAN0TMPTR34 RSCAN0.TMPTR34.UINT32
#define RSCAN0TMPTR34L RSCAN0.TMPTR34.UINT16[L]
#define RSCAN0TMPTR34LL RSCAN0.TMPTR34.UINT8[LL]
#define RSCAN0TMPTR34LH RSCAN0.TMPTR34.UINT8[LH]
#define RSCAN0TMPTR34H RSCAN0.TMPTR34.UINT16[H]
#define RSCAN0TMPTR34HL RSCAN0.TMPTR34.UINT8[HL]
#define RSCAN0TMPTR34HH RSCAN0.TMPTR34.UINT8[HH]
#define RSCAN0TMDF034 RSCAN0.TMDF034.UINT32
#define RSCAN0TMDF034L RSCAN0.TMDF034.UINT16[L]
#define RSCAN0TMDF034LL RSCAN0.TMDF034.UINT8[LL]
#define RSCAN0TMDF034LH RSCAN0.TMDF034.UINT8[LH]
#define RSCAN0TMDF034H RSCAN0.TMDF034.UINT16[H]
#define RSCAN0TMDF034HL RSCAN0.TMDF034.UINT8[HL]
#define RSCAN0TMDF034HH RSCAN0.TMDF034.UINT8[HH]
#define RSCAN0TMDF134 RSCAN0.TMDF134.UINT32
#define RSCAN0TMDF134L RSCAN0.TMDF134.UINT16[L]
#define RSCAN0TMDF134LL RSCAN0.TMDF134.UINT8[LL]
#define RSCAN0TMDF134LH RSCAN0.TMDF134.UINT8[LH]
#define RSCAN0TMDF134H RSCAN0.TMDF134.UINT16[H]
#define RSCAN0TMDF134HL RSCAN0.TMDF134.UINT8[HL]
#define RSCAN0TMDF134HH RSCAN0.TMDF134.UINT8[HH]
#define RSCAN0TMID35 RSCAN0.TMID35.UINT32
#define RSCAN0TMID35L RSCAN0.TMID35.UINT16[L]
#define RSCAN0TMID35LL RSCAN0.TMID35.UINT8[LL]
#define RSCAN0TMID35LH RSCAN0.TMID35.UINT8[LH]
#define RSCAN0TMID35H RSCAN0.TMID35.UINT16[H]
#define RSCAN0TMID35HL RSCAN0.TMID35.UINT8[HL]
#define RSCAN0TMID35HH RSCAN0.TMID35.UINT8[HH]
#define RSCAN0TMPTR35 RSCAN0.TMPTR35.UINT32
#define RSCAN0TMPTR35L RSCAN0.TMPTR35.UINT16[L]
#define RSCAN0TMPTR35LL RSCAN0.TMPTR35.UINT8[LL]
#define RSCAN0TMPTR35LH RSCAN0.TMPTR35.UINT8[LH]
#define RSCAN0TMPTR35H RSCAN0.TMPTR35.UINT16[H]
#define RSCAN0TMPTR35HL RSCAN0.TMPTR35.UINT8[HL]
#define RSCAN0TMPTR35HH RSCAN0.TMPTR35.UINT8[HH]
#define RSCAN0TMDF035 RSCAN0.TMDF035.UINT32
#define RSCAN0TMDF035L RSCAN0.TMDF035.UINT16[L]
#define RSCAN0TMDF035LL RSCAN0.TMDF035.UINT8[LL]
#define RSCAN0TMDF035LH RSCAN0.TMDF035.UINT8[LH]
#define RSCAN0TMDF035H RSCAN0.TMDF035.UINT16[H]
#define RSCAN0TMDF035HL RSCAN0.TMDF035.UINT8[HL]
#define RSCAN0TMDF035HH RSCAN0.TMDF035.UINT8[HH]
#define RSCAN0TMDF135 RSCAN0.TMDF135.UINT32
#define RSCAN0TMDF135L RSCAN0.TMDF135.UINT16[L]
#define RSCAN0TMDF135LL RSCAN0.TMDF135.UINT8[LL]
#define RSCAN0TMDF135LH RSCAN0.TMDF135.UINT8[LH]
#define RSCAN0TMDF135H RSCAN0.TMDF135.UINT16[H]
#define RSCAN0TMDF135HL RSCAN0.TMDF135.UINT8[HL]
#define RSCAN0TMDF135HH RSCAN0.TMDF135.UINT8[HH]
#define RSCAN0TMID36 RSCAN0.TMID36.UINT32
#define RSCAN0TMID36L RSCAN0.TMID36.UINT16[L]
#define RSCAN0TMID36LL RSCAN0.TMID36.UINT8[LL]
#define RSCAN0TMID36LH RSCAN0.TMID36.UINT8[LH]
#define RSCAN0TMID36H RSCAN0.TMID36.UINT16[H]
#define RSCAN0TMID36HL RSCAN0.TMID36.UINT8[HL]
#define RSCAN0TMID36HH RSCAN0.TMID36.UINT8[HH]
#define RSCAN0TMPTR36 RSCAN0.TMPTR36.UINT32
#define RSCAN0TMPTR36L RSCAN0.TMPTR36.UINT16[L]
#define RSCAN0TMPTR36LL RSCAN0.TMPTR36.UINT8[LL]
#define RSCAN0TMPTR36LH RSCAN0.TMPTR36.UINT8[LH]
#define RSCAN0TMPTR36H RSCAN0.TMPTR36.UINT16[H]
#define RSCAN0TMPTR36HL RSCAN0.TMPTR36.UINT8[HL]
#define RSCAN0TMPTR36HH RSCAN0.TMPTR36.UINT8[HH]
#define RSCAN0TMDF036 RSCAN0.TMDF036.UINT32
#define RSCAN0TMDF036L RSCAN0.TMDF036.UINT16[L]
#define RSCAN0TMDF036LL RSCAN0.TMDF036.UINT8[LL]
#define RSCAN0TMDF036LH RSCAN0.TMDF036.UINT8[LH]
#define RSCAN0TMDF036H RSCAN0.TMDF036.UINT16[H]
#define RSCAN0TMDF036HL RSCAN0.TMDF036.UINT8[HL]
#define RSCAN0TMDF036HH RSCAN0.TMDF036.UINT8[HH]
#define RSCAN0TMDF136 RSCAN0.TMDF136.UINT32
#define RSCAN0TMDF136L RSCAN0.TMDF136.UINT16[L]
#define RSCAN0TMDF136LL RSCAN0.TMDF136.UINT8[LL]
#define RSCAN0TMDF136LH RSCAN0.TMDF136.UINT8[LH]
#define RSCAN0TMDF136H RSCAN0.TMDF136.UINT16[H]
#define RSCAN0TMDF136HL RSCAN0.TMDF136.UINT8[HL]
#define RSCAN0TMDF136HH RSCAN0.TMDF136.UINT8[HH]
#define RSCAN0TMID37 RSCAN0.TMID37.UINT32
#define RSCAN0TMID37L RSCAN0.TMID37.UINT16[L]
#define RSCAN0TMID37LL RSCAN0.TMID37.UINT8[LL]
#define RSCAN0TMID37LH RSCAN0.TMID37.UINT8[LH]
#define RSCAN0TMID37H RSCAN0.TMID37.UINT16[H]
#define RSCAN0TMID37HL RSCAN0.TMID37.UINT8[HL]
#define RSCAN0TMID37HH RSCAN0.TMID37.UINT8[HH]
#define RSCAN0TMPTR37 RSCAN0.TMPTR37.UINT32
#define RSCAN0TMPTR37L RSCAN0.TMPTR37.UINT16[L]
#define RSCAN0TMPTR37LL RSCAN0.TMPTR37.UINT8[LL]
#define RSCAN0TMPTR37LH RSCAN0.TMPTR37.UINT8[LH]
#define RSCAN0TMPTR37H RSCAN0.TMPTR37.UINT16[H]
#define RSCAN0TMPTR37HL RSCAN0.TMPTR37.UINT8[HL]
#define RSCAN0TMPTR37HH RSCAN0.TMPTR37.UINT8[HH]
#define RSCAN0TMDF037 RSCAN0.TMDF037.UINT32
#define RSCAN0TMDF037L RSCAN0.TMDF037.UINT16[L]
#define RSCAN0TMDF037LL RSCAN0.TMDF037.UINT8[LL]
#define RSCAN0TMDF037LH RSCAN0.TMDF037.UINT8[LH]
#define RSCAN0TMDF037H RSCAN0.TMDF037.UINT16[H]
#define RSCAN0TMDF037HL RSCAN0.TMDF037.UINT8[HL]
#define RSCAN0TMDF037HH RSCAN0.TMDF037.UINT8[HH]
#define RSCAN0TMDF137 RSCAN0.TMDF137.UINT32
#define RSCAN0TMDF137L RSCAN0.TMDF137.UINT16[L]
#define RSCAN0TMDF137LL RSCAN0.TMDF137.UINT8[LL]
#define RSCAN0TMDF137LH RSCAN0.TMDF137.UINT8[LH]
#define RSCAN0TMDF137H RSCAN0.TMDF137.UINT16[H]
#define RSCAN0TMDF137HL RSCAN0.TMDF137.UINT8[HL]
#define RSCAN0TMDF137HH RSCAN0.TMDF137.UINT8[HH]
#define RSCAN0TMID38 RSCAN0.TMID38.UINT32
#define RSCAN0TMID38L RSCAN0.TMID38.UINT16[L]
#define RSCAN0TMID38LL RSCAN0.TMID38.UINT8[LL]
#define RSCAN0TMID38LH RSCAN0.TMID38.UINT8[LH]
#define RSCAN0TMID38H RSCAN0.TMID38.UINT16[H]
#define RSCAN0TMID38HL RSCAN0.TMID38.UINT8[HL]
#define RSCAN0TMID38HH RSCAN0.TMID38.UINT8[HH]
#define RSCAN0TMPTR38 RSCAN0.TMPTR38.UINT32
#define RSCAN0TMPTR38L RSCAN0.TMPTR38.UINT16[L]
#define RSCAN0TMPTR38LL RSCAN0.TMPTR38.UINT8[LL]
#define RSCAN0TMPTR38LH RSCAN0.TMPTR38.UINT8[LH]
#define RSCAN0TMPTR38H RSCAN0.TMPTR38.UINT16[H]
#define RSCAN0TMPTR38HL RSCAN0.TMPTR38.UINT8[HL]
#define RSCAN0TMPTR38HH RSCAN0.TMPTR38.UINT8[HH]
#define RSCAN0TMDF038 RSCAN0.TMDF038.UINT32
#define RSCAN0TMDF038L RSCAN0.TMDF038.UINT16[L]
#define RSCAN0TMDF038LL RSCAN0.TMDF038.UINT8[LL]
#define RSCAN0TMDF038LH RSCAN0.TMDF038.UINT8[LH]
#define RSCAN0TMDF038H RSCAN0.TMDF038.UINT16[H]
#define RSCAN0TMDF038HL RSCAN0.TMDF038.UINT8[HL]
#define RSCAN0TMDF038HH RSCAN0.TMDF038.UINT8[HH]
#define RSCAN0TMDF138 RSCAN0.TMDF138.UINT32
#define RSCAN0TMDF138L RSCAN0.TMDF138.UINT16[L]
#define RSCAN0TMDF138LL RSCAN0.TMDF138.UINT8[LL]
#define RSCAN0TMDF138LH RSCAN0.TMDF138.UINT8[LH]
#define RSCAN0TMDF138H RSCAN0.TMDF138.UINT16[H]
#define RSCAN0TMDF138HL RSCAN0.TMDF138.UINT8[HL]
#define RSCAN0TMDF138HH RSCAN0.TMDF138.UINT8[HH]
#define RSCAN0TMID39 RSCAN0.TMID39.UINT32
#define RSCAN0TMID39L RSCAN0.TMID39.UINT16[L]
#define RSCAN0TMID39LL RSCAN0.TMID39.UINT8[LL]
#define RSCAN0TMID39LH RSCAN0.TMID39.UINT8[LH]
#define RSCAN0TMID39H RSCAN0.TMID39.UINT16[H]
#define RSCAN0TMID39HL RSCAN0.TMID39.UINT8[HL]
#define RSCAN0TMID39HH RSCAN0.TMID39.UINT8[HH]
#define RSCAN0TMPTR39 RSCAN0.TMPTR39.UINT32
#define RSCAN0TMPTR39L RSCAN0.TMPTR39.UINT16[L]
#define RSCAN0TMPTR39LL RSCAN0.TMPTR39.UINT8[LL]
#define RSCAN0TMPTR39LH RSCAN0.TMPTR39.UINT8[LH]
#define RSCAN0TMPTR39H RSCAN0.TMPTR39.UINT16[H]
#define RSCAN0TMPTR39HL RSCAN0.TMPTR39.UINT8[HL]
#define RSCAN0TMPTR39HH RSCAN0.TMPTR39.UINT8[HH]
#define RSCAN0TMDF039 RSCAN0.TMDF039.UINT32
#define RSCAN0TMDF039L RSCAN0.TMDF039.UINT16[L]
#define RSCAN0TMDF039LL RSCAN0.TMDF039.UINT8[LL]
#define RSCAN0TMDF039LH RSCAN0.TMDF039.UINT8[LH]
#define RSCAN0TMDF039H RSCAN0.TMDF039.UINT16[H]
#define RSCAN0TMDF039HL RSCAN0.TMDF039.UINT8[HL]
#define RSCAN0TMDF039HH RSCAN0.TMDF039.UINT8[HH]
#define RSCAN0TMDF139 RSCAN0.TMDF139.UINT32
#define RSCAN0TMDF139L RSCAN0.TMDF139.UINT16[L]
#define RSCAN0TMDF139LL RSCAN0.TMDF139.UINT8[LL]
#define RSCAN0TMDF139LH RSCAN0.TMDF139.UINT8[LH]
#define RSCAN0TMDF139H RSCAN0.TMDF139.UINT16[H]
#define RSCAN0TMDF139HL RSCAN0.TMDF139.UINT8[HL]
#define RSCAN0TMDF139HH RSCAN0.TMDF139.UINT8[HH]
#define RSCAN0TMID40 RSCAN0.TMID40.UINT32
#define RSCAN0TMID40L RSCAN0.TMID40.UINT16[L]
#define RSCAN0TMID40LL RSCAN0.TMID40.UINT8[LL]
#define RSCAN0TMID40LH RSCAN0.TMID40.UINT8[LH]
#define RSCAN0TMID40H RSCAN0.TMID40.UINT16[H]
#define RSCAN0TMID40HL RSCAN0.TMID40.UINT8[HL]
#define RSCAN0TMID40HH RSCAN0.TMID40.UINT8[HH]
#define RSCAN0TMPTR40 RSCAN0.TMPTR40.UINT32
#define RSCAN0TMPTR40L RSCAN0.TMPTR40.UINT16[L]
#define RSCAN0TMPTR40LL RSCAN0.TMPTR40.UINT8[LL]
#define RSCAN0TMPTR40LH RSCAN0.TMPTR40.UINT8[LH]
#define RSCAN0TMPTR40H RSCAN0.TMPTR40.UINT16[H]
#define RSCAN0TMPTR40HL RSCAN0.TMPTR40.UINT8[HL]
#define RSCAN0TMPTR40HH RSCAN0.TMPTR40.UINT8[HH]
#define RSCAN0TMDF040 RSCAN0.TMDF040.UINT32
#define RSCAN0TMDF040L RSCAN0.TMDF040.UINT16[L]
#define RSCAN0TMDF040LL RSCAN0.TMDF040.UINT8[LL]
#define RSCAN0TMDF040LH RSCAN0.TMDF040.UINT8[LH]
#define RSCAN0TMDF040H RSCAN0.TMDF040.UINT16[H]
#define RSCAN0TMDF040HL RSCAN0.TMDF040.UINT8[HL]
#define RSCAN0TMDF040HH RSCAN0.TMDF040.UINT8[HH]
#define RSCAN0TMDF140 RSCAN0.TMDF140.UINT32
#define RSCAN0TMDF140L RSCAN0.TMDF140.UINT16[L]
#define RSCAN0TMDF140LL RSCAN0.TMDF140.UINT8[LL]
#define RSCAN0TMDF140LH RSCAN0.TMDF140.UINT8[LH]
#define RSCAN0TMDF140H RSCAN0.TMDF140.UINT16[H]
#define RSCAN0TMDF140HL RSCAN0.TMDF140.UINT8[HL]
#define RSCAN0TMDF140HH RSCAN0.TMDF140.UINT8[HH]
#define RSCAN0TMID41 RSCAN0.TMID41.UINT32
#define RSCAN0TMID41L RSCAN0.TMID41.UINT16[L]
#define RSCAN0TMID41LL RSCAN0.TMID41.UINT8[LL]
#define RSCAN0TMID41LH RSCAN0.TMID41.UINT8[LH]
#define RSCAN0TMID41H RSCAN0.TMID41.UINT16[H]
#define RSCAN0TMID41HL RSCAN0.TMID41.UINT8[HL]
#define RSCAN0TMID41HH RSCAN0.TMID41.UINT8[HH]
#define RSCAN0TMPTR41 RSCAN0.TMPTR41.UINT32
#define RSCAN0TMPTR41L RSCAN0.TMPTR41.UINT16[L]
#define RSCAN0TMPTR41LL RSCAN0.TMPTR41.UINT8[LL]
#define RSCAN0TMPTR41LH RSCAN0.TMPTR41.UINT8[LH]
#define RSCAN0TMPTR41H RSCAN0.TMPTR41.UINT16[H]
#define RSCAN0TMPTR41HL RSCAN0.TMPTR41.UINT8[HL]
#define RSCAN0TMPTR41HH RSCAN0.TMPTR41.UINT8[HH]
#define RSCAN0TMDF041 RSCAN0.TMDF041.UINT32
#define RSCAN0TMDF041L RSCAN0.TMDF041.UINT16[L]
#define RSCAN0TMDF041LL RSCAN0.TMDF041.UINT8[LL]
#define RSCAN0TMDF041LH RSCAN0.TMDF041.UINT8[LH]
#define RSCAN0TMDF041H RSCAN0.TMDF041.UINT16[H]
#define RSCAN0TMDF041HL RSCAN0.TMDF041.UINT8[HL]
#define RSCAN0TMDF041HH RSCAN0.TMDF041.UINT8[HH]
#define RSCAN0TMDF141 RSCAN0.TMDF141.UINT32
#define RSCAN0TMDF141L RSCAN0.TMDF141.UINT16[L]
#define RSCAN0TMDF141LL RSCAN0.TMDF141.UINT8[LL]
#define RSCAN0TMDF141LH RSCAN0.TMDF141.UINT8[LH]
#define RSCAN0TMDF141H RSCAN0.TMDF141.UINT16[H]
#define RSCAN0TMDF141HL RSCAN0.TMDF141.UINT8[HL]
#define RSCAN0TMDF141HH RSCAN0.TMDF141.UINT8[HH]
#define RSCAN0TMID42 RSCAN0.TMID42.UINT32
#define RSCAN0TMID42L RSCAN0.TMID42.UINT16[L]
#define RSCAN0TMID42LL RSCAN0.TMID42.UINT8[LL]
#define RSCAN0TMID42LH RSCAN0.TMID42.UINT8[LH]
#define RSCAN0TMID42H RSCAN0.TMID42.UINT16[H]
#define RSCAN0TMID42HL RSCAN0.TMID42.UINT8[HL]
#define RSCAN0TMID42HH RSCAN0.TMID42.UINT8[HH]
#define RSCAN0TMPTR42 RSCAN0.TMPTR42.UINT32
#define RSCAN0TMPTR42L RSCAN0.TMPTR42.UINT16[L]
#define RSCAN0TMPTR42LL RSCAN0.TMPTR42.UINT8[LL]
#define RSCAN0TMPTR42LH RSCAN0.TMPTR42.UINT8[LH]
#define RSCAN0TMPTR42H RSCAN0.TMPTR42.UINT16[H]
#define RSCAN0TMPTR42HL RSCAN0.TMPTR42.UINT8[HL]
#define RSCAN0TMPTR42HH RSCAN0.TMPTR42.UINT8[HH]
#define RSCAN0TMDF042 RSCAN0.TMDF042.UINT32
#define RSCAN0TMDF042L RSCAN0.TMDF042.UINT16[L]
#define RSCAN0TMDF042LL RSCAN0.TMDF042.UINT8[LL]
#define RSCAN0TMDF042LH RSCAN0.TMDF042.UINT8[LH]
#define RSCAN0TMDF042H RSCAN0.TMDF042.UINT16[H]
#define RSCAN0TMDF042HL RSCAN0.TMDF042.UINT8[HL]
#define RSCAN0TMDF042HH RSCAN0.TMDF042.UINT8[HH]
#define RSCAN0TMDF142 RSCAN0.TMDF142.UINT32
#define RSCAN0TMDF142L RSCAN0.TMDF142.UINT16[L]
#define RSCAN0TMDF142LL RSCAN0.TMDF142.UINT8[LL]
#define RSCAN0TMDF142LH RSCAN0.TMDF142.UINT8[LH]
#define RSCAN0TMDF142H RSCAN0.TMDF142.UINT16[H]
#define RSCAN0TMDF142HL RSCAN0.TMDF142.UINT8[HL]
#define RSCAN0TMDF142HH RSCAN0.TMDF142.UINT8[HH]
#define RSCAN0TMID43 RSCAN0.TMID43.UINT32
#define RSCAN0TMID43L RSCAN0.TMID43.UINT16[L]
#define RSCAN0TMID43LL RSCAN0.TMID43.UINT8[LL]
#define RSCAN0TMID43LH RSCAN0.TMID43.UINT8[LH]
#define RSCAN0TMID43H RSCAN0.TMID43.UINT16[H]
#define RSCAN0TMID43HL RSCAN0.TMID43.UINT8[HL]
#define RSCAN0TMID43HH RSCAN0.TMID43.UINT8[HH]
#define RSCAN0TMPTR43 RSCAN0.TMPTR43.UINT32
#define RSCAN0TMPTR43L RSCAN0.TMPTR43.UINT16[L]
#define RSCAN0TMPTR43LL RSCAN0.TMPTR43.UINT8[LL]
#define RSCAN0TMPTR43LH RSCAN0.TMPTR43.UINT8[LH]
#define RSCAN0TMPTR43H RSCAN0.TMPTR43.UINT16[H]
#define RSCAN0TMPTR43HL RSCAN0.TMPTR43.UINT8[HL]
#define RSCAN0TMPTR43HH RSCAN0.TMPTR43.UINT8[HH]
#define RSCAN0TMDF043 RSCAN0.TMDF043.UINT32
#define RSCAN0TMDF043L RSCAN0.TMDF043.UINT16[L]
#define RSCAN0TMDF043LL RSCAN0.TMDF043.UINT8[LL]
#define RSCAN0TMDF043LH RSCAN0.TMDF043.UINT8[LH]
#define RSCAN0TMDF043H RSCAN0.TMDF043.UINT16[H]
#define RSCAN0TMDF043HL RSCAN0.TMDF043.UINT8[HL]
#define RSCAN0TMDF043HH RSCAN0.TMDF043.UINT8[HH]
#define RSCAN0TMDF143 RSCAN0.TMDF143.UINT32
#define RSCAN0TMDF143L RSCAN0.TMDF143.UINT16[L]
#define RSCAN0TMDF143LL RSCAN0.TMDF143.UINT8[LL]
#define RSCAN0TMDF143LH RSCAN0.TMDF143.UINT8[LH]
#define RSCAN0TMDF143H RSCAN0.TMDF143.UINT16[H]
#define RSCAN0TMDF143HL RSCAN0.TMDF143.UINT8[HL]
#define RSCAN0TMDF143HH RSCAN0.TMDF143.UINT8[HH]
#define RSCAN0TMID44 RSCAN0.TMID44.UINT32
#define RSCAN0TMID44L RSCAN0.TMID44.UINT16[L]
#define RSCAN0TMID44LL RSCAN0.TMID44.UINT8[LL]
#define RSCAN0TMID44LH RSCAN0.TMID44.UINT8[LH]
#define RSCAN0TMID44H RSCAN0.TMID44.UINT16[H]
#define RSCAN0TMID44HL RSCAN0.TMID44.UINT8[HL]
#define RSCAN0TMID44HH RSCAN0.TMID44.UINT8[HH]
#define RSCAN0TMPTR44 RSCAN0.TMPTR44.UINT32
#define RSCAN0TMPTR44L RSCAN0.TMPTR44.UINT16[L]
#define RSCAN0TMPTR44LL RSCAN0.TMPTR44.UINT8[LL]
#define RSCAN0TMPTR44LH RSCAN0.TMPTR44.UINT8[LH]
#define RSCAN0TMPTR44H RSCAN0.TMPTR44.UINT16[H]
#define RSCAN0TMPTR44HL RSCAN0.TMPTR44.UINT8[HL]
#define RSCAN0TMPTR44HH RSCAN0.TMPTR44.UINT8[HH]
#define RSCAN0TMDF044 RSCAN0.TMDF044.UINT32
#define RSCAN0TMDF044L RSCAN0.TMDF044.UINT16[L]
#define RSCAN0TMDF044LL RSCAN0.TMDF044.UINT8[LL]
#define RSCAN0TMDF044LH RSCAN0.TMDF044.UINT8[LH]
#define RSCAN0TMDF044H RSCAN0.TMDF044.UINT16[H]
#define RSCAN0TMDF044HL RSCAN0.TMDF044.UINT8[HL]
#define RSCAN0TMDF044HH RSCAN0.TMDF044.UINT8[HH]
#define RSCAN0TMDF144 RSCAN0.TMDF144.UINT32
#define RSCAN0TMDF144L RSCAN0.TMDF144.UINT16[L]
#define RSCAN0TMDF144LL RSCAN0.TMDF144.UINT8[LL]
#define RSCAN0TMDF144LH RSCAN0.TMDF144.UINT8[LH]
#define RSCAN0TMDF144H RSCAN0.TMDF144.UINT16[H]
#define RSCAN0TMDF144HL RSCAN0.TMDF144.UINT8[HL]
#define RSCAN0TMDF144HH RSCAN0.TMDF144.UINT8[HH]
#define RSCAN0TMID45 RSCAN0.TMID45.UINT32
#define RSCAN0TMID45L RSCAN0.TMID45.UINT16[L]
#define RSCAN0TMID45LL RSCAN0.TMID45.UINT8[LL]
#define RSCAN0TMID45LH RSCAN0.TMID45.UINT8[LH]
#define RSCAN0TMID45H RSCAN0.TMID45.UINT16[H]
#define RSCAN0TMID45HL RSCAN0.TMID45.UINT8[HL]
#define RSCAN0TMID45HH RSCAN0.TMID45.UINT8[HH]
#define RSCAN0TMPTR45 RSCAN0.TMPTR45.UINT32
#define RSCAN0TMPTR45L RSCAN0.TMPTR45.UINT16[L]
#define RSCAN0TMPTR45LL RSCAN0.TMPTR45.UINT8[LL]
#define RSCAN0TMPTR45LH RSCAN0.TMPTR45.UINT8[LH]
#define RSCAN0TMPTR45H RSCAN0.TMPTR45.UINT16[H]
#define RSCAN0TMPTR45HL RSCAN0.TMPTR45.UINT8[HL]
#define RSCAN0TMPTR45HH RSCAN0.TMPTR45.UINT8[HH]
#define RSCAN0TMDF045 RSCAN0.TMDF045.UINT32
#define RSCAN0TMDF045L RSCAN0.TMDF045.UINT16[L]
#define RSCAN0TMDF045LL RSCAN0.TMDF045.UINT8[LL]
#define RSCAN0TMDF045LH RSCAN0.TMDF045.UINT8[LH]
#define RSCAN0TMDF045H RSCAN0.TMDF045.UINT16[H]
#define RSCAN0TMDF045HL RSCAN0.TMDF045.UINT8[HL]
#define RSCAN0TMDF045HH RSCAN0.TMDF045.UINT8[HH]
#define RSCAN0TMDF145 RSCAN0.TMDF145.UINT32
#define RSCAN0TMDF145L RSCAN0.TMDF145.UINT16[L]
#define RSCAN0TMDF145LL RSCAN0.TMDF145.UINT8[LL]
#define RSCAN0TMDF145LH RSCAN0.TMDF145.UINT8[LH]
#define RSCAN0TMDF145H RSCAN0.TMDF145.UINT16[H]
#define RSCAN0TMDF145HL RSCAN0.TMDF145.UINT8[HL]
#define RSCAN0TMDF145HH RSCAN0.TMDF145.UINT8[HH]
#define RSCAN0TMID46 RSCAN0.TMID46.UINT32
#define RSCAN0TMID46L RSCAN0.TMID46.UINT16[L]
#define RSCAN0TMID46LL RSCAN0.TMID46.UINT8[LL]
#define RSCAN0TMID46LH RSCAN0.TMID46.UINT8[LH]
#define RSCAN0TMID46H RSCAN0.TMID46.UINT16[H]
#define RSCAN0TMID46HL RSCAN0.TMID46.UINT8[HL]
#define RSCAN0TMID46HH RSCAN0.TMID46.UINT8[HH]
#define RSCAN0TMPTR46 RSCAN0.TMPTR46.UINT32
#define RSCAN0TMPTR46L RSCAN0.TMPTR46.UINT16[L]
#define RSCAN0TMPTR46LL RSCAN0.TMPTR46.UINT8[LL]
#define RSCAN0TMPTR46LH RSCAN0.TMPTR46.UINT8[LH]
#define RSCAN0TMPTR46H RSCAN0.TMPTR46.UINT16[H]
#define RSCAN0TMPTR46HL RSCAN0.TMPTR46.UINT8[HL]
#define RSCAN0TMPTR46HH RSCAN0.TMPTR46.UINT8[HH]
#define RSCAN0TMDF046 RSCAN0.TMDF046.UINT32
#define RSCAN0TMDF046L RSCAN0.TMDF046.UINT16[L]
#define RSCAN0TMDF046LL RSCAN0.TMDF046.UINT8[LL]
#define RSCAN0TMDF046LH RSCAN0.TMDF046.UINT8[LH]
#define RSCAN0TMDF046H RSCAN0.TMDF046.UINT16[H]
#define RSCAN0TMDF046HL RSCAN0.TMDF046.UINT8[HL]
#define RSCAN0TMDF046HH RSCAN0.TMDF046.UINT8[HH]
#define RSCAN0TMDF146 RSCAN0.TMDF146.UINT32
#define RSCAN0TMDF146L RSCAN0.TMDF146.UINT16[L]
#define RSCAN0TMDF146LL RSCAN0.TMDF146.UINT8[LL]
#define RSCAN0TMDF146LH RSCAN0.TMDF146.UINT8[LH]
#define RSCAN0TMDF146H RSCAN0.TMDF146.UINT16[H]
#define RSCAN0TMDF146HL RSCAN0.TMDF146.UINT8[HL]
#define RSCAN0TMDF146HH RSCAN0.TMDF146.UINT8[HH]
#define RSCAN0TMID47 RSCAN0.TMID47.UINT32
#define RSCAN0TMID47L RSCAN0.TMID47.UINT16[L]
#define RSCAN0TMID47LL RSCAN0.TMID47.UINT8[LL]
#define RSCAN0TMID47LH RSCAN0.TMID47.UINT8[LH]
#define RSCAN0TMID47H RSCAN0.TMID47.UINT16[H]
#define RSCAN0TMID47HL RSCAN0.TMID47.UINT8[HL]
#define RSCAN0TMID47HH RSCAN0.TMID47.UINT8[HH]
#define RSCAN0TMPTR47 RSCAN0.TMPTR47.UINT32
#define RSCAN0TMPTR47L RSCAN0.TMPTR47.UINT16[L]
#define RSCAN0TMPTR47LL RSCAN0.TMPTR47.UINT8[LL]
#define RSCAN0TMPTR47LH RSCAN0.TMPTR47.UINT8[LH]
#define RSCAN0TMPTR47H RSCAN0.TMPTR47.UINT16[H]
#define RSCAN0TMPTR47HL RSCAN0.TMPTR47.UINT8[HL]
#define RSCAN0TMPTR47HH RSCAN0.TMPTR47.UINT8[HH]
#define RSCAN0TMDF047 RSCAN0.TMDF047.UINT32
#define RSCAN0TMDF047L RSCAN0.TMDF047.UINT16[L]
#define RSCAN0TMDF047LL RSCAN0.TMDF047.UINT8[LL]
#define RSCAN0TMDF047LH RSCAN0.TMDF047.UINT8[LH]
#define RSCAN0TMDF047H RSCAN0.TMDF047.UINT16[H]
#define RSCAN0TMDF047HL RSCAN0.TMDF047.UINT8[HL]
#define RSCAN0TMDF047HH RSCAN0.TMDF047.UINT8[HH]
#define RSCAN0TMDF147 RSCAN0.TMDF147.UINT32
#define RSCAN0TMDF147L RSCAN0.TMDF147.UINT16[L]
#define RSCAN0TMDF147LL RSCAN0.TMDF147.UINT8[LL]
#define RSCAN0TMDF147LH RSCAN0.TMDF147.UINT8[LH]
#define RSCAN0TMDF147H RSCAN0.TMDF147.UINT16[H]
#define RSCAN0TMDF147HL RSCAN0.TMDF147.UINT8[HL]
#define RSCAN0TMDF147HH RSCAN0.TMDF147.UINT8[HH]
#define RSCAN0TMID48 RSCAN0.TMID48.UINT32
#define RSCAN0TMID48L RSCAN0.TMID48.UINT16[L]
#define RSCAN0TMID48LL RSCAN0.TMID48.UINT8[LL]
#define RSCAN0TMID48LH RSCAN0.TMID48.UINT8[LH]
#define RSCAN0TMID48H RSCAN0.TMID48.UINT16[H]
#define RSCAN0TMID48HL RSCAN0.TMID48.UINT8[HL]
#define RSCAN0TMID48HH RSCAN0.TMID48.UINT8[HH]
#define RSCAN0TMPTR48 RSCAN0.TMPTR48.UINT32
#define RSCAN0TMPTR48L RSCAN0.TMPTR48.UINT16[L]
#define RSCAN0TMPTR48LL RSCAN0.TMPTR48.UINT8[LL]
#define RSCAN0TMPTR48LH RSCAN0.TMPTR48.UINT8[LH]
#define RSCAN0TMPTR48H RSCAN0.TMPTR48.UINT16[H]
#define RSCAN0TMPTR48HL RSCAN0.TMPTR48.UINT8[HL]
#define RSCAN0TMPTR48HH RSCAN0.TMPTR48.UINT8[HH]
#define RSCAN0TMDF048 RSCAN0.TMDF048.UINT32
#define RSCAN0TMDF048L RSCAN0.TMDF048.UINT16[L]
#define RSCAN0TMDF048LL RSCAN0.TMDF048.UINT8[LL]
#define RSCAN0TMDF048LH RSCAN0.TMDF048.UINT8[LH]
#define RSCAN0TMDF048H RSCAN0.TMDF048.UINT16[H]
#define RSCAN0TMDF048HL RSCAN0.TMDF048.UINT8[HL]
#define RSCAN0TMDF048HH RSCAN0.TMDF048.UINT8[HH]
#define RSCAN0TMDF148 RSCAN0.TMDF148.UINT32
#define RSCAN0TMDF148L RSCAN0.TMDF148.UINT16[L]
#define RSCAN0TMDF148LL RSCAN0.TMDF148.UINT8[LL]
#define RSCAN0TMDF148LH RSCAN0.TMDF148.UINT8[LH]
#define RSCAN0TMDF148H RSCAN0.TMDF148.UINT16[H]
#define RSCAN0TMDF148HL RSCAN0.TMDF148.UINT8[HL]
#define RSCAN0TMDF148HH RSCAN0.TMDF148.UINT8[HH]
#define RSCAN0TMID49 RSCAN0.TMID49.UINT32
#define RSCAN0TMID49L RSCAN0.TMID49.UINT16[L]
#define RSCAN0TMID49LL RSCAN0.TMID49.UINT8[LL]
#define RSCAN0TMID49LH RSCAN0.TMID49.UINT8[LH]
#define RSCAN0TMID49H RSCAN0.TMID49.UINT16[H]
#define RSCAN0TMID49HL RSCAN0.TMID49.UINT8[HL]
#define RSCAN0TMID49HH RSCAN0.TMID49.UINT8[HH]
#define RSCAN0TMPTR49 RSCAN0.TMPTR49.UINT32
#define RSCAN0TMPTR49L RSCAN0.TMPTR49.UINT16[L]
#define RSCAN0TMPTR49LL RSCAN0.TMPTR49.UINT8[LL]
#define RSCAN0TMPTR49LH RSCAN0.TMPTR49.UINT8[LH]
#define RSCAN0TMPTR49H RSCAN0.TMPTR49.UINT16[H]
#define RSCAN0TMPTR49HL RSCAN0.TMPTR49.UINT8[HL]
#define RSCAN0TMPTR49HH RSCAN0.TMPTR49.UINT8[HH]
#define RSCAN0TMDF049 RSCAN0.TMDF049.UINT32
#define RSCAN0TMDF049L RSCAN0.TMDF049.UINT16[L]
#define RSCAN0TMDF049LL RSCAN0.TMDF049.UINT8[LL]
#define RSCAN0TMDF049LH RSCAN0.TMDF049.UINT8[LH]
#define RSCAN0TMDF049H RSCAN0.TMDF049.UINT16[H]
#define RSCAN0TMDF049HL RSCAN0.TMDF049.UINT8[HL]
#define RSCAN0TMDF049HH RSCAN0.TMDF049.UINT8[HH]
#define RSCAN0TMDF149 RSCAN0.TMDF149.UINT32
#define RSCAN0TMDF149L RSCAN0.TMDF149.UINT16[L]
#define RSCAN0TMDF149LL RSCAN0.TMDF149.UINT8[LL]
#define RSCAN0TMDF149LH RSCAN0.TMDF149.UINT8[LH]
#define RSCAN0TMDF149H RSCAN0.TMDF149.UINT16[H]
#define RSCAN0TMDF149HL RSCAN0.TMDF149.UINT8[HL]
#define RSCAN0TMDF149HH RSCAN0.TMDF149.UINT8[HH]
#define RSCAN0TMID50 RSCAN0.TMID50.UINT32
#define RSCAN0TMID50L RSCAN0.TMID50.UINT16[L]
#define RSCAN0TMID50LL RSCAN0.TMID50.UINT8[LL]
#define RSCAN0TMID50LH RSCAN0.TMID50.UINT8[LH]
#define RSCAN0TMID50H RSCAN0.TMID50.UINT16[H]
#define RSCAN0TMID50HL RSCAN0.TMID50.UINT8[HL]
#define RSCAN0TMID50HH RSCAN0.TMID50.UINT8[HH]
#define RSCAN0TMPTR50 RSCAN0.TMPTR50.UINT32
#define RSCAN0TMPTR50L RSCAN0.TMPTR50.UINT16[L]
#define RSCAN0TMPTR50LL RSCAN0.TMPTR50.UINT8[LL]
#define RSCAN0TMPTR50LH RSCAN0.TMPTR50.UINT8[LH]
#define RSCAN0TMPTR50H RSCAN0.TMPTR50.UINT16[H]
#define RSCAN0TMPTR50HL RSCAN0.TMPTR50.UINT8[HL]
#define RSCAN0TMPTR50HH RSCAN0.TMPTR50.UINT8[HH]
#define RSCAN0TMDF050 RSCAN0.TMDF050.UINT32
#define RSCAN0TMDF050L RSCAN0.TMDF050.UINT16[L]
#define RSCAN0TMDF050LL RSCAN0.TMDF050.UINT8[LL]
#define RSCAN0TMDF050LH RSCAN0.TMDF050.UINT8[LH]
#define RSCAN0TMDF050H RSCAN0.TMDF050.UINT16[H]
#define RSCAN0TMDF050HL RSCAN0.TMDF050.UINT8[HL]
#define RSCAN0TMDF050HH RSCAN0.TMDF050.UINT8[HH]
#define RSCAN0TMDF150 RSCAN0.TMDF150.UINT32
#define RSCAN0TMDF150L RSCAN0.TMDF150.UINT16[L]
#define RSCAN0TMDF150LL RSCAN0.TMDF150.UINT8[LL]
#define RSCAN0TMDF150LH RSCAN0.TMDF150.UINT8[LH]
#define RSCAN0TMDF150H RSCAN0.TMDF150.UINT16[H]
#define RSCAN0TMDF150HL RSCAN0.TMDF150.UINT8[HL]
#define RSCAN0TMDF150HH RSCAN0.TMDF150.UINT8[HH]
#define RSCAN0TMID51 RSCAN0.TMID51.UINT32
#define RSCAN0TMID51L RSCAN0.TMID51.UINT16[L]
#define RSCAN0TMID51LL RSCAN0.TMID51.UINT8[LL]
#define RSCAN0TMID51LH RSCAN0.TMID51.UINT8[LH]
#define RSCAN0TMID51H RSCAN0.TMID51.UINT16[H]
#define RSCAN0TMID51HL RSCAN0.TMID51.UINT8[HL]
#define RSCAN0TMID51HH RSCAN0.TMID51.UINT8[HH]
#define RSCAN0TMPTR51 RSCAN0.TMPTR51.UINT32
#define RSCAN0TMPTR51L RSCAN0.TMPTR51.UINT16[L]
#define RSCAN0TMPTR51LL RSCAN0.TMPTR51.UINT8[LL]
#define RSCAN0TMPTR51LH RSCAN0.TMPTR51.UINT8[LH]
#define RSCAN0TMPTR51H RSCAN0.TMPTR51.UINT16[H]
#define RSCAN0TMPTR51HL RSCAN0.TMPTR51.UINT8[HL]
#define RSCAN0TMPTR51HH RSCAN0.TMPTR51.UINT8[HH]
#define RSCAN0TMDF051 RSCAN0.TMDF051.UINT32
#define RSCAN0TMDF051L RSCAN0.TMDF051.UINT16[L]
#define RSCAN0TMDF051LL RSCAN0.TMDF051.UINT8[LL]
#define RSCAN0TMDF051LH RSCAN0.TMDF051.UINT8[LH]
#define RSCAN0TMDF051H RSCAN0.TMDF051.UINT16[H]
#define RSCAN0TMDF051HL RSCAN0.TMDF051.UINT8[HL]
#define RSCAN0TMDF051HH RSCAN0.TMDF051.UINT8[HH]
#define RSCAN0TMDF151 RSCAN0.TMDF151.UINT32
#define RSCAN0TMDF151L RSCAN0.TMDF151.UINT16[L]
#define RSCAN0TMDF151LL RSCAN0.TMDF151.UINT8[LL]
#define RSCAN0TMDF151LH RSCAN0.TMDF151.UINT8[LH]
#define RSCAN0TMDF151H RSCAN0.TMDF151.UINT16[H]
#define RSCAN0TMDF151HL RSCAN0.TMDF151.UINT8[HL]
#define RSCAN0TMDF151HH RSCAN0.TMDF151.UINT8[HH]
#define RSCAN0TMID52 RSCAN0.TMID52.UINT32
#define RSCAN0TMID52L RSCAN0.TMID52.UINT16[L]
#define RSCAN0TMID52LL RSCAN0.TMID52.UINT8[LL]
#define RSCAN0TMID52LH RSCAN0.TMID52.UINT8[LH]
#define RSCAN0TMID52H RSCAN0.TMID52.UINT16[H]
#define RSCAN0TMID52HL RSCAN0.TMID52.UINT8[HL]
#define RSCAN0TMID52HH RSCAN0.TMID52.UINT8[HH]
#define RSCAN0TMPTR52 RSCAN0.TMPTR52.UINT32
#define RSCAN0TMPTR52L RSCAN0.TMPTR52.UINT16[L]
#define RSCAN0TMPTR52LL RSCAN0.TMPTR52.UINT8[LL]
#define RSCAN0TMPTR52LH RSCAN0.TMPTR52.UINT8[LH]
#define RSCAN0TMPTR52H RSCAN0.TMPTR52.UINT16[H]
#define RSCAN0TMPTR52HL RSCAN0.TMPTR52.UINT8[HL]
#define RSCAN0TMPTR52HH RSCAN0.TMPTR52.UINT8[HH]
#define RSCAN0TMDF052 RSCAN0.TMDF052.UINT32
#define RSCAN0TMDF052L RSCAN0.TMDF052.UINT16[L]
#define RSCAN0TMDF052LL RSCAN0.TMDF052.UINT8[LL]
#define RSCAN0TMDF052LH RSCAN0.TMDF052.UINT8[LH]
#define RSCAN0TMDF052H RSCAN0.TMDF052.UINT16[H]
#define RSCAN0TMDF052HL RSCAN0.TMDF052.UINT8[HL]
#define RSCAN0TMDF052HH RSCAN0.TMDF052.UINT8[HH]
#define RSCAN0TMDF152 RSCAN0.TMDF152.UINT32
#define RSCAN0TMDF152L RSCAN0.TMDF152.UINT16[L]
#define RSCAN0TMDF152LL RSCAN0.TMDF152.UINT8[LL]
#define RSCAN0TMDF152LH RSCAN0.TMDF152.UINT8[LH]
#define RSCAN0TMDF152H RSCAN0.TMDF152.UINT16[H]
#define RSCAN0TMDF152HL RSCAN0.TMDF152.UINT8[HL]
#define RSCAN0TMDF152HH RSCAN0.TMDF152.UINT8[HH]
#define RSCAN0TMID53 RSCAN0.TMID53.UINT32
#define RSCAN0TMID53L RSCAN0.TMID53.UINT16[L]
#define RSCAN0TMID53LL RSCAN0.TMID53.UINT8[LL]
#define RSCAN0TMID53LH RSCAN0.TMID53.UINT8[LH]
#define RSCAN0TMID53H RSCAN0.TMID53.UINT16[H]
#define RSCAN0TMID53HL RSCAN0.TMID53.UINT8[HL]
#define RSCAN0TMID53HH RSCAN0.TMID53.UINT8[HH]
#define RSCAN0TMPTR53 RSCAN0.TMPTR53.UINT32
#define RSCAN0TMPTR53L RSCAN0.TMPTR53.UINT16[L]
#define RSCAN0TMPTR53LL RSCAN0.TMPTR53.UINT8[LL]
#define RSCAN0TMPTR53LH RSCAN0.TMPTR53.UINT8[LH]
#define RSCAN0TMPTR53H RSCAN0.TMPTR53.UINT16[H]
#define RSCAN0TMPTR53HL RSCAN0.TMPTR53.UINT8[HL]
#define RSCAN0TMPTR53HH RSCAN0.TMPTR53.UINT8[HH]
#define RSCAN0TMDF053 RSCAN0.TMDF053.UINT32
#define RSCAN0TMDF053L RSCAN0.TMDF053.UINT16[L]
#define RSCAN0TMDF053LL RSCAN0.TMDF053.UINT8[LL]
#define RSCAN0TMDF053LH RSCAN0.TMDF053.UINT8[LH]
#define RSCAN0TMDF053H RSCAN0.TMDF053.UINT16[H]
#define RSCAN0TMDF053HL RSCAN0.TMDF053.UINT8[HL]
#define RSCAN0TMDF053HH RSCAN0.TMDF053.UINT8[HH]
#define RSCAN0TMDF153 RSCAN0.TMDF153.UINT32
#define RSCAN0TMDF153L RSCAN0.TMDF153.UINT16[L]
#define RSCAN0TMDF153LL RSCAN0.TMDF153.UINT8[LL]
#define RSCAN0TMDF153LH RSCAN0.TMDF153.UINT8[LH]
#define RSCAN0TMDF153H RSCAN0.TMDF153.UINT16[H]
#define RSCAN0TMDF153HL RSCAN0.TMDF153.UINT8[HL]
#define RSCAN0TMDF153HH RSCAN0.TMDF153.UINT8[HH]
#define RSCAN0TMID54 RSCAN0.TMID54.UINT32
#define RSCAN0TMID54L RSCAN0.TMID54.UINT16[L]
#define RSCAN0TMID54LL RSCAN0.TMID54.UINT8[LL]
#define RSCAN0TMID54LH RSCAN0.TMID54.UINT8[LH]
#define RSCAN0TMID54H RSCAN0.TMID54.UINT16[H]
#define RSCAN0TMID54HL RSCAN0.TMID54.UINT8[HL]
#define RSCAN0TMID54HH RSCAN0.TMID54.UINT8[HH]
#define RSCAN0TMPTR54 RSCAN0.TMPTR54.UINT32
#define RSCAN0TMPTR54L RSCAN0.TMPTR54.UINT16[L]
#define RSCAN0TMPTR54LL RSCAN0.TMPTR54.UINT8[LL]
#define RSCAN0TMPTR54LH RSCAN0.TMPTR54.UINT8[LH]
#define RSCAN0TMPTR54H RSCAN0.TMPTR54.UINT16[H]
#define RSCAN0TMPTR54HL RSCAN0.TMPTR54.UINT8[HL]
#define RSCAN0TMPTR54HH RSCAN0.TMPTR54.UINT8[HH]
#define RSCAN0TMDF054 RSCAN0.TMDF054.UINT32
#define RSCAN0TMDF054L RSCAN0.TMDF054.UINT16[L]
#define RSCAN0TMDF054LL RSCAN0.TMDF054.UINT8[LL]
#define RSCAN0TMDF054LH RSCAN0.TMDF054.UINT8[LH]
#define RSCAN0TMDF054H RSCAN0.TMDF054.UINT16[H]
#define RSCAN0TMDF054HL RSCAN0.TMDF054.UINT8[HL]
#define RSCAN0TMDF054HH RSCAN0.TMDF054.UINT8[HH]
#define RSCAN0TMDF154 RSCAN0.TMDF154.UINT32
#define RSCAN0TMDF154L RSCAN0.TMDF154.UINT16[L]
#define RSCAN0TMDF154LL RSCAN0.TMDF154.UINT8[LL]
#define RSCAN0TMDF154LH RSCAN0.TMDF154.UINT8[LH]
#define RSCAN0TMDF154H RSCAN0.TMDF154.UINT16[H]
#define RSCAN0TMDF154HL RSCAN0.TMDF154.UINT8[HL]
#define RSCAN0TMDF154HH RSCAN0.TMDF154.UINT8[HH]
#define RSCAN0TMID55 RSCAN0.TMID55.UINT32
#define RSCAN0TMID55L RSCAN0.TMID55.UINT16[L]
#define RSCAN0TMID55LL RSCAN0.TMID55.UINT8[LL]
#define RSCAN0TMID55LH RSCAN0.TMID55.UINT8[LH]
#define RSCAN0TMID55H RSCAN0.TMID55.UINT16[H]
#define RSCAN0TMID55HL RSCAN0.TMID55.UINT8[HL]
#define RSCAN0TMID55HH RSCAN0.TMID55.UINT8[HH]
#define RSCAN0TMPTR55 RSCAN0.TMPTR55.UINT32
#define RSCAN0TMPTR55L RSCAN0.TMPTR55.UINT16[L]
#define RSCAN0TMPTR55LL RSCAN0.TMPTR55.UINT8[LL]
#define RSCAN0TMPTR55LH RSCAN0.TMPTR55.UINT8[LH]
#define RSCAN0TMPTR55H RSCAN0.TMPTR55.UINT16[H]
#define RSCAN0TMPTR55HL RSCAN0.TMPTR55.UINT8[HL]
#define RSCAN0TMPTR55HH RSCAN0.TMPTR55.UINT8[HH]
#define RSCAN0TMDF055 RSCAN0.TMDF055.UINT32
#define RSCAN0TMDF055L RSCAN0.TMDF055.UINT16[L]
#define RSCAN0TMDF055LL RSCAN0.TMDF055.UINT8[LL]
#define RSCAN0TMDF055LH RSCAN0.TMDF055.UINT8[LH]
#define RSCAN0TMDF055H RSCAN0.TMDF055.UINT16[H]
#define RSCAN0TMDF055HL RSCAN0.TMDF055.UINT8[HL]
#define RSCAN0TMDF055HH RSCAN0.TMDF055.UINT8[HH]
#define RSCAN0TMDF155 RSCAN0.TMDF155.UINT32
#define RSCAN0TMDF155L RSCAN0.TMDF155.UINT16[L]
#define RSCAN0TMDF155LL RSCAN0.TMDF155.UINT8[LL]
#define RSCAN0TMDF155LH RSCAN0.TMDF155.UINT8[LH]
#define RSCAN0TMDF155H RSCAN0.TMDF155.UINT16[H]
#define RSCAN0TMDF155HL RSCAN0.TMDF155.UINT8[HL]
#define RSCAN0TMDF155HH RSCAN0.TMDF155.UINT8[HH]
#define RSCAN0TMID56 RSCAN0.TMID56.UINT32
#define RSCAN0TMID56L RSCAN0.TMID56.UINT16[L]
#define RSCAN0TMID56LL RSCAN0.TMID56.UINT8[LL]
#define RSCAN0TMID56LH RSCAN0.TMID56.UINT8[LH]
#define RSCAN0TMID56H RSCAN0.TMID56.UINT16[H]
#define RSCAN0TMID56HL RSCAN0.TMID56.UINT8[HL]
#define RSCAN0TMID56HH RSCAN0.TMID56.UINT8[HH]
#define RSCAN0TMPTR56 RSCAN0.TMPTR56.UINT32
#define RSCAN0TMPTR56L RSCAN0.TMPTR56.UINT16[L]
#define RSCAN0TMPTR56LL RSCAN0.TMPTR56.UINT8[LL]
#define RSCAN0TMPTR56LH RSCAN0.TMPTR56.UINT8[LH]
#define RSCAN0TMPTR56H RSCAN0.TMPTR56.UINT16[H]
#define RSCAN0TMPTR56HL RSCAN0.TMPTR56.UINT8[HL]
#define RSCAN0TMPTR56HH RSCAN0.TMPTR56.UINT8[HH]
#define RSCAN0TMDF056 RSCAN0.TMDF056.UINT32
#define RSCAN0TMDF056L RSCAN0.TMDF056.UINT16[L]
#define RSCAN0TMDF056LL RSCAN0.TMDF056.UINT8[LL]
#define RSCAN0TMDF056LH RSCAN0.TMDF056.UINT8[LH]
#define RSCAN0TMDF056H RSCAN0.TMDF056.UINT16[H]
#define RSCAN0TMDF056HL RSCAN0.TMDF056.UINT8[HL]
#define RSCAN0TMDF056HH RSCAN0.TMDF056.UINT8[HH]
#define RSCAN0TMDF156 RSCAN0.TMDF156.UINT32
#define RSCAN0TMDF156L RSCAN0.TMDF156.UINT16[L]
#define RSCAN0TMDF156LL RSCAN0.TMDF156.UINT8[LL]
#define RSCAN0TMDF156LH RSCAN0.TMDF156.UINT8[LH]
#define RSCAN0TMDF156H RSCAN0.TMDF156.UINT16[H]
#define RSCAN0TMDF156HL RSCAN0.TMDF156.UINT8[HL]
#define RSCAN0TMDF156HH RSCAN0.TMDF156.UINT8[HH]
#define RSCAN0TMID57 RSCAN0.TMID57.UINT32
#define RSCAN0TMID57L RSCAN0.TMID57.UINT16[L]
#define RSCAN0TMID57LL RSCAN0.TMID57.UINT8[LL]
#define RSCAN0TMID57LH RSCAN0.TMID57.UINT8[LH]
#define RSCAN0TMID57H RSCAN0.TMID57.UINT16[H]
#define RSCAN0TMID57HL RSCAN0.TMID57.UINT8[HL]
#define RSCAN0TMID57HH RSCAN0.TMID57.UINT8[HH]
#define RSCAN0TMPTR57 RSCAN0.TMPTR57.UINT32
#define RSCAN0TMPTR57L RSCAN0.TMPTR57.UINT16[L]
#define RSCAN0TMPTR57LL RSCAN0.TMPTR57.UINT8[LL]
#define RSCAN0TMPTR57LH RSCAN0.TMPTR57.UINT8[LH]
#define RSCAN0TMPTR57H RSCAN0.TMPTR57.UINT16[H]
#define RSCAN0TMPTR57HL RSCAN0.TMPTR57.UINT8[HL]
#define RSCAN0TMPTR57HH RSCAN0.TMPTR57.UINT8[HH]
#define RSCAN0TMDF057 RSCAN0.TMDF057.UINT32
#define RSCAN0TMDF057L RSCAN0.TMDF057.UINT16[L]
#define RSCAN0TMDF057LL RSCAN0.TMDF057.UINT8[LL]
#define RSCAN0TMDF057LH RSCAN0.TMDF057.UINT8[LH]
#define RSCAN0TMDF057H RSCAN0.TMDF057.UINT16[H]
#define RSCAN0TMDF057HL RSCAN0.TMDF057.UINT8[HL]
#define RSCAN0TMDF057HH RSCAN0.TMDF057.UINT8[HH]
#define RSCAN0TMDF157 RSCAN0.TMDF157.UINT32
#define RSCAN0TMDF157L RSCAN0.TMDF157.UINT16[L]
#define RSCAN0TMDF157LL RSCAN0.TMDF157.UINT8[LL]
#define RSCAN0TMDF157LH RSCAN0.TMDF157.UINT8[LH]
#define RSCAN0TMDF157H RSCAN0.TMDF157.UINT16[H]
#define RSCAN0TMDF157HL RSCAN0.TMDF157.UINT8[HL]
#define RSCAN0TMDF157HH RSCAN0.TMDF157.UINT8[HH]
#define RSCAN0TMID58 RSCAN0.TMID58.UINT32
#define RSCAN0TMID58L RSCAN0.TMID58.UINT16[L]
#define RSCAN0TMID58LL RSCAN0.TMID58.UINT8[LL]
#define RSCAN0TMID58LH RSCAN0.TMID58.UINT8[LH]
#define RSCAN0TMID58H RSCAN0.TMID58.UINT16[H]
#define RSCAN0TMID58HL RSCAN0.TMID58.UINT8[HL]
#define RSCAN0TMID58HH RSCAN0.TMID58.UINT8[HH]
#define RSCAN0TMPTR58 RSCAN0.TMPTR58.UINT32
#define RSCAN0TMPTR58L RSCAN0.TMPTR58.UINT16[L]
#define RSCAN0TMPTR58LL RSCAN0.TMPTR58.UINT8[LL]
#define RSCAN0TMPTR58LH RSCAN0.TMPTR58.UINT8[LH]
#define RSCAN0TMPTR58H RSCAN0.TMPTR58.UINT16[H]
#define RSCAN0TMPTR58HL RSCAN0.TMPTR58.UINT8[HL]
#define RSCAN0TMPTR58HH RSCAN0.TMPTR58.UINT8[HH]
#define RSCAN0TMDF058 RSCAN0.TMDF058.UINT32
#define RSCAN0TMDF058L RSCAN0.TMDF058.UINT16[L]
#define RSCAN0TMDF058LL RSCAN0.TMDF058.UINT8[LL]
#define RSCAN0TMDF058LH RSCAN0.TMDF058.UINT8[LH]
#define RSCAN0TMDF058H RSCAN0.TMDF058.UINT16[H]
#define RSCAN0TMDF058HL RSCAN0.TMDF058.UINT8[HL]
#define RSCAN0TMDF058HH RSCAN0.TMDF058.UINT8[HH]
#define RSCAN0TMDF158 RSCAN0.TMDF158.UINT32
#define RSCAN0TMDF158L RSCAN0.TMDF158.UINT16[L]
#define RSCAN0TMDF158LL RSCAN0.TMDF158.UINT8[LL]
#define RSCAN0TMDF158LH RSCAN0.TMDF158.UINT8[LH]
#define RSCAN0TMDF158H RSCAN0.TMDF158.UINT16[H]
#define RSCAN0TMDF158HL RSCAN0.TMDF158.UINT8[HL]
#define RSCAN0TMDF158HH RSCAN0.TMDF158.UINT8[HH]
#define RSCAN0TMID59 RSCAN0.TMID59.UINT32
#define RSCAN0TMID59L RSCAN0.TMID59.UINT16[L]
#define RSCAN0TMID59LL RSCAN0.TMID59.UINT8[LL]
#define RSCAN0TMID59LH RSCAN0.TMID59.UINT8[LH]
#define RSCAN0TMID59H RSCAN0.TMID59.UINT16[H]
#define RSCAN0TMID59HL RSCAN0.TMID59.UINT8[HL]
#define RSCAN0TMID59HH RSCAN0.TMID59.UINT8[HH]
#define RSCAN0TMPTR59 RSCAN0.TMPTR59.UINT32
#define RSCAN0TMPTR59L RSCAN0.TMPTR59.UINT16[L]
#define RSCAN0TMPTR59LL RSCAN0.TMPTR59.UINT8[LL]
#define RSCAN0TMPTR59LH RSCAN0.TMPTR59.UINT8[LH]
#define RSCAN0TMPTR59H RSCAN0.TMPTR59.UINT16[H]
#define RSCAN0TMPTR59HL RSCAN0.TMPTR59.UINT8[HL]
#define RSCAN0TMPTR59HH RSCAN0.TMPTR59.UINT8[HH]
#define RSCAN0TMDF059 RSCAN0.TMDF059.UINT32
#define RSCAN0TMDF059L RSCAN0.TMDF059.UINT16[L]
#define RSCAN0TMDF059LL RSCAN0.TMDF059.UINT8[LL]
#define RSCAN0TMDF059LH RSCAN0.TMDF059.UINT8[LH]
#define RSCAN0TMDF059H RSCAN0.TMDF059.UINT16[H]
#define RSCAN0TMDF059HL RSCAN0.TMDF059.UINT8[HL]
#define RSCAN0TMDF059HH RSCAN0.TMDF059.UINT8[HH]
#define RSCAN0TMDF159 RSCAN0.TMDF159.UINT32
#define RSCAN0TMDF159L RSCAN0.TMDF159.UINT16[L]
#define RSCAN0TMDF159LL RSCAN0.TMDF159.UINT8[LL]
#define RSCAN0TMDF159LH RSCAN0.TMDF159.UINT8[LH]
#define RSCAN0TMDF159H RSCAN0.TMDF159.UINT16[H]
#define RSCAN0TMDF159HL RSCAN0.TMDF159.UINT8[HL]
#define RSCAN0TMDF159HH RSCAN0.TMDF159.UINT8[HH]
#define RSCAN0TMID60 RSCAN0.TMID60.UINT32
#define RSCAN0TMID60L RSCAN0.TMID60.UINT16[L]
#define RSCAN0TMID60LL RSCAN0.TMID60.UINT8[LL]
#define RSCAN0TMID60LH RSCAN0.TMID60.UINT8[LH]
#define RSCAN0TMID60H RSCAN0.TMID60.UINT16[H]
#define RSCAN0TMID60HL RSCAN0.TMID60.UINT8[HL]
#define RSCAN0TMID60HH RSCAN0.TMID60.UINT8[HH]
#define RSCAN0TMPTR60 RSCAN0.TMPTR60.UINT32
#define RSCAN0TMPTR60L RSCAN0.TMPTR60.UINT16[L]
#define RSCAN0TMPTR60LL RSCAN0.TMPTR60.UINT8[LL]
#define RSCAN0TMPTR60LH RSCAN0.TMPTR60.UINT8[LH]
#define RSCAN0TMPTR60H RSCAN0.TMPTR60.UINT16[H]
#define RSCAN0TMPTR60HL RSCAN0.TMPTR60.UINT8[HL]
#define RSCAN0TMPTR60HH RSCAN0.TMPTR60.UINT8[HH]
#define RSCAN0TMDF060 RSCAN0.TMDF060.UINT32
#define RSCAN0TMDF060L RSCAN0.TMDF060.UINT16[L]
#define RSCAN0TMDF060LL RSCAN0.TMDF060.UINT8[LL]
#define RSCAN0TMDF060LH RSCAN0.TMDF060.UINT8[LH]
#define RSCAN0TMDF060H RSCAN0.TMDF060.UINT16[H]
#define RSCAN0TMDF060HL RSCAN0.TMDF060.UINT8[HL]
#define RSCAN0TMDF060HH RSCAN0.TMDF060.UINT8[HH]
#define RSCAN0TMDF160 RSCAN0.TMDF160.UINT32
#define RSCAN0TMDF160L RSCAN0.TMDF160.UINT16[L]
#define RSCAN0TMDF160LL RSCAN0.TMDF160.UINT8[LL]
#define RSCAN0TMDF160LH RSCAN0.TMDF160.UINT8[LH]
#define RSCAN0TMDF160H RSCAN0.TMDF160.UINT16[H]
#define RSCAN0TMDF160HL RSCAN0.TMDF160.UINT8[HL]
#define RSCAN0TMDF160HH RSCAN0.TMDF160.UINT8[HH]
#define RSCAN0TMID61 RSCAN0.TMID61.UINT32
#define RSCAN0TMID61L RSCAN0.TMID61.UINT16[L]
#define RSCAN0TMID61LL RSCAN0.TMID61.UINT8[LL]
#define RSCAN0TMID61LH RSCAN0.TMID61.UINT8[LH]
#define RSCAN0TMID61H RSCAN0.TMID61.UINT16[H]
#define RSCAN0TMID61HL RSCAN0.TMID61.UINT8[HL]
#define RSCAN0TMID61HH RSCAN0.TMID61.UINT8[HH]
#define RSCAN0TMPTR61 RSCAN0.TMPTR61.UINT32
#define RSCAN0TMPTR61L RSCAN0.TMPTR61.UINT16[L]
#define RSCAN0TMPTR61LL RSCAN0.TMPTR61.UINT8[LL]
#define RSCAN0TMPTR61LH RSCAN0.TMPTR61.UINT8[LH]
#define RSCAN0TMPTR61H RSCAN0.TMPTR61.UINT16[H]
#define RSCAN0TMPTR61HL RSCAN0.TMPTR61.UINT8[HL]
#define RSCAN0TMPTR61HH RSCAN0.TMPTR61.UINT8[HH]
#define RSCAN0TMDF061 RSCAN0.TMDF061.UINT32
#define RSCAN0TMDF061L RSCAN0.TMDF061.UINT16[L]
#define RSCAN0TMDF061LL RSCAN0.TMDF061.UINT8[LL]
#define RSCAN0TMDF061LH RSCAN0.TMDF061.UINT8[LH]
#define RSCAN0TMDF061H RSCAN0.TMDF061.UINT16[H]
#define RSCAN0TMDF061HL RSCAN0.TMDF061.UINT8[HL]
#define RSCAN0TMDF061HH RSCAN0.TMDF061.UINT8[HH]
#define RSCAN0TMDF161 RSCAN0.TMDF161.UINT32
#define RSCAN0TMDF161L RSCAN0.TMDF161.UINT16[L]
#define RSCAN0TMDF161LL RSCAN0.TMDF161.UINT8[LL]
#define RSCAN0TMDF161LH RSCAN0.TMDF161.UINT8[LH]
#define RSCAN0TMDF161H RSCAN0.TMDF161.UINT16[H]
#define RSCAN0TMDF161HL RSCAN0.TMDF161.UINT8[HL]
#define RSCAN0TMDF161HH RSCAN0.TMDF161.UINT8[HH]
#define RSCAN0TMID62 RSCAN0.TMID62.UINT32
#define RSCAN0TMID62L RSCAN0.TMID62.UINT16[L]
#define RSCAN0TMID62LL RSCAN0.TMID62.UINT8[LL]
#define RSCAN0TMID62LH RSCAN0.TMID62.UINT8[LH]
#define RSCAN0TMID62H RSCAN0.TMID62.UINT16[H]
#define RSCAN0TMID62HL RSCAN0.TMID62.UINT8[HL]
#define RSCAN0TMID62HH RSCAN0.TMID62.UINT8[HH]
#define RSCAN0TMPTR62 RSCAN0.TMPTR62.UINT32
#define RSCAN0TMPTR62L RSCAN0.TMPTR62.UINT16[L]
#define RSCAN0TMPTR62LL RSCAN0.TMPTR62.UINT8[LL]
#define RSCAN0TMPTR62LH RSCAN0.TMPTR62.UINT8[LH]
#define RSCAN0TMPTR62H RSCAN0.TMPTR62.UINT16[H]
#define RSCAN0TMPTR62HL RSCAN0.TMPTR62.UINT8[HL]
#define RSCAN0TMPTR62HH RSCAN0.TMPTR62.UINT8[HH]
#define RSCAN0TMDF062 RSCAN0.TMDF062.UINT32
#define RSCAN0TMDF062L RSCAN0.TMDF062.UINT16[L]
#define RSCAN0TMDF062LL RSCAN0.TMDF062.UINT8[LL]
#define RSCAN0TMDF062LH RSCAN0.TMDF062.UINT8[LH]
#define RSCAN0TMDF062H RSCAN0.TMDF062.UINT16[H]
#define RSCAN0TMDF062HL RSCAN0.TMDF062.UINT8[HL]
#define RSCAN0TMDF062HH RSCAN0.TMDF062.UINT8[HH]
#define RSCAN0TMDF162 RSCAN0.TMDF162.UINT32
#define RSCAN0TMDF162L RSCAN0.TMDF162.UINT16[L]
#define RSCAN0TMDF162LL RSCAN0.TMDF162.UINT8[LL]
#define RSCAN0TMDF162LH RSCAN0.TMDF162.UINT8[LH]
#define RSCAN0TMDF162H RSCAN0.TMDF162.UINT16[H]
#define RSCAN0TMDF162HL RSCAN0.TMDF162.UINT8[HL]
#define RSCAN0TMDF162HH RSCAN0.TMDF162.UINT8[HH]
#define RSCAN0TMID63 RSCAN0.TMID63.UINT32
#define RSCAN0TMID63L RSCAN0.TMID63.UINT16[L]
#define RSCAN0TMID63LL RSCAN0.TMID63.UINT8[LL]
#define RSCAN0TMID63LH RSCAN0.TMID63.UINT8[LH]
#define RSCAN0TMID63H RSCAN0.TMID63.UINT16[H]
#define RSCAN0TMID63HL RSCAN0.TMID63.UINT8[HL]
#define RSCAN0TMID63HH RSCAN0.TMID63.UINT8[HH]
#define RSCAN0TMPTR63 RSCAN0.TMPTR63.UINT32
#define RSCAN0TMPTR63L RSCAN0.TMPTR63.UINT16[L]
#define RSCAN0TMPTR63LL RSCAN0.TMPTR63.UINT8[LL]
#define RSCAN0TMPTR63LH RSCAN0.TMPTR63.UINT8[LH]
#define RSCAN0TMPTR63H RSCAN0.TMPTR63.UINT16[H]
#define RSCAN0TMPTR63HL RSCAN0.TMPTR63.UINT8[HL]
#define RSCAN0TMPTR63HH RSCAN0.TMPTR63.UINT8[HH]
#define RSCAN0TMDF063 RSCAN0.TMDF063.UINT32
#define RSCAN0TMDF063L RSCAN0.TMDF063.UINT16[L]
#define RSCAN0TMDF063LL RSCAN0.TMDF063.UINT8[LL]
#define RSCAN0TMDF063LH RSCAN0.TMDF063.UINT8[LH]
#define RSCAN0TMDF063H RSCAN0.TMDF063.UINT16[H]
#define RSCAN0TMDF063HL RSCAN0.TMDF063.UINT8[HL]
#define RSCAN0TMDF063HH RSCAN0.TMDF063.UINT8[HH]
#define RSCAN0TMDF163 RSCAN0.TMDF163.UINT32
#define RSCAN0TMDF163L RSCAN0.TMDF163.UINT16[L]
#define RSCAN0TMDF163LL RSCAN0.TMDF163.UINT8[LL]
#define RSCAN0TMDF163LH RSCAN0.TMDF163.UINT8[LH]
#define RSCAN0TMDF163H RSCAN0.TMDF163.UINT16[H]
#define RSCAN0TMDF163HL RSCAN0.TMDF163.UINT8[HL]
#define RSCAN0TMDF163HH RSCAN0.TMDF163.UINT8[HH]
#define RSCAN0TMID64 RSCAN0.TMID64.UINT32
#define RSCAN0TMID64L RSCAN0.TMID64.UINT16[L]
#define RSCAN0TMID64LL RSCAN0.TMID64.UINT8[LL]
#define RSCAN0TMID64LH RSCAN0.TMID64.UINT8[LH]
#define RSCAN0TMID64H RSCAN0.TMID64.UINT16[H]
#define RSCAN0TMID64HL RSCAN0.TMID64.UINT8[HL]
#define RSCAN0TMID64HH RSCAN0.TMID64.UINT8[HH]
#define RSCAN0TMPTR64 RSCAN0.TMPTR64.UINT32
#define RSCAN0TMPTR64L RSCAN0.TMPTR64.UINT16[L]
#define RSCAN0TMPTR64LL RSCAN0.TMPTR64.UINT8[LL]
#define RSCAN0TMPTR64LH RSCAN0.TMPTR64.UINT8[LH]
#define RSCAN0TMPTR64H RSCAN0.TMPTR64.UINT16[H]
#define RSCAN0TMPTR64HL RSCAN0.TMPTR64.UINT8[HL]
#define RSCAN0TMPTR64HH RSCAN0.TMPTR64.UINT8[HH]
#define RSCAN0TMDF064 RSCAN0.TMDF064.UINT32
#define RSCAN0TMDF064L RSCAN0.TMDF064.UINT16[L]
#define RSCAN0TMDF064LL RSCAN0.TMDF064.UINT8[LL]
#define RSCAN0TMDF064LH RSCAN0.TMDF064.UINT8[LH]
#define RSCAN0TMDF064H RSCAN0.TMDF064.UINT16[H]
#define RSCAN0TMDF064HL RSCAN0.TMDF064.UINT8[HL]
#define RSCAN0TMDF064HH RSCAN0.TMDF064.UINT8[HH]
#define RSCAN0TMDF164 RSCAN0.TMDF164.UINT32
#define RSCAN0TMDF164L RSCAN0.TMDF164.UINT16[L]
#define RSCAN0TMDF164LL RSCAN0.TMDF164.UINT8[LL]
#define RSCAN0TMDF164LH RSCAN0.TMDF164.UINT8[LH]
#define RSCAN0TMDF164H RSCAN0.TMDF164.UINT16[H]
#define RSCAN0TMDF164HL RSCAN0.TMDF164.UINT8[HL]
#define RSCAN0TMDF164HH RSCAN0.TMDF164.UINT8[HH]
#define RSCAN0TMID65 RSCAN0.TMID65.UINT32
#define RSCAN0TMID65L RSCAN0.TMID65.UINT16[L]
#define RSCAN0TMID65LL RSCAN0.TMID65.UINT8[LL]
#define RSCAN0TMID65LH RSCAN0.TMID65.UINT8[LH]
#define RSCAN0TMID65H RSCAN0.TMID65.UINT16[H]
#define RSCAN0TMID65HL RSCAN0.TMID65.UINT8[HL]
#define RSCAN0TMID65HH RSCAN0.TMID65.UINT8[HH]
#define RSCAN0TMPTR65 RSCAN0.TMPTR65.UINT32
#define RSCAN0TMPTR65L RSCAN0.TMPTR65.UINT16[L]
#define RSCAN0TMPTR65LL RSCAN0.TMPTR65.UINT8[LL]
#define RSCAN0TMPTR65LH RSCAN0.TMPTR65.UINT8[LH]
#define RSCAN0TMPTR65H RSCAN0.TMPTR65.UINT16[H]
#define RSCAN0TMPTR65HL RSCAN0.TMPTR65.UINT8[HL]
#define RSCAN0TMPTR65HH RSCAN0.TMPTR65.UINT8[HH]
#define RSCAN0TMDF065 RSCAN0.TMDF065.UINT32
#define RSCAN0TMDF065L RSCAN0.TMDF065.UINT16[L]
#define RSCAN0TMDF065LL RSCAN0.TMDF065.UINT8[LL]
#define RSCAN0TMDF065LH RSCAN0.TMDF065.UINT8[LH]
#define RSCAN0TMDF065H RSCAN0.TMDF065.UINT16[H]
#define RSCAN0TMDF065HL RSCAN0.TMDF065.UINT8[HL]
#define RSCAN0TMDF065HH RSCAN0.TMDF065.UINT8[HH]
#define RSCAN0TMDF165 RSCAN0.TMDF165.UINT32
#define RSCAN0TMDF165L RSCAN0.TMDF165.UINT16[L]
#define RSCAN0TMDF165LL RSCAN0.TMDF165.UINT8[LL]
#define RSCAN0TMDF165LH RSCAN0.TMDF165.UINT8[LH]
#define RSCAN0TMDF165H RSCAN0.TMDF165.UINT16[H]
#define RSCAN0TMDF165HL RSCAN0.TMDF165.UINT8[HL]
#define RSCAN0TMDF165HH RSCAN0.TMDF165.UINT8[HH]
#define RSCAN0TMID66 RSCAN0.TMID66.UINT32
#define RSCAN0TMID66L RSCAN0.TMID66.UINT16[L]
#define RSCAN0TMID66LL RSCAN0.TMID66.UINT8[LL]
#define RSCAN0TMID66LH RSCAN0.TMID66.UINT8[LH]
#define RSCAN0TMID66H RSCAN0.TMID66.UINT16[H]
#define RSCAN0TMID66HL RSCAN0.TMID66.UINT8[HL]
#define RSCAN0TMID66HH RSCAN0.TMID66.UINT8[HH]
#define RSCAN0TMPTR66 RSCAN0.TMPTR66.UINT32
#define RSCAN0TMPTR66L RSCAN0.TMPTR66.UINT16[L]
#define RSCAN0TMPTR66LL RSCAN0.TMPTR66.UINT8[LL]
#define RSCAN0TMPTR66LH RSCAN0.TMPTR66.UINT8[LH]
#define RSCAN0TMPTR66H RSCAN0.TMPTR66.UINT16[H]
#define RSCAN0TMPTR66HL RSCAN0.TMPTR66.UINT8[HL]
#define RSCAN0TMPTR66HH RSCAN0.TMPTR66.UINT8[HH]
#define RSCAN0TMDF066 RSCAN0.TMDF066.UINT32
#define RSCAN0TMDF066L RSCAN0.TMDF066.UINT16[L]
#define RSCAN0TMDF066LL RSCAN0.TMDF066.UINT8[LL]
#define RSCAN0TMDF066LH RSCAN0.TMDF066.UINT8[LH]
#define RSCAN0TMDF066H RSCAN0.TMDF066.UINT16[H]
#define RSCAN0TMDF066HL RSCAN0.TMDF066.UINT8[HL]
#define RSCAN0TMDF066HH RSCAN0.TMDF066.UINT8[HH]
#define RSCAN0TMDF166 RSCAN0.TMDF166.UINT32
#define RSCAN0TMDF166L RSCAN0.TMDF166.UINT16[L]
#define RSCAN0TMDF166LL RSCAN0.TMDF166.UINT8[LL]
#define RSCAN0TMDF166LH RSCAN0.TMDF166.UINT8[LH]
#define RSCAN0TMDF166H RSCAN0.TMDF166.UINT16[H]
#define RSCAN0TMDF166HL RSCAN0.TMDF166.UINT8[HL]
#define RSCAN0TMDF166HH RSCAN0.TMDF166.UINT8[HH]
#define RSCAN0TMID67 RSCAN0.TMID67.UINT32
#define RSCAN0TMID67L RSCAN0.TMID67.UINT16[L]
#define RSCAN0TMID67LL RSCAN0.TMID67.UINT8[LL]
#define RSCAN0TMID67LH RSCAN0.TMID67.UINT8[LH]
#define RSCAN0TMID67H RSCAN0.TMID67.UINT16[H]
#define RSCAN0TMID67HL RSCAN0.TMID67.UINT8[HL]
#define RSCAN0TMID67HH RSCAN0.TMID67.UINT8[HH]
#define RSCAN0TMPTR67 RSCAN0.TMPTR67.UINT32
#define RSCAN0TMPTR67L RSCAN0.TMPTR67.UINT16[L]
#define RSCAN0TMPTR67LL RSCAN0.TMPTR67.UINT8[LL]
#define RSCAN0TMPTR67LH RSCAN0.TMPTR67.UINT8[LH]
#define RSCAN0TMPTR67H RSCAN0.TMPTR67.UINT16[H]
#define RSCAN0TMPTR67HL RSCAN0.TMPTR67.UINT8[HL]
#define RSCAN0TMPTR67HH RSCAN0.TMPTR67.UINT8[HH]
#define RSCAN0TMDF067 RSCAN0.TMDF067.UINT32
#define RSCAN0TMDF067L RSCAN0.TMDF067.UINT16[L]
#define RSCAN0TMDF067LL RSCAN0.TMDF067.UINT8[LL]
#define RSCAN0TMDF067LH RSCAN0.TMDF067.UINT8[LH]
#define RSCAN0TMDF067H RSCAN0.TMDF067.UINT16[H]
#define RSCAN0TMDF067HL RSCAN0.TMDF067.UINT8[HL]
#define RSCAN0TMDF067HH RSCAN0.TMDF067.UINT8[HH]
#define RSCAN0TMDF167 RSCAN0.TMDF167.UINT32
#define RSCAN0TMDF167L RSCAN0.TMDF167.UINT16[L]
#define RSCAN0TMDF167LL RSCAN0.TMDF167.UINT8[LL]
#define RSCAN0TMDF167LH RSCAN0.TMDF167.UINT8[LH]
#define RSCAN0TMDF167H RSCAN0.TMDF167.UINT16[H]
#define RSCAN0TMDF167HL RSCAN0.TMDF167.UINT8[HL]
#define RSCAN0TMDF167HH RSCAN0.TMDF167.UINT8[HH]
#define RSCAN0TMID68 RSCAN0.TMID68.UINT32
#define RSCAN0TMID68L RSCAN0.TMID68.UINT16[L]
#define RSCAN0TMID68LL RSCAN0.TMID68.UINT8[LL]
#define RSCAN0TMID68LH RSCAN0.TMID68.UINT8[LH]
#define RSCAN0TMID68H RSCAN0.TMID68.UINT16[H]
#define RSCAN0TMID68HL RSCAN0.TMID68.UINT8[HL]
#define RSCAN0TMID68HH RSCAN0.TMID68.UINT8[HH]
#define RSCAN0TMPTR68 RSCAN0.TMPTR68.UINT32
#define RSCAN0TMPTR68L RSCAN0.TMPTR68.UINT16[L]
#define RSCAN0TMPTR68LL RSCAN0.TMPTR68.UINT8[LL]
#define RSCAN0TMPTR68LH RSCAN0.TMPTR68.UINT8[LH]
#define RSCAN0TMPTR68H RSCAN0.TMPTR68.UINT16[H]
#define RSCAN0TMPTR68HL RSCAN0.TMPTR68.UINT8[HL]
#define RSCAN0TMPTR68HH RSCAN0.TMPTR68.UINT8[HH]
#define RSCAN0TMDF068 RSCAN0.TMDF068.UINT32
#define RSCAN0TMDF068L RSCAN0.TMDF068.UINT16[L]
#define RSCAN0TMDF068LL RSCAN0.TMDF068.UINT8[LL]
#define RSCAN0TMDF068LH RSCAN0.TMDF068.UINT8[LH]
#define RSCAN0TMDF068H RSCAN0.TMDF068.UINT16[H]
#define RSCAN0TMDF068HL RSCAN0.TMDF068.UINT8[HL]
#define RSCAN0TMDF068HH RSCAN0.TMDF068.UINT8[HH]
#define RSCAN0TMDF168 RSCAN0.TMDF168.UINT32
#define RSCAN0TMDF168L RSCAN0.TMDF168.UINT16[L]
#define RSCAN0TMDF168LL RSCAN0.TMDF168.UINT8[LL]
#define RSCAN0TMDF168LH RSCAN0.TMDF168.UINT8[LH]
#define RSCAN0TMDF168H RSCAN0.TMDF168.UINT16[H]
#define RSCAN0TMDF168HL RSCAN0.TMDF168.UINT8[HL]
#define RSCAN0TMDF168HH RSCAN0.TMDF168.UINT8[HH]
#define RSCAN0TMID69 RSCAN0.TMID69.UINT32
#define RSCAN0TMID69L RSCAN0.TMID69.UINT16[L]
#define RSCAN0TMID69LL RSCAN0.TMID69.UINT8[LL]
#define RSCAN0TMID69LH RSCAN0.TMID69.UINT8[LH]
#define RSCAN0TMID69H RSCAN0.TMID69.UINT16[H]
#define RSCAN0TMID69HL RSCAN0.TMID69.UINT8[HL]
#define RSCAN0TMID69HH RSCAN0.TMID69.UINT8[HH]
#define RSCAN0TMPTR69 RSCAN0.TMPTR69.UINT32
#define RSCAN0TMPTR69L RSCAN0.TMPTR69.UINT16[L]
#define RSCAN0TMPTR69LL RSCAN0.TMPTR69.UINT8[LL]
#define RSCAN0TMPTR69LH RSCAN0.TMPTR69.UINT8[LH]
#define RSCAN0TMPTR69H RSCAN0.TMPTR69.UINT16[H]
#define RSCAN0TMPTR69HL RSCAN0.TMPTR69.UINT8[HL]
#define RSCAN0TMPTR69HH RSCAN0.TMPTR69.UINT8[HH]
#define RSCAN0TMDF069 RSCAN0.TMDF069.UINT32
#define RSCAN0TMDF069L RSCAN0.TMDF069.UINT16[L]
#define RSCAN0TMDF069LL RSCAN0.TMDF069.UINT8[LL]
#define RSCAN0TMDF069LH RSCAN0.TMDF069.UINT8[LH]
#define RSCAN0TMDF069H RSCAN0.TMDF069.UINT16[H]
#define RSCAN0TMDF069HL RSCAN0.TMDF069.UINT8[HL]
#define RSCAN0TMDF069HH RSCAN0.TMDF069.UINT8[HH]
#define RSCAN0TMDF169 RSCAN0.TMDF169.UINT32
#define RSCAN0TMDF169L RSCAN0.TMDF169.UINT16[L]
#define RSCAN0TMDF169LL RSCAN0.TMDF169.UINT8[LL]
#define RSCAN0TMDF169LH RSCAN0.TMDF169.UINT8[LH]
#define RSCAN0TMDF169H RSCAN0.TMDF169.UINT16[H]
#define RSCAN0TMDF169HL RSCAN0.TMDF169.UINT8[HL]
#define RSCAN0TMDF169HH RSCAN0.TMDF169.UINT8[HH]
#define RSCAN0TMID70 RSCAN0.TMID70.UINT32
#define RSCAN0TMID70L RSCAN0.TMID70.UINT16[L]
#define RSCAN0TMID70LL RSCAN0.TMID70.UINT8[LL]
#define RSCAN0TMID70LH RSCAN0.TMID70.UINT8[LH]
#define RSCAN0TMID70H RSCAN0.TMID70.UINT16[H]
#define RSCAN0TMID70HL RSCAN0.TMID70.UINT8[HL]
#define RSCAN0TMID70HH RSCAN0.TMID70.UINT8[HH]
#define RSCAN0TMPTR70 RSCAN0.TMPTR70.UINT32
#define RSCAN0TMPTR70L RSCAN0.TMPTR70.UINT16[L]
#define RSCAN0TMPTR70LL RSCAN0.TMPTR70.UINT8[LL]
#define RSCAN0TMPTR70LH RSCAN0.TMPTR70.UINT8[LH]
#define RSCAN0TMPTR70H RSCAN0.TMPTR70.UINT16[H]
#define RSCAN0TMPTR70HL RSCAN0.TMPTR70.UINT8[HL]
#define RSCAN0TMPTR70HH RSCAN0.TMPTR70.UINT8[HH]
#define RSCAN0TMDF070 RSCAN0.TMDF070.UINT32
#define RSCAN0TMDF070L RSCAN0.TMDF070.UINT16[L]
#define RSCAN0TMDF070LL RSCAN0.TMDF070.UINT8[LL]
#define RSCAN0TMDF070LH RSCAN0.TMDF070.UINT8[LH]
#define RSCAN0TMDF070H RSCAN0.TMDF070.UINT16[H]
#define RSCAN0TMDF070HL RSCAN0.TMDF070.UINT8[HL]
#define RSCAN0TMDF070HH RSCAN0.TMDF070.UINT8[HH]
#define RSCAN0TMDF170 RSCAN0.TMDF170.UINT32
#define RSCAN0TMDF170L RSCAN0.TMDF170.UINT16[L]
#define RSCAN0TMDF170LL RSCAN0.TMDF170.UINT8[LL]
#define RSCAN0TMDF170LH RSCAN0.TMDF170.UINT8[LH]
#define RSCAN0TMDF170H RSCAN0.TMDF170.UINT16[H]
#define RSCAN0TMDF170HL RSCAN0.TMDF170.UINT8[HL]
#define RSCAN0TMDF170HH RSCAN0.TMDF170.UINT8[HH]
#define RSCAN0TMID71 RSCAN0.TMID71.UINT32
#define RSCAN0TMID71L RSCAN0.TMID71.UINT16[L]
#define RSCAN0TMID71LL RSCAN0.TMID71.UINT8[LL]
#define RSCAN0TMID71LH RSCAN0.TMID71.UINT8[LH]
#define RSCAN0TMID71H RSCAN0.TMID71.UINT16[H]
#define RSCAN0TMID71HL RSCAN0.TMID71.UINT8[HL]
#define RSCAN0TMID71HH RSCAN0.TMID71.UINT8[HH]
#define RSCAN0TMPTR71 RSCAN0.TMPTR71.UINT32
#define RSCAN0TMPTR71L RSCAN0.TMPTR71.UINT16[L]
#define RSCAN0TMPTR71LL RSCAN0.TMPTR71.UINT8[LL]
#define RSCAN0TMPTR71LH RSCAN0.TMPTR71.UINT8[LH]
#define RSCAN0TMPTR71H RSCAN0.TMPTR71.UINT16[H]
#define RSCAN0TMPTR71HL RSCAN0.TMPTR71.UINT8[HL]
#define RSCAN0TMPTR71HH RSCAN0.TMPTR71.UINT8[HH]
#define RSCAN0TMDF071 RSCAN0.TMDF071.UINT32
#define RSCAN0TMDF071L RSCAN0.TMDF071.UINT16[L]
#define RSCAN0TMDF071LL RSCAN0.TMDF071.UINT8[LL]
#define RSCAN0TMDF071LH RSCAN0.TMDF071.UINT8[LH]
#define RSCAN0TMDF071H RSCAN0.TMDF071.UINT16[H]
#define RSCAN0TMDF071HL RSCAN0.TMDF071.UINT8[HL]
#define RSCAN0TMDF071HH RSCAN0.TMDF071.UINT8[HH]
#define RSCAN0TMDF171 RSCAN0.TMDF171.UINT32
#define RSCAN0TMDF171L RSCAN0.TMDF171.UINT16[L]
#define RSCAN0TMDF171LL RSCAN0.TMDF171.UINT8[LL]
#define RSCAN0TMDF171LH RSCAN0.TMDF171.UINT8[LH]
#define RSCAN0TMDF171H RSCAN0.TMDF171.UINT16[H]
#define RSCAN0TMDF171HL RSCAN0.TMDF171.UINT8[HL]
#define RSCAN0TMDF171HH RSCAN0.TMDF171.UINT8[HH]
#define RSCAN0TMID72 RSCAN0.TMID72.UINT32
#define RSCAN0TMID72L RSCAN0.TMID72.UINT16[L]
#define RSCAN0TMID72LL RSCAN0.TMID72.UINT8[LL]
#define RSCAN0TMID72LH RSCAN0.TMID72.UINT8[LH]
#define RSCAN0TMID72H RSCAN0.TMID72.UINT16[H]
#define RSCAN0TMID72HL RSCAN0.TMID72.UINT8[HL]
#define RSCAN0TMID72HH RSCAN0.TMID72.UINT8[HH]
#define RSCAN0TMPTR72 RSCAN0.TMPTR72.UINT32
#define RSCAN0TMPTR72L RSCAN0.TMPTR72.UINT16[L]
#define RSCAN0TMPTR72LL RSCAN0.TMPTR72.UINT8[LL]
#define RSCAN0TMPTR72LH RSCAN0.TMPTR72.UINT8[LH]
#define RSCAN0TMPTR72H RSCAN0.TMPTR72.UINT16[H]
#define RSCAN0TMPTR72HL RSCAN0.TMPTR72.UINT8[HL]
#define RSCAN0TMPTR72HH RSCAN0.TMPTR72.UINT8[HH]
#define RSCAN0TMDF072 RSCAN0.TMDF072.UINT32
#define RSCAN0TMDF072L RSCAN0.TMDF072.UINT16[L]
#define RSCAN0TMDF072LL RSCAN0.TMDF072.UINT8[LL]
#define RSCAN0TMDF072LH RSCAN0.TMDF072.UINT8[LH]
#define RSCAN0TMDF072H RSCAN0.TMDF072.UINT16[H]
#define RSCAN0TMDF072HL RSCAN0.TMDF072.UINT8[HL]
#define RSCAN0TMDF072HH RSCAN0.TMDF072.UINT8[HH]
#define RSCAN0TMDF172 RSCAN0.TMDF172.UINT32
#define RSCAN0TMDF172L RSCAN0.TMDF172.UINT16[L]
#define RSCAN0TMDF172LL RSCAN0.TMDF172.UINT8[LL]
#define RSCAN0TMDF172LH RSCAN0.TMDF172.UINT8[LH]
#define RSCAN0TMDF172H RSCAN0.TMDF172.UINT16[H]
#define RSCAN0TMDF172HL RSCAN0.TMDF172.UINT8[HL]
#define RSCAN0TMDF172HH RSCAN0.TMDF172.UINT8[HH]
#define RSCAN0TMID73 RSCAN0.TMID73.UINT32
#define RSCAN0TMID73L RSCAN0.TMID73.UINT16[L]
#define RSCAN0TMID73LL RSCAN0.TMID73.UINT8[LL]
#define RSCAN0TMID73LH RSCAN0.TMID73.UINT8[LH]
#define RSCAN0TMID73H RSCAN0.TMID73.UINT16[H]
#define RSCAN0TMID73HL RSCAN0.TMID73.UINT8[HL]
#define RSCAN0TMID73HH RSCAN0.TMID73.UINT8[HH]
#define RSCAN0TMPTR73 RSCAN0.TMPTR73.UINT32
#define RSCAN0TMPTR73L RSCAN0.TMPTR73.UINT16[L]
#define RSCAN0TMPTR73LL RSCAN0.TMPTR73.UINT8[LL]
#define RSCAN0TMPTR73LH RSCAN0.TMPTR73.UINT8[LH]
#define RSCAN0TMPTR73H RSCAN0.TMPTR73.UINT16[H]
#define RSCAN0TMPTR73HL RSCAN0.TMPTR73.UINT8[HL]
#define RSCAN0TMPTR73HH RSCAN0.TMPTR73.UINT8[HH]
#define RSCAN0TMDF073 RSCAN0.TMDF073.UINT32
#define RSCAN0TMDF073L RSCAN0.TMDF073.UINT16[L]
#define RSCAN0TMDF073LL RSCAN0.TMDF073.UINT8[LL]
#define RSCAN0TMDF073LH RSCAN0.TMDF073.UINT8[LH]
#define RSCAN0TMDF073H RSCAN0.TMDF073.UINT16[H]
#define RSCAN0TMDF073HL RSCAN0.TMDF073.UINT8[HL]
#define RSCAN0TMDF073HH RSCAN0.TMDF073.UINT8[HH]
#define RSCAN0TMDF173 RSCAN0.TMDF173.UINT32
#define RSCAN0TMDF173L RSCAN0.TMDF173.UINT16[L]
#define RSCAN0TMDF173LL RSCAN0.TMDF173.UINT8[LL]
#define RSCAN0TMDF173LH RSCAN0.TMDF173.UINT8[LH]
#define RSCAN0TMDF173H RSCAN0.TMDF173.UINT16[H]
#define RSCAN0TMDF173HL RSCAN0.TMDF173.UINT8[HL]
#define RSCAN0TMDF173HH RSCAN0.TMDF173.UINT8[HH]
#define RSCAN0TMID74 RSCAN0.TMID74.UINT32
#define RSCAN0TMID74L RSCAN0.TMID74.UINT16[L]
#define RSCAN0TMID74LL RSCAN0.TMID74.UINT8[LL]
#define RSCAN0TMID74LH RSCAN0.TMID74.UINT8[LH]
#define RSCAN0TMID74H RSCAN0.TMID74.UINT16[H]
#define RSCAN0TMID74HL RSCAN0.TMID74.UINT8[HL]
#define RSCAN0TMID74HH RSCAN0.TMID74.UINT8[HH]
#define RSCAN0TMPTR74 RSCAN0.TMPTR74.UINT32
#define RSCAN0TMPTR74L RSCAN0.TMPTR74.UINT16[L]
#define RSCAN0TMPTR74LL RSCAN0.TMPTR74.UINT8[LL]
#define RSCAN0TMPTR74LH RSCAN0.TMPTR74.UINT8[LH]
#define RSCAN0TMPTR74H RSCAN0.TMPTR74.UINT16[H]
#define RSCAN0TMPTR74HL RSCAN0.TMPTR74.UINT8[HL]
#define RSCAN0TMPTR74HH RSCAN0.TMPTR74.UINT8[HH]
#define RSCAN0TMDF074 RSCAN0.TMDF074.UINT32
#define RSCAN0TMDF074L RSCAN0.TMDF074.UINT16[L]
#define RSCAN0TMDF074LL RSCAN0.TMDF074.UINT8[LL]
#define RSCAN0TMDF074LH RSCAN0.TMDF074.UINT8[LH]
#define RSCAN0TMDF074H RSCAN0.TMDF074.UINT16[H]
#define RSCAN0TMDF074HL RSCAN0.TMDF074.UINT8[HL]
#define RSCAN0TMDF074HH RSCAN0.TMDF074.UINT8[HH]
#define RSCAN0TMDF174 RSCAN0.TMDF174.UINT32
#define RSCAN0TMDF174L RSCAN0.TMDF174.UINT16[L]
#define RSCAN0TMDF174LL RSCAN0.TMDF174.UINT8[LL]
#define RSCAN0TMDF174LH RSCAN0.TMDF174.UINT8[LH]
#define RSCAN0TMDF174H RSCAN0.TMDF174.UINT16[H]
#define RSCAN0TMDF174HL RSCAN0.TMDF174.UINT8[HL]
#define RSCAN0TMDF174HH RSCAN0.TMDF174.UINT8[HH]
#define RSCAN0TMID75 RSCAN0.TMID75.UINT32
#define RSCAN0TMID75L RSCAN0.TMID75.UINT16[L]
#define RSCAN0TMID75LL RSCAN0.TMID75.UINT8[LL]
#define RSCAN0TMID75LH RSCAN0.TMID75.UINT8[LH]
#define RSCAN0TMID75H RSCAN0.TMID75.UINT16[H]
#define RSCAN0TMID75HL RSCAN0.TMID75.UINT8[HL]
#define RSCAN0TMID75HH RSCAN0.TMID75.UINT8[HH]
#define RSCAN0TMPTR75 RSCAN0.TMPTR75.UINT32
#define RSCAN0TMPTR75L RSCAN0.TMPTR75.UINT16[L]
#define RSCAN0TMPTR75LL RSCAN0.TMPTR75.UINT8[LL]
#define RSCAN0TMPTR75LH RSCAN0.TMPTR75.UINT8[LH]
#define RSCAN0TMPTR75H RSCAN0.TMPTR75.UINT16[H]
#define RSCAN0TMPTR75HL RSCAN0.TMPTR75.UINT8[HL]
#define RSCAN0TMPTR75HH RSCAN0.TMPTR75.UINT8[HH]
#define RSCAN0TMDF075 RSCAN0.TMDF075.UINT32
#define RSCAN0TMDF075L RSCAN0.TMDF075.UINT16[L]
#define RSCAN0TMDF075LL RSCAN0.TMDF075.UINT8[LL]
#define RSCAN0TMDF075LH RSCAN0.TMDF075.UINT8[LH]
#define RSCAN0TMDF075H RSCAN0.TMDF075.UINT16[H]
#define RSCAN0TMDF075HL RSCAN0.TMDF075.UINT8[HL]
#define RSCAN0TMDF075HH RSCAN0.TMDF075.UINT8[HH]
#define RSCAN0TMDF175 RSCAN0.TMDF175.UINT32
#define RSCAN0TMDF175L RSCAN0.TMDF175.UINT16[L]
#define RSCAN0TMDF175LL RSCAN0.TMDF175.UINT8[LL]
#define RSCAN0TMDF175LH RSCAN0.TMDF175.UINT8[LH]
#define RSCAN0TMDF175H RSCAN0.TMDF175.UINT16[H]
#define RSCAN0TMDF175HL RSCAN0.TMDF175.UINT8[HL]
#define RSCAN0TMDF175HH RSCAN0.TMDF175.UINT8[HH]
#define RSCAN0TMID76 RSCAN0.TMID76.UINT32
#define RSCAN0TMID76L RSCAN0.TMID76.UINT16[L]
#define RSCAN0TMID76LL RSCAN0.TMID76.UINT8[LL]
#define RSCAN0TMID76LH RSCAN0.TMID76.UINT8[LH]
#define RSCAN0TMID76H RSCAN0.TMID76.UINT16[H]
#define RSCAN0TMID76HL RSCAN0.TMID76.UINT8[HL]
#define RSCAN0TMID76HH RSCAN0.TMID76.UINT8[HH]
#define RSCAN0TMPTR76 RSCAN0.TMPTR76.UINT32
#define RSCAN0TMPTR76L RSCAN0.TMPTR76.UINT16[L]
#define RSCAN0TMPTR76LL RSCAN0.TMPTR76.UINT8[LL]
#define RSCAN0TMPTR76LH RSCAN0.TMPTR76.UINT8[LH]
#define RSCAN0TMPTR76H RSCAN0.TMPTR76.UINT16[H]
#define RSCAN0TMPTR76HL RSCAN0.TMPTR76.UINT8[HL]
#define RSCAN0TMPTR76HH RSCAN0.TMPTR76.UINT8[HH]
#define RSCAN0TMDF076 RSCAN0.TMDF076.UINT32
#define RSCAN0TMDF076L RSCAN0.TMDF076.UINT16[L]
#define RSCAN0TMDF076LL RSCAN0.TMDF076.UINT8[LL]
#define RSCAN0TMDF076LH RSCAN0.TMDF076.UINT8[LH]
#define RSCAN0TMDF076H RSCAN0.TMDF076.UINT16[H]
#define RSCAN0TMDF076HL RSCAN0.TMDF076.UINT8[HL]
#define RSCAN0TMDF076HH RSCAN0.TMDF076.UINT8[HH]
#define RSCAN0TMDF176 RSCAN0.TMDF176.UINT32
#define RSCAN0TMDF176L RSCAN0.TMDF176.UINT16[L]
#define RSCAN0TMDF176LL RSCAN0.TMDF176.UINT8[LL]
#define RSCAN0TMDF176LH RSCAN0.TMDF176.UINT8[LH]
#define RSCAN0TMDF176H RSCAN0.TMDF176.UINT16[H]
#define RSCAN0TMDF176HL RSCAN0.TMDF176.UINT8[HL]
#define RSCAN0TMDF176HH RSCAN0.TMDF176.UINT8[HH]
#define RSCAN0TMID77 RSCAN0.TMID77.UINT32
#define RSCAN0TMID77L RSCAN0.TMID77.UINT16[L]
#define RSCAN0TMID77LL RSCAN0.TMID77.UINT8[LL]
#define RSCAN0TMID77LH RSCAN0.TMID77.UINT8[LH]
#define RSCAN0TMID77H RSCAN0.TMID77.UINT16[H]
#define RSCAN0TMID77HL RSCAN0.TMID77.UINT8[HL]
#define RSCAN0TMID77HH RSCAN0.TMID77.UINT8[HH]
#define RSCAN0TMPTR77 RSCAN0.TMPTR77.UINT32
#define RSCAN0TMPTR77L RSCAN0.TMPTR77.UINT16[L]
#define RSCAN0TMPTR77LL RSCAN0.TMPTR77.UINT8[LL]
#define RSCAN0TMPTR77LH RSCAN0.TMPTR77.UINT8[LH]
#define RSCAN0TMPTR77H RSCAN0.TMPTR77.UINT16[H]
#define RSCAN0TMPTR77HL RSCAN0.TMPTR77.UINT8[HL]
#define RSCAN0TMPTR77HH RSCAN0.TMPTR77.UINT8[HH]
#define RSCAN0TMDF077 RSCAN0.TMDF077.UINT32
#define RSCAN0TMDF077L RSCAN0.TMDF077.UINT16[L]
#define RSCAN0TMDF077LL RSCAN0.TMDF077.UINT8[LL]
#define RSCAN0TMDF077LH RSCAN0.TMDF077.UINT8[LH]
#define RSCAN0TMDF077H RSCAN0.TMDF077.UINT16[H]
#define RSCAN0TMDF077HL RSCAN0.TMDF077.UINT8[HL]
#define RSCAN0TMDF077HH RSCAN0.TMDF077.UINT8[HH]
#define RSCAN0TMDF177 RSCAN0.TMDF177.UINT32
#define RSCAN0TMDF177L RSCAN0.TMDF177.UINT16[L]
#define RSCAN0TMDF177LL RSCAN0.TMDF177.UINT8[LL]
#define RSCAN0TMDF177LH RSCAN0.TMDF177.UINT8[LH]
#define RSCAN0TMDF177H RSCAN0.TMDF177.UINT16[H]
#define RSCAN0TMDF177HL RSCAN0.TMDF177.UINT8[HL]
#define RSCAN0TMDF177HH RSCAN0.TMDF177.UINT8[HH]
#define RSCAN0TMID78 RSCAN0.TMID78.UINT32
#define RSCAN0TMID78L RSCAN0.TMID78.UINT16[L]
#define RSCAN0TMID78LL RSCAN0.TMID78.UINT8[LL]
#define RSCAN0TMID78LH RSCAN0.TMID78.UINT8[LH]
#define RSCAN0TMID78H RSCAN0.TMID78.UINT16[H]
#define RSCAN0TMID78HL RSCAN0.TMID78.UINT8[HL]
#define RSCAN0TMID78HH RSCAN0.TMID78.UINT8[HH]
#define RSCAN0TMPTR78 RSCAN0.TMPTR78.UINT32
#define RSCAN0TMPTR78L RSCAN0.TMPTR78.UINT16[L]
#define RSCAN0TMPTR78LL RSCAN0.TMPTR78.UINT8[LL]
#define RSCAN0TMPTR78LH RSCAN0.TMPTR78.UINT8[LH]
#define RSCAN0TMPTR78H RSCAN0.TMPTR78.UINT16[H]
#define RSCAN0TMPTR78HL RSCAN0.TMPTR78.UINT8[HL]
#define RSCAN0TMPTR78HH RSCAN0.TMPTR78.UINT8[HH]
#define RSCAN0TMDF078 RSCAN0.TMDF078.UINT32
#define RSCAN0TMDF078L RSCAN0.TMDF078.UINT16[L]
#define RSCAN0TMDF078LL RSCAN0.TMDF078.UINT8[LL]
#define RSCAN0TMDF078LH RSCAN0.TMDF078.UINT8[LH]
#define RSCAN0TMDF078H RSCAN0.TMDF078.UINT16[H]
#define RSCAN0TMDF078HL RSCAN0.TMDF078.UINT8[HL]
#define RSCAN0TMDF078HH RSCAN0.TMDF078.UINT8[HH]
#define RSCAN0TMDF178 RSCAN0.TMDF178.UINT32
#define RSCAN0TMDF178L RSCAN0.TMDF178.UINT16[L]
#define RSCAN0TMDF178LL RSCAN0.TMDF178.UINT8[LL]
#define RSCAN0TMDF178LH RSCAN0.TMDF178.UINT8[LH]
#define RSCAN0TMDF178H RSCAN0.TMDF178.UINT16[H]
#define RSCAN0TMDF178HL RSCAN0.TMDF178.UINT8[HL]
#define RSCAN0TMDF178HH RSCAN0.TMDF178.UINT8[HH]
#define RSCAN0TMID79 RSCAN0.TMID79.UINT32
#define RSCAN0TMID79L RSCAN0.TMID79.UINT16[L]
#define RSCAN0TMID79LL RSCAN0.TMID79.UINT8[LL]
#define RSCAN0TMID79LH RSCAN0.TMID79.UINT8[LH]
#define RSCAN0TMID79H RSCAN0.TMID79.UINT16[H]
#define RSCAN0TMID79HL RSCAN0.TMID79.UINT8[HL]
#define RSCAN0TMID79HH RSCAN0.TMID79.UINT8[HH]
#define RSCAN0TMPTR79 RSCAN0.TMPTR79.UINT32
#define RSCAN0TMPTR79L RSCAN0.TMPTR79.UINT16[L]
#define RSCAN0TMPTR79LL RSCAN0.TMPTR79.UINT8[LL]
#define RSCAN0TMPTR79LH RSCAN0.TMPTR79.UINT8[LH]
#define RSCAN0TMPTR79H RSCAN0.TMPTR79.UINT16[H]
#define RSCAN0TMPTR79HL RSCAN0.TMPTR79.UINT8[HL]
#define RSCAN0TMPTR79HH RSCAN0.TMPTR79.UINT8[HH]
#define RSCAN0TMDF079 RSCAN0.TMDF079.UINT32
#define RSCAN0TMDF079L RSCAN0.TMDF079.UINT16[L]
#define RSCAN0TMDF079LL RSCAN0.TMDF079.UINT8[LL]
#define RSCAN0TMDF079LH RSCAN0.TMDF079.UINT8[LH]
#define RSCAN0TMDF079H RSCAN0.TMDF079.UINT16[H]
#define RSCAN0TMDF079HL RSCAN0.TMDF079.UINT8[HL]
#define RSCAN0TMDF079HH RSCAN0.TMDF079.UINT8[HH]
#define RSCAN0TMDF179 RSCAN0.TMDF179.UINT32
#define RSCAN0TMDF179L RSCAN0.TMDF179.UINT16[L]
#define RSCAN0TMDF179LL RSCAN0.TMDF179.UINT8[LL]
#define RSCAN0TMDF179LH RSCAN0.TMDF179.UINT8[LH]
#define RSCAN0TMDF179H RSCAN0.TMDF179.UINT16[H]
#define RSCAN0TMDF179HL RSCAN0.TMDF179.UINT8[HL]
#define RSCAN0TMDF179HH RSCAN0.TMDF179.UINT8[HH]
#define RSCAN0THLACC0 RSCAN0.THLACC0.UINT32
#define RSCAN0THLACC0L RSCAN0.THLACC0.UINT16[L]
#define RSCAN0THLACC0LL RSCAN0.THLACC0.UINT8[LL]
#define RSCAN0THLACC0LH RSCAN0.THLACC0.UINT8[LH]
#define RSCAN0THLACC0H RSCAN0.THLACC0.UINT16[H]
#define RSCAN0THLACC0HL RSCAN0.THLACC0.UINT8[HL]
#define RSCAN0THLACC0HH RSCAN0.THLACC0.UINT8[HH]
#define RSCAN0THLACC1 RSCAN0.THLACC1.UINT32
#define RSCAN0THLACC1L RSCAN0.THLACC1.UINT16[L]
#define RSCAN0THLACC1LL RSCAN0.THLACC1.UINT8[LL]
#define RSCAN0THLACC1LH RSCAN0.THLACC1.UINT8[LH]
#define RSCAN0THLACC1H RSCAN0.THLACC1.UINT16[H]
#define RSCAN0THLACC1HL RSCAN0.THLACC1.UINT8[HL]
#define RSCAN0THLACC1HH RSCAN0.THLACC1.UINT8[HH]
#define RSCAN0THLACC2 RSCAN0.THLACC2.UINT32
#define RSCAN0THLACC2L RSCAN0.THLACC2.UINT16[L]
#define RSCAN0THLACC2LL RSCAN0.THLACC2.UINT8[LL]
#define RSCAN0THLACC2LH RSCAN0.THLACC2.UINT8[LH]
#define RSCAN0THLACC2H RSCAN0.THLACC2.UINT16[H]
#define RSCAN0THLACC2HL RSCAN0.THLACC2.UINT8[HL]
#define RSCAN0THLACC2HH RSCAN0.THLACC2.UINT8[HH]
#define RSCAN0THLACC3 RSCAN0.THLACC3.UINT32
#define RSCAN0THLACC3L RSCAN0.THLACC3.UINT16[L]
#define RSCAN0THLACC3LL RSCAN0.THLACC3.UINT8[LL]
#define RSCAN0THLACC3LH RSCAN0.THLACC3.UINT8[LH]
#define RSCAN0THLACC3H RSCAN0.THLACC3.UINT16[H]
#define RSCAN0THLACC3HL RSCAN0.THLACC3.UINT8[HL]
#define RSCAN0THLACC3HH RSCAN0.THLACC3.UINT8[HH]
#define RSCAN0THLACC4 RSCAN0.THLACC4.UINT32
#define RSCAN0THLACC4L RSCAN0.THLACC4.UINT16[L]
#define RSCAN0THLACC4LL RSCAN0.THLACC4.UINT8[LL]
#define RSCAN0THLACC4LH RSCAN0.THLACC4.UINT8[LH]
#define RSCAN0THLACC4H RSCAN0.THLACC4.UINT16[H]
#define RSCAN0THLACC4HL RSCAN0.THLACC4.UINT8[HL]
#define RSCAN0THLACC4HH RSCAN0.THLACC4.UINT8[HH]
/* <-SEC M1.10.1 */
/* <-QAC 0857 */
/* <-QAC 0639 */
#endif
