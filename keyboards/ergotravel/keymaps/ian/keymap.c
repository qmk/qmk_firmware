#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum custom_layers {
    _COLEMAK,
    _ADJUST,
    _RAISE,
    _LOWER,
    _QWERTY
};

#define BASELYR TO(_COLEMAK) // base layer
#define LOWER MO(_LOWER) // momentary lower layer
#define RAISE MO(_RAISE) // momentary raise layer
#define ADJUST MO(_ADJUST) // momentary adjust layer
#define QWERTY TG(_QWERTY)
#define LLOWER TG(_LOWER) // lock for lower layer
#define LRAISE TG(_RAISE) // lock for raise layer
#define LHALF LALT(LGUI(KC_LEFT)) // spec left half screen
#define TLHALF LCTL(LGUI(KC_LEFT)) // spec top left half
#define BLHALF LCTL(LSFT(LGUI(KC_LEFT))) // spec bottom left half
#define RHALF LALT(LGUI(KC_RIGHT)) // spec right half screen
#define TRHALF LCTL(LGUI(KC_RIGHT)) // spec top right half
#define BRHALF LCTL(LSFT(LGUI(KC_RIGHT))) // spec bottom right half
#define SAFBCK LGUI(KC_LBRC) // safari back
#define SAFFWD LGUI(KC_RBRC) // safari forward
#define CENTER LALT(LGUI(KC_C)) // spec center
#define FULL LALT(LGUI(KC_F)) // spec full screen

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAK] = LAYOUT(
    //,------+-------+-------+-------+-------+-------+-------.     ,-------+-------+-------+-------+-------+-------+-------.
      KC_ESC ,  KC_Q ,  KC_W ,  KC_F ,  KC_P ,  KC_G ,KC_LCBR,      KC_RCBR,  KC_J  ,  KC_L ,  KC_U ,  KC_Y ,KC_SCLN,KC_BSPC,
    //,------+-------+-------+-------+-------+-------+-------.     ,-------+-------+-------+-------+-------+-------+-------.
      KC_TAB ,  KC_A ,  KC_R ,  KC_S ,  KC_T ,  KC_D ,KC_LPRN,      KC_RPRN, KC_H  ,  KC_N ,  KC_E ,  KC_I , KC_O  ,KC_QUOT,
    //,------+-------+-------+-------+-------+-------+-------.     ,-------+-------+-------+-------+-------+-------+-------.
      KC_BSLS, KC_Z  ,  KC_X ,  KC_C ,  KC_V ,  KC_B ,KC_LBRC ,      KC_RBRC ,  KC_K ,  KC_M ,KC_COMM, KC_DOT,KC_SLSH,KC_ENT ,
    //,------+-------+-------+-------+-------+-------+-------.     .-------+-------+-------+-------+-------+-------+-------.
      ADJUST ,KC_LCTL,KC_LALT,KC_LGUI, LOWER, KC_SPC,                       KC_LSFT, RAISE, KC_LEFT, KC_DOWN, KC_UP,KC_RGHT
    //,------+-------+-------+-------+-------/-------/                     \-------\-------+-------+-------+-------+-------'
  ),

  [_ADJUST] = LAYOUT(
    //,------+-------+-------+-------+-------+-------+-------.     ,-------+-------+-------+-------+-------+-------+-------.
      BASELYR,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,      XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, RESET ,
    //,------+-------+-------+-------+-------+-------+-------.     ,-------+-------+-------+-------+-------+-------+-------.
      XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,      XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    //,------+-------+-------+-------+-------+-------+-------.     ,-------+-------+-------+-------+-------+-------+-------.
      XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,      XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    //|------+-------+-------+-------+-------+-------+-------.     .-------+-------+-------+-------+-------+-------+-------.
      _______,KC_F10 ,KC_F11 ,KC_F12 ,LLOWER ,XXXXXXX,                      XXXXXXX,LRAISE ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX
    //`------+-------+-------+-------+-------/-------/                      \------\-------+-------+-------+-------+-------'
  ),

  [_RAISE] = LAYOUT(
    //,------+-------+-------+-------+-------+-------+-------.     ,-------+-------+-------+-------+-------+-------+-------.
      BASELYR,KC_EXLM, KC_AT, KC_HASH, KC_DLR,KC_LCBR,XXXXXXX,      XXXXXXX, KC_RCBR, TLHALF,  CENTER,  TRHALF, XXXXXXX, KC_BSPC,
    //,------+-------+-------+-------+-------+-------+-------.     ,-------+-------+-------+-------+-------+-------+-------.
      KC_TILD,KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,XXXXXXX,      XXXXXXX, KC_RPRN, LHALF,   FULL,    RHALF,  XXXXXXX, KC_VOLU,
    //,------+-------+-------+-------+-------+-------+-------.     ,-------+-------+-------+-------+-------+-------+-------.
      KC_GRV, KC_MINS,KC_PLUS,KC_UNDS,KC_EQL, KC_LBRC,XXXXXXX,      XXXXXXX, KC_RBRC, BLHALF,  XXXXXXX, BRHALF, XXXXXXX, KC_VOLD,
    //|-------+-------+-------+-------+-------+-------+-------.    .-------+-------+-------+-------+-------+-------+-------|
       XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_TRNS,KC_SPC,                     KC_LSFT, KC_TRNS, XXXXXXX, KC_F14, KC_F15,  KC_MUTE
    //`-------+-------+-------+-------+-------/-------/                     \------\-------+-------+-------+-------+-------'
  ),

  [_LOWER] = LAYOUT(
    //,------+-------+-------+-------+-------+-------+-------.     ,-------+-------+-------+-------+-------+-------+-------.
      BASELYR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LCBR,XXXXXXX,      XXXXXXX, KC_RCBR, KC_7,  KC_8, KC_9,   KC_MINS,  KC_BSPC,
    //,------+-------+-------+-------+-------+-------+-------.     ,-------+-------+-------+-------+-------+-------+-------.
      XXXXXXX, XXXXXXX, SAFBCK,  XXXXXXX, SAFFWD,  KC_LPRN,XXXXXXX,      XXXXXXX, KC_RPRN, KC_4,  KC_5, KC_6,   KC_PLUS,  XXXXXXX,
    //,------+-------+-------+-------+-------+-------+-------.     ,-------+-------+-------+-------+-------+-------+-------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC,XXXXXXX,      XXXXXXX, KC_RBRC, KC_1,  KC_2, KC_3,   KC_ASTR,  KC_ENT,
    //|-------+-------+-------+-------+-------+-------+-------.    .-------+-------+-------+-------+-------+-------+-------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS, KC_SPC,                  KC_LSFT, KC_0,  KC_0, KC_DOT, KC_SLASH, XXXXXXX 
    //`-------+-------+-------+-------+-------/-------/                     \------\-------+-------+-------+-------+-------'
  )

};

   

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    
  }
  return true;
}

