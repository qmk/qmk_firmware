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
        0, 0, 0, 192, 192, 192, 192, 60,  60, 60,  60,  60,  60,  60, 60, 60, 60, 60, 60, 192, 192, 192, 192, 0,   0, 252, 252, 252, 252, 60, 60, 60, 60, 252, 252, 252, 252, 60,  60,  60, 60, 252, 252, 252, 252, 0, 0, 0, 0, 0,  0,  192, 192, 192, 192, 60,  60, 60, 60, 192, 192, 192, 192, 0,   0,   0,   0, 0, 0, 252, 252, 252, 252, 60, 60, 60, 60, 252, 252, 252, 252, 60, 60, 60, 60, 252, 252, 252, 252, 0,   0,   60,  60, 60, 60, 252, 252, 252, 252, 60, 60, 60, 60, 0, 0,   192, 192, 192, 192, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60,  60,  60,  192, 192, 192, 192, 0, 0, 0, 0, 0, 0, 63, 63,  63,  63,  192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 3,  3,   3,   3,   0,   0,  3,  3,  3,  3,  0,  0,  0,  0,  255, 255, 255, 255, 0,   0, 0, 0, 3, 3,
        3, 3, 0, 0,   252, 252, 252, 252, 3,  3,   3,   3,   0,   0,  0,  0,  3,  3,  3,  3,   252, 252, 252, 252, 0, 0,   3,   3,   3,   3,  0,  0,  0,  0,   255, 255, 255, 255, 0,   0,  0,  0,   3,   3,   3,   3, 0, 0, 0, 0,  0,  0,   255, 255, 255, 255, 0,  0,  0,  0,   0,   0,   255, 255, 255, 255, 0, 0, 0, 0,   0,   0,   0,   0,  0,  0,  0,  0,   3,   3,   3,   3,  0,  0,  0,  0,   0,   0,   192, 192, 192, 192, 3,  3,  3,  3,   3,   3,   3,   3,  3,  3,  3,  3, 252, 252, 252, 252, 0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  255, 255, 255, 255, 0,   0,   0,   0, 0, 0, 0, 0, 0, 0,  255, 255, 255, 255, 60,  60,  60,  60,  60,  60,  60,  60,  60,  60,  60,  60, 255, 255, 255, 255, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   255, 255, 255, 255, 0, 0, 0, 0, 0,
        0, 0, 0, 0,   0,   0,   0,   0,   0,  255, 255, 255, 255, 0,  0,  0,  0,  0,  0,  255, 255, 255, 255, 0,   0, 0,   0,   0,   0,   0,  0,  0,  0,  0,   0,   192, 192, 192, 192, 0,  0,  0,   0,   0,   0,   3, 3, 3, 3, 60, 60, 60,  60,  60,  60,  60,  60, 60, 60, 60,  60,  3,   3,   3,   3,   0,   0, 0, 0, 0,   0,   0,   0,   0,  0,  63, 63, 63,  63,  0,   0,   0,  0,  0,  0,  0,   0,   0,   0,   63,  63,  63,  63, 0,  0,  0,   0,   0,   0,   0,  0,  0,  0,  0, 0,   63,  63,  63,  63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   63,  63,  63,  63,  0,   0,   0, 0, 0, 0, 0, 0, 0,  0,   60,  60,  60,  60,  63,  63,  63,  63,  60,  60,  60,  60,  0,   0,   3,  3,   3,   3,   60,  60, 60, 60, 60, 60, 60, 60, 60, 60, 60,  60,  3,   3,   3,   3, 0, 0, 0,
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
