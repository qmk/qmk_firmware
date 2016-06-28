#include "keymap_common.h"

const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  `|BSp|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn0|
     * |-----------------------------------------------------------'
     * |     |Gui|Alt  |         Space         |Alt  |Gui|   |     |
     * `-----------------------------------------------------------'
     */
    [0] =
    KEYMAP(ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,GRV, \
           TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSPC, \
           LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   FN3, QUOT,FN6, \
           FN7, Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, FN2, RSFT,FN1, \
           NO,  LGUI,LALT,          FN4,                FN5, RGUI,NO, NO),

    /* Layer 1: HHKB mode (HHKB Fn)
     * ,-----------------------------------------------------------.
     * |Pwr| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |Backs|
     * |-----------------------------------------------------------|
     * |      |VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
     * |-----------------------------------------------------------|
     * |        |   |   |   |   |   |  +|  -|End|PgD|Dow|      |   |
     * `-----------------------------------------------------------'
     * |     |Gui|Alt  |         Space         |Alt  |Gui|   |     |
     * `-----------------------------------------------------------'
     */ 
    [1] = 
    KEYMAP(PWR, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
           CAPS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS, UP,  TRNS,BSPC, \
           LCTL,VOLD,VOLU,MUTE,TRNS,TRNS,PAST,PSLS,HOME,PGUP,LEFT,RGHT,ENT, \
           LSFT,TRNS,TRNS,TRNS,TRNS,TRNS,PPLS,PMNS,END, PGDN,DOWN,RSFT,TRNS, \
           TRNS,LGUI,LALT,          TRNS,               RALT,RGUI,TRNS,TRNS),

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
           TRNS,LGUI,LALT,          SPC,                RALT,RGUI,TRNS,TRNS),

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
           TRNS,LGUI,LALT,          BTN1,               TRNS,TRNS,TRNS,TRNS),

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
           TRNS,LGUI,LALT,          TRNS,               TRNS,TRNS,TRNS,TRNS),

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
const uint16_t fn_actions[] = {
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
