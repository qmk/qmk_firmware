/*
 * @brief LPC43xx/LPC18xx mcu header
 *
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __SYSTEM_LPC43XX_H
#define __SYSTEM_LPC43XX_H

#ifdef __cplusplus
extern "C" {
#endif

/* System initialization options */
#define PIN_SETUP             1 /* Configure pins during initialization */
#define CLOCK_SETUP           1 /* Configure clocks during initialization */
#define MEMORY_SETUP          0 /* Configure external memory during init */
#define SPIFI_INIT            1 /* Initialize SPIFI */

/* Crystal frequency into device */
#define CRYSTAL_MAIN_FREQ_IN 12000000

/* Crystal frequency into device for RTC/32K input */
#define CRYSTAL_32K_FREQ_IN 32768

/* Default CPU clock frequency */
#if defined(CHIP_LPC43XX)
#define MAX_CLOCK_FREQ (204000000)
#else
#define MAX_CLOCK_FREQ (180000000)
#endif

#if defined(__FPU_PRESENT) && __FPU_PRESENT == 1
  /* FPU declarations */
  #define LPC_CPACR	          0xE000ED88

  #define SCB_MVFR0           0xE000EF40
  #define SCB_MVFR0_RESET     0x10110021

  #define SCB_MVFR1           0xE000EF44
  #define SCB_MVFR1_RESET     0x11000011

  #if defined(__ARMCC_VERSION)
    void fpuInit(void) __attribute__ ((section("BOOTSTRAP_CODE")));
  #else
    extern void fpuInit(void);
  #endif
#endif

extern uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  */

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit (void);
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_LPC43XX_H */
