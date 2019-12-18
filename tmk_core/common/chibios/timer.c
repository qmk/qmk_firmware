#include "ch.h"

#include "timer.h"

static systime_t last_systime    = 0;
static systime_t overflow        = 0;
static uint32_t  current_time_ms = 0;

void timer_init(void) { timer_clear(); }

void timer_clear(void) {
    last_systime    = chVTGetSystemTime();
    overflow        = 0;
    current_time_ms = 0;
}

uint16_t timer_read(void) { return (uint16_t)timer_read32(); }

uint32_t timer_read32(void) {
    systime_t     systime = chVTGetSystemTime();
    sysinterval_t elapsed = chTimeDiffX(last_systime, systime);
    last_systime          = systime;
    current_time_ms += chTimeI2MS(elapsed);
    return current_time_ms;
}

uint16_t timer_elapsed(uint16_t last) { return TIMER_DIFF_16(timer_read(), last); }

uint32_t timer_elapsed32(uint32_t last) { return TIMER_DIFF_32(timer_read32(), last); }
