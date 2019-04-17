/* Copyright 2017 Wunder
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
#include "bbaserdem.h"

// Layer shorthand
#define _BASE 0
#define _FUNC 1
#define FUNCT MO(_FUNC)
#define XXX KC_NO
#define RGB_RMD RGB_MODE_REVERSE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_ortho_5x15_wrapper(
            __QWERTY_NUMBER_13__,                                                               KC_BSPC,KC_DEL,
    KC_ESC, __QWERTY_ROW_QW_12__,                                                               KC_HOME,KC_PGUP,
    KC_TAB, __QWERTY_ROW_AS_12__,                                                               KC_END, KC_PGDN,
    KC_LSFT,__QWERTY_ROW_ZX_11__,                                                       KC_RSFT,KC_UP,  KC_INS,
    KC_LCTL,KC_LGUI,KC_LALT,KC_SPC,XXX, KC_ENT,XXX, KC_SPC,XXX, KC_RALT,FUNCT,  KC_CAPS,KC_LEFT,KC_DOWN,KC_RGHT),

[_FUNC] =  LAYOUT_ortho_5x15_wrapper(
    RESET, __QWERTY_FUNCTN_12__,                                                                XXX,    KC_PSCR,
    BL_BRTG,RGB_RMD,RGB_HUI,RGB_SAI,RGB_VAI,RGB_SPI, XXX,XXX,XXX,XXX,XXX,XXX,XXX,               XXX,    XXX,
    BL_STEP,RGB_MOD,RGB_HUD,RGB_SAD,RGB_VAD,RGB_SPD, XXX,XXX,XXX,XXX,XXX,XXX,XXX,               KC_MUTE,XXX,
    BL_TOGG,RGB_TOG, XXX,XXX,XXX,XXX,XXX,XXX,XXX,XXX,XXX,XXX,                           KC_VOLD,KC_MSTP,KC_VOLU,
    XXX,    XXX,    XXX,    SECRET1,XXX,SECRET2,XXX,SECRET3,XXX,XXX,    _______,XXX,    KC_MPRV,KC_MPLY,KC_MNXT)
};

uint32_t layer_state_set_keymap(uint32_t state) {
    if ( biton32(state) == _FUNC ) {
        capslock_led_on();
        keycaps_led_on();
        gp103_led_on();
        gp100_led_on();
    } else {
        capslock_led_off();
        keycaps_led_off();
        gp103_led_off();
        gp100_led_off();
    }
    return state;
};
