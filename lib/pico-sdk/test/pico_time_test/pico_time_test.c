/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hardware/sync.h>
#include "pico/stdlib.h"
#include "pico/test.h"
#include <inttypes.h>
PICOTEST_MODULE_NAME("pico_time_test", "pico_time test harness");

#define NUM_TIMEOUTS 500
#define MAX_TIMERS_PER_POOL 250
static_assert(PICO_TIME_DEFAULT_ALARM_POOL_MAX_TIMERS >= MAX_TIMERS_PER_POOL, "");
#define TEST_LENGTH_US 2000000

#ifndef NDEBUG
#define NUM_REPEATING_TIMERS 30
#else
#define NUM_REPEATING_TIMERS 50
#endif
static struct repeating_timer repeating_timers[NUM_REPEATING_TIMERS];
static uint repeating_timer_callback_count[NUM_REPEATING_TIMERS];

static struct timeout {
    alarm_id_t alarm_id;
    absolute_time_t target;
    absolute_time_t fired_at;
    uint pool;
    uint fired_count;
    bool cancelled;
    bool not_cancelled; // tried to cancel but it was done
} timeouts[NUM_TIMEOUTS];

int64_t timer_callback1(alarm_id_t id, void *user_data) {
    struct timeout *timeout = (struct timeout *)user_data;
    assert(timeout >= timeouts && timeout < (timeouts + NUM_TIMEOUTS));
    timeout->fired_at = get_absolute_time();
    timeout->fired_count++;
//    printf("%d %d %ld\n", timeout->pool, id, to_us_since_boot(timeout->target));
    return 0;
}

int sort_by_target(const void *a, const void *b) {
    const struct timeout *ta = (const struct timeout *)a;
    const struct timeout *tb = (const struct timeout *)b;
    int64_t delta = absolute_time_diff_us(tb->target, ta->target);
    if (delta < 0) return -1;
    else if (delta > 0) return 1;
    return 0;
}

static bool repeating_timer_callback(struct repeating_timer *t) {
    // check we get the right timer structure
    uint i = (uintptr_t)t->user_data;
    hard_assert(i == (t - repeating_timers));
    repeating_timer_callback_count[i]++;
    return true;
}

#ifndef PICO_HARDWARE_TIMER_RESOLUTION_US
#define RESOLUTION_ALLOWANCE 0
#else
#define RESOLUTION_ALLOWANCE PICO_HARDWARE_TIMER_RESOLUTION_US
#endif

int issue_195_test(void);

int main() {
    setup_default_uart();
    alarm_pool_init_default();

    PICOTEST_START();
    struct alarm_pool *pools[NUM_TIMERS];
    for(uint i=0; i<NUM_TIMERS; i++) {
        if (i == alarm_pool_hardware_alarm_num(alarm_pool_get_default())) {
            pools[i] = alarm_pool_get_default();
        } else {
            pools[i] = alarm_pool_create(i, MAX_TIMERS_PER_POOL);
        }
        PICOTEST_CHECK_AND_ABORT(pools[i], "failed to create timer pool");
    }

    // Check default config has valid data in it
    PICOTEST_START_SECTION("Alarm ordering test");

    absolute_time_t time_base = get_absolute_time();
    uint32_t init_ms = 1000;
    for(uint i = 0; i < NUM_TIMEOUTS; i++) {
//        printf("%d %p\n", i);
        absolute_time_t target;
        uint pool;
        if (1 == (i&127u)) {
            // want occasional duplicate time
            target = timeouts[i-1].target;
            pool = timeouts[i-1].pool;
        } else {
            target = delayed_by_us(time_base, init_ms + (rand() % TEST_LENGTH_US));
            pool = rand() % 4;
        }
        timeouts[i].target = target;
        timeouts[i].pool = pool;
        alarm_id_t id = alarm_pool_add_alarm_at(pools[pool], target, timer_callback1, timeouts + i, true);
        PICOTEST_CHECK_AND_ABORT(id >=0, "Failed to add timer");
    }
    PICOTEST_CHECK(absolute_time_diff_us(time_base, get_absolute_time()) < init_ms * 1000, "This is a flaky test :-(");

    uint64_t last_fired_at[NUM_TIMERS];
    uint64_t last_target[NUM_TIMERS];
    memset(&last_fired_at, 0, sizeof(last_fired_at));
    printf("Sleeping...\n");
    sleep_us(TEST_LENGTH_US + 250000);
    printf("   ...done\n");

    qsort(timeouts, NUM_TIMEOUTS, sizeof(struct timeout), sort_by_target);

    uint64_t max_jitter = 0;
    for(uint i = 0; i < NUM_TIMEOUTS; i++) {
        printf("%d %d %"PRIi64" : %"PRIi64"\n", timeouts[i].pool, timeouts[i].fired_count, to_us_since_boot(timeouts[i].fired_at), to_us_since_boot(timeouts[i].target));
        PICOTEST_CHECK(timeouts[i].fired_count, "Timer should have fired");
        PICOTEST_CHECK(timeouts[i].fired_count < 2, "Timer should only have fired once");
        uint64_t fired_at = to_us_since_boot(timeouts[i].fired_at);
        PICOTEST_CHECK(timeouts[i].fired_count != 1 || fired_at >= MAX(RESOLUTION_ALLOWANCE,
                                                                       to_us_since_boot(timeouts[i].target)) - RESOLUTION_ALLOWANCE, "Timer fired early");
        // we need to be in order unless the targets are the same in which case order is arbitrary
        PICOTEST_CHECK(timeouts[i].fired_count != 1 || fired_at > MAX(RESOLUTION_ALLOWANCE, last_fired_at[timeouts[i].pool]) - RESOLUTION_ALLOWANCE ||
                               to_us_since_boot(timeouts[i].target) == last_target[timeouts[i].pool], "Timer fired out of order");
        last_fired_at[timeouts[i].pool] = fired_at;
        last_target[timeouts[i].pool] = to_us_since_boot(timeouts[i].target);
        if (timeouts[i].fired_count == 1) {
            uint64_t jitter = absolute_time_diff_us(timeouts[i].target, timeouts[i].fired_at);
            if (jitter > max_jitter) {
                max_jitter = jitter;
            }
        }
    }
    printf("MAX JITTER: %dus\n", (uint)max_jitter);

    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("Alarm completion or canceled");
    memset(timeouts, 0, sizeof(timeouts));

    absolute_time_t time_base = get_absolute_time();
    // this runs concurrently with the firing, so some are in the past
    uint approx_past_timeouts = 0;
//    uint32_t save = save_and_disable_interrupts();
    for(uint i = 0; i < NUM_TIMEOUTS; i++) {
//        printf("%d %p\n", i);
        absolute_time_t target = delayed_by_us(time_base, (rand() % TEST_LENGTH_US));
        if (absolute_time_diff_us(target, get_absolute_time()) >= 0) {
            approx_past_timeouts++;
        }
        uint pool = rand() % 4;
        timeouts[i].target = target;
        timeouts[i].pool = pool;
        alarm_id_t id = alarm_pool_add_alarm_at(pools[pool], target, timer_callback1, timeouts + i, true);
        timeouts[i].alarm_id = id;
        PICOTEST_CHECK_AND_ABORT(id >=0, "Failed to add timer");
        if (id && !(rand() & 6)) {
            uint j = rand() % (i + 1);
            if (timeouts[j].alarm_id && !timeouts[j].cancelled && !timeouts[j].not_cancelled) {
//                alarm_pool_dump(pools[pool]);
//                printf("removing %d\n", timeouts[j].alarm_id);
                if (alarm_pool_cancel_alarm(pools[timeouts[j].pool], timeouts[j].alarm_id)) {
                    timeouts[j].cancelled = true;
                } else {
                    timeouts[j].not_cancelled = true;
                }
//                printf("removed %d\n", timeouts[j].alarm_id);
//                alarm_pool_dump(pools[pool]);
            }
        }
        busy_wait_us_32(2000); // we want to overlap with the firing
    }
    printf("approx past timeouts %d/%d\n", approx_past_timeouts, NUM_TIMEOUTS);
    sleep_us(TEST_LENGTH_US  - 2000 * NUM_TIMEOUTS / 4 + 250000);
    for(uint i = 0; i < NUM_TIMEOUTS/4; i++) {
        printf("%d %d %d/%d/%d %"PRIi64" : %"PRIi64"\n", timeouts[i].pool, (int)timeouts[i].alarm_id, timeouts[i].fired_count, timeouts[i].cancelled,
               timeouts[i].not_cancelled, to_us_since_boot(timeouts[i].fired_at), to_us_since_boot(timeouts[i].target));
        uint total = timeouts[i].fired_count + timeouts[i].cancelled;
        PICOTEST_CHECK( timeouts[i].not_cancelled ? timeouts[i].fired_count : true, "Timer that failed to cancel should have fired");
        PICOTEST_CHECK(total == 1, "Timer should have fired or been cancelled");
    }

    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("Repeating timertest");
    for(uint i=0;i<NUM_REPEATING_TIMERS;i++) {

        add_repeating_timer_us(500+ (rand() & 1023), repeating_timer_callback, (void *)(uintptr_t)i, repeating_timers + i);
    }

    sleep_ms(3000);
    uint callbacks = 0;
    for(uint i=0;i<NUM_REPEATING_TIMERS;i++) {
        PICOTEST_CHECK(cancel_repeating_timer(repeating_timers + i), "Cancelling repeating timer should succeed");
        PICOTEST_CHECK(repeating_timer_callback_count[i] > 1, "Each repeating timer should have been called back multiple times");
        callbacks += repeating_timer_callback_count[i];
    }
    uint callbacks2 = 0;
    for(uint i=0;i<NUM_REPEATING_TIMERS;i++) {
        PICOTEST_CHECK(!cancel_repeating_timer(repeating_timers + i), "Re-cancelling repeating timer should fail");
        callbacks2 += repeating_timer_callback_count[i];
    }
    PICOTEST_CHECK(callbacks == callbacks2, "No repeating timers should have been called back after being cancelled")

    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("end of time");
    PICOTEST_CHECK(absolute_time_diff_us(at_the_end_of_time, get_absolute_time()) < 0, "now should be before the end of time")
    PICOTEST_CHECK(absolute_time_diff_us(get_absolute_time(), at_the_end_of_time) > 0, "the end of time should be after now")
    PICOTEST_CHECK(absolute_time_diff_us(at_the_end_of_time, at_the_end_of_time) == 0, "the end of time should equal itself")
    absolute_time_t near_the_end_of_time;
    update_us_since_boot(&near_the_end_of_time, 0x7ffffeffffffffff);
    PICOTEST_CHECK(absolute_time_diff_us(near_the_end_of_time, at_the_end_of_time) > 0, "near the end of time should be before the end of time")
    PICOTEST_END_SECTION();

    if (issue_195_test()) {
        return -1;
    }

    PICOTEST_END_TEST();
}

#define ISSUE_195_TIMER_DELAY 50
volatile int issue_195_counter;
int64_t issue_195_callback(alarm_id_t id, void *user_data) {
    issue_195_counter++;
    return -ISSUE_195_TIMER_DELAY;
}

int issue_195_test(void) {
    PICOTEST_START_SECTION("Issue #195 race condition - without fix may hang on gcc 10.2.1 release builds");
    absolute_time_t t1 = get_absolute_time();
    int id = add_alarm_in_us(ISSUE_195_TIMER_DELAY, issue_195_callback, NULL, true);
    for(uint i=0;i<5000;i++) {
        sleep_us(100);
        sleep_us(100);
        uint delay = 9; // 9 seems to be the magic number (at least for reproducing on 10.2.1)
        sleep_us(delay);
    }
    absolute_time_t t2 = get_absolute_time();
    cancel_alarm(id);
    int expected_count = absolute_time_diff_us(t1, t2) / ISSUE_195_TIMER_DELAY;
    printf("Timer fires approx_expected=%d actual=%d\n", expected_count, issue_195_counter);
    PICOTEST_END_SECTION();
    return 0;
}

