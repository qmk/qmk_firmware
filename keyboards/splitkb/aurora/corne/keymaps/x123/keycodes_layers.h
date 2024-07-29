#ifndef KEYCODES_LAYERS_H
#define KEYCODES_LAYERS_H

enum layer_names {
    _DEFAULT,
    _GAMER,
    _NO_HOMEROW,
    _NUMS,
    _GAMER_NUMS,
    _SYMS,
    _ONESHOT,
    _NAVI
};

enum custom_keycodes {
  SMTD_KEYCODES_BEGIN = SAFE_RANGE,
  CKC_A, // reads as C(ustom) + KC_A, but you may give any name here
  CKC_S,
  CKC_D,
  CKC_F,
  CKC_J, // reads as C(ustom) + KC_A, but you may give any name here
  CKC_K,
  CKC_L,
  CKC_SCLN,
  CKC_NUMS,
  CKC_SYMS,
  SMTD_KEYCODES_END,
  GAMER,
  COLEMAK,
  COLEMAK_NOHOMEROW,
  ADJUST,
  ONESHOT,
  DT_UP_50,
  DT_DOWN_50,
  DT_UP_X2,
  DT_DOWN_X2,
  DT_200,
  DT_MAX,
  ALT_TAB,
  ALT_F4,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  ENTER_CLOSE_TAB,
  TAB_CLOSE,
  TURBO_MODIFIER,
  TURBO_UP,
  TURBO_DOWN,
  TURBO_LEFT,
  TURBO_RIGHT,
  SNAP_TAP_A,
  SNAP_TAP_D,
  TAP_DOWN,
  TAP_UP,
  SEQ_DOWN,
  SEQ_UP,
  FOLLOW_DOWN,
  FOLLOW_UP,
  RELEASE_DOWN,
  RELEASE_UP,
  CLEAR_SNAPS,
  BUILD_SNAPS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DEFAULT] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                          ,-----------------------------------------------------.
       TAB_CLOSE,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_ESC, CKC_A, CKC_S, CKC_D, CKC_F,    KC_G,                               KC_H, CKC_J, CKC_K, CKC_L, CKC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_CAPS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                 KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, ENTER_CLOSE_TAB,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
                                          QK_LEAD, ALT_TAB, CKC_NUMS,        CKC_SYMS,   MO(_NAVI), MO(_ONESHOT)
                                      //`--------------------------'        `--------------------------'
  ),

#ifdef BIG_MEMORY
   [_GAMER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                          ,-----------------------------------------------------.
      KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                  KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_ESC, KC_A, KC_S, KC_D, KC_F,  KC_G,                                           KC_H, CKC_J, CKC_K, CKC_L, CKC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_LEFT_SHIFT, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,                                KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, BUILD_SNAPS,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
                                 KC_LEFT_CTRL, MO(_GAMER_NUMS), KC_SPC,        CKC_SYMS,  MO(_NAVI), MO(_ONESHOT)
                                      //`--------------------------'        `--------------------------'
  ),

   [_GAMER_NUMS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                          ,-----------------------------------------------------.
      KC_TRNS, KC_TRNS, KC_1,  KC_2,    KC_3,   KC_TRNS,                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_TRNS, KC_4,  KC_5,    KC_6,   KC_TRNS,                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_TRNS, KC_7,  KC_8,    KC_9,   KC_TRNS,                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_NO, KC_TRNS,        KC_TRNS,   KC_TRNS, KC_TRNS
                                      //`--------------------------'        `--------------------------'
  ),

#endif

  [_NO_HOMEROW] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                          ,-----------------------------------------------------.
       TAB_CLOSE,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_ESC, KC_A, KC_S, KC_D, KC_F,    KC_G,                                         KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, ENTER_CLOSE_TAB,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LSFT, ALT_TAB, CKC_NUMS,        CKC_SYMS,   MO(_NAVI), MO(_ONESHOT)
                                      //`--------------------------'        `--------------------------'
  ),

  [_NAVI] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                          ,-----------------------------------------------------.
     TAB_CLOSE, KC_NO  ,  KC_NO  ,  KC_NO  ,  KC_NO  ,   KC_NO  ,                      KC_NO  , KC_PGUP, UP, KC_NO  , KC_HOME, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|'
      KC_ESC , KC_LEFT_GUI, KC_LEFT_ALT, KC_LEFT_CTRL, KC_LEFT_SHIFT, KC_APP ,         KC_HOME, LEFT, DOWN, RIGHT, KC_END, KC_PSCR  ,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
     KC_MUTE, KC_VOLD, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU,                             KC_NO  , KC_PGDN, KC_NO  , KC_NO  , KC_END,  ENTER_CLOSE_TAB,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LSFT, KC_BSPC, TURBO_MODIFIER,         KC_NO  , KC_NO  , KC_NO
                                      //`--------------------------'        `--------------------------'
  ), 

  [_NUMS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_NO,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                            KC_6,     KC_7,    KC_8,    KC_9,   KC_0,   KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CALC, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                      KC_PAST,  KC_P4,   KC_P5,   KC_P6,  KC_PPLS, KC_PEQL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NUM  , KC_NO  , KC_NO  , KC_NO  , KC_NO, KC_NO,                         KC_PSLS,  KC_P1,   KC_P2,   KC_P3,  KC_PMNS, KC_PENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_NO  , KC_NO  , KC_NO  ,    KC_ENT, KC_P0, KC_PDOT 
                                      //`--------------------------'  `--------------------------'
  ),

  [_SYMS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_GRV, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                       KC_CIRC, KC_AMPR,   KC_ASTR,  KC_LPRN,  KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TILD  , KC_NO, KC_NO  , KC_SLSH, KC_LCBR, KC_LBRC,                      KC_RBRC, KC_RCBR, KC_BSLS, KC_MINS, KC_PPLS, KC_NO  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO  , KC_LEFT_ANGLE_BRACKET , KC_RIGHT_ANGLE_BRACKET , KC_COPY, KC_PSTE, KC_NO  ,                     KC_NO  , KC_NO  , KC_PIPE, KC_UNDS, KC_EQL, KC_NO  ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_NO  , KC_NO  , KC_ENT  ,    KC_ENT, KC_TRNS, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

#ifdef BIG_MEMORY
[_ONESHOT] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        TAP_UP  ,   SEQ_UP  ,   FOLLOW_UP  ,   RELEASE_UP  ,  TURBO_UP  ,  DF(_DEFAULT)  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_F7,  KC_F8,    KC_F9,    KC_F10,  KC_F11,  KC_F12,                      TAP_DOWN, SEQ_DOWN, FOLLOW_DOWN, RELEASE_DOWN  , TURBO_DOWN  , DF(_GAMER)  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      CLEAR_SNAPS  , KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                      QK_BOOT, KC_NO  , KC_NO  , KC_NO  , KC_NO  , DF(_NO_HOMEROW)  ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_NO  , ALT_F4  , KC_NO  ,    KC_NO  , KC_NO  , KC_NO
                                      //`--------------------------'  `--------------------------'
  )
#else
[_ONESHOT] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        TAP_UP  ,   SEQ_UP  ,   FOLLOW_UP  ,   RELEASE_UP  ,  TURBO_UP  ,  DF(_DEFAULT)  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_F7,  KC_F8,    KC_F9,    KC_F10,  KC_F11,  KC_F12,                      TAP_DOWN, SEQ_DOWN, FOLLOW_DOWN, RELEASE_DOWN  , TURBO_DOWN  , KC_NO  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO  , KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                      QK_BOOT, KC_NO  , KC_NO  , KC_NO  , KC_NO  , DF(_NO_HOMEROW)  ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_NO  , ALT_F4  , KC_NO  ,    KC_NO  , KC_NO  , KC_NO
                                      //`--------------------------'  `--------------------------'
  )
#endif
};

#endif
