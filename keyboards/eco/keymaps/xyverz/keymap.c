// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

// Default ECO Layout
// KLE here : http://www.keyboard-layout-editor.com/#/gists/0733eca6b4cb88ff9d7de746803f4039

#include "eco.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  BACKLIT
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Aliases to make reading the keymap easier
#define GUIBSPC GUI_T(KC_BSPC) // GUI when held, BSPC when tapped.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-------------------------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |      |      |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |      |      |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |      |      |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * | Ctrl | Alt  | Left |Right |Lower | Bksp |  GUI |Enter |Space |Raise |  Up  | Down |  GUI |Enter |
 * `-------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,   KC_NO,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_NO,   KC_NO,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_NO,   KC_NO,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   KC_BSPC, KC_LGUI, KC_ENT,  KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_ENT 
),

/* Colemak
 * ,-------------------------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |      |      |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |      |      |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |      |      |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * | Ctrl | Alt  | Left |Right |Lower | Bksp |  GUI |Enter |Space |Raise |  Up  | Down |  GUI |Enter |
 * `-------------------------------------------------------------------------------------------------'
 */
[_COLEMAK] = KEYMAP(
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_NO,   KC_NO,   KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
  KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_NO,   KC_NO,   KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_NO,   KC_NO,   KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   KC_BSPC, KC_LGUI, KC_ENT,  KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_ENT 
),

/* Dvorak
 * ,-------------------------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |      |      |   F  |   G  |   C  |   R  |   L  |  /   |
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |      |      |   D  |   H  |   T  |   N  |   S  |  -   |
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |      |      |   B  |   M  |   W  |   V  |   Z  | Shift|
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * | Ctrl | Alt  | Left |Right |Lower | Bksp |  GUI |Enter |Space |Raise |  Up  | Down |  GUI |Enter |
 * `-------------------------------------------------------------------------------------------------'
 */
[_DVORAK] = KEYMAP(
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_NO,   KC_NO,   KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
  KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_NO,   KC_NO,   KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
  KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_NO,   KC_NO,   KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
  KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   KC_BSPC, KC_LGUI, KC_ENT,  KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_ENT 
),

/* Lower
 * ,-------------------------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |      |      |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * | Caps |      | Mute | Vol- | Vol+ |      |      |      |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * |      |      | Prev | Play | Next |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * | Brite|      | Home |  End |      |  Del |      |      |      |      |      |      |      |      |
 * `-------------------------------------------------------------------------------------------------'
 */
[_LOWER] = KEYMAP(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_NO,   KC_NO,   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_NO,   KC_NO,   _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_NO,   KC_NO,   _______, _______, _______, _______, _______, _______,
  _______, _______, KC_HOME, KC_END,  _______, KC_DEL,  _______, _______, KC_INS,  _______, KC_PGUP, KC_PGDN, _______, _______
),

/* Raise
 * ,-------------------------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |      |      |   6  |   7  |   8  |   9  |   0  |   -  |
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-------------------------------------------------------------------------------------------------'
 */
[_RAISE] = KEYMAP(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_NO,   KC_NO,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_NO,   KC_NO,   _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_NO,   KC_NO,   _______, _______, _______, _______, _______, _______,
  _______, _______, KC_HOME, KC_END,  _______, KC_DEL,  _______, _______, KC_INS,  _______, KC_PGUP, KC_PGDN, _______, _______
),


/* Adjust
 * ,-------------------------------------------------------------------------------------------------.
 * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-------------------------------------------------------------------------------------------------'
 */
[_ADJUST] = KEYMAP(
  KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,   KC_NO,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12 ,
  _______, RESET,   _______, _______, _______, _______, KC_NO,   KC_NO,   _______, QWERTY,  COLEMAK, DVORAK,  _______, _______,
  _______, _______, _______, _______, _______, _______, KC_NO,   KC_NO,   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_DVORAK);
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
  }
  return true;
}

