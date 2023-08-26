// Copyright 2021 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define AUDIO_PIN C6
#ifdef AUDIO_ENABLE
#    define STARTUP_SONG SONG(STARTUP_SOUND)
#endif

#define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RAINBOW_SWIRL + 2)

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
