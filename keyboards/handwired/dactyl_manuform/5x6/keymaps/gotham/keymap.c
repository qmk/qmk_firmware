/* A standard layout for the Dactyl Manuform 5x6 Keyboard */

#include QMK_KEYBOARD_H
#include "gotham.h"

enum dactyl_5x6_keycodes { KC_EX1 = NEW_SAFE_RANGE, KC_EX2, EX_MODE };

enum extra_key_modes { MODE_SCROLL = 0, MODE_ARROWS_LR, MODE_ARROWS_UD, __MODE_LAST };

static uint8_t extra_key_mode = MODE_SCROLL;
/*
 * The `LAYOUT_dactyl_5x6_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */

// clang-format off
#define LAYOUT_dactyl_5x6_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A,  \
    K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A  \
  ) \
  LAYOUT_wrapper_5x6( \
        KC_ESC,  K01, K02, K03, K04, K05,       K06, K07, K08, K09, K0A, KC_GRV, \
        ALT_ESC, K11, K12, K13, K14, K15,       K16, K17, K18, K19, K1A, KC_BSLS, \
        KC_LSFT, K21, K22, K23, K24, K25,       K26, K27, K28, K29, K2A, RSFT_T(KC_QUOT), \
        CTL_EQL, K31, K32, K33, K34, K35,       K36, K37, K38, K39, K3A, RCTL_T(KC_MINS), \
                 KC_LALT, KC_LGUI,                       KC_EX1, KC_EX2, \
                        SP_LOWR, TB_RAIS,         EN_LOWR, BK_RAIS, \
                          KC_LCTL, KC_LALT,    KC_RALT, KC_DEL, \
                          KC_LCTL, KC_LGUI,    KC_EQL,  EX_MODE \
    )
/* Re-pass though to allow templates to be used */
#define LAYOUT_dactyl_5x6_base_wrapper(...)       LAYOUT_dactyl_5x6_base(__VA_ARGS__)

#define LAYOUT_wrapper_5x6( ... ) LAYOUT_5x6(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_dactyl_5x6_base_wrapper(
        ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________,
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),

    [_COLEMAK] = LAYOUT_dactyl_5x6_base_wrapper(
        ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________,
        _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
        _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
        _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
    ),

    [_DVORAK] = LAYOUT_dactyl_5x6_base_wrapper(
        ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________,
        _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
        _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
        _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
    ),

    [_WORKMAN] = LAYOUT_dactyl_5x6_base_wrapper(
        ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________,
        _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
        _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
        _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
    ),

    [_NORMAN] = LAYOUT_dactyl_5x6_base_wrapper(
        ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________,
        _________________NORMAN_L1_________________, _________________NORMAN_R1_________________,
        _________________NORMAN_L2_________________, _________________NORMAN_R2_________________,
        _________________NORMAN_L3_________________, _________________NORMAN_R3_________________
    ),

    [_GAME] = LAYOUT_wrapper_5x6(
      _______, ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________, _______,
      GN_ESC,  __________________GAME_L1__________________, _________________QWERTY_R1_________________, _______,
      _______, __________________GAME_L2__________________, _________________QWERTY_R2_________________, _______,
      _______, __________________GAME_L3__________________, _________________QWERTY_R3_________________, _______,
                    KC_LALT, KC_LGUI,                                          KC_BSPC, KC_DEL, \
                                      KC_SPC, GN_TAB,            TG_GNAV, KC_ENT, \
                                        KC_LCTL, KC_LALT,     KC_RALT, KC_BSPC, \
                                        KC_LCTL, KC_LGUI,     EX_MODE, KC_EQL
    ),

    [_GAMENAV] = LAYOUT_wrapper_5x6(
      _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
      _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
      _______, ___________________BLANK___________________, _______, _______, KC_UP,   _______, _______, _______,
      _______, ___________________BLANK___________________, _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______, _______,
                    _______, _______,                                           _______, _______, \
                                    _______, _______,            _______, _______, \
                                        _______, _______,     _______, _______, \
                                        _______, _______,     _______, _______
    ),

    [_GAMENUM] = LAYOUT_wrapper_5x6(
      KC_F11,  __________________FN_LEFT__________________, __________________FN_RIGHT_________________, KC_F12,
      _______, KC_NO, KC_1, KC_2, KC_3, KC_NO,              TG_GAME,  KC_F1,  KC_F2,  KC_F3,  KC_F10,    _______,
      _______, KC_0,  KC_4, KC_5, KC_6, KC_NO,              KC_NO,    KC_F4,  KC_F5,  KC_F6,  KC_F11,    _______,
      _______, KC_NO, KC_7, KC_8, KC_9, KC_NO,              KC_NO,    KC_F7,  KC_F8,  KC_F9,  KC_F12,    _______,
                    _______, _______,                                           _______, _______, \
                                    _______, _______,            _______, _______, \
                                        _______, _______,     _______, _______, \
                                        _______, _______,     _______, _______

    ),

    [_LOWER] = LAYOUT_dactyl_5x6_base_wrapper(
      ___________________BLANK___________________,    ___________________BLANK___________________,
      _________________LOWER_L1__________________,    _________________LOWER_R1__________________,
      _________________LOWER_L2__________________,    _________________LOWER_R2__________________,
      _________________LOWER_L3__________________,    _________________LOWER_R3__________________
    ),

    [_RAISE] = LAYOUT_dactyl_5x6_base_wrapper(
      ___________________BLANK___________________,    ___________________BLANK___________________,
      _________________RAISE_L1__________________,    _________________RAISE_R1__________________,
      _________________RAISE_L2__________________,    _________________RAISE_R2__________________,
      _________________RAISE_L3__________________,    _________________RAISE_R3__________________
    ),

    [_ADJUST] = LAYOUT_dactyl_5x6_base_wrapper(
      ___________________BLANK___________________,    ___________________BLANK___________________,
      _________________ADJUST_L1_________________,    _________________ADJUST_R1_________________,
      _________________ADJUST_L2_________________,    _________________ADJUST_R2_________________,
      _________________ADJUST_L3_________________,    _________________ADJUST_R3_________________
    ),

    [_MOUSE] = LAYOUT_dactyl_5x6_base_wrapper(
      ___________________KC_NO___________________,    ___________________KC_NO___________________,
      ___________________KC_NO___________________,    __________________MOUSE1___________________,
      ___________________KC_NO___________________,    __________________MOUSE2___________________,
      ___________________KC_NO___________________,    __________________MOUSE3___________________
    ),
};
// clang-format on

layer_state_t layer_state_set_keymap(layer_state_t state) { return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); }

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    bool pressed = record->event.pressed;
    switch (keycode) {
        case EX_MODE:
            if (pressed) {
                extra_key_mode = (extra_key_mode + 1) % __MODE_LAST;
            }
            break;
        case KC_EX1:
            switch (extra_key_mode) {
                case MODE_SCROLL:
                    pressed ? register_code(KC_MS_WH_DOWN) : unregister_code(KC_MS_WH_DOWN);
                    break;
                case MODE_ARROWS_LR:
                    pressed ? register_code(KC_LEFT) : unregister_code(KC_LEFT);
                    break;
                case MODE_ARROWS_UD:
                    pressed ? register_code(KC_DOWN) : unregister_code(KC_DOWN);
                    break;
                default:
                    pressed ? register_code(KC_LEFT) : unregister_code(KC_LEFT);
            }
            break;
        case KC_EX2:
            switch (extra_key_mode) {
                case MODE_SCROLL:
                    pressed ? register_code(KC_MS_WH_UP) : unregister_code(KC_MS_WH_UP);
                    break;
                case MODE_ARROWS_LR:
                    pressed ? register_code(KC_RIGHT) : unregister_code(KC_RIGHT);
                    break;
                case MODE_ARROWS_UD:
                    pressed ? register_code(KC_UP) : unregister_code(KC_UP);
                    break;
                default:
                    pressed ? register_code(KC_RIGHT) : unregister_code(KC_RIGHT);
            }
            break;
    }
    return true;
}
