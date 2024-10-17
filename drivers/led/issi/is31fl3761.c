/* Copyright 2024 TAB
 * Copyright 2024 OWLab
 * Copyright 2024 Qwertykeys
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

#include "is31fl3761.h"
#include "i2c_master.h"
#include "gpio.h"
#include "wait.h"

/**
 * @brief Sample:
 * #include "rgb_matrix.h"
 * const rgb_matrix_driver_t rgb_matrix_driver = {
 *     .init          = is31fl3761_init_drivers,
 *     .flush         = is31fl3761_flush,
 *     .set_color     = is31fl3761_set_color,
 *     .set_color_all = is31fl3761_set_color_all,
 * };
 */

#define IS31FL3761_PWM_0_REGISTER_COUNT 252
#define IS31FL3761_PWM_1_REGISTER_COUNT 252
#define IS31FL3761_PWM_2_REGISTER_COUNT 90
#define IS31FL3761_SCALING_REGISTER_COUNT 66
#define IS31FL3761_SCALING_START_ADDR 0x5B

#ifndef IS31FL3761_I2C_TIMEOUT
#    define IS31FL3761_I2C_TIMEOUT 100
#endif

#ifndef IS31FL3761_I2C_PERSISTENCE
#    define IS31FL3761_I2C_PERSISTENCE 0
#endif

#ifndef IS31FL3761_CONFIGURATION
#    define IS31FL3761_CONFIGURATION 0x01
#endif

#ifndef IS31FL3761_PWM_FREQUENCY
#    define IS31FL3761_PWM_FREQUENCY IS31FL3761_PWM_FREQUENCY_26K_HZ
#endif

#ifndef IS31FL3761_SW_PULLDOWN
#    define IS31FL3761_SW_PULLDOWN IS31FL3761_PDR_2V6
#endif

#ifndef IS31FL3761_CS_PULLUP
#    define IS31FL3761_CS_PULLUP IS31FL3761_PUR_VCC_SUB_0V8
#endif

#ifndef IS31FL3761_GLOBAL_CURRENT
#    define IS31FL3761_GLOBAL_CURRENT 0xFF
#endif

const uint8_t i2c_addresses[IS31FL3761_DRIVER_COUNT] = {
    IS31FL3761_I2C_ADDRESS_1,
#ifdef IS31FL3761_I2C_ADDRESS_2
    IS31FL3761_I2C_ADDRESS_2,
#    ifdef IS31FL3761_I2C_ADDRESS_3
    IS31FL3761_I2C_ADDRESS_3,
#        ifdef IS31FL3761_I2C_ADDRESS_4
    IS31FL3761_I2C_ADDRESS_4,
#        endif
#    endif
#endif
};

// These buffers match the IS31FL3761 and IS31FL3761A PWM registers.
// The scaling buffers match the page 2 and 3 LED On/Off registers.
// Storing them like this is optimal for I2C transfers to the registers.
// We could optimize this and take out the unused registers from these
// buffers and the transfers in is31fl3761_write_pwm_buffer() but it's
// probably not worth the extra complexity.
typedef struct is31fl3761_driver_t {
    uint8_t pwm_buffer_0[IS31FL3761_PWM_0_REGISTER_COUNT];
    uint8_t pwm_buffer_1[IS31FL3761_PWM_1_REGISTER_COUNT];
    uint8_t pwm_buffer_2[IS31FL3761_PWM_2_REGISTER_COUNT];
    bool    pwm_buffer_dirty;
    uint8_t scaling_buffer[IS31FL3761_SCALING_REGISTER_COUNT];
    bool    scaling_buffer_dirty;
} PACKED is31fl3761_driver_t;

static is31fl3761_driver_t driver_buffers[IS31FL3761_DRIVER_COUNT] = {{
    .pwm_buffer_0         = {0},
    .pwm_buffer_1         = {0},
    .pwm_buffer_2         = {0},
    .pwm_buffer_dirty     = false,
    .scaling_buffer       = {0},
    .scaling_buffer_dirty = false,
}};

void is31fl3761_write_register(uint8_t index, uint8_t reg, uint8_t data) {
#if IS31FL3761_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3761_I2C_PERSISTENCE; i++) {
        if (i2c_write_register(i2c_addresses[index] << 1, reg, &data, 1, IS31FL3761_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
    }
#else
    i2c_write_register(i2c_addresses[index] << 1, reg, &data, 1, IS31FL3761_I2C_TIMEOUT);
#endif
}

void is31fl3761_select_page(uint8_t index, uint8_t page) {
    is31fl3761_write_register(index, IS31FL3761_REG_COMMAND_WRITE_LOCK, IS31FL3761_COMMAND_WRITE_LOCK_MAGIC);
    is31fl3761_write_register(index, IS31FL3761_REG_COMMAND, page);
}

static void is31fl3761_write_pwm_page_buffer(uint8_t index, uint8_t page, uint8_t count, uint8_t *buffer) {
    is31fl3761_select_page(index, page);

    // Transmit PWM0 registers in 14 transfers of 18 bytes.
    // Iterate over the pwm_buffer_0 contents at 18 byte intervals.
    for (uint8_t i = 0; i < count; i += 18) {
#if IS31FL3761_I2C_PERSISTENCE > 0
        for (uint8_t j = 0; j < IS31FL3761_I2C_PERSISTENCE; j++) {
            if (i2c_write_register(i2c_addresses[index] << 1, i + 1, buffer + i, 18, IS31FL3761_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
        }
#else
        i2c_write_register(i2c_addresses[index] << 1, i + 1, buffer + i, 18, IS31FL3761_I2C_TIMEOUT);
#endif
    }
}

void is31fl3761_write_pwm_buffer(uint8_t index) {
    is31fl3761_write_pwm_page_buffer(index, IS31FL3761_COMMAND_PAGE_0, IS31FL3761_PWM_0_REGISTER_COUNT, driver_buffers[index].pwm_buffer_0);
    is31fl3761_write_pwm_page_buffer(index, IS31FL3761_COMMAND_PAGE_1, IS31FL3761_PWM_1_REGISTER_COUNT, driver_buffers[index].pwm_buffer_1);
    is31fl3761_write_pwm_page_buffer(index, IS31FL3761_COMMAND_PAGE_2, IS31FL3761_PWM_2_REGISTER_COUNT, driver_buffers[index].pwm_buffer_2);
    // Update pwm data
    is31fl3761_write_register(index, IS31FL3761_REG_PWM_UPDATE, 0x00);
}

void is31fl3761_init_drivers(void) {
    i2c_init();

#if defined(IS31FL3761_SDB_PIN)
    gpio_set_pin_output(IS31FL3761_SDB_PIN);
    gpio_write_pin_high(IS31FL3761_SDB_PIN);
#endif

    for (uint8_t i = 0; i < IS31FL3761_DRIVER_COUNT; i++) {
        is31fl3761_init(i);
        memset(driver_buffers[i].scaling_buffer, 0xFF, IS31FL3761_SCALING_REGISTER_COUNT);
        driver_buffers[i].scaling_buffer_dirty = true;
    }

    // for (int i = 0; i < IS31FL3761_LED_COUNT; i++) {
    //     is31fl3761_set_led_control_register(i, true, true, true);
    // }

    for (uint8_t i = 0; i < IS31FL3761_DRIVER_COUNT; i++) {
        is31fl3761_update_led_control_registers(i);
    }
}

void is31fl3761_init(uint8_t index) {
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, shutdown is enabled last.
    // Set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.
    // Unlock the command register.

    is31fl3761_select_page(index, IS31FL3761_COMMAND_PAGE_2);

    // Set to Normal operation
    is31fl3761_write_register(index, IS31FL3761_FUNCTION_REG_CONFIGURATION, IS31FL3761_CONFIGURATION);

    // Set Golbal Current Control Register
    is31fl3761_write_register(index, IS31FL3761_FUNCTION_REG_GLOBAL_CURRENT, IS31FL3761_GLOBAL_CURRENT);
    // Set Pull up & Down for SWx CSy
    is31fl3761_write_register(index, IS31FL3761_FUNCTION_REG_PULLDOWNUP, ((IS31FL3761_SW_PULLDOWN << 4) | IS31FL3761_CS_PULLUP));
    // Set PWM frequency
    is31fl3761_write_register(index, IS31FL3761_FUNCTION_REG_PWM_FREQUENCY, (IS31FL3761_PWM_FREQUENCY & 0b111));

    // is31fl3761_update_led_scaling_registers(index, 0xFF, 0xFF, 0xFF);

    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

uint8_t get_pwm_value(uint8_t driver, uint16_t reg) {
    if (reg < 0x100) {
        return driver_buffers[driver].pwm_buffer_0[reg];
    } else if (reg < 0x200) {
        return driver_buffers[driver].pwm_buffer_1[reg & 0xFF];
    } else {
        return driver_buffers[driver].pwm_buffer_2[reg & 0xFF];
    }
}

void set_pwm_value(uint8_t driver, uint16_t reg, uint8_t value) {
    if (reg < 0x100) {
        driver_buffers[driver].pwm_buffer_0[reg] = value;
    } else if (reg < 0x200) {
        driver_buffers[driver].pwm_buffer_1[reg & 0xFF] = value;
    } else {
        driver_buffers[driver].pwm_buffer_2[reg & 0xFF] = value;
    }
}

void is31fl3761_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    is31fl3761_led_t led;

    if (index >= 0 && index < IS31FL3761_LED_COUNT) {
        memcpy_P(&led, (&g_is31fl3761_leds[index]), sizeof(led));

        if (get_pwm_value(led.driver, led.r) == red && get_pwm_value(led.driver, led.g) == green && get_pwm_value(led.driver, led.b) == blue) {
            return;
        }

        set_pwm_value(led.driver, led.r, red);
        set_pwm_value(led.driver, led.g, green);
        set_pwm_value(led.driver, led.b, blue);
        driver_buffers[led.driver].pwm_buffer_dirty = true;
    }
}

void is31fl3761_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < IS31FL3761_LED_COUNT; i++) {
        is31fl3761_set_color(i, red, green, blue);
    }
}

void set_scaling_value(uint8_t driver, uint16_t reg, uint8_t value) {
    if (reg < 0x100) {
        driver_buffers[driver].scaling_buffer[reg / 18] = value;
    } else if (reg < 0x200) {
        driver_buffers[driver].scaling_buffer[((reg & 0xFF) / 18) + 14] = value;
    } else if (reg < 0x225) {
        driver_buffers[driver].scaling_buffer[((reg & 0xFF) / 18) + 28] = value;
    } else {
        driver_buffers[driver].scaling_buffer[30 + (((reg & 0xFF) - CS3_SW1) * 2 / 3)] = value;
    }
}

void is31fl3761_set_led_control_register(uint8_t index, bool red, bool green, bool blue) {
    is31fl3761_led_t led;
    memcpy_P(&led, (&g_is31fl3761_leds[index]), sizeof(led));

    set_scaling_value(led.driver, led.r, red ? 0xFF : 0x00);
    set_scaling_value(led.driver, led.g, green ? 0xFF : 0x00);
    set_scaling_value(led.driver, led.b, blue ? 0xFF : 0x00);

    driver_buffers[led.driver].scaling_buffer_dirty = true;
}

void is31fl3761_update_pwm_buffers(uint8_t index) {
    if (driver_buffers[index].pwm_buffer_dirty) {
        is31fl3761_write_pwm_buffer(index);

        driver_buffers[index].pwm_buffer_dirty = false;
    }
}

void is31fl3761_set_pwm_buffer(const is31fl3761_led_t *pled, uint8_t red, uint8_t green, uint8_t blue) {
    set_pwm_value(pled->driver, pled->r, red);
    set_pwm_value(pled->driver, pled->g, green);
    set_pwm_value(pled->driver, pled->b, blue);
    driver_buffers[pled->driver].pwm_buffer_dirty = true;
}

void is31fl3761_update_led_control_registers(uint8_t index) {
    if (driver_buffers[index].scaling_buffer_dirty) {
        is31fl3761_select_page(index, IS31FL3761_COMMAND_PAGE_2);

        for (uint8_t i = 0; i < IS31FL3761_SCALING_REGISTER_COUNT; i++) {
            is31fl3761_write_register(index, IS31FL3761_SCALING_START_ADDR + i, driver_buffers[index].scaling_buffer[i]);
        }
        driver_buffers[index].scaling_buffer_dirty = false;
    }
}

void is31fl3761_set_scaling_registers(const is31fl3761_led_t *pled, uint8_t red, uint8_t green, uint8_t blue) {
    set_scaling_value(pled->driver, pled->r, red);
    set_scaling_value(pled->driver, pled->g, green);
    set_scaling_value(pled->driver, pled->b, blue);
    driver_buffers[pled->driver].scaling_buffer_dirty = true;
}

void is31fl3761_flush(void) {
    for (uint8_t i = 0; i < IS31FL3761_DRIVER_COUNT; i++) {
        is31fl3761_update_pwm_buffers(i);
    }
}
