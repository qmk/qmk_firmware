/* Copyright 2023 Nebuleon
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
#include "process_default_layer.h"
#include "quantum.h"
#include "quantum_keycodes.h"

#if !defined(NO_ACTION_LAYER)

bool process_default_layer(uint16_t keycode, keyrecord_t *record) {
    if (IS_QK_PERSISTENT_DEF_LAYER(keycode) && !record->event.pressed) {
        uint8_t layer = QK_PERSISTENT_DEF_LAYER_GET_LAYER(keycode);
        set_single_persistent_default_layer(layer);
        return false;
    }

    return true;
}

#endif // !defined(NO_ACTION_LAYER)
