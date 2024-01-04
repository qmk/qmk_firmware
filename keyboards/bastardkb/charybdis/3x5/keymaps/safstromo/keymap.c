#include QMK_KEYBOARD_H

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_FUNCTION,
    LAYER_NAVIGATION,
    LAYER_POINTER,
    LAYER_ADJUST,
    LAYER_SYMBOLS,
};
enum custom_keycodes {
    ARROW = SAFE_RANGE,
    ARROW_EQL,
};

#define COLEMAK DF(LAYER_BASE)
#define SYM MO(LAYER_SYMBOLS)
#define NAV MO(LAYER_NAVIGATION)
#define FKEYS MO(LAYER_FUNCTION)
#define ADJUST MO(LAYER_ADJUST)
#define COPY LCTL(KC_C)
#define PASTE LCTL(KC_V)
#define UNDO LCTL(KC_Z)
#define CUT LCTL(KC_X)
#define SFT_QT LSFT(RALT(KC_DQT))
#define ALT_SQT RALT(KC_QUOT)
#define ALT_SPC LALT_T(KC_SPC)

// Automatically enable sniping-mode on the pointer layer.
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define SPC_NAV LT(LAYER_NAVIGATION, KC_SPC)
#define TAB_SYM LT(LAYER_SYMBOLS, KC_TAB)
#define ENT_NAV LT(LAYER_NAVIGATION, KC_ENT)
#define BSP_NAV LT(LAYER_NAVIGATION, KC_BSPC)
#define _L_PTR(KC) LT(LAYER_POINTER, KC)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
/*
* Base Layer: Colemak DH
*
* ,----------------------------------.                              ,----------------------------------.
* |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |
* |------+------+------+------+------|                              |------+------+------+------+------|
* |GUI(A)|alt(R)|sft(S)|ctl(T)|   G  |                              |   M  |ctl(N)|sft(E)|alt(I)|GUI(O)|
* |------+------+------+------+------|                              |------+------+------+------+------|
* |   Z  |   X  |   C  |   D  |  V   |                              |   K  |   H  | ,  < | . >  | /  ? |
* `--------------------+------+------|                              |------+------+------+------+------'
*               |      |  Sym |Space |                              | Enter|  Nav |
*               `------`-------------'                              `-------------'
*/

#define LAYOUT_LAYER_BASE                                                                     \
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, \
       LGUI_T(KC_A),    LALT_T(KC_R),    LSFT_T(KC_S),    LCTL_T(KC_T),    KC_G,    KC_M,    RCTL_T(KC_N),    RSFT_T(KC_E),    LALT_T(KC_I), LGUI_T(KC_O), \
       KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, \
                      _______, TAB_SYM, SPC_NAV, ENT_NAV, BSP_NAV

/** Convenience row shorthands. */
#define _______________DEAD_HALF_ROW_______________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ______________HOME_ROW_GACS_L______________ KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX
#define ______________HOME_ROW_GACS_R______________ XXXXXXX, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI
/*
     * Function/media Layer: Function/media keys
     *
     * ,----------------------------------.                              ,-----------------------------------.
     * |  F1  |  F2  |  F3  |  F4  |  F5  |                              |   F6  |  F7  |  F8  |  F9  | F10  |
     * |------+------+------+------+------|                              |-------+------+------+------+------|
     * |  GUI | Alt  |Shift | Ctrl |      |                              |       | Ctrl |Shift |  Alt | F11  |
     * |------+------+------+------+------|                              |-------+------+------+------+------|
     * |Prtscr|      |      |      |Adjust|                              |Colemak|Vol Up|Vol DN| Mute | F12  |
     * `--------------------+------+------|                              |------+------+------+------+-------'
     *                |     |      |      |                              |      |      |
     *                `-------------------'                              `-------------'
     */

#define LAYOUT_LAYER_FUNCTION                                                                 \
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, \
    KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, _______, _______, KC_LCTL, KC_LSFT, KC_LALT, KC_F11, \
    KC_PSCR, _______, _______, _______, ADJUST, COLEMAK, KC_VOLU, KC_VOLD, KC_MUTE, KC_F12, \
                      XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX


/** \brief Mouse emulation and pointer functions. */
#define LAYOUT_LAYER_POINTER                                                                  \
    XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD, S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, \
    ______________HOME_ROW_GACS_L______________, ______________HOME_ROW_GACS_R______________, \
    _______, DRGSCRL, SNIPING, _______, _______, _______,  _______,  SNIPING, DRGSCRL, _______, \
                      KC_BTN2, KC_BTN1, KC_BTN3, KC_BTN3, KC_BTN1

/*
     * Nav/Num Layer: Numbers, navigation
     *
     * ,----------------------------------.                              ,----------------------------------.
     * |   1  |   2  |  3   |  4   |  5   |                              |   6  |   7  |   8  |   9  |  0   |
     * |------+------+------+------+------|                              |------+------+------+------+------|
     * | PSCR |      |      |      | Home |                              |  End |  ←   |   ↓  |  ↑   |  →   |
     * |------+------+------+------+------|                              |------+------+------+------+------|
     * | PSCR | CUT  | COPY | UNDO | PASTE|                              |      | Home | PgDn | PgUp |      |
     * `--------------------+------+------|                              |------+------+------+------+------'
     *               | BSPC |Space |Fkeys |                              | Enter|      |
     *               `------`-------------'                              `-------------'
     */

#define LAYOUT_LAYER_NAVIGATION                                                               \
       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, \
    KC_PSCR, _______, _______, _______, KC_HOME, KC_END, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, \
    KC_PSCR,     CUT,    COPY,    UNDO,   PASTE, KC_PGDN, KC_HOME,  KC_PGDN,  KC_PGUP, _______, \
                      KC_TRNS, FKEYS, KC_TRNS, KC_TRNS ,KC_TRNS

/*
    * Adjust Layer:
    *
    * ,----------------------------------.                              ,----------------------------------.
    * |      |      |      |      |      |                              |      |      |      |      |      |
    * |------+------+------+------+------|                              |------+------+------+------+------|
    * |      |      |      |      |      |                              |      |      |      |      |      |
    * |------+------+------+------+------|                              |------+------+------+------+------|
    * |      |      |      |      |      |                              |      |      |      |      |      |
    * `--------------------+------+------|                              |------+------+------+------+------'
    *                |     |      |      |                              |      |      |
    *                `-------------------'                              `-------------'
    */
#define LAYOUT_LAYER_ADJUST                                                                  \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
                       _______, _______, _______, _______, _______

/*
     * Sym Layer: Symbols
     *
     * ,----------------------------------.                                ,-----------------------------------.
     * |        |      |   "  |   \  |      |                              |      |      |  '   |      |       |
     * |--------+------+------+------+------|                              |------+------+------+------+-------|
     * |   !    |   @  |   #  |   $  |   %  |                              |   ^  |   [  |   ]  |   &  |   *   |
     * |--------+------+------+------+------|                              |------+------+------+------+-------|
     * |   ESC  |   ~  |   `  |   |  |   \  |                              |   -  |   -  |   =  |   +  |       |
     * `----------------------+------+------|                              |------+------+------+------+-------'
     *                  |     |      |      |                              | Enter| Fkeys|
     *                  `-------------------'                              `-------------'
     */

#define LAYOUT_LAYER_SYMBOLS                                                                  \
    _______, _______, SFT_QT, KC_BSLS, _______, _______, _______, ALT_SQT, _______, _______, \
     KC_EXLM,   KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_AMPR, KC_ASTR, \
    _______, KC_TILD, KC_GRV, KC_PIPE, _______, KC_MINS, KC_MINS, KC_EQL, KC_PPLS, _______, \
                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, FKEYS

/**
 * \brief Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GACS (Gui, Alt, Ctl, Shift)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     HOME_ROW_MOD_GACS(LAYER_ALPHAS_QWERTY)
 */
/*
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
*/
/**
 * \brief Add pointer layer keys to a layout.
 *
 * Expects a 10-key per row layout.  The layout passed in parameter must contain
 * at least 30 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     POINTER_MOD(LAYER_ALPHAS_QWERTY)
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

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(POINTER_MOD(LAYOUT_LAYER_BASE)),
  [LAYER_FUNCTION] = LAYOUT_wrapper(LAYOUT_LAYER_FUNCTION),
  [LAYER_NAVIGATION] = LAYOUT_wrapper(LAYOUT_LAYER_NAVIGATION),
  [LAYER_ADJUST] = LAYOUT_wrapper(LAYOUT_LAYER_ADJUST),
  [LAYER_POINTER] = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
  [LAYER_SYMBOLS] = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
};

// clang-format on

// combos
const uint16_t PROGMEM backspace_combo[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM esc_combo[]       = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM tab_combo[]       = {LALT_T(KC_R), LSFT_T(KC_S), COMBO_END};
const uint16_t PROGMEM del_combo[]       = {KC_Y, KC_SCLN, COMBO_END};
const uint16_t PROGMEM a_combo[]         = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM ae_combo[]        = {RSFT_T(KC_E), LALT_T(KC_I), COMBO_END};
const uint16_t PROGMEM oe_combo[]        = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM lprn_combo[]      = {KC_F, LSFT_T(KC_S), COMBO_END};
const uint16_t PROGMEM lcbr_combo[]      = {KC_P, LCTL_T(KC_T), COMBO_END};
const uint16_t PROGMEM lbrc_combo[]      = {KC_W, LALT_T(KC_R), COMBO_END};
const uint16_t PROGMEM rbrc_combo[]      = {KC_Y, LALT_T(KC_I), COMBO_END};
const uint16_t PROGMEM rprn_combo[]      = {KC_U, RSFT_T(KC_E), COMBO_END};
const uint16_t PROGMEM rcbr_combo[]      = {KC_L, RCTL_T(KC_N), COMBO_END};
const uint16_t PROGMEM under_combo[]     = {KC_M, KC_K, COMBO_END};
const uint16_t PROGMEM arrow_combo[]     = {LCTL_T(KC_T), KC_G, COMBO_END};
const uint16_t PROGMEM arroweql_combo[]  = {KC_P, KC_B, COMBO_END};
const uint16_t PROGMEM back_to_colemak[] = {KC_ENT, KC_SPC, COMBO_END};
const uint16_t PROGMEM eql_combo[]       = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM minus_combo[]     = {RCTL_T(KC_N), KC_H, COMBO_END};
const uint16_t PROGMEM plus_combo[]      = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM delword_combo[]   = {KC_H, KC_DOT, COMBO_END};
combo_t                key_combos[]      = {
    COMBO(backspace_combo, KC_BSPC), COMBO(esc_combo, KC_ESC), COMBO(tab_combo, KC_TAB), COMBO(del_combo, KC_DEL), COMBO(ae_combo, RALT(KC_Q)), COMBO(oe_combo, RALT(KC_P)), COMBO(a_combo, RALT(KC_W)), COMBO(lbrc_combo, KC_LBRC), COMBO(rbrc_combo, KC_RBRC), COMBO(lprn_combo, KC_LPRN), COMBO(lcbr_combo, KC_LCBR), COMBO(rprn_combo, KC_RPRN), COMBO(rcbr_combo, KC_RCBR), COMBO(under_combo, KC_UNDS), COMBO(arrow_combo, ARROW), COMBO(arroweql_combo, ARROW_EQL), COMBO(back_to_colemak, COLEMAK), COMBO(eql_combo, KC_EQL), COMBO(minus_combo, KC_MINS), COMBO(plus_combo, KC_PPLS), COMBO(delword_combo, LCTL(KC_BSPC)),
};

// Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ARROW:
            if (record->event.pressed) {
                SEND_STRING("->");
            }
            break;

        case ARROW_EQL:
            if (record->event.pressed) {
                SEND_STRING("=>");
            }
            break;
    }
    return true;
};
// Tapping speed
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_O):
            return TAPPING_TERM + 250;
        case LGUI_T(KC_A):
            return TAPPING_TERM + 250;
        default:
            return TAPPING_TERM;
    }
}

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE
