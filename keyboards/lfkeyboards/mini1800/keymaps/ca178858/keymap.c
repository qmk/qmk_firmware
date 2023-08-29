#include QMK_KEYBOARD_H

enum keymap_layout {
    VANILLA = 0,  // matches MF68 layout
    FUNC,         // 0x08
    SETTINGS,     // 0x10
};

enum {
    TD_ESC_FUNC = 0,
    TD_ESC_CTRL,
    TD_SPC_SPAM
};

// Colors of the layer indicator LED
// This list needs to define layer 0xFFFFFFFF, it is the end of the list, and the unknown layer
const Layer_Info layer_info[] = {
    // Layer     Mask           Red     Green   Blue
    {0x00000000, 0xFFFFFFFF, {0x00, 0xFF, 0x00}}, // base layers - green
    {0x00000002, 0xFFFFFFFE, {0x00, 0x00, 0xFF}}, // function layer - blue
    {0x00000004, 0xFFFFFFFC, {0xFF, 0x00, 0xFF}}, // settings layer - magenta
    {0xFFFFFFFF, 0xFFFFFFFF, {0xFF, 0xFF, 0xFF}}, // unknown layer - REQUIRED - white
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
     * |Ctrl|Gui |Alt |      Space            |ALT |GUI |Func|CTRL |   |Lft| Dn |Rig |
     * `-----------------------------------------------------------'   `-------------'
     */
    [VANILLA] = LAYOUT(
        QK_GESC,         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC,                  KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS,                  KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        TD(TD_ESC_FUNC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,                   KC_P4,   KC_P5,   KC_P6,   LALT(KC_F5),
        KC_LSFT,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                    KC_RSFT,     KC_UP,       KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_LCTL,         KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, KC_RCTL, MO(FUNC),     KC_LEFT, KC_DOWN, KC_RGHT,     KC_P0,   KC_PDOT
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
    [FUNC] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,                        _______, _______, _______, _______,
        XXXXXXX, KC_HOME, KC_UP,   KC_END,  KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       _______, _______, _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,          XXXXXXX,                       _______, _______, _______, _______,
        _______, XXXXXXX, KC_DEL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX,                   TG(SETTINGS),     _______,     _______, _______, _______, _______,
        _______, _______, _______,                            KC_PGDN,                            _______, _______, _______,          _______, _______, _______,     _______, _______
    ),

    /* Keymap SETTINGS: Settings Layer
     * ,-----------------------------------------------------------.     ,-------------.
     * |Esc  |f1| f2| f3| f4|  | f5| f6| f7| f8|   | f9|f10|f11|f12  |  |Prnt|ScLk|Paus|
     * |-------------------------------------------------------------|  |--------------|
     * |FN0 |   |   |   |   |   |   |   |   |  |   |BL-|BL+|BL Togl|    |RGB Tog |Val+|
     * |-----------------------------------------------------------|    |-------------|
     * |MuMode|   |   |   |   |   |   |   |   |   |   |   |  |LEDTst|    |RGB Mode|Val-|
     * |-----------------------------------------------------------|    `-------------'
     * |AudTgl |Hz+|MS+|   |   |   |   |   |   |   |   |   |  RST  |
     * |-----------------------------------------------------------|      ,----.
     * |ClickTgl|Hz-|MS-|   |   |   |   |   |   |   |   |Layer Clr |      |Hue+|
     * |--------------------------------------------------------------------------.
     * |    |    |    |                       |    |    |    |     | |Sat-|Hue-|Sat+|
     * `----------------------------------------------------------------------------'
     */
    [SETTINGS] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BL_DOWN, BL_UP,   BL_TOGG,                  RGB_TOG, RGB_VAI, XXXXXXX, XXXXXXX,
        MU_NEXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                  RGB_MOD, RGB_VAD, XXXXXXX, XXXXXXX,
        AU_TOGG, KC_F1,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          QK_BOOT,                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MU_TOGG, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,     RGB_HUI,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX,     RGB_SAD, RGB_HUD, RGB_SAI,     XXXXXXX, XXXXXXX
    )
};

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
};

void matrix_init_user(void) {
    // This keymap only has a single base layer, so reset the default if needed
    if (eeconfig_read_default_layer() > 1) {
        eeconfig_update_default_layer(1);
        default_layer_set(1);
    }
}
