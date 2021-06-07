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

#ifdef POINTING_DEVICE_ENABLE

#include "wait.h"
#include "debug.h"
#include "print.h"
#include "pmw3360.h"
#include "pmw3360_firmware.h"

bool _inBurst = false;

#ifndef PMW_CPI
#    define PMW_CPI 1600
#endif
#ifndef SPI_DIVISOR
#    define SPI_DIVISOR 2
#endif
#ifndef ROTATIONAL_TRANSFORM_ANGLE
#    define ROTATIONAL_TRANSFORM_ANGLE 0x00
#endif

void print_byte(uint8_t byte) { dprintf("%c%c%c%c%c%c%c%c|", (byte & 0x80 ? '1' : '0'), (byte & 0x40 ? '1' : '0'), (byte & 0x20 ? '1' : '0'), (byte & 0x10 ? '1' : '0'), (byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'), (byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0')); }

bool spi_start_adv(void) {
    bool status = spi_start(SPI_SS_PIN, false, 3, SPI_DIVISOR);
    wait_us(1);
    return status;
}

void spi_stop_adv(void) {
    wait_us(1);
    spi_stop();
}

spi_status_t spi_write_adv(uint8_t reg_addr, uint8_t data) {
    if (reg_addr != REG_Motion_Burst) {
        _inBurst = false;
    }

    spi_start_adv();
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

uint8_t spi_read_adv(uint8_t reg_addr) {
    spi_start_adv();
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

void pmw_set_cpi(uint16_t cpi) {
    int cpival = constrain((cpi / 100) - 1, 0, 0x77);  // limits to 0--119

    spi_start_adv();
    spi_write_adv(REG_Config1, cpival);
    spi_stop();
}

bool pmw_spi_init(void) {
    spi_init();
    _inBurst = false;

    spi_stop();
    spi_start_adv();
    spi_stop();

    spi_write_adv(REG_Shutdown, 0xb6); // Shutdown first
    wait_ms(300);

    spi_start_adv();
    wait_us(40);
    spi_stop_adv();
    wait_us(40);

    spi_write_adv(REG_Power_Up_Reset, 0x5a);
    wait_ms(50);

    spi_read_adv(REG_Motion);
    spi_read_adv(REG_Delta_X_L);
    spi_read_adv(REG_Delta_X_H);
    spi_read_adv(REG_Delta_Y_L);
    spi_read_adv(REG_Delta_Y_H);

    pmw_upload_firmware();

    spi_stop_adv();

    wait_ms(10);
    pmw_set_cpi(PMW_CPI);

    wait_ms(1);

    return pmw_check_signature();
}

void pmw_upload_firmware(void) {
    spi_write_adv(REG_Config2, 0x00);

    spi_write_adv(REG_Angle_Tune, constrain(ROTATIONAL_TRANSFORM_ANGLE, -30, 30));

    spi_write_adv(REG_SROM_Enable, 0x1d);

    wait_ms(10);

    spi_write_adv(REG_SROM_Enable, 0x18);

    spi_start_adv();
    spi_write(REG_SROM_Load_Burst | 0x80);
    wait_us(15);

    unsigned char c;
    for (int i = 0; i < firmware_length; i++) {
        c = (unsigned char)pgm_read_byte(firmware_data + i);
        spi_write(c);
        wait_us(15);
    }
    wait_us(200);

    spi_read_adv(REG_SROM_ID);

    spi_write_adv(REG_Config2, 0x00);

    spi_stop();
    wait_ms(10);
}

bool pmw_check_signature(void) {
    uint8_t pid      = spi_read_adv(REG_Product_ID);
    uint8_t iv_pid   = spi_read_adv(REG_Inverse_Product_ID);
    uint8_t SROM_ver = spi_read_adv(REG_SROM_ID);
    return (pid == 0x42 && iv_pid == 0xBD && SROM_ver == 0x04);  // signature for SROM 0x04
}

report_pmw_t pmw_read_burst(void) {
    if (!_inBurst) {
        dprintf("burst on");
        spi_write_adv(REG_Motion_Burst, 0x00);
        _inBurst = true;
    }

    spi_start_adv();
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

    print_byte(data.motion);
    print_byte(data.dx);
    print_byte(data.mdx);
    print_byte(data.dy);
    print_byte(data.mdy);
    dprintf("\n");

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

#endif
