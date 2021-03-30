/* Copyright 2018 Holten Campbell
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
#include "milestogo.h"

/* customized matrix needs to be updated in local config.h
#define MATRIX_ROWS 5
#define MATRIX_COLS 15
#define MATRIX_ROW_PINS { E6, C7, B5, B4, C6 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, D6, D4, D5, D3, D2, D1, D0, B6, D7}
*/

#define LAYOUT_wrap_m2primee(...) LAYOUT_m2primee(__VA_ARGS__)
#define LAYOUT_wrap_m2primee_trns(...) LAYOUT_m2primee_trns(__VA_ARGS__)

// clang-format off
#define LAYOUT_m2primee(\
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K112,\
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, \
    K300, K301, K303, K304, K306, K308, K311, K312, \
    K413, K414 )\
    {\
        {K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, KC_NO, KC_NO},\
        {K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, KC_NO, K112, KC_NO, KC_NO},\
        {K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, KC_NO, KC_NO}, \
        {K300, K301, KC_NO, K303, K304, KC_NO, K306, KC_NO, K308, KC_NO, KC_NO, K311, K312, KC_NO, KC_NO}, \
        {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K413, K414 } \
    }

#define LAYOUT_m2primee_trns(\
    K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, \
    K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K112, \
    K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211) \
    {\
        {KC_TRNS, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, KC_NO, KC_NO}, \
        {KC_TRNS, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, KC_NO, K112, KC_NO, KC_NO}, \
        {KC_LSFT, K201, K202, K203, K204, K205, KC_TRNS, K207, K208, K209, K210, K211, KC_TRNS, KC_NO, KC_NO}, \
        {KC_LALT, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_RSFT, KC_NO, KC_NO}, \
        {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, B_1ME, KC_ENTER } \
    }


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_wrap_m2primee(\
KC_TAB, _________________QWERTY_L1_________________, _________________QWERTY_R1_________________, KC_MINS, KC_EQL,
LT(_MOV,KC_ESC), _________________QWERTY_L2_________________, _________________QWERTY_R2_________________, KC_QUOT, 
KC_LSFT, _________________QWERTY_L3_________________, MO(_SYM), _________________QWERTY_R3_________________, KC_RSFT, 
B_2ME, KC_LALT, LT(_NUM, KC_DEL), KC_BSPC, KC_SPC, LT(_NUM, KC_ESC), B_2ME, KC_RALT, 
B_1ME, KC_ENTER),

    [_NUM] = LAYOUT_wrap_m2primee(\
KC_TRNS, __________40_______NUM_L1__________________, __________40_______NUM_R1__________________, KC_VOLD, KC_VOLU, 
KC_TRNS, __________40_______NUM_L2__________________, __________40_______NUM_R2__________________, KC_ENT, 
KC_TRNS, __________40_______NUM_L3__________________, KC_TRNS, __________40_______NUM_R3__________________, KC_TRNS, 
KC_TRNS, KC_TRNS, KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
KC_TRNS, KC_TRNS),

    [_CDH] = LAYOUT_wrap_m2primee_trns(\
______________COLEMAK_MOD_DH_L1____________, ______________COLEMAK_MOD_DH_R1____________, KC_TRNS, KC_TRNS,
______________COLEMAK_MOD_DH_L2____________, ______________COLEMAK_MOD_DH_R2____________, KC_QUOT, 
______________COLEMAK_MOD_DH_L3____________, KC_TRNS, ______________COLEMAK_MOD_DH_R3____________),

    [_SYM] = LAYOUT_wrap_m2primee_trns(\
___________________SYM_L1__________________, ___________________SYM_R1__________________, KC_TRNS, KC_TRNS, 
___________________SYM_L2__________________, ___________________SYM_R2__________________, KC_TRNS,
___________________SYM_L3__________________, KC_TRNS, ___________________SYM_R3__________________),

    [_MOV] = LAYOUT_wrap_m2primee_trns(\
__________40_______MOV_L1__________________, __________40_______MOV_R1__________________, KC_TRNS, KC_CDH,
__________40_______MOV_L2__________________, __________40_______MOV_R2__________________, KC_TRNS, 
__________40_______MOV_L3__________________, KC_TRNS, __________40_______MOV_R3__________________),

     [_DMOV] = LAYOUT_wrap_m2primee_trns(\
____________40__DELMOV_L1__________________,  ____________40__DELMOV_R1__________________ , KC_TRNS, KC_CDH,
____________40__DELMOV_L2__________________,  ____________40__DELMOV_R2__________________ , KC_TRNS, 
____________40__DELMOV_L3__________________,  KC_TRNS, ____________40__DELMOV_R3__________________ ),
};

// clang-format on

void matrix_init_user(void) {
    // set CapsLock LED to output and high by default, drop low when on.
    setPinOutput(B1);
    writePinHigh(B1);
    // set NumLock LED to output and low
    setPinOutput(B2);
    writePinLow(B2);
    // set ScrollLock LED to output and low
    setPinOutput(B3);
    writePinLow(B3);

    backlight_enable();
    backlight_level(2);
}

bool led_update_kb(led_t led_state) {
#ifndef USE_BABBLEPASTE
    // if we aren't using the LEDs to show bablepaste options, use them to show standard keyboard stuff
    writePin(B1, led_state.caps_lock);
    writePin(B2, led_state.num_lock);
    writePin(B3, led_state.scroll_lock);
#endif
    return true;
}

void babble_modeswitch_kb(uint8_t mode) {
#ifdef USE_BABBLEPASTE
    switch (mode) {
        case (BABL_READMUX_MODE):
            writePinHigh(B3);
            writePinLow(B2);
            backlight_level(1);
            break;
        case (BABL_LINUX_MODE):
            writePinHigh(B2);
            writePinLow(B3);
            backlight_level(2);
            break;
        case (BABL_MAC_MODE):  // backlight on, indicator leds off
            writePinLow(B3);
            writePinLow(B2);
            backlight_level(4);
            break;
    }

    // call the user function
    babble_modeswitch_user(mode);
#endif
}

// function for layer indicator LED
layer_state_t layer_state_set_user(layer_state_t state) {
    // Turn on top LED if we are in colemak, off for qwerty.
    writePin(B1, layer_state_cmp(state, _CDH));
    return state;
}
