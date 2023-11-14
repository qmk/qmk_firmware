/* Copyright 2021 Jasper Chan
 *           2023 Huckies <https://github.com/Huckies>
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

#include "aw20216s.h"
#include "wait.h"
#include "spi_master.h"

/* The AW20216S appears to be somewhat similar to the IS31FL743, although quite
 * a few things are different, such as the command byte format and page ordering.
 * The LED addresses start from 0x00 instead of 0x01.
 */
#define AW20216S_ID 0b1010 << 4

#define AW20216S_PAGE_FUNCTION 0x00 << 1   // PG0, Function registers
#define AW20216S_PAGE_PWM 0x01 << 1        // PG1, LED PWM control
#define AW20216S_PAGE_SCALING 0x02 << 1    // PG2, LED current scaling control
#define AW20216S_PAGE_PATCHOICE 0x03 << 1  // PG3, Pattern choice?
#define AW20216S_PAGE_PWMSCALING 0x04 << 1 // PG4, LED PWM + Scaling control?

#define AW20216S_WRITE 0
#define AW20216S_READ 1

#define AW20216S_REG_CONFIGURATION 0x00 // PG0
#define AW20216S_REG_GLOBALCURRENT 0x01 // PG0
#define AW20216S_REG_RESET 0x2F         // PG0
#define AW20216S_REG_MIXFUNCTION 0x46   // PG0

// Default value of AW20216S_REG_CONFIGURATION
// D7:D4 = 1011, SWSEL (SW1~SW12 active)
// D3 = 0?, reserved (apparently this should be 1 but it doesn't seem to matter)
// D2:D1 = 00, OSDE (open/short detection enable)
// D0 = 0, CHIPEN (write 1 to enable LEDs when hardware enable pulled high)
#define AW20216S_CONFIG_DEFAULT 0b10110000
#define AW20216S_MIXCR_DEFAULT 0b00000000
#define AW20216S_RESET_CMD 0xAE
#define AW20216S_CHIPEN 1
#define AW20216S_LPEN (0x01 << 1)

#define AW20216S_PWM_REGISTER_COUNT 216

#ifndef AW20216S_SCALING_MAX
#    define AW20216S_SCALING_MAX 150
#endif

#ifndef AW20216S_GLOBAL_CURRENT_MAX
#    define AW20216S_GLOBAL_CURRENT_MAX 150
#endif

#ifndef AW20216S_SPI_MODE
#    define AW20216S_SPI_MODE 0
#endif

#ifndef AW20216S_SPI_DIVISOR
#    define AW20216S_SPI_DIVISOR 4
#endif

uint8_t g_pwm_buffer[AW20216S_DRIVER_COUNT][AW20216S_PWM_REGISTER_COUNT];
bool    g_pwm_buffer_update_required[AW20216S_DRIVER_COUNT] = {false};

bool aw20216s_write(pin_t cs_pin, uint8_t page, uint8_t reg, uint8_t* data, uint8_t len) {
    static uint8_t s_spi_transfer_buffer[2] = {0};

    if (!spi_start(cs_pin, false, AW20216S_SPI_MODE, AW20216S_SPI_DIVISOR)) {
        spi_stop();
        return false;
    }

    s_spi_transfer_buffer[0] = (AW20216S_ID | page | AW20216S_WRITE);
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

static inline bool aw20216s_write_register(pin_t cs_pin, uint8_t page, uint8_t reg, uint8_t value) {
    // Little wrapper so callers need not care about sending a buffer
    return aw20216s_write(cs_pin, page, reg, &value, 1);
}

void aw20216s_soft_reset(pin_t cs_pin) {
    aw20216s_write_register(cs_pin, AW20216S_PAGE_FUNCTION, AW20216S_REG_RESET, AW20216S_RESET_CMD);
}

static void aw20216s_init_scaling(pin_t cs_pin) {
    // Set constant current to the max, control brightness with PWM
    for (uint8_t i = 0; i < AW20216S_PWM_REGISTER_COUNT; i++) {
        aw20216s_write_register(cs_pin, AW20216S_PAGE_SCALING, i, AW20216S_SCALING_MAX);
    }
}

static inline void aw20216s_init_current_limit(pin_t cs_pin) {
    // Push config
    aw20216s_write_register(cs_pin, AW20216S_PAGE_FUNCTION, AW20216S_REG_GLOBALCURRENT, AW20216S_GLOBAL_CURRENT_MAX);
}

static inline void aw20216s_soft_enable(pin_t cs_pin) {
    // Push config
    aw20216s_write_register(cs_pin, AW20216S_PAGE_FUNCTION, AW20216S_REG_CONFIGURATION, AW20216S_CONFIG_DEFAULT | AW20216S_CHIPEN);
}

static inline void aw20216s_auto_lowpower(pin_t cs_pin) {
    aw20216s_write_register(cs_pin, AW20216S_PAGE_FUNCTION, AW20216S_REG_MIXFUNCTION, AW20216S_MIXCR_DEFAULT | AW20216S_LPEN);
}

void aw20216s_init_drivers(void) {
    spi_init();

    aw20216s_init(AW20216S_CS_PIN_1, AW20216S_EN_PIN_1);
#if defined(AW20216S_CS_PIN_2)
    aw20216s_init(AW20216S_CS_PIN_2, AW20216S_EN_PIN_2);
#endif
}

void aw20216s_init(pin_t cs_pin, pin_t en_pin) {
    setPinOutput(en_pin);
    writePinHigh(en_pin);

    aw20216s_soft_reset(cs_pin);
    wait_ms(2);

    // Drivers should start with all scaling and PWM registers as off
    aw20216s_init_current_limit(cs_pin);
    aw20216s_init_scaling(cs_pin);

    aw20216s_soft_enable(cs_pin);
    aw20216s_auto_lowpower(cs_pin);
}

void aw20216s_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    aw20216s_led_t led;
    memcpy_P(&led, (&g_aw20216s_leds[index]), sizeof(led));

    if (g_pwm_buffer[led.driver][led.r] == red && g_pwm_buffer[led.driver][led.g] == green && g_pwm_buffer[led.driver][led.b] == blue) {
        return;
    }
    g_pwm_buffer[led.driver][led.r]          = red;
    g_pwm_buffer[led.driver][led.g]          = green;
    g_pwm_buffer[led.driver][led.b]          = blue;
    g_pwm_buffer_update_required[led.driver] = true;
}

void aw20216s_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t i = 0; i < AW20216S_LED_COUNT; i++) {
        aw20216s_set_color(i, red, green, blue);
    }
}

void aw20216s_update_pwm_buffers(pin_t cs_pin, uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        aw20216s_write(cs_pin, AW20216S_PAGE_PWM, 0, g_pwm_buffer[index], AW20216S_PWM_REGISTER_COUNT);
    }
    g_pwm_buffer_update_required[index] = false;
}

void aw20216s_flush(void) {
    aw20216s_update_pwm_buffers(AW20216S_CS_PIN_1, 0);
#if defined(AW20216S_CS_PIN_2)
    aw20216s_update_pwm_buffers(AW20216S_CS_PIN_2, 1);
#endif
}
