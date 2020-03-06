//Author: mike terhar
#include QMK_KEYBOARD_H

#ifdef BACKLIGHT_ENABLE
  #include "backlight.h"
#endif

enum minivan_layers {
  _QWERTY,
  _NUMSYM,
  _FKEYS,
  _FKEYGRV,
  _PLOVER,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  DYNKEY,
  DYNAMIC_MACRO_RANGE,
};

#define FKEYS LT(_FKEYS, KC_TAB)
#define NUMSYM TT(_NUMSYM)
#define FKEYGRV LT(_FKEYS, KC_GRV)
#define MACSLEEP M(5)
#define PLOVER M(6)
#define LAYERRESET M(7)
#define BACKLIT M(8)
#define ADJUST M(9)

#include "dynamic_macro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = {
  {FKEYS, KC_Q,   KC_W,   KC_E, KC_R,   KC_T,   KC_Y,   KC_U, KC_I,   KC_O,  KC_P,   KC_BSPC},
  {KC_ESC, KC_A,   KC_S,   KC_D, KC_F,   KC_G,   KC_H,   KC_J, KC_K,   KC_L,  KC_SCLN,KC_QUOT},
  {KC_LSFT,KC_Z,   KC_X,   KC_C, KC_V,   KC_B,   KC_N,   KC_M, KC_COMM,KC_DOT,KC_SLSH,SFT_T(KC_ENT) },
  {KC_LCTL,KC_LALT,KC_LGUI, KC_SPC,XXXXXXX,XXXXXXX,XXXXXXX,NUMSYM,KC_LEFT,KC_DOWN,KC_UP ,KC_RIGHT}
},
[_NUMSYM] = {
  {FKEYGRV,  KC_1,  KC_2,    KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,  _______},
  {KC_DEL,KC_EXLM, KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN, ADJUST },
  { _______,  KC_UNDS,KC_PLUS, KC_LCBR,KC_RCBR,KC_PIPE , KC_MINS,KC_EQL,KC_LBRC, KC_RBRC, KC_BSLS, _______},
  {_______,_______,_______,_______,XXXXXXX,XXXXXXX,XXXXXXX,_______,    KC_HOME, KC_PGDN, KC_PGUP, KC_END}
},
[_FKEYS] ={
  {_______, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5, KC_F6, KC_F7,  KC_F8,  KC_F9,  KC_F10, _______},
  {KC_DEL, KC_F11, KC_F12,  KC_F13,  KC_F14,  KC_F15, _______, _______,  _______,  MACSLEEP, DYN_REC_START1, DYN_REC_START2 },
  {KC_CAPS,  _______, _______,  _______,  _______, _______, _______, _______, DYN_MACRO_PLAY1, DYN_MACRO_PLAY2,_______,DYN_REC_STOP},
  {_______,_______,_______,LAYERRESET,XXXXXXX,XXXXXXX,XXXXXXX,LAYERRESET,    KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},
[_PLOVER] = {
  {KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   },
  {XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC},
  {XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {LAYERRESET, XXXXXXX, KC_C,    KC_V,   XXXXXXX ,  XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX}
},
[_ADJUST] = {
 {_______ , RESET,   _______, _______, _______, _______, _______, _______, KC_SLCK, KC_PAUS, KC_PSCR, KC_DEL },
 {_______ , _______, _______, _______, _______,  AG_NORM, AG_SWAP, QWERTY,  _______, MACSLEEP,  PLOVER, _______},
 {_______ , _______,  _______,  _______,   _______,  _______,   _______,  _______, _______, _______, _______, _______},
 {BACKLIT, _______, _______, LAYERRESET, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______}
}
};

#ifdef AUDIO_ENABLE

float tone_startup[][2]           = SONG(STARTUP_SOUND);
float tone_qwerty[][2]            = SONG(QWERTY_SOUND);
float tone_dyn_macro_rec[][2]     = SONG(DVORAK_SOUND);
float tone_dyn_macro_play[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]            = SONG(PLOVER_SOUND);
float tone_adjust[][2]            = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]            = SONG(MUSIC_SCALE_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 5: // MACSLEEP
            if (record->event.pressed) {
              register_code(KC_RSFT);
              register_code(KC_RCTL);
              register_code(KC_POWER);
              unregister_code(KC_POWER);
              unregister_code(KC_RCTL);
              unregister_code(KC_RSFT);
            }
        break;
        case 6: // PLOVER
              if (record->event.pressed) {
              #ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_NOTE_ARRAY(tone_plover, false, 0);
              #endif
              layer_off(_NUMSYM);
              layer_off(_FKEYS);
              layer_off(_ADJUST);
              layer_on(_PLOVER);
            }
        break;
        case 7: // LAYERRESET
              if (record->event.pressed) {
              #ifdef AUDIO_ENABLE
                PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
              #endif
              layer_off(_NUMSYM);
              layer_off(_FKEYS);
              layer_off(_PLOVER);
              layer_off(_ADJUST);
            }
        break;
        case 8: // BACKLIT
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        break;
        case 9: // ADJUST
          if(record->event.pressed) {
            #ifdef AUDIO_ENABLE
              stop_all_notes();
              PLAY_NOTE_ARRAY(tone_adjust, false, 0);
            #endif
            layer_off(_NUMSYM);
            layer_off(_FKEYS);
            layer_off(_PLOVER);
            layer_on(_ADJUST);
          }
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint16_t macro_kc = keycode;
  if (keycode == FKEYS || keycode == ADJUST || keycode == FKEYGRV ){
    macro_kc = DYN_REC_STOP;
  }
  if (!process_record_dynamic_macro(macro_kc, record)) {
    return false;
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
