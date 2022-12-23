#include QMK_KEYBOARD_H
#include "mattly.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // I apparently soldered in my switches on the wrong sides of the boards, so this is mirrored

  [_BASE_MAC] = LAYOUT_split_3x6_3(
    KC_SCLN, KC_P,    O_CTL,   I_ALT,   U_GUI,   KC_Y,               KC_T,    R_GUI,   E_ALT,   W_CTL,   KC_Q,    KC_BSPC,
    KC_QUOT, MINSCTL, L_ALT,   K_GUI,   J_SFT,   KC_H,               KC_G,    F_SFT,   D_GUI,   S_ALT,   A_CTL,   KC_CAPS,
    KC_ENT,  KC_SLSH, KC_DOT,  KC_COMM, KC_M,    KC_N,               KC_B,    KC_V,    KC_C,    KC_X,    KC_Z,    NAVLOCK,
                                  DEL_WRP, BSP_SYM, SPC_SFT,  SPC_SFT, TAB_NUM, ESC_HYP
  ),

  [_OVER_WIN] = LAYOUT_split_3x6_3(
    _______, _______, O_GUI,   _______, U_CTL,   _______,            _______, R_CTL,   _______, W_GUI,   _______, _______,
    _______, MINSGUI, _______, K_CTL,   _______, _______,            _______, _______, D_CTL,   _______, A_GUI,   _______,
    _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
                                  _______, _______, _______,   _______, _______, _______
  ),


  [_SYMBOL] = LAYOUT_split_3x6_3(
    _______, XXXXXXX, KC_ASTR, KC_PLUS, KC_RABK, KC_LABK,            KC_RBRC, KC_LBRC, KC_TILD, KC_GRV,  KC_AMPR, _______,
    _______, KC_UNDS, KC_AT,   KC_EXLM, KC_COLN, KC_SCLN,            KC_RPRN, KC_LPRN, KC_EQL,  KC_PERC, KC_DLR,  _______,
    _______, KC_QUES, KC_BSLS, KC_PIPE, KC_DQUO, KC_QUOT,            KC_RCBR, KC_LCBR, KC_HASH, KC_CIRC, KC_HASH, XXXXXXX,
                                  _______, _______, _______,   _______, _______, _______
  ),

  [_NAVNUM] = LAYOUT_split_3x6_3(
    KC_PLUS, KC_DOT,  KC_P9,   KC_P8,   KC_P7,   KC_DLR,             KC_PGUP, M_FWORD, KC_UP,   M_BWORD, M_NAVFW, M_NXWIN,
    KC_MINS, KC_EQL,  KC_P6,   KC_P5,   KC_P4,   KC_PERC,            KC_PGDN, KC_RGHT, KC_DOWN, KC_LEFT, M_NAVBK, M_PVWIN,
    KC_ASTR, KC_COMM, KC_P3,   KC_P2,   KC_P1,   KC_P0,              M_NXTAB, KC_END,  XXXXXXX, KC_HOME, M_PVTAB, _______,
                                   KC_P0,  _______, _______,  _______, _______, _______
  ),
  [_NAVNUM_WIN] = LAYOUT_split_3x6_3(
    _______, _______, _______, _______, _______, _______,            _______, W_FWORD, _______, W_BWORD, W_NAVFW, W_NXWIN,
    _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, W_NAVBK, W_PVWIN,
    _______, _______, _______, _______, _______, _______,            W_NXTAB, _______, _______, _______, W_PVTAB, _______,
                                   _______, _______, _______,   _______, _______, _______
  ),

  [_FUNCT] = LAYOUT_split_3x6_3(
    KC_F15,  KC_F12,  KC_F9,   KC_F8,   KC_F7,   KC_VOLU,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
    KC_F14,  KC_F11,  KC_F6,   KC_F5,   KC_F4,   KC_MUTE,            XXXXXXX, TOG_WIN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_F13,  KC_F10,  KC_F3,   KC_F2,   KC_F1,   KC_VOLD,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, _______, _______,   _______, _______, _______
  ),
  [_FUNCT_WIN] = LAYOUT_split_3x6_3(
    _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______,   _______, _______, _______
  ),
};
