// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "macros.h"

enum dynamic_codes { KC_AE = SAFE_RANGE, KC_OE, KC_AA };

bool process_dynamic(uint16_t keycode, keyrecord_t* record);
