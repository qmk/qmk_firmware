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
    #ifdef RGB_MATRIX_ENABLE
    RGB_TPK = QK_KB_0,  // Toggle Per-Key
    RGB_TUG,           // Toggle Underglow
    #endif  // RGB_MATRIX_ENABLE
    KB_VRSN = QK_KB_9   // debug, type version
};

#ifndef RGB_MATRIX_ENABLE
    #define RGB_TPK _______
    #define RGB_TUG _______
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
     * │Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │PSc│Scr│Pse│
     * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Backspc│ │Ins│Hom│PgU│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │ │Del│End│PgD│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │  Shift   │     │ ↑ │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐
     * │Ctrl│GUI │Alt │         space          │ Alt│ GUI│MO(1│Ctrl│ │ ← │ ↓ │ → │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘
     */
    [0] = LAYOUT_tkl_ansi(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SCRL, KC_PAUS,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /*
     * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
     * │Rst│   │BR+│BR-│mMC│mLP│ │Br-│Br+│Prv│Ply│ │Nxt│Mut│Vl-│Vl+│ │   │   │   │
     * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │ │   │Hu+│   │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
     * │     │Tog│Mod│   │   │   │   │   │   │   │   │   │   │     │ │St-│Hu-│St+│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
     * │      │   │mod│   │   │   │   │   │   │   │   │   │        │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐
     * │        │   │   │   │Ver│   │NRO│   │   │   │   │  MO(2)   │     │Br+│
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐
     * │    │    │    │                        │    │    │    │    │ │Sp-│Br-│Sp+│
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘
     */
    [1] = LAYOUT_tkl_ansi(
        QK_BOOT,          KC_BRID,  KC_BRIU, KC_MCON, KC_LPAD, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______,
        _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUI, _______,
        _______, RGB_TOG, RGB_MOD,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_SAI,
        _______, _______, RGB_RMOD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______,  _______, _______, KB_VRSN, _______, NK_TOGG, _______, _______, _______, _______,          MO(2),            RGB_VAI,
        _______, _______, _______,                             _______,                            _______, _______, _______, _______, RGB_SPD, RGB_VAD, RGB_SPI
    ),

    /*
     * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
     * │   │   │   │   │   │   │ │   │   │   │   │ │   │   │   │   │ │   │   │   │
     * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
     * │M00│M01│M02│M03│M04│M05│M06│M07│M08│M09│M10│   │   │       │ │   │   │   │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
     * │     │M11│M12│M13│M14│M15│M16│   │   │   │   │   │   │     │ │   │   │   │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
     * │      │   │   │   │   │   │   │   │   │   │   │   │        │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐
     * │        │   │   │   │   │   │   │   │   │   │   │          │     │   │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐
     * │    │    │    │                        │    │    │    │    │ │   │   │   │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘
     */
    [2] = LAYOUT_tkl_ansi(
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        MC_0,    MC_1,    MC_2,    MC_3,    MC_4,    MC_5,    MC_6,    MC_7,    MC_8,    MC_9,    MC_10,   _______, _______, _______, _______, _______, _______,
        _______, MC_11,   MC_12,   MC_13,   MC_14,   MC_15,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______
    )
};

#ifdef RGB_MATRIX_ENABLE

/*
 * RGB Stuff
 */

#define ID87_CAPS_LOCK_KEY_INDEX 40  // position of Caps Lock key

#define ID87_CAPS_LOCK_MAX_BRIGHTNESS 0xFF
#ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #undef ID87_CAPS_LOCK_MAX_BRIGHTNESS
    #define ID87_CAPS_LOCK_MAX_BRIGHTNESS RGB_MATRIX_MAXIMUM_BRIGHTNESS
#endif

#define ID87_CAPS_LOCK_VAL_STEP 8
#ifdef RGB_MATRIX_VAL_STEP
    #undef ID87_CAPS_LOCK_VAL_STEP
    #define ID87_CAPS_LOCK_VAL_STEP RGB_MATRIX_VAL_STEP
#endif

user_config_t user_config;

void id87_update_rgb_mode(void) {
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

void id87_get_rgb_mode(void) {
    user_config.raw = eeconfig_read_kb();  // read config from EEPROM
    id87_update_rgb_mode();
}

void keyboard_post_init_user(void) {
    id87_get_rgb_mode();
}

void eeconfig_init_user(void) {
    // EEPROM is getting reset!
    user_config.raw = 0;
    id87_update_rgb_mode();
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Caps Lock key stuff

    if (host_keyboard_led_state().caps_lock) {
        uint8_t v = rgb_matrix_get_val();
        if (v < ID87_CAPS_LOCK_VAL_STEP) {
            v = ID87_CAPS_LOCK_VAL_STEP;
        } else if (v < (ID87_CAPS_LOCK_MAX_BRIGHTNESS - ID87_CAPS_LOCK_VAL_STEP)) {
            if (!user_config.rgb_disable_perkey) {
                v += ID87_CAPS_LOCK_VAL_STEP;  // inc. by one more step than current brightness
            }  // else leave as current brightness
        } else {
            v = ID87_CAPS_LOCK_MAX_BRIGHTNESS;
        }
        rgb_matrix_set_color(ID87_CAPS_LOCK_KEY_INDEX, v, v, v);  // white, brightness adjusted
    } else if (user_config.rgb_disable_perkey) {
        rgb_matrix_set_color(ID87_CAPS_LOCK_KEY_INDEX, HSV_OFF);  // off
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
                id87_update_rgb_mode();
            }
            return false;

        case RGB_TPK:
            if (record->event.pressed) {
                user_config.rgb_disable_perkey ^= 1;
                id87_update_rgb_mode();
            }
            return false;

        case RGB_TUG:
            if (record->event.pressed) {
                user_config.rgb_disable_underglow ^= 1;
                id87_update_rgb_mode();
            }
            return false;

        case EE_CLR:
            if (!record->event.pressed) {  // on release
                id87_get_rgb_mode();
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

        default:
            return true; /* Process all other keycodes normally */
    }
}
