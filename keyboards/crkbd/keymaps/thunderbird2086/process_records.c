// Copyright 2021 Allen Choi (@thunderbird2086)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "keycodes.h"

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
    switch (keycode) {

    case COLEMAK:
        if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
        }
        break;
    case QWERTY:
        if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
        }
        break;
    }

    return process_record_keymap(keycode, record) && process_record_secrets(keycode, record)
#   if defined(OLED_ENABLE)
           && process_record_oled(keycode, record)
#   endif
           ;
}
