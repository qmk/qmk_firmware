#include QMK_KEYBOARD_H

/*
 Keymap is loosely based on DivergeJM's Nyquist keymap
 Major changes made:
  - DVORAK, COLEMAK, FUNCTION, MOUSE, and ADJUST layers have been removed
  - right 2u key performs backspace, not enter
  - LOWER layer controls function keys, media controls, and underglow
  - ARROW layer uses JKLI for arrow keys
  - Bootmagic enabled and bootmagic initialization key changed from space to enter
*/

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

  // Enable these functions using FUNC(n) macro.
  const uint16_t PROGMEM fn_actions[] = {
      [0] = LT(_LOWER, KC_SPC),    //Hold for momentary Lower layer, Tap for Backspace,
      [1] = LT(_RAISE, KC_BSPC),     //Hold for momentary Raise layer, Tap for Space,
      [2] = MO(_ARROW), //Hold for momentary Arrow
   };

#define SPC_LWR FUNC(0)
#define BSP_RSE FUNC(1)
#define ARW FUNC(2)

// Underglow setup
#define RGBLIGHT_SLEEP
#define RGBLIGHT_ANIMATIONS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .----------------------------------------.     .-----------------------------------------.
 * | Esc |   1  |   2  |   3  |   4  |   5  |     |   6  |   7  |   8  |   9  |   0  |  -   |
 * |-----+------+------+------+------+------|     |------+------+------+------+------+------|
 * | Tab |   Q  |   W  |   E  |   R  |   T  |     |   Y  |   U  |   I  |   O  |   P  |Enter |
 * |-----+------+------+------+------+------|     |------+------+------+------+------+------|
 * | Caps|   A  |   S  |   D  |   F  |   G  |     |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |-----+------+------+------+------+------|     |------+------+------+------+------+------|
 * |Lshft|   Z  |   X  |   C  |   V  |   B  |     |   N  |   M  |   ,  |   .  |  /   |Rshft |
 * |-----+------+------+------+------+------|     |------+------+------+------+------+------|
 * |Arrow| LCtrl| LAlt | LGui |  Bspc/Raise |     |   Spc/Lower | RGui | RAlt | RCtrl| Del  |
 * `----------------------------------------'     '-----------------------------------------'
 */

[_QWERTY] = LAYOUT(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,      KC_9,    KC_0,    KC_MINS,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,      KC_O,    KC_P,    KC_ENT,
  KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,      KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,   KC_DOT,  KC_SLSH, KC_RSFT,
  ARW,     KC_LCTL, KC_LALT, KC_LGUI, BSP_RSE, BSP_RSE, SPC_LWR, SPC_LWR, KC_RGUI,   KC_RALT, KC_RCTL, KC_DEL
  ),

/* Raise
 * ,-----------------------------------------.    .-----------------------------------------.
 * |      |      |      |      |      |      |    |   =  |   /  |   *  |   -  |   \  |   `  |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |   7  |   8  |   9  |   +  |   [  |   ]  |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |   4  |   5  |   6  | Enter|      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Lshft|      |      |      |      |      |    |   1  |   2  |   3  | Space|      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      | LGui |             |    |      0      |   .  | Bspc |      |      |
 * `-----------------------------------------'    `-----------------------------------------'
 */

[_RAISE] = LAYOUT(
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_PEQL, KC_PSLS, KC_PAST, KC_MINS,  KC_BSLS, KC_GRV,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_7,    KC_8,    KC_9,    KC_PPLS,  KC_LBRC, KC_RBRC,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_4,    KC_5,    KC_6,    KC_PENT,  XXXXXXX, XXXXXXX,
  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_1,    KC_2,    KC_3,    KC_SPC,   XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,  _______,  KC_0,    KC_0,    KC_DOT,  KC_BSPC,  XXXXXXX, XXXXXXX
),

/* Lower
 * ,-----------------------------------------.    .-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | >/|| | Mute | Vol- | Vol+ | |<<  | >>|  |    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |RGB IO|RGB >>|RGB <<|Hue++ |Hue-- |      |    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |Sat++ |Sat-- |Val++ |Val-- |             |    |             |      |      |      |      |
 * `-----------------------------------------'    `-----------------------------------------'
*/

[_LOWER] = LAYOUT(
  KC_F1,    KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_F7,    KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_MPLY,  KC_MUTE, KC_VOLD,  KC_VOLU, KC_MPRV, KC_MNXT, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  RGB_TOG,  RGB_MOD, RGB_RMOD, RGB_HUI, RGB_HUD, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  RGB_SAI,  RGB_SAD, RGB_VAI,  RGB_VAD, XXXXXXX, XXXXXXX, _______,  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

/* Arrow
 * ,-----------------------------------------.     ,----------------------------------------.
 * |      |      |      |      |      |      |     |     |      |      |      |      |      |
 * |------+------+------+------+------+------|     |-----+------+------+------+------+------|
 * |      |      |      |      |      |      |     |     |      |  Up  |      |      |      |
 * |------+------+------+------+------+------|     |-----+------+------+------+------+------|
 * |      |      |      |      |      |      |     |     | Left | Down |Right |      |      |
 * |------+------+------+------+------+------|     |-----+------+------+------+------+------|
 * |      |      |      |      |      |      |     |     |      |      |      |      |      |
 * |------+------+------+------+------+------|     |-----+------+------+------+------+------|
 * |      |      |      | Gui  |             |     |            |      |      |      |      |
 * `-----------------------------------------'     `----------------------------------------'
 */

[_ARROW] = LAYOUT(
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX,  XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT,  XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,
  _______,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX
),

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

/* Cases to switch default layer to QWERTY, COLEMAK or DVORAK
    and to access ADJUST layer to access the switch keys */
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
  }
  return true;
}
