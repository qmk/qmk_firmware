#include "leader_user.h"
#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;
#endif
bool leader_succeed;

void matrix_scan_user(void) {
  static bool has_ran_yet;
  if (!has_ran_yet) {
    has_ran_yet = true;
    startup_user();
  }
#ifdef TAP_DANCE_ENABLE  // Run Diablo 3 macro checking code.
//  run_diablo_macro_check();
#endif 
#ifdef RGBLIGHT_ENABLE
  matrix_scan_rgb();
#endif

//  matrix_scan_keymap();
}

void leader_start_user(void) {
#ifdef RGBLIGHT_ENABLE
 rgblight_savebase();
 rgblight_mode_noeeprom(1);
 rgblight_sethsv_noeeprom(HSV_GOLDENROD);
#endif
}

void leader_end_user(void) {
  leader_succeed = false;

  if (leader_sequence_one_key(KC_W)) {
    // vim/tmux: Use in command mode in vim: write to file, switch tmux pane in the current session window and repeat the last command
    SEND_STRING(":w" SS_TAP(X_ENTER));
    tmux_pane_switch_repeat();
    leader_succeed = true;
  } else
  if (leader_sequence_one_key(KC_T)) {
    // Send the Tmux Prefix
    tmux_prefix();
    leader_succeed = true;
  } else
  if (leader_sequence_one_key(KC_A)) {
     // tmux: Send the prefix and press 'right' arrow
    tmux_prefix();
    tap_code(KC_RIGHT);
    leader_succeed = true;
  } else
  if (leader_sequence_two_keys(KC_T, KC_T)) {
    // tmux: Send the prefix to a nested session
    tmux_prefix();
    tmux_prefix();
    leader_succeed = true;
  } else
  if (leader_sequence_two_keys(KC_T, KC_R)) {
    // tmux: Switch pane and repeat last action
    tmux_pane_switch_repeat();
    leader_succeed = true;
  } else
  if (leader_sequence_two_keys(KC_V, KC_Z)){
    // vim: Zoom pane
    tap_code16(LCTL(KC_W));
    tap_code16(LSFT(KC_BSLS));
    leader_succeed = true;
  } else
  if (leader_sequence_two_keys(KC_V, KC_R)) {
    // vim: Substitute and place cursor
    SEND_STRING(":%s///g" SS_TAP(X_LEFT));
    tap_code(KC_LEFT);
    tap_code(KC_LEFT);
    leader_succeed = true;
  } else
  if (leader_sequence_two_keys(KC_V, KC_T)) {
    // vim: move current pane to new tab
    tap_code16(LCTL(KC_W));
    tap_code16(LSFT(KC_T));
    leader_succeed = true;
  } else
  if (leader_sequence_one_key(KC_R)){
    // Toggle RGB Layer indicator
    tap_code16(KC_RGB_T);
    leader_succeed = true;
  } else
  if (leader_sequence_one_key(KC_SPC)){
    // One Shot Unicode layer
//TODO      tap_code16(OS_UNI);
    leader_succeed = true;
  } else
  if (leader_sequence_two_keys(KC_SPC, KC_SPC)){
    // Toggle _MODS
    tap_code16(TG_MODS);
    leader_succeed = true;
  } else
  if (leader_sequence_three_keys(KC_BSPC, KC_BSPC, KC_BSPC)){
    // Reset the keyboard
    reset_keyboard();
    leader_succeed = true;
  }

// pick color depending of success /fail
// fade leader_start from 100 to 0
// fade new color from  0 to 100 to 0
// fade old color from 0 to 100
#ifdef RGBLIGHT_ENABLE
  if (leader_succeed) {
    fadeflash_leds(HSV_GREEN);
  } else {
    fadeflash_leds(HSV_RED);
  }
#endif
}
