/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_SYNC_H
#define _HARDWARE_SYNC_H

#include "pico.h"

#ifndef __cplusplus

#if (__STDC_VERSION__ >= 201112L)
#include <stdatomic.h>
#else
enum {
    memory_order_acquire, memory_order_release
};
static inline void atomic_thread_fence(uint x) {}
#endif

#else

#include <atomic>

#endif

#ifndef PICO_SPINLOCK_ID_TIMER
#define PICO_SPINLOCK_ID_TIMER 10
#endif

#ifndef PICO_SPINLOCK_ID_STRIPED_FIRST
#define PICO_SPINLOCK_ID_STRIPED_FIRST 16
#endif

#ifndef PICO_SPINLOCK_ID_STRIPED_LAST
#define PICO_SPINLOCK_ID_STRIPED_LAST 23
#endif

typedef struct _spin_lock_t spin_lock_t;

inline static void __mem_fence_acquire() {
#ifndef __cplusplus
    atomic_thread_fence(memory_order_acquire);
#else
    std::atomic_thread_fence(std::memory_order_acquire);
#endif
}

inline static void __mem_fence_release() {
#ifndef __cplusplus
    atomic_thread_fence(memory_order_release);
#else
    std::atomic_thread_fence(std::memory_order_release);
#endif
}

#ifdef __cplusplus
extern "C" {
#endif

void __sev();

void __wev();

void __wfi();

void __wfe();

uint32_t save_and_disable_interrupts();

void restore_interrupts(uint32_t status);

uint spin_lock_get_num(spin_lock_t *lock);

spin_lock_t *spin_lock_instance(uint lock_num);

void spin_lock_unsafe_blocking(spin_lock_t *lock);

void spin_unlock_unsafe(spin_lock_t *lock);

uint32_t spin_lock_blocking(spin_lock_t *lock);

bool is_spin_locked(const spin_lock_t *lock);

void spin_unlock(spin_lock_t *lock, uint32_t saved_irq);

spin_lock_t *spin_lock_init(uint lock_num);

void clear_spin_locks(void);

uint next_striped_spin_lock_num();

void spin_lock_claim(uint lock_num);
void spin_lock_claim_mask(uint32_t lock_num_mask);
void spin_lock_unclaim(uint lock_num);
int spin_lock_claim_unused(bool required);
uint spin_lock_num(spin_lock_t *lock);

#ifdef __cplusplus
}
#endif
#endif
