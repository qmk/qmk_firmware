// Copyright 2026 Roman Kuzmitskii (@damex)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "battery.h"

#ifndef BATTERY_CHARGER_CABLE_PIN
#    error "BATTERY_CHARGER_CABLE_PIN must be defined"
#endif
#ifndef BATTERY_CHARGER_FULL_PIN
#    error "BATTERY_CHARGER_FULL_PIN must be defined"
#endif

#if defined(BATTERY_CHARGER_CABLE_ACTIVE_HIGH) && !defined(BATTERY_CHARGER_CABLE_ACTIVE_LOW)
#    define BATTERY_CHARGER_CABLE_ACTIVE_LEVEL 1
#elif defined(BATTERY_CHARGER_CABLE_ACTIVE_LOW) && !defined(BATTERY_CHARGER_CABLE_ACTIVE_HIGH)
#    define BATTERY_CHARGER_CABLE_ACTIVE_LEVEL 0
#else
#    error "Define exactly one of BATTERY_CHARGER_CABLE_ACTIVE_HIGH or BATTERY_CHARGER_CABLE_ACTIVE_LOW"
#endif

#if defined(BATTERY_CHARGER_FULL_ACTIVE_HIGH) && !defined(BATTERY_CHARGER_FULL_ACTIVE_LOW)
#    define BATTERY_CHARGER_FULL_ACTIVE_LEVEL 1
#elif defined(BATTERY_CHARGER_FULL_ACTIVE_LOW) && !defined(BATTERY_CHARGER_FULL_ACTIVE_HIGH)
#    define BATTERY_CHARGER_FULL_ACTIVE_LEVEL 0
#else
#    error "Define exactly one of BATTERY_CHARGER_FULL_ACTIVE_HIGH or BATTERY_CHARGER_FULL_ACTIVE_LOW"
#endif

void battery_charger_init(void);
battery_charging_state_t battery_charger_get_state(void);
