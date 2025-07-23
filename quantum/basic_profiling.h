// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

/*
    This API allows for basic profiling information to be printed out over console.

    Usage example:

        #include "basic_profiling.h"

        // Original code:
        matrix_task();

        // Delete the original, replace with the following (variant 1, automatic naming):
        PROFILE_CALL(1000, matrix_task());

        // Delete the original, replace with the following (variant 2, explicit naming):
        PROFILE_CALL_NAMED(1000, "matrix_task", {
            matrix_task();
        });
*/

#if defined(PROTOCOL_LUFA) || defined(PROTOCOL_VUSB)
#    define TIMESTAMP_GETTER TCNT0
#elif defined(PROTOCOL_CHIBIOS)
#    define TIMESTAMP_GETTER chSysGetRealtimeCounterX()
#else
#    error Unknown protocol in use
#endif

#ifndef CONSOLE_ENABLE
// Can't do anything if we don't have console output enabled.
#    define PROFILE_CALL_NAMED(count, name, call) \
        do {                                      \
        } while (0)
#else
#    define PROFILE_CALL_NAMED(count, name, call)                                                                         \
        do {                                                                                                              \
            static uint64_t inner_sum = 0;                                                                                \
            static uint64_t outer_sum = 0;                                                                                \
            uint32_t        start_ts;                                                                                     \
            static uint32_t end_ts;                                                                                       \
            static uint32_t write_location = 0;                                                                           \
            start_ts                       = TIMESTAMP_GETTER;                                                            \
            if (write_location > 0) {                                                                                     \
                outer_sum += start_ts - end_ts;                                                                           \
            }                                                                                                             \
            do {                                                                                                          \
                call;                                                                                                     \
            } while (0);                                                                                                  \
            end_ts = TIMESTAMP_GETTER;                                                                                    \
            inner_sum += end_ts - start_ts;                                                                               \
            ++write_location;                                                                                             \
            if (write_location >= ((uint32_t)count)) {                                                                    \
                uint32_t inner_avg = inner_sum / (((uint32_t)count) - 1);                                                 \
                uint32_t outer_avg = outer_sum / (((uint32_t)count) - 1);                                                 \
                dprintf("%s -- Percentage time spent: %d%%\n", (name), (int)(inner_avg * 100 / (inner_avg + outer_avg))); \
                inner_sum      = 0;                                                                                       \
                outer_sum      = 0;                                                                                       \
                write_location = 0;                                                                                       \
            }                                                                                                             \
        } while (0)

#endif // CONSOLE_ENABLE

#define PROFILE_CALL(count, call) PROFILE_CALL_NAMED(count, #call, call)
