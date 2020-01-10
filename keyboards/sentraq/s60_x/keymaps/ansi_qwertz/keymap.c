/*
Copyright 2016 Julien Pecqueur <julien@peclu.net>
Copyright 2016 Felix Uhl <ifreilicht@gmail.com>

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

#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 1

//uncomment to activate dead keys
//#define DONT_REVIVE_DEADKEYS 1

//Function keycodes for better readability
//SpaceFN
//OneShot LeftShift
//GamingMode Lock (disables SpaceFn and OneShot LShift)
//Function
//Mute microphone
#define KC_SPACEFN LT(2, KC_SPACE)
#define KC_OSLS KC_FN3
#define KC_GMLK KC_FN1
#define KC_FUNC MO(2)
#define MICMUTE RCTL(KC_LCTL)

enum function_codes {
    F_OSLS = 3,
    F_GMLK = 1,
};

enum layer_names {
    DEFAULT,
    GAMING,
    FUNCTION
};

enum languages {
    GERMAN
};

#define LANGUAGE GERMAN

enum custom_keycodes {
    KC_CM_A = SAFE_RANGE,
//  KC_CM_B,
    KC_CM_C,
//  KC_CM_D,
    KC_CM_E,
//  KC_CM_F,
    KC_CM_G,
//  KC_CM_H,
    KC_CM_I,
//  KC_CM_J,
    KC_CM_K,
    KC_CM_L,
    KC_CM_M,
    KC_CM_N,
    KC_CM_O,
    KC_CM_P,
//  KC_CM_Q,
    KC_CM_R,
    KC_CM_S,
//  KC_CM_T,
    KC_CM_U,
//  KC_CM_V,
    KC_CM_W,
//  KC_CM_X,
    KC_CM_Y,
    KC_CM_Z
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layout 0: Default Layer
    * ,-----------------------------------------------------------.
    * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|Del|
    * |-----------------------------------------------------------|
    * |Tab  |  Q|  W|  E|  R|  T|  Z|  U|  I|  O|  P|  [|  ]|BckSp|
    * |-----------------------------------------------------------|
    * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |
    * |-----------------------------------------------------------|
    * |Shift   |  Y|  X|  C|  V|  B|  N|  M|  ,|  .|  /| Up  |RSft|
    * |-----------------------------------------------------------|
    * |Fn2 |Gui |Alt |         SpaceFn       |Alt |Left|Down|Right|
    * `-----------------------------------------------------------'
    */
    [DEFAULT] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Z,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,          \
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,           \
        KC_LSFT, KC_NUBS, KC_Y,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_UP,   KC_RSFT, \
        KC_FUNC, KC_LGUI, KC_LALT,                            KC_SPACEFN,                                  KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Layout 1: Gaming Layer, SpaceFn disabled
    * ,-----------------------------------------------------------.
    * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    * |-----------------------------------------------------------|
    * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
    * |-----------------------------------------------------------|
    * |      |   |   |   |   |   |   |   |   |   |   |   |        |
    * |-----------------------------------------------------------|
    * |        |   |   |   |   |   |   |   |   |   |   |     |Fn1 |
    * |-----------------------------------------------------------|
    * |   |RSft|     |          Space         |    |    |    |    |
    * `-----------------------------------------------------------'
    */
    [GAMING] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_GMLK,  \
        _______, KC_RSFT,   _______,                            KC_SPC,                                    _______, _______, _______, _______
    ),

    /* Layout 2: Function Layer
    * MicMute requires special software to be installed. Check readme.md for more information
    * ,-----------------------------------------------------------.
    * |`  | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|RES|
    * |-----------------------------------------------------------|
    * |     |   |   |   |Prv|Ply|Nxt| � |   | � |   |Prt|Slk|Pau  |
    * |-----------------------------------------------------------|
    * |      | � | � |   |Vl-|Mut|Vl+|   |   |   |   |   |PEnt    |
    * |-----------------------------------------------------------|
    * |        |  |  |  |MicMut|Cal|   |   |   |   |Pau |PUp |Fn1 |
    * |-----------------------------------------------------------|
    * |    |    |    |                        |    |Home|PDn |End |
    * `-----------------------------------------------------------'
    */
    [FUNCTION] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,   RESET,   \
        _______, _______, KC_CM_W, KC_CM_E, KC_MPRV, KC_MPLY, KC_MNXT, KC_CM_U, KC_CM_I, KC_CM_O, KC_CM_P, KC_PSCR, KC_SLCK, KC_PAUS, \
        _______, KC_CM_A, KC_CM_S, _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, KC_CM_K, KC_CM_L, _______, _______, _______, KC_PENT,          \
        _______, _______, KC_CM_Y, _______, KC_CM_C, MICMUTE, KC_CALC, KC_CM_N, KC_CM_M, _______, _______, _______,          KC_PGUP, KC_GMLK, \
        _______, _______, _______,                            _______,                                     _______, KC_HOME, KC_PGDN, KC_END
    ),
};

/*
* Fn action definition
*/
const uint16_t PROGMEM fn_actions[] = {
    [F_GMLK] = ACTION_LAYER_TOGGLE(1),                  // Disable SpaceFn and Oneshot Shift
    [F_OSLS] = ACTION_MODS_ONESHOT(MOD_LSFT)            // Oneshot Leftshift
};

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_german(uint16_t keycode, keyrecord_t *record) {
    uint16_t send_code = 0;
    if (record->event.pressed) {
        switch (keycode) {
        case KC_CM_A:
            send_code = KC_Q;
            break;
        case KC_CM_O:
            send_code = KC_P;
            break;
        case KC_CM_U:
            send_code = KC_Y;
            break;
        case KC_CM_S:
            send_code = KC_S;
            break;
        }

        if (send_code == 0) {
            return true;
        }
        else {
            register_code(KC_RALT);
            register_code(send_code);
            unregister_code(send_code);
            unregister_code(KC_RALT);
            return false;
        }
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //revive dead keys
#ifndef DONT_REVIVE_DEADKEYS
    bool shift_active = keyboard_report->mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_LSFT));
    bool altgr_active = keyboard_report->mods & (MOD_BIT(KC_RALT));
    if ((keycode == KC_QUOT && !altgr_active) ||
        keycode == KC_GRV ||
        (keycode == KC_6 && shift_active))
    {
        if (record->event.pressed) {
            register_code(keycode);
            unregister_code(keycode);
            register_code(KC_SPACE);
            unregister_code(KC_SPACE);
        }
        return false;
    }
#endif
#if LANGUAGE == GERMAN
    return process_german(keycode, record);
#else
    return true;
#endif
}

void led_set_user(uint8_t usb_led) {

}
