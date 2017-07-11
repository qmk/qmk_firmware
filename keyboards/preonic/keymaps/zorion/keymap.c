#include "preonic.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum preonic_layers {
  _QWERTY,
  _COLEMAK,
  _CLMK2,
  _DVORAK,
  _NUMFUN,
  _LOWER,
  _RAISE,
  _ADJUST,
  _FN
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  CLMK2,
  DVORAK,
  NUMFUN,
  LOWER,
  RAISE,
  BACKLIT,
  FN
};

enum {
  TD_LLCK = 0,
  TD_RLCK,
  TD_FLCK,
  TD_CLCK
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  FN  | Ctrl | GUI  | Alt  |Lower |Space | Space|Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL},
  {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
  {MO(_FN), KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Adj  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  FN  | Ctrl | GUI  | Alt  |Lower |Space | Bksp |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL},
  {KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT},
  {TD(TD_CLCK), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
  {TD(TD_FLCK), KC_LCTL, KC_LGUI, KC_LALT, TD(TD_LLCK),   KC_SPC,  KC_BSPC, TD(TD_RLCK),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

/* Colemak 2
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Adj  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |   '  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  FN  | Ctrl | GUI  | Alt  |Lower |Space | Bksp |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_CLMK2] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL},
  {KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT},
  {MO(_FN), KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_BSPC, RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  FN  | Ctrl | GUI  | Alt  |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_ESC,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_DEL},
  {KC_TAB,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH},
  {KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT },
  {MO(_FN), KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

/* Numpad + Function keys = NUMFUN!!!
  * ,-----------------------------------------------------------------------------------.
  * |   `  |      |      |      |      |      | Home |   7  |   8  |   9  |   /  | Bksp |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * |  Esc |  F1  |  F2  |  F3  |  F4  |      | PgUp |   4  |   5  |   6  |   *  |  Del |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * |  Tab |  F5  |  F6  |  F7  |  F8  |      | PgDn |   1  |   2  |   3  |   -  |  Tab |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * | Shift|  F9  |  F10 |  F11 |  F12 |      |  End |   0  |   .  | Enter|   +  | Enter|
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * |  Fn  | Ctrl |  GUI |  Alt | Lower| Space| Bksp | Raise| Left | Down |  Up  | Right|
  * `-----------------------------------------------------------------------------------'
  */
[_NUMFUN] = {
  {KC_GRV,  _______, _______, _______, _______, _______, KC_HOME, KC_P7,   KC_P8,   KC_P9,   KC_PSLS, KC_BSPC},
  {KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, KC_PGUP, KC_P4,   KC_P5,   KC_P6,   KC_PAST, KC_DEL},
  {KC_TAB,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, KC_PGUP, KC_P1,   KC_P2,   KC_P3,   KC_PMNS, KC_TAB},
  {KC_LSFT, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_END,  KC_P0,   KC_PDOT, KC_PENT, KC_PPLS, KC_ENT},
  {MO(_FN), KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_BSPC, RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |      |      | Home | PgDn | PgUp |  End |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |      | Left | Down |  Up  | Right|      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX},
  {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______},
  {_______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______},
  {_______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      | Mute | Vol- | Vol+ |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |  Up  |      |      |      |      |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  Lt  |  Dn  |  Rt  |      |      |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {_______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______, _______, _______, _______, _______, XXXXXXX},
  {_______, _______,  KC_UP , _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE},
  {_______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |NumFun|Colemk|Qwerty|Dvorak|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |MidiOn|MidOff|      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {_______, _______, _______, _______, _______, _______, _______, NUMFUN,  COLEMAK, QWERTY,  DVORAK,  XXXXXXX},
  {_______, _______, _______, _______, _______, _______, _______, _______, MI_ON,   MI_OFF,  _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Function layer
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FN] = {
  {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}


};

#ifdef AUDIO_ENABLE
float tone_startup[][2] = {
  {NOTE_B5, 20},
  {NOTE_B6, 8},
  {NOTE_DS6, 20},
  {NOTE_B6, 8}
};

float tone_qwerty[][2]  = SONG(QWERTY_SOUND);
float tone_dvorak[][2]  = SONG(DVORAK_SOUND);
float tone_colemak[][2] = SONG(COLEMAK_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);

float music_scale[][2]  = SONG(MUSIC_SCALE_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void low_press(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 1) {
    layer_on(_LOWER);
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
  }
}

void low_done(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 2) {
    layer_on(_LOWER);
  }
}

void low_reset(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 1) {
    layer_off(_LOWER);
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
  }
}

void rai_press(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 1) {
    layer_on(_RAISE);
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
  }
}

void rai_done(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 2) {
    layer_on(_RAISE);
  }
}

void rai_reset(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 1) {
    layer_off(_RAISE);
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
  }
}

void fn_press(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 1) {
    layer_on(_FN);
  }
}

void fn_done(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 2) {
    layer_on(_FN);
  }
}

void fn_reset(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 1) {
    layer_off(_FN);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LLCK] = ACTION_TAP_DANCE_FN_ADVANCED(low_press, low_done, low_reset),
  [TD_RLCK] = ACTION_TAP_DANCE_FN_ADVANCED(rai_press, rai_done, rai_reset),
  [TD_FLCK] = ACTION_TAP_DANCE_FN_ADVANCED(fn_press, fn_done, fn_reset),
  [TD_CLCK] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case QWERTY:
        if (record->event.pressed) {
          #ifdef AUDIO_ENABLE
            PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
          #endif
          persistent_default_layer_set(1UL<<_QWERTY);
        }
        return false;
        break;
      case COLEMAK:
        if (record->event.pressed) {
          #ifdef AUDIO_ENABLE
            PLAY_NOTE_ARRAY(tone_colemak, false, 0);
          #endif
          persistent_default_layer_set(1UL<<_COLEMAK);
        }
        return false;
        break;
      case CLMK2:
        if (record->event.pressed) {
          #ifdef AUDIO_ENABLE
            PLAY_NOTE_ARRAY(tone_colemak, false, 0);
          #endif
          persistent_default_layer_set(1UL<<_CLMK2);
        }
        return false;
        break;
      case DVORAK:
        if (record->event.pressed) {
          #ifdef AUDIO_ENABLE
            PLAY_NOTE_ARRAY(tone_dvorak, false, 0);
          #endif
          persistent_default_layer_set(1UL<<_DVORAK);
        }
        return false;
        break;
      case NUMFUN:
        if (record->event.pressed) {
          #ifdef AUDIO_ENABLE
            PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
          #endif
          persistent_default_layer_set(1UL<<_NUMFUN);
        }
        return false;
        break;
      case LOWER:
        if (record->event.pressed) {
          layer_on(_LOWER);
          update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
          layer_off(_LOWER);
          update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        break;
      case RAISE:
        if (record->event.pressed) {
          layer_on(_RAISE);
          update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
          layer_off(_RAISE);
          update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        break;
      case BACKLIT:
        if (record->event.pressed) {
          register_code(KC_RSFT);
          #ifdef BACKLIGHT_ENABLE
            backlight_step();
          #endif
        } else {
          unregister_code(KC_RSFT);
        }
        return false;
        break;
    }
    return true;
};

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user()
{
    PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_NOTE_ARRAY(music_scale, false, 0);
}

#endif
