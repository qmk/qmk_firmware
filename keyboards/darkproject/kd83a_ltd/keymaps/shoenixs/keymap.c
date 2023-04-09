/* Copyright 2022 GSKY <gskyGit@gsky.com.tw>
 * Copyright 2023 SHVD3x https://t.me/shvd3x
 * Copyright 2023 Shoenixs https://t.me/Shoenixs
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

//LEDS
//Верхний (Top) - C14 
//Средний (Midle) - C15
//Нижний (Lower) - C0 

#include QMK_KEYBOARD_H

enum custom_layers {
    Win,
    Winfn,
    Win1,

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[Win] = LAYOUT(
  KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_MPLY,
  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_PGUP, 
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGDN,    
  MO(Win1), KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,   KC_END,    
  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,    KC_DEL,    
  KC_LCTL,  KC_LGUI,  KC_LALT,                      KC_SPC,                                 KC_RALT,  MO(Winfn),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[Winfn] = LAYOUT(
  QK_BOOT,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_SLEP,  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_BRIU, 
  KC_TRNS,  RGB_VAI,  RGB_SAI,  RGB_HUI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_BRID,    
  KC_TRNS,  RGB_VAD,  RGB_SAD,  RGB_HUD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,    
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            RGB_MOD,  KC_TRNS,    
  KC_TRNS,  KC_TRNS,  KC_TRNS,                      MAGIC_TOGGLE_NKRO,                      KC_TRNS,  KC_TRNS,  KC_TRNS,  RGB_HUD,  RGB_RMOD, RGB_HUI),

[Win1] = LAYOUT(
  QK_BOOT,  KC_F13,   KC_F14,   KC_F15,   KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,   KC_F21,   KC_F22,   KC_F23,   KC_F24,   KC_TRNS,  KC_TRNS, 
  KC_MPLY,  KC_MPRV,  KC_MNXT,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, 
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,    
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,    
  KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [Win] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
        [Winfn] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
        [Win1] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)  },
};
#endif

void led_init_ports(void) {
  setPinOutput(C0); 
  setPinOutput(C14);
  setPinOutput(C15);
  writePinLow(C15);
  writePinLow(C0);
  writePinHigh(C14);
};

layer_state_t layer_state_set_user(layer_state_t state) {

    writePin(C0, layer_state_cmp(state, 1));
	writePin(C15, layer_state_cmp(state, 2));

    return state;

};
