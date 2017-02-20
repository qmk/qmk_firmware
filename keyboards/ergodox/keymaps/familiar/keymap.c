#include "ergodox.h"
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
  
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = KEYMAP(KC_ESCAPE,KC_1,KC_2,KC_3,KC_4,KC_5,KC_MINUS,KC_DELETE,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_HOME,KC_TAB,KC_A,KC_S,KC_D,KC_F,KC_G,KC_LSPO,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_END,CTL_T(KC_LGUI),KC_APPLICATION,KC_GRAVE,KC_QUOTE,KC_BSLASH,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,ALT_T(KC_SPACE),MO(1),KC_RALT,KC_KP_PLUS,KC_6,KC_7,KC_8,KC_9,KC_0,KC_PSCREEN,KC_PGUP,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_BSPACE,KC_H,KC_J,KC_K,KC_L,KC_SCOLON,KC_ENTER,KC_PGDOWN,KC_N,KC_M,KC_COMMA,KC_DOT,KC_KP_SLASH,KC_RSPC,KC_LBRACKET,KC_RBRACKET,KC_TRANSPARENT,KC_APPLICATION,CTL_T(KC_RGUI),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_RALT,MO(1),ALT_T(KC_SPACE)),

  [1] = KEYMAP(M(0),KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F11,KC_PAUSE,KC_TRANSPARENT,KC_TRANSPARENT,KC_UP,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_LEFT,KC_DOWN,KC_RIGHT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MEDIA_PREV_TRACK,KC_MEDIA_STOP,KC_MEDIA_PLAY_PAUSE,KC_MEDIA_NEXT_TRACK,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_F12,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_INSERT,KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

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
    
  }
  return true;
}

void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

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

};
