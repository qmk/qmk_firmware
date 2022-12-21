// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#if defined(KEYBOARD_yandrstudio_sp60_rev1)
    #include "rev1.h"
#else
    #include "rev2.h"
#endif

enum keyboard_keycodes {
#ifdef VIA_ENABLE
    LOCK_GUI = USER00,
#else
    LOCK_GUI = SAFE_RANGE,
#endif
    TOG_MACOS_KEYMAP,
    KC_MISSION_CONTROL,
    KC_LAUNCHPAD,
#ifdef VIA_ENABLE
    NEW_SAFE_RANGE = SAFE_RANGE
#else
    NEW_SAFE_RANGE
#endif
};

#define KC_LG    LOCK_GUI
#define KC_MACOS TOG_MACOS_KEYMAP
#define KC_MCTL  KC_MISSION_CONTROL
#define KC_LPAD  KC_LAUNCHPAD
