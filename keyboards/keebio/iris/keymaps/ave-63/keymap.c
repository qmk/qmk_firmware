/* Features of this keymap:

--Lots of functionality on left hand for conjunction with mouse or pen in right hand
--_COMMAND layer ESDF arrow keys
--_MEH layer ESDF is super handy for switching tabs (SF) and apps (ED)
--_MEH layer other keys are linked with my AutoHotKey script
--macro for handling parentheses is very nice (credit: u/drashna)

Some things are very non-standard, like position of number keys, etc.
Will require heavy modification for most people.
*/
#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define MODS_SHIFT_MASK (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))

enum my_layers {
  _QWERTY,
  _SYMBOL,
  _COMMAND,
  _MEH
};

enum custom_keycodes {
    KC_MPRN = SAFE_RANGE,
    KC_MBRC,
    KC_MCBR,
    KC_MABK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
   KC_ESC,  KC_GRV,  KC_AT, KC_BSLS,   KC_NO, TG(_SYMBOL),                     KC_NO, KC_LGUI, KC_MBRC, KC_RBRC,   KC_NO,  KC_DEL,
   KC_TAB,  KC_Q,    KC_W,     KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
   KC_LCTL, KC_A,    KC_S,     KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, MO(_SYMBOL),
   KC_LALT, KC_Z,    KC_X,     KC_C,    KC_V,    KC_B, MO(_MEH),       KC_QUOT, KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
                                 KC_NO,  KC_LSFT, MO(_COMMAND),            KC_ENT,  KC_SPC, KC_NO
),
[_SYMBOL] = LAYOUT(
   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
   KC_TRNS,  KC_EQL,    KC_9,    KC_8,    KC_7, KC_PLUS,                    KC_HASH, KC_UNDS, KC_MCBR, KC_RCBR, KC_TRNS, KC_TRNS, 
   KC_TRNS,    KC_0,    KC_6,    KC_5,    KC_4, KC_MINS,                    KC_CIRC, KC_AMPR, KC_MPRN, KC_RPRN, KC_RBRC, KC_TRNS, 
   KC_TRNS, KC_SLSH,    KC_3,    KC_2,    KC_1, KC_ASTR, KC_TRNS,  KC_TRNS, KC_EXLM, KC_DLR,  KC_MABK, KC_TRNS, KC_TRNS, KC_TRNS, 
                                 KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,  KC_TRNS,  KC_TRNS 
),
[_COMMAND] = LAYOUT(
    KC_APP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
   KC_TRNS, KC_PGUP, KC_HOME,   KC_UP,  KC_END, KC_VOLU,                    KC_SCRL,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_TRNS, 
   KC_TRNS, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD,                    KC_CAPS,   KC_F5,   KC_F6,   KC_F7,   KC_F8, KC_TRNS, 
   KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_TRNS, KC_MUTE, KC_TRNS,  KC_TRNS, KC_PAUS,   KC_F1,   KC_F2,   KC_F3,   KC_F4, KC_TRNS, 
                                 KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,  KC_TRNS,  KC_TRNS 
),
[_MEH] = LAYOUT(
   LALT(KC_F4), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT, 
   KC_TRNS, MEH(KC_Q), LCTL(KC_W), LSFT(KC_TAB), KC_DEL, MEH(KC_T),          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
   KC_TRNS, MEH(KC_A),LSFT(LCTL(KC_TAB)),KC_TAB,LCTL(KC_TAB),MEH(KC_G),      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
   KC_TRNS,MEH(KC_Z),MEH(KC_X),MEH(KC_C),MEH(KC_V),MEH(KC_B),KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
                                 KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,  KC_TRNS,  KC_TRNS 
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t code_timer;
  switch (keycode) {
  case KC_MCBR:                                  
    if(record->event.pressed){
      code_timer= timer_read();
      SEND_STRING("{");
    } else {
      if (timer_elapsed(code_timer) > TAPPING_TERM) {
        SEND_STRING("}" SS_TAP(X_LEFT));
      } 
    }
    return false;
    break;
  case KC_MBRC:                                  
    if(record->event.pressed){
      code_timer= timer_read();
      SEND_STRING("[");
    } else {
      if (timer_elapsed(code_timer) > TAPPING_TERM) {
        SEND_STRING("]" SS_TAP(X_LEFT));
      } 
    }
    return false;
    break;
  case KC_MPRN:                                  
    if(record->event.pressed){
      code_timer= timer_read();
      SEND_STRING("(");
    } else {
      if (timer_elapsed(code_timer) > TAPPING_TERM) {
        SEND_STRING(")" SS_TAP(X_LEFT));
      } 
    }
    return false;
    break;
  case KC_MABK:                                  
    if(record->event.pressed){
      code_timer= timer_read();
      if (get_mods() & MODS_SHIFT_MASK){
        SEND_STRING("<");
      } else {
        SEND_STRING(",");
      }
    } else {
      if (timer_elapsed(code_timer) > TAPPING_TERM) {
        if (get_mods()  & MODS_SHIFT_MASK){
          SEND_STRING(">" SS_TAP(X_LEFT));
        }
      } 
    }
    return false;
    break;
  }
  return true;
}