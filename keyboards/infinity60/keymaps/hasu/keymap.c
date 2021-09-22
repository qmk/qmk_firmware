#include QMK_KEYBOARD_H

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
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
    [0] = LAYOUT_60_ansi_split_bs_rshift(
        KC_ESC,        KC_1,    KC_2,    KC_3,    KC_4,          KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,           KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
        KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,          KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,           KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL,       KC_A,    KC_S,    KC_D,    KC_F,          KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    LT(3, KC_SCLN), KC_QUOT, MT(KC_RCTL, KC_ENT),
        OSM(MOD_LSFT), KC_Z,    KC_X,    KC_C,    KC_V,          KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  LT(2, KC_SLSH), KC_RSFT, TG(1),
        KC_NO,         KC_LGUI, KC_LALT,          LT(4, KC_SPC),                   MO(4),   KC_RGUI, KC_NO,   KC_NO
    ),

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
    [1] = LAYOUT_60_ansi_split_bs_rshift(
        KC_PWR, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
        KC_CAPS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_PSCR,KC_SLCK,KC_PAUS, KC_UP,  KC_TRNS,KC_BSPC,
        KC_LCTL,KC_VOLD,KC_VOLU,KC_MUTE,KC_TRNS,KC_TRNS,KC_PAST,KC_PSLS,KC_HOME,KC_PGUP,KC_LEFT,KC_RGHT,KC_ENT,
        KC_LSFT,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_PPLS,KC_PMNS,KC_END, KC_PGDN,KC_DOWN,KC_RSFT,KC_TRNS,
        KC_TRNS,KC_LGUI,KC_LALT,          KC_TRNS,                      KC_RALT,KC_RGUI,KC_TRNS,KC_TRNS
    ),

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
    [2] = LAYOUT_60_ansi_split_bs_rshift(
        KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,         KC_F11, KC_F12, KC_INS, KC_DEL,
        KC_TAB, KC_HOME,KC_PGDN,KC_UP,  KC_PGUP,KC_END, KC_HOME,KC_PGDN,KC_PGUP,KC_END, KC_NO,          KC_NO,  KC_NO,  KC_BSPC,
        KC_LCTL,KC_NO,  KC_LEFT,KC_DOWN,KC_RGHT,KC_NO,  KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_NO,          KC_NO,  KC_ENT,
        KC_LSFT,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_HOME,KC_PGDN,KC_PGUP,KC_END, LT(2, KC_SLSH), KC_RSFT,KC_TRNS,
        KC_TRNS,KC_LGUI,KC_LALT,          KC_SPC,                       KC_RALT,KC_RGUI,KC_TRNS,        KC_TRNS
    ),

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
    [3] = LAYOUT_60_ansi_split_bs_rshift(
        KC_GRV,       KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,        KC_INS, KC_DEL,
        LALT(KC_TAB), KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_WH_L,KC_WH_D,KC_MS_U,        KC_WH_U,        KC_WH_R,        ALT_T(KC_LEFT), ALT_T(KC_RGHT),LALT(KC_TAB),
        KC_LCTL,      KC_ACL0,KC_ACL1,KC_ACL2,KC_ACL2,KC_NO,  KC_NO,  KC_MS_L,KC_MS_D,        KC_MS_R,        LT(3, KC_SCLN), KC_NO,          KC_ENT,
        KC_LSFT,      KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_BTN3,KC_BTN2,KC_BTN1,ALT_T(KC_LEFT), ALT_T(KC_RGHT), KC_NO,          KC_RSFT,        KC_TRNS,
        KC_TRNS,      KC_LGUI,KC_LALT,          KC_BTN1,                      KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS
    ),

    /* Layer 4: Mouse mode(IJKL)[Space]
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Tab  |   |   |   |   |   |MwL|MwD|McU|MwU|MwR|Wbk|Wfr|Alt-T|
     * |-----------------------------------------------------------|
     * |Contro|VlD|VlU|VlM|   |   |   |McL|McD|McR|Mb1|   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |Mb3|Mb2|Mb1|A/L|A/R|   |Shift |   |
     * `-----------------------------------------------------------'
     *      |Gui |Alt  |          Mb1          |Fn   |Fn |
     *      `--------------------------------------------'
     * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel
     */
    [4] = LAYOUT_60_ansi_split_bs_rshift(
        KC_GRV,       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,          KC_F10,         KC_F11,  KC_F12,  KC_INS,       KC_DEL,
        LALT(KC_TAB), KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_WH_L, KC_WH_D, KC_MS_U, KC_WH_U,        KC_WH_R,        KC_BTN4, KC_BTN5, LALT(KC_TAB),
        KC_LCTL,      KC_VOLD, KC_VOLU, KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_MS_L, KC_MS_D, KC_MS_R,        KC_BTN1,        KC_NO,            KC_ENT,
        KC_LSFT,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_BTN3, KC_BTN2, KC_BTN1, ALT_T(KC_LEFT), ALT_T(KC_RGHT), KC_NO,   KC_RSFT, KC_NO,
        KC_NO,        KC_LGUI, KC_LALT,                   KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};
