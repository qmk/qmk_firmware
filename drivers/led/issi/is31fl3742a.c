/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
 * Copyright 2018 Yiancar
 * Copyright 2020 MelGeek
 * Copyright 2021 MasterSpoon
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

#include "is31fl3742a.h"
#include "i2c_master.h"
#include "wait.h"

#define IS31FL3742A_PWM_REGISTER_COUNT 180
#define IS31FL3742A_SCALING_REGISTER_COUNT 180

#ifndef IS31FL3742A_I2C_TIMEOUT
#    define IS31FL3742A_I2C_TIMEOUT 100
#endif

#ifndef IS31FL3742A_I2C_PERSISTENCE
#    define IS31FL3742A_I2C_PERSISTENCE 0
#endif

#ifndef IS31FL3742A_CONFIGURATION
#    define IS31FL3742A_CONFIGURATION 0x31
#endif

#ifndef IS31FL3742A_PWM_FREQUENCY
#    define IS31FL3742A_PWM_FREQUENCY IS31FL3742A_PWM_FREQUENCY_29K_HZ
#endif

#ifndef IS31FL3742A_SW_PULLDOWN
#    define IS31FL3742A_SW_PULLDOWN IS31FL3742A_PDR_8K_OHM
#endif

#ifndef IS31FL3742A_CS_PULLUP
#    define IS31FL3742A_CS_PULLUP IS31FL3742A_PUR_8K_OHM
#endif

#ifndef IS31FL3742A_GLOBAL_CURRENT
#    define IS31FL3742A_GLOBAL_CURRENT 0xFF
#endif

uint8_t g_pwm_buffer[IS31FL3742A_DRIVER_COUNT][IS31FL3742A_PWM_REGISTER_COUNT];
bool    g_pwm_buffer_update_required[IS31FL3742A_DRIVER_COUNT]        = {false};
bool    g_scaling_registers_update_required[IS31FL3742A_DRIVER_COUNT] = {false};

uint8_t g_scaling_registers[IS31FL3742A_DRIVER_COUNT][IS31FL3742A_SCALING_REGISTER_COUNT];

void is31fl3742a_write_register(uint8_t addr, uint8_t reg, uint8_t data) {
#if IS31FL3742A_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3742A_I2C_PERSISTENCE; i++) {
        if (i2c_writeReg(addr << 1, reg, &data, 1, IS31FL3742A_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
    }
#else
    i2c_writeReg(addr << 1, reg, &data, 1, IS31FL3742A_I2C_TIMEOUT);
#endif
}

void is31fl3742a_select_page(uint8_t addr, uint8_t page) {
    is31fl3742a_write_register(addr, IS31FL3742A_REG_COMMAND_WRITE_LOCK, IS31FL3742A_COMMAND_WRITE_LOCK_MAGIC);
    is31fl3742a_write_register(addr, IS31FL3742A_REG_COMMAND, page);
}

void is31fl3742a_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer) {
    // Assumes page 0 is already selected.
    // Transmit PWM registers in 6 transfers of 30 bytes.

    // Iterate over the pwm_buffer contents at 30 byte intervals.
    for (uint8_t i = 0; i < IS31FL3742A_PWM_REGISTER_COUNT; i += 30) {
#if IS31FL3742A_I2C_PERSISTENCE > 0
        for (uint8_t j = 0; j < IS31FL3742A_I2C_PERSISTENCE; j++) {
            if (i2c_writeReg(addr << 1, i + 1, pwm_buffer + i, 30, IS31FL3742A_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
        }
#else
        i2c_writeReg(addr << 1, i + 1, pwm_buffer + i, 30, IS31FL3742A_I2C_TIMEOUT);
#endif
    }
}

void is31fl3742a_init_drivers(void) {
    i2c_init();

    is31fl3742a_init(IS31FL3742A_I2C_ADDRESS_1);
#if defined(IS31FL3742A_I2C_ADDRESS_2)
    is31fl3742a_init(IS31FL3742A_I2C_ADDRESS_2);
#    if defined(IS31FL3742A_I2C_ADDRESS_3)
    is31fl3742a_init(IS31FL3742A_I2C_ADDRESS_3);
#        if defined(IS31FL3742A_I2C_ADDRESS_4)
    is31fl3742a_init(IS31FL3742A_I2C_ADDRESS_4);
#        endif
#    endif
#endif

    for (int i = 0; i < IS31FL3742A_LED_COUNT; i++) {
        is31fl3742a_set_scaling_register(i, 0xFF, 0xFF, 0xFF);
    }

    is31fl3742a_update_scaling_registers(IS31FL3742A_I2C_ADDRESS_1, 0);
#if defined(IS31FL3742A_I2C_ADDRESS_2)
    is31fl3742a_update_scaling_registers(IS31FL3742A_I2C_ADDRESS_2, 1);
#    if defined(IS31FL3742A_I2C_ADDRESS_3)
    is31fl3742a_update_scaling_registers(IS31FL3742A_I2C_ADDRESS_3, 2);
#        if defined(IS31FL3742A_I2C_ADDRESS_4)
    is31fl3742a_update_scaling_registers(IS31FL3742A_I2C_ADDRESS_4, 3);
#        endif
#    endif
#endif
}

void is31fl3742a_init(uint8_t addr) {
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, shutdown is enabled last.
    // Set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.

    is31fl3742a_select_page(addr, IS31FL3742A_COMMAND_SCALING);

    // Turn off all LEDs.
    for (int i = 0; i < IS31FL3742A_SCALING_REGISTER_COUNT; i++) {
        is31fl3742a_write_register(addr, i, 0x00);
    }

    is31fl3742a_select_page(addr, IS31FL3742A_COMMAND_PWM);

    for (int i = 0; i < IS31FL3742A_PWM_REGISTER_COUNT; i++) {
        is31fl3742a_write_register(addr, i, 0x00);
    }

    is31fl3742a_select_page(addr, IS31FL3742A_COMMAND_FUNCTION);

    is31fl3742a_write_register(addr, IS31FL3742A_FUNCTION_REG_PULLDOWNUP, (IS31FL3742A_SW_PULLDOWN << 4) | IS31FL3742A_CS_PULLUP);
    is31fl3742a_write_register(addr, IS31FL3742A_FUNCTION_REG_GLOBAL_CURRENT, IS31FL3742A_GLOBAL_CURRENT);
    is31fl3742a_write_register(addr, IS31FL3742A_FUNCTION_REG_PWM_FREQUENCY, (IS31FL3742A_PWM_FREQUENCY & 0b0111));
    is31fl3742a_write_register(addr, IS31FL3742A_FUNCTION_REG_CONFIGURATION, IS31FL3742A_CONFIGURATION);

    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

void is31fl3742a_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    is31fl3742a_led_t led;

    if (index >= 0 && index < IS31FL3742A_LED_COUNT) {
        memcpy_P(&led, (&g_is31fl3742a_leds[index]), sizeof(led));

        if (g_pwm_buffer[led.driver][led.r] == red && g_pwm_buffer[led.driver][led.g] == green && g_pwm_buffer[led.driver][led.b] == blue) {
            return;
        }

        g_pwm_buffer[led.driver][led.r]          = red;
        g_pwm_buffer[led.driver][led.g]          = green;
        g_pwm_buffer[led.driver][led.b]          = blue;
        g_pwm_buffer_update_required[led.driver] = true;
    }
}

void is31fl3742a_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < IS31FL3742A_LED_COUNT; i++) {
        is31fl3742a_set_color(i, red, green, blue);
    }
}

void is31fl3742a_set_scaling_register(uint8_t index, uint8_t red, uint8_t green, uint8_t blue) {
    is31fl3742a_led_t led;
    memcpy_P(&led, (&g_is31fl3742a_leds[index]), sizeof(led));

    g_scaling_registers[led.driver][led.r]          = red;
    g_scaling_registers[led.driver][led.g]          = green;
    g_scaling_registers[led.driver][led.b]          = blue;
    g_scaling_registers_update_required[led.driver] = true;
}

void is31fl3742a_update_pwm_buffers(uint8_t addr, uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        is31fl3742a_select_page(addr, IS31FL3742A_COMMAND_PWM);

        is31fl3742a_write_pwm_buffer(addr, g_pwm_buffer[index]);

        g_pwm_buffer_update_required[index] = false;
    }
}

void is31fl3742a_update_scaling_registers(uint8_t addr, uint8_t index) {
    if (g_scaling_registers_update_required[index]) {
        is31fl3742a_select_page(addr, IS31FL3742A_COMMAND_SCALING);

        for (int i = 0; i < IS31FL3742A_SCALING_REGISTER_COUNT; i++) {
            is31fl3742a_write_register(addr, i, g_scaling_registers[index][i]);
        }

        g_scaling_registers_update_required[index] = false;
    }
}

void is31fl3742a_flush(void) {
    is31fl3742a_update_pwm_buffers(IS31FL3742A_I2C_ADDRESS_1, 0);
#if defined(IS31FL3742A_I2C_ADDRESS_2)
    is31fl3742a_update_pwm_buffers(IS31FL3742A_I2C_ADDRESS_2, 1);
#    if defined(IS31FL3742A_I2C_ADDRESS_3)
    is31fl3742a_update_pwm_buffers(IS31FL3742A_I2C_ADDRESS_3, 2);
#        if defined(IS31FL3742A_I2C_ADDRESS_4)
    is31fl3742a_update_pwm_buffers(IS31FL3742A_I2C_ADDRESS_4, 3);
#        endif
#    endif
#endif
}
