/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
 * Copyright 2019 Clueboard
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

#include "is31fl3731-simple.h"
#include <string.h>
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

// Transfer buffer for TWITransmitData()
uint8_t g_twi_transfer_buffer[20];

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
    g_twi_transfer_buffer[0] = reg;
    g_twi_transfer_buffer[1] = data;

#if IS31FL3731_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3731_I2C_PERSISTENCE; i++) {
        if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 2, IS31FL3731_I2C_TIMEOUT) == 0) {
            break;
        }
    }
#else
    i2c_transmit(addr << 1, g_twi_transfer_buffer, 2, IS31FL3731_I2C_TIMEOUT);
#endif
}

void is31fl3731_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer) {
    // assumes bank is already selected

    // transmit PWM registers in 9 transfers of 16 bytes
    // g_twi_transfer_buffer[] is 20 bytes

    // iterate over the pwm_buffer contents at 16 byte intervals
    for (int i = 0; i < IS31FL3731_PWM_REGISTER_COUNT; i += 16) {
        // set the first register, e.g. 0x24, 0x34, 0x44, etc.
        g_twi_transfer_buffer[0] = 0x24 + i;
        // copy the data from i to i+15
        // device will auto-increment register for data after the first byte
        // thus this sets registers 0x24-0x33, 0x34-0x43, etc. in one transfer
        memcpy(g_twi_transfer_buffer + 1, pwm_buffer + i, 16);

#if IS31FL3731_I2C_PERSISTENCE > 0
        for (uint8_t i = 0; i < IS31FL3731_I2C_PERSISTENCE; i++) {
            if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 17, IS31FL3731_I2C_TIMEOUT) == 0) break;
        }
#else
        i2c_transmit(addr << 1, g_twi_transfer_buffer, 17, IS31FL3731_I2C_TIMEOUT);
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
        is31fl3731_set_led_control_register(i, true);
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

    // select "function register" bank
    is31fl3731_write_register(addr, IS31FL3731_REG_COMMAND, IS31FL3731_COMMAND_FUNCTION);

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

    // select bank 0
    is31fl3731_write_register(addr, IS31FL3731_REG_COMMAND, IS31FL3731_COMMAND_FRAME_1);

    // turn off all LEDs in the LED control register
    for (int i = 0; i < IS31FL3731_LED_CONTROL_REGISTER_COUNT; i++) {
        is31fl3731_write_register(addr, i, 0x00);
    }

    // turn off all LEDs in the blink control register (not really needed)
    for (int i = 0x12; i <= 0x23; i++) {
        is31fl3731_write_register(addr, i, 0x00);
    }

    // set PWM on all LEDs to 0
    for (int i = 0x24; i <= 0xB3; i++) {
        is31fl3731_write_register(addr, i, 0x00);
    }

    // select "function register" bank
    is31fl3731_write_register(addr, IS31FL3731_REG_COMMAND, IS31FL3731_COMMAND_FUNCTION);

    // disable software shutdown
    is31fl3731_write_register(addr, IS31FL3731_FUNCTION_REG_SHUTDOWN, 0x01);

    // select bank 0 and leave it selected.
    // most usage after initialization is just writing PWM buffers in bank 0
    // as there's not much point in double-buffering
    is31fl3731_write_register(addr, IS31FL3731_REG_COMMAND, IS31FL3731_COMMAND_FRAME_1);
}

void is31fl3731_set_value(int index, uint8_t value) {
    is31fl3731_led_t led;
    if (index >= 0 && index < IS31FL3731_LED_COUNT) {
        memcpy_P(&led, (&g_is31fl3731_leds[index]), sizeof(led));

        // Subtract 0x24 to get the second index of g_pwm_buffer

        if (g_pwm_buffer[led.driver][led.v - 0x24] == value) {
            return;
        }
        g_pwm_buffer[led.driver][led.v - 0x24]   = value;
        g_pwm_buffer_update_required[led.driver] = true;
    }
}

void is31fl3731_set_value_all(uint8_t value) {
    for (int i = 0; i < IS31FL3731_LED_COUNT; i++) {
        is31fl3731_set_value(i, value);
    }
}

void is31fl3731_set_led_control_register(uint8_t index, bool value) {
    is31fl3731_led_t led;
    memcpy_P(&led, (&g_is31fl3731_leds[index]), sizeof(led));

    uint8_t control_register = (led.v - 0x24) / 8;
    uint8_t bit_value        = (led.v - 0x24) % 8;

    if (value) {
        g_led_control_registers[led.driver][control_register] |= (1 << bit_value);
    } else {
        g_led_control_registers[led.driver][control_register] &= ~(1 << bit_value);
    }

    g_led_control_registers_update_required[led.driver] = true;
}

void is31fl3731_update_pwm_buffers(uint8_t addr, uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        is31fl3731_write_pwm_buffer(addr, g_pwm_buffer[index]);
        g_pwm_buffer_update_required[index] = false;
    }
}

void is31fl3731_update_led_control_registers(uint8_t addr, uint8_t index) {
    if (g_led_control_registers_update_required[index]) {
        for (int i = 0; i < IS31FL3731_LED_CONTROL_REGISTER_COUNT; i++) {
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
