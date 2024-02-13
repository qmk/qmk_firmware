/* Copyright 2024 HorrorTroll <https://github.com/HorrorTroll>
 * Copyright 2024 Harrison Chan (Xelus)
 * Copyright 2024 Dimitris Mantzouranis <d3xter93@gmail.com>
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

#include "is31fl3729-mono.h"
#include "i2c_master.h"
#include "wait.h"

#define IS31FL3729_PWM_REGISTER_COUNT 143
#define IS31FL3729_SCALING_REGISTER_COUNT 16

#ifndef IS31FL3729_I2C_TIMEOUT
#    define IS31FL3729_I2C_TIMEOUT 100
#endif

#ifndef IS31FL3729_I2C_PERSISTENCE
#    define IS31FL3729_I2C_PERSISTENCE 0
#endif

#ifndef IS31FL3729_CONFIGURATION
#    define IS31FL3729_CONFIGURATION IS31FL3729_CONFIG_SWS_15_9
#endif

#ifndef IS31FL3729_GLOBAL_CURRENT
#    define IS31FL3729_GLOBAL_CURRENT 0x40
#endif

#ifndef IS31FL3729_PULLDOWNUP
#    define IS31FL3729_PULLDOWNUP 0x33
#endif

#ifndef IS31FL3729_SPREAD_SPECTRUM
#    define IS31FL3729_SPREAD_SPECTRUM IS31FL3729_SSP_DISABLE
#endif

#ifndef IS31FL3729_SPREAD_SPECTRUM_RANGE
#    define IS31FL3729_SPREAD_SPECTRUM_RANGE IS31FL3729_RNG_5_PERCENT
#endif

#ifndef IS31FL3729_SPREAD_SPECTRUM_CYCLE_TIME
#    define IS31FL3729_SPREAD_SPECTRUM_CYCLE_TIME IS31FL3729_CLT_1980_US
#endif

#ifndef IS31FL3729_PWM_FREQUENCY
#    define IS31FL3729_PWM_FREQUENCY IS31FL3729_PWM_FREQUENCY_32K_HZ
#endif

// These buffers match the PWM & scaling registers.
// Storing them like this is optimal for I2C transfers to the registers.
uint8_t g_pwm_buffer[IS31FL3729_DRIVER_COUNT][IS31FL3729_PWM_REGISTER_COUNT];
bool    g_pwm_buffer_update_required[IS31FL3729_DRIVER_COUNT] = {false};

uint8_t g_scaling_registers[IS31FL3729_DRIVER_COUNT][IS31FL3729_SCALING_REGISTER_COUNT];
bool    g_scaling_registers_update_required[IS31FL3729_DRIVER_COUNT] = {false};

void is31fl3729_write_register(uint8_t addr, uint8_t reg, uint8_t data) {
#if IS31FL3729_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3729_I2C_PERSISTENCE; i++) {
        if (i2c_write_register(addr << 1, reg, &data, 1, IS31FL3729_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
    }
#else
    i2c_write_register(addr << 1, reg, &data, 1, IS31FL3729_I2C_TIMEOUT);
#endif
}

void is31fl3729_write_pwm_buffer(uint8_t addr, uint8_t index) {
    // Transmit PWM registers in 9 transfers of 16 bytes.

    // Iterate over the pwm_buffer contents at 16 byte intervals.
    for (uint8_t i = 0; i <= IS31FL3729_PWM_REGISTER_COUNT; i += 16) {
#if IS31FL3729_I2C_PERSISTENCE > 0
        for (uint8_t j = 0; j < IS31FL3729_I2C_PERSISTENCE; j++) {
            if (i2c_write_register(addr << 1, i, g_pwm_buffer[index] + i, 16, IS31FL3729_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
        }
#else
        i2c_write_register(addr << 1, i, g_pwm_buffer[index] + i, 16, IS31FL3729_I2C_TIMEOUT);
#endif
    }
}

void is31fl3729_init_drivers(void) {
    i2c_init();

    is31fl3729_init(IS31FL3729_I2C_ADDRESS_1);
#if defined(IS31FL3729_I2C_ADDRESS_2)
    is31fl3729_init(IS31FL3729_I2C_ADDRESS_2);
#    if defined(IS31FL3729_I2C_ADDRESS_3)
    is31fl3729_init(IS31FL3729_I2C_ADDRESS_3);
#        if defined(IS31FL3729_I2C_ADDRESS_4)
    is31fl3729_init(IS31FL3729_I2C_ADDRESS_4);
#        endif
#    endif
#endif

    for (int i = 0; i < IS31FL3729_LED_COUNT; i++) {
        is31fl3729_set_scaling_register(i, 0xFF);
    }

    is31fl3729_update_scaling_registers(IS31FL3729_I2C_ADDRESS_1, 0);
#if defined(IS31FL3729_I2C_ADDRESS_2)
    is31fl3729_update_scaling_registers(IS31FL3729_I2C_ADDRESS_2, 1);
#    if defined(IS31FL3729_I2C_ADDRESS_3)
    is31fl3729_update_scaling_registers(IS31FL3729_I2C_ADDRESS_3, 2);
#        if defined(IS31FL3729_I2C_ADDRESS_4)
    is31fl3729_update_scaling_registers(IS31FL3729_I2C_ADDRESS_4, 3);
#        endif
#    endif
#endif
}

void is31fl3729_init(uint8_t addr) {
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, shutdown is enabled last.
    // Set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.

    // Set Pull up & Down for SWx CSy
    is31fl3729_write_register(addr, IS31FL3729_REG_PULLDOWNUP, IS31FL3729_PULLDOWNUP);

    // Set Spread Spectrum Register if applicable
    is31fl3729_write_register(addr, IS31FL3729_REG_SPREAD_SPECTRUM, ((IS31FL3729_SPREAD_SPECTRUM & 0b1) << 4) | ((IS31FL3729_SPREAD_SPECTRUM_RANGE & 0b11) << 2) | (IS31FL3729_SPREAD_SPECTRUM_CYCLE_TIME & 0b11));

    // Set PWM Frequency Register if applicable
    is31fl3729_write_register(addr, IS31FL3729_REG_PWM_FREQUENCY, IS31FL3729_PWM_FREQUENCY);

    // Set Golbal Current Control Register
    is31fl3729_write_register(addr, IS31FL3729_REG_GLOBAL_CURRENT, IS31FL3729_GLOBAL_CURRENT);

    // Set to Normal operation
    is31fl3729_write_register(addr, IS31FL3729_REG_CONFIGURATION, IS31FL3729_CONFIGURATION);

    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

void is31fl3729_set_value(int index, uint8_t value) {
    is31fl3729_led_t led;
    if (index >= 0 && index < IS31FL3729_LED_COUNT) {
        memcpy_P(&led, (&g_is31fl3729_leds[index]), sizeof(led));

        if (g_pwm_buffer[led.driver][led.v] == value) {
            return;
        }

        g_pwm_buffer_update_required[led.driver] = true;
        g_pwm_buffer[led.driver][led.v]          = value;
    }
}

void is31fl3729_set_value_all(uint8_t value) {
    for (int i = 0; i < IS31FL3729_LED_COUNT; i++) {
        is31fl3729_set_value(i, value);
    }
}

void is31fl3729_set_scaling_register(uint8_t index, uint8_t value) {
    is31fl3729_led_t led;
    memcpy_P(&led, (&g_is31fl3729_leds[index]), sizeof(led));

    // need to do a bit of checking here since 3729 scaling is per CS pin.
    // not the usual per single LED key as per other ISSI drivers
    // only enable them, since they should be default disabled
    int cs_value = (led.v & 0x0F) - 1;

    g_scaling_registers[led.driver][cs_value] = value;

    g_scaling_registers_update_required[led.driver] = true;
}

void is31fl3729_update_pwm_buffers(uint8_t addr, uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        is31fl3729_write_pwm_buffer(addr, index);

        g_pwm_buffer_update_required[index] = false;
    }
}

void is31fl3729_update_scaling_registers(uint8_t addr, uint8_t index) {
    if (g_scaling_registers_update_required[index]) {
        for (uint8_t i = 0; i < IS31FL3729_SCALING_REGISTER_COUNT; i++) {
            is31fl3729_write_register(addr, IS31FL3729_REG_SCALING + i, g_scaling_registers[index][i]);
        }

        g_scaling_registers_update_required[index] = false;
    }
}

void is31fl3729_flush(void) {
    is31fl3729_update_pwm_buffers(IS31FL3729_I2C_ADDRESS_1, 0);
#if defined(IS31FL3729_I2C_ADDRESS_2)
    is31fl3729_update_pwm_buffers(IS31FL3729_I2C_ADDRESS_2, 1);
#    if defined(IS31FL3729_I2C_ADDRESS_3)
    is31fl3729_update_pwm_buffers(IS31FL3729_I2C_ADDRESS_3, 2);
#        if defined(IS31FL3729_I2C_ADDRESS_4)
    is31fl3729_update_pwm_buffers(IS31FL3729_I2C_ADDRESS_4, 3);
#        endif
#    endif
#endif
}
