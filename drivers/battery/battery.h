// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>

void battery_init(void);

uint8_t battery_get_percent(void);
