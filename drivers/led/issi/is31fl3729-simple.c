/* Copyright 2023 HorrorTroll <https://github.com/HorrorTroll>
 * Copyright 2023 Harrison Chan (Xelus)
 * Copyright 2023 Dimitris Mantzouranis <d3xter93@gmail.com>
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

#include "wait.h"

#include "is31fl3729-simple.h"
#include <string.h>
#include "i2c_master.h"
#include "progmem.h"

// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 00 <-> GND
// 01 <-> SCL
// 10 <-> SDA
// 11 <-> VCC
// ADDR represents A2:A1 of the 7-bit address.
// The result is: 0b01101(ADDR)
#define ISSI_ADDR_DEFAULT 0x68

// Registers
#define ISSI_REG_SCALING 0x90
#define ISSI_REG_CONFIGURATION 0xA0
#define ISSI_REG_GLOBALCURRENT 0xA1
#define ISSI_REG_PULLDOWNUP 0xB0
#define ISSI_REG_RESET 0xCF
#define ISSI_REG_PWM_SET 0xB2

// Set defaults for Timeout and Persistence
#ifndef ISSI_TIMEOUT
#    define ISSI_TIMEOUT 100
#endif
#ifndef ISSI_PERSISTENCE
#    define ISSI_PERSISTENCE 0
#endif

// Set defaults for Registers
#ifndef ISSI_CONFIGURATION
#    define ISSI_CONFIGURATION 0x01
#endif
#ifndef ISSI_GLOBALCURRENT
#    define ISSI_GLOBALCURRENT 0x40
#endif
#ifndef ISSI_PULLDOWNUP
#    define ISSI_PULLDOWNUP 0x33
#endif
#ifndef ISSI_PWM_SET
#    define ISSI_PWM_SET 0x01
#endif

// Set buffer sizes
#define ISSI_MAX_LEDS 143
#define ISSI_MAX_SCALINGS 16

// Transfer buffer for TWITransmitData()
uint8_t g_twi_transfer_buffer[20];

// These buffers match the PWM & scaling registers.
// Storing them like this is optimal for I2C transfers to the registers.
uint8_t g_pwm_buffer[LED_DRIVER_COUNT][ISSI_MAX_LEDS];
bool    g_pwm_buffer_update_required[LED_DRIVER_COUNT] = {false};

uint8_t g_scaling_registers[LED_DRIVER_COUNT][ISSI_MAX_SCALINGS];
bool    g_scaling_registers_update_required[LED_DRIVER_COUNT] = {false};

void is31fl3729_write_register(uint8_t addr, uint8_t reg, uint8_t data) {
    // Set register address and register data ready to write
    g_twi_transfer_buffer[0] = reg;
    g_twi_transfer_buffer[1] = data;

#if ISSI_PERSISTENCE > 0
    for (uint8_t i = 0; i < ISSI_PERSISTENCE; i++) {
        if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 2, ISSI_TIMEOUT) == 0) break;
    }
#else
    i2c_transmit(addr << 1, g_twi_transfer_buffer, 2, ISSI_TIMEOUT);
#endif
}

bool is31fl3729_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer) {
    // iterate over the pwm_buffer contents at ISSI_MAX_SCALINGS byte intervals
    // datasheet does not mention it, but it auto-increments in 15x9 mode, and
    // hence does not require us to skip any addresses
    for (int i = 0; i <= ISSI_MAX_LEDS; i += ISSI_MAX_SCALINGS) {
        g_twi_transfer_buffer[0] = i;

        // copy the data from i to i+ISSI_MAX_SCALINGS
        // device will auto-increment register for data after the first byte
        // thus this sets registers 0x01-0x10, 0x11-0x20, etc. in one transfer
        memcpy(g_twi_transfer_buffer + 1, pwm_buffer + i, ISSI_MAX_SCALINGS);

#if ISSI_PERSISTENCE > 0
        for (uint8_t i = 0; i < ISSI_PERSISTENCE; i++) {
            if (i2c_transmit(addr << 1, g_twi_transfer_buffer, ISSI_MAX_SCALINGS + 1, ISSI_TIMEOUT) != 0) {
                return false;
            }
        }
#else
        if (i2c_transmit(addr << 1, g_twi_transfer_buffer, ISSI_MAX_SCALINGS + 1, ISSI_TIMEOUT) != 0) {
            return false;
        }
#endif
    }

    return true;
}

void is31fl3729_init(uint8_t addr) {
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, shutdown is enabled last.
    // Set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.

    // Set Pull up & Down for SWx CSy
    is31fl3729_write_register(addr, ISSI_REG_PULLDOWNUP, ISSI_PULLDOWNUP);

    // Set PWM Frequency Register if applicable
    is31fl3729_write_register(addr, ISSI_REG_PWM_SET, ISSI_PWM_SET);

    // Set Golbal Current Control Register
    is31fl3729_write_register(addr, ISSI_REG_GLOBALCURRENT, ISSI_GLOBALCURRENT);

    // Set to Normal operation
    is31fl3729_write_register(addr, ISSI_REG_CONFIGURATION, ISSI_CONFIGURATION);

    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

void is31fl3729_set_value(int index, uint8_t value) {
    is31_led led;
    if (index >= 0 && index < LED_MATRIX_LED_COUNT) {
        memcpy_P(&led, (&g_is31_leds[index]), sizeof(led));

        if (g_pwm_buffer[led.driver][led.v] == value) {
            return;
        }

        g_pwm_buffer_update_required[led.driver] = true;
        g_pwm_buffer[led.driver][led.v]          = value;
    }
}

void is31fl3729_set_value_all(uint8_t value) {
    for (int i = 0; i < LED_MATRIX_LED_COUNT; i++) {
        is31fl3729_set_value(i, value);
    }
}

void is31fl3729_set_led_control_register(uint8_t index, bool value) {
    is31_led led;
    memcpy_P(&led, (&g_is31_leds[index]), sizeof(led));

    // need to do a bit of checking here since 3729 scaling is per CS pin.
    // not the usual per single LED key as per other ISSI drivers
    // only enable them, since they should be default disabled
    int cs_value = (led.v & 0x0F) - 1;

    if (value) {
        g_scaling_registers[led.driver][cs_value] = 0xFF;
    }

    g_scaling_registers_update_required[led.driver] = true;
}

void is31fl3729_update_pwm_buffers(uint8_t addr, uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        is31fl3729_write_pwm_buffer(addr, g_pwm_buffer[index]);
    }

    g_pwm_buffer_update_required[index] = false;
}

void is31fl3729_update_led_control_registers(uint8_t addr, uint8_t index) {
    if (g_scaling_registers_update_required[index]) {
        for (int i = 0; i < ISSI_MAX_SCALINGS; i++) {
            is31fl3729_write_register(addr, ISSI_REG_SCALING + i, g_scaling_registers[index][i]);
        }

        g_scaling_registers_update_required[index] = false;
    }
}
