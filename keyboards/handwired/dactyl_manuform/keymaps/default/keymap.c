#include "dactyl_manuform.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _BASE 0
#define _UPPER 1
#define _LOWER 2

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  NAV,
  NUM,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base (qwerty)
 * ,----------------------------------,                             ,----------------------------------,
 * |   Q  |   W  |   E  |   R  |   T  |                             |   Y  |   U  |   I  |   O  |   P  | 
 * |------+------+------+------+------|                             |-------------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |                             |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------|                             |------|------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |                             |   N  |   M  |   ,  |   .  |   '  |
 * |------+------+------+-------------,                             ,-------------+------+------+------,
 *        |  [   |   ]  |                                                         |   -  |   =  |
 *        '------+------'-------------'                             '-------------'------+------'
 *                      | esc  |  bs  |                             | space|enter |
 *                      |  +   |   +  |                             |  +   |  +   |
 *                      | shift| ctrl |                             | alt  |shift |
 *                      '------+------'                             '------+------'
 *                                    '------+------' '------+------'
 *                                    | TAB  | HOME | | END  | DEL  |
 *                                    '------+------' '------+------'
 *                                    | Lower|  ~   | | GUI  | Upper|
 *                                    '------+------' '------+------'
 */

[_BASE] = LAYOUT( \
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, \
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_QUOT, \
           KC_LBRC, KC_RBRC,                                                             KC_MINS, KC_EQL,                    \
                             SFT_T(KC_ESC),  CTL_T(KC_BSPC),  ALT_T(KC_SPC),  SFT_T(KC_ENT),                                 \
                                        KC_TAB,     KC_HOME, KC_END,  KC_DEL,                                                \
                                        MO(_UPPER), KC_GRV,  KC_LGUI, MO(_LOWER)                                             \
),
/* Upper
 * ,----------------------------------,                             ,----------------------------------,
 * |      |      |  mup |      |      |                             | VOL+ |      |  up  |      | PgUp |
 * |------+------+------+------+------|                             |-------------+------+------+------|
 * |      | mleft| mdown|mright|      |                             | MUTE | left | down |right | PgDn |
 * |------+------+------+------+------|                             |------|------+------+------+------|
 * |      |      |      |      |      |                             | VOL- |  /   |  \   |  ?   |  |   |
 * |------+------+------+-------------,                             ,-------------+------+------+------,
 *        |      |      |                                                         | mbtn |mbtn2 |
 *        '------+------'-------------'                             '-------------'------+------'
 *                      | ESC  |  BS  |                             | SPACE|ENTER |
 *                      |  +   |   +  |                             |  +   |  +   |
 *                      | SHIFT| CTRL |                             | ALT  |SHIFT |
 *                      '------+------'                             '------+------'
 *                                    '------+------' '------+------'
 *                                    | TAB  | HOME | | END  | DEL  |
 *                                    '------+------' '------+------'
 *                                    | Lower|  ~   | | GUI  | Upper|
 *                                    '------+------' '------+------'
 */

[_UPPER] = LAYOUT( \
  KC_TRNS,  KC_TRNS,    KC_MS_UP,   KC_TRNS,     KC_TRNS, KC_VOLU, KC_TRNS,  KC_UP,      KC_TRNS,    KC_PGUP,   \
  KC_TRNS,  KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_TRNS, KC_MUTE, KC_LEFT,  KC_DOWN,    KC_RIGHT,   KC_PGDOWN, \
  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS, KC_VOLD, KC_SLSH,  KC_BSLS,    KC_QUES,    KC_PIPE,   \
            KC_TRNS,    KC_TRNS,                                             KC_MS_BTN1, KC_MS_BTN2,            \
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                              \
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                              \
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS                                               \
),
/* Lower
 * ,----------------------------------,                             ,----------------------------------,
 * | F1   | F2   | F3   | F4   | F5   |                             |  F6  | F7   |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|                             |-------------+------+------+------|
 * |  1   |  2   |  3   |  4   |  5   |                             |  6   |  7   |  8   |  9   |  10  |
 * |------+------+------+------+------|                             |------|------+------+------+------|
 * |  !   |  @   |  #   |  $   |  %   |                             |  ^   |  &   |  *   |  (   |  )   |
 * |------+------+------+-------------,                             ,-------------+------+------+------,
 *        | F11  | F12  |                                                         |  -   |  =   |
 *        '------+------'-------------'                             '-------------'------+------'
 *                      | ESC  |  BS  |                             | SPACE|ENTER |
 *                      |  +   |   +  |                             |  +   |  +   |
 *                      | SHIFT| CTRL |                             | ALT  |SHIFT |
 *                      '------+------'                             '------+------'
 *                                    '------+------' '------+------'
 *                                    | TAB  | HOME | | END  | DEL  |
 *                                    '------+------' '------+------'
 *                                    | Lower|  ~   | | GUI  | Upper|
 *                                    '------+------' '------+------'
 */
[_LOWER] = LAYOUT( \
  KC_F1,   KC_F2,  KC_F3,   KC_F4,  KC_F5,   KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  \
  KC_1,    KC_2,   KC_3,    KC_4,   KC_5,    KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    \
  KC_EXLM, KC_AT,  KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR,  KC_ASTR, KC_LPRN, KC_RPRN, \
           KC_F11, KC_F12,                                      KC_TRNS, KC_TRNS,          \
                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            \
                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            \
                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS                             \
)
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

