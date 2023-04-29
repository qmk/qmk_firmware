// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
 * IDOBAO ID67 Keymap for a ID67 Bestype, built for Mac use
 */

#include QMK_KEYBOARD_H
#include "version.h"

enum {
    _BASE = 0,
    _FN1,
    _FN2,
    _FN3
};

enum {
    KB_VRSN = SAFE_RANGE
};

#define LT1_C_L LT(_FN1, KC_CAPS)

#ifndef MIN
    #define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

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
     * │Ctrl│Opt │Comm│                        │Fn1 │Fn2 │ │Lf │Dn │Rt │
     * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
     */
    [_BASE] = LAYOUT_65_ansi_blocker(
        QK_GESC,  KC_1,     KC_2,    KC_3,     KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,   KC_EQL,  KC_BSPC,   KC_GRAVE,
        KC_TAB,   KC_Q,     KC_W,    KC_E,     KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,   KC_RBRC, KC_BSLS,   KC_DELETE,
        LT1_C_L,  KC_A,     KC_S,    KC_D,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,            KC_ENT,    KC_PGUP,
        KC_LSFT,            KC_Z,    KC_X,     KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_RSFT, KC_UP,     KC_PGDN,
        KC_LCTL,  KC_LALT,           KC_LGUI,                    KC_SPC,                             FN_MO13, FN_MO23,   KC_LEFT, KC_DOWN,   KC_RIGHT),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │ ~ │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│ ERASE │F13│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │     │   │Up │   │   │   │   │   │   │   │PSc│Hom│End│Eject│Ins│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │ Caps │Lf │Dn │Rt │   │   │   │   │   │   │PUp│PDn│ enter  │Hom│
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │  Shft  │   │   │   │   │   │   │   │   │Ins│Del│Shift │   │End│
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
     * │ctrl│opt │comm│                        │    │Fn3 │ │   │   │   │
     * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
     */
    [_FN1] = LAYOUT_65_ansi_blocker(
        KC_GRAVE, KC_F1,    KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,    KC_F12,  KC_ERAS,   KC_F13,
        _______,  XXXXXXX,  KC_UP,   XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_HOME,   KC_END,  KC_EJCT,   KC_INS,
        KC_CAPS,  KC_LEFT,  KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_PGDN,            KC_PENT,   KC_HOME,
        KC_RSFT,            XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_INS,  KC_DELETE, KC_LSFT, _______,   KC_END,
        KC_RCTL,  KC_RALT,           KC_RGUI,                    _______,                            _______, _______,   _______, _______,   _______),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │Esc│SB-│SB+│mMC│mLP│Br-│Br+│Prv│Ply│Nxt│Mut│Vl-│Vl+│  out  │F14│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │ Tog │Mod│   │   │   │   │   │   │   │   │   │   │   │     │PSc│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │      │mod│   │   │   │   │   │   │   │   │Hu+│Sa+│        │SLk│
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │        │   │   │   │   │   │   │   │   │Hu-│Sa-│      │Br+│Pau│
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
     * │    │    │    │                        │Fn3 │    │ │Sp-│Br-│Sp+│
     * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
     */
    [_FN2] = LAYOUT_65_ansi_blocker(
        KC_ESC,   KC_BRID,  KC_BRIU, KC_MCON,  KC_LPAD, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD,   KC_VOLU, KC_OUT,    KC_F14,
        RGB_TOG,  RGB_MOD,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,   KC_PSCR,
        XXXXXXX,  RGB_RMOD, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUI, RGB_SAI,            XXXXXXX,   KC_SCRL,
        XXXXXXX,            XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUD, RGB_SAD,   XXXXXXX, RGB_VAI,   KC_PAUS,
        XXXXXXX,  XXXXXXX,           XXXXXXX,                    XXXXXXX,                            XXXXXXX, XXXXXXX,   RGB_SPD, RGB_VAD,   RGB_SPI),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │RST│M01│M02│M03│M04│M05│M06│M07│M08│M09│M10│M11│M12│ Power │F15│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │     │   │   │   │   │   │   │   │   │   │   │   │   │Sleep│   │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │      │   │   │   │   │   │   │   │   │   │   │   │ Debug  │   │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │        │   │   │   │Ver│   │   │   │   │   │   │      │M00│   │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
     * │    │    │    │          Wake          │    │    │ │M13│M14│M15│
     * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
     */
    [_FN3] = LAYOUT_65_ansi_blocker(
        QK_BOOT,  MC_1,     MC_2,    MC_3,    MC_4,    MC_5,    MC_6,    MC_7,    MC_8,    MC_9,    MC_10,   MC_11,     MC_12,   KC_PWR,    KC_F15,
        XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, KC_SLEP,   XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            DB_TOGG,   XXXXXXX,
        XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, KB_VRSN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, MC_0,      XXXXXXX,
        XXXXXXX,  XXXXXXX,           XXXXXXX,                   KC_WAKE,                            XXXXXXX, XXXXXXX,   MC_13,   MC_14,     MC_15)
};

#ifdef RGB_MATRIX_ENABLE

/*
 * RGB Stuff
 */

#ifdef RGBLIGHT_VAL_STEP
    #define RGB_BRIGHTER_BY RGBLIGHT_VAL_STEP
#else
    #define RGB_BRIGHTER_BY 26  // about 10%
#endif

#define LED_FLAG_ALPHA_KEY 0x10  // Alpha keys (for Caps Lock)
#define LED_FLAG_LAYER_IND 0x20  // Layer indicator

const uint8_t g_led_config_new_flags[RGB_MATRIX_LED_COUNT] = {
    // Extended LED Index to Flag
    // ** Remember: on ID67 this is in reverse order
    0x21, 0x01, 0x01, 0x01, 0x01,                   0x04,             0x01,       0x01, 0x21,  // Spc row
    0x21, 0x01, 0x01, 0x04, 0x04, 0x04, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,       0x21,  // ZXC row
    0x21, 0x01,       0x04, 0x04, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x29,  // ASD row
    0x21, 0x04, 0x04, 0x04, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x21,  // QWE row
    0x21, 0x01, 0x04, 0x04, 0x04, 0x04, 0x24, 0x24, 0x24, 0x24, 0x04, 0x04, 0x04, 0x04, 0x21   // 123 row
};

#define ID67_CAPS_LOCK_KEY_INDEX 36  // position of Caps Lock key

bool isRGBOff = false;
bool isCapsBlink = false;
static uint16_t recording_timer;

void keyboard_pre_init_user(void) {
    // override `config.h` flags with new values
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) g_led_config.flags[i] = g_led_config_new_flags[i];
}

void keyboard_post_init_user(void) {
    isRGBOff = false;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    uint8_t v = MIN( rgblight_get_val() + RGB_BRIGHTER_BY, 0xFF );
    uint8_t current_layer = get_highest_layer(layer_state);

    // Caps Lock key stuff

    if (host_keyboard_led_state().caps_lock) {
        if (isRGBOff) {
            rgb_matrix_set_color(ID67_CAPS_LOCK_KEY_INDEX, v, v, v);  // white
        } else {
            // Caps Lock key/LED
            if (timer_elapsed(recording_timer) > 500) {
                isCapsBlink = !isCapsBlink;
                recording_timer = timer_read();
            }
            if (isCapsBlink) {
                rgb_matrix_set_color(ID67_CAPS_LOCK_KEY_INDEX, v, v, v);  // white
            }

            // Alpha keys/LEDs
            for (uint8_t i = led_min; i <= led_max; i++) {
                if ((g_led_config.flags[i] & LED_FLAG_ALPHA_KEY) != 0)  {
                    rgb_matrix_set_color(i, v, 0, 0);  //red
                }
            }
        }
    } else if (isRGBOff) {
        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;

        if ((g_led_config.flags[ID67_CAPS_LOCK_KEY_INDEX] & LED_FLAG_LAYER_IND) != 0) {
            switch (current_layer) {
                case _FN1: b = v; break;  // blue
                case _FN2: g = v; break;  // green
                case _FN3: r = v; break;  // red
            }
        }

        rgb_matrix_set_color(ID67_CAPS_LOCK_KEY_INDEX, r, g, b);  // off
    }

    // Layer indicator stuff

    switch (current_layer) {
        case _FN1:
            for (uint8_t i = led_min; i <= led_max; i++) {
                if ((g_led_config.flags[i] & LED_FLAG_LAYER_IND) != 0) {
                    rgb_matrix_set_color(i, 0, 0, v);  // blue
                }
            }
            break;

        case _FN2:
            for (uint8_t i = led_min; i <= led_max; i++) {
                if ((g_led_config.flags[i] & LED_FLAG_LAYER_IND) != 0) {
                    rgb_matrix_set_color(i, 0, v, 0);  // green
                }
            }
            break;

        case _FN3:
            for (uint8_t i = led_min; i <= led_max; i++) {
                if ((g_led_config.flags[i] & LED_FLAG_LAYER_IND) != 0) {
                    rgb_matrix_set_color(i, v, 0, 0);  // red
                }
            }
            break;

        default:
            if (isRGBOff) {
                // switch layer indicators off only if in OFF mode
                for (uint8_t i = led_min; i <= led_max; i++) {
                    if ((g_led_config.flags[i] & LED_FLAG_LAYER_IND) != 0) {
                        rgb_matrix_set_color(i, 0, 0, 0);  // red
                    }
                }
            }
            break;
    }
    return false;
}

#endif

/*
 * Mac Fn-key stuff
 */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        // handle RGB toggle key
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL:
                        isRGBOff = true;
                        rgb_matrix_set_flags(LED_FLAG_INDICATOR | LED_FLAG_LAYER_IND);
                        rgb_matrix_set_color_all(0, 0, 0);
                        break;
                    default:
                        isRGBOff = false;
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();  // turn the lights back on
                }
            }
            return false;

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
