/*
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
#include "rhruiz.h"
#include "ortho_5x14.c"

const hue_sat_pair hue_sat_pairs[] = {[_FN1] = {2, 255}, [_FN2] = {200, 255}, [_CFG] = {80, 255}, [_NUM] = {45, 255}};

void matrix_scan_user(void) { rhruiz_update_layer_colors(layer_state); }

bool rhruiz_is_layer_indicator_led(uint8_t index) { return index == RGBLED_NUM - 1 || index == RGBLED_NUM / 2; }

void rhruiz_update_layer_colors(layer_state_t state) {
    if (biton32(state) < 1UL) {
        return;
    }

    const hue_sat_pair hs = hue_sat_pairs[biton32(layer_state)];

    rhruiz_change_leds_to(hs.hue, hs.sat);
}
