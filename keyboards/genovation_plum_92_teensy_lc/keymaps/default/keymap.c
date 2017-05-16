#include "action_layer.h"
#include "genovation_plum_92_teensy_lc.h"

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qerty */
[0] = KEYMAP(ESC,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10,  F11,  F12, PSCR, F14,   F15, \
             GRV,  1,   2,   3,   4,   5,   6,   7,   8,   9,   0,    MINS, EQL, BSPC, INS,   PGUP,  \
             TAB,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,    LBRC, RBRC,BSLS, DELETE,PGDN, \
             BSPC, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN, QUOT, DELETE, HOME, X,  VOLU, \
             LSFT, Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH, RSFT, UP,  END,  X,     VOLD, \
             LCTL, LALT,LGUI,     SPC,           ENT,      FN2, RCTL, LEFT, DOWN,RGHT, FN0,   MUTE),

    /* 1: FN 1 */
[1] = KEYMAP(ESC,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10,  F11,  F12, PSCR, F14,   F15, \
             GRV,  1,   2,   3,   4,   5,   6,   7,   8,   9,   0,    MINS, EQL, BSPC, INS,   PGUP,  \
             TAB,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,    LBRC, RBRC,BSLS, DELETE,PGDN, \
             BSPC, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN, QUOT, DELETE, HOME, X,  VOLU, \
             LSFT, Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH, RSFT, UP,  END,  X,     VOLD, \
             LCTL, LALT,LGUI,     SPC,           ENT,      FN2, RCTL, LEFT, DOWN,RGHT, FN0,   MUTE),
};