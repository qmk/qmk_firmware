// Copyright 2023 The QMK Community (@qmk)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#if defined(OLED_ENABLE)
#    if !defined(OLED_UPDATE_INTERVAL)
#        define OLED_UPDATE_INTERVAL 5
#    endif

#    if !defined(OLED_SECTION_BREAK)
#        define OLED_SECTION_BREAK "-----"
#    endif
#endif
