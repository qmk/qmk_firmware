/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2022 Daniel Kao <daniel.m.kao@gmail.com>
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

#include "cirque_pinnacle.h"
#include "report.h"

#ifndef CIRQUE_PINNACLE_TAPPING_TERM
#    include "action.h"
#    include "action_tapping.h"
#    define CIRQUE_PINNACLE_TAPPING_TERM GET_TAPPING_TERM(KC_BTN1, &(keyrecord_t){})
#endif
#ifndef CIRQUE_PINNACLE_TOUCH_DEBOUNCE
#    define CIRQUE_PINNACLE_TOUCH_DEBOUNCE (CIRQUE_PINNACLE_TAPPING_TERM * 8)
#endif

typedef enum {
    SCROLL_UNINITIALIZED,
    SCROLL_DETECTING,
    SCROLL_VALID,
    NOT_SCROLL,
} circular_scroll_status_t;

typedef struct {
    int8_t v;
    int8_t h;
    bool   suppress_touch;
} circular_scroll_t;

typedef struct {
    float                    mag;
    int16_t                  x;
    int16_t                  y;
    uint16_t                 z;
    circular_scroll_status_t state;
    bool                     axis;
    // settings
    float   outer_ring_pct; // width of outer ring
    float   movement_pct;   // amount of movement before triggering scroll validation
    float   movement_ratio; // ratio of movement along perimeter / movement towards center
    uint8_t wheel_clicks;   // how many clicks to report in a half circle
} circular_scroll_context_t;

typedef struct {
    uint16_t timer;
    bool     touchDown;
} trackpad_tap_context_t;

typedef struct {
    bool tap_enable;
    bool circular_scroll_enable;
} cirque_pinnacle_features_t;

bool cirque_pinnacle_gestures(report_mouse_t* mouse_report, pinnacle_data_t touchData);
void cirque_pinnacle_enable_tap(bool enable);
void cirque_pinnacle_enable_circular_scroll(bool enable);
void cirque_pinnacle_configure_circular_scroll(float outer_ring_pct, float movement_pct, float movement_ratio, uint8_t wheel_clicks);
