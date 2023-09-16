// Copyright 2022 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_DISABLE_KEYCODES // disable keycodes for RGB Light controls, only status LED is supported
#    define PICA40_RGBLIGHT_TIMEOUT 5 // turn RGB off after N minutes
#endif
