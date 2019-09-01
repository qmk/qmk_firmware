#include QMK_KEYBOARD_H
#include "keymap_jp.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  JP = SAFE_RANGE,
  US,
  SHIFT,
  QWERTY,
  LOWER,
  RAISE,
  ADJUST,
  Z_0,
  Z_1,
  Z_2,
  Z_3,
  Z_4,
  Z_5,
  Z_6,
  Z_7,
  Z_8,
  Z_9,
  CIRC,
  AT,
  LBRC,
  RBRC,
  BSLS,
  AMPR,
  QUOT,
  LPRN,
  RPRN,
  EQL,
  TILD,
  PIPE,
  GRV,
  LCBR,
  PLUS,
  ASTR,
  RCBR,
  UNDS,
  MINS,
  SCLN,
  COMM,
  DOT,
  SLSH,
  EXLM,
  HASH,
  DLR,
  PERC,
  DEL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,----------------------------------------------------------------------------------------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |   [  |                    |   ]  |   6  |   7  |   8  |   9  |   0  |  `   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   -  |                    |   =  |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  | Bksp |                    | Bksp |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  | Shift|                    | Shift|   N  |   M  |   ,  |   .  |   /  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Shift|Adjust|  ALt |  GUI |||||||| Lower| Space|      ||||||||      | Enter| Raise||||||||  GUI |  ALt |Adjust| Shift|
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY] = LAYOUT( \
    KC_ESC,  Z_1,     Z_2,     Z_3,     Z_4,     Z_5,     LBRC   ,                        RBRC,    Z_6,     Z_7,     Z_8,     Z_9,     Z_0,     GRV    , \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    MINS   ,                        EQL,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    BSLS   , \
    KC_LGUI, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_BSPC,                        KC_BSPC, KC_H,    KC_J,    KC_K,    KC_L,    SCLN,    QUOT   , \
    SHIFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    SHIFT  ,                        SHIFT,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SHIFT  , \
    SHIFT,   ADJUST,  KC_LALT, KC_LCTL,          LOWER,   KC_SPC ,XXXXXXX,        XXXXXXX,KC_ENT , RAISE,            KC_LCTL, KC_LALT, ADJUST,  SHIFT    \
  ),

  /* Lower
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |      |                    |      |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |  ~   |   !  |   @  |   #  |   $  |   %  |      |                    |      |   ^  |   &  |   *  |   (  |   )  |  |   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Tab  |   1  |   2  |   3  |   4  |   5  |      |                    |      |   6  |   7  |   8  |   9  |   0  | Enter|
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |   -  |   [  |      |                    |      |   ]  |   =  |      |      |      |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      | Bksp |      ||||||||      | Bksp |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT(
    KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,                        _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12 , \
    TILD,    EXLM,    AT,      HASH,    DLR,     PERC,    _______,                        _______, CIRC,    AMPR,    ASTR,    LPRN,    RPRN,    PIPE   , \
    KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,                        _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0   , KC_ENT , \
    _______, _______, _______, _______, KC_MINS, LBRC,    _______,                        _______, RBRC,    EQL,     _______, _______, _______, _______, \
    _______, _______, _______, _______,          _______, KC_BSPC,_______,        _______,KC_BSPC, _______,          _______, _______, _______, _______  \
  ),

  /* Raise
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |      |                    |      |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |  ~   |   !  |   @  |   #  |   $  |   %  |      |                    |      |   ^  |   &  |   *  |   (  |   )  |  |   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Tab  |   1  |   2  |   3  |   4  |   5  |      |                    |      |   6  |   7  |   8  |   9  |   0  | Enter|
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |   -  |   [  |      |                    |      |   ]  |   =  |      |      |      |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      | Bksp |      ||||||||      | Bksp |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_RAISE] = LAYOUT(
    KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,                        _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12 , \
    TILD,    EXLM,    AT,      HASH,    DLR,     PERC,    _______,                        _______, CIRC,    AMPR,    ASTR,    LPRN,    RPRN,    PIPE   , \
    KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,                        _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0   , KC_ENT , \
    _______, _______, _______, _______, KC_MINS, LBRC,    _______,                        _______, RBRC,    EQL,     _______, _______, _______, _______, \
    _______, _______, _______, _______,          _______, KC_BSPC,_______,        _______,KC_BSPC, _______,          _______, _______, _______, _______  \
  ),

  /* Adjust
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |  US  |                    |  JP  |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |  ~   |   !  |   @  |   #  |   $  |   %  |      |                    |      |   ^  |   &  |   *  |   (  |   )  |  |   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      | Home |PageDn|PageUp|  End ||||||||      |                    |      | Left | Down |  Up  | Right||||||||      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |   _  |   {  |      |                    |      |   }  |   +  |      |      |      |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      | Bksp |      ||||||||      | Bksp |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_ADJUST] = LAYOUT(
    KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   US     ,                        JP,      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12 , \
    TILD,    EXLM,    AT,      HASH,    DLR,     PERC,    _______,                        _______, CIRC,    AMPR,    ASTR,    LPRN,    RPRN,    PIPE   , \
    _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, _______,                        _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, _______, \
    _______, _______, _______, _______, UNDS,    LCBR,    _______,                        _______, RCBR,    PLUS,    _______, _______, _______, _______, \
    _______, _______, _______, _______,          _______, KC_BSPC,_______,        _______,KC_BSPC, _______,          _______, _______, _______, _______  \
  )
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

#define JP_LAYOUT true
#define US_LAYOUT false

#ifdef MASTER_LEFT
bool LAYOUT_STATUS = US_LAYOUT;
#else
bool LAYOUT_STATUS = JP_LAYOUT;
#endif

bool SHIFT_PRESSED = false;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

#define SEND_STRING_RESTORE(STR) \
  (SHIFT_PRESSED ? SEND_STRING(STR SS_DOWN(X_LSHIFT)) : SEND_STRING(STR SS_UP(X_LSHIFT)))

#define KEY(CODE) \
  (record->event.pressed ? SEND_STRING_RESTORE(SS_DOWN(X_ ## CODE)) : SEND_STRING_RESTORE(SS_UP(X_ ## CODE)))

#define KEY_SHIFT(CODE) \
  (record->event.pressed ? SEND_STRING_RESTORE(SS_DOWN(X_LSHIFT) SS_DOWN(X_ ## CODE)) : SEND_STRING_RESTORE(SS_UP(X_ ## CODE)))

#define KEY_UPSHIFT(CODE) \
  (record->event.pressed ? SEND_STRING_RESTORE(SS_UP(X_LSHIFT) SS_DOWN(X_ ## CODE)) : SEND_STRING_RESTORE(SS_UP(X_ ## CODE)))

#define SHIFT_DU(CODE_DOWN, CODE_UP) (SHIFT_PRESSED ? CODE_DOWN : CODE_UP)
#define CASE_US(CODE, US, JP) case CODE: (LAYOUT_STATUS == JP_LAYOUT ? JP : US); return false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    CASE_US(Z_0,  KEY(0), SHIFT_DU(KEY_SHIFT(9), KEY(0)));
    CASE_US(Z_1,  KEY(1), KEY(1));
    CASE_US(Z_2,  KEY(2), SHIFT_DU(KEY_UPSHIFT(LBRACKET), KEY(2)));
    CASE_US(Z_3,  KEY(3), KEY(3));
    CASE_US(Z_4,  KEY(4), KEY(4));
    CASE_US(Z_5,  KEY(5), KEY(5));
    CASE_US(Z_6,  KEY(6), SHIFT_DU(KEY_UPSHIFT(EQUAL), KEY(6)));
    CASE_US(Z_7,  KEY(7), SHIFT_DU(KEY_SHIFT(6), KEY(7)));
    CASE_US(Z_8,  KEY(8), SHIFT_DU(KEY_SHIFT(QUOTE), KEY(8)));
    CASE_US(Z_9,  KEY(9), SHIFT_DU(KEY_SHIFT(8), KEY(9)));
    CASE_US(DEL,  KEY(DELETE), KEY_UPSHIFT(BSPACE));
    CASE_US(TILD, KEY_SHIFT(GRAVE), KEY_SHIFT(EQUAL));
    CASE_US(EXLM, KEY_SHIFT(1), KEY_SHIFT(1));
    CASE_US(AT,   KEY_SHIFT(2), KEY(LBRACKET));
    CASE_US(HASH, KEY_SHIFT(3), KEY_SHIFT(3));
    CASE_US(DLR,  KEY_SHIFT(4), KEY_SHIFT(4));
    CASE_US(PERC, KEY_SHIFT(5), KEY_SHIFT(5));
    CASE_US(CIRC, KEY_SHIFT(6), KEY(EQUAL));
    CASE_US(AMPR, KEY_SHIFT(7), KEY_SHIFT(6));
    CASE_US(ASTR, KEY_SHIFT(8), KEY_SHIFT(QUOTE));
    CASE_US(LPRN, KEY_SHIFT(9), KEY_SHIFT(8));
    CASE_US(RPRN, KEY_SHIFT(0), KEY_SHIFT(9));
    CASE_US(LBRC, KEY(LBRACKET), SHIFT_DU(KEY_SHIFT(RBRACKET), KEY(RBRACKET)));
    CASE_US(RBRC, KEY(RBRACKET), SHIFT_DU(KEY_SHIFT(NONUS_HASH), KEY(NONUS_HASH)));
    CASE_US(LCBR, KEY_SHIFT(LBRACKET), KEY_SHIFT(RBRACKET));
    CASE_US(RCBR, KEY_SHIFT(RBRACKET), KEY_SHIFT(NONUS_HASH));
    CASE_US(GRV,  KEY(GRAVE), SHIFT_DU(KEY_SHIFT(EQUAL), KEY_SHIFT(LBRACKET)));
    CASE_US(BSLS, KEY(BSLASH), SHIFT_DU(KEY_SHIFT(INT3), KEY(INT3)));
    CASE_US(PIPE, KEY_SHIFT(BSLASH), KEY_SHIFT(INT3));
    CASE_US(MINS, KEY(MINUS), SHIFT_DU(KEY_SHIFT(INT1), KEY(MINUS)));
    CASE_US(UNDS, KEY_SHIFT(MINUS), KEY_SHIFT(INT1));
    CASE_US(EQL,  KEY(EQUAL), SHIFT_DU(KEY_SHIFT(SCOLON), KEY_SHIFT(MINUS)));
    CASE_US(PLUS, KEY_SHIFT(EQUAL), KEY_SHIFT(SCOLON));
    CASE_US(SCLN, KEY(SCOLON), SHIFT_DU(KEY_UPSHIFT(QUOTE), KEY(SCOLON)));
    CASE_US(QUOT, KEY(QUOTE), SHIFT_DU(KEY_SHIFT(2), KEY_SHIFT(7)));
    case JP:
      if (record->event.pressed)
        LAYOUT_STATUS = JP_LAYOUT;
      return false;
      break;
    case US:
      if (record->event.pressed)
        LAYOUT_STATUS = US_LAYOUT;
      return false;
      break;
    case SHIFT:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_LSHIFT));
        SHIFT_PRESSED = true;
      } else {
        SEND_STRING(SS_UP(X_LSHIFT));
        SHIFT_PRESSED = false;
      }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed)
        set_single_persistent_default_layer(_QWERTY);
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed)
        layer_on(_ADJUST);
      else
        layer_off(_ADJUST);
      return false;
      break;
  }
  return true;
}

