// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "davidkristoffersen.h"

#define handle_false(bool) if (!bool) return false;

enum test_codes { KC_T0 = SAFE_RANGE, KC_T1, KC_T2 };

#ifdef MULTI_LANGUAGE
enum language_codes { KC_AE = KC_T2 + 1, KC_OE, KC_AA };
#endif

bool process_debug(uint16_t keycode, keyrecord_t* record);
bool process_language(uint16_t keycode, keyrecord_t* record);

// Prepend key records with macros
bool process_record_user(uint16_t keycode, keyrecord_t* record);

