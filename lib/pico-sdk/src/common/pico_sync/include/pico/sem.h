/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_SEM_H
#define _PICO_SEM_H

#include "pico/lock_core.h"

/** \file sem.h
 *  \defgroup sem sem
 *  \ingroup pico_sync
 *  \brief Semaphore API for restricting access to a resource
 *
 * A semaphore holds a number of available permits. `sem_acquire` methods will acquire a permit if available
 * (reducing the available count by 1) or block if the number of available permits is 0.
 * \ref sem_release() increases the number of available permits by one potentially unblocking a `sem_acquire` method.
 *
 * Note that \ref sem_release() may be called an arbitrary number of times, however the number of available
 * permits is capped to the max_permit value specified during semaphore initialization.
 *
 * Although these semaphore related functions can be used from IRQ handlers, it is obviously preferable to only
 * release semaphores from within an IRQ handler (i.e. avoid blocking)
 */

#ifdef __cplusplus
extern "C" {
#endif
typedef struct __packed_aligned semaphore {
    struct lock_core core;
    int16_t permits;
    int16_t max_permits;
} semaphore_t;


/*! \brief  Initialise a semaphore structure
 *  \ingroup sem
 *
 * \param sem Pointer to semaphore structure
 * \param initial_permits How many permits are initially acquired
 * \param max_permits  Total number of permits allowed for this semaphore
 */
void sem_init(semaphore_t *sem, int16_t initial_permits, int16_t max_permits);

/*! \brief  Return number of available permits on the semaphore
 *  \ingroup sem
 *
 * \param sem Pointer to semaphore structure
 * \return The number of permits available on the semaphore.
 */
int sem_available(semaphore_t *sem);

/*! \brief  Release a permit on a semaphore
 *  \ingroup sem
 *
 * Increases the number of permits by one (unless the number of permits is already at the maximum).
 * A blocked `sem_acquire` will be released if the number of permits is increased.
 *
 * \param sem Pointer to semaphore structure
 * \return true if the number of permits available was increased.
 */
bool sem_release(semaphore_t *sem);

/*! \brief  Reset semaphore to a specific number of available permits
 *  \ingroup sem
 *
 * Reset value should be from 0 to the max_permits specified in the init function
 *
 * \param sem Pointer to semaphore structure
 * \param permits the new number of available permits
 */
void sem_reset(semaphore_t *sem, int16_t permits);

/*! \brief  Acquire a permit from the semaphore
 *  \ingroup sem
 *
 * This function will block and wait if no permits are available.
 *
 * \param sem Pointer to semaphore structure
 */
void sem_acquire_blocking(semaphore_t *sem);

/*! \brief  Acquire a permit from a semaphore, with timeout
 *  \ingroup sem
 *
 * This function will block and wait if no permits are available, until the
 * defined timeout has been reached. If the timeout is reached the function will
 * return false, otherwise it will return true.
 *
 * \param sem Pointer to semaphore structure
 * \param timeout_ms Time to wait to acquire the semaphore, in milliseconds.
 * \return false if timeout reached, true if permit was acquired.
 */
bool sem_acquire_timeout_ms(semaphore_t *sem, uint32_t timeout_ms);

/*! \brief  Acquire a permit from a semaphore, with timeout
 *  \ingroup sem
 *
 * This function will block and wait if no permits are available, until the
 * defined timeout has been reached. If the timeout is reached the function will
 * return false, otherwise it will return true.
 *
 * \param sem Pointer to semaphore structure
 * \param timeout_us Time to wait to acquire the semaphore, in microseconds.
 * \return false if timeout reached, true if permit was acquired.
 */
bool sem_acquire_timeout_us(semaphore_t *sem, uint32_t timeout_us);

/*! \brief Wait to acquire a permit from a semaphore until a specific time
 *  \ingroup sem
 *
 * This function will block and wait if no permits are available, until the
 * specified timeout time. If the timeout is reached the function will
 * return false, otherwise it will return true.
 *
 * \param sem Pointer to semaphore structure
 * \param until The time after which to return if the sem is not available.
 * \return true if permit was acquired, false if the until time was reached before
 * acquiring.
 */
bool sem_acquire_block_until(semaphore_t *sem, absolute_time_t until);

/*! \brief Attempt to acquire a permit from a semaphore without blocking
 *  \ingroup sem
 *
 * This function will return false without blocking if no permits are
 * available, otherwise it will acquire a permit and return true.
 *
 * \param sem Pointer to semaphore structure
 * \return true if permit was acquired.
 */
bool sem_try_acquire(semaphore_t *sem);

#ifdef __cplusplus
}
#endif
#endif
