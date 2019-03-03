/*
Copyright 2019 Batuhan Başerdem <baserdem.batuhan@gmail.com> @bbaserdem
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "bbaserdem.h"

// Keymap custom keycodes
__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

//----Specific functionality

// Audio: Music layer (audio_stuff.h)
__attribute__ ((weak))
bool process_record_audio(uint16_t keycode, keyrecord_t *record) {
    return true;
}
// Macro: Double key presses (double_press.h)
__attribute__ ((weak))
bool process_record_macro(uint16_t keycode, keyrecord_t *record) {
    return true;
}
// Mouse: Extra mouse codes (mouse_emulation.h)
__attribute__ ((weak))
bool process_record_mouse(uint16_t keycode, keyrecord_t *record) {
    return true;
}
// RGBLIGHT: RGB backlight modifiers (rgb_bl_stuff.h)
__attribute__ ((weak))
bool process_record_rgb_light(uint16_t keycode, keyrecord_t *record) {
    return true;
}
// RGB MATRIX: RGB backlight modifiers (rgb_key_stuff.h)
__attribute__ ((weak))
bool process_record_rgb_matrix(uint16_t keycode, keyrecord_t *record) {
    return true;
}
// Secrets: Secret keycodes that output macros (secrets.h)
__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
    return true;
}

//-----Keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case K_LOCK:
            if (record->event.pressed) {
                userspace_config.lock_flag = !userspace_config.lock_flag;
            }
            return false;
            break;
        case MANUAL_ELLIPSIS:
            if (record->event.pressed) {
                SEND_STRING("...");
            }
            return false;
            break;
    }
    return process_record_keymap(keycode, record)   &&
    process_record_audio(keycode, record)           &&
    process_record_macro(keycode, record)           &&
    process_record_mouse(keycode, record)           &&
    process_record_rgb_light(keycode, record)       &&
    process_record_rgb_matrix(keycode, record)      &&
    process_record_secrets(keycode, record);
}
