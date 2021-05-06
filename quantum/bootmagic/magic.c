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

keymap_config_t keymap_config;

__attribute__((weak)) void bootmagic(void) {}

/** \brief Magic
 *
 * FIXME: Needs doc
 */
void magic(void) {
    /* check signature */
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }

    /* init globals */
    debug_config.raw  = eeconfig_read_debug();
    keymap_config.raw = eeconfig_read_keymap();

    bootmagic();

    /* read here just incase bootmagic process changed its value */
    layer_state_t default_layer = (layer_state_t)eeconfig_read_default_layer();
    default_layer_set(default_layer);

    /* Also initialize layer state to trigger callback functions for layer_state */
    layer_state_set_kb((layer_state_t)layer_state);
}
