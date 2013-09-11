/*
Copyright 2011,2012,2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* 
 * Keymap for PFU HHKB Pro
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "debug.h"
#include "keymap.h"


#define KEYMAP( \
    K31, K30, K00, K10, K11, K20, K21, K40, K41, K60, K61, K70, K71, K50, K51, \
    K32, K01, K02, K13, K12, K23, K22, K42, K43, K62, K63, K73, K72, K52, \
    K33, K04, K03, K14, K15, K24, K25, K45, K44, K65, K64, K74, K53, \
    K34, K05, K06, K07, K16, K17, K26, K46, K66, K76, K75, K55, K54, \
         K35, K36,           K37,                K57, K56 \
) \
{ \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07 }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_NO    }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37 }, \
    { KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_NO    }, \
    { KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57 }, \
    { KC_##K60, KC_##K61, KC_##K62, KC_##K63, KC_##K64, KC_##K65, KC_##K66, KC_NO    }, \
    { KC_##K70, KC_##K71, KC_##K72, KC_##K73, KC_##K74, KC_##K75, KC_##K76, KC_NO    } \
}

#ifdef KEYMAP_SECTION
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
static const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|
     * |-----------------------------------------------------------|
     * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|  '|Fn4     |
     * |-----------------------------------------------------------|
     * |Fn5     |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|Fn2|Shift |Fn1|
     * `-----------------------------------------------------------'
     *       |Gui|Alt  |         Fn6           |Alt  |Fn7|
     *       `-------------------------------------------'
     */
    KEYMAP(ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,GRV, \
           TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSPC, \
           LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   FN3, QUOT,FN4, \
            FN5,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, FN2, RSFT,FN1, \
                LGUI,LALT,          FN6,                RALT,RGUI),

    /* Layer 1: HHKB mode (HHKB Fn)
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
    KEYMAP(GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
           CAPS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  PSCR,SLCK,PAUS, UP,  NO,  BSPC, \
           LCTL,VOLD,VOLU,MUTE,NO,  NO,  PAST,PSLS,HOME,PGUP,LEFT,RGHT,ENT, \
           LSFT,NO,  NO,  NO,  NO,  NO,  PPLS,PMNS,END, PGDN,DOWN,RSFT,TRNS, \
                LGUI,LALT,          SPC,                RALT,RGUI),

    /* Layer 2: Vi mode (Slash)
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
    KEYMAP(GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
           TAB, HOME,PGDN,UP,  PGUP,END, HOME,PGDN,PGUP,END, NO,  NO,  NO,  BSPC, \
           LCTL,NO,  LEFT,DOWN,RGHT,NO,  LEFT,DOWN,UP,  RGHT,NO,  NO,  ENT, \
           LSFT,NO,  NO,  NO,  NO,  NO,  HOME,PGDN,PGUP,END, TRNS,RSFT,NO, \
                LGUI,LALT,          SPC,                RALT,RGUI),

    /* Layer 3: Mouse mode (Semicolon)
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
           TAB, NO,  NO,  NO,  NO,  NO,  WH_L,WH_D,WH_U,WH_R,NO,  NO,  NO,  BSPC, \
           LCTL,NO,  ACL0,ACL1,ACL2,NO,  MS_L,MS_D,MS_U,MS_R,TRNS,QUOT,ENT, \
           LSFT,NO,  NO,  NO,  NO,  BTN3,BTN2,BTN1,BTN4,BTN5,SLSH,RSFT,NO, \
                LGUI,LALT,          BTN1,               RALT,TRNS),

    /* Layer 4: Matias half-qwerty keyboard style (Space)
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

    /* Layer5: another Mouse mode (Space)
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Tab  |   |   |   |   |   |MwL|MwD|MwU|MwR|   |Wbk|Wfr|Close|
     * |-----------------------------------------------------------|
     * |Contro|   |   |   |   |   |McL|McD|McU|McR|Fn0|   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |Mb3|Mb2|Mb1|Mb4|Mb5|   |Shift |   |
     * `-----------------------------------------------------------'
     *      |Gui |Alt  |          Fn0          |Alt  |Fn0|
     *      `--------------------------------------------'
     * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel 
     */
    KEYMAP(ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
           TAB, NO,  NO,  NO,  NO,  NO,  WH_L,WH_D,WH_U,WH_R,WSTP,WBAK,WFWD,FN8, \
           LCTL,NO,  ACL0,ACL1,ACL2,NO,  MS_L,MS_D,MS_U,MS_R,NO,  NO,  ENT, \
           LSFT,NO,  NO,  NO,  NO,  BTN3,BTN2,BTN1,BTN4,BTN5,NO,  RSFT,NO, \
                LGUI,LALT,          TRNS,               RALT,RGUI),
};



/* id for user defined functions */
enum function_id {
    LSHIFT_LPAREN,
    RSHIFT_RPAREN,
};

enum macro_id {
    LSHIFT_PAREN,
    RSHIFT_PAREN,
    HELLO,
    VOLUP,
};


/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION
const uint16_t fn_actions[] __attribute__ ((section (".keymap.fn_actions"))) = {
#else
static const uint16_t fn_actions[] PROGMEM = {
#endif
    [0] = ACTION_DEFAULT_LAYER_SET(0),                // Default layer(not used)
    [1] = ACTION_LAYER_TAP_TOGGLE(1),                 // HHKB layer(toggle with 5 taps)
    [2] = ACTION_LAYER_TAP_KEY(2, KC_SLASH),          // Cursor layer with Slash*
    [3] = ACTION_LAYER_TAP_KEY(3, KC_SCLN),           // Mousekey layer with Semicolon*
    [4] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_ENT),      // RControl with tap Enter*
    [5] = ACTION_MODS_ONESHOT(MOD_LSFT),              // Oneshot Shift*
    [6] = ACTION_LAYER_TAP_KEY(5, KC_SPC),            // Mousekey layer with Space
    [7] = ACTION_LAYER_TOGGLE(3),                     // Mousekey layer(toggle)
    [8] = ACTION_MODS_KEY(MOD_LCTL, KC_W),            // Close Tab

//  [8] = ACTION_LMOD_TAP_KEY(KC_LCTL, KC_BSPC),       // LControl with tap Backspace
//  [9] = ACTION_LMOD_TAP_KEY(KC_LCTL, KC_ESC),        // LControl with tap Esc
//  [11] = ACTION_FUNCTION_TAP(LSHIFT_LPAREN),         // Function: LShift with tap '('
//  [12] = ACTION_FUNCTION_TAP(RSHIFT_RPAREN),         // Function: RShift with tap ')'
//  [13] = ACTION_MACRO_TAP(LSHIFT_PAREN),             // Macro: LShift with tap '('
//  [14] = ACTION_MACRO_TAP(RSHIFT_PAREN),             // Macro: RShift with tap ')'
//  [15] = ACTION_MACRO(HELLO),                        // Macro: say hello
//  [9] = ACTION_MACRO(VOLUP),                         // Macro: media key
};


/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    keyevent_t event = record->event;
    tap_t tap = record->tap;

    switch (id) {
        case LSHIFT_PAREN:
            if (tap.count > 0 && !tap.interrupted) {
                return (event.pressed ?
                        MACRO( D(LSHIFT), D(9), U(9), U(LSHIFT), END ) : MACRO_NONE);
            } else {
                return (event.pressed ?
                        MACRO( D(LSHIFT), END ) : MACRO( U(LSHIFT), END ) );
            }
        case RSHIFT_PAREN:
            if (tap.count > 0 && !tap.interrupted) {
                return (event.pressed ?
                        MACRO( D(RSHIFT), D(0), U(0), U(RSHIFT), END ) : MACRO_NONE);
            } else {
                return (event.pressed ?
                        MACRO( D(RSHIFT), END ) : MACRO( U(RSHIFT), END ) );
            }
        case HELLO:
            return (event.pressed ?
                    MACRO( I(0), T(H), T(E), T(L), T(L), W(255), T(O), END ) :
                    MACRO_NONE );
        case VOLUP:
            return (event.pressed ?
                    MACRO( D(VOLU), U(VOLU), END ) :
                    MACRO_NONE );
    }
    return MACRO_NONE;
}



/*
 * user defined action function
 */
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    keyevent_t event = record->event;
    tap_t tap = record->tap;

    switch (id) {
        case LSHIFT_LPAREN:
            // LShft + tap '('
            // NOTE: cant use register_code to avoid conflicting with magic key bind
            if (event.pressed) {
                if (tap.count == 0 || tap.interrupted) {
                    add_mods(MOD_BIT(KC_LSHIFT));
                } else {
                    host_add_mods(MOD_BIT(KC_LSHIFT));
                    host_add_key(KC_9);
                    host_send_keyboard_report();
                    host_del_mods(MOD_BIT(KC_LSHIFT));
                    host_del_key(KC_9);
                    host_send_keyboard_report();
                }
            } else {
                if (tap.count == 0 || tap.interrupted) {
                    del_mods(MOD_BIT(KC_LSHIFT));
                }
            }
            break;
        case RSHIFT_RPAREN:
            // RShift + tap ')'
            if (event.pressed) {
                if (tap.count == 0 || tap.interrupted) {
                    add_mods(MOD_BIT(KC_RSHIFT));
                } else {
                    host_add_mods(MOD_BIT(KC_RSHIFT));
                    host_add_key(KC_0);
                    host_send_keyboard_report();
                    host_del_mods(MOD_BIT(KC_RSHIFT));
                    host_del_key(KC_0);
                    host_send_keyboard_report();
                }
            } else {
                if (tap.count == 0 || tap.interrupted) {
                    del_mods(MOD_BIT(KC_RSHIFT));
                }
            }
            break;
    }
}



/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, key_t key)
{
    return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
}

/* translates Fn index to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
    action_t action;
    action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
    return action;
}
