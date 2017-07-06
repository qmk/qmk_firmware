#include "jd45.h"

enum jd45_layers
{
  _QWERTY,
  _QWERTYNUMMODS,
  _NUMPAD,
  _FKEYNUMPAD,
  _NUMSYM,
  _FUNCTION,
  _ADJUST
};

enum jd45_keycodes
{
  NUMSYM = SAFE_RANGE,
  FNSPC,
  FKEYTAB,
  MACSLEEP,
  NUMPAD,
  FKEYNUMPAD,
  FUNCTION,
  USEFNMODS,
  USENUMMODS,
  DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"

#define LONGPRESS_DELAY 150
#define LAYER_TOGGLE_DELAY 900

#define _______ KC_TRNS
#define __MOD__ KC_TRNS
#define XXXXXXX KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = {
  {FKEYTAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_MINS, KC_BSPC},
   {CTL_T(KC_ESC),    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  LT(2, KC_QUOT)},
     {KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, SFT_T(KC_ENT)},
  { XXXXXXX, KC_LALT, KC_LGUI, XXXXXXX,  XXXXXXX,  XXXXXXX, FNSPC,  MO(_FUNCTION),  MO(_ADJUST),   XXXXXXX }
},
[_QWERTYNUMMODS] = {
{  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {XXXXXXX, _______, _______, XXXXXXX,  XXXXXXX,  XXXXXXX,_______, _______, _______, XXXXXXX }
},
[_NUMSYM] = {
{KC_GRV,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,   KC_0, _______, KC_DEL},
 {__MOD__, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______, _______},
  {_______, _______, _______, _______, _______, KC_SPC, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, _______},
{XXXXXXX, __MOD__, __MOD__, XXXXXXX,  XXXXXXX,  XXXXXXX, _______, __MOD__, __MOD__, XXXXXXX}
},
[_FUNCTION] = {
{__MOD__,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11, KC_F12},
{__MOD__, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
{_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
{XXXXXXX, __MOD__, __MOD__, XXXXXXX,  XXXXXXX,  XXXXXXX, _______, __MOD__, __MOD__, XXXXXXX }
},
[_NUMPAD] = {
{KC_GRV,  _______,   KC_UP, _______,   KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_PSCR, KC_LBRC, KC_RBRC},
{_______, KC_LEFT, KC_DOWN, KC_RGHT,   KC_4,    KC_5,    KC_6,  KC_INS, KC_HOME, KC_PGUP, _______, _______},
{_______, _______, _______, _______,   KC_1,    KC_2,    KC_3,  KC_DEL,  KC_END, KC_PGDN, _______, _______},
{XXXXXXX, _______, _______, XXXXXXX,  XXXXXXX,  XXXXXXX, _______, _______, _______, XXXXXXX }
},
[_FKEYNUMPAD] = {
{_______, _______, KC_VOLU, _______,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_PSCR, _______, _______},
{_______, KC_MPRV, KC_VOLD, KC_MNXT,   KC_F4,   KC_F5,   KC_F6,    KC_J,    KC_K,    KC_L, KC_SCLN, _______},
{_______, _______, _______, _______,   KC_F1,   KC_F2,   KC_F3, KC_MUTE, KC_MPRV, KC_MNXT, KC_MSTP, _______},
{XXXXXXX, _______, _______, XXXXXXX,  XXXXXXX,  XXXXXXX, _______, __MOD__, KC_PAUS, XXXXXXX }
},
[_ADJUST] = {
  {_______, RESET, _______, _______, _______, _______, _______, DYN_REC_START1, DYN_REC_START2, _______, KC_PSCR, _______, _______},
  { _______, _______, _______, _______, USEFNMODS, _______, _______, DYN_MACRO_PLAY1, DYN_MACRO_PLAY2, MACSLEEP, _______, _______},
  {  _______, _______, _______, _______, _______, _______, USENUMMODS, _______, _______, _______, _______, _______},
  {XXXXXXX, _______, _______,XXXXXXX,  XXXXXXX,  XXXXXXX, _______, __MOD__, __MOD__, XXXXXXX}
 }
};

const uint16_t PROGMEM fn_actions[] = {

};

static uint16_t function_layer = _NUMSYM;
static uint16_t spacefn_key = KC_NO;
static uint16_t key_timer;

void persistent_function_layer_set(uint16_t new_function_layer) {
  // eeconfig_update_function_layer(new_function_layer);
  function_layer = new_function_layer;
  // should clear layers to avoid getting stuck.
}

static bool singular_key = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint16_t macro_kc = (keycode == MO(_ADJUST) ? DYN_REC_STOP : keycode);
  if (!process_record_dynamic_macro(macro_kc, record)) {
    return false;
  }
  uint8_t layer;
  layer = biton32(layer_state);  // get the current layer

  switch (keycode) {
  case FNSPC:
    if (record->event.pressed) {
      key_timer = timer_read();
      singular_key = true;
      // layer_on(_FUNCTION);
      layer_on(function_layer);
    } else {
      layer_off(function_layer);
      if(singular_key) {
        register_code(KC_SPC);
        unregister_code(KC_SPC);
        singular_key = false;
      }
      /* remove hold-to-toggle for now
      else if (timer_elapsed(key_timer) < LAYER_TOGGLE_DELAY || !singular_key) {
        layer_off(function_layer);
      }*/
    }
    return false;
    break;
  case FKEYTAB:
    if (record->event.pressed) {
      key_timer = timer_read();
      singular_key = true;
      // layer_on(_FUNCTION);
      layer_on(_FUNCTION);
    } else {
      if(singular_key) {
        layer_off(_FUNCTION);
        register_code(KC_TAB);
        unregister_code(KC_TAB);
        singular_key = false;
      }
    }
  return false;
  break;
  case MACSLEEP:
    if (record->event.pressed) {
      // ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT, KC_POWER);
      register_code(KC_RSFT);
      register_code(KC_RCTL);
      register_code(KC_POWER);
      unregister_code(KC_POWER);
      unregister_code(KC_RCTL);
      unregister_code(KC_RSFT);
    }
    return false;
    break;
  case NUMSYM:
    if (record->event.pressed) {
      key_timer = timer_read();
      singular_key = true;
      // layer_on(_FUNCTION);
      layer_on(function_layer);
    } else {
      if (timer_elapsed(key_timer) < LAYER_TOGGLE_DELAY || !singular_key) {
        layer_off(function_layer);
      }
    }
    // update_tri_layer(function_layer, _SHIFTED, _FUNCSHIFT);
    return false;
    break;
  //SHIFT is handled as LSHIFT in the general case
  case NUMPAD:
    if (record->event.pressed) {
      key_timer = timer_read();
      singular_key = true;
      layer_on(_NUMPAD);
    } else {
      if (timer_elapsed(key_timer) < LAYER_TOGGLE_DELAY || !singular_key) {
        layer_off(_NUMPAD);
      }
    }
    // update_tri_layer(function_layer, _SHIFTED, _FUNCSHIFT);
    return false;
    break;
  case USEFNMODS:
    if (record->event.pressed) {
      persistent_function_layer_set(_QWERTY);
      #ifdef AUDIO_ENABLE
        PLAY_NOTE_ARRAY(tone_fnpc, false, 0);
      #endif
    }
    return false;
    break;
  case USENUMMODS:
    if (record->event.pressed) {
      persistent_function_layer_set(_QWERTYNUMMODS);
      #ifdef AUDIO_ENABLE
        PLAY_NOTE_ARRAY(tone_fnmac, false, 0);
      #endif
    }
    return false;
    break;
  //If any other key was pressed during the layer mod hold period,
  //then the layer mod was used momentarily, and should block latching
  default:
  // this block needs to handle a few things
  // 1. what happens when preceeding keystroke overlaps tapped spacebar
  //    Outcome: character 'e' should be rendered before the space
  //    State: "e" keycode has already been registered... just don't disrupt it
  //      Space will not have been registered,
  //      Singular_key will be true,
  //      Layer will be function
  // 2. what happens when spacebar overlaps the following key
    if (record->event.pressed && keycode != FNSPC) {
      if(singular_key){
        spacefn_key = keycode;
        keycode = KC_NO;
        return false;
      }
    } else {
      if(layer == function_layer && spacefn_key != KC_NO){
        // translate to base layer
        // record->event->key->col
        // record->event->key->row
        uint16_t qwerty_keycode = keymaps[_QWERTY][record->event.key.row][record->event.key.col];
        register_code(qwerty_keycode);
        unregister_code(qwerty_keycode);
        spacefn_key = KC_NO;
      }
      singular_key = false;
    }
    break;
  }

  return true;
};
