#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/**
 *TV44 keymap definition macro
 */
#define KEYMAP_TV44( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11, K12, \
    K13, K14, K15, K16, K17, K18, K19, K20, K21, K22, K23, K24, \
    K25, K26, K27, K28, K29, K30, K31, K32, K33, K34, K35, K36, \
    K37,   K38,   K39,     K40,     K41,     K42,   K43,   K44  \
) { \
    { K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K10,   K11,   K12, }, \
    { K13,   K14,   K15,   K16,   K17,   K18,   K19,   K20,   K21,   K22,   K23,   K24, }, \
    { K25,   K26,   K27,   K28,   K29,   K30,   K31,   K32,   K33,   K34,   K35,   K36, }, \
    { K37,   K38,   K39,   K40, KC_NO, KC_NO,  KC_NO,  K41,   K42,   K43, KC_NO,   K44  }  \
}

/**
 *TV45 keymap definition macro (arrows layout)
 */
#define KEYMAP_TV45( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11, K12, \
    K13, K14, K15, K16, K17, K18, K19, K20, K21, K22, K23, K24, \
    K25, K26, K27, K28, K29, K30, K31, K32, K33, K34, K35, K36, \
    K37,   K38,   K39,     K40,     K41,    K42, K43, K44, K45  \
) { \
    { K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K10,   K11,   K12, }, \
    { K13,   K14,   K15,   K16,   K17,   K18,   K19,   K20,   K21,   K22,   K23,   K24, }, \
    { K25,   K26,   K27,   K28,   K29,   K30,   K31,   K32,   K33,   K34,   K35,   K36, }, \
    { K37,   K38,   K39,   K40, KC_NO, KC_NO,  KC_NO,  K41,   K42,   K43,   K44,   K45  }  \
}

#endif
