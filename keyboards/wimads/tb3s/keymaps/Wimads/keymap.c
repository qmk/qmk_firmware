/* Copyright 2024 Wimads
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

////TO DO////
/* Undo EE_BOOT
 * Remove snipe
 * Add layer for EEPROM stuff in place of snipe
*/
#include QMK_KEYBOARD_H
#include "maccel.c"

enum layers {
   _DEF,
   _QMK,
};

#define LMB KC_BTN1
#define RMB KC_BTN2
#define MMB KC_BTN3
#define BCK KC_BTN4
#define FWD KC_BTN5

#define RST_QMK LT(_QMK, QK_BOOT) //
#define DRTGSCR LT(10, KC_NO)     //drag-toggle-scroll >>further defined in macro

#include "gboards/g/keymap_combo.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEF] = LAYOUT(RMB,    DRTGSCR,  LMB),
    [_QMK] = LAYOUT(EE_CLR, DPI_RMOD, DPI_MOD)
};

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    return pointing_device_task_maccel(mouse_report);
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    static bool dragscroll = false; //dragscroll active or not
    static bool drag_toggle = false; //dragscroll was activated via toggle or not
    switch(keycode) {
        case RST_QMK:
            if (record->event.pressed && record->tap.count){
                reset_keyboard();
                return false;
            } return true;
        case DRTGSCR: //dragscroll / drag_toggle / sniping - all in one key!
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
                charybdis_set_pointer_dragscroll_enabled(dragscroll);
            } else { //on release
                if(!drag_toggle) { //if no drag_toggle, turn off dragscroll
                    dragscroll = false;
                    charybdis_set_pointer_dragscroll_enabled(dragscroll);
                } //else do nothing
            } return false;

        default:
            return true;
    }//.switch(keycode)
    return true;
};
