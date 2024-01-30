#include QMK_KEYBOARD_H

static void ctrl_plus_key(keyrecord_t *record, uint16_t key);

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _LOWER,
    _RAISE,
};

enum custom_keycodes {
    KC_LOWER = SAFE_RANGE,
    KC_RAISE,
    KC_PRVWD,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND,
    KC_DLINE,
    // USER DEFINED KEYCODES
    KC_QUIT,
    KC_CLOSE,
    KC_REL,
    KC_NTAB,
    KC_ALL,
    KC_SAVE,
    KC_SRCH
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | GESC |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |   -  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |   \  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |   '  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | RAlt | LAlt | Space| / LOWER /       \RAISE \  | Bspc | Home |REFRES| End  |
 *            |      |      |      |      |/       /         \Enter \ |      |      |      |      |
 *            `-----------------------------------'           '------''---------------------------'
 */

[_QWERTY] = LAYOUT(
  QK_GESC,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_MINS,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSLS,
  KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,   KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,     KC_NO, KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
                 KC_LGUI,KC_RALT,KC_LALT, KC_SPC, MO(_LOWER),      LT(_RAISE, KC_ENT), KC_BSPC,  KC_HOME, KC_WREF, KC_END
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |KC_GRV|  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  |  F10 | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  | Quit | Cls  |      | Rld  | Tab  |                    |      |   {  |   }  |   +  |   =  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps | All  | Save |      | Srch |      |-------.    ,-------|      |   (  |   )  |   [  |   ]  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      | Undo | Cut  | Copy | Paste|      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | / LOWER /       \      \  |      |      |      |      |
 *            |      |      |      |      |/  ^^^^^/         \      \ |      |      |      |      |
 *            `-----------------------------------'           '------''---------------------------'
 */
[_LOWER] = LAYOUT(
   KC_GRV,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_F11,  KC_F12,
    KC_F1,  KC_QUIT, KC_CLOSE,_______, KC_REL,  KC_NTAB,                 _______, KC_LCBR, KC_RCBR, KC_PLUS, KC_EQL, _______,
  KC_CAPS,  KC_ALL,  KC_SAVE, _______, KC_SRCH, _______,                 _______, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, _______,
  _______,  KC_UNDO,  KC_CUT, KC_COPY,KC_PASTE, _______, _______,      _______, _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
),
/* RAISE
 * ,----------------------------------------.                     ,-----------------------------------------.
 * |      |      |  /   |  *   |  -   |  +   |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |7/HOME| 8/UP |9/PGUP|      |                    |      | PWrd |  Up  | NWrd | DLine|      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |4/LEFT|  5   |6/RIGT|      |-------.    ,-------|      | Left | Down | Rigth|  Del |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |1/END |2/DOWN|3/PGDN|      |-------|    |-------|      | LStr |      | LEnd |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |0/INS |./DEL |      |ENTER | /NumLock/       \ RAISE\  |      |      |      |      |
 *            |      |      |      |      |/       /         \^^^^^ \ |      |      |      |      |
 *            `-----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT(
  _______, _______,  KC_PSLS,  KC_PAST,  KC_PMNS, KC_PPLS,                       _______,  _______, _______,  _______,  _______, _______,
  _______, _______,  KC_KP_7,  KC_KP_8,  KC_KP_9, _______,                       KC_PGUP, KC_PRVWD,   KC_UP, KC_NXTWD, KC_DLINE, _______,
  _______, _______,  KC_KP_4,  KC_KP_5,  KC_KP_6, _______,                       KC_PGDN,  KC_LEFT, KC_DOWN,  KC_RGHT,   KC_DEL, _______,
  _______, _______,  KC_KP_1,  KC_KP_2,  KC_KP_3, _______,  _______,       _______, _______, KC_LSTRT, _______,  KC_LEND,  _______, _______,
                        KC_KP_0, KC_PDOT, _______, KC_PENT,  KC_NUM,       _______, _______, _______,  _______,  _______
)
};

#ifdef OLED_ENABLE

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

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Qwrt"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
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
                     //CMD-arrow on Mac, but we have CTL and GUI swapped
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
                    //CMD-arrow on Mac, but we have CTL and GUI swapped
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
        case KC_DLINE:
            ctrl_plus_key(record, KC_BSPC);
            break;
        case KC_COPY:
            ctrl_plus_key(record, KC_C);
            return false;
        case KC_PASTE:
            ctrl_plus_key(record, KC_V);
            return false;
        case KC_CUT:
            ctrl_plus_key(record, KC_X);
            return false;
        case KC_UNDO:
            ctrl_plus_key(record, KC_Z);
            return false;
        // USER DEFINED CODES NOT INCLUDED IN DEFAULT CONFIG
        case KC_QUIT:
            ctrl_plus_key(record, KC_Q);
            return false;
        case KC_CLOSE:
            ctrl_plus_key(record, KC_W);
            return false;
        case KC_REL:
            ctrl_plus_key(record, KC_R);
            return false;
        case KC_NTAB:
            ctrl_plus_key(record, KC_T);
            return false;
        case KC_ALL:
            ctrl_plus_key(record, KC_A);
            return false;
        case KC_SAVE:
            ctrl_plus_key(record, KC_S);
            return false;
        case KC_SRCH:
            ctrl_plus_key(record, KC_F);
            return false;
    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}

#endif

static void ctrl_plus_key(keyrecord_t *record, uint16_t key) {
    if (record->event.pressed) {
        register_mods(mod_config(MOD_LCTL));
        register_code(key);
    } else {
        unregister_mods(mod_config(MOD_LCTL));
        unregister_code(key);
    }
    return;
}
