// Copyright 2021 Victor Toni (@vitoni)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <quantum/action.h>

#include "rgb_matrix_effects.h"

/**
 * @brief Executes periodic tasks, eg. fading or checking for upcoming supend.
 * @details Function declaration as weak as the implementation might "disappear" depending on the RGB settings used.
 * The weak declaration avoids having to change `keymap.c`.
 */
__attribute__((weak))
void matrix_scan_user_rgb(void);

/**
 * @brief Executes tasks based on user activity, eg. fading in.
 * @details Function declaration as weak as the implementation might "disappear" depending on the RGB settings used.
 * The weak declaration avoids having to change `keymap.c`.
 * @param[in]   keycode
 * @param[in]   record
 * @return `false` if further processing should be stopped, `true` otherwise
 */
__attribute__((weak))
bool process_record_user_rgb(const uint16_t keycode, const keyrecord_t *record);
