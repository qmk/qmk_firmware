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
#include <math.h>
#include "cirque_pinnacle_gestures.h"
#include "pointing_device.h"
#include "timer.h"

#ifdef POINTING_DEVICE_MOTION_PIN
#    error POINTING_DEVICE_MOTION_PIN not supported when using inertial cursor. Need repeated calls to get_report() to generate glide events.
#endif

static cirque_pinnacle_features_t features = {.tap_enable = true};
static trackpad_tap_context_t     tap;

static report_mouse_t trackpad_tap(report_mouse_t mouse_report, pinnacle_data_t touchData) {
    if (touchData.touchDown != tap.touchDown) {
        tap.touchDown = touchData.touchDown;
        if (!touchData.zValue) {
            if (timer_elapsed(tap.timer) < CIRQUE_PINNACLE_TAPPING_TERM && tap.timer != 0) {
                mouse_report.buttons = pointing_device_handle_buttons(mouse_report.buttons, true, POINTING_DEVICE_BUTTON1);
                pointing_device_set_report(mouse_report);
                pointing_device_send();
#if TAP_CODE_DELAY > 0
                wait_ms(TAP_CODE_DELAY);
#endif
                mouse_report.buttons = pointing_device_handle_buttons(mouse_report.buttons, false, POINTING_DEVICE_BUTTON1);
                pointing_device_set_report(mouse_report);
                pointing_device_send();
            }
        }
        tap.timer = timer_read();
    }
    if (timer_elapsed(tap.timer) > (CIRQUE_PINNACLE_TOUCH_DEBOUNCE)) {
        tap.timer = 0;
    }

    return mouse_report;
}

// extern this function for now
void cirque_pinnacle_enable_tap(bool enable) {
    features.tap_enable = enable;
}

static circular_scroll_context_t scroll = {.outer_ring_pct = 33, .movement_pct = 6, .movement_ratio = 1.2, .wheel_clicks = 9};

static circular_scroll_t circular_scroll(pinnacle_data_t touchData) {
    circular_scroll_t report = {0, 0, false};
    int16_t           x, y;
    uint16_t          center = cirque_pinnacle_get_scale() / 2;
    int8_t            wheel_clicks;
    float             mag, ang, scalar_projection, scalar_rejection, parallel_movement, perpendicular_movement;
    int32_t           dot, det;

    if (touchData.zValue) {
        // place origin at center of trackpad
        x = (int16_t)(touchData.xValue - center);
        y = (int16_t)(touchData.yValue - center);

        // check if first touch
        if (!scroll.z) {
            report.suppress_touch = false;
            // check if touch falls within outer ring
            mag = hypotf(x, y);
            if (mag / center >= (100.0 - scroll.outer_ring_pct) / 100.0) {
                scroll.state = SCROLL_DETECTING;
                scroll.x     = x;
                scroll.y     = y;
                scroll.mag   = mag;
                // decide scroll axis:
                //   vertical if started from righ half
                //   horizontal if started from left half
                // reverse for left hand? TODO?
#if defined(POINTING_DEVICE_ROTATION_90)
                scroll.axis = y < 0;
#elif defined(POINTING_DEVICE_ROTATION_180)
                scroll.axis = x > 0;
#elif defined(POINTING_DEVICE_ROTATION_270)
                scroll.axis = y > 0;
#else
                scroll.axis = x < 0;
#endif
            }
        } else if (scroll.state == SCROLL_DETECTING) {
            report.suppress_touch = true;
            // already detecting scroll, check movement from touchdown location
            mag = hypotf(x - scroll.x, y - scroll.y);
            if (mag >= scroll.movement_pct / 100.0 * center) {
                // check ratio of movement towards center vs. along perimeter
                // this distinguishes circular scroll from swipes that start from edge of trackpad
                dot                    = (int32_t)scroll.x * (int32_t)x + (int32_t)scroll.y * (int32_t)y;
                det                    = (int32_t)scroll.x * (int32_t)y - (int32_t)scroll.y * (int32_t)x;
                scalar_projection      = dot / scroll.mag;
                scalar_rejection       = det / scroll.mag;
                parallel_movement      = fabs(scroll.mag - fabs(scalar_projection));
                perpendicular_movement = fabs(scalar_rejection);
                if (parallel_movement * scroll.movement_ratio > perpendicular_movement) {
                    // not a scroll, release coordinates
                    report.suppress_touch = false;
                    scroll.state          = NOT_SCROLL;
                } else {
                    // scroll detected
                    scroll.state = SCROLL_VALID;
                }
            }
        }
        if (scroll.state == SCROLL_VALID) {
            report.suppress_touch = true;
            dot                   = (int32_t)scroll.x * (int32_t)x + (int32_t)scroll.y * (int32_t)y;
            det                   = (int32_t)scroll.x * (int32_t)y - (int32_t)scroll.y * (int32_t)x;
            ang                   = atan2f(det, dot);
            wheel_clicks          = roundf(ang * (float)scroll.wheel_clicks / M_PI);
            if (wheel_clicks >= 1 || wheel_clicks <= -1) {
                if (scroll.axis == 0) {
                    report.v = -wheel_clicks;
                } else {
                    report.h = wheel_clicks;
                }
                scroll.x = x;
                scroll.y = y;
            }
        }
    }

    scroll.z = touchData.zValue;
    if (!scroll.z) scroll.state = SCROLL_UNINITIALIZED;

    return report;
}

// extern this for now
void cirque_pinnacle_enable_circular_scroll(bool enable) {
    features.circular_scroll_enable = enable;
}

// To set a trackpad exclusively as scroll wheel: outer_ring_pct = 100, movement_pct = 0, movement_ratio = 0
void cirque_pinnacle_configure_circular_scroll(float outer_ring_pct, float movement_pct, float movement_ratio, uint8_t wheel_clicks) {
    scroll.outer_ring_pct = outer_ring_pct;
    scroll.movement_pct   = movement_pct;
    scroll.movement_ratio = movement_ratio;
    scroll.wheel_clicks   = wheel_clicks;
}

bool cirque_pinnacle_gestures(report_mouse_t* mouse_report, pinnacle_data_t touchData) {
    bool              suppress_mouse_update = false;
    circular_scroll_t scroll_report;

    if (features.circular_scroll_enable) {
        scroll_report         = circular_scroll(touchData);
        mouse_report->v       = scroll_report.v;
        mouse_report->h       = scroll_report.h;
        suppress_mouse_update = scroll_report.suppress_touch;
    }
    if (features.tap_enable) {
        *mouse_report = trackpad_tap(*mouse_report, touchData);
    }

    return suppress_mouse_update;
}
