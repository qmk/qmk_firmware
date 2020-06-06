/* Copyright 2020 sekigon-gonnoc
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

#include QMK_KEYBOARD_H
#include "report.h"
#include "mtch6102.h"
#include "i2c_master.h"

#ifndef MTCH6102_X_DIR
#    define MTCH6102_X_DIR -1
#endif

#ifndef MTCH6102_Y_DIR
#    define MTCH6102_Y_DIR 1
#endif

#ifndef I2C_TIMEOUT
#    define I2C_TIMEOUT 500
#endif

static uint8_t pointing_device_button = 0;
static bool    send_flag              = false;

void pointing_device_set_button(uint8_t btn) {
    pointing_device_button |= btn;
    send_flag = true;
}

void pointing_device_clear_button(uint8_t btn) {
    pointing_device_button &= ~btn;
    send_flag = true;
}

typedef union {
    struct {
        uint8_t status, x_msb, y_msb, xy_lsb, gesture;
    };
    uint8_t dat[5];
} mtch6102_reg_t;

uint16_t check_mtch6102() {
    uint8_t dat[2] = {0};

    if (i2c_readReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR), 0, dat, sizeof(dat),
                    I2C_TIMEOUT)) {
        return 0;
    }

    return ((uint16_t)dat[0] << 8) | dat[1];
}

int init_mtch6102(void) {
    uint8_t dat = 0b0011;
    uint8_t res = 0;
    res |= i2c_writeReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR), MTCH6102_REG_MODE,
                        &dat, 1, I2C_TIMEOUT);

    uint8_t default_config[] = {
        0x09, 0x06, 0x06, 0x37, 0x28, 0x85, 0x02, 0x4C, 0x06, 0x10, 0x04, 0x01,
        0x01, 0x0A, 0x00, 0x14, 0x14, 0x02, 0x01, 0x01, 0x05, 0x00, 0x00, 0x40,
        0x40, 0x19, 0x19, 0x40, 0x32, 0x00, 0x0C, 0x20, 0x04, 0x2D, 0x2D, 0x25,

    };
    res |=
        i2c_writeReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR), MTCH6102_REG_CFG_START,
                     default_config, sizeof(default_config), I2C_TIMEOUT);

    dat = 0x20;
    res |= i2c_writeReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR), MTCH6102_REG_CMD,
                        &dat, 1, I2C_TIMEOUT);

    return res;
}

bool read_mtch6102(mtch6102_data_t* const data) {
    mtch6102_reg_t reg;

    if (i2c_readReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR), MTCH6102_REG_STAT,
                    reg.dat, sizeof(mtch6102_reg_t), I2C_TIMEOUT)) {
        print("regread error\n");
        return false;
    }

    data->gesture = reg.gesture;
    data->status  = reg.status;
    data->x       = (reg.x_msb << 4) | (reg.xy_lsb >> 4);
    data->y       = (reg.y_msb << 4) | (reg.xy_lsb & 0xF);

    return true;
}

bool process_mtch6102(mtch6102_data_t const* const data,
                      report_mouse_t* const        rep_mouse) {
    static uint16_t x_buf, y_buf;
    static bool     touch_state;
    static bool     release_button = false;

    uint16_t x_dif, y_dif;

    if (touch_state && (data->status & TOUCH)) {
        x_dif        = data->x - x_buf;
        y_dif        = data->y - y_buf;
        rep_mouse->x = x_dif * MTCH6102_X_DIR;
        rep_mouse->y = y_dif * MTCH6102_Y_DIR;
        send_flag    = true;
    }

    if ((data->status & GESTURE) &&
        (data->gesture == GES_TAP || data->gesture == GES_DOUBLE_TAP)) {
        rep_mouse->buttons = 1;
        release_button     = true;
        send_flag          = true;
    } else if (release_button) {
        rep_mouse->buttons = 0;
        send_flag          = true;
    }

    if (pointing_device_button != 0) {
        rep_mouse->buttons = pointing_device_button;
    }

    touch_state = data->status & TOUCH;
    x_buf       = data->x;
    y_buf       = data->y;

    return send_flag;
}

int sleep_mtch6102(void) {
    uint8_t dat = 0b0000;
    return i2c_writeReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR), MTCH6102_REG_MODE,
                        &dat, 1, I2C_TIMEOUT);
}

void test_mtch6102(void) {
    uint8_t dat = 0x08;

    // start manufacturing test
    uint8_t res = i2c_writeReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR),
                               MTCH6102_REG_CMD, &dat, 1, I2C_TIMEOUT);

    if (res != 0) {
        xprintf("test command failed\n");
        return;
    }

    uint32_t retry = 100;
    do {
        i2c_readReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR),
                                MTCH6102_REG_CMD, &dat, 1, I2C_TIMEOUT);

        if ((dat & 0x08) == 0) {
            // manufacturing test end
            break;
        }
    } while(retry--);

    if (retry == 0) {
        xprintf("test timeout\n");
        return;
    }

    uint8_t mfg_test_res[6] = {0};
    i2c_readReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR), 0xD0,
                mfg_test_res, sizeof(mfg_test_res), I2C_TIMEOUT);

    xprintf("res:0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n", mfg_test_res[0],
            mfg_test_res[1], mfg_test_res[2], mfg_test_res[3], mfg_test_res[4],
            mfg_test_res[5]);
}

