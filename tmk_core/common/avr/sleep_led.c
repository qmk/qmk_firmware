#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "led.h"
#include "sleep_led.h"

#define TCCRxB TCCR1B
#define TIMERx_COMPA_vect TIMER1_COMPA_vect
#if defined(__AVR_ATmega32A__)  // This MCU has only one TIMSK register
#    define TIMSKx TIMSK
#else
#    define TIMSKx TIMSK1
#endif
#define OCIExA OCIE1A
#define OCRxx OCR1A

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
#define SLEEP_LED_TIMER_TOP F_CPU / (256 * 64)

/** \brief Sleep LED initialization
 *
 * FIXME: needs doc
 */
void sleep_led_init(void) {
    /* Timer1 setup */
    /* CTC mode */
    TCCRxB |= _BV(WGM12);
    /* Clock selelct: clk/1 */
    TCCRxB |= _BV(CS10);
    /* Set TOP value */
    uint8_t sreg = SREG;
    cli();
    OCRxx = SLEEP_LED_TIMER_TOP;
    SREG   = sreg;
}

/** \brief Sleep LED enable
 *
 * FIXME: needs doc
 */
void sleep_led_enable(void) {
    /* Enable Compare Match Interrupt */
    TIMSKx |= _BV(OCIExA);
}

/** \brief Sleep LED disable
 *
 * FIXME: needs doc
 */
void sleep_led_disable(void) {
    /* Disable Compare Match Interrupt */
    TIMSKx &= ~_BV(OCIExA);
}

/** \brief Sleep LED toggle
 *
 * FIXME: needs doc
 */
void sleep_led_toggle(void) {
    /* Disable Compare Match Interrupt */
    TIMSKx ^= _BV(OCIExA);
}

/** \brief Breathing Sleep LED brighness(PWM On period) table
 *
 * (64[steps] * 4[duration]) / 64[PWM periods/s] = 4 second breath cycle
 *
 * http://www.wolframalpha.com/input/?i=%28sin%28+x%2F64*pi%29**8+*+255%2C+x%3D0+to+63
 * (0..63).each {|x| p ((sin(x/64.0*PI)**8)*255).to_i }
 */
static const uint8_t breathing_table[64] PROGMEM = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 6, 10, 15, 23, 32, 44, 58, 74, 93, 113, 135, 157, 179, 199, 218, 233, 245, 252, 255, 252, 245, 233, 218, 199, 179, 157, 135, 113, 93, 74, 58, 44, 32, 23, 15, 10, 6, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

ISR(TIMERx_COMPA_vect) {
    /* Software PWM
     * timer:1111 1111 1111 1111
     *       \_____/\/ \_______/____  count(0-255)
     *          \    \______________  duration of step(4)
     *           \__________________  index of step table(0-63)
     */
    static union {
        uint16_t row;
        struct {
            uint8_t count : 8;
            uint8_t duration : 2;
            uint8_t index : 6;
        } pwm;
    } timer = {.row = 0};

    timer.row++;

    // LED on
    if (timer.pwm.count == 0) {
        led_set(1 << USB_LED_CAPS_LOCK);
    }
    // LED off
    if (timer.pwm.count == pgm_read_byte(&breathing_table[timer.pwm.index])) {
        led_set(0);
    }
}
