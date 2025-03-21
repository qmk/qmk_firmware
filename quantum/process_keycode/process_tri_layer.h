// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "action.h"

/**
 * @brief Handles tri layer behavior
 *
 * @param keycode the keycode
 * @param record the key record structure
 * @return true continue handling keycodes
 * @return false stop handling keycodes
 */
bool process_tri_layer(uint16_t keycode, keyrecord_t *record);
