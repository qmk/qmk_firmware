/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/timer.h"
#if defined(__unix__) || defined(__APPLE__)
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#endif

// in our case not a busy wait
PICO_WEAK_FUNCTION_DEF(busy_wait_us)
void PICO_WEAK_FUNCTION_IMPL_NAME(busy_wait_us_32)(uint32_t delay_us) {
#if defined(__unix__) || defined(__APPLE__)
    usleep(delay_us);
#else
    assert(false);
#endif
}
PICO_WEAK_FUNCTION_DEF(busy_wait_us)
void PICO_WEAK_FUNCTION_IMPL_NAME(busy_wait_us)(uint64_t delay_us) {
    absolute_time_t t;
    update_us_since_boot(&t, time_us_64() + delay_us);
    busy_wait_until(t);
}

// this may or may not wrap
PICO_WEAK_FUNCTION_DEF(time_us_64)
uint64_t PICO_WEAK_FUNCTION_IMPL_NAME(time_us_64)() {
#if defined(__unix__) || defined(__APPLE__)
//    struct timeval tv;
//    gettimeofday(&tv, NULL);
//    return tv.tv_sec * (uint64_t) 1000000 + tv.tv_usec;
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * (uint64_t) 1000000 + ts.tv_nsec / 1000;
#else
    panic_unsupported();
#endif
}

PICO_WEAK_FUNCTION_DEF(timer_us_32)
uint32_t PICO_WEAK_FUNCTION_IMPL_NAME(timer_us_32)() {
    return (uint32_t) time_us_64();
}

PICO_WEAK_FUNCTION_DEF(time_reached)
bool PICO_WEAK_FUNCTION_IMPL_NAME(time_reached)(absolute_time_t t) {
    uint64_t target = to_us_since_boot(t);
    return time_us_64() >= target;
}

PICO_WEAK_FUNCTION_DEF(busy_wait_until)
void PICO_WEAK_FUNCTION_IMPL_NAME(busy_wait_until)(absolute_time_t target) {
#if defined(__unix__)
    struct timespec tspec;
    tspec.tv_sec = to_us_since_boot(target) / 1000000;
    tspec.tv_nsec = (to_us_since_boot(target) % 1000000) * 1000;
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &tspec, NULL);
#else
    const int chunk = 1u<<30u;
    uint64_t target_us = to_us_since_boot(target);
    uint64_t time_us = time_us_64();
    while ((int64_t)(target_us - time_us) >= chunk) {
        busy_wait_us_32(chunk);
        time_us = time_us_64();
    }
    if (target_us > time_us) {
        busy_wait_us_32(target_us - time_us);
    }
#endif
}

static uint8_t claimed_alarms;

void hardware_alarm_claim(uint alarm_num) {
    assert(!(claimed_alarms & (1u << alarm_num)));
    claimed_alarms |= 1u <<alarm_num;
}

void hardware_alarm_unclaim(uint alarm_num) {
    assert(claimed_alarms & (1u << alarm_num));
    claimed_alarms &= ~(1u <<alarm_num);
}

int hardware_alarm_claim_unused(bool required) {
    int alarm_id = claimed_alarms ? __builtin_clz(~claimed_alarms) : 1;
    if (alarm_id >= NUM_TIMERS) return -1;
    claimed_alarms |= 1u << alarm_id;
    return alarm_id;
}

PICO_WEAK_FUNCTION_DEF(hardware_alarm_set_callback)
void PICO_WEAK_FUNCTION_IMPL_NAME(hardware_alarm_set_callback)(uint alarm_num, hardware_alarm_callback_t callback) {
    panic_unsupported();
}

PICO_WEAK_FUNCTION_DEF(hardware_alarm_set_target)
bool PICO_WEAK_FUNCTION_IMPL_NAME(hardware_alarm_set_target)(uint alarm_num, absolute_time_t target) {
    panic_unsupported();
}

PICO_WEAK_FUNCTION_DEF(hardware_alarm_cancel)
void PICO_WEAK_FUNCTION_IMPL_NAME(hardware_alarm_cancel)(uint alarm_num) {
    panic_unsupported();
}

PICO_WEAK_FUNCTION_DEF(hardware_alarm_force_irq)
void PICO_WEAK_FUNCTION_IMPL_NAME(hardware_alarm_force_irq)(uint alarm_num) {
    panic_unsupported();
}
