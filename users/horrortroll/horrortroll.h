/* Copyright 2023 HorrorTroll <https://github.com/HorrorTroll>
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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
    _BASE,
    _FN,
};

enum custom_keycodes {
    //Custom Gradient control keycode
    G1_HUI = SAFE_RANGE, //Custom gradient color 1 hue increase
    G1_HUD,              //Custom gradient color 1 hue decrease
    G1_SAI,              //Custom gradient color 1 saturation increase
    G1_SAD,              //Custom gradient color 1 saturation decrease
    G1_VAI,              //Custom gradient color 1 value increase
    G1_VAD,              //Custom gradient color 1 value decrease
    G2_HUI,              //Custom gradient color 2 hue increase
    G2_HUD,              //Custom gradient color 2 hue decrease
    G2_SAI,              //Custom gradient color 2 saturation increase
    G2_SAD,              //Custom gradient color 2 saturation decrease
    G2_VAI,              //Custom gradient color 2 value increase
    G2_VAD,              //Custom gradient color 2 value decrease
    G_PRE,               //Gradient presets
    REF_G,               //Toggle between linear and reflected gradient
    G_FLIP,              //Flip the gradient colors
  
    //Custom led effect keycode
    RGB_C_E,             //Cycle user effect
};
