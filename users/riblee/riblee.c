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
        case WORKMAN:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_WORKMAN);
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
        case CG_NORM:
            set_unicode_input_mode(UC_MAC);
            break;
        case CG_SWAP:
            set_unicode_input_mode(UC_LNX);
            break;
    }
    return true;
};

#ifdef OLED_ENABLE

static char receive_buffer[128] = {};
static uint8_t receive_buffer_length = 0;
uint16_t startup_timer;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    startup_timer = timer_read();
    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0, 96, 96, 96,240,248,255, 63, 56,255,255,248, 63, 63,248,255,255, 56, 63,255,248,240, 96, 96, 96,  0,  0,  0,  0,  0,252,254, 38, 54, 60,  8,240,152,152,248,240, 24,248,224,248,120,224,240,120, 96,248,248,248,248, 32,248,248, 24, 24,240,248,248,248,240,240,248,152,152,254,254,  0,  0,  0,254,254,152,248,240, 24,248,224,240,120,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,219,219,219,255,255,255,240,192,143,159, 63,  0,  0, 63,159,143,192,240,255,255,255,219,219,219,  0,  0,  0,  0,  0,192,225,112, 48, 48, 48,112,225,129,  1,240,240,240,193,  1,  0,  1,193,240,240,241,  1,  1,241,240,193,225,112, 48,  0,  1,  1,  1,  1,240,241, 49, 49, 49,  0,240,240,  0,129,193,129,193,192,  0,196,135,193,192,128,128,192,192,128,  0,  0,192,128,  0,128,192,128,  0,  0,192,192,128,128,192,192,192,128,  0,128,192,128,192,192,  0,128,192,192,192,128,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  6,  6,  6, 15, 31,255,255, 31,255,255, 31,252,252, 31,255,255, 31,255,255, 31, 15,  6,  6,  6,  0,  0,  0,  0,  0, 15, 31, 56, 48, 48, 48, 60,127,103, 96, 63, 63,  0,  7, 63, 56, 31,  7,  0, 63, 63,  0,  0, 63, 63,  7, 30, 60, 48,  0,  0,  0,  0,  0, 63, 31,  3,  3,  3,  0, 63, 63,  0, 31, 63,  1,  0,  0,  0, 63, 31,  0,  1, 63, 63,  0,  0, 63, 63,  0,  7, 63, 60, 63,  7, 31, 60, 63, 15,  0, 28, 60, 54, 54, 63, 63,  0, 63, 63,  1,  0,  0, 31, 63, 54, 54, 55, 55,  2,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,128,128,128,128,128,  0,  0,192,192,192,  0,192,192,192,  0,  0,  0,  0,  0,  0,192,192,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255, 29,127,255,247,224,  0,254,254,254,  0,255,255,255,198,254,254,254,  0,  0,255,255,255,124,254,254,214,214,222,222, 92,124,254,254,214,214,222,222, 92,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };

    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

static void render_info(void) {
    // Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            if (layer_state_cmp(default_layer_state, _QWERTY)) {
                oled_write_P(PSTR("Qwerty\n"), false);
            } else if (layer_state_cmp(default_layer_state, _COLEMAK)) {
                oled_write_P(PSTR("Colmak\n"), false);
            } else if (layer_state_cmp(default_layer_state, _DVORAK)) {
                oled_write_P(PSTR("Dvorak\n"), false);
            } else if (layer_state_cmp(default_layer_state, _WORKMAN)) {
                oled_write_P(PSTR("Workman\n"), false);
            } else if (layer_state_cmp(default_layer_state, _HUNGARIAN)) {
                oled_write_P(PSTR("HUN Qwerty\n"), false);
            } else {
                oled_write_P(PSTR("Undefined\n"), false);
            }
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

void oled_task_user(void) {
    static bool finished_timer = false;
    if (!finished_timer && (timer_elapsed(startup_timer) < 1000)) {
        render_logo();
    } else {
        if (!finished_timer) {
            oled_clear();
            finished_timer = true;
        }
        render_info();
    }
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
