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
// We could optimize this and take out the unused registers from these
// buffers and the transfers in IS31FL_common_write_pwm_register() but it's
// probably not worth the extra complexity.
uint8_t g_pwm_buffer[DRIVER_COUNT][ISSI_MAX_LEDS];
bool    g_pwm_buffer_update_required[DRIVER_COUNT] = {false};

uint8_t g_scaling_buffer[DRIVER_COUNT][ISSI_SCALING_SIZE];
bool    g_scaling_buffer_update_required[DRIVER_COUNT] = {false};


void IS31FL_common_write_register(uint8_t addr, uint8_t reg, uint8_t data) {
// If the transaction fails function returns false.
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

void IS31FL_common_init(uint8_t addr, uint8_t ssr) {
	// Setup phase, need to take out of software shutdown and configure
	// Spread Spectrum Register is passed and to be set as per data sheet

    // Unlock the command register.
    IS31FL_common_write_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, ISSI_REGISTER_UNLOCK);
    // Select Function Register
    IS31FL_common_write_register(addr, ISSI_COMMANDREGISTER, ISSI_PAGE_FUNCTION);
    // Set Configuration Register to remove Software shutdown
    IS31FL_common_write_register(addr, ISSI_REG_CONFIGURATION, ISSI_CONFIGURATION);
    // Set Golbal Current Control Register
    IS31FL_common_write_register(addr, ISSI_REG_GLOBALCURRENT, ISSI_GLOBALCURRENT);
	// Set Pull up & Down for SWx CSy
    IS31FL_common_write_register(addr, ISSI_REG_PULLDOWNUP, ISSI_PULLDOWNUP);
	// Set Tempature Status
    IS31FL_common_write_register(addr, ISSI_REG_TEMP, ISSI_TEMP);
    // Set Spread Spectrum Register, passed through as sets SYNC function
    IS31FL_common_write_register(addr, ISSI_REG_SSR, ssr);
	// Set PWM Frequency Enable Register if applicable
	#ifdef ISSI_REG_PWM_ENABLE
	IS31FL_common_write_register(addr, ISSI_REG_PWM_ENABLE, ISSI_PWM_ENABLE);
	#endif
	// Set PWM Frequency Register if applicable
	#ifdef ISSI_REG_PWM_SET
	IS31FL_common_write_register(addr, ISSI_REG_PWM_SET, ISSI_PWM_SET);
	#endif	
	
    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

bool IS31FL_common_write_pwm_register(uint8_t addr, uint8_t *pwm_buffer) {
	// PWM page already selected and unlocked by IS31FL_common_update_pwm_register
    for (int i = 0; i < ISSI_MAX_LEDS; i += ISSI_PWM_TRF_SIZE) {
        g_twi_transfer_buffer[0] = i + ISSI_PWM_REG_1ST;
        memcpy(g_twi_transfer_buffer + 1, pwm_buffer + i, ISSI_PWM_TRF_SIZE);

#if ISSI_PERSISTENCE > 0
        for (uint8_t i = 0; i < ISSI_PERSISTENCE; i++) {
            if (i2c_transmit(addr << 1, g_twi_transfer_buffer, ISSI_PWM_TRF_SIZE + 1, ISSI_TIMEOUT) != 0) {
                return false;
            }
        }
#else
        if (i2c_transmit(addr << 1, g_twi_transfer_buffer, ISSI_PWM_TRF_SIZE + 1, ISSI_TIMEOUT) != 0) {
            return false;
        }
#endif
    }
    return true;
}

void IS31FL_common_update_pwm_register(uint8_t addr, uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
	// unlock the command register and select PWM Page
    IS31FL_common_write_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, ISSI_REGISTER_UNLOCK);
    IS31FL_common_write_register(addr, ISSI_COMMANDREGISTER, ISSI_PAGE_PWM);

	// Hand off the update to IS31FL_common_write_pwm_register
        if (!IS31FL_common_write_pwm_register(addr, g_pwm_buffer[index])) {
	// If write_pwm_buffer was successful set scaling buffer to be updated
            g_scaling_buffer_update_required[index] = true;
        }
    }
	// Update flags that pwm_buffer has been updated
    g_pwm_buffer_update_required[index] = false;
}

// Colour is set by adjusting PWM of each LED
void IS31FL_RGB_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index >= 0 && index < DRIVER_LED_TOTAL) {
        is31_led led = g_is31_leds[index];

        g_pwm_buffer[led.driver][led.r] = red;
        g_pwm_buffer[led.driver][led.g] = green;
        g_pwm_buffer[led.driver][led.b] = blue;
        g_pwm_buffer_update_required[led.driver] = true;
    }
}

void IS31FL_RGB_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        IS31FL_common_set_color(i, red, green, blue);
    }
}

// Setup Scaling register that decides the peak current of each LED
void IS31FL_RGB_set_scaling_buffer(uint8_t index, bool red, bool green, bool blue) {
    is31_led led = g_is31_leds[index];

    if (red) {g_scaling_buffer[led.driver][led.r] = ISSI_SCAL_RED;
	} else {g_scaling_buffer[led.driver][led.r] = ISSI_SCAL_RED_OFF;
	}
    if (green) {g_scaling_buffer[led.driver][led.g] = ISSI_SCAL_GREEN;
	} else {g_scaling_buffer[led.driver][led.g] = ISSI_SCAL_GREEN_OFF;
	}
    if (blue) {g_scaling_buffer[led.driver][led.b] = ISSI_SCAL_BLUE;
	} else {g_scaling_buffer[led.driver][led.b] = ISSI_SCAL_BLUE_OFF;
	}

    g_scaling_buffer_update_required[led.driver] = true;
}

bool IS31FL_common_write_scaling_register(uint8_t addr, uint8_t *scale_buffer) {
	// Scaling page already selected and unlocked by IS31FL_common_update_scaling_register
    for (int i = 0; i < ISSI_SCALING_SIZE; i += ISSI_SCALING_TRF_SIZE) {
        g_twi_transfer_buffer[0] = i + ISSI_SCL_REG_1ST;
        memcpy(g_twi_transfer_buffer + 1, scale_buffer + i, ISSI_SCALING_TRF_SIZE);

#if ISSI_PERSISTENCE > 0
        for (uint8_t i = 0; i < ISSI_PERSISTENCE; i++) {
            if (i2c_transmit(addr << 1, g_twi_transfer_buffer, ISSI_SCALING_TRF_SIZE + 1, ISSI_TIMEOUT) != 0) {
                return false;
            }
        }
#else
        if (i2c_transmit(addr << 1, g_twi_transfer_buffer, ISSI_SCALING_TRF_SIZE + 1, ISSI_TIMEOUT) != 0) {
            return false;
        }
#endif
    }
    return true;
}

void IS31FL_common_update_scaling_register(uint8_t addr, uint8_t index) {
    if (g_scaling_buffer_update_required[index]) {
	// unlock the command register and select Scaling register
        IS31FL_common_write_register(addr, ISSI_COMMANDREGISTER_WRITELOCK, ISSI_REGISTER_UNLOCK);
        IS31FL_common_write_register(addr, ISSI_COMMANDREGISTER, ISSI_PAGE_SCALING);
	// Hand off the update to IS31FL_common_write_scaling_register
		IS31FL_common_write_scaling_register(addr, g_scaling_buffer[index]);
    }
	// Update flags that scaling_buffer has been updated
    g_scaling_buffer_update_required[index] = false;
}