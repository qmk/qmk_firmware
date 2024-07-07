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
		KC_ESC,   KC_Q,     KC_W,     KC_E,   KC_R,    KC_T,          KC_Y,   KC_U,     KC_I, KC_O,    KC_P,    KC_DEL, KC_BSPC,
		KC_TAB,   KC_A,     KC_S,     KC_D,   KC_F,    KC_G,          KC_H,   KC_J,     KC_K, KC_L,    KC_QUOT, KC_ENT,
		KC_LSFT,  KC_Z,     KC_X,     KC_C,   KC_V,    KC_B,          MO(3),  KC_N,     KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT,
		KC_LCTL,  KC_LALT,                    MO(2), MO(1),	          KC_SPC, KC_RALT,                          KC_RGUI, KC_RCTL
    ),

    LAYOUT(
		KC_GRV,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,    KC_UP,     KC_TRNS,   KC_MUTE,   KC_VOLD,   KC_VOLU,
		KC_CAPS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_LEFT,    KC_DOWN,   KC_RIGHT,  KC_SCLN,   KC_BSLS,
		KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
		BL_TOGG,   BL_STEP,                         KC_TRNS,    KC_TRNS,	        KC_TRNS,   KC_TRNS,                                     KC_TRNS,   KC_TRNS
    ),

    LAYOUT(
		KC_TRNS,  KC_1,      KC_2,      KC_3,      KC_4,       KC_5,             KC_6,      KC_7,     KC_8,    KC_9,    KC_0,      KC_MINS,  KC_EQL,
		KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_P4,    KC_P5,   KC_P6,   KC_LBRC,   KC_RBRC,
		KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_P1,    KC_P2,   KC_P3,   KC_TRNS,   KC_TRNS,  KC_TRNS,
		KC_TRNS,  KC_TRNS,                         KC_TRNS,    KC_TRNS,	         KC_PENT,   KC_PDOT,                               KC_TRNS,  KC_TRNS
    ),

    LAYOUT(
		KC_TRNS,  KC_F1,     KC_F2,     KC_F3,     KC_F4,      KC_F5,            KC_F6,     KC_F7,    KC_F8,   KC_F9,   KC_F10,    KC_F11,   KC_F12,
		KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,
		KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,  KC_TRNS,
		KC_TRNS,  KC_TRNS,                         KC_TRNS,    KC_TRNS,	         KC_TRNS,   KC_TRNS,                               KC_TRNS,  KC_TRNS
    ),

    LAYOUT(
		KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
		KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
		KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
		KC_TRNS,   KC_TRNS,                         KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,                                     KC_TRNS,   KC_TRNS
    ),

    LAYOUT(
		KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
		KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
		KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
		KC_TRNS,   KC_TRNS,                         KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,                                     KC_TRNS,   KC_TRNS
    ),

    LAYOUT(
		KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
		KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
		KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
		KC_TRNS,   KC_TRNS,                         KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,                                     KC_TRNS,   KC_TRNS
    ),

    LAYOUT(
		KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
		KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
		KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
		KC_TRNS,   KC_TRNS,                         KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,                                     KC_TRNS,   KC_TRNS
    )
};

void matrix_init_user(void) {
  // set CapsLock LED to output and low
  gpio_set_pin_output(B1);
  gpio_write_pin_low(B1);
  // set NumLock LED to output and low
  gpio_set_pin_output(B2);
  gpio_write_pin_low(B2);
  // set ScrollLock LED to output and low
  gpio_set_pin_output(B3);
  gpio_write_pin_low(B3);
}

bool led_update_user(led_t led_state) {
  if (led_state.num_lock) {
    gpio_write_pin_high(B2);
  } else {
    gpio_write_pin_low(B2);
  }
  if (led_state.caps_lock) {
    gpio_write_pin_high(B1);
  } else {
    gpio_write_pin_low(B1);
  }
  return false;
}

//function for layer indicator LED
layer_state_t layer_state_set_user(layer_state_t state)
{
    if (get_highest_layer(state) == 1) {
    gpio_write_pin_high(B3);
	} else {
		gpio_write_pin_low(B3);
    }
    return state;
}
