#include QMK_KEYBOARD_H

enum keymap_layout {
    VANILLA = 0,  // matches MF68 layout
    FUNC,
    SETTINGS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap VANILLA: (Base Layer) Default Layer
     * ,---------.  ,------------------------------------------------------------.  ,---------.
     * | F1 | F2 |  |Esc~| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |  0| - | = |Backspa|  | Ins|PgUp|
     * |---------|  |------------------------------------------------------------|  |---------|
     * | F3 | F4 |  |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  Ret|  | Del|PgDn|
     * |---------|  |--------------------------------------------------------.  |  `---------'
     * | F5 | F6 |  |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  # |  |
     * |---------|  |-----------------------------------------------------------|  ,----.
     * | F7 | F8 |  |Shft| \ |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |  | Up |
     * |---------|  |-------------------------------------------------------------------------.
     * | F9 | F10|  |Ctrl|Win |Alt |      Space            |Alt |Ctrl|Func |    |Lft| Dn |Rig |
     * `---------'  `------------------------------------------------------'    `-------------'
     */
    [VANILLA] = LAYOUT_iso(
        KC_F1,   KC_F2,   QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC,          KC_INS,  KC_PGUP,
        KC_F3,   KC_F4,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_ENT,           KC_DEL,  KC_PGDN,
        KC_F5,   KC_F6,   KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS,
        KC_F7,   KC_F8,   KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           KC_RSFT,          KC_UP,
        KC_F9,   KC_F10,  KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RCTL, MO(FUNC),          KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Keymap FUNCTION: Function Layer
     * ,---------.  ,-------------------------------------------------------------.  ,---------.
     * |    |    |  | ` |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Delete   |  | Ins|Home|
     * |---------|  |-------------------------------------------------------------|  |---------|
     * |    |    |  |Tab  |Hom| Up|End|PgU|   |   |   |   |   |   |   |   |       |  | Del|End |
     * |---------|  |-------------------------------------------------------------|  `---------'
     * |    |    |  |MO(FUNC)|Lft|Dn |Rig|PgD|   |Lft|Dwn| Up|Rgt|   |   |        |
     * |---------|  |-------------------------------------------------------------|  ,----.
     * |    |    |  |Shift   |   |   |   |   |   |   |Mute|V- |V+ |  |TG(SETTINGS)|  | Up |
     * |---------|  |--------------------------------------------------------------------------.
     * |    |    |  |Ctrl|Win |Alt |        PgD            |Alt |Func |CTRL |     |Lft| Dn |Rig |
     * `---------'  `------------------------------------------------------'     `-------------'
     */
    [FUNC] = LAYOUT_iso(
        _______, _______, KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,                _______, KC_HOME,
        _______, _______, XXXXXXX, KC_HOME, KC_UP,   KC_END,  KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,               _______, KC_END,
        _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX,          TG(SETTINGS),          _______,
        _______, _______, _______, _______, _______,                            KC_PGDN,                            _______, _______, _______,               _______, _______, _______
    ),

    /* Keymap SETTINGS: Settings Layer
     * ,---------.  ,-------------------------------------------------------------.  ,-------------.
     * |    |    |  |LayClr|   |   |   |   |   |   |   |   |  |   |BL-|BL+|BL Togl|  |RGB Tog |Val+|
     * |---------|  |-------------------------------------------------------------|  |-------------|
     * |    |    |  |MuMode |   |   |   |   |   |   |   |   |   |   |   |  |LEDTst|  |RGB Mode|Val-|
     * |---------|  |-------------------------------------------------------------|  `-------------'
     * |    |    |  |AudTgl   |Hz+|MS+|   |   |   |   |   |   |   |   |   |  RST  |
     * |---------|  |-------------------------------------------------------------|  ,----.
     * |    |    |  |ClickTgl  |Hz-|MS-|   |   |   |   |MuTgl|  |  |   |Layer Clr |  |Hue+|
     * |---------|  |-------------------------------------------------------------------------.
     * |    |    |  |    |    |    |                         |    |    |     |  |Sat-|Hue-|Sat+|
     * `---------'  `--------------------------------------------------------'  `--------------'
     */
    [SETTINGS] = LAYOUT_iso(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BL_DOWN, BL_UP,   BL_TOGG,          UG_TOGG, UG_VALU,
        XXXXXXX, XXXXXXX, MU_NEXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          UG_NEXT, UG_VALD,
        XXXXXXX, XXXXXXX, AU_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MU_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          UG_HUEU,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX,          UG_SATD, UG_HUED, UG_SATU
    )
};
