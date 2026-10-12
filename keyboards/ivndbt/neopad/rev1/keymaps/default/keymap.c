/* Copyright 2021 ivndbt
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
            LAYER 0 - MUSIC
    /-----------------------------`
    |  TO(1)  |  stop   |   mute  |	L ENC: prev/next song
    |---------|---------|---------|
    |   prev  |  play   |   next  |	R ENC: vol up/down
    \-----------------------------'
    */
    [0] = LAYOUT(
                TO(1),     KC_MSTP,  KC_MUTE,
    		    KC_MPRV,   KC_MPLY,  KC_MNXT
    ),

    /*
            LAYER 1 - MOVEMENT IN WINDOWS
    /---------------------------------------`
    |    TO(2)    | maximize | show desktop | L ENC: change desktop
    |-------------|----------|--------------|
    | move window | minimize | move window  | R ENC: change browser tab + change explorer window
    \---------------------------------------'
    */
    [1] = LAYOUT(
				TO(2),     		LGUI(KC_UP),    LGUI(KC_D),
				LGUI(KC_LEFT),	LGUI(KC_DOWN),  LGUI(KC_RIGHT)
    ),

    /*
            LAYER 2 - SHORTCUT
    /------------------------------`
    |  TO(3)  |   esc   | task man | L ENC: redo/undo
    |---------|---------|----------|
    |   cut   |   copy  |   paste  | R ENC: mouse wheel up/down
    \------------------------------'
    */
    [2] = LAYOUT(
                TO(3),     		KC_ESC,    		LCTL(LSFT(KC_ESC)),
    		    LCTL(KC_X),		LCTL(KC_C),     LCTL(KC_V)
    ),

    /*
            LAYER 3 - AUDACITY
    /-----------------------------`
    |  TO(0)  |   REC   |   canc  |	L ENC: pan right/left
    |---------|---------|---------|
    |   ctrl  |   play  |  pause  |	R ENC: mouse wheel up/down
    \-----------------------------'
    */
    [3] = LAYOUT(
                TO(0),     	LSFT(KC_R),    	KC_DEL,
    		    KC_LCTL,	KC_SPC,         KC_P
    ),

};


bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {											/* LEFT ENCODER */
        switch (get_highest_layer(layer_state)) {
            case 0:
                // layer 0 - next song (CW) and previous (CCW)
                if (clockwise) {
                    tap_code(KC_MNXT);
                } else {
                    tap_code(KC_MPRV);
                }
                break;

            case 1:
                // layer 1 - change desktop right (CW) and left (CCW)
                if (clockwise) {
                    tap_code16(LCTL(LGUI(KC_RIGHT)));
                } else {
                    tap_code16(LCTL(LGUI(KC_LEFT)));
                }
                break;

            case 2:
                // layer 2 - redo (CW) and undo (CCW)
                if (clockwise) {
                    tap_code16(LCTL(KC_Y));
                } else {
                    tap_code16(LCTL(KC_Z));
                }
                break;

	    case 3:
                // layer 3 - pan right (CW) and left (CCW)
                if (clockwise) {
                    tap_code(MS_WHLR);
                } else {
                    tap_code(MS_WHLL);
                }
                break;
        }

    } else if (index == 1) {									/* RIGHT ENCODER */
        switch (get_highest_layer(layer_state)) {
            case 0:
                // layer 0 - volume up (CW) and down (CCW)
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;

            case 1:
                // layer 1 - change browser tab (CW) and change explorer window (CCW)
                if (clockwise) {
                    tap_code16(LCTL(KC_TAB));
                } else {
                    tap_code16(LALT(LSFT(KC_TAB)));
                }
                break;

            case 2:
                // layer 2 - wheel up (CW) and down (CCW)
                if (clockwise) {
                    tap_code(MS_WHLU);
                } else {
                    tap_code(MS_WHLD);
                }
                break;

            case 3:
                // layer 3 - wheel up (CW) and down (CCW)
                if (clockwise) {
                    tap_code(MS_WHLU);
                } else {
                    tap_code(MS_WHLD);
                }
                break;
        }
    }
    return true;
}
