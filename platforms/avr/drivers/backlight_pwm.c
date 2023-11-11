#include "backlight.h"
#include "gpio.h"
#include "progmem.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Maximum duty cycle limit
#ifndef BACKLIGHT_LIMIT_VAL
#    define BACKLIGHT_LIMIT_VAL 255
#endif

#if (defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__) || defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__)) && (BACKLIGHT_PIN == B5 || BACKLIGHT_PIN == B6 || BACKLIGHT_PIN == B7)
#    define ICRx ICR1
#    define TCCRxA TCCR1A
#    define TCCRxB TCCR1B
#    define TIMERx_OVF_vect TIMER1_OVF_vect
#    define TIMSKx TIMSK1
#    define TOIEx TOIE1

#    if BACKLIGHT_PIN == B5
#        define COMxx0 COM1A0
#        define COMxx1 COM1A1
#        define OCRxx OCR1A
#    elif BACKLIGHT_PIN == B6
#        define COMxx0 COM1B0
#        define COMxx1 COM1B1
#        define OCRxx OCR1B
#    elif BACKLIGHT_PIN == B7
#        define COMxx0 COM1C0
#        define COMxx1 COM1C1
#        define OCRxx OCR1C
#    endif
#elif (defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__) || defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__)) && (BACKLIGHT_PIN == C4 || BACKLIGHT_PIN == C5 || BACKLIGHT_PIN == C6)
#    define ICRx ICR3
#    define TCCRxA TCCR3A
#    define TCCRxB TCCR3B
#    define TIMERx_OVF_vect TIMER3_OVF_vect
#    define TIMSKx TIMSK3
#    define TOIEx TOIE3

#    if BACKLIGHT_PIN == C4
#        if (defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__))
#            error This MCU has no C4 pin!
#        else
#            define COMxx0 COM3C0
#            define COMxx1 COM3C1
#            define OCRxx OCR3C
#        endif
#    elif BACKLIGHT_PIN == C5
#        if (defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__))
#            error This MCU has no C5 pin!
#        else
#            define COMxx0 COM3B0
#            define COMxx1 COM3B1
#            define OCRxx OCR3B
#        endif
#    elif BACKLIGHT_PIN == C6
#        define COMxx0 COM3A0
#        define COMxx1 COM3A1
#        define OCRxx OCR3A
#    endif
#elif (defined(__AVR_AT90USB162__) || defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega32U2__)) && (BACKLIGHT_PIN == B7 || BACKLIGHT_PIN == C5 || BACKLIGHT_PIN == C6)
#    define ICRx ICR1
#    define TCCRxA TCCR1A
#    define TCCRxB TCCR1B
#    define TIMERx_OVF_vect TIMER1_OVF_vect
#    define TIMSKx TIMSK1
#    define TOIEx TOIE1

#    if BACKLIGHT_PIN == B7
#        define COMxx0 COM1C0
#        define COMxx1 COM1C1
#        define OCRxx OCR1C
#    elif BACKLIGHT_PIN == C5
#        define COMxx0 COM1B0
#        define COMxx1 COM1B1
#        define OCRxx OCR1B
#    elif BACKLIGHT_PIN == C6
#        define COMxx0 COM1A0
#        define COMxx1 COM1A1
#        define OCRxx OCR1A
#    endif
#elif defined(__AVR_ATmega32A__) && (BACKLIGHT_PIN == D4 || BACKLIGHT_PIN == D5)
#    define ICRx ICR1
#    define TCCRxA TCCR1A
#    define TCCRxB TCCR1B
#    define TIMERx_OVF_vect TIMER1_OVF_vect
#    define TIMSKx TIMSK
#    define TOIEx TOIE1

#    if BACKLIGHT_PIN == D4
#        define COMxx0 COM1B0
#        define COMxx1 COM1B1
#        define OCRxx OCR1B
#    elif BACKLIGHT_PIN == D5
#        define COMxx0 COM1A0
#        define COMxx1 COM1A1
#        define OCRxx OCR1A
#    endif
#elif (defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)) && (BACKLIGHT_PIN == B1 || BACKLIGHT_PIN == B2)
#    define ICRx ICR1
#    define TCCRxA TCCR1A
#    define TCCRxB TCCR1B
#    define TIMERx_OVF_vect TIMER1_OVF_vect
#    define TIMSKx TIMSK1
#    define TOIEx TOIE1

#    if BACKLIGHT_PIN == B1
#        define COMxx0 COM1A0
#        define COMxx1 COM1A1
#        define OCRxx OCR1A
#    elif BACKLIGHT_PIN == B2
#        define COMxx0 COM1B0
#        define COMxx1 COM1B1
#        define OCRxx OCR1B
#    endif
#endif

#ifndef BACKLIGHT_RESOLUTION
#    define BACKLIGHT_RESOLUTION 0xFFFFU
#endif

#if (BACKLIGHT_RESOLUTION > 0xFFFF || BACKLIGHT_RESOLUTION < 0x00FF)
#    error "Backlight resolution must be between 0x00FF and 0xFFFF"
#endif

#define BREATHING_SCALE_FACTOR F_CPU / BACKLIGHT_RESOLUTION / 120

static inline void enable_pwm(void) {
#if BACKLIGHT_ON_STATE == 1
    TCCRxA |= _BV(COMxx1);
#else
    TCCRxA |= _BV(COMxx1) | _BV(COMxx0);
#endif
}

static inline void disable_pwm(void) {
#if BACKLIGHT_ON_STATE == 1
    TCCRxA &= ~(_BV(COMxx1));
#else
    TCCRxA &= ~(_BV(COMxx1) | _BV(COMxx0));
#endif
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
        // Turn off PWM control on backlight pin
        disable_pwm();
    } else {
        // Turn on PWM control of backlight pin
        enable_pwm();
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

bool is_breathing(void) {
    return !!(TIMSKx & _BV(TOIEx));
}

#    define breathing_interrupt_enable() \
        do {                             \
            TIMSKx |= _BV(TOIEx);        \
        } while (0)
#    define breathing_interrupt_disable() \
        do {                              \
            TIMSKx &= ~_BV(TOIEx);        \
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

/* Assuming a 16MHz CPU clock and a timer that resets at 64k (ICR1), the following interrupt handler will run
 * about 244 times per second.
 *
 * The following ISR runs at F_CPU/ISRx. With a 16MHz clock and default pwm resolution, that means 244Hz
 */
ISR(TIMERx_OVF_vect) {
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
    setPinOutput(BACKLIGHT_PIN);
#if BACKLIGHT_ON_STATE == 1
    writePinLow(BACKLIGHT_PIN);
#else
    writePinHigh(BACKLIGHT_PIN);
#endif

    // I could write a wall of text here to explain... but TL;DW
    // Go read the ATmega32u4 datasheet.
    // And this: http://blog.saikoled.com/post/43165849837/secret-konami-cheat-code-to-high-resolution-pwm-on

    // Pin PB7 = OCR1C (Timer 1, Channel C)
    // Compare Output Mode = Clear on compare match, Channel C = COM1C1=1 COM1C0=0
    // (i.e. start high, go low when counter matches.)
    // WGM Mode 14 (Fast PWM) = WGM13=1 WGM12=1 WGM11=1 WGM10=0
    // Clock Select = clk/1 (no prescaling) = CS12=0 CS11=0 CS10=1

    /*
    14.8.3:
    "In fast PWM mode, the compare units allow generation of PWM waveforms on the OCnx pins. Setting the COMnx1:0 bits to two will produce a non-inverted PWM [..]."
    "In fast PWM mode the counter is incremented until the counter value matches either one of the fixed values 0x00FF, 0x01FF, or 0x03FF (WGMn3:0 = 5, 6, or 7), the value in ICRn (WGMn3:0 = 14), or the value in OCRnA (WGMn3:0 = 15)."
    */
    TCCRxA = _BV(COMxx1) | _BV(WGM11);            // = 0b00001010;
    TCCRxB = _BV(WGM13) | _BV(WGM12) | _BV(CS10); // = 0b00011001;
    ICRx   = BACKLIGHT_RESOLUTION;

    backlight_init();

#ifdef BACKLIGHT_BREATHING
    if (is_backlight_breathing()) {
        breathing_enable();
    }
#endif
}
