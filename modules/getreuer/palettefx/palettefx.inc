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
 * @file palettefx.inc
 * @brief PaletteFx community module effects definitions
 *
 * For full documentation, see
 * <https://getreuer.info/posts/keyboards/palettefx>
 */

#ifdef COMMUNITY_MODULE_PALETTEFX_ENABLE

#include "palettefx_default_config.h"

#if defined(PALETTEFX_ENABLE_ALL_EFFECTS) || defined(PALETTEFX_GRADIENT_ENABLE)
RGB_MATRIX_EFFECT(PALETTEFX_GRADIENT)
#endif
#if defined(PALETTEFX_ENABLE_ALL_EFFECTS) || defined(PALETTEFX_FLOW_ENABLE)
RGB_MATRIX_EFFECT(PALETTEFX_FLOW)
#endif
#if defined(PALETTEFX_ENABLE_ALL_EFFECTS) || defined(PALETTEFX_RIPPLE_ENABLE)
RGB_MATRIX_EFFECT(PALETTEFX_RIPPLE)
#endif
#if defined(PALETTEFX_ENABLE_ALL_EFFECTS) || defined(PALETTEFX_SPARKLE_ENABLE)
RGB_MATRIX_EFFECT(PALETTEFX_SPARKLE)
#endif
#if defined(PALETTEFX_ENABLE_ALL_EFFECTS) || defined(PALETTEFX_VORTEX_ENABLE)
RGB_MATRIX_EFFECT(PALETTEFX_VORTEX)
#endif
#if defined(RGB_MATRIX_KEYREACTIVE_ENABLED) && ( \
    defined(PALETTEFX_ENABLE_ALL_EFFECTS) || defined(PALETTEFX_REACTIVE_ENABLE))
RGB_MATRIX_EFFECT(PALETTEFX_REACTIVE)
#endif

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "palettefx.h"

#if !(defined(PALETTEFX_ENABLE_ALL_EFFECTS) || \
      defined(PALETTEFX_GRADIENT_ENABLE) || \
      defined(PALETTEFX_FLOW_ENABLE) || \
      defined(PALETTEFX_RIPPLE_ENABLE) || \
      defined(PALETTEFX_SPARKLE_ENABLE) || \
      defined(PALETTEFX_VORTEX_ENABLE) || \
      (defined(RGB_MATRIX_KEYREACTIVE_ENABLED) && \
       defined(PALETTEFX_REACTIVE_ENABLE)))
#pragma message \
    "palettefx: No palettefx effects are enabled. Enable all effects by adding in config.h `#define PALETTEFX_ENABLE_ALL_EFFECTS`, or enable individual effects with `#define PALETTE_<name>_ENABLE`."
#endif

#if defined(PALETTEFX_ENABLE_ALL_EFFECTS) || defined(PALETTEFX_GRADIENT_ENABLE)
// "Gradient" static effect. This is essentially a palette-colored version of
// RGB_MATRIX_GRADIENT_UP_DOWN. A vertically-sloping gradient is made, with the
// highest color on the top keys of keyboard and the lowest color at the bottom.
static bool PALETTEFX_GRADIENT(effect_params_t* params) {
  // On first call, compute and cache the slope of the gradient.
  static uint8_t gradient_slope = 0;
  if (!gradient_slope) {
    uint8_t y_max = 64;  // To avoid overflow below, x_max must be at least 64.
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; ++i) {
      if (g_led_config.point[i].y > y_max) {
        y_max = g_led_config.point[i].y;
      }
    }
    // Compute the quotient `255 / y_max` with 6 fractional bits and rounding.
    gradient_slope = (64 * 255 + y_max / 2) / y_max;
  }

  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  const uint16_t* palette = palettefx_get_palette_data();

  for (uint8_t i = led_min; i < led_max; ++i) {
    RGB_MATRIX_TEST_LED_FLAGS();
    const uint8_t y = g_led_config.point[i].y;
    const uint8_t value = 255 - (((uint16_t)y * (uint16_t)gradient_slope) >> 6);
    rgb_t rgb = rgb_matrix_hsv_to_rgb(palettefx_interp_color(palette, value));
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }

  return rgb_matrix_check_finished_leds(led_max);
}
#endif

#if defined(PALETTEFX_ENABLE_ALL_EFFECTS) || defined(PALETTEFX_FLOW_ENABLE)
// "Flow" animated effect. Draws moving wave patterns mimicking the appearance
// of flowing liquid. For interesting variety of patterns, space coordinates are
// slowly rotated and a function of several sine waves is evaluated.
static bool PALETTEFX_FLOW(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  const uint16_t* palette = palettefx_get_palette_data();
  const uint16_t time =
      palettefx_scaled_time(g_rgb_timer, 1 + rgb_matrix_config.speed / 8);
  // Compute rotation coefficients with 7 fractional bits.
  const int8_t rot_c = cos8(time / 4) - 128;
  const int8_t rot_s = sin8(time / 4) - 128;
  const uint8_t omega = 32 + sin8(time) / 4;

  for (uint8_t i = led_min; i < led_max; ++i) {
    RGB_MATRIX_TEST_LED_FLAGS();
    const uint8_t x = g_led_config.point[i].x;
    const uint8_t y = g_led_config.point[i].y;

    // Rotate (x, y) by the 2x2 rotation matrix described by rot_c, rot_s.
    const uint8_t x1 = (uint8_t)((((int16_t)rot_c) * ((int16_t)x)) / 128)
        - (uint8_t)((((int16_t)rot_s) * ((int16_t)y)) / 128);
    const uint8_t y1 = (uint8_t)((((int16_t)rot_s) * ((int16_t)x)) / 128)
        + (uint8_t)((((int16_t)rot_c) * ((int16_t)y)) / 128);

    uint8_t value = scale8(sin8(x1 - 2 * time), omega) + y1 + time / 4;
    // Evaluate `sawtooth(value)`.
    value = 2 * ((value <= 127) ? value : (255 - value));

    rgb_t rgb = rgb_matrix_hsv_to_rgb(palettefx_interp_color(palette, value));
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }

  return rgb_matrix_check_finished_leds(led_max);
}
#endif

#if defined(PALETTEFX_ENABLE_ALL_EFFECTS) || defined(PALETTEFX_RIPPLE_ENABLE)
// "Ripple" animated effect. Draws circular rings emanating from random points,
// simulating water drops falling in a quiet pool.
static bool PALETTEFX_RIPPLE(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  const uint16_t* palette = palettefx_get_palette_data();

  // Each instance of this struct represents one water drop. For efficiency, at
  // most 3 drops are active at any time.
  static struct {
    uint16_t time;
    uint8_t x;
    uint8_t y;
    uint8_t amplitude;
    uint8_t scale;
    uint8_t phase;
  } drops[3];
  static uint32_t drop_timer = 0;
  static uint8_t drops_tail = 0;

  if (params->iter == 0) {
    if (params->init) {
      for (uint8_t j = 0; j < 3; ++j) {
        drops[j].amplitude = 0;
      }
      drop_timer = g_rgb_timer;
    }

    if (drops[drops_tail].amplitude == 0 &&
        timer_expired32(g_rgb_timer, drop_timer)) {
      // Spawn a new drop, located at a random LED.
      const uint8_t i = random8_max(RGB_MATRIX_LED_COUNT);
      drops[drops_tail].time = (uint16_t)g_rgb_timer;
      drops[drops_tail].x = g_led_config.point[i].x;
      drops[drops_tail].y = g_led_config.point[i].y;
      drops[drops_tail].amplitude = 1;
      ++drops_tail;
      if (drops_tail == 3) { drops_tail = 0; }
      drop_timer = g_rgb_timer + 1000;
    }

    uint8_t amplitude(uint8_t t) {  // Drop amplitude as a function of time.
      if (t <= 55) {
        return (t < 32) ? (3 + 5 * t) : 192;
      } else {
        t = (((uint16_t)(255 - t)) * UINT16_C(123)) >> 7;
        return scale8(t, t);
      }
    }

    for (uint8_t j = 0; j < 3; ++j) {
      if (drops[j].amplitude == 0) { continue; }
      const uint16_t tick = scale16by8(g_rgb_timer - drops[j].time,
          1 + rgb_matrix_config.speed / 4);
      if (tick < 4 * 255) {
        const uint8_t t = (uint8_t)(tick / 4);
        drops[j].amplitude = amplitude(t);
        drops[j].scale = 255 / (1 + t / 2);
        drops[j].phase = (uint8_t)tick;
      } else {
        drops[j].amplitude = 0;  // Animation for this drop is complete.
      }
    }
  }

  for (uint8_t i = led_min; i < led_max; ++i) {
    RGB_MATRIX_TEST_LED_FLAGS();
    int16_t value = 128;

    for (uint8_t j = 0; j < 3; ++j) {
      if (drops[j].amplitude == 0) { continue; }

      const uint8_t x = abs8((g_led_config.point[i].x - drops[j].x) / 2);
      const uint8_t y = abs8((g_led_config.point[i].y - drops[j].y) / 2);
      const uint8_t r = sqrt16(x * x + y * y);
      const uint16_t r_scaled = (uint16_t)r * (uint16_t)drops[j].scale;

      if (r_scaled < 255) {
        // The drop is made from a radial sine wave modulated by a smooth bump
        // to localize its spatial extent.
        const uint8_t bump = scale8(ease8InOutApprox(255 - (uint8_t)r_scaled),
                                    drops[j].amplitude);
        const int8_t wave = (int16_t)cos8(8 * r - drops[j].phase) - 128;
        value += ((int16_t)wave * (int16_t)bump) / 128;
      }
    }

    // Clip `value` to 0-255 range.
    if (value < 0) { value = 0; }
    if (value > 255) { value = 255; }
    rgb_t rgb =
        rgb_matrix_hsv_to_rgb(palettefx_interp_color(palette, (uint8_t)value));
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }

  return rgb_matrix_check_finished_leds(led_max);
}
#endif

#if defined(PALETTEFX_ENABLE_ALL_EFFECTS) || defined(PALETTEFX_SPARKLE_ENABLE)
// "Sparkle" effect. Each LED is animated by a sine wave with pseudorandom
// phase, so that the matrix "sparkles." All the LED sines are modulated by a
// global amplitude factor, which varies by a slower sine wave, so that the
// matrix as a whole periodically brightens and dims.
static bool PALETTEFX_SPARKLE(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  const uint16_t* palette = palettefx_get_palette_data();
  const uint8_t time =
      palettefx_scaled_time(g_rgb_timer, 1 + rgb_matrix_config.speed / 8);
  const uint8_t amplitude = 128 + sin8(time) / 2;
  uint16_t rand_state = 1 + params->iter;

  for (uint8_t i = led_min; i < led_max; ++i) {
    RGB_MATRIX_TEST_LED_FLAGS();
    // Multiplicative congruential generator for a random phase for each LED.
    rand_state *= UINT16_C(36563);
    const uint8_t phase = (uint8_t)(rand_state >> 8);

    const uint8_t value = scale8(sin8(2 * time + phase), amplitude);

    rgb_t rgb = rgb_matrix_hsv_to_rgb(palettefx_interp_color(palette, value));
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }

  return rgb_matrix_check_finished_leds(led_max);
}
#endif

#if defined(PALETTEFX_ENABLE_ALL_EFFECTS) || defined(PALETTEFX_VORTEX_ENABLE)
// "Vortex" animated effect. LEDs are animated according to a polar function
// with the appearance of a spinning vortex centered on k_rgb_matrix_center.
static bool PALETTEFX_VORTEX(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  const uint16_t* palette = palettefx_get_palette_data();
  const uint16_t time =
      palettefx_scaled_time(g_rgb_timer, 1 + rgb_matrix_config.speed / 4);

  for (uint8_t i = led_min; i < led_max; ++i) {
    RGB_MATRIX_TEST_LED_FLAGS();
    const int16_t x = g_led_config.point[i].x - k_rgb_matrix_center.x;
    const int16_t y = g_led_config.point[i].y - k_rgb_matrix_center.y;
    uint8_t value = sin8(atan2_8(y, x) + time - sqrt16(x * x + y * y) / 2);

    rgb_t rgb = rgb_matrix_hsv_to_rgb(palettefx_interp_color(palette, value));
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }

  return rgb_matrix_check_finished_leds(led_max);
}
#endif

#if defined(RGB_MATRIX_KEYREACTIVE_ENABLED) && ( \
    defined(PALETTEFX_ENABLE_ALL_EFFECTS) || defined(PALETTEFX_REACTIVE_ENABLE))
// Reactive animated effect. This effect is "reactive," it responds to key
// presses. For each key press, LEDs near the key change momentarily.
static bool PALETTEFX_REACTIVE(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  const uint16_t* palette = palettefx_get_palette_data();
  const uint8_t count = g_last_hit_tracker.count;

  uint8_t amplitude(uint8_t t) {  // Bump amplitude as a function of time.
    if (t <= 55) {
      return (t < 32) ? (4 + 8 * t) : 255;
    } else {
      t = (((uint16_t)(255 - t)) * UINT16_C(164)) >> 7;
      return scale8(t, t);
    }
  }

  uint8_t hit_amplitude[LED_HITS_TO_REMEMBER] = {0};
  for (uint8_t j = 0; j < count; ++j) {
    const uint16_t tick = scale16by8(g_last_hit_tracker.tick[j],
        1 + rgb_matrix_config.speed / 4);
    if (tick <= 255) {
      hit_amplitude[j] = amplitude((uint8_t)tick);
    }
  }

  for (uint8_t i = led_min; i < led_max; ++i) {
    RGB_MATRIX_TEST_LED_FLAGS();
    uint8_t value = 0;

    for (uint8_t j = 0; j < count; ++j) {
      if (hit_amplitude[j] == 0) { continue; }

      uint8_t dx = abs8((g_led_config.point[i].x - g_last_hit_tracker.x[j]) / 2);
      uint8_t dy = abs8((g_led_config.point[i].y - g_last_hit_tracker.y[j]) / 2);
      if (dx < 21 && dy < 21) {
        const uint16_t dist_sqr = dx * dx + dy * dy;
        if (dist_sqr < 21 * 21) {  // Accumulate a radial bump for each hit.
          const uint8_t dist = sqrt16(dist_sqr);
          value = qadd8(value, scale8(255 - 12 * dist, hit_amplitude[j]));
          // Early loop exit where the value has saturated.
          if (value == 255) { break; }
        }
      }
    }

    hsv_t hsv = palettefx_interp_color(palette, value);
    if (value < 32) {  // Make the background dark regardless of palette.
      hsv.v = scale8(hsv.v, 64 + 6 * value);
    }

    const rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return rgb_matrix_check_finished_leds(led_max);
}
#endif

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif  // COMMUNITY_MODULE_PALETTEFX_ENABLE

