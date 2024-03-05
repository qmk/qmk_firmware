// Copyright 2024 burkfers (@burkfers)
// Copyright 2024 Wimads (@wimads)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h" // IWYU pragma: keep
#include "maccel.h"
#include "math.h"

static uint32_t maccel_timer;

/* MACCEL_SCALE
 * A device specific parameter (C) required to ensure consistent acceleration behaviour across different devices.
 * lower/higher value = pointer speedier/slower
 * - PMW3360: 200
 * - PMW3389: 200
 *
 * Linearity across different user CPI settings in the reported distance moved
 * works better when pointer task throttling is enforced,
 * that is, `POINTING_DEVICE_TASK_THROTTLE_MS` is defined (at least in PMW3360).
 *,
 * Disclaimer: values guesstimated by scientifically questionable emperical testing.
 */
#ifndef MACCEL_TAKEOFF
#    define MACCEL_TAKEOFF 1.6 // (K) lower/higher value = curve starts more smoothly/abrubtly
#endif
#ifndef MACCEL_GROWTH_RATE
#    define MACCEL_GROWTH_RATE 0.22 // (G) lower/higher value = curve reaches its upper limit slower/faster
#endif
#ifndef MACCEL_OFFSET
#    define MACCEL_OFFSET 2.2 // (S) lower/higher value = acceleration kicks in earlier/later
#endif
#ifndef MACCEL_LIMIT
#    define MACCEL_LIMIT 0.2 // (M) upper limit of accel curve (maximum acceleration factor)
#endif
#ifndef MACCEL_CPI_THROTTLE_MS
#    define MACCEL_CPI_THROTTLE_MS 200 // milliseconds to wait between requesting the device's current DPI
#endif
#ifndef MACCEL_ROUNDING_CURRY_TIMEOUT_MS
#    define MACCEL_ROUNDING_CURRY_TIMEOUT_MS 300 // mouse report ellapsed time after which quantization error gets reset
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
#        define MACCEL_SCALE_STEP 20
#    endif
#    ifndef MACCEL_TAKEOFF_STEP
#        define MACCEL_TAKEOFF_STEP 0.2f
#    endif
#    ifndef MACCEL_GROWTH_RATE_STEP
#        define MACCEL_GROWTH_RATE_STEP 0.01f
#    endif
#    ifndef MACCEL_OFFSET_STEP
#        define MACCEL_OFFSET_STEP 0.1f
#    endif
#    ifndef MACCEL_LIMIT_STEP
#        define MACCEL_LIMIT_STEP 0.2f
#    endif
#endif

float maccel_get_takeoff(void) {
    return g_maccel_config.takeoff;
}
float maccel_get_growth_rate(void) {
    return g_maccel_config.growth_rate;
}
float maccel_get_offset(void) {
    return g_maccel_config.offset;
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
    g_maccel_config.offset = val;
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
    static float rounding_curry_x = 0;
    static float rounding_curry_y = 0;

    const uint16_t report_elapsed_time = timer_elapsed32(maccel_timer);
    if (mouse_report.x != 0 || mouse_report.y != 0) {
        maccel_timer = timer_read32();
    } else if ((mouse_report.x == 0 && mouse_report.y == 0) || !g_maccel_config.enabled) {
        if (report_elapsed_time > MACCEL_ROUNDING_CURRY_TIMEOUT_MS) {
            rounding_curry_x = rounding_curry_y = 0;
        }
        return mouse_report;
    }
    // Reset carry when pointer stops moving or swaps direction, to follow user's hand.
    if (mouse_report.x * rounding_curry_x < 0) rounding_curry_x = 0;
    if (mouse_report.y * rounding_curry_y < 0) rounding_curry_y = 0;

    // Limit expensive calls to get device cpi settings only when mouse stationay for > 200ms.
    static uint16_t device_cpi = 300;
    if (report_elapsed_time > MACCEL_CPI_THROTTLE_MS) {
        device_cpi = pointing_device_get_cpi();
        // do the junk-fix untill merge with qbk-upstream
        pointing_device_set_cpi(device_cpi);
    }
    // euclidean distance moved: sqrt(x^2 + y^2)
    const float distance     = sqrtf(mouse_report.x * mouse_report.x + mouse_report.y * mouse_report.y);
    const float velocity_raw = distance / report_elapsed_time;
    // Normalize input velocity across DPIs rougly in the range 0..10, where the curve grows.
    const float cpi_scale = 1000.0f / device_cpi;
    const float velocity  = velocity_raw * cpi_scale;
    // Generalised Sigmoid acceleration factor: y(x) = M - (M - 1) / {1 + e^[K(x - S)]}^(G/K)
    // see https://www.desmos.com/calculator/m7mzjocsb4
    const float k             = g_maccel_config.takeoff;
    const float g             = g_maccel_config.growth_rate;
    const float s             = g_maccel_config.offset;
    const float m             = g_maccel_config.limit;
    const float maccel_factor = 1.2 - (1.2 - m) / powf(1 + expf(k * (velocity - s)), g / k);
    // DPI-scale also mouse-report x, y and account old quantization errors.
    const float new_x = rounding_curry_x + maccel_factor * mouse_report.x;
    const float new_y = rounding_curry_y + maccel_factor * mouse_report.y;
    // Accumulate any difference from next integer (quantization).
    rounding_curry_x = new_x - (int)new_x;
    rounding_curry_y = new_y - (int)new_y;
    // clamp values
    const mouse_xy_report_t x = CONSTRAIN_REPORT(new_x);
    const mouse_xy_report_t y = CONSTRAIN_REPORT(new_y);

// console output for debugging (enable/disable in config.h)
#ifdef MACCEL_DEBUG
    // const float distance_out = sqrtf(x * x + y * y);
    const float velocity_out = velocity * maccel_factor;
    printf("MACCEL:  DPI:%i  Tko: %.3f  Grw: %.3f  Ofs: %.3f  Lmt: %.3f  |  Fct: %.3f  v.in: %.3f  v.out: %.3f  new.x: %.3f  int.x: %i  cst.x %i  cur.x: %.3f\n", device_cpi, g_maccel_config.takeoff, g_maccel_config.growth_rate, g_maccel_config.offset, g_maccel_config.limit, maccel_factor, velocity, velocity_out, new_x, (int)new_x, CONSTRAIN_REPORT(new_x), rounding_curry_x);
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
            printf("MACCEL:keycode: scl: %.1f TKO: %.3f gro: %.3f ofs: %.3f lmt: %.3f\n", g_maccel_config.takeoff, g_maccel_config.growth_rate, g_maccel_config.offset, g_maccel_config.limit);
            return false;
        }
        if (keycode == growth_rate) {
            maccel_set_growth_rate(maccel_get_growth_rate() + get_mod_step(MACCEL_GROWTH_RATE_STEP));
            printf("MACCEL:keycode: scl: %.1f tko: %.3f GRO: %.3f ofs: %.3f lmt: %.3f\n", g_maccel_config.takeoff, g_maccel_config.growth_rate, g_maccel_config.offset, g_maccel_config.limit);
            return false;
        }
        if (keycode == offset) {
            maccel_set_offset(maccel_get_offset() + get_mod_step(MACCEL_OFFSET_STEP));
            printf("MACCEL:keycode: scl: %.1f tko: %.3f gro: %.3f OFS: %.3f lmt: %.3f\n", g_maccel_config.takeoff, g_maccel_config.growth_rate, g_maccel_config.offset, g_maccel_config.limit);
            return false;
        }
        if (keycode == limit) {
            maccel_set_limit(maccel_get_limit() + get_mod_step(MACCEL_LIMIT_STEP));
            printf("MACCEL:keycode: scl: %.1f tko: %.3f gro: %.3f ofs: %.3f LMT: %.3f\n", g_maccel_config.takeoff, g_maccel_config.growth_rate, g_maccel_config.offset, g_maccel_config.limit);
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
