#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum custom_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ARROW
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ARROW
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .----------------------------------------------------------------------------------.
 * | Esc |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |Enter |
 * |-----+------+------+------+------+------|------+------+------+------+------+------|
 * | Tab |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |-----+------+------+------+------+------|------+------+------+------+------+------|
 * |Lshft|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  /   |Rshft |
 * |-----+------+------+------+------+------|------+------+------+------+------+------|
 * |Arrow| LCtrl| LAlt | LGui | Lower| Bspc | Space| Raise| RGui | RAlt |RCtrl |  -   |
 * `----------------------------------------------------------------------------------'
 */

[_QWERTY] = LAYOUT_planck_grid(
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,      KC_O,    KC_P,    KC_ENT,
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,      KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,   KC_DOT,  KC_SLSH, KC_RSFT,
  ARROW,   KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_BSPC, KC_SPC,  RAISE,   KC_RGUI,   KC_RALT, KC_RCTL, KC_MINS
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |   7  |   8  |   9  |   /  |   \  |   `  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |   4  |   5  |   6  |   *  |   (  |   )  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Lshft|      |      |      |      |      |   1  |   2  |   3  |   -  |   [  |   ]  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      | LGui |      |      |   0  |   .  |   =  |   +  |   {  |   }  |
 * `-----------------------------------------------------------------------------------'
 */

[_LOWER] = LAYOUT_planck_grid(
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_7,    KC_8,    KC_9,    KC_PSLS,  KC_BSLS, KC_GRV,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_4,    KC_5,    KC_6,    KC_PAST,  KC_LPRN, KC_RPRN,
  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_1,    KC_2,    KC_3,    KC_MINS,  KC_LBRC, KC_RBRC,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,  XXXXXXX,  KC_0,    KC_DOT,  KC_PEQL, KC_PPLS,  KC_LCBR, KC_RCBR
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | >/|| | Mute | Vol- | Vol+ | |<<  | >>|  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
*/

[_RAISE] = LAYOUT_planck_grid(
  KC_F1,    KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_F7,    KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_MPLY,  KC_MUTE, KC_VOLD,  KC_VOLU, KC_MPRV, KC_MNXT, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Arrow
 * ,----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |     |      |  Up  |      |      |      |
 * |------+------+------+------+------+------|-----+------+------+------+------+------|
 * |      |      |      |      |      |      |     | Left | Down |Right |      |      |
 * |------+------+------+------+------+------|-----+------+------+------+------+------|
 * |      |      |      |      |      |      |     |      |      |      |      |      |
 * |------+------+------+------+------+------|-----+------+------+------+------+------|
 * |      |      |      | Gui  |      |      |     |      |      |      |      |      |
 * `----------------------------------------------------------------------------------'
 */

[_ARROW] = LAYOUT_planck_grid(
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX,  XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT,  XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,
  _______,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
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
    case ARROW:
        if (record->event.pressed) {
          layer_on(_ARROW);
        } else {
          layer_off(_ARROW);
        }
        return false;
        break;
  }
  return true;
}
