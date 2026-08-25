// Copyright 2024 Su (@isuua)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "transport.h"
#include "lowpower.h"
#include "module.h"
#include "smsg.h"

void wireless_init(void);
void wireless_devs_change(uint8_t old_devs, uint8_t new_devs, bool reset);
uint8_t wireless_get_current_devs(void);
void wireless_pre_task(void);
void wireless_post_task(void);
void wireless_task(void);
