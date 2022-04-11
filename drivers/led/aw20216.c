/* Copyright 2021 Jasper Chan
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

#include "aw20216.h"
#include "spi_master.h"

/* The AW20216 appears to be somewhat similar to the IS31FL743, although quite
 * a few things are different, such as the command byte format and page ordering.
 * The LED addresses start from 0x00 instead of 0x01.
 */
#define AWINIC_ID 0b1010 << 4

#define AW_PAGE_FUNCTION 0x00 << 1   // PG0, Function registers
#define AW_PAGE_PWM 0x01 << 1        // PG1, LED PWM control
#define AW_PAGE_SCALING 0x02 << 1    // PG2, LED current scaling control
#define AW_PAGE_PATCHOICE 0x03 << 1  // PG3, Pattern choice?
#define AW_PAGE_PWMSCALING 0x04 << 1 // PG4, LED PWM + Scaling control?

#define AW_WRITE 0
#define AW_READ 1

#define AW_REG_CONFIGURATION 0x00 // PG0
#define AW_REG_GLOBALCURRENT 0x01 // PG0

// Default value of AW_REG_CONFIGURATION
// D7:D4 = 1011, SWSEL (SW1~SW12 active)
// D3 = 0?, reserved (apparently this should be 1 but it doesn't seem to matter)
// D2:D1 = 00, OSDE (open/short detection enable)
// D0 = 0, CHIPEN (write 1 to enable LEDs when hardware enable pulled high)
#define AW_CONFIG_DEFAULT 0b10110000
#define AW_CHIPEN 1

#define AW_PWM_REGISTER_COUNT 216

#ifndef AW_SCALING_MAX
#    define AW_SCALING_MAX 150
#endif

#ifndef AW_GLOBAL_CURRENT_MAX
#    define AW_GLOBAL_CURRENT_MAX 150
#endif

#ifndef AW_SPI_DIVISOR
#    define AW_SPI_DIVISOR 4
#endif

uint8_t g_pwm_buffer[DRIVER_COUNT][AW_PWM_REGISTER_COUNT];
bool    g_pwm_buffer_update_required[DRIVER_COUNT] = {false};

bool AW20216_write(pin_t cs_pin, uint8_t page, uint8_t reg, uint8_t* data, uint8_t len) {
    static uint8_t s_spi_transfer_buffer[2] = {0};

    if (!spi_start(cs_pin, false, 0, AW_SPI_DIVISOR)) {
        spi_stop();
        return false;
    }

    s_spi_transfer_buffer[0] = (AWINIC_ID | page | AW_WRITE);
    s_spi_transfer_buffer[1] = reg;

    if (spi_transmit(s_spi_transfer_buffer, 2) != SPI_STATUS_SUCCESS) {
        spi_stop();
        return false;
    }

    if (spi_transmit(data, len) != SPI_STATUS_SUCCESS) {
        spi_stop();
        return false;
    }

    spi_stop();
    return true;
}

static inline bool AW20216_write_register(pin_t cs_pin, uint8_t page, uint8_t reg, uint8_t value) {
    // Little wrapper so callers need not care about sending a buffer
    return AW20216_write(cs_pin, page, reg, &value, 1);
}

static void AW20216_init_scaling(pin_t cs_pin) {
    // Set constant current to the max, control brightness with PWM
    for (uint8_t i = 0; i < AW_PWM_REGISTER_COUNT; i++) {
        AW20216_write_register(cs_pin, AW_PAGE_SCALING, i, AW_SCALING_MAX);
    }
}

static inline void AW20216_init_current_limit(pin_t cs_pin) {
    // Push config
    AW20216_write_register(cs_pin, AW_PAGE_FUNCTION, AW_REG_GLOBALCURRENT, AW_GLOBAL_CURRENT_MAX);
}

static inline void AW20216_soft_enable(pin_t cs_pin) {
    // Push config
    AW20216_write_register(cs_pin, AW_PAGE_FUNCTION, AW_REG_CONFIGURATION, AW_CONFIG_DEFAULT | AW_CHIPEN);
}

void AW20216_init(pin_t cs_pin, pin_t en_pin) {
    setPinOutput(en_pin);
    writePinHigh(en_pin);

    // Drivers should start with all scaling and PWM registers as off
    AW20216_init_current_limit(cs_pin);
    AW20216_init_scaling(cs_pin);

    AW20216_soft_enable(cs_pin);
}

void AW20216_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    aw_led led;
    memcpy_P(&led, (&g_aw_leds[index]), sizeof(led));

    g_pwm_buffer[led.driver][led.r]          = red;
    g_pwm_buffer[led.driver][led.g]          = green;
    g_pwm_buffer[led.driver][led.b]          = blue;
    g_pwm_buffer_update_required[led.driver] = true;
}

void AW20216_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        AW20216_set_color(i, red, green, blue);
    }
}

void AW20216_update_pwm_buffers(pin_t cs_pin, uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        AW20216_write(cs_pin, AW_PAGE_PWM, 0, g_pwm_buffer[index], AW_PWM_REGISTER_COUNT);
    }
    g_pwm_buffer_update_required[index] = false;
}
