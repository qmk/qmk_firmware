/* Copyright 2020 Janos Daniel Reibl <janos.daniel.reibl@protonmail.com> @riblee
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

#include "riblee.h"
#include "raw_hid.h"
#include <string.h>

const uint8_t shift = MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT);

// Tap Dance functions
void dance_key_a (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING("a");
        reset_tap_dance(state);
    } else if (state->count == 2) {
        if (!(keyboard_report->mods & shift)) {
            send_unicode_string("á");
        } else {
            send_unicode_string("Á");
        }

        reset_tap_dance(state);
    }
}

void dance_key_e (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING("e");
        reset_tap_dance(state);
    } else if (state->count == 2) {
        if (!(keyboard_report->mods & shift)) {
            send_unicode_string("é");
        } else {
            send_unicode_string("É");
        }

        reset_tap_dance(state);
    }
}

void dance_key_i (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING("i");
        reset_tap_dance(state);
    } else if (state->count == 2) {
        if (!(keyboard_report->mods & shift)) {
            send_unicode_string("í");
        } else {
            send_unicode_string("Í");
        }

        reset_tap_dance(state);
    }
}

void dance_key_o (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING("o");
        reset_tap_dance(state);
    } else if (state->count == 2) {
        if (!(keyboard_report->mods & shift)) {
            send_unicode_string("ó");
        } else {
            send_unicode_string("Ó");
        }

        reset_tap_dance(state);
    } else if (state->count == 3) {
        if (!(keyboard_report->mods & shift)) {
            send_unicode_string("ö");
        } else {
            send_unicode_string("Ö");
        }

        reset_tap_dance(state);
    } else if (state->count == 4) {
        if (!(keyboard_report->mods & shift)) {
            send_unicode_string("ő");
        } else {
            send_unicode_string("Ő");
        }

        reset_tap_dance(state);
    }
}

void dance_key_u (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING("u");
        reset_tap_dance(state);
    } else if (state->count == 2) {
        if (!(keyboard_report->mods & shift)) {
            send_unicode_string("ú");
        } else {
            send_unicode_string("Ú");
        }

        reset_tap_dance(state);
    } else if (state->count == 3) {
        if (!(keyboard_report->mods & shift)) {
            send_unicode_string("ü");
        } else {
            send_unicode_string("Ü");
        }

        reset_tap_dance(state);
    } else if (state->count == 4) {
        if (!(keyboard_report->mods & shift)) {
            send_unicode_string("ű");
        } else {
            send_unicode_string("Ű");
        }

        reset_tap_dance(state);
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
            break;
        case DVORAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DVORAK);
            }
            return false;
            break;
        case HUNGARIAN:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_HUNGARIAN);
            }
            return false;
            break;
        case BACKLIT:
            if (record->event.pressed) {
                register_code(keycode_config(KC_LGUI));
#ifdef BACKLIGHT_ENABLE
                backlight_step();
#endif
            } else {
                unregister_code(keycode_config(KC_LGUI));
            }
            return false;
            break;
    }
    return true;
};

#ifdef OLED_ENABLE

static char receive_buffer[128] = {};
static uint8_t receive_buffer_length = 0;

void oled_task_user(void) {
    // Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Print string received via HID RAW
    oled_write_ln(receive_buffer, false);
}

#ifdef RAW_ENABLE

void raw_hid_receive(uint8_t *data, uint8_t length) {

    // Append data to receive_buffer, without the first byte
    memcpy(receive_buffer + receive_buffer_length, data + 1, length - 1);
    receive_buffer_length += (length - 1);

    // First byte indicate if we will recive more package for the current string
    // If it's 1 then this was the last package and we can reset the offset
    if (data[0] == 1) {
        // Reset the offset for memcpy to the begining of our buffer
        receive_buffer_length = 0;
    }

    // Reset the offset to prevent overwriting memory outside of the buffer
    if (receive_buffer_length + 32 >= 128) {
        receive_buffer_length = 0;
    }

}

#endif

#endif
