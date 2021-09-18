/*
 * Good on you for modifying your layout, this is the most nonQMK layout you will come across
 * There are three modes, Steno (the default), QWERTY (Toggleable) and a Momentary symbol layer
 *
 * Don't modify the steno layer directly, instead add chords using the keycodes and macros
 * from sten.h to the layout you want to modify.
 *
 * Observe the comment above processQWERTY!
 *
 * http://docs.gboards.ca
 */

#include QMK_KEYBOARD_H
//#include "sten.h"
#include "keymap_plover_hid.h"

// Proper Layers
#define FUNCT   (LSD | LK | LP | LH)
#define MEDIA   (LSD | LK | LW | LR)
#define MOVE    (ST1 | ST2)

// QMK Layers
#define STENO_LAYER   0

/* Keyboard Layout
 * ,---------------------------------.    ,------------------------------.
 * | FN  | LSU | LFT | LP | LH | ST1 |    | ST3 | RF | RP | RL | RT | RD |
 * |-----+-----+-----+----+----|-----|    |-----|----+----+----+----+----|
 * | PWR | LSD | LK  | LW | LR | ST2 |    | ST4 | RR | BB | RG | RS | RZ |
 * `---------------------------------'    `------------------------------'
 *                   ,---------------,    .---------------.
 *                   | LNO | LA | LO |    | RE | RU | RNO |
 *                   `---------------'    `---------------'
 */

// "Layers"
// Steno layer should be first in your map.
// When PWR | FN | ST3 | ST4 is pressed, the layer is increased to the next map. You must return to STENO_LAYER at the end.
// If you need more space for chords, remove the two gaming layers.
// Note: If using NO_ACTION_TAPPING, LT will not work!

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Main layer, everything goes through here
    [0] = LAYOUT_georgi(
    PLV_X1,  PLV_SL,  PLV_TL,  PLV_PL,  PLV_HL,  PLV_STR,       PLV_STR, PLV_FR,  PLV_PR,  PLV_LR,  PLV_TR,  PLV_DR,
    PLV_X2,  PLV_SL,  PLV_KL,  PLV_WL,  PLV_RL,  PLV_STR,       PLV_STR, PLV_RR,  PLV_BR,  PLV_GR,  PLV_SR,  PLV_ZR,
                              PLV_NUM,  PLV_A,     PLV_O,         PLV_E,  PLV_U, PLV_NUM
    )
};
// Don't fuck with this, thanks.
size_t keymapsCount  = sizeof(keymaps)/sizeof(keymaps[0]);
