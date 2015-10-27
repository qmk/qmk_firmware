/**************************************************************************//**
 * @file     system_LPC15xx.c
 * @brief    CMSIS Cortex-M3 Device System Source File for
 *           NXP LPC15xx Device Series
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
#include "LPC15xx.h"

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
#define SYSPLLCLKSEL_Val      0x00000001              // Reset value: 0x000
//
//   <e> Clock Configuration (Manual)
#define CLOCK_SETUP_REG       1
//
//     <o.0..1> Main Clock Source Select A (MAINCLKSELA)
//        <0=> IRC Oscillator
//        <1=> System Oscillator
//        <2=> WD Oscillator
#define MAINCLKSELA_Val       0x00000001              // Reset value: 0x000
//
//     <o.0..1> Main Clock Source Select B (MAINCLKSELB)
//        <0=> MAINCLKSELA
//        <1=> System PLL Input
//        <2=> System PLL Output
//        <3=> RTC Oscillator
#define MAINCLKSELB_Val       0x00000002              // Reset value: 0x000
//
//     <h> System PLL Setting (SYSPLLCTRL)
//              <i> F_clkout = M * F_clkin = F_CCO / (2 * P)
//              <i> F_clkin must be in the range of  10 MHz to  25 MHz
//              <i> F_CCO   must be in the range of 156 MHz to 320 MHz
//       <o.0..5> MSEL: Feedback Divider Selection
//              <i> M = MSEL + 1
//            <0-31>
//       <o.5..7> PSEL: Post Divider Selection
//              <i> Post divider ratio P. Division ratio is 2 * P
//            <0=> P = 1
//            <1=> P = 2
//            <2=> P = 4
//            <3=> P = 8
//     </h>
#define SYSPLLCTRL_Val        0x00000005              // Reset value: 0x000
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
//     <o> CPU Frequency [Hz]  <1000000-72000000:1000>
#define PLL_API_FREQ_Val      72000000
//   </e>
//
//   <e> USB Clock Configuration
#define USB_CLOCK_SETUP       0
//     <h> USB PLL Control (USBPLLCTRL)
//              <i> F_clkout = M * F_clkin = F_CCO / (2 * P)
//              <i> F_clkin must be in the range of  10 MHz to  25 MHz
//              <i> F_CCO   must be in the range of 156 MHz to 320 MHz
//       <o.0..5>   MSEL: Feedback Divider Selection
//              <i> M = MSEL + 1
//            <0-31>
//       <o.7..6>   PSEL: Post Divider Selection
//              <i> Post divider ratio P. Division ratio is 2 * P
//            <0=> P = 1
//            <1=> P = 2
//            <2=> P = 4
//            <3=> P = 8
//     </h>
#define USBPLLCTRL_Val        0x00000023              // Reset value: 0x000
//
//     <o.0..1> USB PLL Clock Source Select (USBPLLCLKSEL.SEL)
//                   <0=> IRC Oscillator
//                   <1=> System Oscillator
#define USBPLLCLKSEL_Val      0x00000001              // Reset value: 0x000
//
//     <o.0..1> USB Clock Source Select (USBCLKSEL.SEL)
//                   <0=> IRC Oscillator
//                   <1=> System Oscillator
//                   <2=> USB PLL out
//                   <3=> Main clock
#define USBCLKSEL_Val         0x00000002              // Reset value: 0x000
//
//     <o.0..7> USB Clock Divider (USBCLKDIV.DIV)
//                     <i> Divides USB clock to 48 MHz.
//                     <i> 0 = is disabled
//                   <0-255>
#define USBCLKDIV_Val         0x00000001              // Reset Value: 0x001
//   </e>
//
//   <e> SCT Clock Configuration
#define SCT_CLOCK_SETUP       1
//     <h> SCT PLL Control (SCTPLLCTRL)
//              <i> F_clkout = M * F_clkin = F_CCO / (2 * P)
//              <i> F_clkin must be in the range of  10 MHz to  25 MHz
//              <i> F_CCO   must be in the range of 156 MHz to 320 MHz
//       <o.0..5>   MSEL: Feedback Divider Selection
//              <i> M = MSEL + 1
//            <0-31>
//       <o.7..6>   PSEL: Post Divider Selection
//              <i> Post divider ratio P. Division ratio is 2 * P
//            <0=> P = 1
//            <1=> P = 2
//            <2=> P = 4
//            <3=> P = 8
//     </h>
#define SCTPLLCTRL_Val        0x00000005              // Reset value: 0x000
//
//     <o.0..1> SCT PLL Clock Source Select (SCTPLLCLKSEL.SEL)
//                   <0=> IRC Oscillator
//                   <1=> System Oscillator
#define SCTPLLCLKSEL_Val      0x00000001              // Reset value: 0x000
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
#define __WDT_OSC_CLK  (     503000UL)        /* WDT oscillator freq          */

/*----------------------------------------------------------------------------
  Check the register settings
 *----------------------------------------------------------------------------*/
#define CHECK_RANGE(val, min, max)                ((val < min) || (val > max))
#define CHECK_RSVD(val, mask)                     (val & mask)

#if (CHECK_RANGE((SYSOSCCTRL_Val), 0, 1))
   #error "SYSOSCCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((SYSPLLCLKSEL_Val), 0, 3))
   #error "SYSPLLCLKSEL: Value out of range!"
#endif

#if (CHECK_RSVD((SYSPLLCTRL_Val),  ~0x000000FF))
   #error "SYSPLLCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((MAINCLKSELA_Val), 0, 2))
   #error "MAINCLKSELA: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((MAINCLKSELB_Val),  ~0x00000003))
   #error "MAINCLKSELB: Invalid values of reserved bits!"
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

#if (CHECK_RSVD((USBPLLCTRL_Val),  ~0x00000FF))
   #error "USBPLLCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((USBCLKSEL_Val), 0, 3))
   #error "USBCLKSEL: Value out of range!"
#endif

#if (CHECK_RANGE((USBCLKDIV_Val), 0, 255))
   #error "USBCLKDIV: Value out of range!"
#endif

#if (CHECK_RANGE((SCTPLLCLKSEL_Val), 0, 1))
   #error "SCTPLLCLKSEL: Value out of range!"
#endif

#if (CHECK_RSVD((SCTPLLCTRL_Val),  ~0x00000FF))
   #error "SCTPLLCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE(XTAL_CLK_Val, 1000000, 25000000))
   #error "XTAL frequency is out of bounds"
#endif

#if (CHECK_RANGE(PLL_API_MODE_Val, 0, 3))
   #error "PLL API Mode Select not valid"
#endif

#if (CHECK_RANGE(PLL_API_FREQ_Val, 1000000, 72000000))
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
  #else
    #error "Oops"
  #endif

  #if (CLOCK_SETUP_REG == 1)                    /* Clock Setup via Register   */

    #if   ((MAINCLKSELA_Val & 0x03) == 0)
      #define __MAINA_CLOCK            (__IRC_OSC_CLK)
    #elif ((MAINCLKSELA_Val & 0x03) == 1)
      #define __MAINA_CLOCK            (__SYS_OSC_CLK)
    #elif ((MAINCLKSELA_Val & 0x03) == 2)
      #define __MAINA_CLOCK            (__WDT_OSC_CLK)
    #else
      #error "Oops"
    #endif

    #define  __SYS_PLLCLKOUT           (__SYS_PLLCLKIN * ((SYSPLLCTRL_Val & 0x01F) + 1))

    /* main clock calculation */
    #if   ((MAINCLKSELB_Val & 0x03) == 0)
      #define __MAINB_CLOCK            (__MAINA_CLOCK)
    #elif ((MAINCLKSELB_Val & 0x03) == 1)
      #define __MAINB_CLOCK            (__SYS_PLLCLKIN)
    #elif ((MAINCLKSELB_Val & 0x03) == 2)
      #define __MAINB_CLOCK            (__SYS_PLLCLKOUT)
    #elif ((MAINCLKSELB_Val & 0x03) == 3)
      #define __MAINB_CLOCK            (__RTC_OSC_CLK)
    #else
      #error "Oops"
    #endif

    #define __SYSTEM_CLOCK             (__MAINB_CLOCK / SYSAHBCLKDIV_Val)
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
  ROM ** rom = (ROM **) 0x03000200;             /* pointer to power API calls */

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
  /* Determine clock frequency according to clock register values             */
  switch (LPC_SYSCON->MAINCLKSELB & 0x03) {
		case 0:                                    /* MAINCLKSELA  clock sel      */
      switch (LPC_SYSCON->MAINCLKSELA & 0x03) {
        case 0:                                 /* Internal RC oscillator     */
          SystemCoreClock = __IRC_OSC_CLK;
          break;
        case 1:                                 /* System oscillator          */
          SystemCoreClock = __SYS_OSC_CLK;
          break;
        case 2:                                 /* Watchdog oscillator        */
          SystemCoreClock = __WDT_OSC_CLK;
          break;
        case 3:                                 /* Reserved                   */
          SystemCoreClock = 0;
          break;
      }
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
    case 2:                                     /* System PLL Clock Out       */
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
    case 3:                                     /* WDT Oscillator             */
      SystemCoreClock = __WDT_OSC_CLK;
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
 */
void SystemInit (void) {
#if (CLOCK_SETUP)
  volatile uint32_t i;
#endif

#if (CLOCK_SETUP)                               /* Clock Setup                */

#if ((SYSPLLCLKSEL_Val & 0x03) == 1)
  LPC_SYSCON->SYSOSCCTRL    = SYSOSCCTRL_Val;
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 21);       /* Power-up sysosc            */
  for (i = 0; i < 200; i++) __NOP();            /* Wait for osc to stabilize  */
#endif

  LPC_SYSCON->SYSPLLCLKSEL  = SYSPLLCLKSEL_Val; /* Select PLL Input           */

#if (CLOCK_SETUP_REG == 1)                      /* Clock Setup via Register   */

#if (((MAINCLKSELA_Val & 0x03) == 1) )
  LPC_SYSCON->SYSOSCCTRL    = SYSOSCCTRL_Val;
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 21);       /* Power-up sysosc            */
  for (i = 0; i < 200; i++) __NOP();            /* Wait for osc to stabilize  */
#endif

#if (((MAINCLKSELA_Val & 0x03) == 2) )
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 20);       /* Power-up WDT Clock         */
  for (i = 0; i < 200; i++) __NOP();            /* Wait for osc to stabilize  */
#endif

#if ((MAINCLKSELB_Val & 0x03) == 3)
  LPC_SYSCON->RTCOSCCTRL    =  (1 << 0);        /* Enable 32 kHz output       */
  for (i = 0; i < 200; i++) __NOP();            /* Wait for osc to stabilize  */
#endif

  LPC_SYSCON->MAINCLKSELA = MAINCLKSELA_Val;    /* select MAINCLKA clock      */

#if ((MAINCLKSELB_Val & 0x03) == 2)              /* Main Clock is PLL Out      */
  LPC_SYSCON->SYSPLLCTRL    = SYSPLLCTRL_Val;
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 22);       /* Power-up SYSPLL            */
  while (!(LPC_SYSCON->SYSPLLSTAT & 0x01));     /* Wait Until PLL Locked      */
#endif

  LPC_SYSCON->MAINCLKSELB = MAINCLKSELB_Val;    /* select Main clock         */

  LPC_SYSCON->SYSAHBCLKDIV  = SYSAHBCLKDIV_Val;
#endif                                          /* Clock Setup via Register   */

#if (CLOCK_SETUP_API == 1)                      /* Clock Setup via PLL API    */
//  LPC_SYSCON->SYSPLLCLKSEL  = 0x00;             /* Use IRC                    */

  LPC_SYSCON->MAINCLKSELB   = (1 << 2);         /* Select System PLL output   */

  LPC_SYSCON->SYSAHBCLKDIV  = 1;

  setPLL(PLL_API_MODE_Val, __SYS_PLLCLKIN / 1000, PLL_API_FREQ_Val / 1000);
#endif                                          /* Clock Setup via PLL API    */

#if (USB_CLOCK_SETUP == 1)                      /* USB clock is used          */
  LPC_SYSCON->PDRUNCFG     &= ~(1 <<  9);       /* Power-up USB PHY           */

#if ((USBCLKSEL_Val & 0x003) == 2)              /* USB clock is USB PLL out   */
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 23);       /* Power-up USB PLL           */
  LPC_SYSCON->USBPLLCLKSEL  = USBPLLCLKSEL_Val; /* Select PLL Input           */

  LPC_SYSCON->USBPLLCTRL    = USBPLLCTRL_Val;
  while (!(LPC_SYSCON->USBPLLSTAT   & 0x01));   /* Wait Until PLL Locked      */

  LPC_SYSCON->USBCLKSEL     = 0x02;             /* Select USB PLL             */
#endif

  LPC_SYSCON->USBCLKSEL     = USBCLKSEL_Val;    /* Select USB Clock           */
  LPC_SYSCON->USBCLKDIV     = USBCLKDIV_Val;    /* Set USB clock divider      */

#else                                           /* USB clock is not used      */
  LPC_SYSCON->PDRUNCFG     |=  (1 <<  9);       /* Power-down USB PHY         */
  LPC_SYSCON->PDRUNCFG     |=  (1 << 23);       /* Power-down USB PLL         */
#endif

#if (SCT_CLOCK_SETUP == 1)                      /* SCT clock is used          */
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 24);       /* Power-up SCT PLL           */
  LPC_SYSCON->SCTPLLCLKSEL  = SCTPLLCLKSEL_Val; /* Select PLL Input           */

  LPC_SYSCON->SCTPLLCTRL    = SCTPLLCTRL_Val;
  while (!(LPC_SYSCON->SCTPLLSTAT   & 0x01));   /* Wait Until PLL Locked      */
#else                                           /* SCT clock is not used      */
  LPC_SYSCON->PDRUNCFG     |=  (1 << 24);       /* Power-down SCT PLL         */
#endif

#endif                                          /* Clock Setup                */


  LPC_SYSCON->SYSAHBCLKCTRL0 |= (1UL << 12); /* enable clock for SWM       */

}
