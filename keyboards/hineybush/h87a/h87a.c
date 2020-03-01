/* Copyright 2018 Josh Hinnebusch
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
#include "h87a.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
   	setPinOutput(D5);
    setPinOutput(E6);
}

bool led_update_kb(led_t led_state) {
    writePin(D5, !led_state.caps_lock);
    writePin(E6, !led_state.scroll_lock);
    return true;
}

void eeconfig_init_kb(void) {  // EEPROM is getting reset!
  rgblight_enable(); // Enable RGB by default
  rgblight_sethsv(0, 255, 128);  // Set default HSV - red hue, full saturation, medium brightness
  rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 2); // set to RGB_RAINBOW_SWIRL by default
  
  eeconfig_update_kb(0);
}
