/*
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_BTSTACK_CYW43_H
#define _PICO_BTSTACK_CYW43_H

#include "pico/async_context.h"
#ifdef __cplusplus
extern "C" {
#endif

/** \file pico/btstack_cyw43.h
 * \defgroup pico_bstack_cyw43
 * \ingroup pico_cyw43_driver
 *
 * \brief Low-level Bluetooth HCI support.
 *
 * This library provides utility functions to initialise and de-initialise BTstack for CYW43,
*/

/*
 * \brief Perform initialisation of BTstack/CYW43 integration
 * \ingroup pico_btstack_cyw43
 *
 * \param context the async_context instance that provides the abstraction for handling asynchronous work.
 * \return true on success or false an error
 */
bool btstack_cyw43_init(async_context_t *context);

/*
 * \brief De-initialise BTstack/CYW43 integration
 * \ingroup pico_btstack_cyw43
 *
 * \param context the async_context the btstack_cyw43 support was added to via \ref btstack_cyw43_init
 */
void btstack_cyw43_deinit(async_context_t *context);

#ifdef __cplusplus
}
#endif
#endif
