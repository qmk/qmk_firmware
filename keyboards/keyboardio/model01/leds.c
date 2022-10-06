/* Copyright 2018 James Laird-Wah
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
#include "model01.h"

#define I2C_TIMEOUT     1000

void set_all_leds_to(uint8_t r, uint8_t g, uint8_t b) {
  uint8_t buf[] = {
    TWI_CMD_LED_SET_ALL_TO,
    b, g, r
  };
  i2c_transmit(I2C_ADDR(LEFT), buf, sizeof(buf), I2C_TIMEOUT);
  i2c_transmit(I2C_ADDR(RIGHT), buf, sizeof(buf), I2C_TIMEOUT);
  _delay_us(10);
}

void set_led_to(int led, uint8_t r, uint8_t g, uint8_t b) {
  uint8_t buf[] = {
    TWI_CMD_LED_SET_ONE_TO,
    led & 0x1f,
    b, g, r
  };
  int hand = (led >= 32) ? RIGHT : LEFT;
  i2c_transmit(I2C_ADDR(hand), buf, sizeof(buf), I2C_TIMEOUT);
  _delay_us(10);
}

#ifdef RGB_MATRIX_ENABLE

__attribute__ ((weak))
led_config_t g_led_config = { {
    {  27,  26,  20,  19,  12,  11,   4,   3 },
    {  28,  25,  21,  18,  13,  10,   5,   2 },
    {  29,  24,  22,  17,  14,   9,   6,   1 },
    {  30,  31,  23,  16,  15,   8,   7,   0 },
    {  60,  59,  52,  51,  44,  43,  37,  36 },
    {  61,  58,  53,  50,  45,  42,  38,  35 },
    {  62,  57,  54,  49,  46,  41,  39,  34 },
    {  63,  56,  55,  48,  47,  40,  32,  33 }
}, {
    {   3,  35 }, {   0,  26 }, {   0,  17 }, {   0,   6 }, {  14,   5 }, {  15,  16 }, {  16,  25 }, {  17,  34 },
    {  31,  29 }, {  31,  19 }, {  30,  11 }, {  30,   1 }, {  45,   0 }, {  45,   8 }, {  46,  17 }, {  46,  27 },
    {  60,  27 }, {  60,  18 }, {  60,   9 }, {  60,   0 }, {  74,   2 }, {  74,  11 }, {  75,  20 }, {  74,  28 },
    {  89,  30 }, {  89,  19 }, {  89,   7 }, {  70,  38 }, {  82,  41 }, {  93,  45 }, { 104,  50 }, {  74,  64 },
    { 149,  64 }, { 119,  50 }, { 130,  45 }, { 141,  41 }, { 153,  38 }, { 134,   7 }, { 134,  19 }, { 134,  30 },
    { 149,  28 }, { 148,  20 }, { 149,  11 }, { 149,   2 }, { 163,   0 }, { 163,   9 }, { 163,  18 }, { 163,  27 },
    { 177,  27 }, { 177,  17 }, { 178,   8 }, { 178,   0 }, { 193,   1 }, { 193,  11 }, { 192,  19 }, { 192,  29 },
    { 206,  34 }, { 207,  25 }, { 208,  16 }, { 209,   5 }, { 224,   6 }, { 223,  17 }, { 223,  26 }, { 220,  35 }
}, {
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4
} };


static struct {
  uint8_t b;
  uint8_t g;
  uint8_t r;
} __attribute__((packed)) led_state[64];

static void set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
  led_state[index].r = r;
  led_state[index].g = g;
  led_state[index].b = b;
}

static void set_color_all(uint8_t r, uint8_t g, uint8_t b) {
  for (int i=0; i<RGB_MATRIX_LED_COUNT; i++)
    set_color(i, r, g, b);
}

static void init(void) {
  // Enable high current pathway to LEDs - this does violate the USB spec though! (1.6 amps...)
  DDRE |= _BV(6);
  PORTE &= ~_BV(6);

  // Overcurrent check input
  DDRB &= ~_BV(4);
  PORTB &= ~_BV(4);
}

static void flush(void) {
  uint8_t *bank_data = (uint8_t*)&led_state[0];
  uint8_t command[1 + 8*3];
  for (int hand=0; hand<2; hand++) {
    int addr = I2C_ADDR(hand);

    for (int bank=0; bank<4; bank++) {
      command[0] = TWI_CMD_LED_BASE + bank;
      memcpy(&command[1], bank_data, 8*3);
      i2c_transmit(addr, command, sizeof(command), I2C_TIMEOUT);
      _delay_us(100);

      bank_data += 8*3;
    }
  }
}

const rgb_matrix_driver_t rgb_matrix_driver = {
  .init = init,
  .flush = flush,
  .set_color = set_color,
  .set_color_all = set_color_all
};

#endif

/* vim: set ts=2 sw=2 et: */
