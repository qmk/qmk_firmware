/* Copyright 2023 Tobias Minn (0x544D)
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
    BASE,
    FN1,
    FN2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

   /* ISO 65 layout by 0x544D (ISO German keyboard layout shown)
   *
   * ,-----------------------------------------------------------------------------------------------.
   * | Esc | 1 ! | 2 " | 3 § | 4 $ | 5 % | 6 & | 7 / | 8 ( | 9 ) | 0 = | ß ? | ´ ` | Backspace | Del |
   * |-----------------------------------------------------------------------------------------------|
   * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Z  |  U  |  I  |  O  |  P  |  Ü  | + * | Enter  | PgU |
   * |----------------------------------------------------------------------------------       |-----|
   * | MO(2)   |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  Ö  |  Ä  | # ' |       | PgD |
   * |-----------------------------------------------------------------------------------------------|
   * | Shift | < > |  Y  |  X  |  C  |  V  |  B  |  N  |  M  | , ; | . : | - _ |  Shift  |  Up | Del |
   * |-----------------------------------------------------------------------------------------------|
   * | LCtl  | LGUI  | LAlt  |            Space                  |RAlt |MO(1)|RCtl | Lft | Dwn | Rgh |
   * `-----------------------------------------------------------------------------------------------'
   */
    [BASE] = LAYOUT_65_iso(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC,          KC_PGUP,
        MO(2),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  KC_BSLS, KC_ENT,  KC_PGDN,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, KC_UP,   KC_DEL,  
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, MO(1),   KC_RCTL,  KC_LEFT, KC_DOWN, KC_RGHT
    ),

   /* Funtion Layer 1: Media Controls with arrow keys / RShift (Play Pause), F keys,
   *                   RGB matrix control
   * ,-----------------------------------------------------------------------------------------------.
   * | °^  | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |   Delete  |Home |
   * |-----------------------------------------------------------------------------------------------|
   * |        |RGB_T|RGB+ |RGB- |HUE+ |HUE- |SAT+ |SAT- |BGH+ |BGH- |     |     |     |        |Home |
   * |----------------------------------------------------------------------------------       |-----|
   * |         |     |     |     |     |     |     |     |     |     |     |     |     |       | End |
   * |-----------------------------------------------------------------------------------------------|
   * |       |     |     |     |     |     |     |     |     |     |     |     |  MPlay  |Vol_U| End |
   * |-----------------------------------------------------------------------------------------------|
   * |       |       |       |                                   |     |Trans|     | MPrv|Vol_D| MNxt|
   * `-----------------------------------------------------------------------------------------------'
   */
    [FN1] = LAYOUT_65_iso(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_DEL,  KC_HOME,
        KC_NO,   RGB_TOG, RGB_MOD, RGB_RMOD,RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_NO,   KC_NO,    KC_NO,            KC_HOME,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_END,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_MPLY, KC_VOLU, KC_END,
        KC_NO,   KC_NO,   KC_NO,                              KC_NO,                     KC_NO,   KC_TRNS, KC_NO,    KC_MPRV, KC_VOLD, KC_MNXT
    ),


   /* Funtion Layer 2: Media Controls left hand, F keys, Page up/down, Home/end, Program/RESET
   * ,-----------------------------------------------------------------------------------------------.
   * | °^  | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |   Delete  |Home |
   * |-----------------------------------------------------------------------------------------------|
   * |        |     |Vol_D|Vol_U|     |     |     |     |     |     |RESET|     |     |        |Home |
   * |----------------------------------------------------------------------------------       |-----|
   * |  Trans  |MPrv |MPlay| MNxt|     |     |     |     |     |     |     |     |     |       | End |
   * |-----------------------------------------------------------------------------------------------|
   * |       |     |     |     |     |     |     |     |     |     |     |     |         |PGUP | End |
   * |-----------------------------------------------------------------------------------------------|
   * |       |       |       |                                   |     |     |     | Home|PGDN | End |
   * `-----------------------------------------------------------------------------------------------'
   */
    [FN2] = LAYOUT_65_iso(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_DEL,  KC_HOME,
        KC_NO,   KC_NO,   KC_VOLD, KC_VOLU, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   QK_BOOT, KC_NO,    KC_NO,            KC_HOME,
        KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_END,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_PGUP, KC_END,
        KC_NO,   KC_NO,   KC_NO,                              KC_NO,                     KC_NO,   KC_NO,   KC_NO,    KC_HOME, KC_PGDN, KC_END
    )

};