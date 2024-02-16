/* Copyright 2021 peepeetee
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
#pragma once


// #define MODS_SHIFT  (get_mods() & MOD_MASK_SHIFT)
// #define MODS_CTRL   (get_mods() & MOD_MASK_CTRL)
// #define MODS_ALT    (get_mods() & MOD_MASK_ALT)

// #define IS_COMMAND() (get_mods() == MOD_MASK_SHIFT)      // Key combination that allows the use of magic commands (useful for debugging)

// #define NO_DEBUG                    // Disable debugging
// #define NO_PRINT                    // Disable printing/debugging using hid_listen
// #define NO_ACTION_LAYER             // Disable layers
// #define NO_ACTION_TAPPING           // Disable tap dance and other tapping features
// #define NO_ACTION_ONESHOT           // Disable one-shot modifiers
// #define NO_ACTION_MACRO             // Disable old style macro handling: MACRO() & action_get_macro
// #define TERMINAL_HELP
// #define MOUSEKEY_INTERVAL 20
// #define MOUSEKEY_DELAY 0
// #define MOUSEKEY_TIME_TO_MAX 60
// #define MOUSEKEY_MAX_SPEED 10
// #define MOUSEKEY_WHEEL_DELAY 0
#define FORCE_NKRO                  // NKRO by default requires to be turned on, this forces it on during keyboard startup regardless of EEPROM setting. NKRO can still be turned off but will be turned on again if the keyboard reboots.
// #define STRICT_LAYER_RELEASE        // Force a key release to be evaluated using the current layer stack instead of remembering which layer it came from (used for advanced cases)
// #define LOCKING_SUPPORT_ENABLE      // Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
// #define LOCKING_RESYNC_ENABLE       // Tries to keep switch state consistent with keyboard LED state
 #define TAPPING_TERM 200            // How long before a tap becomes a hold, if set above 500, a key tapped during the tapping term will turn it into a hold too
// #define TAPPING_TERM_PER_KEY        // Enables handling for per key TAPPING_TERM settings
// #define RETRO_TAPPING               // Tap anyway, even after TAPPING_TERM, if there was no other key interruption between press and release
// #define TAPPING_TOGGLE 2            // How many taps before triggering the toggle
// #define PERMISSIVE_HOLD             // Makes tap and hold keys trigger the hold if another key is pressed before releasing, even if it hasn't hit the TAPPING_TERM. See Permissive Hold for details
// #define QUICK_TAP_TERM 0          // Makes it possible to use a dual role key as modifier shortly after having been tapped. See Hold after tap. Breaks any Tap Toggle functionality (TT or the One Shot Tap Toggle)
// #define LEADER_TIMEOUT 300          // How long before the leader key times out. If you're having issues finishing the sequence before it times out, you may need to increase the timeout setting. Or you may want to enable the LEADER_PER_KEY_TIMING option, which resets the timeout after each key is tapped.
// #define LEADER_PER_KEY_TIMING       // Sets the timer for leader key chords to run on each key press rather than overall
// #define LEADER_KEY_STRICT_KEY_PROCESSING    // Disables keycode filtering for Mod-Tap and Layer-Tap keycodes. Eg, if you enable this, you would need to specify MT(MOD_CTL, KC_A) if you want to use KC_A.
// #define ONESHOT_TIMEOUT 300         // How long before oneshot times out
// #define ONESHOT_TAP_TOGGLE 2        // How many taps before oneshot toggle is triggered
// #define COMBO_TERM 200              // How long for the Combo keys to be detected. Defaults to TAPPING_TERM if not defined.
// #define TAP_CODE_DELAY 100          // Sets the delay between register_code and unregister_code, if you're having issues with it registering properly (common on VUSB boards). The value is in milliseconds.
// #define TAP_HOLD_CAPS_DELAY 80      // Sets the delay for Tap Hold keys (LT, MT) when using KC_CAPS_LOCK keycode, as this has some special handling on MacOS.  The value is in milliseconds, and defaults to 80 ms if not defined. For macOS, you may want to set this to 200 or higher.

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES         // reacts to keypresses
// #define RGB_MATRIX_KEYRELEASES        // reacts to keyreleases (instead of keypresses)
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_ALPHAS_MODS // Sets the default mode, if none has been set
// #define RGBLIGHT_HUE_STEP 12        // Units to step when in/decreasing hue
// #define RGBLIGHT_SAT_STEP 25        // Units to step when in/decreasing saturation
// #define RGBLIGHT_VAL_STEP 12        // Units to step when in/decreasing value (brightness)
// #define RGB_MATRIX_SLEEP // turn off effects when suspended
// #define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// #define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)

// #define RGBLIGHT_EFFECT_BREATHE_CENTER              // If defined, used to calculate the curve for the breathing animation. Valid values are 1.0 to 2.7
// #define RGBLIGHT_EFFECT_BREATHE_MAX 255             // The maximum brightness for the breathing mode. Valid values are 1 to 255
// #define RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL 1000     // How long to wait between light changes for the "Christmas" animation, in milliseconds
// #define RGBLIGHT_EFFECT_CHRISTMAS_STEP 2            // The number of LEDs to group the red/green colors by for the "Christmas" animation
// #define RGBLIGHT_EFFECT_KNIGHT_LED_NUM RGBLED_NUM   // The number of LEDs to have the "Knight" animation travel
// #define RGBLIGHT_EFFECT_KNIGHT_LENGTH 3             // The number of LEDs to light up for the "Knight" animation
// #define RGBLIGHT_EFFECT_KNIGHT_OFFSET 0             // The number of LEDs to start the "Knight" animation from the start of the strip by
// #define RGBLIGHT_RAINBOW_SWIRL_RANGE 255            // Range adjustment for the rainbow swirl effect to get different swirls
// #define RGBLIGHT_EFFECT_SNAKE_LENGTH 4              // The number of LEDs to light up for the "Snake" animation

// This list in in the correct mode order. Next mode is the following line, previous mode is previous line. Loops around.
// #undef ENABLE_RGB_MATRIX_SOLID_COLOR                   // Static single hue, no speed support
// #undef ENABLE_RGB_MATRIX_ALPHAS_MODS                   // Static dual hue, speed is hue for secondary hue
#undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN     // Static gradient top to bottom, speed controls how much gradient changes
#undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT  // Static gradient top to bottom, speed controls how much gradient changes
#undef ENABLE_RGB_MATRIX_BREATHING            // Single hue brightness cycling animation
#undef ENABLE_RGB_MATRIX_BAND_SAT             // Single hue band fading saturation scrolling left to right
#undef ENABLE_RGB_MATRIX_BAND_VAL             // Single hue band fading brightness scrolling left to right
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT    // Single hue 3 blade spinning pinwheel fades saturation
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL    // Single hue 3 blade spinning pinwheel fades brightness
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT      // Single hue spinning spiral fades saturation
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL      // Single hue spinning spiral fades brightness
#undef ENABLE_RGB_MATRIX_CYCLE_ALL            // Full keyboard solid hue cycling through full gradient
//#undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT              // Full gradient scrolling left to right
#undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN           // Full gradient scrolling top to bottom
#undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON  // Full gradent Chevron shapped scrolling left to right
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN            // Full gradient scrolling out to in
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL       // Full dual gradients scrolling out to in
#undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL          // Full gradient spinning pinwheel around center of keyboard
#undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL            // Full gradient spinning spiral around center of keyboard
#undef ENABLE_RGB_MATRIX_DUAL_BEACON             // Full gradient spinning around center of keyboard
#undef ENABLE_RGB_MATRIX_RAINBOW_BEACON          // Full tighter gradient spinning around center of keyboard
#undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS       // Full dual gradients spinning two halfs of keyboard
#undef ENABLE_RGB_MATRIX_RAINDROPS               // Randomly changes a single key's hue
#undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS     // Randomly changes a single key's hue and saturation
// =================================================== Requires RGB_MATRIX_FRAMEBUFFER_EFFECTS =============================================================
// #undef ENABLE_RGB_MATRIX_TYPING_HEATMAP                // How hot is your WPM!
#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN               // That famous computer simulation
                                                    // =================================================== RGB_MATRIX_KEYPRESSES OR RGB_MATRIX_KEYRELEASES =====================================================
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE      // Pulses keys hit to hue & value then fades value out
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE             // Static single hue, pulses keys hit to shifted hue then fades to current hue
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE        // Hue & value pulse near a single key hit then fades value out
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE   // Hue & value pulse near multiple key hits then fades value out
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS       // Hue & value pulse the same column and row of a single key hit then fades value out
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS  // Hue & value pulse the same column and row of multiple key hits then fades value out
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS       // Hue & value pulse away on the same column and row of a single key hit then fades value out
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS  // Hue & value pulse away on the same column and row of multiple key hits then fades value out
#undef ENABLE_RGB_MATRIX_SPLASH                     // Full gradient & value pulse away from a single key hit then fades value out
#undef ENABLE_RGB_MATRIX_MULTISPLASH                // Full gradient & value pulse away from multiple key hits then fades value out
#undef ENABLE_RGB_MATRIX_SOLID_SPLASH               // Hue & value pulse away from a single key hit then fades value out
#undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH          // Hue & value pulse away from multiple key hits then fades value out
