/* Copyright 2016 Jack Humbert
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

#include "keycode_config.h"

extern keymap_config_t keymap_config;

/** \brief keycode_config
 *
 * This function is used to check a specific keycode against the bootmagic config,
 * and will return the corrected keycode, when appropriate.
 */
uint16_t keycode_config(uint16_t keycode) {
    switch (keycode) {
        case KC_CAPSLOCK:
        case KC_LOCKING_CAPS:
            if (keymap_config.swap_control_capslock || keymap_config.capslock_to_control) {
                return KC_LCTL;
            }
            return keycode;
        case KC_LCTL:
            if (keymap_config.swap_control_capslock) {
                return KC_CAPSLOCK;
            }
            if (keymap_config.swap_lctl_lgui) {
                if (keymap_config.no_gui) {
                    return KC_NO;
                }
                return KC_LGUI;
            }
            return KC_LCTL;
        case KC_LALT:
            if (keymap_config.swap_lalt_lgui) {
                if (keymap_config.no_gui) {
                    return KC_NO;
                }
                return KC_LGUI;
            }
            return KC_LALT;
        case KC_LGUI:
            if (keymap_config.swap_lalt_lgui) {
                return KC_LALT;
            }
            if (keymap_config.swap_lctl_lgui) {
                return KC_LCTRL;
            }
            if (keymap_config.no_gui) {
                return KC_NO;
            }
            return KC_LGUI;
        case KC_RCTL:
            if (keymap_config.swap_rctl_rgui) {
                if (keymap_config.no_gui) {
                    return KC_NO;
                }
                return KC_RGUI;
            }
            return KC_RCTL;
        case KC_RALT:
            if (keymap_config.swap_ralt_rgui) {
                if (keymap_config.no_gui) {
                    return KC_NO;
                }
                return KC_RGUI;
            }
            return KC_RALT;
        case KC_RGUI:
            if (keymap_config.swap_ralt_rgui) {
                return KC_RALT;
            }
            if (keymap_config.swap_rctl_rgui) {
                return KC_RCTL;
            }
            if (keymap_config.no_gui) {
                return KC_NO;
            }
            return KC_RGUI;
        case KC_GRAVE:
            if (keymap_config.swap_grave_esc) {
                return KC_ESC;
            }
            return KC_GRAVE;
        case KC_ESC:
            if (keymap_config.swap_grave_esc) {
                return KC_GRAVE;
            }
            return KC_ESC;
        case KC_BSLASH:
            if (keymap_config.swap_backslash_backspace) {
                return KC_BSPACE;
            }
            return KC_BSLASH;
        case KC_BSPACE:
            if (keymap_config.swap_backslash_backspace) {
                return KC_BSLASH;
            }
            return KC_BSPACE;
        default:
            return keycode;
    }
}

/** \brief mod_config
 *
 *  This function checks the mods passed to it against the bootmagic config,
 *  and will remove or replace mods, based on that.
 */

uint8_t mod_config(uint8_t mod) {
    if (keymap_config.swap_lalt_lgui) {
        if ((mod & MOD_RGUI) == MOD_LGUI) {
            mod &= ~MOD_LGUI;
            mod |= MOD_LALT;
        } else if ((mod & MOD_RALT) == MOD_LALT) {
            mod &= ~MOD_LALT;
            mod |= MOD_LGUI;
        }
    }
    if (keymap_config.swap_ralt_rgui) {
        if ((mod & MOD_RGUI) == MOD_RGUI) {
            mod &= ~MOD_RGUI;
            mod |= MOD_RALT;
        } else if ((mod & MOD_RALT) == MOD_RALT) {
            mod &= ~MOD_RALT;
            mod |= MOD_RGUI;
        }
    }
    if (keymap_config.swap_lctl_lgui) {
        if ((mod & MOD_RGUI) == MOD_LGUI) {
            mod &= ~MOD_LGUI;
            mod |= MOD_LCTL;
        } else if ((mod & MOD_RCTL) == MOD_LCTL) {
            mod &= ~MOD_LCTL;
            mod |= MOD_LGUI;
        }
    }
    if (keymap_config.swap_rctl_rgui) {
        if ((mod & MOD_RGUI) == MOD_RGUI) {
            mod &= ~MOD_RGUI;
            mod |= MOD_RCTL;
        } else if ((mod & MOD_RCTL) == MOD_RCTL) {
            mod &= ~MOD_RCTL;
            mod |= MOD_RGUI;
        }
    }
    if (keymap_config.no_gui) {
        mod &= ~MOD_LGUI;
        mod &= ~MOD_RGUI;
    }

    return mod;
}
