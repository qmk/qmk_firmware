// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "davidkristoffersen.h"

#ifdef MULTI_LANGUAGE
// Get special shifted code
uint16_t converted_shift_code(uint16_t keycode, int lang);

// Get language specific code
uint16_t converted_language(uint16_t keycode, int lang);
#endif
