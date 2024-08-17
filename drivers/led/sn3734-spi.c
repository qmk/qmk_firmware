/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

#include "sn3734-spi.h"
#include <string.h>
#include "spi_master.h"
#include "wait.h"
#include "gpio.h"

#ifdef DRIVER_CS_PINS
        pin_t cs_pins[] = DRIVER_CS_PINS;
#else
        error "no DRIVER_CS_PINS defined"
#endif
#define SN3734_DRIVER_COUNT (sizeof(cs_pins) / sizeof(pin_t))

#ifndef SN3734_SWS
#    define SN3734_SWS SN3734_SWS_ALL
#endif

#ifndef SN2734_SCALING
#    define SN2734_SCALING \
        { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }
#endif

#ifndef SN3734_SRS
#    define SN3734_SRS SN3734_PWM_FREQUENCY_6K_HZ
#endif

#ifndef SN3734_SWPDR
#    define SN3734_SWPDR SN3734_SWPDR_2V0
#endif

#ifndef SN3734_CSPUR
#    define SN3734_CSPUR SN3734_CSPUR_PVCC_MINUS_2V0
#endif

#ifndef SN3734_GLOBAL_CURRENT
#    define SN3734_GLOBAL_CURRENT 0xFF
#endif

#define SN3734_WRITE (0 << 7)
#define SN3734_READ (1 << 7)
#define SN3734_ID (0b110 << 4)

uint8_t g_pwm_buffer[SN3734_DRIVER_COUNT][SN3734_PWM_REGISTER_COUNT];
bool    g_pwm_buffer_update_required[SN3734_DRIVER_COUNT]        = {false};
bool    g_scaling_registers_update_required[SN3734_DRIVER_COUNT] = {false};

bool sn3734_write(uint8_t index, uint8_t page, uint8_t reg, uint8_t *data, uint8_t len) {
    static uint8_t spi_transfer_buffer[2] = {0};

    if (index > ARRAY_SIZE(((pin_t[])DRIVER_CS_PINS)) - 1) return false;

    if (!spi_start(cs_pins[index], false, 0, SNLED23751_SPI_DIVISOR)) {
        spi_stop();
        return false;
    }

    spi_transfer_buffer[0] = SN3734_WRITE | SN3734_ID | (page & 0x0F);
    spi_transfer_buffer[1] = reg;

    if (spi_transmit(spi_transfer_buffer, 2) != SPI_STATUS_SUCCESS) {
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

bool sn3734_write_register(uint8_t index, uint8_t page, uint8_t reg, uint8_t data) {
    return sn3734_write(index, page, reg, &data, 1);
}

bool sn3734_write_pwm_buffer(uint8_t index, uint8_t *pwm_buffer) {
    if (g_pwm_buffer_update_required[index]) {
        sn3734_write(index, SN3734_PWM_PAGE, SN3734_PWM_PAGE_PWM_START, pwm_buffer, SN3734_PWM_PAGE_REGISTER_COUNT);
        sn3734_write(index, SN3734_FUNC_PAGE, SN3734_FUNC_PAGE_PWM_START, pwm_buffer + SN3734_PWM_PAGE_REGISTER_COUNT, SN3734_FUNC_PAGE_REGISTER_COUNT);
    }
    g_pwm_buffer_update_required[index] = false;
    return true;
}

void sn3734_init_drivers(void) {
#if defined(LED_DRIVER_SHUTDOWN_PIN)
    setPinOutput(LED_DRIVER_SHUTDOWN_PIN);
    writePinHigh(LED_DRIVER_SHUTDOWN_PIN);
#endif

    spi_init();

    for (uint8_t i = 0; i < SN3734_DRIVER_COUNT; i++)
        sn3734_init(i);
}

void sn3734_init(uint8_t index) {
    setPinOutput(cs_pins[index]);
    writePinHigh(cs_pins[index]);

    // Reset all registers
    sn3734_write_register(index, SN3734_FUNC_PAGE, SN3734_FUNC_REG_RESET, 0xAE);
    // Set to normal mode
    sn3734_write_register(index, SN3734_FUNC_PAGE, SN3734_FUNC_REG_CONFIGURATION, SN3734_NORMAL_MODE | SN3734_PWM_MODE_8 | SN3734_SWS);
    // Set Golbal Current Control Register
    sn3734_write_register(index, SN3734_FUNC_PAGE, SN3734_FUNC_REG_GLOBAL_CURRENT, SN3734_GLOBAL_CURRENT);
    // Set Pull up & Down for SWx CSy
    sn3734_write_register(index, SN3734_FUNC_PAGE, SN3734_FUNC_REG_PULLDOWNUP, SN3734_SWPDR | SN3734_CSPUR);
    // Set Scan rate frequencY
    sn3734_write_register(index, SN3734_FUNC_PAGE, SN3734_FUNC_REG_SRS, (SN3734_SRS & 0b111));

    // Set Scaling register
    uint8_t scaling_reg[SCALING_REG_LEN] = SN2734_SCALING;
    sn3734_write(index, SN3734_FUNC_PAGE, SN3734_SCALING_START, scaling_reg, SCALING_REG_LEN);

    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

void sn3734_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    sn3734_led_t led;
    if (index >= 0 && index < SN3734_LED_COUNT) {
        memcpy_P(&led, (&g_sn3734_leds[index]), sizeof(led));

        if (g_pwm_buffer[led.driver][led.r] == red && g_pwm_buffer[led.driver][led.g] == green && g_pwm_buffer[led.driver][led.b] == blue) {
            return;
        }
        g_pwm_buffer_update_required[led.driver] = true;
        g_pwm_buffer[led.driver][led.r]          = red;
        g_pwm_buffer[led.driver][led.g]          = green;
        g_pwm_buffer[led.driver][led.b]          = blue;
    }
}

void sn3734_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < SN3734_LED_COUNT; i++) {
        sn3734_set_color(i, red, green, blue);
    }
}

void sn3734_update_pwm_buffers(uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        sn3734_write_pwm_buffer(index, g_pwm_buffer[index]);
        /* Update PWM Register*/
        sn3734_write_register(index, SN3734_FUNC_PAGE, SN3734_FUNC_REG_PWM_UPDATE, 0);
    }

    g_pwm_buffer_update_required[index] = false;
}

void sn3734_set_pwm_buffer(const sn3734_led_t *pled, uint8_t red, uint8_t green, uint8_t blue) {
    g_pwm_buffer[pled->driver][pled->r] = red;
    g_pwm_buffer[pled->driver][pled->g] = green;
    g_pwm_buffer[pled->driver][pled->b] = blue;

    g_pwm_buffer_update_required[pled->driver] = true;
}

void sn3734_flush(void) {
    for (uint8_t i = 0; i < SN3734_DRIVER_COUNT; i++)
        sn3734_update_pwm_buffers(i);
}

void sn3734_shutdown(void) {
#if defined(LED_DRIVER_SHUTDOWN_PIN)
    writePinLow(LED_DRIVER_SHUTDOWN_PIN);
#else
    for (uint8_t i = 0; i < SNLED27351_DRIVER_COUNT; i++)
        sn3734_sw_shutdown(i);
#endif
}

void sn3734_exit_shutdown(void) {
#if defined(LED_DRIVER_SHUTDOWN_PIN)
    writePinHigh(LED_DRIVER_SHUTDOWN_PIN);
#else
    for (uint8_t i = 0; i < SNLED27351_DRIVER_COUNT; i++)
        sn3734_sw_return_normal(i);
#endif
}

void sn3734_sw_return_normal(uint8_t index) {
    // Setting LED driver to normal mode
    sn3734_write_register(index, SN3734_FUNC_PAGE, SN3734_FUNC_REG_CONFIGURATION, SN3734_NORMAL_MODE | SN3734_PWM_MODE_8 | SN3734_SWS);
}

void sn3734_sw_shutdown(uint8_t index) {
    // Setting LED driver to shutdown mode
    sn3734_write_register(index, SN3734_FUNC_PAGE, SN3734_FUNC_REG_CONFIGURATION, SN3734_SHUT_DOWN_MODE | SN3734_PWM_MODE_8 | SN3734_SWS);
}
