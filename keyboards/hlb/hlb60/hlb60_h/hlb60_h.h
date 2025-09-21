/*
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

#include "quantum.h"

#define CAPS_LOCK_ENABLE true
#define CAPS_LOCK_COLOR HSV_GREEN

#define LAYER_FN_COLOR HSV_PURPLE
#define LAYER_MEDIA_COLOR HSV_ORANGE
#define LAYER_GAMING_COLOR HSV_CYAN
#define LAYER_MAC_COLOR HSV_RED
#define LAYER_INDIC_COLOR HSV_WHITE

enum layers {
    _BASE = 0,
    _FN,
    _MEDIA,
    _GAME,
    _MAC,
};

enum hlbKeycodes {
    LAY_INDIC_RGB = QK_KB_0,
};
