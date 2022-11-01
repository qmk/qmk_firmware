// Copyright 2022 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef RGBLIGHT_ENABLE
#    define RGB_TIMEOUT 5
#endif

bool encoder_update_user(uint8_t index, bool clockwise);
