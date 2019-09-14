#include "timer.h"

#define TICK_INTERVAL 10
/* Mill second tick count */
volatile uint32_t timer_count = 0;

void timer_tick(uint8_t interval) {
  timer_count += interval;
}
/* Timer interrupt handler */
void ticker(void* context)  {
}

/* Timer Initialize
 * Using single shot timer because task queue will overflow
 * if the timer runs in repeated mode during bonding
 */
void timer_init(void)
{
}

void timer_clear(void)
{
    timer_count = 0;
}

uint16_t timer_read(void)
{
    return (uint16_t)(timer_count & 0xFFFF);
}

uint32_t timer_read32(void)
{
    return timer_count;
}

uint16_t timer_elapsed(uint16_t last)
{
    return TIMER_DIFF_16(timer_read(), last);
}

uint32_t timer_elapsed32(uint32_t last)
{
    return TIMER_DIFF_32(timer_read32(), last);
}
