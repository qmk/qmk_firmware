/****************************************************************************
 *   $Id:: LPC11xx.h 9198 2012-05-29 usb00175                     $
 *   Project: NXP LPC11xx software example  
 *
 *   Description:
 *     CMSIS Cortex-M0 Core Peripheral Access Layer Header File for 
 *     NXP LPC11xx Device Series 
 
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
* is used in conjunction with NXP Semiconductors microcontrollers.  This 
* copyright, permission, and disclaimer notice must appear in all copies of 
* this code.

****************************************************************************/
#ifndef __LPC11xx_H__
#define __LPC11xx_H__

#ifdef __cplusplus
 extern "C" {
#endif 

/** @addtogroup LPC11xx_Definitions LPC11xx Definitions
  This file defines all structures and symbols for LPC11xx:
    - Registers and bitfields
    - peripheral base address
    - peripheral ID
    - PIO definitions
  @{
*/


/******************************************************************************/
/*                Processor and Core Peripherals                              */
/******************************************************************************/
/** @addtogroup LPC11xx_CMSIS LPC11xx CMSIS Definitions
  Configuration of the Cortex-M0 Processor and Core Peripherals
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
  NonMaskableInt_IRQn           = -14,    /*!< 2 Non Maskable Interrupt                           */
  HardFault_IRQn                = -13,    /*!< 3 Cortex-M0 Hard Fault Interrupt                   */
  SVCall_IRQn                   = -5,     /*!< 11 Cortex-M0 SV Call Interrupt                     */
  PendSV_IRQn                   = -2,     /*!< 14 Cortex-M0 Pend SV Interrupt                     */
  SysTick_IRQn                  = -1,     /*!< 15 Cortex-M0 System Tick Interrupt                 */

/******  LPC11Cxx or LPC11xx Specific Interrupt Numbers *******************************************************/
  WAKEUP0_IRQn                  = 0,        /*!< All I/O pins can be used as wakeup source.       */
  WAKEUP1_IRQn                  = 1,        /*!< There are 13 pins in total for LPC11xx           */
  WAKEUP2_IRQn                  = 2,
  WAKEUP3_IRQn                  = 3,
  WAKEUP4_IRQn                  = 4,   
  WAKEUP5_IRQn                  = 5,        
  WAKEUP6_IRQn                  = 6,        
  WAKEUP7_IRQn                  = 7,        
  WAKEUP8_IRQn                  = 8,        
  WAKEUP9_IRQn                  = 9,        
  WAKEUP10_IRQn                 = 10,       
  WAKEUP11_IRQn                 = 11,       
  WAKEUP12_IRQn                 = 12,       
  CAN_IRQn                      = 13,       /*!< CAN Interrupt                                    */
  SSP1_IRQn                     = 14,       /*!< SSP1 Interrupt                                   */
  I2C_IRQn                      = 15,       /*!< I2C Interrupt                                    */
  TIMER_16_0_IRQn               = 16,       /*!< 16-bit Timer0 Interrupt                          */
  TIMER_16_1_IRQn               = 17,       /*!< 16-bit Timer1 Interrupt                          */
  TIMER_32_0_IRQn               = 18,       /*!< 32-bit Timer0 Interrupt                          */
  TIMER_32_1_IRQn               = 19,       /*!< 32-bit Timer1 Interrupt                          */
  SSP0_IRQn                     = 20,       /*!< SSP0 Interrupt                                   */
  UART_IRQn                     = 21,       /*!< UART Interrupt                                   */
  Reserved0_IRQn                = 22,       /*!< Reserved Interrupt                               */
  Reserved1_IRQn                = 23,       
  ADC_IRQn                      = 24,       /*!< A/D Converter Interrupt                          */
  WDT_IRQn                      = 25,       /*!< Watchdog timer Interrupt                         */  
  BOD_IRQn                      = 26,       /*!< Brown Out Detect(BOD) Interrupt                  */
  FMC_IRQn                      = 27,       /*!< Flash Memory Controller Interrupt                */
  EINT3_IRQn                    = 28,       /*!< External Interrupt 3 Interrupt                   */
  EINT2_IRQn                    = 29,       /*!< External Interrupt 2 Interrupt                   */
  EINT1_IRQn                    = 30,       /*!< External Interrupt 1 Interrupt                   */
  EINT0_IRQn                    = 31,       /*!< External Interrupt 0 Interrupt                   */
} IRQn_Type;

/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M0 Processor and Core Peripherals */
#define __MPU_PRESENT             0         /*!< MPU present or not                               */
#define __NVIC_PRIO_BITS          2         /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used     */

/*@}*/ /* end of group LPC11xx_CMSIS */


#include "core_cm0.h"                       /* Cortex-M0 processor and core peripherals           */
#include "system_LPC11xx.h"                 /* System Header                                      */


/******************************************************************************/
/*                Device Specific Peripheral Registers structures             */
/******************************************************************************/

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/*------------- System Control (SYSCON) --------------------------------------*/
/** @addtogroup LPC11xx_SYSCON LPC11xx System Control Block 
  @{
*/
typedef struct
{
  __IO uint32_t SYSMEMREMAP;            /*!< Offset: 0x000 System memory remap (R/W) */
  __IO uint32_t PRESETCTRL;             /*!< Offset: 0x004 Peripheral reset control (R/W) */
  __IO uint32_t SYSPLLCTRL;             /*!< Offset: 0x008 System PLL control (R/W) */
  __I uint32_t SYSPLLSTAT;             /*!< Offset: 0x00C System PLL status (R/ ) */
       uint32_t RESERVED0[4];

  __IO uint32_t SYSOSCCTRL;             /*!< Offset: 0x020 System oscillator control (R/W) */
  __IO uint32_t WDTOSCCTRL;             /*!< Offset: 0x024 Watchdog oscillator control (R/W) */
  __IO uint32_t IRCCTRL;                /*!< Offset: 0x028 IRC control (R/W) */
       uint32_t RESERVED1[1];
  __IO uint32_t SYSRSTSTAT;             /*!< Offset: 0x030 System reset status Register (R/ ) */
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
  __IO uint32_t SSP0CLKDIV;             /*!< Offset: 0x094 SSP0 clock divider (R/W) */          
  __IO uint32_t UARTCLKDIV;             /*!< Offset: 0x098 UART clock divider (R/W) */
  __IO uint32_t SSP1CLKDIV;             /*!< Offset: 0x09C SSP1 clock divider (R/W) */          
       uint32_t RESERVED6[12];

  __IO uint32_t WDTCLKSEL;              /*!< Offset: 0x0D0 WDT clock source select (R/W) */
  __IO uint32_t WDTCLKUEN;              /*!< Offset: 0x0D4 WDT clock source update enable (R/W) */
  __IO uint32_t WDTCLKDIV;              /*!< Offset: 0x0D8 WDT clock divider (R/W) */
       uint32_t RESERVED8[1];              
  __IO uint32_t CLKOUTCLKSEL;           /*!< Offset: 0x0E0 CLKOUT clock source select (R/W) */
  __IO uint32_t CLKOUTUEN;              /*!< Offset: 0x0E4 CLKOUT clock source update enable (R/W) */
  __IO uint32_t CLKOUTDIV;              /*!< Offset: 0x0E8 CLKOUT clock divider (R/W) */       
       uint32_t RESERVED9[5];
  
  __IO uint32_t PIOPORCAP0;             /*!< Offset: 0x100 POR captured PIO status 0 (R/ ) */           
  __IO uint32_t PIOPORCAP1;             /*!< Offset: 0x104 POR captured PIO status 1 (R/ ) */   
       uint32_t RESERVED10[18];
  __IO uint32_t BODCTRL;                /*!< Offset: 0x150 BOD control (R/W) */
  __IO uint32_t SYSTCKCAL;              /*!< Offset: 0x154 System tick counter calibration (R/W) */
       
       uint32_t RESERVED13[7];
  __IO uint32_t NMISRC;                 /*!< Offset: 0x174 NMI source selection register (R/W) */
       uint32_t RESERVED14[34];
       
  __IO uint32_t STARTAPRP0;             /*!< Offset: 0x200 Start logic edge control Register 0 (R/W) */     
  __IO uint32_t STARTERP0;              /*!< Offset: 0x204 Start logic signal enable Register 0 (R/W) */      
  __O  uint32_t STARTRSRP0CLR;          /*!< Offset: 0x208 Start logic reset Register 0  ( /W) */
  __I uint32_t STARTSRP0;              /*!< Offset: 0x20C Start logic status Register 0 (R/) */
  __IO uint32_t STARTAPRP1;             /*!< Offset: 0x210 Start logic edge control Register 0 (R/W). (LPC11UXX only) */     
  __IO uint32_t STARTERP1;              /*!< Offset: 0x214 Start logic signal enable Register 0 (R/W). (LPC11UXX only) */      
  __O  uint32_t STARTRSRP1CLR;          /*!< Offset: 0x218 Start logic reset Register 0  ( /W). (LPC11UXX only) */
  __IO uint32_t STARTSRP1;              /*!< Offset: 0x21C Start logic status Register 0 (R/W). (LPC11UXX only) */
       uint32_t RESERVED17[4];

  __IO uint32_t PDSLEEPCFG;             /*!< Offset: 0x230 Power-down states in Deep-sleep mode (R/W) */
  __IO uint32_t PDAWAKECFG;             /*!< Offset: 0x234 Power-down states after wake-up (R/W) */        
  __IO uint32_t PDRUNCFG;               /*!< Offset: 0x238 Power-down configuration Register (R/W) */
       uint32_t RESERVED15[110];
  __I  uint32_t DEVICE_ID;              /*!< Offset: 0x3F4 Device ID (R/ ) */
} LPC_SYSCON_TypeDef;
/*@}*/ /* end of group LPC11xx_SYSCON */


/*------------- Pin Connect Block (IOCON) --------------------------------*/
/** @addtogroup LPC11xx_IOCON LPC11xx I/O Configuration Block 
  @{
*/
typedef struct
{
  __IO uint32_t PIO2_6;                 /*!< Offset: 0x000 I/O configuration for pin PIO2_6 (R/W) */
       uint32_t RESERVED0[1];
  __IO uint32_t PIO2_0;                 /*!< Offset: 0x008 I/O configuration for pin PIO2_0/DTR/SSEL1 (R/W) */
  __IO uint32_t RESET_PIO0_0;           /*!< Offset: 0x00C I/O configuration for pin RESET/PIO0_0  (R/W) */
  __IO uint32_t PIO0_1;                 /*!< Offset: 0x010 I/O configuration for pin PIO0_1/CLKOUT/CT32B0_MAT2 (R/W) */
  __IO uint32_t PIO1_8;                 /*!< Offset: 0x014 I/O configuration for pin PIO1_8/CT16B1_CAP0 (R/W) */
  __IO uint32_t SSEL1_LOC;              /*!< Offset: 0x018 IOCON SSEL1 location register (IOCON_SSEL1_LOC, address 0x4004 4018) */
  __IO uint32_t PIO0_2;                 /*!< Offset: 0x01C I/O configuration for pin PIO0_2/SSEL0/CT16B0_CAP0 (R/W) */

  __IO uint32_t PIO2_7;                 /*!< Offset: 0x020 I/O configuration for pin PIO2_7 (R/W) */
  __IO uint32_t PIO2_8;                 /*!< Offset: 0x024 I/O configuration for pin PIO2_8 (R/W) */
  __IO uint32_t PIO2_1;                 /*!< Offset: 0x028 I/O configuration for pin PIO2_1/nDSR/SCK1 (R/W) */
  __IO uint32_t PIO0_3;                 /*!< Offset: 0x02C I/O configuration for pin PIO0_3 (R/W) */
  __IO uint32_t PIO0_4;                 /*!< Offset: 0x030 I/O configuration for pin PIO0_4/SCL (R/W) */
  __IO uint32_t PIO0_5;                 /*!< Offset: 0x034 I/O configuration for pin PIO0_5/SDA (R/W) */
  __IO uint32_t PIO1_9;                 /*!< Offset: 0x038 I/O configuration for pin PIO1_9/CT16B1_MAT0 (R/W) */
  __IO uint32_t PIO3_4;                 /*!< Offset: 0x03C I/O configuration for pin PIO3_4 (R/W) */

  __IO uint32_t PIO2_4;                 /*!< Offset: 0x040 I/O configuration for pin PIO2_4 (R/W) */
  __IO uint32_t PIO2_5;                 /*!< Offset: 0x044 I/O configuration for pin PIO2_5 (R/W) */
  __IO uint32_t PIO3_5;                 /*!< Offset: 0x048 I/O configuration for pin PIO3_5 (R/W) */
  __IO uint32_t PIO0_6;                 /*!< Offset: 0x04C I/O configuration for pin PIO0_6/SCK0 (R/W) */
  __IO uint32_t PIO0_7;                 /*!< Offset: 0x050 I/O configuration for pin PIO0_7/nCTS (R/W) */
  __IO uint32_t PIO2_9;                 /*!< Offset: 0x054 I/O configuration for pin PIO2_9 (R/W) */
  __IO uint32_t PIO2_10;                /*!< Offset: 0x058 I/O configuration for pin PIO2_10 (R/W) */
  __IO uint32_t PIO2_2;                 /*!< Offset: 0x05C I/O configuration for pin PIO2_2/DCD/MISO1 (R/W) */

  __IO uint32_t PIO0_8;                 /*!< Offset: 0x060 I/O configuration for pin PIO0_8/MISO0/CT16B0_MAT0 (R/W) */
  __IO uint32_t PIO0_9;                 /*!< Offset: 0x064 I/O configuration for pin PIO0_9/MOSI0/CT16B0_MAT1 (R/W) */
  __IO uint32_t SWCLK_PIO0_10;          /*!< Offset: 0x068 I/O configuration for pin SWCLK/PIO0_10/SCK0/CT16B0_MAT2 (R/W) */
  __IO uint32_t PIO1_10;                /*!< Offset: 0x06C I/O configuration for pin PIO1_10/AD6/CT16B1_MAT1 (R/W) */
  __IO uint32_t PIO2_11;                /*!< Offset: 0x070 I/O configuration for pin PIO2_11/SCK0 (R/W) */
  __IO uint32_t R_PIO0_11;              /*!< Offset: 0x074 I/O configuration for pin TDI/PIO0_11/AD0/CT32B0_MAT3 (R/W) */
  __IO uint32_t R_PIO1_0;               /*!< Offset: 0x078 I/O configuration for pin TMS/PIO1_0/AD1/CT32B1_CAP0 (R/W) */
  __IO uint32_t R_PIO1_1;               /*!< Offset: 0x07C I/O configuration for pin TDO/PIO1_1/AD2/CT32B1_MAT0 (R/W) */

  __IO uint32_t R_PIO1_2;               /*!< Offset: 0x080 I/O configuration for pin nTRST/PIO1_2/AD3/CT32B1_MAT1 (R/W) */
  __IO uint32_t PIO3_0;                 /*!< Offset: 0x084 I/O configuration for pin PIO3_0/nDTR (R/W) */
  __IO uint32_t PIO3_1;                 /*!< Offset: 0x088 I/O configuration for pin PIO3_1/nDSR (R/W) */
  __IO uint32_t PIO2_3;                 /*!< Offset: 0x08C I/O configuration for pin PIO2_3/RI/MOSI1 (R/W) */
  __IO uint32_t SWDIO_PIO1_3;           /*!< Offset: 0x090 I/O configuration for pin SWDIO/PIO1_3/AD4/CT32B1_MAT2 (R/W) */
  __IO uint32_t PIO1_4;                 /*!< Offset: 0x094 I/O configuration for pin PIO1_4/AD5/CT32B1_MAT3 (R/W) */
  __IO uint32_t PIO1_11;                /*!< Offset: 0x098 I/O configuration for pin PIO1_11/AD7 (R/W) */
  __IO uint32_t PIO3_2;                 /*!< Offset: 0x09C I/O configuration for pin PIO3_2/nDCD (R/W) */

  __IO uint32_t PIO1_5;                 /*!< Offset: 0x0A0 I/O configuration for pin PIO1_5/nRTS/CT32B0_CAP0 (R/W) */
  __IO uint32_t PIO1_6;                 /*!< Offset: 0x0A4 I/O configuration for pin PIO1_6/RXD/CT32B0_MAT0 (R/W) */
  __IO uint32_t PIO1_7;                 /*!< Offset: 0x0A8 I/O configuration for pin PIO1_7/TXD/CT32B0_MAT1 (R/W) */
  __IO uint32_t PIO3_3;                 /*!< Offset: 0x0AC I/O configuration for pin PIO3_3/nRI (R/W) */
  __IO uint32_t SCK_LOC;                /*!< Offset: 0x0B0 SCK pin location select Register (R/W) */
  __IO uint32_t DSR_LOC;                /*!< Offset: 0x0B4 DSR pin location select Register (R/W) */
  __IO uint32_t DCD_LOC;                /*!< Offset: 0x0B8 DCD pin location select Register (R/W) */
  __IO uint32_t RI_LOC;                 /*!< Offset: 0x0BC RI pin location Register (R/W) */

  __IO uint32_t CT16B0_CAP0_LOC;        /*!< Offset: 0x0C0 IOCON CT16B0_CAP0 location register (IOCON_CT16B0_CAP0_LOC, address 0x4004 40C0) */
  __IO uint32_t SCK1_LOC;               /*!< Offset: 0x0C4 IOCON SCK1 location register (IOCON_SCK1_LOC, address 0x4004 40C4) */
  __IO uint32_t MISO1_LOC;              /*!< Offset: 0x0C8 IOCON MISO1 location register (IOCON_MISO1_LOC, address 0x4004 40C8) */
  __IO uint32_t MOSI1_LOC;              /*!< Offset: 0x0CC IOCON MOSI1 location register (IOCON_MOSI1_LOC, address 0x4004 40CC) */
  __IO uint32_t CT32B0_CAP0_LOC;        /*!< Offset: 0x0D0 IOCON CT32B0_CAP0 location register (IOCON_CT32B0_CAP0_LOC, address 0x4004 40D0) */
  __IO uint32_t RXD_LOC;                /*!< Offset: 0x0D4 IOCON RXD location register (IOCON_RXD_LOC, address 0x4004 40D4) */
} LPC_IOCON_TypeDef;
/*@}*/ /* end of group LPC11xx_IOCON */


/*------------- Power Management Unit (PMU) --------------------------*/
/** @addtogroup LPC11xx_PMU LPC11xx Power Management Unit 
  @{
*/
typedef struct
{
  __IO uint32_t PCON;                   /*!< Offset: 0x000 Power control Register (R/W) */
  __IO uint32_t GPREG0;                 /*!< Offset: 0x004 General purpose Register 0 (R/W) */
  __IO uint32_t GPREG1;                 /*!< Offset: 0x008 General purpose Register 1 (R/W) */
  __IO uint32_t GPREG2;                 /*!< Offset: 0x00C General purpose Register 2 (R/W) */
  __IO uint32_t GPREG3;                 /*!< Offset: 0x010 General purpose Register 3 (R/W) */
  __IO uint32_t GPREG4;                 /*!< Offset: 0x014 General purpose Register 4 (R/W) */
} LPC_PMU_TypeDef;
/*@}*/ /* end of group LPC11xx_PMU */



// ------------------------------------------------------------------------------------------------
// -----                                       FLASHCTRL                                      -----
// ------------------------------------------------------------------------------------------------

typedef struct {                            /*!< (@ 0x4003C000) FLASHCTRL Structure    */
  __I  uint32_t RESERVED0[4];
  __IO uint32_t FLASHCFG;                   /*!< (@ 0x4003C010) Flash memory access time configuration register */
  __I  uint32_t RESERVED1[3];
  __IO uint32_t FMSSTART;                   /*!< (@ 0x4003C020) Signature start address register */
  __IO uint32_t FMSSTOP;                    /*!< (@ 0x4003C024) Signature stop-address register */
  __I  uint32_t RESERVED2[1];
  __I  uint32_t FMSW0;                      /*!< (@ 0x4003C02C) Word 0 [31:0]          */
  __I  uint32_t FMSW1;                      /*!< (@ 0x4003C030) Word 1 [63:32]         */
  __I  uint32_t FMSW2;                      /*!< (@ 0x4003C034) Word 2 [95:64]         */
  __I  uint32_t FMSW3;                      /*!< (@ 0x4003C038) Word 3 [127:96]        */
  __I  uint32_t RESERVED3[1001];
  __I  uint32_t FMSTAT;                     /*!< (@ 0x4003CFE0) Signature generation status register */
  __I  uint32_t RESERVED4[1];
  __IO uint32_t FMSTATCLR;                  /*!< (@ 0x4003CFE8) Signature generation status clear register */
} LPC_FLASHCTRL_Type;


/*------------- General Purpose Input/Output (GPIO) --------------------------*/
/** @addtogroup LPC11xx_GPIO LPC11xx General Purpose Input/Output 
  @{
*/
typedef struct
{
  union {
    __IO uint32_t MASKED_ACCESS[4096];  /*!< Offset: 0x0000 to 0x3FFC Port data Register for pins PIOn_0 to PIOn_11 (R/W) */
    struct {
         uint32_t RESERVED0[4095];
    __IO uint32_t DATA;                 /*!< Offset: 0x3FFC Port data Register (R/W) */
    };
  };
       uint32_t RESERVED1[4096];
  __IO uint32_t DIR;                    /*!< Offset: 0x8000 Data direction Register (R/W) */
  __IO uint32_t IS;                     /*!< Offset: 0x8004 Interrupt sense Register (R/W) */
  __IO uint32_t IBE;                    /*!< Offset: 0x8008 Interrupt both edges Register (R/W) */
  __IO uint32_t IEV;                    /*!< Offset: 0x800C Interrupt event Register  (R/W) */
  __IO uint32_t IE;                     /*!< Offset: 0x8010 Interrupt mask Register (R/W) */
  __I uint32_t RIS;                    /*!< Offset: 0x8014 Raw interrupt status Register (R/ ) */
  __I uint32_t MIS;                    /*!< Offset: 0x8018 Masked interrupt status Register (R/ ) */
  __O uint32_t IC;                     /*!< Offset: 0x801C Interrupt clear Register (/W) */
} LPC_GPIO_TypeDef;
/*@}*/ /* end of group LPC11xx_GPIO */

/*------------- Timer (TMR) --------------------------------------------------*/
/** @addtogroup LPC11xx_TMR LPC11xx 16/32-bit Counter/Timer 
  @{
*/
typedef struct
{
  __IO uint32_t IR;                     /*!< Offset: 0x000 Interrupt Register (R/W) */
  __IO uint32_t TCR;                    /*!< Offset: 0x004 Timer Control Register (R/W) */
  __IO uint32_t TC;                     /*!< Offset: 0x008 Timer Counter Register (R/W) */
  __IO uint32_t PR;                     /*!< Offset: 0x00C Prescale Register (R/W) */
  __IO uint32_t PC;                     /*!< Offset: 0x010 Prescale Counter Register (R/W) */
  __IO uint32_t MCR;                    /*!< Offset: 0x014 Match Control Register (R/W) */
  union {
  __IO uint32_t MR[4];                  /*!< Offset: Match Register base */
  struct{
  __IO uint32_t MR0;                    /*!< Offset: 0x018 Match Register 0 (R/W) */
  __IO uint32_t MR1;                    /*!< Offset: 0x01C Match Register 1 (R/W) */
  __IO uint32_t MR2;                    /*!< Offset: 0x020 Match Register 2 (R/W) */
  __IO uint32_t MR3;                    /*!< Offset: 0x024 Match Register 3 (R/W) */
  };
  };
  __IO uint32_t CCR;                    /*!< Offset: 0x028 Capture Control Register (R/W) */
  __I  uint32_t CR0;                    /*!< Offset: 0x02C Capture Register 0 (R/ ) */
  __I  uint32_t CR1;                    /*!< Offset: 0x030 Capture Register 1 (R/ ) */
       uint32_t RESERVED1[2];
  __IO uint32_t EMR;                    /*!< Offset: 0x03C External Match Register (R/W) */
       uint32_t RESERVED2[12];
  __IO uint32_t CTCR;                   /*!< Offset: 0x070 Count Control Register (R/W) */
  __IO uint32_t PWMC;                   /*!< Offset: 0x074 PWM Control Register (R/W) */
} LPC_TMR_TypeDef;
/*@}*/ /* end of group LPC11xx_TMR */


/*------------- Universal Asynchronous Receiver Transmitter (UART) -----------*/
/** @addtogroup LPC11xx_UART LPC11xx Universal Asynchronous Receiver/Transmitter 
  @{
*/
typedef struct
{
  union {
  __I  uint32_t  RBR;                   /*!< Offset: 0x000 Receiver Buffer  Register (R/ ) */
  __O  uint32_t  THR;                   /*!< Offset: 0x000 Transmit Holding Register ( /W) */
  __IO uint32_t  DLL;                   /*!< Offset: 0x000 Divisor Latch LSB (R/W) */
  };
  union {
  __IO uint32_t  DLM;                   /*!< Offset: 0x004 Divisor Latch MSB (R/W) */
  __IO uint32_t  IER;                   /*!< Offset: 0x000 Interrupt Enable Register (R/W) */
  };
  union {
  __I  uint32_t  IIR;                   /*!< Offset: 0x008 Interrupt ID Register (R/ ) */
  __O  uint32_t  FCR;                   /*!< Offset: 0x008 FIFO Control Register ( /W) */
  };
  __IO uint32_t  LCR;                   /*!< Offset: 0x00C Line Control Register (R/W) */
  __IO uint32_t  MCR;                   /*!< Offset: 0x010 Modem control Register (R/W) */
  __I  uint32_t  LSR;                   /*!< Offset: 0x014 Line Status Register (R/ ) */
  __I  uint32_t  MSR;                   /*!< Offset: 0x018 Modem status Register (R/ ) */
  __IO uint32_t  SCR;                   /*!< Offset: 0x01C Scratch Pad Register (R/W) */
  __IO uint32_t  ACR;                   /*!< Offset: 0x020 Auto-baud Control Register (R/W) */
       uint32_t  RESERVED0;
  __IO uint32_t  FDR;                   /*!< Offset: 0x028 Fractional Divider Register (R/W) */
       uint32_t  RESERVED1;
  __IO uint32_t  TER;                   /*!< Offset: 0x030 Transmit Enable Register (R/W) */
       uint32_t  RESERVED2[6];
  __IO uint32_t  RS485CTRL;             /*!< Offset: 0x04C RS-485/EIA-485 Control Register (R/W) */
  __IO uint32_t  ADRMATCH;              /*!< Offset: 0x050 RS-485/EIA-485 address match Register (R/W) */
  __IO uint32_t  RS485DLY;              /*!< Offset: 0x054 RS-485/EIA-485 direction control delay Register (R/W) */
  __I  uint32_t  FIFOLVL;               /*!< Offset: 0x058 FIFO Level Register (R) */
} LPC_UART_TypeDef;
/*@}*/ /* end of group LPC11xx_UART */


/*------------- Synchronous Serial Communication (SSP) -----------------------*/
/** @addtogroup LPC11xx_SSP LPC11xx Synchronous Serial Port 
  @{
*/
typedef struct
{
  __IO uint32_t CR0;                    /*!< Offset: 0x000 Control Register 0 (R/W) */
  __IO uint32_t CR1;                    /*!< Offset: 0x004 Control Register 1 (R/W) */
  __IO uint32_t DR;                     /*!< Offset: 0x008 Data Register (R/W) */
  __I  uint32_t SR;                     /*!< Offset: 0x00C Status Registe (R/ ) */
  __IO uint32_t CPSR;                   /*!< Offset: 0x010 Clock Prescale Register (R/W) */
  __IO uint32_t IMSC;                   /*!< Offset: 0x014 Interrupt Mask Set and Clear Register (R/W) */
  __I uint32_t RIS;                    /*!< Offset: 0x018 Raw Interrupt Status Register (R/) */
  __I uint32_t MIS;                    /*!< Offset: 0x01C Masked Interrupt Status Register (R/) */
  __O uint32_t ICR;                    /*!< Offset: 0x020 SSPICR Interrupt Clear Register (/W) */
} LPC_SSP_TypeDef;
/*@}*/ /* end of group LPC11xx_SSP */


/*------------- Inter-Integrated Circuit (I2C) -------------------------------*/
/** @addtogroup LPC11xx_I2C LPC11xx I2C-Bus Interface 
  @{
*/
typedef struct
{
  __IO uint32_t CONSET;                 /*!< Offset: 0x000 I2C Control Set Register (R/W) */
  __I  uint32_t STAT;                   /*!< Offset: 0x004 I2C Status Register (R/ ) */
  __IO uint32_t DAT;                    /*!< Offset: 0x008 I2C Data Register (R/W) */
  __IO uint32_t ADR0;                   /*!< Offset: 0x00C I2C Slave Address Register 0 (R/W) */
  __IO uint32_t SCLH;                   /*!< Offset: 0x010 SCH Duty Cycle Register High Half Word (R/W) */
  __IO uint32_t SCLL;                   /*!< Offset: 0x014 SCL Duty Cycle Register Low Half Word (R/W) */
  __O  uint32_t CONCLR;                 /*!< Offset: 0x018 I2C Control Clear Register ( /W) */
  __IO uint32_t MMCTRL;                 /*!< Offset: 0x01C Monitor mode control register (R/W) */
  __IO uint32_t ADR1;                   /*!< Offset: 0x020 I2C Slave Address Register 1 (R/W) */
  __IO uint32_t ADR2;                   /*!< Offset: 0x024 I2C Slave Address Register 2 (R/W) */
  __IO uint32_t ADR3;                   /*!< Offset: 0x028 I2C Slave Address Register 3 (R/W) */
  __I  uint32_t DATA_BUFFER;            /*!< Offset: 0x02C Data buffer register ( /W) */
  __IO uint32_t MASK0;                  /*!< Offset: 0x030 I2C Slave address mask register 0 (R/W) */
  __IO uint32_t MASK1;                  /*!< Offset: 0x034 I2C Slave address mask register 1 (R/W) */
  __IO uint32_t MASK2;                  /*!< Offset: 0x038 I2C Slave address mask register 2 (R/W) */
  __IO uint32_t MASK3;                  /*!< Offset: 0x03C I2C Slave address mask register 3 (R/W) */
} LPC_I2C_TypeDef;
/*@}*/ /* end of group LPC11xx_I2C */


/*------------- Watchdog Timer (WDT) -----------------------------------------*/
/** @addtogroup LPC11xx_WDT LPC11xx WatchDog Timer 
  @{
*/
typedef struct
{
  __IO uint32_t MOD;                    /*!< Offset: 0x000 Watchdog mode register (R/W) */
  __IO uint32_t TC;                     /*!< Offset: 0x004 Watchdog timer constant register (R/W) */
  __O  uint32_t FEED;                   /*!< Offset: 0x008 Watchdog feed sequence register (W) */
  __I  uint32_t TV;                     /*!< Offset: 0x00C Watchdog timer value register (R) */
       uint32_t RESERVED0;
  __IO uint32_t WARNINT;				/*!< Offset: 0x014 Watchdog timer warning int. register (R/W) */
  __IO uint32_t WINDOW;					/*!< Offset: 0x018 Watchdog timer window value register (R/W) */
} LPC_WDT_TypeDef;
/*@}*/ /* end of group LPC11xx_WDT */


/*------------- Analog-to-Digital Converter (ADC) ----------------------------*/
/** @addtogroup LPC11xx_ADC LPC11xx Analog-to-Digital Converter 
  @{
*/
typedef struct
{
  __IO uint32_t CR;                     /*!< Offset: 0x000       A/D Control Register (R/W) */
  __IO uint32_t GDR;                    /*!< Offset: 0x004       A/D Global Data Register (R/W) */
       uint32_t RESERVED0;
  __IO uint32_t INTEN;                  /*!< Offset: 0x00C       A/D Interrupt Enable Register (R/W) */
  __IO uint32_t DR[8];                  /*!< Offset: 0x010-0x02C A/D Channel 0..7 Data Register (R/W) */
  __I  uint32_t STAT;                   /*!< Offset: 0x030       A/D Status Register (R/ ) */
} LPC_ADC_TypeDef;
/*@}*/ /* end of group LPC11xx_ADC */


/*------------- CAN Controller (CAN) ----------------------------*/
/** @addtogroup LPC11xx_CAN LPC11xx Controller Area Network(CAN) 
  @{
*/
typedef struct
{
  __IO uint32_t CNTL;				/* 0x000 */
  __IO uint32_t STAT;
  __IO uint32_t EC;
  __IO uint32_t BT;
  __IO uint32_t INT;
  __IO uint32_t TEST;
  __IO uint32_t BRPE;
       uint32_t RESERVED0;
  __IO uint32_t IF1_CMDREQ;			/* 0x020 */
  __IO uint32_t IF1_CMDMSK;
  __IO uint32_t IF1_MSK1;
  __IO uint32_t IF1_MSK2;
  __IO uint32_t IF1_ARB1;
  __IO uint32_t IF1_ARB2;
  __IO uint32_t IF1_MCTRL;
  __IO uint32_t IF1_DA1;
  __IO uint32_t IF1_DA2;
  __IO uint32_t IF1_DB1;
  __IO uint32_t IF1_DB2;
       uint32_t RESERVED1[13];   
  __IO uint32_t IF2_CMDREQ;			/* 0x080 */
  __IO uint32_t IF2_CMDMSK;
  __IO uint32_t IF2_MSK1;
  __IO uint32_t IF2_MSK2;
  __IO uint32_t IF2_ARB1;
  __IO uint32_t IF2_ARB2;
  __IO uint32_t IF2_MCTRL;
  __IO uint32_t IF2_DA1;
  __IO uint32_t IF2_DA2;
  __IO uint32_t IF2_DB1;
  __IO uint32_t IF2_DB2;
       uint32_t RESERVED2[21];
  __I  uint32_t TXREQ1;				/* 0x100 */
  __I  uint32_t TXREQ2;
       uint32_t RESERVED3[6];
  __I  uint32_t ND1;				/* 0x120 */
  __I  uint32_t ND2;
       uint32_t RESERVED4[6];
  __I  uint32_t IR1;				/* 0x140 */
  __I  uint32_t IR2;
       uint32_t RESERVED5[6];
  __I  uint32_t MSGV1;				/* 0x160 */
  __I  uint32_t MSGV2;
       uint32_t RESERVED6[6];
  __IO uint32_t CLKDIV;				/* 0x180 */
} LPC_CAN_TypeDef;
/*@}*/ /* end of group LPC11xx_CAN */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/* Base addresses                                                             */
#define LPC_FLASH_BASE        (0x00000000UL)
#define LPC_RAM_BASE          (0x10000000UL)
#define LPC_APB0_BASE         (0x40000000UL)
#define LPC_AHB_BASE          (0x50000000UL)

/* APB0 peripherals                                                           */
#define LPC_I2C_BASE          (LPC_APB0_BASE + 0x00000)
#define LPC_WDT_BASE          (LPC_APB0_BASE + 0x04000)
#define LPC_UART_BASE         (LPC_APB0_BASE + 0x08000)
#define LPC_CT16B0_BASE       (LPC_APB0_BASE + 0x0C000)
#define LPC_CT16B1_BASE       (LPC_APB0_BASE + 0x10000)
#define LPC_CT32B0_BASE       (LPC_APB0_BASE + 0x14000)
#define LPC_CT32B1_BASE       (LPC_APB0_BASE + 0x18000)
#define LPC_ADC_BASE          (LPC_APB0_BASE + 0x1C000)
#define LPC_PMU_BASE          (LPC_APB0_BASE + 0x38000)
#define LPC_FLASHCTRL_BASE    (LPC_APB0_BASE + 0x3C000)
#define LPC_SSP0_BASE         (LPC_APB0_BASE + 0x40000)
#define LPC_IOCON_BASE        (LPC_APB0_BASE + 0x44000)
#define LPC_SYSCON_BASE       (LPC_APB0_BASE + 0x48000)
#define LPC_CAN_BASE          (LPC_APB0_BASE + 0x50000)
#define LPC_SSP1_BASE         (LPC_APB0_BASE + 0x58000)

/* AHB peripherals                                                            */
#define LPC_GPIO_BASE         (LPC_AHB_BASE  + 0x00000)
#define LPC_GPIO0_BASE        (LPC_AHB_BASE  + 0x00000)
#define LPC_GPIO1_BASE        (LPC_AHB_BASE  + 0x10000)
#define LPC_GPIO2_BASE        (LPC_AHB_BASE  + 0x20000)
#define LPC_GPIO3_BASE        (LPC_AHB_BASE  + 0x30000)

/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/
#define LPC_I2C               ((LPC_I2C_TypeDef    *) LPC_I2C_BASE   )
#define LPC_WDT               ((LPC_WDT_TypeDef    *) LPC_WDT_BASE   )
#define LPC_UART              ((LPC_UART_TypeDef   *) LPC_UART_BASE  )
#define LPC_TMR16B0           ((LPC_TMR_TypeDef    *) LPC_CT16B0_BASE)
#define LPC_TMR16B1           ((LPC_TMR_TypeDef    *) LPC_CT16B1_BASE)
#define LPC_TMR32B0           ((LPC_TMR_TypeDef    *) LPC_CT32B0_BASE)
#define LPC_TMR32B1           ((LPC_TMR_TypeDef    *) LPC_CT32B1_BASE)
#define LPC_ADC               ((LPC_ADC_TypeDef    *) LPC_ADC_BASE   )
#define LPC_PMU               ((LPC_PMU_TypeDef    *) LPC_PMU_BASE   )
#define LPC_FLASHCTRL         ((LPC_FLASHCTRL_Type *) LPC_FLASHCTRL_BASE)
#define LPC_SSP0              ((LPC_SSP_TypeDef    *) LPC_SSP0_BASE  )
#define LPC_SSP1              ((LPC_SSP_TypeDef    *) LPC_SSP1_BASE  )
#define LPC_CAN               ((LPC_CAN_TypeDef    *) LPC_CAN_BASE   )
#define LPC_IOCON             ((LPC_IOCON_TypeDef  *) LPC_IOCON_BASE )
#define LPC_SYSCON            ((LPC_SYSCON_TypeDef *) LPC_SYSCON_BASE)
#define LPC_GPIO0             ((LPC_GPIO_TypeDef   *) LPC_GPIO0_BASE )
#define LPC_GPIO1             ((LPC_GPIO_TypeDef   *) LPC_GPIO1_BASE )
#define LPC_GPIO2             ((LPC_GPIO_TypeDef   *) LPC_GPIO2_BASE )
#define LPC_GPIO3             ((LPC_GPIO_TypeDef   *) LPC_GPIO3_BASE )

#ifdef __cplusplus
}
#endif

#endif  /* __LPC11xx_H__ */
