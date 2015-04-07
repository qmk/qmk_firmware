/* 
 * Hasu: my personal keymap
 */
#include "keymap_common.h"


#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
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
    KEYMAP(ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,GRV, \
           TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSPC, \
           LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   FN3, QUOT,FN6, \
           FN7, Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, FN2, RSFT,FN1, \
                LGUI,LALT,          FN4,                FN5, RGUI),

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
    KEYMAP(GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
           CAPS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  PSCR,SLCK,PAUS, UP,  NO,  BSPC, \
           LCTL,VOLD,VOLU,MUTE,NO,  NO,  PAST,PSLS,HOME,PGUP,LEFT,RGHT,ENT, \
           LSFT,NO,  NO,  NO,  NO,  NO,  PPLS,PMNS,END, PGDN,DOWN,RSFT,TRNS, \
                LGUI,LALT,          TRNS,               RALT,RGUI),

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
    KEYMAP(GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
           TAB, HOME,PGDN,UP,  PGUP,END, HOME,PGDN,PGUP,END, NO,  NO,  NO,  BSPC, \
           LCTL,NO,  LEFT,DOWN,RGHT,NO,  LEFT,DOWN,UP,  RGHT,NO,  NO,  ENT, \
           LSFT,NO,  NO,  NO,  NO,  NO,  HOME,PGDN,PGUP,END, FN2, RSFT,TRNS, \
                LGUI,LALT,          SPC,                RALT,RGUI),

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
     * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel
     */
    [3] = \
    KEYMAP(GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
           FN8, NO,  NO,  NO,  NO,  NO,  WH_L,WH_D,MS_U,WH_U,WH_R,FN9, FN10,FN8, \
           LCTL,ACL0,ACL1,ACL2,ACL2,NO,  NO,  MS_L,MS_D,MS_R,FN3, NO,  ENT, \
           LSFT,NO,  NO,  NO,  NO,  BTN3,BTN2,BTN1,FN9, FN10,NO,  RSFT,TRNS, \
                LGUI,LALT,          BTN1,               TRNS,TRNS),

    /* Layer 4: Mouse mode(IJKL)[Space]
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
     * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel
     */
    [4] = \
    KEYMAP(GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
           FN8, NO,  NO,  NO,  NO,  NO,  WH_L,WH_D,MS_U,WH_U,WH_R,BTN4,BTN5,FN8, \
           LCTL,VOLD,VOLU,MUTE,NO,  NO,  NO,  MS_L,MS_D,MS_R,BTN1,NO,  ENT, \
           LSFT,NO,  NO,  NO,  NO,  BTN3,BTN2,BTN1,FN9, FN10,NO,  RSFT,TRNS, \
                LGUI,LALT,          TRNS,               TRNS,TRNS),

#if 0
    /* Layer 3: Mouse mode(HJKL)[Semicolon]
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Tab  |   |   |   |   |   |MwL|MwD|MwU|MwR|   |   |   |Backs|
     * |-----------------------------------------------------------|
     * |Contro|   |   |   |   |   |McL|McD|McU|McR|Fn0|   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |Mb3|Mb2|Mb1|Mb4|Mb5|   |Shift |   |
     * `-----------------------------------------------------------'
     *      |Gui |Alt  |          Mb1          |Alt  |Fn0|
     *      `--------------------------------------------'
     * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel 
     */
    KEYMAP(GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
           TAB, NO,  NO,  NO,  NO,  NO,  NO,  WH_D,WH_U,RGHT,NO,  NO,  NO,  BSPC, \
           LCTL,NO,  ACL0,ACL1,ACL2,NO,  MS_L,MS_D,MS_U,MS_R,TRNS,QUOT,ENT, \
           LSFT,NO,  NO,  NO,  NO,  BTN3,BTN2,BTN1,FN9, FN10,SLSH,RSFT,NO, \
                LGUI,LALT,          BTN1,               RALT,TRNS),

    /* Layer4: Mouse mode(HJKL)[Space]
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Tab  |   |   |   |   |   |MwL|MwD|MwU|MwR|   |Wbk|Wfr|Alt-T|
     * |-----------------------------------------------------------|
     * |Contro|   |   |   |   |   |McL|McD|McU|McR|Fn0|   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |Mb3|Mb2|Mb1|Mb4|Mb5|   |Shift |   |
     * `-----------------------------------------------------------'
     *      |Gui |Alt  |          Fn0          |Alt  |Fn0|
     *      `--------------------------------------------'
     * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel 
     */
    KEYMAP(GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
           FN8, NO,  NO,  NO,  NO,  NO,  NO,  WH_D,WH_U,RGHT,NO,  FN9, FN10,FN8, \
           LCTL,NO,  ACL0,ACL1,ACL2,NO,  MS_L,MS_D,MS_U,MS_R,BTN1,NO,  ENT, \
           LSFT,NO,  NO,  NO,  NO,  BTN3,BTN2,BTN1,FN9, FN10,NO,  RSFT,NO, \
                LGUI,LALT,          TRNS,               RALT,RGUI),
#endif
#if 0
    /* Layer x: Matias half-qwerty keyboard style[Space]
     * ,-----------------------------------------------------------.
     * |  -|  0|  9|  8|  7|  6|  5|  4|  3|  2|  1|   |   |   |Esc|
     * |-----------------------------------------------------------|
     * |Backs|  P|  O|  I|  U|  Y|  T|  R|  E|  W|  Q|   |   |Tab  |
     * |-----------------------------------------------------------|
     * |Contro|  ;|  L|  K|  J|  H|  G|  F|  D|  S|  A|Con|Control |
     * |-----------------------------------------------------------|
     * |Shift   |  /|  .|  ,|  M|  N|  B|  V|  C|  X|  Z|Shift |   |
     * `-----------------------------------------------------------'
     *      |Gui |Alt  |          Fn0          |Alt  |Gui|
     *      `--------------------------------------------'
     */
    KEYMAP(MINS,0,   9,   8,   7,   6,   5,   4,   3,   2,   1,   NO,  NO,  NO,  ESC, \
           BSPC,P,   O,   I,   U,   Y,   T,   R,   E,   W,   Q,   NO,  NO,  TAB, \
           LCTL,SCLN,L,   K,   J,   H,   G,   F,   D,   S,   A,   RCTL,RCTL, \
           LSFT,SLSH,DOT, COMM,M,   N,   B,   V,   C,   X,   Z,   RSFT,NO, \
                LGUI,LALT,          TRNS,               RALT,RGUI),
#endif
};



/* id for user defined functions */
enum function_id {
    LSHIFT_LPAREN,
};

enum macro_id {
    HELLO,
    VOLUP,
    ALT_TAB,
};


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
    [5] = ACTION_LAYER_MOMENTARY(4),                  // Mousekey layer(IJKL)
    [6] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_ENT),      // RControl with tap Enter
    [7] = ACTION_MODS_ONESHOT(MOD_LSFT),              // Oneshot Shift
    [8] = ACTION_MACRO(ALT_TAB),                      // Application switching
    [9] = ACTION_MODS_KEY(MOD_LALT, KC_LEFT),
   [10] = ACTION_MODS_KEY(MOD_LALT, KC_RIGHT),

//  [x] = ACTION_LMOD_TAP_KEY(KC_LCTL, KC_BSPC),        // LControl with tap Backspace
//  [x] = ACTION_LMOD_TAP_KEY(KC_LCTL, KC_ESC),         // LControl with tap Esc
//  [x] = ACTION_FUNCTION_TAP(LSHIFT_LPAREN),           // Function: LShift with tap '('
//  [x] = ACTION_MACRO(HELLO),                          // Macro: say hello
//  [x] = ACTION_MACRO(VOLUP),                          // Macro: media key
};


/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case HELLO:
            return (record->event.pressed ?
                    MACRO( I(0), T(H), T(E), T(L), T(L), W(255), T(O), END ) :
                    MACRO_NONE );
        case VOLUP:
            return (record->event.pressed ?
                    MACRO( D(VOLU), U(VOLU), END ) :
                    MACRO_NONE );
        case ALT_TAB:
            return (record->event.pressed ?
                    MACRO( D(LALT), D(TAB), END ) :
                    MACRO( U(TAB), END ));
    }
    return MACRO_NONE;
}



/*
 * user defined action function
 */
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (record->event.pressed) dprint("P"); else dprint("R");
    dprintf("%d", record->tap.count);
    if (record->tap.interrupted) dprint("i");
    dprint("\n");

    switch (id) {
        case LSHIFT_LPAREN:
            // Shift parentheses example: LShft + tap '('
            // http://stevelosh.com/blog/2012/10/a-modern-space-cadet/#shift-parentheses
            // http://geekhack.org/index.php?topic=41989.msg1304899#msg1304899
            if (record->event.pressed) {
                if (record->tap.count > 0 && !record->tap.interrupted) {
                    if (record->tap.interrupted) {
                        dprint("tap interrupted\n");
                        register_mods(MOD_BIT(KC_LSHIFT));
                    }
                } else {
                    register_mods(MOD_BIT(KC_LSHIFT));
                }
            } else {
                if (record->tap.count > 0 && !(record->tap.interrupted)) {
                    add_weak_mods(MOD_BIT(KC_LSHIFT));
                    send_keyboard_report();
                    register_code(KC_9);
                    unregister_code(KC_9);
                    del_weak_mods(MOD_BIT(KC_LSHIFT));
                    send_keyboard_report();
                    record->tap.count = 0;  // ad hoc: cancel tap
                } else {
                    unregister_mods(MOD_BIT(KC_LSHIFT));
                }
            }
            break;
    }
}
