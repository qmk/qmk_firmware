/* Copyright 2017 @TurboMech /u/TurboMech <discord> @A9entOran9e#6134
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
#include "turbomech.h"

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

#define _QWERTY 0 //BASE layer
#define _FUNCTION 1 //Function layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BL
 * ,- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -.
 * |   Esc   |   Scrn  |   Scrn  | Expose  |Launchpad|   Show  |Dock Hide|  Screen | Shortcut| Shortcut| Shortcut| Shortcut|   Play  |  Mute   | Vol Up  | Vol Down|
 * |         |Brght Up | Brght Dn|         |         | Desktop |  Toggle | Capture |         |         |         |         |   Pause |         |         |         |
 * |- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - - - -+- - - - -|
 * |    `    |    1    |    2    |    3    |    4    |    5    |    6    |    7    |    8    |    9    |    0    |    -    |    +    |     Backspace     |  POWER  |
 * |         |         |         |         |         |         |         |         |         |         |         |         |         |                   |         |
 * |- - - - - - - +- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - +- - - - -|
 * |     TAB      |    Q    |    W    |    E    |    R    |    T    |    Y    |    U    |    I    |    O    |    P    |    [    |     ]   |      \       | Shortcut|
 * |              |         |         |         |         |         |         |         |         |         |         |         |         |              |         |
 * |- - - - - - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - - - - -+- - - - -|
 * |      CAPS       |    A    |    S    |    D    |    F    |    G    |    H    |    J    |    K    |    L    |    ;    |    '    |        Enter        |   Page  |
 * |                 |         |         |         |         |         |         |         |         |         |         |         |                     |    Up   |
 * |- - - - - - - - - - - +- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - - +- - - - -+- - - - -+
 * |        Shift         |    Z    |    X    |    C    |    V    |    B    |    N    |    M    |    ,    |    .    |    /    |     Shift      |   Up    |  Page   |
 * |                      |         |         |         |         |         |         |         |         |         |         |                |         |  Down   |
 * |- - - - - +- - - - - - +- - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -|
 * |  Control |   Option   |     Gui    |                             Space                            |   Gui   |   Opt   |    Fn   |  Left   |   Down  |  Right  |
 * |          |    /Alt    |            |                                                              |         |   Alt   |         |         |         |         |
 * `- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -'
 */

	[_QWERTY] = LAYOUT(
		KC_ESC, KC_F14, KC_F15, LCTL(KC_UP), LCTL(KC_L), KC_F11, LALT(LGUI(KC_D)), LCTL(KC_S), LCTL(LSFT(KC_O)), LCTL(LGUI(KC_1)), LCTL(LGUI(KC_2)), LCTL(LGUI(KC_3)), KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU,
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_POWER,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, LCTL(LGUI(KC_N)),
		KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
		KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, KC_UP, KC_PGDN,
		KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, KC_RALT, MO(1), KC_LEFT, KC_DOWN, KC_RGHT),

/* FN1 - SEE readme.md
 * ,- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -.
 * |   Quit  |   F1    |    F2   |   F3    |   F4    |   F5    |    F6   |   F7    |    F8   |    F9   |   F10   |   F11   |   F12   |  Trns   |  Trns   |   DFU   |
 * |   All   |         |         |         |         |         |         |         |         |         |         |         |         |         |         |  Reset  |
 * |- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - - - -+- - - - -|
 * |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |       Delete      |   Lock  |
 * |         |         |         |         |         |         |         |         |         |         |         |         |         |                   |Shortcut |
 * |- - - - - - - +- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - +- - - - -|
 * |     Trns     |   RGB   |   RGB   |   RGB   |   RGB   | RGB Hue | RGB Hue | RGB Sat | RGB Sat |  Trns   |   Trns  |   Trns  |   Trns  |     Trns     |   Trns  |
 * |              |  Toggle |   Mode  | Increase| Decrease| Increase| Decrease| Increase| Decrease|         |         |         |         |              |         |
 * |- - - - - - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - - - - -+- - - - -|
 * |      Trns       |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |  Trns   |  Trns   |   Trns  |   Trns  |  Trns   |   Trns  |        Trns         |   Trns  |
 * |                 |         |         |         |         |         |         |         |         |         |         |         |                     |         |
 * |- - - - - - - - - - - +- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - - +- - - - -+- - - - -+
 * |         Trns         |Backlight|Backlight|Backlight|Backlight|   Trns  |  Trns   |   Trns  |   Trns  |   Trns  |   Trns  |     Trns       |  Trns   |  Trns   |
 * |                      |  Toggle | Increase| Decrease|   Step  |         |         |         |         |         |         |                |         |         |
 * |- - - - - +- - - - - - +- - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -|
 * |   Trns   |    Trns    |    Trns    |                             Trns                             |  Trns   |  Trns   |  Trns   |  Trns   |   Trns  |  Trns   |
 * |          |            |            |                                                              |         |         |         |         |         |         |
 * `- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -'
 */


	[_FUNCTION] = LAYOUT(
		LALT(LGUI(KC_Q)), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_RESET,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, LCTL(LALT(LGUI(KC_S))),
		KC_TRNS, RGB_TOG, RGB_MOD, RGB_VAI, RGB_VAD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, BL_TOGG, BL_INC, BL_DEC, BL_STEP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

};

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		DDRB |= (1 << 2); PORTB &= ~(1 << 2);
	} else {
		DDRB &= ~(1 << 2); PORTB &= ~(1 << 2);
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_KANA)) {

	} else {

	}

}

enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
}
