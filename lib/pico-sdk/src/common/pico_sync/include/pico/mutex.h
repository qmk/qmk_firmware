/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_MUTEX_H
#define _PICO_MUTEX_H

#include "pico/lock_core.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file mutex.h
 *  \defgroup mutex mutex
 *  \ingroup pico_sync
 * \brief Mutex API for non IRQ mutual exclusion between cores
 *
 * Mutexes are application level locks usually used protecting data structures that might be used by
 * multiple threads of execution. Unlike critical sections, the mutex protected code is not necessarily
 * required/expected to complete quickly, as no other sytem wide locks are held on account of an acquired mutex.
 *
 * When acquired, the mutex has an owner (see \ref lock_get_caller_owner_id) which with the plain SDK is just
 * the acquiring core, but in an RTOS it could be a task, or an IRQ handler context.
 *
 * Two variants of mutex are provided; \ref mutex_t (and associated mutex_ functions) is a regular mutex that cannot
 * be acquired recursively by the same owner (a deadlock will occur if you try). \ref recursive_mutex_t
 * (and associated recursive_mutex_ functions) is a recursive mutex that can be recursively obtained by
 * the same caller, at the expense of some more overhead when acquiring and releasing.
 *
 * It is generally a bad idea to call blocking mutex_ or recursive_mutex_ functions from within an IRQ handler.
 * It is valid to call \ref mutex_try_enter or \ref recursive_mutex_try_enter from within an IRQ handler, if the operation
 * that would be conducted under lock can be skipped if the mutex is locked (at least by the same owner).
 *
 * NOTE: For backwards compatibility with version 1.2.0 of the SDK, if the define
 * PICO_MUTEX_ENABLE_SDK120_COMPATIBILITY is set to 1, then the the regular mutex_ functions
 * may also be used for recursive mutexes. This flag will be removed in a future version of the SDK.
 *
 * See \ref critical_section.h for protecting access between multiple cores AND IRQ handlers
 */

/*! \brief recursive mutex instance
 * \ingroup mutex
 */
typedef struct __packed_aligned  {
    lock_core_t core;
    lock_owner_id_t owner;      //! owner id LOCK_INVALID_OWNER_ID for unowned
    uint8_t enter_count;        //! ownership count
#if PICO_MUTEX_ENABLE_SDK120_COMPATIBILITY
    bool recursive;
#endif
} recursive_mutex_t;

/*! \brief regular (non recursive) mutex instance
 * \ingroup mutex
 */
#if !PICO_MUTEX_ENABLE_SDK120_COMPATIBILITY
typedef struct __packed_aligned mutex {
    lock_core_t core;
    lock_owner_id_t owner;      //! owner id LOCK_INVALID_OWNER_ID for unowned
} mutex_t;
#else
typedef recursive_mutex_t mutex_t; // they are one and the same when backwards compatible with SDK1.2.0
#endif

/*! \brief  Initialise a mutex structure
 *  \ingroup mutex
 *
 * \param mtx Pointer to mutex structure
 */
void mutex_init(mutex_t *mtx);

/*! \brief  Initialise a recursive mutex structure
 *  \ingroup mutex
 *
 * A recursive mutex may be entered in a nested fashion by the same owner
 *
 * \param mtx Pointer to recursive mutex structure
 */
void recursive_mutex_init(recursive_mutex_t *mtx);

/*! \brief  Take ownership of a mutex
 *  \ingroup mutex
 *
 * This function will block until the caller can be granted ownership of the mutex.
 * On return the caller owns the mutex
 *
 * \param mtx Pointer to mutex structure
 */
void mutex_enter_blocking(mutex_t *mtx);

/*! \brief  Take ownership of a recursive mutex
 *  \ingroup mutex
 *
 * This function will block until the caller can be granted ownership of the mutex.
 * On return the caller owns the mutex
 *
 * \param mtx Pointer to recursive mutex structure
 */
void recursive_mutex_enter_blocking(recursive_mutex_t *mtx);

/*! \brief Attempt to take ownership of a mutex
 *  \ingroup mutex
 *
 * If the mutex wasn't owned, this will claim the mutex for the caller and return true.
 * Otherwise (if the mutex was already owned) this will return false and the
 * caller will NOT own the mutex.
 *
 * \param mtx Pointer to mutex structure
 * \param owner_out If mutex was already owned, and this pointer is non-zero, it will be filled in with the owner id of the current owner of the mutex
 * \return true if mutex now owned, false otherwise
 */
bool mutex_try_enter(mutex_t *mtx, uint32_t *owner_out);

/*! \brief Attempt to take ownership of a mutex until the specified time
 *  \ingroup mutex
 *
 * If the mutex wasn't owned, this method will immediately claim the mutex for the caller and return true.
 * If the mutex is owned by the caller, this method will immediately return false,
 * If the mutex is owned by someone else, this method will try to claim it until the specified time, returning
 * true if it succeeds, or false on timeout
 *
 * \param mtx Pointer to mutex structure
 * \param until The time after which to return if the caller cannot be granted ownership of the mutex
 * \return true if mutex now owned, false otherwise
 */
bool mutex_try_enter_block_until(mutex_t *mtx, absolute_time_t until);

/*! \brief Attempt to take ownership of a recursive mutex
 *  \ingroup mutex
 *
 * If the mutex wasn't owned or was owned by the caller, this will claim the mutex and return true.
 * Otherwise (if the mutex was already owned by another owner) this will return false and the
 * caller will NOT own the mutex.
 *
 * \param mtx Pointer to recursive mutex structure
 * \param owner_out If mutex was already owned by another owner, and this pointer is non-zero,
 *                  it will be filled in with the owner id of the current owner of the mutex
 * \return true if the recursive mutex (now) owned, false otherwise
 */
bool recursive_mutex_try_enter(recursive_mutex_t *mtx, uint32_t *owner_out);

/*! \brief Wait for mutex with timeout
 *  \ingroup mutex
 *
 * Wait for up to the specific time to take ownership of the mutex. If the caller
 * can be granted ownership of the mutex before the timeout expires, then true will be returned
 * and the caller will own the mutex, otherwise false will be returned and the caller will NOT own the mutex.
 *
 * \param mtx Pointer to mutex structure
 * \param timeout_ms The timeout in milliseconds.
 * \return true if mutex now owned, false if timeout occurred before ownership could be granted
 */
bool mutex_enter_timeout_ms(mutex_t *mtx, uint32_t timeout_ms);

/*! \brief Wait for recursive mutex with timeout
 *  \ingroup mutex
 *
 * Wait for up to the specific time to take ownership of the recursive mutex. If the caller
 * already has ownership of the mutex or can be granted ownership of the mutex before the timeout expires,
 * then true will be returned and the caller will own the mutex, otherwise false will be returned and the caller
 * will NOT own the mutex.
 *
 * \param mtx Pointer to recursive mutex structure
 * \param timeout_ms The timeout in milliseconds.
 * \return true if the recursive mutex (now) owned, false if timeout occurred before ownership could be granted
 */
bool recursive_mutex_enter_timeout_ms(recursive_mutex_t *mtx, uint32_t timeout_ms);

/*! \brief Wait for mutex with timeout
 *  \ingroup mutex
 *
 * Wait for up to the specific time to take ownership of the mutex. If the caller
 * can be granted ownership of the mutex before the timeout expires, then true will be returned
 * and the caller will own the mutex, otherwise false will be returned and the caller
 * will NOT own the mutex.
 *
 * \param mtx Pointer to mutex structure
 * \param timeout_us The timeout in microseconds.
 * \return true if mutex now owned, false if timeout occurred before ownership could be granted
 */
bool mutex_enter_timeout_us(mutex_t *mtx, uint32_t timeout_us);

/*! \brief Wait for recursive mutex with timeout
 *  \ingroup mutex
 *
 * Wait for up to the specific time to take ownership of the recursive mutex. If the caller
 * already has ownership of the mutex or can be granted ownership of the mutex before the timeout expires,
 * then true will be returned and the caller will own the mutex, otherwise false will be returned and the caller
 * will NOT own the mutex.
 *
 * \param mtx Pointer to mutex structure
 * \param timeout_us The timeout in microseconds.
 * \return true if the recursive mutex (now) owned, false if timeout occurred before ownership could be granted
 */
bool recursive_mutex_enter_timeout_us(recursive_mutex_t *mtx, uint32_t timeout_us);

/*! \brief Wait for mutex until a specific time
 *  \ingroup mutex
 *
 * Wait until the specific time to take ownership of the mutex. If the caller
 * can be granted ownership of the mutex before the timeout expires, then true will be returned
 * and the caller will own the mutex, otherwise false will be returned and the caller
 * will NOT own the mutex.
 *
 * \param mtx Pointer to mutex structure
 * \param until The time after which to return if the caller cannot be granted ownership of the mutex
 * \return true if mutex now owned, false if timeout occurred before ownership could be granted
 */
bool mutex_enter_block_until(mutex_t *mtx, absolute_time_t until);

/*! \brief Wait for mutex until a specific time
 *  \ingroup mutex
 *
 * Wait until the specific time to take ownership of the mutex. If the caller
 * already has ownership of the mutex or can be granted ownership of the mutex before the timeout expires,
 * then true will be returned and the caller will own the mutex, otherwise false will be returned and the caller
 * will NOT own the mutex.
 *
 * \param mtx Pointer to recursive mutex structure
 * \param until The time after which to return if the caller cannot be granted ownership of the mutex
 * \return true if the recursive mutex (now) owned, false if timeout occurred before ownership could be granted
 */
bool recursive_mutex_enter_block_until(recursive_mutex_t *mtx, absolute_time_t until);

/*! \brief  Release ownership of a mutex
 *  \ingroup mutex
 *
 * \param mtx Pointer to mutex structure
 */
void mutex_exit(mutex_t *mtx);

/*! \brief  Release ownership of a recursive mutex
 *  \ingroup mutex
 *
 * \param mtx Pointer to recursive mutex structure
 */
void recursive_mutex_exit(recursive_mutex_t *mtx);

/*! \brief Test for mutex initialized state
 *  \ingroup mutex
 *
 * \param mtx Pointer to mutex structure
 * \return true if the mutex is initialized, false otherwise
 */
static inline bool mutex_is_initialized(mutex_t *mtx) {
    return mtx->core.spin_lock != 0;
}

/*! \brief Test for recursive mutex initialized state
 *  \ingroup mutex
 *
 * \param mtx Pointer to recursive mutex structure
 * \return true if the recursive mutex is initialized, false otherwise
 */
static inline bool recursive_mutex_is_initialized(recursive_mutex_t *mtx) {
    return mtx->core.spin_lock != 0;
}

/*! \brief Helper macro for static definition of mutexes
 *  \ingroup mutex
 *
 * A mutex defined as follows:
 *
 * ```c
 * auto_init_mutex(my_mutex);
 * ```
 *
 * Is equivalent to doing
 *
 * ```c
 * static mutex_t my_mutex;
 *
 * void my_init_function() {
 *    mutex_init(&my_mutex);
 * }
 * ```
 *
 * But the initialization of the mutex is performed automatically during runtime initialization
 */
#define auto_init_mutex(name) static __attribute__((section(".mutex_array"))) mutex_t name

/*! \brief Helper macro for static definition of recursive mutexes
 *  \ingroup mutex
 *
 * A recursive mutex defined as follows:
 *
 * ```c
 * auto_init_recursive_mutex(my_recursive_mutex);
 * ```
 *
 * Is equivalent to doing
 *
 * ```c
 * static recursive_mutex_t my_recursive_mutex;
 *
 * void my_init_function() {
 *    recursive_mutex_init(&my_recursive_mutex);
 * }
 * ```
 *
 * But the initialization of the mutex is performed automatically during runtime initialization
 */
#define auto_init_recursive_mutex(name) static __attribute__((section(".mutex_array"))) recursive_mutex_t name = { .core = { .spin_lock = (spin_lock_t *)1 /* marker for runtime_init */ }, .owner = 0, .enter_count = 0 }

#ifdef __cplusplus
}
#endif
#endif
