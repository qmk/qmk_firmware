/* Copyright 2023 Clickety Split Ltd.
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
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    } else {
        return rotation;
    }
}

static void render_keylock_status(led_t led_state) {
    oled_write_P(PSTR("Lock: "), false);
    oled_write_P(PSTR("CAPS"), led_state.caps_lock);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("NUML"), led_state.num_lock);
    oled_write_P(PSTR(" "), false);
    oled_write_ln_P(PSTR("SCLK"), led_state.scroll_lock);
}

static void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Mods: "), false);
    oled_write_P(PSTR("Sft"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("Ctl"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("Alt"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("GUI"), (modifiers & MOD_MASK_GUI));
}

static void render_secondary_oled(void) {
    // Version Information
#if defined(KEYBOARD_clickety_split_leeloo_rev1)
    oled_write_P(PSTR("Leeloo v1\n\n"), false);
#else
    oled_write_P(PSTR("Leeloo v2\n\n"), false);
#endif
    
    oled_write_P(PSTR("Firmware: "), false);
    
#if defined(KEYBOARD_clickety_split_leeloo_rev1)
    oled_write_P(PSTR("v1.13"), false);
#else
    oled_write_P(PSTR("v2.13"), false);
#endif
    
    oled_write_P(PSTR("\n"), false);
    oled_write_P(PSTR("Clickety Split Ltd."), false);
}

static void render_status(void) {
    // Host Keyboard Layer Status
    switch (get_highest_layer(default_layer_state)) {
        case 0:
            oled_write_P(PSTR("QWERTY | "), false);
            break;
    }

    // Host Keyboard Layer Status
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Base   \n"), false);
            break;

        case 1:
            oled_write_P(PSTR("Lower   \n"), false);
            break;

        case 2:
            oled_write_P(PSTR("Raise   \n"), false);
            break;

        case 3:
            oled_write_P(PSTR("Adjust  \n"), false);
            break;

        default:
            oled_write_P(PSTR("Unknown \n"), false);
    }

    oled_write_P(PSTR("\n"), false);
    render_keylock_status(host_keyboard_led_state());
    render_mod_status(get_mods() | get_oneshot_mods());
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false; 
    }

    if (is_keyboard_master()) {
        // Renders the current keyboard state (layer, lock, caps, scroll, etc)
        render_status();
    } else {
        // Version Information
        render_secondary_oled();
    }

    return false;

}
#endif // OLED_ENABLE

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code_delay(KC_VOLD, 10);
        } else {
            tap_code_delay(KC_VOLU, 10);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}
#endif // ENCODER_ENABLE
