/* Felix Keyboard Layout
 *
 */
#include QMK_KEYBOARD_H
#include <keymap_german.h>
#include <keymap_HomeRowMod.h>

enum layer_names {
    NEO_BASE,
    _FL_Arrow,
    _FL_Sym,
    _FL_Number
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [NEO_BASE] = LAYOUT_reviung41(
  //|--------|--------|--------|--------|--------|--------|                    |--------|--------|--------|--------|--------|--------|
    KC_ESC,  DE_X,    DE_V,    DE_L,    DE_C,    DE_W,                         DE_K,    DE_H,    DE_G,    DE_F,    DE_Q,    DE_SS,
    KC_TAB,  HRN_L1,  HRN_L2,  HRN_L3,  HRN_L4,  DE_O,                         DE_S,    HRN_R1,  HRN_R2,  HRN_R3,  HRN_R4,  DE_Y,
    KC_LGUI, DE_UDIA, DE_ODIA, DE_ADIA, DE_P,    DE_Z,                         DE_B,    DE_M,    DE_COMM, DE_DOT,  DE_J,    XXXXXXX,
  //Thumb cluster
    MO(_FL_Sym),
    LT(_FL_Number,KC_BSPC),
    KC_SPC,
    LT(_FL_Arrow,KC_ENT),
    LT(_FL_Arrow,KC_ENT)
  ),

  [_FL_Arrow] = LAYOUT_reviung41(
  //|--------|--------|--------|--------|--------|--------|                    |--------|--------|--------|--------|--------|--------|
    KC_ESC,  XXXXXXX, DE_7,    DE_8,    DE_9,    XXXXXXX,                      KC_PGUP, KC_HOME, KC_UP,   KC_END,  XXXXXXX, XXXXXXX,
    KC_TAB,  XXXXXXX, DE_4,    DE_5,    DE_6,    XXXXXXX,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT,XXXXXXX, XXXXXXX,
    KC_LGUI, DE_0,    DE_1,    DE_2,    DE_3,    XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //Thumb cluster
    _______,
    KC_DEL,
    _______,
    _______,
    _______
  ),


  [_FL_Sym] = LAYOUT_reviung41(
  //|--------|--------|--------|--------|--------|--------|                    |--------|--------|--------|--------|--------|--------|
    KC_ESC,  XXXXXXX, DE_UNDS, DE_LBRC, DE_RBRC, DE_CIRC,                      DE_EXLM, DE_LABK, DE_RABK, DE_EQL,  DE_AMPR, XXXXXXX,
    KC_TAB,  DE_BSLS, DE_SLSH, DE_LCBR, DE_RCBR, DE_ASTR,                      DE_QUES, DE_LPRN, DE_RPRN, DE_MINS, DE_COLN, DE_AT,
    KC_LGUI, DE_HASH, DE_DLR,  DE_PIPE, DE_TILD, DE_GRV,                       DE_PLUS, DE_PERC, DE_DQUO, DE_QUOT, XXXXXXX, XXXXXXX,
  //Thumb cluster
    _______,
    _______,
    _______,
    _______,
    _______
  ),


  [_FL_Number] = LAYOUT_reviung41(
  //|--------|--------|--------|--------|--------|--------|                    |--------|--------|--------|--------|--------|--------|
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F6,   KC_F6,   KC_F6,   KC_F10,  KC_F11,
    _______, DE_1,    DE_2,    DE_3,    DE_4,    DE_5,                         DE_6,    DE_7,    DE_8,    DE_9,    DE_0,    KC_F12,
    _______, XXXXXXX, XXXXXXX, DE_COMM, DE_DOT,  XXXXXXX,                      DE_EQL,  DE_PLUS, DE_MINS, DE_ASTR, DE_SLSH, XXXXXXX,
  //Thumb cluster
    _______,
    _______,
    _______
    ,
    _______,
    _______
  )
};