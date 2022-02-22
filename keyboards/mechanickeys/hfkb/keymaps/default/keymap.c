/* Copyright 2022 jfescobar18
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
  [0] = LAYOUT_all( /* 0: qwerty */
    KC_ESC,  KC_F1,   KC_F2,   KC_F3, KC_F4, KC_F5, KC_F6,  KC_F7, KC_F8, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
    
    KC_GRV,  KC_1,    KC_2,    KC_3,  KC_4,  KC_5,  KC_6,   KC_7,  KC_8,  KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSLS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,  KC_T,  KC_Y,   KC_U,  KC_I,  KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_ENT,
    KC_CAPS, KC_A,    KC_S,    KC_D,  KC_F,  KC_G,  KC_H,   KC_J,  KC_K,  KC_L,    KC_SCLN, KC_QUOT,          KC_BSLS,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,  KC_C,  KC_V,  KC_B,   KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(1),
             KC_LALT, KC_LGUI,                      KC_SPC,               KC_RGUI, KC_RALT
  ),

  [1] = LAYOUT_all( /* 1: media and nav */
    KC_TRNS, KC_BRID, KC_BRIU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS,
    
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
             KC_TRNS, KC_TRNS,                            KC_TRNS,                   KC_TRNS, KC_TRNS
  ),
};

void keyboard_pre_init_kb(void) {
    setPinOutput(LED_00);
    setPinOutput(LED_01);
    setPinOutput(LED_02);
    keyboard_pre_init_user();
}

void shutdown_user() {
    writePinLow(LED_00);
    writePinLow(LED_01);
    writePinLow(LED_02);
}

void matrix_init_kb(void) {
    uint8_t led_delay_ms = 80;
    for (int i = 0; i < 2; i++) {
        writePinHigh(LED_00);
        writePinHigh(LED_01);
        writePinHigh(LED_02);
        wait_ms(led_delay_ms);
        writePinLow(LED_00);
        writePinLow(LED_01);
        writePinLow(LED_02);
        if (i < 1) {
            wait_ms(led_delay_ms);
        }
    }

    matrix_init_user();
}

layer_state_t layer_state_set_user(layer_state_t state) {
    writePin(LED_00, layer_state_cmp(state, 1));
    writePin(LED_01, layer_state_cmp(state, 2));
    writePin(LED_02, layer_state_cmp(state, 3));
    
    return state;
}
