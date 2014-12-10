#include "keymap_common.h"

const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|
     * |-----------------------------------------------------------|
     * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|  '|Fn6     |
     * |-----------------------------------------------------------|
     * |Fn7     |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|Fn2|Shift |Fn1|
     * `-----------------------------------------------------------'
     *       |Gui|Alt  |         Fn4           |Fn5  |Gui|
     *       `-------------------------------------------'
     */
    [0] = \
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   FN3, QUOT,     FN6,                         P4,  P5,  P6,  PPLS,
    FN7, Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, FN2,           RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          FN4,                     RALT,FN5, FN5, FN1,      LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* Layer 1: HHKB mode[HHKB Fn]
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |Backs|
     * |-----------------------------------------------------------|
     * |Contro|VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |  +|  -|End|PgD|Dow|Shift |   |
     * `-----------------------------------------------------------'
     *       |Gui|Alt  |         Space         |Alt  |Gui|
     *       `-------------------------------------------'
     */ 
    [1] = \
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,
    GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,      INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    CAPS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  PSCR,SLCK,PAUS, UP,  NO, BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    LCTL,VOLD,VOLU,MUTE,NO,  NO,  PAST,PSLS,HOME,PGUP,LEFT,RGHT,     ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,NO,  NO,  NO,  NO,  NO,  PPLS,PMNS,END, PGDN,DOWN,          RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, TRNS,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* Layer 2: Vi mode[Slash]
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Tab  |Hom|PgD|Up |PgU|End|Hom|PgD|PgUlEnd|   |   |   |Backs|
     * |-----------------------------------------------------------|
     * |Contro|   |Lef|Dow|Rig|   |Lef|Dow|Up |Rig|   |   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |Hom|PgD|PgUlEnd|Fn0|Shift |   |
     * `-----------------------------------------------------------'
     *       |Gui|Alt  |          Space        |Alt  |Gui|
     *       `-------------------------------------------'
     */
    [2] = \
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,
    GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,      INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, HOME,PGDN,UP,  PGUP,END, HOME,PGDN,PGUP,END, NO,  NO,  NO,  BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    LCTL,NO,  LEFT,DOWN,RGHT,NO,  LEFT,DOWN,UP,  RGHT,NO,  NO,       ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,NO,  NO,  NO,  NO,  NO,  HOME,PGDN,PGUP,END, TRNS,          RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* Layer 3: Mouse mode(IJKL)[Semicolon]
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Tab  |   |   |   |   |   |MwL|MwD|McU|MwU|MwR|Wbk|Wfr|Alt-T|
     * |-----------------------------------------------------------|
     * |Contro|   |   |   |   |   |Mb2|McL|McD|McR|Fn |   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |Mb3|Mb2|Mb1|Mb4|Mb5|   |Shift |   |
     * `-----------------------------------------------------------'
     *      |Gui |Alt  |          Mb1          |Fn   |Fn |
     *      `--------------------------------------------'
     * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel8
     */
    [3] = \
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,
    GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, FN8,      INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    FN8, NO,  NO,  NO,  NO,  NO,  WH_L,WH_D,MS_U,WH_U,WH_R,WBAK,WFWD,FN8,      DEL, END, PGDN,    P7,  P8,  P9,
    LCTL,ACL0,ACL1,ACL2,ACL2,NO,  NO,  MS_L,MS_D,MS_R,TRNS,NO,       ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,NO,  NO,  NO,  NO,  BTN3,BTN2,BTN1,BTN4,BTN5,NO,            RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          BTN1,                    RALT,TRNS,TRNS,RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* Layer 5: Mouse mode(IJKL)[Space]
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Tab  |   |   |   |   |   |MwL|MwD|McU|MwU|MwR|Wbk|Wfr|Alt-T|
     * |-----------------------------------------------------------|
     * |Contro|   |   |   |   |   |Mb2|McL|McD|McR|Mb1|   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |Mb3|Mb2|Mb1|Mb4|Mb5|   |Shift |   |
     * `-----------------------------------------------------------'
     *      |Gui |Alt  |          Mb1          |Fn   |Fn |
     *      `--------------------------------------------'
     * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel8
     */
    [4] = \
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,
    GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, FN8,      INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    FN8, NO,  NO,  NO,  NO,  NO,  WH_L,WH_D,MS_U,WH_U,WH_R,WBAK,WFWD,FN8,      DEL, END, PGDN,    P7,  P8,  P9,
    LCTL,ACL0,ACL1,ACL2,ACL2,NO,  NO,  MS_L,MS_D,MS_R,BTN1,NO,       ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,NO,  NO,  NO,  NO,  BTN3,BTN2,BTN1,BTN4,BTN5,NO,            RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          TRNS,                    RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),
};


/*
 * Macro definition
 */
enum macro_id {
    ALT_TAB,
};
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case ALT_TAB:
            return (record->event.pressed ?
                    MACRO( D(LALT), D(TAB), END ) :
                    MACRO( U(TAB), END ));
    }
    return MACRO_NONE;
}


/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION_ENABLE
const uint16_t fn_actions[] __attribute__ ((section (".keymap.fn_actions"))) = {
#else
const uint16_t fn_actions[] PROGMEM = {
#endif
    [0] = ACTION_DEFAULT_LAYER_SET(0),                // Default layer(not used)
    [1] = ACTION_LAYER_TAP_TOGGLE(1),                 // HHKB layer(toggle with 5 taps)
    [2] = ACTION_LAYER_TAP_KEY(2, KC_SLASH),          // Cursor layer with Slash*
    [3] = ACTION_LAYER_TAP_KEY(3, KC_SCLN),           // Mousekey layer with Semicolon*
    [4] = ACTION_LAYER_TAP_KEY(4, KC_SPC),            // Mousekey layer with Space
    [5] = ACTION_LAYER_MOMENTARY(3),                  // Mousekey layer
    [6] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_ENT),      // RControl with tap Enter
    [7] = ACTION_MODS_ONESHOT(MOD_LSFT),              // Oneshot Shift
    [8] = ACTION_MACRO(ALT_TAB),                      // Application switching
};
