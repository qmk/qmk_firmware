/* Copyright 2020 bottilabo [twitter @bottinabo]
 *                          [https://github.com/bottilabo/bottilabo_onehand]
 *
 * GNU General Public License version 3 [http://www.gnu.org/licenses/]
 */

#include QMK_KEYBOARD_H
#include "stdafx.h"

#pragma message("Bottilabo ONEHAND")

#include "IM_ONEHAND.h"


bool check_singletap(uint16_t keycode,bool press) {
    static uint16_t prev_key = 0;
    static tick_t prev_tick = 0;

    bool ret = false;
    tick_t now = timer_read();
    if( press ) {
        prev_key = keycode;
        prev_tick = now;
    }
    else {
        if( prev_key == keycode && elapsed_time(now,prev_tick)<DBLTAP_TERM ) {
            ret = true;
        }
        prev_key = 0;
        prev_tick = 0;
    }

    return ret;
}
bool check_dbltap(uint16_t keycode) {
    static uint16_t prev_key = 0;
    static tick_t prev_tick = 0;

    tick_t now = timer_read();
    bool ret = false;
    if( prev_key == keycode && elapsed_time(now,prev_tick)<DBLTAP_TERM ) {
        ret = true;
    }

    prev_key = keycode;
    prev_tick = now;

    return ret;
}




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

void send_im_mode_key(bool jp_mode) {
    send_keycode(KC_LALT,1);
    send_keycode(KC_GRV,2);
    send_keycode(KC_LALT,0);
}

static bool im_jp = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool singletap = check_singletap(keycode,record->event.pressed);
    if( record->event.pressed )
    {
        //bool dbltap = check_dbltap(keycode);

        switch(keycode) {
            case K_IM_EN:
                im_jp = false;
                IM_ONEHAND_enable(1);
                send_im_mode_key(im_jp);
                break;
            case K_IM_JP:
                im_jp = true;
                IM_ONEHAND_enable(2);
                send_im_mode_key(im_jp);
                break;
        }
    }
    else {
        if( keycode == K_TL3 && singletap ) {
            im_jp = !im_jp;
            if(im_jp)
                IM_ONEHAND_enable(2);
            else
                IM_ONEHAND_enable(1);
            send_im_mode_key(im_jp);
        }
    }

    if( ! process_record_local(keycode,record) )
        return false;

    if( !process_ONEHAND(keycode, record) )
        return false;

    return true;
}

