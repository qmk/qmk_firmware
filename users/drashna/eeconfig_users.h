// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>

void eeconfig_read_user_config(uint32_t *data);
void eeconfig_update_user_config(const uint32_t *data);

void eeconfig_read_user_data(void *data);
void eeconfig_update_user_data(const void *data);
