#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _DVORAK 1
#define _GAME 2

#define _LOWER 3
#define _RAISE 4
#define _FN 5
#define _ADJUST 16
#define _DVORAK 1

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  DVORAK,
  GAME,
  ADJUST,
  FN
};

#define LEADER_TIMEOUT 400

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define GAME MO(_GAME)
#define FN MO(_FN)

#define RSPA  LT(_FN, KC_SPC)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Func |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   "  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Lead | GUI  | Alt  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT( \
    KC_GESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,\
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT ,\
    KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,\
    KC_LCTL, KC_LEAD, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),
  // I'd like to flip the esc enter and shift keys somedayi
/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   /  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Lead | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT( \
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
    KC_GESC, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_ENT ,
    KC_LSPO, KC_SLSH, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSPC,
    KC_LEAD, KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  RSPA,    RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   |  |   :  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |   {  |   }  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |Lower | Bksp | Bksp |Raise | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_PIPE, KC_COLON, _______,
  KC_DEL,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC,  _______,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TILD, _______, KC_LCBR, KC_RCBR,  _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   4  |   5  |   6  |   +  |      |      |   -  |   =  |   \  |   ;  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Enter |   7  |   8  |   9  |   -  |      |      |      |      |   [  |   ]  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   ,  |   0  |  .   |Lower | Bksp | Bksp |Raise | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______, _______, KC_MINS,  KC_EQL , KC_BSLS, KC_SCLN, _______,
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    _______,
  _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, KC_GRAVE, _______, KC_LBRC, KC_RBRC, _______,
  _______, _______, _______, _______, _______, _______, _______, _______,  _______, KC_RALT, KC_RGUI,  KC_RCTL
),

[_FN] = LAYOUT(
  _______, _______, _______, _______, _______, _______, _______, KC_TILD, KC_SLSH, KC_BSLS,  _______, _______,
  _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_SCLN, _______,
  _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______, KC_LBRC,  KC_LBRC, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RALT,  KC_RGUI,  KC_RCTL
),

[_GAME] = LAYOUT(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_1,    KC_2,   KC_3,     KC_4,     KC_5,    KC_ESC,
  KC_1,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,   KC_K,     KC_L,     KC_QUOT, KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,   KC_COMM,  KC_DOT,   KC_SLSH, KC_RSPC,
  KC_LCTL, KC_LGUI, KC_LALT, KC_3,    LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN,  KC_UP,   KC_RGHT
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |Taskmg|Qwerty|      |      |      |      |      |      |RGBVAI|RGBSAI|RGBHUI|caltde|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Dvorak|      |      |      |      |      |RGBVAD|RGBSAD|RGBHUD|RGBTOG|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |BLSTEP|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | RESET|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT( \
  TSKMGR,  QWERTY , _______, _______, _______, _______,  _______,  _______, RGB_VAI, RGB_SAI, RGB_HUI, CALTDEL, \
  _______, _______, _______, DVORAK , _______, GAME,     _______,  _______, RGB_VAD, RGB_SAD, RGB_HUD, RGB_TOG, \
  _______, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_G, RGB_M_SW, RGB_M_SN, RGB_M_K, _______, _______, _______, BL_STEP, \
  _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______, RESET    \
),

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case GAME:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_GAME);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();
    SEQ_ONE_KEY(KC_SCLN) {
      SEND_STRING(SS_LCTRL("Z"));
      }
    SEQ_ONE_KEY(KC_Q) {
      SEND_STRING(SS_LCTRL("x"));
      }
    SEQ_ONE_KEY(KC_J) {
      SEND_STRING(SS_LCTRL("c"));
      }
    SEQ_ONE_KEY(KC_K) {
      SEND_STRING(SS_LCTRL("v"));
      }
    SEQ_ONE_KEY(KC_A) {
      SEND_STRING(SS_LCTRL("a"));
      }
    SEQ_ONE_KEY(KC_P) {
      SEND_STRING(SS_LGUI(SS_LALT(SS_TAP(X_PSCREEN))));
      }
    SEQ_ONE_KEY(KC_L) {
      SEND_STRING(SS_LGUI(SS_LALT(SS_TAP(X_PSCREEN))));
      }
    SEQ_ONE_KEY(KC_S) {
      SEND_STRING(SS_RALT("sf"));
      }
    }
}
