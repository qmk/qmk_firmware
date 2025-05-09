// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

//// Custom pins, might be useful in a keymap
// Wired to input of last shift register, overrides 10k pullup/pulldown
#define ELORA_SELFTEST_PIN GP14

// Can be used for USB current detection
#define ELORA_CC1_PIN      GP28
#define ELORA_CC2_PIN      GP29
