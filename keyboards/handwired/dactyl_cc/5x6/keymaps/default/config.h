// Copyright 2022 mjohns
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Enables This makes it easier for fast typists to use dual-function keys */
#define PERMISSIVE_HOLD

/* mouse config */
#define MOUSEKEY_DELAY          0
// Lowering MOUSEKEY_INTERVAL raises the cursor speed significantly, you may want to lower MOUSEKEY_MAX_SPEED (default: 10)
#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_MAX_SPEED       7
#define MOUSEKEY_WHEEL_DELAY 0

/* layer config */
#define TAPPING_TOGGLE 1

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
