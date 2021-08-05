#include QMK_KEYBOARD_H
#include "version.h"

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
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)

enum custom_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox_pretty(
    KC_ESCAPE,      KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_LEFT,                                        KC_RIGHT,       KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_RBRACKET,
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_DELETE,                                      KC_BSPACE,      KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_LBRACKET,
    KC_BSPACE,      KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                                                           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCOLON,      KC_QUOTE,
    KC_LSPO,      LCTL_T(KC_Z),   LALT_T(KC_X),     KC_C,           KC_V,           KC_B,           KC_ENTER,                                       LCTL(KC_GRAVE), KC_N,           KC_M,           KC_COMMA,       RALT_T(KC_DOT), RCTL_T(KC_SLASH),KC_RSPC,
    LT(1,KC_GRAVE), KC_UP,          KC_DOWN,        LT(2,KC_LEFT),        SH_T(KC_RIGHT),                                                                                                       LT(1,KC_UP),    KC_DOWN,        KC_LEFT,        KC_RIGHT,       KC_CAPSLOCK,
                                                                                                    LALT(LCTL(LGUI(LSFT(KC_TAB)))),KC_GRAVE,       KC_MINUS,       KC_EQUAL,
                                                                                                                    KC_BSLASH,      KC_PGUP,
                                                                                    KC_SPACE,       KC_LGUI,        LCTL(KC_GRAVE), KC_PGDOWN,      KC_SPACE,       KC_ENTER
  ),
  [1] = LAYOUT_ergodox_pretty(
    KC_ESCAPE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,
    LT(2,KC_NO),    KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_UP,          KC_7,           KC_8,           KC_9,           KC_KP_PLUS,     KC_F12,
    KC_TRANSPARENT, KC_HASH,        LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),   LGUI(KC_W),     KC_GRAVE,                                                                       KC_DOWN,        KC_4,           KC_5,           KC_6,           KC_KP_MINUS,    KC_TRANSPARENT,
    KC_TRANSPARENT, KC_PERC,        LGUI(KC_LEFT),  LGUI(KC_RIGHT), LGUI(KC_RIGHT), KC_TILD,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_BSPACE,      KC_1,           KC_2,           KC_3,           KC_KP_ASTERISK, KC_MEDIA_PLAY_PAUSE,
    KC_TRANSPARENT, KC_MS_WH_LEFT,  KC_MS_WH_UP,        KC_MS_WH_DOWN,      KC_MS_WH_RIGHT,                                                                                                 KC_TRANSPARENT, KC_KP_0,        RALT_T(KC_KP_DOT),KC_KP_SLASH,    KC_RSHIFT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_F13,         KC_F15,         KC_TRANSPARENT, KC_TRANSPARENT, KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP
  ),
  [2] = LAYOUT_ergodox_pretty(
    RESET,          LCTL(LSFT(KC_POWER)),KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_UP,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_LEFT,        KC_DOWN,     KC_RIGHT,       KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PLAY_PAUSE,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_BTN1,     KC_MS_BTN2,                                                                                                     KC_AUDIO_VOL_UP,KC_AUDIO_VOL_DOWN,KC_AUDIO_MUTE,  KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LSFT(LALT(KC_AUDIO_VOL_DOWN)), LSFT(LALT(KC_AUDIO_VOL_UP))
  ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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


