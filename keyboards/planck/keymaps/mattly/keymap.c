#include QMK_KEYBOARD_H
#include "mattly.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_QWERTY] = LAYOUT_planck_grid(
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_SCLN,
    KC_CAPS, A_CTRL,  S_ALT,   D_GUI,   F_SHFT,  KC_G,    KC_H,    J_SHFT,  K_GUI,   L_ALT,   MINSCTL, KC_QUOT,
    XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    XXXXXXX, NAVLOCK, XXXXXXX, ESC_HYP, BSP_NUM, ENT_SFT, SPC_SFT, TAB_SYM, DEL_WRP, XXXXXXX, SYMLOCK, XXXXXXX
 ),

 [_SYMBOL] = LAYOUT_planck_grid(
     _______, KC_AMPR, KC_GRV,  KC_TILD, KC_LBRC, KC_RBRC, KC_LABK, KC_RABK, KC_PLUS, KC_ASTR, XXXXXXX, _______,
     _______, KC_DLR,  KC_PERC, KC_EQL,  KC_LPRN, KC_RPRN, KC_SCLN, KC_COLN, KC_EXLM, KC_AT,   KC_UNDS, _______,
     _______, XXXXXXX, KC_CIRC, KC_HASH, KC_LCBR, KC_RCBR, KC_QUOT, KC_DQUO, KC_PIPE, KC_BSLS, KC_QUES, _______,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
 ),

[_NAVNUM] = LAYOUT_planck_grid(
    _______, XXXXXXX, BWORD,   KC_UP,   FWORD,   KC_PGUP, KC_DOT,  KC_7,    KC_8,    KC_9,    KC_PLUS, KC_ASTR,
    _______, KC_ENT,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_0,    KC_4,    KC_5,    KC_6,    KC_MINS, KC_SLSH,
    _______, KC_BSPC, KC_HOME, KC_TAB,  KC_END,  KC_DEL,  KC_COMM, KC_1,    KC_2,    KC_3,    KC_EQL,  KC_PERC,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_COLN, KC_DLR,  _______
),

[_FUNCT] = LAYOUT_planck_grid(
    QK_BOOT, XALLWIN, XPRVSPC, NWIN,    XNXTSPC, XDESKTP, XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F13,
    DB_TOGG, XNOTIFY, PTAB,    PWIN,    NTAB,    NAVBACK, NAVFWD,  KC_F4,   KC_F5,   KC_F6,   KC_F11,  KC_F14,
    KC_MUTE, KC_VOLD, KC_VOLU, KC_MRWD, KC_MFFD, KC_MPLY, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F12,  KC_F15,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};


