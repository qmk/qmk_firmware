 /* Copyright 2021 Daniil <Macbet> Kivenko
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

#include "chrisgve.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_QWERTY_MAC] = LAYOUT_60_tsangan_hhkb(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
		CPS_CTL, KC_A,    KC_S,    M_NAV_1, KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   R_SHIFT, ADJUST,
		XXXXXXX, KC_LALT, KC_LGUI,                                     KC_SPC,                                      KC_RGUI, KC_RALT, XXXXXXX
	),

	[_MAC_NAV_1] = LAYOUT_60_tsangan_hhkb(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, M_F_WRD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, A_SHIFT, S_SHIFT, _______, M_NAV_2, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
		_______, _______, _______, _______, _______, M_B_WRD, _______, _______, _______, _______, _______,                   _______, _______,
		_______, _______, _______,                                     _______,                                     _______, _______, _______
	),

	[_MAC_NAV_2] = LAYOUT_60_tsangan_hhkb(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,          _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______,
		_______, _______, _______,                                     _______,                                     _______, _______, _______
	),

	[_QWERTY_LINUX] = LAYOUT_60_tsangan_hhkb(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
		CPS_CTL, KC_A,    KC_S,    L_NAV_1, KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   R_SHIFT, ADJUST,
		XXXXXXX, KC_LGUI, KC_LALT,                                     KC_SPC,                                      KC_RALT, KC_RGUI, XXXXXXX
	),

	[_LINUX_NAV_1] = LAYOUT_60_tsangan_hhkb(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, L_F_WRD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, A_SHIFT, S_SHIFT, _______, L_NAV_2, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
		_______, _______, _______, _______, _______, L_B_WRD, _______, _______, _______, _______, _______,                   _______, _______,
		_______, _______, _______,                                     _______,                                     _______, _______, _______
	),

	[_LINUX_NAV_2] = LAYOUT_60_tsangan_hhkb(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,          _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______,
		_______, _______, _______,                                     _______,                                     _______, _______, _______
	),

	[_QWERTY_WIN] = LAYOUT_60_tsangan_hhkb(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
		CPS_CTL, KC_A,    KC_S,    W_NAV_1, KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   R_SHIFT, ADJUST,
		XXXXXXX, KC_LGUI, KC_LALT,                                     KC_SPC,                                      KC_RALT, KC_RGUI, XXXXXXX
	),

	[_WIN_NAV_1] = LAYOUT_60_tsangan_hhkb(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, W_F_WRD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, A_SHIFT, S_SHIFT, _______, W_NAV_2, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
		_______, _______, _______, _______, _______, W_B_WRD, _______, _______, _______, _______, _______,                   _______, _______,
		_______, _______, _______,                                     _______,                                     _______, _______, _______
	),

	[_WIN_NAV_2] = LAYOUT_60_tsangan_hhkb(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,          _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______,
		_______, _______, _______,                                     _______,                                     _______, _______, _______
	),

	[_ADJUST] = LAYOUT_60_tsangan_hhkb(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
		RESET,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, _______,          _______,
		_______, DF_MAC,  DF_LNX,  DF_WIN,  _______, _______, _______, KC_MUTE, _______, _______, _______,                   _______, _______,
		_______, _______, _______,                                     KC_MPLY,                                     _______, _______, _______
	),

};

// RGB configuration and setup light layer for caps on

enum generic_layer_t {
    _DEF_L,
    _NAV1_L,
    _NAV2_L,
    _ADJ_L,
    _NUM_L,
};

bool caps_lock = false;  // Indicator if caps lock is on
bool def_layer = true;   // Indicates if the board is on a default layer
uint8_t cur_layer = _DEF_L;   // Current layer

void reset_rgb(void) {
    rgb_matrix_disable_noeeprom();
}

void set_rgb(uint8_t red, uint8_t green, uint8_t blue) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_set_color_all(red, green, blue);
}

void keyboard_post_init_user() {
    reset_rgb();
}

void set_nav_1_rgb(void) {
    set_rgb(RGB_NAV1_R, RGB_NAV1_G, RGB_NAV1_B);
}

void set_nav_2_rgb(void) {
    set_rgb(RGB_NAV2_R, RGB_NAV2_G, RGB_NAV2_B);
}

void set_caps_rgb(void) {
    set_rgb(RGB_CAPS_R, RGB_CAPS_G, RGB_CAPS_B); // Warm white
}

void set_adj_rgb(void) {
    set_rgb(RGB_ADJ_R, RGB_ADJ_G, RGB_ADJ_B);
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    if (caps_lock) {
        set_caps_rgb();
    } else {
        reset_rgb();
    }
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch(get_highest_layer(state)) {
        case _MAC_NAV_1:
        case _LINUX_NAV_1:
        case _WIN_NAV_1:
            cur_layer = _NAV1_L;
            def_layer = false;
            set_nav_1_rgb();
            break;
        case _MAC_NAV_2:
        case _LINUX_NAV_2:
        case _WIN_NAV_2:
            cur_layer = _NAV2_L;
            def_layer = false;
            set_nav_2_rgb();
            break;
        case _ADJUST:
            cur_layer = _ADJ_L;
            def_layer = false;
            set_adj_rgb();
            break;
        default:
            cur_layer = _DEF_L;
            def_layer = true;
            if (caps_lock) {
                set_caps_rgb();
            } else {
                reset_rgb();
            }
    }
    return state;
}

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        set_caps_rgb();
        caps_lock = true;
    } else {
        if (def_layer) {
            reset_rgb();
        }
        caps_lock = false;
    }
}

void rgb_matrix_indicators_user(void) {
    if (caps_lock) {
        set_caps_rgb();
    } else {
        switch(cur_layer) {
            case _DEF_L:
                reset_rgb();
                break;
            case _NAV1_L:
                set_nav_1_rgb();
                break;
            case _NAV2_L:
                set_nav_2_rgb();
                break;
            case _ADJ_L:
                set_adj_rgb();
                break;
            default:
                break;
        }
    }
}

