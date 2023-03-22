/* 
Copyright 2021 owlab
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "print.h"
#include "os_detection.h"

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}




//定义一个新键码
enum custom_keycodes {
    KC_00 = SAFE_RANGE,
    KC_WINLK, // Toggles Win key on and off
    KC_WINLK1,
    KC_WINLK2,
};
bool is_app_active = true; // 空格键是否激活
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif 
uprintf("OS=%u\n", detected_host_os());
	
	switch (keycode) {

       
    case KC_WINLK:
        if (record->event.pressed) {// 按下此按键触发以下行为 
            if(!keymap_config.no_gui) {
                process_magic(GUI_OFF, record);
            } else {
                process_magic(GUI_ON, record);
            }
        } else  unregister_code16(keycode);
        break;

    case KC_APP:
        if (keymap_config.no_gui)
            return false;
        break;
        
    }
    
    return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


	[0] = LAYOUT(
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_PSCR, KC_PSCR, KC_PAUS, 
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,     KC_ENT,  
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,             KC_RSFT,                KC_UP,
		KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT,   MO(1), KC_APP, KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT
	),
	[1] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______,          _______, _______, _______, 
		_______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT, _______, _______, _______,
		_______, _______, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______,
		_______, _______, _______, RGB_HUI, _______, _______, _______, NK_TOGG, _______, _______, _______,              _______,               RGB_MOD,
		 EE_CLR, KC_WINLK, _______,                            _______,                            _______, _______, KC_WINLK1, _______, RGB_SPD, RGB_RMOD, RGB_SPI
	),

	[2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______,               _______,
		_______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______
	),

	[3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______,               _______,
		_______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______
	)
};


