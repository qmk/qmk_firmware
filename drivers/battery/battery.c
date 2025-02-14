// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "battery_driver.h"
#include "battery.h"
#include "timer.h"

#ifndef BATTERY_SAMPLE_INTERVAL
#    define BATTERY_SAMPLE_INTERVAL 30000
#endif

static uint8_t last_bat_level = 100;

void battery_init(void) {
    battery_driver_init();

    last_bat_level = battery_driver_sample_percent();
}

void battery_task(void) {
    static uint32_t bat_timer = 0;
    if (timer_elapsed32(bat_timer) > BATTERY_SAMPLE_INTERVAL) {
        last_bat_level = battery_driver_sample_percent();

        bat_timer = timer_read32();
    }
}

uint8_t battery_get_percent(void) {
    return last_bat_level;
}
