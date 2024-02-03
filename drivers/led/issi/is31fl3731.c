/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
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

#include "is31fl3731.h"
#include "i2c_master.h"
#include "wait.h"

#define IS31FL3731_PWM_REGISTER_COUNT 144
#define IS31FL3731_LED_CONTROL_REGISTER_COUNT 18

#ifndef IS31FL3731_I2C_TIMEOUT
#    define IS31FL3731_I2C_TIMEOUT 100
#endif

#ifndef IS31FL3731_I2C_PERSISTENCE
#    define IS31FL3731_I2C_PERSISTENCE 0
#endif

// These buffers match the IS31FL3731 PWM registers 0x24-0xB3.
// Storing them like this is optimal for I2C transfers to the registers.
// We could optimize this and take out the unused registers from these
// buffers and the transfers in is31fl3731_write_pwm_buffer() but it's
// probably not worth the extra complexity.
uint8_t g_pwm_buffer[IS31FL3731_DRIVER_COUNT][IS31FL3731_PWM_REGISTER_COUNT];
bool    g_pwm_buffer_update_required[IS31FL3731_DRIVER_COUNT] = {false};

uint8_t g_led_control_registers[IS31FL3731_DRIVER_COUNT][IS31FL3731_LED_CONTROL_REGISTER_COUNT] = {0};
bool    g_led_control_registers_update_required[IS31FL3731_DRIVER_COUNT]                        = {false};

void is31fl3731_write_register(uint8_t addr, uint8_t reg, uint8_t data) {
#if IS31FL3731_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3731_I2C_PERSISTENCE; i++) {
        if (i2c_write_register(addr << 1, reg, &data, 1, IS31FL3731_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
    }
#else
    i2c_write_register(addr << 1, reg, &data, 1, IS31FL3731_I2C_TIMEOUT);
#endif
}

void is31fl3731_select_page(uint8_t addr, uint8_t page) {
    is31fl3731_write_register(addr, IS31FL3731_REG_COMMAND, page);
}

void is31fl3731_write_pwm_buffer(uint8_t addr, uint8_t index) {
    // Assumes page 0 is already selected.
    // Transmit PWM registers in 9 transfers of 16 bytes.

    // Iterate over the pwm_buffer contents at 16 byte intervals.
    for (uint8_t i = 0; i < IS31FL3731_PWM_REGISTER_COUNT; i += 16) {
#if IS31FL3731_I2C_PERSISTENCE > 0
        for (uint8_t j = 0; j < IS31FL3731_I2C_PERSISTENCE; j++) {
            if (i2c_write_register(addr << 1, IS31FL3731_FRAME_REG_PWM + i, g_pwm_buffer[index] + i, 16, IS31FL3731_I2C_TIMEOUT) == I2C_STATUS_SUCCESS) break;
        }
#else
        i2c_write_register(addr << 1, IS31FL3731_FRAME_REG_PWM + i, g_pwm_buffer[index] + i, 16, IS31FL3731_I2C_TIMEOUT);
#endif
    }
}

void is31fl3731_init_drivers(void) {
    i2c_init();

    is31fl3731_init(IS31FL3731_I2C_ADDRESS_1);
#if defined(IS31FL3731_I2C_ADDRESS_2)
    is31fl3731_init(IS31FL3731_I2C_ADDRESS_2);
#    if defined(IS31FL3731_I2C_ADDRESS_3)
    is31fl3731_init(IS31FL3731_I2C_ADDRESS_3);
#        if defined(IS31FL3731_I2C_ADDRESS_4)
    is31fl3731_init(IS31FL3731_I2C_ADDRESS_4);
#        endif
#    endif
#endif

    for (int i = 0; i < IS31FL3731_LED_COUNT; i++) {
        is31fl3731_set_led_control_register(i, true, true, true);
    }

    is31fl3731_update_led_control_registers(IS31FL3731_I2C_ADDRESS_1, 0);
#if defined(IS31FL3731_I2C_ADDRESS_2)
    is31fl3731_update_led_control_registers(IS31FL3731_I2C_ADDRESS_2, 1);
#    if defined(IS31FL3731_I2C_ADDRESS_3)
    is31fl3731_update_led_control_registers(IS31FL3731_I2C_ADDRESS_3, 2);
#        if defined(IS31FL3731_I2C_ADDRESS_4)
    is31fl3731_update_led_control_registers(IS31FL3731_I2C_ADDRESS_4, 3);
#        endif
#    endif
#endif
}

void is31fl3731_init(uint8_t addr) {
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, first enable software shutdown,
    // then set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.

    is31fl3731_select_page(addr, IS31FL3731_COMMAND_FUNCTION);

    // enable software shutdown
    is31fl3731_write_register(addr, IS31FL3731_FUNCTION_REG_SHUTDOWN, 0x00);
#ifdef IS31FL3731_DEGHOST // set to enable de-ghosting of the array
    is31fl3731_write_register(addr, IS31FL3731_FUNCTION_REG_GHOST_IMAGE_PREVENTION, IS31FL3731_GHOST_IMAGE_PREVENTION_GEN);
#endif

    // this delay was copied from other drivers, might not be needed
    wait_ms(10);

    // picture mode
    is31fl3731_write_register(addr, IS31FL3731_FUNCTION_REG_CONFIG, IS31FL3731_CONFIG_MODE_PICTURE);
    // display frame 0
    is31fl3731_write_register(addr, IS31FL3731_FUNCTION_REG_PICTURE_DISPLAY, 0x00);
    // audio sync off
    is31fl3731_write_register(addr, IS31FL3731_FUNCTION_REG_AUDIO_SYNC, 0x00);

    is31fl3731_select_page(addr, IS31FL3731_COMMAND_FRAME_1);

    // turn off all LEDs in the LED control register
    for (uint8_t i = 0; i < IS31FL3731_LED_CONTROL_REGISTER_COUNT; i++) {
        is31fl3731_write_register(addr, IS31FL3731_FRAME_REG_LED_CONTROL + i, 0x00);
    }

    // turn off all LEDs in the blink control register (not really needed)
    for (uint8_t i = 0; i < IS31FL3731_LED_CONTROL_REGISTER_COUNT; i++) {
        is31fl3731_write_register(addr, IS31FL3731_FRAME_REG_BLINK_CONTROL + i, 0x00);
    }

    // set PWM on all LEDs to 0
    for (uint8_t i = 0; i < IS31FL3731_PWM_REGISTER_COUNT; i++) {
        is31fl3731_write_register(addr, IS31FL3731_FRAME_REG_PWM + i, 0x00);
    }

    is31fl3731_select_page(addr, IS31FL3731_COMMAND_FUNCTION);

    // disable software shutdown
    is31fl3731_write_register(addr, IS31FL3731_FUNCTION_REG_SHUTDOWN, 0x01);

    // select page 0 and leave it selected.
    // most usage after initialization is just writing PWM buffers in page 0
    // as there's not much point in double-buffering
    is31fl3731_select_page(addr, IS31FL3731_COMMAND_FRAME_1);
}

void is31fl3731_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    is31fl3731_led_t led;

    if (index >= 0 && index < IS31FL3731_LED_COUNT) {
        memcpy_P(&led, (&g_is31fl3731_leds[index]), sizeof(led));

        if (g_pwm_buffer[led.driver][led.r] == red && g_pwm_buffer[led.driver][led.g] == green && g_pwm_buffer[led.driver][led.b] == blue) {
            return;
        }

        g_pwm_buffer[led.driver][led.r]          = red;
        g_pwm_buffer[led.driver][led.g]          = green;
        g_pwm_buffer[led.driver][led.b]          = blue;
        g_pwm_buffer_update_required[led.driver] = true;
    }
}

void is31fl3731_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < IS31FL3731_LED_COUNT; i++) {
        is31fl3731_set_color(i, red, green, blue);
    }
}

void is31fl3731_set_led_control_register(uint8_t index, bool red, bool green, bool blue) {
    is31fl3731_led_t led;
    memcpy_P(&led, (&g_is31fl3731_leds[index]), sizeof(led));

    uint8_t control_register_r = led.r / 8;
    uint8_t control_register_g = led.g / 8;
    uint8_t control_register_b = led.b / 8;
    uint8_t bit_r              = led.r % 8;
    uint8_t bit_g              = led.g % 8;
    uint8_t bit_b              = led.b % 8;

    if (red) {
        g_led_control_registers[led.driver][control_register_r] |= (1 << bit_r);
    } else {
        g_led_control_registers[led.driver][control_register_r] &= ~(1 << bit_r);
    }
    if (green) {
        g_led_control_registers[led.driver][control_register_g] |= (1 << bit_g);
    } else {
        g_led_control_registers[led.driver][control_register_g] &= ~(1 << bit_g);
    }
    if (blue) {
        g_led_control_registers[led.driver][control_register_b] |= (1 << bit_b);
    } else {
        g_led_control_registers[led.driver][control_register_b] &= ~(1 << bit_b);
    }

    g_led_control_registers_update_required[led.driver] = true;
}

void is31fl3731_update_pwm_buffers(uint8_t addr, uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        is31fl3731_write_pwm_buffer(addr, index);

        g_pwm_buffer_update_required[index] = false;
    }
}

void is31fl3731_update_led_control_registers(uint8_t addr, uint8_t index) {
    if (g_led_control_registers_update_required[index]) {
        for (uint8_t i = 0; i < IS31FL3731_LED_CONTROL_REGISTER_COUNT; i++) {
            is31fl3731_write_register(addr, i, g_led_control_registers[index][i]);
        }

        g_led_control_registers_update_required[index] = false;
    }
}

void is31fl3731_flush(void) {
    is31fl3731_update_pwm_buffers(IS31FL3731_I2C_ADDRESS_1, 0);
#if defined(IS31FL3731_I2C_ADDRESS_2)
    is31fl3731_update_pwm_buffers(IS31FL3731_I2C_ADDRESS_2, 1);
#    if defined(IS31FL3731_I2C_ADDRESS_3)
    is31fl3731_update_pwm_buffers(IS31FL3731_I2C_ADDRESS_3, 2);
#        if defined(IS31FL3731_I2C_ADDRESS_4)
    is31fl3731_update_pwm_buffers(IS31FL3731_I2C_ADDRESS_4, 3);
#        endif
#    endif
#endif
}
