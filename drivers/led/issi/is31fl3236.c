// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "is31fl3236.h"
#include "i2c_master.h"
#include "gpio.h"

#define IS31FL3236_PWM_REGISTER_COUNT 36
#define IS31FL3236_LED_CONTROL_REGISTER_COUNT 36

#ifndef IS31FL3236_I2C_TIMEOUT
#    define IS31FL3236_I2C_TIMEOUT 100
#endif

#ifndef IS31FL3236_I2C_PERSISTENCE
#    define IS31FL3236_I2C_PERSISTENCE 0
#endif

#ifndef IS31FL3236_PWM_FREQUENCY
#    define IS31FL3236_PWM_FREQUENCY IS31FL3236_PWM_FREQUENCY_3K_HZ // OFS - IS31FL3236A only
#endif

const uint8_t i2c_addresses[IS31FL3236_DRIVER_COUNT] = {
    IS31FL3236_I2C_ADDRESS_1,
#ifdef IS31FL3236_I2C_ADDRESS_2
    IS31FL3236_I2C_ADDRESS_2,
#    ifdef IS31FL3236_I2C_ADDRESS_3
    IS31FL3236_I2C_ADDRESS_3,
#        ifdef IS31FL3236_I2C_ADDRESS_4
    IS31FL3236_I2C_ADDRESS_4,
#        endif
#    endif
#endif
};

typedef struct is31fl3236_driver_t {
    uint8_t pwm_buffer[IS31FL3236_PWM_REGISTER_COUNT];
    bool    pwm_buffer_dirty;
    uint8_t led_control_buffer[IS31FL3236_LED_CONTROL_REGISTER_COUNT];
    bool    led_control_buffer_dirty;
} PACKED is31fl3236_driver_t;

is31fl3236_driver_t driver_buffers[IS31FL3236_DRIVER_COUNT] = {{
    .pwm_buffer               = {0},
    .pwm_buffer_dirty         = false,
    .led_control_buffer       = {0},
    .led_control_buffer_dirty = false,
}};

void is31fl3236_write_register(uint8_t index, uint8_t reg, uint8_t data) {
#if IS31FL3236_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3236_I2C_PERSISTENCE; i++) {
        if (i2c_write_register(i2c_addresses[index] << 1, reg, &data, 1, IS31FL3236_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
    }
#else
    i2c_write_register(i2c_addresses[index] << 1, reg, &data, 1, IS31FL3236_I2C_TIMEOUT);
#endif
}

void is31fl3236_write_pwm_buffer(uint8_t index) {
#if IS31FL3236_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3236_I2C_PERSISTENCE; i++) {
        if (i2c_write_register(i2c_addresses[index] << 1, IS31FL3236_REG_PWM, driver_buffers[index].pwm_buffer, 36, IS31FL3236_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
    }
#else
    i2c_write_register(i2c_addresses[index] << 1, IS31FL3236_REG_PWM, driver_buffers[index].pwm_buffer, 36, IS31FL3236_I2C_TIMEOUT);
#endif
}

void is31fl3236_init_drivers(void) {
    i2c_init();

#if defined(IS31FL3236_SDB_PIN)
    gpio_set_pin_output(IS31FL3236_SDB_PIN);
    gpio_write_pin_high(IS31FL3236_SDB_PIN);
#endif

    for (uint8_t i = 0; i < IS31FL3236_DRIVER_COUNT; i++) {
        is31fl3236_init(i);
    }

    for (uint8_t i = 0; i < IS31FL3236_LED_COUNT; i++) {
        is31fl3236_set_led_control_register(i, true, true, true);
    }

    for (uint8_t i = 0; i < IS31FL3236_DRIVER_COUNT; i++) {
        is31fl3236_update_led_control_registers(i);
    }
}

void is31fl3236_init(uint8_t index) {
    // In case we ever want to reinitialize (?)
    is31fl3236_write_register(index, IS31FL3236_REG_RESET, 0x00);

    // Turn off software shutdown
    is31fl3236_write_register(index, IS31FL3236_REG_SHUTDOWN, 0x01);

    // Set all PWM values to zero
    for (uint8_t i = 0; i < IS31FL3236_PWM_REGISTER_COUNT; i++) {
        is31fl3236_write_register(index, IS31FL3236_REG_PWM + i, 0x00);
    }

    // turn off all LEDs in the LED control register
    for (uint8_t i = 0; i < IS31FL3236_LED_CONTROL_REGISTER_COUNT; i++) {
        is31fl3236_write_register(index, IS31FL3236_REG_LED_CONTROL + i, 0x00);
    }

    // Set PWM frequency (IS31FL3236A)
    is31fl3236_write_register(index, IS31FL3236_REG_PWM_FREQUENCY, IS31FL3236_PWM_FREQUENCY);

    // Load PWM registers and LED Control register data
    is31fl3236_write_register(index, IS31FL3236_REG_UPDATE, 0x01);
}

void is31fl3236_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    is31fl3236_led_t led;

    if (index < IS31FL3236_LED_COUNT) {
        memcpy_P(&led, (&g_is31fl3236_leds[index]), sizeof(led));

        if (driver_buffers[led.driver].pwm_buffer[led.r] == red && driver_buffers[led.driver].pwm_buffer[led.g] == green && driver_buffers[led.driver].pwm_buffer[led.b] == blue) {
            return;
        }

        driver_buffers[led.driver].pwm_buffer[led.r] = red;
        driver_buffers[led.driver].pwm_buffer[led.g] = green;
        driver_buffers[led.driver].pwm_buffer[led.b] = blue;
        driver_buffers[led.driver].pwm_buffer_dirty  = true;
    }
}

void is31fl3236_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t i = 0; i < IS31FL3236_LED_COUNT; i++) {
        is31fl3236_set_color(i, red, green, blue);
    }
}

void is31fl3236_set_led_control_register(uint8_t index, bool red, bool green, bool blue) {
    is31fl3236_led_t led;
    memcpy_P(&led, (&g_is31fl3236_leds[index]), sizeof(led));

    driver_buffers[led.driver].led_control_buffer[led.r] = red ? 0x01 : 0x00;
    driver_buffers[led.driver].led_control_buffer[led.g] = green ? 0x01 : 0x00;
    driver_buffers[led.driver].led_control_buffer[led.b] = blue ? 0x01 : 0x00;
    driver_buffers[led.driver].led_control_buffer_dirty  = true;
}

void is31fl3236_update_pwm_buffers(uint8_t index) {
    if (driver_buffers[index].pwm_buffer_dirty) {
        is31fl3236_write_pwm_buffer(index);
        // Load PWM registers and LED Control register data
        is31fl3236_write_register(index, IS31FL3236_REG_UPDATE, 0x01);

        driver_buffers[index].pwm_buffer_dirty = false;
    }
}

void is31fl3236_update_led_control_registers(uint8_t index) {
    if (driver_buffers[index].led_control_buffer_dirty) {
        for (uint8_t i = 0; i < IS31FL3236_LED_CONTROL_REGISTER_COUNT; i++) {
            is31fl3236_write_register(index, IS31FL3236_REG_LED_CONTROL + i, driver_buffers[index].led_control_buffer[i]);
        }

        driver_buffers[index].led_control_buffer_dirty = false;
    }
}

void is31fl3236_flush(void) {
    for (uint8_t i = 0; i < IS31FL3236_DRIVER_COUNT; i++) {
        is31fl3236_update_pwm_buffers(i);
    }
}
