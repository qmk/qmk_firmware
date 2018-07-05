#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef BACKLIGHT_ENABLE
  #include "backlight.h"
#endif

#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

void backlight_toggle(void){
};

enum roadkit_layers {
  _NUMPAD,
  _FPH,
  _FPHNOISY,
  _ADJUST,
  _DYN
};

enum roadkit_keycodes {
  NUMPAD = SAFE_RANGE,
  FPH_1,
  FPH_2,
  FPH_3,
  FPH_4,
  FPH_5,
  FPH_6,
  FPH_7,
  FPH_8,
  FPH_9,
  FN_0,
  BACKLIT,
  MACSLEEP,
  DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"

// Fillers to make keymaps cleaner looking
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NUMPAD] = LAYOUT_numpad_4x4( /* Numpad */
    KC_KP_7,    KC_KP_8,    KC_KP_9,    KC_KP_PLUS,  \
    KC_KP_4,    KC_KP_5,    KC_KP_6,                 \
    KC_KP_1,    KC_KP_2,    KC_KP_3,    KC_KP_ENTER, \
    LT(_ADJUST, KC_KP_0),   KC_KP_DOT                \
  ),
  [_FPH] = LAYOUT_numpad_4x4( /* Quiet T9 */
    FPH_7,      FPH_8,      FPH_9,      KC_KP_PLUS,         \
    FPH_4,      FPH_5,      FPH_6,                          \
    FPH_1,      FPH_2,      FPH_3,      SFT_T(KC_KP_ENTER), \
    LT(_ADJUST, KC_SPACE),  KC_KP_DOT                       \
  ),
  [_FPHNOISY] = LAYOUT_numpad_4x4( /* Noisy T9 */
    FPH_7,      FPH_8,      FPH_9,      KC_KP_PLUS,         \
    FPH_4,      FPH_5,      FPH_6,                          \
    FPH_1,      FPH_2,      FPH_3,      SFT_T(KC_KP_ENTER), \
    LT(_ADJUST, KC_SPACE),  KC_KP_DOT                       \
    ),
  [_ADJUST] = LAYOUT_numpad_4x4( /* Adjustments */
    KC_NUMLOCK, TG(_FPHNOISY), TG(_FPH), TG(_NUMPAD), \
    KC_BSPC,    BACKLIT,       KC_DEL,                \
    MACSLEEP,   _______,       _______,  _______,     \
    _______,                   MO(_DYN)               \
  ),
  [_DYN] = LAYOUT_numpad_4x4( /* DYNAMIC MACRO */
    DYN_REC_START1, DYN_REC_START2, _______, DYN_REC_STOP, \
    _______, _______,  _______,                            \
    DYN_MACRO_PLAY1, DYN_MACRO_PLAY2, _______, _______,    \
    _______,            _______                            \
  ),
};

const uint16_t PROGMEM fn_actions[] = {

};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

uint16_t fph_tap_qty = false;
uint16_t fph_keycode = 0; // stores which spacebar was used, either raise or lower...

uint16_t get_render_keycode(uint16_t keycode, uint16_t tap_qty){ // maybe replace shift with "mods"
  tap_qty--; // reduce by one to match array indexes.
  switch(keycode){
    case FPH_2:
      {uint16_t kc[] = {KC_A, KC_B, KC_C};
       if(tap_qty % 6 > 2)
        return LSFT(kc[tap_qty % 3]);
      return kc[tap_qty % 3];}
    break;
    case FPH_3:
      {uint16_t kc[] = {KC_D, KC_E, KC_F};
       if(tap_qty % 6 > 2)
        return LSFT(kc[tap_qty % 3]);
      return kc[tap_qty % 3];}
    break;
    case FPH_4:
      {uint16_t kc[] = {KC_G, KC_H, KC_I};
       if(tap_qty % 6 > 2)
        return LSFT(kc[tap_qty % 3]);
      return kc[tap_qty % 3];}
    break;
    case FPH_5:
      {uint16_t kc[] = {KC_J, KC_K, KC_L};
       if(tap_qty % 6 > 2)
        return LSFT(kc[tap_qty % 3]);
      return kc[tap_qty % 3];}
    break;
    case FPH_6:
      {uint16_t kc[] = {KC_M, KC_N, KC_O};
       if(tap_qty % 6 > 2)
        return LSFT(kc[tap_qty % 3]);
      return kc[tap_qty % 3];}
    break;
    case FPH_7:
      {uint16_t kc[] = {KC_P, KC_Q, KC_R, KC_S};
       if(tap_qty % 8 > 2)
        return LSFT(kc[tap_qty % 4]);
      return kc[tap_qty % 4];}
    break;
    case FPH_8:
      {uint16_t kc[] = {KC_T, KC_U, KC_V};
       if(tap_qty % 8 > 2)
        return LSFT(kc[tap_qty % 4]);
      return kc[tap_qty % 4];}
    break;
    case FPH_9:
      {uint16_t kc[] = {KC_W, KC_X, KC_Y, KC_Z};
       if(tap_qty % 8 > 2)
        return LSFT(kc[tap_qty % 4]);
      return kc[tap_qty % 4];}
    break;
    case FPH_1:
      {uint16_t kc[] = {KC_COMM, LSFT(KC_SLSH), KC_EXLM, KC_AT, KC_MINS, KC_UNDS, KC_PLUS, \
          KC_SCLN, LSFT(KC_SCLN), KC_QUOT, LSFT(KC_QUOT), KC_TILD, \
          KC_PIPE, KC_BSLS, KC_HASH, LSFT(KC_4), KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, \
          KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, LSFT(KC_COMM), LSFT(KC_DOT)};
      return kc[tap_qty % 26];}
  }
  return KC_NO;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_dynamic_macro(keycode, record)) {
      return false;
    }
    uint8_t layer;
    layer = biton32(layer_state);

    switch (keycode) {
    case FPH_1 ... FPH_9:
      if(layer == _FPHNOISY){
        if (record->event.pressed) {
          if(fph_keycode != keycode) { // key change
            fph_tap_qty = 0;
            fph_keycode = keycode;
          } else { // same key tapped again so erase and increment.
            register_code(KC_BSPC);
            unregister_code(KC_BSPC);
            fph_tap_qty++;
          }
          uint16_t render_keycode = get_render_keycode(keycode, fph_tap_qty);
          // find mods? Apply mods..
          register_code(render_keycode);
          unregister_code(render_keycode);
        } else {
          // do we need to do anything on key-release?
        }
      } else { // not noisy, be demure .
        if (record->event.pressed) {
          if(fph_keycode != keycode) { // key change, kill everything.
            uint16_t render_keycode = get_render_keycode(fph_keycode, fph_tap_qty);
            // find mods? Apply mods..
            register_code(render_keycode);
            unregister_code(render_keycode);
            fph_keycode = keycode;
            fph_tap_qty = 0;
          } else { // same key tapped again so increment counter silently
            fph_tap_qty++;
          }
        } else {
            // do we need to do anything on key-release?
            // maybe start a timer on this one?
        }
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      }
      return false;
      break;
    case MACSLEEP:
      if (record->event.pressed) {
          register_code(KC_RSFT);
          register_code(KC_RCTL);
          register_code(KC_POWER);
          unregister_code(KC_POWER);
          unregister_code(KC_RCTL);
          unregister_code(KC_RSFT);
      }
      return false;
      break;
  }
  return true;
}
