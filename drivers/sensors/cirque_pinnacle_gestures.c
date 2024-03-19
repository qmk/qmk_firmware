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
#include <stdlib.h>
#include <lib/lib8tion/lib8tion.h>
#include "cirque_pinnacle_gestures.h"
#include "pointing_device.h"
#include "timer.h"
#include "wait.h"
#if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED)
#    include "keyboard.h"
#endif

#if defined(CIRQUE_PINNACLE_DPAD_MODE_ENABLE)
#    include "keyboard.h"
#    include "action.h"
#endif

#if (defined(CIRQUE_PINNACLE_TAP_ENABLE) || defined(CIRQUE_PINNACLE_CIRCULAR_SCROLL_ENABLE) || defined(CIRQUE_PINNACLE_DPAD_MODE_ENABLE)) && CIRQUE_PINNACLE_POSITION_MODE
static cirque_pinnacle_features_t features = {
    .circular_scroll_enable = true,
    .dpad_mode_enable       = true,
    .tap_enable             = true,
};
#endif

#if defined(CIRQUE_PINNACLE_TAP_ENABLE) && CIRQUE_PINNACLE_POSITION_MODE
static trackpad_tap_context_t tap;

static report_mouse_t trackpad_tap(report_mouse_t mouse_report, pinnacle_data_t touchData) {
    if (touchData.touchDown != tap.touchDown) {
        tap.touchDown = touchData.touchDown;
        if (!touchData.zValue) {
            if (timer_elapsed(tap.timer) < CIRQUE_PINNACLE_TAPPING_TERM && tap.timer != 0) {
                mouse_report.buttons = pointing_device_handle_buttons(mouse_report.buttons, true, POINTING_DEVICE_BUTTON1);
            }
        }
        tap.timer = timer_read();
    }
    if (timer_elapsed(tap.timer) > (CIRQUE_PINNACLE_TOUCH_DEBOUNCE)) {
        tap.timer = 0;
    }

    return mouse_report;
}

void cirque_pinnacle_enable_tap(bool enable) {
    features.tap_enable = enable;
}
#endif

#ifdef CIRQUE_PINNACLE_CIRCULAR_SCROLL_ENABLE
#    if !CIRQUE_PINNACLE_POSITION_MODE
#        error "Circular scroll is not supported in relative mode"
#    endif
/* To set a trackpad exclusively as scroll wheel: outer_ring_pct = 100, trigger_px = 0, trigger_ang = 0 */
static circular_scroll_context_t scroll = {.config = {.outer_ring_pct = 33,
                                                      .trigger_px     = 16,
                                                      .trigger_ang    = 9102, /* 50 degrees */
                                                      .wheel_clicks   = 18}};
#endif

#if defined(CIRQUE_PINNACLE_CIRCULAR_SCROLL_ENABLE) || defined(CIRQUE_PINNACLE_DPAD_MODE_ENABLE)
#    define ATAN2_16_RANGE 0x8000
static inline uint16_t atan2_16(int32_t dy, int32_t dx) {
    if (dy == 0) {
        if (dx >= 0) {
            return 0;
        } else {
            return ATAN2_16_RANGE;
        }
    }

    int32_t abs_y = dy > 0 ? dy : -dy;
    int16_t a;

    if (dx >= 0) {
        a = 8192 - (8192 * (dx - abs_y) / (dx + abs_y));
    } else {
        a = 24576 - (8192 * (dx + abs_y) / (abs_y - dx));
    }

    if (dy < 0) {
        return -a; // negate if in quad III or IV
    }
    return a;
}
#endif

#ifdef CIRQUE_PINNACLE_CIRCULAR_SCROLL_ENABLE
static circular_scroll_t circular_scroll(pinnacle_data_t touchData) {
    circular_scroll_t report = {0, 0, false};
    int8_t            x, y, wheel_clicks;
    uint8_t           center = INT8_MAX, mag;
    int16_t           ang, dot, det, opposite_side, adjacent_side;
    uint16_t          scale = cirque_pinnacle_get_scale();

    if (touchData.zValue) {
        /*
         * Place origin at center of trackpad, treat coordinates as vectors.
         * Scale to +/-INT8_MAX; angles are independent of resolution.
         */
        if (scale) {
            /* Rotate coordinates into a consistent orientation */
            report_mouse_t rot = {.x = (int8_t)((int32_t)touchData.xValue * INT8_MAX * 2 / scale - center), .y = (int8_t)((int32_t)touchData.yValue * INT8_MAX * 2 / scale - center)};
#    if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED)
            if (!is_keyboard_left()) {
                rot = pointing_device_adjust_by_defines_right(rot);
            } else
#    endif
            {
                rot = pointing_device_adjust_by_defines(rot);
            }
            x = rot.x;
            y = rot.y;
        } else {
            x = 0;
            y = 0;
        }

        /* Check if first touch */
        if (!scroll.z) {
            report.suppress_touch = false;
            /* Check if touch falls within outer ring */
            mag = sqrt16(x * x + y * y);
            if (mag * 100 / center >= 100 - scroll.config.outer_ring_pct) {
                scroll.state = SCROLL_DETECTING;
                scroll.x     = x;
                scroll.y     = y;
                scroll.mag   = mag;
                /*
                 * Decide scroll axis:
                 *   Vertical if started from righ half
                 *   Horizontal if started from left half
                 * Flipped for left-handed
                 */
                scroll.axis = x < 0;
            }
        } else if (scroll.state == SCROLL_DETECTING) {
            report.suppress_touch = true;
            /* Already detecting scroll, check movement from touchdown location */
            mag = sqrt16((x - scroll.x) * (x - scroll.x) + (y - scroll.y) * (y - scroll.y));
            if (mag >= scroll.config.trigger_px) {
                /*
                 * Find angle of movement.
                 * 0 degrees here means movement towards center of circle
                 */
                dot           = scroll.x * x + scroll.y * y;
                det           = scroll.x * y - scroll.y * x;
                opposite_side = abs(det);                                /* Based on scalar rejection */
                adjacent_side = abs(scroll.mag * scroll.mag - abs(dot)); /* Based on scalar projection */
                ang           = (int16_t)atan2_16(opposite_side, adjacent_side);
                if (ang < scroll.config.trigger_ang) {
                    /* Not a scroll, release coordinates */
                    report.suppress_touch = false;
                    scroll.state          = NOT_SCROLL;
                } else {
                    /* Scroll detected */
                    scroll.state = SCROLL_VALID;
                }
            }
        }
        if (scroll.state == SCROLL_VALID) {
            report.suppress_touch = true;
            dot                   = scroll.x * x + scroll.y * y;
            det                   = scroll.x * y - scroll.y * x;
            ang                   = (int16_t)atan2_16(det, dot);
            wheel_clicks          = ((int32_t)ang * scroll.config.wheel_clicks) / 65536;
            if (wheel_clicks >= 1 || wheel_clicks <= -1) {
                if (scroll.config.left_handed) {
                    if (scroll.axis == 0) {
                        report.h = -wheel_clicks;
                    } else {
                        report.v = wheel_clicks;
                    }
                } else {
                    if (scroll.axis == 0) {
                        report.v = -wheel_clicks;
                    } else {
                        report.h = wheel_clicks;
                    }
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

void cirque_pinnacle_enable_circular_scroll(bool enable) {
    features.circular_scroll_enable = enable;
}

void cirque_pinnacle_configure_circular_scroll(uint8_t outer_ring_pct, uint8_t trigger_px, uint16_t trigger_ang, uint8_t wheel_clicks, bool left_handed) {
    scroll.config.outer_ring_pct = outer_ring_pct;
    scroll.config.trigger_px     = trigger_px;
    scroll.config.trigger_ang    = trigger_ang;
    scroll.config.wheel_clicks   = wheel_clicks;
    scroll.config.left_handed    = left_handed;
}
#endif

#if defined(CIRQUE_PINNACLE_DPAD_MODE_ENABLE)
static dpad_state_t dpad = {
    .keystate = 0,
    .discrete = true,
};
void dpad_emit_key(dpad_key_t key, bool press) {
#    if !defined(CIRQUE_PINNACLE_DPAD_KEYMAP_ROW)
#        error "dpad mode has now keymap row assigned to it"
#    endif
    if (press) {
        if (!(dpad.keystate & (1 << key))) {
            switch (key) {
                case DPAD_UP:
                    action_exec(MAKE_KEYEVENT(CIRQUE_PINNACLE_DPAD_KEYMAP_ROW, 0, true));
                    break;
                case DPAD_LEFT:
                    action_exec(MAKE_KEYEVENT(CIRQUE_PINNACLE_DPAD_KEYMAP_ROW, 1, true));
                    break;
                case DPAD_RIGHT:
                    action_exec(MAKE_KEYEVENT(CIRQUE_PINNACLE_DPAD_KEYMAP_ROW, 2, true));
                    break;
                case DPAD_DOWN:
                    action_exec(MAKE_KEYEVENT(CIRQUE_PINNACLE_DPAD_KEYMAP_ROW, 3, true));
                    break;
            }
            dpad.keystate |= (1 << key);
        }
    } else {
        if (dpad.keystate & (1 << key)) {
            switch (key) {
                case DPAD_UP:
                    action_exec(MAKE_KEYEVENT(CIRQUE_PINNACLE_DPAD_KEYMAP_ROW, 0, false));
                    break;
                case DPAD_LEFT:
                    action_exec(MAKE_KEYEVENT(CIRQUE_PINNACLE_DPAD_KEYMAP_ROW, 1, false));
                    break;
                case DPAD_RIGHT:
                    action_exec(MAKE_KEYEVENT(CIRQUE_PINNACLE_DPAD_KEYMAP_ROW, 2, false));
                    break;
                case DPAD_DOWN:
                    action_exec(MAKE_KEYEVENT(CIRQUE_PINNACLE_DPAD_KEYMAP_ROW, 3, false));
                    break;
            }
            dpad.keystate &= ~(1 << key);
        }
    }
}

bool dpad_mode(pinnacle_data_t touchData) {
    uint8_t  center = INT8_MAX;
    uint16_t scale  = cirque_pinnacle_get_scale();
    /* rotation center == center of the touchpad */
    report_mouse_t rot = {.x = (int8_t)((int32_t)touchData.xValue * INT8_MAX * 2 / scale - center), .y = (int8_t)((int32_t)touchData.yValue * INT8_MAX * 2 / scale - center)};
    rot                = pointing_device_adjust_by_defines(rot);

    uint8_t r = sqrt16(rot.x * rot.x + rot.y * rot.y);
    // TODO: use radius for deadzone in the center?

    int16_t theta = atan2_16(rot.x, rot.y);
    if (touchData.touchDown) {
        /* discrete mode:
         *   only one cardinal key at a time
         *
         * the four quadrants 'theta' goes through, and how they are divided into dpad keys:
         * R = ATAN2_16_RANGE
         *
         *            |
         *          -----
         *[-R/2,-R]/  Up \  [R/2,R]
         *        .       .
         *       / ..   .. \
         *       |   . .   |
         *    ---Left . Right-->X
         *       |   . .   |
         *       \ ..   .. /
         *        .       .
         *[-0,-R/2]\ Down/  [0,R/2]
         *          -----
         *            |
         *            v Y
         */
        if (dpad.discrete) {
            if (-1.0 / 4 * ATAN2_16_RANGE < theta && theta < 1.0 / 4 * ATAN2_16_RANGE) {
                pd_dprintf("%s D [%4d,%4d] t=%4d r=%4d\n", __FUNCTION__, rot.x, rot.y, theta, r);
                // TODO: debounce? repeat/autooff?
                dpad_emit_key(DPAD_DOWN, true);
                // release adjacent keys, if held
                dpad_emit_key(DPAD_LEFT, false);
                dpad_emit_key(DPAD_RIGHT, false);
                dpad_emit_key(DPAD_UP, false);
            } else if (1.0 / 4 * ATAN2_16_RANGE < theta && theta < 3.0 / 4 * ATAN2_16_RANGE) {
                pd_dprintf("%s R [%4d,%4d] t=%4d r=%4d\n", __FUNCTION__, rot.x, rot.y, theta, r);
                dpad_emit_key(DPAD_DOWN, false);
                dpad_emit_key(DPAD_LEFT, false);
                dpad_emit_key(DPAD_RIGHT, true);
                dpad_emit_key(DPAD_UP, false);
            } else if (-3.0 / 4 * ATAN2_16_RANGE < theta && theta < -1.0 / 4 * ATAN2_16_RANGE) {
                pd_dprintf("%s L [%4d,%4d] t=%4d r=%4d\n", __FUNCTION__, rot.x, rot.y, theta, r);
                dpad_emit_key(DPAD_DOWN, false);
                dpad_emit_key(DPAD_LEFT, true);
                dpad_emit_key(DPAD_RIGHT, false);
                dpad_emit_key(DPAD_UP, false);
            } else if (3.0 / 4 * ATAN2_16_RANGE < theta || theta < -3.0 / 4 * ATAN2_16_RANGE) {
                pd_dprintf("%s U [%4d,%4d] t=%4d r=%4d\n", __FUNCTION__, rot.x, rot.y, theta, r);
                dpad_emit_key(DPAD_DOWN, false);
                dpad_emit_key(DPAD_LEFT, false);
                dpad_emit_key(DPAD_RIGHT, false);
                dpad_emit_key(DPAD_UP, true);
            }
        } else {
            /* blend mode: split circle into octants,
             *   with four cardinal directions = one key,
             *   and four diagonals = two keys
             *
             *             |
             *           +---+
             *          /\ U /\
             *         /UL| |UR\
             *        --  \ /  --
             *        | \_ | _/ |
             *      --|L _-+-_ R|-> X
             *        | /  |  \ |
             *        --  / \  --
             *         \DL| |DR/
             *          \/ D \/
             *           +---+
             *             |
             *             v Y
             */
            if (-1.0 / 8 * ATAN2_16_RANGE < theta && theta < 1.0 / 8 * ATAN2_16_RANGE) {
                pd_dprintf("%s D [%4d,%4d] t=%4d r=%4d\n", __FUNCTION__, rot.x, rot.y, theta, r);
                dpad_emit_key(DPAD_DOWN, true);
                dpad_emit_key(DPAD_LEFT, false);
                dpad_emit_key(DPAD_RIGHT, false);
                dpad_emit_key(DPAD_UP, false);
            } else if (1.0 / 8 * ATAN2_16_RANGE < theta && theta < 3.0 / 8 * ATAN2_16_RANGE) {
                pd_dprintf("%s DR [%4d,%4d] t=%4d r=%4d\n", __FUNCTION__, rot.x, rot.y, theta, r);
                dpad_emit_key(DPAD_DOWN, true);
                dpad_emit_key(DPAD_LEFT, false);
                dpad_emit_key(DPAD_RIGHT, true);
                dpad_emit_key(DPAD_UP, false);
            } else if (3.0 / 8 * ATAN2_16_RANGE < theta && theta < 5.0 / 8 * ATAN2_16_RANGE) {
                pd_dprintf("%s R [%4d,%4d] t=%4d r=%4d\n", __FUNCTION__, rot.x, rot.y, theta, r);
                dpad_emit_key(DPAD_DOWN, false);
                dpad_emit_key(DPAD_LEFT, false);
                dpad_emit_key(DPAD_RIGHT, true);
                dpad_emit_key(DPAD_UP, false);
            } else if (5.0 / 8 * ATAN2_16_RANGE < theta && theta < 7.0 / 8 * ATAN2_16_RANGE) {
                pd_dprintf("%s UR [%4d,%4d] t=%4d r=%4d\n", __FUNCTION__, rot.x, rot.y, theta, r);
                dpad_emit_key(DPAD_DOWN, false);
                dpad_emit_key(DPAD_LEFT, false);
                dpad_emit_key(DPAD_RIGHT, true);
                dpad_emit_key(DPAD_UP, true);
            } else if (-3.0 / 8 * ATAN2_16_RANGE < theta && theta < -1.0 / 8 * ATAN2_16_RANGE) {
                pd_dprintf("%s DL [%4d,%4d] t=%4d r=%4d\n", __FUNCTION__, rot.x, rot.y, theta, r);
                dpad_emit_key(DPAD_DOWN, true);
                dpad_emit_key(DPAD_LEFT, true);
                dpad_emit_key(DPAD_RIGHT, false);
                dpad_emit_key(DPAD_UP, false);
            } else if (-5.0 / 8 * ATAN2_16_RANGE < theta && theta < -3.0 / 8 * ATAN2_16_RANGE) {
                pd_dprintf("%s L [%4d,%4d] t=%4d r=%4d\n", __FUNCTION__, rot.x, rot.y, theta, r);
                dpad_emit_key(DPAD_DOWN, false);
                dpad_emit_key(DPAD_LEFT, true);
                dpad_emit_key(DPAD_RIGHT, false);
                dpad_emit_key(DPAD_UP, false);
            } else if (-7.0 / 8 * ATAN2_16_RANGE < theta && theta < -5.0 / 8 * ATAN2_16_RANGE) {
                pd_dprintf("%s UL [%4d,%4d] t=%4d r=%4d\n", __FUNCTION__, rot.x, rot.y, theta, r);
                dpad_emit_key(DPAD_DOWN, false);
                dpad_emit_key(DPAD_LEFT, true);
                dpad_emit_key(DPAD_RIGHT, false);
                dpad_emit_key(DPAD_UP, true);
            } else if (7.0 / 8 * ATAN2_16_RANGE < theta || theta < -7.0 / 8 * ATAN2_16_RANGE) {
                pd_dprintf("%s U [%4d,%4d] t=%4d r=%4d\n", __FUNCTION__, rot.x, rot.y, theta, r);
                dpad_emit_key(DPAD_DOWN, false);
                dpad_emit_key(DPAD_LEFT, false);
                dpad_emit_key(DPAD_RIGHT, false);
                dpad_emit_key(DPAD_UP, true);
            }
        }
    } else { // touchDown = false
        dpad_emit_key(DPAD_DOWN, false);
        dpad_emit_key(DPAD_LEFT, false);
        dpad_emit_key(DPAD_RIGHT, false);
        dpad_emit_key(DPAD_UP, false);
        dpad.keystate = 0;
    }
    return true;
}

void cirque_pinnacle_enable_dpad_mode(bool enable) {
    features.dpad_mode_enable = enable;
}

void cirque_pinnacle_configure_dpad_mode(bool discrete) {
    dpad.discrete = discrete;
}
#endif // CIRQUE_PINNACLE_DPAD_MODE_ENABLE

bool cirque_pinnacle_gestures(report_mouse_t* mouse_report, pinnacle_data_t touchData) {
    bool suppress_mouse_update = false;

#if defined(CIRQUE_PINNACLE_DPAD_MODE_ENABLE)
#    if !CIRQUE_PINNACLE_POSITION_MODE
#        error "dpad mode is not supported in relative mode"
#    endif
    if (features.dpad_mode_enable && dpad_mode(touchData)) {
        return true;
    }
#endif

#ifdef CIRQUE_PINNACLE_CIRCULAR_SCROLL_ENABLE
#    if !CIRQUE_PINNACLE_POSITION_MODE
#        error "Circular scroll is not supported in relative mode"
#    endif
    circular_scroll_t scroll_report;
    if (features.circular_scroll_enable) {
        scroll_report         = circular_scroll(touchData);
        mouse_report->v       = scroll_report.v;
        mouse_report->h       = scroll_report.h;
        suppress_mouse_update = scroll_report.suppress_touch;
    }
#endif

#if defined(CIRQUE_PINNACLE_TAP_ENABLE) && CIRQUE_PINNACLE_POSITION_MODE
    if (features.tap_enable) {
        *mouse_report = trackpad_tap(*mouse_report, touchData);
    }
#endif

    return suppress_mouse_update;
}
