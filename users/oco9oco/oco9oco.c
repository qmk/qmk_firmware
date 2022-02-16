/*
Copyright 2022 oco9oco <oco9oco@gmail.com>
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
#include "oco9oco.h"

void haen_keycode(uint16_t keycode){
    tap_code(KC_HAEN);
    tap_code(keycode);
    tap_code(KC_HAEN);
}
// process_record_user
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case F1_1:
            if(record->tap.count && record->event.pressed){
                tap_code(KC_1);
            }else if(record->event.pressed) {
                tap_code16(C(KC_F1));
            }
            return false;
            break;
        case F2_2:
            if(record->tap.count && record->event.pressed){
                tap_code(KC_2);
            }else if(record->event.pressed) {
                tap_code16(C(KC_F2));
            }
            return false;
            break;
        case F3_3:
            if(record->tap.count && record->event.pressed){
                tap_code(KC_3);
            }else if(record->event.pressed) {
                tap_code16(C(KC_F3));
            }
            return false;
            break;
        case F4_4:
            if(record->tap.count && record->event.pressed){
                tap_code(KC_4);
            }else if(record->event.pressed) {
                tap_code16(C(A(KC_F4)));
            }
            return false;
            break;
        case F5_5:
            if(record->tap.count && record->event.pressed){
                tap_code(KC_5);
            }else if(record->event.pressed) {
                tap_code16(C(KC_F5));
            }
            return false;
            break;
        case F6_6:
            if(record->tap.count && record->event.pressed){
                tap_code(KC_6);
            }else if(record->event.pressed) {
                tap_code16(C(KC_F6));
            }
            return false;
            break;
        case F7_7:
            if(record->tap.count && record->event.pressed){
                tap_code(KC_7);
            }else if(record->event.pressed) {
                tap_code16(C(KC_F7));
            }
            return false;
            break;
        case F8_8:
            if(record->tap.count && record->event.pressed){
                tap_code(KC_8);
            }else if(record->event.pressed) {
                tap_code16(C(KC_F8));
            }
            return false;
            break;
        case F9_9:
            if(record->tap.count && record->event.pressed){
                tap_code(KC_9);
            }else if(record->event.pressed) {
                tap_code16(C(KC_F9));
            }
            return false;
            break;
        case F0_0:
            if(record->tap.count && record->event.pressed){
                tap_code(KC_0);
            }else if(record->event.pressed) {
                tap_code16(C(KC_F10));
            }
            return false;
            break;

// HAEN_A ... HAEN_G
        case HAEN_A:
            if (record->event.pressed) {
                haen_keycode(KC_A);
            }
            break;
        case HAEN_B:
            if (record->event.pressed) {
                haen_keycode(KC_B);
            }
            break;
        case HAEN_C:
            if (record->event.pressed) {
                haen_keycode(KC_C);
            }
            break;
        case HAEN_D:
            if (record->event.pressed) {
                haen_keycode(KC_D);
            }
            break;
        case HAEN_E:
            if (record->event.pressed) {
                haen_keycode(KC_E);
            }
            break;
        case HAEN_F:
            if (record->event.pressed) {
                haen_keycode(KC_F);
            }
            break;
        case HAEN_G:
            if (record->event.pressed) {
                haen_keycode(KC_G);
            }
            break;
// 괄호 커서이동 기능
        case LT(_IPC, KC_BSPC):
        case LT(_NUM, KC_DEL):
            if (record->event.pressed) {
                prns_pressed = false;
                num_in_prns  = false;
            } else {
                if (prns_pressed && num_in_prns) {
                    SEND_STRING(SS_TAP(X_RGHT));
                }
            }
            break;            
        case KC_1 ... KC_0:
            if (record->event.pressed && prns_pressed) {
                num_in_prns = true;
            } return true;
            
// Intercept mod-tap
        case _IPC_A:
            if(record->tap.count && record->event.pressed){
                SEND_STRING(SS_TAP(X_HAEN) SS_TAP(X_A) SS_TAP(X_HAEN));
            }else if(record->event.pressed) {
                register_code(KC_LGUI);
            }else{
                unregister_code(KC_LGUI);
            }
            return false;
            break;

        case _IPC_S:
            if(record->tap.count && record->event.pressed){
                SEND_STRING("()" SS_TAP(X_LEFT));
                prns_pressed = true;
            }else if(record->event.pressed) {
                register_code(KC_LALT);
            }else{
                unregister_code(KC_LALT);
            }
            return false;
            break;
       
        case _IPC_F:
            if(record->tap.count && record->event.pressed){
                SEND_STRING(", ");
            }else if(record->event.pressed) {
                register_code(KC_LSFT);
            }else{
                unregister_code(KC_LSFT);
            }
            return false;
            break;
        case _IPC_Z:
            if (record->tap.count && record->event.pressed) {
                tap_code16(C(KC_Z));
            } else if (record->event.pressed) {
                register_code(KC_LSFT);
            } else {unregister_code(KC_LSFT);}
            return false;

        case BRKT:
            if (record->event.pressed) {
                SEND_STRING("[]" SS_TAP(X_LEFT));
                prns_pressed = true;  // 괄호입력상태
            }
            break;
        case CMM_SPC:
            if (record->event.pressed) {
                SEND_STRING(", ");
            }
            break;
        case CLN_SPC:
            if (record->event.pressed) {
                SEND_STRING(": ");
            }
            break;
        // case SLSH_LL:
        //     if (record->event.pressed) {
        //         SEND_STRING(SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_SLSH) SS_TAP(X_RGHT) SS_TAP(X_RGHT));
        //     }
        //     break;
    }
    return true;
};
