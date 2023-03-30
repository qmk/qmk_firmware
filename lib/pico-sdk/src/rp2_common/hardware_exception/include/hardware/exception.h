/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_EXCEPTION_H
#define _HARDWARE_EXCEPTION_H

#include "pico.h"
#include "hardware/address_mapped.h"
#include "hardware/regs/m0plus.h"

/** \file exception.h
 *  \defgroup hardware_exception hardware_exception
 *
 * Methods for setting processor exception handlers
 *
 * Exceptions are identified by a \ref exception_number which is a number from -15 to -1; these are the numbers relative to
 * the index of the first IRQ vector in the vector table. (i.e. vector table index is exception_num plus 16)
 *
 * There is one set of exception handlers per core, so the exception handlers for each core as set by these methods are independent.
 *
 * \note That all exception APIs affect the executing core only (i.e. the core calling the function).
 */

// PICO_CONFIG: PARAM_ASSERTIONS_ENABLED_EXCEPTION, Enable/disable assertions in the exception module, type=bool, default=0, group=hardware_exception
#ifndef PARAM_ASSERTIONS_ENABLED_EXCEPTION
#define PARAM_ASSERTIONS_ENABLED_EXCEPTION 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief  Exception number definitions
 *
 * Note for consistency with irq numbers, these numbers are defined to be negative. The VTABLE index is
 * the number here plus 16.
 *
 * Name                 | Value | Exception
 * ---------------------|-------|----------
 * NMI_EXCEPTION        |  -14  | Non Maskable Interrupt
 * HARDFAULT_EXCEPTION  |  -13  | HardFault
 * SVCALL_EXCEPTION     |   -5  | SV Call
 * PENDSV_EXCEPTION     |   -2  | Pend SV
 * SYSTICK_EXCEPTION    |   -1  | System Tick
 *
 * \ingroup hardware_exception
 */
enum exception_number {
    NMI_EXCEPTION        = -14,     /* Non Maskable Interrupt */
    HARDFAULT_EXCEPTION  = -13,     /* HardFault Interrupt */
    SVCALL_EXCEPTION     =  -5,     /* SV Call Interrupt */
    PENDSV_EXCEPTION     =  -2,     /* Pend SV Interrupt */
    SYSTICK_EXCEPTION    =  -1,     /* System Tick Interrupt */
};

/*! \brief Exception handler function type
 *  \ingroup hardware_exception
 *
 * All exception handlers should be of this type, and follow normal ARM EABI register saving conventions
 */
typedef void (*exception_handler_t)(void);

/*! \brief  Set the exception handler for an exception on the executing core.
 *  \ingroup hardware_exception
 *
 * This method will assert if an exception handler has been set for this exception number on this core via
 * this method, without an intervening restore via exception_restore_handler.
 *
 * \note this method may not be used to override an exception handler that was specified at link time by
 * providing a strong replacement for the weakly defined stub exception handlers. It will assert in this case too.
 *
 * \param num Exception number
 * \param handler The handler to set
 * \see exception_number
 */
exception_handler_t exception_set_exclusive_handler(enum exception_number num, exception_handler_t handler);

/*! \brief Restore the original exception handler for an exception on this core
 *  \ingroup hardware_exception
 *
 * This method may be used to restore the exception handler for an exception on this core to the state
 * prior to the call to exception_set_exclusive_handler(), so that exception_set_exclusive_handler()
 * may be called again in the future.
 *
 * \param num Exception number \ref exception_number
 * \param original_handler The original handler returned from \ref exception_set_exclusive_handler
 * \see exception_set_exclusive_handler()
 */
void exception_restore_handler(enum exception_number num, exception_handler_t original_handler);

/*! \brief Get the current exception handler for the specified exception from the currently installed vector table
 * of the execution core
 *  \ingroup hardware_exception
 *
 * \param num Exception number
 * \return the address stored in the VTABLE for the given exception number
 */
exception_handler_t exception_get_vtable_handler(enum exception_number num);
#ifdef __cplusplus
}
#endif

#endif
