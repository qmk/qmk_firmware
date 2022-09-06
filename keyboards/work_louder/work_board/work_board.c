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
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (clockwise) {
        tap_code(KC_VOLD);
    } else {
        tap_code(KC_VOLU);
    }
    return true;
}
#endif

#ifdef OLED_DRIVER_ENABLE
#    ifdef RGB_MATRIX_ENABLE
#        error Cannot run OLED and Per Key RGB at the same time due to pin conflicts
#    endif
__attribute__((weak)) oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_90; }

__attribute__((weak)) void oled_task_user(void) {
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
}
#endif


#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {  49,  48,  47,  46,  45,  43,  42,  41,  40,  39,  38,  37},
    {  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36 },
    {  24,  23,  22,  21,  20,  19,  18,  17,  16,  15,  14,  13 },
    {   0,   1,   2,   3,   4,   5,   7,   8,   9,  10,  11,  12 },
}, {
    { 223,  63 }, { 203,  63 }, { 183,  63 }, { 162,  63 }, { 142,  63 }, { 122,  63 }, { 101,  63 }, {  81,  63 }, {  61,  63 }, {  40,  63 }, {  20,  63 }, {   0,  63 },
    {   0,  42 }, {  20,  42 }, {  40,  42 }, {  61,  42 }, {  81,  42 }, { 101,  42 }, { 122,  42 }, { 142,  42 }, { 162,  42 }, { 183,  42 }, { 203,  42 }, { 223,  42 },
    { 223,  21 }, { 203,  21 }, { 183,  21 }, { 162,  21 }, { 142,  21 }, { 122,  21 }, { 101,  21 }, {  81,  21 }, {  61,  21 }, {  40,  21 }, {  20,  21 }, {   0,  21 },
    {   0,   0 }, {  20,   0 }, {  40,   0 }, {  61,   0 }, {  81,   0 }, { 101,   0 }, { 122,   0 }, { 132,   0 }, { 142,   0 }, { 162,   0 }, { 183,   0 }, { 203,   0 }, { 223,   0 },
}, {
    1, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1, 4,4,4, 1, 1, 1, 1, 1
} };

#endif
