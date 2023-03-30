/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_UTIL_QUEUE_H
#define _PICO_UTIL_QUEUE_H

#include "pico.h"
#include "hardware/sync.h"

// PICO_CONFIG: PICO_QUEUE_MAX_LEVEL, Maintain a field for the highest level that has been reached by a queue, type=bool, default=0, advanced=true, group=queue
#ifndef PICO_QUEUE_MAX_LEVEL
#define PICO_QUEUE_MAX_LEVEL 0
#endif

/** \file queue.h
 * \defgroup queue queue
 * Multi-core and IRQ safe queue implementation.
 *
 * Note that this queue stores values of a specified size, and pushed values are copied into the queue
 * \ingroup pico_util
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "pico/lock_core.h"

typedef struct {
    lock_core_t core;
    uint8_t *data;
    uint16_t wptr;
    uint16_t rptr;
    uint16_t element_size;
    uint16_t element_count;
#if PICO_QUEUE_MAX_LEVEL
    uint16_t max_level;
#endif
} queue_t;

/*! \brief Initialise a queue with a specific spinlock for concurrency protection
 *  \ingroup queue
 *
 * \param q Pointer to a queue_t structure, used as a handle
 * \param element_size Size of each value in the queue
 * \param element_count Maximum number of entries in the queue
 * \param spinlock_num The spin ID used to protect the queue
 */
void queue_init_with_spinlock(queue_t *q, uint element_size, uint element_count, uint spinlock_num);

/*! \brief Initialise a queue, allocating a (possibly shared) spinlock
 *  \ingroup queue
 *
 * \param q Pointer to a queue_t structure, used as a handle
 * \param element_size Size of each value in the queue
 * \param element_count Maximum number of entries in the queue
 */
static inline void queue_init(queue_t *q, uint element_size, uint element_count) {
    return queue_init_with_spinlock(q, element_size, element_count, next_striped_spin_lock_num());
}

/*! \brief Destroy the specified queue.
 *  \ingroup queue
 *
 * \param q Pointer to a queue_t structure, used as a handle
 *
 * Does not deallocate the queue_t structure itself.
 */
void queue_free(queue_t *q);

/*! \brief Unsafe check of level of the specified queue.
 *  \ingroup queue
 *
 * \param q Pointer to a queue_t structure, used as a handle
 * \return Number of entries in the queue
 *
 * This does not use the spinlock, so may return incorrect results if the
 * spin lock is not externally locked
 */
static inline uint queue_get_level_unsafe(queue_t *q) {
    int32_t rc = (int32_t)q->wptr - (int32_t)q->rptr;
    if (rc < 0) {
        rc += q->element_count + 1;
    }
    return (uint)rc;
}

/*! \brief Check of level of the specified queue.
 *  \ingroup queue
 *
 * \param q Pointer to a queue_t structure, used as a handle
 * \return Number of entries in the queue
 */
static inline uint queue_get_level(queue_t *q) {
    uint32_t save = spin_lock_blocking(q->core.spin_lock);
    uint level = queue_get_level_unsafe(q);
    spin_unlock(q->core.spin_lock, save);
    return level;
}

#if PICO_QUEUE_MAX_LEVEL
/*! \brief Returns the highest level reached by the specified queue since it was created
 *         or since the max level was reset
 *  \ingroup queue
 *
 * \param q Pointer to a queue_t structure, used as a handle
 * \return Maximum level of the queue
 */
static inline uint queue_get_max_level(queue_t *q) {
    return q->max_level;
}
#endif

#if PICO_QUEUE_MAX_LEVEL
/*! \brief Reset the highest level reached of the specified queue.
 *  \ingroup queue
 *
 * \param q Pointer to a queue_t structure, used as a handle
 */
static inline void queue_reset_max_level(queue_t *q) {
    uint32_t save = spin_lock_blocking(q->core.spin_lock);
    q->max_level = queue_get_level_unsafe(q);
    spin_unlock(q->core.spin_lock, save);
}
#endif

/*! \brief Check if queue is empty
 *  \ingroup queue
 *
 * \param q Pointer to a queue_t structure, used as a handle
 * \return true if queue is empty, false otherwise
 *
 * This function is interrupt and multicore safe.
 */
static inline bool queue_is_empty(queue_t *q) {
    return queue_get_level(q) == 0;
}

/*! \brief Check if queue is full
 *  \ingroup queue
 *
 * \param q Pointer to a queue_t structure, used as a handle
 * \return true if queue is full, false otherwise
 *
 * This function is interrupt and multicore safe.
 */
static inline bool queue_is_full(queue_t *q) {
    return queue_get_level(q) == q->element_count;
}

// nonblocking queue access functions:

/*! \brief Non-blocking add value queue if not full
 *  \ingroup queue
 *
 * \param q Pointer to a queue_t structure, used as a handle
 * \param data Pointer to value to be copied into the queue
 * \return true if the value was added
 *
 * If the queue is full this function will return immediately with false, otherwise
 * the data is copied into a new value added to the queue, and this function will return true.
 */
bool queue_try_add(queue_t *q, const void *data);

/*! \brief Non-blocking removal of entry from the queue if non empty
 *  \ingroup queue
 *
 * \param q Pointer to a queue_t structure, used as a handle
 * \param data Pointer to the location to receive the removed value
 * \return true if a value was removed
 *
 * If the queue is not empty function will copy the removed value into the location provided and return
 * immediately with true, otherwise the function will return immediately with false.
 */
bool queue_try_remove(queue_t *q, void *data);

/*! \brief Non-blocking peek at the next item to be removed from the queue
 *  \ingroup queue
 *
 * \param q Pointer to a queue_t structure, used as a handle
 * \param data Pointer to the location to receive the peeked value
 * \return true if there was a value to peek
 *
 * If the queue is not empty this function will return immediately with true with the peeked entry
 * copied into the location specified by the data parameter, otherwise the function will return false.
 */
bool queue_try_peek(queue_t *q, void *data);

// blocking queue access functions:

/*! \brief Blocking add of value to queue
 *  \ingroup queue
 *
 * \param q Pointer to a queue_t structure, used as a handle
 * \param data Pointer to value to be copied into the queue
 *
 * If the queue is full this function will block, until a removal happens on the queue
 */
void queue_add_blocking(queue_t *q, const void *data);

/*! \brief Blocking remove entry from queue
 *  \ingroup queue
 *
 * \param q Pointer to a queue_t structure, used as a handle
 * \param data Pointer to the location to receive the removed value
 *
 * If the queue is empty this function will block until a value is added.
 */
void queue_remove_blocking(queue_t *q, void *data);

/*! \brief Blocking peek at next value to be removed from queue
 *  \ingroup queue
 *
 * \param q Pointer to a queue_t structure, used as a handle
 * \param data Pointer to the location to receive the peeked value
 *
 * If the queue is empty function will block until a value is added
 */
void queue_peek_blocking(queue_t *q, void *data);

#ifdef __cplusplus
}
#endif
#endif
