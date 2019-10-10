#include QMK_KEYBOARD_H
#include "tominabox1.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    *  |GESC| Q  | W  | F  | P  | G  | J  | L  | U  | Y  | ;  | BSPC |
    *  | TAB | A  | R  | S  | T  | D  | H  | N  | E  | I  | O  | '   |
    *  |SHIFT | Z  | X  | C  | V  | B  | K  | M  | ,  | UP  | . | /  |
    *  |CTRL | WIN   | ALT |   ENTR   |  SPACE | LFT  |DOWN|RGHT|FKEY|
    */

    [_BASE] = LAYOUT_arrow(
      KC_GESC, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,    KC_BSPC,
      LCTL_T(KC_TAB),  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_UP, KC_DOT,   LT(_FKEY, KC_SLSH),
      KC_LCTL, KC_LGUI, KC_LALT, KC_ENT_LOW, KC_SPC_RSE,  KC_LEFT, KC_DOWN, KC_RIGHT, MO(_FKEY)
    ),

    /*
    *  | ~  | !  | @  | #  | $  | %  | ^  | &  | *  | (  | )  | DEL  |
    *  |     |    |    |    |    |    |    |  _ |  + |  { |  } | PIPE|
    *  |SHIFT |    |    |    |    |    |    |    |PGDN| UP  | ? | /  |
    *  |CTRL | WIN   | ALT |   ENTR   |  SPACE | LFT  |DOWN|RGHT|FKEY|
    */

    [_LOWER] = LAYOUT_arrow(
      KC_TILD, KC_EXLM, TD(KC_EML),   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
      KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
      KC_CAPS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_PGDN, KC_UP, KC_QUES, KC_SLSH,
      LCA(KC_DEL),   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END
    ),

    /*
    *  | `  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 0  | BSPC |
    *  | INS |    |    |    |    |    |    |  - |  = |  [ |  ] |  \  |
    *  |      |    |    |    |    |    |    |    |    |    |  / |    |
    *  |CTRL | WIN   | ALT |   ENTR   |  SPACE | LFT  |DOWN|RGHT|FKEY|
    */

    [_RAISE] = LAYOUT_arrow(
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
      KC_INS,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_SLSH, KC_NO,
      KC_LCTL, KC_LGUI, KC_LALT, SPC_LOW,  SPC_UPR,  KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /*
     *  |REST|EERS|    |    |    |    |    |    |    |    |    |      |
     *  |     |    |    |    |    |    |    |    |    |    |    |     |
     *  |      |    |    |    |    |    |    |    |    |    |    |    |
     *  |     |       |     |   ENTR   |  SPACE |      |    |    |    |
     */

    [_ADJUST] = LAYOUT_arrow(
      RESET,EEP_RST,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_TRNS,   KC_TRNS,   KC_NO,   KC_NO, KC_NO,   KC_NO
    ),

    /*
     *  |    | F1 | F2 | F3 | F4 | F5 | F6 | F7 | F8 | F9 | F10|      |
     *  |     |    |    |    |    |    |    |    |    |F11 | F12|     |
     *  |      |    |    |    |    |    |    |    |    |    |    |    |
     *  |     |       |     |          |        | FKEY |    |    |    |
     */

    [_FKEY] = LAYOUT_arrow(
      KC_NO, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_NO,
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_F11,   KC_F12,   KC_NO,
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_TRNS,   KC_NO, KC_NO,   KC_TRNS
    ),
  };
