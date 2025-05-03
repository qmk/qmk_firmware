// Copyright 2022 Stefan Kerkmann (KarlK90)
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

    uint16_t cpival = (pmw33xx_read(sensor, REG_Resolution_H) << 8) | pmw33xx_read(sensor, REG_Resolution_L);
    return (uint16_t)((cpival + 1) & 0xFFFF) * PMW33XX_CPI_STEP;
}

void pmw33xx_set_cpi(uint8_t sensor, uint16_t cpi) {
    if (sensor >= pmw33xx_number_of_sensors) {
        return;
    }

    uint16_t cpival = CONSTRAIN((cpi / PMW33XX_CPI_STEP), (PMW33XX_CPI_MIN / PMW33XX_CPI_STEP), (PMW33XX_CPI_MAX / PMW33XX_CPI_STEP)) - 1U;
    // Sets upper byte first for more consistent setting of cpi
    pmw33xx_write(sensor, REG_Resolution_H, (cpival >> 8) & 0xFF);
    pmw33xx_write(sensor, REG_Resolution_L, cpival & 0xFF);
}

// PID, Inverse PID
const uint8_t pmw33xx_firmware_signature[2] PROGMEM = {0x42, 0xBD};
