#include <ch.h>

#include "timer.h"

static uint32_t ticks_offset = 0;
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

void timer_init(void) { timer_clear(); }

void timer_clear(void) {
    chSysLock();
    ticks_offset = get_system_time_ticks();
    chSysUnlock();
}

uint16_t timer_read(void) { return (uint16_t)timer_read32(); }

uint32_t timer_read32(void) {
    chSysLock();
    uint32_t ticks = get_system_time_ticks() - ticks_offset;
    chSysUnlock();

    return (uint32_t)TIME_I2MS(ticks);
}

uint16_t timer_elapsed(uint16_t last) { return TIMER_DIFF_16(timer_read(), last); }

uint32_t timer_elapsed32(uint32_t last) { return TIMER_DIFF_32(timer_read32(), last); }
