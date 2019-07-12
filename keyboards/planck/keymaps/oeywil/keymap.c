#include QMK_KEYBOARD_H
#include "secret.h"

enum planck_layers {
  _DEFAULT,
  _LOWER,
  _RAISE,
  _FUNCTION,
  _GAME,
  _GAMERAISE
};

#define LOWER    MO(_LOWER)
#define RAISE    MO(_RAISE)
#define FUNCTION MO(_FUNCTION)
#define GAMER    MO(_GAMERAISE)

#define NO_OE   KC_SCLN
#define NO_AE   KC_QUOT
#define NO_AA   KC_LBRC
#define NO_EXCL LSFT(KC_1)
#define NO_QEST LSFT(KC_MINS)
#define NO_APOS KC_BSLS
#define NO_QUOT LSFT(KC_2)
#define NO_UMLA KC_RBRC
#define NO_HASH LSFT(KC_3)
#define NO_FSLS LSFT(KC_7)
#define NO_LPAR LSFT(KC_8)
#define NO_RPAR LSFT(KC_9)
#define NO_ALFA ALGR(KC_2)
#define NO_AMPE LSFT(KC_6)
#define NO_USDO ALGR(KC_4)
#define NO_PERC LSFT(KC_5)
#define NO_BSLS KC_EQL
#define NO_ASTE LSFT(KC_BSLS)
#define NO_LBRA ALGR(KC_7)
#define NO_RBRA ALGR(KC_0)
#define NO_LBRC ALGR(KC_8)
#define NO_RBRC ALGR(KC_9)
#define NO_ANBR KC_NUBS
#define NO_DASH KC_SLSH
#define NO_PLUS KC_MINS
#define NO_EQUA LSFT(KC_0)

#define TSKMGR LCTL(LSFT(KC_ESC))
#define STEAM  LSFT(KC_F7)
#define WKILL  LALT(KC_F4)
#define BWORD  LCTL(KC_LEFT)
#define FWORD  LCTL(KC_RIGHT)

float onsong[][2] = SONG(MARIO_MUSHROOM);
float offsong[][2] = SONG(PLOVER_GOODBYE_SOUND);

enum custom_keycodes {
  PWD = SAFE_RANGE,
  MAIL,
  GAMEON,
  GAMEOFF
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case PWD:
      if (record->event.pressed) {
        SEND_STRING(pwd_str);
      }
      break;
    case MAIL:
      if (record->event.pressed) {
        SEND_STRING(mail_str);
      }
      break;
    case GAMEON:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(onsong);
        #endif
        layer_on(_GAME);
      }
      break;
    case GAMEOFF:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(offsong);
        #endif
        layer_off(_GAME);
      }
      break;
  }
  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Default
   * ,-----------------------------------------------------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | BkSp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ø  |   Æ  |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   Å  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | Win  | Alt  | Lower|    Space    |    Enter    | Raise| AltGr| Game | Fn   |
   * `-----------------------------------------------------------------------------------'
   */
  [_DEFAULT] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,  KC_T,   KC_Y,  KC_U,   KC_I,    KC_O,    KC_P,   KC_BSPC,
    KC_GESC, KC_A,    KC_S,    KC_D,  KC_F,  KC_G,   KC_H,  KC_J,   KC_K,    KC_L,    NO_OE,  NO_AE,
    KC_LSFT, KC_Z,    KC_X,    KC_C,  KC_V,  KC_B,   KC_N,  KC_M,   KC_COMM, KC_DOT,  NO_AA,  KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT, LOWER, KC_NO, KC_SPC, KC_NO, KC_ENT, RAISE,   KC_RALT, GAMEON, FUNCTION
  ),
  /* Lower
   * ,-----------------------------------------------------------------------------------.
   * | Tab  | <Word| Up   | Word>| PgUp |      |      |      |  F7  |  F8  |  F9  |  Del |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | BkSp | Left | Down | Right| PgDn |      |      |      |  F4  |  F5  |  F6  |      |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Shift| Home |      | End  |      |      |      |      |  F1  |  F2  |  F3  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | Win  | Alt  | Lower|    Space    |    Enter    |      |      |      |      |
   * `-----------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT_planck_grid(
    KC_TRNS, BWORD,   KC_UP,   FWORD,    KC_PGUP, KC_NO,   KC_NO, KC_NO,   KC_F7, KC_F8, KC_F9, KC_DEL,
    KC_BSPC, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, KC_NO,   KC_NO, KC_NO,   KC_F4, KC_F5, KC_F6, KC_NO,
    KC_TRNS, KC_HOME, KC_NO,   KC_END,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_F1, KC_F2, KC_F3, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_NO,   KC_TRNS, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO
  ),
  /* Raise
   * ,-----------------------------------------------------------------------------------.
   * | Tab  |   !  |   ?  |   '  |   "  |   ¨  |      |   /  |   7  |   8  |   9  | Ins  |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | BkSp |   @  |   &  |   #  |   $  |   %  |  <>  |   \  |   4  |   5  |   6  |   *  |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   (  |   )  |   {  |   }  |   [  |   ]  |   0  |   1  |   2  |   3  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | Win  | Alt  |      |    Space    |    Enter    | Raise|   -  |   +  |   =  |
   * `-----------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT_planck_grid(
    KC_TRNS, NO_EXCL, NO_QEST, NO_APOS, NO_QUOT, NO_UMLA, KC_NO,   NO_FSLS, KC_7,    KC_8,    KC_9,    KC_INS,
    KC_BSPC, NO_ALFA, NO_AMPE, NO_HASH, NO_USDO, NO_PERC, NO_ANBR, NO_BSLS, KC_4,    KC_5,    KC_6,    NO_ASTE,
    KC_TRNS, NO_LPAR, NO_RPAR, NO_LBRA, NO_RBRA, NO_LBRC, NO_RBRC, KC_0,    KC_1,    KC_2,    KC_3,    KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_NO,   KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, NO_DASH, NO_PLUS, NO_EQUA
  ),
  /* Function
   * ,-----------------------------------------------------------------------------------.
   * |      |      |      |      |      |TskMgr|      |      |      |      | Pwd  | Vol+ |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Reset|      |      |      |      |      |      |      | Wkill|      |      | Vol- |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      | Mail |      |      |      | VolM |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |  Play/Pause |     Next    |      |      |      |      |
   * `-----------------------------------------------------------------------------------'
   */
  [_FUNCTION] = LAYOUT_planck_grid(
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TSKMGR,  KC_NO, KC_NO,   KC_NO, KC_NO, PWD,   KC_VOLU,
    RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO,   WKILL, KC_NO, KC_NO, KC_VOLD,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, MAIL,    KC_NO, KC_NO, KC_NO, KC_MUTE,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MPLY, KC_NO, KC_MNXT, KC_NO, KC_NO, KC_NO, KC_NO
  ),
  /* Game
   * ,-----------------------------------------------------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | BkSp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |      | Alt  | Raise|    Space    |    Enter    |      |      |      |      |
   * `-----------------------------------------------------------------------------------'
   */
  [_GAME] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,  KC_W,    KC_E,  KC_R,  KC_T,   KC_Y,  KC_U,   KC_I,  KC_O,  KC_P,  KC_BSPC,
    KC_ESC,  KC_A,  KC_S,    KC_D,  KC_F,  KC_G,   KC_H,  KC_J,   KC_K,  KC_L,  KC_NO, KC_NO,
    KC_LSFT, KC_Z,  KC_X,    KC_C,  KC_V,  KC_B,   KC_N,  KC_M,   KC_NO, KC_NO, KC_NO, KC_NO,
    KC_LCTL, KC_NO, KC_LALT, GAMER, KC_NO, KC_SPC, KC_NO, KC_ENT, KC_NO, KC_NO, KC_NO, KC_NO
  ),
  /* Game raise
   * ,-----------------------------------------------------------------------------------.
   * |  Tab |  1   |  2   |  3   |   4  |   5  |      |      |      |      |      | Vol+ |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * |  Esc |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |      |      |      | Vol- |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|      |      |      |      |      |      |      |      |      |      | VolM |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |      |  Alt |      |    Space    |    Enter    |      |      | Def  | Steam|
   * `-----------------------------------------------------------------------------------'
   */
  [_GAMERAISE] = LAYOUT_planck_grid(
    KC_TRNS, KC_1,  KC_2,    KC_3,    KC_4,  KC_5,    KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,   KC_VOLU,
    KC_TRNS, KC_F1, KC_F2,   KC_F3,   KC_F4, KC_F5,   KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,   KC_VOLD,
    KC_TRNS, KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,   KC_MUTE,
    KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_NO, KC_NO, GAMEOFF, STEAM
  )
};
