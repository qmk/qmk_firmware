/* Copyright 2020 Terence Rudkin
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

bool leader_succeeded;
#define WRAP_SELECTION(st)  SEND_STRING(SS_LCTL(SS_TAP(X_X)) st SS_TAP(X_LEFT) SS_LCTL(SS_TAP(X_V)) SS_TAP(X_RIGHT))


#define CUA_CUT     register_code (KC_LSFT); register_code (KC_DEL);unregister_code (KC_DEL); unregister_code (KC_LSFT)
#define CUA_COPY    register_code (KC_LCTL); register_code (KC_DEL);unregister_code (KC_DEL); unregister_code (KC_LCTL)
#define CUA_PASTE   register_code (KC_LSFT); register_code (KC_INS);unregister_code (KC_INS); unregister_code (KC_LSFT)


LEADER_EXTERNS();

void matrix_scan_user(void) {


    LEADER_DICTIONARY() {
    leader_succeeded = leading = false;

    SEQ_ONE_KEY(KC_EQL){
        SEND_STRING("+=");
        leader_succeeded = true;
    }
    SEQ_ONE_KEY(KC_SLSH){
        CUA_CUT;
        SEND_STRING("*/");
        tap_code16(KC_LEFT);
        tap_code16(KC_LEFT);
        SEND_STRING("/*");
        CUA_PASTE;
         tap_code16(KC_RIGHT);
         tap_code16(KC_RIGHT);
    }
    SEQ_ONE_KEY(KC_T) {
      
      SEND_STRING(SS_LCTL(SS_LSFT("t")));
      leader_succeeded = true;
    } 
    SEQ_ONE_KEY(KC_9) {
      
      SEND_STRING("{");
      leader_succeeded = true;
    } 
    SEQ_ONE_KEY(KC_0) {
      
      SEND_STRING("}");
      leader_succeeded = true;
    } 
    SEQ_ONE_KEY(KC_COMM) {
      
      SEND_STRING("[");
      leader_succeeded = true;
    } 
    SEQ_ONE_KEY(KC_DOT) {
      
      SEND_STRING("]");
      leader_succeeded = true;
    } 
    SEQ_ONE_KEY(KC_TAB) {
        tap_code16(KC_INS);
      leader_succeeded = true;
    } 
    SEQ_ONE_KEY(KC_LEAD) {
      tap_code16(KC_DEL);   
      leader_succeeded = true;
    } 
    SEQ_ONE_KEY(KC_Z) {
        WRAP_SELECTION("()");
      leader_succeeded = true;
    } 
    SEQ_ONE_KEY(KC_B) {
        register_code (KC_LCTL); 
        register_code (KC_B); 

        unregister_code (KC_B);
        unregister_code (KC_LCTL);
        register_code (KC_ESC);  
        unregister_code (KC_ESC);
  
      leader_succeeded = true;
    } 
    SEQ_ONE_KEY(KC_C) {
        CUA_CUT;
        SEND_STRING("()");
        tap_code16(KC_LEFT);
        CUA_PASTE;
         tap_code16(KC_RIGHT);
      leader_succeeded = true;
    } 
    SEQ_THREE_KEYS(KC_C,KC_A,KC_D) {
        tap_code16(C(A(KC_DEL)));
    }
    SEQ_TWO_KEYS(KC_E, KC_D) {
      SEND_STRING(SS_LGUI("r") "cmd\n" SS_LCTL("c"));
      leader_succeeded = true;
    } 
    SEQ_TWO_KEYS(KC_DOT, KC_DOT) { 
      SEND_STRING("=>");
      leader_succeeded = true;
    }
    SEQ_TWO_KEYS(KC_COMM, KC_COMM) { 
      SEND_STRING("<=");
      leader_succeeded = true;
    }
    SEQ_THREE_KEYS(KC_D,KC_D,KC_G){
        SEND_STRING("https://duckduckgo.com/");
        leader_succeeded = true;
    }

   /*  ``` => LdrKey > Escape > Escape > Escape */
   SEQ_THREE_KEYS(KC_GESC, KC_GESC, KC_GESC) { 
        SEND_STRING("```");
   }
    leader_end();
  }



}







void leader_start(void) {
 rgblight_setrgb_range(200, 200, 255, 0, 9); 
}

void leader_end(void) {
  if (leader_succeeded) {
     rgblight_blink_layer(1,500);
  } else {
       rgblight_setrgb_range(255,0,0 , 0, 9);
  }
}

