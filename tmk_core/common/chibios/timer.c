#include <ch.h>

#include "timer.h"

static uint32_t last_systime_ms = 0;
static uint32_t time_ms = 0;

void timer_init(void) { timer_clear(); }

void timer_clear(void) {

    last_systime_ms = (uint64_t)chVTGetSystemTime();
    time_ms = 0;
}

uint16_t timer_read(void) { return (uint16_t)timer_read32(); }

uint32_t timer_read32(void) {
    uint32_t systime_ms = TIME_I2MS((uint32_t)chVTGetSystemTime());
    time_ms += systime_ms - last_systime_ms;
    last_systime_ms = systime_ms;
    return time_ms;
}

uint16_t timer_elapsed(uint16_t last) { return TIMER_DIFF_16(timer_read(), last); }

uint32_t timer_elapsed32(uint32_t last) { return TIMER_DIFF_32(timer_read32(), last); }
