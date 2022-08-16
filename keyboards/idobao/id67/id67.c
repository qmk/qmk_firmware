/* Copyright 2021 Tybera
 * Copyright 2021 thewerther
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

#include "id67.h"

#define __ NO_LED

#if defined(RGB_MATRIX_ENABLE)

/* NB!!: Indices are reversed on the physical board, top left is bottom right.
 * These "LED Index to *" arrays are in that reversed order!
 * i.e., Space row on top, listed right to left */
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    {66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52},
    {51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37},
    {36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, __, 24, 23},
    {22, __, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10,  9},
    { 8,  7, __,  6, __, __,  5, __, __, __,  4,  3,  2,  1,  0},
}, {
    // LED Index to Physical Position
    // based on: https://gist.github.com/vinorodrigues/07fd735683856b2a06c7c52b9b3878cb
    {224, 64}, {209, 64}, {194, 64}, {170, 64}, {151, 64},                                  {95, 64},                      {39, 64},           {21, 64}, {2, 64},
    {224, 48}, {209, 48}, {189, 48}, {168, 48}, {153, 48}, {138, 48}, {123, 48}, {108, 48}, {93, 48},  {78, 48}, {63, 48}, {49, 48}, {34, 48},           {9, 48},
    {224, 32}, {200, 32},            {175, 32}, {161, 32}, {146, 32}, {131, 32}, {116, 32}, {101, 32}, {86, 32}, {71, 32}, {56, 32}, {41, 32}, {26, 32}, {6, 32},
    {224, 16}, {205, 16}, {187, 16}, {172, 16}, {157, 16}, {142, 16}, {127, 16}, {112, 16}, {97, 16},  {82, 16}, {67, 16}, {52, 16}, {37, 16}, {22, 16}, {4, 16},
    {224, 0},  {202, 0},  {179, 0},  {164, 0},  {149, 0},  {134, 0},  {119, 0},  {105, 0},  {90, 0},   {75, 0},  {60, 0},  {45, 0},  {30, 0},  {15, 0},  {0, 0}
    #ifndef ID67_DISABLE_UNDERGLOW
    // underglow LEDs
    , {0, 0}, {56, 0}, {112, 0}, {168, 0}, {224, 0},
    {224, 64}, {168, 64}, {112, 64}, {56, 64}, {0, 64}
    #endif
},  {
    // LED Index to Flag
    4, 4, 4, 1, 1,          4,       1,    1, 1,  // first row
    1, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,  // second row
    1,    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9,  // third row
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,  // fourth row
    1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4   // fifth row
    // underglow LEDs
    #ifndef ID67_DISABLE_UNDERGLOW
    , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
    #endif
} };

#endif  // #ifdef RGB_MATRIX_ENABLE


/* Use `#define ID67_CAPS_LOCK_KEY_INDEX 36` in `keymaps/yourkeymap/config.h`
 * if you want to enable Caps-Lock LED mode */
#if defined(RGB_MATRIX_ENABLE) && defined(ID67_CAPS_LOCK_KEY_INDEX)

#define ID67_CAPS_LOCK_MAX_BRIGHTNESS 0xFF
#ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #undef ID67_CAPS_LOCK_MAX_BRIGHTNESS
    #define ID67_CAPS_LOCK_MAX_BRIGHTNESS RGB_MATRIX_MAXIMUM_BRIGHTNESS
#endif

#define ID67_CAPS_LOCK_VAL_STEP 8
#ifdef RGB_MATRIX_VAL_STEP
    #undef ID67_CAPS_LOCK_VAL_STEP
    #define ID67_CAPS_LOCK_VAL_STEP RGB_MATRIX_VAL_STEP
#endif

/* This function is defined as weak, so if you create your own in keymap then
 * that will compile, not this */
__attribute__((weak))
void rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        uint8_t b = rgb_matrix_get_val();
        if (b < ID67_CAPS_LOCK_VAL_STEP) {
            b = ID67_CAPS_LOCK_VAL_STEP;
        } else if (b < (ID67_CAPS_LOCK_MAX_BRIGHTNESS - ID67_CAPS_LOCK_VAL_STEP)) {
            b += ID67_CAPS_LOCK_VAL_STEP;  // one step more than current brightness
        } else {
            b = ID67_CAPS_LOCK_MAX_BRIGHTNESS;
        }
        rgb_matrix_set_color(ID67_CAPS_LOCK_KEY_INDEX, b, b, b);  // white, with the adjusted brightness
    }
}

#endif // #ifdef ID67_CAPS_LOCK_KEY_INDEX
