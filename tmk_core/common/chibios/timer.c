#include "ch.h"

#include "timer.h"

#if CH_CFG_ST_RESOLUTION < 32
static uint32_t last_systime = 0;
static uint32_t overflow     = 0;
#endif

void timer_init(void) { timer_clear(); }

void timer_clear(void) {
#if CH_CFG_ST_RESOLUTION < 32
    last_systime = (uint32_t)chVTGetSystemTime();
    overflow     = 0;
#endif
}

uint16_t timer_read(void) { return (uint16_t)timer_read32(); }

uint32_t timer_read32(void) {
    uint32_t systime = (uint32_t)chVTGetSystemTime();

#if CH_CFG_ST_RESOLUTION < 32

    if (systime < last_systime) {
        overflow += ((uint32_t)1) << CH_CFG_ST_RESOLUTION;
    }

    last_systime = systime;
    return (uint32_t)TIME_I2MS(systime + overflow);

#else

    return (uint32_t)TIME_I2MS(systime);

#endif
}

uint16_t timer_elapsed(uint16_t last) { return TIMER_DIFF_16(timer_read(), last); }

uint32_t timer_elapsed32(uint32_t last) { return TIMER_DIFF_32(timer_read32(), last); }
