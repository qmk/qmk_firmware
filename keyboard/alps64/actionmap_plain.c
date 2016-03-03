#include <avr/pgmspace.h>
#include "actionmap.h"
#include "action_code.h"
#include "actionmap_common.h"


/*
 * Actions
 */
#define AC_LM1      ACTION_LAYER_MOMENTARY(1)                   // HHKB layer


const uint16_t PROGMEM actionmaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|BSpc   |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
     * |-----------------------------------------------------------|
     * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|  '|FN1     |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|Fn2|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui |Alt  |       Space            |Alt   |Fn5 |Ctrl |
     * `-----------------------------------------------------------'
     */
    [0] = ACTIONMAP_AEK( \
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
        LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,ENT, \
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT, \
        LCTL,LGUI,LALT,          SPC,                          RALT,RGUI,LM1),
    /* HHKB mode[HHKB Fn]
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|   `   |
     * |-----------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |Del  |
     * |-----------------------------------------------------------|
     * |Contro|VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |  +|  -|End|PgD|Dow|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui |Alt  |       Space            |Alt   |Fn5 |Ctrl |
     * `-----------------------------------------------------------'
     */
    [1] = ACTIONMAP_AEK( \
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, GRV, \
        CAPS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS,UP,  TRNS,DEL, \
        TRNS,VOLD,VOLU,MUTE,TRNS,TRNS,PAST,PSLS,HOME,PGUP,LEFT,RGHT,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PPLS,PMNS,END, PGDN,DOWN,TRNS, \
        TRNS,TRNS,TRNS,          TRNS,                         TRNS,TRNS,TRNS),
};
