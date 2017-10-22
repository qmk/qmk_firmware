#include "frosty_flake.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"

enum QFR_layers {
  _COLEMAK,
  _LOWER,
  _MOUSE
};

enum QFR_keycodes {
  COLEMAK = SAFE_RANGE,
  LOWER,
  MOUSE
};

  const uint16_t PROGMEM fn_actions[] = { //ACTION_LAYER_TAP_TOGGLE requires that number of taps be defined in *config.h* - default set to 5
      [0] = ACTION_LAYER_TAP_KEY(_LOWER, KC_SPC),    //Hold for momentary Lower layer, Tap for Space, 
      [1] = ACTION_LAYER_TAP_TOGGLE(_LOWER),         //Hold for momentary Mouse, Tap for toggle Mouse
      [2] = ACTION_LAYER_TAP_TOGGLE(_MOUSE),         //Hold for momentary Lower, Tap for toggle Lower
   };
#define SPC_LW FUNC(0)
#define LWR FUNC(1)
#define MSE FUNC(2)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK] = KEYMAP_TKL(\
      KC_ESC,    KC_F1,     KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_PSCR,KC_SLCK,KC_PAUS, \
      KC_GRV,    KC_1,      KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL, KC_BSPC,  KC_INS, KC_HOME,KC_PGUP, \
      KC_TAB,    KC_Q,      KC_W,   KC_F,   KC_P,   KC_G,   KC_J,   KC_L,   KC_U,   KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC,KC_BSLS,  KC_DEL, KC_END, KC_PGDN, \
      KC_BSPC,   KC_A,      KC_R,   KC_S,   KC_T,   KC_D,   KC_H,   KC_N,   KC_E,   KC_I,    KC_O,    KC_QUOT,         KC_ENT ,                           \
      KC_LSPO,KC_NUBS,KC_Z, KC_X,   KC_C,   KC_V,   KC_B,   KC_K,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,          KC_RSPC,                   KC_UP,          \
      KC_LCTL,KC_LGUI,      KC_LALT,                SPC_LW,                                  MSE,     KC_RGUI, KC_APP, KC_RCTL,  KC_LEFT,KC_DOWN,KC_RGHT
      ),

[_LOWER] = KEYMAP_TKL(\
      RESET,    _______,    _______,   _______,  _______, _______,   _______,   _______,   _______,  _______, _______, _______, _______,           _______,_______,_______, \
      KC_TILD,  KC_EXLM,    KC_AT,     KC_HASH,  KC_DLR,  KC_PERC,   KC_CIRC,   KC_AMPR,   KC_ASTR,  KC_LBRC, KC_RBRC, KC_UNDS, KC_PLUS, KC_BSPC,  _______,_______,_______, \
      KC_TAB,   KC_PGUP,    KC_HOME,   KC_UP,    KC_END,  XXXXXXX,   XXXXXXX,   KC_BTN3,   KC_BTN4,  KC_BTN5, XXXXXXX, KC_LCBR, KC_RCBR, KC_PIPE,  _______,_______,_______, \
      KC_CAPS,  KC_PGDN,    KC_LEFT,   KC_DOWN,  KC_RGHT, XXXXXXX,   XXXXXXX,   KC_BTN1,   KC_BTN2,  XXXXXXX, XXXXXXX, _______,          _______,                            \
      _______,XXXXXXX,_______,_______, _______,  _______, XXXXXXX,   XXXXXXX,   XXXXXXX,   _______,  _______, _______,                   _______,          _______,          \
      _______,  _______,    _______,             _______,                       KC_RALT,   _______,  _______, _______,                            _______,_______,_______  \
      ),

[_MOUSE] = KEYMAP_TKL(\
      _______,  _______,   _______,   _______,  _______, _______,   _______,   _______,   _______,  _______, _______, _______, _______,            _______,_______,_______, \
      KC_GRV,   KC_1,      KC_2,      KC_3,     KC_4,    KC_5,      KC_6,      KC_7,      KC_8,     KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL,    _______,_______,_______, \
      KC_TAB,   KC_WH_U,   KC_WH_L,   KC_MS_U,  KC_WH_R, XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS,   _______,_______,_______, \
      KC_BSPC,  KC_WH_D,   KC_MS_L,   KC_MS_D,  KC_MS_R, XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX, XXXXXXX, _______,          _______,                             \
      _______,XXXXXXX,KC_Z,KC_X,      KC_C,     KC_V,    XXXXXXX,   XXXXXXX,   XXXXXXX,   _______,  _______,  _______,                  _______,           _______,          \
      _______,  _______,   _______,             KC_ACL2,                       MSE,       _______,  _______,  _______,                             _______,_______,_______  \
      )
};
