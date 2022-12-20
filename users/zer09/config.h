#ifndef USERSPACE_CONFIG_H
#define USERSPACE_CONFIG_H

// this makes it possible to do rolling combos (zx) with keys that
// convert to other keys on hold (z becomes ctrl when you hold it,
// and when this option isn't enabled, z rapidly followed by x
// actually sends Ctrl-x. That's bad.)
#define IGNORE_MOD_TAP_INTERRUPT
#undef PERMISSIVE_HOLD
#define STRICT_LAYER_RELEASE

#define FORCE_NKRO

#ifndef TAPPING_TOGGLE
#define TAPPING_TOGGLE 1
#endif

#ifdef TAPPING_TERM
#undef TAPPING_TERM
#endif
#define TAPPING_TERM 95

// Disable action_get_macro and fn_actions, since we don't use these
// and it saves on space in the firmware.
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#endif
