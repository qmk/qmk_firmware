/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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

#define _AUDACITY 0
#define _LIGHTS 1

enum custom_keycodes {
  AUDACITY = SAFE_RANGE,
  LIGHTS,
};

#define KC_ KC_TRNS
#define KC_AUD AUDACITY
#define KC_LITE LIGHTS
#define KC_ZNRM LCTL(KC_2) // zoom normal
#define KC_SAVE LCTL(KC_S) // save
#define KC_SYNC LALT(KC_S) // sync-lock tracks
#define KC_SLNC LCTL(KC_L) // silence selection
#define KC_BL_S BL_STEP
#define KC_RGBM RGB_MOD
#define KC_RGBT RGB_TOG


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Vol Dn/Up |      | Knob 2: Page Dn/Up |
        | Press: Mute       | Home | Press: Play/Pause  |
        | Hold: Layer 2     | Up   | RGB Mode           |
        | Left              | Down | Right              |
     */
    [_AUDACITY] = LAYOUT(
    //,-------+-------+-------.
       KC_LITE,KC_SAVE,KC_ZNRM,
    //|-------+-------+-------|
       KC_SYNC,KC_SLNC,KC_BSPC,
    //|-------+-------+-------|
       KC_SPC , KC_F1 , KC_F2
    //`-------+-------+-------'
    ),
    /*
        | RESET          | N/A  | Media Stop |
        | Held: Layer 2  | Home | RGB Mode   |
        | Media Previous | End  | Media Next |
     */
    [_LIGHTS] = LAYOUT(
    //,-------+-------+-------.
         KC_  ,KC_BL_S,KC_STOP,
    //|-------+-------+-------|
       KC_RGBM,KC_HOME,KC_RGBT,
    //|-------+-------+-------|
       KC_MPRV,KC_END ,KC_MNXT
    //`-------+-------+-------'
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_RGHT);
        } else {
            tap_code(KC_LEFT);
        }
    }
    else if (index == 1) {
        if (clockwise) {
	    SEND_STRING(SS_LCTRL("1")); // audacity zoom in
        } else {
	    SEND_STRING(SS_LCTRL("3")); // audacity zoom out
        }
    }
}
