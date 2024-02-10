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

const uint8_t i2c_addresses[IS31FL3742A_DRIVER_COUNT] = {
    IS31FL3742A_I2C_ADDRESS_1,
#ifdef IS31FL3742A_I2C_ADDRESS_2
    IS31FL3742A_I2C_ADDRESS_2,
#    ifdef IS31FL3742A_I2C_ADDRESS_3
    IS31FL3742A_I2C_ADDRESS_3,
#        ifdef IS31FL3742A_I2C_ADDRESS_4
    IS31FL3742A_I2C_ADDRESS_4,
#        endif
#    endif
#endif
};

typedef struct is31fl3742a_driver_t {
    uint8_t pwm_buffer[IS31FL3742A_PWM_REGISTER_COUNT];
    bool    pwm_buffer_dirty;
    uint8_t scaling_buffer[IS31FL3742A_SCALING_REGISTER_COUNT];
    bool    scaling_buffer_dirty;
} PACKED is31fl3742a_driver_t;

is31fl3742a_driver_t driver_buffers[IS31FL3742A_DRIVER_COUNT] = {{
    .pwm_buffer           = {0},
    .pwm_buffer_dirty     = false,
    .scaling_buffer       = {0},
    .scaling_buffer_dirty = false,
}};

void is31fl3742a_write_register(uint8_t index, uint8_t reg, uint8_t data) {
#if IS31FL3742A_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3742A_I2C_PERSISTENCE; i++) {
        if (i2c_write_register(i2c_addresses[index] << 1, reg, &data, 1, IS31FL3742A_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
    }
#else
    i2c_write_register(i2c_addresses[index] << 1, reg, &data, 1, IS31FL3742A_I2C_TIMEOUT);
#endif
}

void is31fl3742a_select_page(uint8_t index, uint8_t page) {
    is31fl3742a_write_register(index, IS31FL3742A_REG_COMMAND_WRITE_LOCK, IS31FL3742A_COMMAND_WRITE_LOCK_MAGIC);
    is31fl3742a_write_register(index, IS31FL3742A_REG_COMMAND, page);
}

void is31fl3742a_write_pwm_buffer(uint8_t index) {
    // Assumes page 0 is already selected.
    // Transmit PWM registers in 6 transfers of 30 bytes.

    // Iterate over the pwm_buffer contents at 30 byte intervals.
    for (uint8_t i = 0; i < IS31FL3742A_PWM_REGISTER_COUNT; i += 30) {
#if IS31FL3742A_I2C_PERSISTENCE > 0
        for (uint8_t j = 0; j < IS31FL3742A_I2C_PERSISTENCE; j++) {
            if (i2c_write_register(i2c_addresses[index] << 1, i, driver_buffers[index].pwm_buffer + i, 30, IS31FL3742A_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
        }
#else
        i2c_write_register(i2c_addresses[index] << 1, i, driver_buffers[index].pwm_buffer + i, 30, IS31FL3742A_I2C_TIMEOUT);
#endif
    }
}

void is31fl3742a_init_drivers(void) {
    i2c_init();

    for (uint8_t i = 0; i < IS31FL3742A_DRIVER_COUNT; i++) {
        is31fl3742a_init(i);
    }

    for (int i = 0; i < IS31FL3742A_LED_COUNT; i++) {
        is31fl3742a_set_scaling_register(i, 0xFF, 0xFF, 0xFF);
    }

    for (uint8_t i = 0; i < IS31FL3742A_DRIVER_COUNT; i++) {
        is31fl3742a_update_scaling_registers(i);
    }
}

void is31fl3742a_init(uint8_t index) {
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, shutdown is enabled last.
    // Set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.

    is31fl3742a_select_page(index, IS31FL3742A_COMMAND_SCALING);

    // Turn off all LEDs.
    for (uint8_t i = 0; i < IS31FL3742A_SCALING_REGISTER_COUNT; i++) {
        is31fl3742a_write_register(index, i, 0x00);
    }

    is31fl3742a_select_page(index, IS31FL3742A_COMMAND_PWM);

    for (uint8_t i = 0; i < IS31FL3742A_PWM_REGISTER_COUNT; i++) {
        is31fl3742a_write_register(index, i, 0x00);
    }

    is31fl3742a_select_page(index, IS31FL3742A_COMMAND_FUNCTION);

    is31fl3742a_write_register(index, IS31FL3742A_FUNCTION_REG_PULLDOWNUP, (IS31FL3742A_SW_PULLDOWN << 4) | IS31FL3742A_CS_PULLUP);
    is31fl3742a_write_register(index, IS31FL3742A_FUNCTION_REG_GLOBAL_CURRENT, IS31FL3742A_GLOBAL_CURRENT);
    is31fl3742a_write_register(index, IS31FL3742A_FUNCTION_REG_PWM_FREQUENCY, (IS31FL3742A_PWM_FREQUENCY & 0b0111));
    is31fl3742a_write_register(index, IS31FL3742A_FUNCTION_REG_CONFIGURATION, IS31FL3742A_CONFIGURATION);

    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

void is31fl3742a_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    is31fl3742a_led_t led;

    if (index >= 0 && index < IS31FL3742A_LED_COUNT) {
        memcpy_P(&led, (&g_is31fl3742a_leds[index]), sizeof(led));

        if (driver_buffers[led.driver].pwm_buffer[led.r] == red && driver_buffers[led.driver].pwm_buffer[led.g] == green && driver_buffers[led.driver].pwm_buffer[led.b] == blue) {
            return;
        }

        driver_buffers[led.driver].pwm_buffer[led.r] = red;
        driver_buffers[led.driver].pwm_buffer[led.g] = green;
        driver_buffers[led.driver].pwm_buffer[led.b] = blue;
        driver_buffers[led.driver].pwm_buffer_dirty  = true;
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

    driver_buffers[led.driver].scaling_buffer[led.r] = red;
    driver_buffers[led.driver].scaling_buffer[led.g] = green;
    driver_buffers[led.driver].scaling_buffer[led.b] = blue;
    driver_buffers[led.driver].scaling_buffer_dirty  = true;
}

void is31fl3742a_update_pwm_buffers(uint8_t index) {
    if (driver_buffers[index].pwm_buffer_dirty) {
        is31fl3742a_select_page(index, IS31FL3742A_COMMAND_PWM);

        is31fl3742a_write_pwm_buffer(index);

        driver_buffers[index].pwm_buffer_dirty = false;
    }
}

void is31fl3742a_update_scaling_registers(uint8_t index) {
    if (driver_buffers[index].scaling_buffer_dirty) {
        is31fl3742a_select_page(index, IS31FL3742A_COMMAND_SCALING);

        for (uint8_t i = 0; i < IS31FL3742A_SCALING_REGISTER_COUNT; i++) {
            is31fl3742a_write_register(index, i, driver_buffers[index].scaling_buffer[i]);
        }

        driver_buffers[index].scaling_buffer_dirty = false;
    }
}

void is31fl3742a_flush(void) {
    for (uint8_t i = 0; i < IS31FL3742A_DRIVER_COUNT; i++) {
        is31fl3742a_update_pwm_buffers(i);
    }
}
