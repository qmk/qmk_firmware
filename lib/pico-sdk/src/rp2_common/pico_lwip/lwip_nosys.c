/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/async_context.h"

#include <lwip/init.h>
#include "lwip/timeouts.h"

static void update_next_timeout(async_context_t *context, async_when_pending_worker_t *worker);
static void lwip_timeout_reached(async_context_t *context, async_at_time_worker_t *worker);

static async_when_pending_worker_t always_pending_update_timeout_worker = {
        .do_work = update_next_timeout
};

static async_at_time_worker_t lwip_timeout_worker = {
        .do_work = lwip_timeout_reached,
};

static void lwip_timeout_reached(__unused async_context_t *context, __unused async_at_time_worker_t *worker) {
    assert(worker == &lwip_timeout_worker);
    sys_check_timeouts();
}

static void update_next_timeout(async_context_t *context, async_when_pending_worker_t *worker) {
    assert(worker == &always_pending_update_timeout_worker);
    // we want to run on every execution of the helper to re-reflect any changes
    // to the underlying lwIP timers which may have happened in the interim
    // (note that worker will be called on every outermost exit of the async_context
    // lock, and lwIP timers should not be modified whilst not holding the lock.
    worker->work_pending = true;
    uint32_t sleep_ms = sys_timeouts_sleeptime();
    if (sleep_ms == SYS_TIMEOUTS_SLEEPTIME_INFINITE) {
        lwip_timeout_worker.next_time = at_the_end_of_time;
    } else {
        lwip_timeout_worker.next_time = make_timeout_time_ms(sleep_ms);
    }
    async_context_add_at_time_worker(context, &lwip_timeout_worker);
}

bool lwip_nosys_init(async_context_t *context) {
    static bool done_lwip_init;
    if (!done_lwip_init) {
        lwip_init();
        done_lwip_init = true;
    }
    // we want the worker to be called on every async helper run (starting with the next)
    always_pending_update_timeout_worker.work_pending = true;
    async_context_add_when_pending_worker(context, &always_pending_update_timeout_worker);
    return true;
}

void lwip_nosys_deinit(async_context_t *context) {
    async_context_remove_at_time_worker(context, &lwip_timeout_worker);
    async_context_remove_when_pending_worker(context, &always_pending_update_timeout_worker);
}

#if NO_SYS
/* lwip has provision for using a mutex, when applicable */
sys_prot_t sys_arch_protect(void) {
    return 0;
}

void sys_arch_unprotect(__unused sys_prot_t pval) {
}

/* lwip needs a millisecond time source, and the TinyUSB board support code has one available */
uint32_t sys_now(void) {
    return to_ms_since_boot(get_absolute_time());
}
#endif