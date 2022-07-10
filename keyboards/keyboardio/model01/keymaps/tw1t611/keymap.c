#include QMK_KEYBOARD_H
#include "keymap_german.h"

/* layer constants */
enum {
  DEF = 0,
  MOD,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[DEF] = LAYOUT(
  _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                      KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , DE_SS  ,
  KC_ESC , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , RGB_MOD,    KC_MUTE, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , DE_ADIA,
  KC_TAB , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , DE_SECT,    _______, KC_H   , KC_J   , KC_K   , KC_L   , DE_SLSH, DE_ODIA,
  DE_PIPE, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , _______,    _______, KC_N   , KC_M   , DE_COMM, DE_DOT , DE_MINS, DE_UDIA,
                                         KC_LALT,                                 KC_LGUI,
                                            KC_SPC ,                           KC_ENT ,
                                               KC_LSFT,                     MO(MOD),
                                                  KC_BSPC,               KC_DEL ,
                                      KC_LCTL,                                        KC_RCTL
  ),
[MOD] = LAYOUT(
  KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                      KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
  DE_CIRC, DE_QUOT, DE_DQUO, DE_LCBR, DE_RCBR, DE_GRV , RGB_TOG,    _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END , DE_EQL , DE_PERC,
  DE_TILD, DE_EXLM, DE_DLR , DE_LPRN, DE_RPRN, DE_AMPR, _______,    _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, DE_QUES, DE_ASTR,
  DE_BSLS, DE_HASH, DE_LABK, DE_LBRC, DE_RBRC, DE_RABK, _______,    RESET  , DE_AT  , DE_EURO, DE_SCLN, DE_COLN, DE_UNDS, DE_PLUS,
                                         _______,                                 _______,
                                            _______,                           _______,
                                               _______,                     _______,
                                                  _______,               _______,
                                      _______,                                        _______
  )
};

/* template for new layouts:
LAYOUT(
  _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
                                         _______,                                 _______,
                                            _______,                           _______,
                                               _______,                     _______,
                                                  _______,               _______,
                                      _______,                                        _______
  )
*/

/* vim: set ts=2 sw=2 et: */
