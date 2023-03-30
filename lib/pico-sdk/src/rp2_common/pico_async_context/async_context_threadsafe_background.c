/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include "pico/async_context_threadsafe_background.h"
#include "pico/async_context_base.h"
#include "pico/sync.h"
#include "hardware/irq.h"

static const async_context_type_t template;
static async_context_threadsafe_background_t *async_contexts_by_user_irq[NUM_USER_IRQS];

static void low_priority_irq_handler(void);
static void process_under_lock(async_context_threadsafe_background_t *self);
static int64_t alarm_handler(alarm_id_t id, void *user_data);

#ifndef ASYNC_CONTEXT_THREADSAFE_BACKGROUND_DEFAULT_LOW_PRIORITY_IRQ_HANDLER_PRIORITY
#define ASYNC_CONTEXT_THREADSAFE_BACKGROUND_DEFAULT_LOW_PRIORITY_IRQ_HANDLER_PRIORITY PICO_LOWEST_IRQ_PRIORITY
#endif

#ifndef ASYNC_CONTEXT_THREADSAFE_BACKGROUND_ALARM_POOL_MAX_ALARMS
#define ASYNC_CONTEXT_THREADSAFE_BACKGROUND_ALARM_POOL_MAX_ALARMS 4
#endif

async_context_threadsafe_background_config_t async_context_threadsafe_background_default_config(void) {
    async_context_threadsafe_background_config_t config = {
            .low_priority_irq_handler_priority = ASYNC_CONTEXT_THREADSAFE_BACKGROUND_DEFAULT_LOW_PRIORITY_IRQ_HANDLER_PRIORITY,
            .custom_alarm_pool = NULL,
    };
    return config;
}

static inline uint recursive_mutex_enter_count(recursive_mutex_t *mutex) {
    return mutex->enter_count;
}

static inline lock_owner_id_t recursive_mutex_owner(recursive_mutex_t *mutex) {
    return mutex->owner;
}

static void async_context_threadsafe_background_wake_up(async_context_t *self_base) {
    async_context_threadsafe_background_t *self = (async_context_threadsafe_background_t *)self_base;
#if ASYNC_CONTEXT_THREADSAFE_BACKGROUND_MULTI_CORE
    if (self_base->core_num == get_core_num()) {
        // on same core, can dispatch directly
        irq_set_pending(self->low_priority_irq_num);
    } else {
        // remove the existing alarm (it may have already fired) so we don't overflow the pool with repeats
        //
        // note that force_alarm_id is not protected here, however if we miss removing one, they will fire
        // almost immediately anyway (since they were set in the past)
        alarm_id_t force_alarm_id = self->force_alarm_id;
        if (force_alarm_id > 0) {
            alarm_pool_cancel_alarm(self->alarm_pool, force_alarm_id);
        }
        // we cause an early timeout (0 is always in the past) on the alarm_pool core
        // note that by the time this returns, the timer may already have fired, so we
        // may end up setting self->force_alarm_id to a stale timer id, but that is fine as we
        // will harmlessly cancel it again next time
        self->force_alarm_id = alarm_pool_add_alarm_at_force_in_context(self->alarm_pool, from_us_since_boot(0),
                                                                        alarm_handler, self);
    }
#else
    // on same core, can dispatch directly
    irq_set_pending(self->low_priority_irq_num);
#endif
    sem_release(&self->work_needed_sem);
}

// Prevent background processing in pensv and access by the other core
// These methods are called in pensv context and on either core
// They can be called recursively
static inline void lock_acquire(async_context_threadsafe_background_t *self) {
    // Lock the other core and stop low_prio_irq running
    recursive_mutex_enter_blocking(&self->lock_mutex);
}

static void async_context_threadsafe_background_lock_check(async_context_t *self_base) {
    async_context_threadsafe_background_t *self = (async_context_threadsafe_background_t *)self_base;
    // Lock the other core and stop low_prio_irq running
    if (recursive_mutex_enter_count(&self->lock_mutex) < 1 || recursive_mutex_owner(&self->lock_mutex) != lock_get_caller_owner_id()) {
        panic_compact("async_context lock_check failed");
    }
}

typedef struct sync_func_call{
    async_when_pending_worker_t worker;
    semaphore_t sem;
    uint32_t (*func)(void *param);
    void *param;
    uint32_t rc;
} sync_func_call_t;

static void handle_sync_func_call(async_context_t *context, async_when_pending_worker_t *worker) {
    sync_func_call_t *call = (sync_func_call_t *)worker;
    call->rc = call->func(call->param);
    sem_release(&call->sem);
    async_context_remove_when_pending_worker(context, worker);
}


static void lock_release(async_context_threadsafe_background_t *self) {
    bool outermost = 1 == recursive_mutex_enter_count(&self->lock_mutex);
    // note that it is *not* a requirement to have low_prio_irq_missed handled on the
    // same core and in low-priority riq, as we are only *logically* a single thread. the user
    // is already free to call from either core, and this would only happen on a different
    // core, if the user *themselves* is acquiring the lock from other cores anyway

#if ASYNC_CONTEXT_THREADSAFE_BACKGROUND_MULTI_CORE
    bool wake_other_core = false;
#endif
    if (outermost) {
        // note that we always do a processing on outermost lock exit, to facilitate cases
        // like lwIP where we have no notification when lwIP timers are added.
#if ASYNC_CONTEXT_THREADSAFE_BACKGROUND_MULTI_CORE
        if (self->core.core_num == get_core_num()) {
            process_under_lock(self);
        } else if (async_context_base_needs_servicing(&self->core)) {
            // have to wake up other core
            wake_other_core = true;
        }
#else
        process_under_lock(self);
#endif
    }
    recursive_mutex_exit(&self->lock_mutex);
#if ASYNC_CONTEXT_THREADSAFE_BACKGROUND_MULTI_CORE
    if (wake_other_core) {
        async_context_threadsafe_background_wake_up(&self->core);
    }
#endif
}

uint32_t async_context_threadsafe_background_execute_sync(async_context_t *self_base, uint32_t (*func)(void *param), void *param) {
    async_context_threadsafe_background_t *self = (async_context_threadsafe_background_t*)self_base;
#if ASYNC_CONTEXT_THREADSAFE_BACKGROUND_MULTI_CORE
    if (self_base->core_num != get_core_num()) {
        hard_assert(!recursive_mutex_enter_count(&self->lock_mutex));
        sync_func_call_t call;
        call.worker.do_work = handle_sync_func_call;
        call.func = func;
        call.param = param;
        sem_init(&call.sem, 0, 1);
        async_context_add_when_pending_worker(self_base, &call.worker);
        async_context_set_work_pending(self_base, &call.worker);
        sem_acquire_blocking(&call.sem);
        return call.rc;
    }
#endif
    // short-circuit if we are on the right core
    lock_acquire(self);
    uint32_t rc = func(param);
    lock_release(self);
    return rc;
}

static bool low_prio_irq_init(async_context_threadsafe_background_t  *self, uint8_t priority) {
    assert(get_core_num() == self->core.core_num);
    int irq = user_irq_claim_unused(false);
    if (irq < 0) return false;
    self->low_priority_irq_num = (uint8_t) irq;
    uint index = irq - FIRST_USER_IRQ;
    assert(index < count_of(async_contexts_by_user_irq));
    async_contexts_by_user_irq[index] = self;
    irq_set_exclusive_handler(self->low_priority_irq_num, low_priority_irq_handler);
    irq_set_enabled(self->low_priority_irq_num, true);
    irq_set_priority(self->low_priority_irq_num, priority);
    return true;
}

static void low_prio_irq_deinit(async_context_threadsafe_background_t *self) {
    if (self->low_priority_irq_num > 0) {
        assert(get_core_num() == self->core.core_num);
        irq_set_enabled(self->low_priority_irq_num, false);
        irq_remove_handler(self->low_priority_irq_num, low_priority_irq_handler);
        user_irq_unclaim(self->low_priority_irq_num);
        self->low_priority_irq_num = 0;
    }
}

static int64_t alarm_handler(__unused alarm_id_t id, void *user_data) {
    async_context_threadsafe_background_t *self = (async_context_threadsafe_background_t*)user_data;
#if ASYNC_CONTEXT_THREADSAFE_BACKGROUND_MULTI_CORE
    self->force_alarm_id = 0;
#endif
    self->alarm_pending = false;
    async_context_threadsafe_background_wake_up(&self->core);
    return 0;
}

bool async_context_threadsafe_background_init(async_context_threadsafe_background_t *self, async_context_threadsafe_background_config_t *config) {
    memset(self, 0, sizeof(*self));
    self->core.type = &template;
    self->core.flags = ASYNC_CONTEXT_FLAG_CALLBACK_FROM_IRQ | ASYNC_CONTEXT_FLAG_CALLBACK_FROM_NON_IRQ;
    self->core.core_num = get_core_num();
    if (config->custom_alarm_pool) {
        self->alarm_pool = config->custom_alarm_pool;
    } else {
#if PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
        self->alarm_pool = alarm_pool_create_with_unused_hardware_alarm(ASYNC_CONTEXT_THREADSAFE_BACKGROUND_ALARM_POOL_MAX_ALARMS);
        self->alarm_pool_owned = true;
#else
        self->alarm_pool = alarm_pool_get_default();
#if ASYNC_CONTEXT_THREADSAFE_BACKGROUND_MULTI_CORE
        if (self->core.core_num != alarm_pool_core_num(self->alarm_pool)) {
            self->alarm_pool = alarm_pool_create_with_unused_hardware_alarm(ASYNC_CONTEXT_THREADSAFE_BACKGROUND_ALARM_POOL_MAX_ALARMS);
            self->alarm_pool_owned = true;
        }
#endif
#endif
    }
    assert(self->core.core_num == alarm_pool_core_num(self->alarm_pool));
    sem_init(&self->work_needed_sem, 1, 1);
    recursive_mutex_init(&self->lock_mutex);
    bool ok = low_prio_irq_init(self, config->low_priority_irq_handler_priority);
    return ok;
}

static void async_context_threadsafe_background_set_work_pending(async_context_t *self_base, async_when_pending_worker_t *worker) {
    worker->work_pending = true;
    async_context_threadsafe_background_wake_up(self_base);
}

static void async_context_threadsafe_background_deinit(async_context_t *self_base) {
    async_context_threadsafe_background_t *self = (async_context_threadsafe_background_t *)self_base;
    // todo we do not currently handle this correctly; we could, but seems like a rare case
    assert(get_core_num() == self_base->core_num);
    low_prio_irq_deinit(self);
    if (self->alarm_id > 0) alarm_pool_cancel_alarm(self->alarm_pool, self->alarm_id);
#if ASYNC_CONTEXT_THREADSAFE_BACKGROUND_MULTI_CORE
    if (self->alarm_pool_owned) {
        alarm_pool_destroy(self->alarm_pool);
    }
#endif
    // acquire the lock to make sure the callback is not running (we have already disabled the IRQ
    recursive_mutex_enter_blocking(&self->lock_mutex);
    recursive_mutex_exit(&self->lock_mutex);
    memset(self, 0, sizeof(*self));
}

static void process_under_lock(async_context_threadsafe_background_t *self) {
#ifndef NDEBUG
    async_context_threadsafe_background_lock_check(&self->core);
    assert(self->core.core_num == get_core_num());
#endif
    do {
        absolute_time_t next_time = async_context_base_execute_once(&self->core);
        // if the next wakeup time is in the past then loop
        if (absolute_time_diff_us(get_absolute_time(), next_time) <= 0) continue;
        // if there is no next wakeup time, we're done
        if (is_at_the_end_of_time(next_time)) {
            // cancel the alarm early (we will have been called soon after an alarm wakeup), so that
            // we don't risk alarm_id collision.
            if (self->alarm_id > 0) {
                alarm_pool_cancel_alarm(self->alarm_pool, self->alarm_id);
                self->alarm_id = 0;
            }
            break;
        }
        // the following is an optimization; we are often called much more frequently than timeouts actually change,
        // and removing and re-adding the timers has some non-trivial overhead (10s of microseconds), we choose
        // to allow the existing timeout to run to completion, and then re-asses from there, unless the new wakeup
        // time is before the last one set.
        //
        // note that alarm_pending is not protected, however, if it is wrong, it is wrong in the sense that it is
        // false when it should be true, so if it is wrong due to a race, we will cancel and re-add the alarm which is safe.
        if (self->alarm_pending && absolute_time_diff_us(self->last_set_alarm_time, next_time) > 0) break;
        // cancel the existing alarm (it may no longer exist)
        if (self->alarm_id > 0) alarm_pool_cancel_alarm(self->alarm_pool, self->alarm_id);
        self->last_set_alarm_time = next_time;
        self->alarm_pending = true;
        self->alarm_id = alarm_pool_add_alarm_at(self->alarm_pool, next_time, alarm_handler, self, false);
        if (self->alarm_id > 0) break;
        self->alarm_pending = false;
    } while (true);
}

// Low priority interrupt handler to perform background processing
static void low_priority_irq_handler(void) {
    uint index = __get_current_exception() - VTABLE_FIRST_IRQ - FIRST_USER_IRQ;
    assert(index < count_of(async_contexts_by_user_irq));
    async_context_threadsafe_background_t *self = async_contexts_by_user_irq[index];
    if (!self) return;
    assert(self->core.core_num == get_core_num());
    if (recursive_mutex_try_enter(&self->lock_mutex, NULL)) {
        // if the recurse count is not 1 then we have pre-empted something which held the lock on the same core,
        // so we cannot do processing here (however processing will be done when that lock is released)
        if (recursive_mutex_enter_count(&self->lock_mutex) == 1) {
            process_under_lock(self);
        }
        recursive_mutex_exit(&self->lock_mutex);
    }
}

static void async_context_threadsafe_background_wait_until(__unused async_context_t *self_base, absolute_time_t until) {
    // can be called in IRQs, in which case we just have to wait
    if (__get_current_exception()) {
        busy_wait_until(until);
    } else {
        sleep_until(until);
    }
}

static void async_context_threadsafe_background_wait_for_work_until(async_context_t *self_base, absolute_time_t until) {
    async_context_threadsafe_background_t *self = (async_context_threadsafe_background_t *)self_base;
    sem_acquire_block_until(&self->work_needed_sem, until);
}

static bool async_context_threadsafe_background_add_at_time_worker(async_context_t *self_base, async_at_time_worker_t *worker) {
    async_context_threadsafe_background_t *self = (async_context_threadsafe_background_t *)self_base;
    lock_acquire(self);
    bool rc = async_context_base_add_at_time_worker(self_base, worker);
    lock_release(self);
    return rc;
}

static bool async_context_threadsafe_background_remove_at_time_worker(async_context_t *self_base, async_at_time_worker_t *worker) {
    async_context_threadsafe_background_t *self = (async_context_threadsafe_background_t *)self_base;
    lock_acquire(self);
    bool rc = async_context_base_remove_at_time_worker(self_base, worker);
    lock_release(self);
    return rc;
}

static bool async_context_threadsafe_background_add_when_pending_worker(async_context_t *self_base, async_when_pending_worker_t *worker) {
    async_context_threadsafe_background_t *self = (async_context_threadsafe_background_t *)self_base;
    lock_acquire(self);
    bool rc = async_context_base_add_when_pending_worker(self_base, worker);
    lock_release(self);
    return rc;
}

static bool async_context_threadsafe_background_when_pending_worker(async_context_t *self_base, async_when_pending_worker_t *worker) {
    async_context_threadsafe_background_t *self = (async_context_threadsafe_background_t *)self_base;
    lock_acquire(self);
    bool rc = async_context_base_remove_when_pending_worker(self_base, worker);
    lock_release(self);
    return rc;
}

static void async_context_threadsafe_background_acquire_lock_blocking(async_context_t *self_base) {
    lock_acquire((async_context_threadsafe_background_t *) self_base);
}

static void async_context_threadsafe_background_release_lock(async_context_t *self_base) {
    lock_release((async_context_threadsafe_background_t *)self_base);
}

static const async_context_type_t template = {
        .type = ASYNC_CONTEXT_THREADSAFE_BACKGROUND,
        .acquire_lock_blocking = async_context_threadsafe_background_acquire_lock_blocking,
        .release_lock = async_context_threadsafe_background_release_lock,
        .lock_check = async_context_threadsafe_background_lock_check,
        .execute_sync = async_context_threadsafe_background_execute_sync,
        .add_at_time_worker = async_context_threadsafe_background_add_at_time_worker,
        .remove_at_time_worker = async_context_threadsafe_background_remove_at_time_worker,
        .add_when_pending_worker = async_context_threadsafe_background_add_when_pending_worker,
        .remove_when_pending_worker = async_context_threadsafe_background_when_pending_worker,
        .set_work_pending = async_context_threadsafe_background_set_work_pending,
        .poll = 0,
        .wait_until = async_context_threadsafe_background_wait_until,
        .wait_for_work_until = async_context_threadsafe_background_wait_for_work_until,
        .deinit = async_context_threadsafe_background_deinit,
};


