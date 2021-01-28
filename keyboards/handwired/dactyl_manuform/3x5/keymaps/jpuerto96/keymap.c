#include QMK_KEYBOARD_H


#define _BASE 0
#define _RAISE 1
#define _LOWER 2

// Fillers to make layering more clear

// Left-hand HR Mods
#define ALT_A ALT_T(KC_A)
#define GUI_S GUI_T(KC_S)
#define SFT_L SFT_T(KC_D)
#define CTL_F CTL_T(KC_F)

// Right-hand HR Mods
#define CTL_J  CTL_T(KC_J)
#define SFT_K  SFT_T(KC_K)
#define GUI_L  GUI_T(KC_L)
#define ALT_SC ALT_T(KC_SCLN)

#define ____ KC_TRNS

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base (qwerty)
 * ,----------------------------------,                             ,----------------------------------,
 * |   q  |   w  |   e  |   r  |   t  |                             |   y  |   u  |   i  |   o  |   p  |
 * |------+------+------+------+------|                             |-------------+------+------+------|
 * |   a  |   s  |   d  |   f  |   g  |                             |   h  |   j  |   k  |   l  |   ;  |
 * |------+------+------+------+------|                             |------|------+------+------+------|
 * |   z  |   x  |   c  |   v  |   b  |                             |   n  |   m  |   ,  |   .  |   /  |
 * |------+------+------+-------------,                             ,-------------+------+------+------,
 *             |TAB+CTL|LOWER |SPC+GUI|                             |ENT+SFT|RAISE |BSP+CTL|
 *               +------'-------------'                             '-------------'------+
 */

[_BASE] = LAYOUT( \
  KC_Q, KC_W, KC_E,    KC_R,    KC_T,                                       KC_Y, KC_U,    KC_I,    KC_O,   KC_P,    \
  ALT_A, GUI_S, SFT_L, CTL_F,    KC_G,                                      KC_H, CTL_J,   SFT_K,   GUI_L,  ALT_SC, \
  KC_Z, KC_X, KC_C,    KC_V,    KC_B,                                       KC_N, KC_M,    KC_COMM, KC_DOT, KC_SLSH, \
              KC_TAB, LOWER, KC_SPC,                                   KC_ENT, RAISE,   KC_BSPC \
),

/* Raise
 * ,----------------------------------,                             ,----------------------------------,
 * |  !   |  @   |  #   |  $   |  %   |                             | ^    |  &   | *    |  (   | )    |
 * |------+------+------+------+------|                             |-------------+------+------+------|
 * |  F1  | F2   | F3   | F4   |  F5  |                             | -    | =    | {    | }    |  '   |
 * |------+------+------+------+------|                             |------|------+------+------+------|
 * |  F6  |  F7  | F8   | F9   |  F10 |                             | _    |  +   |  [   |  ]   |  \   |
 * |------+------+------+-------------,                             ,-------------+------+------+------,
 *        |      |      |                                                         |      |      |
 *        '------+------'-------------'                             '-------------'------+------'
 */

[_RAISE] = LAYOUT( \
  KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,   \
  KC_F1,   KC_F2, KC_F3,   KC_F4,  KC_F5,                     KC_MINS, KC_EQL,  KC_LCBR, KC_RCBR, KC_QUOT, \
  KC_F6,   KC_F7, KC_F8,   KC_F9,  KC_F10,                    KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, \
                   ____,    ____,  ____,                      ____,    ____,    ____              \
),

/* Lower
 * ,----------------------------------,                             ,----------------------------------,
 * |  1   |  2   |  3   |  4   |  5   |                             |   6  |  7   |   8  |   9  |    0 |
 * |------+------+------+------+------|                             |-------------+------+------+------|
 * |  |   |  `   |  ~   |      |      |                             |      |  lt  |  dn  |  up  |  rt  |
 * |------+------+------+------+------|                             |------|------+------+------+------|
 * |      |      |      |      |      |                             |      |      |      |      |      |
 * |------+------+------+-------------,                             ,-------------+------+------+------,
 *        |      |      |                                                         |      |      |
 *        '------+------'-------------'                             '-------------'------+------'
 */

[_LOWER] = LAYOUT( \
  KC_1,    KC_2,   KC_3,    KC_4,   KC_5,                     KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    \
  KC_PIPE, KC_GRV, KC_TILD, ____,   ____,                     ____,    KC_LEFT,    KC_DOWN,   KC_UP,   KC_RGHT, \
  ____,    ____,   ____,    ____,   ____,                     ____,    ____,     ____,    ____,    ____, \
           ____,   ____,    ____,                             ____,    ____,     ____        \
)
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}
