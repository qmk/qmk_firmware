// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "keymap_extras/keymap_norwegian.h"
#include "davidkristoffersen.h"

// Better norwegian defines
#undef NO_LESS
#define NO_LESS KC_NUBS     // <
#undef NO_GRTR
#define NO_GRTR S(NO_LESS)  // >
#undef NO_AE
#define NO_AE KC_QUOT       // Æ
#undef NO_OE
#define NO_OE KC_SCLN       // Ø
#undef NO_AA
#define NO_AA KC_LBRC       // Å
