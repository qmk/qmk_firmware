#include QMK_KEYBOARD_H
#include "keymap_swedish.h"

//Heavily modified keymap. Some features:
//Multiple layouts, I use dvorak as main.
//Nordic(swedish) signs
//Symbols, numpad, arrows/navigation reachable under the alpas via the layers
//Mirrored ctl, alt and shift to be able to use both hands when doing commands
//Gaming layer, qwerty with space on left half.

enum layer_names {
    _DVORAK,
    _COLEMAK,
    _QWERTY,
    _WORKMAN,
    _GAMING,
    _NUMPAD,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  DVORAK,
  COLEMAK,
  WORKMAN,
  GAMING,
  NUMPAD,
};

#define KC_ KC_TRNS

#define SE_YEN ALGR(SE_6) //isn't in the swedish_keymap.h
#define KC_CATDEL LCTL(LALT(KC_DEL)) // Ctrl alt del
#define KC_TSKMGR LCTL(S(KC_ESC)) // Ctrl shift esc
#define KC_NUMP TG(_NUMPAD)  // Toggle layer NUMPAD for use in LAYOUT_kc
#define KC_Close RALT(KC_F4) // Alt F4
#define KC_MEH1 MEH(KC_1)
#define KC_MEH2 MEH(KC_2)
#define KC_MEH3 MEH(KC_3)
#define KC_MEH4 MEH(KC_4)
#define KC_MEH5 MEH(KC_5)

#define KC_LOWR MO(_LOWER)
#define KC_RASE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                          ,--------+--------+--------+--------+--------+--------.
      KC_DEL , KC_APP , KC_VOLD, KC_MUTE, KC_VOLU, KC_LGUI,                            KC_GRV , KC_MPRV, KC_MPLY, KC_MNXT, KC_DOWN, KC_ESC ,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_TAB , KC_Q   , KC_W   , KC_E   , KC_ R  , KC_T   ,                            KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , SE_ARNG,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                            KC_H   , KC_J   , KC_K   , KC_L   , SE_ODIA, SE_ADIA,
  //|--------+--------+--------+--------+--------+--------+--------.        ,--------|--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_NUMP,          KC_ENT , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
  //`--------+--------+--------+----+---+--------+--------+--------/        \--------+--------+--------+---+----+--------+--------+--------'
                                     KC_LALT, KC_LOWR, KC_BSPC,                   KC_SPC , KC_RASE, KC_LALT
  //                                `--------+--------+--------'                `--------+--------+--------'
  ),

  [_GAMING] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                          ,--------+--------+--------+--------+--------+--------.
      KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                            KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_ESC ,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_TAB , KC_Q   , KC_W   , KC_E   , KC_ R  , KC_T   ,                            KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_DEL ,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                            KC_H   , KC_J   , KC_K   , KC_L   , SE_ODIA, KC_RCTL,
  //|--------+--------+--------+--------+--------+--------+--------.        ,--------|--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_NUMP,          KC_ENT , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
  //`--------+--------+--------+----+---+--------+--------+--------/        \--------+--------+--------+---+----+--------+--------+--------'
                                     KC_LALT, KC_LOWR, KC_BSPC,                   KC_SPC , KC_RASE, KC_LALT
  //                                `--------+--------+--------'                `--------+--------+--------'
  ),

 [_DVORAK] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                          ,--------+--------+--------+--------+--------+--------.
      KC_DEL , KC_APP , KC_VOLD, KC_MUTE, KC_VOLU, KC_LGUI,                            KC_GRV , KC_MPRV, KC_MPLY, KC_MNXT, KC_DOWN, KC_ESC ,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_TAB , SE_ARNG, SE_ADIA, SE_ODIA, KC_P   , KC_Y   ,                            KC_F   , KC_G   , KC_C   , KC_R   , KC_L   ,KC_DEL  ,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_A   , KC_O   , KC_E   , KC_U   , KC_I   ,                            KC_D   , KC_H   , KC_T   , KC_N   , KC_S   ,KC_RCTL ,
  //|--------+--------+--------+--------+--------+--------+--------.        ,--------|--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_DOT , KC_Q   , KC_J   , KC_K   , KC_X   , KC_NUMP,          KC_ENT , KC_B   , KC_M   , KC_W   , KC_V   , KC_Z   ,KC_RSFT ,
  //`--------+--------+--------+----+---+--------+--------+--------/        \--------+--------+--------+---+----+--------+--------+--------'
                                     KC_LALT, KC_LOWR, KC_BSPC,                   KC_SPC , KC_RASE, KC_LALT
  //                                `--------+--------+--------'                `--------+--------+--------'
  ),

 [_COLEMAK] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                          ,--------+--------+--------+--------+--------+--------.
      KC_DEL , KC_APP , KC_VOLD, KC_MUTE, KC_VOLU, KC_LGUI,                            KC_GRV , KC_MPRV, KC_MPLY, KC_MNXT, KC_DOWN, KC_ESC ,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   ,                            KC_J   , KC_L   , KC_U   , KC_Y   , SE_ARNG, SE_ADIA,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_A   , KC_R   , KC_S   , KC_T   , KC_D   ,                            KC_H   , KC_N   , KC_E   , KC_I   , KC_O   , SE_ODIA,
  //|--------+--------+--------+--------+--------+--------+--------.        ,--------|--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_NUMP,          KC_ENT , KC_K   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
  //`--------+--------+--------+----+---+--------+--------+--------/        \--------+--------+--------+---+----+--------+--------+--------'
                                     KC_LALT, KC_LOWR, KC_BSPC,                   KC_SPC , KC_RASE, KC_LALT
  //                                `--------+--------+--------'                `--------+--------+--------'
  ),

[_WORKMAN] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                          ,--------+--------+--------+--------+--------+--------.
      KC_DEL , KC_APP , KC_VOLD, KC_MUTE, KC_VOLU, KC_LGUI,                            KC_GRV , KC_MPRV, KC_MPLY, KC_MNXT, KC_DOWN, KC_ESC ,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_TAB , KC_Q   , KC_W   , KC_R   , KC_W     KC_B   ,                            KC_J   , KC_F   , KC_U   , KC_P   , SE_ARNG, SE_ODIA,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_A   , KC_S   , KC_H   , KC_T   , KC_G   ,                            KC_Y   , KC_N   , KC_E   , KC_O   , KC_I   , KC_RCTL,
  //|--------+--------+--------+--------+--------+--------+--------.        ,--------|--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_Z   , KC_X   , KC_M   , KC_C   , KC_V   , KC_NUMP,          KC_ENT , KC_K   , KC_L   , SE_ADIA, KC_DOT , KC_SLSH, KC_RSFT,
  //`--------+--------+--------+----+---+--------+--------+--------/        \--------+--------+--------+---+----+--------+--------+--------'
                                      KC_LALT, KC_LOWR, KC_BSPC,                 KC_SPC  , KC_RASE, KC_LALT
  //                                `--------+--------+--------'                `--------+--------+--------'
  ),

  [_NUMPAD] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                          ,--------+--------+--------+--------+--------+--------.
      KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,                            KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
             , KC_MEH1, KC_BTN2, KC_MS_U, KC_BTN1, KC_CATDEL,                          KC_PIPE, KC_P7  , KC_P8  , KC_P9  , KC_SLSH,        ,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
             , KC_MEH4, KC_MS_L, KC_MS_D, KC_MS_R, KC_TSKMGR,                          KC_COMM, KC_P4  , KC_P5  , KC_P6  , KC_MINS,        ,
  //|--------+--------+--------+--------+--------+--------+--------.        ,--------|--------+--------+--------+--------+--------+--------|
             , KC_MEH5, KC_ACL0, KC_ACL1, KC_ACL2, KC_MEH3,         ,        KC_PENT , KC_DOT , KC_P1  , KC_P2  , KC_P3  , KC_P0  ,        ,
  //`--------+--------+--------+----+---+--------+--------+--------/        \--------+--------+--------+---+----+--------+--------+--------'
                                     KC_LALT , KC_LOWR, KC_BSPC,                         , KC_P0  , KC_NLCK
  //                                `--------+--------+--------'                `--------+--------+--------'
  ),


  [_LOWER] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                          ,--------+--------+--------+--------+--------+--------.
      KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,                            KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
             , KC_CAPS, KC_PGUP, KC_UP  , KC_PGDN, KC_ESC,                             KC_RCBR, KC_EXLM, KC_ASTR, KC_LPRN, KC_UNDS,        ,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
             , KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,                             KC_RPRN, KC_QUES, SE_LBRC, SE_RBRC, KC_LABK,        ,
  //|--------+--------+--------+--------+--------+--------+--------.        ,--------|--------+--------+--------+--------+--------+--------|
             , KC_ENT ,        ,        ,        , KC_DEL ,                ,         , KC_RABK, SE_LABK, SE_LCBR, SE_RCBR, SE_RABK,       ,
  //`--------+--------+--------+----+---+--------+--------+--------/        \--------+--------+--------+---+----+--------+--------+--------'
                                             ,        ,        ,                         ,        ,
  //                                `--------+--------+--------'                `--------+--------+--------'
  ),

  [_RAISE] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                          ,--------+--------+--------+--------+--------+--------.
      SE_TILD, KC_EXLM, KC_GRV , KC_EQL , KC_DLR , KC_PERC,                            SE_PND , SE_EURO , SE_YEN, SE_RCBR, KC_RPRN,        ,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
             , SE_PIPE , SE_AT , KC_HASH, KC_DQT , KC_PERC,                            KC_PIPE, KC_7   , KC_8   , KC_9   , KC_PMNS, KC_PSLS,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
             , SE_BSLS, SE_TILD, SE_SLSH, KC_AMPR, KC_BSLS,                            KC_COMM, KC_4   ,  KC_5  ,  KC_6  , KC_PPLS, KC_PAST,
  //|--------+--------+--------+--------+--------+--------+--------.        ,--------|--------+--------+--------+--------+--------+--------|
             , KC_PIPE, SE_CURR, KC_PLUS, KC_CIRC, KC_TILD,         ,        KC_PENT , KC_DOT , KC_1   , KC_2   , KC_3   , KC_0   , KC_PEQL,
  //`--------+--------+--------+----+---+--------+--------+--------/        \--------+--------+--------+---+----+--------+--------+--------'
                                             ,        , KC_DEL  ,                        ,        ,
  //                                `--------+--------+--------'                `--------+--------+--------'
  ),

  [_ADJUST] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                          ,--------+--------+--------+--------+--------+--------.
      GAMING , DVORAK,  WORKMAN, COLEMAK, QWERTY ,   RESET,                           _______, _______, _______, _______, KC_PWR,    RESET,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      _______, _______, _______,LGUI(KC_UP),_______,LALT(KC_F4),                       _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      _______, _______,LGUI(KC_LEFT),LGUI(KC_DOWN),LGUI(KC_RGHT),_______,             _______,  DEBUG  , RGB_HUD, RGB_SAD, RGB_VAD, BL_STEP,
  //|--------+--------+--------+--------+--------+--------+--------.        ,--------|--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //`--------+--------+--------+----+---+--------+--------+--------/        \--------+--------+--------+---+----+--------+--------+--------'
                                      _______, _______, _______,                  _______, _______, _______
  //                                `--------+--------+--------'                `--------+--------+--------'
  )

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
    case NUMPAD:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_NUMPAD);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
    case WORKMAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WORKMAN);
      }
      return false;
    case GAMING:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_GAMING);
      }
      return false;
  }
  return true;
}
