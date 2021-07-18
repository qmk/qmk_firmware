#pragma once

// Define mousekey settings
#define MOUSEKEY_DELAY          0
#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_MAX_SPEED      2
#define MOUSEKEY_TIME_TO_MAX    5
#define MOUSEKEY_WHEEL_DELAY    0

#define LSPO_KEY KC_9
#define RSPC_KEY KC_0
#define LSPO_MOD KC_LSHIFT
#define RSPC_MOD KC_RSHIFT

// This makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when
// you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)
#define IGNORE_MOD_TAP_INTERRUPT
