/* Copyright 2019 Garret G. (TheRoyalSweatshirt)
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

enum layer_names {
    _BASE,
    _LOWER
};

#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* BASE
   *        ,-----------------------------------------------------------------------------------.
   *        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10  | F11 |  F12 |
   *        |------+------+------+------+------+-------------+------+------+------+------+------|
   *        | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |
   *        |+------+------+------+------+-----+------+------+------+------+------+------+------|
   *  RotEn | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * ,------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | PgUp | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------|
   * | Lower| Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | PgDn | Del  | Ctrl | GUI  | ALT  |Lower |SPACE |SPACE | End  | Left | Down |  Up  |Right |
   * `------------------------------------------------------------------------------------------'
   */
  	[_BASE] = LAYOUT(
              KC_F1,     KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12,
              KC_ESC,    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,      KC_0,    KC_MINUS,
    KC_NO,    KC_TAB,    KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,      KC_P,     KC_BSPC,
    KC_PGUP,  KC_LCTL,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,      KC_SCLN,  KC_QUOT,
    KC_HOME,  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,    KC_SLSH,   KC_ENT,
    KC_PGDN,  KC_DEL,    KC_RCTL, KC_LGUI,  KC_LALT,  LOWER,    KC_SPC,   KC_SPC,   KC_END,   KC_LEFT,  KC_DOWN,   KC_UP,    KC_RGHT
  ),

  /* LOWER
   *        ,-----------------------------------------------------------------------------------.
   *        |TOGRGB|      |      |      |Sat(-)|Hue(-)|Hue(+)|Sat(+)|      |      |Brght-|Brght+|
   *        |------+------+------+------+------+-------------+------+------+------+------+------|
   *        |  `   |      |      |      |      |      |      |      |      |      |      |   =  |
   *        |+------+------+------+------+-----+------+------+------+------+------+------+------|
   *  RotEn |      |      |  Up  |      |      |      |      |      |      |   [  |   ]  |   \  |
   * ,------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Home |      | Left | Down |Right |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | End  |      |      |      |      |      |      |      |      |      |      |      |PrScn |
   * `------------------------------------------------------------------------------------------'
   */
    [_LOWER] = LAYOUT(
              UG_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  UG_SATD,  UG_HUED,  UG_HUEU,  UG_SATU,  KC_TRNS,  KC_TRNS,  UG_VALD,  UG_VALU,
              KC_GRAVE, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_EQUAL,
    KC_NUM,   KC_TRNS,  KC_TRNS,  KC_UP,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_LBRC,  KC_RBRC,  KC_BSLS,
    KC_HOME,  KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_END,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_PSCR
  )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(MS_WHLL);
        } else {
            tap_code(MS_WHLR);
        }
    }
    return true;
}
