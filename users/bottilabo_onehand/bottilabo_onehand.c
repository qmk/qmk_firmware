/* Copyright 2020 bottilabo [twitter @bottinabo]
 *                          [https://github.com/bottilabo/bottilabo_onehand]
 *
 * GNU General Public License version 3 [http://www.gnu.org/licenses/]
 */

#include QMK_KEYBOARD_H
#include "stdafx.h"

#pragma message("Bottilabo ONEHAND")

#include "IM_ONEHAND.h"

__attribute__((weak))
void matrix_init_local(void) {
}

__attribute__((weak))
void matrix_scan_local(void) {
}

__attribute__((weak))
bool process_record_local(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void matrix_init_user(void) {
	IM_ONEHAND_enable(1);
    matrix_init_local();
}
void matrix_scan_user(void) {
    matrix_scan_local();
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if( record->event.pressed )
    {
        switch(keycode) {
            case K_IM_EN:
                IM_ONEHAND_enable(1);
                break;
            case K_IM_JP:
                IM_ONEHAND_enable(2);
                break;
        }
    }

    if( ! process_record_local(keycode,record) )
        return false;

    if( !process_ONEHAND(keycode, record) )
        return false;

    return true;
}

