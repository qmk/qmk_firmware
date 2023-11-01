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

#include "is31fl3741.h"
#include <string.h>
#include "i2c_master.h"
#include "wait.h"

#define IS31FL3741_COMMANDREGISTER 0xFD
#define IS31FL3741_COMMANDREGISTER_WRITELOCK 0xFE
#define IS31FL3741_INTERRUPTMASKREGISTER 0xF0
#define IS31FL3741_INTERRUPTSTATUSREGISTER 0xF1
#define IS31FL3741_IDREGISTER 0xFC

#define IS31FL3741_PAGE_PWM0 0x00      // PG0
#define IS31FL3741_PAGE_PWM1 0x01      // PG1
#define IS31FL3741_PAGE_SCALING_0 0x02 // PG2
#define IS31FL3741_PAGE_SCALING_1 0x03 // PG3
#define IS31FL3741_PAGE_FUNCTION 0x04  // PG4

#define IS31FL3741_REG_CONFIGURATION 0x00 // PG4
#define IS31FL3741_REG_GLOBALCURRENT 0x01 // PG4
#define IS31FL3741_REG_PULLDOWNUP 0x02    // PG4
#define IS31FL3741_REG_PWM_FREQUENCY 0x36 // PG4
#define IS31FL3741_REG_RESET 0x3F         // PG4

#define IS31FL3741_PWM_REGISTER_COUNT 351

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

#ifndef IS31FL3741_SWPULLUP
#    define IS31FL3741_SWPULLUP IS31FL3741_PUR_32KR
#endif

#ifndef IS31FL3741_CSPULLUP
#    define IS31FL3741_CSPULLUP IS31FL3741_PUR_32KR
#endif

#ifndef IS31FL3741_GLOBALCURRENT
#    define IS31FL3741_GLOBALCURRENT 0xFF
#endif

// Transfer buffer for TWITransmitData()
uint8_t g_twi_transfer_buffer[20] = {0xFF};

// These buffers match the IS31FL3741 and IS31FL3741A PWM registers.
// The scaling buffers match the PG2 and PG3 LED On/Off registers.
// Storing them like this is optimal for I2C transfers to the registers.
// We could optimize this and take out the unused registers from these
// buffers and the transfers in is31fl3741_write_pwm_buffer() but it's
// probably not worth the extra complexity.
uint8_t g_pwm_buffer[IS31FL3741_DRIVER_COUNT][IS31FL3741_PWM_REGISTER_COUNT];
bool    g_pwm_buffer_update_required[IS31FL3741_DRIVER_COUNT]        = {false};
bool    g_scaling_registers_update_required[IS31FL3741_DRIVER_COUNT] = {false};

uint8_t g_scaling_registers[IS31FL3741_DRIVER_COUNT][IS31FL3741_PWM_REGISTER_COUNT];

void is31fl3741_write_register(uint8_t addr, uint8_t reg, uint8_t data) {
    g_twi_transfer_buffer[0] = reg;
    g_twi_transfer_buffer[1] = data;

#if IS31FL3741_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3741_I2C_PERSISTENCE; i++) {
        if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 2, IS31FL3741_I2C_TIMEOUT) == 0) break;
    }
#else
    i2c_transmit(addr << 1, g_twi_transfer_buffer, 2, IS31FL3741_I2C_TIMEOUT);
#endif
}

bool is31fl3741_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer) {
    // Assume PG0 is already selected

    for (int i = 0; i < 342; i += 18) {
        if (i == 180) {
            // unlock the command register and select PG1
            is31fl3741_write_register(addr, IS31FL3741_COMMANDREGISTER_WRITELOCK, 0xC5);
            is31fl3741_write_register(addr, IS31FL3741_COMMANDREGISTER, IS31FL3741_PAGE_PWM1);
        }

        g_twi_transfer_buffer[0] = i % 180;
        memcpy(g_twi_transfer_buffer + 1, pwm_buffer + i, 18);

#if IS31FL3741_I2C_PERSISTENCE > 0
        for (uint8_t i = 0; i < IS31FL3741_I2C_PERSISTENCE; i++) {
            if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 19, IS31FL3741_I2C_TIMEOUT) != 0) {
                return false;
            }
        }
#else
        if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 19, IS31FL3741_I2C_TIMEOUT) != 0) {
            return false;
        }
#endif
    }

    // transfer the left cause the total number is 351
    g_twi_transfer_buffer[0] = 162;
    memcpy(g_twi_transfer_buffer + 1, pwm_buffer + 342, 9);

#if IS31FL3741_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3741_I2C_PERSISTENCE; i++) {
        if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 10, IS31FL3741_I2C_TIMEOUT) != 0) {
            return false;
        }
    }
#else
    if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 10, IS31FL3741_I2C_TIMEOUT) != 0) {
        return false;
    }
#endif

    return true;
}

void is31fl3741_init_drivers(void) {
    i2c_init();

    is31fl3741_init(IS31FL3741_I2C_ADDRESS_1);
#if defined(IS31FL3741_I2C_ADDRESS_2)
    is31fl3741_init(IS31FL3741_I2C_ADDRESS_2);
#    if defined(IS31FL3741_I2C_ADDRESS_3)
    is31fl3741_init(IS31FL3741_I2C_ADDRESS_3);
#        if defined(IS31FL3741_I2C_ADDRESS_4)
    is31fl3741_init(IS31FL3741_I2C_ADDRESS_4);
#        endif
#    endif
#endif

    for (int i = 0; i < IS31FL3741_LED_COUNT; i++) {
        is31fl3741_set_led_control_register(i, true, true, true);
    }

    is31fl3741_update_led_control_registers(IS31FL3741_I2C_ADDRESS_1, 0);
#if defined(IS31FL3741_I2C_ADDRESS_2)
    is31fl3741_update_led_control_registers(IS31FL3741_I2C_ADDRESS_2, 1);
#    if defined(IS31FL3741_I2C_ADDRESS_3)
    is31fl3741_update_led_control_registers(IS31FL3741_I2C_ADDRESS_3, 2);
#        if defined(IS31FL3741_I2C_ADDRESS_4)
    is31fl3741_update_led_control_registers(IS31FL3741_I2C_ADDRESS_4, 3);
#        endif
#    endif
#endif
}

void is31fl3741_init(uint8_t addr) {
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, shutdown is enabled last.
    // Set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.
    // Unlock the command register.

    // Unlock the command register.
    is31fl3741_write_register(addr, IS31FL3741_COMMANDREGISTER_WRITELOCK, 0xC5);

    // Select PG4
    is31fl3741_write_register(addr, IS31FL3741_COMMANDREGISTER, IS31FL3741_PAGE_FUNCTION);

    // Set to Normal operation
    is31fl3741_write_register(addr, IS31FL3741_REG_CONFIGURATION, IS31FL3741_CONFIGURATION);

    // Set Golbal Current Control Register
    is31fl3741_write_register(addr, IS31FL3741_REG_GLOBALCURRENT, IS31FL3741_GLOBALCURRENT);
    // Set Pull up & Down for SWx CSy
    is31fl3741_write_register(addr, IS31FL3741_REG_PULLDOWNUP, ((IS31FL3741_CSPULLUP << 4) | IS31FL3741_SWPULLUP));
    // Set PWM frequency
    is31fl3741_write_register(addr, IS31FL3741_REG_PWM_FREQUENCY, (IS31FL3741_PWM_FREQUENCY & 0b1111));

    // is31fl3741_update_led_scaling_registers(addr, 0xFF, 0xFF, 0xFF);

    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

void is31fl3741_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    is31fl3741_led_t led;
    if (index >= 0 && index < IS31FL3741_LED_COUNT) {
        memcpy_P(&led, (&g_is31fl3741_leds[index]), sizeof(led));

        if (g_pwm_buffer[led.driver][led.r] == red && g_pwm_buffer[led.driver][led.g] == green && g_pwm_buffer[led.driver][led.b] == blue) {
            return;
        }
        g_pwm_buffer_update_required[led.driver] = true;
        g_pwm_buffer[led.driver][led.r]          = red;
        g_pwm_buffer[led.driver][led.g]          = green;
        g_pwm_buffer[led.driver][led.b]          = blue;
    }
}

void is31fl3741_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < IS31FL3741_LED_COUNT; i++) {
        is31fl3741_set_color(i, red, green, blue);
    }
}

void is31fl3741_set_led_control_register(uint8_t index, bool red, bool green, bool blue) {
    is31fl3741_led_t led;
    memcpy_P(&led, (&g_is31fl3741_leds[index]), sizeof(led));

    if (red) {
        g_scaling_registers[led.driver][led.r] = 0xFF;
    } else {
        g_scaling_registers[led.driver][led.r] = 0x00;
    }

    if (green) {
        g_scaling_registers[led.driver][led.g] = 0xFF;
    } else {
        g_scaling_registers[led.driver][led.g] = 0x00;
    }

    if (blue) {
        g_scaling_registers[led.driver][led.b] = 0xFF;
    } else {
        g_scaling_registers[led.driver][led.b] = 0x00;
    }

    g_scaling_registers_update_required[led.driver] = true;
}

void is31fl3741_update_pwm_buffers(uint8_t addr, uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        // unlock the command register and select PG2
        is31fl3741_write_register(addr, IS31FL3741_COMMANDREGISTER_WRITELOCK, 0xC5);
        is31fl3741_write_register(addr, IS31FL3741_COMMANDREGISTER, IS31FL3741_PAGE_PWM0);

        is31fl3741_write_pwm_buffer(addr, g_pwm_buffer[index]);
    }

    g_pwm_buffer_update_required[index] = false;
}

void is31fl3741_set_pwm_buffer(const is31fl3741_led_t *pled, uint8_t red, uint8_t green, uint8_t blue) {
    g_pwm_buffer[pled->driver][pled->r] = red;
    g_pwm_buffer[pled->driver][pled->g] = green;
    g_pwm_buffer[pled->driver][pled->b] = blue;

    g_pwm_buffer_update_required[pled->driver] = true;
}

void is31fl3741_update_led_control_registers(uint8_t addr, uint8_t index) {
    if (g_scaling_registers_update_required[index]) {
        // unlock the command register and select PG2
        is31fl3741_write_register(addr, IS31FL3741_COMMANDREGISTER_WRITELOCK, 0xC5);
        is31fl3741_write_register(addr, IS31FL3741_COMMANDREGISTER, IS31FL3741_PAGE_SCALING_0);

        // CS1_SW1 to CS30_SW6 are on PG2
        for (int i = CS1_SW1; i <= CS30_SW6; ++i) {
            is31fl3741_write_register(addr, i, g_scaling_registers[index][i]);
        }

        // unlock the command register and select PG3
        is31fl3741_write_register(addr, IS31FL3741_COMMANDREGISTER_WRITELOCK, 0xC5);
        is31fl3741_write_register(addr, IS31FL3741_COMMANDREGISTER, IS31FL3741_PAGE_SCALING_1);

        // CS1_SW7 to CS39_SW9 are on PG3
        for (int i = CS1_SW7; i <= CS39_SW9; ++i) {
            is31fl3741_write_register(addr, i - CS1_SW7, g_scaling_registers[index][i]);
        }

        g_scaling_registers_update_required[index] = false;
    }
}

void is31fl3741_set_scaling_registers(const is31fl3741_led_t *pled, uint8_t red, uint8_t green, uint8_t blue) {
    g_scaling_registers[pled->driver][pled->r] = red;
    g_scaling_registers[pled->driver][pled->g] = green;
    g_scaling_registers[pled->driver][pled->b] = blue;

    g_scaling_registers_update_required[pled->driver] = true;
}

void is31fl3741_flush(void) {
    is31fl3741_update_pwm_buffers(IS31FL3741_I2C_ADDRESS_1, 0);
#if defined(IS31FL3741_I2C_ADDRESS_2)
    is31fl3741_update_pwm_buffers(IS31FL3741_I2C_ADDRESS_2, 1);
#    if defined(IS31FL3741_I2C_ADDRESS_3)
    is31fl3741_update_pwm_buffers(IS31FL3741_I2C_ADDRESS_3, 2);
#        if defined(IS31FL3741_I2C_ADDRESS_4)
    is31fl3741_update_pwm_buffers(IS31FL3741_I2C_ADDRESS_4, 3);
#        endif
#    endif
#endif
}
