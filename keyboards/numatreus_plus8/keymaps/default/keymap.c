// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 10

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( /* Qwerty */
    KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                           KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_MINS,
    KC_LCTL,    KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                           KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_ENT,
    KC_LSFT,    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                           KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_UP,    SFT_T(KC_SLSH),
    KC_MUTE,    KC_VOLD,  KC_VOLU,  KC_LALT,  KC_LGUI,  KC_SPC,   LOWER,    RAISE,  KC_BSPC, KC_LGUI, KC_LALT,  KC_LEFT,  KC_DOWN,  KC_RGHT
  ),

  /*
   * !        @     #    $     %        ||     ^    &    *     (    )
   *  del   left  down right pgdn       ||     down    F4    F5    F6   F11
   *       volup             reset      ||             F1    F2    F3   F12
   *       voldn  super shift space bspc|| alt  ent    L0  prtsc scroll pause
   */
  [_LOWER] = LAYOUT( /* [> LOWER <] */
    KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                       KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_EQL,
    KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,                      KC_HOME,KC_PGDN,KC_PGUP,KC_END, KC_BSLS,KC_QUOT,
    KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,                     _______,_______,KC_LBRC,KC_RBRC,KC_PGUP,_______,
    KC_MRWD,KC_MPLY,KC_MFFD,_______,_______,_______,_______,    _______,_______,_______,_______,KC_HOME,KC_PGDN,KC_END
  ),

  /*
   *  1       2     3     4     5        ||     6    7     8     9    0
   *  #     left   down  right  $        ||     pgdn    4     5     6    +
   *  [       ]      (     )    &        ||       `     1     2     3    \
   * lower  insert super shift space bksp|| alt Ent   fn    .     0    =
   */
  [_RAISE] = LAYOUT( /* [> RAISE <] */
    KC_TILD,KC_EXLM,KC_AT,  KC_HASH,KC_DLR,KC_PERC,                     KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_PLUS,
    _______,_______,_______,KC_DEL, KC_RGHT,KC_ESC,                     KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_PIPE,KC_DQUO,
    _______,_______,_______,_______,_______,KC_LEFT,                    _______,_______,KC_LCBR,KC_RCBR,_______,_______,
    KC_MRWD,KC_MPLY,KC_MFFD,_______,_______,_______,_______,    _______,_______,_______,_______,_______,_______,_______
  ),

  /*
   * !        @     #    $     %        ||     ^    &    *     (    )
   *  del   left  down right pgdn       ||     down    F4    F5    F6   F11
   *       volup             reset      ||             F1    F2    F3   F12
   *       voldn  super shift space bspc|| alt  ent    L0  prtsc scroll pause
   */
  [_ADJUST] = LAYOUT( /* [> ADJUST <] */
    _______,_______,_______,_______,RESET,  _______,                    _______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,                    _______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,                    _______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,    _______,_______,_______,_______,_______,_______,_______
  )

};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        register_code(KC_RSFT);
      } else {
        unregister_code(KC_RSFT);
      }
    break;
  }
  return MACRO_NONE;
};

// レイヤーキーを変換・無変換キーと共用する際に動作を改善する。
static bool lower_pressed = false;
static uint16_t lower_pressed_time = 0;
static bool raise_pressed = false;
static uint16_t raise_pressed_time = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        lower_pressed = true;
        lower_pressed_time = record->event.time;

        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        /*
        長押し時に入力キャンセルする場合はこれ
        if (lower_pressed && (TIMER_DIFF_16(record->event.time, lower_pressed_time) < TAPPING_TERM)) {
        */
        if (lower_pressed) {
          register_code(KC_LANG2); // for macOS
          register_code(KC_MHEN);
          unregister_code(KC_MHEN);
          unregister_code(KC_LANG2);
        }
        lower_pressed = false;
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        raise_pressed = true;
        raise_pressed_time = record->event.time;

        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        /*
        長押し時に入力キャンセルする場合はこれ
        if (raise_pressed && (TIMER_DIFF_16(record->event.time, raise_pressed_time) < TAPPING_TERM)) {
        */
        if (raise_pressed) {
          register_code(KC_LANG1); // for macOS
          register_code(KC_HENK);
          unregister_code(KC_HENK);
          unregister_code(KC_LANG1);
        }
        raise_pressed = false;
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
    default:
      if (record->event.pressed) {
        // reset the flags
        lower_pressed = false;
        raise_pressed = false;
      }
      break;
  }
  return true;
}
/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
         print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
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
*/
