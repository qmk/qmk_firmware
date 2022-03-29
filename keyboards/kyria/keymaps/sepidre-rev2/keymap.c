#include QMK_KEYBOARD_H
#include "enums.h"
#include "layer.h"
#include "oled.c"
#include "logics.c"
// [Keymaps] -----------------------------------------------------------------//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	  [_NEO] = LAYOUT(
      LT(_WEAPON, KC_ESC), DE_X,   DE_V,   DE_L,   DE_C,   DE_W,                   /*|*/                  DE_K, DE_H, DE_G,    DE_F,   DE_Q, DE_SS,
      LSFT_T(KC_TAB),      DE_U,   DE_I,   DE_A,   DE_E,   DE_O,                   /*|*/                  DE_S, DE_N, DE_R,    DE_T,   DE_D, DE_Y,
      KC_LCTRL,            DE_UE,  DE_OE,  DE_AE,  DE_P,   DE_Z, _______, _______, /*|*/ _______, _______,DE_B, DE_M, DE_COMM, DE_DOT, DE_J, DE_MINS,
                                       _______, _______,KC_LEAD, KC_SPC, MO(_NUM), /*|*/ MO(_SYM), LSFT_T(KC_ENT), LALT_T(KC_PGDN), _______, _______
    ),

      [_NUM] = LAYOUT(
      KC_ENT,     KC_HOME,  KC_BSPC,   KC_UP,    KC_DEL,   KC_END,                    /*|*/                  KC_PAST, KC_7, KC_8, KC_9, KC_PMNS, KC_PEQL,
      _______,    KC_UNDO,  KC_LEFT,   KC_DOWN,  KC_RIGHT, KC_PGDOWN,                 /*|*/                  KC_PSLS, KC_4, KC_5, KC_6, KC_PPLS, _______,
      LCTL(KC_S), KC_AGAIN, LCA(DE_R), S(KC_F5), KC_F12,   KC_PGUP, _______, _______, /*|*/ _______, _______,KC_0,    KC_1, KC_2, KC_3, KC_PDOT, KC_PCMM,
                                            _______, _______,KC_F2, KC_SPC, MO(_NUM), /*|*/ MO(_SYM), LSFT_T(KC_ENT), LALT_T(KC_PGDN), _______, _______
    ),

      [_SYM] = LAYOUT(
      KC_ESC,     DE_AT,   DE_UNDS, DE_LBRC, DE_RBRC, DE_CIRC,                  /*|*/                  DE_EXLM, DE_LABK, DE_RABK, DE_EQL,  DE_AMPR, DE_SECT,
      LCTL(KC_Z), DE_BSLS, DE_SLSH, DE_LCBR, DE_RCBR, DE_ASTR,                  /*|*/                  DE_QUES, DE_LPRN, DE_RPRN, DE_MINS, DE_COLN, DE_EURO,
      LCTL(KC_S), DE_HASH, DE_DLR,  DE_PIPE, DE_TILD, DE_GRV, _______, _______, /*|*/ _______, _______,DE_PLUS, DE_PERC, DE_DQUO, DE_QUOT, DE_SCLN, TG(_GAME),
                             _______, _______, LCA_T(KC_DEL), _______, _______, /*|*/ _______, LSFT_T(KC_ENT), LALT_T(KC_PGDN), _______, _______
    ),

	  [_GAME] = LAYOUT(
      KC_ESC,  DE_X,    DE_V,   DE_L,  DE_C,   DE_W,                   /*|*/                  DE_K, DE_H, DE_G,    DE_F,   DE_Q, DE_SS,
      KC_LSFT, DE_U,    DE_I,   DE_A,  DE_E,   DE_O,                   /*|*/                  DE_S, DE_N, DE_R,    DE_T,   DE_D, DE_Y,
      KC_LCTL, DE_COMM, DE_DOT, DE_D,  DE_P,   DE_Z, _______, _______, /*|*/ _______, _______,DE_B, DE_M, DE_COMM, DE_DOT, DE_J, DE_MINS,
                        _______, _______, KC_TAB, KC_SPC, MO(_WEAPON), /*|*/ MO(_SYM), KC_ENT, LALT_T(KC_PGDN), _______, _______
    ),

	  [_WEAPON] = LAYOUT(
      KC_ESC,  KC_1,  KC_2,      KC_3, KC_4, KC_5,                   /*|*/                   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
      KC_TAB,  KC_LSFT, DE_6,    KC_S, KC_7, KC_8,                   /*|*/                   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
      KC_MSEL, KC_LCTL, DE_MINS, KC_X, DE_9, DE_0, _______, _______, /*|*/ _______, _______, KC_PGUP, KC_PGDN, _______, _______, EEP_RST, TG(_GAME),
                        _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, /*|*/ KC_ENT, KC_SPC, LALT_T(KC_PGDN), _______, _______
    ),

      [_ADJ] = LAYOUT(
      KC_SYSTEM_WAKE, _______,  _______,  KC_SLCK, _______,   _______,                 /*|*/                   RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD,  HIBER,
      KC_F7,          KC_F8,    KC_F9,    KC_F10,  KC_F11,    KC_F12,                  /*|*/                   DE_S,    RGB_HUD, RGB_SAD, RGB_VAD, RGB_RMOD, _______,
      KC_F1,          KC_F2,    KC_F3,    KC_F4,   KC_F5,     KC_F6, _______, _______, /*|*/ _______, _______, _______, _______, _______, _______,  _______, _______,
                                  _______, _______, LGUI_T(KC_PGUP), KC_SPC, MO(_NUM), /*|*/ MO(_SYM), KC_ENT, LALT_T(KC_PGDN), _______, _______
    )
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};
