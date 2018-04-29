#include "nyquist.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _QWERTY2 1
#define _ADJUST 8
#define _ADJUST2 9
#define _FKeys 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  QWERTY2,
  ADJUST,
  ADJUST2,
  FKeys,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define CtShIns LALT(LSFT(KC_INS))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Esc/ADJ|  A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |      |    Space    |    Space    |   [  |  ]   |  -   |  =   |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT( \
  KC_GRV,              KC_1,    KC_2,    KC_3,    KC_4,      KC_5,    KC_6,    KC_7,   KC_8,    KC_9,     KC_0,     KC_BSPC, \
  KC_TAB,              KC_Q,    KC_W,    KC_E,    KC_R,      KC_T,    KC_Y,    KC_U,   KC_I,    KC_O,     KC_P,     KC_BSLS, \
  LT(_ADJUST, KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,      KC_G,    KC_H,    KC_J,   KC_K,    KC_L,     KC_SCLN,  LT(_ADJUST2, KC_QUOT), 
  KC_LSFT,             KC_Z,    KC_X,    KC_C,    KC_V,      KC_B,    KC_N,    KC_M,   KC_COMM, KC_DOT,   KC_SLSH,  KC_ENT , \
  KC_LCTL,             KC_LGUI, KC_LALT, _______, _______,   KC_SPC,  KC_SPC, _______, KC_LBRC, KC_RBRC, KC_MINUS, KC_EQUAL  \
),

/* Qwerty2
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Esc/ADJ|  A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | ALT  |   [  |    Space    |    Space    |   ]  |  -   |  =   |Shift |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY2] = LAYOUT( \
  KC_GRV,              KC_1,    KC_2,    KC_3,    KC_4,      KC_5,    KC_6,   KC_7,    KC_8,    KC_9,     KC_0,     KC_BSPC, \
  KC_TAB,              KC_Q,    KC_W,    KC_E,    KC_R,      KC_T,    KC_Y,   KC_U,    KC_I,    KC_O,     KC_P,     KC_BSLS, \
  LT(_ADJUST, KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,      KC_G,    KC_H,   KC_J,    KC_K,    KC_L,     KC_SCLN,  LT(_ADJUST2, KC_QUOT), \
  KC_LSFT,             KC_Z,    KC_X,    KC_C,    KC_V,      KC_B,    KC_N,   KC_M,    KC_COMM, KC_DOT,   KC_SLSH,  KC_RSFT , \
  KC_LCTL,             KC_LGUI, KC_LALT, KC_LBRC, _______,   KC_SPC,  KC_SPC, _______, KC_RBRC, KC_MINUS, KC_EQUAL, KC_RSFT  \
),

/* Adjust
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |  End |      |      |      |      |      | Home |  del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Map1  |Map2  |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |   l  |   d  |   u  |   r  |  [   |  ]   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |Paste |      |      |      |   -  |   =  |  -   |  =   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |Enter |Enter |      |      |      |      |FKEYS |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT( \
  _______, _______, _______, _______, KC_END,  _______, _______, _______, _______,  _______,  KC_HOME, KC_DELETE, \
  _______, QWERTY,  QWERTY2, _______, _______, _______, _______, _______, _______,  _______,  _______, _______,   \
  _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,    KC_RIGHT, KC_LBRC, KC_RBRC,   \
  _______, _______, _______, _______, CtShIns, _______, _______, _______, KC_MINUS, KC_EQUAL, KC_MINUS, KC_EQUAL,    \
  _______, _______, _______, _______, _______, KC_ENT,  KC_ENT,  _______, _______,  _______,  _______, FKeys     \
),

/* Adjust2
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST2] = LAYOUT( \
  _______, _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______, _______, \
  _______, _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______, _______, \
  _______, _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______, _______, \
  _______, _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______, _______, \
  _______, _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______, _______ \
),

/* FKeys (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FKeys] =  LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
)

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case QWERTY2:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY2);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case ADJUST2:
      if (record->event.pressed) {
        layer_on(_ADJUST2);
      } else {
        layer_off(_ADJUST2);
      }
      return false;
      break;
    case FKeys:
      if (record->event.pressed) {
        layer_on(_FKeys);
      } else {
        layer_off(_FKeys);
      }
      return false;
      break;
  }
  return true;
}
