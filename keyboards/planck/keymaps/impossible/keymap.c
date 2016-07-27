// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "planck.h"
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

#define _ALPHA 0
#define _FN 1
#define _QWERTY 2
#define _PLOVER 3
#define _ADJUST 4

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  PLOVER,
  LOWER,
  RAISE,
  BACKLIT,
  EXT_PLV
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/* Alpha-numeric
 * ,-----------------------------------------------------------------------------------------------.
 * |   Q   |   D   |   R   |   W   |   B   |   F   |   U   |   P   |   J   |   7   |   8   |   9   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |   A   |   S   |   H   |   T   |   G   |   N   |   E   |   O   |   I   |   4   |   5   |   6   |
 * |-------+-------+-------+-------+-------+-------|-------+-------+-------+-------+-------+-------|
 * |   Z   |   X   |   M   |   C   |   V   |   L   |   Y   |   K   |   Up  |   1   |   2   |   3   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |Alt/Tab|Gui/Esc|   ,   |CTL/Bsp| Fn/Ent|SFT/SPC|   .   |  Left |  Down | Right |   0   |   /   |
 * `-----------------------------------------------------------------------------------------------'
 */

[_ALPHA] = {
  {KC_Q, KC_D, KC_R, KC_W, KC_B, KC_F, KC_U, KC_P, KC_J, KC_KP_7, KC_KP_8, KC_KP_9},
  {KC_A, KC_S, KC_H, KC_T, KC_G, KC_N, KC_E, KC_O, KC_I, KC_KP_4, KC_KP_5, KC_KP_6},
  {KC_Z, KC_X, KC_M, KC_C, KC_V, KC_L, KC_Y, KC_K, KC_UP, KC_KP_1, KC_KP_2, KC_KP_3},
  {ALT_T(KC_TAB), GUI_T(KC_ESC), KC_COMM, CTL_T(KC_BSPC), LT(_FN, KC_ENTER), SFT_T(KC_SPC), KC_DOT,
   KC_LEFT, KC_DOWN, KC_RGHT, KC_KP_0, KC_SLASH}
},

/* FN-key held
 * ,-----------------------------------------------------------------------------------------------.
 * |   !   |   @   |   #   |   $   |   %   |   ^   |   &   |   *   |  F12  |   F7  |   F8  |   F9  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Caps |   [   |   ]   |   -   |  Del  |   =   |   (   |   )   |  F11  |   F4  |   F5  |   F6  |
 * |-------+-------+-------+-------+-------+-------|-------+-------+-------+-------+-------+-------|
 * |  DFU  | Insert| PrtSc | ScrLk | Pause | NumLk |  Menu |       |  PgUp |   F1  |   F2  |   F3  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |Alt/Tab|Gui/Esc|   `   |CTL/Bsp| Fn/Ent|SFT/SPC|   ;   |  Home |  PgDn |  End  |  F10  |   /   |
 * `-----------------------------------------------------------------------------------------------'
 */

[_FN] = {
  {KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_FN12, KC_FN7, KC_FN8, KC_FN9},
  {KC_CAPSLOCK, KC_LBRACKET, KC_RBRACKET, KC_MINUS, KC_DELETE, KC_EQUAL, KC_LPRN, KC_RPRN, KC_FN11, KC_FN4, KC_FN5, KC_FN6},
  {RESET, KC_INS, KC_PSCR, KC_SLCK, KC_PAUSE, KC_NUMLOCK, KC_MENU, XXXXXXX, KC_PGUP, KC_FN1, KC_FN2, KC_FN3},
  {_______, _______, KC_GRAVE, _______, _______, _______, KC_SCOLON, KC_HOME, KC_PGDN, KC_END, KC_FN10, KC_BSLASH}
},

/* Qwerty
 * ,-----------------------------------------------------------------------------------------------.
 * |  Tab  |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   | Bksp  |
 * |-------+-------+-------+-------+-------+---------------+-------+-------+-------+-------+-------|
 * |  Esc  |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   |  "    |
 * |-------+-------+-------+-------+-------+-------|-------+-------+-------+-------+-------+-------|
 * | Shift |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   /   |Enter  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Brite | Ctrl  | Alt   | GUI   |Lower  |    Sp ace     |Raise  | Left  | Down  |  Up   |Right  |
 * `-----------------------------------------------------------------------------------------------'
 */

[_QWERTY] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
  {BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------------------.
 * |   S   |   T   |   P   |   H   |   *   |   F   |   P   |   L   |   T   |   D   |       |       |
 * |-------+-------+-------+-------+-------+-------|-------+-------+-------+-------+-------+-------|
 * |   S   |   K   |   W   |   R   |   *   |   R   |   B   |   G   |   S   |   Z   |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |   #   |   #   |   #   |   #   |       |   #   |   #   |   #   |   #   |   #   |       |       |
 * |-------+-------+-------+-------+-------+---------------+-------+-------+-------+-------+-------|
 * | Exit  |       |   A   |   O   |       |   E   |   U   |       |       |       |       |       |
 * `-----------------------------------------------------------------------------------------------'
 */

[_PLOVER] = {
  {KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_U,    KC_I,    KC_O,    KC_P,    XXXXXXX, XXXXXXX},
  {KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_J,    KC_K,    KC_L,    KC_SCLN, XXXXXXX, XXXXXXX},
  {KC_1,    KC_1,    KC_1,    KC_1,    XXXXXXX, KC_1,    KC_1,    KC_1,    KC_1,    XXXXXXX, XXXXXXX},
  {EXT_PLV, XXXXXXX, KC_C,    KC_V,    XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX}
},

/* Adjust
 * ,-----------------------------------------------------------------------------------------------.
 * |       | Reset |       |       |       |       |       |       |       |       |       |  Del  |
 * |-------+-------+-------+-------+-------+---------------+-------+-------+-------+-------+-------|
 * |       |       |       |Aud on |Audoff |AGnorm |AGswap |Qwerty |       |       |Plover |       |
 * |-------+-------+-------+-------+-------+-------|-------+-------+-------+-------+-------+-------|
 * |       |Voice- |Voice+ |Mus on |Musoff |MIDIon |MIDIof |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |       |       |       |
 * `-----------------------------------------------------------------------------------------------'
 */

[_ADJUST] = {
  {_______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL},
  {_______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  PLOVER,  _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}


};

#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
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
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_NOTE_ARRAY(tone_plover, false, 0);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_plover_gb, false, 0);
        #endif
        layer_off(_PLOVER);
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
