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

#include "spi_master.h"
#include "pmw3389.h"
#include "wait.h"
#include "debug.h"
#include "print.h"
#include "pmw3389_firmware.h"

// Registers
// clang-format off
#define REG_Product_ID                 0x00
#define REG_Revision_ID                0x01
#define REG_Motion                     0x02
#define REG_Delta_X_L                  0x03
#define REG_Delta_X_H                  0x04
#define REG_Delta_Y_L                  0x05
#define REG_Delta_Y_H                  0x06
#define REG_SQUAL                      0x07
#define REG_RawData_Sum                0x08
#define REG_Maximum_RawData            0x09
#define REG_Minimum_RawData            0x0a
#define REG_Shutter_Lower              0x0b
#define REG_Shutter_Upper              0x0c
#define REG_Ripple_Control             0x0d
#define REG_Resolution_L               0x0e
#define REG_Resolution_H               0x0f
#define REG_Config2                    0x10
#define REG_Angle_Tune                 0x11
#define REG_Frame_Capture              0x12
#define REG_SROM_Enable                0x13
#define REG_Run_Downshift              0x14
#define REG_Rest1_Rate_Lower           0x15
#define REG_Rest1_Rate_Upper           0x16
#define REG_Rest1_Downshift            0x17
#define REG_Rest2_Rate_Lower           0x18
#define REG_Rest2_Rate_Upper           0x19
#define REG_Rest2_Downshift            0x1a
#define REG_Rest3_Rate_Lower           0x1b
#define REG_Rest3_Rate_Upper           0x1c
#define REG_Observation                0x24
#define REG_Data_Out_Lower             0x25
#define REG_Data_Out_Upper             0x26
#define REG_SROM_ID                    0x2a
#define REG_Min_SQ_Run                 0x2b
#define REG_RawData_Threshold          0x2c
#define REG_Control2                   0x2d
#define REG_Config5_L                  0x2e
#define REG_Config5_H                  0x2f
#define REG_Power_Up_Reset             0X3a
#define REG_Shutdown                   0x3b
#define REG_Inverse_Product_ID         0x3f
#define REG_LiftCutoff_Cal3            0x41
#define REG_Angle_Snap                 0x42
#define REG_LiftCutoff_Cal1            0x4a
#define REG_Motion_Burst               0x50
#define REG_SROM_Load_Burst            0x62
#define REG_Lift_Config                0x63
#define REG_RawData_Burst              0x64
#define REG_LiftCutoff_Cal2            0x65
#define REG_LiftCutoff_Cal_Timeout     0x71
#define REG_LiftCutoff_Cal_Min_Length  0x72
#define REG_PWM_Period_Cnt             0x73
#define REG_PWM_Width_Cnt              0x74

#define CPI_STEP       50
// clang-format on

// limits to 0--319, resulting in a CPI range of 50 -- 16000 (as only steps of 50 are possible).
#ifndef MAX_CPI
#    define MAX_CPI 0x013f
#endif

bool _inBurst = false;

#ifdef CONSOLE_ENABLE
void print_byte(uint8_t byte) { dprintf("%c%c%c%c%c%c%c%c|", (byte & 0x80 ? '1' : '0'), (byte & 0x40 ? '1' : '0'), (byte & 0x20 ? '1' : '0'), (byte & 0x10 ? '1' : '0'), (byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'), (byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0')); }
#endif
#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

bool pmw3389_spi_start(void) {
    bool status = spi_start(PMW3389_CS_PIN, PMW3389_SPI_LSBFIRST, PMW3389_SPI_MODE, PMW3389_SPI_DIVISOR);
    // tNCS-SCLK, 120ns
    wait_us(1);
    return status;
}

spi_status_t pmw3389_write(uint8_t reg_addr, uint8_t data) {
    pmw3389_spi_start();

    if (reg_addr != REG_Motion_Burst) {
        _inBurst = false;
    }

    // send address of the register, with MSBit = 1 to indicate it's a write
    spi_status_t status = spi_write(reg_addr | 0x80);
    status              = spi_write(data);

    // tSCLK-NCS for write operation is 35 us
    wait_us(35);
    spi_stop();

    // tSWW/tSWR (=180us) minus tSCLK-NCS. Could be shortened, but is looks like a safe lower bound
    wait_us(145);
    return status;
}

uint8_t pmw3389_read(uint8_t reg_addr) {
    pmw3389_spi_start();
    // send adress of the register, with MSBit = 0 to indicate it's a read
    spi_write(reg_addr & 0x7f);
    // tSRAD (=160us)
    wait_us(160);
    uint8_t data = spi_read();

    // tSCLK-NCS, 120ns
    wait_us(1);
    spi_stop();

    //  tSRW/tSRR (=20us) minus tSCLK-NCS
    wait_us(19);
    return data;
}

bool pmw3389_init(void) {
    setPinOutput(PMW3389_CS_PIN);

    spi_init();
    _inBurst = false;

    spi_stop();
    pmw3389_spi_start();
    spi_stop();

    pmw3389_write(REG_Shutdown, 0xb6);  // Shutdown first
    wait_ms(300);

    pmw3389_spi_start();
    wait_us(40);
    spi_stop();
    wait_us(40);

    // power up, need to first drive NCS high then low, see above.
    pmw3389_write(REG_Power_Up_Reset, 0x5a);
    wait_ms(50);

    // read registers and discard
    pmw3389_read(REG_Motion);
    pmw3389_read(REG_Delta_X_L);
    pmw3389_read(REG_Delta_X_H);
    pmw3389_read(REG_Delta_Y_L);
    pmw3389_read(REG_Delta_Y_H);

    pmw3389_upload_firmware();

    spi_stop();

    wait_ms(10);
    pmw3389_set_cpi(PMW3389_CPI);

    wait_ms(1);

    pmw3389_write(REG_Config2, 0x00);

    pmw3389_write(REG_Angle_Tune, constrain(ROTATIONAL_TRANSFORM_ANGLE, -127, 127));

    pmw3389_write(REG_Lift_Config, PMW3389_LIFTOFF_DISTANCE);

    bool init_success = pmw3389_check_signature();
#ifdef CONSOLE_ENABLE
    if (init_success) {
        dprintf("pmw3389 signature verified");
    } else {
        dprintf("pmw3389 signature verification failed!");
    }
#endif

    writePinLow(PMW3389_CS_PIN);

    return init_success;
}

void pmw3389_upload_firmware(void) {
    // Datasheet claims we need to disable REST mode first, but during startup
    // it's already disabled and we're not turning it on ...
    // pmw3389_write(REG_Config2, 0x00);  // disable REST mode
    pmw3389_write(REG_SROM_Enable, 0x1d);

    wait_ms(10);

    pmw3389_write(REG_SROM_Enable, 0x18);

    pmw3389_spi_start();
    spi_write(REG_SROM_Load_Burst | 0x80);
    wait_us(15);

    // legacy only for PMW3389 spi_transmit failed to load firmware
    unsigned char c;
    for (int i = 0; i < FIRMWARE_LENGTH; i++) {
        c = (unsigned char)pgm_read_byte(firmware_data + i);
        spi_write(c);
        wait_us(15);
    }

    wait_us(200);

    pmw3389_read(REG_SROM_ID);
    pmw3389_write(REG_Config2, 0x00);
}

bool pmw3389_check_signature(void) {
    uint8_t pid      = pmw3389_read(REG_Product_ID);
    uint8_t iv_pid   = pmw3389_read(REG_Inverse_Product_ID);
    uint8_t SROM_ver = pmw3389_read(REG_SROM_ID);
    return (pid == firmware_signature[0] && iv_pid == firmware_signature[1] && SROM_ver == firmware_signature[2]);  // signature for SROM 0x04
}

uint16_t pmw3389_get_cpi(void) {
    uint16_t cpival = (pmw3389_read(REG_Resolution_H) << 8) | pmw3389_read(REG_Resolution_L);
    return (uint16_t)((cpival + 1) & 0xffff) * CPI_STEP;
}

void pmw3389_set_cpi(uint16_t cpi) {
    uint16_t cpival = constrain((cpi / CPI_STEP) - 1, 0, MAX_CPI);
    // Sets upper byte first for more consistent setting of cpi
    pmw3389_write(REG_Resolution_H, (cpival >> 8) & 0xff);
    pmw3389_write(REG_Resolution_L, cpival & 0xff);
}

report_pmw3389_t pmw3389_read_burst(void) {
    report_pmw3389_t report = {0};

    if (!_inBurst) {
#ifdef CONSOLE_ENABLE
        dprintf("burst on");
#endif
        pmw3389_write(REG_Motion_Burst, 0x00);
        _inBurst = true;
    }

    pmw3389_spi_start();
    spi_write(REG_Motion_Burst);
    wait_us(35);  // waits for tSRAD_MOTBR

    report.motion = spi_read();
    spi_read();  // skip Observation
    // delta registers
    report.dx  = spi_read();
    report.mdx = spi_read();
    report.dy  = spi_read();
    report.mdy = spi_read();

    if (report.motion & 0b111) {  // panic recovery, sometimes burst mode works weird.
        _inBurst = false;
    }

    spi_stop();

#ifdef CONSOLE_ENABLE
    if (debug_mouse) {
        print_byte(report.motion);
        print_byte(report.dx);
        print_byte(report.mdx);
        print_byte(report.dy);
        print_byte(report.mdy);
        dprintf("\n");
    }
#endif

    report.isMotion    = (report.motion & 0x80) != 0;
    report.isOnSurface = (report.motion & 0x08) == 0;
    report.dx |= (report.mdx << 8);
    report.dx = report.dx * -1;
    report.dy |= (report.mdy << 8);
    report.dy = report.dy * -1;

    return report;
}
