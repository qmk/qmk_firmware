#include "../../config.h"

/**
 *JD45 keymap definition macro
 */
#define LAYOUT_JD45( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11, K12, K13, \
    K14, K15, K16, K17, K18, K19, K20, K21, K22, K23, K24, K25, \
    K26, K27, K28, K29, K30, K31, K32, K33, K34, K35, K36, K37, \
    K38, K39, K40, K41, K42, K43, K44, K45, K46, K47 \
) { \
    { K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K10,   K11,   K12,   K13   }, \
    { K14,   K15,   K16,   K17,   K18,   K19,   K20,   K21,   K22,   K23,   K24,   K25,   KC_NO }, \
    { K26,   K27,   K28,   K29,   K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   KC_NO }, \
    { K38,   K39,   K40,   K41,   K42,   KC_NO, K43,   KC_NO, K44,   K45,   K46,   K47,   KC_NO }  \
}

// this makes it possible to do rolling combos (zx) with keys that
// convert to other keys on hold (z becomes ctrl when you hold it,
// and when this option isn't enabled, z rapidly followed by x
// actually sends Ctrl-x. That's bad.)
#define IGNORE_MOD_TAP_INTERRUPT
#undef PERMISSIVE_HOLD
#undef PREVENT_STUCK_MODIFIERS

#define FORCE_NKRO

#ifndef TAPPING_TOGGLE
  #define TAPPING_TOGGLE  1
#endif

#ifdef TAPPING_TERM
  #undef TAPPING_TERM
#endif // TAPPING_TERM

#define TAPPING_TERM 300

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
