#include QMK_KEYBOARD_H

//#include "v1.h"

//Following line allows macro to read current RGB settings

rgblight_config_t RGB_current_config;

#define KC_KANJI KC_GRV


enum Layer
{
  _QWERTY,
  _DIA,
  _YOU,
  _CHIKA,
  _ZURA,
  _RUBY,
  _YOHANE,
  _RIKO,
  _MARI,
  _KANAN,
  _RUBY_SUB1,
  _RUBY_SUB2,
  _RUBY_SUB3,
  _SCHOOL_IDOL_FESTIVAL
};

#define SEND_DIA 100
#define SEND_YOU 101
#define SEND_CHIKA 102
#define SEND_ZURA 103
#define SEND_RUBY 104
#define SEND_YOHANE 105
#define SEND_RIKO 106
#define SEND_MARI 107
#define SEND_KANAN 108


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  DIA,
  YOU,
  CHIKA,
  ZURA,
  RUBY,
  RUBY_SUB1,
  RUBY_SUB2,
  RUBY_SUB3,
  YOHANE,
  RIKO,
  MARI,
  KANAN,
  TO_SCHOOL_IDOL_FESTIVAL,
  RETURN_SCHOOL_IDOL_FESTIVAL
};


int long_tap_timer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    DIA, YOU, CHIKA, ZURA, RUBY, YOHANE, RIKO, MARI, KANAN
  ),
  [_DIA] = LAYOUT(
    DIA, KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_LSFT
  ),

  [_YOU] = LAYOUT(
    KC_H, YOU, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_LSFT
  ),

  [_CHIKA] = LAYOUT(
    KC_O, KC_P, CHIKA, KC_Q, KC_R, KC_S, KC_T, KC_U, KC_LSFT
  ),

  [_ZURA] = LAYOUT(
    KC_V, KC_W, KC_X, ZURA, KC_Y, KC_Z, KC_M, KC_N, KC_LSFT
  ),

  //推しをたくさん押せるようにルビーちゃんには複数のレイヤー設定
  [_RUBY] = LAYOUT(
    KC_CIRC, KC_LPRN, KC_QUOT, RUBY_SUB1, RUBY, RUBY_SUB2, KC_LCBR, KC_EXLM, KC_LSFT
  ),
  [_RUBY_SUB1] = LAYOUT(
    KC_RCBR, KC_AT, KC_PIPE, RUBY_SUB1, RUBY, RUBY_SUB2, KC_HASH, KC_EQL, KC_LSFT
  ),
  [_RUBY_SUB2] = LAYOUT(
    KC_TILD, KC_DLR, KC_LBRC, RUBY_SUB1, RUBY, RUBY_SUB2, KC_PERC, KC_RBRC, KC_LSFT
  ),
  [_RUBY_SUB3] = LAYOUT(
    TO_SCHOOL_IDOL_FESTIVAL, KC_DLR, KC_LBRC, RUBY_SUB1, RUBY, RUBY_SUB2, KC_PERC, KC_RBRC, RETURN_SCHOOL_IDOL_FESTIVAL
  ),

  [_YOHANE] = LAYOUT(
    KC_0, KC_1, KC_2, KC_3, KC_4, YOHANE, KC_5, KC_6, KC_LSFT
  ),

  [_RIKO] = LAYOUT(
    KC_7, KC_8, KC_9, KC_PLUS, KC_MINS, KC_ASTR, RIKO, KC_SLSH, KC_LSFT
  ),

  [_MARI] = LAYOUT(
    KC_TAB, KC_DEL, KC_COMM, KC_SPC, KC_ENT, KC_BSPC, KC_DOT, MARI, KC_LSFT
  ),

  [_KANAN] = LAYOUT(
    KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_ENT, KC_BSPC, KC_AMPR, KC_KANJI, KANAN
  ),
  [_SCHOOL_IDOL_FESTIVAL] = LAYOUT(
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9
  ),
};

void check_tap_and_send_key(int MEMBER) {
  if (long_tap_timer < 500) {
    switch (MEMBER) {
      case SEND_DIA:
        SEND_STRING("KUROSAWA DIA");
      break;
      case SEND_YOU:
        SEND_STRING("WATANABE YOU");
      break;
      case SEND_CHIKA:
        SEND_STRING("TAKAMI CHIKA");
      break;
      case SEND_ZURA:
        SEND_STRING("KUNIKIDA HANAMARU");
      break;
      case SEND_RUBY:
        SEND_STRING("KUROSAWA RUBY");
      break;
      case SEND_YOHANE:
        SEND_STRING("TSUSHIMA YOSHIKO");
      break;
      case SEND_RIKO:
        SEND_STRING("SAKURAUCHI RIKO");
      break;
      case SEND_MARI:
        SEND_STRING("OHARA MARI");
      break;
      case SEND_KANAN:
        SEND_STRING("MATSUURA KANAN");
      break;
      }
  }
  long_tap_timer = 0;
}

int aqours_color_h[] = { 26, 340, 150,   0, 199, 220, 53, 265, 322};
int aqours_color_s[] = {255, 165, 255, 255, 255, 350, 255, 255, 255};
int aqours_color_v[] = {255, 255, 255, 255, 255, 255, 200, 255, 255};

void LED_default_set(void) {

  sethsv(aqours_color_h[2], aqours_color_s[2], aqours_color_v[2], (rgb_led_t *)&led[0]);
  sethsv(aqours_color_h[7], aqours_color_s[7], aqours_color_v[7], (rgb_led_t *)&led[1]);
  sethsv(aqours_color_h[1], aqours_color_s[1], aqours_color_v[1], (rgb_led_t *)&led[2]);
  sethsv(aqours_color_h[5], aqours_color_s[5], aqours_color_v[5], (rgb_led_t *)&led[3]);
  sethsv(aqours_color_h[8], aqours_color_s[8], aqours_color_v[8], (rgb_led_t *)&led[4]);
  sethsv(aqours_color_h[6], aqours_color_s[6], aqours_color_v[6], (rgb_led_t *)&led[5]);
  sethsv(aqours_color_h[0], aqours_color_s[0], aqours_color_v[0], (rgb_led_t *)&led[6]);
  sethsv(aqours_color_h[4], aqours_color_s[4], aqours_color_v[4], (rgb_led_t *)&led[7]);
  sethsv(aqours_color_h[3], aqours_color_s[3], aqours_color_v[3], (rgb_led_t *)&led[8]);

  rgblight_set();

}


void LED_layer_set(int aqours_index) {
  for (int c = 0; c < 9; c++) {
    sethsv(aqours_color_h[aqours_index], aqours_color_s[aqours_index], aqours_color_v[aqours_index], (rgb_led_t *)&led[c]);
  }
  rgblight_set();
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {

    case DIA:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_DIA);
        LED_layer_set(3);
      } else {
        check_tap_and_send_key(SEND_DIA);
        layer_off(_DIA);
        LED_default_set();
      }
      break;

    case YOU:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_YOU);
        LED_layer_set(4);
      } else {
        check_tap_and_send_key(SEND_YOU);
        layer_off(_YOU);
        LED_default_set();
      }
      break;

    case CHIKA:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_CHIKA);
        LED_layer_set(0);
      } else {
        check_tap_and_send_key(SEND_CHIKA);
        layer_off(_CHIKA);
        LED_default_set();
      }
      break;

    case ZURA:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_ZURA);
        LED_layer_set(6);
      } else {
        check_tap_and_send_key(SEND_ZURA);
        layer_off(_ZURA);
        LED_default_set();
      }
      break;

    case RUBY:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_RUBY);
        LED_layer_set(8);
      } else {
        check_tap_and_send_key(SEND_RUBY);
        layer_off(_RUBY);
        LED_default_set();
      }
      break;
    case RUBY_SUB1:
      if (record->event.pressed) {
        layer_on(_RUBY_SUB1);
        if (IS_LAYER_ON(_RUBY_SUB1) && IS_LAYER_ON(_RUBY_SUB2)) {
          layer_on(_RUBY_SUB3);
        } else {
          layer_off(_RUBY_SUB3);
        }
      } else {
        layer_off(_RUBY_SUB1);
      }
      break;
    case RUBY_SUB2:
      if (record->event.pressed) {
        layer_on(_RUBY_SUB2);
        if (IS_LAYER_ON(_RUBY_SUB1) && IS_LAYER_ON(_RUBY_SUB2)) {
          layer_on(_RUBY_SUB3);
        } else {
          layer_off(_RUBY_SUB3);
        }
      } else {
        layer_off(_RUBY_SUB2);
      }
      break;

    case YOHANE:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_YOHANE);
        LED_layer_set(5);
      } else {
        check_tap_and_send_key(SEND_YOHANE);
        layer_off(_YOHANE);
        LED_default_set();
      }
      break;

    case RIKO:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_RIKO);
        LED_layer_set(1);
      } else {
        check_tap_and_send_key(SEND_RIKO);
        layer_off(_RIKO);
        LED_default_set();
      }
      break;

    case MARI:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_MARI);
        LED_layer_set(7);
      } else {
        check_tap_and_send_key(SEND_MARI);
        layer_off(_MARI);
        LED_default_set();
      }
      break;

    case KANAN:
      if (record->event.pressed) {
        long_tap_timer = 1;
        layer_on(_KANAN);
        LED_layer_set(2);
      } else {
        check_tap_and_send_key(SEND_KANAN);
        layer_off(_KANAN);
        LED_default_set();
      }
      break;

    case TO_SCHOOL_IDOL_FESTIVAL:
      if (record->event.pressed) {
        LED_default_set();
        layer_on(_SCHOOL_IDOL_FESTIVAL);
      }
      break;
    case RETURN_SCHOOL_IDOL_FESTIVAL:
      if (record->event.pressed) {
        layer_off(_SCHOOL_IDOL_FESTIVAL);
      }
      break;
  }

  return true;
}


void matrix_scan_user(void) {

  if (long_tap_timer > 0) {
    long_tap_timer++;
  }
}
