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
  _FN2,
  _FN3,
  _FN4
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_HOME] = LAYOUT(
                                                                                                       KC_MPLY,
    KC_GESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,             KC_ENT,
    KC_LSPO,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSPC,
    KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,           KC_SPC,                    KC_SPC,  KC_RALT, MO(1),   MO(2)
),
[_FN2] = LAYOUT(
                                                                                                       RESET,
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,           _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,          _______,                   _______, _______, _______, _______
),
[_FN3] = LAYOUT(
                                                                                                       EEP_RST,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, KC_BSLS,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_SCLN, KC_QUOT,          _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_SLSH,
    _______, _______, _______, _______,          _______,                   _______, _______, _______, _______
),
[_FN4] = LAYOUT(
                                                                                                       _______,
    _______, _______, _______, _______, _______, _______, _______, KC_INS,  KC_HOME, KC_DEL,  KC_END,  _______,
    _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_UP,   KC_PGDN,          _______,
    _______,          _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,
    _______, _______, _______, _______,          _______,                   _______, _______, _______, _______
),
};
// clang-format on

/*layer switcher */
uint32_t layer_state_set_user(uint32_t state) {
state = update_tri_layer_state(state, _FN2, _FN3, _FN4);
return state;
}
/* rotary encoder (MX12) - add different functions for layers here */
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (IS_LAYER_ON(_FN4)) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (IS_LAYER_ON(_FN3)) {
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
        0,132, 16,208,210,192, 64, 60,188, 44, 60,188,188, 44, 56, 60, 44, 61, 60, 64,210,200,208,  1,  0,253,108,180,253, 60, 60,108, 62,252,253,116,188, 36, 60, 41, 60,244,220,126,252,  0, 34, 16,  0, 18,128,208,196, 73,192, 56, 60, 53, 60,192,203,208,210, 16,  4,  0,146,  4,  0,220,237,116,252, 60,188, 41, 45,248,188,244,254, 56, 60, 60, 41,216,108,252,160,  8,161, 60,148, 60, 53,252,106,220,252, 53, 28,124, 54,  0, 20,192, 82, 68,194, 44, 56, 20,189, 61, 60, 52, 31, 52, 62, 60, 44, 64,197, 64,210,  0, 36,  0,
        0, 16, 64, 29, 63,183, 63,192, 84,192,202,192,128, 64,201,192,193,196,192,  3, 19, 66, 11, 64,  8,147, 34,131, 66,  9,144, 10,  1,255,246,189,247,  1, 16,  2,160,  7, 66, 35,  1,  8,  0,189,244,220,236, 19,130, 11, 65,  0, 13, 68,  0, 11, 34,131,  2,236,254,248,252,  0, 33,131, 10,147, 65,  0, 36,  0,  2,247,191,127,247,128, 18, 96,  8,133, 17, 83,130,  8, 33,  4,  0, 82,  0,253,191,237,235,128,137, 32,  3, 32,  0,159,253,253,247,  0, 32,  3,  0, 44,  0,  0,137, 64,  2, 40,  0, 19, 66, 11, 17, 32, 10,  1,
        1, 16,  2,192, 72,202,144,  3, 67, 19,131, 41,  3,147, 35,  3,130, 19,131,188,228,188,244, 16, 66,  8, 80,  0,  2, 84,128,  8,  1,239,255,237,191,  0, 16,  2, 32,  0, 72,  2, 16,129, 16,255,123,223,251, 60, 52, 60, 60,180, 60,181, 60, 44,188, 56, 60,239,255,110,255,132,  0, 36,  0,  2,132, 32,  1, 18,128,190,219,255,219,  0, 17,  4,129, 32,  4,136,  0, 32,  5,160, 10, 40,  0,255,255,235,127,128,  0, 73,  1, 72,  0,247,191,247,190,  0,  0,133,  0, 16,130,  9,  0, 36,  0, 64,  2,200, 81,200,194,  0, 18,  0,
        64,  4, 17, 67, 39, 67, 11, 60,124, 20,188, 44, 53,188, 44,180,188, 44, 60, 67,  2, 51,  3,168,  2, 81,  2,128, 10, 64,  4,144,  0, 47,189, 62,183,  0, 32,197, 64,  8,  2, 36,128,  8,  0,239,123, 47,126,  1,160,  8,130,176,  4, 18,  2, 84,  4, 17,128,119, 21,107,127,  0, 16,  1,  0, 42, 64,  0, 17,  0,136, 55, 62, 29, 55,  0,138, 64,  2, 20, 64,  8,138,  0,  0, 52, 76,189, 56, 31, 61,111, 27, 44, 52,141, 61,  0, 64, 39,  2, 31,133, 52, 45, 61,156, 60, 56,188, 61, 89, 44,120, 44,  3, 43,131, 10, 32, 33,  6,
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
        case _FN2:
            oled_set_cursor(0, 1);
            oled_write_P(logo[4][0], false);
            oled_set_cursor(0, 2);
            oled_write_P(logo[5][0], false);
            break;
        case _FN3:
            oled_set_cursor(0, 1);
            oled_write_P(logo[4][1], false);
            oled_set_cursor(0, 2);
            oled_write_P(logo[5][1], false);
            break;
        case _FN4:
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

/* Resets via on eep reset - thank you drashna! */
void eeconfig_init_kb(void) {
#if defined(VIA_ENABLE)
    via_eeprom_set_valid(false);
    via_init();
#endif
    eeconfig_init_user();
}
