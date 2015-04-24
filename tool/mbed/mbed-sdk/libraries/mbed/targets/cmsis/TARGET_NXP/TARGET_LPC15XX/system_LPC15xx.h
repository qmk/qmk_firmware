/**************************************************************************//**
 * @file     system_LPC15xx.h
 * @brief    CMSIS Cortex-M3 Device System Header File for
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


#ifndef __SYSTEM_LPC15xx_H
#define __SYSTEM_LPC15xx_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/** @addtogroup LPC15xx_System
 * @{
 */

extern uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  */


/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
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

/**
 * @}
 */

#endif /* __SYSTEM_LPC15xx_H */
