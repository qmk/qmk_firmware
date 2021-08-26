/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "matrix.h"
#include "bootloader.h"
#include "debug.h"
#include "keymap.h"
#include "host.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "bootmagic.h"

/** \brief Scan Keycode
 *
 * FIXME: needs doc
 */
static bool scan_keycode(uint8_t keycode) {
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        matrix_row_t matrix_row = matrix_get_row(r);
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            if (matrix_row & ((matrix_row_t)1 << c)) {
                if (keycode == keymap_key_to_keycode(0, (keypos_t){.row = r, .col = c})) {
                    return true;
                }
            }
        }
    }
    return false;
}

/** \brief Bootmagic Scan Keycode
 *
 * FIXME: needs doc
 */
static bool bootmagic_scan_keycode(uint8_t keycode) {
    if (!scan_keycode(BOOTMAGIC_KEY_SALT)) return false;

    return scan_keycode(keycode);
}

void bootmagic(void) {
    /* do scans in case of bounce */
    print("bootmagic scan: ... ");
    uint8_t scan = 100;
    while (scan--) {
        matrix_scan();
        wait_ms(10);
    }
    print("done.\n");

    /* bootmagic skip */
    if (bootmagic_scan_keycode(BOOTMAGIC_KEY_SKIP)) {
        return;
    }

    /* eeconfig clear */
    if (bootmagic_scan_keycode(BOOTMAGIC_KEY_EEPROM_CLEAR)) {
        eeconfig_init();
    }

    /* bootloader */
    if (bootmagic_scan_keycode(BOOTMAGIC_KEY_BOOTLOADER)) {
        bootloader_jump();
    }

    if (bootmagic_scan_keycode(BOOTMAGIC_KEY_DEBUG_ENABLE)) {
        if (bootmagic_scan_keycode(BOOTMAGIC_KEY_DEBUG_MATRIX)) {
            debug_config.matrix = !debug_config.matrix;
        } else if (bootmagic_scan_keycode(BOOTMAGIC_KEY_DEBUG_KEYBOARD)) {
            debug_config.keyboard = !debug_config.keyboard;
        } else if (bootmagic_scan_keycode(BOOTMAGIC_KEY_DEBUG_MOUSE)) {
            debug_config.mouse = !debug_config.mouse;
        } else {
            debug_config.enable = !debug_config.enable;
        }
    }
    eeconfig_update_debug(debug_config.raw);

    if (bootmagic_scan_keycode(BOOTMAGIC_KEY_SWAP_CONTROL_CAPSLOCK)) {
        keymap_config.swap_control_capslock = !keymap_config.swap_control_capslock;
    }
    if (bootmagic_scan_keycode(BOOTMAGIC_KEY_CAPSLOCK_TO_CONTROL)) {
        keymap_config.capslock_to_control = !keymap_config.capslock_to_control;
    }
    if (bootmagic_scan_keycode(BOOTMAGIC_KEY_SWAP_LALT_LGUI)) {
        keymap_config.swap_lalt_lgui = !keymap_config.swap_lalt_lgui;
    }
    if (bootmagic_scan_keycode(BOOTMAGIC_KEY_SWAP_RALT_RGUI)) {
        keymap_config.swap_ralt_rgui = !keymap_config.swap_ralt_rgui;
    }
    if (bootmagic_scan_keycode(BOOTMAGIC_KEY_NO_GUI)) {
        keymap_config.no_gui = !keymap_config.no_gui;
    }
    if (bootmagic_scan_keycode(BOOTMAGIC_KEY_SWAP_GRAVE_ESC)) {
        keymap_config.swap_grave_esc = !keymap_config.swap_grave_esc;
    }
    if (bootmagic_scan_keycode(BOOTMAGIC_KEY_SWAP_BACKSLASH_BACKSPACE)) {
        keymap_config.swap_backslash_backspace = !keymap_config.swap_backslash_backspace;
    }
    if (bootmagic_scan_keycode(BOOTMAGIC_HOST_NKRO)) {
        keymap_config.nkro = !keymap_config.nkro;
    }
    eeconfig_update_keymap(keymap_config.raw);

    /* default layer */
    uint8_t default_layer = 0;
    if (bootmagic_scan_keycode(BOOTMAGIC_KEY_DEFAULT_LAYER_0)) {
        default_layer |= (1 << 0);
    } else if (bootmagic_scan_keycode(BOOTMAGIC_KEY_DEFAULT_LAYER_1)) {
        default_layer |= (1 << 1);
    } else if (bootmagic_scan_keycode(BOOTMAGIC_KEY_DEFAULT_LAYER_2)) {
        default_layer |= (1 << 2);
    } else if (bootmagic_scan_keycode(BOOTMAGIC_KEY_DEFAULT_LAYER_3)) {
        default_layer |= (1 << 3);
    } else if (bootmagic_scan_keycode(BOOTMAGIC_KEY_DEFAULT_LAYER_4)) {
        default_layer |= (1 << 4);
    } else if (bootmagic_scan_keycode(BOOTMAGIC_KEY_DEFAULT_LAYER_5)) {
        default_layer |= (1 << 5);
    } else if (bootmagic_scan_keycode(BOOTMAGIC_KEY_DEFAULT_LAYER_6)) {
        default_layer |= (1 << 6);
    } else if (bootmagic_scan_keycode(BOOTMAGIC_KEY_DEFAULT_LAYER_7)) {
        default_layer |= (1 << 7);
    }
    eeconfig_update_default_layer(default_layer);

    /* EE_HANDS handedness */
    if (bootmagic_scan_keycode(BOOTMAGIC_KEY_EE_HANDS_LEFT)) {
        eeconfig_update_handedness(true);
    } else if (bootmagic_scan_keycode(BOOTMAGIC_KEY_EE_HANDS_RIGHT)) {
        eeconfig_update_handedness(false);
    }
}
