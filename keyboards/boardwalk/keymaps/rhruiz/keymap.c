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

#ifdef RGBLIGHT_LAYERS
const rgblight_segment_t PROGMEM fn1_colors[] = RGBLIGHT_LAYER_SEGMENTS({0, 7, 2, 255, 255});

const rgblight_segment_t PROGMEM fn2_colors[] = RGBLIGHT_LAYER_SEGMENTS({0, 7, 200, 255, 255});

const rgblight_segment_t PROGMEM cfg_colors[] = RGBLIGHT_LAYER_SEGMENTS({0, 7, 80, 255, 255});

const rgblight_segment_t PROGMEM num_colors[] = RGBLIGHT_LAYER_SEGMENTS({0, 7, 45, 255, 255});

const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST(fn1_colors, fn2_colors, cfg_colors, num_colors);
#else
const hue_sat_pair hue_sat_pairs[] = {[_FN1] = {2, 255}, [_FN2] = {200, 255}, [_CFG] = {80, 255}, [_NUM] = {45, 255}};

bool rhruiz_is_layer_indicator_led(uint8_t index) { return index >= RGBLED_NUM / 2; }
#endif

void rhruiz_update_layer_colors(layer_state_t state) {
#ifdef RGBLIGHT_LAYERS
    rgblight_set_layer_state(0, layer_state_cmp(state, _FN1));
    rgblight_set_layer_state(1, layer_state_cmp(state, _FN2));
    rgblight_set_layer_state(2, layer_state_cmp(state, _CFG));
    rgblight_set_layer_state(3, layer_state_cmp(state, _NUM));
#else
    if (biton32(state) < _FN1) {
        rhruiz_rgblight_reset();
        return;
    }

    const hue_sat_pair hs = hue_sat_pairs[biton32(state)];

    rhruiz_change_leds_to(hs.hue, hs.sat);
#endif
}

#ifdef RGBLIGHT_LAYERS
void keyboard_post_init_keymap(void) {
    rgblight_layers = _rgb_layers;
}
#endif
