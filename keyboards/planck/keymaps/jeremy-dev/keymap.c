// This is the personal keymap of Jeremy Cowgar (@jcowgar). It is written for the programmer.

// Configuration options
#define PREVENT_STUCK_MODIFIERS

#pragma message "You may need to add LAYOUT_planck_grid to your keymap layers - see default for an example"
#include "planck.h"
#include "action_layer.h"
#include "eeconfig.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
enum my_layers {
  ALPH = 0,
  NUMS,
  CURS,
  SYMB,
  FKEY
};

// Each macro gets a name for readability.
enum my_keycodes {
  MY_ABVE = SAFE_RANGE,
  MY_BELW,
  MY_TERM,
  MY_DEQL, // /=
  MY_MEQL, // *=
  MY_SEQL, // -=
  MY_PEQL, // +=
  MY_NEQL, // !=
  MY_LTGT, // <>
  MY_DPIP, // ||
  MY_DAMP, // &&
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [ALPH] = {
    {KC_Q,          KC_W,      KC_E,      KC_R,      KC_T,    KC_LBRC,        KC_RBRC,        KC_Y,    KC_U,      KC_I,      KC_O,      KC_P},
    {KC_A,          KC_S,      KC_D,      KC_F,      KC_G,    KC_LPRN,        KC_RPRN,        KC_H,    KC_J,      KC_K,      KC_L,      KC_SCLN},
    {SFT_T(KC_Z),   KC_X,      KC_C,      KC_V,      KC_B,    KC_LCBR,        KC_RCBR,        KC_N,    KC_M,      KC_COMM,   KC_DOT,    SFT_T(KC_SLSH)},
    {CTL_T(KC_TAB), OSL(FKEY), OSL(NUMS), OSL(SYMB), KC_SPC,  ALT_T(KC_BSPC), GUI_T(KC_DELT), KC_ENT,  OSL(SYMB), OSL(CURS), TG(CURS),  CTL_T(KC_ESC)}
  },
  [NUMS] = {
    {KC_NO,         KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_TRNS,        KC_TRNS,        KC_COMM, KC_7,      KC_8,      KC_9,      KC_SLSH},
    {KC_LSFT,       KC_LGUI,   KC_LALT,   KC_LCTL,   KC_NO,   KC_TRNS,        KC_TRNS,        KC_LPRN, KC_4,      KC_5,      KC_6,      KC_ASTR},
    {KC_NO,         KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_TRNS,        KC_TRNS,        KC_RPRN, KC_1,      KC_2,      KC_3,      KC_MINS},
    {KC_NO,         KC_NO,     KC_TRNS,   TG(NUMS),  KC_TRNS, KC_TRNS,        KC_TRNS,        KC_TRNS, KC_0,      KC_DOT,    KC_EQL,    KC_PLUS}
  },
  [CURS] = {
    {KC_MPLY,       KC_BSPC,   KC_UP,     KC_DELT,   KC_PGUP, KC_TRNS,        KC_TRNS,        KC_NO,   KC_NO,     KC_NO,     KC_NO,     KC_NO},
    {KC_VOLU,       KC_LEFT,   KC_DOWN,   KC_RGHT,   KC_PGDN, KC_TRNS,        KC_TRNS,        KC_NO,   KC_LCTL,   KC_LALT,   KC_LGUI,   KC_LSFT},
    {KC_VOLD,       KC_NO,     MY_ABVE,   MY_TERM,   KC_NO,   KC_TRNS,        KC_TRNS,        KC_NO,   KC_NO,     KC_NO,     KC_NO,     KC_LSFT},
    {KC_MUTE,       KC_NO,     MY_BELW,   KC_NO,     KC_TRNS, KC_TRNS,        KC_TRNS,        KC_TRNS, KC_NO,     KC_TRNS,   KC_TRNS,   KC_NO}
  },
  [SYMB] = {
    {MY_DEQL,       MY_MEQL,   MY_SEQL,   MY_PEQL,   MY_NEQL, KC_NO,          KC_NO,          MY_LTGT, KC_LABK,   KC_RABK,   KC_COLN,   KC_DLR},
    {KC_SLSH,       KC_ASTR,   KC_MINS,   KC_PLUS,   KC_EQL,  KC_NO,          KC_PIPE,        MY_DPIP, KC_GRV,    KC_QUOT,   KC_DQUO,   KC_HASH},
    {KC_BSLS,       KC_CIRC,   KC_PERC,   KC_UNDS,   KC_NO,   KC_NO,          KC_AMPR,        MY_DAMP, KC_TILD,   KC_AT,     KC_EXLM,   KC_QUES},
    {KC_NO,         KC_NO,     KC_NO,     KC_TRNS,   KC_NO,   KC_TRNS,        KC_TRNS,        KC_TRNS, KC_TRNS,   KC_NO,     KC_NO,     KC_NO}
  },
  [FKEY] = {
    {KC_NO,         KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,          KC_NO,          KC_NO,   KC_F9,     KC_F10,    KC_F11,    KC_F12},
    {KC_LSFT,       KC_LGUI,   KC_LALT,   KC_LCTL,   KC_NO,   KC_NO,          KC_NO,          KC_NO,   KC_F5,     KC_F6,     KC_F7,     KC_F8},
    {KC_NO,         KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,          KC_NO,          KC_NO,   KC_F1,     KC_F2,     KC_F3,     KC_F4},
    {KC_NO,         KC_TRNS,   KC_NO,     KC_NO,     KC_NO,   KC_NO,          KC_NO,          KC_NO,   KC_NO,     KC_NO,     KC_NO,     KC_NO}
  }
};

void press_key(uint16_t key) {
  register_code(key);
  unregister_code(key);
}

void press_two_keys(uint16_t key1, uint16_t key2) {
  register_code(key1);
  register_code(key2);
  unregister_code(key2);
  unregister_code(key1);
}

void press_three_keys(uint16_t key1, uint16_t key2, uint16_t key3) {
  register_code(key1);
  register_code(key2);
  register_code(key3);
  unregister_code(key3);
  unregister_code(key2);
  unregister_code(key1);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MY_BELW:
      if (record->event.pressed) {
        press_two_keys(KC_LGUI, KC_RGHT);
        press_key(KC_ENT);
      }

      return false;

    case MY_ABVE:
      if (record->event.pressed) {
        press_two_keys(KC_LGUI, KC_LEFT);
        press_key(KC_ENT);
        press_key(KC_UP);
      }

      return false;

    case MY_TERM:
      if (record->event.pressed) {
        press_three_keys(KC_LGUI, KC_LSFT, KC_ENT);
      }

      return false;

    case MY_DEQL: // /=
      if (record->event.pressed) {
        press_key(KC_SLSH);
        press_key(KC_EQL);
      }

      return false;

    case MY_MEQL: // *=
      if (record->event.pressed) {
        press_two_keys(KC_LSFT, KC_ASTR);
        press_key(KC_EQL);
      }

      return false;

    case MY_SEQL: // -=
      if (record->event.pressed) {
        press_key(KC_MINS);
        press_key(KC_EQL);
      }

      return false;

    case MY_PEQL: // +=
      if (record->event.pressed) {
        press_two_keys(KC_LSFT, KC_PLUS);
        press_key(KC_EQL);
      }

      return false;

    case MY_NEQL: // !=
      if (record->event.pressed) {
        press_two_keys(KC_LSFT, KC_EXLM);
        press_key(KC_EQL);
      }

      return false;

    case MY_LTGT: // <>
      if (record->event.pressed) {
        press_two_keys(KC_LSFT, KC_LABK);
        press_two_keys(KC_LSFT, KC_RABK);
      }

      return false;

    case MY_DPIP: // ||
      if (record->event.pressed) {
        press_two_keys(KC_LSFT, KC_PIPE);
        press_two_keys(KC_LSFT, KC_PIPE);
      }

      return false;

    case MY_DAMP: // &&
      if (record->event.pressed) {
        press_two_keys(KC_LSFT, KC_AMPR);
        press_two_keys(KC_LSFT, KC_AMPR);
      }

      return false;
  }

  return true;
}
