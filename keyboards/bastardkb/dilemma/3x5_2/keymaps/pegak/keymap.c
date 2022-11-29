/**
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2022 Petr Glaser <syreanis+1@gmail.com> (@pegak)
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
#include "sendstring_czech.h"
#include "features/achordion.h"
#include "features/autocorrection.h"
#include "features/select_word.h"

enum bstiq_layers {
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
#define DILEMMA_AUTO_SNIPING_ON_LAYER LAYER_MOUSE

#define SPC_NAV LT(LAYER_NAV, KC_SPC)
#define TAB_MED LT(LAYER_MEDIA, KC_TAB)
#define BSP_NUM LT(LAYER_NUM, KC_BSPC)
#define ENT_SYM LT(LAYER_SYM, KC_ENT)
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
// Multichar shortcuts
enum custom_keycodes {
    COAL = SAFE_RANGE,
    OR,
    AND,
    ARR,
    SEQL,
    NEQL,
    BVAR,
    CO_SPC,
    OPT,
    COMM,

    TD_CZ_U,

    NEXTSEN,
    SELWORD,
    SRCHSEL,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    //[TD_CZ_U] = ACTION_TAP_DANCE_DOUBLE(CZ_U, CZ_URNG)
    //[TD_CZ_U] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
};

void matrix_scan_user(void) {
  achordion_task();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_achordion(keycode, record)) { return false; }
    if (!process_autocorrection(keycode, record)) { return false; }
    if (!process_select_word(keycode, record, SELWORD)) { return false; }

    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();

    switch (keycode) {
        case NEXTSEN:  // Next sentence macro.
            if (record->event.pressed) {
                SEND_STRING(". ");
                add_oneshot_mods(MOD_BIT(KC_LSFT));  // Set one-shot mod for shift.
            }
            return false;
        case COAL:
            if (record->event.pressed) {
                SEND_STRING("??");
            }
            return false;
        case OR:
            if (record->event.pressed) {
                SEND_STRING("||");
            }
            return false;
        case AND:
            if (record->event.pressed) {
                SEND_STRING("&&");
            }
            return false;
        case ARR:
            if (record->event.pressed) {
                if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {  // Is shift held?
                    del_mods(MOD_MASK_SHIFT);  // Temporarily delete shift.
                    del_oneshot_mods(MOD_MASK_SHIFT);
                    SEND_STRING("->");
                    set_mods(mods);            // Restore mods.
                } else {
                    SEND_STRING("=>");
                }
            }
            return false;
        case SEQL:
            if (record->event.pressed) {
                SEND_STRING("===");
            }
            return false;
        case NEQL:
            if (record->event.pressed) {
                SEND_STRING("!==");
            }
            return false;
        case BVAR:
            if (record->event.pressed) {
                SEND_STRING("${");
            }
            return false;
        case CO_SPC:
            if (record->event.pressed) {
                SEND_STRING(": ");
            }
            return false;
        case OPT:
            if (record->event.pressed) {
                SEND_STRING("?.");
            }
            return false;
        case COMM:
            if (record->event.pressed) {
                SEND_STRING("/*");
            }
            return false;
        case SRCHSEL:  // Searches the current selection in a new tab.
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("ct") SS_DELAY(100) SS_LCTL("v") SS_TAP(X_ENTER));
            }
            return false;
    }

    return true;
}

/** Base layer with special QWERTZ layout. */
#define LAYOUT_LAYER_BASE                                                                               \
       CZ_Q,    CZ_W,    CZ_E,    CZ_R,    CZ_T,    CZ_Z,    CZ_U,  CZ_I,       CZ_O,      CZ_P,    \
       CZ_A,    CZ_S,    CZ_D,    CZ_F,    CZ_G,    CZ_H,    CZ_J,      CZ_K,       CZ_L,      CZ_ACUT, \
       CZ_Y,    CZ_X,    CZ_C,    CZ_V,    CZ_B,    CZ_N,    CZ_M,      CZ_COMM,    CZ_DOT,    CZ_CARN, \
                                SPC_NAV,   TAB_MED, ENT_SYM, BSP_NUM

/** Convenience key shorthands. */
#define U_NA KC_NO // Present but not available for use.
#define U_NU KC_NO // Available but not used.

/** Convenience row shorthands. */
#define ________________HOME_ROW_NA________________    U_NA,    U_NA,    U_NA,    U_NA,    U_NA
#define ______________HOME_ROW_GASC_L______________ KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL,    U_NA
#define ______________HOME_ROW_ALGR_L______________    U_NA, KC_ALGR,    U_NA,    U_NA,    U_NA
#define ______________HOME_ROW_GASC_R______________    U_NA, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI
#define ______________HOME_ROW_ALGR_R______________    U_NA,    U_NA,    U_NA, KC_ALGR,    U_NA

/* Layers */
// Main right
#define LAYOUT_LAYER_NAV                                                                                   \
       U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    KC_CAPS,   KC_MYCM,     KC_HOME, KC_END,    SRCHSEL,   \
       KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NU,    CAPS_WORD, KC_LEFT,     KC_DOWN, KC_UP,     KC_RGHT,   \
       U_NU,    USR_CUT, USR_CPY, USR_PST, U_NU,    SELWORD,   KC_WBAK,     U_NU,    NEXTSEN,   KC_WFWD,   \
                                U_NA,      U_NU,    KC_PGDN,   KC_PGUP

// Main right
#define LAYOUT_LAYER_MEDIA                                                                             \
       U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU,      KC_MUTE,  KC_MPLY,    U_NU,     U_NU,   \
       KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NU,    U_NU,      KC_MPRV,  KC_VOLD, KC_VOLU,  KC_MNXT,   \
       U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU,      U_NU,     U_NU,    U_NU,     U_NU,      \
                                U_NA,      U_NU,    U_NU,      U_NU

// Main left
#define LAYOUT_LAYER_SYM                                                                                              \
       CZ_RNGA,    CZ_GRV,    CZ_LCBR,    CZ_RCBR,    CZ_SLSH,    COAL,    ARR,       SEQL,    NEQL,      BVAR,       \
       CZ_SCLN,    CZ_QUOT,   CZ_LPRN,    CZ_RPRN,    CZ_CIRC,    OR,      CZ_LABK,   CZ_RABK, CZ_PIPE,   CZ_EXLM,    \
       CZ_BSLS,    CZ_DQUO,   CZ_LBRC,    CZ_RBRC,    CZ_TILD,    AND,     CO_SPC,    OPT,     COMM,      KC_LSFT,    \
                                CZ_ACUT,  CZ_CARN,    U_NA,       U_NU

// Main left
#define LAYOUT_LAYER_NUM                                                                                   \
       CZ_MINS,    CZ_7,    CZ_8,    CZ_9,    CZ_SLSH, U_NU,      U_NU,     U_NU,    U_NU,      U_NU,      \
       CZ_PLUS,    CZ_4,    CZ_5,    CZ_6,    CZ_ASTR, U_NU,      CZ_LPRN,  CZ_RPRN, CZ_LABK,   CZ_RABK,   \
       CZ_EQL,     CZ_1,    CZ_2,    CZ_3,    CZ_PERC, U_NU,      U_NU,     U_NU,    U_NU,      U_NU,      \
                                    CZ_0,     U_NU,    U_NU,      U_NA

// Main both
#define LAYOUT_LAYER_MOUSE                                                                                 \
       U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    KC_CAPS,   KC_BTN1,     KC_BTN2, KC_BTN3,   KC_WSCH,   \
       KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NU,    U_NU,      MS_L,        MS_D,    MS_U,      MS_R,      \
       U_NU,    USR_CUT, USR_CPY, USR_PST, U_NU,    U_NU,      WH_L,        WH_D,    WH_U,      WH_R,      \
                                KC_BTN2,   U_NA,    KC_BTN1, KC_BTN3

/** Layers by Quentin */
// Buttons.
#define LAYOUT_LAYER_MBO                                                                      \
    ________________HOME_ROW_NA________________, USR_RDO, USR_PST, USR_CPY, USR_CUT, USR_UND, \
    ______________HOME_ROW_GASC_L______________, KC_BSPC, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, \
    KC_BTN3, KC_ALGR, KC_BTN2, KC_BTN1,    U_NA,  KC_DEL, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, \
                                  U_NA,    U_NA,  KC_ENT,  KC_ENT

// Media.
#define LAYOUT_LAYER_MEDIA_OLD                                                                    \
    ________________HOME_ROW_NA________________, USR_RDO, USR_PST, USR_CPY, USR_CUT, USR_UND, \
    ______________HOME_ROW_GASC_L______________,    U_NU,    MS_L,    MS_D,    MS_U,    MS_R, \
    ______________HOME_ROW_ALGR_L______________,    U_NU,    WH_L,    WH_D,    WH_U,    WH_R, \
                                  U_NA,    U_NA, KC_BTN1, KC_BTN3

// Navigation.
#define LAYOUT_LAYER_NAV_OLD                                                                  \
    ________________HOME_ROW_NA________________, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, \
    ______________HOME_ROW_GASC_L______________,    U_NU, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, \
    ______________HOME_ROW_ALGR_L______________,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU, \
                                  U_NA,    U_NA, KC_MSTP, KC_MPLY

// Mouse.
#define LAYOUT_LAYER_MOUSE_OLD                                                                \
    S_D_MOD, USR_PST, USR_CPY, USR_CUT, USR_UND, USR_RDO, USR_PST, USR_CPY, USR_CUT, USR_UND, \
    DPI_MOD, DRGSCRL, KC_LSFT, DRGSCRL, _______,    U_NU,    MS_L,    MS_D,    MS_U,    MS_R, \
    USR_RDO, USR_PST, USR_CPY, KC_BTN3, USR_UND,    U_NU,    WH_L,    WH_D,    WH_U,    WH_R, \
                               KC_BTN1, KC_BTN2, KC_BTN1, KC_BTN3

// Symbols.
#define LAYOUT_LAYER_SYM_OLD                                                                  \
    KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, ________________HOME_ROW_NA________________, \
    KC_COLN,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, ______________HOME_ROW_GASC_R______________, \
    KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_MINS, ______________HOME_ROW_ALGR_R______________, \
                               KC_RPRN, KC_LPRN,    U_NA,    U_NA

// Numerals.
#define LAYOUT_LAYER_NUM_OLD                                                                  \
    KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC, ________________HOME_ROW_NA________________, \
    KC_SCLN,    KC_4,    KC_5,    KC_6,  KC_EQL, ______________HOME_ROW_GASC_R______________, \
     KC_GRV,    KC_1,    KC_2,    KC_3, KC_UNDS, ______________HOME_ROW_ALGR_R______________, \
                                  KC_0, KC_MINS,    U_NA,    U_NA

// Function keys.
#define LAYOUT_LAYER_FUN                                                                      \
     KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR, ________________HOME_ROW_NA________________, \
     KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL, ______________HOME_ROW_GASC_R______________, \
     KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS, ______________HOME_ROW_ALGR_R______________,\
                                KC_APP,  KC_TAB,    U_NA,    U_NA

/**
 * Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GASC (Gui, Alt, Ctrl, Shift)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with `LAYOUT_LAYER_BASE` defined above, eg.:
 *
 *     HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE)
 */
#define _HOME_ROW_MOD_GACS(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      RGUI_T(L10), RCTL_T(L11), RALT_T(L12), RSFT_T(L13),        L14,  \
             R15,  RSFT_T(R16), RALT_T(R17), RCTL_T(R18), RGUI_T(R19), \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

/**
 * Add mouse layer keys to a layout.
 *
 * Expects a 10-key per row layout.  The layout passed in parameter must contain
 * at least 30 keycodes.
 *
 * This is meant to be used with `LAYOUT_LAYER_BASE` defined above, eg.:
 *
 *     MOUSE_MOD(LAYOUT_LAYER_BASE)
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
            L20, MOUSE(L21),        L22,        L23,        L24,  \
            R25,        R26,        R27, MOUSE(R28),        R29, \
      __VA_ARGS__
#define MOUSE_MOD(...) _MOUSE_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT_split_3x5_2(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(
    MOUSE_MOD(HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE))
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

#if defined(POINTING_DEVICE_ENABLE) && defined(DILEMMA_AUTO_SNIPING_ON_LAYER)
layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    dilemma_set_pointer_sniping_enabled(layer_state_cmp(state, DILEMMA_AUTO_SNIPING_ON_LAYER));
    return state;
}
#endif // POINTING_DEVICE_ENABLE && DILEMMA_AUTO_SNIPING_ON_LAYER

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

void shutdown_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_setrgb(RGB_RED);
#endif // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all(RGB_RED);
    rgb_matrix_update_pwm_buffers();
#endif // RGB_MATRIX_ENABLE
}
