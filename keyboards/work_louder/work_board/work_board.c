/* Copyright 2021 Drashna Jael're
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

#include "work_board.h"

#if !defined(VIA_ENABLE) && defined(ENCODER_ENABLE)
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    if (clockwise) {
        tap_code(KC_VOLD);
    } else {
        tap_code(KC_VOLU);
    }
    return true;
}
#endif

#ifdef OLED_ENABLE
#    ifdef RGB_MATRIX_ENABLE
#        error Cannot run OLED and Per Key RGB at the same time due to pin conflicts
#    endif
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_90;
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    oled_write_P(PSTR("LAYER"), false);
    oled_write_P(PSTR("Lower"), layer_state_is(3));
    oled_write_P(PSTR("Raise"), layer_state_is(4));
    oled_write_P(PSTR("Adjst"), layer_state_is(5));

    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(PSTR("Lock:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_usb_state.num_lock);
    oled_write_P(PSTR("C"), led_usb_state.caps_lock);
    oled_write_ln_P(PSTR("S"), led_usb_state.scroll_lock);

    uint8_t modifiers = get_mods() | get_oneshot_mods();
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));

    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    oled_write_P(PSTR("BTMGK"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][0], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][0], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][1], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][1], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" NKRO"), keymap_config.nkro);

    return false;
}
#endif

#ifdef RGB_MATRIX_ENABLE
// clang-format off
led_config_t g_led_config = { {
    { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48 },
    { 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25 },
    { 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 },
    { 12, 11, 10,  9,  8,  7,  5,  4,  3,  2,  1,  0}
}, {
    { 223,  63 }, { 203,  63 }, { 183,  63 }, { 162,  63 }, { 142,  63 }, { 122,  63 }, { 112,  63 }, { 101,  63 }, {  81,  63 }, {  61,  63 }, {  40,  63 }, {  20,  63 }, {   0,  63 },
    {   0,  42 }, {  20,  42 }, {  40,  42 }, {  61,  42 }, {  81,  42 }, { 101,  42 }, { 122,  42 }, { 142,  42 }, { 162,  42 }, { 183,  42 }, { 203,  42 }, { 223,  42 },
    { 223,  21 }, { 203,  21 }, { 183,  21 }, { 162,  21 }, { 142,  21 }, { 122,  21 }, { 101,  21 }, {  81,  21 }, {  61,  21 }, {  40,  21 }, {  20,  21 }, {   0,  21 },
    {   0,   0 }, {  20,   0 }, {  40,   0 }, {  61,   0 }, {  81,   0 }, { 101,   0 }, { 122,   0 }, { 142,   0 }, { 162,   0 }, { 183,   0 }, { 203,   0 }, { 223,   0 }
}, {
    1, 1, 1, 1, 1, 4,4,4, 1, 1, 1, 1, 1,
    1, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 1
} };
// clang-format on

__attribute__((weak)) void rgb_matrix_indicators_user(void) {
#    ifdef VIA_ENABLE
    static bool     layout_2u = false;
    static uint16_t timer = 0;
    if (timer_elapsed(timer) > 500) {
        timer     = timer_read();
        layout_2u = (bool)via_get_layout_options();
    }
    if (layout_2u) {
        rgb_matrix_set_color(5, 0, 0, 0);
        rgb_matrix_set_color(7, 0, 0, 0);
    } else {
        rgb_matrix_set_color(6, 0, 0, 0);
    }
#    else
    rgb_matrix_set_color(5, 0, 0, 0);
    rgb_matrix_set_color(7, 0, 0, 0);
#    endif
}

void keyboard_pre_init_kb(void) {
    setPinOutput(B2);
    setPinOutput(B3);
    setPinOutput(B7);

    writePinLow(B2);
    writePinLow(B3);
    writePinLow(B7);

    keyboard_pre_init_user();
}

#endif
