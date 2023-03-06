/* Copyright (C) 2022 jonylee@hfd
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

// clang-format off
enum __layers {
    WIN_B,
    WIN_WASD,
    WIN_FN,
    MAC_B,
    MAC_WASD,
    MAC_FN
};
enum custom_keycodes {
    KC_RESET = SAFE_RANGE
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [WIN_B] = LAYOUT( /* Base */
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,  KC_F7,   KC_F8,   KC_F9,    KC_F10,   KC_F11,     KC_F12,     KC_DEL,                                  KC_HOME,  KC_END,  KC_PGUP,   KC_PGDN,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,    KC_EQL,     KC_BSPC,                                 KC_NUM,  KC_PSLS,  KC_PAST,   KC_PMNS,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,     KC_P,     KC_LBRC,    KC_RBRC,    KC_BSLS,                                 KC_P7,     KC_P8,    KC_P9,   KC_PPLS,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,                KC_ENT,                                  KC_P4,     KC_P5,    KC_P6,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,   KC_SLSH,                          KC_RSFT,                KC_UP,           KC_P1,     KC_P2,    KC_P3,   KC_PENT,
		KC_LCTL, KC_LGUI, KC_LALT,                  KC_SPC,                           KC_RALT,  MO(WIN_FN),KC_LEFT,                                      KC_DOWN,  KC_RGHT,            KC_P0,    KC_PDOT),

    [WIN_WASD] = LAYOUT( /* Base */
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,  KC_F7,   KC_F8,   KC_F9,    KC_F10,   KC_F11,     KC_F12,     KC_DEL,                                  KC_HOME,  KC_END,  KC_PGUP,   KC_PGDN,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,    KC_EQL,     KC_BSPC,                                 KC_NUM,  KC_PSLS,  KC_PAST,   KC_PMNS,
		KC_TAB,  KC_Q,    KC_UP,   KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,     KC_P,     KC_LBRC,    KC_RBRC,    KC_BSLS,                                 KC_P7,     KC_P8,    KC_P9,   KC_PPLS,
		KC_CAPS, KC_LEFT, KC_DOWN, KC_RIGHT,KC_F,   KC_G,   KC_H,   KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,                KC_ENT,                                  KC_P4,     KC_P5,    KC_P6,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,   KC_SLSH,                          KC_RSFT,                KC_W,           KC_P1,     KC_P2,    KC_P3,   KC_PENT,
		KC_LCTL, KC_LGUI, KC_LALT,                  KC_SPC,                           KC_RALT,  MO(WIN_FN),KC_A,                                          KC_S,     KC_D,            KC_P0,    KC_PDOT),


    [WIN_FN] = LAYOUT( /* FN */
	    KC_ESC,  KC_MYCM, KC_MAIL, KC_WSCH, KC_WHOM,KC_MSEL,KC_MPLY,KC_MPRV,KC_MNXT,KC_F9,   KC_F10,   KC_F11,     KC_F12,     KC_DEL,                                  KC_HOME,  KC_END,  KC_PGUP,   KC_PGDN,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,    KC_8,   KC_9,    KC_0,   RGB_SPD,    RGB_SPI,     KC_BSPC,                                  KC_NUM,  KC_PSLS,  KC_PAST,   KC_PMNS,
		KC_TAB,  KC_Q,    TG(WIN_WASD),   KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_INS, DF(MAC_B),  KC_PSCR, KC_LBRC,    KC_RBRC,    RGB_MOD,                              KC_P7,     KC_P8,    KC_P9,   KC_PPLS,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,  KC_J,    KC_K, RGB_TOG,    KC_SCLN, KC_QUOT,             RGB_HUI,                                  KC_P4,     KC_P5,    KC_P6,
		KC_LSFT, KC_Z,    KC_X,    KC_CALC, KC_V,   KC_B,   KC_N,  KC_MUTE, KC_VOLD,KC_VOLU,  KC_SLSH,                        KC_RSFT,               RGB_VAI,           KC_P1,     KC_P2,    KC_P3,   KC_PENT,
		KC_LCTL, MAGIC_TOGGLE_GUI, KC_LALT,                  KC_SPC,                           KC_RALT,  MO(WIN_FN),RGB_SAD,                          RGB_VAD,  RGB_SAI,            KC_P0,    KC_PDOT),

    [MAC_B] = LAYOUT( /* Base */
		KC_ESC,  KC_BRID, KC_BRIU, KC_MCTL, KC_LPAD, KC_F5,  KC_F6, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD,  KC_VOLU,      KC_DEL,                                   KC_HOME,  KC_END,  KC_PGUP,   KC_PGDN,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,    KC_EQL,     KC_BSPC,                                 KC_NUM,  KC_PSLS,  KC_PAST,   KC_PMNS,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,     KC_P,     KC_LBRC,    KC_RBRC,    KC_BSLS,                                 KC_P7,     KC_P8,    KC_P9,   KC_PPLS,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,                KC_ENT,                                  KC_P4,     KC_P5,    KC_P6,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,   KC_SLSH,                          KC_RSFT,                KC_UP,           KC_P1,     KC_P2,    KC_P3,   KC_PENT,
		KC_LCTL, KC_LALT, KC_LGUI,                  KC_SPC,                           KC_RGUI,   MO(MAC_FN),KC_LEFT,                                      KC_DOWN,  KC_RGHT,            KC_P0,    KC_PDOT),

    [MAC_WASD] = LAYOUT( /* Base */
		KC_ESC,  KC_BRID, KC_BRIU, KC_MCTL, KC_LPAD, KC_F5,  KC_F6, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD,  KC_VOLU,      KC_DEL,                                   KC_HOME,  KC_END,  KC_PGUP,   KC_PGDN,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,    KC_EQL,     KC_BSPC,                                 KC_NUM,  KC_PSLS,  KC_PAST,   KC_PMNS,
		KC_TAB,  KC_Q,    KC_UP,   KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,     KC_P,     KC_LBRC,    KC_RBRC,    KC_BSLS,                                 KC_P7,     KC_P8,    KC_P9,   KC_PPLS,
		KC_CAPS, KC_LEFT, KC_DOWN, KC_RIGHT,KC_F,   KC_G,   KC_H,   KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,               KC_ENT,                                  KC_P4,     KC_P5,    KC_P6,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,   KC_SLSH,                          KC_RSFT,                KC_UP,           KC_P1,     KC_P2,    KC_P3,   KC_PENT,
		KC_LCTL, KC_LALT, KC_LGUI,                  KC_SPC,                           KC_RGUI,   MO(MAC_FN),KC_LEFT,                                      KC_DOWN,  KC_RGHT,            KC_P0,    KC_PDOT),

    [MAC_FN] = LAYOUT( /* FN */
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6, KC_F7,   KC_F8,  KC_F9,     KC_F10,  KC_F11,     KC_F12,     KC_DEL,                                   KC_HOME,  KC_END,  KC_PGUP,   KC_PGDN,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,  KC_7,    KC_8,   KC_9,      KC_0,    RGB_SPD,    RGB_SPI,    KC_BSPC,                                  KC_NUM,  KC_PSLS,  KC_PAST,   KC_PMNS,
		KC_TAB,  KC_Q,TG(MAC_WASD),KC_E,    KC_R,   KC_T,   KC_Y,  KC_U,    KC_INS, DF(WIN_B), KC_PSCR, KC_LBRC,    KC_RBRC,    RGB_MOD,                                  KC_P7,     KC_P8,    KC_P9,   KC_PPLS,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,  KC_J,    KC_K,   RGB_TOG,   KC_SCLN, KC_QUOT,                RGB_HUI,                                  KC_P4,     KC_P5,    KC_P6,
		KC_LSFT, KC_Z,    KC_X,    KC_CALC, KC_V,   KC_B,   KC_N,  KC_MUTE, KC_VOLD,KC_VOLU,  KC_SLSH,                          KC_RSFT,               RGB_VAI,           KC_P1,     KC_P2,    KC_P3,   KC_PENT,
		KC_LCTL, KC_LALT, KC_LGUI,                  KC_SPC,                           KC_RGUI,  MO(MAC_FN),RGB_SAD,                                   RGB_VAD,  RGB_SAI,            KC_P0,    KC_PDOT)

};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef VIA_ENABLE
        case KC_RESET: {
            if (record->event.pressed) {
#    include "via.h"
                via_eeprom_set_valid(false);
                eeconfig_init_via();
            }
            return false;
        }
#endif
    }
    return true;
}
// clang-format off
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [WIN_B] = {ENCODER_CCW_CW(KC_VOLU, KC_VOLD)}, 
    [WIN_WASD] = {ENCODER_CCW_CW(KC_VOLU, KC_VOLD)}, 
    [WIN_FN] = {ENCODER_CCW_CW(RGB_VAI, RGB_VAD)}, 
    [MAC_B] = {ENCODER_CCW_CW(KC_VOLU, KC_VOLD)}, 
    [MAC_WASD] = {ENCODER_CCW_CW(KC_VOLU, KC_VOLD)}, 
    [MAC_FN] = {ENCODER_CCW_CW(RGB_VAI, RGB_VAD)}
    };
#endif
