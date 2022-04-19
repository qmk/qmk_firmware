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
#include "pimoroni_trackball.h"
#include "i2c_master.h"
#include "print.h"
#include "debug.h"
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

static uint16_t precision = 128;

uint16_t pimoroni_trackball_get_cpi(void) {
    return (precision * 125);
}
/**
 * @brief Sets the scaling value for pimoroni trackball
 *
 * Sets a scaling value for pimoroni trackball to allow runtime adjustment. This isn't used by the sensor and is an
 * approximation so the functions are consistent across drivers.
 *
 * NOTE: This rounds down to the nearest number divisable by 125 that's a positive integer, values below 125 are clamped to 125.
 *
 * @param cpi uint16_t
 */
void pimoroni_trackball_set_cpi(uint16_t cpi) {
    if (cpi < 249) {
        precision = 1;
    } else {
        precision = (cpi - (cpi % 125)) / 125;
    }
}

void pimoroni_trackball_set_rgbw(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    uint8_t                              data[4] = {r, g, b, w};
    __attribute__((unused)) i2c_status_t status  = i2c_writeReg(PIMORONI_TRACKBALL_ADDRESS << 1, PIMORONI_TRACKBALL_REG_LED_RED, data, sizeof(data), PIMORONI_TRACKBALL_TIMEOUT);

#ifdef CONSOLE_ENABLE
    if (debug_mouse) dprintf("Trackball RGBW i2c_status_t: %d\n", status);
#endif
}

i2c_status_t read_pimoroni_trackball(pimoroni_data_t* data) {
    i2c_status_t status = i2c_readReg(PIMORONI_TRACKBALL_ADDRESS << 1, PIMORONI_TRACKBALL_REG_LEFT, (uint8_t*)data, sizeof(*data), PIMORONI_TRACKBALL_TIMEOUT);
#ifdef CONSOLE_ENABLE
    if (debug_mouse) {
        static uint16_t d_timer;
        if (timer_elapsed(d_timer) > PIMORONI_TRACKBALL_DEBUG_INTERVAL) {
            dprintf("Trackball READ i2c_status_t: %d L: %d R: %d Up: %d D: %d SW: %d\n", status, data->left, data->right, data->up, data->down, data->click);
            d_timer = timer_read();
        }
    }
#endif

    return status;
}

__attribute__((weak)) void pimoroni_trackball_device_init(void) {
    i2c_init();
    pimoroni_trackball_set_rgbw(0x00, 0x00, 0x00, 0x00);
}

int16_t pimoroni_trackball_get_offsets(uint8_t negative_dir, uint8_t positive_dir, uint8_t scale) {
    uint8_t offset     = 0;
    bool    isnegative = false;
    if (negative_dir > positive_dir) {
        offset     = negative_dir - positive_dir;
        isnegative = true;
    } else {
        offset = positive_dir - negative_dir;
    }
    uint16_t magnitude = (scale * offset * offset * precision) >> 7;
    return isnegative ? -(int16_t)(magnitude) : (int16_t)(magnitude);
}

void pimoroni_trackball_adapt_values(int8_t* mouse, int16_t* offset) {
    if (*offset > 127) {
        *mouse = 127;
        *offset -= 127;
    } else if (*offset < -127) {
        *mouse = -127;
        *offset += 127;
    } else {
        *mouse  = *offset;
        *offset = 0;
    }
}
