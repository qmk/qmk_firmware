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

#include "is31fl3729.h"
#include "i2c_master.h"
#include "gpio.h"
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

#ifndef IS31FL3729_SW_PULLDOWN
#    define IS31FL3729_SW_PULLDOWN IS31FL3729_SW_PULLDOWN_2K_OHM_SW_OFF
#endif

#ifndef IS31FL3729_CS_PULLUP
#    define IS31FL3729_CS_PULLUP IS31FL3729_CS_PULLUP_2K_OHM_CS_OFF
#endif

#ifndef IS31FL3729_SPREAD_SPECTRUM
#    define IS31FL3729_SPREAD_SPECTRUM IS31FL3729_SPREAD_SPECTRUM_DISABLE
#endif

#ifndef IS31FL3729_SPREAD_SPECTRUM_RANGE
#    define IS31FL3729_SPREAD_SPECTRUM_RANGE IS31FL3729_SPREAD_SPECTRUM_RANGE_5_PERCENT
#endif

#ifndef IS31FL3729_SPREAD_SPECTRUM_CYCLE_TIME
#    define IS31FL3729_SPREAD_SPECTRUM_CYCLE_TIME IS31FL3729_SPREAD_SPECTRUM_CYCLE_TIME_1980_US
#endif

#ifndef IS31FL3729_PWM_FREQUENCY
#    define IS31FL3729_PWM_FREQUENCY IS31FL3729_PWM_FREQUENCY_32K_HZ
#endif

const uint8_t i2c_addresses[IS31FL3729_DRIVER_COUNT] = {
    IS31FL3729_I2C_ADDRESS_1,
#ifdef IS31FL3729_I2C_ADDRESS_2
    IS31FL3729_I2C_ADDRESS_2,
#    ifdef IS31FL3729_I2C_ADDRESS_3
    IS31FL3729_I2C_ADDRESS_3,
#        ifdef IS31FL3729_I2C_ADDRESS_4
    IS31FL3729_I2C_ADDRESS_4,
#        endif
#    endif
#endif
};

// These buffers match the PWM & scaling registers.
// Storing them like this is optimal for I2C transfers to the registers.
typedef struct is31fl3729_driver_t {
    uint8_t pwm_buffer[IS31FL3729_PWM_REGISTER_COUNT];
    bool    pwm_buffer_dirty;
    uint8_t scaling_buffer[IS31FL3729_SCALING_REGISTER_COUNT];
    bool    scaling_buffer_dirty;
} PACKED is31fl3729_driver_t;

is31fl3729_driver_t driver_buffers[IS31FL3729_DRIVER_COUNT] = {{
    .pwm_buffer           = {0},
    .pwm_buffer_dirty     = false,
    .scaling_buffer       = {0},
    .scaling_buffer_dirty = false,
}};

void is31fl3729_write_register(uint8_t index, uint8_t reg, uint8_t data) {
#if IS31FL3729_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3729_I2C_PERSISTENCE; i++) {
        if (i2c_write_register(i2c_addresses[index] << 1, reg, &data, 1, IS31FL3729_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
    }
#else
    i2c_write_register(i2c_addresses[index] << 1, reg, &data, 1, IS31FL3729_I2C_TIMEOUT);
#endif
}

void is31fl3729_write_pwm_buffer(uint8_t index) {
    // Transmit PWM registers in 11 transfers of 13 bytes.

    // Iterate over the pwm_buffer contents at 13 byte intervals.
    for (uint8_t i = 0; i <= IS31FL3729_PWM_REGISTER_COUNT; i += 13) {
#if IS31FL3729_I2C_PERSISTENCE > 0
        for (uint8_t j = 0; j < IS31FL3729_I2C_PERSISTENCE; j++) {
            if (i2c_write_register(i2c_addresses[index] << 1, IS31FL3729_REG_PWM + i, driver_buffers[index].pwm_buffer + i, 13, IS31FL3729_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
        }
#else
        i2c_write_register(i2c_addresses[index] << 1, IS31FL3729_REG_PWM + i, driver_buffers[index].pwm_buffer + i, 13, IS31FL3729_I2C_TIMEOUT);
#endif
    }
}

void is31fl3729_init_drivers(void) {
    i2c_init();

#if defined(IS31FL3729_SDB_PIN)
    gpio_set_pin_output(IS31FL3729_SDB_PIN);
    gpio_write_pin_high(IS31FL3729_SDB_PIN);
#endif

    for (uint8_t i = 0; i < IS31FL3729_DRIVER_COUNT; i++) {
        is31fl3729_init(i);
    }

    for (int i = 0; i < IS31FL3729_LED_COUNT; i++) {
        is31fl3729_set_scaling_register(i, 0xFF, 0xFF, 0xFF);
    }

    for (uint8_t i = 0; i < IS31FL3729_DRIVER_COUNT; i++) {
        is31fl3729_update_scaling_registers(i);
    }
}

void is31fl3729_init(uint8_t index) {
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, shutdown is enabled last.
    // Set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.

    is31fl3729_write_register(index, IS31FL3729_REG_PULLDOWNUP, ((IS31FL3729_SW_PULLDOWN & 0b111) << 4) | (IS31FL3729_CS_PULLUP & 0b111));
    is31fl3729_write_register(index, IS31FL3729_REG_SPREAD_SPECTRUM, ((IS31FL3729_SPREAD_SPECTRUM & 0b1) << 4) | ((IS31FL3729_SPREAD_SPECTRUM_RANGE & 0b11) << 2) | (IS31FL3729_SPREAD_SPECTRUM_CYCLE_TIME & 0b11));
    is31fl3729_write_register(index, IS31FL3729_REG_PWM_FREQUENCY, IS31FL3729_PWM_FREQUENCY);
    is31fl3729_write_register(index, IS31FL3729_REG_GLOBAL_CURRENT, IS31FL3729_GLOBAL_CURRENT);
    is31fl3729_write_register(index, IS31FL3729_REG_CONFIGURATION, IS31FL3729_CONFIGURATION);

    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

void is31fl3729_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    is31fl3729_led_t led;
    if (index >= 0 && index < IS31FL3729_LED_COUNT) {
        memcpy_P(&led, (&g_is31fl3729_leds[index]), sizeof(led));

        if (driver_buffers[led.driver].pwm_buffer[led.r] == red && driver_buffers[led.driver].pwm_buffer[led.g] == green && driver_buffers[led.driver].pwm_buffer[led.b] == blue) {
            return;
        }

        driver_buffers[led.driver].pwm_buffer[led.r] = red;
        driver_buffers[led.driver].pwm_buffer[led.g] = green;
        driver_buffers[led.driver].pwm_buffer[led.b] = blue;
        driver_buffers[led.driver].pwm_buffer_dirty  = true;
    }
}

void is31fl3729_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < IS31FL3729_LED_COUNT; i++) {
        is31fl3729_set_color(i, red, green, blue);
    }
}

void is31fl3729_set_scaling_register(uint8_t index, uint8_t red, uint8_t green, uint8_t blue) {
    is31fl3729_led_t led;
    memcpy_P(&led, (&g_is31fl3729_leds[index]), sizeof(led));

    // need to do a bit of checking here since 3729 scaling is per CS pin.
    // not the usual per RGB key as per other ISSI drivers
    // only enable them, since they should be default disabled
    int cs_red   = (led.r & 0x0F) - 1;
    int cs_green = (led.g & 0x0F) - 1;
    int cs_blue  = (led.b & 0x0F) - 1;

    driver_buffers[led.driver].scaling_buffer[cs_red]   = red;
    driver_buffers[led.driver].scaling_buffer[cs_green] = green;
    driver_buffers[led.driver].scaling_buffer[cs_blue]  = blue;
    driver_buffers[led.driver].scaling_buffer_dirty     = true;
}

void is31fl3729_update_pwm_buffers(uint8_t index) {
    if (driver_buffers[index].pwm_buffer_dirty) {
        is31fl3729_write_pwm_buffer(index);

        driver_buffers[index].pwm_buffer_dirty = false;
    }
}

void is31fl3729_update_scaling_registers(uint8_t index) {
    if (driver_buffers[index].scaling_buffer_dirty) {
        for (uint8_t i = 0; i < IS31FL3729_SCALING_REGISTER_COUNT; i++) {
            is31fl3729_write_register(index, IS31FL3729_REG_SCALING + i, driver_buffers[index].scaling_buffer[i]);
        }

        driver_buffers[index].scaling_buffer_dirty = false;
    }
}

void is31fl3729_flush(void) {
    for (uint8_t i = 0; i < IS31FL3729_DRIVER_COUNT; i++) {
        is31fl3729_update_pwm_buffers(i);
    }
}
