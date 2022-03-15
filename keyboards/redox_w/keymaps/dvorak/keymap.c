/* Copyright 2021 66f94eae(66f94eae@gmail.com)
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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
    _DVORAK,
    _SYMB,
    _QWERTY,
    _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_DVORAK] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
    KC_GESC  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_BSPC ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    KC_TAB  ,KC_QUOT ,KC_COMM ,KC_DOT  ,KC_P    ,KC_Y    ,KC_LBRC,                          KC_RBRC ,KC_F    ,KC_G    ,KC_C    ,KC_R    ,KC_L    ,KC_SLSH  ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    KC_LCTL  ,KC_A   ,KC_O    ,KC_E    ,KC_U    ,KC_I    ,KC_MINS,                          KC_EQL   ,KC_D    ,KC_H    ,KC_T    ,KC_N    ,KC_S    ,KC_BSLS ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    KC_LSFT ,KC_SCLN ,KC_Q    ,KC_J    ,KC_K    ,KC_X    ,KC_PGUP ,KC_HOME ,        KC_END  ,KC_PGDN ,KC_B    ,KC_M    ,KC_W   ,KC_V     ,KC_Z    ,KC_RSFT ,
//├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
    KC_CAPS ,KC_APP ,KC_LALT ,KC_LGUI  ,    LT(3,KC_MUTE), KC_SPC  ,KC_INS  ,        KC_DEL  ,KC_ENT  ,    KC_RALT ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
//└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
),

[_SYMB] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
    KC_GESC  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F8   ,KC_F9   ,KC_F10   ,KC_F11  ,KC_F12 ,KC_BSPC ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    KC_TAB , KC_BTN1 ,KC_MS_U  ,KC_BTN2 ,KC_WH_U ,KC_COPY ,KC_F6 ,                            KC_F7  ,KC_COPY ,KC_P7 	,KC_P8 	 ,KC_P9   ,KC_MPRV ,KC_PPLS ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    KC_LCTL ,KC_MS_L ,KC_MS_D  ,KC_MS_R ,KC_WH_D ,KC_CUT  ,KC_VOLD ,                          KC_VOLU ,KC_CUT ,KC_P4 	,KC_P5   ,KC_P6   ,KC_MNXT ,KC_PMNS ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    KC_LSFT ,KC_WH_L ,KC_UP   ,KC_WH_R ,KC_LGUI ,KC_PSTE ,KC_WH_U ,KC_SLCK ,        KC_NLCK ,KC_WH_D ,KC_PSTE ,KC_P1 	,KC_P2   ,KC_P3   ,KC_PEQL ,KC_PAST ,
//├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
    KC_CAPS ,KC_LEFT ,KC_DOWN ,KC_RGHT, LT(3,KC_MUTE)     ,KC_SPC  ,KC_ESC ,        KC_DEL  ,KC_ENT ,    KC_APP   ,     KC_P0   ,KC_PDOT ,KC_PENT ,KC_PSLS 
//└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
),

[_QWERTY] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
    KC_GESC  ,KC_1     ,KC_2   ,KC_3    ,KC_4     ,KC_5   ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9     ,KC_0  ,KC_BSPC,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    KC_TAB  ,KC_Q     ,KC_W   ,KC_E    ,KC_R    ,KC_T    ,KC_MINS ,                          KC_EQL  ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_BSLS ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    KC_LCTL ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_LBRC ,                          KC_RBRC ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_HOME ,KC_PGUP ,        KC_PGDN ,KC_END   ,KC_N   ,KC_M    ,KC_COMM ,KC_DOT ,KC_SLSH ,KC_RSFT ,
//├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
    KC_CAPS ,KC_LGUI ,KC_LALT , KC_APP  ,LT(3,KC_MUTE) ,   KC_SPC ,KC_INS ,          KC_DEL ,KC_ENT       , KC_APP      , KC_LEFT ,KC_UP   ,KC_DOWN  ,KC_RGHT
//└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
),

[_ADJUST] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
    KC_GESC   ,TO(0)   ,TO(1)   ,TO(2)   ,KC_NO   ,KC_NO   ,                                            KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO  ,KC_NO   ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,                          KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,                          KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    KC_LSFT  ,KC_NO   ,KC_NO   ,KC_NO    ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO           ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO ,KC_RSFT ,
//├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
    KC_NO   ,KC_NO   ,KC_NO   ,KC_LGUI        ,LT(3,KC_MUTE), KC_NO   ,KC_NO           ,KC_NO   ,KC_NO        ,KC_APP    ,KC_NO  ,KC_NO   ,KC_NO   ,KC_NO
//└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
)

};

layer_state_t layer_state_set_user(layer_state_t state)
{
    switch (get_highest_layer(state)) {
        case _DVORAK:
            blu_led_off;
            grn_led_off;
            break;
        case _SYMB:
            blu_led_on;
            grn_led_off;
            break;
        case _QWERTY:
            blu_led_off;
            grn_led_on;
            break;
        case _ADJUST:
            blu_led_on;
            grn_led_on;
            break;
        default:
            break;
    }
    return state;
}

bool led_update_user(led_t led_state)
{
    if (led_state.caps_lock) {
        red_led_on;
    } else {
        red_led_off;
    }
    if (led_state.num_lock) {
        wht_led_on;
    } else {
        wht_led_off;
    }
    return false;
}
