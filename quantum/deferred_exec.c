// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stddef.h>
#include <timer.h>
#include <deferred_exec.h>

#ifndef MAX_DEFERRED_EXECUTORS
#    define MAX_DEFERRED_EXECUTORS 8
#endif

typedef struct deferred_executor_t {
    uint16_t               token;
    uint32_t               trigger_time;
    deferred_exec_callback callback;
    void *                 cb_arg;
} deferred_executor_t;

static uint16_t            current_token                     = 0;
static uint32_t            last_deferred_exec_check          = 0;
static deferred_executor_t executors[MAX_DEFERRED_EXECUTORS] = {0};

deferred_token defer_exec(uint32_t delay_ms, deferred_exec_callback callback, void *cb_arg) {
    // Ignore queueing if it's a zero-time delay, or invalid callback
    if (delay_ms == 0 || !callback) {
        return INVALID_DEFERRED_TOKEN;
    }

    // Find an unused slot and claim it
    for (int i = 0; i < MAX_DEFERRED_EXECUTORS; ++i) {
        deferred_executor_t *entry = &executors[i];
        if (entry->trigger_time == 0) {
            // Work out the new token value
            do {
                ++current_token;
            } while (current_token == INVALID_DEFERRED_TOKEN);  // Skip INVALID_DEFERRED_TOKEN

            // Set up the executor table entry
            entry->token        = current_token;
            entry->trigger_time = timer_read32() + delay_ms;
            entry->callback     = callback;
            entry->cb_arg       = cb_arg;
            return (deferred_token)current_token;
        }
    }

    // None available
    return INVALID_DEFERRED_TOKEN;
}

bool extend_deferred_exec(deferred_token token, uint32_t delay_ms) {
    // Ignore queueing if it's a zero-time delay
    if (delay_ms == 0) {
        return false;
    }

    // Find the entry corresponding to the token
    for (int i = 0; i < MAX_DEFERRED_EXECUTORS; ++i) {
        deferred_executor_t *entry = &executors[i];
        if (entry->token == (uint16_t)token) {
            // Found it, extend the delay
            entry->trigger_time = timer_read32() + delay_ms;
            return true;
        }
    }

    // Not found
    return false;
}

bool cancel_deferred_exec(deferred_token token) {
    // Find the entry corresponding to the token
    for (int i = 0; i < MAX_DEFERRED_EXECUTORS; ++i) {
        deferred_executor_t *entry = &executors[i];
        if (entry->token == (uint16_t)token) {
            // Found it, cancel and clear the table entry
            entry->token        = INVALID_DEFERRED_TOKEN;
            entry->trigger_time = 0;
            entry->callback     = NULL;
            entry->cb_arg       = NULL;
            return true;
        }
    }

    // Not found
    return false;
}

void deferred_exec_task(void) {
    uint32_t now = timer_read32();

    // Throttle only once per millisecond
    if (((int32_t)TIMER_DIFF_32(now, last_deferred_exec_check)) > 0) {
        last_deferred_exec_check = now;

        // Run through each of the executors
        for (int i = 0; i < MAX_DEFERRED_EXECUTORS; ++i) {
            deferred_executor_t *entry = &executors[i];

            // Check if we're supposed to execute this entry
            if (entry->token != INVALID_DEFERRED_TOKEN && entry->trigger_time > 0 && ((int32_t)TIMER_DIFF_32(entry->trigger_time, now)) <= 0) {
                // Invoke the callback and work work out if we should be requeued
                uint32_t delay_ms = entry->callback(entry->cb_arg);

                // Update the trigger time if we have to repeat, otherwise clear it out
                if (delay_ms > 0) {
                    // Intentionally add just the delay to the existing trigger time -- this ensures the next
                    // invocation is with respect to the previous trigger, rather than when it got to execution. Under
                    // normal circumstances this won't cause issue, but if another executor is invoked that takes a
                    // considerable length of time, then this ensures best-effort timing between invocations.
                    entry->trigger_time += delay_ms;
                } else {
                    // If it was zero, then the callback is cancelling repeated execution. Free up the slot.
                    entry->token        = INVALID_DEFERRED_TOKEN;
                    entry->trigger_time = 0;
                    entry->callback     = NULL;
                    entry->cb_arg       = NULL;
                }
            }
        }
    }
}
