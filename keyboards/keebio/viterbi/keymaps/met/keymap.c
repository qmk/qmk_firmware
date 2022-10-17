#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define CANCEL LCTL(KC_C)
#define TERM LCTL(LALT(KC_T))
#define ALPHAMOD LT(_ALPHA, KC_VOLD)
#define CTLBSP MT(MOD_LCTL, KC_BSPC)
#define GUIDEL MT(MOD_LGUI, KC_DEL)
#define ALTSPC MT(MOD_LALT, KC_SPACE)
#define SPCMOD LT(_MOD, KC_SPACE)
#define JUMPBACK LSFT(KC_TAB)
#define NTAB LCTL(KC_T)
#define CTAB LCTL(KC_W)
#define TAB1 LCTL(KC_1)
#define TAB2 LCTL(KC_2)
#define TAB3 LCTL(KC_3)
#define TAB4 LCTL(KC_4)
#define BWORD LCTL(KC_BSPC)
#define LWORD LCTL(KC_LEFT)
#define RWORD LCTL(KC_RIGHT)
#define TABMOD LT(_MOD, KC_TAB)
#define ENTMOD LT(_ENT, KC_ENTER)

enum layer_names {
  _BASE,
  _PLAYING,
  _PLAYED,
  _NUMS,
  _FN,
  _TEST,
  _ALPHA,
  _QWERTY,
  _REV,
  _DEL,
  _MOD,
  _ENT
};

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
  SOURCE,
  PUSH,
  TEST,
  TST,
  ENAME,
  SNAME,
  LNAME,
  BUS,
  PMERGE,
  CSPEAK
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
  SEND_STRING(SS_TAP(X_N));
  SEND_STRING(SS_TAP(X_N));
  SEND_STRING(SS_LCTL(SS_TAP(X_C)));
}
  break;
  case RESUME:
  if (record->event.pressed) {
  layer_off(_PLAYED);
  layer_on(_PLAYING);
  SEND_STRING(SS_LCTL(SS_TAP(X_C)));
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
  SEND_STRING(SS_TAP(X_N));
}
  break;
  case SHUTDOWN:
  if (record->event.pressed) {
  SEND_STRING(SS_LCTL(SS_TAP(X_C)));
  SEND_STRING("shutdown now");
  SEND_STRING(SS_TAP(X_ENTER));
}
  break;
  case REBOOT:
  if (record->event.pressed) {
  SEND_STRING(SS_LCTL(SS_TAP(X_C)));
  SEND_STRING("reboot");
  SEND_STRING(SS_TAP(X_ENTER));
  }
  break;
  case SOURCE:
  if (record->event.pressed) {
  SEND_STRING("source .bashrc");
  SEND_STRING(SS_TAP(X_ENTER));
  }
  break;
  case PUSH:
  if (record->event.pressed) {
  SEND_STRING("ftp rossmontsinger.net");
  _delay_ms(250);
  SEND_STRING(SS_TAP(X_ENTER));
  _delay_ms(2250);
  SEND_STRING("met@rossmontsinger.net");
  _delay_ms(250);
  SEND_STRING(SS_TAP(X_ENTER));
  _delay_ms(2500);
  SEND_STRING("metboard");
  _delay_ms(250);
  SEND_STRING(SS_TAP(X_ENTER));
  }
  break;
  case TEST:
  if (record->event.pressed) {
  layer_off(_NUMS);
  layer_off(_ALPHA);
  layer_off(_PLAYED);
  layer_on(_PLAYING);
  SEND_STRING(SS_LCTL(SS_TAP(X_C)));
  _delay_ms(250);
  SEND_STRING("play Desktop/met/a_lazoom.mp3");
  SEND_STRING(SS_TAP(X_ENTER));
  }
  case TST:
  if (record->event.pressed) {
  SEND_STRING("tst");
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
  case PMERGE:
  if (record->event.pressed) {
  SEND_STRING(SS_TAP(X_HOME));
  SEND_STRING(SS_TAP(X_BACKSPACE));
  SEND_STRING(SS_TAP(X_SPACE));
  SEND_STRING(SS_LCTL(SS_TAP(X_BACKSPACE)));
  SEND_STRING(SS_TAP(X_SPACE));
      }
break;
case CSPEAK:
  if (record->event.pressed) {
  SEND_STRING(SS_TAP(X_PAGE_DOWN));
  SEND_STRING(SS_TAP(X_ENTER));
  SEND_STRING(SS_TAP(X_ENTER));
  SEND_STRING(SS_TAP(X_PAGE_DOWN));
}
 break;
};

  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_ortho_5x14(
    KC_NO,   STOP   , TST    , _______, _______, _______, BUS    ,     _______, _______, _______, _______, _______, _______, _______, \
    KC_NO,   _______, SET    , SET    , SET    , _______, _______,     _______, _______, _______, _______, _______, _______, _______, \
    KC_NO,   _______, SET    , SET    , SET    , _______, _______,     _______, _______, _______, _______, _______, _______, _______, \
    KC_NO,   LNAME  , SET    , SET    , SET    , _______, _______,     _______, _______, _______, _______, _______, _______, _______, \
    KC_NO,   MO(_FN), _______, SET    , _______, _______, _______,     TG(_QWERTY),KC_B, _______, _______, _______, _______, _______ \
  ),

  [_PLAYING] = LAYOUT_ortho_5x14(
    KC_NO,   _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   _______, _______, _______, _______, _______, STOP   ,     _______, _______, _______, _______, _______, _______, _______
  ),

  [_PLAYED] = LAYOUT_ortho_5x14(
    KC_NO,   _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   _______,_______, _______, _______, _______,NEWRESUME,    _______, _______, _______, _______, _______, _______, _______
  ),

  [_NUMS] = LAYOUT_ortho_5x14(
    KC_NO,   _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   _______, KC_7   , KC_8   , KC_9   , _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   _______, KC_4   , KC_5   , KC_6   , _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   _______, KC_1   , KC_2   , KC_3   , _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   _______, _______, KC_0   , _______, _______, GO     ,     _______, _______, _______, _______, _______, _______, _______
  ),

  [_FN] = LAYOUT_ortho_5x14(
    KC_NO,   SHUTDOWN,_______, _______, _______, _______, KC_VOLU,    _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   REBOOT , _______, _______, _______, _______, KC_VOLD,    _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   ENAME  , _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   _______, _______, _______, _______, _______, SOURCE ,    _______, _______, _______, _______, _______, _______, _______
  ),

  [_TEST] = LAYOUT_ortho_5x14(
    KC_NO,   TST    , TST    , TST    , TST    , TST    , TST     ,    _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   TST    , TST    , TST    , TST    , TST    , TST     ,    _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   TST    , TST    , TST    , TST    , TST    , TST     ,    _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   TST    , TST    , TST    , TST    , TST    , TST     ,    _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   TST    , TST    , TST    , TST    , TST    , TST     ,    _______, _______, _______, _______, _______, _______, _______
  ),
    
  [_ALPHA] = LAYOUT_ortho_5x14(
    KC_NO,   _______, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   ,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   KC_N   , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   KC_M   , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   _______, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO,   _______, KC_H   , KC_J   , KC_K   , KC_L   , GO     ,     _______, _______, _______, _______, _______, _______, _______
  ),
  
 [_QWERTY] = LAYOUT_ortho_5x14(
    KC_NO,   KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL  ,
    KC_NO,   KC_CAPS, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,     KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC ,
    KC_NO,   KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,     KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_PGUP ,
    KC_NO,   KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,     KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_UP,   KC_PGDN ,
    KC_NO,   CTLBSP , GUIDEL , KC_ENTER, ALTSPC, TABMOD , KC_BSPC,     ENTMOD , SPCMOD ,MO(_DEL), KC_BSLS, KC_LEFT, KC_DOWN, KC_RIGHT
  ),

  
  [_REV] = LAYOUT_ortho_5x14(
    KC_NO  , _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO  , _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO  , _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO  , _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO  , _______, _______, _______, _______, KC_TAB , KC_PGDN,     _______, _______, _______, _______, _______, _______, _______
  ),
  
  
 [_DEL] = LAYOUT_ortho_5x14(
    KC_NO  , _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO  , _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO  , _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO  , _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO  , _______, _______, _______, _______, KC_BSPC, BWORD  ,     _______, _______, _______, _______, _______, _______, _______
  ),
  
 [_MOD] = LAYOUT_ortho_5x14(
    KC_NO  , KC_GRAVE,KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,     KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , NTAB ,
    KC_NO  , _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, CTAB,
    KC_NO  , _______, _______, _______, _______, _______, _______,     KC_HOME, KC_LEFT, KC_UP  ,KC_RIGHT, KC_END , _______, _______,
    KC_NO  , _______, _______, _______, _______, _______, _______,     _______, PMERGE , KC_DOWN, _______, _______, _______, _______,
    KC_NO  , _______, _______, _______, _______, LWORD  , RWORD  ,     TG(_QWERTY),_______,_______,_______,_______, _______, _______
  ),
   
 [_ENT] = LAYOUT_ortho_5x14(
    KC_NO  , _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO  , _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO  , _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO  , _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO  , _______, _______, _______, _______, _______, CSPEAK ,     _______, _______, _______, _______, _______, _______, _______
  )
};

