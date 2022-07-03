// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdbool.h>
#include "action.h"

/** \brief Intercept keycodes and detect unlock sequences
 */
bool preprocess_secure(uint16_t keycode, keyrecord_t *record);

/** \brief Handle any secure specific keycodes
 */
bool process_secure(uint16_t keycode, keyrecord_t *record);
