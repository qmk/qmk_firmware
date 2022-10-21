// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "specialk.h"
#include "version.h"

typedef union {
    uint32_t raw;
    struct {
        bool in_arrow_mode:1;
        #ifdef RGB_MATRIX_ENABLE
        bool rgb_disable_perkey:1;
        #ifndef ID61_DISABLE_UNDERGLOW
        bool rgb_disable_underglow:1;
        #endif  // ID61_DISABLE_UNDERGLOW
        #endif  // RGB_MATRIX_ENABLE
    };
} user_config_t;

enum {
    _BASE = 0,
    _FN1,
    _FN2,
    _FN3
};

enum {
    KC_MCON = USER00,  // macOS Open Mission Control
    KC_LPAD,           // macOS Open Launchpad
    KB_ARRW,           // toggle right modifiers are arrows feature
    KB_RSFT,           // right shift or up arrow
    KB_RALT,           // right alt or left arrow
    KB_RAPP,           // menu or down arrow (Windows Menu)
    KB_RCOM,           // right gui or left arrow (macOS Command)
    KB_ROPT,           // right alt or down arrow (macOS Option)
    KB_RCTL,           // right ctrl ot right arrow
    KB_VRSN            // debug, type version
};

enum macos_consumer_usages {
    _AC_SHOW_ALL_WINDOWS = 0x29F,  // mapped to KC_MCON
    _AC_SHOW_ALL_APPS    = 0x2A0   // mapped to KC_LPAD
};

/* Special Keys */
#define SK_LT1C LT(_FN1, KC_CAPS)  // Layer Tap 1, i.e., Tap = Caps Lock, Hold = Layer 1
#define SK_LT2A LT(_FN2, KC_APP)   // Layer Tap 2, i.e., Tap = Menu, Hold = Layer 2

/* key matrix */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Backspc│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │*Caps*│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │  *Caps* => Tap = Caps Lock, Hold = Layer 1 (Fn1)
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │  ↑Shift  │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │Ctrl│Win │Alt │                        │Fn1 │←Alt│↓Mnu│→Ctl│
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     */
    [_BASE] = LAYOUT_60_ansi(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS,
        SK_LT1C, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH, KB_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             MO(_FN1), KB_RALT, KB_RAPP, KB_RCTL
    ),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │ ' │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│  Del  │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │ArwMd│   │ ↑ │   │   │Tog│Hu+│Sa+│Br+│Sp+│PSc│Hom│End│ Ins │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │      │ ← │ ↓ │ → │   │Mod│Hu-│Sa-│Br-│Sp-│   │PUp│        │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │        │   │   │   │Ver│Rst│NKR│   │   │   │PDn│          │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │    │    │    │                        │    │    │    │    │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     */
    [_FN1] = LAYOUT_60_ansi(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        KB_ARRW, _______, KC_UP,   _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, KC_PSCR, KC_HOME, KC_END,  KC_INS,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, _______, KC_PGUP, _______,
        _______,          _______, _______, _______, KB_VRSN, QK_BOOT, NK_TOGG, _______, _______, _______, KC_PGDN, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    ),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │      │   │   │   │   │   │   │   │   │   │   │   │        │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │        │   │   │   │   │   │   │   │   │   │   │          │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │    │    │    │                        │    │    │    │    │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     */
    [_FN2] = LAYOUT_60_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    ),

    [_FN3] = LAYOUT_60_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    )
};

user_config_t user_config;

#ifdef RGB_MATRIX_ENABLE

/*
 * RGB Stuff
 */

#define ID61_CAPS_LOCK_KEY_INDEX 32  // position of Caps Lock key

#define ID61_CAPS_LOCK_MAX_BRIGHTNESS 0xFF
#ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #undef ID61_CAPS_LOCK_MAX_BRIGHTNESS
    #define ID61_CAPS_LOCK_MAX_BRIGHTNESS RGB_MATRIX_MAXIMUM_BRIGHTNESS
#endif

#define ID61_CAPS_LOCK_VAL_STEP 8
#ifdef RGB_MATRIX_VAL_STEP
    #undef ID61_CAPS_LOCK_VAL_STEP
    #define ID61_CAPS_LOCK_VAL_STEP RGB_MATRIX_VAL_STEP
#endif

void ID61_update_rgb_mode(void) {
    uint8_t flags = LED_FLAG_ALL;

    if (user_config.rgb_disable_perkey
        #ifndef ID61_DISABLE_UNDERGLOW
        && user_config.rgb_disable_underglow
        #endif  // ID61_DISABLE_UNDERGLOW
        ) {
        flags = 0;  // All OFF Condition
    } else {
        if (user_config.rgb_disable_perkey) {
            #ifndef ID61_DISABLE_UNDERGLOW
            flags = LED_FLAG_UNDERGLOW | 0xF0;
            #else
            flags = 0xF0;
            #endif  // ID61_DISABLE_UNDERGLOW
        }
        #ifndef ID61_DISABLE_UNDERGLOW
        if (user_config.rgb_disable_underglow) {
            flags = LED_FLAG_MODIFIER | LED_FLAG_KEYLIGHT | LED_FLAG_INDICATOR | 0xF0;
        }
        #endif  // ID61_DISABLE_UNDERGLOW
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

void ID61_get_rgb_mode(void) {
    user_config.raw = eeconfig_read_kb();  // read config from EEPROM
    ID61_update_rgb_mode();
}

void keyboard_post_init_user(void) {
    ID61_get_rgb_mode();
}

void eeconfig_init_user(void) {
    // EEPROM is getting reset!
    user_config.raw = 0;
    ID61_update_rgb_mode();
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Caps Lock key stuff

    if (host_keyboard_led_state().caps_lock) {
        uint8_t v = rgb_matrix_get_val();
        if (v < ID61_CAPS_LOCK_VAL_STEP) {
            v = ID61_CAPS_LOCK_VAL_STEP;
        } else if (v < (ID61_CAPS_LOCK_MAX_BRIGHTNESS - ID61_CAPS_LOCK_VAL_STEP)) {
            if (!user_config.rgb_disable_perkey) {
                v += ID61_CAPS_LOCK_VAL_STEP;  // inc. by one more step than current brightness
            }  // else leave as current brightness
        } else {
            v = ID61_CAPS_LOCK_MAX_BRIGHTNESS;
        }
        rgb_matrix_set_color(ID61_CAPS_LOCK_KEY_INDEX, v, v, v);  // white, brightness adjusted
    } else if (user_config.rgb_disable_perkey) {
        rgb_matrix_set_color(ID61_CAPS_LOCK_KEY_INDEX, HSV_OFF);  // off
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
             * for ID61_DISABLE_UNDERGLOW
             * |    Level    | Per-key |
             * |-------------|---------|
             * | 0 (default) |   on    |
             * |     1       |   OFF   |
             */
            if (record->event.pressed) {
                if ( (!user_config.rgb_disable_perkey)
                    #ifndef ID61_DISABLE_UNDERGLOW
                    && (!user_config.rgb_disable_underglow)
                    #endif  // ID61_DISABLE_UNDERGLOW
                    ) {
                    user_config.rgb_disable_perkey = 1;

                #ifndef ID61_DISABLE_UNDERGLOW

                } else if ( user_config.rgb_disable_perkey && (!user_config.rgb_disable_underglow) ) {
                    user_config.rgb_disable_perkey = 0;
                    user_config.rgb_disable_underglow = 1;

                } else if ( (!user_config.rgb_disable_perkey) && user_config.rgb_disable_underglow ) {
                    user_config.rgb_disable_perkey = 1;

                #endif  // ID61_DISABLE_UNDERGLOW

                } else {
                    user_config.rgb_disable_perkey = 0;
                    #ifndef ID61_DISABLE_UNDERGLOW
                    user_config.rgb_disable_underglow = 0;
                    #endif  // ID61_DISABLE_UNDERGLOW
                }
                ID61_update_rgb_mode();
            }
            return false;

        case EE_CLR:
            if (!record->event.pressed) {  // on release
                ID61_get_rgb_mode();
            }
            return true;  // let this one pass on

        #endif  // RGB_MATRIX_ENABLE

        case KB_ARRW:
            if (record->event.pressed) {
                user_config.in_arrow_mode ^= 1;
            }
            return false;

        case KB_RSFT: return ID61_process_special_k(keycode, record, user_config.in_arrow_mode, KC_RSFT, KC_UP, KC_PGUP);
        case KB_RALT: return ID61_process_special_k(keycode, record, user_config.in_arrow_mode, KC_RALT, KC_LEFT, KC_HOME);
        case KB_RAPP: return ID61_process_special_k(keycode, record, user_config.in_arrow_mode, KC_APP, KC_DOWN, KC_PGDN);
        case KB_RCOM: return ID61_process_special_k(keycode, record, user_config.in_arrow_mode, KC_RGUI, KC_LEFT, KC_HOME);
        case KB_ROPT: return ID61_process_special_k(keycode, record, user_config.in_arrow_mode, KC_RALT, KC_DOWN, KC_PGDN);
        case KB_RCTL: return ID61_process_special_k(keycode, record, user_config.in_arrow_mode, KC_RCTL, KC_RIGHT, KC_END);

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

        // Shift + Backspace = Delete, see: https://docs.qmk.fm/#/feature_advanced_keycodes?id=shift-backspace-for-delete
        case KC_BSPC: return ID61_backspace_special(keycode, record);

        default:
            return true; /* Process all other keycodes normally */
    }
}
