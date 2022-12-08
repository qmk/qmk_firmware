#include QMK_KEYBOARD_H

enum keymap_layout {
    VANILLA = 0,  // matches MF68 layout
    DEFAULT_WKL,  // 0x02 Function in CapsLock location, gui key disabled
    DEFAULT_OSX,  // 0x04 Function in CapsLock location, gui/alt swapped for OSX
    CS_GO,        // 0x08 Function in CapsLock location, gui/alt swapped for OSX
    FUNC,         // 0x10
    SETTINGS,     // 0x20
};

enum {
    TD_ESC_FUNC = 0,
};

// Colors of the layer indicator LED
// This list needs to define layer 0xFFFFFFFF, it is the end of the list, and the unknown layer
const Layer_Info layer_info[] = {
    // Layer     Mask           Red     Green   Blue
    {0x00000000, 0xFFFFFFF8, {0x00, 0xFF, 0x00}}, // base layers (VANILLA, DEFAULT_WKL, DEFAULT_OSX) - green
    {0x00000008, 0xFFFFFFF8, {0x07FF, 0x07FF, 0x0000}}, // CSGO layer - orange
    {0x00000010, 0xFFFFFFF0, {0x0000, 0x0000, 0x0FFF}}, // function layer - blue
    {0x00000020, 0xFFFFFFE0, {0x0FFF, 0x0000, 0x0FFF}}, // settings layer - magenta
    {0xFFFFFFFF, 0xFFFFFFFF, {0x0FFF, 0x0FFF, 0x0FFF}}, // unknown layer - REQUIRED - white
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap VANILLA: (Base Layer) Default Layer
     * ,-----------------------------------------------------------------------------.
     * |Esc  |f1| f2| f3| f4|  | f5| f6| f7| f8|   | f9|f10|f11|f12|  |Prnt|ScLk|Paus|
     * |-----------------------------------------------------------|  |--------------|
     * | ~ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |  0| - | = |Backsp |  | Ins|Home|PgUp|
     * |-----------------------------------------------------------|  |--------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  | Del| End|PgDn|
     * |-----------------------------------------------------------|  `--------------'
     * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
     * |-----------------------------------------------------------|        ,----.
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |        | Up |
     * |-----------------------------------------------------------|   ,-------------.
     * |Ctrl|Gui |Alt |      Space            |ALT |GUI |CTRL |Func|   |Lft| Dn |Rig |
     * `-----------------------------------------------------------'   `-------------'
     */
    [VANILLA] = LAYOUT_tkl_ansi(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_0,    KC_1,     KC_2,              KC_3,    KC_4,    KC_5,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC,           KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS,           KC_DEL,  KC_END,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                    KC_RSFT,                    KC_UP,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, KC_RCTL, MO(FUNC), MO(SETTINGS),      KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Keymap DEFAULT_TKL: (Base Layer) Default Layer
     * ,-----------------------------------------------------------------------------.
     * |Esc  |f1| f2| f3| f4|  | f5| f6| f7| f8|   | f9|f10|f11|f12|  |Prnt|ScLk|Paus|
     * |-----------------------------------------------------------|  |--------------|
     * | ~ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |  0| - | = |Backsp |  | Ins|Home|PgUp|
     * |-----------------------------------------------------------|  |--------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  | Del| End|PgDn|
     * |-----------------------------------------------------------|  `--------------'
     * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
     * |-----------------------------------------------------------|       ,----.
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |       | Up |
     * |-----------------------------------------------------------|   ,-------------.
     * |Ctrl|    |Alt |      Space            |ALT |    |CTRL |Func|   |Lft| Dn |Rig |
     * `-----------------------------------------------------------'   `-------------'
     */
    [DEFAULT_WKL] = LAYOUT_tkl_ansi(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,        KC_PSCR, KC_SCRL, KC_PAUS,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,       KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,       KC_DEL,  KC_END,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,                KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, KC_RCTL, MO(FUNC),      KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Keymap DEFAULT_OSX: (Base Layer) Default Layer
     * ,-----------------------------------------------------------------------------.
     * |Esc  |f1| f2| f3| f4|  | f5| f6| f7| f8|   | f9|f10|f11|f12|  |Prnt|ScLk|Paus|
     * |-----------------------------------------------------------|  |--------------|
     * | ~ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |  0| - | = |Backsp |  | Ins|Home|PgUp|
     * |-----------------------------------------------------------|  |--------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  | Del| End|PgDn|
     * |-----------------------------------------------------------|  `--------------'
     * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
     * |-----------------------------------------------------------|        ,----.
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |        | Up |
     * |-----------------------------------------------------------|   ,-------------.
     * |Ctrl| Opt |Cmd |      Space           |Cmd |Opt |CTRL |Func|   |Lft| Dn |Rig |
     * `-----------------------------------------------------------'   `-------------'
     */
    [DEFAULT_OSX] = LAYOUT_tkl_ansi(
        KC_ESC,                   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,             KC_SCRL, KC_PAUS, LALT(KC_F5),
        KC_GRV,          KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC,            KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS,            KC_DEL,  KC_END,  KC_PGDN,
        TD(TD_ESC_FUNC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,
        KC_LSFT,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                    KC_RSFT,                     KC_UP,
        KC_LCTL,         KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, KC_RCTL, MO(FUNC), MO(SETTINGS),       KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [CS_GO] = LAYOUT_tkl_ansi(
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______,
        KC_LCTL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,               _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______,      _______, _______, _______
    ),

    /* Keymap FUNCTION: Function Layer
     * ,-------------------------------------------------------------.  ,--------------.
     * |Esc  |f1| f2| f3| f4|  | f5| f6| f7| f8|   | f9|f10|f11|f12  |  |Prnt|ScLk|Paus|
     * |-------------------------------------------------------------|  |--------------|
     * | ` |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Delete   |  |    |    |    |
     * |-------------------------------------------------------------|  |--------------|
     * |Tab  |   |PgU|   |   |   |   |   | Up|   |   |   |   |       |  |    |    |    |
     * |-------------------------------------------------------------|  `--------------'
     * |Control|Hme|PgD|End|   |   |   |Lft|Dwn|Rgt|   |   |         |
     * |-------------------------------------------------------------|       ,----.
     * |Shift   |   |Del|   |   |   |   |Mute|V- |V+ |  |TG(SETTINGS)|       | Up |
     * |-------------------------------------------------------------'   ,-------------.
     * |Func|Win |Alt |        PgD           |Alt |Ctrl |Func |          |Lft| Dn |Rig |
     * `------------------------------------------------------'          `-------------'
     */
    [FUNC] = LAYOUT_tkl_ansi(
        KC_ESC,           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           KC_PSCR,   KC_SCRL, KC_PAUS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,            TO(CS_GO), _______, _______,
        XXXXXXX, KC_PGUP, KC_UP,   KC_PGDN, KC_HOME, XXXXXXX, XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           _______,   _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,          XXXXXXX,
        _______, XXXXXXX, KC_DEL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX,                   TG(SETTINGS),                 _______,
        _______, _______, _______,                            KC_PGDN,                            _______, _______, _______, _______,             _______, _______, _______
    ),

    /* Keymap SETTINGS: Settings Layer
     * ,-----------------------------------------------------------.     ,-------------.
     * |Esc  |f1| f2| f3| f4|  | f5| f6| f7| f8|   | f9|f10|f11|f12  |  |Prnt|ScLk|Paus|
     * |-------------------------------------------------------------|  |--------------|
     * |LayClr|   |   |   |   |   |   |   |   |  |   |BL-|BL+|BL Togl|    |RGB Tog |Val+|
     * |-----------------------------------------------------------|    |-------------|
     * |Debug|   |   |   |   |   |   |   |   |   |   |   |  |LEDTst|    |RGB Mode|Val-|
     * |-----------------------------------------------------------|    `-------------'
     * |AU_TOGG|Hz+|MS+|   |   |   |   |   |   |   |   |   |  RST  |
     * |-----------------------------------------------------------|  ,----.
     * |ClickTgl|Hz-|MS-|   |   |   |   |   |   |   |   |Layer Clr |  |Hue+|
     * |------------------------------------------------------------------------.
     * |    |    |    |      Print Debug      |    |    |     |  |Sat-|Hue-|Sat+|
     * `------------------------------------------------------'  `--------------'
     */
    [SETTINGS] = LAYOUT_tkl_ansi(
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BL_DOWN,      XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BL_DOWN, BL_UP,   BL_TOGG,      RGB_TOG, RGB_VAI, XXXXXXX,
        MU_NEXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      RGB_MOD, RGB_VAD, XXXXXXX,
        AU_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          QK_BOOT,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MU_TOGG, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,               RGB_HUI,
        XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, _______,      RGB_SAD, RGB_HUD, RGB_SAI
    )
};

void tap_esc_func_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        layer_on(FUNC);
    } else {
        tap_code(KC_ESC);
    }
}

void tap_esc_func_reset(qk_tap_dance_state_t *state, void *user_data) {
    layer_off(FUNC);
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_FUNC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_esc_func_finished, tap_esc_func_reset),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if ((layer_state & (1 << CS_GO)) && (keycode == 44)) {
        if (get_mods() & (MOD_BIT(KC_LGUI))) {
            return false;
        }
    }
    return true;
}
