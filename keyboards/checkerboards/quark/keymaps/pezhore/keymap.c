/* Copyright 2015-2017 Jack Humbert
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

enum ortho_4x12_layers {
  _QWERTY,
  _FN,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum ortho_4x12_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  SHRUG,  // ¯\_(ツ)_/¯
  TFLIP,  // (╯°□°)╯︵ ┻━┻
  POOP,   // 💩
  DPOINT, // (ಠ_ಠ)
  STRUT,  // ᕕ( ᐛ )ᕗ
  SARCSM, // ⸮
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |Bkpsc |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | FN   | Ctrl | GUI  | ALT  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  MO(_FN), KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* FN
 * ,-----------------------------------------------------------------------------------.
 * | `    |      |      |      |      |      |      |      |      |POOP  |PrtScr|Del   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |UC_Wnc|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |SHRUG |TFLIP | POOP |DPOINT|STRUT |      |      |      |      |SARCSM|UC_Lin|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FN] = LAYOUT_ortho_4x12(
   KC_GRV,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  POOP,     KC_PSCR,  KC_DEL,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  UC_M_WC,
  _______,    SHRUG,    TFLIP,     POOP,   DPOINT,    STRUT,  _______,  _______,  _______,  _______,   SARCSM,  UC_M_LN,
  _______,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,  _______
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |Raise | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12(
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_DEL,
  KC_DEL,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,   KC_F6,     KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE,
  _______,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,  KC_F12,    _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      | Prev |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |Lower |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_DEL,
  KC_DEL,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,
  _______,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  KC_MPRV,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_MNXT,  KC_VOLD,  KC_VOLU,  KC_MPLY
),


/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset| Debug|      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12(
  _______,  QK_BOOT,  DEBUG,    _______,  _______,  _______,  _______,  TERM_ON,  TERM_OFF, _______,  _______,  KC_DEL,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER,  _RAISE,  _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER,  _RAISE,  _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER,  _RAISE,  _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER,  _RAISE,  _ADJUST);
          }
          return false;
          break;
        case SHRUG:
          if (record->event.pressed) {
            send_unicode_string("¯\\_(ツ)_/¯");
          }
          return false;
          break;
        case TFLIP:
          if (record->event.pressed) {
            send_unicode_string("(╯°□°)╯︵ ┻━┻");
          }
          return false;
          break;
        case POOP:
          if (record->event.pressed) {
            send_unicode_string("💩");
          }
          return false;
          break;
        case DPOINT:
          if (record->event.pressed) {
            send_unicode_string("(ಠ_ಠ)");
          }
          return false;
          break;
        case STRUT:
          if (record->event.pressed) {
            send_unicode_string("ᕕ( ᐛ )ᕗ");
          }
          return false;
          break;
        case SARCSM:
          if (record->event.pressed) {
            send_unicode_string("⸮");
          }
          return false;
          break;
      }
    return true;
};