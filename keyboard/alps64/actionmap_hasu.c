#include <avr/pgmspace.h>
#include "actionmap.h"
#include "action_code.h"
#include "actionmap_common.h"


/*
 * Actions
 */
#define AC_LM1      ACTION_LAYER_MOMENTARY(1)                   // HHKB layer
#define AC_LT1      ACTION_LAYER_TAP_KEY(1, KC_ENTER)           // HHKB layer
#define AC_LT2      ACTION_LAYER_TAP_KEY(2, KC_SLASH)           // Cursor layer with Slash*
#define AC_LT3      ACTION_LAYER_TAP_KEY(3, KC_SCLN)            // Mousekey layer with Semicolon*
#define AC_LT4      ACTION_LAYER_TAP_KEY(4, KC_SPC)             // Space Fn
#define AC_LM3      ACTION_LAYER_MOMENTARY(3)                   // Mousekey layer(IJKL)
#define AC_APSW     ACTION_MACRO(ALT_TAB)                       // Application switching
#define AC_BACK     ACTION_MODS_KEY(MOD_LALT, KC_LEFT)
#define AC_FRWD     ACTION_MODS_KEY(MOD_LALT, KC_RIGHT)
#define AC_LM5      ACTION_LAYER_MOMENTARY(5)


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


const uint16_t PROGMEM actionmaps[][MATRIX_ROWS][MATRIX_COLS] = {
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
    [0] = ACTIONMAP_AEK( \
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSPC, \
        LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   LT3, QUOT,LT1, \
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, LT2, RSFT, \
        LCTL,LGUI,LALT,          LT4,                          LM5, LM3, LM1),
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
        PWR, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, GRV, \
        CAPS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS,UP,  TRNS,DEL, \
        TRNS,VOLD,VOLU,MUTE,TRNS,TRNS,PAST,PSLS,HOME,PGUP,LEFT,RGHT,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PPLS,PMNS,END, PGDN,DOWN,TRNS, \
        TRNS,TRNS,TRNS,          TRNS,                         TRNS,TRNS,TRNS),

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
    [2] = ACTIONMAP_AEK( \
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, GRV, \
        TAB, HOME,PGDN,UP,  PGUP,END, HOME,PGDN,PGUP,END, TRNS,TRNS,TRNS,DEL, \
        TRNS,TRNS,LEFT,DOWN,RGHT,TRNS,LEFT,DOWN,UP,  RGHT,TRNS,TRNS,ENT, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,HOME,PGDN,PGUP,END, TRNS,TRNS, \
        TRNS,TRNS,TRNS,          TRNS,                         TRNS,TRNS,TRNS),

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
    [3] = ACTIONMAP_AEK( \
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, GRV, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,WH_D,MS_U,WH_U,RGHT,BACK,FRWD,APSW, \
        TRNS,ACL0,ACL1,ACL2,ACL2,NO,  NO,  MS_L,MS_D,MS_R,TRNS,TRNS,TRNS,\
        TRNS,TRNS,TRNS,TRNS,TRNS,BTN3,BTN2,BTN1,BACK,FRWD,TRNS,TRNS, \
        TRNS,TRNS,TRNS,          BTN1,                         TRNS,TRNS,TRNS),

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
    [4] = ACTIONMAP_AEK( \
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, GRV, \
        APSW,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,WH_D,MS_U,WH_U,RGHT,BACK,FRWD,APSW, \
        TRNS,VOLD,VOLU,MUTE,TRNS,TRNS,TRNS,MS_L,MS_D,MS_R,BTN1,TRNS,ENT, \
        TRNS,TRNS,TRNS,TRNS,TRNS,BTN3,BTN2,BTN1,BACK,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,          TRNS,                         TRNS,TRNS,TRNS),

    /* 40% */
    [5] = ACTIONMAP_AEK( \
        TRNS,1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   TRNS,TRNS,TRNS, \
        TRNS,s(1),s(2),s(3),s(4),s(5),s(6),s(7),s(8),s(9),s(0),TRNS,TRNS,TRNS, \
        TRNS,1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,          TRNS,                         TRNS,TRNS,TRNS),
};
