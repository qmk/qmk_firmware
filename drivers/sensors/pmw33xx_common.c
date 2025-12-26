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

extern const uint8_t pmw33xx_firmware_signature[2] PROGMEM;

static const pin_t cs_pins_left[]  = PMW33XX_CS_PINS;
static const pin_t cs_pins_right[] = PMW33XX_CS_PINS_RIGHT;

static bool in_burst_left[ARRAY_SIZE(cs_pins_left)]   = {0};
static bool in_burst_right[ARRAY_SIZE(cs_pins_right)] = {0};

bool __attribute__((cold)) pmw33xx_upload_firmware(uint8_t sensor);
bool __attribute__((cold)) pmw33xx_check_signature(uint8_t sensor);

const pointing_device_driver_t pmw33xx_pointing_device_driver = {
    .init       = pmw33xx_init_wrapper,
    .get_report = pmw33xx_get_report,
    .set_cpi    = pmw33xx_set_cpi_wrapper,
    .get_cpi    = pmw33xx_get_cpi_wrapper,
};

uint16_t __attribute__((weak)) pmw33xx_srom_get_length(void) {
    return 0;
}

uint8_t __attribute__((weak)) pmw33xx_srom_get_byte(uint16_t position) {
    return 0;
}

void pmw33xx_set_cpi_all_sensors(uint16_t cpi) {
    for (uint8_t sensor = 0; sensor < pmw33xx_number_of_sensors; sensor++) {
        pmw33xx_set_cpi(sensor, cpi);
    }
}

bool pmw33xx_spi_start(uint8_t sensor) {
    if (!spi_start(cs_pins[sensor], false, 3, PMW33XX_SPI_DIVISOR)) {
        spi_stop();
        return false;
    }
    // tNCS-SCLK, 10ns
    wait_us(1);
    return true;
}

bool pmw33xx_write(uint8_t sensor, uint8_t reg_addr, uint8_t data) {
    if (!pmw33xx_spi_start(sensor)) {
        return false;
    }

    if (reg_addr != REG_Motion_Burst) {
        in_burst[sensor] = false;
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

uint8_t pmw33xx_read(uint8_t sensor, uint8_t reg_addr) {
    if (!pmw33xx_spi_start(sensor)) {
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

__attribute__((weak)) bool pmw33xx_check_signature(uint8_t sensor) {
    uint8_t signature_dump[2] = {
        pmw33xx_read(sensor, REG_Product_ID),
        pmw33xx_read(sensor, REG_Inverse_Product_ID),
    };

    return memcmp_P(signature_dump, pmw33xx_firmware_signature, sizeof(signature_dump)) == 0;
}

bool pmw33xx_upload_firmware(uint8_t sensor) {
    // Datasheet claims we need to disable REST mode first, but during startup
    // it's already disabled and we're not turning it on ...
    // pmw33xx_write(REG_Config2, 0x00);  // disable REST mode
    if (!pmw33xx_write(sensor, REG_SROM_Enable, 0x1d)) {
        return false;
    }
    wait_ms(10);
    pmw33xx_write(sensor, REG_SROM_Enable, 0x18);

    if (!pmw33xx_spi_start(sensor)) {
        return false;
    }

    spi_write(REG_SROM_Load_Burst | 0x80);
    wait_us(15);

    for (size_t i = 0; i < pmw33xx_srom_get_length(); i++) {
        spi_write(pmw33xx_srom_get_byte(i));
        wait_us(15);
    }

    spi_stop();
    wait_us(200);

    pmw33xx_read(sensor, REG_SROM_ID);
    pmw33xx_write(sensor, REG_Config2, 0x00);

    return true;
}

bool pmw33xx_init(uint8_t sensor) {
    if (sensor >= pmw33xx_number_of_sensors) {
        return false;
    }
    spi_init();

    // power up, need to first drive NCS high then low. the datasheet does not
    // say for how long, 40us works well in practice.
    if (!pmw33xx_spi_start(sensor)) {
        return false;
    }
    wait_us(40);
    spi_stop();
    wait_us(40);

    if (!pmw33xx_write(sensor, REG_Power_Up_Reset, 0x5a)) {
        return false;
    }
    wait_ms(50);

    // read registers and discard
    pmw33xx_read(sensor, REG_Motion);
    pmw33xx_read(sensor, REG_Delta_X_L);
    pmw33xx_read(sensor, REG_Delta_X_H);
    pmw33xx_read(sensor, REG_Delta_Y_L);
    pmw33xx_read(sensor, REG_Delta_Y_H);

    if (pmw33xx_srom_get_length() != 0) {
        if (!pmw33xx_upload_firmware(sensor)) {
            pd_dprintf("PMW33XX (%d): firmware upload failed!\n", sensor);
            return false;
        }
    } else {
        pd_dprintf("PMW33XX (%d): firmware upload skipped.\n", sensor);
    }

    spi_stop();

    wait_ms(10);
    pmw33xx_set_cpi(sensor, PMW33XX_CPI);

    wait_ms(1);

    pmw33xx_write(sensor, REG_Config2, 0x00);
    pmw33xx_write(sensor, REG_Angle_Tune, CONSTRAIN(ROTATIONAL_TRANSFORM_ANGLE, -127, 127));
    pmw33xx_write(sensor, REG_Lift_Config, PMW33XX_LIFTOFF_DISTANCE);

    if (!pmw33xx_check_signature(sensor)) {
        pd_dprintf("PMW33XX (%d): firmware signature verification failed!\n", sensor);
        return false;
    }

    return true;
}

pmw33xx_report_t pmw33xx_read_burst(uint8_t sensor) {
    pmw33xx_report_t report = {0};

    if (sensor >= pmw33xx_number_of_sensors) {
        return report;
    }

    if (!in_burst[sensor]) {
        pd_dprintf("PMW33XX (%d): burst\n", sensor);
        if (!pmw33xx_write(sensor, REG_Motion_Burst, 0x00)) {
            return report;
        }
        in_burst[sensor] = true;
    }

    if (!pmw33xx_spi_start(sensor)) {
        return report;
    }

    spi_write(REG_Motion_Burst);
    wait_us(35); // waits for tSRAD_MOTBR

    spi_receive((uint8_t *)&report, sizeof(report));

    // panic recovery, sometimes burst mode works weird.
    if (report.motion.w & 0b111) {
        in_burst[sensor] = false;
    }

    spi_stop();

    pd_dprintf("PMW33XX (%d): motion: 0x%x dx: %i dy: %i\n", sensor, report.motion.w, report.delta_x, report.delta_y);

    report.delta_x *= -1;
    report.delta_y *= -1;

    return report;
}

bool pmw33xx_init_wrapper(void) {
    return pmw33xx_init(0);
}

void pmw33xx_set_cpi_wrapper(uint16_t cpi) {
    pmw33xx_set_cpi(0, cpi);
}

uint16_t pmw33xx_get_cpi_wrapper(void) {
    return pmw33xx_get_cpi(0);
}

report_mouse_t pmw33xx_get_report(report_mouse_t mouse_report) {
    pmw33xx_report_t report    = pmw33xx_read_burst(0);
    static bool      in_motion = false;

    if (report.motion.b.is_lifted) {
        return mouse_report;
    }

    if (!report.motion.b.is_motion) {
        in_motion = false;
        return mouse_report;
    }

    if (!in_motion) {
        in_motion = true;
        pd_dprintf("PWM3360 (0): starting motion\n");
    }

    mouse_report.x = CONSTRAIN_HID_XY(report.delta_x);
    mouse_report.y = CONSTRAIN_HID_XY(report.delta_y);
    return mouse_report;
}
