#include "quantum.h"

#ifdef SWAP_HANDS_ENABLE
__attribute__ ((weak))
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}},
  {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}},
  {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}},
  {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}},
  {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}},
  {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}},
  {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}},
  {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}},
};
#endif

#ifdef BACKLIGHT_ENABLE
static bool backlight_was_toggled = false;

void suspend_power_down_kb(void) {
    if (is_backlight_enabled()) {
        backlight_disable();
        backlight_was_toggled = true;
    }
}

void suspend_wakeup_init_kb(void) {
    if (backlight_was_toggled) {
        backlight_enable();
        backlight_was_toggled = false;
    }
}
#endif

#ifdef PHYSICAL_LEDS_ENABLE
void led_init_kb(void)
{
#ifdef NUM_LOCK_LED_PIN
    gpio_set_pin_output(NUM_LOCK_LED_PIN);
    RESET_NUM_LOCK_LED();
#endif // NUM_LOCK_LED_PIN
#ifdef CAPS_LOCK_LED_PIN
    gpio_set_pin_output(CAPS_LOCK_LED_PIN);
    RESET_CAPS_LOCK_LED();
#endif // CAPS_LOCK_LED_PIN
#ifdef SCROLL_LOCK_LED_PIN
    gpio_set_pin_output(SCROLL_LOCK_LED_PIN);
    RESET_SCROLL_LOCK_LED();
#endif // SCROLL_LOCK_LED_PIN
}
#endif // PHYSICAL_LEDS_ENABLE

void matrix_init_kb(void) {
#ifdef PHYSICAL_LEDS_ENABLE
  led_init_kb();
#endif // PHYSICAL_LEDS_ENABLE
  matrix_init_user();
};

#ifdef PHYSICAL_LEDS_ENABLE
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
#ifdef NUM_LOCK_LED_PIN
        UPDATE_NUM_LOCK_LED();
#endif // NUM_LOCK_LED_PIN
#ifdef CAPS_LOCK_LED_PIN
        UPDATE_CAPS_LOCK_LED();
#endif // CAPS_LOCK_LED_PIN
#ifdef SCROLL_LOCK_LED_PIN
        UPDATE_SCROLL_LOCK_LED();
#endif // SCROLL_LOCK_LED_PIN
    }
    return res;
}
#endif // PHYSICAL_LEDS_ENABLE
