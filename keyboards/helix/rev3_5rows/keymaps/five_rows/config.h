// Copyright (c) 2022 Takeshi Ishii (mtei@github)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#undef TAPPING_TERM
#define TAPPING_TERM 300
#define PERMISSIVE_HOLD
/* when TAPPING_TERM >= 500 same effect PERMISSIVE_HOLD.
   see tmk_core/common/action_tapping.c */

#undef OLED_UPDATE_INTERVAL
#ifdef DEBUG_MATRIX_SCAN_RATE
#    define OLED_UPDATE_INTERVAL 500
#else
#    define OLED_UPDATE_INTERVAL 50
#endif

#define PSEUDO_SPRINTF_DEFINED

