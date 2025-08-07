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

__attribute__((weak)) void battery_percent_changed_user(uint8_t level) {}
__attribute__((weak)) void battery_percent_changed_kb(uint8_t level) {}

static void handle_percent_changed(void) {
    battery_percent_changed_user(last_bat_level);
    battery_percent_changed_kb(last_bat_level);
}

void battery_task(void) {
    static uint32_t bat_timer = 0;
    if (timer_elapsed32(bat_timer) > BATTERY_SAMPLE_INTERVAL) {
        last_bat_level = battery_driver_sample_percent();

        handle_percent_changed();

        bat_timer = timer_read32();
    }
}

uint8_t battery_get_percent(void) {
    return last_bat_level;
}
