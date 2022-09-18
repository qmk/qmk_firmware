/* Copyright 2021 kuriatsu
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                          KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL,
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC,
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,              XXXXXXX,    KC_N,    KC_M, KC_COMM,   C_DOT, KC_SLSH,
                         KC_ESC, KC_RGUI, KC_LALT,  KC_SPC, KC_LSFT,     KC_BSPC,  KC_ENT, MO(_FN), KC_BSLS,  KC_GRV
    ),
    [_FN] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                         KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
      _______, XXXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, RGB_TOG,                       KC_PGUP, XXXXXXX,   KC_UP, XXXXXXX, KC_PSCR, XXXXXXX, XXXXXXX,
      _______, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, RGB_MOD,                       KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
      _______, XXXXXXX, XXXXXXX, XXXXXXX, RGB_VAI, RGB_HUI,              _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      _______, _______, _______, _______, _______,                        KC_DEL, _______, _______, _______, _______
    )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}


#ifdef OLED_ENABLE
static void render_scrl(void) {
    static const char PROGMEM raw_scrl[] = {
        128,192,192,224, 96, 48, 48, 48, 48, 48, 48, 48,240,240,240,240,240,112,112, 56, 56, 56, 56, 24, 28, 28, 28,124,248,248,240, 64,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,192,224,112, 56, 56, 56, 56,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        7, 15, 28, 24, 24, 24, 12, 12,  0,  0,192,254,255,255,255, 15, 32, 32, 48, 48, 16, 24, 24,  8, 12,140,156,254,255, 51,129,192,192,224,224,224,224,224,192,192,192,224,224,224,  0,  0,  0,  0,192,192,224, 96,  0,  0,  0,240,254,255,255,135,192,224,224,224,224,224,128,  0,  0,128,128,192,224, 96, 96,224,224,224,224,224, 96,  0,  0,  0,128,192,192,224,224,224,224,224, 64,  0,128,128,192,224, 96,224,224,224,224,224,224, 96,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,128,192,252,255,255,127, 15,  1, 16, 24,  8, 12, 12, 12,132,134,198,238,127, 59,131,  0, 30, 63, 63,124,248,240,240,  3,  1,193,253,255,127,  7,  0,  0,128,240,254,255, 63,  7,  0,128,224,254,255,127,  7,  1,  0,  0,192,252,255,127, 63,251,252,255,127,  7,  1,  0,128,192,252,255,255, 31,  1,128,192,192, 30, 63, 63,124,248,240,240,193,224,252,255,255,  7,  1,  0,128,192,252,255,255, 31,  1,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        96,112,112, 48, 56, 28, 14, 15,  3,  3,  5,  4,  4,  6,  6,  2,  2,  2,  3,  3,  1,  1,  1,  1,  7,  7, 15, 31, 31, 12, 12, 12,  6,  7,  3,  1,  0,  0, 31, 31, 15, 14,  6,  7,  3, 15, 31, 15, 15,  7,  7,  3, 63, 31, 31, 31, 30, 14, 14,  6,  7,  3,  3,  1,  0,  0, 15, 31, 31, 15,  6,  6,  3, 11, 31, 15, 15,  7,  7,  7, 15, 31, 31, 12, 12, 12,  6,  7,  3,  1,  0, 15, 31, 31, 15,  6,  6,  3, 11, 31, 15, 15,  7,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_scrl, sizeof(raw_scrl));
}


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return rotation;
}


bool oled_task_user(void) {
    render_scrl();
    oled_set_cursor(14, 0);
    oled_write_P(PSTR("WPM:"), false);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
    return false;
}
#endif
