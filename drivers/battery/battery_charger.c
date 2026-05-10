// Copyright 2026 Roman Kuzmitskii (@damex)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "battery_charger.h"
#include "gpio.h"

void battery_charger_init(void) {
    gpio_set_pin_input(BATTERY_CHARGER_CABLE_PIN);
    gpio_set_pin_input_high(BATTERY_CHARGER_FULL_PIN);
}

battery_charging_state_t battery_charger_get_state(void) {
    bool cable = gpio_read_pin(BATTERY_CHARGER_CABLE_PIN) == BATTERY_CHARGER_CABLE_ACTIVE_LEVEL;
    bool full  = gpio_read_pin(BATTERY_CHARGER_FULL_PIN) == BATTERY_CHARGER_FULL_ACTIVE_LEVEL;
    if (!cable) {
        return BATTERY_NOT_CHARGING;
    }
    if (full) {
        return BATTERY_FULL;
    }
    return BATTERY_CHARGING;
}
