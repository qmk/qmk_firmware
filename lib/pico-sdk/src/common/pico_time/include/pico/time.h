/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_TIME_H
#define _PICO_TIME_H

#include "pico.h"
#include "hardware/timer.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file time.h
 *  \defgroup pico_time pico_time
 *
 * API for accurate timestamps, sleeping, and time based callbacks
 *
 * \note The functions defined here provide a much more powerful and user friendly wrapping around the
 * low level hardware timer functionality. For these functions (and any other SDK functionality
 * e.g. timeouts, that relies on them) to work correctly, the hardware timer should not be modified. i.e. it is expected
 * to be monotonically increasing once per microsecond. Fortunately there is no need to modify the hardware
 * timer as any functionality you can think of that isn't already covered here can easily be modelled
 * by adding or subtracting a constant value from the unmodified hardware timer.
 *
 * \sa \ref hardware_timer
 */

// PICO_CONFIG: PARAM_ASSERTIONS_ENABLED_TIME, Enable/disable assertions in the time module, type=bool, default=0, group=pico_time
#ifndef PARAM_ASSERTIONS_ENABLED_TIME
#define PARAM_ASSERTIONS_ENABLED_TIME 0
#endif

// PICO_CONFIG: PICO_TIME_SLEEP_OVERHEAD_ADJUST_US, How many microseconds to wake up early (and then busy_wait) to account for timer overhead when sleeping in low power mode, type=int, default=6, group=pico_time
#ifndef PICO_TIME_SLEEP_OVERHEAD_ADJUST_US
#define PICO_TIME_SLEEP_OVERHEAD_ADJUST_US 6
#endif
/*!
 * \defgroup timestamp timestamp
 *  \ingroup pico_time
 * \brief Timestamp functions relating to points in time (including the current time)
 *
 * These are functions for dealing with timestamps (i.e. instants in time) represented by the type absolute_time_t. This opaque
 * type is provided to help prevent accidental mixing of timestamps and relative time values.
 */

/*! \brief Return a representation of the current time.
 * \ingroup timestamp
 *
 * Returns an opaque high fidelity representation of the current time sampled during the call.
 *
 * \return the absolute time (now) of the hardware timer
 *
 * \sa absolute_time_t
 * \sa sleep_until()
 * \sa time_us_64()
 */
static inline absolute_time_t get_absolute_time(void) {
    absolute_time_t t;
    update_us_since_boot(&t, time_us_64());
    return t;
}

static inline uint32_t us_to_ms(uint64_t us) {
    if (us >> 32u) {
        return (uint32_t)(us / 1000u);
    } else {
        return ((uint32_t)us) / 1000u;
    }
}

/*! fn to_ms_since_boot
 * \ingroup timestamp
 * \brief Convert a timestamp into a number of milliseconds since boot.
 * \param t an absolute_time_t value to convert
 * \return the number of milliseconds since boot represented by t
 * \sa to_us_since_boot()
 */
static inline uint32_t to_ms_since_boot(absolute_time_t t) {
    uint64_t us = to_us_since_boot(t);
    return us_to_ms(us);
}

/*! \brief Return a timestamp value obtained by adding a number of microseconds to another timestamp
 * \ingroup timestamp
 *
 * \param t the base timestamp
 * \param us the number of microseconds to add
 * \return the timestamp representing the resulting time
 */
static inline absolute_time_t delayed_by_us(const absolute_time_t t, uint64_t us) {
    absolute_time_t t2;
    uint64_t base = to_us_since_boot(t);
    uint64_t delayed = base + us;
    if ((int64_t)delayed < 0) {
        // absolute_time_t (to allow for signed time deltas) is never greater than INT64_MAX which == at_the_end_of_time
        delayed = INT64_MAX;
    }
    update_us_since_boot(&t2, delayed);
    return t2;
}

/*! \brief Return a timestamp value obtained by adding a number of milliseconds to another timestamp
 * \ingroup timestamp
 *
 * \param t the base timestamp
 * \param ms the number of milliseconds to add
 * \return the timestamp representing the resulting time
 */
static inline absolute_time_t delayed_by_ms(const absolute_time_t t, uint32_t ms) {
    absolute_time_t t2;
    uint64_t base = to_us_since_boot(t);
    uint64_t delayed = base + ms * 1000ull;
    if ((int64_t)delayed < 0) {
        // absolute_time_t (to allow for signed time deltas) is never greater than INT64_MAX which == at_the_end_of_time
        delayed = INT64_MAX;
    }
    update_us_since_boot(&t2, delayed);
    return t2;
}

/*! \brief Convenience method to get the timestamp a number of microseconds from the current time
 * \ingroup timestamp
 *
 * \param us the number of microseconds to add to the current timestamp
 * \return the future timestamp
 */
static inline absolute_time_t make_timeout_time_us(uint64_t us) {
    return delayed_by_us(get_absolute_time(), us);
}

/*! \brief Convenience method to get the timestamp a number of milliseconds from the current time
 * \ingroup timestamp
 *
 * \param ms the number of milliseconds to add to the current timestamp
 * \return the future timestamp
 */
static inline absolute_time_t make_timeout_time_ms(uint32_t ms) {
    return delayed_by_ms(get_absolute_time(), ms);
}

/*! \brief Return the difference in microseconds between two timestamps
 * \ingroup timestamp
 *
 * \note be careful when diffing against large timestamps (e.g. \ref at_the_end_of_time)
 * as the signed integer may overflow.
 *
 * \param from the first timestamp
 * \param to the second timestamp
 * \return the number of microseconds between the two timestamps (positive if `to` is after `from` except
 * in case of overflow)
 */
static inline int64_t absolute_time_diff_us(absolute_time_t from, absolute_time_t to) {
    return (int64_t)(to_us_since_boot(to) - to_us_since_boot(from));
}

/*! \brief Return the earlier of two timestamps
 * \ingroup timestamp
 *
 * \param a the first timestamp
 * \param b the second timestamp
 * \return the earlier of the two timestamps
 */
static inline absolute_time_t absolute_time_min(absolute_time_t a, absolute_time_t b) {
    return to_us_since_boot(a) < to_us_since_boot(b) ? a : b;
}

/*! \brief The timestamp representing the end of time; this is actually not the maximum possible
 * timestamp, but is set to 0x7fffffff_ffffffff microseconds to avoid sign overflows with time
 * arithmetic. This is almost 300,000 years, so should be sufficient.
 * \ingroup timestamp
 */
extern const absolute_time_t at_the_end_of_time;

/*! \brief Determine if the given timestamp is "at_the_end_of_time"
 * \ingroup timestamp
 *  \param t the timestamp
 *  \return true if the timestamp is at_the_end_of_time
 *  \sa at_the_end_of_time
 */
static inline bool is_at_the_end_of_time(absolute_time_t t) {
    return to_us_since_boot(t) == to_us_since_boot(at_the_end_of_time);
}

/*! \brief The timestamp representing a null timestamp
 * \ingroup timestamp
 */
extern const absolute_time_t nil_time;

/*! \brief Determine if the given timestamp is nil
 * \ingroup timestamp
 *  \param t the timestamp
 *  \return true if the timestamp is nil
 *  \sa nil_time
 */
static inline bool is_nil_time(absolute_time_t t) {
    return !to_us_since_boot(t);
}

/*!
 * \defgroup sleep sleep
 * \ingroup pico_time
 * \brief Sleep functions for delaying execution in a lower power state.
 *
 * These functions allow the calling core to sleep. This is a lower powered sleep; waking and re-checking time on every processor
 * event (WFE)
 *
 * \note  These functions should not be called from an IRQ handler.
 *
 * \note  Lower powered sleep requires use of the \link alarm_pool_get_default default alarm pool\endlink which may
 * be disabled by the PICO_TIME_DEFAULT_ALARM_POOL_DISABLED #define or currently full in which case these functions
 * become busy waits instead.
 *
 * \note  Whilst \a sleep_ functions are preferable to \a busy_wait functions from a power perspective, the \a busy_wait equivalent function
 * may return slightly sooner after the target is reached.
 *
 * \sa busy_wait_until() \sa busy_wait_us() \sa busy_wait_us_32()
 */

/*! \brief Wait until after the given timestamp to return
 * \ingroup sleep
 *
 * \note  This method attempts to perform a lower power (WFE) sleep
 *
 * \param target the time after which to return
 * \sa sleep_us()
 * \sa busy_wait_until()
 * */
void sleep_until(absolute_time_t target);

/*! \brief Wait for the given number of microseconds before returning
 * \ingroup sleep
 *
 * \note This method attempts to perform a lower power (WFE) sleep
 *
 * \param us the number of microseconds to sleep
 * \sa busy_wait_us()
 */
void sleep_us(uint64_t us);

/*! \brief Wait for the given number of milliseconds before returning
 * \ingroup sleep
 *
 * \note This method attempts to perform a lower power sleep (using WFE) as much as possible.
 *
 * \param ms the number of milliseconds to sleep
 */
void sleep_ms(uint32_t ms);

/*! \brief Helper method for blocking on a timeout
 * \ingroup sleep
 *
 * This method will return in response to an event (as per __wfe) or
 * when the target time is reached, or at any point before.
 *
 * This method can be used to implement a lower power polling loop waiting on
 * some condition signalled by an event (__sev()).
 *
 * This is called \a best_effort because under certain circumstances (notably the default timer pool
 * being disabled or full) the best effort is simply to return immediately without a __wfe, thus turning the calling
 * code into a busy wait.
 *
 * Example usage:
 * ```c
 * bool my_function_with_timeout_us(uint64_t timeout_us) {
 *     absolute_time_t timeout_time = make_timeout_time_us(timeout_us);
 *     do {
 *         // each time round the loop, we check to see if the condition
 *         // we are waiting on has happened
 *         if (my_check_done()) {
 *             // do something
 *             return true;
 *         }
 *         // will try to sleep until timeout or the next processor event 
 *     } while (!best_effort_wfe_or_timeout(timeout_time));
 *     return false; // timed out
 * }
 * ```
 *
 * @param timeout_timestamp the timeout time
 * @return true if the target time is reached, false otherwise
 */
bool best_effort_wfe_or_timeout(absolute_time_t timeout_timestamp);

/*!
 * \defgroup alarm alarm
 * \ingroup pico_time
 * \brief Alarm functions for scheduling future execution
 *
 *  Alarms are added to alarm pools, which may hold a certain fixed number of active alarms. Each alarm pool
 *  utilizes one of four underlying hardware alarms, thus you may have up to four alarm pools. An alarm pool
 *  calls (except when the callback would happen before or during being set) the callback on the core from which
 *  the alarm pool was created. Callbacks are called from the hardware alarm IRQ handler, so care must
 *  be taken in their implementation.
 *
 *  A default pool is created  the core specified by PICO_TIME_DEFAULT_ALARM_POOL_HARDWARE_ALARM_NUM
 *  on core 0, and may be used by the method variants that take no alarm pool parameter.
 *
 * \sa struct alarm_pool
 * \sa hardware_timer
 */

// PICO_CONFIG: PICO_TIME_DEFAULT_ALARM_POOL_DISABLED, Disable the default alarm pool, type=bool, default=0, advanced=true, group=pico_time
#ifndef PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
/*!
 * \brief If 1 then the default alarm pool is disabled (so no hardware alarm is claimed for the pool)
 *
 * \note Setting to 1 may cause some code not to compile as default timer pool related methods are removed
 *
 * \note When the default alarm pool is disabled, \a sleep_ methods and timeouts are no longer lower powered
 * (they become \a busy_wait_)
 *
 * \ingroup alarm
 * \sa #PICO_TIME_DEFAULT_ALARM_POOL_HARDWARE_ALARM_NUM
 * \sa alarm_pool_get_default()
 */
#define PICO_TIME_DEFAULT_ALARM_POOL_DISABLED 0
#endif

// PICO_CONFIG: PICO_TIME_DEFAULT_ALARM_POOL_HARDWARE_ALARM_NUM, Select which HW alarm is used for the default alarm pool, min=0, max=3, default=3, advanced=true, group=pico_time
#ifndef PICO_TIME_DEFAULT_ALARM_POOL_HARDWARE_ALARM_NUM
/*!
 * \brief Selects which hardware alarm is used for the default alarm pool
 * \ingroup alarm
 * \sa alarm_pool_get_default()
 */
#define PICO_TIME_DEFAULT_ALARM_POOL_HARDWARE_ALARM_NUM 3
#endif

// PICO_CONFIG: PICO_TIME_DEFAULT_ALARM_POOL_MAX_TIMERS, Selects the maximum number of concurrent timers in the default alarm pool, min=0, max=255, default=16, advanced=true, group=pico_time
#ifndef PICO_TIME_DEFAULT_ALARM_POOL_MAX_TIMERS
/*!
 * \brief Selects the maximum number of concurrent timers in the default alarm pool
 * \ingroup alarm
 *
 * \note For implementation reasons this is limited to PICO_PHEAP_MAX_ENTRIES which defaults to 255
 * \sa #PICO_TIME_DEFAULT_ALARM_POOL_HARDWARE_ALARM_NUM
 * \sa alarm_pool_get_default()
 */
#define PICO_TIME_DEFAULT_ALARM_POOL_MAX_TIMERS 16
#endif

/**
 * \brief The identifier for an alarm
 *
 * \note this identifier is signed because -1 is used as an error condition when creating alarms
 *
 * \note alarm ids may be reused, however for convenience the implementation makes an attempt to defer
 * reusing as long as possible. You should certainly expect it to be hundreds of ids before one is
 * reused, although in most cases it is more. Nonetheless care must still be taken when cancelling
 * alarms or other functionality based on alarms when the alarm may have expired, as eventually
 * the alarm id may be reused for another alarm.
 *
 * \ingroup alarm
 */
typedef int32_t alarm_id_t; // note this is signed because we use -1 as a meaningful error value

/**
 * \brief User alarm callback
 * \ingroup alarm
 * \param id the alarm_id as returned when the alarm was added
 * \param user_data the user data passed when the alarm was added
 * \return <0 to reschedule the same alarm this many us from the time the alarm was previously scheduled to fire
 * \return >0 to reschedule the same alarm this many us from the time this method returns
 * \return 0 to not reschedule the alarm
 */
typedef int64_t (*alarm_callback_t)(alarm_id_t id, void *user_data);

typedef struct alarm_pool alarm_pool_t;

/**
 * \brief Create the default alarm pool (if not already created or disabled)
 * \ingroup alarm
 */
void alarm_pool_init_default(void);

#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
/*!
 * \brief The default alarm pool used when alarms are added without specifying an alarm pool,
 *        and also used by the SDK to support lower power sleeps and timeouts.
 *
 * \ingroup alarm
 * \sa #PICO_TIME_DEFAULT_ALARM_POOL_HARDWARE_ALARM_NUM
 */
alarm_pool_t *alarm_pool_get_default(void);
#endif

/**
 * \brief Create an alarm pool
 *
 * The alarm pool will call callbacks from an alarm IRQ Handler on the core of this function is called from.
 *
 * In many situations there is never any need for anything other than the default alarm pool, however you
 * might want to create another if you want alarm callbacks on core 1 or require alarm pools of
 * different priority (IRQ priority based preemption of callbacks)
 *
 * \note This method will hard assert if the hardware alarm is already claimed.
 *
 * \ingroup alarm
 * \param hardware_alarm_num the hardware alarm to use to back this pool
 * \param max_timers the maximum number of timers
 *        \note For implementation reasons this is limited to PICO_PHEAP_MAX_ENTRIES which defaults to 255
 * \sa alarm_pool_get_default()
 * \sa hardware_claiming
 */
alarm_pool_t *alarm_pool_create(uint hardware_alarm_num, uint max_timers);

/**
 * \brief Create an alarm pool, claiming an used hardware alarm to back it.
 *
 * The alarm pool will call callbacks from an alarm IRQ Handler on the core of this function is called from.
 *
 * In many situations there is never any need for anything other than the default alarm pool, however you
 * might want to create another if you want alarm callbacks on core 1 or require alarm pools of
 * different priority (IRQ priority based preemption of callbacks)
 *
 * \note This method will hard assert if the there is no free hardware to claim.
 *
 * \ingroup alarm
 * \param max_timers the maximum number of timers
 *        \note For implementation reasons this is limited to PICO_PHEAP_MAX_ENTRIES which defaults to 255
 * \sa alarm_pool_get_default()
 * \sa hardware_claiming
 */
alarm_pool_t *alarm_pool_create_with_unused_hardware_alarm(uint max_timers);

/**
 * \brief Return the hardware alarm used by an alarm pool
 * \ingroup alarm
 * \param pool the pool
 * \return the hardware alarm used by the pool
 */
uint alarm_pool_hardware_alarm_num(alarm_pool_t *pool);

/**
 * \brief Return the core number the alarm pool was initialized on (and hence callbacks are called on)
 * \ingroup alarm
 * \param pool the pool
 * \return the core used by the pool
 */
uint alarm_pool_core_num(alarm_pool_t *pool);

/**
 * \brief Destroy the alarm pool, cancelling all alarms and freeing up the underlying hardware alarm
 * \ingroup alarm
 * \param pool the pool
 * \return the hardware alarm used by the pool
 */
void alarm_pool_destroy(alarm_pool_t *pool);

/*!
 * \brief Add an alarm callback to be called at a specific time
 * \ingroup alarm
 *
 * Generally the callback is called as soon as possible after the time specified from an IRQ handler
 * on the core the alarm pool was created on. If the callback is in the past or happens before
 * the alarm setup could be completed, then this method will optionally call the callback itself
 * and then return a return code to indicate that the target time has passed.
 *
 * \note It is safe to call this method from an IRQ handler (including alarm callbacks), and from either core.
 *
 * @param pool the alarm pool to use for scheduling the callback (this determines which hardware alarm is used, and which core calls the callback)
 * @param time the timestamp when (after which) the callback should fire
 * @param callback the callback function
 * @param user_data user data to pass to the callback function
 * @param fire_if_past if true, and the alarm time falls before or during this call before the alarm can be set,
 *                     then the callback should be called during (by) this function instead 
 * @return >0 the alarm id for an active (at the time of return) alarm
 * @return 0 if the alarm time passed before or during the call AND there is no active alarm to return the id of.
 *           The latter can either happen because fire_if_past was false (i.e. no timer was ever created),
 *           or if the callback <i>was</i> called during this method but the callback cancelled itself by returning 0
 * @return -1 if there were no alarm slots available
 */
alarm_id_t alarm_pool_add_alarm_at(alarm_pool_t *pool, absolute_time_t time, alarm_callback_t callback, void *user_data, bool fire_if_past);

/*!
 * \brief Add an alarm callback to be called at or after a specific time
 * \ingroup alarm
 *
 * The callback is called as soon as possible after the time specified from an IRQ handler
 * on the core the alarm pool was created on. Unlike \ref alarm_pool_add_alarm_at, this method
 * guarantees to call the callback from that core even if the time is during this method call or in the past.
 *
 * \note It is safe to call this method from an IRQ handler (including alarm callbacks), and from either core.
 *
 * @param pool the alarm pool to use for scheduling the callback (this determines which hardware alarm is used, and which core calls the callback)
 * @param time the timestamp when (after which) the callback should fire
 * @param callback the callback function
 * @param user_data user data to pass to the callback function
 * @return >0 the alarm id for an active (at the time of return) alarm
 * @return -1 if there were no alarm slots available
 */
alarm_id_t alarm_pool_add_alarm_at_force_in_context(alarm_pool_t *pool, absolute_time_t time, alarm_callback_t callback,
                                                    void *user_data);
/*!
 * \brief Add an alarm callback to be called after a delay specified in microseconds
 * \ingroup alarm
 *
 * Generally the callback is called as soon as possible after the time specified from an IRQ handler
 * on the core the alarm pool was created on. If the callback is in the past or happens before
 * the alarm setup could be completed, then this method will optionally call the callback itself
 * and then return a return code to indicate that the target time has passed.
 *
 * \note It is safe to call this method from an IRQ handler (including alarm callbacks), and from either core.
 *
 * @param pool the alarm pool to use for scheduling the callback (this determines which hardware alarm is used, and which core calls the callback)
 * @param us the delay (from now) in microseconds when (after which) the callback should fire
 * @param callback the callback function
 * @param user_data user data to pass to the callback function
 * @param fire_if_past if true, and the alarm time falls during this call before the alarm can be set,
 *                     then the callback should be called during (by) this function instead 
 * @return >0 the alarm id
 * @return 0 if the alarm time passed before or during the call AND there is no active alarm to return the id of.
 *           The latter can either happen because fire_if_past was false (i.e. no timer was ever created),
 *           or if the callback <i>was</i> called during this method but the callback cancelled itself by returning 0
 * @return -1 if there were no alarm slots available
 */
static inline alarm_id_t alarm_pool_add_alarm_in_us(alarm_pool_t *pool, uint64_t us, alarm_callback_t callback, void *user_data, bool fire_if_past) {
    return alarm_pool_add_alarm_at(pool, delayed_by_us(get_absolute_time(), us), callback, user_data, fire_if_past);
}

/*!
 * \brief Add an alarm callback to be called after a delay specified in milliseconds
 * \ingroup alarm
 *
 * Generally the callback is called as soon as possible after the time specified from an IRQ handler
 * on the core the alarm pool was created on. If the callback is in the past or happens before
 * the alarm setup could be completed, then this method will optionally call the callback itself
 * and then return a return code to indicate that the target time has passed.
 *
 * \note It is safe to call this method from an IRQ handler (including alarm callbacks), and from either core.
 *
 * @param pool the alarm pool to use for scheduling the callback (this determines which hardware alarm is used, and which core calls the callback)
 * @param ms the delay (from now) in milliseconds when (after which) the callback should fire
 * @param callback the callback function
 * @param user_data user data to pass to the callback function
 * @param fire_if_past if true, and the alarm time falls before or during this call before the alarm can be set,
 *                     then the callback should be called during (by) this function instead 
 * @return >0 the alarm id
 * @return 0 if the alarm time passed before or during the call AND there is no active alarm to return the id of.
 *           The latter can either happen because fire_if_past was false (i.e. no timer was ever created),
 *           or if the callback <i>was</i> called during this method but the callback cancelled itself by returning 0
 * @return -1 if there were no alarm slots available
 */
static inline alarm_id_t alarm_pool_add_alarm_in_ms(alarm_pool_t *pool, uint32_t ms, alarm_callback_t callback, void *user_data, bool fire_if_past) {
    return alarm_pool_add_alarm_at(pool, delayed_by_ms(get_absolute_time(), ms), callback, user_data, fire_if_past);
}

/*!
 * \brief Cancel an alarm
 * \ingroup alarm
 * \param pool the alarm_pool containing the alarm
 * \param alarm_id the alarm
 * \return true if the alarm was cancelled, false if it didn't exist
 * \sa alarm_id_t for a note on reuse of IDs
 */
bool alarm_pool_cancel_alarm(alarm_pool_t *pool, alarm_id_t alarm_id);

#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
/*!
 * \brief Add an alarm callback to be called at a specific time
 * \ingroup alarm
 *
 * Generally the callback is called as soon as possible after the time specified from an IRQ handler
 * on the core of the default alarm pool (generally core 0). If the callback is in the past or happens before
 * the alarm setup could be completed, then this method will optionally call the callback itself
 * and then return a return code to indicate that the target time has passed.
 *
 * \note It is safe to call this method from an IRQ handler (including alarm callbacks), and from either core.
 *
 * @param time the timestamp when (after which) the callback should fire
 * @param callback the callback function
 * @param user_data user data to pass to the callback function
 * @param fire_if_past if true, and the alarm time falls before or during this call before the alarm can be set,
 *                     then the callback should be called during (by) this function instead 
 * @return >0 the alarm id
 * @return 0 if the alarm time passed before or during the call AND there is no active alarm to return the id of.
 *           The latter can either happen because fire_if_past was false (i.e. no timer was ever created),
 *           or if the callback <i>was</i> called during this method but the callback cancelled itself by returning 0
 * @return -1 if there were no alarm slots available
 */
static inline alarm_id_t add_alarm_at(absolute_time_t time, alarm_callback_t callback, void *user_data, bool fire_if_past) {
    return alarm_pool_add_alarm_at(alarm_pool_get_default(), time, callback, user_data, fire_if_past);
}

/*!
 * \brief Add an alarm callback to be called after a delay specified in microseconds
 * \ingroup alarm
 *
 * Generally the callback is called as soon as possible after the time specified from an IRQ handler
 * on the core of the default alarm pool (generally core 0). If the callback is in the past or happens before
 * the alarm setup could be completed, then this method will optionally call the callback itself
 * and then return a return code to indicate that the target time has passed.
 *
 * \note It is safe to call this method from an IRQ handler (including alarm callbacks), and from either core.
 *
 * @param us the delay (from now) in microseconds when (after which) the callback should fire
 * @param callback the callback function
 * @param user_data user data to pass to the callback function
 * @param fire_if_past if true, and the alarm time falls during this call before the alarm can be set,
 *                     then the callback should be called during (by) this function instead 
 * @return >0 the alarm id
 * @return 0 if the alarm time passed before or during the call AND there is no active alarm to return the id of.
 *           The latter can either happen because fire_if_past was false (i.e. no timer was ever created),
 *           or if the callback <i>was</i> called during this method but the callback cancelled itself by returning 0
 * @return -1 if there were no alarm slots available
 */
static inline alarm_id_t add_alarm_in_us(uint64_t us, alarm_callback_t callback, void *user_data, bool fire_if_past) {
    return alarm_pool_add_alarm_in_us(alarm_pool_get_default(), us, callback, user_data, fire_if_past);
}

/*!
 * \brief Add an alarm callback to be called after a delay specified in milliseconds
 * \ingroup alarm
 *
 * Generally the callback is called as soon as possible after the time specified from an IRQ handler
 * on the core of the default alarm pool (generally core 0). If the callback is in the past or happens before
 * the alarm setup could be completed, then this method will optionally call the callback itself
 * and then return a return code to indicate that the target time has passed.
 *
 * \note It is safe to call this method from an IRQ handler (including alarm callbacks), and from either core.
 *
 * @param ms the delay (from now) in milliseconds when (after which) the callback should fire
 * @param callback the callback function
 * @param user_data user data to pass to the callback function
 * @param fire_if_past if true, and the alarm time falls during this call before the alarm can be set,
 *                     then the callback should be called during (by) this function instead 
 * @return >0 the alarm id
 * @return 0 if the alarm time passed before or during the call AND there is no active alarm to return the id of.
 *           The latter can either happen because fire_if_past was false (i.e. no timer was ever created),
 *           or if the callback <i>was</i> called during this method but the callback cancelled itself by returning 0
 * @return -1 if there were no alarm slots available
 */
static inline alarm_id_t add_alarm_in_ms(uint32_t ms, alarm_callback_t callback, void *user_data, bool fire_if_past) {
    return alarm_pool_add_alarm_in_ms(alarm_pool_get_default(), ms, callback, user_data, fire_if_past);
}
/*!
 * \brief Cancel an alarm from the default alarm pool
 * \ingroup alarm
 * \param alarm_id the alarm
 * \return true if the alarm was cancelled, false if it didn't exist
 * \sa alarm_id_t for a note on reuse of IDs
 */
static inline bool cancel_alarm(alarm_id_t alarm_id) {
    return alarm_pool_cancel_alarm(alarm_pool_get_default(), alarm_id);
}

#endif

/*!
 * \defgroup repeating_timer repeating_timer
 * \ingroup pico_time
 * \brief Repeating Timer functions for simple scheduling of repeated execution
 *
 * \note The regular \a alarm_ functionality can be used to make repeating alarms (by return non zero from the callback),
 * however these methods abstract that further (at the cost of a user structure to store the repeat delay in (which
 * the alarm framework does not have space for).
 */

typedef struct repeating_timer repeating_timer_t;

/**
 * \brief Callback for a repeating timer
 * \ingroup repeating_timer
 * \param rt repeating time structure containing information about the repeating time. user_data is of primary important to the user
 * \return true to continue repeating, false to stop.
 */
typedef bool (*repeating_timer_callback_t)(repeating_timer_t *rt);

/**
 * \brief Information about a repeating timer
 * \ingroup repeating_timer
 * \return
 */
struct repeating_timer {
    int64_t delay_us;
    alarm_pool_t *pool;
    alarm_id_t alarm_id;
    repeating_timer_callback_t callback;
    void *user_data;
};

/*!
 * \brief Add a repeating timer that is called repeatedly at the specified interval in microseconds
 * \ingroup repeating_timer
 *
 * Generally the callback is called as soon as possible after the time specified from an IRQ handler
 * on the core the alarm pool was created on. If the callback is in the past or happens before
 * the alarm setup could be completed, then this method will optionally call the callback itself
 * and then return a return code to indicate that the target time has passed.
 *
 * \note It is safe to call this method from an IRQ handler (including alarm callbacks), and from either core.
 *
 * @param pool the alarm pool to use for scheduling the repeating timer (this determines which hardware alarm is used, and which core calls the callback)
 * @param delay_us the repeat delay in microseconds; if >0 then this is the delay between one callback ending and the next starting; if <0 then this is the negative of the time between the starts of the callbacks. The value of 0 is treated as 1
 * @param callback the repeating timer callback function
 * @param user_data user data to pass to store in the repeating_timer structure for use by the callback.
 * @param out the pointer to the user owned structure to store the repeating timer info in. BEWARE this storage location must outlive the repeating timer, so be careful of using stack space
 * @return false if there were no alarm slots available to create the timer, true otherwise.
 */
bool alarm_pool_add_repeating_timer_us(alarm_pool_t *pool, int64_t delay_us, repeating_timer_callback_t callback, void *user_data, repeating_timer_t *out);

/*!
 * \brief Add a repeating timer that is called repeatedly at the specified interval in milliseconds
 * \ingroup repeating_timer
 *
 * Generally the callback is called as soon as possible after the time specified from an IRQ handler
 * on the core the alarm pool was created on. If the callback is in the past or happens before
 * the alarm setup could be completed, then this method will optionally call the callback itself
 * and then return a return code to indicate that the target time has passed.
 *
 * \note It is safe to call this method from an IRQ handler (including alarm callbacks), and from either core.
 *
 * @param pool the alarm pool to use for scheduling the repeating timer (this determines which hardware alarm is used, and which core calls the callback)
 * @param delay_ms the repeat delay in milliseconds; if >0 then this is the delay between one callback ending and the next starting; if <0 then this is the negative of the time between the starts of the callbacks. The value of 0 is treated as 1 microsecond
 * @param callback the repeating timer callback function
 * @param user_data user data to pass to store in the repeating_timer structure for use by the callback.
 * @param out the pointer to the user owned structure to store the repeating timer info in. BEWARE this storage location must outlive the repeating timer, so be careful of using stack space
 * @return false if there were no alarm slots available to create the timer, true otherwise.
 */
static inline bool alarm_pool_add_repeating_timer_ms(alarm_pool_t *pool, int32_t delay_ms, repeating_timer_callback_t callback, void *user_data, repeating_timer_t *out) {
    return alarm_pool_add_repeating_timer_us(pool, delay_ms * (int64_t)1000, callback, user_data, out);
}

#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
/*!
 * \brief Add a repeating timer that is called repeatedly at the specified interval in microseconds
 * \ingroup repeating_timer
 *
 * Generally the callback is called as soon as possible after the time specified from an IRQ handler
 * on the core of the default alarm pool (generally core 0). If the callback is in the past or happens before
 * the alarm setup could be completed, then this method will optionally call the callback itself
 * and then return a return code to indicate that the target time has passed.
 *
 * \note It is safe to call this method from an IRQ handler (including alarm callbacks), and from either core.
 *
 * @param delay_us the repeat delay in microseconds; if >0 then this is the delay between one callback ending and the next starting; if <0 then this is the negative of the time between the starts of the callbacks. The value of 0 is treated as 1
 * @param callback the repeating timer callback function
 * @param user_data user data to pass to store in the repeating_timer structure for use by the callback.
 * @param out the pointer to the user owned structure to store the repeating timer info in. BEWARE this storage location must outlive the repeating timer, so be careful of using stack space
 * @return false if there were no alarm slots available to create the timer, true otherwise.
 */
static inline bool add_repeating_timer_us(int64_t delay_us, repeating_timer_callback_t callback, void *user_data, repeating_timer_t *out) {
    return alarm_pool_add_repeating_timer_us(alarm_pool_get_default(), delay_us, callback, user_data, out);
}

/*!
 * \brief Add a repeating timer that is called repeatedly at the specified interval in milliseconds
 * \ingroup repeating_timer
 *
 * Generally the callback is called as soon as possible after the time specified from an IRQ handler
 * on the core of the default alarm pool (generally core 0). If the callback is in the past or happens before
 * the alarm setup could be completed, then this method will optionally call the callback itself
 * and then return a return code to indicate that the target time has passed.
 *
 * \note It is safe to call this method from an IRQ handler (including alarm callbacks), and from either core.
 *
 * @param delay_ms the repeat delay in milliseconds; if >0 then this is the delay between one callback ending and the next starting; if <0 then this is the negative of the time between the starts of the callbacks. The value of 0 is treated as 1 microsecond
 * @param callback the repeating timer callback function
 * @param user_data user data to pass to store in the repeating_timer structure for use by the callback.
 * @param out the pointer to the user owned structure to store the repeating timer info in. BEWARE this storage location must outlive the repeating timer, so be careful of using stack space
 * @return false if there were no alarm slots available to create the timer, true otherwise.
 */
static inline bool add_repeating_timer_ms(int32_t delay_ms, repeating_timer_callback_t callback, void *user_data, repeating_timer_t *out) {
    return alarm_pool_add_repeating_timer_us(alarm_pool_get_default(), delay_ms * (int64_t)1000, callback, user_data, out);
}
#endif

/**
 * \brief Cancel a repeating timer
 * \ingroup repeating_timer
 * \param timer the repeating timer to cancel
 * \return true if the repeating timer was cancelled, false if it didn't exist
 * \sa alarm_id_t for a note on reuse of IDs
 */
bool cancel_repeating_timer(repeating_timer_t *timer);

#ifdef __cplusplus
}
#endif

#endif
