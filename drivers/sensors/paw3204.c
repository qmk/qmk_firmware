/* Copyright 2021 Gompa (@Gompa)
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

// https://github.com/shinoaliceKabocha/choco60_track/tree/master/keymaps/default

#include "paw3204.h"
#include "wait.h"
#include "debug.h"
#include "gpio.h"
#include "pointing_device.h"

#define PAW3204_REG_PID1 0x00
#define PAW3204_REG_PID2 0x01
#define PAW3204_REG_STAT 0x02
#define PAW3204_REG_X 0x03
#define PAW3204_REG_Y 0x04

#define PAW3204_REG_SETUP 0x06
#define PAW3204_REG_IMGQUAL 0x07
#define PAW3204_REG_IMGREC 0x0E
#define PAW3204_REG_IMGTRASH 0x0D

#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

// CPI values
enum paw3204_cpi_values {
    PAW3204_CPI400,  // 0b000
    PAW3204_CPI500,  // 0b001
    PAW3204_CPI600,  // 0b010
    PAW3204_CPI800,  // 0b011
    PAW3204_CPI1000, // 0b100
    PAW3204_CPI1200, // 0b101
    PAW3204_CPI1600, // 0b110
};

uint8_t paw3204_serial_read(paw3204_config_t* paw3204_config);
void    paw3204_serial_write(paw3204_config_t* paw3204_config, uint8_t reg_addr);
uint8_t paw3204_read_reg(paw3204_config_t* paw3204_config, uint8_t reg_addr);
void    paw3204_write_reg(paw3204_config_t* paw3204_config, uint8_t reg_addr, uint8_t data);


void paw3204_init(const void* config) {
    paw3204_config_t* paw3204_config = (paw3204_config_t*)config;

    gpio_set_pin_output(paw3204_config->sclk);    // setclockpin to output
    gpio_set_pin_input_high(paw3204_config->sdio); // set datapin input high

    paw3204_write_reg(paw3204_config, PAW3204_REG_SETUP, 0x86); // reset sensor and set 1600cpi
    wait_us(5);

    paw3204_read_reg(paw3204_config,0x00); // read id
    paw3204_read_reg(paw3204_config, 0x01); // read id2
    // PAW3204_write_reg(REG_SETUP,0x06);  // dont reset sensor and set cpi 1600
    paw3204_write_reg(paw3204_config, PAW3204_REG_IMGTRASH, 0x32); // write image trashhold
}

uint8_t paw3204_serial_read(paw3204_config_t* paw3204_config) {
    gpio_set_pin_input(paw3204_config->sdio);
    uint8_t byte = 0;

    for (uint8_t i = 0; i < 8; ++i) {
        gpio_write_pin_low(paw3204_config->sclk);
        wait_us(1);

        byte = (byte << 1) | readPin(paw3204_config->sdio);

        gpio_write_pin_high(paw3204_config->sclk);
        wait_us(1);
    }

    return byte;
}

void paw3204_serial_write(paw3204_config_t* paw3204_config, uint8_t data) {
    gpio_write_pin_low(paw3204_config->sdio);
    gpio_set_pin_output(paw3204_config->sdio);

    for (int8_t b = 7; b >= 0; b--) {
        gpio_write_pin_low(paw3204_config->sclk);
        if (data & (1 << b)) {
            gpio_write_pin_high(paw3204_config->sdio);
        } else {
            gpio_write_pin_low(paw3204_config->sdio);
        }
        gpio_write_pin_high(paw3204_config->sclk);
    }

    wait_us(4);
}

report_paw3204_t paw3204_read(paw3204_config_t* paw3204_config) {
    report_paw3204_t data = {0};

    data.isMotion = paw3204_read_reg(paw3204_config, PAW3204_REG_STAT) & (1 << 7); // check for motion only (bit 7 in field)
    data.x        = (int8_t)paw3204_read_reg(paw3204_config, PAW3204_REG_X);
    data.y        = (int8_t)paw3204_read_reg(paw3204_config, PAW3204_REG_Y);

    return data;
}

void paw3204_write_reg(paw3204_config_t* paw3204_config, uint8_t reg_addr, uint8_t data) {
    paw3204_serial_write(paw3204_config, 0b10000000 | reg_addr);
    paw3204_serial_write(paw3204_config, data);
}

uint8_t paw3204_read_reg(paw3204_config_t* paw3204_config, uint8_t reg_addr) {
    paw3204_serial_write(paw3204_config, reg_addr);
    wait_us(5);
    return paw3204_serial_read(paw3204_config);
}

void paw3204_set_cpi(const void* config, uint16_t cpi) {
    paw3204_config_t* paw3204_config = (paw3204_config_t*)config;

    uint8_t cpival = PAW3204_CPI1000;
    if (cpi <= 450) {
        cpival = PAW3204_CPI400;
    } else if (cpi <= 550) {
        cpival = PAW3204_CPI500;
    } else if (cpi <= 700) {
        cpival = PAW3204_CPI600;
    } else if (cpi <= 900) {
        cpival = PAW3204_CPI800;
    } else if (cpi <= 1100) {
        cpival = PAW3204_CPI1000;
    } else if (cpi <= 1400) {
        cpival = PAW3204_CPI1200;
    } else if (cpi > 1400) {
        cpival = PAW3204_CPI1600;
    }
    paw3204_write_reg(paw3204_config, PAW3204_REG_SETUP, cpival);
}

uint16_t paw3204_get_cpi(const void* config) {
    paw3204_config_t* paw3204_config = (paw3204_config_t*)config;

    uint16_t cpival = 1000;

    switch (paw3204_read_reg(paw3204_config, PAW3204_REG_SETUP) & 0b111) {
        case PAW3204_CPI400:
            cpival = 400;
            break;
        case PAW3204_CPI500:
            cpival = 500;
            break;
        case PAW3204_CPI600:
            cpival = 600;
            break;
        case PAW3204_CPI800:
            cpival = 800;
            break;
        case PAW3204_CPI1000:
            cpival = 1000;
            break;
        case PAW3204_CPI1200:
            cpival = 1200;
            break;
        case PAW3204_CPI1600:
            cpival = 1600;
            break;
    }
    return cpival;
}

uint8_t read_pid_paw3204(paw3204_config_t* paw3204_config) {
    return paw3204_read_reg(paw3204_config, PAW3204_REG_PID1);
}

report_mouse_t paw3204_get_report(const void* config) {
    paw3204_config_t* paw3204_config = (paw3204_config_t*)config;
    report_paw3204_t data = paw3204_read(paw3204_config);
    report_mouse_t mouse_report = {0};
    if (data.isMotion) {
        pd_dprintf("Raw ] X: %d, Y: %d\n", data.x, data.y);

        mouse_report.x = data.x;
        mouse_report.y = data.y;
    }

    return mouse_report;
}
