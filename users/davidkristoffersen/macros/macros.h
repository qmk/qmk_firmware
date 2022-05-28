// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "davidkristoffersen.h"

#define handle_false(bool) if (!bool) return false;

#ifdef MULTI_LANGUAGE
enum language_codes { KC_AE = SAFE_RANGE, KC_OE, KC_AA };
#endif
enum test_codes { TEST_0 = SAFE_RANGE, TEST_1, TEST_2 };

bool process_debug(uint16_t keycode, keyrecord_t* record);
bool process_language(uint16_t keycode, keyrecord_t* record);

// Prepend key records with macros
bool process_record_user(uint16_t keycode, keyrecord_t* record);

