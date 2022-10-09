// Copyright 2017-2019 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#if defined(KEYBOARD_kbdfans_kbd75_rev1)
    #include "rev1.h"
#elif defined(KEYBOARD_kbdfans_kbd75_rev2)
    #include "rev2.h"
#endif
