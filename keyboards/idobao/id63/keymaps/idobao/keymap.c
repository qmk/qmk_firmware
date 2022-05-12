// Copyright 2022 idobaokb (@idobaokb)
// SPDX-License-Identifier: GPL-2.0-or-later

/* ------------------------------------------------------------------
 * This is the IDOBAO factory default keymap ;)
 * ------------------------------------------------------------------ */

#include QMK_KEYBOARD_H
#include "version.h"

enum {
    _BASE = 0,
    _FN1,
    _FN2,
    _FN3
};

enum {
    KC_MCON = USER00,  // macOS Open Mission Control
    KC_LPAD,           // macOS Open Launchpad
    KB_VRSN = USER09   // debug, type version
};

enum macos_consumer_usages {
    _AC_SHOW_ALL_WINDOWS = 0x29F,  // mapped to KC_MCON
    _AC_SHOW_ALL_APPS    = 0x2A0   // mapped to KC_LPAD
};

/* Special Keys */
#define SK_LT1C LT(_FN1, KC_CAPS)  // Layer Tap 1, i.e., Tap = Caps Lock, Hold = Layer 1
#define SK_LT2M LT(_FN2, KC_MENU)  // Layer Tap 2, i.e., Tap = Menu, Hold = Layer 2

/* key matrix */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Backspc│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │*Caps*│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │  *Caps* => Tap = Caps Lock, Hold = Layer 1
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┬───┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │Shift │Up │ / │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬───┼───┼───┤
     * │Ctrl│Win │Alt │                        │*M*│Fn1│Lf │Dn │Rt │  *M* => Tap = Menu, Hold = Layer 2
     * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘
     */
    [_BASE] = LAYOUT_63_ansi(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,   KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        SK_LT1C, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,   KC_V,     KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT, KC_UP,   KC_SLSH,
        KC_LCTL, KC_LGUI,          KC_LALT,                   KC_SPC,                    SK_LT2M, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │ ~ │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│  Del  │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │     │tog│up │mod│hu+│hu-│sa+│sa-│br+│br-│prn│slk│pus│ Ins │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │ Caps │lf │dn │rt │   │   │   │   │sp+│sp-│   │   │        │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┬───┤
     * │        │Rst│   │mod│   │   │   │   │   │   │      │PUp│ / │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬───┼───┼───┤
     * │    │    │    │                        │   │ * │Hom│PDn│End│
     * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘
     */
    [_FN1] = LAYOUT_63_ansi(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, RGB_TOG, KC_UP,   RGB_MOD, RGB_HUI,  RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_PSCR, KC_SLCK, KC_PAUS, KC_INS,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,  _______, _______, _______, RGB_SPI, RGB_SPD, _______, _______,          _______,
        _______,          RESET,   _______, RGB_RMOD, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, _______,
        _______, _______,          _______,                    _______,                   _______, _______, KC_HOME, KC_PGDN, KC_END
    ),

    [_FN2] = LAYOUT_63_ansi(
        KC_ESC,  KC_BRID, KC_BRIU, KC_MCON, KC_LPAD, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_POWER,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, KB_VRSN, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______,          _______,                   _______,                   _______, _______, _______, _______, _______
    ),

    [_FN3] = LAYOUT_63_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______,          _______,                   _______,                   _______, _______, _______, _______, _______
    )
};

#ifdef RGB_MATRIX_ENABLE

/*
 * RGB Stuff
 */

#define ID63_CAPS_LOCK_KEY_INDEX 34  // position of Caps Lock key

bool isRGBOff = false;

#define ID63_CAPS_LOCK_MAX_BRIGHTNESS 0xFF
#ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #undef ID63_CAPS_LOCK_MAX_BRIGHTNESS
    #define ID63_CAPS_LOCK_MAX_BRIGHTNESS RGB_MATRIX_MAXIMUM_BRIGHTNESS
#endif

#define ID63_CAPS_LOCK_VAL_STEP 8
#ifdef RGB_MATRIX_VAL_STEP
    #undef ID63_CAPS_LOCK_VAL_STEP
    #define ID63_CAPS_LOCK_VAL_STEP RGB_MATRIX_VAL_STEP
#endif

void keyboard_post_init_user(void) {
    isRGBOff = false;
}

// void rgb_matrix_indicators_user(void) {
//     // do nothing, override base <<weak>> function to disable it
// }

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Caps Lock key stuff

    if (host_keyboard_led_state().caps_lock) {
        uint8_t v = rgb_matrix_get_val();
        if (v < ID63_CAPS_LOCK_VAL_STEP) {
            v = ID63_CAPS_LOCK_VAL_STEP;
        } else if (v < (ID63_CAPS_LOCK_MAX_BRIGHTNESS - ID63_CAPS_LOCK_VAL_STEP)) {
            if (!isRGBOff) {
                v += ID63_CAPS_LOCK_VAL_STEP;  // inc. by one more step than current brightness
            }  // else leave as current brightness
        } else {
            v = ID63_CAPS_LOCK_MAX_BRIGHTNESS;
        }
        rgb_matrix_set_color(ID63_CAPS_LOCK_KEY_INDEX, v, v, v);  // white, brightness adjusted
    } else if (isRGBOff) {
        rgb_matrix_set_color(ID63_CAPS_LOCK_KEY_INDEX, HSV_OFF);  // off
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
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL:
                        isRGBOff = true;
                        rgb_matrix_set_flags(0);
                        rgb_matrix_set_color_all(HSV_OFF);
                        break;
                    default:
                        isRGBOff = false;
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();  // turn the lights back on
                }
            }
            return false;
        #endif

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
            }
            return false;

        case KC_LPAD:
            if (record->event.pressed) {
                host_consumer_send(_AC_SHOW_ALL_APPS);
            }
            return false;

        default:
            return true; /* Process all other keycodes normally */
    }
}
