/*
Copyright 2023 Spencer Deven <splitlogicdesign@gmail.com>
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
#include "quantum.h"
#include "print.h"
#include "display.h"

static bool display_enabled;

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
// Key Matrix to LED Index
  // Left Hand
  { 8, 6, 5, 3, 2, 0, NO_LED },
  { 9, 10, 11, 12, 13, 14, 15 },
  { 24, 22, 21, 19, 18, 17, 31 },
  { 25, 26, 27, 28, 29, 30, 32 },
  { 43, 41, 40, 38, 37, 35, 33 },
  // Right Hand
  { 52, 50, 49, 47, 46, 44, NO_LED },
  { 53, 54, 55, 56, 57, 58, 59 },
  { 68, 66, 65, 63, 62, 61, 75 },
  { 69, 70, 71, 72, 73, 74, 76 },
  { 87, 85, 84, 82, 81, 79, 77 },


},
{
{ 80, 10 },
{ 74, 2 },
{ 64, 9 },
{ 49, 7 },
{ 38, 1 },
{ 33, 9 },
{ 18, 13 },
{ 9, 5 },
{ 2, 13 },
{ 2, 24 },
{ 18, 24 },
{ 33, 19 },
{ 49, 18 },
{ 64, 20 },
{ 80, 21 },
{ 96, 37 },
{ 91, 29 },
{ 80, 32 },
{ 64, 31 },
{ 49, 29 },
{ 41, 29 },
{ 33, 30 },
{ 18, 35 },
{ 10, 35 },
{ 2, 35 },
{ 2, 45 },
{ 18, 45 },
{ 33, 41 },
{ 49, 40 },
{ 64, 41 },
{ 80, 42 },
{ 96, 49 },
{ 108, 54 },
{ 102, 64 },
{ 93, 61 },
{ 85, 58 },
{ 72, 53 },
{ 64, 52 },
{ 49, 50 },
{ 41, 52 },
{ 33, 52 },
{ 18, 56 },
{ 10, 57 },
{ 2, 56 },
{ 142, 10 },
{ 149, 2 },
{ 158, 9 },
{ 174, 7 },
{ 185, 1 },
{ 190, 9 },
{ 205, 13 },
{ 213, 5 },
{ 220, 13 },
{ 220, 24 },
{ 205, 24 },
{ 190, 19 },
{ 174, 18 },
{ 158, 20 },
{ 142, 21 },
{ 126, 37 },
{ 133, 29 },
{ 142, 32 },
{ 158, 31 },
{ 174, 29 },
{ 182, 29 },
{ 190, 30 },
{ 205, 35 },
{ 213, 35 },
{ 220, 35 },
{ 220, 45 },
{ 205, 45 },
{ 190, 41 },
{ 174, 40 },
{ 158, 41 },
{ 142, 42 },
{ 127, 49 },
{ 113, 54 },
{ 120, 64 },
{ 129, 61 },
{ 138, 58 },
{ 151, 53 },
{ 158, 52 },
{ 174, 50 },
{ 182, 52 },
{ 190, 52 },
{ 205, 56 },
{ 214, 57 },
{ 220, 56 },
},
{
  // LED Index to Flag
 4, 4, 4, 4, 4, 4, 4,
 4, 4, 4, 4, 4, 4, 4,
 4, 4, 4, 4, 4, 4, 4,
 4, 4, 4, 4, 4, 4, 4,
 4, 4, 4, 4, 4, 4, 4,
 4, 4, 4, 4, 4, 4, 4,
 4, 4, 4, 4, 4, 4, 4,
 4, 4, 4, 4, 4, 4, 4,
 4, 4, 4, 4, 4, 4, 4,
 4, 4, 4, 4, 4, 4, 4,
 4, 4, 4, 4, 4, 4, 4,
 4, 4, 4, 4, 4, 4, 4,
 4, 4, 4, 4
} };
#endif

void housekeeping_task_kb(void) {
    display_housekeeping_task();

    housekeeping_task_user();
}

void keyboard_post_init_kb(void)
{
    display_enabled = display_init_kb();

    keyboard_post_init_user();
}
