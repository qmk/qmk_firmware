/*
** ###################################################################
**     Compilers:           ARM Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     
**
**     Version:             rev. 1.0, 2011-12-15
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright: 2015 Freescale Semiconductor, Inc. All Rights Reserved.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2011-12-15)
**         Initial version
**
** ###################################################################
*/

/**
 * @file MK20DX256
 * @version 1.0
 * @date 2011-12-15
 * @brief Device specific configuration file for MK20DX256 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "MK20DX256.h"

#define DISABLE_WDOG    1

#define CLOCK_SETUP     3
/* Predefined clock setups
   0 ... Multipurpose Clock Generator (MCG) in FLL Engaged Internal (FEI) mode
         Reference clock source for MCG module is the slow internal clock source 32.768kHz
         Core clock = 41.94MHz, BusClock = 41.94MHz
         This works on Teensy3.1
   1 ... Multipurpose Clock Generator (MCG) in PLL Engaged External (PEE) mode
         Reference clock source for MCG module is an external crystal 8MHz
         Core clock = 48MHz, BusClock = 48MHz
   2 ... Multipurpose Clock Generator (MCG) in Bypassed Low Power External (BLPE) mode
         Core clock/Bus clock derived directly from an external crystal 8MHz with no multiplication
         Core clock = 8MHz, BusClock = 8MHz
   3 ... Multipurpose Clock Generator (MCG) in PLL Engaged External (PEE) mode
         Reference clock source for MCG module is an external crystal 16MHz
         Core clock = 72MHz, BusClock = 48MHz
         This is the default Teensy3.1 72Mhz set up      
*/

/*----------------------------------------------------------------------------
  Define clock source values
 *----------------------------------------------------------------------------*/
#if (CLOCK_SETUP == 0)
    #define CPU_XTAL_CLK_HZ                 8000000u /* Value of the external crystal or oscillator clock frequency in Hz */
    #define CPU_XTAL32k_CLK_HZ              32768u   /* Value of the external 32k crystal or oscillator clock frequency in Hz */
    #define CPU_INT_SLOW_CLK_HZ             32768u   /* Value of the slow internal oscillator clock frequency in Hz  */
    #define CPU_INT_FAST_CLK_HZ             4000000u /* Value of the fast internal oscillator clock frequency in Hz  */
    #define DEFAULT_SYSTEM_CLOCK            41943040u /* Default System clock value */
#elif (CLOCK_SETUP == 1)
    #define CPU_XTAL_CLK_HZ                 8000000u /* Value of the external crystal or oscillator clock frequency in Hz */
    #define CPU_XTAL32k_CLK_HZ              32768u   /* Value of the external 32k crystal or oscillator clock frequency in Hz */
    #define CPU_INT_SLOW_CLK_HZ             32768u   /* Value of the slow internal oscillator clock frequency in Hz  */
    #define CPU_INT_FAST_CLK_HZ             4000000u /* Value of the fast internal oscillator clock frequency in Hz  */
    #define DEFAULT_SYSTEM_CLOCK            48000000u /* Default System clock value */
#elif (CLOCK_SETUP == 2)
    #define CPU_XTAL_CLK_HZ                 8000000u /* Value of the external crystal or oscillator clock frequency in Hz */
    #define CPU_XTAL32k_CLK_HZ              32768u   /* Value of the external 32k crystal or oscillator clock frequency in Hz */
    #define CPU_INT_SLOW_CLK_HZ             32768u   /* Value of the slow internal oscillator clock frequency in Hz  */
    #define CPU_INT_FAST_CLK_HZ             4000000u /* Value of the fast internal oscillator clock frequency in Hz  */
    #define DEFAULT_SYSTEM_CLOCK            8000000u /* Default System clock value */
#elif (CLOCK_SETUP == 3)
    #define CPU_XTAL_CLK_HZ                 16000000u /* Value of the external crystal or oscillator clock frequency in Hz */
    #define CPU_XTAL32k_CLK_HZ              32768u   /* Value of the external 32k crystal or oscillator clock frequency in Hz */
    #define CPU_INT_SLOW_CLK_HZ             32768u   /* Value of the slow internal oscillator clock frequency in Hz  */
    #define CPU_INT_FAST_CLK_HZ             4000000u /* Value of the fast internal oscillator clock frequency in Hz  */
    #define DEFAULT_SYSTEM_CLOCK            72000000u /* Default System clock value */    
#endif /* (CLOCK_SETUP == 2) */


/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */
void SystemInit (void) {
  /* SystemInit MUST NOT use any variables from the .data section, as this section is not loaded yet! */

#if (DISABLE_WDOG)
  /* Disable the WDOG module */
  /* WDOG_UNLOCK: WDOGUNLOCK=0xC520 */
  WDOG->UNLOCK = (uint16_t)0xC520u;     /* Key 1 */
  /* WDOG_UNLOCK : WDOGUNLOCK=0xD928 */
  WDOG->UNLOCK  = (uint16_t)0xD928u;    /* Key 2 */
  /* WDOG_STCTRLH: DISTESTWDOG=0,BYTESEL=0,TESTSEL=0,TESTWDOG=0,STNDBYEN=1,WAITEN=1,STOPEN=1,DBGEN=0,ALLOWUPDATE=1,WINEN=0,IRQRSTEN=0,CLKSRC=1,WDOGEN=0 */
  WDOG->STCTRLH = (uint16_t)0x01D2u;
#endif /* (DISABLE_WDOG) */

#if (CLOCK_SETUP == 0)
  /* SIM->CLKDIV1: OUTDIV1=0,OUTDIV2=0,OUTDIV4=1 Set Prescalers 41.94MHz cpu, 41.94MHz system, 20.97MHz flash*/
  SIM->CLKDIV1 = SIM_CLKDIV1_OUTDIV4(1);
  /* Switch to FEI Mode */
  /* MCG->C1: CLKS=0,FRDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
  MCG->C1 = MCG_C1_IREFS_MASK | MCG_C1_IRCLKEN_MASK;
  /* MCG->C2: LOCKRE0=0,RANGE0=0,HGO=0,EREFS=0,LP=0,IRCS=0 */
  MCG->C2 = (uint8_t)0x00u;
  /* MCG_C4: DMX32=0,DRST_DRS=1 */
  MCG->C4 = (uint8_t)((MCG->C4 & (uint8_t)~(uint8_t)0xC0u) | (uint8_t)0x20u);
  /* MCG->C5: PLLCLKEN=0,PLLSTEN=0,PRDIV0=0 */
  MCG->C5 = (uint8_t)0x00u;
  /* MCG->C6: LOLIE=0,PLLS=0,CME=0,VDIV0=0 */
  MCG->C6 = (uint8_t)0x00u;
  while((MCG->S & MCG_S_IREFST_MASK) == 0u) { } /* Check that the source of the FLL reference clock is the internal reference clock. */
  while((MCG->S & 0x0Cu) != 0x00u) { } /* Wait until output of the FLL is selected */
  
#elif (CLOCK_SETUP == 1)
  /* SIM->CLKDIV1: OUTDIV1=0,OUTDIV2=0,OUTDIV4=1 Set Prescalers 48MHz cpu, 48MHz system, 24MHz flash*/
  SIM->CLKDIV1 = SIM_CLKDIV1_OUTDIV4(1);
  /* Switch to FBE Mode */
  /* OSC0->CR: ERCLKEN=0,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  OSC0->CR = (uint8_t)0x00u;
  /* MCG->C7: OSCSEL=0 */
  MCG->C7 = (uint8_t)0x00u;
  /* MCG->C2: LOCKRE0=0,RANGE0=2,HGO=0,EREFS=1,LP=0,IRCS=0 */
  MCG->C2 = MCG_C2_RANGE0(2);
  /* MCG->C1: CLKS=2,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  MCG->C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(3) | MCG_C1_IRCLKEN_MASK;
  /* MCG->C4: DMX32=0,DRST_DRS=0 */
  MCG->C4 &= (uint8_t)~(uint8_t)0xE0u;
  /* MCG->C5: PLLCLKEN=0,PLLSTEN=0,PRDIV0=3 */
  MCG->C5 = MCG_C5_PRDIV0(3);
  /* MCG->C6: LOLIE=0,PLLS=0,CME=0,VDIV0=0 */
  MCG->C6 = (uint8_t)0x00u;
  while((MCG->S & MCG_S_OSCINIT0_MASK) == 0u) { } /* Check that the oscillator is running */
  while((MCG->S & 0x0Cu) != 0x08u) { } /* Wait until external reference clock is selected as MCG output */
  /* Switch to PBE Mode */
  /* MCG_C5: PLLCLKEN=0,PLLSTEN=0,PRDIV0=3 */
  MCG->C5 = MCG_C5_PRDIV0(3);
  /* MCG->C6: LOLIE=0,PLLS=1,CME=0,VDIV0=0 */
  MCG->C6 = MCG_C6_PLLS_MASK;
  while((MCG->S & MCG_S_PLLST_MASK) == 0u) { } /* Wait until the source of the PLLS clock has switched to the PLL */
  while((MCG->S & MCG_S_LOCK0_MASK) == 0u) { } /* Wait until locked */
  /* Switch to PEE Mode */
  /* MCG->C1: CLKS=0,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  MCG->C1 = MCG_C1_FRDIV(3) | MCG_C1_IRCLKEN_MASK;
  while((MCG->S & 0x0Cu) != 0x0Cu) { } /* Wait until output of the PLL is selected */
  while((MCG->S & MCG_S_LOCK0_MASK) == 0u) { } /* Wait until locked */
  
#elif (CLOCK_SETUP == 2)
  /* SIM->CLKDIV1: OUTDIV1=0,OUTDIV2=0,OUTDIV4=1 Set Prescalers 8MHz cpu, 8MHz system, 8MHz flash*/
  SIM->CLKDIV1 = SIM_CLKDIV1_OUTDIV4(1);
  /* Switch to FBE Mode */
  /* OSC0->CR: ERCLKEN=0,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  OSC0->CR = (uint8_t)0x00u;
  /* MCG->C7: OSCSEL=0 */
  MCG->C7 = (uint8_t)0x00u;
  /* MCG->C2: LOCKRE0=0,RANGE0=2,HGO=0,EREFS=1,LP=0,IRCS=0 */
  MCG->C2 = MCG_C2_RANGE0(2) | MCG_C2_EREFS0_MASK;
  /* MCG->C1: CLKS=2,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  MCG->C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(3) | MCG_C1_IRCLKEN_MASK;
  /* MCG->C4: DMX32=0,DRST_DRS=0 */
  MCG->C4 &= (uint8_t)~(uint8_t)0xE0u;
  /* MCG->C5: PLLCLKEN=0,PLLSTEN=0,PRDIV0=0 */
  MCG->C5 = (uint8_t)0x00u;
  /* MCG->C6: LOLIE=0,PLLS=0,CME=0,VDIV0=0 */
  MCG->C6 = (uint8_t)0x00u;
  while((MCG->S & MCG_S_OSCINIT0_MASK) == 0u) { } /* Check that the oscillator is running */
  while((MCG->S & 0x0CU) != 0x08u) { } /* Wait until external reference clock is selected as MCG output */
  /* Switch to BLPE Mode */
  /* MCG->C2: LOCKRE0=0,RANGE0=2,HGO=0,EREFS=1,LP=0,IRCS=0 */
  MCG->C2 = MCG_C2_RANGE0(2) | MCG_C2_EREFS0_MASK;
  
#elif (CLOCK_SETUP == 3)
  /* SIM->CLKDIV1: OUTDIV1=0,OUTDIV2=0,OUTDIV4=1 Set Prescalers 72MHz cpu, 72MHz system, 36MHz flash*/
  SIM->CLKDIV1 = SIM_CLKDIV1_OUTDIV4(1);
  /* SIM->CLKDIV2: USBDIV=2,USBFRAC=1 Divide 72MHz system clock for USB 48MHz */
  SIM->CLKDIV2 = SIM_CLKDIV2_USBDIV(2) | SIM_CLKDIV2_USBFRAC_MASK;
  /* OSC0->CR: ERCLKEN=0,EREFSTEN=0,SC2P=1,SC4P=0,SC8P=1,SC16P=0 10pF loading capacitors for 16MHz system oscillator*/
  OSC0->CR = OSC_CR_SC8P_MASK | OSC_CR_SC2P_MASK;
  /* Switch to FBE Mode */
  /* MCG->C7: OSCSEL=0 */
  MCG->C7 = (uint8_t)0x00u;
  /* MCG->C2: LOCKRE0=0,RANGE0=2,HGO=0,EREFS=1,LP=0,IRCS=0 */
  MCG->C2 = MCG_C2_RANGE0(2) | MCG_C2_EREFS0_MASK;
  //MCG->C2 = (uint8_t)0x24u;
  /* MCG->C1: CLKS=2,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  MCG->C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(3) | MCG_C1_IRCLKEN_MASK;
  /* MCG->C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */  
  MCG->C4 &= (uint8_t)~(uint8_t)0xE0u; 
  /* MCG->C5: PLLCLKEN=0,PLLSTEN=0,PRDIV0=7 */
  MCG->C5 = MCG_C5_PRDIV0(7);
  /* MCG->C6: LOLIE=0,PLLS=0,CME=0,VDIV0=0 */
  MCG->C6 = (uint8_t)0x00u;
  while((MCG->S & MCG_S_OSCINIT0_MASK) == 0u) { } /* Check that the oscillator is running */
  while((MCG->S & 0x0Cu) != 0x08u) { } /* Wait until external reference clock is selected as MCG output */
  /* Switch to PBE Mode */
  /* MCG_C5: PLLCLKEN=0,PLLSTEN=0,PRDIV0=5 */
  MCG->C5 = MCG_C5_PRDIV0(5);
  /* MCG->C6: LOLIE=0,PLLS=1,CME=0,VDIV0=3 */
  MCG->C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV0(3);
  while((MCG->S & MCG_S_PLLST_MASK) == 0u) { } /* Wait until the source of the PLLS clock has switched to the PLL */
  while((MCG->S & MCG_S_LOCK0_MASK) == 0u) { } /* Wait until locked */
  /* Switch to PEE Mode */
  /* MCG->C1: CLKS=0,FRDIV=2,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  MCG->C1 = MCG_C1_FRDIV(2) | MCG_C1_IRCLKEN_MASK;
  while((MCG->S & 0x0Cu) != 0x0Cu) { } /* Wait until output of the PLL is selected */
  while((MCG->S & MCG_S_LOCK0_MASK) == 0u) { } /* Wait until locked */  
#endif /* (CLOCK_SETUP) */
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {
  uint32_t MCGOUTClock;                                                        /* Variable to store output clock frequency of the MCG module */
  uint8_t Divider;

  if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x0u) {
    /* Output of FLL or PLL is selected */
    if ((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0u) {
      /* FLL is selected */
      if ((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0u) {
        /* External reference clock is selected */
        if ((MCG->C7 & MCG_C7_OSCSEL_MASK) == 0x0u) {
          MCGOUTClock = CPU_XTAL_CLK_HZ;                                       /* System oscillator drives MCG clock */
        } else { /* (!((MCG->C7 & MCG_C7_OSCSEL_MASK) == 0x0u)) */
          MCGOUTClock = CPU_XTAL32k_CLK_HZ;                                    /* RTC 32 kHz oscillator drives MCG clock */
        } /* (!((MCG->C7 & MCG_C7_OSCSEL_MASK) == 0x0u)) */
        Divider = (uint8_t)(1u << ((MCG->C1 & MCG_C1_FRDIV_MASK) >> MCG_C1_FRDIV_SHIFT));
        MCGOUTClock = (MCGOUTClock / Divider);  /* Calculate the divided FLL reference clock */
        if ((MCG->C2 & MCG_C2_RANGE0_MASK) != 0x0u) {
          MCGOUTClock /= 32u;                                                  /* If high range is enabled, additional 32 divider is active */
        } /* ((MCG->C2 & MCG_C2_RANGE0_MASK) != 0x0u) */
      } else { /* (!((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0u)) */
        MCGOUTClock = CPU_INT_SLOW_CLK_HZ;                                     /* The slow internal reference clock is selected */
      } /* (!((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0u)) */
      /* Select correct multiplier to calculate the MCG output clock  */
      switch (MCG->C4 & (MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS_MASK)) {
        case 0x0u:
          MCGOUTClock *= 640u;
          break;
        case 0x20u:
          MCGOUTClock *= 1280u;
          break;
        case 0x40u:
          MCGOUTClock *= 1920u;
          break;
        case 0x60u:
          MCGOUTClock *= 2560u;
          break;
        case 0x80u:
          MCGOUTClock *= 732u;
          break;
        case 0xA0u:
          MCGOUTClock *= 1464u;
          break;
        case 0xC0u:
          MCGOUTClock *= 2197u;
          break;
        case 0xE0u:
          MCGOUTClock *= 2929u;
          break;
        default:
          break;
      }
    } else { /* (!((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0u)) */
      /* PLL is selected */
      Divider = (1u + (MCG->C5 & MCG_C5_PRDIV0_MASK));
      MCGOUTClock = (uint32_t)(CPU_XTAL_CLK_HZ / Divider);                     /* Calculate the PLL reference clock */
      Divider = ((MCG->C6 & MCG_C6_VDIV0_MASK) + 24u);
      MCGOUTClock *= Divider;                       /* Calculate the MCG output clock */
    } /* (!((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0u)) */
  } else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x40u) {
    /* Internal reference clock is selected */
    if ((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0u) {
      MCGOUTClock = CPU_INT_SLOW_CLK_HZ;                                       /* Slow internal reference clock selected */
    } else { /* (!((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0u)) */
      MCGOUTClock = CPU_INT_FAST_CLK_HZ / (1 << ((MCG->SC & MCG_SC_FCRDIV_MASK) >> MCG_SC_FCRDIV_SHIFT));  /* Fast internal reference clock selected */
    } /* (!((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0u)) */
  } else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80u) {
    /* External reference clock is selected */
    if ((MCG->C7 & MCG_C7_OSCSEL_MASK) == 0x0u) {
      MCGOUTClock = CPU_XTAL_CLK_HZ;                                           /* System oscillator drives MCG clock */
    } else { /* (!((MCG->C7 & MCG_C7_OSCSEL_MASK) == 0x0u)) */
      MCGOUTClock = CPU_XTAL32k_CLK_HZ;                                        /* RTC 32 kHz oscillator drives MCG clock */
    } /* (!((MCG->C7 & MCG_C7_OSCSEL_MASK) == 0x0u)) */
  } else { /* (!((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80u)) */
    /* Reserved value */
    return;
  } /* (!((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80u)) */
  SystemCoreClock = (MCGOUTClock / (1u + ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT)));
}
