// Copyright 2022 Pablo Martinez (@elpekenin)
// Copyright 2022 Daniel Kao (dkao)
// Copyright 2022 Stefan Kerkmann (KarlK90)
// Copyright 2022 Ulrich Spörlein (@uqs)
// Copyright 2021 Alabastard (@Alabastard-64)
// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// Copyright 2019 Sunjun Kim
// Copyright 2020 Ploopy Corporation
// SPDX-License-Identifier: GPL-2.0-or-later

#include "pointing_device_internal.h"
#include "pmw33xx_common.h"
#include "string.h"
#include "wait.h"
#include "spi_master.h"
#include "progmem.h"

bool __attribute__((cold)) pmw33xx_upload_firmware(pointing_device_spi_config_t *spi_config, const pmw33xx_regs_common_t *reg, const uint8_t *firmware_data, const uint16_t firmware_length);
bool __attribute__((cold)) pmw33xx_check_signature(pointing_device_spi_config_t *spi_config, const pmw33xx_regs_common_t *reg, const uint8_t *firmware_signature);

bool in_burst = false; // FIX ME - move out and pass in

bool pmw33xx_spi_start(pointing_device_spi_config_t *spi_config, const pmw33xx_regs_common_t *reg) {
    if (!spi_start(spi_config->cs, false, spi_config->mode, spi_config->divisor)) {
        spi_stop();
        return false;
    }
    // tNCS-SCLK, 10ns
    wait_us(1);
    return true;
}

bool pmw33xx_write(pointing_device_spi_config_t *spi_config, const pmw33xx_regs_common_t *reg, uint8_t reg_addr, uint8_t data) {
    if (!pmw33xx_spi_start(spi_config, reg)) {
        return false;
    }

    if (reg_addr != reg->Motion_Burst) {
        in_burst = false;
    }

    // send address of the register, with MSBit = 1 to indicate it's a write
    uint8_t command[2] = {reg_addr | 0x80, data};
    if (spi_transmit(command, sizeof(command)) != SPI_STATUS_SUCCESS) {
        return false;
    }

    // tSCLK-NCS for write operation is 35us
    wait_us(35);
    spi_stop();

    // tSWW/tSWR (=18us) minus tSCLK-NCS. Could be shortened, but it looks like
    // a safe lower bound
    wait_us(145);
    return true;
}

uint8_t pmw33xx_read(pointing_device_spi_config_t *spi_config, const pmw33xx_regs_common_t *reg, uint8_t reg_addr) {
    if (!pmw33xx_spi_start(spi_config, reg)) {
        return 0;
    }

    // send adress of the register, with MSBit = 0 to indicate it's a read
    spi_write(reg_addr & 0x7f);
    // tSRAD (=160us)
    wait_us(160);
    uint8_t data = spi_read();

    // tSCLK-NCS, 120ns
    wait_us(1);
    spi_stop();

    //  tSRW/tSRR (=20us) mins tSCLK-NCS
    wait_us(19);
    return data;
}

bool pmw33xx_check_signature(pointing_device_spi_config_t *spi_config, const pmw33xx_regs_common_t *reg, const uint8_t *firmware_signature) {
    uint8_t signature_dump[3] = {
        pmw33xx_read(spi_config, reg, reg->Product_ID),
        pmw33xx_read(spi_config, reg, reg->Inverse_Product_ID),
        pmw33xx_read(spi_config, reg, reg->SROM_ID),
    };

    return memcmp(firmware_signature, signature_dump, sizeof(signature_dump)) == 0;
}

bool pmw33xx_upload_firmware(pointing_device_spi_config_t *spi_config, const pmw33xx_regs_common_t *reg, const uint8_t *firmware_data, const uint16_t firmware_length) {
    // Datasheet claims we need to disable REST mode first, but during startup
    // it's already disabled and we're not turning it on ...
    // pmw33xx_write(REG_Config2, 0x00);  // disable REST mode
    if (!pmw33xx_write(spi_config, reg, reg->SROM_Enable, 0x1d)) {
        return false;
    }
    wait_ms(10);
    pmw33xx_write(spi_config, reg, reg->SROM_Enable, 0x18);

    if (!pmw33xx_spi_start(spi_config, reg)) {
        return false;
    }

    spi_write(reg->SROM_Load_Burst | 0x80);
    wait_us(15);

    for (size_t i = 0; i < firmware_length; i++) {
        spi_write(pgm_read_byte(firmware_data + i));
        wait_us(15);
    }
    wait_us(200);

    pmw33xx_read(spi_config, reg, reg->SROM_ID);
    pmw33xx_write(spi_config, reg, reg->Config2, 0x00);

    return true;
}

bool pmw33xx_init(pointing_device_spi_config_t *spi_config, const pmw33xx_regs_common_t *reg, const uint8_t *firmware_data, const uint16_t firmware_length, const uint8_t *firmware_signature) {
    spi_init();

    // power up, need to first drive NCS high then low. the datasheet does not
    // say for how long, 40us works well in practice.
    if (!pmw33xx_spi_start(spi_config, reg)) {
        return false;
    }
    wait_us(40);
    spi_stop();
    wait_us(40);

    if (!pmw33xx_write(spi_config, reg, reg->Power_Up_Reset, 0x5a)) {
        return false;
    }
    wait_ms(50);

    // read registers and discard
    pmw33xx_read(spi_config, reg, reg->Motion);
    pmw33xx_read(spi_config, reg, reg->Delta_X_L);
    pmw33xx_read(spi_config, reg, reg->Delta_X_H);
    pmw33xx_read(spi_config, reg, reg->Delta_Y_L);
    pmw33xx_read(spi_config, reg, reg->Delta_Y_H);

    if (!pmw33xx_upload_firmware(spi_config, reg, firmware_data, firmware_length)) {
        pd_dprintf("PMW33XX: firmware upload failed!\n");
        return false;
    }

    spi_stop();

    wait_ms(10);

    pmw33xx_write(spi_config, reg, reg->Config2, 0x00);
    pmw33xx_write(spi_config, reg, reg->Angle_Tune, CONSTRAIN(ROTATIONAL_TRANSFORM_ANGLE, -127, 127));
    pmw33xx_write(spi_config, reg, reg->Lift_Config, PMW33XX_LIFTOFF_DISTANCE);

    if (!pmw33xx_check_signature(spi_config, reg, firmware_signature)) {
        pd_dprintf("PMW33XX: firmware signature verification failed!\n");
        return false;
    }

    return true;
}

pmw33xx_report_t pmw33xx_read_burst(pointing_device_spi_config_t *spi_config, const pmw33xx_regs_common_t *reg) {
    pmw33xx_report_t report = {0};

    if (!in_burst) {
        pd_dprintf("PMW33XX: burst\n");
        if (!pmw33xx_write(spi_config, reg, reg->Motion_Burst, 0x00)) {
            return report;
        }
        in_burst = true;
    }

    if (!pmw33xx_spi_start(spi_config, reg)) {
        return report;
    }

    spi_write(reg->Motion_Burst);
    wait_us(35); // waits for tSRAD_MOTBR

    spi_receive((uint8_t *)&report, sizeof(report));

    // panic recovery, sometimes burst mode works weird.
    if (report.motion.w & 0b111) {
        in_burst = false;
    }

    spi_stop();

    pd_dprintf("PMW33XX: motion: 0x%x dx: %i dy: %i\n", report.motion.w, report.delta_x, report.delta_y);

    report.delta_x *= -1;
    report.delta_y *= -1;

    return report;
}

report_mouse_t pmw33xx_get_report(pointing_device_spi_config_t *spi_config, const pmw33xx_regs_common_t *reg) {
    pmw33xx_report_t report       = pmw33xx_read_burst(spi_config, reg);
    report_mouse_t   mouse_report = {0};
    static bool      in_motion    = false;

    if (report.motion.b.is_lifted) {
        return mouse_report;
    }

    if (!report.motion.b.is_motion) {
        in_motion = false;
        return mouse_report;
    }

    if (!in_motion) {
        in_motion = true;
        pd_dprintf("PWM33XX: starting motion\n");
    }

    mouse_report.x = CONSTRAIN_HID_XY(report.delta_x);
    mouse_report.y = CONSTRAIN_HID_XY(report.delta_y);
    return mouse_report;
}