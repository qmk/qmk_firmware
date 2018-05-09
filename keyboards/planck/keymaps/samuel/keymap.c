/**
 * Sam's Dvorak Layout Optimized for programming
 **/

#include "planck.h"
#include "action_layer.h"

#define _______ KC_TRNS

extern keymap_config_t keymap_config;

enum planck_layers {
  _DVORAK,
  _LOWER,
  _RAISE,
  _SYMBOLS,
};

enum planck_keycodes {
  DVORAK = SAFE_RANGE,
  LOWER,
  RAISE,
  SYMBOLS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   -  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | LGUI |TabBck| Alt  |Lower |Raise |Space |Symbol| Alt  | Tab  | RGUI | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = {
  { KC_ESC, KC_QUOT,   KC_COMM,  KC_DOT,    KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,   KC_BSPC},
  {KC_MINS,    KC_A,      KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_ENT},
  {KC_LSFT, KC_SCLN,      KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,   KC_RSFT},
  {KC_LCTL, KC_LGUI, S(KC_TAB), KC_LALT,   LOWER,   RAISE,  KC_SPC, SYMBOLS, KC_RALT,  KC_TAB, KC_RGUI,   KC_RCTL}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |Delete|Pg Up |  Up  |Pg Dn |   (  |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Bksp | Left | Down |Right |   )  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Insert| Copy | Cut  |Paste |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_LOWER] = {
  {_______,  KC_DEL, KC_PGUP,     KC_UP,  KC_PGDN, KC_LPRN, _______, _______, _______, _______, _______, _______},
  {_______, KC_BSPC, KC_LEFT,   KC_DOWN, KC_RIGHT, KC_RPRN, _______, _______, _______, _______, _______, _______},
  {_______,  KC_INS, KC_COPY,    KC_CUT, KC_PASTE, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______,   _______,  _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |   +  |   1  |   2  |   3  |   =  |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   0  |   4  |   5  |   6  |   *  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   ^  |   7  |   8  |   9  |   /  |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {_______, KC_PLUS,  KC_1,      KC_2,     KC_3,  KC_EQL, _______, _______, _______, _______, _______, _______},
  {_______,    KC_0,  KC_4,      KC_5,     KC_6, KC_ASTR, _______, _______, _______, _______, _______, _______},
  {_______, KC_CIRC,  KC_7,      KC_8,     KC_9, KC_SLSH, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Symbols
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |   [  |   ]  |   @  |   $  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   !  |   ?  |   &  |   |  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   \  |   #  |   `  |   %  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_SYMBOLS] = {
  {_______, _______, _______,   _______,  _______, _______, _______, KC_LBRC, KC_RBRC,   KC_AT,  KC_DLR, _______},
  {_______, _______, _______,   _______,  _______, KC_MPLY, _______, KC_EXLM, KC_QUES, KC_AMPR, KC_PIPE, _______},
  {_______, _______, _______,   KC_VOLD,  KC_VOLU, KC_MPRV, KC_MNXT, KC_BSLS, KC_HASH,  KC_GRV, KC_PERC, _______},
  {_______, _______, _______,   _______,  _______, _______, _______, _______, _______, _______, _______, _______}
}


};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        // update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        // update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        // update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        // update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case SYMBOLS:
      if (record->event.pressed) {
        layer_on(_SYMBOLS);
        // update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_SYMBOLS);
        // update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}