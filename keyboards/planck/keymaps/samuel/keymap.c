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
};

enum planck_keycodes {
  DVORAK = SAFE_RANGE,
  LOWER,
  RAISE,
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
 * | Ctrl |   /  |TabBck| Alt  |Lower |    Space    |Raise | Alt  | Tab  |      | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = {
  { KC_ESC, KC_QUOT,   KC_COMM,  KC_DOT,    KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,   KC_BSPC},
  {KC_MINS,    KC_A,      KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_ENT},
  {KC_LSFT, KC_SCLN,      KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,   KC_RSFT},
  {KC_LCTL, KC_SLSH, S(KC_TAB), KC_LALT,   LOWER,  KC_SPC,  KC_SPC,   RAISE, KC_RALT,  KC_TAB, _______,   KC_RCTL}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |Pg Up |  Up  |Pg Dn |      |      |   >  |   =  |   <  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | Left | Down |Right |      |      |   !  |   ?  |   &  |   |  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |Delete|Insert| LGUI |      |      |   \  |   ~  |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_LOWER] = {
  {_______, _______, KC_PGUP,     KC_UP,  KC_PGDN, KC_MS_U, KC_BTN1,   KC_GT,  KC_EQL,   KC_LT, _______, _______},
  {_______, _______, KC_LEFT,   KC_DOWN, KC_RIGHT, KC_MS_L, KC_MS_R, KC_EXLM, KC_QUES, KC_AMPR, KC_PIPE, _______},
  {_______, _______,  KC_DEL, KC_INSERT,  KC_LGUI, KC_MS_D, KC_BTN2, KC_BSLS, KC_TILD, _______, _______, _______},
  {_______, _______, _______,   _______,  _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |   $  |   @  |   {  |   }  |      |      |   1  |   2  |   3  |   +  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ^  |   [  |   ]  |   (  |   )  |m Play|   0  |   4  |   5  |   6  |   *  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   %  |   #  | Vol- | Vol+ |m Prev|m Next|   7  |   8  |   9  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {_______, KC_DLR ,   KC_AT,   KC_LCBR,  KC_RCBR, _______, _______,    KC_1,    KC_2,    KC_3, KC_PLUS, _______},
  {KC_CIRC, KC_LBRC, KC_RBRC,   KC_LPRN,  KC_RPRN, KC_MPLY,    KC_0,    KC_4,    KC_5,    KC_6, KC_ASTR, _______},
  {_______, KC_PERC, KC_HASH,   KC_VOLD,  KC_VOLU, KC_MPRV, KC_MNXT,    KC_7,    KC_8,    KC_9, _______, _______},
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
  }
  return true;
}