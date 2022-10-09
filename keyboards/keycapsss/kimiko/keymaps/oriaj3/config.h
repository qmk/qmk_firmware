/* Copyright 2019 MechMerlin
 * Copyright 2020 @ben_roe (keycapsss.com)
 * Copyright 2022 @oriaj3
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

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define OLED_FONT_H "keyboards/keycapsss/kimiko/keymaps/rgb_matrix/glcdfont.c"
// #define OLED_FONT_WIDTH 5
// #define OLED_FONT_HEIGHT 7


#ifdef RGB_MATRIX_ENABLE

// The pin connected to the data pin of the LEDs
#define RGB_DI_PIN D3
// The number of LEDs connected
#define DRIVER_LED_TOTAL 60
#define RGBLED_NUM 60
#define RGB_MATRIX_SPLIT {30,30}
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_TRANSPORT_MIRROR


#   define RGB_MATRIX_KEYPRESSES // reacts to keypresses
// #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
// #   define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#   define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #   define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// #   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 80 // limits maximum brightness of LEDs to 80 out of 255. Higher may cause the controller to crash.
#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 8
#    define RGB_MATRIX_VAL_STEP 8
#    define RGB_MATRIX_SPD_STEP 10



//  ENABLES EFFECTS. See alls the effects -> https://github.com/samhocevar-forks/qmk-firmware/blob/master/docs/feature_rgb_matrix.md#rgb-matrix-effects
#   define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50
#   define ENABLE_RGB_MATRIX_BAND_SPLIT
#   define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#   define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#   define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
//#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
//#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
//#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
//#   define ENABLE_RGB_MATRIX_MULTISPLASH
//#   define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#  define ENABLE_RGB_MATRIX_SPLASH
#endif

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK
