/* Copyright 2019 Kaylyn Bogle
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

enum layers {
    _BASE = 0,
    _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
        KC_F1,   KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_F2,   KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_F3,  KC_LSFT,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_F4,  KC_LCTL,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    //
    MO(_ADJUST),KC_LGUI, KC_LALT, KC_BSPC,  KC_ENT,  KC_SPC, KC_MINUS
    //└────────┴────────┴────────┴────────┴────────┴────────┴────────┘
    ),
    [_ADJUST] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
       RGB_TOG,TO(_BASE),XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  RESET,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       RGB_M_K, XXXXXXX, RGB_RMOD,RGB_HUI, RGB_MOD, XXXXXXX, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX, XXXXXXX, RGB_SAD, RGB_HUD, RGB_SAI, XXXXXXX, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼
       XXXXXXX, XXXXXXX, RGB_VAD, XXXXXXX, RGB_VAI, XXXXXXX, XXXXXXX,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼
    //
       _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    //└────────┴────────┴────────┴────────┴────────┴────────┴────────┘
    ),
};

#if defined(OLED_ENABLE)
const char* get_layer_name(uint8_t layer) {
    switch (layer) {
        case _BASE:
            return PSTR("Default");
            break;
        case _ADJUST:
            return PSTR("Adjust");
            break;
        default:
            return PSTR("Unknown");
            break;
    }
}

bool oled_task_user(void) {
    oled_write_ln_P(get_layer_name(biton32(layer_state)), false);
    return false;
}
#endif
