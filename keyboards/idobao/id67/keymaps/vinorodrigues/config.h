// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
 * IDOBAO ID67 Keymap for a ID67 Bestype, built for Mac use
 */

#pragma once

#ifdef RGB_MATRIX_ENABLE
    #define ID67_DISABLE_UNDERGLOW

    #ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
        #undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #endif
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200  // limits maximum brightness of LEDs to x out of 255

    //// #define RGB_MATRIX_KEYPRESSES

    // RGB Matrix config, nit-pick a few animations. "////" = already defined in base `config.h`, `#undef` disables it

    //// #define ENABLE_RGB_MATRIX_ALPHAS_MODS             // Static dual hue, speed is hue for secondary hue
    //// #define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN        // Static gradient top to bottom, speed controls how much gradient changes
    //// #define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT     // Static gradient left to right, speed controls how much gradient changes
    //// #define ENABLE_RGB_MATRIX_BREATHING               // Single hue brightness cycling animation
    //// #define ENABLE_RGB_MATRIX_BAND_SAT                // Single hue band fading saturation scrolling left to right
    //// #define ENABLE_RGB_MATRIX_BAND_VAL                // Single hue band fading brightness scrolling left to right
    //// #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT       // Single hue 3 blade spinning pinwheel fades saturation
    //// #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL       // Single hue 3 blade spinning pinwheel fades brightness
    //// #define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT         // Single hue spinning spiral fades saturation
    //// #define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL         // Single hue spinning spiral fades brightness
    //// #define ENABLE_RGB_MATRIX_CYCLE_ALL               // Full keyboard solid hue cycling through full gradient
    //// #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT        // Full gradient scrolling left to right
    //// #define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN           // Full gradient scrolling top to bottom
    //// #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN            // Full gradient scrolling out to in
    //// #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL       // Full dual gradients scrolling out to in
    //// #define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON  // Full gradient Chevron shaped scrolling left to right
    //// #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL          // Full gradient spinning pinwheel around center of keyboard
    //// #define ENABLE_RGB_MATRIX_CYCLE_SPIRAL            // Full gradient spinning spiral around center of keyboard
    //// #define ENABLE_RGB_MATRIX_DUAL_BEACON             // Full gradient spinning around center of keyboard
    //// #define ENABLE_RGB_MATRIX_RAINBOW_BEACON          // Full tighter gradient spinning around center of keyboard
    //// #define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS       // Full dual gradients spinning two halfs of keyboard
    //// #define ENABLE_RGB_MATRIX_RAINDROPS               // Randomly changes a single key's hue
    //// #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS     // Randomly changes a single key's hue and saturation
    //// #define ENABLE_RGB_MATRIX_HUE_BREATHING           // Hue shifts up a slight amount at the same time, then shifts back
    //// #define ENABLE_RGB_MATRIX_HUE_PENDULUM            // Hue shifts up a slight amount in a wave to the right, then back to the left
    //// #define ENABLE_RGB_MATRIX_HUE_WAVE                // Hue shifts up a slight amount and then back down in a wave to the right

    #undef ENABLE_RGB_MATRIX_PIXEL_RAIN
    #undef ENABLE_RGB_MATRIX_PIXEL_FLOW
    //// #undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL

    // don't need `#if`, animation modes themselves check defines
    // #if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
    //// #define ENABLE_RGB_MATRIX_TYPING_HEATMAP
    //// #define ENABLE_RGB_MATRIX_DIGITAL_RAIN
    // #endif

    // don't need `#if`, animation modes themselves check defines
    // #if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)
    //// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE     // Pulses keys hit to hue & value then fades value out
    //// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE            // Static single hue, pulses keys hit to shifted hue then fades to current hue
    //// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE       // Hue & value pulse near a single key hit then fades value out
    //// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE  // Hue & value pulse near multiple key hits then fades value out
    //// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS      // Hue & value pulse the same column and row of a single key hit then fades value out
    //// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS // Hue & value pulse the same column and row of multiple key hits then fades value out
    //// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS      // Hue & value pulse away on the same column and row of a single key hit then fades value out
    //// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS // Hue & value pulse away on the same column and row of multiple key hits then fades value out
    //// #define ENABLE_RGB_MATRIX_SPLASH                    // Full gradient & value pulse away from a single key hit then fades value out
    //// #define ENABLE_RGB_MATRIX_MULTISPLASH               // Full gradient & value pulse away from multiple key hits then fades value out
    //// #define ENABLE_RGB_MATRIX_SOLID_SPLASH              // Hue & value pulse away from a single key hit then fades value out
    //// #define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH         // Hue & value pulse away from multiple key hits then fades value out
    // #endif
#endif
