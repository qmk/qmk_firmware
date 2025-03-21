// Copyright 2022 Stefan Kerkmann (KarlK90)
// Copyright 2022 Ulrich Spörlein (@uqs)
// Copyright 2021 Alabastard (@Alabastard-64)
// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// Copyright 2019 Sunjun Kim
// Copyright 2020 Ploopy Corporation
// SPDX-License-Identifier: GPL-2.0-or-later

#include "pmw33xx_common.h"
#include "progmem.h"

uint16_t pmw33xx_get_cpi(uint8_t sensor) {
    if (sensor >= pmw33xx_number_of_sensors) {
        return 0;
    }

    uint8_t cpival = pmw33xx_read(sensor, REG_Config1);
    // In some cases (100, 900, 1700, 2500), reading the CPI corrupts the firmware and the sensor stops responding.
    // To avoid this, we write the value back to the sensor, which seems to prevent the corruption.
    pmw33xx_write(sensor, REG_Config1, cpival);
    return (uint16_t)((cpival + 1) & 0xFF) * PMW33XX_CPI_STEP;
}

void pmw33xx_set_cpi(uint8_t sensor, uint16_t cpi) {
    if (sensor >= pmw33xx_number_of_sensors) {
        return;
    }

    uint8_t cpival = CONSTRAIN((cpi / PMW33XX_CPI_STEP), (PMW33XX_CPI_MIN / PMW33XX_CPI_STEP), (PMW33XX_CPI_MAX / PMW33XX_CPI_STEP)) - 1U;
    pmw33xx_write(sensor, REG_Config1, cpival);
}

// PID, Inverse PID, SROM version
const uint8_t pmw33xx_firmware_signature[2] PROGMEM = {0x42, 0xBD};
