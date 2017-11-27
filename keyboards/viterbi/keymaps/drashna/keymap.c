#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "drashna.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define LMACRO   TG(_MACROS)
#define DIABLO   TG(_DIABLO)
#define GAMEPAD  TG(_OVERWATCH)
#define MEDIA    TG(_MEDIA)
#define COVECUBE TG(_COVECUBE)

enum more_custom_keycodes {
  KC_KP_00 = NEW_SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_NUMLOCK] = KEYMAP(
      LMACRO,      DIABLO,      GAMEPAD,     KC_NLCK, KC_SLCK, KC_COLN, KC_PSLS,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      MEDIA,       KC_CALC,     COVECUBE,    KC_P7,   KC_P8,   KC_P9,   KC_PAST,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_HOME,     KC_DEL,      KC_PGUP,     KC_P4,   KC_P5,   KC_P6,   KC_PMNS,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_END,      KC_UP,       KC_PGDN,     KC_P1,   KC_P2,   KC_P3,   KC_PPLS,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_LEFT,     KC_DOWN,     KC_RGHT,     KC_P0,   KC_KP_00,KC_PDOT, KC_PENT,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
  ),

  [_DIABLO] = KEYMAP(
      KC_ESC,      DIABLO,      KC_V,        KC_D,        XXXXXXX,     XXXXXXX,     KC_L,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_TAB,      KC_S,        KC_F,        KC_I,        KC_M,        KC_T,        KC_J,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_Q,        KC_1,        KC_2,        KC_3,        KC_4,        KC_G,        KC_F,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_LCTL,     TD(TD_D3_1), TD(TD_D3_2), TD(TD_D3_3), TD(TD_D3_4), KC_Z,        KC_DIABLO_CLEAR,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_LALT,     KC_F4,       KC_F5,       KC_F8,       KC_F9,       KC_F10,      SFT_T(KC_SPACE),          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
  ),

  [_OVERWATCH] = KEYMAP(  // Game pad layout designed primarily for Overwatch
      LMACRO,      KC_ESC,      GAMEPAD,     KC_1,        KC_2,        KC_3,        KC_4,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      MEDIA,       KC_TAB,      KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_Z,        KC_LCTL,     KC_A,        KC_S,        KC_D,        KC_F,        KC_G,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_Y,        KC_LSFT,     KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_F1,       KC_U,        KC_I,        KC_Y,        KC_V,        KC_SPC,      KC_V,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
  ),

  [_MACROS] = KEYMAP(
      LMACRO,      XXXXXXX,     GAMEPAD,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_SYMM,     KC_TORB,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_GLHF,     KC_GOODGAME, XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_SALT,     KC_MORESALT, KC_SALTHARD, KC_JUSTGAME, KC_AIM,      XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
  ),

  [_COVECUBE] = KEYMAP(
      COVECUBE,    XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
  ),

  [_MEDIA] = KEYMAP(
      KC_RESET,KC_MAKE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      MEDIA,   XXXXXXX, RGB_SAI, RGB_VAI, RGB_M_P, RGB_M_B, RGB_M_R,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      RGB_TOG, RGB_MOD, RGB_SAD, RGB_VAD, RGB_M_SW,RGB_M_SN,RGB_M_K,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, RGB_M_K, RGB_M_X, RGB_M_G,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
  )


};


bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_KP_00:
    if (record->event.pressed) {
      register_code(KC_KP_0);
      unregister_code(KC_KP_0);
      register_code(KC_KP_0);
      unregister_code(KC_KP_0);
    }
    return false;
    break;
  }
  return true;
}





