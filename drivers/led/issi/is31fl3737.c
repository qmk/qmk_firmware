/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
 * Copyright 2018 Yiancar
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

#include "is31fl3737.h"
#include "i2c_master.h"
#include "wait.h"

// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 00 <-> GND
// 01 <-> SCL
// 10 <-> SDA
// 11 <-> VCC
// ADDR1 represents A1:A0 of the 7-bit address.
// ADDR2 represents A3:A2 of the 7-bit address.
// The result is: 0b101(ADDR2)(ADDR1)
#define ISSI_ADDR_DEFAULT 0x50

#define ISSI_COMMANDREGISTER 0xFD
#define ISSI_COMMANDREGISTER_WRITELOCK 0xFE
#define ISSI_INTERRUPTMASKREGISTER 0xF0
#define ISSI_INTERRUPTSTATUSREGISTER 0xF1

#define ISSI_PAGE_LEDCONTROL 0x00 // PG0
#define ISSI_PAGE_PWM 0x01        // PG1
#define ISSI_PAGE_AUTOBREATH 0x02 // PG2
#define ISSI_PAGE_FUNCTION 0x03   // PG3

#define ISSI_REG_CONFIGURATION 0x00 // PG3
#define ISSI_REG_GLOBALCURRENT 0x01 // PG3
#define ISSI_REG_RESET 0x11         // PG3
#define ISSI_REG_SWPULLUP 0x0F      // PG3
#define ISSI_REG_CSPULLUP 0x10      // PG3

#ifndef ISSI_TIMEOUT
#    define ISSI_TIMEOUT 100
#endif

#ifndef ISSI_PERSISTENCE
#    define ISSI_PERSISTENCE 0
#endif

#ifndef ISSI_SWPULLUP
#    define ISSI_SWPULLUP PUR_0R
#endif

#ifndef ISSI_CSPULLUP
#    define ISSI_CSPULLUP PUR_0R
#endif

// Transfer buffer for TWITransmitData()
uint8_t g_twi_transfer_buffer[20];

// These buffers match the IS31FL3737 PWM registers.
// The control buffers match the PG0 LED On/Off registers.
// Storing them like this is optimal for I2C transfers to the registers.
// We could optimize this and take out the unused registers from these
// buffers and the transfers in IS31FL3737_write_pwm_buffer() but it's
// probably not worth the extra complexity.

uint8_t g_pwm_buffer[DRIVER_COUNT][192];
bool    g_pwm_buffer_update_required[DRIVER_COUNT] = {false};

uint8_t g_led_control_registers[DRIVER_COUNT][24]             = {0};
bool    g_led_control_registers_update_required[DRIVER_COUNT] = {false};

void IS31FL3737_write_register(uint8_t addr, uint8_t reg, uint8_t data) {
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

void IS31FL3737_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer) {
    // assumes PG1 is already selected

    // transmit PWM registers in 12 transfers of 16 bytes
    // g_twi_transfer_buffer[] is 20 bytes

    // iterate over the pwm_buffer contents at 16 byte intervals
    for (int i = 0; i < 192; i += 16) {
        g_twi_transfer_buffer[0] = i;
        // copy the data from i to i+15
        // device will auto-increment register for data after the first byte
        // thus this sets registers 0x00-0x0F, 0x10-0x1F, etc. in one transfer
        for (int j = 0; j < 16; j++) {
            g_twi_transfer_buffer[1 + j] = pwm_buffer[i + j];
        }

#if ISSI_PERSISTENCE > 0
        for (uint8_t i = 0; i < ISSI_PERSISTENCE; i++) {
            if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 17, ISSI_TIMEOUT) == 0) break;
        }
#else
        i2c_transmit(addr << 1, g_twi_transfer_buffer, 17, ISSI_TIMEOUT);
#endif
    }
}

void IS31FL3737_init(uint8_t addr) {
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, shutdown is enabled last.
    // Set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.

    // Unlock the command register.
    IS31FL3737_write_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);

    // Select PG0
    IS31FL3737_write_register(addr, ISSI_COMMANDREGISTER, ISSI_PAGE_LEDCONTROL);
    // Turn off all LEDs.
    for (int i = 0x00; i <= 0x17; i++) {
        IS31FL3737_write_register(addr, i, 0x00);
    }

    // Unlock the command register.
    IS31FL3737_write_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);

    // Select PG1
    IS31FL3737_write_register(addr, ISSI_COMMANDREGISTER, ISSI_PAGE_PWM);
    // Set PWM on all LEDs to 0
    // No need to setup Breath registers to PWM as that is the default.
    for (int i = 0x00; i <= 0xBF; i++) {
        IS31FL3737_write_register(addr, i, 0x00);
    }

    // Unlock the command register.
    IS31FL3737_write_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);

    // Select PG3
    IS31FL3737_write_register(addr, ISSI_COMMANDREGISTER, ISSI_PAGE_FUNCTION);
    // Set de-ghost pull-up resistors (SWx)
    IS31FL3737_write_register(addr, ISSI_REG_SWPULLUP, ISSI_SWPULLUP);
    // Set de-ghost pull-down resistors (CSx)
    IS31FL3737_write_register(addr, ISSI_REG_CSPULLUP, ISSI_CSPULLUP);
    // Set global current to maximum.
    IS31FL3737_write_register(addr, ISSI_REG_GLOBALCURRENT, 0xFF);
    // Disable software shutdown.
    IS31FL3737_write_register(addr, ISSI_REG_CONFIGURATION, 0x01);

    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

void IS31FL3737_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    is31_led led;
    if (index >= 0 && index < DRIVER_LED_TOTAL) {
        memcpy_P(&led, (&g_is31_leds[index]), sizeof(led));

        g_pwm_buffer[led.driver][led.r]          = red;
        g_pwm_buffer[led.driver][led.g]          = green;
        g_pwm_buffer[led.driver][led.b]          = blue;
        g_pwm_buffer_update_required[led.driver] = true;
    }
}

void IS31FL3737_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        IS31FL3737_set_color(i, red, green, blue);
    }
}

void IS31FL3737_set_led_control_register(uint8_t index, bool red, bool green, bool blue) {
    is31_led led;
    memcpy_P(&led, (&g_is31_leds[index]), sizeof(led));

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

void IS31FL3737_update_pwm_buffers(uint8_t addr, uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        // Firstly we need to unlock the command register and select PG1
        IS31FL3737_write_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);
        IS31FL3737_write_register(addr, ISSI_COMMANDREGISTER, ISSI_PAGE_PWM);

        IS31FL3737_write_pwm_buffer(addr, g_pwm_buffer[index]);
    }
    g_pwm_buffer_update_required[index] = false;
}

void IS31FL3737_update_led_control_registers(uint8_t addr, uint8_t index) {
    if (g_led_control_registers_update_required[index]) {
        // Firstly we need to unlock the command register and select PG0
        IS31FL3737_write_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);
        IS31FL3737_write_register(addr, ISSI_COMMANDREGISTER, ISSI_PAGE_LEDCONTROL);
        for (int i = 0; i < 24; i++) {
            IS31FL3737_write_register(addr, i, g_led_control_registers[index][i]);
        }
    }
    g_led_control_registers_update_required[index] = false;
}
