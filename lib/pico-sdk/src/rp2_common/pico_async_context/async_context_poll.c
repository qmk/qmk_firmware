/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include "pico/async_context_poll.h"
#include "pico/async_context_base.h"
#include "pico/sync.h"

static void noop(__unused async_context_t *context) { }

static const async_context_type_t template;

bool async_context_poll_init_with_defaults(async_context_poll_t *self) {
    memset(self, 0, sizeof(*self));
    self->core.core_num = get_core_num();
    self->core.type = &template;
    self->core.flags = ASYNC_CONTEXT_FLAG_POLLED | ASYNC_CONTEXT_FLAG_CALLBACK_FROM_NON_IRQ;
    sem_init(&self->sem, 1, 1);
    return true;
}

static void async_context_poll_wake_up(async_context_t *self_base) {
    sem_release(&((async_context_poll_t *)self_base)->sem);
}

static void async_context_poll_requires_update(async_context_t *self_base, async_when_pending_worker_t *worker) {
    worker->work_pending = true;
    async_context_poll_wake_up(self_base);
}

static void async_context_poll_poll(async_context_t *self_base) {
    async_context_base_execute_once(self_base);
}

static void async_context_poll_wait_until(__unused async_context_t *self_base, absolute_time_t until) {
    sleep_until(until);
}

static void async_context_poll_wait_for_work_until(async_context_t *self_base, absolute_time_t until) {
    absolute_time_t next_time = self_base->next_time;
    async_context_poll_t *self = (async_context_poll_t *)self_base;
    sem_acquire_block_until(&self->sem, absolute_time_min(next_time, until));
}

static void async_context_poll_lock_check(async_context_t *self_base) {
    if (__get_current_exception() || get_core_num() != self_base->core_num) {
        panic("async_context_poll context check failed (IRQ or wrong core)");
    }
}

uint32_t async_context_poll_execute_sync(__unused async_context_t *context, uint32_t (*func)(void *param), void *param) {
    return func(param);
}

static const async_context_type_t template = {
        .type = ASYNC_CONTEXT_POLL,
        .acquire_lock_blocking = noop,
        .release_lock = noop,
        .lock_check = async_context_poll_lock_check,
        .execute_sync = async_context_poll_execute_sync,
        .add_at_time_worker = async_context_base_add_at_time_worker,
        .remove_at_time_worker = async_context_base_remove_at_time_worker,
        .add_when_pending_worker = async_context_base_add_when_pending_worker,
        .remove_when_pending_worker = async_context_base_remove_when_pending_worker,
        .set_work_pending = async_context_poll_requires_update,
        .poll = async_context_poll_poll,
        .wait_until = async_context_poll_wait_until,
        .wait_for_work_until = async_context_poll_wait_for_work_until,
        .deinit = noop,
};
