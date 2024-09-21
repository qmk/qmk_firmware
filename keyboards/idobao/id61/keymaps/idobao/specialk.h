// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "action.h"

bool ID61_process_special_k(uint16_t keycode, keyrecord_t *record, bool arrow_mode, uint8_t k_norm, uint8_t k_spcl, uint8_t k_altr);
bool ID61_backspace_special(uint16_t keycode, keyrecord_t *record);
