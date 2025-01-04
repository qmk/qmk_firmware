// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "pointing_device.h"

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
    int16_t twist;
    int16_t tilt_x;
    int16_t tilt_y;
} spacemouse_data_t;

bool              spacemouse_send_command(uint8_t cmd);
void              spacemouse_init(void);
spacemouse_data_t spacemouse_get_data(void);
report_mouse_t spacemouse_get_report(report_mouse_t mouse_report);
