/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
 * Copyright 2018 Yiancar
 * Copyright 2021 Doni Crosby
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

#include "is31fl3737-mono.h"
#include "i2c_master.h"
#include "wait.h"

#define IS31FL3737_PWM_REGISTER_COUNT 192 // actually 144
#define IS31FL3737_LED_CONTROL_REGISTER_COUNT 24

#ifndef IS31FL3737_I2C_TIMEOUT
#    define IS31FL3737_I2C_TIMEOUT 100
#endif

#ifndef IS31FL3737_I2C_PERSISTENCE
#    define IS31FL3737_I2C_PERSISTENCE 0
#endif

#ifndef IS31FL3737_PWM_FREQUENCY
#    define IS31FL3737_PWM_FREQUENCY IS31FL3737_PWM_FREQUENCY_8K4_HZ // PFS - IS31FL3737B only
#endif

#ifndef IS31FL3737_SW_PULLUP
#    define IS31FL3737_SW_PULLUP IS31FL3737_PUR_0_OHM
#endif

#ifndef IS31FL3737_CS_PULLDOWN
#    define IS31FL3737_CS_PULLDOWN IS31FL3737_PDR_0_OHM
#endif

#ifndef IS31FL3737_GLOBAL_CURRENT
#    define IS31FL3737_GLOBAL_CURRENT 0xFF
#endif

// These buffers match the IS31FL3737 PWM registers.
// The control buffers match the page 0 LED On/Off registers.
// Storing them like this is optimal for I2C transfers to the registers.
// We could optimize this and take out the unused registers from these
// buffers and the transfers in is31fl3737_write_pwm_buffer() but it's
// probably not worth the extra complexity.

uint8_t g_pwm_buffer[IS31FL3737_DRIVER_COUNT][IS31FL3737_PWM_REGISTER_COUNT];
bool    g_pwm_buffer_update_required[IS31FL3737_DRIVER_COUNT] = {false};

uint8_t g_led_control_registers[IS31FL3737_DRIVER_COUNT][IS31FL3737_LED_CONTROL_REGISTER_COUNT] = {0};
bool    g_led_control_registers_update_required[IS31FL3737_DRIVER_COUNT]                        = {false};

void is31fl3737_write_register(uint8_t addr, uint8_t reg, uint8_t data) {
#if IS31FL3737_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3737_I2C_PERSISTENCE; i++) {
        if (i2c_writeReg(addr << 1, reg, &data, 1, IS31FL3737_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
    }
#else
    i2c_writeReg(addr << 1, reg, &data, 1, IS31FL3737_I2C_TIMEOUT);
#endif
}

void is31fl3737_select_page(uint8_t addr, uint8_t page) {
    is31fl3737_write_register(addr, IS31FL3737_REG_COMMAND_WRITE_LOCK, IS31FL3737_COMMAND_WRITE_LOCK_MAGIC);
    is31fl3737_write_register(addr, IS31FL3737_REG_COMMAND, page);
}

void is31fl3737_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer) {
    // Assumes page 1 is already selected.
    // Transmit PWM registers in 12 transfers of 16 bytes.

    // Iterate over the pwm_buffer contents at 16 byte intervals.
    for (uint8_t i = 0; i < IS31FL3737_PWM_REGISTER_COUNT; i += 16) {
#if IS31FL3737_I2C_PERSISTENCE > 0
        for (uint8_t j = 0; j < IS31FL3737_I2C_PERSISTENCE; j++) {
            if (i2c_writeReg(addr << 1, i, pwm_buffer + i, 16, IS31FL3737_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
        }
#else
        i2c_writeReg(addr << 1, i, pwm_buffer + i, 16, IS31FL3737_I2C_TIMEOUT);
#endif
    }
}

void is31fl3737_init_drivers(void) {
    i2c_init();

    is31fl3737_init(IS31FL3737_I2C_ADDRESS_1);
#if defined(IS31FL3737_I2C_ADDRESS_2)
    is31fl3737_init(IS31FL3737_I2C_ADDRESS_2);
#    if defined(IS31FL3737_I2C_ADDRESS_3)
    is31fl3737_init(IS31FL3737_I2C_ADDRESS_3);
#        if defined(IS31FL3737_I2C_ADDRESS_4)
    is31fl3737_init(IS31FL3737_I2C_ADDRESS_4);
#        endif
#    endif
#endif

    for (int i = 0; i < IS31FL3737_LED_COUNT; i++) {
        is31fl3737_set_led_control_register(i, true);
    }

    is31fl3737_update_led_control_registers(IS31FL3737_I2C_ADDRESS_1, 0);
#if defined(IS31FL3737_I2C_ADDRESS_2)
    is31fl3737_update_led_control_registers(IS31FL3737_I2C_ADDRESS_2, 1);
#    if defined(IS31FL3737_I2C_ADDRESS_3)
    is31fl3737_update_led_control_registers(IS31FL3737_I2C_ADDRESS_3, 2);
#        if defined(IS31FL3737_I2C_ADDRESS_4)
    is31fl3737_update_led_control_registers(IS31FL3737_I2C_ADDRESS_4, 3);
#        endif
#    endif
#endif
}

void is31fl3737_init(uint8_t addr) {
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, shutdown is enabled last.
    // Set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.

    is31fl3737_select_page(addr, IS31FL3737_COMMAND_LED_CONTROL);

    // Turn off all LEDs.
    for (int i = 0; i < IS31FL3737_LED_CONTROL_REGISTER_COUNT; i++) {
        is31fl3737_write_register(addr, i, 0x00);
    }

    is31fl3737_select_page(addr, IS31FL3737_COMMAND_PWM);

    // Set PWM on all LEDs to 0
    // No need to setup Breath registers to PWM as that is the default.
    for (int i = 0; i < IS31FL3737_PWM_REGISTER_COUNT; i++) {
        is31fl3737_write_register(addr, i, 0x00);
    }

    is31fl3737_select_page(addr, IS31FL3737_COMMAND_FUNCTION);

    // Set de-ghost pull-up resistors (SWx)
    is31fl3737_write_register(addr, IS31FL3737_FUNCTION_REG_SW_PULLUP, IS31FL3737_SW_PULLUP);
    // Set de-ghost pull-down resistors (CSx)
    is31fl3737_write_register(addr, IS31FL3737_FUNCTION_REG_CS_PULLDOWN, IS31FL3737_CS_PULLDOWN);
    // Set global current to maximum.
    is31fl3737_write_register(addr, IS31FL3737_FUNCTION_REG_GLOBAL_CURRENT, IS31FL3737_GLOBAL_CURRENT);
    // Disable software shutdown.
    is31fl3737_write_register(addr, IS31FL3737_FUNCTION_REG_CONFIGURATION, ((IS31FL3737_PWM_FREQUENCY & 0b111) << 3) | 0x01);

    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

void is31fl3737_set_value(int index, uint8_t value) {
    is31fl3737_led_t led;

    if (index >= 0 && index < IS31FL3737_LED_COUNT) {
        memcpy_P(&led, (&g_is31fl3737_leds[index]), sizeof(led));

        if (g_pwm_buffer[led.driver][led.v] == value) {
            return;
        }

        g_pwm_buffer[led.driver][led.v]          = value;
        g_pwm_buffer_update_required[led.driver] = true;
    }
}

void is31fl3737_set_value_all(uint8_t value) {
    for (int i = 0; i < IS31FL3737_LED_COUNT; i++) {
        is31fl3737_set_value(i, value);
    }
}

void is31fl3737_set_led_control_register(uint8_t index, bool value) {
    is31fl3737_led_t led;
    memcpy_P(&led, (&g_is31fl3737_leds[index]), sizeof(led));

    uint8_t control_register = led.v / 8;
    uint8_t bit_value        = led.v % 8;

    if (value) {
        g_led_control_registers[led.driver][control_register] |= (1 << bit_value);
    } else {
        g_led_control_registers[led.driver][control_register] &= ~(1 << bit_value);
    }

    g_led_control_registers_update_required[led.driver] = true;
}

void is31fl3737_update_pwm_buffers(uint8_t addr, uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        is31fl3737_select_page(addr, IS31FL3737_COMMAND_PWM);

        is31fl3737_write_pwm_buffer(addr, g_pwm_buffer[index]);

        g_pwm_buffer_update_required[index] = false;
    }
}

void is31fl3737_update_led_control_registers(uint8_t addr, uint8_t index) {
    if (g_led_control_registers_update_required[index]) {
        is31fl3737_select_page(addr, IS31FL3737_COMMAND_LED_CONTROL);

        for (int i = 0; i < IS31FL3737_LED_CONTROL_REGISTER_COUNT; i++) {
            is31fl3737_write_register(addr, i, g_led_control_registers[index][i]);
        }

        g_led_control_registers_update_required[index] = false;
    }
}

void is31fl3737_flush(void) {
    is31fl3737_update_pwm_buffers(IS31FL3737_I2C_ADDRESS_1, 0);
#if defined(IS31FL3737_I2C_ADDRESS_2)
    is31fl3737_update_pwm_buffers(IS31FL3737_I2C_ADDRESS_2, 1);
#    if defined(IS31FL3737_I2C_ADDRESS_3)
    is31fl3737_update_pwm_buffers(IS31FL3737_I2C_ADDRESS_3, 2);
#        if defined(IS31FL3737_I2C_ADDRESS_4)
    is31fl3737_update_pwm_buffers(IS31FL3737_I2C_ADDRESS_4, 3);
#        endif
#    endif
#endif
}
