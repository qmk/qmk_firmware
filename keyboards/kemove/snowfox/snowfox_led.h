// Copyright 2021 Yaotian Feng / Codetector
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "snowfox.h"
#include "snowfox_ble.h"

bool ble_update_kb(ble_handle_t *ble_handle);
void snowfox_led_task(void);
void snowfox_led_show_battery(bool show);
void snowfox_led_show_profile(uint8_t profile);
