#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef CONSOLE_ENABLE
  #include <print.h>
#endif
#include "layer_number.h"

extern keymap_config_t keymap_config;

extern uint8_t is_master;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  EUCALYN,
  KEYPAD,
  KC_xEISU,
  KC_xKANA,
  KC_ZERO2,
  RGBRST
};

//Macros
#define KC_LOWER  MO(_LOWER)
#define KC_RABS   LT(_RAISE,KC_BSPC)
#define KC_RAEN   LT(_RAISE,KC_ENT)
#define KC_FF12   LT(_PADFUNC,KC_F12)
#define KC_____   _______
#define KC_XXXX   XXXXXXX
#define KC_ADJ    MO(_ADJUST)
#define KC_LSMI   LSFT(KC_MINS)
#define KC_LSEQ   LSFT(KC_EQL)
#define KC_LSRB   LSFT(KC_RBRC)
#define KC_LSLB   LSFT(KC_LBRC)
#define ___       _______

#if MATRIX_ROWS == 10 // HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  BS  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  | Ctrl |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   `  |   '  |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Lower | Lower| Caps |  Alt |  GUI | Space|  BS  | Enter| Space| GUI  | Alt  | Menu |Lower |Lower |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT_kc( \
      ESC,    1,    2,    3,    4,    5,                  6,    7,    8,    9,    0,  BSPC, \
      TAB,    Q,    W,    E,    R,    T,                  Y,    U,    I,    O,    P,  BSLS, \
      LCTL,   A,    S,    D,    F,    G,                  H,    J,    K,    L, SCLN,  RCTL, \
      LSFT,   Z,    X,    C,    V,    B,    GRV,  QUOT,   N,    M, COMM,  DOT, SLSH,  RSFT, \
      LOWER, LOWER, CAPS, LALT, LGUI, SPC, RABS,  RAEN, SPC, RGUI, RALT,  APP,LOWER, LOWER \
      ),

  /* Colemak
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   F  |   P  |   G  |             |   J  |   L  |   U  |   Y  |   ;  | \    |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   R  |   S  |   T  |   D  |             |   H  |   N  |   E  |   I  |   O  | Ctrl |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   `  |   '  |   K  |   M  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Lower | Lower| Caps |  Alt |  GUI | Space|  BS  | Enter| Space| GUI  | Alt  | Menu |Lower |Lower |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_COLEMAK] = LAYOUT_kc( \
      ESC,    1,    2,    3,    4,    5,                  6,    7,    8,    9,    0,  BSPC, \
      TAB,    Q,    W,    F,    P,    G,                  J,    L,    U,    Y, SCLN,  BSLS, \
      LCTL,   A,    R,    S,    T,    D,                  H,    N,    E,    I,    O,  RCTL, \
      LSFT,   Z,    X,    C,    V,    B,    GRV,  QUOT,   K,    M, COMM,  DOT, SLSH,  RSFT, \
      LOWER, LOWER, CAPS, LALT, LGUI, SPC, RABS,  RAEN, SPC, RGUI, RALT,  APP,LOWER, LOWER \
      ),

  /* Dvorak
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   '  |   ,  |   .  |   P  |   Y  |             |   F  |   G  |   C  |   R  |   L  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   O  |   E  |   U  |   I  |             |   D  |   H  |   T  |   N  |   S  | Ctrl |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   ;  |   Q  |   J  |   K  |   X  |   `  |   /  |   B  |   M  |   W  |   V  |   Z  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Lower | Lower| Caps |  Alt |  GUI | Space|  BS  | Enter| Space| GUI  | Alt  | Menu |Lower |Lower |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_DVORAK] = LAYOUT_kc( \
      ESC,    1,    2,    3,    4,    5,                  6,    7,    8,    9,    0,  BSPC, \
      TAB, QUOT, COMM,  DOT,    P,    Y,                  F,    G,    C,    R,    L,  BSLS, \
      LCTL,   A,    O,    E,    U,    I,                  D,    H,    T,    N,    S,  RCTL, \
      LSFT, SCLN,   Q,    J,    K,    X,    GRV,  SLSH,   B,    M,    W,    V,    Z,  RSFT, \
      LOWER, LOWER, CAPS, LALT, LGUI, SPC, RABS,  RAEN, SPC, RGUI, RALT,  APP,LOWER, LOWER \
      ),

  /* Eucalyn (http://eucalyn.hatenadiary.jp/entry/about-eucalyn-layout)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   ,  |   .  |   ;  |             |   M  |   R  |   D  |   Y  |   P  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   O  |   E  |   I  |   U  |             |   G  |   T  |   K  |   S  |   N  | Ctrl |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   F  |   `  |   '  |   B  |   H  |   J  |   L  |   /  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Lower | Lower| Caps |  Alt |  GUI | Space|  BS  | Enter| Space| GUI  | Alt  | Menu |Lower |Lower |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_EUCALYN] = LAYOUT_kc( \
      ESC,    1,    2,    3,    4,    5,                  6,    7,    8,    9,    0,  BSPC, \
      TAB,    Q,    W, COMM,  DOT, SCLN,                  M,    R,    D,    Y,    P,  BSLS, \
      LCTL,   A,    O,    E,    I,    U,                  G,    T,    K,    S,    N,  RCTL, \
      LSFT,   Z,    X,    C,    V,    F,    GRV,  QUOT,   B,    H,    J,    L, SLSH,  RSFT, \
      LOWER, LOWER, CAPS, LALT, LGUI, SPC, RABS,  RAEN, SPC, RGUI, RALT,  APP,LOWER, LOWER \
      ),

  /* Keypad
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Tab  |   /  |   *  | Del  |  F1  |  F6  |             |  F1  |  F6  | Del  | Tab  |   /  |   *  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   7  |   8  |   9  | BS   |  F2  |  F7  |             |  F2  |  F7  | BS   |   7  |   8  |   9  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   4  |   5  |   6  |  -   |  F3  |  F8  |             |  F3  |  F8  |  -   |   4  |   5  |   6  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |   1  |   2  |   3  |  +   |  F4  |  F9  |  F11 |  F11 |  F4  |  F9  |  +   |   1  |   2  |   3  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |   0  |   ,  |   .  | Enter|  F5  |  F10 |  F12 |  F12 |  F5  |  F10 | Enter|   0  |  ,   |   .  |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_KEYPAD] = LAYOUT_kc( \
      TAB,  PSLS, PAST, DEL,    F1,   F6,               F1,   F6,  DEL,  TAB, PSLS, PAST, \
      KP_7, KP_8, KP_9, BSPC,   F2,   F7,               F2,   F7, BSPC, KP_7, KP_8, KP_9, \
      KP_4, KP_5, KP_6, PMNS,   F3,   F8,               F3,   F8, PMNS, KP_4, KP_5, KP_6, \
      KP_1, KP_2, KP_3, PPLS,   F4,   F9,  F11,  F11,   F4,   F9, PPLS, KP_1, KP_2, KP_3, \
      KP_0, COMM, PDOT, PENT,   F5,  F10, FF12, FF12,   F5,  F10, PENT, KP_0, COMM, PDOT \
      ),

  /*  AUX modifier key layer
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |  00  |      |      |      |      |      |      |      |      |      |      |  00  |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_KAUX] = LAYOUT_kc( \
      ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____, \
      ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____, \
      ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____, \
      ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
      ____,ZERO2, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ZERO2,____ \
   ),

  /*  Keypad function layer
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      | Pause| ScrLk| PtrSc|             | PtrSc| ScrLk| Pause|      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      | Home |  Up  | PgUp |             | PgUp |  Up  | Home |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |Delete|Insert| Left | Down | Right|             | Left | Down | Right|Insert|Delete|      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      | End  |      | PgDn |Adjust|Adjust| PgDn |      | End  |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_PADFUNC] = LAYOUT_kc( \
      XXXX, XXXX, XXXX, PAUS, SLCK, PSCR,             PSCR, SLCK, PAUS, XXXX, XXXX, XXXX, \
      XXXX, XXXX, XXXX, HOME, UP,   PGUP,             PGUP, UP,   HOME, XXXX, XXXX, XXXX, \
      XXXX,  DEL,  INS, LEFT, DOWN, RGHT,             LEFT, DOWN, RGHT, INS,  DEL,  XXXX, \
      XXXX, XXXX, XXXX, END,  XXXX, PGDN,  ADJ,  ADJ, PGDN, XXXX, END,  XXXX, XXXX, XXXX, \
      XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, ____, ____, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX \
   ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |Pause | ScrLk| Ins  |      |             |      | Ins  | ScrLk|Pause |      | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | PgUp |      | Up   |Delete| Home |             | Home |Delete| Up   |      | PgUp |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      | PgDn | Left | Down | Right| End  |Adjust|Adjust| End  | Left | Down | Right| PgDn |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      | PrtSc|      |      |      |      |      |      |      |      | PrtSc|      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT_kc( \
      XXXX,  F1,   F2,   F3,   F4,   F5,                F6,   F7,   F8,   F9,  F10,  F11, \
      XXXX, XXXX, PAUS, SLCK, INS,  XXXX,             XXXX,  INS, SLCK, PAUS, XXXX,  F12, \
      ____, HOME, XXXX, UP,   DEL,  PGUP,             PGUP,  DEL,   UP, XXXX, HOME, ____, \
      ____, END,  LEFT, DOWN, RGHT, PGDN, XXXX, XXXX, PGDN, LEFT, DOWN, RGHT,  END, ____, \
      ____, ____, PSCR, ____, ____, ____,  ADJ,  ADJ, ____, ____, ____, PSCR, ____, ____ \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |  _   |  -   |             |  =   |  +   |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |  {   |  [   |             |  ]   |  }   |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      | EISU | EISU | KANA | KANA | Next | Vol- | Vol+ | Play |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT_kc( \
      XXXX, XXXX, XXXX, XXXX, XXXX, XXXX,             XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, \
      XXXX, XXXX, XXXX, XXXX, LSMI, MINS,              EQL, LSEQ, XXXX, XXXX, XXXX, XXXX, \
      ____, XXXX, XXXX, XXXX, LSLB, LBRC,             RBRC, LSRB, XXXX, XXXX, XXXX, ____, \
      ____, XXXX, XXXX, XXXX, XXXX,xEISU,xEISU, xKANA,xKANA,MNXT, VOLD, VOLU, MPLY, ____, \
      ADJ,   ADJ, XXXX, ____, ____, XXXX, ____, ____, XXXX, ____, ____, XXXX,  ADJ,  ADJ \
      ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |Keypad|Dvorak|Colemk|Euclyn|Qwerty|             |Qwerty|Euclyn|Colemk|Dvorak|Keypad|      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Reset|RGBRST|RGB ON|Aud on| Win  |             | Win  |Aud on|RGB ON|RGBRST|      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | HUE+ | SAT+ | VAL+ |RGB md|Audoff| Mac  |             | Mac  |Audoff|RGB md| VAL+ | SAT+ | HUE+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | HUE- | SAT- | VAL- |      |      |      |      |      |      |      |      | VAL- | SAT- | HUE- |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
      XXXXXXX, KEYPAD,  DVORAK,  COLEMAK, EUCALYN,  QWERTY,          QWERTY,  EUCALYN, COLEMAK,  DVORAK,  KEYPAD, XXXXXXX, \
      XXXXXXX, RESET,   RGBRST,  RGB_TOG,   AU_ON, AG_SWAP,          AG_SWAP,   AU_ON, RGB_TOG,  RGBRST, XXXXXXX, XXXXXXX, \
      RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD,  AU_OFF, AG_NORM,          AG_NORM,  AU_OFF, RGB_MOD, RGB_VAI, RGB_SAI, RGB_HUI, \
      RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, ___,___, XXXXXXX, XXXXXXX, XXXXXXX, RGB_VAD, RGB_SAD, RGB_HUD, \
      _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ___,___, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______ \
   ),

  /*  AUX modifier key layer
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |  BS  | Enter|      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_AUX] = LAYOUT_kc( \
      ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____, \
      ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____, \
      ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____, \
      ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
      ____, ____, ____, ____, ____, BSPC, RAEN, ____, ____, ____, ____, ____, ____, ____ \
      )
};

#else
#error "undefined keymaps"
#endif


#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

int current_default_layer;

uint32_t default_layer_state_set_kb(uint32_t state) {
    // 1<<_QWERTY  - 1 == 1 - 1 == _QWERTY (=0)
    // 1<<_COLEMAK - 1 == 2 - 1 == _COLEMAK (=1)
    current_default_layer = state - 1;
    // 1<<_DVORAK  - 2 == 4 - 2 == _DVORAK (=2)
    if ( current_default_layer == 3 ) current_default_layer -= 1;
    // 1<<_EUCALYN - 5 == 8 - 5 == _EUCALYN (=3)
    if ( current_default_layer == 7 ) current_default_layer -= 4;
    // 1<<_KEYPAD  - 12 == 16 - 12 == _KEYPAD (=4)
    if ( current_default_layer == 15 ) current_default_layer -= 11;
    return state;
}

void update_base_layer(int base)
{
    if( current_default_layer != base ) {
        eeconfig_update_default_layer(1UL<<base);
        default_layer_set(1UL<<base);
        layer_off(_AUX);
        layer_off(_KAUX);
    } else {
        if( base < _KEYPAD )
            layer_invert(_AUX);
        else
            layer_invert(_KAUX);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        update_base_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        update_base_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        update_base_layer(_DVORAK);
      }
      return false;
      break;
    case EUCALYN:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        update_base_layer(_EUCALYN);
      }
      return false;
      break;
    case KEYPAD:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        update_base_layer(_KEYPAD);
      }
      return false;
      break;
    case KC_ZERO2:
      if (record->event.pressed) {
          SEND_STRING("00");
      }
      return false;
      break;
    case KC_xEISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KC_xKANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      break;
  }
  return true;
}

void matrix_init_user(void) {
#ifdef AUDIO_ENABLE
    startup_user();
#endif
    INIT_HELIX_OLED();
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
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
