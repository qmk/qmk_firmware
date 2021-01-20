#include "d48tr.h"
#include "action_layer.h"
#include "eeconfig.h"
#include <print.h>
#include "trackball.c"

extern keymap_config_t keymap_config;

void startup_user() {
    debug_enable = true;
}

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  MS_L,
  MS_R,
  MS_WH
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   -  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |MS_R  |MS_WH |MS_L  |Space |Lower/|Raise/| Left | Down |  Up  |Right |
 * |      |      |      |      |      |      |Space |GRAVE |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
*/
[_QWERTY] = KEYMAP( \
  KC_ESC ,  KC_Q,      KC_W,      KC_E,    KC_R,    KC_T,      KC_Y,             KC_U,               KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_TAB ,  KC_A,      KC_S,      KC_D,    KC_F,    KC_G,      KC_H,             KC_J,               KC_K,    KC_L,    KC_MINS, KC_ENT,  \
  KC_LSFT,  KC_Z,      KC_X,      KC_C,    KC_V,    KC_B,      KC_N,             KC_M,               KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
  KC_LCTL,  KC_LGUI,   MS_R,      MS_WH,   MS_L,    KC_SPC,    LT(_LOWER,KC_SPC),LT(_RAISE,KC_GRAVE),KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |  F1  |  F2  |  F3  |      |      |   ^  |   \  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   4  |   5  |   6  |  F4  |  F5  |  F6  |      |      |   @  |   [  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   7  |   8  |   9  |  F7  |  F8  |  F9  |      |      |   *  |   ]  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |Alt   |MS_WH |MS_L  |Space |Lower/|Raise/| Left |   /  |   _  |Right |
 * |      |      |      |      |      |      |Space |GRAVE |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
*/
[_LOWER] = KEYMAP( \
  KC_ESC ,  KC_1,      KC_2,      KC_3,    KC_F1,   KC_F2,     KC_F3,            XXXXXXX,            XXXXXXX, KC_CIRC, KC_JYEN, KC_BSPC, \
  KC_TAB ,  KC_4,      KC_5,      KC_6,    KC_F4,   KC_F5,     KC_F6,            XXXXXXX,            XXXXXXX, KC_AT  , KC_LBRC, KC_ENT, \
  KC_LSFT,  KC_7,      KC_8,      KC_9,    KC_F7,   KC_F8,     KC_F9,            XXXXXXX,            XXXXXXX, KC_PAST, KC_RBRC, KC_RSFT, \
  KC_LCTL,  KC_LGUI,   KC_LALT,  MS_WH,   MS_L,    KC_SPC,    LT(_LOWER,KC_SPC),LT(_LOWER,KC_GRAVE)   ,KC_LEFT, KC_SLSH, KC_UNDS, KC_RGHT \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |Alt   |MS_WH |MS_L  |Space |Lower/|Raise/| Left | Down |  Up  |Right |
 * |      |      |      |      |      |      |Space |GRAVE |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
*/
[_RAISE] = KEYMAP( \
  KC_ESC ,  KC_1,      KC_2,      KC_3,    KC_4,    KC_5,      KC_6,             KC_7,               KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB ,  KC_F1,     KC_F2,     KC_F3,   KC_F4,   KC_F5,     KC_F6,            KC_F7,              KC_F8,   KC_F9,   KC_F10,  KC_ENT, \
  KC_LSFT,  KC_F7,     KC_F8,     KC_F9,   KC_F10,  KC_F11,    KC_F12,           XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT, \
  KC_LCTL,  KC_LGUI,   KC_LALT,  MS_WH,   MS_L,    KC_SPC,    LT(_LOWER,KC_SPC),LT(_RAISE,KC_GRAVE),KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
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
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
    case MS_L:
      if (record->event.pressed) {
        mouse_btn1 = true;
      } else {
        mouse_btn1 = false;
      }
      return false;
      break;
    case MS_R:
      if (record->event.pressed) {
        mouse_btn2 = true;
      } else {
        mouse_btn2 = false;
      }
      return false;
      break;
    case MS_WH:
      if (record->event.pressed) {
        wheel = true;
      } else {
        wheel = false;
      }
      return false;
      break;
  }
	

	
  return true;
}


