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
 * @file palettefx.c
 * @brief PaletteFx community module implementation
 *
 * For full documentation, see
 * <https://getreuer.info/posts/keyboards/palettefx>
 */

#include "palettefx.h"
#include "quantum.h"

#include <lib/lib8tion/lib8tion.h>

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 0, 0);

/**
 * @brief 16-bit HSV color.
 *
 * Represents a color with a 16-bit value in hue-saturation-value (HSV) space.
 * Components are packed as:
 *
 *  - Hue: lowest 8 bits.
 *  - Saturation: middle 4 bits.
 *  - Value: highest 4 bits.
 */
#define HSV16(h, s, v) ((((v) >> 4) << 12) | (((s) >> 4) << 8) | ((h) & 0xff))

/** Unpacks 16-bit HSV color to hsv_t. */
static hsv_t unpack_hsv16(uint16_t hsv16) {
  return (hsv_t){
    .h = (uint8_t)hsv16,
    .s = ((uint8_t)(hsv16 >> 8) & 0x0f) * 17,
    .v = ((uint8_t)(hsv16 >> 12) & 0x0f) * 17,
  };
}

/** PaletteFx palette color data. */
static const uint16_t palettefx_palettes[][16] PROGMEM = {
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_AFTERBURN_ENABLE)
  // "Afterburn" palette.
  {
    HSV16(139, 255,  85),
    HSV16(134, 255,  85),
    HSV16(131, 255, 102),
    HSV16(128, 255, 102),
    HSV16(127, 187, 102),
    HSV16(125, 119, 102),
    HSV16(124,  51, 102),
    HSV16(125,   0, 119),
    HSV16( 15,  17, 119),
    HSV16( 17,  51, 153),
    HSV16( 18, 102, 170),
    HSV16( 19, 153, 204),
    HSV16( 21, 187, 238),
    HSV16( 23, 238, 255),
    HSV16( 26, 255, 255),
    HSV16( 30, 255, 255),
  },
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_AMBER_ENABLE)
  // "Amber" palette.
  {
    HSV16(  5, 187, 170),
    HSV16( 15, 221, 170),
    HSV16( 22, 238, 187),
    HSV16( 23, 238, 187),
    HSV16( 25, 255, 204),
    HSV16( 27, 255, 221),
    HSV16( 29, 255, 238),
    HSV16( 29, 255, 255),
    HSV16( 28, 187, 255),
    HSV16( 30,  68, 255),
    HSV16( 32,  34, 255),
    HSV16( 32,  34, 255),
    HSV16( 26, 119, 255),
    HSV16( 24, 238, 255),
    HSV16( 21, 221, 255),
    HSV16( 16, 204, 255),
  },
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_BADWOLF_ENABLE)
  // "Bad Wolf" palette. Inspired by the Bad Wolf theme by Steve Losh, which is
  // distributed under MIT/X11 license.
  // https://github.com/sjl/badwolf/tree/61d75affa51d40213d671edc9c8ff83992d7fd6f
  {
    HSV16( 14,  34,   0),
    HSV16(245, 255, 255),
    HSV16(245, 255, 255),
    HSV16(245, 255, 255),
    HSV16( 14,  34,   0),
    HSV16( 14,  34,   0),
    HSV16( 14,  34,   0),
    HSV16( 14,  34,   0),
    HSV16( 14,  34,   0),
    HSV16( 14,  34,   0),
    HSV16( 24,  17, 136),
    HSV16( 28,   0, 255),
    HSV16( 24,  17, 136),
    HSV16( 14,  34,   0),
    HSV16( 14,  34,   0),
    HSV16( 14,  34,   0),
  },
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_CARNIVAL_ENABLE)
  // "Carnival" palette.
  {
    HSV16(132, 255,  85),
    HSV16(121, 187,  85),
    HSV16(108, 170, 102),
    HSV16( 90, 153, 119),
    HSV16( 70, 187, 136),
    HSV16( 57, 255, 153),
    HSV16( 50, 255, 187),
    HSV16( 44, 255, 204),
    HSV16( 39, 255, 238),
    HSV16( 32, 255, 255),
    HSV16( 27, 255, 255),
    HSV16( 22, 255, 255),
    HSV16( 18, 255, 255),
    HSV16(  8, 221, 238),
    HSV16(252, 204, 238),
    HSV16(241, 255, 221),
  },
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_CLASSIC_ENABLE)
  // "Classic" palette.
  {
    HSV16(150, 255,  85),
    HSV16(151, 238, 119),
    HSV16(160, 136, 119),
    HSV16(176, 102, 136),
    HSV16(193,  85, 136),
    HSV16(216,  85, 136),
    HSV16(234, 102, 153),
    HSV16(247, 119, 187),
    HSV16(  3, 153, 204),
    HSV16( 10, 204, 221),
    HSV16( 15, 255, 255),
    HSV16( 18, 255, 255),
    HSV16( 23, 255, 255),
    HSV16( 24, 204, 255),
    HSV16( 25, 136, 255),
    HSV16( 26,  85, 255),
  },
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_DRACULA_ENABLE)
  // "Dracula" palette. Inspired by the Dracula theme by Zeno Rocha, which is
  // distributed under MIT license.
  // https://github.com/dracula/dracula-theme/tree/ac4dc82dab2a3c35e5cac0cd80c97fbf4c2ca986
  {
    HSV16(165, 153, 119),
    HSV16(167, 153, 136),
    HSV16(170, 170, 187),
    HSV16(173, 170, 221),
    HSV16(177, 170, 238),
    HSV16(183, 170, 255),
    HSV16(190, 170, 255),
    HSV16(200, 153, 255),
    HSV16(216, 153, 255),
    HSV16(230, 170, 255),
    HSV16(  2, 153, 255),
    HSV16( 29, 153, 238),
    HSV16( 44, 255, 255),
    HSV16( 53, 238, 255),
    HSV16( 63, 238, 238),
    HSV16( 85, 238, 238),
  },
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_GROOVY_ENABLE)
  // "Groovy" palette. Inspired by the Gruvbox theme by Pavel Pertsev, which is
  // distributed under MIT/X11 license.
  // https://github.com/morhetz/gruvbox/tree/f1ecde848f0cdba877acb0c740320568252cc482
  {
    HSV16( 26, 136, 187),
    HSV16( 23,  85, 102),
    HSV16( 21,  85,  85),
    HSV16( 21,  85,  85),
    HSV16( 21,  85,  85),
    HSV16( 17, 102, 102),
    HSV16(  5, 204, 255),
    HSV16(  4, 255, 255),
    HSV16(  4, 255, 255),
    HSV16(  7, 204, 255),
    HSV16( 23, 136, 187),
    HSV16( 26, 136, 187),
    HSV16( 28, 136, 187),
    HSV16( 50, 238, 238),
    HSV16( 54, 255, 238),
    HSV16( 54, 255, 238),
  },
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_NOTPINK_ENABLE)
  // "Not Pink" palette.
  {
    HSV16(  9, 255, 153),
    HSV16(  3, 221, 187),
    HSV16(252, 204, 187),
    HSV16(248, 204, 187),
    HSV16(247, 187, 204),
    HSV16(245, 187, 238),
    HSV16(244, 170, 255),
    HSV16(245, 153, 255),
    HSV16(252, 102, 255),
    HSV16( 16,  68, 255),
    HSV16( 40,  34, 255),
    HSV16( 32,  51, 255),
    HSV16(  6,  85, 255),
    HSV16(248, 136, 255),
    HSV16(247, 187, 255),
    HSV16(249, 221, 255),
  },
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_PHOSPHOR_ENABLE)
  // "Phosphor" palette.
  {
    HSV16(116, 102,  34),
    HSV16(113, 170,  51),
    HSV16(113, 255,  68),
    HSV16(110, 255,  68),
    HSV16(109, 255,  85),
    HSV16(105, 255, 102),
    HSV16( 95, 238, 102),
    HSV16( 85, 238, 119),
    HSV16( 84, 255, 136),
    HSV16( 84, 255, 153),
    HSV16( 83, 255, 187),
    HSV16( 80, 238, 204),
    HSV16( 69, 221, 238),
    HSV16( 46, 204, 255),
    HSV16( 42, 153, 255),
    HSV16( 40, 102, 255),
  },
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_POLARIZED_ENABLE)
  // "Polarized" palette. Inspired by the Solarized theme by Ethan Schoonover,
  // which is distributed under MIT license.
  // https://github.com/altercation/solarized/tree/62f656a02f93c5190a8753159e34b385588d5ff3
  {
    HSV16(139, 255,  68),
    HSV16(139, 221,  85),
    HSV16(139, 204, 102),
    HSV16(138, 204, 119),
    HSV16(137, 204, 136),
    HSV16(137, 187, 170),
    HSV16(137, 153, 187),
    HSV16(132, 170, 187),
    HSV16(126, 187, 238),
    HSV16(124, 102, 255),
    HSV16(124, 102, 255),
    HSV16(124, 187, 255),
    HSV16(130, 170, 204),
    HSV16(137, 153, 187),
    HSV16(137, 153, 204),
    HSV16(137, 136, 221),
  },
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_ROSEGOLD_ENABLE)
  // "Rose Gold" palette.
  {
    HSV16(246, 255, 204),
    HSV16(250, 238, 221),
    HSV16(253, 221, 238),
    HSV16(  1, 221, 255),
    HSV16(  6, 221, 255),
    HSV16( 12, 221, 255),
    HSV16( 18, 204, 255),
    HSV16( 22, 170, 255),
    HSV16( 20, 204, 255),
    HSV16( 17, 221, 255),
    HSV16( 12, 221, 255),
    HSV16(  7, 221, 255),
    HSV16(255, 204, 255),
    HSV16(248, 204, 255),
    HSV16(241, 238, 255),
    HSV16(235, 255, 255),
  },
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_SPORT_ENABLE)
  // "Sport" palette.
  {
    HSV16(156, 102,  51),
    HSV16(155, 102,  68),
    HSV16(155, 102,  68),
    HSV16(154, 102,  68),
    HSV16(155, 102,  85),
    HSV16(156,  85, 102),
    HSV16(158,  68, 119),
    HSV16(159,  51, 136),
    HSV16(158,  17, 153),
    HSV16(130,   0, 170),
    HSV16( 49,  17, 204),
    HSV16( 42,  51, 238),
    HSV16( 39,  85, 255),
    HSV16( 37, 119, 255),
    HSV16( 36, 170, 255),
    HSV16( 36, 255, 255),
  },
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_SYNTHWAVE_ENABLE)
  // "Synthwave" palette.
  {
    HSV16(170, 221, 119),
    HSV16(180, 221, 153),
    HSV16(196, 238, 153),
    HSV16(209, 255, 153),
    HSV16(220, 255, 170),
    HSV16(227, 255, 204),
    HSV16(233, 255, 238),
    HSV16(245, 204, 255),
    HSV16(  3, 170, 255),
    HSV16( 13, 187, 255),
    HSV16( 21, 204, 255),
    HSV16( 28, 221, 255),
    HSV16( 43, 255, 255),
    HSV16( 42, 255, 255),
    HSV16( 68,  68, 255),
    HSV16(132, 255, 255),
  },
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_THERMAL_ENABLE)
  // "Thermal" palette.
  {
    HSV16(  7,   0,  17),
    HSV16(  8,   0,  17),
    HSV16( 12,   0,  34),
    HSV16( 13,   0,  51),
    HSV16( 15,  17,  51),
    HSV16( 16,  17,  68),
    HSV16( 20,  34,  85),
    HSV16( 95,   0, 102),
    HSV16(126,  85, 119),
    HSV16(112,  85, 153),
    HSV16( 54, 136, 187),
    HSV16( 39, 238, 221),
    HSV16( 33, 255, 255),
    HSV16( 25, 238, 255),
    HSV16( 13, 238, 255),
    HSV16(  5, 238, 255),
  },
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_VIRIDIS_ENABLE)
  // "Viridis" palette. Inspired by the Viridis colormap by Stefan van der Walt
  // and Nathaniel Smith, which is distributed under CC0 license.
  // https://github.com/BIDS/colormap/blob/bc549477db0c12b54a5928087552ad2cf274980f/colormaps.py
  {
    HSV16(204, 221, 102),
    HSV16(194, 187, 119),
    HSV16(183, 153, 136),
    HSV16(169, 119, 153),
    HSV16(155, 153, 153),
    HSV16(145, 170, 153),
    HSV16(137, 187, 153),
    HSV16(130, 204, 153),
    HSV16(123, 221, 153),
    HSV16(117, 221, 170),
    HSV16(108, 187, 187),
    HSV16( 93, 153, 204),
    HSV16( 71, 170, 221),
    HSV16( 56, 221, 221),
    HSV16( 46, 255, 238),
    HSV16( 39, 255, 255),
  },
#endif
#if defined(PALETTEFX_ENABLE_ALL_PALETTES) || defined(PALETTEFX_WATERMELON_ENABLE)
  // "Watermelon" palette.
  {
    HSV16( 67, 255, 102),
    HSV16( 55, 255, 153),
    HSV16( 47, 255, 204),
    HSV16( 48, 136, 238),
    HSV16( 48,  68, 255),
    HSV16( 45,  34, 255),
    HSV16( 39,  34, 255),
    HSV16( 17,  85, 255),
    HSV16(  8, 187, 255),
    HSV16(  1, 255, 255),
    HSV16(  2, 238, 255),
    HSV16(  2, 238, 255),
    HSV16(  0, 238, 255),
    HSV16(253, 255, 238),
    HSV16(254, 255, 238),
    HSV16(255, 255, 221),
  },
#endif
#if __has_include("palettefx_user.inc")  // Include user palettes if present.
#include "palettefx_user.inc"
#endif
};
/** Number of palettes. User palettes, if any, are included in the count. */
#define NUM_PALETTEFX_PALETTES \
    (sizeof(palettefx_palettes) / sizeof(*palettefx_palettes))

// Validate at compile time that `1 <= NUM_PALETTEFX_PALETTES <= 32`. The upper
// limit is due to using RGB Matrix's hue config to select palettes.
_Static_assert(
    NUM_PALETTEFX_PALETTES >= 1,
    "palettefx: No palettes are enabled. To fix: enable all built-in palettes by adding in config.h `#define PALETTE_ENABLE_ALL_PALETTES`, or enable at least one with `#define PALETTE_<name>_ENABLE`, or define at least one custom palette in palettefx_user.inc.");
_Static_assert(
    NUM_PALETTEFX_PALETTES <= 256 / RGB_MATRIX_HUE_STEP,
    "palettefx: Too many palettes. Up to 32 (= 256 / RGB_MATRIX_HUE_STEP) palettes are supported. Otherwise, some palettes would be unreachable.");

/** Gets the index of the selected palette. */
static uint8_t palettefx_get_palette(void) {
  uint8_t i =
      (rgb_matrix_get_hue() / RGB_MATRIX_HUE_STEP) % NUM_PALETTEFX_PALETTES;

  if (256 % (RGB_MATRIX_HUE_STEP * NUM_PALETTEFX_PALETTES) != 0) {
    // Hue wraps mod 256. If NUM_PALETTEFX_PALETTES is not a power of 2, modulo
    // 256 wraps would jump, and adjustment is needed to cycle as desired:
    //
    // * If the hue is a step or less from 256, assume it has wrapped down
    //   from 0 and the last palette is selected.
    // * Otherwise, i = ((hue / step) % NUM_PALETTEFX_PALETTES) is used. If
    //   256 - 2 * step <= hue < 256 - step, hue is set to (step * i).
    hsv_t hsv = rgb_matrix_get_hsv();
    if (hsv.h >= 256 - 2 * RGB_MATRIX_HUE_STEP) {
      if (hsv.h >= 256 - RGB_MATRIX_HUE_STEP) {
        i = NUM_PALETTEFX_PALETTES - 1;
        hsv.h = RGB_MATRIX_HUE_STEP * (
            (256 / (RGB_MATRIX_HUE_STEP * NUM_PALETTEFX_PALETTES)) *
                NUM_PALETTEFX_PALETTES
            - 1);
      } else {
        i %= NUM_PALETTEFX_PALETTES;
        hsv.h = RGB_MATRIX_HUE_STEP * i;
      }
      rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
    }
  }

  return i;
}

const uint16_t* palettefx_get_palette_data(void) {
  return palettefx_palettes[palettefx_get_palette()];
}

const uint16_t* palettefx_get_palette_data_by_index(uint8_t i) {
  return palettefx_palettes[i % NUM_PALETTEFX_PALETTES];
}

uint8_t palettefx_num_palettes(void) {
  return NUM_PALETTEFX_PALETTES;
}

hsv_t palettefx_interp_color(const uint16_t* palette, uint8_t x) {
  // Clamp `x` to [8, 247] and subtract 8, mapping to the range [0, 239].
  x = (x <= 8) ? 0 : ((x < 247) ? (x - 8) : 239);
  // Get index into the palette, 0 <= i <= 14.
  const uint8_t i = x >> 4;
  // Fractional position between i and (i + 1).
  const uint8_t frac = x << 4;

  // Look up palette colors at i and (i + 1).
  hsv_t a = unpack_hsv16(pgm_read_word(&palette[i]));
  hsv_t b = unpack_hsv16(pgm_read_word(&palette[i + 1]));

  // Linearly interpolate in HSV, accounting for wrapping in hue.
  const uint8_t hue_wrap = 128 & (a.h >= b.h ? (a.h - b.h) : (b.h - a.h));
  return (hsv_t){
    .h = lerp8by8(a.h ^ hue_wrap, b.h ^ hue_wrap, frac) ^ hue_wrap,
    .s = scale8(lerp8by8(a.s, b.s, frac), rgb_matrix_config.hsv.s),
    .v = scale8(lerp8by8(a.v, b.v, frac), rgb_matrix_config.hsv.v),
  };
}

uint16_t palettefx_scaled_time(uint32_t timer, uint8_t scale) {
  static uint16_t wrap_correction = 0;
  static uint8_t last_high_byte = 0;
  const uint8_t high_byte = (uint8_t)(timer >> 16);

  if (last_high_byte != high_byte) {
    last_high_byte = high_byte;
    wrap_correction += ((uint16_t)scale) << 8;
  }

  return scale16by8(timer, scale) + wrap_correction;
}

