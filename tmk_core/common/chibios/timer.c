#include "ch.h"

#include "timer.h"

void timer_init(void) { timer_clear(); }

void timer_clear(void) {}

uint16_t timer_read(void) { return (uint16_t)timer_read32(); }

uint32_t timer_read32(void) {
    uint32_t systime = (uint32_t)chVTGetSystemTime();
    return TIME_I2MS(systime);
}

uint16_t timer_elapsed(uint16_t last) { return TIMER_DIFF_16(timer_read(), last); }

uint32_t timer_elapsed32(uint32_t last) { return TIMER_DIFF_32(timer_read32(), last); }
