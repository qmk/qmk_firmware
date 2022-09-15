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
__attribute__((weak)) uint16_t keycode_config(uint16_t keycode) {
    switch (keycode) {
        case QK_BASIC ... QK_MODS_MAX: /* 0x0000 ... 0x1fff*/
            /* basic keycodes and keycodes with extra modifiers */
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:   /* 0x4000 ... 0x4fff */
        case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX: /* 0x5600 ... 0x56ff */
            /* the low byte might also contain some special values, but
             * these values should not be changed by the magic settings
             */
        case QK_MOD_TAP ... QK_MOD_TAP_MAX: /* 0x6000 ... 0x7fff */
            break;
        default:
            return keycode;
    }
    /* only the low byte of keycode swapped depending on the magic settings */
    uint16_t keycode_mask = keycode & 0xff00;
    switch (keycode & 0x00ff) {
        case KC_CAPS_LOCK:
        case KC_LOCKING_CAPS_LOCK:
            if (keymap_config.swap_control_capslock || keymap_config.capslock_to_control) {
                return KC_LEFT_CTRL | keycode_mask;
            } else if (keymap_config.swap_escape_capslock) {
                return KC_ESCAPE | keycode_mask;
            }
            return keycode;
        case KC_LEFT_CTRL:
            if (keymap_config.swap_control_capslock) {
                return KC_CAPS_LOCK | keycode_mask;
            }
            if (keymap_config.swap_lctl_lgui) {
                if (keymap_config.no_gui) {
                    return KC_NO | keycode_mask;
                }
                return KC_LEFT_GUI | keycode_mask;
            }
            return keycode;
        case KC_LEFT_ALT:
            if (keymap_config.swap_lalt_lgui) {
                if (keymap_config.no_gui) {
                    return KC_NO | keycode_mask;
                }
                return KC_LEFT_GUI | keycode_mask;
            }
            return keycode;
        case KC_LEFT_GUI:
            if (keymap_config.swap_lalt_lgui) {
                return KC_LEFT_ALT | keycode_mask;
            }
            if (keymap_config.swap_lctl_lgui) {
                return KC_LEFT_CTRL | keycode_mask;
            }
            if (keymap_config.no_gui) {
                return KC_NO | keycode_mask;
            }
            return keycode;
        case KC_RIGHT_CTRL:
            if (keymap_config.swap_rctl_rgui) {
                if (keymap_config.no_gui) {
                    return KC_NO | keycode_mask;
                }
                return KC_RIGHT_GUI | keycode_mask;
            }
            return keycode;
        case KC_RIGHT_ALT:
            if (keymap_config.swap_ralt_rgui) {
                if (keymap_config.no_gui) {
                    return KC_NO | keycode_mask;
                }
                return KC_RIGHT_GUI | keycode_mask;
            }
            return keycode;
        case KC_RIGHT_GUI:
            if (keymap_config.swap_ralt_rgui) {
                return KC_RIGHT_ALT | keycode_mask;
            }
            if (keymap_config.swap_rctl_rgui) {
                return KC_RIGHT_CTRL | keycode_mask;
            }
            if (keymap_config.no_gui) {
                return KC_NO | keycode_mask;
            }
            return keycode;
        case KC_GRAVE:
            if (keymap_config.swap_grave_esc) {
                return KC_ESCAPE | keycode_mask;
            }
            return keycode;
        case KC_ESCAPE:
            if (keymap_config.swap_grave_esc) {
                return KC_GRAVE | keycode_mask;
            } else if (keymap_config.swap_escape_capslock) {
                return KC_CAPS_LOCK | keycode_mask;
            }
            return keycode;
        case KC_BACKSLASH:
            if (keymap_config.swap_backslash_backspace) {
                return KC_BACKSPACE | keycode_mask;
            }
            return keycode;
        case KC_BACKSPACE:
            if (keymap_config.swap_backslash_backspace) {
                return KC_BACKSLASH | keycode_mask;
            }
            return keycode;
        default:
            return keycode;
    }
}

/** \brief mod_config
 *
 *  This function checks the mods passed to it against the bootmagic config,
 *  and will remove or replace mods, based on that.
 */

__attribute__((weak)) uint8_t mod_config(uint8_t mod) {
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
