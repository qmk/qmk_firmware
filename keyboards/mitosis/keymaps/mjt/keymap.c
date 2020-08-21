// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum mitosis_layers
{
  _QWERTY,
  _SHIFTED,
  _FUNCTIONPC,
  _FUNCTIONMAC,
  _FUNCSHIFT,
  _ADJUST
};

enum mitosis_keycodes
{
  FNKEY = SAFE_RANGE,
  SHIFT,
  MACSLEEP,
  FNMAC,
  FNPC,
  AUDIOTEST,
  DYNAMIC_MACRO_RANGE,
};


// Macro definitions for readability
enum mitosis_macros
{
  VOLU,
  VOLD,
  ESCM
};


#include "dynamic_macro.h"

#define LONGPRESS_DELAY 150
#define LAYER_TOGGLE_DELAY 900

// Fillers to make layering more clear
#define __MOD__ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( /* QWERTY adapted to this crazy thing */
    KC_Q,       KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,        KC_P,
    KC_A,       KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,    KC_L,        KC_SCLN,
    SFT_T(KC_Z), KC_X,   KC_C,    KC_V,    KC_B,           KC_N,    KC_M,    KC_COMM, KC_DOT,      SFT_T(KC_SLSH),
                KC_LCTL, M(ESCM),  KC_TAB,  KC_QUOT,       KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,
                KC_LALT, KC_LGUI, KC_SPC,  SHIFT,          FNKEY,   KC_BSPC, KC_ENT,  MO(_ADJUST)
  ),


  [_SHIFTED] = LAYOUT( /* Shifted Layer, layered so that tri_layer can be used, or selectively
                                         able to modify individual key's shifted behaviour */
    _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,
             __MOD__, KC_DEL,  _______, _______,       _______, _______, _______, _______,
             __MOD__, __MOD__, _______, __MOD__,       __MOD__, _______, _______, XXXXXXX
  ),


  [_FUNCTIONPC] = LAYOUT( /* Function Layer mimicks planck's raise layer somewhat */
    KC_1,       KC_2,          KC_3,    KC_4,      KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    LCTL(KC_A), LCTL(KC_S),    _______, LCTL(KC_F),_______,       _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,
    LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V),_______,       _______, KC_BSLS, _______, _______, KC_QUOT,
                __MOD__,        KC_DEL, _______,   KC_GRV,        KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                __MOD__,       __MOD__, _______,   __MOD__,       __MOD__, _______, KC_PSCR, XXXXXXX
  ),

  [_FUNCTIONMAC] = LAYOUT( /* Function Layer mimicks planck's raise layer somewhat */
    KC_1,       KC_2,          KC_3,    KC_4,      KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    LGUI(KC_A), LGUI(KC_S),    _______, LGUI(KC_F),_______,       _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,
    LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V),_______,       _______, KC_BSLS, _______, _______, KC_QUOT,
                __MOD__,        KC_DEL, _______,   KC_GRV,        KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                __MOD__,       __MOD__, _______,   __MOD__,       __MOD__, _______, KC_PSCR, XXXXXXX
  ),

  [_FUNCSHIFT] = LAYOUT( /* Function Shifted Layer mimicks planck's lower layer somewhat */
    _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   _______, _______, KC_LCBR, KC_RCBR,
    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,        KC_F12,  _______, _______, _______, _______,
             __MOD__, KC_DEL,  _______, KC_TILD,       _______, _______, _______, _______,
             __MOD__, __MOD__, _______, __MOD__,       __MOD__, _______, _______, _______
  ),


  [_ADJUST] = LAYOUT( /* Adjust layer for fancy stuff and macros */
    RESET,   FNPC,    _______, _______,  _______,       _______, DYN_REC_START1,  DYN_REC_START2,  _______,  _______,
    FNMAC,   _______,   AU_ON, AU_OFF,   _______,       _______, _______,         _______,         MACSLEEP, _______,
    MUV_DE,  MUV_IN,    MU_ON, MU_OFF,   _______,       _______, KC_MUTE,         KC_MPRV,         KC_MNXT,  KC_MPLY,
             __MOD__, _______, _______,  _______,       _______, DYN_MACRO_PLAY1, DYN_MACRO_PLAY2,  _______,
             __MOD__, __MOD__, _______,  __MOD__,       __MOD__, _______,         _______,         __MOD__
  )

};

#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dyn_macro_rec[][2]     = SONG(DVORAK_SOUND);
float tone_dyn_macro_play[][2]    = SONG(COLEMAK_SOUND);
float tone_fnpc[][2]     = SONG(PLOVER_SOUND);
float tone_fnmac[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif

static uint16_t function_layer = _FUNCTIONMAC;
static uint16_t key_timer;

void persistent_function_layer_set(uint16_t new_function_layer) {
  // eeconfig_update_function_layer(new_function_layer);
  function_layer = new_function_layer;
  // should clear layers to avoid getting stuck.
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {

  //switch multiplexing for media, short tap for volume up, long press for play/pause
  case VOLU:
    if (record->event.pressed) {
      key_timer = timer_read();           // if the key is being pressed, we start the timer.
    } else {         // this means the key was just released, so we can figure out how long it was pressed for (tap or "held down").
      if (timer_elapsed(key_timer) > LONGPRESS_DELAY) {           // LONGPRESS_DELAY being 150ms, the threshhold we pick for counting something as a tap.
        return MACRO(T(MPLY), END);
      } else {
        return MACRO(T(VOLU), END);
      }
    }
    break;

  //switch multiplexing for media, short tap for volume down, long press for next track
  case VOLD:
    if (record->event.pressed) {
      key_timer = timer_read();
    } else {
      if (timer_elapsed(key_timer) > LONGPRESS_DELAY) {
        return MACRO(T(MNXT), END);
      } else {
        return MACRO(T(VOLD), END);
      }
    }
    break;

  //switch multiplexing for escape, short tap for escape, long press for context menu
  case ESCM:
    if (record->event.pressed) {
      key_timer = timer_read();
    } else {
      if (timer_elapsed(key_timer) > LONGPRESS_DELAY) {
        return MACRO(T(APP), END);
      } else {
        return MACRO(T(ESC), END);
      }
    }
    break;
  }
  return MACRO_NONE;
};

static bool singular_key = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint16_t macro_kc = (keycode == MO(_ADJUST) ? DYN_REC_STOP : keycode);
  if (!process_record_dynamic_macro(macro_kc, record)) {
    return false;
  }
  uint8_t layer;
  layer = biton32(layer_state);  // get the current layer

  //custom layer handling for tri_layer,
  switch (keycode) {
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
  case FNKEY:
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
    update_tri_layer(function_layer, _SHIFTED, _FUNCSHIFT);
    return false;
    break;
  //SHIFT is handled as LSHIFT in the general case
  case SHIFT:
    if (record->event.pressed) {
      key_timer = timer_read();
      singular_key = true;
      layer_on(_SHIFTED);
      register_code(KC_LSFT);
    } else {
      if (timer_elapsed(key_timer) < LAYER_TOGGLE_DELAY || !singular_key) {
        layer_off(_SHIFTED);
        unregister_code(KC_LSFT);
      }
    }
    update_tri_layer(function_layer, _SHIFTED, _FUNCSHIFT);
    return false;
    break;
  case FNPC:
    if (record->event.pressed) {
      persistent_function_layer_set(_FUNCTIONPC);
      #ifdef AUDIO_ENABLE
        PLAY_SONG(tone_fnpc);
      #endif
    }
    return false;
    break;
  case FNMAC:
    if (record->event.pressed) {
      persistent_function_layer_set(_FUNCTIONMAC);
      #ifdef AUDIO_ENABLE
        PLAY_SONG(tone_fnmac);
      #endif
    }
  return false;
  break;
    case AUDIOTEST:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
        PLAY_SONG(music_scale);
        register_code(KC_M);
        unregister_code(KC_M);
        #endif
        register_code(KC_A);
      } else {
        unregister_code(KC_A);
      }
    return false;
    break;
  //If any other key was pressed during the layer mod hold period,
  //then the layer mod was used momentarily, and should block latching
  default:
    singular_key = false;
    break;
  }

  //FUNCSHIFT has been shifted by the SHIFT handling, some keys need to be excluded
  if (layer == _FUNCSHIFT) {
    //F1-F12 should be sent as unshifted keycodes,
    //and ] needs to be unshifted or it is sent as }
    if ( (keycode >= KC_F1 && keycode <= KC_F12)
         || keycode == KC_RBRC ) {
      if (record->event.pressed) {
        unregister_mods(MOD_LSFT);
      } else {
        register_mods(MOD_LSFT);
      }
    }
  }

  return true;
};

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_SONG(tone_startup);
}

void shutdown_user()
{
    PLAY_SONG(tone_goodbye);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif

void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  switch (layer) {
  case _QWERTY:
    set_led_off;
    break;
  case _FUNCTIONMAC:
    set_led_blue;
    break;
  case _FUNCTIONPC:
    set_led_cyan;
    break;
  case _SHIFTED:
    set_led_red;
    break;
  case _FUNCSHIFT:
    set_led_green;
    break;
  case _ADJUST:
    set_led_white;
    break;
  default:
    break;
  }
};
