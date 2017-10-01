#include "roadkit.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _NP 0
#define _L1 1
#define _L2 2

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

enum custom_keycodes {
  NUMPAD = SAFE_RANGE,
  ADMIN,
  SMSPC1,
  STR192,
  STR255
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Numpad
 * ,-----------------------.
 * |  7  |  8  |  9  |Bksp |
 * |-----`-----`-----`-----|
 * |  4  |  5  |  6  | Tab |
 * |-----`-----`-----`-----|
 * |  1  |  2  |  3  |Enter|
 * |-----`-----`-----`-----|
 * |  0  |Space|  .  |  /  |
 * `-----`-----`-----`-----'
 * | L1  | L2  |     |     | Layer hold
 */
  [_NP] = /* Numpad */
    SINGLES_KEYMAP(KC_P7,        KC_P8,         KC_P9,   KC_BSPC, \
                   KC_P4,        KC_P5,         KC_P6,   KC_TAB, \
                   KC_P1,        KC_P2,         KC_P3,   KC_PENT, \
                   LT(1, KC_P0), LT(2, KC_SPC), KC_PDOT, KC_PSLS),

/* L1
 * ,-----------------------.
 * |Reset|     |     | Del |
 * |-----`-----`-----`-----|
 * | Left| Down| Up  |Right|
 * |-----`-----`-----`-----|
 * | 192.| 255 |     |     |
 * |-----`-----`-----`-----|
 * |_____| LED |  .  |     |
 * `-----`-----`-----`-----'
 */
  [_L1] = /* LAYER 1 */
    SINGLES_KEYMAP(RESET,   XXXXXXX, XXXXXXX, KC_DEL, \
                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, \
                   STR192,  STR255,  XXXXXXX, XXXXXXX, \
                   _______, BL_STEP, _______, XXXXXXX),
 
/* L2
 * ,-----------------------.
 * |     |     | str | str |
 * |-----`-----`-----`-----|
 * |     |     |     |     |
 * |-----`-----`-----`-----|
 * |     |     |     |     |
 * |-----`-----`-----`-----|
 * |     |_____|     |     |
 * `-----`-----`-----`-----'
 */
  [_L2] = /* LAYER 2 */
    SINGLES_KEYMAP(XXXXXXX, XXXXXXX, ADMIN,   SMSPC1, \
                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                   XXXXXXX, _______, XXXXXXX, XXXXXXX)
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ADMIN:
      if (record->event.pressed) {
	SEND_STRING("Administrator");
      }
      return false;
      break;
    case SMSPC1:
      if (record->event.pressed) {
	SEND_STRING("Simspace1!");
      }
      return false;
      break;
    case STR192:
      if (record->event.pressed) {
	SEND_STRING("192.168.");
      }
      return false;
      break;
    case STR255:
      if (record->event.pressed) {
	SEND_STRING("255");
      }
      return false;
      break;
  }
  return true;
};
