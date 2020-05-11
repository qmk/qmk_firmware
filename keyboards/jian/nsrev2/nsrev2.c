#include "nsrev2.h"

// TODO:
#ifdef SWAP_HANDS_ENABLE
const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{13, 0}, {12, 0}, {11, 0}, {10, 0}, {9, 0}, {8, 0}, {7, 0}, {6, 0}, {5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}},
  {{13, 1}, {12, 1}, {11, 1}, {10, 1}, {9, 1}, {8, 1}, {7, 1}, {6, 1}, {5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1}},
  {{13, 2}, {12, 2}, {11, 2}, {10, 2}, {9, 2}, {8, 2}, {7, 2}, {6, 2}, {5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 2}},
  {{13, 3}, {12, 3}, {11, 3}, {10, 3}, {9, 3}, {8, 3}, {7, 3}, {6, 3}, {5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}},
};
#endif

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

#ifdef PHYSICAL_LEDS_ENABLE
void led_init_kb(void)
{
#ifdef NUM_LOCK_LED_PIN
    setPinOutput(NUM_LOCK_LED_PIN);
    RESET_NUM_LOCK_LED();
#endif // NUM_LOCK_LED_PIN
#ifdef CAPS_LOCK_LED_PIN
    setPinOutput(CAPS_LOCK_LED_PIN);
    RESET_CAPS_LOCK_LED();
#endif // CAPS_LOCK_LED_PIN
#ifdef SCROLL_LOCK_LED_PIN
    setPinOutput(SCROLL_LOCK_LED_PIN);
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
