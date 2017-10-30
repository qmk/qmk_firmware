#include "planck.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "keymap_uk.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _FUNC 3
#define _ADJUST 16
#define _DYN 6

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  FUNC,
  LOWER,
  RAISE,
  DYNAMIC_MACRO_RANGE
};

#include "dynamic_macro.h"

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  ;:  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shft |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  ,<  |  .>  |  /?  | Shft |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Fn   | Ctrl | Alt  | GUI  |Lower | Bksp |Space |Raise | Shift| MENU | Ctrl | Fn   |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_ESC,                KC_Q,       KC_W,        KC_E,      KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,      KC_O,      KC_P,       KC_BSPC                 },
  {MT(MOD_LSFT, KC_TAB),  KC_A,       KC_S,        KC_D,      KC_F,    KC_G,    KC_H,    KC_J,    KC_K,      KC_L,      KC_SCLN,    MT(MOD_RSFT, KC_ENT)    },
  {KC_LSHIFT,             KC_Z,       KC_X,        KC_C,      KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,   KC_DOT,    KC_SLSH,    KC_RSHIFT               },
  {MO(_FUNC),             KC_LCTL,    KC_LALT,     KC_LGUI,   LOWER,   KC_BSPC, KC_SPC,  RAISE,   KC_LSHIFT, KC_BTN2,   KC_RCTL,    MO(_FUNC)               } 
},

/* Function
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  1!  |  2"  |  3£  |  4$  |  5%  |  6^  |  7&  |  8*  |  9(  |  0)  |  ~   |INSERT|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|  \|  |  `¬  |  #~  |   *  |  -_  |  =+  |  \|  |  [{  |  ]}  |  '@  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Fn   | Ctrl | Alt  | GUI  |Lower | Bksp |Space |Raise | MENU | Alt  | Ctrl | Fn   |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC] = {
  {KC_F1,     KC_F2,           KC_F3,    KC_F4,         KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,    KC_F10,  KC_F11,  KC_F12                 },
  {KC_1,      KC_2,            KC_3,     KC_4,          KC_5,    KC_6,    KC_7,    KC_8,      KC_9,     KC_0,    UK_TILD, KC_INSERT              },
  {KC_LSHIFT, KC_NONUS_BSLASH, KC_GRAVE, KC_NONUS_HASH, KC_PAST, KC_MINS, KC_EQL,  KC_BSLASH, KC_LBRC,  KC_RBRC, KC_QUOT, MT(MOD_RSFT, KC_ENT)   },
  {_______,   _______,         _______,  _______,       _______, _______, _______, _______,   _______,  _______, _______, _______                }
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  1!  |  2"  |  3£  |  4$  |  5%  |  6^  |  7&  |  8*  |  9(  |  0)  | DEL  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  !   |   "  |   £  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |WrdDel|WrdBks|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|  \|  |  `¬  |  #~  |  '@  |  -_  |  =+  |  #~  |  [{  |  ]}  |  '@  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |Lower | Del  |Space |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_1,        KC_2,            KC_3,           KC_4,           KC_5,          KC_6,          KC_7,           KC_8,            KC_9,           KC_0,          KC_DEL,          KC_BSPC                },
  {LSFT(KC_1),  LSFT(KC_2),      LSFT(KC_3),     LSFT(KC_4),     LSFT(KC_5),    LSFT(KC_6),    LSFT(KC_7),     LSFT(KC_8),      LSFT(KC_9),     LSFT(KC_0),    LCTL(KC_DEL),    LCTL(KC_BSPC)          },
  {KC_LSPO,     KC_NONUS_BSLASH, KC_GRAVE,       KC_NONUS_HASH,  KC_QUOT,       KC_MINS,       KC_EQL,         KC_NONUS_HASH,   KC_LBRC,        KC_RBRC,       KC_QUOT,         MT(MOD_RSFT, KC_ENT)   },
  {_______,     _______,         _______,        _______,        _______,       KC_DEL,        _______,        _______,         KC_MNXT,        KC_VOLD,       KC_VOLU,         KC_MPLY                }
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |      |WRDSEL|  [   |   ]  |      |      | PGUP | HOME |PGDOWN|      |PRNTSC|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   `  |      |      |  (   |   )  |      |      | HOME |  UP  | END  |      |ZOOM +|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |  {   |   }  |      |  |<  | LEFT | DOWN |RIGHT |  >|  |ZOOM -|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |  Alt | Enter|Raise |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_GRV,  XXXXXXX, M(1),    KC_LBRC,       KC_RBRC,       XXXXXXX,   XXXXXXX,       KC_PGUP,  KC_HOME,  KC_PGDOWN,  XXXXXXX,        KC_PSCREEN            },
  {KC_GRV,  XXXXXXX, XXXXXXX, LSFT(KC_9),    LSFT(KC_0),    XXXXXXX,   XXXXXXX,       KC_HOME,  KC_UP,    KC_END,     XXXXXXX,        LCTL(LSFT(KC_EQL))    },
  {_______, XXXXXXX, XXXXXXX, LSFT(KC_LBRC), LSFT(KC_RBRC), XXXXXXX,   LCTL(KC_LEFT), KC_LEFT,  KC_DOWN,  KC_RIGHT,   LCTL(KC_RIGHT), LCTL(KC_MINS)         },
  {_______, _______, _______, _______,       _______,       KC_LALT,   KC_ENT,        _______,  XXXXXXX,  _______,    _______,        _______               }
},


/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * | ???? | Reset|Qwerty|      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | CAPS |      |      |      |      |      |      | Mute | Vol+ | Play |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Prev | Vol- | Next |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | DYN  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {M(0),    RESET,   QWERTY,  _______, _______, _______, _______, _______,             _______,           _______,              _______,  KC_DEL  },
  {KC_CAPS, _______, _______, _______, _______, _______, _______, KC_AUDIO_MUTE,       KC_AUDIO_VOL_UP,   KC_MEDIA_PLAY_PAUSE,  _______,  _______ },
  {_______, _______, _______, _______, _______, _______, _______, KC_MEDIA_PREV_TRACK, KC_AUDIO_VOL_DOWN, KC_MEDIA_NEXT_TRACK,  _______,  _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______,             MO(_DYN),          _______,              _______,  _______ }
},

/* DYN: Macro Recording and Playback
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      | REC1 | REC2 |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      | PLAY1| PLAY2|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      | STOP | STOP |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_DYN]= {
    {_______,  _______, _______, _______, _______, DYN_REC_START1,  DYN_REC_START2,   _______, _______, _______, _______, _______},
    {_______,  _______, _______, _______, _______, DYN_MACRO_PLAY1, DYN_MACRO_PLAY2,  _______, _______, _______, _______, _______},
    {_______,  _______, _______, _______, _______, DYN_REC_STOP,    DYN_REC_STOP,     _______, _______, _______, _______, _______},
    {_______,  _______, _______, _______, _______, _______,         _______,          _______, _______, _______, _______, _______}
},  

};


void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (!process_record_dynamic_macro(keycode, record)) {
      return false;
  }

   switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
  }
  return true;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch(id) {
    // These would trigger when you hit a key mapped as M(0)
    case 0:
      if (record->event.pressed) {
        return MACRO(
            // SENSITIVE
            END
        );
      }
      break;
    case 1: // Word Select
      if (record->event.pressed) {
        return MACRO(
            DOWN(KC_LCTL), DOWN(KC_RIGHT), UP(KC_RIGHT), DOWN(KC_LSFT), DOWN(KC_LEFT), UP(KC_LEFT), UP(KC_LSFT), UP(KC_LCTL),
            END
        );
      }
  }
  return MACRO_NONE;
};