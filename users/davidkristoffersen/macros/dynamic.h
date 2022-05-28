// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "macros.h"

#define LANG_US DF(QGMLWB_US)
#define LANG_NO DF(QGMLWB_NO)

enum dynamic_codes { KC_AE = SAFE_RANGE, KC_OE, KC_AA };

bool process_dynamic(uint16_t keycode, keyrecord_t* record);
