/****************************************************************************
 *   $Id:: LPC8xx.h 6437 2012-10-31 11:06:06Z dep00694                     $
 *   Project: NXP LPC8xx software example
 *
 *   Description:
 *     CMSIS Cortex-M0+ Core Peripheral Access Layer Header File for
 *     NXP LPC800 Device Series
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.

 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors'
 * relevant copyright in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers. This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
****************************************************************************/
#ifndef __LPC8xx_H__
#define __LPC8xx_H__

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup LPC8xx_Definitions LPC8xx Definitions
  This file defines all structures and symbols for LPC8xx:
    - Registers and bitfields
    - peripheral base address
    - PIO definitions
  @{
*/


/******************************************************************************/
/*                Processor and Core Peripherals                              */
/******************************************************************************/
/** @addtogroup LPC8xx_CMSIS LPC8xx CMSIS Definitions
  Configuration of the Cortex-M0+ Processor and Core Peripherals
  @{
*/

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */
typedef enum IRQn
{
/******  Cortex-M0 Processor Exceptions Numbers ***************************************************/
  Reset_IRQn                    = -15,    /*!< 1 Reset Vector, invoked on Power up and warm reset*/
  NonMaskableInt_IRQn           = -14,    /*!< 2 Non Maskable Interrupt                           */
  HardFault_IRQn                = -13,    /*!< 3 Cortex-M0 Hard Fault Interrupt                   */
  SVCall_IRQn                   = -5,     /*!< 11 Cortex-M0 SV Call Interrupt                     */
  PendSV_IRQn                   = -2,     /*!< 14 Cortex-M0 Pend SV Interrupt                     */
  SysTick_IRQn                  = -1,     /*!< 15 Cortex-M0 System Tick Interrupt                 */

/******  LPC8xx Specific Interrupt Numbers ********************************************************/
  SPI0_IRQn                     = 0,        /*!< SPI0                                             */
  SPI1_IRQn                     = 1,        /*!< SPI1                                             */
  Reserved0_IRQn                = 2,        /*!< Reserved Interrupt                               */
  UART0_IRQn                    = 3,        /*!< USART0                                            */
  UART1_IRQn                    = 4,        /*!< USART1                                            */
  UART2_IRQn                    = 5,        /*!< USART2                                            */
  Reserved1_IRQn                = 6,        /*!< Reserved Interrupt                               */
  Reserved2_IRQn                = 7,        /*!< Reserved Interrupt                               */
  I2C_IRQn                      = 8,        /*!< I2C                                              */
  SCT_IRQn                      = 9,        /*!< SCT                                              */
  MRT_IRQn                      = 10,       /*!< MRT                                              */
  CMP_IRQn                      = 11,       /*!< CMP                                              */
  WDT_IRQn                      = 12,      /*!< WDT                                              */
  BOD_IRQn                      = 13,       /*!< BOD                                              */
  Reserved3_IRQn                = 14,       /*!< Reserved Interrupt                               */
  WKT_IRQn                      = 15,       /*!< WKT Interrupt                                    */
  Reserved4_IRQn                = 16,       /*!< Reserved Interrupt                               */
  Reserved5_IRQn                = 17,       /*!< Reserved Interrupt                               */
  Reserved6_IRQn                = 18,       /*!< Reserved Interrupt                               */
  Reserved7_IRQn                = 19,       /*!< Reserved Interrupt                               */
  Reserved8_IRQn                = 20,       /*!< Reserved Interrupt                               */
  Reserved9_IRQn                = 21,       /*!< Reserved Interrupt                               */
  Reserved10_IRQn               = 22,       /*!< Reserved Interrupt                               */
  Reserved11_IRQn               = 23,       /*!< Reserved Interrupt                               */
  PININT0_IRQn               	  = 24,       /*!< External Interrupt 0                             */
  PININT1_IRQn                  = 25,       /*!< External Interrupt 1                             */
  PININT2_IRQn                  = 26,       /*!< External Interrupt 2                             */
  PININT3_IRQn                  = 27,       /*!< External Interrupt 3                             */
  PININT4_IRQn                  = 28,       /*!< External Interrupt 4                             */
  PININT5_IRQn                  = 29,       /*!< External Interrupt 5                             */
  PININT6_IRQn                  = 30,       /*!< External Interrupt 6                             */
  PININT7_IRQn                  = 31,       /*!< External Interrupt 7                             */
} IRQn_Type;

/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M0+ Processor and Core Peripherals */
#define __MPU_PRESENT             0         /*!< MPU present or not                               */
#define __VTOR_PRESENT            1         /**< Defines if an VTOR is present or not */
#define __NVIC_PRIO_BITS          2         /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used     */

/*@}*/ /* end of group LPC8xx_CMSIS */


#include "core_cm0plus.h"                  /* Cortex-M0+ processor and core peripherals          */
#include "system_LPC8xx.h"                 /* System Header                                      */


/******************************************************************************/
/*                Device Specific Peripheral Registers structures             */
/******************************************************************************/

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/*------------- System Control (SYSCON) --------------------------------------*/
/** @addtogroup LPC8xx_SYSCON LPC8xx System Control Block
  @{
*/
typedef struct
{
  __IO uint32_t SYSMEMREMAP;            /*!< Offset: 0x000 System memory remap (R/W) */
  __IO uint32_t PRESETCTRL;             /*!< Offset: 0x004 Peripheral reset control (R/W) */
  __IO uint32_t SYSPLLCTRL;             /*!< Offset: 0x008 System PLL control (R/W) */
  __IO uint32_t SYSPLLSTAT;             /*!< Offset: 0x00C System PLL status (R/W ) */
       uint32_t RESERVED0[4];

  __IO uint32_t SYSOSCCTRL;             /*!< Offset: 0x020 System oscillator control (R/W) */
  __IO uint32_t WDTOSCCTRL;             /*!< Offset: 0x024 Watchdog oscillator control (R/W) */
       uint32_t RESERVED1[2];
  __IO uint32_t SYSRSTSTAT;             /*!< Offset: 0x030 System reset status Register (R/W ) */
       uint32_t RESERVED2[3];
  __IO uint32_t SYSPLLCLKSEL;           /*!< Offset: 0x040 System PLL clock source select (R/W) */
  __IO uint32_t SYSPLLCLKUEN;           /*!< Offset: 0x044 System PLL clock source update enable (R/W) */
       uint32_t RESERVED3[10];

  __IO uint32_t MAINCLKSEL;             /*!< Offset: 0x070 Main clock source select (R/W) */
  __IO uint32_t MAINCLKUEN;             /*!< Offset: 0x074 Main clock source update enable (R/W) */
  __IO uint32_t SYSAHBCLKDIV;           /*!< Offset: 0x078 System AHB clock divider (R/W) */
       uint32_t RESERVED4[1];

  __IO uint32_t SYSAHBCLKCTRL;          /*!< Offset: 0x080 System AHB clock control (R/W) */
       uint32_t RESERVED5[4];
  __IO uint32_t UARTCLKDIV;             /*!< Offset: 0x094 UART clock divider (R/W) */
       uint32_t RESERVED6[18];

  __IO uint32_t CLKOUTSEL;              /*!< Offset: 0x0E0 CLKOUT clock source select (R/W) */
  __IO uint32_t CLKOUTUEN;              /*!< Offset: 0x0E4 CLKOUT clock source update enable (R/W) */
  __IO uint32_t CLKOUTDIV;              /*!< Offset: 0x0E8 CLKOUT clock divider (R/W) */
       uint32_t RESERVED7;
  __IO uint32_t UARTFRGDIV;             /*!< Offset: 0x0F0 UART fractional divider SUB(R/W) */
  __IO uint32_t UARTFRGMULT;             /*!< Offset: 0x0F4 UART fractional divider ADD(R/W) */
       uint32_t RESERVED8[1];
  __IO uint32_t EXTTRACECMD;            /*!< (@ 0x400480FC) External trace buffer command register  */
  __IO uint32_t PIOPORCAP0;             /*!< Offset: 0x100 POR captured PIO status 0 (R/ ) */
       uint32_t RESERVED9[12];
  __IO uint32_t IOCONCLKDIV[7];       /*!< (@0x40048134-14C) Peripheral clock x to the IOCON block for programmable glitch filter */
  __IO uint32_t BODCTRL;                /*!< Offset: 0x150 BOD control (R/W) */
  __IO uint32_t SYSTCKCAL;              /*!< Offset: 0x154 System tick counter calibration (R/W) */
       uint32_t RESERVED10[6];
  __IO uint32_t IRQLATENCY;             /*!< (@ 0x40048170) IRQ delay */
  __IO uint32_t NMISRC;                 /*!< (@ 0x40048174) NMI Source Control     */
  __IO uint32_t PINTSEL[8];             /*!< (@ 0x40048178) GPIO Pin Interrupt Select register 0 */
       uint32_t RESERVED11[27];
  __IO uint32_t STARTERP0;              /*!< Offset: 0x204 Start logic signal enable Register 0 (R/W) */
       uint32_t RESERVED12[3];
  __IO uint32_t STARTERP1;              /*!< Offset: 0x214 Start logic signal enable Register 0 (R/W) */
       uint32_t RESERVED13[6];
  __IO uint32_t PDSLEEPCFG;             /*!< Offset: 0x230 Power-down states in Deep-sleep mode (R/W) */
  __IO uint32_t PDAWAKECFG;             /*!< Offset: 0x234 Power-down states after wake-up (R/W) */
  __IO uint32_t PDRUNCFG;               /*!< Offset: 0x238 Power-down configuration Register (R/W) */
       uint32_t RESERVED14[110];
  __I  uint32_t DEVICE_ID;              /*!< Offset: 0x3F4 Device ID (R/ ) */
} LPC_SYSCON_TypeDef;
/*@}*/ /* end of group LPC8xx_SYSCON */


/**
  * @brief Product name title=UM10462 Chapter title=LPC8xx I/O configuration Modification date=3/16/2011 Major revision=0 Minor revision=3  (IOCONFIG)
  */

typedef struct {                            /*!< (@ 0x40044000) IOCONFIG Structure     */
  __IO uint32_t PIO0_17;                    /*!< (@ 0x40044000) I/O configuration for pin PIO0_17 */
  __IO uint32_t PIO0_13;                    /*!< (@ 0x40044004) I/O configuration for pin PIO0_13 */
  __IO uint32_t PIO0_12;                    /*!< (@ 0x40044008) I/O configuration for pin PIO0_12 */
  __IO uint32_t PIO0_5;                     /*!< (@ 0x4004400C) I/O configuration for pin PIO0_5 */
  __IO uint32_t PIO0_4;                     /*!< (@ 0x40044010) I/O configuration for pin PIO0_4 */
  __IO uint32_t PIO0_3;                     /*!< (@ 0x40044014) I/O configuration for pin PIO0_3 */
  __IO uint32_t PIO0_2;                     /*!< (@ 0x40044018) I/O configuration for pin PIO0_2 */
  __IO uint32_t PIO0_11;                    /*!< (@ 0x4004401C) I/O configuration for pin PIO0_11 */
  __IO uint32_t PIO0_10;                    /*!< (@ 0x40044020) I/O configuration for pin PIO0_10 */
  __IO uint32_t PIO0_16;                    /*!< (@ 0x40044024) I/O configuration for pin PIO0_16 */
  __IO uint32_t PIO0_15;                    /*!< (@ 0x40044028) I/O configuration for pin PIO0_15 */
  __IO uint32_t PIO0_1;                     /*!< (@ 0x4004402C) I/O configuration for pin PIO0_1 */
  __IO uint32_t Reserved;                   /*!< (@ 0x40044030) I/O configuration for pin (Reserved) */
  __IO uint32_t PIO0_9;                     /*!< (@ 0x40044034) I/O configuration for pin PIO0_9 */
  __IO uint32_t PIO0_8;                     /*!< (@ 0x40044038) I/O configuration for pin PIO0_8 */
  __IO uint32_t PIO0_7;                     /*!< (@ 0x4004403C) I/O configuration for pin PIO0_7 */
  __IO uint32_t PIO0_6;                     /*!< (@ 0x40044040) I/O configuration for pin PIO0_6 */
  __IO uint32_t PIO0_0;                     /*!< (@ 0x40044044) I/O configuration for pin PIO0_0 */
  __IO uint32_t PIO0_14;                    /*!< (@ 0x40044048) I/O configuration for pin PIO0_14 */
} LPC_IOCON_TypeDef;
/*@}*/ /* end of group LPC8xx_IOCON */

/**
  * @brief Product name title=UM10462 Chapter title=LPC8xx Flash programming firmware Major revision=0 Minor revision=3  (FLASHCTRL)
  */
typedef struct {                            /*!< (@ 0x40040000) FLASHCTRL Structure    */
  __I  uint32_t  RESERVED0[4];
  __IO uint32_t  FLASHCFG;                          /*!< (@ 0x40040010) Flash configuration register                           */
  __I  uint32_t  RESERVED1[3];
  __IO uint32_t  FMSSTART;                          /*!< (@ 0x40040020) Signature start address register                       */
  __IO uint32_t  FMSSTOP;                           /*!< (@ 0x40040024) Signature stop-address register                        */
  __I  uint32_t  RESERVED2;
  __I  uint32_t  FMSW0;
} LPC_FLASHCTRL_TypeDef;
/*@}*/ /* end of group LPC8xx_FLASHCTRL */


/*------------- Power Management Unit (PMU) --------------------------*/
/** @addtogroup LPC8xx_PMU LPC8xx Power Management Unit
  @{
*/
typedef struct
{
  __IO uint32_t PCON;                   /*!< Offset: 0x000 Power control Register (R/W) */
  __IO uint32_t GPREG0;                 /*!< Offset: 0x004 General purpose Register 0 (R/W) */
  __IO uint32_t GPREG1;                 /*!< Offset: 0x008 General purpose Register 1 (R/W) */
  __IO uint32_t GPREG2;                 /*!< Offset: 0x00C General purpose Register 2 (R/W) */
  __IO uint32_t GPREG3;                 /*!< Offset: 0x010 General purpose Register 3 (R/W) */
  __IO uint32_t DPDCTRL;                /*!< Offset: 0x014 Deep power-down control register (R/W) */
} LPC_PMU_TypeDef;
/*@}*/ /* end of group LPC8xx_PMU */


/*------------- Switch Matrix Port --------------------------*/
/** @addtogroup LPC8xx_SWM LPC8xx Switch Matrix Port
  @{
*/
typedef struct
{
  union {
    __IO uint32_t PINASSIGN[9];
    struct {
      __IO uint32_t PINASSIGN0;
      __IO uint32_t PINASSIGN1;
      __IO uint32_t PINASSIGN2;
      __IO uint32_t PINASSIGN3;
      __IO uint32_t PINASSIGN4;
      __IO uint32_t PINASSIGN5;
      __IO uint32_t PINASSIGN6;
      __IO uint32_t PINASSIGN7;
      __IO uint32_t PINASSIGN8;
    };
  };
  __I  uint32_t  RESERVED0[103];
  __IO uint32_t  PINENABLE0;
} LPC_SWM_TypeDef;
/*@}*/ /* end of group LPC8xx_SWM */


// ------------------------------------------------------------------------------------------------
// -----                                       GPIO_PORT                                      -----
// ------------------------------------------------------------------------------------------------

/**
  * @brief Product name title=UM10462 Chapter title=LPC8xx GPIO Modification date=3/17/2011 Major revision=0 Minor revision=3  (GPIO_PORT)
  */

typedef struct {
  __IO uint8_t B0[18];                   /*!< (@ 0xA0000000) Byte pin registers port 0 */
  __I  uint16_t RESERVED0[2039];
  __IO uint32_t W0[18];                  /*!< (@ 0xA0001000) Word pin registers port 0 */
       uint32_t RESERVED1[1006];
  __IO uint32_t DIR0;                          /* 0x2000 */
       uint32_t RESERVED2[31];
  __IO uint32_t MASK0;                                  /* 0x2080 */
       uint32_t RESERVED3[31];
  __IO uint32_t PIN0;                          /* 0x2100 */
       uint32_t RESERVED4[31];
  __IO uint32_t MPIN0;                                   /* 0x2180 */
       uint32_t RESERVED5[31];
  __IO uint32_t SET0;                         /* 0x2200 */
       uint32_t RESERVED6[31];
  __O  uint32_t CLR0;                         /* 0x2280 */
       uint32_t RESERVED7[31];
  __O  uint32_t NOT0;                                    /* 0x2300 */

} LPC_GPIO_PORT_TypeDef;


// ------------------------------------------------------------------------------------------------
// -----                                     PIN_INT                                     -----
// ------------------------------------------------------------------------------------------------

/**
  * @brief Product name title=UM10462 Chapter title=LPC8xx GPIO Modification date=3/17/2011 Major revision=0 Minor revision=3  (PIN_INT)
  */

typedef struct {                            /*!< (@ 0xA0004000) PIN_INT Structure */
  __IO uint32_t ISEL;                       /*!< (@ 0xA0004000) Pin Interrupt Mode register */
  __IO uint32_t IENR;                       /*!< (@ 0xA0004004) Pin Interrupt Enable (Rising) register */
  __IO uint32_t SIENR;                      /*!< (@ 0xA0004008) Set Pin Interrupt Enable (Rising) register */
  __IO uint32_t CIENR;                      /*!< (@ 0xA000400C) Clear Pin Interrupt Enable (Rising) register */
  __IO uint32_t IENF;                       /*!< (@ 0xA0004010) Pin Interrupt Enable Falling Edge / Active Level register */
  __IO uint32_t SIENF;                      /*!< (@ 0xA0004014) Set Pin Interrupt Enable Falling Edge / Active Level register */
  __IO uint32_t CIENF;                      /*!< (@ 0xA0004018) Clear Pin Interrupt Enable Falling Edge / Active Level address */
  __IO uint32_t RISE;                       /*!< (@ 0xA000401C) Pin Interrupt Rising Edge register */
  __IO uint32_t FALL;                       /*!< (@ 0xA0004020) Pin Interrupt Falling Edge register */
  __IO uint32_t IST;                        /*!< (@ 0xA0004024) Pin Interrupt Status register */
  __IO uint32_t PMCTRL;                     /*!< (@ 0xA0004028) GPIO pattern match interrupt control register          */
  __IO uint32_t PMSRC;                      /*!< (@ 0xA000402C) GPIO pattern match interrupt bit-slice source register */
  __IO uint32_t PMCFG;                      /*!< (@ 0xA0004030) GPIO pattern match interrupt bit slice configuration register */
} LPC_PIN_INT_TypeDef;


/*------------- CRC Engine (CRC) -----------------------------------------*/
/** @addtogroup LPC8xx_CRC
  @{
*/
typedef struct
{
  __IO uint32_t MODE;
  __IO uint32_t SEED;
  union {
  __I  uint32_t SUM;
  __O  uint32_t WR_DATA_DWORD;
  __O  uint16_t WR_DATA_WORD;
       uint16_t RESERVED_WORD;
  __O  uint8_t WR_DATA_BYTE;
       uint8_t RESERVED_BYTE[3];
  };
} LPC_CRC_TypeDef;
/*@}*/ /* end of group LPC8xx_CRC */

/*------------- Comparator (CMP) --------------------------------------------------*/
/** @addtogroup LPC8xx_CMP LPC8xx Comparator
  @{
*/
typedef struct {                            /*!< (@ 0x40024000) CMP Structure          */
  __IO uint32_t  CTRL;                      /*!< (@ 0x40024000) Comparator control register */
  __IO uint32_t  LAD;                       /*!< (@ 0x40024004) Voltage ladder register */
} LPC_CMP_TypeDef;
/*@}*/ /* end of group LPC8xx_CMP */


/*------------- Wakeup Timer (WKT) --------------------------------------------------*/
/** @addtogroup LPC8xx_WKT
  @{
*/
typedef struct {                            /*!< (@ 0x40028000) WKT Structure          */
  __IO uint32_t  CTRL;                      /*!< (@ 0x40028000) Alarm/Wakeup Timer Control register */
       uint32_t  Reserved[2];
  __IO uint32_t  COUNT;                     /*!< (@ 0x4002800C) Alarm/Wakeup TImer counter register */
} LPC_WKT_TypeDef;
/*@}*/ /* end of group LPC8xx_WKT */

/*------------- Multi-Rate Timer(MRT) --------------------------------------------------*/
//New, Copied from lpc824
/**
  * @brief Multi-Rate Timer (MRT) (MRT)
  */
typedef struct {                                    /*!< (@ 0x40004000) MRT Structure                                          */
  __IO uint32_t  INTVAL0;                           /*!< (@ 0x40004000) MRT0 Time interval value register. This value
                                                         is loaded into the TIMER0 register.                                   */
  __I  uint32_t  TIMER0;                            /*!< (@ 0x40004004) MRT0 Timer register. This register reads the
                                                         value of the down-counter.                                            */
  __IO uint32_t  CTRL0;                             /*!< (@ 0x40004008) MRT0 Control register. This register controls
                                                         the MRT0 modes.                                                       */
  __IO uint32_t  STAT0;                             /*!< (@ 0x4000400C) MRT0 Status register.                                  */
  __IO uint32_t  INTVAL1;                           /*!< (@ 0x40004010) MRT0 Time interval value register. This value
                                                         is loaded into the TIMER0 register.                                   */
  __I  uint32_t  TIMER1;                            /*!< (@ 0x40004014) MRT0 Timer register. This register reads the
                                                         value of the down-counter.                                            */
  __IO uint32_t  CTRL1;                             /*!< (@ 0x40004018) MRT0 Control register. This register controls
                                                         the MRT0 modes.                                                       */
  __IO uint32_t  STAT1;                             /*!< (@ 0x4000401C) MRT0 Status register.                                  */
  __IO uint32_t  INTVAL2;                           /*!< (@ 0x40004020) MRT0 Time interval value register. This value
                                                         is loaded into the TIMER0 register.                                   */
  __I  uint32_t  TIMER2;                            /*!< (@ 0x40004024) MRT0 Timer register. This register reads the
                                                         value of the down-counter.                                            */
  __IO uint32_t  CTRL2;                             /*!< (@ 0x40004028) MRT0 Control register. This register controls
                                                         the MRT0 modes.                                                       */
  __IO uint32_t  STAT2;                             /*!< (@ 0x4000402C) MRT0 Status register.                                  */
  __IO uint32_t  INTVAL3;                           /*!< (@ 0x40004030) MRT0 Time interval value register. This value
                                                         is loaded into the TIMER0 register.                                   */
  __I  uint32_t  TIMER3;                            /*!< (@ 0x40004034) MRT0 Timer register. This register reads the
                                                         value of the down-counter.                                            */
  __IO uint32_t  CTRL3;                             /*!< (@ 0x40004038) MRT0 Control register. This register controls
                                                         the MRT0 modes.                                                       */
  __IO uint32_t  STAT3;                             /*!< (@ 0x4000403C) MRT0 Status register.                                  */
  __I  uint32_t  RESERVED0[45];
  __I  uint32_t  IDLE_CH;                           /*!< (@ 0x400040F4) Idle channel register. This register returns
                                                         the number of the first idle channel.                                 */
  __IO uint32_t  IRQ_FLAG;                          /*!< (@ 0x400040F8) Global interrupt flag register                         */
} LPC_MRT_TypeDef;

/*------------- Universal Asynchronous Receiver Transmitter (USART) -----------*/
/** @addtogroup LPC8xx_UART LPC8xx Universal Asynchronous Receiver/Transmitter
  @{
*/
/**
  * @brief Product name title=LPC8xx MCU Chapter title=USART Modification date=4/18/2012 Major revision=0 Minor revision=9  (USART)
  */
typedef struct
{
  __IO uint32_t  CFG;								/* 0x00 */
  __IO uint32_t  CTRL;
  __IO uint32_t  STAT;
  __IO uint32_t  INTENSET;
  __O  uint32_t  INTENCLR;					/* 0x10 */
  __I  uint32_t  RXDATA;
  __I  uint32_t  RXDATA_STAT;
  __IO uint32_t  TXDATA;
  __IO uint32_t  BRG;								/* 0x20 */
  __IO uint32_t  INTSTAT;
} LPC_USART_TypeDef;

/*@}*/ /* end of group LPC8xx_USART */


/*------------- Synchronous Serial Interface Controller (SPI) -----------------------*/
/** @addtogroup LPC8xx_SPI LPC8xx Synchronous Serial Port
  @{
*/
typedef struct
{
  __IO uint32_t  CFG;			    /* 0x00 */
  __IO uint32_t  DLY;
  __IO uint32_t  STAT;
  __IO uint32_t  INTENSET;
  __O  uint32_t  INTENCLR;		/* 0x10 */
  __I  uint32_t  RXDAT;
  __IO uint32_t  TXDATCTL;
  __IO uint32_t  TXDAT;
  __IO uint32_t  TXCTRL;		  /* 0x20 */
  __IO uint32_t  DIV;
  __I  uint32_t  INTSTAT;
} LPC_SPI_TypeDef;
/*@}*/ /* end of group LPC8xx_SPI */


/*------------- Inter-Integrated Circuit (I2C) -------------------------------*/
/** @addtogroup LPC8xx_I2C I2C-Bus Interface
  @{
*/
typedef struct
{
  __IO uint32_t  CFG;			  /* 0x00 */
  __IO uint32_t  STAT;
  __IO uint32_t  INTENSET;
  __O  uint32_t  INTENCLR;
  __IO uint32_t  TIMEOUT;		/* 0x10 */
  __IO uint32_t  DIV;
  __IO uint32_t  INTSTAT;
       uint32_t  Reserved0[1];
  __IO uint32_t  MSTCTL;			  /* 0x20 */
  __IO uint32_t  MSTTIME;
  __IO uint32_t  MSTDAT;
       uint32_t  Reserved1[5];
  __IO uint32_t  SLVCTL;			  /* 0x40 */
  __IO uint32_t  SLVDAT;
  __IO uint32_t  SLVADR0;
  __IO uint32_t  SLVADR1;
  __IO uint32_t  SLVADR2;			  /* 0x50 */
  __IO uint32_t  SLVADR3;
  __IO uint32_t  SLVQUAL0;
       uint32_t  Reserved2[9];
  __I  uint32_t  MONRXDAT;			/* 0x80 */
} LPC_I2C_TypeDef;

/*@}*/ /* end of group LPC8xx_I2C */

/**
  * @brief State Configurable Timer (SCT) (SCT)
  */

/**
  * @brief Product name title=UM10430 Chapter title=LPC8xx State Configurable Timer (SCT) Modification date=1/18/2011 Major revision=0 Minor revision=7  (SCT)
  */

#define CONFIG_SCT_nEV   (6)             /* Number of events */
#define CONFIG_SCT_nRG   (5)             /* Number of match/compare registers */
#define CONFIG_SCT_nOU   (4)             /* Number of outputs */

typedef struct
{
    __IO  uint32_t CONFIG;              /* 0x000 Configuration Register */
    union {
        __IO uint32_t CTRL_U;           /* 0x004 Control Register */
        struct {
            __IO uint16_t CTRL_L;       /* 0x004 low control register */
            __IO uint16_t CTRL_H;       /* 0x006 high control register */
        };
    };
    __IO uint16_t LIMIT_L;              /* 0x008 limit register for counter L */
    __IO uint16_t LIMIT_H;              /* 0x00A limit register for counter H */
    __IO uint16_t HALT_L;               /* 0x00C halt register for counter L */
    __IO uint16_t HALT_H;               /* 0x00E halt register for counter H */
    __IO uint16_t STOP_L;               /* 0x010 stop register for counter L */
    __IO uint16_t STOP_H;               /* 0x012 stop register for counter H */
    __IO uint16_t START_L;              /* 0x014 start register for counter L */
    __IO uint16_t START_H;              /* 0x016 start register for counter H */
         uint32_t RESERVED1[10];        /* 0x018-0x03C reserved */
    union {
        __IO uint32_t COUNT_U;          /* 0x040 counter register */
        struct {
            __IO uint16_t COUNT_L;      /* 0x040 counter register for counter L */
            __IO uint16_t COUNT_H;      /* 0x042 counter register for counter H */
        };
    };
    __IO uint16_t STATE_L;              /* 0x044 state register for counter L */
    __IO uint16_t STATE_H;              /* 0x046 state register for counter H */
    __I  uint32_t INPUT;                /* 0x048 input register */
    __IO uint16_t REGMODE_L;            /* 0x04C match - capture registers mode register L */
    __IO uint16_t REGMODE_H;            /* 0x04E match - capture registers mode register H */
    __IO uint32_t OUTPUT;               /* 0x050 output register */
    __IO uint32_t OUTPUTDIRCTRL;        /* 0x054 Output counter direction Control Register */
    __IO uint32_t RES;                  /* 0x058 conflict resolution register */
         uint32_t RESERVED2[37];        /* 0x05C-0x0EC reserved */
    __IO uint32_t EVEN;                 /* 0x0F0 event enable register */
    __IO uint32_t EVFLAG;               /* 0x0F4 event flag register */
    __IO uint32_t CONEN;                /* 0x0F8 conflict enable register */
    __IO uint32_t CONFLAG;              /* 0x0FC conflict flag register */

    union {
        __IO union {                    /* 0x100-... Match / Capture value */
            uint32_t U;                 /*       SCTMATCH[i].U  Unified 32-bit register */
            struct {
                uint16_t L;             /*       SCTMATCH[i].L  Access to L value */
                uint16_t H;             /*       SCTMATCH[i].H  Access to H value */
            };
        } MATCH[CONFIG_SCT_nRG];
        __I union {
            uint32_t U;                 /*       SCTCAP[i].U  Unified 32-bit register */
            struct {
                uint16_t L;             /*       SCTCAP[i].L  Access to H value */
                uint16_t H;             /*       SCTCAP[i].H  Access to H value */
            };
        } CAP[CONFIG_SCT_nRG];
    };


         uint32_t RESERVED3[32-CONFIG_SCT_nRG];      /* ...-0x17C reserved */

    union {
        __IO uint16_t MATCH_L[CONFIG_SCT_nRG];       /* 0x180-... Match Value L counter */
        __I  uint16_t CAP_L[CONFIG_SCT_nRG];         /* 0x180-... Capture Value L counter */
    };
         uint16_t RESERVED4[32-CONFIG_SCT_nRG];      /* ...-0x1BE reserved */
    union {
        __IO uint16_t MATCH_H[CONFIG_SCT_nRG];       /* 0x1C0-... Match Value H counter */
        __I  uint16_t CAP_H[CONFIG_SCT_nRG];         /* 0x1C0-... Capture Value H counter */
    };

         uint16_t RESERVED5[32-CONFIG_SCT_nRG];      /* ...-0x1FE reserved */


    union {
        __IO union {                    /* 0x200-... Match Reload / Capture Control value */
            uint32_t U;                 /*       SCTMATCHREL[i].U  Unified 32-bit register */
            struct {
                uint16_t L;             /*       SCTMATCHREL[i].L  Access to L value */
                uint16_t H;             /*       SCTMATCHREL[i].H  Access to H value */
            };
        } MATCHREL[CONFIG_SCT_nRG];
        __IO union {
            uint32_t U;                 /*       SCTCAPCTRL[i].U  Unified 32-bit register */
            struct {
                uint16_t L;             /*       SCTCAPCTRL[i].L  Access to H value */
                uint16_t H;             /*       SCTCAPCTRL[i].H  Access to H value */
            };
        } CAPCTRL[CONFIG_SCT_nRG];
    };

         uint32_t RESERVED6[32-CONFIG_SCT_nRG];      /* ...-0x27C reserved */

    union {
        __IO uint16_t MATCHREL_L[CONFIG_SCT_nRG];    /* 0x280-... Match Reload value L counter */
        __IO uint16_t CAPCTRL_L[CONFIG_SCT_nRG];     /* 0x280-... Capture Control value L counter */
    };
         uint16_t RESERVED7[32-CONFIG_SCT_nRG];      /* ...-0x2BE reserved */
    union {
        __IO uint16_t MATCHREL_H[CONFIG_SCT_nRG];    /* 0x2C0-... Match Reload value H counter */
        __IO uint16_t CAPCTRL_H[CONFIG_SCT_nRG];     /* 0x2C0-... Capture Control value H counter */
    };
         uint16_t RESERVED8[32-CONFIG_SCT_nRG];      /* ...-0x2FE reserved */

    __IO struct {                       /* 0x300-0x3FC  SCTEVENT[i].STATE / SCTEVENT[i].CTRL*/
        uint32_t STATE;                 /* Event State Register */
        uint32_t CTRL;                  /* Event Control Register */
    } EVENT[CONFIG_SCT_nEV];

         uint32_t RESERVED9[128-2*CONFIG_SCT_nEV];   /* ...-0x4FC reserved */

    __IO struct {                       /* 0x500-0x57C  SCTOUT[i].SET / SCTOUT[i].CLR */
        uint32_t SET;                   /* Output n Set Register */
        uint32_t CLR;                   /* Output n Clear Register */
    } OUT[CONFIG_SCT_nOU];

         uint32_t RESERVED10[191-2*CONFIG_SCT_nOU];  /* ...-0x7F8 reserved */

    __I  uint32_t MODULECONTENT;        /* 0x7FC Module Content */

} LPC_SCT_TypeDef;
/*@}*/ /* end of group LPC8xx_SCT */


/*------------- Watchdog Timer (WWDT) -----------------------------------------*/
/** @addtogroup LPC8xx_WDT LPC8xx WatchDog Timer
  @{
*/
typedef struct
{
  __IO uint32_t MOD;                    /*!< Offset: 0x000 Watchdog mode register (R/W) */
  __IO uint32_t TC;                     /*!< Offset: 0x004 Watchdog timer constant register (R/W) */
  __O  uint32_t FEED;                   /*!< Offset: 0x008 Watchdog feed sequence register (W) */
  __I  uint32_t TV;                     /*!< Offset: 0x00C Watchdog timer value register (R) */
       uint32_t RESERVED;               /*!< Offset: 0x010 RESERVED                          */
  __IO uint32_t WARNINT;                /*!< Offset: 0x014 Watchdog timer warning int. register (R/W) */
  __IO uint32_t WINDOW;                 /*!< Offset: 0x018 Watchdog timer window value register (R/W) */
} LPC_WWDT_TypeDef;
/*@}*/ /* end of group LPC8xx_WDT */


#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/* Base addresses                                                             */
#define LPC_FLASH_BASE        (0x00000000UL)
#define LPC_RAM_BASE          (0x10000000UL)
#define LPC_ROM_BASE          (0x1FFF0000UL)
#define LPC_APB0_BASE         (0x40000000UL)
#define LPC_AHB_BASE          (0x50000000UL)

/* APB0 peripherals */
#define LPC_WWDT_BASE         (LPC_APB0_BASE + 0x00000)
#define LPC_MRT_BASE          (LPC_APB0_BASE + 0x04000)
#define LPC_WKT_BASE          (LPC_APB0_BASE + 0x08000)
#define LPC_SWM_BASE          (LPC_APB0_BASE + 0x0C000)
#define LPC_PMU_BASE          (LPC_APB0_BASE + 0x20000)
#define LPC_CMP_BASE          (LPC_APB0_BASE + 0x24000)

#define LPC_FLASHCTRL_BASE    (LPC_APB0_BASE + 0x40000)
#define LPC_IOCON_BASE        (LPC_APB0_BASE + 0x44000)
#define LPC_SYSCON_BASE       (LPC_APB0_BASE + 0x48000)
#define LPC_I2C_BASE          (LPC_APB0_BASE + 0x50000)
#define LPC_SPI0_BASE         (LPC_APB0_BASE + 0x58000)
#define LPC_SPI1_BASE         (LPC_APB0_BASE + 0x5C000)
#define LPC_USART0_BASE       (LPC_APB0_BASE + 0x64000)
#define LPC_USART1_BASE       (LPC_APB0_BASE + 0x68000)
#define LPC_USART2_BASE       (LPC_APB0_BASE + 0x6C000)

/* AHB peripherals                                                            */
#define LPC_CRC_BASE         (LPC_AHB_BASE + 0x00000)
#define LPC_SCT_BASE         (LPC_AHB_BASE + 0x04000)

#define LPC_GPIO_PORT_BASE    (0xA0000000)
#define LPC_PIN_INT_BASE     (LPC_GPIO_PORT_BASE  + 0x4000)

/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/
#define LPC_WWDT              ((LPC_WWDT_TypeDef   *) LPC_WWDT_BASE  )
#define LPC_MRT               ((LPC_MRT_TypeDef    *) LPC_MRT_BASE   )


#define LPC_WKT               ((LPC_WKT_TypeDef    *) LPC_WKT_BASE   )
#define LPC_SWM               ((LPC_SWM_TypeDef    *) LPC_SWM_BASE   )
#define LPC_PMU               ((LPC_PMU_TypeDef    *) LPC_PMU_BASE   )
#define LPC_CMP               ((LPC_CMP_TypeDef    *) LPC_CMP_BASE   )

#define LPC_FLASHCTRL         ((LPC_FLASHCTRL_TypeDef *) LPC_FLASHCTRL_BASE )
#define LPC_IOCON             ((LPC_IOCON_TypeDef  *) LPC_IOCON_BASE )
#define LPC_SYSCON            ((LPC_SYSCON_TypeDef *) LPC_SYSCON_BASE)
#define LPC_I2C               ((LPC_I2C_TypeDef    *) LPC_I2C_BASE   )
#define LPC_SPI0              ((LPC_SPI_TypeDef    *) LPC_SPI0_BASE  )
#define LPC_SPI1              ((LPC_SPI_TypeDef    *) LPC_SPI1_BASE  )
#define LPC_USART0            ((LPC_USART_TypeDef   *) LPC_USART0_BASE )
#define LPC_USART1            ((LPC_USART_TypeDef   *) LPC_USART1_BASE )
#define LPC_USART2            ((LPC_USART_TypeDef   *) LPC_USART2_BASE )

#define LPC_CRC               ((LPC_CRC_TypeDef    *) LPC_CRC_BASE   )
#define LPC_SCT               ((LPC_SCT_TypeDef    *) LPC_SCT_BASE   )

#define LPC_GPIO_PORT         ((LPC_GPIO_PORT_TypeDef  *) LPC_GPIO_PORT_BASE  )
#define LPC_PIN_INT          ((LPC_PIN_INT_TypeDef   *) LPC_PIN_INT_BASE  )

#ifdef __cplusplus
}
#endif

#endif  /* __LPC8xx_H__ */
