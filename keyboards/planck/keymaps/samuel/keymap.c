#include "planck.h"
#include "action_layer.h"

#define TAPPING_TERM 250

extern keymap_config_t keymap_config;

static uint16_t alt_timers[2]  = { 0, 0};

bool altInterupted = false;

enum planck_layers {
  _DVORAK,
  _RISE
};

enum planck_keycodes {
  DVORAK = SAFE_RANGE,
  RISE,
  LALT,
  RALT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_DVORAK] =

{{ LT(_RISE, KC_DEL), KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, LT(_RISE, KC_SLSH)},
{ LSFT_T(KC_EQL), KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, RSFT_T(KC_MINUS)},
{ LCTL_T(KC_LBRC), KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, RCTL_T(KC_RBRC)},
{ LGUI_T(KC_GRAVE), LALT, KC_LEFT, KC_RGHT, KC_BSPC, KC_TAB, KC_ENT, KC_SPC, KC_UP, KC_DOWN, RALT, RGUI_T(KC_BSLASH)}
},

[_RISE] =

{{ KC_TRNS, LCTL(KC_Z), LCTL(KC_C), LCTL(KC_X), LCTL(KC_V), KC_INS, KC_EQL, KC_7, KC_8, KC_9, KC_F11, KC_TRNS},
{ KC_TRNS, KC_ESC, KC_CAPS, KC_PGUP, KC_PGDN, KC_F4, KC_ASTR, KC_4, KC_5, KC_6, KC_0, KC_TRNS},
{ KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_1, KC_2, KC_3, KC_F12, KC_TRNS},
{ KC_TRNS, KC_TRNS, LCTL(LSFT(KC_LEFT)), LCTL(LSFT(KC_RGHT)), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LCTL(LSFT(KC_UP)), LCTL(LSFT(KC_DOWN)), KC_TRNS, KC_TRNS}
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
    case LALT:
      if (record->event.pressed) {
        alt_timers[0] = timer_read();
        altInterupted = false;
        register_mods(MOD_BIT(KC_LALT));
      } else {
        unregister_mods(MOD_BIT(KC_LALT));
        if (!altInterupted && timer_elapsed(alt_timers[0]) < TAPPING_TERM) {
          mod_type(KC_LSHIFT, KC_9);
        }
      }
      return false;
      break;
    case RALT:
      if (record->event.pressed) {
        alt_timers[1] = timer_read();
        altInterupted = false;
        register_mods(MOD_BIT(KC_RALT));
      } else {
        unregister_mods(MOD_BIT(KC_RALT));
        if (!altInterupted && timer_elapsed(alt_timers[1]) < TAPPING_TERM) {
          mod_type(KC_LSHIFT, KC_0);
        }
      }
      return false;
      break;
  }
  altInterupted = true;
  return true;
}
