/* Copyright 2024 Colin Lam (Ploopy Corporation)
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

#include "paw3222.h"
#include "wait.h"
#include "gpio.h"
#include "spi_master.h"
#include "pointing_device_internal.h"

#define MSB1 0x80
#define MSB0 0x7F

const pointing_device_driver_t paw3222_pointing_device_driver = {
    .init       = paw3222_init,
    .get_report = paw3222_get_report,
    .set_cpi    = paw3222_set_cpi,
    .get_cpi    = paw3222_get_cpi,
};

// Convert a 12-bit twos complement binary-represented number into a
// signed 12-bit integer.
static int16_t convert_twoscomp_12(uint16_t data) {
    if ((data & 0x800) == 0x800)
        return -2048 + (data & 0x7FF);
    else
        return data;
}

void paw3222_write(uint8_t reg_addr, uint8_t data) {
    spi_start(PAW3222_CS_PIN, false, 3, PAW3222_SPI_DIVISOR);
    wait_us(1); // Tncs_lead
    spi_write(reg_addr | MSB1);
    spi_write(data);
    wait_us(1); // Tncs_lag
    spi_stop();
}

uint8_t paw3222_read(uint8_t reg_addr) {
    spi_start(PAW3222_CS_PIN, false, 3, PAW3222_SPI_DIVISOR);
    wait_us(1); // Tncs_lead
    spi_write(reg_addr & MSB0);
    wait_us(10); // Tprep_rd
    uint8_t data = spi_read();
    wait_us(1); // Tncs_lag
    spi_stop();

    return data;
}

bool paw3222_init(void) {
    gpio_set_pin_output(PAW3222_CS_PIN);

    // CS must be kept low at power-up stage for at least 1ms
    gpio_write_pin_low(PAW3222_CS_PIN);
    wait_ms(10);
    gpio_write_pin_high(PAW3222_CS_PIN);

    spi_init();

    // reboot
    paw3222_write(0x06, 0x80);
    wait_ms(50);

    if (!paw3222_check_signature()) {
        return false;
    }

    // initialize
    paw3222_write(0x09, 0x5A);
    paw3222_write(0x0D, 0x23);
    paw3222_write(0x0E, 0x24);
    paw3222_write(0x19, 0x1C);
    paw3222_write(0x05, 0xA1);
    paw3222_write(0x2B, 0x6D);
    paw3222_write(0x30, 0x2E);
    paw3222_write(0x5C, 0xDF);
    paw3222_write(0x7F, 0x01);
    paw3222_write(0x06, 0x14);
    paw3222_write(0x31, 0x25);
    paw3222_write(0x34, 0xC4);
    paw3222_write(0x36, 0xCC);
    paw3222_write(0x37, 0x42);
    paw3222_write(0x38, 0x01);
    paw3222_write(0x3A, 0x76);
    paw3222_write(0x3B, 0x34);
    paw3222_write(0x42, 0x39);
    paw3222_write(0x43, 0xF2);
    paw3222_write(0x44, 0x39);
    paw3222_write(0x45, 0xF0);
    paw3222_write(0x46, 0x12);
    paw3222_write(0x47, 0x39);
    paw3222_write(0x48, 0xE3);
    paw3222_write(0x49, 0x48);
    paw3222_write(0x4A, 0xD3);
    paw3222_write(0x4B, 0x98);
    paw3222_write(0x64, 0x46);
    paw3222_write(0x71, 0x28);
    paw3222_write(0x72, 0x28);
    paw3222_write(0x7F, 0x00);
    paw3222_write(0x09, 0x00);

    // read a burst, then discard
    paw3222_read_burst();

    return true;
}

report_paw3222_t paw3222_read_burst(void) {
    report_paw3222_t report = {0};

    uint8_t motion = paw3222_read(0x02);
    if ((motion & MSB1) == MSB1) {
        // Motion detected
        uint16_t dx     = (uint16_t)paw3222_read(0x03);
        uint16_t dy     = (uint16_t)paw3222_read(0x04);
        uint16_t dxy_hi = (uint16_t)paw3222_read(0x12);

        dx = dx | ((dxy_hi & 0xF0) << 4);
        dy = dy | ((dxy_hi & 0x0F) << 8);

        report.dx = convert_twoscomp_12(dx);
        report.dy = convert_twoscomp_12(dy);
    }

    return report;
}

void paw3222_set_cpi(uint16_t cpi) {
    uint16_t cpival   = (cpi) < (480) ? (480) : ((cpi) > (4020) ? (4020) : (cpi));
    uint8_t  cpival_x = (cpival + (30 / 2)) / 30;
    uint8_t  cpival_y = (cpival + (29 / 2)) / 29;

    paw3222_write(0x09, 0x5A);
    paw3222_write(0x0D, cpival_x);
    paw3222_write(0x0E, cpival_y);
    paw3222_write(0x09, 0x00);
}

uint16_t paw3222_get_cpi(void) {
    uint8_t cpival = paw3222_read(0x0D);
    return (uint16_t)(cpival * 30);
}

report_mouse_t paw3222_get_report(report_mouse_t mouse_report) {
    report_paw3222_t data = paw3222_read_burst();

    if (data.dx != 0 || data.dy != 0) {
        pd_dprintf("Raw ] X: %d, Y: %d\n", data.dx, data.dy);
        mouse_report.x = CONSTRAIN_HID_XY(data.dx);
        mouse_report.y = CONSTRAIN_HID_XY(data.dy);
    }

    return mouse_report;
}

bool paw3222_check_signature(void) {
    uint8_t checkval_1 = paw3222_read(0x00);
    uint8_t checkval_2 = paw3222_read(0x01);

    return (checkval_1 == 0x30 && checkval_2 == 0x02);
}
