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

#define L_QWERTY 0
#define L_LOWER 1 << _LOWER
#define L_RAISE 1 << _RAISE
#define L_ADJUST 1 << _ADJUST

/* #define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 /* Default Layer
     * ,-----------------------------------------------------------.
     * | Esc|  Q |  W |  E |  R |  T |  Y |  U |  I |  O |  P | BS |
     * |-----------------------------------------------------------|
     * | Tab |  A |  S |  D |  F |  G |  H |  J |  K |  L | Ent    |
     * |-----------------------------------------------------------|
     * | LSft   |  Z |  X |  C |  V |  B |  N |  M |  ,  |  . | /? |
     * |-----------------------------------------------------------|
     * | LCtl | LGui| LAlt|  spc fn0  |  spc fn1    |fn2|RAlt|RCtl |
     * `-----------------------------------------------------------'
 */
    [_QWERTY] = LAYOUT( \
        KC_ESC,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,   KC_BSPC,\
        KC_TAB,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_ENT,\
        KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,\
        KC_LCTL, KC_LGUI, KC_LALT   , LT(_LOWER, KC_SPC),   LT(_RAISE, KC_SPC),LT(_ADJUST, KC_LGUI), KC_RALT, KC_RCTL \
        ),

 /* Lower Layer
     * ,-----------------------------------------------------------.
     * |  ~ |  ! |  @ |  # |  $ |  % |  ^ |  & |  * |  ( |  ) | Del|
     * |-----------------------------------------------------------|
     * |   F1   | F2 | F3 | F4 | F5 |  F6 | _ | + | [ | ] |  Pipe  |
     * |-----------------------------------------------------------|
     * |    F7    | F8 | F9 | F10| F11| F12|   |    |    | Up |    |
     * |-----------------------------------------------------------|
     * |     |    |     |           |             |Left|Down|Right |
     * `-----------------------------------------------------------'
     */
    [_LOWER] = LAYOUT( \
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, \
		KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
		KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS),_______, KC_UP, _______, \
		_______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT \
		),

	/* Raise Layer
     * ,-----------------------------------------------------------.
     * |  ` |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 | Del|
     * |-----------------------------------------------------------|
     * |  F1   | F2s | F3 | F4 | F5 |  F6 | _ | + | [ | ] |  Pipe  |
     * |-----------------------------------------------------------|
     * |    F7    | F8 | F9 | F10| F11| F12| End|PgDn| ↓ |    |    |
     * |-----------------------------------------------------------|
     * |     |    |     |           |             |     |    |     |
     * `-----------------------------------------------------------'
     */
    [_RAISE] = LAYOUT( \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
		KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
		KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, _______, _______, KC_DEL, \
		_______, KC_TRNS, _______, KC_TRNS, KC_TRNS, _______, _______, RGB_TOG \
		),

	/* Adjust Layer
     * ,-----------------------------------------------------------.
     * |   |    |    |    |Reset|    |    |    |    |    |    |    |
     * |-----------------------------------------------------------|
     * |       |     |    |    | MAC|      |   |WIN|   |   |       |
     * |-----------------------------------------------------------|
     * |   Caps   |    |    |    |     |    |    |   |   |    |    |
     * |-----------------------------------------------------------|
     * |     |    |     |           |             |     |    |     |
     * `-----------------------------------------------------------'
      */
    [_ADJUST] = LAYOUT( \
        _______, _______,   _______, _______, RESET, _______, _______, _______, _______, _______, _______, KC_DEL, \
		_______, _______, _______, _______, AG_NORM,  _______, _______, AG_SWAP, _______, _______,  _______,  \
		KC_CAPS, _______, _______, RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD, \
		KC_SYSTEM_SLEEP, _______, _______, _______, _______, _______, _______, _______ \
		),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case QMKBEST:
        //     if (record->event.pressed) {
        //         // when keycode QMKBEST is pressed
        //         SEND_STRING("QMK is the best thing ever!");
        //     } else {
        //         // when keycode QMKBEST is released
        //     }
        //     break;
        // case QMKURL:
        //     if (record->event.pressed) {
        //         // when keycode QMKURL is pressed
        //         SEND_STRING("https://qmk.fm/\n");
        //     } else {
        //         // when keycode QMKURL is released
        //     }
        //     break;
    }
    return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Upper encoder */
        switch (layer_state) {
            case L_QWERTY:
                if (clockwise) {
                    tap_code(KC_TAB);
                } else {
                    register_code(KC_LSFT);
                    tap_code(KC_TAB);
                    unregister_code(KC_LSFT);
                }
            break;
            case L_RAISE:
                if (clockwise) {
                //    tap_code(KC_VOLU);
                    if(keymap_config.swap_lalt_lgui==false){
                        tap_code(KC_LANG2);
                    }else {
                        SEND_STRING(SS_LALT("`"));
                    }
                } else {
                    if(keymap_config.swap_lalt_lgui==false){
                    tap_code(KC_LANG1);
                    } else {
                        SEND_STRING(SS_LALT("`"));
                    }
                }
            break;
            case L_ADJUST:
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
            }
        }

    } else if (index == 1) { /* Lower encoder */
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}

/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
