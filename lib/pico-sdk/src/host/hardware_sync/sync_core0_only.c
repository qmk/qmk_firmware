/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/sync.h"
#include "hardware/platform_defs.h"

// This is a dummy implementation that is single threaded

static struct _spin_lock_t {
    bool locked;
} _spinlocks[NUM_SPIN_LOCKS];

PICO_WEAK_FUNCTION_DEF(save_and_disable_interrupts)

//static uint8_t striped_spin_lock_num;

uint32_t PICO_WEAK_FUNCTION_IMPL_NAME(save_and_disable_interrupts)() {
    return 0;
}

PICO_WEAK_FUNCTION_DEF(restore_interrupts)

void PICO_WEAK_FUNCTION_IMPL_NAME(restore_interrupts)(uint32_t status) {
}

PICO_WEAK_FUNCTION_DEF(spin_lock_instance)

spin_lock_t *PICO_WEAK_FUNCTION_IMPL_NAME(spin_lock_instance)(uint lock_num) {
    assert(lock_num < NUM_SPIN_LOCKS);
    return &_spinlocks[lock_num];
}

PICO_WEAK_FUNCTION_DEF(spin_lock_get_num)

uint PICO_WEAK_FUNCTION_IMPL_NAME(spin_lock_get_num)(spin_lock_t *lock) {
    return lock - _spinlocks;
}

PICO_WEAK_FUNCTION_DEF(spin_lock_init)

spin_lock_t *PICO_WEAK_FUNCTION_IMPL_NAME(spin_lock_init)(uint lock_num) {
    spin_lock_t *lock = spin_lock_instance(lock_num);
    spin_unlock_unsafe(lock);
    return lock;
}

PICO_WEAK_FUNCTION_DEF(spin_lock_unsafe_blocking)

void PICO_WEAK_FUNCTION_IMPL_NAME(spin_lock_unsafe_blocking)(spin_lock_t *lock) {
    lock->locked = true;
}

PICO_WEAK_FUNCTION_DEF(spin_lock_blocking)

uint32_t PICO_WEAK_FUNCTION_IMPL_NAME(spin_lock_blocking)(spin_lock_t *lock) {
    spin_lock_unsafe_blocking(lock);
    return 1; // todo wrong value
}

PICO_WEAK_FUNCTION_DEF(is_spin_locked)

bool PICO_WEAK_FUNCTION_IMPL_NAME(is_spin_locked)(const spin_lock_t *lock) {
    return lock->locked;
}

PICO_WEAK_FUNCTION_DEF(spin_unlock_unsafe)

void PICO_WEAK_FUNCTION_IMPL_NAME(spin_unlock_unsafe)(spin_lock_t *lock) {
    lock->locked = false;
}

PICO_WEAK_FUNCTION_DEF(spin_unlock)

void PICO_WEAK_FUNCTION_IMPL_NAME(spin_unlock)(spin_lock_t *lock, uint32_t saved_irq) {
    spin_unlock_unsafe(lock);
}

PICO_WEAK_FUNCTION_DEF(__sev)

volatile bool event_fired;

void PICO_WEAK_FUNCTION_IMPL_NAME(__sev)() {
    event_fired = true;
}

PICO_WEAK_FUNCTION_DEF(__wfi)

void PICO_WEAK_FUNCTION_IMPL_NAME(__wfi)() {
    panic("Can't wait on irq for host core0 only implementation");
}

PICO_WEAK_FUNCTION_DEF(__wfe)

void PICO_WEAK_FUNCTION_IMPL_NAME(__wfe)() {
    while (!event_fired) tight_loop_contents();
}

PICO_WEAK_FUNCTION_DEF(get_core_num)

uint PICO_WEAK_FUNCTION_IMPL_NAME(get_core_num)() {
    return 0;
}

PICO_WEAK_FUNCTION_DEF(clear_spin_locks)

void PICO_WEAK_FUNCTION_IMPL_NAME(clear_spin_locks)(void) {
    for (uint i = 0; i < NUM_SPIN_LOCKS; i++) {
        spin_unlock_unsafe(spin_lock_instance(i));
    }
}

PICO_WEAK_FUNCTION_DEF(next_striped_spin_lock_num)
uint PICO_WEAK_FUNCTION_IMPL_NAME(next_striped_spin_lock_num)() {
    return 0;
}

PICO_WEAK_FUNCTION_DEF(spin_lock_claim)
void PICO_WEAK_FUNCTION_IMPL_NAME(spin_lock_claim)(uint lock_num) {
}

PICO_WEAK_FUNCTION_DEF(spin_lock_claim_mask)
void PICO_WEAK_FUNCTION_IMPL_NAME(spin_lock_claim_mask)(uint32_t mask) {
}

PICO_WEAK_FUNCTION_DEF(spin_lock_unclaim)
void PICO_WEAK_FUNCTION_IMPL_NAME(spin_lock_unclaim)(uint lock_num) {
}

PICO_WEAK_FUNCTION_DEF(spin_lock_claim_unused)
int PICO_WEAK_FUNCTION_IMPL_NAME(spin_lock_claim_unused)(bool required) {
    return 0;
}

PICO_WEAK_FUNCTION_DEF(spin_lock_num)
uint PICO_WEAK_FUNCTION_IMPL_NAME(spin_lock_num)(spin_lock_t *lock) {
    return 0;
}