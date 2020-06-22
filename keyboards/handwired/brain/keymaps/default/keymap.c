#include QMK_KEYBOARD_H



// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  LOWER = SAFE_RANGE,

  RAISE,
  ADJUST,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[_QWERTY] = LAYOUT(
  //       |------------------------------------------.         ,---------------------------------------------,
              KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_NO,           KC_NO, KC_Y,  KC_U,    KC_I,   KC_O,    KC_P,
  //|------+------+------+------+------+------+-------|         |------+------+------+-------+--------+-------+--------,
    KC_LCTL,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_NO,           KC_NO, KC_H,  KC_J,    KC_K,   KC_L, KC_SCLN, KC_QUOT,
  //|------+------+------+------+------+------+-------|         |------+------+------+-------+-------+--------+--------,
    KC_LSFT,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_NO,           KC_NO, KC_N,  KC_M, KC_COMM, KC_DOT, KC_SLSH,  KC_ESC,
  //|------+------+------+------+------+------+-------|         |------+------+------+-------+-------+--------+--------|
             KC_NO, KC_NO,        KC_NO, LOWER, KC_SPC,          KC_ENT, RAISE, KC_NO,          KC_NO,   KC_NO,
         //|------+------|   //|-------+------+-------|         |------+------+------|       |-------+--------|
                                  KC_NO, KC_NO,  KC_NO,           KC_NO, KC_NO,  KC_NO
                             //`----------------------'         `--------------------'

  ),

[_LOWER] = LAYOUT(
  //       |-----------------------------------------------.         ,--------------------------------------------------------,
              KC_1,  KC_2,    KC_3,   KC_3,    KC_4, KC_ESC,              KC_5,    KC_6,    KC_7,     KC_8,     KC_9,     KC_0,
  //|------+------+------+--------+-------+------+---------|         |--------+--------+--------+---------+---------+---------+--------,
    KC_LCTL, KC_NO, KC_NO,   KC_NO,  KC_NO,   KC_NO,  KC_NO,             KC_NO, KC_LEFT, KC_DOWN,    KC_UP, KC_RIGHT,    KC_NO, KC_BSPC,
  //|------+------+------+--------+-------+------+---------|         |--------+--------+--------+---------+---------+---------+--------,
    KC_LSFT, KC_NO, KC_NO,   KC_NO,  KC_NO,   KC_NO,  KC_NO,             KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,
  //|------+------+------+---+----+-------+------+---------|         |--------+--------+--------+---------+---------+---------+--------|
             KC_NO, KC_NO,         KC_LGUI,   LOWER, KC_SPC,            KC_ENT,   RAISE, KC_RALT,              KC_NO,    KC_NO,
         //|------+------|      //|------+------+----------|         |--------+------+----------|         |---------+---------|
                                     KC_NO,   KC_NO,  KC_NO,             KC_NO,   KC_NO,   KC_NO
                                //`------------------------'         `--------------------------'
  ),

[_RAISE] = LAYOUT(
  //       |------------------------------------------------.         ,-----------------------------------------------------,
           KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_ESC,           KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|------+------+------+--------+-------+------+---------|         |--------+--------+--------+--------+--------+--------+--------,
    KC_LCTL, KC_NO, KC_NO,   KC_NO,  KC_NO,   KC_NO,  KC_NO,             KC_NO, KC_MINS,  KC_EQL, KC_LCBR, KC_RCBR, KC_PIPE,  KC_GRV,
  //|------+------+------+--------+-------+------+---------|         |--------+--------+--------+--------+--------+--------+--------,
    KC_LSFT, KC_NO, KC_NO,   KC_NO,  KC_NO,   KC_NO,  KC_NO,             KC_NO, KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_TILD,
  //|------+------+------+---+----+-------+------+---------|         |--------+--------+--------+--------+--------+--------+--------|
             KC_NO, KC_NO,         KC_LGUI,   LOWER, KC_SPC,            KC_ENT,   RAISE, KC_RALT,            KC_NO,   KC_NO,
         //|------+------|      //|------+------+----------|         |--------+------+----------|        |--------+--------|
                                     KC_NO,   KC_NO,  KC_NO,             KC_NO,   KC_NO,   KC_NO
                                //`------------------------'         `--------------------------'
  ),


[_ADJUST] = LAYOUT(
  //       |------------------------------------------------.         ,-----------------------------------------------------,
             KC_NO, KC_NO,   KC_NO,  KC_NO,   KC_NO,  KC_NO,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|------+------+------+--------+-------+------+---------|         |--------+--------+--------+--------+--------+--------+--------,
    KC_LCTL, KC_NO, KC_NO,   KC_NO,  KC_NO,   KC_NO,  KC_NO,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|------+------+------+--------+-------+------+---------|         |--------+--------+--------+--------+--------+--------+--------,
    KC_LSFT, KC_NO, KC_NO,   KC_NO,  KC_NO,   KC_NO,  KC_NO,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|------+------+------+---+----+-------+------+---------|         |--------+--------+--------+--------+--------+--------+--------|
             KC_NO, KC_NO,         KC_LGUI,   LOWER, KC_SPC,            KC_ENT,   RAISE, KC_RALT,            KC_NO,   KC_NO,
         //|------+------|      //|------+------+----------|         |--------+------+----------|        |--------+--------|
                                     KC_NO,   KC_NO,  KC_NO,             KC_NO,   KC_NO,   KC_NO
                                //`------------------------'         `--------------------------'
  )


};



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
  }
  return true;
}
