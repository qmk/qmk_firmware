#include "drashna.h"

/*
 * The `LAYOUT_gergo_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */
// clang-format off
#define LAYOUT_gergo_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_gergo_wrapper( \
    KC_ESC,  K01,    K02,     K03,      K04,     K05,                                                K06,     K07,     K08,     K09,     K0A,    KC_PIPE,      \
    LALT_T(KC_TAB), K11, K12, K13,      K14,     K15,     _______,                         _______,  K16,     K17,     K18,     K19,     K1A, RALT_T(KC_QUOT), \
    OS_LSFT, CTL_T(K21), K22, K23,      K24,     K25,     _______, _______,       _______, _______,  K26,     K27,     K28,     K29, RCTL_T(K2A), OS_RSFT,      \
                                       KC_GRV,   KC_SPC,  BK_LWER, OS_LALT,       OS_RGUI, DL_RAIS, KC_ENT, _______                            \
    )

#define LAYOUT_gergo_base_wrapper(...)       LAYOUT_gergo_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_gergo_base_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
        ),
    [_COLEMAK] = LAYOUT_gergo_base_wrapper(
        _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
        _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
        _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
    ),

    [_DVORAK] = LAYOUT_gergo_base_wrapper(
        _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
        _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
        _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
    ),

    [_WORKMAN] = LAYOUT_gergo_base_wrapper(
        _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
        _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
        _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
    ),

    [_NORMAN] = LAYOUT_gergo_base_wrapper(
        _________________NORMAN_L1_________________, _________________NORMAN_L1_________________,
        _________________NORMAN_L2_________________, _________________NORMAN_R2_________________,
        _________________NORMAN_L3_________________, _________________NORMAN_R3_________________
    ),

    [_MALTRON] = LAYOUT_gergo_base_wrapper(
        _________________MALTRON_L1________________, _________________MALTRON_R1________________,
        _________________MALTRON_L2________________, _________________MALTRON_R2________________,
        _________________MALTRON_L3________________, _________________MALTRON_R3________________
    ),

    [_EUCALYN] = LAYOUT_gergo_base_wrapper(
        _________________EUCALYN_L1________________, _________________EUCALYN_R1________________,
        _________________EUCALYN_L2________________, _________________EUCALYN_R2________________,
        _________________EUCALYN_L3________________, _________________EUCALYN_R3________________
    ),

    [_CARPLAX] = LAYOUT_gergo_base_wrapper(
        _____________CARPLAX_QFMLWY_L1_____________, _____________CARPLAX_QFMLWY_R1_____________,
        _____________CARPLAX_QFMLWY_L2_____________, _____________CARPLAX_QFMLWY_R2_____________,
        _____________CARPLAX_QFMLWY_L3_____________, _____________CARPLAX_QFMLWY_R3_____________
    ),

    [_MODS] = LAYOUT_gergo_wrapper(
        _______, ___________________BLANK___________________,                                           ___________________BLANK___________________, _______,
        _______, ___________________BLANK___________________, _______,                         _______, ___________________BLANK___________________, _______,
        KC_LSFT, ___________________BLANK___________________, _______, _______,       _______, _______, ___________________BLANK___________________, KC_RSFT,
                                            _______, _______, _______, _______,       _______, _______, _______, _______
        ),
    [_LOWER] = LAYOUT_gergo_wrapper(
        KC_F12,  _________________LOWER_L1__________________,                                           _________________LOWER_R1__________________, KC_F11,
        _______, _________________LOWER_L2__________________, _______,                         _______, _________________LOWER_R2__________________, KC_PIPE,
        _______, _________________LOWER_L3__________________, _______, _______,       _______, _______, _________________LOWER_R3__________________, _______,
                                            _______, _______, _______, _______,       _______, _______, _______, _______
        ),

    [_RAISE] = LAYOUT_gergo_wrapper(
        _______, _________________RAISE_L1__________________,                                           _________________RAISE_R1__________________, _______,
        _______, _________________RAISE_L2__________________, _______,                         _______, _________________RAISE_R2__________________, KC_BSLS,
        _______, _________________RAISE_L3__________________, _______, _______,       _______, _______, _________________RAISE_R3__________________, _______,
                                            _______, _______, _______, _______,       _______, _______, _______, _______
        ),

    [_ADJUST] = LAYOUT_gergo_wrapper(
        KC_MAKE, _________________ADJUST_L1_________________,                                           _________________ADJUST_R1_________________, KC_RESET,
        VRSN,    _________________ADJUST_L2_________________, _______,                         KC_NUKE, _________________ADJUST_R2_________________, EEP_RST,
        _______, _________________ADJUST_L3_________________, _______, _______,       _______, _______, _________________ADJUST_R3_________________, TG_MODS,
                                            _______, _______, _______, _______,       _______, _______, _______, _______
        ),

};

/* Keymap template

    [SYMB] = LAYOUT_gergo_wrapper(
        _______, _______, _______, _______, _______, _______,                                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______, _______,       _______, _______, _______, _______
        ),

    */
// clang-format on
