
#include "pointing_device_drivers.h"

// get_report functions should probably be moved to their respective drivers.

#if defined(POINTING_DEVICE_DRIVER_pimoroni_trackball)
#    include "pimoroni_trackball.h"

report_mouse_t pimorono_trackball_get_report(void) {
    static fast_timer_t throttle      = 0;
    static uint16_t     debounce      = 0;
    pimoroni_data_t     pimoroni_data = {0};
    report_mouse_t      report        = {0};

    if (error_count < PIMORONI_TRACKBALL_ERROR_COUNT && timer_elapsed_fast(throttle) >= PIMORONI_TRACKBALL_INTERVAL_MS) {
        i2c_status_t status = read_pimoroni_trackball(&pimoroni_data);

        if (status == I2C_STATUS_SUCCESS) {
            error_count = 0;

            if (!(pimoroni_data.click & 128)) {
                if (!debounce) {
                    x_offset += pimoroni_trackball_get_offsets(pimoroni_data.right, pimoroni_data.left, PIMORONI_TRACKBALL_MOUSE_SCALE);
                    y_offset += pimoroni_trackball_get_offsets(pimoroni_data.down, pimoroni_data.up, PIMORONI_TRACKBALL_MOUSE_SCALE);
                    pimoroni_trackball_adapt_values(&report.x, &x_offset);
                    pimoroni_trackball_adapt_values(&report.y, &y_offset);
                } else {
                    debounce--;
                }
            } else {
                report.buttons = 0b1;
                debounce       = PIMORONI_TRACKBALL_DEBOUNCE_CYCLES;
            }
        }
    } else {
        error_count++;
    }

    throttle = timer_read_fast();
    return report;
}

// clang-format off
const pointing_device_driver_t pointing_device_driver = {
    .init = pimironi_device_init;
    .get_report = pimorono_trackball_get_report;
};
// clang-format on
#elif defined(POINTING_DEVICE_DRIVER_pmw3360)
#    include "pmw3360.h"

report_mouse_t pmw3360_get_report(void) {
    report_pmw_t data = pmw_read_burst();
    static uint16_t MotionStart = 0;  // Timer for accel, 0 is resting state

    if (data.isOnSurface && data.isMotion) {
        // Reset timer if stopped moving
        if (!data.isMotion) {
            if (MotionStart != 0) MotionStart = 0;
            return;
        }

        // Set timer if new motion
        if ((MotionStart == 0) && data.isMotion) {
            if (debug_mouse) dprintf("Starting motion.\n");
            MotionStart = timer_read();
        }
        data.dx = constrain(data.dx, -127, 127);
        data.dy = constrain(data.dy, -127, 127);
    }

    return { .button = 0, .x = data.dx, .y = data.dy };
}

     // clang-format off
const pointing_device_driver_t pointing_device_driver = {
    .init = pmw3360_init;
    .get_report = pmw3360_get_report;
};
// clang-format on
#endif
