/*
Copyright 2023 John Stegeman

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

/*

LED index mapping:

          (31)              (32)              (33)                                    (67)              (66)              (65)
┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
│0       │1       │2       │3       │4       │5       │                          │39      │38      │37      │36      │35      │34      │
├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
│11      │10      │9       │8       │7       │6       │                          │40      │41      │42      │43      │44      │45      │
├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
│12      │13      │14      │15      │16      │17      │                          │51      │50      │49      │48      │47      │46      │
├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
│23      │22      │21      │20      │19      │18      │27      │        │61      │52      │53      │54      │55      │56      │57      │
└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                               │24      │25      │26      │                 │60      │59      │58      │
                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
          (30)              (29)              (28)                                    (62)              (63)              (64)

*/

const rgblight_segment_t PROGMEM COLEMAK_LIGHT_LAYER[] = RGBLIGHT_LAYER_SEGMENTS(
    // left side
    {0, 6, HSV_BLUE},
    {6, 5, HSV_AZURE},
    {11, 2, HSV_BLUE},
    {13, 10, HSV_AZURE},
    {23, 2, HSV_BLUE},
    {25, 1, HSV_RED},
    {26, 2, HSV_BLUE},
    {28, 3, HSV_BLUE}, // underglow
    {31, 3, HSV_BLUE}, // underglow
    // right side
    {34, 6, HSV_BLUE},
    {40, 4, HSV_AZURE},
    {44, 3, HSV_BLUE},
    {47, 7, HSV_AZURE},
    {54, 5, HSV_BLUE},
    {59, 1, HSV_RED},
    {60, 2, HSV_BLUE},
    {62, 3, HSV_BLUE}, // underglow
    {65, 3, HSV_BLUE} // underglow
);

const rgblight_segment_t PROGMEM NAVNUM_LIGHT_LAYER[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 14, HSV_BLACK},
    {14, 3, HSV_GREEN},
    {17, 2, HSV_BLACK},
    {19, 1, HSV_GREEN},
    {20, 21, RGB_OFF},
    {41, 3, HSV_GREEN},
    {44, 4, HSV_BLACK},
    {48, 3, HSV_GREEN},
    {51, 2, HSV_BLACK},
    {53, 3, HSV_GREEN},
    {56, 2, HSV_BLACK},
    {58, 1, HSV_GREEN},
    {59, 9, HSV_BLACK} 
);


const rgblight_segment_t* const PROGMEM MY_LIGHT_LAYERS[] = RGBLIGHT_LAYERS_LIST(
    COLEMAK_LIGHT_LAYER,
    NAVNUM_LIGHT_LAYER
);