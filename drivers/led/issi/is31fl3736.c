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

#include "is31fl3736.h"
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

#ifndef ISSI_GLOBALCURRENT
#    define ISSI_GLOBALCURRENT 0xFF
#endif

// Transfer buffer for TWITransmitData()
uint8_t g_twi_transfer_buffer[20];

// These buffers match the IS31FL3736 PWM registers.
// The control buffers match the PG0 LED On/Off registers.
// Storing them like this is optimal for I2C transfers to the registers.
// We could optimize this and take out the unused registers from these
// buffers and the transfers in IS31FL3736_write_pwm_buffer() but it's
// probably not worth the extra complexity.
uint8_t g_pwm_buffer[DRIVER_COUNT][192];
bool    g_pwm_buffer_update_required = false;

uint8_t g_led_control_registers[DRIVER_COUNT][24] = {{0}, {0}};
bool    g_led_control_registers_update_required   = false;

void IS31FL3736_write_register(uint8_t addr, uint8_t reg, uint8_t data) {
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

void IS31FL3736_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer) {
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

void IS31FL3736_init(uint8_t addr) {
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, shutdown is enabled last.
    // Set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.

    // Unlock the command register.
    IS31FL3736_write_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);

    // Select PG0
    IS31FL3736_write_register(addr, ISSI_COMMANDREGISTER, ISSI_PAGE_LEDCONTROL);
    // Turn off all LEDs.
    for (int i = 0x00; i <= 0x17; i++) {
        IS31FL3736_write_register(addr, i, 0x00);
    }

    // Unlock the command register.
    IS31FL3736_write_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);

    // Select PG1
    IS31FL3736_write_register(addr, ISSI_COMMANDREGISTER, ISSI_PAGE_PWM);
    // Set PWM on all LEDs to 0
    // No need to setup Breath registers to PWM as that is the default.
    for (int i = 0x00; i <= 0xBF; i++) {
        IS31FL3736_write_register(addr, i, 0x00);
    }

    // Unlock the command register.
    IS31FL3736_write_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);

    // Select PG3
    IS31FL3736_write_register(addr, ISSI_COMMANDREGISTER, ISSI_PAGE_FUNCTION);
    // Set de-ghost pull-up resistors (SWx)
    IS31FL3736_write_register(addr, ISSI_REG_SWPULLUP, ISSI_SWPULLUP);
    // Set de-ghost pull-down resistors (CSx)
    IS31FL3736_write_register(addr, ISSI_REG_CSPULLUP, ISSI_CSPULLUP);
    // Set global current to maximum.
    IS31FL3736_write_register(addr, ISSI_REG_GLOBALCURRENT, ISSI_GLOBALCURRENT);
    // Disable software shutdown.
    IS31FL3736_write_register(addr, ISSI_REG_CONFIGURATION, 0x01);

    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

void IS31FL3736_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    is31_led led;
    if (index >= 0 && index < RGB_MATRIX_LED_COUNT) {
        memcpy_P(&led, (&g_is31_leds[index]), sizeof(led));

        g_pwm_buffer[led.driver][led.r] = red;
        g_pwm_buffer[led.driver][led.g] = green;
        g_pwm_buffer[led.driver][led.b] = blue;
        g_pwm_buffer_update_required    = true;
    }
}

void IS31FL3736_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        IS31FL3736_set_color(i, red, green, blue);
    }
}

void IS31FL3736_set_led_control_register(uint8_t index, bool red, bool green, bool blue) {
    is31_led led;
    memcpy_P(&led, (&g_is31_leds[index]), sizeof(led));

    // IS31FL3733
    // The PWM register for a matrix position (0x00 to 0xBF) can be
    // divided by 8 to get the LED control register (0x00 to 0x17),
    // then mod 8 to get the bit position within that register.

    // IS31FL3736
    // The PWM register for a matrix position (0x00 to 0xBF) is interleaved, so:
    // A1=0x00 A2=0x02 A3=0x04 A4=0x06 A5=0x08 A6=0x0A A7=0x0C A8=0x0E
    // B1=0x10 B2=0x12 B3=0x14
    // But also, the LED control registers (0x00 to 0x17) are also interleaved, so:
    // A1-A4=0x00 A5-A8=0x01
    // So, the same math applies.

    uint8_t control_register_r = led.r / 8;
    uint8_t control_register_g = led.g / 8;
    uint8_t control_register_b = led.b / 8;

    uint8_t bit_r = led.r % 8;
    uint8_t bit_g = led.g % 8;
    uint8_t bit_b = led.b % 8;

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

    g_led_control_registers_update_required = true;
}

void IS31FL3736_mono_set_brightness(int index, uint8_t value) {
    if (index >= 0 && index < 96) {
        // Index in range 0..95 -> A1..A8, B1..B8, etc.
        // Map index 0..95 to registers 0x00..0xBE (interleaved)
        uint8_t pwm_register          = index * 2;
        g_pwm_buffer[0][pwm_register] = value;
        g_pwm_buffer_update_required  = true;
    }
}

void IS31FL3736_mono_set_brightness_all(uint8_t value) {
    for (int i = 0; i < 96; i++) {
        IS31FL3736_mono_set_brightness(i, value);
    }
}

void IS31FL3736_mono_set_led_control_register(uint8_t index, bool enabled) {
    // Index in range 0..95 -> A1..A8, B1..B8, etc.

    // Map index 0..95 to registers 0x00..0xBE (interleaved)
    uint8_t pwm_register = index * 2;
    // Map register 0x00..0xBE (interleaved) into control register and bit
    uint8_t control_register = pwm_register / 8;
    uint8_t bit              = pwm_register % 8;

    if (enabled) {
        g_led_control_registers[0][control_register] |= (1 << bit);
    } else {
        g_led_control_registers[0][control_register] &= ~(1 << bit);
    }

    g_led_control_registers_update_required = true;
}

void IS31FL3736_update_pwm_buffers(uint8_t addr1, uint8_t addr2) {
    if (g_pwm_buffer_update_required) {
        // Firstly we need to unlock the command register and select PG1
        IS31FL3736_write_register(addr1, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);
        IS31FL3736_write_register(addr1, ISSI_COMMANDREGISTER, ISSI_PAGE_PWM);

        IS31FL3736_write_pwm_buffer(addr1, g_pwm_buffer[0]);
        // IS31FL3736_write_pwm_buffer(addr2, g_pwm_buffer[1]);
    }
    g_pwm_buffer_update_required = false;
}

void IS31FL3736_update_led_control_registers(uint8_t addr1, uint8_t addr2) {
    if (g_led_control_registers_update_required) {
        // Firstly we need to unlock the command register and select PG0
        IS31FL3736_write_register(addr1, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);
        IS31FL3736_write_register(addr1, ISSI_COMMANDREGISTER, ISSI_PAGE_LEDCONTROL);
        for (int i = 0; i < 24; i++) {
            IS31FL3736_write_register(addr1, i, g_led_control_registers[0][i]);
            // IS31FL3736_write_register(addr2, i, g_led_control_registers[1][i]);
        }
        g_led_control_registers_update_required = false;
    }
}
