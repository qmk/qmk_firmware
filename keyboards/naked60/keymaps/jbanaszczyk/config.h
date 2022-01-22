#pragma once

// Set Polling rate to 1000Hz
#define USB_POLLING_INTERVAL_MS 1

#define TAPPING_TERM 220

#ifdef NKRO_ENABLE
#define FORCE_NKRO
#endif

#ifdef PERMISSIVE_HOLD
#undef PERMISSIVE_HOLD
#endif

#define IGNORE_MOD_TAP_INTERRUPT

#ifndef TAPPING_TOGGLE
#define TAPPING_TOGGLE  2
#endif

#ifndef ONESHOT_TIMEOUT
#define ONESHOT_TIMEOUT 2000
#endif

#define RCPC_KEYS KC_LCTL, KC_LSFT, KC_0
