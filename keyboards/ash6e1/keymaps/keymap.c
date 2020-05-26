/* Copyright 2020 sh_xguitar
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
    [0] = LAYOUT( /* Base */
        MO(1),  KC_HOME, KC_PGUP,
        KC_DEL, KC_END,  KC_PGDN
        
    ),
    [1] = LAYOUT(
        _______, BL_STEP, BL_BRTG, 
        KC_MPRV, BL_TOGG, KC_MNXT
    )
};
 

void dip_switch_update_user(uint8_t index, bool active) 
{ 
 switch (index) {
        case 0:     //ENC0_SW
        if(active) //ENC0 pressed
        { 
            tap_code(KC_MPLY);
        } 
    else //ENC0 released
                {
            //do nothing
        }
            break;
        }
    }

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}
