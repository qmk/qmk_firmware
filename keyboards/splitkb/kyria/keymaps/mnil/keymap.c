/* Copyright 2022 Mats Nilsson
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

#include "mnil.h"

layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, _SYMBOLS, _NAVIGATION, _NUMPAD); }

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [_COLEMAK] = LAYOUT(
        _______,  KC_Q  ,  KC_W  ,  KC_F  ,  KC_P  ,  KC_B  ,                                            KC_J,  KC_L  ,  KC_U ,   KC_Y ,TD(OAA), _______,
        _______, TD(AAE),  KC_R  ,  KC_S  ,  KC_T  ,  KC_G  ,                                            KC_M,  KC_N  ,  KC_E ,   KC_I ,  KC_O , _______,
        _______,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_D  ,  KC_V  , KC_ESC , _______,     _______,_______ ,    KC_K,  KC_H  ,KC_COMM, KC_DOT ,SE_MINS, _______,
                                   _______, KC_LGUI, SFT_TAB,_NAV_SPC, KC_LCTL,     KC_LSFT,_SYM_ENT,CTL_BSPC,ALT_DEL , _______
    ),
    [_SYMBOLS] = LAYOUT(   
        _______, KC_NO,   SE_PIPE, SE_LBRC, SE_RBRC, KC_NO  ,                                         S(KC_5), SE_QUES, SE_AT,   SE_EQL,  SE_DLR,  _______,
        _______, SE_LCBR, SE_RCBR, SE_LPRN, SE_RPRN, KC_NO  ,                                         SE_PLUS, S(KC_1), S(KC_2), S(KC_3), SE_AMPR, _______,
        _______, M_TILD,  M_CIRC,  SE_LABK, SE_RABK, KC_NO  , KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, SE_QUOT, SE_SLSH, SE_BSLS, SE_ASTR, M_BTCK,  _______,
                                   _______, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, _______
    ),
    [_NAVIGATION] = LAYOUT(
        _______, KC_NO,   CUT,     COPY,    PASTE,   AUTOFILL,                                        KC_WH_L, KC_HOME, KC_WH_D, KC_WH_U, KC_END,  _______,
        _______, KC_ACL0, KC_ACL1, KC_BTN2, KC_BTN1, KC_LCTL,                                         KC_WH_R, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______,
        _______, KC_ACL2, KC_BTN4, KC_BTN3, KC_BTN5, KC_NO,   KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
                                   _______, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, _______
    ),
    [_NUMPAD] = LAYOUT(
        _______, QUIT,    WIN,     MVWSL  , MVWSR,   CRYWS,                                           TERM,    KC_7,    KC_8,    KC_9,    KC_COMM, _______,
        _______, CS_TAB,  C_TAB,   PRVWS,   NXTWS,   I3MOD,                                           OPEN,    KC_4,    KC_5,    KC_6,    KC_0,    _______,
        _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, MOVWS,   KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, BROWSER, KC_1,    KC_2,    KC_3,    KC_DOT,  _______,
                                   _______, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, _______
    )
    // clang-format on
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_WH_U);
        } else {
            tap_code(KC_WH_D);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_WH_R);
        } else {
            tap_code(KC_WH_L);
        }
    }
    return false;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Mats Nilsson\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state)) {
            case _COLEMAK:
                oled_write_P(PSTR("Colemak\n"), false);
                break;
            case _QWERTY:
                oled_write_P(PSTR("Qwerty\n"), false);
                break;
            case _SYMBOLS:
                oled_write_P(PSTR("Symbols\n"), false);
                break;
            case _NAVIGATION:
                oled_write_P(PSTR("Navigation\n"), false);
                break;
            case _NUMPAD:
                oled_write_P(PSTR("Numpad\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
                break;
        }
    } else {
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
            0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
    return false;
}
