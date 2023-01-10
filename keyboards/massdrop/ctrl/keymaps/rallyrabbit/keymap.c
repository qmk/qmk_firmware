#include QMK_KEYBOARD_H

enum ctrl_keycodes {
    U_T_AUTO = SAFE_RANGE, /* USB Extra Port Toggle Auto Detect / Always Active */
    U_T_AGCR,              /* USB Toggle Automatic GCR control */
    DBG_TOG,               /* DEBUG Toggle On / Off */
    DBG_MTRX,              /* DEBUG Toggle Matrix Prints */
    DBG_KBD,               /* DEBUG Toggle Keyboard Prints */
    DBG_MOU,               /* DEBUG Toggle Mouse Prints */
    MD_BOOT,               /* Restart into bootloader after hold timeout */
    KC_A_AC,               /* A with acute accent */
    KC_E_AC,               /* E with acute accent */
    KC_I_AC,               /* I with acute accent */
    KC_O_AC,               /* O with acute accent */
    KC_U_AC,               /* U with acute accent */
    KC_AE_C,               /* AE character */
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PSCR, KC_SCRL, KC_PAUS,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                              KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(1),   KC_APP,  KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            KC_MUTE, _______, _______,
        KC_NUM,  KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_0, _______, _______, _______,   KC_MPLY, KC_MSTP, KC_VOLU,
        _______, _______, _______, KC_E_AC, RGB_SPI, RGB_VAI, RGB_SAI, KC_U_AC, KC_I_AC, KC_O_AC, _______,U_T_AUTO,U_T_AGCR, _______,   KC_MPRV, KC_MNXT, KC_VOLD,
        _______, KC_A_AC, KC_AE_C, _______, RGB_SPD, RGB_VAD, RGB_SAD, _______, _______, _______, _______, _______, KC_ENT,
        KC_LSFT, RGB_TOG, _______, _______, _______, MD_BOOT, NK_TOGG, _______, _______, _______, _______, KC_RSFT,                              RGB_HUI,
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,           RGB_RMOD, RGB_HUD, RGB_MOD
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______, _______,                              _______,
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______
    ),
    */
};

#define MODS_SHIFT  (get_mods() & MOD_MASK_SHIFT)
#define MODS_CTRL   (get_mods() & MOD_MASK_CTRL)
#define MODS_ALT    (get_mods() & MOD_MASK_ALT)

void matrix_init_user(void) {
    /* Initialize for the Windows Unicode Set for Special Characters by default */
    set_unicode_input_mode(UNICODE_MODE_WINDOWS);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
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

        case KC_A_AC:
            if (record->event.pressed) {
                if (MODS_SHIFT) {
                    send_unicode_string("Á");
                } else {
                    send_unicode_string("á");
                }
            }
            return false;


        case KC_E_AC:
            if (record->event.pressed) {
                if (MODS_SHIFT) {
                    send_unicode_string("É");
                } else {
                    send_unicode_string("é");
                }
            }
            return false;

        case KC_I_AC:
            if (record->event.pressed) {
                if (MODS_SHIFT) {
                    send_unicode_string("Í");
                } else {
                    send_unicode_string("í");
                }
            }
            return false;


        case KC_O_AC:
            if (record->event.pressed) {
                if (MODS_SHIFT) {
                    send_unicode_string("Ó");
                } else {
                    send_unicode_string("ó");
                }
            }
            return false;


        case KC_U_AC:
            if (record->event.pressed) {
                if (MODS_SHIFT) {
                    send_unicode_string("Ú");
                } else {
                    send_unicode_string("ú");
                }
            }
            return false;

        case KC_AE_C:
            if (record->event.pressed) {
                if (MODS_SHIFT) {
                    send_unicode_string("Æ");
                } else {
                    send_unicode_string("æ");
                }
            }
            return false;

        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL:
                    {
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                        rgb_matrix_set_color_all(0, 0, 0);
                    }
                    break;

                    case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR):
                    {
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        rgb_matrix_set_color_all(0, 0, 0);
                    }
                    break;

                    case LED_FLAG_UNDERGLOW:
                    {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_disable_noeeprom();
                    }
                    break;

                    default:
                    {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();
                    }
                    break;
                }
            }
            return false;

        default:
            return true; /* Process all other keycodes normally */
    }
}
