#include "drashna.h"

/*
 * The `LAYOUT_orthodox_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */
// clang-format off
#define LAYOUT_wrapper(...)            LAYOUT(__VA_ARGS__)
#define LAYOUT_orthodox_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
    KC_ESC,  K01,    K02,     K03,      K04,     K05,                                                             K06,     K07,     K08,     K09,     K0A,     KC_BSPC, \
    LALT_T(KC_TAB), K11, K12, K13,      K14,     K15,              OS_LALT, OS_LGUI,   OS_RALT, RAISE,            K16,     K17,     K18,     K19,     K1A, RALT_T(K1B), \
    KC_MLSF, CTL_T(K21), K22, K23,      K24,     K25,     LOWER,   KC_SPACE,KC_BSPC,   KC_DEL,  KC_ENT,  RAISE,   K26,     K27,     K28,     K29, RCTL_T(K2A), KC_MRSF  \
  )
#define LAYOUT_base_wrapper(...)       LAYOUT_orthodox_base(__VA_ARGS__)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT_LAYER_1] = LAYOUT_base_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),

    [_DEFAULT_LAYER_2] = LAYOUT_base_wrapper(
        ______________COLEMAK_MOD_DH_L1____________, ______________COLEMAK_MOD_DH_R1____________,
        ______________COLEMAK_MOD_DH_L2____________, ______________COLEMAK_MOD_DH_R2____________,
        ______________COLEMAK_MOD_DH_L3____________, ______________COLEMAK_MOD_DH_R3____________
    ),
    [_DEFAULT_LAYER_3] = LAYOUT_base_wrapper(
        _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
        _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
        _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
    ),

    [_DEFAULT_LAYER_4] = LAYOUT_base_wrapper(
        _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
        _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
        _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
    ),


  [_LOWER] = LAYOUT_wrapper(\
    KC_TILD, _________________LOWER_L1__________________,                                                               _________________LOWER_R1__________________, KC_BSPC,
    KC_F11,  _________________LOWER_L2__________________,          _______, _______,         _______, _______,          _________________LOWER_R2__________________, KC_PIPE,
    KC_F12,  _________________LOWER_L3__________________, _______, _______, _______,         _______, _______, _______, _________________LOWER_R3__________________, _______
  ),

  [_RAISE] = LAYOUT_wrapper(\
    KC_GRV,  _________________RAISE_L1__________________,                                                               _________________RAISE_R1__________________, KC_BSPC,
    _______, _________________RAISE_L2__________________,          _______, _______,         _______, _______,          _________________RAISE_R2__________________, KC_BSLS,
    _______, _________________RAISE_L3__________________, _______, _______, _______,         _______, _______, _______, _________________RAISE_R3__________________, _______
  ),

  [_ADJUST] = LAYOUT_wrapper(\
    KC_MAKE, _________________ADJUST_L1_________________,                                                               _________________ADJUST_R1_________________, KC_RESET,
    VRSN,    _________________ADJUST_L2_________________,          _______, _______,         _______, KC_NUKE,          _________________ADJUST_R2_________________, EEP_RST,
    TG_MODS, _________________ADJUST_L3_________________, _______, _______, _______,         _______, _______, _______, _________________ADJUST_R3_________________, KC_MPLY
  )

};
// clang-format on

void matrix_init_keymap(void) {
#ifndef CONVERT_TO_PROTON_C
    setPinOutput(D5);
    writePinHigh(D5);

    setPinOutput(B0);
    writePinHigh(B0);
#endif
}
