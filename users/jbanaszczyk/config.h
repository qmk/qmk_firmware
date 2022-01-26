#pragma once

//#define USB_POLLING_INTERVAL_MS 10

#define TAPPING_TERM 200

#define AUTO_SHIFT_TIMEOUT 165

#define DYNAMIC_MACRO_NO_NESTING

#define GRAVE_ESC_CTRL_OVERRIDE

#define IGNORE_MOD_TAP_INTERRUPT

#ifdef NKRO_ENABLE
#define FORCE_NKRO
#endif

#ifdef PERMISSIVE_HOLD
#undef PERMISSIVE_HOLD
#endif

#ifndef ONESHOT_TIMEOUT
#define ONESHOT_TIMEOUT 2000
#endif

#define RCPC_KEYS KC_LCTL, KC_LSFT, KC_0

#if !defined(NO_DEBUG) && !defined(CONSOLE_ENABLE)
#define NO_DEBUG
#endif

#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif
