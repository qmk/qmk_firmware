/*
 * To keep Timer0 for common/timer.c override arduino/wiring.c.
 */
#define __DELAY_BACKWARD_COMPATIBLE__

// Need to disable GCC's "maybe-uninitialized" warning for this file, as it causes issues when running `KEEP_INTERMEDIATES=yes`.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#include <util/delay.h>
#pragma GCC diagnostic pop

#include "platforms/timer.h"


unsigned long millis(void)
{
    return timer_read32();
}
unsigned long micros(void)
{
    return timer_read32() * 1000UL;
}
void delay(unsigned long ms)
{
    _delay_ms(ms);
}
void delayMicroseconds(unsigned int us)
{
    _delay_us(us);
}
void init(void)
{
    timer_init();
}
