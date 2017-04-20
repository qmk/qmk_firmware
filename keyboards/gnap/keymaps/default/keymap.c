#include "gnap.h"
#include "action_layer.h"

#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _TB 3

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */

[_QWERTY] = { /* Qwerty */
  {KC_ESC,   KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,    KC_Y,     KC_U,      KC_I,      KC_O,       KC_P,       KC_BSPC},
  {F(3),     KC_A,    KC_S,    KC_D,    KC_F,     KC_G,    KC_H,     KC_J,      KC_K,      KC_L,       KC_SCLN,    KC_QUOT},
  {KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,    KC_N,     KC_M,      KC_COMM,   KC_DOT,     KC_SLSH,    F(0)},
  {KC_LCTL,  KC_LALT, KC_LGUI, KC_APP,  F(1),     KC_SPC,  KC_SPC,   F(2),      KC_LEFT,   KC_DOWN,    KC_UP,      KC_RGHT}
},

[_LOWER] = {
  {S(KC_GRV),S(KC_1), S(KC_2), S(KC_3), S(KC_4),  S(KC_5), S(KC_6),  S(KC_7),   S(KC_8),   S(KC_9),    S(KC_0),    KC_BSPC},
  {KC_TRNS,  KC_TRNS, KC_TRNS, KC_PAUSE,KC_TRNS,  KC_TRNS, KC_TRNS,  S(KC_MINS),S(KC_EQL), S(KC_LBRC), S(KC_RBRC), S(KC_BSLS)},
  {KC_TRNS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,    KC_F7,     KC_F8,     KC_F9,      KC_F10,     KC_TRNS},
  {KC_TRNS,  KC_TRNS, KC_TRNS, KC_CAPS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,   KC_MNXT,   KC_VOLD,    KC_VOLU,    KC_MPLY}
},

[_RAISE] = {
  {KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,     KC_5,    KC_6,     KC_7,      KC_8,      KC_9,       KC_0,       KC_DELETE},
  {KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_MINS,   KC_EQL,    KC_LBRC,    KC_RBRC,    KC_BSLS},
  {KC_TRNS,  KC_F11,  KC_F12,  KC_F13,  KC_F14,   KC_F15,  KC_F16,   KC_F17,    KC_F18,    KC_F19,     KC_F20,     KC_TRNS},
  {KC_TRNS,  KC_TRNS, KC_TRNS, BL_STEP, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,   KC_HOME,   KC_PGDN,    KC_PGUP,    KC_END}
},

[_TB] = { /* Tab */
  {KC_ESC,   KC_CALC, KC_WHOM, KC_MAIL, KC_MYCM,  KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_PSCR,    KC_TRNS},
  {KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS},
  {KC_TRNS,  F(4),    F(5),    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS},
  {KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,   KC_MS_L,   KC_MS_D,    KC_MS_U,    KC_MS_R}
},

};

enum function_id {
    GNAPLED_TOGGLE,
    GNAPLED_STEP_MODE,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_ENT),
  [1]  = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay
  [2]  = ACTION_LAYER_MOMENTARY(2),  // to Fn overlay  
  [3]  = ACTION_LAYER_TAP_KEY(_TB, KC_TAB),
  [4]  = ACTION_FUNCTION(GNAPLED_TOGGLE),
  [5]  = ACTION_FUNCTION(GNAPLED_STEP_MODE),

};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {

}

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {
    case GNAPLED_TOGGLE:
      if (record->event.pressed) {
        gnaplight_toggle();
      }
      break;
    case GNAPLED_STEP_MODE:
      if (record->event.pressed) {
        gnaplight_step();
      }
      break;
  }
}
