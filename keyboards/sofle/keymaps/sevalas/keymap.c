#include "transactions.h"

#include QMK_KEYBOARD_H

static uint16_t last_keycode[OLED_LAST_KEYCODE_SIZE] = {KC_NO};
static char oled_keylog_str[OLED_KEYLOGGER_SIZE + 1] = {0};

static const char PROGMEM code_to_name[256] = {0,0,0,0,'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0',0,0,0,0,0,'-','=','[',']','\\','#',';','\'','`',',','.','/',0,0,0,0,0,'P','S',0,' ',0,0,' ',' ',0,0,0,0,0,0,0,0,' ',' ',' ',' ',' ',' ',' ',0,0,0,0,0,0,0x9E,0x9E,' ',' ',' ',' ',' ',' ',' ',0x80,0x80,0x80,0x80,0x80,0x81,0x82,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,'C','S','A','G','C','S','A','G',' ',0,0,0,0,0,0,0,0,'C',0,0,0,0,0,'N',0,' ',0,0,' ',0,0x9E,0x9E,0,0,' ',' ',' ',' ',0x80,0x80,0x80,0x80,0x80,0x81,0x82,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,' ',' ',' ',0,0,0,0,0,' ',0,0,0,0,0,0,0,0,0
};

static inline void copy_last_keycode(uint8_t size, const void *buffer) {
    memcpy(last_keycode, buffer, size);
}

static inline void copy_oled_keylog(uint8_t size, const void *buffer) {
    memcpy(oled_keylog_str, buffer, size);
}

void keycode_sync(uint8_t size, const void *buffer, uint8_t target_size, void *target_buffer) {
    copy_last_keycode(size, buffer);
}

void keylogger_string_sync(uint8_t size, const void *buffer, uint8_t target_size, void *target_buffer) {
    copy_oled_keylog(size, buffer);
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(RPC_ID_USER_LAST_KEYCODE, keycode_sync);
    transaction_register_rpc(RPC_ID_USER_OLED_KEYLOG_STR, keylogger_string_sync);
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        bool needs_sync = false;
        static char keylog_temp[OLED_KEYLOGGER_SIZE + 1] = {0};
        uint16_t last_keycode_temp[OLED_LAST_KEYCODE_SIZE] = {KC_NO};

        if (memcmp(oled_keylog_str, keylog_temp, OLED_KEYLOGGER_SIZE + 1) != 0) {
            needs_sync = true;
            memcpy(keylog_temp, oled_keylog_str, OLED_KEYLOGGER_SIZE + 1);
        }
        if (memcmp(last_keycode, last_keycode_temp, OLED_LAST_KEYCODE_SIZE * sizeof(uint16_t)) != 0) {
            needs_sync = true;
            memcpy(last_keycode_temp, last_keycode, OLED_LAST_KEYCODE_SIZE * sizeof(uint16_t));
        }

        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_USER_OLED_KEYLOG_STR, OLED_KEYLOGGER_SIZE + 1, oled_keylog_str)) {
                wait_ms(10);
                transaction_rpc_send(RPC_ID_USER_LAST_KEYCODE, OLED_LAST_KEYCODE_SIZE * sizeof(uint16_t), last_keycode);
            }
        }
    }
}

void add_keylog(uint16_t keycode, keyrecord_t *record) {
    if (IS_QK_MOD_TAP(keycode)) {
        keycode = (record->tap.count) ? keycode_config(QK_MOD_TAP_GET_TAP_KEYCODE(keycode)) :
                                       keycode_config(0xE0 + biton(QK_MOD_TAP_GET_MODS(keycode) & 0xF) + biton(QK_MOD_TAP_GET_MODS(keycode) & 0x10));
    } else if (IS_QK_LAYER_TAP(keycode) && record->tap.count) {
        keycode = keycode_config(QK_LAYER_TAP_GET_TAP_KEYCODE(keycode));
    } else if (IS_QK_MODS(keycode)) {
        keycode = keycode_config(QK_MODS_GET_BASIC_KEYCODE(keycode));
    } else if (IS_QK_BASIC(keycode)) {
        keycode = keycode_config(keycode);
    }

    if ((keycode == KC_BSPC) && mod_config(get_mods()) & MOD_MASK_CTRL) {
        memset(oled_keylog_str, ' ', OLED_KEYLOGGER_SIZE);
        oled_keylog_str[OLED_KEYLOGGER_SIZE] = '\0';
        return;
    }

    char code = 0;
    if (keycode < ARRAY_SIZE(code_to_name)) {
        code = pgm_read_byte(&code_to_name[keycode]);
    }

    if (code != 0) {
        size_t len = strlen(oled_keylog_str);

        if (len < OLED_KEYLOGGER_SIZE) {
            memmove(oled_keylog_str, oled_keylog_str, len);
            oled_keylog_str[len] = code;
        } else {
            memmove(oled_keylog_str, oled_keylog_str + 1, len - 1);
            oled_keylog_str[len - 1] = code;
            oled_keylog_str[len] = '\0';
        }
    }

    last_keycode[0] = keycode;
}

enum sofle_layers {
    _DEFAULTS = 0,
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
    KC_D_MUTE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_GRV, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE, LAG(KC_K), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MINS, KC_CAPS, KC_LGUI, KC_LALT, KC_LOWER, KC_SPC, KC_ENT, KC_RAISE, KC_RALT, KC_RCTL, KC_PSCR),
    [_LOWER] = LAYOUT(KC_TRNS, KC_CIRC, KC_NUM, KC_PSLS, KC_PAST, KC_PMNS, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_TRNS, KC_PSLS, KC_PERC, KC_P7, KC_P8, KC_P9, KC_PPLS, KC_BTN2, KC_AT, KC_LBRC, KC_RBRC, KC_DLR, KC_TRNS, KC_TRNS, KC_PDOT, KC_P4, KC_P5, KC_P6, KC_COMM, KC_EXLM, KC_BSLS, KC_LPRN, KC_RPRN, KC_SLSH, KC_INS, KC_TRNS, KC_P0, KC_P1, KC_P2, KC_P3, KC_EQL, KC_TRNS, KC_TRNS, KC_HASH, KC_AMPR, KC_LCBR, KC_RCBR, KC_CIRC, KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_ADJUST, KC_TRNS, KC_TRNS, KC_TRNS),
    [_RAISE] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_TRNS, KC_TRNS, KC_MENU, KC_AGIN, KC_CUT, KC_COPY, KC_MYCM, KC_PGUP, KC_INS, KC_HOME, KC_NO, KC_F12, KC_TRNS, KC_TRNS, KC_WSCH, KC_UNDO, KC_SLCT, KC_PSTE, KC_FIND, KC_PGDN, KC_UP, KC_END, KC_NO, KC_NO, KC_INS, KC_TRNS, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_F), KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS, KC_ADJUST, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
    [_ADJUST] = LAYOUT(QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, DB_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_VAI, KC_NO, RGB_SPI, RGB_MOD, RGB_HUI, KC_NO, KC_NO, KC_VOLD, KC_MUTE, KC_VOLU, KC_NO, KC_NO, RGB_VAD, KC_NO, RGB_SPD, RGB_RMOD, RGB_HUD, RGB_TOG, KC_NO, KC_NO, KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, NK_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

#ifdef OLED_ENABLE

void uint16_to_hex_string(uint16_t value, char *hex_str) {
    const char hex_chars[] = "0123456789ABCDEF";
    hex_str[0] = hex_chars[(value >> 12) & 0xF];
    hex_str[1] = hex_chars[(value >> 8) & 0xF];
    hex_str[2] = hex_chars[(value >> 4) & 0xF];
    hex_str[3] = hex_chars[value & 0xF];
    hex_str[4] = '\0';
}

static void print_status_narrow(void) {
    oled_write_ln_P(PSTR("THE\nSVL"), false);
    oled_write_ln_P(PSTR(""), false);
    oled_write_P(PSTR("\n"), false);

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Qwrt"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n"), false);
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
        case _ADJUST:
            oled_write_P(PSTR("Adj\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("K-log"), false);
    char keycode_str[5];
    uint16_to_hex_string(last_keycode[0], keycode_str);
    oled_write(keycode_str, false);
    oled_write_P(PSTR("\n\n"), false);
    oled_write(oled_keylog_str, true);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return (is_keyboard_master()) ? rotation : OLED_ROTATION_270;
}

bool oled_task_user(void) {
    print_status_narrow();
    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        add_keylog(keycode, record);
        transaction_rpc_send(RPC_ID_USER_LAST_KEYCODE, sizeof(last_keycode), last_keycode);
        switch (keycode) {
            case KC_QWERTY:
                set_single_persistent_default_layer(_QWERTY);
                return false;
            case KC_LOWER:
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                return false;
            case KC_RAISE:
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                return false;
            case KC_ADJUST:
                layer_on(_ADJUST);
                return false;
            case KC_D_MUTE:
                register_mods(mod_config(MOD_MEH));
                register_code(KC_UP);
        }
    } else {
        switch (keycode) {
            case KC_LOWER:
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                return false;
            case KC_RAISE:
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                return false;
            case KC_ADJUST:
                layer_off(_ADJUST);
                return false;
            case KC_D_MUTE:
                unregister_mods(mod_config(MOD_MEH));
                unregister_code(KC_UP);
        }
    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        tap_code(clockwise ? KC_VOLU : KC_VOLD);
    } else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case _QWERTY:
                tap_code(clockwise ? KC_PGDN : KC_PGUP);
                break;
            case _RAISE:
            case _LOWER:
                tap_code(clockwise ? KC_DOWN : KC_UP);
                break;
            default:
                tap_code(clockwise ? KC_WH_D : KC_WH_U);
                break;
        }
    }
    return false;
}

#endif