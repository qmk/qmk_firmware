#include "s60_x.h"

/* Main layer: Test layout, using all keys.

      0     1     2     3     4     5     6     7     8     9     A     B     C     D     E
   ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
 0 │GRAVE│  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  -  │  =  │PGUP │BKSPC│
   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 1 │ TAB │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │  \  │█████│
   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 2 │CAPSL│  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  │  '  │PGDN │ENTER│█████│
   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 3 │LSHFT│HOME │  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │ END │RSHFT│  UP │
   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 4 │LCTRL│L_GUI│L_ALT│█████│█████│█████│ SPC │█████│█████│█████│R_ALT│R_GUI│ APP │RCTRL│█████│
   └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: ANSI qwerty */
	LAYOUT_legacy(GRV,    1,    2,    3,    4,    5,    6,    7,    8,    9,    0, MINS,  EQL, PGUP, BSPC, \
           TAB,    Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P, LBRC, RBRC, BSLS,       \
          CAPS,    A,    S,    D,    F,    G,    H,    J,    K,    L, SCLN, QUOT, PGDN, ENT ,       \
          LSFT, HOME,    Z,    X,    C,    V,    B,    N,    M, COMM,  DOT, SLSH,  END, RSFT,   UP, \
          LCTL, LGUI, LALT,                    SPC,                   RALT, RGUI,  APP, RCTL),
};
const uint16_t PROGMEM fn_actions[] = {};

