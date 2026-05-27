// Copyright 2024 Matt (@matt)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// When another key is pressed while an LT() key is held, immediately
// treat it as a hold (layer activation) rather than waiting for tapping term.
// This makes all chord layers trigger reliably without delay.
#define HOLD_ON_OTHER_KEY_PRESS

// Additional hold detection: if another key is pressed AND released while
// an LT() key is still held, also treat it as a hold. Complements the above.
#define PERMISSIVE_HOLD
