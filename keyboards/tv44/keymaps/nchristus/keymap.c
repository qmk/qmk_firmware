//Author: tong92 <tong92power@gmail.com>

#include "tv44.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef BACKLIGHT_ENABLE
  #include "backlight.h"
#endif

// Fillers to make layering more clear
#define _______ KC_TRNS
#define LOWER F(1)
#define RAISE F(2)
#define CTRLESC CTL_T(KC_ESC)
#define SHIFTUP SFT_T(KC_UP)
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,--------------------------------------------------------------------------.
 * | Tab  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  Bksp |
 * |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
 * | Ctrl  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '   |
 * |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
 * | Shift  |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  | Up  |  /  |
 * |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
 * | Alt  | RAISE | GUI | Space/RAISE | Space/LOWER | LOWER | Left| DOWN|RIGHT|
 * `--------------------------------------------------------------------------'
 */
[0] = KEYMAP_ARROW(
KC_TAB,  KC_Q,  KC_W,    KC_E, KC_R, KC_T,  KC_Y,  KC_U, KC_I,    KC_O,    KC_P,    KC_BSPC,
CTRLESC, KC_A,  KC_S,    KC_D, KC_F, KC_G,  KC_H,  KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT,
KC_LSFT, KC_Z,  KC_X,    KC_C, KC_V, KC_B,  KC_N,  KC_M, KC_COMM, KC_DOT,  SHIFTUP, KC_SLSH,
KC_LALT, MO(2), KC_LGUI,             RAISE, LOWER,       MO(1),   KC_LEFT, KC_DOWN, KC_RIGHT
),
/* LOWER
 * ,--------------------------------------------------------------------------.
 * |  `   |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |       |
 * |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
 * |       |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  -  |  +  |  [  |  ]  |   \  |
 * |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
 * |        |  F7 |  F8 |  F9 | F10 | F11 | F12 |     |     |     |  /  |     |
 * |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
 * |      |       |      |             |             |      |     |     |    |
 * `--------------------------------------------------------------------------'
 */
[1] = KEYMAP_ARROW(
KC_GRV,  KC_1,    KC_2,    KC_3,  KC_4,   KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
_______, KC_F1,   KC_F2,   KC_F3, KC_F4,  KC_F5,   KC_F6,   KC_MINS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS,
_______, KC_F7,   KC_F8,   KC_F9, KC_F10, KC_F11,  KC_F12,  _______, _______, _______, _______, _______,
_______, _______, _______,                XXXXXXX, _______,          _______, _______, _______, _______
),
/* RAISE
 * ,--------------------------------------------------------------------------.
 * |  ~   |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  |       |
 * |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
 * |       |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  _  |  =  |  {  |  }  |   |  |
 * |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
 * |        |  F7 |  F8 |  F9 | F10 | F11 | F12 |     |     |     |     |     |
 * |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
 * |      |       |      |             |             |      |     |     |    |
 * `--------------------------------------------------------------------------'
 */
[2] = KEYMAP_ARROW(
KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,   KC_F6,   KC_UNDS, KC_EQL,  KC_LCBR, KC_RCBR, KC_PIPE,
_______, KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11,  KC_F12,  _______, _______, _______, _______, _______,
_______, _______, _______,                  _______, XXXXXXX,          _______, _______, _______, _______
)
};

const uint16_t PROGMEM fn_actions[] = {
 [1] = ACTION_LAYER_TAP_KEY(1, KC_SPC),
 [2] = ACTION_LAYER_TAP_KEY(2, KC_ENT)
};
