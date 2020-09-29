
#pragma once

#ifdef RGB_MATRIX_ENABLE
    

  #define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
  // #define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
  // #define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
  // #define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
  // #define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 225  // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
  #define RGB_MATRIX_HUE_STEP 8
  #define RGB_MATRIX_SAT_STEP 8
  #define RGB_MATRIX_VAL_STEP 8
  #define RGB_MATRIX_SPD_STEP 10

   #define DISABLE_RGB_MATRIX_ALPHAS_MODS
//   #define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
//   #define DISABLE_RGB_MATRIX_BREATHING
//    #define DISABLE_RGB_MATRIX_BAND_SAT
//   #define DISABLE_RGB_MATRIX_BAND_VAL
//    #define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
//    #define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
//    #define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
//    #define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
//   #define DISABLE_RGB_MATRIX_CYCLE_ALL
   #define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT // POWER ISSUE!
//   #define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
   #define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
   #define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
//    #define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
   #define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
   #define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
//   #define DISABLE_RGB_MATRIX_DUAL_BEACON
//   #define DISABLE_RGB_MATRIX_RAINBOW_BEACON
//    #define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
//   #define DISABLE_RGB_MATRIX_RAINDROPS
//   #define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS

//   #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
//   #define DISABLE_RGB_MATRIX_TYPING_HEATMAP
//   #define DISABLE_RGB_MATRIX_DIGITAL_RAIN

//   #define RGB_MATRIX_KEYPRESSES  // reacts to keypresses

  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS

//   #define DISABLE_RGB_MATRIX_SPLASH
//   #define DISABLE_RGB_MATRIX_MULTISPLASH
//   #define DISABLE_RGB_MATRIX_SOLID_SPLASH
//   #define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH

//  #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_TYPING_HEATMAP
#endif


// num rgb_matrix_effects {
//     RGB_MATRIX_NONE = 0,
//     RGB_MATRIX_SOLID_COLOR = 1,     // Static single hue, no speed support
//     RGB_MATRIX_ALPHAS_MODS,         // Static dual hue, speed is hue for secondary hue
//     RGB_MATRIX_GRADIENT_UP_DOWN,    // Static gradient top to bottom, speed controls how much gradient changes
//     RGB_MATRIX_GRADIENT_LEFT_RIGHT,    // Static gradient left to right, speed controls how much gradient changes
//     RGB_MATRIX_BREATHING,           // Single hue brightness cycling animation
//     RGB_MATRIX_BAND_SAT,        // Single hue band fading saturation scrolling left to right
//     RGB_MATRIX_BAND_VAL,        // Single hue band fading brightness scrolling left to right
//     RGB_MATRIX_BAND_PINWHEEL_SAT,   // Single hue 3 blade spinning pinwheel fades saturation
//     RGB_MATRIX_BAND_PINWHEEL_VAL,   // Single hue 3 blade spinning pinwheel fades brightness
//     RGB_MATRIX_BAND_SPIRAL_SAT,     // Single hue spinning spiral fades saturation
//     RGB_MATRIX_BAND_SPIRAL_VAL,     // Single hue spinning spiral fades brightness
//     RGB_MATRIX_CYCLE_ALL,           // Full keyboard solid hue cycling through full gradient
//     RGB_MATRIX_CYCLE_LEFT_RIGHT,    // Full gradient scrolling left to right
//     RGB_MATRIX_CYCLE_UP_DOWN,       // Full gradient scrolling top to bottom
//     RGB_MATRIX_CYCLE_OUT_IN,        // Full gradient scrolling out to in
//     RGB_MATRIX_CYCLE_OUT_IN_DUAL,   // Full dual gradients scrolling out to in
//     RGB_MATRIX_RAINBOW_MOVING_CHEVRON,  // Full gradent Chevron shapped scrolling left to right
//     RGB_MATRIX_CYCLE_PINWHEEL,      // Full gradient spinning pinwheel around center of keyboard
//     RGB_MATRIX_CYCLE_SPIRAL,        // Full gradient spinning spiral around center of keyboard
//     RGB_MATRIX_DUAL_BEACON,         // Full gradient spinning around center of keyboard
//     RGB_MATRIX_RAINBOW_BEACON,      // Full tighter gradient spinning around center of keyboard
//     RGB_MATRIX_RAINBOW_PINWHEELS,   // Full dual gradients spinning two halfs of keyboard
//     RGB_MATRIX_RAINDROPS,           // Randomly changes a single key's hue
//     RGB_MATRIX_JELLYBEAN_RAINDROPS, // Randomly changes a single key's hue and saturation
// #if define(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
//     RGB_MATRIX_TYPING_HEATMAP,      // How hot is your WPM!
//     RGB_MATRIX_DIGITAL_RAIN,        // That famous computer simulation
// #endif
// #if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)
//     RGB_MATRIX_SOLID_REACTIVE_SIMPLE,   // Pulses keys hit to hue & value then fades value out
//     RGB_MATRIX_SOLID_REACTIVE,      // Static single hue, pulses keys hit to shifted hue then fades to current hue
//     RGB_MATRIX_SOLID_REACTIVE_WIDE       // Hue & value pulse near a single key hit then fades value out
//     RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE  // Hue & value pulse near multiple key hits then fades value out
//     RGB_MATRIX_SOLID_REACTIVE_CROSS      // Hue & value pulse the same column and row of a single key hit then fades value out
//     RGB_MATRIX_SOLID_REACTIVE_MULTICROSS // Hue & value pulse the same column and row of multiple key hits then fades value out
//     RGB_MATRIX_SOLID_REACTIVE_NEXUS      // Hue & value pulse away on the same column and row of a single key hit then fades value out
//     RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS // Hue & value pulse away on the same column and row of multiple key hits then fades value out
//     RGB_MATRIX_SPLASH,              // Full gradient & value pulse away from a single key hit then fades value out
//     RGB_MATRIX_MULTISPLASH,         // Full gradient & value pulse away from multiple key hits then fades value out
//     RGB_MATRIX_SOLID_SPLASH,        // Hue & value pulse away from a single key hit then fades value out
//     RGB_MATRIX_SOLID_MULTISPLASH,   // Hue & value pulse away from multiple key hits then fades value out
// #endif
//     RGB_MATRIX_EFFECT_MAX
// };