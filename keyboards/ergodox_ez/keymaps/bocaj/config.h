#ifndef USERSPACE_CONFIG_H
  #define USERSPACE_CONFIG_H

  #ifndef ONESHOT_TAP_TOGGLE
    #define ONESHOT_TAP_TOGGLE 2
  #endif // ONESHOT_TAP_TOGGLE

  #ifndef ONESHOT_TIMEOUT
    #define ONESHOT_TIMEOUT 3000
  #endif // ONESHOT_TIMEOUT

  #ifndef QMK_KEYS_PER_SCAN
    #define QMK_KEYS_PER_SCAN 4
  #endif // QMK KEYS PER SCAN

  // Testing Autoshift
  #define NO_AUTO_SHIFT_SPECIAL
  #define NO_AUTO_SHIFT_NUMERIC
  #define AUTO_SHIFT_SETUP

  // this makes it possible to do rolling combos (zx) with keys that
  // convert to other keys on hold (z becomes ctrl when you hold it,
  // and when this option isn't enabled, z rapidly followed by x
  // actually sends Ctrl-x. That's bad.)
  #define IGNORE_MOD_TAP_INTERRUPT
  #undef PERMISSIVE_HOLD
  #undef PREVENT_STUCK_MODIFIERS

  #ifndef TAPPING_TOGGLE
    #define TAPPING_TOGGLE  2
  #endif

  #ifdef TAPPING_TERM
    #undef TAPPING_TERM
  #endif
  #define TAPPING_TERM 200

  // Disable action_get_macro and fn_actions, since we don't use these
  // and it saves on space in the firmware.
  #define NO_ACTION_MACRO
  #define NO_ACTION_FUNCTION

#endif // !USERSPACE_CONFIG_H
