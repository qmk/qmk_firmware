// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "davidkristoffersen.h"
#include "dynamic.h"
#include "static.h"

#define handle_false(bool) if (!bool) return false;

// Prepend key records with macros
bool process_record_user(uint16_t keycode, keyrecord_t* record);
