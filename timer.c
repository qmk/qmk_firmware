#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "timer.h"

volatile uint16_t timer_count = 0;

// Configure timer 0 to generate a timer overflow interrupt every
// 256*1024 clock cycles, or approx 61 Hz when using 16 MHz clock
// This demonstrates how to use interrupts to implement a simple
// inactivity timeout.
void timer_init(void)
{
    TCCR0A = 0x00;
    TCCR0B = 0x05;
    TIMSK0 = (1<<TOIE0);
}

inline
void timer_clear(void)
{
    uint8_t sreg = SREG;
    cli();
    timer_count = 0;
    SREG = sreg;
}

inline
uint16_t timer_read(void)
{
    uint16_t t;

    uint8_t sreg = SREG;
    cli();
    t = timer_count;
    SREG = sreg;

    return t;
}

inline
uint16_t timer_elapsed(uint16_t last)
{
    uint16_t t;

    uint8_t sreg = SREG;
    cli();
    t = timer_count;
    SREG = sreg;

    return TIMER_DIFF(t, last);
}

// This interrupt routine is run approx 61 times per second.
// A very simple inactivity timeout is implemented, where we
// will send a space character and print a message to the
// hid_listen debug message window.
ISR(TIMER0_OVF_vect)
{
    timer_count++;
}
