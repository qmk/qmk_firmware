/*
** ###################################################################
**     Processor:           MK64FN1M0VMD12
**     Compilers:           Keil ARM C/C++ Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          GNU C Compiler - CodeSourcery Sourcery G++
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    K64P144M120SF5RM, Rev.2, January 2014
**     Version:             rev. 2.5, 2014-02-10
**     Build:               b140611
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright (c) 2014 Freescale Semiconductor, Inc.
**     All rights reserved.
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2013-08-12)
**         Initial version.
**     - rev. 2.0 (2013-10-29)
**         Register accessor macros added to the memory map.
**         Symbols for Processor Expert memory map compatibility added to the memory map.
**         Startup file for gcc has been updated according to CMSIS 3.2.
**         System initialization updated.
**         MCG - registers updated.
**         PORTA, PORTB, PORTC, PORTE - registers for digital filter removed.
**     - rev. 2.1 (2013-10-30)
**         Definition of BITBAND macros updated to support peripherals with 32-bit acces disabled.
**     - rev. 2.2 (2013-12-09)
**         DMA - EARS register removed.
**         AIPS0, AIPS1 - MPRA register updated.
**     - rev. 2.3 (2014-01-24)
**         Update according to reference manual rev. 2
**         ENET, MCG, MCM, SIM, USB - registers updated
**     - rev. 2.4 (2014-02-10)
**         The declaration of clock configurations has been moved to separate header file system_MK64F12.h
**         Update of SystemInit() and SystemCoreClockUpdate() functions.
**     - rev. 2.5 (2014-02-10)
**         The declaration of clock configurations has been moved to separate header file system_MK64F12.h
**         Update of SystemInit() and SystemCoreClockUpdate() functions.
**         Module access macro module_BASES replaced by module_BASE_PTRS.
**
** ###################################################################
*/

/*!
 * @file MK64F12
 * @version 2.5
 * @date 2014-02-10
 * @brief Device specific configuration file for MK64F12 (header file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#ifndef SYSTEM_MK64F12_H_
#define SYSTEM_MK64F12_H_                        /**< Symbol preventing repeated inclusion */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


#define DISABLE_WDOG                   1

#ifndef CLOCK_SETUP
  #define CLOCK_SETUP                  4
#endif

/* MCG mode constants */

#define MCG_MODE_FEI                   0U
#define MCG_MODE_FBI                   1U
#define MCG_MODE_BLPI                  2U
#define MCG_MODE_FEE                   3U
#define MCG_MODE_FBE                   4U
#define MCG_MODE_BLPE                  5U
#define MCG_MODE_PBE                   6U
#define MCG_MODE_PEE                   7U

/* Predefined clock setups
   0 ... Default  part configuration
         Multipurpose Clock Generator (MCG) in FEI mode.
         Reference clock source for MCG module: Slow internal reference clock
         Core clock = 20.97152MHz
         Bus clock  = 20.97152MHz
   1 ... Maximum achievable clock frequency configuration
         Multipurpose Clock Generator (MCG) in PEE mode.
         Reference clock source for MCG module: System oscillator 0 reference clock
         Core clock = 120MHz
         Bus clock  = 60MHz
   2 ... Chip internaly clocked, ready for Very Low Power Run mode.
         Multipurpose Clock Generator (MCG) in BLPI mode.
         Reference clock source for MCG module: Fast internal reference clock
         Core clock = 4MHz
         Bus clock  = 4MHz
   3 ... Chip externally clocked, ready for Very Low Power Run mode.
         Multipurpose Clock Generator (MCG) in BLPE mode.
         Reference clock source for MCG module: RTC oscillator reference clock
         Core clock = 0.032768MHz
         Bus clock  = 0.032768MHz
   4 ... USB clock setup
         Multipurpose Clock Generator (MCG) in PEE mode.
         Reference clock source for MCG module: System oscillator 0 reference clock
         Core clock = 120MHz
         Bus clock  = 60MHz
 */

/* Define clock source values */

#define CPU_XTAL_CLK_HZ                50000000u           /* Value of the external crystal or oscillator clock frequency in Hz */
#define CPU_XTAL32k_CLK_HZ             32768u              /* Value of the external 32k crystal or oscillator clock frequency in Hz */
#define CPU_INT_SLOW_CLK_HZ            32768u              /* Value of the slow internal oscillator clock frequency in Hz  */
#define CPU_INT_FAST_CLK_HZ            4000000u            /* Value of the fast internal oscillator clock frequency in Hz  */
#define CPU_INT_IRC_CLK_HZ             48000000u           /* Value of the 48M internal oscillator clock frequency in Hz  */

/* RTC oscillator setting */
/* RTC_CR: SC2P=0,SC4P=0,SC8P=0,SC16P=0,CLKO=1,OSCE=1,WPS=0,UM=0,SUP=0,WPE=0,SWR=0 */
#define SYSTEM_RTC_CR_VALUE            0x0300U             /* RTC_CR */

/* Low power mode enable */
/* SMC_PMPROT: AVLP=1,ALLS=1,AVLLS=1 */
#define SYSTEM_SMC_PMPROT_VALUE        0x2AU               /* SMC_PMPROT */

/* Internal reference clock trim */
/* #undef SLOW_TRIM_ADDRESS */                             /* Slow oscillator not trimmed. Commented out for MISRA compliance. */
/* #undef SLOW_FINE_TRIM_ADDRESS */                        /* Slow oscillator not trimmed. Commented out for MISRA compliance. */
/* #undef FAST_TRIM_ADDRESS */                             /* Fast oscillator not trimmed. Commented out for MISRA compliance. */
/* #undef FAST_FINE_TRIM_ADDRESS */                        /* Fast oscillator not trimmed. Commented out for MISRA compliance. */

#if (CLOCK_SETUP == 0)
  #define DEFAULT_SYSTEM_CLOCK         20971520u           /* Default System clock value */
  #define MCG_MODE                     MCG_MODE_FEI /* Clock generator mode */
  /* MCG_C1: CLKS=0,FRDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE          0x06U               /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE=2,HGO=0,EREFS=0,LP=0,IRCS=0 */
  #define SYSTEM_MCG_C2_VALUE          0x20U               /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE          0x00U               /* MCG_C4 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=0,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE          0x00U               /* MCG_SC */
/* MCG_C5: PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=0 */
  #define SYSTEM_MCG_C5_VALUE          0x00U               /* MCG_C5 */
/* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
  #define SYSTEM_MCG_C6_VALUE          0x00U               /* MCG_C6 */
/* MCG_C7: OSCSEL=0 */
  #define SYSTEM_MCG_C7_VALUE          0x00U               /* MCG_C7 */
/* OSC_CR: ERCLKEN=0,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC_CR_VALUE          0x00U               /* OSC_CR */
/* SMC_PMCTRL: LPWUI=0,RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
/* SIM_CLKDIV1: OUTDIV1=0,OUTDIV2=0,OUTDIV3=1,OUTDIV4=1 */
  #define SYSTEM_SIM_CLKDIV1_VALUE     0x00110000U         /* SIM_CLKDIV1 */
/* SIM_SOPT1: USBREGEN=0,USBSSTBY=0,USBVSTBY=0,OSC32KSEL=2,RAMSIZE=0 */
  #define SYSTEM_SIM_SOPT1_VALUE       0x00080000U         /* SIM_SOPT1 */
/* SIM_SOPT2: SDHCSRC=0,TIMESRC=0,RMIISRC=0,USBSRC=0,PLLFLLSEL=0,TRACECLKSEL=0,PTD7PAD=0,FBSL=0,CLKOUTSEL=0,RTCCLKOUTSEL=0 */
  #define SYSTEM_SIM_SOPT2_VALUE       0x00U               /* SIM_SOPT2 */
#elif (CLOCK_SETUP == 1)
  #define DEFAULT_SYSTEM_CLOCK         120000000u          /* Default System clock value */
  #define MCG_MODE                     MCG_MODE_PEE /* Clock generator mode */
  /* MCG_C1: CLKS=0,FRDIV=7,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE          0x3AU               /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE=2,HGO=0,EREFS=0,LP=0,IRCS=0 */
  #define SYSTEM_MCG_C2_VALUE          0x20U               /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE          0x00U               /* MCG_C4 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=0,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE          0x00U               /* MCG_SC */
/* MCG_C5: PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=0x13 */
  #define SYSTEM_MCG_C5_VALUE          0x13U               /* MCG_C5 */
/* MCG_C6: LOLIE0=0,PLLS=1,CME0=0,VDIV0=0x18 */
  #define SYSTEM_MCG_C6_VALUE          0x58U               /* MCG_C6 */
/* MCG_C7: OSCSEL=0 */
  #define SYSTEM_MCG_C7_VALUE          0x00U               /* MCG_C7 */
/* OSC_CR: ERCLKEN=1,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC_CR_VALUE          0x80U               /* OSC_CR */
/* SMC_PMCTRL: LPWUI=0,RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
/* SIM_CLKDIV1: OUTDIV1=0,OUTDIV2=1,OUTDIV3=1,OUTDIV4=4 */
  #define SYSTEM_SIM_CLKDIV1_VALUE     0x01140000U         /* SIM_CLKDIV1 */
/* SIM_SOPT1: USBREGEN=0,USBSSTBY=0,USBVSTBY=0,OSC32KSEL=2,RAMSIZE=0 */
  #define SYSTEM_SIM_SOPT1_VALUE       0x00080000U         /* SIM_SOPT1 */
/* SIM_SOPT2: SDHCSRC=0,TIMESRC=0,RMIISRC=0,USBSRC=0,PLLFLLSEL=1,TRACECLKSEL=0,PTD7PAD=0,FBSL=0,CLKOUTSEL=0,RTCCLKOUTSEL=0 */
  #define SYSTEM_SIM_SOPT2_VALUE       0x00010000U         /* SIM_SOPT2 */
#elif (CLOCK_SETUP == 2)
  #define DEFAULT_SYSTEM_CLOCK         4000000u            /* Default System clock value */
  #define MCG_MODE                     MCG_MODE_BLPI /* Clock generator mode */
  /* MCG_C1: CLKS=1,FRDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE          0x46U               /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE=2,HGO=0,EREFS=0,LP=1,IRCS=1 */
  #define SYSTEM_MCG_C2_VALUE          0x23U               /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE          0x00U               /* MCG_C4 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=0,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE          0x00U               /* MCG_SC */
/* MCG_C5: PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=0 */
  #define SYSTEM_MCG_C5_VALUE          0x00U               /* MCG_C5 */
/* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
  #define SYSTEM_MCG_C6_VALUE          0x00U               /* MCG_C6 */
/* MCG_C7: OSCSEL=0 */
  #define SYSTEM_MCG_C7_VALUE          0x00U               /* MCG_C7 */
/* OSC_CR: ERCLKEN=1,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC_CR_VALUE          0x80U               /* OSC_CR */
/* SMC_PMCTRL: LPWUI=0,RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
/* SIM_CLKDIV1: OUTDIV1=0,OUTDIV2=0,OUTDIV3=0,OUTDIV4=4 */
  #define SYSTEM_SIM_CLKDIV1_VALUE     0x00040000U         /* SIM_CLKDIV1 */
/* SIM_SOPT1: USBREGEN=0,USBSSTBY=0,USBVSTBY=0,OSC32KSEL=2,RAMSIZE=0 */
  #define SYSTEM_SIM_SOPT1_VALUE       0x00080000U         /* SIM_SOPT1 */
/* SIM_SOPT2: SDHCSRC=0,TIMESRC=0,RMIISRC=0,USBSRC=0,PLLFLLSEL=3,TRACECLKSEL=0,PTD7PAD=0,FBSL=0,CLKOUTSEL=0,RTCCLKOUTSEL=0 */
  #define SYSTEM_SIM_SOPT2_VALUE       0x00030000U         /* SIM_SOPT2 */
#elif (CLOCK_SETUP == 3)
  #define DEFAULT_SYSTEM_CLOCK         32768u              /* Default System clock value */
  #define MCG_MODE                     MCG_MODE_BLPE /* Clock generator mode */
  /* MCG_C1: CLKS=2,FRDIV=0,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE          0x82U               /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE=2,HGO=0,EREFS=0,LP=1,IRCS=1 */
  #define SYSTEM_MCG_C2_VALUE          0x23U               /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE          0x00U               /* MCG_C4 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=1,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE          0x02U               /* MCG_SC */
/* MCG_C5: PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=0 */
  #define SYSTEM_MCG_C5_VALUE          0x00U               /* MCG_C5 */
/* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
  #define SYSTEM_MCG_C6_VALUE          0x00U               /* MCG_C6 */
/* MCG_C7: OSCSEL=1 */
  #define SYSTEM_MCG_C7_VALUE          0x01U               /* MCG_C7 */
/* OSC_CR: ERCLKEN=0,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC_CR_VALUE          0x00U               /* OSC_CR */
/* SMC_PMCTRL: LPWUI=0,RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
/* SIM_CLKDIV1: OUTDIV1=0,OUTDIV2=0,OUTDIV3=0,OUTDIV4=0 */
  #define SYSTEM_SIM_CLKDIV1_VALUE     0x00U               /* SIM_CLKDIV1 */
/* SIM_SOPT1: USBREGEN=0,USBSSTBY=0,USBVSTBY=0,OSC32KSEL=2,RAMSIZE=0 */
  #define SYSTEM_SIM_SOPT1_VALUE       0x00080000U         /* SIM_SOPT1 */
/* SIM_SOPT2: SDHCSRC=0,TIMESRC=0,RMIISRC=0,USBSRC=0,PLLFLLSEL=3,TRACECLKSEL=0,PTD7PAD=0,FBSL=0,CLKOUTSEL=0,RTCCLKOUTSEL=0 */
  #define SYSTEM_SIM_SOPT2_VALUE       0x00030000U         /* SIM_SOPT2 */
#elif (CLOCK_SETUP == 4)
  #define DEFAULT_SYSTEM_CLOCK         120000000u          /* Default System clock value */
  #define MCG_MODE                     MCG_MODE_PEE /* Clock generator mode */
  /* MCG_C1: CLKS=0,FRDIV=7,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE          0x3AU               /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE=2,HGO=0,EREFS=0,LP=0,IRCS=0 */
  #define SYSTEM_MCG_C2_VALUE          0x20U               /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE          0x00U               /* MCG_C4 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=0,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE          0x00U               /* MCG_SC */
/* MCG_C5: PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=0x13 */
  #define SYSTEM_MCG_C5_VALUE          0x13U               /* MCG_C5 */
/* MCG_C6: LOLIE0=0,PLLS=1,CME0=0,VDIV0=0x18 */
  #define SYSTEM_MCG_C6_VALUE          0x58U               /* MCG_C6 */
/* MCG_C7: OSCSEL=0 */
  #define SYSTEM_MCG_C7_VALUE          0x00U               /* MCG_C7 */
/* OSC_CR: ERCLKEN=1,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC_CR_VALUE          0x80U               /* OSC_CR */
/* SMC_PMCTRL: LPWUI=0,RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
/* SIM_CLKDIV1: OUTDIV1=0,OUTDIV2=1,OUTDIV3=1,OUTDIV4=4 */
  #define SYSTEM_SIM_CLKDIV1_VALUE     0x01140000U         /* SIM_CLKDIV1 */
/* SIM_CLKDIV2: USBDIV=4,USBFRAC=1 */
  #define SYSTEM_SIM_CLKDIV2_VALUE     0x09U               /* SIM_CLKDIV2 */
/* SIM_SOPT1: USBREGEN=0,USBSSTBY=0,USBVSTBY=0,OSC32KSEL=2,RAMSIZE=0 */
  #define SYSTEM_SIM_SOPT1_VALUE       0x00080000U         /* SIM_SOPT1 */
/* SIM_SOPT2: SDHCSRC=0,TIMESRC=0,RMIISRC=0,USBSRC=0,PLLFLLSEL=1,TRACECLKSEL=0,PTD7PAD=0,FBSL=0,CLKOUTSEL=0,RTCCLKOUTSEL=0 */
  #define SYSTEM_SIM_SOPT2_VALUE       0x00010000U         /* SIM_SOPT2 */
#endif

/**
 * @brief System clock frequency (core clock)
 *
 * The system clock frequency supplied to the SysTick timer and the processor
 * core clock. This variable can be used by the user application to setup the
 * SysTick timer or configure other parameters. It may also be used by debugger to
 * query the frequency of the debug timer or configure the trace clock speed
 * SystemCoreClock is initialized with a correct predefined value.
 */
extern uint32_t SystemCoreClock;

/**
 * @brief Setup the microcontroller system.
 *
 * Typically this function configures the oscillator (PLL) that is part of the
 * microcontroller device. For systems with variable clock speed it also updates
 * the variable SystemCoreClock. SystemInit is called from startup_device file.
 */
void SystemInit (void);

/**
 * @brief Updates the SystemCoreClock variable.
 *
 * It must be called whenever the core clock is changed during program
 * execution. SystemCoreClockUpdate() evaluates the clock register settings and calculates
 * the current core clock.
 */
void SystemCoreClockUpdate (void);

#ifdef __cplusplus
}
#endif

#endif  /* #if !defined(SYSTEM_MK64F12_H_) */
