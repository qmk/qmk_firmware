#include QMK_KEYBOARD_H

enum layer_names {
    BASE,
    MDIA,
    NUMB,
    MOUS
};

#ifdef RGBLIGHT_ENABLE
#define ERGOSLAB_BRIGHTNESS 112
#define HSV_ERGOSLAB_ORANGE 28, 255, 16
#define HSV_ERGOSLAB_RED 0, 255, ERGOSLAB_BRIGHTNESS
#define HSV_ERGOSLAB_GREEN 85, 255, ERGOSLAB_BRIGHTNESS
#define HSV_ERGOSLAB_CYAN 128, 255, ERGOSLAB_BRIGHTNESS
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_ergoslab(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                           KC_Y,     KC_U,     KC_I,     KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                           KC_H,     KC_J,     KC_K,     KC_L,    KC_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                           KC_N,     KC_M,     KC_COMM,  KC_DOT,  KC_SLSH,
    KC_QUOT, KC_LALT, KC_DEL,  KC_ENT,  KC_LSFT, KC_LCTL,     MO(NUMB), KC_SPC,   KC_LEFT,  KC_DOWN,  KC_UP,   KC_RGHT,
             KC_LBRC, KC_LPRN, KC_ESC,  MO(MDIA),KC_RGUI,     KC_TAB,   TG(MOUS), KC_BSPC,  KC_RPRN,  KC_RBRC
  ),

  [MDIA] = LAYOUT_ergoslab(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                          KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,
    _______, _______, _______, _______, KC_F11,                         KC_F12,   KC_HOME,  KC_PGDN,  KC_PGUP, KC_END,
    _______, _______, _______, _______, _______,                        RGB_TOG,  _______,  _______,  _______, KC_MUTE,
    _______, QK_BOOT,   _______, _______, _______, _______,     _______,  _______,  _______,  KC_VOLD,  KC_VOLU, _______,
             _______, _______, _______, _______, _______,     _______,  _______,  _______,  _______,  _______
  ),

  [NUMB] = LAYOUT_ergoslab(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                        KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_BSLS, KC_PIPE,
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,     KC_7,     KC_8,     KC_9,    KC_0,
    KC_UNDS, KC_MINS, KC_PLUS, KC_EQL,  KC_GRV,                         KC_COLN,  KC_TILD,  _______,  _______, _______,
    _______, _______, _______, _______, _______, _______,     _______,  _______,  KC_QUOT,  KC_DQT,   _______, _______,
             _______, _______, _______, _______, _______,     _______,  _______,  _______,  _______,  _______
  ),

  [MOUS] = LAYOUT_ergoslab(
    _______, _______, KC_MS_U, _______, _______,                        _______,  _______,  KC_WH_U,  _______, _______,
    _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,                        _______,  KC_BTN3,  KC_WH_D,  _______, _______,
    _______, _______, _______, _______, _______,                        _______,  _______,  _______,  _______, _______,
    _______, _______, _______, _______, KC_ACL0,  _______,     KC_BTN2, KC_BTN1,  _______,  _______,  _______, _______,
             _______, _______, _______, _______,  _______,     _______, _______,  _______,  _______,  _______
  ),
};

#ifdef RGBLIGHT_ENABLE
layer_state_t layer_state_set_user(layer_state_t state) {
  uint8_t layer = get_highest_layer(state);
  switch (layer) {
      case BASE:
          rgblight_sethsv(HSV_ERGOSLAB_ORANGE);
        break;
      case MDIA:
          rgblight_sethsv(HSV_ERGOSLAB_RED);
        break;
      case NUMB:
          rgblight_sethsv(HSV_ERGOSLAB_GREEN);
        break;
      case MOUS:
          rgblight_sethsv(HSV_ERGOSLAB_CYAN);
        break;
      default:
        break;
    }
  return state;
};
#endif
