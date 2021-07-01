#include "mike1808.h"

#if (__has_include("secrets.h") && !defined(NO_SECRETS))
#    include "secrets.h"
#else
// `PROGMEM const char secret[][x]` may work better, but it takes up more space in the firmware
// And I'm not familiar enough to know which is better or why...
static const char *const secret[] = {"test1", "test2", "test3", "test4", "test5"};
#endif

// userspace_config_t userspace_config;

bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_SECRET_1 ... KC_SECRET_5:  // Secrets!  Externally defined strings, not stored in repo
            if (!record->event.pressed) {
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                send_string_with_delay(secrets[keycode - KC_SECRET_1], MACRO_TIMER);
            }
            return false;
            break;
    }
    return true;
}

void suspend_power_down_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(true);
#endif  // RGB_MATRIX_ENABLE
}

void suspend_wakeup_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(false);
#endif  // RGB_MATRIX_ENABLE
}

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        HSV hsv = {HSV_RED};
        hsv.v = rgb_matrix_get_val();
        RGB rgb = hsv_to_rgb(hsv);

        for (uint8_t i = led_min; i < led_max; i++) {
            if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
            }
        }
    }
}
#endif  // RGB_MATRIX_ENABLE

