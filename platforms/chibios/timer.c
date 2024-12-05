#include <ch.h>

#include "timer.h"

static uint32_t ticks_offset = 0;
static uint32_t last_ticks   = 0;
static uint32_t ms_offset    = 0;
static uint32_t saved_ms     = 0;
#if CH_CFG_ST_RESOLUTION < 32
static uint32_t last_systime = 0;
static uint32_t overflow     = 0;
#endif

// Get the current system time in ticks as a 32-bit number.
// This function must be called from within a system lock zone (so that it can safely use and update the static data).
static inline uint32_t get_system_time_ticks(void) {
    uint32_t systime = (uint32_t)chVTGetSystemTimeX();

#if CH_CFG_ST_RESOLUTION < 32
    // If the real system timer resolution is less than 32 bits, provide the missing bits by checking for the counter
    // overflow.  For this to work, this function must be called at least once for every overflow of the system timer.
    // In the 16-bit case, the corresponding times are:
    //    - CH_CFG_ST_FREQUENCY = 100000, overflow will occur every ~0.65 seconds
    //    - CH_CFG_ST_FREQUENCY = 10000, overflow will occur every ~6.5 seconds
    //    - CH_CFG_ST_FREQUENCY = 1000, overflow will occur every ~65 seconds
    if (systime < last_systime) {
        overflow += ((uint32_t)1) << CH_CFG_ST_RESOLUTION;
    }
    last_systime = systime;
    systime += overflow;
#endif

    return systime;
}

#if CH_CFG_ST_RESOLUTION < 32
static virtual_timer_t update_timer;

// Update the system tick counter every half of the timer overflow period; this should keep the tick counter correct
// even if something blocks timer interrupts for 1/2 of the timer overflow period.
#    define UPDATE_INTERVAL (((sysinterval_t)1) << (CH_CFG_ST_RESOLUTION - 1))

// VT callback function to keep the overflow bits of the system tick counter updated.
static void update_fn(struct ch_virtual_timer *timer, void *arg) {
    (void)arg;
    chSysLockFromISR();
    get_system_time_ticks();
    chVTSetI(&update_timer, UPDATE_INTERVAL, update_fn, NULL);
    chSysUnlockFromISR();
}
#endif

// The highest multiple of CH_CFG_ST_FREQUENCY that fits into uint32_t.  This number of ticks will necessarily
// correspond to some integer number of seconds.
#define OVERFLOW_ADJUST_TICKS ((uint32_t)((UINT32_MAX / CH_CFG_ST_FREQUENCY) * CH_CFG_ST_FREQUENCY))

// The time in milliseconds which corresponds to OVERFLOW_ADJUST_TICKS ticks (this is a precise conversion, because
// OVERFLOW_ADJUST_TICKS corresponds to an integer number of seconds).
#define OVERFLOW_ADJUST_MS (TIME_I2MS(OVERFLOW_ADJUST_TICKS))

void timer_init(void) {
    timer_clear();
#if CH_CFG_ST_RESOLUTION < 32
    chVTObjectInit(&update_timer);
    chVTSet(&update_timer, UPDATE_INTERVAL, update_fn, NULL);
#endif
}

void timer_clear(void) {
    chSysLock();
    ticks_offset = get_system_time_ticks();
    last_ticks   = 0;
    ms_offset    = 0;
    chSysUnlock();
}

__attribute__((weak)) void platform_timer_save_value(uint32_t value) {
    saved_ms = value;
}

__attribute__((weak)) uint32_t platform_timer_restore_value(void) {
    return saved_ms;
}

void timer_restore(void) {
    chSysLock();
    ticks_offset = get_system_time_ticks();
    last_ticks   = 0;
    ms_offset    = platform_timer_restore_value();
    chSysUnlock();
}

void timer_save(void) {
    platform_timer_save_value(timer_read32());
}

uint16_t timer_read(void) {
    return (uint16_t)timer_read32();
}

uint32_t timer_read32(void) {
    chSysLock();
    uint32_t ticks = get_system_time_ticks() - ticks_offset;
    if (ticks < last_ticks) {
        // The 32-bit tick counter overflowed and wrapped around.  We cannot just extend the counter to 64 bits here,
        // because TIME_I2MS() may encounter overflows when handling a 64-bit argument; therefore the solution here is
        // to subtract a reasonably large number of ticks from the tick counter to bring its value below the 32-bit
        // limit again, and then add the equivalent number of milliseconds to the converted value.  (Adjusting just the
        // converted value to account for 2**32 ticks is not possible in general, because 2**32 ticks may not correspond
        // to an integer number of milliseconds).
        ticks -= OVERFLOW_ADJUST_TICKS;
        ticks_offset += OVERFLOW_ADJUST_TICKS;
        ms_offset += OVERFLOW_ADJUST_MS;
    }
    last_ticks              = ticks;
    uint32_t ms_offset_copy = ms_offset; // read while still holding the lock to ensure a consistent value
    chSysUnlock();

    return (uint32_t)TIME_I2MS(ticks) + ms_offset_copy;
}

uint16_t timer_elapsed(uint16_t last) {
    return TIMER_DIFF_16(timer_read(), last);
}

uint32_t timer_elapsed32(uint32_t last) {
    return TIMER_DIFF_32(timer_read32(), last);
}
