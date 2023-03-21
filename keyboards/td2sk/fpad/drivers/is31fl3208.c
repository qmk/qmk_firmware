// Copyright 2023 td2sk (@td2sk)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "drivers/is31fl3208.h"

#include <string.h>

#include "i2c_master.h"
#include "gpio.h"

#define IS31FL3208_I2C_ADDR 0b11011000

#define ISSI_REG_SHUTDOWN 0x00
#define ISSI_REG_PWM 0x01
#define ISSI_REG_UPDATE 0x13
#define ISSI_REG_LED_CONTROL 0x14
#define ISSI_REG_GLOBAL_CONTROL 0x26
#define ISSI_REG_FREQUENCY 0x27
#define ISSI_REG_RESET 0x2F

#define ISSI_TIMEOUT 100

#define MAX_LEDS 18

static uint8_t g_trans_buf[20];

enum IS31FL3208_SHUTDOWN_REGISTER {
    IS31FL3208_SHUTDOWN_REGISTER_SOFTWARE_SHUTDOWN = 0,
    IS31FL3208_SHUTDOWN_REGISTER_NORMAL_OPERATION  = 1,
};

enum IS31FL3208_CURRENT_CONTROL {
    IS31FL3208_CURRENT_CONTROL_MAX            = 0x10,
    IS31FL3208_CURRENT_CONTROL_ELEVEN_TWELFTH = 0x11,
    IS31FL3208_CURRENT_CONTROL_NINE_TWELFTH   = 0x12,
    IS31FL3208_CURRENT_CONTROL_SEVEN_TWELFTH  = 0x13,
    IS31FL3208_CURRENT_CONTROL_ZERO           = 0x00,
};

enum IS31FL3208_GLOBAL_CONTROL {
    IS31FL3208_GLOBAL_CONTROL_NORMAL_OPERATION = 0,
    IS31FL3208_GLOBAL_CONTROL_SHUTDOWN         = 1,
};

static void IS31FL3208_write_register(uint8_t reg, uint8_t data) {
    g_trans_buf[0] = reg;
    g_trans_buf[1] = data;
    i2c_transmit(IS31FL3208_I2C_ADDR, g_trans_buf, 2, ISSI_TIMEOUT);
}

static void IS31FL3208_reset(void) {
    IS31FL3208_write_register(ISSI_REG_RESET, 0x00);
}

static void IS31FL3208_set_current_all(enum IS31FL3208_CURRENT_CONTROL current) {
    memset(g_trans_buf, current, MAX_LEDS);
    i2c_writeReg(IS31FL3208_I2C_ADDR, ISSI_REG_LED_CONTROL, g_trans_buf, MAX_LEDS, ISSI_TIMEOUT);
}

static void IS31FL3208_pwm_off(void) {
    memset(g_trans_buf, 0x00, MAX_LEDS);
    i2c_writeReg(IS31FL3208_I2C_ADDR, ISSI_REG_PWM, g_trans_buf, MAX_LEDS, ISSI_TIMEOUT);
}

void IS31FL3208_init(void) {
    IS31FL3208_reset();
    IS31FL3208_set_current_all(IS31FL3208_CURRENT_CONTROL_SEVEN_TWELFTH);
    IS31FL3208_write_register(ISSI_REG_GLOBAL_CONTROL, IS31FL3208_GLOBAL_CONTROL_NORMAL_OPERATION);
    IS31FL3208_pwm_off();

    IS31FL3208_update();

    IS31FL3208_write_register(ISSI_REG_SHUTDOWN, IS31FL3208_SHUTDOWN_REGISTER_NORMAL_OPERATION);

#ifdef CUSTOM_IS31FL3208_ENABLE_PIN
    setPinOutput(CUSTOM_IS31FL3208_ENABLE_PIN);
    writePinHigh(CUSTOM_IS31FL3208_ENABLE_PIN);
#endif
}

static const uint8_t lut_order[5][3] = {{2, 1, 0}, {2, 1, 0}, {2, 1, 0}, {2, 1, 0}, {0, 1, 2}};

static const uint8_t lut_port[] = {3, 2, 1, 0, 4};

void IS31FL3208_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    g_trans_buf[lut_order[index][0]] = red;
    g_trans_buf[lut_order[index][1]] = green;
    g_trans_buf[lut_order[index][2]] = blue;
    i2c_writeReg(IS31FL3208_I2C_ADDR, ISSI_REG_PWM + 3 * lut_port[index], g_trans_buf, 3, ISSI_TIMEOUT);
}

void IS31FL3208_update(void) {
    IS31FL3208_write_register(ISSI_REG_UPDATE, 0x00);
}
