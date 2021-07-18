#include QMK_KEYBOARD_H
#include "prototype30.h"
#include "keymap_italian.h"


extern keymap_config_t keymap_config;
bool alt_tab_enabled;
uint32_t alt_tab_timer;

// custom keycodes
enum prototype30_tapcodes {
  TD_Q_ESC,
  TD_P_BKSP,
  TD_I_UP,
  TD_K_DOWN,
  TD_J_LEFT,
  TD_L_RIGHT
};

//Friendly Layer Names
enum prototype30_layers {
  _QWERTY,
  _SUPER,
  _SHIFT_SUPER,
  _LOWER,
  _ACCENT,
  _ALT_TAB,
  _MUSIC
};


// custom keycodes
enum prototype30_keycodes {
  QWERTY = SAFE_RANGE,
  SUPER,
  LOWER,
  BOOT,
  BACKLIT,
  ALT_TAB,
  PLAY_1,
  PLAY_2,
  PLAY_3,
  MUSIC,
  MUSIC_OFF
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_ortho_3x10(
    TD(TD_Q_ESC),   KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,   KC_U,  TD(TD_I_UP),     KC_O,    TD(TD_P_BKSP),
    LGUI_T(KC_A),   LT(_ALT_TAB,KC_S),  KC_D,  KC_F,  KC_G,  KC_H,   TD(TD_J_LEFT),  TD(TD_K_DOWN),     TD(TD_L_RIGHT),  RGUI_T(KC_ENT),
    LSFT_T(KC_Z),   LCTL_T(KC_X), LALT_T(KC_C), LT(_ACCENT,KC_V),  LT(_SHIFT_SUPER, KC_BSPC),  LT(_SUPER, KC_SPC),  LT(_ACCENT, KC_B), RALT_T(KC_N),  RCTL_T(KC_M),  RSFT_T(IT_COMM)
  ),
  [_SUPER] = LAYOUT_ortho_3x10(
    KC_1,  KC_2,  KC_3,  IT_MINS,  IT_EQL,   IT_BKSL,  KC_HOME,  KC_UP,    KC_END,    KC_BSPC,
    KC_4,  KC_5,  KC_6,  IT_LBRC,  IT_RBRC,  IT_SLSH,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  KC_DEL ,
    LT(_SHIFT_SUPER, KC_7), KC_8,  KC_9,     KC_0,  MO(_LOWER),   _______,  IT_QST,  IT_LESS,  IT_APOS,   IT_DOT
  ),
  [_SHIFT_SUPER] = LAYOUT_ortho_3x10(
    IT_EXLM, IT_AT,   IT_SHRP, IT_UNDS,  IT_PLUS,   IT_PIPE,  S(KC_HOME),  S(KC_UP),    S(KC_END),    _______,
    IT_DLR,  IT_PERC, IT_CRC,  IT_LCBR,  IT_RCBR,  IT_MORE, S(KC_LEFT),  S(KC_DOWN),  S(KC_RIGHT),  _______ ,
    IT_AMPR, IT_ASTR, IT_LPRN, IT_RPRN,  _______,   MO(_LOWER),  IT_SCLN,  IT_MORE,  IT_DQOT,   IT_COLN
  ),
  [_LOWER] = LAYOUT_ortho_3x10(
    BL_STEP, RGB_TOG,  PLAY_1,  KC_MUTE,  XXXXXXX,  KC_WH_U,  KC_MS_BTN1,  KC_MS_U,  KC_MS_BTN2,  KC_PGUP,
    KC_TAB,  RGB_MOD,  PLAY_2,  KC_VOLU,  XXXXXXX,  KC_WH_D,  KC_MS_L,     KC_MS_D,  KC_MS_R,     KC_PGDN,
    KC_LSFT, XXXXXXX,  PLAY_3,  KC_VOLD,  _______,  KC_DOT,   BOOT,       XXXXXXX,  KC_LGUI,     KC_RSFT
  ),
  [_ACCENT] = LAYOUT_ortho_3x10(
    IT_EURO, XXXXXXX, IT_EACC, KC_F1,   KC_F2,   KC_F3,   IT_UACC, IT_IACC, IT_OACC, XXXXXXX,
    IT_AACC, KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_LSFT, KC_LCTL, KC_LALT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_RALT, KC_RCTL, KC_RSFT
  ),
  [_ALT_TAB] = LAYOUT_ortho_3x10(
    ALT_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______
  ),
  [_MUSIC] = LAYOUT_ortho_3x10(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MUSIC_OFF
  ),
};

#ifdef AUDIO_ENABLE

const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_ortho_3x10(
    19, 20, 21, 22, 23, 29, 30, 31, 32, 33,
    12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
     0,  1,  2,  3,  4,  5,  6,  7,  15, 16
);

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
float tone_goodbye[][2] = SONG(GOODBYE_SOUND);

float tone_1[][2]     = SONG(ODE_TO_JOY);
float tone_2[][2]  = SONG(CAMPANELLA);
float tone_3[][2]     = SONG(FANTASIE_IMPROMPTU);

#endif

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ALT_TAB:
      if (record->event.pressed) {
        alt_tab_enabled = true;
        register_code(KC_LGUI);
        tap_code(KC_TAB);
      }
      break;
    case BOOT:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_plover_gb);
          wait_ms(500);
        #endif
        reset_keyboard();
      }
      return false;
      break;
    case MUSIC:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_plover_gb);
          music_on();
          layer_on(_MUSIC);
        #endif
      }
      return false;
      break;
    case PLAY_1:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_1);
        #endif
      }
      return false;
      break;
    case PLAY_2:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_2);
        #endif
      }
      return false;
      break;
    case PLAY_3:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_3);
        #endif
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE

        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_plover_gb);
        #endif

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
        set_tempo(255);
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    wait_ms(20); // gets rid of tick
    PLAY_SONG(tone_startup);
}

void shutdown_user()
{
    PLAY_SONG(tone_goodbye);
    wait_ms(150);
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

bool music_mask_user(uint16_t keycode) {

  switch (keycode) {
    case MUSIC_OFF:
      music_off();
      layer_state_set(_QWERTY);
      return false;

    default:
      return true;
  }
}

#endif

void matrix_scan_user(void) {

  if (alt_tab_enabled && (get_highest_layer(layer_state)==_QWERTY)) {
    unregister_code(KC_LGUI);
    alt_tab_enabled=false;
   }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_Q_ESC]   = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
  [TD_P_BKSP]  = ACTION_TAP_DANCE_DOUBLE(KC_P, KC_BSPC),
  [TD_I_UP]    = ACTION_TAP_DANCE_DOUBLE(KC_I, KC_UP),
  [TD_K_DOWN]  = ACTION_TAP_DANCE_DOUBLE(KC_K, KC_DOWN),
  [TD_J_LEFT]  = ACTION_TAP_DANCE_DOUBLE(KC_J, KC_LEFT),
  [TD_L_RIGHT] = ACTION_TAP_DANCE_DOUBLE(KC_L, KC_RIGHT),
};
