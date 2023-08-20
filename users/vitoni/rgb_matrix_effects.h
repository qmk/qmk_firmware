// Copyright 2021 Victor Toni (@vitoni)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

/**
 * States reflecting the state of the keyboard.
 * Dependeing on these states various effects can set for the RGB matrix.
 */
enum states {
    REGULAR             //!< when in regular use
#if defined(RGB_IDLE_TIMEOUT)
    ,IDLE_FADE_OUT      //!< when started idling
    ,IDLE               //!< when idling
#endif
#if defined(RGB_FADE_IN) || defined(RGB_IDLE_TIMEOUT)
    ,FADE_IN            //!< when starting initially or before going back to REGULAR
#endif
#if defined(RGB_DISABLE_WITH_FADE_OUT)
    ,FADE_OUT           //!< before supending
#endif
    ,SUSPENDED          //!< expecting to be suspended by RGB_MATRIX_TIMEOUT any time
};

/**
 * @brief Scales down `g_rgb_timer` so that it can be used for RGB effects.
 * @details Usually these calculations aredone internally by some RGB effects.
 This method exposed to scaling so that all effects to have same timebase. If `rgb_matrix_config.speed` all effects are affected the same.
 * @param[in]   factor The factor can be used to speed up some operations in relation to others.
 * @return scaled down timer taking into account the given factor
 * @see g_rgb_timer
 * @see rgb_matrix_config.speed
 */
uint8_t rgb_time_2_scale_w_factor(const uint8_t factor);

/**
 * @brief Scales down `g_rgb_timer` so that it can be used for RGB effects.
 * @return scaled down timer
 * @see rgb_time_2_scale_w_factor()
 */
uint8_t rgb_time_2_scale(void);

/**
 * @brief Inverse function to calculate time required to execute `timer` steps.
 * @details This method allows calculation of the time needed to execute N `timer`steps.
 Usefull when using a scaled down time but requiring the time needed to perform these steps.
 * @param[in]   scaled_time scaled down timer to inverse to time
 * @return time corresponding to scaled down time
 * @see rgb_time_2_scale()
 */
uint16_t scale_2_rgb_time(const uint8_t scaled_time);

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
void rgb_matrix_sethsv_noeeprom_user(const uint16_t hue, const uint8_t sat, const uint8_t val);

#if defined(RGB_FADE_IN) || defined(RGB_DISABLE_WITH_FADE_OUT) || defined(RGB_IDLE_TIMEOUT)
#   if defined(RGB_MATRIX_MAXIMUM_BRIGHTNESS)
#       if (RGB_MATRIX_MAXIMUM_BRIGHTNESS) < 1
#           error "RGB_MATRIX_MAXIMUM_BRIGHTNESS must not be less than ONE"
#       endif
#       if UINT8_MAX < (RGB_MATRIX_MAXIMUM_BRIGHTNESS)
#           error "RGB_MATRIX_MAXIMUM_BRIGHTNESS must not be larger than UINT8_MAX"
#       endif
#   else
#       define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#   endif
#endif

#if defined(RGB_FADE_IN) || defined(RGB_IDLE_TIMEOUT)
/**
 * @brief Calculates the time offset required by fade in.
 * @details Using an arbitrary timer any point on the sine curve might be pointed to.
 * The offset is calculated so that
 * a) the point is at the lowest point in the curve and the curve is raising
 * b) the point is near the current brightness (eg. fade in might be called while fading out and the lowest value has not yet been reached).
 * @param[in]   time Current time usually represented by a(usually scaled) timer
 * @return Offset required so that time matches the current brightness
 */
uint8_t calc_fade_in_offset(const uint8_t time);

/**
 * @brief Increases value/brightness until reaching RGB_MATRIX_MAXIMUM_BRIGHTNESS based on given timer.
 * @param[in]   time A (usually scaled) timer
 * @return Returns `true` if RGB_MATRIX_MAXIMUM_BRIGHTNESS has been reached, `false` otherwise.
 */
bool fade_in(const uint8_t time);
#endif

#if defined(RGB_DISABLE_WITH_FADE_OUT)
#   if !defined(RGB_MATRIX_TIMEOUT)
#       warning "RGB_DISABLE_WITH_FADE_OUT expects RGB_MATRIX_TIMEOUT to be defined"
#   endif
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
uint8_t calc_fade_out_offset(const uint8_t time);
#endif

#if defined(RGB_DISABLE_WITH_FADE_OUT)
/**
 * @brief Decreases value/brightness until reaching 0 based on given timer.
 * @param[in]   time A (usually scaled) timer
 * @return Returns `true` if 0 has been reached, `false` otherwise.
 */
bool fade_out(const uint8_t time);
#endif

#if defined(RGB_IDLE_TIMEOUT)
#   if RGB_IDLE_TIMEOUT < 0
#       error "RGB_IDLE_TIMEOUT must not be less than ZERO"
#   endif
#   if !defined(RGB_IDLE_MINIMUM_BRIGHTNESS)
        // minimum brightness when idling
#       define RGB_IDLE_MINIMUM_BRIGHTNESS (RGB_MATRIX_MAXIMUM_BRIGHTNESS/5)
#   endif
#   if RGB_IDLE_MINIMUM_BRIGHTNESS < 0
#       error "RGB_IDLE_MINIMUM_BRIGHTNESS must not be less than ZERO"
#   endif // RGB_IDLE_MINIMUM_BRIGHTNESS < 0
#   if RGB_MATRIX_MAXIMUM_BRIGHTNESS <= RGB_IDLE_MINIMUM_BRIGHTNESS
#       error "RGB_IDLE_MINIMUM_BRIGHTNESS must be less than RGB_MATRIX_MAXIMUM_BRIGHTNESS"
#   endif // RGB_MATRIX_MAXIMUM_BRIGHTNESS <= RGB_IDLE_MINIMUM_BRIGHTNESS

/**
 * @brief Decreases value/brightness until reaching `RGB_IDLE_MINIMUM_BRIGHTNESS` based on given timer.
 * @param[in]   time A (usually scaled) timer
 * @return Returns `true` if `RGB_IDLE_MINIMUM_BRIGHTNESS` has been reached, `false` otherwise.
 */
bool idle_fade_out(const uint8_t time);

#if defined(RGB_IDLE_BREATHE)
#   if !defined(RGB_IDLE_MAXIMUM_BRIGHTNESS)
        // maximum brightness when idling
#       define RGB_IDLE_MAXIMUM_BRIGHTNESS (RGB_MATRIX_MAXIMUM_BRIGHTNESS*3/5)
#   endif
#   if !(0 <= RGB_IDLE_MAXIMUM_BRIGHTNESS)
#       error "RGB_IDLE_MINIMUM_BRIGHTNESS must not be less than ZERO, was: " RGB_IDLE_MAXIMUM_BRIGHTNESS
#   endif // RGB_IDLE_MAXIMUM_BRIGHTNESS < 0
#   if !(RGB_IDLE_MINIMUM_BRIGHTNESS < RGB_IDLE_MAXIMUM_BRIGHTNESS)
#       error "RGB_IDLE_MINIMUM_BRIGHTNESS must be less than RGB_IDLE_MAXIMUM_BRIGHTNESS"
#   endif // RGB_IDLE_MAXIMUM_BRIGHTNESS <= RGB_IDLE_MINIMUM_BRIGHTNESS
#   if !(RGB_IDLE_MAXIMUM_BRIGHTNESS <= RGB_MATRIX_MAXIMUM_BRIGHTNESS)
#       error "RGB_IDLE_MAXIMUM_BRIGHTNESS must be less than or equal to RGB_MATRIX_MAXIMUM_BRIGHTNESS"
#   endif // RGB_MATRIX_MAXIMUM_BRIGHTNESS <= RGB_IDLE_MAXIMUM_BRIGHTNESS

/**
 * @brief Changes value/brightness to create a breathing effect based on given timer.
 * @details Brightness will breathe in the range starting from `RGB_IDLE_MINIMUM_BRIGHTNESS` to `RGB_IDLE_MAXIMUM_BRIGHTNESS`.
 * @param[in]   time A (usually scaled) timer
 */
void idle_breathe(const uint8_t time);
#endif // RGB_IDLE_BREATHE

#endif // RGB_IDLE_TIMEOUT
