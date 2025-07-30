// Copyright 2025 emolitor (github.com/emolitor)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "module.h"
#include "smsg.h"

void wireless_devs_change(uint8_t old_devs, uint8_t new_devs, bool reset);
uint8_t wireless_get_current_devs(void);
