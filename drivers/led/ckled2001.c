/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

#include "ckled2001.h"
#include "i2c_master.h"
#include "wait.h"

#ifndef CKLED2001_TIMEOUT
#    define CKLED2001_TIMEOUT 100
#endif

#ifndef CKLED2001_PERSISTENCE
#    define CKLED2001_PERSISTENCE 0
#endif

#ifndef PHASE_CHANNEL
#    define PHASE_CHANNEL MSKPHASE_12CHANNEL
#endif

// Transfer buffer for TWITransmitData()
uint8_t g_twi_transfer_buffer[20];

// These buffers match the CKLED2001 PWM registers.
// The control buffers match the PG0 LED On/Off registers.
// Storing them like this is optimal for I2C transfers to the registers.
// We could optimize this and take out the unused registers from these
// buffers and the transfers in CKLED2001_write_pwm_buffer() but it's
// probably not worth the extra complexity.
uint8_t g_pwm_buffer[DRIVER_COUNT][192];
bool    g_pwm_buffer_update_required[DRIVER_COUNT] = {false};

uint8_t g_led_control_registers[DRIVER_COUNT][24]             = {0};
bool    g_led_control_registers_update_required[DRIVER_COUNT] = {false};

bool CKLED2001_write_register(uint8_t addr, uint8_t reg, uint8_t data) {
    // If the transaction fails function returns false.
    g_twi_transfer_buffer[0] = reg;
    g_twi_transfer_buffer[1] = data;

#if CKLED2001_PERSISTENCE > 0
    for (uint8_t i = 0; i < CKLED2001_PERSISTENCE; i++) {
        if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 2, CKLED2001_TIMEOUT) != 0) {
            return false;
        }
    }
#else
    if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 2, CKLED2001_TIMEOUT) != 0) {
        return false;
    }
#endif
    return true;
}

bool CKLED2001_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer) {
    // Assumes PG1 is already selected.
    // If any of the transactions fails function returns false.
    // Transmit PWM registers in 12 transfers of 16 bytes.
    // g_twi_transfer_buffer[] is 20 bytes

    // Iterate over the pwm_buffer contents at 16 byte intervals.
    for (int i = 0; i < 192; i += 16) {
        g_twi_transfer_buffer[0] = i;
        // Copy the data from i to i+15.
        // Device will auto-increment register for data after the first byte
        // Thus this sets registers 0x00-0x0F, 0x10-0x1F, etc. in one transfer.
        for (int j = 0; j < 16; j++) {
            g_twi_transfer_buffer[1 + j] = pwm_buffer[i + j];
        }

#if CKLED2001_PERSISTENCE > 0
        for (uint8_t i = 0; i < CKLED2001_PERSISTENCE; i++) {
            if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 17, CKLED2001_TIMEOUT) != 0) {
                return false;
            }
        }
#else
        if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 17, CKLED2001_TIMEOUT) != 0) {
            return false;
        }
#endif
    }
    return true;
}

void CKLED2001_init(uint8_t addr) {
    // Select to function page
    CKLED2001_write_register(addr, CONFIGURE_CMD_PAGE, FUNCTION_PAGE);
    // Setting LED driver to shutdown mode
    CKLED2001_write_register(addr, CONFIGURATION_REG, MSKSW_SHUT_DOWN_MODE);
    // Setting internal channel pulldown/pullup
    CKLED2001_write_register(addr, PDU_REG, MSKSET_CA_CB_CHANNEL);
    // Select number of scan phase
    CKLED2001_write_register(addr, SCAN_PHASE_REG, PHASE_CHANNEL);
    // Setting PWM Delay Phase
    CKLED2001_write_register(addr, SLEW_RATE_CONTROL_MODE1_REG, MSKPWM_DELAY_PHASE_ENABLE);
    // Setting Driving/Sinking Channel Slew Rate
    CKLED2001_write_register(addr, SLEW_RATE_CONTROL_MODE2_REG, MSKDRIVING_SINKING_CHHANNEL_SLEWRATE_ENABLE);
    // Setting Iref
    CKLED2001_write_register(addr, SOFTWARE_SLEEP_REG, MSKSLEEP_DISABLE);
    // Set LED CONTROL PAGE (Page 0)
    CKLED2001_write_register(addr, CONFIGURE_CMD_PAGE, LED_CONTROL_PAGE);
    for (int i = 0; i < LED_CONTROL_ON_OFF_LENGTH; i++) {
        CKLED2001_write_register(addr, i, 0x00);
    }

    // Set PWM PAGE (Page 1)
    CKLED2001_write_register(addr, CONFIGURE_CMD_PAGE, LED_PWM_PAGE);
    for (int i = 0; i < LED_CURRENT_TUNE_LENGTH; i++) {
        CKLED2001_write_register(addr, i, 0x00);
    }

    // Set CURRENT PAGE (Page 4)
    CKLED2001_write_register(addr, CONFIGURE_CMD_PAGE, CURRENT_TUNE_PAGE);
    for (int i = 0; i < LED_CURRENT_TUNE_LENGTH; i++) {
        CKLED2001_write_register(addr, i, 0xFF);
    }

    // Enable LEDs ON/OFF
    CKLED2001_write_register(addr, CONFIGURE_CMD_PAGE, LED_CONTROL_PAGE);
    for (int i = 0; i < LED_CONTROL_ON_OFF_LENGTH; i++) {
        CKLED2001_write_register(addr, i, 0xFF);
    }

    // Select to function page
    CKLED2001_write_register(addr, CONFIGURE_CMD_PAGE, FUNCTION_PAGE);
    // Setting LED driver to normal mode
    CKLED2001_write_register(addr, CONFIGURATION_REG, MSKSW_NORMAL_MODE);
}

void CKLED2001_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    ckled2001_led led;
    if (index >= 0 && index < DRIVER_LED_TOTAL) {
        memcpy_P(&led, (&g_ckled2001_leds[index]), sizeof(led));

        g_pwm_buffer[led.driver][led.r]          = red;
        g_pwm_buffer[led.driver][led.g]          = green;
        g_pwm_buffer[led.driver][led.b]          = blue;
        g_pwm_buffer_update_required[led.driver] = true;
    }
}

void CKLED2001_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        CKLED2001_set_color(i, red, green, blue);
    }
}

void CKLED2001_set_led_control_register(uint8_t index, bool red, bool green, bool blue) {
    ckled2001_led led;
    memcpy_P(&led, (&g_ckled2001_leds[index]), sizeof(led));

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

void CKLED2001_update_pwm_buffers(uint8_t addr, uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        CKLED2001_write_register(addr, CONFIGURE_CMD_PAGE, LED_PWM_PAGE);

        // If any of the transactions fail we risk writing dirty PG0,
        // refresh page 0 just in case.
        if (!CKLED2001_write_pwm_buffer(addr, g_pwm_buffer[index])) {
            g_led_control_registers_update_required[index] = true;
        }
    }
    g_pwm_buffer_update_required[index] = false;
}

void CKLED2001_update_led_control_registers(uint8_t addr, uint8_t index) {
    if (g_led_control_registers_update_required[index]) {
        CKLED2001_write_register(addr, CONFIGURE_CMD_PAGE, LED_CONTROL_PAGE);
        for (int i = 0; i < 24; i++) {
            CKLED2001_write_register(addr, i, g_led_control_registers[index][i]);
        }
    }
    g_led_control_registers_update_required[index] = false;
}

void CKLED2001_return_normal(uint8_t addr) {
    // Select to function page
    CKLED2001_write_register(addr, CONFIGURE_CMD_PAGE, FUNCTION_PAGE);
    // Setting LED driver to normal mode
    CKLED2001_write_register(addr, CONFIGURATION_REG, MSKSW_NORMAL_MODE);
}

void CKLED2001_shutdown(uint8_t addr) {
    // Select to function page
    CKLED2001_write_register(addr, CONFIGURE_CMD_PAGE, FUNCTION_PAGE);
    // Setting LED driver to shutdown mode
    CKLED2001_write_register(addr, CONFIGURATION_REG, MSKSW_SHUT_DOWN_MODE);
    // Write SW Sleep Register
    CKLED2001_write_register(addr, SOFTWARE_SLEEP_REG, MSKSLEEP_ENABLE);
}
