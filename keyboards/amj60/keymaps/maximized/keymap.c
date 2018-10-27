
#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DEF 0
#define _SPC 1

// dual-role shortcuts
#define SPACEDUAL LT(_SPC, KC_SPACE)


// increase readability 
#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _DEF: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| \ | ~ |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]| bspc|
     * |-----------------------------------------------------------|
     * |Caps   | A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| Return |
     * |-----------------------------------------------------------|
     * |Sft | Fn0|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| Sft |Fn2|
     * |-----------------------------------------------------------|
     * |Ctrl|Win |Alt |      Space/Fn0         |Alt |Win |Menu|RCtl|
     * `-----------------------------------------------------------'
     */
    [_DEF] = LAYOUT_max(
        KC_ESC,   KC_1,    KC_2,    KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,    KC_0,    KC_MINS, KC_EQL, KC_BSLS, KC_GRV, \
        KC_TAB,   KC_Q,    KC_W,    KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,    KC_P,    KC_LBRC, KC_RBRC,    KC_BSPC,  \
        KC_CAPS,  KC_A,    KC_S,    KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT, KC_ENT,   \
        KC_LSFT,  F(0),    KC_Z,    KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,    F(1),     \
        KC_LCTL,  KC_LALT, KC_LGUI,             SPACEDUAL,                       KC_RGUI, KC_RALT, KC_RCTL,    F(2)),

    /* Keymap 1: F-and-vim Layer, modified with Space (by holding space)
     * ,-----------------------------------------------------------.
     * |PrSc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|   |  |
     * |-----------------------------------------------------------|
     * |    |Paus| Up| [ | ] |   |   |   | ( | ) |   |   |   | Del |
     * |-----------------------------------------------------------|
     * |      |Lft|Dwn|Rgt|   |   |Left|Down|Right|Up|  |   | PLAY |
     * |-----------------------------------------------------------|
     * |    |   |   |   | < | > |   |M0 |   |   |   |   | Vol+ |   |
     * |-----------------------------------------------------------|
     * |    |    |    |                        |Alt |Prev|Vol-|Next|
     * `-----------------------------------------------------------'
     */
    [_SPC] = LAYOUT_max(
        KC_PSCR, KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,    KC_F7,     KC_F8,     KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,  \
        _______, KC_PAUS, KC_UP,   _______,  _______, _______, _______,  _______, _______, _______, _______, _______, _______, KC_DEL, \
        _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, KC_LEFT,  KC_DOWN,   KC_UP,     KC_RGHT, _______, _______, KC_MPLY, \
        _______, _______, _______, _______,  _______, _______, KC_SPACE, M(0),      _______,   _______, _______, _______, KC_VOLU, _______, \
        _______, _______, _______,                                  _______,                                 _______, KC_MPRV, KC_VOLD, KC_MNXT),

};
