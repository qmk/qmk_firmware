// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

//------------------------------------
// Common
//------------------------------------

/**
 * @typedef A token that can be used to cancel or extend an existing deferred execution.
 */
typedef uint8_t deferred_token;

/**
 * @def The constant used to denote an invalid deferred execution token.
 */
#define INVALID_DEFERRED_TOKEN 0

/**
 * @typedef Callback to execute.
 * @param trigger_time[in] the intended trigger time to execute the callback -- equivalent time-space as timer_read32()
 * @param cb_arg[in] the callback argument specified when enqueueing the deferred executor
 * @return non-zero re-queues the callback to execute after the returned number of milliseconds. Zero cancels repeated execution.
 */
typedef uint32_t (*deferred_exec_callback)(uint32_t trigger_time, void *cb_arg);

//------------------------------------
// Basic API: used by user-mode code, guaranteed to not collide with core deferred execution
//------------------------------------

/**
 * Configures the supplied deferred executor to be executed after the required number of milliseconds.
 *
 * @param delay_ms[in] the number of milliseconds before executing the callback
 * @param callback[in] the executor to invoke
 * @param cb_arg[in] the argument to pass to the executor, may be NULL if unused by the executor
 * @return a token usable for extension/cancellation, or INVALID_DEFERRED_TOKEN if an error occurred
 */
deferred_token defer_exec(uint32_t delay_ms, deferred_exec_callback callback, void *cb_arg);

/**
 * Allows for extending the timeframe before an existing deferred execution is invoked.
 *
 * @param token[in] the returned value from defer_exec for the deferred execution you wish to extend
 * @param delay_ms[in] the number of milliseconds before executing the callback
 * @return true if the token was extended successfully, otherwise false
 */
bool extend_deferred_exec(deferred_token token, uint32_t delay_ms);

/**
 * Allows for cancellation of an existing deferred execution.
 *
 * @param token[in] the returned value from defer_exec for the deferred execution you wish to cancel
 * @return true if the token was cancelled successfully, otherwise false
 */
bool cancel_deferred_exec(deferred_token token);

/**
 * Forward declaration for the main loop in order to execute any deferred executors. Should not be invoked by keyboard/user code.
 */
void deferred_exec_task(void);

//------------------------------------
// Advanced API: used when a custom-allocated table is used, primarily for core code.
//------------------------------------

/**
 * @struct Structure for containing self-hosted deferred executor tables.
 * @brief Core-side code can use this to create their own tables without impacting on the use of users' ability to add deferred execution.
 *        Code outside deferred_exec.c should not worry about internals of this struct, and should just allocate the required number in an array.
 */
typedef struct deferred_executor_t {
    deferred_token         token;
    uint32_t               trigger_time;
    deferred_exec_callback callback;
    void                  *cb_arg;
} deferred_executor_t;

/**
 * Configures the supplied deferred executor to be executed after the required number of milliseconds.
 *
 * @param table[in] the custom table used for storage
 * @param table_count[in] the number of available items in the table
 * @param delay_ms[in] the number of milliseconds before executing the callback
 * @param callback[in] the executor to invoke
 * @param cb_arg[in] the argument to pass to the executor, may be NULL if unused by the executor
 * @return a token usable for extension/cancellation, or INVALID_DEFERRED_TOKEN if an error occurred
 */
deferred_token defer_exec_advanced(deferred_executor_t *table, size_t table_count, uint32_t delay_ms, deferred_exec_callback callback, void *cb_arg);

/**
 * Allows for extending the timeframe before an existing deferred execution is invoked.
 *
 * @param token[in] the returned value from defer_exec for the deferred execution you wish to extend
 * @param delay_ms[in] the number of milliseconds before executing the callback
 * @return true if the token was extended successfully, otherwise false
 */
bool extend_deferred_exec_advanced(deferred_executor_t *table, size_t table_count, deferred_token token, uint32_t delay_ms);

/**
 * Allows for cancellation of an existing deferred execution.
 *
 * @param token[in] the returned value from defer_exec for the deferred execution you wish to cancel
 * @return true if the token was cancelled successfully, otherwise false
 */
bool cancel_deferred_exec_advanced(deferred_executor_t *table, size_t table_count, deferred_token token);

/**
 * Forward declaration for the main loop in order to execute any custom table deferred executors. Should not be invoked by keyboard/user code.
 * Needed for any custom-allocated deferred execution tables. Any core tasks should add appropriate invocation to quantum/main.c.
 *
 * @param table[in] the custom table used for storage
 * @param table_count[in] the number of available items in the table
 * @param last_execution_time[in,out] the last execution time -- this will be checked first to determine if execution is needed, and updated if execution occurred
 */
void deferred_exec_advanced_task(deferred_executor_t *table, size_t table_count, uint32_t *last_execution_time);
