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
#include "proton_c.h"
#include "hal.h"
#include "eeconfig.h"
#include "backlight_led.h"

#define LED_ON()        palSetLine(C13);
#define LED_OFF()       palClearLine(C13);

// overloads
void matrix_init_kb(void) {
    // enable status led on C13 and flash it a few times 
    palSetLineMode(C13, PAL_MODE_OUTPUT_PUSHPULL);
    blink_led(3);

	// start backlight
	backlight_init_kb();

    // continue startup
    matrix_init_user();
}

// blink the MCU LED every 200ms 
void blink_led(uint8_t times) {
    while ( times-- ) {
        LED_ON();
        wait_ms(200);
        LED_OFF();
        wait_ms(200);
    }
}
