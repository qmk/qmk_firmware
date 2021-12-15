/* Copyright 2017 Andreas Lindhé
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
#include "debug.h"
#include "action_layer.h"
#include "keymap_swedish.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Print  |   !  |  "   |  #   |  #   |  %   |      |           |Middle|   &  |  /   |  (   |  )   |  =   |  ?     |
 * | Screen |   1  |  2 @ |  3 £ |  4 $ |  5   | F11  |           |Mouse |   6  |  7 { |  8 [ |  9 ] |  0 } |  + \   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    | Q    | W    | E    | R    | T    | ~L1  |           |  L1  | Y    | U    | I    | O    | P    | Å      |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | CapsLk | A    | S    | D    | F    | G    |------|           |------| H    | J    | K    | L    | Ö    | Ä      |
 * |--------+------+------+------+------+------| `    |           | Del  |------+------+------+------+------+--------|
 * | LShft  | Z    | X    | C    | V    | B    |  '   |           |      | N    | M    | ,    | .    | -    | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LCtl |  ^   | *    | LAlt | LGui |                                       | AltGr| Down |  Up  | Left | Right|
 *   | (')  |  " ~ | '  ´ |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,--------------.
 *                                        | LCtl | LAlt |       | Home |   End  |
 *                                 ,------|------|------|       |------+-------+------.
 *                                 |      |      |  ~   |       | PgUp |       |      |
 *                                 | Space|Back- |------|       |------|  Tab  |Enter |
 *                                 |      |space | Esc  |       | PgDn |       | L2   |
 *                                 `--------------------'       `---------------------'
 */

[BASE] = LAYOUT_ergodox(  // layer 0 : default
    // left hand
    KC_PSCR,         KC_1,     KC_2,     KC_3,    KC_4,    KC_5,   KC_F11,
    KC_TAB,          KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,   MO(SYMB),
    KC_CAPS,         KC_A,     KC_S,     KC_D,    KC_F,    KC_G,
    KC_LSFT,         KC_Z,     KC_X,     KC_C,    KC_V,    KC_B,   SE_ACUT,
    CTL_T(SE_QUOT),  SE_CIRC,  SE_ASTR,  KC_LALT, KC_LGUI,
                                               KC_LCTRL,  KC_LALT,
                                                          SE_TILD,
                                         KC_SPC, KC_BSPC, KC_ESC,
    // right hand
         KC_MS_BTN3,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,     SE_PLUS,
         TG(SYMB),  KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,     SE_ARNG,
                    KC_H,   KC_J,    KC_K,    KC_L,    SE_ODIA,  SE_ADIA,
         KC_DEL,    KC_N,   KC_M,    KC_COMM, KC_DOT,  SE_MINS,  KC_RSFT,
                            KC_ALGR, KC_DOWN, KC_UP,   KC_LEFT,  KC_RGHT,
         KC_HOME,        KC_END,
         KC_PGUP,
         KC_PGDN, KC_TAB, LT(MDIA, KC_ENT)
),

/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |  /   |   *  |  -   |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |           |      |      |  7   |  8   |  9   |  +   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |------|           |------|      |  4   |  5   |  6   |  +   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  F9  |  F10 |  F11 |  F12 |      |      |           |      |      |  1   |  2   |  3   | Enter|        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |  0   | ,    | .    | Enter|      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_TRNS, KC_TRNS,
       KC_TRNS, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_TRNS,
       KC_TRNS, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_PSLS, KC_PAST, KC_PMNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_7,    KC_8,    KC_9,    KC_PPLS, KC_TRNS,
                KC_TRNS, KC_4,    KC_5,    KC_6,    KC_PPLS, KC_TRNS,
       RESET,   KC_TRNS, KC_1,    KC_2,    KC_3,    KC_PENT, KC_TRNS,
                         KC_0,    KC_COMM, KC_DOT,  KC_PENT, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      | Play | Pause| Prev | Next |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      | Lclk | Rclk |      |      |           |      |      |VolDn |VolUp | Mute |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |LeClk |RiClk |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_BTN1, KC_BTN2, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_MPLY, KC_MPLY, KC_MPRV, KC_MNXT, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_3_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            // none
            break;
    }

    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
        // if capslk is on, set led 1 on
        ergodox_right_led_1_on();
    } else {
        ergodox_right_led_1_off();
    }

};
