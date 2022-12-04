#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _NUMPAD 0
#define _ADJUST 1

enum custom_keycodes {
  NUMPAD = SAFE_RANGE,
  ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |   0  |   1  |   4  |   7  | nlck |  <-- |   0  |   1  |   4  |   7  | nlck |  <-- |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  adj |   2  |   5  |   8  |   /  |  \/  |   ,  |   2  |   5  |   8  |   /  |  \/  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   .  |   3  |   6  |   9  |   *  |  /\  |   .  |   3  |   6  |   9  |   *  |  /\  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Enter|  tab |   -  |   +  |bckspc|  --> | Enter|  tab |   -  |   +  |bckspc|  --> |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_ortho_4x12(
  KC_KP_0,     KC_KP_1,    KC_KP_4,     KC_KP_7,    KC_NUMLOCK,     KC_LEFT,   KC_KP_0,     KC_KP_1,    KC_KP_4,     KC_KP_7,    KC_NUMLOCK,     KC_LEFT,
  ADJUST,      KC_KP_2,    KC_KP_5,     KC_KP_8,    KC_KP_SLASH,    KC_DOWN,   ADJUST,      KC_KP_2,    KC_KP_5,     KC_KP_8,    KC_KP_SLASH,    KC_DOWN,
  KC_KP_DOT,   KC_KP_3,    KC_KP_6,     KC_KP_9,    KC_KP_ASTERISK, KC_UP,     KC_KP_DOT,   KC_KP_3,    KC_KP_6,     KC_KP_9,    KC_KP_ASTERISK, KC_UP,
  KC_KP_ENTER, KC_TAB,     KC_KP_MINUS, KC_KP_PLUS, KC_BSPACE,      KC_RIGHT,  KC_KP_ENTER, KC_TAB,     KC_KP_MINUS, KC_KP_PLUS, KC_BSPACE,      KC_RIGHT
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | QK_BOOT QK_BOOT |      |      |      |      |RGBMOD|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  LAYOUT_ortho_4x12(
  _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______,  _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, QK_BOOT, QK_BOOT, _______, _______, _______, _______, RGB_MOD
)


};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
