/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
 * Copyright 2018 Yiancar
 * Copyright 2020 MelGeek
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

#include "is31fl3741-mono.h"
#include "i2c_master.h"
#include "gpio.h"
#include "wait.h"

#define IS31FL3741_PWM_0_REGISTER_COUNT 180
#define IS31FL3741_PWM_1_REGISTER_COUNT 171
#define IS31FL3741_SCALING_0_REGISTER_COUNT 180
#define IS31FL3741_SCALING_1_REGISTER_COUNT 171

#ifndef IS31FL3741_I2C_TIMEOUT
#    define IS31FL3741_I2C_TIMEOUT 100
#endif

#ifndef IS31FL3741_I2C_PERSISTENCE
#    define IS31FL3741_I2C_PERSISTENCE 0
#endif

#ifndef IS31FL3741_CONFIGURATION
#    define IS31FL3741_CONFIGURATION 0x01
#endif

#ifndef IS31FL3741_PWM_FREQUENCY
#    define IS31FL3741_PWM_FREQUENCY IS31FL3741_PWM_FREQUENCY_29K_HZ
#endif

#ifndef IS31FL3741_SW_PULLUP
#    define IS31FL3741_SW_PULLUP IS31FL3741_PUR_32K_OHM
#endif

#ifndef IS31FL3741_CS_PULLDOWN
#    define IS31FL3741_CS_PULLDOWN IS31FL3741_PDR_32K_OHM
#endif

#ifndef IS31FL3741_GLOBAL_CURRENT
#    define IS31FL3741_GLOBAL_CURRENT 0xFF
#endif

const uint8_t i2c_addresses[IS31FL3741_DRIVER_COUNT] = {
    IS31FL3741_I2C_ADDRESS_1,
#ifdef IS31FL3741_I2C_ADDRESS_2
    IS31FL3741_I2C_ADDRESS_2,
#    ifdef IS31FL3741_I2C_ADDRESS_3
    IS31FL3741_I2C_ADDRESS_3,
#        ifdef IS31FL3741_I2C_ADDRESS_4
    IS31FL3741_I2C_ADDRESS_4,
#        endif
#    endif
#endif
};

// These buffers match the IS31FL3741 and IS31FL3741A PWM registers.
// The scaling buffers match the page 2 and 3 LED On/Off registers.
// Storing them like this is optimal for I2C transfers to the registers.
// We could optimize this and take out the unused registers from these
// buffers and the transfers in is31fl3741_write_pwm_buffer() but it's
// probably not worth the extra complexity.
typedef struct is31fl3741_driver_t {
    uint8_t pwm_buffer_0[IS31FL3741_PWM_0_REGISTER_COUNT];
    uint8_t pwm_buffer_1[IS31FL3741_PWM_1_REGISTER_COUNT];
    bool    pwm_buffer_dirty;
    uint8_t scaling_buffer_0[IS31FL3741_SCALING_0_REGISTER_COUNT];
    uint8_t scaling_buffer_1[IS31FL3741_SCALING_1_REGISTER_COUNT];
    bool    scaling_buffer_dirty;
} PACKED is31fl3741_driver_t;

is31fl3741_driver_t driver_buffers[IS31FL3741_DRIVER_COUNT] = {{
    .pwm_buffer_0         = {0},
    .pwm_buffer_1         = {0},
    .pwm_buffer_dirty     = false,
    .scaling_buffer_0     = {0},
    .scaling_buffer_1     = {0},
    .scaling_buffer_dirty = false,
}};

void is31fl3741_write_register(uint8_t index, uint8_t reg, uint8_t data) {
#if IS31FL3741_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3741_I2C_PERSISTENCE; i++) {
        if (i2c_write_register(i2c_addresses[index] << 1, reg, &data, 1, IS31FL3741_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
    }
#else
    i2c_write_register(i2c_addresses[index] << 1, reg, &data, 1, IS31FL3741_I2C_TIMEOUT);
#endif
}

void is31fl3741_select_page(uint8_t index, uint8_t page) {
    is31fl3741_write_register(index, IS31FL3741_REG_COMMAND_WRITE_LOCK, IS31FL3741_COMMAND_WRITE_LOCK_MAGIC);
    is31fl3741_write_register(index, IS31FL3741_REG_COMMAND, page);
}

void is31fl3741_write_pwm_buffer(uint8_t index) {
    is31fl3741_select_page(index, IS31FL3741_COMMAND_PWM_0);

    // Transmit PWM0 registers in 6 transfers of 30 bytes.

    // Iterate over the pwm_buffer_0 contents at 30 byte intervals.
    for (uint8_t i = 0; i < IS31FL3741_PWM_0_REGISTER_COUNT; i += 30) {
#if IS31FL3741_I2C_PERSISTENCE > 0
        for (uint8_t j = 0; j < IS31FL3741_I2C_PERSISTENCE; j++) {
            if (i2c_write_register(i2c_addresses[index] << 1, i, driver_buffers[index].pwm_buffer_0 + i, 30, IS31FL3741_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
        }
#else
        i2c_write_register(i2c_addresses[index] << 1, i, driver_buffers[index].pwm_buffer_0 + i, 30, IS31FL3741_I2C_TIMEOUT);
#endif
    }

    is31fl3741_select_page(index, IS31FL3741_COMMAND_PWM_1);

    // Transmit PWM1 registers in 9 transfers of 19 bytes.

    // Iterate over the pwm_buffer_1 contents at 19 byte intervals.
    for (uint8_t i = 0; i < IS31FL3741_PWM_1_REGISTER_COUNT; i += 19) {
#if IS31FL3741_I2C_PERSISTENCE > 0
        for (uint8_t i = 0; i < IS31FL3741_I2C_PERSISTENCE; i++) {
            if (i2c_write_register(i2c_addresses[index] << 1, i, driver_buffers[index].pwm_buffer_1 + i, 19, IS31FL3741_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
        }
#else
        i2c_write_register(i2c_addresses[index] << 1, i, driver_buffers[index].pwm_buffer_1 + i, 19, IS31FL3741_I2C_TIMEOUT);
#endif
    }
}

void is31fl3741_init_drivers(void) {
    i2c_init();

#if defined(IS31FL3741_SDB_PIN)
    setPinOutput(IS31FL3741_SDB_PIN);
    writePinHigh(IS31FL3741_SDB_PIN);
#endif

    for (uint8_t i = 0; i < IS31FL3741_DRIVER_COUNT; i++) {
        is31fl3741_init(i);
    }

    for (int i = 0; i < IS31FL3741_LED_COUNT; i++) {
        is31fl3741_set_led_control_register(i, true);
    }

    for (uint8_t i = 0; i < IS31FL3741_DRIVER_COUNT; i++) {
        is31fl3741_update_led_control_registers(i);
    }
}

void is31fl3741_init(uint8_t index) {
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, shutdown is enabled last.
    // Set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.
    // Unlock the command register.

    is31fl3741_select_page(index, IS31FL3741_COMMAND_FUNCTION);

    // Set to Normal operation
    is31fl3741_write_register(index, IS31FL3741_FUNCTION_REG_CONFIGURATION, IS31FL3741_CONFIGURATION);

    // Set Golbal Current Control Register
    is31fl3741_write_register(index, IS31FL3741_FUNCTION_REG_GLOBAL_CURRENT, IS31FL3741_GLOBAL_CURRENT);
    // Set Pull up & Down for SWx CSy
    is31fl3741_write_register(index, IS31FL3741_FUNCTION_REG_PULLDOWNUP, ((IS31FL3741_CS_PULLDOWN << 4) | IS31FL3741_SW_PULLUP));
    // Set PWM frequency
    is31fl3741_write_register(index, IS31FL3741_FUNCTION_REG_PWM_FREQUENCY, (IS31FL3741_PWM_FREQUENCY & 0b1111));

    // is31fl3741_update_led_scaling_registers(index, 0xFF, 0xFF, 0xFF);

    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

uint8_t get_pwm_value(uint8_t driver, uint16_t reg) {
    if (reg & 0x100) {
        return driver_buffers[driver].pwm_buffer_1[reg & 0xFF];
    } else {
        return driver_buffers[driver].pwm_buffer_0[reg];
    }
}

void set_pwm_value(uint8_t driver, uint16_t reg, uint8_t value) {
    if (reg & 0x100) {
        driver_buffers[driver].pwm_buffer_1[reg & 0xFF] = value;
    } else {
        driver_buffers[driver].pwm_buffer_0[reg] = value;
    }
}

void is31fl3741_set_value(int index, uint8_t value) {
    is31fl3741_led_t led;

    if (index >= 0 && index < IS31FL3741_LED_COUNT) {
        memcpy_P(&led, (&g_is31fl3741_leds[index]), sizeof(led));

        if (get_pwm_value(led.driver, led.v) == value) {
            return;
        }

        set_pwm_value(led.driver, led.v, value);
        driver_buffers[led.driver].pwm_buffer_dirty = true;
    }
}

void is31fl3741_set_value_all(uint8_t value) {
    for (int i = 0; i < IS31FL3741_LED_COUNT; i++) {
        is31fl3741_set_value(i, value);
    }
}

void set_scaling_value(uint8_t driver, uint16_t reg, uint8_t value) {
    if (reg & 0x100) {
        driver_buffers[driver].scaling_buffer_1[reg & 0xFF] = value;
    } else {
        driver_buffers[driver].scaling_buffer_0[reg] = value;
    }
}

void is31fl3741_set_led_control_register(uint8_t index, bool value) {
    is31fl3741_led_t led;
    memcpy_P(&led, (&g_is31fl3741_leds[index]), sizeof(led));

    set_scaling_value(led.driver, led.v, value ? 0xFF : 0x00);

    driver_buffers[led.driver].scaling_buffer_dirty = true;
}

void is31fl3741_update_pwm_buffers(uint8_t index) {
    if (driver_buffers[index].pwm_buffer_dirty) {
        is31fl3741_write_pwm_buffer(index);

        driver_buffers[index].pwm_buffer_dirty = false;
    }
}

void is31fl3741_set_pwm_buffer(const is31fl3741_led_t *pled, uint8_t value) {
    set_pwm_value(pled->driver, pled->v, value);
    driver_buffers[pled->driver].pwm_buffer_dirty = true;
}

void is31fl3741_update_led_control_registers(uint8_t index) {
    if (driver_buffers[index].scaling_buffer_dirty) {
        is31fl3741_select_page(index, IS31FL3741_COMMAND_SCALING_0);

        for (uint8_t i = 0; i < IS31FL3741_SCALING_0_REGISTER_COUNT; i++) {
            is31fl3741_write_register(index, i, driver_buffers[index].scaling_buffer_0[i]);
        }

        is31fl3741_select_page(index, IS31FL3741_COMMAND_SCALING_1);

        for (uint8_t i = 0; i < IS31FL3741_SCALING_1_REGISTER_COUNT; i++) {
            is31fl3741_write_register(index, i, driver_buffers[index].scaling_buffer_1[i]);
        }

        driver_buffers[index].scaling_buffer_dirty = false;
    }
}

void is31fl3741_set_scaling_registers(const is31fl3741_led_t *pled, uint8_t value) {
    set_scaling_value(pled->driver, pled->v, value);
    driver_buffers[pled->driver].scaling_buffer_dirty = true;
}

void is31fl3741_flush(void) {
    for (uint8_t i = 0; i < IS31FL3741_DRIVER_COUNT; i++) {
        is31fl3741_update_pwm_buffers(i);
    }
}
