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
      rgblight_increase_val();
    }else{
      rgblight_decrease_val();
    }
  }
}

#ifdef OLED_DRIVER_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write(qmk_logo, false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

void oled_task_user(void) {
    uint8_t light_level = rgblight_get_val();
    light_level = (uint8_t)(100.0 * ((float)light_level/(float)RGBLIGHT_LIMIT_VAL)); // Convert to %
    char c_light_level[3];
    itoa(light_level, c_light_level, 10);

    render_logo(); // Render the QMK logo
    oled_write_ln(PSTR(""), false); // Add a newline
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write(led_state.num_lock ? PSTR("   |NUM|") : PSTR("   |   |"), false);
    oled_write(led_state.caps_lock ? PSTR("|CAP|") : PSTR("|   |"), false);
    oled_write(led_state.scroll_lock ? PSTR("|SCR|   ") : PSTR("|   |   "), false);

    oled_write_ln(PSTR(""), false); // Add a newline
    oled_write(PSTR("    BKLT: "), false);
    oled_write(c_light_level, false);
    oled_write_ln(PSTR("%    "), false);
}
#endif
