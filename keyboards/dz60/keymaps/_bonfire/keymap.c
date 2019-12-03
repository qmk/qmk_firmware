#include QMK_KEYBOARD_H

/**
 * Each layer gets a name for readability.
 *
 * v6.1.0
 * 
 */
#define BASE    0   // Layer: QWERTY / Base
#define NRMN    1   // Layer: Norman
#define GAME    2   // Layer: Game
#define FCTN    3   // Layer: Function
#define KEYB    4   // Layer: Keyboard

#include "keymap-defs.c"
#include "keymap-layers.c"
#include "keymap-functions.c"
