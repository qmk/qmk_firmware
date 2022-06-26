/* Copyright 2017 Joshua Broekhuijsen <snipeye+qmk@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2021 Dasky (@daskygit)
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

#include "pointing_device.h"
#include "debug.h"
#include "wait.h"
#include "timer.h"
#include <stddef.h>

#define CONSTRAIN_HID(amt) ((amt) < INT8_MIN ? INT8_MIN : ((amt) > INT8_MAX ? INT8_MAX : (amt)))
#define CONSTRAIN_HID_XY(amt) ((amt) < XY_REPORT_MIN ? XY_REPORT_MIN : ((amt) > XY_REPORT_MAX ? XY_REPORT_MAX : (amt)))

// get_report functions should probably be moved to their respective drivers.
#if defined(POINTING_DEVICE_DRIVER_adns5050)
report_mouse_t adns5050_get_report(report_mouse_t mouse_report) {
    report_adns5050_t data = adns5050_read_burst();

    if (data.dx != 0 || data.dy != 0) {
#    ifdef CONSOLE_ENABLE
        if (debug_mouse) dprintf("Raw ] X: %d, Y: %d\n", data.dx, data.dy);
#    endif

        mouse_report.x = (mouse_xy_report_t)data.dx;
        mouse_report.y = (mouse_xy_report_t)data.dy;
    }

    return mouse_report;
}

// clang-format off
const pointing_device_driver_t pointing_device_driver = {
    .init         = adns5050_init,
    .get_report   = adns5050_get_report,
    .set_cpi      = adns5050_set_cpi,
    .get_cpi      = adns5050_get_cpi,
};
// clang-format on

#elif defined(POINTING_DEVICE_DRIVER_adns9800)

report_mouse_t adns9800_get_report_driver(report_mouse_t mouse_report) {
    report_adns9800_t sensor_report = adns9800_get_report();

    mouse_report.x = CONSTRAIN_HID_XY(sensor_report.x);
    mouse_report.y = CONSTRAIN_HID_XY(sensor_report.y);

    return mouse_report;
}

// clang-format off
const pointing_device_driver_t pointing_device_driver = {
    .init       = adns9800_init,
    .get_report = adns9800_get_report_driver,
    .set_cpi    = adns9800_set_cpi,
    .get_cpi    = adns9800_get_cpi
};
// clang-format on

#elif defined(POINTING_DEVICE_DRIVER_analog_joystick)
report_mouse_t analog_joystick_get_report(report_mouse_t mouse_report) {
    report_analog_joystick_t data = analog_joystick_read();

#    ifdef CONSOLE_ENABLE
    if (debug_mouse) dprintf("Raw ] X: %d, Y: %d\n", data.x, data.y);
#    endif

    mouse_report.x = data.x;
    mouse_report.y = data.y;

    mouse_report.buttons = pointing_device_handle_buttons(mouse_report.buttons, data.button, POINTING_DEVICE_BUTTON1);

    return mouse_report;
}

// clang-format off
const pointing_device_driver_t pointing_device_driver = {
    .init       = analog_joystick_init,
    .get_report = analog_joystick_get_report,
    .set_cpi    = NULL,
    .get_cpi    = NULL
};
// clang-format on

#elif defined(POINTING_DEVICE_DRIVER_cirque_pinnacle_i2c) || defined(POINTING_DEVICE_DRIVER_cirque_pinnacle_spi)
#    ifndef CIRQUE_PINNACLE_TAPPING_TERM
#        include "action.h"
#        include "action_tapping.h"
#        define CIRQUE_PINNACLE_TAPPING_TERM GET_TAPPING_TERM(KC_BTN1, &(keyrecord_t){})
#    endif
#    ifndef CIRQUE_PINNACLE_TOUCH_DEBOUNCE
#        define CIRQUE_PINNACLE_TOUCH_DEBOUNCE (CIRQUE_PINNACLE_TAPPING_TERM * 8)
#    endif

typedef struct {
    bool tap_enable;
    bool circular_scroll_enable;
    bool cursor_glide_enable;
} cirque_pinnacle_features_t;

static cirque_pinnacle_features_t features = {.tap_enable = true};

typedef struct {
    uint16_t timer;
    bool     touchDown;
} trackpad_tap_context_t;

static trackpad_tap_context_t tap;

static report_mouse_t trackpad_tap(report_mouse_t mouse_report, pinnacle_data_t touchData) {
    if (touchData.touchDown != tap.touchDown) {
        tap.touchDown = touchData.touchDown;
        if (!touchData.zValue) {
            if (timer_elapsed(tap.timer) < CIRQUE_PINNACLE_TAPPING_TERM && tap.timer != 0) {
                mouse_report.buttons = pointing_device_handle_buttons(mouse_report.buttons, true, POINTING_DEVICE_BUTTON1);
                pointing_device_set_report(mouse_report);
                pointing_device_send();
#    if TAP_CODE_DELAY > 0
                wait_ms(TAP_CODE_DELAY);
#    endif
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
#    if defined(POINTING_DEVICE_ROTATION_90)
                scroll.axis = y < 0;
#    elif defined(POINTING_DEVICE_ROTATION_180)
                scroll.axis = x > 0;
#    elif defined(POINTING_DEVICE_ROTATION_270)
                scroll.axis = y > 0;
#    else
                scroll.axis = x < 0;
#    endif
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

typedef struct {
    mouse_xy_report_t dx;
    mouse_xy_report_t dy;
    bool              valid;
} cursor_glide_t;

typedef struct {
    float             trigger_pct;
    float             coef;
    float             v0;
    int16_t           x;
    int16_t           y;
    uint16_t          z;
    uint16_t          timer;
    uint16_t          interval;
    uint16_t          counter;
    mouse_xy_report_t dx0;
    mouse_xy_report_t dy0;
} cursor_glide_context_t;

static cursor_glide_context_t glide = {.trigger_pct = 2};

static cursor_glide_t cursor_glide(void) {
    cursor_glide_t report;
    float          p;
    int16_t        x, y;

    glide.counter++;
    // calculate current position
    p            = glide.v0 * glide.counter - glide.coef * glide.counter * glide.counter / 2;
    x            = (int16_t)(p * glide.dx0 / glide.v0);
    y            = (int16_t)(p * glide.dy0 / glide.v0);
    report.dx    = (mouse_xy_report_t)(x - glide.x);
    report.dy    = (mouse_xy_report_t)(y - glide.y);
    report.valid = true;
    if (report.dx <= 1 && report.dx >= -1 && report.dy <= 1 && report.dy >= -1) {
        glide.dx0 = 0;
        glide.dy0 = 0;
    }
    glide.x     = x;
    glide.y     = y;
    glide.timer = timer_read();

    return report;
}

static cursor_glide_t cursor_glide_check(void) {
    cursor_glide_t invalid_report = {0, 0, false};
    if (glide.z || (glide.dx0 == 0 && glide.dy0 == 0) || timer_elapsed(glide.timer) < glide.interval) {
        return invalid_report;
    } else {
        return cursor_glide();
    }
}

static cursor_glide_t cursor_glide_start(void) {
    cursor_glide_t invalid_report = {0, 0, false};

    glide.coef     = 0.4; // good enough default
    glide.interval = 10;  // hardcode for 100sps
    glide.timer    = timer_read();
    glide.counter  = 0;
    glide.v0       = (glide.dx0 == 0 && glide.dy0 == 0) ? 0.0 : hypotf(glide.dx0, glide.dy0); // skip trigonometry if not needed
    glide.x        = 0;
    glide.y        = 0;
    glide.z        = 0;

    if (glide.v0 < glide.trigger_pct * cirque_pinnacle_get_scale() / 100) {
        // not enough velocity to be worth gliding, abort
        glide.dx0 = 0;
        glide.dy0 = 0;
        return invalid_report;
    }

    return cursor_glide();
}

static void cursor_glide_update(mouse_xy_report_t dx, mouse_xy_report_t dy, uint16_t z) {
    glide.dx0 = dx;
    glide.dy0 = dy;
    glide.z   = z;
}

// extern this for now
void cirque_pinnacle_enable_cursor_glide(bool enable) {
    features.cursor_glide_enable = enable;
}

void cirque_pinnacle_configure_cursor_glide(float trigger_pct) {
    glide.trigger_pct = trigger_pct;
}

report_mouse_t cirque_pinnacle_get_report(report_mouse_t mouse_report) {
    pinnacle_data_t          touchData = cirque_pinnacle_read_data();
    circular_scroll_t        scroll_report;
    cursor_glide_t           glide_report;
    mouse_xy_report_t        report_x = 0, report_y = 0;
    static mouse_xy_report_t x = 0, y = 0;

#    if !CIRQUE_PINNACLE_POSITION_MODE
#        error Cirque Pinnacle with relative mode not implemented yet.
#    endif

    if (features.cursor_glide_enable) {
        glide_report = cursor_glide_check();
    }

    if (!touchData.valid) {
        if (features.cursor_glide_enable && glide_report.valid) {
            report_x = glide_report.dx;
            report_y = glide_report.dy;
            goto mouse_report_update;
        }
        return mouse_report;
    }

#    if CONSOLE_ENABLE
    if (debug_mouse && touchData.touchDown) {
        dprintf("cirque_pinnacle touchData x=%4d y=%4d z=%2d\n", touchData.xValue, touchData.yValue, touchData.zValue);
    }
#    endif

    // Scale coordinates to arbitrary X, Y resolution
    cirque_pinnacle_scale_data(&touchData, cirque_pinnacle_get_scale(), cirque_pinnacle_get_scale());

    if (features.circular_scroll_enable) {
        scroll_report  = circular_scroll(touchData);
        mouse_report.v = scroll_report.v;
        mouse_report.h = scroll_report.h;
        if (scroll_report.suppress_touch) {
            goto mouse_report_update;
        }
    }
    if (x && y && touchData.xValue && touchData.yValue) {
        report_x = (mouse_xy_report_t)(touchData.xValue - x);
        report_y = (mouse_xy_report_t)(touchData.yValue - y);
    }
    x = touchData.xValue;
    y = touchData.yValue;

    if (features.cursor_glide_enable) {
        if (touchData.touchDown) {
            cursor_glide_update(report_x, report_y, touchData.zValue);
        } else if (!glide_report.valid) {
            glide_report = cursor_glide_start();
            if (glide_report.valid) {
                report_x = glide_report.dx;
                report_y = glide_report.dy;
            }
        }
    }

mouse_report_update:
    mouse_report.x = report_x;
    mouse_report.y = report_y;

    if (features.tap_enable) {
        mouse_report = trackpad_tap(mouse_report, touchData);
    }

    return mouse_report;
}

uint16_t cirque_pinnacle_get_cpi(void) {
    return (uint16_t)roundf((float)cirque_pinnacle_get_scale() * 25.4f / (float)CIRQUE_PINNACLE_DIAMETER_MM);
}
void cirque_pinnacle_set_cpi(uint16_t cpi) {
    cirque_pinnacle_set_scale(roundf((float)cpi * (float)CIRQUE_PINNACLE_DIAMETER_MM / 25.4f));
}

// clang-format off
const pointing_device_driver_t pointing_device_driver = {
    .init       = cirque_pinnacle_init,
    .get_report = cirque_pinnacle_get_report,
    .set_cpi    = cirque_pinnacle_set_cpi,
    .get_cpi    = cirque_pinnacle_get_cpi
};
// clang-format on

#elif defined(POINTING_DEVICE_DRIVER_pimoroni_trackball)

mouse_xy_report_t pimoroni_trackball_adapt_values(clamp_range_t* offset) {
    if (*offset > XY_REPORT_MAX) {
        *offset -= XY_REPORT_MAX;
        return (mouse_xy_report_t)XY_REPORT_MAX;
    } else if (*offset < XY_REPORT_MIN) {
        *offset += XY_REPORT_MAX;
        return (mouse_xy_report_t)XY_REPORT_MIN;
    } else {
        mouse_xy_report_t temp_return = *offset;
        *offset                       = 0;
        return temp_return;
    }
}

report_mouse_t pimoroni_trackball_get_report(report_mouse_t mouse_report) {
    static uint16_t      debounce      = 0;
    static uint8_t       error_count   = 0;
    pimoroni_data_t      pimoroni_data = {0};
    static clamp_range_t x_offset = 0, y_offset = 0;

    if (error_count < PIMORONI_TRACKBALL_ERROR_COUNT) {
        i2c_status_t status = read_pimoroni_trackball(&pimoroni_data);

        if (status == I2C_STATUS_SUCCESS) {
            error_count = 0;

            if (!(pimoroni_data.click & 128)) {
                mouse_report.buttons = pointing_device_handle_buttons(mouse_report.buttons, false, POINTING_DEVICE_BUTTON1);
                if (!debounce) {
                    x_offset += pimoroni_trackball_get_offsets(pimoroni_data.right, pimoroni_data.left, PIMORONI_TRACKBALL_SCALE);
                    y_offset += pimoroni_trackball_get_offsets(pimoroni_data.down, pimoroni_data.up, PIMORONI_TRACKBALL_SCALE);
                    mouse_report.x = pimoroni_trackball_adapt_values(&x_offset);
                    mouse_report.y = pimoroni_trackball_adapt_values(&y_offset);
                } else {
                    debounce--;
                }
            } else {
                mouse_report.buttons = pointing_device_handle_buttons(mouse_report.buttons, true, POINTING_DEVICE_BUTTON1);
                debounce             = PIMORONI_TRACKBALL_DEBOUNCE_CYCLES;
            }
        } else {
            error_count++;
        }
    }
    return mouse_report;
}

// clang-format off
const pointing_device_driver_t pointing_device_driver = {
    .init       = pimoroni_trackball_device_init,
    .get_report = pimoroni_trackball_get_report,
    .set_cpi    = pimoroni_trackball_set_cpi,
    .get_cpi    = pimoroni_trackball_get_cpi
};
// clang-format on

#elif defined(POINTING_DEVICE_DRIVER_pmw3360)
static void pmw3360_device_init(void) {
    pmw3360_init(0);
}

report_mouse_t pmw3360_get_report(report_mouse_t mouse_report) {
    report_pmw3360_t data        = pmw3360_read_burst(0);
    static uint16_t  MotionStart = 0; // Timer for accel, 0 is resting state

    if (data.isOnSurface && data.isMotion) {
        // Reset timer if stopped moving
        if (!data.isMotion) {
            if (MotionStart != 0) MotionStart = 0;
            return mouse_report;
        }

        // Set timer if new motion
        if ((MotionStart == 0) && data.isMotion) {
#    ifdef CONSOLE_ENABLE
            if (debug_mouse) dprintf("Starting motion.\n");
#    endif
            MotionStart = timer_read();
        }
        mouse_report.x = CONSTRAIN_HID_XY(data.dx);
        mouse_report.y = CONSTRAIN_HID_XY(data.dy);
    }

    return mouse_report;
}

// clang-format off
const pointing_device_driver_t pointing_device_driver = {
    .init       = pmw3360_device_init,
    .get_report = pmw3360_get_report,
    .set_cpi    = pmw3360_set_cpi,
    .get_cpi    = pmw3360_get_cpi
};
// clang-format on

#elif defined(POINTING_DEVICE_DRIVER_pmw3389)
static void pmw3389_device_init(void) {
    pmw3389_init();
}

report_mouse_t pmw3389_get_report(report_mouse_t mouse_report) {
    report_pmw3389_t data        = pmw3389_read_burst();
    static uint16_t  MotionStart = 0; // Timer for accel, 0 is resting state

    if (data.isOnSurface && data.isMotion) {
        // Reset timer if stopped moving
        if (!data.isMotion) {
            if (MotionStart != 0) MotionStart = 0;
            return mouse_report;
        }

        // Set timer if new motion
        if ((MotionStart == 0) && data.isMotion) {
#    ifdef CONSOLE_ENABLE
            if (debug_mouse) dprintf("Starting motion.\n");
#    endif
            MotionStart = timer_read();
        }
        mouse_report.x = CONSTRAIN_HID_XY(data.dx);
        mouse_report.y = CONSTRAIN_HID_XY(data.dy);
    }

    return mouse_report;
}

// clang-format off
const pointing_device_driver_t pointing_device_driver = {
    .init       = pmw3389_device_init,
    .get_report = pmw3389_get_report,
    .set_cpi    = pmw3389_set_cpi,
    .get_cpi    = pmw3389_get_cpi
};
// clang-format on

#else
__attribute__((weak)) void           pointing_device_driver_init(void) {}
__attribute__((weak)) report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
    return mouse_report;
}
__attribute__((weak)) uint16_t pointing_device_driver_get_cpi(void) {
    return 0;
}
__attribute__((weak)) void pointing_device_driver_set_cpi(uint16_t cpi) {}

// clang-format off
const pointing_device_driver_t pointing_device_driver = {
    .init       = pointing_device_driver_init,
    .get_report = pointing_device_driver_get_report,
    .get_cpi    = pointing_device_driver_get_cpi,
    .set_cpi    = pointing_device_driver_set_cpi
};
// clang-format on

#endif
