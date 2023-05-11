/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#include "drashna.h"

// clang-format off
#define LAYOUT_split_3x5_2_wrapper(...) LAYOUT_split_3x5_2(__VA_ARGS__)
#define LAYOUT_split_3x5_2_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
    ) \
    LAYOUT_split_3x5_2 ( \
       K01,    K02,      K03,     K04,     K05,                K06,     K07,     K08,     K09,     K0A, \
       ALT_T(K11), K12,  K13,     K14,     GUI_T(K15),  LGUI_T(K16),    K17,     K18,     K19, LALT_T(K1A), \
       CTL_T(K21), K22,  K23,     K24,     K25,                K26,     K27,     K28,     K29, RCTL_T(K2A), \
                              KC_SPC,  BK_LWER,              DL_RAIS, RSFT_T(KC_ENT) \
    )

#define LAYOUT_split_3x5_2_base_wrapper(...)       LAYOUT_split_3x5_2_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DEFAULT_LAYER_1] = LAYOUT_split_3x5_2_base_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),

    [_DEFAULT_LAYER_2] = LAYOUT_split_3x5_2_base_wrapper(
        ______________COLEMAK_MOD_DH_L1____________, ______________COLEMAK_MOD_DH_R1____________,
        ______________COLEMAK_MOD_DH_L2____________, ______________COLEMAK_MOD_DH_R2____________,
        ______________COLEMAK_MOD_DH_L3____________, ______________COLEMAK_MOD_DH_R3____________
    ),
    [_DEFAULT_LAYER_3] = LAYOUT_split_3x5_2_base_wrapper(
        _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
        _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
        _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
    ),

    [_DEFAULT_LAYER_4] = LAYOUT_split_3x5_2_base_wrapper(
        _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
        _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
        _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
    ),

    [_MOUSE] = LAYOUT_split_3x5_2(
        _______, _______, _______, _______, _______,    KC_WH_U, DPI_RMOD,DPI_MOD, S_D_RMOD,S_D_MOD,
        _______, _______, _______, _______, _______,    KC_WH_D, KC_BTN1, KC_BTN3, KC_BTN2, KC_BTN6,
        _______, _______, _______, _______, _______,    KC_BTN7, KC_BTN4, KC_BTN5, KC_BTN8, _______,
                                    SNIPING, _______,    _______, _______
    ),
    [_LOWER] = LAYOUT_split_3x5_2_wrapper(
        _________________LOWER_L1__________________,    _________________LOWER_R1__________________,
        _________________LOWER_L2__________________,    _________________LOWER_R2__________________,
        _________________LOWER_L3__________________,    _________________LOWER_R3__________________,
                                   _______, _______,    _______, AUTO_CTN
    ),
    [_RAISE] = LAYOUT_split_3x5_2_wrapper(
        _________________RAISE_L1__________________,    _________________RAISE_R1__________________,
        _________________RAISE_L2__________________,    _________________RAISE_R2__________________,
        _________________RAISE_L3__________________,    _________________RAISE_R3__________________,
                                   _______, _______,    _______, _______
    ),
    [_ADJUST] = LAYOUT_split_3x5_2_wrapper(
        _________________ADJUST_L1_________________,    _________________ADJUST_R1_________________,
        _________________ADJUST_L2_________________,    _________________ADJUST_R2_________________,
        _________________ADJUST_L3_________________,    _________________ADJUST_R3_________________,
                                   KC_NUKE, _______,    _______, QK_BOOT
    ),
};


void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    for (int32_t i = 0; i < 40; i++) {
        __asm__ volatile("nop" ::: "memory");
    }
}


#if defined(OLED_ENABLE) && defined(OLED_DISPLAY_128X128)
#    ifdef UNICODE_COMMON_ENABLE
#        include "process_unicode_common.h"
#        include "keyrecords/unicode.h"
#    endif

extern const char PROGMEM display_border[3];


extern uint32_t oled_timer;
extern bool is_oled_enabled;


bool oled_task_keymap(void) {
    static const char PROGMEM header_image[] = {
        0, 192, 32, 16, 8, 4, 2, 1, 1, 1, 1, 1, 1, 1, 1, 3, 7, 15, 31, 63, 127, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 127, 63, 31, 15, 7, 3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 4, 8, 16, 32, 192, 0,
        //         0,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  7, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0
    };
    oled_write_raw_P(header_image, sizeof(header_image));
    oled_set_cursor(7, 0);
    oled_write_P(PSTR("Dilemma"), true);

    render_default_layer_state(1, 1);
    render_layer_state(1, 2);
    render_kitty(0, 5);
    render_wpm(1, 7, 5);
#   if defined(POINTING_DEVICE_ENABLE)
    render_pointing_dpi_status(dilemma_get_pointer_sniping_enabled() ? dilemma_get_pointer_sniping_dpi() : dilemma_get_pointer_default_dpi(), 1, 7, 6);
    render_mouse_mode(17, 6);
#    elif defined(WPM_ENABLE) && defined(DEBUG_MATRIX_SCAN_RATE)
    render_matrix_scan_rate(1, 7, 6);
#    endif
    render_bootmagic_status(7, 7);
    render_user_status(1, 9);

    render_mod_status(get_mods() | get_oneshot_mods(), 1, 10);
    render_keylock_status(host_keyboard_led_state(), 1, 11);
    render_unicode_mode(1, 12);

//    render_rgb_hsv(1, 13);
    oled_set_cursor(1, 13);
    oled_write_P(PSTR("OS: "), false);
    extern os_variant_t os_type;
        switch (os_type) {
            case OS_LINUX:
                oled_write_ln_P(PSTR("Linux"), false);
                break;
            case OS_WINDOWS:
                oled_write_ln_P(PSTR("Windows"), false);
                break;
            case OS_MACOS:
                oled_write_ln_P(PSTR("MacOS"), false);
                break;
            case OS_IOS:
                oled_write_ln_P(PSTR("iOS"), false);
                break;
            default:
                break;
        }

    render_keylogger_status(1, 14);

    for (uint8_t i = 1; i < 15; i++) {
        oled_set_cursor(0, i);
        oled_write_raw_P(display_border, sizeof(display_border));
        oled_set_cursor(21, i);
        oled_write_raw_P(display_border, sizeof(display_border));
    }

    static const char PROGMEM footer_image[] = {0, 3, 4, 8, 16, 32, 64, 128, 128, 128, 128, 128, 128, 128, 192, 224, 240, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 240, 224, 192, 128, 128, 128, 128, 128, 128, 128, 64, 32, 16, 8, 4, 3, 0};
    oled_set_cursor(0, 15);
    oled_write_raw_P(footer_image, sizeof(footer_image));

    return false;
}
#endif


#ifdef SWAP_HANDS_ENABLE
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    /* Left hand, matrix positions */
    {{0, 4}, {3, 4}, {2, 4}, {5, 4}, {4, 4}},
    {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}},
    {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}},
    {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}},
    /* Right hand, matrix positions */
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}},
    {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}},
    {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}},
    {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}},
    };
#endif
