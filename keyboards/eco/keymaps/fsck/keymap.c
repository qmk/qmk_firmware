// Below layout is based upon That-Canadian's ECO layout and fsck's planck layout

#include "eco.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _RAISE 3

#define _FUNCTION 15
#define _ADJUST 16

enum eco_keycodes {
  QWERTY = SAFE_RANGE,
  RAISE
};

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))
#define JC_Z    CTL_T(KC_Z)
#define JC_X    ALT_T(KC_X)
#define JC_C    GUI_T(KC_C)
#define JC_COMM GUI_T(KC_COMM)
#define JC_DOT  ALT_T(KC_DOT)
#define JC_SLSH CTL_T(KC_SLSH)

#define JC_CAPS LT(_RAISE,KC_CAPS)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-------------------------------------------------------------------------------------------------.
 * | Tab  |   1  |   2  |   3  |   4  |   5  |   -  |  =   |   6  |   7  |   8  |   9  |  10  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  | Home | PgUp |   Y  |   U  |   I  |   O  |   P  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Raise|   A  |   S  |   D  |   F  |   G  | End  | PgDn |   H  |   J  |   K  |   L  |   ;  | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |    Space    |   N  |   M  |   ,  |   .  |   /  | Shift|
 * |      | Ctrl | Alt  | GUI  |             |             |             | GUI  | Alt  | Ctrl |      |
 * `-------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_TAB,   KC_1,   KC_2,    KC_3,   KC_4,    KC_5,  KC_MINS, KC_EQL,  KC_6,   KC_7,   KC_8,     KC_9,     KC_0,    KC_BSPC},
  {KC_GESC,  KC_Q,   KC_W,    KC_E,   KC_R,    KC_T,  KC_HOME, KC_PGUP, KC_Y,   KC_U,   KC_I,     KC_O,     KC_P,    KC_QUOT}, 
  {JC_CAPS,  KC_A,   KC_S,    KC_D,   KC_F,    KC_G,  KC_END,  KC_PGDN, KC_H,   KC_J,   KC_K,     KC_L,     KC_SCLN, KC_ENT},
  {KC_LSFT,  JC_Z,   JC_X,    JC_C,   KC_V,    KC_B,  KC_SPC,  KC_SPC,  KC_N,   KC_M,   JC_COMM,  JC_DOT,   JC_SLSH, KC_RSFT}
},


/* Raise
 * ,-------------------------------------------------------------------------------------------------.
 * |  `   |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |  F6  |  F7  |  F8  |  F9  |  F0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |      |  Up  |      |      |      |      |PrntSc|      |      |      |   [  |   ]  |   \  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Left | Down | Right|      |      |ScrLck|Pause |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |      |      |             |      |      |      |Insert|
 * `-------------------------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL},
  {_______, _______, KC_UP,   _______, _______, _______, _______, KC_PSCR, _______, _______, _______, KC_LBRC, KC_RBRC, KC_BSLS},
  {_______, KC_LEFT, KC_DOWN, KC_RIGHT,_______, _______, KC_SLCK, KC_PAUS, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS}
}
};
