// Copyright 2021 a (@trwnh on Github)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#ifdef RGB_MATRIX_ENABLE
	#define RGB_DISABLE_WHEN_USB_SUSPENDED

	#define RGB_MATRIX_FRAMEBUFFER_EFFECTS // Heatmap, Rain
	#define RGB_MATRIX_KEYPRESSES // REACTIVE, SPLASH modes

	// #undef ENABLE_RGB_MATRIX_SOLID_COLOR               // BUILT IN (MAPPED!) Static single color.
	#undef ENABLE_RGB_MATRIX_ALPHAS_MODS                // Accenting various keys on the keyboard.
	// #undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN           // Top down rainbow!
	// #undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT        // Left Right Rainbow (the top-down is better imho).
	// #undef ENABLE_RGB_MATRIX_BREATHING                  // Built in (MAPPED!)
	#undef ENABLE_RGB_MATRIX_BAND_SAT                   // Single hue band fading saturation scrolling left to right (with white)
	#undef ENABLE_RGB_MATRIX_BAND_VAL                   // Single hue band fading brightness scrolling left to right (with black)
	#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT          // Single hue 3 blade spinning pinwheel fades sat (RGB_MATRIX_CYCLE_PINWHEEL)
	#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL          // See above
	#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT            // See above
	#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL            // Single hue spinning spiral fades brightness (with black)
	#undef ENABLE_RGB_MATRIX_CYCLE_ALL                  // Full keyboard cycling through rainbow
	// #undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT           // BUILT IN (MAPPED!) Full Rainbow Left to Right
	// #undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN              // Full gradient scrolling top to bottom
	// #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN               // Rainbow circles coming to center.
	// #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL          // Two Rainbow circles coming to 1/3 and 2/3 points.
	#undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON     // Full gradent Chevron shapped scrolling left to right
	// #undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL             // BUILT IN (MAPPED!) - Consider disabling this - my poor eyes.
	// #undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL               // Full gradient spinning spiral around center of keyboard
	// #undef ENABLE_RGB_MATRIX_DUAL_BEACON                // Two rainbows spinning around keyboards
	// #undef ENABLE_RGB_MATRIX_RAINBOW_BEACON             // Similar to above.
	// #undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS          // Enough of the spinning rainbows - we get it! :-)
	#undef ENABLE_RGB_MATRIX_RAINDROPS                  // Jellybeans are better.
	#undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS        // Randomly changes a single key's hue and saturation - better than above.
	#undef ENABLE_RGB_MATRIX_HUE_BREATHING              // Hue shifts up a slight ammount at the same time, then shifts back
	#undef ENABLE_RGB_MATRIX_HUE_PENDULUM               // Hue shifts up a slight ammount in a wave to the right, then back to the left
	#undef ENABLE_RGB_MATRIX_HUE_WAVE                   // Hue shifts up a slight ammount and then back down in a wave to the right
	#undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL              // Single hue fractal filled keys pulsing horizontally out to edges
	#undef ENABLE_RGB_MATRIX_PIXEL_FLOW                 // Pulsing RGB flow along LED wiring with random hues
	#undef ENABLE_RGB_MATRIX_PIXEL_RAIN                 // Randomly light keys with random hues
	#undef ENABLE_RGB_MATRIX_TYPING_HEATMAP             // Hot keys!
	#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN               // The Matrix!
	#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE      // Key hits shown in current hue - all other keys black: wide slightly better imo
	// #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE             // Key hits shown in current hue - all other keys shifted hue
	// #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE        // Hue & value pulse around a single key hit then fades value out (black otherwise)
	#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE   // same as above but a bit too intense imo.
	#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS       // Column and Row single color fade.
	#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS  // Column and Row single color fade. (Multi-keys)
	#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS       // Hue & value pulse away on the same column and row of key hit then fades
	#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS  // Hue & value pulse away on the same column and row of multi-key hit then fades
	// #undef ENABLE_RGB_MATRIX_SPLASH                     // Full rainbow pulses from key hit. All else black.
	// #undef ENABLE_RGB_MATRIX_MULTISPLASH                // Full rainbow pulses from multi-keys. All else black.
	// #undef ENABLE_RGB_MATRIX_SOLID_SPLASH               // Single color pulses from key hit. All else black. (Using solid_reactive_wide instead).
	// #undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH          // Single color pulses from muli-keys. All else black. (Using solid_reactive_wide instead).
#endif