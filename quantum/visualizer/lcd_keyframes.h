/* Copyright 2017 Fred Sundvik
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

#ifndef QUANTUM_VISUALIZER_LCD_KEYFRAMES_H_
#define QUANTUM_VISUALIZER_LCD_KEYFRAMES_H_

#include "visualizer.h"

// Displays the layer text centered vertically on the screen
bool lcd_keyframe_display_layer_text(keyframe_animation_t* animation, visualizer_state_t* state);
// Displays a bitmap (0/1) of all the currently active layers
bool lcd_keyframe_display_layer_bitmap(keyframe_animation_t* animation, visualizer_state_t* state);
// Displays a bitmap (0/1) of all the currently active mods
bool lcd_keyframe_display_mods_bitmap(keyframe_animation_t* animation, visualizer_state_t* state);
// Displays the keyboard led states (CAPS (Caps lock), NUM (Num lock), SCRL (Scroll lock), COMP (Compose), KANA)
bool lcd_keyframe_display_led_states(keyframe_animation_t* animation, visualizer_state_t* state);
// Displays both the layer text and the led states
bool lcd_keyframe_display_layer_and_led_states(keyframe_animation_t* animation, visualizer_state_t* state);
// Displays the QMK logo on the LCD screen
bool lcd_keyframe_draw_logo(keyframe_animation_t* animation, visualizer_state_t* state);

bool lcd_keyframe_disable(keyframe_animation_t* animation, visualizer_state_t* state);
bool lcd_keyframe_enable(keyframe_animation_t* animation, visualizer_state_t* state);


#endif /* QUANTUM_VISUALIZER_LCD_KEYFRAMES_H_ */
