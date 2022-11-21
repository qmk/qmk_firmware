// Copyright (c) 2022 Takeshi Ishii (mtei@github)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#undef TAPPING_TERM
#define TAPPING_TERM 300
#define PERMISSIVE_HOLD

#undef OLED_UPDATE_INTERVAL
#ifdef DEBUG_MATRIX_SCAN_RATE
#    define OLED_UPDATE_INTERVAL 500
#else
#    define OLED_UPDATE_INTERVAL 50
#endif

#define PSEUDO_SPRINTF_DEFINED

