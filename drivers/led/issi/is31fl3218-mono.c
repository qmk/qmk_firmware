/* Copyright 2018 Jason Williams (Wilba)
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

#include "is31fl3218-mono.h"
#include "i2c_master.h"
#include "gpio.h"

#define IS31FL3218_PWM_REGISTER_COUNT 18
#define IS31FL3218_LED_CONTROL_REGISTER_COUNT 3

#ifndef IS31FL3218_I2C_TIMEOUT
#    define IS31FL3218_I2C_TIMEOUT 100
#endif

#ifndef IS31FL3218_I2C_PERSISTENCE
#    define IS31FL3218_I2C_PERSISTENCE 0
#endif

typedef struct is31fl3218_driver_t {
    uint8_t pwm_buffer[IS31FL3218_PWM_REGISTER_COUNT];
    bool    pwm_buffer_dirty;
    uint8_t led_control_buffer[IS31FL3218_LED_CONTROL_REGISTER_COUNT];
    bool    led_control_buffer_dirty;
} PACKED is31fl3218_driver_t;

// IS31FL3218 has 18 PWM outputs and a fixed I2C address, so no chaining.
is31fl3218_driver_t driver_buffers = {
    .pwm_buffer               = {0},
    .pwm_buffer_dirty         = false,
    .led_control_buffer       = {0},
    .led_control_buffer_dirty = false,
};

void is31fl3218_write_register(uint8_t reg, uint8_t data) {
#if IS31FL3218_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3218_I2C_PERSISTENCE; i++) {
        if (i2c_write_register(IS31FL3218_I2C_ADDRESS << 1, reg, &data, 1, IS31FL3218_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
    }
#else
    i2c_write_register(IS31FL3218_I2C_ADDRESS << 1, reg, &data, 1, IS31FL3218_I2C_TIMEOUT);
#endif
}

void is31fl3218_write_pwm_buffer(void) {
#if IS31FL3218_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3218_I2C_PERSISTENCE; i++) {
        if (i2c_write_register(IS31FL3218_I2C_ADDRESS << 1, IS31FL3218_REG_PWM, driver_buffers.pwm_buffer, 18, IS31FL3218_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
    }
#else
    i2c_write_register(IS31FL3218_I2C_ADDRESS << 1, IS31FL3218_REG_PWM, driver_buffers.pwm_buffer, 18, IS31FL3218_I2C_TIMEOUT);
#endif
}

void is31fl3218_init(void) {
    i2c_init();

#if defined(IS31FL3218_SDB_PIN)
    setPinOutput(IS31FL3218_SDB_PIN);
    writePinHigh(IS31FL3218_SDB_PIN);
#endif

    // In case we ever want to reinitialize (?)
    is31fl3218_write_register(IS31FL3218_REG_RESET, 0x00);

    // Turn off software shutdown
    is31fl3218_write_register(IS31FL3218_REG_SHUTDOWN, 0x01);

    // Set all PWM values to zero
    for (uint8_t i = 0; i < IS31FL3218_PWM_REGISTER_COUNT; i++) {
        is31fl3218_write_register(IS31FL3218_REG_PWM + i, 0x00);
    }

    // turn off all LEDs in the LED control register
    for (uint8_t i = 0; i < IS31FL3218_LED_CONTROL_REGISTER_COUNT; i++) {
        is31fl3218_write_register(IS31FL3218_REG_LED_CONTROL_1 + i, 0x00);
    }

    // Load PWM registers and LED Control register data
    is31fl3218_write_register(IS31FL3218_REG_UPDATE, 0x01);

    for (int i = 0; i < IS31FL3218_LED_COUNT; i++) {
        is31fl3218_set_led_control_register(i, true);
    }

    is31fl3218_update_led_control_registers();
}

void is31fl3218_set_value(int index, uint8_t value) {
    is31fl3218_led_t led;

    if (index >= 0 && index < IS31FL3218_LED_COUNT) {
        memcpy_P(&led, (&g_is31fl3218_leds[index]), sizeof(led));

        if (driver_buffers.pwm_buffer[led.v] == value) {
            return;
        }

        driver_buffers.pwm_buffer[led.v] = value;
        driver_buffers.pwm_buffer_dirty  = true;
    }
}

void is31fl3218_set_value_all(uint8_t value) {
    for (int i = 0; i < IS31FL3218_LED_COUNT; i++) {
        is31fl3218_set_value(i, value);
    }
}

void is31fl3218_set_led_control_register(uint8_t index, bool value) {
    is31fl3218_led_t led;
    memcpy_P(&led, (&g_is31fl3218_leds[index]), sizeof(led));

    uint8_t control_register = led.v / 6;
    uint8_t bit_value        = led.v % 6;

    if (value) {
        driver_buffers.led_control_buffer[control_register] |= (1 << bit_value);
    } else {
        driver_buffers.led_control_buffer[control_register] &= ~(1 << bit_value);
    }

    driver_buffers.led_control_buffer_dirty = true;
}

void is31fl3218_update_pwm_buffers(void) {
    if (driver_buffers.pwm_buffer_dirty) {
        is31fl3218_write_pwm_buffer();
        // Load PWM registers and LED Control register data
        is31fl3218_write_register(IS31FL3218_REG_UPDATE, 0x01);

        driver_buffers.pwm_buffer_dirty = false;
    }
}

void is31fl3218_update_led_control_registers(void) {
    if (driver_buffers.led_control_buffer_dirty) {
        for (uint8_t i = 0; i < IS31FL3218_LED_CONTROL_REGISTER_COUNT; i++) {
            is31fl3218_write_register(IS31FL3218_REG_LED_CONTROL_1 + i, driver_buffers.led_control_buffer[i]);
        }

        driver_buffers.led_control_buffer_dirty = false;
    }
}
