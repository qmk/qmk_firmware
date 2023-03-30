/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_ASYNC_CONTEXT_THREADSAFE_BACKGROUND_H
#define _PICO_ASYNC_CONTEXT_THREADSAFE_BACKGROUND_H

/** \file pico/async_context.h
 *  \defgroup async_context_threadsafe_background async_context_threadsafe_background
 *  \ingroup pico_async_context
 *  
 * async_context_threadsafe_background provides an implementation of \ref async_context that handles asynchronous
 * work in a low priority IRQ, and there is no need for the user to poll for work.
 *
 * \note The workers used with this async_context MUST be safe to call from an IRQ.
 */

#include "pico/async_context.h"
#include "pico/sem.h"
#include "pico/mutex.h"
#include "hardware/irq.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ASYNC_CONTEXT_THREADSAFE_BACKGROUND_MULTI_CORE
#define ASYNC_CONTEXT_THREADSAFE_BACKGROUND_MULTI_CORE LIB_PICO_MULTICORE
#endif

typedef struct async_context_threadsafe_background async_context_threadsafe_background_t;

/**
 * \brief Configuration object for async_context_threadsafe_background instances.
 */
typedef struct async_context_threadsafe_background_config {
/**
 * the priority of the low priority IRQ
 */
    uint8_t low_priority_irq_handler_priority;
    /**
     * a specific alarm pool to use (or NULL to use ta default)
     *
     * \note this alarm pool MUST be on the same core as the async_context
     *
     * The default alarm pool used is the "default alarm pool" (see
     * \ref alarm_pool_get_default()) if available, and if that is on the same
     * core, otherwise a private alarm_pool instance created during
     * initialization.
     */
    alarm_pool_t *custom_alarm_pool;
} async_context_threadsafe_background_config_t;

struct async_context_threadsafe_background {
    async_context_t core;
    alarm_pool_t *alarm_pool; // this must be on the same core as core_num
    absolute_time_t last_set_alarm_time;
    recursive_mutex_t lock_mutex;
    semaphore_t work_needed_sem;
    volatile alarm_id_t alarm_id;
#if ASYNC_CONTEXT_THREADSAFE_BACKGROUND_MULTI_CORE
    volatile alarm_id_t force_alarm_id;
    bool alarm_pool_owned;
#endif
    uint8_t low_priority_irq_num;
    volatile bool alarm_pending;
};

/*!
 * \brief Initialize an async_context_threadsafe_background instance using the specified configuration
 * \ingroup async_context_threadsafe_background
 *
 * If this method succeeds (returns true), then the async_context is available for use
 * and can be de-initialized by calling async_context_deinit().
 * 
 * \param self a pointer to async_context_threadsafe_background structure to initialize
 * \param config the configuration object specifying characteristics for the async_context
 * \return true if initialization is successful, false otherwise
 */
bool async_context_threadsafe_background_init(async_context_threadsafe_background_t *self, async_context_threadsafe_background_config_t *config);

/*!
 * \brief Return a copy of the default configuration object used by \ref async_context_threadsafe_background_init_with_defaults() 
 * \ingroup async_context_threadsafe_background
 *
 * The caller can then modify just the settings it cares about, and call \ref async_context_threasafe_background_init()
 * \return the default configuration object
 */
async_context_threadsafe_background_config_t async_context_threadsafe_background_default_config(void);

/*!
 * \brief Initialize an async_context_threadsafe_background instance with default values
 * \ingroup async_context_threadsafe_background
 *
 * If this method succeeds (returns true), then the async_context is available for use
 * and can be de-initialized by calling async_context_deinit().
 * 
 * \param self a pointer to async_context_threadsafe_background structure to initialize
 * \return true if initialization is successful, false otherwise
 */
static inline bool async_context_threadsafe_background_init_with_defaults(async_context_threadsafe_background_t *self) {
    async_context_threadsafe_background_config_t config = async_context_threadsafe_background_default_config();
    return async_context_threadsafe_background_init(self, &config);
}

#ifdef __cplusplus
}
#endif

#endif