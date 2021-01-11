// by Matthew Pepers - https://github.com/pepers

/* grid planck layout - modified programmer dvorak
,-----------------------------------------------------------------------------------------------.
| pause |   @   |   |   |   ^   |       |       |       |       |   *   |   #   |   $   |  del  |
|  esc  |  ; :  |  , <  |  . >  |   P   |   Y   |   F   |   G   |   G   |   C   |   R   | bkspc |
|  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |  F7   |  F8   |  F9   |  F10  |  F11  |  F12  |
|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|
|   &   |   /   |   {   |   (   |   [   |   =   |   !   |   ]   |   )   |   }   |   \   |   +   |
|  ` ~  |   A   |   O   |   E   |   U   |   I   |   D   |   H   |   T   |   N   |   S   |  - _  |
|   %   |   7   |   5   |   3   |   1   |   9   |   0   |   2   |   4   |   6   |   8   |   ?   |
|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|
|       |       |       |       |       |       |       |       |       |       |       | prtsc |
|  tab  |  ' "  |   Q   |   J   |   K   |   X   |   B   |   M   |   W   |   V   |   Z   | retrn |
|       |       |       |       |       |       |       |       |       |       |       | insrt |
|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|
|       |       |       |       |       |       |       |       |       |       |       |       |
| lctrl | lgui  | lalt  | ralt  | lower | shift | space | raise | left  | down  |  up   | right |
|       |       |       |       |       |       |       |       | home  | pgdn  | pgup  |  end  |
`-----------------------------------------------------------------------------------------------'
*/

#include "keymap.h"

#define KC_MO1 MO(1)
#define KC_MO2 MO(2)

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* 0: dvorak */
  [0] = KEYMAP_GRID( ESC, SCLN, COMM,  DOT,    P,    Y,    F,    G,    C,    R,    L, BSPC,   \
                     GRV,    A,    O,    E,    U,    I,    D,    H,    T,    N,    S, MINS,   \
                     TAB, QUOT,    Q,    J,    K,    X,    B,    M,    W,    V,    Z,  ENT,   \
                    LCTL, LGUI, LALT, RALT,  MO1, LSFT,  SPC,  MO2, LEFT, DOWN,   UP, RGHT),

  /* 1: lower (FN1) */
  [1] = KEYMAP_GRID( F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,  F10,  F11,  F12,   \
                   FN17,    7,    5,    3,    1,    9,    0,    2,    4,    6,    8, FN18,   \
                   TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,  INS,   \
                   TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, HOME, PGDN, PGUP,  END),

  /* 2: raise (FN2) */
  [2] = KEYMAP_GRID(PAUS, FN19, FN20, FN21, TRNS, TRNS, TRNS, TRNS, FN22, FN23, FN24,  DEL,   \
                    FN10, SLSH, FN11, FN12, LBRC,  EQL, FN13, RBRC, FN14, FN15, BSLS, FN16,   \
                    TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, PSCR,   \
                    TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS),

};

const uint16_t PROGMEM fn_actions[] = {
    // lower row1
    [17] = ACTION_MODS_KEY(MOD_LSFT, KC_5),        // %
    [18] = ACTION_MODS_KEY(MOD_LSFT, KC_SLASH),    // ?
    
    // raise row0
    [19] = ACTION_MODS_KEY(MOD_LSFT, KC_2),        // @
    [20] = ACTION_MODS_KEY(MOD_LSFT, KC_BSLASH),   // |
    [21] = ACTION_MODS_KEY(MOD_LSFT, KC_6),        // ^
    [22] = ACTION_MODS_KEY(MOD_LSFT, KC_8),        // *
    [23] = ACTION_MODS_KEY(MOD_LSFT, KC_3),        // #
    [24] = ACTION_MODS_KEY(MOD_LSFT, KC_4),        // $
    
    // raise row1
    [10] = ACTION_MODS_KEY(MOD_LSFT, KC_7),        // &
    [11] = ACTION_MODS_KEY(MOD_LSFT, KC_LBRACKET), // {
    [12] = ACTION_MODS_KEY(MOD_LSFT, KC_9),        // (
    [13] = ACTION_MODS_KEY(MOD_LSFT, KC_1),        // !
    [14] = ACTION_MODS_KEY(MOD_LSFT, KC_0),        // )
    [15] = ACTION_MODS_KEY(MOD_LSFT, KC_RBRACKET), // }
    [16] = ACTION_MODS_KEY(MOD_LSFT, KC_EQUAL),    // +
};
