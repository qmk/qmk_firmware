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

#define BERRY_COLORS 4
HSV berryColorsHsv[BERRY_COLORS] = {
    {HSV_PURPLE},
    {HSV_CYAN},
    {HSV_MAGENTA},
    {HSV_TEAL}
};

int colorIndex = 0;
int nextIndex = 0;
long int colorCounter = 0;
long int colorRepeat = 100000;

static HSV berryLerpImpl(HSV hsv, uint8_t i, uint8_t time) {
    colorCounter += (int)(rgb_matrix_config.speed / 8);

    if (colorCounter >= colorRepeat) {
        colorIndex += 1;
        if (colorIndex == BERRY_COLORS) {
            colorIndex = 0;
        }
        colorCounter = 0;
    }

    nextIndex = colorIndex + 1;
    if (nextIndex == BERRY_COLORS) {
        nextIndex = 0;
    }

    HSV a = berryColorsHsv[colorIndex];
    HSV b = berryColorsHsv[nextIndex];

    float t = (1.0f * colorCounter) / (1.0f * colorRepeat);
    return hsvLerp(a, b, t);
}

bool berryLerp(effect_params_t* params) { return effect_runner_i(params, &berryLerpImpl); }

