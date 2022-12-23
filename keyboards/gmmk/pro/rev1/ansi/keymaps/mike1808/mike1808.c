/* Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "mike1808.h"

#if (__has_include("secrets.h") && !defined(NO_SECRETS))
#    include "secrets.h"
#else
// `PROGMEM const char secret[][x]` may work better, but it takes up more space in the firmware
// And I'm not familiar enough to know which is better or why...
static const char *const secrets[] = {"test1", "test2", "test3", "test4", "test5"};
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
bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) {
    // Turn on sideglow when CAPS LOCK is activated
    if (host_keyboard_led_state().caps_lock) {
        HSV hsv = {CAPS_LOCK_COLOR};
        hsv.v = rgb_matrix_get_val();
        RGB rgb = hsv_to_rgb(hsv);

        for (uint8_t i = led_min; i < led_max; i++) {
            if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
                RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
            }
        }
    }
    return false;
}
#endif  // RGB_MATRIX_ENABLE
