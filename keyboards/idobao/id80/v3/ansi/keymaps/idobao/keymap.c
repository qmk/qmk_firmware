// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// Copyright 2022 IDOBAO (@idobaokb)
// SPDX-License-Identifier: GPL-2.0-or-later

/* ------------------------------------------------------------------
 * This is the IDOBAO factory default keymap ;)
 * ------------------------------------------------------------------ */

#include QMK_KEYBOARD_H
#include "version.h"

#ifdef RGB_MATRIX_ENABLE

typedef union {
    uint32_t raw;
    struct {
        bool rgb_disable_perkey:1;
        bool rgb_disable_underglow:1;
    };
} user_config_t;

#endif  // RGB_MATRIX_ENABLE

enum {
    _BASE = 0,
    _FN1,
    _FN2,
    _FN3
};

enum {
    KC_MCON = USER00,  // macOS Open Mission Control
    KC_LPAD,           // macOS Open Launchpad
    #ifdef RGB_MATRIX_ENABLE
    RGB_TPK,           // Toggle Per-Key
    RGB_TUG,           // Toggle Underglow
    #endif  // RGB_MATRIX_ENABLE
    KB_VRSN = USER09   // debug, type version
};

#ifndef RGB_MATRIX_ENABLE
    #define RGB_TPK _______
    #define RGB_TUG _______
#endif  // RGB_MATRIX_ENABLE

enum macos_consumer_usages {
    _AC_SHOW_ALL_WINDOWS = 0x29F,  // mapped to KC_MCON
    _AC_SHOW_ALL_APPS    = 0x2A0   // mapped to KC_LPAD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┐┌───┐
     * │Esc││F1 │F2 │F3 │F4 ││F5 │F6 │F7 │F8 ││F9 │F10│F11│F12││Fn1││Ins│
     * ├───┼┴──┬┴──┬┴──┬┴──┬┴┴─┬─┴─┬─┴─┬─┴─┬─┴┴┬──┴┬──┴┬──┴┬──┴┴───┤├───┤
     * │`~ │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │-_ │=+ │Backspc││Hom│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤├───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │[{ │]} │ \|  ││Del│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤└───┘
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │;: │'" │ Enter  │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┘
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │,< │.> │/? │Shift │┌───┐
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┴┬──┴──┬───┘│ ↑ │
     * │Ctrl│Win │Alt │         Space          │ Alt │Ctrl │┌───┼───┼───┐
     * └────┴────┴────┴────────────────────────┴─────┴─────┘│ ← │ ↓ │ → │
     *                                                      └───┴───┴───┘
     */
    [_BASE] = LAYOUT_80_ansi(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  MO(_FN1), KC_INS,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,  KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,  KC_DEL,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                    KC_RALT, KC_RCTL,                   KC_LEFT, KC_DOWN,  KC_RGHT
    ),

    /*
     * ┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┐┌───┐
     * │Rst││   │   │   │   ││   │   │   │   ││   │PSc│SLk│Pau││   ││Mut│
     * ├───┼┴──┬┴──┬┴──┬┴──┬┴┴─┬─┴─┬─┴─┬─┴─┬─┴┴┬──┴┬──┴┬──┴┬──┴┴───┤├───┤
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │       ││Vl+│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤├───┤
     * │     │Tog│   │Mod│Hu+│Hu-│Sa+│Sa-│Br+│Br-│Sp+│Sp-│   │     ││Vl-│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤└───┘
     * │      │   │   │   │   │   │   │   │   │   │   │   │        │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┘
     * │        │   │   │mod│Ver│   │NKR│   │   │   │   │      │┌───┐
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┴┬──┴──┬───┘│PUp│
     * │    │    │    │                        │     │     │┌───┼───┼───┐
     * └────┴────┴────┴────────────────────────┴─────┴─────┘│Hom│PDn│End│
     *                                                      └───┴───┴───┘
     */
    [_FN1] = LAYOUT_80_ansi(
        QK_BOOT, _______, _______, _______, _______,  _______, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, KC_MUTE,
        _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU,
        _______, RGB_TOG, _______, RGB_MOD, RGB_HUI,  RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, _______, _______, KC_VOLD,
        _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, RGB_RMOD, KB_VRSN, _______, NK_TOGG, _______, _______, _______, _______, _______, KC_PGUP,
        _______, _______, _______,                    _______,                   _______, _______,                   KC_HOME, KC_PGDN, KC_END
    ),

    /*
     * ┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┐┌───┐
     * │   ││   │   │   │   ││   │   │   │   ││   │   │   │   ││   ││   │
     * ├───┼┴──┬┴──┬┴──┬┴──┬┴┴─┬─┴─┬─┴─┬─┴─┬─┴┴┬──┴┬──┴┬──┴┬──┴┴───┤├───┤
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │       ││   │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤├───┤
     * │     │   │   │   │   │   │   │   │   │   │   │   │   │     ││   │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤└───┘
     * │      │   │   │   │   │   │   │   │   │   │   │   │        │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┘
     * │        │   │   │   │   │   │   │   │   │   │   │      │┌───┐
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┴┬──┴──┬───┘│   │
     * │    │    │    │                        │     │     │┌───┼───┼───┐
     * └────┴────┴────┴────────────────────────┴─────┴─────┘│   │   │   │
     *                                                      └───┴───┴───┘
     */
    [_FN2] = LAYOUT_80_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______,                   _______,                   _______, _______,                   _______, _______, _______, _______
    ),

    [_FN3] = LAYOUT_80_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______,                   _______,                   _______, _______,                   _______, _______, _______, _______
    )
};

#ifdef RGB_MATRIX_ENABLE

/*
 * RGB Stuff
 */

#define ID80_CAPS_LOCK_KEY_INDEX 34  // position of Caps Lock key

#define ID80_CAPS_LOCK_MAX_BRIGHTNESS 0xFF
#ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #undef ID80_CAPS_LOCK_MAX_BRIGHTNESS
    #define ID80_CAPS_LOCK_MAX_BRIGHTNESS RGB_MATRIX_MAXIMUM_BRIGHTNESS
#endif

#define ID80_CAPS_LOCK_VAL_STEP 8
#ifdef RGB_MATRIX_VAL_STEP
    #undef ID80_CAPS_LOCK_VAL_STEP
    #define ID80_CAPS_LOCK_VAL_STEP RGB_MATRIX_VAL_STEP
#endif

user_config_t user_config;

void id80_update_rgb_mode(void) {
    uint8_t flags = LED_FLAG_ALL;

    if (user_config.rgb_disable_perkey  &&  user_config.rgb_disable_underglow) {
        flags = 0;  // All OFF Condition
    } else {
        if (user_config.rgb_disable_perkey) {
            flags = LED_FLAG_UNDERGLOW | 0xF0;
        }
        if (user_config.rgb_disable_underglow) {
            flags = LED_FLAG_MODIFIER | LED_FLAG_KEYLIGHT | LED_FLAG_INDICATOR | 0xF0;
        }
    }

    if (flags == 0) {
        rgb_matrix_set_flags(0);
        rgb_matrix_set_color_all(HSV_OFF);
    } else {
        rgb_matrix_set_flags(flags);
        rgb_matrix_enable_noeeprom();
    }

    eeconfig_update_kb(user_config.raw);  // write back to EEPROM
}

void id80_get_rgb_mode(void) {
    user_config.raw = eeconfig_read_kb();  // read config from EEPROM
    id80_update_rgb_mode();
}

void keyboard_post_init_user(void) {
    id80_get_rgb_mode();
}

void eeconfig_init_user(void) {
    // EEPROM is getting reset!
    user_config.raw = 0;
    id80_update_rgb_mode();
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Caps Lock key stuff

    if (host_keyboard_led_state().caps_lock) {
        uint8_t v = rgb_matrix_get_val();
        if (v < ID80_CAPS_LOCK_VAL_STEP) {
            v = ID80_CAPS_LOCK_VAL_STEP;
        } else if (v < (ID80_CAPS_LOCK_MAX_BRIGHTNESS - ID80_CAPS_LOCK_VAL_STEP)) {
            if (!user_config.rgb_disable_perkey) {
                v += ID80_CAPS_LOCK_VAL_STEP;  // inc. by one more step than current brightness
            }  // else leave as current brightness
        } else {
            v = ID80_CAPS_LOCK_MAX_BRIGHTNESS;
        }
        rgb_matrix_set_color(ID80_CAPS_LOCK_KEY_INDEX, v, v, v);  // white, brightness adjusted
    } else if (user_config.rgb_disable_perkey) {
        rgb_matrix_set_color(ID80_CAPS_LOCK_KEY_INDEX, HSV_OFF);  // off
    }
    return false;
}

#endif  // RGB_MATRIX_ENABLE

/*
 * Extra keys and RGB Toggle handler
 */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

        // handle RGB toggle key - this ensures caps lock always works
        #ifdef RGB_MATRIX_ENABLE

        case QK_BOOT:
            if (record->event.pressed) {
                rgb_matrix_set_color_all(RGB_MATRIX_MAXIMUM_BRIGHTNESS, 0, 0);  // All red
                rgb_matrix_driver.flush();
            }
            return true;

        case RGB_TOG:
            /* roll through the LED modes
             * |    Level   | Per-key | Underglow |
             * |------------|---------|-----------|
             * | 0 (defalt) |   on    |    on     |
             * |     1      |   OFF   |    on     |
             * |     2      |   on    |    OFF    |
             * |     3      |   OFF   |    OFF    |
             */
            if (record->event.pressed) {
                if ( (!user_config.rgb_disable_perkey) && (!user_config.rgb_disable_underglow) ) {
                    user_config.rgb_disable_perkey = 1;
                } else if ( user_config.rgb_disable_perkey && (!user_config.rgb_disable_underglow) ) {
                    user_config.rgb_disable_perkey = 0;
                    user_config.rgb_disable_underglow = 1;
                } else if ( (!user_config.rgb_disable_perkey) && user_config.rgb_disable_underglow ) {
                    user_config.rgb_disable_perkey = 1;
                } else {
                    user_config.rgb_disable_perkey = 0;
                    user_config.rgb_disable_underglow = 0;
                }
                id80_update_rgb_mode();
            }
            return false;

        case RGB_TPK:
            if (record->event.pressed) {
                user_config.rgb_disable_perkey ^= 1;
                id80_update_rgb_mode();
            }
            return false;

        case RGB_TUG:
            if (record->event.pressed) {
                user_config.rgb_disable_underglow ^= 1;
                id80_update_rgb_mode();
            }
            return false;

        case EE_CLR:
            if (!record->event.pressed) {  // on release
                id80_get_rgb_mode();
            }
            return true;  // let this one pass on

        #endif  // RGB_MATRIX_ENABLE

        // print firmware version
        case KB_VRSN:
            if (!get_mods()) {
                if (!record->event.pressed) {
                    SEND_STRING(QMK_KEYBOARD ":" QMK_KEYMAP " (v" QMK_VERSION ")");
                }
            }
            return false;

        // @see: https://github.com/qmk/qmk_firmware/issues/10111#issuecomment-752300353
        case KC_MCON:
            if (record->event.pressed) {
                host_consumer_send(_AC_SHOW_ALL_WINDOWS);
            } else {
                host_consumer_send(0);
            }
            return false;

        case KC_LPAD:
            if (record->event.pressed) {
                host_consumer_send(_AC_SHOW_ALL_APPS);
            } else {
                host_consumer_send(0);
            }
            return false;

        default:
            return true; /* Process all other keycodes normally */
    }
}
