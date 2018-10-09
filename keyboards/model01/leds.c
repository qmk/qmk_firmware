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
#include <quantum.h>
#include <i2c_master.h>
#include <led_tables.h>
#include <rgb_matrix.h>
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
const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
  {{0x73}, {  3, 35}, 0},
  {{0x72}, {  0, 26}, 0},
  {{0x71}, {  0, 17}, 0},
  {{0x70}, {  0,  6}, 0},
  {{0x60}, { 14,  5}, 0},
  {{0x61}, { 15, 16}, 0},
  {{0x62}, { 16, 25}, 0},
  {{0x63}, { 17, 34}, 0},
  {{0x53}, { 31, 29}, 0},
  {{0x52}, { 31, 19}, 0},
  {{0x51}, { 30, 11}, 0},
  {{0x50}, { 30,  1}, 0},
  {{0x40}, { 45,  0}, 0},
  {{0x41}, { 45,  8}, 0},
  {{0x42}, { 46, 17}, 0},
  {{0x43}, { 46, 27}, 0},
  {{0x33}, { 60, 27}, 0},
  {{0x32}, { 60, 18}, 0},
  {{0x31}, { 60,  9}, 0},
  {{0x30}, { 60,  0}, 0},
  {{0x20}, { 74,  2}, 0},
  {{0x21}, { 74, 11}, 0},
  {{0x22}, { 75, 20}, 0},
  {{0x23}, { 74, 28}, 0},
  {{0x12}, { 89, 30}, 0},
  {{0x11}, { 89, 19}, 0},
  {{0x10}, { 89,  7}, 0},
  {{0x00}, { 70, 38}, 1},
  {{0x01}, { 82, 41}, 1},
  {{0x02}, { 93, 45}, 1},
  {{0x03}, {104, 50}, 1},
  {{0x13}, { 74, 64}, 1},
  {{0x67}, {149, 64}, 1},
  {{0x77}, {119, 50}, 1},
  {{0x76}, {130, 45}, 1},
  {{0x75}, {141, 41}, 1},
  {{0x74}, {153, 38}, 1},
  {{0x64}, {134,  7}, 0},
  {{0x65}, {134, 19}, 0},
  {{0x66}, {134, 30}, 0},
  {{0x57}, {149, 28}, 0},
  {{0x56}, {148, 20}, 0},
  {{0x55}, {149, 11}, 0},
  {{0x54}, {149,  2}, 0},
  {{0x44}, {163,  0}, 0},
  {{0x45}, {163,  9}, 0},
  {{0x46}, {163, 18}, 0},
  {{0x47}, {163, 27}, 0},
  {{0x37}, {177, 27}, 0},
  {{0x36}, {177, 17}, 0},
  {{0x35}, {178,  8}, 0},
  {{0x34}, {178,  0}, 0},
  {{0x24}, {193,  1}, 0},
  {{0x25}, {193, 11}, 0},
  {{0x26}, {192, 19}, 0},
  {{0x27}, {192, 29}, 0},
  {{0x17}, {206, 34}, 0},
  {{0x16}, {207, 25}, 0},
  {{0x15}, {208, 16}, 0},
  {{0x14}, {209,  5}, 0},
  {{0x04}, {224,  6}, 0},
  {{0x05}, {223, 17}, 0},
  {{0x06}, {223, 26}, 0},
  {{0x07}, {220, 35}, 0},
};

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
  for (int i=0; i<DRIVER_LED_TOTAL; i++)
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
