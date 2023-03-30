/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/critical_section.h"

#if !PICO_NO_HARDWARE
static_assert(sizeof(critical_section_t) == 8, "");
#endif

void critical_section_init(critical_section_t *crit_sec) {
    critical_section_init_with_lock_num(crit_sec, (uint)spin_lock_claim_unused(true));
}

void critical_section_init_with_lock_num(critical_section_t *crit_sec, uint lock_num) {
    crit_sec->spin_lock = spin_lock_instance(lock_num);
    __mem_fence_release();
}

void critical_section_deinit(critical_section_t *crit_sec) {
    spin_lock_unclaim(spin_lock_get_num(crit_sec->spin_lock));
    crit_sec->spin_lock = NULL;
}