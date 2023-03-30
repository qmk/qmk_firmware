/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/mutex.h"
#include "pico/time.h"

void mutex_init(mutex_t *mtx) {
    lock_init(&mtx->core, next_striped_spin_lock_num());
    mtx->owner = LOCK_INVALID_OWNER_ID;
#if PICO_MUTEX_ENABLE_SDK120_COMPATIBILITY
    mtx->recursive = false;
#endif
    __mem_fence_release();
}

void recursive_mutex_init(recursive_mutex_t *mtx) {
    lock_init(&mtx->core, next_striped_spin_lock_num());
    mtx->owner = LOCK_INVALID_OWNER_ID;
    mtx->enter_count = 0;
#if PICO_MUTEX_ENABLE_SDK120_COMPATIBILITY
    mtx->recursive = true;
#endif
    __mem_fence_release();
}

void __time_critical_func(mutex_enter_blocking)(mutex_t *mtx) {
#if PICO_MUTEX_ENABLE_SDK120_COMPATIBILITY
    if (mtx->recursive) {
        recursive_mutex_enter_blocking(mtx);
        return;
    }
#endif
    lock_owner_id_t caller = lock_get_caller_owner_id();
    do {
        uint32_t save = spin_lock_blocking(mtx->core.spin_lock);
        if (!lock_is_owner_id_valid(mtx->owner)) {
            mtx->owner = caller;
            spin_unlock(mtx->core.spin_lock, save);
            break;
        }
        lock_internal_spin_unlock_with_wait(&mtx->core, save);
    } while (true);
}

void __time_critical_func(recursive_mutex_enter_blocking)(recursive_mutex_t *mtx) {
    lock_owner_id_t caller = lock_get_caller_owner_id();
    do {
        uint32_t save = spin_lock_blocking(mtx->core.spin_lock);
        if (mtx->owner == caller || !lock_is_owner_id_valid(mtx->owner)) {
            mtx->owner = caller;
            uint __unused total = ++mtx->enter_count;
            spin_unlock(mtx->core.spin_lock, save);
            assert(total); // check for overflow
            return;
        } else {
            lock_internal_spin_unlock_with_wait(&mtx->core, save);
        }
    } while (true);
}

bool __time_critical_func(mutex_try_enter)(mutex_t *mtx, uint32_t *owner_out) {
#if PICO_MUTEX_ENABLE_SDK120_COMPATIBILITY
    if (mtx->recursive) {
        return recursive_mutex_try_enter(mtx, owner_out);
    }
#endif
    bool entered;
    uint32_t save = spin_lock_blocking(mtx->core.spin_lock);
    if (!lock_is_owner_id_valid(mtx->owner)) {
        mtx->owner = lock_get_caller_owner_id();
        entered = true;
    } else {
        if (owner_out) *owner_out = (uint32_t) mtx->owner;
        entered = false;
    }
    spin_unlock(mtx->core.spin_lock, save);
    return entered;
}

bool __time_critical_func(mutex_try_enter_block_until)(mutex_t *mtx, absolute_time_t until) {
    // not using lock_owner_id_t to avoid backwards incompatibility change to mutex_try_enter API
    static_assert(sizeof(lock_owner_id_t) <= 4, "");
    uint32_t owner;
    if (!mutex_try_enter(mtx, &owner)) {
        if ((lock_owner_id_t)owner == lock_get_caller_owner_id()) return false; // deadlock, so we can never own it
        return mutex_enter_block_until(mtx, until);
    }
    return true;
}

bool __time_critical_func(recursive_mutex_try_enter)(recursive_mutex_t *mtx, uint32_t *owner_out) {
    bool entered;
    lock_owner_id_t caller = lock_get_caller_owner_id();
    uint32_t save = spin_lock_blocking(mtx->core.spin_lock);
    if (!lock_is_owner_id_valid(mtx->owner) || mtx->owner == caller) {
        mtx->owner = caller;
        uint __unused total = ++mtx->enter_count;
        assert(total); // check for overflow
        entered = true;
    } else {
        if (owner_out) *owner_out = (uint32_t) mtx->owner;
        entered = false;
    }
    spin_unlock(mtx->core.spin_lock, save);
    return entered;
}

bool __time_critical_func(mutex_enter_timeout_ms)(mutex_t *mtx, uint32_t timeout_ms) {
    return mutex_enter_block_until(mtx, make_timeout_time_ms(timeout_ms));
}

bool __time_critical_func(recursive_mutex_enter_timeout_ms)(recursive_mutex_t *mtx, uint32_t timeout_ms) {
    return recursive_mutex_enter_block_until(mtx, make_timeout_time_ms(timeout_ms));
}

bool __time_critical_func(mutex_enter_timeout_us)(mutex_t *mtx, uint32_t timeout_us) {
    return mutex_enter_block_until(mtx, make_timeout_time_us(timeout_us));
}

bool __time_critical_func(recursive_mutex_enter_timeout_us)(recursive_mutex_t *mtx, uint32_t timeout_us) {
    return recursive_mutex_enter_block_until(mtx, make_timeout_time_us(timeout_us));
}

bool __time_critical_func(mutex_enter_block_until)(mutex_t *mtx, absolute_time_t until) {
#if PICO_MUTEX_ENABLE_SDK120_COMPATIBILITY
    if (mtx->recursive) {
        return recursive_mutex_enter_block_until(mtx, until);
    }
#endif
    assert(mtx->core.spin_lock);
    lock_owner_id_t caller = lock_get_caller_owner_id();
    do {
        uint32_t save = spin_lock_blocking(mtx->core.spin_lock);
        if (!lock_is_owner_id_valid(mtx->owner)) {
            mtx->owner = caller;
            spin_unlock(mtx->core.spin_lock, save);
            return true;
        } else {
            if (lock_internal_spin_unlock_with_best_effort_wait_or_timeout(&mtx->core, save, until)) {
                // timed out
                return false;
            }
            // not timed out; spin lock already unlocked, so loop again
        }
    } while (true);
}

bool __time_critical_func(recursive_mutex_enter_block_until)(recursive_mutex_t *mtx, absolute_time_t until) {
    assert(mtx->core.spin_lock);
    lock_owner_id_t caller = lock_get_caller_owner_id();
    do {
        uint32_t save = spin_lock_blocking(mtx->core.spin_lock);
        if (!lock_is_owner_id_valid(mtx->owner) || mtx->owner == caller) {
            mtx->owner = caller;
            uint __unused total = ++mtx->enter_count;
            spin_unlock(mtx->core.spin_lock, save);
            assert(total); // check for overflow
            return true;
        } else {
            if (lock_internal_spin_unlock_with_best_effort_wait_or_timeout(&mtx->core, save, until)) {
                // timed out
                return false;
            }
            // not timed out; spin lock already unlocked, so loop again
        }
    } while (true);
}

void __time_critical_func(mutex_exit)(mutex_t *mtx) {
#if PICO_MUTEX_ENABLE_SDK120_COMPATIBILITY
    if (mtx->recursive) {
        recursive_mutex_exit(mtx);
        return;
    }
#endif
    uint32_t save = spin_lock_blocking(mtx->core.spin_lock);
    assert(lock_is_owner_id_valid(mtx->owner));
    mtx->owner = LOCK_INVALID_OWNER_ID;
    lock_internal_spin_unlock_with_notify(&mtx->core, save);
}

void __time_critical_func(recursive_mutex_exit)(recursive_mutex_t *mtx) {
    uint32_t save = spin_lock_blocking(mtx->core.spin_lock);
    assert(lock_is_owner_id_valid(mtx->owner));
    assert(mtx->enter_count);
    if (!--mtx->enter_count) {
        mtx->owner = LOCK_INVALID_OWNER_ID;
        lock_internal_spin_unlock_with_notify(&mtx->core, save);
    } else {
        spin_unlock(mtx->core.spin_lock, save);
    }
}