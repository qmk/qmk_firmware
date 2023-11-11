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

#include "is31fl3736-simple.h"
#include <string.h>
#include "i2c_master.h"
#include "wait.h"

#define IS31FL3736_COMMANDREGISTER 0xFD
#define IS31FL3736_COMMANDREGISTER_WRITELOCK 0xFE
#define IS31FL3736_INTERRUPTMASKREGISTER 0xF0
#define IS31FL3736_INTERRUPTSTATUSREGISTER 0xF1

#define IS31FL3736_PAGE_LEDCONTROL 0x00 // PG0
#define IS31FL3736_PAGE_PWM 0x01        // PG1
#define IS31FL3736_PAGE_AUTOBREATH 0x02 // PG2
#define IS31FL3736_PAGE_FUNCTION 0x03   // PG3

#define IS31FL3736_REG_CONFIGURATION 0x00 // PG3
#define IS31FL3736_REG_GLOBALCURRENT 0x01 // PG3
#define IS31FL3736_REG_RESET 0x11         // PG3
#define IS31FL3736_REG_SW_PULLUP 0x0F     // PG3
#define IS31FL3736_REG_CS_PULLDOWN 0x10   // PG3

#define IS31FL3736_PWM_REGISTER_COUNT 192 // actually 96
#define IS31FL3736_LED_CONTROL_REGISTER_COUNT 24

#ifndef IS31FL3736_I2C_TIMEOUT
#    define IS31FL3736_I2C_TIMEOUT 100
#endif

#ifndef IS31FL3736_I2C_PERSISTENCE
#    define IS31FL3736_I2C_PERSISTENCE 0
#endif

#ifndef IS31FL3736_PWM_FREQUENCY
#    define IS31FL3736_PWM_FREQUENCY IS31FL3736_PWM_FREQUENCY_8K4_HZ // PFS - IS31FL3736B only
#endif

#ifndef IS31FL3736_SW_PULLUP
#    define IS31FL3736_SW_PULLUP IS31FL3736_PUR_0_OHM
#endif

#ifndef IS31FL3736_CS_PULLDOWN
#    define IS31FL3736_CS_PULLDOWN IS31FL3736_PDR_0_OHM
#endif

#ifndef IS31FL3736_GLOBALCURRENT
#    define IS31FL3736_GLOBALCURRENT 0xFF
#endif

// Transfer buffer for TWITransmitData()
uint8_t g_twi_transfer_buffer[20];

// These buffers match the IS31FL3736 PWM registers.
// The control buffers match the PG0 LED On/Off registers.
// Storing them like this is optimal for I2C transfers to the registers.
// We could optimize this and take out the unused registers from these
// buffers and the transfers in is31fl3736_write_pwm_buffer() but it's
// probably not worth the extra complexity.
uint8_t g_pwm_buffer[IS31FL3736_DRIVER_COUNT][IS31FL3736_PWM_REGISTER_COUNT];
bool    g_pwm_buffer_update_required[IS31FL3736_DRIVER_COUNT] = {false};

uint8_t g_led_control_registers[IS31FL3736_DRIVER_COUNT][IS31FL3736_LED_CONTROL_REGISTER_COUNT] = {0};
bool    g_led_control_registers_update_required[IS31FL3736_DRIVER_COUNT]                        = {false};

void is31fl3736_write_register(uint8_t addr, uint8_t reg, uint8_t data) {
    g_twi_transfer_buffer[0] = reg;
    g_twi_transfer_buffer[1] = data;

#if IS31FL3736_I2C_PERSISTENCE > 0
    for (uint8_t i = 0; i < IS31FL3736_I2C_PERSISTENCE; i++) {
        if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 2, IS31FL3736_I2C_TIMEOUT) == 0) break;
    }
#else
    i2c_transmit(addr << 1, g_twi_transfer_buffer, 2, IS31FL3736_I2C_TIMEOUT);
#endif
}

void is31fl3736_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer) {
    // assumes PG1 is already selected

    // transmit PWM registers in 12 transfers of 16 bytes
    // g_twi_transfer_buffer[] is 20 bytes

    // iterate over the pwm_buffer contents at 16 byte intervals
    for (int i = 0; i < IS31FL3736_PWM_REGISTER_COUNT; i += 16) {
        g_twi_transfer_buffer[0] = i;
        // copy the data from i to i+15
        // device will auto-increment register for data after the first byte
        // thus this sets registers 0x00-0x0F, 0x10-0x1F, etc. in one transfer
        memcpy(g_twi_transfer_buffer + 1, pwm_buffer + i, 16);

#if IS31FL3736_I2C_PERSISTENCE > 0
        for (uint8_t i = 0; i < IS31FL3736_I2C_PERSISTENCE; i++) {
            if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 17, IS31FL3736_I2C_TIMEOUT) == 0) break;
        }
#else
        i2c_transmit(addr << 1, g_twi_transfer_buffer, 17, IS31FL3736_I2C_TIMEOUT);
#endif
    }
}

void is31fl3736_init_drivers(void) {
    i2c_init();

    is31fl3736_init(IS31FL3736_I2C_ADDRESS_1);
#if defined(IS31FL3736_I2C_ADDRESS_2)
    is31fl3736_init(IS31FL3736_I2C_ADDRESS_2);
#    if defined(IS31FL3736_I2C_ADDRESS_3)
    is31fl3736_init(IS31FL3736_I2C_ADDRESS_3);
#        if defined(IS31FL3736_I2C_ADDRESS_4)
    is31fl3736_init(IS31FL3736_I2C_ADDRESS_4);
#        endif
#    endif
#endif

    for (int i = 0; i < IS31FL3736_LED_COUNT; i++) {
        is31fl3736_set_led_control_register(i, true);
    }

    is31fl3736_update_led_control_registers(IS31FL3736_I2C_ADDRESS_1, 0);
#if defined(IS31FL3736_I2C_ADDRESS_2)
    is31fl3736_update_led_control_registers(IS31FL3736_I2C_ADDRESS_2, 1);
#    if defined(IS31FL3736_I2C_ADDRESS_3)
    is31fl3736_update_led_control_registers(IS31FL3736_I2C_ADDRESS_3, 2);
#        if defined(IS31FL3736_I2C_ADDRESS_4)
    is31fl3736_update_led_control_registers(IS31FL3736_I2C_ADDRESS_4, 3);
#        endif
#    endif
#endif
}

void is31fl3736_init(uint8_t addr) {
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, shutdown is enabled last.
    // Set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.

    // Unlock the command register.
    is31fl3736_write_register(addr, IS31FL3736_COMMANDREGISTER_WRITELOCK, 0xC5);

    // Select PG0
    is31fl3736_write_register(addr, IS31FL3736_COMMANDREGISTER, IS31FL3736_PAGE_LEDCONTROL);
    // Turn off all LEDs.
    for (int i = 0; i < IS31FL3736_LED_CONTROL_REGISTER_COUNT; i++) {
        is31fl3736_write_register(addr, i, 0x00);
    }

    // Unlock the command register.
    is31fl3736_write_register(addr, IS31FL3736_COMMANDREGISTER_WRITELOCK, 0xC5);

    // Select PG1
    is31fl3736_write_register(addr, IS31FL3736_COMMANDREGISTER, IS31FL3736_PAGE_PWM);
    // Set PWM on all LEDs to 0
    // No need to setup Breath registers to PWM as that is the default.
    for (int i = 0; i < IS31FL3736_PWM_REGISTER_COUNT; i++) {
        is31fl3736_write_register(addr, i, 0x00);
    }

    // Unlock the command register.
    is31fl3736_write_register(addr, IS31FL3736_COMMANDREGISTER_WRITELOCK, 0xC5);

    // Select PG3
    is31fl3736_write_register(addr, IS31FL3736_COMMANDREGISTER, IS31FL3736_PAGE_FUNCTION);
    // Set de-ghost pull-up resistors (SWx)
    is31fl3736_write_register(addr, IS31FL3736_REG_SW_PULLUP, IS31FL3736_SW_PULLUP);
    // Set de-ghost pull-down resistors (CSx)
    is31fl3736_write_register(addr, IS31FL3736_REG_CS_PULLDOWN, IS31FL3736_CS_PULLDOWN);
    // Set global current to maximum.
    is31fl3736_write_register(addr, IS31FL3736_REG_GLOBALCURRENT, IS31FL3736_GLOBALCURRENT);
    // Disable software shutdown.
    is31fl3736_write_register(addr, IS31FL3736_REG_CONFIGURATION, ((IS31FL3736_PWM_FREQUENCY & 0b111) << 3) | 0x01);

    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

void is31fl3736_set_value(int index, uint8_t value) {
    is31fl3736_led_t led;
    if (index >= 0 && index < IS31FL3736_LED_COUNT) {
        memcpy_P(&led, (&g_is31fl3736_leds[index]), sizeof(led));

        if (g_pwm_buffer[led.driver][led.v] == value) {
            return;
        }
        g_pwm_buffer[led.driver][led.v]          = value;
        g_pwm_buffer_update_required[led.driver] = true;
    }
}

void is31fl3736_set_value_all(uint8_t value) {
    for (int i = 0; i < IS31FL3736_LED_COUNT; i++) {
        is31fl3736_set_value(i, value);
    }
}

void is31fl3736_set_led_control_register(uint8_t index, bool value) {
    is31fl3736_led_t led;
    memcpy_P(&led, (&g_is31fl3736_leds[index]), sizeof(led));

    // The PWM register for a matrix position (0x00 to 0xBF) is interleaved, so:
    // A1=0x00 A2=0x02 A3=0x04 A4=0x06 A5=0x08 A6=0x0A A7=0x0C A8=0x0E
    // B1=0x10 B2=0x12 B3=0x14
    // But also, the LED control registers (0x00 to 0x17) are also interleaved, so:
    // A1-A4=0x00 A5-A8=0x01

    uint8_t control_register = led.v / 8;
    uint8_t bit_value        = led.v % 8;

    if (value) {
        g_led_control_registers[led.driver][control_register] |= (1 << bit_value);
    } else {
        g_led_control_registers[led.driver][control_register] &= ~(1 << bit_value);
    }

    g_led_control_registers_update_required[led.driver] = true;
}

void is31fl3736_update_pwm_buffers(uint8_t addr, uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        // Firstly we need to unlock the command register and select PG1
        is31fl3736_write_register(addr, IS31FL3736_COMMANDREGISTER_WRITELOCK, 0xC5);
        is31fl3736_write_register(addr, IS31FL3736_COMMANDREGISTER, IS31FL3736_PAGE_PWM);

        is31fl3736_write_pwm_buffer(addr, g_pwm_buffer[index]);
        g_pwm_buffer_update_required[index] = false;
    }
}

void is31fl3736_update_led_control_registers(uint8_t addr, uint8_t index) {
    if (g_led_control_registers_update_required[index]) {
        // Firstly we need to unlock the command register and select PG0
        is31fl3736_write_register(addr, IS31FL3736_COMMANDREGISTER_WRITELOCK, 0xC5);
        is31fl3736_write_register(addr, IS31FL3736_COMMANDREGISTER, IS31FL3736_PAGE_LEDCONTROL);
        for (int i = 0; i < IS31FL3736_LED_CONTROL_REGISTER_COUNT; i++) {
            is31fl3736_write_register(addr, i, g_led_control_registers[index][i]);
        }
        g_led_control_registers_update_required[index] = false;
    }
}

void is31fl3736_flush(void) {
    is31fl3736_update_pwm_buffers(IS31FL3736_I2C_ADDRESS_1, 0);
#if defined(IS31FL3736_I2C_ADDRESS_2)
    is31fl3736_update_pwm_buffers(IS31FL3736_I2C_ADDRESS_2, 1);
#    if defined(IS31FL3736_I2C_ADDRESS_3)
    is31fl3736_update_pwm_buffers(IS31FL3736_I2C_ADDRESS_3, 2);
#        if defined(IS31FL3736_I2C_ADDRESS_4)
    is31fl3736_update_pwm_buffers(IS31FL3736_I2C_ADDRESS_4, 3);
#        endif
#    endif
#endif
}
