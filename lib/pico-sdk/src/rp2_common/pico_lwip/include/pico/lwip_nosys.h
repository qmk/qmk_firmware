/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_LWIP_NOSYS_H
#define _PICO_LWIP_NOSYS_H

#include "pico.h"
#include "pico/async_context.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file pico/lwip_nosys.h
* \defgroup pico_lwip_nosys pico_lwip_nosys
* \ingroup pico_lwip
* \brief Glue library for integration lwIP in \c NO_SYS=1 mode with the SDK. Simple \c init and \c deinit
* are all that is required to hook up lwIP via an \ref async_context instance.
*/

/*! \brief Initializes lwIP (NO_SYS=1 mode) support support using the provided async_context
*  \ingroup pico_lwip_nosys
*
*  If the initialization succeeds, \ref lwip_nosys_deinit() can be called to shutdown lwIP support
*
* \param context the async_context instance that provides the abstraction for handling asynchronous work.
* \return true if the initialization succeeded
*/
bool lwip_nosys_init(async_context_t *context);

/*! \brief De-initialize lwIP (NO_SYS=1 mode) support
 *  \ingroup pico_lwip_nosys
 *
 * Note that since lwIP may only be initialized once, and doesn't itself provide a shutdown mechanism, lwIP
 * itself may still consume resources
 *
 * It is however safe to call \ref lwip_nosys_init again later.
 *
 * \param context the async_context the lwip_nosys support was added to via \ref lwip_nosys_init
*/
void lwip_nosys_deinit(async_context_t *context);

#ifdef __cplusplus
}
#endif
#endif