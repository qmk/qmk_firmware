#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "timer.h"

uint16_t timer_count = 0;

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
    cli();
    timer_count = 0;
    sei();
}

inline
uint16_t timer_read(void)
{
    uint8_t _sreg = SREG;
    uint16_t t;

    cli();
    t = timer_count;
    SREG = _sreg;

    return t;
}

inline
uint16_t timer_elapsed(uint16_t last)
{
    uint8_t _sreg = SREG;
    uint16_t t;

    cli();
    t = timer_count;
    SREG = _sreg;

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

