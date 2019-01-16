/*
Copyright 2019 Batuhan Başerdem <baserdem.batuhan@gmail.com> @bbaserdem
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
#include "mouse_emulation.h"

bool process_record_mouse(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MO_NE:
            if( record->event.pressed ) {
                mousekey_on(MO_N);
                mousekey_on(MO_E);
                mousekey_send();
            } else {
                mousekey_off(MO_N);
                mousekey_off(MO_E);
                mousekey_send();
            }
            return false;
            break;
        case MO_NW:
            if( record->event.pressed ) {
                mousekey_on(MO_N);
                mousekey_on(MO_W);
                mousekey_send();
            } else {
                mousekey_off(MO_N);
                mousekey_off(MO_W);
                mousekey_send();
            }
            return false;
            break;
        case MO_SE:
            if( record->event.pressed ) {
                mousekey_on(MO_S);
                mousekey_on(MO_E);
                mousekey_send();
            } else {
                mousekey_off(MO_S);
                mousekey_off(MO_E);
                mousekey_send();
            }
            return false;
            break;
        case MO_SW:
            if( record->event.pressed ) {
                mousekey_on(MO_S);
                mousekey_on(MO_W);
                mousekey_send();
            } else {
                mousekey_off(MO_S);
                mousekey_off(MO_W);
                mousekey_send();
            }
            return false;
            break;
        case MO_S_NE:
            if( record->event.pressed ) {
                mousekey_on(MO_S_N);
                mousekey_on(MO_S_E);
                mousekey_send();
            } else {
                mousekey_off(MO_S_N);
                mousekey_off(MO_S_E);
                mousekey_send();
            }
            return false;
            break;
        case MO_S_NW:
            if( record->event.pressed ) {
                mousekey_on(MO_S_N);
                mousekey_on(MO_S_W);
                mousekey_send();
            } else {
                mousekey_off(MO_S_N);
                mousekey_off(MO_S_W);
                mousekey_send();
            }
            return false;
            break;
        case MO_S_SE:
            if( record->event.pressed ) {
                mousekey_on(MO_S_S);
                mousekey_on(MO_S_E);
                mousekey_send();
            } else {
                mousekey_off(MO_S_S);
                mousekey_off(MO_S_E);
                mousekey_send();
            }
            return false;
            break;
        case MO_S_SW:
            if( record->event.pressed ) {
                mousekey_on(MO_S_S);
                mousekey_on(MO_S_W);
                mousekey_send();
            } else {
                mousekey_off(MO_S_S);
                mousekey_off(MO_S_W);
                mousekey_send();
            }
            return false;
            break;
    }
    return true;
}
