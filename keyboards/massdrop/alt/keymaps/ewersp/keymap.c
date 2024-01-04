#include QMK_KEYBOARD_H

enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
    ALT_DEL,               //Added to map left alt + backspace to delete
};

// Friendly layer names
enum alt_layers {
    DEF = 0,
    ALT,
    FUNC,
    SUPR
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, MO(SUPR),                           KC_SPC,                             KC_RALT, MO(FUNC),KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [ALT] = LAYOUT_65_ansi_blocker(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, KC_LALT,                            _______,                            _______, _______, _______, _______, _______
    ),
    [FUNC] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_MUTE,
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, KC_PSCR, KC_SCRL, KC_PAUS, _______, KC_END,
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU,
        _______, RGB_TOG, _______, _______, EE_CLR,  MD_BOOT, NK_TOGG, DBG_TOG, _______, TG(ALT), _______, _______,          KC_PGUP, KC_VOLD,
        _______, _______, KC_LALT,                            _______,                            _______, _______, KC_HOME, KC_PGDN, KC_END
    ),
    [SUPR] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  ALT_DEL, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_END,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, KC_HOME, _______, KC_END
    )
};

// EEPROM storage mode
enum alt_rgb_mode {
    RGB_MODE_ALL,
    RGB_MODE_KEYLIGHT,
    RGB_MODE_UNDERGLOW,
    RGB_MODE_NONE,
};

// EEPROM storage type
typedef union {
    uint32_t raw;
    struct {
        uint8_t rgb_mode :8;
    };
} alt_config_t;

alt_config_t alt_config;

// Read from EEPROM on init to load the last saved mode
void keyboard_post_init_kb(void) {
    alt_config.raw = eeconfig_read_user();
    switch (alt_config.rgb_mode) {
        case RGB_MODE_ALL:
            rgb_matrix_set_flags(LED_FLAG_ALL);
            rgb_matrix_enable_noeeprom();
            break;
        case RGB_MODE_KEYLIGHT:
            rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
            rgb_matrix_set_color_all(0, 0, 0);
            break;
        case RGB_MODE_UNDERGLOW:
            rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
            rgb_matrix_set_color_all(0, 0, 0);
            break;
        case RGB_MODE_NONE:
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
            break;
    }
}

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

// If the super alt layer is the active layer
bool super_alt_layer_active = false;

// If we need to unregister alt when leaving the super alt layer
bool need_to_unregister_alt = false;

// This runs code every time that the layers get changed
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case DEF:
            // When returning to the default layer, check if we need to unregister the left alt key
            if (super_alt_layer_active && need_to_unregister_alt) {
                unregister_code(KC_LALT);
            }

            super_alt_layer_active = false;
            need_to_unregister_alt = false;
            break;
        case SUPR:
            super_alt_layer_active = true;
            break;
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        // These are the keys we want to 'fall though' and behave as usual when pressed with the alt modifier
        case KC_A ... KC_Z:
        case KC_TAB:
        case KC_DEL:
        case KC_UP:
        case KC_DOWN:
        case MO(FUNC):
            if (super_alt_layer_active && record->event.pressed) {
                // Only activate the alt modifier for the first key press
                if ((get_mods() & MOD_BIT(KC_LALT)) == false) {
                    register_code(KC_LALT);
                    need_to_unregister_alt = true;
                }
            }
            // We still want to process the keycode normally
            return true;
        case KC_F4:
            // Map alt+shift+4 to alt+f4
            if (super_alt_layer_active && (get_mods() & MOD_BIT(KC_LSFT))) {
                if (record->event.pressed) {
                    register_code(KC_LALT);
                } else {
                    unregister_code(KC_LALT);
                }
            }
            return true;
        case ALT_DEL:
            if (record->event.pressed) {
                register_code(KC_DEL);
            } else {
                unregister_code(KC_DEL);
            }
            return false;
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case QK_CLEAR_EEPROM:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    eeconfig_init();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                        rgb_matrix_set_color_all(0, 0, 0);
                        alt_config.rgb_mode = RGB_MODE_KEYLIGHT;
                        break;
                    }
                    case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        rgb_matrix_set_color_all(0, 0, 0);
                        alt_config.rgb_mode = RGB_MODE_UNDERGLOW;
                        break;
                    }
                    case LED_FLAG_UNDERGLOW: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_disable_noeeprom();
                        alt_config.rgb_mode = RGB_MODE_NONE;
                        break;
                    }
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();
                        alt_config.rgb_mode = RGB_MODE_ALL;
                        break;
                    }
                }
                eeconfig_update_user(alt_config.raw);
            }
            return false;
        default:
            return true; // Process all other keycodes normally
    }
}
