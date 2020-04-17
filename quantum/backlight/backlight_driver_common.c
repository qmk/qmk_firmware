#include "quantum.h"
#include "backlight.h"
#include "backlight_driver_common.h"

#ifdef SPLIT_KEYBOARD
#    include "split_util.h"
#endif

#if !defined(BACKLIGHT_PIN) && !defined(BACKLIGHT_PINS)
#    error "Backlight pin/pins not defined. Please configure."
#endif

static inline void backlight_on(pin_t backlight_pin) {
#if BACKLIGHT_ON_STATE == 0
    writePinLow(backlight_pin);
#else
    writePinHigh(backlight_pin);
#endif
}

static inline void backlight_off(pin_t backlight_pin) {
#if BACKLIGHT_ON_STATE == 0
    writePinHigh(backlight_pin);
#else
    writePinLow(backlight_pin);
#endif
}

#if defined(BACKLIGHT_PINS)
static const pin_t backlight_pins[] = BACKLIGHT_PINS;
#    ifndef BACKLIGHT_LED_COUNT
#        define BACKLIGHT_LED_COUNT (sizeof(backlight_pins) / sizeof(pin_t))
#    endif

#    define FOR_EACH_LED(x)                                 \
        for (uint8_t i = 0; i < BACKLIGHT_LED_COUNT; i++) { \
            pin_t backlight_pin = backlight_pins[i];        \
            { x }                                           \
        }
#else
// we support only one backlight pin
static const pin_t backlight_pin = BACKLIGHT_PIN;
#    define FOR_EACH_LED(x) x
#endif

#if !defined(BACKLIGHT_PIN) && !defined(BACKLIGHT_PINS)
#    error "Backlight pin/pins not defined. Please configure."
#endif

#ifdef SPLIT_KEYBOARD
#if defined(BACKLIGHT_PINS_RIGHT)
static const pin_t backlight_pins_right[] = BACKLIGHT_PINS_RIGHT;
#    ifndef BACKLIGHT_LED_COUNT_RIGHT
#        define BACKLIGHT_LED_COUNT_RIGHT (sizeof(backlight_pins_right) / sizeof(pin_t))
#    endif

#    define FOR_EACH_LED_RIGHT(x)                                 \
        for (uint8_t i = 0; i < BACKLIGHT_LED_COUNT_RIGHT; i++) { \
            pin_t backlight_pin_right = backlight_pins_right[i];        \
            { x }                                           \
        }
#else
// we support only one backlight pin
static const pin_t backlight_pin_right = BACKLIGHT_PIN_RIGHT;
#    define FOR_EACH_LED_RIGHT(x) x
#endif
#endif // SPLIT_KEYBOARD

void backlight_pins_init(void) {
    // Setup backlight pin as output and output to off state.
    FOR_EACH_LED(setPinOutput(backlight_pin); backlight_off(backlight_pin);)
}

void backlight_pins_on(void) { FOR_EACH_LED(backlight_on(backlight_pin);) }

void backlight_pins_off(void) { FOR_EACH_LED(backlight_off(backlight_pin);) }

#ifdef SPLIT_KEYBOARD
void backlight_pins_init_right(void) {
    // Setup backlight pin as output and output to off state.
    FOR_EACH_LED_RIGHT(setPinOutput(backlight_pin_right); backlight_off(backlight_pin_right);)
}

void backlight_pins_on_right(void) { FOR_EACH_LED_RIGHT(backlight_on(backlight_pin_right);) }

void backlight_pins_off_right(void) { FOR_EACH_LED_RIGHT(backlight_off(backlight_pin_right);) }
#endif
