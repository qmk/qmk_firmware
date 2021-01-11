#include QMK_KEYBOARD_H
#include "mattly.h"

// extern keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_SCLN,
    KC_CAPS, A_CTRL,  S_ALT,   D_GUI,   F_SHFT,  KC_G,                               KC_H,    J_SHFT,  K_GUI,   L_ALT,   MINSCTL, KC_QUOT,
    XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    SPC_SFT,         BSP_NUM,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
                                   ESC_HYP, BSP_NUM, ENT_SFT,                   SPC_SFT, TAB_SYM, DEL_WRP
  ),

  [_SYMBOL] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
    _______, KC_AMPR, KC_GRV,  KC_TILD, KC_LBRC, KC_RBRC,                            KC_LABK, KC_RABK, KC_PLUS, KC_ASTR, XXXXXXX, _______,
    _______, KC_DLR,  KC_PERC, KC_EQL,  KC_LPRN, KC_RPRN,                            KC_SCLN, KC_COLN, KC_EXLM, KC_AT,   KC_UNDS, _______,
    RESET,   XXXXXXX, KC_CIRC, KC_HASH, KC_LCBR, KC_RCBR, _______,          _______, KC_QUOT, KC_DQUO, KC_PIPE, KC_BSLS, KC_QUES, _______,
                                  _______, _______, _______,                     _______, _______, _______
  ),

  [_NAVNUM] = LAYOUT(
    XNOTIFY, XXXXXXX, XPRVSPC, NWIN,    XNXTSPC, XXXXXXX,                            XXXXXXX, KC_SLSH, KC_ASTR, KC_MINS, KC_PLUS, XXXXXXX,
    XALLWIN, NAVFWD,  BWORD,   KC_UP,   FWORD,   KC_PGUP,                            KC_DLR,  KC_P7,   KC_P8,   KC_P9,   KC_DOT,  XXXXXXX,
    XDESKTP, NAVBACK, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                            KC_PERC, KC_P4,   KC_P5,   KC_P6,   KC_EQL,  XXXXXXX,
    RESET,   PTAB,    KC_HOME, PWIN,    KC_END,  NTAB,    _______,          _______, XXXXXXX, KC_P1,   KC_P2,   KC_P3,   KC_ENT,  XXXXXXX,
                                   _______, _______, _______,                   _______, _______, KC_P0
  ),

  [_FUNCT] = LAYOUT(
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    RESET,   XALLWIN, XPRVSPC, NWIN,    XNXTSPC, XDESKTP,                            XXXXXXX, RGB_TOG, RGB_M_P, RGB_M_B, RGB_M_K, RESET,
    DEBUG,   XNOTIFY, PTAB,    PWIN,    NTAB,    XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_MUTE, KC_VOLD, KC_VOLU, KC_MRWD, KC_MFFD, KC_MPLY, _______,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, _______, _______,                   _______, _______, _______
  )
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_MS_WH_UP);
        } else {
            tap_code(KC_MS_WH_DOWN);
        }
    }
}

