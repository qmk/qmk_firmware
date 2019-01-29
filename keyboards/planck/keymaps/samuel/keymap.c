#include "planck.h"
#include "action_layer.h"

#define TAPPING_TERM 250

extern keymap_config_t keymap_config;

static uint16_t tap_timers[10]  = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

bool tap_interupted = false;

enum planck_layers {
  _DVORAK,
  _RISE
};

// where the 'T_' communicates how the key does something different when tapped.
enum planck_keycodes {
  DVORAK = SAFE_RANGE,
  RISE,
  KC_T_LALT,
  KC_T_RALT,
  KC_T_LGUI,
  KC_T_RGUI,
  KC_T_LCTL,
  KC_T_RCTL,
  KC_T_LSFT,
  KC_T_RSFT,
  KC_T_LRSE,
  KC_T_RRSE,
  KC_EZRGHT,
  KC_EZLEFT,
  KC_EZUP,
  KC_EZDOWN,
  KC_EZUNDO,
  KC_EZCOPY,
  KC_EZCUT,
  KC_EZPSTE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_DVORAK] =

{{ KC_T_LRSE, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_T_RRSE},
{ KC_T_LSFT, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_T_RSFT},
{ KC_T_LCTL, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_T_RCTL},
{ KC_T_LGUI, KC_T_LALT, KC_UP, KC_DOWN, KC_BSPC, KC_TAB, KC_ENT, KC_SPC, KC_LEFT, KC_RIGHT, KC_T_RALT, KC_T_RGUI}
},

[_RISE] =

{{ KC_TRANSPARENT, KC_EZUNDO, KC_EZCOPY, KC_EZCUT, KC_EZPSTE, KC_INS, KC_EQL, KC_7, KC_8, KC_9, KC_F11, KC_TRANSPARENT},
{ KC_TRANSPARENT, KC_ESC, KC_CAPS, KC_PGUP, KC_PGDN, KC_F4, KC_ASTR, KC_4, KC_5, KC_6, KC_0, KC_TRANSPARENT},
{ KC_TRANSPARENT, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_1, KC_2, KC_3, KC_F12, KC_TRANSPARENT},
{ KC_TRANSPARENT, KC_TRANSPARENT, KC_EZUP, KC_EZDOWN, KC_TRANSPARENT, KC_AMPR, KC_PIPE, KC_TRANSPARENT, KC_EZLEFT, KC_EZRGHT, KC_TRANSPARENT, KC_TRANSPARENT}
},

};

void mod_type(uint16_t modcode, uint16_t keycode) {
  register_mods(MOD_BIT(modcode));
  register_code(keycode);
  unregister_code(keycode);
  unregister_mods(MOD_BIT(modcode));
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case RISE:
      if (record->event.pressed) {
        layer_on(_RISE);
      } else {
        layer_off(_RISE);
      }
      return false;
      break;

case KC_T_LALT:
if (record->event.pressed) {
  tap_timers[0] = timer_read();
  tap_interupted = false;
  register_mods(MOD_BIT(KC_LALT));
 } else {
  unregister_mods(MOD_BIT(KC_LALT));
  if (!tap_interupted && timer_elapsed(tap_timers[0]) < TAPPING_TERM) {
    mod_type(KC_LSHIFT, KC_9);
    tap_interupted = true;
  }
 }
return false;
break;
case KC_T_RALT:
if (record->event.pressed) {
  tap_timers[1] = timer_read();
  tap_interupted = false;
  register_mods(MOD_BIT(KC_RALT));
 } else {
  unregister_mods(MOD_BIT(KC_RALT));
  if (!tap_interupted && timer_elapsed(tap_timers[1]) < TAPPING_TERM) {
    mod_type(KC_LSHIFT, KC_0);
    tap_interupted = true;
  }
 }
return false;
break;

case KC_T_LGUI:
if (record->event.pressed) {
  tap_timers[2] = timer_read();
  tap_interupted = false;
  register_mods(MOD_BIT(KC_LGUI));
 } else {
  unregister_mods(MOD_BIT(KC_LGUI));
  if (!tap_interupted && timer_elapsed(tap_timers[2]) < TAPPING_TERM) {
    SEND_STRING(SS_TAP(X_GRAVE));
    tap_interupted = true;
  }
 }
return false;
break;
case KC_T_RGUI:
if (record->event.pressed) {
  tap_timers[3] = timer_read();
  tap_interupted = false;
  register_mods(MOD_BIT(KC_RGUI));
 } else {
  unregister_mods(MOD_BIT(KC_RGUI));
  if (!tap_interupted && timer_elapsed(tap_timers[3]) < TAPPING_TERM) {
    SEND_STRING(SS_TAP(X_BSLASH));
    tap_interupted = true;
  }
 }
return false;
break;

case KC_T_LCTL:
if (record->event.pressed) {
  tap_timers[4] = timer_read();
  tap_interupted = false;
  register_mods(MOD_BIT(KC_LCTL));
 } else {
  unregister_mods(MOD_BIT(KC_LCTL));
  if (!tap_interupted && timer_elapsed(tap_timers[4]) < TAPPING_TERM) {
    SEND_STRING(SS_TAP(X_LBRACKET));
    tap_interupted = true;
  }
 }
return false;
break;
case KC_T_RCTL:
if (record->event.pressed) {
  tap_timers[5] = timer_read();
  tap_interupted = false;
  register_mods(MOD_BIT(KC_RCTL));
 } else {
  unregister_mods(MOD_BIT(KC_RCTL));
  if (!tap_interupted && timer_elapsed(tap_timers[5]) < TAPPING_TERM) {
    SEND_STRING(SS_TAP(X_RBRACKET));
    tap_interupted = true;
  }
 }
return false;
break;

case KC_T_LSFT:
if (record->event.pressed) {
  tap_timers[6] = timer_read();
  tap_interupted = false;
  register_mods(MOD_BIT(KC_LSFT));
 } else {
  unregister_mods(MOD_BIT(KC_LSFT));
  if (!tap_interupted && timer_elapsed(tap_timers[6]) < TAPPING_TERM) {
    SEND_STRING(SS_TAP(X_EQUAL));
    tap_interupted = true;
  }
 }
return false;
break;
case KC_T_RSFT:
if (record->event.pressed) {
  tap_timers[7] = timer_read();
  tap_interupted = false;
  register_mods(MOD_BIT(KC_RSFT));
 } else {
  unregister_mods(MOD_BIT(KC_RSFT));
  if (!tap_interupted && timer_elapsed(tap_timers[7]) < TAPPING_TERM) {
    SEND_STRING(SS_TAP(X_MINUS));
    tap_interupted = true;
  }
 }
return false;
break;

case KC_T_LRSE:
if (record->event.pressed) {
  tap_timers[8] = timer_read();
  tap_interupted = false;
  layer_on(_RISE);
 } else {
  layer_off(_RISE);
  if (!tap_interupted && timer_elapsed(tap_timers[8]) < TAPPING_TERM) {
    SEND_STRING(SS_TAP(X_DELETE));
    tap_interupted = true;
  }
 }
return false;
break;
case KC_T_RRSE:
if (record->event.pressed) {
  tap_timers[9] = timer_read();
  tap_interupted = false;
  layer_on(_RISE);
 } else {
  layer_off(_RISE);
  if (!tap_interupted && timer_elapsed(tap_timers[9]) < TAPPING_TERM) {
    SEND_STRING(SS_TAP(X_SLASH));
    tap_interupted = true;
  }
 }
return false;
break;

case KC_EZRGHT:
if (record->event.pressed) {
  mod_type(LCTL(KC_LSHIFT), KC_RGHT);
 }
return false;
break;
case KC_EZLEFT:
if (record->event.pressed) {
  mod_type(LCTL(KC_LSHIFT), KC_LEFT);
 }
return false;
break;
case KC_EZDOWN:
if (record->event.pressed) {
  mod_type(LCTL(KC_LSHIFT), KC_DOWN);
 }
return false;
break;
case KC_EZUP:
if (record->event.pressed) {
  mod_type(LCTL(KC_LSHIFT), KC_UP);
 }
return false;
break;
case KC_EZUNDO:
if (record->event.pressed) {
  mod_type(KC_LCTL, KC_Z);
}
return false;
break;
case KC_EZCOPY:
if (record->event.pressed) {
  mod_type(KC_LCTL, KC_C);
}
return false;
break;
case KC_EZCUT:
if (record->event.pressed) {
  mod_type(KC_LCTL, KC_X);
}
return false;
break;
case KC_EZPSTE:
if (record->event.pressed) {
  mod_type(KC_LCTL, KC_V);
}
return false;
break;

  }
  tap_interupted = true;
  return true;
}
