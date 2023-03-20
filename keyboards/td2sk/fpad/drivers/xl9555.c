// Copyright 2023 td2sk (@td2sk)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "xl9555.h"

#include "i2c_master.h"

#define XL9555_I2C_ADDR 0b01000000

#define XL9555_TIMEOUT 100

#define XL9555_COMMAND_INPUT 0x00
#define XL9555_COMMAND_OUTPUT 0x02
#define XL9555_COMMAND_POLARITY 0x04
#define XL9555_COMMAND_CONFIGURATION 0x06

static uint8_t g_trans_buf[2];

void XL9555_set_polarity(uint8_t port0, uint8_t port1) {
    g_trans_buf[0] = port0;
    g_trans_buf[1] = port1;
    i2c_writeReg(XL9555_I2C_ADDR, XL9555_COMMAND_POLARITY, g_trans_buf, 2, XL9555_TIMEOUT);
}

uint16_t XL9555_read(void) {
    i2c_readReg(XL9555_I2C_ADDR, XL9555_COMMAND_INPUT, g_trans_buf, 2, XL9555_TIMEOUT);
    return (((uint16_t)g_trans_buf[1]) << 8) | g_trans_buf[0];
}
