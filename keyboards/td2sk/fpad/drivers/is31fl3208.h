// Copyright 2023 td2sk (@td2sk)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdint.h>

void IS31FL3208_init(void);
void IS31FL3208_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void IS31FL3208_update(void);
