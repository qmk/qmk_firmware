/* Copyright 2021 Jay Greco
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
#pragma once

#include <quantum.h>
#include <stdint.h>
#include <i2c_master.h>
#include <progmem.h>

#define I2C_TIMEOUT 100

#define OSC_ENABLED             0x01
#define OSC_DISABLED            0x00

#define HT16K33_DISP_ON         0x01
#define HT16K33_DISP_OFF        0x01

#define HT16K33_BLINK_OFF       0x00
#define HT16K33_BLINK_ON        0x01
#define HT16K33_BLINK_2HZ       0x01
#define HT16K33_BLINK_1HZ       0x02
#define HT16K33_BLINK_HALFHZ    0x03

#define HT16K33_CMD_DISP        0x00
#define HT16K33_CMD_ENABLE      0x20
#define HT16K33_CMD_BLINK       0x80
#define HT16K33_CMD_BRIGHTNESS  0xE0

#define HT16K33_BRIGHTNESS_MIN  0x00
#define HT16K33_BRIGHTNESS_MAX  0x0F

void ht16K33_init(uint8_t addr),
  ht16K33_setBlinkMode(uint8_t addr, uint8_t mode),
  ht16K33_setBrightness(uint8_t addr, uint8_t brightness),
  ht16K33_refresh(uint8_t addr, uint16_t *displayBuffer, uint8_t bufLen);

#if defined(__AVR__)
static i2c_status_t i2c_transmit_P(uint8_t address, const uint8_t *data, uint16_t length, uint16_t timeout) {
    i2c_status_t status = i2c_start(address | I2C_WRITE, timeout);

    for (uint16_t i = 0; i < length && status >= 0; i++) {
        status = i2c_write(pgm_read_byte((const char *)data++), timeout);
        if (status) break;
    }

    i2c_stop();

    return status;
}
#endif

void ht16K33_init(uint8_t addr) {
    i2c_init();
    static const uint8_t PROGMEM data[] = {HT16K33_CMD_ENABLE | OSC_ENABLED};
    i2c_transmit_P((addr << 1), &data[0], sizeof(data), I2C_TIMEOUT);
    ht16K33_setBrightness(addr, HT16K33_BRIGHTNESS_MIN);
    ht16K33_setBlinkMode(addr, HT16K33_BLINK_OFF);
}

void ht16K33_setBlinkMode(uint8_t addr, uint8_t mode) {
    if ((mode < HT16K33_BLINK_OFF)|(mode > HT16K33_BLINK_HALFHZ)) {
        mode = HT16K33_BLINK_OFF;
    }
    uint8_t data[] = {(HT16K33_CMD_BLINK | mode << 1 | HT16K33_DISP_ON)};
    i2c_transmit((addr << 1), &data[0], sizeof(data), I2C_TIMEOUT);
}

void ht16K33_setBrightness(uint8_t addr, uint8_t brightness) {
    uint8_t data[] = {(HT16K33_CMD_BRIGHTNESS | brightness)};
    i2c_transmit((addr << 1), &data[0], sizeof(data), I2C_TIMEOUT);
}

void ht16K33_refresh(uint8_t addr, uint16_t *displayBuffer, uint8_t bufLen) {
    i2c_start((addr << 1), I2C_TIMEOUT);
    i2c_write((uint8_t)HT16K33_CMD_DISP, I2C_TIMEOUT);
    for (int i = 0; i < bufLen; i++) {
        i2c_write((displayBuffer[i] & 0xFF), I2C_TIMEOUT);
        i2c_write((displayBuffer[i] >> 8), I2C_TIMEOUT);
    }
    i2c_stop();
}