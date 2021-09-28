#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _ADJUST 1

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  ADJUST,
};

#define FN      LT(_ADJUST, KC_PENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------.
 * | Bcsp | Home |  End |  PUp |  PDn |  FN  |
 * |------+------+------+------+------+------|
 * | Del  |   1  |   2  |   3  | Slsh | Print|
 * |------+------+------+------+------+------|
 * | Ins  |   4  |   5  |   6  |  Ast |  Up  |
 * |------+------+------+------+------+------|
 * | NLock|   7  |   8  |   9  |  Up  | Down |
 * |------+------+------+------+------+------|
 * |      0      | Meta | Left | Down | Right|
 * `-----------------------------------------'
 */

 /* [_QWERTY] = LAYOUT( \
  *  KC_DEL , KC_HOME, KC_END, KC_PGUP, KC_PGDN, KC_BSPC, KC_DEL , KC_HOME, KC_END , KC_PGUP, KC_PGDN, KC_PAUS, \
  *  KC_INS , KC_P1  , KC_P2 , KC_P3  , KC_PSLS, KC_PSCR, KC_INS , KC_P1  , KC_P2  , KC_P3  , KC_PSLS, KC_PSCR, \
  *  KC_F5  , KC_P4  , KC_P5 , KC_P6  , KC_PAST, KC_PDOT, KC_F5  , KC_P4  , KC_P5  , KC_P6  , KC_PAST, KC_UP, \
  *  KC_LSFT, KC_P7  , KC_P8 , KC_P9  , KC_PMNS, KC_PEQL, KC_NLCK, KC_P7  , KC_P8  , KC_P9  , KC_PMNS, KC_DOWN, \
  *  KC_LBRC, KC_RBRC, KC_P0 , KC_PPLS , FN     , FN     , KC_P0  , KC_P0  , KC_LBRC, KC_RBRC, KC_EQL , FN \
  *  ), */

[_QWERTY] = LAYOUT( \
 FN      , KC_PGDN, KC_PGUP, KC_END , KC_HOME, KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
 KC_PSCR , KC_PSLS, KC_P3  , KC_P2  , KC_P1  , KC_DEL , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
 KC_BRIU , KC_PAST, KC_P6  , KC_P5  , KC_P4  , KC_INS , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
 KC_BRID , KC_UP  , KC_P9  , KC_P8  , KC_P7  , KC_APP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
 KC_RIGHT, KC_DOWN, KC_LEFT, KC_LGUI , KC_P0  , KC_P0  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
),

/* Adjust
 * ,-----------------------------------------.
 * |      |      |      |      |      | Reset|
 * |------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |      | Debug|
 * |------+------+------+------+------+------|
 * |      |  F4  |  F5  |  F6  |      |      |
 * |------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |      |      |
 * |------+------+------+------+------+------|
 * |     F10     |  F11 |  F12 |      |      |
 * `-----------------------------------------'
 */
/* 
 *  [_ADJUST] =  LAYOUT( \
 *  _______, _______, _______, _______, _______, RESET,   _______, _______, _______, _______, _______, RESET, \
 *  _______, KC_F1,   KC_F2,   KC_F3,   _______, DEBUG,   _______, KC_F1,   KC_F2,   KC_F3,   _______, DEBUG, \
 *  _______, KC_F4,   KC_F5,   KC_F6,   _______, _______, _______, KC_F4,   KC_F5,   KC_F6,   _______, _______, \
 *  _______, KC_F7,   KC_F8,   KC_F9,   KC_PDOT, _______, _______, KC_F7,   KC_F8,   KC_F9,   _______, _______, \
 *  KC_F10 , KC_F11,  KC_F12, KC_PEQL,  _______, _______, KC_F10, KC_F10,   KC_F11,  KC_F12,  _______, _______ \
 *  )
 *  */

 [_ADJUST] =  LAYOUT( \
 _______, BL_STEP, BL_TOGG, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
 _______, _______, KC_F3  , KC_F2  , KC_F1  , _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
 _______, _______, KC_F6  , KC_F5  , KC_F4  , _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
 _______, _______, KC_F9  , KC_F8  , KC_F7  , _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
 _______, KC_PEQL, KC_F12 , KC_F11 , KC_F10 ,  KC_F10, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
)

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef CONSOLE_ENABLE
          uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
        #endif 
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
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
