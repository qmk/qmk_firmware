/*
Copyright 2020 Cloudboards
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


bool numlock_status = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT_numpad_5x4_Base(
		KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, 
    	KC_P7,   KC_P8,   KC_P9,            
    	KC_P4,   KC_P5,   KC_P6,   KC_PPLS, 
    	KC_P1,   KC_P2,   KC_P3,            
    	KC_P0,   KC_PDOT, KC_PENT  
	),
};


// void keyboard_pre_init_user(void) {
//   // Call the keyboard pre init code.

//   // Set our LED pins as output (I don't have the pin sheet with me right now sorry carter lol)
//   setPinOutput();
//   setPinOutput();
//   setPinOutput();
// }

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  debug_mouse=true;
}


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

//Encoder stuff
void encoder_update_user(uint8_t index, bool clockwise) {
    if(index == 0){
        if (clockwise) {
        tap_code(KC_VOLU);
      } else {
        tap_code(KC_VOLD);
      }
    }
}

//OLED stuff
#ifdef OLED_DRIVER_ENABLE

//Need logo here, gotta find some converter online
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x00
    };

    oled_write_P(qmk_logo, false);
}

static const char PROGMEM numlock_on[] = {
  0x4E, 0x55, 0x4D, 0x20, 0x20, 0x99, 0x9A, 0x00
};

static const char PROGMEM numlock_off[] = {
  0x20, 0x20, 0x20, 0x20, 0x20, 0x99, 0x9A, 0x00
};



oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_0;
}

void oled_task_user(void) {
  render_status();
}
#endif

void led_set_user(uint8_t usb_led) {

}