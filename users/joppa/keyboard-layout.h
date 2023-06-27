#pragma once
//#include QMK_KEYBOARD_H // Does not need this, its included before this file in joppa.c
// Macro stuff
enum custom_keycodes {
	PAREN = SAFE_RANGE,
    BRACKET,
    CURLEY,
	QUOT,
	DQUOT,
	MY_END,
	MY_HOME,
	MY_PASTE,
	MY_COPY,
 	MY_PGUP,
	MY_PGDN,
	MY_GUI_NUM,
	MY_UNDRDO,
	_AA, // Åå
	_AE, // æÆ
	_OE, // øØ
};

enum layers { BASE, MBO, MEDIA, NAV, MOUSE, SYM, NUM, FUN };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_miryoku(
    KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,               KC_I,              KC_O,             KC_P,
    LGUI_T(KC_A),      LALT_T(KC_S),      LCTL_T(KC_D),      LSFT_T(KC_F),      KC_G,              KC_H,              LSFT_T(KC_J),      LCTL_T(KC_K),      LALT_T(KC_L),      RGUI_T(_OE),
    KC_Z,              ALGR_T(KC_X),      KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              QK_LEAD,           _AA,               _AE,
    U_NP,              U_NP,              LT(MEDIA, KC_COMM),LT(NAV, KC_SPC),   LT(MOUSE, KC_DOT), LT(FUN, KC_ENT),   LT(NUM, KC_BSPC),  OSL(SYM),          U_NP,              U_NP
  ),
  [NAV] = LAYOUT_miryoku(
    QK_RBT,   U_NA,    U_NA,    U_NA,    U_NA,    MY_UNDRDO,MY_PASTE,MY_COPY, U_CUT,   KC_APP,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,    KC_LEFT,  KC_DOWN,	KC_UP,   KC_RGHT, KC_CAPS,
    U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    MY_HOME,  MY_PGDN,	MY_PGUP, MY_END,  KC_INS,
    U_NP,    U_NP,    U_NA,    TG(NAV), U_NA,    KC_ENT,   KC_BSPC,	KC_DEL,  U_NP,    U_NP
  ),
  [MOUSE] = LAYOUT_miryoku(
    QK_RBT,   U_NA,    U_NA,    U_NA,    U_NA,    U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,    KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, U_NU,
    U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, U_NU,
    U_NP,    U_NP,    U_NA,    U_NA,    TG(MOUSE),KC_BTN1,KC_BTN3, KC_BTN2, U_NP,    U_NP
  ),
  [MEDIA] = LAYOUT_miryoku(
    QK_RBT,   U_NA,    U_NA,    U_NA,    U_NA,    RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,    KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, U_NU,
    U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU,
    U_NP,    U_NP,    U_NA,    U_NA,    U_NA,    KC_MSTP, KC_MPLY, KC_MUTE, U_NP,    U_NP
  ),
  [MBO] = LAYOUT_miryoku(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_TRNS, KC_TRNS, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,   U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
    U_NP,    U_NP,    KC_BTN2, KC_BTN3, KC_BTN1, KC_BTN1, KC_BTN3, KC_BTN2, U_NP,    U_NP
  ),
  [NUM] = LAYOUT_miryoku(
    KC_PLUS, KC_7,    KC_8,    KC_9,    KC_ASTR, U_NA,    U_NA,    U_NA,    U_NA,    QK_RBT,
    KC_MINS, KC_4,    KC_5,    KC_6,    KC_SLSH, U_NA,    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    KC_PERC, KC_1,    KC_2,    KC_3,    KC_EQL , U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
    U_NP,    U_NP,    U_NA,    KC_0,    KC_DOT,  U_NA,    TG(NUM), U_NA,    U_NP,    U_NP
  ),
  [SYM] = LAYOUT_miryoku(
	KC_PLUS, KC_EXLM, KC_SCLN, QUOT,    KC_ASTR, KC_CIRC, KC_TILD, KC_HASH, KC_UNDS, KC_AMPR,
	KC_MINS, KC_QUES, KC_COLN, DQUOT,   KC_SLSH, CURLEY,  PAREN,   BRACKET, KC_DLR,  KC_DOT,
	KC_PERC, KC_TRNS, KC_TRNS, KC_GRV,  KC_EQL,  KC_RCBR, KC_RPRN, KC_RBRC, KC_TRNS, KC_TRNS,
	U_NP,    U_NP,    KC_PIPE, KC_BSLS, KC_LT,   KC_GT,   KC_AT,   TG(SYM), U_NP,    U_NP
  ),
  [FUN] = LAYOUT_miryoku(
    KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR, U_NA,    U_NA,    U_NA,    U_NA,    QK_RBT,
    KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SCRL, U_NA,    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
    U_NP,    U_NP,    KC_APP,  KC_SPC,  KC_TAB,  U_NA,    U_NA,    U_NA,    U_NP,    U_NP
  )
};
