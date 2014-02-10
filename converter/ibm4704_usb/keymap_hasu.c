#include "keymap_common.h"


const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: default
     * ,-----------------------------------------------------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|???|BS |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|xxx|Ret |
     * |-----------------------------------------------------------|
     * |Shif|xxx|  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|xxx|Shift |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui|Alt  |         Space             |Alt  |Gui|Ctrl |
     * `-----------------------------------------------------------'
     */
    KEYMAP(
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,GRV, \
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSPC, \
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   FN1, QUOT,NO,  ENT, \
    LSFT,NO,  Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, FN2, NO,  FN0, \
    LCTL,LGUI,LALT,          FN3,                               RGUI,RCTL \
    ),

    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
    CAPS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  PSCR,SLCK,PAUS, UP, NO,  BSPC, \
    LCTL,VOLD,VOLU,MUTE,NO,  NO,  PAST,PSLS,HOME,PGUP,LEFT,RGHT,NO,  ENT, \
    LSFT,NO,  NO,  NO,  NO,  NO,  NO,  PPLS,PMNS,END, PGDN,DOWN,NO,  TRNS, \
    LCTL,LGUI,LALT,          SPC,                               RGUI,RCTL \
    ),

    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
    TAB, NO,  NO,  NO,  NO,  NO,  WH_L,WH_D,WH_U,WH_R,WSTP,WBAK,WFWD,BSPC, \
    LCTL,NO,  ACL0,ACL1,ACL2,NO,  MS_L,MS_D,MS_U,MS_R,TRNS,NO,  NO,  ENT, \
    LSFT,NO,  NO,  NO,  NO,  NO,  BTN3,BTN2,BTN1,BTN4,BTN5,NO,  NO,  RSFT,\
    LCTL,LGUI,LALT,          BTN1,                              RGUI,RCTL \
    ),

    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
    TAB, HOME,PGDN,UP,  PGUP,END, HOME,PGDN,PGUP,END, NO,  NO,  NO,  BSPC, \
    LCTL,NO,  LEFT,DOWN,RGHT,NO,  LEFT,DOWN,UP,  RGHT,NO,  NO,  NO,  ENT, \
    LSFT,NO,  NO,  NO,  NO,  NO,  NO,  HOME,PGDN,PGUP,END, TRNS,NO,  RSFT, \
    LCTL,LGUI,LALT,          SPC,                               RGUI,RCTL \
    ),

    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
    TAB, NO,  NO,  NO,  NO,  NO,  WH_L,WH_D,MS_U,WH_U,WH_R,BTN4,BTN5,FN4, \
    LCTL,VOLD,VOLU,MUTE,NO,  NO,  BTN2,MS_L,MS_D,MS_R,BTN1,NO,  NO,  ENT, \
    LSFT,NO,  NO,  NO,  NO,  NO,  BTN3,BTN2,BTN1,BTN4,BTN5,NO,  NO,  NO, \
    LCTL,LGUI,LALT,          TRNS,                              RGUI,RCTL \
    ),
};

enum macro_id {
    ALT_TAB,
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),
    [1] = ACTION_LAYER_TAP_KEY(2, KC_SCLN),
    [2] = ACTION_LAYER_TAP_KEY(3, KC_SLASH),
    [3] = ACTION_LAYER_TAP_KEY(4, KC_SPC),
    [4] = ACTION_MACRO(ALT_TAB),
};

/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    keyevent_t event = record->event;

    switch (id) {
        case ALT_TAB:
            return (event.pressed ?
                    MACRO( D(LALT), D(TAB), END ) :
                    MACRO( U(TAB), END ));
    }
    return MACRO_NONE;
}
