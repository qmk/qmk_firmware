/* Copyright 2021 JasonRen(biu)
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
#include QMK_KEYBOARD_H



#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        {0, NO_LED, 1, 2, 3, 4, NO_LED, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, \
        {32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, NO_LED, 19, 18, 17, 16}, \
        {33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, NO_LED, 46, 47, 48, 49}, \
        {62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, NO_LED, NO_LED, 50, NO_LED, NO_LED, NO_LED}, \
        {63, NO_LED, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, NO_LED, NO_LED, NO_LED, 75, NO_LED}, \
        {86, 85, 84, NO_LED, NO_LED, NO_LED, 83, NO_LED, NO_LED, NO_LED, 82, 81, 80, NO_LED, 79, 78, 77, 76}
    },
    {
      // LED Index to Physical Position
        {0,0},      {26,0},{40,0},{53,0},{66,0},        {92,0},{105,0},{119,0},{132,0},{145,0},{158,0},{171,0},{184,0},{198,0},{211,0},{224,0}, \
        {211,13},{198,13},{184,13},{171,13},    {158,13},{145,13},{132,13},{119,13},{105,13},{92,13},{79,13},{66,13},{53,13},{40,13},{26,13},{13,13},{0,13}, \
        {0,26},{13,26},{26,26},{40,26},{53,26},{66,26},{79,26},{92,26},{105,26},{119,26},{132,26},{145,26},{158,26},    {184,26},{198,26},{211,26},{224,26}, \
        {184,38},             {158,38},{145,38},{132,38},{119,38},{105,38},{92,38},{79,38},{66,38},{53,38},{40,38},{26,38},{0,38}, \
        {0,51},    {13,51},{26,51},{40,51},{53,51},{66,51},{79,51},{92,51},{105,51},{119,51},{132,51},{145,51},              {211,51}, \
        {224,64},{211,64},{198,64},{184,64},        {158,64},{145,64},{132,64},     {92,64},        {26,64},{13,64},{0,64}
    },
    {
      // LED Index to Flag
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, \
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, \
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, \
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, \
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
    }
};


#endif

#ifdef RGB_DISABLE_WHEN_USB_SUSPENDED
void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif
