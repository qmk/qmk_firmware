/*
Copyright 2012,2013 gezhaoyou <gezhaoyou@126.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case QK_USER_1:
        if (record->event.pressed) {            
            SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_SPACE) SS_UP(X_LGUI) SS_DELAY(1000) SS_TAP(X_LGUI) SS_DELAY(1000) "terminal" SS_DELAY(1000) SS_TAP(X_ENTER) SS_DELAY(1000) "open https://veilid.com\n" SS_DELAY(1000) "start https://veilid.com\n");
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ortho_1x1(QK_USER_1),
};