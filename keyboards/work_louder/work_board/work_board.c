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

#include "quantum.h"

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
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    rgb_matrix_set_color(5, 0, 0, 0);
    rgb_matrix_set_color(7, 0, 0, 0);
    return true;
}

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(B2);
    gpio_set_pin_output(B3);
    gpio_set_pin_output(B7);

    gpio_write_pin_low(B2);
    gpio_write_pin_low(B3);
    gpio_write_pin_low(B7);

    keyboard_pre_init_user();
}

#endif
