/* mbed Microcontroller Library
 * Copyright (C) 2008-2009 ARM Limited. All rights reserved.
 *
 * ARM7 version of CMSIS-like functionality - not advised for use outside mbed!
 */

#include <stdint.h>
#include "LPC23xx.h"

#define CLOCK_SETUP           1
#define SCS_Val               0x00000020
#define CLKSRCSEL_Val         0x00000001

#define PLL0_SETUP            1
#define PLL0CFG_Val           0x00000013
#define CCLKCFG_Val           0x00000007
#define USBCLKCFG_Val         0x00000009
#define PCLKSEL0_Val          0x00000000
#define PCLKSEL1_Val          0x00000000
#define PCONP_Val             0x042887DE
#define CLKOUTCFG_Val         0x00000000
#define MAMCR_Val             0x00000001  // there is a bug in the MAM so it should never be fully enabled (only disabled or partially enabled)
#define MAMTIM_Val            0x00000004

/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/
    
#define XTAL        (12000000UL)        /* Oscillator frequency               */
#define OSC_CLK     (      XTAL)        /* Main oscillator frequency          */
#define RTC_CLK     (   32000UL)        /* RTC oscillator frequency           */
#define IRC_OSC     ( 4000000UL)        /* Internal RC oscillator frequency   */

/* F_cco0 = (2 * M * F_in) / N  */
#define __M               (((PLL0CFG_Val      ) & 0x7FFF) + 1)
#define __N               (((PLL0CFG_Val >> 16) & 0x00FF) + 1)
#define __FCCO(__F_IN)    ((2 * __M * __F_IN) / __N) 
#define __CCLK_DIV        (((CCLKCFG_Val      ) & 0x00FF) + 1)

/* Determine core clock frequency according to settings */
 #if (PLL0_SETUP)
    #if   ((CLKSRCSEL_Val & 0x03) == 1)
        #define __CORE_CLK (__FCCO(OSC_CLK) / __CCLK_DIV)
    #elif ((CLKSRCSEL_Val & 0x03) == 2)
        #define __CORE_CLK (__FCCO(RTC_CLK) / __CCLK_DIV)
    #else 
        #define __CORE_CLK (__FCCO(IRC_OSC) / __CCLK_DIV)
    #endif
 #endif


/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = __CORE_CLK;/*!< System Clock Frequency (Core Clock)*/

/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)            /* Get Core Clock Frequency      */
{
  /* Determine clock frequency according to clock register values             */
  if (((LPC_SC->PLL0STAT >> 24) & 3) == 3) { /* If PLL0 enabled and connected */
    switch (LPC_SC->CLKSRCSEL & 0x03) {
      case 0:                                /* Int. RC oscillator => PLL0    */
      case 3:                                /* Reserved, default to Int. RC  */
        SystemCoreClock = (IRC_OSC * 
                          (((2 * ((LPC_SC->PLL0STAT & 0x7FFF) + 1))) /
                          (((LPC_SC->PLL0STAT >> 16) & 0xFF) + 1))   /
                          ((LPC_SC->CCLKCFG & 0xFF)+ 1));
        break;
      case 1:                                /* Main oscillator => PLL0       */
        SystemCoreClock = (OSC_CLK * 
                          (((2 * ((LPC_SC->PLL0STAT & 0x7FFF) + 1))) /
                          (((LPC_SC->PLL0STAT >> 16) & 0xFF) + 1))   /
                          ((LPC_SC->CCLKCFG & 0xFF)+ 1));
        break;
      case 2:                                /* RTC oscillator => PLL0        */
        SystemCoreClock = (RTC_CLK * 
                          (((2 * ((LPC_SC->PLL0STAT & 0x7FFF) + 1))) /
                          (((LPC_SC->PLL0STAT >> 16) & 0xFF) + 1))   /
                          ((LPC_SC->CCLKCFG & 0xFF)+ 1));
        break;
    }
  } else {
    switch (LPC_SC->CLKSRCSEL & 0x03) {
      case 0:                                /* Int. RC oscillator => PLL0    */
      case 3:                                /* Reserved, default to Int. RC  */
        SystemCoreClock = IRC_OSC / ((LPC_SC->CCLKCFG & 0xFF)+ 1);
        break;
      case 1:                                /* Main oscillator => PLL0       */
        SystemCoreClock = OSC_CLK / ((LPC_SC->CCLKCFG & 0xFF)+ 1);
        break;
      case 2:                                /* RTC oscillator => PLL0        */
        SystemCoreClock = RTC_CLK / ((LPC_SC->CCLKCFG & 0xFF)+ 1);
        break;
    }
  }
}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemFrequency variable.
 */
void SystemInit (void)
{
#if (CLOCK_SETUP)                       /* Clock Setup                        */
  LPC_SC->SCS       = SCS_Val;
  if (SCS_Val & (1 << 5)) {             /* If Main Oscillator is enabled      */
    while ((LPC_SC->SCS & (1 << 6)) == 0);  /* Wait for Oscillator to be ready    */
  }

  LPC_SC->CCLKCFG   = CCLKCFG_Val;          /* Setup Clock Divider                */

#if (PLL0_SETUP)
  LPC_SC->CLKSRCSEL = CLKSRCSEL_Val;        /* Select Clock Source for PLL0       */
  LPC_SC->PLL0CFG   = PLL0CFG_Val;
  LPC_SC->PLL0CON   = 0x01;                 /* PLL0 Enable                        */
  LPC_SC->PLL0FEED  = 0xAA;
  LPC_SC->PLL0FEED  = 0x55;
  while (!(LPC_SC->PLL0STAT & (1 << 26)));  /* Wait for PLOCK0                    */

  LPC_SC->PLL0CON   = 0x03;                 /* PLL0 Enable & Connect              */
  LPC_SC->PLL0FEED  = 0xAA;
  LPC_SC->PLL0FEED  = 0x55;
#endif

  LPC_SC->USBCLKCFG = USBCLKCFG_Val;        /* Setup USB Clock Divider            */
#endif

  LPC_SC->PCLKSEL0  = PCLKSEL0_Val;         /* Peripheral Clock Selection         */
  LPC_SC->PCLKSEL1  = PCLKSEL1_Val;

  LPC_SC->PCONP     = PCONP_Val;            /* Power Control for Peripherals      */
    
  // Setup MAM
  LPC_SC->MAMTIM      = MAMTIM_Val;
  LPC_SC->MAMCR       = MAMCR_Val;
}
