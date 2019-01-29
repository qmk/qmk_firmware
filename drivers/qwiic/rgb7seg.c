/* Copyright 2017 Jason Williams
 * Copyright 2017 Jack Humbert
 * Copyright 2018 Yiancar
 * Copyright 2019 Clueboard
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

#include <stdint.h>
#include <stdbool.h>
#include "quantum.h"
#include "rgb7seg.h"
#include "is31fl3235a.h"
#include "progmem.h"
#include "config.h"
#include "eeprom.h"
#include <string.h>
#include <math.h>

#ifndef MAX
    #define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#endif

#ifndef MIN
    #define MIN(a,b) ((a) < (b)? (a): (b))
#endif

// State variables
uint32_t g7_tick = 0;      // Global tick at 20 Hz
bool rgb7seg_enabled = 0;  // Whether or not the display is turned on

/*
const rgb7seg_led g_rgb7seg_leds[IS31FL3235A_COUNT * 8][4] = {
/ * Refer to IS31 manual for these locations
 *  driver
 *  |   R LED address
 *  |   |      G LED address
 *  |   |      |      B LED address
 *  |   |      |      | * /
    {0, OUT17, OUT16, OUT15},  // A, top middle
    {0, OUT22, OUT21, OUT20},  // B, top right
    {0, OUT26, OUT27, OUT28},  // C, bottom right
    {0, OUT1,  OUT2,  OUT3},   // D, bottom center
    {0, OUT23, OUT24, OUT25},  // DP, dot
    {0, OUT4,  OUT5,  OUT6},   // E, bottom left
    {0, OUT9,  OUT7,  OUT8},   // F, top left
    {0, OUT14, OUT13, OUT12},  // G, center
    #if IS31FL3235A_COUNT > 1
    {1, OUT17, OUT16, OUT15},  // A, top middle
    {1, OUT22, OUT21, OUT20},  // B, top right
    {1, OUT26, OUT27, OUT28},  // C, bottom right
    {1, OUT1,  OUT2,  OUT3},   // D, bottom center
    {1, OUT23, OUT24, OUT25},  // DP, dot
    {1, OUT4,  OUT5,  OUT6},   // E, bottom left
    {1, OUT9,  OUT7,  OUT8},   // F, top left
    {1, OUT14, OUT13, OUT12},  // G, center
    #endif
    #if IS31FL3235A_COUNT > 2
    {2, OUT17, OUT16, OUT15},  // A, top middle
    {2, OUT17, OUT16, OUT15},  // A, top middle
    {2, OUT22, OUT21, OUT20},  // B, top right
    {2, OUT26, OUT27, OUT28},  // C, bottom right
    {2, OUT1,  OUT2,  OUT3},   // D, bottom center
    {2, OUT23, OUT24, OUT25},  // DP, dot
    {2, OUT4,  OUT5,  OUT6},   // E, bottom left
    {2, OUT9,  OUT7,  OUT8},   // F, top left
    {2, OUT14, OUT13, OUT12},  // G, center
    #endif
    #if IS31FL3235A_COUNT > 3
    {3, OUT17, OUT16, OUT15},  // A, top middle
    {3, OUT22, OUT21, OUT20},  // B, top right
    {3, OUT26, OUT27, OUT28},  // C, bottom right
    {3, OUT1,  OUT2,  OUT3},   // D, bottom center
    {3, OUT23, OUT24, OUT25},  // DP, dot
    {3, OUT4,  OUT5,  OUT6},   // E, bottom left
    {3, OUT9,  OUT7,  OUT8},   // F, top left
    {3, OUT14, OUT13, OUT12},  // G, center
    {3, OUT22, OUT21, OUT20},  // B, top right
    #endif
};
*/

// API
void rgb7seg_flush(void) {
    IS31FL3235A_update_pwm_buffers(IS31FL3235A_DRIVER_ADDR_1, 0);
    #if IS31FL3235A_COUNT > 1
        IS31FL3235A_update_pwm_buffers(IS31FL3235A_DRIVER_ADDR_2, 1);
    #endif
    #if IS31FL3235A_COUNT > 2
        IS31FL3235A_update_pwm_buffers(IS31FL3235A_DRIVER_ADDR_3, 2);
    #endif
    #if IS31FL3235A_COUNT > 3
        IS31FL3235A_update_pwm_buffers(IS31FL3235A_DRIVER_ADDR_4, 3);
    #endif
}

void rgb7seg_set_index_value(int index, uint8_t value) {
    IS31FL3235A_set_value(index, value);
}

void rgb7seg_set_index_value_all(uint8_t value) {
    IS31FL3235A_set_value_all(value);
}

// All LEDs off
void rgb7seg_off(void) {
    rgb7seg_set_index_value_all(0);
}

void rgb7seg_task(void) {
    g7_tick++;

    // Do something here?

    // Tell the LED driver to update its state
    rgb7seg_flush();
}

void rgb7seg_init(void) {
    #ifdef IS31FL3235A_DRIVER_ADDR_1
        IS31FL3235A_init(IS31FL3235A_DRIVER_ADDR_1);
    #endif
    #ifdef IS31FL3235A_DRIVER_ADDR_2
        IS31FL3235A_init(IS31FL3235A_DRIVER_ADDR_2);
    #endif
    #ifdef IS31FL3235A_DRIVER_ADDR_3
        IS31FL3235A_init(IS31FL3235A_DRIVER_ADDR_3);
    #endif
    #ifdef IS31FL3235A_DRIVER_ADDR_4
        IS31FL3235A_init(IS31FL3235A_DRIVER_ADDR_4);
    #endif

    // Wait half a second for the driver to finish initializing
    wait_ms(500);
}

uint32_t rgb7seg_get_tick(void) {
    return g7_tick;
}

void rgb7seg_toggle(void) {
    rgb7seg_enabled ^= 1;
}

void rgb7seg_enable(void) {
    rgb7seg_enabled = 1;
}

void rgb7seg_disable(void) {
    rgb7seg_enabled = 0;
}

void rgb7seg_increase_val(void) {
    // FIXME: Implement
}

void rgb7seg_decrease_val(void) {
    // FIXME: Implement
}
