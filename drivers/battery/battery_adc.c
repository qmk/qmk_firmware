// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "analog.h"
#include "gpio.h"

#ifndef BATTERY_PIN
#    error("BATTERY_PIN not configured!")
#endif

#ifndef BATTERY_REF_VOLTAGE_MV
#    define BATTERY_REF_VOLTAGE_MV 3300
#endif

#ifndef BATTERY_VOLTAGE_DIVIDER_R1
#    define BATTERY_VOLTAGE_DIVIDER_R1 100000
#endif

#ifndef BATTERY_VOLTAGE_DIVIDER_R2
#    define BATTERY_VOLTAGE_DIVIDER_R2 100000
#endif

// TODO: infer from adc config?
#ifndef BATTERY_ADC_RESOLUTION
#    define BATTERY_ADC_RESOLUTION 10
#endif

void battery_init(void) {
    gpio_set_pin_input(BATTERY_PIN);
}

__attribute__((weak)) uint16_t battery_raw_to_mv(uint32_t raw) {
    uint32_t bat_mv = raw * BATTERY_REF_VOLTAGE_MV / (1 << BATTERY_ADC_RESOLUTION);

#if BATTERY_VOLTAGE_DIVIDER_R1 > 0 && BATTERY_VOLTAGE_DIVIDER_R2 > 0
    bat_mv = bat_mv * (BATTERY_VOLTAGE_DIVIDER_R1 + BATTERY_VOLTAGE_DIVIDER_R2) / BATTERY_VOLTAGE_DIVIDER_R2;
#endif

    return bat_mv;
}

__attribute__((weak)) uint8_t battery_mv_to_percent(uint16_t bat_mv) {
    // https://github.com/zmkfirmware/zmk/blob/3f7c9d7cc4f46617faad288421025ea2a6b0bd28/app/module/drivers/sensor/battery/battery_common.c#L33
    if (bat_mv >= 4200) {
        return 100;
    } else if (bat_mv <= 3450) {
        return 0;
    }

    return bat_mv * 2 / 15 - 459;
}

uint8_t battery_get_percent(void) {
    uint16_t raw = analogReadPin(BATTERY_PIN);

    uint16_t bat_mv = battery_raw_to_mv(raw);

    return battery_mv_to_percent(bat_mv);
}
