/* Copyright 2019 Thomas Baart
 * Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#ifdef HAPTIC_ENABLE
#    include "haptic.h"
extern haptic_config_t haptic_config;
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_4x3( /* Base */
        KC_MUTE, TG(1),   TG(2),
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,
        KC_P1,   KC_P2,   KC_P3
    ),
    [1] = LAYOUT_ortho_4x3( /* Layer 1 */
        QK_BOOT, _______, XXXXXXX,
        AU_ON,   AU_OFF,  XXXXXXX,
        CK_TOGG, XXXXXXX, CK_UP,
        CK_RST,  XXXXXXX, CK_DOWN
    ),
    [2] = LAYOUT_ortho_4x3( /* Layer 2*/
        RGB_TOG, RGB_MOD, _______,
        RGB_HUI, RGB_SAI, RGB_VAI,
        RGB_HUD, RGB_SAD, RGB_VAD,
        HF_TOGG, HF_FDBK, HF_CONT
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { { KC_DOWN, KC_UP   } },
    [1] = { { KC_VOLD, KC_VOLU } },
    [2] = { { RGB_MOD, RGB_RMOD} },
};
#endif
// clang-format on

static bool     is_asleep = false;
static uint32_t oled_timer;

void render_oled_logo(void) {
    // clang-format off
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
    // clang-format on
    oled_write_ln_P(qmk_logo, false);
}

void render_user_status(void) {
    static const char PROGMEM audio_status[2][3] = {{0xE0, 0xE1, 0}, {0xE2, 0xE3, 0}};
    oled_write_P(audio_status[is_audio_on()], false);
    static const char PROGMEM audio_clicky_status[2][3] = {{0xF4, 0xF5, 0}, {0xF6, 0xF7, 0}};
    oled_write_P(audio_clicky_status[is_clicky_on() && is_audio_on()], false);
    static const char PROGMEM rgb_layer_status[2][3] = {{0xEE, 0xEF, 0}, {0xF0, 0xF1, 0}};
    oled_write_P(rgb_layer_status[rgblight_is_enabled()], false);
    static const char PROGMEM nukem_good[2][3] = {{0xF8, 0xF9, 0}, {0xF6, 0xF7, 0}};
    oled_write_P(nukem_good[0], haptic_config.enable);
}

void keyboard_post_init_user(void) { oled_scroll_set_speed(0); }

bool oled_task_user(void) {
    if (is_asleep) {
        oled_off();
        return false;;
    }

    if (timer_elapsed32(oled_timer) < 30000) {
        oled_on();
        oled_scroll_off();
        oled_write_P(PSTR("SplitKB's Zima"), false);
        char layer[2] = {0};
        uint8_t n        = get_highest_layer(layer_state);
        layer[1]         = '\0';
        layer[0]         = '0' + n % 10;
        oled_write_P(PSTR("   L:"), false);
        oled_write_ln(layer, false);
        oled_write_ln_P(PSTR("--------------"), false);
        if (rgblight_is_enabled()) {
            oled_write_P(PSTR("HSV: "), false);
            char hsv_char[4];
            n           = rgblight_get_hue();
            hsv_char[3] = '\0';
            hsv_char[2] = '0' + n % 10;
            hsv_char[1] = (n /= 10) % 10 ? '0' + (n) % 10 : (n / 10) % 10 ? '0' : ' ';
            hsv_char[0] = n / 10 ? '0' + n / 10 : ' ';
            oled_write(hsv_char, false);
            oled_write_P(PSTR(", "), false);
            n           = rgblight_get_sat();
            hsv_char[3] = '\0';
            hsv_char[2] = '0' + n % 10;
            hsv_char[1] = (n /= 10) % 10 ? '0' + (n) % 10 : (n / 10) % 10 ? '0' : ' ';
            hsv_char[0] = n / 10 ? '0' + n / 10 : ' ';
            oled_write(hsv_char, false);
            oled_write_P(PSTR(", "), false);
            n           = rgblight_get_val();
            hsv_char[3] = '\0';
            hsv_char[2] = '0' + n % 10;
            hsv_char[1] = (n /= 10) % 10 ? '0' + (n) % 10 : (n / 10) % 10 ? '0' : ' ';
            hsv_char[0] = n / 10 ? '0' + n / 10 : ' ';
            oled_write_ln(hsv_char, false);
        } else {
            oled_write_ln_P(PSTR("RGB LIGHT DISABLED"), false);
        }
        render_user_status();
    } else {
        if (timer_elapsed32(oled_timer) < 120000) {
            oled_on();
            render_oled_logo();
            oled_scroll_right();
        } else {
            oled_off();
        }
    }
    return false;
}

void suspend_power_down_user(void) { is_asleep = true; }

void suspend_wakeup_init_user(void) { is_asleep = false; }

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    oled_timer = timer_read32();

    return true;
}
