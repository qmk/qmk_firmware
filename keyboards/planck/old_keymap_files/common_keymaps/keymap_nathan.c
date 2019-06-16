// Author: Nathan Ross Powell <nathanrospowell@gmail.com>
// https://github.com/nathanrosspowell/tmk_keyboard/blob/planck-jack/keyboard/planck/keymap_nathan.c

#include "keymap.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   /* 0: main layer
    * ,-----------------------------------------------------------------------.
    * |Tab  | q   | w   | e   | r   | t   | y   | u   | i   | o   | p   | BS  |
    * |-----------------------------------------------------------------------|
    * |Ctrl | a   | s   | d   | f   | g   | h   | j   | k   | l   | ;   | Ret |
    * |-----------------------------------------------------------------------|
    * |Shift| z   | x   | c   | v   | b   | n   | m   | [   | (   | {   | <   |
    * |-----------------------------------------------------------------------|
    * |Meta | \   | /   | Alt |Lower|Space|Space|Upper|Left |Down | Up  |Right|
    * `-----------------------------------------------------------------------'
    */
  [0] = KEYMAP_GRID(
       TAB,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    BSPC,
       LCTL, A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, ENT,
       RSFT, Z,    X,    C,    V,    B,    N,    M,    LBRC, FN10, FN11, FN12,
       LGUI, BSLS, SLSH, LALT, FN0,  SPC,  SPC,  FN1,  LEFT, DOWN, UP,   RGHT),

   /* 1: fn left/lower layer
    * The top row are Visual Studio combos:
    *   'Run', 'Breakpoint', 'Step over', 'Step into', 'Set cursor to line'
    * 2nd row are key combos:
    *   'ctrl-alt-delete', 'ctrl-shift-escape'
    * 3rd row are macros keys:
    *   'P0' - 'P5' execute a script on Windows machines
    * ,-----------------------------------------------------------------------.
    * | ESC | F5   | F9 | F10 | F11 |S+F11|CSF10|NLock|Num7 |Num8 |Num9 | Del |
    * |-----------------------------------------------------------------------|
    * |     |C/A/D|C/S/E| Ins |Print|Pause|SLock|Num0 |Num4 |Num5 |Num6 |Num= |
    * |-----------------------------------------------------------------------|
    * |     | P0  | P1  | P2  | P3  | P4  | P5  |Num. |Num1 |Num2 |Num3 |Num/ |
    * |-----------------------------------------------------------------------|
    * |     |User |     |     |     |     |     |     |Home |PgDn |PgUp | End |
    * `-----------------------------------------------------------------------'
    */
  [1] = KEYMAP_GRID(
       ESC,  F5,   F9,   F10,  F11,  FN30, FN31, NLCK, P7,   P8,   P9,   DEL,
       TRNS, FN16, FN17, INS,  PSCR, PAUS, SLCK, P0,   P4,   P5,   P6,   PEQL,
       TRNS, FN2,  FN3,  FN4,  FN5,  FN6,  FN7,  PDOT, P1,   P2,   P3,   PSLS,
       TRNS, FN8,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, HOME, PGDN, PGUP, END ),

  /* 2: fn right/raise layer
    * ,-----------------------------------------------------------------------.
    * | F1  | F2  | F3  | F4  |F5   | F6  | F7  | F8  | F9  | F10 | F11 | F12 |
    * |-----------------------------------------------------------------------|
    * |     | !   | @   | #   | $   | %   | ^   | &   | *   | -   | +   | =   |
    * |-----------------------------------------------------------------------|
    * |     | _   | '   | "   | `   | ~   | ,   | .   | ]   | )   | }   | >   |
    * |-----------------------------------------------------------------------|
    * |     |NextT|PrevT|     |     |     | Esc |     |Mute |Vol- |Vol+ | P/P |
    * `-----------------------------------------------------------------------'
    */
  [2] = KEYMAP_GRID(
       F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,   F10,  F11,  F12,
       TRNS, FN18, FN19, FN20, FN21, FN22, FN23, FN24, FN25, MINS, FN26, PAST,
       TRNS, FN27, QUOT, FN28, GRV,  FN29, COMM, DOT,  RBRC, FN13, FN14, FN15,
       TRNS, MNXT, MPRV, TRNS, TRNS, TRNS, ESC,  TRNS, MUTE, VOLD, VOLU, MPLY ),
};

enum macro_id {
    M_P0,
    M_P1,
    M_P2,
    M_P3,
    M_P4,
    M_P5,
    M_USERNAME
};

const uint16_t PROGMEM fn_actions[] = {
  [0] = ACTION_LAYER_MOMENTARY(1), // left/lower layer
  [1] = ACTION_LAYER_MOMENTARY(2), // right/raise layer
  // Program macros
  [2] = ACTION_MACRO(M_P0),
  [3] = ACTION_MACRO(M_P1),
  [4] = ACTION_MACRO(M_P2),
  [5] = ACTION_MACRO(M_P3),
  [6] = ACTION_MACRO(M_P4),
  [7] = ACTION_MACRO(M_P5),
  [8] = ACTION_MACRO(M_USERNAME),
  // Braces
  [10] = ACTION_MODS_KEY(MOD_LSFT, KC_9), // (
  [11] = ACTION_MODS_KEY(MOD_LSFT, KC_LBRC), // {
  [12] = ACTION_MODS_KEY(MOD_LSFT, KC_COMMA), // <
  [13] = ACTION_MODS_KEY(MOD_LSFT, KC_0),  // )
  [14] = ACTION_MODS_KEY(MOD_LSFT, KC_RBRC), // }
  [15] = ACTION_MODS_KEY(MOD_LSFT, KC_DOT), // >
  // Combo
  [16] = ACTION_MODS_KEY(MOD_LALT | MOD_LCTL, KC_DEL), // Ctrl+Alt+Delete
  [17] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL, KC_ESC), // Ctrl+Shft+Escape
  // Symbols
  [18] = ACTION_MODS_KEY(MOD_LSFT, KC_1), // !
  [19] = ACTION_MODS_KEY(MOD_LSFT, KC_2), // @
  [20] = ACTION_MODS_KEY(MOD_LSFT, KC_3), // #
  [21] = ACTION_MODS_KEY(MOD_LSFT, KC_4), // $
  [22] = ACTION_MODS_KEY(MOD_LSFT, KC_5), // %
  [23] = ACTION_MODS_KEY(MOD_LSFT, KC_6), // ^
  [24] = ACTION_MODS_KEY(MOD_LSFT, KC_7), // &
  [25] = ACTION_MODS_KEY(MOD_LSFT, KC_8), // *
  [26] = ACTION_MODS_KEY(MOD_LSFT, KC_EQL), // +
  [27] = ACTION_MODS_KEY(MOD_LSFT, KC_MINUS), // _
  [28] = ACTION_MODS_KEY(MOD_LSFT, KC_QUOTE), // "
  [29] = ACTION_MODS_KEY(MOD_LSFT, KC_GRAVE), // ~
  // Debugging
  [30] = ACTION_MODS_KEY(MOD_LSFT, KC_F11), // Step into
  [31] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL, KC_F10), // Set cursor to line
 };

// Run a script and pass a key number to it. This is Windows specific and the script needs to be on your path.
// *open run dialog* keypress.py [PRG_NUM]
#define ADD_PYTHON_PROGRAM_ON_WIN( PRG_NUM )  MACRO( D(LGUI), T(R), U(LGUI), W(100), T(K), T(E), T(Y), T(P), T(R), T(E), T(S), T(S), T(DOT), T(P), T(Y), T(SPC), T(PRG_NUM), END )
// *return*
#define RUN_PYTHON_PROGRAM_ON_WIN MACRO( T(ENT), END )

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    keyevent_t event = record->event;
    switch (id) {
        case M_P0:
            return event.pressed ?
                ADD_PYTHON_PROGRAM_ON_WIN( 0 ) :
                RUN_PYTHON_PROGRAM_ON_WIN;
        case M_P1:
            return event.pressed ?
                ADD_PYTHON_PROGRAM_ON_WIN( 1 ) :
                RUN_PYTHON_PROGRAM_ON_WIN;
        case M_P2:
            return event.pressed ?
                ADD_PYTHON_PROGRAM_ON_WIN( 2 ) :
                RUN_PYTHON_PROGRAM_ON_WIN;
        case M_P3:
            return event.pressed ?
                ADD_PYTHON_PROGRAM_ON_WIN( 3 ) :
                RUN_PYTHON_PROGRAM_ON_WIN;
        case M_P4:
            return event.pressed ?
                ADD_PYTHON_PROGRAM_ON_WIN( 4 ) :
                RUN_PYTHON_PROGRAM_ON_WIN;
        case M_P5:
            return event.pressed ?
                ADD_PYTHON_PROGRAM_ON_WIN( 5 ) :
                RUN_PYTHON_PROGRAM_ON_WIN;
        case M_USERNAME:
            return event.pressed ?
                MACRO( T(N), T(A), T(T), T(H), T(A), T(N), T(R), T(O), T(S), T(S), T(P), T(O), T(W), T(E), T(L), T(L), END ) :
                MACRO_NONE;
    }
    return MACRO_NONE;
}
