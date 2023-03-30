/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_CYW43_DRIVER_H
#define _PICO_CYW43_DRIVER_H

/** \file pico/cyw43_driver.h
 *  \defgroup pico_cyw43_driver pico_cyw43_driver
 *
 * A wrapper around the lower level cyw43_driver, that integrates it with \ref pico_async_context
 * for handling background work.
 */

#include "pico.h"
#include "pico/async_context.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Initializes the lower level cyw43_driver and integrates it with the provided async_context
 *  \ingroup pico_cyw43_driver
 *
 *  If the initialization succeeds, \ref lwip_nosys_deinit() can be called to shutdown lwIP support
 *
 * \param context the async_context instance that provides the abstraction for handling asynchronous work.
 * \return true if the initialization succeeded
*/
bool cyw43_driver_init(async_context_t *context);

/*! \brief De-initialize the lowever level cyw43_driver and unhooks it from the async_context
 *  \ingroup pico_cyw43_driver
 *
 * \param context the async_context the cyw43_driver support was added to via \ref cyw43_driver_init
*/
void cyw43_driver_deinit(async_context_t *context);

#ifdef __cplusplus
}
#endif
#endif