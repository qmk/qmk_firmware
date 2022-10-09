/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
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
#include "bb-underglow.h"

/* UNDERGLOW IMPLEMENTATION
 */

// Define the layer switching code

// An empty layer on the base
const rgblight_segment_t PROGMEM bb_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 0, HSV_WHITE}
);
// Gaming layer is turquoise
const rgblight_segment_t PROGMEM bb_game_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {RGBLIGHT_LEFT_BEG, RGBLIGHT_LEFT_NUM, HSV_PURPLE}
);
// Character overlay is chartereuse
const rgblight_segment_t PROGMEM bb_char_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_GOLD}
);

// Right-hand layers

// Media layer is orange
const rgblight_segment_t PROGMEM bb_medi_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {RGBLIGHT_RIGHT_BEG, RGBLIGHT_RIGHT_NUM, HSV_MAGENTA}
);
// Navigation layer is green
const rgblight_segment_t PROGMEM bb_navi_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {RGBLIGHT_RIGHT_BEG, RGBLIGHT_RIGHT_NUM, HSV_GREEN}
);
// Symbol layer is purple
const rgblight_segment_t PROGMEM bb_symb_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {RGBLIGHT_RIGHT_BEG, RGBLIGHT_RIGHT_NUM, HSV_YELLOW}
);

// Left-hand layers

// Number layer is blue
const rgblight_segment_t PROGMEM bb_numb_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {RGBLIGHT_LEFT_BEG, RGBLIGHT_LEFT_NUM, HSV_BLUE}
);
// Function layer is red
const rgblight_segment_t PROGMEM bb_func_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {RGBLIGHT_LEFT_BEG, RGBLIGHT_LEFT_NUM, HSV_RED}
);
// Pointer layer is yellow
const rgblight_segment_t PROGMEM bb_mous_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {RGBLIGHT_LEFT_BEG, RGBLIGHT_LEFT_NUM, HSV_SPRINGGREEN}
);

// Music playback layer is magenta
const rgblight_segment_t PROGMEM bb_musi_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, HSV_ORANGE}
);

const rgblight_segment_t* const PROGMEM bb_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    bb_base_layer,
    bb_char_layer,
    bb_game_layer,
    bb_medi_layer,
    bb_navi_layer,
    bb_symb_layer,
    bb_numb_layer,
    bb_func_layer,
    bb_mous_layer,
    bb_musi_layer
);

// Enable the LED switching layers
void keyboard_post_init_underglow(void) {
    rgblight_layers = bb_rgb_layers;
    // Default rgb mode is rainbow swirl; set this
    rgblight_sethsv_noeeprom(100, 255, 255);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL + 0);
}

// Set RGBLIGHT state depending on layer
layer_state_t layer_state_set_underglow(layer_state_t state) {
    // Activate layers if on that region
    rgblight_set_layer_state(_BASE, layer_state_cmp(state, _BASE));
    rgblight_set_layer_state(_GAME, layer_state_cmp(state, _GAME));
    rgblight_set_layer_state(_CHAR, layer_state_cmp(state, _CHAR));
    rgblight_set_layer_state(_MEDI, layer_state_cmp(state, _MEDI));
    rgblight_set_layer_state(_NAVI, layer_state_cmp(state, _NAVI));
    rgblight_set_layer_state(_SYMB, layer_state_cmp(state, _SYMB));
    rgblight_set_layer_state(_NUMB, layer_state_cmp(state, _NUMB));
    rgblight_set_layer_state(_FUNC, layer_state_cmp(state, _FUNC));
    rgblight_set_layer_state(_MOUS, layer_state_cmp(state, _MOUS));
    rgblight_set_layer_state(_MUSI, layer_state_cmp(state, _MUSI));
    // Return so other stuff can be done
    return state;
}

// Hook into shutdown code
void shutdown_underglow(void) {
    // Make the LED's red on shutdown
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv(HSV_WHITE);
}
