// Copyright 2025 Dimitrix LLC
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// This keymap has no tap-hold or one-shot keys (MO() works without either), so drop
// both. That frees 68 B of the 16U2's 512 B RAM (the tapping waiting buffer and tap
// state) and shortens the deepest key-processing call chain, which leaves more of its
// small stack free. Remove these if you add LT(), MT(), TT(), OSM() etc.
#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT
