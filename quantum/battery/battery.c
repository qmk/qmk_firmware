// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "battery_driver.h"
#include "battery.h"
#include "timer.h"

#ifdef BATTERY_CHARGER_ENABLE
#    include "battery_charger.h"
#endif

#ifndef BATTERY_SAMPLE_INTERVAL
#    define BATTERY_SAMPLE_INTERVAL 30000
#endif

static uint8_t                  last_bat_level       = 100;
static battery_charging_state_t last_charging_state  = BATTERY_CHARGING_UNKNOWN;

void battery_init(void) {
    battery_driver_init();
    last_bat_level = battery_driver_sample_percent();

#ifdef BATTERY_CHARGER_ENABLE
    battery_charger_init();
    last_charging_state = battery_charger_get_state();
#endif
}

__attribute__((weak)) void battery_percent_changed_user(uint8_t level) {}
__attribute__((weak)) void battery_percent_changed_kb(uint8_t level) {}

__attribute__((weak)) void battery_charging_state_changed_user(battery_charging_state_t state) {}
__attribute__((weak)) void battery_charging_state_changed_kb(battery_charging_state_t state) {}

static void handle_percent_changed(void) {
    battery_percent_changed_user(last_bat_level);
    battery_percent_changed_kb(last_bat_level);
}

#ifdef BATTERY_CHARGER_ENABLE
static void handle_charging_state_changed(void) {
    battery_charging_state_changed_user(last_charging_state);
    battery_charging_state_changed_kb(last_charging_state);
}
#endif

void battery_task(void) {
    static uint32_t bat_timer = 0;
    if (timer_elapsed32(bat_timer) > BATTERY_SAMPLE_INTERVAL) {
        last_bat_level = battery_driver_sample_percent();

        handle_percent_changed();

        bat_timer = timer_read32();
    }

#ifdef BATTERY_CHARGER_ENABLE
    battery_charging_state_t new_state = battery_charger_get_state();
    if (new_state != last_charging_state) {
        last_charging_state = new_state;
        handle_charging_state_changed();
    }
#endif
}

uint8_t battery_get_percent(void) {
    return last_bat_level;
}

battery_charging_state_t battery_get_charging_state(void) {
    return last_charging_state;
}
