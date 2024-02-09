/* Copyright 2018 Jason Williams (Wilba)
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

#include "is31fl3736-mono.h"
#include "i2c_master.h"
#include "wait.h"

#define IS31FL3736_PWM_REGISTER_COUNT 192 // actually 96
#define IS31FL3736_LED_CONTROL_REGISTER_COUNT 24

#ifndef IS31FL3736_I2C_TIMEOUT
#    define IS31FL3736_I2C_TIMEOUT 100
#endif

#ifndef IS31FL3736_I2C_PERSISTENCE
#    define IS31FL3736_I2C_PERSISTENCE 0
#endif

#ifndef IS31FL3736_PWM_FREQUENCY
#    define IS31FL3736_PWM_FREQUENCY IS31FL3736_PWM_FREQUENCY_8K4_HZ // PFS - IS31FL3736B only
#endif

#ifndef IS31FL3736_SW_PULLUP
#    define IS31FL3736_SW_PULLUP IS31FL3736_PUR_0_OHM
#endif

#ifndef IS31FL3736_CS_PULLDOWN
#    define IS31FL3736_CS_PULLDOWN IS31FL3736_PDR_0_OHM
#endif

#ifndef IS31FL3736_GLOBAL_CURRENT
#    define IS31FL3736_GLOBAL_CURRENT 0xFF
#endif

const uint8_t i2c_addresses[IS31FL3736_DRIVER_COUNT] = {
    IS31FL3736_I2C_ADDRESS_1,
#ifdef IS31FL3736_I2C_ADDRESS_2
    IS31FL3736_I2C_ADDRESS_2,
#    ifdef IS31FL3736_I2C_ADDRESS_3
    IS31FL3736_I2C_ADDRESS_3,
#        ifdef IS31FL3736_I2C_ADDRESS_4
    IS31FL3736_I2C_ADDRESS_4,
#        endif
#    endif
#endif
};

// These buffers match the IS31FL3736 PWM registers.
// The control buffers match the page 0 LED On/Off registers.
// Storing them like this is optimal for I2C transfers to the registers.
// We could optimize this and take out the unused registers from these
// buffers and the transfers in is31fl3736_write_pwm_buffer() but it's
// probably not worth the extra complexity.
typedef struct is31fl3736_driver_t {
    uint8_t pwm_buffer[IS31FL3736_PWM_REGISTER_COUNT];
    bool    pwm_buffer_dirty;
    uint8_t led_control_buffer[IS31FL3736_LED_CONTROL_REGISTER_COUNT];
    bool    led_control_buffer_dirty;
} PACKED is31fl3736_driver_t;

is31fl3736_driver_t driver_buffers[IS31FL3736_DRIVER_COUNT] = {{
    .pwm_buffer               = {0},
    .pwm_buffer_dirty         = false,
    .led_control_buffer       = {0},
    .led_control_buffer_dirty = false,
}};

void is31fl3736_write_register(uint8_t index, uint8_t reg, uint8_t data) {
#if IS31FL3736_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3736_I2C_PERSISTENCE; i++) {
        if (i2c_write_register(i2c_addresses[index] << 1, reg, &data, 1, IS31FL3736_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
    }
#else
    i2c_write_register(i2c_addresses[index] << 1, reg, &data, 1, IS31FL3736_I2C_TIMEOUT);
#endif
}

void is31fl3736_select_page(uint8_t index, uint8_t page) {
    is31fl3736_write_register(index, IS31FL3736_REG_COMMAND_WRITE_LOCK, IS31FL3736_COMMAND_WRITE_LOCK_MAGIC);
    is31fl3736_write_register(index, IS31FL3736_REG_COMMAND, page);
}

void is31fl3736_write_pwm_buffer(uint8_t index) {
    // Assumes page 1 is already selected.
    // Transmit PWM registers in 12 transfers of 16 bytes.

    // Iterate over the pwm_buffer contents at 16 byte intervals.
    for (uint8_t i = 0; i < IS31FL3736_PWM_REGISTER_COUNT; i += 16) {
#if IS31FL3736_I2C_PERSISTENCE > 0
        for (uint8_t j = 0; j < IS31FL3736_I2C_PERSISTENCE; j++) {
            if (i2c_write_register(i2c_addresses[index] << 1, i, driver_buffers[index].pwm_buffer + i, 16, IS31FL3736_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
        }
#else
        i2c_write_register(i2c_addresses[index] << 1, i, driver_buffers[index].pwm_buffer + i, 16, IS31FL3736_I2C_TIMEOUT);
#endif
    }
}

void is31fl3736_init_drivers(void) {
    i2c_init();

    for (uint8_t i = 0; i < IS31FL3736_DRIVER_COUNT; i++) {
        is31fl3736_init(i);
    }

    for (int i = 0; i < IS31FL3736_LED_COUNT; i++) {
        is31fl3736_set_led_control_register(i, true);
    }

    for (uint8_t i = 0; i < IS31FL3736_DRIVER_COUNT; i++) {
        is31fl3736_update_led_control_registers(i);
    }
}

void is31fl3736_init(uint8_t index) {
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, shutdown is enabled last.
    // Set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.

    is31fl3736_select_page(index, IS31FL3736_COMMAND_LED_CONTROL);

    // Turn off all LEDs.
    for (uint8_t i = 0; i < IS31FL3736_LED_CONTROL_REGISTER_COUNT; i++) {
        is31fl3736_write_register(index, i, 0x00);
    }

    is31fl3736_select_page(index, IS31FL3736_COMMAND_PWM);

    // Set PWM on all LEDs to 0
    // No need to setup Breath registers to PWM as that is the default.
    for (uint8_t i = 0; i < IS31FL3736_PWM_REGISTER_COUNT; i++) {
        is31fl3736_write_register(index, i, 0x00);
    }

    is31fl3736_select_page(index, IS31FL3736_COMMAND_FUNCTION);

    // Set de-ghost pull-up resistors (SWx)
    is31fl3736_write_register(index, IS31FL3736_FUNCTION_REG_SW_PULLUP, IS31FL3736_SW_PULLUP);
    // Set de-ghost pull-down resistors (CSx)
    is31fl3736_write_register(index, IS31FL3736_FUNCTION_REG_CS_PULLDOWN, IS31FL3736_CS_PULLDOWN);
    // Set global current to maximum.
    is31fl3736_write_register(index, IS31FL3736_FUNCTION_REG_GLOBAL_CURRENT, IS31FL3736_GLOBAL_CURRENT);
    // Disable software shutdown.
    is31fl3736_write_register(index, IS31FL3736_FUNCTION_REG_CONFIGURATION, ((IS31FL3736_PWM_FREQUENCY & 0b111) << 3) | 0x01);

    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

void is31fl3736_set_value(int index, uint8_t value) {
    is31fl3736_led_t led;

    if (index >= 0 && index < IS31FL3736_LED_COUNT) {
        memcpy_P(&led, (&g_is31fl3736_leds[index]), sizeof(led));

        if (driver_buffers[led.driver].pwm_buffer[led.v] == value) {
            return;
        }

        driver_buffers[led.driver].pwm_buffer[led.v] = value;
        driver_buffers[led.driver].pwm_buffer_dirty  = true;
    }
}

void is31fl3736_set_value_all(uint8_t value) {
    for (int i = 0; i < IS31FL3736_LED_COUNT; i++) {
        is31fl3736_set_value(i, value);
    }
}

void is31fl3736_set_led_control_register(uint8_t index, bool value) {
    is31fl3736_led_t led;
    memcpy_P(&led, (&g_is31fl3736_leds[index]), sizeof(led));

    // The PWM register for a matrix position (0x00 to 0xBF) is interleaved, so:
    // A1=0x00 A2=0x02 A3=0x04 A4=0x06 A5=0x08 A6=0x0A A7=0x0C A8=0x0E
    // B1=0x10 B2=0x12 B3=0x14
    // But also, the LED control registers (0x00 to 0x17) are also interleaved, so:
    // A1-A4=0x00 A5-A8=0x01

    uint8_t control_register = led.v / 8;
    uint8_t bit_value        = led.v % 8;

    if (value) {
        driver_buffers[led.driver].led_control_buffer[control_register] |= (1 << bit_value);
    } else {
        driver_buffers[led.driver].led_control_buffer[control_register] &= ~(1 << bit_value);
    }

    driver_buffers[led.driver].led_control_buffer_dirty = true;
}

void is31fl3736_update_pwm_buffers(uint8_t index) {
    if (driver_buffers[index].pwm_buffer_dirty) {
        is31fl3736_select_page(index, IS31FL3736_COMMAND_PWM);

        is31fl3736_write_pwm_buffer(index);

        driver_buffers[index].pwm_buffer_dirty = false;
    }
}

void is31fl3736_update_led_control_registers(uint8_t index) {
    if (driver_buffers[index].led_control_buffer_dirty) {
        is31fl3736_select_page(index, IS31FL3736_COMMAND_LED_CONTROL);

        for (uint8_t i = 0; i < IS31FL3736_LED_CONTROL_REGISTER_COUNT; i++) {
            is31fl3736_write_register(index, i, driver_buffers[index].led_control_buffer[i]);
        }

        driver_buffers[index].led_control_buffer_dirty = false;
    }
}

void is31fl3736_flush(void) {
    for (uint8_t i = 0; i < IS31FL3736_DRIVER_COUNT; i++) {
        is31fl3736_update_pwm_buffers(i);
    }
}
