#include "keymap_common.h"

/*
 * Hasu
 */
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|  '|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|Fn2|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl|Gui |Alt |      Space             |Alt |Fn4 |Fn4 |Fn1 |
     * `-----------------------------------------------------------'
     */
    KEYMAP_ANSI(
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
        LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   FN2, QUOT,     ENT,  \
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, FN1,           FN9,  \
        LCTL,LGUI,LALT,          SPC,                     RALT,FN3, FN3, FN0),
    /* Keymap 1: colemak */
    KEYMAP_ANSI(
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC, \
        TAB, Q,   W,   F,   P,   G,   J,   L,   U,   Y,   SCLN,LBRC,RBRC,BSLS, \
        BSPC,A,   R,   S,   T,   D,   H,   N,   E,   I,   O,   QUOT,     ENT,  \
        LSFT,Z,   X,   C,   V,   B,   K,   M,   COMM,DOT, SLSH,          RSFT, \
        LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, FN0),
    /* Keymap 2: dvorak */
    KEYMAP_ANSI(
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   LBRC,RBRC,BSPC, \
        TAB, QUOT,COMM,DOT, P,   Y,   F,   G,   C,   R,   L,   SLSH,EQL, BSLS, \
        CAPS,A,   O,   E,   U,   I,   D,   H,   T,   N,   S,   MINS,     ENT,  \
        LSFT,SCLN,Q,   J,   K,   X,   B,   M,   W,   V,   Z,             RSFT, \
        LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, FN0),
    /* Keymap 3: workman */
    KEYMAP_ANSI(
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC, \
        TAB, Q,   D,   R,   W,   B,   J,   F,   U,   P,   SCLN,LBRC,RBRC,BSLS, \
        BSPC,A,   S,   H,   T,   G,   Y,   N,   E,   O,   I,   QUOT,     ENT,  \
        LSFT,Z,   X,   M,   C,   V,   K,   L,   COMM,DOT, SLSH,          RSFT, \
        LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, FN0),

    /* Overlay 4: HHKB mode
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete |
     * |-----------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |Inser|
     * |-----------------------------------------------------------|
     * |Contro|VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |  +|  -|End|PgD|Dow|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl|Gui |Alt |      Space             |Alt |Gui |App |    |
     * `-----------------------------------------------------------'
     */
    KEYMAP_ANSI(
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,  \
        CAPS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS,UP,  TRNS,INS,  \
        LCTL,VOLD,VOLU,MUTE,TRNS,TRNS,PAST,PSLS,HOME,PGUP,LEFT,RGHT,     ENT,  \
        LSFT,TRNS,TRNS,TRNS,TRNS,TRNS,PPLS,PMNS,END, PGDN,DOWN,          RSFT, \
        LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,FN4, TRNS),
    /* Overlay 5: Vi mode (Slash)
     * ,-----------------------------------------------------------.
     * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Backsp |
     * |-----------------------------------------------------------|
     * |Tab  |Hom|PgD|Up |PgU|End|Hom|PgD|PgU|End|   |   |   |     |
     * |-----------------------------------------------------------|
     * |Contro|   |Lef|Dow|Rig|   |Lef|Dow|Up |Rig|   |   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |Hom|PgD|PgU|End|   |Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl|Gui |Alt |      Space             |Alt |Gui |App |Ctrl|
     * `-----------------------------------------------------------'
     */
    KEYMAP_ANSI(
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, BSPC, \
        TAB, HOME,PGDN,UP,  PGUP,END, HOME,PGDN,PGUP,END, TRNS,TRNS,TRNS,TRNS, \
        LCTL,TRNS,LEFT,DOWN,RGHT,TRNS,LEFT,DOWN,UP,  RGHT,TRNS,TRNS,     ENT,  \
        LSFT,TRNS,TRNS,TRNS,TRNS,TRNS,HOME,PGDN,PGUP,END, TRNS,          RSFT, \
        LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL),
    /* Overlay 6: Mouse mode (Semicolon/App)
     * ,-----------------------------------------------------------.
     * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Backsp |
     * |-----------------------------------------------------------|
     * |Tab  |   |   |   |   |   |MwL|MwD|MwU|MwR|   |   |   |     |
     * |-----------------------------------------------------------|
     * |Contro|   |Ac0|Ac1|Ac1|   |McL|McD|McU|McR|   |   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |Mb3|Mb2|Mb1|Mb4|Mb5|   |Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl|Gui |Alt |      Space             |    |    |    |    |
     * `-----------------------------------------------------------'
     * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel
     */
    KEYMAP_ANSI(
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, BSPC, \
        TAB, TRNS,TRNS,TRNS,TRNS,TRNS,WH_L,WH_D,WH_U,WH_R,TRNS,TRNS,TRNS,TRNS, \
        LCTL,TRNS,ACL0,ACL1,ACL2,TRNS,MS_L,MS_D,MS_U,MS_R,TRNS,TRNS,     ENT,  \
        LSFT,TRNS,TRNS,TRNS,TRNS,BTN3,BTN2,BTN1,BTN4,BTN5,TRNS,          RSFT, \
        LCTL,LGUI,LALT,          BTN1,                    TRNS,TRNS,TRNS,RCTL),
    /* Overlay 7: Layout selector
     * ,-----------------------------------------------------------.
     * | Lq| Lc| Ld| Lw|   |   |   |   |   |   |   |   |   |       |
     * |-----------------------------------------------------------|
     * |     |Lq |Lw |   |   |   |   |   |   |   |   |   |   |     |
     * |-----------------------------------------------------------|
     * |      |   |   |Ld |   |   |   |   |   |   |   |   |        |
     * |-----------------------------------------------------------|
     * |        |   |   |Lc |   |   |   |   |   |   |   |          |
     * |-----------------------------------------------------------|
     * |    |    |    |                        |    |    |    |    |
     * `-----------------------------------------------------------'
     * Lq: set Qwerty layout
     * Lc: set Colemak layout
     * Ld: set Dvorak layout
     * Lw: set Workman layout
     */
    KEYMAP_ANSI(
        FN5, FN6, FN7, FN8, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,FN5, FN8, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,FN7, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS, \
        TRNS,TRNS,TRNS,FN6, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS, \
        TRNS,TRNS,TRNS,          TRNS,                    TRNS,TRNS,TRNS,TRNS),
};

/*
 * Fn action definition
 */
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(4),
    [1] = ACTION_LAYER_TAP_KEY(5, KC_SLASH),
    [2] = ACTION_LAYER_TAP_KEY(6, KC_SCLN),
    [3] = ACTION_LAYER_MOMENTARY(6),
    [4] = ACTION_LAYER_MOMENTARY(7),   // to Layout selector
    [5] = ACTION_DEFAULT_LAYER_SET(0),  // set qwerty layout
    [6] = ACTION_DEFAULT_LAYER_SET(1),  // set colemak layout
    [7] = ACTION_DEFAULT_LAYER_SET(2),  // set dvorak layout
    [8] = ACTION_DEFAULT_LAYER_SET(3),  // set workman layout
    [9] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_GRV),
};
