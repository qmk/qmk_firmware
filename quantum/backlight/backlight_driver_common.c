#include "backlight.h"
#include "backlight_driver_common.h"
#include "gpio.h"
#include "util.h"

#if !defined(BACKLIGHT_PIN) && !defined(BACKLIGHT_PINS)
#    error "Backlight pin/pins not defined. Please configure."
#endif

#if defined(BACKLIGHT_PINS)
static const pin_t backlight_pins[] = BACKLIGHT_PINS;
#    ifndef BACKLIGHT_LED_COUNT
#        define BACKLIGHT_LED_COUNT ARRAY_SIZE(backlight_pins)
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

static inline void backlight_on(pin_t backlight_pin) {
#if BACKLIGHT_ON_STATE == 0
    gpio_write_pin_low(backlight_pin);
#else
    gpio_write_pin_high(backlight_pin);
#endif
}

static inline void backlight_off(pin_t backlight_pin) {
#if BACKLIGHT_ON_STATE == 0
    gpio_write_pin_high(backlight_pin);
#else
    gpio_write_pin_low(backlight_pin);
#endif
}

void backlight_pins_init(void) {
    // Setup backlight pin as output and output to off state.
    FOR_EACH_LED(gpio_set_pin_output(backlight_pin); backlight_off(backlight_pin);)
}

void backlight_pins_on(void) {
    FOR_EACH_LED(backlight_on(backlight_pin);)
}

void backlight_pins_off(void) {
    FOR_EACH_LED(backlight_off(backlight_pin);)
}
