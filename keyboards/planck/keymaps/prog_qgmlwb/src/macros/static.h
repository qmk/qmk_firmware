// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "../base.h"

enum static_codes { TEST_0 = SAFE_RANGE, TEST_1, TEST_2 };

bool process_static(uint16_t keycode, keyrecord_t* record);
