/* Copyright 2019 ENDO Katsuhiro <ka2hiro@kagizaraya.jp>
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

// Defines the keycodes used by our macros in process_record_user
enum layer_names {
    _QWERTY,
    _HAPPY,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  HAPPY,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 *
 *           ,------------------------------------------------.       ,------------------------------------------------.
 *           |  Esc |   1  |   2  |   3  |   4  |   5  |   -  |       |   =  |   6  |   7  |   8  |   9  |   0  |   \  |
 *           |------+------+------+------+------+------+------|       |------+------+------+------+------+------+------|
 *           |  Tab |   Q  |   W  |   E  |   R  |   T  |   [  |       |   ]  |   Y  |   U  |   I  |   O  |   P  | BkSp |
 *           |------+------+------+------+------+------+------|       |------+------+------+------+------+------+------|
 *           | Ctrl |   A  |   S  |   D  |   F  |   G  |   `  |       |   '  |   H  |   J  |   K  |   L  |   ;  |Enter |
 *           |------+------+------+------+------+------+------|       |------+------+------+------+------+------+------+------.
 *           |Shift |   Z  |   X  |   C  |   V  |   B  | Caps |       |  Del |   N  |   M  |   ,  |   .  |   /  |Shift | Fn   |
 *           `--------------------+------+------+------+------|       |------+------+------+------+------+------+------+------'
 *                                | LAlt | LGUI |  Fn  | Space|        |Space |  Fn | LGUI | LAlt |
 *                                `---------------------------'       `---------------------------'
 */
[_QWERTY] = LAYOUT(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS,      KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,      KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_GRV,       KC_QUOT, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_CAPS,      KC_DEL,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,  MO(_HAPPY),
                             KC_LALT, KC_LGUI, MO(_HAPPY), KC_SPC,    KC_SPC,  MO(_HAPPY), KC_RGUI, KC_RALT
),

/* Happy
 *
 *           ,------------------------------------------------.       ,------------------------------------------------.
 *           |  Pwr |  F1  |  F2  |  F3  |  F4  |  F5  |      |       |      |  F6  |  F7  |  F8  |  F9  |  F0  |  Del |
 *           |------+------+------+------+------+------+------|       |------+------+------+------+------+------+------|
 *           | Caps |  F11 |  F12 |BLTOGG|      |BL INC|BL DEC|       |      |      | Psc  | Slk  | Pus  | Up   |  Ins |
 *           |------+------+------+------+------+------+------|       |------+------+------+------+------+------+------|
 *           |      | Vol- | Vol+ | Mute |RGBHUI|RGBSAI|RGBVAI|       |   *  |   /  | Home | PgUp | Left | Right|      |
 *           |------+------+------+------+------+------+------|       +------+------+------+------+------+------+------+------.
 *           |      |RGBTOG|RGBMOD|RGBRMD|RGBHUD|RGBSAD|RGBVAD|       |   +  |   -  | End  | PgDn | Down |      |      |      |
 *           `--------------------+------+------+------+------|       |------+------+------+------+------+------+------+------'
 *                                |      |      |      |      |       |      |      |      |      |
 *                                `---------------------------'       `---------------------------'
 */
[_HAPPY] = LAYOUT(
  KC_PWR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,      _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
  KC_CAPS, KC_F10,  KC_F12,  BL_TOGG, _______, BL_INC , BL_DEC ,      _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, KC_UP,   KC_INS,
  _______, KC_VOLD, KC_VOLU, KC_MUTE, RGB_HUI, RGB_SAI, RGB_VAI,      KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, _______,
  _______, RGB_TOG, RGB_MOD, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD,      KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN,  _______, _______, _______,
                             _______, _______, _______, _______,      _______, _______, _______, _______
)

};

