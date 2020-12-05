#include QMK_KEYBOARD_H
#include "bbaserdem.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Layout
 * ,-----------------------------------------------------------.
 * |Blt|Lck| ` | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = |
 * |---+---+-----------------------------------------------+---|
 * |Int|Trm|                                               |Cps|
 * |---+---|                                               |---|
 * |Clc|Psw|                                               | \ |
 * |---+---|                    PLANCK                     |---|
 * |Rev|Ffw|                                               | [ |
 * |---+---|                                               |---|
 * |Tog|Mut|                                               | ] |
 * `-----------------------------------------------------------'
 */
[0] = KM( FKLAVYE ),
[1] = KM( AYARLAR ),
};

