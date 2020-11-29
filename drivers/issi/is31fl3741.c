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

#include "wait.h"

#include "is31fl3741.h"
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
// ADDR1 represents A1:A0 of the 7-bit address.
// ADDR2 represents A3:A2 of the 7-bit address.
// The result is: 0b101(ADDR2)(ADDR1)
#define ISSI_ADDR_DEFAULT 0x60

#define ISSI_COMMANDREGISTER 0xFD
#define ISSI_COMMANDREGISTER_WRITELOCK 0xFE
#define ISSI_INTERRUPTMASKREGISTER 0xF0
#define ISSI_INTERRUPTSTATUSREGISTER 0xF1
#define ISSI_IDREGISTER 0xFC

#define ISSI_PAGE_PWM0 0x00       // PG0
#define ISSI_PAGE_PWM1 0x01       // PG1
#define ISSI_PAGE_SCALING_0 0x02  // PG2
#define ISSI_PAGE_SCALING_1 0x03  // PG3
#define ISSI_PAGE_FUNCTION 0x04   // PG4

#define ISSI_REG_CONFIGURATION 0x00  // PG4
#define ISSI_REG_GLOBALCURRENT 0x01  // PG4
#define ISSI_REG_PULLDOWNUP 0x02     // PG4
#define ISSI_REG_RESET 0x3F          // PG4

#ifndef ISSI_TIMEOUT
#    define ISSI_TIMEOUT 100
#endif

#ifndef ISSI_PERSISTENCE
#    define ISSI_PERSISTENCE 0
#endif

#define ISSI_MAX_LEDS 351

// Transfer buffer for TWITransmitData()
uint8_t g_twi_transfer_buffer[20] = {0xFF};

// These buffers match the IS31FL3741 and IS31FL3741A PWM registers.
// The scaling buffers match the PG2 and PG3 LED On/Off registers.
// Storing them like this is optimal for I2C transfers to the registers.
// We could optimize this and take out the unused registers from these
// buffers and the transfers in IS31FL3741_write_pwm_buffer() but it's
// probably not worth the extra complexity.
uint8_t g_pwm_buffer[DRIVER_COUNT][ISSI_MAX_LEDS];
bool    g_pwm_buffer_update_required                      = false;
bool    g_scaling_registers_update_required[DRIVER_COUNT] = {false};

uint8_t g_scaling_registers[DRIVER_COUNT][ISSI_MAX_LEDS];

uint32_t IS31FL3741_get_cw_sw_position(uint8_t cs, uint8_t sw) {
    uint32_t pos = 0;

    if (cs < 31) {
        if (sw < 7) {
            pos = (sw - 1) * 30 + (cs - 1);

        } else {
            pos = 0xB4 + (sw - 7) * 30 + (cs - 1);
        }
    } else {
        pos = 0xB4 + 0x5A + (sw - 1) * 9 + (cs - 31);
    }

    return pos;
}

void IS31FL3741_write_register(uint8_t addr, uint8_t reg, uint8_t data) {
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

bool IS31FL3741_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer) {
    // unlock the command register and select PG2
    IS31FL3741_write_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);
    IS31FL3741_write_register(addr, ISSI_COMMANDREGISTER, ISSI_PAGE_PWM0);

    for (int i = 0; i < 342; i += 18) {
        g_twi_transfer_buffer[0] = i % 180;

        if (i == 180) {
            // unlock the command register and select PG2
            IS31FL3741_write_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);
            IS31FL3741_write_register(addr, ISSI_COMMANDREGISTER, ISSI_PAGE_PWM1);
        }

        memcpy(g_twi_transfer_buffer + 1, pwm_buffer + i, 18);

#if ISSI_PERSISTENCE > 0
        for (uint8_t i = 0; i < ISSI_PERSISTENCE; i++) {
            if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 19, ISSI_TIMEOUT) != 0) {
                return false;
            }
        }
#else
        if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 19, ISSI_TIMEOUT) != 0) {
            return false;
        }
#endif
    }

    // transfer the left cause the total number is 351
    g_twi_transfer_buffer[0] = 162;
    memcpy(g_twi_transfer_buffer + 1, pwm_buffer + 342, 9);

#if ISSI_PERSISTENCE > 0
    for (uint8_t i = 0; i < ISSI_PERSISTENCE; i++) {
        if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 10, ISSI_TIMEOUT) != 0) {
            return false;
        }
    }
#else
    if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 10, ISSI_TIMEOUT) != 0) {
        return false;
    }
#endif

    return true;
}

void IS31FL3741_init(uint8_t addr) {
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, shutdown is enabled last.
    // Set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.
    // Unlock the command register.

    // Unlock the command register.
    IS31FL3741_write_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);

    // Select PG4
    IS31FL3741_write_register(addr, ISSI_COMMANDREGISTER, ISSI_PAGE_FUNCTION);

    // Set to Normal operation
    IS31FL3741_write_register(addr, ISSI_REG_CONFIGURATION, 0x01);

    // Set Golbal Current Control Register
    IS31FL3741_write_register(addr, ISSI_REG_GLOBALCURRENT, 0xFF);
    // Set Pull up & Down for SWx CSy
    IS31FL3741_write_register(addr, ISSI_REG_PULLDOWNUP, 0x77);

    // IS31FL3741_update_led_scaling_registers(addr, 0xFF, 0xFF, 0xFF);

    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

void IS31FL3741_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index >= 0 && index < DRIVER_LED_TOTAL) {
        is31_led led = g_is31_leds[index];
        uint32_t rp = 0, gp = 0, bp = 0;

        rp = IS31FL3741_get_cw_sw_position(led.rcs, led.rsw);
        gp = IS31FL3741_get_cw_sw_position(led.gcs, led.gsw);
        bp = IS31FL3741_get_cw_sw_position(led.bcs, led.bsw);

        g_pwm_buffer[led.driver][rp] = red;
        g_pwm_buffer[led.driver][gp] = green;
        g_pwm_buffer[led.driver][bp] = blue;
        g_pwm_buffer_update_required = true;
    }
}

void IS31FL3741_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        IS31FL3741_set_color(i, red, green, blue);
    }
}

void IS31FL3741_set_led_control_register(uint8_t index, bool red, bool green, bool blue) {
    is31_led led = g_is31_leds[index];

    uint32_t scaling_register_r = IS31FL3741_get_cw_sw_position(led.rcs, led.rsw);
    uint32_t scaling_register_g = IS31FL3741_get_cw_sw_position(led.gcs, led.gsw);
    uint32_t scaling_register_b = IS31FL3741_get_cw_sw_position(led.bcs, led.bsw);

    if (red) {
        g_scaling_registers[led.driver][scaling_register_r] = 0xFF;
    } else {
        g_scaling_registers[led.driver][scaling_register_r] = 0x00;
    }

    if (green) {
        g_scaling_registers[led.driver][scaling_register_g] = 0xFF;
    } else {
        g_scaling_registers[led.driver][scaling_register_g] = 0x00;
    }

    if (blue) {
        g_scaling_registers[led.driver][scaling_register_b] = 0xFF;
    } else {
        g_scaling_registers[led.driver][scaling_register_b] = 0x00;
    }

    g_scaling_registers_update_required[led.driver] = true;
}

void IS31FL3741_update_pwm_buffers(uint8_t addr1, uint8_t addr2) {
    if (g_pwm_buffer_update_required) {
        IS31FL3741_write_pwm_buffer(addr1, g_pwm_buffer[0]);
    }

    g_pwm_buffer_update_required = false;
}

void IS31FL3741_set_pwm_buffer(const is31_led *pled, uint8_t red, uint8_t green, uint8_t blue) {
    uint32_t rp = 0, gp = 0, bp = 0;

    rp = IS31FL3741_get_cw_sw_position(pled->rcs, pled->rsw);
    gp = IS31FL3741_get_cw_sw_position(pled->gcs, pled->gsw);
    bp = IS31FL3741_get_cw_sw_position(pled->bcs, pled->bsw);

    g_pwm_buffer[pled->driver][rp] = red;
    g_pwm_buffer[pled->driver][gp] = green;
    g_pwm_buffer[pled->driver][bp] = blue;

    g_pwm_buffer_update_required = true;
}

void IS31FL3741_update_led_control_registers(uint8_t addr, uint8_t index) {
    if (g_scaling_registers_update_required[index]) {
        // unlock the command register and select PG2
        IS31FL3741_write_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);
        IS31FL3741_write_register(addr, ISSI_COMMANDREGISTER, ISSI_PAGE_SCALING_0);

        for (int i = 0; i < 180; ++i) {
            IS31FL3741_write_register(addr, i, g_scaling_registers[0][i]);
        }

        // unlock the command register and select PG3
        IS31FL3741_write_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5);
        IS31FL3741_write_register(addr, ISSI_COMMANDREGISTER, ISSI_PAGE_SCALING_1);

        for (int i = 0; i < 171; ++i) {
            IS31FL3741_write_register(addr, i, g_scaling_registers[0][180 + i]);
        }

        g_scaling_registers_update_required[index] = false;
    }
}

void IS31FL3741_set_scaling_registers(const is31_led *pled, uint8_t red, uint8_t green, uint8_t blue) {
    uint32_t rp = 0, gp = 0, bp = 0;

    rp = IS31FL3741_get_cw_sw_position(pled->rcs, pled->rsw);
    gp = IS31FL3741_get_cw_sw_position(pled->gcs, pled->gsw);
    bp = IS31FL3741_get_cw_sw_position(pled->bcs, pled->bsw);

    g_scaling_registers[pled->driver][rp] = red;
    g_scaling_registers[pled->driver][gp] = green;
    g_scaling_registers[pled->driver][bp] = blue;
}
