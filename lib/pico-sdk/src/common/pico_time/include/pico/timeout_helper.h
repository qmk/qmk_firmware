/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_TIMEOUT_HELPER_H
#define _PICO_TIMEOUT_HELPER_H

#include "pico/time.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct timeout_state {
    absolute_time_t next_timeout;
    uint64_t param;
} timeout_state_t;

typedef bool (*check_timeout_fn)(timeout_state_t *ts);

check_timeout_fn init_single_timeout_until(timeout_state_t *ts, absolute_time_t target);
check_timeout_fn init_per_iteration_timeout_us(timeout_state_t *ts, uint64_t per_iteration_timeout_us);

#ifdef __cplusplus
}
#endif

#endif