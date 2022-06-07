// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "davidkristoffersen.h"

// Get current language layer
int get_language(void);

// Get special shifted code
uint16_t get_special_shifted_code(uint16_t keycode, int lang);

// Get language specific code
uint16_t get_other_language_code(uint16_t keycode, int lang);
