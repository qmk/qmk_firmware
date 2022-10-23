/*
QMK Firmware Massdrop CTRL M-AS Keymap
Copyright (C) 2020 matthewrobo

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(SOLID_REACTIVE_WIDE2)
RGB_MATRIX_EFFECT(SOLID_REACTIVE_MULTIWIDE2)
RGB_MATRIX_EFFECT(SOLID_REACTIVE_NEXUS2)
RGB_MATRIX_EFFECT(SOLID_REACTIVE_MULTINEXUS2)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV SOLID_REACTIVE_WIDE_math2(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick - dist > 255 || dist > 32 ? 255 : tick - dist;
    hsv.v           = qadd8(hsv.v, 255 - effect);
    return hsv;
}

static HSV SOLID_REACTIVE_NEXUS_math2(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick - dist > 255 || ((dx > 8 || dx < -8) && (dy > 8 || dy < -8)) ? 255 : tick - dist;
    hsv.v           = qadd8(hsv.v, 255 - effect);
    hsv.h           = rgb_matrix_config.hsv.h + dy / 4;
    return hsv;
}

bool SOLID_REACTIVE_WIDE2(effect_params_t* params) { return effect_runner_reactive_splash(qsub8(g_last_hit_tracker.count, 1), params, &SOLID_REACTIVE_WIDE_math2); }
bool SOLID_REACTIVE_MULTIWIDE2(effect_params_t* params) { return effect_runner_reactive_splash(0, params, &SOLID_REACTIVE_WIDE_math2); }
bool SOLID_REACTIVE_NEXUS2(effect_params_t* params) { return effect_runner_reactive_splash(qsub8(g_last_hit_tracker.count, 1), params, &SOLID_REACTIVE_NEXUS_math2); }
bool SOLID_REACTIVE_MULTINEXUS2(effect_params_t* params) { return effect_runner_reactive_splash(0, params, &SOLID_REACTIVE_NEXUS_math2); }

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
