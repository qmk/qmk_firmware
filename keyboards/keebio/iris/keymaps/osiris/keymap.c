#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum layer_names {
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE
};

#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST  QK_BOOT
#define KC_BL_S BL_STEP

// left shift as a left key too - makes perfect sense
#define KC_LESF LSFT_T(KC_LEFT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     QK_GESC, KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_BSLS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     KC_LCTL, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     KC_LESF, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,KC_LBRC,     KC_RBRC, KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_RGHT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       KC_LGUI,KC_LOWR,KC_ENT ,         KC_SPC ,KC_RASE,KC_RALT
  //                  `----+----+----'        `----+----+----'
  ),

    [_COLEMAK] = LAYOUT(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     QK_GESC, KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     KC_TAB , KC_Q  , KC_W  , KC_F  , KC_P  , KC_G  ,                KC_J  , KC_L  , KC_U  , KC_Y  ,KC_SCLN,KC_BSLS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     KC_LCTL, KC_A  , KC_R  , KC_S  , KC_T  , KC_D  ,                KC_H  , KC_N  , KC_E  , KC_I  , KC_O  ,KC_QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     KC_LESF, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,KC_LBRC,     KC_RBRC, KC_K  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_RGHT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       KC_LGUI,KC_LOWR,KC_ENT ,         KC_SPC ,KC_RASE,KC_RALT
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = LAYOUT(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     KC_GRV ,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,               KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     _______,_______,_______,_______,_______,_______,               _______,_______,KC_BTN1,_______,_______,_______,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     _______,_______,_______,_______,_______,_______,               KC_MS_L,KC_MS_D,KC_MS_U,KC_MS_R,_______,_______,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     _______,_______,_______,_______,_______, KC_UP ,_______,     _______,KC_DOWN,_______,_______,_______,_______,_______,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       _______,_______,_______,         _______,_______,   _______
  //                  `----+----+----'        `----+----+----'

),
  [_RAISE] = LAYOUT(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                KC_F6 , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     _______,_______,KC_VOLU,_______,_______,KC_LBRC,               KC_RBRC,KC_UNDS,KC_PLUS,_______,_______,KC_MUTE,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     _______,KC_MPLY,KC_VOLD,KC_MNXT,_______,KC_LPRN,               KC_RPRN,KC_MINS,KC_EQL ,_______,_______,_______,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     _______,_______,_______,_______,_______,_______,_______,     _______,_______,_______,_______,_______,_______,_______,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       _______,_______,_______,         _______,_______, _______
  //                  `----+----+----'        `----+----+----'
  ),

  [_ADJUST] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                          ,-------+-------+-------+-------+-------+-------.
     _______,_______,_______,_______,_______, QWERTY,                           COLEMAK,_______,_______,_______,_______,_______,
  //|-------+-------+-------+-------+-------+-------|                          |-------+-------+-------+-------+-------+-------|
     _______,RGB_TOG,RGB_MOD,RGB_HUI,RGB_SAI,RGB_VAI,                           _______,_______,_______,_______,_______,_______,
  //|-------+-------+-------+-------+-------+-------|                          |-------+-------+-------+-------+-------+-------|
     QK_BOOT,DB_TOGG,_______,RGB_HUD,RGB_SAD,RGB_VAD,                           _______,_______,_______,_______,_______,_______,
  //|-------+-------+-------+-------+-------+-------+-------.        ,-------|-------+-------+-------+-------+-------+-------|
     BL_STEP,_______,_______,_______,_______,_______,_______,         _______,_______,_______,_______,_______,_______,_______,
  //`--------+-------+-------+----+--+-------+-------+-------/        \-------+-------+-------+---+---+-------+-------+-------'
                                    _______,_______,_______,             _______,_______,_______
  //                               `-------+-------+-------'            `-------+-------+-------'
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
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
  }
  return true;
}
