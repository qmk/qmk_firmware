/*
Copyright 2022 Matt F

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum layer {
  _QWERTY,
  _QWERTYX,
  _FUNCTION,
  _EXTRA,
};


#define QWERTY    DF(_QWERTY)
#define QWERTYX   DF(_QWERTYX)
#define FN        MO(_FUNCTION)
#define BACKFN    LT(_FUNCTION, KC_BSPC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(
        KC_ESC,  KC_GRV,  KC_1,    KC_2,   KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,  KC_BSPC,  \
                 KC_TAB,  KC_Q,    KC_W,   KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_DEL,            \
                 KC_CAPS, KC_A,    KC_S,   KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                      \
                 KC_LSFT, KC_Z,    KC_X,   KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   FN,        \
        KC_LCTL, KC_LGUI, KC_LALT,                  FN,      KC_SPC,  KC_SPC,                    KC_RALT, KC_RCTL, KC_LGUI, KC_LEFT, KC_DOWN, KC_RGHT    \
        ),

/* Default
 *  .-----------------------------------------------------------------------------------------------------------------------------------------------+
 *  | ESC    | ~      | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      |  0     | -      | +      | Backspc| Back   |
 *  |        | `      |        |        |        |        |        |        |        |        |        |        | _      | =      |        |        |  
 *  +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 *       |    TAB     | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      | ]      |  DELETE     |
 *       |            |        |        |        |        |        |        |        |        |        |        | {      | }      |             |  
 *    +---------------+--------+--------+--------+--------+------- +--------+--------+--------+--------+--------+--------|--------+-------------+
 *    | CAPS LOCK     | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      |  ENTER            |
 *    |               |        |        |        |        |        |        |        |        |        | :      | "      |                   |  
 *  +-----------------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------+-------+-----------+-----+
 * |  SHIFT           | Z      | X      | C      | V      | B      | N      | M      | <      | >      | /      | RSHIFT         |  UP    |  Fn    |
 * |                  |        |        |        |        |        |        |        | ,      | .      | ?      |                |        |        |
 * |----------+----------+----------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+
 * | LCTRL    | LGUI     | LALT     |          Fn       |   SPACE     |         Space        | RALT   | RCTRL  | GUI    | LEFT   | DOWN   | RIGHT  |
 * |          |          |          |                   |             |                      |        |        |        |        |        |        |  
 * '--------------------------------------------------------------------------------------------------------------------------------------+--------+
 */



	[_QWERTYX] = LAYOUT(
		KC_ESC,  KC_GRV,  KC_1,    KC_2,   KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,  \
		         KC_TAB,  KC_Q,    KC_W,   KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_DEL,           \
		         BACKFN,  KC_A,    KC_S,   KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                     \
		         SC_LSPO, KC_Z,    KC_X,   KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC,          KC_UP,   FN, \
		KC_LCTL, KC_LGUI, KC_LALT,                  FN,      KC_SPC,  KC_SPC,                    KC_RALT, KC_RCTL, KC_LGUI, KC_LEFT, KC_DOWN, KC_RGHT   \
		),

/* Default
 *  .-----------------------------------------------------------------------------------------------------------------------------------------------+
 *  | ESC    | ~      | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      |  0     | -      | +      | Backspc| Back   |
 *  |        | `      |        |        |        |        |        |        |        |        |        |        | _      | =      |        |        |  
 *  +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 *       |    TAB     | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      | ]      |  DELETE     |
 *       |            |        |        |        |        |        |        |        |        |        |        | {      | }      |             |  
 *    +---------------+--------+--------+--------+--------+------- +--------+--------+--------+--------+--------+--------|--------+-------------+
 *    | BACKSPACE (FN)| A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      |  ENTER            |
 *    |               |        |        |        |        |        |        |        |        |        | :      | "      |                   |  
 *  +-----------------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------+-------+-----------+-----+
 * |  CADET SHIFT (   | Z      | X      | C      | V      | B      | N      | M      | <      | >      | /      | CADET SHIFT  ) |  UP    |  Fn    |
 * |                  |        |        |        |        |        |        |        | ,      | .      | ?      |                |        |        |
 * |----------+----------+----------+--------------------------------------------------------+--------+--------+--------+--------+--------|--------+
 * | LCTRL    | LGUI     | LALT     |          Fn       |   SPACE     |        Space         | RALT   | GUI    | RCTRL  | LEFT   | DOWN   | RIGHT  |
 * |          |          |          |                   |             |                      |        |        |        |        |        |        |  
 * '--------------------------------------------------------------------------------------------------------------------------------------+--------+
*/


    [_FUNCTION] = LAYOUT(
        QK_BOOT,   QWERTYX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  QK_BOOT,   \
                 QWERTY,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,  KC_TRNS, KC_PSCR, KC_TRNS, KC_TRNS, KC_DEL,           \
                 _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_TRNS, KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS, RGB_TOG,                   \
                 KC_TRNS, RGB_M_R, RGB_M_X, RGB_M_SW,RGB_M_K, RGB_M_B, RGB_M_G, KC_MUTE, KC_VOLD, KC_VOLU, KC_BSLS, KC_CAPS,          KC_PGUP, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_ENT,  KC_PDOT,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END   \
        ), 

/* Fn
 *  .-----------------------------------------------------------------------------------------------------------------------------------------------+
 *  |        |QWERTYEX| F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     |  F10   | F11    | F12    | DELETE | RESET  |
 *  |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |  
 *  +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 *       |  QWERTY    | HOME   | UP     | END    | PGUP   |        |        |        | INS    |        | Print  |        |        |  DELETE     |
 *       |            |        |        |        |        |        |        |        |        |        | Screen |        |        |             |  
 *    +---------------+--------+--------+--------+--------+------- +--------+--------+--------+--------+--------+--------|--------+-------------+
 *    |               | LEFT   | DOWN   | RIGHT  | PGDN   |        |        | PREV   | PLAY   | NEXT   |        |        |   RGB TOG          |
 *    |               |        |        |        |        |        |        |        |        |        |        |        |                    |  
 *  +-----------------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------+-------+------------+----+
 * |                  | Rainbow| Xmas   | Swirl  | Knight |Breathe |GradieNt| MUTE   | VOL DN | VOL UP | PIPE \ | CAPS LOCK      | PAGEUP |  Fn    |
 * |                  |        |        |        |        |        |        |        |        |        |        |                |        |        |
 * |----------+----------+----------+---------------------------------------------------------+--------+--------+----------------+--------+--------+
 * |          |          |          |        Fn         |   ENTER     |     NUM.Dot          |        |        |        | HOME   | PAGEDN | END    |
 * |          |          |          |                   |             |                      |        |        |        |        |        |        |  
 * '--------------------------------------------------------------------------------------------------------------------------------------+--------+
 */

    [_EXTRA] = LAYOUT(
        QK_BOOT,   QWERTYX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  QK_BOOT,   \
                 QWERTY,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,  KC_TRNS, KC_PSCR, KC_TRNS, KC_TRNS, KC_DEL,           \
                 _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_TRNS, KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS, RGB_TOG,                   \
                 KC_TRNS, RGB_M_R, RGB_M_X, RGB_M_SW,RGB_M_K, RGB_M_B, RGB_M_G, KC_MUTE, KC_VOLD, KC_VOLU, KC_BSLS, KC_CAPS,          KC_PGUP, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_ENT,  KC_PDOT,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END   \
        ), 

/* Fn
 *  .-----------------------------------------------------------------------------------------------------------------------------------------------+
 *  |        |QWERTYX | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     |  F10   | F11    | F12    | DELETE | RESET  |
 *  |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |  
 *  +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 *       |  QWERTY    | HOME   | UP     | END    | PGUP   |        |        |        | INS    |        | Print  |        |        |  DELETE     |
 *       |            |        |        |        |        |        |        |        |        |        | Screen |        |        |             |  
 *    +---------------+--------+--------+--------+--------+------- +--------+--------+--------+--------+--------+--------|--------+-------------+
 *    |               | LEFT   | DOWN   | RIGHT  | PGDN   |        |        | PREV   | PLAY   | NEXT   |        |        |   RGB TOG          |
 *    |               |        |        |        |        |        |        |        |        |        |        |        |                    |  
 *  +-----------------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------+-------+------------+----+
 * |                  | Rainbow| Xmas   | Swirl  | Knight |Breathe |GradieNt| MUTE   | VOL DN | VOL UP | PIPE \ | CAPS LOCK      | PAGEUP |  Fn    |
 * |                  |        |        |        |        |        |        |        |        |        |        |                |        |     E2 |
 * |----------+----------+----------+---------------------------------------------------------+--------+--------+----------------+--------+--------+
 * |          |          |          |        Fn         |   ENTER     |     NUM.Dot          |        |        |        | HOME   | PAGEDN | END    |
 * |       E3 |          |          |                   |         E3  |                      |        |        |     E2 |        |        |        |  
 * '--------------------------------------------------------------------------------------------------------------------------------------+--------+
 */
};


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] =   { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN),   ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_QWERTYX] =  { ENCODER_CCW_CW(C(KC_TAB), C(S(KC_TAB))),    ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN),   ENCODER_CCW_CW(RGB_SAD, RGB_SAI)  },
    [_FUNCTION] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),           ENCODER_CCW_CW(KC_RIGHT, KC_LEFT),            ENCODER_CCW_CW(RGB_SPD, RGB_SPI)  },
    [_EXTRA] =    { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD),          ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN),   ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
};
#endif



    /* Encoder Positions
 *  .-----------------------------------------------------------------------------------------------------------------------------------------------+
 *  |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 *  |     E1 |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |  
 *  +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
 *       |            |        |        |        |        |        |        |        |        |        |        |        |        |             |
 *       |            |        |        |        |        |        |        |        |        |        |        |        |        |             |  
 *    +---------------+--------+--------+--------+--------+------- +--------+--------+--------+--------+--------+--------|--------+-------------+
 *    |               |        |        |        |        |        |        |        |        |        |        |        |                    |
 *    |               |        |        |        |        |        |        |        |        |        |        |        |                    |  
 *  +-----------------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------+-------+------------+----+
 * |                  |        |        |        |        |        |        |        |        |        |        |                |        |        |
 * |                  |        |        |        |        |        |        |        |        |        |        |                |        |     E2 |
 * |----------+----------+----------+---------------------------------------------------------+--------+--------+----------------+--------+--------+
 * |          |          |          |                   |             |                      |        |        |        |        |        |        |
 * |       E3 |          |          |                   |         E3  |                      |        |        |     E2 |        |        |        |  
 * '--------------------------------------------------------------------------------------------------------------------------------------+--------+
  */