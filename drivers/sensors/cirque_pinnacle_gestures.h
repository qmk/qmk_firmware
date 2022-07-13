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

typedef struct {
    bool tap_enable;
    bool circular_scroll_enable;
} cirque_pinnacle_features_t;

#ifdef CIRQUE_PINNACLE_TAP_ENABLE
#    ifndef CIRQUE_PINNACLE_TAPPING_TERM
#        include "action.h"
#        include "action_tapping.h"
#        define CIRQUE_PINNACLE_TAPPING_TERM GET_TAPPING_TERM(KC_BTN1, &(keyrecord_t){})
#    endif
#    ifndef CIRQUE_PINNACLE_TOUCH_DEBOUNCE
#        define CIRQUE_PINNACLE_TOUCH_DEBOUNCE (CIRQUE_PINNACLE_TAPPING_TERM * 8)
#    endif

typedef struct {
    uint16_t timer;
    bool     touchDown;
} trackpad_tap_context_t;

/* Enable/disable tap gesture */
void cirque_pinnacle_enable_tap(bool enable);
#endif

#ifdef CIRQUE_PINNACLE_CIRCULAR_SCROLL_ENABLE
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
    uint8_t  outer_ring_pct; /* Width of outer ring, given as a percentage of the radius */
    uint8_t  trigger_px;     /* Amount of movement before triggering scroll validation, in pixels 0~127 */
    uint16_t trigger_ang;    /* Angle required to validate scroll, in radians where pi = 32768 */
    uint8_t  wheel_clicks;   /* How many clicks to report in a circle */
    bool     left_handed;    /* Whether scrolling should be flipped for left handed use */
} circular_scroll_config_t;

typedef struct {
    circular_scroll_config_t config;
    circular_scroll_status_t state;
    uint8_t                  mag;
    int8_t                   x;
    int8_t                   y;
    uint16_t                 z;
    bool                     axis;
} circular_scroll_context_t;

/* Enable/disable circular scroll gesture */
void cirque_pinnacle_enable_circular_scroll(bool enable);

/*
 * Configure circular scroll gesture.
 * Trackpad can be configured to act exclusively as a scroll wheel with outer_ring_pct = 0, trigger_px = 0, trigger_ang = 0.
 * @param outer_ring_pct Width of outer ring from which to begin scroll validation, given as a percentage of the radius.
 * @param trigger_px Amount of movement before triggering scroll validation. Expressed in pixels, trackpad coordinates are scaled to radius of 128 pixels for circular scroll.
 * @param triger_ang Angle required to validate scroll, angle smaller than this will invalidate scroll. In radians where pi = 32768, 0 means movement towards center of trackpad, 16384 means movement perpendicular to center.
 * @param wheel_clicks Number of scroll wheel clicks to report in a full rotation.
 * @param left_handed Whether scrolling should be flipped for left-handed use.
 */
void cirque_pinnacle_configure_circular_scroll(uint8_t outer_ring_pct, uint8_t trigger_px, uint16_t trigger_ang, uint8_t wheel_clicks, bool left_handed);
#endif

#ifdef POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
/* Implementation in pointing_device_drivers.c */

/* Enable/disable inertial cursor */
void cirque_pinnacle_enable_cursor_glide(bool enable);

/*
 * Configure inertial cursor.
 * @param trigger_px Movement required to trigger cursor glide, set this to non-zero if you have some amount of hover.
 */
void cirque_pinnacle_configure_cursor_glide(float trigger_px);
#endif

/* Process available gestures */
bool cirque_pinnacle_gestures(report_mouse_t* mouse_report, pinnacle_data_t touchData);
