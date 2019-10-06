/* Copyright 2019 mechmerlin
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
#include "rgblight.h"
#include "i2c_master.h"
#include "quantum.h"

#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;

void rgblight_set(void) {
    if (!rgblight_config.enable) {
        for (uint8_t i = 0; i < RGBLED_NUM; i++) {
            led[i].r = 0;
            led[i].g = 0;
            led[i].b = 0;
        }
    }

    i2c_init();
    i2c_transmit(0xb0, (uint8_t*)led, 3 * RGBLED_NUM, 100);
}
#endif

void matrix_init_kb(void) {
#ifdef RGBLIGHT_ENABLE
    if (rgblight_config.enable) {
        i2c_init();
        i2c_transmit(0xb0, (uint8_t*)led, 3 * RGBLED_NUM, 100);
    }
#endif
    // call user level keymaps, if any
    matrix_init_user();
}

void matrix_scan_kb(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_task();
#endif
    matrix_scan_user();
    /* Nothing else for now. */
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

void backlight_init_ports(void) {
    // initialize pins D0, D1, D4 and D6 as output
    setPinOutput(D0);
    setPinOutput(D1);
    setPinOutput(D4);
    setPinOutput(D6);

    // turn backlight LEDs on
    writePinHigh(D0);
    writePinHigh(D1);
    writePinHigh(D4);
    writePinHigh(D6);
}

void backlight_set(uint8_t level) {
	if (level == 0) {
        // turn backlight LEDs off
        writePinLow(D0);
        writePinLow(D1);
        writePinLow(D4);
        writePinLow(D6);
	} else {
        // turn backlight LEDs on
        writePinHigh(D0);
        writePinHigh(D1);
        writePinHigh(D4);
        writePinHigh(D6);
	}
}
