/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_LWIP_FREERTOS_H
#define _PICO_LWIP_FREERTOS_H

#include "pico.h"
#include "pico/async_context.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file pico/lwip_freertos.h
* \defgroup pico_lwip_freertos pico_lwip_freertos
* \ingroup pico_lwip
* \brief Glue library for integration lwIP in \c NO_SYS=0 mode with the SDK. Simple \c init and \c deinit
* are all that is required to hook up lwIP (with full blocking API support) via an \ref async_context instance.
*/

/*! \brief Initializes lwIP (NO_SYS=0 mode) support support for FreeRTOS using the provided async_context
 *  \ingroup pico_lwip_freertos
 *
 * If the initialization succeeds, \ref lwip_freertos_deinit() can be called to shutdown lwIP support
 *
 * \param context the async_context instance that provides the abstraction for handling asynchronous work. Note in general
 * this would be an \ref async_context_freertos instance, though it doesn't have to be.
 *
 * \return true if the initialization succeeded
*/
bool lwip_freertos_init(async_context_t *context);

/*! \brief De-initialize lwIP (NO_SYS=0 mode) support for FreeRTOS
 *  \ingroup pico_lwip_freertos
 *
 * Note that since lwIP may only be initialized once, and doesn't itself provide a shutdown mechanism, lwIP
 * itself may still consume resources.
 *
 * It is however safe to call \ref lwip_freertos_init again later.
 *
 * \param context the async_context the lwip_freertos support was added to via \ref lwip_freertos_init
*/
void lwip_freertos_deinit(async_context_t *context);

#ifdef __cplusplus
}
#endif
#endif