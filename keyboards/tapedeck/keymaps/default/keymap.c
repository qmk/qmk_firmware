/* Copyright 2023 Gowla
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
#include "print.h"

#define BASE 0 

#ifdef POT_ENABLE
  #include "analog.h"
#endif

int16_t pot_val = 0;
int16_t prev_val = 0;
int16_t val = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_ESC, 			KC_MNXT, 			KC_MPLY, 	KC_MNXT, KC_MPLY,
        RGB_MODE_RAINBOW,   RGB_MODE_RGBTEST,   RGB_M_K, 	RGB_TOG, KC_MPLY,
        KC_F1,        		KC_F2, 				KC_F3, 			KC_F14
    )
};

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
		  tap_code(KC_WH_U);
		} else {
		  tap_code(KC_WH_D);
		}
	} else if (index == 1) { /* Second encoder */
		if (clockwise) {
		  tap_code(KC_BRIU);
		} else {
		  tap_code(KC_BRID);
		}
	  }
	
	return false;
};

void matrix_init_user(void) {
#ifdef POT_ENABLE
    analogReference(ADC_REF_POWER);
#endif
}

uint8_t divisor = 0;

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void slider(void) {
    if (divisor++) { // only run the slider function 1/256 times it's called
        return;
    }

    pot_val = analogReadPin(D4);
	val = map(pot_val, 0, 1023, 1, 50);

	if (( val > (prev_val + 1)) && val != prev_val){
		int i;
		for (i = prev_val; i < val; i++ )
				{tap_code(KC_VOLU);}
	}
	if ((val  < (prev_val - 1)) && val != prev_val){
		int i;
		for (i = val; i < prev_val; i++ )
				{tap_code(KC_VOLD);}
	}
	prev_val = val;
}

void matrix_scan_user(void) {
#ifdef POT_ENABLE
	slider();
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
	#ifdef CONSOLE_ENABLE
		uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
	#endif 
	  return true;
}

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
	// led hue, sat, val, led
	rgblight_sethsv_range(HSV_GREEN, 0, 2);
	rgblight_sethsv_noeeprom(HSV_GREEN);
}
#endif






