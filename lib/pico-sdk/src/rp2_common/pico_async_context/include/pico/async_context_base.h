/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_ASYNC_CONTEXT_BASE_H
#define _PICO_ASYNC_CONTEXT_BASE_H

#include "pico/async_context.h"

#ifdef __cplusplus
extern "C" {
#endif

// common functions for async_context implementations to use
bool async_context_base_add_at_time_worker(async_context_t *self, async_at_time_worker_t *worker);
bool async_context_base_remove_at_time_worker(async_context_t *self, async_at_time_worker_t *worker);

bool async_context_base_add_when_pending_worker(async_context_t *self, async_when_pending_worker_t *worker);
bool async_context_base_remove_when_pending_worker(async_context_t *self, async_when_pending_worker_t *worker);

async_at_time_worker_t *async_context_base_remove_ready_at_time_worker(async_context_t *self);
void async_context_base_refresh_next_timeout(async_context_t *self);

absolute_time_t async_context_base_execute_once(async_context_t *self);
bool async_context_base_needs_servicing(async_context_t *self);

#ifdef __cplusplus
}
#endif

#endif