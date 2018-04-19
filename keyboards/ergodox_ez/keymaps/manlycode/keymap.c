#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"


#include "keymap_german.h"

#include "keymap_nordic.h"



enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
  RGB_0000FF
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = KEYMAP(
      // left hand
      KC_GRAVE,       KC_1,           KC_2,            KC_3,      KC_4,      KC_5,            OSL(1),
      KC_BSLASH,      KC_Q,           KC_W,            KC_E,      KC_R,      KC_T,            TG(1),
      KC_TAB,         KC_A,           KC_S,            KC_D,      KC_F,      KC_G,
      KC_LSHIFT,      KC_Z,           KC_X,            KC_C,      KC_V,      KC_B,            ALL_T(KC_NO),
      KC_TRANSPARENT, KC_TRANSPARENT, LALT(KC_LSHIFT), KC_LEFT,   KC_LGUI,
      KC_UP,          KC_DOWN,
      KC_LALT,
      KC_BSPACE,      KC_ESCAPE,      KC_LCTL,
      
      // right hand
      OSL(2),         KC_6,           KC_7,            KC_8,      KC_9,      KC_0,            KC_MINUS,
      TG(2),          KC_Y,           KC_U,            KC_I,      KC_O,      KC_P,            KC_EQUAL,
      KC_H,           KC_J,           KC_K,            KC_L,      KC_SCOLON, KC_QUOTE,
      MEH_T(KC_NO),   KC_N,           KC_M,            KC_COMMA,  KC_DOT,    CTL_T(KC_SLASH), KC_LSHIFT,
      KC_LGUI,        KC_LBRACKET,    KC_RBRACKET,     KC_BSLASH, MO(1),
      KC_LEFT,        KC_RIGHT,       KC_LALT,         KC_LCTL,   KC_ENTER,  KC_SPACE
      ),

  [1] = KEYMAP(
      // left hand
      KC_ESCAPE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,    KC_TRANSPARENT,
      KC_TRANSPARENT, KC_EXLM,        KC_AT,          KC_LCBR,        KC_RCBR,        KC_PIPE,  KC_TRANSPARENT,
      KC_TRANSPARENT, KC_HASH,        KC_DLR,         KC_LPRN,        KC_RPRN,        KC_GRAVE,
      KC_TRANSPARENT, KC_PERC,        KC_CIRC,        KC_LBRACKET,    KC_RBRACKET,    KC_TILD,  KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
      KC_F14,         KC_F15,
      KC_TRANSPARENT,
      KC_BSPACE,      KC_ESCAPE,      KC_TRANSPARENT,
      // right hand
      KC_TRANSPARENT,    KC_F6,           KC_F7,            KC_F8,    KC_F9,          KC_F10,         KC_F11,
      KC_TRANSPARENT,    KC_TRANSPARENT,  LGUI(LSFT(KC_L)), KC_8,     KC_9,           KC_ASTR,        KC_F12,
      KC_TRANSPARENT,    KC_DOWN,         KC_UP,            KC_LEFT,  KC_RIGHT,       KC_TRANSPARENT,
      KC_TRANSPARENT,    KC_AMPR,         KC_1,             KC_2,     KC_3,           KC_BSLASH,      KC_TRANSPARENT,
      KC_TRANSPARENT,    KC_DOT,          KC_0,             KC_EQUAL, KC_TRANSPARENT,
      KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP,
      KC_TRANSPARENT,    KC_TRANSPARENT,  KC_TRANSPARENT,   KC_TRANSPARENT
    ),

  [2] = KEYMAP(
      // left hand
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_UP,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_BTN1,     KC_MS_BTN2,
      KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
      
      // right hand
      KC_TRANSPARENT,  KC_TRANSPARENT,    KC_TRANSPARENT, KC_TRANSPARENT,      KC_TRANSPARENT,      KC_TRANSPARENT,      KC_TRANSPARENT,
      KC_TRANSPARENT,  KC_TRANSPARENT,    KC_TRANSPARENT, KC_TRANSPARENT,      KC_TRANSPARENT,      KC_TRANSPARENT,      KC_TRANSPARENT,
      KC_TRANSPARENT,  KC_TRANSPARENT,    KC_TRANSPARENT, KC_TRANSPARENT,      KC_TRANSPARENT,      KC_MEDIA_PLAY_PAUSE,
      KC_TRANSPARENT,  KC_TRANSPARENT,    KC_TRANSPARENT, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_TRANSPARENT,      KC_TRANSPARENT,
      KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE,  KC_TRANSPARENT,      KC_TRANSPARENT,
      KC_TRANSPARENT,  KC_TRANSPARENT,
      KC_TRANSPARENT,
      KC_TRANSPARENT,  KC_TRANSPARENT,    KC_WWW_BACK),

};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
      break;
    
    case RGB_0000FF:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
          rgblight_setrgb(0x00,0x00,0xff);
        #endif
      }
      return false;
      break;
    
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #endif
        break;
      case 1:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }
    return state;

};
