/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/sync.h"
#include "hardware/claim.h"

static_assert(PICO_SPINLOCK_ID_STRIPED_LAST >= PICO_SPINLOCK_ID_STRIPED_FIRST, "");
static uint8_t striped_spin_lock_num = PICO_SPINLOCK_ID_STRIPED_FIRST;
static uint32_t claimed;

static void check_lock_num(uint __unused lock_num) {
    invalid_params_if(SYNC, lock_num >= 32);
}

void spin_locks_reset(void) {
    for (uint i = 0; i < NUM_SPIN_LOCKS; i++) {
        spin_unlock_unsafe(spin_lock_instance(i));
    }
}

spin_lock_t *spin_lock_init(uint lock_num) {
    assert(lock_num < NUM_SPIN_LOCKS);
    spin_lock_t *lock = spin_lock_instance(lock_num);
    spin_unlock_unsafe(lock);
    return lock;
}

uint next_striped_spin_lock_num() {
    uint rc = striped_spin_lock_num++;
    if (striped_spin_lock_num > PICO_SPINLOCK_ID_STRIPED_LAST) {
        striped_spin_lock_num = PICO_SPINLOCK_ID_STRIPED_FIRST;
    }
    return rc;
}

void spin_lock_claim(uint lock_num) {
    check_lock_num(lock_num);
    hw_claim_or_assert((uint8_t *) &claimed, lock_num, "Spinlock %d is already claimed");
}

void spin_lock_claim_mask(uint32_t mask) {
    for(uint i = 0; mask; i++, mask >>= 1u) {
        if (mask & 1u) spin_lock_claim(i);
    }
}

void spin_lock_unclaim(uint lock_num) {
    check_lock_num(lock_num);
    spin_unlock_unsafe(spin_lock_instance(lock_num));
    hw_claim_clear((uint8_t *) &claimed, lock_num);
}

int spin_lock_claim_unused(bool required) {
    return hw_claim_unused_from_range((uint8_t*)&claimed, required, PICO_SPINLOCK_ID_CLAIM_FREE_FIRST, PICO_SPINLOCK_ID_CLAIM_FREE_LAST, "No spinlocks are available");
}

bool spin_lock_is_claimed(uint lock_num) {
    check_lock_num(lock_num);
    return hw_is_claimed((uint8_t *) &claimed, lock_num);
}

