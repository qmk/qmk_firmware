#include QMK_KEYBOARD_H
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
#define GAMEPAD  TG(_GAMEPAD)
#define MEDIA    TT(_MEDIA)
#define COVECUBE TG(_COVECUBE)


//enum more_custom_keycodes {
//  KC_P00 = NEW_SAFE_RANGE
//};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_NUMLOCK] = LAYOUT_ortho_5x7(
      LMACRO,  DIABLO,  GAMEPAD, KC_NLCK, KC_SLCK, KC_COLN, KC_PSLS,
      MEDIA,   KC_CALC, COVECUBE,KC_P7,   KC_P8,   KC_P9,   KC_PAST,
      KC_HOME, KC_DEL,  KC_PGUP, KC_P4,   KC_P5,   KC_P6,   KC_PMNS,
      KC_END,  KC_UP,   KC_PGDN, KC_P1,   KC_P2,   KC_P3,   KC_PPLS,
      KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT, KC_COLN, KC_PENT
  ),

  [_DIABLO] = LAYOUT_ortho_5x7(
      KC_ESC,  DIABLO,  KC_V,    KC_D,    XXXXXXX, XXXXXXX, KC_L,
      KC_TAB,  KC_S,    KC_F,    KC_I,    KC_M,    KC_T,    KC_J,
      KC_Q,    KC_1,    KC_2,    KC_3,    KC_4,    KC_G,    KC_F,
      KC_LCTL, KC_D3_3, KC_D3_3, KC_D3_3, KC_D3_3, KC_Z,    KC_DIABLO_CLEAR,
      KC_LALT, KC_F4,   KC_F5,   KC_F8,   KC_F9,   KC_F10,  SFT_T(KC_SPACE)
  ),

  [_GAMEPAD] = LAYOUT_ortho_5x7(  // Game pad layout designed primarily for Overwatch
      LMACRO,  KC_ESC,  GAMEPAD, KC_1,    KC_2,    KC_3,    KC_4,
      MEDIA,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
      KC_Z,    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
      KC_Y,    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
      KC_F1,   KC_U,    KC_I,    KC_Y,    KC_V,    KC_SPC,  KC_V
  ),

  [_MACROS] = LAYOUT_ortho_5x7(
      LMACRO,      KC_OVERWATCH,GAMEPAD,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,
      KC_C9,       XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,
      KC_SYMM,     KC_TORB,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,
      KC_GLHF,     KC_GOODGAME, KC_GGEZ,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,
      KC_SALT,     KC_MORESALT, KC_SALTHARD, KC_JUSTGAME, KC_AIM,      XXXXXXX,     KC_PENT
  ),

  [_COVECUBE] = LAYOUT_ortho_5x7(
      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,
      XXXXXXX,     XXXXXXX,     COVECUBE,    XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,
      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,
      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,
      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX
  ),

  [_MEDIA] = LAYOUT_ortho_5x7(
      KC_MAKE, KC_RESET,MU_TOG,  AU_ON,   AU_OFF,  CK_TOGG, RGB_SAD,
      MEDIA,   EPRM,    KC_RGB_T,RGB_M_P, RGB_M_B, RGB_M_R, RGB_SAI,
      RGB_TOG, RGB_MOD, RGB_RMOD,RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_HUD,
      KC_MPLY, KC_MPRV, KC_MNXT, RGB_M_X, RGB_M_G, RGB_M_P, RGB_HUI,
      KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, RGB_VAD, RGB_VAI
  )


};

void matrix_init_keymap(void) {
  DDRD &= ~(1<<5);
  PORTD &= ~(1<<5);

  DDRB &= ~(1<<0);
  PORTB &= ~(1<<0);
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {

  //switch (keycode) {
  //case KC_P00:
  //  if (!record->event.pressed) {
  //    register_code(KC_KP_0);
  //    unregister_code(KC_KP_0);
  //    register_code(KC_KP_0);
  //    unregister_code(KC_KP_0);
  //  }
  //  return false;
  //  break;
  //}
  return true;
}





