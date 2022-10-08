/* Copyright 2020 Jonathan Rascher
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

/* Enable NKRO by default. All my devices support this, and it enables me to
 * dispense with the NK_TOGG key, thus saving firmware space by not compiling
 * magic keycode support.
 */
#define FORCE_NKRO

/* Wait between tap_code register and unregister to fix flaky media keys. */
#undef TAP_CODE_DELAY

#define TAP_CODE_DELAY 20

/* Treat mod-tap keys as holds even if the mod-tap key and the key being
 * modified are both released within TAPPING_TERM. This assumes the mod-tap key
 * isn't usually pressed in quick succession with other tapped keys, which is
 * good when the tap keycode is something like KC_ESC rather than a letter.
 */
#define PERMISSIVE_HOLD

/* Turn off key repeat support of the tap keycode for tap-hold keys, enabling
 * holds to work correctly in quick succession after taps.
 */
#define TAPPING_FORCE_HOLD

#if defined(OLED_ENABLE)
/* The built-in OLED timeout wakes the OLED screen every time the buffer is
 * updated, even if no user activity has occurred recently. This prevents the
 * OLED from ever turning off during a continuously running animation. To avoid
 * this, we disable the default timeout and implement our own in
 * oled_task_user.
 */
#    undef OLED_TIMEOUT
#    define OLED_DISABLE_TIMEOUT

#    if defined(SPLIT_KEYBOARD)
/* Sync OLED on/off state between halves of split keyboards. */
#        define SPLIT_OLED_ENABLE
#    endif
#endif

#if defined(RGB_MATRIX_ENABLE)
/* Turn off per-key RGB when the host goes to sleep. */
#    define RGB_DISABLE_WHEN_USB_SUSPENDED

/* Keep per-key RGB increments consistent across keyboards. */
#    undef RGB_MATRIX_HUE_STEP
#    undef RGB_MATRIX_SAT_STEP
#    undef RGB_MATRIX_VAL_STEP
#    undef RGB_MATRIX_SPD_STEP

#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 17
#    define RGB_MATRIX_VAL_STEP 17
#    define RGB_MATRIX_SPD_STEP 17

/* Enable specific per-key animation modes. */
#    define ENABLE_RGB_MATRIX_ALPHAS_MODS
#    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#    define ENABLE_RGB_MATRIX_BAND_SAT
#    define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#    define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#    define ENABLE_RGB_MATRIX_BAND_VAL
#    define ENABLE_RGB_MATRIX_BREATHING
#    define ENABLE_RGB_MATRIX_CYCLE_ALL
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#    define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#    define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#    define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#    define ENABLE_RGB_MATRIX_DUAL_BEACON
#    define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    define ENABLE_RGB_MATRIX_HUE_BREATHING
#    define ENABLE_RGB_MATRIX_HUE_PENDULUM
#    define ENABLE_RGB_MATRIX_HUE_WAVE
#    define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#    define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#    define ENABLE_RGB_MATRIX_PIXEL_RAIN
#    define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#    define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#    define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#    define ENABLE_RGB_MATRIX_RAINDROPS

/* Enable additional per-key animation modes that require a copy of the
 * framebuffer (with accompanying storage cost).
 */
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#    define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#endif

#if defined(RGBLIGHT_ENABLE)
/* Turn off RGB underglow when the host goes to sleep. */
#    define RGBLIGHT_SLEEP

/* Keep RGB underglow level increments consistent across keyboards. */
#    undef RGBLIGHT_HUE_STEP
#    undef RGBLIGHT_SAT_STEP
#    undef RGBLIGHT_VAL_STEP

#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 17
#    define RGBLIGHT_VAL_STEP 17

/* Enable specific underglow animation modes. (Skip TWINKLE because it seems to
 * be broken on ARM: https://github.com/qmk/qmk_firmware/issues/15345.)
 */
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#endif

#if defined(BACKLIGHT_ENABLE)
/* Enable backlight breathing across the board. */
#    define BACKLIGHT_BREATHING

/* Keep backlight level increments consistent across keyboards. */
#    undef BACKLIGHT_LEVELS

#    define BACKLIGHT_LEVELS 7
#endif

/* Turn off unused config options to reduce firmware size. */
#define LAYER_STATE_8BIT
#define NO_ACTION_ONESHOT
#undef LOCKING_RESYNC_ENABLE
#undef LOCKING_SUPPORT_ENABLE
