#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Layers
#define _QWERTY 0 // Base layer
#define _NUMB 1
#define _NAVI 2

// Keys
#define KC_NUMB MO(_NUMB)
#define KC_NAVI MO(_NAVI)
#define KC_AGRV LALT_T(KC_GRAVE)
#define KC_GUIE LGUI_T(KC_ESC)
#define KC_REST RESET
#define KC_DBUG DEBUG

// Tap Dance Declarations
enum {
  TD_LALT_GRV_BSLS = 0,
  TD_LSFT_LBRC,
  TD_RSFT_RBRC,
};

void alt_grave_backslash(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      if (!state->pressed) {
        register_code(KC_GRAVE);
      } else {
        register_code(KC_LALT);
      }
    } else if (state->count == 2) {
      register_code(KC_BSLASH);
    }
}

void alt_grave_backslash_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      unregister_code(KC_GRAVE);
      unregister_code(KC_LALT);
    } else if (state->count == 2) {
      unregister_code(KC_BSLASH);
    }
}

void left_brackets(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (!state->pressed) {
      register_code(KC_LSFT);
      register_code(KC_9);
    } else {
      register_code(KC_LSFT);
    }
  } else if (state->count == 2) {
    register_code(KC_LBRC);
  }
}

void left_brackets_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      unregister_code(KC_LSFT);
      unregister_code(KC_9);
    } else if (state->count == 2) {
      unregister_code(KC_LBRC);
    }
}

void right_brackets(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      if (!state->pressed) {
        register_code(KC_RSFT);
        register_code(KC_0);
      } else {
        register_code(KC_RSFT);
      }
    } else if (state->count == 2) {
      register_code(KC_RBRC);
    }
}

void right_brackets_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_RSFT);
        unregister_code(KC_0);
    } else if (state->count == 2) {
      unregister_code(KC_RBRC);
    }
}


// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap once for KC_SLSH, twice for KC_BSLS
  [TD_LALT_GRV_BSLS]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, alt_grave_backslash, alt_grave_backslash_reset),
  [TD_LSFT_LBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, left_brackets, left_brackets_reset),
  [TD_RSFT_RBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, right_brackets, right_brackets_reset)
};

// Tap Dance Keys
#define KC_AGRB TD(TD_LALT_GRV_BSLS)
#define KC_LSBK TD(TD_LSFT_LBRC)
#define KC_RSBK TD(TD_RSFT_RBRC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
//,----+----+----+----+----+----.              ,----+----+----+----+----+----.
   GUIE, 1,   2,   3,   4,   5,                  6,   7,   8,   9,   0,  DEL,
//|----+----+----+----+----+----|              |----+----+----+----+----+----|
   TAB,  Q,   W,   E,   R,   T,                  Y,   U,   I,   O,   P,  BSPC,
//|----+----+----+----+----+----|              |----+----+----+----+----+----|
   AGRB, A,   S,   D,   F,   G,                  H,   J,   K,   L,  SCLN,QUOT,
//|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
   LSBK, Z,   X,   C,   V,   B,  MINS,     EQL,  N,   M,  COMM,DOT, SLSH,RSBK,
//`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                     NUMB,LCTL,SPC,          ENT, RCTL,NAVI
//                  `----+----+----'        `----+----+----'
     ),

  [_NUMB] = LAYOUT_kc(
//,----+----+----+----+----+----.              ,----+----+----+----+----+----.
   F12,  F1,  F2,  F3,  F4,  F5,                 F6,  F7,  F8,  F9, F10, F11,
//|----+----+----+----+----+----|              |----+----+----+----+----+----|
    NO, F17, F18, F19, F20,  NO,                 NO,  7,   8,   9,   0,  TRNS,
//|----+----+----+----+----+----|              |----+----+----+----+----+----|
   TRNS,F13, F14, F15, F16,  NO,                ASTR, 4,   5,   6,  PLUS,TRNS,
//|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
   TRNS,F21, F22, F23, F24,  NO, TRNS,     TRNS,SLSH, 1,   2,   3,  MINS,TRNS,
//`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                     TRNS,TRNS,TRNS,         TRNS,DOT, TRNS
//                  `----+----+----'        `----+----+----'
      ),

 [_NAVI] = LAYOUT_kc(
//,----+----+----+----+----+----.              ,----+----+----+----+----+----.
   PWR, MUTE,VOLD,VOLU,BRID,BRIU,               REST,DBUG, NO,  NO,  NO, TRNS,
//|----+----+----+----+----+----|              |----+----+----+----+----+----|
   WAKE,HOME,PGUP, UP, PGDN,TRNS,                NO,  NO,  NO,  NO,  NO, TRNS,
//|----+----+----+----+----+----|              |----+----+----+----+----+----|
   TRNS,END, LEFT,DOWN,RGHT,TRNS,               PAUS,CAPS,PSCR,SLCK,INS, TRNS,
//|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS, NO,  NO,  NO,  NO,  NO, TRNS,
//`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                     TRNS,TRNS,TRNS,         TRNS,TRNS,TRNS
//                  `----+----+----'        `----+----+----'
     )
};
