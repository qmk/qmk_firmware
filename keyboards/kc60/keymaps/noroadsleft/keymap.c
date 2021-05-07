/* Copyright 2018-2020 James Young (@noroadsleft)
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

#include "noroadsleft.h"
#include "sendstring_dvorak.h"
//#include "sendstring_colemak.h"
#include "print.h"


/**********************
** LAYER DEFINITIONS **
**********************/
enum layer_names {
    // BASE LAYERS
    _QW,  // QWERTY
    _DV,  // Dvorak
    _CM,  // Colemak
    // QUAKE 2 OVERLAY
    _Q2,  // Quake 2
    // FUNCTION LAYER
    _FN,  // Function
    // OTHER LAYERS
    _NP,  // Numpad
    _MA,  // Macros
    _SY,  // System
};


// KEYCODE DEFINITIONS
#define NO_CHNG KC_TRNS // Note for me for keys I need to leave as Pass-through

#define FN_CAPS LT(_FN, KC_CAPS)  // Function Layer when held, Caps Lock when tapped
#define Q2_CAPS LT(_FQ, KC_CAPS)  // Quake 2 Function Layer when held, Caps Lock when tapped

#define CTL_GRV MT(MOD_LCTL, KC_GRV)  // Left Control when held, Grave accent when tapped


// MACRO DEFINITIONS
enum custom_keycodes {
    GO_Q2 = KEYMAP_SAFE_RANGE,
    Q2_ENT
};


/*******************
** MODIFIER MASKS **
*******************/
#define MOD_MASK_RALT   (MOD_BIT(KC_RALT))
unsigned char q2InputMode = 0;


bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        // these are our macros!
        case GO_Q2:
            if (record->event.pressed) {
                //default_layer_set(_QW);
                layer_move(_QW); // TO(_QW);
                layer_on(_Q2);
                //layer_off(_SY);
            };
            return false;
        case Q2_ENT:
            if (record->event.pressed) {
                if (q2InputMode == 0) {
                    tap_code(KC_ENT);
                    q2InputMode = 1;
                    layer_on(_DV);
                    //layer_on(_Q2);
                } else if (q2InputMode == 1) {
                    tap_code(KC_ENT);
                    q2InputMode = 0;
                    layer_off(_DV);
                } else {
                    tap_code(KC_ENT);
                }
            };
            return false;
        case KC_ESC:
            if (record->event.pressed) {
                if (q2InputMode > 0) {
                    tap_code(KC_ESC);
                    q2InputMode = 0;
                    layer_off(_DV);
                } else {
                    tap_code(KC_ESC);
                }
            };
            return false;
        case KC_GRV:
            if (IS_LAYER_ON(_Q2) == true) {
                if (record->event.pressed) {
                    if (q2InputMode == 0) {
                        tap_code(KC_GRV);
                        q2InputMode = 2;
                        layer_on(_DV);
                    } else if (q2InputMode == 1) {
                        tap_code(KC_GRV);
                        q2InputMode = 2;
                    } else {
                        tap_code(KC_GRV);
                        q2InputMode = 0;
                        layer_off(_DV);
                    }
                }
            };
            return false;
        case KC_Z:
            if (record->event.pressed) {
                if ( get_mods() & MOD_MASK_RALT ) {
                    register_code(KC_NUBS);
                } else {
                    register_code(KC_Z);
                }
            } else {
                if ( get_mods() & MOD_MASK_RALT ) {
                    unregister_code(KC_NUBS);
                } else {
                    unregister_code(KC_Z);
                }
            };
            return false;
        case KC_1 ... KC_0:
            if (record->event.pressed) {
                if ( get_mods() & MOD_MASK_RALT ) {
                    register_code( keycode + 0x3B );
                } else {
                    register_code( keycode );
                }
            } else {
                if ( get_mods() & MOD_MASK_RALT ) {
                    unregister_code( keycode + 0x3B );
                } else {
                    unregister_code( keycode );
                }
            }
            return false;
        case KC_F1 ... KC_F12:
            if (record->event.pressed) {
                if ( get_mods() & MOD_MASK_RALT ) {
                    register_code( keycode + 0x2E );
                } else {
                    register_code( keycode );
                }
            } else {
                if ( get_mods() & MOD_MASK_RALT ) {
                    unregister_code( keycode + 0x2E );
                } else {
                    unregister_code( keycode );
                }
            }
            return false;
    } // switch()
    return true;
};


// KEYMAPS
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /****************
    ** BASE LAYERS **
    ****************/

    /* QWERTY */
    [_QW] = LAYOUT_60_ansi(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        FN_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
        CTL_GRV, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_MA), MO(_FN), KC_RCTL
    ),

    /* Dvorak */
    [_DV] = LAYOUT_60_ansi(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,  KC_BSLS,
        FN_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,          KC_ENT,
        KC_LSFT,          KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,             KC_RSFT,
        CTL_GRV, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_MA), MO(_FN), KC_RCTL
    ),

    /* Colemak */
    [_CM] = LAYOUT_60_ansi(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS,
        FN_CAPS, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
        CTL_GRV, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_MA), MO(_FN), KC_RCTL
    ),

    /*********************
    ** QUAKE 2 OVERLAYS **
    *********************/

    /* Quake 2 */
    [_Q2] = LAYOUT_60_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          Q2_ENT,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        KC_GRV,  _______, _______,                            _______,                            _______, _______, _______, _______
    ),

    /********************
    ** FUNCTION LAYERS **
    ********************/

    /* Fn layer */
    [_FN] = LAYOUT_60_ansi(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, KC_CALC, KC_APP,  _______, _______, _______, KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_PSCR, KC_SLCK, KC_PAUS,
        NO_CHNG, M_SALL,  _______, _______, _______, _______, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,          KC_PENT,
        _______,          M_UNDO,  M_CUT,   M_COPY,  M_PASTE, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, TG(_SY),          _______,
        _______, _______, _______,                            TG(_NP),                            _______, _______, NO_CHNG, _______
    ),

    /*****************
    ** OTHER LAYERS **
    *****************/

    /* Numpad layer */
    [_NP] = LAYOUT_60_ansi(
        _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   _______, _______, _______, _______,
        _______, _______, _______, _______, KC_E,    KC_F,    _______, KC_P4,   KC_P5,   KC_P6,   KC_PAST, KC_PSLS, KC_PEQL, _______,
        _______, _______, _______, _______, KC_C,    KC_D,    _______, KC_P1,   KC_P2,   KC_P3,   KC_PPLS, KC_PMNS,          KC_PENT,
        _______,          _______, _______, _______, KC_A,    KC_B,    _______, KC_P0,   _______, KC_PDOT, _______,          _______,
        _______, _______, _______,                            TG(_NP),                            _______, _______, NO_CHNG, _______
    ),

    /* Macro layer */
    [_MA] = LAYOUT_60_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, DM_REC1, DM_REC2, _______,
        _______, _______, _______, G_PUSH,  _______, _______, _______, _______, _______, _______, _______, DM_PLY1, DM_PLY2, DM_RSTP,
        _______, _______, _______, G_FTCH,  _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, G_BRCH,  _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                            _______, _______, NO_CHNG, _______
    ),

    /* System layer */
    [_SY] = LAYOUT_60_ansi(
        TG(_SY), TO(_QW), TO(_DV), TO(_CM), GO_Q2,   XXXXXXX, XXXXXXX, XXXXXXX, RESET,   XXXXXXX, DEBUG,   XXXXXXX, VRSN,    XXXXXXX,
        XXXXXXX, XXXXXXX, M_MDSWP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX,          XXXXXXX, XXXXXXX, BL_DEC,  BL_TOGG, BL_INC,  BL_BRTG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, XXXXXXX, NO_CHNG, XXXXXXX
    ),

};
