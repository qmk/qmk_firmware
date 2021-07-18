#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "keymap_german_osx.h"

#define BASE 0
#define SYMB 1
#define MDIA 2
#define SMLY 3
#define NUMB 4
#define EGOS 5

#define M_CTRL_CMDV 0
#define M_CTRL_CMDC 1
#define M_MEH_SH_ACUT 2
#define M_LGUI_SHFT 3
#define M_CTL_SFT_HASH 4
#define M_DE_OSX_CIRC_CTRLCMD 5
#define M_DE_OSX_PLUS_CTRLALT 6
#define SM_SMILE 7
#define SM_SMIRK 8
#define SM_CRY 9
#define SM_SAD 10
#define SM_HEART 11
#define SM_LAUGH 12
#define SM_KISS 13
#define SM_FROWN 14
#define M_TOGGLE_5 15

//Layout keymap.c generated with ErgodoxLayoutGenerator V1.0BETA1
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE]=LAYOUT_ergodox(
//left half
    KC_ESC, DE_OSX_1, DE_OSX_2, DE_OSX_3, DE_OSX_4, DE_OSX_5, M(M_CTL_SFT_HASH), 
    KC_TAB, DE_OSX_Q, DE_OSX_W, DE_OSX_E, DE_OSX_R, DE_OSX_T, KC_LGUI, 
    KC_LALT, DE_OSX_A, DE_OSX_S, DE_OSX_D, DE_OSX_F, DE_OSX_G, 
    KC_LSFT, CTL_T(DE_OSX_Y), DE_OSX_X, DE_OSX_C, DE_OSX_V, DE_OSX_B, KC_LALT, 
                  LT(SYMB,DE_OSX_LESS), M(M_DE_OSX_CIRC_CTRLCMD), M(M_DE_OSX_PLUS_CTRLALT), KC_UP, KC_DOWN, 
                                              M(M_MEH_SH_ACUT), TG(MDIA), 
                                                     KC_HOME, 
                                       KC_BSPC, KC_DEL, LT(SMLY,KC_END), 
    //right half
    M(M_CTL_SFT_HASH), DE_OSX_6, DE_OSX_7, DE_OSX_8, DE_OSX_9, DE_OSX_0, DE_OSX_SS, 
    KC_RGUI, DE_OSX_Z, DE_OSX_U, DE_OSX_I, DE_OSX_O, DE_OSX_P, DE_OSX_UE, 
           DE_OSX_H, DE_OSX_J, DE_OSX_K, DE_OSX_L, DE_OSX_OE, ALT_T(DE_OSX_AE), 
    KC_RALT, DE_OSX_N, DE_OSX_M, DE_OSX_COMM, DE_OSX_DOT, CTL_T(DE_OSX_MINS), KC_RSFT, 
                         KC_LEFT, KC_RIGHT, LGUI(KC_LSFT), LALT(KC_LSFT), LT(SYMB,DE_OSX_PLUS), 
    TG(NUMB), ALL_T(DE_OSX_ACUT), 
    KC_PGUP, 
    KC_PGDN, KC_ENT, KC_SPC),
[SYMB]=LAYOUT_ergodox(
//left half
    KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_TRNS, 
    KC_TRNS, DE_OSX_LESS, DE_OSX_MORE, DE_OSX_EXLM, DE_OSX_QST, KC_TRNS, KC_TRNS, 
    KC_TRNS, DE_OSX_HASH, DE_OSX_DLR, DE_OSX_BSLS, DE_OSX_SLSH, KC_DOT, 
    KC_TRNS, KC_TRNS, DE_OSX_LESS, DE_OSX_PERC, DE_OSX_PIPE, DE_OSX_TILD, KC_TRNS, 
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
                                              KC_TRNS, KC_TRNS, 
                                                     KC_TRNS, 
                                       KC_TRNS, KC_DEL, KC_TRNS, 
    //right half
    M(M_TOGGLE_5), KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, 
    KC_TRNS, LALT(LSFT(KC_7)), LALT(KC_5), LALT(KC_6), DE_OSX_LESS, DE_OSX_MORE, DE_OSX_EXLM, 
           DE_OSX_SLSH, DE_OSX_LPRN, DE_OSX_RPRN, LALT(KC_8), LALT(KC_9), DE_OSX_HASH, 
    KC_TRNS, DE_OSX_PIPE, DE_OSX_TILD, DE_OSX_CIRC, KC_UP, DE_OSX_MINS, LSFT(KC_4), 
                         DE_OSX_QUOT, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, 
    KC_F13, KC_F12, 
    KC_F14, 
    KC_F15, KC_TRNS, KC_TRNS),
[MDIA]=LAYOUT_ergodox(
//left half
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, 
    KC_TRNS, KC_TRNS, KC_WH_L, KC_WH_D, KC_WH_R, KC_BTN3, KC_TRNS, 
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
                                              KC_TRNS, KC_TRNS, 
                                                     KC_TRNS, 
                                       KC_TRNS, KC_TRNS, KC_TRNS, 
    //right half
    KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
           KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_VOLD, KC_TRNS, KC_MPRV, KC_MNXT, KC_UP, KC_TRNS, 
                         KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, 
    KC_TRNS, KC_TRNS, 
    KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_WBAK),
[SMLY]=LAYOUT_ergodox(
//left half
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
                                              KC_TRNS, KC_TRNS, 
                                                     KC_TRNS, 
                                       KC_TRNS, KC_TRNS, KC_TRNS, 
    //right half
    M(SM_SMILE), M(SM_SMIRK), M(SM_LAUGH), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, M(SM_FROWN), M(SM_SAD), M(SM_CRY), KC_TRNS, KC_TRNS, KC_TRNS, 
           M(SM_HEART), M(SM_KISS), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, 
    KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS),
[NUMB]=LAYOUT_ergodox(
//left half
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
                                              KC_TRNS, KC_TRNS, 
                                                     KC_TRNS, 
                                       KC_TRNS, KC_TRNS, KC_TRNS, 
    //right half
    KC_TRNS, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, 
    KC_TRNS, KC_UP, KC_7, KC_8, KC_9, LSFT(KC_RBRC), KC_F12, 
           KC_DOWN, KC_4, KC_5, KC_6, KC_RBRC, DE_OSX_MINS, 
    KC_TRNS, LSFT(KC_6), KC_1, KC_2, KC_3, LSFT(KC_7), KC_TRNS, 
                         KC_0, KC_DOT, KC_COMM, DE_OSX_EQL, KC_TRNS, 
    KC_TRNS, KC_TRNS, 
    KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS),
[EGOS]=LAYOUT_ergodox(
//left half
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
                  KC_LCTL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
                                              KC_F1, KC_F2, 
                                                     KC_F3, 
                                       KC_SPC, KC_LCTL, KC_F4, 
    //right half
    M(M_TOGGLE_5), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, 
    KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
static uint16_t start;
switch(id) {
case M_TOGGLE_5:
//Macro: M_TOGGLE_5//-----------------------
 if (record->event.pressed){
           layer_state ^= (1<<5);
           layer_state &= (1<<5);
        }

break;
case M_CTRL_CMDC:
//Macro: M_CTRL_CMDC//-----------------------
if (record->event.pressed) {
			start = timer_read();
			return MACRO(D(LCTRL),END);
		} else {
			if (timer_elapsed(start) >150) {
				return MACRO(U(LCTRL),END);
			} else {
				return MACRO(U(LCTRL),D(LGUI),T(C),U(LGUI),END);
			}
		}

break;
case M_DE_OSX_PLUS_CTRLALT:
//Macro: M_DE_OSX_PLUS_CTRLALT//-----------------------
if (record->event.pressed) {
			start = timer_read();
			return MACRO(D(LCTRL),D(LALT),END);
		} else {
			if (timer_elapsed(start) >150) {
				return MACRO(U(LCTRL),U(LALT),END);
			} else {
				return MACRO(U(LCTRL),U(LALT),T(RBRC),END);
			}
		}

break;
case SM_KISS:
//Macro: SM_KISS//-----------------------
if (record->event.pressed) {
			return MACRO(D(LSFT),T(DOT),U(LSFT),T(SLSH),D(LSFT),T(RBRC),U(LSFT),END);
		}

break;
case SM_FROWN:
//Macro: SM_FROWN//-----------------------
if (record->event.pressed) {
			return MACRO(D(LSFT),T(DOT),U(LSFT),T(SLSH),D(LALT),T(8),U(LALT),END);
		}

break;
case SM_CRY:
//Macro: SM_CRY//-----------------------
if (record->event.pressed) {
			return MACRO(D(LSFT),T(COMM),U(LSFT),T(SLSH),D(LSFT),T(8),U(LSFT),END);
		}

break;
case SM_SMILE:
//Macro: SM_SMILE//-----------------------
if (record->event.pressed) {
			return MACRO(D(LSFT),T(DOT),U(LSFT),T(SLSH),D(LSFT),T(9),U(LSFT),END);
		}

break;
case SM_SMIRK:
//Macro: SM_SMIRK//-----------------------
if (record->event.pressed) {
			return MACRO(D(LSFT),T(COMM),U(LSFT),T(SLSH),D(LSFT),T(9),U(LSFT),END);
		}

break;
case M_LGUI_SHFT:
//Macro: M_LGUI_SHFT//-----------------------
if (record->event.pressed){
			return MACRO(D(LGUI),D(LSFT),END);
		}else{
			return MACRO(U(LGUI),U(LSFT),END);
		}

break;
case SM_HEART:
//Macro: SM_HEART//-----------------------
if (record->event.pressed) {
			return MACRO(T(GRV),T(3),END);
		}

break;
case SM_LAUGH:
//Macro: SM_LAUGH//-----------------------
if (record->event.pressed) {
			return MACRO(D(LSFT),T(DOT),U(LSFT),T(SLSH),D(LSFT),T(D),U(LSFT),END);
		}

break;
case M_CTL_SFT_HASH:
//Macro: M_CTL_SFT_HASH//-----------------------
if (record->event.pressed) {
			start = timer_read();
			return MACRO(D(LCTRL),D(LSFT),END);
		} else {
			if (timer_elapsed(start) >150) {
				return MACRO(U(LCTRL),U(LSFT),END);
			} else {
				return MACRO(U(LCTRL),U(LSFT),T(BSLS),END);
			}
		}

break;
case SM_SAD:
//Macro: SM_SAD//-----------------------
if (record->event.pressed) {
			return MACRO(D(LSFT),T(DOT),U(LSFT),T(SLSH),D(LSFT),T(8),U(LSFT),END);
		}

break;
case M_DE_OSX_CIRC_CTRLCMD:
//Macro: M_DE_OSX_CIRC_CTRLCMD//-----------------------
if (record->event.pressed) {
			start = timer_read();
			return MACRO(D(LCTRL),D(LGUI),END);
		} else {
			if (timer_elapsed(start) >150) {
				return MACRO(U(LCTRL),U(LGUI),END);
			} else {
				return MACRO(U(LCTRL),U(LGUI),T(NUBS),END);
			}
		}

break;
case M_CTRL_CMDV:
//Macro: M_CTRL_CMDV//-----------------------
if (record->event.pressed) {
			start = timer_read();
			return MACRO(D(LCTRL),END);
		} else {
			if (timer_elapsed(start) >150) {
				return MACRO(U(LCTRL),END);
			} else {
				return MACRO(U(LCTRL),D(LGUI),T(V),U(LGUI),END);
			}
		}

break;
case M_MEH_SH_ACUT:
//Macro: M_MEH_SH_ACUT//-----------------------
if (record->event.pressed) {
			start = timer_read();
			return MACRO(D(LCTRL),D(LSFT),D(LALT),END);
		} else {
			if (timer_elapsed(start) >150) {
				return MACRO(U(LCTRL),U(LSFT),U(LALT),END);
			} else {
				return MACRO(U(LCTRL),U(LALT),T(EQL),U(LSFT),END);
			}
		}

break;
}
return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

uint8_t layer = biton32(layer_state);

ergodox_board_led_off();
ergodox_right_led_1_off();
ergodox_right_led_2_off();
ergodox_right_led_3_off();
switch (layer) {

    case SYMB:
        ergodox_right_led_1_on();
        
        
        break;
    case MDIA:
        
        ergodox_right_led_2_on();
        
        break;
    case SMLY:
        
        
        ergodox_right_led_3_on();
        break;
    case NUMB:
        ergodox_right_led_1_on();
        
        ergodox_right_led_3_on();
        break;
    case EGOS:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
default:
// none
break;
}

};

