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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
		KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_DEL, KC_BSPC,
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_QUOT, KC_ENT,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, MO(1), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_LSFT,
		BL_TOGG, BL_STEP,  KC_RBRC, MO(1),	KC_SPC, KC_MINS, KC_LGUI, TO(1)
    )
	/*
	LAYOUT(
		KC_Q, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_DEL, KC_BSPC,
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_QUOT, KC_ENT,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, MO(1), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_LSFT,
		KC_LCTL, KC_LALT,  KC_RBRC, MO(1),	KC_SPC, KC_MINS, KC_LGUI, TO(0)
	),
	
	LAYOUT(
		KC_Q, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_DEL, KC_BSPC,
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_QUOT, KC_ENT,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, MO(1), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_LSFT,
		KC_LCTL, KC_LALT,  KC_RBRC, MO(1),	KC_SPC, KC_MINS, KC_LGUI, TO(0)
	),
	
	LAYOUT(
		KC_Q, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_DEL, KC_BSPC,
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_QUOT, KC_ENT,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, MO(1), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_LSFT,
		KC_LCTL, KC_LALT,  KC_RBRC, MO(1),	KC_SPC, KC_MINS, KC_LGUI, TO(0)
	)*/
};



void matrix_init_user(void) {
  // set CapsLock LED to output and low
  DDRB |= (1 << 1);
  PORTB &= ~(1 << 1);
  // set NumLock LED to output and low
  DDRB |= (1 << 2);
  PORTB &= ~(1 << 2);
  // set ScrollLock LED to output and low
  DDRB |= (1 << 3);
  PORTB &= ~(1 << 3);
}

void matrix_scan_user(void) {

}


void led_set_user(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_NUM_LOCK)) {
    PORTB |= (1<<2);
  } else {
    PORTB &= ~(1<<2);
  }
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    PORTB |= (1<<1);
  } else {
    PORTB &= ~(1<<1);
  }
/*  
  if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
    PORTB |= (1<<3);
  } else {
    PORTB &= ~(1<<3);
  }*/
  
}

//function for layer indicator LED
uint32_t layer_state_set_user(uint32_t state)
{
    if (biton32(state) == 1) {
        PORTB |= (1<<3);
	} else {
		PORTB &= ~(1<<3);
    }
    return state;
}
