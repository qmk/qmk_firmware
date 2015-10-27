/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(__FSL_INTERRUPT_MANAGER_H__)
#define __FSL_INTERRUPT_MANAGER_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_interrupt_features.h"
#include "device/fsl_device_registers.h"

/*! @addtogroup interrupt_manager*/
/*! @{*/

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name interrupt_manager APIs*/
/*@{*/

/*!
 * @brief Installs an interrupt handler routine for a given IRQ number. 
 *
 * This function lets the application  register/replace the interrupt 
 * handler for a specified IRQ number. The IRQ number is different than the vector
 * number. IRQ 0  starts from the vector 16 address. See a chip-specific reference
 * manual for details and the  startup_MKxxxx.s file for each chip
 * family to find out the default interrupt handler for each device. This
 * function converts the IRQ number to the vector number by adding 16 to
 * it. 
 *
 * @param irqNumber IRQ number
 * @param handler   Interrupt handler routine address pointer
 */
void INT_SYS_InstallHandler(IRQn_Type irqNumber, void (*handler)(void));

/*!
 * @brief Enables an interrupt for a given IRQ number. 
 *
 * This function  enables the individual interrupt for a specified IRQ
 * number. It calls the system NVIC API to access the interrupt control
 * register. The input IRQ number does not include the core interrupt, only
 * the peripheral interrupt, from 0 to a maximum supported IRQ.
 *
 * @param irqNumber IRQ number
 */
static inline void INT_SYS_EnableIRQ(IRQn_Type irqNumber)
{
    /* check IRQ number */
    assert(0 <= irqNumber);
    assert(irqNumber <= FSL_FEATURE_INTERRUPT_IRQ_MAX);

    /* call core API to enable the IRQ*/
    NVIC_EnableIRQ(irqNumber);
}

/*!
 * @brief Disables an interrupt for a given IRQ number. 
 *
 * This function  enables the individual interrupt for a specified IRQ
 * number. It  calls the system NVIC API to access the interrupt control
 * register.
 *
 * @param irqNumber IRQ number
 */
static inline void INT_SYS_DisableIRQ(IRQn_Type irqNumber)
{
    /* check IRQ number */
    assert(0 <= irqNumber);
    assert(irqNumber <= FSL_FEATURE_INTERRUPT_IRQ_MAX);

    /* call core API to disable the IRQ*/
    NVIC_DisableIRQ(irqNumber);
}

/*!
 * @brief Enables system interrupt.
 *
 * This function  enables the global interrupt by calling the core API.
 *
 */
void INT_SYS_EnableIRQGlobal(void);

/*!
 * @brief Disable system interrupt. 
 *
 * This function  disables the global interrupt by calling the core API.
 *
 */
void INT_SYS_DisableIRQGlobal(void);

/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* __FSL_INTERRUPT_MANAGER_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

