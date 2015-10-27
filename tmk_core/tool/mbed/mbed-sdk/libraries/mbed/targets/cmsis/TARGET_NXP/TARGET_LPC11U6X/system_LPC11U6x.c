/**************************************************************************//**
 * @file     system_LPC11U6x.c
 * @brief    CMSIS Cortex-M3 Device System Source File for
 *           NXP LPC11U6x Device Series
 * @version  V1.00
 * @date     19. July 2013
 *
 * @note
 * Copyright (C) 2013 ARM Limited. All rights reserved.
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
#include "LPC11U6x.h"

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

/*- SystemCoreClock Configuration -------------------------------------------*/
// <e0> SystemCoreClock Configuration
#define CLOCK_SETUP           1
//
//   <h> System Oscillator Control (SYSOSCCTRL)
//     <o.0>      BYPASS: System Oscillator Bypass Enable
//                     <i> If enabled then PLL input (sys_osc_clk) is fed
//                     <i> directly from XTALIN and XTALOUT pins.
//     <o.1>      FREQRANGE: System Oscillator Frequency Range
//                     <i> Determines frequency range for Low-power oscillator.
//                   <0=> 1 - 20 MHz
//                   <1=> 15 - 25 MHz
//   </h>
#define SYSOSCCTRL_Val        0x00000000              // Reset value: 0x000
//
//   <o.0..1> System PLL Clock Source Select (SYSPLLCLKSEL)
//        <0=> IRC Oscillator
//        <1=> Crystal Oscillator (SYSOSC)
//        <3=> RTC Oscillator (32 kHz)
#define SYSPLLCLKSEL_Val      0x00000001              // Reset value: 0x000
//
//   <e> Clock Configuration (Manual)
#define CLOCK_SETUP_REG       1
//
//     <h> WD Oscillator Setting (WDTOSCCTRL)
//       <o.0..4> DIVSEL: Select Divider for Fclkana
//              <i> wd_osc_clk = Fclkana / (2 × (1 + DIVSEL))
//            <0-31>
//       <o.5..8> FREQSEL: Select WD Oscillator Analog Output Frequency (Fclkana)
//            <1=> 0.5 MHz
//            <2=> 0.8 MHz
//            <3=> 1.1 MHz
//            <4=> 1.4 MHz
//            <5=> 1.6 MHz
//            <6=> 1.8 MHz
//            <7=> 2.0 MHz
//            <8=> 2.2 MHz
//            <9=> 2.4 MHz
//            <10=> 2.6 MHz
//            <11=> 2.7 MHz
//            <12=> 2.9 MHz
//            <13=> 3.1 MHz
//            <14=> 3.2 MHz
//            <15=> 3.4 MHz
//     </h>
#define WDTOSCCTRL_Val        0x000000A0              // Reset value: 0x0A0
//
//     <h> System PLL Setting (SYSPLLCTRL)
//              <i> F_clkout = M * F_clkin = F_CCO / (2 * P)
//              <i> F_clkin must be in the range of  10 MHz to  25 MHz
//              <i> F_CCO   must be in the range of 156 MHz to 320 MHz
//       <o.0..4> MSEL: Feedback Divider Selection
//              <i> M = MSEL + 1
//            <0-31>
//       <o.5..6> PSEL: Post Divider Selection
//              <i> Post divider ratio P. Division ratio is 2 * P
//            <0=> P = 1
//            <1=> P = 2
//            <2=> P = 4
//            <3=> P = 8
//     </h>
#define SYSPLLCTRL_Val        0x00000023              // Reset value: 0x000
//
//     <o.0..1> Main Clock Source Select (MAINCLKSEL)
//        <0=> IRC Oscillator
//        <1=> PLL Input
//        <2=> WD Oscillator
//        <3=> PLL Output
#define MAINCLKSEL_Val        0x00000003              // Reset value: 0x000
//
//     <o.0..7>   System AHB Clock Divider (SYSAHBCLKDIV.DIV)
//            <i> Divides main clock to provide system clock to core, memories, and peripherals.
//            <i> 0 = is disabled
//          <0-255>
#define SYSAHBCLKDIV_Val      0x00000001              // Reset value: 0x001
//   </e>
//
//   <e> Clock Configuration (via ROM PLL API)
#define CLOCK_SETUP_API       0
//
//     <o> PLL API Mode Select
//          <0=> Exact
//          <1=> Less than or equal
//          <2=> Greater than or equal
//          <3=> As close as possible
#define PLL_API_MODE_Val      0
//
//     <o> CPU Frequency [Hz]  <1000000-50000000:1000>
#define PLL_API_FREQ_Val      48000000
//   </e>
//
//   <e> USB Clock Configuration
#define USB_CLOCK_SETUP       1
//     <h> USB PLL Control (USBPLLCTRL)
//              <i> F_clkout = M * F_clkin = F_CCO / (2 * P)
//              <i> F_clkin must be in the range of  10 MHz to  25 MHz
//              <i> F_CCO   must be in the range of 156 MHz to 320 MHz
//       <o.0..4>   MSEL: Feedback Divider Selection
//              <i> M = MSEL + 1
//            <0-31>
//       <o.5..6>   PSEL: Post Divider Selection
//              <i> Post divider ratio P. Division ratio is 2 * P
//            <0=> P = 1
//            <1=> P = 2
//            <2=> P = 4
//            <3=> P = 8
//     </h>
#define USBPLLCTRL_Val        0x00000023              // Reset value: 0x000
//
//     <o.0..1> USB PLL Clock Source Select (USBPLLCLKSEL.SEL)
//                     <i> USB PLL clock source must be switched to System Oscillator for correct USB operation
//                   <0=> IRC Oscillator
//                   <1=> System Oscillator
#define USBPLLCLKSEL_Val      0x00000001              // Reset value: 0x000
//
//     <o.0..1> USB Clock Source Select (USBCLKSEL.SEL)
//                   <0=> USB PLL out
//                   <1=> Main clock
#define USBCLKSEL_Val         0x00000000              // Reset value: 0x000
//
//     <o.0..7> USB Clock Divider (USBCLKDIV.DIV)
//                     <i> Divides USB clock to 48 MHz.
//                     <i> 0 = is disabled
//                   <0-255>
#define USBCLKDIV_Val         0x00000001              // Reset Value: 0x001
//   </e>
//
// </e>
//
// <o0>System Oscillator (XTAL) Frequency [Hz] <1000000-25000000>
//          <i> XTAL frequency must be in the range of  1 MHz to  25 MHz
//
#define XTAL_CLK_Val          12000000

/*
//-------- <<< end of configuration section >>> ------------------------------
*/

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define __XTAL_CLK     ( XTAL_CLK_Val)        /* Oscillator freq              */
#define __SYS_OSC_CLK  (   __XTAL_CLK)        /* System oscillator freq       */
#define __IRC_OSC_CLK  (   12000000UL)        /* Internal RC oscillator freq  */
#define __RTC_OSC_CLK  (      32768UL)        /* RTC oscillator freq          */

/*----------------------------------------------------------------------------
  Check the register settings
 *----------------------------------------------------------------------------*/
#define CHECK_RANGE(val, min, max)                ((val < min) || (val > max))
#define CHECK_RSVD(val, mask)                     (val & mask)

#if (CHECK_RSVD((SYSOSCCTRL_Val),  ~0x00000003))
   #error "SYSOSCCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((WDTOSCCTRL_Val),  ~0x000001FF))
   #error "WDTOSCCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((SYSPLLCLKSEL_Val), 0, 3))
   #error "SYSPLLCLKSEL: Value out of range!"
#endif

#if (SYSPLLCLKSEL_Val == 3)                        // RTC Oscillator used as PLL input
  #if (CLOCK_SETUP_API == 1)
    #error "SYSPLLCLKSEL: RTC oscillator not allowed as PLL clock source!"
	#endif
  #if (CLOCK_SETUP_REG == 1) && (MAINCLKSEL_Val == 3)  // RTC Oscillator used as PLL input
    #error "SYSPLLCLKSEL: RTC oscillator not allowed as PLL clock source!"
	#endif
#endif

#if (CHECK_RSVD((SYSPLLCTRL_Val),  ~0x0000007F))
   #error "SYSPLLCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((MAINCLKSEL_Val),  ~0x00000003))
   #error "MAINCLKSEL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((SYSAHBCLKDIV_Val), 0, 255))
   #error "SYSAHBCLKDIV: Value out of range!"
#endif

#if ( CLOCK_SETUP_REG == CLOCK_SETUP_API )
   #error "You must select either manual or API based Clock Configuration!"
#endif

#if (CHECK_RANGE((USBPLLCLKSEL_Val), 0, 1))
   #error "USBPLLCLKSEL: Value out of range!"
#endif

#if (CHECK_RSVD((USBPLLCTRL_Val),  ~0x000007F))
   #error "USBPLLCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((USBCLKSEL_Val), 0, 1))
   #error "USBCLKSEL: Value out of range!"
#endif

#if (CHECK_RANGE((USBCLKDIV_Val), 0, 255))
   #error "USBCLKDIV: Value out of range!"
#endif

#if (CHECK_RANGE(XTAL_CLK_Val, 1000000, 25000000))
   #error "XTAL frequency is out of bounds"
#endif

#if (CHECK_RANGE(PLL_API_MODE_Val, 0, 3))
   #error "PLL API Mode Select not valid"
#endif

#if (CHECK_RANGE(PLL_API_FREQ_Val, 1000000, 50000000))
   #error "CPU Frequency (API mode) not valid"
#endif



/*----------------------------------------------------------------------------
  Calculate system core clock
 *----------------------------------------------------------------------------*/
#if (CLOCK_SETUP)                               /* Clock Setup                */

  /* sys_pllclkin calculation */
  #if   ((SYSPLLCLKSEL_Val & 0x03) == 0)
    #define __SYS_PLLCLKIN           (__IRC_OSC_CLK)
  #elif ((SYSPLLCLKSEL_Val & 0x03) == 1)
    #define __SYS_PLLCLKIN           (__SYS_OSC_CLK)
  #elif ((SYSPLLCLKSEL_Val & 0x03) == 3)
    #define __SYS_PLLCLKIN           (__RTC_OSC_CLK)
  #else
    #error "Oops"
  #endif

  #if (CLOCK_SETUP_REG == 1)                    /* Clock Setup via Register   */

    #define __FREQSEL   ((WDTOSCCTRL_Val >> 5) & 0x0F)
    #define __DIVSEL   (((WDTOSCCTRL_Val & 0x1F) << 1) + 2)

    #if  (__FREQSEL ==  0)
      #error "WDTOSCCTRL.FREQSEL undefined!"
    #elif (__FREQSEL ==  1)
      #define __OSC_CLK              ( 500000 / __DIVSEL)
    #elif (__FREQSEL ==  2)
      #define __OSC_CLK              ( 800000 / __DIVSEL)
    #elif (__FREQSEL ==  3)
      #define __OSC_CLK              (1100000 / __DIVSEL)
    #elif (__FREQSEL ==  4)
      #define __OSC_CLK              (1400000 / __DIVSEL)
    #elif (__FREQSEL ==  5)
      #define __OSC_CLK              (1600000 / __DIVSEL)
    #elif (__FREQSEL ==  6)
      #define __OSC_CLK              (1800000 / __DIVSEL)
    #elif (__FREQSEL ==  7)
      #define __OSC_CLK              (2000000 / __DIVSEL)
    #elif (__FREQSEL ==  8)
      #define __OSC_CLK              (2200000 / __DIVSEL)
    #elif (__FREQSEL ==  9)
      #define __OSC_CLK              (2400000 / __DIVSEL)
    #elif (__FREQSEL == 10)
      #define __OSC_CLK              (2600000 / __DIVSEL)
    #elif (__FREQSEL == 11)
      #define __OSC_CLK              (2700000 / __DIVSEL)
    #elif (__FREQSEL == 12)
      #define __OSC_CLK              (2900000 / __DIVSEL)
    #elif (__FREQSEL == 13)
      #define __OSC_CLK              (3100000 / __DIVSEL)
    #elif (__FREQSEL == 14)
      #define __OSC_CLK              (3200000 / __DIVSEL)
    #else
      #define __OSC_CLK              (3400000 / __DIVSEL)
    #endif

    #define  __SYS_PLLCLKOUT           (__SYS_PLLCLKIN * ((SYSPLLCTRL_Val & 0x01F) + 1))

    /* main clock calculation */
    #if   ((MAINCLKSEL_Val & 0x03) == 0)
      #define __MAIN_CLOCK             (__IRC_OSC_CLK)
    #elif ((MAINCLKSEL_Val & 0x03) == 1)
      #define __MAIN_CLOCK             (__SYS_PLLCLKIN)
    #elif ((MAINCLKSEL_Val & 0x03) == 2)
      #define __MAIN_CLOCK             (__OSC_CLK)
    #elif ((MAINCLKSEL_Val & 0x03) == 3)
      #define __MAIN_CLOCK             (__SYS_PLLCLKOUT)
    #else
      #error "Oops"
    #endif

    #define __SYSTEM_CLOCK             (__MAIN_CLOCK / SYSAHBCLKDIV_Val)
  #endif /* Clock Setup via Register */

  #if (CLOCK_SETUP_API == 1)                    /* Clock Setup via ROM API    */
    #define __SYSTEM_CLOCK           (PLL_API_FREQ_Val)
  #endif /* Clock Setup via PLL API */

#else
  #define __SYSTEM_CLOCK             (__IRC_OSC_CLK)
#endif  /* CLOCK_SETUP */



#if ((CLOCK_SETUP == 1) && (CLOCK_SETUP_API == 1)) /* PLL Setup via PLL API   */
#include "power_api.h"

typedef struct _ROM {
   const unsigned p_dev0;
   const unsigned p_dev1;
   const unsigned p_dev2;
   const PWRD *   pPWRD;                        /* ROM Power Management API   */
   const unsigned p_dev4;
   const unsigned p_dev5;
   const unsigned p_dev6;
   const unsigned p_dev7;
}  ROM;

/*----------------------------------------------------------------------------
  PLL API Function
 *----------------------------------------------------------------------------*/
static void setPLL(const uint32_t pllMode, const uint32_t pllInFreq, const uint32_t reqCpuFreq)
{
  uint32_t cmd[5], res[5];
  ROM ** rom = (ROM **) 0x1FFF1FF8;             /* pointer to power API calls */

  cmd[0] = pllInFreq;                           /* PLL's input   freq in KHz  */
  cmd[1] = reqCpuFreq;                          /* requested CPU freq in KHz  */
  cmd[2] = pllMode;
  cmd[3] = 0;                                   /* no timeout for PLL to lock */

  /* Execute API call */
  (*rom)->pPWRD->set_pll(cmd, res);             /* call API function          */
  if ((res[0] != PLL_CMD_SUCCESS)){             /* in case of an error ...    */
    while(1);                                   /* ... stay here              */
  }
}
#endif




/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = __SYSTEM_CLOCK;      /* System Clock Frequency     */


/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)               /* Get Core Clock Frequency   */
{
  uint32_t oscClk = 0;

  /* Determine clock frequency according to clock register values             */
  switch ((LPC_SYSCON->WDTOSCCTRL >> 5) & 0x0F) {
    case 0:  oscClk =       0; break;
    case 1:  oscClk =  500000; break;
    case 2:  oscClk =  800000; break;
    case 3:  oscClk = 1100000; break;
    case 4:  oscClk = 1400000; break;
    case 5:  oscClk = 1600000; break;
    case 6:  oscClk = 1800000; break;
    case 7:  oscClk = 2000000; break;
    case 8:  oscClk = 2200000; break;
    case 9:  oscClk = 2400000; break;
    case 10: oscClk = 2600000; break;
    case 11: oscClk = 2700000; break;
    case 12: oscClk = 2900000; break;
    case 13: oscClk = 3100000; break;
    case 14: oscClk = 3200000; break;
    case 15: oscClk = 3400000; break;
  }
  oscClk /= ((LPC_SYSCON->WDTOSCCTRL & 0x1F) << 1) + 2;

  switch (LPC_SYSCON->MAINCLKSEL & 0x03) {
    case 0:                                     /* Internal RC oscillator     */
      SystemCoreClock = __IRC_OSC_CLK;
      break;
    case 1:                                     /* Input Clock to System PLL  */
      switch (LPC_SYSCON->SYSPLLCLKSEL & 0x03) {
        case 0:                                 /* Internal RC oscillator     */
          SystemCoreClock = __IRC_OSC_CLK;
          break;
        case 1:                                 /* System oscillator          */
          SystemCoreClock = __SYS_OSC_CLK;
          break;
        case 2:                                 /* Reserved                   */
        case 3:                                 /* Reserved                   */
          SystemCoreClock = 0;
          break;
      }
      break;
    case 2:                                     /* WDT Oscillator             */
      SystemCoreClock = oscClk;
      break;
    case 3:                                     /* System PLL Clock Out       */
      switch (LPC_SYSCON->SYSPLLCLKSEL & 0x03) {
        case 0:                                 /* Internal RC oscillator     */
          SystemCoreClock = __IRC_OSC_CLK * ((LPC_SYSCON->SYSPLLCTRL & 0x01F) + 1);
          break;
        case 1:                                 /* System oscillator          */
          SystemCoreClock = __SYS_OSC_CLK * ((LPC_SYSCON->SYSPLLCTRL & 0x01F) + 1);
          break;
        case 2:                                 /* Reserved                   */
        case 3:                                 /* Reserved                   */
          SystemCoreClock = 0;
          break;
      }
      break;
  }

  SystemCoreClock /= LPC_SYSCON->SYSAHBCLKDIV;

}

#define PDRUN_VALID_BITS    0x000025FFL
#define PDRUN_RESERVED_ONE  0x0000C800L

static void power_down_config(uint32_t val)
{
  volatile uint32_t tmp;
  tmp = (LPC_SYSCON->PDRUNCFG & PDRUN_VALID_BITS);
  tmp |= (val & PDRUN_VALID_BITS);
  LPC_SYSCON->PDRUNCFG = (tmp | PDRUN_RESERVED_ONE);
}

static void power_up_config(uint32_t val)
{
  volatile uint32_t tmp;
  tmp = (LPC_SYSCON->PDRUNCFG & PDRUN_VALID_BITS);
  tmp &= ~(val & PDRUN_VALID_BITS);
  LPC_SYSCON->PDRUNCFG = (tmp | PDRUN_RESERVED_ONE);
}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 */
void SystemInit (void) {
#if (CLOCK_SETUP)
  volatile uint32_t i;
#endif
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
  LPC_SYSCON->SYSPLLCTRL    = SYSPLLCTRL_Val;

#if (CLOCK_SETUP)                               /* Clock Setup                */

#if ((SYSPLLCLKSEL_Val & 0x03) == 1)
  // Initialize XTALIN/XTALOUT pins
  LPC_IOCON->PIO2_0 = 0x01;
  LPC_IOCON->PIO2_1 = 0x01;

  LPC_SYSCON->SYSOSCCTRL    = SYSOSCCTRL_Val;
  power_up_config(1<<5);                        /* Power-up sysosc            */
  for (i = 0; i < 2500; i++) __NOP();           /* Wait for osc to stabilize  */
#endif

#if ((SYSPLLCLKSEL_Val & 0x03) == 3)
  LPC_SYSCON->RTCOSCCTRL    =  (1 << 0);        /* Enable 32 kHz output       */
  for (i = 0; i < 200; i++) __NOP();            /* Wait for osc to stabilize  */
#endif

  LPC_SYSCON->SYSPLLCLKSEL  = SYSPLLCLKSEL_Val; /* Select PLL Input           */
  LPC_SYSCON->SYSPLLCLKUEN  = 0x01;             /* Update Clock Source        */
  LPC_SYSCON->SYSPLLCLKUEN  = 0x00;             /* Toggle Update Register     */
  LPC_SYSCON->SYSPLLCLKUEN  = 0x01;
  while (!(LPC_SYSCON->SYSPLLCLKUEN & 0x01));   /* Wait Until Updated         */

#if (CLOCK_SETUP_REG == 1)                      /* Clock Setup via Register   */

#if (((MAINCLKSEL_Val & 0x03) == 2) )
  LPC_SYSCON->WDTOSCCTRL    = WDTOSCCTRL_Val;
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 6);        /* Power-up WDT Clock         */
  for (i = 0; i < 2000; i++) __NOP();           /* Wait for osc to stabilize  */
#endif

#if ((MAINCLKSEL_Val & 0x03) == 3)              /* Main Clock is PLL Out      */
  power_down_config(1<<7);                      /* Power-down SYSPLL          */
  LPC_SYSCON->SYSPLLCTRL    = SYSPLLCTRL_Val;
  power_up_config(1<<7);                        /* Power-up SYSPLL            */
  while (!(LPC_SYSCON->SYSPLLSTAT & 0x01));     /* Wait Until PLL Locked      */
#endif

  LPC_SYSCON->MAINCLKSEL    = MAINCLKSEL_Val;   /* Select Clock Source        */
  LPC_SYSCON->MAINCLKUEN    = 0x01;             /* Update MCLK Clock Source   */
  LPC_SYSCON->MAINCLKUEN    = 0x00;             /* Toggle Update Register     */
  LPC_SYSCON->MAINCLKUEN    = 0x01;
  while (!(LPC_SYSCON->MAINCLKUEN & 0x01));     /* Wait Until Updated         */

  LPC_SYSCON->SYSAHBCLKDIV  = SYSAHBCLKDIV_Val;
#endif                                          /* Clock Setup via Register   */

#if (CLOCK_SETUP_API == 1)                      /* Clock Setup via PLL API    */
//  LPC_SYSCON->SYSPLLCLKSEL  = 0x00;             /* Use IRC                    */
//  LPC_SYSCON->SYSPLLCLKUEN  = 0x01;             /* Update Clock Source        */
//  LPC_SYSCON->SYSPLLCLKUEN  = 0x00;             /* Toggle Update Register     */
//  LPC_SYSCON->SYSPLLCLKUEN  = 0x01;
//  while (!(LPC_SYSCON->SYSPLLCLKUEN & 0x01));   /* Wait Until Updated       */

  LPC_SYSCON->MAINCLKSEL    = SYSPLLCLKSEL_Val; /* Select same as SYSPLL      */
  LPC_SYSCON->MAINCLKUEN    = 0x01;             /* Update MCLK Clock Source   */
  LPC_SYSCON->MAINCLKUEN    = 0x00;             /* Toggle Update Register     */
  LPC_SYSCON->MAINCLKUEN    = 0x01;
  while (!(LPC_SYSCON->MAINCLKUEN & 0x01));     /* Wait Until Updated         */

  LPC_SYSCON->SYSAHBCLKDIV  = 1;

  setPLL(PLL_API_MODE_Val, __SYS_PLLCLKIN / 1000, PLL_API_FREQ_Val / 1000);
#endif                                          /* Clock Setup via PLL API    */

#if (USB_CLOCK_SETUP == 1)                      /* USB clock is used          */
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 10);       /* Power-up USB PHY           */

#if ((USBCLKSEL_Val & 0x003) == 0)              /* USB clock is USB PLL out   */
  LPC_SYSCON->PDRUNCFG     &= ~(1 <<  8);       /* Power-up USB PLL           */
  LPC_SYSCON->USBPLLCLKSEL  = USBPLLCLKSEL_Val; /* Select PLL Input           */
  LPC_SYSCON->USBPLLCLKUEN  = 0x01;             /* Update Clock Source        */
  LPC_SYSCON->USBPLLCLKUEN  = 0x00;             /* Toggle Update Register     */
  LPC_SYSCON->USBPLLCLKUEN  = 0x01;
  while (!(LPC_SYSCON->USBPLLCLKUEN & 0x01));   /* Wait Until Updated         */

  LPC_SYSCON->USBPLLCTRL    = USBPLLCTRL_Val;
  while (!(LPC_SYSCON->USBPLLSTAT   & 0x01));   /* Wait Until PLL Locked      */

  LPC_SYSCON->USBCLKSEL     = 0x00;             /* Select USB PLL             */
#endif

  LPC_SYSCON->USBCLKSEL     = USBCLKSEL_Val;    /* Select USB Clock           */
  LPC_SYSCON->USBCLKDIV     = USBCLKDIV_Val;    /* Set USB clock divider      */

#else                                           /* USB clock is not used      */
  LPC_SYSCON->PDRUNCFG     |=  (1 << 10);       /* Power-down USB PHY         */
  LPC_SYSCON->PDRUNCFG     |=  (1 <<  8);       /* Power-down USB PLL         */
#endif

#endif                                          /* Clock Setup                */

}
