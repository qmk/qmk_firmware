// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "action.h"

bool process_rgb_matrix(uint16_t keycode, keyrecord_t *record);
