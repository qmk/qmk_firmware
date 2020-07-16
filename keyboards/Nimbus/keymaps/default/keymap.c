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
#include <print.h>


bool numlock_status = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT_numpad_5x4(
		KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    	KC_P7,   KC_P8,   KC_P9, 
    	KC_P4,   KC_P5,   KC_P6, KC_PPLS, 
    	KC_P1,   KC_P2,   KC_P3, 
    	KC_P0,   KC_PDOT, KC_PENT
	),
};


void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output (I don't have the pin sheet with me right now sorry carter lol)
  setPinOutput(C7);

}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  debug_mouse=true;

  rgblight_enable();
  rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 5);
}


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

//Encoder stuff
//https://beta.docs.qmk.fm/using-qmk/hardware-features/feature_encoders
void encoder_update_user(uint8_t index, bool clockwise) {
    backlight_enable();
    if(index == 0){
        if (clockwise) {
          dprint("Vol going up");
        tap_code(KC_VOLU);
        backlight_increase();
      } else {
          dprint("Vol going down");
        tap_code(KC_VOLD);
        backlight_decrease();
      }
    }
}

//OLED stuff
#ifdef OLED_DRIVER_ENABLE

//http://www.majer.ch/lcd/adf_bitmap.php
//Make a logo now
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}



// static const char PROGMEM numlock_on[] = {
//   0x4E, 0x55, 0x4D, 0x20, 0x20, 0x99, 0x9A, 0x00
// };

// static const char PROGMEM numlock_off[] = {
//   0x20, 0x20, 0x20, 0x20, 0x20, 0x99, 0x9A, 0x00
// };

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_0;
}

void oled_task_user(void) {
  render_logo();
}
#endif

//DEBUG stuff to see if presses work and what not.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
  return true;
}


void led_set_user(uint8_t usb_led) {

}
