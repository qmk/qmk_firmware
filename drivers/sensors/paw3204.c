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

#define REG_PID1 0x00
#define REG_PID2 0x01
#define REG_STAT 0x02
#define REG_X 0x03
#define REG_Y 0x04

#define REG_SETUP 0x06
#define REG_IMGQUAL 0x07
#define REG_IMGREC 0x0E
#define REG_IMGTRASH 0x0D

#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

// CPI values
enum cpi_values {
    CPI400,  // 0b000
    CPI500,  // 0b001
    CPI600,  // 0b010
    CPI800,  // 0b011
    CPI1000, // 0b100
    CPI1200, // 0b101
    CPI1600, // 0b110
};

uint8_t paw3204_serial_read(void);
void    paw3204_serial_write(uint8_t reg_addr);
uint8_t paw3204_read_reg(uint8_t reg_addr);
void    paw3204_write_reg(uint8_t reg_addr, uint8_t data);

void paw3204_init(void) {
    setPinOutput(PAW3204_SCLK_PIN);    // setclockpin to output
    setPinInputHigh(PAW3204_SDIO_PIN); // set datapin input high

    paw3204_write_reg(REG_SETUP, 0x86); // reset sensor and set 1600cpi
    wait_us(5);

    paw3204_read_reg(0x00); // read id
    paw3204_read_reg(0x01); // read id2
    // PAW3204_write_reg(REG_SETUP,0x06);  // dont reset sensor and set cpi 1600
    paw3204_write_reg(REG_IMGTRASH, 0x32); // write image trashhold
}

uint8_t paw3204_serial_read(void) {
    setPinInput(PAW3204_SDIO_PIN);
    uint8_t byte = 0;

    for (uint8_t i = 0; i < 8; ++i) {
        writePinLow(PAW3204_SCLK_PIN);
        wait_us(1);

        byte = (byte << 1) | readPin(PAW3204_SDIO_PIN);

        writePinHigh(PAW3204_SCLK_PIN);
        wait_us(1);
    }

    return byte;
}

void paw3204_serial_write(uint8_t data) {
    writePinLow(PAW3204_SDIO_PIN);
    setPinOutput(PAW3204_SDIO_PIN);

    for (int8_t b = 7; b >= 0; b--) {
        writePinLow(PAW3204_SCLK_PIN);
        if (data & (1 << b)) {
            writePinHigh(PAW3204_SDIO_PIN);
        } else {
            writePinLow(PAW3204_SDIO_PIN);
        }
        writePinHigh(PAW3204_SCLK_PIN);
    }

    wait_us(4);
}

report_paw3204_t paw3204_read(void) {
    report_paw3204_t data = {0};

    data.isMotion = paw3204_read_reg(REG_STAT) & (1 << 7); // check for motion only (bit 7 in field)
    data.x        = (int8_t)paw3204_read_reg(REG_X);
    data.y        = (int8_t)paw3204_read_reg(REG_Y);

    return data;
}

void paw3204_write_reg(uint8_t reg_addr, uint8_t data) {
    paw3204_serial_write(0b10000000 | reg_addr);
    paw3204_serial_write(data);
}

uint8_t paw3204_read_reg(uint8_t reg_addr) {
    paw3204_serial_write(reg_addr);
    wait_us(5);
    return paw3204_serial_read();
}

void paw3204_set_cpi(uint16_t cpi) {
    uint8_t cpival = CPI1000;
    if (cpi <= 450) {
        cpival = CPI400;
    } else if (cpi <= 550) {
        cpival = CPI500;
    } else if (cpi <= 700) {
        cpival = CPI600;
    } else if (cpi <= 900) {
        cpival = CPI800;
    } else if (cpi <= 1100) {
        cpival = CPI1000;
    } else if (cpi <= 1400) {
        cpival = CPI1200;
    } else if (cpi > 1400) {
        cpival = CPI1600;
    }
    paw3204_write_reg(REG_SETUP, cpival);
}

uint16_t paw3204_get_cpi(void) {
    uint16_t cpival = 1000;

    switch (paw3204_read_reg(REG_SETUP) & 0b111) {
        case CPI400:
            cpival = 400;
            break;
        case CPI500:
            cpival = 500;
            break;
        case CPI600:
            cpival = 600;
            break;
        case CPI800:
            cpival = 800;
            break;
        case CPI1000:
            cpival = 1000;
            break;
        case CPI1200:
            cpival = 1200;
            break;
        case CPI1600:
            cpival = 1600;
            break;
    }
    return cpival;
}

uint8_t read_pid_paw3204(void) {
    return paw3204_read_reg(REG_PID1);
}
