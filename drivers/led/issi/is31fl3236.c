/* Copyright 2018 Jason Williams (Wilba)
 * Copyright 2021 Jamal Bouajjaj (Electro707)
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
#include "is31fl3236.h"
#include "i2c_master.h"

// This is the full 8-bit address
#define ISSI_DEFAULT_ADDRESS 0b0111100

// These are the register addresses
#define ISSI_REG_SHUTDOWN 0x00
#define ISSI_REG_PWM 0x01
#define ISSI_REG_CONTROL 0x26
#define ISSI_REG_UPDATE 0x25
#define ISSI_REG_RESET 0x4F
#define ISSI_REG_G_CONTROL 0x4A
#define ISSI_REG_FREQ 0x4B

// Default timeout if no I2C response
#define ISSI_TIMEOUT 100

// Reusable buffer for transfers
uint8_t g_twi_transfer_buffer[40];

// IS31FL3236 has 36 PWM outputs.
// If used as RGB LED driver, LEDs are assigned RGB,RGB,RGB,RGB,RGB,RGB
// The RGB handling is done in user space
uint8_t g_pwm_buffer[36];
bool    g_pwm_buffer_update_required = false;
uint8_t g_led_control_registers[36];
bool    g_led_control_update_required = false;

void IS31FL3236_write_register(uint8_t addr, uint8_t reg, uint8_t data) {
    g_twi_transfer_buffer[0] = reg;
    g_twi_transfer_buffer[1] = data;
    i2c_transmit(addr << 1, g_twi_transfer_buffer, 2, ISSI_TIMEOUT);
}

void IS31FL3236_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer) {
    g_twi_transfer_buffer[0] = ISSI_REG_PWM;
    for (int i = 0; i < 36; i++) {
        g_twi_transfer_buffer[1 + i] = pwm_buffer[i];
    }

    i2c_transmit(addr << 1, g_twi_transfer_buffer, 37, ISSI_TIMEOUT);
}

void IS31FL3236_write_led_control_buffer(uint8_t addr, uint8_t *led_control_buffer) {
    g_twi_transfer_buffer[0] = ISSI_REG_CONTROL;
    for (int i = 0; i < 36; i++) {
        g_twi_transfer_buffer[1 + i] = led_control_buffer[i];
    }

    i2c_transmit(addr << 1, g_twi_transfer_buffer, 37, ISSI_TIMEOUT);
}

void IS31FL3236_init(uint8_t addr) {
    // In case we ever want to reinitialize (?)
    IS31FL3236_write_register(addr, ISSI_REG_RESET, 0x00);

    // Turn off software shutdown
    IS31FL3236_write_register(addr, ISSI_REG_SHUTDOWN, 0x01);

    // Set all PWM values to zero
    for (uint8_t i = 0; i < 36; i++) {
        IS31FL3236_write_register(addr, ISSI_REG_PWM + i, 0x00);
    }

    // Enable all channels
    for (uint8_t i = 0; i < 36; i++) {
        // Set each LED to half current and enable them
        // TODO: Set an option to change the current drive thru a calling function
        IS31FL3236_write_register(addr, ISSI_REG_CONTROL + i, 0b001);
    }

    // Load PWM registers and LED Control register data
    IS31FL3236_write_register(addr, ISSI_REG_UPDATE, 0x00);
}

void IS31FL3236_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    is31_led led;
    memcpy_P(&led, (&g_is31_leds[index]), sizeof(led));

    g_pwm_buffer[led.r]          = red;
    g_pwm_buffer[led.g]          = green;
    g_pwm_buffer[led.b]          = blue;
    g_pwm_buffer_update_required = true;
}

void IS31FL3236_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < 6; i++) {
        IS31FL3236_set_color(i, red, green, blue);
    }
}

void IS31FL3236_set_led_control_register(uint8_t index, bool red, bool green, bool blue) {
    is31_led led;
    memcpy_P(&led, (&g_is31_leds[index]), sizeof(led));

    g_led_control_registers[led.r] = red;
    g_led_control_registers[led.g] = green;
    g_led_control_registers[led.b] = blue;
    g_led_control_update_required  = true;
}

void IS31FL3236_update_pwm_buffers(uint8_t addr) {
    if (g_pwm_buffer_update_required) {
        IS31FL3236_write_pwm_buffer(addr, g_pwm_buffer);
        // Load PWM registers and LED Control register data
        IS31FL3236_write_register(addr, ISSI_REG_UPDATE, 0x00);
    }
    g_pwm_buffer_update_required = false;
}

void IS31FL3236_update_led_control_registers(uint8_t addr) {
    if (g_led_control_update_required) {
        IS31FL3236_write_led_control_buffer(addr, g_led_control_registers);
        // Load PWM registers and LED Control register data
        IS31FL3236_write_register(addr, ISSI_REG_UPDATE, 0x00);
    }
    g_led_control_update_required = false;
}
