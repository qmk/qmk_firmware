/*
 * Copyright 2025 esplo
 * Copyright 2021 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2019 Hiroyuki Okada
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

#include <math.h>
#include "wait.h"
#include "debug.h"
#include "gpio.h"
#include "timer.h"
#include "pointing_device_internal.h"
#include "modular_adns5050.h"

// Registers
// clang-format off
#define REG_PRODUCT_ID     0x00
#define REG_REVISION_ID    0x01
#define REG_MOTION         0x02
#define REG_DELTA_X        0x03
#define REG_DELTA_Y        0x04
#define REG_SQUAL          0x05
#define REG_SHUTTER_UPPER  0x06
#define REG_SHUTTER_LOWER  0x07
#define REG_MAXIMUM_PIXEL  0x08
#define REG_PIXEL_SUM      0x09
#define REG_MINIMUM_PIXEL  0x0a
#define REG_PIXEL_GRAB     0x0b
#define REG_MOUSE_CONTROL  0x0d
#define REG_MOUSE_CONTROL2 0x19
#define REG_LED_DC_MODE    0x22
#define REG_CHIP_RESET     0x3a
#define REG_PRODUCT_ID2    0x3e
#define REG_INV_REV_ID     0x3f
#define REG_MOTION_BURST   0x63
// clang-format on

const pointing_device_driver_t modular_adns5050_pointing_device_driver = {
    .init       = modular_adns5050_init,
    .get_report = modular_adns5050_get_all_report,
    .set_cpi    = modular_adns5050_set_all_cpi,
    .get_cpi    = modular_adns5050_get_all_cpi,
};

// set zero for all elements
static bool connected[NUM_MODULAR_ADNS5050]    = {false};
static bool powered_down[NUM_MODULAR_ADNS5050] = {false};

const pin_t SCLK_PINS[]  = MODULAR_ADNS5050_SCLK_PINS;
const pin_t SDIO_PINS[]  = MODULAR_ADNS5050_SDIO_PINS;
const pin_t CS_PINS[]    = MODULAR_ADNS5050_CS_PINS;
const pin_t RESET_PINS[] = MODULAR_ADNS5050_RESET_PINS;

// angle for each sensor.
uint16_t angle[NUM_MODULAR_ADNS5050] = {0};
uint32_t trackball_timeout_length    = 5 * 60 * 1000; // default: 5 min
uint32_t trackball_timeout           = 0;

void modular_adns5050_init(void) {
    for (uint8_t i = 0; i < NUM_MODULAR_ADNS5050; i++) {
        // Initialize the ADNS serial pins.
        gpio_set_pin_output(SCLK_PINS[i]);
        gpio_set_pin_output(SDIO_PINS[i]);
        gpio_set_pin_output(CS_PINS[i]);

        // RESET pin must be high
        gpio_set_pin_output(RESET_PINS[i]);
        gpio_write_pin_high(RESET_PINS[i]);

        powered_down[i] = true;
        connected[i]    = false;
    }

    modular_adns5050_wake_up_all(false);
}

report_mouse_t modular_adns5050_get_all_report(report_mouse_t mouse_report) {
    for (uint8_t i = 0; i < NUM_MODULAR_ADNS5050; i++) {
        report_mouse_t m = modular_adns5050_get_report(i, mouse_report);
        mouse_report.x += m.x;
        mouse_report.y += m.y;
    }
    modular_adns5050_check_timeout();

    return mouse_report;
}

uint16_t modular_adns5050_get_all_cpi(void) {
    // get the maximum CPI since the CPI should be the same amoung all sensors
    uint16_t maxCPI = 0;
    for (uint8_t i = 0; i < NUM_MODULAR_ADNS5050; i++) {
        uint16_t cpi = modular_adns5050_get_cpi(i);
        maxCPI       = (maxCPI > cpi) ? maxCPI : cpi;
    }
    return maxCPI;
}

void modular_adns5050_set_all_cpi(uint16_t cpi) {
    for (uint8_t i = 0; i < NUM_MODULAR_ADNS5050; i++) {
        modular_adns5050_set_cpi(i, cpi);
    }
}

void modular_adns5050_power_down_all(void) {
    for (uint8_t i = 0; i < NUM_MODULAR_ADNS5050; i++) {
        if (powered_down[i]) {
            continue;
        }
        modular_adns5050_power_down(i);
    }
}

void modular_adns5050_wake_up_all(bool connected_only) {
    for (uint8_t i = 0; i < NUM_MODULAR_ADNS5050; i++) {
        modular_adns5050_wake_up(i, connected_only);
    }
}

void modular_adns5050_check_timeout(void) {
    if (trackball_timeout_length == 0) {
        return;
    }
    if (timer_expired32(timer_read32(), trackball_timeout)) {
        modular_adns5050_power_down_all();
    }
}

uint8_t modular_adns5050_get_connected_count(void) {
    uint8_t count = 0;
    for (uint8_t i = 0; i < NUM_MODULAR_ADNS5050; i++) {
        if (connected[i]) {
            count++;
        }
    }
    return count;
}

void modular_adns5050_set_led_off_length(uint32_t length_ms) {
    trackball_timeout_length = length_ms;
}

void modular_adns5050_wake_up(uint8_t index, bool connected_only) {
    trackball_timeout = timer_read32() + trackball_timeout_length;

    // skip if the sensor is already active
    if (!powered_down[index]) {
        return;
    }

    if (connected_only && !connected[index]) {
        return;
    }

    // reboot the adns.
    // if the adns hasn't initialized yet, this is harmless.
    modular_adns5050_write_reg(index, REG_CHIP_RESET, 0x5a);

    // wait maximum time before adns is ready.
    // this ensures that the adns is actuall ready after reset.
    wait_ms(55);

    // check if ADNS-5050 is connected
    // Product_ID must be 0x12
    // if you read this value before initialized, this value is 0x09 AFAIK
    uint8_t product_id = modular_adns5050_read_reg(index, REG_PRODUCT_ID);
    if (product_id != 0x12) {
        powered_down[index] = true;
        return;
    }

    powered_down[index] = false;
    connected[index]    = true;

    // read a burst from the adns and then discard it.
    // gets the adns ready for write commands
    // (for example, setting the dpi).
    modular_adns5050_read_burst(index);
}

// Perform a synchronization with the ADNS.
// Just as with the serial protocol, this is used by the slave to send a
// synchronization signal to the master.
void modular_adns5050_sync(uint8_t index) {
    gpio_write_pin_low(CS_PINS[index]);
    wait_us(1);
    gpio_write_pin_high(CS_PINS[index]);
}

void modular_adns5050_cs_select(uint8_t index) {
    gpio_write_pin_low(CS_PINS[index]);
}

void modular_adns5050_cs_deselect(uint8_t index) {
    gpio_write_pin_high(CS_PINS[index]);
}

uint8_t modular_adns5050_serial_read(uint8_t index) {
    gpio_set_pin_input(SDIO_PINS[index]);
    uint8_t byte = 0;

    for (uint8_t i = 0; i < 8; ++i) {
        gpio_write_pin_low(SCLK_PINS[index]);
        wait_us(1);

        byte = (byte << 1) | gpio_read_pin(SDIO_PINS[index]);

        gpio_write_pin_high(SCLK_PINS[index]);
        wait_us(1);
    }

    return byte;
}

void modular_adns5050_serial_write(uint8_t index, uint8_t data) {
    gpio_set_pin_output(SDIO_PINS[index]);

    for (int8_t b = 7; b >= 0; b--) {
        gpio_write_pin_low(SCLK_PINS[index]);

        if (data & (1 << b))
            gpio_write_pin_high(SDIO_PINS[index]);
        else
            gpio_write_pin_low(SDIO_PINS[index]);

        wait_us(2);

        gpio_write_pin_high(SCLK_PINS[index]);
    }

    // tSWR. See page 15 of the ADNS spec sheet.
    // Technically, this is only necessary if the next operation is an SDIO
    // read. This is not guaranteed to be the case, but we're being lazy.
    wait_us(4);

    // Note that tSWW is never necessary. All write operations require at
    // least 32us, which exceeds tSWW, so there's never a need to wait for it.
}

// Read a byte of data from a register on the ADNS.
// Don't forget to use the register map (as defined in the header file).
uint8_t modular_adns5050_read_reg(uint8_t index, uint8_t reg_addr) {
    modular_adns5050_cs_select(index);

    modular_adns5050_serial_write(index, reg_addr);

    // We don't need a minimum tSRAD here. That's because a 4ms wait time is
    // already included in adns5050_serial_write(), so we're good.
    // See page 10 and 15 of the ADNS spec sheet.
    // wait_us(4);

    uint8_t byte = modular_adns5050_serial_read(index);

    // tSRW & tSRR. See page 15 of the ADNS spec sheet.
    // Technically, this is only necessary if the next operation is an SDIO
    // read or write. This is not guaranteed to be the case.
    // Honestly, this wait could probably be removed.
    wait_us(1);

    modular_adns5050_cs_deselect(index);

    return byte;
}

void modular_adns5050_write_reg(uint8_t index, uint8_t reg_addr, uint8_t data) {
    modular_adns5050_cs_select(index);
    modular_adns5050_serial_write(index, 0b10000000 | reg_addr);
    modular_adns5050_serial_write(index, data);
    modular_adns5050_cs_deselect(index);
}

// Convert a two's complement byte from an unsigned data type into a signed
// data type.
int8_t modular_convert_twoscomp(uint8_t data) {
    if ((data & 0x80) == 0x80) {
        return -128 + (data & 0x7F);
    } else {
        return data;
    }
}

report_modular_adns5050_t modular_adns5050_read_burst(uint8_t index) {
    modular_adns5050_cs_select(index);

    report_modular_adns5050_t data;
    data.dx = 0;
    data.dy = 0;

    if (powered_down[index]) {
        return data;
    }

    modular_adns5050_serial_write(index, REG_MOTION_BURST);

    // We don't need a minimum tSRAD here. That's because a 4ms wait time is
    // already included in adns5050_serial_write(), so we're good.
    // See page 10 and 15 of the ADNS spec sheet.
    // wait_us(4);

    uint8_t x = modular_adns5050_serial_read(index);
    uint8_t y = modular_adns5050_serial_read(index);

    // Burst mode returns a bunch of other shit that we don't really need.
    // Setting CS to high ends burst mode early.
    modular_adns5050_cs_deselect(index);

    data.dx = modular_convert_twoscomp(x);
    data.dy = modular_convert_twoscomp(y);

    return data;
}

// Don't forget to use the definitions for CPI in the header file.
void modular_adns5050_set_cpi(uint8_t index, uint16_t cpi) {
    uint8_t cpival = constrain((cpi / 125), 0x1, 0xD); // limits to 0--119

    modular_adns5050_write_reg(index, REG_MOUSE_CONTROL2, 0b10000 | cpival);
}

uint16_t modular_adns5050_get_cpi(uint8_t index) {
    uint8_t cpival = modular_adns5050_read_reg(index, REG_MOUSE_CONTROL2);
    return (uint16_t)((cpival & 0b10000) * 125);
}

bool modular_adns5050_check_signature(uint8_t index) {
    uint8_t pid  = modular_adns5050_read_reg(index, REG_PRODUCT_ID);
    uint8_t rid  = modular_adns5050_read_reg(index, REG_REVISION_ID);
    uint8_t pid2 = modular_adns5050_read_reg(index, REG_PRODUCT_ID2);

    return (pid == 0x12 && rid == 0x01 && pid2 == 0x26);
}

void modular_adns5050_power_down(uint8_t index) {
    if (!powered_down[index]) {
        powered_down[index] = true;
        modular_adns5050_write_reg(index, REG_MOUSE_CONTROL, 0b10);
        dprintf("mouse %d powered down\n", index);
    }
}

report_mouse_t modular_adns5050_get_report(uint8_t index, report_mouse_t mouse_report) {
    report_modular_adns5050_t data = modular_adns5050_read_burst(index);

    if (data.dx != 0 || data.dy != 0) {
        // use true just to update the timeout
        modular_adns5050_wake_up(index, true);

        pd_dprintf("[%X] Raw ] X: %d, Y: %d\n", i, data.dx, data.dy);
        double            rad   = angle[index] * (M_PI / 180);
        mouse_xy_report_t x_rev = cos(rad) * data.dx + -sin(rad) * data.dy;
        mouse_xy_report_t y_rev = sin(rad) * data.dx + cos(rad) * data.dy;
        mouse_report.x += x_rev;
        mouse_report.y += y_rev;
    }

    return mouse_report;
}

void modular_adns5050_set_angle(uint8_t index, uint16_t value) {
    angle[index] = value;
}

void modular_adns5050_add_angle(uint8_t index, int16_t value) {
    angle[index] = (360 + angle[index] + value) % 360;
}

uint16_t modular_adns5050_get_angle(uint8_t index) {
    return angle[index];
}
