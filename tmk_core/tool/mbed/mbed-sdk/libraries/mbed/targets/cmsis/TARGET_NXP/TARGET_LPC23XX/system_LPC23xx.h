/* mbed Microcontroller Library
 * Copyright (C) 2008-2009 ARM Limited. All rights reserved.
 *
 * ARM7 version of CMSIS-like functionality - not advised for use outside mbed!
 * based on cmsis system_LPC17xx.h 
 */

#ifndef __SYSTEM_LPC23xx_H
#define __SYSTEM_LPC23xx_H

#ifdef __cplusplus
 extern "C" {
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

/**
 * Update SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * @brief  Updates the SystemCoreClock with current core Clock 
 *         retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate (void);


#ifdef __cplusplus
}
#endif 

#endif
