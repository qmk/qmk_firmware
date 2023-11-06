// Copyright 2021 Victor Toni (@vitoni)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_matrix_effects.h"

#include <rgb_matrix.h>
#include <lib/lib8tion/lib8tion.h>

#include "utils.h"

/*
 Offset used to start at the right point in th curve to avoid big jumps in brightness
  0 =>    0% (signed) =>  50% (unsigned)
  64 =>  100% (signed) => 100% (unsigned)
 128 =>    0% (signed) =>  50% (unsigned)
 192 => -100% (signed) =>   0% (unsigned)
*/
enum PHASE {
    PHASE_ZERO_RAISING
    ,PHASE_HIGH
    ,PHASE_ZERO_FALLING
    ,PHASE_LOW
};

/**
 * @brief Calculates the offset so that a specific time is aligned to a specific point in the sine curve.
 * @param[in]   time    The time for which the offset shopuld be calculated.
 * @param[in]   phase   Phase which should be reached with the offset
 * @see PHASE
 */
uint8_t offset_for_time(const uint8_t time, const uint8_t phase) {
    switch (phase) {
        case PHASE_ZERO_RAISING:
            return 0 - time;
        case PHASE_HIGH:
            return 64 - time;
        case PHASE_ZERO_FALLING:
            return 128 - time;
        case PHASE_LOW:
            return 192 - time;
        default:
            return 0;
    }
}

/**
 * @brief Scales down `g_rgb_timer` so that it can be used for RGB effects.
 * @return scaled down timer
 * @see rgb_time_2_scale_w_factor()
 */
uint8_t rgb_time_2_scale(void) {
    static const uint8_t factor = 1;
    return rgb_time_2_scale_w_factor(factor);
}

/*
 * Used to slow down RGB speed.
 */
static const uint8_t rgb_speed_divisor = 8;

/**
 * @brief Scales down `g_rgb_timer` so that it can be used for RGB effects.
 * @details Usually these calculations aredone internally by some RGB effects.
 This method exposed to scaling so that all effects to have same timebase. If `rgb_matrix_config.speed` all effects are affected the same.
 * @param[in]   factor The factor can be used to speed up some operations in relation to others.
 * @return scaled down timer taking into account the given factor
 * @see g_rgb_timer
 * @see rgb_matrix_config.speed
 */
uint8_t rgb_time_2_scale_w_factor(const uint8_t rgb_speed_factor) {
    const uint8_t scaled_time = scale16by8(g_rgb_timer, rgb_matrix_config.speed * rgb_speed_factor / rgb_speed_divisor);

    return scaled_time;
}

/**
 * @brief Inverse function to calculate time required to execute `timer` steps.
 * @details This method allows calculation of the time needed to execute N `timer`steps.
 Usefull when using a scaled down time but requiring the time needed to perform these steps.
 * @param[in]   scaled_time scaled down timer to inverse to time
 * @return time corresponding to scaled down time
 * @see rgb_time_2_scale()
 */
uint16_t scale_2_rgb_time(const uint8_t scaled_time) {
    const uint16_t time = scaled_time * rgb_speed_divisor * UINT8_MAX / rgb_matrix_config.speed;

    return time;
}

bool fade_in_ranged(const uint8_t time, const uint8_t range_min, const uint8_t range_max) {
    static const uint8_t max_delta = 1;
    return scaled_sin_up(time, range_min, range_max, max_delta, &(rgb_matrix_config.hsv.v));
}

bool fade_out_ranged(const uint8_t time, const uint8_t range_min, const uint8_t range_max) {
    static const uint8_t max_delta = 1;
    return scaled_sin_down(time, range_min, range_max, max_delta, &(rgb_matrix_config.hsv.v));
}

/**
 * @brief Convenience method to eventually skip the value part when setting HSV.
 * @details When setting HSV this includes the value/brightness.
 As changing brightness might interfer with fading or breathing effects,
 this method can skip the value part of HSV (depending on the preprocessor flag: RGB_FADE_IN).
 * @param[in]   hue Hue
 * @param[in]   sat Saturation
 * @param[in]   hue Value (brightness)
 * @see rgb_matrix_sethsv_noeeprom()
 */
void rgb_matrix_sethsv_noeeprom_user(const uint16_t hue, const uint8_t sat, const uint8_t val) {
#if defined(RGB_FADE_IN) || defined(RGB_IDLE_TIMEOUT)
    rgb_matrix_config.hsv.h = hue;
    rgb_matrix_config.hsv.s = sat;
    // omitting setting the value to avoid interfering with effects
//    rgb_matrix_config.hsv.v = val;
#else
    rgb_matrix_sethsv_noeeprom(hue, sat, val);
#endif
}

#if defined(RGB_FADE_IN) || defined(RGB_IDLE_TIMEOUT)
/**
 * @brief Calculates the time offset required by fade in.
 * @details Using an arbitrary timer any point on the sine curve might be pointed to.
 * The offest is calculated so that
 * a) the point is at the lowest point in the curve and the curve is raising
 * b) the point is near the current brightness (eg. fade in might be called while fading out and the lowest value has not yet been reached).
 * @param[in]   time Current time usually represented by (usually scaled) timer
 * @return Offset required so that time matches the current brightness
 */
uint8_t calc_fade_in_offset(const uint8_t time) {
    static const uint8_t max_steps = UINT8_MAX/2;
    static const uint8_t range_min = 0;
    static const uint8_t range_max = RGB_MATRIX_MAXIMUM_BRIGHTNESS;

    // start at the right point in the sine curve
    uint8_t time_offset = offset_for_time(time, PHASE_LOW);

    // find the right offset to match the current brightness
    for (int i = 1; i < max_steps; i++) {
        const uint8_t value = scaled_sin(time + time_offset + 1, range_min, range_max);
        if (in_range(value, range_min, range_max) && value < rgb_matrix_config.hsv.v) {
            time_offset++;
        } else {
            break;
        }
    }

    return time_offset;
}

/**
 * @brief Increases value/brightness until reaching RGB_MATRIX_MAXIMUM_BRIGHTNESS based on given timer.
 * @param[in]   time A (usually scaled) timer
 * @return Returns `true` if RGB_MATRIX_MAXIMUM_BRIGHTNESS has been reached, `false` otherwise.
 */
bool fade_in(const uint8_t time) {
    static const uint8_t range_min = 0;
    static const uint8_t range_max = RGB_MATRIX_MAXIMUM_BRIGHTNESS;

    return fade_in_ranged(time, range_min, range_max);
}
#endif

#if defined(RGB_DISABLE_WITH_FADE_OUT) || defined(RGB_IDLE_TIMEOUT)
/**
 * @brief Calculates the time offset required by fade out.
 * @details Using an arbitrary timer any point on the Sinus curve might be pointed to.
 * The offest is calculated so that
 * a) the point is at the highest point in the curve and the curve is failing
 * b) the point is near the current brightness (eg. fade out might be called while on breath effect).
 * @param[in]   time Current time usually represented by a(usually scaled) timer
 * @return Offset required so that time matches the current brightness
 */
uint8_t calc_fade_out_offset(const uint8_t time) {
    static const uint8_t range_min = 0;
    static const uint8_t range_max = RGB_MATRIX_MAXIMUM_BRIGHTNESS;

    // start at the right point in the sin() curve
    uint8_t time_offset = offset_for_time(time, PHASE_HIGH);

    // find the right offset to match the current brightness
    for (int i = 1; i < 127; i++) {
        const uint8_t value = scaled_sin(time + time_offset + 1, range_min, range_max);
        if (in_range(value, range_min, range_max) && rgb_matrix_config.hsv.v < value) {
            time_offset++;
        } else {
            break;
        }
    }

    return time_offset;
}
#endif

#if defined(RGB_DISABLE_WITH_FADE_OUT)
/**
 * @brief Decreases value/brightness until reaching 0 based on given timer.
 * @param[in]   time A (usually scaled) timer
 * @return Returns `true` if 0 has been reached, `false` otherwise.
 */
bool fade_out(const uint8_t time) {
    static const uint8_t range_min = 0;
    static const uint8_t range_max = RGB_MATRIX_MAXIMUM_BRIGHTNESS;

    return fade_out_ranged(time, range_min, range_max);
}
#endif

#if defined(RGB_IDLE_TIMEOUT)
/**
 * @brief Decreases value/brightness until reaching `RGB_IDLE_MINIMUM_BRIGHTNESS` based on given timer.
 * @param[in]   time A (usually scaled) timer
 * @return Returns `true` if `RGB_IDLE_MINIMUM_BRIGHTNESS` has been reached, `false` otherwise.
 */
bool idle_fade_out(const uint8_t time) {
    static const uint8_t range_min = RGB_IDLE_MINIMUM_BRIGHTNESS;
    static const uint8_t range_max = RGB_MATRIX_MAXIMUM_BRIGHTNESS;

    return fade_out_ranged(time, range_min, range_max);
}

#if defined(RGB_IDLE_BREATHE)
/**
 * @brief Changes value/brightness to create a breathing effect based on given timer.
 * @details Brightness will breathe in the range starting from `RGB_IDLE_MINIMUM_BRIGHTNESS` to `RGB_IDLE_MAXIMUM_BRIGHTNESS`.
 * @param[in]   time A (usually scaled) timer
 */
void idle_breathe(const uint8_t time) {
    static const uint8_t range_min = RGB_IDLE_MINIMUM_BRIGHTNESS;
    static const uint8_t range_max = RGB_IDLE_MAXIMUM_BRIGHTNESS;

    rgb_matrix_config.hsv.v = scaled_sin(time, range_min, range_max);
}
#endif // RGB_IDLE_BREATHE
#endif // RGB_IDLE_TIMEOUT
