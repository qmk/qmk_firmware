#include QMK_KEYBOARD_H

enum keymap_layout {
    VANILLA = 0,  // matches MF68 layout
    CS_GO,        // 0x08
    FUNC,         // 0x10
    SETTINGS,     // 0x20
};

enum {
    TD_ESC_FUNC = 0,
    TD_ESC_CTRL,
    TD_SPC_SPAM
};

bool spam_space = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap BASE: (Base Layer) Default Layer
     * ,---------.  ,------------------------------------------------------------.  ,---------.
     * |Vol-|Vol+|  |Esc~| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |  0| - | = |Backspa|  | Ins|PgUp|
     * |---------|  |------------------------------------------------------------|  |---------|
     * | F3 | F4 |  |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     \|  | Del|PgDn|
     * |---------|  |------------------------------------------------------------|  `---------'
     * | F5 | F6 |  |Control |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
     * |---------|  |------------------------------------------------------------|  ,----.
     * | F7 | F8 |  |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|  Shift    |  | Up |
     * |---------|  |-------------------------------------------------------------------------.
     * | F9 | F10|  |Func|Alt |Cmd |      Space            |Cmd |Alt |Func |    |Lft| Dn |Rig |
     * `---------'  `------------------------------------------------------'    `-------------'
     */
    [VANILLA] = LAYOUT_split_rshift(
        KC_VOLD, KC_VOLU, QK_GESC,         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,       KC_BSPC,            LALT(KC_F5), KC_PGUP,
        KC_F3,   KC_F4,   KC_TAB,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,      KC_BSLS,            KC_DEL,      KC_PGDN,
        KC_F5,   KC_F6,   TD(TD_ESC_FUNC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,               KC_ENT,
        KC_F7,   KC_F8,   KC_LSFT,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,      MO(CS_GO),          KC_UP,
        KC_F9,   KC_F10,  KC_LCTL,         KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, KC_RCTL, MO(FUNC),                KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [CS_GO] = LAYOUT_split_rshift(
        _______, _______, QK_GESC,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,            _______,     _______,
        _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,            _______,     _______,
        _______, _______, KC_LCTL,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,               _______,
        _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                          _______,
        _______, _______, _______,         _______, _______,                            _______,                            _______, _______, _______,                 _______, _______, _______
    ),

    /* Keymap FUNCTION: Function Layer
     * ,---------.  ,-------------------------------------------------------------.  ,---------.
     * | V- | V+ |  | ` |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Delete   |  | Ins|Home|
     * |---------|  |-------------------------------------------------------------|  |---------|
     * |    |    |  |Tab  |   |PgU|   |   |   |   |   | Up|   |   |   |   |       |  | Del|End |
     * |---------|  |-------------------------------------------------------------|  `---------'
     * |    |    |  |Control|Hme|PgD|End|   |   |   |Lft|Dwn|Rgt|   |   |         |
     * |---------|  |-------------------------------------------------------------|  ,----.
     * |    |    |  |Shift   |   |Del|   |   |   |   |Mute|V- |V+ |  |TG(SETTINGS)|  | Up |
     * |---------|  |--------------------------------------------------------------------------.
     * |    | F10|  |Func|Win |Alt |        PgD           |Alt |Ctrl |Func |     |Lft| Dn |Rig |
     * `---------'  `------------------------------------------------------'     `-------------'
     */
    [FUNC] = LAYOUT_split_rshift(
        _______, _______, KC_GRV,          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,       KC_DEL,             TO(CS_GO),   KC_HOME,
        _______, _______, XXXXXXX,         KC_PGUP, KC_UP,   KC_PGDN, KC_HOME, XXXXXXX, XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,            _______,     KC_END,
        _______, _______, _______,         KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,               XXXXXXX,
        _______, _______, _______,         XXXXXXX, KC_DEL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX,          TG(SETTINGS), XXXXXXX,            _______,
        _______, _______, _______,         _______, _______,                            KC_PGDN,                            _______, _______, _______,                 _______, _______, _______
    ),

    /* Keymap SETTINGS: Settings Layer
     * ,---------.  ,-----------------------------------------------------------.  ,-------------.
     * |    |    |  |FN0 |BL0|BL1|BL2|BL3|   |   |   |   |  |   |BL-|BL+|BL Togl|  |RGB Tog |Val+|
     * |---------|  |-----------------------------------------------------------|  |-------------|
     * |    |    |  |Debug|   |   |   |   |   |   |   |   |   |   |   |  |RGBTst|  |RGB Mode|Val-|
     * |---------|  |-----------------------------------------------------------|  `-------------'
     * |    |    |  |LayrClr|Hz+|MS+|   |   |   |   |   |   |   |   |   |  RST  |
     * |---------|  |-----------------------------------------------------------|  ,----.
     * |    |    |  |ClickTgl|Hz-|MS-|   |   |   |   |   |   |   |   |Layer Clr |  |Hue+|
     * |---------|  |------------------------------------------------------------------------.
     * |    |    |  |    |    |    |      Print Debug      |    |    |     |  |Sat-|Hue-|Sat+|
     * `---------'  `------------------------------------------------------'  `--------------'
     */
    [SETTINGS] = LAYOUT_split_rshift(
        XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BL_DOWN, BL_UP,        BL_TOGG,            RGB_TOG,     RGB_VAI,
        XXXXXXX, XXXXXXX, DB_TOGG,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,            RGB_MOD,     RGB_VAD,
        XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,               QK_BOOT,
        XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,      XXXXXXX,            RGB_HUI,
        XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX,                 RGB_SAD, RGB_HUD, RGB_SAI
    )
};

void tap_space_spam_finished(tap_dance_state_t *state, void *user_data) {
    if (get_mods() & (MOD_BIT(KC_LGUI))) {
      return;
    }
    if (state->pressed) {
        spam_space = true;
    }
    tap_code(KC_SPC);
}

void tap_space_spam_reset(tap_dance_state_t *state, void *user_data) {
    spam_space = false;
    unregister_code(KC_SPC);
}

void tap_esc_func_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        layer_on(FUNC);
    } else {
        tap_code(KC_ESC);
    }
}

void tap_esc_func_reset(tap_dance_state_t *state, void *user_data) {
    layer_off(FUNC);
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_FUNC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_esc_func_finished, tap_esc_func_reset),
    [TD_SPC_SPAM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_space_spam_finished, tap_space_spam_reset),
};

void matrix_scan_user(void) {
    if (spam_space && !(get_mods() & (MOD_BIT(KC_LGUI)))) {
        tap_code(KC_SPC);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if ((layer_state & (1 << CS_GO)) && (keycode == 44)) {
        if (get_mods() & (MOD_BIT(KC_LGUI))) {
            return false;
        }
    }
    return true;
}
