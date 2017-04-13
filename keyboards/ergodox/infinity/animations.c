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

#if defined(VISUALIZER_ENABLE)

#include "animations.h"
#include "visualizer.h"
#ifdef LCD_ENABLE
#include "lcd_keyframes.h"
#endif
#ifdef LCD_BACKLIGHT_ENABLE
#include "lcd_backlight_keyframes.h"
#endif

#ifdef LED_ENABLE
#include "led_keyframes.h"
#endif

#include "visualizer_keyframes.h"


#if defined(LCD_ENABLE) && defined(LCD_BACKLIGHT_ENABLE)

// Don't worry, if the startup animation is long, you can use the keyboard like normal
// during that time
keyframe_animation_t default_startup_animation = {
    .num_frames = 4,
    .loop = false,
    .frame_lengths = {0, 0, 0, gfxMillisecondsToTicks(5000), 0},
    .frame_functions = {
            lcd_keyframe_enable,
            backlight_keyframe_enable,
            lcd_keyframe_draw_logo,
            backlight_keyframe_animate_color,
    },
};

keyframe_animation_t default_suspend_animation = {
    .num_frames = 4,
    .loop = false,
    .frame_lengths = {0, gfxMillisecondsToTicks(1000), 0, 0},
    .frame_functions = {
            lcd_keyframe_display_layer_text,
            backlight_keyframe_animate_color,
            lcd_keyframe_disable,
            backlight_keyframe_disable,
    },
};
#endif

#if defined(LED_ENABLE)
#define CROSSFADE_TIME 1000
#define GRADIENT_TIME 3000

keyframe_animation_t led_test_animation = {
    .num_frames = 14,
    .loop = true,
    .frame_lengths = {
        gfxMillisecondsToTicks(1000), // fade in
        gfxMillisecondsToTicks(1000), // no op (leds on)
        gfxMillisecondsToTicks(1000), // fade out
        gfxMillisecondsToTicks(CROSSFADE_TIME), // crossfade
        gfxMillisecondsToTicks(GRADIENT_TIME), // left to rigt (outside in)
        gfxMillisecondsToTicks(CROSSFADE_TIME), // crossfade
        gfxMillisecondsToTicks(GRADIENT_TIME), // top_to_bottom
        0,           // mirror leds
        gfxMillisecondsToTicks(CROSSFADE_TIME), // crossfade
        gfxMillisecondsToTicks(GRADIENT_TIME), // left_to_right (mirrored, so inside out)
        gfxMillisecondsToTicks(CROSSFADE_TIME), // crossfade
        gfxMillisecondsToTicks(GRADIENT_TIME), // top_to_bottom
        0,           // normal leds
        gfxMillisecondsToTicks(CROSSFADE_TIME), // crossfade

    },
    .frame_functions = {
        led_keyframe_fade_in_all,
        keyframe_no_operation,
        led_keyframe_fade_out_all,
        led_keyframe_crossfade,
        led_keyframe_left_to_right_gradient,
        led_keyframe_crossfade,
        led_keyframe_top_to_bottom_gradient,
        led_keyframe_mirror_orientation,
        led_keyframe_crossfade,
        led_keyframe_left_to_right_gradient,
        led_keyframe_crossfade,
        led_keyframe_top_to_bottom_gradient,
        led_keyframe_normal_orientation,
        led_keyframe_crossfade,
    },
};
#endif

#endif
