// Copyright 2023 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef VIA_ENABLE  // Only works if VIA is enabled

#define EEPROM_USER_CONFIG_ADDRESS (VIA_EEPROM_CUSTOM_CONFIG_ADDR + 1)

#include "color.h"

typedef struct PACKED {
	uint8_t h;
	uint8_t s;
} HS;

typedef struct {
    HS color[9];
} user_config_t;

extern user_config_t user_config;

#endif  // VIA_ENABLE
