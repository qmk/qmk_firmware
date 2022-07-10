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
        #ifndef ID67_DISABLE_UNDERGLOW
        bool rgb_disable_underglow:1;
        #endif  // ID67_DISABLE_UNDERGLOW
    };
} user_config_t;

#endif  // RGB_MATRIX_ENABLE

enum {
    KC_MCON = USER00,  // macOS Open Mission Control
    KC_LPAD,           // macOS Open Launchpad
    #ifdef RGB_MATRIX_ENABLE
    RGB_TPK,           // Toggle Per-Key
    #ifndef ID67_DISABLE_UNDERGLOW
    RGB_TUG,           // Toggle Underglow
    #endif  // ID67_DISABLE_UNDERGLOW
    #endif  //RGB_MATRIX_ENABLE
    KB_VRSN = USER09   // debug, type version
};

#ifndef RGB_MATRIX_ENABLE
    #define RGB_TPK _______
    #define RGB_TUG _______
#else
    #ifdef ID67_DISABLE_UNDERGLOW
        #define RGB_TUG _______
    #endif  // ID67_DISABLE_UNDERGLOW
#endif  // RGB_MATRIX_ENABLE

enum macos_consumer_usages {
    _AC_SHOW_ALL_WINDOWS = 0x29F,  // mapped to KC_MCON
    _AC_SHOW_ALL_APPS    = 0x2A0   // mapped to KC_LPAD
};

/* Special Keys */
#define SK_LT1C LT(1, KC_CAPS)  // Layer Tap 1, i.e., Tap = Caps Lock, Hold = Layer 1
#define SK_LT2A LT(2, KC_APP)   // Layer Tap 2, i.e., Tap = Menu, Hold = Layer 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Backspc│ ~ │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │Del│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │*Caps*│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │PUp│  *Caps* => `LT(1, KC_CAPS)`
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shft │Up │PDn│
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
     * │Ctrl│Win │Alt │                        │Fn1 │*Mn*│ │Lf │Dn │Rt │  *Mn* => `LT(2, KC_APP)`
     * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
     */
    [0] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_TILD,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,      KC_DEL,
        SK_LT1C,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,              KC_PGUP,
        KC_LSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,          KC_PGDN,
        KC_LCTL,   KC_LGUI,   KC_LALT,                       KC_SPC,                              MO(1),     SK_LT2A,   KC_LEFT,   KC_DOWN,    KC_RGHT
    ),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│       │   │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │     │Tog│Up │Mod│Hu+│Hu-│Sa+│Sa-│Br+│Br-│   │TUG│TPK│     │   │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │      │Lf │Dn │Rt │   │   │   │   │   │Ins│Hom│PUp│        │   │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │        │RST│Sp+│Sp-│   │Vl-│Mut│Vl+│Del│End│PDn│      │   │   │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
     * │    │    │    │                        │    │    │ │   │   │   │
     * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
     */
    [1] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,          _______,
        _______,     RGB_TOG, KC_UP,   RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, RGB_TUG, RGB_TPK, _______,      _______,
        KC_CAPS,       KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, KC_INS,  KC_HOME, KC_PGUP, _______,             _______,
        _______,         QK_BOOT,  RGB_SPI,  RGB_SPD, KB_VRSN, KC_VOLD, KC_MUTE, KC_VOLU, KC_DEL,  KC_END,  KC_PGDN, _______, _______,         _______,
        _______,   _______,   _______,                      _______,                              _______,   _______,   _______,   _______,    _______
    ),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │   │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │   │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │      │   │   │   │   │   │   │   │   │   │   │   │        │   │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │        │   │   │   │   │   │   │   │   │   │   │      │   │   │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
     * │    │    │    │                        │    │    │ │   │   │   │
     * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
     */
	[2] = LAYOUT_65_ansi_blocker(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,
        _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,
        _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______,
        _______,   _______,   _______,                      _______,                              _______,   _______,   _______,   _______,    _______
    ),

	[3] = LAYOUT_65_ansi_blocker(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,
        _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,
        _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______,
        _______,   _______,   _______,                      _______,                              _______,   _______,   _______,   _______,    _______
    )
};

#ifdef RGB_MATRIX_ENABLE

/*
 * RGB Stuff
 */

#define ID67_CAPS_LOCK_KEY_INDEX 36  // position of Caps Lock key

#define ID67_CAPS_LOCK_MAX_BRIGHTNESS 0xFF
#ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #undef ID67_CAPS_LOCK_MAX_BRIGHTNESS
    #define ID67_CAPS_LOCK_MAX_BRIGHTNESS RGB_MATRIX_MAXIMUM_BRIGHTNESS
#endif

#define ID67_CAPS_LOCK_VAL_STEP 8
#ifdef RGB_MATRIX_VAL_STEP
    #undef ID67_CAPS_LOCK_VAL_STEP
    #define ID67_CAPS_LOCK_VAL_STEP RGB_MATRIX_VAL_STEP
#endif

user_config_t user_config;

void id67_update_rgb_mode(void) {
    uint8_t flags = LED_FLAG_ALL;

    if (user_config.rgb_disable_perkey
        #ifndef ID67_DISABLE_UNDERGLOW
        && user_config.rgb_disable_underglow
        #endif  // ID67_DISABLE_UNDERGLOW
        ) {
        flags = 0;  // All OFF Condition
    } else {
        if (user_config.rgb_disable_perkey) {
            #ifndef ID67_DISABLE_UNDERGLOW
            flags = LED_FLAG_UNDERGLOW | 0xF0;
            #else
            flags = 0xF0;
            #endif  // ID67_DISABLE_UNDERGLOW
        }
        #ifndef ID67_DISABLE_UNDERGLOW
        if (user_config.rgb_disable_underglow) {
            flags = LED_FLAG_MODIFIER | LED_FLAG_KEYLIGHT | LED_FLAG_INDICATOR | 0xF0;
        }
        #endif  // ID67_DISABLE_UNDERGLOW
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

void id67_get_rgb_mode(void) {
    user_config.raw = eeconfig_read_kb();  // read config from EEPROM
    id67_update_rgb_mode();
}

void keyboard_post_init_user(void) {
    id67_get_rgb_mode();
}

void eeconfig_init_user(void) {
    // EEPROM is getting reset!
    user_config.raw = 0;
    id67_update_rgb_mode();
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Caps Lock key stuff

    if (host_keyboard_led_state().caps_lock) {
        uint8_t v = rgb_matrix_get_val();
        if (v < ID67_CAPS_LOCK_VAL_STEP) {
            v = ID67_CAPS_LOCK_VAL_STEP;
        } else if (v < (ID67_CAPS_LOCK_MAX_BRIGHTNESS - ID67_CAPS_LOCK_VAL_STEP)) {
            if (!user_config.rgb_disable_perkey) {
                v += ID67_CAPS_LOCK_VAL_STEP;  // inc. by one more step than current brightness
            }  // else leave as current brightness
        } else {
            v = ID67_CAPS_LOCK_MAX_BRIGHTNESS;
        }
        rgb_matrix_set_color(ID67_CAPS_LOCK_KEY_INDEX, v, v, v);  // white, brightness adjusted
    } else if (user_config.rgb_disable_perkey) {
        rgb_matrix_set_color(ID67_CAPS_LOCK_KEY_INDEX, HSV_OFF);  // off
    }
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
             * |    Level    | Per-key | Underglow |
             * |-------------|---------|-----------|
             * | 0 (default) |   on    |    on     |
             * |     1       |   OFF   |    on     |
             * |     2       |   on    |    OFF    |
             * |     3       |   OFF   |    OFF    |
             *
             * for ID67_DISABLE_UNDERGLOW
             * |    Level    | Per-key |
             * |-------------|---------|
             * | 0 (default) |   on    |
             * |     1       |   OFF   |
             */
            if (record->event.pressed) {
                if ((!user_config.rgb_disable_perkey)
                    #ifndef ID67_DISABLE_UNDERGLOW
                    && (!user_config.rgb_disable_underglow)
                    #endif  // ID67_DISABLE_UNDERGLOW
                    ) {
                    user_config.rgb_disable_perkey = 1;

                #ifndef ID67_DISABLE_UNDERGLOW

                } else if (user_config.rgb_disable_perkey && (!user_config.rgb_disable_underglow)) {
                    user_config.rgb_disable_perkey = 0;
                    user_config.rgb_disable_underglow = 1;

                } else if ((!user_config.rgb_disable_perkey) && user_config.rgb_disable_underglow) {
                    user_config.rgb_disable_perkey = 1;

                #endif  // ID67_DISABLE_UNDERGLOW

                } else {
                    user_config.rgb_disable_perkey = 0;
                    #ifndef ID67_DISABLE_UNDERGLOW
                    user_config.rgb_disable_underglow = 0;
                    #endif  // ID67_DISABLE_UNDERGLOW
                }

                id67_update_rgb_mode();
            }
            return false;

        case RGB_TPK:
            if (record->event.pressed) {
                user_config.rgb_disable_perkey ^= 1;
                id67_update_rgb_mode();
            }
            return false;

        #ifndef ID67_DISABLE_UNDERGLOW

        case RGB_TUG:
            if (record->event.pressed) {
                user_config.rgb_disable_underglow ^= 1;
                id67_update_rgb_mode();
            }
            return false;

        #endif  // ID67_DISABLE_UNDERGLOW

        case EE_CLR:
            if (!record->event.pressed) {  // on release
                id67_get_rgb_mode();
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
