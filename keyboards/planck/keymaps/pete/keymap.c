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
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _FCT 5
#define _SETUP 6
#define _MAC 7
#define _WIN 8
#define _LIN 9
#define _MICMUTE 16
#define _OS 17


// Macro name shortcuts
#define QWERTY M(_QWERTY)
#define COLEMAK M(_COLEMAK)
#define DVORAK M(_DVORAK)
#define LOWER M(_LOWER)
#define RAISE M(_RAISE)
#define FCT M(_FCT)
#define OS M(_OS)
#define MAC M(_MAC)
#define WIN M(_WIN)
#define LIN M(_LIN)
#define MICMUTE M(_MICMUTE)

#define MACPRNT LGUI(LSFT(KC_3))
#define MACPRNT2 LGUI(LSFT(KC_4))
#define WINPRNT KC_PSCR
#define WINPRNT2 LGUI(KC_PSCR)
#define CYCLWIN LGUI(KC_GRV)
#define MACSLEEP LSFT(LCTL(KC_POWER))
#define WINSLEEP KC_SLEP

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
  {OS,     KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

[_COLEMAK] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC},
  {KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
  {OS,      KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

[_DVORAK] = {
  {KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC},
  {KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH},
  {KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT },
  {OS,      KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

[_LOWER] = {
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
  {_______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______,  _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},

[_RAISE] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {_______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_RAISE,  _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},

[_SETUP] = { /* Setup */
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, WIN,     MAC,     _______, _______, QWERTY,  COLEMAK, DVORAK,  _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, RESET,   RESET,   _______, _______, _______, _______, _______}
},
[_MAC] = { /* Mac */
  {CYCLWIN,MACSLEEP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_DELT},
  {_______, MICMUTE, KC_MUTE, KC_VOLD, KC_VOLU, MACPRNT,MACPRNT2, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX},
  {_______, BL_STEP, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX},
  {_______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDOWN,KC_PGUP,KC_END }
},
[_WIN] = { /* Windows */
  {CYCLWIN,WINSLEEP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_DELT},
  {_______, MICMUTE, KC_MUTE, KC_VOLD, KC_VOLU, WINPRNT,WINPRNT2, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX},
  {_______, BL_STEP, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX},
  {_______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDOWN,KC_PGUP,KC_END }
},
[_LIN] = { /* Linux */
  {KC_L,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}

};

int currentOs = _MAC;
const uint16_t PROGMEM fn_actions[] = {

};

#ifdef AUDIO_ENABLE

float tone_startup[][2] = {
  {440.0*pow(2.0,(31)/12.0), 12},
  {440.0*pow(2.0,(28)/12.0), 8},
  {440.0*pow(2.0,(19)/12.0), 8},
  {440.0*pow(2.0,(24)/12.0), 8},
  {440.0*pow(2.0,(28)/12.0), 20}
};

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);

float music_scale[][2] = SONG(MUSIC_SCALE_SOUND);
float goodbye[][2] = SONG(GOODBYE_SOUND);
#endif


void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case _QWERTY:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
            #endif
            persistant_default_layer_set(1UL<<_QWERTY);
          }
          break;
        case _COLEMAK:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_NOTE_ARRAY(tone_colemak, false, 0);
            #endif
            persistant_default_layer_set(1UL<<_COLEMAK);
          }
          break;
        case _DVORAK:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_NOTE_ARRAY(tone_dvorak, false, 0);
            #endif
            persistant_default_layer_set(1UL<<_DVORAK);
          }
          break;
        case _LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _SETUP);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _SETUP);
          }
          break;
        case _RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _SETUP);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _SETUP);
          }
          break;
        case _FCT:
          if (record->event.pressed) {
            layer_on(_FCT);
          } else {
            layer_off(_FCT);
          }
        break;
        case _MICMUTE:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            register_code(KC_RCTL);
            register_code(KC_RALT);
            register_code(KC_RGUI);
          } else {
            unregister_code(KC_RSFT);
            unregister_code(KC_RCTL);
            unregister_code(KC_RALT);
            unregister_code(KC_RGUI);
          } 
        break;
        case _OS:
          if (record->event.pressed) {
            layer_on(currentOs);
          } else {
            layer_off(_MAC);
            layer_off(_WIN);
            layer_off(_LIN);
          }
        break;
        case _MAC:
        case _WIN:
        case _LIN:
          if (record->event.pressed) {
            layer_off(currentOs);
            currentOs = id;
          }
        break;        
      }
    return MACRO_NONE;
};

void matrix_init_user(void) {
  #ifdef AUDIO_ENABLE
    _delay_ms(20); // stops the tick
    PLAY_NOTE_ARRAY(tone_startup, false, 0);
  #endif
}

#ifdef AUDIO_ENABLE
void play_goodbye_tone()
{
  PLAY_NOTE_ARRAY(goodbye, false, 0);
  _delay_ms(150);
}

uint8_t starting_note = 0x0C;
int offset = 0;

bool process_action_user(keyrecord_t *record) {

  if (IS_LAYER_ON(_MUSIC)) {
    if (record->event.pressed) {
        play_note(((double)220.0)*pow(2.0, -4.0)*pow(2.0,(starting_note + SCALE[record->event.key.col + offset])/12.0+(MATRIX_ROWS - record->event.key.row)), 0xF);
    } else {
        stop_note(((double)220.0)*pow(2.0, -4.0)*pow(2.0,(starting_note + SCALE[record->event.key.col + offset])/12.0+(MATRIX_ROWS - record->event.key.row)));
    }
    return false;
  }
  return true;
}
#endif
