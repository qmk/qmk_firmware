#include QMK_KEYBOARD_H
#include "vosechu.h"

extern keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_ortho_half_5x7( // Base layer
  KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_9    ,
  ALT_TAB , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , TT(TT1) ,
  CTL_ESC , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , TT(TT2) ,
  KC_F13  , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , TT(TT3) ,
  KC_MEH  , CTL_GRV , ALT_TAB , KC_LALT , MO(LWR) , LFT_BK  , SFT_SPC
),
[LWR] = LAYOUT_ortho_half_5x7( // EVE layer
  _______   , _______ , _______ , _______ , _______ , _______ , _______ ,
  A(KC_LEFT), KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F9   ,
  SFT_SPC   , A(KC_F1), A(KC_F2), A(KC_F3), A(KC_F4), _______ , _______ ,
  A(KC_RGHT), C(KC_F1), C(KC_F2), C(KC_F3), C(KC_F4), _______ , _______ ,
  _______   , RESET   , _______ , _______ , _LAYER_ , KC_DEL  , KC_ENT
),
[LFT] = LAYOUT_ortho_half_5x7( // Media
  _______ , KC_F10  , KC_F11  , KC_F12  , KC_PSCR , KC_SLCK , KC_PAUS ,
  _______ , KC_F7   , KC_F8   , KC_F9   , KC_INS  , KC_HOME , KC_PGUP ,
  RGB_TOG , KC_F4   , KC_F5   , KC_F6   , KC_DEL  , KC_END  , KC_PGDN ,
  _______ , KC_F1   , KC_F2   , KC_F3   , KC_VOLU , KC_VOLD , KC_MUTE ,
  _______ , _______ , _______ , _______ , PSWD    , _LAYER_ , PSWD_ALT
),
[TT1] = LAYOUT_ortho_half_5x7( // Override WASD with arrows
  _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
  _______ , _______ , KC_UP   , _______ , _______ , _______ , _______ ,
  _______ , KC_LEFT , KC_DOWN , KC_RGHT , _______ , _______ , _______ ,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
  _______ , _______ , _______ , _______ , _______ , _______ , _______
),
[TT2] = LAYOUT_ortho_half_5x7( // Browser layer
  C(KC_W) , C(KC_1) , C(KC_T) , C(KC_9) , _______ , _______ , _______ ,
  WBWSRBK , WTABLFT , KC_UP   , WTABRGT , WBWSRFW , _______ , _______ ,
  KC_ESC  , KC_LEFT , KC_DOWN , KC_RGHT , C(KC_R) , _______ , _______ ,
  _______ , _______ , _______ , _______ , _______ , _______ , TT(T23X),
  _______ , _______ , _______ , _______ , _______ , _______ , _______
),
[TT3] = LAYOUT_ortho_half_5x7( // OS X override layer
  _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
  _______ , _______ , _______ , _______ , _______ , _______ , TT(T23X),
  _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
  _______ , _______ , _______ , KC_LGUI , _______ , _______ , _______
),
[T23X] = LAYOUT_ortho_half_5x7( // Browser layer
  G(KC_W) , G(KC_1) , G(KC_T) , G(KC_9) , _______ , SLACKTB , _______ ,
  BWSR_BK , TAB_LFT , KC_UP   , TAB_RGT , BWSR_FW , SLACKUP , _______ ,
  KC_ESC  , KC_LEFT , KC_DOWN , KC_RGHT , G(KC_R) , SLACKDN , _______ ,
  _______ , _______ , KC_Q    , KC_J    , KC_K    , _______ , _______ ,
  _______ , _______ , _______ , KC_LGUI , _______ , _______ , _______
),
// [_EMPTY] = LAYOUT(
//   _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
//   _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
//   _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
//   _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
//   _______ , _______ , _______ , _______ , _______ , _______ , _______
// ),
};

void keyboard_post_init_user(void) {
    // Call the post init code.
    rgblight_enable_noeeprom(); // enables Rgb, without saving settings
    rgblight_mode_noeeprom(0);
    rgblight_sethsv_noeeprom(0, 0, 0);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
  case TT1:
    rgblight_sethsv_noeeprom(HSV_BLUE);
    break;
  case TT2:
    rgblight_sethsv_noeeprom(HSV_PURPLE);
    break;
  case T23X:
    rgblight_sethsv_noeeprom(HSV_GOLD);
    break;
  case TT3:
    rgblight_sethsv_noeeprom(HSV_GREEN);
    break;
  default: //  for any other layers, or the default layer
    rgblight_sethsv_noeeprom(0, 0, 0);
    break;
  }

  return state;
}

void suspend_power_down_user(void) {
    rgblight_disable();
}

void suspend_wakeup_init_user(void) {
    rgblight_enable();
}


// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     case TT1:
//       if (record->event.pressed) {

//       } else {

//       }
//       return false;
//       break;
//   }
//   return true;
// }
