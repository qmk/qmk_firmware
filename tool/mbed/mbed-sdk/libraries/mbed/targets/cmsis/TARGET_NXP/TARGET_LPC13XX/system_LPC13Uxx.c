/******************************************************************************
 * @file     system_LPC13Uxx.c
 * @purpose  CMSIS Cortex-M3 Device Peripheral Access Layer Source File
 *           for the NXP LPC13xx Device Series
 * @version  V1.10
 * @date     24. November 2010
 *
 * @note
 * Copyright (C) 2009-2010 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/


#include <stdint.h>
#include "LPC13Uxx.h"

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

/*--------------------- Clock Configuration ----------------------------------
//
// <e> Clock Configuration
//   <h> System Oscillator Control Register (SYSOSCCTRL)
//     <o1.0>      BYPASS: System Oscillator Bypass Enable
//                     <i> If enabled then PLL input (sys_osc_clk) is fed
//                     <i> directly from XTALIN and XTALOUT pins.
//     <o1.9>      FREQRANGE: System Oscillator Frequency Range
//                     <i> Determines frequency range for Low-power oscillator.
//                   <0=> 1 - 20 MHz
//                   <1=> 15 - 25 MHz
//   </h>
//
//   <h> Watchdog Oscillator Control Register (WDTOSCCTRL)
//     <o2.0..4>   DIVSEL: Select Divider for Fclkana
//                     <i> wdt_osc_clk = Fclkana/ (2 * (1 + DIVSEL))
//                   <0-31>
//     <o2.5..8>   FREQSEL: Select Watchdog Oscillator Analog Output Frequency (Fclkana)
//                   <0=> Undefined
//                   <1=> 0.5 MHz
//                   <2=> 0.8 MHz
//                   <3=> 1.1 MHz
//                   <4=> 1.4 MHz
//                   <5=> 1.6 MHz
//                   <6=> 1.8 MHz
//                   <7=> 2.0 MHz
//                   <8=> 2.2 MHz
//                   <9=> 2.4 MHz
//                   <10=> 2.6 MHz
//                   <11=> 2.7 MHz
//                   <12=> 2.9 MHz
//                   <13=> 3.1 MHz
//                   <14=> 3.2 MHz
//                   <15=> 3.4 MHz
//   </h>
//
//   <h> System PLL Control Register (SYSPLLCTRL)
//                   <i> F_clkout = M * F_clkin = F_CCO / (2 * P)
//                   <i> F_clkin must be in the range of  10 MHz to  25 MHz
//                   <i> F_CCO   must be in the range of 156 MHz to 320 MHz
//     <o3.0..4>   MSEL: Feedback Divider Selection
//                     <i> M = MSEL + 1
//                   <0-31>
//     <o3.5..6>   PSEL: Post Divider Selection
//                   <0=> P = 1
//                   <1=> P = 2
//                   <2=> P = 4
//                   <3=> P = 8
//   </h>
//
//   <h> System PLL Clock Source Select Register (SYSPLLCLKSEL)
//     <o4.0..1>   SEL: System PLL Clock Source
//                   <0=> IRC Oscillator
//                   <1=> System Oscillator
//                   <2=> Reserved
//                   <3=> Reserved
//   </h>
//
//   <h> Main Clock Source Select Register (MAINCLKSEL)
//     <o5.0..1>   SEL: Clock Source for Main Clock
//                   <0=> IRC Oscillator
//                   <1=> Input Clock to System PLL
//                   <2=> WDT Oscillator
//                   <3=> System PLL Clock Out
//   </h>
//
//   <h> System AHB Clock Divider Register (SYSAHBCLKDIV)
//     <o6.0..7>   DIV: System AHB Clock Divider
//                     <i> Divides main clock to provide system clock to core, memories, and peripherals.
//                     <i> 0 = is disabled
//                   <0-255>
//   </h>
//
//   <h> USB PLL Control Register (USBPLLCTRL)
//                   <i> F_clkout = M * F_clkin = F_CCO / (2 * P)
//                   <i> F_clkin must be in the range of  10 MHz to  25 MHz
//                   <i> F_CCO   must be in the range of 156 MHz to 320 MHz
//     <o7.0..4>   MSEL: Feedback Divider Selection
//                     <i> M = MSEL + 1
//                   <0-31>
//     <o7.5..6>   PSEL: Post Divider Selection
//                   <0=> P = 1
//                   <1=> P = 2
//                   <2=> P = 4
//                   <3=> P = 8
//   </h>
//
//   <h> USB PLL Clock Source Select Register (USBPLLCLKSEL)
//     <o8.0..1>   SEL: USB PLL Clock Source
//                     <i> USB PLL clock source must be switched to System Oscillator for correct USB operation
//                   <0=> IRC Oscillator
//                   <1=> System Oscillator
//                   <2=> Reserved
//                   <3=> Reserved
//   </h>
//
//   <h> USB Clock Source Select Register (USBCLKSEL)
//     <o9.0..1>   SEL: System PLL Clock Source
//                   <0=> USB PLL out
//                   <1=> Main clock
//                   <2=> Reserved
//                   <3=> Reserved
//   </h>
//
//   <h> USB Clock Divider Register (USBCLKDIV)
//     <o10.0..7>  DIV: USB Clock Divider
//                     <i> Divides USB clock to 48 MHz.
//                     <i> 0 = is disabled
//                   <0-255>
//   </h>
// </e>
*/
#define CLOCK_SETUP           1
#define SYSOSCCTRL_Val        0x00000000              // Reset: 0x000
#define WDTOSCCTRL_Val        0x00000000              // Reset: 0x000
#define SYSPLLCTRL_Val        0x00000025              // Reset: 0x000
#define SYSPLLCLKSEL_Val      0x00000001              // Reset: 0x000
#define MAINCLKSEL_Val        0x00000003              // Reset: 0x000
#define SYSAHBCLKDIV_Val      0x00000001              // Reset: 0x001
#define USBPLLCTRL_Val        0x00000023              // Reset: 0x000
#define USBPLLCLKSEL_Val      0x00000001              // Reset: 0x000
#define USBCLKSEL_Val         0x00000000              // Reset: 0x000
#define USBCLKDIV_Val         0x00000001              // Reset: 0x001

/*
//-------- <<< end of configuration section >>> ------------------------------
*/

/*----------------------------------------------------------------------------
  Check the register settings
 *----------------------------------------------------------------------------*/
#define CHECK_RANGE(val, min, max)                ((val < min) || (val > max))
#define CHECK_RSVD(val, mask)                     (val & mask)

/* Clock Configuration -------------------------------------------------------*/
#if (CHECK_RSVD((SYSOSCCTRL_Val),  ~0x00000003))
   #error "SYSOSCCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((WDTOSCCTRL_Val),  ~0x000001FF))
   #error "WDTOSCCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((SYSPLLCLKSEL_Val), 0, 2))
   #error "SYSPLLCLKSEL: Value out of range!"
#endif

#if (CHECK_RSVD((SYSPLLCTRL_Val),  ~0x000001FF))
   #error "SYSPLLCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((MAINCLKSEL_Val),  ~0x00000003))
   #error "MAINCLKSEL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((SYSAHBCLKDIV_Val), 0, 255))
   #error "SYSAHBCLKDIV: Value out of range!"
#endif

#if (CHECK_RANGE((USBPLLCLKSEL_Val), 0, 1))
   #error "USBPLLCLKSEL: Value out of range!"
#endif

#if (CHECK_RSVD((USBPLLCTRL_Val),  ~0x000001FF))
   #error "USBPLLCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((USBCLKSEL_Val), 0, 1))
   #error "USBCLKSEL: Value out of range!"
#endif

#if (CHECK_RANGE((USBCLKDIV_Val), 0, 255))
   #error "USBCLKDIV: Value out of range!"
#endif


/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/
    
/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define __XTAL            (12000000UL)    /* Oscillator frequency             */
#define __SYS_OSC_CLK     (    __XTAL)    /* Main oscillator frequency        */
#define __IRC_OSC_CLK     (12000000UL)    /* Internal RC oscillator frequency */


#define __FREQSEL   ((WDTOSCCTRL_Val >> 5) & 0x0F)
#define __DIVSEL   (((WDTOSCCTRL_Val & 0x1F) << 1) + 2)

#if (CLOCK_SETUP)                         /* Clock Setup              */
  #if  (__FREQSEL ==  0)
    #define __WDT_OSC_CLK        ( 0)                  /* undefined */
  #elif (__FREQSEL ==  1)
    #define __WDT_OSC_CLK        ( 500000 / __DIVSEL)
  #elif (__FREQSEL ==  2)
    #define __WDT_OSC_CLK        ( 800000 / __DIVSEL)
  #elif (__FREQSEL ==  3)
    #define __WDT_OSC_CLK        (1100000 / __DIVSEL)
  #elif (__FREQSEL ==  4)
    #define __WDT_OSC_CLK        (1400000 / __DIVSEL)
  #elif (__FREQSEL ==  5)
    #define __WDT_OSC_CLK        (1600000 / __DIVSEL)
  #elif (__FREQSEL ==  6)
    #define __WDT_OSC_CLK        (1800000 / __DIVSEL)
  #elif (__FREQSEL ==  7)
    #define __WDT_OSC_CLK        (2000000 / __DIVSEL)
  #elif (__FREQSEL ==  8)
    #define __WDT_OSC_CLK        (2200000 / __DIVSEL)
  #elif (__FREQSEL ==  9)
    #define __WDT_OSC_CLK        (2400000 / __DIVSEL)
  #elif (__FREQSEL == 10)
    #define __WDT_OSC_CLK        (2600000 / __DIVSEL)
  #elif (__FREQSEL == 11)
    #define __WDT_OSC_CLK        (2700000 / __DIVSEL)
  #elif (__FREQSEL == 12)
    #define __WDT_OSC_CLK        (2900000 / __DIVSEL)
  #elif (__FREQSEL == 13)
    #define __WDT_OSC_CLK        (3100000 / __DIVSEL)
  #elif (__FREQSEL == 14)
    #define __WDT_OSC_CLK        (3200000 / __DIVSEL)
  #else
    #define __WDT_OSC_CLK        (3400000 / __DIVSEL)
  #endif

  /* sys_pllclkin calculation */
  #if   ((SYSPLLCLKSEL_Val & 0x03) == 0)
    #define __SYS_PLLCLKIN           (__IRC_OSC_CLK)
  #elif ((SYSPLLCLKSEL_Val & 0x03) == 1)
    #define __SYS_PLLCLKIN           (__SYS_OSC_CLK)
  #else
    #define __SYS_PLLCLKIN           (0)
  #endif

  #define  __SYS_PLLCLKOUT         (__SYS_PLLCLKIN * ((SYSPLLCTRL_Val & 0x01F) + 1))

  /* main clock calculation */
  #if   ((MAINCLKSEL_Val & 0x03) == 0)
    #define __MAIN_CLOCK             (__IRC_OSC_CLK)
  #elif ((MAINCLKSEL_Val & 0x03) == 1)
    #define __MAIN_CLOCK             (__SYS_PLLCLKIN)
  #elif ((MAINCLKSEL_Val & 0x03) == 2)
    #if (__FREQSEL ==  0)
      #error "MAINCLKSEL: WDT Oscillator selected but FREQSEL is undefined!"
    #else
      #define __MAIN_CLOCK           (__WDT_OSC_CLK)
    #endif
  #elif ((MAINCLKSEL_Val & 0x03) == 3)
    #define __MAIN_CLOCK             (__SYS_PLLCLKOUT)
  #else
    #define __MAIN_CLOCK             (0)
  #endif

  #define __SYSTEM_CLOCK             (__MAIN_CLOCK / SYSAHBCLKDIV_Val)         

#else
  #define __SYSTEM_CLOCK             (__IRC_OSC_CLK)
#endif  // CLOCK_SETUP 


/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = __SYSTEM_CLOCK;/*!< System Clock Frequency (Core Clock)*/


/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)            /* Get Core Clock Frequency      */
{
  uint32_t wdt_osc = 0;

  /* Determine clock frequency according to clock register values             */
  switch ((LPC_SYSCON->WDTOSCCTRL >> 5) & 0x0F) {
    case 0:  wdt_osc =       0; break;
    case 1:  wdt_osc =  500000; break;
    case 2:  wdt_osc =  800000; break;
    case 3:  wdt_osc = 1100000; break;
    case 4:  wdt_osc = 1400000; break;
    case 5:  wdt_osc = 1600000; break;
    case 6:  wdt_osc = 1800000; break;
    case 7:  wdt_osc = 2000000; break;
    case 8:  wdt_osc = 2200000; break;
    case 9:  wdt_osc = 2400000; break;
    case 10: wdt_osc = 2600000; break;
    case 11: wdt_osc = 2700000; break;
    case 12: wdt_osc = 2900000; break;
    case 13: wdt_osc = 3100000; break;
    case 14: wdt_osc = 3200000; break;
    case 15: wdt_osc = 3400000; break;
  }
  wdt_osc /= ((LPC_SYSCON->WDTOSCCTRL & 0x1F) << 1) + 2;
 
  switch (LPC_SYSCON->MAINCLKSEL & 0x03) {
    case 0:                             /* Internal RC oscillator             */
      SystemCoreClock = __IRC_OSC_CLK;
      break;
    case 1:                             /* Input Clock to System PLL          */
      switch (LPC_SYSCON->SYSPLLCLKSEL & 0x03) {
          case 0:                       /* Internal RC oscillator             */
            SystemCoreClock = __IRC_OSC_CLK;
            break;
          case 1:                       /* System oscillator                  */
            SystemCoreClock = __SYS_OSC_CLK;
            break;
          case 2:                       /* Reserved                           */
          case 3:                       /* Reserved                           */
            SystemCoreClock = 0;
            break;
      }
      break;
    case 2:                             /* WDT Oscillator                     */
      SystemCoreClock = wdt_osc;
      break;
    case 3:                             /* System PLL Clock Out               */
      switch (LPC_SYSCON->SYSPLLCLKSEL & 0x03) {
          case 0:                       /* Internal RC oscillator             */
            if (LPC_SYSCON->SYSPLLCTRL & 0x180) {
              SystemCoreClock = __IRC_OSC_CLK;
            } else {
              SystemCoreClock = __IRC_OSC_CLK * ((LPC_SYSCON->SYSPLLCTRL & 0x01F) + 1);
            }
            break;
          case 1:                       /* System oscillator                  */
            if (LPC_SYSCON->SYSPLLCTRL & 0x180) {
              SystemCoreClock = __SYS_OSC_CLK;
            } else {
              SystemCoreClock = __SYS_OSC_CLK * ((LPC_SYSCON->SYSPLLCTRL & 0x01F) + 1);
            }
            break;
          case 2:                       /* Reserved                           */
          case 3:                       /* Reserved                           */
            SystemCoreClock = 0;
            break;
      }
      break;
  }

  SystemCoreClock /= LPC_SYSCON->SYSAHBCLKDIV;  

}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit (void) {
  volatile uint32_t i;

#if (CLOCK_SETUP)                                 /* Clock Setup              */

#if ((SYSPLLCLKSEL_Val & 0x03) == 1)
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 5);          /* Power-up System Osc      */
  LPC_SYSCON->SYSOSCCTRL    = SYSOSCCTRL_Val;
  for (i = 0; i < 200; i++) __NOP();
#endif

  LPC_SYSCON->SYSPLLCLKSEL  = SYSPLLCLKSEL_Val;   /* Select PLL Input         */
#if ((MAINCLKSEL_Val & 0x03) == 3)                /* Main Clock is PLL Out    */
  LPC_SYSCON->SYSPLLCTRL    = SYSPLLCTRL_Val;
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 7);          /* Power-up SYSPLL          */
  while (!(LPC_SYSCON->SYSPLLSTAT & 0x01));	      /* Wait Until PLL Locked    */
#endif

#if (((MAINCLKSEL_Val & 0x03) == 2) )
  LPC_SYSCON->WDTOSCCTRL    = WDTOSCCTRL_Val;
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 6);          /* Power-up WDT Clock       */
  for (i = 0; i < 200; i++) __NOP();
#endif

  LPC_SYSCON->MAINCLKSEL    = MAINCLKSEL_Val;     /* Select PLL Clock Output  */

  LPC_SYSCON->SYSAHBCLKDIV  = SYSAHBCLKDIV_Val;

#if ((USBCLKDIV_Val & 0x1FF) != 0)                /* USB clock is used        */
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 10);         /* Power-up USB PHY         */

  /* Regardless USB PLL is used as USB clock or not, USB PLL needs to be configured. */
  LPC_SYSCON->PDRUNCFG     &= ~(1 <<  8);         /* Power-up USB PLL         */
  LPC_SYSCON->USBPLLCLKSEL  = USBPLLCLKSEL_Val;   /* Select PLL Input         */
  LPC_SYSCON->USBPLLCTRL    = USBPLLCTRL_Val;
  while (!(LPC_SYSCON->USBPLLSTAT   & 0x01));     /* Wait Until PLL Locked    */

  LPC_SYSCON->USBCLKSEL     = USBCLKSEL_Val;      /* Select USB Clock         */
  LPC_SYSCON->USBCLKDIV     = USBCLKDIV_Val;      /* Set USB clock divider    */

#else                                             /* USB clock is not used    */                        
  LPC_SYSCON->PDRUNCFG     |=  (1 << 10);         /* Power-down USB PHY       */
  LPC_SYSCON->PDRUNCFG     |=  (1 <<  8);         /* Power-down USB PLL       */
#endif

#endif

  /* System clock to the IOCON needs to be enabled or
  most of the I/O related peripherals won't work. */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);

}
