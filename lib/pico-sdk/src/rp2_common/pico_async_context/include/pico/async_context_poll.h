/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_ASYNC_CONTEXT_POLL_H
#define _PICO_ASYNC_CONTEXT_POLL_H

/** \file pico/async_context.h
 *  \defgroup async_context_poll async_context_poll
 *  \ingroup pico_async_context
 *
 * async_context_poll provides an implementation of \ref async_context that is intended for use with a simple
 * polling loop on one core. It is not thread safe.
 *
 * The \ref async_context_poll() method must be called periodically to handle asynchronous work that may now be
 * pending. \ref async_context_wait_for_work_until() may be used to block a polling loop until there is work to do,
 * and prevent tight spinning.
 */
#include "pico/async_context.h"
#include "pico/sem.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct async_context_poll {
    async_context_t core;
    semaphore_t sem;
} async_context_poll_t;

/*!
 * \brief Initialize an async_context_poll instance with default values
 * \ingroup async_context_poll
 *
 * If this method succeeds (returns true), then the async_context is available for use
 * and can be de-initialized by calling async_context_deinit().
 *
 * \param self a pointer to async_context_poll structure to initialize
 * \return true if initialization is successful, false otherwise
 */
bool async_context_poll_init_with_defaults(async_context_poll_t *self);

#ifdef __cplusplus
}
#endif

#endif