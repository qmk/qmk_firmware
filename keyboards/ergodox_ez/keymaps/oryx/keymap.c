#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "keymap_french.h"
#include "keymap_spanish.h"
#include "keymap_hungarian.h"
#include "keymap_swedish.h"
#include "keymap_br_abnt2.h"
#include "keymap_canadian_multilingual.h"
#include "keymap_german_ch.h"
#include "keymap_jp.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)

enum custom_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  HSV_172_255_255,
  HSV_86_255_128,
  HSV_27_255_255,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox_pretty(
          WEBUSB_PAIR,       KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_LEFT,                                        KC_RIGHT,       KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINUS,
              KC_DELETE,      KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           TG(1),                                          TG(1),          KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSLASH,
                  KC_BSPACE,      KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                                                           KC_H,           KC_J,           KC_K,           KC_L,           LT(2,KC_SCOLON),LGUI_T(KC_QUOTE),
                      KC_LSHIFT,      LCTL_T(KC_Z),   KC_X,           KC_C,           KC_V,           KC_B,           KC_HYPR,                                        KC_MEH,         KC_N,           KC_M,           KC_COMMA,       KC_DOT,         RCTL_T(KC_SLASH),KC_RSHIFT,
                          LT(1,KC_GRAVE), KC_QUOTE,       LALT(KC_LSHIFT),KC_LEFT,        KC_RIGHT,                                                                                                       KC_UP,          KC_DOWN,        KC_LBRACKET,    KC_RBRACKET,    MO(1),
                                                                                                                              LALT_T(KC_APPLICATION),KC_LGUI,        KC_LALT,        LCTL_T(KC_ESCAPE),
                                                                                                                                                                                                                                                  KC_HOME,        KC_PGUP,
                                                                                                                                                                                                                                                                                                                                      KC_SPACE,       KC_BSPACE,      KC_END,         KC_PGDOWN,      KC_TAB,         KC_ENTER
                                                                                                                                                                                                                                                                                                                                        ),
  [1] = LAYOUT_ergodox_pretty(
          KC_ESCAPE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,
              KC_TRANSPARENT, KC_EXLM,        KC_AT,          KC_LCBR,        KC_RCBR,        KC_PIPE,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_UP,          KC_7,           KC_8,           KC_9,           KC_ASTR,        KC_F12,
                  KC_TRANSPARENT, KC_HASH,        KC_DLR,         KC_LPRN,        KC_RPRN,        KC_GRAVE,                                                                       KC_DOWN,        KC_4,           KC_5,           KC_6,           KC_PLUS,        KC_TRANSPARENT,
                      KC_TRANSPARENT, KC_PERC,        KC_CIRC,        KC_LBRACKET,    KC_RBRACKET,    KC_TILD,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_AMPR,        KC_1,           KC_2,           KC_3,           KC_BSLASH,      KC_TRANSPARENT,
                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_DOT,         KC_0,           KC_EQUAL,       KC_TRANSPARENT,
                                                                                                                              RGB_MOD,        HSV_172_255_255,RGB_TOG,        RGB_SLD,
                                                                                                                                                                                                                                                  HSV_86_255_128, KC_TRANSPARENT,
                                                                                                                                                                                                                                                                                                                                      RGB_VAD,        RGB_VAI,        HSV_27_255_255, KC_TRANSPARENT, RGB_HUD,        RGB_HUI
                                                                                                                                                                                                                                                                                                                                        ),
  [2] = LAYOUT_ergodox_pretty(
          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
              KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_UP,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                  KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PLAY_PAUSE,
                      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_TRANSPARENT, KC_TRANSPARENT,
                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_BTN1,     KC_MS_BTN2,                                                                                                     KC_AUDIO_VOL_UP,KC_AUDIO_VOL_DOWN,KC_AUDIO_MUTE,  KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                              KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                                                                                                                                                  KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                                                                                                                                                                                                                                      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_WWW_BACK
                                                                                                                                                                                                                                                                                                                                        ),
};


bool suspended = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case RGB_SLD:
        if (record->event.pressed) {
                rgblight_mode(1);
              }
        return false;
      case HSV_172_255_255:
        if (record->event.pressed) {
                #ifdef RGBLIGHT_ENABLE
                  rgblight_enable();
                  rgblight_mode(1);
                  rgblight_sethsv(172,255,255);
                #endif
              }
        return false;
      case HSV_86_255_128:
        if (record->event.pressed) {
                #ifdef RGBLIGHT_ENABLE
                  rgblight_enable();
                  rgblight_mode(1);
                  rgblight_sethsv(86,255,128);
                #endif
              }
        return false;
      case HSV_27_255_255:
        if (record->event.pressed) {
                #ifdef RGBLIGHT_ENABLE
                  rgblight_enable();
                  rgblight_mode(1);
                  rgblight_sethsv(27,255,255);
                #endif
              }
        return false;
    }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {

    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
          case 1:
            ergodox_right_led_1_on();
            break;
          case 2:
            ergodox_right_led_2_on();
            break;
          case 3:
            ergodox_right_led_3_on();
            break;
          case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
          case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
          case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
          case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
          default:
            break;
        }
    return state;

};
