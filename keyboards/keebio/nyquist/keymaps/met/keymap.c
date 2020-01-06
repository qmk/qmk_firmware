#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _PLAYING 1
#define _PLAYED 2
#define _NUMS 3
#define _FN 4
#define _ALPHA 5
#define _QWERTY 6
#define CANCEL LCTL(KC_C)
#define TERM LCTL(LALT(KC_T))
#define ALPHAMOD LT(_ALPHA, KC_VOLD)


enum custom_keycodes {
  MET = SAFE_RANGE,
  SET,
  GO,
  STOP,
  RESUME,
  NEWRESUME,
  SYNC,
  SHUTDOWN,
  REBOOT,
  TEST,
  ENAME,
  SNAME,
  LNAME,
  BUS

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case SET:
  if (record->event.pressed) {
  layer_on(_NUMS);
  SEND_STRING("met ");
}
  break;
  case GO:
  if (record->event.pressed) {
  layer_off(_NUMS);
  layer_off(_ALPHA);
  layer_off(_PLAYED);
  layer_on(_PLAYING);
  SEND_STRING(SS_TAP(X_ENTER));
}
  break;
  case STOP:
  if (record->event.pressed) {
  layer_off(_PLAYING);
  layer_on(_PLAYED);
  layer_off(_NUMS);
  layer_off(_ALPHA);
  SEND_STRING(SS_LCTRL(SS_TAP(X_C)));
}
  break;
  case RESUME:
  if (record->event.pressed) {
  layer_off(_PLAYED);
  layer_on(_PLAYING);
  SEND_STRING(SS_LCTRL(SS_TAP(X_C)));
  SEND_STRING(SS_TAP(X_UP));
  SEND_STRING(SS_TAP(X_ENTER));
}
  break;
  case NEWRESUME:
  if (record->event.pressed) {
  layer_off(_NUMS);
  layer_off(_ALPHA);
  layer_off(_PLAYED);
  layer_on(_PLAYING);
  SEND_STRING(SS_TAP(X_R));
  SEND_STRING(SS_TAP(X_ENTER));
}
  break;
  case SYNC:
  if (record->event.pressed) {
  SEND_STRING(SS_LCTRL(SS_TAP(X_C)));
  _delay_ms(70);
  SEND_STRING(SS_TAP(X_R));
  SEND_STRING(SS_TAP(X_ENTER));
}
  break;
  case SHUTDOWN:
  if (record->event.pressed) {
  SEND_STRING(SS_LCTRL(SS_TAP(X_C)));
  SEND_STRING("shutdown now");
  SEND_STRING(SS_TAP(X_ENTER));
}
  break;
  case REBOOT:
  if (record->event.pressed) {
  SEND_STRING(SS_LCTRL(SS_TAP(X_C)));
  SEND_STRING("reboot");
  SEND_STRING(SS_TAP(X_ENTER));
  }
  break;
  case TEST:
  if (record->event.pressed) {
  layer_off(_NUMS);
  layer_off(_ALPHA);
  layer_off(_PLAYED);
  layer_on(_PLAYING);
  SEND_STRING(SS_LCTRL(SS_TAP(X_C)));
  _delay_ms(250);
  SEND_STRING("play Desktop/met/a_lazoom.mp3");
  SEND_STRING(SS_TAP(X_ENTER));
  }
  break;
  case ENAME:
  if (record->event.pressed) {
  SEND_STRING("sname ");
  layer_on(_NUMS);
  layer_on(_ALPHA);
  }
  break;
  case SNAME:
  if (record->event.pressed) {
  SEND_STRING(SS_TAP(X_ENTER));
  layer_off(_NUMS);
  layer_off(_ALPHA);
  }
  break;
  case LNAME:
  if (record->event.pressed) {
  SEND_STRING("met $");
  layer_off(_NUMS);
  layer_on(_ALPHA);
  }
  break;
  case BUS:
  if (record->event.pressed) {
  SEND_STRING("met $bus");
  layer_off(_NUMS);
  layer_off(_ALPHA);
  layer_off(_PLAYED);
  layer_on(_PLAYING);
  SEND_STRING(SS_TAP(X_ENTER));
  }
  break;
};

  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[_BASE] = LAYOUT_ortho_5x12( \
  BUS    , _______, _______, _______, _______, STOP   ,    _______, _______, _______, _______, _______, _______, \
  _______, _______, SET    , SET    , SET    , KC_VOLU,    _______, _______, _______, _______, _______, _______, \
  _______, _______, SET    , SET    , SET    , KC_VOLD,    _______, _______, _______, _______, _______, _______, \
  _______, _______, SET    , SET    , SET    , LNAME  ,    _______, _______, _______, _______, _______, _______, \
  _______, _______, MO(_FN), SET    , _______, _______,    _______, _______, _______, _______, _______, _______ \
),

[_PLAYING] = LAYOUT_ortho_5x12(
    _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, STOP   ,  _______, _______, _______, _______, _______, _______
  ),
  
    
[_PLAYED] = LAYOUT_ortho_5x12(
    _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,NEWRESUME, _______, _______, _______, _______, _______, _______
  ),
  
[_NUMS] = LAYOUT_ortho_5x12(
    _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
    _______, _______, KC_7   , KC_8   , KC_9   , _______,  _______, _______, _______, _______, _______, _______,
    _______, _______, KC_4   , KC_5   , KC_6   , _______,  _______, _______, _______, _______, _______, _______,
    _______, _______, KC_1   , KC_2   , KC_3   , _______,  _______, _______, _______, _______, _______, _______,
    _______, _______, _______, KC_0   , _______, GO     ,  _______, _______, _______, _______, _______, _______
  ),

  
[_FN] = LAYOUT_ortho_5x12(
    _______, _______, _______, _______, _______, SHUTDOWN, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, REBOOT  , _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, TEST    , _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, ENAME   , _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, TERM    ,  _______, _______, _______, _______, _______, _______
  ),
[_ALPHA] = LAYOUT_ortho_5x12(
    KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , _______,  _______, _______, _______, _______, _______, _______,
    KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , _______,  _______, _______, _______, _______, _______, _______,
    KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , _______,  _______, _______, _______, _______, _______, _______,
    KC_H   , KC_J   , KC_K   , KC_L   , KC_X   , _______,  _______, _______, _______, _______, _______, _______,
    KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , GO     ,  _______, _______, _______, _______, _______, _______
  ),
  
 [_QWERTY] = LAYOUT_ortho_5x14(
    KC_INS,  KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC, KC_DEL ,
    KC_MINS, KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,     KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC,
    KC_EQL,  KC_ESC , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,     KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT ,
    KC_PGUP, KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,     KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_HOME, KC_END ,
    KC_PGDN, ADJUST , KC_LCTL, KC_LALT, KC_LGUI, LOWER  , KC_SPC ,     KC_SPC , RAISE  , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_BSLS
  )

};
