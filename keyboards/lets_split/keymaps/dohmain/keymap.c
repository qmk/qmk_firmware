#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

// #define _QWERTY 0
// #define _COLEMAK 1
// #define _LOWER 2
// #define _RAISE 3
// #define _ADJUST 16

enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _LOWER,
  _RAISE,
  _FUNCTION,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE,
  FUNCTION,
  ADJUST
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /* QWERTY Layer 
   * ,------------------------------------------------------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  ||   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------++------+------+------+------+------+------|
   * |FnCaps|   A  |   S  |   D  |   F  |   G  ||   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------++------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  ||   N  |   M  |   ,  |   .  |   /  |Shift |
   * |------+------+------+------+------+------++------+------+------+------+------+------|
   * |      | Ctrl | GUI  | Alt  |Lower |Enter ||Space |Raise | Left | Down |  Up  |Right |
   * `------------------------------------------------------------------------------------'
   */
[_QWERTY] = KEYMAP( \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
    LT(4, KC_CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  \
    KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, \
    XXXXXXX, KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_ENT,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

/* Colemak Layer 
   * ,------------------------------------------------------------------------------------.
   * | Tab  |   Q  |   W  |   F  |   P  |   G  ||   J  |   L  |   U  |   Y  |   ;  | Bksp |
   * |------+------+------+------+------+------++------+------+------+------+------+------|
   * |FnCaps|   A  |   R  |   S  |   T  |   D  ||   H  |   N  |   E  |   I  |   O  |  "   |
   * |------+------+------+------+------+------++------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  ||   K  |   M  |   ,  |   .  |   /  |Shift |
   * |------+------+------+------+------+------++------+------+------+------+------+------|
   * |      | Ctrl | GUI  | Alt  |Lower |Enter ||Space |Raise | Left | Down |  Up  |Right |
   * `------------------------------------------------------------------------------------'
   */
[_COLEMAK] = KEYMAP( \
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC, \
    LT(4, KC_CAPS), KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,  \
    KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, \
    XXXXXXX, KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_ENT,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

/* Lower
    * ,------------------------------------------------------------------------------------.
    * |   `  |   1  |   2  |   3  |   4  |   5  ||   6  |   7  |   8  |   9  |   0  | Bksp |
    * |------+------+------+------+------+------++------+------+------+------+------+------|
    * |      |      |      |      |      |      ||      |   -  |   =  |   [  |   ]  |  \   |
    * |------+------+------+------+------+------++------+------+------+------+------+------|
    * | Shift|      |      |      |      |      ||      | Mute |   ,  |   .  |      |Shift |
    * |------+------+------+------+------+------++------+------+------+------+------+------|
    * |      | Ctrl | GUI  | Alt  |Lower |Enter ||Space |Raise | Next | Vol- | Vol+ | Play |
    * `------------------------------------------------------------------------------------'
    */
[_LOWER] = KEYMAP ( \
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
    KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, _______, _______, KC_MPLY, KC_RSFT, \
    XXXXXXX, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT  \
),

/* Raise
    * ,------------------------------------------------------------------------------------.
    * |   ~  |   !  |   @  |   #  |   $  |   %  ||   ^  |   &  |   *  |   (  |   )  | Bksp |
    * |------+------+------+------+------+------++------+------+------+------+------+------|
    * | Esc  |  F1  |  F2  |  F3  |  F4  |  F5  ||  F6  |   _  |   +  |   {  |   }  |  |   |
    * |------+------+------+------+------+------++------+------+------+------+------+------|
    * | Shift|  F7  |  F8  |  F9  |  F10 |  F11 ||  F12 |      |      |      |      |Shift |
    * |------+------+------+------+------+------++------+------+------+------+------+------|
    * |      | Ctrl | GUI  | Alt  |Lower |Enter ||Space |Raise | Home | PgDn | PgUp | End  |
    * `-----------------------------------------------------------------------------------'
    */
[_RAISE] = KEYMAP ( \
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_INS,  \
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
    KC_LSFT, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT, \
    XXXXXXX, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
),

/* Function
    * ,------------------------------------------------------------------------------------.
    * |      |      |      |      |      |      ||      | Home |  Up  | End  |Prtsc |      |
    * |------+------+------+------+------+------++------+------+------+------+------+------|
    * |      |      |      |      |      |      || PgUp | Left | Down | Right| Del  | Ins  |
    * |------+------+------+------+------+------++------+------+------+------+------+------|
    * | Shift|      |      |      |      |      || PgDn |      |      |      |      |Shift |
    * |------+------+------+------+------+------++------+------+------+------+------+------|
    * |      | Ctrl | Menu | Alt  |      |Enter ||Space |      |      |      |      |      |
    * `------------------------------------------------------------------------------------'
    */
[_FUNCTION] = KEYMAP ( \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_UP,   KC_END,  KC_PSCR, XXXXXXX, \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,  KC_INS,  \
    KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT, \
    XXXXXXX, _______, KC_APP,  _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
),

/* Adjust (Lower + Raise)
    * ,------------------------------------------------------------------------------------.
    * |      |QWERTY|      |      |      |      ||RGBVA-|RGBVA+|      |      |      |      |
    * |------+------+------+------+------+------++------+------+------+------+------+------|
    * |      |      |      |      |      |      ||      |Plain |Breath|Rnbow |Swirl |      |
    * |------+------+------+------+------+------++------+------+------+------+------+------|
    * |      |      |      |COLEMK|      |      ||      |Snake |Knight|Grade |X-mas |      |
    * |------+------+------+------+------+------++------+------+------+------+------+------|
    * |      |      |      |      |Lower |RGBTOG||RGBMOD|Raise |RGBHU-|RGBSA-|RGBSA+|RGBHU+|
    * `------------------------------------------------------------------------------------'
    */
[_ADJUST] = KEYMAP ( \
  XXXXXXX, QWERTY,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_VAD, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, COLEMAK, XXXXXXX, XXXXXXX, XXXXXXX, RGB_M_SN, RGB_M_K, RGB_M_G, RGB_M_G, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, RGB_TOG, RGB_MOD, _______, RGB_HUD, RGB_SAD, RGB_SAI, RGB_HUI  \
)

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
