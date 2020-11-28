// qmk flash -kb bm40hsrgb -km sigma-squared

#pragma once

#define RGBLIGHT_LAYERS

#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF

//#define RGBLIGHT_ANIMATIONS


#define LAYOUT_sigma2(\
K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K10,   K11,\
K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K20,   K21,   K22,   K23,\
K24,   K25,   K26,   K27,   K28,   K29,   K30,   K31,   K32,   K33,   K34,   K35,\
K36,   K37,   K38,   K39,   K40,       K41,      K42,   KC_43, KC_44, KC_45, K46\
)\
LAYOUT_planck_mit(\
K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K10,   K11,\
K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K20,   K21,   K22,   K23,\
K24,   K25,   K26,   K27,   K28,   K29,   K30,   K31,   K32,   K33,   K34,   K35,\
K36,   K37,   K38,   K39,   K40,       K41,      K42,   KC_43, KC_44, KC_45, K46\
)
