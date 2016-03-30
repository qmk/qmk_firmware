#include "keymap_common.h"

/*
 * Hasu
 */
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|   \   |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Bspc |
     * |-----------------------------------------------------------|
     * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|  '|FN1     |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|Fn2|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui |Alt  |       Space            |Alt   |Fn5 |Ctrl |
     * `-----------------------------------------------------------'
     */
    [0] = KEYMAP_AEK( \
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSPC, \
        LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   FN3, QUOT,FN1, \
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, FN2, RSFT, \
        LCTL,LGUI,LALT,          FN4,                          RALT,FN5, FN0),

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
    [1] = KEYMAP_AEK( \
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, GRV, \
        CAPS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  PSCR,SLCK,PAUS,UP,  NO,  DEL, \
        LCTL,VOLD,VOLU,MUTE,NO,  NO,  PAST,PSLS,HOME,PGUP,LEFT,RGHT,TRNS, \
        LSFT,NO,  NO,  NO,  NO,  NO,  PPLS,PMNS,END, PGDN,DOWN,RSFT, \
        LCTL,LGUI,LALT,          TRNS,                         RALT,RGUI,TRNS),

    /* Vi mode[Slash]
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Del    |
     * |-----------------------------------------------------------|
     * |Tab  |Hom|PgD|Up |PgU|End|Hom|PgD|PgUlEnd|   |   |   |Backs|
     * |-----------------------------------------------------------|
     * |Contro|   |Lef|Dow|Rig|   |Lef|Dow|Up |Rig|   |   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |Hom|PgD|PgUlEnd|Fn0|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui |Alt  |       Space            |Alt   |Fn5 |Ctrl |
     * `-----------------------------------------------------------'
     */
    [2] = KEYMAP_AEK( \
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, GRV, \
        TAB, HOME,PGDN,UP,  PGUP,END, HOME,PGDN,PGUP,END, NO,  NO,  NO,  DEL, \
        LCTL,NO,  LEFT,DOWN,RGHT,NO,  LEFT,DOWN,UP,  RGHT,NO,  NO,  ENT, \
        LSFT,NO,  NO,  NO,  NO,  NO,  HOME,PGDN,PGUP,END, FN2, RSFT, \
        LCTL,LGUI,LALT,          SPC,                          RALT,RGUI,RCTL),

    /* Mouse mode(IJKL)[Semicolon]
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Tab  |   |   |   |   |   |MwL|MwD|McU|MwU|MwR|Wbk|Wfr|Alt-T|
     * |-----------------------------------------------------------|
     * |Contro|   |   |   |   |   |Mb2|McL|McD|McR|Fn |   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |Mb3|Mb2|Mb1|Mb4|Mb5|   |Shift |   |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui |Alt  |       Space            |Alt   |Fn5 |Ctrl |
     * `-----------------------------------------------------------'
     * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel
     */
    [3] = KEYMAP_AEK( \
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, GRV, \
        FN8, NO,  NO,  NO,  NO,  NO,  NO,  WH_D,MS_U,WH_U,RGHT,FN9, FN10,FN8, \
        LCTL,ACL0,ACL1,ACL2,ACL2,NO,  NO,  MS_L,MS_D,MS_R,TRNS,NO,  ENT, \
        LSFT,NO,  NO,  NO,  NO,  BTN3,BTN2,BTN1,FN9, FN10,NO,  RSFT, \
        LCTL,LGUI,LALT,          BTN1,                         TRNS,TRNS,TRNS),

    /* Layer 4: Mouse mode(IJKL)[Space]
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Tab  |   |   |   |   |   |MwL|MwD|McU|MwU|MwR|Wbk|Wfr|Alt-T|
     * |-----------------------------------------------------------|
     * |Contro|   |   |   |   |   |Mb2|McL|McD|McR|Mb1|   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |Mb3|Mb2|Mb1|Mb4|Mb5|   |Shift |   |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui |Alt  |       Space            |Alt   |Fn5 |Ctrl |
     * `-----------------------------------------------------------'
     * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel
     */
    [4] = KEYMAP_AEK( \
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, GRV, \
        FN8, NO,  NO,  NO,  NO,  NO,  NO,  WH_D,MS_U,WH_U,RGHT,FN9, FN10,FN8, \
        LCTL,VOLD,VOLU,MUTE,NO,  NO,  NO,  MS_L,MS_D,MS_R,BTN1,NO,  ENT, \
        LSFT,NO,  NO,  NO,  NO,  BTN3,BTN2,BTN1,FN9, FN10,NO,  RSFT, \
        LCTL,LGUI,LALT,          TRNS,                         TRNS,TRNS,TRNS),
};


/* id for user defined function/macro */
enum function_id {
    NONE,
};

enum macro_id {
    ALT_TAB,
};


/*
 * Fn action definition
 */
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),                  // HHKB layer
    [1] = ACTION_LAYER_TAP_KEY(1, KC_ENTER),          // HHKB layer
    [2] = ACTION_LAYER_TAP_KEY(2, KC_SLASH),          // Cursor layer with Slash*
    [3] = ACTION_LAYER_TAP_KEY(3, KC_SCLN),           // Mousekey layer with Semicolon*
    [4] = ACTION_LAYER_TAP_KEY(4, KC_SPC),            // Mousekey layer with Space
    [5] = ACTION_LAYER_MOMENTARY(3),                  // Mousekey layer(IJKL)
    [6] = ACTION_LAYER_TAP_KEY(MOD_RCTL, KC_ENT),      // RControl with tap Enter
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
        case ALT_TAB:
            return (record->event.pressed ?
                    MACRO( D(LALT), D(TAB), END ) :
                    MACRO( U(TAB), END ));
    }
    return MACRO_NONE;
}
