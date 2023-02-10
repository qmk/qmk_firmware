/* Copyright 2018-2021 James Laird-Wah, Islam Sharabash
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

#include "quantum.h"
#include "i2c_master.h"
#include "led_tables.h"
#include "rgb_matrix.h"
#include <string.h>
#include "raise.h"
#include "wire-protocol-constants.h"
#include "print.h"
#include "leds.h"

// Color order of LEDs is Green, Red, Blue.
typedef struct PACKED {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} raiseRGB;

#define LEDS_PER_HAND 72
#define LED_BANKS 9
#define LEDS_PER_BANK 8
#define LED_BYTES_PER_BANK (sizeof(raiseRGB) * LEDS_PER_BANK)

// shifting << 1 is because drivers/chibios/i2c_master.h expects the address
// shifted.
// 0x58 and 0x59 are the addresses defined in dygma/raise/Hand.h
#define I2C_ADDR_LEFT (0x58 << 1)
#define I2C_ADDR_RIGHT (0x59 << 1)
#define I2C_ADDR(hand) ((hand) ? I2C_ADDR_RIGHT : I2C_ADDR_LEFT)
#define LEFT 0
#define RIGHT 1

static raiseRGB led_pending[2 * LEDS_PER_HAND];
static raiseRGB led_state[2 * LEDS_PER_HAND];

static void set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
    int sled = led_map[index];
    // The red component of the LED is apparently stronger than the others.
    // From: https://github.com/keyboardio/Kaleidoscope/blob/aba8c9ee66bbb5ded15135618d2b2964ee82b2cc/plugins/Kaleidoscope-Hardware-Dygma-Raise/src/kaleidoscope/device/dygma/raise/RaiseSide.cpp#L235-L242
    if (r >= 26) {
        r -= 26;
    }
    led_pending[sled].r = r;
    led_pending[sled].g = g;
    led_pending[sled].b = b;
}

static void set_color_all(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) set_color(i, r, g, b);
}

static void init(void) {
    set_color_all(0,0,0);
}

static void flush(void) {
    uint8_t  command[1 + LED_BYTES_PER_BANK];

    // SUBTLE(ibash) alternate hands when transmitting led data, otherwise the
    // mcu in the hand seems to have trouble keeping up with the i2c
    // transmission
    for (int bank = 0; bank < LED_BANKS; bank++) {
        for (int hand = 0; hand < 2; hand++) {
            int addr = I2C_ADDR(hand);
            int i = (hand * LEDS_PER_HAND) + (bank * LEDS_PER_BANK);

            if (memcmp(&led_state[i], &led_pending[i], LED_BYTES_PER_BANK) == 0) {
                // No change.
                continue;
            }

            // Update LED state
            memcpy(&led_state[i], &led_pending[i], LED_BYTES_PER_BANK);

            command[0] = TWI_CMD_LED_BASE + bank;
            memcpy(&command[1], &led_pending[i], LED_BYTES_PER_BANK);
            i2c_transmit(addr, command, sizeof(command), I2C_TIMEOUT);

            // delay to prevent issues with the i2c bus
            wait_us(10);
        }
    }
}

const rgb_matrix_driver_t rgb_matrix_driver = {.init = init, .flush = flush, .set_color = set_color, .set_color_all = set_color_all};
