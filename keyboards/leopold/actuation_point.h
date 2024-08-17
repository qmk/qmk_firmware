// Copyright 2024 Wilhelm Schuster
// Copyright 2017 Balz Guenat
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>

int8_t actuation_point_make_shallower(void);

int8_t actuation_point_make_deeper(void);

int8_t actuation_point_adjust(int8_t offset);

void actuation_point_reset(void);
