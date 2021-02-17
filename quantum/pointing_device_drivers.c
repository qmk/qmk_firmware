
#include "pointing_device.h"

// get_report functions should probably be moved to their respective drivers.

#if defined(POINTING_DEVICE_DRIVER_pmw3360)
#include "pmw3360.h"

short_mouse_t get_report(void) {
    report_pmw_t data = pmw_read_burst();
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

    return { .button = 0, .x = data.dx, .y = data.dy };
}

const pointing_device_driver_t pointing_device_driver = {
    .init = pmw_spi_init;
    .get_report = get_report;
};

#elif defined POINTING_DEVICE_DRIVER_pimoroni_trackball
#include "i2c_master.h"

void init(void) {
    i2c_init();
    trackball_set_rgbw(0x00, 0x00, 0x00, 0x00);
}

int16_t mouse_offset(uint8_t positive, uint8_t negative, int16_t scale) {
    int16_t offset    = (int16_t)positive - (int16_t)negative;
    int16_t magnitude = (int16_t)(scale * offset * offset * precisionSpeed);
    return offset < 0 ? -magnitude : magnitude;
}

void update_member(int8_t* member, int16_t* offset) {
    if (*offset > 127) {
        *member = 127;
        *offset -= 127;
    } else if (*offset < -127) {
        *member = -127;
        *offset += 127;
    } else {
        *member = *offset;
        *offset = 0;
    }
}

short_mouse_t get_report() {
    static bool     debounce;
    static uint16_t debounce_timer;
    short_mouse_t   report;
    uint8_t         state[5] = {};
    if (i2c_readReg(TRACKBALL_WRITE, 0x04, state, 5, I2C_TIMEOUT) == I2C_STATUS_SUCCESS) {
        if (!state[4] && !debounce) {
                h_offset -= mouse_offset(state[2], state[3], 1);
                v_offset -= mouse_offset(state[1], state[0], 1);
            } else {
                x_offset += mouse_offset(state[2], state[3], 5);
                y_offset += mouse_offset(state[1], state[0], 5);
            }
        } else {
            if (state[4]) {
                debounce       = true;
                debounce_timer = timer_read();
            }
        }
    }

    if (timer_elapsed(debounce_timer) > MOUSE_DEBOUNCE) debounce = false;

    if (state[4] & (1 << 7)) {
        report.buttons |= MOUSE_BTN1;
    } else {
        report.buttons &= ~MOUSE_BTN1;
    }

    update_member(&report.x, &y_offset);
    update_member(&report.y, &x_offset);

    return report;
}

const pointing_device_driver_t pointing_device_driver = {
    .init = init;
    .get_report = get_report;
};

#endif
