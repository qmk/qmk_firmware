#include "print.h"
#include "quantum.h"

#include "pcal6416a/pcal6416a.h"
#include "indicator_leds.h"

#ifndef NUM_LOCK_PCAL_PINS
#define NUM_LOCK_PCAL_PINS {}
#endif

#ifndef SCROLL_LOCK_PCAL_PINS
#define SCROLL_LOCK_PCAL_PINS {}
#endif

#ifndef CAPS_LOCK_PCAL_PINS
#define CAPS_LOCK_PCAL_PINS {}
#endif

static const pcal_gpio_pin num_lock_pins[] = NUM_LOCK_PCAL_PINS;
static const pcal_gpio_pin scroll_lock_pins[] = SCROLL_LOCK_PCAL_PINS;
static const pcal_gpio_pin caps_lock_pins[] = CAPS_LOCK_PCAL_PINS;

#define PIN_ARR_SIZE(ARR) (sizeof(ARR)/sizeof(pcal_gpio_pin))

void indicator_leds_init(void) {
    set_pin_array_initial_state(num_lock_pins, PIN_ARR_SIZE(num_lock_pins), LOW);
    set_pin_array_initial_state(scroll_lock_pins, PIN_ARR_SIZE(scroll_lock_pins), LOW);
    set_pin_array_initial_state(caps_lock_pins, PIN_ARR_SIZE(caps_lock_pins), LOW);
}

// Runs after matrix init so pcal6416a will be configured
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        set_pin_array_state(num_lock_pins, PIN_ARR_SIZE(num_lock_pins), led_state.num_lock);
        set_pin_array_state(scroll_lock_pins, PIN_ARR_SIZE(scroll_lock_pins), led_state.scroll_lock);
        set_pin_array_state(caps_lock_pins, PIN_ARR_SIZE(caps_lock_pins), led_state.caps_lock);
    }

    return res;
}
