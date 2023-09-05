#include QMK_KEYBOARD_H

bool set_scrolling = true;

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 2.0
#define SCROLL_DIVISOR_V 2.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// Function to handle mouse reports and perform (smoothed) drag scrolling
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (!set_scrolling){
        return mouse_report;
    }

    // Calculate and accumulate scroll values based on mouse movement and divisors
    scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
    scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

    // Assign integer parts of accumulated scroll values to the mouse report
    mouse_report.h = (int8_t)scroll_accumulated_h;
    mouse_report.v = (int8_t)scroll_accumulated_v;

    // Update accumulated scroll values by subtracting the integer parts
    scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
    scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

    // Clear the X and Y values of the mouse report
    mouse_report.x = mouse_report.y = 0;

    return mouse_report;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_0,
        KC_1,
                KC_3,
                KC_5,
        KC_6, KC_7,
        KC_8, KC_9,
        KC_A, KC_B,
        KC_C, KC_D,
        KC_E, KC_F,
        KC_G
    )
};
