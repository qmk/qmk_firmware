/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/lock_core.h"

void lock_init(lock_core_t *core, uint lock_num) {
    valid_params_if(LOCK_CORE, lock_num < NUM_SPIN_LOCKS);
    core->spin_lock = spin_lock_instance(lock_num);
}

