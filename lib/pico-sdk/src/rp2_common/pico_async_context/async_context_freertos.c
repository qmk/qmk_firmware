/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include "pico/async_context_freertos.h"
#include "pico/async_context_base.h"
#include "pico/sync.h"
#include "hardware/irq.h"

#include "semphr.h"

#if configNUM_CORES > 1 && !defined(configUSE_CORE_AFFINITY)
#error async_context_freertos requires configUSE_CORE_AFFINITY under SMP
#endif

static const async_context_type_t template;

static void async_context_freertos_acquire_lock_blocking(async_context_t *self_base);
static void async_context_freertos_release_lock(async_context_t *self_base);
static void async_context_freertos_lock_check(async_context_t *self_base);

static TickType_t sensible_ticks_until(absolute_time_t until) {
    TickType_t ticks;
    int64_t delay_us = absolute_time_diff_us(get_absolute_time(), until);
    if (delay_us <= 0) {
        ticks = 0;
    } else {
        static const uint32_t max_delay = 60000000;
        uint32_t delay_us_32 = delay_us > max_delay ? max_delay : (uint32_t) delay_us;
        ticks = pdMS_TO_TICKS((delay_us_32+999)/1000);
        // we want to round up, as both rounding down to zero is wrong (may produce no delays
        // where delays are needed), but also we don't want to wake up, and then realize there
        // is no work to do yet!
        ticks++;
    }
    return ticks;
}

static void process_under_lock(async_context_freertos_t *self) {
#ifndef NDEBUG
    async_context_freertos_lock_check(&self->core);
#endif
    bool repeat;
    do {
        repeat = false;
        absolute_time_t next_time = async_context_base_execute_once(&self->core);
        TickType_t ticks;
        if (is_at_the_end_of_time(next_time)) {
            ticks = portMAX_DELAY;
        } else {
            ticks = sensible_ticks_until(next_time);
        }
        if (ticks) {
            // last parameter (timeout) is also 'ticks', since there is no point waiting to change the period
            // for longer than the period itself!
            repeat = pdFALSE == xTimerChangePeriod(self->timer_handle, ticks, ticks);
        } else {
            repeat = true;
        }
    } while (repeat);
}

static void async_context_task(__unused void *vself) {
    async_context_freertos_t *self = (async_context_freertos_t *)vself;
    do {
        ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
        if (self->task_should_exit) break;
        async_context_freertos_acquire_lock_blocking(&self->core);
        process_under_lock(self);
        async_context_freertos_release_lock(&self->core);
        __sev(); // it is possible regular code is waiting on a WFE on the other core
    } while (!self->task_should_exit);
    vTaskDelete(NULL);
}

static void async_context_freertos_wake_up(async_context_t *self_base) {
    async_context_freertos_t *self = (async_context_freertos_t *)self_base;
    if (self->task_handle) {
        if (portCHECK_IF_IN_ISR()) {
            vTaskNotifyGiveFromISR(self->task_handle, NULL);
            xSemaphoreGiveFromISR(self->work_needed_sem, NULL);
        } else {
            // we don't want to wake ourselves up (we will only ever be called
            // from the async_context_task if we own the lock, in which case processing
            // will already happen when the lock is finally unlocked
            if (xTaskGetCurrentTaskHandle() != self->task_handle) {
                xTaskNotifyGive(self->task_handle);
                xSemaphoreGive(self->work_needed_sem);
            } else {
#ifndef NDEBUG
                async_context_freertos_lock_check(self_base);
#endif
            }
        }
    }
}

static void timer_handler(__unused TimerHandle_t handle)
{
    async_context_freertos_t *self = (async_context_freertos_t *)pvTimerGetTimerID(handle);
    async_context_freertos_wake_up(&self->core);
}

bool async_context_freertos_init(async_context_freertos_t *self, async_context_freertos_config_t *config) {
    memset(self, 0, sizeof(*self));
    self->core.type = &template;
    self->core.flags = ASYNC_CONTEXT_FLAG_CALLBACK_FROM_NON_IRQ;
    self->core.core_num = get_core_num();
    self->lock_mutex = xSemaphoreCreateRecursiveMutex();
    self->work_needed_sem = xSemaphoreCreateBinary();
    self->timer_handle = xTimerCreate( "async_context_timer",       // Just a text name, not used by the kernel.
                                    portMAX_DELAY,
                                    pdFALSE,        // The timers will auto-reload themselves when they expire.
                                    self,
                                    timer_handler);

    if (!self->lock_mutex ||
        !self->work_needed_sem ||
        !self->timer_handle ||
        pdPASS != xTaskCreate(async_context_task, "async_context_task", config->task_stack_size, self,
                config->task_priority, &self->task_handle)) {
        async_context_deinit(&self->core);
        return false;
    }
#if configNUM_CORES > 1
    UBaseType_t core_id = config->task_core_id;
    if (core_id == (UBaseType_t)-1) {
        core_id = portGET_CORE_ID();
    }
    // we must run on a single core
    vTaskCoreAffinitySet(self->task_handle, 1u << core_id);
#endif
    return true;
}

static uint32_t end_task_func(void *param) {
    async_context_freertos_t *self = (async_context_freertos_t *)param;
    // we will immediately exit
    self->task_should_exit = true;
    return 0;
}

void async_context_freertos_deinit(async_context_t *self_base) {
    async_context_freertos_t *self = (async_context_freertos_t *)self_base;
    if (self->task_handle) {
        async_context_execute_sync(self_base, end_task_func, self_base);
    }
    if (self->timer_handle) {
        xTimerDelete(self->timer_handle, 0);
    }
    if (self->lock_mutex) {
        vSemaphoreDelete(self->lock_mutex);
    }
    if (self->work_needed_sem) {
        vSemaphoreDelete(self->work_needed_sem);
    }
    memset(self, 0, sizeof(*self));
}

void async_context_freertos_acquire_lock_blocking(async_context_t *self_base) {
    async_context_freertos_t *self = (async_context_freertos_t *)self_base;
    // Lock the other core and stop low_prio_irq running
    assert(!portCHECK_IF_IN_ISR());
    xSemaphoreTakeRecursive(self->lock_mutex, portMAX_DELAY);
    self->nesting++;
}

void async_context_freertos_lock_check(__unused async_context_t *self_base) {
#ifndef NDEBUG
    async_context_freertos_t *self = (async_context_freertos_t *)self_base;
    // Lock the other core and stop low_prio_irq running
    assert(xSemaphoreGetMutexHolder(self->lock_mutex) == xTaskGetCurrentTaskHandle());
#endif
}

typedef struct sync_func_call{
    async_when_pending_worker_t worker;
    SemaphoreHandle_t sem;
    uint32_t (*func)(void *param);
    void *param;
    uint32_t rc;
} sync_func_call_t;

static void handle_sync_func_call(async_context_t *context, async_when_pending_worker_t *worker) {
    sync_func_call_t *call = (sync_func_call_t *)worker;
    call->rc = call->func(call->param);
    xSemaphoreGive(call->sem);
    async_context_remove_when_pending_worker(context, worker);
}

uint32_t async_context_freertos_execute_sync(async_context_t *self_base, uint32_t (*func)(void *param), void *param) {
    async_context_freertos_t *self = (async_context_freertos_t*)self_base;
    hard_assert(xSemaphoreGetMutexHolder(self->lock_mutex) != xTaskGetCurrentTaskHandle());
    sync_func_call_t call;
    call.worker.do_work = handle_sync_func_call;
    call.func = func;
    call.param = param;
    call.sem = xSemaphoreCreateBinary();
    async_context_add_when_pending_worker(self_base, &call.worker);
    async_context_set_work_pending(self_base, &call.worker);
    xSemaphoreTake(call.sem, portMAX_DELAY);
    vSemaphoreDelete(call.sem);
    return call.rc;
}

void async_context_freertos_release_lock(async_context_t *self_base) {
    async_context_freertos_t *self = (async_context_freertos_t *)self_base;
    bool do_wakeup = false;
    if (self->nesting == 1) {
        // note that we always do a processing on outermost lock exit, to facilitate cases
        // like lwIP where we have no notification when lwIP timers are added.
        //
        // this operation must be done from the right task
        if (self->task_handle != xTaskGetCurrentTaskHandle()) {
            // note we defer the wakeup until after we release the lock, otherwise it can be wasteful
            // (waking up the task, but then having it block immediately on us)
            do_wakeup = true;
        } else {
            process_under_lock(self);
        }
    }
    --self->nesting;
    xSemaphoreGiveRecursive(self->lock_mutex);
    if (do_wakeup) {
        async_context_freertos_wake_up(self_base);
    }
}

static bool async_context_freertos_add_at_time_worker(async_context_t *self_base, async_at_time_worker_t *worker) {
    async_context_freertos_acquire_lock_blocking(self_base);
    bool rc = async_context_base_add_at_time_worker(self_base, worker);
    async_context_freertos_release_lock(self_base);
    return rc;
}

static bool async_context_freertos_remove_at_time_worker(async_context_t *self_base, async_at_time_worker_t *worker) {
    async_context_freertos_acquire_lock_blocking(self_base);
    bool rc = async_context_base_remove_at_time_worker(self_base, worker);
    async_context_freertos_release_lock(self_base);
    return rc;
}

static bool async_context_freertos_add_when_pending_worker(async_context_t *self_base, async_when_pending_worker_t *worker) {
    async_context_freertos_acquire_lock_blocking(self_base);
    bool rc = async_context_base_add_when_pending_worker(self_base, worker);
    async_context_freertos_release_lock(self_base);
    return rc;
}

static bool async_context_freertos_remove_when_pending_worker(async_context_t *self_base, async_when_pending_worker_t *worker) {
    async_context_freertos_acquire_lock_blocking(self_base);
    bool rc = async_context_base_remove_when_pending_worker(self_base, worker);
    async_context_freertos_release_lock(self_base);
    return rc;
}

static void async_context_freertos_set_work_pending(async_context_t *self_base, async_when_pending_worker_t *worker) {
    worker->work_pending = true;
    async_context_freertos_wake_up(self_base);
}

static void async_context_freertos_wait_until(async_context_t *self_base, absolute_time_t until) {
    assert(!portCHECK_IF_IN_ISR());
    TickType_t ticks = sensible_ticks_until(until);
    vTaskDelay(ticks);
}

static void async_context_freertos_wait_for_work_until(async_context_t *self_base, absolute_time_t until) {
    async_context_freertos_t *self = (async_context_freertos_t *)self_base;
    assert(!portCHECK_IF_IN_ISR());
    while (!time_reached(until)) {
        TickType_t ticks = sensible_ticks_until(until);
        if (!ticks || xSemaphoreTake(self->work_needed_sem, ticks)) return;
    }
}

static const async_context_type_t template = {
        .type = ASYNC_CONTEXT_FREERTOS,
        .acquire_lock_blocking = async_context_freertos_acquire_lock_blocking,
        .release_lock = async_context_freertos_release_lock,
        .lock_check = async_context_freertos_lock_check,
        .execute_sync = async_context_freertos_execute_sync,
        .add_at_time_worker = async_context_freertos_add_at_time_worker,
        .remove_at_time_worker = async_context_freertos_remove_at_time_worker,
        .add_when_pending_worker = async_context_freertos_add_when_pending_worker,
        .remove_when_pending_worker = async_context_freertos_remove_when_pending_worker,
        .set_work_pending = async_context_freertos_set_work_pending,
        .poll = 0,
        .wait_until = async_context_freertos_wait_until,
        .wait_for_work_until = async_context_freertos_wait_for_work_until,
        .deinit = async_context_freertos_deinit,
};
