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
* http://www.renesas.com/disclaimer
* Copyright (C) 2012 - 2014 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/**************************************************************************//**
 * @file     MBRZA1H.h
 * @brief    CMSIS Cortex-A9 Core Peripheral Access Layer Header File for 
 *           Renesas MBRZA1H Device Series
 * @version
 * @date     19 Sept 2013
 *
 * @note
 *
 ******************************************************************************/

#ifndef __MBRZA1H_H__
#define __MBRZA1H_H__

#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum IRQn
{
/******  SGI Interrupts Numbers                 ****************************************/
  SGI0_IRQn           =  0,
  SGI1_IRQn           =  1,
  SGI2_IRQn           =  2,
  SGI3_IRQn           =  3,
  SGI4_IRQn           =  4,
  SGI5_IRQn           =  5,
  SGI6_IRQn           =  6,
  SGI7_IRQn           =  7,
  SGI8_IRQn           =  8,
  SGI9_IRQn           =  9,
  SGI10_IRQn          = 10,
  SGI11_IRQn          = 11,
  SGI12_IRQn          = 12,
  SGI13_IRQn          = 13,
  SGI14_IRQn          = 14,
  SGI15_IRQn          = 15,

/******  Cortex-A9 Processor Exceptions Numbers ****************************************/
  /* 16 - 578 */
  PMUIRQ0_IRQn         = 16,
  COMMRX0_IRQn         = 17,
  COMMTX0_IRQn         = 18,
  CTIIRQ0_IRQn         = 19,

  IRQ0_IRQn            = 32,
  IRQ1_IRQn            = 33,
  IRQ2_IRQn            = 34,
  IRQ3_IRQn            = 35,
  IRQ4_IRQn            = 36,
  IRQ5_IRQn            = 37,
  IRQ6_IRQn            = 38,
  IRQ7_IRQn            = 39,

  PL310ERR_IRQn        = 40,

  DMAINT0_IRQn         = 41,        /*!< DMAC Interrupt         */
  DMAINT1_IRQn         = 42,        /*!< DMAC Interrupt         */
  DMAINT2_IRQn         = 43,        /*!< DMAC Interrupt         */
  DMAINT3_IRQn         = 44,        /*!< DMAC Interrupt         */
  DMAINT4_IRQn         = 45,        /*!< DMAC Interrupt         */
  DMAINT5_IRQn         = 46,        /*!< DMAC Interrupt         */
  DMAINT6_IRQn         = 47,        /*!< DMAC Interrupt         */
  DMAINT7_IRQn         = 48,        /*!< DMAC Interrupt         */
  DMAINT8_IRQn         = 49,        /*!< DMAC Interrupt         */
  DMAINT9_IRQn         = 50,        /*!< DMAC Interrupt         */
  DMAINT10_IRQn        = 51,        /*!< DMAC Interrupt         */
  DMAINT11_IRQn        = 52,        /*!< DMAC Interrupt         */
  DMAINT12_IRQn        = 53,        /*!< DMAC Interrupt         */
  DMAINT13_IRQn        = 54,        /*!< DMAC Interrupt         */
  DMAINT14_IRQn        = 55,        /*!< DMAC Interrupt         */
  DMAINT15_IRQn        = 56,        /*!< DMAC Interrupt         */
  DMAERR_IRQn          = 57,        /*!< DMAC Interrupt         */

  /* 58-72 Reserved */

  USBI0_IRQn           = 73,
  USBI1_IRQn           = 74,

  S0_VI_VSYNC0_IRQn    = 75,
  S0_LO_VSYNC0_IRQn    = 76,
  S0_VSYNCERR0_IRQn    = 77,
  GR3_VLINE0_IRQn      = 78,
  S0_VFIELD0_IRQn      = 79,
  IV1_VBUFERR0_IRQn    = 80,
  IV3_VBUFERR0_IRQn    = 81,
  IV5_VBUFERR0_IRQn    = 82,
  IV6_VBUFERR0_IRQn    = 83,
  S0_WLINE0_IRQn       = 84,
  S1_VI_VSYNC0_IRQn    = 85,
  S1_LO_VSYNC0_IRQn    = 86,
  S1_VSYNCERR0_IRQn    = 87,
  S1_VFIELD0_IRQn      = 88,
  IV2_VBUFERR0_IRQn    = 89,
  IV4_VBUFERR0_IRQn    = 90,
  S1_WLINE0_IRQn       = 91,
  OIR_VI_VSYNC0_IRQn   = 92,
  OIR_LO_VSYNC0_IRQn   = 93,
  OIR_VSYNCERR0_IRQn   = 94,
  OIR_VFIELD0_IRQn     = 95,
  IV7_VBUFERR0_IRQn    = 96,
  IV8_VBUFERR0_IRQn    = 97,
  /* 98 Reserved */
  S0_VI_VSYNC1_IRQn    = 99,
  S0_LO_VSYNC1_IRQn    = 100,
  S0_VSYNCERR1_IRQn    = 101,
  GR3_VLINE1_IRQn      = 102,
  S0_VFIELD1_IRQn      = 103,
  IV1_VBUFERR1_IRQn    = 104,
  IV3_VBUFERR1_IRQn    = 105,
  IV5_VBUFERR1_IRQn    = 106,
  IV6_VBUFERR1_IRQn    = 107,
  S0_WLINE1_IRQn       = 108,
  S1_VI_VSYNC1_IRQn    = 109,
  S1_LO_VSYNC1_IRQn    = 110,
  S1_VSYNCERR1_IRQn    = 111,
  S1_VFIELD1_IRQn      = 112,
  IV2_VBUFERR1_IRQn    = 113,
  IV4_VBUFERR1_IRQn    = 114,
  S1_WLINE1_IRQn       = 115,
  OIR_VI_VSYNC1_IRQn   = 116,
  OIR_LO_VSYNC1_IRQn   = 117,
  OIR_VSYNCERR1_IRQn   = 118,
  OIR_VFIELD1_IRQn     = 119,
  IV7_VBUFERR1_IRQn    = 120,
  IV8_VBUFERR1_IRQn    = 121,
  /* Reserved = 122 */

  IMRDI_IRQn           = 123,
  IMR2I0_IRQn          = 124,
  IMR2I1_IRQn          = 125,

  JEDI_IRQn            = 126,
  JDTI_IRQn            = 127,

  CMP0_IRQn            = 128,
  CMP1_IRQn            = 129,

  INT0_IRQn            = 130,
  INT1_IRQn            = 131,
  INT2_IRQn            = 132,
  INT3_IRQn            = 133,

  OSTMI0TINT_IRQn      = 134,       /*!< OSTM Interrupt         */
  OSTMI1TINT_IRQn      = 135,       /*!< OSTM Interrupt         */

  CMI_IRQn             = 136,
  WTOUT_IRQn           = 137,

  ITI_IRQn             = 138,

  TGI0A_IRQn           = 139,
  TGI0B_IRQn           = 140,
  TGI0C_IRQn           = 141,
  TGI0D_IRQn           = 142,
  TGI0V_IRQn           = 143,
  TGI0E_IRQn           = 144,
  TGI0F_IRQn           = 145,
  TGI1A_IRQn           = 146,
  TGI1B_IRQn           = 147,
  TGI1V_IRQn           = 148,
  TGI1U_IRQn           = 149,
  TGI2A_IRQn           = 150,
  TGI2B_IRQn           = 151,
  TGI2V_IRQn           = 152,
  TGI2U_IRQn           = 153,
  TGI3A_IRQn           = 154,
  TGI3B_IRQn           = 155,
  TGI3C_IRQn           = 156,
  TGI3D_IRQn           = 157,
  TGI3V_IRQn           = 158,
  TGI4A_IRQn           = 159,
  TGI4B_IRQn           = 160,
  TGI4C_IRQn           = 161,
  TGI4D_IRQn           = 162,
  TGI4V_IRQn           = 163,

  CMI1_IRQn            = 164,
  CMI2_IRQn            = 165,

  SGDEI0_IRQn          = 166,
  SGDEI1_IRQn          = 167,
  SGDEI2_IRQn          = 168,
  SGDEI3_IRQn          = 169,

  ADI_IRQn             = 170,
  LMTI_IRQn            = 171,

  SSII0_IRQn           = 172,       /*!< SSIF Interrupt         */
  SSIRXI0_IRQn         = 173,       /*!< SSIF Interrupt         */
  SSITXI0_IRQn         = 174,       /*!< SSIF Interrupt         */
  SSII1_IRQn           = 175,       /*!< SSIF Interrupt         */
  SSIRXI1_IRQn         = 176,       /*!< SSIF Interrupt         */
  SSITXI1_IRQn         = 177,       /*!< SSIF Interrupt         */
  SSII2_IRQn           = 178,       /*!< SSIF Interrupt         */
  SSIRTI2_IRQn         = 179,       /*!< SSIF Interrupt         */
  SSII3_IRQn           = 180,       /*!< SSIF Interrupt         */
  SSIRXI3_IRQn         = 181,       /*!< SSIF Interrupt         */
  SSITXI3_IRQn         = 182,       /*!< SSIF Interrupt         */
  SSII4_IRQn           = 183,       /*!< SSIF Interrupt         */
  SSIRTI4_IRQn         = 184,       /*!< SSIF Interrupt         */
  SSII5_IRQn           = 185,       /*!< SSIF Interrupt         */
  SSIRXI5_IRQn         = 186,       /*!< SSIF Interrupt         */
  SSITXI5_IRQn         = 187,       /*!< SSIF Interrupt         */

  SPDIFI_IRQn          = 188,

  INTIICTEI0_IRQn      = 189,       /*!< RIIC Interrupt         */
  INTIICRI0_IRQn       = 190,       /*!< RIIC Interrupt         */
  INTIICTI0_IRQn       = 191,       /*!< RIIC Interrupt         */
  INTIICSPI0_IRQn      = 192,       /*!< RIIC Interrupt         */
  INTIICSTI0_IRQn      = 193,       /*!< RIIC Interrupt         */
  INTIICNAKI0_IRQn     = 194,       /*!< RIIC Interrupt         */
  INTIICALI0_IRQn      = 195,       /*!< RIIC Interrupt         */
  INTIICTMOI0_IRQn     = 196,       /*!< RIIC Interrupt         */
  INTIICTEI1_IRQn      = 197,       /*!< RIIC Interrupt         */
  INTIICRI1_IRQn       = 198,       /*!< RIIC Interrupt         */
  INTIICTI1_IRQn       = 199,       /*!< RIIC Interrupt         */
  INTIICSPI1_IRQn      = 200,       /*!< RIIC Interrupt         */
  INTIICSTI1_IRQn      = 201,       /*!< RIIC Interrupt         */
  INTIICNAKI1_IRQn     = 202,       /*!< RIIC Interrupt         */
  INTIICALI1_IRQn      = 203,       /*!< RIIC Interrupt         */
  INTIICTMOI1_IRQn     = 204,       /*!< RIIC Interrupt         */
  INTIICTEI2_IRQn      = 205,       /*!< RIIC Interrupt         */
  INTIICRI2_IRQn       = 206,       /*!< RIIC Interrupt         */
  INTIICTI2_IRQn       = 207,       /*!< RIIC Interrupt         */
  INTIICSPI2_IRQn      = 208,       /*!< RIIC Interrupt         */
  INTIICSTI2_IRQn      = 209,       /*!< RIIC Interrupt         */
  INTIICNAKI2_IRQn     = 210,       /*!< RIIC Interrupt         */
  INTIICALI2_IRQn      = 211,       /*!< RIIC Interrupt         */
  INTIICTMOI2_IRQn     = 212,       /*!< RIIC Interrupt         */
  INTIICTEI3_IRQn      = 213,       /*!< RIIC Interrupt         */
  INTIICRI3_IRQn       = 214,       /*!< RIIC Interrupt         */
  INTIICTI3_IRQn       = 215,       /*!< RIIC Interrupt         */
  INTIICSPI3_IRQn      = 216,       /*!< RIIC Interrupt         */
  INTIICSTI3_IRQn      = 217,       /*!< RIIC Interrupt         */
  INTIICNAKI3_IRQn     = 218,       /*!< RIIC Interrupt         */
  INTIICALI3_IRQn      = 219,       /*!< RIIC Interrupt         */
  INTIICTMOI3_IRQn     = 220,       /*!< RIIC Interrupt         */

  SCIFBRI0_IRQn        = 221,       /*!< SCIF Interrupt         */
  SCIFERI0_IRQn        = 222,       /*!< SCIF Interrupt         */
  SCIFRXI0_IRQn        = 223,       /*!< SCIF Interrupt         */
  SCIFTXI0_IRQn        = 224,       /*!< SCIF Interrupt         */
  SCIFBRI1_IRQn        = 225,       /*!< SCIF Interrupt         */
  SCIFERI1_IRQn        = 226,       /*!< SCIF Interrupt         */
  SCIFRXI1_IRQn        = 227,       /*!< SCIF Interrupt         */
  SCIFTXI1_IRQn        = 228,       /*!< SCIF Interrupt         */
  SCIFBRI2_IRQn        = 229,       /*!< SCIF Interrupt         */
  SCIFERI2_IRQn        = 230,       /*!< SCIF Interrupt         */
  SCIFRXI2_IRQn        = 231,       /*!< SCIF Interrupt         */
  SCIFTXI2_IRQn        = 232,       /*!< SCIF Interrupt         */
  SCIFBRI3_IRQn        = 233,       /*!< SCIF Interrupt         */
  SCIFERI3_IRQn        = 234,       /*!< SCIF Interrupt         */
  SCIFRXI3_IRQn        = 235,       /*!< SCIF Interrupt         */
  SCIFTXI3_IRQn        = 236,       /*!< SCIF Interrupt         */
  SCIFBRI4_IRQn        = 237,       /*!< SCIF Interrupt         */
  SCIFERI4_IRQn        = 238,       /*!< SCIF Interrupt         */
  SCIFRXI4_IRQn        = 239,       /*!< SCIF Interrupt         */
  SCIFTXI4_IRQn        = 240,       /*!< SCIF Interrupt         */
  SCIFBRI5_IRQn        = 241,       /*!< SCIF Interrupt         */
  SCIFERI5_IRQn        = 242,       /*!< SCIF Interrupt         */
  SCIFRXI5_IRQn        = 243,       /*!< SCIF Interrupt         */
  SCIFTXI5_IRQn        = 244,       /*!< SCIF Interrupt         */
  SCIFBRI6_IRQn        = 245,       /*!< SCIF Interrupt         */
  SCIFERI6_IRQn        = 246,       /*!< SCIF Interrupt         */
  SCIFRXI6_IRQn        = 247,       /*!< SCIF Interrupt         */
  SCIFTXI6_IRQn        = 248,       /*!< SCIF Interrupt         */
  SCIFBRI7_IRQn        = 249,       /*!< SCIF Interrupt         */
  SCIFERI7_IRQn        = 250,       /*!< SCIF Interrupt         */
  SCIFRXI7_IRQn        = 251,       /*!< SCIF Interrupt         */
  SCIFTXI7_IRQn        = 252,       /*!< SCIF Interrupt         */

  INTRCANGERR_IRQn     = 253,
  INTRCANGRECC_IRQn    = 254,
  INTRCAN0REC_IRQn     = 255,
  INTRCAN0ERR_IRQn     = 256,
  INTRCAN0TRX_IRQn     = 257,
  INTRCAN1REC_IRQn     = 258,
  INTRCAN1ERR_IRQn     = 259,
  INTRCAN1TRX_IRQn     = 260,
  INTRCAN2REC_IRQn     = 261,
  INTRCAN2ERR_IRQn     = 262,
  INTRCAN2TRX_IRQn     = 263,
  INTRCAN3REC_IRQn     = 264,
  INTRCAN3ERR_IRQn     = 265,
  INTRCAN3TRX_IRQn     = 266,
  INTRCAN4REC_IRQn     = 267,
  INTRCAN4ERR_IRQn     = 268,
  INTRCAN4TRX_IRQn     = 269,

  RSPISPEI0_IRQn       = 270,       /*!< RSPI Interrupt         */
  RSPISPRI0_IRQn       = 271,       /*!< RSPI Interrupt         */
  RSPISPTI0_IRQn       = 272,       /*!< RSPI Interrupt         */
  RSPISPEI1_IRQn       = 273,       /*!< RSPI Interrupt         */
  RSPISPRI1_IRQn       = 274,       /*!< RSPI Interrupt         */
  RSPISPTI1_IRQn       = 275,       /*!< RSPI Interrupt         */
  RSPISPEI2_IRQn       = 276,       /*!< RSPI Interrupt         */
  RSPISPRI2_IRQn       = 277,       /*!< RSPI Interrupt         */
  RSPISPTI2_IRQn       = 278,       /*!< RSPI Interrupt         */
  RSPISPEI3_IRQn       = 279,       /*!< RSPI Interrupt         */
  RSPISPRI3_IRQn       = 280,       /*!< RSPI Interrupt         */
  RSPISPTI3_IRQn       = 281,       /*!< RSPI Interrupt         */
  RSPISPEI4_IRQn       = 282,       /*!< RSPI Interrupt         */
  RSPISPRI4_IRQn       = 283,       /*!< RSPI Interrupt         */
  RSPISPTI4_IRQn       = 284,       /*!< RSPI Interrupt         */

  IEBBTD_IRQn          = 285,
  IEBBTERR_IRQn        = 286,
  IEBBTSTA_IRQn        = 287,
  IEBBTV_IRQn          = 288,

  ISY_IRQn             = 289,
  IERR_IRQn            = 290,
  ITARG_IRQn           = 291,
  ISEC_IRQn            = 292,
  IBUF_IRQn            = 293,
  IREADY_IRQn          = 294,

  STERB_IRQn           = 295,
  FLTENDI_IRQn         = 296,
  FLTREQ0I_IRQn        = 297,
  FLTREQ1I_IRQn        = 298,

  MMC0_IRQn            = 299,
  MMC1_IRQn            = 300,
  MMC2_IRQn            = 301,

  SCHI0_3_IRQn         = 302,
  SDHI0_0_IRQn         = 303,
  SDHI0_1_IRQn         = 304,
  SCHI1_3_IRQn         = 305,
  SDHI1_0_IRQn         = 306,
  SDHI1_1_IRQn         = 307,

  ARM_IRQn             = 308,
  PRD_IRQn             = 309,
  CUP_IRQn             = 310,

  SCUAI0_IRQn          = 311,
  SCUAI1_IRQn          = 312,
  SCUFDI0_IRQn         = 313,
  SCUFDI1_IRQn         = 314,
  SCUFDI2_IRQn         = 315,
  SCUFDI3_IRQn         = 316,
  SCUFUI0_IRQn         = 317,
  SCUFUI1_IRQn         = 318,
  SCUFUI2_IRQn         = 319,
  SCUFUI3_IRQn         = 320,
  SCUDVI0_IRQn         = 321,
  SCUDVI1_IRQn         = 322,
  SCUDVI2_IRQn         = 323,
  SCUDVI3_IRQn         = 324,

  MLB_CINT_IRQn        = 325,
  MLB_SINT_IRQn        = 326,

  DRC10_IRQn           = 327,
  DRC11_IRQn           = 328,

  /* 329-330 Reserved  */

  LINI0_INT_T_IRQn     = 331,
  LINI0_INT_R_IRQn     = 332,
  LINI0_INT_S_IRQn     = 333,
  LINI0_INT_M_IRQn     = 334,
  LINI1_INT_T_IRQn     = 335,
  LINI1_INT_R_IRQn     = 336,
  LINI1_INT_S_IRQn     = 337,
  LINI1_INT_M_IRQn     = 338,

  /* 339-346 Reserved */

  SCIERI0_IRQn         = 347,
  SCIRXI0_IRQn         = 348,
  SCITXI0_IRQn         = 349,
  SCITEI0_IRQn         = 350,
  SCIERI1_IRQn         = 351,
  SCIRXI1_IRQn         = 352,
  SCITXI1_IRQn         = 353,
  SCITEI1_IRQn         = 354,

  AVBI_DATA            = 355,
  AVBI_ERROR           = 356,
  AVBI_MANAGE          = 357,
  AVBI_MAC             = 358,

  ETHERI_IRQn          = 359,

  /* 360-363 Reserved */

  CEUI_IRQn            = 364,

  /* 365-380 Reserved */


  H2XMLB_ERRINT_IRQn   = 381,
  H2XIC1_ERRINT_IRQn   = 382,
  X2HPERI1_ERRINT_IRQn = 383,
  X2HPERR2_ERRINT_IRQn = 384,
  X2HPERR34_ERRINT_IRQn= 385,
  X2HPERR5_ERRINT_IRQn = 386,
  X2HPERR67_ERRINT_IRQn= 387,
  X2HDBGR_ERRINT_IRQn  = 388,
  X2HBSC_ERRINT_IRQn   = 389,   
  X2HSPI1_ERRINT_IRQn  = 390,   
  X2HSPI2_ERRINT_IRQn  = 391,   
  PRRI_IRQn            = 392,

  IFEI0_IRQn           = 393,
  OFFI0_IRQn           = 394,
  PFVEI0_IRQn          = 395,
  IFEI1_IRQn           = 396,
  OFFI1_IRQn           = 397,
  PFVEI1_IRQn          = 398,

  /* 399-415 Reserved */
  TINT0_IRQn           = 416,
  TINT1_IRQn           = 417,
  TINT2_IRQn           = 418,
  TINT3_IRQn           = 419,
  TINT4_IRQn           = 420,
  TINT5_IRQn           = 421,
  TINT6_IRQn           = 422,
  TINT7_IRQn           = 423,
  TINT8_IRQn           = 424,
  TINT9_IRQn           = 425,
  TINT10_IRQn          = 426,
  TINT11_IRQn          = 427,
  TINT12_IRQn          = 428,
  TINT13_IRQn          = 429,
  TINT14_IRQn          = 430,
  TINT15_IRQn          = 431,
  TINT16_IRQn          = 432,
  TINT17_IRQn          = 433,
  TINT18_IRQn          = 434,
  TINT19_IRQn          = 435,
  TINT20_IRQn          = 436,
  TINT21_IRQn          = 437,
  TINT22_IRQn          = 438,
  TINT23_IRQn          = 439,
  TINT24_IRQn          = 440,
  TINT25_IRQn          = 441,
  TINT26_IRQn          = 442,
  TINT27_IRQn          = 443,
  TINT28_IRQn          = 444,
  TINT29_IRQn          = 445,
  TINT30_IRQn          = 446,
  TINT31_IRQn          = 447,
  TINT32_IRQn          = 448,
  TINT33_IRQn          = 449,
  TINT34_IRQn          = 450,
  TINT35_IRQn          = 451,
  TINT36_IRQn          = 452,
  TINT37_IRQn          = 453,
  TINT38_IRQn          = 454,
  TINT39_IRQn          = 455,
  TINT40_IRQn          = 456,
  TINT41_IRQn          = 457,
  TINT42_IRQn          = 458,
  TINT43_IRQn          = 459,
  TINT44_IRQn          = 460,
  TINT45_IRQn          = 461,
  TINT46_IRQn          = 462,
  TINT47_IRQn          = 463,
  TINT48_IRQn          = 464,
  TINT49_IRQn          = 465,
  TINT50_IRQn          = 466,
  TINT51_IRQn          = 467,
  TINT52_IRQn          = 468,
  TINT53_IRQn          = 469,
  TINT54_IRQn          = 470,
  TINT55_IRQn          = 471,
  TINT56_IRQn          = 472,
  TINT57_IRQn          = 473,
  TINT58_IRQn          = 474,
  TINT59_IRQn          = 475,
  TINT60_IRQn          = 476,
  TINT61_IRQn          = 477,
  TINT62_IRQn          = 478,
  TINT63_IRQn          = 479,
  TINT64_IRQn          = 480,
  TINT65_IRQn          = 481,
  TINT66_IRQn          = 482,
  TINT67_IRQn          = 483,
  TINT68_IRQn          = 484,
  TINT69_IRQn          = 485,
  TINT70_IRQn          = 486,
  TINT71_IRQn          = 487,
  TINT72_IRQn          = 488,
  TINT73_IRQn          = 489,
  TINT74_IRQn          = 490,
  TINT75_IRQn          = 491,
  TINT76_IRQn          = 492,
  TINT77_IRQn          = 493,
  TINT78_IRQn          = 494,
  TINT79_IRQn          = 495,
  TINT80_IRQn          = 496,
  TINT81_IRQn          = 497,
  TINT82_IRQn          = 498,
  TINT83_IRQn          = 499,
  TINT84_IRQn          = 500,
  TINT85_IRQn          = 501,
  TINT86_IRQn          = 502,
  TINT87_IRQn          = 503,
  TINT88_IRQn          = 504,
  TINT89_IRQn          = 505,
  TINT90_IRQn          = 506,
  TINT91_IRQn          = 507,
  TINT92_IRQn          = 508,
  TINT93_IRQn          = 509,
  TINT94_IRQn          = 510,
  TINT95_IRQn          = 511,
  TINT96_IRQn          = 512,
  TINT97_IRQn          = 513,
  TINT98_IRQn          = 514,
  TINT99_IRQn          = 515,
  TINT100_IRQn         = 516,
  TINT101_IRQn         = 517,
  TINT102_IRQn         = 518,
  TINT103_IRQn         = 519,
  TINT104_IRQn         = 520,
  TINT105_IRQn         = 521,
  TINT106_IRQn         = 522,
  TINT107_IRQn         = 523,
  TINT108_IRQn         = 524,
  TINT109_IRQn         = 525,
  TINT110_IRQn         = 526,
  TINT111_IRQn         = 527,
  TINT112_IRQn         = 528,
  TINT113_IRQn         = 529,
  TINT114_IRQn         = 530,
  TINT115_IRQn         = 531,
  TINT116_IRQn         = 532,
  TINT117_IRQn         = 533,
  TINT118_IRQn         = 534,
  TINT119_IRQn         = 535,
  TINT120_IRQn         = 536,
  TINT121_IRQn         = 537,
  TINT122_IRQn         = 538,
  TINT123_IRQn         = 539,
  TINT124_IRQn         = 540,
  TINT125_IRQn         = 541,
  TINT126_IRQn         = 542,
  TINT127_IRQn         = 543,
  TINT128_IRQn         = 544,
  TINT129_IRQn         = 545,
  TINT130_IRQn         = 546,
  TINT131_IRQn         = 547,
  TINT132_IRQn         = 548,
  TINT133_IRQn         = 549,
  TINT134_IRQn         = 550,
  TINT135_IRQn         = 551,
  TINT136_IRQn         = 552,
  TINT137_IRQn         = 553,
  TINT138_IRQn         = 554,
  TINT139_IRQn         = 555,
  TINT140_IRQn         = 556,
  TINT141_IRQn         = 557,
  TINT142_IRQn         = 558,
  TINT143_IRQn         = 559,
  TINT144_IRQn         = 560,
  TINT145_IRQn         = 561,
  TINT146_IRQn         = 562,
  TINT147_IRQn         = 563,
  TINT148_IRQn         = 564,
  TINT149_IRQn         = 565,
  TINT150_IRQn         = 566,
  TINT151_IRQn         = 567,
  TINT152_IRQn         = 568,
  TINT153_IRQn         = 569,
  TINT154_IRQn         = 570,
  TINT155_IRQn         = 571,
  TINT156_IRQn         = 572,
  TINT157_IRQn         = 573,
  TINT158_IRQn         = 574,
  TINT159_IRQn         = 575,
  TINT160_IRQn         = 576,
  TINT161_IRQn         = 577,
  TINT162_IRQn         = 578,
  TINT163_IRQn         = 579,
  TINT164_IRQn         = 580,
  TINT165_IRQn         = 581,
  TINT166_IRQn         = 582,
  TINT167_IRQn         = 583,
  TINT168_IRQn         = 584,
  TINT169_IRQn         = 585,
  TINT170_IRQn         = 586

} IRQn_Type;

#define Renesas_RZ_A1_IRQ_MAX  TINT170_IRQn

/* --------  Configuration of the Cortex-A9 Processor and Core Peripherals  ------- */
#define __CA9_REV                 0x0000    /*!< Core revision r0                                */

#define __MPU_PRESENT             1         /*!< MPU present or not                               */

#define __FPU_PRESENT             1         /*!< FPU present or not                               */

#define __NVIC_PRIO_BITS          5         /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used     */

#include <core_ca9.h>
#include "system_MBRZA1H.h"


/******************************************************************************/
/*                Device Specific Peripheral Section                          */
/******************************************************************************/
/** @addtogroup Renesas_RZ_A1_Peripherals Renesas_RZ_A1 Peripherals
  Renesas_RZ_A1 Device Specific Peripheral registers structures
  @{
*/

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

#include "pl310.h"
#include "gic.h"
#include "nvic_wrapper.h"
#include "cmsis_nvic.h"

#include "ostm_iodefine.h"
#include "gpio_iodefine.h"
#include "cpg_iodefine.h"
#include "l2c_iodefine.h"

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

/*@}*/ /* end of group Renesas_RZ_A1_Peripherals */


/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/** @addtogroup Renesas_RZ_A1_MemoryMap Renesas_RZ_A1 Memory Mapping
  @{
*/

/* R7S72100 CPU board  */
#define Renesas_RZ_A1_NORFLASH_BASE0               (0x00000000UL)                        /*!< (FLASH0    ) Base Address */
#define Renesas_RZ_A1_NORFLASH_BASE1               (0x04000000UL)                        /*!< (FLASH1    ) Base Address */
#define Renesas_RZ_A1_SDRAM_BASE0                  (0x08000000UL)                        /*!< (SDRAM0    ) Base Address */
#define Renesas_RZ_A1_SDRAM_BASE1                  (0x0C000000UL)                        /*!< (SDRAM1    ) Base Address */
#define Renesas_RZ_A1_USER_AREA0                   (0x10000000UL)                        /*!< (USER0     ) Base Address */
#define Renesas_RZ_A1_USER_AREA1                   (0x14000000UL)                        /*!< (USER1     ) Base Address */
#define Renesas_RZ_A1_SPI_IO0                      (0x18000000UL)                        /*!< (SPI_IO0   ) Base Address */
#define Renesas_RZ_A1_SPI_IO1                      (0x1C000000UL)                        /*!< (SPI_IO1   ) Base Address */
#define Renesas_RZ_A1_ONCHIP_SRAM_BASE             (0x20000000UL)                        /*!< (SRAM_OC   ) Base Address */
#define Renesas_RZ_A1_SPI_MIO_BASE                 (0x3fe00000UL)                        /*!< (SPI_MIO   ) Base Address */
#define Renesas_RZ_A1_BSC_BASE                     (0x3ff00000UL)                        /*!< (BSC       ) Base Address */
#define Renesas_RZ_A1_PERIPH_BASE0                 (0xe8000000UL)                        /*!< (PERIPH0   ) Base Address */
#define Renesas_RZ_A1_PERIPH_BASE1                 (0xfcf00000UL)                        /*!< (PERIPH1   ) Base Address */
#define Renesas_RZ_A1_GIC_DISTRIBUTOR_BASE         (0xe8201000UL)                        /*!< (GIC DIST  ) Base Address */
#define Renesas_RZ_A1_GIC_INTERFACE_BASE           (0xe8202000UL)                        /*!< (GIC CPU IF) Base Address */
#define Renesas_RZ_A1_PL310_BASE                   (0x3ffff000UL)                        /*!< (PL310     ) Base Address */
#define Renesas_RZ_A1_ONCHIP_SRAM_NC_BASE          (0x60000000UL)                        /*!< (SRAM_OC   ) Base Address */

//Following macros define the descriptors and attributes used to define the Renesas_RZ_A1 MMU flat-map
//Sect_Normal. Outer & inner wb/wa, non-shareable, executable, rw, domain 0.
#define section_normal(descriptor_l1, region)     region.rg_t = SECTION; \
                                   region.domain = 0x0; \
                                   region.e_t = ECC_DISABLED; \
                                   region.g_t = GLOBAL; \
                                   region.inner_norm_t = WB_WA; \
                                   region.outer_norm_t = WB_WA; \
                                   region.mem_t = NORMAL; \
                                   region.sec_t = NON_SECURE; \
                                   region.xn_t = EXECUTE; \
                                   region.priv_t = RW; \
                                   region.user_t = RW; \
                                   region.sh_t = NON_SHARED; \
                                   __get_section_descriptor(&descriptor_l1, region);

#define section_normal_nc(descriptor_l1, region)     region.rg_t = SECTION; \
                                   region.domain = 0x0; \
                                   region.e_t = ECC_DISABLED; \
                                   region.g_t = GLOBAL; \
                                   region.inner_norm_t = NON_CACHEABLE; \
                                   region.outer_norm_t = NON_CACHEABLE; \
                                   region.mem_t = NORMAL; \
                                   region.sec_t = SECURE; \
                                   region.xn_t = EXECUTE; \
                                   region.priv_t = RW; \
                                   region.user_t = RW; \
                                   region.sh_t = NON_SHARED; \
                                   __get_section_descriptor(&descriptor_l1, region);

//Sect_Normal_Cod. Outer & inner wb/wa, non-shareable, executable, ro, domain 0.
#define section_normal_cod(descriptor_l1, region) region.rg_t = SECTION; \
                                   region.domain = 0x0; \
                                   region.e_t = ECC_DISABLED; \
                                   region.g_t = GLOBAL; \
                                   region.inner_norm_t = WB_WA; \
                                   region.outer_norm_t = WB_WA; \
                                   region.mem_t = NORMAL; \
                                   region.sec_t = NON_SECURE; \
                                   region.xn_t = EXECUTE; \
                                   region.priv_t = READ; \
                                   region.user_t = READ; \
                                   region.sh_t = NON_SHARED; \
                                   __get_section_descriptor(&descriptor_l1, region);

//Sect_Normal_RO. Sect_Normal_Cod, but not executable
#define section_normal_ro(descriptor_l1, region)  region.rg_t = SECTION; \
                                   region.domain = 0x0; \
                                   region.e_t = ECC_DISABLED; \
                                   region.g_t = GLOBAL; \
                                   region.inner_norm_t = WB_WA; \
                                   region.outer_norm_t = WB_WA; \
                                   region.mem_t = NORMAL; \
                                   region.sec_t = NON_SECURE; \
                                   region.xn_t = NON_EXECUTE; \
                                   region.priv_t = READ; \
                                   region.user_t = READ; \
                                   region.sh_t = NON_SHARED; \
                                   __get_section_descriptor(&descriptor_l1, region);

//Sect_Normal_RW. Sect_Normal_Cod, but writeable and not executable
#define section_normal_rw(descriptor_l1, region) region.rg_t = SECTION; \
                                   region.domain = 0x0; \
                                   region.e_t = ECC_DISABLED; \
                                   region.g_t = GLOBAL; \
                                   region.inner_norm_t = WB_WA; \
                                   region.outer_norm_t = WB_WA; \
                                   region.mem_t = NORMAL; \
                                   region.sec_t = NON_SECURE; \
                                   region.xn_t = NON_EXECUTE; \
                                   region.priv_t = RW; \
                                   region.user_t = RW; \
                                   region.sh_t = NON_SHARED; \
                                   __get_section_descriptor(&descriptor_l1, region);
//Sect_SO. Strongly-ordered (therefore shareable), not executable, rw, domain 0, base addr 0
#define section_so(descriptor_l1, region) region.rg_t = SECTION; \
                                   region.domain = 0x0; \
                                   region.e_t = ECC_DISABLED; \
                                   region.g_t = GLOBAL; \
                                   region.inner_norm_t = NON_CACHEABLE; \
                                   region.outer_norm_t = NON_CACHEABLE; \
                                   region.mem_t = STRONGLY_ORDERED; \
                                   region.sec_t = SECURE; \
                                   region.xn_t = NON_EXECUTE; \
                                   region.priv_t = RW; \
                                   region.user_t = RW; \
                                   region.sh_t = NON_SHARED; \
                                   __get_section_descriptor(&descriptor_l1, region);

//Sect_Device_RO. Device, non-shareable, non-executable, ro, domain 0, base addr 0
#define section_device_ro(descriptor_l1, region) region.rg_t = SECTION; \
                                   region.domain = 0x0; \
                                   region.e_t = ECC_DISABLED; \
                                   region.g_t = GLOBAL; \
                                   region.inner_norm_t = NON_CACHEABLE; \
                                   region.outer_norm_t = NON_CACHEABLE; \
                                   region.mem_t = STRONGLY_ORDERED; \
                                   region.sec_t = SECURE; \
                                   region.xn_t = NON_EXECUTE; \
                                   region.priv_t = READ; \
                                   region.user_t = READ; \
                                   region.sh_t = NON_SHARED; \
                                   __get_section_descriptor(&descriptor_l1, region);

//Sect_Device_RW. Sect_Device_RO, but writeable
#define section_device_rw(descriptor_l1, region) region.rg_t = SECTION; \
                                   region.domain = 0x0; \
                                   region.e_t = ECC_DISABLED; \
                                   region.g_t = GLOBAL; \
                                   region.inner_norm_t = NON_CACHEABLE; \
                                   region.outer_norm_t = NON_CACHEABLE; \
                                   region.mem_t = STRONGLY_ORDERED; \
                                   region.sec_t = SECURE; \
                                   region.xn_t = NON_EXECUTE; \
                                   region.priv_t = RW; \
                                   region.user_t = RW; \
                                   region.sh_t = NON_SHARED; \
                                   __get_section_descriptor(&descriptor_l1, region);
//Page_4k_Device_RW.  Shared device, not executable, rw, domain 0
#define page4k_device_rw(descriptor_l1, descriptor_l2, region) region.rg_t = PAGE_4k; \
                                   region.domain = 0x0; \
                                   region.e_t = ECC_DISABLED; \
                                   region.g_t = GLOBAL; \
                                   region.inner_norm_t = NON_CACHEABLE; \
                                   region.outer_norm_t = NON_CACHEABLE; \
                                   region.mem_t = SHARED_DEVICE; \
                                   region.sec_t = SECURE; \
                                   region.xn_t = NON_EXECUTE; \
                                   region.priv_t = RW; \
                                   region.user_t = RW; \
                                   region.sh_t = NON_SHARED; \
                                   __get_page_descriptor(&descriptor_l1, &descriptor_l2, region);

//Page_64k_Device_RW.  Shared device, not executable, rw, domain 0
#define page64k_device_rw(descriptor_l1, descriptor_l2, region)  region.rg_t = PAGE_64k; \
                                   region.domain = 0x0; \
                                   region.e_t = ECC_DISABLED; \
                                   region.g_t = GLOBAL; \
                                   region.inner_norm_t = NON_CACHEABLE; \
                                   region.outer_norm_t = NON_CACHEABLE; \
                                   region.mem_t = SHARED_DEVICE; \
                                   region.sec_t = SECURE; \
                                   region.xn_t = NON_EXECUTE; \
                                   region.priv_t = RW; \
                                   region.user_t = RW; \
                                   region.sh_t = NON_SHARED; \
                                   __get_page_descriptor(&descriptor_l1, &descriptor_l2, region);

/*@}*/ /* end of group Renesas_RZ_A1_MemoryMap */

/******************************************************************************/
/*                         Clock Settings                                     */
/******************************************************************************/
/** @addtogroup Renesas_RZ_A1_H_Clocks Renesas_RZ_A1 Clock definitions
  @{
*/

/*
 * Clock Mode 0 settings
 * SW1-4(MD_CLK):ON
 * SW1-5(MD_CLKS):ON
 * FRQCR=0x1035
 *   CLKEN2    = 0b - unstable
 *   CLKEN[1:0]=01b - Output, Low, Low
 *   IFC[1:0]  =00b - CPU clock is 1/1 PLL clock
 * FRQCR2=0x0001
 *   GFC[1:0]  =01b - Graphic clock is 2/3 bus clock
 */
#define CM0_RENESAS_RZ_A1_CLKIN  ( 13333333u)
#define CM0_RENESAS_RZ_A1_CLKO   ( 66666666u)
#define CM0_RENESAS_RZ_A1_I_CLK  (400000000u)
#define CM0_RENESAS_RZ_A1_G_CLK  (266666666u)
#define CM0_RENESAS_RZ_A1_B_CLK  (133333333u)
#define CM0_RENESAS_RZ_A1_P1_CLK ( 66666666u)
#define CM0_RENESAS_RZ_A1_P0_CLK ( 33333333u)

/*
 * Clock Mode 1 settings
 * SW1-4(MD_CLK):OFF
 * SW1-5(MD_CLKS):ON
 * FRQCR=0x1335
 *   CLKEN2    = 0b - unstable
 *   CLKEN[1:0]=01b - Output, Low, Low
 *   IFC[1:0]  =11b - CPU clock is 1/3 PLL clock
 * FRQCR2=0x0003
 *   GFC[1:0]  =11b - graphic clock is 1/3 bus clock
 */
#define CM1_RENESAS_RZ_A1_CLKIN  ( 48000000u)
#define CM1_RENESAS_RZ_A1_CLKO   ( 64000000u)
#define CM1_RENESAS_RZ_A1_I_CLK  (128000000u)
#define CM1_RENESAS_RZ_A1_G_CLK  (128000000u)
#define CM1_RENESAS_RZ_A1_B_CLK  (128000000u)
#define CM1_RENESAS_RZ_A1_P1_CLK ( 64000000u)
#define CM1_RENESAS_RZ_A1_P0_CLK ( 32000000u)

/*@}*/ /* end of group Renesas_RZ_A1_Clocks */

/******************************************************************************/
/*                         CPG   Settings                                     */
/******************************************************************************/
/** @addtogroup Renesas_RZ_A1_H_CPG Renesas_RZ_A1 CPG Bit definitions
  @{
*/

#define CPG_FRQCR_SHIFT_CKOEN2  (14)
#define CPG_FRQCR_BIT_CKOEN2    (0x1 << CPG_FRQCR_SHIFT_CKOEN2)
#define CPG_FRQCR_SHIFT_CKOEN0  (12)
#define CPG_FRQCR_BITS_CKOEN0   (0x3 << CPG_FRQCR_SHIFT_CKOEN0)
#define CPG_FRQCR_SHIFT_IFC     (8)
#define CPG_FRQCR_BITS_IFC      (0x3 << CPG_FRQCR_SHIFT_IFC)

#define CPG_FRQCR2_SHIFT_GFC    (0)
#define CPG_FRQCR2_BITS_GFC     (0x3 << CPG_FRQCR2_SHIFT_GFC)


#define CPG_STBCR1_BIT_STBY     (0x80u)
#define CPG_STBCR1_BIT_DEEP     (0x40u)
#define CPG_STBCR2_BIT_HIZ      (0x80u)
#define CPG_STBCR2_BIT_MSTP20   (0x01u) /* CoreSight */
#define CPG_STBCR3_BIT_MSTP37   (0x80u) /* IEBus */
#define CPG_STBCR3_BIT_MSTP36   (0x40u) /* IrDA */
#define CPG_STBCR3_BIT_MSTP35   (0x20u) /* LIN0 */
#define CPG_STBCR3_BIT_MSTP34   (0x10u) /* LIN1 */
#define CPG_STBCR3_BIT_MSTP33   (0x08u) /* Multi-Function Timer */
#define CPG_STBCR3_BIT_MSTP32   (0x04u) /* CAN */
#define CPG_STBCR3_BIT_MSTP30   (0x01u) /* Motor Control PWM Timer */
#define CPG_STBCR4_BIT_MSTP47   (0x80u) /* SCIF0 */
#define CPG_STBCR4_BIT_MSTP46   (0x40u) /* SCIF1 */
#define CPG_STBCR4_BIT_MSTP45   (0x20u) /* SCIF2 */
#define CPG_STBCR4_BIT_MSTP44   (0x10u) /* SCIF3 */
#define CPG_STBCR4_BIT_MSTP43   (0x08u) /* SCIF4 */
#define CPG_STBCR4_BIT_MSTP42   (0x04u) /* SCIF5 */
#define CPG_STBCR4_BIT_MSTP41   (0x02u) /* SCIF6 */
#define CPG_STBCR4_BIT_MSTP40   (0x01u) /* SCIF7 */
#define CPG_STBCR5_BIT_MSTP57   (0x80u) /* SCI0 */
#define CPG_STBCR5_BIT_MSTP56   (0x40u) /* SCI1 */
#define CPG_STBCR5_BIT_MSTP55   (0x20u) /* Sound Generator0 */
#define CPG_STBCR5_BIT_MSTP54   (0x10u) /* Sound Generator1 */
#define CPG_STBCR5_BIT_MSTP53   (0x08u) /* Sound Generator2 */
#define CPG_STBCR5_BIT_MSTP52   (0x04u) /* Sound Generator3 */
#define CPG_STBCR5_BIT_MSTP51   (0x02u) /* OSTM0 */
#define CPG_STBCR5_BIT_MSTP50   (0x01u) /* OSTM1 */
#define CPG_STBCR6_BIT_MSTP67   (0x80u) /* General A/D Comvertor */
#define CPG_STBCR6_BIT_MSTP66   (0x40u) /* Capture Engine */
#define CPG_STBCR6_BIT_MSTP65   (0x20u) /* Display out comparison0 */
#define CPG_STBCR6_BIT_MSTP64   (0x10u) /* Display out comparison1 */   
#define CPG_STBCR6_BIT_MSTP63   (0x08u) /* Dynamic Range Compalator0 */
#define CPG_STBCR6_BIT_MSTP62   (0x04u) /* Dynamic Range Compalator1 */
#define CPG_STBCR6_BIT_MSTP61   (0x02u) /* JPEG Decoder */
#define CPG_STBCR6_BIT_MSTP60   (0x01u) /* Realtime Clock */
#define CPG_STBCR7_BIT_MSTP77   (0x80u) /* Video Decoder0 */
#define CPG_STBCR7_BIT_MSTP76   (0x40u) /* Video Decoder1 */
#define CPG_STBCR7_BIT_MSTP74   (0x10u) /* Ether */
#define CPG_STBCR7_BIT_MSTP73   (0x04u) /* NAND Flash Memory Controller */
#define CPG_STBCR7_BIT_MSTP71   (0x02u) /* USB0 */
#define CPG_STBCR7_BIT_MSTP70   (0x01u) /* USB1 */
#define CPG_STBCR8_BIT_MSTP87   (0x80u) /* IMR-LS2_0 */
#define CPG_STBCR8_BIT_MSTP86   (0x40u) /* IMR-LS2_1 */
#define CPG_STBCR8_BIT_MSTP85   (0x20u) /* IMR-LSD */
#define CPG_STBCR8_BIT_MSTP84   (0x10u) /* MMC Host Interface */
#define CPG_STBCR8_BIT_MSTP83   (0x08u) /* MediaLB */
#define CPG_STBCR8_BIT_MSTP81   (0x02u) /* SCUX */
#define CPG_STBCR9_BIT_MSTP97   (0x80u) /* RIIC0 */
#define CPG_STBCR9_BIT_MSTP96   (0x40u) /* RIIC1 */
#define CPG_STBCR9_BIT_MSTP95   (0x20u) /* RIIC2 */
#define CPG_STBCR9_BIT_MSTP94   (0x10u) /* RIIC3 */
#define CPG_STBCR9_BIT_MSTP93   (0x08u) /* SPI Multi I/O Bus Controller0 */
#define CPG_STBCR9_BIT_MSTP92   (0x04u) /* SPI Multi I/O Bus Controller1 */
#define CPG_STBCR9_BIT_MSTP91   (0x02u) /* VDC5_0 */
#define CPG_STBCR9_BIT_MSTP90   (0x01u) /* VDC5_1 */
#define CPG_STBCR10_BIT_MSTP107 (0x80u) /* RSPI0 */
#define CPG_STBCR10_BIT_MSTP106 (0x40u) /* RSPI1 */
#define CPG_STBCR10_BIT_MSTP105 (0x20u) /* RSPI2 */
#define CPG_STBCR10_BIT_MSTP104 (0x10u) /* RSPI3 */
#define CPG_STBCR10_BIT_MSTP103 (0x08u) /* RSPI4 */
#define CPG_STBCR10_BIT_MSTP102 (0x04u) /* ROMDEC */
#define CPG_STBCR10_BIT_MSTP101 (0x02u) /* SPIDF */
#define CPG_STBCR10_BIT_MSTP100 (0x01u) /* OpenVG */
#define CPG_STBCR11_BIT_MSTP115 (0x20u) /* SSIF0 */
#define CPG_STBCR11_BIT_MSTP114 (0x10u) /* SSIF1 */
#define CPG_STBCR11_BIT_MSTP113 (0x08u) /* SSIF2 */
#define CPG_STBCR11_BIT_MSTP112 (0x04u) /* SSIF3 */
#define CPG_STBCR11_BIT_MSTP111 (0x02u) /* SSIF4 */
#define CPG_STBCR11_BIT_MSTP110 (0x01u) /* SSIF5 */
#define CPG_STBCR12_BIT_MSTP123 (0x08u) /* SD Host Interface00 */
#define CPG_STBCR12_BIT_MSTP122 (0x04u) /* SD Host Interface01 */
#define CPG_STBCR12_BIT_MSTP121 (0x02u) /* SD Host Interface10 */
#define CPG_STBCR12_BIT_MSTP120 (0x01u) /* SD Host Interface11 */
#define CPG_CSTBCR1_BIT_CMSTP11 (0x02u) /* PFV */
#define CPG_SWRSTCR1_BIT_AXTALE (0x80u) /* AUDIO_X1 */
#define CPG_SWRSTCR1_BIT_SRST16 (0x40u) /* SSIF0 */
#define CPG_SWRSTCR1_BIT_SRST15 (0x20u) /* SSIF1 */
#define CPG_SWRSTCR1_BIT_SRST14 (0x10u) /* SSIF2 */
#define CPG_SWRSTCR1_BIT_SRST13 (0x08u) /* SSIF3 */
#define CPG_SWRSTCR1_BIT_SRST12 (0x04u) /* SSIF4 */
#define CPG_SWRSTCR1_BIT_SRST11 (0x02u) /* SSIF5 */
#define CPG_SWRSTCR2_BIT_SRST27 (0x80u) /* Display out comparison0 */
#define CPG_SWRSTCR2_BIT_SRST26 (0x40u) /* Display out comparison1 */
#define CPG_SWRSTCR2_BIT_SRST25 (0x20u) /* Dynamic Range Compalator0 */
#define CPG_SWRSTCR2_BIT_SRST24 (0x10u) /* Dynamic Range Compalator1 */
#define CPG_SWRSTCR2_BIT_SRST23 (0x08u) /* VDC5_0 */
#define CPG_SWRSTCR2_BIT_SRST22 (0x04u) /* VDC5_1 */
#define CPG_SWRSTCR2_BIT_SRST21 (0x02u) /* JPEG Decoder */
#define CPG_SWRSTCR3_BIT_SRST36 (0x40u) /* DMA */
#define CPG_SWRSTCR3_BIT_SRST35 (0x20u) /* IMR-LS2_0 */
#define CPG_SWRSTCR3_BIT_SRST34 (0x10u) /* IMR-LS2_1 */
#define CPG_SWRSTCR3_BIT_SRST33 (0x08u) /* IMR-LSD? */
#define CPG_SWRSTCR3_BIT_SRST32 (0x04u) /* OpenVG */
#define CPG_SWRSTCR3_BIT_SRST31 (0x02u) /* Capture Engine */
#define CPG_SWRSTCR4_BIT_SRST41 (0x02u) /* Video Decoder0 */
#define CPG_SWRSTCR4_BIT_SRST40 (0x01u) /* Video Decoder1 */
#define CPG_SYSCR1_BIT_VRAME4   (0x10u) /* VRAM E Page4 */
#define CPG_SYSCR1_BIT_VRAME3   (0x08u) /* VRAM E Page3 */
#define CPG_SYSCR1_BIT_VRAME2   (0x04u) /* VRAM E Page2 */
#define CPG_SYSCR1_BIT_VRAME1   (0x02u) /* VRAM E Page1 */
#define CPG_SYSCR1_BIT_VRAME0   (0x01u) /* VRAM E Page0 */
#define CPG_SYSCR2_BIT_VRAMWE4  (0x10u) /* VRAM WE Page4 */
#define CPG_SYSCR2_BIT_VRAMWE3  (0x08u) /* VRAM WE Page3 */
#define CPG_SYSCR2_BIT_VRAMWE2  (0x04u) /* VRAM WE Page2 */
#define CPG_SYSCR2_BIT_VRAMWE1  (0x02u) /* VRAM WE Page1 */
#define CPG_SYSCR2_BIT_VRAMWE0  (0x01u) /* VRAM WE Page0 */
#define CPG_SYSCR3_BIT_RRAMWE3  (0x08u) /* RRAM WE Page3 */
#define CPG_SYSCR3_BIT_RRAMWE2  (0x04u) /* RRAM WE Page2 */
#define CPG_SYSCR3_BIT_RRAMWE1  (0x02u) /* RRAM WE Page1 */
#define CPG_SYSCR3_BIT_RRAMWE0  (0x01u) /* RRAM WE Page0 */

/*@}*/ /* end of group Renesas_RZ_A1_CPG */

/******************************************************************************/
/*                        GPIO   Settings                                     */
/******************************************************************************/
/** @addtogroup Renesas_RZ_A1_H_GPIO Renesas_RZ_A1 GPIO Bit definitions
  @{
*/

#define GPIO_BIT_N0  (1u <<  0)
#define GPIO_BIT_N1  (1u <<  1)
#define GPIO_BIT_N2  (1u <<  2)
#define GPIO_BIT_N3  (1u <<  3)
#define GPIO_BIT_N4  (1u <<  4)
#define GPIO_BIT_N5  (1u <<  5)
#define GPIO_BIT_N6  (1u <<  6)
#define GPIO_BIT_N7  (1u <<  7)
#define GPIO_BIT_N8  (1u <<  8)
#define GPIO_BIT_N9  (1u <<  9)
#define GPIO_BIT_N10 (1u << 10)
#define GPIO_BIT_N11 (1u << 11)
#define GPIO_BIT_N12 (1u << 12)
#define GPIO_BIT_N13 (1u << 13)
#define GPIO_BIT_N14 (1u << 14)
#define GPIO_BIT_N15 (1u << 15)


#define MD_BOOT10_MASK    (0x3)

#define MD_BOOT10_BM0     (0x0)
#define MD_BOOT10_BM1     (0x2)
#define MD_BOOT10_BM3     (0x1)
#define MD_BOOT10_BM4_5   (0x3)

#define MD_CLK        (1u << 2)
#define MD_CLKS       (1u << 3)

/*@}*/ /* end of group Renesas_RZ_A1_GPIO */

#ifdef __cplusplus
}
#endif

#endif  // __MBRZA1H_H__
