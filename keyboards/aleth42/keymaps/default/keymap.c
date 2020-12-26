/* Copyright 2020 monksoffunk
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
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 /* Default Layer
     * ,-----------------------------------------------------------.
     * | Esc|  Q |  W |  E |  R |  T |  Y |  U |  I |  O |  P | BS |
     * |-----------------------------------------------------------|
     * | Tab |  A |  S |  D |  F |  G |  H |  J |  K |  L | Ent    |
     * |-----------------------------------------------------------|
     * | LSft   |  Z |  X |  C |  V |  B |  N |  M |  , |  . |fn(/)|
     * |-----------------------------------------------------------|
     * | LCtl | LAlt| LGui|  spc fn0  |  spc fn1    |RGui|RAlt|RCtl|
     * `-----------------------------------------------------------'
 */
    [_QWERTY] = LAYOUT(
        KC_ESC,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,   KC_BSPC,
        KC_TAB,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_ENT,
        KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  LT(_ADJUST, KC_SLSH),
        KC_LCTL, KC_LALT   , KC_LGUI, LT(_LOWER, KC_SPC),   LT(_RAISE, KC_SPC), KC_RGUI, KC_RALT, KC_RCTL
        ),

 /* Lower Layer
     * ,-----------------------------------------------------------.
     * |  ~ |  ! |  @ |  # |  $ |  % |  ^ |  & |  * |  ( |  ) | Del|
     * |-----------------------------------------------------------|
     * |        |    |    |    |    |     | _ | + | { | } |  Pipe  |
     * |-----------------------------------------------------------|
     * |          |    |    |    |    |    |   | ;  | '  | Up |    |
     * |-----------------------------------------------------------|
     * |     |    |     |           |             |Left|Down|Right |
     * `-----------------------------------------------------------'
     */
    [_LOWER] = LAYOUT(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
		_______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
		_______, _______, _______, _______, _______, _______, _______, KC_SCLN, KC_QUOT, KC_UP,   _______,
		_______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT
		),

	/* Raise Layer
     * ,-----------------------------------------------------------.
     * |  ` |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 | Del|
     * |-----------------------------------------------------------|
     * |  F1   | F2  | F3 | F4 | F5 |  F6 | - | = | [ | ] |  Pipe  |
     * |-----------------------------------------------------------|
     * |    F7    | F8 | F9 | F10| F11| F12|  \ |  \ |   |    |    |
     * |-----------------------------------------------------------|
     * |     |    |     |           |             |     |    |     |
     * `-----------------------------------------------------------'
     */
    [_RAISE] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
		KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
		KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______
		),

	/* Adjust Layer
     * ,-----------------------------------------------------------.
     * |Mute| F1 | F2 | F3 | F4 | F5 | F6 | F7 | F8 | F9 | F10|F11 |
     * |-----------------------------------------------------------|
     * |       |BTOG |BSTP|BINC| MAC|RGBTOG|HUI|WIN|SAI|VAI|  F12  |
     * |-----------------------------------------------------------|
     * |   Caps   |Reset|BBRE|BDEC|    |RMOD|HUD |   |SAD|VAD |    |
     * |-----------------------------------------------------------|
     * |SLEEP|    |     |           |             |     |    |     |
     * `-----------------------------------------------------------'
      */
    [_ADJUST] = LAYOUT(
        KC_MUTE, KC_F1,   KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
		_______, BL_TOGG, BL_STEP, BL_INC,  AG_NORM,  RGB_TOG, RGB_HUI, AG_SWAP, RGB_SAI, RGB_VAI,  KC_F12,
		KC_CAPS, RESET,   BL_BRTG, BL_DEC,  _______,  RGB_MOD, RGB_HUD, _______, RGB_SAD, RGB_VAD,  _______,
		KC_SLEP, _______, _______, _______, _______, _______, _______, _______
		),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Left encoder */
        switch (get_highest_layer(layer_state)) {
            case _QWERTY:
                if (clockwise) {
                    tap_code(KC_TAB);
                } else {
                    tap_code16(S(KC_TAB));
                }
                break;
            case _RAISE:
                if (clockwise) {
                //    tap_code(KC_VOLU);
                    if(keymap_config.swap_lalt_lgui==false){
                        tap_code(KC_LANG2);
                    }else {
                        tap_code16(A(KC_GRV));
                    }
                } else {
                    if(keymap_config.swap_lalt_lgui==false){
                    tap_code(KC_LANG1);
                    } else {
                        tap_code16(A(KC_GRV));
                    }
                }
                break;
            case _ADJUST:
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
            }
        }

    } else if (index == 1) { /* Right encoder */
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}
