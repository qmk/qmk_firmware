/* Copyright 2024-2025 Grigory Avdyushin
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

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0x00, 0x0A, 0x0A
    };

    oled_write_P(qmk_logo, false);
}

static void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("MODS:"), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_ln_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
    oled_write_ln_P(PSTR(" "), false);
}

static void render_layer_state(void) {
    oled_write_ln_P(PSTR(" "), false);
    oled_write_P("BASE ", layer_state_is(0));
    oled_write_P("LOWER", layer_state_is(1));
    oled_write_P("RAISE", layer_state_is(2));
    oled_write_P("NAV  ", layer_state_is(3));
    oled_write_ln_P(PSTR(" "), false);
}

static void render_capsword_state(bool on) {
    oled_write_ln_P("CAPSW", on);
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    render_logo();
    render_layer_state();
    render_mod_status(get_mods() | get_oneshot_mods());
    render_capsword_state(is_caps_word_on());
    return false;
}

 #endif
