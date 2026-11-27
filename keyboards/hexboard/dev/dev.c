// Copyright 2022-2023 Zach DeCook
// SPDX-License-Identifier: GPL-3.0-only

#include "quantum.h"

#ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}
#endif
