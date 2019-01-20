/* Copyright 2018 Andreas Lindhé, Christoffer Holmberg
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
#include "version.h"
#include "keymap_swedish.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define ARRW 3 // arrow + soon mouse

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ½    |   !  |  "   |  #   |  #   |  %   | Ins  |           |  L1  |   &  |  /   |  (   |  )   |  =   |  ?     |
 * |   §    |   1  |  2 @ |  3 £ |  4 $ |  5   |      |           |      |   6  |  7 { |  8 [ |  9 ] |  0 } |  + \   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |  L2  |           |  L2  |   Y  |   U  |   I  |   O  |   P  |   Å    |
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   L4   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |Ö / L3|   Ä/L2 |
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------| Back |           |Forwd |------+------+------+------+------+--------|
 * | LShift/|  Z   |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ;  |   :  |  _   | RShift/|
 * |    (   |      |      |      |      |      |      |           |      |      |      |   ,  |   .  |  -   |   )    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | '/   |  `   |Alt   | Left | Right|                                       |  Spc | Bksp | AltGr|  *   |  ~/  |
 *   | Ctrl |  '   |      |      |      |                                       |      |      |      |      | Ctrl |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | <>|  | End  |       | Home |   ^    |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 | Left | Right| PgDn |       | PgUp |   Up   | Down |
 *                                 |------|------|------|       |------|--------|------|
 *                                 | Ctrl/| Alt/ |      |       |      |  Alt/  | Ctrl/|
 *                                 | Enter| Esc  | Lgui |       | Lgui |  Esc   | Enter|
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox_80(  // layer 0 : default
    // left hand
    NO_HALF,          KC_1,           KC_2,          KC_3,    KC_4,    KC_5,   KC_INS,
    KC_TAB,           KC_Q,           KC_W,          KC_E,    KC_R,    KC_T,   TG(SYMB),
    MO(ARRW),         KC_A,           KC_S,          KC_D,    KC_F,    KC_G,
    KC_LSPO,          CTL_T(KC_Z),    KC_X,          KC_C,    KC_V,    KC_B,   KC_WBAK,
    CTL_T(NO_APOS),   NO_ACUT,        KC_LALT,       KC_BSPC, KC_SPC,
                                                                             NO_LESS,   KC_END,
                                                              KC_LEFT,      KC_RIGHT,  KC_PGDN,
                                                        CTL_T(KC_ENT), ALT_T(KC_ESC),  KC_LGUI,

    // right hand
         TO(ARRW),       KC_6,   KC_7,   KC_8,    KC_9,    KC_0,              NO_PLUS,
         TG(SYMB),       KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,              NO_AA,
                         KC_H,   KC_J,   KC_K,    KC_L,    LT(MDIA, NO_OSLH), LT(SYMB, NO_AE),
         KC_WFWD,        KC_N,   KC_M,   KC_COMM, KC_DOT,  NO_MINS,           KC_RSPC,
                                 KC_SPC, KC_BSPC, KC_ALGR, NO_ASTR,           CTL_T(NO_TILD),
        KC_HOME,  NO_CIRC,
        KC_PGUP,  KC_UP,         KC_DOWN,
        KC_LGUI,  ALT_T(KC_ESC), CTL_T(KC_ENT)
),
/* Keymap: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |Version |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   -  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |------|------|------|       |------|------|------|
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox_80(
       // left hand
       VRSN,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  _______,
       _______,KC_EXLM,NO_AT,  NO_LCBR,NO_RCBR,NO_PIPE,_______,
       _______,KC_HASH,NO_DLR, NO_LPRN,NO_RPRN,NO_GRV,
       _______,KC_PERC,NO_CIRC,NO_LBRC,NO_RBRC,NO_TILD,_______,
          EPRM,_______,_______,_______,_______,
                                       _______,_______,
                               _______,_______,_______,
                               _______,_______,_______,
       // right hand
       _______, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       _______, KC_UP,   KC_7,   KC_8,    KC_9,    NO_ASTR, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    NO_PLUS, _______,
       _______, NO_AMPR, KC_1,   KC_2,    KC_3,    NO_MINS, _______,
                         _______,KC_DOT,  KC_0,    NO_EQL,  _______,
       _______, _______,
       _______, _______, _______,
       _______, _______, _______
),

/* Keymap: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | MsUp |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |MsLeft|MsDown|MsRght|      |      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |------|------|       |------|------|------|
 *                                 |      |      |      |       |      |      |BrBck |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox_80(
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_MS_U, _______, _______, _______, _______,
        _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_BTN1, KC_BTN2,
                                            _______, _______,
                                   _______, _______, _______,
                                   _______, _______, _______,
     // right hand
        _______,  _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______,
                  _______, _______, _______, _______, _______, KC_MPLY,
        _______,  _______, _______, KC_MPRV, KC_MNXT, _______, _______,
                           KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,
        _______, _______,
        _______, _______, _______,
        _______, _______, KC_WBAK
),
 // Keymap: Ducky Style arrows
[ARRW] = LAYOUT_ergodox_80(
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_UP  , _______, _______, _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_DEL,  _______,
                                            _______, _______,
                                   _______, _______, _______,
                                   _______, _______, _______,
     // right hand
        TO(BASE),  _______, _______, _______, _______, _______, _______,
        _______,   _______, _______, _______, _______, _______, _______,
                   _______, _______, _______, _______, _______, _______,
        _______,   _______, _______, _______, _______, _______, _______,
                            _______, _______, _______, _______, _______,
        _______, _______,
        _______, _______, _______,
        _______, _______, _______
),

};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

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
      // Binary: lsb at bottom
        case 1:
          ergodox_right_led_3_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_board_led_on();
        default:
            // none
            break;
    }
};
