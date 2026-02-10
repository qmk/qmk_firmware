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

RGB_MATRIX_EFFECT(FLOW)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// "Flow" animated effect. Draws moving wave patterns mimicking the appearance
// of flowing liquid. For interesting variety of patterns, space coordinates are
// slowly rotated and a function of several sine waves is evaluated.
static bool FLOW(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    static uint16_t wrap_correction = 0;
    static uint8_t  last_high_byte  = 0;
    const uint8_t   time_scale      = 1 + rgb_matrix_config.speed / 8;
    const uint8_t   high_byte       = (uint8_t)(g_rgb_timer >> 16);
    if (last_high_byte != high_byte) {
        last_high_byte = high_byte;
        wrap_correction += ((uint16_t)time_scale) << 8;
    }
    const uint16_t time = scale16by8(g_rgb_timer, time_scale) + wrap_correction;

    // Compute rotation coefficients with 7 fractional bits.
    const int8_t  rot_c = cos8(time / 4) - 128;
    const int8_t  rot_s = sin8(time / 4) - 128;
    const uint8_t omega = 32 + sin8(time) / 4;

    for (uint8_t i = led_min; i < led_max; ++i) {
        RGB_MATRIX_TEST_LED_FLAGS();
        const uint8_t x = g_led_config.point[i].x;
        const uint8_t y = g_led_config.point[i].y;

        // Rotate (x, y) by the 2x2 rotation matrix described by rot_c, rot_s.
        const uint8_t x1 = (uint8_t)((((int16_t)rot_c) * ((int16_t)x)) / 128) - (uint8_t)((((int16_t)rot_s) * ((int16_t)y)) / 128);
        const uint8_t y1 = (uint8_t)((((int16_t)rot_s) * ((int16_t)x)) / 128) + (uint8_t)((((int16_t)rot_c) * ((int16_t)y)) / 128);

        uint8_t value = scale8(sin8(x1 - 2 * time), omega) + y1 + time / 4;
        value         = (value <= 127) ? value : (255 - value);

        hsv_t hsv = rgb_matrix_config.hsv;
        hsv.h -= value / 4;
        hsv.s     = scale8(hsv.s, (value < 74) ? 255 : (549 - 4 * value));
        hsv.v     = scale8(hsv.v, (value < 95) ? (64 + 2 * value) : 255);

        rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
