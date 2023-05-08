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
// MOD-TAP ALIASES
#define GUIT_A LGUI_T(KC_A)
#define SFTT_A LSFT_T(KC_A)
#define SFTT_Z LSFT_T(KC_Z)
#define GUIT_Z LGUI_T(KC_Z)
#define ALTT_S LALT_T(KC_S)
#define CTLT_D LCTL_T(KC_D)
#define SFTT_F LSFT_T(KC_F)
#define SFTT_J LSFT_T(KC_J)
#define CTLT_K LCTL_T(KC_K)
#define ALTT_L LALT_T(KC_L)
#define GUIT_SCL LGUI_T(KC_SCLN)
#define SFTT_M LSFT_T(KC_M)
#define CTL_CL LCTL_T(KC_COMM)
#define ALT_DT LALT_T(KC_DOT)
#define GUI_SLSH LGUI_T(KC_SLSH)
// NUMBER ROW MOD-TAP KEYS
#define F1_1 LT(_BASE, KC_1)
#define F2_2 LT(_BASE, KC_2)
#define F3_3 LT(_BASE, KC_3)
#define F4_4 LT(_BASE, KC_4)
#define F5_5 LT(_BASE, KC_5)
#define F6_6 LT(_BASE, KC_6)
#define F7_7 LT(_BASE, KC_7)
#define F8_8 LT(_BASE, KC_8)
#define F9_9 LT(_BASE, KC_9)
#define F0_0 LT(_BASE, KC_0)
/* REGIONS

N N N N N N E  E N N N N N N
L X X X X X E  E X X X X X R
L X X X X X E  E X X X X X R
L X X X X X      X X X X X R
m m m m m   T  T   m m m m m
        T T T  T T T
N
L,R
E
X Base row
T Thumb row
m Modifier row

X = (
Q W E R T  Y U I O P
A S D F G  H J K L ;
Z X C V B  N M , . /
)
*/

// QWERTY
//     |--------|--------|--------|--------|--------|
#define __________________NUMROW_L_________________ KC_1, KC_2, KC_3, KC_4, KC_5
#define __________________NUMROW_R_________________ KC_6, KC_7, KC_8, KC_9, KC_0
#define __________________FN_ROW_L_________________ KC_F1, KC_F2, KC_F3, KC_F4, KC_F5
#define __________________FN_ROW_R_________________ KC_F6, KC_F7, KC_F8, KC_F9, KC_F10
//     |--------|--------|--------|--------|--------|
#define __________________QWERTY_L1________________ LSFT_T(KC_Q), KC_W, KC_E, KC_R, KC_T
#define __________________QWERTY_L2________________ KC_A, KC_S, KC_D, KC_F, KC_G
#define __________________QWERTY_L3_SFTZ___________ SFTT_Z, KC_X, KC_C, KC_V, KC_B
#define __________________QWERTY_GUIZ_L3___________ LGUI_T(KC_Z), KC_X, KC_C, KC_V, KC_B

#define __________________QWERTY_L2_SFTA___________ SFTT_A, KC_S, KC_D, SFTT_F, KC_G
#define __________________QWERTY_L3________________ KC_Z, KC_X, KC_C, KC_V, KC_B
//     |--------|--------|--------|--------|--------|
#define __________________QWERTY_R1________________ KC_Y, KC_U, KC_I, KC_O, KC_P
#define __________________QWERTY_R2________________ KC_H, KC_J, KC_K, KC_L, KC_SCLN
#define __________________QWERTY_R3________________ KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH
//     |--------|--------|--------|--------|--------|
#define __________________QWERTY_HOME_L2___________ GUIT_A, ALTT_S, CTLT_D, SFTT_F, KC_G
#define __________________QWERTY_HOME_R2___________ KC_H, SFTT_J, CTLT_K, ALTT_L, KC_SCLN
#define __________________QWERTY_HOME_R3___________ KC_N, KC_M, LCTL_T(KC_COMM), LALT_T(KC_DOT), LGUI_T(KC_SLSH)
// different layout
#define __________________QWERTY_SACS_L2___________ SFTT_A, ALTT_S, CTLT_D, SFTT_F, KC_G
// process-intercepted keys

#define _IPC_A LT(_IPC, KC_A)
#define _IPC_S LT(_IPC, KC_S)
#define _IPC_D LT(_IPC, KC_D)
#define _IPC_C LT(_IPC, KC_C)
#define _IPC_F LT(_IPC, KC_F)
#define _IPC_Z LT(_IPC, KC_Z)
#define _IPC_MIN LCTL_T(KC_MINS)

#define IPC(x) LT(_IPC, KC_##x)
#define NAV(x) LT(_NAV, KC_##x)
#define IPC_MIN _IPC_MIN
#define IPC_COMM LSFT_T(KC_COMM)
#define _NUM_A LT(_NUM, KC_A)
#define _NUM_S LT(_NUM, KC_S)
#define _NUM_D LT(_NUM, KC_D)
#define _NUM_F LT(_NUM, KC_F)
#define _NUM_MIN LCTL_T(KC_MINS)

#define NUM(x) LT(_NUM, KC_##x)

#define BULLET_U C(S(KC_LBRC))
#define BULLET_D C(S(KC_RBRC))

// function keys
#define UNDO C(KC_Z)
#define CUT C(KC_X)
#define COPY C(KC_C)
#define PASTE C(KC_V)
#define BOLDFACE C(KC_B)
#define GUI_RGHT LSG(KC_RGHT)

#define CTRL_F1 C(KC_F1)
#define ALT_F4 A(KC_F4)
#define SCRNSHOT LSG(KC_S)
#define TO_BASE TO(_BASE)
#define TO_NOMOD TG(_BASE_NOMOD)
#define LT_NAV_0 LT(_NAV, KC_0)
#define MT_CAPS LALT_T(KC_CAPS)
#define SFT_CAPS LT(_BASE, KC_BTN1)

// NUMPAD
#define _________NUM_789_________ KC_7, KC_8, KC_9
#define _________NUM_456_________ KC_4, KC_5, KC_6
#define _________NUM_123_________ KC_1, KC_2, KC_3

// FUNCPAD
#define _____________FUNC_2789____________ KC_F12, KC_F7, KC_F8, KC_F9
#define _____________FUNC_1456____________ KC_F11, KC_F4, KC_F5, KC_F6
#define _____________FUNC_0123____________ KC_F10, KC_F1, KC_F2, KC_F3

// NUMROW

// TAP-HOLD CONFIG CONDITIONS
// ROW INDEX
// #if PRODUCT == Crkbd
//   #define ALPHA_QWERT 0 //AFTER NUMBER ROW
//   #define ALPHA_ASDFG 1 //AFTER NUMBER ROW
//   #define ALPHA_ZXCVB 2 //AFTER NUMBER ROW
// #else
//   #define NUMBR_12345 0 //NO NUMBER ROW
//   #define ALPHA_QWERT 1 //NO NUMBER ROW
//   #define ALPHA_ASDFG 2 //NO NUMBER ROW
//   #define ALPHA_ZXCVB 3 //NO NUMBER ROW
// #endif

// COLUMN INDEX
#define MOD_COL 0
#define ALPHA_QAZ 1
#define ALPHA_WSX 2
#define ALPHA_EDC 3
#define ALPHA_RFV 4
#define ALPHA_TGB 5

#define KEY_ROW record->event.key.row
#define KEY_COL record->event.key.col
#define __PRESSED__ record->event.pressed
#define __TAPPED__ record->tap.count
//#define __IF_PRESSED__ if(record->event.pressed){
//#define __IF_HELD__ if(record->event.pressed && !record->tap.count){
//#define __IF_RELEASED__ } else {

// wrapper layout
#define LAYOUT_crkbd_wrapper(...) LAYOUT_split_3x6_3(__VA_ARGS__)
#define LAYOUT_moonlander_wrapper(...) LAYOUT_moonlander(__VA_ARGS__)
#define LAYOUT_kimiko_wrapper(...) LAYOUT(__VA_ARGS__)
#define LAYOUT_ID75_wrapper(...) LAYOUT_ortho_5x15(__VA_ARGS__)

#define _ALT _BASE_NOMOD

// MOVED COMBO TO EACH KEYBOARDS

// Korean
bool user_debug;
bool prns_pressed; // 괄호입력상태
bool brkt_pressed;
bool num_in_prns; // 괄호 치고 번호를 입력한 경우
bool cite_done;
int  switch_cite;
int  user_i;
bool kca_pressed;
bool qwert;
// BASE KEYMAPS [3X5 + 3 THUMB KEYS]

#define __BASE_L1 __________________QWERTY_L1________________
#define __BASE_L2 __________________QWERTY_SACS_L2___________
#define __BASE_L3 __________________QWERTY_GUIZ_L3___________

#define __BASE_R1 __________________QWERTY_R1________________
#define __BASE_R2 __________________QWERTY_HOME_R2___________
#define __BASE_R3 __________________QWERTY_R3________________

#define __ALT_L1 __________________QWERTY_L1________________
#define __ALT_L2 __________________QWERTY_L2________________
#define __ALT_L3 __________________QWERTY_L3________________

#define __ALT_R1 __________________QWERTY_R1________________
#define __ALT_R2 __________________QWERTY_R2________________
#define __ALT_R3 __________________QWERTY_R3________________

#define __IPC_L1 HAEN_B, HAEN_C, HAEN_E, HAEN_D, KC_SLSH
#define __IPC_L2 IPC(A), IPC(S), IPC_MIN, IPC(F), KC_DOT
#define __IPC_L3 IPC(Z), BRKT, IPC(C), KC_EQL, KC_COLN

#define __IPC_R1 KC_LBRC, _________NUM_789_________, KC_RBRC
#define __IPC_R2 KC_GRV, _________NUM_456_________, KC_COLN
#define __IPC_R3 A(KC_2), _________NUM_123_________, _______

#define __NAV_L1 XXXXXXX, A(KC_7), A(KC_8), A(KC_9), KC_F6
#define __NAV_L2 XXXXXXX, KC_LALT, KC_LCTL, KC_LSFT, KC_F7
#define __NAV_L3 NAV(Z), C(KC_X), C(KC_C), C(KC_V), C(KC_B)

#define __NAV_R1 XXXXXXX, A(KC_1), A(KC_2), A(KC_3), XXXXXXX
#define __NAV_R2 KC_INS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
#define __NAV_R3 KC_APP, KC_HOME, KC_PGDN, KC_PGUP, KC_END

#define __MOUSE_L1 XXXXXXX, KC_WH_D, KC_MS_U, KC_WH_U, XXXXXXX
#define __MOUSE_L2 KC_LSFT, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX
#define __MOUSE_L3 UNDO, CUT, COPY, PASTE, BOLDFACE

#define __MOUSE_R1 XXXXXXX, KC_ACL2, XXXXXXX, XXXXXXX, XXXXXXX
#define __MOUSE_R2 KC_INS, KC_ACL0, KC_BTN1, KC_BTN2, KC_BTN3
#define __MOUSE_R3 KC_APP, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT

#define __FUNC_L1 RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX
#define __FUNC_L2 KC_LSFT, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX
#define __FUNC_L3 KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define __FUNC_R1 XXXXXXX, KC_F9, KC_F10, KC_F11, KC_F12
#define __FUNC_R2 XXXXXXX, KC_F5, KC_F6, KC_F7, KC_F8
#define __FUNC_R3 XXXXXXX, KC_F1, KC_F2, KC_F3, KC_F4

// Thumb keys
#define THUMB_L1 LCTL_T(KC_TAB)
#define THUMB_L2 LT(_IPC, KC_BSPC)
#define THUMB_L3 LT(_IPC, KC_DEL)

#define THUMB_R3 LT(_MOUSE, KC_ENT)
#define THUMB_R2 LT(_NAV, KC_SPC)
#define THUMB_R1 LT(_FUNC, KC_LNG1)

#define __BASE_LT THUMB_L1, THUMB_L2, LSFT_T(KC_DEL)
#define __BASE_RT THUMB_R3, THUMB_R2, THUMB_R1

#define __ALT_LT _______, LT(_IPC, KC_BSPC), LSFT_T(KC_DEL)
#define __ALT_RT _______, _______, _______

#define __NAV_LT BRKT, KC_BSPC, KC_DEL
#define __NAV_RT _______, KC_TRNS, _______

#define __IPC_LT _______, _______, _______
#define __IPC_RT _______, LT(_NAV, KC_0), _______

#define __MOUSE_LT KC_LCTL, KC_SPC, KC_ENT
#define __MOUSE_RT KC_TRNS, _______, _______

#define __FUNC_LT _______, _______, _______
#define __FUNC_RT _______, _______, KC_TRNS

// AUX KEYS E.G. NUM ROWS, FUNC ROW
#define __NONE XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define __IPC_L0 A62B18, E05C, E05B, KC_SLSH, XXXXXXX
#define __IPC_R0 KC_LT, KC_LPRN, KC_GRV, KC_RPRN, KC_GT
#define __NAV_L0 CTRL_F1, KC_F2, KC_F3, ALT_F4, KC_F5
#define __NAV_R0 KC_F6, KC_F7, KC_F8, KC_F9, KC_F10
#define __NUMROW_L KC_1, KC_2, KC_3, KC_4, KC_5
#define __NUMROW_R KC_6, KC_7, KC_8, KC_9, KC_0
#define __FN_ROW_L KC_F1, KC_F2, KC_F3, KC_F4, KC_F5
#define __FN_ROW_R KC_F6, KC_F7, KC_F8, KC_F9, KC_F10

#define __NUM_789 KC_7, KC_8, KC_9
#define __NUM_456 KC_4, KC_5, KC_6
#define __NUM_123 KC_1, KC_2, KC_3

enum custom_keycodes {
    PRNS = SAFE_RANGE,
    BRKT,
    ABRK,
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
    PDF_HL, // ADOBE PDF HIGHLIGHT MACRO
    JOINTBL,
    ENT_HOME,
    AT_IPC,
    HWP_CITE,
    CLASS_A,
    CLASS_E,
};

enum layer_index {
    _BASE = 0,       // QWERTY with home row mods
    _BASE_NOMOD,     // Just QWERTY
    _USER_MACRO, // SORIZAVA STENO 3-BEOL LAYOUT
    _NAV,            // Arrows
    _IPC,            //
    _NUM,
    _MOUSE,   //
    _FUNC,    //
    _ONEHAND, //
    _SETTINGS,
};
