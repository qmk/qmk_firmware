/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/timeout_helper.h"

static bool check_single_timeout_us(timeout_state_t *ts) {
    return time_reached(ts->next_timeout);
}

check_timeout_fn init_single_timeout_until(timeout_state_t *ts, absolute_time_t target) {
    ts->next_timeout = target;
    return check_single_timeout_us;
}

static bool check_per_iteration_timeout_us(timeout_state_t *ts) {
    if (time_reached(ts->next_timeout)) {
        return true;
    }
    ts->next_timeout = make_timeout_time_us(ts->param);
    return false;
}

check_timeout_fn init_per_iteration_timeout_us(timeout_state_t *ts, uint64_t per_iteration_timeout_us) {
    ts->next_timeout = make_timeout_time_us(per_iteration_timeout_us);
    ts->param = per_iteration_timeout_us;
    return check_per_iteration_timeout_us;
}
