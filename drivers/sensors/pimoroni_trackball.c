/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2021 Dasky (@daskygit)
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

#include "pointing_device_internal.h"
#include "pimoroni_trackball.h"
#include "timer.h"

// clang-format off
#define PIMORONI_TRACKBALL_REG_LED_RED 0x00
#define PIMORONI_TRACKBALL_REG_LED_GRN 0x01
#define PIMORONI_TRACKBALL_REG_LED_BLU 0x02
#define PIMORONI_TRACKBALL_REG_LED_WHT 0x03
#define PIMORONI_TRACKBALL_REG_LEFT    0x04
#define PIMORONI_TRACKBALL_REG_RIGHT   0x05
#define PIMORONI_TRACKBALL_REG_UP      0x06
#define PIMORONI_TRACKBALL_REG_DOWN    0x07
// clang-format on

static uint8_t      max_speed        = 10;
static i2c_status_t last_read_status = I2C_STATUS_SUCCESS;

uint8_t pimoroni_trackball_get_max_speed(void) {
    return max_speed;
}

uint16_t pimoroni_trackball_get_cpi(void) {
    return (max_speed * 320);
}
/**
 * @brief Sets the scaling value for pimoroni trackball
 *
 * Sets a scaling value for pimoroni trackball to allow runtime adjustment. This isn't used by the sensor and is an
 * approximation so the functions are consistent across drivers.
 *
 * NOTE: This clamps cpi to between 320 and 32000. Default 3200.
 *
 * @param cpi uint16_t
 */
void pimoroni_trackball_set_cpi(uint16_t cpi) {
    if (cpi < 320) {
        max_speed = 1;
    } else if (cpi > 32000) {
        max_speed = 100;
    } else {
        max_speed = (cpi - (cpi % 320)) / 320;
    }
}

void pimoroni_trackball_set_rgbw(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    uint8_t data[4] = {r, g, b, w};
    if (last_read_status == I2C_STATUS_SUCCESS) {
        __attribute__((unused)) i2c_status_t status = i2c_writeReg(PIMORONI_TRACKBALL_ADDRESS << 1, PIMORONI_TRACKBALL_REG_LED_RED, data, sizeof(data), PIMORONI_TRACKBALL_TIMEOUT);
        pd_dprintf("Trackball RGBW i2c_status_t: %d\n", status);
    } else {
        pd_dprintf("Trackball RGBW last read not successful.");
    }
}

i2c_status_t pimoroni_trackball_read(pimoroni_data_t* data) {
    last_read_status = i2c_readReg(PIMORONI_TRACKBALL_ADDRESS << 1, PIMORONI_TRACKBALL_REG_LEFT, (uint8_t*)data, sizeof(*data), PIMORONI_TRACKBALL_TIMEOUT);

#ifdef POINTING_DEVICE_DEBUG
    static uint16_t d_timer;
    if (timer_elapsed(d_timer) > PIMORONI_TRACKBALL_DEBUG_INTERVAL) {
        pd_dprintf("Trackball READ i2c_status_t: %d L: %d R: %d Up: %d D: %d SW: %d\n", last_read_status, data->left, data->right, data->up, data->down, data->click);
        d_timer = timer_read();
    }
#endif

    return last_read_status;
}

__attribute__((weak)) void pimoroni_trackball_device_init(void) {
    i2c_init();
    pimoroni_trackball_set_rgbw(0x00, 0x00, 0x00, 0xff);
}