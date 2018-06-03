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
    { K38,   K39,   K40,   K41,   K42, KC_NO,   K43, KC_NO,   K44,   K45,   K46,   K47,   KC_NO }  \
}

/**
 * This makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when
 * you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)
 */
#define IGNORE_MOD_TAP_INTERRUPT

/**
 * Improve the smootheness of mouse interaction
 */
#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_DELAY          0
#define MOUSEKEY_TIME_TO_MAX    5
#define MOUSEKEY_MAX_SPEED      2
#define MOUSEKEY_WHEEL_DELAY    0