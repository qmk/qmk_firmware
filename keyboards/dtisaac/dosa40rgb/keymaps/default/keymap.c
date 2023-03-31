/* Copyright 2021 DTIsaac
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _L1,
	_L2
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    BASE,
	L1,
};

#define L1 MO(_L1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
	[_BASE] = LAYOUT(
				 KC_ESC,          KC_Q,     KC_W,      KC_E,      KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,   KC_BSPC,
                 LT(_L2,KC_CAPS), KC_A,     KC_S,      KC_D,      KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_ENT,
                 KC_LSFT,         KC_Z,     KC_X,      KC_C,      KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_RSFT,
                 KC_LCTL,         KC_LGUI,  KC_LALT,   			  KC_SPACE,           KC_SPACE,			  KC_RALT,  L1,		  KC_RCTL
    ),
    [_L1] = LAYOUT(
				 QK_BOOT,           KC_1,     KC_2,      KC_3,      KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,    KC_DEL,
                 KC_TRNS,         KC_F1,    KC_F2,     KC_F3,     KC_F4,    KC_F5,    KC_F6,    KC_MINS,  KC_EQL,   KC_SCLN,  KC_QUOT,
                 KC_TRNS,         KC_F7,    KC_F8,     KC_F9,     KC_F10,   KC_F11,   KC_F12,   KC_TRNS,  KC_TRNS,  KC_SLSH,  KC_TRNS,
                 KC_TRNS,         KC_TRNS,  KC_TRNS,   			  KC_TRNS,            KC_TRNS,   		  KC_TRNS,  KC_TRNS,  KC_TRNS
	),
    [_L2] = LAYOUT(
                 RGB_TOG,         RGB_RMOD, KC_UP,     RGB_MOD,   RGB_HUI,  RGB_VAI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  OU_USB,   OU_BT,   KC_TRNS,
                 KC_TRNS,         KC_LEFT,  KC_DOWN,   KC_RGHT,   RGB_HUD,  RGB_VAD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_TRNS,  KC_BSLS,
                 KC_TRNS,         KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                 KC_TRNS,         KC_TRNS,  KC_TRNS,   			  KC_TAB,             KC_TRNS,  		  KC_TRNS,  KC_TRNS,  KC_TRNS
    ),
};

bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(22, 200, 200, 200);
    }
    if (IS_LAYER_ON(_L1)) {
        rgb_matrix_set_color(35, 0, 200, 200);
    }
    if (IS_LAYER_ON(_L2)) {
        rgb_matrix_set_color(22, 200, 0, 200);
    }
    return false;
}

void keyboard_pre_init_user(void) {
    setPinOutput(B5);
    writePinLow(B5);
}
