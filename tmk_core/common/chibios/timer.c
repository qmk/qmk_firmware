#include "ch.h"

#include "timer.h"

static uint32_t reset_point = 0;
#if CH_CFG_ST_RESOLUTION < 32
static uint32_t last_systime = 0;
static uint32_t overflow     = 0;
#endif

void timer_init(void) { timer_clear(); }

void timer_clear(void) {
    reset_point = (uint32_t)chVTGetSystemTime();
#if CH_CFG_ST_RESOLUTION < 32
    last_systime = reset_point;
    overflow     = 0;
#endif
}

uint16_t timer_read(void) { return (uint16_t)timer_read32(); }

uint32_t timer_read32(void) {
    uint32_t systime = (uint32_t)chVTGetSystemTime();

#if CH_CFG_ST_RESOLUTION < 32
    // If/when we need to support 64-bit chips, this may need to be modified to match the native bit-ness of the MCU.
    // At this point, the only SysTick resolution allowed other than 32 is 16 bit.
    // In the 16-bit case, at:
    //    - CH_CFG_ST_FREQUENCY = 100000, overflow will occur every ~0.65 seconds
    //    - CH_CFG_ST_FREQUENCY = 10000, overflow will occur every ~6.5 seconds
    //    - CH_CFG_ST_FREQUENCY = 1000, overflow will occur every ~65 seconds
    // With this implementation, as long as we ensure a timer read happens at least once during the overflow period, timing should be accurate.
    if (systime < last_systime) {
        overflow += ((uint32_t)1) << CH_CFG_ST_RESOLUTION;
    }

    last_systime = systime;
    return (uint32_t)TIME_I2MS(systime - reset_point + overflow);
#else
    return (uint32_t)TIME_I2MS(systime - reset_point);
#endif
}

uint16_t timer_elapsed(uint16_t last) { return TIMER_DIFF_16(timer_read(), last); }

uint32_t timer_elapsed32(uint32_t last) { return TIMER_DIFF_32(timer_read32(), last); }
