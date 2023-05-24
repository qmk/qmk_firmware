// Copyright (c) 2022 Takeshi Ishii (mtei@github)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// place overrides here

#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(STARTUP_SOUND)
  #define AUDIO_CLICKY
#endif

#undef TAPPING_TERM
#define TAPPING_TERM 300
#define PERMISSIVE_HOLD
/* when TAPPING_TERM >= 500 same effect PERMISSIVE_HOLD.
   see tmk_core/common/action_tapping.c */

// If you need more program area, try select and reduce rgblight modes to use.

