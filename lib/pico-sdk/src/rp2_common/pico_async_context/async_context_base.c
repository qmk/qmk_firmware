/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/async_context_base.h"

bool async_context_base_add_at_time_worker(async_context_t *self, async_at_time_worker_t *worker) {
    async_at_time_worker_t **prev = &self->at_time_list;
    while (*prev) {
        if (worker == *prev) {
            return false;
        }
        prev = &(*prev)->next;
    }
    *prev = worker;
    worker->next = NULL;
    return true;
}

bool async_context_base_remove_at_time_worker(async_context_t *self, async_at_time_worker_t *worker) {
    async_at_time_worker_t **prev = &self->at_time_list;
    while (*prev) {
        if (worker == *prev) {
            *prev = worker->next;
            return true;
        }
        prev = &(*prev)->next;
    }
    return false;
}

bool async_context_base_add_when_pending_worker(async_context_t *self, async_when_pending_worker_t *worker) {
    async_when_pending_worker_t **prev = &self->when_pending_list;
    while (*prev) {
        if (worker == *prev) {
            return false;
        }
        prev = &(*prev)->next;
    }
    *prev = worker;
    worker->next = NULL;
    return true;
}

bool async_context_base_remove_when_pending_worker(async_context_t *self, async_when_pending_worker_t *worker) {
    async_when_pending_worker_t **prev = &self->when_pending_list;
    while (*prev) {
        if (worker == *prev) {
            *prev = worker->next;
            return true;
        }
        prev = &(*prev)->next;
    }
    return false;
}

async_at_time_worker_t *async_context_base_remove_ready_at_time_worker(async_context_t *self) {
    async_at_time_worker_t **best_prev = NULL;
    if (self->at_time_list) {
        absolute_time_t earliest = get_absolute_time();
        for (async_at_time_worker_t **prev = &self->at_time_list; *prev; prev = &(*prev)->next) {
            if (absolute_time_diff_us((*prev)->next_time, earliest) >= 0) {
                earliest = (*prev)->next_time;
                assert(!is_at_the_end_of_time(earliest)); // should never be less than now
                best_prev = prev;
            }
        }
    }
    async_at_time_worker_t *rc;
    if (best_prev) {
        rc = *best_prev;
        *best_prev = rc->next;
    } else {
        rc = NULL;
    }
    return rc;
}

void async_context_base_refresh_next_timeout(async_context_t *self) {
    absolute_time_t earliest = at_the_end_of_time;
    for (async_at_time_worker_t *worker = self->at_time_list; worker; ) {
        async_at_time_worker_t *next = worker->next;
        if (absolute_time_diff_us(worker->next_time, earliest) > 0) {
            earliest = worker->next_time;
        }
        worker = next;
    }
    self->next_time = earliest;
}

absolute_time_t async_context_base_execute_once(async_context_t *self) {
    async_at_time_worker_t *at_time_worker;
    while (NULL != (at_time_worker = async_context_base_remove_ready_at_time_worker(self))) {
        at_time_worker->do_work(self, at_time_worker);
    }
    for(async_when_pending_worker_t *when_pending_worker = self->when_pending_list; when_pending_worker; when_pending_worker = when_pending_worker->next) {
        if (when_pending_worker->work_pending) {
            when_pending_worker->work_pending = false;
            when_pending_worker->do_work(self, when_pending_worker);
        }
    }
    async_context_base_refresh_next_timeout(self);
    return self->next_time;
}

bool async_context_base_needs_servicing(async_context_t *self) {
    absolute_time_t now = get_absolute_time();
    if (self->at_time_list) {
        for (async_at_time_worker_t *worker = self->at_time_list; worker; worker = worker->next) {
            if (absolute_time_diff_us(worker->next_time, now) >= 0) {
                return true;
            }
        }
    }
    for(async_when_pending_worker_t *when_pending_worker = self->when_pending_list; when_pending_worker; when_pending_worker = when_pending_worker->next) {
        if (when_pending_worker->work_pending) {
            return true;
        }
    }
    return false;
}