#include "llama.h"

extern keymap_config_t keymap_config;

enum custom_keycodes {
  RGB_DEC = SAFE_RANGE,
  NAV_FN,
  NUM_SYM,
  NUM_PAD
};

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all neniceniceed to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _NAV_FN 4
#define _NUM_SYM 5
#define _NUM_SYM_SFT 6
#define _NUMPAD 8

#define _ADJUST 15

// Fillers to make layering more clear
#define _______ KC_TRNS
#define ___X___ KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  
  [_QWERTY] = LLAMA_KEYMAP( \
    KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_ESC , KC_TAB , KC_BSPC, KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , \
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_P7  , KC_P8  , KC_P9  , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC, \
    KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_P4  , KC_P5  , KC_P6  , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_P1  , KC_P2  , KC_P3  , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT, \
    KC_LCTL, KC_CAPS, KC_LGUI, KC_LALT, KC_SPC , NAV_FN , KC_P0  , KC_P0  , KC_PDOT, NUM_SYM, KC_SPC , NUM_PAD, ___X___, ___X___, ___X___  \
  ),
  
  [_NAV_FN] = LLAMA_KEYMAP( \
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, ___X___, ___X___, ___X___, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS, \
    KC_ESC , KC_HOME, KC_UP  , KC_END , KC_PGUP, KC_INS , ___X___, ___X___, ___X___, ___X___, KC_F1  , KC_F2  , KC_F3  , KC_F4  , _______, \
    _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_DEL , ___X___, ___X___, ___X___, KC_BSLS, KC_F5  , KC_F6  , KC_F7  , KC_F8  , ___X___, \
    _______, ___X___, ___X___, ___X___, KC_BSPC, KC_ENT , ___X___, ___X___, ___X___, KC_ENT , KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______, \
    _______, _______, _______, _______, _______, _______, ___X___, ___X___, ___X___, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS  \
  ),
  
  [_NUM_SYM] = LLAMA_KEYMAP( 
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, ___X___, ___X___, ___X___, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS, \
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , ___X___, ___X___, ___X___, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______, \
    _______, ___X___, KC_LCBR, KC_RCBR, ___X___, KC_DEL , ___X___, ___X___, ___X___, KC_BSLS, KC_MINS, KC_LBRC, KC_RBRC, KC_SCLN, KC_QUOT, \
    _______, ___X___, KC_LT  , KC_GT  , KC_BSPC, KC_ENT , ___X___, ___X___, ___X___, KC_ENT , KC_EQL , KC_COMM, KC_DOT , KC_SLSH, _______, \
    _______, _______, _______, _______, _______, _______, ___X___, ___X___, ___X___, _______, _______, _______, _______, _______, _______  \
  ),
  
  [_NUM_SYM_SFT] = LLAMA_KEYMAP( 
    KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , ___X___, ___X___, ___X___, KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , \
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, ___X___, ___X___, ___X___, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
    _______, ___X___, KC_LBRC, KC_RBRC, ___X___, KC_DEL , ___X___, ___X___, ___X___, KC_PIPE, KC_UNDS, KC_LCBR, KC_RCBR, KC_COLN, KC_DQT , \
    _______, ___X___, KC_LPRN, KC_RPRN, KC_BSPC, KC_ENT , ___X___, ___X___, ___X___, KC_ENT , KC_PLUS, KC_LT  , KC_GT  , KC_QUES, _______, \
    _______, _______, _______, _______, _______, _______, ___X___, ___X___, ___X___, _______, _______, _______, _______, _______, _______  \
  ),
  
  [_NUMPAD] = LLAMA_KEYMAP( \
    _______, _______, _______, _______, _______, _______, ___X___, ___X___, ___X___, ___X___, ___X___, KC_PSLS, KC_PAST, ___X___, _______, \
    _______, _______, _______, _______, _______, _______, ___X___, ___X___, ___X___, KC_PAST, KC_P7  , KC_P8  , KC_P9  , KC_PMNS, _______, \
    _______, _______, _______, _______, _______, _______, ___X___, ___X___, ___X___, KC_PSLS, KC_P4  , KC_P5  , KC_P6  , KC_PPLS, KC_PENT, \
    _______, _______, _______, _______, _______, _______, ___X___, ___X___, ___X___, KC_P0  , KC_P1  , KC_P2  , KC_P3  , KC_PSLS, _______, \
    _______, _______, _______, _______, _______, _______, ___X___, ___X___, ___X___, _______, KC_P0  , _______, KC_PDOT, KC_PAST, _______  \
  ),
  
  
  [_ADJUST] = LLAMA_KEYMAP( \
    ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, \
    RESET,   ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, DEBUG  , \
    ___X___, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, \
    ___X___, RGB_HUD, RGB_SAD, RGB_VAD, RGB_DEC, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, \
    ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, _______, ___X___, _______, ___X___, ___X___, ___X___  \
  )
  
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_DEC:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_step_reverse();
        #endif
      }
      return false;
      
    case NAV_FN:
      if (record->event.pressed) {
        layer_on(_NAV_FN);
      } else {
        layer_off(_NAV_FN);
      }
      update_tri_layer(_NAV_FN, _NUM_SYM, _NUM_SYM_SFT);
      return false;

    case NUM_SYM:
      if (record->event.pressed) {
        layer_on(_NUM_SYM);
      } else {
        layer_off(_NUM_SYM);
      }
      update_tri_layer(_NAV_FN, _NUM_SYM, _NUM_SYM_SFT);
      update_tri_layer(_NUMPAD, _NUM_SYM, _ADJUST);
      return false;

    case NUM_PAD:
      if (record->event.pressed) {
        layer_on(_NUMPAD);
      } else {
        layer_off(_NUMPAD);
      }
      update_tri_layer(_NUMPAD, _NUM_SYM, _ADJUST);
      return false;
  }
  return true;
}
