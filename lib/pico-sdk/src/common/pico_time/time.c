/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <limits.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "pico.h"
#include "pico/time.h"
#include "pico/util/pheap.h"
#include "pico/sync.h"

const absolute_time_t ABSOLUTE_TIME_INITIALIZED_VAR(nil_time, 0);
const absolute_time_t ABSOLUTE_TIME_INITIALIZED_VAR(at_the_end_of_time, INT64_MAX);

typedef struct alarm_pool_entry {
    absolute_time_t target;
    alarm_callback_t callback;
    void *user_data;
} alarm_pool_entry_t;

typedef struct alarm_pool {
    pheap_t *heap;
    spin_lock_t *lock;
    alarm_pool_entry_t *entries;
    // one byte per entry, used to provide more longevity to public IDs than heap node ids do
    // (this is increment every time the heap node id is re-used)
    uint8_t *entry_ids_high;
    alarm_id_t alarm_in_progress; // this is set during a callback from the IRQ handler... it can be cleared by alarm_cancel to prevent repeats
    uint8_t hardware_alarm_num;
    uint8_t core_num;
} alarm_pool_t;

#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
// To avoid bringing in calloc, we statically allocate the arrays and the heap
PHEAP_DEFINE_STATIC(default_alarm_pool_heap, PICO_TIME_DEFAULT_ALARM_POOL_MAX_TIMERS);
static alarm_pool_entry_t default_alarm_pool_entries[PICO_TIME_DEFAULT_ALARM_POOL_MAX_TIMERS];
static uint8_t default_alarm_pool_entry_ids_high[PICO_TIME_DEFAULT_ALARM_POOL_MAX_TIMERS];
static lock_core_t sleep_notifier;

static alarm_pool_t default_alarm_pool = {
        .heap = &default_alarm_pool_heap,
        .entries = default_alarm_pool_entries,
        .entry_ids_high = default_alarm_pool_entry_ids_high,
};

static inline bool default_alarm_pool_initialized(void) {
    return default_alarm_pool.lock != NULL;
}
#endif

static alarm_pool_t *pools[NUM_TIMERS];
static void alarm_pool_post_alloc_init(alarm_pool_t *pool, uint hardware_alarm_num);


static inline alarm_pool_entry_t *get_entry(alarm_pool_t *pool, pheap_node_id_t id) {
    assert(id && id <= pool->heap->max_nodes);
    return pool->entries + id - 1;
}

static inline uint8_t *get_entry_id_high(alarm_pool_t *pool, pheap_node_id_t id) {
    assert(id && id <= pool->heap->max_nodes);
    return pool->entry_ids_high + id - 1;
}

bool timer_pool_entry_comparator(void *user_data, pheap_node_id_t a, pheap_node_id_t b) {
    alarm_pool_t *pool = (alarm_pool_t *)user_data;
    return to_us_since_boot(get_entry(pool, a)->target) < to_us_since_boot(get_entry(pool, b)->target);
}

static inline alarm_id_t make_public_id(uint8_t id_high, pheap_node_id_t id) {
    return (alarm_id_t)(((uint)id_high << 8u * sizeof(id)) | id);
}

void alarm_pool_init_default() {
#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
    // allow multiple calls for ease of use from host tests
    if (!default_alarm_pool_initialized()) {
        ph_post_alloc_init(default_alarm_pool.heap, PICO_TIME_DEFAULT_ALARM_POOL_MAX_TIMERS,
                           timer_pool_entry_comparator, &default_alarm_pool);
        hardware_alarm_claim(PICO_TIME_DEFAULT_ALARM_POOL_HARDWARE_ALARM_NUM);
        alarm_pool_post_alloc_init(&default_alarm_pool,
                                   PICO_TIME_DEFAULT_ALARM_POOL_HARDWARE_ALARM_NUM);
    }
    lock_init(&sleep_notifier, PICO_SPINLOCK_ID_TIMER);
#endif
}

#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
alarm_pool_t *alarm_pool_get_default() {
    assert(default_alarm_pool_initialized());
    return &default_alarm_pool;
}
#endif

static pheap_node_id_t add_alarm_under_lock(alarm_pool_t *pool, absolute_time_t time, alarm_callback_t callback,
                                       void *user_data, pheap_node_id_t reuse_id, bool create_if_past, bool *missed) {
    pheap_node_id_t id;
    if (reuse_id) {
        assert(!ph_contains_node(pool->heap, reuse_id));
        id = reuse_id;
    } else {
        id = ph_new_node(pool->heap);
    }
    if (id) {
        alarm_pool_entry_t *entry = get_entry(pool, id);
        entry->target = time;
        entry->callback = callback;
        entry->user_data = user_data;
        if (id == ph_insert_node(pool->heap, id)) {
            bool is_missed = hardware_alarm_set_target(pool->hardware_alarm_num, time);
            if (is_missed && !create_if_past) {
                ph_remove_and_free_node(pool->heap, id);
            }
            if (missed) *missed = is_missed;
        }
    }
    return id;
}

static void alarm_pool_alarm_callback(uint alarm_num) {
    // note this is called from timer IRQ handler
    alarm_pool_t *pool = pools[alarm_num];
    bool again;
    do {
        absolute_time_t now = get_absolute_time();
        alarm_callback_t callback = NULL;
        absolute_time_t target = nil_time;
        void *user_data = NULL;
        uint8_t id_high;
        again = false;
        uint32_t save = spin_lock_blocking(pool->lock);
        pheap_node_id_t next_id = ph_peek_head(pool->heap);
        if (next_id) {
            alarm_pool_entry_t *entry = get_entry(pool, next_id);
            if (absolute_time_diff_us(now, entry->target) <= 0) {
                // we don't free the id in case we need to re-add the timer
                pheap_node_id_t __unused removed_id = ph_remove_head(pool->heap, false);
                assert(removed_id == next_id); // will be true under lock
                target = entry->target;
                callback = entry->callback;
                user_data = entry->user_data;
                assert(callback);
                id_high = *get_entry_id_high(pool, next_id);
                pool->alarm_in_progress = make_public_id(id_high, removed_id);
            } else {
                if (hardware_alarm_set_target(alarm_num, entry->target)) {
                    again = true;
                }
            }
        }
        spin_unlock(pool->lock, save);
        if (callback) {
            int64_t repeat = callback(make_public_id(id_high, next_id), user_data);
            save = spin_lock_blocking(pool->lock);
            // todo think more about whether we want to keep calling
            if (repeat < 0 && pool->alarm_in_progress) {
                assert(pool->alarm_in_progress == make_public_id(id_high, next_id));
                add_alarm_under_lock(pool, delayed_by_us(target, (uint64_t)-repeat), callback, user_data, next_id, true, NULL);
            } else if (repeat > 0 && pool->alarm_in_progress) {
                assert(pool->alarm_in_progress == make_public_id(id_high, next_id));
                add_alarm_under_lock(pool, delayed_by_us(get_absolute_time(), (uint64_t)repeat), callback, user_data, next_id,
                                     true, NULL);
            } else {
                // need to return the id to the heap
                ph_free_node(pool->heap, next_id);
                (*get_entry_id_high(pool, next_id))++; // we bump it for next use of id
            }
            pool->alarm_in_progress = 0;
            spin_unlock(pool->lock, save);
            again = true;
        }
    } while (again);
}

// note the timer is create with IRQs on this core
alarm_pool_t *alarm_pool_create(uint hardware_alarm_num, uint max_timers) {
    alarm_pool_t *pool = (alarm_pool_t *) malloc(sizeof(alarm_pool_t));
    pool->heap = ph_create(max_timers, timer_pool_entry_comparator, pool);
    pool->entries = (alarm_pool_entry_t *)calloc(max_timers, sizeof(alarm_pool_entry_t));
    pool->entry_ids_high = (uint8_t *)calloc(max_timers, sizeof(uint8_t));
    hardware_alarm_claim(hardware_alarm_num);
    alarm_pool_post_alloc_init(pool, hardware_alarm_num);
    return pool;
}

alarm_pool_t *alarm_pool_create_with_unused_hardware_alarm(uint max_timers) {
    alarm_pool_t *pool = (alarm_pool_t *) malloc(sizeof(alarm_pool_t));
    pool->heap = ph_create(max_timers, timer_pool_entry_comparator, pool);
    pool->entries = (alarm_pool_entry_t *)calloc(max_timers, sizeof(alarm_pool_entry_t));
    pool->entry_ids_high = (uint8_t *)calloc(max_timers, sizeof(uint8_t));
    alarm_pool_post_alloc_init(pool, (uint)hardware_alarm_claim_unused(true));
    return pool;
}

void alarm_pool_post_alloc_init(alarm_pool_t *pool, uint hardware_alarm_num) {
    hardware_alarm_cancel(hardware_alarm_num);
    hardware_alarm_set_callback(hardware_alarm_num, alarm_pool_alarm_callback);
    pool->lock = spin_lock_instance(next_striped_spin_lock_num());
    pool->hardware_alarm_num = (uint8_t) hardware_alarm_num;
    pool->core_num = (uint8_t) get_core_num();
    pools[hardware_alarm_num] = pool;
}

void alarm_pool_destroy(alarm_pool_t *pool) {
#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
    if (pool == &default_alarm_pool) {
        assert(false); // attempt to delete default alarm pool
        return;
    }
#endif
    assert(pools[pool->hardware_alarm_num] == pool);
    pools[pool->hardware_alarm_num] = NULL;
    // todo clear out timers
    ph_destroy(pool->heap);
    hardware_alarm_set_callback(pool->hardware_alarm_num, NULL);
    hardware_alarm_unclaim(pool->hardware_alarm_num);
    free(pool->entry_ids_high);
    free(pool->entries);
    free(pool);
}

alarm_id_t alarm_pool_add_alarm_at(alarm_pool_t *pool, absolute_time_t time, alarm_callback_t callback,
                                   void *user_data, bool fire_if_past) {
    bool missed = false;

    alarm_id_t public_id;
    do {
        uint8_t id_high = 0;
        uint32_t save = spin_lock_blocking(pool->lock);

        pheap_node_id_t id = add_alarm_under_lock(pool, time, callback, user_data, 0, false, &missed);
        if (id) id_high = *get_entry_id_high(pool, id);

        spin_unlock(pool->lock, save);

        if (!id) {
            // no space in pheap to allocate an alarm
            return -1;
        }

        // note that if missed was true, then the id was never added to the pheap (because we
        // passed false for create_if_past arg above)
        public_id = missed ? 0 : make_public_id(id_high, id);
        if (missed && fire_if_past) {
            // ... so if fire_if_past == true we call the callback
            int64_t repeat = callback(public_id, user_data);
            // if not repeated we have no id to return so set public_id to 0,
            // otherwise we need to repeat, but will assign a new id next time
            // todo arguably this does mean that the id passed to the first callback may differ from subsequent calls
            if (!repeat) {
                public_id = 0;
                break;
            } else if (repeat < 0) {
                time = delayed_by_us(time, (uint64_t)-repeat);
            } else {
                time = delayed_by_us(get_absolute_time(), (uint64_t)repeat);
            }
        } else {
            // either:
            // a) missed == false && public_id is > 0
            // b) missed == true && fire_if_past == false && public_id = 0
            // but we are done in either case
            break;
        }
    } while (true);
    return public_id;
}

alarm_id_t alarm_pool_add_alarm_at_force_in_context(alarm_pool_t *pool, absolute_time_t time, alarm_callback_t callback,
                                                    void *user_data) {
    bool missed = false;

    uint8_t id_high = 0;
    uint32_t save = spin_lock_blocking(pool->lock);

    pheap_node_id_t id = add_alarm_under_lock(pool, time, callback, user_data, 0, true, &missed);
    if (id) id_high = *get_entry_id_high(pool, id);
    spin_unlock(pool->lock, save);
    if (!id) return -1;
    if (missed) {
        // we want to fire the timer forcibly because it is in the past. Note that we do
        // not care about racing with other timers, as it is harmless to have the IRQ
        // wake up one time too many, we just need to make sure it does wake up
        hardware_alarm_force_irq(pool->hardware_alarm_num);
    }
    return make_public_id(id_high, id);
}

bool alarm_pool_cancel_alarm(alarm_pool_t *pool, alarm_id_t alarm_id) {
    bool rc = false;
    uint32_t save = spin_lock_blocking(pool->lock);
    pheap_node_id_t id = (pheap_node_id_t) alarm_id;
    if (ph_contains_node(pool->heap, id)) {
        assert(alarm_id != pool->alarm_in_progress); // it shouldn't be in the heap if it is in progress
        // check we have the right high value
        uint8_t id_high = (uint8_t)((uint)alarm_id >> 8u * sizeof(pheap_node_id_t));
        if (id_high == *get_entry_id_high(pool, id)) {
            rc = ph_remove_and_free_node(pool->heap, id);
            // note we don't bother to remove the actual hardware alarm timeout...
            // it will either do callbacks or not depending on other alarms, and reset the next timeout itself
            assert(rc);
        }
    } else {
        if (alarm_id == pool->alarm_in_progress) {
            // make sure the alarm doesn't repeat
            pool->alarm_in_progress = 0;
        }
    }
    spin_unlock(pool->lock, save);
    return rc;
}

uint alarm_pool_hardware_alarm_num(alarm_pool_t *pool) {
    return pool->hardware_alarm_num;
}

uint alarm_pool_core_num(alarm_pool_t *pool) {
    return pool->core_num;
}

static void alarm_pool_dump_key(pheap_node_id_t id, void *user_data) {
    alarm_pool_t *pool = (alarm_pool_t *)user_data;
#if PICO_ON_DEVICE
    printf("%lld (hi %02x)", to_us_since_boot(get_entry(pool, id)->target), *get_entry_id_high(pool, id));
#else
    printf("%"PRIu64, to_us_since_boot(get_entry(pool, id)->target));
#endif
}

static int64_t repeating_timer_callback(__unused alarm_id_t id, void *user_data) {
    repeating_timer_t *rt = (repeating_timer_t *)user_data;
    assert(rt->alarm_id == id);
    if (rt->callback(rt)) {
        return rt->delay_us;
    } else {
        rt->alarm_id = 0;
        return 0;
    }
}

bool alarm_pool_add_repeating_timer_us(alarm_pool_t *pool, int64_t delay_us, repeating_timer_callback_t callback, void *user_data, repeating_timer_t *out) {
    if (!delay_us) delay_us = 1;
    out->pool = pool;
    out->callback = callback;
    out->delay_us = delay_us;
    out->user_data = user_data;
    out->alarm_id = alarm_pool_add_alarm_at(pool, make_timeout_time_us((uint64_t)(delay_us >= 0 ? delay_us : -delay_us)),
                                            repeating_timer_callback, out, true);
    // note that if out->alarm_id is 0, then the callback was called during the above call (fire_if_past == true)
    // and then the callback removed itself.
    return out->alarm_id >= 0;
}

bool cancel_repeating_timer(repeating_timer_t *timer) {
    bool rc = false;
    if (timer->alarm_id) {
        rc = alarm_pool_cancel_alarm(timer->pool, timer->alarm_id);
        timer->alarm_id = 0;
    }
    return rc;
}

void alarm_pool_dump(alarm_pool_t *pool) {
    uint32_t save = spin_lock_blocking(pool->lock);
    ph_dump(pool->heap, alarm_pool_dump_key, pool);
    spin_unlock(pool->lock, save);
}

#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
static int64_t sleep_until_callback(__unused alarm_id_t id, __unused void *user_data) {
    uint32_t save = spin_lock_blocking(sleep_notifier.spin_lock);
    lock_internal_spin_unlock_with_notify(&sleep_notifier, save);
    return 0;
}
#endif

void sleep_until(absolute_time_t t) {
#if PICO_ON_DEVICE && !defined(NDEBUG)
    if (__get_current_exception()) {
        panic("Attempted to sleep inside of an exception handler; use busy_wait if you must");
    }
#endif
#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
    uint64_t t_us = to_us_since_boot(t);
    uint64_t t_before_us = t_us - PICO_TIME_SLEEP_OVERHEAD_ADJUST_US;
    // needs to work in the first PICO_TIME_SLEEP_OVERHEAD_ADJUST_US of boot
    if (t_before_us > t_us) t_before_us = 0;
    absolute_time_t t_before;
    update_us_since_boot(&t_before, t_before_us);
    if (absolute_time_diff_us(get_absolute_time(), t_before) > 0) {
        if (add_alarm_at(t_before, sleep_until_callback, NULL, false) >= 0) {
            // able to add alarm for just before the time
            while (!time_reached(t_before)) {
                uint32_t save = spin_lock_blocking(sleep_notifier.spin_lock);
                lock_internal_spin_unlock_with_wait(&sleep_notifier, save);
            }
        }
    }
#else
    // hook in case we're in RTOS; note we assume using the alarm pool is better always if available.
    sync_internal_yield_until_before(t);
#endif
    // now wait until the exact time
    busy_wait_until(t);
}

void sleep_us(uint64_t us) {
#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
    sleep_until(make_timeout_time_us(us));
#else
    if (us < PICO_TIME_SLEEP_OVERHEAD_ADJUST_US) {
        busy_wait_us(us);
    } else {
        // hook in case we're in RTOS; note we assume using the alarm pool is better always if available.
        absolute_time_t t = make_timeout_time_us(us - PICO_TIME_SLEEP_OVERHEAD_ADJUST_US);
        sync_internal_yield_until_before(t);

        // then wait the rest of thw way
        busy_wait_until(t);
    }
#endif
}

void sleep_ms(uint32_t ms) {
    sleep_us(ms * 1000ull);
}

bool best_effort_wfe_or_timeout(absolute_time_t timeout_timestamp) {
#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
    if (__get_current_exception()) {
        tight_loop_contents();
        return time_reached(timeout_timestamp);
    } else {
        alarm_id_t id;
        id = add_alarm_at(timeout_timestamp, sleep_until_callback, NULL, false);
        if (id <= 0) {
            tight_loop_contents();
            return time_reached(timeout_timestamp);
        } else {
            __wfe();
            // we need to clean up if it wasn't us that caused the wfe; if it was this will be a noop.
            cancel_alarm(id);
            return time_reached(timeout_timestamp);
        }
    }
#else
    tight_loop_contents();
    return time_reached(timeout_timestamp);
#endif
}
