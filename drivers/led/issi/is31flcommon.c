/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
 * Copyright 2018 Yiancar
 * Copyright 2020 MelGeek
 * Copyright 2021 MasterSpoon
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

#include "is31flcommon.h"
#include "i2c_master.h"
#include "wait.h"
#include <string.h>

// Set defaults for Timeout and Persistence
#ifndef ISSI_TIMEOUT
#    define ISSI_TIMEOUT 100
#endif
#ifndef ISSI_PERSISTENCE
#    define ISSI_PERSISTENCE 0
#endif

// Transfer buffer for TWITransmitData()
uint8_t g_twi_transfer_buffer[20];

// These buffers match the PWM & scaling registers.
// Storing them like this is optimal for I2C transfers to the registers.
uint8_t g_pwm_buffer[DRIVER_COUNT][ISSI_MAX_LEDS];
bool    g_pwm_buffer_update_required[DRIVER_COUNT] = {false};

uint8_t g_scaling_buffer[DRIVER_COUNT][ISSI_SCALING_SIZE];
bool    g_scaling_buffer_update_required[DRIVER_COUNT] = {false};

// For writing of single register entry
void IS31FL_write_single_register(uint8_t addr, uint8_t reg, uint8_t data) {
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

// For writing of mulitple register entries to make use of address auto increment
// Once the controller has been called and we have written the first bit of data
// the controller will move to the next register meaning we can write sequential blocks.
bool IS31FL_write_multi_registers(uint8_t addr, uint8_t *source_buffer, uint8_t buffer_size, uint8_t transfer_size, uint8_t start_reg_addr) {
    // Split the buffer into chunks to transfer
    for (int i = 0; i < buffer_size; i += transfer_size) {
        // Set the first entry of transfer buffer to the first register we want to write
        g_twi_transfer_buffer[0] = i + start_reg_addr;
        // Copy the section of our source buffer into the transfer buffer after first register address
        memcpy(g_twi_transfer_buffer + 1, source_buffer + i, transfer_size);

#if ISSI_PERSISTENCE > 0
        for (uint8_t i = 0; i < ISSI_PERSISTENCE; i++) {
            if (i2c_transmit(addr << 1, g_twi_transfer_buffer, transfer_size + 1, ISSI_TIMEOUT) != 0) {
                return false;
            }
        }
#else
        if (i2c_transmit(addr << 1, g_twi_transfer_buffer, transfer_size + 1, ISSI_TIMEOUT) != 0) {
            return false;
        }
#endif
    }
    return true;
}

void IS31FL_unlock_register(uint8_t addr, uint8_t page) {
    // unlock the command register and select Page to write
    IS31FL_write_single_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, ISSI_REGISTER_UNLOCK);
    IS31FL_write_single_register(addr, ISSI_COMMANDREGISTER, page);
}

void IS31FL_common_init(uint8_t addr, uint8_t ssr) {
    // Setup phase, need to take out of software shutdown and configure
    // ISSI_SSR_x is passed to allow Master / Slave setting where applicable

    // Unlock the command register & select Function Register
    IS31FL_unlock_register(addr, ISSI_PAGE_FUNCTION);
    // Set Configuration Register to remove Software shutdown
    IS31FL_write_single_register(addr, ISSI_REG_CONFIGURATION, ISSI_CONFIGURATION);
    // Set Golbal Current Control Register
    IS31FL_write_single_register(addr, ISSI_REG_GLOBALCURRENT, ISSI_GLOBALCURRENT);
    // Set Pull up & Down for SWx CSy
    IS31FL_write_single_register(addr, ISSI_REG_PULLDOWNUP, ISSI_PULLDOWNUP);
// Set Tempature Status
#ifdef ISSI_REG_TEMP
    IS31FL_write_single_register(addr, ISSI_REG_TEMP, ISSI_TEMP);
#endif
    // Set Spread Spectrum Register, passed through as sets SYNC function
    IS31FL_write_single_register(addr, ISSI_REG_SSR, ssr);
// Set PWM Frequency Enable Register if applicable
#ifdef ISSI_REG_PWM_ENABLE
    IS31FL_write_single_register(addr, ISSI_REG_PWM_ENABLE, ISSI_PWM_ENABLE);
#endif
// Set PWM Frequency Register if applicable
#ifdef ISSI_REG_PWM_SET
    IS31FL_write_single_register(addr, ISSI_REG_PWM_SET, ISSI_PWM_SET);
#endif

    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

void IS31FL_common_update_pwm_register(uint8_t addr, uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        // Queue up the correct page
        IS31FL_unlock_register(addr, ISSI_PAGE_PWM);
        // Hand off the update to IS31FL_write_multi_registers
        IS31FL_write_multi_registers(addr, g_pwm_buffer[index], ISSI_MAX_LEDS, ISSI_PWM_TRF_SIZE, ISSI_PWM_REG_1ST);
        // Update flags that pwm_buffer has been updated
        g_pwm_buffer_update_required[index] = false;
    }
}

#ifdef ISSI_MANUAL_SCALING
void IS31FL_set_manual_scaling_buffer(void) {
    for (int i = 0; i < ISSI_MANUAL_SCALING; i++) {
        is31_led scale = g_is31_scaling[i];
#    ifdef RGB_MATRIX_ENABLE
        if (scale.driver >= 0 && scale.driver < RGB_MATRIX_LED_COUNT) {
            is31_led led = g_is31_leds[scale.driver];

            g_scaling_buffer[led.driver][led.r] = scale.r;
            g_scaling_buffer[led.driver][led.g] = scale.g;
            g_scaling_buffer[led.driver][led.b] = scale.b;
#    elif defined(LED_MATRIX_ENABLE)
        if (scale.driver >= 0 && scale.driver < LED_MATRIX_LED_COUNT) {
            is31_led led = g_is31_leds[scale.driver];

            g_scaling_buffer[led.driver][led.v] = scale.v;
#    endif
            g_scaling_buffer_update_required[led.driver] = true;
        }
    }
}
#endif

void IS31FL_common_update_scaling_register(uint8_t addr, uint8_t index) {
    if (g_scaling_buffer_update_required[index]) {
        // Queue up the correct page
        IS31FL_unlock_register(addr, ISSI_PAGE_SCALING);
        // Hand off the update to IS31FL_write_multi_registers
        IS31FL_write_multi_registers(addr, g_scaling_buffer[index], ISSI_SCALING_SIZE, ISSI_SCALING_TRF_SIZE, ISSI_SCL_REG_1ST);
        // Update flags that scaling_buffer has been updated
        g_scaling_buffer_update_required[index] = false;
    }
}

#ifdef RGB_MATRIX_ENABLE
// Colour is set by adjusting PWM register
void IS31FL_RGB_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index >= 0 && index < RGB_MATRIX_LED_COUNT) {
        is31_led led = g_is31_leds[index];

        g_pwm_buffer[led.driver][led.r]          = red;
        g_pwm_buffer[led.driver][led.g]          = green;
        g_pwm_buffer[led.driver][led.b]          = blue;
        g_pwm_buffer_update_required[led.driver] = true;
    }
}

void IS31FL_RGB_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        IS31FL_RGB_set_color(i, red, green, blue);
    }
}

// Setup Scaling register that decides the peak current of each LED
void IS31FL_RGB_set_scaling_buffer(uint8_t index, bool red, bool green, bool blue) {
    is31_led led = g_is31_leds[index];
    if (red) {
        g_scaling_buffer[led.driver][led.r] = ISSI_SCAL_RED;
    } else {
        g_scaling_buffer[led.driver][led.r] = ISSI_SCAL_RED_OFF;
    }
    if (green) {
        g_scaling_buffer[led.driver][led.g] = ISSI_SCAL_GREEN;
    } else {
        g_scaling_buffer[led.driver][led.g] = ISSI_SCAL_GREEN_OFF;
    }
    if (blue) {
        g_scaling_buffer[led.driver][led.b] = ISSI_SCAL_BLUE;
    } else {
        g_scaling_buffer[led.driver][led.b] = ISSI_SCAL_BLUE_OFF;
    }
    g_scaling_buffer_update_required[led.driver] = true;
}

#elif defined(LED_MATRIX_ENABLE)
// LED Matrix Specific scripts
void IS31FL_simple_set_scaling_buffer(uint8_t index, bool value) {
    is31_led led = g_is31_leds[index];
    if (value) {
        g_scaling_buffer[led.driver][led.v] = ISSI_SCAL_LED;
    } else {
        g_scaling_buffer[led.driver][led.v] = ISSI_SCAL_LED_OFF;
    }
    g_scaling_buffer_update_required[led.driver] = true;
}

void IS31FL_simple_set_brightness(int index, uint8_t value) {
    if (index >= 0 && index < LED_MATRIX_LED_COUNT) {
        is31_led led = g_is31_leds[index];
        g_pwm_buffer[led.driver][led.v] = value;
        g_pwm_buffer_update_required[led.driver] = true;
    }
}

void IS31FL_simple_set_brigntness_all(uint8_t value) {
    for (int i = 0; i < LED_MATRIX_LED_COUNT; i++) {
        IS31FL_simple_set_brightness(i, value);
    }
}
#endif
