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

#include "is31fl3763.h"
#include "i2c_master.h"
#include "gpio.h"
#include "wait.h"

#define ISSI_ADDR_DEFAULT 0x6C

#define ISSI_COMMANDREGISTER 0xFE
#define ISSI_COMMANDREGISTER_WRITELOCK 0xFF
#define ISSI_INTERRUPTMASKREGISTER 0xF0
#define ISSI_INTERRUPTSTATUSREGISTER 0xF1

#define ISSI_PAGE_PWM 0x00         // PG0
#define ISSI_PAGE_PWM_CONTROL 0x01 // PG1

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

#ifndef ISSI_PWM_FREQUENCY
#    define ISSI_PWM_FREQUENCY 0b000
#endif

#ifndef ISSI_SWPULLUP
#    define ISSI_SWPULLUP PUR_0R
#endif

#ifndef ISSI_CSPULLUP
#    define ISSI_CSPULLUP PUR_0R
#endif

#ifndef ISSI_GLOBALCURRENT
#    define ISSI_GLOBALCURRENT 0x80
#endif

const uint8_t i2c_addresses[DRIVER_COUNT] = {
    DRIVER_ADDR_1,
    DRIVER_ADDR_2,
};

// Transfer buffer for TWITransmitData()
uint8_t g_twi_transfer_buffer[20];

// These buffers match the IS31FL3733 PWM registers.
// The control buffers match the PG0 LED On/Off registers.
// Storing them like this is optimal for I2C transfers to the registers.
// We could optimize this and take out the unused registers from these
// buffers and the transfers in is31fl3733_write_pwm_buffer() but it's
// probably not worth the extra complexity.
uint8_t g_pwm_buffer[DRIVER_COUNT][328];
bool    g_pwm_buffer_update_required[DRIVER_COUNT] = {false};

uint8_t g_led_control_registers[DRIVER_COUNT][24]             = {0};
bool    g_led_control_registers_update_required[DRIVER_COUNT] = {false};

// I2C
void is31fl3763_write_register(uint8_t index, uint8_t reg, uint8_t data) {
    // If the transaction fails function returns false.
#if ISSI_PERSISTENCE > 0
    for (uint8_t i = 0; i < ISSI_PERSISTENCE; i++) {
        if (i2c_write_register(i2c_addresses[index] << 1, reg, &data, 1, ISSI_TIMEOUT) != 0) {
            return false;
        }
    }
#else
    i2c_write_register(i2c_addresses[index] << 1, reg, &data, 1, ISSI_TIMEOUT);
#endif
}

uint8_t PWM_H_Tab[14][12] = {
    // sw  1   2    3    4    5     6   7    8    9    10   11   12
    {0x01, 0x02, 0x04, 0x05, 0x07, 0x08, 0x0A, 0x0B, 0X0D, 0X0E, 0X10, 0X11}, // CS01 | CS15
    {0X13, 0X14, 0X16, 0X17, 0X19, 0X1A, 0X1C, 0X1D, 0X1F, 0X20, 0X22, 0X23}, // CS02 | CS16
    {0X25, 0X26, 0X28, 0X29, 0X2B, 0X2C, 0X2E, 0X2F, 0X31, 0X32, 0X34, 0X35}, // CS03 | CS17
    {0X37, 0X38, 0X3A, 0X3B, 0X3D, 0X3E, 0X40, 0X41, 0X43, 0X44, 0X46, 0X47}, // CS04 | CS18
    {0X49, 0X4A, 0X4C, 0X4D, 0X4F, 0X50, 0X52, 0X53, 0X55, 0X56, 0X58, 0X59}, // CS05
    {0X5B, 0X5C, 0X5E, 0X5F, 0X61, 0X62, 0X64, 0X65, 0X67, 0X68, 0X6A, 0X6B}, // CS06
    {0X6D, 0X6E, 0X70, 0X71, 0X73, 0X74, 0X76, 0X77, 0X79, 0X7A, 0X7C, 0X7D}, // CS07
    {0X7F, 0X80, 0X82, 0X83, 0X85, 0X86, 0X88, 0X89, 0X8B, 0X8C, 0X8E, 0X8F}, // CS08
    {0x91, 0x92, 0x94, 0x95, 0x97, 0x98, 0x9A, 0x9B, 0X9D, 0X9E, 0XA0, 0XA1}, // CS09
    {0XA3, 0XA4, 0XA6, 0XA7, 0XA9, 0XAA, 0XAC, 0XAD, 0XAF, 0XB0, 0XB2, 0XB3}, // CS10
    {0XB5, 0XB6, 0XB8, 0XB9, 0XBB, 0XBC, 0XBE, 0XBF, 0XC1, 0XC2, 0XC4, 0XC5}, // CS11
    {0XC7, 0XC8, 0XCA, 0XCB, 0XCD, 0XCE, 0XD0, 0XD1, 0XD3, 0XD4, 0XD6, 0XD7}, // CS12
    {0XD9, 0XDA, 0XDC, 0XDD, 0XDF, 0XE0, 0XE2, 0XE3, 0XE5, 0XE6, 0XE8, 0XE9}, // CS13
    {0XEB, 0XEC, 0XEE, 0XEF, 0XF1, 0XF2, 0XF4, 0XF5, 0XF7, 0XF8, 0XFA, 0XFB}  // CS14
};

void is31fl3763_write_pwm_buffer(uint8_t index) {
    uint16_t addr_sart = 0;

    for (int i = 0; i < 18; i += 1) {
        if (i >= 14) {
            is31fl3763_write_register(index, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);
            is31fl3763_write_register(index, ISSI_COMMANDREGISTER, ISSI_PAGE_PWM_CONTROL);

            addr_sart = ((i - 14) * 18);

            i2c_write_register(i2c_addresses[index] << 1, addr_sart, &g_pwm_buffer[index][(addr_sart | 0X100)], 18, ISSI_TIMEOUT);

        } else {
            is31fl3763_write_register(index, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);
            is31fl3763_write_register(index, ISSI_COMMANDREGISTER, ISSI_PAGE_PWM);

            addr_sart = (i * 18);

            i2c_write_register(i2c_addresses[index] << 1, addr_sart, &g_pwm_buffer[index][(addr_sart)], 18, ISSI_TIMEOUT);
        }
    }

    is31fl3763_write_register(index, 0xFD, 0x00);
}

void is31fl3763_init_drivers(void) {
    i2c_init();

    for (uint8_t i = 0; i < DRIVER_COUNT; i++) {
        is31fl3763_init(i);
    }

    for (int i = 0; i < DRIVER_COUNT; i++) {
        is31fl3763_set_led_control_register(i, true, true, true);
    }

    for (uint8_t i = 0; i < DRIVER_COUNT; i++) {
        is31fl3763_update_led_control_registers(i);
    }
}

void is31fl3763_init(uint8_t index) {
    uint8_t i, j;

    // Unlock the command register.
    is31fl3763_write_register(index, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);
    is31fl3763_write_register(index, ISSI_COMMANDREGISTER, ISSI_PAGE_PWM);

    // Turn off all LEDs.
    for (i = 0; i < 14; i++) {
        for (j = 0; j < 12; j++) {
            is31fl3763_write_register(index, PWM_H_Tab[i][j], 0X00);
        }
    }

    // Unlock the command register.
    is31fl3763_write_register(index, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);
    is31fl3763_write_register(index, ISSI_COMMANDREGISTER, ISSI_PAGE_PWM_CONTROL);

    // Turn off all LEDs.
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 12; j++) {
            is31fl3763_write_register(index, PWM_H_Tab[i][j], 0X00);
        }
    }

    // Unlock the command register.
    is31fl3763_write_register(index, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);
    // Select PG1
    is31fl3763_write_register(index, ISSI_COMMANDREGISTER, ISSI_PAGE_PWM_CONTROL);
    // Set de-ghost pull-up resistors (SWx)(CSx)
    is31fl3763_write_register(index, 0x62, 0x66); //
    // Set global current to maximum.
    is31fl3763_write_register(index, 0x61, ISSI_GLOBALCURRENT);
    // Disable software shutdown.
    is31fl3763_write_register(index, 0x60, 0x09);

    is31fl3763_write_register(index, 0x63, 0x00);

    uint8_t SL_Set;
    for (SL_Set = 0x49; SL_Set <= 0x5A; SL_Set++) {
        is31fl3763_write_register(index, SL_Set, 0x80);
    }
    is31fl3763_write_register(index, 0xFD, 0x00); // update

    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

void is31fl3763_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    is31_led led;
    if (index >= 0 && index < RGB_MATRIX_LED_COUNT) {
        memcpy_P(&led, (&g_is31_leds[index]), sizeof(led));

        g_pwm_buffer[led.driver][led.r]          = red;
        g_pwm_buffer[led.driver][led.g]          = green;
        g_pwm_buffer[led.driver][led.b]          = blue;
        g_pwm_buffer_update_required[led.driver] = true;
    }
}

void is31fl3763_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        is31fl3763_set_color(i, red, green, blue);
    }
}

void is31fl3763_set_led_control_register(uint8_t index, bool red, bool green, bool blue) {
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

void is31fl3763_update_pwm_buffers(uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        // Firstly we need to unlock the command register and select PG1.
        is31fl3763_write_register(index, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);
        is31fl3763_write_register(index, ISSI_COMMANDREGISTER, ISSI_PAGE_PWM);

        is31fl3763_write_pwm_buffer(index);

        g_pwm_buffer_update_required[index] = false;
    }
}

void is31fl3763_update_led_control_registers(uint8_t index) {
    if (g_led_control_registers_update_required[index]) {
        // Firstly we need to unlock the command register and select PG0
        is31fl3763_write_register(index, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);
        is31fl3763_write_register(index, ISSI_COMMANDREGISTER, 0x01);
        for (int i = 0; i < 24; i++) {
            is31fl3763_write_register(index, i, g_led_control_registers[index][i]);
        }
    }
    g_led_control_registers_update_required[index] = false;
}

void is31fl3763_flush(void) {
    for (uint8_t i = 0; i < DRIVER_COUNT; i++) {
        is31fl3763_update_pwm_buffers(i);
    }
}
