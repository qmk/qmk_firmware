// Copyright 2021 Joric (@joric)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#ifndef BOOTMAGIC_ROW
#    define BOOTMAGIC_ROW 0
#endif
#ifndef BOOTMAGIC_COLUMN
#    define BOOTMAGIC_COLUMN 1
#endif

#ifndef BOOTMAGIC_ROW_RIGHT
#    define BOOTMAGIC_ROW_RIGHT 4
#endif
#ifndef BOOTMAGIC_COLUMN_RIGHT
#    define BOOTMAGIC_COLUMN_RIGHT 1
#endif

#ifdef RGBLIGHT_ENABLE
#    ifndef RGBLIGHT_LIMIT_VAL
#        define RGBLIGHT_LIMIT_VAL 120
#    endif
#endif
