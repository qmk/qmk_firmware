/* Copyright 2021 Vincent Santillo (vincentsantillo@gmail.com)
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

static HSV hsvLerp(HSV a, HSV b, float t) {
    // Prepare incoming hue values in QMK format
    // QMK HSV Values are [0, 255], representing a Hue value from [0, 360] degrees
    float a_h = a.h / 255.0f; // Map QMK HSV from [0, 1]
    float b_h = b.h / 255.0f;
    float d = b_h - a_h;

    // If a.h > b.h, swap variables
    if (a_h > b_h) {
        float temp_h = b_h;
        b_h = a_h;
        a_h = temp_h;

        d = -d;
        t = 1.0f - t;
    }

    // Calculate the Hue in HSV space
    float h = 0.0f;
    if (d > 0.5f) {
        a_h = a_h + 1.0f;
        h = fmod((a_h + t * (b_h - a_h)), 1);
    } else if (d <= 0.5f) {
        h = a_h + t * d;
    }

    // Set and interpolate
    HSV hsv;
    hsv.h = (uint8_t)(255*h);
    hsv.s = 255;
    hsv.v = 255;

    // Return HSV value
    return hsv;
}
