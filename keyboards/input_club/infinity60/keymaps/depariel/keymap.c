#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]| Bksp|
     * |-----------------------------------------------------------|
     * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn2|
     * |-----------------------------------------------------------'
     * |Fn2 |Gui |Alt |         Space           |RAlt|Prv|PlPs|Next|
     * `-----------------------------------------------------------'
     */
    [0] = LAYOUT_60_ansi_split_bs_rshift(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,            KC_BSLS,  KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,           KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, LT(5, KC_ENT),
        SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC, MO(4),
        MO(4),   KC_LGUI, KC_LALT,               LT(3, KC_SPC),                 KC_RALT, KC_MPRV, KC_MPLY, KC_MNXT),

    /* Layer 1: "Toggle" off SpaceFn for League of Legends
     */
    [1] = LAYOUT_60_ansi_split_bs_rshift(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS,  KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(4),
        MO(4),   KC_LGUI, KC_LALT,                   KC_SPC,                    KC_RALT, KC_MPRV, KC_MPLY, KC_MNXT),
           
    /* Layer 2: "Toggle" off SpaceFn for MapleRoyals
     */
    [2] = LAYOUT_60_ansi_split_bs_rshift(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS,  KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_LSFT,
        MO(4),   KC_LGUI, KC_LALT,                   KC_SPC,                    KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT),

    /* Layer 3: FN layer 1
     */ 
    [3] = LAYOUT_60_ansi_split_bs_rshift(
        KC_NO,           KC_F1,   KC_F2,   KC_F3,   KC_F4,          KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_NO,
        KC_NO,           KC_BTN1, KC_MS_U, KC_BTN2, LALT(KC_F4),    KC_HOME, KC_PGUP, KC_PSCR, KC_SCRL, KC_UP,   KC_NO,   KC_LPRN, KC_RPRN, KC_DEL,
        MO(6),           KC_MS_L, KC_MS_D, KC_MS_R, KC_NO,          KC_END,  KC_PGDN, KC_TILD, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,
        LGUI(KC_SPC),    KC_NO,   KC_NO,   KC_NO,   KC_NO,          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_CALC, KC_MENU, KC_TRNS, TG(4),
        KC_TRNS,         KC_TRNS, KC_TRNS,                       LT(3, KC_SPC),                KC_TRNS, KC_VOLD, KC_MUTE, KC_VOLU),
    
    /* Layer 4: FN layer 2
     */ 
    [4] = LAYOUT_60_ansi_split_bs_rshift(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_PMNS, KC_PPLS, KC_PSLS, TG(2),
        KC_CAPS, KC_NO,   KC_UP,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_PSCR, KC_NO,   KC_P7,   KC_P8,   KC_P9,   KC_PAST, KC_BSPC,
        KC_LCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_P4,   KC_P5,   KC_P6,   KC_PENT,
        KC_LSFT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_P1,   KC_P2,   KC_P3,   KC_RSFT, MO(4),
        KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                   KC_P0,   KC_PDOT, KC_NO,   TG(1)),
    
    /* Layer 5: FN layer 3
     */ 
    [5] = LAYOUT_60_ansi_split_bs_rshift(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,
        KC_TAB , KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_NO,            KC_TRNS,
        KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_F17,  KC_F18,  KC_F19,  KC_F20,  LT(5, KC_ENT),
        KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                   KC_RALT, KC_NO,   KC_NO,  KC_NO),
    
    /* Layer 6: FN layer 4
     */ 
    [6] = LAYOUT_60_ansi_split_bs_rshift(
        KC_NO,                 KC_NO,            KC_NO,          KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        LCTL(LSFT(KC_TAB)),    KC_NO,            LGUI(KC_UP),    KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        MO(6),                 LGUI(KC_LEFT),    LGUI(KC_DOWN),  LGUI(KC_RGHT),    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_TRNS,               KC_NO,            KC_NO,          KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS,
        KC_TRNS,               KC_TRNS,          KC_TRNS,                   KC_TRNS,                 KC_TRNS, KC_NO,   KC_NO,   KC_NO),
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};
