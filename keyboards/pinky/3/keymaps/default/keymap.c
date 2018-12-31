#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

extern keymap_config_t keymap_config;

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_ADJ   ADJUST
#define KC_RST   RESET
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------+------.  ,------------------------------------------------.
        ESC,     Q,     W,     E,     R,     T,  LPRN,     RPRN,     Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
      CTLTB,     A,     S,     D,     F,     G,  LBRC,     RBRC,     H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,   ADJ,      ADJ,     N,     M,  COMM,   DOT,  SLSH,   ENT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                            LALT, LOWER,  LGUI,   SPC,      SPC,  RGUI, RAISE,  RALT \
                       //`---------------------------'  `---------------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------+------.  ,------------------------------------------------.
        GRV,     1,     2,     3,     4,     5, _____,    _____,     6,     7,     8,     9,     0,  BSLS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____, _____,    _____, _____, _____, _____,  MINS,   EQL, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____, _____,    _____, _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                           _____, _____, _____, _____,    _____, _____, _____, _____ \
                       //`---------------------------'  `---------------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------+------.  ,------------------------------------------------.
        GRV,     1,     2,     3,     4,     5, _____,    _____,     6,     7,     8,     9,     0,  BSLS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____, _____,    _____, _____, _____, _____,  MINS,   EQL, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____, _____,    _____, _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                           _____, _____, _____, _____,    _____, _____, _____, _____ \
                       //`---------------------------'  `---------------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------+------.  ,------------------------------------------------.
      _____,    F1,    F2,    F3,    F4,    F5,  LCBR,     RCBR,    F6,    F7,    F8,    F9,   F10, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
      _____,   F11,   F12, _____, _____, _____,  LCBR,     RCBR,  HOME,  PGDN,  PGUP,   END, _____, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____, _____,    _____, _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                           _____, _____, _____, _____,    _____, _____, _____, _____ \
                       //`---------------------------'  `---------------------------'
  )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
//
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
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
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
  }
  return true;
}

