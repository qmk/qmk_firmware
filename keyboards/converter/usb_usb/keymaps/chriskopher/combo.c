/* Copyright 2020 Christopher Ko <chriskopher@gmail.com>
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

#include "shared_enum.h"

#include "quantum.h"

enum combo_event {
    SD_LAYER_COMBO,
    KL_MEH_COMBO,
};

const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};  // Combo: S + D for SuperDuper mode
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};  // Combo: K + L for Meh modifier

// Register the combo action
combo_t key_combos[COMBO_COUNT] = {
    [SD_LAYER_COMBO] = COMBO_ACTION(sd_combo),
    [KL_MEH_COMBO]   = COMBO_ACTION(kl_combo),
};

// Called after a combo event is triggered
void process_combo_event(uint8_t combo_index, bool pressed) {
    switch (combo_index) {
        case SD_LAYER_COMBO:
            if (pressed) {
                layer_on(_SUPERDUPER);
            } else {
                layer_off(_SUPERDUPER);
            }
            break;

        case KL_MEH_COMBO:
            if (pressed) {
                register_mods(MOD_MEH);
            } else {
                unregister_mods(MOD_MEH);
            }
            break;
    }
}
