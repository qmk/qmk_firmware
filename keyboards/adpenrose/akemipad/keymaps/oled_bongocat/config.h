// Copyright 2022 Arturo Avila (@ADPenrose)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef AUDIO_ENABLE
#    define NO_MUSIC_MODE
#endif

#ifdef OLED_ENABLE
#    define OLED_TIMEOUT 120000
#endif

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_ACTION_ONESHOT
#define LAYER_STATE_8BIT
