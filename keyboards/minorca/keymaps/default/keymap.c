// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "minorca.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _FN0 3
#define _FN1 4
#define _FN2 5
#define _ADJUST 16

enum minorca_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  FN0,
  FN1,
  FN2,
  BACKLIT
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Enter     |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift    |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /     |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl  |  Alt  |  FN0  |    Space      |     Space      |   FN1  | '   |    FN2    |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = { 
  {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,        KC_BSPC },
  {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    XXXXXXX,     KC_ENT },
  {KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,      KC_SLSH },
  {KC_LCTL, XXXXXXX, KC_LALT, FN0,     KC_SPC,  XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX, FN1,     KC_QUOT,     FN2     }                                   
},

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Bksp |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /         |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl  |  Alt  |  FN0  |    Space      |     Space      |   FN1  |   ' |    FN2    |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = {
  {KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC },
  {KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,   XXXXXXX, KC_O,    },
  {KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH },
  {KC_LCTL, XXXXXXX, KC_LALT, FN0,     KC_SPC,  XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX, FN1,     KC_QUOT,     FN2 }
},

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | `    |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |      S      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z         |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl  |  Alt  |  FN0  |    Space      |     Space      |   FN1  | '   |    FN2    |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = {
  {KC_GRV,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,  KC_BSPC},
  {KC_TAB,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    XXXXXXX, KC_S },
  {KC_LSFT, XXXXXXX, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z },
  {KC_LCTL, XXXXXXX, KC_LALT, FN0,     KC_SPC,  XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX, FN1,     KC_QUOT,     FN2  }
},

/* FN0
 * ,-----------------------------------------------------------------------------------.
 * |  ~   |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | |    |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |  ~   |  =   |   _  |  [  |  ]  |     '         |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Caps |      |      |      |      |      |      |      |      |      |      :      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |    Vol+     |       Vol-     |        | Next     |   Play    |
 * `-----------------------------------------------------------------------------------'
 */
[_FN0] = {
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE        },
  {_______, _______, _______, _______, _______, KC_TILD, KC_EQL,  KC_UNDS, KC_LBRC, KC_RBRC, XXXXXXX, KC_QUOT        },
  {KC_CAPSLOCK, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______, S(KC_SCLN) },
  {_______, XXXXXXX, _______, _______, KC_VOLU, XXXXXXX, XXXXXXX, KC_VOLD, XXXXXXX, _______, KC_MNXT, KC_MPLY        }
},

/* FN1
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | \    |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  `   |  +   |   -  |   :  |   ;  |        "    |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |     ;       |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |    Vol+     |       Vol-     |        | Next     |   Play    |
 * `-----------------------------------------------------------------------------------'
 */
[_FN1] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_BSLS           },
  {_______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_GRV,  KC_PLUS,   KC_MINS, S(KC_SCLN), KC_SCLN, XXXXXXX, S(KC_QUOT) },
  {_______, XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______, KC_SCLN                 },
  {_______, XXXXXXX, _______, _______, KC_VOLU,  XXXXXXX, XXXXXXX, KC_VOLD, XXXXXXX, _______, KC_MNXT, KC_MPLY        }
},

/* FN2
 * ,-----------------------------------------------------------------------------------.
 * |      |      |  Up  |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |        |  Left|  Down| Right|      |      |      |      |        |  Up  |         |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |             |      |      |      |      |      |      |      | Left | Right|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |    PgUp         | PgDn           |      |    Down   |        |
 * `-----------------------------------------------------------------------------------'
 */

[_FN2] = {
  {XXXXXXX, XXXXXXX, KC_UP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX    },
  {XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_UP, XXXXXXX, XXXXXXX  },
  {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_LEFT, KC_RIGHT, XXXXXXX},
  {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX, XXXXXXX, KC_PGDN, XXXXXXX, XXXXXXX, KC_DOWN, _______  }
},

/* Adjust (FN0 + FN1)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {_______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_DEL},
  {_______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  XXXXXXX, _______},
  {_______, XXXXXXX, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______},
  {_______, XXXXXXX, _______, _______, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, _______, _______}
}


};

#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif


void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_colemak, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_dvorak, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case FN0:
      if (record->event.pressed) {
        layer_on(_FN0);
        update_tri_layer(_FN0, _FN1, _ADJUST);
      } else {
        layer_off(_FN0);
        update_tri_layer(_FN0, _FN1, _ADJUST);
      }
      return false;
      break;
    case FN1:
      if (record->event.pressed) {
        layer_on(_FN1);
        update_tri_layer(_FN0, _FN1, _ADJUST);
      } else {
        layer_off(_FN1);
        update_tri_layer(_FN0, _FN1, _ADJUST);
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
    case FN2:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_NOTE_ARRAY(tone_plover, false, 0);
        #endif
        layer_on(_FN2);
      } else {
        layer_off(_FN2);
      }
      return false;
      break;
  }
  return true;
}

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
