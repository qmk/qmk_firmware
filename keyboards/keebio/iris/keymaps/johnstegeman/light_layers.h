// Copyright 2022 Ignacy Radliński (@radlinskii)
// SPDX-License-Identifier: GPL-2.0-or-later

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

const rgblight_segment_t LOWER_LIGHT_LAYER[] = RGBLIGHT_LAYER_SEGMENTS(
    {14, 3, HSV_RED},
    {19, 1, HSV_RED}
);


const rgblight_segment_t* const PROGMEM MY_LIGHT_LAYERS[] = RGBLIGHT_LAYERS_LIST(
    COLEMAK_LIGHT_LAYER,
    LOWER_LIGHT_LAYER
);
