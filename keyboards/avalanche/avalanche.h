// Copyright 2022 Vitaly Volkov (@vlkv)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef KEYBOARD_avalanche_v1
    #include "v1.h"
#elif KEYBOARD_avalanche_v2
    #include "v2.h"
#elif KEYBOARD_avalanche_v3
    #include "v3.h"
#endif

#include "quantum.h"
