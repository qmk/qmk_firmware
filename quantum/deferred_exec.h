// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdbool.h>
#include <stdint.h>

// A token that can be used to cancel an existing deferred execution.
typedef uint8_t deferred_token;
#define INVALID_DEFERRED_TOKEN 0

// Callback to execute.
//  -- Parameter trigger_time: the intended trigger time to execute the callback -- equivalent time-space as timer_read32()
//               cb_arg: the callback argument specified when enqueueing the deferred executor
//  -- Return value: Non-zero re-queues the callback to execute after the returned number of milliseconds. Zero cancels repeated execution.
typedef uint32_t (*deferred_exec_callback)(uint32_t trigger_time, void *cb_arg);

// Configures the supplied deferred executor to be executed after the required number of milliseconds.
//  -- Parameter delay_ms: the number of milliseconds before executing the callback
//  --           callback: the executor to invoke
//  --           cb_arg: the argument to pass to the executor, may be NULL if unused by the executor
//  -- Return value: a token usable for cancellation, or INVALID_DEFERRED_TOKEN if an error occurred
deferred_token defer_exec(uint32_t delay_ms, deferred_exec_callback callback, void *cb_arg);

// Allows for extending the timeframe before an existing deferred execution is invoked.
//  -- Parameter token: the returned value from defer_exec for the deferred execution you wish to extend.
//  --           delay_ms: the new delay (with respect to the current time)
//  -- Return value: if the token was found, and the delay was extended
bool extend_deferred_exec(deferred_token token, uint32_t delay_ms);

// Allows for cancellation of an existing deferred execution.
//  -- Parameter token: the returned value from defer_exec for the deferred execution you wish to cancel.
//  -- Return value: if the token was found, and the executor was cancelled
bool cancel_deferred_exec(deferred_token token);

// Forward declaration for the main loop in order to execute any deferred executors. Should not be invoked by keyboard/user code.
void deferred_exec_task(void);
