// Copyright 2023 Massdrop, Inc.
// SPDX-License-Identifier: GPL-2.0-or-later
#ifdef RGB_MATRIX_ENABLE
#    include "host.h"
#    include "quantum.h"
#    include "rgb_matrix.h"

#    ifdef RGB_MATRIX_CAPS_LOCK_INDEX
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    if (host_keyboard_led_state().caps_lock && (rgb_matrix_get_flags() != LED_FLAG_NONE)) {
        rgb_matrix_set_color(RGB_MATRIX_CAPS_LOCK_INDEX, RGB_WHITE);
    } else if (rgb_matrix_get_flags() == LED_FLAG_UNDERGLOW) {
        rgb_matrix_set_color(RGB_MATRIX_CAPS_LOCK_INDEX, RGB_OFF);
    }
    return true;
}
#    endif

#    ifdef RGB_MATRIX_CYCLE_ZONES_ENABLE
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    if (!record->event.pressed) {
        switch (keycode) {
            case QK_RGB_MATRIX_TOGGLE:
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL:
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                        break;
                    case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR):
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        break;
                    case LED_FLAG_UNDERGLOW:
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        break;
                    default:
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        break;
                }
                return false;
        }
    }
    return true;
};
#    endif

#endif
