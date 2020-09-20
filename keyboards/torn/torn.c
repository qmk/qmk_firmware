/*
 * Copyright 2020 Richard Titmuss <richard.titmuss@gmail.com>
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
#include "torn.h"
#include "i2c_master.h"
#include "mcp23018.h"

static uint8_t led_state[3] = {1, 1, 1};

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    i2c_init();

    matrix_init_user();
}

void matrix_scan_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)
    if (mcp23018_reset_required()) {
        msp23018_init();
        secondary_encoder_init();
        // torn_set_led(2, 1);
    }

    matrix_scan_user();
    secondary_encoder_read();
}

void torn_set_led(uint8_t led, bool state) {
    led_state[led] = !state;

    // toggle leds by setting the pin direction
    uint8_t iodir = 0b11111000 | led_state[0] << 2 | led_state[1] << 1 | led_state[2];
    mcp23018_writeReg(IODIRB, &iodir, 1);
}
