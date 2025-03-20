// Copyright 2024-2025 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file palettefx.h
 * @brief PaletteFx community module: Add more colors to your keyboard
 *
 *
 * For full documentation, see
 * <https://getreuer.info/posts/keyboards/palettefx>
 */

#pragma once

#include <stdint.h>
#include "color.h"
#include "palettefx_default_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Gets the color data for the selected palette. */
const uint16_t* palettefx_get_palette_data(void);

/** Gets the color data for the ith palette. */
const uint16_t* palettefx_get_palette_data_by_index(uint8_t i);

/** Returns the number of palettes. */
uint8_t palettefx_num_palettes(void);

/**
 * @brief Computes the interpolated HSV palette color at 0 <= x < 256.
 *
 * Looks up and linearly interpolates `palette` at 0 <= x < 256. The color
 * saturation and value are scaled according to rgb_matrix_config.
 *
 * @note `palette` must point to a PROGMEM address.
 *
 * @param palette Pointer to PROGMEM of a size-16 table of HSV16 colors.
 * @param x       Palette lookup position, a value in 0-255.
 * @return HSV color.
 */
hsv_t palettefx_interp_color(const uint16_t* palette, uint8_t x);

/**
 * @brief Compute a scaled 16-bit time that wraps smoothly.
 *
 * Computes `timer` scaled by `scale`, returning the result as a uint16.
 * Generally, the scaled time would have a discontinuity every ~65 seconds when
 * `timer` wraps 16-bit range. This is corrected for to wrap smoothly mod 2^16.
 *
 * @param timer A 32-bit timer.
 * @param scale Scale value in 0-255.
 * @return Scaled time.
 */
uint16_t palettefx_scaled_time(uint32_t timer, uint8_t scale);

// The following enum constants may be used to refer to PaletteFx palettes by
// name. To set a particular palette programmatically, do e.g.
//
//     void keyboard_post_init_user(void) {
//       uint8_t i = PALETTEFX_CARNIVAL;  // Set Carnival palette at startup.
//       rgb_matrix_sethsv_noeeprom(RGB_MATRIX_HUE_STEP * i, 255, 255);
//     }
//
// If you have defined additional palettes in palettefx_user.inc, they may be
// referred to by `PALETTEFX_USER_0`, `PALETTEFX_USER_1`, etc.
enum {
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_AFTERBURN_ENABLE)
  PALETTEFX_AFTERBURN,
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_AMBER_ENABLE)
  PALETTEFX_AMBER,
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_BADWOLF_ENABLE)
  PALETTEFX_BADWOLF,
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_CARNIVAL_ENABLE)
  PALETTEFX_CARNIVAL,
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_CLASSIC_ENABLE)
  PALETTEFX_CLASSIC,
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_DRACULA_ENABLE)
  PALETTEFX_DRACULA,
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_GROOVY_ENABLE)
  PALETTEFX_GROOVY,
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_NOTPINK_ENABLE)
  PALETTEFX_NOTPINK,
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_PHOSPHOR_ENABLE)
  PALETTEFX_PHOSPHOR,
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_POLARIZED_ENABLE)
  PALETTEFX_POLARIZED,
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_ROSEGOLD_ENABLE)
  PALETTEFX_ROSEGOLD,
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_SPORT_ENABLE)
  PALETTEFX_SPORT,
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_SYNTHWAVE_ENABLE)
  PALETTEFX_SYNTHWAVE,
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_THERMAL_ENABLE)
  PALETTEFX_THERMAL,
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_VIRIDIS_ENABLE)
  PALETTEFX_VIRIDIS,
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_WATERMELON_ENABLE)
  PALETTEFX_WATERMELON,
#endif
  PALETTEFX_USER_0,
  PALETTEFX_USER_1,
  PALETTEFX_USER_2,
  PALETTEFX_USER_3,
  PALETTEFX_USER_4,
  PALETTEFX_USER_5,
  PALETTEFX_USER_6,
  PALETTEFX_USER_7,
  PALETTEFX_USER_8,
  PALETTEFX_USER_9,
  PALETTEFX_USER_10,
  PALETTEFX_USER_11,
  PALETTEFX_USER_12,
  PALETTEFX_USER_13,
  PALETTEFX_USER_14,
  PALETTEFX_USER_15,
};

#ifdef __cplusplus
}
#endif

