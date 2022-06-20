// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#if defined(PLATFORM_SUPPORTS_SYNCHRONIZATION)
#    if defined(SPLIT_KEYBOARD)
void split_shared_memory_lock(void);
void split_shared_memory_unlock(void);
#    endif
#else
inline void split_shared_memory_lock(void){};
inline void split_shared_memory_unlock(void){};
#endif

/* GCCs cleanup attribute expects a function with one parameter, which is a
 * pointer to a type compatible with the variable. As we don't want to expose
 * the platforms internal mutex type this workaround with auto generated adapter
 * function is defined */
#define QMK_DECLARE_AUTOUNLOCK_HELPERS(prefix)                              \
    inline unsigned prefix##_autounlock_lock_helper(void) {                 \
        prefix##_lock();                                                    \
        return 0;                                                           \
    }                                                                       \
                                                                            \
    inline void prefix##_autounlock_unlock_helper(unsigned* unused_guard) { \
        prefix##_unlock();                                                  \
    }

/* Convinience macro the automatically generate the correct RAII-style
 * lock_autounlock function macro */
#define QMK_DECLARE_AUTOUNLOCK_CALL(prefix) unsigned prefix##_guard __attribute__((unused, cleanup(prefix##_autounlock_unlock_helper))) = prefix##_autounlock_lock_helper

QMK_DECLARE_AUTOUNLOCK_HELPERS(split_shared_memory)

/**
 * @brief Acquire exclusive access to the split keyboard shared memory, by
 * calling the platforms `split_shared_memory_lock()` function. The lock is
 * automatically released by calling the platforms `split_shared_memory_unlock()`
 * function. This happens when the block where
 * `split_shared_memory_lock_autounlock()` is called in goes out of scope i.e.
 * when the enclosing function returns.
 */
#define split_shared_memory_lock_autounlock QMK_DECLARE_AUTOUNLOCK_CALL(split_shared_memory)
