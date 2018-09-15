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
#include "model01.h"

#define I2C_TIMEOUT     1000

#define LINCOR(i) pgm_read_byte(&CIE1931_CURVE[i])

int set_all_leds_to_raw(uint8_t r, uint8_t g, uint8_t b) {
  uint8_t buf[] = {
    TWI_CMD_LED_SET_ALL_TO,
    b, g, r
  };
  int ret = 0;
  ret |= i2c_transmit(I2C_ADDR(LEFT), buf, sizeof(buf), I2C_TIMEOUT);
  ret |= i2c_transmit(I2C_ADDR(RIGHT), buf, sizeof(buf), I2C_TIMEOUT);
  _delay_us(10);
  return ret;
}

int set_all_leds_to(uint8_t r, uint8_t g, uint8_t b) {
  return set_all_leds_to_raw(LINCOR(r), LINCOR(g), LINCOR(b));
}

int set_led_to_raw(uint8_t led, uint8_t r, uint8_t g, uint8_t b) {
  uint8_t buf[] = {
    TWI_CMD_LED_SET_ONE_TO,
    led & 0x1f,
    b, g, r
  };
  int hand = (led >= 32) ? RIGHT : LEFT;
  int ret = i2c_transmit(I2C_ADDR(hand), buf, sizeof(buf), I2C_TIMEOUT);
  _delay_us(10);
  return ret;
}

int set_led_to(uint8_t led, uint8_t r, uint8_t g, uint8_t b) {
  return set_led_to_raw(led, LINCOR(r), LINCOR(g), LINCOR(b));
}

/* vim: set ts=2 sw=2 et: */
