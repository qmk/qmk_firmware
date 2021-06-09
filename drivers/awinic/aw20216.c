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

#define AW_PAGE_FUNCTION 0x00 << 1    // PG0, Function registers
#define AW_PAGE_PWM 0x01 << 1         // PG1, LED PWM control
#define AW_PAGE_SCALING 0x02 << 1     // PG2, LED current scaling control
#define AW_PAGE_PATCHOICE 0x03 << 1   // PG3, Pattern choice?
#define AW_PAGE_PWMSCALING 0x04 << 1  // PG4, LED PWM + Scaling control?

#define AW_WRITE 0
#define AW_READ 1

#define AW_REG_CONFIGURATION 0x00  // PG0
#define AW_REG_GLOBALCURRENT 0x01  // PG0

// Default value of AW_REG_CONFIGURATION
// D7:D4 = 1011, SWSEL (SW1~SW12 active)
// D3 = 0?, reserved (apparently this should be 1 but it doesn't seem to matter)
// D2:D1 = 00, OSDE (open/short detection enable)
// D0 = 0, CHIPEN (write 1 to enable LEDs when hardware enable pulled high)
#define AW_CONFIG_DEFAULT 0b10110000
#define AW_CHIPEN 1

#ifndef AW_SCALING_MAX
#    define AW_SCALING_MAX 150
#endif

#ifndef AW_GLOBAL_CURRENT_MAX
#    define AW_GLOBAL_CURRENT_MAX 150
#endif

#ifndef DRIVER_1_CS
#    define DRIVER_1_CS B13
#endif

#ifndef DRIVER_1_EN
#    define DRIVER_1_EN C13
#endif

uint8_t g_spi_transfer_buffer[20] = {0};
aw_led  g_pwm_buffer[DRIVER_LED_TOTAL];
bool    g_pwm_buffer_update_required[DRIVER_LED_TOTAL];

bool AW20216_write_register(pin_t slave_pin, uint8_t page, uint8_t reg, uint8_t data) {
    // Do we need to call spi_stop() if this fails?
    if (!spi_start(slave_pin, false, 0, 16)) {
        return false;
    }

    g_spi_transfer_buffer[0] = (AWINIC_ID | page | AW_WRITE);
    g_spi_transfer_buffer[1] = reg;
    g_spi_transfer_buffer[2] = data;

    if (spi_transmit(g_spi_transfer_buffer, 3) != SPI_STATUS_SUCCESS) {
        spi_stop();
        return false;
    }
    spi_stop();
    return true;
}

bool AW20216_init_scaling(void) {
    // Set constant current to the max, control brightness with PWM
    aw_led led;
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        led = g_aw_leds[i];
        if (led.driver == 0) {
            AW20216_write_register(DRIVER_1_CS, AW_PAGE_SCALING, led.r, AW_SCALING_MAX);
            AW20216_write_register(DRIVER_1_CS, AW_PAGE_SCALING, led.g, AW_SCALING_MAX);
            AW20216_write_register(DRIVER_1_CS, AW_PAGE_SCALING, led.b, AW_SCALING_MAX);
        }
#ifdef DRIVER_2_CS
        else if (led.driver == 1) {
            AW20216_write_register(DRIVER_2_CS, AW_PAGE_SCALING, led.r, AW_SCALING_MAX);
            AW20216_write_register(DRIVER_2_CS, AW_PAGE_SCALING, led.g, AW_SCALING_MAX);
            AW20216_write_register(DRIVER_2_CS, AW_PAGE_SCALING, led.b, AW_SCALING_MAX);
        }
#endif
    }
    return true;
}

bool AW20216_soft_enable(void) {
    AW20216_write_register(DRIVER_1_CS, AW_PAGE_FUNCTION, AW_REG_CONFIGURATION, AW_CONFIG_DEFAULT | AW_CHIPEN);
#ifdef DRIVER_2_CS
    AW20216_write_register(DRIVER_2_CS, AW_PAGE_FUNCTION, AW_REG_CONFIGURATION, AW_CONFIG_DEFAULT | AW_CHIPEN);
#endif
    return true;
}

void AW20216_update_pwm(int index, uint8_t red, uint8_t green, uint8_t blue) {
    aw_led led = g_aw_leds[index];
    if (led.driver == 0) {
        AW20216_write_register(DRIVER_1_CS, AW_PAGE_PWM, led.r, red);
        AW20216_write_register(DRIVER_1_CS, AW_PAGE_PWM, led.g, green);
        AW20216_write_register(DRIVER_1_CS, AW_PAGE_PWM, led.b, blue);
    }
#ifdef DRIVER_2_CS
    else if (led.driver == 1) {
        AW20216_write_register(DRIVER_2_CS, AW_PAGE_PWM, led.r, red);
        AW20216_write_register(DRIVER_2_CS, AW_PAGE_PWM, led.g, green);
        AW20216_write_register(DRIVER_2_CS, AW_PAGE_PWM, led.b, blue);
    }
#endif
    return;
}

void AW20216_init(void) {
    // All LEDs should start with all scaling and PWM registers as off
    setPinOutput(DRIVER_1_EN);
    writePinHigh(DRIVER_1_EN);
    AW20216_write_register(DRIVER_1_CS, AW_PAGE_FUNCTION, AW_REG_GLOBALCURRENT, AW_GLOBAL_CURRENT_MAX);
#ifdef DRIVER_2_EN
    setPinOutput(DRIVER_2_EN);
    writePinHigh(DRIVER_2_EN);
    AW20216_write_register(DRIVER_2_CS, AW_PAGE_FUNCTION, AW_REG_GLOBALCURRENT, AW_GLOBAL_CURRENT_MAX);
#endif
    AW20216_init_scaling();
    AW20216_soft_enable();
    return;
}

void AW20216_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    g_pwm_buffer[index].r               = red;
    g_pwm_buffer[index].g               = green;
    g_pwm_buffer[index].b               = blue;
    g_pwm_buffer_update_required[index] = true;
    return;
}
void AW20216_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        AW20216_set_color(i, red, green, blue);
    }
    return;
}
void AW20216_update_pwm_buffers(void) {
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (g_pwm_buffer_update_required[i]) {
            AW20216_update_pwm(i, g_pwm_buffer[i].r, g_pwm_buffer[i].g, g_pwm_buffer[i].b);
            g_pwm_buffer_update_required[i] = false;
        }
    }
    return;
}
