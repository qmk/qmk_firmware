#include "preonic.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

// Layer names
#define _COLEMAK 0
#define _GAME 1
#define _RAISE 2

enum preonic_keycodes {
  COLEMAK = SAFE_RANGE,
  GAME,
  RAISE
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   \  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   =  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   [  |   ]  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   -  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |   '  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ;  |   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  | ENTER|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ESC  | ALT  | GUI  | SHIFT| CTRL | BKSP | SPACE| RAISE| SHIFT|      | DEL  | TAB  |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = {
  {KC_GRV ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_BSLS},
  {KC_EQL ,KC_Q   ,KC_W   ,KC_F   ,KC_P   ,KC_G   ,KC_J   ,KC_L   ,KC_U   ,KC_Y   ,KC_LBRC,KC_RBRC},
  {KC_MINS,KC_A   ,KC_R   ,KC_S   ,KC_T   ,KC_D   ,KC_H   ,KC_N   ,KC_E   ,KC_I   ,KC_O   ,KC_QUOT},
  {KC_SCLN,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,KC_K   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,KC_ENT },
  {KC_ESC ,KC_LALT,KC_LGUI,KC_LSFT,KC_LCTL,KC_BSPC,KC_SPC ,RAISE  ,KC_RSFT,_______,KC_DEL ,KC_TAB }
},

/* Game
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |NUM LK|   ÷  |   ×  |   -  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   1  |   2  |   3  |   +  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+
 * | CTRL |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   4  |   5  |   6  |   =  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+
 * | SHIFT|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   7  |   8  |   9  | ENTER|
 * |------+------+------+------+------+------+------+------+------+------+------+------+
 * |      | ALT  | GUI  | SPACE| CTRL | BKSP | SPACE| RAISE|   ,  |   0  |   .  | TAB  |
 * `-----------------------------------------------------------------------------------'
 */
[_GAME] = {
  {KC_ESC ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,KC_6   ,KC_7   ,KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS},
  {KC_TAB ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,KC_Y   ,KC_U   ,KC_P1  ,KC_P2  ,KC_P3  ,KC_PPLS},
  {KC_LCTL,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,KC_H   ,KC_J   ,KC_P4  ,KC_P5  ,KC_P6  ,KC_PEQL},
  {KC_LSFT,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,KC_N   ,KC_M   ,KC_P7  ,KC_P8  ,KC_P9  ,KC_PENT},
  {XXXXXXX,KC_LALT,KC_LGUI,KC_SPC ,KC_LCTL,KC_BSPC,KC_SPC ,RAISE  ,KC_PCMM,KC_P0  ,KC_PDOT,KC_TAB }
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | SLEEP|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |PRTSCR|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | SYM  |  F11 |  F12 |      |AU TOG| VOL+ |BL INC|COLMAK| GAME | MUSIC| MENU |SCRLCK|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAPS | PREV | STOP | PLAY | NEXT | VOL- |BL DEC| LEFT | DOWN |  UP  | RIGHT| PAUSE|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | BACK | STOP | RFRSH| FRWRD| MUTE |BL TOG| HOME | PGDN | PGUP | END  |INSERT|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | RESET|      |      |      |      | DEL  |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_SLEP,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_PSCR},
  {XXXXXXX,KC_F11 ,KC_F12 ,XXXXXXX,AU_TOG ,KC_VOLU,BL_INC ,COLEMAK,GAME   ,MU_TOG ,KC_MENU,KC_SLCK},
  {KC_CAPS,KC_MPRV,KC_MSTP,KC_MPLY,KC_MNXT,KC_VOLD,BL_DEC ,KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,KC_PAUS},
  {XXXXXXX,KC_WBAK,KC_WSTP,KC_WREF,KC_WFWD,KC_MUTE,BL_TOGG,KC_HOME,KC_PGDN,KC_PGUP,KC_END ,KC_INS },
  {RESET  ,_______,_______,_______,_______,KC_DEL ,_______,_______,_______,_______,_______,_______}
}

};



#ifdef AUDIO_ENABLE

float tone_startup[][2] = {
  {NOTE_B5, 20},
  {NOTE_B6, 8},
  {NOTE_DS6, 20},
  {NOTE_B6, 8}
};
float tone_colemak[][2] = SONG(COLEMAK_SOUND);
float tone_game[][2]    = {
  {NOTE_E6, 10}   ,{NOTE_E6, 10}  ,{NOTE_REST, 10} ,{NOTE_E6, 10}   ,
  {NOTE_REST, 10} ,{NOTE_C6, 10}  ,{NOTE_E6, 10}   ,{NOTE_REST, 10} ,
  {NOTE_G6, 10}   ,{NOTE_REST, 30},
  {NOTE_G5, 10}   ,{NOTE_REST, 30}
};
float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
float music_scale[][2]  = SONG(MUSIC_SCALE_SOUND);

void startup_user() {
  _delay_ms(20); // gets rid of tick
  PLAY_NOTE_ARRAY(tone_startup, false, 0);
}
void shutdown_user() {
  PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
  _delay_ms(150);
  stop_all_notes();
}

void music_on_user(void) {
  music_scale_user();
}
void music_scale_user(void) {
  PLAY_NOTE_ARRAY(music_scale, false, 0);
}

#endif



void matrix_init_user(void) {
  #ifdef AUDIO_ENABLE
  startup_user();
  #endif
}

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
        PLAY_NOTE_ARRAY(tone_colemak, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      break;
    case GAME:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
        PLAY_NOTE_ARRAY(tone_game, false, STACCATO);
        #endif
        persistent_default_layer_set(1UL<<_GAME);
      }
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      break;
    default:
      return true;
      break;
  }

  return false;
};
