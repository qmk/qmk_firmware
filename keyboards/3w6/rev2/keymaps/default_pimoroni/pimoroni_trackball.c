/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include "pimoroni_trackball.h"
#include "i2c_master.h"

static uint8_t scrolling      = 0;
static int16_t x_offset       = 0;
static int16_t y_offset       = 0;
static int16_t h_offset       = 0;
static int16_t v_offset       = 0;
static float   precisionSpeed = 1;

static uint16_t i2c_timeout_timer;

#ifndef I2C_TIMEOUT
#    define I2C_TIMEOUT 100
#endif
#ifndef I2C_WAITCHECK
#    define I2C_WAITCHECK 1000
#endif
#ifndef MOUSE_DEBOUNCE
#    define MOUSE_DEBOUNCE 5
#endif

void trackball_set_rgbw(uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
    uint8_t data[] = {0x00, red, green, blue, white};
    i2c_transmit(TRACKBALL_WRITE, data, sizeof(data), I2C_TIMEOUT);
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

__attribute__((weak)) void trackball_check_click(bool pressed, report_mouse_t* mouse) {
    if (pressed) {
        mouse->buttons |= MOUSE_BTN1;
    } else {
        mouse->buttons &= ~MOUSE_BTN1;
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (true) {
        xprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    }


    if (!process_record_user(keycode, record)) { return false; }

/* If Mousekeys is disabled, then use handle the mouse button
 * keycodes.  This makes things simpler, and allows usage of
 * the keycodes in a consistent manner.  But only do this if
 * Mousekeys is not enable, so it's not handled twice.
 */
#ifndef MOUSEKEY_ENABLE
    if (IS_MOUSEKEY_BUTTON(keycode)) {
        report_mouse_t currentReport = pointing_device_get_report();
        if (record->event.pressed) {
            currentReport.buttons |= 1 << (keycode - KC_MS_BTN1);
        } else {
            currentReport.buttons &= ~(1 << (keycode - KC_MS_BTN1));
        }
        pointing_device_set_report(currentReport);
        pointing_device_send();
    }
#endif

    return true;
}

void trackball_register_button(bool pressed, enum mouse_buttons button) {
    report_mouse_t currentReport = pointing_device_get_report();
    if (pressed) {
        currentReport.buttons |= button;
    } else {
        currentReport.buttons &= ~button;
    }
    pointing_device_set_report(currentReport);
}

float trackball_get_precision(void) { return precisionSpeed; }
void  trackball_set_precision(float precision) { precisionSpeed = precision; }
bool  trackball_is_scrolling(void) { return scrolling; }
void  trackball_set_scrolling(bool scroll) { scrolling = scroll; }


__attribute__((weak)) void pointing_device_init(void) { trackball_set_rgbw(0x80, 0x00, 0x00, 0x00); }

bool pointing_device_task(void) {
    static bool     debounce;
    static uint16_t debounce_timer;
    uint8_t         state[5] = {};
    if (timer_elapsed(i2c_timeout_timer) > I2C_WAITCHECK) {
        if (i2c_read_register(TRACKBALL_WRITE, 0x04, state, 5, I2C_TIMEOUT) == I2C_STATUS_SUCCESS) {
            if (!state[4] && !debounce) {
                if (scrolling) {
#ifdef PIMORONI_TRACKBALL_INVERT_X
                    h_offset += mouse_offset(state[2], state[3], 1);
#else
                    h_offset -= mouse_offset(state[2], state[3], 1);
#endif
#ifdef PIMORONI_TRACKBALL_INVERT_Y
                    v_offset += mouse_offset(state[1], state[0], 1);
#else
                    v_offset -= mouse_offset(state[1], state[0], 1);
#endif
                } else {
#ifdef PIMORONI_TRACKBALL_INVERT_X
                    x_offset -= mouse_offset(state[2], state[3], 5);
#else
                    x_offset += mouse_offset(state[2], state[3], 5);
#endif
#ifdef PIMORONI_TRACKBALL_INVERT_Y
                    y_offset -= mouse_offset(state[1], state[0], 5);
#else
                    y_offset += mouse_offset(state[1], state[0], 5);
#endif
                }
            } else {
                if (state[4]) {
                    debounce       = true;
                    debounce_timer = timer_read();
                }
            }
        } else {
            i2c_timeout_timer = timer_read();
        }
    }

    if (timer_elapsed(debounce_timer) > MOUSE_DEBOUNCE) debounce = false;

    report_mouse_t mouse = pointing_device_get_report();
    // trackball_check_click(state[4] & (1 << 7), &mouse);

#ifndef PIMORONI_TRACKBALL_ROTATE
    update_member(&mouse.x, &x_offset);
    update_member(&mouse.y, &y_offset);
    update_member(&mouse.h, &h_offset);
    update_member(&mouse.v, &v_offset);
#else
    update_member(&mouse.x, &y_offset);
    update_member(&mouse.y, &x_offset);
    update_member(&mouse.h, &v_offset);
    update_member(&mouse.v, &h_offset);
#endif
    pointing_device_set_report(mouse);
    return pointing_device_send();
}
