#include "encoder.h"
bool encoder_update_user(uint8_t index, bool clockwise) {
  static uint16_t kc;
  uint8_t temp_mod = get_mods();
  if (index == 0) { /* first encoder */
    if (clockwise) {
      //if (temp_mod & MOD_BIT(KC_HYPR)){ // TODO: not how this works, only registers CTRL
        if ((temp_mod & MOD_MASK_CTRL) && (temp_mod & MOD_MASK_SHIFT) && (temp_mod & MOD_MASK_ALT) && (temp_mod & MOD_MASK_GUI)) { // HYPER
          kc = encoder_actions[0][8];
        } else if ( (temp_mod & MOD_MASK_SHIFT) && (temp_mod & MOD_MASK_ALT) ) {  // ALT+SHIFT
          kc = encoder_actions[0][7];
        } else if ( (temp_mod & MOD_MASK_SHIFT) && (temp_mod & MOD_MASK_CTRL) ) { // CTRL+SHIFT
          kc = encoder_actions[0][6];
        } else if ( (temp_mod & MOD_MASK_CTRL) && (temp_mod & MOD_MASK_ALT) ) {   // CTRL+ALT
          kc = encoder_actions[0][5];
        } else if (temp_mod & MOD_MASK_GUI) {   // GUI
          kc = encoder_actions[0][4];
        } else if (temp_mod & MOD_MASK_SHIFT) { // SHIFT
          kc = encoder_actions[0][3];
        } else if (temp_mod & MOD_MASK_ALT) {   // ALT
          kc = encoder_actions[0][2];
        } else if (temp_mod & MOD_MASK_CTRL) {  // CTRL
          kc = encoder_actions[0][1];
        } else {                                // None
          kc = encoder_actions[0][0];
        }
      } else { // Counter Clockwise
        if ((temp_mod & MOD_MASK_CTRL) && (temp_mod & MOD_MASK_SHIFT) && (temp_mod & MOD_MASK_ALT) && (temp_mod & MOD_MASK_GUI)) { // HYPER
          kc = encoder_actions[1][8];
        } else if ( (temp_mod & MOD_MASK_SHIFT) && (temp_mod & MOD_MASK_ALT) ) {  // ALT+SHIFT
          kc = encoder_actions[1][7];
        } else if ( (temp_mod & MOD_MASK_SHIFT) && (temp_mod & MOD_MASK_CTRL) ) { // CTRL+SHIFT
          kc = encoder_actions[1][6];
        } else if ( (temp_mod & MOD_MASK_CTRL) && (temp_mod & MOD_MASK_ALT) ) {   // CTRL+ALT
          kc = encoder_actions[1][5];
        } else if (temp_mod & MOD_MASK_GUI) {   // GUI
          kc = encoder_actions[1][4];
        } else if (temp_mod & MOD_MASK_SHIFT) { // SHIFT
          kc = encoder_actions[1][3];
        } else if (temp_mod & MOD_MASK_ALT) {   // ALT
          kc = encoder_actions[1][2];
        } else if (temp_mod & MOD_MASK_CTRL) {  // CTRL
          kc = encoder_actions[1][1];
        } else {                                // None
          kc = encoder_actions[1][0];
        }
      }
        clear_mods();
        tap_code16(kc);
        set_mods(temp_mod);
  } else if (index == 1){ // second Encoder
      if (clockwise) {
        tap_code(KC_0);
      } else{
        tap_code(KC_1);
      }
  }
    return true;
}
const uint16_t PROGMEM encoder_actions[][9] = { \
//  None     CTRL     ALT                SHIFT    GUI             CTRL+ALT             CTRL+SHFT ALT+SHFT      HYPER
  { KC_PGDN, KC_DOWN, KC_AUDIO_VOL_UP,   KC_END,  KC_WWW_FORWARD, KC_AUDIO_MUTE,       KC_RIGHT, LSFT(KC_TAB), KC_MEDIA_NEXT_TRACK}, \
  { KC_PGUP, KC_UP,   KC_AUDIO_VOL_DOWN, KC_HOME, KC_WWW_BACK,    KC_MEDIA_PLAY_PAUSE, KC_LEFT,  KC_TAB,       KC_MEDIA_PREV_TRACK}
};
