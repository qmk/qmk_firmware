#include "elapsedMillis.h"
#include "timer.h"

elapsedMillis elapsed;

void timer_init(void)
{
    elapsed = 0;
}

void timer_clear(void)
{
    elapsed = 0;
}

uint16_t timer_read(void)
{
    long count = (long) elapsed;
    return (uint16_t)(count & 0xFFFF);
}

uint32_t timer_read32(void)
{
    long count = (long) elapsed;
    return (uint32_t)(count & 0xFFFFFFFF);
}

uint16_t timer_elapsed(uint16_t last)
{
    return TIMER_DIFF_16(timer_read(), last);
}

uint32_t timer_elapsed32(uint32_t last)
{
    return TIMER_DIFF_32(timer_read32(), last);
}
