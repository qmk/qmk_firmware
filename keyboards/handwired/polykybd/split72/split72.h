/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once


#define LAYOUT_left_right_stacked(\
    lc0r0, lc1r0 ,lc2r0, lc3r0, lc4r0, lc5r0 ,lc6r0, \
    lc0r1, lc1r1 ,lc2r1, lc3r1, lc4r1, lc5r1 ,lc6r1, \
    lc0r2, lc1r2 ,lc2r2, lc3r2, lc4r2, lc5r2 ,lc6r2, lc7r3, \
    lc0r3, lc1r3 ,lc2r3, lc3r3, lc4r3, lc5r3 ,lc6r3, lc7r4, \
    lc0r4, lc1r4 ,lc2r4, lc3r4,        lc4r4 ,lc5r4, lc6r4, \
    \
           rc1r0 ,rc2r0, rc3r0, rc4r0, rc5r0 ,rc6r0, rc7r0, \
           rc1r1 ,rc2r1, rc3r1, rc4r1, rc5r1 ,rc6r1, rc7r1, \
    rc0r3, rc1r2 ,rc2r2, rc3r2, rc4r2, rc5r2 ,rc6r2, rc7r2, \
    rc0r4, rc1r3 ,rc2r3, rc3r3, rc4r3, rc5r3 ,rc6r3, rc7r3, \
    rc1r4, rc2r4 ,rc3r4,        rc4r4, rc5r4 ,rc6r4, rc7r4 \
  ) { \
    { lc0r0, lc1r0 ,lc2r0, lc3r0, lc4r0, lc5r0 ,lc6r0, KC_NO }, \
    { lc0r1, lc1r1 ,lc2r1, lc3r1, lc4r1, lc5r1 ,lc6r1, KC_NO }, \
    { lc0r2, lc1r2 ,lc2r2, lc3r2, lc4r2, lc5r2 ,lc6r2, KC_NO }, \
    { lc0r3, lc1r3 ,lc2r3, lc3r3, lc4r3, lc5r3 ,lc6r3, lc7r3 }, \
    { lc0r4, lc1r4 ,lc2r4, lc3r4, lc4r4, lc5r4 ,lc6r4, lc7r4 }, \
    \
    { KC_NO, rc1r0 ,rc2r0, rc3r0, rc4r0, rc5r0 ,rc6r0, rc7r0 }, \
    { KC_NO, rc1r1 ,rc2r1, rc3r1, rc4r1, rc5r1 ,rc6r1, rc7r1 }, \
    { KC_NO, rc1r2 ,rc2r2, rc3r2, rc4r2, rc5r2 ,rc6r2, rc7r2 }, \
    { rc0r3, rc1r3 ,rc2r3, rc3r3, rc4r3, rc5r3 ,rc6r3, rc7r3 }, \
    { rc0r4, rc1r4 ,rc2r4, rc3r4, rc4r4, rc5r4 ,rc6r4, rc7r4 } \
}
