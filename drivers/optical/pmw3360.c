/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2020 Ploopy Corporation
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

#include "pmw3360.h"
#ifndef PMW3360_FIRMWARE_H
#    include "pmw3360_firmware.h"
#endif

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif
bool _inBurst = false;

#ifndef PMW3360_CPI
#    define PMW3360_CPI 1600
#endif

#ifdef __AVR__
#    ifndef SPI_DIVISOR
#        define SPI_DIVISOR 8
#    endif
#    ifndef SPI_CS_PIN
#        define SPI_CS_PIN SPI_SS_PIN
#    endif
#else
#    ifndef SPI_DIVISOR
#        error SPI_DIVISOR not defined. Please define the divider.
#    endif
#    ifndef SPI_CS_PIN
#        error No Cable Select pin defined. Please define SPI_CS_PIN
#    endif
#endif

#ifndef ROTATIONAL_TRANSFORM_ANGLE
#    define ROTATIONAL_TRANSFORM_ANGLE 0x00
#endif

#ifdef CONSOLE_ENABLE
void print_byte(uint8_t byte) { dprintf("%c%c%c%c%c%c%c%c|", (byte & 0x80 ? '1' : '0'), (byte & 0x40 ? '1' : '0'), (byte & 0x20 ? '1' : '0'), (byte & 0x10 ? '1' : '0'), (byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'), (byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0')); }
#endif

// some advanced SPI functions.  Would port to spi_master, but some of this is VERY dependant on pmw3389 code

bool spi_start_pmw3360(void) {
    bool status = spi_start(SPI_CS_PIN, false, 3, SPI_DIVISOR);
    wait_us(1);
    return status;
}

void spi_stop_pmw3360(void) {
    wait_us(1);
    spi_stop();
}

spi_status_t spi_write_pmw3360(uint8_t reg_addr, uint8_t data) {
    if (reg_addr != REG_Motion_Burst) {
        _inBurst = false;
    }

    spi_start_pmw3360();
    // send address of the register, with MSBit = 1 to indicate it's a write
    spi_status_t status = spi_write(reg_addr | 0x80);
    status = spi_write(data);

    // tSCLK-NCS for write operation
    wait_us(20);

    // tSWW/tSWR (=120us) minus tSCLK-NCS. Could be shortened, but is looks like a safe lower bound
    wait_us(100);
    spi_stop();
    return status;
}

uint8_t spi_read_pmw3360(uint8_t reg_addr) {
    spi_start_pmw3360();
    // send adress of the register, with MSBit = 0 to indicate it's a read
    spi_write(reg_addr & 0x7f);

    uint8_t data = spi_read();

    // tSCLK-NCS for read operation is 120ns
    wait_us(1);

    //  tSRW/tSRR (=20us) minus tSCLK-NCS
    wait_us(19);

    spi_stop();
    return data;
}

void pmw3360_set_cpi(uint16_t cpi) {
    int cpival = constrain((cpi / 100) - 1, 0, 0x77);  // limits to 0--119

    spi_start_pmw3360();
    spi_write_pmw3360(REG_Config1, cpival);
    spi_stop();
}

bool pmw3360_spi_init(void) {
    spi_init();
    _inBurst = false;

    spi_stop();
    spi_start_pmw3360();
    spi_stop();

    spi_write_pmw3360(REG_Shutdown, 0xb6);  // Shutdown first
    wait_ms(300);

    spi_start_pmw3360();
    wait_us(40);
    spi_stop_pmw3360();
    wait_us(40);

    spi_write_pmw3360(REG_Power_Up_Reset, 0x5a);
    wait_ms(50);

    spi_read_pmw3360(REG_Motion);
    spi_read_pmw3360(REG_Delta_X_L);
    spi_read_pmw3360(REG_Delta_X_H);
    spi_read_pmw3360(REG_Delta_Y_L);
    spi_read_pmw3360(REG_Delta_Y_H);

    pmw3360_upload_firmware();

    spi_stop_pmw3360();

    wait_ms(10);
    pmw3360_set_cpi(PMW3360_CPI);

    wait_ms(1);

    return pmw3360_check_signature();
}

void pmw3360_upload_firmware(void) {
    spi_write_pmw3360(REG_Config2, 0x00);

    spi_write_pmw3360(REG_Angle_Tune, constrain(ROTATIONAL_TRANSFORM_ANGLE, -30, 30));

    spi_write_pmw3360(REG_SROM_Enable, 0x1d);

    wait_ms(10);

    spi_write_pmw3360(REG_SROM_Enable, 0x18);

    spi_start_pmw3360();
    spi_write(REG_SROM_Load_Burst | 0x80);
    wait_us(15);

    unsigned char c;
    for (int i = 0; i < firmware_length; i++) {
        c = (unsigned char)pgm_read_byte(firmware_data + i);
        spi_write(c);
        wait_us(15);
    }
    wait_us(200);

    spi_read_pmw3360(REG_SROM_ID);

    spi_write_pmw3360(REG_Config2, 0x00);

    spi_stop();
    wait_ms(10);
}

bool pmw3360_check_signature(void) {
    uint8_t pid      = spi_read_pmw3360(REG_Product_ID);
    uint8_t iv_pid   = spi_read_pmw3360(REG_Inverse_Product_ID);
    uint8_t SROM_ver = spi_read_pmw3360(REG_SROM_ID);
    return (pid == PMW3360_PRODUCT_ID && iv_pid == PMW3360_INVERSE_PRODUCT_ID && SROM_ver == PMW3360_SROM_VERSION);
}

report_pmw_t pmw3360_read_burst(void) {
    if (!_inBurst) {
#ifdef CONSOLE_ENABLE
        dprintf("burst on");
#endif
        spi_write_pmw3360(REG_Motion_Burst, 0x00);
        _inBurst = true;
    }

    spi_start_pmw3360();
    spi_write(REG_Motion_Burst);
    wait_us(35);  // waits for tSRAD

    report_pmw_t data;
    data.motion = 0;
    data.dx     = 0;
    data.mdx    = 0;
    data.dy     = 0;
    data.mdx    = 0;

    data.motion = spi_read();
    spi_write(0x00);  // skip Observation
    data.dx  = spi_read();
    data.mdx = spi_read();
    data.dy  = spi_read();
    data.mdy = spi_read();

    spi_stop();

#ifdef CONSOLE_ENABLE
    print_byte(data.motion);
    print_byte(data.dx);
    print_byte(data.mdx);
    print_byte(data.dy);
    print_byte(data.mdy);
    dprintf("\n");
#endif

    data.isMotion    = (data.motion & 0x80) != 0;
    data.isOnSurface = (data.motion & 0x08) == 0;
    data.dx |= (data.mdx << 8);
    data.dx = data.dx * -1;
    data.dy |= (data.mdy << 8);
    data.dy = data.dy * -1;

    spi_stop();

    if (data.motion & 0b111) {  // panic recovery, sometimes burst mode works weird.
        _inBurst = false;
    }

    return data;
}
