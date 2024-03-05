/* Copyright 2024 burkfers (@burkfers)
 * Copyright 2024 Wimads (@wimads)
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

#include "quantum.h" // IWYU pragma: keep
#include "maccel.h"
#include "math.h"

static uint32_t maccel_timer;

#ifndef MACCEL_TAKEOFF
#    define MACCEL_TAKEOFF 1.6 // lower/higher value = curve starts more smoothly/abrubtly
#endif
#ifndef MACCEL_GROWTH_RATE
#    define MACCEL_GROWTH_RATE 0.22 // lower/higher value = curve reaches its upper limit slower/faster
#endif
#ifndef MACCEL_OFFSET
#    define MACCEL_OFFSET 2.2 // lower/higher value = acceleration kicks in earlier/later
#endif
#ifndef MACCEL_LIMIT
#    define MACCEL_LIMIT 6.0 // upper limit of accel curve (maximum acceleration factor)
#endif

maccel_config_t g_maccel_config = {
    // clang-format off
    .growth_rate =  MACCEL_GROWTH_RATE,
    .offset =       MACCEL_OFFSET,
    .limit =        MACCEL_LIMIT,
    .takeoff =      MACCEL_TAKEOFF,
    .enabled =      true
    // clang-format on
};

#ifdef MACCEL_USE_KEYCODES
#    ifndef MACCEL_TAKEOFF_STEP
#        define MACCEL_TAKEOFF_STEP 0.01f
#    endif
#    ifndef MACCEL_GROWTH_RATE_STEP
#        define MACCEL_GROWTH_RATE_STEP 0.01f
#    endif
#    ifndef MACCEL_OFFSET_STEP
#        define MACCEL_OFFSET_STEP 0.1f
#    endif
#    ifndef MACCEL_LIMIT_STEP
#        define MACCEL_LIMIT_STEP 0.1f
#    endif
#endif

float maccel_get_takeoff(void) {
    return g_maccel_config.takeoff;
}
float maccel_get_growth_rate(void) {
    return g_maccel_config.growth_rate;
}
float maccel_get_offset(void) {
    return g_maccel_config.limit;
}
float maccel_get_limit(void) {
    return g_maccel_config.limit;
}
void maccel_set_takeoff(float val) {
    if (val >= 0.5) { // value less than 0.5 leads to nonsensical results
        g_maccel_config.takeoff = val;
    }
}
void maccel_set_growth_rate(float val) {
    if (val >= 0) { // value less 0 leads to nonsensical results
        g_maccel_config.growth_rate = val;
    }
}
void maccel_set_offset(float val) {
    g_maccel_config.limit = val;
}
void maccel_set_limit(float val) {
    if (val >= 1) { // limit less than 1 leads to nonsensical results
        g_maccel_config.limit = val;
    }
}

void maccel_enabled(bool enable) {
    g_maccel_config.enabled = enable;
#ifdef MACCEL_DEBUG
    printf("maccel: enabled: %d\n", g_maccel_config.enabled);
#endif
}
bool maccel_get_enabled(void) {
    return g_maccel_config.enabled;
}
void maccel_toggle_enabled(void) {
    maccel_enabled(!maccel_get_enabled());
}

#define _CONSTRAIN(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))
#define CONSTRAIN_REPORT(val) (mouse_xy_report_t) _CONSTRAIN(val, XY_REPORT_MIN, XY_REPORT_MAX)

report_mouse_t pointing_device_task_maccel(report_mouse_t mouse_report) {
    // rounding carry to recycle dropped floats from integer mouse repoarts
    static float rounding_carry_x = 0;
    static float rounding_carry_y = 0;
    // time since last mouse report:
    uint16_t delta_time = timer_elapsed32(maccel_timer);
    // don't do maccel math if report = 0, or maccel not enabled:
    if ((mouse_report.x == 0 && mouse_report.y == 0) || !g_maccel_config.enabled) {
        return mouse_report;
    }
    // reset timer:
    maccel_timer = timer_read32();
    // reset rounding carry when flipping direction (positive to negative):
    if (mouse_report.x * rounding_carry_x < 0) rounding_carry_x = 0;
    if (mouse_report.y * rounding_carry_y < 0) rounding_carry_y = 0;
    // get device cpi setting, only call when mouse hasn't moved since more than 200ms
    static uint16_t device_cpi = 300;
    if (delta_time > 200) {
#ifdef POINTING_DEVICE_DRIVER_azoteq_iqs5xx
        wait_ms(2);
#endif // POINTING_DEVICE_DRIVER_azoteq_iqs5xx
        device_cpi = pointing_device_get_cpi();
#ifdef POINTING_DEVICE_DRIVER_pmw3360
        // janky bug-fix for PMW3360
        pointing_device_set_cpi(device_cpi);
#endif // POINTING_DEVICE_DRIVER_pmw3360
    }
    // calculate dpi correction factor (for normalizing velocity range across different user dpi settings)
    const float dpi_correction = (float)1000.0f / device_cpi;
    // calculate euclidean distance moved (sqrt(x^2 + y^2))
    const float distance = sqrtf(mouse_report.x * mouse_report.x + mouse_report.y * mouse_report.y);
    // calculate delta velocity: dv = distance/dt
    const float velocity_raw = distance / delta_time;
    // correct raw velocity for dpi
    const float velocity = dpi_correction * velocity_raw;
    // calculate mouse acceleration factor: f(dv) = c - ((c-1) / ((1 + e^(x(x - b)) * a/z)))
    const float maccel_factor = 1 - (1 - g_maccel_config.limit) / powf(1 + expf(g_maccel_config.takeoff * (velocity - g_maccel_config.limit)), g_maccel_config.growth_rate / g_maccel_config.takeoff);
    // DPI-scale also mouse-report x, y and account old quantization errors.
    const float new_x = rounding_carry_x + maccel_factor * mouse_report.x;
    const float new_y = rounding_carry_y + maccel_factor * mouse_report.y;
    // Accumulate any difference from next integer (quantization).
    rounding_carry_x = new_x - (int)new_x;
    rounding_carry_y = new_y - (int)new_y;
    // clamp values
    const mouse_xy_report_t x = CONSTRAIN_REPORT(new_x);
    const mouse_xy_report_t y = CONSTRAIN_REPORT(new_y);

// console output for debugging (enable/disable in config.h)
#ifdef MACCEL_DEBUG
    // const float distance_out = sqrtf(x * x + y * y);
    const float velocity_out = velocity * maccel_factor;
    printf("MACCEL: DPI:%4i Tko: %.3f Grw: %.3f Ofs: %.3f Lmt: %.3f | Fct: %.3f v.in: %.3f v.out: %.3f v.raw %3f\n", device_cpi, g_maccel_config.takeoff, g_maccel_config.growth_rate, g_maccel_config.offset, g_maccel_config.limit, maccel_factor, velocity, velocity_out, velocity_raw);
#endif // MACCEL_DEBUG

    // report back accelerated values
    mouse_report.x = x;
    mouse_report.y = y;

    return mouse_report;
}

#ifdef MACCEL_USE_KEYCODES
static inline float get_mod_step(float step) {
    const uint8_t mod_mask = get_mods();
    if (mod_mask & MOD_MASK_CTRL) {
        step *= 10; // control increases by factor 10
    }
    if (mod_mask & MOD_MASK_SHIFT) {
        step *= -1; // shift inverts
    }
    return step;
}

bool process_record_maccel(uint16_t keycode, keyrecord_t *record, uint16_t takeoff, uint16_t growth_rate, uint16_t offset, uint16_t limit) {
    if (record->event.pressed) {
        if (keycode == takeoff) {
            maccel_set_takeoff(maccel_get_takeoff() + get_mod_step(MACCEL_TAKEOFF_STEP));
            printf("MACCEL:keycode: TKO: %.3f gro: %.3f ofs: %.3f lmt: %.3f\n", g_maccel_config.takeoff, g_maccel_config.growth_rate, g_maccel_config.limit, g_maccel_config.limit);
            return false;
        }
        if (keycode == growth_rate) {
            maccel_set_growth_rate(maccel_get_growth_rate() + get_mod_step(MACCEL_GROWTH_RATE_STEP));
            printf("MACCEL:keycode: tko: %.3f GRO: %.3f ofs: %.3f lmt: %.3f\n", g_maccel_config.takeoff, g_maccel_config.growth_rate, g_maccel_config.limit, g_maccel_config.limit);
            return false;
        }
        if (keycode == offset) {
            maccel_set_offset(maccel_get_offset() + get_mod_step(MACCEL_OFFSET_STEP));
            printf("MACCEL:keycode: tko: %.3f gro: %.3f OFS: %.3f lmt: %.3f\n", g_maccel_config.takeoff, g_maccel_config.growth_rate, g_maccel_config.limit, g_maccel_config.limit);
            return false;
        }
        if (keycode == limit) {
            maccel_set_limit(maccel_get_limit() + get_mod_step(MACCEL_LIMIT_STEP));
            printf("MACCEL:keycode: tko: %.3f gro: %.3f ofs: %.3f LMT: %.3f\n", g_maccel_config.takeoff, g_maccel_config.growth_rate, g_maccel_config.limit, g_maccel_config.limit);
            return false;
        }
    }
    return true;
}
#else
bool process_record_maccel(uint16_t keycode, keyrecord_t *record, uint16_t takeoff, uint16_t growth_rate, uint16_t offset, uint16_t limit) {
    // provide a do-nothing keyrecord function so a user doesn't need to unshim when disabling the keycodes
    return true;
}
#endif

// provide weak do-nothing shims so users do not need to unshim when diabling via
__attribute__((weak)) void keyboard_post_init_maccel(void) {
    return;
}
