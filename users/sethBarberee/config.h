/* Copyright 2021 SethBarberee <seth.barberee@gmail.com>
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
#pragma once

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_SLEEP
#    ifndef RGBLIGHT_HUE_STEP
#        define RGBLIGHT_HUE_STEP 8
#    endif
#    ifndef RGBLIGHT_SAT_STEPT
#        define RGBLIGHT_SAT_STEP 8
#    endif
#    ifndef RGBLIGHT_VAL_STEP
#        define RGBLIGHT_VAL_STEP 8
#    endif

// Trim animations I don't use/like
#    ifdef RGBLIGHT_ANIMATIONS
#        undef RGBLIGHT_ANIMATIONS
#    endif
#    ifndef RGBLIGHT_EFFECT_BREATHING
#        define RGBLIGHT_EFFECT_BREATHING
#    endif
#    ifndef RGBLIGHT_EFFECT_STATIC_GRADIENT
#        define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    endif
#    ifndef RGBLIGHT_EFFECT_TWINKLE
#        define RGBLIGHT_EFFECT_TWINKLE
#    endif
#    ifdef RGBLIGHT_DEFAULT_MODE
#        undef RGBLIGHT_DEFAULT_MODE
#        define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_TWINKLE
#    endif

#    ifndef CAPS_LOCK_MODE
#        define CAPS_LOCK_MODE RGBLIGHT_MODE_STATIC_LIGHT
#    endif
#endif // RGBLIGHT_ENABLE

#ifndef AUDIO_ENABLE
#    define NO_MUSIC_MODE
#endif // AUDIO_ENABLE

#define FORCE_NKRO // Force NKRO on by default

// Totally taken from @drashna's userspace
#ifdef TAPPING_TERM
#    undef TAPPING_TERM
#endif // TAPPING_TERM
//
// Keeping these commented for examples when I want to tweak per keyboard
// but setting a default across my boards for now
//
//#if defined(KEYBOARD_ergodox_ez)
//#    define TAPPING_TERM 185
#if defined(KEYBOARD_crkbd)
#    define TAPPING_TERM 185
#else
#    define TAPPING_TERM 200
#endif

#if !defined(LAYER_STATE_16BIT) && !defined(LAYER_STATE_8BIT) && !defined(LAYER_STATE_32BIT)
#    define LAYER_STATE_8BIT
#endif

/* Disable unused and unneeded features to reduce on firmware size */
#ifdef LOCKING_SUPPORT_ENABLE
#    undef LOCKING_SUPPORT_ENABLE
#endif
#ifdef LOCKING_RESYNC_ENABLE
#    undef LOCKING_RESYNC_ENABLE
#endif
