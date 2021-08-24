/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

enum local_layers {
    _QWERTY,
    _RGB,
    _FUNC,
};

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,-------------.
     * |   1  |  2   |
     * |------+------|
     * |   3  |  4   |
     * |------+------|
     * |   5  |  6   |
     * |------+------|
     * | FUNC | RGB  |
     * `-------------'
     */
    [_QWERTY] = LAYOUT( \
        KC_1,      KC_2, \
        KC_3,      KC_4, \
        KC_5,      KC_6, \
        MO(_FUNC), TG(_RGB) \
      ),

    /* RGB
     * ,-------------.
     * | Mode-| Mode+|
     * |------+------|
     * | HUE- | HUE+ |
     * |------+------|
     * | SAT- | SAT+ |
     * |------+------|
     * |RGBTOG|      |
     * `-------------'
     */
    [_RGB] = LAYOUT( \
        RGB_RMOD, RGB_MOD, \
        RGB_HUD,  RGB_HUI, \
        RGB_SAD,  RGB_SAI, \
        RGB_TOG,  KC_TRNS \
      ),

    /* Function
     * ,-------------.
     * |   Q  |CALDEL|
     * |------+------|
     * |   A  |TSKMGR|
     * |------+------|
     * |   Z  |  X   |
     * |------+------|
     * |      |  C   |
     * `-------------'
     */
    [_FUNC] = LAYOUT( \
        KC_Q,    CALTDEL, \
        KC_A,    TSKMGR, \
        KC_Z,    KC_X, \
        _______, RESET \
      )

};




#ifdef RGB_MATRIX_ENABLE
  led_config_t g_led_config = {
  {
    {  7,  0 },
    {  6,  1 },
    {  5,  2 },
    {  4,  3 },
  },{
    { 121,   2 }, { 121,  23 },
    { 121,  41 }, { 121,  60 },
    { 103,   2 }, { 103,  23 },
    { 103,  41 }, { 103,  60 },
  },{
    1, 1, 1, 1,
    1, 1, 1, 1,
  }
  };
#endif
