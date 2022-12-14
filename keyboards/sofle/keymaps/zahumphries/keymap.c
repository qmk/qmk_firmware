#include QMK_KEYBOARD_H

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
    KC_PRVWD,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND,
    KC_DWORD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * QWERTY
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bspc |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  \   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Esc  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
     * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
     * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |Enter |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | LGUI | LAlt | LCTR |LOWER | /Space  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `-----------------------------------'           '------''---------------------------'
     */

    [_QWERTY] = LAYOUT(
        KC_GRV,  KC_1,  KC_2,  KC_3,   KC_4,  KC_5,                           KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,  KC_W,  KC_E,   KC_R,  KC_T,                           KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_BSLS,
        KC_ESC,  KC_A,  KC_S,  KC_D,   KC_F,  KC_G,                           KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,  KC_X,  KC_C,   KC_V,  KC_B, KC_MUTE,         XXXXXXX, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
             KC_LGUI, KC_LALT, KC_LCTRL, KC_LOWER, KC_SPC,            KC_SPC, KC_RAISE, KC_RCTRL, KC_RALT, KC_RGUI
    ),

    /* LOWER
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | Del  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |  ~   | Home | Pwrd |  Up  | Nwrd |  End |                    |   6  |   7  |   8  |   {  |   }  | F11  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Caps |      | Left | Down | Right|   $  |-------.    ,-------|   ^  |   _  |   +  |   [  |   ]  | F12  |
     * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      | Enter|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | LGUI | LAlt | LCTR |LOWER | / PLAY  /       \ PLAY \  |RAISE | RCTR | RAlt | RGUI |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `-----------------------------------'           '------''---------------------------'
     */
    [_LOWER] = LAYOUT(
        _______, KC_F1,   KC_F2,    KC_F3,   KC_F4,    KC_F5,                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
        KC_TILD, KC_HOME, KC_PRVWD, KC_UP,   KC_NXTWD, KC_END,                     KC_6,    KC_7,    KC_8,    KC_LCBR, KC_RCBR, KC_F11,
        KC_CAPS, _______, KC_LEFT,  KC_DOWN, KC_RGHT,  KC_DLR,                     KC_CIRC, KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_F12,
        _______, _______,  _______,  _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
                        _______, _______, _______, _______, KC_MPLY,          KC_MPLY, _______, _______, _______, _______
    ),
    /* RAISE
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    |      |      |      |      |      | DWord|
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |  `   | Ins  | Pscr | MVUP |      |      |                    |      | PWrd |  Up  | NWrd | DLine| Bspc |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      | MVDN |      | Caps |-------.    ,-------|      |   -  |  =   |   [  |  ]   | Bspc |
     * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
     * |Shift | Undo |  Cut | Copy | Paste|      |-------|    |-------|      | LStr |      | LEnd |      | Shift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | LGUI | LAlt | LCTR |LOWER | / PLAY  /       \ PLAY \  |RAISE | RCTR | RAlt | RGUI |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `-----------------------------------'           '------''---------------------------'
     */
    [_RAISE] = LAYOUT(
        _______, _______, _______, _______,    _______,  _______,                   _______, _______,  _______, _______,  _______,  C(KC_DEL),
        KC_GRV,  KC_INS,  KC_PSCR, A(KC_UP),   _______,  _______,                   _______, KC_PRVWD, KC_UP,   KC_NXTWD, KC_DLINE, _______,
        _______, KC_LALT, KC_LCTL, A(KC_DOWN), _______,  KC_CAPS,                   _______, KC_MINS,  KC_EQL,  _______,  _______,  _______,
        _______, KC_UNDO, KC_CUT,  KC_COPY,    KC_PASTE, _______, _______, _______, _______, KC_LSTRT, _______, KC_LEND,  _______,  _______,
                      _______, _______, _______, _______, KC_MPLY,                KC_MPLY, _______, _______, _______, _______
    ),
    /* ADJUST
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | RESET|      |QWERTY|      |      |      |                    |      |      |      |      |      | F12  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |MACWIN|      |      |      |-------.    ,-------|      |      |      |      |      |      |
     * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | LGUI | LAlt | LCTR |LOWER | / Play  /       \ Play \  |RAISE | RCTR | RAlt | RGUI |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `-----------------------------------'           '------''---------------------------'
     */
    [_ADJUST] = LAYOUT(
        _______, KC_F1,   KC_F2,     KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        RESET,   _______, KC_QWERTY, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_F12,
        _______, _______, CG_TOGG,   _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______,   _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
                    _______, _______, _______,   _______, KC_MPLY,              KC_MPLY, _______, _______, _______, _______
    )
};

#ifdef OLED_DRIVER_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("MODE"), false);
    oled_write_ln_P(PSTR(""), false);
    if (keymap_config.swap_lctl_lgui) {
        oled_write_ln_P(PSTR("MAC"), false);
    } else {
        oled_write_ln_P(PSTR("WIN"), false);
    }

    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_logo();
    } else {
        print_status_narrow();
    }
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case KC_PRVWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_NXTWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_LSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    // CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_LEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    // CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
        case KC_COPY:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_C);
            }
            return false;
        case KC_PASTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_V);
            }
            return false;
        case KC_CUT:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_X);
            }
            return false;
            break;
        case KC_UNDO:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;
    }
    return true;
}

#ifdef ENCODER_ENABLE

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGUP);
        } else {
            tap_code(KC_PGDOWN);
        }
    }
}

#endif
