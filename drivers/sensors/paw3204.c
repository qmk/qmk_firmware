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

#include "paw3204.h"
#include "wait.h"
#include "debug.h"
#include "gpio.h"

uint8_t datatogglestate;
#define REG_PID1 0x00
#define REG_PID2 0x01
#define REG_STAT 0x02
#define REG_X 0x03
#define REG_Y 0x04

#define REG_SETUP 0x06
#define REG_IMGQUAL 0x07
#define REG_IMGREC 0x0E
#define REG_IMGTRASH 0x0D

void PAW3204_init(void) {
    setPinOutput(PAW3204_SCLK);    // setclockpin to output
    setPinInputHigh(PAW3204_DATA); // set datapin input high

    PAW3204_write_reg(REG_SETUP, 0x86); // reset sensor and set 1600cpi
    wait_us(5);

    PAW3204_read_reg(0x00); // read id
    PAW3204_read_reg(0x01); // read id2
    // PAW3204_write_reg(REG_SETUP,0x06);  // dont reset sensor and set cpi 1600
    PAW3204_write_reg(REG_IMGTRASH, 0x32); // write image trashhold
}

uint8_t PAW3204_serial_read(void) {
    setPinInput(PAW3204_DATA);
    uint8_t byte = 0;

    for (uint8_t i = 0; i < 8; ++i) {
        writePinLow(PAW3204_SCLK);
        wait_us(1);

        byte = (byte << 1) | readPin(PAW3204_DATA);

        writePinHigh(PAW3204_SCLK);
        wait_us(1);
    }

    return byte;
}

void PAW3204_serial_write(uint8_t data) {
    datatogglestate = readPin(PAW3204_DATA);
    if (datatogglestate == 1) {
        writePinLow(PAW3204_DATA);
    } else {
        writePinLow(PAW3204_DATA);
    }
    setPinOutput(PAW3204_DATA);

    for (int8_t b = 7; b >= 0; b--) {
        writePinLow(PAW3204_SCLK);
        if (data & (1 << b))
            writePinHigh(PAW3204_DATA);
        else
            writePinLow(PAW3204_DATA);
        // wait_us(2);
        writePinHigh(PAW3204_SCLK);
    }

    wait_us(4);
}

int8_t convert_twoscomp(uint8_t data) {
    if ((data & 0x80) == 0x80)
        return -128 + (data & 0x7F);
    else
        return data;
}

report_paw3204_t PAW3204_read(void) {
    report_paw3204_t data;
    uint8_t          pid  = read_pid_paw3204();
    uint8_t          stat = PAW3204_read_reg(REG_STAT);
    if (pid == 0x30 && (stat == 0x84 || stat == 0x86)) {
        data.x = convert_twoscomp(PAW3204_read_reg(REG_X));
        data.y = convert_twoscomp(PAW3204_read_reg(REG_Y));
    }

    return data;
}

void PAW3204_write_reg(uint8_t reg_addr, uint8_t data) {
    PAW3204_serial_write(0b10000000 | reg_addr);
    PAW3204_serial_write(data);
}

uint8_t PAW3204_read_reg(uint8_t reg_addr) {
    PAW3204_serial_write(reg_addr);

    wait_us(5);

    uint8_t byte = PAW3204_serial_read();

    return byte;
}

void PAW3204_set_cpi(uint16_t cpi) {
    uint8_t cpival = constrain((cpi / 200) - 2, 0x0, 0x6);
    PAW3204_write_reg(REG_SETUP, cpival);
}

uint16_t PAW3204_get_cpi(void) {
    uint8_t cpival = PAW3204_read_reg(REG_SETUP);
    return (uint16_t)(cpival + 2) * 200;
}

uint8_t read_pid_paw3204(void) {
    uint8_t byte = PAW3204_read_reg(REG_PID1);
    return byte;
}