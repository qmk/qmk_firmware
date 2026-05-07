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
    _LOWER,
    _RAISE,
    _ADJUST,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 *
 * ,----------------------------------------------------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | BkSp |
 * |------+------+------+------+------|------+------+------+------+------|------|
 * |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Enter|
 * |------+------+------+------+------|------+------+------+------+------|------|
 * |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
 * `-------------+------+------+------|------+------+------+------+------+------'
 *               | GUI  | LOWER|Ctrl/Esc|Space| RAISE| Alt | Tab  |
 *               `------------------------------------------------'
 */
[_QWERTY] = LAYOUT(
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT,
                    KC_LGUI, LOWER, MT(MOD_LCTL, KC_ESC),  KC_SPC, RAISE, KC_LALT, KC_TAB
),

/* Raise
 *
 * ,----------------------------------------------------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------|------+------+------+------+------|------|
 * |  Tab |   _  |   +  |  |   |  ~   |   :  |   "  |   >  |   {  |   }  |      |
 * |------+------+------+------+------|------+------+------+------+------|------|
 * |  Caps|   -  |   =  |  \   |  `   |   ;  |   '  |   <  |   [  |   ]  |      |
 * `-------------+------+------+------|------+------+------+------+------+------'
 *               |      |      |      |      |      |      |      |
 *               `------------------------------------------------'
 */
[_RAISE] = LAYOUT( 
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  KC_TAB,  KC_UNDS, KC_PLUS, KC_PIPE, KC_TILD, KC_COLN, KC_DQUO, KC_GT,   KC_LCBR, KC_RCBR, _______,
  KC_CAPS, KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,  KC_SCLN, KC_QUOT, KC_LT,   KC_LBRC, KC_RBRC, _______,
                    _______, _______, _______, _______, _______,  _______, _______
),

/* Lower
 *
 * ,----------------------------------------------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------|------+------+------+------+------|------|
 * |  Tab |      |      |      |Enter | Left | Down |  Up  | Right| Enter|      |
 * |------+------+------+------+------|------+------+------+------+------|------|
 * |  Ctrl|      |  GUI |  Alt | Del  | BkSp | PgUp | PgDn |      |      |      |
 * `-------------+------+------+------|------+------+------+------+------+------'
 *               |      |      |      |      |      |      |      |
 *               `------------------------------------------------'
 */
[_LOWER] = LAYOUT(
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  KC_TAB,  _______, _______, _______, KC_ENT,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,  _______,
  KC_LCTL, _______, KC_LGUI, KC_LALT, KC_DEL,  KC_BSPC, KC_PGUP, KC_PGDN, _______, _______, _______,
                    _______, _______, _______, _______, _______, _______, _______
),


/* Adjust (Lower + Raise)
 *
 * ,----------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |   F6 |  F7  |  F8  |  F9  |  F10 |      |
 * |------+------+------+------+------|------+------+------+------+------|------|
 * |  F11 |  F12 |      |RGBSAI|RGBSAD|RGBVAI|RGBVAD|      |      |      |      |
 * |------+------+------+------+------|------+------+------+------+------|------|
 * | Reset|RGBTOG|RGBMOD|RGBHUI|RGBHUD| Prev | Next | Vol- | Vol+ | Play |      |
 * `-------------+------+------+------|------+------+------+------+------+------'
 *               |      |      |      |      |      |      |      |
 *               `------------------------------------------------'
 */
[_ADJUST] =  LAYOUT(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
  KC_F11,  KC_F12,  UG_PREV, UG_SATU, UG_SATD,  UG_VALU, UG_VALD, _______, _______, _______, _______,
  QK_BOOT, UG_TOGG, UG_NEXT, UG_HUEU, UG_HUED,  KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, _______,
                    _______, _______, _______,  _______, _______,  _______, _______
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
  }
  return true;
}
