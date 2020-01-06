#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _REV 1
#define _DEL 2
#define _MOD 3
#define _ENT 4
#define CANCEL LCTL(KC_C)
#define TERM LCTL(LALT(KC_T))
#define ALPHAMOD LT(_ALPHA, KC_VOLD)
#define CTLBSP MT(MOD_LCTL, KC_BSPC)
#define GUIDEL MT(MOD_LGUI, KC_DEL)
#define ALTSPC MT(MOD_LALT, KC_SPACE)
#define SPCMOD LT(_MOD, KC_SPACE) 
#define BWORD LCTL(KC_BSPC)
#define JUMPBACK LSFT(KC_TAB)
#define NTAB LCTL(KC_T)
#define CTAB LCTL(KC_W)
#define TAB1 LCTL(KC_1)
#define TAB2 LCTL(KC_2)
#define TAB3 LCTL(KC_3)
#define TAB4 LCTL(KC_4)
#define LWORD LCTL(KC_LEFT)
#define RWORD LCTL(KC_RIGHT)
#define TABMOD LT(_MOD, KC_TAB)
#define ENTMOD LT(_ENT, KC_ENTER)

enum custom_keycodes {
  MET = SAFE_RANGE,
  PMERGE,
  CSPEAK
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  
  case PMERGE:
  if (record->event.pressed) {
  SEND_STRING(SS_TAP(X_HOME));
  SEND_STRING(SS_TAP(X_BSPACE));
  SEND_STRING(SS_TAP(X_SPACE));
  SEND_STRING(SS_LCTRL(SS_TAP(X_BSPACE)));
  SEND_STRING(SS_TAP(X_SPACE));
      }
break;
case CSPEAK:
  if (record->event.pressed) {
  SEND_STRING(SS_TAP(X_PGDOWN));
  SEND_STRING(SS_TAP(X_ENTER));
  SEND_STRING(SS_TAP(X_ENTER));
  SEND_STRING(SS_TAP(X_PGDOWN));
}
 break;
};

  return true;
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


 
  
 [_REV] = LAYOUT_ortho_5x14(
    KC_NO,   KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL  ,
    KC_NO,   KC_TAB, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,     KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC ,
    KC_NO,   JUMPBACK, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,     KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_PGUP ,
    KC_NO,   KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,     KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_UP,   KC_PGDN ,
    KC_NO,   CTLBSP , GUIDEL , KC_ENTER, ALTSPC, TABMOD , KC_BSPC,     ENTMOD , SPCMOD ,MO(_DEL), KC_BSLS, KC_LEFT, KC_DOWN, KC_RIGHT
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
    KC_NO  , _______, _______, _______, _______, LWORD  , RWORD  ,     _______, _______,_______,_______,_______, _______, _______
  ),
   
 [_ENT] = LAYOUT_ortho_5x14(
    KC_NO  , _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO  , _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO  , _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO  , _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    KC_NO  , _______, _______, _______, _______, _______, CSPEAK ,     _______, _______, _______, _______, _______, _______, _______
  )
};

