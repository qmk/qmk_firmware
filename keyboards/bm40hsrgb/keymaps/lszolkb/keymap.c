/* Copyright 2020 tominabox1
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

#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2

enum custom_keycodes {
    LAYER0 = SAFE_RANGE,
    LAYER1,
    LAYER2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* LAYER0
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Lyr2 | Ctrl | Alt  | GUI  | Lyr1 |    Space    | Lyr1 | Left | Up |  Down  |Right |
 * `-----------------------------------------------------------------------------------'
 */

[_LAYER0] = LAYOUT_planck_mit(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,  KC_U,    KC_I,    KC_O,   KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,  KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,  KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
    MO(2),   KC_LCTL, KC_LALT, KC_LGUI, MO(1),    KC_SPC,     MO(1),   KC_LEFT, KC_UP,  KC_DOWN, KC_RGHT
),

/* LAYER1
 * ,-----------------------------------------------------------------------------------.
 * | ` ~  |  1!  |  2@  |  3#  |  4$  |  5%  |  6^  |  7&  |  8*  |  9(  |  0)  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  -_  |  =+  |  [{  |  ]}  | \|   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |Pg Up |Pg Dn | Vol+ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Vol- |
 * `-----------------------------------------------------------------------------------'
 */

[_LAYER1] = LAYOUT_planck_mit(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,       KC_8,       KC_9,    KC_0,    KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS,    KC_EQL,     KC_LBRC, KC_RBRC, KC_BSLS,
    KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS,    KC_NUBS,    KC_PGUP, KC_PGDN, KC_VOLU,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_MPRV,    KC_MSTP,    KC_MPLY, KC_MNXT, KC_VOLD
),

/* LAYER2
 *                      v------------------------RGB CONTROL--------------------v
 * ,------------------------------------------------------------------------------------.
 * |Reset |      |      |      |      |      |Speed+|RGBMOD+| HUE- | SAT+ |BRGTH+|BLTog |
 * |------+------+------+------+------+------+------+-------+------+------+------+------|
 * |      |      |      |      |      |      |Speed-|RGBMOD-| HUE+ | SAT- |BRGTH-|      |
 * |------+------+------+------+------+------+------+-------+------+------+------+------|
 * |      |      |      |      |      |      |      |       |      |      |      |      |
 * |------+------+------+------+------+------+------+-------+------+------+------+------|
 * |      |      |      |      |      |             |       |      |      |      |      |
 * `------------------------------------------------------------------------------------'
 */

[_LAYER2] = LAYOUT_planck_mit(
    RESET,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   RGB_SPI, RGB_MOD,  RGB_HUI,  RGB_SAI, RGB_VAI, RGB_TOG,
    DEBUG,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   RGB_SPD, RGB_RMOD, RGB_HUD,  RGB_SAD, RGB_VAD, KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,
    KC_TRNS, KC_NO,   KC_NO,   GUI_ON,  GUI_OFF,     KC_TRNS,      KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO
)

};
