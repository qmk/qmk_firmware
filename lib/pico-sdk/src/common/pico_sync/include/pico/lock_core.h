/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_LOCK_CORE_H
#define _PICO_LOCK_CORE_H

#include "pico.h"
#include "pico/time.h"
#include "hardware/sync.h"

/** \file lock_core.h
 *  \defgroup lock_core lock_core
 *  \ingroup pico_sync
 * \brief base synchronization/lock primitive support
 *
 * Most of the pico_sync locking primitives contain a lock_core_t structure member. This currently just holds a spin
 * lock which is used only to protect the contents of the rest of the structure as part of implementing the synchronization
 * primitive. As such, the spin_lock member of lock core is never still held on return from any function for the primitive.
 *
 * \ref critical_section is an exceptional case in that it does not have a lock_core_t and simply wraps a spin lock, providing
 * methods to lock and unlock said spin lock.
 *
 * lock_core based structures work by locking the spin lock, checking state, and then deciding whether they additionally need to block
 * or notify when the spin lock is released. In the blocking case, they will wake up again in the future, and try the process again.
 *
 * By default the SDK just uses the processors' events via SEV and WEV for notification and blocking as these are sufficient for
 * cross core, and notification from interrupt handlers. However macros are defined in this file that abstract the wait
 * and notify mechanisms to allow the SDK locking functions to effectively be used within an RTOS or other environment.
 *
 * When implementing an RTOS, it is desirable for the SDK synchronization primitives that wait, to block the calling task (and immediately yield),
 * and those that notify, to wake a blocked task which isn't on processor. At least the wait macro implementation needs to be atomic with the protecting
 * spin_lock unlock from the callers point of view; i.e. the task should unlock the spin lock when it starts its wait. Such implementation is
 * up to the RTOS integration, however the macros are defined such that such operations are always combined into a single call
 * (so they can be perfomed atomically) even though the default implementation does not need this, as a WFE which starts
 * following the corresponding SEV is not missed.
 */

// PICO_CONFIG: PARAM_ASSERTIONS_ENABLED_LOCK_CORE, Enable/disable assertions in the lock core, type=bool, default=0, group=pico_sync
#ifndef PARAM_ASSERTIONS_ENABLED_LOCK_CORE
#define PARAM_ASSERTIONS_ENABLED_LOCK_CORE 0
#endif

/** \file lock_core.h
 *  \ingroup lock_core
 *
 * Base implementation for locking primitives protected by a spin lock. The spin lock is only used to protect
 * access to the remaining lock state (in primitives using lock_core); it is never left locked outside
 * of the function implementations
 */
struct lock_core {
    // spin lock protecting this lock's state
    spin_lock_t *spin_lock;

    // note any lock members in containing structures need not be volatile;
    // they are protected by memory/compiler barriers when gaining and release spin locks
};

typedef struct lock_core lock_core_t;

/*! \brief  Initialise a lock structure
 *  \ingroup lock_core
 *
 * Inititalize a lock structure, providing the spin lock number to use for protecting internal state.
 *
 * \param core Pointer to the lock_core to initialize
 * \param lock_num Spin lock number to use for the lock. As the spin lock is only used internally to the locking primitive
 *                 method implementations, this does not need to be globally unique, however could suffer contention
 */
void lock_init(lock_core_t *core, uint lock_num);

#ifndef lock_owner_id_t
/*! \brief  type to use to store the 'owner' of a lock.
 *  \ingroup lock_core
 * By default this is int8_t as it only needs to store the core number or -1, however it may be
 * overridden if a larger type is required (e.g. for an RTOS task id)
 */
#define lock_owner_id_t int8_t
#endif

#ifndef LOCK_INVALID_OWNER_ID
/*! \brief  marker value to use for a lock_owner_id_t which does not refer to any valid owner
 *  \ingroup lock_core
 */
#define LOCK_INVALID_OWNER_ID ((lock_owner_id_t)-1)
#endif

#ifndef lock_get_caller_owner_id
/*! \brief  return the owner id for the caller
 *  \ingroup lock_core
 * By default this returns the calling core number, but may be overridden (e.g. to return an RTOS task id)
 */
#define lock_get_caller_owner_id() ((lock_owner_id_t)get_core_num())
#ifndef lock_is_owner_id_valid
#define lock_is_owner_id_valid(id) ((id)>=0)
#endif
#endif

#ifndef lock_is_owner_id_valid
#define lock_is_owner_id_valid(id) ((id) != LOCK_INVALID_OWNER_ID)
#endif

#ifndef lock_internal_spin_unlock_with_wait
/*! \brief   Atomically unlock the lock's spin lock, and wait for a notification.
 *  \ingroup lock_core
 *
 * _Atomic_ here refers to the fact that it should not be possible for a concurrent lock_internal_spin_unlock_with_notify
 * to insert itself between the spin unlock and this wait in a way that the wait does not see the notification (i.e. causing
 * a missed notification). In other words this method should always wake up in response to a lock_internal_spin_unlock_with_notify
 * for the same lock, which completes after this call starts.
 *
 * In an ideal implementation, this method would return exactly after the corresponding lock_internal_spin_unlock_with_notify
 * has subsequently been called on the same lock instance, however this method is free to return at _any_ point before that;
 * this macro is _always_ used in a loop which locks the spin lock, checks the internal locking primitive state and then
 * waits again if the calling thread should not proceed.
 *
 * By default this macro simply unlocks the spin lock, and then performs a WFE, but may be overridden
 * (e.g. to actually block the RTOS task).
 *
 * \param lock the lock_core for the primitive which needs to block
 * \param save the uint32_t value that should be passed to spin_unlock when the spin lock is unlocked. (i.e. the `PRIMASK`
 *             state when the spin lock was acquire
 */
#define lock_internal_spin_unlock_with_wait(lock, save) spin_unlock((lock)->spin_lock, save), __wfe()
#endif

#ifndef lock_internal_spin_unlock_with_notify
/*! \brief   Atomically unlock the lock's spin lock, and send a notification
 *  \ingroup lock_core
 *
 * _Atomic_ here refers to the fact that it should not be possible for this notification to happen during a
 * lock_internal_spin_unlock_with_wait in a way that that wait does not see the notification (i.e. causing
 * a missed notification). In other words this method should always wake up any lock_internal_spin_unlock_with_wait
 * which started before this call completes.
 *
 * In an ideal implementation, this method would wake up only the corresponding lock_internal_spin_unlock_with_wait
 * that has been called on the same lock instance, however it is free to wake up any of them, as they will check
 * their condition and then re-wait if necessary/
 *
 * By default this macro simply unlocks the spin lock, and then performs a SEV, but may be overridden
 * (e.g. to actually un-block RTOS task(s)).
 *
 * \param lock the lock_core for the primitive which needs to block
 * \param save the uint32_t value that should be passed to spin_unlock when the spin lock is unlocked. (i.e. the PRIMASK
 *             state when the spin lock was acquire)
 */
#define lock_internal_spin_unlock_with_notify(lock, save) spin_unlock((lock)->spin_lock, save), __sev()
#endif

#ifndef lock_internal_spin_unlock_with_best_effort_wait_or_timeout
/*! \brief   Atomically unlock the lock's spin lock, and wait for a notification or a timeout
 *  \ingroup lock_core
 *
 * _Atomic_ here refers to the fact that it should not be possible for a concurrent lock_internal_spin_unlock_with_notify
 * to insert itself between the spin unlock and this wait in a way that the wait does not see the notification (i.e. causing
 * a missed notification). In other words this method should always wake up in response to a lock_internal_spin_unlock_with_notify
 * for the same lock, which completes after this call starts.
 *
 * In an ideal implementation, this method would return exactly after the corresponding lock_internal_spin_unlock_with_notify
 * has subsequently been called on the same lock instance or the timeout has been reached, however this method is free to return
 * at _any_ point before that; this macro is _always_ used in a loop which locks the spin lock, checks the internal locking
 * primitive state and then waits again if the calling thread should not proceed.
 *
 * By default this simply unlocks the spin lock, and then calls \ref best_effort_wfe_or_timeout
 * but may be overridden (e.g. to actually block the RTOS task with a timeout).
 *
 * \param lock the lock_core for the primitive which needs to block
 * \param save the uint32_t value that should be passed to spin_unlock when the spin lock is unlocked. (i.e. the PRIMASK
 *             state when the spin lock was acquire)
 * \param until the \ref absolute_time_t value
 * \return true if the timeout has been reached
 */
#define lock_internal_spin_unlock_with_best_effort_wait_or_timeout(lock, save, until) ({ \
    spin_unlock((lock)->spin_lock, save);                                                \
    best_effort_wfe_or_timeout(until);                                                   \
})
#endif

#ifndef sync_internal_yield_until_before
/*! \brief   yield to other processing until some time before the requested time
 *  \ingroup lock_core
 *
 * This method is provided for cases where the caller has no useful work to do
 * until the specified time.
 *
 * By default this method does nothing, however it can be overridden (for example by an
 * RTOS which is able to block the current task until the scheduler tick before
 * the given time)
 *
 * \param until the \ref absolute_time_t value
 */
#define sync_internal_yield_until_before(until) ((void)0)
#endif

#endif
