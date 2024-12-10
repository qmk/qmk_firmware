// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     *   /─────/       /─────/─────/─────/─────/─────/─────/─────/─────/─────/─────/
     *  /Esc  /       /F1   /F2   /F3   /F4   /F5   /F6   /F7   /F8   /F9   /F10  /
     * /─────/       /─────/─────/─────/─────/─────/─────/─────/─────/─────/─────/
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│ │Ins│Hom│PgU│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │ │Del│End│PgD│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │    Shift │     │ ↑ │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐
     * │Ctrl│GUI │Alt │                        │ Alt│ Fn │Menu│Ctrl│ │ ← │ ↓ │ → │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘
     */
    [0] = LAYOUT_tkl_ansi(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,

        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_DEL,  KC_END,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,             KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1)  , KC_APP,  KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /*
     *  /     /       /MyCmp/HomeP/Calc /Media/ ⏮  / ⏭  / ⏯   / ⏹   /Mute /     /
     *
     * │   │💡│   │   │   │   │   │   │   │   │   │   │   │       │ │   │   │V+ │
     * │     │   │🔆│   │   │   │   │   │   │   │   │   │   │BootL│ │   │   │V- │
     * │      │   │🔅│   │   │   │   │   │   │   │   │   │        │
     * │        │   │🎨│   │   │   │   │   │   │   │   │          │     │🗘 │
     * │    │    │    │                        │    │    │    │    │ │㉈ │🗘 │㉏ │
     */
    [1] = LAYOUT_tkl_ansi(
        _______,          KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, _______,

        _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU,
        _______, _______, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT, _______, _______, KC_VOLD,
        _______, _______, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          RGB_MOD,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) }
};
#endif

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        // 0     1     2     3     4     5     6     7     8     9    10    11    12    13    14    15    16    17    18    19    20
        0x20, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xBC, 0xBD, 0xBE, 0xBF,
        0x00
    };

   oled_write_P(qmk_logo, false);
   oled_write_pixel(126, 0, 1);
   oled_write_pixel(127, 0, 1);
   oled_write_pixel(126, 1, 1);
}

static const char PROGMEM caps_on[] = { 0x9C, 0x9D, 0x9E, 0x9F };
static const char PROGMEM caps_off[] = { 0xBC, 0xBD, 0xBE, 0xBF };

bool oled_task_user(void) {
    render_logo();

    bool caps = host_keyboard_led_state().caps_lock;

    if (caps) {
        oled_set_cursor(17, 3);
        oled_write(caps ? caps_on : caps_off, false);
    }
    return false;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    bool caps = host_keyboard_led_state().caps_lock;

    if (caps) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                rgb_matrix_set_color(i, RGB_RED);
            }
        }
    }

    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, RGB_GREEN);
                }
            }
        }
    }

    return false;
}
