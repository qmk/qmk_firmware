// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "progmem.h"
#include "util.h"

#define IS31FL3236_REG_SHUTDOWN 0x00
#define IS31FL3236_REG_PWM 0x01
#define IS31FL3236_REG_UPDATE 0x25
#define IS31FL3236_REG_LED_CONTROL 0x26
#define IS31FL3236_REG_GLOBAL_CONTROL 0x4A
#define IS31FL3236_REG_PWM_FREQUENCY 0x4B
#define IS31FL3236_REG_RESET 0x4F

#define IS31FL3236_I2C_ADDRESS_GND 0x3C
#define IS31FL3236_I2C_ADDRESS_SCL 0x3D
#define IS31FL3236_I2C_ADDRESS_SDA 0x3E
#define IS31FL3236_I2C_ADDRESS_VCC 0x3F

#if defined(RGB_MATRIX_IS31FL3236)
#    define IS31FL3236_LED_COUNT RGB_MATRIX_LED_COUNT
#endif

#if defined(IS31FL3236_I2C_ADDRESS_4)
#    define IS31FL3236_DRIVER_COUNT 4
#elif defined(IS31FL3236_I2C_ADDRESS_3)
#    define IS31FL3236_DRIVER_COUNT 3
#elif defined(IS31FL3236_I2C_ADDRESS_2)
#    define IS31FL3236_DRIVER_COUNT 2
#elif defined(IS31FL3236_I2C_ADDRESS_1)
#    define IS31FL3236_DRIVER_COUNT 1
#endif

typedef struct is31fl3236_led_t {
    uint8_t driver : 2;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} PACKED is31fl3236_led_t;

extern const is31fl3236_led_t PROGMEM g_is31fl3236_leds[IS31FL3236_LED_COUNT];

void is31fl3236_init_drivers(void);

void is31fl3236_init(uint8_t index);

void is31fl3236_write_register(uint8_t index, uint8_t reg, uint8_t data);

void is31fl3236_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);

void is31fl3236_set_color_all(uint8_t red, uint8_t green, uint8_t blue);

void is31fl3236_set_led_control_register(uint8_t index, bool red, bool green, bool blue);

void is31fl3236_update_pwm_buffers(uint8_t index);

void is31fl3236_update_led_control_registers(uint8_t index);

void is31fl3236_flush(void);

#define IS31FL3236_PWM_FREQUENCY_3K_HZ 0b0
#define IS31FL3236_PWM_FREQUENCY_22K_HZ 0b1

#define OUT1 0x00
#define OUT2 0x01
#define OUT3 0x02
#define OUT4 0x03
#define OUT5 0x04
#define OUT6 0x05
#define OUT7 0x06
#define OUT8 0x07
#define OUT9 0x08
#define OUT10 0x09
#define OUT11 0x0A
#define OUT12 0x0B
#define OUT13 0x0C
#define OUT14 0x0D
#define OUT15 0x0E
#define OUT16 0x0F
#define OUT17 0x10
#define OUT18 0x11
#define OUT19 0x12
#define OUT20 0x13
#define OUT21 0x14
#define OUT22 0x15
#define OUT23 0x16
#define OUT24 0x17
#define OUT25 0x18
#define OUT26 0x19
#define OUT27 0x1A
#define OUT28 0x1B
#define OUT29 0x1C
#define OUT30 0x1D
#define OUT31 0x1E
#define OUT32 0x1F
#define OUT33 0x20
#define OUT34 0x21
#define OUT35 0x22
#define OUT36 0x23
