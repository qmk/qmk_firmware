#include QMK_KEYBOARD_H
#include "no_keycodes.h"

#if __has_include("secrets.h")
#  include "secrets.h"
#else
#  define mail_str ""
#  define pwd_str ""
#endif

// layer definitions
enum planck_layers {
  _DEFAULT,
  _LOWER,
  _RAISE,
  _GAME,
  _GLOW
};

// macro definitions
enum planck_keycodes {
  BEEP = SAFE_RANGE,
};

// sounds
#ifdef AUDIO_ENABLE
  float onsong[][2]  = SONG(MARIO_MUSHROOM);
  float offsong[][2] = SONG(PLOVER_GOODBYE_SOUND);
  float beep[][2]    = SONG(TERMINAL_SOUND);
#endif

// macro declarations
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BEEP:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(beep);
        #endif
      }
      break;
  }
  return true;
};

// leader key
bool leader_succeed;
bool leader_layer_on;
bool leader_layer_off;
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leader_succeed = leading = false;
    leader_layer_on = false;
    leader_layer_off = false;

    SEQ_TWO_KEYS(KC_P, KC_P) {
      SEND_STRING(pwd_str);
      leader_succeed = true;
    }
    SEQ_TWO_KEYS(KC_P, KC_M) {
      SEND_STRING(mail_str);
      leader_succeed = true;
    }
    SEQ_TWO_KEYS(KC_B, KC_B) {
      SEND_STRING("build"SS_TAP(X_ENTER));
      leader_succeed = true;
    }
    SEQ_TWO_KEYS(KC_B, KC_F) {
      SEND_STRING("flash"SS_TAP(X_ENTER));
      reset_keyboard();
      leader_succeed = true;
    }
    SEQ_TWO_KEYS(KC_L, KC_G) {
      layer_on(_GAME);
      leader_layer_on = true;
    }
    SEQ_TWO_KEYS(KC_L, KC_D) {
      layer_off(_GAME);
      leader_layer_off = true;
    }
    leader_end();
  }
}

void leader_end(void) {
  if (leader_succeed) {
    // do nothing
  } else if (leader_layer_on) {
    #ifdef AUDIO_ENABLE
      PLAY_SONG(onsong);
    #endif
  } else if (leader_layer_off) {
    #ifdef AUDIO_ENABLE
      PLAY_SONG(offsong);
    #endif
  } else {
    #ifdef AUDIO_ENABLE
      PLAY_SONG(beep);
    #endif
  }
}

// layer declarations
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Default
   * ,-----------------------------------------------------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   Å  | BkSp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ø  |   Æ  |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   P  |   ,  |   .  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | Lead | Win  | Alt  | Lower| Space| Enter| Raise| AltGr| App  | Lead | Ctrl |
   * `-----------------------------------------------------------------------------------'
   */
  [_DEFAULT] = LAYOUT_planck_grid(
    KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,       KC_T,   KC_Y,   KC_U,       KC_I,    KC_O,    NO_AA,   KC_BSPC,
    KC_ESC,        KC_A,    KC_S,    KC_D,    KC_F,       KC_G,   KC_H,   KC_J,       KC_K,    KC_L,    NO_OE,   NO_AE,
    KC_LSPO,       KC_Z,    KC_X,    KC_C,    KC_V,       KC_B,   KC_N,   KC_M,       KC_P,    KC_COMM, KC_DOT,  KC_RSPC,
    OSM(MOD_LCTL), KC_LEAD, KC_LGUI, KC_LALT, MO(_LOWER), KC_SPC, KC_ENT, MO(_RAISE), KC_ALGR, KC_APP,  KC_LEAD, OSM(MOD_RCTL)
  ),
  /* Lower
   * ,-----------------------------------------------------------------------------------.
   * | Tab  | <Word| Up   | Word>| PgUp |      |      |      |  F7  |  F8  |  F9  |  Del |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | BkSp | Left | Down | Right| PgDn |      |      |      |  F4  |  F5  |  F6  |      |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Shift| Home |      | End  |      |      |      |      |  F1  |  F2  |  F3  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |      | Win  | Alt  | Lower| M_PP |M_Next|      |      | Mute | VolD | VolUp|
   * `-----------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT_planck_grid(
    KC_TRNS, LCTL(KC_LEFT), KC_UP,   LCTL(KC_RIGHT), KC_PGUP, KC_NO,   KC_NO,   KC_NO, KC_F7, KC_F8,   KC_F9, KC_DEL,
    KC_BSPC, KC_LEFT,       KC_DOWN, KC_RIGHT,       KC_PGDN, KC_NO,   KC_NO,   KC_NO, KC_F4, KC_F5,   KC_F6, KC_NO,
    KC_TRNS, KC_HOME,       KC_NO,   KC_END,         KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_F1, KC_F2,   KC_F3, KC_TRNS,
    KC_TRNS, KC_NO,         KC_TRNS, KC_TRNS,        KC_TRNS, KC_MPLY, KC_MNXT, KC_NO, KC_NO, KC_MUTE, KC_VOLD, KC_VOLU
  ),
  /* Raise
   * ,-----------------------------------------------------------------------------------.
   * | Tab  |   !  |   ?  |   *  |   '  |   "  |   ¨  |   /  |   7  |   8  |   9  | Ins  |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | BkSp |   @  |   &  |   $  |   #  |   %  |  <>  |   \  |   4  |   5  |   6  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   |  |   ~  |   {  |   }  |   [  |   ]  |   0  |   1  |   2  |   3  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |      | Win  | Alt  |      | Space| Enter| Raise| AltGr|   -  |   +  |   =  |
   * `-----------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT_planck_grid(
    KC_TRNS, NO_EXCL, NO_QEST, NO_ASTE, NO_APOS, NO_QUOT, NO_UMLA, NO_FSLS, KC_7,    KC_8,    KC_9,    KC_INS,
    KC_BSPC, NO_ALFA, NO_AMPE, NO_USDO, NO_HASH, NO_PERC, NO_ANBR, NO_BSLS, KC_4,    KC_5,    KC_6,    KC_NO,
    KC_TRNS, NO_PIPE, NO_TILD, NO_LBRA, NO_RBRA, NO_LBRC, NO_RBRC, KC_0,    KC_1,    KC_2,    KC_3,    KC_TRNS,
    KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, NO_DASH, NO_PLUS, NO_EQUA
  ),
  /* Game
   * ,-----------------------------------------------------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |      | BkSp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   P  |   ,  |   .  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | Lead |      | Alt  | Lower| Space| Enter| Lower|      |      | Lead |      |
   * `-----------------------------------------------------------------------------------'
   */
  [_GAME] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W, KC_E,    KC_R,      KC_T,   KC_Y,   KC_U,      KC_I, KC_O,    BEEP,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S, KC_D,    KC_F,      KC_G,   KC_H,   KC_J,      KC_K, KC_L,    BEEP,    BEEP,
    KC_LSFT, KC_Z,    KC_X, KC_C,    KC_V,      KC_B,   KC_N,   KC_M,      KC_P, KC_COMM, KC_DOT,  BEEP,
    KC_LCTL, KC_LEAD, BEEP, KC_LALT, MO(_GLOW), KC_SPC, KC_ENT, MO(_GLOW), BEEP, BEEP,    KC_LEAD, BEEP
  ),
  /* Game lower
   * ,-----------------------------------------------------------------------------------.
   * |  Tab |   1  |   2  |   3  |      |      |      |      |      |      |      | Steam|
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * |  Esc |   4  |   5  |   6  |      |      |      |      |      |      |      | F12  |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   7  |   8  |   9  |   0  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |      |      |  Alt |      | PlyPa| Next |      |      | Mute | VolD | VolUp|
   * `-----------------------------------------------------------------------------------'
   */
  [_GLOW] = LAYOUT_planck_grid(
    KC_TRNS, KC_1,    KC_2,    KC_3,    KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,   LSFT(KC_F7),
    KC_TRNS, KC_4,    KC_5,    KC_6,    KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_F12,
    KC_TRNS, KC_7,    KC_8,    KC_9,    KC_0,    KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_MUTE,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_MNXT, KC_NO, KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU
  )
};
