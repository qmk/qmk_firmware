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
* File Name : gpio_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef GPIO_IODEFINE_H
#define GPIO_IODEFINE_H
/* ->QAC 0639 : Over 127 members (C90) */
/* ->SEC M1.10.1 : Not magic number */

struct st_gpio
{                                                          /* GPIO             */
/* start of struct st_gpio_from_p1 */
    volatile uint16_t P1;                                     /*  P1              */
    volatile uint8_t   dummy348[2];                            /*                  */
/* end of struct st_gpio_from_p1 */
/* start of struct st_gpio_from_p1 */
    volatile uint16_t P2;                                     /*  P2              */
    volatile uint8_t   dummy349[2];                            /*                  */
/* end of struct st_gpio_from_p1 */
/* start of struct st_gpio_from_p1 */
    volatile uint16_t P3;                                     /*  P3              */
    volatile uint8_t   dummy350[2];                            /*                  */
/* end of struct st_gpio_from_p1 */
/* start of struct st_gpio_from_p1 */
    volatile uint16_t P4;                                     /*  P4              */
    volatile uint8_t   dummy351[2];                            /*                  */
/* end of struct st_gpio_from_p1 */
/* start of struct st_gpio_from_p1 */
    volatile uint16_t P5;                                     /*  P5              */
    volatile uint8_t   dummy352[2];                            /*                  */
/* end of struct st_gpio_from_p1 */
/* start of struct st_gpio_from_p1 */
    volatile uint16_t P6;                                     /*  P6              */
    volatile uint8_t   dummy353[2];                            /*                  */
/* end of struct st_gpio_from_p1 */
/* start of struct st_gpio_from_p1 */
    volatile uint16_t P7;                                     /*  P7              */
    volatile uint8_t   dummy354[2];                            /*                  */
/* end of struct st_gpio_from_p1 */
/* start of struct st_gpio_from_p1 */
    volatile uint16_t P8;                                     /*  P8              */
    volatile uint8_t   dummy355[2];                            /*                  */
/* end of struct st_gpio_from_p1 */
/* start of struct st_gpio_from_p1 */
    volatile uint16_t P9;                                     /*  P9              */
    volatile uint8_t   dummy356[2];                            /*                  */
/* end of struct st_gpio_from_p1 */
/* start of struct st_gpio_from_p1 */
    volatile uint16_t P10;                                    /*  P10             */
    volatile uint8_t   dummy357[2];                            /*                  */
/* end of struct st_gpio_from_p1 */
/* start of struct st_gpio_from_p1 */
    volatile uint16_t P11;                                    /*  P11             */
    volatile uint8_t   dummy3580[2];                           /*                  */
/* end of struct st_gpio_from_p1 */
    volatile uint8_t   dummy3581[212];                         /*                  */
#define GPIO_PSRn_COUNT 11
    volatile uint32_t  PSR1;                                   /*  PSR1            */
    volatile uint32_t  PSR2;                                   /*  PSR2            */
    volatile uint32_t  PSR3;                                   /*  PSR3            */
    volatile uint32_t  PSR4;                                   /*  PSR4            */
    volatile uint32_t  PSR5;                                   /*  PSR5            */
    volatile uint32_t  PSR6;                                   /*  PSR6            */
    volatile uint32_t  PSR7;                                   /*  PSR7            */
    volatile uint32_t  PSR8;                                   /*  PSR8            */
    volatile uint32_t  PSR9;                                   /*  PSR9            */
    volatile uint32_t  PSR10;                                  /*  PSR10           */
    volatile uint32_t  PSR11;                                  /*  PSR11           */
    volatile uint8_t   dummy359[208];                          /*                  */
/* start of struct st_gpio_from_ppr0 */
    volatile uint16_t PPR0;                                   /*  PPR0            */
    volatile uint8_t   dummy360[2];                            /*                  */
/* end of struct st_gpio_from_ppr0 */
/* start of struct st_gpio_from_ppr0 */
    volatile uint16_t PPR1;                                   /*  PPR1            */
    volatile uint8_t   dummy361[2];                            /*                  */
/* end of struct st_gpio_from_ppr0 */
/* start of struct st_gpio_from_ppr0 */
    volatile uint16_t PPR2;                                   /*  PPR2            */
    volatile uint8_t   dummy362[2];                            /*                  */
/* end of struct st_gpio_from_ppr0 */
/* start of struct st_gpio_from_ppr0 */
    volatile uint16_t PPR3;                                   /*  PPR3            */
    volatile uint8_t   dummy363[2];                            /*                  */
/* end of struct st_gpio_from_ppr0 */
/* start of struct st_gpio_from_ppr0 */
    volatile uint16_t PPR4;                                   /*  PPR4            */
    volatile uint8_t   dummy364[2];                            /*                  */
/* end of struct st_gpio_from_ppr0 */
/* start of struct st_gpio_from_ppr0 */
    volatile uint16_t PPR5;                                   /*  PPR5            */
    volatile uint8_t   dummy365[2];                            /*                  */
/* end of struct st_gpio_from_ppr0 */
/* start of struct st_gpio_from_ppr0 */
    volatile uint16_t PPR6;                                   /*  PPR6            */
    volatile uint8_t   dummy366[2];                            /*                  */
/* end of struct st_gpio_from_ppr0 */
/* start of struct st_gpio_from_ppr0 */
    volatile uint16_t PPR7;                                   /*  PPR7            */
    volatile uint8_t   dummy367[2];                            /*                  */
/* end of struct st_gpio_from_ppr0 */
/* start of struct st_gpio_from_ppr0 */
    volatile uint16_t PPR8;                                   /*  PPR8            */
    volatile uint8_t   dummy368[2];                            /*                  */
/* end of struct st_gpio_from_ppr0 */
/* start of struct st_gpio_from_ppr0 */
    volatile uint16_t PPR9;                                   /*  PPR9            */
    volatile uint8_t   dummy369[2];                            /*                  */
/* end of struct st_gpio_from_ppr0 */
/* start of struct st_gpio_from_ppr0 */
    volatile uint16_t PPR10;                                  /*  PPR10           */
    volatile uint8_t   dummy370[2];                            /*                  */
/* end of struct st_gpio_from_ppr0 */
/* start of struct st_gpio_from_ppr0 */
    volatile uint16_t PPR11;                                  /*  PPR11           */
    volatile uint8_t   dummy3710[2];                           /*                  */
/* end of struct st_gpio_from_ppr0 */
    volatile uint8_t   dummy3711[212];                         /*                  */
/* start of struct st_gpio_from_pm1 */
    volatile uint16_t PM1;                                    /*  PM1             */
    volatile uint8_t   dummy372[2];                            /*                  */
/* end of struct st_gpio_from_pm1 */
/* start of struct st_gpio_from_pm1 */
    volatile uint16_t PM2;                                    /*  PM2             */
    volatile uint8_t   dummy373[2];                            /*                  */
/* end of struct st_gpio_from_pm1 */
/* start of struct st_gpio_from_pm1 */
    volatile uint16_t PM3;                                    /*  PM3             */
    volatile uint8_t   dummy374[2];                            /*                  */
/* end of struct st_gpio_from_pm1 */
/* start of struct st_gpio_from_pm1 */
    volatile uint16_t PM4;                                    /*  PM4             */
    volatile uint8_t   dummy375[2];                            /*                  */
/* end of struct st_gpio_from_pm1 */
/* start of struct st_gpio_from_pm1 */
    volatile uint16_t PM5;                                    /*  PM5             */
    volatile uint8_t   dummy376[2];                            /*                  */
/* end of struct st_gpio_from_pm1 */
/* start of struct st_gpio_from_pm1 */
    volatile uint16_t PM6;                                    /*  PM6             */
    volatile uint8_t   dummy377[2];                            /*                  */
/* end of struct st_gpio_from_pm1 */
/* start of struct st_gpio_from_pm1 */
    volatile uint16_t PM7;                                    /*  PM7             */
    volatile uint8_t   dummy378[2];                            /*                  */
/* end of struct st_gpio_from_pm1 */
/* start of struct st_gpio_from_pm1 */
    volatile uint16_t PM8;                                    /*  PM8             */
    volatile uint8_t   dummy379[2];                            /*                  */
/* end of struct st_gpio_from_pm1 */
/* start of struct st_gpio_from_pm1 */
    volatile uint16_t PM9;                                    /*  PM9             */
    volatile uint8_t   dummy380[2];                            /*                  */
/* end of struct st_gpio_from_pm1 */
/* start of struct st_gpio_from_pm1 */
    volatile uint16_t PM10;                                   /*  PM10            */
    volatile uint8_t   dummy381[2];                            /*                  */
/* end of struct st_gpio_from_pm1 */
/* start of struct st_gpio_from_pm1 */
    volatile uint16_t PM11;                                   /*  PM11            */
    volatile uint8_t   dummy3820[2];                           /*                  */
/* end of struct st_gpio_from_pm1 */
    volatile uint8_t   dummy3821[208];                         /*                  */
/* start of struct st_gpio_from_pmc0 */
    volatile uint16_t PMC0;                                   /*  PMC0            */
    volatile uint8_t   dummy383[2];                            /*                  */
/* end of struct st_gpio_from_pmc0 */
/* start of struct st_gpio_from_pmc0 */
    volatile uint16_t PMC1;                                   /*  PMC1            */
    volatile uint8_t   dummy384[2];                            /*                  */
/* end of struct st_gpio_from_pmc0 */
/* start of struct st_gpio_from_pmc0 */
    volatile uint16_t PMC2;                                   /*  PMC2            */
    volatile uint8_t   dummy385[2];                            /*                  */
/* end of struct st_gpio_from_pmc0 */
/* start of struct st_gpio_from_pmc0 */
    volatile uint16_t PMC3;                                   /*  PMC3            */
    volatile uint8_t   dummy386[2];                            /*                  */
/* end of struct st_gpio_from_pmc0 */
/* start of struct st_gpio_from_pmc0 */
    volatile uint16_t PMC4;                                   /*  PMC4            */
    volatile uint8_t   dummy387[2];                            /*                  */
/* end of struct st_gpio_from_pmc0 */
/* start of struct st_gpio_from_pmc0 */
    volatile uint16_t PMC5;                                   /*  PMC5            */
    volatile uint8_t   dummy388[2];                            /*                  */
/* end of struct st_gpio_from_pmc0 */
/* start of struct st_gpio_from_pmc0 */
    volatile uint16_t PMC6;                                   /*  PMC6            */
    volatile uint8_t   dummy389[2];                            /*                  */
/* end of struct st_gpio_from_pmc0 */
/* start of struct st_gpio_from_pmc0 */
    volatile uint16_t PMC7;                                   /*  PMC7            */
    volatile uint8_t   dummy390[2];                            /*                  */
/* end of struct st_gpio_from_pmc0 */
/* start of struct st_gpio_from_pmc0 */
    volatile uint16_t PMC8;                                   /*  PMC8            */
    volatile uint8_t   dummy391[2];                            /*                  */
/* end of struct st_gpio_from_pmc0 */
/* start of struct st_gpio_from_pmc0 */
    volatile uint16_t PMC9;                                   /*  PMC9            */
    volatile uint8_t   dummy392[2];                            /*                  */
/* end of struct st_gpio_from_pmc0 */
/* start of struct st_gpio_from_pmc0 */
    volatile uint16_t PMC10;                                  /*  PMC10           */
    volatile uint8_t   dummy393[2];                            /*                  */
/* end of struct st_gpio_from_pmc0 */
/* start of struct st_gpio_from_pmc0 */
    volatile uint16_t PMC11;                                  /*  PMC11           */
    volatile uint8_t   dummy3940[2];                           /*                  */
/* end of struct st_gpio_from_pmc0 */
    volatile uint8_t   dummy3941[212];                         /*                  */
/* start of struct st_gpio_from_pfc1 */
    volatile uint16_t PFC1;                                   /*  PFC1            */
    volatile uint8_t   dummy395[2];                            /*                  */
/* end of struct st_gpio_from_pfc1 */
/* start of struct st_gpio_from_pfc1 */
    volatile uint16_t PFC2;                                   /*  PFC2            */
    volatile uint8_t   dummy396[2];                            /*                  */
/* end of struct st_gpio_from_pfc1 */
/* start of struct st_gpio_from_pfc1 */
    volatile uint16_t PFC3;                                   /*  PFC3            */
    volatile uint8_t   dummy397[2];                            /*                  */
/* end of struct st_gpio_from_pfc1 */
/* start of struct st_gpio_from_pfc1 */
    volatile uint16_t PFC4;                                   /*  PFC4            */
    volatile uint8_t   dummy398[2];                            /*                  */
/* end of struct st_gpio_from_pfc1 */
/* start of struct st_gpio_from_pfc1 */
    volatile uint16_t PFC5;                                   /*  PFC5            */
    volatile uint8_t   dummy399[2];                            /*                  */
/* end of struct st_gpio_from_pfc1 */
/* start of struct st_gpio_from_pfc1 */
    volatile uint16_t PFC6;                                   /*  PFC6            */
    volatile uint8_t   dummy400[2];                            /*                  */
/* end of struct st_gpio_from_pfc1 */
/* start of struct st_gpio_from_pfc1 */
    volatile uint16_t PFC7;                                   /*  PFC7            */
    volatile uint8_t   dummy401[2];                            /*                  */
/* end of struct st_gpio_from_pfc1 */
/* start of struct st_gpio_from_pfc1 */
    volatile uint16_t PFC8;                                   /*  PFC8            */
    volatile uint8_t   dummy402[2];                            /*                  */
/* end of struct st_gpio_from_pfc1 */
/* start of struct st_gpio_from_pfc1 */
    volatile uint16_t PFC9;                                   /*  PFC9            */
    volatile uint8_t   dummy403[2];                            /*                  */
/* end of struct st_gpio_from_pfc1 */
/* start of struct st_gpio_from_pfc1 */
    volatile uint16_t PFC10;                                  /*  PFC10           */
    volatile uint8_t   dummy404[2];                            /*                  */
/* end of struct st_gpio_from_pfc1 */
/* start of struct st_gpio_from_pfc1 */
    volatile uint16_t PFC11;                                  /*  PFC11           */
    volatile uint8_t   dummy4050[2];                           /*                  */
/* end of struct st_gpio_from_pfc1 */
    volatile uint8_t   dummy4051[212];                         /*                  */
/* start of struct st_gpio_from_pfce1 */
    volatile uint16_t PFCE1;                                  /*  PFCE1           */
    volatile uint8_t   dummy406[2];                            /*                  */
/* end of struct st_gpio_from_pfce1 */
/* start of struct st_gpio_from_pfce1 */
    volatile uint16_t PFCE2;                                  /*  PFCE2           */
    volatile uint8_t   dummy407[2];                            /*                  */
/* end of struct st_gpio_from_pfce1 */
/* start of struct st_gpio_from_pfce1 */
    volatile uint16_t PFCE3;                                  /*  PFCE3           */
    volatile uint8_t   dummy408[2];                            /*                  */
/* end of struct st_gpio_from_pfce1 */
/* start of struct st_gpio_from_pfce1 */
    volatile uint16_t PFCE4;                                  /*  PFCE4           */
    volatile uint8_t   dummy409[2];                            /*                  */
/* end of struct st_gpio_from_pfce1 */
/* start of struct st_gpio_from_pfce1 */
    volatile uint16_t PFCE5;                                  /*  PFCE5           */
    volatile uint8_t   dummy410[2];                            /*                  */
/* end of struct st_gpio_from_pfce1 */
/* start of struct st_gpio_from_pfce1 */
    volatile uint16_t PFCE6;                                  /*  PFCE6           */
    volatile uint8_t   dummy411[2];                            /*                  */
/* end of struct st_gpio_from_pfce1 */
/* start of struct st_gpio_from_pfce1 */
    volatile uint16_t PFCE7;                                  /*  PFCE7           */
    volatile uint8_t   dummy412[2];                            /*                  */
/* end of struct st_gpio_from_pfce1 */
/* start of struct st_gpio_from_pfce1 */
    volatile uint16_t PFCE8;                                  /*  PFCE8           */
    volatile uint8_t   dummy413[2];                            /*                  */
/* end of struct st_gpio_from_pfce1 */
/* start of struct st_gpio_from_pfce1 */
    volatile uint16_t PFCE9;                                  /*  PFCE9           */
    volatile uint8_t   dummy414[2];                            /*                  */
/* end of struct st_gpio_from_pfce1 */
/* start of struct st_gpio_from_pfce1 */
    volatile uint16_t PFCE10;                                 /*  PFCE10          */
    volatile uint8_t   dummy415[2];                            /*                  */
/* end of struct st_gpio_from_pfce1 */
/* start of struct st_gpio_from_pfce1 */
    volatile uint16_t PFCE11;                                 /*  PFCE11          */
    volatile uint8_t   dummy4160[2];                           /*                  */
/* end of struct st_gpio_from_pfce1 */
    volatile uint8_t   dummy4161[212];                         /*                  */
/* start of struct st_gpio_from_pnot1 */
    volatile uint16_t PNOT1;                                  /*  PNOT1           */
    volatile uint8_t   dummy417[2];                            /*                  */
/* end of struct st_gpio_from_pnot1 */
/* start of struct st_gpio_from_pnot1 */
    volatile uint16_t PNOT2;                                  /*  PNOT2           */
    volatile uint8_t   dummy418[2];                            /*                  */
/* end of struct st_gpio_from_pnot1 */
/* start of struct st_gpio_from_pnot1 */
    volatile uint16_t PNOT3;                                  /*  PNOT3           */
    volatile uint8_t   dummy419[2];                            /*                  */
/* end of struct st_gpio_from_pnot1 */
/* start of struct st_gpio_from_pnot1 */
    volatile uint16_t PNOT4;                                  /*  PNOT4           */
    volatile uint8_t   dummy420[2];                            /*                  */
/* end of struct st_gpio_from_pnot1 */
/* start of struct st_gpio_from_pnot1 */
    volatile uint16_t PNOT5;                                  /*  PNOT5           */
    volatile uint8_t   dummy421[2];                            /*                  */
/* end of struct st_gpio_from_pnot1 */
/* start of struct st_gpio_from_pnot1 */
    volatile uint16_t PNOT6;                                  /*  PNOT6           */
    volatile uint8_t   dummy422[2];                            /*                  */
/* end of struct st_gpio_from_pnot1 */
/* start of struct st_gpio_from_pnot1 */
    volatile uint16_t PNOT7;                                  /*  PNOT7           */
    volatile uint8_t   dummy423[2];                            /*                  */
/* end of struct st_gpio_from_pnot1 */
/* start of struct st_gpio_from_pnot1 */
    volatile uint16_t PNOT8;                                  /*  PNOT8           */
    volatile uint8_t   dummy424[2];                            /*                  */
/* end of struct st_gpio_from_pnot1 */
/* start of struct st_gpio_from_pnot1 */
    volatile uint16_t PNOT9;                                  /*  PNOT9           */
    volatile uint8_t   dummy425[2];                            /*                  */
/* end of struct st_gpio_from_pnot1 */
/* start of struct st_gpio_from_pnot1 */
    volatile uint16_t PNOT10;                                 /*  PNOT10          */
    volatile uint8_t   dummy426[2];                            /*                  */
/* end of struct st_gpio_from_pnot1 */
/* start of struct st_gpio_from_pnot1 */
    volatile uint16_t PNOT11;                                 /*  PNOT11          */
    volatile uint8_t   dummy4270[2];                           /*                  */
/* end of struct st_gpio_from_pnot1 */
    volatile uint8_t   dummy4271[212];                         /*                  */
#define GPIO_PMSRn_COUNT 11
    volatile uint32_t  PMSR1;                                  /*  PMSR1           */
    volatile uint32_t  PMSR2;                                  /*  PMSR2           */
    volatile uint32_t  PMSR3;                                  /*  PMSR3           */
    volatile uint32_t  PMSR4;                                  /*  PMSR4           */
    volatile uint32_t  PMSR5;                                  /*  PMSR5           */
    volatile uint32_t  PMSR6;                                  /*  PMSR6           */
    volatile uint32_t  PMSR7;                                  /*  PMSR7           */
    volatile uint32_t  PMSR8;                                  /*  PMSR8           */
    volatile uint32_t  PMSR9;                                  /*  PMSR9           */
    volatile uint32_t  PMSR10;                                 /*  PMSR10          */
    volatile uint32_t  PMSR11;                                 /*  PMSR11          */
    volatile uint8_t   dummy428[208];                          /*                  */
#define GPIO_PMCSRn_COUNT 12
    volatile uint32_t  PMCSR0;                                 /*  PMCSR0          */
    volatile uint32_t  PMCSR1;                                 /*  PMCSR1          */
    volatile uint32_t  PMCSR2;                                 /*  PMCSR2          */
    volatile uint32_t  PMCSR3;                                 /*  PMCSR3          */
    volatile uint32_t  PMCSR4;                                 /*  PMCSR4          */
    volatile uint32_t  PMCSR5;                                 /*  PMCSR5          */
    volatile uint32_t  PMCSR6;                                 /*  PMCSR6          */
    volatile uint32_t  PMCSR7;                                 /*  PMCSR7          */
    volatile uint32_t  PMCSR8;                                 /*  PMCSR8          */
    volatile uint32_t  PMCSR9;                                 /*  PMCSR9          */
    volatile uint32_t  PMCSR10;                                /*  PMCSR10         */
    volatile uint32_t  PMCSR11;                                /*  PMCSR11         */
    volatile uint8_t   dummy429[212];                          /*                  */
/* start of struct st_gpio_from_pfcae1 */
    volatile uint16_t PFCAE1;                                 /*  PFCAE1          */
    volatile uint8_t   dummy430[2];                            /*                  */
/* end of struct st_gpio_from_pfcae1 */
/* start of struct st_gpio_from_pfcae1 */
    volatile uint16_t PFCAE2;                                 /*  PFCAE2          */
    volatile uint8_t   dummy431[2];                            /*                  */
/* end of struct st_gpio_from_pfcae1 */
/* start of struct st_gpio_from_pfcae1 */
    volatile uint16_t PFCAE3;                                 /*  PFCAE3          */
    volatile uint8_t   dummy432[2];                            /*                  */
/* end of struct st_gpio_from_pfcae1 */
/* start of struct st_gpio_from_pfcae1 */
    volatile uint16_t PFCAE4;                                 /*  PFCAE4          */
    volatile uint8_t   dummy433[2];                            /*                  */
/* end of struct st_gpio_from_pfcae1 */
/* start of struct st_gpio_from_pfcae1 */
    volatile uint16_t PFCAE5;                                 /*  PFCAE5          */
    volatile uint8_t   dummy434[2];                            /*                  */
/* end of struct st_gpio_from_pfcae1 */
/* start of struct st_gpio_from_pfcae1 */
    volatile uint16_t PFCAE6;                                 /*  PFCAE6          */
    volatile uint8_t   dummy435[2];                            /*                  */
/* end of struct st_gpio_from_pfcae1 */
/* start of struct st_gpio_from_pfcae1 */
    volatile uint16_t PFCAE7;                                 /*  PFCAE7          */
    volatile uint8_t   dummy436[2];                            /*                  */
/* end of struct st_gpio_from_pfcae1 */
/* start of struct st_gpio_from_pfcae1 */
    volatile uint16_t PFCAE8;                                 /*  PFCAE8          */
    volatile uint8_t   dummy437[2];                            /*                  */
/* end of struct st_gpio_from_pfcae1 */
/* start of struct st_gpio_from_pfcae1 */
    volatile uint16_t PFCAE9;                                 /*  PFCAE9          */
    volatile uint8_t   dummy438[2];                            /*                  */
/* end of struct st_gpio_from_pfcae1 */
/* start of struct st_gpio_from_pfcae1 */
    volatile uint16_t PFCAE10;                                /*  PFCAE10         */
    volatile uint8_t   dummy439[2];                            /*                  */
/* end of struct st_gpio_from_pfcae1 */
/* start of struct st_gpio_from_pfcae1 */
    volatile uint16_t PFCAE11;                                /*  PFCAE11         */
    volatile uint8_t   dummy4400[2];                           /*                  */
/* end of struct st_gpio_from_pfcae1 */
    volatile uint8_t   dummy4401[464];                         /*                  */
    volatile uint32_t  SNCR;                                   /*  SNCR            */
    volatile uint8_t   dummy441[13308];                        /*                  */
    volatile uint16_t PIBC0;                                  /*  PIBC0           */
    volatile uint8_t   dummy442[2];                            /*                  */
/* start of struct st_gpio_from_pibc1 */
    volatile uint16_t PIBC1;                                  /*  PIBC1           */
    volatile uint8_t   dummy443[2];                            /*                  */
/* end of struct st_gpio_from_pibc1 */
/* start of struct st_gpio_from_pibc1 */
    volatile uint16_t PIBC2;                                  /*  PIBC2           */
    volatile uint8_t   dummy444[2];                            /*                  */
/* end of struct st_gpio_from_pibc1 */
/* start of struct st_gpio_from_pibc1 */
    volatile uint16_t PIBC3;                                  /*  PIBC3           */
    volatile uint8_t   dummy445[2];                            /*                  */
/* end of struct st_gpio_from_pibc1 */
/* start of struct st_gpio_from_pibc1 */
    volatile uint16_t PIBC4;                                  /*  PIBC4           */
    volatile uint8_t   dummy446[2];                            /*                  */
/* end of struct st_gpio_from_pibc1 */
/* start of struct st_gpio_from_pibc1 */
    volatile uint16_t PIBC5;                                  /*  PIBC5           */
    volatile uint8_t   dummy447[2];                            /*                  */
/* end of struct st_gpio_from_pibc1 */
/* start of struct st_gpio_from_pibc1 */
    volatile uint16_t PIBC6;                                  /*  PIBC6           */
    volatile uint8_t   dummy448[2];                            /*                  */
/* end of struct st_gpio_from_pibc1 */
/* start of struct st_gpio_from_pibc1 */
    volatile uint16_t PIBC7;                                  /*  PIBC7           */
    volatile uint8_t   dummy449[2];                            /*                  */
/* end of struct st_gpio_from_pibc1 */
/* start of struct st_gpio_from_pibc1 */
    volatile uint16_t PIBC8;                                  /*  PIBC8           */
    volatile uint8_t   dummy450[2];                            /*                  */
/* end of struct st_gpio_from_pibc1 */
/* start of struct st_gpio_from_pibc1 */
    volatile uint16_t PIBC9;                                  /*  PIBC9           */
    volatile uint8_t   dummy451[2];                            /*                  */
/* end of struct st_gpio_from_pibc1 */
/* start of struct st_gpio_from_pibc1 */
    volatile uint16_t PIBC10;                                 /*  PIBC10          */
    volatile uint8_t   dummy452[2];                            /*                  */
/* end of struct st_gpio_from_pibc1 */
/* start of struct st_gpio_from_pibc1 */
    volatile uint16_t PIBC11;                                 /*  PIBC11          */
    volatile uint8_t   dummy4530[2];                           /*                  */
/* end of struct st_gpio_from_pibc1 */
    volatile uint8_t   dummy4531[212];                         /*                  */
/* start of struct st_gpio_from_pbdc1 */
    volatile uint16_t PBDC1;                                  /*  PBDC1           */
    volatile uint8_t   dummy454[2];                            /*                  */
/* end of struct st_gpio_from_pbdc1 */
/* start of struct st_gpio_from_pbdc1 */
    volatile uint16_t PBDC2;                                  /*  PBDC2           */
    volatile uint8_t   dummy455[2];                            /*                  */
/* end of struct st_gpio_from_pbdc1 */
/* start of struct st_gpio_from_pbdc1 */
    volatile uint16_t PBDC3;                                  /*  PBDC3           */
    volatile uint8_t   dummy456[2];                            /*                  */
/* end of struct st_gpio_from_pbdc1 */
/* start of struct st_gpio_from_pbdc1 */
    volatile uint16_t PBDC4;                                  /*  PBDC4           */
    volatile uint8_t   dummy457[2];                            /*                  */
/* end of struct st_gpio_from_pbdc1 */
/* start of struct st_gpio_from_pbdc1 */
    volatile uint16_t PBDC5;                                  /*  PBDC5           */
    volatile uint8_t   dummy458[2];                            /*                  */
/* end of struct st_gpio_from_pbdc1 */
/* start of struct st_gpio_from_pbdc1 */
    volatile uint16_t PBDC6;                                  /*  PBDC6           */
    volatile uint8_t   dummy459[2];                            /*                  */
/* end of struct st_gpio_from_pbdc1 */
/* start of struct st_gpio_from_pbdc1 */
    volatile uint16_t PBDC7;                                  /*  PBDC7           */
    volatile uint8_t   dummy460[2];                            /*                  */
/* end of struct st_gpio_from_pbdc1 */
/* start of struct st_gpio_from_pbdc1 */
    volatile uint16_t PBDC8;                                  /*  PBDC8           */
    volatile uint8_t   dummy461[2];                            /*                  */
/* end of struct st_gpio_from_pbdc1 */
/* start of struct st_gpio_from_pbdc1 */
    volatile uint16_t PBDC9;                                  /*  PBDC9           */
    volatile uint8_t   dummy462[2];                            /*                  */
/* end of struct st_gpio_from_pbdc1 */
/* start of struct st_gpio_from_pbdc1 */
    volatile uint16_t PBDC10;                                 /*  PBDC10          */
    volatile uint8_t   dummy463[2];                            /*                  */
/* end of struct st_gpio_from_pbdc1 */
/* start of struct st_gpio_from_pbdc1 */
    volatile uint16_t PBDC11;                                 /*  PBDC11          */
    volatile uint8_t   dummy4640[2];                           /*                  */
/* end of struct st_gpio_from_pbdc1 */
    volatile uint8_t   dummy4641[212];                         /*                  */
/* start of struct st_gpio_from_pipc1 */
    volatile uint16_t PIPC1;                                  /*  PIPC1           */
    volatile uint8_t   dummy465[2];                            /*                  */
/* end of struct st_gpio_from_pipc1 */
/* start of struct st_gpio_from_pipc1 */
    volatile uint16_t PIPC2;                                  /*  PIPC2           */
    volatile uint8_t   dummy466[2];                            /*                  */
/* end of struct st_gpio_from_pipc1 */
/* start of struct st_gpio_from_pipc1 */
    volatile uint16_t PIPC3;                                  /*  PIPC3           */
    volatile uint8_t   dummy467[2];                            /*                  */
/* end of struct st_gpio_from_pipc1 */
/* start of struct st_gpio_from_pipc1 */
    volatile uint16_t PIPC4;                                  /*  PIPC4           */
    volatile uint8_t   dummy468[2];                            /*                  */
/* end of struct st_gpio_from_pipc1 */
/* start of struct st_gpio_from_pipc1 */
    volatile uint16_t PIPC5;                                  /*  PIPC5           */
    volatile uint8_t   dummy469[2];                            /*                  */
/* end of struct st_gpio_from_pipc1 */
/* start of struct st_gpio_from_pipc1 */
    volatile uint16_t PIPC6;                                  /*  PIPC6           */
    volatile uint8_t   dummy470[2];                            /*                  */
/* end of struct st_gpio_from_pipc1 */
/* start of struct st_gpio_from_pipc1 */
    volatile uint16_t PIPC7;                                  /*  PIPC7           */
    volatile uint8_t   dummy471[2];                            /*                  */
/* end of struct st_gpio_from_pipc1 */
/* start of struct st_gpio_from_pipc1 */
    volatile uint16_t PIPC8;                                  /*  PIPC8           */
    volatile uint8_t   dummy472[2];                            /*                  */
/* end of struct st_gpio_from_pipc1 */
/* start of struct st_gpio_from_pipc1 */
    volatile uint16_t PIPC9;                                  /*  PIPC9           */
    volatile uint8_t   dummy473[2];                            /*                  */
/* end of struct st_gpio_from_pipc1 */
/* start of struct st_gpio_from_pipc1 */
    volatile uint16_t PIPC10;                                 /*  PIPC10          */
    volatile uint8_t   dummy474[2];                            /*                  */
/* end of struct st_gpio_from_pipc1 */
/* start of struct st_gpio_from_pipc1 */
    volatile uint16_t PIPC11;                                 /*  PIPC11          */
    volatile uint8_t   dummy4750[2];                           /*                  */
/* end of struct st_gpio_from_pipc1 */
    volatile uint8_t   dummy4751[2288];                        /*                  */
    volatile uint16_t JPPR0;                                  /*  JPPR0           */
    volatile uint8_t   dummy476[30];                           /*                  */
    volatile uint16_t JPMC0;                                  /*  JPMC0           */
    volatile uint8_t   dummy477[78];                           /*                  */
    volatile uint32_t  JPMCSR0;                                /*  JPMCSR0         */
    volatile uint8_t   dummy478[876];                          /*                  */
    volatile uint16_t JPIBC0;                                 /*  JPIBC0          */
};


struct st_gpio_from_p1
{
    volatile uint16_t P1;                                     /*  P1              */
    volatile uint8_t   dummy1[3];                              /*                  */
};


struct st_gpio_from_ppr0
{
    volatile uint16_t PPR0;                                   /*  PPR0            */
    volatile uint8_t   dummy1[2];                              /*                  */
};


struct st_gpio_from_pm1
{
    volatile uint16_t PM1;                                    /*  PM1             */
    volatile uint8_t   dummy1[2];                              /*                  */
};


struct st_gpio_from_pmc0
{
    volatile uint16_t PMC0;                                   /*  PMC0            */
    volatile uint8_t   dummy1[2];                              /*                  */
};


struct st_gpio_from_pfc1
{
    volatile uint16_t PFC1;                                   /*  PFC1            */
    volatile uint8_t   dummy1[2];                              /*                  */
};


struct st_gpio_from_pfce1
{
    volatile uint16_t PFCE1;                                  /*  PFCE1           */
    volatile uint8_t   dummy1[2];                              /*                  */
};


struct st_gpio_from_pnot1
{
    volatile uint16_t PNOT1;                                  /*  PNOT1           */
    volatile uint8_t   dummy1[2];                              /*                  */
};


struct st_gpio_from_pfcae1
{
    volatile uint16_t PFCAE1;                                 /*  PFCAE1          */
    volatile uint8_t   dummy1[2];                              /*                  */
};


struct st_gpio_from_pibc1
{
    volatile uint16_t PIBC1;                                  /*  PIBC1           */
    volatile uint8_t   dummy1[2];                              /*                  */
};


struct st_gpio_from_pbdc1
{
    volatile uint16_t PBDC1;                                  /*  PBDC1           */
    volatile uint8_t   dummy1[2];                              /*                  */
};


struct st_gpio_from_pipc1
{
    volatile uint16_t PIPC1;                                  /*  PIPC1           */
    volatile uint8_t   dummy1[2];                              /*                  */
};


#define GPIO    (*(struct st_gpio    *)0xFCFE3004uL) /* GPIO */

/* Start of channnel array defines of GPIO */

/* Channnel array defines of GPIO_FROM_PIPC1_ARRAY */
/*(Sample) value = GPIO_FROM_PIPC1_ARRAY[ channel ]->PIPC1; */
#define GPIO_FROM_PIPC1_ARRAY_COUNT  11
#define GPIO_FROM_PIPC1_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &GPIO_FROM_PIPC1, &GPIO_FROM_PIPC2, &GPIO_FROM_PIPC3, &GPIO_FROM_PIPC4, &GPIO_FROM_PIPC5, &GPIO_FROM_PIPC6, &GPIO_FROM_PIPC7, &GPIO_FROM_PIPC8, \
    &GPIO_FROM_PIPC9, &GPIO_FROM_PIPC10, &GPIO_FROM_PIPC11 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define GPIO_FROM_PIPC1 (*(struct st_gpio_from_pipc1 *)&GPIO.PIPC1) /* GPIO_FROM_PIPC1 */
#define GPIO_FROM_PIPC2 (*(struct st_gpio_from_pipc1 *)&GPIO.PIPC2) /* GPIO_FROM_PIPC2 */
#define GPIO_FROM_PIPC3 (*(struct st_gpio_from_pipc1 *)&GPIO.PIPC3) /* GPIO_FROM_PIPC3 */
#define GPIO_FROM_PIPC4 (*(struct st_gpio_from_pipc1 *)&GPIO.PIPC4) /* GPIO_FROM_PIPC4 */
#define GPIO_FROM_PIPC5 (*(struct st_gpio_from_pipc1 *)&GPIO.PIPC5) /* GPIO_FROM_PIPC5 */
#define GPIO_FROM_PIPC6 (*(struct st_gpio_from_pipc1 *)&GPIO.PIPC6) /* GPIO_FROM_PIPC6 */
#define GPIO_FROM_PIPC7 (*(struct st_gpio_from_pipc1 *)&GPIO.PIPC7) /* GPIO_FROM_PIPC7 */
#define GPIO_FROM_PIPC8 (*(struct st_gpio_from_pipc1 *)&GPIO.PIPC8) /* GPIO_FROM_PIPC8 */
#define GPIO_FROM_PIPC9 (*(struct st_gpio_from_pipc1 *)&GPIO.PIPC9) /* GPIO_FROM_PIPC9 */
#define GPIO_FROM_PIPC10 (*(struct st_gpio_from_pipc1 *)&GPIO.PIPC10) /* GPIO_FROM_PIPC10 */
#define GPIO_FROM_PIPC11 (*(struct st_gpio_from_pipc1 *)&GPIO.PIPC11) /* GPIO_FROM_PIPC11 */


/* Channnel array defines of GPIO_FROM_PBDC1_ARRAY */
/*(Sample) value = GPIO_FROM_PBDC1_ARRAY[ channel ]->PBDC1; */
#define GPIO_FROM_PBDC1_ARRAY_COUNT  11
#define GPIO_FROM_PBDC1_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &GPIO_FROM_PBDC1, &GPIO_FROM_PBDC2, &GPIO_FROM_PBDC3, &GPIO_FROM_PBDC4, &GPIO_FROM_PBDC5, &GPIO_FROM_PBDC6, &GPIO_FROM_PBDC7, &GPIO_FROM_PBDC8, \
    &GPIO_FROM_PBDC9, &GPIO_FROM_PBDC10, &GPIO_FROM_PBDC11 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define GPIO_FROM_PBDC1 (*(struct st_gpio_from_pbdc1 *)&GPIO.PBDC1) /* GPIO_FROM_PBDC1 */
#define GPIO_FROM_PBDC2 (*(struct st_gpio_from_pbdc1 *)&GPIO.PBDC2) /* GPIO_FROM_PBDC2 */
#define GPIO_FROM_PBDC3 (*(struct st_gpio_from_pbdc1 *)&GPIO.PBDC3) /* GPIO_FROM_PBDC3 */
#define GPIO_FROM_PBDC4 (*(struct st_gpio_from_pbdc1 *)&GPIO.PBDC4) /* GPIO_FROM_PBDC4 */
#define GPIO_FROM_PBDC5 (*(struct st_gpio_from_pbdc1 *)&GPIO.PBDC5) /* GPIO_FROM_PBDC5 */
#define GPIO_FROM_PBDC6 (*(struct st_gpio_from_pbdc1 *)&GPIO.PBDC6) /* GPIO_FROM_PBDC6 */
#define GPIO_FROM_PBDC7 (*(struct st_gpio_from_pbdc1 *)&GPIO.PBDC7) /* GPIO_FROM_PBDC7 */
#define GPIO_FROM_PBDC8 (*(struct st_gpio_from_pbdc1 *)&GPIO.PBDC8) /* GPIO_FROM_PBDC8 */
#define GPIO_FROM_PBDC9 (*(struct st_gpio_from_pbdc1 *)&GPIO.PBDC9) /* GPIO_FROM_PBDC9 */
#define GPIO_FROM_PBDC10 (*(struct st_gpio_from_pbdc1 *)&GPIO.PBDC10) /* GPIO_FROM_PBDC10 */
#define GPIO_FROM_PBDC11 (*(struct st_gpio_from_pbdc1 *)&GPIO.PBDC11) /* GPIO_FROM_PBDC11 */


/* Channnel array defines of GPIO_FROM_PIBC1_ARRAY */
/*(Sample) value = GPIO_FROM_PIBC1_ARRAY[ channel ]->PIBC1; */
#define GPIO_FROM_PIBC1_ARRAY_COUNT  11
#define GPIO_FROM_PIBC1_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &GPIO_FROM_PIBC1, &GPIO_FROM_PIBC2, &GPIO_FROM_PIBC3, &GPIO_FROM_PIBC4, &GPIO_FROM_PIBC5, &GPIO_FROM_PIBC6, &GPIO_FROM_PIBC7, &GPIO_FROM_PIBC8, \
    &GPIO_FROM_PIBC9, &GPIO_FROM_PIBC10, &GPIO_FROM_PIBC11 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define GPIO_FROM_PIBC1 (*(struct st_gpio_from_pibc1 *)&GPIO.PIBC1) /* GPIO_FROM_PIBC1 */
#define GPIO_FROM_PIBC2 (*(struct st_gpio_from_pibc1 *)&GPIO.PIBC2) /* GPIO_FROM_PIBC2 */
#define GPIO_FROM_PIBC3 (*(struct st_gpio_from_pibc1 *)&GPIO.PIBC3) /* GPIO_FROM_PIBC3 */
#define GPIO_FROM_PIBC4 (*(struct st_gpio_from_pibc1 *)&GPIO.PIBC4) /* GPIO_FROM_PIBC4 */
#define GPIO_FROM_PIBC5 (*(struct st_gpio_from_pibc1 *)&GPIO.PIBC5) /* GPIO_FROM_PIBC5 */
#define GPIO_FROM_PIBC6 (*(struct st_gpio_from_pibc1 *)&GPIO.PIBC6) /* GPIO_FROM_PIBC6 */
#define GPIO_FROM_PIBC7 (*(struct st_gpio_from_pibc1 *)&GPIO.PIBC7) /* GPIO_FROM_PIBC7 */
#define GPIO_FROM_PIBC8 (*(struct st_gpio_from_pibc1 *)&GPIO.PIBC8) /* GPIO_FROM_PIBC8 */
#define GPIO_FROM_PIBC9 (*(struct st_gpio_from_pibc1 *)&GPIO.PIBC9) /* GPIO_FROM_PIBC9 */
#define GPIO_FROM_PIBC10 (*(struct st_gpio_from_pibc1 *)&GPIO.PIBC10) /* GPIO_FROM_PIBC10 */
#define GPIO_FROM_PIBC11 (*(struct st_gpio_from_pibc1 *)&GPIO.PIBC11) /* GPIO_FROM_PIBC11 */


/* Channnel array defines of GPIO_FROM_PFCAE1_ARRAY */
/*(Sample) value = GPIO_FROM_PFCAE1_ARRAY[ channel ]->PFCAE1; */
#define GPIO_FROM_PFCAE1_ARRAY_COUNT  11
#define GPIO_FROM_PFCAE1_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &GPIO_FROM_PFCAE1, &GPIO_FROM_PFCAE2, &GPIO_FROM_PFCAE3, &GPIO_FROM_PFCAE4, &GPIO_FROM_PFCAE5, &GPIO_FROM_PFCAE6, &GPIO_FROM_PFCAE7, &GPIO_FROM_PFCAE8, \
    &GPIO_FROM_PFCAE9, &GPIO_FROM_PFCAE10, &GPIO_FROM_PFCAE11 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define GPIO_FROM_PFCAE1 (*(struct st_gpio_from_pfcae1 *)&GPIO.PFCAE1) /* GPIO_FROM_PFCAE1 */
#define GPIO_FROM_PFCAE2 (*(struct st_gpio_from_pfcae1 *)&GPIO.PFCAE2) /* GPIO_FROM_PFCAE2 */
#define GPIO_FROM_PFCAE3 (*(struct st_gpio_from_pfcae1 *)&GPIO.PFCAE3) /* GPIO_FROM_PFCAE3 */
#define GPIO_FROM_PFCAE4 (*(struct st_gpio_from_pfcae1 *)&GPIO.PFCAE4) /* GPIO_FROM_PFCAE4 */
#define GPIO_FROM_PFCAE5 (*(struct st_gpio_from_pfcae1 *)&GPIO.PFCAE5) /* GPIO_FROM_PFCAE5 */
#define GPIO_FROM_PFCAE6 (*(struct st_gpio_from_pfcae1 *)&GPIO.PFCAE6) /* GPIO_FROM_PFCAE6 */
#define GPIO_FROM_PFCAE7 (*(struct st_gpio_from_pfcae1 *)&GPIO.PFCAE7) /* GPIO_FROM_PFCAE7 */
#define GPIO_FROM_PFCAE8 (*(struct st_gpio_from_pfcae1 *)&GPIO.PFCAE8) /* GPIO_FROM_PFCAE8 */
#define GPIO_FROM_PFCAE9 (*(struct st_gpio_from_pfcae1 *)&GPIO.PFCAE9) /* GPIO_FROM_PFCAE9 */
#define GPIO_FROM_PFCAE10 (*(struct st_gpio_from_pfcae1 *)&GPIO.PFCAE10) /* GPIO_FROM_PFCAE10 */
#define GPIO_FROM_PFCAE11 (*(struct st_gpio_from_pfcae1 *)&GPIO.PFCAE11) /* GPIO_FROM_PFCAE11 */


/* Channnel array defines of GPIO_FROM_PNOT1_ARRAY */
/*(Sample) value = GPIO_FROM_PNOT1_ARRAY[ channel ]->PNOT1; */
#define GPIO_FROM_PNOT1_ARRAY_COUNT  11
#define GPIO_FROM_PNOT1_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &GPIO_FROM_PNOT1, &GPIO_FROM_PNOT2, &GPIO_FROM_PNOT3, &GPIO_FROM_PNOT4, &GPIO_FROM_PNOT5, &GPIO_FROM_PNOT6, &GPIO_FROM_PNOT7, &GPIO_FROM_PNOT8, \
    &GPIO_FROM_PNOT9, &GPIO_FROM_PNOT10, &GPIO_FROM_PNOT11 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define GPIO_FROM_PNOT1 (*(struct st_gpio_from_pnot1 *)&GPIO.PNOT1) /* GPIO_FROM_PNOT1 */
#define GPIO_FROM_PNOT2 (*(struct st_gpio_from_pnot1 *)&GPIO.PNOT2) /* GPIO_FROM_PNOT2 */
#define GPIO_FROM_PNOT3 (*(struct st_gpio_from_pnot1 *)&GPIO.PNOT3) /* GPIO_FROM_PNOT3 */
#define GPIO_FROM_PNOT4 (*(struct st_gpio_from_pnot1 *)&GPIO.PNOT4) /* GPIO_FROM_PNOT4 */
#define GPIO_FROM_PNOT5 (*(struct st_gpio_from_pnot1 *)&GPIO.PNOT5) /* GPIO_FROM_PNOT5 */
#define GPIO_FROM_PNOT6 (*(struct st_gpio_from_pnot1 *)&GPIO.PNOT6) /* GPIO_FROM_PNOT6 */
#define GPIO_FROM_PNOT7 (*(struct st_gpio_from_pnot1 *)&GPIO.PNOT7) /* GPIO_FROM_PNOT7 */
#define GPIO_FROM_PNOT8 (*(struct st_gpio_from_pnot1 *)&GPIO.PNOT8) /* GPIO_FROM_PNOT8 */
#define GPIO_FROM_PNOT9 (*(struct st_gpio_from_pnot1 *)&GPIO.PNOT9) /* GPIO_FROM_PNOT9 */
#define GPIO_FROM_PNOT10 (*(struct st_gpio_from_pnot1 *)&GPIO.PNOT10) /* GPIO_FROM_PNOT10 */
#define GPIO_FROM_PNOT11 (*(struct st_gpio_from_pnot1 *)&GPIO.PNOT11) /* GPIO_FROM_PNOT11 */


/* Channnel array defines of GPIO_FROM_PFCE1_ARRAY */
/*(Sample) value = GPIO_FROM_PFCE1_ARRAY[ channel ]->PFCE1; */
#define GPIO_FROM_PFCE1_ARRAY_COUNT  11
#define GPIO_FROM_PFCE1_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &GPIO_FROM_PFCE1, &GPIO_FROM_PFCE2, &GPIO_FROM_PFCE3, &GPIO_FROM_PFCE4, &GPIO_FROM_PFCE5, &GPIO_FROM_PFCE6, &GPIO_FROM_PFCE7, &GPIO_FROM_PFCE8, \
    &GPIO_FROM_PFCE9, &GPIO_FROM_PFCE10, &GPIO_FROM_PFCE11 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define GPIO_FROM_PFCE1 (*(struct st_gpio_from_pfce1 *)&GPIO.PFCE1) /* GPIO_FROM_PFCE1 */
#define GPIO_FROM_PFCE2 (*(struct st_gpio_from_pfce1 *)&GPIO.PFCE2) /* GPIO_FROM_PFCE2 */
#define GPIO_FROM_PFCE3 (*(struct st_gpio_from_pfce1 *)&GPIO.PFCE3) /* GPIO_FROM_PFCE3 */
#define GPIO_FROM_PFCE4 (*(struct st_gpio_from_pfce1 *)&GPIO.PFCE4) /* GPIO_FROM_PFCE4 */
#define GPIO_FROM_PFCE5 (*(struct st_gpio_from_pfce1 *)&GPIO.PFCE5) /* GPIO_FROM_PFCE5 */
#define GPIO_FROM_PFCE6 (*(struct st_gpio_from_pfce1 *)&GPIO.PFCE6) /* GPIO_FROM_PFCE6 */
#define GPIO_FROM_PFCE7 (*(struct st_gpio_from_pfce1 *)&GPIO.PFCE7) /* GPIO_FROM_PFCE7 */
#define GPIO_FROM_PFCE8 (*(struct st_gpio_from_pfce1 *)&GPIO.PFCE8) /* GPIO_FROM_PFCE8 */
#define GPIO_FROM_PFCE9 (*(struct st_gpio_from_pfce1 *)&GPIO.PFCE9) /* GPIO_FROM_PFCE9 */
#define GPIO_FROM_PFCE10 (*(struct st_gpio_from_pfce1 *)&GPIO.PFCE10) /* GPIO_FROM_PFCE10 */
#define GPIO_FROM_PFCE11 (*(struct st_gpio_from_pfce1 *)&GPIO.PFCE11) /* GPIO_FROM_PFCE11 */


/* Channnel array defines of GPIO_FROM_PFC1_ARRAY */
/*(Sample) value = GPIO_FROM_PFC1_ARRAY[ channel ]->PFC1; */
#define GPIO_FROM_PFC1_ARRAY_COUNT  11
#define GPIO_FROM_PFC1_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &GPIO_FROM_PFC1, &GPIO_FROM_PFC2, &GPIO_FROM_PFC3, &GPIO_FROM_PFC4, &GPIO_FROM_PFC5, &GPIO_FROM_PFC6, &GPIO_FROM_PFC7, &GPIO_FROM_PFC8, \
    &GPIO_FROM_PFC9, &GPIO_FROM_PFC10, &GPIO_FROM_PFC11 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define GPIO_FROM_PFC1 (*(struct st_gpio_from_pfc1 *)&GPIO.PFC1) /* GPIO_FROM_PFC1 */
#define GPIO_FROM_PFC2 (*(struct st_gpio_from_pfc1 *)&GPIO.PFC2) /* GPIO_FROM_PFC2 */
#define GPIO_FROM_PFC3 (*(struct st_gpio_from_pfc1 *)&GPIO.PFC3) /* GPIO_FROM_PFC3 */
#define GPIO_FROM_PFC4 (*(struct st_gpio_from_pfc1 *)&GPIO.PFC4) /* GPIO_FROM_PFC4 */
#define GPIO_FROM_PFC5 (*(struct st_gpio_from_pfc1 *)&GPIO.PFC5) /* GPIO_FROM_PFC5 */
#define GPIO_FROM_PFC6 (*(struct st_gpio_from_pfc1 *)&GPIO.PFC6) /* GPIO_FROM_PFC6 */
#define GPIO_FROM_PFC7 (*(struct st_gpio_from_pfc1 *)&GPIO.PFC7) /* GPIO_FROM_PFC7 */
#define GPIO_FROM_PFC8 (*(struct st_gpio_from_pfc1 *)&GPIO.PFC8) /* GPIO_FROM_PFC8 */
#define GPIO_FROM_PFC9 (*(struct st_gpio_from_pfc1 *)&GPIO.PFC9) /* GPIO_FROM_PFC9 */
#define GPIO_FROM_PFC10 (*(struct st_gpio_from_pfc1 *)&GPIO.PFC10) /* GPIO_FROM_PFC10 */
#define GPIO_FROM_PFC11 (*(struct st_gpio_from_pfc1 *)&GPIO.PFC11) /* GPIO_FROM_PFC11 */


/* Channnel array defines of GPIO_FROM_PMC0_ARRAY */
/*(Sample) value = GPIO_FROM_PMC0_ARRAY[ channel ]->PMC0; */
#define GPIO_FROM_PMC0_ARRAY_COUNT  12
#define GPIO_FROM_PMC0_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &GPIO_FROM_PMC0, &GPIO_FROM_PMC1, &GPIO_FROM_PMC2, &GPIO_FROM_PMC3, &GPIO_FROM_PMC4, &GPIO_FROM_PMC5, &GPIO_FROM_PMC6, &GPIO_FROM_PMC7, \
    &GPIO_FROM_PMC8, &GPIO_FROM_PMC9, &GPIO_FROM_PMC10, &GPIO_FROM_PMC11 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define GPIO_FROM_PMC0 (*(struct st_gpio_from_pmc0 *)&GPIO.PMC0) /* GPIO_FROM_PMC0 */
#define GPIO_FROM_PMC1 (*(struct st_gpio_from_pmc0 *)&GPIO.PMC1) /* GPIO_FROM_PMC1 */
#define GPIO_FROM_PMC2 (*(struct st_gpio_from_pmc0 *)&GPIO.PMC2) /* GPIO_FROM_PMC2 */
#define GPIO_FROM_PMC3 (*(struct st_gpio_from_pmc0 *)&GPIO.PMC3) /* GPIO_FROM_PMC3 */
#define GPIO_FROM_PMC4 (*(struct st_gpio_from_pmc0 *)&GPIO.PMC4) /* GPIO_FROM_PMC4 */
#define GPIO_FROM_PMC5 (*(struct st_gpio_from_pmc0 *)&GPIO.PMC5) /* GPIO_FROM_PMC5 */
#define GPIO_FROM_PMC6 (*(struct st_gpio_from_pmc0 *)&GPIO.PMC6) /* GPIO_FROM_PMC6 */
#define GPIO_FROM_PMC7 (*(struct st_gpio_from_pmc0 *)&GPIO.PMC7) /* GPIO_FROM_PMC7 */
#define GPIO_FROM_PMC8 (*(struct st_gpio_from_pmc0 *)&GPIO.PMC8) /* GPIO_FROM_PMC8 */
#define GPIO_FROM_PMC9 (*(struct st_gpio_from_pmc0 *)&GPIO.PMC9) /* GPIO_FROM_PMC9 */
#define GPIO_FROM_PMC10 (*(struct st_gpio_from_pmc0 *)&GPIO.PMC10) /* GPIO_FROM_PMC10 */
#define GPIO_FROM_PMC11 (*(struct st_gpio_from_pmc0 *)&GPIO.PMC11) /* GPIO_FROM_PMC11 */


/* Channnel array defines of GPIO_FROM_PM1_ARRAY */
/*(Sample) value = GPIO_FROM_PM1_ARRAY[ channel ]->PM1; */
#define GPIO_FROM_PM1_ARRAY_COUNT  11
#define GPIO_FROM_PM1_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &GPIO_FROM_PM1, &GPIO_FROM_PM2, &GPIO_FROM_PM3, &GPIO_FROM_PM4, &GPIO_FROM_PM5, &GPIO_FROM_PM6, &GPIO_FROM_PM7, &GPIO_FROM_PM8, \
    &GPIO_FROM_PM9, &GPIO_FROM_PM10, &GPIO_FROM_PM11 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define GPIO_FROM_PM1 (*(struct st_gpio_from_pm1 *)&GPIO.PM1)    /* GPIO_FROM_PM1 */
#define GPIO_FROM_PM2 (*(struct st_gpio_from_pm1 *)&GPIO.PM2)    /* GPIO_FROM_PM2 */
#define GPIO_FROM_PM3 (*(struct st_gpio_from_pm1 *)&GPIO.PM3)    /* GPIO_FROM_PM3 */
#define GPIO_FROM_PM4 (*(struct st_gpio_from_pm1 *)&GPIO.PM4)    /* GPIO_FROM_PM4 */
#define GPIO_FROM_PM5 (*(struct st_gpio_from_pm1 *)&GPIO.PM5)    /* GPIO_FROM_PM5 */
#define GPIO_FROM_PM6 (*(struct st_gpio_from_pm1 *)&GPIO.PM6)    /* GPIO_FROM_PM6 */
#define GPIO_FROM_PM7 (*(struct st_gpio_from_pm1 *)&GPIO.PM7)    /* GPIO_FROM_PM7 */
#define GPIO_FROM_PM8 (*(struct st_gpio_from_pm1 *)&GPIO.PM8)    /* GPIO_FROM_PM8 */
#define GPIO_FROM_PM9 (*(struct st_gpio_from_pm1 *)&GPIO.PM9)    /* GPIO_FROM_PM9 */
#define GPIO_FROM_PM10 (*(struct st_gpio_from_pm1 *)&GPIO.PM10)  /* GPIO_FROM_PM10 */
#define GPIO_FROM_PM11 (*(struct st_gpio_from_pm1 *)&GPIO.PM11)  /* GPIO_FROM_PM11 */


/* Channnel array defines of GPIO_FROM_PPR0_ARRAY */
/*(Sample) value = GPIO_FROM_PPR0_ARRAY[ channel ]->PPR0; */
#define GPIO_FROM_PPR0_ARRAY_COUNT  12
#define GPIO_FROM_PPR0_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &GPIO_FROM_PPR0, &GPIO_FROM_PPR1, &GPIO_FROM_PPR2, &GPIO_FROM_PPR3, &GPIO_FROM_PPR4, &GPIO_FROM_PPR5, &GPIO_FROM_PPR6, &GPIO_FROM_PPR7, \
    &GPIO_FROM_PPR8, &GPIO_FROM_PPR9, &GPIO_FROM_PPR10, &GPIO_FROM_PPR11 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define GPIO_FROM_PPR0 (*(struct st_gpio_from_ppr0 *)&GPIO.PPR0) /* GPIO_FROM_PPR0 */
#define GPIO_FROM_PPR1 (*(struct st_gpio_from_ppr0 *)&GPIO.PPR1) /* GPIO_FROM_PPR1 */
#define GPIO_FROM_PPR2 (*(struct st_gpio_from_ppr0 *)&GPIO.PPR2) /* GPIO_FROM_PPR2 */
#define GPIO_FROM_PPR3 (*(struct st_gpio_from_ppr0 *)&GPIO.PPR3) /* GPIO_FROM_PPR3 */
#define GPIO_FROM_PPR4 (*(struct st_gpio_from_ppr0 *)&GPIO.PPR4) /* GPIO_FROM_PPR4 */
#define GPIO_FROM_PPR5 (*(struct st_gpio_from_ppr0 *)&GPIO.PPR5) /* GPIO_FROM_PPR5 */
#define GPIO_FROM_PPR6 (*(struct st_gpio_from_ppr0 *)&GPIO.PPR6) /* GPIO_FROM_PPR6 */
#define GPIO_FROM_PPR7 (*(struct st_gpio_from_ppr0 *)&GPIO.PPR7) /* GPIO_FROM_PPR7 */
#define GPIO_FROM_PPR8 (*(struct st_gpio_from_ppr0 *)&GPIO.PPR8) /* GPIO_FROM_PPR8 */
#define GPIO_FROM_PPR9 (*(struct st_gpio_from_ppr0 *)&GPIO.PPR9) /* GPIO_FROM_PPR9 */
#define GPIO_FROM_PPR10 (*(struct st_gpio_from_ppr0 *)&GPIO.PPR10) /* GPIO_FROM_PPR10 */
#define GPIO_FROM_PPR11 (*(struct st_gpio_from_ppr0 *)&GPIO.PPR11) /* GPIO_FROM_PPR11 */


/* Channnel array defines of GPIO_FROM_P1_ARRAY */
/*(Sample) value = GPIO_FROM_P1_ARRAY[ channel ]->P1; */
#define GPIO_FROM_P1_ARRAY_COUNT  11
#define GPIO_FROM_P1_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &GPIO_FROM_P1, &GPIO_FROM_P2, &GPIO_FROM_P3, &GPIO_FROM_P4, &GPIO_FROM_P5, &GPIO_FROM_P6, &GPIO_FROM_P7, &GPIO_FROM_P8, \
    &GPIO_FROM_P9, &GPIO_FROM_P10, &GPIO_FROM_P11 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define GPIO_FROM_P1 (*(struct st_gpio_from_p1 *)&GPIO.P1)       /* GPIO_FROM_P1 */
#define GPIO_FROM_P2 (*(struct st_gpio_from_p1 *)&GPIO.P2)       /* GPIO_FROM_P2 */
#define GPIO_FROM_P3 (*(struct st_gpio_from_p1 *)&GPIO.P3)       /* GPIO_FROM_P3 */
#define GPIO_FROM_P4 (*(struct st_gpio_from_p1 *)&GPIO.P4)       /* GPIO_FROM_P4 */
#define GPIO_FROM_P5 (*(struct st_gpio_from_p1 *)&GPIO.P5)       /* GPIO_FROM_P5 */
#define GPIO_FROM_P6 (*(struct st_gpio_from_p1 *)&GPIO.P6)       /* GPIO_FROM_P6 */
#define GPIO_FROM_P7 (*(struct st_gpio_from_p1 *)&GPIO.P7)       /* GPIO_FROM_P7 */
#define GPIO_FROM_P8 (*(struct st_gpio_from_p1 *)&GPIO.P8)       /* GPIO_FROM_P8 */
#define GPIO_FROM_P9 (*(struct st_gpio_from_p1 *)&GPIO.P9)       /* GPIO_FROM_P9 */
#define GPIO_FROM_P10 (*(struct st_gpio_from_p1 *)&GPIO.P10)     /* GPIO_FROM_P10 */
#define GPIO_FROM_P11 (*(struct st_gpio_from_p1 *)&GPIO.P11)     /* GPIO_FROM_P11 */

/* End of channnel array defines of GPIO */


#define GPIOP1 GPIO.P1
#define GPIOP2 GPIO.P2
#define GPIOP3 GPIO.P3
#define GPIOP4 GPIO.P4
#define GPIOP5 GPIO.P5
#define GPIOP6 GPIO.P6
#define GPIOP7 GPIO.P7
#define GPIOP8 GPIO.P8
#define GPIOP9 GPIO.P9
#define GPIOP10 GPIO.P10
#define GPIOP11 GPIO.P11
#define GPIOPSR1 GPIO.PSR1
#define GPIOPSR2 GPIO.PSR2
#define GPIOPSR3 GPIO.PSR3
#define GPIOPSR4 GPIO.PSR4
#define GPIOPSR5 GPIO.PSR5
#define GPIOPSR6 GPIO.PSR6
#define GPIOPSR7 GPIO.PSR7
#define GPIOPSR8 GPIO.PSR8
#define GPIOPSR9 GPIO.PSR9
#define GPIOPSR10 GPIO.PSR10
#define GPIOPSR11 GPIO.PSR11
#define GPIOPPR0 GPIO.PPR0
#define GPIOPPR1 GPIO.PPR1
#define GPIOPPR2 GPIO.PPR2
#define GPIOPPR3 GPIO.PPR3
#define GPIOPPR4 GPIO.PPR4
#define GPIOPPR5 GPIO.PPR5
#define GPIOPPR6 GPIO.PPR6
#define GPIOPPR7 GPIO.PPR7
#define GPIOPPR8 GPIO.PPR8
#define GPIOPPR9 GPIO.PPR9
#define GPIOPPR10 GPIO.PPR10
#define GPIOPPR11 GPIO.PPR11
#define GPIOPM1 GPIO.PM1
#define GPIOPM2 GPIO.PM2
#define GPIOPM3 GPIO.PM3
#define GPIOPM4 GPIO.PM4
#define GPIOPM5 GPIO.PM5
#define GPIOPM6 GPIO.PM6
#define GPIOPM7 GPIO.PM7
#define GPIOPM8 GPIO.PM8
#define GPIOPM9 GPIO.PM9
#define GPIOPM10 GPIO.PM10
#define GPIOPM11 GPIO.PM11
#define GPIOPMC0 GPIO.PMC0
#define GPIOPMC1 GPIO.PMC1
#define GPIOPMC2 GPIO.PMC2
#define GPIOPMC3 GPIO.PMC3
#define GPIOPMC4 GPIO.PMC4
#define GPIOPMC5 GPIO.PMC5
#define GPIOPMC6 GPIO.PMC6
#define GPIOPMC7 GPIO.PMC7
#define GPIOPMC8 GPIO.PMC8
#define GPIOPMC9 GPIO.PMC9
#define GPIOPMC10 GPIO.PMC10
#define GPIOPMC11 GPIO.PMC11
#define GPIOPFC1 GPIO.PFC1
#define GPIOPFC2 GPIO.PFC2
#define GPIOPFC3 GPIO.PFC3
#define GPIOPFC4 GPIO.PFC4
#define GPIOPFC5 GPIO.PFC5
#define GPIOPFC6 GPIO.PFC6
#define GPIOPFC7 GPIO.PFC7
#define GPIOPFC8 GPIO.PFC8
#define GPIOPFC9 GPIO.PFC9
#define GPIOPFC10 GPIO.PFC10
#define GPIOPFC11 GPIO.PFC11
#define GPIOPFCE1 GPIO.PFCE1
#define GPIOPFCE2 GPIO.PFCE2
#define GPIOPFCE3 GPIO.PFCE3
#define GPIOPFCE4 GPIO.PFCE4
#define GPIOPFCE5 GPIO.PFCE5
#define GPIOPFCE6 GPIO.PFCE6
#define GPIOPFCE7 GPIO.PFCE7
#define GPIOPFCE8 GPIO.PFCE8
#define GPIOPFCE9 GPIO.PFCE9
#define GPIOPFCE10 GPIO.PFCE10
#define GPIOPFCE11 GPIO.PFCE11
#define GPIOPNOT1 GPIO.PNOT1
#define GPIOPNOT2 GPIO.PNOT2
#define GPIOPNOT3 GPIO.PNOT3
#define GPIOPNOT4 GPIO.PNOT4
#define GPIOPNOT5 GPIO.PNOT5
#define GPIOPNOT6 GPIO.PNOT6
#define GPIOPNOT7 GPIO.PNOT7
#define GPIOPNOT8 GPIO.PNOT8
#define GPIOPNOT9 GPIO.PNOT9
#define GPIOPNOT10 GPIO.PNOT10
#define GPIOPNOT11 GPIO.PNOT11
#define GPIOPMSR1 GPIO.PMSR1
#define GPIOPMSR2 GPIO.PMSR2
#define GPIOPMSR3 GPIO.PMSR3
#define GPIOPMSR4 GPIO.PMSR4
#define GPIOPMSR5 GPIO.PMSR5
#define GPIOPMSR6 GPIO.PMSR6
#define GPIOPMSR7 GPIO.PMSR7
#define GPIOPMSR8 GPIO.PMSR8
#define GPIOPMSR9 GPIO.PMSR9
#define GPIOPMSR10 GPIO.PMSR10
#define GPIOPMSR11 GPIO.PMSR11
#define GPIOPMCSR0 GPIO.PMCSR0
#define GPIOPMCSR1 GPIO.PMCSR1
#define GPIOPMCSR2 GPIO.PMCSR2
#define GPIOPMCSR3 GPIO.PMCSR3
#define GPIOPMCSR4 GPIO.PMCSR4
#define GPIOPMCSR5 GPIO.PMCSR5
#define GPIOPMCSR6 GPIO.PMCSR6
#define GPIOPMCSR7 GPIO.PMCSR7
#define GPIOPMCSR8 GPIO.PMCSR8
#define GPIOPMCSR9 GPIO.PMCSR9
#define GPIOPMCSR10 GPIO.PMCSR10
#define GPIOPMCSR11 GPIO.PMCSR11
#define GPIOPFCAE1 GPIO.PFCAE1
#define GPIOPFCAE2 GPIO.PFCAE2
#define GPIOPFCAE3 GPIO.PFCAE3
#define GPIOPFCAE4 GPIO.PFCAE4
#define GPIOPFCAE5 GPIO.PFCAE5
#define GPIOPFCAE6 GPIO.PFCAE6
#define GPIOPFCAE7 GPIO.PFCAE7
#define GPIOPFCAE8 GPIO.PFCAE8
#define GPIOPFCAE9 GPIO.PFCAE9
#define GPIOPFCAE10 GPIO.PFCAE10
#define GPIOPFCAE11 GPIO.PFCAE11
#define GPIOSNCR GPIO.SNCR
#define GPIOPIBC0 GPIO.PIBC0
#define GPIOPIBC1 GPIO.PIBC1
#define GPIOPIBC2 GPIO.PIBC2
#define GPIOPIBC3 GPIO.PIBC3
#define GPIOPIBC4 GPIO.PIBC4
#define GPIOPIBC5 GPIO.PIBC5
#define GPIOPIBC6 GPIO.PIBC6
#define GPIOPIBC7 GPIO.PIBC7
#define GPIOPIBC8 GPIO.PIBC8
#define GPIOPIBC9 GPIO.PIBC9
#define GPIOPIBC10 GPIO.PIBC10
#define GPIOPIBC11 GPIO.PIBC11
#define GPIOPBDC1 GPIO.PBDC1
#define GPIOPBDC2 GPIO.PBDC2
#define GPIOPBDC3 GPIO.PBDC3
#define GPIOPBDC4 GPIO.PBDC4
#define GPIOPBDC5 GPIO.PBDC5
#define GPIOPBDC6 GPIO.PBDC6
#define GPIOPBDC7 GPIO.PBDC7
#define GPIOPBDC8 GPIO.PBDC8
#define GPIOPBDC9 GPIO.PBDC9
#define GPIOPBDC10 GPIO.PBDC10
#define GPIOPBDC11 GPIO.PBDC11
#define GPIOPIPC1 GPIO.PIPC1
#define GPIOPIPC2 GPIO.PIPC2
#define GPIOPIPC3 GPIO.PIPC3
#define GPIOPIPC4 GPIO.PIPC4
#define GPIOPIPC5 GPIO.PIPC5
#define GPIOPIPC6 GPIO.PIPC6
#define GPIOPIPC7 GPIO.PIPC7
#define GPIOPIPC8 GPIO.PIPC8
#define GPIOPIPC9 GPIO.PIPC9
#define GPIOPIPC10 GPIO.PIPC10
#define GPIOPIPC11 GPIO.PIPC11
#define GPIOJPPR0 GPIO.JPPR0
#define GPIOJPMC0 GPIO.JPMC0
#define GPIOJPMCSR0 GPIO.JPMCSR0
#define GPIOJPIBC0 GPIO.JPIBC0
/* <-SEC M1.10.1 */
/* <-QAC 0639 */
#endif
