/* Copyright 2017 Kolja Brauns
*/
#include QMK_KEYBOARD_H

#ifndef KEYMAP_GERMAN
#define KEYMAP_GERMAN

#include "keymap.h"

#endif

//Tap Dance Declarations
enum {
  TD_ESC_RUPT = 0
};

enum {
  TD_TAB = 1
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice Ctrl+Alt+Del
  [TD_ESC_RUPT]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, LALT(LCTL(KC_DEL))),
  [TD_TAB]  = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, LGUI(KC_TAB))
// Other declarations would go here, separated by commas, if you have them
};

//In Layer declaration, add tap dance item in place of a key code


// Layer shorthand
#define _QWZ 0
#define _FNC 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 
    /* QWZ
 * .-----------------------------------------------------------------------------------------------------------------------.
 * |  Esc  |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |   ß   |   ´   | BckSpc|  Esc  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Tab  |   Q   |   W   |   E   |   R   |   T   |   Z   |   U   |   I   |   O   |   P   |   Ü   |   +   |       |  PgUp |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------| Enter |-------|
 * | Ctrl/ |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   Ö   |   Ä   |   #   |       |  PgDn |
 * | GUITab|       |       |       |       |       |       |       |       |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | LShift|   Y   |   X   |    C  |   V   |   B   |   N   |   M   |   ,   |   .   |   -   |   ^   | Home/ |  Up   |  End  |
 * |       |       |       |       |       |       |       |       |       |       |       |       | RShift|       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | LCtrl | LAlt  | MO(1)/|     Space     |   Backspace   | MO(1)/|AltGr/ |  Win  |   <   |  Del  | Left  | Down  | Right |
 * |       |       | Enter |               |               | TO(1) |Pause  |       |       |       |       |       |       |
 * °-----------------------------------------------------------------------------------------------------------------------°
 */
 
	[_QWZ] = LAYOUT_ortho_5x15(
	TD(TD_ESC_RUPT), KC_1,    KC_2,          KC_3,   KC_4,   KC_5,    KC_6,  KC_7,  KC_8,                  KC_9,    KC_0,    DE_SS,   DE_ACUT,               KC_BSPC, KC_ESC,
	KC_TAB,          KC_Q,    KC_W,          KC_E,   KC_R,   KC_T,    DE_Z,  KC_U,  KC_I,                  KC_O,    KC_P,    DE_UDIA, DE_PLUS,               KC_NO,   KC_PGUP,
	TD(TD_TAB),      KC_A,    KC_S,          KC_D,   KC_F,   KC_G,    KC_H,  KC_J,  KC_K,                  KC_L,    DE_ODIA, DE_ADIA, DE_HASH,               KC_ENT,  KC_PGDN,
    KC_LSFT,         DE_Y,    KC_X,          KC_C,   KC_V,   KC_B,    KC_N,  KC_M,  KC_COMM,               KC_DOT,  DE_MINS, DE_CIRC, MT(MOD_RSFT, KC_HOME), KC_UP,   KC_END,
    KC_LCTL,         KC_LALT, LT(1, KC_ENT), KC_SPC, KC_NO,  KC_BSPC, KC_NO, TT(1), MT(MOD_RALT, KC_PAUS), KC_RGUI, DE_LABK, KC_DEL,  KC_LEFT,               KC_DOWN, KC_RGHT
    ),
	
	/* FNC
 * .-----------------------------------------------------------------------------------------------------------------------.
 * | Reset |   F1  |   F2  |   F3  |   F4  |   F5  |   F6  |   F7  |   F8  |   F9  |   F10 |  F11  |  F12  | _____ | _____ |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | _____ | _____ | _____ |Bright+| _____ | _____ | _____ | _____ | _____ |   Up  | PrtSc | _____ | _____ | _____ | _____ |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | _____ | _____ | _____ |RGB Tog|RGB Mod| _____ | _____ | _____ | Left  |  Down | Right | _____ | _____ | Play  | _____ |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | CpsLck| _____ | _____ |Bright-| _____ | _____ | _____ | _____ | _____ | _____ | _____ | _____ | _____ | VolUp | Mute  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | TO(0) | _____ | _____ | _____ | _____ | _____ | _____ | _____ | _____ | _____ | _____ | _____ | Prev  | VolDn | Next  |
 * °-----------------------------------------------------------------------------------------------------------------------°
*/	
	[_FNC] = LAYOUT_ortho_5x15(
	QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, RGB_VAI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP,   KC_PSCR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_MPLY, KC_TRNS,
	KC_CAPS, KC_TRNS, KC_TRNS, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU, KC_MUTE,
	TO(0),   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_VOLD, KC_MNXT
	)
	
};

