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

struct __attribute__((packed)) cRGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

#define LEDS_PER_HAND 72
#define LED_BANKS 9
#define LEDS_PER_BANK 8
#define LED_BYTES_PER_BANK (sizeof(cRGB) * LEDS_PER_BANK)

// shifting << 1 is because drivers/chibios/i2c_master.h expects the address
// shifted.
// 0x58 and 0x59 are the addresses defined in dygma/raise/Hand.h
#define I2C_ADDR_LEFT (0x58 << 1)
#define I2C_ADDR_RIGHT (0x59 << 1)
#define I2C_ADDR(hand) ((hand) ? I2C_ADDR_RIGHT : I2C_ADDR_LEFT)
#define LEFT 0
#define RIGHT 1

static cRGB led_state[2 * LEDS_PER_HAND];

void set_all_leds_to(uint8_t r, uint8_t g, uint8_t b) {
    uint8_t buf[] = {TWI_CMD_LED_SET_ALL_TO, b, g, r};
    i2c_transmit(I2C_ADDR(LEFT), buf, sizeof(buf), I2C_TIMEOUT);
    wait_us(10);
    i2c_transmit(I2C_ADDR(RIGHT), buf, sizeof(buf), I2C_TIMEOUT);
    wait_us(10);
}

void set_led_to(int led, uint8_t r, uint8_t g, uint8_t b) {
    int     sled  = led_map[led];
    uint8_t buf[] = {TWI_CMD_LED_SET_ONE_TO, sled & 0x1f, b, g, r};
    int     hand  = (sled >= LEDS_PER_HAND) ? RIGHT : LEFT;
    i2c_transmit(I2C_ADDR(hand), buf, sizeof(buf), I2C_TIMEOUT);
    wait_us(10);
}

static void set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
    int sled = led_map[index];

    led_state[sled].r = r;
    led_state[sled].g = g;
    led_state[sled].b = b;
}

static void set_color_all(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) set_color(i, r, g, b);
}

static void init(void) {}

static void flush(void) {
    uint8_t  command[1 + LED_BYTES_PER_BANK];

    // SUBTLE(ibash) alternate hands when transmitting led data, otherwise the
    // mcu in the hand seems to have trouble keeping up with the i2c
    // transmission
    for (int bank = 0; bank < LED_BANKS; bank++) {
        for (int hand = 0; hand < 2; hand++) {
            int addr = I2C_ADDR(hand);
            int i = (hand * LEDS_PER_HAND) + (bank * LEDS_PER_BANK);
            uint8_t *bank_data = (uint8_t *)&led_state[i];

            command[0] = TWI_CMD_LED_BASE + bank;
            memcpy(&command[1], bank_data, LED_BYTES_PER_BANK);
            i2c_transmit(addr, command, sizeof(command), I2C_TIMEOUT);

            // delay to prevent issues with the i2c bus
            wait_us(10);
        }
    }
}

const rgb_matrix_driver_t rgb_matrix_driver = {.init = init, .flush = flush, .set_color = set_color, .set_color_all = set_color_all};
