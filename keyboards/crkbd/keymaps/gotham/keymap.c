#include QMK_KEYBOARD_H
#include "gotham.h"

#ifdef OLED_DRIVER_ENABLE
#    include "oled.c"
#endif

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#    include "rgb.c"
#endif

enum crkbd_keybodes {
  RGBRST = NEW_SAFE_RANGE
};


/*
 * The `LAYOUT_crkbd_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */

// clang-format off
#define LAYOUT_crkbd_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
    ALT_ESC,  K01,  K02,  K03,  K04,  K05,    K06,  K07,  K08,  K09,  K0A,  KC_BSLS, \
    KC_LSFT,  K11,  K12,  K13,  K14,  K15,    K16,  K17,  K18,  K19,  K1A,  RSFT_T(KC_QUOT), \
    CTL_EQL,  K21,  K22,  K23,  K24,  K25,    K26,  K27,  K28,  K29,  K2A,  RCTL_T(KC_MINS), \
                KC_LGUI, SP_LOWR, TB_RAIS,    EN_LOWR,  BK_RAIS, MS_DEL \
  )
/* Re-pass though to allow templates to be used */
#define LAYOUT_crkbd_base_wrapper(...)       LAYOUT_crkbd_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_crkbd_base_wrapper(
    _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
    _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
    _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
  ),

  [_COLEMAK] = LAYOUT_crkbd_base_wrapper(
    _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
    _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
    _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
  ),

  [_DVORAK] = LAYOUT_crkbd_base_wrapper(
    _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
    _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
    _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
  ),

  [_WORKMAN] = LAYOUT_crkbd_base_wrapper(
    _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
    _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
    _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
  ),

  [_NORMAN] = LAYOUT_crkbd_base_wrapper(
    _________________NORMAN_L1_________________, _________________NORMAN_L1_________________,
    _________________NORMAN_L2_________________, _________________NORMAN_R2_________________,
    _________________NORMAN_L3_________________, _________________NORMAN_R3_________________
  ),

  [_GAME] = LAYOUT_wrapper(
    GN_ESC,  __________________GAME_L1__________________,   _________________QWERTY_R1_________________, TG_GAME,
    _______, __________________GAME_L2__________________,   _________________QWERTY_R2_________________, TG_GNAV,
    _______, __________________GAME_L3__________________,   _________________QWERTY_R3_________________, _______,
                                 KC_LALT, KC_SPC, GN_TAB,   KC_ENT, KC_BSPC, KC_DEL
  ),

  [_GAMENAV] = LAYOUT_wrapper(
    _______, ___________________BLANK___________________,   ___________________BLANK___________________, _______,
    _______, ___________________BLANK___________________,   _______, _______, KC_UP,   _______, _______, _______,
    _______, ___________________BLANK___________________,   _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______, _______,
                               _______, _______, _______,   _______, _______, _______
  ),

  [_GAMENUM] = LAYOUT_wrapper(
    _______, KC_NO,  KC_1, KC_2, KC_3, KC_NO,    TG_GAME,  KC_F1,  KC_F2,  KC_F3,  KC_F10, _______,
    _______, KC_0,   KC_4, KC_5, KC_6, KC_NO,    KC_NO,    KC_F4,  KC_F5,  KC_F6,  KC_F11, _______,
    _______, KC_NO,  KC_7, KC_8, KC_9, KC_NO,    KC_NO,    KC_F7,  KC_F8,  KC_F9,  KC_F12, _______,
                   _______, _______, _______,    _______, _______, _______
  ),

  [_LOWER] = LAYOUT_crkbd_base_wrapper(
    _________________LOWER_L1__________________, _________________LOWER_R1__________________,
    _________________LOWER_L2__________________, _________________LOWER_R2__________________,
    _________________LOWER_L3__________________, _________________LOWER_R3__________________
  ),

  [_RAISE] = LAYOUT_crkbd_base_wrapper(
    _________________RAISE_L1__________________, _________________RAISE_R1__________________,
    _________________RAISE_L2__________________, _________________RAISE_R2__________________,
    _________________RAISE_L3__________________, _________________RAISE_R3__________________
  ),

  [_ADJUST] = LAYOUT_wrapper(
    _______, _________________ADJUST_L1_________________,   _________________ADJUST_R1_________________, TG_GAME,
    _______, _________________ADJUST_L2_________________,   _________________ADJUST_R2_________________, _______,
    _______, _________________ADJUST_L3_________________,   MU_TOG, RGB_SAD, RGB_VAD, RGB_HUD, RGBRST,   _______,
                               _______, _______, _______,   _______, _______, _______

  ),

  [_MOUSE] = LAYOUT_crkbd_base_wrapper(
    ___________________KC_NO___________________, __________________MOUSE1___________________,
    ___________________KC_NO___________________, __________________MOUSE2___________________,
    ___________________KC_NO___________________, __________________MOUSE3___________________
  ),
};
// clang-format on

layer_state_t layer_state_set_keymap(layer_state_t state) {
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    /* For any layer other than default, save current RGB state and switch to layer-based RGB */
    if (layer_state_cmp(state, 0)) {
        restore_rgb_config();
    } else {
        uint8_t layer = get_highest_layer(state);
        if (layer_state_cmp(layer_state, 0)) save_rgb_config();
        rgb_by_layer(layer);
    }
#endif
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_DRIVER_ENABLE
    if (record->event.pressed) {
        oled_timer = timer_read();
        add_keylog(keycode);
    }
#endif

    switch (keycode) {
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
        case RGB_MOD:
        case RGB_TOG:
        case RGB_HUI:
        case RGB_HUD:
        case RGB_SAI:
        case RGB_SAD:
        case RGB_VAI:
        case RGB_VAD:
        case RGB_SPI:
        case RGB_SPD:
            /* Override layer-based RGB and resume RGB effect to be able to preview changes */
            if (record->event.pressed) {
                restore_rgb_config();
                process_rgb(keycode, record);
                save_rgb_config();
            }
            return false;
        case RGBRST:
            if (record->event.pressed) {
#    ifdef RGBLIGHT_ENABLE
                eeconfig_update_rgblight_default();
                rgblight_enable();
#    elif RGB_MATRIX_ENABLE
                eeconfig_update_rgb_matrix_default();
                rgb_matrix_enable();
#    endif
                save_rgb_config();
            }
            return false;
#endif
    }
    return true;
}
