#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "led.h"
#include "sleep_led.h"

/* Software PWM
 *  ______           ______           __
 * |  ON  |___OFF___|  ON  |___OFF___|   ....
 * |<-------------->|<-------------->|<- ....
 *     PWM period       PWM period
 *
 * 256              interrupts/period[resolution]
 * 64               periods/second[frequency]
 * 256*64           interrupts/second
 * F_CPU/(256*64)   clocks/interrupt
 */
#define SLEEP_LED_TIMER_TOP F_CPU/(256*64)

void sleep_led_init(void)
{
    /* Timer1 setup */
    /* CTC mode */
    TCCR1B |= _BV(WGM12);
    /* Clock selelct: clk/1 */
    TCCR1B |= _BV(CS10);
    /* Set TOP value */
    uint8_t sreg = SREG;
    cli();
    OCR1AH = (SLEEP_LED_TIMER_TOP>>8)&0xff;
    OCR1AL = SLEEP_LED_TIMER_TOP&0xff;
    SREG = sreg;
}

void sleep_led_enable(void)
{
    /* Enable Compare Match Interrupt */
    TIMSK1 |= _BV(OCIE1A);
}

void sleep_led_disable(void)
{
    /* Disable Compare Match Interrupt */
    TIMSK1 &= ~_BV(OCIE1A);
}


/* Breathing Sleep LED brighness(PWM On period) table
 * (32[steps] * 8[duration]) / 64[PWM periods/s] = 4 second breath cycle
 */
static const uint8_t breathing_table[32] PROGMEM = {
    0, 0, 0, 2, 9, 21, 37, 56, 78, 127, 151, 175, 197, 216, 232, 244,
    254, 244, 216, 197, 175, 151, 127, 78, 56, 37, 21, 9, 2, 0, 0, 0
};

ISR(TIMER1_COMPA_vect)
{
    /* Software PWM
     * timer:1111 1111 1111 1111
     *       \----/\-/ \-------/+---  count(0-255)
     *         |    +---------------  duration of step(8)
     *         +--------------------  index of step table(0-31)
     */
    static union {
        uint16_t row;
        struct {
            uint8_t count:8;
            uint8_t duration:3;
            uint8_t index:5;
        } pwm;
    } timer = { .row = 0 };

    timer.row++;
    
    // LED on
    if (timer.pwm.count == 0) {
        led_set(1<<USB_LED_CAPS_LOCK);
    }
    // LED off
    if (timer.pwm.count == pgm_read_byte(&breathing_table[timer.pwm.index])) {
        led_set(0);
    }
}
