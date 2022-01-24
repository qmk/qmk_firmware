/* Copyright 2021 yfuku
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
#include QMK_KEYBOARD_H
#include <stdio.h>

enum layer_names {
    _0,
    _1,
    _2,
    _3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_0] = LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_A, KC_B, KC_C, KC_D, KC_E,
        KC_6, KC_7, KC_8, KC_9, KC_0, KC_F, KC_G, KC_H, KC_I, KC_J
    ),
    [_1] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_2] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_3] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

#ifdef OLED_ENABLE

void render_layer_state(void) {
    switch (get_highest_layer(layer_state)) {
        case _0:
            oled_write_ln_P(PSTR("Layer: Default"), false);
            break;
        case _1:
            oled_write_ln_P(PSTR("Layer: 1"), false);
            break;
        case _2:
            oled_write_ln_P(PSTR("Layer: 2"), false);
            break;
        case _3:
            oled_write_ln_P(PSTR("Layer: 3"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Layer: Undefined"), false);
    }
}

char keylog_str[24]  = {};
char keylogs_str[21] = {};
int  keylogs_str_idx = 0;

const char code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ';', '\'', ' ', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c", record->event.key.row, record->event.key.col, keycode, name);

    // update keylogs
    if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
        keylogs_str_idx = 0;
        for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
            keylogs_str[i] = ' ';
        }
    }

    keylogs_str[keylogs_str_idx] = name;
    keylogs_str_idx++;
}

const char *read_keylog(void) { return keylog_str; }
const char *read_keylogs(void) { return keylogs_str; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_layer_state();
        oled_write_ln(read_keylog(), false);
        oled_write_ln(read_keylogs(), false);
    } else {
        oled_write_ln("sandbox keyboard", false);
    }

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    return true;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

#endif
