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
//test commit
void appcmd(uint16_t keycode) {
    tap_code(KC_APP);
    tap_code(keycode);
}
//쌍자음 감지기
/*
    if keyrecord row가 doubleconsonants일 때
        corne: row 0
        lily58, kimiko, id75, moonlander: row 1
    save instaShift on
    else instaShift off

    다룰 조합들
    이따가  vs 임다가
        -dlaekrk
    QWERT 발동 조건

    임대    vs 이때
    이때    vs 이뗴
    dlEo - shift QWERT 다음에는 무조건 shift 해제

*/

// process_record_user
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_IPC, KC_BSPC):
        case LT(_NUM, KC_DEL):
            if (__PRESSED__) {
                prns_pressed = false;
                brkt_pressed = false;
                num_in_prns  = false;
                switch_cite  = 0;
                cite_done    = true;
            } else {
                if (num_in_prns) {
                    if(prns_pressed){tap_code(KC_RGHT);}
                    if(brkt_pressed){
                        cite_done = true;
                        tap_code(KC_RGHT);
                    }
                }
            }
            return true;
            break;

        case CLASS_A:
            if (__PRESSED__) {
                if (!cite_done) {
                    tap_code(KC_BSPC);
                    tap_code(KC_BSPC);
                    tap_code(KC_BSPC);
                    tap_code(KC_BSPC);
                }
                switch (switch_cite) {
                    case 0:
                        SEND_STRING("A62B");
                        switch_cite = 1;
                        break;
                    case 1:
                        SEND_STRING("A41D");
                        switch_cite = 0;
                        break;
                }
            } else {
                cite_done = false;
            }
            break;
        case CLASS_E:
            if (__PRESSED__) {
                if (!cite_done) {
                    tap_code(KC_BSPC);
                    tap_code(KC_BSPC);
                    tap_code(KC_BSPC);
                    tap_code(KC_BSPC);
                }
                switch (switch_cite) {
                    case 0:
                        SEND_STRING("E05B");
                        switch_cite = 1;
                        break;
                    case 1:
                        SEND_STRING("E05C");
                        switch_cite = 2;
                        break;
                    case 2:
                        SEND_STRING("E05G");
                        switch_cite = 3;
                        break;
                    case 3:
                        SEND_STRING("E06B");
                        switch_cite = 0;
                        break;
                }
            } else {
                cite_done = false;
            }
            break;

            // appcmd function
        case JOINTBL:
            if (__PRESSED__) {
                appcmd(KC_J);
            }
            break;

        case PDF_HL:
            if (__PRESSED__) {
                appcmd(KC_H);
            }
            break;

#ifdef RGBLIGHT_ENABLE
        case TO_NOMOD:
            if (__PRESSED__) {
                rgblight_setrgb(0, 0, 50);
            }
            return true;
        case TO_BASE:
            if (__PRESSED__) {
                rgblight_setrgb(RGB_OFF);
            }
            return true;
#endif
            // 괄호 커서이동 기능
        case KC_COMM:
            if (__PRESSED__ /* && (brkt_pressed||prns_pressed)*/) {
                cite_done = true;
            }
            return true;
        case KC_1 ... KC_0:
            if (__PRESSED__ && (prns_pressed || brkt_pressed)) {
                num_in_prns = true;
                cite_done   = true;
            }
            return true;
            break;
        // HWP_CITE
        case HWP_CITE:
            // prns 안에서는 cite_done = false
            // comma 누르면 cite_done = true
            // prns && num 상태에서는 cite_done = true, SPC_COMM
            if (__PRESSED__) {
                switch (switch_cite) {
                    case 0:
                        if (!cite_done) {
                            user_i = 0;
                            while (user_i < 2) {
                                tap_code(KC_BSPC);
                                user_i++;
                            }
                        }
                        if (!brkt_pressed) {
                            SEND_STRING("[]" SS_TAP(X_LEFT));
                            brkt_pressed = true;
                        }
                        switch_cite = 3;
                        break;
                    case 3:
                        SEND_STRING("anseks ");
                        switch_cite = 4;
                        cite_done   = false;
                        break;
                    case 4:
                        if (!cite_done) {
                            user_i = 0;
                            while (user_i < 3) {
                                tap_code(KC_BSPC);
                                user_i++;
                            }
                        }
                        if (brkt_pressed && num_in_prns) {
                            SEND_STRING(", ");
                            num_in_prns = false;
                        }
                        SEND_STRING("cjdrngkd ");
                        switch_cite = 2;
                        cite_done   = false;
                        break;
                    case 2:
                        if (!cite_done) {
                            user_i = 0;
                            while (user_i < 4) {
                                tap_code(KC_BSPC);
                                user_i++;
                            }
                        }
                        if (brkt_pressed && num_in_prns) {
                            SEND_STRING(", ");
                            num_in_prns = false;
                        }
                        SEND_STRING("eh ");
                        switch_cite = 0;
                        cite_done   = false;
                        break;
                }
            }
            break;
            // Intercept mod-tap
        case IPC(A):
            if (__TAPPED__ && __PRESSED__) {
                SEND_STRING(SS_TAP(X_LNG1) SS_TAP(X_A) SS_TAP(X_LNG1));
                // tap_code(KC_A);
            } else if (__PRESSED__) {
                register_code(KC_LSFT);
            } else {
                unregister_code(KC_LSFT);
            }
            return false;
            break;

        case IPC(S):
            if (__TAPPED__ && __PRESSED__) {
                SEND_STRING("()" SS_TAP(X_LEFT));
                prns_pressed = true;
            } else if (__PRESSED__) {
                register_code(KC_LALT);
            } else {
                unregister_code(KC_LALT);
            }
            return false;
            break;
        case IPC(F):
            if (__TAPPED__ && __PRESSED__) {
                SEND_STRING(", ");
            } else if (__PRESSED__) {
                register_code(KC_LSFT);
            } else {
                unregister_code(KC_LSFT);
            }
            return false;
            break;

        case IPC(Z):
            if (__TAPPED__ && __PRESSED__) {
                tap_code16(SCRNSHOT);
            } else if (__PRESSED__) {
                register_code(KC_LGUI);
            } else {
                unregister_code(KC_LGUI);
            }
            return false;
            break;

        case IPC(C):
            if (__TAPPED__ && __PRESSED__) {
                tap_code16(KC_UNDS);
            } else if (__PRESSED__) {
                tap_code16(KC_EQL);
            }
            return false;
            break;

        case NAV(Z):
            if (__TAPPED__ && __PRESSED__) {
                tap_code16(C(KC_Z));
            } else if (__PRESSED__) {
                register_code(KC_LGUI);
            } else {
                unregister_code(KC_LGUI);
            }
            return false;
            break;

        case SFT_CAPS:
            if (__TAPPED__ && __PRESSED__) {
                tap_code16(KC_BTN1);
            } else if (__PRESSED__) {
                register_code(KC_BTN4);
            } else {
                unregister_code(KC_BTN4);
            }
            return false;
            break;


        case THUMB_L3:
            if (__TAPPED__ && __PRESSED__) {
                tap_code16(KC_DEL);
            } else if (__PRESSED__) {
                register_code(KC_BTN4);
            } else {
                unregister_code(KC_BTN4);
            }
            return false;
            break;

        // CLOSING BRACKET PAIRS
        case BRKT:
            if (__PRESSED__) {
                SEND_STRING("[]" SS_TAP(X_LEFT));
                brkt_pressed = true; // 괄호입력상태
            }
            break;
        case ABRK:
            if (__PRESSED__) {
                SEND_STRING("<>" SS_TAP(X_LEFT));
                prns_pressed = true; // 괄호입력상태
            }
            break;

        case CMM_SPC:
            if (__PRESSED__) {
                SEND_STRING(", ");
            }
            break;
        case CLN_SPC:
            if (__PRESSED__) {
                SEND_STRING(": ");
            }
            break;
        case ENT_HOME:
            if (__PRESSED__) {
                tap_code(KC_ENT);
                layer_move(_BASE);
            }
            break;
        case AT_IPC:
            if (__PRESSED__) {
                SEND_STRING("@IPC");
            }
            break;
            // case SLSH_LL:
            //     if (__PRESSED__) {
            //         SEND_STRING(SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_SLSH) SS_TAP(X_RGHT) SS_TAP(X_RGHT));
            //     }
            //     break;
    }
    return true;
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GUIT_Z:
            return TAPPING_TERM + 200;
        case THUMB_L2:
        case SFTT_A:
            return TAPPING_TERM - 170;
        case SFTT_F:
        case SFTT_J:
        case GUIT_A:
        case GUIT_SCL:
            return TAPPING_TERM + 50;
        case NAV(S):
        case NAV(D):
        case NAV(F):
            return TAPPING_TERM - 100;
        default:
            return TAPPING_TERM;
    }
}
// Get hold on other key press
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record){
    switch (keycode) {
        // case SFTT_A:
            return true;
        default:
            return false;
    }
}
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case IPC(Z):
        case THUMB_L1:
        case THUMB_L2:
        case THUMB_L3:
        case THUMB_R1:

        case THUMB_R3:
        case SFT_CAPS:
        // case SFTT_A:
        // case SFTT_Z:
        // case GUIT_Z:
        // case SFTT_F:
        // case SFTT_J:
        // case ALTT_S:
        // case CTLT_D:
        // case GUIT_SCL:
        // case ALTT_L:
        // case CTLT_K:
        // case GUIT_A:
        // case LT(_NAV, KC_0):
        // case IPC_COMM:
            return true;
        default:
            return false;
    }
}


