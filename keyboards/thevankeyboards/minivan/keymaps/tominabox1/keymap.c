#include QMK_KEYBOARD_H
#include "tominabox1.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    *  |GESC| Q  | W  | F  | P  | G  | J  | L  | U  | Y  | ;  | BSPC |
    *  | TAB | A  | R  | S  | T  | D  | H  | N  | E  | I  | O  | '   |
    *  |SHIFT | Z  | X  | C  | V  | B  | K  | M  | ,  | UP  | . | /  |
    *  |CTRL | WIN   | ALT |   ENTR   |  SPACE | LFT  |DOWN|RGHT|FKEY|
    */

    [_BASE] = LAYOUT_arrow_wrapper(
      __________________MINIVAN1_________________,
      __________________MINIVAN2_________________,
      __________________MINIVAN3_________________,
      __________________MINIVAN4_________________
    ),

    /*
    *  | ~  | !  | @  | #  | $  | %  | ^  | &  | *  | (  | )  | DEL  |
    *  |     |    |    |    |    |    |    |  _ |  + |  { |  } | PIPE|
    *  |SHIFT |    |    |    |    |    |    |    |PGDN| UP  | ? | /  |
    *  |CTRL | WIN   | ALT |   ENTR   |  SPACE | LFT  |DOWN|RGHT|FKEY|
    */

    [_LOWER] = LAYOUT_arrow_wrapper(
      _________________LOWER_1___________________,
      _________________LOWER_2___________________,
      __________________MININUM3_________________,
      __________________MININUM4_________________
    ),

    /*
    *  | `  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 0  | BSPC |
    *  | INS |    |    |    |    |    |    |  - |  = |  [ |  ] |  \  |
    *  |      |    |    |    |    |    |    |    |    |    |  / |    |
    *  |CTRL | WIN   | ALT |   ENTR   |  SPACE | LFT  |DOWN|RGHT|FKEY|
    */

    [_RAISE] = LAYOUT_arrow_wrapper(
      ___________________RAISE1__________________,
      ___________________RAISE2__________________,
      ___________________RVAN_3__________________,
      ___________________RVAN_4__________________
    ),

    /*
     *  |REST|EERS|    |    |    |    |    |    |    |    |    |      |
     *  |     |    |    |    |    |    |    |    |    |    |    |     |
     *  |      |    |    |    |    |    |    |    |    |    |    |    |
     *  |     |       |     |   ENTR   |  SPACE |      |    |    |    |
     */

    [_ADJUST] = LAYOUT_arrow_wrapper(
      ___________________ADJST1__________________,
      ___________________ADJST2__________________,
      ___________________ADJVAN3_________________,
      ___________________ADJVAN4_________________
    ),

    /*
     *  |    | F1 | F2 | F3 | F4 | F5 | F6 | F7 | F8 | F9 | F10|      |
     *  |     |    |    |    |    |    |    |    |    |F11 | F12|     |
     *  |      |    |    |    |    |    |    |    |    |    |    |    |
     *  |     |       |     |          |        | FKEY |    |    |    |
     */

    [_FKEY] = LAYOUT_arrow_wrapper(
      ___________________FKEY1___________________,
      ___________________FKEY2___________________,
      ___________________FVAN_3__________________,
      ___________________FVAN_4__________________
    ),
  };
