// Copyright 2021 br (@b-)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


#define MODS_SHIFT  (get_mods() & MOD_MASK_SHIFT)
#define MODS_CTRL   (get_mods() & MOD_MASK_CTRL)
#define MODS_ALT    (get_mods() & MOD_MASK_ALT)

// #define IS_COMMAND() (get_mods() == MOD_MASK_SHIFT)      // Key combination that allows the use of magic commands (useful for debugging)

// #define NO_DEBUG                    			// Disable debugging
// #define NO_PRINT                    			// Disable printing/debugging using hid_listen
// #define NO_ACTION_LAYER             			// Disable layers
// #define NO_ACTION_TAPPING           			// Disable tap dance and other tapping features
// #define NO_ACTION_ONESHOT           			// Disable one-shot modifiers
// #define NO_ACTION_MACRO             			// Disable old style macro handling: MACRO() & action_get_macro
// #define TERMINAL_HELP
// #define MOUSEKEY_INTERVAL 20
// #define MOUSEKEY_DELAY 0
// #define MOUSEKEY_TIME_TO_MAX 60
// #define MOUSEKEY_MAX_SPEED 10
// #define MOUSEKEY_WHEEL_DELAY 0
//#define FORCE_NKRO                  			// NKRO by default requires to be turned on, this forces it on during keyboard startup regardless of EEPROM setting. NKRO can still be turned off but will be turned on again if the keyboard reboots.
// #define STRICT_LAYER_RELEASE        			// Force a key release to be evaluated using the current layer stack instead of remembering which layer it came from (used for advanced cases)
// #define LOCKING_SUPPORT_ENABLE      			// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
// #define LOCKING_RESYNC_ENABLE       			// Tries to keep switch state consistent with keyboard LED state
// #define TAPPING_TERM 200            			// How long before a tap becomes a hold, if set above 500, a key tapped during the tapping term will turn it into a hold too
// #define TAPPING_TERM_PER_KEY        			// Enabling to allow to tweak individual keys
// #define RETRO_TAPPING               			// Tap anyway, even after TAPPING_TERM, if there was no other key interruption between press and release
// #define TAPPING_TOGGLE 2            			// How many taps before triggering the toggle
// #define PERMISSIVE_HOLD             			// Makes tap and hold keys trigger the hold if another key is pressed before releasing, even if it hasn't hit the TAPPING_TERM. See Permissive Hold for details
// #define QUICK_TAP_TERM 0          			// Makes it possible to use a dual role key as modifier shortly after having been tapped. See Hold after tap. Breaks any Tap Toggle functionality (TT or the One Shot Tap Toggle)
// #define LEADER_TIMEOUT 300          			// How long before the leader key times out. If you're having issues finishing the sequence before it times out, you may need to increase the timeout setting. Or you may want to enable the LEADER_PER_KEY_TIMING option, which resets the timeout after each key is tapped.
// #define LEADER_PER_KEY_TIMING       			// Sets the timer for leader key chords to run on each key press rather than overall
// #define LEADER_KEY_STRICT_KEY_PROCESSING    	// Disables keycode filtering for Mod-Tap and Layer-Tap keycodes. Eg, if you enable this, you would need to specify MT(MOD_CTL, KC_A) if you want to use KC_A.
// #define ONESHOT_TIMEOUT 3000         		// How long before oneshot times out
// #define ONESHOT_TAP_TOGGLE 2        			// How many taps before oneshot toggle is triggered
// #define COMBO_TERM 200              			// How long for the Combo keys to be detected. Defaults to TAPPING_TERM if not defined.
// #define TAP_CODE_DELAY 100          			// Sets the delay between register_code and unregister_code, if you're having issues with it registering properly (common on VUSB boards). The value is in milliseconds.
#define TAP_CODE_DELAY 25          			// Sets the delay between register_code and unregister_code, if you're having issues with it registering properly (common on VUSB boards). The value is in milliseconds.
// #define TAP_HOLD_CAPS_DELAY 80      			// Sets the delay for Tap Hold keys (LT, MT) when using KC_CAPS_LOCK keycode, as this has some special handling on MacOS.  The value is in milliseconds, and defaults to 80 ms if not defined. For macOS, you may want to set this to 200 or higher.
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES         			// reacts to keypresses
// #define RGB_MATRIX_KEYRELEASES        		// reacts to keyreleases (instead of keypresses)



//Teal and Blue
//#define RGB_MATRIX_DEFAULT_HUE 127 			// Default boot color
//#define RGB_MATRIX_DEFAULT_SPD 47 			// Used to determine the color for the modifiers

//Teal and Blue
//#define RGB_MATRIX_DEFAULT_HUE 120 			// Default boot color
//#define RGB_MATRIX_DEFAULT_SPD 50 			//Used to determine the color for the modifiers


//QMK HSV is based on 255 value wheel rather than 360

//Cyan and Yellow
//#define RGB_MATRIX_DEFAULT_HUE 127 			// Default boot color
//#define RGB_MATRIX_DEFAULT_SPD 177

//Cyan and Green
//#define RGB_MATRIX_DEFAULT_HUE 127 			// Default boot color
//#define RGB_MATRIX_DEFAULT_SPD 215

// #define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS

#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_REACTIVE  	// Sets the default mode, if none has been set
#define RGB_MATRIX_DEFAULT_HUE 180  //purple  alphas with green background when pressed.

// This list in in the correct mode order. Next mode is the following line, previous mode is previous line. Loops around.
#define ENABLE_RGB_MATRIX_ALPHAS_MODS
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_BAND_SAT
#define ENABLE_RGB_MATRIX_BAND_VAL
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#define ENABLE_RGB_MATRIX_DUAL_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define ENABLE_RGB_MATRIX_RAINDROPS
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define ENABLE_RGB_MATRIX_HUE_BREATHING
#define ENABLE_RGB_MATRIX_HUE_PENDULUM
#define ENABLE_RGB_MATRIX_HUE_WAVE
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#define ENABLE_RGB_MATRIX_PIXEL_RAIN

#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN

#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
