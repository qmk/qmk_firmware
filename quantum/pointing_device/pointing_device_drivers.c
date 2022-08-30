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
#    ifdef POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
static bool cursor_glide_enable = true;

static cursor_glide_context_t glide = {.config = {
                                           .coef       = 102, /* Good default friction coef */
                                           .interval   = 10,  /* 100sps */
                                           .trigger_px = 10,  /* Default threshold in case of hover, set to 0 if you'd like */
                                       }};

void cirque_pinnacle_enable_cursor_glide(bool enable) {
    cursor_glide_enable = enable;
}

void cirque_pinnacle_configure_cursor_glide(float trigger_px) {
    glide.config.trigger_px = trigger_px;
}
#    endif

#    if CIRQUE_PINNACLE_POSITION_MODE

#        ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
static bool is_touch_down;

bool auto_mouse_activation(report_mouse_t mouse_report) {
    return is_touch_down || mouse_report.x != 0 || mouse_report.y != 0 || mouse_report.h != 0 || mouse_report.v != 0 || mouse_report.buttons;
}
#        endif

report_mouse_t cirque_pinnacle_get_report(report_mouse_t mouse_report) {
    pinnacle_data_t   touchData = cirque_pinnacle_read_data();
    mouse_xy_report_t report_x = 0, report_y = 0;
    static uint16_t   x = 0, y = 0;
#        ifdef POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
    cursor_glide_t    glide_report = {0};

    if (cursor_glide_enable) {
        glide_report = cursor_glide_check(&glide);
    }
#        endif

    if (!touchData.valid) {
#        ifdef POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
        if (cursor_glide_enable && glide_report.valid) {
            report_x = glide_report.dx;
            report_y = glide_report.dy;
            goto mouse_report_update;
        }
#        endif
        return mouse_report;
    }

#        if CONSOLE_ENABLE
    if (debug_mouse && touchData.touchDown) {
        dprintf("cirque_pinnacle touchData x=%4d y=%4d z=%2d\n", touchData.xValue, touchData.yValue, touchData.zValue);
    }
#        endif

#        ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    is_touch_down = touchData.touchDown;
#        endif

    // Scale coordinates to arbitrary X, Y resolution
    cirque_pinnacle_scale_data(&touchData, cirque_pinnacle_get_scale(), cirque_pinnacle_get_scale());

    if (!cirque_pinnacle_gestures(&mouse_report, touchData)) {
        if (x && y && touchData.xValue && touchData.yValue) {
            report_x = CONSTRAIN_HID_XY((int16_t)(touchData.xValue - x));
            report_y = CONSTRAIN_HID_XY((int16_t)(touchData.yValue - y));
        }
        x = touchData.xValue;
        y = touchData.yValue;

#        ifdef POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
        if (cursor_glide_enable) {
            if (touchData.touchDown) {
                cursor_glide_update(&glide, report_x, report_y, touchData.zValue);
            } else if (!glide_report.valid) {
                glide_report = cursor_glide_start(&glide);
                if (glide_report.valid) {
                    report_x = glide_report.dx;
                    report_y = glide_report.dy;
                }
            }
        }
#        endif
    }

#        ifdef POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
mouse_report_update:
#        endif
    mouse_report.x = report_x;
    mouse_report.y = report_y;

    return mouse_report;
}

uint16_t cirque_pinnacle_get_cpi(void) {
    return CIRQUE_PINNACLE_PX_TO_INCH(cirque_pinnacle_get_scale());
}
void cirque_pinnacle_set_cpi(uint16_t cpi) {
    cirque_pinnacle_set_scale(CIRQUE_PINNACLE_INCH_TO_PX(cpi));
}

// clang-format off
const pointing_device_driver_t pointing_device_driver = {
    .init       = cirque_pinnacle_init,
    .get_report = cirque_pinnacle_get_report,
    .set_cpi    = cirque_pinnacle_set_cpi,
    .get_cpi    = cirque_pinnacle_get_cpi
};
// clang-format on
#    else
report_mouse_t cirque_pinnacle_get_report(report_mouse_t mouse_report) {
    pinnacle_data_t touchData = cirque_pinnacle_read_data();

    // Scale coordinates to arbitrary X, Y resolution
    cirque_pinnacle_scale_data(&touchData, cirque_pinnacle_get_scale(), cirque_pinnacle_get_scale());

    if (touchData.valid) {
        mouse_report.buttons = touchData.buttons;
        mouse_report.x       = CONSTRAIN_HID_XY(touchData.xDelta);
        mouse_report.y       = CONSTRAIN_HID_XY(touchData.yDelta);
        mouse_report.v       = touchData.wheelCount;
    }
    return mouse_report;
}

// clang-format off
const pointing_device_driver_t pointing_device_driver = {
    .init       = cirque_pinnacle_init,
    .get_report = cirque_pinnacle_get_report,
    .set_cpi    = cirque_pinnacle_set_scale,
    .get_cpi    = cirque_pinnacle_get_scale
};
// clang-format on
#    endif

#elif defined(POINTING_DEVICE_DRIVER_paw3204)

report_mouse_t paw3204_get_report(report_mouse_t mouse_report) {
    report_paw3204_t data = paw3204_read();
    if (data.isMotion) {
#    ifdef CONSOLE_ENABLE
        dprintf("Raw ] X: %d, Y: %d\n", data.x, data.y);
#    endif

        mouse_report.x = data.x;
        mouse_report.y = data.y;
    }

    return mouse_report;
}
const pointing_device_driver_t pointing_device_driver = {
    .init       = paw3204_init,
    .get_report = paw3204_get_report,
    .set_cpi    = paw3204_set_cpi,
    .get_cpi    = paw3204_get_cpi,
};
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

#elif defined(POINTING_DEVICE_DRIVER_pmw3360) || defined(POINTING_DEVICE_DRIVER_pmw3389)
static void pmw33xx_init_wrapper(void) {
    pmw33xx_init(0);
}

static void pmw33xx_set_cpi_wrapper(uint16_t cpi) {
    pmw33xx_set_cpi(0, cpi);
}

static uint16_t pmw33xx_get_cpi_wrapper(void) {
    return pmw33xx_get_cpi(0);
}

report_mouse_t pmw33xx_get_report(report_mouse_t mouse_report) {
    pmw33xx_report_t report    = pmw33xx_read_burst(0);
    static bool      in_motion = false;

    if (report.motion.b.is_lifted) {
        return mouse_report;
    }

    if (!report.motion.b.is_motion) {
        in_motion = false;
        return mouse_report;
    }

    if (!in_motion) {
        in_motion = true;
        dprintf("PWM3360 (0): starting motion\n");
    }

    mouse_report.x = CONSTRAIN_HID_XY(report.delta_x);
    mouse_report.y = CONSTRAIN_HID_XY(report.delta_y);
    return mouse_report;
}

// clang-format off
const pointing_device_driver_t pointing_device_driver = {
    .init       = pmw33xx_init_wrapper,
    .get_report = pmw33xx_get_report,
    .set_cpi    = pmw33xx_set_cpi_wrapper,
    .get_cpi    = pmw33xx_get_cpi_wrapper
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
