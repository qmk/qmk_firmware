// Copyright 2023 Robert Mills (@robcmills)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Equivalent to zmk behavior-hold-tap tap-preferred flavor
// Do not force the mod-tap key press to be handled as a modifier
// if any other key was pressed while the mod-tap key is held down.
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY

// Equivalent to zmk behavior-hold-tap hold-preferred flavor
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

