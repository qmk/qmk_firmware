
#include "minorca.h"
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

// Macro name shortcuts
#define QWERTY M(_QWERTY)
#define LOWER M(_LOWER)
#define RAISE M(_RAISE)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = { /* Qwerty */
  {KC_ESC,     KC_Q,       KC_W,       KC_E,       KC_R,     KC_T,    KC_Y,     KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC},
  {FUNC(0),    KC_A,       KC_S,       KC_D,       KC_F,     KC_G,    KC_H,     KC_J,       KC_K,       KC_L,       XXXXXXX,    KC_QUOT},
  {KC_LSFT,    XXXXXXX,    KC_Z,       KC_X,       KC_C,     KC_V,    KC_B,     KC_N,       KC_M,       KC_COMM,    KC_DOT,     FUNC(1)},
  {KC_LCTL,    XXXXXXX,    KC_LGUI,    KC_LALT,    FUNC(2),  XXXXXXX, XXXXXXX,  FUNC(3),    XXXXXXX,    KC_RALT,    KC_APP,     KC_RCTL}
},

[_RAISE] = {
  {S(KC_GRV),  S(KC_1),    S(KC_2),    S(KC_3),    S(KC_4),  S(KC_5), S(KC_6),  S(KC_7),    S(KC_8),    S(KC_9),    S(KC_0),    KC_BSPC},
  {KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_PAUSE,   KC_TRNS,  KC_TRNS, KC_TRNS,  S(KC_MINS), S(KC_EQL),  S(KC_LBRC), XXXXXXX,    S(KC_BSLS)},
  {KC_TRNS,    XXXXXXX,    KC_F1,      KC_F2,      KC_F3,    KC_F4,   KC_F5,    KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_ENT},
  {KC_TRNS,    XXXXXXX,    KC_TRNS,    KC_TRNS,    KC_TRNS,  XXXXXXX, XXXXXXX,  KC_TRNS,    XXXXXXX,    KC_MNXT,    KC_MUTE,    KC_MPLY}
},

[_LOWER] = {
  {KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,     KC_5,    KC_6,     KC_7,       KC_8,       KC_9,       KC_0,       KC_DELETE},
  {KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS, KC_TRNS,  KC_MINS,    KC_EQL,     KC_LBRC,    XXXXXXX,    KC_BSLS},
  {KC_TRNS,    XXXXXXX,    KC_F11,     KC_F12,     KC_F13,   KC_F14,  KC_F15,   KC_F16,     KC_F17,     KC_F18,     KC_PGUP,    KC_ENT},
  {KC_TRNS,    XXXXXXX,    KC_TRNS,    KC_TRNS,    KC_TRNS,  XXXXXXX, XXXXXXX,  KC_TRNS,    XXXXXXX,    KC_HOME,    KC_PGDN,    KC_END}
},

[_TB] = { /* Tab */
  {KC_ESC,     KC_CALC,    KC_WHOM,    KC_MAIL,    KC_MYCM,  KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_PSCR,    KC_TRNS},
  {KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    XXXXXXX,    KC_TRNS},
  {KC_TRNS,    XXXXXXX,    RGB_TOG,    RGB_MOD,    RGB_HUI,  RGB_HUD, RGB_SAI,  RGB_SAD,    RGB_VAI,    RGB_VAD,    KC_UP,      KC_ENT},
  {BL_STEP,    XXXXXXX,    KC_TRNS,    KC_TRNS,    KC_TRNS,  XXXXXXX, XXXXXXX,  KC_TRNS,    XXXXXXX,    KC_LEFT,    KC_DOWN,    KC_RGHT}
}
};


const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_LAYER_TAP_KEY(_TB, KC_TAB),
  [1]  = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_ENT),
  [2]  = ACTION_LAYER_TAP_KEY(_RAISE, KC_SPC),
  [3]  = ACTION_LAYER_TAP_KEY(_LOWER, KC_SPC),
};
