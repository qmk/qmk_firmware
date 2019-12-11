#include "quantum.h"
#include "backlight.h"

#if !defined(BACKLIGHT_PIN) && !defined(BACKLIGHT_PINS)
#    error "Backlight pin/pins not defined. Please configure."
#endif

#ifdef BACKLIGHT_BREATHING
#    error "Backlight breathing is not available for software PWM. Please disable."
#endif

#ifndef BACKLIGHT_ON_STATE
#    define BACKLIGHT_ON_STATE 0
#endif

#ifdef BACKLIGHT_PINS
#    define BACKLIGHT_PIN_INIT BACKLIGHT_PINS
#else
#    define BACKLIGHT_PIN_INIT \
        { BACKLIGHT_PIN }
#endif

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
    // Setup backlight pin as output and output to on state.
    FOR_EACH_LED(setPinOutput(backlight_pin); backlight_on(backlight_pin);)
}

void backlight_task(void) {
    static uint8_t backlight_tick = 0;

    if ((0xFFFF >> (get_backlight_level() * ((BACKLIGHT_LEVELS + 1) / 2))) & (1 << backlight_tick)) {
        FOR_EACH_LED(backlight_on(backlight_pin);)
    } else {
        FOR_EACH_LED(backlight_off(backlight_pin);)
    }
    backlight_tick = (backlight_tick + 1) % 16;
}

void backlight_set(uint8_t level) {
    // noop as backlight_task uses get_backlight_level()
}
