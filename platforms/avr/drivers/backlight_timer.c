#include "backlight.h"
#include "backlight_driver_common.h"
#include "progmem.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Maximum duty cycle limit
#ifndef BACKLIGHT_LIMIT_VAL
#    define BACKLIGHT_LIMIT_VAL 255
#endif

#ifndef BACKLIGHT_PWM_TIMER
#    define BACKLIGHT_PWM_TIMER 1
#endif

#if BACKLIGHT_PWM_TIMER == 1
#    define ICRx ICR1
#    define TCCRxA TCCR1A
#    define TCCRxB TCCR1B
#    define TIMERx_COMPA_vect TIMER1_COMPA_vect
#    define TIMERx_OVF_vect TIMER1_OVF_vect
#    if defined(__AVR_ATmega32A__) // This MCU has only one TIMSK register
#        define TIMSKx TIMSK
#    else
#        define TIMSKx TIMSK1
#    endif
#    define TOIEx TOIE1

#    define OCIExA OCIE1A
#    define OCRxx OCR1A
#elif BACKLIGHT_PWM_TIMER == 3
#    define ICRx ICR1
#    define TCCRxA TCCR3A
#    define TCCRxB TCCR3B
#    define TIMERx_COMPA_vect TIMER3_COMPA_vect
#    define TIMERx_OVF_vect TIMER3_OVF_vect
#    define TIMSKx TIMSK3
#    define TOIEx TOIE3

#    define OCIExA OCIE3A
#    define OCRxx OCR3A
#else
#    error Invalid backlight PWM timer!
#endif

#ifndef BACKLIGHT_RESOLUTION
#    define BACKLIGHT_RESOLUTION 0xFFFFU
#endif

#if (BACKLIGHT_RESOLUTION > 0xFFFF || BACKLIGHT_RESOLUTION < 0x00FF)
#    error "Backlight resolution must be between 0x00FF and 0xFFFF"
#endif

#define BREATHING_SCALE_FACTOR F_CPU / BACKLIGHT_RESOLUTION / 120

// The idea of software PWM assisted by hardware timers is the following
// we use the hardware timer in fast PWM mode like for hardware PWM, but
// instead of letting the Output Match Comparator control the led pin
// (which is not possible since the backlight is not wired to PWM pins on the
// CPU), we do the LED on/off by oursleves.
// The timer is setup to count up to 0xFFFF, and we set the Output Compare
// register to the current 16bits backlight level (after CIE correction).
// This means the CPU will trigger a compare match interrupt when the counter
// reaches the backlight level, where we turn off the LEDs,
// but also an overflow interrupt when the counter rolls back to 0,
// in which we're going to turn on the LEDs.
// The LED will then be on for OCRxx/0xFFFF time, adjusted every 244Hz,
// or F_CPU/BACKLIGHT_RESOLUTION if used.

// Triggered when the counter reaches the OCRx value
ISR(TIMERx_COMPA_vect) {
    backlight_pins_off();
}

// Triggered when the counter reaches the TOP value
// this one triggers at F_CPU/ICRx = 16MHz/65536 =~ 244 Hz
ISR(TIMERx_OVF_vect) {
#ifdef BACKLIGHT_BREATHING
    if (is_breathing()) {
        breathing_task();
    }
#endif
    // for very small values of OCRxx (or backlight level)
    // we can't guarantee this whole code won't execute
    // at the same time as the compare match interrupt
    // which means that we might turn on the leds while
    // trying to turn them off, leading to flickering
    // artifacts (especially while breathing, because breathing_task
    // takes many computation cycles).
    // so better not turn them on while the counter TOP is very low.
    if (OCRxx > ICRx / 250 + 5) {
        backlight_pins_on();
    }
}

// See http://jared.geek.nz/2013/feb/linear-led-pwm
static uint16_t cie_lightness(uint16_t v) {
    if (v <= (uint32_t)ICRx / 12) // If the value is less than or equal to ~8% of max
    {
        return v / 9; // Same as dividing by 900%
    } else {
        // In the next two lines values are bit-shifted. This is to avoid loosing decimals in integer math.
        uint32_t y   = (((uint32_t)v + (uint32_t)ICRx / 6) << 5) / ((uint32_t)ICRx / 6 + ICRx); // If above 8%, add ~16% of max, and normalize with (max + ~16% max)
        uint32_t out = (y * y * y * ICRx) >> 15;                                                // Cube it and undo the bit-shifting. (which is now three times as much due to the cubing)

        if (out > ICRx) // Avoid overflows
        {
            out = ICRx;
        }
        return (uint16_t)out;
    }
}

// rescale the supplied backlight value to be in terms of the value limit	// range for val is [0..ICRx]. PWM pin is high while the timer count is below val.
static uint32_t rescale_limit_val(uint32_t val) {
    return (val * (BACKLIGHT_LIMIT_VAL + 1)) / 256;
}

// range for val is [0..ICRx]. PWM pin is high while the timer count is below val.
static inline void set_pwm(uint16_t val) {
    OCRxx = val;
}

void backlight_set(uint8_t level) {
    if (level > BACKLIGHT_LEVELS) level = BACKLIGHT_LEVELS;

    if (level == 0) {
        if (OCRxx) {
            TIMSKx &= ~(_BV(OCIExA));
            TIMSKx &= ~(_BV(TOIEx));
        }
        backlight_pins_off();
    } else {
        if (!OCRxx) {
            TIMSKx |= _BV(OCIExA);
            TIMSKx |= _BV(TOIEx);
        }
    }
    // Set the brightness
    set_pwm(cie_lightness(rescale_limit_val(ICRx * (uint32_t)level / BACKLIGHT_LEVELS)));
}

void backlight_task(void) {}

#ifdef BACKLIGHT_BREATHING
#    define BREATHING_NO_HALT 0
#    define BREATHING_HALT_OFF 1
#    define BREATHING_HALT_ON 2
#    define BREATHING_STEPS 128

static uint8_t  breathing_halt    = BREATHING_NO_HALT;
static uint16_t breathing_counter = 0;

static uint8_t breath_scale_counter = 1;
/* Run the breathing loop at ~120Hz*/
const uint8_t breathing_ISR_frequency = 120;

static bool breathing = false;

bool is_breathing(void) {
    return breathing;
}

#    define breathing_interrupt_enable() \
        do {                             \
            breathing = true;            \
        } while (0)
#    define breathing_interrupt_disable() \
        do {                              \
            breathing = false;            \
        } while (0)

#    define breathing_min()        \
        do {                       \
            breathing_counter = 0; \
        } while (0)
#    define breathing_max()                                                           \
        do {                                                                          \
            breathing_counter = get_breathing_period() * breathing_ISR_frequency / 2; \
        } while (0)

void breathing_enable(void) {
    breathing_counter = 0;
    breathing_halt    = BREATHING_NO_HALT;
    breathing_interrupt_enable();
}

void breathing_pulse(void) {
    if (get_backlight_level() == 0)
        breathing_min();
    else
        breathing_max();
    breathing_halt = BREATHING_HALT_ON;
    breathing_interrupt_enable();
}

void breathing_disable(void) {
    breathing_interrupt_disable();
    // Restore backlight level
    backlight_set(get_backlight_level());
}

void breathing_self_disable(void) {
    if (get_backlight_level() == 0)
        breathing_halt = BREATHING_HALT_OFF;
    else
        breathing_halt = BREATHING_HALT_ON;
}

/* To generate breathing curve in python:
 * from math import sin, pi; [int(sin(x/128.0*pi)**4*255) for x in range(128)]
 */
static const uint8_t breathing_table[BREATHING_STEPS] PROGMEM = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 17, 20, 24, 28, 32, 36, 41, 46, 51, 57, 63, 70, 76, 83, 91, 98, 106, 113, 121, 129, 138, 146, 154, 162, 170, 178, 185, 193, 200, 207, 213, 220, 225, 231, 235, 240, 244, 247, 250, 252, 253, 254, 255, 254, 253, 252, 250, 247, 244, 240, 235, 231, 225, 220, 213, 207, 200, 193, 185, 178, 170, 162, 154, 146, 138, 129, 121, 113, 106, 98, 91, 83, 76, 70, 63, 57, 51, 46, 41, 36, 32, 28, 24, 20, 17, 15, 12, 10, 8, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Use this before the cie_lightness function.
static inline uint16_t scale_backlight(uint16_t v) {
    return v / BACKLIGHT_LEVELS * get_backlight_level();
}

void breathing_task(void) {
    // Only run this ISR at ~120 Hz
    if (breath_scale_counter++ == BREATHING_SCALE_FACTOR) {
        breath_scale_counter = 1;
    } else {
        return;
    }
    uint16_t interval = (uint16_t)get_breathing_period() * breathing_ISR_frequency / BREATHING_STEPS;
    // resetting after one period to prevent ugly reset at overflow.
    breathing_counter = (breathing_counter + 1) % (get_breathing_period() * breathing_ISR_frequency);
    uint8_t index     = breathing_counter / interval;
    // limit index to max step value
    if (index >= BREATHING_STEPS) {
        index = BREATHING_STEPS - 1;
    }

    if (((breathing_halt == BREATHING_HALT_ON) && (index == BREATHING_STEPS / 2)) || ((breathing_halt == BREATHING_HALT_OFF) && (index == BREATHING_STEPS - 1))) {
        breathing_interrupt_disable();
    }

    // Set PWM to a brightnessvalue scaled to the configured resolution
    set_pwm(cie_lightness(rescale_limit_val(scale_backlight((uint32_t)pgm_read_byte(&breathing_table[index]) * ICRx / 255))));
}

#endif // BACKLIGHT_BREATHING

void backlight_init_ports(void) {
    // Setup backlight pin as output and output to on state.
    backlight_pins_init();

    // I could write a wall of text here to explain... but TL;DW
    // Go read the ATmega32u4 datasheet.
    // And this: http://blog.saikoled.com/post/43165849837/secret-konami-cheat-code-to-high-resolution-pwm-on

    // TimerX setup, Fast PWM mode count to TOP set in ICRx
    TCCRxA = _BV(WGM11); // = 0b00000010;
    // clock select clk/1
    TCCRxB = _BV(WGM13) | _BV(WGM12) | _BV(CS10); // = 0b00011001;
    ICRx   = BACKLIGHT_RESOLUTION;

    backlight_init();

#ifdef BACKLIGHT_BREATHING
    if (is_backlight_breathing()) {
        breathing_enable();
    }
#endif
}
