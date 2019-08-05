/* Copyright 2019 kratsyn
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
#include "syn_c.h"
#include "hal.h"

#define LED_ON()        palSetLine(C13);
#define LED_OFF()       palClearLine(C13);

keyboard_config_t keyboard_config;

void keyboard_pre_init_kb(void) {
    // read kb settings from eeprom
    keyboard_config.raw = eeconfig_read_kb();

	// start backlight
	backlight_init_ports();
}

// initialization overloads
void matrix_init_kb(void) {
    // Intitialize the pins we need to initialize
    palSetLineMode(C13, PAL_MODE_OUTPUT_PUSHPULL);

    // flash the MCU LED
    blink_led(3);
    dprintf("[SYS] Startup complete.\n");
    LED_ON();


    // continue startup
    matrix_init_user();
}

void eeconfig_init_kb(void) {
    keyboard_config.raw = 0;
    keyboard_config.led_level = 4;
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}

void blink_led(uint8_t times) {
    while ( times-- ) {
        LED_ON();
        wait_ms(200);
        LED_OFF();
        wait_ms(200);
    }
}

void matrix_scan_kb(void) {
  matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  return process_record_user(keycode, record);
}
