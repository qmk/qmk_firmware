/* Copyright 2025 TS Design Works LLC
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

 /*******************************************************************************
  * KEYBOARD CORE SETTINGS
  ******************************************************************************/
 // Debounce configuration
 #define DEBOUNCE 5                     // 5ms for better key chatter prevention
 
 // Dynamic macro configuration
 #define DYNAMIC_MACRO_EEPROM_STORAGE   // Enable dynamic macro storage in EEPROM
 #define DYNAMIC_MACRO_SIZE 256         // Larger macro size
 
 // Buffer Sizes
 #define SERIAL_BUFFER_SIZE 64          // Serial buffer size for communication
 
 /*******************************************************************************
  * POWER MANAGEMENT
  ******************************************************************************/
 #define USB_SUSPEND_WAKEUP_DELAY 200   // Delay for waking from suspend
 
 /*******************************************************************************
  * RGB MATRIX CONFIGURATION
  ******************************************************************************/
 // Basic configuration
 #define RGB_MATRIX_LED_COUNT 104       // Total number of LEDs in the RGB matrix
 #define RGB_MATRIX_TIMEOUT 300000      // Auto turn-off RGB after 5 minutes of inactivity
 #define RGB_MATRIX_SLEEP                // Disable RGB effects when the keyboard is suspended
 
 // Performance optimization
 #define RGB_MATRIX_LED_PROCESS_LIMIT ((RGB_MATRIX_LED_COUNT + 7) / 8) // Optimized processing limit
 #define RGB_MATRIX_LED_FLUSH_LIMIT 16  // Moderate flush limit to reduce CPU usage
 #define RGB_MATRIX_KEYRELEASES         // Reactive effects respond to key releases
 
 // Brightness and default settings
 #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200  // Cap maximum brightness to 200/255
 #define RGB_MATRIX_DEFAULT_SPD 100         // Default animation speed
 #define RGB_MATRIX_DEFAULT_VAL 128         // Default brightness value (50%)
 #define RGB_MATRIX_DEFAULT_HUE 0           // Default hue (red)
 
 // Startup configuration
 #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR  // Default startup mode
 #define RGB_MATRIX_STARTUP_HUE 85       // Green color on startup
 #define RGB_MATRIX_STARTUP_SAT 255      // Full saturation
 #define RGB_MATRIX_STARTUP_VAL 128      // Medium brightness on startup
 
 /*******************************************************************************
  * TYPING HEATMAP CONFIGURATION
  ******************************************************************************/
 #define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50  // Delay before heatmap cools down
 #define RGB_MATRIX_TYPING_HEATMAP_SPREAD 40             // Spread of heatmap effect to surrounding keys
 #define RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT 16         // Limit heat intensity for surrounding keys
 #define RGB_MATRIX_TYPING_HEATMAP_INCREASE_STEP 32      // Keystroke count for fully heating a key
 
 /*******************************************************************************
  * ENABLED RGB MATRIX EFFECTS
  ******************************************************************************/
 // Basic effects
 #define ENABLE_RGB_MATRIX_SOLID_COLOR
 #define ENABLE_RGB_MATRIX_BREATHING
 
 // Gradient effects
 #define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
 #define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
 
 // Cycling effects
 #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
 #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
 #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
 #define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
 
 // Moving effects
 #define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
 #define ENABLE_RGB_MATRIX_RAINBOW_BEACON
 #define ENABLE_RGB_MATRIX_RAINBOW
 #define ENABLE_RGB_MATRIX_RAINBOW_SWIRL
 #define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
 
 // Reactive effects
 #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
 #define ENABLE_RGB_MATRIX_SOLID_REACTIVE
 #define ENABLE_RGB_MATRIX_SPLASH
 #define ENABLE_RGB_MATRIX_MULTISPLASH
 #define ENABLE_RGB_MATRIX_SOLID_SPLASH
 
 // Special effects
 #define ENABLE_RGB_MATRIX_RAINDROPS
 #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
 #define ENABLE_RGB_MATRIX_TYPING_HEATMAP
 #define ENABLE_RGB_MATRIX_DIGITAL_RAIN
 #define ENABLE_RGB_MATRIX_EFFECT_PIXEL_RAIN