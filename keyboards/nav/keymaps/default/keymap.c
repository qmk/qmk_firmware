/* Copyright 2018 REPLACE_WITH_YOUR_NAME
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
#include "nav.h"
#define _BL 0
#define _ML 1
#define _RL 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* Base Layer
 ,-----------------.
 | Ins | PU  | Fn1 |
 |-----|-----|-----|
 | Del | PG  | Fn2 |
 |-----|-----|-----|
 |     |  Up |     |
 |-----|-----|-----|
 | Left| Down|Right|
 `-----------------'
 */
  [_BL] = LAYOUT( /* Base */
    KC_INS,    KC_PGUP,    MO(1),
    KC_DEL,    KC_PGDN,    MO(2),
	KC_NO,   KC_UP,   KC_NO,
	KC_LEFT, KC_DOWN, KC_RIGHT
),

  	/* Media
 ,-----------------.
 | Vol+|Media| Fn1 |
 |-----|-----|-----|
 | Vol-| Stop| Fn2 |
 |-----|-----|-----|
 |     | Mute|     |
 |-----|-----|-----|
 | Left| Down|Right|
 `-----------------'
 */
  [_ML] = LAYOUT( /* Base */
    KC_VOLU,    KC_MSEL,    KC_TRNS,
    KC_VOLD,    KC_MSTP,    KC_TRNS,
	KC_NO,   KC_MUTE,   KC_NO,
	KC_MPRV, KC_MPLY, KC_MNXT
),

  	/* RGB Control
 ,-----------------.
 |Toggl| Hue+| Fn1 |
 |-----|-----|-----|
 | M_R | Hue-| Fn2 |
 |-----|-----|-----|
 |     | Val+|     |
 |-----|-----|-----|
 |Mode-| Val-|Mode+|
 `-----------------'
 */
  [_RL] = LAYOUT( /* Base */
    RGB_TOG,  RGB_HUI,    KC_TRNS,
    RGB_M_R,  RGB_HUD,    KC_TRNS,
	KC_NO,   RGB_VAI,   KC_NO,
	RGB_RMOD, RGB_VAD, RGB_MOD
),

};

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
