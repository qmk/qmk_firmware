/**
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
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

enum charybdis_keymap_bstiq_layers {
    LAYER_BASE = 0,
    LAYER_MBO,
    LAYER_MEDIA,
    LAYER_NAV,
    LAYER_MOUSE,
    LAYER_SYM,
    LAYER_NUM,
    LAYER_FUN,
};

// Automatically enable sniping when the mouse layer is on.
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_MOUSE

#define BSP_NAV LT(LAYER_NAV, KC_BSPC)
#define ENT_MBO LT(LAYER_MBO, KC_ENT)
#define TAB_MED LT(LAYER_MEDIA, KC_TAB)
#define ESC_SYM LT(LAYER_SYM, KC_ESC)
#define SPC_NUM LT(LAYER_NUM, KC_SPC)
#define MOUSE(KC) LT(LAYER_MOUSE, KC)

#define USR_RDO KC_AGAIN
#define USR_PST S(KC_INS)
#define USR_CPY C(KC_INS)
#define USR_CUT S(KC_DEL)
#define USR_UND KC_UNDO

#define MS_L KC_MS_LEFT
#define MS_R KC_MS_RIGHT
#define MS_D KC_MS_DOWN
#define MS_U KC_MS_UP

#define WH_L KC_MS_WH_LEFT
#define WH_R KC_MS_WH_RIGHT
#define WH_D KC_MS_WH_DOWN
#define WH_U KC_MS_WH_UP

// clang-format off
/** Convenience macro. */
#define _KC_LAYOUT_wrapper(                                                                             \
         k00,      k01,      k02,      k03,      k04,      k05,      k06,      k07,      k08,      k09, \
         k10,      k11,      k12,      k13,      k14,      k15,      k16,      k17,      k18,      k19, \
         k20,      k21,      k22,      k23,      k24,      k25,      k26,      k27,      k28,      k29, \
         ...)                                                                                           \
    KC_##k00, KC_##k01, KC_##k02, KC_##k03, KC_##k04, KC_##k05, KC_##k06, KC_##k07, KC_##k08, KC_##k09, \
    KC_##k10, KC_##k11, KC_##k12, KC_##k13, KC_##k14, KC_##k15, KC_##k16, KC_##k17, KC_##k18, KC_##k19, \
    KC_##k20, KC_##k21, KC_##k22, KC_##k23, KC_##k24, KC_##k25, KC_##k26, KC_##k27, KC_##k28, KC_##k29, \
    __VA_ARGS__
#define KC_LAYOUT_wrapper(...) _KC_LAYOUT_wrapper(__VA_ARGS__)

/** Base layer with BÉPO layout. */
#define LAYOUT_LAYER_BASE_BEPO KC_LAYOUT_wrapper(               \
       B,    Z,    P,    O, QUOT,  DOT,    V,    D,    L,    J, \
       A,    U,    I,    E, COMM,    C,    T,    S,    R,    N, \
       W,    Y,    X, SLSH,    K,    M,    Q,    G,    H,    F, \
       BSP_NAV, ENT_MBO, TAB_MED,    ESC_SYM, SPC_NUM)

/** Convenience key shorthands. */
#define U_NA KC_NO // Present but not available for use.
#define U_NU KC_NO // Available but not used.

/** Convenience row shorthands. */
#define __________________RESET_L__________________ QK_BOOT,    U_NA,    U_NA,    U_NA,    U_NA
#define __________________RESET_R__________________    U_NA,    U_NA,    U_NA,    U_NA, QK_BOOT
#define ______________HOME_ROW_GASC_L______________ KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL,    U_NA
#define ______________HOME_ROW_ALGR_L______________    U_NA, KC_ALGR,    U_NA,    U_NA,    U_NA
#define ______________HOME_ROW_GASC_R______________    U_NA, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI
#define ______________HOME_ROW_ALGR_R______________    U_NA,    U_NA,    U_NA, KC_ALGR,    U_NA

/** Layers. */

// Buttons.
#define LAYOUT_LAYER_MBO                                                                      \
    __________________RESET_L__________________, USR_RDO, USR_PST, USR_CPY, USR_CUT, USR_UND, \
    ______________HOME_ROW_GASC_L______________, KC_CAPS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, \
    KC_BTN3, KC_ALGR, KC_BTN2, KC_BTN1,    U_NA,  KC_INS, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, \
                         U_NA,    U_NA,    U_NA,  KC_ENT,  KC_DEL

// Media.
#define LAYOUT_LAYER_MEDIA                                                                    \
    __________________RESET_L__________________, USR_RDO, USR_PST, USR_CPY, USR_CUT, USR_UND, \
    ______________HOME_ROW_GASC_L______________,    U_NU,    MS_L,    MS_D,    MS_U,    MS_R, \
    ______________HOME_ROW_ALGR_L______________,    U_NU,    WH_L,    WH_D,    WH_U,    WH_R, \
                         U_NA,    U_NA,    U_NA, KC_BTN1, KC_BTN3

// Navigation.
#define LAYOUT_LAYER_NAV                                                                      \
    __________________RESET_L__________________, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, \
    ______________HOME_ROW_GASC_L______________,    U_NU, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, \
    ______________HOME_ROW_ALGR_L______________,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU, \
                         U_NA,    U_NA,    U_NA, KC_MSTP, KC_MPLY

// Mouse.
#define LAYOUT_LAYER_MOUSE                                                                    \
    S_D_MOD, USR_PST, USR_CPY, USR_CUT, USR_UND, USR_RDO, USR_PST, USR_CPY, USR_CUT, USR_UND, \
    DPI_MOD, DRGSCRL, KC_LSFT, KC_LCTL, _______,    U_NU,    MS_L,    MS_D,    MS_U,    MS_R, \
    USR_RDO, USR_PST, USR_CPY, USR_CUT, USR_UND,    U_NU,    WH_L,    WH_D,    WH_U,    WH_R, \
                      KC_BTN2, KC_BTN1, KC_BTN3, KC_BTN1, KC_BTN3

// Symbols.
#define LAYOUT_LAYER_SYM                                                                      \
    KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, __________________RESET_R__________________, \
    KC_COLN,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, ______________HOME_ROW_GASC_R______________, \
    KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_PIPE, ______________HOME_ROW_ALGR_R______________, \
                      KC_LPRN, KC_RPRN, KC_UNDS,    U_NA,    U_NA

// Numerals.
#define LAYOUT_LAYER_NUM                                                                      \
    KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC, __________________RESET_R__________________, \
    KC_SCLN,    KC_4,    KC_5,    KC_6,  KC_EQL, ______________HOME_ROW_GASC_R______________, \
     KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS, ______________HOME_ROW_ALGR_R______________, \
                       KC_DOT,    KC_0, KC_MINS,    U_NA,    U_NA

// Function keys.
#define LAYOUT_LAYER_FUN                                                                      \
     KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR, __________________RESET_R__________________, \
     KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL, ______________HOME_ROW_GASC_R______________, \
     KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS, ______________HOME_ROW_ALGR_R______________,\
                       KC_APP,  KC_SPC,  KC_TAB,    U_NA,    U_NA

/**
 * Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GASC (Gui, Alt, Shift, Ctl)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with `LAYOUT_LAYER_BASE_BEPO` defined above, eg.:
 *
 *     HOME_ROW_MOD_GASC(LAYOUT_LAYER_BASE_BEPO)
 */
#define _HOME_ROW_MOD_GASC(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      LGUI_T(L10), LALT_T(L11), LSFT_T(L12), LCTL_T(L13),        L14,  \
             R15,  RCTL_T(R16), RSFT_T(R17), LALT_T(R18), RGUI_T(R19), \
      __VA_ARGS__
#define HOME_ROW_MOD_GASC(...) _HOME_ROW_MOD_GASC(__VA_ARGS__)

/**
 * Add mouse layer keys to a layout.
 *
 * Expects a 10-key per row layout.  The layout passed in parameter must contain
 * at least 30 keycodes.
 *
 * This is meant to be used with `LAYOUT_LAYER_BASE_BEPO` defined above, eg.:
 *
 *     MOUSE_MOD(LAYOUT_LAYER_BASE_BEPO)
 */
#define _MOUSE_MOD(                                               \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,             \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,             \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,             \
    ...)                                                          \
            L00,        L01,        L02,        L03,        L04,  \
            R05,        R06,        R07,        R08,        R09,  \
            L10,        L11,        L12,        L13,        L14,  \
            R15,        R16,        R17,        R18,        R19,  \
      MOUSE(L20),       L21,        L22,        L23,        L24,  \
            R25,        R26,        R27,        R28,  MOUSE(R29), \
      __VA_ARGS__
#define MOUSE_MOD(...) _MOUSE_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(
    MOUSE_MOD(HOME_ROW_MOD_GASC(LAYOUT_LAYER_BASE_BEPO))
  ),
  [LAYER_MBO] = LAYOUT_wrapper(LAYOUT_LAYER_MBO),
  [LAYER_MEDIA] = LAYOUT_wrapper(LAYOUT_LAYER_MEDIA),
  [LAYER_NAV] = LAYOUT_wrapper(LAYOUT_LAYER_NAV),
  [LAYER_MOUSE] = LAYOUT_wrapper(LAYOUT_LAYER_MOUSE),
  [LAYER_SYM] = LAYOUT_wrapper(LAYOUT_LAYER_SYM),
  [LAYER_NUM] = LAYOUT_wrapper(LAYOUT_LAYER_NUM),
  [LAYER_FUN] = LAYOUT_wrapper(LAYOUT_LAYER_FUN),
};
// clang-format on

#if defined(POINTING_DEVICE_ENABLE) && defined(CHARYBDIS_AUTO_SNIPING_ON_LAYER)
layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#endif // POINTING_DEVICE_ENABLE && CHARYBDIS_AUTO_SNIPING_ON_LAYER

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif
