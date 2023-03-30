/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdlib.h>
#include <string.h>
#include "pico/util/queue.h"

void queue_init_with_spinlock(queue_t *q, uint element_size, uint element_count, uint spinlock_num) {
    lock_init(&q->core, spinlock_num);
    q->data = (uint8_t *)calloc(element_count + 1, element_size);
    q->element_count = (uint16_t)element_count;
    q->element_size = (uint16_t)element_size;
    q->wptr = 0;
    q->rptr = 0;
}

void queue_free(queue_t *q) {
    free(q->data);
}

static inline void *element_ptr(queue_t *q, uint index) {
    assert(index <= q->element_count);
    return q->data + index * q->element_size;
}

static inline uint16_t inc_index(queue_t *q, uint16_t index) {
    if (++index > q->element_count) { // > because we have element_count + 1 elements
        index = 0;
    }

#if PICO_QUEUE_MAX_LEVEL
    uint16_t level = queue_get_level_unsafe(q);
    if (level > q->max_level) {
        q->max_level = level;
    }
#endif

    return index;
}

static bool queue_add_internal(queue_t *q, const void *data, bool block) {
    do {
        uint32_t save = spin_lock_blocking(q->core.spin_lock);
        if (queue_get_level_unsafe(q) != q->element_count) {
            memcpy(element_ptr(q, q->wptr), data, q->element_size);
            q->wptr = inc_index(q, q->wptr);
            lock_internal_spin_unlock_with_notify(&q->core, save);
            return true;
        }
        if (block) {
            lock_internal_spin_unlock_with_wait(&q->core, save);
        } else {
            spin_unlock(q->core.spin_lock, save);
            return false;
        }
    } while (true);
}

static bool queue_remove_internal(queue_t *q, void *data, bool block) {
    do {
        uint32_t save = spin_lock_blocking(q->core.spin_lock);
        if (queue_get_level_unsafe(q) != 0) {
            memcpy(data, element_ptr(q, q->rptr), q->element_size);
            q->rptr = inc_index(q, q->rptr);
            lock_internal_spin_unlock_with_notify(&q->core, save);
            return true;
        }
        if (block) {
            lock_internal_spin_unlock_with_wait(&q->core, save);
        } else {
            spin_unlock(q->core.spin_lock, save);
            return false;
        }
    } while (true);
}

static bool queue_peek_internal(queue_t *q, void *data, bool block) {
    do {
        uint32_t save = spin_lock_blocking(q->core.spin_lock);
        if (queue_get_level_unsafe(q) != 0) {
            memcpy(data, element_ptr(q, q->rptr), q->element_size);
            lock_internal_spin_unlock_with_notify(&q->core, save);
            return true;
        }
        if (block) {
            lock_internal_spin_unlock_with_wait(&q->core, save);
        } else {
            spin_unlock(q->core.spin_lock, save);
            return false;
        }
    } while (true);
}

bool queue_try_add(queue_t *q, const void *data) {
    return queue_add_internal(q, data, false);
}

bool queue_try_remove(queue_t *q, void *data) {
    return queue_remove_internal(q, data, false);
}

bool queue_try_peek(queue_t *q, void *data) {
    return queue_peek_internal(q, data, false);
}

void queue_add_blocking(queue_t *q, const void *data) {
    queue_add_internal(q, data, true);
}

void queue_remove_blocking(queue_t *q, void *data) {
    queue_remove_internal(q, data, true);
}

void queue_peek_blocking(queue_t *q, void *data) {
    queue_peek_internal(q, data, true);
}
