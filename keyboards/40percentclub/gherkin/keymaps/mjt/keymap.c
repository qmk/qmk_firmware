#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

extern keymap_config_t keymap_config;

//Tap Dance Declarations
enum {
  TD_Z_LCTL = 0,
  TD_X_LGUI = 1,
  TD_C_LALT = 2,
  TD_A_TAB = 3,
  TD_Q_ESC = 4,
};

//Friendly Layer Names
enum gherkin_layers {
  _QWERTY,
  _SONGS,
  _NUMBERS,
  _SYMBOLS,
  _PLOVER,
  _ADJUST
};

// custom keycodes
enum gherkin_keycodes {
  QWERTY = SAFE_RANGE,
  NUMBERS,
  SYMBOLS,
  SONGS,
  PLOVER,
  BACKLIT,
  MACSLEEP,
  EXT_PLV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_ortho_3x10(
    TD(TD_Q_ESC),   KC_W,               KC_E,           KC_R,  KC_T,               KC_Y,   KC_U,  KC_I,     KC_O,    KC_P,
    TD(TD_A_TAB),   LT(_SYMBOLS,KC_S),  KC_D,           KC_F,  KC_G,               KC_H,   KC_J,  KC_K,     KC_L,    LT(_ADJUST,KC_SPC),
    TD(TD_Z_LCTL),  TD(TD_X_LGUI),      TD(TD_C_LALT),  KC_V,  KC_B,  LT(_NUMBERS, KC_N),  KC_M,  KC_COMM,  KC_DOT,  SFT_T(KC_ENT)
  ),
  [_NUMBERS] = LAYOUT_ortho_3x10(
    KC_1,   KC_2,   KC_3,   KC_4,    KC_5,                KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
    KC_F1,  KC_F2,  KC_F3,  KC_F4,   KC_F5,               KC_F6,    KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END ,
    KC_F7,  KC_F8,  KC_F9,  KC_F10,  LT(_ADJUST,KC_F11),  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT
  ),
  [_SYMBOLS] = LAYOUT_ortho_3x10(
    KC_EXLM,  KC_AT,        KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,     KC_RPRN,
    KC_GRV,   _______,      XXXXXXX,  KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_MINS,  KC_EQL ,  KC_SCLN,     KC_QUOT,
    KC_TILD,  MO(_ADJUST),  XXXXXXX,  KC_LCBR,  KC_RCBR,  KC_PIPE,  KC_UNDS,  KC_PLUS,  S(KC_SCLN),  S(KC_QUOT)
  ),
  [_PLOVER] = LAYOUT_ortho_3x10(
    KC_Q,     KC_W,     KC_E,  KC_R,  KC_1,     KC_U,  KC_I,  KC_O,     KC_P,     KC_LBRC,
    KC_A,     KC_S,     KC_D,  KC_F,  KC_G,     KC_J,  KC_K,  KC_L,     KC_SCLN,  KC_QUOT,
    EXT_PLV,  XXXXXXX,  KC_C,  KC_V,  XXXXXXX,  KC_N,  KC_M,  XXXXXXX,  XXXXXXX,  XXXXXXX
  ),
  [_ADJUST] = LAYOUT_ortho_3x10(
    QK_BOOT,  _______,  _______,  _______,  _______,  QWERTY,   NUMBERS,  SYMBOLS,  PLOVER,    SONGS,
    AU_PREV,  AU_NEXT,  MU_ON,    MU_OFF,   _______,  _______,  _______,  _______,  MACSLEEP,  _______,
    BACKLIT,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______
  )
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
          PLAY_SONG(tone_qwerty);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case NUMBERS:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        persistant_default_layer_set(1UL<<_NUMBERS);
      }
      return false;
      break;
    case SYMBOLS:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        persistant_default_layer_set(1UL<<_SYMBOLS);
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(tone_plover);
        #endif
        layer_off(_NUMBERS);
        layer_off(_SYMBOLS);
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
          PLAY_SONG(tone_plover_gb);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
    case MACSLEEP:
      if (record->event.pressed) {
          // ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT, KC_PWR);
          register_code(KC_RSFT);
          register_code(KC_RCTL);
          register_code(KC_PWR);
          unregister_code(KC_PWR);
          unregister_code(KC_RCTL);
          unregister_code(KC_RSFT);
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
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE

void startup_user(void)
{
    _delay_ms(20); // gets rid of tick
    PLAY_SONG(tone_startup);
}

void shutdown_user(void)
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

//Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_Z_LCTL]  = ACTION_TAP_DANCE_DOUBLE(KC_Z, KC_LCTL),
  [TD_X_LGUI]  = ACTION_TAP_DANCE_DOUBLE(KC_X, KC_LGUI),
  [TD_C_LALT]  = ACTION_TAP_DANCE_DOUBLE(KC_C, KC_LALT),
  [TD_A_TAB]  = ACTION_TAP_DANCE_DOUBLE(KC_A, KC_TAB),
  [TD_Q_ESC]  = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC)
};
