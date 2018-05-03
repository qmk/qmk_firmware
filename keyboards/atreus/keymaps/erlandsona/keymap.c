// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define BASE 0
#define NUMS 1
#define MOUS 2

// Some quick aliases, just to make it look pretty
#define _______ KC_TRNS
#define XXXXXXX KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT( /* Qwerty */
    KC_Q       , KC_W   , KC_E   , KC_R   ,  KC_T   ,                 KC_Y  ,  KC_U   , KC_I   , KC_O   , KC_P          ,
    KC_A       , KC_S   , KC_D   , KC_F   ,  KC_G   ,                 KC_H  ,  KC_J   , KC_K   , KC_L   , KC_SCLN       ,
    SFT_T(KC_Z), KC_X   , KC_C   , KC_V   ,  KC_B   ,                 KC_N  ,  KC_M   , KC_COMM, KC_DOT , SFT_T(KC_QUOT),
    KC_LCTL    , KC_LALT, KC_LALT, KC_LGUI,  KC_BSPC, KC_ESC, KC_ENT, KC_SPC,  F(NUMS), KC_RALT, KC_SLSH, KC_BSLS
  ),

  [NUMS] = LAYOUT( /* Numbers / Arrows / Symbols */
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   ,                   KC_LPRN, KC_RPRN, KC_MINS, KC_EQL , KC_LBRC,
    KC_TAB , KC_5   , KC_6   , KC_7   , KC_8   ,                   KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_RBRC,
    _______, KC_9   , KC_0   , KC_DOT , KC_COMM,                   KC_HOME, KC_PGDN, KC_PGUP, KC_END , _______,
    _______, _______, _______, _______, KC_DEL , F(MOUS), _______, _______, _______, _______, _______, _______
  ),

  [MOUS] = LAYOUT( /* Mouse and Media Keys */
    KC_SLCK, KC_PAUSE, KC_F11 , KC_F10 , KC_F9  ,                   KC_F8  , KC_F7  , KC_F6  , KC_F5  , KC_F4,
    KC_VOLD, KC_ACL0 , KC_ACL1, KC_ACL2, KC_VOLU,                   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_F3,
    KC_MUTE, KC_MPRV , KC_MPLY, KC_MNXT, KC_MUTE,                   KC_WH_R, KC_WH_U, KC_WH_D, KC_WH_L, KC_F2,
    _______, _______ , _______, _______, _______, _______, _______, KC_BTN1, F(BASE), RESET  , KC_F12 , KC_F1
  ),
};


// I prefer this layer switching strategy to the TG and MO functions.
// so that I can get out of mouse mode just by tapping/holding my base layer FN key.
const uint16_t PROGMEM fn_actions[] = {
  [BASE] = ACTION_LAYER_OFF(2, 1),  // switch back to layer 0
  [NUMS] = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay
  [MOUS] = ACTION_LAYER_ON(2, 1)  // switch to layer 2
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        register_code(KC_RSFT);
      } else {
        unregister_code(KC_RSFT);
      }
    break;
  }
  return MACRO_NONE;
};
