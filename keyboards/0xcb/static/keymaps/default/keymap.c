/*
Copyright 2021 0xCB - Conor Burns

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
#include QMK_KEYBOARD_H
// clang-format off
enum layer_names {
  _HOME,
  _FN1,
  _FN2,
  _FN3
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_HOME] = LAYOUT(
                                                                                                       KC_MPLY,
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,             KC_ENT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT,
    KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,           MO(1),                     KC_SPC,  KC_RCTL, KC_RALT, KC_RGUI
),
[_FN1] = LAYOUT(
                                                                                                       _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,          _______,                   _______, _______, _______, _______
),
[_FN2] = LAYOUT(
                                                                                                       _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,          _______,                   _______, _______, _______, _______
),
[_FN3] = LAYOUT(
                                                                                                       _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,          _______,                   _______, _______, _______, _______
),
};
// clang-format on

/* rotary encoder (MX12) - add different functions for layers here */
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (IS_LAYER_ON(_FN3)) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (IS_LAYER_ON(_FN2)) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (IS_LAYER_ON(_FN1)) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}
#endif

/* oled stuff :) */
#ifdef OLED_DRIVER_ENABLE
uint16_t startup_timer = 0;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    startup_timer = timer_read();
    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0, 16,192,194,192, 64, 60,188, 44, 60,188, 60, 60, 56, 60, 44, 61, 60, 64,192,192,208,  1,  0,252,252,180,253, 60, 60, 44, 62,252,253,116,252, 52, 60, 44, 60,244,220,254,252,  0,  0, 16,  0,  2,  0,192,192, 65,192, 60, 60, 53, 60,192,193,192,192, 16,  0,  0,144,  4,  0,252,253,116,252, 60, 60, 44, 45,252,188,244,252, 60, 60, 60, 61,216,108,252,  0,  0, 45, 60,156, 60, 53,252,124,220,252, 53, 60, 60, 52,  0,  0,192,210, 64,192, 60, 56, 20,189, 60, 60, 52, 29, 52, 60, 60, 44,192,192, 64,192,  0, 36,  0,
        0, 16,  0, 29, 63, 55, 63,192, 64,192,192,192,192, 64,200,192,192,192,192,  3,  3,  2, 11,  0,  0, 35,  2,  3,  2,  0,  0, 10,  0,255,255,253,247,  0,  0, 16,  0,  1,  0,  3,  1,  8,  0,189,244,252,236, 19,130,  3,  1,  0, 68,  0,  0,  3,  2,131,  2,236,254,248,252,  0, 33,  3,  3,  3,  1,  0, 32,  0,  2,247,255,127,247,  0,  2,  0,  8,  1,  1,  3,  0,  0, 32,  0,  0, 64,  0,255,191,253,251,  0,129,  0,  2, 32,  0,159,255,253,247,  0, 32,  0,  0,  0,  0,  0,136,  0,  1, 32,  0,  3,  2,  3,  3,  0,  8,  1,
        1, 16,  0,192, 64,194,128,  3, 67,  3,  3,  9,  3,  3, 35,  3,  2, 83,  3,252,244,188,244,  0,  0, 32,  0,  0,  2,  0,128,  0,  0,255,255,237,191,  0, 16,  0,  0,  0,  0, 18,  0,128,  0,255,123,223,255, 60, 52, 60, 60, 52, 60,180, 60, 44, 60, 56, 60,239,255,126,255,  0,  0, 32,  4,  0,  0,  0,  0, 16,  0,255,219,255,223,  0, 16,  0,  1,  0,  0,  8,  0,  0,  2,128,  0,  8,  0,255,255,235,255,  0,  0,  0,  0, 72,  0,247,255,247,190,  0,  0,  1,  0, 16,  0,  0,  0,  0,  0, 64,  2,192,192,200,192,  0, 16,  0,
        64,  4,  1,  3,  7,  3, 11, 60, 60, 52,188, 60, 61, 60, 60, 52,188, 44, 60, 67,  2,  3,  3,128,  0, 64,  0,  0,  4,  0,  0, 16,  0, 47, 63, 62, 63,  0,  0,132,  0,  0,  0,  0,128,  8,  0,239,127, 47,127,  0,  0,  0,  2,128,  0,  0,  0, 64,  4,  0,128,127,127,107,127,  0, 16,  0,  0,  2, 64,  0,  0,  0,136, 55, 63, 61, 63,  0,  0,  0,  2,  0, 64,  0,136,  0,  0, 60, 44,189, 60, 31, 63,127, 59, 44, 52,172, 60,  0, 64,  7,  6,  7,133, 60, 44, 61, 28, 60, 56,188, 60, 57, 44, 60, 44,  3,  3,131,  2,  0, 32,  2,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}
/* Shows the name of the current layer and locks for the host (CAPS etc.) */
static void render_layer(void) {
    led_t led_state = host_keyboard_led_state();
    // clang-format off
    static const char PROGMEM logo[][3][7] = {
        {{0x97, 0x98, 0x99, 0x9A, 0}, {0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0}, {0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0}}, /* l      num      CB */
        {{0xB7, 0xB8, 0xB9, 0xBA, 0}, {0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0}, {0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0}}, /* 1      num      CB */
        {{0xD7, 0xD8, 0xD9, 0xDA, 0}, {0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0}, {0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0}}, /* 1      cap      CB */
        {{0xF7, 0xF8, 0xF9, 0xFA, 0}, {0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0}, {0xFB, 0xFC, 0xFD, 0xFE, 0xFF, 0}}, /* l      cap      CB */
        {{0xB7, 0xC0, 0xC1, 0xBA, 0}, {0xB7, 0xC2, 0xC3, 0xBA, 0},             {0xB7, 0xC4, 0xC5, 0xBA, 0}},       /* 2       3       4  */
        {{0xD7, 0xE0, 0xE1, 0xDA, 0}, {0xD7, 0xE2, 0xE3, 0xDA, 0},             {0xD7, 0xE4, 0xE5, 0xDA, 0}},       /* 2       3       4  */
    };
    // clang-format on
    oled_set_cursor(0, 0);
    oled_write_P(logo[0][0], false);
    oled_set_cursor(0, 3);
    oled_write_P(logo[3][0], false);
    switch (get_highest_layer(layer_state)) {
        case _HOME:
            oled_set_cursor(0, 1);
            oled_write_P(logo[1][0], false);
            oled_set_cursor(0, 2);
            oled_write_P(logo[2][0], false);
            break;
        case _FN1:
            oled_set_cursor(0, 1);
            oled_write_P(logo[4][0], false);
            oled_set_cursor(0, 2);
            oled_write_P(logo[5][0], false);
            break;
        case _FN2:
            oled_set_cursor(0, 1);
            oled_write_P(logo[4][1], false);
            oled_set_cursor(0, 2);
            oled_write_P(logo[5][1], false);
            break;
        case _FN3:
            oled_set_cursor(0, 1);
            oled_write_P(logo[4][2], false);
            oled_set_cursor(0, 2);
            oled_write_P(logo[5][2], false);
            break;
        default:
            oled_set_cursor(0, 1);
            oled_write_P(PSTR("    "), false);
            oled_set_cursor(0, 2);
            oled_write_P(PSTR("    "), false);
    }
    oled_set_cursor(8, 0);
    oled_write_P(led_state.num_lock ? logo[0][1] : PSTR("      "), false);
    oled_set_cursor(8, 1);
    oled_write_P(led_state.num_lock ? logo[1][1] : PSTR("      "), false);
    oled_set_cursor(8, 2);
    oled_write_P(led_state.caps_lock ? logo[2][1] : PSTR("      "), false);
    oled_set_cursor(8, 3);
    oled_write_P(led_state.caps_lock ? logo[3][1] : PSTR("      "), false);

    oled_set_cursor(16, 0);
    oled_write_P(logo[0][2], false);
    oled_set_cursor(16, 1);
    oled_write_P(logo[1][2], false);
    oled_set_cursor(16, 2);
    oled_write_P(logo[2][2], false);
    oled_set_cursor(16, 3);
    oled_write_P(logo[3][2], false);
}

void oled_task_user(void) {
    static bool finished_timer = false;
    if (!finished_timer && (timer_elapsed(startup_timer) < 3000)) {
        render_logo();
    } else {
        if (!finished_timer) {
            oled_clear();
            finished_timer = true;
        }
        render_layer();
    }
}
#endif
