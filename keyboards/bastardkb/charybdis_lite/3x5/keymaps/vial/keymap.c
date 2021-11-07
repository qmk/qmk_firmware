/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#ifdef CONSOLE_ENABLE
#include "print.h"
#endif  // CONSOLE_ENABLE

/**
 * The default keymap is a simplified version of the Miryoku layout using
 * a QWERTY alpha base layer.
 */
enum charybdis_vial_keymap_layers {
  LAYER_FIRST = 0,
  LAYER_BASE = LAYER_FIRST,
  LAYER_FUNCTION,
  LAYER_NAVIGATION,
  LAYER_MEDIA,
  LAYER_POINTER,
  LAYER_NUMERAL,
  LAYER_SYMBOLS,
  LAYER_LAST = LAYER_SYMBOLS,
};

enum charybdis_vial_keymap_keycodes {
#ifdef VIA_ENABLE
  USER_RESET = USER00,
#else
  USER_RESET = SAFE_RANGE,
#endif  // VIA_ENABLE
  POINTER_DEFAULT_DPI_FORWARD,
  POINTER_DEFAULT_DPI_REVERSE,
  POINTER_SNIPING_DPI_FORWARD,
  POINTER_SNIPING_DPI_REVERSE,
  SNIPING_MODE,
  SNIPING_MODE_TOGGLE,
  DRAGSCROLL_MODE,
  DRAGSCROLL_MODE_TOGGLE,
  KEYMAP_SAFE_RANGE,
};

#define USR_RST USER_RESET
#define DPI_MOD POINTER_DEFAULT_DPI_FORWARD
#define DPI_RMOD POINTER_DEFAULT_DPI_REVERSE
#define S_D_MOD POINTER_SNIPING_DPI_FORWARD
#define S_D_RMOD POINTER_SNIPING_DPI_REVERSE
#define SNIPING SNIPING_MODE
#define SNP_TOG SNIPING_MODE_TOGGLE
#define DRGSCRL DRAGSCROLL_MODE
#define DRG_TOG DRAGSCROLL_MODE_TOGGLE

#define ESC_MED LT(LAYER_MEDIA, KC_ESC)
#define SPC_NAV LT(LAYER_NAVIGATION, KC_SPC)
#define TAB_FUN LT(LAYER_FUNCTION, KC_TAB)
#define ENT_SYM LT(LAYER_SYMBOLS, KC_ENT)
#define BSP_NUM LT(LAYER_NUMERAL, KC_BSPC)
#define _L_PTR(KC) LT(LAYER_POINTER, KC)

/** Automatically enable sniping-mode on the pointer layer. */
#define AUTO_SNIPING_MODE_ON_LAYER LAYER_POINTER

// clang-format off
#define LAYOUT_charybdis_3x5(...) LAYOUT_split_3x5_3(__VA_ARGS__)

/** QWERTY layout (3 rows, 10 columns). */
#define LAYER_ALPHAS_QWERTY_3x10                                                              \
       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, \
       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, \
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH

/** Thumb clusters used on split 3x5+3 keyboards. */
#define LAYER_ALPHAS_THUMBS_1x6         ESC_MED, SPC_NAV, TAB_FUN, ENT_SYM, BSP_NUM, ESC_MED

/** Convenience row shorthands. */
#define _______________DEAD_HALF_ROW_______________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ______________HOME_ROW_GACS_L______________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX
#define ______________HOME_ROW_GACS_R______________ XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI

/**
 * Layers used on the Charybdis Nano.
 *
 * These layers started off heavily inspired by the Miryoku layout, but trimmed
 * down and tailored for a stock experience that is meant to be fundation for
 * further personalization.
 *
 * See https://github.com/manna-harbour/miryoku for the original layout.
 */

/**
 * Secondary right-hand layer has function keys mirroring the numerals on the
 * primary layer with extras on the pinkie column, plus system keys on the inner
 * column. App is on the tertiary thumb key and other thumb keys are duplicated
 * from the base layer to enable auto-repeat.
 */
#define LAYER_FUNCTION_split_3x5_3                                                            \
    _______________DEAD_HALF_ROW_______________, KC_PSCR,   KC_F7,   KC_F8,   KC_F9,  KC_F12, \
    ______________HOME_ROW_GACS_L______________, KC_SLCK,   KC_F4,   KC_F5,   KC_F6,  KC_F11, \
    _______________DEAD_HALF_ROW_______________, KC_PAUS,   KC_F1,   KC_F2,   KC_F3,  KC_F10, \
                      XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX

/**
 * Tertiary left- and right-hand layer is media and RGB control.  This layer is
 * symmetrical to accomodate the left- and right-hand trackball.
 */
#define LAYER_MEDIA_split_3x5_3                                                               \
    XXXXXXX,RGB_RMOD, RGB_TOG, RGB_MOD, XXXXXXX, XXXXXXX,RGB_RMOD, RGB_TOG, RGB_MOD, XXXXXXX, \
    KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT, KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT, \
    XXXXXXX, XXXXXXX, XXXXXXX, EEP_RST, USR_RST, USR_RST, EEP_RST, XXXXXXX, XXXXXXX, XXXXXXX, \
                      _______, KC_MPLY, KC_MSTP, KC_MSTP, KC_MPLY, _______

/** Mouse emulation and pointer functions. */
#define LAYER_POINTER_split_3x5_3                                                             \
    XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD, S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, \
    ______________HOME_ROW_GACS_L______________, ______________HOME_ROW_GACS_R______________, \
    _______, DRGSCRL, SNIPING, EEP_RST, USR_RST, USR_RST, EEP_RST, SNIPING, DRGSCRL, _______, \
                      KC_BTN2, KC_BTN1, KC_BTN3, KC_BTN3, KC_BTN1, KC_BTN2

/**
 * Primary right-hand layer (left home thumb) is navigation and editing. Cursor
 * keys are on the home position, line and page movement below, clipboard above,
 * caps lock and insert on the inner column. Thumb keys are duplicated from the
 * base layer to avoid having to layer change mid edit and to enable auto-repeat.
 */
#define LAYER_NAVIGATION_split_3x5_3                                                          \
    _______________DEAD_HALF_ROW_______________, _______________DEAD_HALF_ROW_______________, \
    ______________HOME_ROW_GACS_L______________, KC_CLCK, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, \
    _______________DEAD_HALF_ROW_______________,  KC_INS, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, \
                      XXXXXXX, _______, XXXXXXX,  KC_ENT, KC_BSPC,  KC_ESC

/**
 * Primary left-hand layer (right home thumb) is numerals and symbols. Numerals
 * are in the standard numpad locations with symbols in the remaining positions.
 * `KC_DOT` is duplicated from the base layer.
 */
#define LAYER_NUMERAL_split_3x5_3                                                             \
    KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC, _______________DEAD_HALF_ROW_______________, \
    KC_SCLN,    KC_4,    KC_5,    KC_6,  KC_EQL, ______________HOME_ROW_GACS_R______________, \
     KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS, _______________DEAD_HALF_ROW_______________, \
                       KC_DOT,    KC_0, KC_MINS, XXXXXXX, _______, XXXXXXX

/**
 * Secondary left-hand layer has shifted symbols in the same locations to reduce
 * chording when using mods with shifted symbols. `KC_LPRN` is duplicated next to
 * `KC_RPRN`.
 */
#define LAYER_SYMBOLS_split_3x5_3                                                             \
    KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, _______________DEAD_HALF_ROW_______________, \
    KC_COLN,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, ______________HOME_ROW_GACS_R______________, \
    KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_PIPE, _______________DEAD_HALF_ROW_______________, \
                      KC_LPRN, KC_RPRN, KC_UNDS, _______, XXXXXXX, XXXXXXX

/**
 * Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GACS (Gui, Alt, Ctl, Shift)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY_3x10` defined above, eg.:
 *
 *     HOME_ROW_MOD_GACS(LAYER_ALPHAS_QWERTY_3x10)
 */
#define _HOME_ROW_MOD_GACS(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      LGUI_T(L10), LALT_T(L11), LCTL_T(L12), LSFT_T(L13),        L14,  \
             R15,  RSFT_T(R16), RCTL_T(R17), LALT_T(R18), RGUI_T(R19), \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

/**
 * Add pointer layer keys to a layout.
 *
 * Expects a 10-key per row layout.  The layout passed in parameter must contain
 * at least 30 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY_3x10` defined above, eg.:
 *
 *     POINTER_MOD(LAYER_ALPHAS_QUERTY_3x10)
 */
#define _POINTER_MOD(                                                  \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
             L10,         L11,         L12,         L13,         L14,  \
             R15,         R16,         R17,         R18,         R19,  \
      _L_PTR(L20),        L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,  _L_PTR(R29), \
      __VA_ARGS__
#define POINTER_MOD(...) _POINTER_MOD(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_charybdis_3x5(POINTER_MOD(
    HOME_ROW_MOD_GACS(LAYER_ALPHAS_QWERTY_3x10, LAYER_ALPHAS_THUMBS_1x6)
  )),
  [LAYER_FUNCTION] = LAYOUT_charybdis_3x5(LAYER_FUNCTION_split_3x5_3),
  [LAYER_NAVIGATION] = LAYOUT_charybdis_3x5(LAYER_NAVIGATION_split_3x5_3),
  [LAYER_MEDIA] = LAYOUT_charybdis_3x5(LAYER_MEDIA_split_3x5_3),
  [LAYER_NUMERAL] = LAYOUT_charybdis_3x5(LAYER_NUMERAL_split_3x5_3),
  [LAYER_POINTER] = LAYOUT_charybdis_3x5(LAYER_POINTER_split_3x5_3),
  [LAYER_SYMBOLS] = LAYOUT_charybdis_3x5(LAYER_SYMBOLS_split_3x5_3),
};
// clang-format on

/** Whether SHIFT mod is enabled. */
static bool _has_shift_mod(void) {
#ifdef NO_ACTION_ONESHOT
  return mod_config(get_mods()) & MOD_MASK_SHIFT;
#else
  return mod_config(get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;
#endif  // NO_ACTION_ONESHOT
}

#ifdef POINTING_DEVICE_ENABLE
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    case USER_RESET:
      if (record->event.pressed) {
#ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_RED);
#endif  // RGB_MATRIX_ENABLE
      } else {
        reset_keyboard();
      }
      break;
    case POINTER_DEFAULT_DPI_FORWARD:
      if (record->event.pressed) {
        // Step backward if shifted, forward otherwise.
        charybdis_cycle_pointer_default_dpi(/* forward= */ !_has_shift_mod());
      }
      break;
    case POINTER_DEFAULT_DPI_REVERSE:
      if (record->event.pressed) {
        // Step forward if shifted, backward otherwise.
        charybdis_cycle_pointer_default_dpi(/* forward= */ _has_shift_mod());
      }
      break;
    case POINTER_SNIPING_DPI_FORWARD:
      if (record->event.pressed) {
        // Step backward if shifted, forward otherwise.
        charybdis_cycle_pointer_sniping_dpi(/* forward= */ !_has_shift_mod());
      }
      break;
    case POINTER_SNIPING_DPI_REVERSE:
      if (record->event.pressed) {
        // Step forward if shifted, backward otherwise.
        charybdis_cycle_pointer_sniping_dpi(/* forward= */ _has_shift_mod());
      }
      break;
    case SNIPING_MODE:
      charybdis_set_pointer_sniping_enabled(record->event.pressed);
      break;
    case SNIPING_MODE_TOGGLE:
      if (record->event.pressed) {
        charybdis_set_pointer_sniping_enabled(
            !charybdis_get_pointer_sniping_enabled());
      }
      break;
    case DRAGSCROLL_MODE:
      charybdis_set_pointer_dragscroll_enabled(record->event.pressed);
      break;
    case DRAGSCROLL_MODE_TOGGLE:
      if (record->event.pressed) {
        charybdis_set_pointer_dragscroll_enabled(
            !charybdis_get_pointer_dragscroll_enabled());
      }
      break;
  }
  return true;
}

#ifdef AUTO_SNIPING_MODE_ON_LAYER
layer_state_t layer_state_set_kb(layer_state_t state) {
  state = layer_state_set_user(state);
  charybdis_set_pointer_sniping_enabled(
      layer_state_cmp(state, AUTO_SNIPING_MODE_ON_LAYER));
  return state;
}
#endif  // AUTO_SNIPING_MODE_ON_LAYER
#endif  // POINTING_DEVICE_ENABLE

#ifdef CONSOLE_ENABLE
void keyboard_post_init_user(void) { debug_enable = true; }
#endif  // CONSOLE_ENABLE
