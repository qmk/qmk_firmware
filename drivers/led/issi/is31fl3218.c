/* Copyright 2018 Jason Williams (Wilba)
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
#include "is31fl3218.h"
#include "i2c_master.h"

// This is the full 8-bit address
#define ISSI_ADDRESS 0b10101000

// These are the register addresses
#define ISSI_REG_SHUTDOWN 0x00
#define ISSI_REG_PWM 0x01
#define ISSI_REG_CONTROL 0x13
#define ISSI_REG_UPDATE 0x16
#define ISSI_REG_RESET 0x17

// Default timeout if no I2C response
#define ISSI_TIMEOUT 100

// Reusable buffer for transfers
uint8_t g_twi_transfer_buffer[20];

// IS31FL3218 has 18 PWM outputs and a fixed I2C address, so no chaining.
// If used as RGB LED driver, LEDs are assigned RGB,RGB,RGB,RGB,RGB,RGB
uint8_t g_pwm_buffer[18];
bool    g_pwm_buffer_update_required = false;

void is31fl3218_write_register(uint8_t reg, uint8_t data) {
    g_twi_transfer_buffer[0] = reg;
    g_twi_transfer_buffer[1] = data;
    i2c_transmit(ISSI_ADDRESS, g_twi_transfer_buffer, 2, ISSI_TIMEOUT);
}

void is31fl3218_write_pwm_buffer(uint8_t *pwm_buffer) {
    g_twi_transfer_buffer[0] = ISSI_REG_PWM;
    memcpy(g_twi_transfer_buffer + 1, pwm_buffer, 18);

    i2c_transmit(ISSI_ADDRESS, g_twi_transfer_buffer, 19, ISSI_TIMEOUT);
}

void is31fl3218_init(void) {
    // In case we ever want to reinitialize (?)
    is31fl3218_write_register(ISSI_REG_RESET, 0x00);

    // Turn off software shutdown
    is31fl3218_write_register(ISSI_REG_SHUTDOWN, 0x01);

    // Set all PWM values to zero
    for (uint8_t i = 0; i < 18; i++) {
        is31fl3218_write_register(ISSI_REG_PWM + i, 0x00);
    }

    // Enable all channels
    for (uint8_t i = 0; i < 3; i++) {
        is31fl3218_write_register(ISSI_REG_CONTROL + i, 0b00111111);
    }

    // Load PWM registers and LED Control register data
    is31fl3218_write_register(ISSI_REG_UPDATE, 0x01);
}

void is31fl3218_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (g_pwm_buffer[index * 3 + 0] == red && g_pwm_buffer[index * 3 + 1] == green && g_pwm_buffer[index * 3 + 2] == blue) {
        return;
    }
    g_pwm_buffer[index * 3 + 0]  = red;
    g_pwm_buffer[index * 3 + 1]  = green;
    g_pwm_buffer[index * 3 + 2]  = blue;
    g_pwm_buffer_update_required = true;
}

void is31fl3218_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < 6; i++) {
        is31fl3218_set_color(i, red, green, blue);
    }
}

void is31fl3218_update_pwm_buffers(void) {
    if (g_pwm_buffer_update_required) {
        is31fl3218_write_pwm_buffer(g_pwm_buffer);
        // Load PWM registers and LED Control register data
        is31fl3218_write_register(ISSI_REG_UPDATE, 0x01);
    }
    g_pwm_buffer_update_required = false;
}
