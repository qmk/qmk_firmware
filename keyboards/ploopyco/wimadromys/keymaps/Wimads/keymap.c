/* Copyright 2023 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
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
   _DEF,
};

#define LMB KC_BTN1
#define RMB KC_BTN2
#define MMB KC_BTN3
#define BCK KC_BTN4
#define FWD KC_BTN5

#define SCR_SNI LT(10, KC_NO) //dragscroll-sniping

#include "gboards/g/keymap_combo.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEF] = LAYOUT(RMB,   SCR_SNI, LMB)
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    static bool dragscroll = false; //dragscroll active or not
    static bool drag_toggle = false; //dragscroll was activated via toggle or not
    static bool sniping = false;
    switch(keycode) {
        case SCR_SNI: //LCTL(DRGSCRL)
            if (record->event.pressed && record->tap.count) { //on tap
                //toggle dragscroll on/off
                dragscroll = !dragscroll; //invert dragscroll state
                charybdis_set_pointer_dragscroll_enabled(dragscroll); //set dragscroll
                drag_toggle = dragscroll; //set drag_toggle state
            } else if(record->event.pressed && !drag_toggle) { //on hold && not toggled
                //turn dragscroll on while held
                dragscroll = true;
                charybdis_set_pointer_dragscroll_enabled(dragscroll);
            } else if(record->event.pressed && drag_toggle) { //on hold && toggled (ie. tap once and then hold)
                //turn dragscroll off, and turn sniping on
                drag_toggle = false;
                dragscroll = false;
                sniping = true;
                charybdis_set_pointer_dragscroll_enabled(dragscroll);
                charybdis_set_pointer_sniping_enabled(sniping);
            }else { //on release
                if(sniping) { //if sniping true, turn off sniping
                    sniping = false;
                    charybdis_set_pointer_sniping_enabled(sniping);
                } else if(!drag_toggle) { //if no drag_toggle, turn off dragscroll
                    dragscroll = false;
                    charybdis_set_pointer_dragscroll_enabled(dragscroll);
                } //else do nothing
            } return false;

        default:
            return true;
    }//.switch(keycode)
    return true;
};
