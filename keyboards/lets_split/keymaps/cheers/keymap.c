#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _NORMAN 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  NORMAN = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Custom macros
#define SFT_ENT     SFT_T(KC_ENT)               // Tap for Enter, hold for Shift

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Norman
,-----------------------------------------. ,-----------------------------------------.
| Esc  |   Q  |   W  |   D  |   F  |   K  | |   J  |   U  |   R  |   L  |   ;  | Bksp |
|------+------+------+------+------+------| |------+------+------+------+------+------|
| Tab  |   A  |   S  |   E  |   T  |   G  | |   Y  |   N  |   I  |   O  |   H  |  '   |
|------+------+------+------+------+------| |------+------+------+------+------+------|
| Shift|   Z  |   X  |   C  |   V  |   B  | |   P  |   M  |   ,  |   .  |   /  | Enter|
|------+------+------+------+------+------| |------+------+------+------+------+------|
|      |      | Ctrl | Alt  | Lower| GUI  | | Space| Raise| Left | Down |  Up  | Right|
`-----------------------------------------' `-----------------------------------------'
 */
[_NORMAN] = KEYMAP( \
  KC_ESC,  KC_Q,    KC_W,    KC_D,    KC_F,  KC_K,    KC_J,   KC_U,  KC_R,    KC_L,    KC_SCLN, KC_BSPC, \
  KC_TAB,  KC_A,    KC_S,    KC_E,    KC_T,  KC_G,    KC_Y,   KC_N,  KC_I,    KC_O,    KC_H,    KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,    KC_P,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, SFT_ENT, \
  , , KC_LCTL, KC_LALT, LOWER, KC_LGUI, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,-----------------------------------------. ,-----------------------------------------.
 * | Esc  |      |      |      |      |      | |   7  |   8  |   9  |   /  |   =  |      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Tab  |      |      |      |      |      | |   4  |   5  |   6  |   *  |      |      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Shift|      |      |      |      |      | |   1  |   2  |   3  |   -  |      |      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      | Ctrl | Alt  |      | GUI  | |Enter |   0  |   .  |   +  |      |      |
 * `-----------------------------------------' `-----------------------------------------'
 */
[_LOWER] = KEYMAP( \
  _______, , , , , , KC_P7,   KC_P8, KC_P9,   KC_PSLS, KC_PEQL, , \
  _______, , , , , , KC_P4,   KC_P5, KC_P6,   KC_PAST, XXXXXXX, , \
  _______, , , , , , KC_P1,   KC_P2, KC_P3,   KC_PMNS, XXXXXXX, , \
  _______, _______, _______, _______, _______, _______, KC_PENT, KC_P0, KC_PDOT, KC_PPLS, , 
),

/* Raise
 * ,-----------------------------------------. ,-----------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  | |   ^  |   &  |   *  |   (  |   )  |  Del |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |   _  |   ?  |   +  |   {  |   }  |  |   | |   -  |   /  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  | |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |      |      |  Del | | Enter|      | Home |PageDn|PageUp|  End |
 * `-----------------------------------------' `-----------------------------------------'
 */
[_RAISE] = KEYMAP( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,  \
  KC_UNDS, KC_QUES, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_MINS, KC_SLSH, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, _______, _______, _______, _______, KC_DEL,  SFT_ENT, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------. ,-----------------------------------------.
 * |      |Reset |      |      |      |      | |      |      |      |      |      |Reset |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm| |AGswap|Norman|      |      |      |      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |      |      |      | |      |      |      |      |      |      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |      |      |      | |      |      |      |      |      |      |
 * `-----------------------------------------' `-----------------------------------------'
 */
[_ADJUST] = KEYMAP( \
  _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,   \
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, NORMAN,  _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][0] = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case NORMAN:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_NORMAN);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
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
  }
  return true;
}
