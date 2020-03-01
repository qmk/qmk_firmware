#include "quantum.h"
#include "backlight.h"

#if !defined(BACKLIGHT_PIN) && !defined(BACKLIGHT_PINS)
#    error "Backlight pin/pins not defined. Please configure."
#endif

#ifdef BACKLIGHT_BREATHING
#    error "Backlight breathing is not available for software PWM. Please disable."
#endif

#ifndef BACKLIGHT_ON_STATE
#    define BACKLIGHT_ON_STATE 1
#endif

#ifdef BACKLIGHT_PINS
#    define BACKLIGHT_PIN_INIT BACKLIGHT_PINS
#else
#    define BACKLIGHT_PIN_INIT \
        { BACKLIGHT_PIN }
#endif

static uint16_t    s_duty_pattern   = 0;
static const pin_t backlight_pins[] = BACKLIGHT_PIN_INIT;
#define BACKLIGHT_LED_COUNT (sizeof(backlight_pins) / sizeof(pin_t))

#define FOR_EACH_LED(x)                                 \
    for (uint8_t i = 0; i < BACKLIGHT_LED_COUNT; i++) { \
        pin_t backlight_pin = backlight_pins[i];        \
        { x }                                           \
    }

void backlight_on(pin_t backlight_pin) {
#if BACKLIGHT_ON_STATE == 0
    writePinLow(backlight_pin);
#else
    writePinHigh(backlight_pin);
#endif
}

void backlight_off(pin_t backlight_pin) {
#if BACKLIGHT_ON_STATE == 0
    writePinHigh(backlight_pin);
#else
    writePinLow(backlight_pin);
#endif
}

void backlight_init_ports(void) {
    // Setup backlight pin as output and output to off state.
    FOR_EACH_LED(setPinOutput(backlight_pin); backlight_off(backlight_pin);)
}

// clang-format off

/** \brief PWM duty patterns
 *
 * We scale the current backlight level to an index within this array. This allows
 * backlight_task to focus on just switching LEDs on/off, and we can predict the duty pattern
 */
static uint16_t backlight_duty_table[] = {
    0b0000000000000000,
    0b1000000000000000,
    0b1000000010000000,
    0b1000001000010000,
    0b1000100010001000,
    0b1001001001001000,
    0b1010101010101010,
    0b1110111011101110,
    0b1111111111111111,
};
#define backlight_duty_table_size (sizeof(backlight_duty_table) / sizeof(backlight_duty_table[0]))

// clang-format on

static uint8_t scale_backlight(uint8_t v) { return v * (backlight_duty_table_size - 1) / BACKLIGHT_LEVELS; }

void backlight_task(void) {
    static uint8_t backlight_tick = 0;

    if (s_duty_pattern & ((uint16_t)1 << backlight_tick)) {
        FOR_EACH_LED(backlight_on(backlight_pin);)
    } else {
        FOR_EACH_LED(backlight_off(backlight_pin);)
    }
    backlight_tick = (backlight_tick + 1) % 16;
}

void backlight_set(uint8_t level) { s_duty_pattern = backlight_duty_table[scale_backlight(level)]; }
