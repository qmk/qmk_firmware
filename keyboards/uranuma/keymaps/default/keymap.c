#include QMK_KEYBOARD_H

enum layer_number {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  BASE = SAFE_RANGE,
  KANJI,
  LOWER,
  RAISE,
};

// Layer Mode aliases
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_ADUJST ADJUST
#define KC_DLBS BASE //DF(_BASE)

#define KC_RST   RESET
#define KC_SUSFT SUSFT
#define KC_ZSFT  LSFT_T(KC_Z)
#define KC_MNSF  LSFT_T(KC_MINS)
#define KC_ESCT  LCTL_T(KC_ESC)
#define KC_TBAL  LALT_T(KC_TAB)
#define KC_ALAL  LALT_T(KC_A)
#define KC_ALAP  LALT_T(KC_APP)
#define KC_JEQL  LSFT(KC_MINS)
#define KC_WLCK  LALT(KC_L)
#define KC_SFEQ  LSFT(KC_MINS)
#define KC_SFPL  LSFT(KC_SCLN)
#define KC_SFAS  LSFT(KC_QUOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
  //|----------------------------------.                ,---------------------------------
      KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                    KC_Y, KC_U, KC_I, KC_O, KC_P,
  //|------+------+------+------+------|                |------+------+------+------+-----
      KC_A,  KC_S, KC_D,  KC_F, KC_G,                KC_H,  KC_J,  KC_K, KC_L,  KC_BSLS,
  //|------+------+------+------+------|                |------+------+------+------+-----
      KC_ZSFT, KC_X, KC_C, KC_V, KC_B,               KC_N, KC_M, KC_COMM, KC_DOT, KC_MNSF,
  //|------+------+------+------+------|                |------+------+------+------+------
      KC_ESCT, KC_TBAL, KC_PSCR, KC_LALT, KC_SPC, KC_ENT, LALT(KC_GRV), KC_SLSH, KC_BSLS, KC_RBRC,
  //|------+------+------+------+------|                |------+------+------+------+------
      KC_LSFT, MO(_LOWER),               KC_BSPC, KC_ENT,          MO(_RAISE),KC_RCTL
  //|------+------+------+------+------|                |------+------+------+------+------
  ),

  [_LOWER] = LAYOUT(
  //|--------------------------------------------------------------------------------------------------
       KC_1,     KC_2,     KC_3,     KC_4,     KC_5,    KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+--------
       KC_F1,    KC_F2,    KC_F3,    KC_F4,   KC_F5,  KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+--------
       KC_F11,  KC_F12, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, KC_SCLN, KC_UP,    KC_EQL,
  //|---------+---------+---------+---------+---------+--------+---------+---------+---------+---------
      KC_ESCT,KC_TBAL,KC_LGUI, KC_ENT, KC_BSPC, KC_LALT, KANJI, KC_LEFT, KC_DOWN, KC_RGHT,
  //|------+------+------+------+------|                |------+------+------+------+------
      KC_LSFT, MO(_LOWER),             KC_SPC, KC_ENT,                 MO(_RAISE),KC_RCTL
  //|------+------+------+------+------|                |------+------+------+------+------
  ),

  [_RAISE] = LAYOUT(
  //|---------------------------------------------------------------------------------------------------
       KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------
       KC_F1,    KC_F2,    KC_F3,    KC_F4,   KC_F5,  KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------
       KC_F11,  KC_F12, XXXXXXX,  KANJI,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_UP,    KC_RO,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------
      KC_ESCT,KC_TBAL,KC_LGUI, MO(_LOWER),KC_BSPC, KC_ENT, KANJI, KC_LEFT, KC_DOWN, KC_RGHT,
  //|------+------+------+------+------|                |------+------+------+------+------|
      KC_RSFT, MO(_LOWER),               KC_SPC, KC_ENT,                MO(_RAISE), KC_RCTL
  //|------+------+------+------+------|                |------+------+------+------+------|
  ),

};
