#include "dactyl-manuform.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _SYMB 1
#define _NAV 2

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define SYMBOL  MO(_SYMB)
#define NAVIGN  MO(_NAV)
#define SFT_ENT RSFT_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = KEYMAP_4x6(
  // left hand
   KC_TAB,    KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,
   KC_ESC,    KC_A,    KC_S,    KC_D,   KC_F,   KC_G,
   KC_LSHIFT, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,
                       KC_LALT, KC_LGUI,
                               SYMBOL,  KC_SPC,
                               KC_LCTL, NAVIGN,
                               KC_LALT, KC_ENT,

        // right hand
                     KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC,
                     KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
                     KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, SFT_ENT,
                                      KC_RGUI, KC_RALT,
        KC_SPC, SYMBOL,
        NAVIGN, KC_RCTL,
        KC_ENT, KC_RALT),
[_SYMB] = KEYMAP_4x6(
  // left hand
   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,
   _______,  KC_2,     KC_3,     KC_4,     KC_5,     KC_6,
   _______,  KC_1,     _______,  _______,  KC_LBRC,  KC_GRV,
                       _______,  _______,
                               _______, _______,
                               _______, _______,
                               _______, _______,
        // right hand
                     KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,  KC_F12,
                     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS, KC_EQL,
                     KC_BSLS,  KC_RBRC,  _______,  _______,  _______, _______,
                                         _______,  _______,
        _______, _______,
        _______, _______,
        _______, _______),
[_NAV] = KEYMAP_4x6(
  // left hand
   KC_CAPS,  KC_PGUP,  KC_HOME,  KC_UP,    KC_END,   _______,
   _______,  KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_DEL,
   _______,  _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,
                       _______,  _______,
                               _______, _______,
                               _______, _______,
                               _______, _______,
        // right hand
                     _______,  KC_HOME,  KC_UP,    KC_END,   KC_PGUP, KC_INS,
                     KC_DEL,   KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_PGDN, _______,
                     _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  _______, _______,
                                         KC_APP,   KC_PSCR,
        _______, _______,
        _______, _______,
        _______, _______),
};



void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}
