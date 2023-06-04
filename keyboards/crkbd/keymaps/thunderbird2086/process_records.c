// Copyright 2021 Allen Choi (@thunderbird2086)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "keycodes.h"
#include "version.h"

__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

__attribute__((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
    return true;
}

#if defined(OLED_ENABLE)
__attribute__((weak))
bool process_record_oled(uint16_t keycode, keyrecord_t *record) {
    return true;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case COLEMAK:
                set_single_persistent_default_layer(_COLEMAK);
                break;
            case QWERTY:
                set_single_persistent_default_layer(_QWERTY);
                break;
#           if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            case RGBRST:
#               if defined(RGBLIGHT_ENABLE)
                eeconfig_update_rgblight_default();
                rgblight_enable();
#               else 
                eeconfig_update_rgb_matrix_default();
#               endif
                break;
#           endif
            case VRSN:
                send_string(
                    "# qmk " QMK_VERSION "\n" SS_DELAY(VER_NEWLINE_WAIT)
                    "# " QMK_KEYBOARD "/" QMK_KEYMAP "\n" SS_DELAY(VER_NEWLINE_WAIT)
                    "# built on: " QMK_BUILDDATE "\n");
                break;
        }
    }

    return process_record_keymap(keycode, record) && process_record_secrets(keycode, record)
#   if defined(OLED_ENABLE)
           && process_record_oled(keycode, record)
#   endif
           ;
}
