#pragma once

#ifndef QMK_KEYS_PER_SCAN
  #define QMK_KEYS_PER_SCAN 4
#endif // QMK KEYS PER SCAN

// this makes it possible to do rolling combos (zx) with keys that
// convert to other keys on hold (z becomes ctrl when you hold it,
// and when this option isn't enabled, z rapidly followed by x
// actually sends Ctrl-x. That's bad.)
#define IGNORE_MOD_TAP_INTERRUPT
#undef PERMISSIVE_HOLD

#ifdef TAPPING_TERM
#undef TAPPING_TERM
#endif // TAPPING_TERM
#define TAPPING_TERM 175

// Disable action_get_macro and fn_actions, since we don't use these
// and it saves on space in the firmware.
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#define DISABLE_LEADER

#define MACRO_TIMER 5
