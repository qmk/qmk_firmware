/* Copyright 2020 eswai
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
    _LOWER,
    _RAISE,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    KC_TAB        ,KC_Y   ,KC_R   ,KC_O    ,KC_U   ,KC_COMM, KC_NO    , KC_NO   ,KC_DOT ,KC_BSPC,KC_L   ,KC_F   ,KC_P    ,KC_QUOT , \
    CTL_T(KC_ESC) ,KC_D   ,KC_S   ,KC_A    ,KC_I   ,KC_G   , KC_NO    , KC_NO   ,KC_J   ,KC_E   ,KC_H   ,KC_T   ,KC_K    ,KC_SCLN , \
    KC_LSFT       ,KC_V   ,KC_Z   ,KC_X    ,KC_M   ,KC_C   , KC_NO    , KC_NO   ,KC_N   ,KC_W   ,KC_B   ,KC_Q   ,KC_SLSH ,KC_UP   , \
    KC_LCTL       ,KC_LWIN,KC_LALT,KC_LCTL,MO(_LOWER),LSFT_T(KC_SPC)  ,LSFT_T(KC_ENT)   ,MO(_RAISE),KC_RSFT,KC_LEFT,KC_DOWN ,KC_RGHT
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  oled_task_user();
  return true;
}

void matrix_init_user() {
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
      0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf, 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0x0
    };
    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_logo();
    } else {
        render_logo();  // Renders a static logo
        // oled_scroll_left();  // Turns on scrolling
    }
    return false;
}
#endif