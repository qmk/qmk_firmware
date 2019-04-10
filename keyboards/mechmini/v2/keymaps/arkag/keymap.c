#include QMK_KEYBOARD_H
#include "arkag.h"

/*
 Userspace:
 https://github.com/arkag/qmk_firmware/blob/master/users/arkag/arkag.c
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_2u_space_ortho(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, QUOTE,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    M_PMOD,  LRALT,   M_SMOD,  LOWER,   RAISE,        KC_SPC,      MEDIA,   FUNCT,   XXXXXXX, GAME   , KC_LEAD),

  [_RAISE] = LAYOUT_2u_space_ortho(
    GRAVE,   _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    _______, _______,
    _______, OBRACK,  CBRACK,  KC_EQL,  HYPHEN,  _______, _______, KC_4,    KC_5,    KC_6,    _______, KC_NLCK,
    _______, _______, _______, CEDILLA, _______, KC_COMM, KC_PDOT, KC_1,    KC_2,    KC_3,    KC_BSLS, KC_PENT,
    _______, _______, _______, KEEB,    _______,      _______,     KC_0,    KC_PSLS, KC_PMNS, KC_PPLS, KC_PAST),

  [_LOWER] = LAYOUT_2u_space_ortho(
    _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, LRALT,   _______, _______, _______,      _______,     _______, _______, _______, _______, _______),

  [_MEDIA] = LAYOUT_2u_space_ortho(
    _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, _______, _______, KC_MUTE,
    _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,      KC_MPLY,     _______, _______, _______, _______, _______),

  [_FUNCT] = LAYOUT_2u_space_ortho(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,      _______,     _______, _______, M_SFT,   M_SPC,   M_OS   ),

  [_KEEB] = LAYOUT_2u_space_ortho(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, BL_TOGG, BL_STEP, BL_INC,  BL_DEC,  BL_BRTG, _______, _______, _______, _______, _______, _______,
    RGB_M_P, RGB_TOG, RGB_MOD, RGB_VAI, RGB_VAD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, _______, _______, _______,
    RESET,   _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______),

  [_GAMING] = LAYOUT_2u_space_ortho(
    KC_ESC,  KC_F13,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_TAB,  KC_F14,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_LSFT, KC_F15,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_LCTL, KC_F16,  KC_Z,    KC_X,    KC_C,         KC_SPC,      XXXXXXX, XXXXXXX, XXXXXXX, GAME,    XXXXXXX),

};
