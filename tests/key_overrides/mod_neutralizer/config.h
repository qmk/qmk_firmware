// Copyright 2023 Vladislav Kucheriavykh (@precondition)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "test_common.h"

#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_F18

// Neutralize left alt and left GUI (Default value)
#define MODS_TO_NEUTRALIZE \
    { MOD_BIT(KC_LEFT_ALT), MOD_BIT(KC_LEFT_GUI) }
