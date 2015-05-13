#include "keymap_common.h"


const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Default Layer: plain keymap
     * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.             ,---.
     * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|             |   |
     * `---'   `---------------' `---------------' `---------------' `-----------'             `---'
     * ,-----------------------------------------------------------. ,-----------. ,---------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backspa| |Ins|Hom|PgU| |NmL|  =|  /|  *|
     * |-----------------------------------------------------------| |-----------| |---------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  Fn0| |Del|End|PgD| |  7|  8|  9|  -|
     * |-----------------------------------------------------------| `-----------' |---------------|
     * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |               |  4|  5|  6|  +|
     * |-----------------------------------------------------------|     ,---.     |---------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |     |Up |     |  1|  2|  3|   |
     * |-----------------------------------------------------------| ,-----------. |-----------|Ent|
     * |Ctrl |Gui |Alt |         Space             |Alt |Gui |Ctrl | |Lef|Dow|Rig| |      0|  .|   |
     * `-----------------------------------------------------------' `-----------' `---------------'
     */
    KEYMAP_EXT_ANSI(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,                    NO,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,    NLCK,EQL, PSLS,PAST,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,FN0,      DEL, END, PGDN,    P7,  P8,  P9,  PMNS,
    LCAP,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                               RGUI,RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* Default Layer: plain keymap
     * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.             ,---.
     * |`  |   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|             |   |
     * `---'   `---------------' `---------------' `---------------' `-----------'             `---'
     * ,-----------------------------------------------------------. ,-----------. ,---------------.
     * |Esc|F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Delete | |Ins|Hom|PgU| |NmL|Mb1|Mb2|Mb3|
     * |-----------------------------------------------------------| |-----------| |---------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|PrS|ScL|Pau|Up |Ins|  Fn0| |Del|End|PgD| |MwD|McU|MwU|MwD|
     * |-----------------------------------------------------------| `-----------' |---------------|
     * |CapsLo|VoD|VoU|Mut|  F|  G|  H|  J|Hom|PgU|Lef|Rig|Return  |               |McL|McD|McR|MwU|
     * |-----------------------------------------------------------|     ,---.     |---------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|End|PgD|Dow|Shift     |     |PgU|     |MwL|McD|MwR|   |
     * |-----------------------------------------------------------| ,-----------. |-----------|Mb3|
     * |Ctrl |Gui |Alt |         Space             |Alt |Gui |Ctrl | |Hom|PgD|End| |    Mb1|Mb2|   |
     * `-----------------------------------------------------------' `-----------' `---------------'
     */
    KEYMAP_EXT_ANSI(
    GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,                    NO, 
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,      INS, HOME,PGUP,    NLCK,BTN1,BTN2,BTN3,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   PSCR,SLCK,PAUS,UP,  INS, FN0,      DEL, END, PGDN,    WH_D,MS_U,WH_U,WH_D,
    LCAP,VOLD,VOLU,MUTE,F,   G,   H,   J,   HOME,PGUP,LEFT,RGHT,     ENT,                         MS_L,MS_D,MS_R,WH_U,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   END, PGDN,DOWN,          RSFT,          PGUP,         WH_L,MS_D,WH_R,
    LCTL,LGUI,LALT,          SPC,                               RGUI,RCTL,     HOME,PGDN,END,     BTN1,     BTN2,BTN3
    ),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_TAP_KEY(1, KC_BSLS),
};
