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

#define _WORKMAN 0
#define _WORKMAN_FN 1
#define _QWERTY 2
#define _QWERTY_FN 3
#define _PLOVER 4
#define _ADJUST 5

enum planck_keycodes {
  WORKMAN = SAFE_RANGE,
  QWERTY,
  PLOVER
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Workman Alpha-numeric
 * ,-----------------------------------------------------------------------------------------------.
 * |   Q   |   D   |   R   |   W   |   B   |   F   |   U   |   P   |   J   |   7   |   8   |   9   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |   A   |   S   |   H   |   T   |   G   |   N   |   E   |   O   |   I   |   4   |   5   |   6   |
 * |-------+-------+-------+-------+-------+-------|-------+-------+-------+-------+-------+-------|
 * |   Z   |   X   |   M   |   C   |   V   |   L   |   Y   |   K   |   Up  |   1   |   2   |   3   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |Alt/Tab|Gui/Esc|   ,   |CTL/Bsp| Fn/Ent|SFT/SPC|   .   |  Left |  Down | Right |   0   |Adj/ / |
 * `-----------------------------------------------------------------------------------------------'
 */

[_WORKMAN] = {
  {KC_Q,          KC_D,          KC_R,    KC_W,           KC_B,              KC_F,          KC_U,   KC_P,    KC_J,    KC_KP_7, KC_KP_8, KC_KP_9},
  {KC_A,          KC_S,          KC_H,    KC_T,           KC_G,              KC_N,          KC_E,   KC_O,    KC_I,    KC_KP_4, KC_KP_5, KC_KP_6},
  {KC_Z,          KC_X,          KC_M,    KC_C,           KC_V,              KC_L,          KC_Y,   KC_K,    KC_UP,   KC_KP_1, KC_KP_2, KC_KP_3},
  {ALT_T(KC_TAB), GUI_T(KC_ESC), KC_COMM, CTL_T(KC_BSPC), LT(_WORKMAN_FN, KC_ENTER), SFT_T(KC_SPC), KC_DOT, KC_LEFT, KC_DOWN, KC_RGHT, KC_KP_0, LT(_ADJUST, KC_SLASH)}
},

/* FN-key held (Workman)
 * ,-----------------------------------------------------------------------------------------------.
 * |   !   |   @   |   #   |   $   |   %   |   ^   |   &   |   *   |  F12  |   F7  |   F8  |   F9  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |   [   |   ]   |   -   |  Del  |   =   |   (   |   )   |  F11  |   F4  |   F5  |   F6  |
 * |-------+-------+-------+-------+-------+-------|-------+-------+-------+-------+-------+-------|
 * |  Tab  | Insert| PrtSc |       | Pause |       |  Menu |       |  PgUp |   F1  |   F2  |   F3  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |Alt/Tab|  Gui  |   ~   |CTL/Bsp|Fn/Ent |SFT/Spc|   ;   |  Home |  PgDn |  End  |  F10  |   \   |
 * `-----------------------------------------------------------------------------------------------'
 */

[_WORKMAN_FN] = {
  {KC_EXLM, KC_AT,       KC_HASH,     KC_DLR,   KC_PERC,   KC_CIRC,  KC_AMPR,   KC_ASTR, KC_F12,  KC_F7,  KC_F8,  KC_F9},
  {XXXXXXX, KC_LBRACKET, KC_RBRACKET, KC_MINUS, KC_DELETE, KC_EQUAL, KC_LPRN,   KC_RPRN, KC_F11,  KC_F4,  KC_F5,  KC_F6},
  {KC_Tab,  KC_INS,      KC_PSCR,     XXXXXXX,  KC_PAUSE,  XXXXXXX,  KC_MENU,   XXXXXXX, KC_PGUP, KC_F1,  KC_F2,  KC_F3},
  {_______, KC_LGUI,     KC_GRAVE,    _______,  _______,   _______,  KC_SCOLON, KC_HOME, KC_PGDN, KC_END, KC_F10, KC_BSLASH}
},

/* Qwerty
 * ,-----------------------------------------------------------------------------------------------.
 * |Gui/Esc|   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   | Bksp  |
 * |-------+-------+-------+-------+-------+---------------+-------+-------+-------+-------+-------|
 * | Ctrl  |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   | Enter |
 * |-------+-------+-------+-------+-------+---------------+-------+-------+-------+-------+-------|
 * | Shift |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   |   "   |
 * |-------+-------+-------+-------+-------+-------|-------+-------+-------+-------+-------+-------|
 * |Alt/Tab|   Z   |   X   |   C   |   V   | Fn/SPC|   B   |   N   |   M   |   ,   |   .   |Adj/ / |
 * `-----------------------------------------------------------------------------------------------'
 */

[_QWERTY] = {
  {GUI_T(KC_ESC), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,                   KC_7, KC_8, KC_9,    KC_0,    KC_BSPC},
  {KC_LCTL,       KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y,                   KC_U, KC_I, KC_O,    KC_P,    KC_ENT},
  {KC_LSFT,       KC_A, KC_S, KC_D, KC_F, KC_G, KC_H,                   KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT},
  {ALT_T(KC_TAB), KC_Z, KC_X, KC_C, KC_V, KC_B, LT(_QWERTY_FN, KC_SPC), KC_N, KC_M, KC_COMM, KC_DOT,  LT(_ADJUST, KC_SLASH)},
},

/* FN-key held (Qwerty)
 * ,-----------------------------------------------------------------------------------------------.
 * |  Gui  |   F1  |   F2  |   F3  |   F4  |   F5  |   F6  |   F7  |   F8  |   F9  |  F10  |  F11  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Ctrl |   ~   |       |  PgUp |       |       |       |       |   Up  |   -   |   =   |  F12  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Shift |       |  Home |  PgDn |  End  |  Del  |       |  Left |  Down | Right |   [   |   ]   |
 * |-------+-------+-------+-------+-------+-------|-------+-------+-------+-------+-------+-------|
 * |Alt/Tab|       |       |       |       | Fn/Spc|       | Insert| PrtSc | Pause |  Menu |   \   |
 * `-----------------------------------------------------------------------------------------------'
 */

[_QWERTY_FN] = {
  {KC_LGUI, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,     KC_F6,   KC_F7,   KC_F8,    KC_F9,    KC_F10,      KC_F11},
  {_______, KC_GRAVE, XXXXXXX, KC_PGUP, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, KC_UP,    KC_MINUS, KC_EQUAL,    KC_F12},
  {_______, XXXXXXX,  KC_HOME, KC_PGDN, KC_END,  KC_DELETE, XXXXXXX, KC_LEFT, KC_DOWN,  KC_RIGHT, KC_LBRACKET, KC_RBRACKET},
  {_______, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, _______,   XXXXXXX, KC_INS,  KC_PSCR,  KC_PAUSE, KC_MENU,     KC_BSLASH}
},

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------------------.
 * |   S   |   T   |   P   |   H   |   *   |   F   |   P   |   L   |   T   |   D   |       |       |
 * |-------+-------+-------+-------+-------+-------|-------+-------+-------+-------+-------+-------|
 * |   S   |   K   |   W   |   R   |   *   |   R   |   B   |   G   |   S   |   Z   |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |   #   |   #   |   #   |   #   |       |   #   |   #   |   #   |   #   |   #   |       |       |
 * |-------+-------+-------+-------+-------+---------------+-------+-------+-------+-------+-------|
 * |       |       |   A   |   O   |       |   E   |   U   |       |       |       |       | Adjust|
 * `-----------------------------------------------------------------------------------------------'
 */

[_PLOVER] = {
  {KC_Q,    KC_W,    KC_E, KC_R, KC_T,    KC_U, KC_I, KC_O,    KC_P,    KC_LBRC, XXXXXXX, XXXXXXX},
  {KC_A,    KC_S,    KC_D, KC_F, KC_G,    KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT, XXXXXXX, XXXXXXX},
  {KC_1,    KC_1,    KC_1, KC_1, XXXXXXX, KC_1, KC_1, KC_1,    KC_1,    KC_1,    XXXXXXX, XXXXXXX},
  {XXXXXXX, XXXXXXX, KC_C, KC_V, XXXXXXX, KC_N, KC_M, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MO(_ADJUST)}
},

/* Adjust
 * ,-----------------------------------------------------------------------------------------------.
 * |       |       |       |       |       |       |       |       |       |       |       | RESET |
 * |-------+-------+-------+-------+-------+---------------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       | CapLk |Voice +| Audio |MIDIoff|       |
 * |-------+-------+-------+-------+-------+-------|-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       | ScrLk |Voice -| Music |MIDI on|       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       | Numlk |Workman| Qwerty| Plover| Adjust|
 * `-----------------------------------------------------------------------------------------------'
 */

[_ADJUST] = {
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET},
  {_______, _______, _______, _______, _______, _______, _______, KC_CLCK, MUV_IN,  AU_TOG,  MI_OFF,  _______},
  {_______, _______, _______, _______, _______, _______, _______, KC_SLCK, MUV_DE,  MU_TOG,  MI_ON,   _______},
  {_______, _______, _______, _______, _______, _______, _______, KC_NLCK, WORKMAN, QWERTY,  PLOVER,  _______}
}

};

#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_goodbye[][2]    = SONG(GOODBYE_SOUND);

float tone_workman[][2]    = SONG(QWERTY_SOUND);
float tone_qwerty[][2]     = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);

float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

#endif


void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case WORKMAN:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_workman, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_WORKMAN);
      }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_plover, false, 0);
        #endif
        if (!eeconfig_is_enabled()) {
          eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
        persistant_default_layer_set(1UL<<_PLOVER);
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
