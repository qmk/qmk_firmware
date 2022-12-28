// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifndef RGBLIGHT_LIMIT_VAL
#    if defined(OLED_ENABLE)
#        define RGBLIGHT_LIMIT_VAL 100
#    else
#        define RGBLIGHT_LIMIT_VAL 150
#    endif
#endif

#ifndef OLED_BRIGHTNESS
#    ifdef RGBLIGHT_ENABLE
#        define OLED_BRIGHTNESS 80
#    else
#        define OLED_BRIGHTNESS 150
#    endif
#endif
