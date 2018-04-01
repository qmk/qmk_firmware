#include "adohox.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _DVORAK 3
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  DVORAK,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *
 * ,----------------------------------.                        ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |                        |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|                        |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |                        |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------|                        |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |                        |   N  |   M  |   ,  |   .  |   /  |
 * `----------------------------------'                        `----------------------------------'
 *              ,-----------------------------.       ,---------------------------.
 *              | Windows| LOWER|      |     |       |      |      | RAISE| Tab |
 *              `--------------| Space|Enter|       |BckSpc|Shift |------+------.
 *                            |      |     |       |      |      |
 *                            `------------'       `------------'
 */
[_QWERTY] = KEYMAP( \
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, \
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,              KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, \
          LT(KC_LCTRL, KC_LGUI), MO(LOWER), KC_SPC, KC_ENT,                     KC_BSPC, KC_LSHIFT, MO(RAISE), LT(KC_LALT, KC_TAB)               \
),

/* Raise
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |           |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Tab | Left | Down |  Up  | Right|           |   -  |   (  |   )  |   [  |   ]  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Ctrl|   `  |  GUI |  Alt |DVORAK TOGGLE|    |   =  |   {  |   }  |   \  |   '  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_RAISE] = KEYMAP( \
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    \
  KC_TAB,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,      KC_MINS, KC_LPRN, KC_RPRN,  KC_LBRC, KC_RBRC, \
  KC_LCTL, KC_GRV,  KC_LGUI, KC_LALT, TG(DVORAK),      KC_EQL, KC_LCBR, KC_RCBR, KC_BSLS,  KC_QUOT, \
          _______,  _______, _______, _______,      _______, _______, _______, _______            \
),

/* Lower
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |           |   ^  |   &  |   *  |   (  |   )  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Esc |      |      |      |      |           |      |   _  |   +  |   {  |   }  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Caps|   ~  |      |      |      |           |      |      |      |   |  |   "  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|  Del |
 *                  `-------------|      |    | Enter|------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_LOWER] = KEYMAP( \
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, _______, _______, \
  KC_ESC,  _______, _______, _______, _______,      _______, KC_UNDS, KC_PLUS, _______, _______, \
  KC_CAPS, KC_TILD, _______, _______, _______,      _______, _______, _______, KC_PIPE,  KC_DQT, \
          _______, _______, _______, _______,      KC_ENT,  _______, KC_DEL, _______              \
),

/* Modded Dvorak
 *
 * ,----------------------------------.                  ,----------------------------------.
 * |   ;  |   P  |   Y  |   F  |   G  |                 |   C  |   R  |   L  |   V  |   Z  |
 * |------+------+------+------+------|                 |------+------+------+------+------|
 * |   A  |   E  |   O  |   U  |   I  |                 |   D  |   H  |   T  |   N  |   S  |
 * |------+------+------+------+------|                 |------+------+------+------+------|
 * |   Q  |   J  |   K  |   X  |   B  |                 |   M  |   W  |   ,  |   .  |   /  |
 * `----------------------------------'                  `----------------------------------'
 *              ,-----------------------------.       ,---------------------------.
 *              | Windows| LOWER|      |     |       |      |      | RAISE| Tab |
 *              `--------------| Space|Enter|       |BckSpc|Shift |------+------.
 *                            |      |     |       |      |      |
 *                            `------------'       `------------'
 */
[_DVORAK] = KEYMAP( \
  KC_SCLN,    KC_P,    KC_Y,    KC_F,    KC_G,              KC_C,    KC_R,    KC_L,    KC_V,    KC_Z,    \
  KC_A,    KC_E,    KC_O,    KC_U,    KC_I,              KC_D,    KC_H,    KC_T,    KC_N,    KC_S, \
  KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,              KC_M,    KC_W,    KC_COMM, KC_DOT,  KC_SLSH, \
          LT(KC_LCTRL, KC_LGUI), MO(LOWER), KC_SPC, KC_ENT,                     KC_BSPC, KC_LSHIFT, MO(RAISE), LT(KC_LALT, KC_TAB)               \
),

/* Adjust (Lower + Raise)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |           |   F6 |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  F11 |  F12 |      |RGBSAI|RGBSAD|           |RGBVAD|      | Down |      |caltde|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Reset|RGBTOG|RGBMOD|RGBHUI|RGBHUD|           |RGBVAI| Left | Down |Right |Taskmg|
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_ADJUST] =  KEYMAP( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, \
  KC_F11,  KC_F12,  _______, RGB_SAI, RGB_SAD,      RGB_VAD, _______, KC_UP, _______, CALTDEL, \
  RESET,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD,      RGB_VAI, KC_LEFT, KC_DOWN, KC_RGHT,  TSKMGR, \
          _______,  _______, _______, _______,      _______,  _______, _______, _______        \
)
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_QWERTY);
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
    case DVORAK:
      if (record->event.pressed) {
        layer_on(_DVORAK);
//        update_quad_layer(_LOWER, _RAISE, _DVORAK, _ADJUST);
      }
      else
      {
        layer_off(_DVORAK);
//        update_quad_layer(_LOWER, _RAISE, _DVORAK, _ADJUST);
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
