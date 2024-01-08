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

#include "is31fl3218.h"
#include <string.h>
#include "i2c_master.h"

#define IS31FL3218_PWM_REGISTER_COUNT 18
#define IS31FL3218_LED_CONTROL_REGISTER_COUNT 3

#ifndef IS31FL3218_I2C_TIMEOUT
#    define IS31FL3218_I2C_TIMEOUT 100
#endif

#ifndef IS31FL3218_I2C_PERSISTENCE
#    define IS31FL3218_I2C_PERSISTENCE 0
#endif

uint8_t i2c_transfer_buffer[20];

// IS31FL3218 has 18 PWM outputs and a fixed I2C address, so no chaining.
uint8_t g_pwm_buffer[IS31FL3218_PWM_REGISTER_COUNT];
bool    g_pwm_buffer_update_required = false;

uint8_t g_led_control_registers[IS31FL3218_LED_CONTROL_REGISTER_COUNT] = {0};
bool    g_led_control_registers_update_required                        = false;

void is31fl3218_write_register(uint8_t reg, uint8_t data) {
    i2c_transfer_buffer[0] = reg;
    i2c_transfer_buffer[1] = data;
#if IS31FL3218_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3218_I2C_PERSISTENCE; i++) {
        if (i2c_transmit(IS31FL3218_I2C_ADDRESS << 1, i2c_transfer_buffer, 2, IS31FL3218_I2C_TIMEOUT) == 0) break;
    }
#else
    i2c_transmit(IS31FL3218_I2C_ADDRESS << 1, i2c_transfer_buffer, 2, IS31FL3218_I2C_TIMEOUT);
#endif
}

void is31fl3218_write_pwm_buffer(uint8_t *pwm_buffer) {
    i2c_transfer_buffer[0] = IS31FL3218_REG_PWM;
    memcpy(i2c_transfer_buffer + 1, pwm_buffer, 18);

#if IS31FL3218_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3218_I2C_PERSISTENCE; i++) {
        i2c_transmit(IS31FL3218_I2C_ADDRESS << 1, i2c_transfer_buffer, 19, IS31FL3218_I2C_TIMEOUT);
    }
#else
    i2c_transmit(IS31FL3218_I2C_ADDRESS << 1, i2c_transfer_buffer, 19, IS31FL3218_I2C_TIMEOUT);
#endif
}

void is31fl3218_init(void) {
    i2c_init();

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
        is31fl3218_set_led_control_register(i, true, true, true);
    }

    is31fl3218_update_led_control_registers();
}

void is31fl3218_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    is31fl3218_led_t led;

    if (index >= 0 && index < IS31FL3218_LED_COUNT) {
        memcpy_P(&led, (&g_is31fl3218_leds[index]), sizeof(led));

        if (g_pwm_buffer[led.r - IS31FL3218_REG_PWM] == red && g_pwm_buffer[led.g - IS31FL3218_REG_PWM] == green && g_pwm_buffer[led.b - IS31FL3218_REG_PWM] == blue) {
            return;
        }

        g_pwm_buffer[led.r - IS31FL3218_REG_PWM] = red;
        g_pwm_buffer[led.g - IS31FL3218_REG_PWM] = green;
        g_pwm_buffer[led.b - IS31FL3218_REG_PWM] = blue;
        g_pwm_buffer_update_required             = true;
    }
}

void is31fl3218_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < IS31FL3218_LED_COUNT; i++) {
        is31fl3218_set_color(i, red, green, blue);
    }
}

void is31fl3218_set_led_control_register(uint8_t index, bool red, bool green, bool blue) {
    is31fl3218_led_t led;
    memcpy_P(&led, (&g_is31fl3218_leds[index]), sizeof(led));

    uint8_t control_register_r = (led.r - IS31FL3218_REG_PWM) / 6;
    uint8_t control_register_g = (led.g - IS31FL3218_REG_PWM) / 6;
    uint8_t control_register_b = (led.b - IS31FL3218_REG_PWM) / 6;
    uint8_t bit_r              = (led.r - IS31FL3218_REG_PWM) % 6;
    uint8_t bit_g              = (led.g - IS31FL3218_REG_PWM) % 6;
    uint8_t bit_b              = (led.b - IS31FL3218_REG_PWM) % 6;

    if (red) {
        g_led_control_registers[control_register_r] |= (1 << bit_r);
    } else {
        g_led_control_registers[control_register_r] &= ~(1 << bit_r);
    }
    if (green) {
        g_led_control_registers[control_register_g] |= (1 << bit_g);
    } else {
        g_led_control_registers[control_register_g] &= ~(1 << bit_g);
    }
    if (blue) {
        g_led_control_registers[control_register_b] |= (1 << bit_b);
    } else {
        g_led_control_registers[control_register_b] &= ~(1 << bit_b);
    }

    g_led_control_registers_update_required = true;
}

void is31fl3218_update_pwm_buffers(void) {
    if (g_pwm_buffer_update_required) {
        is31fl3218_write_pwm_buffer(g_pwm_buffer);
        // Load PWM registers and LED Control register data
        is31fl3218_write_register(IS31FL3218_REG_UPDATE, 0x01);

        g_pwm_buffer_update_required = false;
    }
}

void is31fl3218_update_led_control_registers(void) {
    if (g_led_control_registers_update_required) {
        for (int i = 0; i < IS31FL3218_LED_CONTROL_REGISTER_COUNT; i++) {
            is31fl3218_write_register(IS31FL3218_REG_LED_CONTROL_1 + i, g_led_control_registers[i]);
        }

        g_led_control_registers_update_required = false;
    }
}
