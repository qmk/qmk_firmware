/* Copyright 2020 Hugh Mungis
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
#include "ake160886.h"
// in keyboard.c
// You could technically add more layers if 160 keys are not enough
// This is me trying to make a normal-ish layout in the middle of the keyboard, leaving the rest unassigned
// Going to need a wiiiide editor window for this to look readable
// Available keycodes are at https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
const uint16_t PROGMEM keymaps[] [MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( \
    NO,         NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,
    NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,

    NO,   NO,   NO,   NO,   NO,   ESC,        NO,         NO,         NO,   NO,   NO,   NO,   NO,         NO, NO,   NO,         NO,   NO,   NO,   NO,
    NO,   NO,   NO,   NO,   NO,   TAB,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    LBRC, RBRC, NO,   NO,   NO,   NO,   NO,   NO,   NO,
    NO,   NO,   NO,   NO,   NO,   CAPS, A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, QUOT, NO,   ENT,  NO,   NO,   NO,   NO,   NO,   NO,
    NO,   NO,   NO,   NO,   NO,   LSFT, NO,   Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH, NO,   RSFT, NO,   NO,   NO,   NO,   NO,   NO,
    NO,         NO,   NO,   NO,   LCTL, LWIN,             LALT,             SPC,        RALT, NO,   APP,  RCTL, NO,         NO,   NO,   NO
  )};

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

/*
void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    matrix_init_user();
}

void matrix_scan_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)

    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // put your per-action keyboard code here
    // runs for every action, just before processing by the firmware

    return process_record_user(keycode, record);
}

bool led_update_kb(led_t led_state) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    return led_update_user(led_state);
}
*/
