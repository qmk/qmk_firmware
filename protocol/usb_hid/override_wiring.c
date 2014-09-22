/*
 * To keep Timer0 for common/timer.c override arduino/wiring.c.
 */
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include "common/timer.h"
#include "Arduino.h"


unsigned long millis()
{
    return timer_read32();
}
unsigned long micros()
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
void init()
{
    timer_init();
}
