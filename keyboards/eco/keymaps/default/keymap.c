
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
#define _FN1 2
#define _FN2 3

enum eco_keycodes {
  QWERTY = SAFE_RANGE
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-------------------------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   [  |   ]  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   '  | Enter|  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|  Up  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  GUI | Alt  | Del  | FN1  | FN1  | Space| Space| FN2  | FN2  | Ctrl | Left | Down | Right|
 * `-------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP(
  KC_ESC,  KC_Q,   KC_W,    KC_E,   KC_R,     KC_T,     KC_Y,   KC_U,   KC_I,     KC_O,     KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
  KC_TAB,  KC_A,   KC_S,    KC_D,   KC_F,     KC_G,     KC_H,   KC_J,   KC_K,     KC_L,     KC_SCLN, KC_QUOT, KC_ENT,  KC_BSLS,
  KC_LSFT, KC_Z,   KC_X,    KC_C,   KC_V,     KC_B,     KC_N,   KC_M,   KC_COMM,  KC_DOT,   KC_SLSH, KC_RSFT, KC_UP,   KC_DEL,
  KC_LCTL, KC_LGUI,KC_LALT, KC_DEL, MO(_FN1), MO(_FN1), KC_SPC, KC_SPC, MO(_FN2), MO(_FN2), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
),

/* FN1
 * ,-------------------------------------------------------------------------------------------------.
 * |      |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |   _  |   +  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |caltde|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      | RESET|
 * `-------------------------------------------------------------------------------------------------'
 */
[_FN1] = KEYMAP(
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS, _______,
  CALTDEL, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET
),

/* Raise
 * ,-------------------------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |   =  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |Taskmg|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-------------------------------------------------------------------------------------------------'
 */
[_FN2] = KEYMAP(
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  _______,
  TSKMGR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
  }
  return true;
}

