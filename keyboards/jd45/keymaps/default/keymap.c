#include "jd45.h"

/* this keymap is to provide a basic keyboard layout for testing the matrix
 * for more practical and complicated keymap refer to other keymaps in the same folder
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP(
  ESC,   Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,     QUOT, BSPC,
  TAB,   A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN,  ENT,
  LSFT,  Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH,  RSFT,
  PAUSE, LCTL, LALT, DEL,  SPC,  DEL,  LEFT, UP,   DOWN, RIGHT ),
};

const uint16_t PROGMEM fn_actions[] = {

};
