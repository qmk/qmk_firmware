#include "_keymap.h"
#include "repeat_command.h"

void run_command(const char string[]) {
  SEND_STRING(SS_LGUI("r"));
  wait_ms(400);
  send_string(string);
  SEND_STRING(SS_TAP(X_ENTER));
}

void vs_snippet(const char string[]) {
  send_string(string);
  wait_ms(200);
  SEND_STRING(SS_TAP(X_TAB));
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode)
    {
      case EMAIL:   send_string("ma.van.manen@live.nl"); return false;
      case CMD:     run_command("cmd");                  return false;
      case UBUNTU:  run_command("ubuntu.exe");           return false;
      case VS_PROP: vs_snippet("prop");                  return false;
      case PASTEX:  repeat_command(SS_LCTRL("v"));       return false;
    }
  }
  else {
    if(repeat_command_check(keycode)) return false;
  }

  return true;
}

// uint32_t layer_state_set_user(uint32_t state)
// {
//   switch (biton32(state))
//   {

//   }

//   return state;
// }

KEYMAPS = {
[_MA] = KC_KEYMAP(
  ESC,      Q,    W,	  E,   R,	 T,   Y,   U,   I,	  O,	  P,	   EQL,    BACKSPACE,
  GUI_TAB,	 A,    S,   D,   F,   G,   H,   J,   K,     L,    SCLN,        ENTER,
  LSHFT_SLSH, Z,    X,	  C,	  V,   B,	  N,   M,  COMM, DOT,  RSHFT_QUOT, PN,
  LCTRL,   LGUI, LALT, FN2, SPC_FN1,   SPC_FN,     LEFT, DOWN, UP,      RIGHT),

[_FN] = KEYMAP(
  _______,		KC_VOLD,	KC_VOLU,	KC_MUTE,	RESET,		_______,	_______,	KC_CALC,	KC_HOME,		KC_PGUP,	KC_PSCR,	KC_SLCK,	KC_DEL,
  KC_CAPS,		KC_MPRV,	KC_MPLY,	KC_MNXT,	_______,	_______,	_______,	_______,	KC_END,	KC_PGDN,	KC_INS,					_______,
  _______,		S(KC_LBRC),	S(KC_9),	KC_LBRC,	_______,	_______,	_______,	_______,	_______,		_______,		_______,				_______,
  _______,		_______,	_______,	_______,	_______, 				_______,				_______,	_______,	_______,				_______),

[_FN1] = KEYMAP(
  KC_GRV,		KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,		KC_F12,
  KC_1,			KC_2,		KC_3,		KC_4,		KC_5,		KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,				KC_EQL,
  _______,		_______,	_______,	_______,	_______,	_______,	_______,	KC_LBRC,	KC_RBRC,	KC_BSLS,	_______, _______,
  _______,		_______,	_______,	_______,	_______, _______,	_______,	_______,	_______, _______),

[_FN2] = KEYMAP(
  CMD,	UBUNTU,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
  _______,		_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,  _______,
  _______,		_______,	_______,	_______,	PASTEX,	  _______,	_______,	EMAIL,  	_______,	_______,  	_______,	_______,
  _______,		_______,	_______,	_______,	_______, 				_______,			_______,	_______,	_______,  _______),

[_PN] = KEYMAP(
  _______,		_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	VS_PROP,	_______,	_______,
  _______,		_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______, _______, 	_______,
  _______,		_______,	_______,	VS_ADD_CLASS,	_______,	_______,	_______,	_______,	_______,	_______, _______,	  _______,
  _______,		_______,	_______,	_______,	_______,  _______,  _______,	_______,	_______, _______),
};
