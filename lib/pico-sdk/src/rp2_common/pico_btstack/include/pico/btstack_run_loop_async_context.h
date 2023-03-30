/*
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_BTSTACK_RUN_LOOP_ASYNC_CONTEXT_H
#define _PICO_BTSTACK_RUN_LOOP_ASYNC_CONTEXT_H

#include "btstack_run_loop.h"
#include "pico/async_context.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Initialize and eturn the singleton BTstack run loop instance that integrates with the async_context API
 * \ingroup pico_btstack
 *
 * \param context the async_context instance that provides the abstraction for handling asynchronous work.
 * \return the BTstack run loop instance
 */
const btstack_run_loop_t *btstack_run_loop_async_context_get_instance(async_context_t *context);

#ifdef __cplusplus
}
#endif
#endif
