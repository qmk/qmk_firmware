/*
Copyright 2020 Seth Bonner <fl3tching101@gmail.com>
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


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0

// Use the following format to create custom key codes to make macros out of and such
/*
enum custom_keycodes {
 FOO = SAFE_RANGE,
};
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_BASE] = LAYOUT_default(
   RGB_MODE_FORWARD,                KC_NUMLOCK,
   KC_KP_7, KC_KP_8, KC_KP_9,       KC_DELETE,
   KC_KP_4, KC_KP_5, KC_KP_6,       KC_END,
   KC_KP_1, KC_KP_2, KC_KP_3,       KC_AUDIO_VOL_UP,
   KC_KP_0, RGB_TOG, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN
 )
};

void encoder_update_user(uint8_t index, bool clockwise){
  if(index == 0) { // first encoder
    if(clockwise){
      tap_code(KC_AUDIO_VOL_UP);
    }else{
      tap_code(KC_AUDIO_VOL_DOWN);
    }
  }else if(index == 1){ // second encoder
    if(clockwise){
      tap_code(KC_NO);
      // To be added back when bug fix is found
      //tap_code(RGB_VAI);
    }else{
      rgblight_decrease_val();
    }
  }
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

void oled_task_user(void) {
    // Print "Hello world!" to the OLED display to test functionality
    oled_write_P(PSTR("Hello world!\n"), false);
    oled_write_P(PSTR("Hello world line 2!\n"), false);
    oled_write_P(PSTR("Hello world line 3!\n"), false);

/* Implement eventually?
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
*/
}
#endif
