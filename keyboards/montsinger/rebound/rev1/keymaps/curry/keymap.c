#include "curry.h"

#define LAYOUT_rebound_base( \
        K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
        K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
        K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
    ) \
    LAYOUT_ortho_4x12_wrapper( \
        KC_TAB,  K01,     K02,     K03,     K04,     K05,     K06,     K07,     K08,     K09,     K0A,     KC_BSPC, \
        KC_ESC,  K11,     K12,     K13,     K14,     K15,     K16,     K17,     K18,     K19,     K1A,     KC_QUOT, \
        KC_LSFT, K21,     K22,     K23,     K24,     K25,     K26,     K27,     K28,     K29,     K2A,     KC_ENT,  \
        ADJUST,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
    )
#define LAYOUT_rebound_base_wrapper(...)       LAYOUT_rebound_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#if defined(ENABLE_QWERTY)
    [_QWERTY] = LAYOUT_rebound_base_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),
#endif

#if defined(ENABLE_COLEMAK)
    [_COLEMAK] = LAYOUT_rebound_base_wrapper(
        _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
        _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
        _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
    ),
#endif

#if defined(ENABLE_DVORAK)
    [_DVORAK] = LAYOUT_rebound_base_wrapper(
        _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
        _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
        _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
    ),
#endif

#if defined(ENABLE_WORKMAN)
    [_WORKMAN] = LAYOUT_rebound_base_wrapper(
        _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
        _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
        _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
    ),
#endif

    [_LOWER] = LAYOUT_ortho_4x12_wrapper(
        KC_F11,  _________________LOWER_L1__________________, _________________LOWER_R1__________________, KC_F12,
        KC_GRV,  _________________LOWER_L2__________________, _________________LOWER_R2__________________, KC_PIPE,
        _______, _________________LOWER_L3__________________, _________________LOWER_R3__________________, _______,
        _______, ___________________BLANK___________________, ___________________BLANK___________________, _______
    ),

    [_RAISE] = LAYOUT_ortho_4x12_wrapper(
        _______, _________________RAISE_L1__________________, _________________RAISE_R1__________________, KC_DEL,
        KC_TILD, _________________RAISE_L2__________________, _________________RAISE_R2__________________, KC_BSLS,
        _______, _________________RAISE_L3__________________, _________________RAISE_R3__________________, _______,
        _______, ___________________BLANK___________________, ___________________BLANK___________________, _______
    ),

    [_ADJUST] =  LAYOUT_ortho_4x12_wrapper(
        KC_MAKE, ___________________BLANK___________________, _________________ADJUST_R1_________________, KC_RST,
        VRSN,    _________________ADJUST_L2_________________, _________________ADJUST_R2_________________, EE_CLR,
        MG_NKRO, ___________________BLANK___________________, _________________ADJUST_R3_________________, _______,
        _______, ___________________BLANK___________________, ___________________BLANK___________________, _______
    )


};
