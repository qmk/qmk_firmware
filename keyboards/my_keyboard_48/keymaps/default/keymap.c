#include QMK_KEYBOARD_H

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3


// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QWERTY,
  LOWER,
  RAISE,
  ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
    KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   KC_Y,    KC_U,    KC_I,     KC_O,    KC_P,     KC_BSPC,  \
    KC_LCTL, KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   KC_H,    KC_J,    KC_K,     KC_L,    KC_SCLN,  KC_QUOT,  \
    KC_LALT, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,    KC_M,    KC_COMM,  KC_DOT,  KC_SLSH,  KC_ENT,   \
    KC_LGUI, KC_LALT, KC_LCTL, KC_LGUI,KC_LSFT,KC_SPC, LOWER,   RAISE,   KC_ESC,   KC_DEL,  KC_PSCR,  KC_ENT  \
  ),

  [_LOWER] = LAYOUT( \
    KC_LCTL, KC_1,    KC_2,    KC_3,    KC_4,     KC_5,    KC_6,    KC_7,     KC_8,    KC_9,      KC_0,    KC_BSLS, \
    KC_LCTL, KC_NO,   KC_NO,   KC_HOME, KC_END,   KC_NO,   KC_LEFT, KC_DOWN,  KC_UP,   KC_RIGHT,  KC_MINS, KC_EQL,\
    KC_LALT, XXXXXXX, XXXXXXX, XXXXXXX, KC_LANG2, KC_LALT, KC_RALT, KC_LANG1, KC_COMM, KC_DOT,    KC_SLSH, KC_ENT, \
    KC_LGUI, KC_LALT, KC_LCTL, KC_LGUI, KC_LSFT,  KC_SPC,  LOWER,   RAISE,    KC_ESC,  KC_DEL,    KC_PSCR, KC_ENT  \
  ),

  [_RAISE] = LAYOUT( \
    KC_TAB,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,   KC_PERC, KC_CIRC, KC_AMPR,  KC_ASTR, KC_LPRN,   KC_RPRN, KC_BSPC, \
    KC_LCTL, KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_GRV,  KC_LCBR,  KC_RCBR, KC_MINS,   KC_EQL,  KC_PIPE, \
    KC_LALT, KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_TILD, KC_LBRC,  KC_RBRC, KC_UNDS,   KC_PLUS, KC_BSLS,\
    KC_LGUI, KC_LALT, KC_LCTL, KC_LGUI, KC_LSFT,  KC_SPC,  LOWER,   RAISE,    KC_ESC,  KC_DEL,    KC_PSCR, KC_ENT  \
  ),

  [_ADJUST] = LAYOUT( \
    F(1),    F(2),    F(3),     F(4),    F(5),    F(6),    F(7),    F(8),    F(9),    F(10),   F(11),   F(12),  \
    _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, BL_TOGG, BL_INC, BL_DEC, KC__MUTE, KC__VOLDOWN,  KC__VOLUP, \
    _______, RGB_MODE_FORWARD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, RGB_MODE_PLAIN, RGB_MODE_BREATHE, RGB_MODE_RAINBOW, RGB_MODE_SWIRL, RGB_MODE_SNAKE,  \
    KC_LGUI, KC_LALT, KC_LCTL, KC_LGUI, KC_LSFT,  KC_SPC,  RAISE,   LOWER,    KC_ESC,  KC_DEL,    KC_PSCR, KC_ENT  \
  )


};


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}
// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
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

void matrix_scan_user(void) {
  // uint8_t layer = biton32(layer_state);

  //   // INSERT CODE HERE: turn off all leds

  //   switch (layer) {
  //       case 0:
  //           // rgblight_enable();
  //           // rgblight_setrgb(0, 0, 255);
  //           // rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
  //           // rgblight_mode_noeeprom(RGBLIGHT_MODE_RGB_TEST);
  //           break;
  //       // case YOUR_LAYER_2:
  //       //     // INSERT CODE HERE: turn on leds that correspond to YOUR_LAYER_2
  //       //     break;
  //       // add case for each layer
  //   }
}

void led_set_user(uint8_t usb_led) {

}



