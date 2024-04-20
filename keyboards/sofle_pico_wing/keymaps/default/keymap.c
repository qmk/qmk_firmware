 // Copyright 2023 QMK
 // SPDX-License-Identifier: GPL-2.0-or-later

 #include QMK_KEYBOARD_H

 // const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 // LAYOUT(
 //     KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,     KC_7,     KC_8,    KC_9,    KC_0,    KC_GRV,
 //     KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,     KC_U,     KC_I,    KC_O,    KC_P,    KC_BSPC,
 //     KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                       KC_H,     KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT,
 //     KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,   KC_MPLY,KC_N,     KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
 //                       KC_LCTL, KC_LGUI, KC_LCMD, KC_LALT, KC_ENT,    KC_SPC, KC_RALT,  KC_RCMD,  KC_RGUI, KC_RCTL
 // )
 // };

 enum sofle_layers {
     _QWERTY,
     _LOWER,
     _RAISE,
     _ADJUST
 };

 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     // clang-format off
         /*
         * QWERTY
         * ,-----------------------------------------.                    ,-----------------------------------------.
         0 |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
         * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
         1 | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
         * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
         2 | Tab  |   A  |   S  |   D  |   F  |   G  |-------     ------- |   H  |   J  |   K  |   L  |   ;  |  '   |
         * |------+------+------+------+------+------|      |     |       |------+------+------+------+------|------|
         3 |LShift|   Z  |   X  |   C  |   V  |   B  |      |     |       |   N  |   M  |   ,  |   .  |   /  |RShift|
         * `-----------------------------------------/ ---- /     \ ---- \-----------------------------------------'
                         | LGUI | LAlt | LCTR |LOWER / Enter/       \Space \RAISE| RCTR | RAlt | RGUI |
         *            `----------------------------------'            '------''---------------------------'
         */
         [_QWERTY] = LAYOUT(
         QK_GESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  @,
         KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC,
         KC_LSFT,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT,
         KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
         KC_LGUI,  KC_LALT,KC_LCTL, MO(_LOWER), KC_SPC, XXXXXXX, XXXXXXX,  KC_ENT, MO(_RAISE), XXXXXXX, XXXXXXX, KC_MENU
        )
 		/* LOWER;
         * ,-----------------------------------------.                    ,-----------------------------------------.
         * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
         * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
         * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
         * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
         * | Tab  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   |  |
         * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
         * | Shift|  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   ;  |   :  |   \  | Shift|
         * `-----------------------------------------/       /     \      \-----------------------------------------'
         *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
         *            |      |      |      |      |/       /         \      \ |      |      |      |      |
         *            `----------------------------------'           '------''---------------------------'
         */
         [_LOWER] = LAYOUT(
         _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
         KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_F12,
         _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
         _______,  KC_EQL, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______, _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN,
         KC_BSLS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
         ),
         /* RAISE
         * ,----------------------------------------.                    ,-----------------------------------------.
         * |      |      |      |      |RGBSAI|RGBSAD|                    |RGSWRL| RGSNK |Debug|RGBMOD|RGBRMOD|      |
         * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
         * | Esc  | Ins  | Pscr | Menu |RGBVAI|RGBTOG|                    |      | PWrd |  Up  | NWrd | DLine| Bspc |
         * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
         * | Tab  | LAt  | LCtl |LShift|RGBVAD| Caps |-------.    ,-------|      | Left | Down | Rigth|  Del | Bspc |
         * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
         * |Shift | Undo |  Cut | Copy | Paste|      |-------|    |-------|      | LStr |      | LEnd |      | Shift|
         * `-----------------------------------------/       /     \      \-----------------------------------------'
         *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
         *            |      |      |      |      |/       /         \      \ |      |      |      |      |
         *            `----------------------------------'           '------''---------------------------'
         */
         [_RAISE] = LAYOUT(
         _______, _______, _______, _______, RGB_SAI, RGB_SAD,RGB_M_SW, RGB_M_SN,DB_TOGG, RGB_MOD,RGB_RMOD, _______,
         _______, KC_INS, KC_PSCR, KC_APP , RGB_VAI, RGB_TOG, KC_PGUP, _______,   KC_UP, _______, KC_DLINE, KC_BSPC,
         _______, KC_LALT, KC_LCTL, KC_LSFT, RGB_VAD, KC_CAPS, KC_PGDN,  KC_LEFT,KC_DOWN, KC_RGHT,  KC_DEL, KC_BSPC,
         _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PASTE,XXXXXXX, _______, _______, XXXXXXX, _______, XXXXXXX, KC_BEEP,
         XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
         ),
         /* ADJUST
         * ,-----------------------------------------.                    ,-----------------------------------------.
         * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
         * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
         * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
         * |QK_BOOT|     |QWERTY|      |      |      |                    |      |      |      |      |      |      |
         * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
         * |  DBG    |      |MACWIN|      |      |   |-------.    ,-------|      | VOLDO| MUTE | VOLUP|      |      |
         * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
         * |  MAKE    |      |      |      |      |   |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
         * `-----------------------------------------/       /     \      \-----------------------------------------'
         *            |Reboot| LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
         *            |      |      |      |      |/       /         \      \ |      |      |      |      |
         *            `----------------------------------'           '------''---------------------------'
         */
         [_ADJUST] = LAYOUT(
         XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
         QK_BOOT , XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
         DB_TOGG  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
         QK_MAKE , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT,
         QK_RBT , XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
         )
         // clang-format on
 };

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}, [1] = {ENCODER_CCW_CW(RGB_MOD, RGB_RMOD)},
    [2] = {ENCODER_CCW_CW(_______, _______)}, [3] = {ENCODER_CCW_CW(_______, _______)}
    //, [4] = {ENCODER_CCW_CW(_______, _______)},
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    //uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    ppppppuprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
  return true;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 3:
                rgb_matrix_set_color(i, RGB_RED);
                break;
            case 2:
                rgb_matrix_set_color(i, RGB_BLUE);
                break;
            case 1:
                rgb_matrix_set_color(i, RGB_YELLOW);
                break;
            default:
                break;
        }
    }
    return false;
}
