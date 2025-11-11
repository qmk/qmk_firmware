// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include <stdint.h>

void sc_ble_battary(uint8_t batt_level);
void wireless_start(uint32_t mode);
void wireless_stop(void);
