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

#include QMK_KEYBOARD_H
//#include <stdio.h> 
//MOD-TAP ALIASES
#define GUIT_A    LGUI_T(KC_A)
#define SFTT_A    LSFT_T(KC_A)
#define SFTT_Z    LSFT_T(KC_Z)
#define ALTT_S    LALT_T(KC_S)
#define CTLT_D    LCTL_T(KC_D)
#define SFTT_F    LSFT_T(KC_F)
#define SFTT_J    LSFT_T(KC_J)
#define CTLT_K    LCTL_T(KC_K)
#define ALTT_L    LALT_T(KC_L)
#define GUIT_SCL  LGUI_T(KC_SCLN)


//NUMBER ROW MOD-TAP KEYS
#define F1_1  LT(_BASE,KC_1)
#define F2_2  LT(_BASE,KC_2)
#define F3_3  LT(_BASE,KC_3)
#define F4_4  LT(_BASE,KC_4)
#define F5_5  LT(_BASE,KC_5)
#define F6_6  LT(_BASE,KC_6)
#define F7_7  LT(_BASE,KC_7)
#define F8_8  LT(_BASE,KC_8)
#define F9_9  LT(_BASE,KC_9)
#define F0_0  LT(_BASE,KC_0)


//Mod-tap macro
//#define LGACS_T(A,B,C,D,E) LGUI_T(A), LALT_T(B), LCTL_T(C), LSFT_T(D), E
//#define RGACS_T(A,B,C,D,E) RGUI_T(A), LALT_T(B), RCTL_T(C), RSFT_T(D), E
// LAYOUT WRAPPER

//QWERTY
//     |--------|--------|--------|--------|--------|
#define __________________NUMROW_L_________________ F1_1, F2_2, F3_3, F4_4, F5_5
#define __________________NUMROW_R_________________ F6_6, F7_7, F8_8, F9_9, F0_0
//     |--------|--------|--------|--------|--------|
#define __________________QWERTY_L1________________ KC_Q, KC_W, KC_E, KC_R, KC_T 
#define __________________QWERTY_L2________________ KC_A, KC_S, KC_D, KC_F, KC_G
#define __________________QWERTY_L3_SFTZ___________ SFTT_Z, KC_X, KC_C, KC_V, KC_B

#define __________________QWERTY_L2_SFTA___________ SFTT_A, KC_S, KC_D, KC_F, KC_G
#define __________________QWERTY_L3________________ KC_Z, KC_X, KC_C, KC_V, KC_B
//     |--------|--------|--------|--------|--------|
#define __________________QWERTY_R1________________ KC_Y, KC_U, KC_I, KC_O, KC_P
#define __________________QWERTY_R2________________ KC_H, KC_J, KC_K, KC_L, KC_SCLN
#define __________________QWERTY_R3________________ KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH
//     |--------|--------|--------|--------|--------|
#define __________________QWERTY_HOME_L2___________ GUIT_A,  ALTT_S,  CTLT_D,  SFTT_F,  KC_G
#define __________________QWERTY_HOME_R2___________ KC_H,    SFTT_J,  CTLT_K,  ALTT_L,  GUIT_SCL
// different layout 
#define __________________QWERTY_SACS_L2___________ SFTT_A,  ALTT_S,  CTLT_D,  SFTT_F,  KC_G

//process-intercepted keys
#define _IPC_A    LT(_IPC,KC_A)
#define _IPC_S    LT(_IPC,KC_S)
#define _IPC_D    LT(_IPC,KC_D)
#define _IPC_F    LT(_IPC,KC_F)
#define _IPC_Z    LT(_IPC,KC_Z)
#define _IPC_MIN  LCTL_T(KC_MINS)

#define _NUM_A    LT(_NUM,KC_A)
#define _NUM_S    LT(_NUM,KC_S)
#define _NUM_D    LT(_NUM,KC_D)
#define _NUM_F    LT(_NUM,KC_F)
#define _NUM_MIN  LCTL_T(KC_MINS)

#define BULLET_U  C(S(KC_LBRC))
#define BULLET_D  C(S(KC_RBRC))


// Thumb keys 
#define THUMB_L1  LCTL_T(KC_TAB)
#define THUMB_L2  LT(_IPC,KC_BSPC)
#define THUMB_L3  LT(_ONEHAND,KC_DEL)
#define THUMB_R3  LT(_MOUSE,KC_ENT)
#define THUMB_R2  LT(_NAV,KC_SPC)
#define THUMB_R1  LT(_FUNC,KC_HAEN)

// function keys
#define UNDO      C(KC_Z)
#define CUT       C(KC_X)
#define COPY      C(KC_C)
#define PASTE     C(KC_V)
#define BOLDFACE  C(KC_B)
#define GUI_RGHT G(KC_RGHT)

#define CTRL_F1   C(KC_F1)
#define ALT_F4    A(KC_F4)
#define SCRNSHOT  LSG(KC_S)
#define TO_BASE   TO(_BASE)
//NAV ROWS
// #define NAV_L1    
// #define NAV_L2
// #define NAV_L3
// #define NAV_R1
// #define NAV_R2
// #define NAV_R3
#define LT_NAV_0 LT(_NAV,KC_0)
#define MT_CAPS  LALT_T(KC_CAPS)
#define SFT_CAPS  LSFT_T(KC_CAPS)
//NUMPAD
#define _________NUM_789_________ KC_7, KC_8, KC_9
#define _________NUM_456_________ KC_4, KC_5, KC_6
#define _________NUM_123_________ KC_1, KC_2, KC_3
//FUNCPAD
        
#define _____________FUNC_2789____________ KC_F12, KC_F7, KC_F8, KC_F9
#define _____________FUNC_1456____________ KC_F11, KC_F4, KC_F5, KC_F6 
#define _____________FUNC_0123____________ KC_F10, KC_F1, KC_F2, KC_F3
//NUMROW


//wrapper layout
#define LAYOUT_crkbd_wrapper(...) LAYOUT_split_3x6_3(__VA_ARGS__)
#define LAYOUT_moonlander_wrapper(...) LAYOUT_MOONLANDER(__VA_ARGS__)
#define LAYOUT_kimiko_wrapper(...) LAYOUT(__VA_ARGS__)

enum custom_keycodes{
  PRNS = SAFE_RANGE,
  BRKT,
  CMM_SPC,
  CLN_SPC,
  SLSH_LL,
  NEXT_LNE, 
  HAEN_A,
  HAEN_B,
  HAEN_C,
  HAEN_D,
  HAEN_E,
  HAEN_F,
  HAEN_G,
};

enum layer_index{
  _BASE=0,      // QWERTY with home row mods
  _BASE_NOMOD,  // Just QWERTY
  _NUM,         // No use ==> HWP 전용으로 사용예정
  _NAV,         // Arrows
  _IPC,         // 
  _MOUSE,       //
  _FUNC,        //
  _ONEHAND,     // 
  _SETTINGS,
};

// COMBOS
enum combos {
    BM_NOMOD,
    BN_HMMOD,
    WE_ONEHAND,
    NM_KC_B,
};

// Korean
extern bool prns_pressed; // 괄호입력상태
extern bool num_in_prns; // 괄호 치고 번호를 입력한 경우
