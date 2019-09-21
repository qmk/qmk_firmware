#include "ergodox_ez.h"
#include "version.h"


#include "keymap_german.h"

#include "keymap_nordic.h"


 enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
 };

#define MACOS_ALPHA  0
#define MACOS_SPECIAL  1
#define MACOS_UMLAUT  2
#define MACOS_EMPTY1  3
#define MACOS_EMPTY2 4

#define WIN_ALPHA   5
#define WIN_SPECIAL  6
#define WIN_UMLAUT  7
#define WIN_EMPTY1  8
#define WIN_EMPTY2  9

#define ALL_MOUSE  10

#define RGBLIGHT_COLOR_LAYER_WIN 0xff,0x00,0x00
#define RGBLIGHT_COLOR_LAYER_MAC 0x00,0xff,0x00


#define EMPTY_LAYER LAYOUT_ergodox(KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO)

// MacOS, German locale
#define MAC_DE_LEFT_CURLY_BRACE  DE_LBRC
#define MAC_DE_RIGHT_CURLY_BRACE  DE_RBRC

#define MAC_DE_LEFT_SQUARE_BRACE  LALT(KC_5)
#define MAC_DE_RIGHT_SQUARE_BRACE LALT(KC_6)

#define MAC_DE_BACKSLASH LSFT(LALT(KC_7))
#define MAC_DE_SLASH LSFT(KC_7)
#define MAC_DE_PIPE LALT(KC_7)

#define MAC_DE_AT LALT(KC_L)
#define MAC_DE_TILDE LALT(KC_N)
#define MAC_DE_GRAVE KC_EQUAL
#define WIN_DE_GRAVE KC_EQUAL
#define WIN_DE_EQUAL LSFT(KC_0)

#define MAC_DE_QUESTION LSFT(NO_QUES)
#define WIN_DE_QUESTION LSFT(NO_QUES)

bool is_mac_layer(uint8_t layer){
  return (layer >= MACOS_ALPHA) && (layer <= MACOS_EMPTY2);
}

bool is_win_layer(uint8_t layer){
  return (layer >= WIN_ALPHA) && (layer <= WIN_EMPTY2);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [MACOS_ALPHA] = LAYOUT_ergodox(
    // Left
    KC_ESCAPE,KC_1,KC_2,KC_3,KC_4,KC_5,MAC_DE_LEFT_SQUARE_BRACE, /* 7 */
    KC_TAB,KC_Q,KC_W,KC_E,KC_R,KC_T,MAC_DE_LEFT_CURLY_BRACE,    /* 7 */
    KC_LCTRL,KC_A,KC_S,KC_D,KC_F,KC_G,           /* 6 */
    KC_LSHIFT,DE_Y,KC_X,KC_C,KC_V,KC_B,NO_LPRN,  /* 7 */
    MO(MACOS_SPECIAL),KC_LALT,KC_LGUI,KC_LEFT,KC_RIGHT, /* 5 */
    // BLOCK
    KC_DELETE,KC_LCTL,KC_HOME,KC_BSPACE,KC_SPACE,KC_END, // 6

    // Right
    MAC_DE_RIGHT_SQUARE_BRACE,KC_6,KC_7,KC_8,KC_9,KC_0,DE_LESS,
    MAC_DE_RIGHT_CURLY_BRACE,DE_Z,KC_U,KC_I,KC_O,KC_P,MAC_DE_SLASH,
    KC_H,KC_J,KC_K,KC_L,LT(ALL_MOUSE,MAC_DE_QUESTION),OSL(MACOS_UMLAUT),NO_RPRN,
    KC_N,KC_M,KC_COMMA,KC_DOT,NO_MINS,KC_RSHIFT,
    KC_UP,KC_DOWN,KC_NO,KC_NONUS_HASH,KC_RALT,
    // BLOCK
    KC_NO,KC_NO,KC_PGUP,KC_PGDOWN,KC_ENTER,KC_SPACE
  ),

  [MACOS_SPECIAL] =  LAYOUT_ergodox(
    // Left
    KC_ESCAPE,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_NO,
    KC_NO,MAC_DE_AT,TO(WIN_ALPHA),KC_NO,KC_NO,KC_NO,KC_NO,
    KC_LCTRL,KC_HASH,KC_DLR,KC_LPRN,KC_RPRN,KC_GRAVE,
    KC_LSHIFT,KC_PERC,KC_CIRC,KC_LBRACKET,KC_RBRACKET,KC_TILD,KC_NO,
    KC_NO,KC_LALT,KC_NO,KC_NO,KC_NO,
    // BLOCK
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,

    // Right
    KC_NO,KC_F6,KC_F7,KC_F8,KC_F9,KC_KP_EQUAL,KC_KP_ASTERISK,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NONUS_HASH,MAC_DE_SLASH,
    KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,MAC_DE_PIPE,KC_KP_PLUS,
    KC_NO,TO(MACOS_ALPHA),KC_NO,KC_NO,KC_NO,MAC_DE_BACKSLASH,KC_KP_MINUS,
    KC_NO,KC_NO,KC_NO,MAC_DE_TILDE,MAC_DE_GRAVE,
    // BLOCK
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO
  ),


  [MACOS_UMLAUT] = LAYOUT_ergodox(
    // Left
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO, // 7
    KC_NO,MAC_DE_AT,KC_NO,DE_EURO,KC_NO,KC_NO,KC_NO,  // 7
    KC_LCTRL,DE_AE,DE_SS,KC_NO,KC_NO,KC_NO, // 6
    KC_LSHIFT,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO, // 7
    KC_NO,KC_LALT,KC_NO,KC_NO,KC_NO, // 5
    // BLOCK
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO, // 6

    // Right
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO, // 7
    KC_NO,DE_Z,DE_UE,KC_NO,DE_OE,KC_NO,KC_NO, // 7
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO, // 6
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO, // 7
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO, // 5
    // BLOCK
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO // 6
  ),

  [MACOS_EMPTY1] = EMPTY_LAYER,
  [MACOS_EMPTY2] = EMPTY_LAYER,


//
//
// Windows
//
//

    [WIN_ALPHA] = LAYOUT_ergodox(
      // Left
      KC_ESCAPE,KC_1,KC_2,KC_3,KC_4,KC_5,DE_LBRC, /* 7 */
      KC_TAB,KC_Q,KC_W,KC_E,KC_R,KC_T,DE_LCBR,    /* 7 */
      KC_LCTRL,KC_A,KC_S,KC_D,KC_F,KC_G,           /* 6 */
      KC_LSHIFT,DE_Y,KC_X,KC_C,KC_V,KC_B,NO_LPRN,  /* 7 */
      MO(WIN_SPECIAL),KC_LALT,KC_LGUI,KC_LEFT,KC_RIGHT, /* 5 */
      // BLOCK
      KC_DELETE,KC_LCTL,KC_HOME,KC_BSPACE,KC_SPACE,KC_END,

      // Right
      DE_RBRC,KC_6,KC_7,KC_8,KC_9,KC_0,DE_LESS,
      DE_RCBR,DE_Z,KC_U,KC_I,KC_O,KC_P,NO_SLSH,
      KC_H,KC_J,KC_K,KC_L,LT(ALL_MOUSE,WIN_DE_QUESTION),OSL(WIN_UMLAUT),NO_RPRN,
      KC_N,KC_M,KC_COMMA,KC_DOT,NO_MINS,KC_RSHIFT,
      KC_UP,KC_DOWN,KC_NO,KC_NONUS_HASH,KC_RALT,
      // BLOCK
      KC_LALT,CTL_T(KC_ESCAPE),KC_PGUP,KC_PGDOWN,KC_ENTER,KC_SPACE
    ),

    [WIN_SPECIAL] =  LAYOUT_ergodox(
      // Left
      KC_ESCAPE,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_NO,
      KC_NO,DE_AT,TO(WIN_ALPHA),KC_NO,KC_NO,KC_NO,KC_NO,
      KC_LCTRL,KC_HASH,KC_DLR,KC_LPRN,KC_RPRN,KC_GRAVE,
      KC_LSHIFT,KC_PERC,KC_CIRC,KC_LBRACKET,KC_RBRACKET,KC_TILD,KC_NO,
      KC_NO,KC_LALT,KC_NO,KC_NO,KC_NO,
      // BLOCK
      KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,

      // Right
      KC_NO,KC_F6,KC_F7,KC_F8,KC_F9,WIN_DE_EQUAL,KC_KP_ASTERISK,
      KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NONUS_HASH,NO_SLSH,
      KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,MAC_DE_PIPE,KC_KP_PLUS,
      KC_NO,KC_NO,TO(MACOS_ALPHA),KC_NO,KC_NO,KC_NONUS_BSLASH,KC_KP_MINUS,
      KC_NO,KC_NO,KC_NO,DE_TILD,WIN_DE_GRAVE,
      // BLOCK
      KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO
    ),


    [WIN_UMLAUT] = LAYOUT_ergodox(
      // Left
      KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO, // 7
      KC_NO,DE_AT,KC_NO,DE_EURO,KC_NO,KC_NO,KC_NO, // 7
      KC_LCTRL,DE_AE,DE_SS,KC_NO,KC_NO,KC_NO, // 6
      KC_LSHIFT,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO, // 7
      KC_NO,KC_LALT,KC_NO,KC_NO,KC_NO, // 5
      // BLOCK
      KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO, // 6

      // Right
      KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO, // 7
      KC_NO,DE_Z,DE_UE,KC_NO,DE_OE,KC_NO,KC_NO, // 7
      KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO, // 6
      KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_RSHIFT, // 7
      KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,  // 5
      // BLOCK
      KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO // 6
    ),

    [WIN_EMPTY1] = EMPTY_LAYER,
    [WIN_EMPTY2] = EMPTY_LAYER,

  [ALL_MOUSE] = LAYOUT_ergodox(
    // Left
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_MS_UP,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,KC_MS_RIGHT,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_LALT,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,

    // BLOCK
    KC_NO,KC_MS_BTN1,KC_MS_BTN2,KC_NO,KC_NO,KC_NO,

    // Right
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_MEDIA_PLAY_PAUSE,KC_NO,KC_NO,
    KC_NO,KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_NO,KC_NO,KC_AUDIO_VOL_UP,KC_AUDIO_VOL_DOWN,
    KC_AUDIO_MUTE,KC_NO,KC_NO,KC_NO,KC_NO,
    // BLOCK
    KC_NO,KC_NO,KC_NO,KC_WWW_BACK),
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

void setup_backlight(uint8_t layer){
  if (is_win_layer(layer)){
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_WIN);
  } else if (is_mac_layer(layer)) {
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_MAC);
  } else {
    ergodox_board_led_off();
  };
};

void matrix_init_user(void) {
  setup_backlight(MACOS_ALPHA);
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

uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(state);


    setup_backlight(layer);
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case MACOS_ALPHA:
      case WIN_ALPHA:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #endif
        break;
      case MACOS_SPECIAL:
      case WIN_SPECIAL:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case MACOS_EMPTY1:
      case WIN_EMPTY1:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case MACOS_EMPTY2:
      case WIN_EMPTY2:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case ALL_MOUSE:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
        /*
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
        */
      default:
        break;
    }
    return state;

};
