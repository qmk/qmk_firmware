/* Copyright 2021 Pierre-Emmanuel Ott
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

enum custom_layers {
  _QWERTY,
  _LEFTHAND,
  _NUM,
  _FUNC
};

#define SPC_LFT LT(_LEFTHAND, KC_SPC)
#define FN_NUM LT(_NUM, KC_MNXT)
#define BSP_FUNC LT(_FUNC, KC_BSPC)

/* This keymap is a regular 40s keymap for most. My concessions include no numpad, and a dedicated left-hand layer.
Enter is on a layer, which seems somewhat safe! 
Changes/improvements include removing all the Quantum mod functions when on the arrow layer, so that Ctrl and Shift act without ambiguity based on short or long presses.
The 3 LEDs on the board show Caps Lock/L1/L2 respectively. L3 has no LED. 
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT(
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,              KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, 
		KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G,             KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, 
		SC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B,             KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, SC_RSPC, 
		LCTL_T(KC_MPRV), LALT_T(KC_MPLY), FN_NUM, SPC_LFT, BSP_FUNC, LGUI_T(KC_DEL), RALT_T(KC_HOME), RCTL_T(KC_END)
		),
	[_LEFTHAND] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_ESC, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_ENT, 
		KC_LSFT, KC_CALC, KC_MYCM, KC_PSCR, KC_ENT, KC_BSPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RSFT, 
		KC_LCTL, KC_LALT, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_RGUI, KC_PGDN, KC_PGUP
		),
	[_NUM] = LAYOUT(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5,                 KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, 
		KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_PLUS, KC_BSLS, 
		KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RSFT, 
		KC_LCTL, KC_LALT, KC_TRNS, KC_TRNS, 				  KC_TRNS, KC_RGUI, KC_RALT, KC_RCTL
		),
	[_FUNC] = LAYOUT(
		QK_BOOT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,    KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, 
		KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SCRL, KC_PAUS, KC_INS, KC_TRNS, KC_TRNS, 
		KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, KC_RSFT, 
		KC_LCTL, KC_LALT, KC_TRNS, KC_TRNS,          KC_TRNS, KC_RGUI, KC_RALT, KC_RCTL
		)
};

void matrix_init_user(void) {
  // set CapsLock LED to output and low
  setPinOutput(B1);
  writePinLow(B1);
  // set Layer 1 to output and low
  setPinOutput(B2);
  writePinLow(B2);
  // set Layer 2 to output and low
  setPinOutput(B3);
  writePinLow(B3);
}

//function to activate Caps Lock LED
bool led_update_user(led_t led_state) {
    writePin(B1, led_state.caps_lock);
    return false;
}

//function for layer indicator LED
layer_state_t layer_state_set_user(layer_state_t state)
{
    if (get_highest_layer(state) == 1) {
    writePinHigh(B2);
	} 
	else {
		writePinLow(B2);
    }
	if (get_highest_layer(state) == 2) {
    writePinHigh(B3);
	} 
	else {
		writePinLow(B3);
    }
    return state;
}