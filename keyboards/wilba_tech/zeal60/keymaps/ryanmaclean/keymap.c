// Ryan MacLean's layout for Zeal60
// Note that LGUI and RGUI are swapped with LALT and RALT respectively, for use with Macs
// Also note that Control has replaced Caps Lock, and that pressing left or right shift once
// will output left parenthese and right parenthese respectively. 
#include QMK_KEYBOARD_H

// [0,13] is either left key of split backspace (e.g. HHKB \| key) or 2U backspace
// [1,13] is either backslash or ISO Enter
// [2,12] is either ANSI Enter or key left of ISO Enter
// [2,13] is right key of split backspace (e.g. HHKB `~ key)
// [3,1] is right key of split left-shift (e.g ISO key)
// [3,13] is right key of split right-shift (e.g. HHKB Fn key)



const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // this is the function signature -- just copy/paste it into your keymap file as it is. KC_LSFT KC_LALT KC_LGUI KC_4
{
  switch(id) {
    case 0: // macOS screenshot to capture are to clipboard - this would trigger when you hit a key mapped as M(0)
      if (record->event.pressed) {
        return MACRO( D(LSFT), D(LCTL), D(LGUI), T(4), U(LSFT), U(LCTL), U(LGUI), W(255), END  ); // this sends the string 'hello' when the macro executes
      }
      break;
    case 1: // macOS screenshot capture area to file - this would trigger when you hit a key mapped as M(1)
      if (record->event.pressed) {
        return MACRO( D(LSFT), D(LGUI), T(4), U(LSFT), U(LGUI), W(255), END  ); // this sends the string 'hello' when the macro executes
      }
      break;
    case 2: // macOS screenshot to clipboard - this would trigger when you hit a key mapped as M(2)
      if (record->event.pressed) {
        return MACRO( D(LSFT), D(LCTL), D(LGUI), T(3), U(LSFT), U(LCTL), U(LGUI), W(255), END  ); // this sends the string 'hello' when the macro executes
      }
      break;
    case 3: // macOS screenshot to file - this would trigger when you hit a key mapped as M(3)
      if (record->event.pressed) {
        return MACRO( D(LSFT), D(LGUI), T(3), U(LSFT), U(LGUI), W(255), END  ); // this sends the string 'hello' when the macro executes
      }
      break;
  }
  return MACRO_NONE;
};

#define CADETL MT(KC_LSFT, KC_LBRC)
#define CADETR MT(KC_RSFT, KC_RBRC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Default layer
[0] = {
	{KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS},
	{KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC},
	{KC_LGUI, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_GRV},
	{KC_LSPO, KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, FN_MO13},
	{KC_LCTL, KC_LALT, KC_LGUI, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_SPC,  KC_NO,   KC_NO,   KC_RGUI, KC_RALT, KC_RCTL, FN_MO23}
},

// Fn1 Layer
[1] = {
	{KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS},
	{KC_CAPS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,  KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_DEL},
	{KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, KC_HOME, KC_PGUP, KC_TRNS, KC_TRNS},
	{KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_END,  KC_PGDN, KC_TRNS, KC_TRNS},
	{KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS}
},

// Fn2 Layer
[2] = {
	{KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
	{KC_TRNS, M(2), M(3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
	{KC_TRNS, M(1), M(0), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
	{KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
	{KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS}
},

// Fn3 Layer (zeal60 Configuration)
[3] = {
	{KC_TRNS, EF_DEC,  EF_INC,  H1_DEC,  H1_INC,  H2_DEC,  H2_INC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, BR_DEC,  BR_INC,  KC_TRNS},
	{KC_TRNS, KC_TRNS, KC_TRNS, S1_DEC,  S1_INC,  S2_DEC,  S2_INC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
	{KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
	{KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
	{KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS}
}

};
