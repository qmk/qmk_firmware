// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#include "synchronization_util.h"
#include "ch.h"

#if defined(SPLIT_KEYBOARD)
static MUTEX_DECL(SPLIT_SHARED_MEMORY_MUTEX);

/**
 * @brief Acquire exclusive access to the split keyboard shared memory, by
 * locking the mutex guarding it. If the mutex is already held, the calling
 * thread will be suspended until the mutex currently owning thread releases the
 * mutex again.
 */
void split_shared_memory_lock(void) {
    chMtxLock(&SPLIT_SHARED_MEMORY_MUTEX);
}

/**
 * @brief Release the split shared memory mutex that has been acquired before.
 */
void split_shared_memory_unlock(void) {
    chMtxUnlock(&SPLIT_SHARED_MEMORY_MUTEX);
}
#endif
