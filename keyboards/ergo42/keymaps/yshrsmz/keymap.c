#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _BASE 0
#define _META 1
#define _SYMB 2
#define _GAME 3


enum custom_keycodes {
  BASE = SAFE_RANGE,
  META,
  SYMB,
  GAME,
  EISU,
  KANA
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE
 * ,------------------------------------------------.   ,------------------------------------------------.
 * |  =   |   Q  |   W  |   E  |   R  |   T  |  [   |   |  ]   |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------+------|   |-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |  (   |   |  )   |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
 * | Sft  |   Z  |   X  |   C  |   V  |   B  |  {   |   |  }   |   N  |   M  |   ,  |   .  |   /  |\/Sft |
 * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
 * | EISU | Ctrl | Alt  | GUI  | ESC/ |Del   |Back  |   |Enter |Space | META | GUI  |=>GAME|=>SYMB| KANA |
 * |      |      |      |      | SYMB |      |Space |   |      |      |      |      |      |      |      |
 * `------------------------------------------------'   `------------------------------------------------'
 */

[_BASE] = LAYOUT( \
  KC_EQL,  KC_Q,     KC_W,    KC_E,    KC_R,             KC_T,     KC_LBRC,  KC_RBRC,    KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_MINS, \
  KC_TAB,  KC_A,     KC_S,    KC_D,    KC_F,             KC_G,     KC_LPRN,  KC_RPRN,    KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT, \
  KC_LSFT, KC_Z,     KC_X,    KC_C,    KC_V,             KC_B,     KC_LCBR,  KC_RCBR,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_BSLS, \
  EISU,    KC_LCTRL, KC_LALT, KC_LGUI, LT(_SYMB, KC_ESC),KC_DEL,   KC_BSPC,     KC_ENT,    KC_SPC,  META,    KC_LGUI,  TG(_GAME), TG(_SYMB), KANA \
),

/* META
 * ,------------------------------------------------.   ,------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |      |   |      |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------+------|   |-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   |      | Left | Down |  Up  |Right | PgUp |      |
 * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  | F10  | F11  | F12  |   |      | Home | End  |Alt+← |Alt+→ | PgDn |      |
 * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   |      |      |      |Reset |      |      |      |
 * |      |      |      |      |      |      |      |   |      |      |      |      |      |      |      |
 * `------------------------------------------------'   `------------------------------------------------'
 */

[_META] = LAYOUT( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PGUP, _______, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_HOME, KC_END,  LALT(KC_LEFT), LALT(KC_RGHT), KC_PGDN, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,   _______, _______, _______ \
),

/* SYMB
 * ,------------------------------------------------.   ,------------------------------------------------.
 * |  ~   |   !  |   @  |   #  |   $  |   %  |      |   |      |   ^  |  &   |   *  |   (  |   )  |   -  |
 * |------+------+------+------+------+------+------|   |-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   |      | Left | Down |  Up  |Right | PgUp |      |
 * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  | F10  | F11  | F12  |   |      | Home | End  |Alt+← |Alt+→ | PgDn |      |
 * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   |      |      |      |Reset |      |      |      |
 * |      |      |      |      |      |      |      |   |      |      |      |      |      |      |      |
 * `------------------------------------------------'   `------------------------------------------------'
 */

[_SYMB] = LAYOUT( \
  KC_TILD, S(KC_1),  S(KC_2), S(KC_3), S(KC_4), S(KC_5), _______, _______, S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), _______, \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PGUP, _______, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_HOME, KC_END,  LALT(KC_LEFT), LALT(KC_RGHT), KC_PGDN, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,   _______, _______, _______ \
),

/* GAME
 * ,------------------------------------------------.   ,------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |  [   |   |  ]   |   Y  |   U  |   I  |   O  |   P  |  @   |
 * |------+------+------+------+------+------+------|   |-------------+------+------+------+------+------|
 * | Alt  |   A  |   S  |   D  |   F  |   G  |  (   |   |  )   |   H  |   J  |   K  |   L  |   ;  |  :   |
 * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
 * | Sft  |   Z  |   X  |   C  |   V  |   B  |  {   |   |  }   |   N  |   M  |   ,  |   .  |   /  |\/Sft |
 * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
 * | Ctrl | GUI  |  App |PrtSc | ESC  |Space |Tab   |   |Back  |Enter | Del  |PrtSc |=>GAME|=>SYMB|  \   |
 * |      |      |      |      |      |      |      |   |Space |      |      |      |      |      |      |
 * `------------------------------------------------'   `------------------------------------------------'
 */
[_GAME] = LAYOUT( \
  KC_TAB,   KC_Q,    KC_W,   KC_E,    KC_R,   KC_T,   KC_RBRC,    KC_BSLS,    KC_Y,   KC_U,    KC_I,     KC_O,    KC_P,    KC_LBRC, \
  KC_LALT,  KC_A,    KC_S,   KC_D,    KC_F,   KC_G,   S(KC_8),    S(KC_9),    KC_H,   KC_J,    KC_K,     KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,    KC_X,   KC_C,    KC_V,   KC_B,   S(KC_RBRC), S(KC_BSLS), KC_N,   KC_M,    KC_COMM,  KC_DOT,  KC_SLSH, SFT_T(KC_RO), \
  KC_LCTRL, KC_LGUI, KC_APP, KC_PSCR, KC_ESC, KC_SPC, KC_TAB,     KC_BSPC,    KC_ENT, KC_DELT, KC_PSCR,  _______, _______, KC_JYEN \
)

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BASE:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_BASE);
      }
      return false;
      break;
    case META:
      if (record->event.pressed) {
        layer_on(_META);
        update_tri_layer(_META, _SYMB, _GAME);
      } else {
        layer_off(_META);
        update_tri_layer(_META, _SYMB, _GAME);
      }
      return false;
      break;
    case SYMB:
      if (record->event.pressed) {
        layer_on(_SYMB);
        update_tri_layer(_META, _SYMB, _GAME);
      } else {
        layer_off(_SYMB);
        update_tri_layer(_META, _SYMB, _GAME);
      }
      return false;
      break;
    case GAME:
      if (record->event.pressed) {
        layer_on(_GAME);
      } else {
        layer_off(_GAME);
      }
      return false;
      break;
    case EISU:
      if (record->event.pressed) {
        register_code(KC_LANG2);
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        register_code(KC_LANG1);
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
  }
  return true;
}
