#include "ergo42.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define BASE 0
#define META 1
#define SYMB 2

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE
 * ,------------------------------------------------.   ,------------------------------------------------.
 * |   `  |   Q  |   W  |   E  |   R  |   T  |  Y   |   |  T   |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------+------|   |-------------+------+------+------+------+------|
 * | Tab/ |   A  |   S  |   D  |   F  |   G  |  [   |   |  ]   |   H  |   J  |   K  |   L  |   ;  |  '   |
 * | Ctrl |      |      |      |      |      |      |   |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
 * | Sft  |   Z  |   X  |   C  |   V  |   B  |  N   |   |  B   |   N  |   M  |   ,  |   .  |   /  |  \   |
 * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
 * |PrtSc | App  | GUI  |XXXXXX|Lang2/|Space |ESC/  |   |BS/   |Enter |Lang1/| Left | Down |  Up  |Right |
 * |      |      |      |      |Alt   |      |~SYMB |   |~META |      |Sft   |      |      |      |      |
 * `------------------------------------------------'   `------------------------------------------------'
 */

[BASE] = KEYMAP( \
  KC_JYEN,        KC_Q,   KC_W,    KC_E,    KC_R,             KC_T,   KC_Y,             /**/ KC_T,              KC_Y,   KC_U,             KC_I,    KC_O,    KC_P,    KC_MINS, \
  LCTL_T(KC_TAB), KC_A,   KC_S,    KC_D,    KC_F,             KC_G,   KC_LBRC,          /**/ KC_RBRC,           KC_H,   KC_J,             KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,        KC_Z,   KC_X,    KC_C,    KC_V,             KC_B,   KC_N,             /**/ KC_B,              KC_N,   KC_M,             KC_COMM, KC_DOT,  KC_SLSH, KC_BSLASH, \
  KC_PSCR,        KC_APP, KC_LGUI, XXXXXXX, LALT_T(KC_LANG2), KC_SPC, LT(SYMB, KC_ESC), /**/ LT(META, KC_BSPC), KC_ENT, LSFT_T(KC_LANG1), KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT \
),

/* META
 * ,------------------------------------------------.   ,------------------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |   6  |      |   |      |   7  |   8  |   9  |   0  |   -  |  ^   |
 * |------+------+------+------+------+------+------|   |-------------+------+------+------+------+------|
 * |      |  F1  |XXXXXX|Muhen | Henk |XXXXXX|      |   |      | Left | Down |  Up  |Right |XXXXXX|XXXXXX|
 * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
 * |      |  F2  |  F3  |  F4  |  F5  |  F6  |      |   |      |  F7  |  F8  |  F9  | F10  | F11  |\/Sft |
 * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   |      |      |      |Reset |      |      |      |
 * |      |      |      |      |      |      |      |   |      |      |      |      |      |      |      |
 * `------------------------------------------------'   `------------------------------------------------'
 */

[META] = KEYMAP( \
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    _______, _______, KC_7,    KC_8,    KC_9,  KC_0,    KC_MINS, KC_EQL, \
  _______, KC_F1,   XXXXXXX, KC_MHEN, KC_HENK, XXXXXXX, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, XXXXXXX, XXXXXXX, \
  _______, KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, KC_F7,   KC_F8,   KC_F9, KC_F10,  KC_F11,  SFT_T(KC_RO), \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET, _______, _______, _______ \
),

/* SYMB
 * ,------------------------------------------------.   ,------------------------------------------------.
 * |   !  |   "  |   #  |   $  |   %  |   &  |      |   |      |   '  |   (  |   )  |   ~  |   =  |  ~   |
 * |------+------+------+------+------+------+------|   |-------------+------+------+------+------+------|
 * |      |XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|   |      |XXXXXX|XXXXXX|XXXXXX|XXXXXX|   +  |  *   |
 * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
 * |      |XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|   |      |XXXXXX|XXXXXX|   <  |   >  |   ?  |  \   |
 * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   |      |      |      |      |      |      |      |
 * |      |      |      |      |      |      |      |   |      |      |      |      |      |      |      |
 * `------------------------------------------------'   `------------------------------------------------'
 */

[SYMB] = KEYMAP( \
  S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), _______, _______, S(KC_7), S(KC_8), S(KC_9),    S(KC_0),   S(KC_MINS), S(KC_EQL), \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,   S(KC_SCLN), S(KC_QUOT), \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, S(KC_COMM), S(KC_DOT), S(KC_SLSH), S(KC_RO), \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,   _______,    _______ \
),

};
