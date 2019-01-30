/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
 * Copyright 2019 Clueboard
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

#ifdef __AVR__
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#else
#include "wait.h"
#endif

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "is31fl3235a.h"
#include "i2c_master.h"
#include "progmem.h"
#include "print.h"


#define ISSI_REG_CONFIG  0x00  // FIXME: Not on 3235?
#define ISSI_REG_CONFIG_PICTUREMODE 0x00  // FIXME: Not on 3235?

//#define ISSI_REG_AUDIOSYNC 0x06  // FIXME: Not on 3235?

#define ISSI_COMMANDREGISTER 0xFD  // FIXME: Not on 3235?
#define ISSI_BANK_FUNCTIONREG 0x0B    // FIXME: Not on 3235?

#ifndef ISSI_TIMEOUT
  #define ISSI_TIMEOUT 100
#endif

#ifndef ISSI_PERSISTENCE
  #define ISSI_PERSISTENCE 0
#endif

// Transfer buffer for TWITransmitData()
uint8_t g_3235a_transfer_buffer[20];

// These buffers match the IS31FL3235A PWM registers 0x05-0x20.
// Storing them like this is optimal for I2C transfers to the registers.
// We could optimize this and take out the unused registers from these
// buffers and the transfers in IS31FL3235A_write_pwm_buffer() but it's
// probably not worth the extra complexity.
uint8_t g_rgb7seg_buffer[IS31FL3235A_COUNT][IS31FL3235A_LED_MAX];
bool g_rgb7seg_buffer_update_required = false;

/* There's probably a better way to init this... */
#if IS31FL3235A_COUNT == 1
    uint8_t g_3235a_control_registers[IS31FL3235A_COUNT][18] = {{0}};
#elif IS31FL3235A_COUNT == 2
    uint8_t g_3235a_control_registers[IS31FL3235A_COUNT][18] = {{0}, {0}};
#elif IS31FL3235A_COUNT == 3
    uint8_t g_3235a_control_registers[IS31FL3235A_COUNT][18] = {{0}, {0}, {0}};
#elif IS31FL3235A_COUNT == 4
    uint8_t g_3235a_control_registers[IS31FL3235A_COUNT][18] = {{0}, {0}, {0}, {0}};
#endif
bool g_rgb7seg_control_registers_update_required = false;

void IS31FL3235A_write_register(uint8_t addr, uint8_t reg, uint8_t data) {
    g_3235a_transfer_buffer[0] = reg;
    g_3235a_transfer_buffer[1] = data;
    xprintf("IS31FL3235A_write_register(0x%x, 0x%x, 0x%x); g_3235a_transfer_buffer:0x%x\n", addr, reg, data, g_3235a_transfer_buffer);

    #if ISSI_PERSISTENCE > 0
        for (uint8_t i = 0; i < ISSI_PERSISTENCE; i++) {
            if (i2c_transmit(addr, g_3235a_transfer_buffer, 2, ISSI_TIMEOUT) == 0) {
              break;
            }
        }
    #else
        if (i2c_transmit(addr, g_3235a_transfer_buffer, 2, ISSI_TIMEOUT) == -1) {
            // When we encounter a timeout ChibiOS says the bus must be reset as it's in an unknown state
            xprintf("i2c transmit timeout, resetting i2c bus!\n");
            i2c_stop(ISSI_TIMEOUT);
            wait_ms(5);
            i2c_start(ISSI_TIMEOUT);
        }
    #endif
}

void IS31FL3235A_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer) {
    // assumes bank is already selected

    // transmit PWM registers in 9 transfers of 16 bytes
    // g_3235a_transfer_buffer[] is 20 bytes

    // iterate over the pwm_buffer contents at 16 byte intervals
    for (int i = 0; i < IS31FL3235A_LED_MAX; i += 16) {
        // set the first register, e.g. 0x24, 0x34, 0x44, etc.
        g_3235a_transfer_buffer[0] = 0x24 + i;
        // copy the data from i to i+15
        // device will auto-increment register for data after the first byte
        // thus this sets registers 0x24-0x33, 0x34-0x43, etc. in one transfer
        for (int j = 0; j < 16; j++) {
            g_3235a_transfer_buffer[1 + j] = pwm_buffer[i + j];
        }

    #if ISSI_PERSISTENCE > 0
      for (uint8_t i = 0; i < ISSI_PERSISTENCE; i++) {
        if (i2c_transmit(addr << 1, g_3235a_transfer_buffer, 17, ISSI_TIMEOUT) == 0)
          break;
      }
    #else
        if (i2c_transmit(addr << 1, g_3235a_transfer_buffer, 17, ISSI_TIMEOUT) == -1) {
            // When we encounter a timeout ChibiOS says the bus must be reset as it's in an unknown state
            xprintf("i2c transmit timeout, resetting i2c bus!\n");
            i2c_stop(ISSI_TIMEOUT);
            wait_ms(5);
            i2c_start(ISSI_TIMEOUT);
        }
    #endif
    }
}

void IS31FL3235A_init(uint8_t addr) {
    wait_ms(2000); // Give QMK Toolbox time to attach
    xprintf("IS31FS3235A_init(0x%x)\n", addr);
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, first enable software shutdown,
    // then set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.

    // Reset settings to default
    //IS31FL3235A_write_register(addr, ISSI_REG_RESET_REG, 0);

    // this delay was copied from other drivers, might not be needed
    wait_ms(10);

    // This is how the Arduino code does init...
    uint8_t i = 0;

    for (i=0x2A; i<=0x45; i++) {
        IS31FL3235A_write_register(addr, i, 0xFF);  // Turn off all LEDs
    }

    for (i=0x05; i<=0x20; i++) {
        IS31FL3235A_write_register(addr, i, 0x00);  // Write all PWM set 0x00
    }

    IS31FL3235A_write_register(addr, 0x25, 0x00);   //update PWM&Control registers
    IS31FL3235A_write_register(addr, 0x4B, 0x01);   //frequency setting 22KHz
    IS31FL3235A_write_register(addr, 0x00, 0x01);   //normal operation

    // This is how the Arduino code does LED turn on
    IS31FL3235A_write_register(addr, 0x05, 0xFF);   // set PWM
    IS31FL3235A_write_register(addr, 0x25, 0x00);   // update PWM&Control registers
    IS31FL3235A_write_register(addr, 0x08, 0xFF);   // set PWM
    IS31FL3235A_write_register(addr, 0x25, 0x00);   // update PWM&Control registers
    IS31FL3235A_write_register(addr, 0x12, 0xFF);   // set PWM
    IS31FL3235A_write_register(addr, 0x25, 0x00);   // update PWM&Control registers

    // FIXME: This is for testing, turn on OUT1 at full brightness
    //IS31FL3235A_write_register(addr, 0x2A, 0xFF);
    //IS31FL3235A_write_register(addr, 0x05, 0x00);

    // I think this finally turns it on?
    //IS31FL3235A_write_register(addr, 0x25, 0x00);    //update PWM&Control registers
    //IS31FL3235A_write_register(addr, 0x4B, 0x01);  //frequency setting 22KHz
    //IS31FL3235A_write_register(addr, 0x00, 0x01);    //normal operation
}

void IS31FL3235A_set_value(int index, uint8_t value) {
/*
    if (index >= 0 && index < IS31FL3235A_LED_COUNT) {
        is31_led led = g_is31_leds[index];

        // Subtract 0x24 to get the second index of g_rgb7seg_buffer
        g_rgb7seg_buffer[led.driver][led.v - 0x24] = value;
        g_rgb7seg_buffer_update_required = true;
    }
*/
}

void IS31FL3235A_set_value_all(uint8_t value) {
    for (int i = 0; i < IS31FL3235A_LED_COUNT; i++) {
        IS31FL3235A_set_value(i, value);
    }
}

void IS31FL3235A_set_led_control_register(uint8_t index, bool value) {
/*
  is31_led led = g_is31_leds[index];

  uint8_t control_register = (led.v - 0x24) / 8;
  uint8_t bit_value = (led.v - 0x24) % 8;

    if (value) {
        g_3235a_control_registers[led.driver][control_register] |= (1 << bit_value);
    } else {
        g_3235a_control_registers[led.driver][control_register] &= ~(1 << bit_value);
    }

    g_rgb7seg_control_registers_update_required = true;
*/
}

void IS31FL3235A_update_pwm_buffers(uint8_t addr, uint8_t index) {
    //xprintf("IS31FS3235A_update_pwm_buffers(0x%x, %d)\n", addr, index);
    if (g_rgb7seg_buffer_update_required) {
        IS31FL3235A_write_pwm_buffer(addr, g_rgb7seg_buffer[index]);
        g_rgb7seg_buffer_update_required = false;
    }
}

void IS31FL3235A_update_led_control_registers(uint8_t addr, uint8_t index) {
    if (g_rgb7seg_control_registers_update_required) {
        for (int i=0; i<18; i++) {
            IS31FL3235A_write_register(addr, i, g_3235a_control_registers[index][i]);
        }
    }
}
