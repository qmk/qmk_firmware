// Copyright 2022 Michal Petrik (@Michal Petrik)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "bat.h"

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    tap_code(clockwise ? KC_VOLU : KC_VOLD);
    return true;
}
